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

////////////////////////////////////////////////////////////////
//
//   Includes all openNURBS toolkit headers required to use the
//   openNURBS toolkit library.  See readme.txt for details.
//
////////////////////////////////////////////////////////////////

#if !defined(OPENNURBS_PUBLIC_INC_)
#define OPENNURBS_PUBLIC_INC_

#define OPENNURBS_PUBLIC_INC_IN_PROGRESS

#if defined(ON_COMPILING_OPENNURBS)
#error Do not include opennurbs_public.h in opennurbs library source code.
#endif

#if defined(OPENNURBS_INC_)
//
// Read the following, think about what you are trying to accomplish,
// and then include exactly one of opennurbs.h or opennurbs_public.h.
//
// If you are building a Rhino plug-in or using the Rhino SDK, 
// then include RhinoSDK.h which will eventually include opennurbs.h.
//
// If you are building your own application and linking with an
// opennurbs_public* library, then include opennurbs_public.h.
// 
#error Include exactly one of opennurbs.h or opennurbs_public.h
#endif


#define OPENNURBS_PUBLIC
#include "opennurbs.h"

#if defined(ON_COMPILER_MSC) && defined(OPENNURBS_PUBLIC_INSTALL_DIR)

#if defined(_DEBUG)
#if defined(ON_64BIT_RUNTIME)
#define OPENNURBS_PUBLIC_LIBS_DIR OPENNURBS_PUBLIC_INSTALL_DIR "/bin/x64/Debug"
#elif defined(ON_32BIT_RUNTIME)
#define OPENNURBS_PUBLIC_LIBS_DIR OPENNURBS_PUBLIC_INSTALL_DIR "/bin/Win32/Debug"
#endif
#else
#if defined(ON_64BIT_RUNTIME)
#define OPENNURBS_PUBLIC_LIBS_DIR OPENNURBS_PUBLIC_INSTALL_DIR "/bin/x64/Release"
#elif defined(ON_32BIT_RUNTIME)
#define OPENNURBS_PUBLIC_LIBS_DIR OPENNURBS_PUBLIC_INSTALL_DIR "/bin/Win32/Release"
#endif
#endif

#if defined(OPENNURBS_IMPORTS)
#pragma message( " --- dynamically linking opennurbs (DLL)." )
#pragma comment(lib, "\"" OPENNURBS_PUBLIC_LIBS_DIR "/" "opennurbs_public.lib" "\"")
#else
#pragma message( " --- statically linking opennurbs." )
#pragma comment(lib, "\"" OPENNURBS_PUBLIC_LIBS_DIR "/" "opennurbs_public_staticlib.lib" "\"")
#pragma comment(lib, "\"" OPENNURBS_PUBLIC_LIBS_DIR "/" "zlib.lib" "\"")
#pragma comment(lib, "\"" OPENNURBS_PUBLIC_LIBS_DIR "/" "freetype263.lib" "\"")
#pragma comment(lib, "rpcrt4.lib")
#pragma comment(lib, "shlwapi.lib")
#endif

#endif

#undef OPENNURBS_PUBLIC_INC_IN_PROGRESS

#endif
