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

#if !defined(OPENNURBS_MEMORY_INC_)
#define OPENNURBS_MEMORY_INC_

#if defined (cplusplus) || defined(_cplusplus) || defined(__cplusplus)
extern "C" {
#endif

ON_DECL
void ON_MemoryManagerBegin(void);

ON_DECL
void ON_MemoryManagerEnd(void);

/*
/////////////////////////////////////////////////////////////////////////////
//
// ALL memory managment in the openNURBS toolkit is done through calls to
//    onmalloc(), oncalloc(), onrealloc(), onfree(), 
//    onmsize(), onmemdup(), onstrdup(), ..., and the
//    new and delete operators
// The on*() functions are all declared in opennurbs_memory.h and defined
// in opennurbs_memory.c.  The new and delete operators that use onmalloc()
// and onfree() are defined in opennurbs_memory_new.cpp.
//
// You may OPTIONALLY provide your own memory managment functions.  See
// opennurbs_memory.c for details.
//
/////////////////////////////////////////////////////////////////////////////
//
// Details:
//
// void* onmalloc( site_t sz );
//
//   If sz is zero, NULL is returned.
//   If sz is positive and there is not enough memory to satify
//   the allocation request, the ON_memory_error_handler(0) is called
//   and NULL is returned.  
//
//   If you have implemented multiple memory pools in a custom manager,
//   the request is sent to the current pool.
//        
//
// void* oncalloc( size_t num, size_t sz );
//
//   If sz or num is zero, NULL is returned.
//   If sz and num are positive and there is not enough memory to satify
//   the allocation request, the ON_memory_error_handler(0) is called
//   and NULL is returned.
//
//   If you have implemented multiple memory pools in a custom manager,
//   the request is sent to the current pool.
//               
//               
// void* onrealloc( void* p, size_t sz );
//
//   If p is NULL, then onmalloc(sz) is called.
//   If sz is zero, then onfree(p) is called and
//   NULL is returned.
//   If p is not NULL, sz is positive, and there is not
//   enough memory to to satify the allocation request,
//   the ON_memory_error_handler(0) is called and NULL is returned.
//   If p is not NULL and is known to be invalid, then
//   ON_memory_error_handler(1) is called.
//
//   If you have implemented multiple memory pools in a custom manager,
//   the request is sent to the current pool.
//
//   NOTE WELL: Microsoft's VC 6.0 realloc() contains a bug that can cause
//              crashes and should be avoided.  See MSDN Knowledge Base
//              article ID Q225099 for more information.
//
//
// void onfree( void* p );
//
//   NULL p is tolerated but considered poor style.
//   If p is not NULL and is known to be invalid, then
//   ON_memory_error_handler(2) is called.
//
//
// size_t onmsize( void*  p );
//
//   If p is NULL, then zero is returned.  Otherwise the
//   the size in bytes of the memory block allocated by onmalloc(),
//   oncalloc(), or onrealloc() is returned.
//               
//
// void* onmemdup( const void* src, size_t sz );
//
//   If src is not NULL and sz is positive, then onmalloc( sz )
//   is called to get memory, sz bytes of src are copied into this
//   memory, and the pointer to this memory is returned.
//   If onmalloc() returns NULL, then NULL is returned.
//   If src is NULL or sz is zero, then NULL is returned.
//               
//
// char* onstrdup( const char* src );
//
//   If src is not NULL, then onmemdup( sc, (strlen(src)+1)*sizeof(src[0]) )
//   is called.  If onmemdup() returns NULL, then NULL is returned.
//   If src is NULL, then NULL is returned.
//               
//
// ON_register_memory_error_handler( ON_memory_error_handler my_handler );
//
//    Use this function to specify the error handler function that will be called
//    if an error occures.  See the description of ON_memory_error_handler() for the
//    error handler function specification.
//
// int ON_memory_error_handler( int error_number );
//
//   This function is called when an error occurs.  The values of error_number
//   are:
//
//     0: There is not enough memory to satisfy an onmalloc() or onrealloc()
//        request.
//
//        If ON_memory_error_handler() returns 0, then onmalloc() or onrealloc()
//        returns NULL.  If ON_memory_error_handler() returns 1, the allocation
//        is attempted again.
//
//     1: An invalid pointer was passed to onrealloc().
//
//        If ON_memory_error_handler() returns 0, then onrealloc() returns NULL.
//        If ON_memory_error_handler() returns 1, the reallocation is attempted
//        again;
//
//     2: An invalid pointer was passed to onfree().
//
//        If ON_memory_error_handler() returns 0, then free() returns.
//        If ON_memory_error_handler() returns 1, the deallocation is
//        attempted again;
//
//     3: An query to onmsize() returned 0 or 0xFFFFFFFF.
//
//        If ON_memory_error_handler() returns 0, then onmsize() returns 0.
//        If ON_memory_error_handler() returns 1, the query is
//        attempted again;
//
// These functions allow you to direct a memory request to a specific pool.  If
// you have not implemented custom memory pool management, these behave exactly
// like onmalloc(), oncalloc(), and onfree().
// 
//   void* onmalloc_from_pool( ON_MEMORY_POOL*, site_t sz );
//   void* oncalloc_from_pool( ON_MEMORY_POOL*, size_t num, size_t sz );
//   void* onrealloc_from_pool( ON_MEMORY_POOL*, void* p, size_t sz );
*/

/* ^^^ see comments above for details ^^^ */

/*
/////////////////////////////////////////////////////////////
//
// Memory error handler - the default handler does nothing.
//
// 
// See opennurbs_memory.c for instructions on using
// custom memory managers.
//
// ON_memory_error_register_handler() returns a pointer to
// the handler you are replacing.  If you pass a NULL,
// the default memory error handler is used.  The default 
// memory error handler returns 0 for all errors.
//
// The input to ON_memory_error_handler(int) is:
//
//   0: malloc/calloc/realloc request returned NULL
//   1: invalid pointer passed to realloc()
//   2: invalid pointer passed to free()
//   3: msize query returned zero or 0xFFFFFFFF
//
// If ON_memory_error_handler(int) returns
//
//   0: The malloc()/calloc()/realloc()/msize() request returns 0.
//   1: The call to malloc()/calloc()/realloc()/msize() is repeated.
//  
*/
/* error handling */
typedef int (*ON_memory_error_handler)(int);
ON_DECL
ON_memory_error_handler ON_memory_error_register_handler( ON_memory_error_handler );

/*
/////////////////////////////////////////////////////////////
//
// Memory pool managment - by default these do nothing
// See opennurbs_memory.c for instructions on using
// custom memory managers
*/

typedef struct tagON_MEMORY_POOL ON_MEMORY_POOL;
struct tagON_MEMORY_POOL
{
  char m__s[16]; // used to store the string "ON_MEMORY_POOL" so
                 // we know what this chunk of memory contains
                 // when debugging complex multi-pool memory leaks.
  /*
  // The default memory managment doesn't use pools.
  // If you provide custom memory managment, you can use these fields.
  //
  // The comments below indicate how Rhino uses these fields.
  */

  /*
  // If nonzero, points to a heap.  If zero, pool uses CRT
  // malloc/calloc/realloc/free.
  */
  void* m_heap;

  void (*m_EndThreadFunction)(ON_MEMORY_POOL* pThisPool);

  /*
  // If nonzero, this pool is associated with an active
  // worker thead and m_thread_id is the thread's id.
  */
  unsigned long m_thread_id;

  /*
  // If nonzero, this pool is temporarily disabled and the
  // main pool should be used for allocation requests that
  // are sent to this pool.
  // onmalloc(), oncalloc(), and onrealloc(0,sz).
  */
  unsigned long m_disabled;

  /*
  // Pool ID.
  //  =  0: invalid value.
  //  = -1: invalid value.
  //  =  1: main application pool
  //  >  1: pool is or was a worker thread pool.  
  //        If m_thread_id is nonzero, then the worker thread 
  //        is still active.  If m_thread_id is zero, the
  //        worker thread successfully completed its task 
  //        and created objects that use memory from this pool.
  //  < -1: pool was a worker thread pool and the pool is no longer
  //        in use.  If This can happen because the worker thread was
  //        canceled or the worker thread finished and didn't leave
  //        any memory allocated in the pool.  The value is the 
  //        negative of the original pool id.
  */
  int   m_pool_id;

  /*
  // Worker thread flag.
  //   If m_h is nonzero, m_i > 1, and m_j is nonzero, then
  //   then a worker thread is running and will be canceled.
  */
  int   m_j;

  /*
  // If pool is a worker thread pool, this value is passed
  // to ExitThread().
  */
  int   m_k;

  /*
  // Reserved for future use.
  */
  int   m_n;
};

ON_DECL
ON_MEMORY_POOL* ON_CreateMemoryPool( void );

ON_DECL
void ON_DestroyMemoryPool( ON_MEMORY_POOL* );

ON_DECL
void ON_CompactMemoryPool( ON_MEMORY_POOL* );

ON_DECL
ON_MEMORY_POOL* ON_MainMemoryPool(void);

ON_DECL
ON_MEMORY_POOL* ON_WorkerMemoryPool(void);

ON_DECL
void ON_SetWorkerMemoryPool( ON_MEMORY_POOL* );

ON_DECL
void*  onmalloc( size_t );

ON_DECL
void*  onmalloc_from_pool( ON_MEMORY_POOL*, size_t );

ON_DECL
void*  oncalloc( size_t, size_t );

ON_DECL
void*  oncalloc_from_pool( ON_MEMORY_POOL*, size_t, size_t );

ON_DECL
void   onfree( void* );

ON_DECL
void*  onrealloc( void*, size_t );

ON_DECL
void*  onrealloc_from_pool( ON_MEMORY_POOL*, void*, size_t );

ON_DECL
size_t onmsize( const void* );

ON_DECL
void*  onmemdup( const void*, size_t );

ON_DECL
char*  onstrdup( const char* );

#if defined(_WCHAR_T_DEFINED)
ON_DECL
wchar_t* onwcsdup( const wchar_t* );
#endif

ON_DECL
unsigned char* onmbsdup( const unsigned char* );

ON_DECL
size_t onmemoryusecount(
          size_t* malloc_count, 
          size_t* realloc_count, 
          size_t* free_count, 
          size_t* pool_count 
          );


/* define to handle _TCHAR* ontcsdup( const _TCHAR* ) */
#if defined(_UNICODE)
#define ontcsdup onwcsdup
#elif defined(_MBCS)
#define ontcsdup onmbsdup
#else
#define ontcsdup onstrdup
#endif

#if defined (cplusplus) || defined(_cplusplus) || defined(__cplusplus)
}
#endif

#endif
