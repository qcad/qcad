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

#if !defined(OPENNURBS_FILE_UTILITIES_INC_)
#define OPENNURBS_FILE_UTILITIES_INC_

class ON_CLASS ON_FileSystem
{
private:
  ON_FileSystem() = delete;
  ~ON_FileSystem() = delete;
  ON_FileSystem(const ON_FileSystem&) = delete;
  ON_FileSystem& operator=(const ON_FileSystem&) = delete;

public:
  static bool PathExists(
    const char* path
    );

  static bool PathExists(
    const wchar_t* path
    );

  /*
  Returns:
    True if path is a directory.
    False otherwise.
  */
  static bool IsDirectory(
    const char* path
    );

  /*
  Returns:
    True if path is a directory.
    False otherwise.
  */
  static bool IsDirectory(
    const wchar_t* path
    );

  /*
  Returns:
    True if path is a directory where files can be written.
    False otherwise.
  */
  static bool IsDirectoryWithWriteAccess(
    const char* path
    );

  /*
  Returns:
    True if path is a directory where files can be written.
    False otherwise.
  */
  static bool IsDirectoryWithWriteAccess(
    const wchar_t* path
    );
  
  /*
  Returns:
    True if path is a file.
    False otherwise.
  */
  static bool IsFile(
    const char* path
    );

  /*
  Returns:
    True if path is a file.
    False otherwise.
  */
  static bool IsFile(
    const wchar_t* path
    );

  /*
  Description
    Remove a file
  Parameters:
    file_path - [in]
      name of file to delete
  Returns:
    True if the file existed and was removed.
  */
  static bool RemoveFile(
    const char* file_path
  );

  /*
  Description
    Remove a file
  Parameters:
    file_path - [in]
      name of file to delete
  Returns:
    True if the file existed and was removed.
  */
  static bool RemoveFile(
    const wchar_t* file_path
  );
};

class ON_CLASS ON_FileSystemPath
{
private:
  ON_FileSystemPath() = delete;
  ~ON_FileSystemPath() = delete;
  ON_FileSystemPath(const ON_FileSystemPath&) = delete;
  ON_FileSystemPath& operator=(const ON_FileSystemPath&) = delete;

public:
  /*
  Platform dependent character used to separate directory names.
  On Windows platforms: 
    ON_FileSystemPath::DirectorySeparator = ON_wString::Backslash.
  On UNIX (including modern Apple) platforms: 
    ON_FileSystemPath::DirectorySeparator = ON_wString::Slash.
  */
  static const char DirectorySeparatorAsChar;
  static const wchar_t DirectorySeparator;

  static const char AlternateDirectorySeparatorAsChar;
  static const wchar_t AlternateDirectorySeparator;

  static bool IsDirectorySeparator(
    char c,
    bool bAllowAlternate
    );

  static bool IsDirectorySeparator(
    wchar_t c,
    bool bAllowAlternate
    );

  /*
  Description:
    Find the locations in a path the specify the drive, directory,
    file name and file extension.
  Parameters:
    path - [in]
      path to split
    volume - [out] (pass null if you don't need the volume)
      If volume is not null and the path parameter begins with a
      Windows volume specification, *volume will either be
      the Windows volume letter followed by the trailing colon
      or a Windows UNC \\<hostname>.  Otherwise volume will
      be the empty string.
    dir - [out] (pass null if you don't need the directory)
      If dir is not null and the path parameter contains a
      directory specification, then the returned value of *dir
      will be the directory specification including the trailing
      slash.
    file_name_stem - [out] (pass null if you don't need the file name stem)
      If file_name_stem is not null and the path parameter contains a
      file name specification, then the returned value of *file_name_stem
      will be the file name stem.
    file_name_ext - [out] (pass null if you don't need the extension)
      If file_name_ext is not null and the path parameter contains a
      file name extension specification, then the returned value of
      *file_name_ext will be the file name extension including the initial
      '.' character.
  Remarks:
    This function will treat a front slash ( / ) and a back slash
    ( \ ) as directory separators.  Because this function parses
    file names store in .3dm files and the .3dm file may have been
    written on a Windows computer and then read on a another
    computer, it looks for a volume specification even when the
    operating system is not Windows.
    This function will not return an directory that does not
    end with a trailing slash.
    This function will not return an empty filename and a non-empty
    extension.
    This function parses the path string according to these rules.
    It does not check the actual file system to see if the answer
    is correct.
  See Also:
    on_splitpath
  */
  static void SplitPath( 
    const char* path,
    ON_String* volume,
    ON_String* dir,
    ON_String* file_name_stem,
    ON_String* file_name_ext
    );

  static void SplitPath( 
    const char* path,
    ON_wString* volume,
    ON_wString* dir,
    ON_wString* file_name_stem,
    ON_wString* file_name_ext
    );

  static void SplitPath( 
    const wchar_t* path,
    ON_wString* volume,
    ON_wString* dir,
    ON_wString* file_name_stem,
    ON_wString* file_name_ext
    );
  
  static void SplitPath( 
    const wchar_t* path,
    ON_wString* volume,
    ON_wString* dir,
    ON_wString* file_name_stem_and_extension
    );

  static bool FilePathHas3dmExtension(
    const wchar_t* file_path,
    bool bAllow3dmbakExtension
  );

  static bool FilePathHas3dmExtension(
    const char* file_path,
    bool bAllow3dmbakExtension
  );

  /*
  Description:
    Determine if the file_name string is a permitted file name.
    Valid file names must be non empty, cannot have two periods in a row,
    and cannot contain directory separators, tildes, and other 
    platform specific values.
  Parameters:
    file_name - [in]
      string to test.
    bAllPlatforms - [in]
      If true, test name for all supported platforms.
  Returns:
    True if the string can be a file name.
  */
  static bool IsValidFileName(
    const char* file_name,
    bool bAllPlatforms
  );

  /*
  Description:
    Determine if the file_name string is a permitted file name.
    Valid file names must be non empty, cannot have two periods in a row,
    and cannot contain directory separators, tildes, and other 
    platform specific values.
  Parameters:
    file_name - [in]
      string to test.
    bAllPlatforms - [in]
      If true, test name for all supported platforms.
  Returns:
    True if the string can be a file name.
  */
  static bool IsValidFileName(
    const wchar_t* file_name,
    bool bAllPlatforms
  );

  /*
  Parameters:
    path - [in]
      path to split
  Returns:
    The volume portion of the path. 
  */
  static const ON_wString VolumeFromPath(
    const wchar_t* path
  );

  /*
  Parameters:
    path - [in]
      path to split
  Returns:
    The directory portion of the path. 
  */
  static const ON_wString DirectoryFromPath(
    const wchar_t* path
  );

  /*
  Parameters:
    path - [in]
      path to split
  Returns:
    The volume and directory portion of the path. 
  */
  static const ON_wString VolumeAndDirectoryFromPath(
    const wchar_t* path
  );

  /*
  Parameters:
    path - [in]
      path to split
    bIncludeExtension - [in]
  Returns:
    The file name portion of the path. 
  */
  static const ON_wString FileNameFromPath(
    const wchar_t* path,
    bool bIncludeExtension
  );

  /*
  Parameters:
    path - [in]
      path to split
  Returns:
    The file name extension portion of the path, including the leading period or "dot".
  */
  static const ON_wString FileNameExtensionFromPath(
    const wchar_t* path
  );

  /*
  Description:
    Condenses // to /
    Condenses /./ to /
    Condenses /sfsdf/../ to /
    Sets all directory separators to directory_separator.
  Parameters:
    bAllowWindowsUNCHostNameOrDiskLetter - [in]
      If bAllowWindowsUNCHostNameOrDiskLetter and the path begins with \\HostName followed by
      a directory separator, then the initial \\ is not condensed. 
      If the path begins with X: followed by a directory separator, where "X" is a single
      letter in the range A to Z or a to z, then the path is considered valid.
    bDeleteWindowsUNCHostNameOrDiskLetter - [in]
      If bAllowWindowsUNCHostNameOrDiskLetter is true and the path begins with a UNC
      host name or disk letter followed by a directory separator, then host name or disk letter
      is deleted.  This is useful when using paths from a Windows platform on a
      non-Windows platform.
    bExpandUser - [in]
      If the path begins with ~ and ON_FileSystemPath::PlatformPath( ON_FileSystemPath::PathId::UserHomeDirectory ) 
      is not empty, then the ~ is replaced with absolute path of user's home directory.
    directory_separator - [in]
      If 0 == directory_separator, then the first directory separator
      is kept when condensing occurs.
      ON_wString::FileSystemPathSeparator is a good choice if you want
      to use the current runtime's separator.
    dirty_path - [in]
      path to clean.
  Return:
    Cleaned path.
  */
  static const ON_wString CleanPath(
    bool bTrimLeft,
    bool bTrimRight,
    bool bAllowWindowsUNCHostNameOrDiskLetter,
    bool bDeleteWindowsUNCHostNameOrDiskLetter,
    bool bExpandUser,
    const wchar_t directory_separator,
    const wchar_t* dirty_path
    );

  static const ON_wString CleanPath(
    bool bTrimLeft,
    bool bTrimRight,
    bool bAllowWindowsUNCHostNameOrDiskLetter,
    bool bDeleteWindowsUNCHostNameOrDiskLetter,
    const wchar_t directory_separator,
    const wchar_t* dirty_path
    );

  /*
  Description:
    If the path begins with ~ and ON_FileSystemPath::PlatformPath( ON_FileSystemPath::PathId::UserHomeDirectory ) 
    is not empty, then the ~ is replaced with absolute path of user's home directory.
  */
  static const ON_wString ExpandUser(
    const char* dirty_path
  );
  static const ON_wString ExpandUser(
    const wchar_t* dirty_path
  );

  /*
  Parameters:
    path - [in]
      path to test
    directory_separator - [in]
      If 0 == directory_separator, then either ON_wString::FileSystemPathSeparator 
      or ON_wString::AlternateFileSystemPathSeparator is permitted as a directory
      separator.
      ON_wString::FileSystemPathSeparator is a good choice if you want
      to use the current runtime's separator.
  Returns:
    True if path begins with ../ or ./
  */
  static bool IsRelativePath(
    const wchar_t* path,
    const wchar_t directory_separator
    );


  /*
  Parameters:
    path - [in]
      path to test
  Returns:
    True if path begins with ../ or ..\ or ./ or .\
  */
  static bool IsRelativePath(
    const wchar_t* path
    );
  /*
  Description:
    Condenses // to /
    Condenses /./ to /
    Condenses /sfsdf/../ to /
    Trims left and right white space.
    Sets all directory separators to ON_FileSystemPath::DirectorySeparator.
    If the Platform is not windows, the UNC host names and volume letters are deleted.
  */
  static const ON_wString CleanPath(
    const wchar_t* dirty_path
    );
  
  /*
  Description:
    Get a the relative path from base_path to full_path.
  Parameters:
    full_path - [in]
    base_path - [in]

  Example
      full_path = L"c:/a/b/c/d/somefile.txt";
      base_path = L"C:/A/B/X/Y/Z/model.3dm";
      ON_wString::GetRelativePath(full_path,base_path) returns
      L"../../../c/d/somefile.txt"

  Example
      full_path = L"c:/a/b/somefile.txt";
      base_path = L"C:/A/B/model.3dm";
      ON_wString::GetRelativePath(full_path,base_path) returns
      L"./somefile.txt"

  Remarks:
    Path separators on the input can be mixed.
    Path separators on the returned relative path are ON_wString::FileSystemPathSeparator
  */
  static const ON_wString RelativePath(
    const wchar_t* full_path,
    bool bFullPathIncludesFileName,
    const wchar_t* base_path,
    bool bBasePathIncludesFileName
    );

  static const ON_wString FullPathFromRelativePath(
    const wchar_t* base_path,
    bool bBasePathIncludesFileName,
    const wchar_t* relative_path
    );

  /*
  Returns:
    true if the platform file system ignores case.
  Remarks:
    Windows and default installations of OS X 10.10.3, and default installations of the UNIX 
    terminal interface in OS X 10.10.3 and later ignore case.
    In the case of OX X, a user can override the default setting.
  */
  static bool PlatformPathIgnoreCase();

  /*
  Parameters:
    bWithTrailingDirectorySeparator - [in]
      true - returned path will have a trailing directory separator.
      false - returned path will not have a trailing directory separator.
  Returns:
    The platform current working directory which should be the directory
    where ON::OpenFile("fname","r") would look for a file named "fname".
  */
  static const ON_wString CurrentDirectory(
    bool bWithTrailingDirectorySeparator
  );

  /*
  Description:
    Removes file name from path.
  Parameters:
    path - [in]
      file system path with a file name.
    file_name - [out]
      If file_name is not nullptr, the removed portion of path
      is returned here.
  Returns:
    path with any file name removed.
  Remarks:
    This function uses on_wsplitpath() to decide if the path ends with characters that
    could be a file name. It does not inspect the file system to see if the file exists.
  */
  static const ON_wString RemoveFileName(
    const wchar_t* path,
    ON_wString* file_name
  );

  /*
  Description:
    Removes Windows volume name from path.
  Parameters:
    path - [in]
      file system path
    volume_name - [out]
      If volume_name is not nullptr, the removed portion of path
      is returned here.
  Returns:
    path with any volume name removed.
  Remarks:
    This function uses on_wsplitpath() to decide if the path begins with characters that
    could be a volume name. It does not inspect the file system to see if the volume exists.
  */
  static const ON_wString RemoveVolumeName(
    const wchar_t* path,
    ON_wString* volume_name
  );

  /*
  Description:
    Combine paths into a single valid path name. Remove internal .. and . 
    directory references. If necessary remove file names.
  Parameters:
    left_side - [in]
    bLeftSideContainsFileName - [in]
      true if left_side path ends in a file name and that
      file name is removed and discarded.
    right_side - [in]
    bRightSideContainsFileName - [in]
      true if right_side path ends in a file name.
      If bAppendTrailingDirectorySeparator is true, that file name is removed
      and discarded. If bAppendTrailingDirectorySeparator is false, the
      returned path ends in that file name.
    bAppendTrailingDirectorySeparator - [in]
      If true, any file names are removed and a directory separator
      is appended to the returned string.
  Returns:
    a path made left_side + right_side
  Remarks:
    This function manipulates string information. 
    This function does not look at storage media
    to see if the paths currently exist.
  */
  static const ON_wString CombinePaths(
    const wchar_t* left_side,
    bool bLeftSideContainsFileName,
    const wchar_t* right_side,
    bool bRightSideContainsFileName,
    bool bAppendTrailingDirectorySeparator
  );

  /// <summary>
  /// ON_FileSystemPath::PathId identifies a collection of commonly used directories.
  /// Use ON_FileSystemPath::PlatformPath() to get the name of the directory.
  /// </summary>
  enum class PathId : unsigned int
  {
    ///<summary>
    /// The current user's home directory.
    ///</summary>
    Unset = 0,

    ///<summary>
    /// The current user's desktop directory.
    ///</summary>
    DesktopDirectory = 1,

    ///<summary>
    /// The current user's documents directory.
    ///</summary>
    DocumentsDirectory = 2,

    ///<summary>
    /// The current user's downloads directory.
    ///</summary>
    DownloadsDirectory = 3,

    ///<summary>
    /// The current user's home directory.
    ///</summary>
    HomeDirectory = 4
  };

  /*
  Parameters:
    path_id - [in]
      Specifies path to get.
  Returns:
    Requested path. If the path does not exist in the current context, 
    the empty string is returned.
  */
  static const ON_wString PlatformPath(
    ON_FileSystemPath::PathId path_id
  );


  ON_DEPRECATED_MSG("Use ON_FileSystem::PathExists")
  static bool PathExists(
    const char* path
    );

  ON_DEPRECATED_MSG("Use ON_FileSystem::PathExists")
  static bool PathExists(
    const wchar_t* path
    );

  ON_DEPRECATED_MSG("Use ON_FileSystem::IsDirectory")
  static bool IsDirectory(
    const char* path
    );

  ON_DEPRECATED_MSG("Use ON_FileSystem::IsDirectory")
  static bool IsDirectory(
    const wchar_t* path
    );

  ON_DEPRECATED_MSG("Use ON_FileSystem::IsFile")
  static bool IsFile(
    const char* path
    );

  ON_DEPRECATED_MSG("Use ON_FileSystem::IsFile")
  static bool IsFile(
    const wchar_t* path
    );
};

class ON_CLASS ON_FileStream
{
public:
  /*
  Description:
    Portable wrapper for C runtime fopen().
  Parameters:
    filename - [in]
    mode - [in]
  Remarks:
    Use the ON_FileStream static functions for reading, writing, 
    seeking, position finding with the FILE pointer returned
    by this function.
  */
  static FILE* Open( const wchar_t* filename, const wchar_t* mode );

  /*
  Description:
    Portable wrapper for C runtime fopen().
  Parameters:
    filename - [in]
    mode - [in]
  Remarks:
    Use the ON_FileStream static functions for reading, writing, 
    seeking, position finding with the FILE pointer returned
    by this function.
  */
  static FILE* Open( const char* filename, const char* mode );

  /*
  Description:
    Portable wrapper for C runtime fclose().
  Parameters:
    fp - [in]
      FILE pointer returned by ON_FileStream::Open().
  Returns:
       0: successful
      -1: null fp parameter
    != 0: fclose() failure code
  */
  static int Close( FILE* fp );

  /*
  Returns:
    True if the file is a 3dm archive.
  */
  static bool Is3dmFile(
    const wchar_t* file_path,
    bool bAllow3dmbakExtension
  );

  /*
  Returns:
    True if the file is a 3dm archive.
  */
  static bool Is3dmFile(
    const char* file_path,
    bool bAllow3dmbakExtension
  );

  /*
  Description:
    Open the file and seek to the location where the 3dm archive information begins.
  Returns:
    A file stream with the current position at the beginning of the 3dm archive.
    nullptr if the file is not a 3dm archive.
  */
  static FILE* Open3dmToRead(
    const wchar_t* file_path
  );

  /*
  Description:
    Open the file and seek to the location where the 3dm archive information begins.
  Returns:
    A file stream with the current position at the beginning of the 3dm archive.
    nullptr if the file is not a 3dm archive.
  */
  static FILE* Open3dmToRead(
    const char* file_path
  );
  
  /*
  Description:
    Portable wrapper for C runtime ftell().
  Parameters:
    fp - [in]
      FILE pointer returned by ON_FileStream::Open().
  Returns:
    >= 0: current file position
      -1: an error occurred
  */
  static ON__INT64 CurrentPosition( FILE* fp );

  /*
  Description:
    Portable wrapper for C runtime fseek(fp,offset,SEEK_CUR).
  Parameters:
    fp - [in]
      FILE pointer returned by ON_FileStream::Open().
    offset - [in]
  */
  static bool SeekFromCurrentPosition( FILE* fp, ON__INT64 offset );

  /*
  Description:
    Portable wrapper for C runtime fseek(fp,offset,SEEK_SET).
  Parameters:
    fp - [in]
      FILE pointer returned by ON_FileStream::Open().
    offset - [in]
  */
  static bool SeekFromStart( FILE* fp, ON__INT64 offset );

  /*
  Description:
    Portable wrapper for C runtime fseek(fp,offset,SEEK_END).
  Parameters:
    fp - [in]
      FILE pointer returned by ON_FileStream::Open().
    offset - [in]
  */
  static bool SeekFromEnd( FILE* fp, ON__INT64 offset );

  /*
  Description:
    Portable wrapper for C runtime fseek(fp,offset,origin).
  Parameters:
    fp - [in]
      FILE pointer returned by ON_FileStream::Open().
    offset - [in]
    origin - [in]
      SEEK_SET (0): seek from beginning of file.  
      SEEK_CUR (1): seek from current position of file pointer.
      SEEK_END (2): seek from end of file.
  */
  static bool Seek( FILE* fp, ON__INT64 offset, int orgin );

  /*
  Description:
    Portable wrapper for C runtime fread(buffer,1,count,fp).
  Parameters:
    fp - [in]
      FILE pointer returned by ON_FileStream::Open()
    count - [in]
      number of bytes to read.
    buffer - [out]
      read bytes are stored in this buffer
  Returns:
    number of bytes read
  */
  static ON__UINT64 Read( FILE* fp, ON__UINT64 count, void* buffer );

  /*
  Description:
    Portable wrapper for C runtime fwrite(buffer,1,count,fp).
  Parameters:
    fp - [in]
      FILE pointer returned by ON_FileStream::Open()
    count - [in]
      number of bytes to write
    buffer - [in]
      data to be written
  Returns:
    number of bytes written.
  */
  static ON__UINT64 Write( FILE* fp, ON__UINT64 count, const void* buffer );

  /*
  Description:
    Portable wrapper for C runtime fflush(fp).
  Parameters:
    fp - [in]
      FILE pointer returned by ON_FileStream::Open().
  Returns:
    true if flush was successful.  False if an error occurred.
  */
  static bool Flush( FILE* fp );

  /*
  Description:
    Portable wrapper for C runtime fstat().
  Parameters:
    fp - [in]
      FILE pointer returned by ON_FileStream::Open().
    file_size - [out]
      If file_size is not null, the the size of the file
      in bytes returned here
    file_metadata_last_modified_time - [out]
      If file_metadata_last_modified_time is not null, then the time the 
      file's metadata (owner, permissions, ...) were last modified is returned
      here as the number of seconds since midnight January 1, 1970.
    file_contents_last_modified_time - [out]
      If file_contents_last_modified_time is not null, then the time the 
      file's contents were last modified is returned here as the number of
      seconds since midnight January 1, 1970.
  Returns:
    true if the query was successful.  False if an error occurred.
  */
  static bool GetFileInformation( 
    FILE* fp,
    ON__UINT64* file_size,
    ON__UINT64* file_metadata_last_modified_time,
    ON__UINT64* file_contents_last_modified_time
    );
  static bool GetFileInformation( 
    const wchar_t* file_name,
    ON__UINT64* file_size,
    ON__UINT64* file_metadata_last_modified_time,
    ON__UINT64* file_contents_last_modified_time
    );
  static bool GetFileInformation( 
    const char* file_name,
    ON__UINT64* file_size,
    ON__UINT64* file_metadata_last_modified_time,
    ON__UINT64* file_contents_last_modified_time
    );
};

class ON_CLASS ON_ContentHash
{
public:
  static const ON_ContentHash Unset;

public:
  ON_ContentHash() = default;
  ~ON_ContentHash() = default;
  ON_ContentHash(const ON_ContentHash&)  = default;
  ON_ContentHash& operator=(const ON_ContentHash&)  = default;

  /*
  Description:
    Create an ON_ContentHash class with the specified size, hash and times.
  Parameters:
    sha1_name_hash - [in]
      The SHA-1 hash of the name (typically a full path file name).
      When the content is identified by a file name in a file system,
      use ON_SHA1_Hash::FileSystemPathHash() to calculate this value.
    byte_count - [in] 
      number of bytes in the content.
    sha1_content_hash - [in]
      The SHA-1 hash of the content (typically a buffer or file).
      You may use ON_SHA1_Has::FileContentHash() or ON_SHA1_Hash::BufferContentHash()
      to calculate this value.
    hash_time - [in]
      The time the sha1_hash was calculated in seconds since January 1, 1970 UCT.
      If 0 is passed in, the current time is used.
    content_last_modified_time - [in]
      Pass 0 if not known.
      The time the hashed information that was last modified in seconds since January 1, 1970 UCT.
      If content_last_modified_time > hash_time, then 0 is used.
  Returns:
    An ON_ContentHash with size and SHA-1 hash and times set from the parameters,
  */
  static ON_ContentHash Create(
    ON_SHA1_Hash sha1_name_hash,
    ON__UINT64 byte_count,
    ON_SHA1_Hash sha1_content_hash,
    ON__UINT64 hash_time,
    ON__UINT64 content_last_modified_time
    );

  /*
  Description:
    Create an ON_ContentHash from a memory buffer.
  Parameters:
    sha1_name_hash - [in]
      A SHA-1 hash of the name associated with this content.
      If the buffer has no name, pass ON_SHA1_Hash::ZeroDigest.
      If the buffer has an empty name, pass ON_SHA1_Hash::EmptyContentHash.
    buffer - [in]  
    byte_count - [in] 
      number of bytes in buffer[]
  Returns:
    An ON_ContentHash with size and SHA-1 hash calculated from the parameters,
    hash time = now, and content last modified time = 0.
  */
  static ON_ContentHash CreateFromBuffer( 
    ON_SHA1_Hash sha1_name_hash,
    const void* buffer,
    size_t byte_count
   );

  /*
  Description:
    Create an ON_ContentHash from a file stream.
  Parameters:
    sha1_file_name_hash - [in]
      A SHA-1 hash of the file name associated with fp.
      Use ON_SHA1_Has::FileSystemPathHash() to create the value.
      If the name is not known, pass ON_SHA1_Hash::ZeroDigest.
    fp - [in] pointer to a file opened with ON:FileOpen(...,"rb")
  Returns:
    An ON_ContentHash with size and SHA-1 hash and times set from the file,
    hash time = now, and content last modified time set from the file system
    information returned by ON_FileStream::GetFileInformation().
  */
  static ON_ContentHash CreateFromFile( 
    ON_SHA1_Hash sha1_file_name_hash,
    FILE* fp
    );

  /*
  Description:
    Create an ON_ContentHash from a file stream.
  Parameters:
    filename - [in] name of file.
  Returns:
    An ON_ContentHash with size and SHA-1 hash and times set from the file,
    hash time = now, and content last modified time set from the file system
    information returned by ON_FileStream::GetFileInformation().
  */
  static ON_ContentHash CreateFromFile( 
    const wchar_t* filename
    );

  static ON_ContentHash CreateFromFile( 
    const char* filename
    );

  class ON_CLASS Cache
  {
  public:
    Cache();
    ~Cache();

    static const ON_ContentHash* FromFile(const wchar_t*);
    static const ON_ContentHash* FromFile(const char*);

    static void Add(const wchar_t*, const ON_ContentHash&);
    static void Add(const char*, const ON_ContentHash&);

  private:
    class Private;
    Private* m_private;
  };

  /*
  Returns:
    True if the SHA-1 hash has been set.
  */
  bool IsSet() const;

  /*
  Returns:
    True if the SHA-1 hash is not set.
  */
  bool IsNotSet() const;

  /*
  Returns:
    Number of bytes in the content (typically a file or buffer).
  */
  ON__UINT64 ByteCount() const;

  /*
  Returns:
    Time the hash SHA-1 hash was calculated in seconds since January 1, 1970 UCT.
  */
  ON__UINT64 HashCalculationTime() const;

  /*
  Returns:
    Time the hashed content was last modified in seconds since January 1, 1970 UCT.
    0 is returned if this time is not known.

    This time should be used for important decisions as a last resort.
    
    When hash values differ, this time may be considered to
    which content is newer (or most recently copied).  

    Unfortunately, in many cases this time is often unknown and incorrectly set.
    For example, some file systems set the last modified time of a copy of 
    an "old" file to the time the copy was created.  Thus a copy of "old" content 
    may appear to be newer than "new" content that has not been copied.  
  */
  ON__UINT64 ContentLastModifiedTime() const;

  /*
  Returns:
    SHA-1 hash of the name (typically a full path file name).
  */
  ON_SHA1_Hash NameHash() const;

  /*
  Returns:
    SHA-1 hash of the content (typically a buffer or file).
  */
  ON_SHA1_Hash ContentHash() const;
  
  /*
  Description:
    Test a buffer to see if it has a matching size and SHA-1 hash.
  Parameters:
    buffer - [in]  
    byte_count - [in] 
      number of bytes in buffer[]
  Returns:
    True if the buffer has a matching byte_count and SHA-1 hash.
  */
  bool IsSameBufferContent( 
    const void* buffer,
    size_t byte_count
    ) const;

  /*
  Description:
    Test a file to see if it has a matching size and SHA-1 hash.
  Parameters:
    fp - [in] pointer to file opened with ON::OpenFile(...,"rb")
    bSkipTimeCheck - [in] if true, the time of last
       modification is not checked.
  Returns:
    True if the file exists, can be read, and has a matching byte_count
    and SHA-1 hash.
  */
  bool IsSameFileContent( 
    FILE* fp
    ) const;

  /*
  Description:
    Test a file to see if it has a matching size and SHA-1 content hash.
  Parameters:
    filename - [in]
  Returns:
    True if the file exists, can be read, and has a matching byte_count
    and SHA-1 content hash.
  */
  bool IsSameFileContent( 
    const wchar_t* filename
    ) const;

  bool IsSameFileContent( 
    const char* filename
    ) const;

  /// <summary>
  /// ON_ContentHash::Compare are the possible results of calling ON_ContentHash::CompareFile().
  /// </summary>
  enum class CompareResult : unsigned char
  {
    /// <summary>
    /// Not set. This value is never returned by ON_ContentHash::CheckFile().
    /// </summary>
    Unset = 0,

    /// <summary>
    /// File exists and its size and content matches the information 
    /// used to set the content hash.
    /// </summary>
    EqualContent = 1,
    
    /// <summary>
    /// File exists and its size or content differs from the information 
    /// used to set the content hash.  Unable to reliably determine which
    /// is newer.
    /// </summary>
    DifferentContent = 2,  

    /// <summary>
    /// File exists and its size or content differs from the information 
    /// used to set the content hash. The file's last modified time
    /// is older than ContentLastModifiedTime().
    /// </summary>
    DifferentContentFileIsOlder = 3,

    /// <summary>
    /// File exists and its size or content differs from the information 
    /// used to set the content hash. The file's last modified time
    /// is newer than ContentLastModifiedTime().
    /// </summary>
    ContentDifferentFileIsNewer = 4,

    /// <summary>
    /// File does not exist.
    /// </summary>
    FileDoesNotExist = 5,

    /// <summary>
    /// File cannot be opened, read, or some other file system issue prevents checking.
    /// </summary>
    FileSystemFailure = 6
  };

  static ON_ContentHash::CompareResult CompareResultFromUnsigned(
    unsigned int compare_result_as_unsigned
    );

  /*
  Description:
    Compare the information used to set this content hash with 
    the contents of the file.
  Parameters:
    file_path - [in]
  bFastCompare - [in]
    If bFastCompare is true and the file_path, create time, last modified time, and size
    exactly match the values in ON_ContentHash, then
    ON_ContentHash::CompareResult::EqualContent is returned
    without performing the expensive SHA1 test on the file's content.
    If bFastCompare is false, the SHA-1 hash of the file's content will be 
    calculated and compared before ON_ContentHash::CompareResult::EqualContent
    is returned.
  Returns:
    Result of compare test as a ON_ContentHash::CompareResult enum.
    ON_ContentHash::CompareResult::DifferentContentFileIsOlder means file_path content is different and older than "this".
    ON_ContentHash::CompareResult::DifferentContentFileIsNewer means file_path content is different and newer than "this".
  */
  ON_ContentHash::CompareResult Compare(
    const wchar_t* file_path,
    bool bFastTest
    ) const;

  /*
  Description:
    Compare the byte count and SHA-1 content hash.
  Parameters:
    file_content_hash - [in]
      ON_ContentHash to compare against this one.
  Returns:
    Result of compare test as a ON_ContentHash::CompareResult enum.
    ON_ContentHash::CompareResult::DifferentContentFileIsOlder means file_content_hash is different and older than "this".
    ON_ContentHash::CompareResult::DifferentContentFileIsNewer means file_content_hash is different and newer than "this".
  */
  ON_ContentHash::CompareResult Compare(
    ON_ContentHash file_content_hash
    ) const;

  /*
  Returns:
    true if a and b have identical ByteCount() and SHA-1 content hash values.
  */
  static bool EqualContent(
    const ON_ContentHash& a,
    const ON_ContentHash& b
    );

  /*
  Returns:
    true if a and b have different ByteCount() or SHA-1 content hash values.
  */
  static bool DifferentContent(
    const ON_ContentHash& a,
    const ON_ContentHash& b
    );


  /*
  Description:
    Compares content byte count and content SHA-1
  */
  static int CompareContent(
    const ON_ContentHash& a,
    const ON_ContentHash& b
    );

  /*
  Description:
    Compares all fields
  */
  static int Compare(
    const ON_ContentHash& a,
    const ON_ContentHash& b
    );

  /*
  Parameters:
    filename - [in]
  Returns:
    True if the file exists, has size > 0, has the same name, same size, and same last modified time
    than this content hash.
    False otherwise.
  Remarks:
    Faster than the ON_ContentHash::EqualContent() and reliable if this content
    hash was set on the same file system.
    Unreliable if the file system does not correctly set last modified times
    or the file was modified less than 2 seconds before the call.
  */
  bool EqualFileNameSizeAndTime(
    const wchar_t* filename
    ) const;

  bool Write(
  class ON_BinaryArchive& archive
    ) const;

  bool Read(
  class ON_BinaryArchive& archive
    );

  void Dump(
    class ON_TextLog& text_log
    ) const;

private:
  // Number of bytes in the buffer or file
  ON__UINT64 m_byte_count = 0;

  // Time this hash was set (always > 0 if this ON_ContentHash is set).
  ON__UINT64 m_hash_time = 0; // number of seconds since Jan 1, 1970, UCT

  // Time the content was last modified.
  // This time is often unknown, or set incorrectly.
  ON__UINT64 m_content_time = 0; // number of seconds since Jan 1, 1970, UCT

  // SHA-1 hash of the content name (file name or other assigned name)
  ON_SHA1_Hash  m_sha1_name_hash = ON_SHA1_Hash::ZeroDigest;

  // SHA-1 hash of the content (buffer or file).
  ON_SHA1_Hash  m_sha1_content_hash = ON_SHA1_Hash::ZeroDigest;
};

class ON_CLASS ON_FileReference
{
public:
  static const ON_FileReference Unset;

#pragma region RH_C_SHARED_ENUM [ON_FileReference::Status] [Rhino.FileIO.FileReferenceStatus] [int]
  ///<summary>Enumerates a list of file statuses.</summary>
  enum class Status : unsigned int
  {
    /// <summary>
    /// Status of a the full path is not known.
    /// </summary>
    Unknown = 0,

    /// <summary>
    /// Full path is valid.
    /// </summary>
    FullPathValid = 1,

    /// <summary>
    /// Unable to locate file.
    /// </summary>
    FileNotFound = 2 
  };
#pragma endregion

  static int Compare(
    const ON_FileReference& a,
    const ON_FileReference& b
    );

  static ON_FileReference::Status StatusFromUnsigned(
    unsigned int full_path_status_as_unsigned
    );

  ON_FileReference() = default;
  ~ON_FileReference() = default;
  ON_FileReference(const ON_FileReference&) = default;
  ON_FileReference& operator=(const ON_FileReference&) = default;

  ON_FileReference(
    const wchar_t* full_path,
    const wchar_t* relative_path,
    ON_ContentHash content_hash,
    ON_FileReference::Status full_path_status
    );

  static ON_FileReference CreateFromFullPath(
    const wchar_t* full_path,
    bool bSetContentHash,
    bool bSetFullPathStatus
    );

#pragma region RH_C_SHARED_ENUM [ON_FileReference::FindFilePreference] [Rhino.FileIO.FileFindPreference] [int]
  ///<summary>Defines options for file search.</summary>
  enum class FindFilePreference : unsigned char
  {
    ///<summary>The choice is not defined.</summary>
    None = 0,

    ///<summary>File name exists in FullPath().</summary>
    FullPath = 1,

    ///<summary>File name exists in base path + RelativePath().</summary>
    RelativePath = 2,

    ///<summary>File name exists in base path directory.</summary>
    BasePath = 3,

    ///<summary>File with matching content exists.</summary>
    ContentMatch = 4,

    ///<summary>Most recently modified file.</summary>
    MostRecent = 5
  };
#pragma endregion

  /*
  Description:
    Uses the full path, relative path and parameter information to find a
    full path to a file that exists.
  Parameters:
    base_path - [in]
      If base_path and RelativePath() are not empty, then path base_path+RelativePath().
      If base_path is not empty, then base_path + filename is considered.
    bBasePathIncludesFileName - [in]
      True if base_path contains a file name that must be removed to get a directory path.
    first_choice - [in]
      When multiple files are found in different locations, the first_choice, second_choice,
      third_choice, forth_choice, and fifth_choice parameters are used to select which file
      is returned.
    second_choice - [in]
      When multiple files are found in different locations, the first_choice, second_choice,
      third_choice, forth_choice, and fifth_choice parameters are used to select which file
      is returned.
    third_choice - [in]
      When multiple files are found in different locations, the first_choice, second_choice,
      third_choice, forth_choice, and fifth_choice parameters are used to select which file
      is returned.
    forth_choice - [in]
      When multiple files are found in different locations, the first_choice, second_choice,
      third_choice, forth_choice, and fifth_choice parameters are used to select which file
      is returned.
    fifth_choice - [in]
      When multiple files are found in different locations, the first_choice, second_choice,
      third_choice, forth_choice, and fifth_choice parameters are used to select which file
      is returned.
    full_path - [out]
      A full path to a file that exists.
      If FullPath() and base_path+RelativePath() resolve to different files, 
      the content hash information is used to select the file.
  Returns:
    If the file is found, then the returned ON_FileReference::FindFilePreference enum value
    indicates why it was selected.
    If the file is not found, then ON_FileReference::FindFilePreference::None is returned
    and full_path is empty.
  Remarks:
    The locations FullPath(), base_path+RelativePath(), and base_path+FileName() are tested.
    If multiple files are found, first_choice, second_choice, third_choice, forth_choice,
    and fifth_choice are used to select which file is returned.
  */
  ON_FileReference::FindFilePreference FindFile(
    const wchar_t* base_path,
    bool bBasePathIncludesFileName,
    ON_FileReference::FindFilePreference first_choice,
    ON_FileReference::FindFilePreference second_choice,
    ON_FileReference::FindFilePreference third_choice,
    ON_FileReference::FindFilePreference forth_choice,
    ON_FileReference::FindFilePreference fifth_choice,
    ON_wString& found_file_full_path
    ) const;

  /*
  Description:
    Uses the full path, relative path and parameter information to find a
    full path to a file that exists.
  Parameters:
    base_path - [in]
      If base_path and RelativePath() are not empty, then path base_path+RelativePath().
      If base_path is not empty, then base_path + filename is considered.
    bBasePathIncludesFileName - [in]
      True if base_path contains a file name that must be removed to get a directory path.
  Returns:
    If the file is found, then the returned ON_FileReference::FindFilePreference enum value
    indicates why it was selected.
    If the file is not found, then ON_FileReference::FindFilePreference::None is returned
    and full_path is empty.
  Remarks:
    The locations FullPath(), base_path+RelativePath(), and base_path+FileName() are tested.
    If multiple files are found, the returned file is selected in the order
    relative path, full path, content match, base path and most recently modified.
    If you prefer a different order, use the version of ON_FileReference::FindFile
    with 5 ON_FileReference::FindFilePreference parameters.
  */
  ON_FileReference::FindFilePreference FindFile(
    const wchar_t* base_path,
    bool bBasePathIncludesFileName,
    ON_wString& found_file_full_path
    ) const;

  /*
  Description:
    The search for the file is identical to the one performed by find file.
    If a file is found, the full path setting in this reference is updated.
  */
  ON_FileReference::FindFilePreference FindFileAndUpdateReference(
    const wchar_t* base_path,
    bool bBasePathIncludesFileName,
    ON_FileReference::FindFilePreference first_choice,
    ON_FileReference::FindFilePreference second_choice,
    ON_FileReference::FindFilePreference third_choice,
    ON_FileReference::FindFilePreference forth_choice,
    ON_FileReference::FindFilePreference fifth_choice,
    bool bUpdateContentHash,
    ON_wString& found_file_full_path
    );

  /*
  Description:
    The search for the file is identical to the one performed by find file.
    If a file is found, the full path setting in this reference is updated.
  */
  ON_FileReference::FindFilePreference FindFileAndUpdateReference(
    const wchar_t* base_path,
    bool bBasePathIncludesFileName,
    bool bUpdateContentHash,
    ON_wString& found_file_full_path
    );

  ON_FileReference::FindFilePreference FindFileAndUpdateReference(
    const wchar_t* base_path,
    bool bBasePathIncludesFileName,
    bool bUpdateContentHash
    );

  /*
  Returns:
    True if FullPath() is not empty.
  */
  bool IsSet() const;

  /*
  Returns:
    True if FullPath() is empty.
  */
  bool IsNotSet() const;

  /*
  Parameters:
    bUseArchiveBasePath - [in]
      If bUseArchiveBasePath is true and a file is being written, then the
      base path of the file being written use used as the base path to
      calculate the relative path.
      If bUseArchiveBasePath is false, then the current value of RelativePath() 
      is saved in the archive.
  */
  bool Write(
    bool bUseArchiveDirectoryAsBasePath,
    ON_BinaryArchive& archive
    ) const;

  /*
  Parameters:
    base_path - [in]
      If base_path is not empty, then the relative path saved
      in the archive will be calculated from FullPath() and base_path.
      If base_path is nullptr or empty, then RelativePath() is saved in
      the archive.
  */
  bool Write(
    const wchar_t* base_path,
    bool bBasePathIncludesFileName,
    ON_BinaryArchive& archive
    ) const;

  /*
  Remarks:
    Calling Read() sets m_full_path_status = ON_FileReference::Status::Unknown,
    even if that was not the status when Write() was called.
  */
  bool Read(
    ON_BinaryArchive& archive
    );

  void Dump(
    class ON_TextLog& text_log
    ) const;

  unsigned int SizeOf() const;

  const ON_wString& FullPath() const;
  const wchar_t* FullPathAsPointer() const;
  void SetFullPath(
    const wchar_t* full_path,
    bool bSetContentHash
    );
  void SetFullPath(
    const char* full_path,
    bool bSetContentHash
    );
  void ClearFullPath();
  
  const ON_wString& RelativePath() const;
  const wchar_t* RelativePathAsPointer() const;
  void SetRelativePath(
    const wchar_t* relative_path
    );
  void SetRelativePath(
    const char* relative_path
    );
  void SetRelativePathFromBasePath(
    const wchar_t* base_path,
    bool bBasePathContainsFileName
    );
  void SetRelativePathFromBasePath(
    const char* base_path,
    bool bBasePathContainsFileName
    );
  void ClearRelativePath();

  /*
  Returns:
    File content hash. This value is persistent, saved in 3dm archive,
    and could have been calculated a long time ago on a different computer.
  */
  const ON_ContentHash& ContentHash() const;
  void SetContentHash(
    ON_ContentHash content_hash
    );
  void ClearContentHash();

  bool UpdateContentHash();

  /*
  Returns:
  Parameters:
    recent_time - [in]
      The time, in number of seconds since January 1, 1970 UTC, to use
      when deciding what content hashes can be considered recent.
      If recent_time is 0 or in the future, then the current value of
      ON_SecondsSinceJanOne1970UTC() is used.
      Typically this parameter is the value of ON_SecondsSinceJanOne1970UTC()
      at the beginning of a calculation durint which any referenced files will
      not be changed.      
  Returns:
    A file content hash value calculated on or after a specified time in the current
    instance of the application. This value is used to detect changed files
    in the current instance of the application. It is cached for performance reasons.
    This value is never saved in 3dm files.
  */
  const ON_ContentHash& RecentContentHash(
    ON__UINT64 recent_time
  ) const;

  /*
  Returns:
    ON_SHA1_Hash::FileSystemPathHash(FullPath());
  Remarks:
    The value of the hash is saved in a runtime cache so
    using this function when comparing paths is efficient
    when multiple compares are required.
  See Also:
    ON_NameHash::CreateFilePathHash( ON_FileReference& file_reference );
  */
  const ON_SHA1_Hash& FullPathHash() const;

  ON_FileReference::Status FullPathStatus() const;
  void SetFullPathStatus(
    ON_FileReference::Status full_path_status
    );

  ON_UUID EmbeddedFileId() const;
  void SetEmbeddedFileId(
    ON_UUID embedded_file_id
    );

private:
  ON_wString m_full_path;
  ON_wString m_relative_path;

  // If the referenced file is saved in the model as an embedded file,
  // the ON_BinaryArchive read code sets m_embedded_file_id
  // at read time.
  mutable ON_UUID m_embedded_file_id = ON_nil_uuid;

  // file content hash. Can be calculated long ago, on a different computer,
  // and is saved in 3dm archived.
  ON_ContentHash m_content_hash; // File content hash.

  mutable ON_ContentHash m_recent_content_hash;

  // m_full_path_hash is cached runtime information. The value is not saved
  // in .3dm archives. It is calculated on demand.
  mutable ON_SHA1_Hash m_full_path_hash = ON_SHA1_Hash::EmptyContentHash; // File path hash.

  ON_FileReference::Status m_full_path_status = ON_FileReference::Status::Unknown;

private:
  ON_FileReference::FindFilePreference Internal_FindFile(
    const wchar_t* base_path,
    bool bBasePathIncludesFileName,
    const ON_FileReference::FindFilePreference* file_preference,
    unsigned int file_preference_count,
    ON_wString& found_file_full_path,
    ON_ContentHash* found_file_content_hash
    ) const;
};

/*
Description:
  Iterates through every item in a file system directory.
*/
class ON_CLASS ON_FileIterator
{
public:
  ON_FileIterator() = default;
  ~ON_FileIterator();

private:
  ON_FileIterator(const ON_FileIterator&) = delete;
  ON_FileIterator& operator=(const ON_FileIterator&) = delete;

public:

  //////////////////////////////////////////////////////////////////////////////////
  //
  // Iteration initialization tools
  //
  /*
  Description:
    Initialize where the search should occur.
  Parameters:
    directory_name - [in]
      The directory to look in.
    item_name_filter - [in]
      If this parameter is null, then the iteration
      includes all names in the directory.
      The item name to search for. This parameter can 
      include wildcard characters, such as an
      asterisk (*) or a question mark (?). For example,
      "\rootdir\subdir\*.*"  will iterate all files in
      the \rootdir\subdir\ directory.

  Returns:
    true:
      The iterator is set to the first item.
    false:
      There are no matching items.

  Remarks:
    Calling FirstItem() is equivalent to calling Initialize() and then calling NextItem().
  */
  bool Initialize( 
    const wchar_t* directory_name
    );
  bool Initialize( 
    const wchar_t* directory_name, 
    const wchar_t* item_name_filter
    );
  bool Initialize( 
    const char* directory_name
    );
  bool Initialize( 
    const char* directory_name, 
    const char* item_name_filter
    );

  //////////////////////////////////////////////////////////////////////////////////
  //
  // Iteration tools
  //

  /*
  Description:
    Find the first matching item in the directory.
  Example:
          // Iterate through the files in a directory named "\rootdir\subdir"
          ON_FileIterator fit;
          fit.Initialize("\\rootdir\\subdir");
          for ( bool bHaveItem = fit.FirstItem(); bHaveItem; bHaveItem = fit.NextItem() )
          {
            if ( fit.CurrentFileIsDirectory() )
              continue;
            ON_String fullpath = fit.CurrentItemFullPathName();
            FILE* fp = ON_FileStream::Open(fullpath,"rb");
            if ( 0 == fp )
            {
              continue;
            }
            ...
            ON_FileStream::Close(fp);
            fp = 0;
          }
        }

  Returns:
    true:
      The iterator is set to the first item.
    false:
      There are no matching items.
  */
  bool FirstItem(); 

  /*
  Description:
    Find the next matching item in the directory.
  Returns:
    true:
      The iterator was advanced to the next item.
    false:
      There are no more matching items.
  */
  bool NextItem();

  /*
  Description:
    Reset this ON_FileIterator so it can be used again.
  */
  void Reset();

  //////////////////////////////////////////////////////////////////////////////////
  //
  // Current item query
  //

  /*
  Returns:
    Current file or directory name in the directory being iterated.
    Use CurrentFullPathItemName() to get the full path name.
  */
  const ON_wString CurrentItemName() const;

  /*
  Returns:
    The name of the directory being iterated.
  */
  const ON_wString DirectoryName() const;

  /*
  Returns:
    If the current item is a file, then the size of the file in bytes is returned.
    If the current item is a directory, then 0 is returned.
  */
  ON__UINT64 CurrentItemSize() const;

  /*
  Returns 
    true if the current item is a directory.
  */
  bool CurrentItemIsDirectory() const;

  /*
  Returns 
    true if the current item is a file.
  */
  bool CurrentItemIsFile() const;

  /*
  Returns 
    true if the current file or directory is hidden.
    This means its name begins with a '.' or it's
    Windows hidden attribute is true.
  */
  bool CurrentItemIsHidden() const;

  const ON_wString CurrentItemFullPathName() const;

  /*
  Returns:
    File last modified time in seconds since January 1, 1970
  Remarks:
    The times returned by ON_FileIterator can differ from the time
    returned by ON_FileStream::GetFileInformation().
  */
  ON__UINT64 CurrentItemLastModifiedTime() const;

  /*
  Returns:
    Number of matching items iterated through.
  */
  ON__UINT64 CurrentItemCount() const;

private:
  ON__UINT32 m_state = 0; // 0 unset, 1=initialized, 2 = iteration in progress. 3 = iteration finished.
  ON__UINT32 m_reserved = 0;

  ON_wString m_directory; // directory passed to Initialize() or FirstItem
  ON_wString m_item_name_filter; // item_name_filter passed to Initialize() or FirstItem
  ON_wString m_item_name; // Current item name.

  // cached full path name 
  //   m_directory + directory separator + m_item_name
  //  (length = 0 if it is not set)
  mutable ON_wString m_full_path_name;

  ON__UINT64 m_count = 0; // number of items iterated through so far
  class ON_DirectoryIteratorImpl* m_impl = nullptr;
};

class ON_CLASS ON_UnicodeTextFile final
{
public:
  enum class Modes { Read, Write };
  enum class Types { Unknown, UTF8, UTF16 };

  ON_UnicodeTextFile(Types type = Types::Unknown);
  ~ON_UnicodeTextFile();

  bool Open(const wchar_t* filename, Modes mode);
  bool Close(void);

  bool ReadString(ON_wString& s);
  bool WriteString(const wchar_t* s);

  ON_UnicodeTextFile(const ON_UnicodeTextFile&) = delete;
  const ON_UnicodeTextFile& operator = (const ON_UnicodeTextFile&) = delete;

private:
  class ON_UnicodeTextFilePrivate* _private;
};

#endif
