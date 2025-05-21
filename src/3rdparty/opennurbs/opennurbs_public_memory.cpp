// Copyright (c) 1993-2024 Robert McNeel & Associates. All rights reserved.
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

#include "opennurbs.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

#if defined(OPENNURBS_IMPORTS)
#error opennurbs_public_memory.c must not be compiled with OPENNURBS_IMPORTS defined.
#endif


void* onmalloc_forever(size_t sz)
{
  return onmalloc(sz);
}

void* onmalloc( size_t sz )
{
  void* p;
  p = (sz > 0) ? malloc(sz) : 0;
  return p;
}

void* oncalloc( size_t num, size_t sz )
{
  void* p;
  p = (num > 0 && sz > 0) ? calloc(num,sz) : 0;
  return p;
}

void onfree( void* memblock )
{
  if ( 0 != memblock )
    free(memblock);
}

void* onrealloc( void* memblock, size_t sz )
{
  if (0 == memblock)
    return onmalloc(sz);
  if (sz <= 0)
  {
    onfree(memblock);
    return 0;
  }
  return realloc(memblock, sz);
}

