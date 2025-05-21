/*
//
// Copyright (c) 1993-2016 Robert McNeel & Associates. All rights reserved.
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
*/

#if !defined(OPENNURBS_INPUT_LIBSDIR_INC_)
#define OPENNURBS_INPUT_LIBSDIR_INC_



// RH-86025, RH3DM-179, 2025-02-14, Pierre:
// ON_CMAKE_BUILD should be renamed "ON_NOT_USING_MSVC_LINK_LIB_PRAGMA"
// This whole thing should be reworked so MSVC builds also use build properties,
// instead of the non-portable #pragma comment(lib, "path").
#if defined(ON_COMPILER_MSC) && !defined(OPENNURBS_INPUT_LIBS_DIR) && !defined(ON_CMAKE_BUILD)

// This header file insures OPENNURBS_INPUT_LIBS_DIR is defined to be
// the path to were the libraries opennurbs.dll links with are located.
// Examples of these libraries are zlib and freetype.

#if defined(OPENNURBS_OUTPUT_DIR)
// Typically, OPENNURBS_OUTPUT_DIR is defined in the 
// MSBuild property sheet opennurbs_msbuild.Cpp.props.
#define OPENNURBS_INPUT_LIBS_DIR OPENNURBS_OUTPUT_DIR
#elif defined(RHINO_LIB_DIR)
// Typically, RHINO_LIB_DIR is defined in a Rhino module property sheet.
#define OPENNURBS_INPUT_LIBS_DIR RHINO_LIB_DIR
#else

// Please define OPENNURBS_INPUT_LIBS_DIR in your build environment 
// Please do not modify the opennurbs vcxproj files. Instead use
// a property sheet (.props file), .sln file, or define it here.
#error You must define OPENNURBS_INPUT_LIBS_DIR

#endif

#endif

#endif
