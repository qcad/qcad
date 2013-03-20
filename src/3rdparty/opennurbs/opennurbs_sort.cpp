/* $NoKeywords: $ */
/*
//
// Copyright (c) 1993-2007 Robert McNeel & Associates. All rights reserved.
// Rhinoceros is a registered trademark of Robert McNeel & Assoicates.
//
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
// ALL IMPLIED WARRANTIES OF FITNESS FOR ANY PARTICULAR PURPOSE AND OF
// MERCHANTABILITY ARE HEREBY DISCLAIMED.
//				
// For complete openNURBS copyright information see <http://www.opennurbs.org>.
//
////////////////////////////////////////////////////////////////
*/

#include "opennurbs.h"

/* this parameter defines the cutoff between using quick sort and
   insertion sort for arrays; arrays with lengths shorter or equal to the
   below value use insertion sort */

#define CUTOFF 8            /* testing shows that this is good value */

/* Note: the theoretical number of stack entries required is
   no more than 1 + log2(num).  But we switch to insertion
   sort for CUTOFF elements or less, so we really only need
   1 + log2(num) - log2(CUTOFF) stack entries.  For a CUTOFF
   of 8, that means we need no more than 30 stack entries for
   32 bit platforms, and 62 for 64-bit platforms. */
#define STKSIZ (8*sizeof(void*) - 2)


//static void heapsort_dbl(double* e, size_t nel)
//{
//  size_t i_end,i,j,k;
//  double e_tmp;
//
//  if (nel < 2) 
//    return;
//  k = nel >> 1;
//  i_end = nel-1;
//  for (;;) 
//  {
//    if (k) 
//    {
//      --k;
//      e_tmp = e[k];
//    } 
//    else 
//    {
//      e_tmp = e[i_end];
//      e[i_end] = e[0];
//      if (!(--i_end)) 
//      {
//        e[0] = e_tmp;
//        break;
//      }
//    }
//    i = k;
//    j = (k<<1) + 1;
//    while (j <= i_end) 
//    {
//      if (j < i_end && e[j] < e[j + 1])
//        j++;
//      if (e_tmp < e[j]) 
//      {
//        e[i] = e[j];
//        i = j;
//        j = (j<<1) + 1;
//      } 
//      else
//        j = i_end + 1;
//    }
//    e[i] = e_tmp;
//  }
//}

static void bubblesort_dbl (double *lo,double *hi)
{
  double max_value;
  double *p, *max;

  while (hi > lo) 
  {
    max_value = *(max = lo);
    for (p = lo+1; p < hi; p++)
    {
      if ( *p > max_value ) 
      {
        max_value = *(max = p);
      }
    }
    if ( *hi < max_value )
    {
      *max = *hi;
    }
    hi--;
  }
}



void  ON_qsort_dbl (double *base, size_t count)
{
  double mid_value, tmp;
  double *lo, *hi;              /* ends of sub-array currently sorting */
  double *mid;                  /* points to middle of subarray */
  double *loguy, *higuy;        /* traveling pointers for partition step */
  double *lostk[STKSIZ], *histk[STKSIZ];
  int stkptr;                 /* stack for saving sub-array to be processed */

  if (count < 2)
      return;                 /* nothing to do */

  stkptr = 0;                 /* initialize stack */

  lo = base;
  hi = base + (count-1);        /* initialize limits */

  for(;;)
  {

    count = (hi - lo) + 1;        /* number of el's to sort */

    /* below a certain count, it is faster to use a O(n^2) sorting method */
    if (count <= CUTOFF) 
    {
      // TODO - determine which is faster
      bubblesort_dbl(lo, hi);
      //heapsort_dbl(lo,count);
    }
    else 
    {
      // The "quick sort" algorithm selects a "pivot" value in the set,
      // p, divides the set into two subsets L and H such that every 
      // element in L is <= p and every element in H is >= p, and 
      // then recurses on the subsets.
      //
      // The algorithm is fast when the subsets have about the same
      // size.  So, the goal is to consistently find p close to the
      // median value of the current set.
      //
      // There are various ways to select the pivot element.  See
      // http://en.wikipedia.org/wiki/Selection_algorithm 
      // http://en.wikipedia.org/wiki/Quicksort
      //
      // There are several standard ways to pick the pivot.
      //
      // 1) Set the pivot to the middle element of the list.
      //
      // 2) Set the pivot to the median of the the first, middle,
      //    and last elements in the list.
      //
      // 3) Set the pivot to a random element in the list.
      //    In order for this approach to be practical, you need
      //    a fast rand() function such that max_rand/count is
      //    large (otherwise you get a bias towards picking elements
      //    at the start of the list). The MSC rand() function 
      //    is not adequate for use here because its range 
      //    is 0 to 32767 and this sorting function needs to
      //    sort arrays larger than 32767.  The MSC rand_s() 
      //    function appears to be good enough because its
      //    range is 0 to 4294967295 (0xFFFFFFFF) and we don't
      //    sort arrays anywhere near that length.  To get
      //    an application to link the rand_s() function you
      //    must define _CRT_RAND_S before including any header
      //    system header files.
      //    
      // 4) Pick the median of medians.  Divide the list into groups
      //    of 5 elements, pick the median of each group, and then
      //    pick the median of the set of count/5 medians.
      //
      // The key is to optimize the function of selection time and
      // poor partitions

      //mid = lo + rand_s()%count; // random element
      mid = lo + (count / 2); // mid = middle element

      // Sort the first, middle, last elements into order.
      // The code is ugly, but it minimizes the number of 
      // comparisons and swaps.
      mid_value = *mid;
      if (mid_value < *lo) 
      {
        if ( mid_value < *hi )
        {
          if ( *hi < *lo )
          {
            // M < H < L
            mid_value = *hi;
            *hi  = *lo;
            *lo  = *mid;
            *mid = mid_value;
          }
          else
          {
            // M < L <= H
            mid_value = *lo;
            *lo = *mid;
            *mid = mid_value;
          }
        }
        else
        {
          // H <= M < L
          tmp = *hi;
          *hi = *lo;
          *lo = tmp;
        }
      }
      else if ( *hi < mid_value )
      {
        if ( *hi < *lo )
        {
          // H < L <= M
          mid_value = *lo;
          *lo  = *hi;
          *hi  = *mid;
          *mid = mid_value;
        }
        else
        {
          // L <= H < M
          mid_value = *hi;
          *hi = *mid;
          *mid = mid_value;
        }
      }
      // At this point *lo <= *mid <= *hi and mid_value = *mid

      if ( mid_value != *mid )
      {
        ON_ERROR("qsort lo,mid,hi sorter has a bug");
      }
      /* We now wish to partition the array into three pieces, one consisting
         of elements <= partition element, one of elements equal to the
         partition element, and one of elements > than it.  This is done
         below; comments indicate conditions established at every step. */

      loguy = lo;
      higuy = hi;

      for (;;) 
      {
        // At this point, the following conditions are met:
        //     lo <= loguy < hi
        //     lo < higuy <= hi
        //     loguy <= mid < higuy
        //     *lo,...,*loguy   <= mid_value
        //     if higuy < hi, then *higuy,...,*(hi-1) > mid_value
        //     *hi >= mid_value

        if ( loguy > hi || *loguy > mid_value )
        {
          ON_ERROR("THE NEXT LINE IS WRONG!");
        }
        // so, we can increment loguy
        loguy++;

        while ( loguy <= hi && *loguy <= mid_value )
          loguy++;

        /* lo < loguy <= hi+1, 
           *lo,...,*loguy-1 <= mid_value
           either loguy > hi or *loguy > mid_value
        */

        do  
        {
          higuy--;
        } while (higuy > mid && *higuy > mid_value);

        /* lo <= higuy < hi, 
           *higuy+1,...,*hi-1 > mid_value
           *higuy <= mid_value
         */


        // At this point,
        //   higuy < hi
        //   loguy > lo
        //   loguy > hi or *loguy > mid_value.
        //   higuy <= mid or *higuy <= mid_value.
        if (higuy < loguy)
          break;

        // At this point:
        //   lo < higuy < hi
        //   lo < loguy <= hi
        //   higuy >= loguy
        //   *loguy > mid_value
        //   *higuy <= mid_value
        // so, the values of loguy and higuy should be
        // swapped.
        //   

        tmp    = *loguy;
        *loguy = *higuy;
        *higuy = tmp;

        /* If the partition element was moved, follow it.  Only need
           to check for mid == higuy, since before the swap,
           A[loguy] > A[mid] implies loguy != mid. 
        */

        if (mid == higuy)
        {
          // The pivot element moved, update mid
          // Since *loguy was > mid_value, we do not
          // have to check for loguy == pivot
          mid = loguy;
        }

        /* A[loguy] <= A[mid], A[higuy] > A[mid]; so condition at top
           of loop is re-established */
      }

      /*     A[i] <= A[mid] for lo <= i < loguy,
             A[i] > A[mid] for higuy < i < hi,
             A[hi] >= A[mid]
             higuy < loguy
         implying:
             higuy == loguy-1
             or higuy == hi - 1, loguy == hi + 1, A[hi] == A[mid] */

      /* Find adjacent elements equal to the partition element.  The
         doubled loop is to avoid calling comp(mid,mid), since some
         existing comparison funcs don't work when passed the same value
         for both pointers. */

      higuy++;
      if (mid < higuy) 
      {
        do  {
            higuy--;
        } while (higuy > mid && *higuy == *mid);
      }
      if (mid >= higuy) 
      {
        do  {
            higuy--;
        } while (higuy > lo && *higuy == *mid);
      }

      /* OK, now we have the following:
            higuy < loguy
            lo <= higuy <= hi
            A[i]  <= A[mid] for lo <= i <= higuy
            A[i]  == A[mid] for higuy < i < loguy
            A[i]  >  A[mid] for loguy <= i < hi
            A[hi] >= A[mid] */

      /* We've finished the partition, now we want to sort the subarrays
         [lo, higuy] and [loguy, hi].
         We do the smaller one first to minimize stack usage.
         We only sort arrays of length 2 or more.*/

      if ( higuy - lo >= hi - loguy ) 
      {
        if (lo < higuy) 
        {
          lostk[stkptr] = lo;
          histk[stkptr] = higuy;
          ++stkptr;
        }                           /* save big recursion for later */

        if (loguy < hi) 
        {
          lo = loguy;
          //goto recurse;           /* do small recursion */
          continue;
        }
      }
      else 
      {
        if (loguy < hi) 
        {
          lostk[stkptr] = loguy;
          histk[stkptr] = hi;
          ++stkptr;               /* save big recursion for later */
        }

        if (lo < higuy) 
        {
          hi = higuy;
          //goto recurse;           /* do small recursion */
          continue;
        }
      }
    }

    /* We have sorted the array, except for any pending sorts on the stack.
       Check if there are any, and do them. */

    --stkptr;
    if (stkptr >= 0) 
    {
      lo = lostk[stkptr];
      hi = histk[stkptr];
      //goto recurse;           /* pop subarray from stack */
      continue;
    }

    break;
  }
}




static void shortsort_s(char *lo, char *hi, size_t width,int (*comp)(void *, const void *, const void *), void *);
#define swap swap_c

static void shortsort(char *lo, char *hi, size_t width,int (*comp)(const void *, const void *));

static void swap(char *p, char *q, size_t width);


/***
*qsort(base, num, wid, comp) - quicksort function for sorting arrays
*
*Purpose:
*   quicksort the array of elements
*   side effects:  sorts in place
*   maximum array size is number of elements times size of elements,
*   but is limited by the virtual address space of the processor
*
*Entry:
*   char *base = pointer to base of array
*   size_t num  = number of elements in the array
*   size_t width = width in bytes of each array element
*   int (*comp)() = pointer to function returning analog of strcmp for
*           strings, but supplied by user for comparing the array elements.
*           it accepts 2 pointers to elements.
*           Returns neg if 1<2, 0 if 1=2, pos if 1>2.
*
*Exit:
*   returns void
*
*Exceptions:
*   Input parameters are validated. Refer to the validation section of the function.
*
*******************************************************************************/

void  myqsort_s (
    void *base,
    size_t num,
    size_t width,
    int (*comp)(void *, const void *, const void *),
    void *context
    )
{
    char *lo, *hi;              /* ends of sub-array currently sorting */
    char *mid;                  /* points to middle of subarray */
    char *loguy, *higuy;        /* traveling pointers for partition step */
    size_t size;                /* size of the sub-array */
    char *lostk[STKSIZ], *histk[STKSIZ];
    int stkptr;                 /* stack for saving sub-array to be processed */

    if (num < 2)
        return;                 /* nothing to do */

    stkptr = 0;                 /* initialize stack */

    lo = (char *)base;
    hi = (char *)base + width * (num-1);        /* initialize limits */

    /* this entry point is for pseudo-recursion calling: setting
       lo and hi and jumping to here is like recursion, but stkptr is
       preserved, locals aren't, so we preserve stuff on the stack */
recurse:

    size = (hi - lo) / width + 1;        /* number of el's to sort */

    /* below a certain size, it is faster to use a O(n^2) sorting method */
    if (size <= CUTOFF) 
    {
        shortsort_s(lo, hi, width, comp, context);
    }
    else {
        /* First we pick a partitioning element.  The efficiency of the
           algorithm demands that we find one that is approximately the median
           of the values, but also that we select one fast.  We choose the
           median of the first, middle, and last elements, to avoid bad
           performance in the face of already sorted data, or data that is made
           up of multiple sorted runs appended together.  Testing shows that a
           median-of-three algorithm provides better performance than simply
           picking the middle element for the latter case. */

        mid = lo + (size / 2) * width;      /* find middle element */

        /* Sort the first, middle, last elements into order */
        if (comp(context, lo, mid) > 0) {
            swap(lo, mid, width);
        }
        if (comp(context, lo, hi) > 0) {
            swap(lo, hi, width);
        }
        if (comp(context, mid, hi) > 0) {
            swap(mid, hi, width);
        }

        /* We now wish to partition the array into three pieces, one consisting
           of elements <= partition element, one of elements equal to the
           partition element, and one of elements > than it.  This is done
           below; comments indicate conditions established at every step. */

        loguy = lo;
        higuy = hi;

        /* Note that higuy decreases and loguy increases on every iteration,
           so loop must terminate. */
        for (;;) {
            /* lo <= loguy < hi, lo < higuy <= hi,
               A[i] <= A[mid] for lo <= i <= loguy,
               A[i] > A[mid] for higuy <= i < hi,
               A[hi] >= A[mid] */

            /* The doubled loop is to avoid calling comp(mid,mid), since some
               existing comparison funcs don't work when passed the same
               value for both pointers. */

            if (mid > loguy) {
                do  {
                    loguy += width;
                } while (loguy < mid && comp(context, loguy, mid) <= 0);
            }
            if (mid <= loguy) {
                do  {
                    loguy += width;
                } while (loguy <= hi && comp(context, loguy, mid) <= 0);
            }

            /* lo < loguy <= hi+1, A[i] <= A[mid] for lo <= i < loguy,
               either loguy > hi or A[loguy] > A[mid] */

            do  {
                higuy -= width;
            } while (higuy > mid && comp(context, higuy, mid) > 0);

            /* lo <= higuy < hi, A[i] > A[mid] for higuy < i < hi,
               either higuy == lo or A[higuy] <= A[mid] */

            if (higuy < loguy)
                break;

            /* if loguy > hi or higuy == lo, then we would have exited, so
               A[loguy] > A[mid], A[higuy] <= A[mid],
               loguy <= hi, higuy > lo */

            swap(loguy, higuy, width);

            /* If the partition element was moved, follow it.  Only need
               to check for mid == higuy, since before the swap,
               A[loguy] > A[mid] implies loguy != mid. */

            if (mid == higuy)
                mid = loguy;

            /* A[loguy] <= A[mid], A[higuy] > A[mid]; so condition at top
               of loop is re-established */
        }

        /*     A[i] <= A[mid] for lo <= i < loguy,
               A[i] > A[mid] for higuy < i < hi,
               A[hi] >= A[mid]
               higuy < loguy
           implying:
               higuy == loguy-1
               or higuy == hi - 1, loguy == hi + 1, A[hi] == A[mid] */

        /* Find adjacent elements equal to the partition element.  The
           doubled loop is to avoid calling comp(mid,mid), since some
           existing comparison funcs don't work when passed the same value
           for both pointers. */

        higuy += width;
        if (mid < higuy) {
            do  {
                higuy -= width;
            } while (higuy > mid && comp(context, higuy, mid) == 0);
        }
        if (mid >= higuy) {
            do  {
                higuy -= width;
            } while (higuy > lo && comp(context, higuy, mid) == 0);
        }

        /* OK, now we have the following:
              higuy < loguy
              lo <= higuy <= hi
              A[i]  <= A[mid] for lo <= i <= higuy
              A[i]  == A[mid] for higuy < i < loguy
              A[i]  >  A[mid] for loguy <= i < hi
              A[hi] >= A[mid] */

        /* We've finished the partition, now we want to sort the subarrays
           [lo, higuy] and [loguy, hi].
           We do the smaller one first to minimize stack usage.
           We only sort arrays of length 2 or more.*/

        if ( higuy - lo >= hi - loguy ) {
            if (lo < higuy) {
                lostk[stkptr] = lo;
                histk[stkptr] = higuy;
                ++stkptr;
            }                           /* save big recursion for later */

            if (loguy < hi) {
                lo = loguy;
                goto recurse;           /* do small recursion */
            }
        }
        else {
            if (loguy < hi) {
                lostk[stkptr] = loguy;
                histk[stkptr] = hi;
                ++stkptr;               /* save big recursion for later */
            }

            if (lo < higuy) {
                hi = higuy;
                goto recurse;           /* do small recursion */
            }
        }
    }

    /* We have sorted the array, except for any pending sorts on the stack.
       Check if there are any, and do them. */

    --stkptr;
    if (stkptr >= 0) {
        lo = lostk[stkptr];
        hi = histk[stkptr];
        goto recurse;           /* pop subarray from stack */
    }
    else
        return;                 /* all subarrays done */
}

void  myqsort (
    void *base,
    size_t num,
    size_t width,
    int (*comp)(const void *, const void *)
    )
{
    char *lo, *hi;              /* ends of sub-array currently sorting */
    char *mid;                  /* points to middle of subarray */
    char *loguy, *higuy;        /* traveling pointers for partition step */
    size_t size;                /* size of the sub-array */
    char *lostk[STKSIZ], *histk[STKSIZ];
    int stkptr;                 /* stack for saving sub-array to be processed */

    if (num < 2)
        return;                 /* nothing to do */

    stkptr = 0;                 /* initialize stack */

    lo = (char *)base;
    hi = (char *)base + width * (num-1);        /* initialize limits */

    /* this entry point is for pseudo-recursion calling: setting
       lo and hi and jumping to here is like recursion, but stkptr is
       preserved, locals aren't, so we preserve stuff on the stack */
recurse:

    size = (hi - lo) / width + 1;        /* number of el's to sort */

    /* below a certain size, it is faster to use a O(n^2) sorting method */
    if (size <= CUTOFF) 
    {
        shortsort(lo, hi, width, comp);
    }
    else {
        /* First we pick a partitioning element.  The efficiency of the
           algorithm demands that we find one that is approximately the median
           of the values, but also that we select one fast.  We choose the
           median of the first, middle, and last elements, to avoid bad
           performance in the face of already sorted data, or data that is made
           up of multiple sorted runs appended together.  Testing shows that a
           median-of-three algorithm provides better performance than simply
           picking the middle element for the latter case. */

        mid = lo + (size / 2) * width;      /* find middle element */

        /* Sort the first, middle, last elements into order */
        if (comp(lo, mid) > 0) {
            swap(lo, mid, width);
        }
        if (comp(lo, hi) > 0) {
            swap(lo, hi, width);
        }
        if (comp(mid, hi) > 0) {
            swap(mid, hi, width);
        }

        /* We now wish to partition the array into three pieces, one consisting
           of elements <= partition element, one of elements equal to the
           partition element, and one of elements > than it.  This is done
           below; comments indicate conditions established at every step. */

        loguy = lo;
        higuy = hi;

        /* Note that higuy decreases and loguy increases on every iteration,
           so loop must terminate. */
        for (;;) {
            /* lo <= loguy < hi, lo < higuy <= hi,
               A[i] <= A[mid] for lo <= i <= loguy,
               A[i] > A[mid] for higuy <= i < hi,
               A[hi] >= A[mid] */

            /* The doubled loop is to avoid calling comp(mid,mid), since some
               existing comparison funcs don't work when passed the same
               value for both pointers. */

            if (mid > loguy) {
                do  {
                    loguy += width;
                } while (loguy < mid && comp(loguy, mid) <= 0);
            }
            if (mid <= loguy) {
                do  {
                    loguy += width;
                } while (loguy <= hi && comp(loguy, mid) <= 0);
            }

            /* lo < loguy <= hi+1, A[i] <= A[mid] for lo <= i < loguy,
               either loguy > hi or A[loguy] > A[mid] */

            do  {
                higuy -= width;
            } while (higuy > mid && comp(higuy, mid) > 0);

            /* lo <= higuy < hi, A[i] > A[mid] for higuy < i < hi,
               either higuy == lo or A[higuy] <= A[mid] */

            if (higuy < loguy)
                break;

            /* if loguy > hi or higuy == lo, then we would have exited, so
               A[loguy] > A[mid], A[higuy] <= A[mid],
               loguy <= hi, higuy > lo */

            swap(loguy, higuy, width);

            /* If the partition element was moved, follow it.  Only need
               to check for mid == higuy, since before the swap,
               A[loguy] > A[mid] implies loguy != mid. */

            if (mid == higuy)
                mid = loguy;

            /* A[loguy] <= A[mid], A[higuy] > A[mid]; so condition at top
               of loop is re-established */
        }

        /*     A[i] <= A[mid] for lo <= i < loguy,
               A[i] > A[mid] for higuy < i < hi,
               A[hi] >= A[mid]
               higuy < loguy
           implying:
               higuy == loguy-1
               or higuy == hi - 1, loguy == hi + 1, A[hi] == A[mid] */

        /* Find adjacent elements equal to the partition element.  The
           doubled loop is to avoid calling comp(mid,mid), since some
           existing comparison funcs don't work when passed the same value
           for both pointers. */

        higuy += width;
        if (mid < higuy) {
            do  {
                higuy -= width;
            } while (higuy > mid && comp(higuy, mid) == 0);
        }
        if (mid >= higuy) {
            do  {
                higuy -= width;
            } while (higuy > lo && comp(higuy, mid) == 0);
        }

        /* OK, now we have the following:
              higuy < loguy
              lo <= higuy <= hi
              A[i]  <= A[mid] for lo <= i <= higuy
              A[i]  == A[mid] for higuy < i < loguy
              A[i]  >  A[mid] for loguy <= i < hi
              A[hi] >= A[mid] */

        /* We've finished the partition, now we want to sort the subarrays
           [lo, higuy] and [loguy, hi].
           We do the smaller one first to minimize stack usage.
           We only sort arrays of length 2 or more.*/

        if ( higuy - lo >= hi - loguy ) {
            if (lo < higuy) {
                lostk[stkptr] = lo;
                histk[stkptr] = higuy;
                ++stkptr;
            }                           /* save big recursion for later */

            if (loguy < hi) {
                lo = loguy;
                goto recurse;           /* do small recursion */
            }
        }
        else {
            if (loguy < hi) {
                lostk[stkptr] = loguy;
                histk[stkptr] = hi;
                ++stkptr;               /* save big recursion for later */
            }

            if (lo < higuy) {
                hi = higuy;
                goto recurse;           /* do small recursion */
            }
        }
    }

    /* We have sorted the array, except for any pending sorts on the stack.
       Check if there are any, and do them. */

    --stkptr;
    if (stkptr >= 0) {
        lo = lostk[stkptr];
        hi = histk[stkptr];
        goto recurse;           /* pop subarray from stack */
    }
    else
        return;                 /* all subarrays done */
}


/***
*shortsort(hi, lo, width, comp) - insertion sort for sorting short arrays
*shortsort_s(hi, lo, width, comp, context) - insertion sort for sorting short arrays
*
*Purpose:
*       sorts the sub-array of elements between lo and hi (inclusive)
*       side effects:  sorts in place
*       assumes that lo < hi
*
*Entry:
*       char *lo = pointer to low element to sort
*       char *hi = pointer to high element to sort
*       size_t width = width in bytes of each array element
*       int (*comp)() = pointer to function returning analog of strcmp for
*               strings, but supplied by user for comparing the array elements.
*               it accepts 2 pointers to elements, together with a pointer to a context
*               (if present). Returns neg if 1<2, 0 if 1=2, pos if 1>2.
*       void *context - pointer to the context in which the function is
*               called. This context is passed to the comparison function.
*
*Exit:
*       returns void
*
*Exceptions:
*
*******************************************************************************/

static void shortsort_s (
    char *lo,
    char *hi,
    size_t width,
    int (*comp)(void *, const void *, const void *),
    void * context
    )
{
    char *p, *max;

    /* Note: in assertions below, i and j are alway inside original bound of
       array to sort. */

    while (hi > lo) {
        /* A[i] <= A[j] for i <= j, j > hi */
        max = lo;
        for (p = lo+width; p <= hi; p += width) {
            /* A[i] <= A[max] for lo <= i < p */
            if (comp(context, p, max) > 0) {
                max = p;
            }
            /* A[i] <= A[max] for lo <= i <= p */
        }

        /* A[i] <= A[max] for lo <= i <= hi */

        swap(max, hi, width);

        /* A[i] <= A[hi] for i <= hi, so A[i] <= A[j] for i <= j, j >= hi */

        hi -= width;

        /* A[i] <= A[j] for i <= j, j > hi, loop top condition established */
    }
    /* A[i] <= A[j] for i <= j, j > lo, which implies A[i] <= A[j] for i < j,
       so array is sorted */
}

static void shortsort (
    char *lo,
    char *hi,
    size_t width,
    int (*comp)(const void *, const void *)
    )
{
    char *p, *max;

    /* Note: in assertions below, i and j are alway inside original bound of
       array to sort. */

    while (hi > lo) 
    {
        /* A[i] <= A[j] for i <= j, j > hi */
        max = lo;
        for (p = lo+width; p <= hi; p += width) {
            /* A[i] <= A[max] for lo <= i < p */
            if (comp( p, max) > 0) {
                max = p;
            }
            /* A[i] <= A[max] for lo <= i <= p */
        }

        /* A[i] <= A[max] for lo <= i <= hi */

        swap(max, hi, width);

        /* A[i] <= A[hi] for i <= hi, so A[i] <= A[j] for i <= j, j >= hi */

        hi -= width;

        /* A[i] <= A[j] for i <= j, j > hi, loop top condition established */
    }
    /* A[i] <= A[j] for i <= j, j > lo, which implies A[i] <= A[j] for i < j,
       so array is sorted */
}

static void swap (char *a,char *b,size_t width)
{
    char tmp;

    if ( a != b )
    {
        while ( width-- ) 
        {
            tmp = *a;
            *a++ = *b;
            *b++ = tmp;
        }
    }
}
