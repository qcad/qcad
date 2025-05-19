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

////////////////////////////////////////////////////////////////
//
//   Includes all system headers required to use the openNURBS toolkit.
//
////////////////////////////////////////////////////////////////

#if !defined(OPENNURBS_SYSTEM_INC_)
#define OPENNURBS_SYSTEM_INC_





#define OPENNURBS_PP2STR_HELPER(s) #s
#define OPENNURBS_PP2STR(s) OPENNURBS_PP2STR_HELPER(s)
/*
// To print the value of a preprocessor macro, do something like:
//
//   #pragma message( "MY_MACRO = " OPENNURBS_PP2STR(MY_MACRO) )
//
// Typically something mysterious is defining a macro whose value
// you would like to see at compile time so you can fix a issue
// involving the preprocessor macro's value.
*/

#if defined(ON_DLL_EXPORTS)
#error "ON_DLL_EXPORTS" is obsolete. V6 uses "OPENNURBS_EXPORTS".
#endif

#if defined(ON_EXPORTS)
#error "ON_EXPORTS" is obsolete. V6 uses "OPENNURBS_EXPORTS".
#endif

#if defined(ON_DLL_IMPORTS)
#error "ON_DLL_IMPORTS" is obsolete. V6 uses "OPENNURBS_IMPORTS".
#endif

#if defined(ON_IMPORTS)
#error "ON_IMPORTS" is obsolete. V6 uses "OPENNURBS_IMPORTS".
#endif

#if defined(OPENNURBS_EXPORTS) && defined(OPENNURBS_IMPORTS)
/*
// - When compiling opennurbs as a dll, define OPENNURBS_EXPORTS.
// - When using opennurbs as a dll, define OPENNURBS_IMPORTS.
// - When compiling opennurbs as a static library, ON_COMPILING_OPENNURBS
//   should be defined and neither OPENNURBS_EXPORTS nor OPENNURBS_IMPORTS
//   should be defined.
// - When using opennurbs as a static library, neither
//   ON_COMPILING_OPENNURBS nor OPENNURBS_EXPORTS nor OPENNURBS_IMPORTS
//   should be defined.
*/
#error At most one of OPENNURBS_EXPORTS or OPENNURBS_IMPORTS can be defined.
#endif

#if defined(OPENNURBS_EXPORTS)
#if !defined(ON_COMPILING_OPENNURBS)
#define ON_COMPILING_OPENNURBS
#endif
#endif

#if defined(_DEBUG)
/* enable OpenNurbs debugging code */
#if !defined(ON_DEBUG)
#define ON_DEBUG
#endif
#endif

#if defined(ON_COMPILING_OPENNURBS) && defined(OPENNURBS_IMPORTS)
/*
// - If you are using opennurbs as library, do not define
//   ON_COMPILING_OPENNURBS.
// - If you are compiling an opennurbs library, define
//   ON_COMPILING_OPENNURBS.
*/
#error At most one of ON_COMPILING_OPENNURBS or OPENNURBS_IMPORTS can be defined.
#endif

/*
// Define ON_NO_WINDOWS if you are compiling on a Windows system but want
// to explicitly exclude inclusion of windows.h.
*/

#if defined(ON_COMPILING_OPENNURBS)
#if !defined(OPENNURBS_WALL)
/*
// When OPENNURBS_WALL is defined, warnings and deprications that
// encourage the highest quality of code are used.
*/
#define OPENNURBS_WALL
#endif
#endif


#include "opennurbs_system_compiler.h"

#include "opennurbs_system_runtime.h"

#pragma ON_PRAGMA_WARNING_PUSH

/* compiler choice */
#if defined(ON_COMPILER_MSC)
#include "opennurbs_windows_targetver.h"
#endif

#if defined(ON_RUNTIME_APPLE) && defined(__OBJC__)

// The header file opennurbs_system_runtime.h is included in several
// places before opennurbs.h or opennurbs_system.h is included.
// Therefore, this define cannot be in opennurbs_system_runtime.h
//
// When ON_RUNTIME_APPLE_OBJECTIVE_C_AVAILABLE is defined and
// ON_RUNTIME_APPLE_IOS is NOT defined
// <Cocoa/Cocoa.h> is included by opennurbs_system.h and
// your project must link with the Apple Cocoa Framework.
#define ON_RUNTIME_APPLE_OBJECTIVE_C_AVAILABLE

#endif

#if defined(ON_RUNTIME_APPLE) && defined(ON_RUNTIME_APPLE_OBJECTIVE_C_AVAILABLE)

// TODO:
//   Requiring ON_RUNTIME_APPLE_OBJECTIVE_C_AVAILABLE is too strong,
//   Determine exactly when ON_RUNTIME_APPLE_CORE_TEXT_AVAILABLE should
//   be defined so opennurbs font / glyph tools will work on iOS.

// The header file opennurbs_system_runtime.h is included in several
// places before opennurbs.h or opennurbs_system.h is included.
// Therefore, this define cannot be in opennurbs_system_runtime.h
//
// When ON_RUNTIME_APPLE_CORE_TEXT_AVAILABLE is defined,
// Apple Core Text and Core Graphics SDK can be used.
#define ON_RUNTIME_APPLE_CORE_TEXT_AVAILABLE
#include <CoreText/CoreText.h>

#endif

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <stdint.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

typedef int8_t       ON__INT8;
typedef uint8_t      ON__UINT8;
typedef int16_t      ON__INT16;
typedef uint16_t     ON__UINT16;
typedef int32_t      ON__INT32;
typedef uint32_t     ON__UINT32;
typedef int64_t      ON__INT64;
typedef uint64_t     ON__UINT64;

#define ON_MAX_SIZE_T SIZE_MAX

#if defined(ON_64BIT_RUNTIME)

/* 64 bit (8 byte) pointers */
#define ON_SIZEOF_POINTER 8
#define ON__UINT_PTR_MAX  UINT64_MAX

typedef ON__INT64   ON__INT_PTR;
typedef ON__UINT64  ON__UINT_PTR;

#elif defined(ON_32BIT_RUNTIME)

/* 32 bit (4 byte) pointers */
#define ON_SIZEOF_POINTER 4
#define ON__UINT_PTR_MAX  UINT32_MAX

typedef ON__INT32   ON__INT_PTR;
typedef ON__UINT32  ON__UINT_PTR;

#else
#error Update OpenNURBS to work with new pointer size.
#endif

ON_STATIC_ASSERT(sizeof(ON__INT8)     == 1);
ON_STATIC_ASSERT(sizeof(ON__UINT8)    == 1);
ON_STATIC_ASSERT(sizeof(ON__INT16)    == 2);
ON_STATIC_ASSERT(sizeof(ON__UINT16)   == 2);
ON_STATIC_ASSERT(sizeof(ON__INT32)    == 4);
ON_STATIC_ASSERT(sizeof(ON__UINT32)   == 4);
ON_STATIC_ASSERT(sizeof(ON__INT64)    == 8);
ON_STATIC_ASSERT(sizeof(ON__UINT64)   == 8);

ON_STATIC_ASSERT_MSG(sizeof(ON__INT_PTR)  == sizeof(void*), "ON_INT_PTR must be an integer type with sizeof(ON_INT_PTR) = sizeof(void*)");
ON_STATIC_ASSERT_MSG(sizeof(ON__UINT_PTR) == sizeof(void*), "ON_UINT_PTR must be an integer type with sizeof(ON_UINT_PTR) = sizeof(void*)");
ON_STATIC_ASSERT_MSG(ON_SIZEOF_POINTER    == sizeof(void*), "ON_SIZEOF_POINTER must be equal to sizeof(void*)");

/*
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
//
// BEGIN - fill in missing types and defines
//
// If you are using an old compiler, then define ON_NEED_* when
// you define ON_COMPILER_* above.
//
*/
#if defined(ON_NEED_BOOL_TYPEDEF)
#undef ON_NEED_BOOL_TYPEDEF
typedef ON__UINT8 bool;
#endif

#if defined(ON_NEED_TRUEFALSE_DEFINE)
#undef ON_NEED_TRUEFALSE_DEFINE
#define true ((bool)1)
#define false ((bool)0)
#endif

#if defined(ON_NEED_NULLPTR_DEFINE)
#undef ON_NEED_NULLPTR_DEFINE
#define nullptr 0
#endif

#if defined(ON_NEED_UTF8_WCHAR_T_TYPEDEF)
#if defined(ON_NEED_UTF16_WCHAR_T_TYPEDEF) || defined(ON_NEED_UTF32_WCHAR_T_TYPEDEF)
#error You may define at most one of ON_NEED_UTF8_WCHAR_T_TYPEDEF, ON_NEED_UTF16_WCHAR_T_TYPEDEF and ON_NEED_UTF16_WCHAR_T_TYPEDEF
#endif
#undef ON_NEED_UTF8_WCHAR_T_TYPEDEF
typedef ON__UINT8 wchar_t;
#define ON_SIZEOF_WCHAR_T 1

#elif defined(ON_NEED_UTF16_WCHAR_T_TYPEDEF)
#if defined(ON_NEED_UTF32_WCHAR_T_TYPEDEF)
#error You may define at most one of ON_NEED_UTF8_WCHAR_T_TYPEDEF, ON_NEED_UTF16_WCHAR_T_TYPEDEF and ON_NEED_UTF16_WCHAR_T_TYPEDEF
#endif
#undef ON_NEED_UTF16_WCHAR_T_TYPEDEF
typedef ON__UINT16 wchar_t;
#define ON_SIZEOF_WCHAR_T 2

#elif defined(ON_NEED_UTF32_WCHAR_T_TYPEDEF)
#undef ON_NEED_UTF32_WCHAR_T_TYPEDEF
typedef ON__UINT32 wchar_t;
#define ON_SIZEOF_WCHAR_T 4

#endif

/*
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
//
// Validate ON_SIZEOF_WCHAR_T and set ON_WCHAR_T_ENCODING
//
*/

#if !defined(ON_SIZEOF_WCHAR_T)
#error unknown sizeof(wchar_t)
#endif

#if !defined(ON_WCHAR_T_ENCODING)

#if (1 == ON_SIZEOF_WCHAR_T)
#define ON_WCHAR_T_ENCODING ON_UnicodeEncoding::ON_UTF_8
#elif (2 == ON_SIZEOF_WCHAR_T)
#if defined(ON_LITTLE_ENDIAN)
#define ON_WCHAR_T_ENCODING ON_UnicodeEncoding::ON_UTF_16LE
#elif  defined(ON_BIG_ENDIAN)
#define ON_WCHAR_T_ENCODING ON_UnicodeEncoding::ON_UTF_16BE
#endif
#elif (4 == ON_SIZEOF_WCHAR_T)
#if defined(ON_LITTLE_ENDIAN)
#define ON_WCHAR_T_ENCODING ON_UnicodeEncoding::ON_UTF_32LE
#elif  defined(ON_BIG_ENDIAN)
#define ON_WCHAR_T_ENCODING ON_UnicodeEncoding::ON_UTF_32BE
#endif
#endif

#if !defined(ON_WCHAR_T_ENCODING)
#error unable to automatically set ON_WCHAR_T_ENCODING
#endif

#endif


/*
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
//
// BEGIN - OBSOLETE  defines
//
// These legacy defines will be removed from V6
//
*/

#if defined(__APPLE__) && (defined(_GNU_SOURCE) || defined(ON_COMPILER_CLANG))
/* Poorly named and used define that indicated using Apple's OSX compiler and/or runtime */
#if !defined(ON_COMPILER_XCODE)
#define ON_COMPILER_XCODE
#endif
#endif

#if defined (ON_RUNTIME_WIN) && !defined(ON_OS_WINDOWS)
#define ON_OS_WINDOWS
#endif

#define ON_MSC_CDECL ON_CALLBACK_CDECL

#if defined(ON_64BIT_RUNTIME)
#define ON_64BIT_POINTER
#elif defined(ON_32BIT_RUNTIME)
#define ON_32BIT_POINTER
#endif

/*
//
// END - OBSOLETE  defines
//
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
*/

// To debug linking pragma path issues, uncomment the following line
//#pragma message( "OPENNURBS_OUTPUT_DIR = " OPENNURBS_PP2STR(OPENNURBS_OUTPUT_DIR) )

#if defined(ON_RUNTIME_WIN) && !defined(ON_NO_WINDOWS)

/*
/////////////////////////////////////////////////////////////////////////
//
// Begin Windows system includes -
*/


#if defined(_M_X64) && defined(WIN32) && defined(WIN64)
// 23 August 2007 Dale Lear

#if defined(_INC_WINDOWS)
// The user has included Microsoft's windows.h before opennurbs.h,
// and windows.h has nested includes that unconditionally define WIN32.
// Just undo the damage here or everybody that includes opennurbs.h after
// windows.h has to fight with this Microsoft bug.
#undef WIN32
#else
#error do not define WIN32 for x64 builds
#endif
// NOTE _WIN32 is defined for any type of Windows build
#endif

#if !defined(_WINDOWS_)
/* windows.h has not been read - read just what we need */
#define WIN32_LEAN_AND_MEAN  /* Exclude rarely-used stuff from Windows headers */
#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <windows.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE
#endif

#if (defined(_M_X64) || defined(_M_ARM64)) && defined(WIN32) && defined(WIN64)
// 23 August 2007 Dale Lear
//   windows.h unconditionally defines WIN32  This is a bug
//   and the hope is this simple undef will let us continue.
#undef WIN32
#endif

#if defined(ON_RUNTIME_WIN) && !defined(NOGDI)
/*
// ok to use Windows GDI RECT, LOGFONT, ... structs.
*/
#define ON_OS_WINDOWS_GDI
#endif

#endif

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <stdlib.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <memory.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#if defined(ON_COMPILER_CLANG) && defined(ON_RUNTIME_APPLE)
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <string.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <math.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <stdio.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <stdarg.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <float.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <time.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <limits.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <ctype.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#if defined(ON_COMPILER_IRIX)
#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <alloca.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#endif

#if !defined(ON_COMPILER_BORLANDC)
#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <wchar.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#endif

#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <io.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <sys/stat.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <tchar.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <Rpc.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#endif

#if defined(ON_COMPILER_GNU)
#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <sys/types.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <sys/stat.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <wctype.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <dirent.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#endif

#if defined(ON_COMPILER_CLANG)
#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <sys/types.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <sys/stat.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <wctype.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <dirent.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#if defined(ON_RUNTIME_ANDROID) || defined(ON_RUNTIME_LINUX) || defined(ON_RUNTIME_WASM)
#include "android_uuid/uuid.h"
#else
#include <uuid/uuid.h>
#endif
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#endif

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <errno.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
// For definition of PRIu64 to print 64-bit ints portably.
#include <inttypes.h>
#if !defined(PRIu64)
#error no PRIu64
#endif

#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE


#if defined (cplusplus) || defined(_cplusplus) || defined(__cplusplus)
// C++ system includes

#if !defined(ON_CPLUSPLUS)
#define ON_CPLUSPLUS
#endif

// Standard C++ tools
#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <new>     // for declaration of placement versions of new used in ON_ClassArray<>.
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <memory>  // for std::shared_ptr
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <utility> // std::move
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <string>  // std::string, std::wstring
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <locale>  // for call create_locale(LC_ALL,"C") in ON_Locale().
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <atomic>  // for std:atomic<type>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <chrono>  // for std:chrono::high_resolution_clock
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#if !defined(OPENNURBS_NO_STD_THREAD)
#include <thread>  // for std::this_thread::sleep_for
#endif
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#if !defined(OPENNURBS_NO_STD_MUTEX)
#include <mutex>  // for std:mutex
#endif
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE


#define ON_NO_SHARED_PTR_DTOR(T) [=](T*){}
#define ON_MANAGED_SHARED_PTR(T, p) std::shared_ptr<T>(p)
#define ON_UNMANAGED_SHARED_PTR(T, p) std::shared_ptr<T>(p,[=](T*){})

#if defined(ON_RUNTIME_APPLE)


#if defined(ON_COMPILER_CLANG)
#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <wchar.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <xlocale.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#endif

#if defined(ON_RUNTIME_APPLE_OBJECTIVE_C_AVAILABLE) && !defined(ON_RUNTIME_APPLE_IOS)
// Opennurbs uses CTFont and NSString to load Apple fonts
// int the ON_Font and freetype internals.
// When ON_RUNTIME_APPLE_OBJECTIVE_C_AVAILABLE is defined, you
// must link with the Apple Foundation and CoreText frameworks.
#define ON_RUNTIME_COCOA_AVAILABLE
#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <Cocoa/Cocoa.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#endif
#endif

#endif

#if !defined(ON_RUNTIME_WIN) && !defined(ON_RUNTIME_APPLE)

// As of September, 2018 Freetype is not reliable on Windows, MacOS, and iOS.
//   Its mapping from UNICODE code points to glyph indices is buggy.
//   It does not support OpenType variable fonts like Windows 10 Bahnschrift.
//   It does not support font simulation (Windows does a great job here.)
//   Its support for multiple locale names is limited.
//   Its support for PANOSE1 is limited.
//   It does not support font substitution.
// Windows uses the Direct Write SDK for font and glyph calculations.
// MacOS and iOS use the Apple Core Text SDK for font and glyph calculations.

#if defined(ON_RUNTIME_ANDROID)
// May work reasonably for Android versions < 8-ish as of Sep 2018.
// Test carefully if working right is important.
#define OPENNURBS_FREETYPE_SUPPORT
#else

// not Windows, Apple, or Android

// To disable freetype support, comment out the following define.
// To enable freetype support, define OPENNURBS_FREETYPE_SUPPORT
// NOTE WELL: freetype is not delivered in a 32-bit version.

// Whenever possible use native OS tools for font and glyph support.
// Things like names, outlines, metrics, UNICODE mapping will generally
// work better align with user's experiences on that platform.
// Freetype is basically a platform neutral font file file reading toolkit
// and has all the limitations that arise from that approach to complex
// information modern OSs manage in complicated ways.

//#define OPENNURBS_FREETYPE_SUPPORT

#endif
#endif

/*
/////////////////////////////////////////////////////////////////////////////////
//
// Validate defines
//
*/

/*
// Validate ON_x_ENDIAN defines
*/
#if defined(ON_LITTLE_ENDIAN) && defined(ON_BIG_ENDIAN)
#error Exactly one of ON_LITTLE_ENDIAN or ON_BIG_ENDIAN must be defined.
#endif

#if !defined(ON_LITTLE_ENDIAN) && !defined(ON_BIG_ENDIAN)
#error Either ON_LITTLE_ENDIAN or ON_BIG_ENDIAN must be defined.
#endif

/*
// Validate ON_xBIT_RUNTIME defines
*/
#if defined(ON_64BIT_RUNTIME) && defined(ON_32BIT_RUNTIME)
#error Exactly one of ON_64BIT_RUNTIME or ON_32BIT_RUNTIME must be defined.
#endif

#if !defined(ON_64BIT_RUNTIME) && !defined(ON_32BIT_RUNTIME)
#error Either ON_64BIT_RUNTIME or ON_32BIT_RUNTIME must be defined.
#endif

/*
// Validate ON_SIZEOF_POINTER defines
*/
#if 8 == ON_SIZEOF_POINTER

#if !defined(ON_64BIT_RUNTIME)
#error 8 = ON_SIZEOF_POINTER and ON_64BIT_RUNTIME is not defined
#endif
#if defined(ON_32BIT_RUNTIME)
#error 8 = ON_SIZEOF_POINTER and ON_32BIT_RUNTIME is defined
#error
#endif

#elif 4 == ON_SIZEOF_POINTER

#if !defined(ON_32BIT_RUNTIME)
#error 4 = ON_SIZEOF_POINTER and ON_32BIT_RUNTIME is not defined
#endif
#if defined(ON_64BIT_RUNTIME)
#error 4 = ON_SIZEOF_POINTER and ON_64BIT_RUNTIME is defined
#endif

#else

#error OpenNURBS assumes sizeof(void*) is 4 or 8 bytes

#endif

#if defined(__FUNCTION__)
#define OPENNURBS__FUNCTION__ __FUNCTION__
#elif defined(__func__)
#define OPENNURBS__FUNCTION__ __func__
#else
#define OPENNURBS__FUNCTION__ ""
#endif

#pragma ON_PRAGMA_WARNING_POP


#endif
