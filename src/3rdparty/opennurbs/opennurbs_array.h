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

#if !defined(ON_ARRAY_INC_)
#define ON_ARRAY_INC_


////////////////////////////////////////////////////////////////
//
// The ON_SimpleArray<> template is more efficient than the
// ON_ClassArray<> template, but ON_SimpleArray<> should not
// be used for arrays of classes that require explicit
// construction, destruction, or copy operators.
//
// Elements returned by AppendNew() are memset to zero.
//
// By default, ON_SimpleArray<> uses onrealloc() to manage
// the dynamic array memory. If you want to use something 
// besides onrealloc() to manage the array memory, then override
// ON_SimpleArray::Realloc().

template <class T> class ON_SimpleArray
{
public:
  // construction ////////////////////////////////////////////////////////

  // These constructors create an array that uses onrealloc() to manage
  // the array memory.
  ON_SimpleArray() ON_NOEXCEPT;

  virtual
  ~ON_SimpleArray();

  // Copy constructor
  ON_SimpleArray( const ON_SimpleArray<T>& );

  ////// Assignment operator
  //////   Making a virtual operator= was a mistake.
  //////   One reason might have been that the operator is virtual
  //////   so ON_UuidList::operator= will be called when one is
  //////   passed as an ON_SimpleArray<ON_UUID>& to a function?
  ////virtual
  ON_SimpleArray<T>& operator=( const ON_SimpleArray<T>& );

#if defined(ON_HAS_RVALUEREF)
  // Clone constructor
  ON_SimpleArray( ON_SimpleArray<T>&& ) ON_NOEXCEPT;

  // Clone assignment
  ON_SimpleArray<T>& operator=( ON_SimpleArray<T>&& ) ON_NOEXCEPT;
#endif

  ON_SimpleArray(size_t); // size_t parameter = initial capacity

  // emergency bailout ///////////////////////////////////////////////////
  void EmergencyDestroy(void); // call only when memory used by this array
                               // may have become invalid for reasons beyond
                               // your control. EmergencyDestroy() zeros
                               // anything that could possibly cause
                               // ~ON_SimpleArray() to crash.

  // query ///////////////////////////////////////////////////////////////
  
	int Count() const;      // number of elements in array
  unsigned int UnsignedCount() const;
	
	int Capacity() const;  // capacity of array

  unsigned int SizeOfArray() const; // amount of memory in the m_a[] array

  unsigned int SizeOfElement() const; // amount of memory in an m_a[] array element

  ON__UINT32 DataCRC(ON__UINT32 current_remainder) const;

  // The operator[] does to not check for valid indices.
  // The caller is responsible for insuring that 0 <= i < Capacity()
  T& operator[]( int );
  T& operator[]( unsigned int );
  T& operator[]( ON__INT64 );
  T& operator[]( ON__UINT64 );
#if defined(ON_RUNTIME_APPLE)
  T& operator[]( size_t );
#endif

  const T& operator[]( int ) const;
  const T& operator[]( unsigned int ) const;  
  const T& operator[]( ON__INT64 ) const;
  const T& operator[]( ON__UINT64 ) const;  
#if defined(ON_RUNTIME_APPLE)
  const T& operator[]( size_t ) const;  
#endif

  operator T*();                     // The cast operators return a pointer
  operator const T*() const;         // to the array.  If Count() is zero,
                                     // this pointer is nullptr.

  T* First();
  const T* First() const;             // returns nullptr if count = 0

  // At(index) returns nullptr if index < 0 or index >= count
  T* At( int );
  T* At( unsigned int );
  T* At( ON__INT64 );
  T* At( ON__UINT64 );
  const T* At( int ) const;
  const T* At( unsigned int ) const;
  const T* At( ON__INT64 ) const;
  const T* At( ON__UINT64 ) const;

  T* Last();
  const T* Last() const;             // returns nullptr if count = 0

  
  // array operations ////////////////////////////////////////////////////

  T& AppendNew();                    // Most efficient way to add a new element 
                                     // to the array.  Increases count by 1.
                                     // Returned element is memset to zero.

  void Append( const T& );           // Append copy of element.
                                     // Increments count by 1.

  void Append( int, const T* );      // Append copy of an array T[count]

  void Prepend( int, const T* );      // Prepend copy of an array T[count]

  void Insert( int, const T& );      // Insert copy of element. Uses
                                     // memmove() to perform any
                                     // necessary moving.
                                     // Increases count by 1.

  void Remove();                     // Removes last element.  Decrements
                                     // count by 1.  Does not change capacity.

  virtual
  void Remove( int );                // Removes element. Uses memmove() to
                                     // perform any necessary shifting.
                                     // Decrements count by 1.  Does not change
                                     // capacity

  void RemoveValue(const T&);        // Removes elements. Uses memcmp() to compare
                                     // Decrements count by removed items.  Does 
                                     // not change capacity

  void RemoveIf(bool predicate(const T& key));
                                     // Removes elements for which predicate 
                                     // returns true. Decrements count 
                                     // by removed items.
                                     // Does not change capacity

  void Empty();           // Sets count to 0, leaves capacity untouched.

  void Reverse();         // reverse order

  void Swap(int,int);     // swap elements i and j

  //////////
  // Search( e ) does a SLOW search of the array starting at array[0]
  // and returns the index "i" of the first element that satisfies 
  // e == array[i]. (== is really memcmp()).  If the search is not 
  // successful, then Search() returns -1.  For Search(T) to work 
  // correctly, T must be a simple type.  Use Search(p,compare())
  // for Ts that are structs/classes that contain pointers.  Search()
  // is only suitable for performing infrequent searches of small 
  // arrays.  Sort the array and use BinarySearch() for performing
  // efficient searches.
  int Search( const T& ) const;

  //////////
  // Search( p, compare ) does a SLOW search of the array starting
  // at array[0] and returns the index "i" of the first element 
  // that satisfies  compare(p,&array[i])==0.  If the search is not
  // successful, then Search() returns -1.  Search() is only suitable
  // for performing infrequent searches of small arrays.  Sort the
  // array and use BinarySearch() for performing efficient searches.
	// See Also: ON_CompareIncreasing<T> and ON_CompareDeccreasing<T>
  int Search( const T*, int (*)(const T*,const T*) ) const;

  //////////
  // BinarySearch( p, compare ) does a fast search of a sorted array
  // and returns the smallest index "i" of the element that satisfies
  // 0==compare(p,&array[i]).  
  //
  // BinarySearch( p, compare, count ) does a fast search of the first
  // count element sorted array and returns the smallest index "i" of 
  // the element that satisfies 0==compare(p,&array[i]).  The version
  // that takes a "count" is useful when elements are being appended
  // during a calculation and the appended elements are not sorted.
  //
  // If the search is successful, 
  // BinarySearch() returns the index of the element (>=0).
  // If the search is not successful, BinarySearch() returns -1.  
  // Use QuickSort( compare ) or, in rare cases and after meaningful
  // performance testing using optimzed release builds, 
  // HeapSort( compare ) to sort the array.
	// See Also: ON_CompareIncreasing<T> and ON_CompareDeccreasing<T>
  int BinarySearch( const T*, int (*)(const T*,const T*) ) const;
  int BinarySearch( const T*, int (*)(const T*,const T*), int ) const;

  const T* BinarySearchPtr(const T*, int (*)(const T*, const T*)) const;
  const T* BinarySearchPtr(const T*, int (*)(const T*, const T*), int) const;


  int InsertInSortedList(const T&, int (*)(const T*, const T*));
  int InsertInSortedList(const T&, int (*)(const T*, const T*), int);

  //////////
  // Sorts the array using the heap sort algorithm.
  // QuickSort() is generally the better choice.
  bool HeapSort( int (*)(const T*,const T*) );

  //////////
  // Sorts the array using the quick sort algorithm.
	// See Also: ON_CompareIncreasing<T> and ON_CompareDeccreasing<T>
  bool QuickSort( int (*)(const T*,const T*) );

  //////////
  // Sorts the array using the quick sort algorithma and then removes duplicates.
	// See Also: ON_CompareIncreasing<T> and ON_CompareDeccreasing<T>
  bool QuickSortAndRemoveDuplicates( int (*)(const T*,const T*) );

  /*
  Description:
    Sort() fills in the index[] array so that 
    array[index[i]] <= array[index[i+1]].  
    The array is not modified.  

  Parameters:
    sort_algorithm - [in]  
      ON::sort_algorithm::quick_sort (best in general) or ON::sort_algorithm::heap_sort
      Use ON::sort_algorithm::heap_sort only if you have done extensive testing with
      optimized release builds and are confident heap sort is 
      significantly faster.
    index - [out] an array of length Count() that is returned with
        some permutation of (0,1,...,Count()-1). 
    compare - [in] compare function compare(a,b,p) should return
        <0 if a<b, 0, if a==b, and >0 if a>b.
  Returns:
    true if successful
  */
  bool Sort( 
    ON::sort_algorithm sort_algorithm, 
    int* /* index[] */ ,
    int (*)(const T*,const T*) 
    ) const; 

  /*
  Description:
    Sort() fills in the index[] array so that 
    array[index[i]] <= array[index[i+1]].  
    The array is not modified.  

  Parameters:
    sort_algorithm - [in]  
      ON::sort_algorithm::quick_sort (best in general) or ON::sort_algorithm::heap_sort
      Use ON::sort_algorithm::heap_sort only if you have done extensive testing with
      optimized release builds and are confident heap sort is 
      significantly faster.
    index - [out] an array of length Count() that is returned with
        some permutation of (0,1,...,Count()-1). 
    compare - [in] compare function compare(a,b,p) should return
        <0 if a<b, 0, if a==b, and >0 if a>b.
    p - [in] pointer passed as third argument to compare.

  Returns:
    true if successful
  */
  bool Sort( 
    ON::sort_algorithm sort_algorithm,
    int*, // index[] 
    int (*)(const T*,const T*,void*), // int compare(const T*,const T*,void* p)
    void* // p
    ) const; 

  //////////
  // Permutes the array so that output[i] = input[index[i]].
  // The index[] array should be a permutation of (0,...,Count()-1).
  bool Permute( const int* /*index[]*/ );

  //////////
  // Zeros all array memory. 
  // Count and capacity are not changed.
  void Zero();

  //////////
  // Sets all bytes in array memory to value. 
  // Count and capacity are not changed.
  void MemSet(unsigned char); 

  //////////
  // Sets all specified items in an array range to a value. 
  // Count and capacity are not changed.
  void SetRange(int from, int count, T);
  
  // memory management ////////////////////////////////////////////////////

  T* Reserve( size_t );    // increase capacity to at least the requested value

  void Shrink();          // remove unused capacity

  void Destroy();         // onfree any memory and set count and capacity to zero
    
  // low level memory management //////////////////////////////////////////

  // By default, ON_SimpleArray<> uses onrealloc() to manage
  // the dynamic array memory. If you want to use something 
  // besides onrealloc() to manage the array memory, then override 
  // Realloc(). The T* Realloc(ptr, capacity) should do the following:
  //
  // 1) If ptr and capacity are zero, return nullptr.
  // 2) If ptr is nullptr, an capacity > 0, allocate a memory block of 
  //    capacity*sizeof(T) bytes and return a pointer to this block.
  //    If the allocation request fails, return nullptr.
  // 3) If ptr is not nullptr and capacity is 0, free the memory block
  //    pointed to by ptr and return nullptr.
  // 4) If ptr is not nullptr and capacity > 0, then reallocate the memory
  //    block and return a pointer to the reallocated block.  If the 
  //    reallocation request fails, return nullptr.
  //
  // NOTE WELL: 
  //    Microsoft's VC 6.0 realloc() contains a bug that can cause
  //    crashes and should be avoided. See MSDN Knowledge Base article
  //    ID Q225099 for more information.
  virtual
  T* Realloc(T*,int); // (re)allocated capacity*sizeof(T) bytes

  T* Array();                         // The Array() function return the 
  
  const T* Array() const;             // m_a pointer value.

  void SetCount( int );               // If value is <= Capacity(), then
                                      // sets count to specified value.

  T* SetCapacity( size_t );            // Shrink/grows capacity.  If value
                                      // is < current Count(), then count
                                      // is reduced to value.
                                      //

  int NewCapacity() const;            // When the dynamic array needs to grow,
                                      // this calculates the new value for m_capacity.

  /*
  Description:
    Expert user tool to take charge of the memory used by 
    the dynamic array.
  Returns:
     A pointer to the array and zeros out this class.
     The returned pointer is on the heap and must be
     deallocated by calling onfree().
  */
  T* KeepArray();

  /*
  Description:
    Do not use this version of SetArray().  Use the one that takes
    a pointer, count and capacity.
  */
  void SetArray(T*);

  /*
  Description:
    Expert user tool to set the memory used by the dynamic array.
  Parameters:
    T* pointer - [in]
    int count [in]
    int capacity - [in]
       m_a is set to pointer, m_count is set to count, and m_capacity
       is set to capacity.  It is critical that the pointer be one 
       returned by onmalloc(sz), where sz >= capacity*sizeof(T[0]).
  */
  void SetArray(T*, int, int);

protected:
  // implementation //////////////////////////////////////////////////////
  void Move( int /* dest index*/, int /* src index */, int /* element count*/ );
	T*   m_a;        // pointer to array memory
	int  m_count;    // 0 <= m_count <= m_capacity
	int  m_capacity; // actual length of m_a[]
};


////////////////////////////////////////////////////////////////
//

#if defined(ON_DLL_TEMPLATE)

ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<bool>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<char>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON__INT8>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON__UINT8>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON__INT16>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON__UINT16>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON__INT32>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON__UINT32>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<float>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<double>;

ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<bool*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<char*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON__INT8*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON__UINT8*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON__INT16*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON__UINT16*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON__INT32*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON__UINT32*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<float*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<double*>;

#endif



////////////////////////////////////////////////////////////////
//
// The ON_ClassArray<> template is designed to be used with
// classes that require non-trivial construction or destruction.
// Any class used with the ON_ClassArray<> template must have a
// robust operator=().
//
// By default, ON_ClassArray<> uses onrealloc() to manage
// the dynamic array memory. If you want to use something 
// besides onrealloc() to manage the array memory, then override
// ON_ClassArray::Realloc().  In practice this means that if your
// class has members with back-pointers, then you cannot use
// it in the default ON_ClassArray.  See ON_ObjectArray
// for an example.
//
template <class T> class ON_ClassArray
{
public:
  // construction ////////////////////////////////////////////////////////
  ON_ClassArray() ON_NOEXCEPT; 
  ON_ClassArray( size_t ); // size_t parameter = initial capacity

  // Copy constructor
  ON_ClassArray( const ON_ClassArray<T>& );

  virtual
  ~ON_ClassArray(); // override for struct member deallocation, etc.

  // Assignment operator
  ON_ClassArray<T>& operator=( const ON_ClassArray<T>& );

#if defined(ON_HAS_RVALUEREF)
  // Clone constructor
  ON_ClassArray( ON_ClassArray<T>&& ) ON_NOEXCEPT;

  // Clone Assignment operator
  ON_ClassArray<T>& operator=( ON_ClassArray<T>&& ) ON_NOEXCEPT;
#endif
  
  // emergency bailout ///////////////////////////////////////////////////
  void EmergencyDestroy(void); // call only when memory used by this array
                               // may have become invalid for reasons beyond
                               // your control. EmergencyDestroy() zeros
                               // anything that could possibly cause
                               // ~ON_ClassArray() to crash.

  // query ///////////////////////////////////////////////////////////////
  
	int Count() const;      // number of elements in array
	unsigned int UnsignedCount() const;

	int Capacity() const;  // capacity of array

  unsigned int SizeOfArray() const; // amount of memory in the m_a[] array

  unsigned int SizeOfElement() const; // amount of memory in an m_a[] array element

  // The operator[] does to not check for valid indices.
  // The caller is responsible for insuring that 0 <= i < Capacity()
  T& operator[]( int );
  T& operator[]( unsigned int );
  T& operator[]( ON__INT64 );
  T& operator[]( ON__UINT64 );
#if defined(ON_RUNTIME_APPLE)
  T& operator[]( size_t );
#endif

  const T& operator[]( int ) const;
  const T& operator[]( unsigned int ) const;  
  const T& operator[]( ON__INT64 ) const;
  const T& operator[]( ON__UINT64 ) const;  
#if defined(ON_RUNTIME_APPLE)
  const T& operator[]( size_t ) const;  
#endif

  operator T*();                     // The cast operators return a pointer
  operator const T*() const;         // to the array.  If Count() is zero,
                                     // this pointer is nullptr.
  T* First();
  const T* First() const;             // returns nullptr if count = 0

  // At(index) returns nullptr if index < 0 or index >= count
  T* At( int );
  T* At( unsigned int );
  T* At( ON__INT64 );
  T* At( ON__UINT64 );
  const T* At( int ) const;
  const T* At( unsigned int ) const;
  const T* At( ON__INT64 ) const;
  const T* At( ON__UINT64 ) const;

  T* Last();
  const T* Last() const;             // returns nullptr if count = 0

  
  // array operations ////////////////////////////////////////////////////

  T& AppendNew();                    // Most efficient way to add a new class 
                                     // to the array.  Increases count by 1.

  void Append( const T& );           // Append copy of element.
                                     // Increments count by 1.

  void Append( int, const T*);       // Append copy of an array T[count]

  void Insert( int, const T& );      // Insert copy of element. Uses
                                     // memmove() to perform any
                                     // necessary moving.
                                     // Increases count by 1.

  void Remove();                     // Removes last element.  Decrements
                                     // count by 1.  Does not change capacity.

  void Remove( int );                // Removes element. Uses memmove() to
                                     // perform any necessary shifting.
                                     // Decrements count by 1.  Does not change
                                     // capacity

  void Empty();           // Sets count to 0, leaves capacity untouched.

  void Reverse();         // reverse order

  void Swap(int,int);     // swap elements i and j

  //////////
  // Search( p, compare ) does a SLOW search of the array starting
  // at array[0] and returns the index "i" of the first element 
  // that satisfies  compare(p,&array[i])==0.  If the search is not
  // successful, then Search() returns -1.  Search() is only suitable
  // for performing infrequent searches of small arrays.  Sort the
  // array and use BinarySearch() for performing efficient searches.
  int Search( const T*, int (*)(const T*,const T*) ) const;

  //////////
  // BinarySearch( p, compare ) does a fast search of a sorted array
  // and returns the smallest index "i" of the element that satisfies
  // 0==compare(p,&array[i]).
  //
  // BinarySearch( p, compare, count ) does a fast search of the first
  // count element sorted array and returns the smallest index "i" of 
  // the element that satisfies 0==compare(p,&array[i]).  The version
  // that takes a "count" is useful when elements are being appended
  // during a calculation and the appended elements are not sorted.
  //
  // If the search is successful, 
  // BinarySearch() returns the index of the element (>=0).
  // If the search is not successful, BinarySearch() returns -1.
  // Use QuickSort( compare ) or, in rare cases and after meaningful
  // performance testing using optimzed release builds, 
  // HeapSort( compare ) to sort the array.
	// See Also: ON_CompareIncreasing<T> and ON_CompareDeccreasing<T>
  int BinarySearch( const T*, int (*)(const T*,const T*) ) const;
  int BinarySearch( const T*, int (*)(const T*,const T*), int ) const;

  int InsertInSortedList(const T&, int (*)(const T*, const T*));
  int InsertInSortedList(const T&, int (*)(const T*, const T*), int);

  //////////
  // Sorts the array using the heap sort algorithm.
	// See Also: ON_CompareIncreasing<T> and ON_CompareDeccreasing<T>
  // QuickSort() is generally the better choice.
  virtual
  bool HeapSort( int (*)(const T*,const T*) );

  //////////
  // Sorts the array using the heap sort algorithm.
  virtual
  bool QuickSort( int (*)(const T*,const T*) );

  /*
  Description:
    Sort() fills in the index[] array so that 
    array[index[i]] <= array[index[i+1]].  
    The array is not modified.  

  Parameters:
    sort_algorithm - [in]  
      ON::sort_algorithm::quick_sort (best in general) or ON::sort_algorithm::heap_sort
      Use ON::sort_algorithm::heap_sort only if you have done extensive testing with
      optimized release builds and are confident heap sort is 
      significantly faster.
    index - [out] an array of length Count() that is returned with
        some permutation of (0,1,...,Count()-1). 
    compare - [in] compare function compare(a,b) should return
        <0 if a<b, 0, if a==b, and >0 if a>b.

  Returns:
    true if successful
  */
  bool Sort( 
    ON::sort_algorithm sort_algorithm, 
    int* /* index[] */ ,
    int (*)(const T*,const T*)
    ) const; 

  /*
  Description:
    Sort() fills in the index[] array so that 
    array[index[i]] <= array[index[i+1]].  
    The array is not modified.  

  Parameters:
    sort_algorithm - [in]  
      ON::sort_algorithm::quick_sort (best in general) or ON::sort_algorithm::heap_sort
      Use ON::sort_algorithm::heap_sort only if you have done extensive testing with
      optimized release builds and are confident heap sort is 
      significantly faster.
    index - [out] an array of length Count() that is returned with
        some permutation of (0,1,...,Count()-1). 
    compare - [in] compare function compare(a,b,p) should return
        <0 if a<b, 0, if a==b, and >0 if a>b.
    p - [in] pointer passed as third argument to compare.

  Returns:
    true if successful
  */
  bool Sort( 
    ON::sort_algorithm sort_algorithm,
    int*, // index[] 
    int (*)(const T*,const T*,void*), // int compare(const T*,const T*,void* p)
    void* // p
    ) const; 

  //////////
  // Permutes the array so that output[i] = input[index[i]].
  // The index[] array should be a permutation of (0,...,Count()-1).
  bool Permute( const int* /*index[]*/ );

  //////////
  // Destroys all elements and fills them with values
  // set by the default constructor.
  // Count and capacity are not changed.
  void Zero();

  // memory management /////////////////////////////////////////////////

  T* Reserve( size_t ); // increase capacity to at least the requested value

  void Shrink();       // remove unused capacity

  void Destroy();      // onfree any memory and set count and capacity to zero
    
  // low level memory management ///////////////////////////////////////

  // By default, ON_ClassArray<> uses onrealloc() to manage
  // the dynamic array memory. If you want to use something 
  // besides onrealloc() to manage the array memory, then override 
  // Realloc(). The T* Realloc(ptr, capacity) should do the following:
  //
  // 1) If ptr and capacity are zero, return nullptr.
  // 2) If ptr is nullptr, an capacity > 0, allocate a memory block of 
  //    capacity*sizeof(T) bytes and return a pointer to this block.
  //    If the allocation request fails, return nullptr.
  // 3) If ptr is not nullptr and capacity is 0, free the memory block
  //    pointed to by ptr and return nullptr.
  // 4) If ptr is not nullptr and capacity > 0, then reallocate the memory
  //    block and return a pointer to the reallocated block.  If the 
  //    reallocation request fails, return nullptr.
  //
  // NOTE WELL: 
  //    Microsoft's VC 6.0 realloc() contains a bug that can cause
  //    crashes and should be avoided. See MSDN Knowledge Base article
  //    ID Q225099 for more information.
  virtual
  T* Realloc(T*,int); // (re)allocated capacity*sizeof(T) bytes

  T* Array();                         // The Array() function return the 
  
  const T* Array() const;             // m_a pointer value.

  void SetCount( int );               // If value is <= Capacity(), then
                                      // sets count to specified value.

  T* SetCapacity( size_t );            // Shrink/grows capacity.  If value
                                      // is < current Count(), then count
                                      // is reduced to value.

  int NewCapacity() const;            // When the dynamic array needs to grow,
                                      // this calculates the new value for m_capacity.

  T* KeepArray();                     // returns pointer to array and zeros
                                      // out this class.  Caller is responsible
                                      // for calling destructor on each element
                                      // and then using onfree() to release array
                                      // memory.  E.g.,
                                      //
                                      //   for (int i=capacity;i>=0;i--) {
                                      //     array[i].~T();
                                      //   }
                                      //   onfree(array);

  /*
  Description:
    Do not use this version of SetArray().  Use the one that takes
    a pointer, count and capacity: SetArray(pointer,count,capacity)
  */
  void SetArray(T*);

  /*
  Description:
    Expert user tool to set the memory used by the dynamic array.
  Parameters:
    T* pointer - [in]
    int count - [in]  0 <= count <= capacity
    int capacity - [in]
       m_a is set to pointer, m_count is set to count, and m_capacity
       is set to capacity.  It is critical that the pointer be one 
       returned by onmalloc(sz), where sz >= capacity*sizeof(T[0]),
       and that the in-place operator new has been used to initialize
       each element of the array.  
  */
  void SetArray(T*, int, int);

protected:
  // implementation //////////////////////////////////////////////////////
  void Move( int /* dest index*/, int /* src index */, int /* element count*/ );
  void ConstructDefaultElement(T*);
  void DestroyElement(T&);
	T*   m_a;        // pointer to array memory
	int  m_count;    // 0 <= m_count <= m_capacity
	int  m_capacity; // actual length of m_a[]
};

#if defined(ON_DLL_TEMPLATE)

ON_DLL_TEMPLATE template class ON_CLASS ON_ClassArray<ON_String>;
ON_DLL_TEMPLATE template class ON_CLASS ON_ClassArray<ON_wString>;

#endif

/*
Description:
  ON_Object array is used to store lists of classes that are
  derived from ON_Object.  It differs from ON_ClassArray in
  that the virtual ON_Object::MemoryRelocate function is called
  when growing the dynamic array requires changing the location
  of the memory buffer used to store the elements in the array.
*/
template <class T> class ON_ObjectArray : public ON_ClassArray<T>
{
public:
  ON_ObjectArray(); 
  ~ON_ObjectArray(); // override for struct member deallocation, etc.
  ON_ObjectArray( size_t ); // size_t parameter = initial capacity
  ON_ObjectArray( const ON_ObjectArray<T>& );
  ON_ObjectArray<T>& operator=( const ON_ObjectArray<T>& );

#if defined(ON_HAS_RVALUEREF)
  // Clone constructor
  ON_ObjectArray( ON_ObjectArray<T>&& );

  // Clone Assignment operator
  ON_ObjectArray<T>& operator=( ON_ObjectArray<T>&& );
#endif

  ON__UINT32 DataCRC(ON__UINT32 current_remainder) const;

  // virtual ON_ClassArray<T> override that 
  // calls MemoryRelocate on each element after
  // the reallocation.
  T* Realloc(T*,int);

  // virtual ON_ClassArray<T> override that 
  // calls MemoryRelocate on each element after
  // the heap sort.
  // QuickSort() is generally the better choice.
  bool HeapSort( int (*)(const T*,const T*) );

  // virtual ON_ClassArray<T> override that 
  // calls MemoryRelocate on each element after
  // the quick sort.
  bool QuickSort( int (*)(const T*,const T*) );
};

class ON_CLASS ON_UuidPair
{
public:
  /*
  Description:
    Compares m_uuid[0] and ignores m_uuid[1]
  */
  static 
  int CompareFirstUuid(const class ON_UuidPair*,const class ON_UuidPair*);

  /*
  Description:
    Compares m_uuid[1] and ignores m_uuid[0]
  */
  static 
  int CompareSecondUuid(const class ON_UuidPair*,const class ON_UuidPair*);

  /*
  Description:
    Compares m_uuid[0] then m_uuid[1].
  */
  static 
  int Compare(const class ON_UuidPair*,const class ON_UuidPair*);

  ON_UuidPair();
  ON_UUID m_uuid[2];
};

#if defined(ON_DLL_TEMPLATE)

ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_UUID>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_UuidIndex>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_UuidPtr>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_UuidPair>;
ON_DLL_TEMPLATE template class ON_CLASS ON_ClassArray<ON_SimpleArray<int> >;

#endif


/*
Description:
  The ON_UuidList class provides a tool to efficiently 
  maintain a list of uuids and determine if a uuid is 
  in the list. This class is based on the premise that 
  there are no duplicate uuids in the list.
*/
class ON_CLASS ON_UuidList : private ON_SimpleArray<ON_UUID>
{
public:
  ON_UuidList();
  ON_UuidList(int capacity);
  ~ON_UuidList();
  ON_UuidList(const ON_UuidList& src);
  ON_UuidList& operator=(const ON_UuidList& src);

  bool operator==(const ON_UuidList& other) const;
  bool operator!=(const ON_UuidList& other) const;

  /*
  Description:
    Fast uuid compare.  Not necessarily the same
    as ON_UuidCompare().
  */
  static
  int CompareUuid( const ON_UUID* a, const ON_UUID* b );

  /*
  Returns:
    Number of active uuids in the list.
  */
  int Count() const;

  /*
  Returns:
    Array of uuids in the list.  Sorted with
    respect to ON_UuidList::CompareUuid().
  Remarks:
    Calling AddUuid() may grow the dynamic array
    and make the pointer invalid.
  */
  const ON_UUID* Array() const;

  /*
  Description:
    Provides an efficient way to empty a list so that it
    can be used again.
  */
  void Empty();

  /*
  Description:
    Destroy list.  If list will be reused, Empty() is more
    efficient.
  */
  void Destroy();

  void Reserve(size_t capacity);

  /*
  Description:
    Makes the uuid list as efficient as possible in both search
    speed and memory usage.  Use Compact() when a uuid list
    will be in use but is not likely to be modified.  A list 
    that has been compacted can still be modified.
  */
  void Compact();

  /*
  Description:
    Adds a uuid to the list.
  Parameters:
    uuid - [in] id to add.
    bCheckForDupicates - [in] if true, then the uuid
       is not added if it is already in the list.
       If you are certain that the uuid is not in the
       list and you are going to have a large list of uuids,
       then setting bCheckForDupicates=false will
       speed up the addition of uuids.
  Returns:
    True if uuid was added.  False if uuid was not added
    because it is already in the collection.
  */
  bool AddUuid(ON_UUID uuid, bool bCheckForDupicates=true);

  /*
  Description:
    Removes a uuid from the list.
  Parameters:
    uuid - [in] id to remove
  Returns:
    True if uuid was in the list and was removed.
    False if uuid was not in the list.
  */
  bool RemoveUuid(ON_UUID uuid);

  /*
  Description:
    Determine if a uuid is in the list.
  Returns:
    True if uuid is in the list.
  */
  bool FindUuid(ON_UUID uuid) const;

  /*
  Description:
    Saves the uuid list in an archive.
  Parameters:
    archive - [in] archive to write to.
  Returns:
    true if write was successful.
  */
  bool Write( 
    class ON_BinaryArchive& archive 
    ) const;

  /*
  Description:
    Saves the uuid list in an archive.
  Parameters:
    archive - [in] archive to write to.
    bSortBeforeWrite - [in]
      True if ids should be sorted before the write
      so future lookups will be fast.  False if
      the current state of the sorted/unsorted bits
      should be preserved.
  Returns:
    true if write was successful.
  */
  bool Write( 
    class ON_BinaryArchive& archive,
      bool bSortBeforeWrite
    ) const;

  /*
  Description:
    Read the uuid list from an archive.
  Parameters:
    archive - [in] archive to read from.
  Returns:
    true if the read was successful.
  */
  bool Read( 
    class ON_BinaryArchive& archive 
    );

  /*
  Description:
    Read the uuid list from an archive.
  Parameters:
    archive - [in] 
      archive to read from.
    bool bSortAfterRead - [in]
      True if ids should be sorted after the read
      so future lookups will be fast.  False if
      the state of the sorted/unsorted bits that
      existed at write time should be preserved.
  Returns:
    true if the read was successful.
  */
  bool Read( 
    class ON_BinaryArchive& archive,
    bool bSortAferRead
    );

  /*
  Description:
    Append the uuids in this class to uuid_list.
  Parameters:
    uuid_list - [in/out]
  Returns:
    Number of uuids added to uuid_list.
  */
  int GetUuids(
     ON_SimpleArray<ON_UUID>& uuid_list
     ) const;

  /*
  Description:
    This tool is used in rare situations when the object ids 
    stored in the uuid list need to be remapped.
  Parameters:
    uuid_remap - [in]
      Is it critical that uuid_remap[] be sorted with respect
      to ON_UuidPair::CompareFirstUuid.
  */
  void RemapUuids( 
    const ON_SimpleArray<ON_UuidPair>& uuid_remap 
    );

private:
  void PurgeHelper();
  void SortHelper();
  ON_UUID* SearchHelper(const ON_UUID*) const;
  int m_sorted_count;
  int m_removed_count;
};

/*
Description:
  The ON_UuidList class provides a tool
  to efficiently maintain a list of uuid-index
  pairs and determine if a uuid is in the list.
  This class is based on the premise that there are
  no duplicate uuids in the list.
*/
class ON_CLASS ON_UuidIndexList : private ON_SimpleArray<ON_UuidIndex>
{
public:
  ON_UuidIndexList() = default;
  ON_UuidIndexList(size_t capacity);
  ~ON_UuidIndexList() = default;
  ON_UuidIndexList(const ON_UuidIndexList& src);
  ON_UuidIndexList& operator=(const ON_UuidIndexList& src);

  /*
  Returns:
    Number of active uuids in the list.
  */
  unsigned int Count() const;

  /*
  Description:
    Provides an efficient way to empty a list so that it
    can be used again.
  */
  void RemoveAll();

  void Reserve( size_t capacity );

  /*
  Description:
    Adds a uuid-index pair to the list.
  Parameters:
    uuid - [in] id to add.  
      This uuid cannot be ON_max_uuid because ON_max_uuid
      is 
    bCheckForDupicates - [in] if true, then the uuid
       is not added if it is already in the list.
       If you are certain that the uuid is not in the list
       and you have a have a large collection of uuids,
       then setting bCheckForDupicates=false will
       speed up the addition of uuids.
  Returns:
    True if uuid was added.  False if uuid was not added
    because it is already in the collection.
  */
  bool AddUuidIndex(
    ON_UUID uuid, 
    int index, 
    bool bCheckForDupicates=true);

  /*
  Description:
    Removes an element with a matching uuid from the list.
  Parameters:
    uuid - [in] id to remove
  Returns:
    True if an element was removed.  False if the uuid
    was not in the list.
  */
  bool RemoveUuid(
    ON_UUID uuid
    );

  /*
  Description:
    Determine if an element with a uuid is in the list.
  Parameters:
    index - [out] if not nullptr and a matching uuid is found,
       then *index is set to the value of the index.
  Returns:
    True if an element was found.  Returns false if
    the uuid is not in the list.
  */
  bool FindUuid(ON_UUID uuid) const;
  bool FindUuid(ON_UUID uuid, int* index) const;

  /*
  Description:
    Determine if a uuid-index pair is in the list.
  Returns:
    True if the uuid-index pair is in the list.
    Returns false if the uuid-index pair is not
    in the list.
  */
  bool FindUuidIndex(ON_UUID uuid, int index) const;

  /*
  Description:
    Append the uuids in this class to uuid_list.
  Parameters:
    uuid_list - [in/out]
  Returns:
    Number of uuids added to uuid_list.
  */
  unsigned int GetUuids(
     ON_SimpleArray<ON_UUID>& uuid_list
     ) const;

  /*
  Description:
    If you will perform lots of searches before the next
    change to the list, then calling ImproveSearchSpeed()
    will speed up the searches by culling removed objects
    and completely sorting the list so only a binary search
    is required. You may edit the list at any time after 
    calling ImproveSearchSpeed().  If you are performing 
    a few searches between edits, then excessive calling
    of ImproveSearchSpeed() may actually decrease overall
    program performance.
  */
  void ImproveSearchSpeed();

private:
  ON_UuidIndex* SearchHelper(const ON_UUID*) const;
  unsigned int m_sorted_count = 0;
  unsigned int m_removed_count = 0;
};







/*
Description:
  The ON_UuidList class provides a tool
  to efficiently maintain a list of uuid-pointer
  pairs and determine if a uuid is in the list.
  This class is based on the premise that there are
  no duplicate uuids in the list.
*/
class ON_CLASS ON_UuidPtrList : private ON_SimpleArray<ON_UuidPtr>
{
public:
  ON_UuidPtrList() = default;
  ON_UuidPtrList(size_t capacity);
  ~ON_UuidPtrList() = default;
  ON_UuidPtrList(const ON_UuidPtrList& src);
  ON_UuidPtrList& operator=(const ON_UuidPtrList& src);

  /*
  Returns:
    Number of active uuids in the list.
  */
  unsigned int Count() const;

  /*
  Description:
    Provides an efficient way to empty a list so that it
    can be used again.
  */
  void RemoveAll();

  void Reserve( size_t capacity );

  /*
  Description:
    Adds a uuid-index pair to the list.
  Parameters:
    uuid - [in] id to add.  
      This uuid cannot be ON_max_uuid because ON_max_uuid
      is 
    bCheckForDupicates - [in] if true, then the uuid
       is not added if it is already in the list.
       If you are certain that the uuid is not in the list
       and you have a have a large collection of uuids,
       then setting bCheckForDupicates=false will
       speed up the addition of uuids.
  Returns:
    True if uuid was added.  False if uuid was not added
    because it is already in the collection.
  */
  bool AddUuidPtr(
    ON_UUID uuid, 
    ON__UINT_PTR ptr, 
    bool bCheckForDupicates=true);

  /*
  Description:
    Removes an element with a matching uuid from the list.
  Parameters:
    uuid - [in] id to remove
  Returns:
    True if an element was removed.  False if the uuid
    was not in the list.
  */
  bool RemoveUuid(
    ON_UUID uuid
    );

  /*
  Description:
    Determine if an element with a uuid is in the list.
  Parameters:
    ptr - [out] if not nullptr and a matching uuid is found,
       then *ptr is set to the value of the m_ptr.
  Returns:
    True if an element was found.  Returns false if
    the uuid is not in the list.
  */
  bool FindUuid(ON_UUID uuid) const;
  bool FindUuid(ON_UUID uuid, ON__UINT_PTR* ptr) const;

  /*
  Description:
    Determine if a uuid-index pair is in the list.
  Returns:
    True if the uuid-index pair is in the list.
    Returns false if the uuid-index pair is not
    in the list.
  */
  bool FindUuidPtr(ON_UUID uuid, ON__UINT_PTR index) const;

  /*
  Description:
    Append the uuids in this class to uuid_list.
  Parameters:
    uuid_list - [in/out]
  Returns:
    Number of uuids added to uuid_list.
  */
  unsigned int GetUuids(
     ON_SimpleArray<ON_UUID>& uuid_list
     ) const;

  /*
  Description:
    If you will perform lots of searches before the next
    change to the list, then calling ImproveSearchSpeed()
    will speed up the searches by culling removed objects
    and completely sorting the list so only a binary search
    is required. You may edit the list at any time after 
    calling ImproveSearchSpeed().  If you are performing 
    a few searches between edits, then excessive calling
    of ImproveSearchSpeed() may actually decrease overall
    program performance.
  */
  void ImproveSearchSpeed();

private:
  ON_UuidPtr* SearchHelper(const ON_UUID*) const;
  unsigned int m_sorted_count = 0;
  unsigned int m_removed_count = 0;
};








/*
Description:
  The ON_UuidPairList class provides a tool
  to efficiently maintain a list of uuid pairs 
  and determine if a uuid is in the list.
  This class is based on the premise that there are
  no duplicate uuids in the list.
*/
class ON_CLASS ON_UuidPairList : private ON_SimpleArray<ON_UuidPair>
{
public:
  ON_UuidPairList();
  ON_UuidPairList(int capacity);
  ~ON_UuidPairList();
  ON_UuidPairList(const ON_UuidPairList& src);
  ON_UuidPairList& operator=(const ON_UuidPairList& src);

  static const ON_UuidPairList EmptyList;

  /*
  Returns:
    Number of active uuids in the list.
  */
  int Count() const;

  /*
  Description:
    Provides an efficient way to empty a list so that it
    can be used again.
  */
  void Empty();

  void Reserve( size_t capacity );

  /*
  Description:
    Adds a uuid-index pair to the list.
  Parameters:
    id1 - [in] id to add.
    id2 - [in] id to add.
    bCheckForDupicates - [in] if true, then the pair
       is not added if id1 is already in the list.
       If you are certain that the id1 is not in the list
       and you have a have a large collection of uuids,
       then setting bCheckForDupicates=false will
       speed up the addition of uuids.
  Returns:
    True if the pair was added.  False if the pair was not added
    because it is already in the collection.
  Remarks:
    You cannot add the pair value ( ON_max_uuid, ON_max_uuid ). This
    pair value is used to mark removed elements in the ON_UuidPairList[].
  */
  bool AddPair(
    ON_UUID id1, 
    ON_UUID id2, 
    bool bCheckForDupicates=true
    );

  /*
  Description:
    Removes an element with a matching id1 from the list.
  Parameters:
    id1 - [in] id to remove
  Returns:
    True if an element was removed.  False if the id1
    was not in the list.
  */
  bool RemovePair(
    ON_UUID id1
    );

  /*
  Description:
    Removes an element with a matching id pair from the list.
  Parameters:
    id1 - [in]
    id2 - [in]
  Returns:
    True if an element was removed.  False if the id pair
    does not appear in the list.
  */
  bool RemovePair(
    ON_UUID id1,
    ON_UUID id2
    );

  /*
  Description:
    Determine if an element with a uuid is in the list.
  Parameters:
    id1 - [in]
    id2 - [out] if not nullptr and a matching id1 is found,
       then *id2 is set to the value of the second uuid.
  Returns:
    True if an element was found.  Returns false if
    the id1 is not in the list.
  */
  bool FindId1(ON_UUID id1, ON_UUID* id2=0) const;

  /*
  Description:
    Determine if an id pair is in the list.
  Returns:
    True if the id pair is in the list.
    False if the id pair is not in the list.
  */
  bool FindPair(ON_UUID id1, ON_UUID id2) const;

  /*
  Description:
    Append the value of the first id in each pair to uuid_list[].
  Parameters:
    uuid_list - [in/out]
  Returns:
    Number of ids appended to uuid_list[].
  */
  int GetId1s(
     ON_SimpleArray<ON_UUID>& uuid_list
     ) const;

  /*
  Description:
    If you will perform lots of searches before the next
    change to the list, then calling ImproveSearchSpeed()
    will speed up the searches by culling removed objects
    and completely sorting the list so only a binary search
    is required. You may edit the list at any time after 
    calling ImproveSearchSpeed().  If you are performing 
    a few searches between edits, then excessive calling
    of ImproveSearchSpeed() may actually decrease overall
    program performance.
  */
  void ImproveSearchSpeed();

  bool Write(
    class ON_BinaryArchive& archive
    ) const;

  bool Read(
    class ON_BinaryArchive& archive
    );

private:
  ON_UuidPair* SearchHelper(const ON_UUID*) const;
  unsigned int m_sorted_count;
  unsigned int m_removed_count;
};



class ON_CLASS ON_UuidPtrList2
{
public:
  ON_UuidPtrList2();
  ~ON_UuidPtrList2();
  ON_UuidPtrList2(const ON_UuidPtrList2& src);
  ON_UuidPtrList2& operator=(const ON_UuidPtrList2& src);

  unsigned int Count() const;
  void RemoveAll();
  void Reserve(size_t capacity);
  bool AddUuidPtr(const ON_UUID& uuid, ON__UINT_PTR ptr);
  bool RemoveUuid(const ON_UUID& uuid);
  bool FindUuid(const ON_UUID& uuid) const;
  bool FindUuid(const ON_UUID& uuid, ON__UINT_PTR* ptr) const;
  bool FindUuidPtr(const ON_UUID& uuid, ON__UINT_PTR index) const;
  unsigned int GetUuids(ON_SimpleArray<ON_UUID>& uuid_list) const;
  void ImproveSearchSpeed();

private:
#pragma warning (push)
#pragma warning (disable : 4251)
  std::unique_ptr<class ON_UuidPtrList2_Private> m_private;
  unsigned char padding[sizeof(ON_UuidPtrList) - sizeof(m_private)];
#pragma warning (pop)
};

class ON_CLASS ON_UuidPairList2
{
public:
  ON_UuidPairList2();
  ~ON_UuidPairList2();
  ON_UuidPairList2(const ON_UuidPairList2& src);
  ON_UuidPairList2& operator=(const ON_UuidPairList2& src);

  static const ON_UuidPairList2 EmptyList;

  unsigned int Count() const;
  void Empty();
  void Reserve(size_t capacity);
  bool AddPair(const ON_UUID& id1, const ON_UUID& id2);
  bool RemovePair(const ON_UUID& id1);
  bool RemovePair(const ON_UUID& id1, const ON_UUID& id2);
  bool FindId1(const ON_UUID& id1, ON_UUID* id2 = 0) const;
  bool FindPair(const ON_UUID& id1, const ON_UUID& id2) const;
  int GetId1s(ON_SimpleArray<ON_UUID>& uuid_list) const;

  void ImproveSearchSpeed();

private:
#pragma warning (push)
#pragma warning (disable : 4251)
  std::unique_ptr<class ON_UuidPairList2_Private> m_private;
  unsigned char padding[sizeof(ON_UuidPairList) - sizeof(m_private)];
#pragma warning (pop)
};

class ON_CLASS ON_UuidIndexList2
{
public:
  ON_UuidIndexList2();
  ~ON_UuidIndexList2();
  ON_UuidIndexList2(const ON_UuidIndexList2& src);
  ON_UuidIndexList2& operator=(const ON_UuidIndexList2& src);

  unsigned int Count() const;
  void RemoveAll();
  void Reserve(size_t capacity);
  bool AddUuidIndex(const ON_UUID& uuid, int index);
  bool RemoveUuid(const ON_UUID& uuid);
  bool FindUuid(const ON_UUID& uuid) const;
  bool FindUuid(const ON_UUID& uuid, int* index) const;
  bool FindUuidIndex(const ON_UUID& uuid, int index) const;
  unsigned int GetUuids(ON_SimpleArray<ON_UUID>& uuid_list) const;
  void ImproveSearchSpeed();

private:
#pragma warning (push)
#pragma warning (disable : 4251)
  std::unique_ptr<class ON_UuidIndexList2_Private> m_private;
  unsigned char padding[sizeof(ON_UuidIndexList) - sizeof(m_private)];
#pragma warning (pop)
};




class ON_CLASS ON_2dexMap : private ON_SimpleArray<ON_2dex>
{
public:
  ON_2dexMap();
  ON_2dexMap(int capacity);
  ~ON_2dexMap();

  int Count() const;

  void Reserve(size_t capacity);

  const ON_2dex* Array() const;

  ON_2dex operator[](int i) const;

  /*
  Description:
    Creates an index map with the values
    (i0,j),...,(i0+count-1,j)
  Parameters:
    count - [in]
       number of elements
    i0 - [in]
       i value of first element
    j - [in]
       j value for all elements
  */
  void Create(int count, int i0, int j);

  /*
  Description:
    Searches for an element with a matching i
    and returns its j value.  If no matching
    element is found, then not_found_rc is returned. 
  Parameters:
    i - [in]
       value of i to search for
    not_found_rc - [in]
       value to return if there is not a match.
  Returns:
    j value
  */
  int FindIndex( 
          int i, 
          int not_found_rc
          ) const;

  /*
  Description:
    Adds and element (i,j).  If there is already an entry with
    value (i,*), then no element is added.
  Parameters:
    i - [in]
    i - [in]
  Returns:
    True if and element it added.
  */
  bool AddIndex( 
          int i, 
          int j
          );

  /*
  Description:
    Searches for an element (i,*) and sets its j value to j.
    If there is no element with a matching i, then false
    is returned.
  Parameters:
    i - [in]
    j - [in]
  Returns:
    True if and element exists and was set.
  */
  bool SetIndex( 
          int i, 
          int j
          );

  /*
  Description:
    If an element (i,*) exists, its j value is set.  Otherwise
    a new element with value (i,j) is added.
  Parameters:
    i - [in]
    j - [in]
  */
  void SetOrAddIndex( 
          int i, 
          int j
          );

  /*
  Description:
    If an element (i,*) exists, it is removed.  If there is
    not an element with a matching i value, then false
    is returned.
  Parameters:
    i - [in]
  Returns:
    True if the element was removed
  */
  bool RemoveIndex( 
          int i
          );

  const ON_2dex* Find2dex(int i) const;

private:
  bool m_bSorted;
};

/* 
Description:
	Compare function for Sort and Search methods.
Returns:
   -1 if *a < *b is true
    1 if *b < *a is true
    0 if neither *a <*b nor *b<*a is true 
Details:
	Use this template functions to sort ON_SimpleArray and
  ON_ClassArray objects into increasing order.  The elements
  of the arrays must be a type with an operator < defined.
	In particular it works with built in types like double, 
  int and pointers.
Example:

          ON_SimpleArray<int> A;
          A = ...;
          // Sort A in increasing order
          A.QuickSort( ON_CompareIncreasing<double> );		

See Also:
  ON_CompareDecreasing
*/
template< class T>
static
int ON_CompareIncreasing( const T* a, const T* b);

/* 
Description:
	Compare function for Sort and Search methods.
Returns:
   -1 if *b < *a is true
    1 if *a < *b is true
    0 if neither *a < *b nor *b < *a is true 
Details:
	Use this template functions to sort ON_SimpleArray and
  ON_ClassArray objects into decreasing order.  The elements
  of the arrays must be a type with an operator < defined.
	In particular it works with built in types like double, 
  int and pointers.
Example:

          class C
          {
          public:
            ...
            bool operator<(const C&) const;
          };
          ...
          ON_ClassArray<C> A;
          A = ...;
          // Sort A in descrasing order
          A.QuickSort( ON_CompareDecreasing<C> );		

See Also:
  ON_CompareIncreasing
*/
template< class T>
static
int ON_CompareDecreasing( const T* a, const T* b);

void ON_SHA1_Accumulate2fPointArray(
  class ON_SHA1& sha1,
  const class ON_SimpleArray<ON_2fPoint>& a
);

void ON_SHA1_Accumulate3fPointArray(
  class ON_SHA1& sha1,
  const class ON_SimpleArray<ON_3fPoint>& a
);

void ON_SHA1_Accumulate4fPointArray(
  class ON_SHA1& sha1,
  const class ON_SimpleArray<ON_4fPoint>& a
);

void ON_SHA1_Accumulate2fVectorArray(
  class ON_SHA1& sha1,
  const class ON_SimpleArray<ON_2fVector>& a
);

void ON_SHA1_Accumulate3fVectorArray(
  class ON_SHA1& sha1,
  const class ON_SimpleArray<ON_3fVector>& a
);

void ON_SHA1_Accumulate2dPointArray(
  class ON_SHA1& sha1,
  const class ON_SimpleArray<ON_2dPoint>& a
);

void ON_SHA1_Accumulate3dPointArray(
  class ON_SHA1& sha1,
  const class ON_SimpleArray<ON_3dPoint>& a
);

void ON_SHA1_Accumulate4dPointArray(
  class ON_SHA1& sha1,
  const class ON_SimpleArray<ON_4dPoint>& a
);

void ON_SHA1_Accumulate2dVectorArray(
  class ON_SHA1& sha1,
  const class ON_SimpleArray<ON_2dVector>& a
);

void ON_SHA1_Accumulate3dVectorArray(
  class ON_SHA1& sha1,
  const class ON_SimpleArray<ON_3dVector>& a
);

// definitions of the template functions are in a different file
// so that Microsoft's developer studio's autocomplete utility
// will work on the template functions.
#include "opennurbs_array_defs.h"

class ON_CLASS ON_Big5UnicodePair
{
public:
  ON_Big5UnicodePair() = default;
  ~ON_Big5UnicodePair() = default;
  ON_Big5UnicodePair(const ON_Big5UnicodePair&) = default;
  ON_Big5UnicodePair& operator=(const ON_Big5UnicodePair&) = default;

public:
  /// <summary>
  /// An array sorted by BIG5 code points and useful for converting BIG5 code points to Unicode code points.
  /// </summary>
  /// <returns>Returns an array sorted by ON_Big5UnicodePair::CompareBig5AndUnicodeCodePoints()</returns>
  static const ON_SimpleArray< ON_Big5UnicodePair >& Big5ToUnicode();

  /// <summary>
  /// An array sorted by Unicode code points and useful for converting Unicode code points to BIG5 code points.
  /// </summary>
  /// <returns>Returns an array sorted by ON_Big5UnicodePair::CompareUnicodeAndBig5CodePoints()</returns>
  static const ON_SimpleArray< ON_Big5UnicodePair >& UnicodeToBig5();

public:
  static const ON_Big5UnicodePair Null;

  /// <summary>
  /// ON_Big5UnicodePair::Error.Big5() = ON_Big5CodePoint::Error and ON_Big5UnicodePair::Error.Unicode() = ON_UnicodeShortCodePoint::Error.
  /// </summary>
  static const ON_Big5UnicodePair Error;

  /// <summary>
  /// Create a BIG5 - Unicode code point pair. 
  /// </summary>
  /// <param name="big5_code_point">
  /// BIG5 code point.
  /// </param>
  /// <param name="unicode_code_point">
  /// Unicode code point.
  /// </param>
  /// <returns></returns>
  static const ON_Big5UnicodePair Create(
    ON_Big5CodePoint big5_code_point,
    ON_UnicodeShortCodePoint unicode_code_point
  );

  static const ON_Big5UnicodePair Create(
    unsigned int big5_code_point,
    unsigned int unicode_code_point
  );

  /// <summary>
  /// Determine if both code points in this pair are 0.
  /// </summary>
  /// <returns>True if both code points are 0.</returns>
  bool IsNull() const;

  /// <summary>
  /// Determing if the values stored as the BIG5 and Unicode code points are equal nonzero ASCII code points.
  /// ASCII code point are in the range 0-0x7F (127 decimal).
  /// Unicode extends ASCII. Strictly speaking, BIG5 does not extend ASCII, but it is common to mix 
  /// single bytes ASCII and double byte BIG5 encodings in the same char string.
  /// BIG5 is a double byte string encoding with the first byte in the range 0x81 to 0xFE, the
  /// minimum BIG5 code point is 0x8140 and the maximum BIG5 code point is 0xFEFE.
  /// Thus it is possible to mix ASCII and BIG5 encodings in the same char string.
  /// </summary>
  /// <param name="bNullIsASCII">
  /// Value to return if both code points are 0.
  /// </param>
  /// <returns>True if both code points are equal and ASCII code points (0 to 0x7F).</returns>
  bool IsASCII(bool bNullIsASCII) const;

  /// <summary>
  /// Determine if the pair of code points is valid. 
  /// If the values for BIG5 and Unicode code point values are &lt 0xFF and equal, the pair is considered valid. 
  /// Use IsASCII() if you need to treat nonzero ASCII code points differently.
  /// </summary>
  /// <param name="bNullIsValid">
  /// Value to return if this pair is null.
  /// </param>
  /// <param name="bASCIICodePointIsValid">
  /// Value to return if this pair is an ASCII code point.
  /// </param>
  /// <returns>True if the BIG5 and Unicode code points are both valid or IsASCII() is true.</returns>
  bool IsValid(bool bNullIsValid, bool bASCIICodePointIsValid) const;

  const ON_Big5CodePoint Big5() const;
  const ON_UnicodeShortCodePoint Unicode() const;

  unsigned int Big5CodePoint() const;
  unsigned int UnicodeCodePoint() const;

  /// <summary>
  /// 
  /// </summary>
  /// </summary>
  /// <param name="bNullIsValid">
  /// Value to return if this pair is null.
  /// </param>
  /// <param name="bASCIICodePointIsValid">
  /// Value to return if this pair is an ASCII code point.
  /// </param>
  /// <returns></returns>
  bool IsStandard(bool bNullIsValid, bool bASCIICodePointIsStandard) const;

  /// <summary>
  /// 
  /// </summary>
  /// <returns>Returns true if this pair is valid and at least one of the code points is a private use code point.
  /// </returns>
  bool IsPrivateUse() const;

  /// <summary>
  /// Compares the BIG5 code point.
  /// </summary>
  /// <param name="lhs"></param>
  /// <param name="rhs"></param>
  /// <returns></returns>
  static int CompareBig5CodePoint(const ON_Big5UnicodePair* lhs, const ON_Big5UnicodePair* rhs);

  /// <summary>
  /// Compares the Unicode code point.
  /// </summary>
  /// <param name="lhs"></param>
  /// <param name="rhs"></param>
  /// <returns></returns>
  static int CompareUnicodeCodePoint(const ON_Big5UnicodePair* lhs, const ON_Big5UnicodePair* rhs);

  /// <summary>
  /// Dictionary compare (BIG5 code point first, Unicode code point second).
  /// </summary>
  /// <param name="lhs"></param>
  /// <param name="rhs"></param>
  /// <returns></returns>
  static int CompareBig5AndUnicodeCodePoints(const ON_Big5UnicodePair* lhs, const ON_Big5UnicodePair* rhs);

  /// <summary>
  /// Dictionary compare (Unicode code point first, BIG5 code point second).
  /// </summary>
  /// <param name="lhs"></param>
  /// <param name="rhs"></param>
  /// <returns></returns>
  static int CompareUnicodeAndBig5CodePoints(const ON_Big5UnicodePair* lhs, const ON_Big5UnicodePair* rhs);

private:
  ON_Big5CodePoint m_big5;
  ON_UnicodeShortCodePoint m_unicode;
};

ON_DECL bool operator==(ON_Big5UnicodePair lhs, ON_Big5UnicodePair rhs);
ON_DECL bool operator!=(ON_Big5UnicodePair lhs, ON_Big5UnicodePair rhs);

#if defined(ON_DLL_TEMPLATE)

ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_Big5UnicodePair>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_Big5CodePoint>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_UnicodeShortCodePoint>;

#endif

#endif
