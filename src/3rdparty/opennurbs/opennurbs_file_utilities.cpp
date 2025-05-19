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

#if defined(ON_COMPILER_MSC) && defined(ON_RUNTIME_WIN)
// November 2015: Visual Studo 2013 (and probably others)
// Shlwapi.h and Shlobj.h are not included in opennurbs_system.h 
// because the have gems like "#define small ..." (Thank You Microsoft!).
// Turns out there is plenty of code that uses opennurbs where crazy 
// developers thought "small" would be a reasonable name for a local
// variable.  Reminds me of dealing with AutoDesk's old #define X 0
// in their headers from 20 years ago. 
#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <Shlwapi.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE
#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <Shlobj.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE
#if defined(_M_X64) && defined(WIN32) && defined(WIN64)
// Shlwapi.h, Shlobj.h and perhaps others, unconditionally define WIN32
#undef WIN32
#endif
#endif

#if defined(ON_RUNTIME_APPLE)
#include "unistd.h" //for unlink
#endif

///////////////////////////////////////////////////////////////////////////////

void ON_String::SplitPath(
  const char* path,
  ON_String* drive,
  ON_String* dir,
  ON_String* fname,
  ON_String* ext
  )
{
  ON_FileSystemPath::SplitPath(
    path,
    drive,
    dir,
    fname,
    ext
    );
}

bool ON_FileSystemPath::IsDirectorySeparator(
  char c,
  bool bAllowAlternate
  )
{
  return (c == ON_FileSystemPath::DirectorySeparatorAsChar || (bAllowAlternate && c == ON_FileSystemPath::DirectorySeparatorAsChar));
}

bool ON_FileSystemPath::IsDirectorySeparator(
  wchar_t c,
  bool bAllowAlternate
  )
{
  return (c == ON_FileSystemPath::DirectorySeparator || (bAllowAlternate && c == ON_FileSystemPath::AlternateDirectorySeparator));
}

void ON_FileSystemPath::SplitPath(
    const char* path,
    ON_String* drive,
    ON_String* dir,
    ON_String* file_name_stem,
    ON_String* ext
    )
{
  const char* dr = 0;
  const char* d = 0;
  const char* f = 0;
  const char* e = 0;

  // Use local path in case drive, dir, file_name_stem or ext are being reused.
  const ON_String local_path(path);
  path = static_cast<const char*>(local_path);
  on_splitpath(path,&dr,&d,&f,&e);

  if ( 0 != drive )
  {
    if ( 0 != dr )
    {
      int length;
      if ( 0 != d )
        length = (int)(d-dr);
      else if ( 0 != f )
        length = (int)(f-dr);
      else if ( 0 != e )
        length = (int)(e-dr);
      else
        length = ON_String::Length(dr);
      *drive = ON_String(dr,length);
    }
    else
      drive->Empty();
  }

  if ( 0 != dir )
  {
    if ( 0 != d )
    {
      int length;
      if ( 0 != f )
        length = (int)(f-d);
      else if ( 0 != e )
        length = (int)(e-d);
      else
        length = ON_String::Length(d);

      *dir = ON_String(d,length);
    }
    else
      dir->Empty();
  }

  if ( 0 != file_name_stem )
  {
    if ( 0 != f )
    {
      int length;
      if ( 0 != e )
        length = (int)(e-f);
      else
        length = ON_String::Length(f);

      *file_name_stem = ON_String(f,length);
    }
    else
      file_name_stem->Empty();
  }

  if ( 0 != ext )
  {
    *ext = e;
  }
}

void ON_wString::SplitPath(
  const char* path,
  ON_wString* drive,
  ON_wString* dir,
  ON_wString* fname,
  ON_wString* ext
  )
{
  ON_FileSystemPath::SplitPath(
    path,
    drive,
    dir,
    fname,
    ext
    );
}

void ON_FileSystemPath::SplitPath(
    const char* path,
    ON_wString* drive,
    ON_wString* dir,
    ON_wString* file_name_stem,
    ON_wString* ext
    )
{
  const char* dr = 0;
  const char* d = 0;
  const char* f = 0;
  const char* e = 0;

  // Use local path in case drive, dir, file_name_stem or ext are being reused.
  const ON_String local_path(path);
  path = static_cast<const char*>(local_path);
  on_splitpath(path,&dr,&d,&f,&e);

  if ( 0 != drive )
  {
    if ( 0 != dr )
    {
      int length;
      if ( 0 != d )
        length = (int)(d-dr);
      else if ( 0 != f )
        length = (int)(f-dr);
      else if ( 0 != e )
        length = (int)(e-dr);
      else
        length = ON_String::Length(dr);

      *drive = ON_wString(dr,length);
    }
    else
      drive->Empty();
  }

  if ( 0 != dir )
  {
    if ( 0 != d )
    {
      int length;
      if ( 0 != f )
        length = (int)(f-d);
      else if ( 0 != e )
        length = (int)(e-d);
      else
        length = ON_String::Length(d);

      *dir = ON_wString(d,length);
    }
    else
      dir->Empty();
  }

  if ( 0 != file_name_stem )
  {
    if ( 0 != f )
    {
      int length;
      if ( 0 != e )
        length = (int)(e-f);
      else
        length = ON_String::Length(f);

      *file_name_stem = ON_wString(f,length);
    }
    else
      file_name_stem->Empty();
  }

  if ( 0 != ext )
  {
    *ext = e;
  }
}


void ON_wString::SplitPath(
  const wchar_t* path,
  ON_wString* drive,
  ON_wString* dir,
  ON_wString* fname,
  ON_wString* ext
  )
{
  ON_FileSystemPath::SplitPath( 
    path,
    drive,
    dir,
    fname,
    ext
    );
}

void ON_FileSystemPath::SplitPath(
  const wchar_t* path,
  ON_wString* drive,
  ON_wString* dir,
  ON_wString* file_name_stem_and_extension
)
{
  const wchar_t* dr = 0;
  const wchar_t* d = 0;
  const wchar_t* f = 0;
  const wchar_t* e = 0;

  // Use local path in case drive, dir, file_name_stem or ext are being reused.
  const ON_wString local_path(path);
  path = static_cast<const wchar_t*>(local_path);
  on_wsplitpath(path,&dr,&d,&f,&e);

  if ( 0 != drive )
  {
    if ( 0 != dr )
    {
      int length;
      if ( 0 != d )
        length = (int)(d-dr);
      else if ( 0 != f )
        length = (int)(f-dr);
      else if ( 0 != e )
        length = (int)(e-dr);
      else
        length = ON_wString::Length(dr);

      *drive = ON_wString(dr,length);
    }
    else
      drive->Empty();
  }

  if ( 0 != dir )
  {
    if ( 0 != d )
    {
      int length;
      if ( 0 != f )
        length = (int)(f-d);
      else if ( 0 != e )
        length = (int)(e-d);
      else
        length = ON_wString::Length(d);
      *dir = ON_wString(d,length);
    }
    else
      dir->Empty();
  }

  if ( 0 != file_name_stem_and_extension )
  {
    if ( 0 != f )
    {
      *file_name_stem_and_extension = f;
    }
    else if ( 0 != e )
    {
      // "C:/dir/.abc" returns ".abc"
      *file_name_stem_and_extension = e;
    }
    else
      file_name_stem_and_extension->Empty();
  }
}


void ON_FileSystemPath::SplitPath( 
  const wchar_t* path,
  ON_wString* drive,
  ON_wString* dir,
  ON_wString* file_name_stem,
  ON_wString* ext
  )
{
  const wchar_t* dr = 0;
  const wchar_t* d = 0;
  const wchar_t* f = 0;
  const wchar_t* e = 0;

  // Use local path in case drive, dir, file_name_stem or ext are being reused.
  const ON_wString local_path(path);
  path = static_cast<const wchar_t*>(local_path);
  on_wsplitpath(path,&dr,&d,&f,&e);

  if ( 0 != drive )
  {
    if ( 0 != dr )
    {
      int length;
      if ( 0 != d )
        length = (int)(d-dr);
      else if ( 0 != f )
        length = (int)(f-dr);
      else if ( 0 != e )
        length = (int)(e-dr);
      else
        length = ON_wString::Length(dr);

      *drive = ON_wString(dr,length);
    }
    else
      drive->Empty();
  }

  if ( 0 != dir )
  {
    if ( 0 != d )
    {
      int length;
      if ( 0 != f )
        length = (int)(f-d);
      else if ( 0 != e )
        length = (int)(e-d);
      else
        length = ON_wString::Length(d);
      *dir = ON_wString(d,length);
    }
    else
      dir->Empty();
  }

  if ( 0 != file_name_stem )
  {
    if ( 0 != f )
    {
      int length;
      if ( 0 != e )
        length = (int)(e-f);
      else
        length = ON_wString::Length(f);
      *file_name_stem = ON_wString(f,length);
    }
    else
      file_name_stem->Empty();
  }

  if ( 0 != ext )
  {
    *ext = e;
  }
}

const ON_wString ON_FileSystemPath::VolumeFromPath(
  const wchar_t* path
)
{
  ON_wString volume;
  ON_FileSystemPath::SplitPath(path, &volume, nullptr, nullptr, nullptr);
  return volume;
}

const ON_wString ON_FileSystemPath::DirectoryFromPath(
  const wchar_t* path
)
{
  ON_wString directory;
  ON_FileSystemPath::SplitPath(path, nullptr, &directory, nullptr, nullptr);
  return directory;
}

const ON_wString ON_FileSystemPath::VolumeAndDirectoryFromPath(
  const wchar_t* path
)
{
  ON_wString volume;
  ON_wString directory;
  ON_FileSystemPath::SplitPath(path, &volume, &directory, nullptr, nullptr);
  const ON_wString volume_and_directory( volume + directory);
  return volume_and_directory;
}

const ON_wString ON_FileSystemPath::FileNameFromPath(
  const wchar_t* path,
  bool bIncludeExtension
)
{
  ON_wString fname;
  if ( bIncludeExtension )
    ON_FileSystemPath::SplitPath(path, nullptr, nullptr, &fname);
  else
    ON_FileSystemPath::SplitPath(path, nullptr, nullptr, &fname, nullptr);
  return fname;
}

const ON_wString ON_FileSystemPath::FileNameExtensionFromPath(
  const wchar_t* path
)
{
  ON_wString ext;
  ON_FileSystemPath::SplitPath(path, nullptr, nullptr, nullptr, &ext);
  return ext;
}

static bool IsAtoZ(int c)
{
  return ((c >= 'A' && c <= 'Z') ||  (c >= 'a' && c <= 'z'));
}

static bool Is0to9(int c)
{
  return (c >= '0' && c <= '9');
}

static bool IsPermittedInPathName(int c)
{
  if ( c >= 0 && c < ON_wString::Space )
    return false;
  switch (c)
  {
  case '/':
  case '\\':
  case ':':
  case '<':
  case '>':
  case '"':
  case '?':
  case '*':
  case '|':
  //case 127:
    return false;
  }
  return true;
}

static bool IsPermittedInHostName(int c)
{
  return IsPermittedInPathName(c);
}


static bool IsDirSep(int c)
{
  switch (c)
  {
  case '/':
  case '\\':
    return true;
  }
  return false;
}

static bool IsDotDir(const wchar_t* path)
{
  return (nullptr != path && '.' == path[0] && IsDirSep(path[1]));
}

static bool IsDotDotDir(const wchar_t* path)
{
  return (nullptr != path && '.' == path[0] && '.' == path[1] && IsDirSep(path[2]));
}


bool ON_FileSystemPath::IsRelativePath(
  const wchar_t* path
  )
{
  return ON_FileSystemPath::IsRelativePath(path, 0);
}

const ON_wString ON_FileSystemPath::CurrentDirectory(
  bool bWithTrailingDirectorySeparator
  )
{
#if defined(ON_RUNTIME_WIN)

  wchar_t* directory = nullptr;
  const unsigned int directory_capacity = 2018;
  const size_t sizeof_directory = directory_capacity * sizeof(directory[0]);
  directory = (wchar_t*)onmalloc(sizeof_directory);
  memset(directory, 0, sizeof_directory);

  DWORD rc = ::GetCurrentDirectory(directory_capacity - 1, directory);
  ON_wString fullpath = directory;
  onfree(directory);

  if (rc <= 0 || fullpath.IsEmpty() )
  {
    ON_ERROR("Windows API ::GetCurrentDirectory() failed.");
    return ON_wString::EmptyString;
  }

  if (bWithTrailingDirectorySeparator)
    fullpath += ON_FileSystemPath::DirectorySeparator;
  return fullpath;

#elif defined(ON_RUNTIME_APPLE)

  char sz[PATH_MAX];
  getcwd(sz, PATH_MAX);
  return sz;

#else

  // unsupported OS
  ON_ERROR("ON_FileSystemPath::CurrentDirectory() not implemented.");
  return ON_wString::EmptyString;   
#endif
}

const ON_wString ON_FileSystemPath::RemoveVolumeName(
  const wchar_t* path,
  ON_wString* volume_name
)
{
  const ON_wString local_path = ON_FileSystemPath::CleanPath(path);
  path = static_cast<const wchar_t*>(local_path);
  const wchar_t* vol = nullptr;
  const wchar_t* dir = nullptr;
  const wchar_t* fname = nullptr;
  const wchar_t* fext = nullptr;
  on_wsplitpath(path, &vol, &dir, &fname, &fext);
  if (nullptr == dir)
  {
    if (nullptr != fname)
      dir = fname;
    else if (nullptr != fext)
      dir = fext;
  }

  if (nullptr != volume_name)
  {
    size_t length
      = (nullptr != vol && nullptr != dir && vol < dir)
      ? (int)(dir - vol)
      : 0;
    if (length > 0)
      *volume_name = ON_wString(vol, (int)length);
    else
      *volume_name = ON_wString::EmptyString;
  }
  return ON_wString(dir);
}

const ON_wString ON_FileSystemPath::RemoveFileName(
  const wchar_t* path,
  ON_wString* file_name
)
{
  const ON_wString local_path = ON_FileSystemPath::CleanPath(path);
  path = static_cast<const wchar_t*>(local_path);
  const wchar_t* vol = nullptr;
  const wchar_t* dir = nullptr;
  const wchar_t* fname = nullptr;
  on_wsplitpath(path, &vol, &dir, &fname, nullptr);
  
  const size_t length
    = (nullptr != fname && nullptr != path && path <= fname)
    ? (int)(fname - path)
    : local_path.Length();

  if (nullptr != file_name)
    *file_name = fname;

  return ON_wString(path,(int)length);
}


const ON_wString ON_FileSystemPath::CombinePaths(
  const wchar_t* left_side,
  bool bLeftSideContainsFileName,
  const wchar_t* right_side,
  bool bRightSideContainsFileName,
  bool bAppendTrailingDirectorySeparator
)
{
  ON_wString lhs_fname;
  ON_wString lhs
    = bLeftSideContainsFileName
    ? ON_FileSystemPath::RemoveFileName(left_side,&lhs_fname)
    : ON_FileSystemPath::CleanPath(left_side);

  ON_wString rhs_fname;
  ON_wString rhs 
    = bRightSideContainsFileName
    ? ON_FileSystemPath::RemoveFileName(right_side,&rhs_fname)
    : ON_FileSystemPath::CleanPath(right_side);

  ON_wString rhs_volume;
  if ( lhs.IsNotEmpty() )
    rhs = ON_FileSystemPath::RemoveVolumeName(rhs, &rhs_volume);

  if (rhs.IsNotEmpty() && ON_FileSystemPath::IsDirectorySeparator(rhs[0], true))
  {
    const ON_wString tmp(static_cast<const wchar_t*>(rhs) + 1);
    rhs = tmp;
  }

  ON_wString path = lhs;
  bool bPathEndsDirectorySeparator 
    = path.IsNotEmpty()
    && ON_FileSystemPath::IsDirectorySeparator(path[path.Length() - 1], true);
  
  if (rhs.IsNotEmpty())
  {
    if (path.IsNotEmpty() && false == bPathEndsDirectorySeparator)
      path += ON_FileSystemPath::DirectorySeparator;
    path += rhs;

    if (lhs.IsNotEmpty() && ON_FileSystemPath::IsRelativePath(rhs))
      path = ON_FileSystemPath::CleanPath(path);

    bPathEndsDirectorySeparator 
      = path.IsNotEmpty()
      && ON_FileSystemPath::IsDirectorySeparator(path[path.Length() - 1], true);
  }

  if (path.IsNotEmpty() && rhs_fname.IsNotEmpty())
    bAppendTrailingDirectorySeparator = true;

  if ((bPathEndsDirectorySeparator ? 0 : 1) != (bAppendTrailingDirectorySeparator ? 0 : 1))
  {
    if (bAppendTrailingDirectorySeparator)
    {
      const wchar_t* vol = nullptr;
      const wchar_t* dir = nullptr;
      // on_wsplitpath is called to avoid appending a directory separator to a 
      on_wsplitpath(static_cast<const wchar_t*>(path), &vol, &dir, nullptr, nullptr);
      if (nullptr != dir && false == ON_FileSystemPath::IsDirectorySeparator(path[path.Length() - 1], true))
        path += ON_FileSystemPath::DirectorySeparator;
    }
    else if ( bPathEndsDirectorySeparator )
    {
      path.SetLength(path.Length() - 1);
    }
  }

  path += rhs_fname;

  return path;
}

bool ON_FileSystemPath::IsRelativePath(
  const wchar_t* path,
  const wchar_t directory_separator
  )
{
  for (;;)
  {
    if (nullptr == path)
      break;
    if ('.' != *path)
      break;
    path++;
    if ('.' == *path)
      path++;
    if (0 != directory_separator)
    {
      if (directory_separator != *path)
        break;
    }
    else
    {
      if (ON_FileSystemPath::DirectorySeparator != *path && ON_FileSystemPath::AlternateDirectorySeparator != *path)
        break;
    }

    return true;
  }
  return false;
}

const ON_wString ON_FileSystemPath::CleanPath(
  const wchar_t* dirty_path
  )
{
  bool bTrimLeft = true;
  bool bTrimRight = true;
  bool bAllowWindowsUNCHostNameOrDiskLetter = true;
  bool bDeleteWindowsUNCHostNameOrDiskLetter = (ON_wString::Backslash != ON_FileSystemPath::DirectorySeparator);
  const wchar_t directory_separator = ON_FileSystemPath::DirectorySeparator;
  return ON_FileSystemPath::CleanPath(
    bTrimLeft,
    bTrimRight,
    bAllowWindowsUNCHostNameOrDiskLetter,
    bDeleteWindowsUNCHostNameOrDiskLetter,
    directory_separator,
    dirty_path
    );
}

static const ON_wString ON_wString_CleanPathFailed()
{
  return ON_wString::EmptyString;
}

const ON_wString ON_FileSystemPath::CleanPath(
  bool bTrimLeft,
  bool bTrimRight,
  bool bAllowWindowsUNCHostNameOrDiskLetter,
  bool bDeleteWindowsUNCHostNameOrDiskLetter,
  const wchar_t directory_separator,
  const wchar_t* dirty_path
)
{
  return ON_FileSystemPath::CleanPath(
    bTrimLeft,
    bTrimRight,
    bAllowWindowsUNCHostNameOrDiskLetter,
    bDeleteWindowsUNCHostNameOrDiskLetter,
    false,
    directory_separator,
    dirty_path
  );
}

const ON_wString ON_FileSystemPath::CleanPath(
  bool bTrimLeft,
  bool bTrimRight,
  bool bAllowWindowsUNCHostNameOrDiskLetter,
  bool bDeleteWindowsUNCHostNameOrDiskLetter,
  bool bExpandUser,
  const wchar_t directory_separator,
  const wchar_t* dirty_path
  )
{
  ON_wString local_dirty_path(dirty_path);
  if ( bTrimLeft )
    local_dirty_path.TrimLeft();
  if ( bTrimRight )
    local_dirty_path.TrimRight();
  if ( local_dirty_path.IsEmpty() )
    return ON_wString_CleanPathFailed();
  if (bExpandUser)
    local_dirty_path = ON_FileSystemPath::ExpandUser(local_dirty_path);

  dirty_path = local_dirty_path;

  const bool bIsUNCHostName 
    = bAllowWindowsUNCHostNameOrDiskLetter 
    && local_dirty_path.Length() >= 3
    && ON_wString::Backslash == local_dirty_path[0]
    && ON_wString::Backslash == local_dirty_path[1]
    && IsPermittedInHostName(local_dirty_path[2])
    && (IsAtoZ(local_dirty_path[2]) || Is0to9(local_dirty_path[2]) || local_dirty_path[2] > 127)
    ;

  const bool bIsWindowsDrive 
    = bAllowWindowsUNCHostNameOrDiskLetter
    && (false == bIsUNCHostName)
    && local_dirty_path.Length() >= 3
    && ':' == local_dirty_path[1]
    && IsAtoZ(local_dirty_path[0])
    ;

  ON_wString clean_path(dirty_path);
  wchar_t* clean_head = clean_path.Array();
  wchar_t* clean_start = clean_head;
  if (bIsUNCHostName)
  {
    clean_start += 3; // skip \\ and first character of host name
    
    // skip rest of host name
    while ( IsPermittedInHostName(*clean_start) )
      clean_start++;    
    if (false == IsDirSep(*clean_start))
      return ON_wString_CleanPathFailed();
  }
  else if (bIsWindowsDrive)
  {
    // Windows drive letter = capital letter
    *clean_start = ON_wString::MapCharacterOrdinal(ON_StringMapOrdinalType::UpperOrdinal,*clean_start);
    clean_start += 2; // Skip drive letter and colon
    if (false == IsDirSep(*clean_start))
      return ON_wString_CleanPathFailed();
  }

  if (bDeleteWindowsUNCHostNameOrDiskLetter && (bIsUNCHostName || bIsWindowsDrive))
  {
    // Delete Windows UNC host name or drive letter
    local_dirty_path = clean_start;
    dirty_path = local_dirty_path;
    clean_path = dirty_path;
    clean_head = clean_path.Array();
    clean_start = clean_head;
  }

  const size_t clean_start_offset = (clean_start - clean_head);

  wchar_t* dst = clean_start;
  wchar_t* src = dst;
  for (;;)
  {
    wchar_t c;
    // advance to directory separator
    for (c = *src; false == IsDirSep(c) && 0 != c; c = *(++src))
    {
      *dst++ = c;
    }
    if ( 0 == c )
      break;
    // normalize directory separator
    *dst++ = (0 != directory_separator) ? directory_separator : c;
    // Condense /./ and //
    for (src++; (IsDirSep(*src) || IsDotDir(src)); src++)
    {
      // empty body;
    }
  }
  *dst = 0;
  if (dst > clean_head)
  {
    clean_path.SetLength(dst - clean_head);
    clean_head = clean_path.Array();
    clean_start = clean_head + clean_start_offset;
  }
  else
  {
    return ON_wString_CleanPathFailed();
  }

  dst = clean_start;
  if (IsDirSep(*dst))
  {
    // Skip over root directory separator
    dst++;
  }
  else
  {
    // Skip over initial ../../../ ... at start of a relative path
    while (IsDotDotDir(dst))
      dst += 3;
  }
  if ( 0 == *dst )
    return clean_path;

  src = dst;
  bool bDirty = false;
  while (*src)
  {
    if (IsDotDotDir(src))
    {
      if (!bDirty)
      {
        ON_ERROR("Bug.");
        return clean_path;
      }
      // will be dealt with in the recursive clean
      *dst++ = *src++;
      *dst++ = *src++;
      *dst++ = *src++;
      continue;
    }
    wchar_t* dir = dst;
    while (false == IsDirSep(*src) && 0 != *src)
    {
      *dst++ = *src++;
    }
    if (dir == dst)
    {
      ON_ERROR("Bug.");
      return clean_path;
    }
    if (0 == *src)
    {
      break;
    }
    if (IsDotDotDir(src + 1))
    {
      // replace dir/../ with ./ and recursively clean 
      dst = dir;
      dst[0] = '.';
      dst[1] = src[3];
      dst += 2;
      src += 4;
      bDirty = true;
      while (IsDotDotDir(src))
      {
        // will be dealt with in the recursive clean
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
      }
    }
    else if (IsDirSep(*src))
    {
      *dst++ = *src++;
    }
    else
    {
      ON_ERROR("Bug");
      return clean_path;
    }
  }

  if (dst > clean_head)
  {
    *dst = 0;
    clean_path.SetLength(dst - clean_head);
    clean_head = clean_path.Array();
    clean_start = clean_head + clean_start_offset;
  }
  else
  {
    ON_ERROR("Bug.");
    return clean_path;
  }

  if ( false == bDirty )
    return clean_path;

  if (dst >= src)
  {
    ON_ERROR("Bug.");
    return clean_path;
  }

  // recursively clean 
  const ON_wString clean_tail = ON_FileSystemPath::CleanPath(false,false,false,false,0,clean_start);
  if (clean_head < clean_start)
  {
    clean_path.SetLength(clean_start - clean_head);
    clean_path += clean_tail;
  }
  else
    clean_path = clean_tail;

  return clean_path;
}

const ON_wString ON_FileSystemPath::ExpandUser(
  const char* dirty_path
)
{
  const ON_wString dirty_local_path(dirty_path);
  return ON_FileSystemPath::ExpandUser(static_cast<const wchar_t*>(dirty_local_path));
}

const ON_wString ON_FileSystemPath::ExpandUser(
  const wchar_t* dirty_path
)
{
  for(;;)
  {
    if (nullptr == dirty_path)
      break;
    if (ON_wString::Tilde != dirty_path[0])
      break;
    if (false == ON_FileSystemPath::IsDirectorySeparator(dirty_path[1], true))
      break;
    ON_wString expanduser_path = ON_FileSystemPath::PlatformPath(ON_FileSystemPath::PathId::HomeDirectory);
    if (expanduser_path.IsEmpty())
      break;
    const wchar_t dir_seps[3]
      =
    {
      ON_FileSystemPath::DirectorySeparator,
      ON_FileSystemPath::AlternateDirectorySeparator,
      0
    };
    expanduser_path.TrimRight(dir_seps);
    if (expanduser_path.IsEmpty())
      break;
    expanduser_path += ON_wString(dirty_path + 1);
    return expanduser_path;
  }
  return ON_wString(dirty_path);
}

bool ON_FileSystem::PathExists(
  const char* path
  )
{
#if defined(ON_COMPILER_MSC) && defined(ON_RUNTIME_WIN)
  return ::PathFileExistsA(path) ? true : false;
#else
  struct stat s;
  if (0 == stat(path, &s))
  {
    if (0 != (s.st_mode & (S_IFDIR|S_IFREG)))
      return true;
  }
  return false;
#endif
}

bool ON_FileSystem::PathExists(
  const wchar_t* path
  )
{
#if defined(ON_COMPILER_MSC) && defined(ON_RUNTIME_WIN)
  return ::PathFileExistsW(path) ? true : false;
#else
  const ON_String pathUTF8(path);
  return ON_FileSystem::PathExists(static_cast<const char*>(pathUTF8));
#endif
}

bool ON_FileSystem::IsDirectory(
  const char* path
  )
{
  if (0 == path || 0 == path[0])
    return false;
#if defined(ON_COMPILER_MSC) && defined(ON_RUNTIME_WIN)
  return ::PathIsDirectoryA(path) ? true : false;
#else
  struct stat s;
  if (0 == stat(path, &s))
  {
    if (0 != (s.st_mode & S_IFDIR))
      return true;
  }
  return false;
#endif
}

bool ON_FileSystem::IsDirectory(
  const wchar_t* path
  )
{
  if (0 == path || 0 == path[0])
    return false;
#if defined(ON_COMPILER_MSC) && defined(ON_RUNTIME_WIN)
  return ::PathIsDirectoryW(path) ? true : false;
#else
  const ON_String pathUTF8(path);
  return ON_FileSystem::IsDirectory(static_cast<const char*>(pathUTF8));
#endif
}

bool ON_FileSystem::IsFile(
  const char* path
  )
{
  if (0 == path || 0 == path[0])
    return false;
#if defined(ON_COMPILER_MSC) && defined(ON_RUNTIME_WIN)
  return ::PathFileExistsA(path) && 0 == ::PathIsDirectoryA(path);
#else
  struct stat s;
  if (0 == stat(path, &s))
  {
    if (0 == (s.st_mode & S_IFDIR) && 0 != (s.st_mode & S_IFREG))
      return true;
  }
  return false;
#endif
}

bool ON_FileSystem::IsFile(
  const wchar_t* path
  )
{
  if (0 == path || 0 == path[0])
    return false;
#if defined(ON_COMPILER_MSC) && defined(ON_RUNTIME_WIN)
  return ::PathFileExistsW(path) && 0 == ::PathIsDirectoryW(path);
#else
  const ON_String pathUTF8(path);
  return ON_FileSystem::IsFile(static_cast<const char*>(pathUTF8));
#endif
}


bool ON_FileSystem::RemoveFile(
  const char* file_path
)
{
  for (;;)
  {
    if ( false == ON_FileSystem::IsFile(file_path) )
      break;
    int rc;
#if defined(ON_RUNTIME_WIN)
    rc = ::_unlink(file_path);
#elif defined(ON_RUNTIME_APPLE)
    rc = ::unlink(file_path);
#else
    rc = std::remove(file_path);
#endif
    if (0 == rc)
      return true;
    break;
  }

  return false;
}

bool ON_FileSystem::RemoveFile(
  const wchar_t* file_path
)
{
  for (;;)
  {
    if ( false == ON_FileSystem::IsFile(file_path) )
      break;
    int rc;
#if defined(ON_RUNTIME_WIN)
    rc = ::_wunlink(file_path);
#elif defined(ON_RUNTIME_APPLE)
    const ON_String utf8_file_path(file_path);
    rc = ::unlink(static_cast<const char*>(utf8_file_path));
#else
    const ON_String utf8_file_path(file_path);
    rc = std::remove(static_cast<const char*>(utf8_file_path));
#endif
    if (0 == rc)
      return true;
    break;
  }

  return false;
}

bool ON_FileSystem::IsDirectoryWithWriteAccess(
  const char* path
)
{
  const ON_wString wide_path(path);
  return ON_FileSystem::IsDirectoryWithWriteAccess(static_cast<const wchar_t*>(wide_path));
}

bool ON_FileSystem::IsDirectoryWithWriteAccess(
  const wchar_t* path
)
{
  if (false == ON_FileSystem::IsDirectory(path))
    return false;

  // native OS tools that query file systems do not
  // work on some network drives.
  // According to Microsoft techs, the only failsafe way
  // is to attempt to write a file.
  // https://social.msdn.microsoft.com/Forums/windowsdesktop/en-US/f57928d3-d89b-426d-a174-d06d97355afc/how-to-check-if-a-filefolder-is-writable-or-not?forum=windowssdk


  // try 2 uuids to get a file name that is not in use.
  for (int attempt = 0; attempt < 2; attempt++)
  {
    const ON_UUID id = ON_CreateId();
    wchar_t s[41];
    memset(s, 0, sizeof(s));
    ON_UuidToString(id, s);
    s[36] = '.';
    s[37] = 't';
    s[38] = 'm';
    s[39] = 'p';
    s[40] = 0;
    const ON_wString tmpfilename = ON_FileSystemPath::CombinePaths(
      path, false, s, true, false
    );
    if (ON_FileSystem::PathExists(tmpfilename))
      continue;

    FILE* fp = ON_FileStream::Open(tmpfilename, L"wb");
    if (nullptr == fp)
      break; // cannot open a file in path
    bool bIsDirectoryWithWriteAccess = false;
    for ( ;; )
    {
      char c = 0;
      const ON__UINT64 sizeof_c = sizeof(c);
      const ON__UINT64 count = ON_FileStream::Write(fp, sizeof_c, &c);
      if (0 != ON_FileStream::Close(fp))
        break; // cannot close the file.
      fp = nullptr;
      if (count != sizeof_c)
        break; // cannot write to the file in path
      bIsDirectoryWithWriteAccess = ON_FileSystem::PathExists(tmpfilename);
      // The purpose of this function is to test if a file can be opened and
      // written to using the same tools that write .3dm files.
      //
      // It is possible to have create and write permissions but not have 
      // read permissions. For this reason, we do not attempt to read the tmp file.
      break;
    }
    if (nullptr == fp)
    {
      // The purpose of this function is to test if a file can be opened and
      // written to using the same tools that write .3dm files.
      //
      // There is speculation that when a directory is managed by dropbox 
      // or perhaps other network storage devices, there may be significant 
      // latency in the file systems that results in a time lag between calling 
      // unlink() and having ON_FileSystem::IsFile() report false.
      // For that reason, we do not check success codes on unlink 
      // or verify the tmp file is gone.
      ON_FileSystem::RemoveFile(tmpfilename);
    }
    return bIsDirectoryWithWriteAccess;
  }

  return false;
}

const ON_wString ON_FileSystemPath::FullPathFromRelativePath(
  const wchar_t* base_path,
  bool bBasePathIncludesFileName,
  const wchar_t* relative_path
  )
{
  if ( nullptr == relative_path || 0 == relative_path )
    return ON_wString::EmptyString;

  if ( nullptr == base_path || 0 == base_path[0] )
    return ON_wString::EmptyString;

  const wchar_t* base_path_end = nullptr;
  if (bBasePathIncludesFileName)
  {
    on_wsplitpath(base_path, nullptr, nullptr, &base_path_end, nullptr);
  }
  else
  {
    base_path_end = base_path + ON_wString::Length(base_path);
  }
  if (nullptr == base_path_end)
    return ON_wString::EmptyString;
  if (!(base_path < base_path_end))
    return ON_wString::EmptyString;
  
  ON_wString dirty_full_path;
  dirty_full_path.Append(base_path,(int)(base_path_end - base_path));
  if ( false == ON_FileSystemPath::IsDirectorySeparator(base_path_end[-1],true) )
    dirty_full_path += ON_FileSystemPath::DirectorySeparator;
  dirty_full_path += relative_path;
  return ON_FileSystemPath::CleanPath(dirty_full_path);
}

static bool CleanAndRemoveFileName(
  const wchar_t* dirty_path,
  bool bPathIncludesFileName,
  ON_wString& volume,
  ON_wString& clean_path,
  ON_wString* file_name
  )
{
  ON_wString path = ON_FileSystemPath::CleanPath(dirty_path);
  for (;;)
  {
    if (path.IsEmpty())
      break;

    if (false == bPathIncludesFileName && false == IsDirSep(path[path.Length() - 1]))
      path += ON_FileSystemPath::DirectorySeparator;

    const wchar_t* p = static_cast<const wchar_t*>(path);
    const wchar_t* v = nullptr;
    const wchar_t* d = nullptr;
    const wchar_t* f = nullptr;
    on_wsplitpath(p, &v, &d, bPathIncludesFileName ? &f : nullptr, nullptr);

    if (nullptr == d || 0 == d[0])
      break;
    
    clean_path = d;

    if (bPathIncludesFileName)
    {
      // remove trailing file name from base_path.
      if (nullptr == f || 0 == f[0])
        break;
      const size_t path_length = (size_t)path.Length();
      if  ( path_length <= 0 )
        break;
      if (!(p <= d && d < f && f < p + path_length))
        break;
      if (!IsDirSep(f[-1]))
        break;
      size_t len = (f - d);
      if (len <= 1 || len >= (size_t)clean_path.Length())
        break;
      if ( nullptr != file_name )
        *file_name = f;
      clean_path.SetLength(len);
    }
    else
    {
      if ( nullptr != file_name )
        *file_name = ON_wString::EmptyString;
    }

    return true;
  }

  volume = ON_wString::EmptyString;
  clean_path = ON_wString::EmptyString;
  if ( nullptr != file_name )
    *file_name = ON_wString::EmptyString;
  return false;
}

const ON_wString ON_FileSystemPath::RelativePath(
  const wchar_t* full_path,
  bool bFullPathIncludesFileName,
  const wchar_t* base_path,
  bool bBasePathIncludesFileName
  )
{
  ON_wString best_answer(full_path);

  ON_wString full_volume;
  ON_wString local_full;
  ON_wString file_name;
  if (false == CleanAndRemoveFileName(full_path,bFullPathIncludesFileName,full_volume,local_full,&file_name))
    return best_answer;

  best_answer = local_full;
  best_answer += file_name;

  ON_wString base_volume;
  ON_wString local_base;
  if (false == CleanAndRemoveFileName(base_path,bBasePathIncludesFileName,base_volume,local_base,nullptr))
    return best_answer;

  if (full_volume.IsNotEmpty() || base_volume.IsNotEmpty() )
  {
    if (false == ON_wString::EqualPath(full_volume,base_volume))
      return best_answer;
  }

  const wchar_t* full_tail = static_cast<const wchar_t*>(local_full);
  const wchar_t* base_tail = static_cast<const wchar_t*>(local_base);
  if (false == IsDirSep(*full_tail) || false == IsDirSep(*base_tail))
  {
    // A double directory separator after the initial CleanAndRemoveFileName()
    // calls indicates invalid file path information.
    return best_answer;
  }

  // Skip initial directory separator
  full_tail++;
  base_tail++;
  if (0 == *full_tail || 0 == *base_tail)
  {
    return best_answer;
  }
  if (IsDirSep(*full_tail) || IsDirSep(*base_tail))
  {
    // A double directory separator after the initial ON_FileSystemPath::CleanPath()
    // calls indicates invalid file path information.
    return best_answer;
  }

  int overlap_directory_count = 0;
  if (0 != *full_tail && 0 != *base_tail)
  {
    const wchar_t* full1 = full_tail;
    const wchar_t* base1 = base_tail;
    while (0 != *full1 && 0 != *base1 )
    {
      if (IsDotDir(base1) || IsDotDotDir(base1))
      {
        overlap_directory_count = 0;
        break;
      }
      bool bFullDirSep = IsDirSep(*full1);
      bool bBaseDirSep = IsDirSep(*base1);
      if (false == bFullDirSep && false == bBaseDirSep)
      {
        // skipping an element of a directory name 
        base1++;
        full1++;
        continue;
      }
      if (bFullDirSep && bBaseDirSep)
      {
        if (false == ON_wString::EqualPath(full_tail, (int)(full1 - full_tail), base_tail, (int)(base1 - base_tail)))
        {
         // directory names have identical lengths and different content
          break;
        }

        // matching directory names

        // skip directory separator
        base1++;
        full1++;
        if (IsDirSep(*base1) || IsDirSep(*full1))
        {
          // damaged input
          break;
        }
        base_tail = base1;
        full_tail = full1;
        overlap_directory_count++;
        continue;
      }
      // directory names have different lengths
      break;
    }
  }

  if (overlap_directory_count < 1)
    return best_answer;

  // It is reasonable for base_tail to be nullptr
  if (nullptr == full_tail && IsDirSep(*full_tail) )
    return best_answer;

  // It is reasonable for base_tail to be nullptr
  if (nullptr != base_tail && IsDirSep(*base_tail) )
    return best_answer;
  
  // set dotdot_count to number of directories left in base_tail
  int dotdot_count = 0;
  while (0 != *base_tail)
  {
    if (IsDotDir(base_tail) || IsDotDotDir(base_tail))
      return best_answer;
    if (IsDirSep(*base_tail))
    {
      if (IsDirSep(base_tail[1]))
        return best_answer; // shouldn't be double dir seps after the initial clean
      dotdot_count++;
    }
    base_tail++;
  }

  // buid relative path
  ON_wString relative_path;
  if (0 == dotdot_count)
  {
    relative_path = L".";
    relative_path += ON_FileSystemPath::DirectorySeparator;
  }
  else
  {
    for (int i = 0; i < dotdot_count; i++)
    {
      relative_path += L"..";
      relative_path += ON_FileSystemPath::DirectorySeparator;
    }
  }
  if (nullptr != full_tail && 0 != full_tail[0] )
    relative_path += full_tail;
  if (file_name.IsNotEmpty())
    relative_path += file_name;

  return relative_path;
}


//////////////////////////////////////////////////////////////////////////////
//
// ON_FileStream implementation
//

FILE* ON_FileStream::Open( const wchar_t* filename, const wchar_t* mode )
{
  FILE* fp = 0;

  if ( 0 == filename || 0 == filename[0] || 0 == mode || 0 == mode[0] )
    return fp;

#if defined(ON_COMPILER_MSC) && defined(ON_RUNTIME_WIN)
  errno_t e = _wfopen_s(&fp,filename,mode); 
  if ( 0 != e && 0 == fp )
    fp = 0; // reference e to keep lint quiet.
#else
  // I can't find an wfopen() or _wfopen() in
  // gcc version egcs-2.91.66 19990314/Linux (egcs-1.1.2 release)
  ON_String fnameUTF8(filename);
  ON_String modeUTF8(mode);
  fp = fopen(fnameUTF8,modeUTF8);
#endif

  return fp;
}

FILE* ON_FileStream::Open( const char* filename, const char* mode )
{
  FILE* fp = 0;

  if ( 0 == filename || 0 == filename[0] || 0 == mode || 0 == mode[0] )
    return fp;

#if defined(ON_COMPILER_MSC) && defined(ON_RUNTIME_WIN)
  errno_t e = fopen_s(&fp,filename,mode); 
  if ( 0 != e && 0 == fp )
    fp = 0; // reference e to keep lint quiet.
#else
  fp = fopen(filename,mode);
#endif

  return fp;
}

int ON_FileStream::Close( FILE* fp )
{
  return ( ( 0 != fp ) ? fclose(fp) : -1 );
}

bool ON_FileStream::Is3dmFile(
  const wchar_t* file_path,
  bool bAllow3dmbakExtension
)
{
  for (;;)
  {
    if (false == ON_FileSystemPath::FilePathHas3dmExtension(file_path, bAllow3dmbakExtension))
      break;
    FILE* fp = ON_FileStream::Open3dmToRead(file_path);
    if (nullptr == fp)
      break;
    ON_FileStream::Close(fp);
    return true;
  }
  return false;
}

bool ON_FileStream::Is3dmFile(
  const char* file_path,
  bool bAllow3dmbakExtension
)
{
  for (;;)
  {
    if (false == ON_FileSystemPath::FilePathHas3dmExtension(file_path, bAllow3dmbakExtension))
      break;
    FILE* fp = ON_FileStream::Open3dmToRead(file_path);
    if (nullptr == fp)
      break;
    ON_FileStream::Close(fp);
    return true;
  }
  return false;
}

bool ON_FileSystemPath::FilePathHas3dmExtension(
  const wchar_t* file_path,
  bool bAllow3dmbakExtension
)
{
  for (;;)
  {
    // test file name
    const wchar_t* e = nullptr;
    on_wsplitpath(file_path, nullptr, nullptr, nullptr, &e);
    if (nullptr == e)
      break;
    if ('.' != e[0])
      break;
    if ('3' != e[1])
      break;
    if ('d' != e[2] && 'D' != e[2])
      break;
    if ('m' != e[3] && 'M' != e[3])
      break;
    if (0 == e[4])
      return true;
    if (false == bAllow3dmbakExtension)
      break;
    if ('b' != e[4] && 'B' != e[4])
      break;
    if ('a' != e[5] && 'A' != e[5])
      break;
    if ('k' != e[6] && 'K' != e[6])
      break;
    if (0 != e[7])
      break;
    return true;
  }
  return false;
}

bool ON_FileSystemPath::FilePathHas3dmExtension(
  const char* file_path,
  bool bAllow3dmbakExtension
)
{
  for (;;)
  {
    // test file name
    const char* e = nullptr;
    on_splitpath(file_path, nullptr, nullptr, nullptr, &e);
    if (nullptr == e)
      break;
    if ('.' != e[0])
      break;
    if ('3' != e[1])
      break;
    if ('d' != e[2] && 'D' != e[2])
      break;
    if ('m' != e[3] && 'M' != e[3])
      break;
    if (0 == e[4])
      return true;
    if (false == bAllow3dmbakExtension)
      break;
    if ('b' != e[4] && 'B' != e[4])
      break;
    if ('a' != e[5] && 'A' != e[5])
      break;
    if ('k' != e[6] && 'K' != e[6])
      break;
    if (0 != e[7])
      break;
    return true;
  }
  return false;
}

bool ON_FileSystemPath::IsValidFileName(
  const char* file_name,
  bool bAllPlatforms
)
{
  const ON_wString wide_file_name(file_name);
  return ON_FileSystemPath::IsValidFileName(static_cast<const wchar_t*>(wide_file_name), bAllPlatforms);
}

bool ON_FileSystemPath::IsValidFileName(
  const wchar_t* file_name,
  bool bAllPlatforms
)
{
  if (nullptr == file_name || 0 == file_name[0])
    return false;

  bool bDoubleDot = false;
  wchar_t prev_c = 0;
  int file_name_length;
  for (file_name_length = 0; 0 != file_name[file_name_length]; file_name_length++)
  {
    if (file_name_length > 256)
      return false;

    // note that all illegal symbols currently tested for have 
    // UNICODE code points <= U+07F, so we can simply test c
    const wchar_t c = file_name[file_name_length];
    if (ON_FileSystemPath::IsDirectorySeparator(c, bAllPlatforms))
      return false;

    switch (c)
    {
    case '.':
      bDoubleDot = ('.' == prev_c);
      break;

    case ':':
#if defined(ON_RUNTIME_WIN)
      return false;
#else
      if (bAllPlatforms)
        return false;
#endif
      break;

      //// Most windows apps have these restrictions, but the file system supports 
      //// names with these characters.
      ////    case ':':
      ////    case '~':
      ////    case '#':
      ////    case '%':
      ////    case '&':
      ////    case '*':
      ////    case '{':
      ////    case '}':
      ////    case '<':
      ////    case '>':
      ////    case '?':
      ////    case '|':
      ////    case '"':
      ////#if defined(ON_RUNTIME_WIN)
      ////      return false;
      ////#else
      ////      if (bAllPlatforms)
      ////        return false;
      ////#endif
      ////    
    }

    prev_c = c;
  }

  switch(prev_c)
  {
  case '.':
    if (1 == file_name_length)
      return false;
    if (2 == file_name_length && bDoubleDot)
      return false; 
    break;

  case '~':
    if (1 == file_name_length)
      return false;
    break;
  }

  return true;
}

const ON_wString ON_FileSystemPath::PlatformPath(ON_FileSystemPath::PathId path_id)
{
#if defined(ON_RUNTIME_WIN)
  KNOWNFOLDERID platform_path_id;
#define ON_INTERNAL_SET_LOCAL_DIRECTORY_ID(win_fid,apple_fid) platform_path_id = win_fid
#elif defined(ON_RUNTIME_COCOA_AVAILABLE)
  NSSearchPathDirectory platform_path_id;
#define ON_INTERNAL_SET_LOCAL_DIRECTORY_ID(win_fid,apple_fid) platform_path_id = apple_fid
#endif

#if defined(ON_INTERNAL_SET_LOCAL_DIRECTORY_ID)
  switch (path_id)
  {
  case ON_FileSystemPath::PathId::DesktopDirectory:
    ON_INTERNAL_SET_LOCAL_DIRECTORY_ID(FOLDERID_Desktop, NSDesktopDirectory);
    break;
  case ON_FileSystemPath::PathId::DocumentsDirectory:
    ON_INTERNAL_SET_LOCAL_DIRECTORY_ID(FOLDERID_Documents, NSDocumentDirectory);
    break;
  case ON_FileSystemPath::PathId::DownloadsDirectory:
    ON_INTERNAL_SET_LOCAL_DIRECTORY_ID(FOLDERID_Downloads, NSDownloadsDirectory);
    break;
  case ON_FileSystemPath::PathId::HomeDirectory:
//#if defined(ON_RUNTIME_WIN)
//    platform_path_id = FOLDERID_Profile;
//#elif defined(ON_RUNTIME_APPLE_OBJECTIVE_C_AVAILABLE)
//     platform_path_id = NSUserDirectory;
//#endif
    ON_INTERNAL_SET_LOCAL_DIRECTORY_ID(FOLDERID_Profile, NSUserDirectory);
    //ON_INTERNAL_SET_LOCAL_DIRECTORY_ID(FOLDERID_Profile, NSHomeDirectory);
    break;
  default:
    return ON_wString::EmptyString;
  }
#undef ON_INTERNAL_SET_LOCAL_DIRECTORY_ID
#endif

  ON_wString path;

#if defined(ON_RUNTIME_WIN)

  const DWORD dwFlags = KF_FLAG_DEFAULT;
  const HANDLE hToken = nullptr; // current user
  wchar_t* windows_path = nullptr;
  const HRESULT hr = ::SHGetKnownFolderPath(
    platform_path_id,
    dwFlags,
    hToken,
    &windows_path
  );
  if (nullptr != windows_path)
  {
    if (S_OK == hr)
      path = windows_path;
    CoTaskMemFree(windows_path);
  }

#elif defined(ON_RUNTIME_COCOA_AVAILABLE)

  NSArray *apple_paths = NSSearchPathForDirectoriesInDomains(platform_path_id, NSUserDomainMask, YES);
  if ([apple_paths count] > 0)
  {
    NSString* apple_path = [apple_paths objectAtIndex : 0];
    if (nullptr != apple_path)
    {
      ON_wString s;
      const int len = (int)apple_path.length;
      s.SetLength(len);
      int idx;
      for (idx = 0; idx < len; idx++)
        s[idx] = [apple_path characterAtIndex : idx];
      s[idx] = 0;
      path = s;
    }
  }

#else

  if (ON_FileSystemPath::PathId::HomeDirectory != path_id)
  {
    ON_ERROR("Function not implemented.");
  }

#endif

  path.TrimLeftAndRight();

  // See if environment variables will
  if (ON_FileSystemPath::PathId::HomeDirectory == path_id && path.IsEmpty())
  {
    const wchar_t dir_seps[4] = {
      ON_FileSystemPath::DirectorySeparator,
      ON_FileSystemPath::AlternateDirectorySeparator,
      ON_wString::Space,
      0
    };
    for (;;)
    {
      path = ON_wString(getenv("HOME"));
      path.TrimLeftAndRight();
      path.TrimRight(dir_seps);
      if ( ON_FileSystem::IsDirectory(path) )
        break;

#if defined(ON_RUNTIME_WIN)
      path = ON_wString(getenv("USERPROFILE"));
      path.TrimLeftAndRight();
      path.TrimRight(dir_seps);
      if ( ON_FileSystem::IsDirectory(path) )
        break;

      path = ON_wString(getenv("HOMEDRIVE")) + ON_wString(getenv("HOMEPATH"));
      path.TrimLeftAndRight();
      path.TrimRight(dir_seps);
      if ( ON_FileSystem::IsDirectory(path) )
        break;
#endif
      path = ON_wString::EmptyString;
      break;
    }
  }

  return path;
}

static unsigned int ON_Internal_SeekTo3DGeometryFileFormatMark(
  FILE* fp
)
{
  const char* tag = "3D Geometry File Format ";
  char buffer[33] = {};

  for (;;)
  {
    if (32 != ON_FileStream::Read(fp, 32, buffer))
      break;

    if (0 != ON_String::CompareOrdinal(tag, 24, buffer, 24, false))
    {
      // it's not a "pure" .3DM file 
      // - see if we have a .3DM file with MS OLE-goo at the start
      // (generally, there is around 6kb of goo.  I keep looking
      // for up to 32mb just in case.)
      unsigned int offset = 0;
      for (unsigned int n = 0; n < 33554432; n++)
      {
        for (int j = 0; j < 31; j++)
          buffer[j] = buffer[j + 1];
        if (!ON_FileStream::Read(fp, 1, &buffer[31]))
          break;
        if (0 == ON_String::CompareOrdinal(tag, 24, buffer, 24, false))
        {
          offset = n + 1;
          break;
        }
      }
      if (0 == offset)
        break;
    }

    // get version
    //char* sVersion = s3d+24;
    // skip leading spaces
    int ver = 0;
    int i = 24;
    while (i < 32 && buffer[i] == ' ')
      i++;
    while (i < 32)
    {
      // TEMPORARY 2 = X
      if (i == 31 && buffer[i] == 'X')
      {
        buffer[i] = '2';
      }

      if (buffer[i] < '0' || buffer[i] > '9')
      {
        // it's not a valid .3DM file version
        break;
      }
      ver = ver * 10 + ((int)(buffer[i] - '0'));
      i++;
    }
    if (ver <= 0)
      break;

    if (false == ON_FileStream::SeekFromCurrentPosition(fp, -32))
      break;

    return (unsigned int)ver;
  }
  ON_FileStream::SeekFromStart(fp, 0);
  return false;
}

FILE* ON_FileStream::Open3dmToRead(
  const wchar_t* file_path
)
{
  FILE* fp = nullptr;

  for (;;)
  {
    fp = ON_FileStream::Open(file_path,L"rb");
    if (nullptr == fp)
      break;

    if ( 0 == ON_Internal_SeekTo3DGeometryFileFormatMark(fp))
      break;

    return fp;
  }

  if ( nullptr != fp )
    ON::CloseFile(fp);

  return nullptr;
}

FILE* ON_FileStream::ON_FileStream::Open3dmToRead(
  const char* file_path
)
{
  FILE* fp = nullptr;

  for (;;)
  {
    fp = ON_FileStream::Open(file_path,"rb");
    if (nullptr == fp)
      break;

    if ( 0 == ON_Internal_SeekTo3DGeometryFileFormatMark(fp))
      break;

    return fp;
  }

  if ( nullptr != fp )
    ON::CloseFile(fp);

  return nullptr;
}


ON__INT64 ON_FileStream::CurrentPosition( FILE* fp )
{
  if ( 0 == fp )
    return -1;
#if defined(ON_COMPILER_MSC) && defined(ON_RUNTIME_WIN)
  return _ftelli64(fp);
#else
  return ftell(fp);
#endif
}

bool ON_FileStream::SeekFromCurrentPosition( FILE* fp, ON__INT64 offset )
{
  return ON_FileStream::Seek(fp,offset,SEEK_CUR);
}

bool ON_FileStream::SeekFromStart( FILE* fp, ON__INT64 offset )
{
  return ON_FileStream::Seek(fp,offset,SEEK_SET);
}

bool ON_FileStream::SeekFromEnd( FILE* fp, ON__INT64 offset )
{
  return ON_FileStream::Seek(fp,offset,SEEK_END);
}

bool ON_FileStream::Seek( FILE* fp, ON__INT64 offset, int origin )
{
  if ( 0 == fp )
    return false;

  if ( origin < 0 || origin > 2 )
    return false;

  if ( 0 == offset && SEEK_CUR == origin )
    return true;
  
#if defined(ON_COMPILER_MSC) && defined(ON_RUNTIME_WIN)
  if (0 != _fseeki64(fp, offset, origin))
    return false;
#else

  const int i = 2147483646;
  const ON__INT64 i64 = i;

  while ( offset > i64 )
  {
    if ( 0 != fseek( fp, i, origin ) )
      return false;
    if (SEEK_CUR != origin)
      origin = SEEK_CUR;
    offset -= i64;
  }

  while ( offset < -i64 )
  {
    if ( 0 != fseek( fp, -i, origin ) )
      return false;
    if (SEEK_CUR != origin)
      origin = SEEK_CUR;
    offset += i64;
  }

  if (0 != offset || SEEK_CUR != origin)
  {
    int ioffset = (int)offset;
    if (0 != fseek(fp, ioffset, origin))
      return false;
  }

#endif

  return true;
}

ON__UINT64 ON_FileStream::Read( FILE* fp, ON__UINT64 count, void* buffer )
{
  ON__UINT64 rc = 0;
  if ( 0 == fp || count <= 0 || 0 == buffer )
    return rc;

  if ( count <= ON_MAX_SIZE_T )
  {
    rc = (ON__UINT64)fread(buffer,1,(size_t)count,fp);
  }
  else
  {
    size_t sz, szread;
    while ( count > 0 )
    {
      sz = ( count > ON_MAX_SIZE_T ) ? ON_MAX_SIZE_T : ((size_t)count);
      szread = fread(buffer,1,sz,fp);
      rc += szread;
      if ( szread != sz )
        break;
      count -= sz;
      buffer = ((unsigned char*)buffer) + sz;
    }
  }

 return rc;
}

ON__UINT64 ON_FileStream::Write( FILE* fp, ON__UINT64 count, const void* buffer )
{
  ON__UINT64 rc = 0;
  if ( 0 == fp || count <= 0 || 0 == buffer )
    return rc;

  if ( count <= ON_MAX_SIZE_T )
  {
    rc = fwrite(buffer,1,(size_t)count,fp);
  }
  else
  {
    size_t sz, szwrite;
    while ( count > 0 )
    {
      sz = ( count > ON_MAX_SIZE_T ) ? ON_MAX_SIZE_T : ((size_t)count);
      szwrite = fwrite(buffer,1,sz,fp);
      rc += szwrite;
      if ( szwrite != sz )
        break;
      count -= sz;
      buffer = ((unsigned char*)buffer) + sz;
    }
  }

 return rc;
}

bool ON_FileStream::Flush( FILE* fp )
{
  if ( 0 == fp )
    return false;
  if ( 0 != fflush(fp) )
    return false;
  return true;
}

bool ON_FileStream::GetFileInformation(
  const wchar_t* file_name,
  ON__UINT64* file_size,
  ON__UINT64* file_metadata_last_modified_time,
  ON__UINT64* file_contents_last_modified_time
  )
{
  FILE* fp = ON::OpenFile(file_name, L"rb");
  bool rc = ON_FileStream::GetFileInformation(fp,file_size,file_metadata_last_modified_time,file_contents_last_modified_time);
  ON::CloseFile(fp);
  return rc;
}

bool ON_FileStream::GetFileInformation(
  const char* file_name,
  ON__UINT64* file_size,
  ON__UINT64* file_metadata_last_modified_time,
  ON__UINT64* file_contents_last_modified_time
  )
{
  FILE* fp = ON::OpenFile(file_name, "rb");
  bool rc = ON_FileStream::GetFileInformation(fp,file_size,file_metadata_last_modified_time,file_contents_last_modified_time);
  ON::CloseFile(fp);
  return rc;
}

bool ON_FileStream::GetFileInformation( 
    FILE* fp,
    ON__UINT64* file_size,
    ON__UINT64* file_metadata_last_modified_time,
    ON__UINT64* file_contents_last_modified_time
    )
{
  bool rc = false;

  if (file_size)
    *file_size = 0;
  if (file_metadata_last_modified_time)
    *file_metadata_last_modified_time = 0;
  if (file_contents_last_modified_time)
    *file_contents_last_modified_time = 0;

  if ( fp )
  {

#if defined(ON_COMPILER_MSC)

    // Microsoft compilers
#if (_MSC_VER >= 1400)
    // VC 8 (2005) 
    // works for file sizes > 4GB 
    // when size_t is a 64 bit integer
    struct _stat64 sb;
    memset(&sb,0,sizeof(sb));
    int fd = _fileno(fp);    
    int fstat_rc = _fstat64(fd, &sb);
#else
    // VC6 compiler
    struct _stat sb;
    memset(&sb,0,sizeof(sb));
    int fd = _fileno(fp);    
    int fstat_rc = _fstat(fd, &sb);
#endif

#else
    // works on most compilers
    int fd = fileno(fp);
    struct stat sb;
    memset(&sb,0,sizeof(sb));
    int fstat_rc = fstat(fd, &sb);
#endif


    if (0 == fstat_rc)
    {
      if (file_size)
        *file_size = (ON__UINT64)sb.st_size;
      if (file_metadata_last_modified_time)
        *file_metadata_last_modified_time = (ON__UINT64)sb.st_ctime;
      if (file_contents_last_modified_time)
        *file_contents_last_modified_time = (ON__UINT64)sb.st_mtime;
      rc = true;
    }
  }

  return rc;
}

//////////////////////////////////////////////////////////////////////////////
//
// ON_FileIterator implementation
//

class ON_DirectoryIteratorImpl
{
private:
  friend class ON_FileIterator;

  ON_DirectoryIteratorImpl();
  ~ON_DirectoryIteratorImpl();
  ON_DirectoryIteratorImpl(const ON_DirectoryIteratorImpl&) = delete;
  ON_DirectoryIteratorImpl& operator=(const ON_DirectoryIteratorImpl&) = delete;

  const wchar_t* CurrentFileNameAsPointer() const;

#if defined(ON_COMPILER_MSC)
  // Used by Windows ::Find
  //ON__UINT32 m_file_attributes_mask = 0;
  HANDLE m_h = 0;
  WIN32_FIND_DATA m_fd;
#else
  // Apple and gcc
  ON_wString m_ws_file_name_filter;
  ON_String m_utf8_file_name_filter;
  DIR* m_dir = nullptr;
  struct dirent m_dirent;
  char m_dirent_name_buffer[NAME_MAX+1]; // < this field provide storage for m_dirent.d_name[]

  // information about the current file
  wchar_t m_current_name[1024];
  ON__UINT64 m_current_file_attributes = 0; // 1 = regular file, 2 = directory
  ON__UINT64 m_current_file_size = 0;
  ON__UINT64 m_current_content_last_modified_time = 0;
#endif
};

ON_DirectoryIteratorImpl::ON_DirectoryIteratorImpl()
{
#if defined(ON_COMPILER_MSC)
  memset(&m_fd,0,sizeof(m_fd));
#else
  memset(&m_dirent,0,sizeof(m_dirent));
  memset(&m_dirent_name_buffer[0],0,sizeof(m_dirent_name_buffer));
  memset(&m_current_name[0],0,sizeof(m_current_name));
#endif
}

ON_DirectoryIteratorImpl::~ON_DirectoryIteratorImpl()
{
#if defined(ON_COMPILER_MSC)
  if ( 0 != m_h )
    ::FindClose(m_h);
#else
  if ( 0 != m_dir )
    closedir(m_dir);
#endif
}

void ON_FileIterator::Reset()
{
  m_state = 0;
  m_directory = ON_wString::EmptyString;
  m_item_name_filter = ON_wString::EmptyString;
  m_item_name = ON_wString::EmptyString;
  m_full_path_name = ON_wString::EmptyString;
  m_count = 0;
  if (nullptr != m_impl)
  {
    delete m_impl;
    m_impl = nullptr;
  }
}


ON__UINT64 ON_FileIterator::CurrentItemCount() const
{
  return m_count;
}

#if defined(ON_COMPILER_MSC)
static bool IsDotOrDotDotDir( const wchar_t* s )
#else
static bool IsDotOrDotDotDir( const char* s )
#endif
{
  bool rc = false;
  for (;;)
  {
    if ( 0 == s )
      break;
    if ( '.' != s[0] )
      break;
    if ( 0 != s[1] )
    {
      if ( '.' != s[1] )
        break;
      if ( 0 != s[2] )
        break;
    }
    rc = true; // s = "." or s = ".."
    break;
  }
  return rc;
}

bool ON_FileIterator::Initialize( 
  const wchar_t* directory_name
  )
{
  const wchar_t* item_name_filter = nullptr;
  return Initialize(directory_name,item_name_filter);
}

bool ON_FileIterator::Initialize( 
  const wchar_t* directory_name, 
  const wchar_t* item_name_filter
  )
{
  const ON_wString local_item_name_filter(item_name_filter);
  item_name_filter = local_item_name_filter;

  ON_wString local_directory_name(directory_name);
  {
    const wchar_t* dir_seps = L"/\\";
    local_directory_name.TrimRight(dir_seps);
    if ( local_directory_name.Length() <= 0 || local_directory_name.IsEmpty() )
      local_directory_name = directory_name;
  }

  Reset();
  m_directory = local_directory_name;
  m_item_name_filter = local_item_name_filter;
  if (m_directory.IsEmpty())
    return false;
  m_state = 1;
  return true;
}

bool ON_FileIterator::Initialize( 
  const char* directory_name
  )
{
  const char* item_name_filter = nullptr;
  return Initialize(directory_name,item_name_filter);
}

bool ON_FileIterator::Initialize(
  const char* directory_name,
  const char* item_name_filter
  )
{
  const ON_wString local_directory_name(directory_name);
  const ON_wString local_item_name_filter(item_name_filter);
  return Initialize(
    static_cast<const wchar_t*>(local_directory_name),
    static_cast<const wchar_t*>(local_item_name_filter)
    );  
}

bool ON_FileIterator::FirstItem()
{
  const ON_wString saved_directory(m_directory);
  const ON_wString saved_item_name_filter(m_item_name_filter);
  if (m_state > 1)
  {
    Reset();
    m_directory = saved_directory;
    m_item_name_filter = saved_item_name_filter;
    if (saved_directory.IsEmpty())
      return false;
    m_state = 1;
  }

  if ( 1 != m_state  || nullptr != m_impl )
    return false;

  m_impl = new ON_DirectoryIteratorImpl();
  m_state = 2;

  const wchar_t* item_name_filter = static_cast<const wchar_t*>(m_item_name_filter);
  if ( nullptr != item_name_filter && 0 == item_name_filter[0] )
    item_name_filter = nullptr;

#if defined(ON_COMPILER_MSC)
  for (;;)
  {
    ON_wString s(m_directory);

    if (0 == item_name_filter)
    {
      // A null file file_name_filter means iterate 
      // through all items in the directory.  To do
      // this using Windows' ::FindFirstFile, set the
      // filter to "*.*", even though some items will
      // not contain a "dot".
      item_name_filter = L"*.*";
    }

    if (0 != item_name_filter[0] && s.IsNotEmpty())
    {
      s += ON_FileSystemPath::DirectorySeparator;
      s += item_name_filter;
    }

    m_impl->m_h = ::FindFirstFile(static_cast<const wchar_t*>(s), &m_impl->m_fd);
    if (0 == m_impl->m_h || INVALID_HANDLE_VALUE == m_impl->m_h || 0 == m_impl->m_fd.cFileName[0])
    {
      // Happens on "fake" directories like "My Music" and "My Videos"
      m_impl->m_h = 0;
      break;
    }

    if (IsDotOrDotDotDir(m_impl->m_fd.cFileName))
    {
      return NextItem();
    }

    m_count++;
    m_impl->m_fd.cFileName[(sizeof(m_impl->m_fd.cFileName) / sizeof(m_impl->m_fd.cFileName[0])) - 1] = 0;
    m_item_name = m_impl->m_fd.cFileName;
    m_full_path_name = ON_wString::EmptyString;
    return true;
  }

#else
  // gcc code
  m_impl->m_utf8_file_name_filter = item_name_filter;
  const ON_String utf8_str(m_directory); // convert wchar_t to utf8 string
  const char* s = utf8_str;
  m_impl->m_dir = (0 != s && 0 != s[0]) ? opendir(s) : 0;
  if ( 0 != m_impl->m_dir )
  {
    return NextItem();
  }
#endif

  Reset();
  m_directory = saved_directory;
  m_item_name_filter = saved_item_name_filter;
  m_state = 3;
  return false;
}

bool ON_FileIterator::NextItem()
{
  m_item_name = ON_wString::EmptyString;
  m_full_path_name = ON_wString::EmptyString;
  if ( 1 == m_state )
    return FirstItem();
  if ( 2 != m_state )
    return false;

#if defined(ON_COMPILER_MSC)
  for (;;)
  {
    if (0 == m_impl->m_h || INVALID_HANDLE_VALUE == m_impl->m_h || 0 == m_impl->m_fd.cFileName[0])
    {
      break;
    }

    for (;;)
    {
      if (!::FindNextFile(m_impl->m_h, &m_impl->m_fd) || 0 == m_impl->m_fd.cFileName[0])
        break;

      if (IsDotOrDotDotDir(m_impl->m_fd.cFileName))
        continue;

      m_count++;
      m_impl->m_fd.cFileName[(sizeof(m_impl->m_fd.cFileName) / sizeof(m_impl->m_fd.cFileName[0])) - 1] = 0;
      m_item_name = m_impl->m_fd.cFileName;
      m_full_path_name = ON_wString::EmptyString;
      return true;
    }

    break;
  }
#else

  // gcc code
  ON__UINT64 current_file_attributes = 0;
  wchar_t current_name[ sizeof(m_impl->m_current_name)/sizeof(m_impl->m_current_name[0]) ];
  for(;;)
  {
    current_file_attributes = 0;
    struct dirent* dp = 0;
    int readdir_errno = readdir_r(m_impl->m_dir, &m_impl->m_dirent, &dp);
    if ( 0 !=  readdir_errno )
      break;
    if ( 0 == dp )
      break;
    if ( 0 == m_impl->m_dirent.d_name[0] )
      break;

    if ( IsDotOrDotDotDir(m_impl->m_dirent.d_name) )
      continue;

    memset( current_name, 0, sizeof(current_name) );
    ON_ConvertUTF8ToWideChar(
      false, // no BOM in input file name as utf8 string
      &m_impl->m_dirent.d_name[0],
      -1, // null terminated utf8 string
      &current_name[0], ((int)(sizeof(current_name)/sizeof(current_name[0]))) - 1, // output wchar_t string
      0, // null output error status
      (4|8|16), // mask common conversion errors
      0, // error_code_point = null terminator inserted at point of conversion error
      0  // null ouput end-of-string pointer
      );
    // TODO
    //   Test m_dirent.d_name to make sure it passes m_ws/utf8_file_name_filter

    ON_wString wpath = m_directory;
    wpath += '/';
    wpath += current_name;

    // get a utf8 version of the full path to pass to stat
    const ON_String utf8buffer(wpath);
    const char* utf8path = utf8buffer;
    if ( 0 == utf8path )
      continue;

    struct stat buf;
    memset(&buf,0,sizeof(buf));
    int stat_errno = stat( utf8path, &buf);
    if ( 0 != stat_errno )
      continue;

    if ( S_ISDIR(buf.st_mode) )
    {
      current_file_attributes = 2;
    }
    else if ( S_ISREG(buf.st_mode) )
    {
      // Only *.ext filters work at this time for non-windows
      const wchar_t* file_name_filter = m_impl->m_ws_file_name_filter;
      if (   0 != file_name_filter
            && '*' == file_name_filter[0] 
            && '.' == file_name_filter[1]
            && 0 != file_name_filter[2]
            && '*' != file_name_filter[2] )
      {
        // assume this is a *.extension filter
        const wchar_t* current_name_ext = 0;
        on_wsplitpath(current_name,0,0,0,&current_name_ext);
        if (   0 == current_name_ext 
            || 0 != wcscmp(file_name_filter+1,current_name_ext) 
           )
        {
          // current_name does pass match file_name_filter
          continue;
        }
      }
      current_file_attributes = 1;
    }
    else
      continue;

    // save current item information
    memcpy( m_impl->m_current_name, current_name, sizeof(m_impl->m_current_name) );
    m_impl->m_current_file_attributes = current_file_attributes;
    m_impl->m_current_file_size = buf.st_size;
    m_impl->m_current_content_last_modified_time = buf.st_mtime;

    m_item_name = m_impl->m_current_name;
    m_full_path_name = ON_wString::EmptyString;
    return true;
  }

#endif
  const ON__UINT64 saved_count = m_count;
  Reset();
  m_count = saved_count;
  m_state = 3;
  return false;
}

const wchar_t* ON_DirectoryIteratorImpl::CurrentFileNameAsPointer() const
{
#if defined(ON_COMPILER_MSC)
  return ( 0 != m_h && 0 != m_fd.cFileName[0] ) ? m_fd.cFileName : nullptr;
#else
  return ( 0 != m_current_name[0] ) ? m_current_name : nullptr;
#endif
}

const ON_wString ON_FileIterator::CurrentItemName() const
{
  return m_item_name;
}

ON__UINT64 ON_FileIterator::CurrentItemSize() const
{
  ON__UINT64 file_size = 0;

  if (nullptr != m_impl)
  {

#if defined(ON_COMPILER_MSC)
    if (0 != m_impl->CurrentFileNameAsPointer())
    {
      file_size = m_impl->m_fd.nFileSizeHigh;
      file_size *= ((ON__UINT64)0xFFFFFFFF);
      file_size += m_impl->m_fd.nFileSizeLow;
    }
#else
    file_size = m_impl->m_current_file_size;
#endif
  }

  return file_size;
}

bool ON_FileIterator::CurrentItemIsDirectory() const
{
  bool rc = false;
  if (nullptr != m_impl)
  {
    const wchar_t* current_file_name = m_impl->CurrentFileNameAsPointer();
    if (0 != current_file_name && 0 != current_file_name[0])
    {
#if defined(ON_COMPILER_MSC)
      if (0 != (FILE_ATTRIBUTE_DIRECTORY & m_impl->m_fd.dwFileAttributes))
      {
        rc = true;
      }
#else
      if ( 2 == m_impl->m_current_file_attributes)
      {
        rc = true;
      }
#endif
    }
  }
  return rc;
}

bool ON_FileIterator::CurrentItemIsFile() const
{
  bool rc = false;
  if (nullptr != m_impl)
  {
    const wchar_t* current_file_name = m_impl->CurrentFileNameAsPointer();
    if (0 != current_file_name && 0 != current_file_name[0])
    {
#if defined(ON_COMPILER_MSC)
      if (0 == (FILE_ATTRIBUTE_DIRECTORY & m_impl->m_fd.dwFileAttributes))
      {
        rc = true;
      }
#else
      if ( 1 == m_impl->m_current_file_attributes)
      {
        rc = true;
      }
#endif
    }
  }
  return rc;
}
bool ON_FileIterator::CurrentItemIsHidden() const
{
  bool rc = false;
  if (nullptr != m_impl)
  {
    const wchar_t* current_file_name = m_impl->CurrentFileNameAsPointer();
    if (0 != current_file_name && 0 != current_file_name[0])
    {
      if ('.' == current_file_name[0])
      {
        rc = true;
      }
#if defined(ON_COMPILER_MSC)
      else if (0 != (FILE_ATTRIBUTE_HIDDEN & m_impl->m_fd.dwFileAttributes))
      {
        rc = true;
      }
#endif
    }
  }
  return rc;
}


const ON_wString ON_FileIterator::CurrentItemFullPathName() const
{
  if (m_full_path_name.IsEmpty() && m_item_name.IsNotEmpty())
  {
    if (m_directory.IsNotEmpty())
    {
      m_full_path_name = m_directory;
      m_full_path_name += ON_FileSystemPath::DirectorySeparator;
      m_full_path_name += m_item_name;
    }
  }
  return m_full_path_name;
}

ON__UINT64 ON_SecondsSinceJanOne1970UTC()
{
#if defined(ON_COMPILER_MSC)

  __time64_t t = _time64(nullptr);
  return (ON__UINT64)t;  

#elif defined(ON_COMPILER_CLANG) || defined(ON_COMPILER_GNU)

  //__time64_t t = _time64(nullptr);
  time_t t = time(nullptr);
  return (ON__UINT64)t;

#else

  __time64_t t = _time64(nullptr);
  return (ON__UINT64)t;  

#endif
}

const ON_wString SecondsSinceJanOne1970UTCToString(
  ON__UINT64 seconds_since_epoch
  )
{
  int year = 0;
  int month = 0;
  int mday = 0;
  int hour = 0;
  int min = 0;
  int sec = 0;

#if defined(ON_COMPILER_MSC)

  const time_t t = (time_t)seconds_since_epoch;
  const struct tm* ptr = _gmtime64( &t );
  if (nullptr != ptr)
  {
    const struct tm uct = *ptr;
    year = uct.tm_year;
    month = uct.tm_mon;
    mday = uct.tm_mday;
    hour = uct.tm_hour;
    min = uct.tm_min;
    sec = uct.tm_sec;
  }

#elif defined(ON_COMPILER_CLANG) || defined(ON_COMPILER_GNU)

  const time_t t = (time_t)seconds_since_epoch;
  const struct tm* ptr = gmtime( &t );
  if (nullptr != ptr)
  {
    const struct tm uct = *ptr;
    year = uct.tm_year;
    month = uct.tm_mon;
    mday = uct.tm_mday;
    hour = uct.tm_hour;
    min = uct.tm_min;
    sec = uct.tm_sec;
  }

#else

  const time_t t = (time_t)seconds_since_epoch;
  const struct tm* ptr = _gmtime64( &t );
  if (nullptr != ptr)
  {
    const struct tm uct = *ptr;
    year = uct.tm_year;
    month = uct.tm_mon;
    mday = uct.tm_mday;
    hour = uct.tm_hour;
    min = uct.tm_min;
    sec = uct.tm_sec;
  }

#endif

  if (
    year >= 1970
    && month >= 1 && month <= 12
    && mday >= 1 && mday <= 31
    && hour >= 0 && hour <= 24
    && min >= 0 && min <= 60
    && sec >= 0 && sec <= 60
    )
  {
    ON_wString sUTC;
    // yyyy-mm-dd hh:mm:ss
    sUTC.Format(L"%04d-%02d-%02d %02d:%02d:%02d UTC",year,month,mday,hour,min,sec);
    return sUTC;
  }

  return ON_wString::EmptyString;
}

#if defined(ON_COMPILER_MSC)
static ON__UINT64 SecondsSinceJanOne1970( FILETIME ft )
{
  // The FILETIME is in 100-nanosecond intervals since January 1, 1601 UCT.
  //
  // Between midnight January 1, 1601 and midnight January 1, 1970 there 
  // were 134774 days = 11644473600 seconds. Each second has 10^7 intervals
  // that are one hundred nanoseconds long.  So, if N = number of one hundred
  // nanosecond intervals since midnight January 1, 1601, then
  // (N / 10000000) - 11644473600 = number of seconds since midnight
  // January 1, 1970.
  //
  // January 1, 1601 was the start of a Gregorian calendary 400 year cycle
  // and "the internet" sometimes cites that as the reason that date is 
  // the "beginning of time" for Windows' FILETIME values.  This convention
  // would slightly simplify the formulae used to account for leap years, 
  // so it is plausable this might might even be true.

  ON__UINT64 ft_since_jan_1_1601 = ft.dwHighDateTime;
  ft_since_jan_1_1601 *= 0xFFFFFFFF;
  ft_since_jan_1_1601 += ft.dwLowDateTime;

  ON__UINT64 hundrednanoseconds_per_second = 10000000;

  ON__UINT64 seconds_since_jan_1_1601 = ft_since_jan_1_1601 / hundrednanoseconds_per_second;
                                                   
  ON__UINT64 seconds_since_jan_1_1970 = seconds_since_jan_1_1601 - 11644473600;

  return seconds_since_jan_1_1970;
}
#endif

ON__UINT64 ON_FileIterator::CurrentItemLastModifiedTime() const
{
  if ( nullptr == m_impl)
    return 0;
#if defined(ON_COMPILER_MSC)
  return SecondsSinceJanOne1970(m_impl->m_fd.ftLastWriteTime);
#else
  return m_impl->m_current_content_last_modified_time;
#endif
}

ON_FileIterator::~ON_FileIterator()
{
  Reset();
}


ON_ContentHash ON_ContentHash::Create(
  ON_SHA1_Hash sha1_name_hash,
  ON__UINT64 byte_count,
  ON_SHA1_Hash sha1_content_hash,
  ON__UINT64 hash_time,
  ON__UINT64 content_last_modified_time
  )
{
  ON_ContentHash hash;
  
  if ( 0 == hash_time )
    hash_time = ON_SecondsSinceJanOne1970UTC();
  hash.m_byte_count = (byte_count > 0) ? byte_count : 0;
  hash.m_hash_time = hash_time;
  
  hash.m_content_time 
    = (content_last_modified_time <= hash_time) 
    ? content_last_modified_time
    : 0;
  
  hash.m_sha1_name_hash = sha1_name_hash;

  hash.m_sha1_content_hash 
    = (hash.m_byte_count > 0)
    ? sha1_content_hash
    : ON_SHA1_Hash::EmptyContentHash
    ;

  return hash;
}

ON_ContentHash ON_ContentHash::CreateFromBuffer( 
  ON_SHA1_Hash sha1_name_hash,
  const void* buffer,
  size_t byte_count
  )
{
  ON__UINT64 hash_time = ON_SecondsSinceJanOne1970UTC();
  ON__UINT64 hash_byte_count = (nullptr != buffer && byte_count >0) ? ((ON__UINT64)byte_count) : 0;
  ON__UINT64 content_last_modifed_time = 0;
  ON_SHA1_Hash sha1_content_hash = ON_SHA1_Hash::BufferContentHash(buffer,(size_t)hash_byte_count);
  return ON_ContentHash::Create(sha1_name_hash,hash_byte_count,sha1_content_hash,hash_time,content_last_modifed_time);
}

ON_ContentHash ON_ContentHash::CreateFromFile( 
  ON_SHA1_Hash sha1_file_name_hash,
  FILE* fp
  )
{
  ON__UINT64 hash_time = ON_SecondsSinceJanOne1970UTC();
  ON__UINT64 file_byte_count = 0;
  ON__UINT64 file_metadata_last_modified_time = 0;
  ON__UINT64 file_contents_last_modified_time = 0;
  if ( false == ON_FileStream::GetFileInformation(fp,&file_byte_count,&file_metadata_last_modified_time,&file_contents_last_modified_time) )
    return ON_ContentHash::Create(sha1_file_name_hash,0,ON_SHA1_Hash::EmptyContentHash,hash_time,0);

  ON__UINT64 hash_byte_count = 0;
  ON_SHA1_Hash sha1_hash = ON_SHA1_Hash::FileContentHash(fp,hash_byte_count);
  return ON_ContentHash::Create(sha1_file_name_hash,hash_byte_count,sha1_hash,hash_time,file_contents_last_modified_time);
}

#include <unordered_map>

using ContentHashMap = std::unordered_map<std::wstring, ON_ContentHash>;

std::weak_ptr<ContentHashMap> g_pContentHashCache;

class ON_ContentHash::Cache::Private
{
public:
  std::shared_ptr<ContentHashMap> p;
};

ON_ContentHash::Cache::Cache()
  : m_private(new Private)
{
  
  m_private->p = g_pContentHashCache.lock();


  if (!m_private->p)
  {
    m_private->p.reset(new ContentHashMap);
    g_pContentHashCache = m_private->p;
  }
}

ON_ContentHash::Cache::~Cache()
{
  delete m_private;
}

void ON_ContentHash::Cache::Add(const wchar_t* path, const ON_ContentHash& hash)
{
  auto map = g_pContentHashCache.lock();
  if (map)
  {
    map->insert(std::make_pair(path, hash));
  }
}


const ON_ContentHash* ON_ContentHash::Cache::FromFile(const wchar_t* path)
{
  auto map = g_pContentHashCache.lock();
  if (map)
  {
    auto it = map->find(path);
    if (it != map->end())
    {
      return &it->second;
    }
  }
  return nullptr;
}

const ON_ContentHash* ON_ContentHash::Cache::FromFile(const char* p)
{
  ON_wString s(p);
  return FromFile((const wchar_t*)s);
}

void ON_ContentHash::Cache::Add(const char* p, const ON_ContentHash& h)
{
  ON_wString s(p);
  Add(s, h);
}

ON_ContentHash ON_ContentHash::CreateFromFile( 
  const wchar_t* filename
  )
{
  if (auto pHash = Cache::FromFile(filename))
  {
    return *pHash;
  }

  ON_SHA1_Hash sha1_file_name_hash = (nullptr == filename) ? ON_SHA1_Hash::ZeroDigest : ON_SHA1_Hash::FileSystemPathHash(filename);
  FILE* fp = ON_FileStream::Open(filename, L"rb");
  ON_ContentHash hash = ON_ContentHash::CreateFromFile(sha1_file_name_hash,fp);
  ON_FileStream::Close(fp);

  Cache::Add(filename, hash);

  return hash;
}

ON_ContentHash ON_ContentHash::CreateFromFile( 
  const char* filename
  )
{
  if (auto pHash = Cache::FromFile(filename))
  {
    return *pHash;
  }

  ON_SHA1_Hash sha1_file_name_hash = (nullptr == filename) ? ON_SHA1_Hash::ZeroDigest : ON_SHA1_Hash::FileSystemPathHash(filename);
  FILE* fp = ON_FileStream::Open(filename, "rb");
  ON_ContentHash hash = ON_ContentHash::CreateFromFile(sha1_file_name_hash,fp);
  ON_FileStream::Close(fp);

  Cache::Add(filename, hash);

  return hash;
}


bool ON_ContentHash::EqualContent(
  const ON_ContentHash& a,
  const ON_ContentHash& b
  )
{
  // Do not compare times
  return (a.m_byte_count == b.m_byte_count && a.m_sha1_content_hash == b.m_sha1_content_hash);
}


bool ON_ContentHash::DifferentContent(
  const ON_ContentHash& a,
  const ON_ContentHash& b
  )
{
  // Do not compare times
  return (a.m_byte_count != b.m_byte_count || a.m_sha1_content_hash != b.m_sha1_content_hash);
}

int ON_ContentHash::CompareContent(
  const ON_ContentHash& a,
  const ON_ContentHash& b
  )
{
  if (a.m_byte_count < b.m_byte_count)
    return -1;
  if (a.m_byte_count > b.m_byte_count)
    return 1;
  if (a.m_byte_count < b.m_byte_count)
    return -1;
  if (a.m_byte_count > b.m_byte_count)
    return 1;
  return ON_SHA1_Hash::Compare(a.m_sha1_content_hash, b.m_sha1_content_hash);
}

int ON_ContentHash::Compare(
  const ON_ContentHash& a,
  const ON_ContentHash& b
  )
{
  const int rc = ON_ContentHash::CompareContent(a, b);
  if (0 != rc)
    return rc;

  if (a.m_hash_time < b.m_hash_time)
    return -1;
  if (a.m_hash_time > b.m_hash_time)
    return 1;

  if (a.m_content_time < b.m_content_time)
    return -1;
  if (a.m_content_time > b.m_content_time)
    return 1;

  return ON_SHA1_Hash::Compare(a.m_sha1_name_hash, b.m_sha1_name_hash);
}

bool ON_ContentHash::EqualFileNameSizeAndTime(
  const wchar_t* filename
  ) const
{
  if (IsNotSet())
    return false;
  if ( m_byte_count <= 0 || m_hash_time <= 0 || m_content_time < m_hash_time )
    return false; // content time is not reliable.
  if (nullptr == filename || 0 == filename[0])
    return false;
  const ON_SHA1_Hash sha1_name_hash = ON_SHA1_Hash::StringHash(filename);
  if ( sha1_name_hash != m_sha1_name_hash )
    return false;
  ON__UINT64 file_byte_count = 0;
  ON__UINT64 file_metadata_last_modified_time = 0;
  ON__UINT64 file_contents_last_modified_time = 0;
  if ( false == ON_FileStream::GetFileInformation(filename,&file_byte_count,&file_metadata_last_modified_time,&file_contents_last_modified_time) )
    return false;
  if ( file_contents_last_modified_time <= 0 )
    return false; // content time is not reliable
  return (file_byte_count == m_byte_count && file_contents_last_modified_time == m_content_time);
}

bool ON_ContentHash::IsSet() const
{
  if ( 0 == m_hash_time )
    return false;
  return 
    (0 == m_byte_count)
    ? (ON_SHA1_Hash::EmptyContentHash == m_sha1_content_hash)
    : (ON_SHA1_Hash::EmptyContentHash != m_sha1_content_hash);
}


bool ON_ContentHash::IsNotSet() const
{
  return (false == IsSet());
}

ON__UINT64 ON_ContentHash::ByteCount() const
{
  return m_byte_count;
}


ON__UINT64 ON_ContentHash::HashCalculationTime() const
{
  return m_hash_time;
}


ON__UINT64 ON_ContentHash::ContentLastModifiedTime() const
{
  return m_content_time;
}


ON_SHA1_Hash ON_ContentHash::ContentHash() const
{
  return m_sha1_content_hash;
}


ON_SHA1_Hash ON_ContentHash::NameHash() const
{
  return m_sha1_name_hash;
}
  

bool ON_ContentHash::IsSameBufferContent(
  const void* buffer,
  size_t byte_count
  ) const
{
  return ON_ContentHash::EqualContent(*this, ON_ContentHash::CreateFromBuffer(ON_SHA1_Hash::ZeroDigest,buffer,byte_count));
}


bool ON_ContentHash::IsSameFileContent( 
  FILE* fp
  ) const
{
  return ON_ContentHash::EqualContent(*this, ON_ContentHash::CreateFromFile(ON_SHA1_Hash::ZeroDigest,fp));
}

bool ON_ContentHash::IsSameFileContent( 
  const wchar_t* filename
  ) const
{
  return ON_ContentHash::EqualContent(*this, ON_ContentHash::CreateFromFile(filename));
}

bool ON_ContentHash::IsSameFileContent( 
  const char* filename
  ) const
{
  return ON_ContentHash::EqualContent(*this, ON_ContentHash::CreateFromFile(filename));
}

ON_ContentHash::CompareResult ON_ContentHash::CompareResultFromUnsigned(
  unsigned int compare_result_as_unsigned
  )
{
  switch (compare_result_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ContentHash::CompareResult::Unset);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ContentHash::CompareResult::EqualContent);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ContentHash::CompareResult::DifferentContent);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ContentHash::CompareResult::DifferentContentFileIsOlder);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ContentHash::CompareResult::ContentDifferentFileIsNewer);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ContentHash::CompareResult::FileDoesNotExist);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ContentHash::CompareResult::FileSystemFailure);
  }

  ON_ERROR("Invalid compare_result_as_unsigned parameter.");
  return ON_ContentHash::CompareResult::Unset;
}

ON_ContentHash::CompareResult ON_ContentHash::Compare(
  const wchar_t* file_name,
  bool bFastTest
  ) const
{
  if ( false ==  ON_FileSystem::IsFile(file_name) )
    return ON_ContentHash::CompareResult::FileDoesNotExist;

  if (IsNotSet())
    return ON_ContentHash::CompareResult::DifferentContent;

  ON_ContentHash file_content_hash = ON_ContentHash::Unset;
  ON__UINT64 file_metadata_last_modified_time = 0;
  if ( false == ON_FileStream::GetFileInformation(file_name,&file_content_hash.m_byte_count,&file_metadata_last_modified_time,&file_content_hash.m_content_time) )
    return ON_ContentHash::CompareResult::FileSystemFailure;
  if (0 == file_content_hash.m_byte_count && 0 == file_metadata_last_modified_time && 0 == file_content_hash.m_content_time)
  {
    return ON_ContentHash::CompareResult::FileSystemFailure;
  }

  const ON__UINT64 current_time = ON_SecondsSinceJanOne1970UTC();
  bool bValidContentHashTime = (m_content_time > 0 && m_hash_time >= m_content_time && current_time >= m_hash_time);
  bool bValidFileTime = (file_content_hash.m_content_time > 0 && current_time >= file_content_hash.m_content_time);
  if (file_content_hash.m_byte_count != m_byte_count)
  {
    if (bValidContentHashTime &&  bValidFileTime)
    {
      // assume time values are accurate.
      if ( file_content_hash.m_content_time < m_content_time )
        return ON_ContentHash::CompareResult::DifferentContentFileIsOlder;
      if ( file_content_hash.m_content_time > m_content_time )
        return ON_ContentHash::CompareResult::ContentDifferentFileIsNewer;
    }
    return ON_ContentHash::CompareResult::DifferentContent;
  }

  file_content_hash.m_sha1_name_hash = ON_SHA1_Hash::StringHash(file_name);
  file_content_hash.m_sha1_content_hash = m_sha1_content_hash;

  if (bValidContentHashTime && bValidFileTime
    && m_content_time == file_content_hash.m_content_time
    && m_byte_count == file_content_hash.m_byte_count
    && m_sha1_name_hash == file_content_hash.m_sha1_name_hash
    )
  {
    if (bFastTest)
      return ON_ContentHash::CompareResult::EqualContent;
  }

  // Have to calculate SHA1 content hash
  file_content_hash = ON_ContentHash::CreateFromFile(file_name);
  return ON_ContentHash::Compare(file_content_hash);
}

ON_ContentHash::CompareResult ON_ContentHash::Compare(
  ON_ContentHash file_content_hash
  ) const
{
  if (file_content_hash.IsNotSet())
  {
    return ( m_sha1_name_hash == ON_SHA1_Hash::EmptyContentHash)
      ? ON_ContentHash::CompareResult::FileDoesNotExist
      : ON_ContentHash::CompareResult::FileSystemFailure;
  }
  if ( IsNotSet() )
    return ON_ContentHash::CompareResult::DifferentContent;
  if ( m_byte_count == file_content_hash.m_byte_count && m_sha1_content_hash == file_content_hash.m_sha1_content_hash )
    return ON_ContentHash::CompareResult::EqualContent;
  const ON__UINT64 current_time = ON_SecondsSinceJanOne1970UTC();
  bool bValidTimes 
    =  m_content_time > 0 
    && m_hash_time >= m_content_time 
    && current_time >= m_hash_time
    && file_content_hash.m_content_time > 0 
    && file_content_hash.m_hash_time >= file_content_hash.m_content_time 
    && current_time >= file_content_hash.m_hash_time
    ;
  if (bValidTimes)
  {
    if ( file_content_hash.m_content_time < m_content_time )
      return ON_ContentHash::CompareResult::DifferentContentFileIsOlder;
    if ( file_content_hash.m_content_time > m_content_time )
      return ON_ContentHash::CompareResult::ContentDifferentFileIsNewer;
  }
  return ON_ContentHash::CompareResult::DifferentContent;
}

bool ON_ContentHash::Read(
  class ON_BinaryArchive& archive
  )
{
  *this = ON_ContentHash::Unset;
  bool rc = false;
  int major_version = 0;
  int minor_version = 0;
  if (!archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version))
    return rc;
  for (;;)
  {
    if ( 1 != major_version )
      break;
    if (!archive.ReadBigInt(&m_byte_count))
      break;
    if (!archive.ReadBigInt(&m_hash_time))
      break;
    if (!archive.ReadBigInt(&m_content_time))
      break;
    if (!m_sha1_name_hash.Read(archive))
      break;
    if (!m_sha1_content_hash.Read(archive))
      break;
    rc = true;
    break;
  }
  if (!archive.EndRead3dmChunk())
    rc = false;
  return rc;
}


bool ON_ContentHash::Write(
  class ON_BinaryArchive& archive
  ) const
{
  if (!archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0))
    return false;
  bool rc = false;
  for (;;)
  {
    if (!archive.WriteBigInt(m_byte_count))
      break;
    if (!archive.WriteBigInt(m_hash_time))
      break;
    if (!archive.WriteBigInt(m_content_time))
      break;
    if (!m_sha1_name_hash.Write(archive))
      break;
    if (!m_sha1_content_hash.Write(archive))
      break;
    rc = true;
    break;
  }
  if (!archive.EndWrite3dmChunk())
    rc = false;
  return rc;
}

void ON_ContentHash::Dump(
  class ON_TextLog& text_log
  ) const
{
  if (IsSet())
  {
    text_log.Print(L"ON_ContentHash:\n");
    text_log.PushIndent();

    text_log.Print(L"Name hash: ");
    m_sha1_name_hash.Dump(text_log);
    text_log.Print(L"Content byte count = %llu\n",m_byte_count);
    text_log.Print(L"Content hash: ");
    m_sha1_content_hash.Dump(text_log);

    const ON_wString content_time
      = ( m_content_time <= 0 )
      ? L"unknown"
      : SecondsSinceJanOne1970UTCToString(m_content_time);
    text_log.Print(L"Content last modified time = %ls\n",static_cast<const wchar_t*>(content_time));

    const ON_wString hash_time
      = ( m_hash_time <= 0 )
      ? L"unknown"
      : SecondsSinceJanOne1970UTCToString(m_hash_time);
    text_log.Print(L"Content hash calculated time = %ls\n",static_cast<const wchar_t*>(content_time));

    text_log.PopIndent();
  }
  else
  {
    text_log.Print(L"ON_ContentHash::Unset\n");
  }
}

int ON_FileReference::Compare(
  const ON_FileReference& a,
  const ON_FileReference& b
  )
{
  int rc;
  for (;;)
  {
    // must compare every byte of every field.
    // If you don't like that, add another clearly named compare function.
    rc = ON_wString::ComparePath(a.m_full_path,b.m_full_path);
    if (0 != rc)
      break;
    rc = ON_wString::CompareOrdinal(a.m_full_path,b.m_full_path,false);
    if (0 != rc)
      break;
    rc = ON_wString::ComparePath(a.m_relative_path,b.m_relative_path);
    if (0 != rc)
      break;
    rc = ON_wString::CompareOrdinal(a.m_relative_path,b.m_relative_path,false);
    if (0 != rc)
      break;
    rc = ON_ContentHash::CompareContent(a.m_content_hash, b.m_content_hash);
    if (0 != rc)
      break;

    break;
  }
  return rc;
}


ON_FileReference::Status ON_FileReference::StatusFromUnsigned(
  unsigned int full_path_status_as_unsigned
  )
{
  switch (full_path_status_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_FileReference::Status::Unknown);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_FileReference::Status::FullPathValid);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_FileReference::Status::FileNotFound);
  }
  ON_ERROR("Invalid parameter.");
  return ON_FileReference::Status::Unknown;
}


ON_FileReference::ON_FileReference(
  const wchar_t* full_path,
  const wchar_t* relative_path,
  ON_ContentHash content_hash,
  ON_FileReference::Status full_path_status
  )
  : m_full_path(full_path)
  , m_relative_path(relative_path)
  , m_content_hash(content_hash)
  , m_full_path_status(full_path_status)
{}

ON_FileReference ON_FileReference::CreateFromFullPath(
  const wchar_t* full_path,
  bool bSetContentHash,
  bool bSetFullPathStatus
  )
{
  ON_wString local_full_path(full_path);
  local_full_path.TrimLeftAndRight();
  if (local_full_path.IsEmpty())
    return ON_FileReference::Unset;
  full_path = local_full_path;
  ON_FileReference::Status full_path_status = ON_FileReference::Unset.m_full_path_status;
  ON_ContentHash content_hash = ON_FileReference::Unset.m_content_hash;
  const bool bFileExists =
    ( bSetFullPathStatus || bSetContentHash )
    ? ON_FileSystem::IsFile(full_path)
    : false;
  if ( bSetFullPathStatus && bFileExists )
    full_path_status = ON_FileReference::Status::FullPathValid;
  if ( bSetContentHash && bFileExists )
    content_hash = ON_ContentHash::CreateFromFile(full_path);

  const wchar_t* relative_path = nullptr;
  const wchar_t* v = nullptr;
  const wchar_t* d = nullptr;
  const wchar_t* f = nullptr;
  const wchar_t* e = nullptr;
  on_wsplitpath(full_path,&v,&d,&f,&e);
  if (nullptr != d && nullptr != f && d < f && '.' == d[0])
  {
    relative_path = full_path;
    full_path = nullptr;
  }

  return ON_FileReference(
    full_path,
    relative_path,
    content_hash,
    full_path_status
    );
}


ON_FileReference::FindFilePreference ON_FileReference::FindFile(
  const wchar_t* base_path,
  bool bBasePathIncludesFileName,
  ON_wString& found_file_full_path
  ) const
{
  const ON_FileReference::FindFilePreference* file_preference = nullptr;
  const unsigned int file_preference_count = 0;
  return Internal_FindFile(
    base_path,
    bBasePathIncludesFileName,
    file_preference,
    file_preference_count,
    found_file_full_path,
    nullptr
    );
}

ON_FileReference::FindFilePreference ON_FileReference::FindFile(
  const wchar_t* base_path,
  bool bBasePathIncludesFileName,
  ON_FileReference::FindFilePreference first_choice,
  ON_FileReference::FindFilePreference second_choice,
  ON_FileReference::FindFilePreference third_choice,
  ON_FileReference::FindFilePreference forth_choice,
  ON_FileReference::FindFilePreference fifth_choice,
  ON_wString& found_file_full_path
  ) const
{
  const ON_FileReference::FindFilePreference file_preference[] = { first_choice, second_choice, third_choice, forth_choice, fifth_choice };
  const unsigned int file_preference_count = (unsigned int)(sizeof(file_preference)/sizeof(file_preference[0]));
  return Internal_FindFile(
    base_path,
    bBasePathIncludesFileName,
    file_preference,
    file_preference_count,
    found_file_full_path,
    nullptr
    );
}

ON_FileReference::FindFilePreference ON_FileReference::FindFileAndUpdateReference(
  const wchar_t* base_path,
  bool bBasePathIncludesFileName,
  bool bUpdateContentHash
  )
{
  ON_wString found_file_full_path;
  return FindFileAndUpdateReference(base_path,bBasePathIncludesFileName,bUpdateContentHash,found_file_full_path);
}

ON_FileReference::FindFilePreference ON_FileReference::FindFileAndUpdateReference(
  const wchar_t* base_path,
  bool bBasePathIncludesFileName,
  bool bUpdateContentHash,
  ON_wString& found_file_full_path
  )
{
  return FindFileAndUpdateReference(
    base_path,
    bBasePathIncludesFileName,
    ON_FileReference::FindFilePreference::None,
    ON_FileReference::FindFilePreference::None,
    ON_FileReference::FindFilePreference::None,
    ON_FileReference::FindFilePreference::None,
    ON_FileReference::FindFilePreference::None,
    bUpdateContentHash,
    found_file_full_path
    );
}

ON_FileReference::FindFilePreference ON_FileReference::FindFileAndUpdateReference(
  const wchar_t* base_path,
  bool bBasePathIncludesFileName,
  ON_FileReference::FindFilePreference first_choice,
  ON_FileReference::FindFilePreference second_choice,
  ON_FileReference::FindFilePreference third_choice,
  ON_FileReference::FindFilePreference forth_choice,
  ON_FileReference::FindFilePreference fifth_choice,
  bool bUpdateContentHash,
  ON_wString& found_file_full_path
  )
{
  const ON_FileReference::FindFilePreference file_preference[] = { first_choice, second_choice, third_choice, forth_choice, fifth_choice };
  const unsigned int file_preference_count = (unsigned int)(sizeof(file_preference)/sizeof(file_preference[0]));
  ON_ContentHash found_file_content_hash = ON_ContentHash::Unset;
  ON_FileReference::FindFilePreference rc = Internal_FindFile(
    base_path,
    bBasePathIncludesFileName,
    file_preference,
    file_preference_count,
    found_file_full_path,
    &found_file_content_hash
    );
  if (rc != ON_FileReference::FindFilePreference::None && found_file_full_path.IsNotEmpty())
  {
    m_full_path = found_file_full_path;
    m_relative_path = ON_wString::EmptyString;
    m_full_path_hash = ON_SHA1_Hash::EmptyContentHash;
    m_embedded_file_id = ON_nil_uuid;
    if ( bUpdateContentHash && found_file_content_hash.IsNotSet() )
      found_file_content_hash = ON_ContentHash::CreateFromFile(m_full_path);
    if ( found_file_content_hash.IsSet() )
      m_content_hash = found_file_content_hash;
  }
  return rc;
}

static ON_FileReference::FindFilePreference Internal_FindFileResult(
  const ON_wString& file_name_result,
  const ON_ContentHash& content_hash_result,
  ON_FileReference::FindFilePreference rc,
  ON_wString& found_file_full_path,
  ON_ContentHash* found_file_content_hash
  )
{
  found_file_full_path = file_name_result;
  if (nullptr != found_file_content_hash)
    *found_file_content_hash = content_hash_result;
  return rc;
}

ON_FileReference::FindFilePreference ON_FileReference::Internal_FindFile(
  const wchar_t* base_path,
  bool bBasePathIncludesFileName,
  const ON_FileReference::FindFilePreference* file_preference,
  unsigned int file_preference_count,
  ON_wString& found_file_full_path,
  ON_ContentHash* found_file_content_hash
  ) const
{
  for (;;)
  {
    if (m_full_path.IsEmpty())
      break;

    const wchar_t* filename = nullptr;
    on_wsplitpath(static_cast<const wchar_t*>(m_full_path), nullptr, nullptr, &filename, nullptr);
    if (nullptr == filename || 0 == filename[0])
      break;

    // Clean up base_path
    ON_wString local_base_path(base_path);
    base_path = nullptr;
    local_base_path.TrimLeftAndRight();

    if ( local_base_path.IsNotEmpty() )
    {
      // When the caller is confused and local_base_path identifies an existing file system element,
      // the set the bBasePathIncludesFileName parameter correctly.
      if (bBasePathIncludesFileName)
      {
        if (ON_FileSystem::IsDirectory(base_path))
          bBasePathIncludesFileName = false;
      }
      else
      {
        if (ON_FileSystem::IsFile(base_path))
          bBasePathIncludesFileName = true;
      }
    }

    if (local_base_path.IsNotEmpty() && bBasePathIncludesFileName)
    {
      bBasePathIncludesFileName = false;
      const wchar_t* start = static_cast<const wchar_t*>(local_base_path);
      const wchar_t* end_mark = nullptr;
      on_wsplitpath(start, nullptr, nullptr, &end_mark, nullptr);
      if (nullptr != start && nullptr != end_mark && start < end_mark)
      {
        local_base_path.SetLength(end_mark - start);
        if (false == ON_FileSystemPath::IsDirectorySeparator(local_base_path[local_base_path.Length() - 1], true))
          local_base_path += ON_FileSystemPath::DirectorySeparator;
        base_path = local_base_path;
      }
    }
    

    // Clean up file preferences and append defaults
    ON_FileReference::FindFilePreference default_pref[] =
    {
      ON_FileReference::FindFilePreference::RelativePath,
      ON_FileReference::FindFilePreference::FullPath,
      ON_FileReference::FindFilePreference::ContentMatch,
      ON_FileReference::FindFilePreference::BasePath,
      ON_FileReference::FindFilePreference::MostRecent
    };
    ON_FileReference::FindFilePreference pref[10 + (sizeof(default_pref) / sizeof(default_pref[0]))];
    unsigned int pref_capacity = (unsigned int)(sizeof(pref) / sizeof(pref[0]));
    unsigned int pref_count = 0;
    for (unsigned int pass = 0; pass < 2; pass++)
    {
      const ON_FileReference::FindFilePreference* pref_source = nullptr;
      unsigned int pref_source_count = 0;
      if (0 == pass)
      {
        pref_source = file_preference;
        pref_source_count = file_preference_count;
      }
      else if (1 == pass)
      {
        pref_source = default_pref;
        pref_source_count = (unsigned int)(sizeof(default_pref) / sizeof(default_pref[0]));
      }
      if (nullptr != pref_source)
        continue;
      for (unsigned int i = 0; i < pref_source_count && pref_count < pref_capacity; i++)
      {
        if (ON_FileReference::FindFilePreference::None == pref_source[i])
          continue;
        unsigned int j;
        for (j = 0; j < i; j++)
        {
          if (pref[j] == pref_source[i])
            break;
        }
        if (j < i)
          continue; // don't add duplicate
        if (pref_count < i)
          pref[pref_count] = pref[i];
        pref_count++;
      }
    }


    ON_wString candidate_file_name[3];  // full path, base path + relative path, base path + file_name
    ON_FileReference::FindFilePreference candidate_file_pref[3] = { ON_FileReference::FindFilePreference::None, ON_FileReference::FindFilePreference::None, ON_FileReference::FindFilePreference::None };
    unsigned int candidate_count = 0;
    for (unsigned int pass = 0; pass < 3; pass++)
    {
      ON_FileReference::FindFilePreference ffp = ON_FileReference::FindFilePreference::None;
      ON_wString name;
      switch (pass)
      {
      case 0:
        name = m_full_path;
        ffp = ON_FileReference::FindFilePreference::FullPath;
        break;
      case 1:
        if (nullptr != base_path && m_relative_path.IsNotEmpty())
        {
          name = ON_FileSystemPath::FullPathFromRelativePath(base_path,false,static_cast<const wchar_t*>(m_relative_path));
          ffp = ON_FileReference::FindFilePreference::RelativePath;
        }
        break;
      case 2:
        if (nullptr != base_path)
        {
          name = ON_FileSystemPath::FullPathFromRelativePath(base_path,false,filename);
          ffp = ON_FileReference::FindFilePreference::BasePath;
        }
        break;
      }
      if (name.IsEmpty() || ON_FileReference::FindFilePreference::None == ffp)
        continue;
      if ( false == ON_FileSystem::IsFile(name) )
        continue;
      if (ffp == pref[0])
      {
        // got lucky
        return Internal_FindFileResult(
          name,
          ON_ContentHash::Unset,
          ffp,
          found_file_full_path,
          found_file_content_hash);
      }
      candidate_file_name[candidate_count] = name;
      candidate_file_pref[candidate_count] = ffp;
      candidate_count++;
    }


    if (0 == candidate_count)
      break;

    if ( 1 == candidate_count )
    {
      return Internal_FindFileResult(
        candidate_file_name[0],
        ON_ContentHash::Unset,
        candidate_file_pref[0],
        found_file_full_path,
        found_file_content_hash);
    }


    ON_ContentHash candidate_file_content[3] = { ON_ContentHash::Unset, ON_ContentHash::Unset, ON_ContentHash::Unset };
    ON__UINT64 candidate_file_time[3] = { 0 };

    for (unsigned int i = 0; i < pref_count; i++)
    {
      switch (pref[i])
      {
      case ON_FileReference::FindFilePreference::None:
        break;

      case ON_FileReference::FindFilePreference::FullPath:
      case ON_FileReference::FindFilePreference::RelativePath:
      case ON_FileReference::FindFilePreference::BasePath:
        for (unsigned int j = 0; j < candidate_count; j++)
        {
          if (pref[i] == candidate_file_pref[j])
          {
            return Internal_FindFileResult(
              candidate_file_name[j],
              candidate_file_content[j],
              candidate_file_pref[j],
              found_file_full_path,
              found_file_content_hash);
          }
        }
        break;

      case ON_FileReference::FindFilePreference::ContentMatch:
        for (unsigned int j = 0; j < candidate_count; j++)
        {
          if (candidate_file_content[j].IsNotSet())
          {
            for (unsigned int k = 0; k < j; k++)
            {
              if (ON_wString::EqualPath(candidate_file_name[j], candidate_file_name[k]))
              {
                candidate_file_content[j] = candidate_file_content[k];
                break;
              }
            }
            if (candidate_file_content[j].IsNotSet())
            {
              // Use EqualFileNameSizeAndTime() to avoid expensive content calculation.
              if (ON_FileReference::FindFilePreference::FullPath == candidate_file_pref[j]
                && m_content_hash.EqualFileNameSizeAndTime(candidate_file_name[j]))
                candidate_file_content[j] = m_content_hash;
              else
                candidate_file_content[j] = ON_ContentHash::CreateFromFile(candidate_file_name[j]);
            }
          }
          if (candidate_file_content[j].IsSet())
          {
            if (ON_ContentHash::EqualContent(m_content_hash, candidate_file_content[j]))
              return Internal_FindFileResult(
                candidate_file_name[j],
                candidate_file_content[j],
                ON_FileReference::FindFilePreference::ContentMatch,
                found_file_full_path,
                found_file_content_hash);
            candidate_file_time[j] = candidate_file_content[j].ContentLastModifiedTime();
          }
        }
        break;

      case ON_FileReference::FindFilePreference::MostRecent:
        {
          unsigned int most_recent_dex = candidate_count;
          ON__UINT64 most_recent_time = 0;
          for (unsigned int j = 0; j < candidate_count; j++)
          {
            if (candidate_file_time[j] <= 0)
            {
              ON__UINT64 t = 0;
              for (unsigned int k = 0; k < j; k++)
              {
                if (ON_wString::EqualPath(candidate_file_name[j], candidate_file_name[k]))
                {
                  t = candidate_file_time[k];
                  break;
                }
              }
              if (t <= 0)
                ON_FileStream::GetFileInformation(candidate_file_name[j], nullptr, nullptr, &t);
              candidate_file_time[j] = t;
            }
            if (candidate_file_time[j] > most_recent_time)
            {
              most_recent_dex = j;
              most_recent_time = candidate_file_time[j];
            }
          }
          if (most_recent_time > 0 && most_recent_dex < candidate_count)
            return Internal_FindFileResult(
            candidate_file_name[most_recent_dex],
            candidate_file_content[most_recent_dex],
            ON_FileReference::FindFilePreference::MostRecent,
            found_file_full_path,
            found_file_content_hash);
        }
        break;

      default:
        break;
      }
    }

    return Internal_FindFileResult(
      candidate_file_name[0],
      candidate_file_content[0],
      candidate_file_pref[0],
      found_file_full_path,
      found_file_content_hash);
    break;
  }

  // file not found
  return Internal_FindFileResult(
    ON_wString::EmptyString,
    ON_ContentHash::Unset,
    ON_FileReference::FindFilePreference::None,
    found_file_full_path,
    found_file_content_hash);
}

bool ON_FileReference::IsSet() const
{
  return m_full_path.IsNotEmpty();
}

bool ON_FileReference::IsNotSet() const
{
  return m_full_path.IsEmpty();
}


bool ON_FileReference::Write(
  bool bUseArchiveBasePath,
  ON_BinaryArchive& archive
  ) const
{
  const wchar_t* base_path
    = bUseArchiveBasePath
    ? archive.ArchiveDirectoryNameAsPointer()
    : nullptr;
  bool bBasePathIncludesFileName = false;
  return Write( base_path, bBasePathIncludesFileName, archive );
}

bool ON_FileReference::Write(
  const wchar_t* base_path,
  bool bBasePathIncludesFileName,
  ON_BinaryArchive& archive
  ) const
{
  const int major_version = 1;

  // the embedded file id was added minor version 1
  const int minor_version = archive.Archive3dmVersion() >= 60 ? 1 : 0;

  if (!archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,major_version,minor_version))
    return false;

  bool rc = false;
  for (;;)
  {
    const bool bBasePathIsEmpty = (nullptr == base_path || 0 == base_path[0]);

    const ON_wString full_path
      = m_full_path.IsEmpty() && m_relative_path.IsNotEmpty() && false == bBasePathIsEmpty
      ? ON_FileSystemPath::CombinePaths(base_path, bBasePathIncludesFileName, m_relative_path, true, false)
      : m_full_path;
    if (!archive.WriteString(full_path))
      break;

    const ON_wString relative_path 
      = (bBasePathIsEmpty || m_full_path.IsEmpty() )
      ? m_relative_path
      : ON_FileSystemPath::RelativePath(m_full_path,true,base_path,bBasePathIncludesFileName);
    if (!archive.WriteString(relative_path))
      break;

    if (!m_content_hash.Write(archive))
      break;
    unsigned int i = static_cast<unsigned int>(m_full_path_status);
    if (!archive.WriteInt(i))
      break;

    // embedded file id added at chunk version 1.1
    ON_UUID embedded_file_id = m_embedded_file_id;

    if ( IsSet() && archive.Active3dmTable() >  ON_3dmArchiveTableType::bitmap_table )
    {
      const ON_ComponentManifestItem& embedded_file_item = archive.Manifest().ItemFromNameHash(
        ON_ModelComponent::Type::Image,
        ON_NameHash::CreateFilePathHash(*this)
        );
      if (embedded_file_item.IsValid())
      {
        // A file with identical full path is embedded in this archive.
        // The embedded file can be used if the referenced file cannot
        // be found when this archive is read.
        embedded_file_id = embedded_file_item.Id();
      }
    }

    if (!archive.WriteUuid(embedded_file_id))
      break;

    rc = true;
    break;
  }

  if (!archive.EndWrite3dmChunk())
    rc = false;
  return rc;
}

bool ON_FileReference::Read(
  ON_BinaryArchive& archive
  )
{
  *this = ON_FileReference::Unset;
  int major_version = 0;
  int minor_version = 0;
  if (!archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version))
    return false;
  bool rc = false;
  for (;;)
  {
    if ( 1 != major_version)
      break;
    if (!archive.ReadString(m_full_path))
      break;
    if (!archive.ReadString(m_relative_path))
      break;
    if (!m_content_hash.Read(archive))
      break;
    
    unsigned int full_path_status_as_unsigned = 0;
    if (!archive.ReadInt(&full_path_status_as_unsigned))
      break;
    //m_full_path_status = ON_FileReference::StatusFromUnsigned(full_path_status_as_unsigned);
    // The full path status must be validated after each read.
    m_full_path_status = ON_FileReference::Status::Unknown; 

    if (minor_version >= 1)
    {
      if (!archive.ReadUuid(m_embedded_file_id))
        break;
    }
    rc = true;
    break;
  }

  if (!archive.EndRead3dmChunk())
    rc = false;
  return rc;

}

void ON_FileReference::Dump(
  class ON_TextLog& text_log
  ) const
{
  text_log.Print("Full path: \"%ls\"\n", static_cast<const wchar_t*>(m_full_path));
  text_log.PushIndent();
  text_log.Print("Relative path: \"%ls\"\n", static_cast<const wchar_t*>(m_relative_path));
  m_content_hash.Dump(text_log);
  text_log.PopIndent();
}

unsigned int ON_FileReference::SizeOf() const
{
  return m_full_path.SizeOf() + m_relative_path.SizeOf() + (unsigned int)(sizeof(*this) - sizeof(m_full_path) - sizeof(m_relative_path));
}

const ON_wString& ON_FileReference::FullPath() const
{
  return m_full_path;
}

const wchar_t* ON_FileReference::FullPathAsPointer() const
{
  return static_cast<const wchar_t*>(m_full_path);
}

void ON_FileReference::SetFullPath(
  const wchar_t* full_path,
  bool bSetContentHash
  )
{
  ON_wString local_full_path(full_path);
  local_full_path.TrimLeftAndRight();
  if (local_full_path.IsEmpty())
    *this = ON_FileReference::Unset;
  else
  {
    const ON_wString clean_full_path = ON_FileSystemPath::CleanPath(local_full_path);
    const bool bFullPathChanged = (0 != ON_wString::CompareOrdinal(clean_full_path, m_full_path, false));
    m_full_path = clean_full_path;
    m_full_path_hash = ON_SHA1_Hash::EmptyContentHash;
    m_embedded_file_id = ON_nil_uuid;
    m_relative_path = ON_wString::EmptyString;
    if (bSetContentHash)
    {
      if (m_content_hash.IsNotSet() || false == m_content_hash.EqualFileNameSizeAndTime(m_full_path))
        m_content_hash = ON_ContentHash::CreateFromFile(m_full_path);
      m_full_path_status
        =  (m_content_hash.IsSet())
        ? ON_FileReference::Status::FullPathValid
        : ON_FileReference::Status::FileNotFound;
    }
    else if (bFullPathChanged)
    {
      m_content_hash = ON_ContentHash::Unset;

      //https://mcneel.myjetbrains.com/youtrack/issue/RH-85181
      //This used to check whether the file was there, eagerly, but this can be a big performance hit, especially on Google Drive.
      //And the accessor for this property is basically never called.
      m_full_path_status = ON_FileReference::Status::Unknown;
    }
  }
}

void ON_FileReference::SetFullPath(
  const char* full_path,
  bool bSetContentHash
  )
{
  const ON_wString local_full_path(full_path);
  SetFullPath(static_cast<const wchar_t*>(local_full_path),bSetContentHash);
}



void ON_FileReference::ClearFullPath()
{
  m_full_path = ON_wString::EmptyString;
  m_full_path_hash = ON_SHA1_Hash::EmptyContentHash;
  m_embedded_file_id = ON_nil_uuid;
  m_full_path_status = ON_FileReference::Status::Unknown;
}

const ON_wString& ON_FileReference::RelativePath() const
{
  return m_relative_path;
}

const wchar_t* ON_FileReference::RelativePathAsPointer() const
{
  return static_cast<const wchar_t*>(m_relative_path);
}

void ON_FileReference::SetRelativePath(
  const wchar_t* relative_path
  )
{
  m_relative_path = relative_path;
  m_relative_path.TrimLeftAndRight();
}

void ON_FileReference::SetRelativePath(
  const char* relative_path
  )
{
  m_relative_path = relative_path;
  m_relative_path.TrimLeftAndRight();
}

void ON_FileReference::SetRelativePathFromBasePath(
  const wchar_t* base_path,
  bool bBasePathContainsFileName
  )
{
  const ON_wString relative_path = ON_FileSystemPath::RelativePath(
    m_full_path,
    true,
    base_path,
    bBasePathContainsFileName
    );
}

void ON_FileReference::SetRelativePathFromBasePath(
  const char* base_path,
  bool bBasePathContainsFileName
  )
{
  const ON_wString local_base_path(base_path);
  SetRelativePathFromBasePath(static_cast<const wchar_t*>(local_base_path),bBasePathContainsFileName);
}

void ON_FileReference::ClearRelativePath()
{
  m_relative_path = ON_wString::EmptyString;
}

const ON_ContentHash& ON_FileReference::ContentHash() const
{
  return m_content_hash;
}

void ON_FileReference::SetContentHash(
  ON_ContentHash content_hash
  )
{
  m_content_hash = content_hash;
}

void ON_FileReference::ClearContentHash()
{
  m_content_hash = ON_ContentHash::Unset;
}

bool ON_FileReference::UpdateContentHash()
{
  if (m_full_path.IsEmpty())
  {
    m_content_hash = ON_FileReference::Unset.ContentHash();
    return true;
  }
  m_content_hash = ON_ContentHash::CreateFromFile(m_full_path);
  m_recent_content_hash = m_content_hash;
  return m_content_hash.IsSet();
}

const ON_ContentHash& ON_FileReference::RecentContentHash(
  ON__UINT64 recent_time
) const
{
  const ON__UINT64 current_time = ON_SecondsSinceJanOne1970UTC();
  if (0 == recent_time || recent_time > current_time)
    recent_time = current_time;
  if (m_recent_content_hash.IsNotSet() || m_recent_content_hash.HashCalculationTime() < recent_time)
  {
    if (m_content_hash.IsSet() && m_content_hash.HashCalculationTime() >= recent_time)
      m_recent_content_hash = m_content_hash;
    else
      m_recent_content_hash = ON_ContentHash::CreateFromFile(m_full_path);
  }
  return m_recent_content_hash;
}

const ON_SHA1_Hash& ON_FileReference::FullPathHash() const
{
  if (m_full_path.IsNotEmpty() && m_full_path_hash == ON_SHA1_Hash::EmptyContentHash)
  {
    m_full_path_hash = ON_SHA1_Hash::FileSystemPathHash(m_full_path);
  }
  return m_full_path_hash;
}

ON_FileReference::Status ON_FileReference::FullPathStatus() const
{
  return m_full_path_status;
}

void ON_FileReference::SetFullPathStatus(
  ON_FileReference::Status full_path_status
  )
{
  m_full_path_status = full_path_status;
}

ON_UUID ON_FileReference::EmbeddedFileId() const
{
  return m_embedded_file_id;
}

void ON_FileReference::SetEmbeddedFileId(
  ON_UUID embedded_file_id
  )
{
  m_embedded_file_id = embedded_file_id;
}

// deprecated
bool ON_FileSystemPath::PathExists(
  const char* path
)
{
  return ON_FileSystem::PathExists(path);
}

// deprecated
bool ON_FileSystemPath::PathExists(
  const wchar_t* path
)
{
  return ON_FileSystem::PathExists(path);
}

// deprecated
bool ON_FileSystemPath::IsFile(
  const char* path
)
{
  return ON_FileSystem::IsFile(path);
}

// deprecated
bool ON_FileSystemPath::IsFile(
  const wchar_t* path
)
{
  return ON_FileSystem::IsFile(path);
}

// deprecated
bool ON_FileSystemPath::IsDirectory(
  const char* path
)
{
  return ON_FileSystem::IsDirectory(path);
}

// deprecated
bool ON_FileSystemPath::IsDirectory(
  const wchar_t* path
)
{
  return ON_FileSystem::IsDirectory(path);
}

// ON_UnicodeTextFile

class ON_File
{
public:
  virtual ~ON_File() { }

  bool Open(const wchar_t* filename, const wchar_t* mode)
  {
    _file = ON_FileStream::Open(filename, mode);  
    return nullptr != _file;
  }

  bool Close(void)                                const { return ON_FileStream::Close(_file) == 0; }
  bool SeekFromCurrentPosition(ON__INT64 offset)  const { return ON_FileStream::SeekFromCurrentPosition(_file, offset); }
  bool SeekFromStart(ON__INT64 offset)            const { return ON_FileStream::SeekFromStart(_file, offset); }
  bool SeekFromEnd(ON__INT64 offset)              const { return ON_FileStream::SeekFromEnd(_file, offset); }
  bool Seek(ON__INT64 offset, int origin)         const { return ON_FileStream::Seek(_file, offset, origin); }
  ON__INT64  CurrentPosition(void)                const { return ON_FileStream::CurrentPosition(_file); }
  ON__UINT64 Read(ON__UINT64 count, void* buffer) const { return ON_FileStream::Read(_file, count, buffer); }

  ON__UINT64 Write(ON__UINT64 count, const void* buffer) const
  {
    return ON_FileStream::Write(_file, count, buffer);
  }

  ON__UINT64 GetLength(void) const
  {
    const auto cur = CurrentPosition();
    SeekFromEnd(0);
    const auto end = CurrentPosition();
    SeekFromStart(cur);

    return end;
  }

private:
  FILE* _file = nullptr;
};

class ON_UnicodeTextFilePrivate final
{
public:
  ~ON_UnicodeTextFilePrivate() { Close(); }

  bool Open(const wchar_t* wszFullPath, ON_UnicodeTextFile::Modes mode);
  bool Close(void);
  bool ReadString(ON_wString& s);
  bool WriteString(const wchar_t* wsz);
  bool ReadHeader(ON_UnicodeTextFile::Types& t);
  bool WriteHeader(void);
  bool ReadStringFromUTF8(ON_wString& s);
  bool ReadStringFromUTF16(ON_wString& s);
  bool WriteStringToUTF8(const wchar_t* wsz);
  bool WriteStringToUTF16(const wchar_t* wsz);
  size_t ReadData(void* buf, size_t bytes_to_read);
  size_t WriteData(const void* buf, size_t bytes_to_write);

public:
  ON_File _file;
  ON_UnicodeTextFile::Types _type = ON_UnicodeTextFile::Types::Unknown;
};

size_t ON_UnicodeTextFilePrivate::ReadData(void* buf, size_t bytes_to_read)
{
  return size_t(_file.Read(bytes_to_read, buf));
}

size_t ON_UnicodeTextFilePrivate::WriteData(const void* buf, size_t bytes_to_write)
{
  return size_t(_file.Write(bytes_to_write, buf));
}

static const wchar_t* FileStreamMode(ON_UnicodeTextFile::Modes m)
{
  if (m == ON_UnicodeTextFile::Modes::Read)
    return L"rb";

  if (m == ON_UnicodeTextFile::Modes::Write)
    return L"wb";

  ON_ASSERT(false);
  return L"";
}

bool ON_UnicodeTextFilePrivate::Open(const wchar_t* wszFullPath, ON_UnicodeTextFile::Modes mode)
{
  bool ok = false;
  int attemptsCounter = 0;

  while (!ok && (attemptsCounter < 100))
  {
    if (_file.Open(wszFullPath, FileStreamMode(mode)))
    {
      ok = true;
    }
    else
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      attemptsCounter++;
    }
  }

  if (ok)
  {
    if (ON_UnicodeTextFile::Modes::Write == mode)
    {
      ok = WriteHeader();
    }
    else
    {
      ok = ReadHeader(_type);
    }
  }

  return ok;
}

bool ON_UnicodeTextFilePrivate::Close(void)
{
  return _file.Close();
}

bool ON_UnicodeTextFilePrivate::ReadHeader(ON_UnicodeTextFile::Types& t)
{
  if (0 != _file.CurrentPosition())
    return false;

  ON__UINT8 pBuf[3] = { 0 };

  if (2 != ReadData(pBuf, 2))
    return false;

  if (pBuf[0] == ON__UINT8(0xFF))
  {
    if (pBuf[1] == ON__UINT8(0xFE))
    {
      t = ON_UnicodeTextFile::Types::UTF16;
      return true;
    }
  }

  if (pBuf[0] == ON__UINT8(0xEF))
  {
    if (pBuf[1] == ON__UINT8(0xBB))
    {
      if (1 == ReadData(pBuf + 2, 1))
      {
        if (pBuf[2] == ON__UINT8(0xBF))
        {
          t = ON_UnicodeTextFile::Types::UTF8;
          return true;
        }
      }
    }
  }

  // No BOM was found so rewind and assume UTF8. This allows testing with ASCII files.
  _file.SeekFromStart(0);
  t = ON_UnicodeTextFile::Types::UTF8;

  return true;
}

bool ON_UnicodeTextFilePrivate::WriteHeader(void)
{
  ON__UINT8 pBuf[3] = { 0 };

  size_t sizeBOM = 2;
  if (ON_UnicodeTextFile::Types::UTF8 == _type)
  {
    sizeBOM = 3;
    pBuf[0] = ON__UINT8(0xEF);
    pBuf[1] = ON__UINT8(0xBB);
    pBuf[2] = ON__UINT8(0xBF);
  }
  else
  if (ON_UnicodeTextFile::Types::UTF16 == _type)
  {
    pBuf[0] = ON__UINT8(0xFF);
    pBuf[1] = ON__UINT8(0xFE);
  }
  else ON_ASSERT(false); // Did you forget to set the type in the constructor?

  if (!WriteData(pBuf, sizeBOM))
    return false;

  return true;
}

bool ON_UnicodeTextFilePrivate::ReadString(ON_wString& s)
{
  switch (_type)
  {
  case ON_UnicodeTextFile::Types::UTF8:
    return ReadStringFromUTF8(s);

  case ON_UnicodeTextFile::Types::UTF16:
    return ReadStringFromUTF16(s);

  case ON_UnicodeTextFile::Types::Unknown:
  default:
    return false;
  }
}

bool ON_UnicodeTextFilePrivate::WriteString(const wchar_t* wsz)
{
  switch (_type)
  {
  case ON_UnicodeTextFile::Types::UTF8:
    return WriteStringToUTF8(wsz);

  case ON_UnicodeTextFile::Types::UTF16:
    return WriteStringToUTF16(wsz);

  case ON_UnicodeTextFile::Types::Unknown:
  default:
    return false;
  }
}

bool ON_UnicodeTextFilePrivate::ReadStringFromUTF8(ON_wString& s)
{
  const auto size_in_bytes = size_t(_file.GetLength() - _file.CurrentPosition());
  auto p = std::unique_ptr<ON__UINT8[]>(new ON__UINT8[size_in_bytes + 1]);
  auto* pBuffer = p.get();

  ReadData(pBuffer, size_in_bytes);
  pBuffer[size_in_bytes] = 0;

  const char* pUTF8 = reinterpret_cast<const char*>(pBuffer);

  const auto num_chars = ON_ConvertUTF8ToWideChar(false, pUTF8, -1, nullptr, 0, nullptr, 0, 0, nullptr);

  auto* string_buf = s.SetLength(num_chars);
  if (nullptr == string_buf)
    return false;

  ON_ConvertUTF8ToWideChar(false, pUTF8, -1, string_buf, num_chars+1, nullptr, 0, 0, nullptr);

  return !s.IsEmpty();
}

bool ON_UnicodeTextFilePrivate::ReadStringFromUTF16(ON_wString& s)
{
  const auto char_size = sizeof(ON__UINT16);
  const auto size_in_bytes = size_t(_file.GetLength() - _file.CurrentPosition());
  const auto size_in_chars = size_t(size_in_bytes / char_size);

#ifdef ON_RUNTIME_WIN
  // On Windows, wchar_t is UTF16 so we can load the file directly into the ON_wString.
  ON_ASSERT(sizeof(wchar_t) == sizeof(ON__UINT16));

  auto* buf = s.SetLength(size_in_chars);
  if (nullptr == buf)
    return false;

  if (ReadData(buf, size_in_bytes) != size_in_bytes)
    return false;

  buf[size_in_chars] = 0;
#else
  // On Mac wchar_t is UTF32 so we have to load the file into a buffer and then convert it to the ON_wString.
  auto p = std::unique_ptr<ON__UINT16[]>(new ON__UINT16[size_in_chars + 1]);
  auto* pUTF16 = p.get();
  ReadData(pUTF16, size_in_bytes);
  pUTF16[size_in_chars] = 0;

  const auto num_chars = ON_ConvertUTF16ToUTF32(false, pUTF16, -1, nullptr, 0, nullptr, 0, 0, nullptr);
  auto* string_buf = s.SetLength(num_chars);
  if (nullptr == string_buf)
    return false;

  ON_ASSERT(sizeof(wchar_t) == sizeof(ON__UINT32));
  auto* pWide = reinterpret_cast<ON__UINT32*>(string_buf);
  ON_ConvertUTF16ToUTF32(false, pUTF16, -1, pWide, num_chars+1, nullptr, 0, 0, nullptr);
#endif

  return true;
}

bool ON_UnicodeTextFilePrivate::WriteStringToUTF8(const wchar_t* wsz)
{
  const auto num_chars = ON_ConvertWideCharToUTF8(false, wsz, -1, nullptr, 0, nullptr, 0, 0, nullptr);

  auto p = std::unique_ptr<char[]>(new char[size_t(num_chars) + 1]);
  auto* pBuffer = p.get();

  ON_ConvertWideCharToUTF8(false, wsz, -1, pBuffer, num_chars + 1, nullptr, 0, 0, nullptr);

  if (WriteData(pBuffer, num_chars) != num_chars)
    return false;

  return true;
}

bool ON_UnicodeTextFilePrivate::WriteStringToUTF16(const wchar_t* wsz)
{
#ifdef ON_RUNTIME_WIN
  // On Windows, wchar_t is UTF16 so we can save the file directly from 'wsz'.
  ON_ASSERT(sizeof(wchar_t) == sizeof(ON__UINT16));

  const auto size_in_bytes = wcslen(wsz) * sizeof(wchar_t);
  if (WriteData(wsz, size_in_bytes) != size_in_bytes)
    return false;
#else
  // On Mac wchar_t is UTF32 so we have to convert 'wsz' to UTF16 in a buffer and write the buffer to the file.
  ON_ASSERT(sizeof(wchar_t) == sizeof(ON__UINT32));
  auto* pWide = reinterpret_cast<const ON__UINT32*>(wsz);

  const auto num_chars = ON_ConvertUTF32ToUTF16(false, pWide, -1, nullptr, 0, nullptr, 0, 0, nullptr);

  const auto num_chars_inc_term = num_chars + 1;
  auto p = std::unique_ptr<ON__UINT16[]>(new ON__UINT16[num_chars_inc_term]);
  auto* pUTF16 = p.get();

  ON_ConvertUTF32ToUTF16(false, pWide, -1, pUTF16, num_chars_inc_term, nullptr, 0, 0, nullptr);

  const auto size_in_bytes = num_chars * sizeof(ON__UINT16);
  if (WriteData(pUTF16, size_in_bytes) != size_in_bytes)
    return false;
#endif

  return true;
}

ON_UnicodeTextFile::ON_UnicodeTextFile(Types t)
{
  _private = new ON_UnicodeTextFilePrivate;
  _private->_type = t;
}

ON_UnicodeTextFile::~ON_UnicodeTextFile()
{
  delete _private;
}

bool ON_UnicodeTextFile::Open(const wchar_t* wszFullPath, Modes mode)
{
  return _private->Open(wszFullPath, mode);
}

bool ON_UnicodeTextFile::Close(void)
{
  return _private->Close();
}

bool ON_UnicodeTextFile::ReadString(ON_wString& s)
{
  return _private->ReadString(s);
}

bool ON_UnicodeTextFile::WriteString(const wchar_t* wsz)
{
  return _private->WriteString(wsz);
}
