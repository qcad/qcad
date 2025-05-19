#include "opennurbs.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

#define OPENNURBS_VERSION_DEFINITION
#include "opennurbs_version.h"
#undef OPENNURBS_VERSION_DEFINITION

unsigned int ON::Version()
{
  static unsigned int version_number = 0;
  if ( 0 == version_number )
  {
    version_number = ON_VersionNumberConstruct(
      OPENNURBS_VERSION_MAJOR,
      OPENNURBS_VERSION_MINOR,
      OPENNURBS_VERSION_YEAR,
      OPENNURBS_VERSION_MONTH,
      OPENNURBS_VERSION_DAY_OF_MONTH,
      OPENNURBS_VERSION_BRANCH
      );
    const unsigned int macro_version_number = OPENNURBS_VERSION_NUMBER;
    if ( macro_version_number != version_number )
    {
      ON_ERROR("Fix ON_VERSION_... defines in openurbs_version.h");
    }
  }
  return version_number;
}

unsigned int ON::VersionMajorMaximum()
{
  return OPENNURBS_MAX_VERSION_MAJOR;
}

unsigned int ON::VersionMinorMaximum()
{
  return OPENNURBS_MAX_VERSION_MINOR;
}

unsigned int ON::VersionMajor()
{
  return OPENNURBS_VERSION_MAJOR;
}

unsigned int ON::VersionMinor()
{
  return OPENNURBS_VERSION_MINOR;
}

unsigned int ON::VersionYear()
{
  return OPENNURBS_VERSION_YEAR;
}

unsigned int ON::VersionMonth()
{
  return OPENNURBS_VERSION_MONTH;
}

unsigned int ON::VersionDayOfMonth()
{
  return OPENNURBS_VERSION_DAY_OF_MONTH;
}
  
unsigned int ON::VersionHour()
{
  return OPENNURBS_VERSION_HOUR;
}
  
unsigned int ON::VersionMinute()
{
  return OPENNURBS_VERSION_MINUTE;
}

unsigned int ON::VersionBranch()
{
  return OPENNURBS_VERSION_BRANCH;
}

const char* ON::SourceGitRevisionHash()
{
#if defined(OPENNURBS_GIT_REVISION_HASH)
  const char* hash = OPENNURBS_GIT_REVISION_HASH;
  if (nullptr != hash && '0' == hash[0] && 0 == hash[1])
    hash = nullptr;
  if ( nullptr != hash && 0 != hash[0])
    return OPENNURBS_GIT_REVISION_HASH;
#endif
  return "";
}

const char* ON::SourceGitBranchName()
{
#if defined(OPENNURBS_GIT_BRANCH_NAME)
  const char* name = OPENNURBS_GIT_BRANCH_NAME;
  if (nullptr != name && '0' == name[0] && 0 == name[1])
    name = nullptr;
  if (nullptr != name && 0 != name[0])
    return OPENNURBS_GIT_BRANCH_NAME;
#endif
  return "";
}

const char* ON::SourceIdentification()
{
#if defined(OPENNURBS_GIT_BRANCH_NAME) && defined(OPENNURBS_GIT_BRANCH_NAME)
  // As version control systems change, this
  // function will be updated to return some appropriate string value.
  // Developer builds currently return "".
  const char* name = OPENNURBS_GIT_BRANCH_NAME;
  if (nullptr != name && '0' == name[0] && 0 == name[1])
    name = nullptr;
  const char* hash = OPENNURBS_GIT_REVISION_HASH;
  if (nullptr != hash && '0' == hash[0] && 0 == hash[1])
    hash = nullptr;
  if (nullptr != hash && 0 != hash[0])
  {
    return
      (nullptr != name && 0 != name[0])
      ? (OPENNURBS_GIT_BRANCH_NAME " @ " OPENNURBS_GIT_REVISION_HASH)
      : "master @ " OPENNURBS_GIT_REVISION_HASH;
  }
  if (nullptr != name && 0 != name[0])
  {
    return OPENNURBS_GIT_BRANCH_NAME;
  }
#endif
  return "";
}

unsigned int ON::VersionGetQuartet(
  unsigned int opennurbs_version_quartet[4]
  )
{
  const unsigned int v[4] = {OPENNURBS_VERSION_QUARTET_WITH_COMMAS};
  if ( opennurbs_version_quartet )
  {
    opennurbs_version_quartet[0] = v[0];
    opennurbs_version_quartet[1] = v[1];
    opennurbs_version_quartet[2] = v[2];
    opennurbs_version_quartet[3] = v[3];
  }
  return OPENNURBS_VERSION_NUMBER;
}

const char* ON::VersionQuartetAsString()
{
  return OPENNURBS_VERSION_QUARTET_STRING;
}

const wchar_t* ON::VersionQuartetAsWideString()
{
  return OPENNURBS_VERSION_QUARTET_WSTRING;
}

int ON_BinaryArchive::CurrentArchiveVersion()
{
  // Latest version of opennurbs binary archives supported by
  // this version of opennurbs.
  return OPENNURBS_CURRENT_ARCHIVE_VERSION;
}


bool ON_TestVersionNumber(
  unsigned int major,
  unsigned int minor,
  unsigned int year,
  unsigned int month,
  unsigned int day_of_month,
  unsigned int platform_branch,
  unsigned int version_as_unsigned_number
)
{
  for (;;)
  {
    if (major < 1 || major > OPENNURBS_MAX_VERSION_MAJOR)
    {
      ON_ERROR("Invalid major parameter");
      break;
    }
    if (minor > OPENNURBS_MAX_VERSION_MINOR)
    {
      ON_ERROR("Invalid minor parameter");
      break;
    }
    if (year < 2000 || year >= 2099)
    {
      ON_ERROR("Invalid year parameter");
      break;
    }
    if (month < 1 || month > 12)
    {
      ON_ERROR("Invalid month parameter");
      break;
    }
    const unsigned int max_day_of_month = ON_DaysInMonthOfGregorianYear(year, month);
    if (2 == month)
    {
      if (max_day_of_month != 28)
      {
        if (max_day_of_month != 29 || 0 != (year % 4))
        {
          ON_ERROR("ON_DaysInMonthOfGregorianYear() has bug");
          break;
        }
      }
    }
    else
    {
      if (max_day_of_month != 30 && max_day_of_month != 31)
      {
        ON_ERROR("ON_DaysInMonthOfGregorianYear() has bug");
        break;
      }
    }

    if (day_of_month < 1 || day_of_month > max_day_of_month || max_day_of_month > 31)
    {
      ON_ERROR("Invalid day_of_month parameter");
      break;
    }

    const unsigned int platform = (platform_branch > 0) ? (2 - (platform_branch % 2)) : 0;

    unsigned int version_major = 0xFFFFFFFFU;
    unsigned int version_minor = 0xFFFFFFFFU;
    unsigned int version_year = 0xFFFFFFFFU;
    unsigned int version_month = 0xFFFFFFFFU;
    unsigned int version_day_of_month = 0xFFFFFFFFU;
    unsigned int version_platform = 0xFFFFFFFFU;

    if (0 == version_as_unsigned_number)
    {
      version_as_unsigned_number = ON_VersionNumberConstruct(
        major,
        minor,
        year,
        month,
        day_of_month,
        platform_branch
      );
    }

    const bool bParsed = ON_VersionNumberParse(
      version_as_unsigned_number,
      &version_major,
      &version_minor,
      &version_year,
      &version_month,
      &version_day_of_month,
      &version_platform
      );
    if (false == bParsed)
    {
      ON_ERROR("Invalid version_as_unsigned_number parameter.");
      break;
    }

    if (
      version_major != major
      || version_minor != minor
      || version_year != year
      || version_month != month
      || version_day_of_month != day_of_month
      || version_platform != platform
      )
    {
      ON_ERROR("version_as_unsigned_number does not encode version information.");
      break;
    }

    const unsigned int version_ctor_cpp = ON_VersionNumberConstruct(
      major,
      minor,
      year,
      month,
      day_of_month,
      platform_branch
    );

    if (version_ctor_cpp != version_as_unsigned_number)
    {
      ON_ERROR("version_as_unsigned_number != ON_VersionNumberConstruct().");
      break;
    }

    const unsigned int version_ctor_macro = ON_VERSION_NUMBER_CTOR(major, minor, year, month, day_of_month, platform_branch);
    if (version_ctor_macro != version_as_unsigned_number)
    {
      ON_ERROR("version_as_unsigned_number != ON_VERSION_NUMBER_CTOR().");
      break;
    }
    return true;
  }

  return false;
}
