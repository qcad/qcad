//
// Copyright (c) 1993-2022 Robert McNeel & Associates. All rights reserved.
// OpenNURBS, Rhinoceros, and Rhino3D are registered trademarks of Robert
// McNeel & Associates.
//
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
// ALL IMPLIED WARRANTIES OF FITNESS FOR ANY PARTICULAR PURPOSE AND OF
// MERCHANTABILITY ARE HEREBY DISCLAIMED.
//				
// For complete openNURBS copyright information see <http://www.opennurbs.org>.
//
////////////////////////////////////////////////////////////////

/*
See opennurbs_sort.cpp for examples showing how to use
opennurbs_quacksort_template.h to define type specific
sorting functions.
*/

#if !defined(ON_QSORT_FNAME)
#error Define ON_QSORT_FNAME macro before including opennurbs_quacksort_template.h
#endif

// ON_SORT_TEMPLATE_TYPE -> double, int, ....
#if !defined(ON_SORT_TEMPLATE_TYPE)

#define BASETYPE void *
#define DATATYPE unsigned char
#define DATAWIDTH m_width

#define Swap(a,b) m_swapfunc(a,b,m_width)

#if defined(ON_SORT_TEMPLATE_USE_CONTEXT)
// use a compare function with context parameter
#define GreaterThan(A,B) m_compare(m_context,A,B) > 0
#else
// use a compare function without context parameter
#define GreaterThan(A,B) m_compare(A,B) > 0
#endif

#else

#define BASETYPE ON_SORT_TEMPLATE_TYPE *
#define DATATYPE ON_SORT_TEMPLATE_TYPE
#define DATAWIDTH 1

#if defined(ON_SORT_TEMPLATE_USE_SWAP)
#define Swap(a,b) m_swapfunc(a,b,m_width)
#else
// use intrinsic assignment
#define Swap(a,b) ON_SORT_TEMPLATE_TYPE tmp = *a; *a = *b; *b = tmp
#endif

#if defined(ON_SORT_TEMPLATE_COMPARE)
// use a compare function like strcmp for char* strings
#define GreaterThan(A,B) ON_SORT_TEMPLATE_COMPARE(A,B) > 0
#else
// use intrinsic type compares
#define GreaterThan(A,B) *A > *B
#endif

#endif

#if !defined(ON_QUACKSORT_SWAP_FUNCS_DEFINED)
#if !defined(ON_SORT_TEMPLATE_TYPE) || defined(ON_SORT_TEMPLATE_USE_SWAP)

// In some files this template is used multiple times.
// The ON_QUACKSORT_SWAP_FUNCS_DEFINED define prevents
// multiple definitions of the static Swap*() functions.
#define ON_QUACKSORT_SWAP_FUNCS_DEFINED

static void SwapChars( unsigned char* a, unsigned char* b, size_t width)
{
  do
  {
    unsigned char x = *a;
    *a++ = *b;
    *b++ = x;
  }
  while( --width);
}

static void SwapInts( unsigned char* a, unsigned char* b, size_t width)
{
  ON__UINT32* ai = (ON__UINT32*)a;
  ON__UINT32* bi = (ON__UINT32*)b;
  do
  {
    ON__UINT32 x = *ai;
    *ai++ = *bi;
    *bi++ = x;
    width -= sizeof(x);
  }
  while( width);
}

static void SwapBigInts( unsigned char* a, unsigned char* b, size_t width)
{
  ON__UINT64* ai = (ON__UINT64*)a;
  ON__UINT64* bi = (ON__UINT64*)b;
  do
  {
    ON__UINT64 x = *ai;
    *ai++ = *bi;
    *bi++ = x;
    width -= sizeof(x);
  }
  while( width);
}

#endif
#endif

// implementation of quick sort with minimum swaps for partition sizes 4 and less
void ON_quacksort( 
  BASETYPE *base
  ,size_t nel
#if !defined(ON_SORT_TEMPLATE_TYPE)
  ,size_t width
#if defined(ON_SORT_TEMPLATE_USE_CONTEXT)
  ,int (*compar)(void*, const void *, const void *)
  ,void* context
#else
  ,int (*compar)(const void *, const void *)
#endif
#endif
  )
{
  class CSorter
  {
  public:
    DATATYPE *m_base;
    size_t m_nel;
    const size_t m_width;
    int (*m_compar)(const void *, const void *);
    void (*m_swapfunc)(unsigned char *, unsigned char *, size_t width);
    unsigned int m_rnd;
//#if defined(ON_SORT_TEMPLATE_TYPE) && !defined(ON_SORT_TEMPLATE_USE_SWAP)
//    ON_SORT_TEMPLATE_TYPE m_tmp;
//#endif

    CSorter( 
      DATATYPE *base
      , size_t nel
      , size_t width
      , int (*compar)(const void *, const void *)
      )
      : m_base((DATATYPE*)base)
      , m_nel(nel)
      , m_width(width)
      , m_compar(compar)
      , m_rnd(62538161)
    {
      // When width is a multiple of 8 or 4 (with most arrays it probably is),
      // use faster integer swappers instead of byte swapper
      if ( 0 == width%sizeof(ON__UINT64))
        m_swapfunc = SwapBigInts;
      else if ( 0 == width%sizeof(ON__UINT32))
        m_swapfunc = SwapInts;
      else
        m_swapfunc = SwapChars;
    };

    ~CSorter() {};

    DATATYPE* Pivot( DATATYPE* base, size_t count)
    {
      // Uses local quick and dirty pseudorandom number generator to 
      // give a fuzzy answer to avoid having the data be arranged in 
      // a way that mechanically always picking the pivot the same way 
      // affects the speed. Mostly affects chevron etc. patterns.
      // 
      // Totally random pivot would guarantee O(nlogn) worst case, but 
      // does not perform as well on sorted or nearly sorted sets.

      m_rnd *= 1664525;
      m_rnd += 1013904223;
      unsigned int dice = (m_rnd>>16)&7;

      size_t p=count>>1; // 1/2

      if ( dice&4)
        p += count>>3;  // +1/8
      if ( dice&2)
        p -= count>>4;  // -1/16
      if ( dice&1)
        p -= count>>5;  // -1/32

      return base + p*DATAWIDTH;
    }

    void SortSmallRange( DATATYPE* p0, size_t count)
    {
      // use minimum compares and swaps for 2 to 4 items
      switch (count)
      {
      case 2:
        {
          DATATYPE* p1 = p0 + DATAWIDTH;
          if ( GreaterThan( p0, p1)) { Swap( p0, p1);}
          return;
        }
      case 3:
        {
          DATATYPE* p1 = p0 + DATAWIDTH;
          DATATYPE* p2 = p1 + DATAWIDTH;
          bool b = false;
          if ( GreaterThan( p0, p1)) { Swap( p0, p1); b = true;}
          if ( GreaterThan( p1, p2)) { Swap( p1, p2); b = true;}
          if ( b && GreaterThan( p0, p1)) { Swap( p0, p1);}
          return;
        }
      case 4:
        {
          DATATYPE* p1 = p0 + DATAWIDTH;
          DATATYPE* p2 = p1 + DATAWIDTH;
          DATATYPE* p3 = p2 + DATAWIDTH;
          if ( GreaterThan( p0, p3)) { Swap( p0, p3);}
          if ( GreaterThan( p1, p2)) { Swap( p1, p2);}
          bool b = false;
          if ( GreaterThan( p2, p3)) { Swap( p2, p3); b = true;}
          if ( GreaterThan( p0, p1)) { Swap( p0, p1); b = true;}
          if ( b && GreaterThan( p1, p2)) { Swap( p1, p2);}
          return;
        }
      }
    }

    void SortRange( DATATYPE* left, DATATYPE* right)
    { 
      while ( left<right)
      { 
        size_t count = (right-left)/DATAWIDTH+1;

        if ( count < 5)
          return SortSmallRange( left, count);

        DATATYPE* pivotleft;
        DATATYPE* pivotright;

        // partition range
        { 
          pivotleft = Pivot( left, count);

          // move pivot to left end
          Swap( left, pivotleft);

          pivotleft = left;
          pivotright = right + DATAWIDTH;
          
          // move =< pivot to left, and > pivot to right
          for(;;)
          {
            // find next first item > pivot
            pivotleft += DATAWIDTH;
            if ( pivotleft >= pivotright)
              break;
            if ( !GreaterThan( pivotleft, left))
              continue;

            // find next last item =< pivot
            do
            {
              pivotright -= DATAWIDTH;
              if ( pivotleft >= pivotright)
                goto END; // to quickly exit a nested loop
            }
            while( GreaterThan( pivotright, left));

            Swap( pivotleft, pivotright);
          }

          END:

          pivotright -= DATAWIDTH;
          // move pivot to final place
          Swap( left, pivotright);
          pivotleft = pivotright;

          // avoid overhead when not likely that there are multiple items == pivot
          if ( pivotright >= right)
          {
            // the whole range is less or equal than pivot
            // check if there are values == pivot left of it. Speeds up sorting arrays with all or lots of equal items.
            for ( pivotleft -= DATAWIDTH; pivotleft > left; pivotleft -= DATAWIDTH)
            {
              if ( GreaterThan( pivotright, pivotleft))
                break;
            }
            pivotleft += DATAWIDTH;
          }
        }

        // limit max recursion depth to log(nel) by only recursing shorter part
        if ( pivotleft-left < right-pivotright)
        {
          // lower part is shorter
          SortRange( left, pivotleft-DATAWIDTH);
          left = pivotright+DATAWIDTH;
        }
        else
        {
          // upper part is shorter
          SortRange( pivotright+DATAWIDTH, right);
          right = pivotleft-DATAWIDTH;
        }
      }
    }

    void Sort()
    {
      SortRange( m_base, m_base + (m_nel-1)*DATAWIDTH);
    }
  };

  if ( !base || nel < 2 )
    return;
#if !defined(ON_SORT_TEMPLATE_TYPE)
  if ( width < 1 || !compar)
    return;
#endif

  CSorter sorter( base, nel, width, compar);
  sorter.Sort();
}

#undef Swap
#undef GreaterThan
#undef DATAWIDTH
#undef DATATYPE
