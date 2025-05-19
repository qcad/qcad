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

#include "opennurbs.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

#include "opennurbs_internal_defines.h"

// {EA2EFFD2-C9A9-4cb1-BE15-D2F46290F1A1}
//const ON_UUID ON_MaterialRef::material_from_layer = 
//{ 0xea2effd2, 0xc9a9, 0x4cb1, { 0xbe, 0x15, 0xd2, 0xf4, 0x62, 0x90, 0xf1, 0xa1 } };



// {86EDFDE4-8AAF-4bcd-AB7C-F7111978D7FE}
//const ON_UUID ON_MaterialRef::material_from_parent = 
//{ 0x86edfde4, 0x8aaf, 0x4bcd, { 0xab, 0x7c, 0xf7, 0x11, 0x19, 0x78, 0xd7, 0xfe } };


// on_stricmp() is a wrapper for case insensitive string compare
// and calls one of _stricmp(), stricmp(), or strcasecmp()
// depending on OS.
int on_stricmp(const char * s1, const char * s2)
{
#if defined(ON_RUNTIME_WIN)
  //return stricmp(s1,s2);
  return _stricmp(s1,s2);
#else
  return strcasecmp(s1,s2);
#endif
}

// on_strupr() calls _strupr() or strupr() depending on OS
char* on_strupr(char* s)
{
#if defined(ON_RUNTIME_WIN)
  return _strupr(s); // ANSI name
#else
  if (s) 
  {
    while (*s) 
    {
      *s = toupper(*s);
      s++;
    }
  }
  return s;
#endif
}

// on_strlwr() calls _strlwr() or strlwr() depending on OS
char* on_strlwr(char* s)
{
#if defined(ON_RUNTIME_WIN)
  return _strlwr(s); // ANSI name
#else
  if (s) {
    while (*s)
    {
      *s = tolower(*s);
      s++;
    }
  }
  return s;
#endif
}

// on_strrev() calls _strrev() or strrev() depending on OS
char* on_strrev(char* s)
{
#if defined(ON_RUNTIME_WIN)
  return _strrev(s); // ANSI name
#else
  int i, j;
  char c;
  for ( i = 0, j = ((int)strlen(s))-1; i < j; i++, j-- ) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
  return s;
#endif
}

#if defined(ON_COMPILER_MSC)
// Disable the MSC /W4 unreachable code warning for the call to on__hack__wcsicmp()
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4702 )
#endif

int on_wcsicmp( const wchar_t* s1, const wchar_t* s2)
{
  // handle nullptr strings consistently and without crashing.
  return ON_wString::Compare(
    s1,
    s2,
    ON_Locale::InvariantCulture,
    true
    );
}

#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_POP
#endif

wchar_t* on_wcsupr(wchar_t* s)
{
  const int length = ON_wString::Length(s);
  if ( length < 0 )
    return nullptr;
  ON_wString::MapStringOrdinal(ON_StringMapOrdinalType::UpperOrdinal,s,length,s,length+1);
  return s;
}

// on_wcslwr() calls _wcslwr() or wcslwr() depending on OS
wchar_t* on_wcslwr(wchar_t* s)
{
  const int length = ON_wString::Length(s);
  if ( length < 0 )
    return nullptr;
  ON_wString::MapStringOrdinal(ON_StringMapOrdinalType::LowerOrdinal,s,length,s,length+1);
  return s;
}


wchar_t* on_wcsrev(wchar_t* s)
{
  return ON_wString::Reverse(s,-1);
}

int on_WideCharToMultiByte(
    const wchar_t* lpWideCharStr,
    int cchWideChar,
    char* lpMultiByteStr,
    int cchMultiByte
    )
{
  // 14 March 2011 Dale Lear
  //   It turns out that Windows WideCharToMultiByte does correctly
  //   convert UTF-16 to UTF-8 in Windows 7 when the code page 
  //   is CP_ACP and calls with CP_UTF8 sometimes fail to do
  //   any conversion.  So, I wrote ON_ConvertWideCharToUTF8()
  //   and opennurbs will use ON_ConvertWideCharToUTF8 to get 
  //   consistent results on all platforms.
  unsigned int error_status = 0;
  unsigned int error_mask = 0xFFFFFFFF;
  ON__UINT32 error_code_point = 0xFFFD;
  const wchar_t* p1 = 0;
  int count = ON_ConvertWideCharToUTF8(false,lpWideCharStr,cchWideChar,lpMultiByteStr,cchMultiByte,
                                       &error_status,error_mask,error_code_point,&p1);
  if ( 0 != error_status )
  {
    ON_ERROR("Error converting UTF-16 encoded wchar_t string to UTF-8 encoded char string.");
  }
  return count;
}

int on_MultiByteToWideChar(
    const char* lpMultiByteStr,
    int cchMultiByte,
    wchar_t* lpWideCharStr,
    int cchWideChar
    )
{
  // 14 March 2011 Dale Lear
  //   It turns out that Windows WideCharToMultiByte does not correctly
  //   convert UTF-8 to UTF-16 in Windows 7 when the code page 
  //   is CP_ACP and calls with CP_UTF8 sometimes fail to do
  //   any conversion.  So, I wrote ON_ConvertUTF8ToWideChar()
  //   and opennurbs will use ON_ConvertUTF8ToWideChar to get 
  //   consistent results on all platforms.
  unsigned int error_status = 0;
  unsigned int error_mask = 0xFFFFFFFF;
  ON__UINT32 error_code_point = 0xFFFD;
  const char* p1 = 0;
  int count = ON_ConvertUTF8ToWideChar(false,lpMultiByteStr,cchMultiByte,lpWideCharStr,cchWideChar,
                                       &error_status,error_mask,error_code_point,&p1);
  if ( 0 != error_status )
  {
    ON_ERROR("Error converting UTF-8 encoded char string to UTF-16 encoded wchar_t string.");
  }
  return count;
}

void on_splitpath(
  const char* path,
  const char** volume,
  const char** dir,
  const char** fname,
  const char** ext
  )
{
  // The "const char* path" parameter is a UTF-8 encoded string. 
  // Since the unicode code point values for the characters we 
  // are searching for ( '/' '\' '.' ':' A-Z a-z) are all > 0 
  // and < 128, we can simply check for an array element having
  // the character value and not have to worry about dealing
  // with UTF-8 continuation values (>= 128).

  const char slash1 = '/';
  const char slash2 = '\\'; // do this even with the os is unix because
                            // we might be parsing a file name saved
                            // in Windows.

  const char* f;
  const char* e;
  const char* s;
  const char* s1;

  if ( 0 != volume )
    *volume = 0;
  if ( 0 != dir )
    *dir = 0;
  if ( 0 != fname )
    *fname = 0;
  if ( 0 != ext )
    *ext = 0;

  if ( 0 != path && 0 != *path )
  {
    // deal with Windows' volume letter (even when the os is unix)
    if ( ':' == path[1] )
    {
      if ( (path[0] >= 'A' && path[0] <= 'Z') || (path[0] >= 'a' && path[0] <= 'z') )
      {
        if ( volume )
          *volume = path;
        path += 2;
        if ( 0 == *path )
          return;
      }
    }
    else if (
      ON_String::Backslash == path[0] 
      && ON_String::Backslash == path[1]
      &&( (path[2] >= 'A' && path[2] <= 'Z') 
        || (path[2] >= 'a' && path[2] <= 'z') 
        || (path[2] >= '0' && path[2] <= '9') 
        )
      )
    {
      // deal with Windows' UNC hostnames like \\hostname (even when the os is unix)
      int i = 3;
      while (
        i < 18
        && ((path[i] >= 'A' && path[i] <= 'Z')
        || (path[i] >= 'a' && path[i] <= 'z')
        || (path[i] >= '0' && path[i] <= '9')
        || '-' == path[i] || '_' == path[i]
        ))
      {
        i++;
      }
      if (i < 18 && (ON_String::Backslash == path[i] || ON_String::Slash == path[i]))
      {
        if ( volume )
          *volume = path;
        path += i;
      }
    }
  }

  if ( 0 != path && 0 != *path )
  {
    e = 0;
    f = 0;
    s1 = path;
    while ( 0 != *s1 )
      s1++;
    s = (s1 > path) ? s1 - 1 : path;
  
    while ( s > path && '.' != *s && slash1 != *s && slash2 != *s )
      s--;

    if ( '.' == *s && 0 != s[1] )
    {
      // extensions must have something after the dot.
      e = s;
      s1 = e;
      s--;
    }

    while ( s > path && slash1 != *s && slash2 != *s )
      s--;

    if ( s >= path && s < s1 )
    {
      if (slash1 == *s || slash2 == *s ) 
      {
        if ( s+1 < s1 )
          f = s+1;
      }
      else if ( s == path )
      {
        f = s;
      }
    }

    if ( 0 == f )
    {
      // must have a non-empty filename in order to have and "extension"
      f = e;
      e = 0;
    }

    if ( 0 != dir && (0 == f || path < f) )
      *dir = path;

    if ( 0 != f && 0 != fname )
      *fname = f;

    if ( 0 != e && 0 != ext )
      *ext = e;
  }

}

void on_wsplitpath(
  const wchar_t* path,
  const wchar_t** volume,
  const wchar_t** dir,
  const wchar_t** fname,
  const wchar_t** ext
  )
{
  // The "const wchar_t* path" parameter is a UTF-8, UTF-16 or UTF-32
  // encoded string. Since the unicode code point values for the 
  // characters we are searching for ( '/' '\' '.' ':' A-Z a-z) are
  // all > 0 and < 128, we can simply check for an array element 
  // having the character value and not have to worry about dealing
  // with UTF-16 surrogate pair values (0xD800-0xDBFF and DC00-DFFF)
  // and UTF-8 continuation values (>= 128).

  const wchar_t slash1 = '/';
  const wchar_t slash2 = '\\'; // do this even with the os is unix because
                               // we might be parsing a file name saved
                               // in Windows.

  const wchar_t* f;
  const wchar_t* e;
  const wchar_t* s;
  const wchar_t* s1;

  if ( 0 != volume )
    *volume = 0;
  if ( 0 != dir )
    *dir = 0;
  if ( 0 != fname )
    *fname = 0;
  if ( 0 != ext )
    *ext = 0;

  if ( 0 != path && 0 != *path )
  {
    // deal with Windows' volume letter (even when the os is unix)
    if ( ':' == path[1] )
    {
      if ( (path[0] >= 'A' && path[0] <= 'Z') || (path[0] >= 'a' && path[0] <= 'z') )
      {
        if ( volume )
          *volume = path;
        path += 2;
        if ( 0 == *path )
          return;
      }
    }
    else if (
      ON_wString::Backslash == path[0] 
      && ON_wString::Backslash == path[1]
      &&( (path[2] >= 'A' && path[2] <= 'Z') 
        || (path[2] >= 'a' && path[2] <= 'z') 
        || (path[2] >= '0' && path[2] <= '9') 
        )
      )
    {
      // deal with Windows' UNC hostnames like \\hostname (even when the os is unix)
      int i = 3;
      while (
        i < 18
        && ((path[i] >= 'A' && path[i] <= 'Z')
        || (path[i] >= 'a' && path[i] <= 'z')
        || (path[i] >= '0' && path[i] <= '9')
        || '-' == path[i] || '_' == path[i]
        ))
      {
        i++;
      }
      if (i < 18 && (ON_wString::Backslash == path[i] || ON_wString::Slash == path[i]))
      {
        if ( volume )
          *volume = path;
        path += i;
      }
    }
  }

  if ( 0 != path && 0 != *path )
  {
    e = 0;
    f = 0;
    s1 = path;
    while ( 0 != *s1 )
      s1++;
    s = (s1 > path) ? s1 - 1 : path;
  
    while ( s > path && '.' != *s && slash1 != *s && slash2 != *s )
      s--;

    if ( '.' == *s && 0 != s[1] )
    {
      // extensions must have something after the dot.
      e = s;
      s1 = e;
      s--;
    }

    while ( s > path && slash1 != *s && slash2 != *s )
      s--;

    if ( s >= path && s < s1 )
    {
      if (slash1 == *s || slash2 == *s ) 
      {
        if ( s+1 < s1 )
          f = s+1;
      }
      else if ( s == path )
      {
        f = s;
      }
    }

    if ( 0 == f )
    {
      // must have a non-empty filename in order to have and "extension"
      f = e;
      e = 0;
    }

    if ( 0 != dir && (0 == f || path < f) )
      *dir = path;

    if ( 0 != f && 0 != fname )
      *fname = f;

    if ( 0 != e && 0 != ext )
      *ext = e;
  }

}


FILE* ON::OpenFile( // like fopen() - needed when OpenNURBS is used as a DLL
        const char* filename, // file name
        const char* filemode // file mode
        )
{
  return ON_FileStream::Open(filename,filemode);
}

FILE* ON::OpenFile( // like fopen() - needed when OpenNURBS is used as a DLL
        const wchar_t* filename, // file name
        const wchar_t* filemode // file mode
        )
{
  return ON_FileStream::Open(filename,filemode);
}

int ON::CloseFile( // like fclose() - needed when OpenNURBS is used as a DLL
        FILE* fp // pointer returned by OpenFile()
        )
{
  return ON_FileStream::Close(fp);
}

int ON::CloseAllFiles()
{
  // returns number of files closed or EOF for error
#if defined(ON_COMPILER_MSC)
  return _fcloseall(); // ANSI C name
#elif defined(ON_RUNTIME_APPLE) || defined(ON_RUNTIME_ANDROID) || defined(ON_RUNTIME_WASM)
  //fcloseall is not supported on mac/ios or android
  return EOF;
#else
  return fcloseall();
#endif
}



ON::active_space ON::ActiveSpace(int i)
{
  ON::active_space as;

  switch(i)
  {
  case no_space:          as = no_space;          break;
  case model_space:       as = model_space;       break;
  case page_space:        as = page_space;        break;
  case uveditor_space:    as = uveditor_space;    break;
  case blockeditor_space: as = blockeditor_space; break;
  default:                as = no_space;          break;
  }

  return as;
}

ON_INTERNAL_OBSOLETE::V5_TextDisplayMode ON_INTERNAL_OBSOLETE::V5TextDisplayModeFromUnsigned(
  unsigned int text_display_mode_as_unsigned
  )
{
  switch (text_display_mode_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kNormal);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kHorizontalToScreen);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kAboveLine);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kInLine);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kHorizontalInCplane);
  }
  ON_ERROR("Invalid text_display_mode_as_unsigned value");
  return (ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kAboveLine);
}

ON::RuntimeEnvironment ON::RuntimeEnvironmentFromUnsigned(
  unsigned int runtime_environment_as_unsigned
  )
{
  switch (runtime_environment_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON::RuntimeEnvironment::Unset);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::RuntimeEnvironment::None);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::RuntimeEnvironment::Windows);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::RuntimeEnvironment::Apple);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::RuntimeEnvironment::Android);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::RuntimeEnvironment::Linux);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::RuntimeEnvironment::WebAssembly);
  }
  ON_ERROR("Invalid runtime_environment_as_unsigned parameter value.");
  return (ON::RuntimeEnvironment::Unset);
}

ON::RuntimeEnvironment ON::CurrentRuntimeEnvironment()
{
#if defined(ON_RUNTIME_WIN)
  return ON::RuntimeEnvironment::Windows;
#elif defined (ON_RUNTIME_APPLE)
  return ON::RuntimeEnvironment::Apple;
#elif defined (ON_RUNTIME_ANDROID)
  return ON::RuntimeEnvironment::Android;
#elif defined (ON_RUNTIME_LINUX)
  return ON::RuntimeEnvironment::Linux;
#elif defined (ON_RUNTIME_WASM)
  return ON::RuntimeEnvironment::WebAssembly;
#else
  ON_ERROR("ON_RUNTIME_... not defined.");
  return ON::RuntimeEnvironment::Unset;
#endif
}

ON::ReadFileResult ON::ReadFileResultFromUnsigned(
  unsigned int read_file_result_as_unsigned
)
{
  switch (read_file_result_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON::ReadFileResult::Unset);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::ReadFileResult::Completed);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::ReadFileResult::CompletedWithErrors);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::ReadFileResult::Failed);
  }
  ON_ERROR("Invalid read_file_result_as_unsigned parameter value.");
  return (ON::ReadFileResult::Unset);
}

bool ON::ReadFileCompleted(
  ON::ReadFileResult read_file_result
)
{
  // true indicates partial to complete success.
  return (ON::ReadFileResult::Unset != read_file_result && ON::ReadFileResult::Failed != read_file_result);
}

bool ON::ReadFileFailed(
  ON::ReadFileResult read_file_result
)
{
  // true indicates total failure.
  return (ON::ReadFileResult::Failed == read_file_result);
}

bool ON::IsMetricLengthUnit(
  ON::LengthUnitSystem length_unit_system
)
{
  bool rc;
  switch (length_unit_system)
  {
  case ON::LengthUnitSystem::Angstroms:
  case ON::LengthUnitSystem::Nanometers:
  case ON::LengthUnitSystem::Microns:
  case ON::LengthUnitSystem::Millimeters:
  case ON::LengthUnitSystem::Centimeters:
  case ON::LengthUnitSystem::Decimeters:
  case ON::LengthUnitSystem::Meters:
  case ON::LengthUnitSystem::Dekameters:
  case ON::LengthUnitSystem::Hectometers:
  case ON::LengthUnitSystem::Kilometers:
  case ON::LengthUnitSystem::Megameters:
  case ON::LengthUnitSystem::Gigameters:
    rc = true;
    break;
  case ON::LengthUnitSystem::NauticalMiles:
  case ON::LengthUnitSystem::AstronomicalUnits:
  case ON::LengthUnitSystem::LightYears:
  case ON::LengthUnitSystem::Parsecs:
    rc = true;
  default:
    rc = false;
    break;
  }
  return rc;
}

bool ON::IsUnitedStatesCustomaryLengthUnit(
  ON::LengthUnitSystem length_unit_system
)
{
  bool rc;
  switch (length_unit_system)
  {
  case ON::LengthUnitSystem::Microinches:
  case ON::LengthUnitSystem::Mils:
  case ON::LengthUnitSystem::Inches:
  case ON::LengthUnitSystem::Feet:
  case ON::LengthUnitSystem::Yards:
  case ON::LengthUnitSystem::Miles:
  case ON::LengthUnitSystem::PrinterPoints:
  case ON::LengthUnitSystem::PrinterPicas:
    rc = true;
    break;
  default:
    rc = false;
    break;
  }
  return rc;
}

bool ON::IsTerrestrialLengthUnit(
  ON::LengthUnitSystem length_unit_system
)
{
  bool rc;
  switch (length_unit_system)
  {
  case ON::LengthUnitSystem::Millimeters:
  case ON::LengthUnitSystem::Centimeters:
  case ON::LengthUnitSystem::Decimeters:
  case ON::LengthUnitSystem::Meters:
  case ON::LengthUnitSystem::Dekameters:
  case ON::LengthUnitSystem::Hectometers:
  case ON::LengthUnitSystem::Kilometers:
    rc = true;
    break;
  case ON::LengthUnitSystem::Inches:
  case ON::LengthUnitSystem::Feet:
  case ON::LengthUnitSystem::Yards:
  case ON::LengthUnitSystem::Miles:
    rc = true;
    break;
  case ON::LengthUnitSystem::NauticalMiles:
    rc = true;
    break;
  default:
    rc = false;
    break;
  }
  return rc;
}

bool ON::IsExtraTerrestrialLengthUnit(
  ON::LengthUnitSystem length_unit_system
)
{
  bool rc;
  switch (length_unit_system)
  {
  case ON::LengthUnitSystem::AstronomicalUnits:
  case ON::LengthUnitSystem::LightYears:
  case ON::LengthUnitSystem::Parsecs:
    rc = true;
  default:
    rc = false;
    break;
  }
  return rc;
}

bool ON::IsMicroscopicLengthUnit(
  ON::LengthUnitSystem length_unit_system
)
{
  bool rc;
  switch (length_unit_system)
  {
  case ON::LengthUnitSystem::Angstroms:
  case ON::LengthUnitSystem::Nanometers:
  case ON::LengthUnitSystem::Microns:
    rc = true;
    break;
  case ON::LengthUnitSystem::Microinches:
  case ON::LengthUnitSystem::Mils:
    rc = true;
    break;
  default:
    rc = false;
    break;
  }
  return rc;
}

bool ON::IsUnitedStatesPrinterLengthUnit(
  ON::LengthUnitSystem length_unit_system
)
{
  bool rc;
  switch (length_unit_system)
  {
  case ON::LengthUnitSystem::PrinterPoints:
  case ON::LengthUnitSystem::PrinterPicas:
    rc = false;
    break;
  default:
    rc = false;
    break;
  }
  return rc;
}

ON::LengthUnitSystem ON::LengthUnitSystemFromUnsigned(unsigned int length_unit_system_as_unsigned)
{
  switch (length_unit_system_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::None);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::Angstroms);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::Nanometers);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::Microns);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::Millimeters);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::Centimeters);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::Decimeters);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::Meters);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::Dekameters);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::Hectometers);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::Kilometers);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::Megameters);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::Gigameters);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::Microinches);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::Mils);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::Inches);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::Feet);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::Yards);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::Miles);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::PrinterPoints);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::PrinterPicas);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::NauticalMiles);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::AstronomicalUnits);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::LightYears);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::Parsecs);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::CustomUnits);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::LengthUnitSystem::Unset);
  }

  ON_ERROR("Invalid length_unit_system_as_unsigned value");
  return (ON::LengthUnitSystem::Unset);
}

static ON::LengthUnitSystem(*Internal_func_ModelLengthUnitSystemCallback)(ON__UINT_PTR) = nullptr;

void ON::RegisterModelLengthUnitSystemCallback(
  ON::LengthUnitSystem(*func_ModelLengthUnitSystemCallback)(ON__UINT_PTR)
)
{
  Internal_func_ModelLengthUnitSystemCallback = func_ModelLengthUnitSystemCallback;
}

ON::LengthUnitSystem ON::ModelLengthUnitSystem(
  ON__UINT_PTR model_serial_number
)
{
  return 
    (nullptr == Internal_func_ModelLengthUnitSystemCallback 
      || 0 == model_serial_number 
      || model_serial_number >= ON_UNSET_UINT_INDEX
      )
    ? ON::LengthUnitSystem::None
    : Internal_func_ModelLengthUnitSystemCallback(model_serial_number);
}

ON::AngleUnitSystem ON::AngleUnitSystemFromUnsigned(unsigned int angle_unit_system_as_unsigned)
{
  switch (angle_unit_system_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON::AngleUnitSystem::None);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::AngleUnitSystem::Turns);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::AngleUnitSystem::Radians);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::AngleUnitSystem::Degrees);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::AngleUnitSystem::Minutes);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::AngleUnitSystem::Seconds);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::AngleUnitSystem::Gradians);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::AngleUnitSystem::Unset);
  }

  ON_ERROR("Invalid angle_unit_system_as_unsigned value");
  return (ON::AngleUnitSystem::Unset);
}


double ON::AngleUnitScale(
    ON::AngleUnitSystem us_from,
    ON::AngleUnitSystem us_to
    )
{
  if (ON::AngleUnitSystem::Unset == us_from || ON::AngleUnitSystem::Unset == us_to)
    return ON_DBL_QNAN;

  // the default cases are here to keep lint quiet
  double scale = 1.0;
  
  if (  us_from != us_to
        && ((int)us_to) > 0 && ((int)us_to) < 6
        // switch weeds out bogus values of us_from
      ) 
  switch( us_from ) 
  {
  case ON::AngleUnitSystem::Turns:
    switch(us_to)
    {
    case ON::AngleUnitSystem::Turns:
      scale = 1.0;
      break;
    case ON::AngleUnitSystem::Radians:
      scale = 2.0*ON_PI;
      break;
    case ON::AngleUnitSystem::Degrees:
      scale = 360.0;
      break;
    case ON::AngleUnitSystem::Minutes:
      scale = 60.0*360.0;
      break;
    case ON::AngleUnitSystem::Seconds:
      scale = 60.0*60.0*360.0;
      break;
    case ON::AngleUnitSystem::Gradians:
      scale = 400.0;
      break;
    case ON::AngleUnitSystem::Unset:
    case ON::AngleUnitSystem::None:
      ON_ERROR("unit system conversion undefined");
      break;
    }
    break;

  case ON::AngleUnitSystem::Radians:
    scale = 1.0;
    switch(us_to)
    {
    case ON::AngleUnitSystem::Turns:
      scale = 0.5/ON_PI;
      break;
    case ON::AngleUnitSystem::Radians:
      scale = 1.0;
      break;
    case ON::AngleUnitSystem::Degrees:
      scale = 180.0/ON_PI;
      break;
    case ON::AngleUnitSystem::Minutes:
      scale = 60.0*180.0/ON_PI;
      break;
    case ON::AngleUnitSystem::Seconds:
      scale = 60.0*60.0*180.0/ON_PI;
      break;
    case ON::AngleUnitSystem::Gradians:
      scale = 400.0/ON_PI;
      break;
    case ON::AngleUnitSystem::Unset:
    case ON::AngleUnitSystem::None:
      ON_ERROR("unit system conversion undefined");
      break;
    }
    break;

  case ON::AngleUnitSystem::Degrees:
    scale = 1.0;
    switch(us_to)
    {
    case ON::AngleUnitSystem::Turns:
      scale = 1.0/360.0;
      break;
    case ON::AngleUnitSystem::Radians:
      scale = ON_PI/180.0;
      break;
    case ON::AngleUnitSystem::Degrees:
      scale = 1.0;
      break;
    case ON::AngleUnitSystem::Minutes:
      scale = 60.0;
      break;
    case ON::AngleUnitSystem::Seconds:
      scale = 60.0*60.0;
      break;
    case ON::AngleUnitSystem::Gradians:
      scale = 10.0/9.0;
      break;
    case ON::AngleUnitSystem::Unset:
    case ON::AngleUnitSystem::None:
      ON_ERROR("unit system conversion undefined");
      break;
    }
    break;

  case ON::AngleUnitSystem::Minutes:
    scale = 1.0;
    switch(us_to)
    {
    case ON::AngleUnitSystem::Turns:
      scale = 1.0/(60.0*360.0);
      break;
    case ON::AngleUnitSystem::Radians:
      scale = ON_PI/(60.0*180.0);
      break;
    case ON::AngleUnitSystem::Degrees:
      scale = 1.0/60.0;
      break;
    case ON::AngleUnitSystem::Minutes:
      scale = 1.0;
      break;
    case ON::AngleUnitSystem::Seconds:
      scale = 60.0;
      break;
    case ON::AngleUnitSystem::Gradians:
      scale = 1.0/54.0;
      break;
    case ON::AngleUnitSystem::Unset:
    case ON::AngleUnitSystem::None:
      ON_ERROR("unit system conversion undefined");
      break;
    }
    break;

  case ON::AngleUnitSystem::Seconds:
    scale = 1.0;
    switch(us_to)
    {
    case ON::AngleUnitSystem::Turns:
      scale = 1.0/(60.0*60.0*360.0);
      break;
    case ON::AngleUnitSystem::Radians:
      scale = ON_PI/(60.0*60.0*180.0);
      break;
    case ON::AngleUnitSystem::Degrees:
      scale = 1.0/(60.0*60.0);
      break;
    case ON::AngleUnitSystem::Minutes:
      scale = 1.0/60.0;
      break;
    case ON::AngleUnitSystem::Seconds:
      scale = 1.0;
      break;
    case ON::AngleUnitSystem::Gradians:
      scale = 1.0/(54.0*60.0);
      break;
    case ON::AngleUnitSystem::Unset:
    case ON::AngleUnitSystem::None:
      ON_ERROR("unit system conversion undefined");
      break;
    }
    break;

  case ON::AngleUnitSystem::Gradians:
    scale = 1.0;
    switch(us_to)
    {
    case ON::AngleUnitSystem::Turns:
      scale = 400.0;
      break;
    case ON::AngleUnitSystem::Radians:
      scale = ON_PI/200.0;
      break;
    case ON::AngleUnitSystem::Degrees:
      scale = 9.0/10.0;
      break;
    case ON::AngleUnitSystem::Minutes:
      scale = 54.0;
      break;
    case ON::AngleUnitSystem::Seconds:
      scale = 60.0*54.0;
      break;
    case ON::AngleUnitSystem::Gradians:
      scale = 1.0;
      break;
    case ON::AngleUnitSystem::Unset:
    case ON::AngleUnitSystem::None:
      ON_ERROR("unit system conversion undefined");
      break;
    }
    break;

  case ON::AngleUnitSystem::Unset:
  case ON::AngleUnitSystem::None:
    ON_ERROR("unit system conversion undefined");
    break;
  }

  return scale;
}


double ON::UnitScale(
                     const class ON_3dmUnitsAndTolerances& u_and_t_from, 
                     const class ON_3dmUnitsAndTolerances& u_and_t_to
                     )
{
  return ON::UnitScale( u_and_t_from.m_unit_system, u_and_t_to.m_unit_system );
}

double ON::UnitScale(
    ON::LengthUnitSystem us_from,
    const class ON_UnitSystem& us_to
    )
{
  ON::LengthUnitSystem us1 = us_to.UnitSystem();
  if (
    ON::LengthUnitSystem::Unset == us_from 
    || ON::LengthUnitSystem::Unset == us1
    || us_from != ON::LengthUnitSystemFromUnsigned(static_cast<unsigned int>(us_from))
    || us1 != ON::LengthUnitSystemFromUnsigned(static_cast<unsigned int>(us1))
    )
  {
    ON_ERROR("Invalid parameters.");
    return ON_DBL_QNAN;
  }

  if (ON::LengthUnitSystem::None == us_from || ON::LengthUnitSystem::None == us1)
    return 1.0;

  if (ON::LengthUnitSystem::CustomUnits == us_from)
  {
    ON_ERROR("Use ON::UnitScale(const ON_UnitSystem&, const ON_UnitSystem& ) for custom units.");
    return 1.0;
  }

  if (us_from == us1)
  {
    return 1.0;
  }

  double scale = 1.0;
  if (    ON::LengthUnitSystem::CustomUnits == us1 
       && ON::LengthUnitSystem::None != us_from
       && ON::LengthUnitSystem::CustomUnits != us_from
    )
  {
    const double meters_per_custom_unit = us_to.MetersPerUnit(ON_DBL_QNAN);
    if ( meters_per_custom_unit > 0.0 && meters_per_custom_unit < ON_UNSET_POSITIVE_VALUE )
    {
      scale *= meters_per_custom_unit;
      us1 = ON::LengthUnitSystem::Meters;
    }
  }
  return scale*ON::UnitScale(us_from,us1);
}

double ON::UnitScale(
    const class ON_UnitSystem& us_from, 
    ON::LengthUnitSystem us_to
    )
{
  ON::LengthUnitSystem us0 = us_from.UnitSystem();

  if (
    ON::LengthUnitSystem::Unset == us0
    || ON::LengthUnitSystem::Unset == us_to
    || us0 != ON::LengthUnitSystemFromUnsigned(static_cast<unsigned int>(us0))
    || us_to != ON::LengthUnitSystemFromUnsigned(static_cast<unsigned int>(us_to))
    )
  {
    ON_ERROR("Invalid parameters.");
    return ON_DBL_QNAN;
  }

  if (ON::LengthUnitSystem::None == us0 || ON::LengthUnitSystem::None == us_to)
    return 1.0;

  if (ON::LengthUnitSystem::CustomUnits == us_to)
  {
    ON_ERROR("Use ON::UnitScale(const ON_UnitSystem&, const ON_UnitSystem& ) for custom units.");
    return 1.0;
  }

  if (us0 == us_to)
    return 1.0;

  double scale = 1.0;
  if (    ON::LengthUnitSystem::CustomUnits == us0 
       && ON::LengthUnitSystem::None != us_to
       && ON::LengthUnitSystem::CustomUnits != us_to
     )
  {
    const double meters_per_custom_unit = us_from.MetersPerUnit(ON_DBL_QNAN);
    if ( meters_per_custom_unit > 0.0 && meters_per_custom_unit < ON_UNSET_POSITIVE_VALUE )
    {
      scale /= meters_per_custom_unit;
      us0 = ON::LengthUnitSystem::Meters;
    }
  }
  return scale*ON::UnitScale(us0,us_to);
}

double ON::UnitScale(
  const class ON_UnitSystem& u_and_t_from, 
  const class ON_UnitSystem& u_and_t_to
  )
{
  ON::LengthUnitSystem us_from = u_and_t_from.UnitSystem();
  ON::LengthUnitSystem us_to   = u_and_t_to.UnitSystem();

  if (
    ON::LengthUnitSystem::Unset == us_from
    || ON::LengthUnitSystem::Unset == us_to
    || us_from != ON::LengthUnitSystemFromUnsigned(static_cast<unsigned int>(us_from))
    || us_to != ON::LengthUnitSystemFromUnsigned(static_cast<unsigned int>(us_to))
    )
  {
    ON_ERROR("Invalid parameters.");
    return ON_DBL_QNAN;
  }

  if (ON::LengthUnitSystem::None == us_from || ON::LengthUnitSystem::None == us_to)
    return 1.0;

  if (ON::LengthUnitSystem::CustomUnits != us_from && ON::LengthUnitSystem::CustomUnits != us_to)
    return ON::UnitScale( us_from, us_to );

  // uncommon custom units case
  const double meters_per_unit_from = u_and_t_from.MetersPerUnit(ON_DBL_QNAN);
  const double meters_per_unit_to = u_and_t_to.MetersPerUnit(ON_DBL_QNAN);
  if (meters_per_unit_from == meters_per_unit_to)
    return 1.0;
  double scale = 1.0;
  if ( ON::LengthUnitSystem::CustomUnits == us_from 
        && meters_per_unit_from > 0.0 
        && meters_per_unit_from < ON_UNSET_POSITIVE_VALUE
        )
  {
    scale /= meters_per_unit_from;
    us_from = ON::LengthUnitSystem::Meters;
  }

  if ( ON::LengthUnitSystem::CustomUnits == us_to 
    && meters_per_unit_to > 0.0 
    && meters_per_unit_to < ON_UNSET_POSITIVE_VALUE 
    )
  {
    scale *= meters_per_unit_to;
    us_to = ON::LengthUnitSystem::Meters;
  }

  scale *= ON::UnitScale( us_from, us_to );

  return scale;
}

static bool IsEnglishUnit( ON::LengthUnitSystem us )
{
  return (
          ON::LengthUnitSystem::Microinches == us
          || ON::LengthUnitSystem::Mils == us
          || ON::LengthUnitSystem::Inches == us
          || ON::LengthUnitSystem::Feet == us
          || ON::LengthUnitSystem::Yards == us
          || ON::LengthUnitSystem::Miles == us
          || ON::LengthUnitSystem::PrinterPoints == us
          || ON::LengthUnitSystem::PrinterPicas == us
         );
}

double ON::UnitScale(
            ON::LengthUnitSystem u0, // from
            ON::LengthUnitSystem u1  // to
            )
{
  // Scale factor for changing unit systems
  // Examples 
  //   100.0  = UnitScale( ON::LengthUnitSystem::Meters, ON::LengthUnitSystem::Centimeters ) 
  //     2.54 = UnitScale( ON::LengthUnitSystem::Inches, ON::LengthUnitSystem::Centimeters ) 
  //    12.0  = UnitScale( ON::LengthUnitSystem::Feet, ON::LengthUnitSystem::Inches ) 

  if (ON::LengthUnitSystem::Unset == u0 || ON::LengthUnitSystem::Unset == u1)
  {
    ON_ERROR("Invalid parameter.");
    return ON_DBL_QNAN;
  }

  if (
    u0 != ON::LengthUnitSystemFromUnsigned(static_cast<unsigned int>(u0))
    || u1 != ON::LengthUnitSystemFromUnsigned(static_cast<unsigned int>(u1))
    )
  {
    ON_ERROR("Invalid parameter.");
    return ON_DBL_QNAN;
  }

  if (ON::LengthUnitSystem::None == u0 || ON::LengthUnitSystem::None == u1)
  {
    return 1.0;
  }

  if (ON::LengthUnitSystem::CustomUnits == u0 || ON::LengthUnitSystem::CustomUnits == u1)
  {
    ON_ERROR("Use ON::UnitScale(const ON_UnitSystem&, const ON_UnitSystem& ) for custom unit scale.");
    return 1.0;
  }

  if (u0 == u1)
  {
    return 1.0;
  }

  // the default cases are here to keep lint quiet
  double scale = 1.0;

  switch( u0 ) 
  {
  case ON::LengthUnitSystem::Angstroms:
    scale = UnitScale( ON::LengthUnitSystem::Meters, u1)*1.0e-10;
    break;

  case ON::LengthUnitSystem::Nanometers:
    scale = UnitScale( ON::LengthUnitSystem::Meters, u1)*1.0e-9;
    break;

  case ON::LengthUnitSystem::Microns:
    scale = UnitScale( ON::LengthUnitSystem::Meters, u1)*1.0e-6;
    break;

  case ON::LengthUnitSystem::Millimeters:
    switch( u1 ) 
    {
    case ON::LengthUnitSystem::Meters:      scale = 1.0e-3; break;
    case ON::LengthUnitSystem::Microns:     scale = 1.0e+3; break;
    case ON::LengthUnitSystem::Centimeters: scale = 1.0e-1; break;

    default:
      scale = IsEnglishUnit(u1)
            ? UnitScale( ON::LengthUnitSystem::Inches, u1 )/25.4
            : UnitScale( ON::LengthUnitSystem::Meters, u1 )*1.0e-3;
      break;
    }
    break;

  case ON::LengthUnitSystem::Centimeters:
    switch( u1 ) 
    {
    case ON::LengthUnitSystem::Meters:      scale = 1.0e-2; break;
    case ON::LengthUnitSystem::Millimeters: scale = 1.0e+1; break;

    default:
      scale = IsEnglishUnit(u1)
            ? UnitScale( ON::LengthUnitSystem::Inches, u1 )/2.54
            : UnitScale( ON::LengthUnitSystem::Meters, u1 )*1.0e-2;
      break;
    }
    break;

  case ON::LengthUnitSystem::Decimeters:
    scale = IsEnglishUnit(u1)
          ? UnitScale( ON::LengthUnitSystem::Inches, u1 )/0.254
          : UnitScale( ON::LengthUnitSystem::Meters, u1 )*1.0e-1;
    break;

  case ON::LengthUnitSystem::Meters:
    switch( u1 ) 
    {
    case ON::LengthUnitSystem::Angstroms:      scale = 1.0e+10; break;
    case ON::LengthUnitSystem::Nanometers:     scale = 1.0e+9;  break;
    case ON::LengthUnitSystem::Microns:        scale = 1.0e+6;  break;
    case ON::LengthUnitSystem::Millimeters:    scale = 1.0e+3;  break;
    case ON::LengthUnitSystem::Centimeters:    scale = 1.0e+2;  break;
    case ON::LengthUnitSystem::Decimeters:     scale = 1.0e1;   break;
    case ON::LengthUnitSystem::Meters:         scale = 1.0;     break;
    case ON::LengthUnitSystem::Dekameters:     scale = 1.0e-1;  break;
    case ON::LengthUnitSystem::Hectometers:    scale = 1.0e-2;  break;
    case ON::LengthUnitSystem::Kilometers:     scale = 1.0e-3;  break;
    case ON::LengthUnitSystem::Megameters:     scale = 1.0e-6;  break;
    case ON::LengthUnitSystem::Gigameters:     scale = 1.0e-9;  break;

    case ON::LengthUnitSystem::NauticalMiles:  scale = 1.0/1852.0; break;
    case ON::LengthUnitSystem::AstronomicalUnits:   scale = 1.0/1.4959787e+11; break;
    case ON::LengthUnitSystem::LightYears:     scale = 1.0/9.4607304725808e+15; break;
    case ON::LengthUnitSystem::Parsecs:        scale = 1.0/3.08567758e+16; break;

    default:
      if ( IsEnglishUnit(u1) )
        scale = UnitScale( ON::LengthUnitSystem::Inches, u1 )/0.0254;
      break;
    }
    break;

  case ON::LengthUnitSystem::Dekameters:
    scale = UnitScale( ON::LengthUnitSystem::Meters, u1 )*10.0;
    break;

  case ON::LengthUnitSystem::Hectometers:
    scale = UnitScale( ON::LengthUnitSystem::Meters, u1 )*100.0;
    break;

  case ON::LengthUnitSystem::Kilometers:
    scale = IsEnglishUnit(u1)
          ? UnitScale( ON::LengthUnitSystem::Inches, u1 )/0.0000254
          : UnitScale( ON::LengthUnitSystem::Meters, u1 )*1000.0;
    break;

  case ON::LengthUnitSystem::Megameters:
    scale = UnitScale( ON::LengthUnitSystem::Meters, u1 )*1.0e6;
    break;

  case ON::LengthUnitSystem::Gigameters:
    scale = UnitScale( ON::LengthUnitSystem::Meters, u1 )*1.0e9;
    break;

  case ON::LengthUnitSystem::Microinches:
    scale = UnitScale( ON::LengthUnitSystem::Inches, u1 )*1.0e-6;
    break;

  case ON::LengthUnitSystem::Mils:
    scale = UnitScale( ON::LengthUnitSystem::Inches, u1 )*1.0e-3;
    break;

  case ON::LengthUnitSystem::Inches:
    switch( u1 ) 
    {
    case ON::LengthUnitSystem::Angstroms:       scale = 2.54e+8; break;
    case ON::LengthUnitSystem::Nanometers:      scale = 2.54e+7; break;
    case ON::LengthUnitSystem::Microns:         scale = 2.54e+4; break;
    case ON::LengthUnitSystem::Millimeters:     scale = 25.4; break;
    case ON::LengthUnitSystem::Centimeters:     scale = 2.54; break;
    case ON::LengthUnitSystem::Decimeters:      scale = 2.54e-1; break;
    case ON::LengthUnitSystem::Meters:          scale = 2.54e-2; break;
    case ON::LengthUnitSystem::Dekameters:      scale = 2.54e-3; break;
    case ON::LengthUnitSystem::Hectometers:     scale = 2.54e-4; break;
    case ON::LengthUnitSystem::Kilometers:      scale = 2.54e-5; break;
    case ON::LengthUnitSystem::Megameters:      scale = 2.54e-8; break;
    case ON::LengthUnitSystem::Gigameters:      scale = 2.54e-11; break;

    case ON::LengthUnitSystem::PrinterPoints: scale = 72.0;            break;
    case ON::LengthUnitSystem::PrinterPicas:  scale = 6.0;             break;
    case ON::LengthUnitSystem::Microinches: scale = 1.0e+6;            break;
    case ON::LengthUnitSystem::Mils:        scale = 1.0e+3;            break;
    case ON::LengthUnitSystem::Inches:      scale = 1.0;               break;
    case ON::LengthUnitSystem::Feet:        scale = 1.0/12.0;          break;
    case ON::LengthUnitSystem::Yards:       scale = 1.0/36.0;          break;
    case ON::LengthUnitSystem::Miles:       scale = 1.0/(12.0*5280.0); break;

    default:
      scale = UnitScale( ON::LengthUnitSystem::Meters, u1 )*2.54e-2;
      break;
    }
    break;

  case ON::LengthUnitSystem::Feet:
    switch( u1 ) 
    {      
    case ON::LengthUnitSystem::Yards:
      scale = 1.0/3.0;
      break;
    case ON::LengthUnitSystem::Miles:
      scale = 1.0/5280.0;
      break;
    default:
      scale = UnitScale( ON::LengthUnitSystem::Inches, u1 )*12.0;
      break;
    }
    break;

  case ON::LengthUnitSystem::Yards:
    switch( u1 ) 
    {      
    case ON::LengthUnitSystem::Feet:        scale = 3.0; break;
    case ON::LengthUnitSystem::Miles:       scale = 1.0/1760.0; break;
    default:
      scale = UnitScale( ON::LengthUnitSystem::Inches, u1 )*36.0;
      break;
    }
    break;

  case ON::LengthUnitSystem::Miles:
    if ( ON::LengthUnitSystem::Feet == u1 )
    {
      scale = 5280.0;
    }
    else
    {
      scale = IsEnglishUnit(u1)
            ? UnitScale( ON::LengthUnitSystem::Inches, u1 )*12.0*5280.0
            : UnitScale( ON::LengthUnitSystem::Meters, u1 )*1609.344;
    }
    break;

  case ON::LengthUnitSystem::PrinterPoints:
    scale = UnitScale( ON::LengthUnitSystem::Inches, u1 )/72.0;
    break;

  case ON::LengthUnitSystem::PrinterPicas:
    scale = UnitScale( ON::LengthUnitSystem::Inches, u1 )/6.0;
    break;

  case ON::LengthUnitSystem::NauticalMiles:
    scale = UnitScale( ON::LengthUnitSystem::Meters, u1 )*1852.0;
    break;

  case ON::LengthUnitSystem::AstronomicalUnits:
    // 1.4959787e+11  http://en.wikipedia.org/wiki/Astronomical_unit
    // 1.495979e+11   http://units.nist.gov/Pubs/SP811/appenB9.htm  
    //    An astronomical unit (au) is the mean distance from the 
    //    center of the earth to the center of the sun.
    scale = UnitScale( ON::LengthUnitSystem::Meters, u1 )*1.4959787e+11;
    break;

  case ON::LengthUnitSystem::LightYears:
    // 9.4607304725808e+15 http://en.wikipedia.org/wiki/Light_year
    // 9.46073e+15 meters  http://units.nist.gov/Pubs/SP811/appenB9.htm
    //    A light year is the distance light travels in one Julian year.
    //    The speed of light is exactly 299792458 meters/second.
    //    A Julian year is exactly 365.25 * 86400 seconds and is 
    //    approximately the time it takes for one earth orbit.
    scale = UnitScale( ON::LengthUnitSystem::Meters, u1 )*9.4607304725808e+15;
    break;

  case ON::LengthUnitSystem::Parsecs:
    // 3.08567758e+16  // http://en.wikipedia.org/wiki/Parsec
    // 3.085678e+16    // http://units.nist.gov/Pubs/SP811/appenB9.htm  
    scale = UnitScale( ON::LengthUnitSystem::Meters, u1 )*3.08567758e+16;
    break;

  case ON::LengthUnitSystem::CustomUnits:
    scale = 1.0;
    break;
  case ON::LengthUnitSystem::None:
    scale = 1.0;
    break;
  case ON::LengthUnitSystem::Unset:
    scale = ON_DBL_QNAN;
    break;
  }

  return scale;
}


ON::OBSOLETE_DistanceDisplayMode ON::DistanceDisplayModeFromUnsigned(unsigned int distance_display_mode_as_unsigned)
{
  switch (distance_display_mode_as_unsigned) 
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON::OBSOLETE_DistanceDisplayMode::Decimal);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::OBSOLETE_DistanceDisplayMode::Fractional);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::OBSOLETE_DistanceDisplayMode::FeetInches);
  }

  ON_ERROR("Invalid distance_display_mode_as_unsigned value");
  return (ON::OBSOLETE_DistanceDisplayMode::Decimal);
}

ON::point_style ON::PointStyle(int i)
{
  //convertintegertopoint_styleenum
  point_style ps = unknown_point_style;
  switch (i) {
  case not_rational: ps = not_rational; break;
  case homogeneous_rational: ps = homogeneous_rational; break;
  case euclidean_rational: ps = euclidean_rational; break;
  default: ps = unknown_point_style; break;
  }
  return ps;
}


ON::knot_style ON::KnotStyle(int i)
{
  //convertintegertoknot_styleenum
  knot_style ks = unknown_knot_style;
  switch (i) {
  case uniform_knots: ks = uniform_knots; break;
  case quasi_uniform_knots: ks = quasi_uniform_knots; break;
  case piecewise_bezier_knots: ks = piecewise_bezier_knots; break;
  case clamped_end_knots: ks = clamped_end_knots; break;
  case non_uniform_knots: ks = non_uniform_knots; break;
  default: ks = unknown_knot_style; break;
  }
  return ks;
}

ON::continuity ON::Continuity(int i)
{
  ON::continuity c = ON::continuity::unknown_continuity;

  switch(i)
  {
  case (int)ON::continuity::unknown_continuity: c = ON::continuity::unknown_continuity; break;
  case (int)ON::continuity::C0_continuous: c = ON::continuity::C0_continuous; break;
  case (int)ON::continuity::C1_continuous: c = ON::continuity::C1_continuous; break;
  case (int)ON::continuity::C2_continuous: c = ON::continuity::C2_continuous; break;
  case (int)ON::continuity::G1_continuous: c = ON::continuity::G1_continuous; break;
  case (int)ON::continuity::G2_continuous: c = ON::continuity::G2_continuous; break;
  
  // 30 March 2003 Dale Lear added these
  case (int)ON::continuity::C0_locus_continuous: c = ON::continuity::C0_locus_continuous; break;
  case (int)ON::continuity::C1_locus_continuous: c = ON::continuity::C1_locus_continuous; break;
  case (int)ON::continuity::C2_locus_continuous: c = ON::continuity::C2_locus_continuous; break;
  case (int)ON::continuity::G1_locus_continuous: c = ON::continuity::G1_locus_continuous; break;
  case (int)ON::continuity::G2_locus_continuous: c = ON::continuity::G2_locus_continuous; break;

  case (int)ON::continuity::Cinfinity_continuous: c = ON::continuity::Cinfinity_continuous; break;

  case (int)ON::continuity::Gsmooth_continuous: c = ON::continuity::Gsmooth_continuous; break;
  };

  return c;
}

ON::continuity ON::ParametricContinuity(int i)
{
  // "erase" the locus setting.
  ON::continuity c = ON::continuity::unknown_continuity;

  switch(i)
  {
  case (int)ON::continuity::unknown_continuity: c = ON::continuity::unknown_continuity; break;
  case (int)ON::continuity::C0_continuous: c = ON::continuity::C0_continuous; break;
  case (int)ON::continuity::C1_continuous: c = ON::continuity::C1_continuous; break;
  case (int)ON::continuity::C2_continuous: c = ON::continuity::C2_continuous; break;
  case (int)ON::continuity::G1_continuous: c = ON::continuity::G1_continuous; break;
  case (int)ON::continuity::G2_continuous: c = ON::continuity::G2_continuous; break;
  case (int)ON::continuity::C0_locus_continuous: c = ON::continuity::C0_continuous; break;
  case (int)ON::continuity::C1_locus_continuous: c = ON::continuity::C1_continuous; break;
  case (int)ON::continuity::C2_locus_continuous: c = ON::continuity::C2_continuous; break;
  case (int)ON::continuity::G1_locus_continuous: c = ON::continuity::G1_continuous; break;
  case (int)ON::continuity::G2_locus_continuous: c = ON::continuity::G2_continuous; break;
  case (int)ON::continuity::Cinfinity_continuous: c = ON::continuity::Cinfinity_continuous; break;
  case (int)ON::continuity::Gsmooth_continuous: c = ON::continuity::Gsmooth_continuous; break;
  };

  return c;
}


ON::continuity ON::PolylineContinuity(int i)
{
  ON::continuity c = ON::continuity::unknown_continuity;

  switch(i)
  {
  case (int)ON::continuity::unknown_continuity: c = ON::continuity::unknown_continuity; break;
  case (int)ON::continuity::C0_continuous: c = ON::continuity::C0_continuous; break;
  case (int)ON::continuity::C1_continuous: c = ON::continuity::C1_continuous; break;
  case (int)ON::continuity::C2_continuous: c = ON::continuity::C1_continuous; break;
  case (int)ON::continuity::G1_continuous: c = ON::continuity::G1_continuous; break;
  case (int)ON::continuity::G2_continuous: c = ON::continuity::G1_continuous; break;
  case (int)ON::continuity::C0_locus_continuous: c = ON::continuity::C0_locus_continuous; break;
  case (int)ON::continuity::C1_locus_continuous: c = ON::continuity::C1_locus_continuous; break;
  case (int)ON::continuity::C2_locus_continuous: c = ON::continuity::C1_locus_continuous; break;
  case (int)ON::continuity::G1_locus_continuous: c = ON::continuity::G1_locus_continuous; break;
  case (int)ON::continuity::G2_locus_continuous: c = ON::continuity::G1_locus_continuous; break;
  case (int)ON::continuity::Cinfinity_continuous: c = ON::continuity::C1_continuous; break;
  case (int)ON::continuity::Gsmooth_continuous: c = ON::continuity::G1_continuous; break;
  };

  return c;
}


ON::curve_style ON::CurveStyle(int i)
{
  //convertintegertocurve_styleenum
  curve_style cs = unknown_curve_style;
  switch (i) {
  case line: cs = line; break;
  case circle: cs = circle; break;
  case ellipse: cs = ellipse; break;
  case parabola: cs = parabola; break;
  case hyperbola: cs = hyperbola; break;
  case planar_polyline: cs = planar_polyline; break;
  case polyline: cs = polyline; break;
  case planar_freeform_curve: cs = planar_freeform_curve; break;
  case freeform_curve: cs = freeform_curve; break;
  default: cs = unknown_curve_style; break;
  }
  return cs;
}

ON::surface_style ON::SurfaceStyle(int i)
{
  //convertintegertosurface_styleenum
  surface_style ss = unknown_surface_style;
  
  switch (i) {
  case plane: ss = plane; break;
  case circular_cylinder: ss = circular_cylinder; break;
  case elliptical_cylinder: ss = elliptical_cylinder; break;
  case circular_cone: ss = circular_cone; break;
  case elliptical_cone: ss = elliptical_cone; break;
  case sphere: ss = sphere; break;
  case torus: ss = torus; break;
  case surface_of_revolution: ss = surface_of_revolution; break;
  case ruled_surface: ss = ruled_surface; break;
  case freeform_surface: ss = freeform_surface; break;
  default: ss = unknown_surface_style; break;
  }
  return ss;
}

ON::sort_algorithm ON::SortAlgorithm(int i)
{
  sort_algorithm sa = ON::sort_algorithm::quick_sort;
  
  switch (i) {
  case (int)ON::sort_algorithm::heap_sort: sa = ON::sort_algorithm::heap_sort; break;
  case (int)ON::sort_algorithm::quick_sort: sa = ON::sort_algorithm::quick_sort; break;
  default: sa = ON::sort_algorithm::quick_sort; break;
  }
  return sa;
}

ON::endian ON::Endian(int i)
{ // convert integer to endian enum
  endian e = (i <= 0) ? ON::endian::little_endian : ON::endian::big_endian;
  return e;
}

ON::endian ON::Endian()
{
  // returns endian-ness of cpu.
  union {
    int i;
    unsigned char b[sizeof(int)];
  } u;
  u.i = 1;
  return (u.b[0] == 1) ? ON::endian::little_endian : ON::endian::big_endian;
}

ON::archive_mode ON::ArchiveMode(int i)
{
  // convert integer to endian enum
  ON::archive_mode a = ON::archive_mode::read;
  switch(i) {
  case (int)ON::archive_mode::read:      a = ON::archive_mode::read; break;
  case (int)ON::archive_mode::write:     a = ON::archive_mode::write; break;
  case (int)ON::archive_mode::readwrite: a = ON::archive_mode::readwrite; break;
  case (int)ON::archive_mode::read3dm:   a = ON::archive_mode::read3dm; break;
  case (int)ON::archive_mode::write3dm:  a = ON::archive_mode::write3dm; break;
  }
  return a;
}

ON::view_projection ON::ViewProjection(int i)
{
  // convert integer to view_projection enum
  view_projection v = ON::unknown_view;
  switch(i) 
  {
  case ON::parallel_view:          v = ON::parallel_view;          break;
  case ON::perspective_view:       v = ON::perspective_view;       break;
  }
  return v;
}

bool ON::IsParallelProjection( ON::view_projection proj )
{
  return ON::parallel_view == proj;
}

bool ON::IsPerspectiveProjection( ON::view_projection proj )
{
  return ( ON::perspective_view == proj );
}

ON::coordinate_system ON::CoordinateSystem(int i)
{
  // convert integer to coordinate_system enum
  coordinate_system cs = world_cs;
  switch(i) {
  case world_cs:  cs = world_cs; break;
  case camera_cs: cs = camera_cs; break;
  case clip_cs:   cs = clip_cs; break;
  case screen_cs: cs = screen_cs; break;
  }
  return cs;
}

ON::exception_type ON::ExceptionType(int i)
{
  // convert integer to exception_type enum
  ON::exception_type e = unknown_exception;
  switch(i) {
  case out_of_memory:               e = out_of_memory; break;
  case unable_to_write_archive:     e = unable_to_write_archive; break;
  case unable_to_read_archive:      e = unable_to_read_archive; break;
  case unable_to_seek_archive:      e = unable_to_seek_archive; break;
  case unexpected_end_of_archive:   e = unexpected_end_of_archive; break;
  case unexpected_value_in_archive: e = unexpected_value_in_archive; break;
  };
  return e;
}

ON::layer_mode ON::LayerMode(int i)
{
  ON::layer_mode m = normal_layer;
	switch(i)
  {
    case normal_layer:        m = normal_layer;       break;
    case hidden_layer:        m = hidden_layer;       break;
    case locked_layer:        m = locked_layer;       break;
  }
  return m;
}

ON::object_mode ON::ObjectMode(int i)
{
  ON::object_mode m = normal_object;
	switch(i)
  {
    case normal_object:  m = normal_object;  break;
    case hidden_object:  m = hidden_object;  break;
    case locked_object:  m = locked_object;  break;
    case idef_object:    m = idef_object;    break;
  }
  return m;
}

ON::object_color_source ON::ObjectColorSource(int i)
{
  // convert integer to object_mode enum
  ON::object_color_source cs = color_from_layer;
  switch (i) 
  {
  case color_from_layer: // use color assigned to layer
    cs = color_from_layer;
    break;
  case color_from_object: // use color assigned to object
    cs = color_from_object;
    break;
  case color_from_material:  // use diffuse render material color
    cs = color_from_material;
    break;
  case color_from_parent:
    cs = color_from_parent;
    break;
  }
  return cs;
}

ON::plot_color_source ON::PlotColorSource(int i)
{
  // convert integer to object_mode enum
  ON::plot_color_source cs = plot_color_from_layer;
  switch (i) 
  {
  case plot_color_from_layer:
    cs = plot_color_from_layer;
    break;
  case plot_color_from_object:
    cs = plot_color_from_object;
    break;
  case plot_color_from_display: 
    cs = plot_color_from_display;
    break;
  case plot_color_from_parent:
    cs = plot_color_from_parent;
    break;
  }
  return cs;
}

ON::plot_weight_source ON::PlotWeightSource(int pw)
{
  switch(pw)
  {
  case plot_weight_from_layer:  return plot_weight_from_layer;  break;
  case plot_weight_from_object: return plot_weight_from_object; break;
  case plot_weight_from_parent: return plot_weight_from_parent; break;
  }
  return plot_weight_from_layer;
}


ON::object_linetype_source ON::ObjectLinetypeSource(int i)
{
  // convert integer to object_mode enum
  ON::object_linetype_source ls = linetype_from_layer;
  switch (i) {
  case linetype_from_layer: // use linetype assigned to layer
    ls = linetype_from_layer;
    break;
  case linetype_from_object: // use linetype assigned to object
    ls = linetype_from_object;
    break;
  case linetype_from_parent:
    ls = linetype_from_parent;
    break;
  }
  return ls;
}

ON::object_material_source ON::ObjectMaterialSource(int i)
{
  ON::object_material_source ms = material_from_layer;
  switch(i) {
  case material_from_layer:
    ms = material_from_layer;
    break;
  case material_from_object:
    ms = material_from_object;
    break;
  case material_from_parent:
    ms = material_from_parent;
    break;
  }
  return ms;
}

ON::light_style ON::LightStyle(int i)
{
  // convert integer to light_style enum
  light_style ls = unknown_light_style;
  switch(i)
  {
    case unknown_light_style: ls = unknown_light_style; break;
    //case view_directional_light: ls = view_directional_light; break;
    //case view_point_light: ls = view_point_light; break;
    //case view_spot_light: ls = view_spot_light; break;
    case camera_directional_light: ls = camera_directional_light; break;
    case camera_point_light: ls = camera_point_light; break;
    case camera_spot_light: ls = camera_spot_light; break;
    case world_directional_light: ls = world_directional_light; break;
    case world_point_light: ls = world_point_light; break;
    case world_spot_light: ls = world_spot_light; break;
    case ambient_light: ls = ambient_light; break;
    case world_linear_light: ls = world_linear_light; break;
    case world_rectangular_light: ls = world_rectangular_light; break;
  }
  return ls;
}

ON::curvature_style ON::CurvatureStyle(int i)
{
  // convert integer to light_style enum
  ON::curvature_style cs = unknown_curvature_style;
  switch(i) {
  case gaussian_curvature:
    cs = gaussian_curvature;
    break;
  case mean_curvature:
    cs = mean_curvature;
    break;
  case min_curvature: 
    // minimum unsigned radius of curvature
    cs = min_curvature;
    break;
  case max_curvature: 
    // maximum unsigned radius of curvature
    cs = max_curvature;
    break;
  //case section_curvature_x:
    // unsigned normal curvature with respect to sections cut perp to world x axis
    //cs = section_curvature_x;
    //break;
  //case section_curvature_y:
    // unsigned normal curvature with respect to sections cut perp to world y axis
    //cs = section_curvature_y;
    //break;
  //case section_curvature_z:
    // unsigned normal curvature with respect to sections cut perp to world z axis
    //cs = section_curvature_z;
    //break;
  }
  return cs;
}

/*enum view_type // This is already in the header. I commented it out to see if it would compile and it does. John Croudy.
{
  model_view_type     = 0,
  plot_page_view_type = 1,
  nested_view_type    = 2 
};*/

ON::view_type ON::ViewType(int vt)
{
  switch(vt)
  {
  case model_view_type:       return (model_view_type);       break;
  case page_view_type:        return (page_view_type);        break;
  case nested_view_type:      return (nested_view_type);      break;
  case uveditor_view_type:    return (uveditor_view_type);    break;
  case blockeditor_view_type: return (blockeditor_view_type); break;
  }

  return (model_view_type);
}


ON::v3_display_mode ON::V3DisplayMode(int i)
{
  // convert integer to light_style enum
  ON::v3_display_mode dm = ON::v3_default_display;
  switch(i) {
  case ON::v3_default_display:
    dm = ON::v3_default_display;
    break;
  case ON::v3_wireframe_display:
    dm = ON::v3_wireframe_display;
    break;
  case ON::v3_shaded_display:
    dm = ON::v3_shaded_display;
    break;
  case ON::v3_renderpreview_display: 
    dm = ON::v3_renderpreview_display;
    break;
  }
  return dm;
}


ON::texture_mode ON::TextureMode(int i)
{
  // convert integer to texture_mode enum
  ON::texture_mode tm;
  switch (i) {
  case no_texture:
    tm = no_texture;
    break;
  case modulate_texture:
    tm = modulate_texture;
    break;
  case decal_texture:
    tm = decal_texture;
    break;
  default:
    tm = no_texture;
    break;
  }
  return tm;
}

ON::object_type ON::ObjectType(int i)
{
  // convert integer to object_type enum
  object_type ot = ON::object_type::unknown_object_type;
  switch(i) 
  {
  case ON::object_type::unknown_object_type:  ot = ON::object_type::unknown_object_type; break;

  case ON::object_type::point_object:         ot = ON::object_type::point_object; break;
  case ON::object_type::pointset_object:      ot = ON::object_type::pointset_object; break;
  case ON::object_type::curve_object:         ot = ON::object_type::curve_object; break;
  case ON::object_type::surface_object:       ot = ON::object_type::surface_object; break;
  case ON::object_type::brep_object:          ot = ON::object_type::brep_object; break;
  case ON::object_type::mesh_object:          ot = ON::object_type::mesh_object; break;
  case ON::object_type::layer_object:         ot = ON::object_type::layer_object; break;
  case ON::object_type::material_object:      ot = ON::object_type::material_object; break;
  case ON::object_type::light_object:         ot = ON::object_type::light_object; break;
  case ON::object_type::annotation_object:    ot = ON::object_type::annotation_object; break;
  case ON::object_type::userdata_object:      ot = ON::object_type::userdata_object; break;
  case ON::object_type::instance_definition:  ot = ON::object_type::instance_definition; break;
  case ON::object_type::instance_reference:   ot = ON::object_type::instance_reference; break;
  case ON::object_type::text_dot:             ot = ON::object_type::text_dot; break;
  case ON::object_type::grip_object:          ot = ON::object_type::grip_object; break;
  case ON::object_type::detail_object:        ot = ON::object_type::detail_object; break;
  case ON::object_type::hatch_object:         ot = ON::object_type::hatch_object; break;
  case ON::object_type::morph_control_object: ot = ON::object_type::morph_control_object; break;
  case ON::object_type::loop_object:          ot = ON::object_type::loop_object; break;
  case ON::object_type::polysrf_filter:       ot = ON::object_type::polysrf_filter; break;
  case ON::object_type::edge_filter:          ot = ON::object_type::edge_filter; break;
  case ON::object_type::polyedge_filter:      ot = ON::object_type::polyedge_filter; break;
  case ON::object_type::meshvertex_filter:    ot = ON::object_type::meshvertex_filter; break;
  case ON::object_type::meshedge_filter:      ot = ON::object_type::meshedge_filter; break;
  case ON::object_type::meshface_filter:      ot = ON::object_type::meshface_filter; break;
  case ON::object_type::cage_object:          ot = ON::object_type::cage_object; break;
  case ON::object_type::phantom_object:       ot = ON::object_type::phantom_object; break;
  case ON::object_type::extrusion_object:     ot = ON::object_type::extrusion_object; break;
  case ON::object_type::meshcomponent_reference: ot = ON::object_type::meshcomponent_reference; break;

  default: ot = ON::object_type::unknown_object_type; break;
  }

  return ot;
}

ON::bitmap_type ON::BitmapType(int i)
{
  // convert integer to object_type enum
  bitmap_type bt = unknown_bitmap_type;
  switch(i) {
  case unknown_bitmap_type: bt = unknown_bitmap_type; break;
  case windows_bitmap:      bt = windows_bitmap; break;
  case opengl_bitmap:       bt = opengl_bitmap; break;
  case png_bitmap:          bt = png_bitmap; break;
  default: bt = unknown_bitmap_type; break;
  }
  return bt;
}

ON::object_decoration ON::ObjectDecoration(int i)
{
  ON::object_decoration d;
  switch(i)
  {
  case no_object_decoration: d = no_object_decoration; break;
  case start_arrowhead:      d = start_arrowhead; break;
  case end_arrowhead:        d = end_arrowhead;   break;
  case both_arrowhead:       d = both_arrowhead;  break;
  default:                   d = no_object_decoration; break;
  }
  return d;
}


ON::osnap_mode ON::OSnapMode(int i)
{
  ON::osnap_mode osm;
  switch((unsigned int)i)
  {
  case os_none:          osm = os_none; break;
  case os_near:          osm = os_near; break;
  case os_focus:         osm = os_focus; break;
  case os_center:        osm = os_center; break;
  case os_vertex:        osm = os_vertex; break;
  case os_knot:          osm = os_knot; break;
  case os_quadrant:      osm = os_quadrant; break;
  case os_midpoint:      osm = os_midpoint; break;
  case os_intersection:  osm = os_intersection; break;
  case os_end:           osm = os_end; break;
  case os_perpendicular: osm = os_perpendicular; break;
  case os_tangent:       osm = os_tangent; break;
  case os_point:         osm = os_point; break;
  case os_all_snaps:     osm = os_all_snaps; break;
  default:
    osm = os_none;
    break;
  };
  return osm;
}


ON::cubic_loft_end_condition ON::CubicLoftEndCondition(int i)
{
  ON::cubic_loft_end_condition e;
  switch(i)
  {
  case cubic_loft_ec_quadratic:
    e = ON::cubic_loft_ec_quadratic;
    break;
  case cubic_loft_ec_linear:
    e = ON::cubic_loft_ec_linear;
    break;
  case cubic_loft_ec_cubic:
    e = ON::cubic_loft_ec_cubic;
    break;
  case cubic_loft_ec_natural:
    e = ON::cubic_loft_ec_natural;
    break;
  case cubic_loft_ec_unit_tangent:
    e = ON::cubic_loft_ec_unit_tangent;
    break;
  case cubic_loft_ec_1st_derivative:
    e = ON::cubic_loft_ec_1st_derivative;
    break;
  case cubic_loft_ec_2nd_derivative:
    e = ON::cubic_loft_ec_2nd_derivative;
    break;
  case cubic_loft_ec_free_cv:
    e = ON::cubic_loft_ec_free_cv;
    break;
  default:
    ON_ERROR("ON::CubicLoftEndCondition(i) value of i is not valid.");
    e = ON::cubic_loft_ec_quadratic;
    break;
  }
  return e;
}


ON::mesh_type ON::MeshType(int i)
{
  mesh_type mt = ON::mesh_type::default_mesh;
  switch(i)
  {
  case (int)ON::mesh_type::default_mesh:  mt = ON::mesh_type::default_mesh;  break;
  case (int)ON::mesh_type::render_mesh:   mt = ON::mesh_type::render_mesh;   break;
  case (int)ON::mesh_type::analysis_mesh: mt = ON::mesh_type::analysis_mesh; break;
  case (int)ON::mesh_type::preview_mesh:  mt = ON::mesh_type::preview_mesh; break;
  case (int)ON::mesh_type::any_mesh:      mt = ON::mesh_type::any_mesh;      break;
  default:            mt = ON::mesh_type::default_mesh;  break;
  }
  return mt;
}


ON_INTERNAL_OBSOLETE::V5_eAnnotationType ON_INTERNAL_OBSOLETE::V5AnnotationTypeFromUnsigned(unsigned int v5_annotation_type_as_unsigned)
{
  // convert integer to eAnnotationType enum
  switch(v5_annotation_type_as_unsigned) 
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtNothing);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimLinear);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAligned);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAngular);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimRadius);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtLeader);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtTextBlock);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimOrdinate);
  }
  ON_ERROR("Invalid v5_annotation_type_as_unsigned value");
  return (ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtNothing);
}

ON::ComponentNameConflictResolution ON::ComponentNameConflictResolutionFromUnsigned(
  unsigned int component_name_conflict_resolution_as_unsigned
)
{
  switch (component_name_conflict_resolution_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON::ComponentNameConflictResolution::Unset);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::ComponentNameConflictResolution::QueryMethod);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::ComponentNameConflictResolution::UseExistingComponent);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::ComponentNameConflictResolution::ReplaceExistingComponent);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::ComponentNameConflictResolution::KeepBothComponentsAutomaticRename);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::ComponentNameConflictResolution::KeepBothComponentsQueryRename);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::ComponentNameConflictResolution::NoConflict);
  }
  ON_ERROR("Invalid component_name_conflict_resolution_as_unsigned value");
  return (ON::ComponentNameConflictResolution::Unset);
}


ON_INTERNAL_OBSOLETE::V5_vertical_alignment ON_INTERNAL_OBSOLETE::V5VerticalAlignmentFromUnsigned(
  unsigned int vertical_alignment_as_unsigned
  )
{
  switch (vertical_alignment_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Centered);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Above);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Below);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Top);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_vertical_alignment::FirstLine);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Middle);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_vertical_alignment::LastLine);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Bottom);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Underlined);
  }
  ON_ERROR("invalid vertical_alignment_as_unsigned parameter.");
  return (ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Centered);
}

ON_INTERNAL_OBSOLETE::V5_vertical_alignment ON_INTERNAL_OBSOLETE::V5VerticalAlignmentFromV6VerticalAlignment(
  const ON::TextVerticalAlignment text_vertical_alignment
)
{
  ON_INTERNAL_OBSOLETE::V5_vertical_alignment valign = ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Centered;

  switch (text_vertical_alignment)
  {
  case ON::TextVerticalAlignment::Top:
    valign = ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Top;
    break;
  case ON::TextVerticalAlignment::MiddleOfTop:
    valign = ON_INTERNAL_OBSOLETE::V5_vertical_alignment::FirstLine;
    break;
  case ON::TextVerticalAlignment::BottomOfTop:
    // no exact mapping works - this works if there is one line of text
    valign = ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Bottom;
    break;
  case ON::TextVerticalAlignment::Middle:
    valign = ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Middle;
    break;
  case ON::TextVerticalAlignment::MiddleOfBottom:
    valign = ON_INTERNAL_OBSOLETE::V5_vertical_alignment::LastLine;
    break;
  case ON::TextVerticalAlignment::Bottom:
    valign = ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Bottom;
    break;
  case ON::TextVerticalAlignment::BottomOfBoundingBox:
    valign = ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Underlined;
    break;
  }

  return valign;
}

ON::TextVerticalAlignment ON_INTERNAL_OBSOLETE::V6VerticalAlignmentFromV5VerticalAlignment(
  ON_INTERNAL_OBSOLETE::V5_vertical_alignment V5_vertical_alignment
)
{
  ON::TextVerticalAlignment valign = ON::TextVerticalAlignment::Middle;

  switch (V5_vertical_alignment)
  {
  case ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Centered:
    valign = ON::TextVerticalAlignment::Middle;    
    break;
  case ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Above:
    // V5 text "above" dim line means "bottom" of text bbox is at insertion point above dim line
    valign = ON::TextVerticalAlignment::Bottom;    
    break;
  case ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Below:
    // V5 text "below" dim line means "top" of text bbox is at insertion point below dim line
    valign = ON::TextVerticalAlignment::Top;    
    break;
  case ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Top:
    valign = ON::TextVerticalAlignment::Top;    
    break;
  case ON_INTERNAL_OBSOLETE::V5_vertical_alignment::FirstLine:
    valign = ON::TextVerticalAlignment::MiddleOfTop;    
    break;
  case ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Middle:
    valign = ON::TextVerticalAlignment::Middle;    
    break;
  case ON_INTERNAL_OBSOLETE::V5_vertical_alignment::LastLine:
    valign = ON::TextVerticalAlignment::MiddleOfBottom;    
    break;
  case ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Bottom:
    valign = ON::TextVerticalAlignment::Bottom;    
    break;
  case ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Underlined:
    valign = ON::TextVerticalAlignment::BottomOfBoundingBox;
    break;
  }

  return valign;
}


ON_INTERNAL_OBSOLETE::V5_horizontal_alignment ON_INTERNAL_OBSOLETE::V5HorizontalAlignmentFromUnsigned(
  unsigned int horizontal_alignment_as_unsigned
  )
{
  switch (horizontal_alignment_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_horizontal_alignment::Left);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_horizontal_alignment::Center);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_horizontal_alignment::Right);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_INTERNAL_OBSOLETE::V5_horizontal_alignment::Auto);
  }
  ON_ERROR("invalid horizontal_alignment_as_unsigned parameter.");
  return (ON_INTERNAL_OBSOLETE::V5_horizontal_alignment::Left);
}

ON_INTERNAL_OBSOLETE::V5_horizontal_alignment ON_INTERNAL_OBSOLETE::V5HorizontalAlignmentFromV6HorizontalAlignment(
  const ON::TextHorizontalAlignment text_horizontal_alignment
)
{
  ON_INTERNAL_OBSOLETE::V5_horizontal_alignment halign = ON_INTERNAL_OBSOLETE::V5_horizontal_alignment::Left;

  switch (text_horizontal_alignment)
  {
  case ON::TextHorizontalAlignment::Left:
    halign = ON_INTERNAL_OBSOLETE::V5_horizontal_alignment::Left;
    break;
  case ON::TextHorizontalAlignment::Center:
    halign = ON_INTERNAL_OBSOLETE::V5_horizontal_alignment::Center;
    break;
  case ON::TextHorizontalAlignment::Right:
    halign = ON_INTERNAL_OBSOLETE::V5_horizontal_alignment::Right;
    break;
  case ON::TextHorizontalAlignment::Auto:
    halign = ON_INTERNAL_OBSOLETE::V5_horizontal_alignment::Left;
    break;
  }

  return halign;
}

ON::TextHorizontalAlignment ON_INTERNAL_OBSOLETE::V6HorizontalAlignmentFromV5HorizontalAlignment(
  ON_INTERNAL_OBSOLETE::V5_horizontal_alignment V5_vertical_alignment
)
{
  ON::TextHorizontalAlignment halign = ON::TextHorizontalAlignment::Left;

  switch (V5_vertical_alignment)
  {
  case ON_INTERNAL_OBSOLETE::V5_horizontal_alignment::Left:
    halign = ON::TextHorizontalAlignment::Left;
    break;
  case ON_INTERNAL_OBSOLETE::V5_horizontal_alignment::Center:
    halign = ON::TextHorizontalAlignment::Center;
    break;
  case ON_INTERNAL_OBSOLETE::V5_horizontal_alignment::Right:
    halign = ON::TextHorizontalAlignment::Right;
    break;
  case ON_INTERNAL_OBSOLETE::V5_horizontal_alignment::Auto:
    halign = ON::TextHorizontalAlignment::Left;
    break;
  }

  return halign;
}

ON_2dex::ON_2dex(
  int iValue,
  int jValue)
  : i(iValue)
  , j(jValue)
{}

ON_2dex ON_2dex::AsIncreasing() const
{
  ON_2dex rc;
  if (j < i)
  {
    rc.i = j;
    rc.j = i;
  }
  else
  {
    rc.i = i;
    rc.j = j;
  }
  return rc;
}

ON_2dex ON_2dex::AsDecreasing() const
{
  ON_2dex rc;
  if (i < j)
  {
    rc.i = j;
    rc.j = i;
  }
  else
  {
    rc.i = i;
    rc.j = j;
  }
  return rc;
}

ON_2udex ON_2udex::AsIncreasing() const
{
  ON_2udex rc;
  if (j < i)
  {
    rc.i = j;
    rc.j = i;
  }
  else
  {
    rc.i = i;
    rc.j = j;
  }
  return rc;
}

ON_2udex ON_2udex::AsDecreasing() const
{
  ON_2udex rc;
  if (i < j)
  {
    rc.i = j;
    rc.j = i;
  }
  else
  {
    rc.i = i;
    rc.j = j;
  }
  return rc;
}

bool ON_2dex::operator==(const ON_2dex& src) const
{
  return i == src.i && j == src.j;
}

bool ON_2dex::operator!=(const ON_2dex& src) const
{
  return i != src.i || j != src.j;
}

bool ON_2udex::operator==(const ON_2udex& src) const
{
  return i == src.i && j == src.j;
}

bool ON_2udex::operator!=(const ON_2udex& src) const
{
  return i != src.i || j != src.j;
}

bool ON_2udex::operator<(const ON_2udex& src) const
{
  return i < src.i || ((j == src.j) && j < src.j);
}

bool ON_2udex::operator<=(const ON_2udex& src) const
{
  return i < src.i || ((j == src.j) && j <= src.j);
}

bool ON_2udex::operator>=(const ON_2udex& src) const
{
  return i > src.i || ((j == src.j) && j >= src.j);
}

bool ON_2udex::operator>(const ON_2udex& src) const
{
  return i > src.i || ((j == src.j) && j > src.j);
}

bool ON_4dex::operator==(const ON_4dex& src) const
{
  return i == src.i && j == src.j && k == src.k && l == src.l;
}

bool ON_4dex::operator!=(const ON_4dex& src) const
{
  return i != src.i || j != src.j || k != src.k || l != src.l;
}

bool ON_4udex::operator==(const ON_4udex& src) const
{
  return i == src.i && j == src.j && k == src.k && l == src.l;
}

bool ON_4udex::operator!=(const ON_4udex& src) const
{
  return i != src.i || j != src.j || k != src.k || l != src.l;
}

ON_3dex::ON_3dex(
  int iValue,
  int jValue,
  int kValue)
  : i(iValue)
  , j(jValue)
  , k(kValue)
{}

ON_4dex::ON_4dex(
  int iValue,
  int jValue,
  int kValue,
  int lValue)
  : i(iValue)
  , j(jValue)
  , k(kValue)
  , l(lValue)
{}

ON_4dex ON_4dex::AsIncreasing() const
{
  auto rc = ON_4dex(i, j, k, l);
  if (j < i) std::swap(rc.i, rc.j);
  if (k < i) std::swap(rc.i, rc.k);
  if (j < i) std::swap(rc.i, rc.l);
  if (k < j) std::swap(rc.j, rc.k);
  if (l < j) std::swap(rc.j, rc.l);
  if (l < k) std::swap(rc.k, rc.l);
  return rc;
}

ON_4dex ON_4dex::AsPairwiseIncreasing() const
{
  auto rc = ON_4dex(i, j, k, l);
  if (k < i)
  {
    std::swap(rc.i, rc.k);
    std::swap(rc.j, rc.l);
  }
  else if (i == k && l < j)
  {
    std::swap(rc.j, rc.l);
  }
  return rc;
}

ON_4udex ON_4udex::AsIncreasing() const
{
  auto rc = ON_4udex(i, j, k, l);
  if (j < i) std::swap(rc.i, rc.j);
  if (k < i) std::swap(rc.i, rc.k);
  if (j < i) std::swap(rc.i, rc.l);
  if (k < j) std::swap(rc.j, rc.k);
  if (l < j) std::swap(rc.j, rc.l);
  if (l < k) std::swap(rc.k, rc.l);
  return rc;
}

ON_4udex ON_4udex::AsPairwiseIncreasing() const
{
  auto rc = ON_4udex(i, j, k, l);
  if (k < i)
  {
    std::swap(rc.i, rc.k);
    std::swap(rc.j, rc.l);
  }
  else if (i == k && l < j)
  {
    std::swap(rc.j, rc.l);
  }
  return rc;
}

int ON_4dex::operator[](int ind) const
{ 
	switch (ind) {
	case 0:
		return i;
	case 1:
		return j;
	case 2:
		return k;
	}
	return l;
}

int& ON_4dex::operator[](int ind)
{
	switch (ind) {
	case 0:
		return i;
	case 1:
		return j;
	case 2:
		return k;
	}
	return l;
}

ON_2udex::ON_2udex(
  unsigned int iValue,
  unsigned int jValue)
  : i(iValue)
  , j(jValue)
{}

int ON_2udex::DictionaryCompare(
  const ON_2udex* lhs,
  const ON_2udex* rhs
)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  if (lhs->i < rhs->i)
    return -1;
  if (lhs->i > rhs->i)
    return 1;
  if (lhs->j < rhs->j)
    return -1;
  if (lhs->j > rhs->j)
    return 1;
  return 0;
}

int ON_2udex::CompareFirstIndex(
  const ON_2udex* lhs,
  const ON_2udex* rhs
)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  if (lhs->i < rhs->i)
    return -1;
  if (lhs->i > rhs->i)
    return 1;
  return 0;
}

int ON_2udex::CompareSecondIndex(
  const ON_2udex* lhs,
  const ON_2udex* rhs
)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  if (lhs->j < rhs->j)
    return -1;
  if (lhs->j > rhs->j)
    return 1;
  return 0;
}



ON_3udex::ON_3udex(
  unsigned int iValue,
  unsigned int jValue,
  unsigned int kValue)
  : i(iValue)
  , j(jValue)
  , k(kValue)
{}

int ON_3udex::DictionaryCompare(
  const ON_3udex* lhs,
  const ON_3udex* rhs
)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  if (lhs->i < rhs->i)
    return -1;
  if (lhs->i > rhs->i)
    return 1;
  if (lhs->j < rhs->j)
    return -1;
  if (lhs->j > rhs->j)
    return 1;
  if (lhs->k < rhs->k)
    return -1;
  if (lhs->k > rhs->k)
    return 1;
  return 0;
}

int ON_3udex::CompareFirstIndex(
  const ON_3udex* lhs,
  const ON_3udex* rhs
)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  if (lhs->i < rhs->i)
    return -1;
  if (lhs->i > rhs->i)
    return 1;
  return 0;
}

int ON_3udex::CompareSecondIndex(
  const ON_3udex* lhs,
  const ON_3udex* rhs
)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  if (lhs->j < rhs->j)
    return -1;
  if (lhs->j > rhs->j)
    return 1;
  return 0;
}

int ON_3udex::CompareThirdIndex(
  const ON_3udex* lhs,
  const ON_3udex* rhs
)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  if (lhs->k < rhs->k)
    return -1;
  if (lhs->k > rhs->k)
    return 1;
  return 0;
}

int ON_3udex::CompareFirstAndSecondIndex(
  const ON_3udex* lhs,
  const ON_3udex* rhs
)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  if (lhs->i < rhs->i)
    return -1;
  if (lhs->i > rhs->i)
    return 1;
  if (lhs->j < rhs->j)
    return -1;
  if (lhs->j > rhs->j)
    return 1;
  return 0;
}

ON_4udex::ON_4udex(
  unsigned int iValue,
  unsigned int jValue,
  unsigned int kValue,
  unsigned int lValue)
  : i(iValue)
  , j(jValue)
  , k(kValue)
  , l(lValue)
{}

void ON_StopWatch::Start()
{
  if (ON_StopWatch::State::Off == m_state || ON_StopWatch::State::Stopped == m_state)
  {
    m_state = ON_StopWatch::State::Running;
    m_start = std::chrono::high_resolution_clock::now();
  }
}

double ON_StopWatch::Stop()
{
  const std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
  double d;
  if ( ON_StopWatch::State::Running == m_state)
  {
    m_stop = t;
    m_state = ON_StopWatch::State::Stopped;
    d = ElapsedTime();
  }
  else
  {
    d = 0.0;
  }
  return d;
}

void ON_StopWatch::Reset()
{
  m_state = ON_StopWatch::State::Off;
}

ON_StopWatch::State ON_StopWatch::CurrentState() const
{
  return m_state;
}

double ON_StopWatch::ElapsedTime() const
{
  std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
  if (ON_StopWatch::State::Stopped == m_state)
    t = m_stop;
  double d;
  if (ON_StopWatch::State::Stopped == m_state || ON_StopWatch::State::Running == m_state)
  {
    //d = std::chrono::duration< double, std::chrono::high_resolution_clock::period >(t - m_start).count();
    d = std::chrono::duration<double, std::ratio<1, 1> >(t - m_start).count();
  }
  else
  {
    d = 0.0;
  }
  return d;
}

ON::LineCapStyle ON::LineCapStyleFromUnsigned(
  unsigned int cap_as_unsigned
)
{
  switch (cap_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON::LineCapStyle::Round);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::LineCapStyle::Flat);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::LineCapStyle::Square);
  }
  ON_ERROR("invalid cap_as_unsigned parameter.");
  return ON::LineCapStyle::Round;
}

ON::LineJoinStyle ON::LineJoinStyleFromUnsigned(
  unsigned int join_as_unsigned
)
{
  switch (join_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON::LineJoinStyle::Round);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::LineJoinStyle::Miter);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::LineJoinStyle::Bevel);
  }
  ON_ERROR("invalid join_as_unsigned parameter.");
  return ON::LineJoinStyle::Round;
}


ON::SectionFillRule ON::SectionFillRuleFromUnsigned(
  unsigned int section_fill_rule_as_unsigned
)
{
  switch (section_fill_rule_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON::SectionFillRule::ClosedCurves);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::SectionFillRule::SolidObjects);
  }
  ON_ERROR("invalid section_fill_rule_as_unsigned parameter.");
  return ON::SectionFillRule::ClosedCurves;
}

ON::SectionAttributesSource ON::SectionAttributesSourceFromUnsigned(
  unsigned int section_attributes_source_as_unsigned
)
{
  switch (section_attributes_source_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON::SectionAttributesSource::FromLayer);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::SectionAttributesSource::FromObject);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::SectionAttributesSource::FromParent);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::SectionAttributesSource::FromSectioner);
  }
  ON_ERROR("invalid section_attributes_source_as_unsigned parameter.");
  return ON::SectionAttributesSource::FromLayer;
}

ON::SectionLabelStyle ON::SectionLabelStyleFromUnsigned(
  unsigned int section_label_style_as_unsigned
)
{
  switch (section_label_style_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON::SectionLabelStyle::None);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::SectionLabelStyle::TextDotFromName);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::SectionLabelStyle::TextFromName);
  }
  ON_ERROR("invalid section_label_style_as_unsigned parameter.");
  return ON::SectionLabelStyle::None;
}


ON::ViewSectionBehavior ON::ViewSectionBehaviorFromUnsigned(
  unsigned int view_section_behavior_as_unsigned
)
{
  switch (view_section_behavior_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON::ViewSectionBehavior::ClipAndSection);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::ViewSectionBehavior::SectionOnly);
  }
  ON_ERROR("invalid view_section_behavior_as_unsigned parameter.");
  return ON::ViewSectionBehavior::ClipAndSection;
}
