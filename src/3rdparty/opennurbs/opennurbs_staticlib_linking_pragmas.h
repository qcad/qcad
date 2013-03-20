#if defined(_MSC_VER)

// This file is specific to Micrsoft's compiler.
// It contains linking pragmas for building the opennurbs examples.

#pragma once

#if defined(ON_DLL_IMPORTS) || defined(ON_DLL_EXPORTS)
// If you get the following error, your compiler settings
// indicate you want to use opennurbs as a DLL but you
// are attempting to link in static libraries.
#error This file contains STATIC LIBRARY linking pragmas.
#endif


#if defined(WIN64)

// x64 (64 bit) static libraries

#if defined(NDEBUG)

// Release x64 (64 bit) libs
#pragma message( " --- Opennurbs examples Release x64 (64 bit) build." )
#pragma comment(lib, "../zlib/x64/Release/zlibx64.lib")
#pragma comment(lib, "../x64/ReleaseStaticLib/opennurbsx64_static.lib")

#else // _DEBUG

// Debug x64 (64 bit) libs
#pragma message( " --- Opennurbs examples Debug x64 (64 bit) build." )
#pragma comment(lib, "../zlib/x64/Debug/zlibx64_d.lib")
#pragma comment(lib, "../x64/DebugStaticLib/opennurbsx64_staticd.lib")

#endif // NDEBUG else _DEBUG

#else // WIN32

// x86 (32 bit) static libraries

#if defined(NDEBUG)

// Release x86 (32 bit) libs
#pragma message( " --- Opennurbs examples Release x86 (32 bit) build." )
#pragma comment(lib, "../zlib/Release/zlib.lib")
#pragma comment(lib, "../ReleaseStaticLib/opennurbs_static.lib")

#else // _DEBUG

// Debug x86 (32 bit) libs
#pragma message( " --- Opennurbs examples Debug x86 (32 bit) build." )
#pragma comment(lib, "../zlib/Debug/zlib_d.lib")
#pragma comment(lib, "../DebugStaticLib/opennurbs_staticd.lib")

#endif // NDEBUG else _DEBUG

#endif // WIN64 else WIN32

#endif
