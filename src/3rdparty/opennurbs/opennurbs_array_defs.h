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

#if !defined(ON_ARRAY_DEFS_INC_)
#define ON_ARRAY_DEFS_INC_

// When this file is parsed with /W4 warnings, two bogus warnings
// are generated.
#pragma ON_PRAGMA_WARNING_PUSH

// The ON_ClassArray<T>::DestroyElement template function generates a
//   C4100: 'x' : unreferenced formal parameter 
// warning.
// This appears to be caused by a bug in the compiler warning code 
// or the way templates are expanded. This pragma is needed squelch the
// bogus warning.
#pragma ON_PRAGMA_WARNING_DISABLE_MSC(4100)

// The ON_CompareIncreasing and ON_CompareDecreasing templates generate a
//   C4211: nonstandard extension used : redefined extern to static
// warning.  Microsoft's compiler appears to have a little trouble 
// when static functions are declared before they are defined in a 
// single .cpp file. This pragma is needed squelch the bogus warning.
#pragma ON_PRAGMA_WARNING_DISABLE_MSC(4211)

// The main reason the definitions of the functions for the 
// ON_SimpleArray and ON_ClassArray templates are in this separate
// file is so that the Microsoft developer studio autocomplete
// functions will work on these classes.
//
// This file is included by opennurbs_array.h in the appropriate
// spot.  If you need the definitions in the file, then you
// should include opennurbs_array.h and let it take care of
// including this file.


/////////////////////////////////////////////////////////////////////////////////////
//  Class ON_SimpleArray<>
/////////////////////////////////////////////////////////////////////////////////////

// construction ////////////////////////////////////////////////////////

template <class T>
T* ON_SimpleArray<T>::Realloc(T* ptr,int capacity)
{
  return (T*)onrealloc(ptr,capacity*sizeof(T));
}

template <class T>
ON_SimpleArray<T>::ON_SimpleArray() ON_NOEXCEPT
  : m_a(nullptr)
  , m_count(0)
  , m_capacity(0)
{}

template <class T>
ON_SimpleArray<T>::ON_SimpleArray( size_t c )
  : m_a(nullptr)
  , m_count(0)
  , m_capacity(0)
{
  if ( c > 0 ) 
    SetCapacity( c );
}

// Copy constructor
template <class T>
ON_SimpleArray<T>::ON_SimpleArray( const ON_SimpleArray<T>& src )
  : m_a(0)
  , m_count(0)
  , m_capacity(0)
{
  *this = src; // operator= defined below
}

template <class T>
ON_SimpleArray<T>::~ON_SimpleArray()
{ 
  SetCapacity(0);
}

template <class T>
ON_SimpleArray<T>& ON_SimpleArray<T>::operator=( const ON_SimpleArray<T>& src )
{
  if( this != &src ) {
    if ( src.m_count <= 0 ) {
      m_count = 0;
    }
    else {
      if ( m_capacity < src.m_count ) {
        SetCapacity( src.m_count );
      }
      if ( m_a ) {
        m_count = src.m_count;
        memcpy( (void*)(m_a), (void*)(src.m_a), m_count*sizeof(T) );
      }
    }
  }  
  return *this;
}

#if defined(ON_HAS_RVALUEREF)

// Clone constructor
template <class T>
ON_SimpleArray<T>::ON_SimpleArray( ON_SimpleArray<T>&& src ) ON_NOEXCEPT
  : m_a(src.m_a)
  , m_count(src.m_count)
  , m_capacity(src.m_capacity)
{
  src.m_a = 0;
  src.m_count = 0;
  src.m_capacity = 0;
}

// Clone assignment
template <class T>
ON_SimpleArray<T>& ON_SimpleArray<T>::operator=( ON_SimpleArray<T>&& src ) ON_NOEXCEPT
{
  if( this != &src ) 
  {
    this->Destroy();
    m_a = src.m_a;
    m_count = src.m_count;
    m_capacity = src.m_capacity;
    src.m_a = 0;
    src.m_count = 0;
    src.m_capacity = 0;
  }  
  return *this;
}

#endif

// emergency destroy ///////////////////////////////////////////////////

template <class T>
void ON_SimpleArray<T>::EmergencyDestroy(void)
{
  m_count = 0;
  m_capacity = 0;
  m_a = 0;
}

// query ///////////////////////////////////////////////////////////////

template <class T>
int ON_SimpleArray<T>::Count() const
{
  return m_count;
}

template <class T>
unsigned int ON_SimpleArray<T>::UnsignedCount() const
{
  return ((unsigned int)m_count);
}

template <class T>
int ON_SimpleArray<T>::Capacity() const
{
  return m_capacity;
}

template <class T>
unsigned int ON_SimpleArray<T>::SizeOfArray() const
{
  return ((unsigned int)(m_capacity*sizeof(T)));
}

template <class T>
unsigned int ON_SimpleArray<T>::SizeOfElement() const
{
  return ((unsigned int)(sizeof(T)));
}


template <class T>
ON__UINT32 ON_SimpleArray<T>::DataCRC(ON__UINT32 current_remainder) const
{
  return ON_CRC32(current_remainder,m_count*sizeof(m_a[0]),m_a);
}

template <class T>
T& ON_SimpleArray<T>::operator[]( int i )
{ 
#if defined(ON_DEBUG)
  if ( i < 0 || i > m_capacity )
  {
    ON_ERROR("ON_SimpleArray[i]: i out of range.");
  }
#endif
  return m_a[i]; 
}

template <class T>
T& ON_SimpleArray<T>::operator[]( unsigned int i )
{ 
#if defined(ON_DEBUG)
  if ( i > (unsigned int)m_capacity )
  {
    ON_ERROR("ON_SimpleArray[i]: i out of range.");
  }
#endif
  return m_a[i]; 
}


template <class T>
T& ON_SimpleArray<T>::operator[]( ON__INT64 i )
{ 
#if defined(ON_DEBUG)
  if ( i < 0 || i > (ON__INT64)m_capacity )
  {
    ON_ERROR("ON_SimpleArray[i]: i out of range.");
  }
#endif
  return m_a[i]; 
}

template <class T>
T& ON_SimpleArray<T>::operator[]( ON__UINT64 i )
{ 
#if defined(ON_DEBUG)
  if ( i > (ON__UINT64)m_capacity )
  {
    ON_ERROR("ON_SimpleArray[i]: i out of range.");
  }
#endif
  return m_a[i]; 
}


#if defined(ON_RUNTIME_APPLE)
template <class T>
T& ON_SimpleArray<T>::operator[](size_t i )
{ 
#if defined(ON_DEBUG)
  if ( i > (size_t)m_capacity )
  {
    ON_ERROR("ON_SimpleArray[i]: i out of range.");
  }
#endif
  return m_a[i]; 
}
#endif

template <class T>
const T& ON_SimpleArray<T>::operator[](int i) const
{
#if defined(ON_DEBUG)
  if ( i < 0 || i > m_capacity )
  {
    ON_ERROR("ON_SimpleArray[i]: i out of range.");
  }
#endif
  return m_a[i];
}

template <class T>
const T& ON_SimpleArray<T>::operator[](unsigned int i) const
{
#if defined(ON_DEBUG)
  if ( i > (unsigned int)m_capacity )
  {
    ON_ERROR("ON_SimpleArray[i]: i out of range.");
  }
#endif
  return m_a[i];
}


template <class T>
const T& ON_SimpleArray<T>::operator[](ON__INT64 i) const
{
#if defined(ON_DEBUG)
  if ( i < 0 || i > ((ON__INT64)m_capacity) )
  {
    ON_ERROR("ON_SimpleArray[i]: i out of range.");
  }
#endif
  return m_a[i];
}

template <class T>
const T& ON_SimpleArray<T>::operator[](ON__UINT64 i) const
{
#if defined(ON_DEBUG)
  if ( i > (ON__UINT64)m_capacity )
  {
    ON_ERROR("ON_SimpleArray[i]: i out of range.");
  }
#endif
  return m_a[i];
}

#if defined(ON_RUNTIME_APPLE)
template <class T>
const T& ON_SimpleArray<T>::operator[](size_t i) const
{
#if defined(ON_DEBUG)
  if ( i > (size_t)m_capacity )
  {
    ON_ERROR("ON_SimpleArray[i]: i out of range.");
  }
#endif
  return m_a[i];
}
#endif

template <class T>
ON_SimpleArray<T>::operator T*()
{
  return (m_count > 0) ? m_a : 0;
}

template <class T>
ON_SimpleArray<T>::operator const T*() const
{
  return (m_count > 0) ? m_a : 0;
}

template <class T>
T* ON_SimpleArray<T>::Array()
{
  return m_a;
}

template <class T>
const T* ON_SimpleArray<T>::Array() const
{
  return m_a;
}

template <class T>
T* ON_SimpleArray<T>::KeepArray()
{
  T* p = m_a;
  m_a = 0;
  m_count = 0;
  m_capacity = 0;
  return p;
}

template <class T>
void ON_SimpleArray<T>::SetArray(T* p)
{
  if ( m_a && m_a != p )
    onfree(m_a);
  m_a = p;
}

template <class T>
void ON_SimpleArray<T>::SetArray(T* p, int count, int capacity)
{
  if ( m_a && m_a != p )
    onfree(m_a);
  m_a = p;
  m_count = count;
  m_capacity = capacity;
}

template <class T>
T* ON_SimpleArray<T>::First()
{ 
  return (m_count > 0) ? m_a : 0;
}

template <class T>
const T* ON_SimpleArray<T>::First() const
{
  return (m_count > 0) ? m_a : 0;
}

template <class T>
T* ON_SimpleArray<T>::At( int i )
{ 
  return (i >= 0 && i < m_count) ? m_a+i : 0;
}

template <class T>
T* ON_SimpleArray<T>::At( unsigned int i )
{ 
  return (i < (unsigned int)m_count) ? m_a+i : 0;
}

template <class T>
const T* ON_SimpleArray<T>::At( int i) const
{
  return (i >= 0 && i < m_count) ? m_a+i : 0;
}

template <class T>
const T* ON_SimpleArray<T>::At( unsigned int i) const
{
  return (i < (unsigned int)m_count) ? m_a+i : 0;
}

template <class T>
T* ON_SimpleArray<T>::At( ON__INT64 i )
{ 
  return (i >= 0 && i < (ON__INT64)m_count) ? m_a+i : 0;
}

template <class T>
T* ON_SimpleArray<T>::At( ON__UINT64 i )
{ 
  return (i < (ON__UINT64)m_count) ? m_a+i : 0;
}

template <class T>
const T* ON_SimpleArray<T>::At( ON__INT64 i) const
{
  return (i >= 0 && i < (ON__INT64)m_count) ? m_a+i : 0;
}

template <class T>
const T* ON_SimpleArray<T>::At( ON__UINT64 i) const
{
  return (i < (ON__UINT64)m_count) ? m_a+i : 0;
}

template <class T>
T* ON_SimpleArray<T>::Last()
{ 
  return (m_count > 0) ? m_a+(m_count-1) : 0;
}

template <class T>
const T* ON_SimpleArray<T>::Last() const
{
  return (m_count > 0) ? m_a+(m_count-1) : 0;
}

// array operations ////////////////////////////////////////////////////

template <class T>
void ON_SimpleArray<T>::Move( int dest_i, int src_i, int ele_cnt )
{
  // private function for moving blocks of array memory
  // caller is responsible for updating m_count.
  if ( ele_cnt <= 0 || src_i < 0 || dest_i < 0 || src_i == dest_i || 
       src_i + ele_cnt > m_count || dest_i > m_count )
    return;

  int capacity = dest_i + ele_cnt;
  if ( capacity > m_capacity ) {
    if ( capacity < 2*m_capacity )
      capacity = 2*m_capacity;
    SetCapacity( capacity );
  }

  memmove( (void*)&m_a[dest_i], (void*)&m_a[src_i], ele_cnt*sizeof(T) );
}

template <class T>
T& ON_SimpleArray<T>::AppendNew()
{
  if ( m_count == m_capacity ) 
  {
    int new_capacity = NewCapacity();
    Reserve( new_capacity );
  }
  memset( (void*)(&m_a[m_count]), 0, sizeof(T) );
  return m_a[m_count++];
}

template <class T>
void ON_SimpleArray<T>::Append( const T& x ) 
{
  const T* p = &x;
  if ( m_count == m_capacity ) 
  {
    const int newcapacity = NewCapacity();
    if ( p >= m_a && p < (m_a + m_capacity) )
    {
      // 26 Sep 2005 Dale Lear
      // x is in the block of memory about to be reallocated.
      void* temp = onmalloc(sizeof(T));
      memcpy(temp, (void*)p, sizeof(T));
      p = (T*)temp;
    }
    Reserve(newcapacity);
    if (nullptr == m_a)
    {
      ON_ERROR("allocation failure");
      return;
    }
  }
  m_a[m_count++] = *p;
  if (p != &x)
    onfree((void*)p);
}

template <class T>
void ON_SimpleArray<T>::Append( int count, const T* buffer ) 
{
  if ( count > 0 && nullptr != buffer ) 
  {
    const size_t sizeof_buffer = count * sizeof(T);
    void* temp = nullptr;
    if ( count + m_count > m_capacity ) 
    {
      int newcapacity = NewCapacity();
      if ( newcapacity < count + m_count )
        newcapacity = count + m_count;
      if ( buffer >= m_a && buffer < (m_a + m_capacity) )
      {
        // buffer is in the block of memory about to be reallocated
        temp = onmalloc(sizeof_buffer);
        memcpy(temp, buffer, sizeof_buffer);
        buffer = (const T*)temp;
      }
      Reserve( newcapacity );
    }
    memcpy( (void*)(m_a + m_count), (void*)(buffer), sizeof_buffer );
    if (nullptr != temp)
      onfree(temp);
    m_count += count;
  }
}


template <class T>
void ON_SimpleArray<T>::Prepend( int count, const T* buffer ) 
{
  if ( count > 0 && nullptr != buffer ) 
  {
    const size_t sizeof_buffer = count * sizeof(T);
    void* temp = nullptr;
    if ( count + m_count > m_capacity ) 
    {
      int newcapacity = NewCapacity();
      if ( newcapacity < count + m_count )
        newcapacity = count + m_count;
      if ( buffer >= m_a && buffer < (m_a + m_capacity) )
      {
        // buffer is in the block of memory about to be reallocated
        temp = onmalloc(sizeof_buffer);
        memcpy(temp, buffer, sizeof_buffer);
        buffer = (const T*)temp;
      }
      Reserve( newcapacity );
    }

    const size_t count0 = (size_t)m_count;
    const size_t count1 = count0 + ((size_t)count);
    T* p0 = m_a;
    T* p = p0 + count0;
    T* p1 = m_a + count1;
    while (p > p0)
      *(--p1) = *(--p);
    memcpy( (void*)(m_a), (void*)(buffer), sizeof_buffer );
    if (nullptr != temp)
      onfree(temp);
    m_count = (int)count1;
  }
}

template <class T>
void ON_SimpleArray<T>::Insert( int i, const T& x ) 
{
  if( i >= 0 && i <= m_count ) 
  {
    const T* p = &x;
    if ( m_count == m_capacity ) 
    {
      if (&x >= m_a && &x < (m_a + m_capacity))
      {
        // x is in the block of memory about to be reallocated.
        void* temp = onmalloc(sizeof(T));
        memcpy(temp, p, sizeof(T));
        p = (T*)temp;
      }
      int newcapacity = NewCapacity();
      Reserve( newcapacity );
    }
	  m_count++;
    Move( i+1, i, m_count-1-i );
	  m_a[i] = *p;
    if (p != &x)
      onfree((void*)p);
  }
}

template <class T>
void ON_SimpleArray<T>::Remove()
{
  Remove(m_count-1);
} 

template <class T>
void ON_SimpleArray<T>::Remove( int i )
{
  if ( i >= 0 && i < m_count ) {
    Move( i, i+1, m_count-1-i );
    m_count--;
    memset( (void*)(&m_a[m_count]), 0, sizeof(T) );
  }
} 

template <class T>
void ON_SimpleArray<T>::RemoveValue(const T& key)
{
  const T* p = &key;
  int t = 0;
  for (int i = 0; i < m_count; i++)
  {
    if (memcmp(p, m_a + i, sizeof(T)))
      *(m_a + t++) = *(m_a + i);
  }
  m_count = t;
}

template <class T>
void ON_SimpleArray<T>::RemoveIf(bool predicate(const T& key))
{
  int t = 0;
  for (int i = 0; i < m_count; i++)
  {
    if (!predicate(*(m_a + i)))
      *(m_a + t++) = *(m_a + i);
  }
  m_count = t;
}

template <class T>
void ON_SimpleArray<T>::Empty()
{
  if ( m_a )
    memset( (void*)(m_a), 0, m_capacity*sizeof(T) );
  m_count = 0;
}

template <class T>
void ON_SimpleArray<T>::Reverse()
{
  // NOTE:
  // If anything in "T" depends on the value of this's address,
  // then don't call Reverse().
  T t;
  int i = 0;  
  int j = m_count-1;
  for ( /*empty*/; i < j; i++, j-- ) {
    t = m_a[i];
    m_a[i] = m_a[j];
    m_a[j] = t;
  }
}

template <class T>
void ON_SimpleArray<T>::Swap( int i, int j )
{
  if ( i != j ) {
    const T t(m_a[i]);
    m_a[i] = m_a[j];
    m_a[j] = t;
  }
}

template <class T>
int ON_SimpleArray<T>::Search( const T& key ) const
{
  const T* p = &key;
  for ( int i = 0; i < m_count; i++ ) {
    if (!memcmp(p,m_a+i,sizeof(T))) 
      return i;
  }
  return -1;
}

template <class T>
int ON_SimpleArray<T>::Search( const T* key, int (*compar)(const T*,const T*) ) const
{
  for ( int i = 0; i < m_count; i++ ) {
    if (!compar(key,m_a+i)) 
      return i;
  }
  return -1;
}

template <class T>
int ON_SimpleArray<T>::BinarySearch( const T* key, int (*compar)(const T*,const T*) ) const
{
  const T* found = (nullptr != key && nullptr != m_a && m_count>0)
                 ? (const T*)bsearch( key, m_a, m_count, sizeof(T), (int(*)(const void*,const void*))compar ) 
                 : nullptr;

  // This worked on a wide range of 32 bit compilers.

  int rc;
  if ( 0 != found )
  {
    // Convert "found" pointer to array index.

#if defined(ON_COMPILER_MSC1300)
    rc = ((int)(found - m_a));
#elif 8 == ON_SIZEOF_POINTER
    // In an ideal world, return ((int)(found - m_a)) would work everywhere.
    // In practice, this should work any 64 bit compiler and we can hope
    // the optimzer generates efficient code.
    const ON__UINT64 fptr = (ON__UINT64)found;
    const ON__UINT64 aptr = (ON__UINT64)m_a;
    const ON__UINT64 sz   = (ON__UINT64)sizeof(T);
    const ON__UINT64 i    = (fptr - aptr)/sz;
    rc = (int)i;
#else
    // In an ideal world, return ((int)(found - m_a)) would work everywhere.
    // In practice, this should work any 32 bit compiler and we can hope
    // the optimzer generates efficient code.
    const ON__UINT32 fptr = (ON__UINT32)found;
    const ON__UINT32 aptr = (ON__UINT32)m_a;
    const ON__UINT32 sz   = (ON__UINT32)sizeof(T);
    const ON__UINT32 i    = (fptr - aptr)/sz;
    rc = (int)i;
#endif
  }
  else
  {
    // "key" not found
    rc = -1;
  }

  return rc;

}

template <class T>
int ON_SimpleArray<T>::BinarySearch( const T* key, int (*compar)(const T*,const T*), int count ) const
{
  if ( count > m_count )
    count = m_count;
  if ( count <= 0 )
    return -1;
  const T* found = (nullptr != key && nullptr != m_a && count > 0)
                 ? (const T*)bsearch( key, m_a, count, sizeof(T), (int(*)(const void*,const void*))compar ) 
                 : nullptr;

  // This worked on a wide range of 32 bit compilers.

  int rc;
  if ( 0 != found )
  {
    // Convert "found" pointer to array index.

#if defined(ON_COMPILER_MSC1300)
    rc = ((int)(found - m_a));
#elif 8 == ON_SIZEOF_POINTER
    // In an ideal world, return ((int)(found - m_a)) would work everywhere.
    // In practice, this should work any 64 bit compiler and we can hope
    // the optimzer generates efficient code.
    const ON__UINT64 fptr = (ON__UINT64)found;
    const ON__UINT64 aptr = (ON__UINT64)m_a;
    const ON__UINT64 sz   = (ON__UINT64)sizeof(T);
    const ON__UINT64 i    = (fptr - aptr)/sz;
    rc = (int)i;
#else
    // In an ideal world, return ((int)(found - m_a)) would work everywhere.
    // In practice, this should work any 32 bit compiler and we can hope
    // the optimzer generates efficient code.
    const ON__UINT32 fptr = (ON__UINT32)found;
    const ON__UINT32 aptr = (ON__UINT32)m_a;
    const ON__UINT32 sz   = (ON__UINT32)sizeof(T);
    const ON__UINT32 i    = (fptr - aptr)/sz;
    rc = (int)i;
#endif
  }
  else
  {
    // "key" not found
    rc = -1;
  }
  return rc;
}


template <class T>
const T* ON_SimpleArray<T>::BinarySearchPtr(const T* key, int (*compar)(const T*, const T*)) const
{
  return 
    (nullptr != key && nullptr != m_a && m_count > 0)
    ? (const T*)bsearch(key, m_a, m_count, sizeof(T), (int(*)(const void*, const void*))compar)
    : nullptr;
}

template <class T>
const T* ON_SimpleArray<T>::BinarySearchPtr(const T* key, int (*compar)(const T*, const T*), int count) const
{
  if (count > m_count)
    count = m_count;
  return 
    (nullptr != key && nullptr != m_a && count > 0)
    ? (const T*)bsearch(key, m_a, count, sizeof(T), (int(*)(const void*, const void*))compar)
    : nullptr;
}


template <class T>
int ON_SimpleArray<T>::InsertInSortedList(const T& e, int (*compar)(const T*, const T*))
{
  const int count = m_count;
  if (count < 0)
    return -1;
  if (0 == count)
  {
    Insert(0, e);
    return 0;
  }

  const unsigned ucount = ((unsigned)count);
  unsigned i0 = 0;
  unsigned i1 = ucount;
  while (i0 < i1)
  {
    const unsigned i = (i0 + i1) / 2;
    const int c = compar(&e, m_a + i);
    if (c < 0)
    {
      i1 = i;
    }
    else if (c > 0)
    {
      i0 = i + 1;
    }
    else
    {
      i1 = i;
      while (i1 + 1 < ucount && 0 == compar(&e, m_a + (i1 + 1)))
        ++i1;
      i0 = i1;
    }
  }
  if (i0 <= ucount)
  {
    Insert(i0, e);
    return ((int)i0);
  }

  return -1;
}


template <class T>
int ON_SimpleArray<T>::InsertInSortedList(const T& e, int (*compar)(const T*, const T*), int count)
{
  if (count > m_count)
    count = m_count;
  if (count < 0)
    return -1;
  if (0 == count)
  {
    Insert(0, e);
    return 0;
  }

  const unsigned ucount = ((unsigned)count);
  unsigned i0 = 0;
  unsigned i1 = ucount;
  while (i0<i1)
  {
    const unsigned i = (i0 + i1) / 2;
    const int c = compar(&e, m_a + i);
    if (c < 0)
    {
      i1 = i;
    }
    else if (c > 0)
    {
      i0 = i + 1;
    }
    else
    {
      i1 = i;
      while (i1 + 1 < ucount && 0 == compar(&e, m_a + (i1 + 1)))
        ++i1;
      i0 = i1;
    }
  }
  if (i0 <= ucount)
  {
    Insert(i0, e);
    return ((int)i0);
  }

  return -1;
}

template <class T>
bool ON_SimpleArray<T>::HeapSort( int (*compar)(const T*,const T*) )
{
  bool rc = false;
  if ( m_a && m_count > 0 && compar ) {
    if ( m_count > 1 )
      ON_hsort( m_a, m_count, sizeof(T), (int(*)(const void*,const void*))compar );
    rc = true;
  }
  return rc;
}

template <class T>
bool ON_SimpleArray<T>::QuickSort( int (*compar)(const T*,const T*) )
{
  bool rc = false;
  if ( m_a && m_count > 0 && compar ) {
    if ( m_count > 1 )
      ON_qsort( m_a, m_count, sizeof(T), (int(*)(const void*,const void*))compar );
    rc = true;
  }
  return rc;
}

template <class T>
bool ON_SimpleArray<T>::QuickSortAndRemoveDuplicates( int (*compar)(const T*,const T*) )
{
  bool rc = false;
  if ( m_a && m_count > 0 && compar )
  {
    if (m_count > 1)
    {
      ON_qsort(m_a, m_count, sizeof(T), (int(*)(const void*, const void*))compar);
      const T* prev_ele = &m_a[0];
      int clean_count = 1;
      for (int i = 1; i < m_count; ++i)
      {
        if (0 == compar(prev_ele, &m_a[i]))
          continue; // duplicate
        if (i > clean_count)
          m_a[clean_count] = m_a[i];
        prev_ele = &m_a[clean_count];
        ++clean_count;
      }
      if (clean_count < m_count)
      {
        memset( (void*)(&m_a[clean_count]), 0, (m_count-clean_count)*sizeof(T) );
        SetCount(clean_count);
      }
    }
    rc = true;
  }
  return rc;
}

template <class T>
bool ON_SimpleArray<T>::Sort( ON::sort_algorithm sa, int* index, int (*compar)(const T*,const T*) ) const
{
  bool rc = false;
  if ( m_a && m_count > 0 && compar && index ) {
    if ( m_count > 1 )
      ON_Sort(sa, index, m_a, m_count, sizeof(T), (int(*)(const void*,const void*))compar );
    else if ( m_count == 1 )
      index[0] = 0;
    rc = true;
  }
  return rc;
}

template <class T>
bool ON_SimpleArray<T>::Sort( ON::sort_algorithm sa, int* index, int (*compar)(const T*,const T*,void*),void* p ) const
{
  bool rc = false;
  if ( m_a && m_count > 0 && compar && index ) {
    if ( m_count > 1 )
      ON_Sort(sa, index, m_a, m_count, sizeof(T), (int(*)(const void*,const void*,void*))compar, p );
    else if ( m_count == 1 )
      index[0] = 0;
    rc = true;
  }
  return rc;
}

template <class T>
bool ON_SimpleArray<T>::Permute( const int* index )
{
  bool rc = false;
  if ( m_a && m_count > 0 && index ) {
    int i;
    T* buffer = (T*)onmalloc(m_count*sizeof(buffer[0]));
    memcpy( (void*)(buffer), (void*)(m_a), m_count*sizeof(T) );
    for (i = 0; i < m_count; i++ )
      memcpy( (void*)(m_a+i), (void*)(buffer+index[i]), sizeof(T) ); // must use memcopy and not operator=
    onfree(buffer);
    rc = true;
  }
  return rc;
}

template <class T>
void ON_SimpleArray<T>::Zero()
{
  if ( m_a && m_capacity > 0 ) {
    memset( (void*)(m_a), 0, m_capacity*sizeof(T) );
  }
}

template <class T>
void ON_SimpleArray<T>::MemSet( unsigned char value )
{
  if ( m_a && m_capacity > 0 ) {
    memset( (void*)(m_a), value, m_capacity*sizeof(T) );
  }
}

template <class T>
void ON_SimpleArray<T>::SetRange(int from, int count, T value)
{
  if (m_a && ((from + count) <= m_capacity))
  {
    for (int i = 0; i < count; i++)
      m_a[from + i] = value;
  }
}

// memory management ////////////////////////////////////////////////////

template <class T>
T* ON_SimpleArray<T>::Reserve( size_t newcap ) 
{
  if( (size_t)m_capacity < newcap )
    SetCapacity( newcap );
  return m_a;
}

template <class T>
void ON_SimpleArray<T>::Shrink()
{
  SetCapacity( m_count );
}

template <class T>
void ON_SimpleArray<T>::Destroy()
{
  SetCapacity( 0 );
}

// low level memory management //////////////////////////////////////////

template <class T>
void ON_SimpleArray<T>::SetCount( int count ) 
{
  if ( count >= 0 && count <= m_capacity )
    m_count = count;
}

template <class T>
T* ON_SimpleArray<T>::SetCapacity( size_t new_capacity ) 
{
  if (0 == m_capacity)
  {
    // Allow "expert" users of ON_SimpleArray<>.SetArray(*,*,0) to clean up after themselves
    // and deals with the case when the forget to clean up after themselves.
    m_a = nullptr;
    m_count = 0;
  }

  // sets capacity to input value
  int capacity = (new_capacity > 0 && new_capacity < ON_UNSET_UINT_INDEX) 
               ? (int)new_capacity 
               : 0;
  if ( capacity != m_capacity ) {
    if( capacity > 0 ) {
      if ( m_count > capacity )
        m_count = capacity;
      // NOTE: Realloc() does an allocation if the first argument is nullptr.
      m_a = Realloc( m_a, capacity );
      if ( m_a ) {
        if ( capacity > m_capacity ) {
          // zero new memory
          memset( (void*) (m_a + m_capacity), 0, (capacity-m_capacity)*sizeof(T) );
        }
        m_capacity = capacity;
      }
      else {
        // out of memory
        m_count = m_capacity = 0;
      }
    }
    else if (m_a) {
      Realloc(m_a,0);
      m_a = 0;
      m_count = m_capacity = 0;
    }
  }
  return m_a;
}

template <class T>
int ON_SimpleArray<T>::NewCapacity() const
{
  // Note: 
  //   This code appears in ON_SimpleArray<T>::NewCapacity()
  //   and ON_ClassArray<T>::NewCapacity().  Changes made to
  //   either function should be made to both functions.
  //   Because this code is template code that has to
  //   support dynamic linking and the code is defined
  //   in a header, I'm using copy-and-paste rather
  //   than a static.

  // This function returns 2*m_count unless that will
  // result in an additional allocation of more than
  // cap_size bytes.  The cap_size concept was added in
  // January 2010 because some calculations on enormous
  // models were slightly underestimating the initial
  // Reserve() size and then wasting gigabytes of memory.

  // cap_size = 128 MB on 32-bit os, 256 MB on 64 bit os
  const size_t cap_size = 32*sizeof(void*)*1024*1024;
  if (m_count*sizeof(T) <= cap_size || m_count < 8)
    return ((m_count <= 2) ? 4 : 2*m_count);

  // Growing the array will increase the memory
  // use by more than cap_size.
  int delta_count = 8 + cap_size/sizeof(T);
  if ( delta_count > m_count )
    delta_count = m_count;
  return (m_count + delta_count);
}

template <class T>
int ON_ClassArray<T>::NewCapacity() const
{
  // Note: 
  //   This code appears in ON_SimpleArray<T>::NewCapacity()
  //   and ON_ClassArray<T>::NewCapacity().  Changes made to
  //   either function should be made to both functions.
  //   Because this code is template code that has to
  //   support dynamic linking and the code is defined
  //   in a header, I'm using copy-and-paste rather
  //   than a static.

  // This function returns 2*m_count unless that will
  // result in an additional allocation of more than
  // cap_size bytes.  The cap_size concept was added in
  // January 2010 because some calculations on enormous
  // models were slightly underestimating the initial
  // Reserve() size and then wasting gigabytes of memory.

  // cap_size = 128 MB on 32-bit os, 256 MB on 64 bit os
  const size_t cap_size = 32*sizeof(void*)*1024*1024;
  if (m_count*sizeof(T) <= cap_size || m_count < 8)
    return ((m_count <= 2) ? 4 : 2*m_count);

  // Growing the array will increase the memory
  // use by more than cap_size.
  int delta_count = 8 + cap_size/sizeof(T);
  if ( delta_count > m_count )
    delta_count = m_count;
  return (m_count + delta_count);
}

/////////////////////////////////////////////////////////////////////////////////////
//  Class ON_ObjectArray<>
/////////////////////////////////////////////////////////////////////////////////////

template <class T>
ON_ObjectArray<T>::ON_ObjectArray()
{
}

template <class T>
ON_ObjectArray<T>::~ON_ObjectArray()
{
}

template <class T>
ON_ObjectArray<T>::ON_ObjectArray( const ON_ObjectArray<T>& src ) : ON_ClassArray<T>(src)
{
}

template <class T>
ON_ObjectArray<T>& ON_ObjectArray<T>::operator=( const ON_ObjectArray<T>& src)
{
  if( this != &src)
  {
    ON_ClassArray<T>::operator =(src);
  }
  return *this;
}

#if defined(ON_HAS_RVALUEREF)

// Clone constructor
template <class T>
ON_ObjectArray<T>::ON_ObjectArray( ON_ObjectArray<T>&& src )
  : ON_ClassArray<T>(std::move(src))
{}

// Clone assignment
template <class T>
ON_ObjectArray<T>& ON_ObjectArray<T>::operator=( ON_ObjectArray<T>&& src )
{
  if( this != &src ) 
  {
    ON_ClassArray<T>::operator=(std::move(src));
  }  
  return *this;
}

#endif

template <class T>
ON_ObjectArray<T>::ON_ObjectArray( size_t c )
  : ON_ClassArray<T>(c)
{
}

template <class T>
T* ON_ObjectArray<T>::Realloc(T* ptr,int capacity)
{
  T* reptr = (T*)onrealloc(ptr,capacity*sizeof(T));
  if ( ptr && reptr && reptr != ptr )
  {
    // The "this->" in this->m_count and this->m_a 
    // are needed for gcc 4 to compile.
    int i;
    for ( i = 0; i < this->m_count; i++ )
    {
      reptr[i].MemoryRelocate();
    }
  }
  return reptr;
}

/////////////////////////////////////////////////////////////////////////////////////
//  Class ON_ClassArray<>
/////////////////////////////////////////////////////////////////////////////////////


// construction ////////////////////////////////////////////////////////

template <class T>
T* ON_ClassArray<T>::Realloc(T* ptr,int capacity)
{
  return (T*)onrealloc(ptr,capacity*sizeof(T));
}

template <class T>
ON__UINT32 ON_ObjectArray<T>::DataCRC(ON__UINT32 current_remainder) const
{
  // The "this->" in this->m_count and this->m_a 
  // are needed for gcc 4 to compile.
  int i;
  for ( i = 0; i < this->m_count; i++ )
  {
    current_remainder = this->m_a[i].DataCRC(current_remainder);
  }
  return current_remainder;
}

template <class T>
ON_ClassArray<T>::ON_ClassArray() ON_NOEXCEPT
  : m_a(nullptr)
  , m_count(0)
  , m_capacity(0)                            
{}

template <class T>
ON_ClassArray<T>::ON_ClassArray( size_t c )
  : m_a(nullptr)
  , m_count(0)
  , m_capacity(0)                            
{
  if ( c > 0 ) 
    SetCapacity( c );
}

// Copy constructor
template <class T>
ON_ClassArray<T>::ON_ClassArray( const ON_ClassArray<T>& src )
  : m_a(nullptr)
  , m_count(0)
  , m_capacity(0)                            
{
  *this = src; // operator= defined below
}

template <class T>
ON_ClassArray<T>::~ON_ClassArray()
{ 
  SetCapacity(0);
}

template <class T>
ON_ClassArray<T>& ON_ClassArray<T>::operator=( const ON_ClassArray<T>& src )
{
  int i;
  if( this != &src ) {
    if ( src.m_count <= 0 ) {
      m_count = 0;
    }
    else {
      if ( m_capacity < src.m_count ) {
        SetCapacity( src.m_count );
      }
      if ( m_a ) {
        m_count = src.m_count;
        for ( i = 0; i < m_count; i++ ) {
          m_a[i] = src.m_a[i];
        }
      }
    }
  }  
  return *this;
}

#if defined(ON_HAS_RVALUEREF)

// Clone constructor
template <class T>
ON_ClassArray<T>::ON_ClassArray( ON_ClassArray<T>&& src ) ON_NOEXCEPT
  : m_a(src.m_a)
  , m_count(src.m_count)
  , m_capacity(src.m_capacity)
{
  src.m_a = 0;
  src.m_count = 0;
  src.m_capacity = 0;
}

// Clone assignment
template <class T>
ON_ClassArray<T>& ON_ClassArray<T>::operator=( ON_ClassArray<T>&& src ) ON_NOEXCEPT
{
  if( this != &src ) 
  {
    // TODO - investigate why we should use std::move(src)
    // instead of the code below
    //ON_ClassArray<T>::operator=(std::move(src));
    // Then investigate why the change was requested only for class array.
    // What about the other dynamic array classes?
    this->Destroy();
    m_a = src.m_a;
    m_count = src.m_count;
    m_capacity = src.m_capacity;
    src.m_a = 0;
    src.m_count = 0;
    src.m_capacity = 0;
  }  
  return *this;
}

#endif

// emergency destroy ///////////////////////////////////////////////////

template <class T>
void ON_ClassArray<T>::EmergencyDestroy(void)
{
  m_count = 0;
  m_capacity = 0;
  m_a = 0;
}

// query ///////////////////////////////////////////////////////////////

template <class T>
int ON_ClassArray<T>::Count() const
{
  return m_count;
}

template <class T>
unsigned int ON_ClassArray<T>::UnsignedCount() const
{
  return ((unsigned int)m_count);
}

template <class T>
int ON_ClassArray<T>::Capacity() const
{
  return m_capacity;
}

template <class T>
unsigned int ON_ClassArray<T>::SizeOfArray() const
{
  return ((unsigned int)(m_capacity*sizeof(T)));
}

template <class T>
unsigned int ON_ClassArray<T>::SizeOfElement() const
{
  return ((unsigned int)(sizeof(T)));
}

template <class T>
T& ON_ClassArray<T>::operator[]( int i )
{ 
#if defined(ON_DEBUG)
  if ( i < 0 || i > m_capacity )
  {
    ON_ERROR("ON_ClassArray[i]: i out of range.");
  }
#endif
  return m_a[i]; 
}


template <class T>
T& ON_ClassArray<T>::operator[]( ON__INT64 i )
{ 
#if defined(ON_DEBUG)
  if ( i < 0 || i > (ON__INT64)m_capacity )
  {
    ON_ERROR("ON_ClassArray[i]: i out of range.");
  }
#endif
  return m_a[i]; 
}

template <class T>
T& ON_ClassArray<T>::operator[]( unsigned int i )
{ 
#if defined(ON_DEBUG)
  if ( i > (unsigned int)m_capacity )
  {
    ON_ERROR("ON_ClassArray[i]: i out of range.");
  }
#endif
  return m_a[i]; 
}

template <class T>
T& ON_ClassArray<T>::operator[]( ON__UINT64 i )
{ 
#if defined(ON_DEBUG)
  if ( i > (ON__UINT64)m_capacity )
  {
    ON_ERROR("ON_ClassArray[i]: i out of range.");
  }
#endif
  return m_a[i]; 
}

#if defined(ON_RUNTIME_APPLE)
template <class T>
T& ON_ClassArray<T>::operator[](size_t i )
{ 
#if defined(ON_DEBUG)
  if ( i > (size_t)m_capacity )
  {
    ON_ERROR("ON_ClassArray[i]: i out of range.");
  }
#endif
  return m_a[i]; 
}
#endif

template <class T>
const T& ON_ClassArray<T>::operator[](int i) const
{
#if defined(ON_DEBUG)
  if ( i < 0 || i > m_capacity )
  {
    ON_ERROR("ON_ClassArray[i]: i out of range.");
  }
#endif
  return m_a[i];
}

template <class T>
const T& ON_ClassArray<T>::operator[](ON__INT64 i) const
{
#if defined(ON_DEBUG)
  if ( i < 0 || i > (ON__INT64)m_capacity )
  {
    ON_ERROR("ON_ClassArray[i]: i out of range.");
  }
#endif
  return m_a[i];
}

template <class T>
const T& ON_ClassArray<T>::operator[](unsigned int i) const
{
#if defined(ON_DEBUG)
  if ( i > (unsigned int)m_capacity )
  {
    ON_ERROR("ON_ClassArray[i]: i out of range.");
  }
#endif
  return m_a[i];
}

template <class T>
const T& ON_ClassArray<T>::operator[](ON__UINT64 i) const
{
#if defined(ON_DEBUG)
  if ( i > (ON__UINT64)m_capacity )
  {
    ON_ERROR("ON_ClassArray[i]: i out of range.");
  }
#endif
  return m_a[i];
}

#if defined(ON_RUNTIME_APPLE)
template <class T>
const T& ON_ClassArray<T>::operator[](size_t i) const
{
#if defined(ON_DEBUG)
  if ( i > (size_t)m_capacity )
  {
    ON_ERROR("ON_ClassArray[i]: i out of range.");
  }
#endif
  return m_a[i];
}
#endif

template <class T>
ON_ClassArray<T>::operator T*()
{
  return (m_count > 0) ? m_a : 0;
}

template <class T>
ON_ClassArray<T>::operator const T*() const
{
  return (m_count > 0) ? m_a : 0;
}

template <class T>
T* ON_ClassArray<T>::Array()
{
  return m_a;
}

template <class T>
const T* ON_ClassArray<T>::Array() const
{
  return m_a;
}

template <class T>
T* ON_ClassArray<T>::KeepArray()
{
  T* p = m_a;
  m_a = 0;
  m_count = 0;
  m_capacity = 0;
  return p;
}

template <class T>
void ON_ClassArray<T>::SetArray(T* p)
{
  if ( m_a && m_a != p )
    Destroy();
  m_a = p;
}

template <class T>
void ON_ClassArray<T>::SetArray(T* p, int count, int capacity)
{
  if ( m_a && m_a != p )
    Destroy();
  m_a = p;
  m_count = count;
  m_capacity = capacity;
}

template <class T>
T* ON_ClassArray<T>::First()
{ 
  return (m_count > 0) ? m_a : 0;
}

template <class T>
const T* ON_ClassArray<T>::First() const
{
  return (m_count > 0) ? m_a : 0;
}

template <class T>
T* ON_ClassArray<T>::At( int i )
{ 
  return (i >= 0 && i < m_count) ? m_a+i : 0;
}

template <class T>
T* ON_ClassArray<T>::At( unsigned int i )
{ 
  return (i < (unsigned int)m_count) ? m_a+i : 0;
}

template <class T>
const T* ON_ClassArray<T>::At( int i) const
{
  return (i >= 0 && i < m_count) ? m_a+i : 0;
}

template <class T>
const T* ON_ClassArray<T>::At( unsigned int i) const
{
  return (i < (unsigned int)m_count) ? m_a+i : 0;
}


template <class T>
T* ON_ClassArray<T>::At( ON__INT64 i )
{ 
  return (i >= 0 && i < (ON__INT64)m_count) ? m_a+i : 0;
}

template <class T>
T* ON_ClassArray<T>::At( ON__UINT64 i )
{ 
  return (i < (ON__UINT64)m_count) ? m_a+i : 0;
}

template <class T>
const T* ON_ClassArray<T>::At( ON__INT64 i) const
{
  return (i >= 0 && i < (ON__INT64)m_count) ? m_a+i : 0;
}

template <class T>
const T* ON_ClassArray<T>::At( ON__UINT64 i) const
{
  return (i < (ON__UINT64)m_count) ? m_a+i : 0;
}


template <class T>
T* ON_ClassArray<T>::Last()
{ 
  return (m_count > 0) ? m_a+(m_count-1) : 0;
}

template <class T>
const T* ON_ClassArray<T>::Last() const
{
  return (m_count > 0) ? m_a+(m_count-1) : 0;
}

// array operations ////////////////////////////////////////////////////

template <class T>
void ON_ClassArray<T>::Move( int dest_i, int src_i, int ele_cnt )
{
  // private function for moving blocks of array memory
  // caller is responsible for updating m_count and managing
  // destruction/creation.
  if ( ele_cnt <= 0 || src_i < 0 || dest_i < 0 || src_i == dest_i || 
       src_i + ele_cnt > m_count || dest_i > m_count )
    return;

  int capacity = dest_i + ele_cnt;
  if ( capacity > m_capacity ) {
    if ( capacity < 2*m_capacity )
      capacity = 2*m_capacity;
    SetCapacity( capacity );
  }

  // This call to memmove is ok, even when T is a class with a vtable
  // because the it doesn't change the vtable for the class.
  // Classes that have back pointers, like ON_UserData, are
  // handled elsewhere and cannot be in ON_ClassArray<>s.
  memmove( (void*)(&m_a[dest_i]), (const void*)(&m_a[src_i]), ele_cnt*sizeof(T) );
}

template <class T>
void ON_ClassArray<T>::ConstructDefaultElement(T* p)
{
  // use placement ( new(size_t,void*) ) to construct
  // T in supplied memory
  new(p) T;
}

template <class T>
void ON_ClassArray<T>::DestroyElement(T& x)
{
  x.~T();
}

template <class T>
T& ON_ClassArray<T>::AppendNew()
{
  if ( m_count == m_capacity ) 
  {
    int newcapacity = NewCapacity();
    Reserve( newcapacity );
  }
  else
  {
    // First destroy what's there ..
    DestroyElement(m_a[m_count]);
    // and then get a properly initialized element
    ConstructDefaultElement(&m_a[m_count]);
  }
  return m_a[m_count++];
}

template <class T>
void ON_ClassArray<T>::Append( const T& x ) 
{
  if ( m_count == m_capacity ) 
  {
    const int newcapacity = NewCapacity();
    if (m_a)
    {
      const int s = (int)(&x - m_a); // (int) cast is for 64 bit pointers
      if ( s >= 0 && s < m_capacity )
      {
        // 26 Sep 2005 Dale Lear
        //    User passed in an element of the m_a[]
        //    that will get reallocated by the call
        //    to Reserve(newcapacity).
        T temp;   // ON_*Array<> templates do not require robust copy constructor.
        temp = x; // ON_*Array<> templates require a robust operator=.
        Reserve( newcapacity );
        if (nullptr == m_a)
        {
          ON_ERROR("allocation failure");
          return;
        }
        m_a[m_count++] = temp;
        return;
      }
    }
    Reserve(newcapacity);
    if (nullptr == m_a)
    {
      ON_ERROR("allocation failure");
      return;
    }
  }
  m_a[m_count++] = x;
}

template <class T>
void ON_ClassArray<T>::Append( int count, const T* p ) 
{
  int i;
  if ( count > 0 && p ) 
  {
    if ( count + m_count > m_capacity ) 
    {
      int newcapacity = NewCapacity();
      if ( newcapacity < count + m_count )
        newcapacity = count + m_count;
      Reserve( newcapacity );
    }
    for ( i = 0; i < count; i++ ) {
      m_a[m_count++] = p[i];
    }
  }
}

// Insert called with a reference uses operator =
template <class T>
void ON_ClassArray<T>::Insert( int i, const T& x ) 
{
  if( i >= 0 && i <= m_count ) 
  {
    if ( m_count == m_capacity ) 
    {
      int newcapacity = NewCapacity();
      Reserve( newcapacity );
    }
    DestroyElement( m_a[m_count] );
	  m_count++;
    if ( i < m_count-1 ) {
      Move( i+1, i, m_count-1-i );
      // This call to memset is ok even when T has a vtable
      // because in-place construction is used later.
      memset( (void*)(&m_a[i]), 0, sizeof(T) );
      ConstructDefaultElement( &m_a[i] );
    }
    else {
      ConstructDefaultElement( &m_a[m_count-1] );
    }
	  m_a[i] = x; // uses T::operator=() to copy x to array
  }
}

template <class T>
void ON_ClassArray<T>::Remove( )
{
  Remove(m_count-1);
} 

template <class T>
void ON_ClassArray<T>::Remove( int i )
{
  if ( i >= 0 && i < m_count ) 
  {
    DestroyElement( m_a[i] );
    // This call to memset is ok even when T has a vtable
    // because in-place construction is used later.
    memset( (void*)(&m_a[i]), 0, sizeof(T) );
    Move( i, i+1, m_count-1-i );
    // This call to memset is ok even when T has a vtable
    // because in-place construction is used later.
    memset( (void*)(&m_a[m_count-1]), 0, sizeof(T) );
    ConstructDefaultElement(&m_a[m_count-1]);
    m_count--;
  }
} 

template <class T>
void ON_ClassArray<T>::Empty()
{
  int i;
  for ( i = m_count-1; i >= 0; i-- ) {
    DestroyElement( m_a[i] );
    // This call to memset is ok even when T has a vtable
    // because in-place construction is used later.
    memset( (void*)(&m_a[i]), 0, sizeof(T) );
    ConstructDefaultElement( &m_a[i] );
  }
  m_count = 0;
}

template <class T>
void ON_ClassArray<T>::Reverse()
{
  // NOTE:
  // If anything in "T" depends on the value of this's address,
  // then don't call Reverse().
  char t[sizeof(T)];
  int i = 0;  
  int j = m_count-1;
  for ( /*empty*/; i < j; i++, j-- ) {
    memcpy( (void*)(t), (void*)(&m_a[i]), sizeof(T) );
    memcpy( (void*)(&m_a[i]), (void*)(&m_a[j]), sizeof(T) );
    memcpy( (void*)(&m_a[j]), (void*)(t), sizeof(T) );
  }
}

template <class T>
void ON_ClassArray<T>::Swap( int i, int j )
{
  if ( i != j && i >= 0 && j >= 0 && i < m_count && j < m_count ) {
    char t[sizeof(T)];
    memcpy( (void*)(t),       (void*)(&m_a[i]), sizeof(T) );
    memcpy( (void*)(&m_a[i]), (void*)(&m_a[j]), sizeof(T) );
    memcpy( (void*)(&m_a[j]), (void*)(t),       sizeof(T) );
  }
}

template <class T>
int ON_ClassArray<T>::Search( const T* key, int (*compar)(const T*,const T*) ) const
{
  for ( int i = 0; i < m_count; i++ ) 
  {
    if (!compar(key,m_a+i)) 
      return i;
  }
  return -1;
}

template <class T>
int ON_ClassArray<T>::BinarySearch( const T* key, int (*compar)(const T*,const T*) ) const
{
  const T* found = (key&&m_a&&m_count>0) ? (const T*)bsearch( key, m_a, m_count, sizeof(T), (int(*)(const void*,const void*))compar ) : nullptr;
  return (nullptr != found && found >= m_a) ? ((int)(found - m_a)) : -1;
}

template <class T>
int ON_ClassArray<T>::BinarySearch( const T* key, int (*compar)(const T*,const T*), int count ) const
{
  if ( count > m_count )
    count = m_count;
  if ( count <= 0 )
    return -1;
  const T* found = (key&&m_a&&m_count>0) ? (const T*)bsearch( key, m_a, count, sizeof(T), (int(*)(const void*,const void*))compar ) : nullptr;
  return (nullptr != found && found >= m_a) ? ((int)(found - m_a)) : -1;
}


template <class T>
int ON_ClassArray<T>::InsertInSortedList(const T& e, int (*compar)(const T*, const T*))
{
  const int count = m_count;
  if (count < 0)
    return -1;
  if (0 == count)
  {
    Insert(0, e);
    return 0;
  }

  const unsigned ucount = ((unsigned)count);
  unsigned i0 = 0;
  unsigned i1 = ucount;
  while (i0 < i1)
  {
    const unsigned i = (i0 + i1) / 2;
    const int c = compar(&e, m_a + i);
    if (c < 0)
    {
      i1 = i;
    }
    else if (c > 0)
    {
      i0 = i + 1;
    }
    else
    {
      i1 = i;
      while (i1 + 1 < ucount && 0 == compar(&e, m_a + (i1 + 1)))
        ++i1;
      i0 = i1;
    }
  }
  if (i0 <= ucount)
  {
    Insert(i0, e);
    return ((int)i0);
  }

  return -1;
}


template <class T>
int ON_ClassArray<T>::InsertInSortedList(const T& e, int (*compar)(const T*, const T*), int count)
{
  if (count > m_count)
    count = m_count;
  if (count < 0)
    return -1;
  if (0 == count)
  {
    Insert(0, e);
    return 0;
  }

  const unsigned ucount = ((unsigned)count);
  unsigned i0 = 0;
  unsigned i1 = ucount;
  while (i0 < i1)
  {
    const unsigned i = (i0 + i1) / 2;
    const int c = compar(&e, m_a + i);
    if (c < 0)
    {
      i1 = i;
    }
    else if (c > 0)
    {
      i0 = i + 1;
    }
    else
    {
      i1 = i;
      while (i1 + 1 < ucount && 0 == compar(&e, m_a + (i1 + 1)))
        ++i1;
      i0 = i1;
    }
  }
  if (i0 <= ucount)
  {
    Insert(i0, e);
    return ((int)i0);
  }

  return -1;
}


template <class T>
bool ON_ClassArray<T>::HeapSort( int (*compar)(const T*,const T*) )
{
  bool rc = false;
  if ( m_a && m_count > 0 && compar ) 
  {
    if ( m_count > 1 )
      ON_hsort( m_a, m_count, sizeof(T), (int(*)(const void*,const void*))compar );
    rc = true;
  }
  return rc;
}

template <class T>
bool ON_ClassArray<T>::QuickSort( int (*compar)(const T*,const T*) )
{
  bool rc = false;
  if ( m_a && m_count > 0 && compar ) 
  {
    if ( m_count > 1 )
      ON_qsort( m_a, m_count, sizeof(T), (int(*)(const void*,const void*))compar );
    rc = true;
  }
  return rc;
}



template <class T>
bool ON_ObjectArray<T>::HeapSort( int (*compar)(const T*,const T*) )
{
  bool rc = false;
  // The "this->" in this->m_count and this->m_a 
  // are needed for gcc 4 to compile.
  if ( this->m_a && this->m_count > 0 && compar ) 
  {
    if ( this->m_count > 1 )
    {
      ON_hsort( this->m_a, this->m_count, sizeof(T), (int(*)(const void*,const void*))compar );
      
      // The MemoryRelocate step is required to synch userdata back pointers
      // so the user data destructor will work correctly.
      int i;
      for ( i = 0; i < this->m_count; i++ )
      {
        this->m_a[i].MemoryRelocate();
      }
    }
    rc = true;
  }
  return rc;
}

template <class T>
bool ON_ObjectArray<T>::QuickSort( int (*compar)(const T*,const T*) )
{
  bool rc = false;
  // The "this->" in this->m_count and this->m_a 
  // are needed for gcc 4 to compile.
  if ( this->m_a && this->m_count > 0 && compar ) 
  {
    if ( this->m_count > 1 )
    {
      ON_qsort( this->m_a, this->m_count, sizeof(T), (int(*)(const void*,const void*))compar );

      // The MemoryRelocate step is required to synch userdata back pointers
      // so the user data destructor will work correctly.
      int i;
      for ( i = 0; i < this->m_count; i++ )
      {
        this->m_a[i].MemoryRelocate();
      }
    }
    rc = true;
  }
  return rc;
}


template <class T>
bool ON_ClassArray<T>::Sort( ON::sort_algorithm sa, int* index, int (*compar)(const T*,const T*) ) const
{
  bool rc = false;
  if ( m_a && m_count > 0 && compar && index )
  {
    if ( m_count > 1 )
      ON_Sort(sa, index, m_a, m_count, sizeof(T), (int(*)(const void*,const void*))compar );
    else if ( m_count == 1 )
      index[0] = 0;
    rc = true;
  }
  return rc;
}

template <class T>
bool ON_ClassArray<T>::Sort( ON::sort_algorithm sa, int* index, int (*compar)(const T*,const T*,void*),void* p ) const
{
  bool rc = false;
  if ( m_a && m_count > 0 && compar && index ) 
  {
    if ( m_count > 1 )
      ON_Sort(sa, index, m_a, m_count, sizeof(T), (int(*)(const void*,const void*,void*))compar, p );
    else if ( m_count == 1 )
      index[0] = 0;
    rc = true;
  }
  return rc;
}

template <class T>
bool ON_ClassArray<T>::Permute( const int* index )
{
  bool rc = false;
  if ( m_a && m_count > 0 && index ) 
  {
    int i;
    T* buffer = (T*)onmalloc(m_count*sizeof(buffer[0]));
    memcpy( (void*)(buffer), (void*)(m_a), m_count*sizeof(T) );
    for (i = 0; i < m_count; i++ )
      memcpy( (void*)(m_a+i), (void*)(buffer+index[i]), sizeof(T) ); // must use memcopy and not operator=
    onfree(buffer);
    rc = true;
  }
  return rc;
}

template <class T>
void ON_ClassArray<T>::Zero()
{
  int i;
  if ( m_a && m_capacity > 0 ) {
    for ( i = m_capacity-1; i >= 0; i-- ) {
      DestroyElement(m_a[i]);
      // This call to memset is ok even when T has a vtable
      // because in-place construction is used later.
      memset( (void*)(&m_a[i]), 0, sizeof(T) );
      ConstructDefaultElement(&m_a[i]);
    }
  }
}

// memory management ////////////////////////////////////////////////////

template <class T>
T* ON_ClassArray<T>::Reserve( size_t newcap ) 
{
  if( (size_t)m_capacity < newcap )
    SetCapacity( newcap );
  return m_a;
}

template <class T>
void ON_ClassArray<T>::Shrink()
{
  SetCapacity( m_count );
}

template <class T>
void ON_ClassArray<T>::Destroy()
{
  SetCapacity( 0 );
}

// low level memory management //////////////////////////////////////////

template <class T>
void ON_ClassArray<T>::SetCount( int count ) 
{
  if ( count >= 0 && count <= m_capacity )
    m_count = count;
}

template <class T>
T* ON_ClassArray<T>::SetCapacity( size_t new_capacity ) 
{
  if (0 == m_capacity)
  {
    // Allow "expert" users of ON_SimpleArray<>.SetArray(*,*,0) to clean up after themselves
    // and deals with the case when the forget to clean up after themselves.
    m_a = nullptr;
    m_count = 0;
  }
  // uses "placement" for class construction/destruction
  int i;
  int capacity = (new_capacity > 0 && new_capacity < ON_UNSET_UINT_INDEX)
               ? (int)new_capacity 
               : 0;

  if ( capacity <= 0 ) {
    if ( m_a ) {
      for ( i = m_capacity-1; i >= 0; i-- ) {
        DestroyElement(m_a[i]);
      }
      Realloc(m_a,0);
      m_a = 0;
    }
    m_count = 0;
    m_capacity = 0;
  }
  else if ( m_capacity < capacity ) {
    // growing
    m_a = Realloc( m_a, capacity );
    // initialize new elements with default constructor
    if ( 0 != m_a )
    {
      // even when m_a is an array of classes with vtable pointers,
      // this call to memset(..., 0, ...) is what I want to do
      // because in-place construction will be used when needed
      // on this memory.
      memset( (void*)(m_a + m_capacity), 0, (capacity-m_capacity)*sizeof(T) );
      for ( i = m_capacity; i < capacity; i++ ) {
        ConstructDefaultElement(&m_a[i]);
      }
      m_capacity = capacity;
    }
    else
    {
      // memory allocation failed
      m_capacity = 0;
      m_count = 0;
    }
  }
  else if ( m_capacity > capacity ) {
    // shrinking
    for ( i = m_capacity-1; i >= capacity; i-- ) {
      DestroyElement(m_a[i]);
    }
    if ( m_count > capacity )
      m_count = capacity;
    m_capacity = capacity;
    m_a = Realloc( m_a, capacity );
    if ( 0 == m_a )
    {
      // memory allocation failed
      m_capacity = 0;
      m_count = 0;
    }
  }
  return m_a;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

template< class T>
int ON_CompareIncreasing( const T* a, const T* b)
{
	if( *a < *b ) 
    return -1;
	if( *b < *a ) 
    return  1;
	return 0;
}

template< class T>
int ON_CompareDecreasing( const T* a, const T* b)
{
	if( *b < *a ) 
    return -1;
	if( *a < *b ) 
    return  1;
	return 0;
}

#pragma ON_PRAGMA_WARNING_POP

#endif
