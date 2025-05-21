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

#if !defined(OPENNURBS_ZLIB_INC_)
#define OPENNURBS_ZLIB_INC_

// If you are using opennurbs as a statically linked library, then
// you may make calls to the same zlib that opennurbs uses.  This
// zlib is compiled with z_ symbol projectection.  All the necessary
// header files are included by opennurbs.h.
// 
// If you are using opennurbs as a DLL or writing a Rhino plug-in
// and you want to use the same zlib that opennurbs uses, then
// compile opennurbs_zlib_memory.cpp into your application
// and statically link with the zlib library. All the necessary
// header files are included by opennurbs.h.


#if !defined(Z_PREFIX)
/* decorates zlib functions with a "z_" prefix to prevent symbol collision. */
#define Z_PREFIX
#endif

#if !defined(MY_ZCALLOC)
/* have zlib use oncalloc() and onfree() for memory management*/
#define MY_ZCALLOC
#endif

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include "./zlib/zlib.h"
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

ON_BEGIN_EXTERNC
voidpf zcalloc(voidpf, unsigned, unsigned);
void  zcfree(voidpf, voidpf);
ON_END_EXTERNC

#endif
