#include "opennurbs.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

ON_FixedSizePool::ON_FixedSizePool()
{
  ////const size_t sz = sizeof(*this);
  ////ON_TextLog::Null.Print("L%d", sz); // suppress compile errors.
  // sz = 72 bytes before step 2 fixes for https://mcneel.myjetbrains.com/youtrack/issue/RH-49375
  //
  // private data members will be rearranged but the size cannot change so that the
  // C++ public SDK remains stable.
  //

  memset(this,0,sizeof(*this));
}

ON_FixedSizePool::~ON_FixedSizePool()
{
  Destroy();
}

#if defined(ON_HAS_RVALUEREF)

ON_FixedSizePool::ON_FixedSizePool(ON_FixedSizePool&& src)
  : m_first_block(src.m_first_block)
  , m_al_element_stack(src.m_al_element_stack)
  , m_al_block(src.m_al_block)
  , m_al_element_array(src.m_al_element_array)
  , m_al_count(src.m_al_count)
  , m_sizeof_element(src.m_sizeof_element)
  , m_block_element_count(src.m_block_element_count)
  , m_active_element_count(src.m_active_element_count)
  , m_total_element_count(src.m_total_element_count)
{
  memset(&src,0,sizeof(*this));
}

ON_FixedSizePool& ON_FixedSizePool::operator=(ON_FixedSizePool&& src)
{
  if (this != &src)
  {
    Destroy();
    m_first_block = src.m_first_block;
    m_al_element_stack = src.m_al_element_stack;
    m_al_block = src.m_al_block;
    m_al_element_array = src.m_al_element_array;
    m_al_count = src.m_al_count;
    m_sizeof_element = src.m_sizeof_element;
    m_block_element_count = src.m_block_element_count;
    m_active_element_count = src.m_active_element_count;
    m_total_element_count = src.m_total_element_count;
    memset(&src,0,sizeof(*this));
  }
  return *this;
}

#endif


size_t ON_FixedSizePool::SizeofElement() const
{
  return m_sizeof_element;
}

size_t ON_FixedSizePool::SizeOfPool() const
{
  size_t element_count = 0;
  void* next = m_first_block;
  for (void* blk = next; nullptr != blk; blk = next)
  {
    next = *((void**)blk);
    element_count += BlockElementCapacity(blk);
  }
  return element_count * m_sizeof_element;
}

size_t ON_FixedSizePool::SizeOfUnusedElements() const
{
  return SizeOfPool() - SizeOfActiveElements();
}

size_t ON_FixedSizePool::SizeOfActiveElements() const
{
  return m_sizeof_element * ((size_t)m_active_element_count);
}


size_t ON_FixedSizePool::DefaultElementCapacityFromSizeOfElement(size_t sizeof_element)
{
  size_t block_element_capacity = 0;
  if (sizeof_element <= 0)
  {
    ON_ERROR("sizeof_element must be > 0");
    return 0;
  }

  size_t page_size = ON_MemoryPageSize();
  if (page_size < 512)
    page_size = 512;

  // The "overhead" is for the 2*sizeof(void*) ON_FixedSizePool uses at
  // the start of each block + 32 bytes extra for the heap manager
  // to keep the total allocation not exceeding multiple of page_size.
  const size_t overhead = 2 * sizeof(void*) + 32;

  size_t page_count = 1;
  block_element_capacity = (page_count * page_size - overhead) / sizeof_element;
  while (block_element_capacity < 1000)
  {
    page_count *= 2;
    block_element_capacity = (page_count * page_size - overhead) / sizeof_element;
    if (page_count > 8 && block_element_capacity > 64)
    {
      // for pools with large elements
      break;
    }
  }

  return block_element_capacity;
}

bool ON_FixedSizePool::Create(
  size_t sizeof_element
)
{
  return ON_FixedSizePool::CreateForExperts(sizeof_element, 0, 0);
}

bool ON_FixedSizePool::Create(
        size_t sizeof_element,
        size_t element_count_estimate,
        size_t block_element_capacity
        )
{
  if ( sizeof_element <= 0 )
  {
    ON_ERROR( "ON_FixedSizePool::Create - sizeof_element <= 0" );
    return false;
  }

  if ( m_sizeof_element != 0 || 0 != m_first_block )
  {
    ON_ERROR( "ON_FixedSizePool::Create - called on a pool that is in use." );
    return false;
  }

  memset(this,0,sizeof(*this));

  m_sizeof_element = sizeof_element;

  if ( block_element_capacity <= 0 )
    block_element_capacity = ON_FixedSizePool::DefaultElementCapacityFromSizeOfElement(m_sizeof_element);

  // capacity for the the 2nd and subsequent blocks
  m_block_element_count = block_element_capacity;

  // Set m_al_count = capacity of the first block.

  // If the estimated number of elements is not too big, then make the 1st block that size.
  if ( element_count_estimate > 0 )
  {
    if (element_count_estimate <= 8*m_block_element_count )
      m_al_count = element_count_estimate; // 1st block will have room for element_count_estimate elements
    else
      m_al_count = 8*m_block_element_count; // 1st block will be 8xlarger than subsequent blocks, but not as huge as requested
  }
  else
  {
    // 1st block is the same size as subsequent blocks
    m_al_count = m_block_element_count;
  }

  return true;
}

bool ON_FixedSizePool::CreateForExperts(
  size_t sizeof_element,
  size_t maximum_element_count_estimate,
  size_t minimum_block2_element_capacity
)
{
  if (m_sizeof_element != 0 || 0 != m_first_block)
  {
    ON_ERROR("ON_FixedSizePool::Create - called on a pool that is in use.");
    return false;
  }

  memset(this, 0, sizeof(*this));

  if (sizeof_element <= 0)
  {
    ON_ERROR("Invalid parameter: sizeof_element <= 0.");
    return false;
  }

  const size_t default_block_capacity = ON_FixedSizePool::DefaultElementCapacityFromSizeOfElement(sizeof_element);
  if (default_block_capacity <= 0 || default_block_capacity* sizeof_element <= 0)
  {
    ON_ERROR("Invalid parameter: sizeof_element is too large for a fixed size pool.");
    return false;
  }

  if (maximum_element_count_estimate < 0)
  {
    ON_ERROR("Invalid parameter: block1_element_count < 0.");
    return false;
  }

  if (0 == maximum_element_count_estimate)
    minimum_block2_element_capacity = 0;
  else if (minimum_block2_element_capacity < 0)
  {
    ON_ERROR("Invalid parameter: minimum_block2_element_capacity < 0.");
    return false;
  }


  size_t block1_capacity = 0; // 1st block will have room for m_al_count elements.
  size_t block2_capacity = 0; // 2nd and subsequent blocks will have room m_block_element_count elements.

  if (maximum_element_count_estimate > 0)
  {
    if (maximum_element_count_estimate <= 4 * default_block_capacity)
    {
      // We should be able to reliably allocate a contiguous memory space
      // that will hold maximum_element_count_estimate elements.
      block1_capacity = maximum_element_count_estimate;

      // The caller claims that maximum_element_count_estimate is a tight upper bound
      // on the number of elements to be allocated.
      // If they underestimated, keep subsequent blocks small assuming that they
      // underestimated by only a little bit.
      block2_capacity = (block1_capacity + 9) / 10;
      if (block2_capacity <= 0)
        block2_capacity = 1;
      if (block2_capacity < minimum_block2_element_capacity)
        block2_capacity = minimum_block2_element_capacity;
    }
    else
    {
      // The value maximum_element_count_estimate is too big for 
      // a reasonably sized chuck of contiguous memory space.
      //
      // Find a way to allocate maximum_element_count_estimate elements from
      // multiple blocks and not waste a bunch of memory when 
      // maximum_element_count_estimate is tight upper bound on the 
      // number of element that will actually be allocated.
      //
      // minimum_block2_element_capacity is intentionally being ignored
      // in this case.
      size_t n = maximum_element_count_estimate / default_block_capacity;
      if (n > 0)
      {
        // We will use n blocks of block1_capacity elements to deliver
        // maximum_element_count_estimate elements. These
        // blocks will be reasonably sized and easy to allocate.
        block1_capacity = maximum_element_count_estimate / n;
        if (n * block1_capacity < maximum_element_count_estimate)
          ++block1_capacity;
        block2_capacity = block1_capacity;
      }
    }
  }

  //////////////////////////////
  // Initialize this pool

  m_sizeof_element = sizeof_element;

  // 1st block will have room for m_al_count elements.
  m_al_count = block1_capacity > 0 ? block1_capacity : default_block_capacity; 

  // 2nd and subsequent blocks will have room m_block_element_count elements.
  m_block_element_count = block2_capacity > 0 ? block2_capacity : default_block_capacity; 

  return true;
}

void ON_FixedSizePool::ReturnAll()
{
  if ( 0 != m_first_block )
  {
    // initialize
    m_al_element_stack = 0;
    //////m_qwerty_it_block = 0;
    //////m_qwerty_it_element = 0;
    m_al_block = m_first_block;
    m_al_element_array = (void*)(((char*)m_al_block) + 2*sizeof(void*));
    m_al_count = BlockElementCapacity(m_first_block);
    m_active_element_count = 0;
    m_total_element_count = 0;
  }
}

void ON_FixedSizePool::Destroy()
{
  void* p;
  void* next;
  next = m_first_block;
  memset(this,0,sizeof(*this));
  for ( p = next; 0 != p; p = next )
  {
    next = *((void**)p);
    onfree(p);
  }
}

size_t ON_FixedSizePool::ActiveElementCount() const
{
  return m_active_element_count;
}

size_t ON_FixedSizePool::TotalElementCount() const
{
  return m_total_element_count;
}

void* ON_FixedSizePool::AllocateDirtyElement()
{
  void* p;

  if ( 0 != m_al_element_stack )
  {
    // use item on the returned stack first.
    p = m_al_element_stack;
    m_al_element_stack = *((void**)m_al_element_stack);
  }
  else
  {
    if ( 0 == m_al_block || 0 == m_al_count )
    {
      // No more memory left in m_al_block.
      void* next_block = (0 != m_al_block)
                       ? *((void**)m_al_block)
                       : 0;
      if ( 0 == next_block )
      {
        // This if clause is used when we need to allocate a new block from the heap
        if ( 0 == m_sizeof_element )
        {
          ON_ERROR("ON_FixedSizePool::AllocateElement - you must call ON_FixedSizePool::Create with a valid element size before using ON_FixedSizePool");
          return nullptr;
        }
        // allocate a new block
        if ( 0 == m_al_count )
          m_al_count = m_block_element_count;

        if ( m_al_count <= 0 )
        {
          ON_ERROR("ON_FixedSizePool::AllocateElement - you must call ON_FixedSizePool::Create with a valid element size before using ON_FixedSizePool");
          return nullptr;
        }

        p = onmalloc( 2*sizeof(void*) + m_al_count*m_sizeof_element ); // get some heap

        // set "next" pointer to zero
        *((void**)p) = nullptr;

        // set "end" pointer to address after last byte in the block
        *((void**)(((char*)p) + sizeof(void*))) = ((char*)p) + (2*sizeof(void*) + m_al_count*m_sizeof_element);
        if ( 0 == m_first_block )
        {
          m_first_block = p;
          // If the call to Create() specified a positive element_count_estimate,
          // then m_sizeof_block needs to be reset for any future block allocations.

        }
        else
        {
          // If m_first_block != 0, then m_al_block is nonzero (or memory for this class has been trashed)
          *((void**)m_al_block) = p;
        }
        m_al_block = p;
      }
      else
      {
        // If we get here, ReturnAll() was used at some point in
        // the past, m_al_block != 0, m_al_count = zero, and we are
        // reusing blocks that were allocated early.
        m_al_block = next_block;
        m_al_count = BlockElementCapacity(m_al_block);
      }

      m_al_element_array = (void*)(((char*)m_al_block)+2*sizeof(void*));
    }
    m_al_count--;
    p = m_al_element_array;
    m_al_element_array = (void*)(((char*)m_al_element_array) + m_sizeof_element);
    m_total_element_count++;
  }

  m_active_element_count++;

  return p;
}

bool ON_FixedSizePool::IsValid() const
{
  if (nullptr != m_first_block)
  {
    const char* block;
    const char* block_end;
    const char* next_block;
    size_t sizeof_block_allocated;
    size_t sizeof_block_total;
    size_t block_element_capacity;
    size_t block_element_count; // allocated element count
    size_t count, capacity;

    size_t total_element_count = 0;

    bool bSkipCcountCheck = false;

    for (block = (const char*)m_first_block; 0 != block; block = next_block)
    {
      const bool bBlockIsAlBlock = (block == m_al_block);

      capacity = BlockElementCapacity(block);
      count
        = bSkipCcountCheck
        ? 0xFFFFFFFF :
        BlockElementCount(block);

      // validate capacity
      next_block = *((const char**)block);
      block += sizeof(void*);
      block_end = *((const char**)(block));
      block += sizeof(void*);
      sizeof_block_total = (block_end - block);

      block_element_capacity = sizeof_block_total / m_sizeof_element;
      if (sizeof_block_total != block_element_capacity * m_sizeof_element)
      {
        ON_ERROR("sizeof_block is not a multiple of m_sizeof_element");
        return false;
      }

      if (capacity != block_element_capacity)
      {
        ON_ERROR("ON_FixedSizePool::BlockElementCapacity error.");
        return false;
      }

      if ( bSkipCcountCheck )
        continue;

      bSkipCcountCheck = bBlockIsAlBlock;

      // Validate allocated count

      if (bBlockIsAlBlock)
      {
        sizeof_block_allocated = (((const char*)m_al_element_array) - block);
        block_element_count = sizeof_block_allocated / m_sizeof_element;
        if (sizeof_block_allocated != block_element_count * m_sizeof_element)
        {
          ON_ERROR("sizeof_block_allocated is not a multiple of m_sizeof_element");
          return false;
        }
        if ( block_element_count > block_element_capacity )
        {
          ON_ERROR("block_element_count > block_element_capacity");
          return false;
        }
        if ( block_element_count + m_al_count != block_element_capacity)
        {
          ON_ERROR("block_element_count + m_al_count != block_element_capacity");
          return false;
        }
      }
      else
      {
        sizeof_block_allocated = sizeof_block_total;
        block_element_count = block_element_capacity;
      }

      total_element_count += block_element_count;
      if (total_element_count > (size_t)m_total_element_count)
      {
        ON_ERROR("m_total_element_count is not correct or some other serious problem.");
        return false;
      }

      if (count != block_element_count)
      {
        ON_ERROR("ON_FixedSizePool::BlockElementCount error.");
        return false;
      }
    }

    if (total_element_count != (size_t)m_total_element_count)
    {
      ON_ERROR("m_total_element_count or m_al_element_array is not correct or some other serious problem.");
      return false;
    }
  }

  if ( m_active_element_count > m_total_element_count )
  {
    ON_ERROR("m_active_element_count > m_total_element_count");
    return false;
  }

  return true;
}

void* ON_FixedSizePool::AllocateElement()
{
  void* p = AllocateDirtyElement();
  if (nullptr != p)
    memset(p, 0, m_sizeof_element);
  return p;
}

void ON_FixedSizePool::ReturnElement(void* p)
{
  if ( p )
  {
    if ( m_active_element_count <= 0 )
    {
      // If you get this error, something is seriously wrong.
      // You may be returning the same element multiple times or
      // you may be returning pointers that are not from this pool.
      // In any case, you're probably going to be crashing sometime soon.
      ON_ERROR("ON_FixedSizePool::ReturnElement - no active elements exist.");
    }
    else
    {
      m_active_element_count--;
      *((void**)p) = m_al_element_stack;
      m_al_element_stack = p;
    }
  }
}

void* ON_FixedSizePool::ThreadSafeAllocateDirtyElement()
{
  void* p = nullptr;
  {
    if ( m_sleep_lock.GetLock() )
    {
      p = AllocateDirtyElement();
      m_sleep_lock.ReturnLock();
    }
  }
  return p;
}

void* ON_FixedSizePool::ThreadSafeAllocateElement()
{
  void* p = nullptr;
  {
    if ( m_sleep_lock.GetLock() )
    {
      p = AllocateElement();
      m_sleep_lock.ReturnLock();
    }
  }
  return p;
}

void ON_FixedSizePool::ThreadSafeReturnElement(void* p)
{
  if (nullptr != p)
  {
    if ( m_sleep_lock.GetLock() )
    {
      ReturnElement(p);
      m_sleep_lock.ReturnLock();
    }
  }
}

ON_FixedSizePoolIterator::ON_FixedSizePoolIterator()
  : m_fsp(0)
  , m_it_block(0)
  , m_it_element(0)
{}

ON_FixedSizePoolIterator::ON_FixedSizePoolIterator( const ON_FixedSizePool& fsp )
  : m_fsp(&fsp)
  , m_it_block(0)
  , m_it_element(0)
{}

const class ON_FixedSizePool* ON_FixedSizePoolIterator::FixedSizePool()
{
  return m_fsp;
}

void ON_FixedSizePoolIterator::Create(const ON_FixedSizePool* fsp)
{
  m_fsp = fsp;
  m_it_block = 0;
  m_it_element = 0;
}


void ON_FixedSizePoolIterator::Reset()
{
  m_it_block = 0;
  m_it_element = 0;
}

void* ON_FixedSizePoolIterator::FirstElement()
{
  if ( m_fsp && m_fsp->m_first_block && m_fsp->m_total_element_count > 0 )
  {
    m_it_block = m_fsp->m_first_block;
    m_it_element = (void*)(((char*)m_it_block)+2*sizeof(void*)); // m_it_element points to first element in m_first_block
  }
  else
  {
    m_it_block = 0;
    m_it_element = 0;
  }
  return m_it_element;
}

void* ON_FixedSizePoolIterator::NextElement()
{
  if ( m_it_element )
  {
    m_it_element = (void*)(((char*)m_it_element) + m_fsp->m_sizeof_element);
    if ( m_it_element == m_fsp->m_al_element_array )
    {
      m_it_block = (void*)1; // must be non-zero
      m_it_element = 0; // terminates iteration
    }
    else if ( m_it_element == *((void**)(((char*)m_it_block) + sizeof(void*))) )
    {
      // m_it_element  = "end" pointer which means we are at the end of m_it_block
      m_it_block = *((void**)m_it_block); // m_it_block = "next" block
      m_it_element = (0 != m_it_block)    // m_it_element points to first element in m_it_block
                   ? (void*)(((char*)m_it_block)+2*sizeof(void*))
                   : 0;
      if ( m_it_element == m_fsp->m_al_element_array )
      {
        // terminate iteration (
        m_it_block = (void*)1; // must be non-zero
        m_it_element = 0; // terminates iteration
      }
    }
  }
  else if ( 0 == m_it_block )
  {
    // Start at the beginning.
    FirstElement();
  }
  return m_it_element;
}

void* ON_FixedSizePoolIterator::CurrentElement() const
{
  return m_it_element;
}

void* ON_FixedSizePoolIterator::FirstElement(size_t element_index)
{
  const char* block;
  const char* block_end;
  const char* next_block;
  size_t block_count;

  m_it_block = 0;
  m_it_element = 0;
  if ( m_fsp && element_index < (size_t)(m_fsp->m_total_element_count) )
  {
    for ( block = (const char*)m_fsp->m_first_block; 0 != block; block = next_block )
    {
      if ( block == m_fsp->m_al_block )
      {
        next_block = 0;
        block_end = (const char*)m_fsp->m_al_element_array;
      }
      else
      {
        next_block = *((const char**)block);
        block_end =  *((const char**)(block + sizeof(void*)));
      }
      block_count = (block_end - block)/m_fsp->m_sizeof_element;
      if ( element_index < block_count )
      {
        m_it_block = (void*)block;
        m_it_element = ((void*)(block + (2*sizeof(void*) + element_index*m_fsp->m_sizeof_element)));
        break;
      }
      element_index -= block_count;
    }
  }
  return m_it_element;
}

size_t ON_FixedSizePool::BlockElementCapacity( const void* block ) const
{
  // returns number of items that can be allocated from block
  if ( 0 == block || m_sizeof_element <= 0 )
    return 0;

  const char* block_end = *((const char**)(((const char*)block)+sizeof(void*)));
  const char* block_head = (((const char*)block) + 2*sizeof(void*));
  return (block_end - block_head)/m_sizeof_element;
}

size_t ON_FixedSizePool::BlockElementCount( const void* block ) const
{
  // returns number of items currently allocated from block
  if ( 0 == block || m_sizeof_element <= 0 )
    return 0;

  const char* block_end
    = (block == m_al_block && m_al_count > 0)
    ? ((const char*)m_al_element_array)
    : *((const char**)(((const char*)block)+sizeof(void*)));

  const char* block_head = (((const char*)block) + 2*sizeof(void*));

  return (block_end - block_head)/m_sizeof_element;
}

void* ON_FixedSizePoolIterator::FirstBlock( size_t* block_element_count )
{
  if ( m_fsp && m_fsp->m_first_block && m_fsp->m_total_element_count > 0 )
  {
    m_it_block = m_fsp->m_first_block;
    m_it_element = (void*)(((char*)m_it_block)+2*sizeof(void*)); // m_it_element points to first element in m_first_block
    if ( 0 != block_element_count )
      *block_element_count = m_fsp->BlockElementCount(m_it_block);
  }
  else
  {
    m_it_block = 0;
    m_it_element = 0;
    if ( 0 != block_element_count )
      *block_element_count = 0;
  }
  return m_it_element;
}

void* ON_FixedSizePoolIterator::NextBlock( size_t* block_element_count )
{
  if ( 0 != m_it_block
       && m_it_block != m_fsp->m_al_block
       && m_it_element == (void*)(((char*)m_it_block)+2*sizeof(void*)) )
  {
    m_it_block = *((void**)m_it_block);
    if ( m_it_block == m_fsp->m_al_element_array )
    {
      m_it_block = 0;
      m_it_element = 0;
      if ( 0 != block_element_count )
        *block_element_count = 0;
    }
    else
    {
      m_it_element = (void*)(((char*)m_it_block)+2*sizeof(void*)); // m_it_element points to first element in m_first_block
      if ( 0 != block_element_count )
        *block_element_count = m_fsp->BlockElementCount(m_it_block);
    }
  }
  else
  {
    m_it_block = 0;
    m_it_element = 0;
    if ( 0 != block_element_count )
      *block_element_count = 0;
  }
  return m_it_element;
}

void* ON_FixedSizePool::Element(size_t element_index) const
{
  if (element_index < (size_t)m_total_element_count)
  {
    const char* block;
    const char* block_end;
    const char* next_block;
    size_t block_count;

    for (block = (const char*)m_first_block; 0 != block; block = next_block)
    {
      if (block == m_al_block)
      {
        next_block = nullptr;

        // for debugging
        // block += sizeof(void*);
        // block_end = *((const char**)(block));
        // block += sizeof(void*);

        block_end = (const char*)m_al_element_array;
        block += 2*sizeof(void*);
      }
      else
      {
        next_block = *((const char**)block);
        block += sizeof(void*);
        block_end = *((const char**)(block));
        block += sizeof(void*);
      }
      block_count = (block_end - block) / m_sizeof_element;
      if (element_index < block_count)
        return ((void*)(block + element_index*m_sizeof_element));
      element_index -= block_count;
    }
  }

  return nullptr;
}

size_t ON_FixedSizePool::ElementIndex(const void* element_pointer) const
{
  if (nullptr != element_pointer)
  {
    const char* block;
    const char* block_end;
    const char* next_block;
    size_t block_count;
    const char* ptr = (const char*)element_pointer;
    size_t ptr_index = 0;
    for (block = (const char*)m_first_block; 0 != block; block = next_block)
    {
      if (block == m_al_block)
      {
        // After a ReturnAll(), a multi-block fsp has unused blocks after m_al_block.
        // Searching must terminate at m_al_block.
        next_block = nullptr;
        block_end = (const char*)m_al_element_array;
        block += (2 * sizeof(void*));
      }
      else
      {
        next_block = *((const char**)block);
        block += sizeof(void*);
        block_end = *((const char**)(block));
        block += sizeof(void*);
      }
      if (ptr >= block && ptr < block_end)
      {
        size_t offset = ptr - block;
        if (0 == offset % m_sizeof_element)
        {
          ptr_index += (unsigned int)(offset/m_sizeof_element);
          return ptr_index;
        }
        // Caller is confused
        ON_ERROR("element_pointer is offset into an fsp element.");
        return ON_MAX_SIZE_T;
      }
      block_count = (block_end - block) / m_sizeof_element;
      ptr_index += block_count;
    }
    // Caller is confused
    ON_ERROR("element_pointer is not in allocated fsp memory.");
    return ON_MAX_SIZE_T;
  }

  return ON_MAX_SIZE_T;
}

bool ON_FixedSizePool::InPool(
  const void* p
) const
{
  if (nullptr != p)
  {
    const char* block;
    const char* block_end;
    const char* next_block;
    const char* ptr = (const char*)p;
    for (block = (const char*)m_first_block; 0 != block; block = next_block)
    {
      if (block == m_al_block)
      {
        // After a ReturnAll(), a multi-block fsp has unused blocks after m_al_block.
        // Searching must terminate at m_al_block.
        next_block = nullptr;
        block_end = (const char*)m_al_element_array;
        block += (2 * sizeof(void*));
      }
      else
      {
        next_block = *((const char**)block);
        block += sizeof(void*);
        block_end = *((const char**)(block));
        block += sizeof(void*);
      }
      if (ptr >= block && ptr < block_end)
        return true;
    }
  }

  return false;
}

void* ON_FixedSizePool::ElementFromId(
  size_t id_offset,
  unsigned int id
  ) const
{
  const char* block;
  const char* block_end;
  const char* next_block;
  unsigned int i0, i1;
  size_t count;
  if (id_offset < sizeof(void*))
  {
    // caller is confused.
    ON_ERROR("id_offset is too small.");
    return nullptr;
  }
  if (id_offset + sizeof(id) > m_sizeof_element)
  {
    // caller is confused.
    ON_ERROR("id_offset is too large.");
    return nullptr;
  }

  for (block = (const char*)m_first_block; 0 != block; block = next_block)
  {
    if (block == m_al_block)
    {
      next_block = nullptr;
      block_end = (const char*)m_al_element_array;
      block += (2 * sizeof(void*));
    }
    else
    {
      next_block = *((const char**)block);
      block += sizeof(void*);
      block_end = *((const char**)(block));
      block += sizeof(void*);
    }

    i1 = *((const unsigned int*)(block_end-(m_sizeof_element-id_offset)));
    if (i1 < id)
      continue;

    if ( id == i1 )
      return (void*)(block_end-m_sizeof_element);

    i0 = *((const unsigned int*)(block + id_offset));
    if (id < i0)
      continue;

    if ( id == i0 )
      return (void*)(block);

    count = (block_end - block)/m_sizeof_element;
    if (i1 - i0 + 1 == count)
    {
      return (void*)(block + ((id-i0)*m_sizeof_element));
    }

    return (void*)ON_BinarySearchArrayForUnsingedInt(id, block, count, m_sizeof_element, id_offset );
  }

  return nullptr;
}

unsigned int ON_FixedSizePool::MaximumElementId(
  size_t id_offset
) const
{
  const char* block;
  const char* block_end;
  const char* next_block;
  unsigned int maximum_id = 0;
  if (id_offset < sizeof(void*))
  {
    // caller is confused.
    ON_ERROR("id_offset is too small.");
    return 0;
  }
  if (id_offset + sizeof(maximum_id) > m_sizeof_element)
  {
    // caller is confused.
    ON_ERROR("id_offset is too large.");
    return 0;
  }

  for (block = (const char*)m_first_block; 0 != block; block = next_block)
  {
    if (block == m_al_block)
    {
      next_block = nullptr;
      block_end = (const char*)m_al_element_array;
      block += (2 * sizeof(void*));
    }
    else
    {
      next_block = *((const char**)block);
      block += sizeof(void*);
      block_end = *((const char**)(block));
      block += sizeof(void*);
    }

    unsigned int i1 = *((const unsigned int*)(block_end-(m_sizeof_element-id_offset)));
    if (i1 > maximum_id)
      maximum_id = i1;
  }

  return maximum_id;
}

bool ON_FixedSizePool::ElementIdIsIncreasing(
  size_t id_offset
) const
{
  const char* block;
  const char* block_end;
  const char* next_block;
  const unsigned int* i0;
  const unsigned int* i1;
  unsigned int prev_id = 0;
  unsigned int id;
  bool bFirstId = true;
  size_t count;
  if (0 != ( m_sizeof_element % sizeof(id)) )
  {
    // caller is confused.
    ON_ERROR("m_sizeof_element must be a multiple of sizeof(unsigned int).");
    return false;
  }
  if (id_offset < sizeof(void*) )
  {
    // caller is confused.
    ON_ERROR("id_offset is too small.");
    return false;
  }
  if (id_offset + sizeof(prev_id) > m_sizeof_element)
  {
    // caller is confused.
    ON_ERROR("id_offset is too large.");
    return false;
  }

  const size_t delta_i = m_sizeof_element / sizeof(id);
  for (block = (const char*)m_first_block; 0 != block; block = next_block)
  {
    if (block == m_al_block)
    {
      next_block = nullptr;
      block_end = (const char*)m_al_element_array;
      block += (2 * sizeof(void*));
    }
    else
    {
      next_block = *((const char**)block);
      block += sizeof(void*);
      block_end = *((const char**)(block));
      block += sizeof(void*);
    }

    count = (block_end - block)/m_sizeof_element;
    if (0 == count)
      continue;

    i0 = ((const unsigned int*)(block + id_offset));
    i1 = ((const unsigned int*)(block_end-(m_sizeof_element-id_offset)));

    if (bFirstId)
    {
      prev_id = *i0;
      bFirstId = false;
      i0 += delta_i;
    }
    while (i0 <= i1)
    {
      id = *i0;
      if (id <= prev_id)
        return false;
      prev_id = id;
      i0 += delta_i;
    }
  }

  return true;
}

unsigned int ON_FixedSizePool::ResetElementId(
  size_t id_offset,
  unsigned int initial_id
)
{
  const char* block;
  const char* block_end;
  const char* next_block;
  unsigned int* i0;
  unsigned int* i1;
  unsigned int id = initial_id;
  size_t count;
  if (0 != ( m_sizeof_element % sizeof(id)) )
  {
    // caller is confused.
    ON_ERROR("m_sizeof_element must be a multiple of sizeof(unsigned int).");
    return 0;
  }
  if (id_offset < sizeof(void*))
  {
    // caller is confused.
    ON_ERROR("id_offset is too small.");
    return 0;
  }
  if (id_offset + sizeof(id) > m_sizeof_element)
  {
    // caller is confused.
    ON_ERROR("id_offset is too large.");
    return 0;
  }

  const size_t delta_i = m_sizeof_element / sizeof(id);
  for (block = (const char*)m_first_block; 0 != block; block = next_block)
  {
    if (block == m_al_block)
    {
      next_block = nullptr;
      block_end = (const char*)m_al_element_array;
      block += (2 * sizeof(void*));
    }
    else
    {
      next_block = *((const char**)block);
      block += sizeof(void*);
      block_end = *((const char**)(block));
      block += sizeof(void*);
    }

    count = (block_end - block)/m_sizeof_element;
    if (0 == count)
      continue;

    i0 = ((unsigned int*)(block + id_offset));
    i1 = ((unsigned int*)(block_end-(m_sizeof_element-id_offset)));

    while (i0 <= i1)
    {
      *i0 = id++;
      i0 += delta_i;
    }
  }

  return id;
}
