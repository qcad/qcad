#if defined(ON_COMPILER_MSC)

// This file is specific to Micrsoft's compiler.
// It contains linking pragmas for building the opennurbs examples.

#pragma once

#if defined(OPENNURBS_EXPORTS) || defined(ON_COMPILING_OPENNURBS)
// If you get the following error, your compiler settings
// indicate you are building an opennurbs library.
// This file is used for linking with opennurbs libraries
// that have been previously built.
#error This file contains linking pragmas for using the opennurbs library.
#endif

#if defined(OPENNURBS_IMPORTS)
#pragma message( " --- dynamically linking opennurbs (DLL)." )
#pragma comment(lib, "\"" OPENNURBS_OUTPUT_DIR "/" "opennurbs_public.lib" "\"")
#else
#pragma message( " --- statically linking opennurbs." )
#pragma comment(lib, "\"" OPENNURBS_OUTPUT_DIR "/" "opennurbs_public_staticlib.lib" "\"")
#pragma comment(lib, "\"" OPENNURBS_OUTPUT_DIR "/" "zlib.lib" "\"")
#if defined(OPENNURBS_FREETYPE_SUPPORT)
#pragma comment(lib, "\"" OPENNURBS_OUTPUT_DIR "/" "freetype263.lib" "\"")
#endif
#pragma comment(lib, "rpcrt4.lib")
#pragma comment(lib, "shlwapi.lib")
#endif

#endif
