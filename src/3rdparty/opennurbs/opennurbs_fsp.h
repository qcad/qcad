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

#if !defined(OPENNURBS_FSP_INC_)
#define OPENNURBS_FSP_INC_

class ON_CLASS ON_FixedSizePoolElement
{
private:
  // ON_FixedSizePoolElement is never instantiated 
  ON_FixedSizePoolElement() = delete;
  ~ON_FixedSizePoolElement() = delete;
  ON_FixedSizePoolElement(const ON_FixedSizePoolElement&) = delete;
  ON_FixedSizePoolElement operator=(const ON_FixedSizePoolElement&) = delete;

public:
  // next element - intentionally not initialized because instantiation is not permitted.
  ON_FixedSizePoolElement* m_next;
};

class ON_CLASS ON_FixedSizePool
{
public:
  ON_FixedSizePool();
  ~ON_FixedSizePool();

#if defined(ON_HAS_RVALUEREF)
  ON_FixedSizePool(ON_FixedSizePool&&);
  ON_FixedSizePool& operator=(ON_FixedSizePool&&);
#endif


  /*
  Description:
    Create a fixed size memory pool.
  Parameters:
    sizeof_element - [in]
      number of bytes in each element. This parameter must be greater than zero.
      In general, use sizeof(element type).  If you pass a "raw" number as
      sizeof_element, then be certain that it is the right size to insure the
      fields in your elements will be properly aligned.
  Remarks:
    You must call Create() on an unused ON_FixedSizePool or call Destroy()
    before calling create.
  Returns:
    True if successful and the pool can be used.
  See Also
    CreateForExperts().
  */
  bool Create(
    size_t sizeof_element
  );

  /*
  Description:
    Create a fixed size memory pool.
    If you have a decent estimate of how many elements you need, 
    CreateForExperts() is a typically a better choice. 
    Otherwise, Create(sizeof_element) is typically the best option.

  Parameters:
    sizeof_element - [in]
      number of bytes in each element. This parameter must be greater than zero.
      In general, use sizeof(element type).  If you pass a "raw" number as
      sizeof_element, then be certain that it is the right size to insure the
      fields in your elements will be properly aligned.
    element_count_estimate - [in] (0 = good default)
      If you know how many elements you will need, pass that number here.
      It is better to slightly overestimate than to slightly underestimate.
      If you do not have a good estimate, then use zero.
    block_element_capacity - [in] (0 = good default)
      If block_element_capacity is zero, Create() will calculate a block
      size that is efficient for most applications.  If you are an expert
      user and want to specify the number of elements per block,
      then pass the number of elements per block here.  When
      block_element_capacity > 0 and element_count_estimate > 0, the first
      block will have a capacity of at least element_count_estimate; in this
      case do not ask for extraordinarily large amounts of contiguous heap.

  Remarks:
    You must call Create() on an unused ON_FixedSizePool or call Destroy()
    before calling create.
  Returns:
    True if successful and the pool can be used.
  */
  bool Create(
    size_t sizeof_element,
    size_t element_count_estimate,
    size_t block_element_capacity
  );


  /*
  Description:
    Create a fixed size memory pool.
  Parameters:
    sizeof_element - [in]
      number of bytes in each element. This parameter must be greater than zero.
      In general, use sizeof(element type).  If you pass a "raw" number as
      sizeof_element, then be certain that it is the right size to insure the
      fields in your elements will be properly aligned.

    maximum_element_count_estimate - [in] (0 = good default)
      If you have a tight upper bound on the number of elements you need
      from this fixed size pool, call Create(sizeof_element) instead.

      If the description of this parameter is confusing to you,
      call Create(sizeof_element) instead.

      If you have a tight upper bound on how many elements you will need,
      pass that number here.  When maximum_element_count_estimate > 0, the 
      initial memory blocks in the fixed size pool will be sized to efficiently 
      deliver maximum_element_count_estimate elements.
      The fixed block pool can become inefficient when maximum_element_count_estimate
      is a gross overestimate or a slight underestimate of the actual number of 
      elements that get allocated.

    minimum_block2_element_capacity - [in] (0 = good default)
      If the description below is confusing, pass 0.
      If maximum_element_count_estimate = 0, this parameter is ignored.
      If maximum_element_count_estimate > 0 and you have an excellent choice 
      for a lower bound on the number of elements per block for unexpected allocations
      of more than maximum_element_count_estimate elements, then pass that value for 
      minimum_block2_element_capacity.

  Remarks:
    You must call Create() or CreateEx() on an unused ON_FixedSizePool or call Destroy()
    before calling create.
  Returns:
    True if successful and the pool can be used.
  */
  bool CreateForExperts(
    size_t sizeof_element,
    size_t maximum_element_count_estimate,
    size_t minimum_block2_element_capacity
  );

  static size_t DefaultElementCapacityFromSizeOfElement(size_t sizeof_element);

  /*
  Description:
    Tool for debugging pool use when tuning block size and block capacity.
  Returns:
    Total operating system heap memory (in bytes) used by this ON_FixedSizePool.
  Remarks:
    SizeOfPool() = SizeOfAllocatedElements() + SizeOfUnusedElements().
  */
  size_t SizeOfPool() const;

  /*
  Description:
    Tool for debugging pool use when tuning block size and block capacity.
  Returns:
    Operating system heap memory (in bytes) that are used by active pool elements.
  Remarks:
    SizeOfPool() = SizeOfActiveElements() + SizeOfUnusedElements().
  */
  size_t SizeOfActiveElements() const;

  /*
  Description:
    Tool for debugging pool use when tuning block size and block capacity.
  Returns:
    Operating system heap memory (in bytes) that has been reserved but is not 
    currently used by active elements.
  Remarks:
    SizeOfPool() = SizeOfActiveElements() + SizeOfUnusedElements().
  */
  size_t SizeOfUnusedElements() const;


  /*
  Returns:
    Size of the elements in this pool.
  */
  size_t SizeofElement() const;

  /*
  Returns:
    A pointer to sizeof_element bytes.  The memory is zeroed.
  Remarks:
    If multiple threads are using this pool, then use ThreadSafeAllocateElement().
  */
  void* AllocateElement();

  /*
  Returns:
    A pointer to sizeof_element bytes.  The values in the returned block are undefined.
  Remarks:
    If multiple threads are using this pool, then use ThreadSafeAllocateDirtyElement().
  */
  void* AllocateDirtyElement();

  /*
  Description:
    Return an element to the pool.
  Parameters:
    p - [in]
      A pointer returned by AllocateElement().
      It is critical that p be from this pool and that
      you return a pointer no more than one time.
  Remarks:
    If multiple threads are using this pool, then use ThreadSafeReturnElement().

    If you find the following remarks confusing, but you really want to use
    ReturnElement(), then here are some simple guidelines.
      1) SizeofElement() must be >= 16
      2) SizeofElement() must be a multiple of 8.
      3) Do not use FirstElement() and NextElement() to iterate through
         the pool.

    If 1 to 3 don't work for you, then you need to understand the following
    information before using ReturnElement().

    ON_FixedMemoryPool uses the first sizeof(void*) bytes of the
    returned element for bookkeeping purposes.  Therefore, if you
    are going to use ReturnElement(), then SizeofElement() must be 
    at least sizeof(void*).  If you are using a platform that requires
    pointers to be aligned on sizeof(void*) boundaries, then
    SizeofElement() must be a multiple of sizeof(void*).
    If you are going to use ReturnElement() and then use FirstElement()
    and NextElement() to iterate through the list of elements, then you
    need to set a value in the returned element to indicate that it
    needs to be skipped during the iteration.  This value cannot be
    located in the fist sizeof(void*) bytes of the element.  If the 
    element is a class with a vtable, you cannot call a virtual 
    function on a returned element because the vtable pointer is 
    trashed when ReturnElement() modifies the fist sizeof(void*) bytes.
  */
  void ReturnElement(void* p);

  /*
  Description:
    Thread safe version of AllocateElement().
  Returns:
    A pointer to sizeof_element bytes.  The memory is zeroed.
  */
  void* ThreadSafeAllocateElement();

  /*
  Description:
    Thread safe version of AllocateDirtyElement().
  Returns:
    A pointer to sizeof_element bytes.  The values in the returned block are undefined.
  */
  void* ThreadSafeAllocateDirtyElement();

  /*
  Description:
    Thread safe version of ReturnElement().
  */
  void ThreadSafeReturnElement(void* p);

  /*
  Description:
    Return all allocated elements to the pool. No heap is freed and
    the pool remains initialized and ready for AllocateElement()
    to be called.
  */
  void ReturnAll();

  /*
  Description:
    Destroy the pool and free all the heap. The pool cannot be used again
    until Create() is called.
  */
  void Destroy();

  /*
  Returns:
    Number of active elements. (Elements that have been returned are not active.)
  */
  size_t ActiveElementCount() const;

  /*
  Returns:
    Total number of elements = number of active elements + number of returned elements.
  */
  size_t TotalElementCount() const;

  /*
  Description:
    Get the i-th element in the fixed size pool.
  Parameters:
    element_index - [in]
  Returns:
    A pointer to the element with the specified index.  
    The first element has element_index = 0 and is the element
    returned by the first call to AllocateElement().
    The last element has element_index = ElementCount()-1.
    If element_index is out of range, nullptr is returned.
  Remarks:
    It is faster to use ON_FixedSizePoolIterator.FirstElement() and
    ON_FixedSizePoolIterator.NextElement() to iterate through the 
    entire list of elements.  This function is relatively
    efficient when there are a few large blocks in the pool
    or element_index is small compared to the number of elements
    in the first few blocks.

    If ReturnElement() is not used or no AllocateElement() calls
    are made after any use of ReturnElement(), then the i-th 
    element is the one returned by the (i+1)-th call to 
    AllocateElement()
  */
  void* Element(
    size_t element_index
    ) const;


  /*
  Description:
    Get the fixed size pool index of an element.
  Parameters:
    element_pointer - [in]
  Returns:
    An index >= 0 and < ON_MAX_SIZE_T if the element_pointer
    points to an element managed by the this fixed size pool.
    ON_MAX_SIZE_T otherwise.
  Remarks:
    It is faster to use ON_FixedSizePoolIterator.FirstElement() and
    ON_FixedSizePoolIterator.NextElement() to iterate through the 
    entire list of elements.  This function is relatively
    efficient when there are a few large blocks in the pool
    or element_pointer is an element in the first few blocks.

    If ReturnElement() is not used or no AllocateElement() calls
    are made after any use of ReturnElement(), then the i-th 
    element is the one returned by the (i+1)-th call to 
    AllocateElement().
  */
  size_t ElementIndex(
    const void* element_pointer
    ) const;

  /*
  Parameters:
    p - [in]
      pointer to test
  Returns:
    True if p points to memory in this pool.
  */
  bool InPool(
    const void* pointer
  ) const;

  /*
  Description:
    If you are certain that all elements in the pool (active and returned)
    have an unsigned 32-bit id that is unique and increasing, then you may use
    this function to find them.
  Parameters:
    id_offset - [in]
      offset into the element where the id is stored.
    id - [in]
      id to search for
  */
  void* ElementFromId(
    size_t id_offset,
    unsigned int id
    ) const;

  /*
  Description:
    If you are certain that all elements in the pool (active and returned)
    have an unsigned 32-bit id that is unique and increasing, then you may use
    this function to find the maximum assigned id.
  Parameters:
    id_offset - [in]
      offset into the element where the id is stored.
  Returns:
    maximum id in all elements (active and returned).
  */
  unsigned int MaximumElementId(
    size_t id_offset
    ) const;

  bool ElementIdIsIncreasing(
    size_t id_offset
    ) const;

  /*
  Returns:
    If successful, (1 + maximum assigned id value) is returned.
    Otherwise 0 is returned.
  */
  unsigned int ResetElementId(
    size_t id_offset,
    unsigned int initial_id
    );

public:
  // Primarily used for debugging
  bool IsValid() const;

private:
  friend class ON_FixedSizePoolIterator;

  void* m_first_block = nullptr;

  // ReturnElement() adds to the m_al_element stack.
  // AllocateElement() will use the stack before using m_al_element_array[]
  void* m_al_element_stack = nullptr;

  void* m_al_block = nullptr; // current element allocation block.
  // m_al_element_array[] is in m_al_block and has length m_al_count.
  void* m_al_element_array = nullptr;
  size_t m_al_count = 0;
  size_t m_sizeof_element = 0;
  size_t m_block_element_count = 0;  // block element count

  //size_t m_active_element_count = 0; // number of active elements
  //size_t m_total_element_count = 0;  // total number of elements (active + returned)

  unsigned int m_active_element_count = 0; // number of active elements
  unsigned int m_total_element_count = 0;  // total number of elements (active + returned)

private:
  // Used by The ThreadSafe...() functions and for expert users 
  // to use when managing memory controlled by this pool. Best
  // to ignore this unless you have a very clear idea of what
  // you are doing, why you are doing it, and when you are doing it.
  // Otherwise, you'll find yourself waiting forever on a nested
  // access request. 
  friend class ON_SleepLockGuard;
  ON_SleepLock m_sleep_lock;

private:
  unsigned int m_reserved0 = 0;

  
private:
  // returns capacity of elements in existing block
  size_t BlockElementCapacity( const void* block ) const;

  // returns number of allocated of elements in existing block
  size_t BlockElementCount( const void* block ) const;

private:
  // prohibit copy construction and operator=.
  ON_FixedSizePool(const ON_FixedSizePool&) = delete;
  ON_FixedSizePool& operator=(const ON_FixedSizePool&) = delete;
};

class ON_CLASS ON_FixedSizePoolIterator
{
public:
  ON_FixedSizePoolIterator();
  ON_FixedSizePoolIterator( const class ON_FixedSizePool& fsp );

  const class ON_FixedSizePool* FixedSizePool();

  void Create(const ON_FixedSizePool* fsp);

  /*
  Description:
    Get the first element when iterating through the list of elements.
  Parameters:
    element_index - [in]
      If you use the version of FirstElement() that has an 
      element_index parameter, then the iteration begins at
      that element.
  Example:
    The loop will iterate through all the elements returned from
    AllocateElement(), including any that have be returned to the pool
    using ReturnElement().

          // iterate through all elements in the pool
          // This iteration will go through TotalElements() items.
          for ( void* p = FirstElement(); 0 != p; p = NextElement() )
          {
            // If you are not using ReturnElement(), then you may process
            // "p" immediately. If you have used ReturnElement(), then you
            // must check some value in p located after the first sizeof(void*)
            // bytes to see if p is active.
            if ( p is not active )
              continue;

            ... process p
          }

  Returns:
    The first element when iterating through the list of elements.
  Remarks:
    FirstElement() and NextElement() will return elements that have 
    been returned to the pool using ReturnElement().  If you use 
    ReturnElement(), then be sure to mark the element so it can be
    identified and skipped.

    Do not make any calls to FirstBlock() or NextBlock() when using
    FirstElement() and NextElement() to iterate through elements.
  */
  void* FirstElement();
  void* FirstElement( size_t element_index );

  /*
  Description:
    Get the next element when iterating through the list of elements.
    If FirstElement() is not called, then the first call to
    NextElement() returns the first element.
  Example:
    See the FirstElement() documentation.
  Returns:
    The next element when iterating through the list of elements.
  Remarks:
    FirstElement() and NextElement() will return elements that have 
    been returned to the pool using ReturnElement().  If you use 
    ReturnElement(), then be sure to mark the element so it can be
    identified and skipped.

    Do not make any calls to FirstBlock() or NextBlock() when using
    FirstElement() and NextElement() to iterate through elements.
  */
  void* NextElement();

  /*
  Returns:
    The most recently returned value from a call to FirstElement()
    or NextElement().
  Remarks:
    Do not make any calls to FirstBlock() or NextBlock() when using
    FirstElement() and NextElement() to iterate through elements.
  */
  void* CurrentElement() const;

  /*
  Description:
    Sets the state of the iterator to the initial state that
    exists after construction.  This is useful if the iterator
    has been used the get one or more elements and then
    the referenced fixed size pool is modified or code wants
    to begin iteration again a used a call to NextElement()
    to return the first element.
  */
  void Reset();


  /*
  Description:
    Get a pointer to the first element in the first block.
  Parameters:
    block_element_count - [out] (can be null)
      If not null, the number of elements allocated from the
      first block is returned in block_element_count.
      Note that if you have used ReturnElement(), some
      of these elements may have been returned.
  Example:
    The loop will iterate through all the blocks.

          // iterate through all blocks in the pool
          size_t block_element_count = 0;
          for ( void* p = FirstBlock(&block_element_count); 
                0 != p; 
                p = NextBlock(&block_element_count) 
              )
          {
            ElementType* e = (ElementType*)p;
            for ( size_t i = 0; 
                  i < block_element_count; 
                  i++, e = ((const char*)e) + SizeofElement() 
                )
            {
              ...
            }
          }

  Returns:
    The first block when iterating the list of blocks.
  Remarks:
    The heap for a fixed size memory pool is simply a linked
    list of blocks. FirstBlock() and NextBlock() can be used
    to iterate through the list of blocks.

    Do not make any calls to FirstElement() or NextElement() when using
    FirstBlock() and NextBlock() to iterate through blocks.
  */
  void* FirstBlock( size_t* block_element_count );

  /*
  Description:
    Get the next block when iterating through the blocks.
  Parameters:
    block_element_count - [out] (can be null)
      If not null, the number of elements allocated from the
      block is returned in block_element_count.  Note that if
      you have used ReturnElement(), some of these elements
      may have been returned.
  Example:
    See the FirstBlock() documentation.
  Returns:
    The next block when iterating through the blocks.
  Remarks:
    Do not make any calls to FirstElement() or NextElement() when using
    FirstBlock() and NextBlock() to iterate through blocks.
  */
  void* NextBlock( size_t* block_element_count );

private:
  const class ON_FixedSizePool* m_fsp;
  void* m_it_block;
  void* m_it_element;
};


template <class T> class ON_SimpleFixedSizePool : private ON_FixedSizePool
{
public:
  // construction ////////////////////////////////////////////////////////

  ON_SimpleFixedSizePool();
  ~ON_SimpleFixedSizePool();
  
  /*
  Description:
    Create a fixed size memory pool.
  Parameters:
    element_count_estimate - [in] (0 = good default)
      If you know how many elements you will need, pass that number here.
      It is better to slightly overestimate than to slightly underestimate.
      If you do not have a good estimate, then use zero.
    block_element_count - [in] (0 = good default)
      If block_element_count is zero, Create() will calculate a block
      size that is efficient for most applications.  If you are an expert
      user and want to specify the number of blocks, then pass the number
      of elements per block here.  When block_element_count > 0 and
      element_count_estimate > 0, the first block will be large enough
      element_count_estimate*sizeof(T) bytes; in this case do not
      ask for extraordinarily large amounts of contiguous heap.
  Remarks:
    You must call Create() on an unused ON_FixedSizePool or call Destroy()
    before calling create.
  Returns:
    True if successful and the pool can be used.
  */
  bool Create( 
    size_t element_count_estimate,
    size_t block_element_count
    );

  /*
  Returns:
    Size of the elements in this pool.
  */
  size_t SizeofElement() const;

  /*
  Returns:
    A pointer to sizeof_element bytes.  The memory is zeroed.
  */
  T* AllocateElement();
  
  /*
  Description:
    Return an element to the pool.
  Parameters:
    p - [in]
      A pointer returned by AllocateElement().
      It is critical that p be from this pool and that
      you return a pointer no more than one time.
  Remarks:
    If you find the following remarks confusing, but you really want to use
    ReturnElement(), then here are some simple guidelines.
      1) SizeofElement() must be >= 16
      2) SizeofElement() must be a multiple of 8.
      3) Do not use FirstElement() and NextElement() to iterate through
         the pool.

    If 1 to 3 don't work for you, then you need to understand the following
    information before using ReturnElement().

    ON_FixedMemoryPool uses the first sizeof(void*) bytes of the
    returned element for bookkeeping purposes.  Therefore, if you
    are going to use ReturnElement(), then SizeofElement() must be 
    at least sizeof(void*).  If you are using a platform that requires
    pointers to be aligned on sizeof(void*) boundaries, then
    SizeofElement() must be a multiple of sizeof(void*).
    If you are going to use ReturnElement() and then use FirstElement()
    and NextElement() to iterate through the list of elements, then you
    need to set a value in the returned element to indicate that it
    needs to be skipped during the iteration.  This value cannot be
    located in the fist sizeof(void*) bytes of the element.  If the 
    element is a class with a vtable, you cannot call a virtual 
    function on a returned element because the vtable pointer is 
    trashed when ReturnElement() modifies the fist sizeof(void*) bytes.
  */
  void ReturnElement(T* p);

  /*
  Description:
    Return all allocated elements to the pool. No heap is freed and
    the pool remains initialized and ready for AllocateElement()
    to be called.
  */
  void ReturnAll();

  /*
  Description:
    Destroy the pool and free all the heap. The pool cannot be used again
    until Create() is called.
  */
  void Destroy();

  /*
  Returns:
    Number of active elements. (Elements that have been returned are not active.)
  */
  size_t ActiveElementCount() const;

  /*
  Returns:
    Total number of elements = number of active elements + number of returned elements.
  */
  size_t TotalElementCount() const;

  /*
  Description:
    Get the i-th element in the pool.
  Parameters:
    element_index - [in]
  Returns:
    A pointer to the i-th element.  The first element has index = 0
    and is the element returned by the first call to AllocateElement().
    The last element has index = ElementCount()-1.
    If i is out of range, null is returned.
  Remarks:
    It is faster to use FirstElement() and NextElement() to iterate
    through the entire list of elements.  This function is relatively
    efficient when there are a few large blocks in the pool
    or element_index is small compared to the number of elements
    in the first few blocks.

    If ReturnElement() is not used or AllocateElement() calls to
    are made after any use of ReturnElement(), then the i-th 
    element is the one returned by the (i+1)-th call to 
    AllocateElement().
  */
  T* Element(size_t element_index) const;

  size_t ElementIndex(
    T*
    ) const;

private:
  // prohibit copy construction and operator=.
  ON_SimpleFixedSizePool(const ON_SimpleFixedSizePool<T>&);
  ON_SimpleFixedSizePool<T>& operator=(const ON_SimpleFixedSizePool<T>&);
};

template <class T> class ON_SimpleFixedSizePoolIterator : private ON_FixedSizePoolIterator
{
public:
  ON_SimpleFixedSizePoolIterator( const class ON_SimpleFixedSizePool<T>& fsp );
  ON_SimpleFixedSizePoolIterator(const class ON_SimpleFixedSizePoolIterator<T>&);

  /*
  Description:
    Get the first element when iterating through the list of elements.
  Parameters:
    element_index - [in]
      If you use the version of FirstElement() that has an 
      element_index parameter, then the iteration begins at
      that element.
  Example:
    The loop will iterate through all the elements returned from
    AllocateElement(), including any that have be returned to the pool
    using ReturnElement().

          // iterate through all elements in the pool
          // This iteration will go through TotalElements() items.
          for ( void* p = FirstElement(); 0 != p; p = NextElement() )
          {
            // If you are not using ReturnElement(), then you may process
            // "p" immediately. If you have used ReturnElement(), then you
            // must check some value in p located after the first sizeof(void*)
            // bytes to see if p is active.
            if ( p is not active )
              continue;

            ... process p
          }

  Returns:
    The first element when iterating through the list of elements.
  Remarks:
    FirstElement() and NextElement() will return elements that have 
    been returned to the pool using ReturnElement().  If you use 
    ReturnElement(), then be sure to mark the element so it can be
    identified and skipped.

    Do not make any calls to FirstBlock() or NextBlock() when using
    FirstElement() and NextElement() to iterate through elements.
  */
  T* FirstElement();
  T* FirstElement( size_t element_index );

  /*
  Description:
    Get the next element when iterating through the list of elements.
    If FirstElement() is not called, then the first call to
    NextElement() returns the first element.
  Example:
    See the FirstElement() documentation.
  Returns:
    The next element when iterating through the list of elements.
  Remarks:
    FirstElement() and NextElement() will return elements that have 
    been returned to the pool using ReturnElement().  If you use 
    ReturnElement(), then be sure to mark the element so it can be
    identified and skipped.

    Do not make any calls to FirstBlock() or NextBlock() when using
    FirstElement() and NextElement() to iterate through elements.
  */
  T* NextElement();

  /*
  Returns:
    The most recently returned value from a call to FirstElement()
    or NextElement().
  Remarks:
    Do not make any calls to FirstBlock() or NextBlock() when using
    FirstElement() and NextElement() to iterate through elements.
  */
  T* CurrentElement();

  /*
  Description:
    Sets the state of the iterator to the initial state that
    exists after construction.  This is useful if the iterator
    has been used the get one or more elements and then
    the referenced fixed size pool is modified or code wants
    to begin iteration again a used a call to NextElement()
    to return the first element.
  */
  void Reset();


  /*
  Description:
    Get a pointer to the first element in the first block.
  Parameters:
    block_element_count - [out] (can be null)
      If not null, the number of elements allocated from the
      first block is returned in block_element_count.
      Note that if you have used ReturnElement(), some
      of these elements may have been returned.
  Example:
    The loop will iterate through all the blocks.

          // iterate through all blocks in the pool
          size_t block_element_count = 0;
          for ( void* p = FirstBlock(&block_element_count); 
                0 != p; 
                p = NextBlock(&block_element_count) 
              )
          {
            ElementType* e = (ElementType*)p;
            for ( size_t i = 0; 
                  i < block_element_count; 
                  i++, e = ((const char*)e) + SizeofElement() 
                )
            {
              ...
            }
          }

  Returns:
    The first block when iterating the list of blocks.
  Remarks:
    The heap for a fixed size memory pool is simply a linked
    list of blocks. FirstBlock() and NextBlock() can be used
    to iterate through the list of blocks.

    Do not make any calls to FirstElement() or NextElement() when using
    FirstBlock() and NextBlock() to iterate through blocks.
  */
  T* FirstBlock( size_t* block_element_count );

  /*
  Description:
    Get the next block when iterating through the blocks.
  Parameters:
    block_element_count - [out] (can be null)
      If not null, the number of elements allocated from the
      block is returned in block_element_count.  Note that if
      you have used ReturnElement(), some of these elements
      may have been returned.
  Example:
    See the FirstBlock() documentation.
  Returns:
    The next block when iterating through the blocks.
  Remarks:
    Do not make any calls to FirstElement() or NextElement() when using
    FirstBlock() and NextBlock() to iterate through blocks.
  */
  T* NextBlock( size_t* block_element_count );

private:
  // no implementation (you can use a copy constructor)
  class ON_SimpleFixedSizePoolIterator<T>& operator=(const class ON_SimpleFixedSizePoolIterator<T>&);
};

// definitions of the template functions are in a different file
// so that Microsoft's developer studio's autocomplete utility
// will work on the template functions.
#include "opennurbs_fsp_defs.h"

#endif

