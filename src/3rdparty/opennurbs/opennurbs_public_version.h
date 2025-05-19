#pragma once

// This file is included by BOTH RC files and C++ files
// This means you have a very limited set of preprocessor instructions
// at your disposal.

// To update version numbers, edit ..\build\build_dates.msbuild
#define RMA_VERSION_MAJOR 8
#define RMA_VERSION_MINOR 18

////////////////////////////////////////////////////////////////
//
// These are set automatically by the build system as the
// first step in each build.
//
#define RMA_VERSION_YEAR   2025
#define RMA_VERSION_MONTH  4
#define RMA_VERSION_DATE   8
#define RMA_VERSION_HOUR   11
#define RMA_VERSION_MINUTE 0

////////////////////////////////////////////////////////////////
//
// branch = 0 to 3
//   This number identifies the branch used in the build.
//
//   The build system automatically sets the value to
//   1, 2 or 3 before compiling any code.
//
//   The file checked into the source code repository
//   always has branch set to 0.
//     0 = developer build
//     1 = build system trunk build
//     2 = build system release candidate build
//     3 = build system release build
#define RMA_VERSION_BRANCH 0

#define VERSION_WITH_COMMAS  8,18,25098,11000
#define VERSION_WITH_PERIODS 8.18.25098.11000
#define COPYRIGHT "Copyright (C) 1993-2025, Robert McNeel & Associates. All Rights Reserved."
#define SPECIAL_BUILD_DESCRIPTION "Public OpenNURBS C++ 3dm file IO library."

#define RMA_VERSION_NUMBER_MAJOR_STRING   "8"
#define RMA_VERSION_NUMBER_MAJOR_WSTRING L"8"
#define RMA_PREVIOUS_VERSION_NUMBER_MAJOR_WSTRING L"7"

#define RMA_VERSION_NUMBER_SR_STRING   "SR18"
#define RMA_VERSION_NUMBER_SR_WSTRING L"SR18"

#define RMA_VERSION_WITH_PERIODS_STRING   "8.18.25098.11000"
#define RMA_VERSION_WITH_PERIODS_WSTRING L"8.18.25098.11000"



// git revision SHA-1 hash as char hexadecimal string
#define RMA_GIT_REVISION_HASH_STRING ""
#define RMA_GIT_REVISION_HASH_WSTRING L""

// git branch name as char string
#define RMA_GIT_BRANCH_NAME_STRING ""
#define RMA_GIT_BRANCH_NAME_WSTRING L""



// RHINO_FILE_FLAGS_MASK can be one or more of the following:
// VS_FF_DEBUG        - File contains debugging information or is compiled with debugging features enabled.
// VS_FF_PATCHED      - File has been modified and is not identical to the original shipping file of the same version number.
// VS_FF_PRERELEASE   - File is a development version, not a commercially released product.
// VS_FF_PRIVATEBUILD - File was not built using standard release procedures. If this value is given, the StringFileInfo block must contain a PrivateBuild string.
// VS_FF_SPECIALBUILD - File was built by the original company using standard release procedures but is a variation of the standard file of the same version number. If this value is given, the StringFileInfo block block must contain a SpecialBuild string.
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(WINDOWS) || defined(_WINDOWS_) || defined(__WINDOWS__)
#if !defined(VS_FF_PRERELEASE)
// At this time, verrsrc.h does not have protection against multiple includes.
// Testing for VS_FF_PRERELEASE seems to prevent double incudes and the
// redef errors it generates.
#include "verrsrc.h"
#endif
#endif

#define RHINO_FILE_FLAGS_MASK VS_FF_PRERELEASE


