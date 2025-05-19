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

#if !defined(OPENNURBS_MEMORY_INC_)
#define OPENNURBS_MEMORY_INC_

#if defined (cplusplus) || defined(_cplusplus) || defined(__cplusplus)
extern "C" {
#endif

ON_DECL
size_t ON_MemoryPageSize();


/*
Allocate memory that is intentionally never returned
should not be considered a memory leak. Typically this is
for an application workspace.
*/
ON_DECL
void* onmalloc_forever( size_t );

ON_DECL
void* onmalloc( size_t );

ON_DECL
void* oncalloc( size_t, size_t );

ON_DECL
void   onfree( void* );

ON_DECL
void* onrealloc( void*, size_t );

ON_DECL
void* onmemdup( const void*, size_t );

ON_DECL
char* onstrdup( const char* );

ON_DECL
wchar_t* onwcsdup( const wchar_t* );

ON_DECL
unsigned char* onmbsdup( const unsigned char* );

#if defined (cplusplus) || defined(_cplusplus) || defined(__cplusplus)
}

class ON_CLASS ON_MemoryAllocationTracking
{
public:
  /*
  Description:
    Windows Debug Builds:
      The constructor saves the current state of memory allocation tracking
      and then enables/disables memory allocation tracking.
    Otherwise:
      Does nothing.
  */
  ON_MemoryAllocationTracking(
    bool bEnableAllocationTracking
  );

  /*
  Description:
    Windows Debug Builds:
      The destructor restores the saved state of memory allocation tracking.
    Otherwise:
      Does nothing.
  */
  ~ON_MemoryAllocationTracking();

private:
  static unsigned int m_g_stack_depth;
  static int m_g_crt_dbg_flag0;
  const unsigned int m_this_statck_depth;
  const int m_this_crt_dbg_flag0;

private:
  ON_MemoryAllocationTracking() = delete;
  ON_MemoryAllocationTracking(const ON_MemoryAllocationTracking&) = delete;
  ON_MemoryAllocationTracking& operator=(const ON_MemoryAllocationTracking&) = delete;
};

#endif

#endif
