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

#if !defined(OPENNURBS_VERSION_NUMBER_INC_)
#define OPENNURBS_VERSION_NUMBER_INC_

/*
Description:
  Create a 4-byte unsigned integer value that has desirable version 
  number properties.

Parameters:
  major_version - [in]
    major_version >= 0 and major_version <= 63

  minor_version - [in]
    minor_version >= 0 and minor_version <= 127

  year - [in]
    year >= 2000 and year <= 2099

  month - [in]
    month >= 1 and month <= 12

  day_of_month - [in]
    day_of_month >= 1 and day_of_month <= ON_DaysInMonthOfGregorianYear(year,month)

  platform_branch - [in]
    0: developer build
    1: Windows Commercial build
    2: Mac Commercial build
    3: Windows BETA build
    4: Mac Beta build
    5: Windows WIP build
    6: Mac WIP build

Returns:
  If the input values are valid, this returns
  a 4-byte nonzero version number with the following properties:
  verA = ON_VersionNumberConstruct(majorA,minorA,<timeA>,branchA)
  verB = ON_VersionNumberConstruct(majorB,minorB,<timeB>,branchB)
  - If majorA > majorB, then verA > verB.
  - If majorA = majorB and minorA > minorB, then verA > verB.
  - If majorA = majorB and minorA = minorB and 
    timeA > timeB, then verA > verB.
  - If majorA = majorB, minorA = minorB, timeA = timeB, and
    branchA > branchB, then verA > verB.
  If any input is not valid, then zero is returned.
*/
ON_DECL
unsigned int ON_VersionNumberConstruct(
  unsigned int major_version,
  unsigned int minor_version,
  unsigned int year,
  unsigned int month,
  unsigned int day_of_month,
  unsigned int platform_branch
  );

/*
Parameters:
  major_version - [in]
    major_version >= 0 and major_version <= 63

Returns:
  The smallest possible non-zero version number
  ON_VersionNumberConstruct() will create
  for a specified major version with valid input.
*/
ON_DECL
unsigned int ON_VersionNumberMinimum(
  unsigned int major_version
  );

/*
Returns:
  True if the version_number is a value created by
  ON_VersionNumberConstruct().
Parameters:
  version_number - [in]
*/
ON_DECL
bool ON_VersionNumberIsValid(
  unsigned int version_number
  );

/*
Parameters:
  archive_3dm_version - [in]
    If the context of the query is a version number from
    an ON_BinaryArchive, then pass the value
    of ON_BinaryArchive.Archive3dmVersion() here.
  version_number - [in]
    version number to test.
Returns:
  True if the version number is in the
  YYYYMMDDn format used by version 1,2,3,4,5
  of opennurbs and the Rhino SDK.
*/
ON_DECL
bool ON_VersionNumberIsYearMonthDateFormat(
  unsigned int archive_3dm_version,
  unsigned int version_number
  );

/*
Parameters:
  major_version - [in]
    >= 0 and < 64
Returns:
  The smallest possible non-zero version number
  ON_VersionNumberConstruct() will create
  for a specified major version with valid input.
*/
ON_DECL
unsigned int ON_VersionNumberFromYearMonthDateFormat(
  unsigned int major_version,
  unsigned int yyyy_mm_dd_n_version_number
  );

/*
Description:
  Parse a version number created by ON_VersionNumberConstruct() to
  recover the input parameters.
Parameters:
  version_number - [in]
    A version number created with ON_VersionNumberConstruct().

  version_major - [out]
    version_major >= 0 and version_major <= 63

  version_minor - [out]
    version_minor >= 0 and version_minor <= 127

  version_year - [out]
    version_year >= 2000 and version_year <= 2099

  version_month - [out]
    version_month >= 1 and version_month <= 12

  version_day_of_month - [out]
    version_day_of_month >= 1 and version_day_of_month <= ON_DaysInMonthOfGregorianYear(year,month)

  version_branch - [out]
    version_branch >= 0 and version_branch <= 3
    0: developer build
    1: build system trunk branch build
    2: build system release candidate build
    3: build system release build

Remarks:
  Any output parameter pointer may be null if you do not want that
  information.

Returns:
  true:
    The version_number parameter is a valid version number.
    All output parameters are set.
  false:
    The version_number parameter is not a valid version number.
    All output parameters are set to zero.
*/
ON_DECL
bool ON_VersionNumberParse(
  unsigned int version_number,
  unsigned int* version_major,
  unsigned int* version_minor,
  unsigned int* version_year,
  unsigned int* version_month,
  unsigned int* version_day_of_month,
  unsigned int* version_branch
  );

/*
Description:
  A tool to validate version information and to test opennurbs version number encoding and parsing.
Parameters:
  major
    A value between 1 and ON::VersionMajorMaximum().
  minor,
    A value between 0 and ON::VersionMinorMaximum().
  year
    A value between 2000 and 2099
  month
    A value between 1 and 12
  day_of_month
    A value between 1 and ON_DaysInMonthOfGregorianYear(year, month).
  platform_branch
    0: developer build
    >= 1: some type of build system build
  version_as_unsigned_number
    Either 0 or the encoded version number to test against the previous parameters.
Returns:
  true 
    Input parameters are valid and testing internal version number utilities passed.
  false
    Input parameters are not valid or a bug was detected in internal version number utilities.
*/
ON_DECL
bool ON_TestVersionNumber(
  unsigned int major,
  unsigned int minor,
  unsigned int year,
  unsigned int month,
  unsigned int day_of_month,
  unsigned int platform_branch,
  unsigned int version_as_unsigned_number
);

ON_DECL
const ON_String ON_VersionNumberToString(
  unsigned int version_number,
  bool bUnsignedFormat,
  bool bDateFormat
);

ON_DECL
const ON_wString ON_VersionNumberToWideString(
  unsigned int version_number,
  bool bUnsignedFormat,
  bool bDateFormat
);

ON_DECL
const ON_String ON_SdkVersionNumberToString(
  unsigned int sdk_version_number,
  unsigned int sdk_service_release_number
);

ON_DECL
const ON_wString ON_SdkVersionNumberToWideString(
  unsigned int sdk_version_number,
  unsigned int sdk_service_release_number
);

/*
Parameters:
  major_version - [in]
    major_version >= 0 and major_version <= 63

  minor_version - [in]
    minor_version >= 0 and minor_version <= 127

  year - [in]
    year >= 2000 and year <= 2099

  month - [in]
    month >= 1 and month <= 12

  day_of_month - [in]
    day_of_month >= 1 and day_of_month <= ON_DaysInMonthOfGregorianYear(year,month)

  hour - [in]
    hour >= 0 and hour <= 23

  minute - [in]
    minute >= 0 and minute <= 59

  branch - [in]
    branch >= 0 and branch <= 3
    0: developer build
    1: build system trunk branch build
    2: build system release candidate build
    3: build system release build

  quartet_values - [out]
    quartet_values[0] = major_version
    quartet_values[1] = minor_version
    quartet_values[2] = (year-2000)*1000 + ON_DayOfGregorianYear(year,month,day_of_month)
    quartet_values[3] = hour*1000 + minute*100 + branch

Returns:
  0: failure because input is not valid
  >0: value of ON_VersionNumberConstruct(major_version,minor_version,year,month,day_of_month,branch)
*/
ON_DECL
unsigned int ON_GetVersionQuartet(
  unsigned int major_version,
  unsigned int minor_version,
  unsigned int year,
  unsigned int month,
  unsigned int day_of_month,
  unsigned int hour,
  unsigned int minute,
  unsigned int branch,
  unsigned short quartet_values[4]
  );

/*
Description:
  Get a null terminated string that describes the version information
  as "major.,minor.yyddd.hhmmb".
Parameters:
  major_version - [in]
    major_version >= 0 and major_version <= 63

  minor_version - [in]
    minor_version >= 0 and minor_version <= 127

  year - [in]
    year >= 2000 and year <= 2099

  month - [in]
    month >= 1 and month <= 12

  day_of_month - [in]
    day_of_month >= 1 and day_of_month <= ON_DaysInMonthOfGregorianYear(year,month)

  hour - [in]
    hour >= 0 and hour <= 23

  minute - [in]
    minute >= 0 and minute <= 59

  branch - [in]
    branch >= 0 and branch <= 3
    0: developer build
    1: build system trunk branch build
    2: build system release candidate build
    3: build system release build

  string_buffer_capacity - [in]
    Number of available char elements in string_buffer[]

  string_buffer - [out]
    If 0 == string_buffer_capacity or nullptr == string_buffer, 
    then the number of char elements in the version number as a string, not including a null terminator,
    is returned and no changes are made to string_buffer.

    If string_buffer_capacity > 0 && nullptr != string_buffer, 
    then the version number as a string is returned in string_buffer. 
    All string_buffer[] elements after the version number string are set to zero.
    (This is a safe and secure string function.)
Returns:
  0: failure because input is not valid
  >0: The number of char elements, not including a null terminator, in the version number as a string.    
*/
ON_DECL
unsigned int ON_GetVersionString(
  unsigned int major_version,
  unsigned int minor_version,
  unsigned int year,
  unsigned int month,
  unsigned int day_of_month,
  unsigned int hour,
  unsigned int minute,
  unsigned int branch,
  size_t string_buffer_capacity,
  char* string_buffer
  );

/*
Description:
  Get a null terminated wide character string that describes the version information
  as "major.minor.yyddd.hhmmb".
Parameters:
  major_version - [in]
    major_version >= 0 and major_version <= 63

  minor_version - [in]
    minor_version >= 0 and minor_version <= 127

  year - [in]
    year >= 2000 and year <= 2099

  month - [in]
    month >= 1 and month <= 12

  day_of_month - [in]
    day_of_month >= 1 and day_of_month <= ON_DaysInMonthOfGregorianYear(year,month)

  hour - [in]
    hour >= 0 and hour <= 23

  minute - [in]
    minute >= 0 and minute <= 59

  branch - [in]
    branch >= 0 and branch <= 3
    0: developer build
    1: build system trunk branch build
    2: build system release candidate build
    3: build system release build

  string_buffer_capacity - [in]
    Number of available char elements in string_buffer[]

  string_buffer - [out]
    If 0 == string_buffer_capacity or nullptr == string_buffer, 
    then the number of wchar_t elements in the version number as a string, not including a null terminator,
    is returned and no changes are made to string_buffer.

    If string_buffer_capacity > 0 && nullptr != string_buffer, 
    then the version number as a string is returned in string_buffer. 
    All string_buffer[] elements after the version number string are set to zero.
    (This is a safe and secure string function.)
Returns:
  0: failure because input is not valid
  >0: The number of char elements, not including a null terminator, in the version number as a string.    
*/
ON_DECL
unsigned int ON_GetVersionWideString(
  unsigned int major_version,
  unsigned int minor_version,
  unsigned int year,
  unsigned int month,
  unsigned int day_of_month,
  unsigned int hour,
  unsigned int minute,
  unsigned int branch,
  size_t string_buffer_capacity,
  wchar_t* string_buffer
  );

#endif
