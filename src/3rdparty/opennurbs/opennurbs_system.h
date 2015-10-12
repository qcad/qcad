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

/*
////////////////////////////////////////////////////////////////
//
//   Includes all system headers required to use the openNURBS toolkit.
//
////////////////////////////////////////////////////////////////
*/

#if !defined(OPENNURBS_SYSTEM_INC_)
#define OPENNURBS_SYSTEM_INC_

#if defined(TL_PURIFY_BUILD) || defined(RHINO_PURIFY_BUILD)
#if !defined(ON_PURIFY_BUILD)
#define ON_PURIFY_BUILD
#endif
#endif

/* compiler choice */
#if defined(_MSC_VER)

/* using a Microsoft compiler */
#define ON_COMPILER_MSC

#if _MSC_VER >= 1300
#define ON_COMPILER_MSC1300
// If you are using VC7/.NET and are having trouble linking 
// to functions that have whcar_t types in arguments, then
// read the documentation about the wchar_t type and
// the /Zc:wchar_t compiler option.

#if _MSC_VER >= 1400
#define ON_COMPILER_MSC1400

// We are using /W4 wrning levels and disable
// these warnings.  I would prefer to use
// /W3 and enable the level 4 warnings we want,
// but microsoft does not have a way to use pragmas
// to enable specific warnings.

#if defined(ON_COMPILING_OPENNURBS)
#pragma warning(disable:4100) // C4100: 'identifier' : unreferenced formal parameter
#endif

#if !defined(_CRT_SECURE_NO_DEPRECATE)
#define _CRT_SECURE_NO_DEPRECATE
// Visual Studio 2005 issues a C4996 warning for lots of
// standard C runtime functions that take string pointers.
// The _CRT_SECURE_NO_DEPRECATE suppresses these warnings.
// If you are an IT manager type and really care about these
// sorts of things, then comment out the define.
#endif

#endif

#endif

#endif

#if defined(__GNUG_) || defined(__GNUG__) || defined(__GNUC_) || defined(__GNUC__) || defined(_GNU_SOURCE) || defined(__GNU_SOURCE)
/* using Gnu's compiler */
#if !defined(ON_COMPILER_GNU)
#define ON_COMPILER_GNU
#endif
#if !defined(_GNU_SOURCE)
#define _GNU_SOURCE
#endif
#endif


#if defined(_GNU_SOURCE) && defined(__APPLE__)
/* using Apple's OSX XCode compiler */
#if !defined(ON_COMPILER_XCODE)
#define ON_COMPILER_XCODE
#endif
#endif

#if defined(__BORLANDC__)
/* using Borland's compiler */
#define ON_COMPILER_BORLAND
#endif

/*
// Define ON_NO_WINDOWS if you are compiling on a Windows system but want
// to explicitly exclude inclusion of windows.h.
*/

#if !defined(ON_NO_WINDOWS)

/*
/////////////////////////////////////////////////////////////////////////
//
// Begin Windows system includes - 
*/
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

#if defined(_M_X64) && defined(WIN32) && defined(WIN64)
// 23 August 2007 Dale Lear

// andrew: begin: fix for compilation on win64 / msvc2013:
#if defined(_INC_WINDOWS)
// The user has included Microsoft's windows.h before opennurbs.h,
// and windows.h has nested includes that unconditionally define WIN32.
// Just undo the damage here or everybody that includes opennurbs.h after
// windows.h has to fight with this Microsoft bug.
#undef WIN32
#else
//#error do not define WIN32 for x64 builds
#endif
//#undef WIN32
// andrew: end

// NOTE _WIN32 is defined for any type of Windows build
#endif

/*
// From windows.h openNURBS only needs definitions of ON_BOOL32, true,
// and false, and a declarations of OutputDebugString(), and
// WideCharToMultiByte().  These 
// defines disable the inclusion of most of the Windows garbage.
*/

#if !defined(_WINDOWS_)
/* windows.h has not been read - read just what we need */
#define WIN32_LEAN_AND_MEAN  /* Exclude rarely-used stuff from Windows headers */
#include <windows.h>
#endif

#if defined(_M_X64) && defined(WIN32) && defined(WIN64)
// 23 August 2007 Dale Lear
//   windows.h unconditionally defines WIN32  This is a bug
//   and the hope is this simple undef will let us continue.
#undef WIN32
#endif

/*
// if ON_OS_WINDOWS is defined, debugging and error
// handing uses some Windows calls and ON_String
// includes resource support.
*/

#if !defined(ON_OS_WINDOWS)
#define ON_OS_WINDOWS
#endif

#if defined(ON_OS_WINDOWS) && !defined(NOGDI)
// ok to use Windows GDI RECT, LOGFONT, ... stucts.
#define ON_OS_WINDOWS_GDI
#endif

#if defined(_MSC_VER)
/* 
  Microsoft's Visual C/C++ requires some functions, including those that
  use vargs to be declared with __cdecl 
  Since this code must also compile with non-Micorosoft compilers, 
  the ON_MSC_CDECL macro is used to insert __cdecl when needed.
*/
#define ON_MSC_CDECL __cdecl

#endif

#endif

#endif

// NOTE: Do not use rand_s() - it crashes Win2000.
//
//#if defined(_MSC_VER) && !defined(_CRT_RAND_S)
//// In order to get high quality random numbers out of
//// Microsoft Visual Studio, you have to define _CRT_RAND_S
//// before including system header files.
//#define _CRT_RAND_S
//#endif

#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <float.h>
#include <time.h>
#include <limits.h>
#include <ctype.h>

#if defined(ON_COMPILER_IRIX)
#include <alloca.h>
#endif

#if !defined(ON_COMPILER_BORLAND)
#include <wchar.h>
#endif

#if defined(ON_OS_WINDOWS)
#include <io.h>
#include <sys\stat.h>
#include <tchar.h>

// ON_CreateUuid calls Windows's ::UuidCreate() which
// is declared in Rpcdce.h and defined in Rpcrt4.lib.
#include <Rpc.h>

#endif

#if defined(ON_COMPILER_GNU)
#include <sys/types.h>
#include <sys/stat.h>
#include <wctype.h>
#if defined(ON_COMPILER_XCODE)
#include <uuid/uuid.h>
#endif
#endif

#if defined (cplusplus) || defined(_cplusplus) || defined(__cplusplus)
// C++ system includes

#if !defined(ON_CPLUSPLUS)
#define ON_CPLUSPLUS
#endif

#include <new> // for declaration of placement versions of new used in onClassArray<>.

#endif

#if !defined(ON_MSC_CDECL)
#define ON_MSC_CDECL
#endif

#if !defined(ON_OS_WINDOWS)

/* define wchar_t, true, false, NULL */

#if !defined(true)
#define true true
#endif

#if !defined(false)
#define false false
#endif

#if !defined(NULL)
#define NULL 0
#endif

#if !defined(_WCHAR_T_DEFINED)
// If you are using VC7/.NET and are having trouble linking 
// to functions that have whcar_t types in arguments, then
// read the documentation about the wchar_t type and
// the /Zc:wchar_t compiler option.  Since 

/* 16-bit wide character ("UNICODE") */

#if !defined(_WCHAR_T)
//typedef unsigned short wchar_t;
//typedef unsigned wchar_t;
#endif

#define _WCHAR_T_DEFINED
#endif

#endif


// As 64 bit compilers become more common, the definitions
// of the next 6 typedefs may need to vary with compiler.
// As much as possible, the size of runtime types is left 
// up to the compiler so performance and ease of use can 
// be maximized.  In the rare cases where it is critical 
// to use an integer that is exactly 16 bits, 32 bits 
// or 64 bits, the ON__INT16, ON__INT32, and ON__INT64
// typedefs are used.

#if defined(_M_X64) || defined(_WIN64) || defined(__LP64__)
// 64 bit (8 byte) pointers
#define ON_SIZEOF_POINTER 8
#define ON_64BIT_POINTER
#else
// 32 bit (4 byte) pointers
#define ON_SIZEOF_POINTER 4
#define ON_32BIT_POINTER
#endif

#if defined(ON_PURIFY_BUILD)
// ON_PURIFY_BUILD is defined in the DebugPurify
// build configuration.  
#pragma message(" --- OpenNURBS Purify build.")
#if defined(ON_32BIT_POINTER) && defined(ON_COMPILING_OPENNURBS)
// The header file ..\PurifyAPI\pure.h contains delclarations
// of the Purify API functions.
// The file ..\PurifyAPI\pure_api.c contains the definitions.
// The versions we have only work in WIN32.
#include "../PurifyAPI/pure.h"
#endif
#endif

// 8 bit integer
typedef char ON__INT8;

// 8 bit unsigned integer
typedef unsigned char ON__UINT8;

// 16 bit integer
typedef short ON__INT16;

// 16 bit unsigned integer
typedef unsigned short ON__UINT16;

// 32 bit integer
typedef int ON__INT32;

// 32 bit unsigned integer
typedef unsigned int ON__UINT32;

#if defined(ON_COMPILER_MSC)

// Microsoft uses __int64

// 64 bit integer
typedef __int64 ON__INT64;

// 64 bit unsigned integer
typedef unsigned __int64 ON__UINT64;

#elif defined(ON_COMPILER_GNU)

// GNU uses long long

// 64 bit integer
typedef long long ON__INT64;

// 64 bit unsigned integer
typedef unsigned long long ON__UINT64;

#else

#error Verify that long long is a 64 bit integer with your compiler!

// 64 bit integer
typedef long long ON__INT64;

// 64 bit unsigned integer
typedef unsigned long long ON__UINT64;

#endif

// 32 bit boolean (true/false) value
// When we can break the SDK, this will be replaced with "bool", which is 1 byte on windows.
typedef int ON_BOOL32;

// ON_INT_PTR must be an integer type with sizeof(ON_INT_PTR) = sizeof(void*).
#if 8 == ON_SIZEOF_POINTER

#if defined(ON_COMPILER_GNU)
typedef long long ON__INT_PTR;
typedef unsigned long long ON__UINT_PTR;
#else
typedef __int64 ON__INT_PTR;
typedef unsigned __int64 ON__UINT_PTR;
#endif

#elif 4 == ON_SIZEOF_POINTER

typedef int ON__INT_PTR;
typedef unsigned int ON__UINT_PTR;

#else
#error Update OpenNURBS to work with new pointer size.
#endif



// In some functions, performance is slightly increased 
// when the endianess of the CPU is known at compile time.
// If the endianness is not known, it is quickly detected
// at runtime and all opennurbs code still works.
//
// If ON_LITTLE_ENDIAN is defined, then the code will
// is compiled assuming little endian byte order.
//
// If ON_BIG_ENDIAN is defined, then the code will
// is compiled assuming big endian byte order.
//
// If neither is defined, the endianess is determined at
// runtime.
//
// If both are defined, a compile error occures.

#if defined(ON_OS_WINDOWS) && defined(ON_COMPILER_MSC)

#if defined(_M_X64) || defined(_M_IX86)
#if !defined(ON_LITTLE_ENDIAN)
#define ON_LITTLE_ENDIAN
#endif
#endif

#endif




#if defined(ON_LITTLE_ENDIAN) && defined(ON_BIG_ENDIAN)
#error At most one of ON_LITTLE_ENDIAN and ON_BIG_ENDIAN can be defined.
#endif


// on_vsnprintf()/on_vsnwprintf() call _vsnprintf()/_vsnwprintf() in Windows
// and something equivalent in other OSs

int on_vsnprintf( char *buffer, size_t count, const char *format, va_list argptr );

int on_vsnwprintf( wchar_t *buffer, size_t count, const wchar_t *format, va_list argptr );


#endif

