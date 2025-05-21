#include "opennurbs.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

#define BRANCH_MAX 0x03
#define TIME_MAX   0x0FFFF


static
unsigned int ON_VersionNumberTime(
  unsigned int year,
  unsigned int month,
  unsigned int day_of_month
  )
{
  unsigned int time;
  unsigned int day_of_year;
  
  day_of_year = (year < 2100 && year >= 2000)
    ? ON_DayOfGregorianYear(year,month,day_of_month)
    : 0;

  if ( day_of_year > 0 )
  {
    time = (year - 2000)*367 + day_of_year;
  }
  else
  {
    time = 0;
  }

  return time;
}

static
bool ON_VersionNumberTimeDeconstruct(
  unsigned int time,
  unsigned int* time_year,
  unsigned int* time_month,
  unsigned int* time_day_of_month
  )
{
  unsigned int year = 0;
  unsigned int month = 0;
  unsigned int day_of_month = 0;
  unsigned int u = time;

  if (u > 0)
  {
    unsigned int day_of_year = (u%367);
    u /= 367;

    if (day_of_year > 0 && u < 100)
    {
      year = u + 2000;
      if ( !ON_GetGregorianMonthAndDayOfMonth(year,day_of_year,&month,&day_of_month) )
      {
        year = 0;
        month = 0;
        day_of_month = 0;
      }
    }
  }

  if ( 0!= time_year)
    *time_year = year;
  if ( 0!= time_month)
    *time_month = month;
  if ( 0!= time_day_of_month)
    *time_day_of_month = day_of_month;

  return (0 != month);
}

unsigned int ON_VersionNumberConstruct(
  unsigned int major_version,
  unsigned int minor_version,
  unsigned int year,
  unsigned int month,
  unsigned int day_of_month,
  unsigned int platform_branch
  )
{
  unsigned int version_number = 0;
  unsigned int version_time = ON_VersionNumberTime(year,month,day_of_month);

  if (version_time > TIME_MAX)
    version_time = TIME_MAX;

  // platform
  //   0 = developer
  //   1 = Windows Commercial/Beta/WIP
  //   2 = Mac OS Commercial/Beta/WIP
  unsigned int platform
    = (platform_branch > 0)
    ? (2 - (platform_branch % 2) )
    : 0;
  if ( platform > BRANCH_MAX )
    platform = 0; // all invalid branch numbers get mapped to "developer"
  if ( minor_version > ON::VersionMinorMaximum())
    minor_version = ON::VersionMinorMaximum();
  if ( major_version > ON::VersionMajorMaximum())
    major_version = ON::VersionMajorMaximum();
  version_number = ((major_version*(ON::VersionMinorMaximum()+1) + minor_version)*(TIME_MAX+1) + version_time)*(BRANCH_MAX+1) + platform;
  version_number |= 0x80000000;
  return version_number;
}

unsigned int ON_VersionNumberFromYearMonthDateFormat(
  unsigned int version_number_major,
  unsigned int YYYYMMDDn_version_number
  )
{
  unsigned int version_number = 0;
  if ( ON_VersionNumberIsYearMonthDateFormat(version_number_major,YYYYMMDDn_version_number) )
  {
    // convert old format to new format
    unsigned int n = (YYYYMMDDn_version_number % 10);
    unsigned int day_of_month = (YYYYMMDDn_version_number/10) % 100;
    unsigned int month = (YYYYMMDDn_version_number/1000) % 100;
    unsigned int year = (YYYYMMDDn_version_number/100000);

    unsigned int major_version = (version_number_major > 0 )
                               ? version_number_major
                               : ((n > 0 && n < 9) ? n : 5);
    unsigned int minor_version = 0;
    unsigned int branch = 0; // 0 = developer
    version_number = ON_VersionNumberConstruct(
      major_version,
      minor_version,
      year,
      month,
      day_of_month,
      branch
      );
  }
  return version_number;
}

unsigned int ON_VersionNumberMinimum(unsigned int major_version)
{
  unsigned int version_number_minimum = ON_VersionNumberConstruct(
    major_version,0,
    2000,1,1,
    0
    );
  return version_number_minimum;
}

bool ON_VersionNumberIsYearMonthDateFormat(
  unsigned int archive_3dm_version,
  unsigned int version_number
  )
{
  // Note: 
  //   When new versions of opennurbs save V2,V3,V4 or V5 files,
  //   they have to write old yyyymmddn version numbers so the
  //   old code will read the file.  In this case, n = 6,7,8,9.
  //   (n=9 meant debug prior to 2014);
  //
  //   200012210 is the earliest known opennurbs version number
  bool rc = false;
  unsigned int min_old_format_year = 2000;
  unsigned int max_old_format_year = 2100;
  if (    version_number >= min_old_format_year*100000 + 1010 
       && version_number < max_old_format_year*100000 
     )
  {
    unsigned int day_of_month = (version_number/10) % 100;
    unsigned int month = (version_number/1000) % 100;
    unsigned int year = (version_number/100000);
    if (    year >= min_old_format_year 
         && year < max_old_format_year
         && month >= 1 && month <= 12
         && day_of_month >= 1 && day_of_month <= ON_DaysInMonthOfGregorianYear(year,month)
       )
    {
      unsigned int version_major = (archive_3dm_version >= 50 && 0 == (archive_3dm_version%10)) ? (archive_3dm_version/10) : archive_3dm_version;
      // valid yyyy-mm-dd - check n
      unsigned int n = version_number%10;

      if (0 == n && 200612060 == version_number)
        n = 5; // bug in 32-bit Rhino 5 SR12 SDK version number (2006 is also a bogus year for V5!)
      else if ( 9 == n && year <= 2016 )
      {
        // 9 was used by debug builds in V2, V3, V4 and V5.
        n = version_major;
      }

      if (    (0 != n && n == version_major)
           || (n <= 4 && year <= 2011)
           || (5==n && year >= 2006)
           || (6==n && year >= 2012)
           || (n>=7 && year >= 2018)
         )
      {
        rc = true;
      }
    }
  }
  return rc;
}




bool ON_VersionNumberIsValid(
  unsigned int version_number
  )
{
  bool rc = ( version_number >= ON_VersionNumberMinimum(1) );
  if (rc)
  {
    unsigned int version_major = 0;
    unsigned int version_minor = 0;
    unsigned int version_branch = 0;
    unsigned int version_year = 0;
    unsigned int version_month = 0;
    unsigned int version_day_of_month = 0;
    rc = ON_VersionNumberParse(
      version_number,
      &version_major,
      &version_minor,
      &version_year,
      &version_month,
      &version_day_of_month,
      &version_branch
      );
    if (rc)
    {
      const unsigned int v = ON_VersionNumberConstruct(version_major,version_minor,version_year,version_month,version_day_of_month,version_branch);
      if ( v != version_number )
        rc = false;
    }
  }

  return rc;
}

bool ON_VersionNumberParse(
  unsigned int version_number,
  unsigned int* version_major,
  unsigned int* version_minor,
  unsigned int* version_year,
  unsigned int* version_month,
  unsigned int* version_day_of_month,
  unsigned int* version_branch
  )
{
  unsigned int u;
  unsigned int version_time;
  unsigned int max;
  bool rc;

  u = version_number;

  if ( ON_VersionNumberIsYearMonthDateFormat(0,u) )
  {
    unsigned int n = u%10;
    u /= 10;
    unsigned int dd = u % 100;
    u /= 100;
    unsigned int mm = u %100;
    u /= 100;
    if (0 == n && 200612060 == version_number)
      n = 5;  // 32-bit Rhino V5 SR12 version number bug
    else if (0 == n)
      n = 2;
    else if ( 9 == n && u < 2017 )
      n = 5; // debug maps to 5
    u = ON_VersionNumberConstruct(n,0,u,mm,dd,0);
  }

  if ( 0 == (0x80000000 & u) )
  {
    // This number was not created by ON_VersionNumberConstruct()
    u = 0;
  }
  else
  {
    // Clear the bit that makes new version numbers
    // created ON_VersionNumberConstruct()
    // bigger than old yyyymmddn version numbers.
    u &= 0x7FFFFFFF;
  }

  max = BRANCH_MAX+1;
  if ( 0 != version_branch )
    *version_branch = u % max;
  u /= max;

  max = TIME_MAX+1;
  version_time = u % max;
  u /= max;

  rc = ON_VersionNumberTimeDeconstruct(
    version_time,
    version_year,
    version_month,
    version_day_of_month);

  max = ON::VersionMinorMaximum()+1;
  if ( 0 != version_minor )
    *version_minor = u % max;
  u /= max;

  if ( 0 != version_major )
    *version_major = u;

  return rc;
}

const ON_String ON_VersionNumberToString(
  unsigned int version_number,
  bool bUnsignedFormat,
  bool bDateFormat
)
{
  unsigned int version_major = 0;
  unsigned int version_minor = 0;
  unsigned int version_year = 0;
  unsigned int version_month = 0;
  unsigned int version_day_of_month = 0;
  unsigned int version_branch = 0;

  if (false == ON_VersionNumberIsValid(version_number))
  {
    bUnsignedFormat = false;
    bDateFormat = false;
  }
  else if (bDateFormat)
  {
    bDateFormat = ON_VersionNumberParse(
      version_number,
      &version_major,
      &version_minor,
      &version_year,
      &version_month,
      &version_day_of_month,
      &version_branch
    );
  }

  ON_String str_version;
  if (bUnsignedFormat)
  {
    str_version = ON_String::FormatToString("%u", version_number);
    if (bDateFormat)
      str_version += " (";
  }

  if (bDateFormat)
  {
    str_version += ON_String::FormatToString(
      "%u.%u %04u-%02u-%02u:%u", 
    version_major,
    version_minor, 
    version_year, 
    version_month, 
    version_day_of_month,
    version_branch
    );
    if (bUnsignedFormat)
      str_version += ")";
  }

  if (str_version.IsEmpty())
  {
    str_version =
      (0 != version_number)
      ? ON_String::FormatToString("0x%08X", version_number)
      : "0";
  }

  return str_version;
}

const ON_wString ON_VersionNumberToWideString(
  unsigned int version_number,
  bool bUnsignedFormat,
  bool bDateFormat
)
{
  return ON_wString(ON_VersionNumberToString(version_number, bUnsignedFormat, bDateFormat));
}

const ON_String ON_SdkVersionNumberToString(
  unsigned int sdk_version_number,
  unsigned int sdk_service_release_number
)
{
  const bool bValidVersionNumber = ON_VersionNumberIsValid(sdk_version_number);
  const bool bValidServiceReleaseNumber = ON_VersionNumberIsValid(sdk_service_release_number);
  ON_String str_version = ON_VersionNumberToString(sdk_version_number, true, false);
  str_version += ".";
  str_version += ON_VersionNumberToString(sdk_service_release_number, true, false);
  if (bValidVersionNumber || bValidServiceReleaseNumber)
  {
    str_version += " (";
    if (bValidVersionNumber != bValidServiceReleaseNumber || sdk_version_number == sdk_service_release_number )
    {
      str_version += ON_VersionNumberToString(bValidVersionNumber ? sdk_version_number : sdk_service_release_number, false, true);
    }
    else
    {
      str_version += ON_VersionNumberToString(sdk_version_number, false, true);
      str_version += ", ";
      str_version += ON_VersionNumberToString(sdk_service_release_number, false, true);
    }
    str_version += ")";
  }
  return str_version;
}

const ON_wString ON_SdkVersionNumberToWideString(
  unsigned int sdk_version_number,
  unsigned int sdk_service_release_number
)
{
  return ON_wString(ON_SdkVersionNumberToString(sdk_version_number, sdk_service_release_number));
}


static
unsigned int AppendValueToString(
  unsigned int u,
  size_t string_buffer_capacity,
  char* string_buffer
  )
{
  unsigned int digit_count = 0;
  unsigned int i;

  if ( string_buffer_capacity > 0 && 0 != string_buffer )
  {
    i = u;
    for(;;)
    {
      digit_count++;
      i /= 10;
      if ( i < 1 )
        break;
    }

    if ( digit_count >= string_buffer_capacity )
      digit_count = 0;
    else
    {
      i = digit_count;
      string_buffer[i] = 0;
      for (;;)
      {
        i--;
        string_buffer[i] = (u % 10) + '0';
        u /= 10;
        if ( u < 1 )
          break;
      }
    }
  }

  return digit_count;
}

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
  )
{
  unsigned int i;
  unsigned int item_value;
  unsigned int version_number = ON_VersionNumberConstruct(
                                      major_version,
                                      minor_version,
                                      year,
                                      month,
                                      day_of_month,
                                      branch
                                      );

  if ( hour >= 24 || minute >= 60 )
  {
    if ( 24 == hour && 0 == minute )
    {
      // leap second
      hour = 23;
      minute = 60;
    }
    if ( 23 != hour || 60 != minute )
    {
      hour = 0;
      minute = 0;
    }
  }

  for(i = 0; i < 4; i++ )
  {
    switch(i)
    {
    case 0:
      item_value = major_version;
      break;
    case 1:
      item_value = minor_version;
      break;
    case 2:
      item_value = (year-2000)*1000 + ON_DayOfGregorianYear(year,month,day_of_month);
      break;
    case 3:
      item_value = (hour*100 + minute)*10 + branch;
      break;
    default:
      continue;
      break;
    }

    if ( item_value > 0xFFFF )
    {
      version_number = 0;
      item_value = 0;
    }

    quartet_values[i] = (unsigned short)item_value;
  }

  return version_number;
}

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
  )
{
  char s[24] = {0};
  const size_t s_capacity = sizeof(s)/sizeof(s[0]);
  unsigned int string_length = 0;
  unsigned int i, j;
  unsigned short quartet_values[4] = {0};
  unsigned int version_number = ON_GetVersionQuartet(
                                      major_version,
                                      minor_version,
                                      year,
                                      month,
                                      day_of_month,
                                      hour,
                                      minute,
                                      branch,
                                      quartet_values
                                      );

  if (string_buffer_capacity <= 0 || nullptr == string_buffer)
  {
    string_buffer_capacity = s_capacity;
    string_buffer = s;
  }

  if ( version_number > 0 )
  {
    for(i = 0; i < 4 && string_length < string_buffer_capacity; i++ )
    {
      if ( i > 0 )
        string_buffer[string_length++] = '.';

      j = AppendValueToString(
        quartet_values[i],
        string_buffer_capacity - string_length,
        string_buffer + string_length
        );

      if ( j <= 0 )
      {
        string_length = 0;
        break;
      }

      string_length += j;

    }
  }

  if ( string_length > string_buffer_capacity )
    string_length = 0;

  for ( i = string_length; i < string_buffer_capacity; i++ )
    string_buffer[i] = 0;

  return string_length;
}

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
  )
{
  char s[24] = {0};
  const size_t s_capacity = sizeof(s)/sizeof(s[0]);
  unsigned int string_length;
  unsigned int i;

  string_length = ON_GetVersionString(
                    major_version,
                    minor_version,
                    year,
                    month,
                    day_of_month,
                    hour,
                    minute,
                    branch,
                    s_capacity, s
                    );
  
  if (string_buffer_capacity > 0 && nullptr != string_buffer)
  {
    if (((size_t)string_length) <= string_buffer_capacity)
    {
      for (i = 0; i < string_length && 0 != s[i]; i++)
      {
        string_buffer[i] = s[i];
      }
    }
    else
    {
      string_length = 0;
      i = 0;
    }

    while (i < string_buffer_capacity)
      string_buffer[i++] = 0;
  }
  
  return string_length;
}






