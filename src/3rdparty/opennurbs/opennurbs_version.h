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

#if !defined(OPENNURBS_VERSION_INC_)
#define OPENNURBS_VERSION_INC_

#if !defined(OPENNURBS_VERSION_DEFINITION)
#error Do NOT include opennurbs_version.h in your code.  Use ON::Version() instead.
#endif

////////////////////////////////////////////////////////////////
//
// Values that identify the version are defined below.
//
// The function
//   ON_VersionNumberConstruct(major,minor,year,month,day_of_month,branch)
// creates a 4-byte unsigned integer that encodes the version information.
//
// The function
//   ON_GetVersionNumberStringConstruct()
// creates a "major.minor.yyddd.hhmmb" version string
// where ddd = day of year (1 to 366).
//
// The function
//   ON_GetVersionNumberQuarted()
// returns an array of 4 unsigned short values
//   (major,minor,yyddd,hhmmb)
// where ddd = day of year (1 to 366).


#include "opennurbs_public_version.h"


#define OPENNURBS_MAX_VERSION_MINOR  0x07F
#define OPENNURBS_MAX_VERSION_MAJOR  0x03F

////////////////////////////////////////////////////////////////
//
// Major version number >= 0 and <= 63
// Minor version number >= 0 and <= 127
//

#define OPENNURBS_VERSION_MAJOR RMA_VERSION_MAJOR
#define OPENNURBS_VERSION_MINOR RMA_VERSION_MINOR

////////////////////////////////////////////////////////////////
//
// The five OPENNURBS_VERSION_... time defines are set
// automatically by the build system as the first step
// in each build.
//

#define OPENNURBS_VERSION_YEAR         RMA_VERSION_YEAR
#define OPENNURBS_VERSION_MONTH        RMA_VERSION_MONTH
#define OPENNURBS_VERSION_DAY_OF_MONTH RMA_VERSION_DATE
#define OPENNURBS_VERSION_HOUR         RMA_VERSION_HOUR
#define OPENNURBS_VERSION_MINUTE       RMA_VERSION_MINUTE

////////////////////////////////////////////////////////////////
//
// branch => 0
// Use ON::VersionBranch() to get this value.
//   This number identifies the branch used in the build.
//
//   The build system automatically sets the value before compiling any code.
//
//   The file checked into the source code repository
//   always has branch set to 0.
//
//  RMA_VERSION_BRANCH is defined in opennurbs_version.h
//    0: developer build
//    1: Windows Commercial build
//    2: Mac Commercial build
//    3: Windows BETA build
//    4: Mac Beta build
//    5: Windows WIP build
//    6: Mac WIP build
//#define OPENNURBS_VERSION_BRANCH 0

#define OPENNURBS_VERSION_BRANCH RMA_VERSION_BRANCH

////////////////////////////////////////////////////////////////
//
// The build process modifies version.h and sets
// RMA_SRC_SVN_REVISION = "<git revision SHA-1 hash>"
// before compiling applications.
//

#define OPENNURBS_GIT_REVISION_HASH RMA_GIT_REVISION_HASH_STRING
#define OPENNURBS_GIT_BRANCH_NAME RMA_GIT_BRANCH_NAME_STRING

////////////////////////////////////////////////////////////////
//
// OPENNURBS_VERSION_QUARTET_STRING is a macro whose value is the
// opennurbs version quartet as a string.
//
#define OPENNURBS_VERSION_QUARTET_STRING  RMA_VERSION_WITH_PERIODS_STRING
#define OPENNURBS_VERSION_QUARTET_WSTRING RMA_VERSION_WITH_PERIODS_WSTRING
#define OPENNURBS_VERSION_QUARTET_WITH_COMMAS VERSION_WITH_COMMAS
#define OPENNURBS_VERSION_QUARTET_WITH_PERIODS VERSION_WITH_PERIODS

////////////////////////////////////////////////////////////////
//
// ON_VERSION_NUMBER_FEBDAYS(year) is a macro whose value is
// the number of days in the month of February in a specified
// year.
//
// In almost every situation, it is best to used the function
// call ON_DaysInMonthOfGregorianYear(year,2) to get this value.
// The ON_VERSION_NUMBER_FEBDAYS macro is for rare and unusual
// situations where the C preprocessor needs this value.
//
#define ON_VERSION_NUMBER_FEBDAYS(year) \
    (((year) % 400) == 0 ? 29 : \
        (((year) % 100) == 0 ? 28 : \
            (((year) % 4) == 0 ? 29 : \
                28)))

////////////////////////////////////////////////////////////////
//
// ON_VERSION_NUMBER_DAYOFYEAR(year, month, day_of_month) is a macro
// whose value is the cardinal day of the year for the
// specified year, month and day_of_month.
//
// In almost every situation, it is best to used the function call
// ON_DayOfGregorianYear(year,month,day_of_month) to get this value.
// The ON_VERSION_NUMBER_DAYOFYEAR macro is for rare and unusual
// situations where the C preprocessor needs this value.
//
#define ON_VERSION_NUMBER_DAYOFYEAR(year, month, day_of_month) \
    ( (day_of_month) \
      + ((month) >=  2 ? 31 : 0) \
      + ((month) >=  3 ? ON_VERSION_NUMBER_FEBDAYS(year) : 0) \
      + ((month) >=  4 ? 31 : 0) \
      + ((month) >=  5 ? 30 : 0) \
      + ((month) >=  6 ? 31 : 0) \
      + ((month) >=  7 ? 30 : 0) \
      + ((month) >=  8 ? 31 : 0) \
      + ((month) >=  9 ? 31 : 0) \
      + ((month) >= 10 ? 30 : 0) \
      + ((month) >= 11 ? 31 : 0) \
      + ((month) >= 12 ? 30 : 0) \
    )

#define ON_VERSION_NUMBER_TIME(year, month, day_of_month) \
  ((((year)-2000)*367) + (ON_VERSION_NUMBER_DAYOFYEAR(year,month,day_of_month)))

// branch is 0 for developer builds, odd for windows builds, and even for Mac builds
// When compressed into 2 bits, the type of build (Commercial/Beta/WIP) is not encoded.
//
//  branch
//    0: developer build
//    1: Windows Commercial build
//    2: Mac Commercial build
//    3: Windows BETA build
//    4: Mac Beta build
//    5: Windows WIP build
//    6: Mac WIP build
//
// ON_VERSION_NUMBER_PLATFORM_ID(branch) =
// = 0: developer build
//   1: Windows build
//   2: Mac build
//
// NOTE WELL:
//   ON_VERSION_NUMBER_PLATFORM_ID(branch) must be a value between 0 and 3.
#define ON_VERSION_NUMBER_PLATFORM_ID(branch) \
   (((branch) > 0x0U) ? (0x02U - ((branch) % 0x02U)) : 0x0U)

////////////////////////////////////////////////////////////////
//
// ON_VERSION_NUMBER_CTOR(major,minor,year,month,day_of_month,branch)
// is a macro whose value is the opennurbs version number encoding
// for the specified major, minor, year, month and day_of_month
// values.
//
// In almost every situation, it is best to used the function call
// ON_VersionNumberConstruct(major,minor,year,month,day_of_month,branch)
// to get this value.  The ON_VERSION_NUMBER_CTOR macro is for
// rare and unusual situations where the C preprocessor needs
// this value.
//
#define ON_VERSION_NUMBER_CTOR(major,minor,year,month,day_of_month,branch) \
  (0x80000000U \
  + ((((major)*0x080U + (minor)))*0x010000U \
  + ((ON_VERSION_NUMBER_TIME(year,month,day_of_month))))*0x04U \
  + ((ON_VERSION_NUMBER_PLATFORM_ID(branch))))

////////////////////////////////////////////////////////////////
//
// OPENNURBS_VERSION_NUMBER is a macro whose value is the
// opennurbs version number.
//
// Always use ON::Version() when you need this value.
// The OPENNURBS_VERSION_NUMBER macro is for rare and unusual
// situations where the C preprocessor needs this value.
//
#define OPENNURBS_VERSION_NUMBER ON_VERSION_NUMBER_CTOR( \
          OPENNURBS_VERSION_MAJOR, OPENNURBS_VERSION_MINOR, \
          OPENNURBS_VERSION_YEAR, OPENNURBS_VERSION_MONTH, OPENNURBS_VERSION_DAY_OF_MONTH, \
          OPENNURBS_VERSION_BRANCH )

// Jan 2017
//  November 2016 Rhino 7 WIP writes version 6 files.
//  October 23 1019, Rhino 7 WIP writes version 7 files.
//  May 17 2021, Rhino 8 WIP writes version 8 files.
//
// More generally, in a stable release product, OPENNURBS_CURRENT_ARCHIVE_VERSION = OPENNURBS_VERSION_MAJOR*10.
// But for some period of time at the beginning of the Rhino (N+1) WIP development cycle,
// Rhino (N+1) WIP writes Rhino N files. That's why OPENNURBS_CURRENT_ARCHIVE_VERSION
// is sometimes (OPENNURBS_VERSION_MAJOR*10) and is sometimes ((OPENNURBS_VERSION_MAJOR-1)*10)
#define OPENNURBS_CURRENT_ARCHIVE_VERSION 80

#endif
