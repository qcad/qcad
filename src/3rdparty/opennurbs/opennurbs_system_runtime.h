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

#if !defined(OPENNURBS_SYSTEM_RUNTIME_INC_)
#define OPENNURBS_SYSTEM_RUNTIME_INC_

////////////////////////////////////////////////////////////////
//
// Determines the runtime environment where the code is executed.
//
////////////////////////////////////////////////////////////////


/*
////////////////////////////////////////////////////////////
//
// BEGIN - ON_RUNTIME_APPLE / ON_RUNTIME_WIN / ON_RUNTIME_ANDROID defines
//
// ON_RUNTIME_* specifies the runtime C/C++ SDK being used
//   At most one the ON_RUNTIME_* should be defined
//
//   ON_RUNTIME_APPLE / ON_RUNTIME_WIN / ON_RUNTIME_ANDROID
//
*/
#if (defined(__APPLE__) || defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) || defined(__IOS__))

#if !defined(ON_RUNTIME_APPLE)
#define ON_RUNTIME_APPLE
#endif

#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(WINDOWS) || defined(_WINDOWS_) || defined(__WINDOWS__)

#if !defined(ON_RUNTIME_WIN)
#define ON_RUNTIME_WIN
#endif

#elif defined(__ANDROID__) || defined(ANDROID)
// __EMSCRIPTEN__ is for a web assembly compile which currently compiles with the
// same settings as an android build. We will need to add an ON_RUNTIME_WASM once
// the __EMSCRIPTEN__ compile stabilizes
#if !defined(ON_RUNTIME_ANDROID)
#define ON_RUNTIME_ANDROID
#endif

#elif defined(__linux__)
#if !defined(ON_RUNTIME_LINUX)
#define ON_RUNTIME_LINUX
#endif

#elif defined(__EMSCRIPTEN__)
#if !defined(ON_RUNTIME_WASM)
#define ON_RUNTIME_WASM
#endif

#endif
/*
//
// END - ON_RUNTIME_APPLE / ON_RUNTIME_WIN / ON_RUNTIME_ANDROID / ON_RUNTIME_WASM defines
//
////////////////////////////////////////////////////////////
*/

/*
////////////////////////////////////////////////////////////
//
// BEGIN - Additional platform defines
//
// ON_64BIT_RUNTIME / ON_32BIT_RUNTIME
// ON_LITTLE_ENDIAN / ON_BIG_ENDIAN
// ON_SIZEOF_WCHAR_T
// ON_RUNTIME_<PLATFORM>_<SUBPLATFORM>
//
*/
#if defined(ON_RUNTIME_APPLE)
#include <TargetConditionals.h>

#if (TARGET_OS_IPHONE == 1)
#define ON_RUNTIME_APPLE_IOS
#endif

#if (TARGET_OS_SIMULATOR == 1)
#define ON_RUNTIME_APPLE_IOS
#define ON_RUNTIME_APPLE_IOS_SIMULATOR
#endif

#if !defined(ON_RUNTIME_APPLE_IOS)
#define ON_RUNTIME_APPLE_MACOS

#if !defined(RHINO_CORE_COMPONENT)
// Apple:
//   Defines RHINO_CORE_COMPONENT here.
//   If we publish an Apple C++ pubic SDK, this will need to be adjusted.
// Windows:
//   uses the property sheet RhinoProjectPropertySheets/Rhino.Cpp.common.props
//   Some build products in Windows are not "core components"
#define RHINO_CORE_COMPONENT 1
#endif
#endif

#if (defined(__LP64__) || defined(__ppc64__))
#define ON_64BIT_RUNTIME
#elif defined(__LP32__)
#define ON_32BIT_RUNTIME
#else
#error Add code to detect sizeof pointer on this Apple platform
#endif

#define ON_SIZEOF_WCHAR_T 4

#if (defined(__ppc__) || defined(__ppc64__))
#define ON_BIG_ENDIAN
#else
#define ON_LITTLE_ENDIAN
#endif

#elif defined(ON_RUNTIME_WIN)

#define ON_SIZEOF_WCHAR_T 2

#if defined(WINDOWS_PHONE)
#define ON_RUNTIME_WIN_MOBILE
#else
#define ON_RUNTIME_WIN_WINOS
#endif

#if defined(_M_X64) || defined(_WIN64) || defined(_M_ARM64)
#define ON_64BIT_RUNTIME
#elif defined(_M_X86) || defined(_WIN32)
#define ON_32BIT_RUNTIME
#else
#error Add code to detect sizeof pointer on this Windows platform
#endif

#if !defined(ON_LITTLE_ENDIAN)
#if (defined(_M_X64) || defined(_M_IX86) || defined (__i386__) || defined( __x86_64__ ) || defined(_M_ARM64))
#define ON_LITTLE_ENDIAN
#endif
#endif

#elif defined(ON_RUNTIME_ANDROID)
// Android is Linux
#define ON_RUNTIME_LINUX
#endif

#if defined(ON_RUNTIME_LINUX) || defined(ON_RUNTIME_WASM)

#if !defined(ON_SIZEOF_WCHAR_T)
#define ON_SIZEOF_WCHAR_T 4
#endif

#include <cstdint>
#if INTPTR_MAX == INT64_MAX
#define ON_64BIT_RUNTIME
#elif INTPTR_MAX == INT32_MAX
#define ON_32BIT_RUNTIME
#endif

#include <endian.h>
#if __BYTE_ORDER == __LITTLE_ENDIAN
#define ON_LITTLE_ENDIAN
#else
#define ON_BIG_ENDIAN
#endif

#endif

#if !defined(ON_64BIT_RUNTIME) && !defined(ON_32BIT_RUNTIME)
/* Attempt to determing runtime pointer size */
#if (defined(_M_X64) || defined(__LP64__) || defined(__ppc64__))
#define ON_64BIT_RUNTIME
#elif (defined(_M_X86) || defined(__LP32__))
#define ON_32BIT_RUNTIME
#endif
#endif

#if defined(ON_64BIT_RUNTIME) && defined(ON_32BIT_RUNTIME)
#error Exactly one of ON_64BIT_RUNTIME or ON_32BIT_RUNTIME must be defined.
#endif

#if !defined(ON_64BIT_RUNTIME) && !defined(ON_32BIT_RUNTIME)
#error Exactly one of ON_64BIT_RUNTIME or ON_32BIT_RUNTIME must be defined.
#endif

#if defined(ON_BIG_ENDIAN) && defined(ON_LITTLE_ENDIAN)
#error Exactly one of ON_LITTLE_ENDIAN or ON_BIG_ENDIAN should be defined.
#endif

#if !defined(ON_BIG_ENDIAN) && !defined(ON_LITTLE_ENDIAN)
#error Exactly one of ON_LITTLE_ENDIAN or ON_BIG_ENDIAN should be defined.
#endif

#if (!defined(ON_ARM_64) && (defined(__aarch64__) || defined(_M_ARM64)))
#define ON_ARM_64
#endif

/*
//
// END - Additional platform defines
//
////////////////////////////////////////////////////////////
*/

#endif
