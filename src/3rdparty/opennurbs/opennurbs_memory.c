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

#include "opennurbs_system.h"
#include "opennurbs_defines.h"
#include "opennurbs_memory.h"
#include "opennurbs_error.h"

#if defined(ON_DLL_IMPORTS)
/*
// If you use OpenNURBS as a windows DLL, then define ON_DLL_IMPORTS 
// in applications that use OpenNURBS and they will get onmalloc(), etc.,
// from the DLL.
//
// If you use OpenNURBS as a static library, do not define ON_DLL_IMPORTS.
*/
#error opennurbs_memory.c must not be compiled with ON_DLL_IMPORTS defined.
#endif

// An opennurbs_memory_*.c file must provide definitions of the
// static onmemhelper_*() functions declared below.  If you want
// to provide custom memory management, then you should fill in the
// "TODO" areas in opennurbs_memory_custom.c and define ON_MEMORY_CUSTOM.

static void   onmemhelper_begin( void );
static void   onmemhelper_end( void );

static void*  onmemhelper_malloc( ON_MEMORY_POOL*, size_t );
static void*  onmemhelper_calloc( ON_MEMORY_POOL*, size_t, size_t );
static void   onmemhelper_free( void* );
static void*  onmemhelper_realloc( ON_MEMORY_POOL*, void*, size_t );
static size_t onmemhelper_msize( const void* );

static ON_MEMORY_POOL* onmemhelper_createpool( void );
static void            onmemhelper_destroypool( ON_MEMORY_POOL* );
static void            onmemhelper_compactpool( ON_MEMORY_POOL* );


static int ON_memory_error(int);

/*
// Memory error handling
//
// See the declaration of ON_memory_error_register_handler() for instructions.
*/
static ON_memory_error_handler ON_memory_error_handler_func = 0;

static int ON_memory_error(int error_number)
{
  /*
  // error_number 0: malloc()/calloc()/realloc() returned 0
  //              1: invalid pointer passed into realloc()
  //              2: invalid pointer passed into free()
  //              3: msize() returned 0 or 0xFFFFFFFF
  //              4: ON_CreateMemoryPool() failed.
  //              5: ON_DestroyMemoryPool() failed.
  //              6: onmemhelper_free() failed.
  //              7: ON_MemoryCompactPool() failed.
  //              8: onmemhelper_exit_thread() failed.
  //              9: bad pool passed to onmemhelper_malloc().
  //             10: onmemhelper_exit_thread failed.
  //
  // If this function returns a nonzero value, the call is repeated.
  // If this function returns zero, the call fails as gracefully as possible.
  */
  return (ON_memory_error_handler_func) ? ON_memory_error_handler_func(error_number) : 0;
}

// glb_pMainPool is set when openNURBS starts and
// is never changed.
static ON_MEMORY_POOL glb_mainpool;

// glb_pWorkerPool is NULL unless a worker thread
// is running.  When a worker thread is starting,
// there is a brief interval when glb_pWorkerPool
// is not NULL and glb_pWorkerPool->m_thread_id
// m_thread_id = main application's thread id.
// After the worker thread terminates, there is 
// a brief period when glb_pWorkerPool->m_thread_id
// is zero.
static ON_MEMORY_POOL* glb_pWorkerPool = 0;

#define ON_CURRENT_POOL &glb_mainpool

static void* onmemhelper_malloc( ON_MEMORY_POOL* pool, size_t sz )
{
  // 4 Sep 2003 - possible for sz=0 to make it to this point
  return ((sz>0)?malloc( sz ):0);
}

static void* onmemhelper_calloc( ON_MEMORY_POOL* pool, size_t num, size_t sz )
{
  return calloc(num,sz);
}

static void onmemhelper_free( void* memblock )
{
  free(memblock);
}

#if defined(_MSC_VER)
#if _MSC_VER == 1200
/*
//  (_MSC_VER is defined as 1200 for Microsoft Visual C++ 6.0)
//
//   NOTE WELL: Microsoft's VC 6.0 realloc() contains a bug that can cause
//              crashes and should be avoided.  See MSDN Knowledge Base
//              article ID Q225099 for more information.
*/
#define ON_REALLOC_BROKEN
#endif
#endif

static void* onmemhelper_realloc( ON_MEMORY_POOL* pool, void* memblock, size_t sz )
{
#if defined(ON_REALLOC_BROKEN)
  /* use malloc() and memcpy() instead of buggy realloc() */
  void* p;
  const size_t memblocksz = _msize(memblock);
  if ( sz <= memblocksz ) {
    /* shrink */
    if ( memblocksz <= 28 || 8*sz >= 7*memblocksz ) 
    {
      /* don't bother reallocating */
      p = memblock;
    }
    else {
      /* allocate smaller block */
      p = malloc(sz);
      if ( p ) 
      {
        memcpy( p, memblock, sz );
        free(memblock);
      }
    }
  }
  else if ( sz > memblocksz ) {
    /* grow */
    p = malloc(sz);
    if ( p ) {
      memcpy( p, memblock, memblocksz );
      free(memblock);
    }
  }
  return p;
#else
  return realloc( memblock, sz );
#endif
}

static size_t onmemhelper_msize( const void* p )
{
#if defined(ON_OS_WINDOWS)
  return _msize((void*)p);
#else
  // OS doesn't support _msize().
  return 0;
#endif
}

static void onmemhelper_begin(void)
{
  return;
}

static void onmemhelper_end(void)
{
  return;
}

static ON_MEMORY_POOL* onmemhelper_createpool( void )
{
  return 0;
}

static void onmemhelper_destroypool( ON_MEMORY_POOL* pool )
{
}

static void onmemhelper_compactpool( ON_MEMORY_POOL* pool )
{
}

ON_memory_error_handler ON_memory_error_register_handler( ON_memory_error_handler f )
{
  ON_memory_error_handler oldf = ON_memory_error_handler_func;
  ON_memory_error_handler_func = f;
  return oldf;
}


#if defined(ON_DEBUG)
#define ON_COUNT_MEMORYUSE
#endif

static size_t onmemoryusecounters[4] = {0,0,0,0}; // {malloc_count,realloc_count,free_count,pool_count}

size_t onmemoryusecount(size_t* malloc_count, size_t* realloc_count, size_t* free_count, size_t* pool_count )
{
  // The counters are uses only when ON_COUNT_MEMORYUSE is defined.
  if ( malloc_count )
    *malloc_count = onmemoryusecounters[0];
  if ( realloc_count )
    *realloc_count = onmemoryusecounters[1];
  if ( free_count )
    *free_count = onmemoryusecounters[2];
  if ( pool_count )
    *pool_count = onmemoryusecounters[3];
  return (onmemoryusecounters[0]+onmemoryusecounters[1]+onmemoryusecounters[2]+onmemoryusecounters[3]);
}

/*
// Memory pool handling
*/

ON_MEMORY_POOL* ON_CreateMemoryPool( void )
{
  ON_MEMORY_POOL* pool = onmemhelper_createpool();
  if ( 0 == pool )
  {
    ON_memory_error(4);
  }
#if defined(ON_COUNT_MEMORYUSE)
  onmemoryusecounters[3]++;
#endif
  return pool;
}


void ON_DestroyMemoryPool( ON_MEMORY_POOL* pool )
{
  onmemhelper_destroypool(pool);
}


void ON_CompactMemoryPool( ON_MEMORY_POOL* pool )
{
  onmemhelper_compactpool(pool);
}

ON_MEMORY_POOL* ON_MainMemoryPool(void)
{
  return &glb_mainpool;
}

ON_MEMORY_POOL* ON_WorkerMemoryPool(void)
{
  return glb_pWorkerPool;
}

void ON_SetWorkerMemoryPool( ON_MEMORY_POOL* pool )
{
  if ( pool && pool->m_pool_id >= 2 )
  {
    glb_pWorkerPool = pool;
  }
  else
  {
    glb_pWorkerPool = 0;
  }
}


void* onmalloc_from_pool( ON_MEMORY_POOL* pool, size_t sz )
{
  void* p;
#if defined(ON_COUNT_MEMORYUSE)
  onmemoryusecounters[0]++;
#endif
  if (!pool)
    pool = ON_CURRENT_POOL;

  if (sz <= 0 )
  {
    // 4 Sep 2003 - using onmalloc(0) to check for cancel
    onmemhelper_malloc( pool, 0 );
    return 0;
  }
  for(;;) {
    p = onmemhelper_malloc( pool, sz );
    if (p)
      break;
    if (!ON_memory_error(0))
      break;
  }
  return p;
}


void* onmalloc( size_t sz )
{
  return onmalloc_from_pool( 0, sz );
}


void* oncalloc_from_pool( ON_MEMORY_POOL* pool, size_t num, size_t sz )
{
  void* p;
#if defined(ON_COUNT_MEMORYUSE)
  onmemoryusecounters[0]++;
#endif
  if ( num<= 0 || sz <=0 )
    return 0;

  if (!pool)
    pool = ON_CURRENT_POOL;

  for(;;) {
    p = onmemhelper_calloc( pool, num, sz );
    if (p)
      break;
    if (!ON_memory_error(0))
      break;
  }
  return p;
}


void* oncalloc( size_t num, size_t sz )
{
  return oncalloc_from_pool( 0, num, sz );
}


void onfree( void* memblock )
{
#if defined(ON_COUNT_MEMORYUSE)
  onmemoryusecounters[2]++;
#endif
  if ( memblock )
    onmemhelper_free( memblock );
}


void* onrealloc( void* memblock, size_t sz )
{
  return onrealloc_from_pool( 0, memblock, sz );
}


void* onrealloc_from_pool( ON_MEMORY_POOL* pool, void* memblock, size_t sz )
{
  void* p;
  if ( sz <= 0 ) {
    onfree(memblock);
    return 0;
  }
  if ( !memblock ) {
    return onmalloc_from_pool( pool, sz);
  }
#if defined(ON_COUNT_MEMORYUSE)
  onmemoryusecounters[1]++;
#endif
  if (!pool)
    pool = ON_CURRENT_POOL;

  for(;;) {
    p = onmemhelper_realloc( pool, memblock, sz );
    if (p)
      break;
    if (!ON_memory_error(0))
      break;
  }
  return p;
}


size_t onmsize( const void* memblock )
{
  size_t sz = 0;
  if (memblock) {
    for(;;) {
      sz = onmemhelper_msize( memblock );
      if ( sz > 0 && sz != 0xFFFFFFFF )
        break;
      if ( !ON_memory_error(3) ) {
        sz = 0;
        break;
      }
    }
  }
  return sz;
}

static int glb_MemoryManagerStatus = 0;


void ON_MemoryManagerBegin(void)
{
  if ( 0 == glb_MemoryManagerStatus ) 
  {
    glb_MemoryManagerStatus = 1;
    onmemhelper_begin();
  }
}


void ON_MemoryManagerEnd(void)
{
  if (1 == glb_MemoryManagerStatus) 
  {
    glb_MemoryManagerStatus = -1;
    onmemhelper_end();
  }
}

