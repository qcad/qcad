//
// Copyright (c) 1993-2012 Robert McNeel & Associates. All rights reserved.
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

// obsolete V5 dimension style
#include "opennurbs_internal_V5_dimstyle.h"

// obsolete V2 and V5 annotation objects
#include "opennurbs_internal_V2_annotation.h"
#include "opennurbs_internal_V5_annotation.h"

const ON_String Internal_RuntimeEnvironmentToString(
  ON::RuntimeEnvironment runtime_environment
)
{
  switch (runtime_environment)
  {
  ON_ENUM_TO_STRING_CASE(ON::RuntimeEnvironment::Unset);
  ON_ENUM_TO_STRING_CASE(ON::RuntimeEnvironment::None);
  ON_ENUM_TO_STRING_CASE(ON::RuntimeEnvironment::Windows);
  ON_ENUM_TO_STRING_CASE(ON::RuntimeEnvironment::Apple);
  ON_ENUM_TO_STRING_CASE(ON::RuntimeEnvironment::Android);
  ON_ENUM_TO_STRING_CASE(ON::RuntimeEnvironment::Linux);
  ON_ENUM_TO_STRING_CASE(ON::RuntimeEnvironment::WebAssembly);
  }

  ON_ERROR("Invalid runtime_environment parameter value.");
  return ON_String::EmptyString;
}

const ON_wString Internal_RuntimeEnvironmentToWideString(
  ON::RuntimeEnvironment runtime_environment
)
{
  const ON_String s = Internal_RuntimeEnvironmentToString(runtime_environment);
  return ON_wString(s);
}

unsigned int ON_BinaryArchive::ArchiveOpenNURBSVersionToWrite(
  unsigned int archive_3dm_version,
  unsigned int opennurbs_version
  )
{
  // When writing V5 files, any version number in the new V6 format needs to be
  // converted to the old V5 format

  unsigned int opennurbs_version_to_write = opennurbs_version;
  if (
    ((archive_3dm_version >= 2 && archive_3dm_version <= 4) || (50 == archive_3dm_version))
    && false == ON_VersionNumberIsYearMonthDateFormat(archive_3dm_version, opennurbs_version)
    )
  {
    unsigned int yyyy = 0;
    unsigned int mm = 0;
    unsigned int dd = 0;
    unsigned int major_version_number = 0;
    if (ON_VersionNumberParse(opennurbs_version, &major_version_number, 0, &yyyy, &mm, &dd, 0))
    {
      unsigned int n = major_version_number < 10 ? major_version_number : 9;
      opennurbs_version_to_write = ((yyyy * 100 + mm) * 100 + dd) * 10 + n;
    }
  }
  return opennurbs_version_to_write;
}

ON_UserDataItemFilter::ON_UserDataItemFilter()
  : m_application_id(ON_nil_uuid)
  , m_item_id(ON_nil_uuid)
  , m_precedence(0)
  , m_bSerialize(false)
{}

ON_UserDataItemFilter::ON_UserDataItemFilter(
  ON_UUID application_id,
  bool bSerialize
  )
  : m_application_id(application_id)
  , m_item_id(ON_nil_uuid)
  , m_precedence(0)
  , m_bSerialize(bSerialize ? true : false)
{}

ON_UserDataItemFilter::ON_UserDataItemFilter(
  ON_UUID application_id,
  ON_UUID item_id,
  bool bSerialize
  )
: m_application_id(application_id)
, m_item_id(item_id)
, m_precedence(0)
, m_bSerialize(bSerialize ? true : false)
{}

int ON_UserDataItemFilter::Compare(
  const class ON_UserDataItemFilter* a,
  const class ON_UserDataItemFilter* b
  )
{
  // null pointer handling
  if (a == b)
    return 0; 
  if (0 == b)
    return -1; // non-null < null
  if (0 == a)
    return 1;

  int rc = ON_UuidCompare(a->m_application_id, b->m_application_id);
  if (0 != rc)
    return rc;

  rc = ON_UuidCompare(a->m_item_id, b->m_item_id);
  if (0 != rc)
    return rc;

  if (a->m_precedence < b->m_precedence)
    return -1;
  if (b->m_precedence < a->m_precedence)
    return 1;
  
  rc = ((int)(a->m_bSerialize ? 1 : 0)) - ((int)(a->m_bSerialize ? 1 : 0));

  return rc;
}



class ON_ReadChunkHelper
{
public:
  /*
  Parameters:
    archive - [in]
    bReadSuccess - [out]
      The value of *bReadSuccess is set to false if an error
      occurs.  Otherwise the value of *bReadSuccess is not
      changed.
  */
  ON_ReadChunkHelper(
    ON_BinaryArchive&,
    bool& bReadSuccess
    );
  ~ON_ReadChunkHelper();

  ON_BinaryArchive& m_binary_archive;
  ON__UINT32 m_chunk_tcode = 0;
  bool m_bSupressPartiallyReadChunkWarning = false;
  ON__INT64 m_chunk_value = 0;
  bool& m_bReadSuccess;

private:
  bool m_bCallEndRead3dmChunk = false;

private:
  // prohibit use - no implementation
  ON_ReadChunkHelper() = delete;
  ON_ReadChunkHelper(const ON_ReadChunkHelper&) = delete;
  ON_ReadChunkHelper& operator=(const ON_ReadChunkHelper&) = delete;
};

ON_ReadChunkHelper::ON_ReadChunkHelper(
  ON_BinaryArchive& binary_archive,
  bool &bReadSuccess
  )
: m_binary_archive(binary_archive)
, m_bReadSuccess(bReadSuccess)
{
  m_bCallEndRead3dmChunk = m_binary_archive.BeginRead3dmBigChunk(&m_chunk_tcode,&m_chunk_value);
  if ( false == m_bCallEndRead3dmChunk || 0 ==  m_chunk_tcode )
  {
    // RH-22447 - valid chunk typecodes are never zero
    m_bReadSuccess = false; 
  }  
}

ON_ReadChunkHelper::~ON_ReadChunkHelper()
{
  if (m_bCallEndRead3dmChunk)
  {
    if ( !m_binary_archive.EndRead3dmChunk(m_bSupressPartiallyReadChunkWarning) )
    {
      m_bReadSuccess = false;
    }
  }
}

bool ON_IsUnsignedChunkTypecode( ON__UINT32 typecode )
{
  // returns tru if the chunk value should be treated as an unsigned int.
  return ( 0 == (TCODE_SHORT & typecode)
           || TCODE_RGB == typecode 
           || TCODE_RGBDISPLAY == typecode
           || TCODE_PROPERTIES_OPENNURBS_VERSION == typecode
           || TCODE_OBJECT_RECORD_TYPE == typecode
         );
}

bool ON_IsLongChunkTypecode(ON__UINT32 typecode)
{
  // NOTE: RenderXXXX plug-in used zero as a typecode in material userdata, sigh ...
  //return (0 != typecode && 0 == (TCODE_SHORT & typecode));
  return (0 == (TCODE_SHORT & typecode));
}

bool ON_IsShortChunkTypecode(ON__UINT32 typecode)
{
  return (0 != (TCODE_SHORT & typecode));
}

static
bool DownSizeINT( ON__INT64 i64, ON__INT32* i32 )
{
  const static ON__INT64 i32max = 2147483647;
  if ( i64 <= i32max && i64 >= (-i32max - 1) )
  {
    *i32 = (ON__INT32)i64;
    return true;
  }

  ON_ERROR("i64 too big to convert to 4 byte signed int");
  *i32 = 0;
  return false;
}

static
bool DownSizeUINT( ON__UINT64 u64, ON__UINT32* u32 )
{
  if ( u64 <= 0xFFFFFFFF )
  {
    *u32 = (ON__UINT32)u64;
    return true;
  }

  ON_ERROR("u64 too big to convert to 4 byte unsigned int");
  *u32 = 0;
  return false;
}

struct ON__3dmV1LayerIndex
{
  int m_layer_index;
  int m_layer_name_length;
  char* m_layer_name;
  struct ON__3dmV1LayerIndex* m_next;
};

ON_BinaryArchive::ON_BinaryArchive( ON::archive_mode mode )
  : m_mode(mode)
{
  if (ON::archive_mode::read3dm == mode || ON::archive_mode::write3dm == mode)
    m_bChunkBoundaryCheck = true;
  m_annotation_context.SetReferencedBinaryArchive(this);
}

class ON_3dmTableStatusLink
{
public:
  ON_3dmTableStatusLink() = default;
  ~ON_3dmTableStatusLink() = default;
  ON_3dmTableStatusLink(const ON_3dmTableStatusLink&) = default;
  ON_3dmTableStatusLink& operator=(const ON_3dmTableStatusLink&) = default;

  ON_3dmTableStatusLink* m_next = nullptr;
  ON_3dmArchiveTableStatus m_table_status;
};

ON_BinaryArchive::~ON_BinaryArchive()
{
  if ( 0 != m_V1_layer_list )
  {
    struct ON__3dmV1LayerIndex* next = m_V1_layer_list;
    m_V1_layer_list = 0;
    for ( int i = 0; 0 != next && i < 1000; i++ )
    {
      struct ON__3dmV1LayerIndex* p = next;
      next = p->m_next;
      onfree(p);
    }
  }

  if (nullptr != m_compressor)
  {
    CompressionEnd();
    onfree(m_compressor);
  }

  ON_3dmTableStatusLink* next = m_3dm_table_status_list;
  m_3dm_table_status_list = nullptr;
  while (nullptr != next)
  {
    ON_3dmTableStatusLink* p = next;
    next = const_cast<ON_3dmTableStatusLink*>(next->m_next);
    delete p;
  }

  m_annotation_context.SetReferencedDimStyle(nullptr,nullptr,ON_UNSET_INT_INDEX);

  if (nullptr != m_archive_3dm_properties)
  {
    delete m_archive_3dm_properties;
    m_archive_3dm_properties = nullptr;
  }

  if (nullptr != m_archive_3dm_settings)
  {
    delete m_archive_3dm_settings;
    m_archive_3dm_settings = nullptr;
  }

  for (int i = 0; i < m_archive_text_style_table.Count(); i++)
  {
    if (nullptr != m_archive_text_style_table[i])
      delete m_archive_text_style_table[i];
  }
  m_archive_text_style_table.Destroy();

  for (int i = 0; i < m_archive_dim_style_table.Count(); i++)
  {
    if (nullptr != m_archive_dim_style_table[i])
      delete m_archive_dim_style_table[i];
  }
  m_archive_dim_style_table.Destroy();
}

bool ON_BinaryArchive::ArchiveFileMoved() const
{
  return m_b3dmArchiveMoved;
}

const ON_wString& ON_BinaryArchive::ArchiveFileName() const
{
  return m_archive_file_name;
}

const ON_wString& ON_BinaryArchive::ArchiveDirectoryName() const
{
  return m_archive_directory_name;
}

const ON_wString& ON_BinaryArchive::ArchiveFullPath() const
{
  return m_archive_full_path;
}

const ON_wString& ON_BinaryArchive::ArchiveSavedAsFullPath() const
{
  return m_archive_saved_as_full_path;
}

const wchar_t* ON_BinaryArchive::ArchiveFileNameAsPointer() const
{
  return static_cast<const wchar_t*>(m_archive_file_name);
}

const wchar_t* ON_BinaryArchive::ArchiveDirectoryNameAsPointer() const
{
  return static_cast<const wchar_t*>(m_archive_directory_name);
}

const wchar_t* ON_BinaryArchive::ArchiveFullPathAsPointer() const
{
  return static_cast<const wchar_t*>(m_archive_full_path);
}

const wchar_t* ON_BinaryArchive::ArchiveSavedAsFullPathPointer() const
{
  return static_cast<const wchar_t*>(m_archive_saved_as_full_path);
}

void ON_BinaryArchive::SetArchiveFullPath(
  const wchar_t* archive_full_path
  )
{
  if (m_archive_full_path.IsNotEmpty())
  {
    // The first attempt wins!
    if (false == m_archive_full_path.EqualOrdinal(archive_full_path, false))
    {
      // You need to get this right on the first try.
      // If you are hitting this error, figure out why you are attempting to change
      // this value and/or and make sure ArchiveFullPath().IsEmpty() 
      // is true before you attempt to set it.
      // This is here because the value gets set correctly and then changed
      // to the wrong value when people use temp files and rename after writing
      // and don't pay attention to what they are doing.
      ON_ERROR("Attempt to change archive path.");
    }
    return;
  }

  ON_wString local_full_path(archive_full_path);
  archive_full_path = local_full_path;

  ON_wString archive_file_name;
  ON_wString archive_directory_name;

  if (nullptr != archive_full_path && 0 != archive_full_path[0])
  {
    const wchar_t* dr = 0;
    const wchar_t* d = 0;
    const wchar_t* f = 0;
    const wchar_t* e = 0;
    on_wsplitpath(archive_full_path, &dr, &d, &f, &e);

    if (archive_full_path == f || (nullptr !=  d && f > archive_full_path && ON_FileSystemPath::IsRelativePath(archive_full_path) ) )
    {
      const ON_wString current_directory = ON_FileSystemPath::CurrentDirectory(true);
      if (current_directory.IsNotEmpty())
      {
        local_full_path = ON_FileSystemPath::CombinePaths(static_cast<const wchar_t*>(current_directory), false, archive_full_path, true, false);
        archive_full_path = local_full_path;
        on_wsplitpath(archive_full_path, &dr, &d, &f, &e);
      }
    }

    if (nullptr != f && 0 != f[0])
    {

      archive_file_name = f;
      if (nullptr == dr)
        dr = d;
      if (nullptr != dr && 0 != dr[0] && dr < f)
      {
        archive_directory_name = dr;
        archive_directory_name.SetLength(f-dr);
      }
    }
  }

  SetArchiveFullPath(
    static_cast<const wchar_t*>(archive_directory_name),
    static_cast<const wchar_t*>(archive_file_name)
    );
  m_archive_full_path = archive_full_path;
  switch (m_mode)
  {
  case ON::archive_mode::write3dm:
  case ON::archive_mode::write:
    m_archive_saved_as_full_path = m_archive_full_path;
    break;
  default:
    break;
  }
}

void ON_BinaryArchive::SetArchiveFullPath(
  const wchar_t* archive_directory_name,
  const wchar_t* archive_file_name
  )
{
  ON_wString s(archive_directory_name);
  s.TrimRight(L"/\\");
  if (s.IsEmpty() || (2 == s.Length() && ':' == s[1]))
    s = archive_directory_name;

  const ON_wString local_directory_name(s);

  if (nullptr != archive_file_name)
  {
    switch (archive_file_name[0])
    {
    case '/':
    case '\\':
    case ':':
      ON_ERROR("archive_file_name is not valid.");
      archive_file_name = nullptr;
    }
  }
  const ON_wString local_file_name(archive_file_name);

  if (m_archive_directory_name.IsNotEmpty() || m_archive_full_path.IsNotEmpty())
  {
    // The first attempt wins!
    if (false == m_archive_directory_name.EqualOrdinal(local_directory_name, false))
    {
      // You need to get this right on the first try.
      // If you are hitting this error, figure out why you are attempting to change
      // this value and/or and make sure ArchiveFullPath().IsEmpty() 
      // is true before you attempt to set it.
      // This is here because the value gets set correctly and then changed
      // to the wrong value when people use temp files and rename after writing
      // and don't pay attention to what they are doing.
      ON_ERROR("Attempt to change archive path.");
    }
    return;
  }

  if (m_archive_file_name.IsNotEmpty() || m_archive_full_path.IsNotEmpty())
  {
    // The first attempt wins!
    if (false == m_archive_file_name.EqualOrdinal(local_file_name, false))
    {
      // You need to get this right on the first try.
      // If you are hitting this error, figure out why you are attempting to change
      // this value and/or and make sure ArchiveFullPath().IsEmpty() 
      // is true before you attempt to set it.
      // This is here because the value gets set correctly and then changed
      // to the wrong value when people use temp files and rename after writing
      // and don't pay attention to what they are doing.
      ON_ERROR("Attempt to change archive path.");
    }
    return;
  }



  m_archive_directory_name = local_directory_name;
  m_archive_file_name = local_file_name;
  if (m_archive_directory_name.IsNotEmpty() && m_archive_file_name.IsNotEmpty())
  {
    m_archive_full_path = ON_wString::EmptyString;
    m_archive_full_path += ON_FileSystemPath::DirectorySeparator;
    m_archive_full_path += m_archive_file_name;
  }
  else
    m_archive_full_path = ON_wString::EmptyString;

  switch (m_mode)
  {
  case ON::archive_mode::write3dm:
  case ON::archive_mode::write:
    m_archive_saved_as_full_path = m_archive_full_path;
    break;
  default:
    break;
  }
}

ON_BinaryArchive::eStorageDeviceError ON_BinaryArchive::StorageDeviceErrorFromUnsigned(
  unsigned int storage_device_error_as_unsigned
  )
{
  switch (storage_device_error_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_BinaryArchive::eStorageDeviceError::None);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_BinaryArchive::eStorageDeviceError::WriteFailed);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_BinaryArchive::eStorageDeviceError::SeekFailedDuringWriting);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_BinaryArchive::eStorageDeviceError::ReadFailed);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_BinaryArchive::eStorageDeviceError::SeekFailedDuringReading);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_BinaryArchive::eStorageDeviceError::UnknownDeviceError);
  }

  ON_ERROR("Invalid storage_device_error_as_unsigned parmeter.");
  return ON_BinaryArchive::eStorageDeviceError::UnknownDeviceError;
}

unsigned int ON_BinaryArchive::StorageDeviceError() const
{
  return m_storage_device_error;
}

void ON_BinaryArchive::SetStorageDeviceError(
  ON_BinaryArchive::eStorageDeviceError storage_device_error
  )
{
  const unsigned int u = static_cast<unsigned int>(storage_device_error);
  SetStorageDeviceError(u);
}


void ON_BinaryArchive::SetStorageDeviceError(
  unsigned int storage_device_error
  )
{
  if (0 != storage_device_error)
  {
    Internal_ReportCriticalError();

    // A critical error terminates the read/write.
    // The first one sets the code and subsequent attempts to modify
    // the code fail.
    if (0 == m_storage_device_error)
    {
      ON_ERROR("Damaged file and / or buggy code. Please investigate.");
      m_storage_device_error = storage_device_error;
    }
  }
}

bool ON_BinaryArchive::ToggleByteOrder(
  size_t count,          // number of elements
  size_t sizeof_element, // size of element (2,4, or 8)
  const void* src,    // source buffer
  void* dst           // destination buffer (can be same as source buffer)
  )
{
  bool rc = (0 == count || (count > 0 && sizeof_element > 0 && nullptr != src && nullptr != dst));
  if ( rc && count > 0 ) 
  {
    unsigned char c[32];
    const unsigned char* a = (const unsigned char*)src;
    unsigned char* b = (unsigned char*)dst;
    const unsigned char* b1 = b + (count*sizeof_element);

    // loops are unrolled and a switch is used
    // to speed things up a bit.
    switch(sizeof_element) 
    {
    case 2:
      while(b < b1) 
      {
        c[0] = *a++;
        c[1] = *a++;
        *b++ = c[1];
        *b++ = c[0];
      }
      break;

    case 4:
      while(b < b1) 
      {
        c[0] = *a++;
        c[1] = *a++;
        c[2] = *a++;
        c[3] = *a++;
        *b++ = c[3];
        *b++ = c[2];
        *b++ = c[1];
        *b++ = c[0];
      }
      break;

    case 8:
      while(b < b1) 
      {
        c[0] = *a++;
        c[1] = *a++;
        c[2] = *a++;
        c[3] = *a++;
        c[4] = *a++;
        c[5] = *a++;
        c[6] = *a++;
        c[7] = *a++;
        *b++ = c[7];
        *b++ = c[6];
        *b++ = c[5];
        *b++ = c[4];
        *b++ = c[3];
        *b++ = c[2];
        *b++ = c[1];
        *b++ = c[0];
      }
      break;

    default:
      if ( sizeof_element < 32 )
      {
        // As of 2 May 2003, this case is never used
        // by core opennurbs objects.
        //
        // This is here so that future code will work
        // if and when 128 bit "ints"/"doubles" become common
        // enough that they can be stored in 3dm files.
        // It may also happen that third party applications
        // on specialized CPUs need to toggle byte order
        // for 128 bit ints/doubles stored as user data.
        size_t i;
        while(b < b1)
        {
          for (i = 0; i < sizeof_element; i++)
            c[i] = *a++;
          while(i--)
            *b++ = c[i];
        }
      }
      else
      {
        rc = false;
      }
      break;
    }
  }
  return rc;
}

ON__UINT64 ON_BinaryArchive::CurrentPosition() const
{
  return m_current_positionX;
}

bool ON_BinaryArchive::Internal_IncrementCurrentPosition(
  ON__UINT64 delta
)
{
  // TODO: Add error detection.
  const ON__UINT64 new_pos = m_current_positionX + delta;
  m_current_positionX = new_pos;
  return true;
}

bool ON_BinaryArchive::Internal_DecrementCurrentPosition(
  ON__UINT64 delta
)
{
  if (m_current_positionX >= delta)
  {
    const ON__UINT64 new_pos = m_current_positionX - delta;
    m_current_positionX = new_pos;
    return true;
  }

  ON_ERROR("Attempt to set current position before start of archive.");

  return false;
}


bool ON_BinaryArchive::SeekFromStart( ON__UINT64 bytes_from_start )
{
  if (UnsetMode())
  {
    ON_ERROR("Invalid archive Mode().");
    return false;
  }

  if (m_bChunkBoundaryCheck)
  {
    const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
    if (nullptr != c)
    {
      ON_ERROR("Attempt to seek before beginning of current chunk.");
      return false;
    }
  } 

  if (0 != CurrentPosition() )
  {
    // Internal_SeekToStart() is a pure virutal function that must overridden.
    if (!Internal_SeekToStartOverride())
    {
      ON_ERROR("Internal_SeekToStartOverride() failed.");
      if (ReadMode())
        SetStorageDeviceError(ON_BinaryArchive::eStorageDeviceError::SeekFailedDuringReading);
      if (WriteMode())
        SetStorageDeviceError(ON_BinaryArchive::eStorageDeviceError::SeekFailedDuringWriting);
      return false;
    }
    m_current_positionX = 0;
  }

  return (bytes_from_start > 0) ? SeekForward(bytes_from_start) : true;
}

bool ON_BinaryArchive::SeekForward( ON__UINT64 bytes_forward )
{
  return Internal_SeekCur(true, bytes_forward);
}

bool ON_BinaryArchive::SeekBackward( ON__UINT64 bytes_backward )
{
  return Internal_SeekCur(false, bytes_backward);
}

bool ON_BinaryArchive::Internal_SeekCur( bool bForward, ON__UINT64 offset )
{
  // Internal_SeekFromCurrentPosition() is a pure virutal function that must overridden. 
  // Some implementations may use signed 4 byte int in critical places.
  // SeekForward() will work correctly in this worst case situation.
  if (UnsetMode())
  {
    ON_ERROR("Invalid archive Mode().");
    return false;
  }

  const ON__UINT64 current_pos = CurrentPosition();

  if (false == bForward && offset > current_pos)
  {
    ON_ERROR("Attempt to seek before archive beginning.");
    return false;
  }

  const ON__UINT64 new_pos
    = bForward
    ? (current_pos + offset)
    : (current_pos - offset);

  if (m_bChunkBoundaryCheck)
  {
    const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
    if (nullptr != c && c->m_start_offset <= current_pos && current_pos <= c->m_end_offset )
    {
      if (new_pos > c->m_end_offset)
      {
        // The code that seeks 1 byte past the end of a level 1 chunk disables chunk boundary checking for that seek.)
        ON_ERROR("Attempt to seek beyond end of current chunk.");
        return false;
      }
      if (new_pos < c->m_start_offset)
      {
        // seeking before beginning of chunk's data
        // (The code that seeks back to write a chunk length disables chunk boundary checking for that write.) 
        ON_ERROR("Attempt to seek before beginning of current chunk.");
        return false;
      }
    }
  }      

  const int dir = bForward ? 1 : -1;
  int ioffset;
  const ON__UINT64 max_internal_seek = 2147483632; // < maximum signed 4 bytes int = 2147483647
  while ( offset > 0 )
  {
    const ON__UINT64 delta = (offset > max_internal_seek) ? max_internal_seek : offset;
    ioffset = dir*((int)delta);
    if (false == Internal_SeekFromCurrentPositionOverride(ioffset))
    {
      ON_ERROR("Internal_SeekFromCurrentPositionOverride(ioffset) failed.");
      if (ReadMode())
        SetStorageDeviceError(ON_BinaryArchive::eStorageDeviceError::SeekFailedDuringReading);
      if (WriteMode())
        SetStorageDeviceError(ON_BinaryArchive::eStorageDeviceError::SeekFailedDuringWriting);
      return false;
    }
    if (bForward)
      Internal_IncrementCurrentPosition(delta);
    else
      Internal_DecrementCurrentPosition(delta);
    offset -= delta;
  }

  return true;
}

bool
ON_BinaryArchive::ReadChar(    // Read an array of 8 bit chars
  size_t count,       // number of chars to read
  char* p
)
{
  return ReadByte(count, p);
}

bool
ON_BinaryArchive::ReadChar(    // Read a single 8 bit char
  char* p
)
{
  return ReadByte(1, p);
}

bool
ON_BinaryArchive::ReadChar(    // Read an array of 8 bit signed chars
		size_t count,       // number of chars to read
  ON__INT8*  p
		)
{
  return ReadByte( count, p );
}

bool
ON_BinaryArchive::ReadChar(    // Read an array of 8 bit unsigned chars
		size_t count,       // number of unsigned chars to read
		ON__UINT8* p   
		)
{
  return ReadByte( count, p );
}

bool
ON_BinaryArchive::ReadChar(    // Read a single 8 bit signed char
		ON__INT8* p
		)
{
  return ReadByte( 1, p );
}

bool
ON_BinaryArchive::ReadChar(    // Read a single 8 bit unsigned char
		ON__UINT8* p
		)
{
  return ReadByte( 1, p );
}

bool
ON_BinaryArchive::ReadInt16( // Read an array of 16 bit integers
		size_t count,            // number of unsigned integers to read
		ON__INT16* p
		)
{
  bool rc = ReadByte( count<<1, p );
  if (rc && m_endian == ON::endian::big_endian)
  {
    // reverse byte order
		unsigned char* b= (unsigned char*) (p);
		unsigned char  c;
		while(count--) {
			c = b[0]; b[0] = b[1]; b[1] = c;
			b += 2;
		}
  }
  return rc;
}

bool
ON_BinaryArchive::ReadShort(   // Read an array of 16 bit shorts
		size_t count,       // number of signed chars to read
		ON__INT16* p
		)
{
#pragma ON_PRAGMA_WARNING_PUSH
// Disable the MSC /W4 "conditional expression is constant" warning
// about 2 == sizeof(*p).  Since this code has to run on machines
// where sizeof(*p) can be 2, 4, or 8 bytes, the test is necessary.
#pragma ON_PRAGMA_WARNING_DISABLE_MSC(4127)

  bool rc = true;

  if ( 2 == sizeof(*p) )
  {
    rc = ReadInt16( count, (ON__INT16*)p );
  }
  else
  {
    size_t j;
    ON__INT16 i16;
    for ( j = 0; j < count && rc; j++ )
    {
      rc = ReadInt16( 1, &i16 );
      *p++ = (short)i16;
    }
  }
  return rc;

#pragma ON_PRAGMA_WARNING_POP
}

bool
ON_BinaryArchive::ReadShort(   // Read an array of 16 bit unsigned shorts
		size_t count,       // number of unsigned chars to read
		ON__UINT16* p
		)
{
  return ReadShort( count, (short*)p );
}

bool
ON_BinaryArchive::ReadShort(   // Read a single 16 bit signed short
		ON__INT16* p
		)
{
  return ReadShort( 1, p );
}

bool
ON_BinaryArchive::ReadShort(   // Read a single 16 bit unsigned short
		ON__UINT16* p
		)
{
  return ReadShort( 1, p );
}

bool
ON_BinaryArchive::ReadInt32( // Read an array of 32 bit signed integers
		size_t count,            // number of 32 bit signed integers to read
		ON__INT32* p
		)
{
  bool rc = ReadByte( count<<2, p );
  if (rc && m_endian == ON::endian::big_endian)
  {
		unsigned char* b= (unsigned char*)p;
		unsigned char  c;
		while(count--) {
			c = b[0]; b[0] = b[3]; b[3] = c;
			c = b[1]; b[1] = b[2]; b[2] = c;
			b += 4;
		}
  }
  return rc;
}

bool
ON_BinaryArchive::ReadInt( // Read an array of signed integers
		size_t count,          // number of signed chars to read
		ON__INT32* p
		)
{
#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_PUSH
// Disable the MSC /W4 "conditional expression is constant" warning
// about 4 == sizeof(*p).  Since this code has to run on machines
// where sizeof(*p) can be 2, 4, or 8 bytes, the test is necessary.
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4127 )
#endif

  bool rc;
  if ( 4 == sizeof(*p) )
  {
    rc = ReadInt32( count, (ON__INT32*)p );
  }
  else
  {
    rc = true;
    ON__INT32 i32;
    size_t j;
    for ( j = 0; j < count && rc; j++ )
    {
      rc = ReadInt32(1,&i32);
      if (rc)
        *p++ = (int)i32;
    }
  }
  return rc;

#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_POP
#endif
}

bool
ON_BinaryArchive::ReadInt( // Read an array of 32 bit unsigned integers
		size_t count,       // number of unsigned chars to read
		ON__UINT32* p
		)
{
  return ReadInt( count, (int*)p );
}

bool
ON_BinaryArchive::ReadInt( // Read a single 32 bit signed integer
		ON__INT32* p
		)
{
  return ReadInt( 1, p );
}

bool
ON_BinaryArchive::ReadInt( // Read a single 32 bit unsigned integer
		ON__UINT32* p
		)
{
  return ReadInt( 1, p );
}

bool ON_BinaryArchive::ReadBigInt( // Read an array of 64 bit signed integers
		size_t count,
		ON__INT64* p 
		)
{
  return ReadInt64(1,p);
}

bool ON_BinaryArchive::ReadBigInt( // Read an array of 64 bit unsigned integers
		size_t count,
		ON__UINT64* p
		)
{
  return ReadInt64(1,(ON__INT64*)p);
}

bool ON_BinaryArchive::ReadBigInt( // Read a single 64 bit signed integer
		ON__INT64* p
		)
{
  return ReadInt64(1,p);
}

bool ON_BinaryArchive::ReadBigInt( // Read a single 64 bit unsigned integer
		ON__UINT64* p
		)
{
  return ReadInt64(1,(ON__INT64*)p);
}



bool
ON_BinaryArchive::ReadLong( // Read an array of 32 bit signed integers
		size_t count,       // number of signed integers to read
		long* p
		)
{
#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_PUSH
// Disable the MSC /W4 "conditional expression is constant" warning
// about 4 == sizeof(*p).  Since this code has to run on machines
// where sizeof(*p) can be 2, 4, or 8 bytes, the test is necessary.
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4127 )
#endif

  bool rc;
  if ( 4 == sizeof(*p) )
  {
    rc = ReadInt32( count, (ON__INT32*)p );
  }
  else
  {
    rc = true;
    ON__INT32 i32;
    size_t j;
    for ( j = 0; j < count && rc; j++ )
    {
      rc = ReadInt32(1,&i32);
      if (rc)
        *p++ = (long)i32;
    }
  }
  return rc;

#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_POP
#endif
}

bool
ON_BinaryArchive::ReadLong( // Read an array of 32 bit integers
		size_t count,       // number of unsigned chars to read
		unsigned long* p
		)
{
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC(4996)
#pragma ON_PRAGMA_WARNING_DISABLE_CLANG("-Wdeprecated-declarations")
  return ReadLong( count, (long*)p );
#pragma ON_PRAGMA_WARNING_POP
}

bool
ON_BinaryArchive::ReadLong( // Read a single 32 bit signed integer
		long* p
		)
{
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC(4996)
#pragma ON_PRAGMA_WARNING_DISABLE_CLANG("-Wdeprecated-declarations")
  return ReadLong( 1, (long*)p );
#pragma ON_PRAGMA_WARNING_POP
}

bool
ON_BinaryArchive::ReadLong( // Read a single 32 bit unsigned integer
		unsigned long* p
		)
{
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC(4996)
#pragma ON_PRAGMA_WARNING_DISABLE_CLANG("-Wdeprecated-declarations")
  return ReadLong( 1, (long*)p );
#pragma ON_PRAGMA_WARNING_POP
}

bool
ON_BinaryArchive::ReadFloat(   // Read an array of floats
		size_t count,       // number of unsigned chars to read
		float* p
		)
{
  // 32 bit floats and 32 bit integers have same size and endian issues
  return ReadInt32( count, (ON__INT32*)p );
}

bool
ON_BinaryArchive::ReadFloat(   // Read a single float
		float* p
		)
{
  return ReadFloat( 1, p );
}

bool
ON_BinaryArchive::ReadDouble(  // Read an array of IEEE 64 bit doubles
		size_t count,       // number of unsigned chars to read
		double* p
		)
{
  bool rc = ReadByte( count<<3, p );
  if (rc && m_endian == ON::endian::big_endian)
  {
		unsigned char* b=(unsigned char*)p;
		unsigned char  c;
		while(count--) {
			c = b[0]; b[0] = b[7]; b[7] = c;
			c = b[1]; b[1] = b[6]; b[6] = c;
			c = b[2]; b[2] = b[5]; b[5] = c;
			c = b[3]; b[3] = b[4]; b[4] = c;
			b += 8;
		}
  }
  return rc;
}

bool
ON_BinaryArchive::ReadDouble(  // Read a single double
		double* p
		)
{
  return ReadDouble( 1, p );
}

bool
ON_BinaryArchive::ReadColor( ON_Color& color )
{
  unsigned int colorref = 0;
  bool rc = ReadByte( 4, (unsigned char*)&colorref ); // ReadByte prevents big endian swaps
  color = colorref;
  return rc;
}

bool
ON_BinaryArchive::ReadColor(ON_4fColor& color)
{
  float f = 0.f;

  bool rc = ReadFloat(&f);
  if (rc)
  {
    color.SetRed(f);
    rc = ReadFloat(&f);
  }
  if (rc)
  {
    color.SetGreen(f);
    rc = ReadFloat(&f);
  }
  if (rc)
  {
    color.SetBlue(f);
    rc = ReadFloat(&f);
  }
  if (rc)
  {
    color.SetAlpha(f);
  }
  return rc;
}

bool
ON_BinaryArchive::ReadPoint (
  ON_2dPoint& p
  )
{
  return ReadDouble( 2, &p.x );
}

bool
ON_BinaryArchive::ReadPoint (
  ON_3dPoint& p
  )
{
  return ReadDouble( 3, &p.x );
}

bool
ON_BinaryArchive::ReadPoint (
  ON_4dPoint& p
  )
{
  return ReadDouble( 4, &p.x );
}

bool
ON_BinaryArchive::ReadVector (
  ON_2dVector& v
  )
{
  return ReadDouble( 2, &v.x );
}

bool
ON_BinaryArchive::ReadVector (
  ON_3dVector& v
  )
{
  return ReadDouble( 3, &v.x );
}

bool ON_BinaryArchive::WriteBoundingBox(const ON_BoundingBox& bbox)
{
  bool rc = WritePoint( bbox.m_min );
  if (rc) rc = WritePoint( bbox.m_max );
  return rc;
}

bool ON_BinaryArchive::ReadBoundingBox(ON_BoundingBox& bbox)
{
  bool rc = ReadPoint( bbox.m_min );
  if (rc) rc = ReadPoint( bbox.m_max );
  return rc;
}

bool 
ON_BinaryArchive::WriteXform( const ON_Xform& x )
{
  return WriteDouble( 16, &x.m_xform[0][0] );
}

bool 
ON_BinaryArchive::ReadXform( ON_Xform& x )
{
  return ReadDouble( 16, &x.m_xform[0][0] );
}
bool 
ON_BinaryArchive::WritePlaneEquation( const ON_PlaneEquation& plane_equation )
{
  bool rc = WriteDouble( 4, &plane_equation.x );
  return rc;
}

bool 
ON_BinaryArchive::ReadPlaneEquation( ON_PlaneEquation& plane_equation )
{
  bool rc = ReadDouble( 4, &plane_equation.x );
  return rc;
}

bool 
ON_BinaryArchive::WritePlane( const ON_Plane& plane )
{
  bool rc = WritePoint( plane.origin );
  if (rc) rc = WriteVector( plane.xaxis );
  if (rc) rc = WriteVector( plane.yaxis );
  if (rc) rc = WriteVector( plane.zaxis );
  if (rc) rc = WriteDouble( 4, &plane.plane_equation.x );
  return rc;
}

bool 
ON_BinaryArchive::ReadPlane( ON_Plane& plane )
{
  bool rc = ReadPoint( plane.origin );
  if (rc) rc = ReadVector( plane.xaxis );
  if (rc) rc = ReadVector( plane.yaxis );
  if (rc) rc = ReadVector( plane.zaxis );
  if (rc) rc = ReadDouble( 4, &plane.plane_equation.x );
  return rc;
}

bool 
ON_BinaryArchive::WriteLine( const ON_Line& line )
{
  bool rc = WritePoint( line.from );
  if (rc) rc = WritePoint( line.to );
  return rc;
}

bool 
ON_BinaryArchive::ReadLine( ON_Line& line )
{
  bool rc = ReadPoint( line.from );
  if (rc) rc = ReadPoint( line.to );
  return rc;
}

bool 
ON_BinaryArchive::WriteArc(const ON_Arc& arc )
{
  bool rc = WriteCircle(arc);
  if (rc)
    rc = WriteInterval(arc.m_angle);
  return rc;
}

bool 
ON_BinaryArchive::ReadArc( ON_Arc& arc )
{
  bool rc = ReadCircle(arc);
  if (rc)
    rc = ReadInterval(arc.m_angle);
  return rc;
}

bool 
ON_BinaryArchive::WriteCircle(const ON_Circle& circle)
{
  bool rc = WritePlane( circle.plane );
  if (rc)
    rc = WriteDouble( circle.radius );
  // m_point[] removed 2001, November, 7
  if (rc)
    rc = WritePoint( circle.PointAt(0.0) );
  if (rc)
    rc = WritePoint( circle.PointAt(0.5*ON_PI) );
  if (rc)
    rc = WritePoint( circle.PointAt(ON_PI) );
  /*
  if (rc)
    rc = WritePoint( circle.m_point[0] );
  if (rc)
    rc = WritePoint( circle.m_point[1] );
  if (rc)
    rc = WritePoint( circle.m_point[2] );
  */
  return rc;
}

bool 
ON_BinaryArchive::ReadCircle(ON_Circle& circle)
{
  ON_3dPoint scratch;
  bool rc = ReadPlane( circle.plane );
  if (rc)
    rc = ReadDouble( &circle.radius );
  // m_point[] removed 2001, November, 7
  if (rc)
    rc = ReadPoint( scratch );
  if (rc)
    rc = ReadPoint( scratch );
  if (rc)
    rc = ReadPoint( scratch );
  /*
  if (rc)
    rc = ReadPoint( circle.m_point[0] );
  if (rc)
    rc = ReadPoint( circle.m_point[1] );
  if (rc)
    rc = ReadPoint( circle.m_point[2] );
  */
  return rc;
}


bool 
ON_BinaryArchive::WriteInterval( const ON_Interval& t )
{
  return WriteDouble( 2, t.m_t );
}

bool 
ON_BinaryArchive::ReadInterval( ON_Interval& t )
{
  return ReadDouble( 2, t.m_t );
}

bool
ON_BinaryArchive::ReadUuid( ON_UUID& uuid )
{
  bool    rc = ReadInt32( 1, (ON__INT32*)(&uuid.Data1) );
  if (rc) rc = ReadInt16( 1, (ON__INT16*)(&uuid.Data2) );
  if (rc) rc = ReadInt16( 1, (ON__INT16*)(&uuid.Data3) );
  if (rc) rc = ReadByte( 8, uuid.Data4 );
  return rc;
}

bool ON_BinaryArchive::ReadDisplayMaterialRef( ON_DisplayMaterialRef& dmr )
{
  bool rc = ReadUuid( dmr.m_viewport_id );
  if (rc) 
    rc = ReadUuid( dmr.m_display_material_id );
  return rc;
}

bool
ON_BinaryArchive::ReadTime( struct tm& utc )
{
  // utc = coordinated universal time ( a.k.a GMT, UTC )
  // (From ANSI C time() and gmtime().)
  bool rc = ReadInt( &utc.tm_sec );
  if ( rc )
    rc = ReadInt( &utc.tm_min );
  if ( rc )
    rc = ReadInt( &utc.tm_hour );
  if ( rc )
    rc = ReadInt( &utc.tm_mday );
  if ( rc )
    rc = ReadInt( &utc.tm_mon );
  if ( rc )
    rc = ReadInt( &utc.tm_year );
  if ( rc )
    rc = ReadInt( &utc.tm_wday );
  if ( rc )
    rc = ReadInt( &utc.tm_yday );
  if ( rc ) {
    if ( utc.tm_sec < 0 || utc.tm_sec > 60 )
      rc = false;
    if ( utc.tm_min < 0 || utc.tm_min > 60 )
      rc = false;
    if ( utc.tm_hour < 0 || utc.tm_hour > 24 )
      rc = false;
    if ( utc.tm_mday < 0 || utc.tm_mday > 31 )
      rc = false;
    if ( utc.tm_mon < 0 || utc.tm_mon > 12 )
      rc = false;
    // no year restrictions because dates are used in archeological userdata
    if ( utc.tm_wday < 0 || utc.tm_wday > 7 )
      rc = false;
    if ( utc.tm_yday < 0 || utc.tm_yday > 366 )
      rc = false;
    if ( !rc ) {
      ON_ERROR("ON_BinaryArchive::ReadTime() - bad time in archive");
    }
  }
  return rc;
}

bool
ON_BinaryArchive::ReadStringSize( // Read size of nullptr terminated string
    size_t* sizeof_string          // (returned size includes nullptr terminator)
    )
{
  ON__UINT32 ui32 = 0;
  bool rc = ReadInt32(1,(ON__INT32*)&ui32);
  // Note that ui32 = number of elements in the string array, including
  // the null terminator.  So ui32 should either be 0 or be >= 2.
  // The string array elements can be chars or unsigned shorts;
  // therefore the number of bytes in the string cannot be determined
  // at this point because we don't know what type of string is
  // being read.
  if (rc)
  {
    // 8 October 2004 Dale Lear
    //    Added the sanity checks on string size to avoid attempts
    //    to allocate huge amounts of memory when the value
    //    comes from a damaged file.
    if ( 0 != (0xF000000 & ui32) )
    {
      // 268 million chars oughta be plenty
      ON_ERROR("string element count is impossibly large");
      rc = false;
    }
    else if ( ui32 > 0 )
    {
      // make sure this is possible
      const ON_3DM_BIG_CHUNK* curchunk = m_chunk.Last();
      if ( 0 != curchunk && 0 == (TCODE_SHORT & curchunk->m_typecode) )
      {
        if (    curchunk->m_big_value < 0 
             || ((ON__INT64)ui32) > curchunk->m_big_value 
           )
        {
          ON_ERROR("string element count exceeds current chunk size");
          rc = false;
        }
      }
    }

    if (rc)
    {
      *sizeof_string = (size_t)ui32;
    }
  }
  return rc;
}


bool
ON_BinaryArchive::ReadStringUTF8ElementCount(
    size_t* string_utf8_element_count
    )
{
  ON__UINT32 ui32 = 0;
  bool rc = ReadInt32(1,(ON__INT32*)&ui32);
  // Note that ui32 = number of elements in the string array, including
  // the null terminator.  So ui32 should either be 0 or be >= 2.
  // The string array elements can be chars or unsigned shorts;
  // therefore the number of bytes in the string cannot be determined
  // at this point because we don't know what type of string is
  // being read.
  if (rc)
  {
    // 8 October 2004 Dale Lear
    //    Added the sanity checks on string size to avoid attempts
    //    to allocate huge amounts of memory when the value
    //    comes from a damaged file.
    if ( 0 != (0xF000000 & ui32) )
    {
      // 268 million chars oughta be plenty
      ON_ERROR("string element count is impossibly large");
      rc = false;
    }
    else if ( ui32 > 0 )
    {
      // make sure this is possible
      const ON_3DM_BIG_CHUNK* curchunk = m_chunk.Last();
      if ( 0 != curchunk && 0 == (TCODE_SHORT & curchunk->m_typecode) )
      {
        if (    curchunk->m_big_value < 0 
             || ((ON__INT64)ui32) > curchunk->m_big_value
           )
        {
          ON_ERROR("string byte count exceeds current chunk size");
          rc = false;
        }
      }
    }
  }
  if (!rc)
    ui32 = 0;
  if ( string_utf8_element_count )
    *string_utf8_element_count = (size_t)ui32;
  return rc;
}


bool
ON_BinaryArchive::ReadStringUTF16ElementCount(
    size_t* string_utf16_element_count
    )
{
  ON__UINT32 ui32 = 0;
  bool rc = ReadInt32(1,(ON__INT32*)&ui32);
  // Note that ui32 = number of ON__UINT16 elements in the string array, 
  // including the null terminator. So ui32 should either be 0 or >= 2.
  if (rc)
  {
    if ( 0 != (0xF000000 & ui32) )
    {
      // 268 million chars oughta be plenty
      ON_ERROR("string element count is impossibly large");
      rc = false;
    }
    else if ( ui32 > 0 )
    {
      // make sure this is possible
      const ON_3DM_BIG_CHUNK* curchunk = m_chunk.Last();
      if ( 0 != curchunk && 0 == (TCODE_SHORT & curchunk->m_typecode) )
      {
        const ON__UINT64 unread_byte_count = curchunk->LengthRemaining(CurrentPosition());
        const ON__UINT64 string_byte_count = (2 * ui32); // 2 = sizeof(ON__UINT16)
        if (unread_byte_count < string_byte_count )
        {
          ON_ERROR("string byte count exceeds current chunk size");
          rc = false;
        }
      }
    }
  }

  if (!rc)
    ui32 = 0;
  if ( string_utf16_element_count )
    *string_utf16_element_count = (size_t)ui32;
  return rc;
}

bool
ON_BinaryArchive::ReadString(         // Read nullptr terminated string
    size_t string_utf8_element_count, // = value from ReadStringUTF8ElementCount()
    char* p                           // array[string_utf8_element_count]
    )
{
  return ReadByte( string_utf8_element_count, p );
}

bool
ON_BinaryArchive::ReadString(         // Read nullptr terminated string
    size_t string_utf8_element_count, // = value from ReadStringUTF8ElementCount()
    unsigned char* p                  // array[string_utf8_element_count]
    )
{
  return ReadByte( string_utf8_element_count, p );
}

bool
ON_BinaryArchive::ReadString(          // Read nullptr terminated unicode string
    size_t string_utf16_element_count, // length = value from ReadStringUTF16ElementCount()
    unsigned short* p                  // array[string_utf16_element_count]
    )
{
  return ReadShort( string_utf16_element_count, p );
}

bool
ON_BinaryArchive::ReadString( ON_String& s )
{
  s.Destroy();
  size_t string_utf8_element_count = 0;
  bool rc = ReadStringUTF8ElementCount( &string_utf8_element_count );
  if ( rc && string_utf8_element_count > 0 ) 
  {
    const int istring_utf8_element_count = (int)string_utf8_element_count; // (int) converts 64 bits size_t
    s.ReserveArray(istring_utf8_element_count);
    ReadString( string_utf8_element_count, s.Array() );
    s.SetLength( istring_utf8_element_count-1 );
  }
  return rc;
}

bool
ON_BinaryArchive::ReadString( ON_wString& s )
{
#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_PUSH
// Disable the MSC /W4 "conditional expression is constant" warning
// about 2 == sizeof(wchar_t).  Since this code has to run on machines
// where sizeof(wchar_t) can be 2, 4, or 8 bytes, the test is necessary.
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4127 )
#endif

  s.Destroy();
  size_t string_utf16_element_count = 0;
  bool rc = ReadStringUTF16ElementCount( &string_utf16_element_count );
  if ( rc && string_utf16_element_count > 0 ) 
  {
    // string_utf16_element_count = number of ON__INT16 elements in
    // the string.  This is almost always the same as the
    // number of unicode code points. However, if one of
    // the code points happens to require two ON__INT16 
    // values to encode, then string_utf16_element_count will be 
    // larger than the number of unicode code points in 
    // the array.
    const int istring_utf16_element_count = (int)string_utf16_element_count;
    if ( 2 == sizeof(wchar_t) ) 
    {
      // When sizeof(wchar_t) is 2 bytes, assume wchar_t strings are 
      // UTF-16 encoded unicode strings.
      s.ReserveArray( istring_utf16_element_count );
      rc = ReadInt16( string_utf16_element_count, (ON__INT16*)s.Array() );
      if (rc)
        s.SetLength( istring_utf16_element_count-1 );
    }
    else if ( 4 == sizeof(wchar_t)  )
    {
      // When sizeof(wchar_t) is 4 bytes, assume wchar_t strings are 
      // UTF-32 encoded unicode strings. (some Apple CLang and GNU gcc implementations do this.)

      // Read the UTF-16 encode string from the file into
      // utf16_buffer[].
      ON_SimpleArray<ON__UINT16> utf16_buffer(istring_utf16_element_count);
      rc = ReadInt16(string_utf16_element_count,(ON__INT16*)utf16_buffer.Array());
      if(rc)
      {
        // convert to a UTF-32 encoded unicode string.
        utf16_buffer.SetCount(istring_utf16_element_count);
        utf16_buffer[istring_utf16_element_count-1] = 0;
        rc = false;
        const ON__UINT16* sUTF16 = utf16_buffer.Array();
        const int bTestByteOrder = false;
        const int sUTF16_count = istring_utf16_element_count-1;
        const ON__UINT32 error_code_point = 0xFFFD;
        const unsigned int error_mask = 0xFFFFFFFF;
        unsigned int error_status = 0;

        const int utf32_array_count = ON_ConvertUTF16ToUTF32(
            bTestByteOrder,
            sUTF16,
            sUTF16_count,
            0, // unsigned int* sUTF32
            0, // int sUTF32_count
            &error_status,
            error_mask,
            error_code_point,
            0 // const ON__UINT16** sNextUTF16
            );

        if ( 0 == utf32_array_count )
        {
          rc = true;
        }
        else if ( utf32_array_count > 0 )
        {
          error_status = 0;
          s.ReserveArray(utf32_array_count+1);
          const int utf32_array_count1 = ON_ConvertUTF16ToUTF32(
              bTestByteOrder,
              sUTF16,
              sUTF16_count,
              (unsigned int*)s.Array(), // unsigned int* sUTF32
              utf32_array_count, // sUTF32_count
              &error_status,
              error_mask,
              error_code_point,
              0 // const ON__UINT16** sNextUTF16
              );
          if ( utf32_array_count1 == utf32_array_count )
          {
            s.SetLength( utf32_array_count );
            rc = true;
          }
        }
      }
    }
    if (!rc)
      s.Destroy();
  }
  return rc;

#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_POP
#endif
}


bool ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON_MappingChannel>& a)
{
  int i, count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  for  ( i = 0; i < count && rc; i++ )
  {
    // ON_MappingChannel::Write() puts the element in a chunk
    rc = a[i].Write(*this);
  }
  return rc;
}

bool ON_BinaryArchive::WriteArray( const ON_ClassArray<ON_MaterialRef>& a)
{
  int i, count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  for  ( i = 0; i < count && rc; i++ )
  {
    // ON_MaterialRef::Write() puts the element in a chunk
    rc = a[i].Write(*this);
  }
  return rc;
}


bool ON_BinaryArchive::WriteArray( int count, const ON_Layer* a)
{
  int i;
  if ( count < 0 || 0 == a )
    count = 0;
  bool rc = WriteInt( count );
  for  ( i = 0; i < count && rc; i++ )
  {
    rc = WriteObject(a[i]);
  }
  return rc;
}

bool ON_BinaryArchive::WriteArray( int count, const ON_Layer*const* a)
{
  int i;
  if ( count < 0 || 0 == a )
    count = 0;
  bool rc = WriteInt( count );
  for  ( i = 0; i < count && rc; i++ )
  {
    rc = WriteObject(a[i]);
  }
  return rc;
}

bool ON_BinaryArchive::WriteArray( const ON_ClassArray<ON_MappingRef>& a )
{
  int i, count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  for  ( i = 0; i < count && rc; i++ )
  {
    // ON_MappingRef::Write() puts the element in a chunk
    rc = a[i].Write(*this);
  }
  return rc;
}


bool ON_BinaryArchive::WriteArray( const ON_ClassArray<ON_ObjRef>& a)
{
  int i, count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  for  ( i = 0; i < count && rc; i++ )
  {
    // ON_ObjRef::Write() puts the element in a chunk
    rc = a[i].Write(*this);
  }
  return rc;
}

bool ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON_ObjRef_IRefID>& a)
{
  int i, count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  for  ( i = 0; i < count && rc; i++ )
  {
    // ON_ObjRef_IRefID::Write() puts the element in a chunk
    rc = a[i].Write(*this);
  }
  return rc;
}

bool ON_BinaryArchive::ReadArray( ON_SimpleArray<ON_MappingChannel>& a )
{
  a.Empty();
  int i, count;
  bool rc = ReadInt( &count );
  if (rc)
  {
    a.SetCapacity(count);
    for  ( i = 0; i < count && rc; i++ )
    {
      rc = a.AppendNew().Read(*this);
    }
  }
  return rc;
}

bool ON_BinaryArchive::ReadArray( ON_ClassArray<ON_MaterialRef>& a)
{
  a.Empty();
  int i, count;
  bool rc = ReadInt( &count );
  if (rc)
  {
    a.SetCapacity(count);
    for  ( i = 0; i < count && rc; i++ )
    {
      rc = a.AppendNew().Read(*this);
    }
  }
  return rc;
}

bool ON_BinaryArchive::ReadArray( ON_ObjectArray<class ON_Layer>& a)
{
  a.Empty();
  int i, count;
  bool rc = ReadInt( &count );
  if (rc)
  {
    a.SetCapacity(count);
    for  ( i = 0; i < count && rc; i++ )
    {
      rc = (1 == ReadObject(a.AppendNew()));
      if (!rc)
      {
        a.Remove();
        break;
      }
    }
  }
  return rc;
}


bool ON_BinaryArchive::ReadArray( ON_SimpleArray<class ON_Layer*>& a)
{
  a.Empty();
  ON_Layer* layer;
  int i, count;
  bool rc = ReadInt( &count );
  if (rc)
  {
    a.SetCapacity(count);
    for  ( i = 0; i < count && rc; i++ )
    {
      layer = 0;
      ON_Object* p = 0;
      rc = (1==ReadObject(&p));
      if (rc)
      {
        layer = ON_Layer::Cast(p);
      }
      if (!rc || 0 == layer)
      {
        if ( p )
          delete p;
        rc = false;
        break;
      }
      a.Append(layer);
    }
  }
  return rc;
}

bool ON_BinaryArchive::ReadArray( ON_ClassArray<ON_MappingRef>& a)
{
  a.Empty();
  int i, count;
  bool rc = ReadInt( &count );
  if (rc)
  {
    a.SetCapacity(count);
    for  ( i = 0; i < count && rc; i++ )
    {
      rc = a.AppendNew().Read(*this);
    }
  }
  return rc;
}

bool ON_BinaryArchive::ReadArray( ON_ClassArray<ON_ObjRef>& a)
{
  a.Empty();
  int i, count;
  bool rc = ReadInt( &count );
  if (rc)
  {
    a.SetCapacity(count);
    for  ( i = 0; i < count && rc; i++ )
    {
      rc = a.AppendNew().Read(*this);
    }
  }
  return rc;
}

bool ON_BinaryArchive::ReadArray( ON_SimpleArray<ON_ObjRef_IRefID>& a)
{
  a.Empty();
  int i, count;
  bool rc = ReadInt( &count );
  if (rc)
  {
    a.SetCapacity(count);
    for  ( i = 0; i < count && rc; i++ )
    {
      rc = a.AppendNew().Read(*this);
    }
  }
  return rc;
}


bool ON_BinaryArchive::ReadArray( ON_SimpleArray<ON_DisplayMaterialRef>& a )
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) 
  {
    a.SetCapacity( count );
    int i;
    for ( i = 0; i < count && rc; i++ )
    {
      rc = ReadDisplayMaterialRef(a.AppendNew());
    }
  }
  return rc;
}

bool 
ON_BinaryArchive::ReadArray( ON_ClassArray<ON_String>& a)
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) 
  {
    a.SetCapacity( count );
    int i;
    for ( i = 0; i < count && rc; i++ )
    {
      rc = ReadString( a.AppendNew() );
    }
  }
  return rc;
}

bool 
ON_BinaryArchive::ReadArray( ON_ClassArray<ON_wString>& a)
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 )
  {
    a.SetCapacity( count );
    int i;
    for ( i = 0; i < count && rc; i++ )
    {
      rc = ReadString( a.AppendNew() );
    }
  }
  return rc;
}

bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON_DisplayMaterialRef>& a )
{
  int i, count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  for  ( i = 0; i < count && rc; i++ )
  {
    rc = WriteDisplayMaterialRef( a[i] );
  }
  return rc;
}

bool 
ON_BinaryArchive::WriteArray( const ON_ClassArray<ON_String>& a )
{
  int i, count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  for  ( i = 0; i < count && rc; i++ )
  {
    rc = WriteString( a[i] );
  }
  return rc;
}

bool 
ON_BinaryArchive::WriteArray( const ON_ClassArray<ON_wString>& a )
{
  int i, count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  for  ( i = 0; i < count && rc; i++ )
  {
    rc = WriteString( a[i] );
  }
  return rc;
}

bool 
ON_BinaryArchive::ReadArray( ON_SimpleArray<bool>& a )
{
#if defined(ON_COMPILER_MSC)
// Disable the MSC /W4 "conditional expression is constant" warning
// about sizeof(*c) == sizeof(*b).  Since this code has to run on machines
// where sizeof(bool) can be 1, 2, 4, or 8 bytes, the test is necessary.
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4127 )
#endif

  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) 
  {
    a.SetCapacity( count );
    char* c = 0;
    bool* b = a.Array();
    if ( sizeof(*c) == sizeof(*b) )
    {
      // 8 bit "bool" on this compiler
      c = (char*)b;
    }
    else if ( b )
    {
      // bigger "bool" on this compiler
      c = (char*)onmalloc(count*sizeof(*c));
    }
    rc = ReadChar( count, c );
    if ( rc )
    {
      if ( c == (char*)b )
      {
        a.SetCount(count);
      }
      else if ( c )
      {
        int i;
        for ( i = 0; i < count; i++ )
        {
          a.Append(c[i]?true:false);
        }
        onfree(c);
      }
    }
  }
  return rc;

#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_POP
#endif

}

bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<char>& a )
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) {
    a.SetCapacity( count );
    rc = ReadChar( count, a.Array() );
    if ( rc )
      a.SetCount(count);
  }
  return rc;
}

bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<ON__INT8>& a )
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt(&count);
  if (rc && count > 0) {
    a.SetCapacity(count);
    rc = ReadChar(count, a.Array());
    if (rc)
      a.SetCount(count);
  }
  return rc;
}

bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<ON__INT16>& a )
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) {
    a.SetCapacity( count );
    rc = ReadShort( count, a.Array() );
    if ( rc )
      a.SetCount(count);
  }
  return rc;
}

bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<ON__INT32>& a )
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) {
    a.SetCapacity( count );
    rc = ReadInt( count, a.Array() );
    if ( rc )
      a.SetCount(count);
  }
  return rc;
}

bool
ON_BinaryArchive::ReadArray(ON_SimpleArray<ON__UINT8>& a)
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt(&count);
  if (rc && count > 0) {
    a.SetCapacity(count);
    rc = ReadChar(count, a.Array());
    if (rc)
      a.SetCount(count);
  }
  return rc;
}

bool
ON_BinaryArchive::ReadArray(ON_SimpleArray<ON__UINT16>& a)
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt(&count);
  if (rc && count > 0) {
    a.SetCapacity(count);
    rc = ReadShort(count, a.Array());
    if (rc)
      a.SetCount(count);
  }
  return rc;
}

bool
ON_BinaryArchive::ReadArray(ON_SimpleArray<ON__UINT32>& a)
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt(&count);
  if (rc && count > 0) {
    a.SetCapacity(count);
    rc = ReadInt(count, a.Array());
    if (rc)
      a.SetCount(count);
  }
  return rc;
}

bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<float>& a )
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) {
    a.SetCapacity( count );
    rc = ReadFloat( count, a.Array() );
    if ( rc )
      a.SetCount(count);
  }
  return rc;
}

bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<double>& a )
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) {
    a.SetCapacity( count );
    rc = ReadDouble( count, a.Array() );
    if ( rc )
      a.SetCount(count);
  }
  return rc;
}

bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<ON_Color>& a )
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) 
  {
    a.SetCapacity( count );
    rc = ReadByte( 4*count, (unsigned char*)a.Array() ); // ReadByte prevents big endian swaps
    if ( rc )
      a.SetCount(count);
  }
  return rc;
}


bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<ON_2dPoint>& a )
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) {
    a.SetCapacity( count );
    rc = ReadDouble( 2*count, &a.Array()->x );
    if ( rc )
      a.SetCount(count);
  }
  return rc;
}

bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<ON_3dPoint>& a )
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) {
    a.SetCapacity( count );
    rc = ReadDouble( 3*count, &a.Array()->x );
    if ( rc )
      a.SetCount(count);
  }
  return rc;
}

bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<ON_4dPoint>& a )
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) {
    a.SetCapacity( count );
    rc = ReadDouble( 4*count, &a.Array()->x );
    if ( rc )
      a.SetCount(count);
  }
  return rc;
}

bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<ON_2dVector>& a )
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) {
    a.SetCapacity( count );
    rc = ReadDouble( 2*count, &a.Array()->x );
    if ( rc )
      a.SetCount(count);
  }
  return rc;
}

bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<ON_3dVector>& a )
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) {
    a.SetCapacity( count );
    rc = ReadDouble( 3*count, &a.Array()->x );
    if ( rc )
      a.SetCount(count);
  }
  return rc;
}

bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<ON_Xform>& a )
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) 
  {
    a.SetCapacity( count );
    int i;
    for ( i = 0; i < count && rc; i++ )
    {
      rc = ReadXform(a.AppendNew());
    }
  }
  return rc;
}

bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<ON_2fPoint>& a )
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) {
    a.SetCapacity( count );
    rc = ReadFloat( 2*count, &a.Array()->x );
    if ( rc )
      a.SetCount(count);
  }
  return rc;
}

bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<ON_3fPoint>& a )
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) {
    a.SetCapacity( count );
    rc = ReadFloat( 3*count, &a.Array()->x );
    if ( rc )
      a.SetCount(count);
  }
  return rc;
}

bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<ON_4fPoint>& a )
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) {
    a.SetCapacity( count );
    rc = ReadFloat( 4*count, &a.Array()->x );
    if ( rc )
      a.SetCount(count);
  }
  return rc;
}

bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<ON_2fVector>& a )
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) {
    a.SetCapacity( count );
    rc = ReadFloat( 2*count, &a.Array()->x );
    if ( rc )
      a.SetCount(count);
  }
  return rc;
}

bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<ON_3fVector>& a )
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) {
    a.SetCapacity( count );
    rc = ReadFloat( 3*count, &a.Array()->x );
    if ( rc )
      a.SetCount(count);
  }
  return rc;
}

bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<ON_UUID>& a )
{
  a.Empty();
  ON_UUID uuid;
  int i, count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) 
  {
    a.SetCapacity( count );
    for ( i = 0; i < count && rc; i++ )
    {
      rc = ReadUuid( uuid );
      if ( rc )
        a.Append(uuid);
    }
  }
  return rc;
}




bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<ON_UuidIndex>& a )
{
  a.Empty();
  ON_UuidIndex idi;
  int i, count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) 
  {
    a.SetCapacity( count );
    for ( i = 0; i < count && rc; i++ )
    {
      rc = ReadUuid( idi.m_id );
      if ( rc )
      {
        rc = ReadInt(&idi.m_i);
        if(rc)
          a.Append(idi);
      }
    }
  }
  return rc;
}

bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<ON_UuidPtr>& a )
{
  a.Empty();
  ON_UuidPtr idi;
  int i, count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) 
  {
    a.SetCapacity( count );
    for ( i = 0; i < count && rc; i++ )
    {
      rc = ReadUuid( idi.m_id );
      if ( rc )
      {
        ON__UINT64 ptr = 0; // 64 bits on all platforms
        rc = ReadBigInt(&ptr);
        if (rc)
        {
          idi.m_ptr = (ON__UINT_PTR)ptr;
          a.Append(idi);
        }
      }
    }
  }
  return rc;
}



bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON_UUID>& a )
{
  int i, count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  for  ( i = 0; i < count && rc; i++ )
  {
    rc = WriteUuid( a[i] );
  }
  return rc;
}


bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON_UuidIndex>& a )
{
  int i, count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  for  ( i = 0; i < count && rc; i++ )
  {
    rc = WriteUuid( a[i].m_id );
    if (rc)
      rc = WriteInt( a[i].m_i );
  }
  return rc;
}

bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON_UuidPtr>& a )
{
  int i, count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  for  ( i = 0; i < count && rc; i++ )
  {
    rc = WriteUuid( a[i].m_id );
    if (rc)
    {
      ON__UINT64 ptr = (ON__UINT64)a[i].m_ptr;
      rc = WriteBigInt(ptr); // 64 bits on all platforms
    }
  }
  return rc;
}


bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<ON_LinetypeSegment>& a )
{
  a.Empty();
  ON_LinetypeSegment seg;
  int i, count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) 
  {
    a.SetCapacity( count );
    for ( i = 0; i < count && rc; i++ )
    {
      rc = ReadLinetypeSegment( seg );
      if ( rc )
        a.Append(seg);
    }
  }
  return rc;
}

bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON_LinetypeSegment>& a )
{
  int i, count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  for  ( i = 0; i < count && rc; i++ )
  {
    rc = WriteLinetypeSegment( a[i] );
  }
  return rc;
}

bool ON_BinaryArchive::ReadLinetypeSegment(ON_LinetypeSegment& seg)
{
  seg = ON_LinetypeSegment::OneMillimeterLine;
  bool rc = ReadDouble(&seg.m_length);
  if (rc)
  {
    // ON_LinetypeSegment::eSegType::Unset was not added initialy, so juggling values is required for
    // Unset, stLine and stSpace.  Any future values with work without
    // juggling.
    unsigned int i = 0;
    rc = ReadInt(&i);
    switch (i)
    {
    case 0:
      i = static_cast<unsigned int>(ON_LinetypeSegment::eSegType::stLine);
      break;
    case 1:
      i = static_cast<unsigned int>(ON_LinetypeSegment::eSegType::stSpace);
      break;
    case ON_UNSET_UINT_INDEX:
      i = static_cast<unsigned int>(ON_LinetypeSegment::eSegType::Unset);
      break;
    }
    seg.m_seg_type = ON_LinetypeSegment::SegmentTypeFromUnsigned(i);
  }
  return rc;
}


bool ON_BinaryArchive::WriteLinetypeSegment( const ON_LinetypeSegment& seg)
{
  // do not add chunk info here
  bool rc = WriteDouble(seg.m_length);
  if (rc)
  {
    // ON_LinetypeSegment::eSegType::Unset was not added initialy, so juggling values is required for
    // Unset, stLine and stSpace.  Any future values with work without
    // juggling.
    unsigned int i;
    switch (seg.m_seg_type)
    {
    case ON_LinetypeSegment::eSegType::Unset:
      i = ON_UNSET_UINT_INDEX;
      break;
    case ON_LinetypeSegment::eSegType::stLine:
      i = 0;
      break;
    case ON_LinetypeSegment::eSegType::stSpace:
      i = 1;
      break;
    default:
      i = static_cast<unsigned int>(seg.m_seg_type);
      break;
    }
    rc = WriteInt(i);
  }
  return rc;
}


bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<ON_SurfaceCurvature>& a )
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) {
    a.SetCapacity( count );
    rc = ReadDouble( 2*count, &a.Array()->k1 );
    if ( rc )
      a.SetCount(count);
  }
  return rc;
}


bool
ON_BinaryArchive::ReadArray( ON_SimpleArray<ON_ClippingPlaneInfo>& a )
{
  a.Empty();
  int count = 0;
  bool rc = ReadInt( &count );
  if ( rc && count > 0 ) 
  {
    a.SetCapacity(count);
    for ( int i = 0; i < count && rc ; i++ )
    {
      rc = a.AppendNew().Read(*this);
      if (!rc)
        a.Remove();
    }
  }
  return rc;
}


bool ON_BinaryArchive::WriteBool( bool b )
{
  // Dale Lear - August 2017 RH-40908
  // Some Release builds using Visual Studio 2017 were optimizing all this code away
  // and writing the value of b as a byte. This was allowing values besides 0 or 1 
  // to be saved in the file.
  // I added WriteBoolTrue() and WriteBoolFalse().

  //// Code that was writing values besides 0 or 1 in Release builds.
  ////unsigned char c = (b?1:0);
  ////return WriteChar(c);

  // New code to avoid error described above.
  return (b) ? WriteBoolTrue() : WriteBoolFalse();
}

bool ON_BinaryArchive::WriteBoolTrue()
{
  // true is saved a a singel byte with value = 1.
  const unsigned char c = 1;
  return WriteChar(c);
}

bool ON_BinaryArchive::WriteBoolFalse()
{
  // false is saved a a single byte with value = 0.
  const unsigned char c = 0;
  return WriteChar(c);
}


bool ON_BinaryArchive::ReadBool( bool *b )
{
  unsigned char c;
  bool rc = ReadChar(&c);
  if (rc && b)
  {
    if ( c != 0 && c != 1 )
    {
      const unsigned int version_6_0_August_24_2017 = ON_VersionNumberConstruct(6, 0, 2017, 8, 24, 0);
      if ( ArchiveOpenNURBSVersion() < version_6_0_August_24_2017 )
      {
        // See RH-40941 and RH-40941 for examples when c is not 0 and not 1 but
        // file writing code was correctly written by the developer.
        c = 1; 
      }
      else
      {
        // WriteBool always writes a 0 or 1.  So either your code
        // has a bug, the file is corrupt, the the file pointer
        // is where it should be.
        ON_ERROR("ON_BinaryArchive::ReadBool - bool value != 0 and != 1");
        rc = false;
      }
    }
    *b = c?true:false;
  }
  return rc;
}

bool
ON_BinaryArchive::WriteChar(    // Write an array of 8 bit chars
		size_t count,       // number of chars to write
		const char* p   
		)
{
  return WriteByte( count, p );
}

bool
ON_BinaryArchive::WriteChar(    // Write a single 8 bit char
  char c
)
{
  return WriteByte(1, &c);
}

bool
ON_BinaryArchive::WriteChar(    // Write an array of 8 bit signed chars
  size_t count,       // number of chars to write
  const ON__INT8* p
)
{
  return WriteByte(count, p);
}

bool
ON_BinaryArchive::WriteChar(    // Write an array of 8 bit unsigned chars
		size_t count,       // number of unsigned chars to write
		const ON__UINT8* p
		)
{
  return WriteByte( count, p );
}

bool
ON_BinaryArchive::WriteChar(    // Write a single 8 bit signed char
		ON__INT8 c
		)
{
  return WriteByte( 1, &c );
}

bool
ON_BinaryArchive::WriteChar(    // Write a single 8 bit unsigned char
		ON__UINT8 c
		)
{
  return WriteByte( 1, &c );
}

bool
ON_BinaryArchive::WriteInt16(   // Write an array of 16 bit shorts
		size_t count,               // number of shorts to write
		const ON__INT16* p
		)
{
  bool rc = true;
  if (m_endian == ON::endian::big_endian)
  {
    if ( count > 0 ) 
    {
      const char* b = (const char*)p;
      while ( rc && count-- ) 
      {
        rc = WriteByte( 1, b+1 );
        if (rc)
          rc = WriteByte( 1, b );
        b++;
        b++;
      }
    }
  }
  else 
  {
    rc = WriteByte( count<<1, p );
  }
  return rc;
}

bool
ON_BinaryArchive::WriteShort(   // Write an array of 16 bit shorts
		size_t count,       // number of shorts to write
		const ON__INT16* p
		)
{
#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_PUSH
// Disable the MSC /W4 "conditional expression is constant" warning
// about 2 == sizeof(*p).  Since this code has to run on machines
// where sizeof(*p) can be 2, 4, or 8 bytes, the test is necessary.
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4127 )
#endif

  bool rc;
  if ( 2 == sizeof(*p) )
  {
    rc = WriteInt16( count, (const ON__INT16*)p );
  }
  else
  {
    rc = true;
    ON__INT16 i16;
    size_t j;
    for ( j = 0; j < count; j++ )
    {
      i16 = (ON__INT16)(*p++);
      rc = WriteInt16( 1, &i16);
    }
  }
  return rc;

#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_POP
#endif
}

bool
ON_BinaryArchive::WriteShort(   // Write an array of 16 bit unsigned shorts
		size_t count,       // number of shorts to write
		const ON__UINT16* p
		)
{
  return WriteShort( count, (const short*)p );
}

bool
ON_BinaryArchive::WriteShort(   // Write a single 16 bit short
		ON__INT16 s
		)
{
  return WriteShort( 1, &s );
}

bool
ON_BinaryArchive::WriteShort(   // Write a single 16 bit unsigned short
		ON__UINT16 s
		)
{
  return WriteShort( 1, &s );
}

bool
ON_BinaryArchive::WriteInt32( // Write an array of 32 bit integers
		size_t count,	            // number of ints to write
		const ON__INT32* p    
		)
{
  bool rc = true;
  if (m_endian == ON::endian::big_endian)
  {
    if ( count > 0 ) 
    {
      const char* b = (const char*)p;
      while ( rc && count-- ) 
      {
        rc = WriteByte( 1, b+3 );
        if (rc) rc = WriteByte( 1, b+2 );
        if (rc) rc = WriteByte( 1, b+1 );
        if (rc) rc = WriteByte( 1, b );
        b += 4;
      }
    }
  }
  else 
  {
    rc = WriteByte( count<<2, p );
  }
  return rc;
}

bool
ON_BinaryArchive::ReadInt64( // Read an array of 64 bit integers
		size_t count,            // number of 64 bit integers to read
		ON__INT64* p
		)
{
  bool rc = ReadByte( count<<3, p );
  if (rc && m_endian == ON::endian::big_endian)
  {
		unsigned char* b=(unsigned char*)p;
		unsigned char  c;
		while(count--) {
			c = b[0]; b[0] = b[7]; b[7] = c;
			c = b[1]; b[1] = b[6]; b[6] = c;
			c = b[2]; b[2] = b[5]; b[5] = c;
			c = b[3]; b[3] = b[4]; b[4] = c;
			b += 8;
		}
  }
  return rc;
}

bool
ON_BinaryArchive::WriteInt64( // Write an array of 64 bit integers
		size_t count,	            // number of ints to write
		const ON__INT64* p    
		)
{
  bool rc = true;
  if (m_endian == ON::endian::big_endian)
  {
    if ( count > 0 ) 
    {
      const char* b = (const char*)p;
      while ( rc && count-- ) 
      {
        rc = WriteByte( 1, b+7 );
        if (rc) rc = WriteByte( 1, b+6 );
        if (rc) rc = WriteByte( 1, b+5 );
        if (rc) rc = WriteByte( 1, b+4 );
        if (rc) rc = WriteByte( 1, b+3 );
        if (rc) rc = WriteByte( 1, b+2 );
        if (rc) rc = WriteByte( 1, b+1 );
        if (rc) rc = WriteByte( 1, b );
        b += 8;
      }
    }
  }
  else 
  {
    rc = WriteByte( count<<3, p );
  }
  return rc;
}

bool
ON_BinaryArchive::WriteInt( // Write an array of integers
		size_t count,	          // number of ints to write
		const ON__INT32* p
		)
{
#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_PUSH
// Disable the MSC /W4 "conditional expression is constant" warning
// about 4 == sizeof(*p).  Since this code has to run on machines
// where sizeof(*p) can be 2, 4, or 8 bytes, the test is necessary.
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4127 )
#endif

  bool rc;
  if ( 4 == sizeof(*p) )
  {
    rc = WriteInt32( count, (const ON__INT32*)p );
  }
  else
  {
    ON__INT32 i32;
    size_t j;
    rc = true;
    for ( j = 0; j < count && rc; j++ )
    {
      i32 = (ON__INT32)(*p++);
      rc = WriteInt32( 1, &i32 );
    }
  }
  return rc;

#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_POP
#endif
}

bool
ON_BinaryArchive::WriteSize(size_t sz)
{
  unsigned int u = (unsigned int)sz;
  return WriteInt(u);
}

bool
ON_BinaryArchive::ReadSize(size_t* sz)
{
  unsigned int u = 0;
  bool rc = ReadInt(&u);
  if (rc)
    *sz = u;
  return rc;
}

bool ON_BinaryArchive::WriteBigSize(size_t sz)
{
  ON__UINT64 u = (ON__UINT64)sz;
  return WriteInt64(1,(ON__INT64*)&u);
}

bool ON_BinaryArchive::ReadBigSize( size_t* sz )
{
  ON__UINT64 u;
  bool rc = ReadInt64(1,(ON__INT64*)&u);
  if (rc)
    *sz = (size_t)u;
  return rc;
}

bool ON_BinaryArchive::WriteBigTime(time_t t)
{
  ON__UINT64 u = (ON__UINT64)t;
  return WriteInt64(1,(ON__INT64*)&u);
}

bool ON_BinaryArchive::ReadBigTime( time_t* t )
{
  ON__UINT64 u;
  bool rc = ReadInt64(1,(ON__INT64*)&u);
  if (rc)
    *t = (time_t)u;
  return rc;
}


bool
ON_BinaryArchive::WriteInt( // Write an array of 32 bit integers
		size_t count,	      // number of ints to write
		const ON__UINT32* p
		)
{
  return WriteInt( count, (const int*)p );
}

bool
ON_BinaryArchive::WriteInt( // Write a single 32 bit signed integer
		ON__INT32 i
		)
{
  return WriteInt( 1, &i );
}

bool
ON_BinaryArchive::WriteInt( // Write a single 32 bit unsigned integer
		ON__UINT32 i
		)
{
  return WriteInt( 1, &i );
}

bool ON_BinaryArchive::WriteBigInt( // Write an array of 64 bit integers
		size_t count,
		const ON__INT64* p      
		)
{
  return WriteInt64(count,p);
}

bool ON_BinaryArchive::WriteBigInt( // Write an array of 64 bit integers
		size_t count,
		const ON__UINT64* p     
		)
{
  return WriteInt64(count,(const ON__INT64*)p);
}

bool ON_BinaryArchive:: WriteBigInt( // Write a single 64 bit integer
		ON__INT64 i
		)
{
  return WriteInt64(1,&i);
}

bool ON_BinaryArchive::WriteBigInt( // Write a single 64 bit unsigned integer
		ON__UINT64 u
		)
{
  return WriteInt64(1,(const ON__INT64*)&u);
}



bool
ON_BinaryArchive::WriteLong( // Write an array of longs
		size_t count,	      // number of longs to write
		const long* p    
		)
{
#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_PUSH
// Disable the MSC /W4 "conditional expression is constant" warning
// about 4 == sizeof(*p).  Since this code has to run on machines
// where sizeof(*p) can be 2, 4, or 8 bytes, the test is necessary.
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4127 )
#endif

  bool rc;
  if ( 4 == sizeof(*p) )
  {
    rc = WriteInt32( count, (const ON__INT32*)p );
  }
  else
  {
    ON__INT32 i32;
    size_t j;
    rc = true;
    for ( j = 0; j < count && rc; j++ )
    {
      i32 = (ON__INT32)(*p++);
      rc = WriteInt32( 1, &i32 );
    }
  }
  return rc;

#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_POP
#endif
}

bool
ON_BinaryArchive::WriteLong( // Write an array of longs
		size_t count,	      // number of longs to write
		const unsigned long* p
		)
{
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC(4996)
#pragma ON_PRAGMA_WARNING_DISABLE_CLANG("-Wdeprecated-declarations")
  return WriteLong( count, (const long*)p );
#pragma ON_PRAGMA_WARNING_POP
}

bool
ON_BinaryArchive::WriteLong( // Write a single long
		long i
		)
{
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC(4996)
#pragma ON_PRAGMA_WARNING_DISABLE_CLANG("-Wdeprecated-declarations")
  return WriteLong( 1, &i );
#pragma ON_PRAGMA_WARNING_POP
}

bool
ON_BinaryArchive::WriteLong( // Write a single unsigned long
		unsigned long i
		)
{
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC(4996)
#pragma ON_PRAGMA_WARNING_DISABLE_CLANG("-Wdeprecated-declarations")
  return WriteLong( 1, &i );
#pragma ON_PRAGMA_WARNING_POP
}


bool
ON_BinaryArchive::WriteFloat(   // Write a number of IEEE floats
		size_t count,       // number of doubles
		const float* p
		)
{
  // floats and integers have same size and endian issues
  return WriteInt( count, (const int*)p );
}

bool
ON_BinaryArchive::WriteFloat(   // Write a single float
		float f
		)
{
  return WriteFloat( 1, &f );
}

bool
ON_BinaryArchive::WriteDouble(  // Write a single double
		size_t count,       // number of doubles
		const double* p
		)
{
  bool rc = true;
  if (m_endian == ON::endian::big_endian) {
    if ( count > 0 ) {
      const char* b = (const char*)p;
      while ( rc && count-- ) {
        rc = WriteByte( 1, b+7 );
        if (rc) rc = WriteByte( 1, b+6 );
        if (rc) rc = WriteByte( 1, b+5 );
        if (rc) rc = WriteByte( 1, b+4 );
        if (rc) rc = WriteByte( 1, b+3 );
        if (rc) rc = WriteByte( 1, b+2 );
        if (rc) rc = WriteByte( 1, b+1 );
        if (rc) rc = WriteByte( 1, b );
        b += 8;
      }
    }
  }
  else {
    rc = WriteByte( count<<3, p );
  }
  return rc;
}

bool
ON_BinaryArchive::WriteComponentIndex(
		const ON_COMPONENT_INDEX& ci
		)
{
  bool rc = WriteInt( ci.m_type );
  if (rc)
    rc = WriteInt( ci.m_index );
  // do not add additional writes - you will break old file IO
  return rc;
}

bool
ON_BinaryArchive::ReadComponentIndex(
		ON_COMPONENT_INDEX& ci
		)
{
  int t;
  ci.m_type = ON_COMPONENT_INDEX::invalid_type;
  ci.m_index = 0;
  bool rc = ReadInt( &t );
  if (rc)
  {
    rc = ReadInt( &ci.m_index );
    if (rc)
    {
      ci.m_type = ON_COMPONENT_INDEX::Type(t);
    }
    // do not add additional read - you will break old file IO
  }
  return rc;
}

bool
ON_BinaryArchive::WriteDouble(  // Write a single double
		const double x
		)
{
  return WriteDouble( 1, &x );
}

bool
ON_BinaryArchive::WriteColor( const ON_Color& color )
{
  unsigned int colorref = color;
  return WriteByte( 4, (const unsigned char*)&colorref ); // WriteByte prevents big endian swaps
}

bool
ON_BinaryArchive::WriteColor(const ON_4fColor& color)
{
  if (!WriteFloat(color.Red())) return false;
  if (!WriteFloat(color.Green())) return false;
  if (!WriteFloat(color.Blue())) return false;
  if (!WriteFloat(color.Alpha())) return false;
  return true;
}

bool
ON_BinaryArchive::WritePoint (
  const ON_2dPoint& p
  )
{
  return WriteDouble( 2, &p.x );
}

bool
ON_BinaryArchive::WritePoint (
  const ON_3dPoint& p
  )
{
  return WriteDouble( 3, &p.x );
}

bool
ON_BinaryArchive::WritePoint (
  const ON_4dPoint& p
  )
{
  return WriteDouble( 4, &p.x );
}

bool
ON_BinaryArchive::WriteVector (
  const ON_2dVector& v
  )
{
  return WriteDouble( 2, &v.x );
}

bool
ON_BinaryArchive::WriteVector (
  const ON_3dVector& v
  )
{
  return WriteDouble( 3, &v.x );
}

bool ON_BinaryArchive::WriteDisplayMaterialRef( const ON_DisplayMaterialRef& dmr )
{
  bool rc = WriteUuid( dmr.m_viewport_id );
  if (rc) rc = WriteUuid( dmr.m_display_material_id );
  return rc;
}

bool
ON_BinaryArchive::WriteUuid( const ON_UUID& uuid )
{
  bool    rc = WriteInt32( 1, (const ON__INT32*)(&uuid.Data1) );
  if (rc) rc = WriteInt16( 1, (const ON__INT16*)(&uuid.Data2) );
  if (rc) rc = WriteInt16( 1, (const ON__INT16*)(&uuid.Data3) );
  if (rc) rc = WriteByte( 8, uuid.Data4 );
  return rc;
}

bool
ON_BinaryArchive::WriteTime( const struct tm& utc )
{
  // utc = coordinated universal time ( a.k.a GMT, UTC )
  // (From ANSI C time() and gmtime().)
  // The checks are here so we can insure files don't contain
  // garbage dates and ReadTime() can treat out of bounds
  // values as file corruption errors.
  int i;
  i = (int)utc.tm_sec;  if ( i < 0 || i > 60 ) i = 0;
  bool rc = WriteInt( i );
  i = (int)utc.tm_min;  if ( i < 0 || i > 60 ) i = 0;
  if ( rc )
    rc = WriteInt( i );
  i = (int)utc.tm_hour;  if ( i < 0 || i > 24 ) i = 0;
  if ( rc )
    rc = WriteInt( i );
  i = (int)utc.tm_mday;  if ( i < 0 || i > 31 ) i = 0;
  if ( rc )
    rc = WriteInt( i );
  i = (int)utc.tm_mon;  if ( i < 0 || i > 12 ) i = 0;
  if ( rc )
    rc = WriteInt( i );

  // no year restrictions because dates are used in archeological userdata
  i = (int)utc.tm_year;
  if ( rc )
    rc = WriteInt( i );

  i = (int)utc.tm_wday;  if ( i < 0 || i > 7 ) i = 0;
  if ( rc )
    rc = WriteInt( i );
  i = (int)utc.tm_yday;  if ( i < 0 || i > 366 ) i = 0;
  if ( rc )
    rc = WriteInt( i );
  return rc;
}

bool
ON_BinaryArchive::WriteString( // Write nullptr terminated UTF-8 encoded unicode string
    const char* sUTF8
    )
{
  size_t string_utf8_element_count = 0;
  if ( sUTF8 )
  {
    while(sUTF8[string_utf8_element_count])
      string_utf8_element_count++;
    if ( string_utf8_element_count )
      string_utf8_element_count++;
  }
  ON__UINT32 ui32 = (ON__UINT32)string_utf8_element_count;
  bool rc = WriteInt32(1,(ON__INT32*)&ui32);
  if ( rc && string_utf8_element_count > 0 )
    rc = WriteByte( string_utf8_element_count, sUTF8 );
  return rc;  
}

bool
ON_BinaryArchive::WriteString( // Write nullptr terminated UTF-8 encoded unicode string
    const unsigned char* sUTF8
    )
{
  return WriteString( (const char*)sUTF8 );
}

bool
ON_BinaryArchive::WriteUTF16String(  
  const unsigned short* sUTF16
  )
{
  // Write nullptr terminated UTF-16 encoded unicode string
  size_t string_utf16_element_count = 0;
  if ( sUTF16 )
  {
    while(sUTF16[string_utf16_element_count])
      string_utf16_element_count++;
    if ( string_utf16_element_count )
      string_utf16_element_count++;
  }
  ON__UINT32 ui32 = (ON__UINT32)string_utf16_element_count;
  bool rc = WriteInt32(1,(ON__INT32*)&ui32);
  if ( rc && string_utf16_element_count > 0 )
  {
    rc = WriteShort( string_utf16_element_count, sUTF16 );
  }
  return rc;  
}

bool
ON_BinaryArchive::WriteString( const ON_String& sUTF8 )
{
  // The ON_String::IsValid call prevents corrupt strings from breaking file IO
  // The parameter MUST be false here.
  sUTF8.IsValid(false);

  size_t string_utf8_element_count = sUTF8.Length();
  if ( string_utf8_element_count )
    string_utf8_element_count++;
  ON__UINT32 ui32 = (ON__UINT32)string_utf8_element_count;
  bool rc = WriteInt32(1,(ON__INT32*)&ui32);
  if ( rc && string_utf8_element_count > 0 )
    rc = WriteByte( string_utf8_element_count, sUTF8.Array() );
  return rc;  
}

bool ON_BinaryArchive::WriteWideString(
  const ON_wString& wide_string
  )
{
  return WriteWideString(static_cast<const wchar_t*>(wide_string), wide_string.Length());
}

bool ON_BinaryArchive::WriteWideString(
  const wchar_t* sWideChar,
  int sWideChar_count
  )
{
  char sUTF8_buffer[256];
  if (!BeginWrite3dmBigChunk(TCODE_UTF8_STRING_CHUNK,0))
    return false;
  bool rc = false;
  for (;;)
  {
    const unsigned char format 
      = (nullptr != sWideChar && sWideChar_count > 0 && sWideChar_count < 2147483647)
      ? 1  // 1 = uncompressed
      : 0; // 0 = empty
    if (!WriteChar(format))
      break;
    if (0 == format)
    {
      rc = true;
      break;
    }

#if 1 == ON_SIZEOF_WCHAR_T
    // wchar_t = char
    rc = WriteChar(sWideChar_count, (const char*)sWideChar);
#else
    // Convert to UTF8
    const wchar_t* sLastWideChar = sWideChar+sWideChar_count;
    int bTestByteOrder = true;
    const wchar_t* sNextWideChar;
    const int sUTF8_capacity = (int)(sizeof(sUTF8_buffer) / sizeof(sUTF8_buffer[0]));
    unsigned int error_status;
    const unsigned int error_mask = 0xFFFFFFFC;
    ON__UINT32 error_code_point = 0xFFFD;
    for (;;)
    {
      error_status = 0;
      sNextWideChar = nullptr;
      int sUTF8_count = ON_ConvertWideCharToUTF8(
        bTestByteOrder,
        sWideChar,
        sWideChar_count,
        sUTF8_buffer,
        sUTF8_capacity,
        &error_status,
        error_mask,
        error_code_point,
        &sNextWideChar
        );
      if (sUTF8_count <= 0 || sUTF8_count > sUTF8_capacity)
      {
        ON_ERROR("Invalid wide char string - incomplete write.");
        // Not serious enough to terminate writing - true will be returned.
        break;
      }

      if (false == WriteChar(sUTF8_count, sUTF8_buffer))
      {
        rc = false;
        break;
      }

      if (0 == (error_status & 0x03) && sNextWideChar == sWideChar + sWideChar_count)
      {
        break; // finished writing UTF8 string.
      }

      if (2 == (error_status & 0x03) && sWideChar < sNextWideChar && sNextWideChar < sLastWideChar)
      {
        int c = (int)(sLastWideChar - sNextWideChar);
        if (c < sWideChar_count)
        {
          sWideChar = sNextWideChar;
          sWideChar_count = c;
          bTestByteOrder = 0; // subsequent conversion should never test byte order
          continue;
        }
      }

      ON_ERROR("Invalid wide char string - incomplete write.");
      // Not serious enough to terminate writing - true will be returned.

#endif
      break;
    }

    rc = true;
    break;
  }
  if (!EndWrite3dmChunk())
    rc = false;
  return rc;

}

bool ON_BinaryArchive::ReadWideString(
  ON_wString& wide_string
  )
{
  wide_string = ON_wString::EmptyString;
  ON__INT64 big_value = 0;

  for (int pass = 0; pass < 2; pass++)
  {
    unsigned int typecode = 0;
    big_value = 0;
    if (0 == pass)
    {
      if (false == PeekAt3dmBigChunkType(&typecode, &big_value))
        return false;
    }
    else
    {
      if (false == BeginRead3dmBigChunk(&typecode, &big_value))
        return false;
    }
    if (TCODE_UTF8_STRING_CHUNK != typecode || big_value < 5)
    {
      if ( 0 != pass )
        EndRead3dmChunk();
      return false;
    }
  }

  wchar_t sWideChar_buffer[512];
  char char_buffer[2][sizeof(sWideChar_buffer)/sizeof(sWideChar_buffer[0])];
  const int buffer_capacity = (int)(sizeof(sWideChar_buffer)/sizeof(sWideChar_buffer[0]));
  int char_buffer_count[2] = { 0 };
  int chunk_byte_count = (int)(big_value-5);
  
  bool rc = false;
  for (;;)
  {
    unsigned char format = 0; 
    if (!ReadChar(&format))
      break;
    if (0 == format)
    {
      if (0 == chunk_byte_count)
        rc = true;
      break;
    }
    if ( 1 != format )
      break;

#if 1 == ON_SIZEOF_WCHAR_T
    wchar_t* sWideChar = wide_string.ReserveArray(chunk_byte_count);
    rc = ReadChar(chunk_byte_count, (char*)sWideChar);
    if (rc)
      wide_string.SetLength(chunk_byte_count);
#else

    const int bTestByteOrder = false;
    const char* sNextUTF8;
    unsigned int error_status;
    const unsigned int error_mask = 0xFFFFFFFC;
    const ON__UINT32 error_code_point = 0xFFFD;

    for (int char_buffer_index=0; /*true*/; char_buffer_index = 1-char_buffer_index)
    {
      // Read UTF8 and convert to wide_char
      char_buffer_count[1-char_buffer_index] = 0;

      int char_count = buffer_capacity - char_buffer_count[char_buffer_index];
      if (char_count > chunk_byte_count)
        char_count = chunk_byte_count;
      if (char_count > 0)
      {
        if (false == ReadChar(char_count, char_buffer[char_buffer_index] + char_buffer_count[char_buffer_index]))
          break;
        chunk_byte_count -= char_count;
        char_buffer_count[char_buffer_index] += char_count;
      }
      else if (chunk_byte_count > 0)
      {
        // This should never happend and is probably a bug.
        // If it occurs due to invalid input, describe the situation
        // in this comment.
        ON_ERROR("char buffer reading stalled.");
        break;
      }

      if (chunk_byte_count > 0 && buffer_capacity == char_buffer_count[char_buffer_index])
      {
        // There are more bytes to read from the archive.
        char c = char_buffer[char_buffer_index][buffer_capacity - 1];
        if (c < 0 || c > 127)
        {
          // c is the second or later byte  in a UTF-8 muli-byte encoding.
          //
          // There are more bytes to read from the archive and it is possible there are more
          // trailing bytes to be read from the archive.  Back up to the beginning of the
          // this multi-byte encoded code point, move the bytes to char_buffer[1-char_buffer_index],
          // and decode them after the next read. 
          for (int i = buffer_capacity - 2; i > 0; i--)
          {
            c = char_buffer[char_buffer_index][i];
            if (c >= 0 && c <= 127)
            {
              // c is the beginning of a UTF-8 encoding sequence.
              char_buffer_count[1 - char_buffer_index] = buffer_capacity - i;
              char_buffer_count[char_buffer_index] = i;
              for (i = 0; i < char_buffer_count[1 - char_buffer_index]; i++)
                char_buffer[1 - char_buffer_index][i] = char_buffer[char_buffer_index][char_buffer_count[char_buffer_index] + i];
              break;
            }
          }
          if (c < 0 || c > 127)
          {
            // 512 bytes of with the hight bit set is not what was written and it cannot be an "overly long" UTF-8 encoding.
            // The arcive contents have been damaged.
            ON_ERROR("archive contents damaged.");
            break;
          }
        }
      }

      error_status = 0;
      sNextUTF8 = nullptr;
      int WideChar_count = ON_ConvertUTF8ToWideChar(
        bTestByteOrder,
        char_buffer[char_buffer_index],
        char_buffer_count[char_buffer_index],
        sWideChar_buffer,
        buffer_capacity,
        &error_status,
        error_mask,
        error_code_point,
        &sNextUTF8
        );
      if (WideChar_count <= 0 || WideChar_count > buffer_capacity)
      {
        ON_ERROR("Invalid UTF-8 encoding - incomplete string read.");
        // Not serious enough to terminate reading.
        rc = true;
        break;
      }

      wide_string.Append(sWideChar_buffer,WideChar_count);

      if ( chunk_byte_count > 0 )
        continue;

      rc = true;
      break;
    }
#endif
    break;
  }
  
  if (!EndRead3dmChunk())
    rc = false;
  
  return rc;
}

bool
ON_BinaryArchive::WriteString( const ON_wString& s )
{
  // No matter what size wchar_t is, this function writes a UTF-16 encoded string
  // to the archive.
#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_PUSH
// Disable the MSC /W4 "conditional expression is constant" warning
// about 2 == sizeof(wchar_t).  Since this code has to run on machines
// where sizeof(wchar_t) can be 2, 4, or ... bytes, the test is necessary.
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4127 )
#endif

  // The ON_wString::IsValid call prevents corrupt strings from breaking file IO
  // The parameter MUST be false here.
  s.IsValid(false);

  // NOTE WELL:
  //   In some cases there are embedded nulls in strings.
  size_t string_element_count = s.Length();
  if ( string_element_count > 0)
    string_element_count++;
  bool rc = false;
  if ( string_element_count <= 1 )
  {
    ON__UINT32 ui32 = 0;
    rc = WriteInt32(1,(ON__INT32*)&ui32);
  }
  else if ( 2 == sizeof(wchar_t) && string_element_count > 0 ) 
  {
    ON__UINT32 ui32 = (ON__UINT32)string_element_count;
    rc = WriteInt32(1,(ON__INT32*)&ui32);
    if (rc)
      rc = WriteInt16( string_element_count, (const ON__INT16*)s.Array() );
  }
  else if ( 4 == sizeof(wchar_t) && string_element_count > 0 )
  {
    // Assume the string is UTF-32 encoded (this is the case for some gcc implementations).
    const int bTestByteOrder = false;
    const ON__UINT32* sUTF32 = (const ON__UINT32*)s.Array();
    const int sUTF32_count = (int)(string_element_count-1);
    const unsigned int error_mask = 0xFFFFFFFF;
    const ON__UINT32 error_code_point = 0xFFFD; 
    unsigned int error_status = 0;

    const int sUTF16_count = ON_ConvertUTF32ToUTF16(
      bTestByteOrder,
      sUTF32,
      sUTF32_count,
      0, // ON__UINT16* sUTF16,
      0, // int sUTF16_count,
      &error_status,
      error_mask,
      error_code_point,
      0 // const ON__UINT32** sNextUTF32
      );

    if ( sUTF16_count > 0 )
    {
      error_status = 0;
      ON_SimpleArray<ON__UINT16> utf16_buffer(sUTF16_count+1);
      utf16_buffer.SetCount(sUTF16_count+1);
      const int sUTF16_count1 = ON_ConvertUTF32ToUTF16(
        bTestByteOrder,
        sUTF32,
        sUTF32_count,
        utf16_buffer.Array(),
        utf16_buffer.Count(),
        &error_status,
        error_mask,
        error_code_point,
        0 // const ON__UINT32** sNextUTF32
        );
      if ( sUTF16_count1 == sUTF16_count )
      {
        utf16_buffer[sUTF16_count] = 0;
        const ON__UINT32 ui32 = (ON__UINT32)(sUTF16_count+1);
        rc = WriteInt32(1,(const ON__INT32*)&ui32);
        if ( rc && ui32 > 0 )
          rc = WriteInt16( ui32, (const ON__INT16*)utf16_buffer.Array() );
      }
    }
  }
  return rc;  

#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_POP
#endif
}

bool ON_BinaryArchive::WriteArray( const ON_SimpleArray<bool>& a )
{
#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_PUSH
// Disable the MSC /W4 "conditional expression is constant" warning
// about sizeof(*c) == sizeof(*b).  Since this code has to run on machines
// where sizeof(bool) can be 1, 2, 4, or 8 bytes, the test is necessary.
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4127 )
#endif

  int count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );

  if ( rc && count > 0 ) 
  {
    char* p = 0;
    const char* c = 0;
    const bool* b = a.Array();
    if ( sizeof(*c) == sizeof(*b) )
    {
      // 8 bit "bool" on this compiler
      c = (char*)(b);
    }
    else if ( b )
    {
      // bigger "bool" on this compiler
      p = (char*)onmalloc(count*sizeof(*p));
      int i;
      for ( i = 0; i < count; i++ )
        p[i] = (b[i]?1:0);
      c = p;
    }
    rc = WriteChar( count, c );
    if ( p )
      onfree(p);
  }

  return rc;

#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_POP
#endif
}

bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<char>& a )
{
  int count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  if ( rc && count > 0 ) {
    rc = WriteChar( count, a.Array() );
  }
  return rc;
}

bool
ON_BinaryArchive::WriteArray(const ON_SimpleArray<ON__INT8>& a)
{
  int count = a.Count();
  if (count < 0)
    count = 0;
  bool rc = WriteInt(count);
  if (rc && count > 0) {
    rc = WriteChar(count, a.Array());
  }
  return rc;
}

bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON__INT16>& a )
{
  int count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  if ( rc && count > 0 ) {
    rc = WriteShort( count, a.Array() );
  }
  return rc;
}

bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON__INT32>& a )
{
  int count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  if ( rc && count > 0 ) {
    rc = WriteInt( count, a.Array() );
  }
  return rc;
}


bool
ON_BinaryArchive::WriteArray(const ON_SimpleArray<ON__UINT8>& a)
{
  int count = a.Count();
  if (count < 0)
    count = 0;
  bool rc = WriteInt(count);
  if (rc && count > 0) {
    rc = WriteChar(count, a.Array());
  }
  return rc;
}

bool
ON_BinaryArchive::WriteArray(const ON_SimpleArray<ON__UINT16>& a)
{
  int count = a.Count();
  if (count < 0)
    count = 0;
  bool rc = WriteInt(count);
  if (rc && count > 0) {
    rc = WriteShort(count, a.Array());
  }
  return rc;
}

bool
ON_BinaryArchive::WriteArray(const ON_SimpleArray<ON__UINT32>& a)
{
  int count = a.Count();
  if (count < 0)
    count = 0;
  bool rc = WriteInt(count);
  if (rc && count > 0) {
    rc = WriteInt(count, a.Array());
  }
  return rc;
}


bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<float>& a )
{
  int count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  if ( rc && count > 0 ) {
    rc = WriteFloat( count, a.Array() );
  }
  return rc;
}

bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<double>& a )
{
  int count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  if ( rc && count > 0 ) {
    rc = WriteDouble( count, a.Array() );
  }
  return rc;
}

bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON_Color>& a )
{
  int count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  if ( rc && count > 0 ) 
  {
    rc = WriteByte( 4*count, (const unsigned char*)a.Array() ); // WriteByte prevents big endian swaps
  }
  return rc;
}

bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON_2dPoint>& a )
{
  int count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  if ( rc && count > 0 ) {
    rc = WriteDouble( count*2, &a.Array()->x );
  }
  return rc;
}

bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON_3dPoint>& a )
{
  int count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  if ( rc && count > 0 ) {
    rc = WriteDouble( count*3, &a.Array()->x );
  }
  return rc;
}

bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON_4dPoint>& a )
{
  int count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  if ( rc && count > 0 ) {
    rc = WriteDouble( count*4, &a.Array()->x );
  }
  return rc;
}

bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON_2dVector>& a )
{
  int count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  if ( rc && count > 0 ) {
    rc = WriteDouble( count*2, &a.Array()->x );
  }
  return rc;
}


bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON_3dVector>& a )
{
  int count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  if ( rc && count > 0 ) {
    rc = WriteDouble( count*3, &a.Array()->x );
  }
  return rc;
}


bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON_Xform>& a )
{
  int count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  if ( rc && count > 0 ) 
  {
    int i;
    for ( i = 0; i < count && rc; i++ )
      rc = WriteXform(a[i]);
  }
  return rc;
}

bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON_2fPoint>& a )
{
  int count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  if ( rc && count > 0 ) {
    rc = WriteFloat( count*2, &a.Array()->x );
  }
  return rc;
}

bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON_3fPoint>& a )
{
  int count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  if ( rc && count > 0 ) {
    rc = WriteFloat( count*3, &a.Array()->x );
  }
  return rc;
}

bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON_4fPoint>& a )
{
  int count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  if ( rc && count > 0 ) {
    rc = WriteFloat( count*4, &a.Array()->x );
  }
  return rc;
}

bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON_2fVector>& a )
{
  int count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  if ( rc && count > 0 ) {
    rc = WriteFloat( count*2, &a.Array()->x );
  }
  return rc;
}

bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON_3fVector>& a )
{
  int count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  if ( rc && count > 0 ) {
    rc = WriteFloat( count*3, &a.Array()->x );
  }
  return rc;
}


bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON_SurfaceCurvature>& a )
{
  int count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  if ( rc && count > 0 ) {
    rc = WriteDouble( count*2, &a.Array()->k1 );
  }
  return rc;
}

bool
ON_BinaryArchive::WriteArray( const ON_SimpleArray<ON_ClippingPlaneInfo>& a )
{
  int count = a.Count();
  if ( count < 0 )
    count = 0;
  bool rc = WriteInt( count );
  for ( int i = 0; i < count && rc ; i++ )
  {
    rc = a[i].Write(*this);
  }
  return rc;
}


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

bool
ON_BinaryArchive::WriteObject( const ON_Object* o )
{
  bool rc = false;
  if ( o )
    rc = WriteObject(*o);
  else {
    // nullptr object has nil UUID and no date
    rc = BeginWrite3dmChunk( TCODE_OPENNURBS_CLASS, 0 );
    if (rc) {
      rc = BeginWrite3dmChunk( TCODE_OPENNURBS_CLASS_UUID, 0 );
      if ( rc ) {
        rc = WriteUuid( ON_nil_uuid );
        if ( !EndWrite3dmChunk() ) // end of TCODE_OPENNURBS_CLASS_UUID chunk
          rc = false;
      }
      if ( !EndWrite3dmChunk() )
        rc = false;
    }
  }
  return rc;
}

bool ON_BinaryArchive::ShouldSerializeUserDataItem(
    ON_UUID application_id,
    ON_UUID item_id
    ) const
{
  if (application_id == ON_nil_uuid)
    return false;

  if (m_user_data_filter.Count() <= 0)  //ALB - Retaining the less-than from previous code although it seems spurious.
    return true;                        //Empty filter, always serialize. See docs for m_user_data_filter
  
  //Validate the assumptions on the docs for m_user_data_filter.
  ON_ASSERT(m_user_data_filter[0].m_application_id == ON_nil_uuid);
  ON_ASSERT(m_user_data_filter[0].m_item_id == ON_nil_uuid);
  ON_ASSERT(m_user_data_filter[0].m_precedence == 0);

  // {31F55AA3-71FB-49f5-A975-757584D937FF}
  static const ON_UUID ON_V4V5_MeshNgonUserData_ID =
  { 0x31F55AA3, 0x71FB, 0x49f5, { 0xA9, 0x75, 0x75, 0x75, 0x84, 0xD9, 0x37, 0xFF } };

  // Userdata that must be saved even when userdata saving is "off".
  // Please discuss any changes with Dale Lear.  In particular,
  // "critical" is used in a narrow sense and modifying this 
  // function to save in form of plug-in's user data saved is
  // not appropriate.  The definition of the user data class must
  // be in the opennurbs library and its purpose must be to extend
  // a core opennurbs data structure, usually because it was the
  // only way to add information to core opennurbs data structure
  // and not break the public C++ SDK.

  unsigned int opennurbs_userdata_application_version = ON_IsOpennurbsApplicationId(application_id);
  if (opennurbs_userdata_application_version >= 4)
  {
    // The user data is opennurbs "core" user data
    unsigned int opennurbs_file_application_version = Archive3dmVersion();
    if (opennurbs_file_application_version > 10 && 0 == opennurbs_file_application_version % 10)
      opennurbs_file_application_version /= 10;

    if (   opennurbs_userdata_application_version >= 5
        && opennurbs_file_application_version >= 5
        && opennurbs_userdata_application_version <= opennurbs_file_application_version
       )
    {
      // As of 30 August 2012, all the core opennurbs user data
      // classes with an application id of ON_opennurbs5_id are
      // deemed "critical" for V5 files.
      return true;
    }

    if (4 == opennurbs_userdata_application_version
      && opennurbs_file_application_version <= 5
      && opennurbs_file_application_version >= 4
      && ON_V4V5_MeshNgonUserData_ID == item_id
      )
    {
      // ON_V4V5_MeshNgonUserData is the only "critical" core 
      // opennurbs user data with an application id of 
      // ON_opennurbs4_id and is saved only in V4 and V5 files.
      return true;
    }
  }

  //See the previous version of this code.
  const bool bReturnNilItemIdImmediately = (m_3dm_version > 0);

  bool bSerialize = m_user_data_filter[0].m_bSerialize;
  bool bFoundNilItemId  = false;

  const int last = m_user_data_filter.Count() - 1;

  for (int i = last; i > 0; i--)  //ALB: Backwards.  The first element of the table is special and should not be considered.
  {
    const ON_UserDataItemFilter& filter_item = m_user_data_filter[i];

    if (application_id == filter_item.m_application_id)
    {
      const bool bNilId = item_id == ON_nil_uuid;

      if (item_id == filter_item.m_item_id || (bNilId && bReturnNilItemIdImmediately))
      {
        bSerialize = filter_item.m_bSerialize;
        break;
      }

      if (bNilId && !bFoundNilItemId)
      {
        bFoundNilItemId = true;
        bSerialize = filter_item.m_bSerialize;
      }
    }
  }

  return bSerialize;
}

bool ON_BinaryArchive::ShouldSerializeUserDataDefault() const
{
  // Default setting is always the first element in the m_user_data_filter[] array.
  return (m_user_data_filter.UnsignedCount() > 0) ? m_user_data_filter[0].m_bSerialize : true;
}

bool ON_BinaryArchive::SetShouldSerializeUserDataDefault(
  bool bSerialize
  )
{
  if (0 != this->m_3dm_version)
    return false; // once reading/writing begins, the settings cannot be changed

  if (0 == m_user_data_filter.UnsignedCount())
  {
    m_user_data_filter.AppendNew().m_bSerialize = bSerialize;
  }
  else
  {
    m_user_data_filter[0].m_bSerialize = bSerialize;
  }

  return true;
}

bool ON_BinaryArchive::SetShouldSerializeUserDataItem(
  ON_UUID application_id,
  ON_UUID item_id,
  bool bSerializeUserDataItem
  )
{
  if (0 != this->m_3dm_version)
    return false; // once reading/writing begins, the settings cannot be changed

  if (ON_nil_uuid == application_id)
    return false;

  if (0 == m_user_data_filter.UnsignedCount())
  {
    m_user_data_filter.AppendNew().m_bSerialize = true;
  }

  if (ON_nil_uuid == application_id && ON_nil_uuid == item_id)
  {
    m_user_data_filter[0].m_bSerialize = bSerializeUserDataItem ? true : false;
    return true;
  }

  ON_UserDataItemFilter& f = m_user_data_filter.AppendNew();
  f.m_application_id = application_id;
  f.m_item_id = item_id;
  f.m_bSerialize = bSerializeUserDataItem ? true : false;
  f.m_precedence = m_user_data_filter.UnsignedCount() - 1;

  return true;
}

bool ON_BinaryArchive::ShouldWriteUserDataItem(
  const class ON_Object* object,
  const class ON_UserData* ud
  ) const
{
  if (nullptr == object)
    return false;
  if (nullptr == ud)
    return false;
  if (object != ud->Owner())
    return false;

  if (false == ShouldSerializeUserDataItem(
    ud->m_application_uuid,
    ud->m_userdata_uuid))
    return false;

  return ud->WriteToArchive(*this, object);
}

bool ON_BinaryArchive::ShouldSerializeNoUserData() const
{
  const unsigned int count = m_user_data_filter.UnsignedCount();
  if (count <= 0)
    return false; // All user data is serialized

  const ON_UserDataItemFilter *f = m_user_data_filter.Array();
  for (unsigned int i = 0; i < count; i++)
  {
    if (false != f[i].m_bSerialize)
      return false;// some type of user data is serialized
  }

  return true;
}

bool ON_BinaryArchive::ShouldSerializeAllUserData() const
{
  const unsigned int count = m_user_data_filter.UnsignedCount();
  if (count <= 0)
    return true; // All user data is serialized

  const ON_UserDataItemFilter *f = m_user_data_filter.Array();
  for (unsigned int i = 0; i < count; i++)
  {
    if (false == f[i].m_bSerialize)
      return false;// some type of user data is not serialized
  }

  return true;
}


bool ON_BinaryArchive::ShouldSerializeSomeUserData() const
{
  const unsigned int count = m_user_data_filter.UnsignedCount();
  if (count <= 0)
    return false; // All user data is serialized

  const ON_UserDataItemFilter *f = m_user_data_filter.Array();
  for (unsigned int i = 0; i < count; i++)
  {
    if (false != f[i].m_bSerialize)
      return true; // some type of user data is serialized
  }

  return false; // No user data is serialized
}


bool ON_BinaryArchive::ObjectHasUserDataToWrite(const ON_Object* object) const
{
  if (nullptr == object)
    return false;

  for (const ON_UserData* ud = object->FirstUserData(); 0 != ud; ud = ud->Next())
  {
    if (ShouldWriteUserDataItem(object, ud))
      return true;
  }

  return false;
}

static
bool IsCoreUserData( const ON_UserData* ud )
{
  // Userdata with IO code we trust.
  if ( 0 == ud )
    return false;
  
  if (ON_IsRhinoApplicationId(ud->m_application_uuid) > 0)
    return true;

  if (ON_IsOpennurbsApplicationId(ud->m_application_uuid) > 0)
    return true;

  return false;
}

bool
ON_BinaryArchive::WriteObject( const ON_Object& model_object )
{
  // writes polymorphic object derived from ON_Object in a way that
  // it can be recreated from ON_BinaryArchive::ReadObject

  if ( m_3dm_version >= 1 && m_3dm_version <= 50 )
  {
    const ON::object_type model_object_type = model_object.ObjectType();
    switch (model_object_type)
    {
    case ON::object_type::curve_object:
      {
        if (m_3dm_version > 2)
          break;
        const ON_Curve* curve = static_cast<const ON_Curve*>(&model_object);
        if (nullptr == curve)
          break;
        if (nullptr != ON_NurbsCurve::Cast(curve))
          break;
        ON_NurbsCurve nurbs_curve;
        if (curve->GetNurbForm(nurbs_curve)
          && nurbs_curve.Order() >= 2
          && nurbs_curve.CVCount() >= nurbs_curve.Order()
          && nurbs_curve.Dimension() >= 1
          )
        {
          return Internal_WriteObject(nurbs_curve);
        }
      }
      break;

    case ON::object_type::surface_object:
      {
        if (m_3dm_version > 2)
          break;
        const ON_Surface* surface = static_cast<const ON_Surface*>(&model_object);
        if (nullptr == surface)
          break;
        if (nullptr != ON_NurbsSurface::Cast(surface))
          break;
        ON_NurbsSurface nurbs_surface;
        if (surface->GetNurbForm(nurbs_surface)
          && nurbs_surface.Order(0) >= 2
          && nurbs_surface.Order(1) >= 2
          && nurbs_surface.CVCount(0) >= nurbs_surface.Order(0)
          && nurbs_surface.CVCount(1) >= nurbs_surface.Order(1)
          && nurbs_surface.Dimension() >= 1
          )
        {
          return Internal_WriteObject(nurbs_surface);
        }
      }
      break;

    case ON::extrusion_object:
      {
        if (m_3dm_version > 4)
          break;
        // 29 September 2010 Dale Lear
        //   ON_Extrusion was added in V5.  It must be translated
        //   to a brep or surface to save it in a V4 file.
        const ON_Extrusion* extrusion = ON_Extrusion::Cast(&model_object);
        if (nullptr == extrusion)
          break;
        ON_Object* V4_object = nullptr;
        if (extrusion->IsCapped() || extrusion->ProfileCount() >= 2)
          V4_object = extrusion->BrepForm(0);
        if (nullptr == V4_object)
        {
          if (m_3dm_version >= 4)
            V4_object = extrusion->SumSurfaceForm(0);
          if (nullptr == V4_object)
            V4_object = extrusion->NurbsSurface(0);
          if (nullptr == V4_object)
            break;
        }
        const bool rc = Internal_WriteObject(*V4_object);
        delete V4_object;
        return rc;
      }
      break;

    case ON::annotation_object:
      {
        const ON_Annotation* V6_annotation = ON_Annotation::Cast(&model_object);
        if (nullptr != V6_annotation)
          return Internal_WriteV5AnnotationObject(*V6_annotation, nullptr);
        if (m_3dm_version > 2)
          break;

        const ON_OBSOLETE_V5_Annotation* V5_annotation = ON_OBSOLETE_V5_Annotation::Cast(&model_object);
        if (nullptr != V5_annotation)
          return Internal_WriteV2AnnotationObject(*V5_annotation, nullptr);
      }
      break;

    case ON::object_type::text_dot:
      {
        if (m_3dm_version > 2)
          break;
        const ON_TextDot* text_dot = ON_TextDot::Cast(&model_object);
        if (nullptr == text_dot)
          break;
        ON_OBSOLETE_V2_TextDot V2_text_dot;
        V2_text_dot.point = text_dot->CenterPoint();
        V2_text_dot.m_text = text_dot->PrimaryText();
        return Internal_WriteObject(V2_text_dot);
      }
      break;
    default:
      break;
    }
  }
  
  return Internal_WriteObject(model_object);
}


bool ON_BinaryArchive::Internal_WriteV5AnnotationObject(
  const ON_Annotation& V6_annotation,
  const ON_3dmAnnotationContext* annotation_context
)
{
  if (m_3dm_version < 1 || m_3dm_version > 50)
  {
    ON_ERROR("m_3dm_version must be bewtween 1 and 5");
    return false;
  }

  // TODO:
  //  If V6_annotation has overrides, figure out how to find the archive index.
  //  Right now, dim style override information is lost when saving a V5 3dm archive.

  const ON_DimStyle* dim_style = nullptr;
  const ON_UUID model_dim_style_id = V6_annotation.DimensionStyleId();
  int V5_3dm_archive_dim_style_index = ON_UNSET_INT_INDEX;
  if (ON_nil_uuid != model_dim_style_id)
  {
    for (unsigned int i = 0; i < m_archive_dim_style_table.UnsignedCount(); i++)
    {
      const ON_DimStyle* model_dim_style = m_archive_dim_style_table[i];
      if (nullptr != model_dim_style && model_dim_style_id == model_dim_style->Id())
      {
        dim_style = model_dim_style;
        V5_3dm_archive_dim_style_index = i;
        break;
      }
    }
    if (nullptr == dim_style)
    {
      const ON_DimStyle& system_dim_style = ON_DimStyle::SystemDimstyleFromId(model_dim_style_id);
      if (model_dim_style_id == system_dim_style.Id())
      {
        dim_style = &system_dim_style;
        V5_3dm_archive_dim_style_index = system_dim_style.Index();
      }
    }
  }

  const ON_DimStyle* override_style = nullptr;

  if (nullptr == dim_style)
  {
    dim_style = &this->ArchiveCurrentDimStyle();
    V5_3dm_archive_dim_style_index = dim_style->Index();
  }
  else if (V6_annotation.HasDimensionStyleOverrides() && dim_style->IdIsNotNil() && dim_style->Id() == V6_annotation.DimensionStyleId())
  {
    const ON_DimStyle& v6_override_style = V6_annotation.DimensionStyle(*dim_style);
    if (v6_override_style.ParentId() == dim_style->Id() && v6_override_style.HasOverrides())
    {
      const ON_SHA1_Hash override_content_hash = v6_override_style.ContentHash();
      for (unsigned int i = 0; i < m_archive_dim_style_table.UnsignedCount(); i++)
      {
        const ON_DimStyle* model_dim_style = m_archive_dim_style_table[i];
        if (dim_style->Id() != model_dim_style->ParentId())
          continue;
        if (override_content_hash != model_dim_style->ContentHash())
          continue;
        override_style = model_dim_style;
        V5_3dm_archive_dim_style_index = i;
        break;
      }
    }
  }

  m_annotation_context.SetReferencedDimStyle(
    dim_style,
    override_style,
    V5_3dm_archive_dim_style_index
  );
  if (nullptr == annotation_context)
    annotation_context = &m_annotation_context;

  ON_OBSOLETE_V5_Annotation* V5_annotation = ON_OBSOLETE_V5_Annotation::CreateFromV6Annotation( V6_annotation, annotation_context );
  bool rc;
  if (nullptr != V5_annotation)
  {
    if (m_3dm_version <= 2)
      rc = Internal_WriteV2AnnotationObject(*V5_annotation,annotation_context);
    else
      rc = Internal_WriteObject(*V5_annotation);
    delete V5_annotation;
  }
  else
  {
    rc = Internal_WriteObject(V6_annotation);
  }

  return rc;
}

bool ON_BinaryArchive::Internal_WriteObject(
  const ON_Object& model_object
)
{
  const ON_ClassId* pID = model_object.ClassId();
  if ( nullptr == pID )
  {
    ON_ERROR("archive_object->ClassId() is nullptr.");
    return false;
  }
    
  if (false == BeginWrite3dmChunk(TCODE_OPENNURBS_CLASS, 0))
    return false;

  bool rc = false;
  for (;;)
  {
    // TCODE_OPENNURBS_CLASS_UUID chunk contains class's UUID 
    if (false == BeginWrite3dmChunk(TCODE_OPENNURBS_CLASS_UUID, 0))
      break;
    const ON_UUID object_class_id = pID->Uuid();
    bool bChunkIdOk = WriteUuid(object_class_id);
    if (false == EndWrite3dmChunk()) // end of TCODE_OPENNURBS_CLASS_UUID chunk
      bChunkIdOk = false;
    if (false == bChunkIdOk)
      break;

    // TCODE_OPENNURBS_CLASS_DATA chunk contains definition of class
    if (false == BeginWrite3dmChunk(TCODE_OPENNURBS_CLASS_DATA, 0))
      break;
    bool bChunkDataOk = model_object.Write(*this) ? true : false;
    if (false == bChunkDataOk)
    {
      ON_ERROR("archive_object->Write() failed.");
    }
    if (false == EndWrite3dmChunk()) // end of TCODE_OPENNURBS_CLASS_DATA chunk
      bChunkDataOk = false;
    if (false == bChunkDataOk)
      break;

    if ( ObjectHasUserDataToWrite(&model_object) )
    {
      // write user data.  Each piece of user data is in a 
      // TCODE_OPENNURBS_CLASS_USERDATA chunk.
      if (false == WriteObjectUserData(model_object))
        break;
    }

    // TCODE_OPENNURBS_CLASS_END chunk marks end of class record
    if (false == BeginWrite3dmChunk(TCODE_OPENNURBS_CLASS_END, 0))
      break;
    if (false == EndWrite3dmChunk())
      break;

    rc = true;
    break;
  }

  if (false == EndWrite3dmChunk()) // end of TCODE_OPENNURBS_CLASS chunk
    rc = false;

  return rc;
}


bool ON_BinaryArchive::WriteObjectUserData( const ON_Object& object )
{
  if ( m_3dm_version < 3 )
  {
    // no user data is saved in V1 and V2 files.
    return true;
  }

  const bool bSaveAllUserData = ShouldSerializeAllUserData();
  const bool bSaveSelectedUserData = bSaveAllUserData ? false : ShouldSerializeSomeUserData();
  const bool bHasWritableUserData = (bSaveAllUserData || ObjectHasUserDataToWrite(&object));

  // writes user data attached to object.
  bool rc = true;
  const ON_UserData* ud;
  ON_UUID userdata_classid;

  ON_UserData* delete_this_ud = 0;
  
  for (ud = object.FirstUserData(); ud && rc; ud = ud->m_userdata_next) 
  {
    if (0 != delete_this_ud)
    {
      if (delete_this_ud->m_userdata_next == ud)
      {
        if (const_cast<ON_Object&>(object).DetachUserData(delete_this_ud))
          delete delete_this_ud;
      }
      delete_this_ud = 0;
    }

    if (ud->DeleteAfterWrite(*this,&object))
      delete_this_ud = const_cast< ON_UserData* >(ud);

    if (false == bHasWritableUserData)
      continue;

    if (!ud->WriteToArchive(*this,&object))
      continue;

    // LOTS of tests to weed out bogus user data
    if ( 0 == ON_UuidCompare( ud->m_userdata_uuid, ON_nil_uuid ) )
      continue;
    if ( &object != ud->m_userdata_owner )
      continue;
    const ON_ClassId* cid = ud->ClassId();
    if ( 0 == cid )
      continue;
    if ( cid == &ON_CLASS_RTTI(ON_UserData) )
      continue;
    if ( cid == &ON_CLASS_RTTI(ON_Object) )
      continue;

    // The UserDataClassUuid() function is used instead of 
    // calling cid->Uuid() so we get the value of the 
    // plug-in's class id when the plug-in is not loaded
    // and ud is ON_UnknownUserData.
    userdata_classid = ud->UserDataClassUuid();
    if ( 0 == ON_UuidCompare( userdata_classid, ON_nil_uuid ) )
      continue;
    if ( 0 == ON_UuidCompare( userdata_classid, ON_CLASS_ID(ON_UserData) ) )
      continue;
    if ( 0 == ON_UuidCompare( userdata_classid, ON_CLASS_ID(ON_Object) ) )
      continue;
    if (0 == ON_UuidCompare(userdata_classid, ON_CLASS_ID(ON_UnknownUserData)))
      continue;
    if (0 == ON_UuidCompare(userdata_classid, ON_CLASS_ID(ON_ObsoleteUserData)))
      continue;

    if ( 3 == m_3dm_version )
    {
      // When saving a V3 archive and the user data is not
      // native V3 data, make sure the plug-in supports
      // writing V3 user data.
      if ( m_V3_plugin_id_list.BinarySearch( &ud->m_application_uuid, ON_UuidCompare ) < 0 )
        continue;
    }

    if (false == bSaveAllUserData 
        && false == ShouldSerializeUserDataItem(ud->m_application_uuid, ud->m_userdata_uuid)
       )
      continue;

    if ( ON_UuidIsNil( ud->m_application_uuid ) )
    {
      // As of version 200909190 - a non-nil application_uuid is 
      // required in order for user data to be saved in a 
      // 3dm archive.
      ON_Error(__FILE__,__LINE__,"Not saving %s userdata - m_application_uuid is nil.",cid->ClassName());
      continue; 
    }

    // See if we have unknown user data (goo) and make sure
    // IsUnknownUserData() agrees with ON_UnknownUserData::Cast().
    const ON_UnknownUserData* unknown_ud = ON_UnknownUserData::Cast(ud);
    if ( 0 == unknown_ud )
    {
      if ( ud->IsUnknownUserData() )
      {
        ON_ERROR("ON_UnknownUserData::Cast(ud) is null and ud->IsUnknownUserData() is true.");
        continue; // something's wrong
      }
    }
    else
    {
      if ( !ud->IsUnknownUserData() )
      {
        ON_ERROR("ON_UnknownUserData::Cast(ud) is not null and ud->IsUnknownUserData() is false.");
        continue; // something's wrong
      }
    }

    if ( 0 != unknown_ud )
    {
      if (false == bSaveAllUserData && false == bSaveSelectedUserData)
        continue; // unknown user data cannot be critical

      if ( unknown_ud->m_3dm_version <= 3 )
        continue; // Unknown will not be resaved in V3 archives

      if ( unknown_ud->m_3dm_version > 5 && unknown_ud->m_3dm_version < 50 )
        continue;

      if ( unknown_ud->m_3dm_opennurbs_version_number < 200701010 )
        continue;

      if ( unknown_ud->m_3dm_version >= 50 && m_3dm_version < 50 )
      {
        // Unknown userdata with 8 byte chunk lengths cannot be
        // saved into a V4 file with 4 byte chunk lengths because
        // the resulting chunk will be unreadable in V4.
        // This is not an error condition.  It is a consequence
        // of V4 IO code not being robust enough to handle
        // 8 bytes chunk lengths.
        continue;
      }
    }

    // Each piece of user data is inside of 
    // a TCODE_OPENNURBS_CLASS_USERDATA chunk.
    rc = BeginWrite3dmChunk( TCODE_OPENNURBS_CLASS_USERDATA, 0 );
    if (rc) {
      rc = Write3dmChunkVersion(2,2);
      // wrap user data header info in an TCODE_OPENNURBS_CLASS_USERDATA_HEADER chunk
      rc = BeginWrite3dmChunk( TCODE_OPENNURBS_CLASS_USERDATA_HEADER, 0 );
      if (rc) 
      {
        if ( rc ) rc = WriteUuid( userdata_classid );
        if ( rc ) rc = WriteUuid( ud->m_userdata_uuid );
        if ( rc ) rc = WriteInt( ud->m_userdata_copycount );
        if ( rc ) rc = WriteXform( ud->m_userdata_xform );

        // added for version 2.1
        if ( rc ) rc = WriteUuid( ud->m_application_uuid );

        // added for version 2.2 - 14, October 2009
        if ( rc )
        {
          rc = WriteBool( unknown_ud ? true : false );
          // ver = 2,3,4,50,60,...
          const int file_format_ver = unknown_ud ? unknown_ud->m_3dm_version : m_3dm_version;
          rc = WriteInt(file_format_ver);
          // ver = opennurbs version number
          unsigned int app_ver = unknown_ud ? unknown_ud->m_3dm_opennurbs_version_number : m_3dm_opennurbs_version;
          unsigned int app_ver_to_write = ON_BinaryArchive::ArchiveOpenNURBSVersionToWrite(file_format_ver, app_ver);
          if (rc) rc = WriteInt(app_ver_to_write);
        }

        if ( !EndWrite3dmChunk() )
          rc = false;
      }
      if (rc) 
      {
        // wrap user data in an anonymous chunk
        rc = BeginWrite3dmChunk( TCODE_ANONYMOUS_CHUNK, 0 );
        if ( rc ) 
        {
          if ( 0 != unknown_ud )
          {
            // 22 January 2004 Dale Lear
            //   Disable crc checking when writing the
            //   unknow user data block.
            //   This has to be done so we don't get an extra
            //   32 bit CRC calculated on the block that
            //   ON_UnknownUserData::Write() writes.  The
            //   original 32 bit crc is at the end of this
            //   block and will be checked when the class
            //   that wrote this user data is present.
            //   The EndWrite3dmChunk() will reset the
            //   CRC checking flags to the appropriate
            //   values.
            m_chunk.Last()->m_do_crc16 = 0;
            m_chunk.Last()->m_do_crc32 = 0;
            m_bDoChunkCRC = false;
          }

          if (m_user_data_depth < 0)
          {
            ON_ERROR("m_user_data_depth < 0");
            m_user_data_depth = 0;
          }
          m_user_data_depth++;
          rc = ud->Write(*this)?true:false;
          m_user_data_depth--;
          if ( !EndWrite3dmChunk() )
            rc = false;
        }
      }
      if ( !EndWrite3dmChunk() )
        rc = false;
    }
  }


  if (0 != delete_this_ud)
  {
    if (0 == delete_this_ud->m_userdata_next)
    {
      if (const_cast<ON_Object&>(object).DetachUserData(delete_this_ud))
        delete delete_this_ud;
    }
    delete_this_ud = 0;
  }

  return rc;
}

int
ON_BinaryArchive::LoadUserDataApplication( ON_UUID application_id )
{
  // This is a virtual function.
  // Rhino overrides this function to load plug-ins.
  return 0;
}

int ON_BinaryArchive::ReadObject( ON_Object** ppObject )
{
  if ( nullptr == ppObject ) 
  {
    ON_ERROR("ON_BinaryArchive::ReadObject() called with nullptr ppObject.");
    return 0;
  }
  *ppObject = nullptr;
  return ReadObjectHelper(ppObject);
}

int ON_BinaryArchive::ReadObject( ON_Object& object )
{
  ON_Object* pObject = &object;
  return ReadObjectHelper(&pObject);
}


int ON_BinaryArchive::ReadObjectHelper( ON_Object** ppObject )
{
  // returns 0: failure - unable to read object because of file IO problems
  //         1: success
  //         3: unable to read object because it's UUID is not registered
  //            this could happen in cases where old code is attempting to read
  //            new objects.
  ON__UINT32 tcode;
  ON__INT64 length_TCODE_OPENNURBS_CLASS = 0;
  ON__INT64 length_TCODE_OPENNURBS_CLASS_UUID = 0;
  ON__INT64 length_TCODE_OPENNURBS_CLASS_DATA = 0;
  ON_UUID uuid;
  const ON_ClassId* pID = 0;
  ON_Object* pObject = *ppObject; // If not null, use input
  const bool bDestinationIsManaged = (nullptr == pObject);
  const ON__INT64 sizeof_chunk_header = (ON__INT64)(4 + SizeofChunkLength());
  const ON__INT64 expected_length_TCODE_OPENNURBS_CLASS_UUID = 20;

  //bool bBogusUserData = false;

  // all ON_Objects written by WriteObject are in a TCODE_OPENNURBS_CLASS chunk
  if ( false == BeginRead3dmBigChunk( &tcode, &length_TCODE_OPENNURBS_CLASS ) )
    return 0;

  // When a nullptr ON_Object is written, the file has
  // 
  //  TCODE_OPENNURBS_CLASS, length = 20 + sizeof_chunk_header
  //  TCODE_OPENNURBS_CLASS_UUID, length = 20
  //    16 byte nil uuid
  //    4 byte TCODE_OPENNURBS_CLASS_UUID crc
  //
  // When a non-nullptr ON_Object is written, the file has
  // 
  //  TCODE_OPENNURBS_CLASS, length = 20 + 3*sizeof_chunk_header + length_DATA_chunk + length_USER_DATA_chunk(s)
  //
  //    TCODE_OPENNURBS_CLASS_UUID, length = 20
  //      16 byte nil uuid
  //      4 byte TCODE_OPENNURBS_CLASS_UUID crc
  //
  //    TCODE_OPENNURBS_CLASS_DATA, length_DATA >= 4
  //      ...
  //      4 byte TCODE_OPENNURBS_CLASS_DATA crc
  //
  //    Optional TCODE_OPENNURBS_CLASS_USERDATA chunks
  //
  //    TCODE_OPENNURBS_CLASS_END, chunk value = 0

  int rc = 0; // return 0 indicates error
  if ( tcode != TCODE_OPENNURBS_CLASS ) 
  {
    ON_ERROR("ON_BinaryArchive::ReadObject() didn't find TCODE_OPENNURBS_CLASS block.");
  }
  else if ( length_TCODE_OPENNURBS_CLASS < expected_length_TCODE_OPENNURBS_CLASS_UUID + sizeof_chunk_header) 
  {
    ON_ERROR("ON_BinaryArchive::ReadObject() TCODE_OPENNURBS_CLASS chunk length too small.");
  }
  else 
  {
    // we break out of this loop if something bad happens
    for (;;) 
    {
      // read class's UUID ///////////////////////////////////////////////////////////
      bool bClassIdRead = false;
      if (false == BeginRead3dmBigChunk(&tcode, &length_TCODE_OPENNURBS_CLASS_UUID))
      {
        break;
      }
      for (;;)
      {
        if (tcode != TCODE_OPENNURBS_CLASS_UUID)
        {
          ON_ERROR("ON_BinaryArchive::ReadObject() didn't find TCODE_OPENNURBS_CLASS_UUID block");
          break;
        }
        if (expected_length_TCODE_OPENNURBS_CLASS_UUID != length_TCODE_OPENNURBS_CLASS_UUID)
        {
          ON_ERROR("ON_BinaryArchive::ReadObject() TCODE_OPENNURBS_CLASS_UUID has invalid length");
          break;
        }
        if (false == ReadUuid(uuid))
        {
          break;
        }
        bClassIdRead = true;
        break;
      }
      if (false == EndRead3dmChunk())
      {
        break;
      }
      if (false == bClassIdRead)
        break;
      ///////////////////////////////////////////////////////////////////////////////

      rc = 1;
      if ( !ON_UuidCompare( &uuid, &ON_nil_uuid ) ) 
      {
        // nil UUID written if nullptr pointer is passed to WriteObject();
        break;
      }

      // Use UUID to get ON_ClassId for this class //////////////////////////////////
      if ( nullptr != pObject )
      {
        pID = pObject->ClassId();
        if ( nullptr == pID ) 
        {
          // pObject is not properly defined. This is a C++ source code error
          // or the data segment is corrupt.
          ON_WARNING(" pObject->ClassId() returned nullptr.");
          rc = 3;
          break;
        }
        if ( nullptr != pID && uuid != pID->Uuid() )
        {
          ON_ERROR("ON_BinaryArchive::ReadObject() - uuid does not match intput pObject's class id.");
          pID = 0;
          rc = 2;
          break;
        }
      }
      else
      {
        pID = ON_ClassId::ClassId( uuid );
      }

      if ( nullptr == pID ) 
      {
        // If you get here and you are not calling ON::Begin() at some point in your
        // executable, then call ON::Begin() to force all class definition to be linked.
        // If you are callig ON::Begin(), then either the uuid is garbage or you are 
        // attempting to read an object with old code.
        // Visit http://www.opennurbs.org to get the latest OpenNURBS code.
        ON_WARNING("ON_BinaryArchive::ReadObject() ON_ClassId::ClassId(uuid) returned nullptr.");
        rc = 3;
        break;
      }
      ///////////////////////////////////////////////////////////////////////////////

      // read class's definitions   /////////////////////////////////////////////////
      if (false == BeginRead3dmBigChunk(&tcode, &length_TCODE_OPENNURBS_CLASS_DATA))
      {
        rc = 0;
        break;
      }

      bool bSuppressPartiallyReadChunkWarning = false;
      if ( tcode != TCODE_OPENNURBS_CLASS_DATA )
      {
        ON_ERROR("ON_BinaryArchive::ReadObject() didn't find TCODE_OPENNURBS_CLASS_DATA block");
        rc = 0;
      }
      else if ( length_TCODE_OPENNURBS_CLASS_DATA <= 0  )
      {
        ON_ERROR("ON_BinaryArchive::ReadObject() TCODE_OPENNURBS_CLASS_DATA chunk length too small");
        rc = 0;
      }
      else 
      {
        if ( nullptr == pObject )
        {
          pObject = pID->Create();
        }
        if ( nullptr == pObject ) 
        {
          ON_ERROR("ON_BinaryArchive::ReadObject() pID->Create() returned nullptr.");
          rc = 0;
        }
        else 
        {
          if ( false == (pObject->Read(*this) ? true : false) ) 
          {
            rc = 0;
            ON_ERROR("ON_BinaryArchive::ReadObject() pObject->Read() failed.");
            if ( bDestinationIsManaged )
              delete pObject;
            // don't break here - we still need to call end chunk.
          }
          else 
          {
            *ppObject = pObject;
            if (
              nullptr != ON_InstanceDefinition::Cast(pObject)
              && 60 == Archive3dmVersion() 
              && ArchiveOpenNURBSVersion() <= 2348834153
              )
            {
              // April 2016
              // The ON_InstanceDefinition Read()/Write() code for V5 and early V6 WIPs was
              // written more than 10 years ago and was not wrapped in an internal chunk.
              // Attempts to use it for V6 IO failed. 
              // Setting bSuppressPartiallyReadChunkWarning = true here suppresses a 
              // false warning when files saved by early V6 WIPs are read.
              bSuppressPartiallyReadChunkWarning = true;
            }
          }
        }
      }

      if ( false == EndRead3dmChunk(bSuppressPartiallyReadChunkWarning) )
      {
        rc = 0;
      }

      if ( 0 != rc && nullptr != pObject )
      {
        // read user data  /////////////////////////////////////////////////
        //   If TCODE_OPENNURBS_CLASS_USERDATA chunks exist, this reads them.
        //   ReadObjectUserData() stops when it reads a TCODE_OPENNURBS_CLASS_END chunk.
        if ( false == ReadObjectUserData(*pObject) )
          rc = 0;
      }

      break; 
    }
  }

  if ( false == EndRead3dmChunk() ) // TCODE_OPENNURBS_CLASS
    rc = 0;

  return rc;
}


bool ON_BinaryArchive::ReadObjectUserDataAnonymousChunk( 
          const ON__UINT64 length_TCODE_ANONYMOUS_CHUNK,
          const int archive_3dm_version,
          const unsigned int archive_opennurbs_version,
          ON_UserData* ud )
{
  // Reads the portion of the file containing the userdata into a buffer
  // and lets the plug-in try to read from that.  If the plug-in fails,
  // we press on because we cannot trust plug-ins to get IO code right.
  bool rc = false;
  bool bChunkReadSuccess = true;

  if ( 0 == ud )
    return false;

  if ( ud->IsUnknownUserData()
       || (archive_3dm_version == Archive3dmVersion() 
           && archive_opennurbs_version == ArchiveOpenNURBSVersion() 
           && IsCoreUserData(ud))
     )
  {
    // assume this userdata's read function is robust.
    ON_ReadChunkHelper ch(*this,bChunkReadSuccess);
    if (    !bChunkReadSuccess
         || TCODE_ANONYMOUS_CHUNK != ch.m_chunk_tcode
         || length_TCODE_ANONYMOUS_CHUNK != (ON__UINT64)ch.m_chunk_value
       )
    {
      return false;
    }
    if ( ud->IsUnknownUserData() )
    {
      // 22 January 2004 Dale Lear:
      //   Disable CRC checking while reading this chunk.  
      //   (If the user data has nested chunks, the crc we get
      //   by reading the thing as one large chunk will be wrong.)
      ON_3DM_BIG_CHUNK* c = m_chunk.Last();
      const ON__UINT64 sizeof_CRC = c->SizeofCRC();
      m_chunk.Last()->m_do_crc16 = false;
      m_chunk.Last()->m_do_crc32 = false;
      m_bDoChunkCRC = false;
      if (c->m_bLongChunk
        && sizeof_CRC > c->SizeofCRC()
        && c->m_start_offset + c->Length() == c->m_end_offset + sizeof_CRC
        )
      {
        c->m_end_offset += sizeof_CRC;
      }
    }

    if (m_user_data_depth < 0)
    {
      ON_ERROR("m_user_data_depth < 0");
      m_user_data_depth = 0;
    }
    m_user_data_depth++;
    rc = ud->Read(*this) ? true : false;
    m_user_data_depth--;
  }
  else
  {
    // Untrusted plug-in userdata.
    // Insulate file reading from possible bugs plug-in IO code by reading
    // entire anonymous chunk into memory and letting the plug-in use
    // the memory buffer archive.
    unsigned char stack_buffer[2048];
    const size_t sizeof_buffer = (size_t)(length_TCODE_ANONYMOUS_CHUNK + 4 + SizeofChunkLength());
    void* freeme = 0;
    void* buffer = (sizeof_buffer <= sizeof(stack_buffer))
                 ? &stack_buffer[0]
                 : (freeme = onmalloc(sizeof_buffer)); // generally, object userdata is small we almost never use heap
    if ( 0 != buffer 
         && sizeof_buffer == ReadBuffer(sizeof_buffer,buffer)
       ) 
    {
      ON_Read3dmBufferArchive memory_archive(
        sizeof_buffer,
        buffer,
        false,
        archive_3dm_version,
        archive_opennurbs_version
        );

      // The TCODE_ANONYMOUS_CHUNK wrapper has chunk lengths set 
      // by whatever version wrote this file.  The information
      // in the chunk has chunk lengths set by the plug-in that
      // originally wrote the user data.  If the plug-in used
      // worte to a version <= 5 archive and the user data has
      // was read as goo and saved as goo in a version 50+
      // archive, then we need to tweak the archive version
      // when reading the chunk length of the TCODE_ANONYMOUS_CHUNK wrapper.
      bool bTweakArchiveVersion = (memory_archive.SizeofChunkLength() != SizeofChunkLength());
      if ( bTweakArchiveVersion )
        memory_archive.SetArchive3dmVersion(Archive3dmVersion());
      ON_ReadChunkHelper ch(memory_archive,bChunkReadSuccess);
      if ( bTweakArchiveVersion )
        memory_archive.SetArchive3dmVersion(archive_3dm_version);

      if (    !bChunkReadSuccess
           || TCODE_ANONYMOUS_CHUNK != ch.m_chunk_tcode
           || length_TCODE_ANONYMOUS_CHUNK != (ON__UINT64)ch.m_chunk_value
         )
        rc = false;
      else
      {
        if (m_user_data_depth < 0)
        {
          ON_ERROR("m_user_data_depth < 0");
          m_user_data_depth = 0;
        }
        m_user_data_depth++;
        rc = ud->Read(memory_archive) ? true : false;
        m_user_data_depth--;
      }
    }
    if ( freeme )
      onfree(freeme);
  }

  if ( !bChunkReadSuccess )
    rc = false;

  return rc;
}


class CUserDataHeaderInfo
{
public:
  CUserDataHeaderInfo();

  void Initialize();

  ON_UUID m_classid;
  ON_UUID m_itemid;
  ON_UUID m_appid;
  int m_3dm_version;
  int m_3dm_opennurbs_version_number;
  int m_copycount;
  bool m_bLastSavedAsGoo;
  ON_Xform m_xform;
};

CUserDataHeaderInfo::CUserDataHeaderInfo()
{
  Initialize();
}

void CUserDataHeaderInfo::Initialize()
{
  memset(this,0,sizeof(*this));
}

static
bool ReadObjectUserDataHeaderHelper( 
          ON_BinaryArchive& binary_archive,
          const int major_userdata_version,
          const int minor_userdata_version,
          CUserDataHeaderInfo& ud_header
          )
{
  bool rc = true;
  ON__UINT32 t = 0;
  ON__INT64 length_TCODE_OPENNURBS_CLASS_USERDATA_HEADER = 0;

  ud_header.Initialize();

  if ( major_userdata_version == 2 )
  {
    // major_userdata_version 2 started wrapping the userdata header info 
    // in a TCODE_OPENNURBS_CLASS_USERDATA_HEADER chunk
    rc = binary_archive.BeginRead3dmBigChunk( &t, &length_TCODE_OPENNURBS_CLASS_USERDATA_HEADER );
    if (!rc)
      return false;
    if ( t != TCODE_OPENNURBS_CLASS_USERDATA_HEADER )
    {
      ON_ERROR("version 2.0 TCODE_OPENNURBS_CLASS_USERDATA chunk is missing TCODE_OPENNURBS_CLASS_USERDATA_HEADER chunk.");
      binary_archive.EndRead3dmChunk(); // end of mystery chunk
      return false;
    }
  }
  
  if (rc) rc = binary_archive.ReadUuid( ud_header.m_classid );
  if (rc) rc = binary_archive.ReadUuid( ud_header.m_itemid );
  if (rc) rc = binary_archive.ReadInt( &ud_header.m_copycount );
  if (rc) rc = binary_archive.ReadXform( ud_header.m_xform );
  if ( major_userdata_version == 2 ) 
  {
    if ( minor_userdata_version >= 1 )
    {
      if (rc) rc = binary_archive.ReadUuid( ud_header.m_appid );
      if ( minor_userdata_version >= 2 )
      {
        // bLastSavedAsGoo is true if the user data was saved
        // into the file by ON_UnknownUserData.
        if (rc) rc = binary_archive.ReadBool( &ud_header.m_bLastSavedAsGoo ); 
        if (rc) rc = binary_archive.ReadInt( &ud_header.m_3dm_version );
        if (rc) rc = binary_archive.ReadInt(&ud_header.m_3dm_opennurbs_version_number);
      }
    }
    if ( !binary_archive.EndRead3dmChunk() ) // end of TCODE_OPENNURBS_CLASS_USERDATA_HEADER
      rc = 0;
  }

  if (!rc)
  {
    ON_ERROR("Unable to read user data header information.");
    return false;
  }

  if (0 == ud_header.m_3dm_version || 0 == ud_header.m_3dm_opennurbs_version_number)
  {
    // The userdata was saved in in an archive before
    // the 3dm_version and 3dm_opennurbs_version were saved in
    // userdata headers.  This means it has to be userdata
    // with 4 byte chunk lengths.  If the archive we are
    // reading was written with a newer version of opennurbs
    // that does save the 3dm version info, then this unknown
    // userdata was that has persisted through multiple read/write 
    // cycles and we cannot tell it's original version. So we
    // will default to a maximum of 5 and 200910180 - the 
    // 3dm versions just before we started saving 3dm 
    // version info n userdata headers.
    if ( binary_archive.Archive3dmVersion() < 50 )
    {
     ud_header.m_3dm_version = binary_archive.Archive3dmVersion();
    }
    else
    {
      // All Archive3dmVersion() >= 50 have userdata_3dm_version info,
      // so this userdata had to be saved as goo from a version 5 or
      // earlier archive.
      ud_header.m_bLastSavedAsGoo = true;
      ud_header.m_3dm_version = 5;
    }
    ud_header.m_3dm_opennurbs_version_number = binary_archive.ArchiveOpenNURBSVersion();
    if (ud_header.m_3dm_opennurbs_version_number >= 200910190)
    {
      ud_header.m_3dm_opennurbs_version_number = 200910180;
      ud_header.m_bLastSavedAsGoo = true;
    }
  }

  return rc;
}

bool ON_BinaryArchive::ReadObjectUserData( ON_Object& object )
{
  bool rc = true;
  bool bChunkReadSuccess = true;
  while(rc && bChunkReadSuccess) 
  {
    // Note:
    //  The destructor ~ON_ReadChunkHelper() may set bChunkReadSuccess
    //  An example of this case occures when reading the corrupt file
    //  attached to bug report RH-22547.
    ON_ReadChunkHelper ch(*this,bChunkReadSuccess);
    if ( !bChunkReadSuccess )
    {
      rc = false;
      break;
    }

    if ( TCODE_OPENNURBS_CLASS_END == ch.m_chunk_tcode )
    {
      // A short TCODE_OPENNURBS_CLASS_END chunk marks the end of the opennurbs class
      break; // done
    }

    if ( TCODE_OPENNURBS_CLASS_USERDATA != ch.m_chunk_tcode )
    {
      if ( 0 == ch.m_chunk_tcode )
      {
        // A short TCODE_OPENNURBS_CLASS_END chunk marks the end of the opennurbs class
        // Checking for zero here fixes RH-22547 which was a report of Rescue3dm taking
        // hours to read a damaged file that was filled with large blocks of zeros 
        // caused by some form of storage media or tranmission corruption.
        rc = false; // there should never be a typecode of zero.
        break;
      }

      // skip new chunk type added by later version
      continue;
    }

    if ( ch.m_chunk_value < (ON__INT64)(8 + 4 * SizeofChunkLength()) )
    {
      ON_ERROR("TCODE_OPENNURBS_CLASS_USERDATA chunk is too short");
      continue;
    }

    // Read userdata header information
    int major_userdata_version = 0;
    int minor_userdata_version = 0;
    rc = Read3dmChunkVersion( &major_userdata_version, &minor_userdata_version );
    if ( !rc )
    {
      ON_ERROR("Unable to read TCODE_OPENNURBS_CLASS_USERDATA chunk version numbers");
      break;
    }

    if ( major_userdata_version < 1 || major_userdata_version > 2 )
    {
      // unsupported version - too old or added in new version
      continue;
    }

    CUserDataHeaderInfo ud_header;
    rc = ReadObjectUserDataHeaderHelper(*this,major_userdata_version,minor_userdata_version,ud_header);
    if (!rc)
    {
      ON_ERROR("Unable to read user data header information.");
      break;
    }

    // we should be ready to read a TCODE_ANONYMOUS_CHUNK containing userdata
    ON__INT64 length_TCODE_ANONYMOUS_CHUNK = 0;
    for(;;)
    {
      ON__UINT32 t = 0;
      rc = PeekAt3dmBigChunkType( &t, &length_TCODE_ANONYMOUS_CHUNK );
      if (!rc)
        break;
      if ( t != TCODE_ANONYMOUS_CHUNK )
      {
        ON_ERROR("Reading object user data - unable to find TCODE_ANONYMOUS_CHUNK");
        rc = false;
        break;
      }
      if ( length_TCODE_ANONYMOUS_CHUNK < 4 )
      {
        ON_ERROR("Reading object user data - length of TCODE_ANONYMOUS_CHUNK < 4");
        rc = false;
        break;
      }
      break;
    }
    if (!rc)
    {
      break;
    }

    if (false == ShouldSerializeUserDataItem(ud_header.m_appid, ud_header.m_itemid))
    {
      ch.m_bSupressPartiallyReadChunkWarning = true;
      continue;
    }

    // attempt to get an instance of the userdata class that saved this information
    ON_UserData* ud = 0;
    for(;;)
    {
      const ON_ClassId* udId = ON_ClassId::ClassId( ud_header.m_classid );
      if ( 0 == udId ) 
      {
        // The application that created this userdata is not active
        if ( !ON_UuidIsNil(ud_header.m_appid) )
        {
          // see if we can load the application
          if ( 1 == LoadUserDataApplication(ud_header.m_appid) )
          {
            // try again
            udId = ON_ClassId::ClassId( ud_header.m_classid );
          }
        }

        if ( 0 == udId )
        {
          // The application that created this user data is
          // not available.  This information will be stored
          // in an ON_UnknownUserData class so that it can
          // persist.
          udId = &ON_CLASS_RTTI(ON_UnknownUserData);
        }
      }

      ON_Object* tmp = udId->Create();
      ud = ON_UserData::Cast(tmp);
      if ( 0 == ud )
      {
        ON_ERROR("Reading object user data - unable to create userdata class");
        if ( tmp )
          delete tmp;
        tmp = 0;
        break;
      }
      tmp = 0;

      break;
    }

    if ( 0 == ud )
    {
      // no luck on this one 
      // One reason can be that the plug-in userdata class has something wrong with 
      // its ON_OBJECT_DECLARE/ON_OBJECT_IMPLEMENT stuff.
      ON_ERROR("Unable to create object user data class. Flawed class id information.");
      continue; // keep trying
    }

    if ( ON_UuidIsNil(ud->m_application_uuid) )
    {
      if ( ON_UuidIsNil(ud_header.m_appid) )
      {
        switch( Archive3dmVersion())
        {
        case 2:
          // V2 archives do not contain app ids.
          // This id flags the userdata as being read from a V3 archive.
          ud_header.m_appid = ON_v2_userdata_id;
          break;
        case 3:
          // V3 archives do not contain app ids.
          // This id flags the userdata as being
          // read from a V3 archive.
          ud_header.m_appid = ON_v3_userdata_id;
          break;
        case 4:
          if ( ArchiveOpenNURBSVersion() < 200909190 )
          {
            // V4 archives before version 200909190
            // did not require user data application ids.
            ud_header.m_appid = ON_v4_userdata_id;
          }
          break;
        }
      }
      ud->m_application_uuid = ud_header.m_appid;
    }
    ud->m_userdata_uuid = ud_header.m_itemid;
    ud->m_userdata_copycount = ud_header.m_copycount;
    ud->m_userdata_xform = ud_header.m_xform;
    if ( ud->IsUnknownUserData() ) 
    {
      ON_UnknownUserData* uud = ON_UnknownUserData::Cast(ud);
      if ( uud ) 
      {
        uud->m_sizeof_buffer = (int)length_TCODE_ANONYMOUS_CHUNK;
        uud->m_unknownclass_uuid = ud_header.m_classid;
        uud->m_3dm_version = ud_header.m_3dm_version;
        uud->m_3dm_opennurbs_version_number = ud_header.m_3dm_opennurbs_version_number;
      }
    }
    ud->m_userdata_owner = &object; // so reading code can look at owner
    bool bReadUserData = ReadObjectUserDataAnonymousChunk(
              length_TCODE_ANONYMOUS_CHUNK,
              ud_header.m_3dm_version,
              ud_header.m_3dm_opennurbs_version_number,
              ud
              );
    ud->m_userdata_owner = 0;
    if (bReadUserData)
    {
      if (ud->DeleteAfterRead(*this,&object))
      {
        // obsolete user data
        delete ud;
      }
      else if (!object.AttachUserData(ud))
      {
        // attach failed
        delete ud;
      }
    }
    else
    {
      delete ud;
    }    
  }

  if ( !bChunkReadSuccess )
    rc = false;

  return rc;
}

bool ON_BinaryArchive::Write3dmChunkVersion(
  int major_version, // major // 0 to 15
  int minor_version // minor // 0 to 16
  )
{
  const unsigned char v = (unsigned char)(major_version*16+minor_version);
  return WriteChar( v );
}

bool ON_BinaryArchive::Read3dmChunkVersion(
  int* major_version, // major // 0 to 15
  int* minor_version // minor // 0 to 16
  )
{
  unsigned char v = 0;
  bool rc = ReadChar( &v );
  if ( minor_version) *minor_version = v%16;
  // The bit shift happens on the fly in the following
  // if statement.  It was happening twice which always
  // set the major version to 0
  //v >>= 4;
  if ( major_version) *major_version = (v>>4);
  return rc;
}

int ON_BinaryArchive::Archive3dmVersion() const
{
  // 1,2,3,4,5,50,60,...
  return m_3dm_version;
}

unsigned int ON_BinaryArchive::ArchiveOpenNURBSVersion() const
{
  return m_3dm_opennurbs_version;
}

ON::RuntimeEnvironment ON_BinaryArchive::ArchiveRuntimeEnvironment() const
{
  return m_archive_runtime_environment;
}

size_t ON_BinaryArchive::ArchiveStartOffset() const
{
  return m_3dm_start_section_offset;
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

bool ON_BinaryArchive::BeginWrite3dmChunk( unsigned int typecode, int value )
{
  ON__INT64 value64 = 0;
  if ( 0 != value )
  {
    if ( ON_IsUnsignedChunkTypecode(typecode) )
    {
      // treat value parameter as an unsigned int
      ON__UINT32 u32 = (ON__UINT32)value;
      ON__UINT64 u64 = u32;
      value64 = (ON__INT64)u64;
    }
    else
    {
      // treat value paramter is a signed int
      value64 = value;
    }
  }
  return BeginWrite3dmBigChunk(typecode,value64);
}

bool ON_BinaryArchive::BeginWrite3dmBigChunk( ON__UINT32 typecode, ON__INT64 value64 )
{
  if (false == WriteMode())
  {
    ON_ERROR("WriteMode() = false.");
    return false;
  }
  m_bDoChunkCRC = false; // no CRC on chunks because length is written twice.
  bool rc = WriteInt32( 1, (ON__INT32*)&typecode );
  if (rc)
    rc = WriteChunkValue( typecode, value64 );
  if (rc)
    rc = PushBigChunk( typecode, value64 );
  return rc;
}

bool ON_BinaryArchive::BeginWrite3dmAnonymousChunk(
  int version
)
{
  const int major_version = 1;
  if (version < 0)
  {
    ON_ERROR("Incorrect version value.");
    return false;
  }
  return BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK, major_version, version);
}

bool ON_BinaryArchive::BeginRead3dmAnonymousChunk(
  int* version
)
{
  int major_version = 0;
  int minor_version = 0;
  bool rc = BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK, &major_version, &minor_version);
  if (rc && (1 != major_version || minor_version < 0))
  {
    ON_ERROR("Incorrect major_version value.");
    // BeginRead3dmChunk() was successful, so EndRead3dmChunk() must be called.
    // The archive is corrupt or this function is being used incorrectly.
    EndRead3dmChunk();
    rc = false;
  }
  if (nullptr != version)
  {
    *version = rc ? minor_version : -1;
  }
  return rc;
}


bool 
ON_BinaryArchive::BeginWrite3dmChunk(
          unsigned int tcode,
          int major_version,
          int minor_version
          )
{
  bool rc = false;
  if (false == WriteMode())
  {
    ON_ERROR("WriteMode() = false.");
  }
  else if ( 0 == tcode )
  {
    ON_ERROR("ON_BinaryArchive::BeginWrite3dmChunk - input tcode = 0");
  }
  else if ( 0 != (tcode & TCODE_SHORT) )
  {
    ON_ERROR("ON_BinaryArchive::BeginWrite3dmChunk - input tcode has short flag set.");
  }
  else if ( major_version <= 0 )
  {
    ON_ERROR("ON_BinaryArchive::BeginWrite3dmChunk - input major_version <= 0.");
  }
  else if ( minor_version < 0 )
  {
    ON_ERROR("ON_BinaryArchive::BeginWrite3dmChunk - input minor_version < 0.");
  }
  else
  {
    rc = BeginWrite3dmChunk(tcode,0);
    if (rc)
    {
      rc = WriteInt(major_version);
      if (rc)
        rc = WriteInt(minor_version);
      if ( !rc)
        EndWrite3dmChunk();
    }
  }
  return rc;
}

bool 
ON_BinaryArchive::EndWrite3dmChunk()
{
  if (false == WriteMode())
  {
    ON_ERROR("WriteMode() = false.");
    return false;
  }

  bool rc = false;
  ON_3DM_BIG_CHUNK* c = m_chunk.Last();
  if ( c ) 
  {
    if ( c->m_bLongChunk ) 
    {
      if ( c->m_do_crc16 ) 
      {
        // write 16 bit CRC
        unsigned char two_zero_bytes[2] = {0,0};
        ON__UINT16 crc = ON_CRC16( c->m_crc16, 2, two_zero_bytes );
        rc = WriteInt16( 1, (ON__INT16*)&crc );
        if (c->m_crc16) 
        {
          // should never happen unless ON_CRC16() code is damaged
          Internal_ReportCRCError();
          ON_ERROR("ON_BinaryArchive::EndWrite3dmChunk: CRC16 computation error.");
        }
      }
      else if ( c->m_do_crc32 ) 
      {
        // write 32 bit CRC
        const ON__UINT32 crc0 = c->m_crc32; 
        rc = WriteInt32( 1, (ON__INT32*)&crc0 );
      }
      else {
        rc = true;
      }

      // write length
      m_bDoChunkCRC = 0;
      const ON__UINT64 offset = CurrentPosition();
      if ( offset < c->m_start_offset ) 
      {
        ON_ERROR("ON_BinaryArchive::EndWrite3dmChunk() - chunk length < 0");
        rc = false;
      }
      else 
      {
        const bool bChunkBoundaryCheck = m_bChunkBoundaryCheck;

        // SeekBackward seeks to SizeofChunkLength() bytes before
        // the chunk data boundary to write the chunk length
        // The SeekForward() seeks 1 byte after the end of the chunk boundary.
        m_bChunkBoundaryCheck = false;

        ON__UINT64 length = (offset - c->m_start_offset);
        if ( !SeekBackward( length + SizeofChunkLength() ) ) 
        {
          rc = false;
        }
        else 
        {
          if ( !WriteChunkLength( length ) )
          {
            rc = false;
          }
          if ( !SeekForward( length ) ) 
          {
            rc = false;
          }
        }

        m_bChunkBoundaryCheck = bChunkBoundaryCheck;

        if ( CurrentPosition() != offset ) 
        {
          ON_ERROR("ON_BinaryArchive::EndWrite3dmChunk() - CurrentPosition() != offset");
          rc = false;
        }
      }
    }
    else 
    {
      // "short" chunks are completely written by call to BeginWrite3dmChunk().
      rc = true;
    }

    m_chunk.Remove();
    c = m_chunk.Last();
    if ( nullptr == c )
    {
      Flush();
      m_bDoChunkCRC = false;
    }
    else
    {
      if ( c->m_bLongChunk )
      {
        ON__UINT64 current_pos = CurrentPosition();
        if (current_pos > c->m_end_offset)
          c->m_end_offset = current_pos;
      }
      m_bDoChunkCRC = (c->m_do_crc16 || c->m_do_crc32);
    }
  }
  return rc;
}

bool ON_BinaryArchive::Write3dmGoo( const ON_3dmGoo& goo )
{
  bool rc = false;

  if ( goo.m_typecode ) {
    const bool savedDoCRC = m_bDoChunkCRC;
    m_bDoChunkCRC = false;
    if ( 0 != (goo.m_typecode & TCODE_SHORT) ) {
      if ( goo.m_value == 0 || (goo.m_value > 0 && goo.m_goo) ) {
        // write long chunk - do not use Begin/EndWrite3dmChunk() because
        //                    goo may contain subchunks and CRC would be
        //                    incorrectly computed.
        rc = WriteInt( goo.m_typecode );
        if (rc) rc = WriteInt( goo.m_value );
        if (rc && goo.m_value>0) rc = WriteByte( goo.m_value, goo.m_goo );
      }
    }
    else {
      // write short chunk
      rc = WriteInt( goo.m_typecode );
      if (rc) rc = WriteInt( goo.m_value );
    }
    m_bDoChunkCRC = savedDoCRC;
  }
  
  return rc;
}

bool ON_BinaryArchive::PeekAt3dmChunkType( unsigned int* typecode, int* value )
{
  // does not change file position
  bool rc;
  unsigned int tc = 0;
  ON__INT64 i64 = 0;
  rc = PeekAt3dmBigChunkType(&tc,&i64);
  if ( rc )
  {
    if ( 0 != typecode )
      *typecode = tc;
    if ( 0 != value )
    {
      ON__INT32 i32 = 0;
      if ( ON_IsUnsignedChunkTypecode(tc) )
        rc = DownSizeUINT((ON__UINT64)i64,(ON__UINT32*)&i32);
      else
        rc = DownSizeINT(i64,&i32);
      *value = i32;
    }
  }
  return rc;
}

bool ON_BinaryArchive::PeekAt3dmBigChunkType( 
      ON__UINT32* typecode,
      ON__INT64* big_value
      )
{
  // does not change file position

  // 10 January 2005 Dale Lear
  //     Do not let the "peeking" affect the CRC.
  const bool bDoChunkCRC = m_bDoChunkCRC;
  m_bDoChunkCRC = false;

  const ON__UINT64 pos0 = CurrentPosition();
  ON__UINT32 t = 0;
  ON__INT64 v = 0;

  const unsigned int saved_error_message_mask = m_error_message_mask;
  m_error_message_mask |= 0x01;
  bool rc = ReadChunkTypecode( &t );
  m_error_message_mask = saved_error_message_mask;
  if (false == rc)
    t = 0;

  if (rc) 
  {
    rc = ReadChunkValue( t, &v );
  }
  const ON__UINT64 pos1 = CurrentPosition();
  if ( pos1 > pos0 && !SeekBackward( pos1-pos0 ) )
  {
    rc = false;
  }

  m_bDoChunkCRC = bDoChunkCRC;

  if ( typecode )
    *typecode = t;
  if ( big_value )
    *big_value = v;

  return rc;
}


bool ON_BinaryArchive::Seek3dmChunkFromStart( 
      // beginning at the start of the active chunk, search portion of
      // archive included in active chunk for the start of a subchunk 
      // with the specified type.
      // if true is returned, then the position is set so the next call to
      // BeginRead3dmChunk() will read a chunk with the specified typecode
      unsigned int typecode   // typecode from opennurbs_3dm.h
      )
{
  bool rc = false;
  if ( ReadMode() ) 
  {
    const ON__UINT64 pos0 = CurrentPosition();
    const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
    if ( c ) 
    {
      // set archive position to the beginning of this chunk
      if ( !ON_IsLongChunkTypecode(c->m_typecode) ) 
      {
        ON_ERROR("ON_BinaryArchive::Seek3dmChunkFromStart() - current chunk is not a long chunk");
        return false;
      }
      if ( c->m_big_value < 0 ) 
      {
        ON_ERROR("ON_BinaryArchive::Seek3dmChunkFromStart() called with an active chunk that has m_value < 0");
        return false;
      }
      if ( pos0 < c->m_start_offset || pos0 > c->m_end_offset ) 
      {
        ON_ERROR("ON_BinaryArchive::Seek3dmChunkFromStart() called with out of bounds current position");
        return false;
      }
      rc = SeekBackward( pos0 - c->m_start_offset ); // pos0 >= c->m_offset, so this size_t subtraction is ok
    }
    else 
    {
      // set archive position to the beginning of archive chunks by skipping
      // 32 byte version info and any start section padding.
      size_t start_offset = ((m_3dm_start_section_offset > 0) ? m_3dm_start_section_offset : 0);
      rc = SeekFromStart( start_offset );
      if (!rc && start_offset > 0)
      {
        start_offset = 0;
        rc = SeekFromStart(start_offset);
      }
      char s3d[33];
      memset(s3d,0,sizeof(s3d));
      if (rc) 
        rc = ReadByte(32,s3d);

      if (rc)
      {
        rc = (0 == strncmp( s3d, "3D Geometry File Format ", 24));
        if ( !rc && start_offset > 0 )
        {
          start_offset = 0;
          rc = SeekFromStart(start_offset);
          if (rc) rc = ReadByte(32,s3d);
          rc = (0 == strncmp( s3d, "3D Geometry File Format ", 24));
        }
      }

      if (rc)
      {
        if ( start_offset != m_3dm_start_section_offset )
          m_3dm_start_section_offset = start_offset;
        unsigned int t=0;
        ON__INT64 v=-1;
        rc = PeekAt3dmBigChunkType(&t,&v);
        if (rc && (t != 1 || v < 0) )
          rc = false;
      }
    }

    if (rc) 
    {
      rc = Seek3dmChunkFromCurrentPosition( typecode );
    }

    if (!rc) 
    {
      SeekFromStart(pos0);
    }
  }
  return rc;
}

ON__UINT64 ON_3DM_BIG_CHUNK::Length() const
{
  return (ON_IsLongChunkTypecode(m_typecode) && m_big_value >= 0 )
    ? ((ON__UINT64)m_big_value)
    : 0;
}

ON__UINT64 ON_3DM_BIG_CHUNK::SizeofCRC() const
{
  const ON__UINT64 sizeof_crc = m_do_crc32 ? 4 : (m_do_crc16 ? 2 : 0);
  return sizeof_crc;
}


ON__UINT64 ON_3DM_BIG_CHUNK::LengthRemaining(
  ON__UINT64 current_position
) const
{
  if (0 == (TCODE_SHORT & m_typecode)
    && m_start_offset <= current_position
    && current_position <= m_end_offset)
  {
    return (m_end_offset - current_position);
  }

  return 0;
}

bool ON_BinaryArchive::Seek3dmChunkFromCurrentPosition( 
      // beginning at the current position, search portion of archive
      // included in active chunk for the start of a subchunk with the
      // specified type.
      // if true is returned, then the position is set so the next call to
      // BeginRead3dmChunk() will read a chunk with the specified typecode
      unsigned int typecode // typecode from opennurbs_3dm.h
      )
{
  bool rc = false;
  if ( ReadMode() ) 
  {
    const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
    const ON__UINT64 pos1 = c ? c->m_start_offset + c->Length() : 0;
    const ON__UINT64 pos_start = CurrentPosition();
    ON__UINT64 pos_prev = 0;
    ON__UINT64 pos = 0;
    unsigned int t;
    ON__INT64 v64;
    bool bFirstTime = true;
    while(pos > pos_prev || bFirstTime) 
    {
      bFirstTime = false;
      pos_prev = pos;
      pos = CurrentPosition();
      if ( pos1 && pos > pos1 )
        break;
      t = !typecode;
      if ( !PeekAt3dmBigChunkType( &t, 0 ) )
        break;
      if ( t == typecode ) 
      {
        rc = true;
        break;
      }
      if ( 0 == t )
      {
        // zero is not a valid typecode - file is corrupt at or before this position
        break;
      }
      if ( !BeginRead3dmBigChunk( &t, &v64 ) )
        break;
      if ( !EndRead3dmChunk() )
        break;
      if ( TCODE_ENDOFTABLE == t && 0 != v64 )
      {
        // TCODE_ENDOFTABLE chunks always have value = 0 - file is corrupt at or before this position
        break;
      }
    }
    if ( !rc ) 
    {
      SeekFromStart( pos_start );
    }
  }
  return rc;
}

bool ON_BinaryArchive::BeginRead3dmBigChunk( unsigned int* typecode, ON__INT64* value )
{
  if (false == ReadMode())
  {
    ON_ERROR("ReadMode() = false.");
    if (typecode)
      *typecode = 0;
    if (value)
      *value = 0;
    return false;
  }

  ON__UINT32 t = 0;
  ON__INT64 v = 0;
  m_bDoChunkCRC = false; // no CRC on chunk headers because length is written twice
  const unsigned int saved_error_message_mask = m_error_message_mask;
  m_error_message_mask |= 0x0001; // disable ReadByte() error message at EOF
  bool rc = ReadChunkTypecode( &t );
  m_error_message_mask = saved_error_message_mask;
  if (rc) 
  {
    if ( t == TCODE_ENDOFFILE ) 
    {
      // Either this chunk is a bona fide end of file mark, or it's "goo" 
      // that Rhino 1.0 or the pre-February 2000 Rhino 1.1 saved and wrote.
      ON__UINT64 sizeof_file = 0;
      if ( rc )
        rc = ReadChunkValue( t, &v );
      if ( rc && v >= 0 && ((ON__UINT64)v) >= SizeofChunkLength() ) 
      {
        ON__UINT64 EOF_chunk_length = (ON__UINT64)v;
        ON__UINT64 pos0 = CurrentPosition();
        rc = ReadEOFSizeOfFile( &sizeof_file );
        ON__UINT64 pos1 = CurrentPosition();
        if ( pos0 > 0 && pos1 > pos0 )
        {
          if ( !SeekBackward(pos1-pos0) )
            rc = false;
        }
        if ( rc ) 
        {
          if ( SeekForward( EOF_chunk_length ) )
          {
            ON__UINT64 pos2 = CurrentPosition(); 
            if ( m_3dm_version <= 1 )
            {
              if ( !AtEnd() ) 
              {
                // Rhino v1 reads chunks with unknown typecodes as a block of "goo"
                // and then saves them back into file.  When this happens to an
                // eof marker, we get TCODE_ENDOFFILE chunks in the middle of a file.
                // This can only happen in m_3dm_version = 1 files.
                t = TCODE_ENDOFFILE_GOO;
              }
            }
            else
            {
              // check that current position matches saved file size
              if ( pos2 != sizeof_file ) {
                ON_ERROR("ON_BinaryArchive::BeginRead3dmChunk() - Rogue eof marker in v2 file.\n");
              }
            }
            rc = SeekBackward( EOF_chunk_length );
          }
        }
        if ( rc )
          rc = PushBigChunk( t, v );
      }
      else 
      {
        ON_ERROR( "ON_BinaryArchive::BeginRead3dmChunk() - file is damaged." );
        rc = false;
        t = 0; // ?? file is trashed ??
      }
    }
    else 
    {
      if ( rc )
        rc = ReadChunkValue( t, &v );
      if ( rc )
        rc = PushBigChunk( t, v );
    }
  }
  if ( typecode )
    *typecode = t;
  if ( value )
    *value = v;
  return rc;
}

bool 
ON_BinaryArchive::BeginRead3dmChunk(
          unsigned int expected_tcode,
          int* major_version,
          int* minor_version
          )
{
  bool rc = false;
  if (false == ReadMode())
  {
    ON_ERROR("ReadMode() = false.");
  }
  else if ( 0 == expected_tcode )
  {
    ON_ERROR("ON_BinaryArchive::BeginRead3dmChunk - input expected_tcode = 0");
  }
  else if ( 0 != (expected_tcode & TCODE_SHORT) )
  {
    ON_ERROR("ON_BinaryArchive::BeginRead3dmChunk - input expected_tcode has short flag set.");
  }
  else if ( 0 == major_version )
  {
    ON_ERROR("ON_BinaryArchive::BeginRead3dmChunk - input major_version nullptr");
  }
  else if ( 0 == minor_version )
  {
    ON_ERROR("ON_BinaryArchive::BeginRead3dmChunk - input minor_version nullptr");
  }
  else
  {
    *major_version = 0;
    *minor_version = 0;
    unsigned int tcode = 0;
    ON__INT64 value = 0;
    rc = PeekAt3dmBigChunkType(&tcode,&value);
    if ( expected_tcode != tcode )
    {
      ON_ERROR("ON_BinaryArchive::BeginRead3dmChunk - unexpected tcode");
      rc = false;
    }
    else if ( value < 8 )
    {
      ON_ERROR("ON_BinaryArchive::BeginRead3dmChunk - unexpected chunk length");
      rc = false;
    }
    else
    {
      tcode = 0;
      value = 0;
      rc = BeginRead3dmBigChunk(&tcode,&value);
      if (rc)
      {
        if ( expected_tcode != tcode || value < 8 )
        {
          // can happen when seek fails
          ON_ERROR("ON_BinaryArchive::BeginRead3dmChunk - unexpected tcode or chunk length - archive driver or device may be bad");
          rc = false;
        }
        else
        {
          rc = ReadInt(major_version);
          if ( rc && *major_version < 1 )
          {
            ON_ERROR("ON_BinaryArchive::BeginRead3dmChunk - major_version < 1");
            rc = false;
          }
          if (rc)
          {
            rc = ReadInt(minor_version);
            if ( rc && *minor_version < 0 )
            {
              ON_ERROR("ON_BinaryArchive::BeginRead3dmChunk - minor_version < 0");
              rc = false;
            }
          }
        }

        if ( !rc )
        {
          // this is required to keep chunk accounting in synch
          EndRead3dmChunk();
        }
      }
    }
  }
  return rc;
}
bool ON_BinaryArchive::EndRead3dmChunk()
{
  return EndRead3dmChunk(false);
}

bool ON_BinaryArchive::EndRead3dmChunk(bool bSupressPartiallyReadChunkWarning)  
{
  if (false == ReadMode())
  {
    ON_ERROR("ReadMode() = false.");
    return false;
  }

  //int length = 0;
  bool rc = false;
  ON_3DM_BIG_CHUNK* c = m_chunk.Last();
  if ( c ) 
  {
    ON__UINT64 file_offset = CurrentPosition();
    ON__UINT64 end_offset = c->m_start_offset;
    if ( c->m_bLongChunk )
    {
      if ( c->m_big_value < 0 )
      {
        Internal_ReportCriticalError();
        ON_ERROR("ON_BinaryArchive::EndRead3dmChunk - negative chunk length");
      }
      else
      {
        end_offset += ((ON__UINT64)c->m_big_value);
      }
    }

    if ( c->m_bLongChunk ) 
    {
      const bool bChunkBoundaryCheck = m_bChunkBoundaryCheck;
      if ( c->m_do_crc16 ) 
      {
        if ( file_offset+2 == end_offset )
        {
          // read 16 bit CRC
          unsigned char two_crc_bytes[2] = {0,0};
          m_bChunkBoundaryCheck = false;
          rc = ReadByte( 2, two_crc_bytes );
          m_bChunkBoundaryCheck = bChunkBoundaryCheck;
          if (rc) 
          {
            file_offset+=2;
            if (c->m_crc16) 
            {
              Internal_ReportCRCError();
              ON_ERROR("ON_BinaryArchive::EndRead3dmChunk: CRC16 error.");
            }
          }
        }
        else
        {
          // partially read chunk - crc check not possible.
          rc = true;
        }
      }
      else if ( c->m_do_crc32 ) 
      {
        if ( file_offset+4 == end_offset )
        {
          // read 32 bit CRC
          ON__UINT32 crc1 = c->m_crc32;
          ON__UINT32 crc0;
          m_bChunkBoundaryCheck = false;
          rc = ReadInt32( 1, (ON__INT32*)&crc0 );
          m_bChunkBoundaryCheck = bChunkBoundaryCheck;
          if (rc) 
          {
            file_offset+=4;
            if (crc0 != crc1) 
            {
              Internal_ReportCRCError();
              ON_ERROR("ON_BinaryArchive::EndRead3dmChunk: CRC32 error.");
            }
          }
        }
        else
        {
          // partially read chunk - crc check not possible.
          rc = true;
        }
      }
      else 
      {
        // no crc in this chunk
        rc = true;
      }
    }
    else 
    {
      rc = true;
    }

    // check length and seek to end of chunk if things are amiss
    if ( file_offset < c->m_start_offset ) 
    {
      Internal_ReportCriticalError();
      ON_ERROR("ON_BinaryArchive::EndRead3dmChunk: current position before start of current chunk.");
      if ( !SeekFromStart( end_offset ) )
        rc = false;
    }
    else if ( file_offset > end_offset ) 
    {
      Internal_ReportCriticalError();
      ON_ERROR("ON_BinaryArchive::EndRead3dmChunk: current position after end of current chunk.");
      if ( !SeekFromStart( end_offset ) )
        rc = false;
    }
    else if ( file_offset != end_offset ) 
    {
      // partially read chunk - happens when chunks are skipped or old code
      // reads a new minor version of a chunk whnich has added information.
      if ( file_offset != c->m_start_offset ) 
      {
        if ( m_3dm_version != 1 || (m_error_message_mask&0x02) == 0 ) 
        {
          // when reading v1 files, there are some situations where
          // it is reasonable to attempt to read 4 bytes at the end
          // of a file.  The above test prevents making a call
          // to ON_WARNING() in these situations.

          unsigned int file_year = 0;
          unsigned int file_month = 0;
          unsigned int file_date = 0;
          unsigned int file_major_version = 0;
          const bool bHaveFileDate = ON_VersionNumberParse(
            m_3dm_opennurbs_version,
            &file_major_version,
            0,
            &file_year,
            &file_month,
            &file_date,
            0
            );

          const unsigned int file_ymd
            = bHaveFileDate
            ? ((file_year * 100 + file_month) * 100 + file_date)
            : 0;

          unsigned int app_year = 0;
          unsigned int app_month = 0;
          unsigned int app_date = 0;
          unsigned int app_major_version = 0;
          const bool bHaveAppDate = ON_VersionNumberParse(
            ON::Version(),
            &app_major_version,
            0,
            &app_year,
            &app_month,
            &app_date,
            0
            );

          const unsigned int app_ymd
            = bHaveAppDate
            ? ((app_year * 100 + app_month) * 100 + app_date)
            : 0;

          if (file_major_version <= app_major_version 
            && file_ymd <= app_ymd
            )
          {
            // We are reading a file written by this version or an
            // earlier version of opennurbs.  
            // There should not be any partially read chunks.
            if (!bSupressPartiallyReadChunkWarning)
            {
              ON_WARNING("ON_BinaryArchive::EndRead3dmChunk: partially read chunk - skipping bytes at end of current chunk.");
            }
          }
        }
      }

      const bool bChunkBoundaryCheck = m_bChunkBoundaryCheck;
      m_bChunkBoundaryCheck = false;
      if ( end_offset > file_offset )
      {
        if ( !SeekForward(end_offset - file_offset) )
          rc = false;
      }
      else if ( end_offset < file_offset )
      {
        if ( !SeekBackward(file_offset - end_offset) )
          rc = false;
      }
      m_bChunkBoundaryCheck = bChunkBoundaryCheck;

    }

    m_chunk.Remove();
    c = m_chunk.Last();
    m_bDoChunkCRC = (c && (c->m_do_crc16 || c->m_do_crc32));
  }
  return rc;
}

bool ON_BinaryArchive::BeginWriteDictionary(
        ON_UUID dictionary_id,
        unsigned int version,
        const wchar_t* dictionary_name
        )
{
#if defined(ON_COMPILER_MSC)
// Disable the MSC /W4 "conditional expression is constant" warning
// about sizeof(unsigned short) == sizeof(*dictionary_name).  
// Since this code has to run on machines where sizeof(wchar_t) 
// can be 2, 4, or 8 bytes, the test is necessary.
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4127 )
#endif

  bool rc = BeginWrite3dmChunk(TCODE_DICTIONARY,1,0);
  if ( !rc )
    return rc;

  // Write dictionary id chunk
  rc = BeginWrite3dmChunk(TCODE_DICTIONARY_ID,1,0);
  if ( rc )
  {
    for(;;)
    {
      rc = WriteUuid(dictionary_id);
      if (!rc) break;
      rc = WriteInt(version);
      if (!rc) break;
      if ( 2 == sizeof(*dictionary_name) )
      {
        rc = WriteUTF16String((const unsigned short*)dictionary_name);
      }
      else
      {
        ON_wString s(dictionary_name);
        rc = WriteString(s);
      }
      if (!rc) break;
      break;
    }
    if ( !EndWrite3dmChunk() ) // TCODE_DICTIONARY_ID end
      rc = false;
  }

  if ( !rc )
    EndWrite3dmChunk(); // TCODE_DICTIONARY end
  return rc;

#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_POP
#endif
}

bool ON_BinaryArchive::EndWriteDictionary()
{
  int chunk_count = m_chunk.Count();
  bool rc = ( chunk_count > 0 && TCODE_DICTIONARY == m_chunk[chunk_count-1].m_typecode );
  if (rc)
  {
    rc = BeginWrite3dmChunk(TCODE_DICTIONARY_END,0);
    if (rc)
      rc = EndWrite3dmChunk(); // TCODE_DICTIONARY_END

    if ( !EndWrite3dmChunk() ) // TCODE_DICTIONARY
      rc = false;
  }
  return rc;
}

bool ON_BinaryArchive::BeginWriteDictionaryEntry(
        int de_type, 
        const wchar_t* entry_name
        )
{
#if defined(ON_COMPILER_MSC)
// Disable the MSC /W4 "conditional expression is constant" warning
// about sizeof(unsigned short) == sizeof(*entry_name).  
// Since this code has to run on machines where sizeof(wchar_t) 
// can be 2, 4, or 8 bytes, the test is necessary.
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4127 )
#endif

  bool rc = BeginWrite3dmChunk(TCODE_DICTIONARY_ENTRY,0);
  if ( rc )
  {
    for(;;)
    {
      rc = WriteInt(de_type);
      if (!rc) break;
      if ( sizeof(unsigned short) == sizeof(*entry_name) )
      {
        rc = WriteUTF16String((const unsigned short*)entry_name);
      }
      else
      {
        ON_wString s(entry_name);
        rc = WriteString(s);
      }
      if (!rc) break;
      break;
    }
    if ( !rc )
      EndWrite3dmChunk(); // TCODE_DICTIONARY_ENTRY
  }
  return rc;

#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_POP
#endif
}

bool ON_BinaryArchive::EndWriteDictionaryEntry()
{
  int chunk_count = m_chunk.Count();
  bool rc = ( chunk_count > 0 && TCODE_DICTIONARY_ENTRY == m_chunk[chunk_count-1].m_typecode )
          ? EndWrite3dmChunk()
          : false;
  return rc;
}

bool ON_BinaryArchive::BeginReadDictionary(
        ON_UUID* dictionary_id,
        unsigned int* version,
        ON_wString& dictionary_name
        )
{
  int major_version = 0;
  int minor_version = 0;
  bool rc = BeginRead3dmChunk(TCODE_DICTIONARY,&major_version,&minor_version);
  if ( rc )
  {
    for(;;)
    {
      rc = (1 == major_version);
      if (!rc) break;

      // Read dictionary id chunk
      rc = BeginRead3dmChunk(TCODE_DICTIONARY_ID,&major_version,&minor_version);
      if ( !rc ) break;
      for(;;)
      {
        rc = (1==major_version);
        if (!rc) break;
        ON_UUID id;
        rc = ReadUuid(id);
        if (!rc) break;
        if ( dictionary_id )
          *dictionary_id = id;
        rc = ReadInt(version);
        if (!rc) break;
        rc = ReadString(dictionary_name);
        if (!rc) break;
        break;
      }
      if ( !EndRead3dmChunk() ) // TCODE_DICTIONARY_ID end
        rc = false;
      break;
    }

    if ( !rc )
      EndRead3dmChunk(); // TCODE_DICTIONARY end
  }
  return rc;
}

bool ON_BinaryArchive::EndReadDictionary()
{
  int chunk_count = m_chunk.Count();
  bool rc = ( chunk_count > 0 && TCODE_DICTIONARY == m_chunk[chunk_count-1].m_typecode )
          ? EndRead3dmChunk()
          : false;
  return rc;
}

int ON_BinaryArchive::BeginReadDictionaryEntry(
        int* de_type, 
        ON_wString& entry_name
        )
{
  unsigned int tcode = 0;
  ON__INT64 chunk_length = 0;
  int chunk_count = m_chunk.Count();
  int rc = ( chunk_count > 0 && TCODE_DICTIONARY == m_chunk[chunk_count-1].m_typecode )
          ? (BeginRead3dmBigChunk(&tcode,&chunk_length)?1:0)
          : 0;
  if ( de_type )
    *de_type = 0;
  if ( rc )
  {
    if ( TCODE_DICTIONARY_ENTRY == tcode )
    {
      for(;;)
      {
        rc = 0;
        if ( !ReadInt(de_type) )
        {
          entry_name.Empty();
          break;
        }
        if ( !ReadString(entry_name) )
        {
          entry_name.Empty();
          break;
        }
        rc = 1;
        break;
      }
    }
    else
    {
      rc = (TCODE_DICTIONARY_END == tcode) ? 2 : 0;
    }
    if ( 1 != rc )
    {
      if ( !EndRead3dmChunk() )
        rc = 0;
    }
  }
  return rc;
}

bool ON_BinaryArchive::EndReadDictionaryEntry()
{
  int chunk_count = m_chunk.Count();
  bool rc = ( chunk_count > 0 && TCODE_DICTIONARY_ENTRY == m_chunk[chunk_count-1].m_typecode )
          ? EndRead3dmChunk()
          : false;
  return rc;
}



bool ON_BinaryArchive::Read3dmGoo( ON_3dmGoo& goo )
{
  // goo is an entire "chunk" that is not short.
  // A call to EndRead3dmChunk() must immediately follow 
  // the call to Read3dmGoo().
  bool rc = false;
  if (goo.m_goo) 
  {
    onfree(goo.m_goo);
    goo.m_goo = 0;
  }
  goo.m_typecode = 0;
  goo.m_value = 0;
  ON_3DM_BIG_CHUNK* c = m_chunk.Last();
  if (c) 
  {
    goo.m_typecode = c->m_typecode;
    if ( c->m_bLongChunk )
      rc = DownSizeUINT(c->Length(),(ON__UINT32*)&goo.m_value);
    else
      rc = DownSizeINT(c->m_big_value,&goo.m_value);
    if ( rc && c->m_bLongChunk && c->m_big_value > 0 ) 
    {
      if ( CurrentPosition() == c->m_start_offset )
      {
        // read the rest of this chunk into the goo.m_goo buffer.
        // 23 January 2004 Dale Lear:
        //   Have to turn of CRC checking because the goo may contiain
        //   subchunks.  If a CRC exixts, it is at the end of the
        //   goo and will persist until the application that
        //   wrote this chunk is available to parse the chunk.
        c->m_do_crc16 = 0;
        c->m_do_crc32 = 0;
        m_bDoChunkCRC = false;
        size_t sizeof_goo = (size_t)c->Length();
        goo.m_goo = (unsigned char*)onmalloc( sizeof_goo );
        rc = ReadByte( sizeof_goo, goo.m_goo );
      }
    }
  }
  return rc;
}

bool ON_BinaryArchive::WriteChunkTypecode( ON__UINT32 typecode )
{
  return WriteInt32(1,(ON__INT32*)&typecode);
}

bool ON_BinaryArchive::ReadChunkTypecode( ON__UINT32* typecode )
{
  ON__UINT32 tc = 0;
  bool rc = ReadInt32(1,(ON__INT32*)&tc);
  if (rc && typecode )
    *typecode = tc;
  return rc;
}

bool ON_BinaryArchive::WriteChunkValue( ON__UINT32 typecode, ON__INT64 big_value )
{
  bool rc;
  if ( 8 == SizeofChunkLength() )
  {
    rc = WriteInt64(1,&big_value);
  }
  else if ( ON_IsUnsignedChunkTypecode(typecode) )
  {
    // treat big_value as an unsigned int
    ON__UINT32 u32 = 0;
    rc = DownSizeUINT((ON__UINT64)big_value,&u32);
    if ( !WriteInt32(1,(ON__INT32*)&u32) )
      rc = false;
  }
  else
  {
    // treat big_value as a signed int
    ON__INT32 v32 = 0;
    rc = DownSizeINT(big_value,&v32);
    if ( !WriteInt32(1,&v32) )
      rc = false;
  }
  return rc;
}


bool ON_BinaryArchive::WriteChunkLength( ON__UINT64 length )
{
  bool rc;
  if ( 8 == SizeofChunkLength() )
  {
    rc = WriteInt64(1,(ON__INT64*)&length);
  }
  else
  {
    ON__UINT32 u32 = 0;
    rc = DownSizeUINT(length,&u32);
    if ( !WriteInt32(1,(ON__INT32*)&u32) )
      rc = false;
  }
  return rc;
}

bool ON_BinaryArchive::ReadEOFSizeOfFile( ON__UINT64* sizeof_file )
{
  bool rc;
  ON__INT64 u64 = 0;
  if ( 8 == SizeofChunkLength() )
  {
    // file has a 8 byte file size
    rc = ReadInt64(1,(ON__INT64*)&u64);
  }
  else
  {
    // file has a 4 byte file size
    ON__UINT32 u32 = 0;
    rc = ReadInt32(1,(ON__INT32*)&u32);
    if ( rc )
      u64 = u32;
  }
  if ( rc && 0 != sizeof_file )
    *sizeof_file = u64;
  return rc;
}

bool ON_BinaryArchive::WriteEOFSizeOfFile( ON__UINT64 sizeof_file )
{
  bool rc;
  if ( 8 == SizeofChunkLength() )
  {
    // file has a 8 byte file size
    rc = WriteInt64(1,(ON__INT64*)&sizeof_file);
  }
  else
  {
    // file has a 4 byte file size
    ON__UINT32 u32=0;
    DownSizeUINT(sizeof_file,&u32);
    rc = WriteInt32(1,(ON__INT32*)&u32);
  }
  return rc;
}

bool ON_BinaryArchive::ReadChunkValue( ON__UINT32 typecode, ON__INT64* value64 )
{
  bool rc;
  ON__INT64 i64 = 0;
  if ( 8 == SizeofChunkLength() )
  {
    // file has a 8 byte chunk value
    rc = ReadInt64(1,&i64);
  }
  else
  {
    // file has a 4 byte chunk value
    if ( ON_IsUnsignedChunkTypecode(typecode) )
    {
      // This Mickey Mouse is here to convince all compilers 
      // that when we read a 4 byte value with the high bit set, 
      // the resulting i64 value is positive. I.e.,
      // 0xFFFFFFFF is converted to 0x00000000FFFFFFFF
      ON__UINT32 u32 = 0;
      ON__UINT64 u64 = 0;
      rc = ReadInt32(1,(ON__INT32*)&u32);
      if ( rc )
        u64 = u32;
      i64 = (ON__INT64)u64;
    }
    else
    {
      // If we read a 4 byte value with the high bit set,
      // the resulting i64 value is negative. I.e.,
      // -1 is converted to -1 (0xFFFFFFFF to 0xFFFFFFFFFFFFFFFF)
      ON__INT32 i32 = 0;
      rc = ReadInt32(1,&i32);
      i64 = i32;
    }
  }
  if ( rc && 0 != value64 )
    *value64 = i64;
  return rc;
}

bool ON_BinaryArchive::ChunkBoundaryCheck() const
{
  return m_bChunkBoundaryCheck;
}

void ON_BinaryArchive::SetChunkBoundaryCheck(
  bool bChunkBoundaryCheck
) 
{
  m_bChunkBoundaryCheck = bChunkBoundaryCheck ? true : false;
}

size_t ON_BinaryArchive::SizeofChunkLength() const
{
  // Version 1 - 4 and early version 5 files had
  // 4 byte chunk lengths.  In October of 2009,
  // 8 byte chunk lengths were phased in for V5
  // files.
  return (m_3dm_version < 50) ? 4 : 8;
}

bool ON_BinaryArchive::PushBigChunk( ON__UINT32 typecode, ON__INT64 big_value )
{
  ON_3DM_BIG_CHUNK c;
  memset(&c,0,sizeof(c));
  c.m_typecode  = typecode;
  c.m_big_value = big_value;
  ON__UINT64 length = 0;
  ON__UINT64 sizeof_crc = 0;

  // | and & are BITOPS - do NOT change to || and &&
  //
  // Some v1 files have a short chunk with typecode = 0.
  //
  // NOTE: RenderXXXX plug-in used zero as a typecode in material userdata, sigh ...
  // so ... const bool bLongChunk = (0 != typecode && 0 == (TCODE_SHORT & typecode)); doesn't work.
  //
  const bool bLongChunk = (0 == (TCODE_SHORT & typecode) && (0 != typecode || 1 != Archive3dmVersion()) && big_value >= 0 );
  if ( bLongChunk )
  {
    length = (ON__UINT64)big_value;

    if ( m_3dm_version == 1 && 0 != (TCODE_LEGACY_GEOMETRY & typecode) )
    {
      // these legacy typecodes have 16 bit CRCs
      c.m_do_crc16 = 1;
      c.m_crc16 = 1;
    }
    else 
    {
      // some other legacy typecodes that have 16 bit CRCs
      switch(typecode) 
      {

      case TCODE_SUMMARY:
        if ( m_3dm_version == 1 ) 
        {
          c.m_do_crc16 = 1;
          c.m_crc16 = 1;
        }
        break;

      case TCODE_OPENNURBS_OBJECT | TCODE_CRC | 0x7FFD:
        if ( m_3dm_version == 1 ) 
        {
          // 1.1 uuid has a 16 bit crc
          c.m_do_crc16 = 1;
          c.m_crc16 = 1;
        }
        else 
        {
          // 2.0 uuid has a 32 bit crc
          c.m_do_crc32 = 1;
          c.m_crc32 = 0;
        }
        break;

      default:
        if ( m_3dm_version != 1 && 0 != (TCODE_CRC & typecode) ) 
        {
          // 32 bit CRC
          c.m_do_crc32 = 1;
          c.m_crc32 = 0;
        }
        break;

      }
    }

    c.m_bLongChunk = 1;
    sizeof_crc = c.m_do_crc32 ? 4 : (c.m_do_crc16 ? 2 : 0);
  }

  c.m_start_offset = CurrentPosition();
  c.m_end_offset = c.m_start_offset;
  if (ReadMode() && length > sizeof_crc)
    c.m_end_offset += (length - sizeof_crc);
  m_bDoChunkCRC = c.m_do_crc16 || c.m_do_crc32;
  
  if ( m_chunk.Capacity() == 0 )
    m_chunk.Reserve(128);
  m_chunk.Append( c );

  return true;
}

void ON_BinaryArchive::EnableSave3dmRenderMeshes(
  unsigned int object_type_flags,
  bool bSave3dmRenderMeshes 
  )
{
  if (bSave3dmRenderMeshes)
  {
    // set object type bits
    m_save_3dm_render_mesh_flags |= object_type_flags;
  }
  else
  {
    // clear object type bits
    unsigned int mask = ~object_type_flags;
    m_save_3dm_render_mesh_flags &= mask;
  }
}

unsigned int ON_BinaryArchive::Save3dmRenderMeshObjectTypeFlags() const
{
  return m_save_3dm_render_mesh_flags;
}

bool ON_BinaryArchive::Save3dmRenderMesh(
  ON::object_type object_type
  ) const
{
  return (0 != (object_type & m_save_3dm_render_mesh_flags));
}

void ON_BinaryArchive::EnableSave3dmAnalysisMeshes(
  unsigned int object_type_flags,
  bool bSave3dmAnalysisMeshes 
  )
{
  if (bSave3dmAnalysisMeshes)
  {
    // set object type bits
    m_save_3dm_analysis_mesh_flags |= object_type_flags;
  }
  else
  {
    // clear object type bits
    unsigned int mask = ~object_type_flags;
    m_save_3dm_analysis_mesh_flags &= mask;
  }
}

unsigned int ON_BinaryArchive::Save3dmAnalysisMeshObjectTypeFlags() const
{
  return m_save_3dm_analysis_mesh_flags;
}

bool ON_BinaryArchive::Save3dmAnalysisMesh(
  ON::object_type object_type
  ) const
{
  return (0 != (object_type & m_save_3dm_analysis_mesh_flags));
}

void ON_BinaryArchive::SetUseBufferCompression(
  bool bUseBufferCompression
)
{
  m_bUseBufferCompression = bUseBufferCompression ? true : false;
}


bool ON_BinaryArchive::UseBufferCompression() const
{
  return m_bUseBufferCompression;
}
  
void ON_BinaryArchive::SetSave3dmPreviewImage(
  bool bSave3dmPreviewImage
)
{
  m_bSave3dmPreviewImage = bSave3dmPreviewImage ? true : false;
}

bool ON_BinaryArchive::Save3dmPreviewImage() const
{
  return m_bSave3dmPreviewImage;
}

void ON_BinaryArchive::SetModelSerialNumber(
  unsigned int model_serial_number,
  unsigned int reference_model_serial_number,
  unsigned int instance_definition_model_serial_number
  )
{
  m_SetModelComponentSerialNumbers = true;
  m_model_serial_number = model_serial_number;
  m_reference_model_serial_number = reference_model_serial_number;
  m_instance_definition_model_serial_number = instance_definition_model_serial_number;
  if (0 != m_reference_model_serial_number || 0 != m_instance_definition_model_serial_number)
    m_bCheckForRemappedIds = true;
}

void ON_BinaryArchive::ClearModelSerialNumber()
{
  m_SetModelComponentSerialNumbers = false;
  m_model_serial_number = 0;
  m_reference_model_serial_number = 0;
  m_instance_definition_model_serial_number = 0;
}

void ON_BinaryArchive::SetCheckForRemappedIds(
  bool bCheckForRemappedIds
)
{
  this->m_bCheckForRemappedIds = bCheckForRemappedIds ? true : false;
}

bool ON_BinaryArchive::CheckForRemappedIds() const
{
  return this->m_bCheckForRemappedIds;
}


unsigned int ON_BinaryArchive::ModelSerialNumber() const
{
  return m_model_serial_number;
}

unsigned int ON_BinaryArchive::ReferenceModelSerialNumber() const
{
  return m_reference_model_serial_number;
}

unsigned int ON_BinaryArchive::InstanceDefinitionModelSerialNumber() const
{
  return m_instance_definition_model_serial_number;
}

void ON_BinaryArchive::SortUserDataFilter()
{
  unsigned int count0 = m_user_data_filter.UnsignedCount();
  if (count0 > 0)
  {
    if (count0 > 1)
    {
      m_user_data_filter.QuickSort(ON_UserDataItemFilter::Compare);

      // remove duplicates
      ON_UserDataItemFilter* f = m_user_data_filter.Array();
      unsigned int i0 = 1;
      f[0].m_precedence = 0;
      f[1].m_precedence = 1;
      for (unsigned i = 2; i < count0; i++)
      {
        if (f[i0].m_application_id == f[i].m_application_id && f[i0].m_item_id == f[i].m_item_id)
          continue;
        i0++;
        if (i0 < i)
          f[i0] = f[i];
        f[i0].m_precedence = i0;
      }
      if (i0 + 1 < count0)
        m_user_data_filter.SetCount(i0 + 1);
    }

    // simplify
    if ( ShouldSerializeAllUserData() )
    {
      // all user data should be serialized.
      m_user_data_filter.Destroy();
    }
    else if ( ShouldSerializeNoUserData() )
    {
      // no user data should be serialized.
      m_user_data_filter.SetCount(1);
      m_user_data_filter.SetCapacity(1);
      m_user_data_filter[0].m_bSerialize = false;
    }
  }
}

static void GetFirst32BytesOf3dmFile(
  int version,
  char sVersion[33]
)
{
  unsigned int i;
  const char* s = "3D Geometry File Format         ";
  for ( i = 0; i < 32; i++)
    sVersion[i] = s[i];
  sVersion[32] = 0;
  if ( version <= 0 )
    sVersion[31] = '0';
  else
  {
    i = 31;
    while(version > 0 && i > 23)
    {
      sVersion[i] = ('0' + ((char)(version %10)));
      i--;
      version /= 10;
    }
  }
  return;
}

bool ON_BinaryArchive::Begin3dmTable(
  ON::archive_mode expected_mode,
  ON_3dmArchiveTableType table
  )
{
  if (ON_3dmArchiveTableType::Unset != Active3dmTable())
  {
    ON_ERROR("Attempt to begin reading or writing a 3dm archive table while another table is active.");

    // call End3dmTable() but do not modify m_3dm_active_table or m_3dm_previous_table values.
    const ON_3dmArchiveTableType saved_3dm_active_table = Active3dmTable();
    const ON_3dmArchiveTableType saved_3dm_previous_table = Previous3dmTable();
    End3dmTable(table,false);
    m_3dm_active_table = saved_3dm_active_table;
    m_3dm_previous_table = saved_3dm_previous_table;
    Internal_ReportCriticalError();
    return false;
  }

  if (ON::archive_mode::read3dm != expected_mode && ON::archive_mode::write3dm != expected_mode)
  {
    ON_ERROR("Invalid expected_mode parameter value.");
    return End3dmTable(table,false);
  }

  if (expected_mode != Mode())
  {
    ON_ERROR("Archive read/write mode is opposited expected_mode.");
    return End3dmTable(table,false);
  }

  if ( table == ON_3dmArchiveTableType::start_section )
  {
    // m_3dm_version is set during reading of the start section.
    if (0 != m_3dm_version && ON::archive_mode::read3dm == Mode())
    {
      ON_ERROR("Archive m_3dm_version is set during start section reading.");
      return End3dmTable(table,false);
    }
  }
  else
  {
    if (m_3dm_version <= 0)
    {
      ON_ERROR("Archive m_3dm_version <= 0.");
      return End3dmTable(table,false);
    }
  }

  if (1 == m_3dm_version && ON::archive_mode::write3dm == expected_mode)
  {
    ON_ERROR("Current opennurbs does not write version 1 files.");
    return End3dmTable(table,false);
  }

  if (ON_3dmArchiveTableType::Unset == table)
  {
    ON_ERROR("Invalid table parameter value.");
    return End3dmTable(table,false);
  }


  const unsigned int previous_index = static_cast<unsigned int>(Previous3dmTable());
  const unsigned int table_index = static_cast<unsigned int>(table);
  
  if (table_index <= previous_index)
  {
    if (ON_3dmArchiveTableType::user_table != table
      || ON_3dmArchiveTableType::user_table != Previous3dmTable()
      )
    {
      ON_ERROR("Multiple attempt to begin reading or writing a 3dm archive section.");
      return End3dmTable(table, false);
    }
  }

  for (ON_3dmTableStatusLink* table_link = m_3dm_table_status_list; nullptr != table_link; table_link = table_link->m_next )
  {
    if (table == table_link->m_table_status.m_table_type)
    {
      if (ON_3dmArchiveTableType::user_table != table
        || ON_3dmArchiveTableType::user_table != Previous3dmTable()
        )
      {
        ON_ERROR("Multiple attempt to begin reading or writing a 3dm archive section.");
        return End3dmTable(table, false);
      }
    }
  }


  const unsigned int settings_index = static_cast<unsigned int>(ON_3dmArchiveTableType::settings_table);
  while (previous_index < settings_index)
  {
    const unsigned int start_index = static_cast<unsigned int>(ON_3dmArchiveTableType::start_section);
    const unsigned int properties_index = static_cast<unsigned int>(ON_3dmArchiveTableType::properties_table);
    if (table_index == start_index)
      break;
    if (previous_index == start_index && table_index == properties_index)
      break;
    if (previous_index == properties_index && table_index == settings_index)
      break;
    ON_ERROR("Must read/write 3dm archive start, properties and settings sections first.");

    // call End3dmTable() but do not modify m_3dm_previous_table value.
    const ON_3dmArchiveTableType saved_3dm_previous_table = Previous3dmTable();
    End3dmTable(table, false);
    m_3dm_previous_table = saved_3dm_previous_table;
    return false;
  }

  // Begin reading the table
  m_3dm_active_table = table;

  ON_3dmTableStatusLink* table_link = new ON_3dmTableStatusLink();
  table_link->m_table_status.m_table_type = table;
  table_link->m_table_status.m_state = ON_3dmArchiveTableStatus::TableState::Started;
  table_link->m_next = m_3dm_table_status_list;
  m_3dm_table_status_list = table_link;

  return true;
}

bool ON_BinaryArchive::Internal_Begin3dmTableRecord(
  ON_3dmArchiveTableType table
  )
{
  if (ON_3dmArchiveTableType::Unset == table)
  {
    Internal_ReportCriticalError();
    ON_ERROR("Attempt to read/write a table record outside the scope of BeginRead/Write3dm...Table() / EndRead/Write3dm...Table().");
    return false;
  }
  if (Active3dmTable() != table)
  {
    Internal_ReportCriticalError();
    ON_ERROR("Attempt to read/write a table record of the wrong type.");
    return false;
  }
  else
  {
    if ( nullptr != m_3dm_table_status_list 
      && table == m_3dm_table_status_list->m_table_status.m_table_type 
      && ON_3dmArchiveTableStatus::TableState::Started == m_3dm_table_status_list->m_table_status.m_state 
      )
      m_3dm_table_status_list->m_table_status.m_state = ON_3dmArchiveTableStatus::TableState::InProgress;
  }
  if (false == ArchiveContains3dmTable(table))
  {
    // Reading a 3dm archive that does not contain this table
    // Not an error condition.
    return false;
  }

  // Continue with attempt to write record.
  return true;
}


bool ON_BinaryArchive::Read3dmTableRecord(
  ON_3dmArchiveTableType table,
  void** ptr
  )
{
  if ( nullptr != ptr )
    *ptr = 0;

  if (false == Internal_Begin3dmTableRecord(table))
    return false;

  if (false == ArchiveContains3dmTable(table))
  {
    // Reading a 3dm archive that does not contain this table
    // Not an error condition.
    return false;
  }
  if (nullptr == ptr)
  {
    // Caller doesn't want the actual elements.
    // Not an error condition.
    return false;
  }

  // Continue with attempt to read record.
  return true;
}

void ON_BinaryArchive::Internal_Increment3dmTableItemCount()
{
  if (nullptr != m_3dm_table_status_list
    && Active3dmTable() == m_3dm_table_status_list->m_table_status.m_table_type
    && ON_3dmArchiveTableStatus::TableState::InProgress == m_3dm_table_status_list->m_table_status.m_state
    )
  {
    m_3dm_table_status_list->m_table_status.m_item_count++;
  }
  else
  {
    ON_ERROR("Table item reading/writing not in progress.");
  }
}


bool ON_BinaryArchive::End3dmTable(
  ON_3dmArchiveTableType table,
  bool bSuccess
  )
{
  bool rc = bSuccess;

  bool bReportError = true;
  if (false == bSuccess)
  {
    Internal_ReportCriticalError();
    bReportError = false;
  }

  if (0 == m_chunk.Count())
  {
    if (table != Active3dmTable())
    {
      ON_ERROR("End3dmTable() table does not match the active table setting.");
      rc = false;
    }
    if (static_cast<unsigned int>(table) > static_cast<unsigned int>(Previous3dmTable()))
      m_3dm_previous_table = table;
    else
    {
      if (
        ON_3dmArchiveTableType::user_table != table
        || ON_3dmArchiveTableType::user_table != Previous3dmTable()
        )
      {
        ON_ERROR("3dm archive tables read/written in incorrect order.");
        rc = false;
      }
    }
    if (false == rc && bReportError)
    {
      Internal_ReportCriticalError();
      bReportError = false;
    }
    if ( nullptr != m_3dm_table_status_list && m_3dm_active_table == m_3dm_table_status_list->m_table_status.m_table_type )
      m_3dm_table_status_list->m_table_status.m_state = ON_3dmArchiveTableStatus::TableState::Finished;
    m_3dm_active_table = ON_3dmArchiveTableType::Unset;
  }
  else
  {
    if (bReportError)
    {
      Internal_ReportCriticalError();
    }
    ON_ERROR("End3dmTable() called while chunks are open.");
    rc = false;
  }

  if (false == rc && ON_3dmArchiveTableType::Unset == m_3dm_first_failed_table)
  {
    ON_ERROR("Reading or writing 3dm archive first failure.");
    m_3dm_first_failed_table = table;
  }
  return rc;
}

bool ON_BinaryArchive::WriteModelComponentName(const ON_ModelComponent & model_component)
{
  ON_wString valid_name;
  if (
    0 == m_user_data_depth
    && ON_BinaryArchive::TableComponentType(this->m_3dm_active_table) == model_component.ComponentType()
    )
  {
    bool bPermitReferencePrefix = false;
    if (false == ON_ModelComponent::IsValidComponentName(m_manifest, model_component, bPermitReferencePrefix, valid_name))
    {
      ON_ERROR("Invalid component name.");
    }
  }
  else
  {
    // user data, list of layers on an idef, or ...
    valid_name = model_component.Name();
  }
  return WriteString(valid_name);
}

void ON_BinaryArchive::IntentionallyWriteCorrupt3dmStartSectionForExpertTesting()
{
  if (ON::archive_mode::write3dm == m_mode)
  {
    if (0 == m_IntentionallyWriteCorrupt3dmStartSection)
      m_IntentionallyWriteCorrupt3dmStartSection = 1; // 1 meas a corrupt start section will be written.
    else if (1 == m_IntentionallyWriteCorrupt3dmStartSection)
    {
      ON_ERROR("Please read the instructions in the header file.");
      m_IntentionallyWriteCorrupt3dmStartSection = 2; // 2 indicates the "expert" tester goofed.
    }
  }
  else
  {
    ON_ERROR("Please read the instructions in the header file.");
    m_IntentionallyWriteCorrupt3dmStartSection = 2; // 2 indicates the "expert" tester goofed.
  }
}

bool ON_BinaryArchive::Write3dmStartSection(int version, const char* sStartSectionComment)
{
  if (!Begin3dmTable(ON::archive_mode::write3dm,ON_3dmArchiveTableType::start_section))
    return false;

  m_archive_runtime_environment = ON::CurrentRuntimeEnvironment();

  m_archive_3dm_start_section_comment = sStartSectionComment;

  if ( 0 == version )
    version = ON_BinaryArchive::CurrentArchiveVersion();

  // 2009 November 6 
  // Default 3dm files now have 8 byte chunk lengths.
  // 3dm archive version numbers >= 50 indicate the file has 8 byte chunk lengths.
  // Rather than change the hundreds of places in Rhino that use 5, 6, 7 ...
  // the "version *= 10" line handles it.  
  if ( version >= 5 && version < 50 )
    version *= 10;

  if ( version > ON_BinaryArchive::CurrentArchiveVersion() )
  {
    ON_ERROR("3dm archive version must be <= ON_BinaryArchive::CurrentArchiveVersion() ");
    return End3dmTable(ON_3dmArchiveTableType::start_section,false);
  }

  if (    version < 2 
       || (version >= 5 && version < 50) 
       || (version >= 50 && 0 != (version % 10)) 
       )
  {
    // 1, 2, 3, 4 use 32-bit chunk lengths.
    // >=50 and a multiple of 10 use 64-bit chunk lengths.
    // 64 bit chunk lengths were required in v5 to handle large mesh objects.
    ON_ERROR("3dm archive version must be 2, 3, 4, 50, 60, 70, ...");
    return End3dmTable(ON_3dmArchiveTableType::start_section,false);
  }

  m_crc_error_count = 0;
  m_critical_error_count = 0;
  m_3dm_version = version;
  m_3dm_opennurbs_version = ON::Version();
  
  SortUserDataFilter();

  char sVersion[64];
  memset( sVersion, 0, sizeof(sVersion) ); 
  GetFirst32BytesOf3dmFile(version,sVersion);

  if (1 == m_IntentionallyWriteCorrupt3dmStartSection)
  {
    if (version == ON_BinaryArchive::CurrentArchiveVersion())
    {
      m_IntentionallyWriteCorrupt3dmStartSection = 3; // 3 indicates the corrupt header was written.
      // Change "3D Geometry File Format         "
      // to "3DXGeometryXFileXFormat         "
      sVersion[2] = 'X';
      sVersion[11] = 'X';
      sVersion[16] = 'X';
    }
    else
    {
      // intentional corruption is requires working with the current version
      m_IntentionallyWriteCorrupt3dmStartSection = 2;
    }
  }

  if (!WriteByte( 32, sVersion ))
    return false;
  if (!BeginWrite3dmBigChunk( TCODE_COMMENTBLOCK, 0 ))
    return false;

  bool rc = false;
  for (;;)
  {
    if (sStartSectionComment && sStartSectionComment[0] )
    {
      if (!WriteByte( strlen(sStartSectionComment), sStartSectionComment) )
        break;
    }
    // write information that helps determine what code wrote the 3dm file
    const ON_String runtime(Internal_RuntimeEnvironmentToString(ON::CurrentRuntimeEnvironment()));
    char s[2048];
    const size_t s_capacity = sizeof(s)/sizeof(s[0]);
    int s_len 
      = ON_String::FormatIntoBuffer(
        s,s_capacity,
        " Runtime: %s 3DM I/O processor: OpenNURBS toolkit version %u (compiled on " __DATE__ ")\n",
        static_cast<const char*>(runtime),
        ON::Version()
        );
    if ( s_len < 0 || s_len + 2 >= s_capacity)
      s_len = 0;
    s[s_len++] = 26; // ^Z
    s[s_len++] = 0;
    if (!WriteByte( s_len, s ))
      break;

    rc = true;
    break;
  }

  if ( !EndWrite3dmChunk() ) // need to call EndWrite3dmChunk() even if a WriteByte() has failed
    rc = false;

  return End3dmTable(ON_3dmArchiveTableType::start_section,rc);
}

static bool Internal_EndOfRuntimeName(char c)
{
  return (c >= 0 && c <= 32);
}

static bool Internal_StartOfRuntimeName(char prev_c, char c)
{
  return ( Internal_EndOfRuntimeName(prev_c) && ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) );
}

static ON::RuntimeEnvironment Internal_RuntimeEnvironmentFromString(
  const ON_String& str
)
{
  if (str.IsEmpty())
    return ON::RuntimeEnvironment::Unset;

  // Look at the start section comment to see if the platform is mentioned.
  const ON_String runtime_windows(Internal_RuntimeEnvironmentToString(ON::RuntimeEnvironment::Windows));
  const ON_String runtime_android(Internal_RuntimeEnvironmentToString(ON::RuntimeEnvironment::Android));
  const ON_String runtime_apple(Internal_RuntimeEnvironmentToString(ON::RuntimeEnvironment::Apple));
  const ON_String runtime_linux(Internal_RuntimeEnvironmentToString(ON::RuntimeEnvironment::Linux));
  const ON_String runtime_wasm(Internal_RuntimeEnvironmentToString(ON::RuntimeEnvironment::WebAssembly));
  const char* sRuntimeWindows[]
    = {
    static_cast<const char*>(runtime_windows),
    "windows",
    nullptr
  };
  const char* sRuntimeAndroid[] = {
    static_cast<const char*>(runtime_android),
    "android",
    nullptr
  };
  const char* sRuntimeApple[] = {
    static_cast<const char*>(runtime_apple),
    "apple",
    "mac rhinoceros",
    nullptr
  };
  const char* sRuntimeLinux[] = {
    static_cast<const char*>(runtime_linux),
    "linux",
    nullptr
  };
  const char* sRuntimeWebAssembly[] = {
    static_cast<const char*>(runtime_wasm),
    "wasm",
    nullptr
  };

  const char capA = (char)'A';
  const char capZ = (char)'Z';
  const char toLowerAZ = (char)('a' - 'A');
  for ( int i0 = 0; i0 < 2; i0++)
  {
    for (int pass = 0; pass < 5; pass++)
    {
      const char** tokens = nullptr;
      ON::RuntimeEnvironment r = ON::RuntimeEnvironment::Unset;
      switch (pass)
      {
      case 0:
        tokens = sRuntimeWindows;
        r = ON::RuntimeEnvironment::Windows;
        break;
      case 1:
        tokens = sRuntimeAndroid;
        r = ON::RuntimeEnvironment::Android;
        break;
      case 2:
        tokens = sRuntimeApple;
        r = ON::RuntimeEnvironment::Apple;
        break;
      case 3:
        tokens = sRuntimeLinux;
        r = ON::RuntimeEnvironment::Linux;
        break;
      case 4:
        tokens = sRuntimeWebAssembly;
        r = ON::RuntimeEnvironment::WebAssembly;
        break;
      }
      for (int i = i0; nullptr != tokens[i]; i++)
      {
        char prev_c = 0;
        for (const char* s = static_cast<const char*>(str); 0 != *s; prev_c = *s++)
        {
          if (!Internal_StartOfRuntimeName(prev_c, *s))
            continue;
          const char* t = tokens[i];
          const char* s1 = s;
          while (0 != *t && 0 != *s1)
          {
            char c = *s1++;
            if (0 != i0)
            {
              if (c >= capA && c <= capZ)
                c += toLowerAZ;
            }
            if (c != *t++)
              break;
          }
          if (0 == *t && Internal_EndOfRuntimeName(*s1))
          {
            return r;
          }
        }
        if (0 == i0)
          break;
      }
    }
  }

  return ON::RuntimeEnvironment::Unset;
}

static ON::RuntimeEnvironment Internal_RuntimeEnvironmentFromWideString(
  const ON_wString& wide_string
)
{
  const ON_String str(wide_string);
  return Internal_RuntimeEnvironmentFromString(str);
}


bool ON_BinaryArchive::Read3dmStartSection( int* version, ON_String& s )
{
  // The first 24 bytes of a 3dm file must be "3D Geometry File Format "
  // The next 8 bytes must be a right justified ASCII integer >= 1.  For
  // example, prior to March 2000, all 3DM files were version 1 files and
  // they began with "3D Geometry File Format        1".  At the time of
  // this writing (May 2011) there are version 1,2,3,4,5 and 50 files.
  //
  // The next section must contain a long chunk with typecode 1.

  if (!Begin3dmTable(ON::archive_mode::read3dm,ON_3dmArchiveTableType::start_section))
    return false;

  m_archive_3dm_start_section_comment = ON_String::EmptyString;
  
  SortUserDataFilter();

  unsigned int typecode = 0;
  ON__INT64 length = -1;
  if ( version )
    *version = m_3dm_version;
  s.Destroy();
  char s3d[33];
  memset( s3d, 0, sizeof(s3d) );
  if (!ReadByte( 32, s3d ))
    return false;

  if ( 0 != strncmp( s3d, "3D Geometry File Format ", 24) ) 
  {
    // it's not a "pure" .3DM file 
    // - see if we have a .3DM file with MS OLE-goo at the start
    // (generally, there is around 6kb of goo.  I keep looking
    // for up to 32mb just in case.)
    unsigned int offset = 0;
    for ( unsigned int n = 0; n < 33554432; n++ ) 
    {
      for ( int j = 0; j < 31; j++ )
        s3d[j] = s3d[j+1];
      if ( !ReadByte( 1, &s3d[31]) ) 
        break;
      if ( 0 == strncmp( s3d, "3D Geometry File Format ", 24) ) 
      {
        offset = n+1;
        break;
      }
    }
    if (0 == offset)
    {
      ON_ERROR("3dm start section header not found.");
      return End3dmTable(ON_3dmArchiveTableType::start_section,false);
    }
    m_3dm_start_section_offset = offset;
  }


  // get version
  //char* sVersion = s3d+24;
  // skip leading spaces
  int ver = 0;
  int i = 24;
  while (i < 32 && s3d[i] == ' ')
    i++;
  while (i < 32)
  {
    // TEMPORARY 2 = X
    if ( i == 31 && s3d[i] == 'X' ) 
    {
      s3d[i] = '2';
    }

    if ( s3d[i] < '0' || s3d[i] > '9' )
    {
      // it's not a valid .3DM file version
      ON_ERROR("3dm start section header is not valid.");
      return End3dmTable(ON_3dmArchiveTableType::start_section,false);
    }
    ver = ver*10 + ((int)(s3d[i]-'0'));
    i++;
  }
  if (ver <= 0)
  {
    ON_ERROR("3dm start section version is not valid.");
    return End3dmTable(ON_3dmArchiveTableType::start_section,false);
  }

  m_3dm_version = ver;
  if ( version )
    *version = ver;

  if ( !BeginRead3dmBigChunk( &typecode, &length ) )
    return false;
  bool rc = false;
  for (;;)
  {
    if ( TCODE_COMMENTBLOCK != typecode ) 
    {
      // it's not a .3DM file
      // Fix https://mcneel.myjetbrains.com/youtrack/issue/RH-36190
      //  If the first chunk is damaged, don't start seeking.
      //  In the bug refereced above, the chunk length was 10^63-ish
      //  because the user had edited a .3dm file with a text editor.
      m_chunk.Remove();
      return false;
    }

    if ( length > 0 ) 
    {
      if ( length > 0x00FFFFFF )
      {
        ON_ERROR("ON_BinaryArchive::Read3dmStartSection - start section string is unreasonably long.");
        rc = false;
      }
      else 
      {
        int slen = (int)length;
        s.ReserveArray( slen+1 );
        s.SetLength( slen );
        s[slen] = 0;
        rc = ReadByte( slen, s.Array() );
        if (rc)
        {
          while (slen > 0 && (0 == s[slen - 1] || 26 == s[slen - 1]))
          {
            s[slen - 1] = 0;
            slen--;
          }
          s.SetLength(slen);
        }
      }
    }
    rc = true;
    break;
  }
  if ( !EndRead3dmChunk() )
    rc = false;

  m_archive_3dm_start_section_comment = s;

  if (ON::RuntimeEnvironment::Unset == m_archive_runtime_environment)
  {
    m_archive_runtime_environment = Internal_RuntimeEnvironmentFromString(m_archive_3dm_start_section_comment);
  }

  if ( !rc )
    return false;
  
  if ( 1 == m_3dm_version ) 
  {
    // In March 2001, we got reports of files with V1 headers and
    // a V2 bodies.  We haven't been able to track down the application
    // that is creating these damaged files, but we can detect them
    // and read them because they all have a TCODE_PROPERTIES_TABLE
    // chunk right after the start comments chunk and no valid V1
    // file has a chunk with a TCODE_PROPERTIES_TABLE tcode.
    //
    // Rhino 1.1 version 31-May-2000 reads 2.0 files as goo.  If a user
    // saves this file for some reason (no instances have been reported)
    // the resulting file has a V1 header, V1 fluff, and a V2 body.
    // This code will cause opennurbs to read the V2 body.
    // a file that is different from those describe This code
    // detects these files.
    {

      const ON__UINT64 pos1 = CurrentPosition();
      //int v1_fluff_chunk_count = 0;
      bool bCheckChunks = true;

      //////////
      while(bCheckChunks) {
        if ( !PeekAt3dmBigChunkType(&typecode,&length) )
          break;
        switch(typecode)
        {
          case TCODE_SUMMARY:
          case TCODE_BITMAPPREVIEW:
          case TCODE_UNIT_AND_TOLERANCES:
          case TCODE_VIEWPORT:
          case TCODE_LAYER:
          case TCODE_RENDERMESHPARAMS:
          case TCODE_CURRENTLAYER:
          case TCODE_ANNOTATION_SETTINGS:
          case TCODE_NOTES:
          case TCODE_NAMED_CPLANE:
          case TCODE_NAMED_VIEW:
            // skip potential v1 fluff
            bCheckChunks = BeginRead3dmBigChunk( &typecode, &length );
            if ( bCheckChunks )
              bCheckChunks = EndRead3dmChunk();
            break;

          //case TCODE_PROPERTIES_TABLE:
          //case TCODE_SETTINGS_TABLE:
          //case TCODE_OBJECT_TABLE:
          //case TCODE_BITMAP_TABLE:
          //case TCODE_LAYER_TABLE:
          //case TCODE_GROUP_TABLE:
          //case TCODE_LIGHT_TABLE:
          //case TCODE_MATERIAL_TABLE:
          //case TCODE_USER_TABLE:
          default:
            if ( TCODE_TABLE == (typecode & 0xFFFF0000) ) {
              // Found a V2 table which has to be V1 goo
              ON_WARNING("ON_BinaryArchive::Read3dmStartSection(): Archive has V1 header and V2 body. Continuing to read V2 body.");
              m_3dm_version = 2;
              if ( version )
                *version = 2;
            }
            bCheckChunks = false;
            break;
        }
      }

      if ( m_3dm_version == 1 ) {
        // move archive pointer back to 
        ON__UINT64 pos2 = CurrentPosition();
        if ( pos2 > pos1 ) 
        {
          SeekBackward(pos2 - pos1);
        }
      }
    }
  }

  if (0 == m_3dm_version)
  {
    ON_ERROR("3dm archive start section is damaged.");
    m_3dm_version = 10*ON::VersionMajor();
    rc = false;
  }

  return End3dmTable(ON_3dmArchiveTableType::start_section,rc);
}


const ON_String& ON_BinaryArchive::Archive3dmStartSectionComment() const
{
  return m_archive_3dm_start_section_comment;
}

const ON_3dmProperties& ON_BinaryArchive::Archive3dmProperties() const
{
  if (nullptr != m_archive_3dm_properties)
    return *m_archive_3dm_properties;

  return ON_3dmProperties::Empty;
}

const ON_3dmSettings& ON_BinaryArchive::Archive3dmSettings() const
{
  if (nullptr != m_archive_3dm_settings)
    return *m_archive_3dm_settings;

  return ON_3dmSettings::Default;
}

bool ON_BinaryArchive::Write3dmProperties(
      const ON_3dmProperties& prop
      )
{
  if (!Begin3dmTable(ON::archive_mode::write3dm,ON_3dmArchiveTableType::properties_table))
    return false;

  if (nullptr != m_archive_3dm_properties)
  {
    delete m_archive_3dm_properties;
    m_archive_3dm_properties = nullptr;
  }

  // version 2+ file properties chunk
  bool rc = BeginWrite3dmChunk(TCODE_PROPERTIES_TABLE,0);
  if ( rc ) 
  {
    rc = prop.Write( *this )?true:false;
    if ( !EndWrite3dmChunk() )
      rc = false;
  }

  const bool final_rc = End3dmTable(ON_3dmArchiveTableType::properties_table,rc);
  if (final_rc)
  {
    m_archive_3dm_properties = new ON_3dmProperties(prop);
  }
  return final_rc;
}

int on_strnicmp(const char * s1, const char * s2, int n)
{
#if defined(ON_RUNTIME_WIN)
  //return stricmp(s1,s2,n);
  return _strnicmp(s1,s2,n);
#else
  return strncasecmp(s1,s2,n);
#endif
}

bool ON_BinaryArchive::Read3dmProperties( ON_3dmProperties& prop )
{
  prop = ON_3dmProperties::Empty;

  if (!Begin3dmTable(ON::archive_mode::read3dm,ON_3dmArchiveTableType::properties_table))
    return false;

  if (nullptr != m_archive_3dm_properties)
  {
    delete m_archive_3dm_properties;
    m_archive_3dm_properties = nullptr;
  }

  // In ON_3dmProperties::Read(), m_3dm_opennurbs_version will be 
  // set to the version of OpenNURBS that was used to write this archive.
  // If the file was written with by a pre 200012210 version of OpenNURBS,
  // then m_3dm_opennurbs_version will be zero.
  m_3dm_opennurbs_version = 0;

  bool rc = true;

  // we need these when reading version 1 files
  const ON__UINT64 pos0 = CurrentPosition();
  bool bHaveRevisionHistory = false;
  bool bHaveNotes = false;
  bool bHavePreviewImage = false;
  bool bDone = false;
  bool bRewindFilePointer = false;

  ON__UINT32 tcode;
  ON__INT64 big_value;
  int version = 0;

  if ( m_3dm_version != 1 ) 
  {
    for(;;) 
    {
      tcode = 0;
      big_value = 0;
      rc = BeginRead3dmBigChunk( &tcode, &big_value );
      if ( !rc ) {
        bRewindFilePointer = true;
        break;
      }

      if ( tcode == TCODE_PROPERTIES_TABLE )
      {
        rc = prop.Read(*this)?true:false;
        if (rc)
        {
          // m_archive_saved_as_full_path 
          //   = path where file was originally saved.
          //   When m_archive_saved_as_full_path != m_archive_full_path,
          //   then the file has been moved since it was saved and 
          //   finding referenced files can get more difficult
          //   if they were moved as well.  That's when the relative
          //   path information in ON_FileReference classes 
          //   is used in conjunction with m_archive_saved_as_full_path.
          m_archive_saved_as_full_path = prop.m_3dmArchiveFullPathName;
          if (m_archive_full_path.IsNotEmpty() 
            && m_archive_saved_as_full_path.IsNotEmpty()
            && m_archive_full_path.ComparePath(m_archive_saved_as_full_path)
            )
          {
            m_b3dmArchiveMoved = true;
          }
        }
      }
      else {
        bRewindFilePointer = true;
      }

      if ( !EndRead3dmChunk() ) {
        rc = false;
        bRewindFilePointer = true;
      }
      if ( tcode == TCODE_PROPERTIES_TABLE || !rc )
        break;
    }
  }
  else 
  {
    // version 1 file
    rc = SeekFromStart(32)?true:false;
    bRewindFilePointer = true;
    for(;;) 
    {
      tcode = 0;
      big_value = 0;
      rc = BeginRead3dmBigChunk( &tcode, &big_value );
      if ( !rc ) {
        rc = true; // assume we are at the end of the file
        bRewindFilePointer = true;
        break;
      }

      switch ( tcode ) {

      case 1: // comments section has application name
        if ( big_value > 1000000 )
        {
          ON_ERROR("Comment length > 1000000");
        }
        else if ( big_value > 1 )
        {
          int slen = (int)big_value;
          int i;
          char* name = 0;
          ON_String s;
          s.ReserveArray( slen+1 );
          s.SetLength( slen );
          s[slen] = 0;
          ReadByte( slen, s.Array() );
          while ( slen > 0 && (0 == s[slen-1] || 26 == s[slen-1]) ) 
          {
            s[slen-1] = 0;
            slen--;
          }
          s.SetLength(slen);
          name = s.Array();
          if ( name ) {
            while(*name) {
              if ( !on_strnicmp(name,"Interface:",10) ) {
                name += 10;
                break;
              }
              name++;
            }
            while(*name && *name <= 32 )
              name++;
            for ( i = 0; name[i] ; i++ ) {
              if ( name[i] == '(' ) {
                name[i] = 0;
                while ( i > 0 && (name[i] <= 32 || name[i] == '-') ) {
                  name[i] = 0;
                  i--;
                }
                break;
              }
            }
            if ( *name )
            {
              char* details = 0;
              if ( !on_strnicmp(name,"Rhinoceros",10) ) {
                prop.m_Application.m_application_URL = "http://www.rhino3d.com";
                details = name+10;
                while ( *details && *details <= 32 )
                  details++;
                while ( (*details >= '0' && *details <= '9') || *details == '.' )
                  details++;
                if ( *details && *details <= 32 ) {
                  *details = 0;
                  details++;
                  while ( *details && (*details <= 32 ||*details == '-')) {
                    details++;
                  }
                }
              }
              if (*name)
                prop.m_Application.m_application_name = name;
              if (details && *details)
                prop.m_Application.m_application_details = details;
            }
          }
        }
        break;

      case TCODE_SUMMARY: 
        // version 1 revision history chunk (has 16 bit CRC)
        version = 1;
        bHaveRevisionHistory = true;
        {
          int slength = 0;
          char* s = 0;
          if (rc) rc = ReadInt(&slength);
          if (rc && slength > 0 ) {
            s = (char*)onmalloc((slength+1)*sizeof(*s));
            memset( s, 0, (slength+1)*sizeof(*s) );
            if (rc) rc = ReadChar( slength, s );
            if ( rc )
              prop.m_RevisionHistory.m_sCreatedBy = s;
            onfree(s);
            slength = 0;
            s = 0;
          }
          if (rc) rc = ReadTime( prop.m_RevisionHistory.m_create_time );
          int i32 = 0;
          if (rc) rc = ReadInt(&i32); // 0 in 1.x files
          if (rc) rc = ReadInt(&slength);
          if ( rc && slength > 0 ) 
          {
            s = (char*)onmalloc((slength+1)*sizeof(*s));
            memset( s, 0, (slength+1)*sizeof(*s) );
            if (rc) rc = ReadChar( slength, s );
            if ( rc )
              prop.m_RevisionHistory.m_sLastEditedBy = s;
            onfree(s);
            slength = 0;
            s = 0;
          }
          if (rc) rc = ReadTime( prop.m_RevisionHistory.m_last_edit_time );
          if (rc) rc = ReadInt(&i32); // 0 in 1.x files
          if (rc) rc = ReadInt( &prop.m_RevisionHistory.m_revision_count );
        }
        break;

      case TCODE_NOTES: 
        // version 1 notes chunk
        version = 1;
        bHaveNotes = true;
        for(;;)
        {
          int slength;
          char* s = 0;
          int i = prop.m_Notes.m_bVisible;
          rc = ReadInt( &i );
          if(!rc) break;
          prop.m_Notes.m_bVisible = i ? true : false;
          rc = ReadInt( &prop.m_Notes.m_window_left );
          if(!rc) break;
          rc = ReadInt( &prop.m_Notes.m_window_top );
          if(!rc) break;
          rc = ReadInt( &prop.m_Notes.m_window_right );
          if(!rc) break;
          rc = ReadInt( &prop.m_Notes.m_window_bottom );
          if(!rc) break;
          rc = ReadInt( &slength );
          if(!rc) break;
          if ( slength > 0 ) 
          {
            s = (char*)onmalloc( (slength+1)*sizeof(*s) );
            memset( s, 0, (slength+1)*sizeof(*s) );
            if ( rc ) rc = ReadChar( slength, s );
            if ( rc ) 
            {
              prop.m_Notes.m_notes = s;
            }
            onfree(s);
            slength = 0;
            s = 0;
          }
          break;
        }
        break;

      case TCODE_BITMAPPREVIEW: 
        // version 1 preview image chunk
        version = 1;
        rc = prop.m_PreviewImage.Read(*this)?true:false;
        bHavePreviewImage = rc;
        break;

      case TCODE_CURRENTLAYER:
      case TCODE_LAYER:
        // version 1 layer and current layer chunks always came after notes/bitmap/summary
        bDone = true;
        bRewindFilePointer = true;
        break;

      default:
        // the call to EndRead3dmChunk() will skip over this chunk
        bRewindFilePointer = true;
        break;
      }

      // this call to EndRead3dmChunk() skips any unread portions of the chunk
      if ( !EndRead3dmChunk() ) {
        rc = false;
        bRewindFilePointer = true;
      }

      if ( bHaveRevisionHistory && bHaveNotes && bHavePreviewImage )
        bDone = true;

      if ( bDone || !rc )
        break;
    }
  }

  if ( bRewindFilePointer ) {
    // reposition file pointer to pos0
    const ON__UINT64 pos1 = CurrentPosition();
    if ( pos0 != pos1 ) 
    {
      if (pos1 > pos0)
        SeekBackward(pos1-pos0);
      else if ( pos1 < pos0 )
        SeekForward(pos0-pos1);
    }
  }

  if (0 == m_3dm_opennurbs_version)
  {
    if (m_3dm_version <= 2)
    {
      // 200012210 is the earliest known opennurbs version number
      // Earlier versions are marked as 0.
      m_3dm_opennurbs_version = 200012210;
    }
    else
    {
      ON_ERROR("The 3dm archive properties section is damaged.");
      m_3dm_opennurbs_version = ON::Version();
    }
  }

  const bool final_rc = End3dmTable(ON_3dmArchiveTableType::properties_table,rc);

  if (ON::RuntimeEnvironment::Unset == m_archive_runtime_environment)
    m_archive_runtime_environment = Internal_RuntimeEnvironmentFromWideString(prop.m_Application.m_application_name);

  if (ON::RuntimeEnvironment::Unset == m_archive_runtime_environment)
    m_archive_runtime_environment = Internal_RuntimeEnvironmentFromWideString(prop.m_Application.m_application_details);

  if (final_rc)
  {
    m_archive_3dm_properties = new ON_3dmProperties(prop);
  }

  return final_rc;
}

bool ON_BinaryArchive::Write3dmSettings(
      const ON_3dmSettings& settings
      )
{
  if (!Begin3dmTable(ON::archive_mode::write3dm,ON_3dmArchiveTableType::settings_table))
    return false;

  if (nullptr != m_archive_3dm_settings)
  {
    delete m_archive_3dm_settings;
    m_archive_3dm_settings = nullptr;
  }

  // version 2+ file settings chunk
  bool rc = BeginWrite3dmChunk(TCODE_SETTINGS_TABLE,0);
  if ( rc ) {
    rc = settings.Write( *this );
    if ( !EndWrite3dmChunk() )
      rc = false;
  }

  if ( rc && 3 == Archive3dmVersion() )
  {
    // Build a list of ids of plug-ins that support saving
    // V3 user data.  If a plug-in id is not in this list,
    // the user data will not be saved in the V3 archive.
    int i, count = settings.m_plugin_list.Count();
    m_V3_plugin_id_list.SetCount(0);
    m_V3_plugin_id_list.SetCapacity( count+5 );
    for ( i = 0; i < count; i++ )
    {
      const ON_UUID& pid = settings.m_plugin_list[i].m_plugin_id;
      if ( !ON_UuidIsNil(pid) )
        m_V3_plugin_id_list.Append(pid);
    }

    // These ids insure V3, V4 and V5 core user data will round trip
    // through SaveAs V3 and SaveAs V4
    m_V3_plugin_id_list.Append( ON_v3_userdata_id );
    m_V3_plugin_id_list.Append( ON_v4_userdata_id );
    m_V3_plugin_id_list.Append( ON_opennurbs4_id );
    m_V3_plugin_id_list.Append( ON_opennurbs5_id );
    m_V3_plugin_id_list.Append( ON_opennurbs6_id );
    m_V3_plugin_id_list.Append( ON_opennurbs7_id );
    m_V3_plugin_id_list.Append( ON_rhino3_id );
    m_V3_plugin_id_list.Append( ON_rhino4_id );
    m_V3_plugin_id_list.Append( ON_rhino5_id );
    m_V3_plugin_id_list.Append( ON_rhino6_id );
    m_V3_plugin_id_list.Append( ON_rhino7_id );
    m_V3_plugin_id_list.QuickSort( ON_UuidCompare );
  }

  bool final_rc = End3dmTable(ON_3dmArchiveTableType::settings_table,rc);

  if (final_rc)
  {
    m_archive_3dm_settings = new ON_3dmSettings(settings);
    m_annotation_context.SetReferencedAnnotationSettings(&m_archive_3dm_settings->m_AnnotationSettings);
    m_annotation_context.SetModelLengthUnitSystem(m_archive_3dm_settings->m_ModelUnitsAndTolerances.m_unit_system.UnitSystem());
    m_annotation_context.SetPageLengthUnitSystem(m_archive_3dm_settings->m_PageUnitsAndTolerances.m_unit_system.UnitSystem());
  }

  return final_rc;
}

bool ON_BinaryArchive::Read3dmSettings( ON_3dmSettings& settings )
{
  if (!Begin3dmTable(ON::archive_mode::read3dm,ON_3dmArchiveTableType::settings_table))
    return false;

  if (nullptr != m_archive_3dm_settings)
  {
    delete m_archive_3dm_settings;
    m_archive_3dm_settings = nullptr;
  }

  bool rc = false;
  ON__UINT32 tcode;
  ON__INT64 big_value;

  if ( m_3dm_version == 1 ) {
    // read legacy v 1 info that is scattered around the file
    rc = settings.Read(*this);
  }
  else {
    rc = true;
    while(rc) 
    {
      tcode = 0;
      big_value = 0;
      rc = BeginRead3dmBigChunk( &tcode, &big_value );
      if ( !rc )
        break;
      if ( tcode == TCODE_SETTINGS_TABLE ) {
        // version 2 model settings
        rc = settings.Read(*this);
      }
      if ( !EndRead3dmChunk() ) {
        rc = false;
        break;
      }
      if ( TCODE_SETTINGS_TABLE == tcode )
        break;
    }
  }

  bool final_rc = End3dmTable(ON_3dmArchiveTableType::settings_table,rc);
  if (final_rc)
  {
    m_archive_3dm_settings = new ON_3dmSettings(settings);
    m_annotation_context.SetReferencedAnnotationSettings(&m_archive_3dm_settings->m_AnnotationSettings);
  }

  return final_rc;
}

bool ON_BinaryArchive::ArchiveContains3dmTable(
  ON_3dmArchiveTableType table,
  unsigned int archive_3dm_version,
  unsigned int opennurbs_library_version
  )
{
  if ( archive_3dm_version <= 0 )
    return false;
  if (archive_3dm_version > 5)
  {
    if (archive_3dm_version < 50)
      return false;
    if (0 != archive_3dm_version % 10)
      return false;
  }
  if ( archive_3dm_version >= 3 && opennurbs_library_version <= 0 )
    return false;

  bool rc;
  switch (table)
  {
  case ON_3dmArchiveTableType::Unset:
    rc = false;
    break;
  case ON_3dmArchiveTableType::start_section:
    rc = true;
    break;
  case ON_3dmArchiveTableType::properties_table:
    rc = true;
    break;
  case ON_3dmArchiveTableType::settings_table:
    rc = true;
    break;
  case ON_3dmArchiveTableType::bitmap_table:
    rc = (archive_3dm_version >= 2);
    break;
  case ON_3dmArchiveTableType::texture_mapping_table:
    rc = (archive_3dm_version >= 4 && opennurbs_library_version >= 200511110);
    break;
  case ON_3dmArchiveTableType::material_table:
    rc = true;
    break;
  case ON_3dmArchiveTableType::linetype_table:
    rc = (archive_3dm_version >= 4 && opennurbs_library_version >= 200503170 );
    break;
  case ON_3dmArchiveTableType::layer_table:
    rc = true;
    break;
  case ON_3dmArchiveTableType::group_table:
    rc = (archive_3dm_version >= 2 && opennurbs_library_version >= 200012210);
    break;
  case ON_3dmArchiveTableType::text_style_table:
    rc =  (archive_3dm_version >= 3 && opennurbs_library_version >= 200109180);
    break;
  case ON_3dmArchiveTableType::dimension_style_table:
    rc =  (archive_3dm_version >= 3 && opennurbs_library_version >= 200109260);
    break;
  case ON_3dmArchiveTableType::light_table:
    rc = true;
    break;
  case ON_3dmArchiveTableType::hatchpattern_table:
    rc = (archive_3dm_version >= 4 && opennurbs_library_version >= 200405030);
    break;
  case ON_3dmArchiveTableType::instance_definition_table:
    rc = (archive_3dm_version >= 3 && opennurbs_library_version >= 200205110);
    break;
  case ON_3dmArchiveTableType::object_table:
    rc = true;
    break;
  case ON_3dmArchiveTableType::historyrecord_table:
    rc = ( archive_3dm_version >= 4 && opennurbs_library_version >= 200601180 );
    break;
  case ON_3dmArchiveTableType::user_table:
    rc = ( archive_3dm_version >= 4);
    break;
  case ON_3dmArchiveTableType::end_mark:
    rc = true;
    break;
  default:
    rc = false;
    break;
  }

  return rc;
}

bool ON_BinaryArchive::ArchiveContains3dmTable(
  ON_3dmArchiveTableType table
  ) const
{
  unsigned int opennurbs_library_version = 0;
  if (ON::archive_mode::read3dm == Mode())
    opennurbs_library_version = m_3dm_opennurbs_version;
  else if (ON::archive_mode::write3dm == Mode())
    opennurbs_library_version = ON::Version();

  if ( 0 == opennurbs_library_version && m_3dm_version <= 3)
    opennurbs_library_version = 200012210;
  
  return ON_BinaryArchive::ArchiveContains3dmTable(
    table,
    m_3dm_version,
    opennurbs_library_version
    );
}

ON_3dmArchiveTableType ON_BinaryArchive::TableTypeFromTypecode( unsigned int typecode )
{
  ON_3dmArchiveTableType tt;
  switch(typecode) 
  {
  case 0:
    tt = m_3dm_active_table;
    break;
  case TCODE_PROPERTIES_TABLE: 
    tt = ON_3dmArchiveTableType::properties_table;
    break;
  case TCODE_SETTINGS_TABLE:  
    tt = ON_3dmArchiveTableType::settings_table;
    break;
  case TCODE_BITMAP_TABLE:    
    tt = ON_3dmArchiveTableType::bitmap_table;
    break;
  case TCODE_TEXTURE_MAPPING_TABLE:
    tt = ON_3dmArchiveTableType::texture_mapping_table; 
    break;
  case TCODE_MATERIAL_TABLE:  
    tt = ON_3dmArchiveTableType::material_table;
    break;
  case TCODE_LINETYPE_TABLE:  
    tt = ON_3dmArchiveTableType::linetype_table;
    break;
  case TCODE_LAYER_TABLE:   
    tt = ON_3dmArchiveTableType::layer_table;
    break;
  case TCODE_LIGHT_TABLE:   
    tt = ON_3dmArchiveTableType::light_table;
    break;
  case TCODE_OBJECT_TABLE:  
    tt = ON_3dmArchiveTableType::object_table;
    break;
  case TCODE_GROUP_TABLE:  
    tt = ON_3dmArchiveTableType::group_table;
    break;
  case TCODE_FONT_TABLE: 
    tt = ON_3dmArchiveTableType::text_style_table;
    break;
  case TCODE_DIMSTYLE_TABLE: 
    tt = ON_3dmArchiveTableType::dimension_style_table; 
    break;
  case TCODE_HATCHPATTERN_TABLE:
    tt = ON_3dmArchiveTableType::hatchpattern_table; 
    break;
  case TCODE_INSTANCE_DEFINITION_TABLE:
    tt = ON_3dmArchiveTableType::instance_definition_table; 
    break;
  case TCODE_HISTORYRECORD_TABLE:
    tt = ON_3dmArchiveTableType::historyrecord_table; 
    break;
  case TCODE_USER_TABLE: 
    tt = ON_3dmArchiveTableType::user_table; 
    break;
  default:
    ON_ERROR("invalid typecode value");
    tt = ON_3dmArchiveTableType::Unset;
    break;
  }
  return tt;
}

bool ON_BinaryArchive::BeginWrite3dmTable( unsigned int typecode )
{
  if (0 == typecode)
  {
    ON_ERROR("ON_BinaryArchive::BeginWrite3dmTable() bad typecode");
    return false;
  }
  const ON_3dmArchiveTableType tt = TableTypeFromTypecode(typecode);
  if (tt == ON_3dmArchiveTableType::Unset) 
  {
    ON_ERROR("ON_BinaryArchive::BeginWrite3dmTable() bad typecode");
    return false;
  }
  if ( Active3dmTable() != ON_3dmArchiveTableType::Unset )
  {
    ON_ERROR("ON_BinaryArchive::BeginWrite3dmTable() m_active_table != no_active_table");
    return false;
  }
  if ( 0 != m_chunk.Count() ) 
  {
    ON_ERROR("ON_BinaryArchive::BeginWrite3dmTable() m_chunk.Count() != 0");
    return false;
  }
  if (false == Begin3dmTable(ON::archive_mode::write3dm,tt))
    return false;

  bool rc;
  if (ArchiveContains3dmTable(tt))
  {
    rc = BeginWrite3dmChunk(typecode, 0);
    if (false == rc)
      End3dmTable(tt, false);
  }
  else
    rc = true;

  return rc;
}

bool ON_BinaryArchive::EndWrite3dmTable( unsigned int typecode )
{
  const ON_3dmArchiveTableType tt = TableTypeFromTypecode(typecode);
  if (tt == ON_3dmArchiveTableType::Unset)
  {
    ON_ERROR("ON_BinaryArchive::EndWrite3dmTable() bad typecode");
    return false;
  }
  if ( Active3dmTable() != tt )
  {
    ON_ERROR("ON_BinaryArchive::EndWrite3dmTable() m_active_table != t");
    return false;
  }
  if ( m_chunk.Count() != 1 )
  {
    ON_ERROR("ON_BinaryArchive::EndWrite3dmTable() m_chunk.Count() != 1");
    return false;
  }
  const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
  if ( 0 == c || c->m_typecode != typecode ) 
  {
    ON_ERROR("ON_BinaryArchive::EndWrite3dmTable() m_chunk.Last()->typecode != typecode");
    return false;
  }
  bool rc = BeginWrite3dmChunk( TCODE_ENDOFTABLE, 0 );
  if (rc)
  {
    if (!EndWrite3dmChunk())
      rc = false;
  }
  if (!EndWrite3dmChunk())
    rc = false;
  Flush();
  return End3dmTable(tt,rc);
}

bool ON_BinaryArchive::BeginRead3dmTable( unsigned int typecode )
{
  bool rc = false;
  if (ON::archive_mode::read3dm != Mode())
  {
    ON_ERROR("ON_BinaryArchive::BeginRead3dmTable() ON::archive_mode::read3dm != Mode()");
    return false;
  }

  if (0 == typecode) 
  {
    ON_ERROR("ON_BinaryArchive::BeginRead3dmTable() bad typecode");
    return false;
  }

  const ON_3dmArchiveTableType tt = TableTypeFromTypecode(typecode);
  if (tt == ON_3dmArchiveTableType::Unset) 
  {
    ON_ERROR("ON_BinaryArchive::BeginRead3dmTable() bad typecode");
    return false;
  }

  const bool bUserTable = ( TCODE_USER_TABLE == typecode || ON_3dmArchiveTableType::user_table == tt );

  if (static_cast<unsigned int>(tt) <= static_cast<unsigned int>(ON_3dmArchiveTableType::settings_table))
  {
    ON_ERROR("ON_BinaryArchive::BeginRead3dmTable cannot be used for start, properties, or settings table.");
    return false;
  }

  if (false == ArchiveContains3dmTable(tt))
  {
    // table type was added after the code that wrote the
    // file was compiled or after this code was compiled.
    if ( bUserTable )
      return false; // false for user tables

    // true for the other tabelss if things are as they should be
    return Begin3dmTable(ON::archive_mode::read3dm,tt);
  }

  if ( m_3dm_version <= 1 ) 
  {
      // version 1 files had can have chunks in any order.  To read a "table",
      // you have to go through the entire list of chunks looking for those
      // that belong to a particular table.
      rc = SeekFromStart(32)?true:false;
      if (Begin3dmTable(ON::archive_mode::read3dm, tt))
      {
        if (false == rc)
          End3dmTable(tt, false);
      }
      return rc;
  }

  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  rc = PeekAt3dmBigChunkType( &tcode, &big_value );
  if ( rc )
  {
    if ( tcode != typecode ) 
    {
      if ( bUserTable ) 
      {
        // it's ok to not have user tables
        return false;
      }

      const bool bIsTableTypeCode = (TCODE_TABLE == (0xFFFFF000 & tcode));
      if (false == bIsTableTypeCode)
      {
        // Dale Lear - Nov 8 2022 - ships in Rhino 8.2
        // Fix https://mcneel.myjetbrains.com/youtrack/issue/RH-77657
        // (detecting corruption in table headers prevents hangs).
        // This value isn't a table typecode (even from a table added int the future).
        // The file is badly corrupt at this point and we have to quit.
        ON_ERROR("tcode is not a table typecode. File is badly corrupted.");
        this->Internal_ReportCriticalError();
        return false;
      }

      // A required table is not at the current position in the archive
      // see if we can find it someplace else in the archive.  This can
      // happen when old code encounters a table that was added later.

      bool bSeekFromStart = true;

      if (   TCODE_HATCHPATTERN_TABLE == tcode
          && TCODE_INSTANCE_DEFINITION_TABLE == typecode
          && 3 == m_3dm_version 
          && 200405190 <= m_3dm_opennurbs_version )
      {
        // Dale Lear
        //   V3 files from 19 may 2004 on contained bogus hatch pattern tables
        //   where the instance definition table was supposed to be.
        //
        // Do not set rc in this code.  The goal of this code is to
        // avoid seeking from the start of the file and posting
        // an ON_ERROR alert about something we can work around
        // and has been fixed in V4.
        bSeekFromStart = false;
        tcode = 0;
        big_value = 0;
        if (BeginRead3dmBigChunk(&tcode, &big_value))
        {
          if (EndRead3dmChunk())
          {
            tcode = 0;
            big_value = 0;
            if (TCODE_HATCHPATTERN_TABLE == tcode)
            {
              // We've skipped the incorrectly positioned hatch pattern table.
              // If we're lucking we are at the start of the correct table.
              PeekAt3dmBigChunkType(&tcode, &big_value);
              if (tcode != typecode)
              {
                // We're not lucky.
                bSeekFromStart = true;
              }
            }
          }
          else
            tcode = 0;            
        }
      }

      if ( bSeekFromStart )
      {
        ON_ERROR("ON_BinaryArchive::BeginRead3dmTable() - current file position not at start of table - searching");
        rc = Seek3dmChunkFromStart( typecode );
      }
    }
    if ( rc ) 
    {
      rc = Begin3dmTable(ON::archive_mode::read3dm,tt);
      if (rc)
      {
        tcode = 0;
        big_value = 0;
        rc = BeginRead3dmBigChunk(&tcode, &big_value);
        if (rc && tcode != typecode)
        {
          ON_ERROR("ON_BinaryArchive::BeginRead3dmTable() - corrupt table - skipping");
          rc = false;
          if (EndRead3dmChunk())
          {
            // 1 November 2005 Dale Lear
            //    This fall back is slow but it has been finding
            //    layer and object tables in damaged files.  I'm
            //    adding it to the other BeginRead3dm...Table()
            //    functions when it makes sense.

            ON__UINT64 filelength = 0;
            ON__UINT32 table_record_record = 0;
            ON_UUID class_uuid = ON_nil_uuid;
            ON__UINT64 min_length_data = 0;
            switch (typecode)
            {
            case TCODE_BITMAP_TABLE:
              table_record_record = TCODE_BITMAP_RECORD;
              class_uuid = ON_nil_uuid;  // multiple types of opennurbs objects in bitmap tables
              min_length_data = 40;
              break;

            case TCODE_TEXTURE_MAPPING_TABLE:
              table_record_record = TCODE_TEXTURE_MAPPING_RECORD;
              class_uuid = ON_CLASS_ID(ON_TextureMapping);
              min_length_data = sizeof(ON_TextureMapping);
              break;

            case TCODE_MATERIAL_TABLE:
              table_record_record = TCODE_MATERIAL_RECORD;
              class_uuid = ON_CLASS_ID(ON_Material);
              min_length_data = 114;
              break;

            case TCODE_LINETYPE_TABLE:
              table_record_record = TCODE_LINETYPE_RECORD;
              class_uuid = ON_CLASS_ID(ON_Linetype);
              min_length_data = 20;
              break;

            case TCODE_LAYER_TABLE:
              table_record_record = TCODE_LAYER_RECORD;
              class_uuid = ON_CLASS_ID(ON_Layer);
              min_length_data = 30;
              break;

            case TCODE_GROUP_TABLE:
              table_record_record = TCODE_GROUP_RECORD;
              class_uuid = ON_CLASS_ID(ON_Group);
              min_length_data = 20;
              break;

            case TCODE_FONT_TABLE:
              table_record_record = TCODE_FONT_RECORD;
              class_uuid = ON_CLASS_ID(ON_TextStyle);
              min_length_data = 30;
              break;

            case TCODE_DIMSTYLE_TABLE:
              table_record_record = TCODE_DIMSTYLE_RECORD;
              class_uuid 
                = (m_3dm_version >= 60)
                ? ON_CLASS_ID(ON_DimStyle)
                : ON_CLASS_ID(ON_V5x_DimStyle);
              min_length_data = 30;
              break;

            case TCODE_LIGHT_TABLE:
              table_record_record = TCODE_LIGHT_RECORD;
              class_uuid = ON_CLASS_ID(ON_Light);
              min_length_data = 30;
              break;

            case TCODE_HATCHPATTERN_TABLE:
              table_record_record = TCODE_HATCHPATTERN_RECORD;
              class_uuid = ON_CLASS_ID(ON_HatchPattern);
              min_length_data = 30;
              break;

            case TCODE_INSTANCE_DEFINITION_TABLE:
              table_record_record = TCODE_INSTANCE_DEFINITION_RECORD;
              class_uuid = ON_CLASS_ID(ON_InstanceDefinition);
              min_length_data = 30;
              break;

            case TCODE_OBJECT_TABLE:
              table_record_record = TCODE_OBJECT_RECORD;
              class_uuid = ON_nil_uuid; // multiple object types in this table
              min_length_data = 26; // ON_Point data is 3 doubles + 2 byte version number
              break;

            case TCODE_HISTORYRECORD_TABLE:
              table_record_record = TCODE_HISTORYRECORD_RECORD;
              class_uuid = ON_CLASS_ID(ON_HistoryRecord);
              min_length_data = sizeof(ON_HistoryRecord);
              break;

            default:
              break;
            }

            if (
              0 != table_record_record 
              && min_length_data > 0 
              )
            {
              if ( FindMisplacedTable(filelength, typecode, table_record_record, class_uuid, min_length_data) )
              {
                tcode = 0;
                big_value = 0;
                if (PeekAt3dmBigChunkType(&tcode, &big_value))
                {
                  if (tcode == typecode)
                  {
                    // try one last time
                    End3dmTable(tt,true);
                    m_3dm_previous_table = ON_3dmArchiveTableType::settings_table;
                    rc = Begin3dmTable(ON::archive_mode::read3dm, tt);
                    if (rc)
                    {
                      tcode = 0;
                      big_value = 0;
                      rc = BeginRead3dmBigChunk(&tcode, &big_value);
                      if (rc)
                      {
                        if (tcode != typecode)
                        {
                          EndRead3dmChunk();
                          rc = false;
                          End3dmTable(tt, false);
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
        if ( false == rc )
          End3dmTable(tt,false);
      }
    }
  }
  
  return rc;
}


int ON_BinaryArchive::GetCurrentChunk(ON_3DM_CHUNK& chunk) const
{
  ON_3DM_BIG_CHUNK big_chunk;
  memset(&chunk,0,sizeof(ON_3DM_CHUNK));
  memset(&big_chunk,0,sizeof(big_chunk));
  int rc = GetCurrentChunk(big_chunk);
  if ( rc > 0 )
  {
    chunk.m_offset = (size_t)big_chunk.m_start_offset;
    chunk.m_typecode = big_chunk.m_typecode;

    ON__INT32 i32 = 0;
    if ( ON_IsLongChunkTypecode( big_chunk.m_typecode ) )
      DownSizeUINT( (ON__UINT64)big_chunk.m_big_value, (ON__UINT32*)&i32 );
    else
      DownSizeINT( big_chunk.m_big_value, &i32 );
    chunk.m_value = i32;

    chunk.m_do_length = big_chunk.m_bLongChunk ? 1 : 0;
    chunk.m_do_crc16 = big_chunk.m_do_crc16 ? 1 : 0;
    chunk.m_do_crc32 = big_chunk.m_do_crc32 ? 1 : 0;
    chunk.m_crc16 = big_chunk.m_crc16;
    chunk.m_crc32 = big_chunk.m_crc32;
  }
  return rc;
}


int ON_BinaryArchive::GetCurrentChunk(ON_3DM_BIG_CHUNK& chunk) const
{
  int rc = m_chunk.Count();
  if ( rc > 0 )
  {
    chunk = m_chunk[rc-1];
  }
  else
  {
    memset(&chunk,0,sizeof(ON_3DM_BIG_CHUNK));
  }
  return rc;
}

static
const unsigned char*  BufferToUINT16(
          bool bReverseByteOrder, 
          const unsigned char* buffer,
          const unsigned char* buffer_max,
          ON__UINT16* u16 )
{
  if ( buffer >= buffer_max || buffer_max - buffer < 2 )
    return 0;
  if ( u16 )
  {
    unsigned char* dst = (unsigned char*)u16;
    if ( bReverseByteOrder )
    {
      dst[0] = buffer[1];
      dst[1] = buffer[0];
    }
    else
    {
      dst[0] = buffer[0];
      dst[1] = buffer[1];
    }
  }
  return buffer+2;
}

static
const unsigned char* BufferToUINT32(
          bool bReverseByteOrder,
          const unsigned char* buffer, 
          const unsigned char* buffer_end,
          ON__UINT32* u32 )
{
  if ( buffer >= buffer_end || buffer_end - buffer < 4 )
    return 0;
  if ( u32 )
  {
    unsigned char* dst = (unsigned char*)u32;
    if ( bReverseByteOrder )
    {
      dst[0] = buffer[3];
      dst[1] = buffer[2];
      dst[2] = buffer[1];
      dst[3] = buffer[0];
    }
    else
    {
      dst[0] = buffer[0];
      dst[1] = buffer[1];
      dst[2] = buffer[2];
      dst[3] = buffer[3];
    }
  }
  return buffer+4;
}

static
const unsigned char* BufferToINT64(
          bool bReverseByteOrder, 
          const unsigned char* buffer, 
          const unsigned char* buffer_end,
          ON__INT64* i64 )
{
  if ( buffer >= buffer_end || buffer_end - buffer < 8 )
    return 0;
  if ( i64 )
  {
    unsigned char* dst = (unsigned char*)i64;
    if ( bReverseByteOrder )
    {
      dst[0] = buffer[7];
      dst[1] = buffer[6];
      dst[2] = buffer[5];
      dst[3] = buffer[4];
      dst[4] = buffer[3];
      dst[5] = buffer[2];
      dst[6] = buffer[1];
      dst[7] = buffer[0];
    }
    else
    {
      dst[0] = buffer[0];
      dst[1] = buffer[1];
      dst[2] = buffer[2];
      dst[3] = buffer[3];
      dst[4] = buffer[4];
      dst[5] = buffer[5];
      dst[6] = buffer[6];
      dst[7] = buffer[7];
    }
  }
  return buffer+8;
}

static
const unsigned char* BufferValidateTcode( 
          bool bReverseByteOrder,
          const unsigned char* buffer, 
          const unsigned char* buffer_end,
          ON__UINT32 expected_tcode )
{
  ON__UINT32 tc = expected_tcode ? 0 : 1;
  buffer = BufferToUINT32(bReverseByteOrder,buffer,buffer_end,&tc);
  return ( 0 != buffer && tc == expected_tcode ) ? buffer : 0;
}

static 
const unsigned char* BufferToChunkValue( 
          bool bReverseByteOrder,
          size_t sizeof_chunk_value, 
          const unsigned char* buffer, 
          const unsigned char* buffer_end,
          ON__INT64* chunk_value )
{
  if ( 8 == sizeof_chunk_value )
  {
    buffer = BufferToINT64(bReverseByteOrder,buffer,buffer_end,chunk_value);
  }
  else
  {
    ON__UINT32 u32;
    ON__UINT64 u64;
    buffer = BufferToUINT32(bReverseByteOrder,buffer,buffer_end,&u32);
    if ( buffer && chunk_value )
    {
      // this u64 = u32 is here so 4 byte unsigned ints with the high
      // bit set are converted to positive 8 bytes ints.
      u64 = u32; 
      *chunk_value = (ON__INT64)u64;
    }
  }
  return buffer;
}

static 
const unsigned char* BufferToUuid(
          bool bReverseByteOrder, 
          const unsigned char* buffer,
          const unsigned char* buffer_end,
          ON_UUID& uuid )
{
  ON__UINT32 data1=0;
  ON__UINT16 data2=0, data3=0;
  if ( buffer >= buffer_end || buffer_end - buffer < 16 )
    return 0;
  buffer = BufferToUINT32(bReverseByteOrder,buffer,buffer_end,&data1);
  if (buffer)
    buffer = BufferToUINT16(bReverseByteOrder,buffer,buffer_end,&data2);
  if (buffer)
    buffer = BufferToUINT16(bReverseByteOrder,buffer,buffer_end,&data3);
  if (buffer)
  {
    if ( buffer >= buffer_end || buffer_end - buffer < 8 )
      buffer = 0;
    else
    {
      uuid.Data1 = data1;
      uuid.Data2 = data2;
      uuid.Data3 = data3;
      memcpy(&uuid.Data4,buffer,8);
      buffer += 8;
    }
  }
  return buffer;
}

static
const unsigned char* EmergencyFindTable_UuidHelper( 
          bool bReverseByteOrder,
          size_t sizeof_chunk_value, 
          const unsigned char* buffer,
          const unsigned char* buffer_end,
          const ON__UINT32 expected_tcode,
          const ON_UUID* expected_uuid
          )
{
  ON__INT64 chunk_value;
  ON__UINT32 c, cc;
  ON_UUID uuid;

  // make sure the value at the start of the buffer = expected_tcode.
  buffer = BufferValidateTcode(bReverseByteOrder,buffer,buffer_end,expected_tcode);
  if ( 0 == buffer )
    return 0;

  // get length of this chunk containing the uuid
  chunk_value = -1;
  buffer = BufferToChunkValue( bReverseByteOrder,sizeof_chunk_value,buffer,buffer_end,&chunk_value );
  if ( 0 == buffer || chunk_value < 0 )
    return 0;

  // determine how long the chunk is supposed to be and validate the length.
  //
  // The "16+4+sizeof_chunk_value+21+4+4" in the bLookForUserTableRecordHeader
  // breaks down as:
  //  16                       sizeof(uuid)
  //  +4                     + sizeof(TCODE_USER_TABLE_RECORD_HEADER chunk typecode)
  //  +sizeof_chunk_value    + sizeof(TCODE_USER_TABLE_RECORD_HEADER chunk length)
  //  +21                    + major ver, minor ver, bool, archive ver, 3dm ver
  //  +4                     + sizeof(TCODE_USER_TABLE_RECORD_HEADER chunk crc)
  //  +4                     + sizeof(TCODE_USER_TABLE_UUID chunk crc)
  const bool bLookForUserTableRecordHeader = (TCODE_USER_TABLE_UUID == expected_tcode
                                              && ((ON__UINT64)chunk_value) >= (16+4+sizeof_chunk_value+21+4+4)
                                             );
  if ( !bLookForUserTableRecordHeader && 20 != chunk_value )
    return 0;
  buffer = BufferToUuid(bReverseByteOrder,buffer,buffer_end,uuid);
  if ( 0 == buffer )
    return 0;
  if( 0 != expected_uuid && uuid != *expected_uuid )
    return 0;
  
  if ( bLookForUserTableRecordHeader )
  {
    // make sure there is a TCODE_USER_TABLE_RECORD_HEADER chunk and skip over it.
    buffer = BufferValidateTcode(bReverseByteOrder,buffer,buffer_end,TCODE_USER_TABLE_RECORD_HEADER);
    if ( 0 == buffer )
      return 0;
    // get length of the TCODE_USER_TABLE_RECORD_HEADER chunk
    ON__INT64 header_length = -1;
    buffer = BufferToChunkValue( bReverseByteOrder,sizeof_chunk_value,buffer,buffer_end,&header_length );
    if ( 0 == buffer )
      return 0;
    if ( header_length < 25 )
      return 0;
    if ( buffer >= buffer_end || buffer_end - buffer < header_length )
      return 0;
    buffer += header_length;
  }

  buffer = BufferToUINT32(bReverseByteOrder,buffer,buffer_end,&c);
  if ( 0 == buffer )
    return 0;
  cc = ON_CRC32(0,4,&uuid.Data1);
  cc = ON_CRC32(cc,2,&uuid.Data2);
  cc = ON_CRC32(cc,2,&uuid.Data3);
  cc = ON_CRC32(cc,8,&uuid.Data4[0]);
  if ( c != cc )
    return 0;

  return buffer;
}


bool ON_BinaryArchive::FindMisplacedTable( 
        ON__UINT64 filelength,
        const ON__UINT32 table_tcode,
        const ON__UINT32 table_record_tcode,
        const ON_UUID class_uuid,
        const ON__UINT64 min_length_data
        )
{
  bool rc = false;
  unsigned char buffer2048[2048];
  const ON__UINT64 pos0 = CurrentPosition();
  if ( filelength > 0 && pos0 >= filelength )
    return false;

  ON__UINT32 tcode;
  ON__INT64 i64;

  const bool bReverseByteOrder = (ON::endian::big_endian == Endian());
  const size_t sizeof_chunk_typecode = 4;
  const size_t sizeof_chunk_value = SizeofChunkLength();
  const size_t sizeof_chunk_header = sizeof_chunk_typecode + sizeof_chunk_value;
  size_t length_of_user_uuid_and_header = 0;
  const bool bFindObjectTable    = (  TCODE_OBJECT_TABLE == table_tcode
                                   && TCODE_OBJECT_RECORD == table_record_tcode );
  const bool bFindUserTable    = (    TCODE_USER_TABLE == table_tcode
                                   && TCODE_USER_RECORD == table_record_tcode );

  if ( TCODE_USER_TABLE == table_tcode && !bFindUserTable )
    return false;
  if ( TCODE_OBJECT_TABLE == table_tcode && !bFindObjectTable )
    return false;
  if ( bFindUserTable && ON_UuidIsNil(class_uuid) )
  {
    // must provide plug-in id when searching for user tables
    ON_ERROR("ON_BinaryArchive::FindMisplacedTable - must provide plug-in id when searching for user tables");
    return false;
  }

  if ( !SeekFromStart(0) )
    return false;

  ON__UINT64 pos1 = CurrentPosition();
  ON__UINT64 pos;
  ON__UINT64 empty_table_pos = 0;    // position of first empty table candidate
  int        empty_table_status = 0; // 1 = found a candidate for an empty table
                                     // 2 = found 2 or more candidates

  const size_t sizeof_buffer2048 = sizeof(buffer2048);
  bool bAtEOF = false;

  while(!bAtEOF)
  {
    pos = CurrentPosition();
    if ( pos < pos1 )
    {
      break;
    }
    else if ( pos > pos1 )
    {
      if ( !SeekBackward(pos - pos1) )
        break;
      if ( pos1 != CurrentPosition() )
        break;
    }

    memset(buffer2048,0,sizeof_buffer2048);
    // Depending on the table and the version of the file, less than 
    // sizeof_buffer128 bytes may be read.  Setting bit 0x04 of
    // m_error_message_mask disables calls to ON_Error when we
    // attempt to read beyond the end of file.
    const unsigned int saved_error_message_mask = m_error_message_mask;
    m_error_message_mask |= 0x04;
    const size_t sizeof_read = Read(sizeof_buffer2048,buffer2048);
    m_error_message_mask = saved_error_message_mask;
    if ( sizeof_read < sizeof_buffer2048 )
    {
      // we need to parse what was read, but there's nothing after this.
      bAtEOF = true;
    }
    if ( sizeof_read < 2*sizeof_chunk_header || sizeof_read > sizeof_buffer2048 )
      break;
    const unsigned char* buffer_end = (&buffer2048[0]) + sizeof_read;
    const unsigned char* buffer = buffer2048;

    pos1++;

    // "read" 4 byte tcode
    tcode = !table_tcode;
    buffer = BufferToUINT32(bReverseByteOrder,buffer,buffer_end,&tcode);
    if ( 0 == buffer )
      break;

    if ( table_tcode != tcode )
    {
      // This for loop looks through the buffer we just
      // read to reduce the amount of times we seek backwards
      // and re-read.
      for ( size_t i = 1; i <= sizeof_read - sizeof_chunk_typecode; i++ )
      {
        tcode = !table_tcode;
        buffer = BufferToUINT32(bReverseByteOrder,&buffer2048[i],buffer_end,&tcode);
        if ( 0 == buffer || table_tcode == tcode )
        {
          if ( bAtEOF && sizeof_read > 0 && 0 != buffer && table_tcode == tcode )
          {
            // this table starts within sizeof_buffer2048 bytes of the eof.
            bAtEOF = false;
          }
          break;
        }
        pos1++;
      }
      continue; // start again with archive positioned at the tcode we want
    }

    // "read" 4 or 8 byte chunk value
    i64 = -1;
    buffer = BufferToChunkValue(bReverseByteOrder,sizeof_chunk_value,buffer,buffer_end,&i64);
    if ( 0 == buffer || i64 <= 0 )
      continue;
    const ON__UINT64 length_of_table = (ON__UINT64)i64;

    if ( length_of_table < 2*sizeof_chunk_header + 4 + min_length_data )
    {
      if ( sizeof_chunk_header == length_of_table && 2 != empty_table_status )
      {
        // see if we are at a TCODE_ENDOFTABLE chunk
        buffer = BufferValidateTcode(bReverseByteOrder,buffer,buffer_end,TCODE_ENDOFTABLE);
        if ( 0 != buffer )
        {
          i64 = -1;
          buffer = BufferToChunkValue(bReverseByteOrder,sizeof_chunk_value,buffer,buffer_end,&i64);
          if ( 0 == i64 )
          {
            if ( 0 == empty_table_status )
            {
              empty_table_pos = pos1-1;
              empty_table_status = 1;
            }
            else
            {
              // found 2 or more candidates for the end of table chunk
              empty_table_status = 2;
            }
          }
        }
      }
      continue;
    }

    if ( bFindUserTable )
    {
      // We found TCODE_USER_TABLE + chunk length.  If it is a user table,
      // there should be a TCODE_USER_TABLE_UUID chunk with a crc.
      const unsigned char* buffer0 = buffer;
      buffer = EmergencyFindTable_UuidHelper(bReverseByteOrder,sizeof_chunk_value,buffer,buffer_end,TCODE_USER_TABLE_UUID,&class_uuid);
      if ( 0 == buffer || buffer <= buffer0 )
        continue;

      length_of_user_uuid_and_header = buffer - buffer0;
      // At this point we should be postioned at the table_record_tcode = TCODE_USER_RECORD chunk
    }

    // see if the start of the buffer contains the 4 byte typecode value = table_record_tcode.
    buffer = BufferValidateTcode(bReverseByteOrder,buffer,buffer_end,table_record_tcode);
    if ( 0 == buffer )
      continue;
    i64 = -1;
    buffer = BufferToChunkValue( bReverseByteOrder, sizeof_chunk_value,buffer,buffer_end,&i64);
    if ( 0 == buffer || i64 <= 0 )
      continue;
    const ON__UINT64 length_of_record = (ON__UINT64)i64;


    if ( bFindUserTable )
    {
      ON__UINT64 expected_length_of_table = length_of_user_uuid_and_header 
                                          + sizeof_chunk_header
                                          + length_of_record;
      if ( expected_length_of_table != length_of_table )
        continue;
    }
    else
    {
      if ( length_of_record < 4*sizeof_chunk_header + 20 + min_length_data )
        continue;
      if ( length_of_record + 2*sizeof_chunk_header > length_of_table)
        continue;

      if (bFindObjectTable)
      {
        buffer = BufferValidateTcode(bReverseByteOrder,buffer,buffer_end,TCODE_OBJECT_RECORD_TYPE);
        if ( 0 == buffer )
          continue;
        // The TCODE_OBJECT_RECORD_TYPE is a shot chunk whose value is a bitfield 
        // used to filter reading of objects.  Checking the value will not help
        // validate the record, but we need to skip over it.
        buffer = BufferToChunkValue(bReverseByteOrder,sizeof_chunk_value,buffer,buffer_end,0);
        if ( 0 == buffer )
          continue;
      }

      buffer = BufferValidateTcode(bReverseByteOrder,buffer,buffer_end,TCODE_OPENNURBS_CLASS);
      if ( 0 == buffer )
        continue;

      i64 = -1;
      buffer = BufferToChunkValue( bReverseByteOrder,sizeof_chunk_value,buffer,buffer_end,&i64);
      if ( 0 == buffer || i64 <= 0 )
        continue;
      const ON__UINT64 length_of_on_class = (ON__UINT64)i64;

      if ( length_of_on_class < 3*sizeof_chunk_header + 20 + min_length_data )
        continue;

      if ( length_of_on_class + sizeof_chunk_header + 4 > length_of_record)
        continue;

      const unsigned char* buffer0 = buffer;
      buffer = EmergencyFindTable_UuidHelper(bReverseByteOrder,sizeof_chunk_value,buffer,buffer_end,TCODE_OPENNURBS_CLASS_UUID,(ON_UuidIsNil(class_uuid) ? nullptr : &class_uuid));
      if ( 0 == buffer || buffer <= buffer0)
        continue;
      const size_t length_of_uuid_chunk = buffer-buffer0;

      buffer = BufferValidateTcode(bReverseByteOrder,buffer,buffer_end,TCODE_OPENNURBS_CLASS_DATA);
      if ( 0 == buffer )
        continue;

      i64 = -1;
      buffer = BufferToChunkValue( bReverseByteOrder,sizeof_chunk_value,buffer,buffer_end,&i64);
      if ( 0 == buffer || i64 < 0 )
        continue;
      const ON__UINT64 length_of_data = (ON__UINT64)i64;

      if ( length_of_data < min_length_data )
        continue;
      if ( length_of_data + length_of_uuid_chunk + 2*sizeof_chunk_header > length_of_on_class)
        continue;
    }

    // position archive at point where the table tcode was read
    if ( !SeekBackward(sizeof_read) )
      break;
    pos = CurrentPosition();
    if ( pos+1 == pos1)
      rc = true;
    break;
  }

  if ( !rc )
  {
    // we didn't fing a table containing anything
    if ( 1 == empty_table_status )
    {
      // we found one candidate for an empty table.
      // This is reasonable for materials, bitmaps, and the like.
      rc = SeekFromStart(empty_table_pos);
    }
    else
    {
      // nothing in this file.
      SeekFromStart(pos0);
    }
  }

  if (rc)
  {
    ON_3dmArchiveTableType tt = TableTypeFromTypecode(table_tcode);
    if (ON_3dmArchiveTableType::Unset != tt)
    {
      // permit a second try
      if (static_cast<unsigned int>(Previous3dmTable()) > static_cast<unsigned int>(ON_3dmArchiveTableType::properties_table) )
        m_3dm_previous_table = ON_3dmArchiveTableType::properties_table;
    }
  }


  return rc;
}

bool ON_BinaryArchive::FindTableInDamagedArchive(
                const unsigned int tcode_table,
                const unsigned int tcode_record,
                const ON_UUID class_uuid,
                const int min_length_data
                )
{
  bool rc = FindMisplacedTable(
                  0,
                  tcode_table,
                  tcode_record,
                  class_uuid,
                  min_length_data
                  );
  return rc;
}

bool ON_BinaryArchive::EndRead3dmTable( unsigned int typecode )
{
  bool rc = false;
  if (0 == typecode)
  {
    ON_ERROR("ON_BinaryArchive::EndRead3dmTable() bad typecode");
    return false;
  }

  const ON_3dmArchiveTableType tt = TableTypeFromTypecode(typecode);
  if (tt == ON_3dmArchiveTableType::Unset)
  {
    ON_ERROR("ON_BinaryArchive::EndRead3dmTable() bad typecode");
    return false;
  }

  if ( Active3dmTable() != tt ) 
  {
    ON_ERROR("ON_BinaryArchive::EndRead3dmTable() m_active_table != t");
    return false;
  }

  if (false == ArchiveContains3dmTable(tt))
  {
    // This archive was written by code that was compiled before the table was added.
    return End3dmTable(tt,true);
  }

  if ( m_3dm_version == 1 ) 
  {
    if ( m_chunk.Count() != 0 )
    {
      ON_ERROR("ON_BinaryArchive::EndRead3dmTable() v1 file m_chunk.Count() != 0");
      return false;
    }
    // rewind for next table
    rc = SeekFromStart(32)?true:false;
  }
  else {
    {
      if ( m_chunk.Count() != 1 ) 
      {
        ON_ERROR("ON_BinaryArchive::EndRead3dmTable() v2 file m_chunk.Count() != 1");
        return false;
      }
      const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
      if ( 0 == c || c->m_typecode != typecode ) 
      {
        ON_ERROR("ON_BinaryArchive::EndRead3dmTable() m_chunk.Last()->typecode != typecode");
        return false;
      }
      rc = EndRead3dmChunk();
    }
  }
  return End3dmTable(m_3dm_active_table,rc);
}

ON_ModelComponent::Type ON_BinaryArchive::TableComponentType(
  ON_3dmArchiveTableType table_type
)
{
  ON_ModelComponent::Type model_component_type;
  switch (table_type)
  {
  case ON_3dmArchiveTableType::Unset:
    model_component_type = ON_ModelComponent::Type::Unset;
    break;
  case ON_3dmArchiveTableType::start_section:
    model_component_type = ON_ModelComponent::Type::Unset;
    break;
  case ON_3dmArchiveTableType::properties_table:
    model_component_type = ON_ModelComponent::Type::Unset;
    break;
  case ON_3dmArchiveTableType::settings_table:
    model_component_type = ON_ModelComponent::Type::Unset;
    break;
  case ON_3dmArchiveTableType::bitmap_table:
    model_component_type = ON_ModelComponent::Type::Image;
    break;
  case ON_3dmArchiveTableType::texture_mapping_table:
    model_component_type = ON_ModelComponent::Type::TextureMapping;
    break;
  case ON_3dmArchiveTableType::material_table:
    model_component_type = ON_ModelComponent::Type::RenderMaterial;
    break;
  case ON_3dmArchiveTableType::linetype_table:
    model_component_type = ON_ModelComponent::Type::LinePattern;
    break;
  case ON_3dmArchiveTableType::layer_table:
    model_component_type = ON_ModelComponent::Type::Layer;
    break;
  case ON_3dmArchiveTableType::group_table:
    model_component_type = ON_ModelComponent::Type::Group;
    break;
  case ON_3dmArchiveTableType::text_style_table:
    model_component_type = ON_ModelComponent::Type::TextStyle;
    break;
  case ON_3dmArchiveTableType::leader_style_table:
    model_component_type = ON_ModelComponent::Type::Unset;
    break;
  case ON_3dmArchiveTableType::dimension_style_table:
    model_component_type = ON_ModelComponent::Type::DimStyle;
    break;
  case ON_3dmArchiveTableType::light_table:
    model_component_type = ON_ModelComponent::Type::RenderLight;
    break;
  case ON_3dmArchiveTableType::hatchpattern_table:
    model_component_type = ON_ModelComponent::Type::HatchPattern;
    break;
  case ON_3dmArchiveTableType::instance_definition_table:
    model_component_type = ON_ModelComponent::Type::InstanceDefinition;
    break;
  case ON_3dmArchiveTableType::object_table:
    model_component_type = ON_ModelComponent::Type::ModelGeometry;
    break;
  case ON_3dmArchiveTableType::historyrecord_table:
    model_component_type = ON_ModelComponent::Type::HistoryRecord;
    break;
  case ON_3dmArchiveTableType::user_table:
    model_component_type = ON_ModelComponent::Type::Unset;
    break;
  case ON_3dmArchiveTableType::end_mark:
    model_component_type = ON_ModelComponent::Type::Unset;
    break;
  default:
    model_component_type = ON_ModelComponent::Type::Unset;
    break;
  }
  return model_component_type;
}


ON_3dmArchiveTableType ON_BinaryArchive::Active3dmTable() const
{
  return m_3dm_active_table;
}

ON_3dmArchiveTableType ON_BinaryArchive::Previous3dmTable() const
{
  return m_3dm_previous_table;
}


ON_3dmArchiveTableType ON_BinaryArchive::FirstFailed3dmTable() const
{
  return m_3dm_first_failed_table;
}

bool ON_BinaryArchive::BeginWrite3dmBitmapTable()
{
  return BeginWrite3dmTable( TCODE_BITMAP_TABLE );
}

bool ON_BinaryArchive::EndWrite3dmBitmapTable()
{
  return EndWrite3dmTable( TCODE_BITMAP_TABLE );
}

bool ON_BinaryArchive::Write3dmImageComponent(
  const ON_ModelComponentReference& model_component_reference
  )
{
  return Write3dmImageComponent(model_component_reference.ModelComponent());
}


bool ON_BinaryArchive::Write3dmImageComponent( 
  const ON_ModelComponent* model_component 
  )
{
  bool rc = false;
  for (;;)
  {
    const ON_Bitmap* image = ON_Bitmap::Cast(model_component);
    if (nullptr == image)
    {
      ON_ERROR("model_component parameter is not an image component.");
      break;
    }
    rc = Write3dmBitmap(*image);
    break;
  }
  return rc;
}

bool ON_BinaryArchive::Write3dmBitmap( const ON_Bitmap& bitmap )
{
  if (false == ArchiveContains3dmTable(ON_3dmArchiveTableType::bitmap_table))
    return true;

  if ( false == Internal_Begin3dmTableRecord(ON_3dmArchiveTableType::bitmap_table) )
    return false;

  bool rc = false;
  if ( m_3dm_version > 1 ) 
  {
    Internal_Increment3dmTableItemCount();
    const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
    if ( c && c->m_typecode == TCODE_BITMAP_TABLE ) 
    {
      rc = BeginWrite3dmChunk( TCODE_BITMAP_RECORD, 0 );
      if ( rc )
      {
        Internal_Write3dmUpdateManifest(bitmap);
        rc = WriteObject( bitmap );
        if ( !EndWrite3dmChunk() )
          rc = false;
      }
    }
    else 
    {
      Internal_ReportCriticalError();
      ON_ERROR("ON_BinaryArchive::Write3dmBitmap() must be called in BeginWrite3dmBitmapTable() block");
      rc = false;
    }
  }
  return rc;
}

bool ON_BinaryArchive::BeginRead3dmBitmapTable()
{
  return BeginRead3dmTable( TCODE_BITMAP_TABLE );
}

bool ON_BinaryArchive::EndRead3dmBitmapTable()
{
  return EndRead3dmTable( TCODE_BITMAP_TABLE );
}

int ON_BinaryArchive::Read3dmBitmap(  // returns 0 at end of bitmap table
                                      //         1 bitmap successfully read
          ON_Bitmap** ppBitmap // bitmap returned here
          )
{
  if ( false == Read3dmTableRecord(ON_3dmArchiveTableType::bitmap_table, (void**)ppBitmap))
    return 0;

  ON_Bitmap* bitmap = 0;
  int rc = 0;
  if ( m_3dm_version != 1 )
  {
    ON__UINT32 tcode = 0;
    ON__INT64 big_value = 0;
    if ( BeginRead3dmBigChunk( &tcode, &big_value ) ) 
    {
      if ( tcode == TCODE_BITMAP_RECORD ) 
      {
        Internal_Increment3dmTableItemCount();
        ON_Object* p = 0;
        if ( ReadObject( &p ) ) 
        {
          bitmap = ON_Bitmap::Cast(p);
          if (nullptr == bitmap)
          {
            ON_ERROR("ON_BinaryArchive::Read3dmBitmap() - corrupt bitmap table");
            delete p;
          }
          else
          {
            Internal_Read3dmUpdateManifest(*bitmap);
            if ( ppBitmap )
              *ppBitmap = bitmap;
            rc = 1;
          }
        }
      }
      else if ( tcode != TCODE_ENDOFTABLE )
      {
        ON_ERROR("ON_BinaryArchive::Read3dmBitmap() - corrupt bitmap table");
        Internal_ReportCriticalError();
      }
      EndRead3dmChunk();
    }
  }

  return rc;
}


bool ON_BinaryArchive::BeginWrite3dmLayerTable()
{
  return BeginWrite3dmTable( TCODE_LAYER_TABLE );
}

bool ON_BinaryArchive::Write3dmLayerComponent(
  const ON_ModelComponentReference& model_component_reference
  )
{
  return Write3dmLayerComponent(model_component_reference.ModelComponent());
}

bool ON_BinaryArchive::Write3dmLayerComponent( 
  const ON_ModelComponent* model_component 
  )
{
  bool rc = false;
  for (;;)
  {
    const ON_Layer* layer = ON_Layer::Cast(model_component);
    if (nullptr == layer)
    {
      ON_ERROR("model_component parameter is not a layer component.");
      break;
    }
    rc = Write3dmLayer(*layer);
    break;
  }
  return rc;
}


bool ON_BinaryArchive::Write3dmLayer( const ON_Layer&  layer )
{
  if (false == ArchiveContains3dmTable(ON_3dmArchiveTableType::layer_table))
    return true;

  if ( false == Internal_Begin3dmTableRecord(ON_3dmArchiveTableType::layer_table) )
    return false;

  bool rc = false;

  // version 2+
  const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
  if ( c && c->m_typecode == TCODE_LAYER_TABLE )
  {
    Internal_Increment3dmTableItemCount();
    rc = BeginWrite3dmChunk( TCODE_LAYER_RECORD, 0 );
    if ( rc )
    {
      Internal_Write3dmUpdateManifest(layer);
      rc = WriteObject( layer );
      if ( !EndWrite3dmChunk() )
        rc = false;
    }
  }
  else {
    Internal_ReportCriticalError();
    ON_ERROR("ON_BinaryArchive::Write3dmLayer() must be called in BeginWrite3dmLayerTable(2) block");
    rc = false;
  }

  return rc;
}

bool ON_BinaryArchive::EndWrite3dmLayerTable()
{
  return EndWrite3dmTable( TCODE_LAYER_TABLE );
}

bool ON_BinaryArchive::BeginRead3dmLayerTable()
{
  m_3dm_v1_layer_index = 0;
  bool rc = BeginRead3dmTable( TCODE_LAYER_TABLE );
  if ( rc && m_3dm_version == 1 )
  {
    rc = Seek3dmChunkFromStart( TCODE_LAYER );
    rc = true; // there are 1.0 files written by the old IO toolkit that have no layers
  }
  return rc;
}

int ON_BinaryArchive::Read3dmV1LayerIndex(const char* sV1LayerName) const
{
  // returns V1 layer index

  int layer_index = -1;

  if (    ON::archive_mode::read3dm == m_mode
       && 0 == m_3dm_opennurbs_version
       && 1 == m_3dm_version
       && 0 != m_V1_layer_list
       && 0 != sV1LayerName 
       && 0 != sV1LayerName[0] 
     )
  {
    struct ON__3dmV1LayerIndex* p = m_V1_layer_list;
    int i;
    for ( i = 0; 0 != p && i < 1000; i++ )
    {
      if ( p->m_layer_index < 0 )
        break;
      if ( p->m_layer_name_length < 1 || p->m_layer_name_length>256)
        break;
      if ( 0 == p->m_layer_name )
        break;
      if ( 0 == p->m_layer_name[0] )
        break;
      if ( 0 != p->m_layer_name[p->m_layer_name_length] )
        break;
      if ( !on_stricmp(p->m_layer_name,sV1LayerName) )
      {
        layer_index = p->m_layer_index;
        break;
      }
      p = p->m_next;
    }
  }

  return layer_index;
}

bool ON_BinaryArchive::Read3dmV1Layer( ON_Layer*& layer )
{
  ON_String s;
  bool rc = 0;
  ON__UINT32 tcode;
  ON__INT64 big_value;
  for (;;) 
  {
    tcode = 0;
    big_value = 0;
    if (!BeginRead3dmBigChunk(&tcode,&big_value))
      break; // assume we are at the end of the file
    if ( tcode == TCODE_LAYER ) {
      layer = new ON_Layer();
      layer->SetIndex(m_3dm_v1_layer_index++);
      rc = 1;
      break;
    }
    if (!EndRead3dmChunk())
       break;
  }
  if ( layer ) {
    rc = false;
    for (;;) 
    {
      tcode = 0;
      big_value = 0;
      if (!BeginRead3dmBigChunk(&tcode,&big_value))
        break;
      switch(tcode) 
      {
      case TCODE_LAYERNAME:
        {
          int slen = 0;
          ReadInt(&slen);
          if ( slen < 0 || slen > 10000 )
          {
            ON_ERROR("ON_BinaryArchive::Read3dmV1Layer() - invalid layer name length");
          }
          else
          {
            s.SetLength(slen);
            if ( ReadByte( s.Length(), s.Array() ) )
            {
              layer->SetName(ON_wString(s));
            }
          }
        }
        break;
      case TCODE_RGB:
        {
          ON__UINT64 rgb64 = (ON__UINT64)big_value;
          ON__UINT32 rgb32 = (ON__UINT32)rgb64;
          layer->SetColor( ON_Color((ON__UINT32)rgb32) );
        }
        break;
      case TCODE_LAYERSTATE:
        switch (big_value) 
        {
        case 1: // hidden
          layer->SetVisible(false);
          layer->SetLocked(false);
          break;
        case 2: // locked
          layer->SetVisible(true);
          layer->SetLocked(true);
          break;
        default: // normal
          layer->SetVisible(true);
          layer->SetLocked(false);
          break;
        }
        break;
      }
      if (!EndRead3dmChunk())
         break;
      if ( TCODE_ENDOFTABLE == tcode ) {
        rc = true;
        break;
      }
    }
    if ( !EndRead3dmChunk() ) // end of TCODE_LAYER chunk
      rc = false;
  }
  if ( !rc && layer ) 
  {
    delete layer;
    layer = 0;
  }
  else if (rc && layer)
  {
    // V1 files did not have layer ids.
    layer->SetId();
    if (    ON::archive_mode::read3dm == m_mode
         && 0 == m_3dm_opennurbs_version
         && 1 == m_3dm_version
         )
    {
      // save layer index and name in a linked list.
      int s_length = s.Length();
      const char* s_name = s.Array();
      if (    layer->Index() >= 0
           && s_length > 0
           && s_length < 256
           && 0 != s_name
           && 0 != s_name[0] 
         )
      {
        struct ON__3dmV1LayerIndex* p = (struct ON__3dmV1LayerIndex*)oncalloc(1, sizeof(*p) + (s_length+1)*sizeof(*p->m_layer_name) );
        p->m_layer_name = (char*)(p+1);
        p->m_layer_index = layer->Index();
        p->m_layer_name_length = s_length;
        memcpy(p->m_layer_name,s_name,s_length*sizeof(*p->m_layer_name));
        p->m_layer_name[s_length] = 0;
        p->m_next = m_V1_layer_list;
        m_V1_layer_list = p;
      }
    }
  }
  return rc;
}

int ON_BinaryArchive::Read3dmLayer( ON_Layer** ppLayer )
{
  if ( false == Read3dmTableRecord(ON_3dmArchiveTableType::layer_table, (void**)ppLayer))
    return 0;

  ON__UINT32 tcode;
  ON__INT64 big_value;
  ON_Layer* layer = nullptr;
  // returns 0 at end of layer table
  if ( m_3dm_version == 1 )
  {
    if (Read3dmV1Layer(layer) && nullptr != layer)
      Internal_Read3dmUpdateManifest(*layer);
  }
  else 
  {
    // version 2+
    tcode = 0;
    big_value = 0;
    if ( BeginRead3dmBigChunk( &tcode, &big_value ) )
    {
      if ( tcode == TCODE_LAYER_RECORD )
      {
        Internal_Increment3dmTableItemCount();
        ON_Object* p = 0;
        if ( ReadObject( &p ) )
        {
          layer = ON_Layer::Cast(p);
          if ( nullptr == layer )
            delete p;
          else
          {
            Internal_Read3dmUpdateManifest(*layer);
          }
        }
        if (nullptr == layer) {
          ON_ERROR("ON_BinaryArchive::Read3dmLayer() - corrupt layer table");
        }
      }
      else if ( tcode != TCODE_ENDOFTABLE ) {
        ON_ERROR("ON_BinaryArchive::Read3dmLayer() - corrupt layer table");
      }
      EndRead3dmChunk();
    }
  }
  if ( layer )
    layer->HasPerViewportSettings(ON_nil_uuid); // this call sets ON_Layer::m__runtime_flags
  *ppLayer = layer;
  return (layer) ? 1 : 0;
}

bool ON_BinaryArchive::EndRead3dmLayerTable()
{
  return EndRead3dmTable( TCODE_LAYER_TABLE );
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

bool ON_BinaryArchive::BeginWrite3dmGroupTable()
{
  return BeginWrite3dmTable( TCODE_GROUP_TABLE );
}

bool ON_BinaryArchive::Write3dmGroupComponent(
  const ON_ModelComponentReference& model_component_reference
  )
{
  return Write3dmGroupComponent(model_component_reference.ModelComponent());
}

bool ON_BinaryArchive::Write3dmGroupComponent( 
  const ON_ModelComponent* model_component 
  )
{
  bool rc = false;
  for (;;)
  {
    const ON_Group* group = ON_Group::Cast(model_component);
    if (nullptr == group)
    {
      ON_ERROR("model_component parameter is not a group component.");
      break;
    }
    rc = Write3dmGroup(*group);
    break;
  }
  return rc;
}


bool ON_BinaryArchive::Write3dmGroup( const ON_Group&  group )
{
  if (false == ArchiveContains3dmTable(ON_3dmArchiveTableType::group_table))
    return true;

  if ( false == Internal_Begin3dmTableRecord(ON_3dmArchiveTableType::group_table) )
    return false;

  bool rc = false;
  const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
  if ( c && c->m_typecode == TCODE_GROUP_TABLE ) 
  {
    Internal_Increment3dmTableItemCount();
    rc = BeginWrite3dmChunk( TCODE_GROUP_RECORD, 0 );
    if ( rc )
    {
      Internal_Write3dmUpdateManifest(group);
      rc = WriteObject( group );
      if ( !EndWrite3dmChunk() )
        rc = false;
    }
  }
  else {
    ON_ERROR("ON_BinaryArchive::Write3dmGroup() must be called in BeginWrite3dmGroupTable() block");
    rc = false;
  }

  return rc;
}

bool ON_BinaryArchive::EndWrite3dmGroupTable()
{
  return EndWrite3dmTable( TCODE_GROUP_TABLE );
}

bool ON_BinaryArchive::BeginRead3dmGroupTable()
{
  return BeginRead3dmTable( TCODE_GROUP_TABLE );
}

int ON_BinaryArchive::Read3dmGroup( ON_Group** ppGroup )
{
  if ( false == Read3dmTableRecord(ON_3dmArchiveTableType::group_table, (void**)ppGroup))
    return 0;

  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  ON_Group* group = nullptr;
  if ( BeginRead3dmBigChunk( &tcode, &big_value ) ) 
  {
    if ( tcode == TCODE_GROUP_RECORD ) 
    {
     Internal_Increment3dmTableItemCount();
      ON_Object* p = 0;
      if ( ReadObject( &p ) ) {
        group = ON_Group::Cast(p);
        if (!group)
          delete p;
        else
          Internal_Read3dmUpdateManifest(*group);
      }
      if (!group) {
        ON_ERROR("ON_BinaryArchive::Read3dmGroup() - corrupt group table");
      }
    }
    else if ( tcode != TCODE_ENDOFTABLE ) {
      ON_ERROR("ON_BinaryArchive::Read3dmGroup() - corrupt group table");
    }
    EndRead3dmChunk();
  }
  *ppGroup = group;
  return (group) ? 1 : 0;
}

bool ON_BinaryArchive::EndRead3dmGroupTable()
{
  return EndRead3dmTable( TCODE_GROUP_TABLE );
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

const ON_TextStyle* ON_BinaryArchive::ArchiveTextStyleFromArchiveTextStyleIndex(
  int archive_text_style_index
) const
{
  if (archive_text_style_index >= 0 && archive_text_style_index < m_archive_text_style_table.Count())
    return m_archive_text_style_table[archive_text_style_index];
  return nullptr;
}

////bool ON_BinaryArchive::WriteArchiveTextStyleIndex(
////  int dim_style_model_index
////)
////{
////  // In version 6, August 2016, text style information was moved to ON_DimStyle.
////  //
////  // When version 5 and earlier files are written, a text style is saved for each
////  // dimstyle and in the same order. This means the V5 text_style index = V5 dim_style index
////  // in the v5 archive.
////  //
////  // When version 6 files are saved a single text style is saved so versions of Rhino WIP
////  // delivered before August 2016 have a text style.
////  int v6_text_style_index = 0;
////  bool rc =
////     ( Archive3dmVersion() < 60 )
////     ? Write3dmReferencedComponentIndex(ON_ModelComponent::Type::DimStyle, dim_style_model_index)
////     : WriteInt(v6_text_style_index);
////  return rc;
////}

////bool ON_BinaryArchive::BeginWrite3dmTextStyleTable()
////{
////  // Does nothing. Text style information is on ON_DimStyle.
////  ON_ERROR("do not call ON_BinaryArchive::BeginWrite3dmTextStyleTable.");
////  return true;
////}
////
////bool ON_BinaryArchive::Write3dmTextStyle(
////  const class ON_TextStyle& text_style
////)
////{
////  // Does nothing. Text style information is on ON_DimStyle.
////  ON_ERROR("do not call ON_BinaryArchive::Write3dmTextStyle.");
////  return true;
////}
////
////bool ON_BinaryArchive::EndWrite3dmTextStyleTable()
////{
////  // Does nothing. Text style information is on ON_DimStyle.
////  ON_ERROR("do not call ON_BinaryArchive::EndWrite3dmTextStyleTable.");
////  return true;
////}

////bool ON_BinaryArchive::Internal_BeginWrite3dmTextStyleTable()
////{
////  return BeginWrite3dmTable( TCODE_FONT_TABLE );
////}



//bool ON_BinaryArchive::Write3dmTextStyleComponent(
//  const ON_ModelComponentReference& model_component_reference
//  )
//{
//  return Write3dmTextStyleComponent(model_component_reference.ModelComponent());
//}
//
//bool ON_BinaryArchive::Write3dmTextStyleComponent(
//  const ON_ModelComponent* model_component
//  )
//{
//  bool rc = false;
//  for (;;)
//  {
//    const ON_TextStyle* text_style = ON_TextStyle::Cast(model_component);
//    if (nullptr == text_style)
//    {
//      ON_ERROR("model_component parameter is not a text style component.");
//      break;
//    }
//    rc = Write3dmTextStyle(*text_style);
//    break;
//  }
//  return rc;
//}

bool ON_BinaryArchive::Internal_Write3dmTextStyle(
  const class ON_TextStyle& text_style
  )
{
  if (false == ArchiveContains3dmTable(ON_3dmArchiveTableType::text_style_table))
    return true;

  if ( false == Internal_Begin3dmTableRecord(ON_3dmArchiveTableType::text_style_table) )
   return false;

  Internal_Increment3dmTableItemCount();

  bool rc = false;

  const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
  if ( c && c->m_typecode == TCODE_FONT_TABLE ) 
  {
    rc = BeginWrite3dmChunk( TCODE_FONT_RECORD, 0 );
    if ( rc ) 
    {
      Internal_Write3dmUpdateManifest(text_style);
      rc = WriteObject( text_style );
      if ( !EndWrite3dmChunk() )
        rc = false;
    }
  }
  else 
  {
    ON_ERROR("ON_BinaryArchive::Write3dmTextStyle() must be called in BeginWrite3dmTextStyleTable() block");
    rc = false;
  }

  return rc;
}

////bool ON_BinaryArchive::Internal_EndWrite3dmTextStyleTable()
////{
////  return EndWrite3dmTable( TCODE_FONT_TABLE );
////}
////
////bool ON_BinaryArchive::BeginRead3dmTextStyleTable()
////{
////  ON_ERROR("Do not call BeginRead3dmTextStyleTable()");
////  return true;
////}
////
////
////int ON_BinaryArchive::Read3dmTextStyle(ON_TextStyle** ppTextStyle)
////{
////  ON_ERROR("Do not call Read3dmTextStyle()");
////  return 0;
////}
////
////bool ON_BinaryArchive::EndRead3dmTextStyleTable()
////{
////  ON_ERROR("Do not call EndRead3dmTextStyleTable()");
////  return true;
////}

int ON_BinaryArchive::Internal_Read3dmTextStyle( ON_TextStyle** ppTextStyle )
{
  if ( false == Read3dmTableRecord(ON_3dmArchiveTableType::text_style_table, (void**)ppTextStyle))
    return 0;

  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  ON_TextStyle* text_style = nullptr;
  if ( BeginRead3dmBigChunk( &tcode, &big_value ) ) 
  {
    if ( tcode == TCODE_FONT_RECORD )
    {
      Internal_Increment3dmTableItemCount();
      ON_Object* p = 0;
      if ( ReadObject( &p ) ) 
      {
        text_style = ON_TextStyle::Cast(p);
        if ( !text_style )
          delete p;
        else
        {
          Internal_Read3dmUpdateManifest(*text_style);
        }
      }
      if (!text_style) {
        ON_ERROR("ON_BinaryArchive::Read3dmTextStyle() - corrupt text_style table");
      }
    }
    else if ( tcode != TCODE_ENDOFTABLE ) {
      ON_ERROR("ON_BinaryArchive::Read3dmTextStyle() - corrupt text_style table");
    }
    EndRead3dmChunk();
  }
  *ppTextStyle = text_style;
  return (text_style) ? 1 : 0;
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////


bool ON_BinaryArchive::Internal_Write3dmDimStyle( const ON_DimStyle&  dimstyle, bool bUpdateManifest )
{
  if (false == ArchiveContains3dmTable(ON_3dmArchiveTableType::dimension_style_table))
    return true;
  
  if ( false == Internal_Begin3dmTableRecord(ON_3dmArchiveTableType::dimension_style_table) )
   return false;

  Internal_Increment3dmTableItemCount();

  bool rc = false;

  const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
  if ( c && c->m_typecode == TCODE_DIMSTYLE_TABLE )
  {
    rc = BeginWrite3dmChunk( TCODE_DIMSTYLE_RECORD, 0 );
    if ( rc )
    {
      if ( bUpdateManifest )
        Internal_Write3dmUpdateManifest(dimstyle);
      if (this->Archive3dmVersion() < 60)
      {
        const ON_V5x_DimStyle V5_dimstyle(
          this->Archive3dmSettings().m_ModelUnitsAndTolerances.m_unit_system.UnitSystem(),
          dimstyle
        );
        rc = WriteObject(V5_dimstyle);
      }
      else
      {
        rc = WriteObject(dimstyle);
      }
      if ( !EndWrite3dmChunk() )
        rc = false;
    }
  }
  else 
  {
    ON_ERROR("ON_BinaryArchive::Write3dmDimStyle() must be called in BeginWrite3dmDimStyleTable() block");
    rc = false;
  }

  return rc;
}

bool ON_BinaryArchive::BeginWrite3dmDimStyleTable()
{
  // August 2016. text style information is now on ON_DimStyle
  // A text style table must still be saved in archives so earlier versions of Rhino
  // can read the archives written by new versions.
  // 
  if (0 != m_archive_dim_style_table_status)
  {
    ON_ERROR("BeginWrite3dmDimStyleTable() called at the wrong time.");
    return false;
  }

  const unsigned int previous_table_index = static_cast<unsigned int>(Previous3dmTable());
  const unsigned int text_style_table_index = static_cast<unsigned int>(ON_3dmArchiveTableType::text_style_table);
  if (previous_table_index >= text_style_table_index)
  {
    ON_ERROR("archive contains text style information. This is incorrect.");
    return false;
  }

  m_archive_dim_style_table_status = 1;
  return true;
}

bool ON_BinaryArchive::Write3dmDimStyleComponent(
  const ON_ModelComponentReference& model_component_reference
  )
{
  return Write3dmDimStyleComponent(model_component_reference.ModelComponent());
}

bool ON_BinaryArchive::Write3dmDimStyleComponent(
  const ON_ModelComponent* model_component
  )
{
  bool rc = false;
  for (;;)
  {
    const ON_DimStyle* dimension_style = ON_DimStyle::Cast(model_component);
    if (nullptr == dimension_style)
    {
      ON_ERROR("model_component parameter is not a text style component.");
      break;
    }
    rc = Write3dmDimStyle(*dimension_style);
    break;
  }
  return rc;
}

bool ON_BinaryArchive::Write3dmDimStyle( const ON_DimStyle&  dimstyle )
{
  if ( dimstyle.ParentIdIsNotNil() || dimstyle.HasOverrides())
  {
    ON_ERROR("Override dimstyles are not stored in the dimstyle table in V6 files.");
    return true; // don't abort writing the file.
  }

  if (1 == m_archive_dim_style_table_status)
  {
    if (0 != m_archive_dim_style_table.UnsignedCount())
    {
      ON_ERROR("Write3dmDimStyle() called at the incorrect time");
      return false;
    }
    m_archive_dim_style_table_status = 2;
  }
  else if (2 == m_archive_dim_style_table_status)
  {
    if (m_archive_dim_style_table.UnsignedCount() <= 0 )
    {
      ON_ERROR("Write3dmDimStyle() called at the incorrect time");
      return false;
    }
  }

  ON_DimStyle* copy_of_model_dimstyle = new ON_DimStyle(dimstyle);
  if (nullptr != copy_of_model_dimstyle)
  {
    Internal_Write3dmUpdateManifest(*copy_of_model_dimstyle);
    m_archive_dim_style_table.Append(copy_of_model_dimstyle);
    if (nullptr == m_archive_current_dim_style)
    {
      if (nullptr != m_archive_3dm_settings)
      {
        if (dimstyle.IdIsNotNil() && dimstyle.Id() == m_archive_3dm_settings->CurrentDimensionStyleId())
          m_archive_current_dim_style = copy_of_model_dimstyle;
      }
    }
  }

  return true;
}

bool ON_BinaryArchive::EndWrite3dmDimStyleTable()
{
  if (m_archive_dim_style_table_status < 1 || m_archive_dim_style_table_status > 2)
  {
    ON_ERROR("EndWrite3dmDimStyleTable() called at the incorrect time");
    return false;
  }

  // August 2016. text style information is now on ON_DimStyle
  // A text style table must still be saved in archives so earlier versions of Rhino
  // can read the archives written by new versions.
  // For V6 files this is empty as of December 15 2016. We've given the WIP system
  // 4 months to transition from a pre Aut 2016 Rhino V6 WIP to a post Aug 2016 Rhino V6 WIP.
  bool rc = true;
  {
    // Write one text style for every dimension style
    rc = BeginWrite3dmTable(TCODE_FONT_TABLE);
    if (false == rc)
      return false;

    // Archive3dmVersion() < 60 added December 15, 2016.
    if (Archive3dmVersion() < 60)
    {
      for (int j = 0; j < m_archive_dim_style_table.Count() && rc; j++)
      {
        const ON_DimStyle* dim_style = m_archive_dim_style_table[j];
        if (nullptr == dim_style)
          continue;
        ON_TextStyle archive_text_style;
        archive_text_style.SetFont(dim_style->FontCharacteristics());
        archive_text_style.SetId(); // we need a new and unique id.
        archive_text_style.SetIndex(dim_style->Index());
        archive_text_style.SetName(dim_style->Name());
        rc = Internal_Write3dmTextStyle(archive_text_style);
      }
    }

    if (!EndWrite3dmTable(TCODE_FONT_TABLE))
      rc = false;

    if (false == rc)
      return false;
  }

  rc = BeginWrite3dmTable(TCODE_DIMSTYLE_TABLE);
  
  if (false == rc)
    return false;
  
  for (int j = 0; j < m_archive_dim_style_table.Count() && rc; j++)
  {
    const ON_DimStyle* dim_style = m_archive_dim_style_table[j];
    if (nullptr == dim_style)
      continue;
    rc = Internal_Write3dmDimStyle(*dim_style, false);
  }

  if (false == EndWrite3dmTable(TCODE_DIMSTYLE_TABLE))
    rc = false;

  m_annotation_context.SetReferencedDimStyle(&ArchiveCurrentDimStyle(),nullptr,ArchiveCurrentDimStyleIndex());

  return rc;
}

const ON_DimStyle* ON_BinaryArchive::Internal_ArchiveCurrentDimStyle()
{
  ON::LengthUnitSystem model_unit_system = ON::LengthUnitSystem::Unset;
  if (nullptr != m_archive_3dm_settings)
  {
    model_unit_system = m_archive_3dm_settings->m_ModelUnitsAndTolerances.m_unit_system.UnitSystem();
    const ON_UUID id = m_archive_3dm_settings->CurrentDimensionStyleId();
    if (ON_nil_uuid != id)
    {
      for (unsigned int i = 0; i < m_archive_dim_style_table.UnsignedCount(); i++)
      {
        const ON_DimStyle* archive_dim_style = m_archive_dim_style_table[i];
        if (archive_dim_style->ParentIdIsNotNil())
          continue;
        if ( id == archive_dim_style->Id())
        {
          return archive_dim_style;
          break;
        }
      }
    }

    const int index = m_archive_3dm_settings->CurrentDimensionStyleIndex();
    if (index >= 0 && index < m_archive_dim_style_table.Count() && nullptr != m_archive_dim_style_table[index] && m_archive_dim_style_table[index]->ParentIdIsNotNil() )
      return m_archive_dim_style_table[index];

    if (ON::IsTerrestrialLengthUnit(model_unit_system))
    {
      double unit_scale = 1e300;
      const ON_DimStyle* inch_mm_ds = nullptr;
      const ON_DimStyle* unit_scale_ds = nullptr;
      for (unsigned int i = 0; i < m_archive_dim_style_table.UnsignedCount(); i++)
      {
        const ON_DimStyle* archive_dim_style = m_archive_dim_style_table[i];
        if (archive_dim_style->ParentIdIsNotNil())
          continue;
        if (false == archive_dim_style->UnitSystemIsSet())
          continue;

        const ON::LengthUnitSystem ds_unit_system = archive_dim_style->UnitSystem();
        if (ds_unit_system == model_unit_system)
          return archive_dim_style;

        if (nullptr == m_archive_current_dim_style)
        {
          if (ON::IsUnitedStatesCustomaryLengthUnit(model_unit_system) && ON::LengthUnitSystem::Inches == ds_unit_system)
          {
            inch_mm_ds = archive_dim_style;
          }
          else if (ON::IsMetricLengthUnit(model_unit_system) && ON::LengthUnitSystem::Millimeters == ds_unit_system)
          {
            inch_mm_ds = archive_dim_style;
          }
        }

        double s = ON::UnitScale(model_unit_system, ds_unit_system);
        if (s < 1.0)
          s = ON::UnitScale(ds_unit_system, model_unit_system);
        if (s > 1.0 && s < unit_scale)
        {
          unit_scale_ds = archive_dim_style;
          unit_scale = s;
        }
      }
      if (nullptr != inch_mm_ds)
        return inch_mm_ds;
      if (nullptr != unit_scale_ds)
        return unit_scale_ds;
    }
  }

  for (unsigned int i = 0; i < m_archive_dim_style_table.UnsignedCount(); i++)
  {
    const ON_DimStyle* archive_dim_style = m_archive_dim_style_table[i];
    if (archive_dim_style->ParentIdIsNotNil())
      continue;
    if (false == archive_dim_style->UnitSystemIsSet())
      continue;
    return archive_dim_style;
  }
  
  const ON_DimStyle* system_ds;
  if (ON::IsUnitedStatesCustomaryLengthUnit(model_unit_system))
    system_ds = &ON_DimStyle::DefaultInchDecimal;  
  else if (ON::IsMetricLengthUnit(model_unit_system))
    system_ds = &ON_DimStyle::DefaultMillimeterSmall;
  else
    system_ds = &ON_DimStyle::Default;

  // invent a current dimstyle. Happens when reading files written by Rhino 1.1.
  ON_DimStyle* current_ds = new ON_DimStyle(*system_ds);
  current_ds->SetId();
  current_ds->SetIndex(m_archive_dim_style_table.Count());
  if ( ON::archive_mode::read3dm == Mode())
    Internal_Read3dmUpdateManifest(*current_ds);
  else
    m_manifest.AddComponentToManifest(*current_ds, true, nullptr);

  m_archive_dim_style_table.Append(current_ds);

  return current_ds;
}

double ON_BinaryArchive::Internal_ArchiveModelSpaceTextScale() const
{
  const double default_model_space_text_scale = 1.0;

  const double model_space_text_scale
    = (nullptr != m_archive_3dm_settings && m_archive_3dm_settings->m_AnnotationSettings.Is_V5_AnnotationScalingEnabled())
    ? m_archive_3dm_settings->m_AnnotationSettings.WorldViewTextScale()
    : default_model_space_text_scale;

  return (model_space_text_scale > 0.0 && ON_IsValid(model_space_text_scale)) ? model_space_text_scale : default_model_space_text_scale;
}

void ON_BinaryArchive::Internal_ConvertTextStylesToDimStyles()
{
  m_text_style_to_dim_style_archive_index_map.SetCount(0);
  const int archive_text_style_count = m_archive_text_style_table.Count();
  if (archive_text_style_count <= 0)
    return;
  m_text_style_to_dim_style_archive_index_map.Reserve(archive_text_style_count);
  
  const int current_ds_index
    = (nullptr == m_archive_current_dim_style)
    ? -1
    : m_archive_current_dim_style->Index();

  for (int i = 0; i < m_archive_text_style_table.Count(); i++)
  {
    ON_2dex& ts_to_ds = m_text_style_to_dim_style_archive_index_map.AppendNew();
    ts_to_ds.i = i;
    ts_to_ds.j 
      = (nullptr == m_archive_text_style_table[i] )
      ? current_ds_index
      : ON_UNSET_INT_INDEX;
  }

  const int archive_dim_style_count = m_archive_dim_style_table.Count();


  for (;;)
  {
    // see if we need to map text styles to dimstyles
    const unsigned int archive_opennurbs_version = ArchiveOpenNURBSVersion();
    unsigned int version_major = 0;
    unsigned int version_minor = 0;
    unsigned int version_year = 0;
    unsigned int version_month = 0;
    unsigned int version_day_of_month = 0;
    unsigned int version_branch = 0;
    bool bParsedVersionNumber = ON_VersionNumberParse(
      archive_opennurbs_version,
      &version_major,
      &version_minor,
      &version_year,
      &version_month,
      &version_day_of_month,
      &version_branch
    );
    if (false == bParsedVersionNumber)
      break;
    if (version_major < 6)
      break;
    if (version_major == 6)
    {
      // version 6 files written before aug 15 2016 have text styles.
      if ((version_year * 10000 + version_month * 100 + version_day_of_month) < (2016 * 10000 + 8 * 100 + 15))
        break;
    }

    // 3dm archive created with new code that has no text style index references.
    // Ignore "fake" text style table in written by new code so files
    // could be read by older code.
    for (int i = 0; i < m_archive_text_style_table.Count(); i++)
      m_text_style_to_dim_style_archive_index_map[i].j = current_ds_index;

    return;
  }

  // Map text styles to dimstyles, creating new dimstyles as required.
  const double model_view_text_scale = Internal_ArchiveModelSpaceTextScale();

  for (int i = 0; i < archive_text_style_count; i++)
  {
    ON_2dex& ts_to_ds = m_text_style_to_dim_style_archive_index_map[i];
    if (ON_UNSET_INT_INDEX != ts_to_ds.j)
      continue; // this text style is already mapped.

    const ON_TextStyle* text_style = m_archive_text_style_table[i];
    if (nullptr == text_style)
    {
      ts_to_ds.j = current_ds_index;
      continue;
    }

    const ON_Font& font = text_style->Font();
    const unsigned int font_sn = font.ManagedFontSerialNumber();
    
    double delta_scale = 1e300;
    for (int j = 0; j < archive_dim_style_count; j++)
    {
      const ON_DimStyle* archive_dim_style = m_archive_dim_style_table[j];
      if (nullptr == archive_dim_style)
        continue;
      if (archive_dim_style->ParentIdIsNotNil())
        continue;
      if (font_sn != archive_dim_style->Font().ManagedFontSerialNumber())
        continue;

      // Do not require exact model_view_text_scale = DimScale(), 
      // We will simply override this property
      // on a per object basis when that is required.
      double d = fabs(model_view_text_scale - archive_dim_style->DimScale());
      if (ON_UNSET_INT_INDEX == ts_to_ds.j || d < delta_scale)
      {
        ts_to_ds.j = j;
        delta_scale = d;
        if (0.0 == delta_scale)
          break;
      }
    }

    if (ON_UNSET_INT_INDEX == ts_to_ds.j)
    {
      // need to make a new dim style for this font.
      ON_DimStyle* dim_style = ON_DimStyle::CreateFromFont(&font, model_view_text_scale, nullptr, &m_manifest, nullptr);
      ts_to_ds.j = m_archive_dim_style_table.Count();
      dim_style->ClearIndex();
      dim_style->SetId();
      const ON::LengthUnitSystem dim_style_unit_system
        = ON::IsUnitedStatesCustomaryLengthUnit(Archive3dmSettings().m_ModelUnitsAndTolerances.m_unit_system.UnitSystem())
        ? ON::LengthUnitSystem::Inches
        : ON::LengthUnitSystem::Millimeters;
      dim_style->SetUnitSystem( dim_style_unit_system );
      m_archive_dim_style_table.Append(dim_style);
      Internal_Read3dmUpdateManifest(*dim_style);
    }

    // If other text styles use the same font, map them as well
    for (int k = i + 1; k < archive_text_style_count; k++)
    {
      text_style = m_archive_text_style_table[k];
      if (nullptr == text_style)
        continue;
      if (font_sn != text_style->Font().ManagedFontSerialNumber())
        continue;
      m_text_style_to_dim_style_archive_index_map[k].j = ts_to_ds.j;
    }
  }
}

bool ON_BinaryArchive::BeginRead3dmDimStyleTable()
{
  // August 2016. text style information is now on ON_DimStyle
  // A text style table must still be saved in archives so earlier versions of Rhino
  // can read the archives written by new versions.
  if (0 != m_archive_dim_style_table_status || ON_UNSET_UINT_INDEX != m_archive_dim_style_table_read_index)
  {
    ON_ERROR("BeginRead3dmDimStyleTable() has already been called.");
    return false;
  }

  m_archive_dim_style_table_read_index = 0;
  
  // read legacy text style table
  if (!BeginRead3dmTable(TCODE_FONT_TABLE))
    return false;

  for (;;)
  {
    ON_TextStyle* text_style = nullptr;
    Internal_Read3dmTextStyle(&text_style);
    if (nullptr == text_style)
      break;
    m_archive_text_style_table.Append(text_style);
  }
  const int archive_text_style_count = m_archive_text_style_table.Count();
  m_text_style_to_dim_style_archive_index_map.SetCount(0);
  m_text_style_to_dim_style_archive_index_map.Reserve(archive_text_style_count);
  for (int i = 0; i < archive_text_style_count; i++)
  {
    ON_2dex& ts_to_ds = m_text_style_to_dim_style_archive_index_map.AppendNew();
    ts_to_ds.i = i;
    ts_to_ds.j = ON_UNSET_INT_INDEX;
  }

  if (!EndRead3dmTable(TCODE_FONT_TABLE))
    return false;

  if (!BeginRead3dmTable(TCODE_DIMSTYLE_TABLE))
    return false;

  m_archive_dim_style_table_status = 1;

  // read all the dimstyles in the 3dm archive
  for (;;)
  {
    ON_DimStyle* archive_dim_style = nullptr;
    int rc = Internal_Read3dmDimStyle(&archive_dim_style);
    const ON::LengthUnitSystem archive_unit_system = Archive3dmSettings().m_ModelUnitsAndTolerances.m_unit_system.UnitSystem();
    if (nullptr != archive_dim_style)
    {
      if (archive_dim_style->ParentId() == archive_dim_style->Id())
      {
        ON_ERROR("Invalid dimstyle parent id in archive.");
        archive_dim_style->ClearParentId();
      }

      if ( archive_dim_style->ParentIdIsNil() )
        archive_dim_style->ClearAllFieldOverrides();
      else
        m_bLegacyOverrideDimStylesInArchive = true;

      archive_dim_style->SetUnitSystemFromContext(true, archive_unit_system, ON::LengthUnitSystem::None);
      m_archive_dim_style_table.Append(archive_dim_style);
    }
    if (rc <= 0)
      break;
  }

  if (m_bLegacyOverrideDimStylesInArchive)
  {
    m_bLegacyOverrideDimStylesInArchive = false;
    for (unsigned int j = 0; j < m_archive_dim_style_table.UnsignedCount(); j++)
    {
      ON_DimStyle* archive_dim_style = m_archive_dim_style_table[j];
      if (archive_dim_style->ParentIdIsNil())
        continue;

      const ON_UUID parent_id = archive_dim_style->ParentId();

      ON_DimStyle* archive_parent_dim_style = nullptr;
      for (unsigned int i = 0; i < m_archive_dim_style_table.UnsignedCount(); i++)
      {
        ON_DimStyle* ds = m_archive_dim_style_table[i];
        if (ds->ParentIdIsNotNil())
          continue;
        if (parent_id == ds->Id())
        {
          archive_parent_dim_style = ds;
          break;
        }
      }

      if (nullptr == archive_parent_dim_style)
      {
        ON_ERROR("Invalid dimstyle parent id in archive.");
        archive_dim_style->ClearAllFieldOverrides();
        archive_dim_style->ClearParentId();
        continue;
      }
    }
  }

  for (unsigned int j = 0; j < m_archive_dim_style_table.UnsignedCount(); j++)
  {
    ON_DimStyle* archive_dim_style = m_archive_dim_style_table[j];
    archive_dim_style->ClearIndex();
    if (archive_dim_style->ParentIdIsNotNil())
    {
      m_bLegacyOverrideDimStylesInArchive = true;
      continue;
    }
    Internal_Read3dmUpdateManifest(*archive_dim_style);
  }

  // Set a current dimstyle.
  m_archive_current_dim_style = Internal_ArchiveCurrentDimStyle();

  // Set the current annotation context
  int V5_archive_dim_style_index = ON_UNSET_INT_INDEX;
  if (nullptr != m_archive_current_dim_style)
  {
    if (m_archive_current_dim_style->IsSystemComponent())
    {
      V5_archive_dim_style_index = m_archive_current_dim_style->Index();
    }
    else
    {
      for (unsigned int j = 0; j < m_archive_dim_style_table.UnsignedCount(); j++)
      {
        if (m_archive_current_dim_style == m_archive_dim_style_table[j])
        {
          V5_archive_dim_style_index = j;
          break;
        }
      }
    }
  }

  m_annotation_context.SetReferencedDimStyle(m_archive_current_dim_style,nullptr,V5_archive_dim_style_index);

  // convert text styles to dimstyles
  Internal_ConvertTextStylesToDimStyles();

  return true; // must return true because calling code must call EndRead3dmDimStyleTable().
}

int ON_BinaryArchive::Read3dmDimStyle(
  class ON_DimStyle** ppDimStyle
)
{
  if (nullptr != ppDimStyle)
    *ppDimStyle = nullptr;

  if (1 != m_archive_dim_style_table_status || m_archive_dim_style_table_read_index >= ON_UNSET_UINT_INDEX - 1)
  {
    ON_ERROR("All calls to Read3dmDimStyle() must be after a single call to BeginRead3dmDimStyleTable() and before a single call to EndRead3dmDimStyleTable().");
    return 0;
  }

  ON_DimStyle* dim_style = nullptr;
  while (m_archive_dim_style_table_read_index < m_archive_dim_style_table.UnsignedCount())
  {
    const unsigned int i = m_archive_dim_style_table_read_index++;
    ON_DimStyle* archive_dim_style = m_archive_dim_style_table[i];
    if (nullptr == archive_dim_style)
      continue;
    if (archive_dim_style->ParentIdIsNotNil())
      continue;

    ON_DimStyle* managed_dim_style = new ON_DimStyle(*archive_dim_style);
    m_archive_dim_style_table[i] = managed_dim_style;
    m_annotation_context.UpdateReferencedDimStyle(archive_dim_style, managed_dim_style);
    if (archive_dim_style == m_archive_current_dim_style)
      m_archive_current_dim_style = managed_dim_style;
    dim_style = archive_dim_style;
    break;
  }

  if (nullptr == dim_style)
  {
    m_archive_dim_style_table_read_index = ON_UNSET_UINT_INDEX - 1;
    return 0;
  }

  if (nullptr != ppDimStyle)
    *ppDimStyle = dim_style;

  return 1;
}

int ON_BinaryArchive::Internal_Read3dmDimStyle(
  class ON_DimStyle**ppDimStyle
  )
{
  if ( false == Read3dmTableRecord(ON_3dmArchiveTableType::dimension_style_table, (void**)ppDimStyle))
    return 0;

  int rc = -1;
  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  if ( BeginRead3dmBigChunk( &tcode, &big_value ) ) 
  {
    if ( tcode == TCODE_DIMSTYLE_RECORD )
    {
      Internal_Increment3dmTableItemCount();

      ON_Object* p = nullptr;
      if ( ReadObject( &p ) ) 
      {
        ON_DimStyle* V6_dimstyle = ON_DimStyle::Cast(p);
        int legacy_text_style_index = ON_UNSET_INT_INDEX;
        if (nullptr == V6_dimstyle)
        {
          ON_V5x_DimStyle* V5_dimstyle = ON_V5x_DimStyle::Cast(p);
          if (nullptr != V5_dimstyle)
          {
            legacy_text_style_index = V5_dimstyle->V5TextStyle().Index();
            V6_dimstyle = new ON_DimStyle(
              this->Archive3dmSettings().m_ModelUnitsAndTolerances.m_unit_system.UnitSystem(),
              *V5_dimstyle
            );
            // This was the behavior for leader text alignment in v5 and didn't have a field in v5 dimstyles.
            // The default so far in V6 is Middle which only looks like v5 with single line leader text
            V6_dimstyle->SetLeaderTextVerticalAlignment(ON::TextVerticalAlignment::MiddleOfTop);
            // old files do not contain unit system information
            // Keep in mind this V5 file may have be written as a "SaveAs V5" from V6 or later.
            // That's why we are checking for a matching system dimstyle before using the unit
            // system from the file.
            V6_dimstyle->SetUnitSystem(ON::LengthUnitSystem::None);
            V6_dimstyle->SetUnitSystemFromContext(true,Archive3dmSettings().m_ModelUnitsAndTolerances.m_unit_system.UnitSystem(),ON::LengthUnitSystem::None);
            delete V5_dimstyle;
          }
          else
          {
            delete p;
            p = nullptr;
          }
        }

        if (nullptr == V6_dimstyle) 
        {
          ON_ERROR("ON_BinaryArchive::Read3dmDimStyle() - corrupt annotation style table");
        }
        else
        {
          rc = 1;
          *ppDimStyle = V6_dimstyle;
        }
      }
    }
    else if (TCODE_ENDOFTABLE == tcode)
    {
      // end of dimension style table
          rc = 0;
    }
    else
    {
      ON_ERROR("ON_BinaryArchive::Read3dmDimStyle() - corrupt annotation style table");
    }
    EndRead3dmChunk();
  }
  
  return rc;
}

bool ON_BinaryArchive::EndRead3dmDimStyleTable()
{
  return EndRead3dmTable( TCODE_DIMSTYLE_TABLE );
}


const ON_DimStyle& ON_BinaryArchive::ArchiveCurrentDimStyle() const
{
  return
    (nullptr == m_archive_current_dim_style)
    ? ON_DimStyle::Default
    : *m_archive_current_dim_style;
}

const int ON_BinaryArchive::ArchiveCurrentDimStyleIndex() const
{
  const ON_DimStyle& dim_style = ArchiveCurrentDimStyle();
  if (dim_style.IsSystemComponent())
    return dim_style.Index();

  const ON_ComponentManifestItem& item = m_manifest.ItemFromId(ON_ModelComponent::Type::DimStyle,ArchiveCurrentDimStyle().Id());
  if (item.IsValid())
    return item.Index();

  return -1;
}

const ON_UUID ON_BinaryArchive::ArchiveCurrentDimStyleId() const
{
  return ArchiveCurrentDimStyle().Id();
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

bool ON_BinaryArchive::BeginWrite3dmHatchPatternTable()
{
  return BeginWrite3dmTable( TCODE_HATCHPATTERN_TABLE );
}

bool ON_BinaryArchive::Write3dmHatchPatternComponent(
  const ON_ModelComponentReference& model_component_reference
  )
{
  return Write3dmHatchPatternComponent(model_component_reference.ModelComponent());
}

bool ON_BinaryArchive::Write3dmHatchPatternComponent(
  const ON_ModelComponent* model_component
  )
{
  bool rc = false;
  for (;;)
  {
    const ON_HatchPattern* hatch_pattern = ON_HatchPattern::Cast(model_component);
    if (nullptr == hatch_pattern)
    {
      ON_ERROR("model_component parameter is not a hatch pattern component.");
      break;
    }
    rc = Write3dmHatchPattern(*hatch_pattern);
    break;
  }
  return rc;
}

bool ON_BinaryArchive::Write3dmHatchPattern( const ON_HatchPattern&  pattern )
{
  if (false == ArchiveContains3dmTable(ON_3dmArchiveTableType::hatchpattern_table))
    return true;

  if ( false == Internal_Begin3dmTableRecord(ON_3dmArchiveTableType::hatchpattern_table) )
   return false;

  Internal_Increment3dmTableItemCount();

  bool rc = false;

  const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
  if ( c && c->m_typecode == TCODE_HATCHPATTERN_TABLE ) 
  {
    rc = BeginWrite3dmChunk( TCODE_HATCHPATTERN_RECORD, 0 );
    if (rc)
    {
      Internal_Write3dmUpdateManifest(pattern);
      rc = WriteObject( pattern );
      if ( !EndWrite3dmChunk() )
        rc = false;
    }

    // 1 Nov 2005 Dale Lear:
    //
    //   This code was used before version 200511010.  The reader can
    //   still read the old files, but old versions of Rhino cannot read
    //   files written with version 200511010 or later.  This happened in
    //   the early beta cycile of V4.  V3 did not have hatch patterns.
    //   Please leave this comment here until Nov 2006 so I can remember
    //   what happened if I have to debug file IO.  By May 2006, all
    //   the betas that could write the bogus hatch tables should have
    //   expired.
    //
    //if ( rc ) {
    //  rc = pattern.Write( *this)?true:false;
    //  if ( !EndWrite3dmChunk())
    //    rc = false;
    //}
  }
  else 
  {
    ON_ERROR("ON_BinaryArchive::Write3dmHatchPattern() must be called in BeginWrite3dmHatchPatternTable() block");
    rc = false;
  }

  return rc;
}

bool ON_BinaryArchive::EndWrite3dmHatchPatternTable()
{
  return EndWrite3dmTable( TCODE_HATCHPATTERN_TABLE );
}

bool ON_BinaryArchive::BeginRead3dmHatchPatternTable()
{
  return BeginRead3dmTable( TCODE_HATCHPATTERN_TABLE );
}

int ON_BinaryArchive::Read3dmHatchPattern( ON_HatchPattern** ppPattern )
{
  if ( false == Read3dmTableRecord(ON_3dmArchiveTableType::hatchpattern_table, (void**)ppPattern))
    return 0;

  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  ON_HatchPattern* hatch_pattern = nullptr;
  if( BeginRead3dmBigChunk( &tcode, &big_value)) 
  {
    if ( tcode == TCODE_HATCHPATTERN_RECORD ) 
    {
      Internal_Increment3dmTableItemCount();

      if ( m_3dm_opennurbs_version < 200511010 )
      {
        // There was a bug in Write3dmHatchPattern and files written 
        // before version 200511010 didn't use ON_Object IO.
        hatch_pattern = new ON_HatchPattern;
        if( !hatch_pattern->Read( *this))
        {
          delete hatch_pattern;
          hatch_pattern = nullptr;
          ON_ERROR("ON_BinaryArchive::Read3dmHatchPattern() - corrupt hatch pattern table");
        }
      }
      else
      {
        ON_Object* p = 0;
        if ( ReadObject( &p ) ) 
        {
          hatch_pattern = ON_HatchPattern::Cast(p);
          if ( nullptr == hatch_pattern )
            delete p;
        }
        if (nullptr == hatch_pattern) 
        {
          ON_ERROR("ON_BinaryArchive::Read3dmHatchPattern() - corrupt hatch pattern table");
        }
      }
    }
    else if ( tcode != TCODE_ENDOFTABLE ) 
    {
      ON_ERROR("ON_BinaryArchive::Read3dmHatchPattern() - corrupt hatch pattern table");
    }

    EndRead3dmChunk();
  }
  if (nullptr != hatch_pattern)
    Internal_Read3dmUpdateManifest(*hatch_pattern);
  *ppPattern = hatch_pattern;
  return( hatch_pattern) ? 1 : 0;
}

bool ON_BinaryArchive::EndRead3dmHatchPatternTable()
{
  return EndRead3dmTable( TCODE_HATCHPATTERN_TABLE);
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

bool ON_BinaryArchive::BeginWrite3dmLinetypeTable()
{
  bool rc = BeginWrite3dmTable( TCODE_LINETYPE_TABLE );
  return rc;
}

bool ON_BinaryArchive:: Write3dmLinePatternComponent(
  const ON_ModelComponentReference& model_component_reference
  )
{
  return Write3dmLinePatternComponent(model_component_reference.ModelComponent());
}


bool ON_BinaryArchive::Write3dmLinePatternComponent( 
  const ON_ModelComponent* model_component 
  )
{
  bool rc = false;
  for (;;)
  {
    const ON_Linetype* line_pattern = ON_Linetype::Cast(model_component);
    if (nullptr == line_pattern)
    {
      ON_ERROR("model_component parameter is not a line pattern component.");
      break;
    }
    rc = Write3dmLinetype(*line_pattern);
    break;
  }
  return rc;
}

bool ON_BinaryArchive::Write3dmLinetype(
  const ON_Linetype& line_pattern
  )
{
  if (false == ArchiveContains3dmTable(ON_3dmArchiveTableType::linetype_table))
    return true;

  if ( false == Internal_Begin3dmTableRecord(ON_3dmArchiveTableType::linetype_table) )
    return false;

  Internal_Increment3dmTableItemCount();

  bool rc = false;

  if( Active3dmTable() != ON_3dmArchiveTableType::linetype_table ) 
  {
    Internal_ReportCriticalError();
    ON_ERROR("ON_BinaryArchive::Write3dmLinetype() - m_active_table != linetype_table");
  }

  const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
  if ( c && c->m_typecode == TCODE_LINETYPE_TABLE ) 
  {
    rc = BeginWrite3dmChunk( TCODE_LINETYPE_RECORD, 0 );
    if ( rc ) 
    {
      Internal_Write3dmUpdateManifest(line_pattern);
      rc = WriteObject( line_pattern );
      if ( !EndWrite3dmChunk())
        rc = false;
    }
  }
  else 
  {
    Internal_ReportCriticalError();
    ON_ERROR("ON_BinaryArchive::Write3dmLinetype() must be called in BeginWrite3dmLinetypeTable() block");
    rc = false;
  }

  return rc;
}

bool ON_BinaryArchive::EndWrite3dmLinetypeTable()
{
  return EndWrite3dmTable( TCODE_LINETYPE_TABLE );
}

bool ON_BinaryArchive::BeginRead3dmLinetypeTable()
{
  return BeginRead3dmTable( TCODE_LINETYPE_TABLE );
}

int ON_BinaryArchive::Read3dmLinetype( ON_Linetype** ppLinetype )
{
  if ( false == Read3dmTableRecord(ON_3dmArchiveTableType::linetype_table, (void**)ppLinetype))
    return 0;

  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  ON_Linetype* linetype = nullptr;
  int rc = -1;
  if( BeginRead3dmBigChunk( &tcode, &big_value)) 
  {
    if ( tcode == TCODE_LINETYPE_RECORD ) 
    {
      Internal_Increment3dmTableItemCount();
      ON_Object* p = 0;
      if ( ReadObject( &p ) )
      {
        linetype = ON_Linetype::Cast(p);
        if (!linetype )
          delete p;
        else
        {
          if (ppLinetype)
            *ppLinetype = linetype;
          Internal_Read3dmUpdateManifest(*linetype);
          rc = 1;
        }
      }
      if (!linetype)
      {
        Internal_ReportCriticalError();
        ON_ERROR("ON_BinaryArchive::Read3dmLinetype() - corrupt linetype table");
      }
    }
    else if ( tcode == TCODE_ENDOFTABLE ) 
    {
     // end of linetype table
      rc = 0;
    }
    else
    {
      Internal_ReportCriticalError();
      ON_ERROR("ON_BinaryArchive::Read3dmLinetype() - corrupt linetype table");
    }
    if (!EndRead3dmChunk())
      rc = -1;
  }

  return rc;
}

bool ON_BinaryArchive::EndRead3dmLinetypeTable()
{
  return EndRead3dmTable( TCODE_LINETYPE_TABLE);
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

bool ON_BinaryArchive::BeginWrite3dmInstanceDefinitionTable()
{
  return BeginWrite3dmTable( TCODE_INSTANCE_DEFINITION_TABLE );
}

bool ON_BinaryArchive::Write3dmInstanceDefinitionComponent(
  const class ON_ModelComponentReference& model_component_reference
  )
{
  return Write3dmInstanceDefinitionComponent(model_component_reference.ModelComponent());
}

bool ON_BinaryArchive::Write3dmInstanceDefinitionComponent(
  const class ON_ModelComponent* model_component
  )
{
  bool rc = false;
  for (;;)
  {
    const ON_InstanceDefinition* instance_definition = ON_InstanceDefinition::Cast(model_component);
    if (nullptr == instance_definition)
    {
      ON_ERROR("model_component parameter is not an instance definition component.");
      break;
    }
    rc = Write3dmInstanceDefinition(*instance_definition);
    break;
  }
  return rc;
}

bool ON_BinaryArchive::Write3dmInstanceDefinition( const ON_InstanceDefinition&  idef )
{
  if (false == ArchiveContains3dmTable(ON_3dmArchiveTableType::instance_definition_table))
    return true;

  if ( false == Internal_Begin3dmTableRecord(ON_3dmArchiveTableType::instance_definition_table) )
   return false;

  Internal_Increment3dmTableItemCount();

  bool rc = false;

  const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
  if ( c && c->m_typecode == TCODE_INSTANCE_DEFINITION_TABLE )
  {
    rc = BeginWrite3dmChunk( TCODE_INSTANCE_DEFINITION_RECORD, 0 );
    if ( rc )
    {
      Internal_Write3dmUpdateManifest(idef);
      rc = WriteObject( idef );
      if ( !EndWrite3dmChunk() )
        rc = false;
    }
  }
  else {
    ON_ERROR("ON_BinaryArchive::Write3dmInstanceDefinition() must be called in BeginWrite3dmInstanceDefinitionTable() block");
    rc = false;
  }

  return rc;
}

bool ON_BinaryArchive::EndWrite3dmInstanceDefinitionTable()
{
  return EndWrite3dmTable( TCODE_INSTANCE_DEFINITION_TABLE );
}

bool ON_BinaryArchive::BeginRead3dmInstanceDefinitionTable()
{
  return BeginRead3dmTable( TCODE_INSTANCE_DEFINITION_TABLE );
}

int ON_BinaryArchive::Read3dmInstanceDefinition( ON_InstanceDefinition** ppInstanceDefinition )
{
  if ( false == Read3dmTableRecord(ON_3dmArchiveTableType::instance_definition_table, (void**)ppInstanceDefinition))
    return 0;

  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  ON_InstanceDefinition* idef = nullptr;
  if ( BeginRead3dmBigChunk( &tcode, &big_value ) ) 
  {
    if ( tcode == TCODE_INSTANCE_DEFINITION_RECORD )
    {
      Internal_Increment3dmTableItemCount();
      ON_Object* p = 0;
      if ( ReadObject( &p ) ) {
        idef = ON_InstanceDefinition::Cast(p);
        if ( !idef )
          delete p;
      }
      if (!idef) {
        ON_ERROR("ON_BinaryArchive::Read3dmInstanceDefinition() - corrupt instance definition table");
      }
    }
    else if ( tcode != TCODE_ENDOFTABLE ) {
      ON_ERROR("ON_BinaryArchive::Read3dmInstanceDefinition() - corrupt instance definition table");
    }
    EndRead3dmChunk();
  }
  if (idef)
  {
    Internal_Read3dmUpdateManifest(*idef);
  }
  *ppInstanceDefinition = idef;
  return (idef) ? 1 : 0;
}

bool ON_BinaryArchive::EndRead3dmInstanceDefinitionTable()
{
  return EndRead3dmTable( TCODE_INSTANCE_DEFINITION_TABLE );
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

bool ON_BinaryArchive::BeginWrite3dmTextureMappingTable()
{
  return BeginWrite3dmTable( TCODE_TEXTURE_MAPPING_TABLE );
}

bool ON_BinaryArchive::Write3dmTextureMappingComponent(
  const ON_ModelComponentReference& model_component_reference
  )
{
  return Write3dmTextureMappingComponent(model_component_reference.ModelComponent());
}


bool ON_BinaryArchive::Write3dmTextureMappingComponent( 
  const ON_ModelComponent* model_component 
  )
{
  bool rc = false;
  for (;;)
  {
    const ON_TextureMapping* texture_mapping = ON_TextureMapping::Cast(model_component);
    if (nullptr == texture_mapping)
    {
      ON_ERROR("model_component parameter is not a texture mapping component.");
      break;
    }
    rc = Write3dmTextureMapping(*texture_mapping);
    break;
  }
  return rc;
}

bool ON_BinaryArchive::Write3dmTextureMapping( const ON_TextureMapping& texture_mapping )
{
  if (false == ArchiveContains3dmTable(ON_3dmArchiveTableType::texture_mapping_table))
    return true;

  if ( false == Internal_Begin3dmTableRecord(ON_3dmArchiveTableType::texture_mapping_table) )
    return false;

  Internal_Increment3dmTableItemCount();

  bool rc = false;

  if ( m_3dm_active_table != ON_3dmArchiveTableType::texture_mapping_table ) 
  {
    ON_ERROR("ON_BinaryArchive::Write3dmTextureMapping() - m_active_table != texture_mapping_table");
  }

  const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
  if ( !c || c->m_typecode != TCODE_TEXTURE_MAPPING_TABLE )
  {
    ON_ERROR("ON_BinaryArchive::Write3dmTextureMapping() - active chunk typecode != TCODE_TEXTURE_MAPPING_TABLE");
  }
  else 
  {
    rc = BeginWrite3dmChunk( TCODE_TEXTURE_MAPPING_RECORD, 0 );
    if (rc)
    {
      Internal_Write3dmUpdateManifest(texture_mapping);
      rc = WriteObject( texture_mapping );
      if ( !EndWrite3dmChunk() )
        rc = false;
    }
  }
  return rc;
}

bool ON_BinaryArchive::EndWrite3dmTextureMappingTable()
{
  return EndWrite3dmTable( TCODE_TEXTURE_MAPPING_TABLE );
}

bool ON_BinaryArchive::BeginRead3dmTextureMappingTable()
{
  return BeginRead3dmTable( TCODE_TEXTURE_MAPPING_TABLE );
}

int ON_BinaryArchive::Read3dmTextureMapping( ON_TextureMapping** ppTextureMapping )
{
  if ( false == Read3dmTableRecord(ON_3dmArchiveTableType::texture_mapping_table, (void**)ppTextureMapping))
    return 0;

  ON_TextureMapping* texture_mapping = nullptr;
  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  int rc = -1;
  if ( BeginRead3dmBigChunk( &tcode, &big_value ) )
  {
    if ( tcode == TCODE_TEXTURE_MAPPING_RECORD ) 
    {
      Internal_Increment3dmTableItemCount();
      ON_Object* p = 0;
      if ( ReadObject( &p ) ) 
      {
        texture_mapping = ON_TextureMapping::Cast(p);
        if ( !texture_mapping )
          delete p;
        else 
        {
          if ( ppTextureMapping )
            *ppTextureMapping = texture_mapping;
          rc = 1;
          Internal_Read3dmUpdateManifest(*texture_mapping);
        }
      }
      if (!texture_mapping)
      {
        Internal_ReportCriticalError();
        ON_ERROR("ON_BinaryArchive::Read3dmTextureMapping() - corrupt texture_mapping table");
      }
    }
    else if ( tcode == TCODE_ENDOFTABLE ) 
    {
      // end of texture_mapping table
      rc = 0;
    }
    else 
    {
      Internal_ReportCriticalError();
      ON_ERROR("ON_BinaryArchive::Read3dmTextureMapping() - corrupt texture_mapping table");
    }
    if ( !EndRead3dmChunk() )
      rc = -1;
  }

  return rc;
}

bool ON_BinaryArchive::EndRead3dmTextureMappingTable()
{
  return EndRead3dmTable( TCODE_TEXTURE_MAPPING_TABLE );
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

bool ON_BinaryArchive::BeginWrite3dmHistoryRecordTable()
{
  return BeginWrite3dmTable( TCODE_HISTORYRECORD_TABLE );
}

bool ON_BinaryArchive::Write3dmHistoryRecordComponent(
  const class ON_ModelComponentReference& model_component_reference
  )
{
  return Write3dmHistoryRecordComponent(model_component_reference.ModelComponent());
}

bool ON_BinaryArchive::Write3dmHistoryRecordComponent(
  const class ON_ModelComponent* model_component
  )
{
  bool rc = false;
  for (;;)
  {
    const ON_HistoryRecord* history_record = ON_HistoryRecord::Cast(model_component);
    if (nullptr == history_record)
    {
      ON_ERROR("model_component parameter is not a history record component.");
      break;
    }
    rc = Write3dmHistoryRecord(*history_record);
    break;
  }
  return rc;
}

bool ON_BinaryArchive::Write3dmHistoryRecord( const ON_HistoryRecord& history_record )
{
  if (false == ArchiveContains3dmTable(ON_3dmArchiveTableType::historyrecord_table))
    return true;

  if ( false == Internal_Begin3dmTableRecord(ON_3dmArchiveTableType::historyrecord_table) )
   return false;

  Internal_Increment3dmTableItemCount();

  bool rc = false;

  const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
  if ( !c || c->m_typecode != TCODE_HISTORYRECORD_TABLE )
  {
    ON_ERROR("ON_BinaryArchive::Write3dmHistoryRecord() - active chunk typecode != TCODE_HISTORYRECORD_TABLE");
  }
  else 
  {
    rc = BeginWrite3dmChunk( TCODE_HISTORYRECORD_RECORD, 0 );
    if (rc)
    {
      Internal_Write3dmUpdateManifest(history_record);
      rc = WriteObject( history_record );
      if ( !EndWrite3dmChunk() )
        rc = false;
    }
  }
  return rc;
}

bool ON_BinaryArchive::EndWrite3dmHistoryRecordTable()
{
  return EndWrite3dmTable( TCODE_HISTORYRECORD_TABLE );
}

bool ON_BinaryArchive::BeginRead3dmHistoryRecordTable()
{
  return BeginRead3dmTable( TCODE_HISTORYRECORD_TABLE );
}

int ON_BinaryArchive::Read3dmHistoryRecord( ON_HistoryRecord*& history_record )
{
  history_record = nullptr;
  if ( false == Read3dmTableRecord(ON_3dmArchiveTableType::historyrecord_table, (void**)&history_record))
    return 0;

  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  int rc = -1;
  if ( BeginRead3dmBigChunk( &tcode, &big_value ) )
  {
    if ( tcode == TCODE_HISTORYRECORD_RECORD ) 
    {
      Internal_Increment3dmTableItemCount();
      ON_Object* p = 0;
      if ( ReadObject( &p ) ) 
      {
        history_record = ON_HistoryRecord::Cast(p);
        if ( nullptr == history_record )
        {
          delete p;
        }
        else 
        {
          rc = 1;
          Internal_Read3dmUpdateManifest(*history_record);
        }
      }
      if (nullptr == history_record)
      {
        ON_ERROR("ON_BinaryArchive::Read3dmHistoryRecord() - corrupt history_record table");
      }
    }
    else if ( tcode == TCODE_ENDOFTABLE ) 
    {
      // end of history_record table
      rc = 0;
    }
    else 
    {
      ON_ERROR("ON_BinaryArchive::Read3dmHistoryRecord() - corrupt history_record table");
    }
    if ( !EndRead3dmChunk() )
      rc = -1;
  }

  return rc;
}

bool ON_BinaryArchive::EndRead3dmHistoryRecordTable()
{
  return EndRead3dmTable( TCODE_HISTORYRECORD_TABLE );
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

bool ON_BinaryArchive::BeginWrite3dmMaterialTable()
{
  return BeginWrite3dmTable( TCODE_MATERIAL_TABLE );
}

bool ON_BinaryArchive::Write3dmMaterialComponent(
  const ON_ModelComponentReference& model_component_reference
  )
{
  return Write3dmMaterialComponent(model_component_reference.ModelComponent());
}


bool ON_BinaryArchive::Write3dmMaterialComponent( 
  const ON_ModelComponent* model_component 
  )
{
  bool rc = false;
  for (;;)
  {
    const ON_Material* render_material = ON_Material::Cast(model_component);
    if (nullptr == render_material)
    {
      ON_ERROR("model_component parameter is not a render material component.");
      break;
    }
    rc = Write3dmMaterial(*render_material);
    break;
  }
  return rc;
}

bool ON_BinaryArchive::Write3dmMaterial( const ON_Material& material )
{
  if (false == ArchiveContains3dmTable(ON_3dmArchiveTableType::material_table))
    return true;

  if ( false == Internal_Begin3dmTableRecord(ON_3dmArchiveTableType::material_table) )
   return false;

  Internal_Increment3dmTableItemCount();

  bool rc = false;

  const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
  if ( !c || c->m_typecode != TCODE_MATERIAL_TABLE )
  {
    Internal_ReportCriticalError();
    ON_ERROR("ON_BinaryArchive::Write3dmMaterial() - active chunk typecode != TCODE_MATERIAL_TABLE");
  }
  else 
  {
    rc = BeginWrite3dmChunk( TCODE_MATERIAL_RECORD, 0 );
    if (rc)
    {
      Internal_Write3dmUpdateManifest(material);
      rc = WriteObject( material );
      if ( !EndWrite3dmChunk() )
        rc = false;
    }
  }
  return rc;
}

bool ON_BinaryArchive::EndWrite3dmMaterialTable()
{
  return EndWrite3dmTable( TCODE_MATERIAL_TABLE );
}

bool ON_BinaryArchive::BeginRead3dmMaterialTable()
{
  m_3dm_v1_material_index = 0;
  return BeginRead3dmTable( TCODE_MATERIAL_TABLE );
}

bool ON_BinaryArchive::Read3dmV1String( ON_String& s )
{
  int string_length = 0;
  s.Empty();
  bool rc = ReadInt( &string_length );
  if (rc) {
    s.ReserveArray(string_length+1);
    rc = ReadChar( string_length, s.Array() );
    if (rc)
      s.SetLength(string_length);
  }
  return rc;
}


class ON__3dmV1_XDATA
{
  // helper class to get V1 "xdata" out of attributes block.
public:
  enum
  {
    unknown_xdata = 0,
    hidden_object_layer_name, // m_string = actual layer name
    locked_object_layer_name, // m_string = actual layer name
    arrow_direction,          // m_vector = arrow head location
    dot_text                  // m_string = dot text
  }
  m_type;
  ON_String m_string; 
  ON_3dVector m_vector;
};

bool ON_BinaryArchive::Read3dmV1AttributesOrMaterial( 
                         ON_3dmObjectAttributes* attributes,
                         ON_Material* material,
                         bool& bHaveMat,
                         unsigned int end_mark_tcode,
                         ON__3dmV1_XDATA* xdata
                         )
{
  // Check ReadV1Material() if you fix any bugs in the mateial related items

  if ( 0 != xdata )
  {
    xdata->m_type = ON__3dmV1_XDATA::unknown_xdata;
  }

  bool rc = false;
  unsigned int u;
  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  ON_Color c;
  bHaveMat = false;
  bool bEndRead3dmChunk_rc;

  const unsigned int saved_error_message_mask = m_error_message_mask;

  int xdata_layer_index = -1;

  if ( attributes )
  {
    attributes->Default();
  }

  if ( material ) 
  {
    *material = ON_Material::Unset;
    material->m_diffuse.SetRGB(255,255,255); // default is (128,128,128)
  }

  for (;;) 
  {
    m_error_message_mask = saved_error_message_mask;

    if ( end_mark_tcode != TCODE_ENDOFTABLE ) {
      tcode = 0;
      big_value = 0;
      if ( !PeekAt3dmBigChunkType(&tcode,&big_value) ) {
        break; // should not happen
      }
      if ( tcode == end_mark_tcode ) {
        rc = true;
        break; // done reading attributes
      }
    }
    tcode = 0;
    big_value = 0;
    if ( !BeginRead3dmBigChunk(&tcode,&big_value) )
      break;
    if ( tcode == end_mark_tcode ) {
      rc = EndRead3dmChunk();
      break;
    }
    
    switch( tcode ) 
    {      
    case (TCODE_OPENNURBS_OBJECT | TCODE_CRC | 0x7FFD):
      // 1.1 object 16 byte UUID + 2 byte crc
      if ( attributes )
        ReadUuid( attributes->m_uuid );
      break;
      
    case TCODE_LAYERREF:
      if (    attributes 
           && (-1 == xdata_layer_index || attributes->m_layer_index != xdata_layer_index) 
           && (big_value >= 0 && big_value < 0x7FFFFFFF)
         )
      {
        const int file_layer_index = (int)big_value;
        const ON_ManifestMapItem& map_item = m_manifest_map.MapItemFromSourceIndex(ON_ModelComponent::Type::Layer, file_layer_index);
        attributes->m_layer_index
          = map_item.SourceAndDestinationAreSet()
          ? map_item.DestinationIndex()
          : file_layer_index;
      }
      break;
      
    case TCODE_RGB:
      if ( big_value != 0xFFFFFF ) 
      {
        if ( material ) 
        {
          ON__UINT64 rgb64 = (ON__UINT64)big_value;
          ON__UINT32 rgb32 = (ON__UINT32)rgb64;
          u = rgb32;
          c.SetRGB( u%256,(u>>8)%256,(u>>16)%256 );
          material->SetDiffuse(c);
          material->SetShine((u >> 24)/100.0*ON_Material::MaxShine);
        }
        bHaveMat = true;
      }
      break;		
      
    case TCODE_RGBDISPLAY:
      if ( attributes ) 
      {
          ON__UINT64 rgb64 = (ON__UINT64)big_value;
          ON__UINT32 rgb32 = (ON__UINT32)rgb64;
          u = rgb32;
        attributes->m_color.SetRGB( u%256,(u>>8)%256,(u>>16)%256 );
      }
      break;
      
    case TCODE_TRANSPARENCY:
      if ( big_value > 0 && big_value <= 255 ) 
      {
        if ( material )
          material->SetTransparency(big_value/255.0);
        bHaveMat = true;
      }
      break;				
      
    case TCODE_NAME:
      if ( attributes ) {
        ON_String s;
        Read3dmV1String(s);
        if( s.Length() > 0 )
          attributes->m_name = s;
      }
      break;
   
    case TCODE_TEXTUREMAP:
      {
        ON_String s;
        Read3dmV1String(s);
        if ( s.Length() > 0 ) 
        {
          if ( material )
          {
            ON_Texture& tx = material->m_textures.AppendNew();
            tx.m_image_file_reference.SetFullPath(s,false);
            tx.m_type = ON_Texture::TYPE::bitmap_texture;
          }
          bHaveMat = true;
        }
      }
      break;

    case TCODE_BUMPMAP:
      if ( material ) {
        ON_String s;
        Read3dmV1String(s);
        if ( s.Length() ) 
        {
          if ( material )
          {
            ON_Texture& tx = material->m_textures.AppendNew();
            tx.m_image_file_reference.SetFullPath(s,false);
            tx.m_type = ON_Texture::TYPE::bump_texture;
          }
          bHaveMat = true;
        }
      }
      break;
      
    case TCODE_XDATA:
      // v1 "xdata"
      if ( attributes ) 
      {
        ON_String layer_name;
        ON_String xid;
        int sizeof_xid = 0;
        int sizeof_data = 0;
        ReadInt(&sizeof_xid);
        ReadInt(&sizeof_data);
        xid.SetLength(sizeof_xid);
        ReadByte(sizeof_xid,xid.Array());
        if ( !on_stricmp("RhHidePrevLayer",static_cast< const char* >(xid)) )
        {
          if ( sizeof_data > 0 )
          {
            // v1 object is hidden - real layer name is in xdata
            char* buffer = (char*)onmalloc((sizeof_data+1)*sizeof(buffer[0]));
            buffer[0] = 0;
            buffer[sizeof_data] = 0;
            if ( ReadByte(sizeof_data,buffer) )
            {
              if ( -1 == xdata_layer_index )
              {
                xdata_layer_index = Read3dmV1LayerIndex(buffer);
                if ( xdata_layer_index >= 0 )
                {
                  attributes->m_layer_index = xdata_layer_index;
                  attributes->SetVisible(false);
                }
              }
              else
              {
                xdata_layer_index = -2;
              }
              //if ( 0 != xdata )
              //{
              //  xdata->m_type = ON__3dmV1_XDATA::hidden_object_layer_name;
              //  xdata->m_string = buffer;               
              //}
            }
            onfree(buffer);
          }
        }
        else if ( !on_stricmp("RhFreezePrevLayer",static_cast< const char* >(xid)) )
        {
          // v1 object is locked - real layer name is in xdata
          if ( sizeof_data > 0 )
          {
            char* buffer = (char*)onmalloc((sizeof_data+1)*sizeof(buffer[0]));
            buffer[0] = 0;
            buffer[sizeof_data] = 0;
            if ( ReadByte(sizeof_data,buffer)  )
            {
              if ( -1 == xdata_layer_index )
              {
                xdata_layer_index = Read3dmV1LayerIndex(buffer);
                if ( xdata_layer_index >= 0 )
                {
                  attributes->m_layer_index = xdata_layer_index;
                  attributes->SetMode(ON::locked_object);
                }
              }
              else
              {
                xdata_layer_index = -2;
              }
              //if ( 0 != xdata )
              //{
              //  xdata->m_type = ON__3dmV1_XDATA::locked_object_layer_name;
              //  xdata->m_string = buffer;            
              //}
            }
            onfree(buffer);
          }
        }
        else if ( !on_stricmp("RhAnnotateArrow",static_cast< const char* >(xid)) && 24 == sizeof_data )
        {
          // v1 annotation arrow objects were saved
          // as TCODE_RH_POINT objects with the
          // arrow tail location = point location and the
          // arrow head location saved in 24 bytes of "xdata".
          ON_3dVector arrow_direction;
          if ( ReadVector( arrow_direction ) && 0 != xdata )
          {
            xdata->m_type = ON__3dmV1_XDATA::arrow_direction;
            xdata->m_vector = arrow_direction;
          }
        }
        else if ( !on_stricmp("RhAnnotateDot",static_cast< const char* >(xid)) )
        {
          if ( sizeof_data > 0 )
          {
            // v1 annotation dot objects were saved
            // as TCODE_RH_POINT objects with the
            // dot text saved in "xdata".
            char* buffer = (char*)onmalloc((sizeof_data+1)*sizeof(buffer[0]));
            buffer[0] = 0;
            buffer[sizeof_data] = 0;
            if ( ReadByte(sizeof_data,buffer) && 0 != xdata )
            {
              xdata->m_type = ON__3dmV1_XDATA::dot_text;
              xdata->m_string = buffer;            
            }
            onfree(buffer);
          }
        }
        else 
        {
          m_error_message_mask |= 0x0002; // disable v1 EndRead3dmChunk() partially read chunk warning
        }
        // call to EndRead3dmChunk() will skip unread junk
      }
      break;
      
    case TCODE_DISP_CPLINES:
      if ( big_value > 0 && big_value <= 0x7FFFFFFF && attributes )
        attributes->m_wire_density = (int)big_value;
      break;

    case TCODE_RENDER_MATERIAL_ID:
      {
        int flag;
        ON_String s;
        ReadInt(&flag);
        if ( flag == 1 ) {
          Read3dmV1String(s);
          if ( s.Length() > 0 ) 
          {
            if (material)
            {
              ON_wString wide_name(s);
              material->SetName(wide_name);
            }
            bHaveMat = true;
          }
        }
      }
      break;
      
    default:
      // obsolete attributes from v1
      m_error_message_mask |= 0x02; // disable v1 EndRead3dmChunk() partially read chunk warning
      break;
    }

    bEndRead3dmChunk_rc = EndRead3dmChunk();
    if ( !bEndRead3dmChunk_rc )
      break;
  }

  m_error_message_mask = saved_error_message_mask;

  if ( bHaveMat ) {
    if ( attributes )
      attributes->m_material_index = m_3dm_v1_material_index;
    if ( material )
      material->SetIndex(m_3dm_v1_material_index);
    m_3dm_v1_material_index++;
  }

  return rc;
}



int ON_BinaryArchive::Read3dmV1Material( ON_Material** ppMaterial )
{
  int rc = 0;
  // returns -1: failure
  //          0: end of material table
  //          1: success

  ON_Material material;
  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  bool bHaveMat;
  bool bEndReadChunk_rc;
  // reads NURBS, point, and mesh objects

  while( 0 == rc )
  {
    bHaveMat = false;
    rc = 0;
    tcode = 0;
    big_value = 0;
    if ( !BeginRead3dmBigChunk(&tcode,&big_value) ) 
    {
      // assume we are at the end of the file
      break;
    }

    switch(tcode)
    {
    case TCODE_RH_POINT:
      // v1 3d point
      {
        ON_3DM_BIG_CHUNK* point_chunk = m_chunk.Last();
        ON__UINT64 pos0 = 0;
        if (    0 != point_chunk 
             && TCODE_RH_POINT == point_chunk->m_typecode 
             && 0 == point_chunk->m_big_value )
        {
          // Some V1 files have TCODE_RH_POINT chunks with length=0.
          // (It appears that points with arrow xdata have this problem.)
          // For these chunks we need to set the chunk length so EndRead3dmChunk()
          // will keep going.
          pos0 = CurrentPosition();
        }
        else
          point_chunk = 0;

        ON_3dPoint pt; // need to read point to get to material defn
        bool bOK = ReadPoint( pt );
        
        if ( bOK )
          bOK = Read3dmV1AttributesOrMaterial( nullptr, &material, bHaveMat, TCODE_ENDOFTABLE );
        
        if ( !bOK )
          rc = -1;
        // else if appropriate, rc will get set to +1 below.

        if ( bOK
             && 0 != point_chunk 
             && point_chunk == m_chunk.Last()
             && TCODE_RH_POINT == point_chunk->m_typecode 
             && 0 == point_chunk->m_big_value )
        {
          // set the chunk length so that reading can continue.
          ON__UINT64 pos1 = CurrentPosition();
          ON__UINT64 chunk_length = (pos1 > pos0) ? (pos1 - pos0) : 0;
          if ( chunk_length >= 32 && chunk_length < 0x0FFFFFFF )
            point_chunk->m_big_value = (ON__INT64)chunk_length;
        }
      }
      break;

    case TCODE_MESH_OBJECT:
      // v1 mesh
      {
        ON__UINT32 tc = 0;
        ON__INT64 i64 = 0;
        if ( !PeekAt3dmBigChunkType( &tc, &i64 ) )
          break;
        if ( tc != TCODE_COMPRESSED_MESH_GEOMETRY )
          break;
        // skip over the TCODE_COMPRESSED_MESH_GEOMETRY chunk
        if ( !BeginRead3dmBigChunk(&tc,&i64) )
          break;
        if ( !EndRead3dmChunk() )
          break;
        // attributes and material informtion follow the TCODE_COMPRESSED_MESH_GEOMETRY chunk
        if ( !Read3dmV1AttributesOrMaterial( nullptr, &material, bHaveMat, TCODE_ENDOFTABLE ) )
          rc = -1;
        // if appropriate, rc will get set to +1 below
      }
      break;

    case TCODE_LEGACY_SHL:
      // v1 polysurface
      if ( !Read3dmV1AttributesOrMaterial( nullptr, &material, bHaveMat, TCODE_LEGACY_SHLSTUFF ) )
        rc = -1;
        // if appropriate, rc will get set to +1 below
      break;
    case TCODE_LEGACY_FAC:
      // v1 trimmed surface
      if ( !Read3dmV1AttributesOrMaterial( nullptr, &material, bHaveMat, TCODE_LEGACY_FACSTUFF ) )
        rc = -1;
        // if appropriate, rc will get set to +1 below
      break;
    case TCODE_LEGACY_CRV:
      // v1 curve
      if ( !Read3dmV1AttributesOrMaterial( nullptr, &material, bHaveMat, TCODE_LEGACY_CRVSTUFF ) )
        rc = -1;
        // if appropriate, rc will get set to +1 below
      break;

    case TCODE_RHINOIO_OBJECT_NURBS_CURVE:
    case TCODE_RHINOIO_OBJECT_NURBS_SURFACE:
    case TCODE_RHINOIO_OBJECT_BREP:
      // old Rhino I/O toolkit nurbs curve, surface, and breps
      {
        ON__UINT32 tc = 0;
        ON__INT64 i64 = 0;
        if ( !PeekAt3dmBigChunkType( &tc, &i64 ) )
          break;
        if ( tc != TCODE_RHINOIO_OBJECT_DATA )
          break;
        // skip over the TCODE_RHINOIO_OBJECT_DATA chunk
        if ( !BeginRead3dmBigChunk(&tc,&i64) )
          break;
        if ( !EndRead3dmChunk() )
          break;
        if ( !Read3dmV1AttributesOrMaterial( nullptr, &material, bHaveMat, TCODE_RHINOIO_OBJECT_END ) )
          rc = -1;
        // if appropriate, rc will get set to +1 below
      }
      break;
    }

    const unsigned int saved_error_message_mask = m_error_message_mask;
    m_error_message_mask |= 0x02; // disable v1 EndRead3dmChunk() partially read chunk warning
    bEndReadChunk_rc = EndRead3dmChunk();
    m_error_message_mask = saved_error_message_mask; // enable v1 EndRead3dmChunk() partially read chunk warning
    if (!bEndReadChunk_rc ) 
    {
      rc = -1;
      break;
    }
    if ( bHaveMat && ppMaterial) 
    {
      Internal_Increment3dmTableItemCount();
      // found a valid non-default material
      *ppMaterial = new ON_Material(material);
      (*ppMaterial)->SetId(); // V1 materials did not have ids
      rc = 1;
      break;
    }
  }

  return rc;
}


int ON_BinaryArchive::Read3dmMaterial( ON_Material** ppMaterial )
{
  if ( false == Read3dmTableRecord(ON_3dmArchiveTableType::material_table, (void**)ppMaterial))
    return 0;

  int rc;
  ON_Material* material = nullptr;
  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  if ( m_3dm_version == 1 ) 
  {
    ON_Material* V1_material = nullptr;
    rc = ON_BinaryArchive::Read3dmV1Material( &V1_material );
    if (nullptr != V1_material)
    {
      if ( V1_material->IdIsNil() )
        V1_material->SetId();
      Internal_Read3dmUpdateManifest(*V1_material);
      if (ppMaterial)
        *ppMaterial = V1_material;
      else
        delete V1_material;
    }
  }
  else 
  {
    // version 2+
    rc = -1;
    if ( BeginRead3dmBigChunk( &tcode, &big_value ) )
    {
      if ( tcode == TCODE_MATERIAL_RECORD ) 
      {
        Internal_Increment3dmTableItemCount();
        ON_Object* p = 0;
        if ( ReadObject( &p ) ) 
        {
          material = ON_Material::Cast(p);
          if ( !material )
            delete p;
          else 
          {
            if ( material->IdIsNil() )
              material->SetId();
            Internal_Read3dmUpdateManifest(*material);
            if ( ppMaterial )
              *ppMaterial = material;
            rc = 1;
          }
        }
        if (!material)
        {
          ON_ERROR("ON_BinaryArchive::Read3dmMaterial() - corrupt material table");
        }
      }
      else if ( tcode == TCODE_ENDOFTABLE ) 
      {
        // end of material table
        rc = 0;
      }
      else 
      {
        ON_ERROR("ON_BinaryArchive::Read3dmMaterial() - corrupt material table");
      }
      if ( !EndRead3dmChunk() )
        rc = -1;
    }
  }
  return rc;
}

bool ON_BinaryArchive::EndRead3dmMaterialTable()
{
  return EndRead3dmTable( TCODE_MATERIAL_TABLE );
}


bool ON_BinaryArchive::BeginWrite3dmLightTable()
{
  return BeginWrite3dmTable( TCODE_LIGHT_TABLE );
}

bool ON_BinaryArchive::Write3dmModelLightComponent(
  const ON_ModelComponentReference& model_component_reference
  )
{
  return Write3dmModelLightComponent(ON_ModelGeometryComponent::Cast(model_component_reference.ModelComponent()));
}

bool ON_BinaryArchive::Write3dmModelLightComponent(
  const ON_ModelGeometryComponent* model_light
  )
{
  bool rc = false;
  for (;;)
  {
    if (nullptr == model_light)
    {
      ON_ERROR("model_light parameter is nullptr.");
      break;
    }

    const ON_Light* light = ON_Light::Cast(model_light->Geometry(nullptr));
    if (nullptr == light)
    {
      ON_ERROR("model_light parameter is empty.");
      break;
    }

    rc = Write3dmLight(*light, model_light->Attributes(nullptr) );
    break;
  }
  return rc;
}


bool ON_BinaryArchive::Write3dmLight( const ON_Light& light,  const ON_3dmObjectAttributes* attributes )
{
  if (false == ArchiveContains3dmTable(ON_3dmArchiveTableType::light_table))
    return true;

  if ( false == Internal_Begin3dmTableRecord(ON_3dmArchiveTableType::light_table) )
   return false;

  Internal_Increment3dmTableItemCount();

  bool rc = false;

  const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
  if ( c && c->m_typecode == TCODE_LIGHT_TABLE ) {
    rc = BeginWrite3dmChunk( TCODE_LIGHT_RECORD, 0 );
    if (rc) 
    {
      // Because render lights have an index (unused), the manifest item has to be set before writing the light.
      Internal_Write3dmLightOrGeometryUpdateManifest(ON_ModelComponent::Type::RenderLight, light.m_light_id, light.m_light_index, light.m_light_name);
      rc = WriteObject( light );
      if (rc)

      // optional TCODE_LIGHT_RECORD_ATTRIBUTES chunk
      if ( rc && attributes ) 
      {
        rc = BeginWrite3dmChunk( TCODE_LIGHT_RECORD_ATTRIBUTES, 0 );
        if (rc) 
        {
          rc = attributes->Write( *this )?true:false;
          if (!EndWrite3dmChunk())
            rc = false;
          if( rc 
              && Archive3dmVersion() >= 4 
              && ObjectHasUserDataToWrite(attributes)
            )
          {
            // 14 May 2008 Dale Lear
            //    Added support for saving light attribute userdata
            rc = BeginWrite3dmChunk( TCODE_LIGHT_RECORD_ATTRIBUTES_USERDATA, 0 );
            if (rc)
            {
              // write user data
              rc = WriteObjectUserData(*attributes);
              if (rc)
              {
                // Because I'm not using Write3dmObject() to write
                // the attributes, the user data must be immediately 
                // followed by a short TCODE_OPENNURBS_CLASS_END chunk 
                // in order for ReadObjectUserData() to work correctly.
                //
                // The reason that this is hacked in is that V3 files did
                // not support attribute user data and doing it this way
                // means that V3 can still read V4 files.
                rc = BeginWrite3dmChunk(TCODE_OPENNURBS_CLASS_END,0);
                if (rc)
                {
                  if (!EndWrite3dmChunk())
                    rc = false;
                }
              }
              if (!EndWrite3dmChunk())
                rc = false;
            }
          }
        }
      }

      // TCODE_LIGHT_RECORD_END chunk marks end of light record
      if ( BeginWrite3dmChunk( TCODE_LIGHT_RECORD_END, 0 ) ) {
        if (!EndWrite3dmChunk())
          rc = false;
      }
      else {
        rc = false;
      }

      if ( !EndWrite3dmChunk() ) // end of TCODE_LIGHT_RECORD
        rc = false;
    }
  }
  else {
    ON_ERROR("ON_BinaryArchive::Write3dmMaterial() - active chunk typecode != TCODE_LIGHT_TABLE");
  }
  return rc;
}

bool ON_BinaryArchive::EndWrite3dmLightTable()
{
  return EndWrite3dmTable( TCODE_LIGHT_TABLE );
}

bool ON_BinaryArchive::BeginRead3dmLightTable()
{
  return BeginRead3dmTable( TCODE_LIGHT_TABLE );
}

int ON_BinaryArchive::Read3dmV1Light(  // returns 0 at end of light table
                    //         1 light successfully read
                    //        -1 if file is corrupt
          ON_Light** ppLight, // light returned here
          ON_3dmObjectAttributes* pAttributes// optional - if NOT nullptr, object attributes are
                                  //            returned here
          )
{
  bool bHaveMat;
  ON_Material material;
  // TODO - read v1 lights
  if ( m_chunk.Count() != 0 ) {
    ON_ERROR("ON_BinaryArchive::Read3dmV1Light() m_chunk.Count() != 0");
    return false;
  }
  bool rc = false;
  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;

  // find TCODE_RH_SPOTLIGHT chunk
  for(;;)
  {
    if ( !BeginRead3dmBigChunk(&tcode,&big_value) )
      break; // assume we are at the end of the file
    if ( tcode == TCODE_RH_SPOTLIGHT ) {
      rc = 1;
      break;
    }
    if ( !EndRead3dmChunk() )
      break;
  }
  if (rc) {
    ON_3dPoint origin;
    ON_3dVector xaxis, yaxis;
    double radius;
    double height;
    double hotspot;

    for(;;)
    {
      rc = ReadPoint( origin );
      if (!rc) break;
      rc = ReadVector( xaxis );
      if (!rc) break;
      rc = ReadVector( yaxis );
      if (!rc) break;
      rc = ReadDouble( &radius );
      if (!rc) break;
      rc = ReadDouble( &height );
      if (!rc) break;
      rc = ReadDouble( &hotspot );
      if (!rc) break;
      if (ppLight ) 
      {
        ON_3dVector Z = ON_CrossProduct( xaxis, yaxis );
        ON_3dPoint  location = height*Z + origin;
        ON_3dVector direction = -Z;

        if( height > 0.0)
          direction *= height;
        ON_Light* light = new ON_Light;
        light->SetStyle( ON::world_spot_light );
        light->SetLocation(location);
        light->SetDirection(direction);
        light->SetSpotExponent( 64.0);
        if( radius > 0.0 && height > 0.0 )
          light->SetSpotAngleRadians( atan( radius/height));
        *ppLight = light;
      }
      break;
    }

    if (rc && ppLight && *ppLight) {
      Internal_Increment3dmTableItemCount();
      bHaveMat = false;
      Read3dmV1AttributesOrMaterial(pAttributes,&material,bHaveMat,TCODE_ENDOFTABLE);
      if ( pAttributes )
        pAttributes->m_material_index = -1;
      if (bHaveMat)
        (*ppLight)->SetDiffuse(material.Diffuse());
    }

    if ( !EndRead3dmChunk() ) // end of TCODE_RH_SPOTLIGHT chunk
      rc = false;
  }

  return rc;
}

int ON_BinaryArchive::Read3dmModelLight(
  class ON_ModelGeometryComponent** model_light
  )
{
  if ( nullptr != model_light )
    *model_light = nullptr;
  ON_Light* light = nullptr;
  ON_3dmObjectAttributes* attributes = new ON_3dmObjectAttributes();
  int rc = Read3dmLight(&light, attributes);
  if (1 == rc && nullptr != light)
  {
    attributes->m_uuid = light->m_light_id;
    attributes->m_name = light->m_light_name;
    ON_ModelGeometryComponent* p = ON_ModelGeometryComponent::CreateManaged(light,attributes,nullptr);
    if (nullptr != p)
    {
      p->SetIndex(light->m_light_index);
      p->SetId(light->m_light_id);
      p->SetName(light->m_light_name);
      *model_light = p;
    }
  }
  else
  {
    delete light;
    delete attributes;
  }
  return rc;
}

int ON_BinaryArchive::Read3dmLight( ON_Light** ppLight, ON_3dmObjectAttributes* attributes )
{
  if ( attributes )
    attributes->Default();
  if ( false == Read3dmTableRecord(ON_3dmArchiveTableType::light_table, (void**)ppLight))
    return 0;
  
  int rc = -1;
  
  if ( m_3dm_version == 1 ) 
  {
    rc = Read3dmV1Light( ppLight, attributes );
  }
  else 
  {
    ON_Light* light = nullptr;
    ON__UINT32 tcode = 0;
    ON__INT64 big_value = 0;
    if ( BeginRead3dmBigChunk( &tcode, &big_value ) ) 
    {
      if ( tcode == TCODE_LIGHT_RECORD )
      {
        Internal_Increment3dmTableItemCount();
        ON_Object* p = 0;
        if ( ReadObject( &p ) ) {
          light = ON_Light::Cast(p);
          if ( !light )
            delete p;
        }
        if (!light) {
          ON_ERROR("ON_BinaryArchive::Read3dmLight() - corrupt light table");
        }
        else {
          *ppLight = light;
          rc = 1;
        }
      }
      else if ( tcode != TCODE_ENDOFTABLE ) 
      {
        ON_ERROR("ON_BinaryArchive::Read3dmLight() - corrupt light table");
      }
      else
        rc = 0;

      while(rc==1) 
      {
        tcode = 0;
        big_value = 0;
        if (!BeginRead3dmBigChunk( &tcode, &big_value )) 
        {
          rc = -1;
          break;
        }
        if ( tcode == TCODE_LIGHT_RECORD_ATTRIBUTES && attributes ) 
        {
          if ( !attributes->Read( *this ) )
            rc = -1;
        }
        else if ( tcode == TCODE_LIGHT_RECORD_ATTRIBUTES_USERDATA )
        {
          if ( 0 != attributes )
          {
            // 14 May 2008
            //   Added support for reading user data on light attributes
            if ( !ReadObjectUserData(*attributes))
              rc = -1;
          }
        }
        if ( !EndRead3dmChunk() )
        {
          rc = -1;
          break;
        }
        if ( tcode == TCODE_LIGHT_RECORD_END )
          break;
      }

      EndRead3dmChunk();
    }
  }

  if ( nullptr != ppLight && nullptr != (*ppLight) )
  {
    // If file is an older version with no id, then create one.
    if (ON_nil_uuid == (*ppLight)->m_light_id)
    {
      if (nullptr != attributes)
      {
        if (ON_nil_uuid == attributes->m_uuid)
        {
          attributes->m_uuid = ON_CreateId();
        }
        (*ppLight)->m_light_id = attributes->m_uuid;
      }
      else
        (*ppLight)->m_light_id = ON_CreateId();
    }
    Internal_Read3dmLightOrGeometryUpdateManifest(
      ON_ModelComponent::Type::RenderLight,
      (*ppLight)->m_light_id,
      (*ppLight)->m_light_index,
      (*ppLight)->m_light_name
      );
  }

  return rc;
}

bool ON_BinaryArchive::EndRead3dmLightTable()
{
  return EndRead3dmTable( TCODE_LIGHT_TABLE );
}

bool ON_BinaryArchive::BeginWrite3dmObjectTable()
{
  return BeginWrite3dmTable( TCODE_OBJECT_TABLE );
}

bool ON_BinaryArchive::Write3dmModelGeometryComponent( 
  const class ON_ModelComponentReference& model_component_reference
  )
{
  return Write3dmModelGeometryComponent(ON_ModelGeometryComponent::Cast(model_component_reference.ModelComponent()));
}
bool ON_BinaryArchive::Write3dmModelGeometryComponent(
  const class ON_ModelGeometryComponent* model_geometry
  )
{
  bool rc = false;
  for (;;)
  {
    if (nullptr == model_geometry)
    {
      ON_ERROR("model_geometry parameter is nullptr.");
      break;
    }

    const ON_Geometry* geometry = model_geometry->Geometry(nullptr);
    if (nullptr == geometry)
    {
      ON_ERROR("model_light parameter is empty.");
      break;
    }

    rc = Write3dmObject(*geometry, model_geometry->Attributes(nullptr) );
    break;
  }
  return rc;
}

bool ON_BinaryArchive::Write3dmObject( 
          const ON_Object& object, 
          const ON_3dmObjectAttributes* attributes 
          )
{
  if ( false == Internal_Begin3dmTableRecord(ON_3dmArchiveTableType::object_table) )
    return false;

  Internal_Increment3dmTableItemCount();

  bool rc = false;

  if ( Archive3dmVersion() <= 2 && object.ObjectType() == ON::pointset_object )
  {
    // There were no point clouds in V1 and V2 files and we cannot handle
    // this problem inside of ON_PointCloud::Write() because we have to
    // write multiple point objects.  (c.f. ON_Brep::Write()).
    const ON_PointCloud* pc = ON_PointCloud::Cast(&object);
    if ( 0 != pc )
    {
      int i, count = pc->PointCount();
      rc = true;
      for ( i = 0; i < count && rc ; i++ )
      {
        ON_Point pt( pc->m_P[i] );
        rc = Write3dmObject( pt, attributes );
      }
      return rc;
    }
  }

  m_annotation_context.SetViewContext( (nullptr != attributes) ? attributes->m_space : ON_3dmAnnotationContext::Default.ViewContext() );

  const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
  if ( c && c->m_typecode == TCODE_OBJECT_TABLE ) 
  {
    Flush();
    rc = BeginWrite3dmChunk( TCODE_OBJECT_RECORD, 0 );
    if (rc) {
      // TCODE_OBJECT_RECORD_TYPE chunk integer value that can be used
      // for skipping unwanted types of objects
      rc = BeginWrite3dmChunk( TCODE_OBJECT_RECORD_TYPE, object.ObjectType() );
      if (rc) {
        if (!EndWrite3dmChunk())
          rc = false;
      }

      // WriteObject writes TCODE_OPENNURBS_CLASS chunk that contains object definition
      rc = WriteObject( object );

      // optional TCODE_OBJECT_RECORD_ATTRIBUTES chunk
      if ( rc && nullptr != attributes ) {
        rc = BeginWrite3dmChunk( TCODE_OBJECT_RECORD_ATTRIBUTES, 0 );
        if (rc) {
          rc = attributes->Write( *this )?true:false;
          if (rc && ON_nil_uuid != attributes->m_uuid)
            Internal_Write3dmLightOrGeometryUpdateManifest(ON_ModelComponent::Type::ModelGeometry, attributes->m_uuid, ON_UNSET_INT_INDEX, ON_wString::EmptyString);

          if (!EndWrite3dmChunk())
            rc = false;

          if( rc 
              && Archive3dmVersion() >= 4 
              && 0 != attributes->FirstUserData() 
              && ObjectHasUserDataToWrite(attributes)
              )
          {
            // 19 October 2004
            //   Added support for saving user data on object attributes
            rc = BeginWrite3dmChunk( TCODE_OBJECT_RECORD_ATTRIBUTES_USERDATA, 0 );
            if (rc)
            {
              // write user data
              rc = WriteObjectUserData(*attributes);
              if (rc)
              {
                // Because I'm not using Write3dmObject() to write
                // the attributes, the user data must be immediately 
                // followed by a short TCODE_OPENNURBS_CLASS_END chunk 
                // in order for ReadObjectUserData() to work correctly.
                //
                // The reason that this is hacked in is that V3 files did
                // not support attribute user data and doing it this way
                // means that V3 can still read V4 files.
                rc = BeginWrite3dmChunk(TCODE_OPENNURBS_CLASS_END,0);
                if (rc)
                {
                  if (!EndWrite3dmChunk())
                    rc = false;
                }
              }
              if (!EndWrite3dmChunk())
                rc = false;
            }
          }
        }
      }

      // TCODE_OBJECT_RECORD_END chunk marks end of object record
      if ( BeginWrite3dmChunk( TCODE_OBJECT_RECORD_END, 0 ) ) {
        if (!EndWrite3dmChunk())
          rc = false;
      }
      else {
        rc = false;
      }

      if (!EndWrite3dmChunk()) // end of TCODE_OBJECT_RECORD
      {
        rc = false;
      }
      if (!Flush())
        rc = false;
    }
    else {
      ON_ERROR("ON_BinaryArchive::Write3dmObject() - active chunk typecode != TCODE_OBJECT_TABLE");
    }
  }

  m_annotation_context.SetViewContext( ON_3dmAnnotationContext::Default.ViewContext() );

  return rc;
}

bool ON_BinaryArchive::EndWrite3dmObjectTable()
{
  return EndWrite3dmTable( TCODE_OBJECT_TABLE );
}

bool ON_BinaryArchive::BeginRead3dmObjectTable()
{
  m_3dm_v1_material_index = 0;
  return BeginRead3dmTable( TCODE_OBJECT_TABLE );
}

bool ON_BinaryArchive::ReadV1_TCODE_RH_POINT(
  ON_Object** ppObject,
  ON_3dmObjectAttributes* pAttributes
  )
{
  ON__UINT64 pos0 = 0;
  ON_3DM_BIG_CHUNK* point_chunk = m_chunk.Last();

  if (    0 != point_chunk 
       && TCODE_RH_POINT == point_chunk->m_typecode 
       && 0 == point_chunk->m_big_value )
  {
    // Some early V1 files have TCODE_RH_POINT chunks with arrow xdata
    // attached have a length set to zero.
    // For these chunks we need to set the chunk length so EndRead3dmChunk()
    // will keep going.
    pos0 = CurrentPosition();
  }
  else
    point_chunk = 0;

  // read v1 point
  bool rc = false;
  bool bHaveMat = false;
  ON_3dPoint pt;
  ON__3dmV1_XDATA xdata;
  rc = ReadPoint(pt);
  if (rc) 
  {
    rc = Read3dmV1AttributesOrMaterial(pAttributes,nullptr,bHaveMat,TCODE_ENDOFTABLE,&xdata);
    // do switch even if Read3dmV1AttributesOrMaterial() fails
    switch ( xdata.m_type )
    {
    case ON__3dmV1_XDATA::arrow_direction:
      if ( xdata.m_vector.Length() > ON_ZERO_TOLERANCE )
      {
        ON_OBSOLETE_V2_AnnotationArrow* arrow = new ON_OBSOLETE_V2_AnnotationArrow();
        arrow->m_tail = pt;
        arrow->m_head = pt + xdata.m_vector;
        *ppObject = arrow;
      }
      else
      {
        *ppObject = new ON_Point(pt);
      }
      break;

    case ON__3dmV1_XDATA::dot_text:
      {
        ON_OBSOLETE_V2_TextDot* dot = new ON_OBSOLETE_V2_TextDot();
        dot->point = pt;
        dot->m_text = xdata.m_string;
        if ( dot->m_text.IsEmpty() )
          dot->m_text = " "; // a single blank
        *ppObject = dot;
      }
      break;

    default:
      *ppObject = new ON_Point(pt);
      break;
    }
  }

  // carefully test for the V1 zero length chunk bug
  if ( rc && pos0 > 0 && 0 != point_chunk && point_chunk == m_chunk.Last() )
  {
    if ( TCODE_RH_POINT == point_chunk->m_typecode && 0 == point_chunk->m_big_value )
    {
      // This TCODE_RH_POINT chunk has the zero length chunk bug
      // that was in some V1 files. 
      // Fill in the correct chunk length so that reading can continue.
      ON__UINT64 pos1 = CurrentPosition();
      ON__UINT64 chunk_length = (pos1 > pos0) ? (pos1 - pos0) : 0;
      if ( chunk_length >= 32 && chunk_length < 0x0FFFFFFF )
        point_chunk->m_big_value = (ON__INT64)chunk_length;
    }
  }

  return rc;
}

static
void TweakAnnotationPlane( ON_Plane& plane )
{
  // 10 November 2003 Dale Lear
  //   Fixed lots of bugs in annotation plane tweaking.
  //   Before the fix this block of code was cut-n-pasted 
  //   in three places.  The fabs() calls were wrong.  In addition
  //   and the
  //   .x values where tested and then the .y/.z values were set.

  //    if( fabs( plane.origin.x > 1e10 ))
  //      plane.origin.x = 0.0;
  //    if( fabs( plane.origin.y > 1e10 ))
  //      plane.origin.y = 0.0;
  //    if( fabs( plane.origin.z > 1e10 ))
  //      plane.origin.z = 0.0;
  //    
  //    if( fabs( plane.xaxis.x > 1e10 ))
  //      plane.xaxis.x = 1.0;
  //    if( fabs( plane.xaxis.x > 1e10 ))
  //      plane.xaxis.y = 0.0;
  //    if( fabs( plane.xaxis.x > 1e10 ))
  //      plane.xaxis.z = 0.0;
  //    
  //    if( fabs( plane.yaxis.x > 1e10 ))
  //      plane.yaxis.x = 0.0;
  //    if( fabs( plane.yaxis.x > 1e10 ))
  //      plane.yaxis.y = 1.0;
  //    if( fabs( plane.yaxis.x > 1e10 ))
  //      plane.yaxis.z = 0.0;

  // Lowell has decided that annotation plane
  // coordinates bigger than "too_big" should be
  // set to zero.
  const double too_big = 1.0e10;

  if( fabs( plane.origin.x ) > too_big )
    plane.origin.x = 0.0;
  if( fabs( plane.origin.y ) > too_big )
    plane.origin.y = 0.0;
  if( fabs( plane.origin.z ) > too_big )
    plane.origin.z = 0.0;
  
  if( fabs( plane.xaxis.x ) > too_big )
    plane.xaxis.x = 1.0;
  if( fabs( plane.xaxis.y ) > too_big )
    plane.xaxis.y = 0.0;
  if( fabs( plane.xaxis.z ) > too_big )
    plane.xaxis.z = 0.0;
  
  if( fabs( plane.yaxis.x ) > too_big )
    plane.yaxis.x = 0.0;
  if( fabs( plane.yaxis.y ) > too_big )
    plane.yaxis.y = 1.0;
  if( fabs( plane.yaxis.z ) > too_big )
    plane.yaxis.z = 0.0;

  plane.xaxis.Unitize();
  plane.yaxis.Unitize();
  plane.zaxis = ON_CrossProduct(plane.xaxis,plane.yaxis);
  plane.zaxis.Unitize();
  plane.UpdateEquation();
}


#define RHINO_ANNOTATION_SETTINGS_VERSION_1  1
#define RHINO_LINEAR_DIMENSION_VERSION_1     1
#define RHINO_RADIAL_DIMENSION_VERSION_1     1
#define RHINO_ANGULAR_DIMENSION_VERSION_1    1
#define RHINO_TEXT_BLOCK_VERSION_1           1
#define RHINO_TEXT_BLOCK_VERSION_2           2
#define RHINO_ANNOTATION_LEADER_VERSION_1    1

#define BUFLEN 128

static bool ReadV1_TCODE_ANNOTATION_Helper( ON_BinaryArchive& archive, char* buffer, ON_wString& tc )
{
  char* cp = 0;
  int j = 0;
  if( !archive.ReadInt( &j))
    return false;
  size_t sz = (j+1)*sizeof(cp[0]);
  if( j > BUFLEN - 1 || !buffer )
  {
    cp = (char*)onmalloc( sz );
    if( !cp)
      return false;
  }
  else
  {
    cp = buffer;
  }

  memset( cp, 0, sz );
  if( !archive.ReadChar( j,  cp))
  {
    if ( cp != buffer )
      onfree(cp);
    return false;
  }

  cp[j] = 0;
  tc = cp;
  if ( cp != buffer )
    onfree( cp );
  return true;
}

bool ON_BinaryArchive::ReadV1_TCODE_ANNOTATION(
  unsigned int tcode,
  ON_Object** ppObject,
  ON_3dmObjectAttributes* pAttributes
  )
{
  enum RhAnnotationType
  {
    Nothing = 0,
    TextBlock = 1,
    DimHorizontal = 2,
    DimVertical = 3,
    DimAligned = 4,
    DimRotated = 5,
    DimAngular = 6,
    DimDiameter = 7 ,
    DimRadius = 8,
    Leader = 9,
    DimLinear = 10,
  };
  
  bool rc = false;
  *ppObject = nullptr;
  ON_wString tc;
  char buffer[BUFLEN];
  int i, j, k, byobject, version;
  //char* cp;
  double d, d4[4];
  //ON_3dPoint pt;

  switch( tcode)
  {
  case TCODE_TEXT_BLOCK:
    {
      // read the version id
      rc = ReadInt( &version);
      if ( rc &&
           (version == RHINO_TEXT_BLOCK_VERSION_1 ||
            version == RHINO_TEXT_BLOCK_VERSION_2) 
         )
      {
        //this is a version we can read....
        // this is a type flag that we throw away
        rc = ReadInt( &i);
        if( !rc)
          return rc;
 
        ON_OBSOLETE_V2_TextObject* text = new ON_OBSOLETE_V2_TextObject;
        text->SetType( ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtTextBlock);

        ON_Plane plane;

        // the entity plane 
        if( !ReadDouble( 3, &plane.origin.x))
          return false;
        if( !ReadDouble( 3, &plane.xaxis.x))
          return false;
        if( !ReadDouble( 3, &plane.yaxis.x))
          return false;

        // 11 November 2003 Dale Lear - see comments in TweakAnnotationPlane()
        TweakAnnotationPlane( plane );

        text->SetPlane( plane);

        // read string to display
        if ( !ReadV1_TCODE_ANNOTATION_Helper( *this, buffer, tc ) )
          return false;
        text->SetUserText( tc.Array());

        // flags ( future )
        if( !ReadInt( 1, &j))
          return false;

        // settings byobject flag
        if( !ReadInt( 1, &byobject))
          return false;

        // depending on the value of byobject, more fields might be read here

        // facename
        if ( !ReadV1_TCODE_ANNOTATION_Helper( *this, buffer, tc ) )
          return false;
        text->SetFaceName(tc);

        // face weight
        if( !ReadInt( 1, &j))
          return false;
        text->SetFontWeight( j);

        if( !ReadDouble( 1, &d))
          return false;
        text->SetHeight( d);

        // 2 extra doubles were written into the file by mistake in version 1
        if( version == RHINO_TEXT_BLOCK_VERSION_1 )
        {
          if( !ReadDouble( 1, &d))
            return false;
          if( !ReadDouble( 1, &d))
            return false;
        }
    
        if( text->UserText().Length() < 1 )
        {
          *ppObject = 0;
          return true;
        }
        *ppObject = text;
        rc = true;
      }
    }
    break;
 
  case TCODE_ANNOTATION_LEADER:
    {
      // read the version id
      if( !ReadInt( &i))
        return false;
      
      if( i == RHINO_ANNOTATION_LEADER_VERSION_1)
      {
        // redundant type code to throw away
        if( !ReadInt( &i))
          return false;

        ON_OBSOLETE_V2_Leader* ldr = new ON_OBSOLETE_V2_Leader;
        ldr->SetType( ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtLeader);

        ON_Plane plane;

        // the entity plane 
        if( !ReadDouble( 3, &plane.origin.x))
          return false;
        if( !ReadDouble( 3, &plane.xaxis.x))
          return false;
        if( !ReadDouble( 3, &plane.yaxis.x))
          return false;
        
        // 11 November 2003 Dale Lear - see comments in TweakAnnotationPlane()
        TweakAnnotationPlane( plane );

        ldr->SetPlane( plane);
        
        // flags ( future )
        if( !ReadInt( 1, &j))
          return false;
        
        // settings byobject flag
        if( !ReadInt( 1, &byobject))
          return false;
        
        // number of points to read
        if( !ReadInt( &k))
          return false;
        
        if( k < 2)
          return true;
        
        ON_SimpleArray<ON_2dPoint> points;
        for( j = 0; j < k; j++ )
        {
          double pt[3];
          if( !ReadDouble( 3, pt))
            return false;
          points.Append( ON_2dPoint( pt));
        }
        ldr->SetPoints( points);
        
        *ppObject = ldr;
        rc = true;
        break;
      }
    }
    break;
  case TCODE_LINEAR_DIMENSION:
    {
      // read the version id
      if( !ReadInt( &i))
        return false;
      
      if( i == RHINO_LINEAR_DIMENSION_VERSION_1)
      {
        if( !ReadInt( &i))
          return false;

        ON_OBSOLETE_V2_DimLinear* dim = new ON_OBSOLETE_V2_DimLinear;
        switch( i )
        {
        case DimHorizontal:
        case DimVertical:
        case DimRotated:
        case DimLinear:
          dim->SetType( ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimLinear);
          break;
        default:
          dim->SetType( ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAligned);
          break;
        }

        ON_Plane plane;

        // the entity plane 
        if( !ReadDouble( 3, &plane.origin.x))
          return false;
        if( !ReadDouble( 3, &plane.xaxis.x))
          return false;
        if( !ReadDouble( 3, &plane.yaxis.x))
          return false;

        // 11 November 2003 Dale Lear - see comments in TweakAnnotationPlane()
        TweakAnnotationPlane( plane );

        dim->SetPlane( plane);
        
        // definition points in coordinates of entity plane
        ON_SimpleArray<ON_2dPoint> points;
        for( j = 0; j < 11; j++ )
        {
          double pt[3];
          if( !ReadDouble( 3, pt))
            return false;
          points.Append( ON_2dPoint( pt));
        }
        dim->SetPoints( points);
        
        // read user text string 
        if ( !ReadV1_TCODE_ANNOTATION_Helper( *this, buffer, tc ) )
          return false;
        dim->SetUserText( tc.Array());
        
        // Set the symbols used in dimension strings to the selected options
        //        SetStringSymbols();
        
        // read string to display
        if ( !ReadV1_TCODE_ANNOTATION_Helper( *this, buffer, tc ) )
          return false;
        dim->SetDefaultText( tc.Array());
        
        // user positioned text flag
        if( !ReadInt( &j))
          return false;
        dim->SetUserPositionedText( j);
        
        // flags ( future )
        if( !ReadInt( 1, &j))
          return false;
        
        // settings byobject flag
        if( !ReadInt( 1, &byobject))
          return false;
        
        *ppObject = dim;
        rc = true;
        break;
      }
    }
    break;

  case TCODE_ANGULAR_DIMENSION:
    {
      // read the version id
      if( !ReadInt( &i))
        return false;
      
      if( i == RHINO_ANGULAR_DIMENSION_VERSION_1)
      {
        if( !ReadInt( &i))
          return false;

        ON_OBSOLETE_V2_DimAngular* dim = new ON_OBSOLETE_V2_DimAngular;
        dim->SetType( ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAngular);
        
        ON_Plane plane;

        // the entity plane 
        if( !ReadDouble( 3, &plane.origin.x))
          return false;
        if( !ReadDouble( 3, &plane.xaxis.x))
          return false;
        if( !ReadDouble( 3, &plane.yaxis.x))
          return false;

        // 11 November 2003 Dale Lear - see comments in TweakAnnotationPlane()
        TweakAnnotationPlane( plane );

        dim->SetPlane( plane);
        
        if( !ReadDouble( &d))
          return false;
        dim->SetAngle( d);

        if( !ReadDouble( &d))
          return false;
        dim->SetRadius( d);

        // distances from apes to start and end of dimensioned lines - not used
        if( !ReadDouble( 4, d4))
          return false;

        // definition points in coordinates of entity plane
        ON_SimpleArray<ON_2dPoint> points;
        for( j = 0; j < 5; j++ )
        {
          double pt[3];
          if( !ReadDouble( 3, pt))
            return false;
          points.Append( ON_2dPoint( pt));
        }
        dim->SetPoints( points);
        
        // read user text string 
        if ( !ReadV1_TCODE_ANNOTATION_Helper( *this, buffer, tc ) )
          return false;
        dim->SetUserText( tc.Array());
        
        // Set the symbols used in dimension strings to the selected options
        //        SetStringSymbols();
        
        // read string to display
        if ( !ReadV1_TCODE_ANNOTATION_Helper( *this, buffer, tc ) )
          return false;
        dim->SetDefaultText( tc.Array());
        
        // user positioned text flag
        if( !ReadInt( &j))
          return false;
        dim->SetUserPositionedText( j);
        
        
        // flags ( future )
        if( !ReadInt( 1, &j))
          return false;
        
        // settings byobject flag
        if( !ReadInt( 1, &byobject))
          return false;
        
        
        *ppObject = dim;
        rc = true;
        break;
      }
    }
    break;

  case TCODE_RADIAL_DIMENSION:
    {
      // read the version id
      if( !ReadInt( &i))
        return false;
      
      if( i == RHINO_RADIAL_DIMENSION_VERSION_1)
      {
        if( !ReadInt( &i))
          return false;

        ON_OBSOLETE_V2_DimRadial* dim = new ON_OBSOLETE_V2_DimRadial;

        switch( i)
        {
        case DimDiameter:
          dim->SetType( ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter);
          break;
        case DimRadius:
          dim->SetType( ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimRadius);
          break;
        }

        ON_Plane plane;

        // the entity plane 
        if( !ReadDouble( 3, &plane.origin.x))
          return false;
        if( !ReadDouble( 3, &plane.xaxis.x))
          return false;
        if( !ReadDouble( 3, &plane.yaxis.x))
          return false;

        // 11 November 2003 Dale Lear - see comments in TweakAnnotationPlane()
        TweakAnnotationPlane( plane );

        dim->SetPlane( plane);
        
        // definition points in coordinates of entity plane
        ON_SimpleArray<ON_2dPoint> points;
        for( j = 0; j < 5; j++ )
        {
          double pt[3];
          if( !ReadDouble( 3, pt))
            return false;
          points.Append( ON_2dPoint( pt));
        }
        dim->SetPoints( points);
        
        // read user text string 
        if ( !ReadV1_TCODE_ANNOTATION_Helper( *this, buffer, tc ) )
          return false;
        dim->SetUserText( tc.Array());
        
        // Set the symbols used in dimension strings to the selected options
        //        SetStringSymbols();
        
        // read string to display
        if ( !ReadV1_TCODE_ANNOTATION_Helper( *this, buffer, tc ) )
          return false;
        dim->SetDefaultText( tc.Array());
        
        // user positioned text flag
        if( !ReadInt( &j))
          return false;
        dim->SetUserPositionedText( j);
        
        // flags ( future )
        if( !ReadInt( 1, &j))
          return false;
        
        // settings byobject flag
        if( !ReadInt( 1, &byobject))
          return false;
        
        
        *ppObject = dim;
        rc = true;
        break;
      }
    
    }
    break;

  default:  // some unknown type to skip over
    return true;
  } //switch
  
  if( rc)
  {
    bool bHaveMat = false;
    Read3dmV1AttributesOrMaterial(pAttributes,nullptr,bHaveMat,TCODE_ENDOFTABLE);
  }
  
  return rc;
  
  // TODO: fill in this function
  
  // input tcode               returned *ppObject points to
  // TCODE_TEXT_BLOCK:         ON_OBSOLETE_V2_TextObject
  // TCODE_ANNOTATION_LEADER:  ON_OBSOLETE_V2_Leader
  // TCODE_LINEAR_DIMENSION:   ON_OBSOLETE_V2_DimLinear
  // TCODE_ANGULAR_DIMENSION:  ON_OBSOLETE_V2_DimAngular
  // TCODE_RADIAL_DIMENSION:   ON_OBSOLETE_V2_DimRadial
  //return true if successful and false for failure.
}


bool ON_BinaryArchive::ReadV1_TCODE_MESH_OBJECT(
                                                ON_Object** ppObject,
                                                ON_3dmObjectAttributes* pAttributes
                                                )
{
  ON_Mesh* mesh = 0;
  bool rc = false;
  // read v1 mesh
  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  int i;
  if ( !BeginRead3dmBigChunk(&tcode,&big_value) )
    return false;
  
  if ( tcode == TCODE_COMPRESSED_MESH_GEOMETRY ) for(;;) 
  {
    
    int point_count = 0;
    int face_count = 0;
    int boolHasVertexNormalsAsInt = false;
    int boolHasTexCoordsAsInt = false;
    ON_BoundingBox bbox;
    
    if (!ReadInt(&point_count) )
      break;
    if ( point_count <= 0 )
      break;
    if (!ReadInt(&face_count) )
      break;
    if ( face_count <= 0 )
      break;
    if (!ReadInt(&boolHasVertexNormalsAsInt) )
      break;
    if (!ReadInt(&boolHasTexCoordsAsInt) )
      break;
    if ( !ReadPoint(bbox.m_min) )
      break;
    if ( !ReadPoint(bbox.m_max) )
      break;

    const bool bHasVertexNormals = boolHasVertexNormalsAsInt ? true : false;
    const bool bHasTexCoords = boolHasTexCoordsAsInt ? true : false;

    mesh = new ON_Mesh(face_count,
                       point_count,
                       bHasVertexNormals,
                       bHasTexCoords
                       );

    // read 3d vertex locations
    {
      ON_3dVector d = bbox.Diagonal();
      double dx = d.x / 65535.0;
      double dy = d.y / 65535.0;
      double dz = d.z / 65535.0;
      unsigned short xyz[3];
      ON_3fPoint pt;
      for ( i = 0; i < point_count; i++ ) {
        if ( !ReadShort(3,xyz) )
          break;
        pt.x = (float)(dx*xyz[0] + bbox.m_min.x);
        pt.y = (float)(dy*xyz[1] + bbox.m_min.y);
        pt.z = (float)(dz*xyz[2] + bbox.m_min.z);
        mesh->m_V.Append(pt);
      }
    }
    if ( mesh->m_V.Count() != point_count )
      break;

    // read triangle/quadrangle faces
    if ( point_count < 65535 ) {
      unsigned short abcd[4];
      for ( i = 0; i < face_count; i++ ) {
        if ( !ReadShort(4,abcd) )
          break;
        ON_MeshFace& f = mesh->m_F.AppendNew();
        f.vi[0] = abcd[0];
        f.vi[1] = abcd[1];
        f.vi[2] = abcd[2];
        f.vi[3] = abcd[3];
      }
    }
    else {
      int abcd[4];
      for ( i = 0; i < face_count; i++ ) {
        if ( !ReadInt(4,abcd) )
          break;
        ON_MeshFace& f = mesh->m_F.AppendNew();
        f.vi[0] = abcd[0];
        f.vi[1] = abcd[1];
        f.vi[2] = abcd[2];
        f.vi[3] = abcd[3];
      }
    }
    if ( mesh->m_F.Count() != face_count )
      break;

    if ( bHasVertexNormals ) {
      char xyz[3];
      ON_3fVector normal;
      for ( i = 0; i < point_count; i++ ) {
        if ( !ReadChar(3,xyz) )
          break;
        normal.x = (float)(((signed char)xyz[0])/127.0);
        normal.y = (float)(((signed char)xyz[1])/127.0);
        normal.z = (float)(((signed char)xyz[2])/127.0);
        mesh->m_N.Append(normal);
      }
      if ( mesh->m_N.Count() != mesh->m_V.Count() )
        break;
    }

    if ( bHasTexCoords ) {
      unsigned short uv[2];
      ON_2fPoint t;
      for ( i = 0; i < point_count; i++ ) {
        if ( !ReadShort(2,uv) )
          break;
        t.x = (float)(uv[0]/65535.0);
        t.y = (float)(uv[1]/65535.0);
        mesh->m_T.Append(t);
      }
      if ( mesh->m_T.Count() != mesh->m_V.Count() )
        break;
    }

    rc = true;

    break;
  }
  
  if ( !EndRead3dmChunk() )
    rc = false;

  if ( rc && mesh ) {
    *ppObject = mesh;
  }
  else {
    if ( mesh )
      delete mesh;
    rc = false;
  }

  if ( rc && mesh ) {
    // attributes and material information follows the TCODE_COMPRESSED_MESH_GEOMETRY chunk;
    bool bHaveMat = false;
    Read3dmV1AttributesOrMaterial(pAttributes,nullptr,bHaveMat,TCODE_ENDOFTABLE);
  }

  return rc;
}

static bool BeginRead3dmLEGACYSTUFF( ON_BinaryArchive& file, unsigned int stuff_tcode )
{
  // begins reading stuff chunk
  bool rc = false;
  ON__UINT32 tcode = !stuff_tcode;
  ON__INT64 big_value = 0;
  for (;;) 
  {
    if ( !file.BeginRead3dmBigChunk(&tcode,&big_value) )
      break;
    if ( tcode == stuff_tcode ) {
      rc = true;
      break;
    }
    if ( !file.EndRead3dmChunk() )
      break;
  }
  return rc;
}

static ON_NurbsCurve* ReadV1_TCODE_LEGACY_SPLSTUFF( ON_BinaryArchive& file )
{
  // reads contents of a v1 TCODE_LEGACY_SPLSTUFF chunk
  ON_NurbsCurve* pNurbsCurve = 0;
  int i, dim, is_rat, order, cv_count, is_closed, form;
  ON_BoundingBox bbox;
  char c;

  // read v1 agspline chunk
  if ( !file.ReadChar(1,&c) )
    return nullptr;
  if ( c != 2 && c != 3 )
    return nullptr;
  dim = c;
  if ( !file.ReadChar(1,&c) )
    return nullptr;
  if ( c != 0 && c != 1 && c != 2 )
    return nullptr;
  is_rat = c; // 0 = no, 1 = euclidean, 2 = homogeneous
  if ( !file.ReadChar(1,&c) )
    return nullptr;
  if ( c < 2 )
    return nullptr;
  order = c;   
  
  {
    // 5 February 2003 - An single case of a V1 file
    //     with a spline that had cv_count = 54467 (>32767)
    //     exists.  Changing from a signed short to
    //     an unsigned short fixed the problem.
    //     The ui casting stuff is here to keep all
    //     the various compilers/lints happy and to
    //     make sure the short with the high bit set
    //     gets properly converted to a positive cv_count.
    unsigned short s;
    if ( !file.ReadShort(1,&s) )
      return nullptr;
    unsigned int ui = s;
    cv_count = (int)ui;
    if ( cv_count < order )
      return nullptr;
  }

  // The "is_closed" and "form" flags are here to recording
  // the values of legacy data found in the Rhino file.  These
  // values are not used in the toolkit code.
  if ( !file.ReadByte(1,&c) )
    return nullptr;  
  if (c != 0 && c != 1 && c != 2)
    return nullptr;
  is_closed = c; // 0 = open, 1 = closed, 2 = periodic
  if ( !file.ReadByte(1,&c) )
    return nullptr;
  form = c;

  // read bounding box
  if ( !file.ReadDouble( dim, bbox.m_min ) )
    return nullptr;
  if ( !file.ReadDouble( dim, bbox.m_max ) )
    return nullptr;

  pNurbsCurve = new ON_NurbsCurve( dim, is_rat?true:false, order, cv_count );

  bool rc = false;
  for(;;) {

    // read legacy v1 knot vector 
    const int knot_count = order+cv_count-2;
    int       knot_index = 0;
    double    knot;

    // clamped_end_knot_flag: 0 = none, 1 = left, 2 = right, 3 = both
    char clamped_end_knot_flag = 0;
    if ( order > 2 ) 
      file.ReadChar(1,&clamped_end_knot_flag);

    // first knot(s)
    if ( !file.ReadDouble(&knot) )
      break;
    pNurbsCurve->m_knot[knot_index++] = knot;
    if (clamped_end_knot_flag % 2) {
      // clamped_start_knot
      while ( knot_index <= order-2 ) 
        pNurbsCurve->m_knot[knot_index++] = knot;
    }

    // middle knots
    while ( knot_index <= cv_count-1 ) {
      if ( !file.ReadDouble(&knot) )
        break;
      pNurbsCurve->m_knot[knot_index++] = knot;
    }
    if ( knot_index <= cv_count-1 )
      break;

    // end knot(s)
    if ( clamped_end_knot_flag >= 2 ) {
      while ( knot_index < knot_count )
        pNurbsCurve->m_knot[knot_index++] = knot;
    }
    else {
      while ( knot_index < knot_count ) {
        if ( !file.ReadDouble(&knot) )
          break;
        pNurbsCurve->m_knot[knot_index++] = knot;
      }
      if ( knot_index < knot_count )
        break;
    }

    // read legacy v1 control points
    const int cvdim = ( is_rat ) ? dim+1 : dim;
    for ( i = 0; i < cv_count; i++ ) {
      if ( !file.ReadDouble( cvdim, pNurbsCurve->CV(i) ) )
        break;
    }
    if ( i < cv_count )
      break;
    if ( is_rat ) {
      // is_rat == 1 check fails because invalid is_rat flags in old files
      // convert rational CVs from euclidean to homogeneous
      double w, *cv;
      int cv_index;
      for ( cv_index = 0; cv_index < cv_count; cv_index++ ) {
        cv = pNurbsCurve->CV(cv_index);
        w = cv[dim];
        for ( i = 0; i < dim; i++ )
          cv[i] *= w;
      }
    }
    if ( order == 2 && cv_count == 2 && pNurbsCurve->m_knot[0] > pNurbsCurve->m_knot[1] ) {
      // a few isolated old v1 3DM file created by Rhino 1.0 files have lines with reversed knots.
      pNurbsCurve->m_knot[0] = -pNurbsCurve->m_knot[0];
      pNurbsCurve->m_knot[1] = -pNurbsCurve->m_knot[1];
    }
    rc = true;

    break;
  }
  if ( !rc && pNurbsCurve ) {
    delete pNurbsCurve;
    pNurbsCurve = 0;
  }
  return pNurbsCurve;
}

static bool ReadV1_TCODE_LEGACY_SPL( ON_BinaryArchive& file,
  ON_NurbsCurve*& pNurbsCurve
  )
{
  // reads contents of TCODE_LEGACY_SPL chunk
  pNurbsCurve = 0;
  bool rc = BeginRead3dmLEGACYSTUFF(file, TCODE_LEGACY_SPLSTUFF );
  if ( !rc )
    return false;
  pNurbsCurve = ReadV1_TCODE_LEGACY_SPLSTUFF(file);
  if ( !file.EndRead3dmChunk() ) // end of TCODE_LEGACY_SPLSTUFF chunk
    rc = false;
  if ( !pNurbsCurve )
    rc = false;
  return rc;
}

static ON_NurbsSurface* ReadV1_TCODE_LEGACY_SRFSTUFF( ON_BinaryArchive& file )
{
  // reads contents of TCODE_LEGACY_SRFSTUFF chunk
  ON_NurbsSurface* pNurbsSurface = 0;
  int i, j, dim=0, is_rat=0, order[2], cv_count[2], is_closed[2], is_singular[2], form;
  ON_BoundingBox bbox;
  char c;

  // read contents of v1 TCODE_LEGACY_SRFSTUFF chunk
  if ( !file.ReadChar(1,&c) )
    return nullptr;
  if ( c != 2 && c != 3 )
    return nullptr;
  dim = c;
  if ( !file.ReadByte(1,&c) )
    return nullptr;
  form = c;
  if ( !file.ReadChar(1,&c) )
    return nullptr;
  if ( c < 1 )
    return nullptr;
  order[0] = c+1;    
  if ( !file.ReadChar(1,&c) )
    return nullptr;
  if ( c < 1 )
    return nullptr;
  order[1] = c+1;    
  
  {
    // 5 February 2003 - An single case of a V1 files
    //     See the comment above in ReadV1_TCODE_LEGACY_SPLSTUFF
    //     concerning the spline with cv_count >= 0x8000.
    //     The analogous fix is here for the surface case.
    unsigned short s;
    if ( !file.ReadShort(1,&s) )
      return nullptr;
    if ( s < 1 )
      return nullptr;
    unsigned int ui = s;
    cv_count[0] = order[0]-1+((int)ui);    
    if ( !file.ReadShort(1,&s) )
      return nullptr;
    if ( s < 1 )
      return nullptr;
    ui = s;
    cv_count[1] = order[1]-1+((int)ui);    
  }
  
  // "ratu" 0 = no, 1 = euclidean, 2 = homogeneous
  if ( !file.ReadChar(1,&c) )
    return nullptr;
  if ( c == 1 ) is_rat = 1; else if ( c == 2 ) is_rat = 2;
  
  // "ratv" 0 = no, 1 = euclidean, 2 = homogeneous
  if ( !file.ReadChar(1,&c) )
    return nullptr;
  if ( c == 1 ) is_rat = 1; else if ( c == 2 ) is_rat = 2;

  // The "is_closed" and "is_singular" flags are here to recording
  // the values of legacy data found in the Rhino file.  These
  // values are not used in the toolkit code.
  if ( !file.ReadByte(1,&c) )
    return nullptr;  
  if (c != 0 && c != 1 && c != 2)
    return nullptr;
  is_closed[0] = c; // 0 = open, 1 = closed, 2 = periodic
  if ( !file.ReadByte(1,&c) )
    return nullptr;  
  if (c != 0 && c != 1 && c != 2)
    return nullptr;
  is_closed[1] = c; // 0 = open, 1 = closed, 2 = periodic

  if ( !file.ReadByte(1,&c) )
    return nullptr;  
  if (c != 0 && c != 1 && c != 2 && c != 3)
    return nullptr;
  is_singular[0] = c;
  if ( !file.ReadByte(1,&c) )
    return nullptr;  
  if (c != 0 && c != 1 && c != 2 && c != 3)
    return nullptr;
  is_singular[1] = c;

  // read bounding box
  if ( !file.ReadDouble( dim, bbox.m_min ) )
    return nullptr;
  if ( !file.ReadDouble( dim, bbox.m_max ) )
    return nullptr;

  pNurbsSurface = new ON_NurbsSurface( dim, is_rat?true:false, 
                                       order[0], order[1], 
                                       cv_count[0], cv_count[1] );

  bool rc = false;
  for (;;) {

    // read legacy v1 knot vectors 
    if ( !file.ReadDouble( order[0]+cv_count[0]-2, pNurbsSurface->m_knot[0] ) )
      break;
    if ( !file.ReadDouble( order[1]+cv_count[1]-2, pNurbsSurface->m_knot[1] ) )
      break;

    // read legacy v1 control points
    const int cvdim = ( is_rat ) ? dim+1 : dim;
    for ( i = 0; i < cv_count[0]; i++ ) {
      for ( j = 0; j < cv_count[1]; j++ ) {
        if ( !file.ReadDouble( cvdim, pNurbsSurface->CV(i,j) ) )
          break;
      }
      if ( j < cv_count[1] )
        break;
    }
    if ( i < cv_count[0] )
      break;
    if ( is_rat == 1 ) {
      double w, *cv;
      int k;
      for ( i = 0; i < cv_count[0]; i++ ) for ( j = 0; j < cv_count[1]; j++ ) {
        cv = pNurbsSurface->CV(i,j);
        w = cv[dim];
        for ( k = 0; k < dim; k++ )
          cv[k] *= w;
      }
    }
    rc = true;

    break;
  }
  if ( !rc ) {
    delete pNurbsSurface;
    pNurbsSurface = 0;
  }

  return pNurbsSurface;
}

static bool ReadV1_TCODE_LEGACY_SRF( ON_BinaryArchive& file,
  ON_NurbsSurface*& pNurbsSurface
  )
{
  pNurbsSurface = 0;
  bool rc = BeginRead3dmLEGACYSTUFF( file, TCODE_LEGACY_SRF );
  if ( rc ) {
    rc = BeginRead3dmLEGACYSTUFF( file, TCODE_LEGACY_SRFSTUFF );
    if ( rc ) {
      pNurbsSurface = ReadV1_TCODE_LEGACY_SRFSTUFF( file );
      if ( !file.EndRead3dmChunk() ) // end of TCODE_LEGACY_SRFSTUFF chunk
        rc = false;
    }
    if ( !file.EndRead3dmChunk() )
      rc = false; // end of TCODE_LEGACY_SRF chunk
  }
  if ( !rc && pNurbsSurface ) {
    delete pNurbsSurface;
    pNurbsSurface = 0;
  }
  return rc;
}

ON_Curve* ReadV1_TCODE_LEGACY_CRVSTUFF( ON_BinaryArchive& file )
{
  // reads contents of a v1 TCODE_LEGACY_CRVSTUFF chunk
  ON_Curve* curve = 0;
  ON_PolyCurve* polycurve = 0;
  ON_NurbsCurve* segment = 0;
  bool rc = false;
  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  int i;
  bool bIsPolyline = false;
  ON_BoundingBox bbox;

  for (;;) {
    char c;
    short s;
    int segment_count = 0;
    file.ReadChar(1,&c);  

    // fix RH-40959
    // Microsoft Visual C 15.3.3 release build fails to set dim (works in debug builds)
    //if ( c != 2 && c != 3 )
    //  break;
    //int dim = c;
    
    // this works
    int dim;
    if (2 == c)
      dim = 2;
    else if (3 == c)
      dim = 3;
    else
      break;


    file.ReadChar(1,&c);
    if ( c != -1 && c != 0 && c != 1 && c != 2 )
      break;
    //int is_closed = (c) ? 1 : 0;
    file.ReadShort(&s);
    if ( s < 1 )
      break;
    file.ReadDouble( dim, bbox.m_min);
    file.ReadDouble( dim, bbox.m_max);
    segment_count = s;
    for ( i = 0; i < segment_count; i++ ) {
      segment = 0;
      tcode = 0;
      big_value = 0;
      if ( !file.BeginRead3dmBigChunk( &tcode, &big_value ) )
        break;
      if ( tcode == TCODE_LEGACY_SPL && big_value > 0 ) {
        ReadV1_TCODE_LEGACY_SPL(file,segment);
      }
      if ( !file.EndRead3dmChunk() ) {
        if ( segment ) {
          delete segment;
          segment = 0;
        }
        break;
      }
      if ( !segment )
        break;
      if ( i == 0 )
        polycurve = new ON_PolyCurve(segment_count);
      if ( segment->CVCount() > 2 || segment->Order() != 2 || segment->IsRational() ) 
      {
        if ( segment->Order() != 2 || segment->IsRational() )
          bIsPolyline = false;
        polycurve->Append(segment);
      }
      else 
      {
        ON_LineCurve* line = new ON_LineCurve();
        line->m_t.Set( segment->m_knot[0], segment->m_knot[1] );
        segment->GetCV( 0, line->m_line.from );
        segment->GetCV( 1, line->m_line.to );
        line->m_dim = segment->m_dim;
        delete segment;
        segment = 0;
        polycurve->Append(line);
      }
    }

    // 5 February 2003
    //   The check for a nullptr polycurve was added to avoid
    //   crashes in files when the first NURBS curve in the
    //   polycurve could not be read.
    if ( 0 == polycurve )
      break;
    if ( polycurve->Count() != segment_count )
      break;
    rc = true;
    break;
  }

  if ( rc && polycurve ) 
  {
    if ( polycurve->Count() == 1 )
    {
      curve = polycurve->HarvestSegment(0);
      delete polycurve;
    }
    else if ( bIsPolyline ) 
    {
      ON_PolylineCurve* pline = new ON_PolylineCurve();
      pline->m_dim = polycurve->Dimension();
      pline->m_t.Reserve(polycurve->Count()+1);
      pline->m_t.SetCount(polycurve->Count()+1);
      polycurve->GetSpanVector( pline->m_t.Array() );
      pline->m_pline.Reserve(polycurve->Count()+1);
      for ( i = 0; i < polycurve->Count(); i++ ) {
        pline->m_pline.Append(polycurve->SegmentCurve(i)->PointAtStart());
      }
      pline->m_pline.Append(polycurve->SegmentCurve(polycurve->Count()-1)->PointAtEnd());
      curve = pline;
      delete polycurve;
    }
    else 
    {
      curve = polycurve;
    }
  }
  else 
  {
    if ( polycurve )
      delete polycurve;
    rc = false;
  }

  return curve;
}

bool ON_Brep::ReadV1_LegacyTrimStuff( ON_BinaryArchive& file, 
        ON_BrepFace&, // face - formal parameter intentionally ignored
        ON_BrepLoop& loop )
{
  // read contents of TCODE_LEGACY_TRMSTUFF chunk
  bool rc = false;
  int revedge, gcon, mono;
  int curve2d_index = -1, curve3d_index = -1, trim_index = -1;
  double tol_3d, tol_2d;
  ON_Curve* curve2d = nullptr;
  ON_Curve* curve3d = nullptr;

  char c;
  file.ReadChar( &c );

  bool bHasEdge = (c % 2 ); // bit 0 = 1 if "tedge" has non nullptr "->edge"
  bool bHasMate = (c & 6 ); // bit 1 or 2 = 1 if "tedge" has non nullptr "->twin"
  bool bIsSeam  = (c & 2 ); // bit 1 = 1 if "tedge->twin" belongs to same face

  if ( !file.ReadInt(&revedge) )
    return false;
  if ( !file.ReadInt(&gcon) )
    return false;
  if ( !file.ReadInt(&mono) )
    return false;
  if ( !file.ReadDouble( &tol_3d ) )
    return false;
  if ( !file.ReadDouble( &tol_2d ) )
    return false;

  // 2d trim curve
  if ( !BeginRead3dmLEGACYSTUFF( file, TCODE_LEGACY_CRV ) )
    return false;
  if ( BeginRead3dmLEGACYSTUFF( file, TCODE_LEGACY_CRVSTUFF ) ) {
    curve2d = ReadV1_TCODE_LEGACY_CRVSTUFF(file);
    if ( !file.EndRead3dmChunk() ) // end of TCODE_LEGACY_CRVSTUFF chunk
      rc = false;
  }
  if ( !file.EndRead3dmChunk() ) // end of TCODE_LEGACY_CRV chunk
    rc = false;
  if ( !curve2d )
    return false;
  curve2d_index = AddTrimCurve(curve2d);
  if ( curve2d_index < 0 ) {
    delete curve2d;
    return false;
  }

  // 3d curve
  if ( bHasEdge ) {
    if ( !BeginRead3dmLEGACYSTUFF( file, TCODE_LEGACY_CRV ) )
      return false;
    if ( BeginRead3dmLEGACYSTUFF( file, TCODE_LEGACY_CRVSTUFF ) ) {
      curve3d = ReadV1_TCODE_LEGACY_CRVSTUFF(file);
      if ( !file.EndRead3dmChunk() ) // end of TCODE_LEGACY_CRVSTUFF chunk
        rc = false;
    }
    if ( !file.EndRead3dmChunk() ) // end of TCODE_LEGACY_CRV chunk
      rc = false;
    if ( !curve3d )
      return false;
    curve3d_index = AddEdgeCurve(curve3d);
    if ( curve3d_index < 0 ) {
      delete curve3d;
      return false;
    }
    ON_BrepEdge& edge = NewEdge(curve3d_index);
    ON_BrepTrim& trim = NewTrim( edge, 
                                    revedge ? true : false,
                                    loop,
                                    curve2d_index
                                    );
    trim_index = trim.m_trim_index;
  }
  else {
    ON_BrepTrim& trim = NewTrim( revedge ? true : false,
                                    loop,
                                    curve2d_index
                                    );
    trim_index = trim.m_trim_index;
  }
  if ( trim_index >= 0 ) {
    ON_BrepTrim& trim = m_T[trim_index];
    trim.m__legacy_2d_tol = tol_2d;
    trim.m__legacy_3d_tol = tol_3d;
    trim.m__legacy_flags_Set(gcon,mono);
    if ( bIsSeam ) {
      trim.m_type = ON_BrepTrim::seam;
    }
    else if ( bHasMate ) {
      trim.m_type = ON_BrepTrim::mated;
    }
    else if ( bHasEdge ) {
      trim.m_type = ON_BrepTrim::boundary;
    }
    else {
      trim.m_type = ON_BrepTrim::singular;
    }
  }

  return (trim_index>=0) ? true : false;
}

bool ON_Brep::ReadV1_LegacyTrim( ON_BinaryArchive& file, 
                            ON_BrepFace& face,
                            ON_BrepLoop& loop )
{
  bool rc = false;
  if ( !BeginRead3dmLEGACYSTUFF( file, TCODE_LEGACY_TRM ) )
    return false;
  rc = BeginRead3dmLEGACYSTUFF( file, TCODE_LEGACY_TRMSTUFF );
  if ( rc ) {
    rc = ReadV1_LegacyTrimStuff( file, face, loop );
    if ( !file.EndRead3dmChunk() ) // end of TCODE_LEGACY_TRMSTUFF
      rc = false;
  }
  if ( !file.EndRead3dmChunk() ) // end of TCODE_LEGACY_TRM chunk
    rc = false;
  return rc;
}


bool ON_Brep::ReadV1_LegacyLoopStuff( ON_BinaryArchive& file, 
                               ON_BrepFace& face )
{
  // reads contents of TCODE_LEGACY_BNDSTUFF chunk
  // read boundary
  ON_BrepLoop::TYPE loop_type = ON_BrepLoop::unknown;
  int tedge_count, btype, lti;
  double pspace_box[2][2]; // parameter space bounding box

  if ( !file.ReadInt( &tedge_count ) )
    return false;
  if ( tedge_count < 1 ) {
    return false;
  }
  if ( !file.ReadInt( &btype ) )
    return false;
  if ( btype < -1 || btype > 1 ) {
    return false;
  }
  if ( !file.ReadDouble( 4, &pspace_box[0][0] ) )
    return false;
  switch( btype ) {
  case -1:
    loop_type = ON_BrepLoop::slit;
    break;
  case  0:
    loop_type = ON_BrepLoop::outer;
    break;
  case  1:
    loop_type = ON_BrepLoop::inner;
    break;
  }
  ON_BrepLoop& loop = NewLoop( loop_type, face );

  for ( lti = 0; lti < tedge_count; lti++ ) {
    if ( !ReadV1_LegacyTrim( file, face, loop ) )
      return false;
  }

  return true;
}

bool ON_Brep::ReadV1_LegacyLoop( ON_BinaryArchive& file, 
                                        ON_BrepFace& face )
{
  bool rc = false;
  if ( !BeginRead3dmLEGACYSTUFF( file, TCODE_LEGACY_BND ) )
    return false;
  rc = BeginRead3dmLEGACYSTUFF( file, TCODE_LEGACY_BNDSTUFF );
  if ( rc ) {
    rc = ReadV1_LegacyLoopStuff( file, face );
    if ( !file.EndRead3dmChunk() ) // end of TCODE_LEGACY_BNDSTUFF
      rc = false;
  }
  if ( !file.EndRead3dmChunk() ) // end of TCODE_LEGACY_BND chunk
    rc = false;
  return rc;
}

bool ON_Brep::ReadV1_LegacyFaceStuff( ON_BinaryArchive& file )
{
  // reads contents of TCODE_LEGACY_FACSTUFF chunk
  ON_NurbsSurface* surface = 0;
  ON_Workspace ws;
  int flipnorm = 0;
  int ftype = 0;
  int bndcnt = 0;
  int twincnt = 0;
  bool bHasOuter = false;
  ON_BoundingBox face_bbox;

  int ti0 = m_T.Count();

  bool rc = false;

  // read flags
  if ( !file.ReadInt(&flipnorm) )
    return false;
  if ( flipnorm < 0 || flipnorm > 1 )
    return false;
  if ( !file.ReadInt(&ftype) )
    return false;
  if ( !file.ReadInt(&bndcnt) )
    return false;
  bHasOuter = (bndcnt%2); // always true in v1 files
  bndcnt /= 2;

  // read bounding box
  if ( !file.ReadDouble( 3, face_bbox.m_min ) )
    return false;
  if ( !file.ReadDouble( 3, face_bbox.m_max ) )
    return false;

  // B-rep edge gluing info 
  if ( !file.ReadInt(&twincnt) )
    return false;
  short* glue = (twincnt > 0 ) ? (short*)ws.GetMemory(twincnt*sizeof(*glue)) : nullptr;
  if (twincnt > 0) {
    if ( !file.ReadShort(twincnt,glue) )
      return false;
  }

  // read surface
  if ( !ReadV1_TCODE_LEGACY_SRF( file, surface ) )
    return false;
  if ( !surface )
    return false;
  const int srf_index = AddSurface(surface);

  // create face
  ON_BrepFace& face = NewFace(srf_index);
  face.m_bRev = (flipnorm) ? true : false;
  face.m_li.Reserve(bndcnt);

  // read boundary loops
  int loop_index = -1;
  if ( !bHasOuter ) {
    // TODO: cook up outer boundary loop (never happes with v1 files)
    face.m_li.Append(loop_index);
  }
  int bi;
  rc = true;
  for ( bi = 0; rc && bi < bndcnt; bi++ ) {
    rc = ReadV1_LegacyLoop( file, face );
  }

  if ( twincnt > 0 ) {
    // twincnt = number of seams edges in face
    // glue[] = order 2 permutation of {0,....,twincnt-1}

    // set seam_i[] = m_T[] indices of seam trims
    int si, ti;
    const int ti1 = m_T.Count();
    int* seam_i = (int*)ws.GetMemory(twincnt*sizeof(*seam_i));
    for ( ti = ti0, si = 0; ti < ti1 && si < twincnt; ti++ ) {
      if (m_T[ti].m_type != ON_BrepTrim::seam )
        continue;
      seam_i[si++] = ti;
    }

    if ( si == twincnt ) {
      // glue seams
      for ( si = 0; si < twincnt; si++ ) {
        if ( glue[si] >= 0 && glue[si] < twincnt ) {
          const int i0 = seam_i[si];
          const int i1 = seam_i[glue[si]];
          // m_T[i0] and m_T[i1] use the same edge;
          const int ei0 = m_T[i0].m_ei;
          const int ei1 = m_T[i1].m_ei;
          if ( ei0 == -1 && ei1 >= 0 ) {
            m_T[i0].m_ei = ei1;
            m_E[ei1].m_ti.Append(i0);
          }
          else if ( ei1 == -1 && ei0 >= 0 ) {
            m_T[i1].m_ei = ei0;
            m_E[ei0].m_ti.Append(i1);
          }
        }
      }
    }
  }

  return rc;
}

bool ON_Brep::ReadV1_LegacyShellStuff( ON_BinaryArchive& file )
{
  // read contents of TCODE_LEGACY_SHLSTUFF chunk
  ON_Workspace ws;
  int outer = 0;
  int facecnt = 0;
  int twincnt = 0;
  ON_BoundingBox shell_bbox;
  const int ti0 = m_T.Count();

  /* read flags */
  file.ReadInt(&outer);  
  file.ReadInt(&facecnt);  

  // read bounding box
  file.ReadPoint( shell_bbox.m_min );
  file.ReadPoint( shell_bbox.m_max );

  /* B-rep edge gluing info */
  file.ReadInt(&twincnt);
  short* glue = (twincnt > 0 ) ? (short*)ws.GetMemory(twincnt*sizeof(*glue)) : nullptr;
  if (twincnt > 0)
    file.ReadShort(twincnt,glue);

  bool rc = true;
  int fi;
  for ( fi = 0; rc && fi < facecnt; fi++ ) {
    rc = BeginRead3dmLEGACYSTUFF( file, TCODE_LEGACY_FAC );
    if ( rc ) {
      rc = BeginRead3dmLEGACYSTUFF( file, TCODE_LEGACY_FACSTUFF );
      if ( rc ) {
        rc = ReadV1_LegacyFaceStuff( file );
        if ( !file.EndRead3dmChunk() ) // end of TCODE_LEGACY_FACSTUFF chunk
          rc = false;
      }
      if ( !file.EndRead3dmChunk() ) // end of TCODE_LEGACY_FAC chunk
        rc = false;
    }
  }

  if ( twincnt > 0 ) {
    // twincnt = number of shared (inter-face) edges
    // glue[] = order 2 permutation of {0,....,twincnt-1}

    // set share_i[] = m_T[] indices of shared trims
    int si, ti;
    const int ti1 = m_T.Count();
    int* share_i = (int*)ws.GetMemory(twincnt*sizeof(*share_i));
    for ( ti = ti0, si = 0; ti < ti1 && si < twincnt; ti++ ) {
      if (m_T[ti].m_type != ON_BrepTrim::mated )
        continue;
      share_i[si++] = ti;
    }

    if ( si == twincnt ) {
      // glue seams
      for ( si = 0; si < twincnt; si++ ) {
        if ( glue[si] >= 0 && glue[si] < twincnt ) {
          const int i0 = share_i[si];
          const int i1 = share_i[glue[si]];
          // m_T[i0] and m_T[i1] use the same edge;
          const int ei0 = m_T[i0].m_ei;
          const int ei1 = m_T[i1].m_ei;
          if ( ei0 == -1 && ei1 >= 0 ) {
            m_T[i0].m_ei = ei1;
            m_E[ei1].m_ti.Append(i0);
          }
          else if ( ei1 == -1 && ei0 >= 0 ) {
            m_T[i1].m_ei = ei0;
            m_E[ei0].m_ti.Append(i1);
          }
        }
      }
    }
  }

  return rc;
}

bool ON_BinaryArchive::ReadV1_TCODE_LEGACY_CRV(
  ON_Object** ppObject,
  ON_3dmObjectAttributes* pAttributes
  )
{
  ON_Curve* curve = nullptr;
  bool rc = false;
  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  bool bHaveMat = false;

  Read3dmV1AttributesOrMaterial(pAttributes,nullptr,bHaveMat,TCODE_LEGACY_CRVSTUFF);

  if ( !BeginRead3dmBigChunk( &tcode, &big_value ) )
    return false;
  if ( tcode == TCODE_LEGACY_CRVSTUFF )
    curve = ReadV1_TCODE_LEGACY_CRVSTUFF(*this);
  rc = EndRead3dmChunk();
  if ( !curve )
    rc = false;
  else
    *ppObject = curve;
  return rc;
}


bool ON_BinaryArchive::ReadV1_TCODE_LEGACY_FAC(
  ON_Object** ppObject,
  ON_3dmObjectAttributes* pAttributes
  )
{
  // read V1 TCODE_LEGACY_FAC chunk
  bool bHaveMat = false;
  if ( !Read3dmV1AttributesOrMaterial(pAttributes,nullptr,bHaveMat,TCODE_LEGACY_FACSTUFF) )
    return false;
  if ( !BeginRead3dmLEGACYSTUFF( *this, TCODE_LEGACY_FACSTUFF ) )
    return false;
  ON_Brep* brep = new ON_Brep();
  bool rc = brep->ReadV1_LegacyFaceStuff( *this );
  if ( !EndRead3dmChunk() ) // end of TCODE_LEGACY_FACSTUFF chunk
    rc = false;

  if ( !rc ) {
    delete brep;
  }
  else {
    brep->SetVertices();
    brep->SetTrimIsoFlags();
    brep->SetTolsFromLegacyValues();
    *ppObject = brep;
  }

  return rc;
}

bool ON_BinaryArchive::ReadV1_TCODE_LEGACY_SHL(
  ON_Object** ppObject,
  ON_3dmObjectAttributes* pAttributes
  )
{
  // read v1 TCODE_LEGACY_SHL chunk
  bool bHaveMat = false;
  if ( !Read3dmV1AttributesOrMaterial(pAttributes,nullptr,bHaveMat,TCODE_LEGACY_SHLSTUFF) )
    return false;
  if ( !BeginRead3dmLEGACYSTUFF( *this, TCODE_LEGACY_SHLSTUFF ) )
    return false;
  ON_Brep* brep = new ON_Brep();
  bool rc = brep->ReadV1_LegacyShellStuff( *this );
  if ( !EndRead3dmChunk() ) // end of TCODE_LEGACY_SHLSTUFF chunk
    rc = false;

  if ( !rc ) {
    delete brep;
  }
  else {
    brep->SetVertices();
    brep->SetTrimIsoFlags();
    brep->SetTolsFromLegacyValues();
    *ppObject = brep;
  }

  return rc;
}


static
ON_NurbsCurve* ReadV1_RHINOIO_NURBS_CURVE_OBJECT_DATA( ON_BinaryArchive& file )
{
  // read TCODE_RHINOIO_OBJECT_DATA chunk that is contained in a
  // TCODE_RHINOIO_OBJECT_NURBS_CURVE chunk.  The TCODE_RHINOIO_OBJECT_DATA
  // chunk contains the definition of NURBS curves written by the 
  // old RhinoIO toolkit.
  ON_NurbsCurve* curve = 0;
  bool rc = false;
  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  int version, dim, is_rat, order, cv_count, flag, i;
  if ( !file.BeginRead3dmBigChunk( &tcode, &big_value ) )
    return nullptr;
  if ( tcode == TCODE_RHINOIO_OBJECT_DATA ) for (;;) {
    if ( !file.ReadInt(&version) )
      break;
    // int bReverse = version & 0x100;
    version &= 0xFFFFFEFF;
    if ( version != 100 && version != 101 )
      break;
    file.ReadInt(&dim);
    if ( dim < 1 )
      break;
    file.ReadInt(&is_rat);
    if ( is_rat < 0 || is_rat > 1 )
      break;
    file.ReadInt(&order);
    if ( order < 2 )
      break;
    file.ReadInt(&cv_count);
    if ( cv_count < order )
      break;
    file.ReadInt(&flag);
    if ( flag != 0 )
      break;

    curve = new ON_NurbsCurve(dim,is_rat,order,cv_count);
    if ( !file.ReadDouble( order+cv_count-2, curve->m_knot ) )
      break;
    int cvdim = is_rat ? dim+1 : dim;
    for ( i = 0; i < cv_count; i++ ) {
      if ( !file.ReadDouble( cvdim, curve->CV(i) ) )
        break;
    }
    if ( i < cv_count )
      break;
    rc = true;
    break;
  }
  if ( !file.EndRead3dmChunk() ) // end of TCODE_RHINOIO_OBJECT_DATA chunk
    rc = false;
  if ( !rc && curve ) {
    delete curve;
    curve = 0;
  }

  return curve;
}

static
ON_NurbsSurface* ReadV1_RHINOIO_NURBS_SURFACE_OBJECT_DATA( ON_BinaryArchive& file )
{
  // read TCODE_RHINOIO_OBJECT_DATA chunk that is contained in a
  // TCODE_RHINOIO_OBJECT_NURBS_SURFACE chunk.  The TCODE_RHINOIO_OBJECT_DATA
  // chunk contains the definition of NURBS surfaces written by the 
  // old RhinoIO toolkit.
  bool rc = false;
  ON_NurbsSurface* surface = 0;
  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  int version, dim, is_rat, order[2], cv_count[2], flag, i, j;

  if ( !file.BeginRead3dmBigChunk( &tcode, &big_value ) )
    return nullptr;
  if ( tcode == TCODE_RHINOIO_OBJECT_DATA ) for (;;) {
    if ( !file.ReadInt(&version) )
      break;
    // int bReverse = version & 0x100;
    version &= 0xFFFFFEFF;
    if ( version != 100 && version != 101 )
      break;
    file.ReadInt(&dim);
    if ( dim < 1 )
      break;
    file.ReadInt(&is_rat);
    if ( is_rat < 0 || is_rat > 1 )
      break;
    file.ReadInt(&order[0]);
    if ( order[0] < 2 )
      break;
    file.ReadInt(&order[1]);
    if ( order[1] < 2 )
      break;
    file.ReadInt(&cv_count[0]);
    if ( cv_count[0] < order[0] )
      break;
    file.ReadInt(&cv_count[1]);
    if ( cv_count[1] < order[1] )
      break;
    file.ReadInt(&flag);
    if ( flag != 0 )
      break;

    surface = new ON_NurbsSurface(dim,is_rat,order[0],order[1],cv_count[0],cv_count[1]);
    if ( !file.ReadDouble( order[0]+cv_count[0]-2, surface->m_knot[0] ) )
      break;
    if ( !file.ReadDouble( order[1]+cv_count[1]-2, surface->m_knot[1] ) )
      break;
    int cvdim = is_rat ? dim+1 : dim;
    for ( i = 0; i < cv_count[0]; i++ ) {
      for ( j = 0; j < cv_count[1]; j++ ) {
        if ( !file.ReadDouble( cvdim, surface->CV(i,j) ) )
          break;
      }
      if ( j < cv_count[1] )
        break;
    }
    if ( i < cv_count[0] )
      break;
    rc = true;
    break;
  }
  if ( !file.EndRead3dmChunk() ) // end of TCODE_RHINOIO_OBJECT_DATA
    rc = false;
  if ( !rc && surface ) {
    delete surface;
    surface = 0;
  }
  return surface;
}

bool ON_BinaryArchive::ReadV1_TCODE_RHINOIO_OBJECT_NURBS_CURVE(
  ON_Object** ppObject,
  ON_3dmObjectAttributes* pAttributes
  )
{
  // read contents of ReadV1_TCODE_RHINOIO_OBJECT_NURBS_CURVE chunk
  // written by v1 RhinoIO toolkit
  ON_NurbsCurve* curve = 0;
  bool rc = false;
  bool bHaveMat = false;
  
  // reads TCODE_RHINOIO_OBJECT_DATA header and nurbs curve definition
  curve = ReadV1_RHINOIO_NURBS_CURVE_OBJECT_DATA(*this);

  if ( curve ) {
    *ppObject = curve;
    rc = true;
    Read3dmV1AttributesOrMaterial(pAttributes,nullptr,bHaveMat,TCODE_RHINOIO_OBJECT_END);
  }

  return rc;
}

bool ON_BinaryArchive::ReadV1_TCODE_RHINOIO_OBJECT_NURBS_SURFACE(
  ON_Object** ppObject,
  ON_3dmObjectAttributes* pAttributes
  )
{
  // read contents of TCODE_RHINOIO_OBJECT_NURBS_SURFACE chunk
  // written by v1 RhinoIO toolkit
  bool bHaveMat = false;
  bool rc = false;
  ON_NurbsSurface* surface = 0;

  surface = ReadV1_RHINOIO_NURBS_SURFACE_OBJECT_DATA( *this );

  if ( surface ) {
    *ppObject = surface;
    rc = true;
    Read3dmV1AttributesOrMaterial(pAttributes,nullptr,bHaveMat,TCODE_RHINOIO_OBJECT_END);
  }

  return rc;
}

static
ON_Curve* ReadV1_RHINOIO_BREP_CURVE( ON_BinaryArchive& file )
{
  ON_Curve* curve = nullptr;
  ON_PolyCurve* pcurve = nullptr;
  ON_NurbsCurve* nurbs_curve = nullptr;
  int segment_index, segment_count = 0;
  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  
  if ( !file.ReadInt(&segment_count) )
    return nullptr;
  if ( segment_count < 1 )
    return nullptr;

  for ( segment_index = 0; segment_index < segment_count; segment_index++ ) {
    if ( !file.BeginRead3dmBigChunk(&tcode,&big_value) )
      break;
    if ( tcode == TCODE_RHINOIO_OBJECT_NURBS_CURVE ) {
      nurbs_curve = ReadV1_RHINOIO_NURBS_CURVE_OBJECT_DATA( file );
    }
    if ( !file.EndRead3dmChunk() )
      break;
    if ( !nurbs_curve )
      break;
    if ( segment_index == 0 ) {
      curve = nurbs_curve;
      nurbs_curve = 0;
    }
    else {
      if ( segment_index == 1 ) {
        pcurve = new ON_PolyCurve();
        pcurve->Append(curve);
        curve = pcurve;
      }
      pcurve->Append(nurbs_curve);
      nurbs_curve = nullptr;
    }
  }

  if ( segment_index < segment_count ) {
    if ( nurbs_curve ) {
      delete nurbs_curve;
      nurbs_curve = 0;
    }
    if ( curve ) {
      delete curve;
      curve = 0;
    }
  }
  return curve;
}

bool ON_BinaryArchive::ReadV1_TCODE_RHINOIO_OBJECT_BREP(
  ON_Object** ppObject,
  ON_3dmObjectAttributes* pAttributes
  )
{
  ON_3dPoint m_oldTrim_mP[2];
  bool bHaveMat = false;
  bool rc = false;
  ON_Brep* brep = 0;
  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  if ( !BeginRead3dmBigChunk( &tcode, &big_value ) )
    return false;
  if ( tcode == TCODE_RHINOIO_OBJECT_DATA ) for (;;) {
    int version = -1;
    int sz, i, j;
    double tol2d, tol3d;
    if ( !ReadInt( &version ) ) 
      break; // serialization version
    // version = 100 means the b-rep was written by the RhinoIO toolkit
    // version = 101 means the b-rep was written by Rhino 1.0
    if ( version != 100 && version != 101 ) {
      return false;
    }

    brep = new ON_Brep();

    // 2d trimming curves
    if ( !ReadInt( &sz ) )
      break;
    if ( sz < 1 ) {
      break;
    }
    brep->m_C2.Reserve(sz);
    for ( i = 0; i < sz; i++ ) {
      ON_Curve* curve = ReadV1_RHINOIO_BREP_CURVE( *this );
      if ( !curve )
        break;
      brep->m_C2.Append(curve);
    }
    if ( i < sz )
      break;

    // 3d trimming curves
    if ( !ReadInt( &sz ) )
      break;
    if ( sz < 1 ) {
      break;
    }
    brep->m_C3.Reserve(sz);
    for ( i = 0; i < sz; i++ ) {
      ON_Curve* curve = ReadV1_RHINOIO_BREP_CURVE( *this );
      if ( !curve )
        break;
      brep->m_C3.Append(curve);
    }
    if ( i < sz )
      break;

    // 3d untrimmed surfaces
    if ( !ReadInt( &sz ) )
      break;
    if ( sz < 1 ) {
      break;
    }
    brep->m_S.Reserve(sz);
    for ( i = 0; i < sz; i++ ) {
      ON_NurbsSurface* surface = 0;
      tcode = 0;
      big_value = 0;
      if ( !BeginRead3dmBigChunk(&tcode,&big_value) )
        break;
      if ( tcode == TCODE_RHINOIO_OBJECT_NURBS_SURFACE ) {
        surface = ReadV1_RHINOIO_NURBS_SURFACE_OBJECT_DATA( *this );
      }
      if ( !EndRead3dmChunk() )
        break;
      if ( !surface )
        break;
      brep->m_S.Append(surface);
    }
    if ( i < sz )
      break;

    // vertices
    ReadInt( &sz );
    brep->m_V.Reserve(sz);
    for ( i = 0; i < sz; i++ ) {
      ON_BrepVertex& vertex = brep->NewVertex();
      if ( !ReadInt( &vertex.m_vertex_index ) ) break;
      if ( !ReadPoint( vertex.point ) ) break;
      if ( !ReadArray( vertex.m_ei ) ) break;
      if ( !ReadDouble( &vertex.m_tolerance ) ) break;
    }
    if ( i < sz )
      break;

    // edges
    ReadInt( &sz );
    brep->m_E.Reserve(sz);
    for ( i = 0; i < sz; i++ ) 
    {
      ON_Interval proxy_domain;
      ON_BrepEdge& edge = brep->NewEdge();
      if ( !ReadInt( &edge.m_edge_index ) ) break;
      if ( !ReadInt( &edge.m_c3i ) ) break;
      if ( !ReadInterval( proxy_domain ) ) break;
      edge.SetProxyCurveDomain(proxy_domain);
      if ( !ReadInt( 2, edge.m_vi ) ) break;
      if ( !ReadArray( edge.m_ti ) ) break;
      if ( !ReadDouble( &edge.m_tolerance ) ) break;
    }
    if ( i < sz )
      break;

    // trims
    ReadInt( &sz );
    brep->m_T.Reserve(sz);
    for ( i = 0; i < sz; i++ ) {
      ON_BrepTrim& trim = brep->NewTrim();
      if ( !ReadInt( &trim.m_trim_index ) ) break;
      if ( !ReadInt( &trim.m_c2i ) ) break;
      ON_Interval d;
      if ( !ReadInterval( d ) ) 
        break;
      trim.SetProxyCurve(nullptr,d);
      if ( !ReadInt( &trim.m_ei ) ) break;
      if ( !ReadInt( 2, trim.m_vi ) ) break;
      j = trim.m_bRev3d;
      if ( !ReadInt( &j ) ) break;
      trim.m_bRev3d = (j!=0);
      if ( !ReadInt( &j ) ) break;
      switch(j) {
      case 1: trim.m_type = ON_BrepTrim::boundary; break;
      case 2: trim.m_type = ON_BrepTrim::mated; break;
      case 3: trim.m_type = ON_BrepTrim::seam; break;
      case 4: trim.m_type = ON_BrepTrim::singular; break;
      }
      if ( !ReadInt( &j ) ) break; // legacy iso flag - ignore and recaluate
      if ( !ReadInt( &trim.m_li ) ) break;
      if ( !ReadDouble( 2, trim.m_tolerance ) ) break;
      if ( !ReadPoint( m_oldTrim_mP[0] ) ) break;
      if ( !ReadPoint( m_oldTrim_mP[1] ) ) break;
      if ( !ReadDouble( &tol2d ) ) break;
      if ( !ReadDouble( &tol3d ) ) break;
    }
    if ( i < sz )
      break;

    // loops
    ReadInt( &sz );
    brep->m_L.Reserve(sz);
    for ( i = 0; i < sz; i++ ) {
      ON_BrepLoop& loop = brep->NewLoop(ON_BrepLoop::unknown);
      if ( !ReadInt( &loop.m_loop_index ) ) break;
      if ( !ReadArray( loop.m_ti ) ) break;
      if ( !ReadInt( &j ) ) break;
      switch (j) {
      case 1: loop.m_type = ON_BrepLoop::outer; break;
      case 2: loop.m_type = ON_BrepLoop::inner; break;
      case 3: loop.m_type = ON_BrepLoop::slit; break;
      }
      if ( !ReadInt( &loop.m_fi ) ) break;
    }
    if ( i < sz )
      break;

    // faces
    ReadInt( &sz );
    brep->m_F.Reserve(sz);
    for ( i = 0; i < sz; i++ ) {
      ON_BrepFace& face = brep->NewFace();
      if ( !ReadInt( &face.m_face_index ) ) break;
      if ( !ReadArray( face.m_li ) ) break;
      if ( !ReadInt( &face.m_si ) ) break;
      int k = face.m_bRev;
      if ( !ReadInt( &k ) ) break;
      face.m_bRev = (k!=0);
    }
    if ( i < sz )
      break;

    // bounding box
    {
      ON_BoundingBox bbox;
      if ( !ReadPoint( bbox.m_min ) ) break;
      if ( !ReadPoint( bbox.m_max ) ) break;
    }

    rc = true;
    break;
  }
  if ( !EndRead3dmChunk() )
    rc = false;
  if ( rc && brep ) {
    brep->SetTrimIsoFlags();
    *ppObject = brep;
  }
  else {
    if ( brep )
      delete brep;
    rc = false;
  }

  if ( rc && brep ) {
    Read3dmV1AttributesOrMaterial(pAttributes,nullptr,bHaveMat,TCODE_RHINOIO_OBJECT_END);
  }

  return rc;
}

int
ON_BinaryArchive::Read3dmV1Object( 
  ON_Object** ppObject,                // object is returned here
  ON_3dmObjectAttributes* pAttributes, // optional - object attributes 
  unsigned int object_filter           // optional filter made by or-ing object_type bits
  )
{
  int rc = 0;
  // returns -1: failure
  //          0: end of geometry table
  //          1: success
  //          2: skipped filtered objects

  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  // reads NURBS, point, and mesh objects
  for (;;)
  {
    tcode = 0;
    big_value = 0;
    if (!BeginRead3dmBigChunk(&tcode, &big_value)) {
      rc = 0; // at the end of the file
      break;
    }
    switch (tcode)
    {

    case  TCODE_TEXT_BLOCK:
    case  TCODE_ANNOTATION_LEADER:
    case  TCODE_LINEAR_DIMENSION:
    case  TCODE_ANGULAR_DIMENSION:
    case  TCODE_RADIAL_DIMENSION:
      if (0 != (ON::annotation_object & object_filter))
      {
        if (ReadV1_TCODE_ANNOTATION(tcode, ppObject, pAttributes))
          rc = 1;
        else
          rc = -1;
      }
      else
      {
        rc = 2;
      }
      break;

    case TCODE_RH_POINT:
      // v1 3d point
      if (0 != (ON::point_object & object_filter)) {
        if (ReadV1_TCODE_RH_POINT(ppObject, pAttributes))
          rc = 1;
        else
          rc = -1;
      }
      else {
        rc = 2;
      }
      break;

    case TCODE_MESH_OBJECT:
      // v1 mesh
      if (0 != (ON::mesh_object & object_filter)) {
        if (ReadV1_TCODE_MESH_OBJECT(ppObject, pAttributes))
          rc = 1;
        else
          rc = -1;
      }
      else {
        rc = 2;
      }
      break;

    case TCODE_LEGACY_SHL:
      // v1 polysurface
      if (0 != (ON::mesh_object & object_filter)) {
        if (ReadV1_TCODE_LEGACY_SHL(ppObject, pAttributes))
          rc = 1;
        else
          rc = -1;
      }
      else {
        rc = 2;
      }
      break;

    case TCODE_LEGACY_FAC:
      // v1 trimmed surface
      if (0 != (ON::mesh_object & object_filter)) {
        if (ReadV1_TCODE_LEGACY_FAC(ppObject, pAttributes))
          rc = 1;
        else
          rc = -1;
      }
      else {
        rc = 2;
      }
      break;

    case TCODE_LEGACY_CRV:
      // v1 curve
      if (0 != (ON::mesh_object & object_filter)) {
        if (ReadV1_TCODE_LEGACY_CRV(ppObject, pAttributes))
          rc = 1;
        else
          rc = -1;
      }
      else {
        rc = 2;
      }
      break;

    case TCODE_RHINOIO_OBJECT_NURBS_CURVE:
      // old Rhino I/O toolkit nurbs curve
      if (0 != (ON::mesh_object & object_filter)) {
        if (ReadV1_TCODE_RHINOIO_OBJECT_NURBS_CURVE(ppObject, pAttributes))
          rc = 1;
        else
          rc = -1;
      }
      else {
        rc = 2;
      }
      break;

    case TCODE_RHINOIO_OBJECT_NURBS_SURFACE:
      // old Rhino I/O toolkit nurbs surface
      if (0 != (ON::mesh_object & object_filter)) {
        if (ReadV1_TCODE_RHINOIO_OBJECT_NURBS_SURFACE(ppObject, pAttributes))
          rc = 1;
        else
          rc = -1;
      }
      else {
        rc = 2;
      }
      break;

    case TCODE_RHINOIO_OBJECT_BREP:
      // old Rhino I/O toolkit nurbs brep
      if (0 != (ON::mesh_object & object_filter)) {
        if (ReadV1_TCODE_RHINOIO_OBJECT_BREP(ppObject, pAttributes))
          rc = 1;
        else
          rc = -1;
      }
      else {
        rc = 2;
      }
      break;
    }

    if (!EndRead3dmChunk())
      break;

    if (1 == rc && nullptr != pAttributes && ON_nil_uuid == pAttributes->m_uuid)
      pAttributes->m_uuid = ON_CreateId(); // v1 files did not have ids.

    if (rc == 1 || rc == -1)
      break;


  }

  return rc;
}

#if 1
class ON_OBSOLETE_CCustomMeshUserData : public ON_UserData
{
	ON_OBJECT_DECLARE(ON_OBSOLETE_CCustomMeshUserData);
public:
  ON_OBSOLETE_CCustomMeshUserData();
	~ON_OBSOLETE_CCustomMeshUserData();
	bool GetDescription( ON_wString& ) override;
  bool Read(ON_BinaryArchive& binary_archive) override;
  bool m_bInUse;
  ON_MeshParameters m_mp;
};

ON_OBJECT_IMPLEMENT(ON_OBSOLETE_CCustomMeshUserData, ON_UserData, "69F27695-3011-4FBA-82C1-E529F25B5FD9");

ON_OBSOLETE_CCustomMeshUserData::ON_OBSOLETE_CCustomMeshUserData()
{
	m_userdata_copycount = 0;
	m_userdata_uuid = ON_CLASS_ID(ON_OBSOLETE_CCustomMeshUserData);
  m_application_uuid = ON_nil_uuid;
  m_bInUse = false;
}

ON_OBSOLETE_CCustomMeshUserData::~ON_OBSOLETE_CCustomMeshUserData()
{
}

bool ON_OBSOLETE_CCustomMeshUserData::Read(ON_BinaryArchive& ba)
{
  int i = 0;
  if ( !ba.ReadInt( &i ) )
    return false;    
  if( !ba.ReadBool( &m_bInUse ) )
    return false;    
  return m_mp.Read( ba );
}

bool ON_OBSOLETE_CCustomMeshUserData::GetDescription( ON_wString& s )
{
	s = "OBSOLETE CustomMeshUserData";
	return true;
}
#endif

int ON_BinaryArchive::Read3dmModelGeometry(
  class ON_ModelGeometryComponent** model_geometry,
  unsigned int object_filter
  )
{
  bool bManageGeometry = false;
  bool bManageAttributes = false;
  return Read3dmModelGeometryForExperts(
    bManageGeometry,
    bManageAttributes,
    model_geometry,
    object_filter
  );
}

int ON_BinaryArchive::Read3dmModelGeometryForExperts(
  bool bManageGeometry,
  bool bManageAttributes,
  class ON_ModelGeometryComponent** model_geometry,
  unsigned int object_filter
)
{
  if ( nullptr != model_geometry )
    *model_geometry = nullptr;
  ON_Object* p = nullptr;
  ON_3dmObjectAttributes* attributes = new ON_3dmObjectAttributes();
  int rc = Read3dmObject(&p, attributes, object_filter);
  ON_Geometry* geometry = ON_Geometry::Cast(p);
  if (1 == rc && nullptr != geometry)
  {
    *model_geometry = ON_ModelGeometryComponent::CreateForExperts(bManageGeometry,geometry,bManageAttributes,attributes,nullptr);
  }
  else
  {
    delete p;
    delete attributes;
  }
  return rc;
}

int ON_BinaryArchive::Read3dmObject( 
  ON_Object** ppObject,                // object is returned here
  ON_3dmObjectAttributes* pAttributes, // optional - object attributes 
  unsigned int object_filter           // optional filter made by or-ing object_type bits
  )
{
  if ( pAttributes )
    pAttributes->Default();

  if ( false == Read3dmTableRecord(ON_3dmArchiveTableType::object_table, (void**)ppObject))
    return 0;

  if ( 0 == object_filter ) // default filter (0) reads every object
    object_filter = 0xFFFFFFFF;

  // returns -1: failure
  //          0: end of geometry table
  //          1: success
  //          2: skipped filtered objects
  //          3: skipped new object (object's class UUID wasn't found in class list)
  int rc = -1;

  if ( m_3dm_version == 1 ) {
    rc = Read3dmV1Object(ppObject,pAttributes,object_filter);
  }
  else 
  {
    ON__UINT32 tcode = 0;
    ON__INT64 length_TCODE_OBJECT_RECORD = 0;
    ON__INT64 value_TCODE_OBJECT_RECORD_TYPE = 0;
    ON__INT64 length_TCODE_OBJECT_RECORD_ATTRIBUTES = 0;
    if ( BeginRead3dmBigChunk( &tcode, &length_TCODE_OBJECT_RECORD ) ) 
    {
      if ( tcode == TCODE_OBJECT_RECORD ) 
      {
        Internal_Increment3dmTableItemCount();
        if (BeginRead3dmBigChunk( &tcode, &value_TCODE_OBJECT_RECORD_TYPE )) 
        {
          if ( tcode != TCODE_OBJECT_RECORD_TYPE ) {
            rc = -1;
            ON_ERROR("ON_BinaryArchive::Read3dmObject() - missing TCODE_OBJECT_RECORD_TYPE chunk.");
          }
          else if ( 0 != value_TCODE_OBJECT_RECORD_TYPE && 0 == (value_TCODE_OBJECT_RECORD_TYPE & object_filter) )
            rc = 2; // skip reading this object
          else
            rc = 1; // need to read this object

          if ( !EndRead3dmChunk() )
            rc = -1;

          if ( 1 == rc )
          {
            switch(ReadObject(ppObject))
            {
            case 1:
              rc = 1; // successfully read this object
              break;
            case 3:
              rc = 3; // skipped object - assume it's just a newer object than this code reads
              break;
            default:
              rc = -1; // serious failure
              break;
            }
          }
        }
        else
          rc = -1;
      }
      else if ( tcode != TCODE_ENDOFTABLE ) {
        ON_ERROR("ON_BinaryArchive::Read3dmObject() - corrupt object table");
        rc = -1;
      }
      else
        rc = 0;

      while(rc==1)
      {
        tcode = 0;
        if (!BeginRead3dmBigChunk( &tcode, &length_TCODE_OBJECT_RECORD_ATTRIBUTES )) {
          rc = -1;
          break;
        }
        if ( tcode == TCODE_OBJECT_RECORD_ATTRIBUTES ) 
        {
          if ( 0 != pAttributes )
          {
            if ( !pAttributes->Read( *this ) )
              rc = -1;
          }
        }
        else if ( tcode == TCODE_OBJECT_RECORD_ATTRIBUTES_USERDATA )
        {
          if ( 0 != pAttributes )
          {
            // 19 October 2004
            //   Added support for saving user data on object attributes
            if ( !ReadObjectUserData(*pAttributes))
              rc = -1;
            else
            {
#if 1
              // 3 March 2011 - convert obsolete user data
              ON_OBSOLETE_CCustomMeshUserData* ud = ON_OBSOLETE_CCustomMeshUserData::Cast(pAttributes->GetUserData(ON_CLASS_ID(ON_OBSOLETE_CCustomMeshUserData)));
              if ( ud )
              {
                ud->m_mp.SetCustomSettingsEnabled(ud->m_bInUse);
                pAttributes->SetCustomRenderMeshParameters(ud->m_mp);
                delete ud;
              }

              //Strip out the $temp_object$ key left over from Block edit
              auto* sl = ON_UserStringList::Cast(pAttributes->GetUserData(ON_CLASS_ID(ON_UserStringList)));
              if (sl)
              {
                sl->SetUserString(L"$temp_object$", nullptr);
              }
#endif
            }
          }
        }

        if ( !EndRead3dmChunk() ) 
        {
          rc = -1;
        }
        if ( tcode == TCODE_OBJECT_RECORD_END )
          break;
      }

      if ( !EndRead3dmChunk() )
        rc = -1;
    }
  }

  if ( 1 == rc 
    && nullptr != ppObject
    && nullptr != *ppObject
    && nullptr != pAttributes
    )
  {
    if (ON_nil_uuid == pAttributes->m_uuid)
    {
      // some older files are missing ids
      // Modern times require unique object ids.
      pAttributes->m_uuid = ON_CreateId();
    }
    else if ( false == Manifest().IdIsAvailable(pAttributes->m_uuid) )
    {
      // And some files contain objects with duplicate ids.
      ON_ERROR("pAttributes->m_uuid is in use. Assigning new id.");
      pAttributes->m_uuid = ON_CreateId();
    }

    // In rare cases one object must be converted into another.
    // Examples include reading obsolete objects and converting them into their 
    // current counterpart, converting WIP objects into a proxy for a commercial build, 
    // and converting a proxy object into a WIP object for a WIP build.
    ON_Object* updated_object = Internal_ConvertObject(*ppObject, pAttributes);

    if (nullptr != updated_object && updated_object != *ppObject)
    {
      delete *ppObject;
      *ppObject = updated_object;
    }

    Internal_Read3dmLightOrGeometryUpdateManifest(
      ON_ModelComponent::Type::ModelGeometry,
      pAttributes->m_uuid,
      ON_UNSET_INT_INDEX,
      pAttributes->m_name
      );
  }

  return rc;
}

bool ON_BinaryArchive::EndRead3dmObjectTable()
{
  bool rc = EndRead3dmTable( TCODE_OBJECT_TABLE );

  if ( 0 != m_V1_layer_list )
  {
    struct ON__3dmV1LayerIndex* next = m_V1_layer_list;
    m_V1_layer_list = 0;
    for ( int i = 0; 0 != next && i < 1000; i++ )
    {
      struct ON__3dmV1LayerIndex* p = next;
      next = p->m_next;
      onfree(p);
    }
  }

  return rc;
}

bool ON_BinaryArchive::BeginWrite3dmUserTable( const ON_UUID& usertable_uuid )
{
  return BeginWrite3dmUserTable(usertable_uuid, false, 0, 0 );
}

bool ON_BinaryArchive::BeginWrite3dmUserTable(
    ON_UUID plugin_id,
    bool bSavingGoo,
    int goo_3dm_version,
    unsigned int goo_opennurbs_version
    )
{
  if ( m_3dm_active_table != ON_3dmArchiveTableType::Unset ) 
  {
    ON_ERROR("ON_BinaryArchive::BeginWrite3dmUserTable() - m_active_table != no_active_table");
  }
  if ( !ON_UuidCompare( &ON_nil_uuid, &plugin_id ) ) {
    ON_ERROR("ON_BinaryArchive::BeginWrite3dmUserTable() - nil usertable_uuid not permitted.");
    return false;
  }

  if (false == ArchiveContains3dmTable(ON_3dmArchiveTableType::user_table))
    return false;
  
  if (false == ShouldSerializeUserDataItem(plugin_id, plugin_id))
    return false;

  if ( bSavingGoo )
  {
    if ( goo_3dm_version <= 3 )
      return false;
    if ( goo_opennurbs_version < 200601010 )
      return false;
    if ( goo_3dm_version >= 50 && Archive3dmVersion() < 50 )
    {
      // goo with 8 byte chunk lengths cannot be saved 
      // in files expecting 4 byte chunk lengths.
      return false;
    }
  }
  else
  {
    goo_3dm_version = Archive3dmVersion();
    goo_opennurbs_version = ArchiveOpenNURBSVersion();
  }

  bool rc = BeginWrite3dmTable( TCODE_USER_TABLE);
  if (rc) {
    rc = BeginWrite3dmChunk( TCODE_USER_TABLE_UUID, 0 );
    if (rc)
    {
      rc = WriteUuid( plugin_id );
      if (rc)
      {
        // The TCODE_USER_TABLE_RECORD_HEADER chunk was added in 
        // version 200910190 to contain the archive and opennurbs
        // version the plug-in used when writing the file.
        // This information is needed so "goo" can be correctly
        // read.
        rc = BeginWrite3dmChunk( TCODE_USER_TABLE_RECORD_HEADER, 1, 0 );
        if ( rc )
        {
          if (rc) rc = WriteBool(bSavingGoo);
          if (rc) rc = WriteInt(goo_3dm_version);
          unsigned int opennurbs_version_to_write = ON_BinaryArchive::ArchiveOpenNURBSVersionToWrite(goo_3dm_version, goo_opennurbs_version);
          if (rc)
            rc = WriteInt(opennurbs_version_to_write);
          if ( !EndWrite3dmChunk() )
            rc = false;
        }
      }
      if ( !EndWrite3dmChunk() )
        rc = false;
    }
    if (rc) {
      rc = BeginWrite3dmChunk( TCODE_USER_RECORD, 0 );
    }
    if ( !rc ) {
      EndWrite3dmTable( TCODE_USER_TABLE);
    }
  }
  return rc;
}

bool ON_BinaryArchive::Write3dmAnonymousUserTableRecord( 
    ON_UUID plugin_id,
    int goo_3dm_version,
    unsigned int goo_opennurbs_version,
    const ON_3dmGoo& goo
    )
{
  if ( ON_UuidIsNil(plugin_id) )
    return false;
  
  if (false == ShouldSerializeUserDataItem(plugin_id, plugin_id))
    return false;

  if ( goo_3dm_version <= 3 )
    return false;
  if (   !ON_VersionNumberIsValid(goo_opennurbs_version) 
      && !ON_VersionNumberIsYearMonthDateFormat(goo_3dm_version,goo_opennurbs_version)
     )
  {
    return false;
  }
  if ( goo.m_typecode != TCODE_USER_RECORD )
    return false;
  if ( 0 == goo.m_value )
    return false;
  if ( 0 == goo.m_goo )
    return false;
  bool bSavingGoo = true;
  if ( !BeginWrite3dmUserTable( plugin_id, bSavingGoo, goo_3dm_version, goo_opennurbs_version ) )
    return false;
  bool rc = WriteByte( goo.m_value, goo.m_goo );
  if ( !EndWrite3dmUserTable() )
    rc = false;
  return rc;
}


bool ON_BinaryArchive::Write3dmAnonymousUserTable( const ON_3dmGoo& goo )
{
  bool rc = false;
  const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
  if ( !c || c->m_typecode != TCODE_USER_RECORD ) {
    ON_ERROR("ON_BinaryArchive::Write3dmAnonymousUserTable() - active chunk not a TCODE_USER_RECORD.");
    rc = false;
  }
  else if ( goo.m_typecode != TCODE_USER_RECORD ) {
    ON_ERROR("ON_BinaryArchive::Write3dmAnonymousUserTable() - goo chunk not a TCODE_USER_RECORD.");
    rc = false;
  }
  else {
    rc = ( goo.m_value > 0 ) ? WriteByte( goo.m_value, goo.m_goo ) : true;
  }
  return rc;
}


bool ON_BinaryArchive::EndWrite3dmUserTable()
{
  bool rc = false;
  const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
  if ( c && c->m_typecode == TCODE_USER_RECORD ) {
    rc = EndWrite3dmChunk();
  }
  else {
    ON_ERROR("ON_BinaryArchive::EndWrite3dmUserTable() - not in a TCODE_USER_RECORD chunk.");
    rc = false;
  }
  if ( !EndWrite3dmTable(TCODE_USER_TABLE) )
    rc = false;
  return rc;
}

bool ON_BinaryArchive::BeginRead3dmUserTable(
    ON_UUID& plugin_id,
    bool* bLastSavedAsGoo,
    int* archive_3dm_version,
    unsigned int* archive_opennurbs_version
    )
{
  bool bReadArchiveInfo = false;
  if ( bLastSavedAsGoo )
    *bLastSavedAsGoo = false;
  if ( archive_3dm_version )
    *archive_3dm_version = 0;
  if ( archive_opennurbs_version )
    *archive_opennurbs_version = 0;

  if ( m_3dm_version == 1 )
    return false;

  bool rc = BeginRead3dmTable( TCODE_USER_TABLE );

  // Do not add calls to EmergencyFindTable() here.
  // BeginRead3dmTable( TCODE_USER_TABLE ) returns
  // false when there are no user tables and that
  // is a common situation.

  if ( rc ) 
  {
    // read table id
    ON__UINT32 tcode = 0;
    ON__INT64 big_value = 0;
    if (rc) rc = BeginRead3dmBigChunk( &tcode, &big_value );
    if (rc)
    {
      if ( tcode != TCODE_USER_TABLE_UUID ) 
      {
        ON_ERROR("ON_BinaryArchive::BeginRead3dmUserTable() - missing user table UUID");
        rc = false;
      }
      else 
      {
        rc = ReadUuid( plugin_id );

        // Version 200910190 of OpenNURBS began writing a TCODE_USER_TABLE_RECORD_HEADER
        // section immediately after the uuid.  This was possible because the uuid
        // was wrapped in a TCODE_USER_TABLE_UUID chunk.  The TCODE_USER_TABLE_RECORD_HEADER
        // contains information that let's us determine what version of Rhino and
        // opennurbs wrote the user table.  We need to know this because "goo"
        // can have chunks with 4 byte lengths embedded in a file with 8 byte
        // chunk lengths.  If this information is missing, then we know the "goo"
        // must have 4 byte chunk lengths and we assume it is from a V4 file.
        //
        // 37 + SizeofChunkLength() = 
        //      16 bytes of uuid
        //    + 4 bytes of TCODE_USER_TABLE_RECORD_HEADER typecode
        //    + SizeofChunkLength() TCODE_USER_TABLE_RECORD_HEADER chunk length
        //    + 1 byte of bSlastSavedAsGoo bool
        //    + 4 bytes of archive_3dm_version
        //    + 4 bytes of archive_opennurbs_version
        //    + 4 bytes of TCODE_USER_TABLE_RECORD_HEADER chunk crc
        //    + 4 bytes of TCODE_USER_TABLE_UUID chunk crc
        const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
        if ( rc 
             && ArchiveOpenNURBSVersion() >= 200910190 
             && 0 != c
             && TCODE_USER_TABLE_UUID == c->m_typecode
             && c->Length() >= 45 + SizeofChunkLength()
           )
        {
          int major_chunk_version = 0;
          int minor_chunk_version = 0;
          rc = BeginRead3dmChunk(TCODE_USER_TABLE_RECORD_HEADER,&major_chunk_version,&minor_chunk_version);
          if (rc)
          {
            bReadArchiveInfo = true;
            bool b = true;
            int arch_ver = 0;
            unsigned int on_ver = 0;
            rc = ReadBool(&b);
            if ( rc && bLastSavedAsGoo )
              *bLastSavedAsGoo = b;
            if (rc)
              rc = ReadInt(&arch_ver);
            if (rc && archive_3dm_version)
              *archive_3dm_version = arch_ver;
            if (rc)
              rc = ReadInt(&on_ver);
            if (rc && archive_opennurbs_version)
              *archive_opennurbs_version = on_ver;
            if ( !EndRead3dmChunk() )
              rc = false;
          }
        }
      }
      if ( !EndRead3dmChunk() )
        rc = false;
    }

    tcode = 0;
    big_value = 0;
    if (rc) rc = BeginRead3dmBigChunk( &tcode, &big_value );
    if (rc) {
      if ( tcode != TCODE_USER_RECORD ) {
        ON_ERROR("ON_BinaryArchive::BeginRead3dmUserTable() - missing user table TCODE_USER_RECORD chunk.");
        EndRead3dmChunk();
        rc = false;
      }
    }

    if (!rc)
      EndRead3dmTable(TCODE_USER_TABLE);

    if ( rc && !bReadArchiveInfo )
    {
      // If the file we are reading is V4 or an early V5 file, then use the 
      // version numbers from the file.  Otherwise, assume the goo is from
      // an early V5 file.  All we know for sure is that the chunk lengths
      // in the user table are 4 bytes.
      if ( Archive3dmVersion() < 50 )
      {
        if (archive_3dm_version)
          *archive_3dm_version = Archive3dmVersion();
        if (archive_opennurbs_version)
          *archive_opennurbs_version = ArchiveOpenNURBSVersion();
      }
      else
      {
        // Assume the goo is from an early V5 file.  
        // All we know for sure is that the chunk lengths
        // in the user table are 4 bytes.
        if (archive_3dm_version) 
          *archive_3dm_version = 5;
        if (archive_opennurbs_version) 
          *archive_opennurbs_version = 200910180;
      }
    }
  }


  return rc;
}

bool ON_BinaryArchive::Read3dmAnonymousUserTable( 
    int archive_3dm_version,
    unsigned int archive_opennurbs_version,
    ON_3dmGoo& goo
    )
{
  if ( 0 == archive_3dm_version )
  {
    if ( Archive3dmVersion() < 50 )
    {
      archive_3dm_version = Archive3dmVersion();
      archive_opennurbs_version = ArchiveOpenNURBSVersion();
    }
    else
    {
      // recent version with 4 byte chunk lengths.
      archive_3dm_version = 5;
      archive_opennurbs_version = 200910190;
    }
  }
  bool rc = Read3dmGoo( goo );
  if (rc && goo.m_typecode != TCODE_USER_RECORD ) {
    ON_ERROR("ON_BinaryArchive::Read3dmAnonymousUserTable() do not read a TCODE_USER_RECORD chunk.");
    rc = false;
  }
  return rc;
}

bool ON_BinaryArchive::EndRead3dmUserTable()
{
  if ( m_chunk.Count() != 2 ) {
    ON_ERROR("ON_BinaryArchive::EndRead3dmUserTable() m_chunk.Count() != 2");
    return false;
  }
  const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
  if ( 0 == c || c->m_typecode != TCODE_USER_RECORD ) {
    ON_ERROR("ON_BinaryArchive::EndRead3dmTable() m_chunk.Last()->typecode != TCODE_USER_RECORD");
    return false;
  }


  // end of TCODE_USER_RECORD chunk
  // Suppress the partially read chunk warning because plug-in IO
  // is too upredictable for this warning to be helpful.
  bool rc = EndRead3dmChunk(true); 

  if (rc) {
    // end of table chunk
    unsigned int tcode = 0;
    ON__INT64 big_value = -1;
    rc = BeginRead3dmBigChunk( &tcode, &big_value );
    if ( rc ) {
      if ( tcode != TCODE_ENDOFTABLE ) {
        ON_ERROR("ON_BinaryArchive::EndRead3dmTable() missing TCODE_ENDOFTABLE marker.");
      }
      if ( !EndRead3dmChunk() )
        rc = false;
    }
  }

  if ( !EndRead3dmTable(TCODE_USER_TABLE) )
    rc = false;
  return rc;
}

bool ON_BinaryArchive::Write3dmEndMark()
{
  Flush();
  if ( m_chunk.Count() != 0 ) {
    ON_ERROR( "ON_BinaryArchive::WriteEndMark() called with unfinished chunks.\n" );
    return false;
  }

  if (false == Begin3dmTable(ON::archive_mode::write3dm,ON_3dmArchiveTableType::end_mark))
    return false;

  ON__UINT64 length = CurrentPosition(); // since no chunks are unfinished, everything
                                  // has been committed to disk in either
                                  // write mode.
  bool rc = BeginWrite3dmChunk( TCODE_ENDOFFILE, 0 );
  if ( rc ) 
  {    
    size_t sizeof_chunk_length = SizeofChunkLength();
    size_t sizeoffile_length = (8==SizeofChunkLength()) ? 8 : 4;
    length += (4 + sizeof_chunk_length + sizeoffile_length );
    rc = WriteEOFSizeOfFile(length);
    if ( !EndWrite3dmChunk() )
      rc = false;
  }
  Flush();

  return End3dmTable(ON_3dmArchiveTableType::end_mark,rc);
}

bool ON_BinaryArchive::Read3dmEndMark( size_t* file_length )
{
  if (false == Begin3dmTable(ON::archive_mode::read3dm,ON_3dmArchiveTableType::end_mark))
    return false;

  unsigned int tcode=0;
  ON__INT64 value=0;
  if ( file_length )
    *file_length = 0;

  const unsigned int saved_error_message_mask = m_error_message_mask;
  m_error_message_mask |= 0x0001; // disable v1 ReadByte() error message at EOF
  bool rc = PeekAt3dmBigChunkType(&tcode,&value);
  m_error_message_mask = saved_error_message_mask;

  if (rc)
  {
    if ( tcode == TCODE_ENDOFFILE ) 
    {
      rc = BeginRead3dmBigChunk(&tcode,&value);
      if ( rc && value > 0 && ((ON__UINT64)value) >= SizeofChunkLength() )
      {
        ON__UINT64 u64 = 0;
        rc = ReadEOFSizeOfFile( &u64 );
        if ( rc && file_length )
          *file_length = (size_t)u64;
        m_3dm_end_mark_length = u64;
        if ( !EndRead3dmChunk() )
          rc = false;
      }
    }
  }
  else if (1 == m_3dm_version)
  {
    // 2015-Nov-13 Dale Lear
    // The end chunk is missing in some V1 files.  It's 20 years later and this error is not helpful.
    rc = true;
  }

  return End3dmTable(ON_3dmArchiveTableType::end_mark,rc);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

ON::endian
ON_BinaryArchive::Endian() const // endian-ness of cpu
{
  return m_endian;
}

ON::archive_mode ON_BinaryArchive::Mode() const
{
  return m_mode;
}

bool ON_BinaryArchive::ReadMode() const
{
  bool bIsReading = false;

  switch (m_mode)
  {
  case ON::archive_mode::unset_archive_mode:
    break;
  case ON::archive_mode::read:
    bIsReading = true;
    break;
  case ON::archive_mode::write:
    break;
  case ON::archive_mode::readwrite:
    bIsReading = true;
    break;
  case ON::archive_mode::read3dm:
    bIsReading = true;
    break;
  case ON::archive_mode::write3dm:
    break;
  default:
    ON_ERROR("Invalid m_mode.");
    break;
  }

  return bIsReading;
}

bool ON_BinaryArchive::WriteMode() const
{
  bool bIsWriting = false;

  switch (m_mode)
  {
  case ON::archive_mode::unset_archive_mode:
    break;
  case ON::archive_mode::read:
    break;
  case ON::archive_mode::write:
    bIsWriting = true;
    break;
  case ON::archive_mode::readwrite:
    bIsWriting = true;
    break;
  case ON::archive_mode::read3dm:
    break;
  case ON::archive_mode::write3dm:
    bIsWriting = true;
    break;
  default:
    ON_ERROR("Invalid m_mode.");
    break;
  }

  return bIsWriting;
}

bool ON_BinaryArchive::UnsetMode() const
{
  return (false == ReadMode() && false == WriteMode());
}

void ON_BinaryArchive::UpdateCRC( size_t count, const void* p )
{
  if ( m_bDoChunkCRC ) {
    ON_3DM_BIG_CHUNK* c = m_chunk.Last();
    if (c) {
      if ( c->m_do_crc16 )
        c->m_crc16 = ON_CRC16( c->m_crc16, count, p ); // version 1 files had 16 bit CRC
      if ( c->m_do_crc32 )
        c->m_crc32 = ON_CRC32( c->m_crc32, count, p ); // version 2 files have 32 bit CRC
    }
  }
}


void ON_BinaryArchive::Internal_ReportCRCError()
{
  m_crc_error_count++;
  if (nullptr != m_3dm_table_status_list 
    && m_3dm_active_table == m_3dm_table_status_list->m_table_status.m_table_type
    && ON_3dmArchiveTableStatus::TableState::Finished !=  m_3dm_table_status_list->m_table_status.m_state
    )
  {
    m_3dm_table_status_list->m_table_status.m_crc_error_count++;
  }
  return;
}


unsigned int ON_BinaryArchive::BadCRCCount() const
{
  return m_crc_error_count;
}

/*
Returns:
  Number of critical errors
*/
unsigned int ON_BinaryArchive::CriticalErrorCount() const
{
  return m_critical_error_count;
}


void ON_BinaryArchive::Internal_ReportCriticalError()
{
  m_critical_error_count++;
  if (nullptr != m_3dm_table_status_list && m_3dm_active_table ==  m_3dm_table_status_list->m_table_status.m_table_type)
  {
    m_3dm_table_status_list->m_table_status.m_critical_error_count++;
  }
  return;
}

const ON_3dmArchiveTableStatus ON_BinaryArchive::Archive3dmTableStatus(
  ON_3dmArchiveTableType table_type
  )
{
  for (const ON_3dmTableStatusLink* link = m_3dm_table_status_list; nullptr != link; link = link->m_next)
  {
    if ( table_type == link->m_table_status.m_table_type )
      return link->m_table_status;
  }
  return ON_3dmArchiveTableStatus::Unset;
}


unsigned int ON_BinaryArchive::ErrorMessageMask() const
{
  return m_error_message_mask;
}

bool ON_BinaryArchive::MaskReadError( ON__UINT64 sizeof_request, ON__UINT64 sizeof_read ) const
{
  if ( 0 == (static_cast<unsigned int>(m_mode) % 2 ) )
    return false; // something is seriously wrong

  if ( sizeof_request == sizeof_read )
    return true; // no error

  if ( sizeof_read > sizeof_request )
    return false; // something is seriously wrong

  if ( 0 != (0x04 & m_error_message_mask) )
    return true;

  if (0 != (0x01 & m_error_message_mask) && 4 == sizeof_request && 0 == sizeof_read)
  {
    // when reading v1 files, there are some situations where
    // it is reasonable to attempt to read 4 bytes at the end
    // of a file.
    return true;
  }

  if (0 == m_3dm_version
    && 0 == m_3dm_opennurbs_version
    && 0 == m_3dm_start_section_offset
    && ON_3dmArchiveTableType::Unset == m_3dm_previous_table
    && ON_3dmArchiveTableType::Unset == m_3dm_active_table
    && ON_3dmArchiveTableType::Unset == m_3dm_first_failed_table
    && 0 == m_chunk
    && ON::archive_mode::read3dm == m_mode
    )
  {
    // In Read3dmStartSection(), we search for the string 
    // "3D Geometry File Format ...".  When a non-.3dm file
    // is searched, we eventually reach the end of the file.
    // This error condition is reported by the returning
    // false from ON_BinaryArchive::Read3dmStartSection().
    // ON_ERROR is not called to prevent annoying everyone
    // when the open file dialog is digging around looking
    // for files.
    return true;
  }

  return false; // parial read not permitted at this time.
}

ON__UINT64 ON_BinaryArchive::ReadBuffer( ON__UINT64 sizeof_buffer, void* buffer )
{
  // Expert user function to load a buffer with up to sizeof_buffer
  // bytes but tolerate encountering the end of the file.
  if ( 0 == buffer )
    return 0;
  unsigned int saved_error_mask = m_error_message_mask;
  m_error_message_mask |= 0x04; // tell Read to tolerate hitting the end of the file
  ON__UINT64 sizeof_read = Read((size_t)sizeof_buffer,buffer);
  m_error_message_mask = saved_error_mask;
  return sizeof_read;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

ON_BinaryFile::ON_BinaryFile( ON::archive_mode archive_mode ) 
  : ON_BinaryArchive( archive_mode )
{}

ON_BinaryFile::ON_BinaryFile( ON::archive_mode archive_mode, FILE* fp ) 
  : ON_BinaryArchive( archive_mode )
  , m_fp(fp)
{}

ON_BinaryFile::ON_BinaryFile( ON::archive_mode archive_mode, const char* file_system_path ) 
  : ON_BinaryArchive( archive_mode )
{
  switch (archive_mode)
  {
  case ON::archive_mode::unset_archive_mode:
    break;
  case ON::archive_mode::read:
  case ON::archive_mode::read3dm:
    m_fp = ON::OpenFile(file_system_path,"rb");
    break;
  case ON::archive_mode::write:
  case ON::archive_mode::write3dm:
    m_fp = ON::OpenFile(file_system_path,"wb");
    break;
  default:
    break;
  }
  if ( nullptr != m_fp )
    m_bCloseFileInDestructor = true;
  else
  {
    ON_ERROR("Invalid parameters");
  }
}


ON_BinaryFile::ON_BinaryFile( ON::archive_mode archive_mode, const wchar_t* file_system_path ) 
  : ON_BinaryArchive( archive_mode )
{
  switch (archive_mode)
  {
  case ON::archive_mode::unset_archive_mode:
    break;
  case ON::archive_mode::read:
  case ON::archive_mode::read3dm:
    m_fp = ON::OpenFile(file_system_path,L"rb");
    break;
  case ON::archive_mode::write:
  case ON::archive_mode::write3dm:
    m_fp = ON::OpenFile(file_system_path,L"wb");
    break;
  default:
    break;
  }
  if ( nullptr != m_fp )
    m_bCloseFileInDestructor = true;
  else
  {
    ON_ERROR("Invalid parameters");
  }
}

ON_BinaryFile::~ON_BinaryFile()
{
  if ( m_bCloseFileInDestructor )
    CloseFile();
  EnableMemoryBuffer(0);
}

bool ON_BinaryFile::FileIsOpen() const
{
  return (nullptr != m_fp);
}

void ON_BinaryFile::CloseFile()
{
  FILE* fp = m_fp;
  if (nullptr != fp)
  {
    m_fp = nullptr;
    ON::CloseFile(fp);
  }
  m_bCloseFileInDestructor = false;
}


size_t ON_BinaryArchive::Read( size_t count, void* p )
{
  size_t readcount = 0;

  if ( !ReadMode() )
  {
    Internal_ReportCriticalError();
    ON_ERROR("ReadMode() is false.");
  }
  else if ( count > 0 )
  {
    if ( nullptr == p )
    {
      Internal_ReportCriticalError();
      ON_ERROR("buffer parameter is nullptr.");
    }
    else
    {
      if (m_bChunkBoundaryCheck)
      {
        const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
        if (nullptr != c)
        {
          const ON__UINT64 current_pos = CurrentPosition();
          const ON__UINT64 new_pos = current_pos + ((ON__UINT64)count);

          if (current_pos < c->m_start_offset)
          {
            ON_ERROR("Attempt to read before the start of current chunk.");
            count = 0;
          }
          else if ( new_pos > c->m_end_offset )
          {
            ON_ERROR("Attempt to read beyond end of current chunk.");
            count = 0;
          }
        }
      }

      if (count > 0)
      {
        readcount = Internal_ReadOverride(count, p);

        if (readcount == count)
        {
          UpdateCRC(count, p);
        }
        else if ( false == MaskReadError(count,readcount) )
        {
          // error occured
          SetStorageDeviceError(ON_BinaryArchive::eStorageDeviceError::ReadFailed);
          ON_ERROR("Internal_ReadOverride(count, p) failed.");
        }

        if (readcount > 0)
          Internal_IncrementCurrentPosition((ON__UINT64)readcount);

      }
    }
  }

  return readcount;
}

bool ON_BinaryArchive::ReadByte(size_t count, void* p)
{
  return (count == Read(count, p));
}

size_t ON_BinaryArchive::Write( size_t count, const void* p )
{
  size_t writecount = 0;

  if ( !WriteMode() )
  {
    Internal_ReportCriticalError();
    ON_ERROR("WriteMode() is false.");
  }
  else if ( count > 0 ) 
  {
    if ( nullptr == p )
    {
      Internal_ReportCriticalError();
      ON_ERROR("buffer parameter is nullptr.");
    }
    else
    {
      const ON__UINT64 current_pos = CurrentPosition();

      if (m_bChunkBoundaryCheck)
      {
        const ON_3DM_BIG_CHUNK* c = m_chunk.Last();
        if (nullptr != c )
        {
          // March 2017 - Do not permit writing outside chunk boundaries.
          // (m_bChunkBoundaryCheck = false when WriteChunkLength() is called).
          if (current_pos < c->m_start_offset )
          {
            ON_ERROR("Attempt to write before current chunk boundary.");
            count = 0;
          }
          if ( current_pos > c->m_end_offset )
          {
            ON_ERROR("Attempt to write after current chunk boundary.");
            count = 0;
          }
        }
      }

      if (count > 0)
      {
        writecount = (size_t)Internal_WriteOverride(count, p);

        if (writecount == count)
        {
          UpdateCRC(count, p);
        }
        else
        {
          SetStorageDeviceError(ON_BinaryArchive::eStorageDeviceError::WriteFailed);
          ON_ERROR("Internal_WriteOverride(count, p) failed.");
        }

        if (writecount > 0)
        {
          ON_3DM_BIG_CHUNK* c = m_chunk.Last();
          if (nullptr != c && current_pos >= c->m_start_offset)
          {
            const ON__UINT64 new_pos = current_pos + (ON__UINT64)writecount;
            if (new_pos > c->m_end_offset)
              c->m_end_offset = new_pos;
          }
          Internal_IncrementCurrentPosition((ON__UINT64)writecount);
        }
      }
    }
  }

  return writecount;
}

bool ON_BinaryArchive::WriteByte( size_t count, const void* p )
{
  return (count == Write(count, p));
}

bool ON_BinaryArchive::EnableCRCCalculation( bool bEnable )
{
  bool rc = m_bDoChunkCRC;
  m_bDoChunkCRC = bEnable ? true : false;
  return rc;
}

bool
ON_BinaryArchive::SetArchive3dmVersion(int v)
{
  bool rc = false;
  // valid versions are 1,2,3,4,5,50,60,70,...
  // 1 - 4 correspond to Rhino V1 - V4.
  // 5 was used for early V5 betas with 4 byte chunk lengths
  // 50 is used for V5 files with 8 bytes chunk lengths.
  // 60, 70, ... will be used for Rhino V6, V7, etc.
  if ( (v >= 1 && v <= 5) || ( v >= 50 && 0 == (v % 10) && v <= ON_BinaryArchive::CurrentArchiveVersion() ) )
  {
    m_3dm_version = v;
    rc = true;
  }
  else 
  {
    m_3dm_version = 0;
    ON_ERROR("ON_BinaryArchive::SetArchive3dmVersion - invalid version");
  }
  return rc;
}

bool
ON_BinaryArchive::SetOpenNURBS3dmVersion(unsigned int v)
{
  m_3dm_opennurbs_version = v;
  return true;
}

void 
ON_BinaryFile::EnableMemoryBuffer(
       int buffer_capacity
       )
{
  if ( buffer_capacity > 0 && !m_memory_buffer) {
    m_memory_buffer = (unsigned char*)onmalloc(buffer_capacity);
    if ( m_memory_buffer ) {
      m_memory_buffer_capacity = buffer_capacity;
      m_memory_buffer_size = 0;
      m_memory_buffer_ptr = 0;
    }
  }
  else {
    if ( buffer_capacity == 0 && m_memory_buffer ) {
      Flush();
      onfree(m_memory_buffer);
    }
    m_memory_buffer = 0;
    m_memory_buffer_capacity = 0;
    m_memory_buffer_size = 0;
    m_memory_buffer_ptr = 0;
  }
}


size_t ON_BinaryFile::Internal_ReadOverride( size_t count, void* p )
{
  const size_t rc  = (m_fp) ? fread( p, 1, count, m_fp ) : 0;
  if (rc != count && nullptr != m_fp)
  {
    if (false == MaskReadError(count, rc))
    {
      ON_ERROR("fread() failed.");
    }
  }
  return rc;
}

size_t ON_BinaryFile::Internal_WriteOverride( size_t count, const void* p )
{
  size_t rc = 0;
  if ( m_fp ) 
  {
    if ( m_memory_buffer ) 
    {
      if ( count+m_memory_buffer_ptr >= m_memory_buffer_capacity ) {
        if ( !Flush() ) // flush existing memory buffer to disk
          return 0;
        rc = fwrite( p, 1, count, m_fp ); // write directly to disk
        if (rc != count)
        {
          ON_ERROR("fwrite() failed - situation A.");
        }
      }
      else 
      {
        // copy to the memory buffer
        memcpy( m_memory_buffer+m_memory_buffer_ptr, p, count );
        m_memory_buffer_ptr += count;
        if ( m_memory_buffer_ptr > m_memory_buffer_size )
          m_memory_buffer_size = m_memory_buffer_ptr;
        rc = count;
      }      
    }
    else
    {
      rc = fwrite( p, 1, count, m_fp );
      if (rc != count)
      {
        ON_ERROR("fwrite() failed - situation B.");
      }
    }
  }
  return rc;
}

bool ON_BinaryFile::Flush()
{
  bool rc = true;
  if ( m_fp ) 
  {
    if ( m_memory_buffer && m_memory_buffer_size > 0 ) 
    {
      // Put all of m_memory_buffer on "disk".
      rc = ( m_memory_buffer_size == fwrite( m_memory_buffer, 1, m_memory_buffer_size, m_fp ));   
      if (false == rc)
      {
        ON_ERROR("fwrite( m_memory_buffer, 1, m_memory_buffer_size, m_fp ) failed.");
      }
      if ( rc && m_memory_buffer_ptr != m_memory_buffer_size ) 
      {
        // The current position is not at the end of what we just wrote.
        // fseek back to m_fp points at the position corresponding to m_memory_buffer_ptr.
        ON__INT64 delta =  (m_memory_buffer_ptr >= m_memory_buffer_size) 
                  ?  ((ON__INT64)(m_memory_buffer_ptr - m_memory_buffer_size))
                  : -((ON__INT64)(m_memory_buffer_size - m_memory_buffer_ptr));
        if ( false == ON_FileStream::SeekFromCurrentPosition(m_fp,delta) )          
        {
          ON_ERROR("ON_FileStream::SeekFromCurrentPosition(m_fp,delta) failed.");
          rc = false;
        }
      }
      m_memory_buffer_size = 0;
      m_memory_buffer_ptr = 0;
    }
  }
  return rc;
}

ON__UINT64 ON_BinaryFile::Internal_CurrentPositionOverride() const
{
  ON__UINT64 offset = 0;

  if ( 0 != m_fp ) 
  {

#if defined(ON_COMPILER_MSC)
    // use an ftell() that supports file offsets > 2GB
    ON__INT64 offset64 = _ftelli64(m_fp);
    if ( offset64 < 0 )
    {
      ON_ERROR(" _ftelli64() failed");
    }
    else
    {
      offset = (ON__UINT64)offset64;
    }
#else
    offset = (ON__UINT64)ftell(m_fp);
#endif

    if ( m_memory_buffer && m_memory_buffer_size > 0 && m_memory_buffer_ptr > 0 ) 
    {
      // add bytes in memory buffer
      offset += (ON__INT64)m_memory_buffer_ptr;
    }
  }
  else 
  {
    ON_ERROR("m_fp is nullptr.");
  }

  return offset;
}

bool ON_BinaryFile::AtEnd() const
{
  bool rc = true;
  if ( m_fp ) 
  {
    rc = false;
    if ( ReadMode() && m_memory_buffer_ptr >= m_memory_buffer_size ) 
    {
      if (feof(m_fp))
      {
        rc = true;
      }
      else
      {
        // Attempt to read a single byte.
        int buffer;
        size_t fread_count = fread(&buffer, 1, 1, m_fp);
        if (feof(m_fp))
        {
          rc = true;
        }
        if (1 == fread_count)
        {
          // undo the 1 byte freed()
          ON_FileStream::SeekFromCurrentPosition(m_fp, -1);
        }
      }
    }
  }
  return rc;
}

bool ON_BinaryFile::Internal_SeekFromCurrentPositionOverride( int offset )
{
  // it appears that the calls to SeekFromCurrentPosition(),
  // and consequent call to fseek(), in ON_BinaryArchive::EndWrite3DMChunk()
  // really slow down 3DM file writing on some networks.  There are
  // reports of a 100x difference in local vs network saves.
  // I could not reproduce these 100x slow saves in testing on McNeel's
  // network but we have a good quality network and a server that's
  // properly tuned.  My guess is that the slow saves are happening
  // on servers that do a poor job of cacheing because they are starved
  // for memory and/or heavily used at the time of the save.
  //
  // To speed up network saves, ON_BinaryFile can optionally use
  // it's own buffer for buffered I/O instead of relying on fwrite()
  // and the OS to handle this.
  bool rc = false;
  if ( m_fp ) 
  {
    if ( nullptr != m_memory_buffer
      && ((ON__INT_PTR)m_memory_buffer_ptr)+((ON__INT_PTR)offset) >= 0
      && m_memory_buffer_ptr+offset <= m_memory_buffer_size ) 
    {
      m_memory_buffer_ptr += offset;
      rc = true;
    }
    else
    {
      // don't deal with memory buffer I/O if seek lands outside of current memory buffer.
      Flush();      
      if ( ON_FileStream::SeekFromCurrentPosition(m_fp,offset) )
      {
        rc = true;
      }
      else 
      {
        ON_ERROR("ON_FileStream::SeekFromCurrentPosition(m_fp,offset) failed.");
      }
    }
  }
  return rc;
}

bool ON_BinaryFile::Internal_SeekToStartOverride()
{
  bool rc = false;
  if ( m_fp ) 
  {
    Flush(); // don't deal with memory buffer I/O in rare seek from start
    if ( ON_FileStream::SeekFromStart(m_fp,0) )
    {
      rc = true;
    }
    else 
    {
      ON_ERROR("ON_FileStream::SeekFromStart(m_fp,0) failed.");
    }
  }
  return rc;
}

ON_3dmGoo::ON_3dmGoo()
        : m_typecode(0),
          m_value(0),
          m_goo(0),
          m_next_goo(0),
          m_prev_goo(0)
{}

ON_3dmGoo::~ON_3dmGoo()
{
  if ( m_prev_goo )
    m_prev_goo->m_next_goo = m_next_goo;
  if ( m_next_goo )
    m_next_goo->m_prev_goo = m_prev_goo;
  if ( m_goo ) {
    onfree(m_goo);
    m_goo = 0;
  }
}

ON_3dmGoo::ON_3dmGoo( const ON_3dmGoo& src )
        : m_typecode(0),
          m_value(0),
          m_goo(0),
          m_next_goo(0),
          m_prev_goo(0)
{
  *this = src;
}

ON_3dmGoo& ON_3dmGoo::operator=( const ON_3dmGoo& src )
{
  if ( this != &src ) {
    if ( m_goo ) {
      onfree(m_goo);
    }
    m_typecode = src.m_typecode;
    m_value = src.m_value;
    m_goo = (m_value > 0 && src.m_goo) ? (unsigned char*)onmemdup( src.m_goo, m_value ) : 0;
  }
  return *this;
}

void ON_3dmGoo::Dump(ON_TextLog& dump) const
{
  dump.Print("typecode = %08x value = %d\n",m_typecode,m_value);
}

bool ON_WriteOneObjectArchive(
          ON_BinaryArchive& archive,
          int version,
          const ON_Object& object
          )
{
	const ON_Object*  object_array = &object;
	return ON_WriteMultipleObjectArchive( archive, version, 1, &object_array );
}

bool ON_WriteOneObjectArchive(
  const wchar_t* filename,
  const ON_Object& object
)
{
	const ON_Object*  object_array = &object;
	return ON_WriteMultipleObjectArchive( filename, 0, 1, &object_array );
}

bool ON_WriteMultipleObjectArchive( 
          ON_BinaryArchive& archive,
          int version,
          const ON_SimpleArray<const ON_Object*>& object_list
          )
{
	return ON_WriteMultipleObjectArchive( archive, version, object_list.Count(), object_list.Array() );
}
bool ON_WriteMultipleObjectArchive(
  const wchar_t* filename,
  int version,
  size_t object_list_count,
  const ON_Object* const* object_list
)
{
  FILE* fp = ON::OpenFile( filename, L"wb" );
  if (nullptr == fp)
    return false;
  ON_BinaryFile archive( ON::archive_mode::write3dm, fp );
  archive.SetArchiveFullPath(filename);
  bool ok = ON_WriteMultipleObjectArchive( archive, version, object_list_count, object_list );
  ON::CloseFile( fp );
  return ok;
}

bool ON_WriteMultipleObjectArchive( 
          ON_BinaryArchive& archive,
          int version,
					size_t object_list_count,
          const ON_Object* const* object_list
          )
{
  if (object_list_count <= 0 || nullptr == object_list)
    return false;

  ONX_Model model;

  const bool bResolveIdAndNameConflicts = true;

  model.m_properties.m_RevisionHistory.NewRevision();
  
  // 1 Feb 2012 Dale Lear 
  //   http://dev.mcneel.com/bugtrack/?q=98543
  //   These simple object archives have no unit system so they
  //   can be read into a file with no scaling.  Prior to
  //   today the unit system was always millimeters.
  model.m_settings.m_ModelUnitsAndTolerances.m_unit_system.SetUnitSystem( ON::LengthUnitSystem::None );

  ON_Layer* layer = new ON_Layer(ON_Layer::Default);
  layer->SetId();
  layer->SetIndex(0);
  model.AddManagedModelComponent(layer, bResolveIdAndNameConflicts);

  for (size_t object_index = 0; object_index < object_list_count; object_index++)
  {
		const ON_Geometry* geometry = ON_Geometry::Cast(object_list[object_index]);
		if ( ON_BrepEdge::Cast(geometry) )
		{
			// write parent brep
			geometry = static_cast<const ON_BrepEdge*>(geometry)->Brep();
		}
		else if ( ON_BrepTrim::Cast(geometry) )
		{
			geometry = nullptr;
		}
		else if ( ON_BrepLoop::Cast(geometry) )
		{
			geometry = static_cast<const ON_BrepLoop*>(geometry)->Brep();
		}
		else if ( ON_BrepFace::Cast(geometry) )
		{
			// write parent brep
			geometry = static_cast<const ON_BrepFace*>(geometry)->Brep();
		}
		else if ( ON_CurveProxy::Cast(geometry) )
		{
			// write actual curve
			geometry = static_cast<const ON_CurveProxy*>(geometry)->ProxyCurve();
		}
		else if ( ON_SurfaceProxy::Cast(geometry) )
		{
			// write actual surface
			geometry = static_cast<const ON_SurfaceProxy*>(geometry)->ProxySurface();
		}

    if (nullptr == geometry)
      continue;

    // bManageGeometry = false means ~ON_ModelGeometryComponent will not delete geometry
    const bool bManageGeometry = false;
    const bool bManageAttributes = true;
    ON_3dmObjectAttributes* attributes = new ON_3dmObjectAttributes();
    attributes->m_layer_index = layer->Index();
    attributes->m_uuid = ON_CreateId();
    ON_ModelGeometryComponent* mg = ON_ModelGeometryComponent::CreateForExperts(
      bManageGeometry,
      const_cast<ON_Geometry*>(geometry), // safe - see bManageGeometry = false comment above.
      bManageAttributes,
      attributes,
      nullptr
    );

    if (nullptr == mg)
    {
      delete attributes;
      continue;
    }

    model.AddManagedModelComponent( mg, bResolveIdAndNameConflicts );
  }

  if ( (0 != version % 10)
    || version < ON_BinaryArchive::CurrentArchiveVersion() - 10
    || version > ON_BinaryArchive::CurrentArchiveVersion()
    )
  {
    version = ON_BinaryArchive::CurrentArchiveVersion();
  }
  model.m_sStartSectionComments = "Archive created by ON_WriteMultipleObjectArchive";
  bool rc = model.Write(archive, version );

  return rc;
}

static 
void Dump3dmChunk_ErrorReportHelper( ON__UINT64 offset, const char* msg, ON_TextLog& dump )
{
  int ioffset = (int)offset;
  dump.Print("** ERROR near offset %d ** %s\n",ioffset,msg);
}
static
bool DumpChunk_PrintHeaderInfo( ON__UINT64 offset0, ON__UINT32 typecode, ON__INT64 big_value, const char* typecode_name, ON_TextLog& dump)
{
  bool bShortChunk = (0 != (typecode & TCODE_SHORT));
  if ( 0 == typecode_name )
    typecode_name = ON_BinaryArchive::TypecodeName(typecode);
  if ( 0 == typecode_name )
    typecode_name = "unknown tcode";
  if ( bShortChunk )
  {
    dump.Print("%6d: %08X %s: value = %lld (%016llX)\n", offset0, typecode, typecode_name, big_value, big_value );
  }
  else 
  {
    // long chunk value = length of chunk data
    if ( big_value < 0 ) 
    {
      Dump3dmChunk_ErrorReportHelper(offset0,"BeginRead3dmChunk() returned length < 0.",dump);
      return false;
    }
    dump.Print("%6d: %08X %s: length = %lld bytes\n", offset0, typecode, typecode_name, big_value );
  }
  return true;
}

#define CASEtcode2string(tc) case tc: s = #tc ; break

const char* ON_BinaryArchive::TypecodeName( unsigned int tcode )
{

  const char* s;
  switch( tcode ) 
  {
  CASEtcode2string(TCODE_FONT_TABLE);
  CASEtcode2string(TCODE_FONT_RECORD);
  CASEtcode2string(TCODE_DIMSTYLE_TABLE);
  CASEtcode2string(TCODE_DIMSTYLE_RECORD);
  CASEtcode2string(TCODE_INSTANCE_DEFINITION_RECORD);
  CASEtcode2string(TCODE_COMMENTBLOCK);
  CASEtcode2string(TCODE_ENDOFFILE);
  CASEtcode2string(TCODE_ENDOFFILE_GOO);
  CASEtcode2string(TCODE_LEGACY_GEOMETRY);
  CASEtcode2string(TCODE_OPENNURBS_OBJECT);
  CASEtcode2string(TCODE_GEOMETRY);
  CASEtcode2string(TCODE_ANNOTATION);
  CASEtcode2string(TCODE_DISPLAY);
  CASEtcode2string(TCODE_RENDER);
  CASEtcode2string(TCODE_INTERFACE);
  CASEtcode2string(TCODE_TOLERANCE);
  CASEtcode2string(TCODE_TABLE);
  CASEtcode2string(TCODE_TABLEREC);
  CASEtcode2string(TCODE_USER);
  CASEtcode2string(TCODE_SHORT);
  CASEtcode2string(TCODE_CRC);
  CASEtcode2string(TCODE_ANONYMOUS_CHUNK);
  CASEtcode2string(TCODE_MATERIAL_TABLE);
  CASEtcode2string(TCODE_LAYER_TABLE);
  CASEtcode2string(TCODE_LIGHT_TABLE);
  CASEtcode2string(TCODE_OBJECT_TABLE);
  CASEtcode2string(TCODE_PROPERTIES_TABLE);
  CASEtcode2string(TCODE_SETTINGS_TABLE);
  CASEtcode2string(TCODE_BITMAP_TABLE);
  CASEtcode2string(TCODE_USER_TABLE);
  CASEtcode2string(TCODE_INSTANCE_DEFINITION_TABLE);
  CASEtcode2string(TCODE_HATCHPATTERN_TABLE);
  CASEtcode2string(TCODE_HATCHPATTERN_RECORD);
  CASEtcode2string(TCODE_LINETYPE_TABLE);
  CASEtcode2string(TCODE_LINETYPE_RECORD);
  CASEtcode2string(TCODE_OBSOLETE_LAYERSET_TABLE);
  CASEtcode2string(TCODE_OBSOLETE_LAYERSET_RECORD);
  CASEtcode2string(TCODE_TEXTURE_MAPPING_TABLE);
  CASEtcode2string(TCODE_TEXTURE_MAPPING_RECORD);
  CASEtcode2string(TCODE_HISTORYRECORD_TABLE);  
  CASEtcode2string(TCODE_HISTORYRECORD_RECORD);
  CASEtcode2string(TCODE_ENDOFTABLE);
  CASEtcode2string(TCODE_PROPERTIES_REVISIONHISTORY);
  CASEtcode2string(TCODE_PROPERTIES_NOTES);
  CASEtcode2string(TCODE_PROPERTIES_PREVIEWIMAGE);
  CASEtcode2string(TCODE_PROPERTIES_COMPRESSED_PREVIEWIMAGE);
  CASEtcode2string(TCODE_PROPERTIES_APPLICATION);
  CASEtcode2string(TCODE_PROPERTIES_OPENNURBS_VERSION);
  CASEtcode2string(TCODE_SETTINGS_PLUGINLIST);
  CASEtcode2string(TCODE_SETTINGS_UNITSANDTOLS);
  CASEtcode2string(TCODE_SETTINGS_RENDERMESH);
  CASEtcode2string(TCODE_SETTINGS_ANALYSISMESH);
  CASEtcode2string(TCODE_SETTINGS_ANNOTATION);
  CASEtcode2string(TCODE_SETTINGS_NAMED_CPLANE_LIST);
  CASEtcode2string(TCODE_SETTINGS_NAMED_VIEW_LIST);
  CASEtcode2string(TCODE_SETTINGS_VIEW_LIST);
  CASEtcode2string(TCODE_SETTINGS_CURRENT_LAYER_INDEX);
  CASEtcode2string(TCODE_SETTINGS_CURRENT_MATERIAL_INDEX);
  CASEtcode2string(TCODE_SETTINGS_CURRENT_COLOR);
  CASEtcode2string(TCODE_SETTINGS__NEVER__USE__THIS);
  CASEtcode2string(TCODE_SETTINGS_CURRENT_WIRE_DENSITY);
  CASEtcode2string(TCODE_SETTINGS_RENDER);
  CASEtcode2string(TCODE_SETTINGS_GRID_DEFAULTS);
  CASEtcode2string(TCODE_SETTINGS_MODEL_URL);
  CASEtcode2string(TCODE_SETTINGS_CURRENT_FONT_INDEX);
  CASEtcode2string(TCODE_SETTINGS_CURRENT_DIMSTYLE_INDEX);
  CASEtcode2string(TCODE_SETTINGS_ATTRIBUTES);
  CASEtcode2string(TCODE_SETTINGS_RENDER_USERDATA);
  CASEtcode2string(TCODE_VIEW_RECORD);
  CASEtcode2string(TCODE_VIEW_CPLANE);
  CASEtcode2string(TCODE_VIEW_VIEWPORT);
  CASEtcode2string(TCODE_VIEW_VIEWPORT_USERDATA);
  CASEtcode2string(TCODE_VIEW_SHOWCONGRID);
  CASEtcode2string(TCODE_VIEW_SHOWCONAXES);
  CASEtcode2string(TCODE_VIEW_SHOWWORLDAXES);
  CASEtcode2string(TCODE_VIEW_TRACEIMAGE);
  CASEtcode2string(TCODE_VIEW_WALLPAPER);
  CASEtcode2string(TCODE_VIEW_WALLPAPER_V3);
  CASEtcode2string(TCODE_VIEW_TARGET);
  CASEtcode2string(TCODE_VIEW_V3_DISPLAYMODE);
  CASEtcode2string(TCODE_VIEW_NAME);
  CASEtcode2string(TCODE_VIEW_POSITION);
  CASEtcode2string(TCODE_VIEW_ATTRIBUTES);
  CASEtcode2string(TCODE_BITMAP_RECORD);
  CASEtcode2string(TCODE_MATERIAL_RECORD);
  CASEtcode2string(TCODE_LAYER_RECORD);
  CASEtcode2string(TCODE_LIGHT_RECORD);
  CASEtcode2string(TCODE_LIGHT_RECORD_ATTRIBUTES);
  CASEtcode2string(TCODE_OBJECT_RECORD_ATTRIBUTES_USERDATA);
  CASEtcode2string(TCODE_OBJECT_RECORD_HISTORY);
  CASEtcode2string(TCODE_OBJECT_RECORD_HISTORY_HEADER);
  CASEtcode2string(TCODE_OBJECT_RECORD_HISTORY_DATA);
  CASEtcode2string(TCODE_LIGHT_RECORD_END);
  CASEtcode2string(TCODE_USER_TABLE_UUID);
  CASEtcode2string(TCODE_USER_TABLE_RECORD_HEADER);
  CASEtcode2string(TCODE_USER_RECORD);
  CASEtcode2string(TCODE_GROUP_TABLE);
  CASEtcode2string(TCODE_GROUP_RECORD);
  CASEtcode2string(TCODE_OBJECT_RECORD);
  CASEtcode2string(TCODE_OBJECT_RECORD_TYPE);
  CASEtcode2string(TCODE_OBJECT_RECORD_ATTRIBUTES);
  CASEtcode2string(TCODE_OBJECT_RECORD_END);
  CASEtcode2string(TCODE_OPENNURBS_CLASS);
  CASEtcode2string(TCODE_OPENNURBS_CLASS_UUID);
  CASEtcode2string(TCODE_OPENNURBS_CLASS_DATA);
  CASEtcode2string(TCODE_OPENNURBS_CLASS_USERDATA);
  CASEtcode2string(TCODE_OPENNURBS_CLASS_USERDATA_HEADER);
  CASEtcode2string(TCODE_OPENNURBS_CLASS_END);
  CASEtcode2string(TCODE_OPENNURBS_BUFFER);
  CASEtcode2string(TCODE_ANNOTATION_SETTINGS);
  CASEtcode2string(TCODE_TEXT_BLOCK);
  CASEtcode2string(TCODE_ANNOTATION_LEADER);
  CASEtcode2string(TCODE_LINEAR_DIMENSION);
  CASEtcode2string(TCODE_ANGULAR_DIMENSION);
  CASEtcode2string(TCODE_RADIAL_DIMENSION);
  CASEtcode2string(TCODE_RHINOIO_OBJECT_NURBS_CURVE);
  CASEtcode2string(TCODE_RHINOIO_OBJECT_NURBS_SURFACE);
  CASEtcode2string(TCODE_RHINOIO_OBJECT_BREP);
  CASEtcode2string(TCODE_RHINOIO_OBJECT_DATA);
  CASEtcode2string(TCODE_RHINOIO_OBJECT_END);
  CASEtcode2string(TCODE_LEGACY_ASM);
  CASEtcode2string(TCODE_LEGACY_PRT);
  CASEtcode2string(TCODE_LEGACY_SHL);
  CASEtcode2string(TCODE_LEGACY_FAC);
  CASEtcode2string(TCODE_LEGACY_BND);
  CASEtcode2string(TCODE_LEGACY_TRM);
  CASEtcode2string(TCODE_LEGACY_SRF);
  CASEtcode2string(TCODE_LEGACY_CRV);
  CASEtcode2string(TCODE_LEGACY_SPL);
  CASEtcode2string(TCODE_LEGACY_PNT);
  CASEtcode2string(TCODE_STUFF);
  CASEtcode2string(TCODE_LEGACY_ASMSTUFF);
  CASEtcode2string(TCODE_LEGACY_PRTSTUFF);
  CASEtcode2string(TCODE_LEGACY_SHLSTUFF);
  CASEtcode2string(TCODE_LEGACY_FACSTUFF);
  CASEtcode2string(TCODE_LEGACY_BNDSTUFF);
  CASEtcode2string(TCODE_LEGACY_TRMSTUFF);
  CASEtcode2string(TCODE_LEGACY_SRFSTUFF);
  CASEtcode2string(TCODE_LEGACY_CRVSTUFF);
  CASEtcode2string(TCODE_LEGACY_SPLSTUFF);
  CASEtcode2string(TCODE_LEGACY_PNTSTUFF);
  CASEtcode2string(TCODE_RH_POINT);
  CASEtcode2string(TCODE_RH_SPOTLIGHT);
  CASEtcode2string(TCODE_OLD_RH_TRIMESH);
  CASEtcode2string(TCODE_OLD_MESH_VERTEX_NORMALS);
  CASEtcode2string(TCODE_OLD_MESH_UV);
  CASEtcode2string(TCODE_OLD_FULLMESH);
  CASEtcode2string(TCODE_MESH_OBJECT);
  CASEtcode2string(TCODE_COMPRESSED_MESH_GEOMETRY);
  CASEtcode2string(TCODE_ANALYSIS_MESH);
  CASEtcode2string(TCODE_NAME);
  CASEtcode2string(TCODE_VIEW);
  CASEtcode2string(TCODE_CPLANE);
  CASEtcode2string(TCODE_NAMED_CPLANE);
  CASEtcode2string(TCODE_NAMED_VIEW);
  CASEtcode2string(TCODE_VIEWPORT);
  CASEtcode2string(TCODE_SHOWGRID);
  CASEtcode2string(TCODE_SHOWGRIDAXES);
  CASEtcode2string(TCODE_SHOWWORLDAXES);
  CASEtcode2string(TCODE_VIEWPORT_POSITION);
  CASEtcode2string(TCODE_VIEWPORT_TRACEINFO);
  CASEtcode2string(TCODE_SNAPSIZE);
  CASEtcode2string(TCODE_NEAR_CLIP_PLANE);
  CASEtcode2string(TCODE_HIDE_TRACE);
  CASEtcode2string(TCODE_NOTES);
  CASEtcode2string(TCODE_UNIT_AND_TOLERANCES);
  CASEtcode2string(TCODE_MAXIMIZED_VIEWPORT);
  CASEtcode2string(TCODE_VIEWPORT_WALLPAPER);
  CASEtcode2string(TCODE_SUMMARY);
  CASEtcode2string(TCODE_BITMAPPREVIEW);
  CASEtcode2string(TCODE_VIEWPORT_V1_DISPLAYMODE);
  CASEtcode2string(TCODE_LAYERTABLE);
  CASEtcode2string(TCODE_LAYERREF);
  CASEtcode2string(TCODE_XDATA);
  CASEtcode2string(TCODE_RGB);
  CASEtcode2string(TCODE_TEXTUREMAP);
  CASEtcode2string(TCODE_BUMPMAP);
  CASEtcode2string(TCODE_TRANSPARENCY);
  CASEtcode2string(TCODE_DISP_AM_RESOLUTION);
  CASEtcode2string(TCODE_RGBDISPLAY);
  CASEtcode2string(TCODE_RENDER_MATERIAL_ID);
  CASEtcode2string(TCODE_LAYER);
  CASEtcode2string(TCODE_LAYER_OBSELETE_1);
  CASEtcode2string(TCODE_LAYER_OBSELETE_2);
  CASEtcode2string(TCODE_LAYER_OBSELETE_3);
  CASEtcode2string(TCODE_LAYERON);
  CASEtcode2string(TCODE_LAYERTHAWED);
  CASEtcode2string(TCODE_LAYERLOCKED);
  CASEtcode2string(TCODE_LAYERVISIBLE);
  CASEtcode2string(TCODE_LAYERPICKABLE);
  CASEtcode2string(TCODE_LAYERSNAPABLE);
  CASEtcode2string(TCODE_LAYERRENDERABLE);
  CASEtcode2string(TCODE_LAYERSTATE);
  CASEtcode2string(TCODE_LAYERINDEX);
  CASEtcode2string(TCODE_LAYERMATERIALINDEX);
  CASEtcode2string(TCODE_RENDERMESHPARAMS);
  CASEtcode2string(TCODE_DISP_CPLINES);
  CASEtcode2string(TCODE_DISP_MAXLENGTH);
  CASEtcode2string(TCODE_CURRENTLAYER);
  CASEtcode2string(TCODE_LAYERNAME);
  CASEtcode2string(TCODE_LEGACY_TOL_FIT);
  CASEtcode2string(TCODE_LEGACY_TOL_ANGLE);
  CASEtcode2string(TCODE_DICTIONARY);
  CASEtcode2string(TCODE_DICTIONARY_ID);
  CASEtcode2string(TCODE_DICTIONARY_ENTRY);
  CASEtcode2string(TCODE_DICTIONARY_END);
  default:
    // unknown typecode.
    s = 0; 
    break;
  }
  return s;
}

#undef CASEtcode2string

char* ON_BinaryArchive::ON_TypecodeParse( unsigned int tcode, char* typecode_name, size_t max_length )
{
  char* s;
  const char* sub_name;
  const char* h = "0123456789ABCDEF";
  char c, c0;
  size_t slen;

  if ( !typecode_name || max_length <= 0 )
    return 0;
  memset(typecode_name,0,max_length*sizeof(typecode_name[0]));
  slen = max_length-1; // the -1 insures the there is a null terminator
  if ( slen <= 0 )
    return 0;

  sub_name = ON_BinaryArchive::TypecodeName(tcode);
  if ( 0 != sub_name && 0 != sub_name[0] )
  {
    c0 = *sub_name++;
    s = typecode_name+1;
    slen--;
    while ( *sub_name )
    {
      if ( slen <= 0 )
        return 0;
      *s++ = *sub_name++;
      slen--;
    }
    typecode_name[0] = c0;
    return typecode_name;    
  }

  sub_name = ON_BinaryArchive::TypecodeName( tcode & 0x7FFF0000 );
  if ( !sub_name || 0 == sub_name[0] )
    return 0;

  c0 = *sub_name++;
  s = typecode_name+1;
  slen--;

  while ( *sub_name )
  {
    if ( slen <= 0 )
      return 0;
    *s++ = *sub_name++;
    slen--;
  }

  sub_name = ON_BinaryArchive::TypecodeName( tcode & TCODE_SHORT );
  if ( sub_name )
  {
    if ( slen <= 0 ) return 0; *s++ = ' '; slen--;
    if ( slen <= 0 ) return 0; *s++ = '|'; slen--;
    if ( slen <= 0 ) return 0; *s++ = ' '; slen--;
    while ( *sub_name )
    {
      if ( slen <= 0 )
        return 0;
      *s++ = *sub_name++;
      slen--;
    }
  }

  sub_name = ON_BinaryArchive::TypecodeName( tcode & TCODE_CRC );
  if ( sub_name )
  {
    if ( slen <= 0 ) return 0; *s++ = ' '; slen--;
    if ( slen <= 0 ) return 0; *s++ = '|'; slen--;
    if ( slen <= 0 ) return 0; *s++ = ' '; slen--;
    while ( *sub_name )
    {
      if ( slen <= 0 )
        return 0;
      *s++ = *sub_name++;
      slen--;
    }
  }

  sub_name = ON_BinaryArchive::TypecodeName( tcode & 0x7FFF );
  if ( sub_name )
  {
    if ( slen <= 0 ) return 0; *s++ = ' '; slen--;
    if ( slen <= 0 ) return 0; *s++ = '|'; slen--;
    if ( slen <= 0 ) return 0; *s++ = ' '; slen--;
    while ( *sub_name )
    {
      if ( slen <= 0 )
        return 0;
      *s++ = *sub_name++;
      slen--;
    }
  }
  else 
  {
    if ( slen <= 0 ) return 0; *s++ = ' '; slen--;
    if ( slen <= 0 ) return 0; *s++ = '|'; slen--;
    if ( slen <= 0 ) return 0; *s++ = ' '; slen--;
    if ( slen <= 0 ) return 0; *s++ = '0'; slen--;
    if ( slen <= 0 ) return 0; *s++ = 'x'; slen--;
    c = h[((tcode & 0x7000) / 0x1000) & 0xF];
    if ( slen > 0 ) {*s++ = c; slen--;}
    c = h[((tcode & 0xF00) / 0x100) & 0xF];
    if ( slen > 0 ) {*s++ = c; slen--;}
    c = h[((tcode & 0xF0) / 0x10) & 0xF];
    if ( slen > 0 ) {*s++ = c; slen--;}
    c = h[tcode & 0xF];
    if ( slen > 0 ) {*s++ = c; slen--;}
  }

  *typecode_name = c0;

  return typecode_name;
}

static
bool Dump3dmChunk_EndReadChunkHelper( ON_BinaryArchive& file, ON__UINT64 offset0, ON__UINT32 tcode, ON__INT64 big_value, ON_TextLog& dump )
{
  const bool bShortChunk = (0 != (tcode & TCODE_SHORT));
  const ON__UINT64 offset1 = file.CurrentPosition();
  bool rc = file.EndRead3dmChunk();
  if ( !rc ) 
  {
    Dump3dmChunk_ErrorReportHelper(offset1,"EndRead3dmChunk() failed.",dump);
  }
  else if (!bShortChunk) 
  {
    // The crc is read or skipped by the EndRead3dmChunk() call.
    // "extra" is the number of bytes we did not parse in the dump.
    ON__INT64 sizeof_crc = (0 != (TCODE_CRC & tcode)) ? 4 : 0;
    ON__INT64 sizeof_chunk_header = 4+file.SizeofChunkLength();
    ON__INT64 delta =  (offset1 > offset0)
              ?  ((ON__INT64)(offset1 - offset0))
              : -((ON__INT64)(offset0 - offset1));
    const ON__INT64 extra = big_value - (delta+sizeof_crc-sizeof_chunk_header);
    if ( extra < 0 ) 
    {
      Dump3dmChunk_ErrorReportHelper(offset0,"Read beyond end of chunk.",dump);
      rc = false;
    }
  }
  return rc;
}

static 
bool Dump3dmChunk_UserDataHeaderHelper( ON__UINT64 offset, ON_BinaryArchive& file, 
                                 int major_userdata_version, int minor_userdata_version, 
                                 ON_TextLog& dump )
{
  // TCODE_OPENNURBS_CLASS_USERDATA chunks have 2 uuids
  // the first identifies the type of ON_Object class
  // the second identifies that kind of user data
  ON_UUID userdata_classid = ON_nil_uuid;
  ON_UUID userdata_itemid = ON_nil_uuid;
  ON_UUID userdata_appid = ON_nil_uuid;  // id of plug-in that owns the user data
  int userdata_copycount = -1;
  ON_Xform userdata_xform;
  bool bLastSavedAsGoo = false;
  int ud_archive_3dm_version = 0;
  int ud_archive_opennurbs_version = 0;

  bool rc = false;
  bool bCallEndRead3dmChunk = false;

  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  const ON__UINT64 offset0 = file.CurrentPosition();

  for(;;)
  {
    if ( 2 == major_userdata_version )
    {
      rc = file.PeekAt3dmBigChunkType(&tcode,&big_value);
      if ( !rc )
      {
        Dump3dmChunk_ErrorReportHelper(offset,"Unable to find the TCODE_OPENNURBS_CLASS_USERDATA_HEADER chunk header in a TCODE_OPENNURBS_CLASS_USERDATA chunk.",dump);
        break;
      }
      if ( TCODE_OPENNURBS_CLASS_USERDATA_HEADER != tcode )
      {
        Dump3dmChunk_ErrorReportHelper(offset,"Unable to find the TCODE_OPENNURBS_CLASS_USERDATA_HEADER chunk header in a TCODE_OPENNURBS_CLASS_USERDATA chunk.",dump);
        rc = false;
        break;
      }
      rc = file.BeginRead3dmBigChunk(&tcode,&big_value); 
      if ( !rc )
      {
        Dump3dmChunk_ErrorReportHelper(offset,"Unable to read the TCODE_OPENNURBS_CLASS_USERDATA_HEADER chunk header in a TCODE_OPENNURBS_CLASS_USERDATA chunk.",dump);
        break;
      }
      if ( TCODE_OPENNURBS_CLASS_USERDATA_HEADER != tcode )
      {
        Dump3dmChunk_ErrorReportHelper(offset,"Missing TCODE_OPENNURBS_CLASS_USERDATA_HEADER chunk header in a TCODE_OPENNURBS_CLASS_USERDATA chunk.",dump);
        Dump3dmChunk_EndReadChunkHelper(file,offset0,tcode,big_value,dump);
        rc = false;
        break;
      }
      bCallEndRead3dmChunk = true;
    }

    rc = file.ReadUuid( userdata_classid );
    if ( !rc ) 
    {
      Dump3dmChunk_ErrorReportHelper(offset,"ReadUuid() failed to read the user data class id.",dump);
      break;
    }

    dump.Print("UserData class id = ");
    dump.Print( userdata_classid );
    const ON_ClassId* pUserDataClassId = ON_ClassId::ClassId(userdata_classid);
    if ( pUserDataClassId )
    {
      const char* sClassName = pUserDataClassId->ClassName();
      if ( sClassName )
      {
        dump.Print(" (%s)",sClassName);
      }
    }
    dump.Print("\n");

    rc = file.ReadUuid( userdata_itemid );
    if ( !rc ) 
    {
       Dump3dmChunk_ErrorReportHelper(offset,"ReadUuid() failed to read the user data item id.",dump);
       break;
    }
    dump.Print("UserData item id = ");
    dump.Print( userdata_itemid );
    dump.Print("\n");

    rc = file.ReadInt( &userdata_copycount );
    if ( !rc )
    {
      Dump3dmChunk_ErrorReportHelper(offset,"ReadInt() failed to read the user data copy count.",dump);
      break;
    }
    dump.Print("UserData copy count = %d\n",userdata_copycount);

    rc = file.ReadXform( userdata_xform );
    if ( !rc )
    {
      Dump3dmChunk_ErrorReportHelper(offset,"ReadXform() failed to read the user data xform.",dump);
      break;
    }

    if ( 2 != major_userdata_version )
      break;
    if ( minor_userdata_version < 1 )
      break;
    rc = file.ReadUuid( userdata_appid );
    if ( !rc)
    {
      Dump3dmChunk_ErrorReportHelper(offset,"ReadUuid() failed to read the user data app plug-in id.",dump);
      break;
    }
    dump.Print("UserData app plug-in id = ");
    dump.Print( userdata_appid );
    dump.Print("\n");
    if ( minor_userdata_version < 2 )
      break;
    rc = file.ReadBool(&bLastSavedAsGoo);
    if (!rc)
    {
      Dump3dmChunk_ErrorReportHelper(offset,"ReadBool() failed to read the user data header bSavedAsGoo value.",dump);
      break;
    }
    rc = file.ReadInt( &ud_archive_3dm_version );
    if (!rc)
    {
      Dump3dmChunk_ErrorReportHelper(offset,"ReadBool() failed to read the user data header bSavedAsGoo value.",dump);
      break;
    }
    rc = file.ReadInt( &ud_archive_opennurbs_version );
    if (!rc)
    {
      Dump3dmChunk_ErrorReportHelper(offset,"ReadBool() failed to read the user data header bSavedAsGoo value.",dump);
      break;
    }
    if ( bLastSavedAsGoo )
      dump.Print("Userdata originally written by opennurbs %d in 3dm version %d and saved as goo in this file.\n",ud_archive_opennurbs_version,ud_archive_3dm_version);
    else
      dump.Print("Userdata written by opennurbs %d in 3dm version %d.\n",ud_archive_opennurbs_version,ud_archive_3dm_version);

    break;
  }

  if ( bCallEndRead3dmChunk )
  {
    if (!Dump3dmChunk_EndReadChunkHelper(file,offset0,tcode,big_value,dump))
    {
      if (rc)
      {
        Dump3dmChunk_ErrorReportHelper(offset,"EndRead3dmChunk() failed to close the TCODE_OPENNURBS_CLASS_USERDATA_HEADER chunk.",dump);
      }
      rc = false;
    }
  }

  return rc;
}


unsigned int 
ON_BinaryArchive::Dump3dmChunk( ON_TextLog& dump, int recursion_depth )
{
  //ON_BinaryArchive& file = *this;
  const char* typecode_name = 0;
  bool bShortChunk = false;
  const ON__UINT64 offset0 = CurrentPosition();
  unsigned int typecode = 0;
  ON__INT64 big_value;
  bool rc = BeginRead3dmBigChunk( &typecode, &big_value );
  if (!rc) 
  {
    Dump3dmChunk_ErrorReportHelper(offset0,"BeginRead3dmChunk() failed.",dump);
  }
  else 
  {
    if ( 0 == typecode ) 
    {
      Dump3dmChunk_ErrorReportHelper(offset0,"BeginRead3dmChunk() returned typecode = 0.",dump);
      EndRead3dmChunk();
      return 0;
    }
    else {
      if ( 0 == recursion_depth )
      {
        dump.Print("\n");
      }

      ////bShortChunk = (0 != (typecode & TCODE_SHORT));
      typecode_name = ON_BinaryArchive::TypecodeName(typecode);
      bShortChunk = (0 != (typecode & TCODE_SHORT));
      if ( !DumpChunk_PrintHeaderInfo(offset0,typecode,big_value,typecode_name,dump) )
      {
        EndRead3dmChunk();
        return 0;
      }

      int major_userdata_version = -1;
      int minor_userdata_version = -1;

      switch( typecode ) 
      {
      case TCODE_PROPERTIES_TABLE:
      case TCODE_SETTINGS_TABLE:
      case TCODE_BITMAP_TABLE:
      case TCODE_MATERIAL_TABLE:
      case TCODE_LAYER_TABLE:
      case TCODE_GROUP_TABLE:
      case TCODE_LIGHT_TABLE:
      case TCODE_FONT_TABLE:
      case TCODE_DIMSTYLE_TABLE:
      case TCODE_HATCHPATTERN_TABLE:
      case TCODE_LINETYPE_TABLE:
      case TCODE_TEXTURE_MAPPING_TABLE:
      case TCODE_HISTORYRECORD_TABLE:
      case TCODE_USER_TABLE:
      case TCODE_INSTANCE_DEFINITION_TABLE:
      case TCODE_OBJECT_TABLE:
        // start of a table
        {
          dump.PushIndent();
          unsigned int record_typecode = 0;
          for (;;) {
            record_typecode = Dump3dmChunk( dump, recursion_depth+1 );
            if ( !record_typecode ) {
              break;
            }
            if ( TCODE_ENDOFTABLE == record_typecode ) {
              break;
            }
          }
          dump.PopIndent();
        }
        break;

      case TCODE_PROPERTIES_OPENNURBS_VERSION:
        {
          dump.PushIndent();
          dump.Print("Version of opennurbs that wrote this file: %lld\n",big_value);
          dump.PopIndent();           
          if (0 == m_3dm_opennurbs_version && big_value > 0 && ((ON__UINT64)big_value) < ON_UNSET_UINT_INDEX)
            ON_SetBinaryArchiveOpenNURBSVersion(*this,(ON__UINT32)big_value);
        }
        break;

      case TCODE_BITMAP_RECORD:
        {
          dump.PushIndent();
          unsigned int bitmap_chunk_typecode = Dump3dmChunk( dump, recursion_depth+1 );
          if ( 0 == typecode )
            typecode = bitmap_chunk_typecode;
          dump.PopIndent();
        }
        break;

      case TCODE_MATERIAL_RECORD:
        {
          dump.PushIndent();
          unsigned int material_chunk_typecode = Dump3dmChunk( dump, recursion_depth+1 );
          if ( 0 == typecode )
            typecode = material_chunk_typecode;
          dump.PopIndent();
        }
        break;

      case TCODE_LAYER_RECORD:
        {
          dump.PushIndent();
          unsigned int material_chunk_typecode = Dump3dmChunk( dump, recursion_depth+1 );
          if ( 0 == typecode )
            typecode = material_chunk_typecode;
          dump.PopIndent();
        }
        break;

      case TCODE_GROUP_RECORD:
        {
          dump.PushIndent();
          unsigned int group_chunk_typecode = Dump3dmChunk( dump, recursion_depth+1 );
          if ( 0 == typecode )
            typecode = group_chunk_typecode;
          dump.PopIndent();
        }
        break;

      case TCODE_FONT_RECORD:
        {
          dump.PushIndent();
          unsigned int font_chunk_typecode = Dump3dmChunk( dump, recursion_depth+1 );
          if ( 0 == typecode )
            typecode = font_chunk_typecode;
          dump.PopIndent();
        }
        break;

      case TCODE_DIMSTYLE_RECORD:
        {
          dump.PushIndent();
          unsigned int dimstyle_chunk_typecode = Dump3dmChunk( dump, recursion_depth+1 );
          if ( 0 == typecode )
            typecode = dimstyle_chunk_typecode;
          dump.PopIndent();
        }
        break;

      case TCODE_LIGHT_RECORD:
        {
          dump.PushIndent();
          unsigned int light_chunk_typecode = 0;
          for (;;) {
            light_chunk_typecode = Dump3dmChunk( dump, recursion_depth+1 );
            if ( !light_chunk_typecode ) {
              break;
            }
            if ( TCODE_LIGHT_RECORD_END == light_chunk_typecode ) {
              break;
            }
            switch( light_chunk_typecode ) {
            //case TCODE_OBJECT_RECORD_TYPE:
            case TCODE_LIGHT_RECORD_ATTRIBUTES:
            case TCODE_LIGHT_RECORD_ATTRIBUTES_USERDATA:
            case TCODE_OPENNURBS_CLASS:
              break;
            default:
              {
                Dump3dmChunk_ErrorReportHelper(offset0,"Rogue chunk in light record.",dump);
              }
            }
          }
          dump.PopIndent();
        }
        break;

      case TCODE_TEXTURE_MAPPING_RECORD:
        {
          dump.PushIndent();
          unsigned int mapping_chunk_typecode = Dump3dmChunk( dump, recursion_depth+1 );
          if ( !typecode )
            typecode = mapping_chunk_typecode;
          dump.PopIndent();
        }
        break;

      case TCODE_HISTORYRECORD_RECORD:
        {
          dump.PushIndent();
          unsigned int history_chunk_typecode = Dump3dmChunk( dump, recursion_depth+1 );
          if ( !typecode )
            typecode = history_chunk_typecode;
          dump.PopIndent();
        }
        break;

      case TCODE_HATCHPATTERN_RECORD:
        {
          dump.PushIndent();
          unsigned int hatch_chunk_typecode = Dump3dmChunk( dump, recursion_depth+1 );
          if ( !typecode )
            typecode = hatch_chunk_typecode;
          dump.PopIndent();
        }
        break;

      case TCODE_INSTANCE_DEFINITION_RECORD:
        {
          dump.PushIndent();
          unsigned int idef_chunk_typecode = Dump3dmChunk( dump, recursion_depth+1 );
          if ( 0 == typecode )
            typecode = idef_chunk_typecode;
          dump.PopIndent();
        }
        break;

      case TCODE_OBJECT_RECORD:
        {
          dump.PushIndent();
          unsigned int object_chunk_typecode = 0;
          for (;;) {
            object_chunk_typecode = Dump3dmChunk( dump, recursion_depth+1 );
            if ( !object_chunk_typecode ) {
              break;
            }
            if ( TCODE_OBJECT_RECORD_END == object_chunk_typecode ) {
              break;
            }
            switch( object_chunk_typecode ) {
            case TCODE_OBJECT_RECORD_TYPE:
            case TCODE_OBJECT_RECORD_ATTRIBUTES:
            case TCODE_OBJECT_RECORD_ATTRIBUTES_USERDATA:
            case TCODE_OPENNURBS_CLASS:
              break;
            default:
              {
                Dump3dmChunk_ErrorReportHelper(offset0,"Rogue chunk in object record.",dump);
              }
            }
          }
          dump.PopIndent();
        }
        break;

      case TCODE_OBJECT_RECORD_ATTRIBUTES:
        {
          dump.PushIndent();
          if ( big_value < 14 )
          {
            Dump3dmChunk_ErrorReportHelper(offset0,"Length of chunk is too small.  Should be >= 14.",dump);
          }
          else
          {
            ON_UUID uuid = ON_nil_uuid;
            int layer_index = -99;
            int mj = -1;
            int mn = -1;
            if ( !Read3dmChunkVersion(&mj,&mn))
            {
              Dump3dmChunk_ErrorReportHelper(offset0,"Read3dmChunkVersion() failed.",dump);
            }
            else if (!ReadUuid(uuid))
            {
              Dump3dmChunk_ErrorReportHelper(offset0,"ReadUuid() failed.",dump);
            }
            else if ( !ReadInt(&layer_index) )
            {
              Dump3dmChunk_ErrorReportHelper(offset0,"ReadInt() failed to read layer index.",dump);
            }
            else
            {
              dump.Print("Rhino object uuid: ");
              dump.Print(uuid);
              dump.Print("\n");
              dump.Print("layer index: %d\n",layer_index);
            }
          }
          dump.PopIndent();
        }
        break;

      case TCODE_OPENNURBS_CLASS:
        {
          dump.PushIndent();
          unsigned int opennurbs_object_chunk_typecode = 0;
          for (;;) {
            opennurbs_object_chunk_typecode = Dump3dmChunk( dump, recursion_depth+1  );
            if ( !opennurbs_object_chunk_typecode ) {
              break;
            }
            if ( TCODE_OPENNURBS_CLASS_END == opennurbs_object_chunk_typecode ) {
              break;
            }
            switch( opennurbs_object_chunk_typecode ) 
            {
            case TCODE_OPENNURBS_CLASS_UUID:
              break;
            case TCODE_OPENNURBS_CLASS_DATA:
              break;
            case TCODE_OPENNURBS_CLASS_USERDATA:
              break;
            default:
              {
                Dump3dmChunk_ErrorReportHelper(offset0,"Rogue chunk in OpenNURBS class record.",dump);
              }
            }
          }
          dump.PopIndent();
        }
        break;

      case TCODE_OPENNURBS_CLASS_USERDATA:
        {
          if ( !Read3dmChunkVersion(&major_userdata_version, &minor_userdata_version ) )
          {
            Dump3dmChunk_ErrorReportHelper(offset0,"Read3dmChunkVersion() failed to read TCODE_OPENNURBS_CLASS_USERDATA chunk version.",dump);
          }
          else
          {
            dump.PushIndent();
            dump.Print("UserData chunk version: %d.%d\n",
                       major_userdata_version,
                       minor_userdata_version
                       );
            if ( 1 == major_userdata_version || 2 == major_userdata_version )
            {
              const ON__UINT64 userdata_header_offset = CurrentPosition();
              switch ( major_userdata_version )
              {
              case 1:
              case 2:
                {
                  // version 1 user data header information was not wrapped
                  // in a chunk.
                  //
                  // version 2 user data header information is wrapped
                  // in a TCODE_OPENNURBS_CLASS_USERDATA_HEADER chunk.
                  if ( Dump3dmChunk_UserDataHeaderHelper( 
                                  userdata_header_offset, *this, 
                                  major_userdata_version, minor_userdata_version,
                                  dump ) 
                     )
                  {
                    // a TCODE_ANONYMOUS_CHUNK contains user data goo
                    int anon_typecode =  Dump3dmChunk( dump, recursion_depth+1 );
                    if ( TCODE_ANONYMOUS_CHUNK != anon_typecode )
                    {
                      Dump3dmChunk_ErrorReportHelper( offset0,"Userdata Expected a TCODE_ANONYMOUS_CHUNK chunk.",dump);
                    }
                  }
                }
                break;
              default:
                if ( major_userdata_version < 3 )
                {
                }
                else
                {
                  dump.Print("New user data format created after this diagnostic tool was written.\n");
                }
                break;
              }
            }

            dump.PopIndent();
          }
        }
        break;

      case TCODE_OPENNURBS_CLASS_UUID:
      case TCODE_USER_TABLE_UUID:
        {
          dump.PushIndent();
          ON_UUID uuid = ON_nil_uuid;
          const ON_ClassId* pClassId = 0;
          if ( !ReadUuid( uuid ) ) {
             Dump3dmChunk_ErrorReportHelper(offset0,"ReadUuid() failed.",dump);
          }
          else 
          {
            if ( typecode == TCODE_OPENNURBS_CLASS_UUID ) 
            {
              dump.Print("OpenNURBS class id = ");
              pClassId = ON_ClassId::ClassId(uuid);
            }
            else if ( typecode == TCODE_USER_TABLE_UUID ) 
            {
              dump.Print("User table id = ");
            }
            else {
              dump.Print("UUID = ");
            }
            dump.Print( uuid );
            if ( pClassId )
            {
              const char* sClassName = pClassId->ClassName();
              if ( sClassName )
              {
                dump.Print(" (%s)",sClassName);
              }
            }
            dump.Print("\n");
          }

          dump.PopIndent();
        }
        break;

      case TCODE_OPENNURBS_CLASS_USERDATA_HEADER:
        {
          // we should never get here because this chunk is parsed in the TCODE_OPENNURBS_CLASS_USERDATA case above.
          Dump3dmChunk_ErrorReportHelper(offset0,"Encountered TCODE_OPENNURBS_CLASS_USERDATA_HEADER chunk outside a TCODE_OPENNURBS_CLASS_USERDATA chunk.",dump);
        }
        break;

      case TCODE_ENDOFFILE:
      case TCODE_ENDOFFILE_GOO:
        {
          dump.PushIndent();
          if ( big_value < 4 ) {
            Dump3dmChunk_ErrorReportHelper(offset0,"TCODE_ENDOFFILE chunk withlength < 4.",dump);
          }
          else {
            ON__UINT64 sizeof_file = 0;
            ReadEOFSizeOfFile(&sizeof_file);
            dump.Print("current position = %d  stored size = %llu\n",
                       CurrentPosition(), 
                       sizeof_file
                       );
          }
          dump.PopIndent();
        }
        break;

      }
    }

    const ON__UINT64 offset1 = CurrentPosition();
    if ( !EndRead3dmChunk(true) ) 
    {
      Dump3dmChunk_ErrorReportHelper(offset1,"EndRead3dmChunk() failed.",dump);
      rc = false;
    }
    else if (!bShortChunk) 
    {
      ON__INT64 delta =  (offset1 > offset0)
                ?  ((ON__INT64)(offset1 - offset0))
                : -((ON__INT64)(offset0 - offset1));
      const ON__INT64 extra = big_value - (delta-4-SizeofChunkLength());
      if ( extra < 0 ) 
      {
        Dump3dmChunk_ErrorReportHelper(offset0,"Read beyond end of chunk.",dump);
      }
    }
  }
  return typecode;
}



ON_Read3dmBufferArchive::ON_Read3dmBufferArchive( 
          size_t sizeof_buffer, 
          const void* buffer,
          bool bCopyBuffer,
          int archive_3dm_version,
          unsigned int archive_opennurbs_version
          )
: ON_BinaryArchive(ON::archive_mode::read3dm)
, m_p(0)
, m_buffer(0)
, m_sizeof_buffer(0)
, m_buffer_position(0)
, m_reserved1(0)
, m_reserved2(0)
, m_reserved3(0)
, m_reserved4(0)
{
  if ( sizeof_buffer > 0 && 0 != buffer )
  {
    if ( bCopyBuffer )
    {
      m_p = onmalloc(sizeof_buffer);
      if ( 0 != m_p )
        memcpy(m_p,buffer,sizeof_buffer);
      m_buffer = (const unsigned char*)m_p;
    }
    else
    {
      m_buffer = (const unsigned char*)buffer;
    }
    if ( m_buffer )
    {
      m_sizeof_buffer = sizeof_buffer;
      SetArchive3dmVersion(archive_3dm_version);
      ON_SetBinaryArchiveOpenNURBSVersion(*this,archive_opennurbs_version);
    }
  }
}

ON_Read3dmBufferArchive::~ON_Read3dmBufferArchive()
{
  if ( m_p )
    onfree(m_p);
}

// ON_BinaryArchive overrides
ON__UINT64 ON_Read3dmBufferArchive::Internal_CurrentPositionOverride() const
{
  return (ON__UINT64)m_buffer_position;
}

bool ON_Read3dmBufferArchive::Internal_SeekFromCurrentPositionOverride( int offset )
{
  bool rc = false;
  if ( m_buffer )
  {
    if (offset >= 0 )
    {
      m_buffer_position += offset;
      rc = true;
    }
    else if ( size_t(-offset) <= m_buffer_position )
    {
      m_buffer_position -= (size_t(-offset));
      rc = true;
    }
  }
  return rc;
}

bool ON_Read3dmBufferArchive::Internal_SeekToStartOverride()
{
  bool rc = false;
  if ( m_buffer ) 
  {
    m_buffer_position = 0;
    rc = true;
  }
  return rc;
}

bool ON_Read3dmBufferArchive::AtEnd() const
{
  return (m_buffer_position >= m_sizeof_buffer) ? true : false;
}

size_t ON_Read3dmBufferArchive::Internal_ReadOverride( size_t count, void* buffer )
{
  if ( count <= 0 || 0 == buffer )
    return 0;

  size_t maxcount = ( m_sizeof_buffer > m_buffer_position ) 
                  ? (m_sizeof_buffer - m_buffer_position)
                  : 0;
  if ( count > maxcount )
    count = maxcount;

  if ( count > 0 ) 
  {
    memcpy( buffer, m_buffer+m_buffer_position, count );
    m_buffer_position += count;
  }

  return count;
}

size_t ON_Read3dmBufferArchive::Internal_WriteOverride( size_t, const void* )
{
  // ON_Read3dmBufferArchive does not support Write() and Flush()
  return 0;
}

bool ON_Read3dmBufferArchive::Flush()
{
  // ON_Read3dmBufferArchive does not support Write() and Flush()
  return false;
}


size_t ON_Read3dmBufferArchive::SizeOfBuffer() const
{
  return m_sizeof_buffer;
}

const void* ON_Read3dmBufferArchive::Buffer() const
{
  return (const void*)m_buffer;
}

ON_Write3dmBufferArchive::ON_Write3dmBufferArchive( 
          size_t initial_sizeof_buffer, 
          size_t max_sizeof_buffer, 
          int archive_3dm_version,
          unsigned int archive_opennurbs_version
          )
: ON_BinaryArchive(ON::archive_mode::write3dm)
, m_p(0)
, m_buffer(0)
, m_sizeof_buffer(0)
, m_max_sizeof_buffer(max_sizeof_buffer)
, m_sizeof_archive(0)
, m_buffer_position(0)
, m_reserved1(0)
, m_reserved2(0)
, m_reserved3(0)
, m_reserved4(0)
{
  if ( initial_sizeof_buffer > 0 )
    AllocBuffer(initial_sizeof_buffer);
  if ( archive_3dm_version < 2 )
  {
    archive_3dm_version = ON_BinaryArchive::CurrentArchiveVersion();
    archive_opennurbs_version = ON::Version();
  }
  SetArchive3dmVersion(archive_3dm_version);
  ON_SetBinaryArchiveOpenNURBSVersion(*this,archive_opennurbs_version);
}

ON_Write3dmBufferArchive::~ON_Write3dmBufferArchive()
{
  if ( m_p )
    onfree(m_p);
}

void ON_Write3dmBufferArchive::AllocBuffer( size_t sz )
{
  if ( sz > m_sizeof_buffer 
       && (m_max_sizeof_buffer <= 0 || sz <= m_max_sizeof_buffer) 
     )
  {
    if (sz < 2 * m_sizeof_buffer || 0 == m_sizeof_buffer)
    {
      sz = 2*m_sizeof_buffer;
      if (sz < 512)
        sz = 512;
      if (sz > m_max_sizeof_buffer && m_max_sizeof_buffer > 0)
        sz = m_max_sizeof_buffer;
    }

    m_p = onrealloc(m_p,sz);
    m_buffer = (unsigned char*)m_p;

    if ( 0 != m_buffer )
    {
      memset( m_buffer + m_sizeof_buffer, 0, sz - m_sizeof_buffer );
      m_sizeof_buffer = sz;
    }
    else
    {
      m_sizeof_buffer = 0;
    }
  }
}

// ON_BinaryArchive overrides
ON__UINT64 ON_Write3dmBufferArchive::Internal_CurrentPositionOverride() const
{
  return (ON__UINT64)m_buffer_position;
}

bool ON_Write3dmBufferArchive::Internal_SeekFromCurrentPositionOverride( int offset )
{
  bool rc = false;
  if ( m_buffer )
  {
    if (offset >= 0 )
    {
      m_buffer_position += offset;
      rc = true;
    }
    else if ( size_t(-offset) <= m_buffer_position )
    {
      m_buffer_position -= (size_t(-offset));
      rc = true;
    }
  }
  return rc;
}

bool ON_Write3dmBufferArchive::Internal_SeekToStartOverride()
{
  m_buffer_position = 0;
  return true;
}

bool ON_Write3dmBufferArchive::AtEnd() const
{
  return (m_buffer_position >= m_sizeof_buffer) ? true : false;
}

size_t ON_Write3dmBufferArchive::Internal_ReadOverride( size_t count, void* buffer )
{
  if ( count <= 0 || 0 == buffer )
    return 0;

  size_t maxcount = ( m_sizeof_buffer > m_buffer_position ) 
                  ? (m_sizeof_buffer - m_buffer_position)
                  : 0;
  if ( count > maxcount )
    count = maxcount;

  if ( count > 0 ) 
  {
    memcpy( buffer, m_buffer+m_buffer_position, count );
    m_buffer_position += count;
  }

  return count;
}

size_t ON_Write3dmBufferArchive::Internal_WriteOverride( size_t sz, const void* buffer )
{
  if ( sz <= 0 || 0 == buffer )
    return 0;

  if ( m_buffer_position + sz > m_sizeof_buffer )
  {
    AllocBuffer(m_buffer_position + sz);
  }

  if ( m_buffer_position + sz > m_sizeof_buffer )
    return 0;

  memcpy( m_buffer + m_buffer_position, buffer, sz );
  m_buffer_position += sz;
  if ( m_buffer_position > m_sizeof_archive )
    m_sizeof_archive = m_buffer_position;

  return sz;
}

bool ON_Write3dmBufferArchive::Flush()
{
  // Nothing to flush
  return true;
}


size_t ON_Write3dmBufferArchive::SizeOfBuffer() const
{
  return m_sizeof_buffer;
}

const void* ON_Write3dmBufferArchive::Buffer() const
{
  return (const void*)m_buffer;
}

void* ON_Write3dmBufferArchive::HarvestBuffer()
{
  void* buffer = m_buffer;

  m_p = 0;
  m_buffer = 0;
  m_sizeof_buffer = 0;
  m_sizeof_archive = 0;
  m_buffer_position = 0;

  return buffer;
}

size_t ON_Write3dmBufferArchive::SizeOfArchive() const
{
  return m_sizeof_archive;
}




ON_BinaryArchiveBuffer::ON_BinaryArchiveBuffer( ON::archive_mode mode, ON_Buffer* buffer )
: ON_BinaryArchive(mode)
, m_buffer(buffer)
{
  if (nullptr != m_buffer)
    m_buffer->SeekFromStart(0);
}

ON_BinaryArchiveBuffer::~ON_BinaryArchiveBuffer()
{
  m_buffer = 0;
}

bool ON_BinaryArchiveBuffer::SetBuffer( ON_Buffer* buffer )
{
  if ( 0 == m_buffer )
  {
    m_buffer = buffer;
    if (nullptr != m_buffer)
      m_buffer->SeekFromStart(0);
    return true;
  }

  return false;
}

ON_Buffer* ON_BinaryArchiveBuffer::Buffer() const
{
  return m_buffer;
}

ON__UINT64 ON_BinaryArchiveBuffer::Internal_CurrentPositionOverride() const
{
  if ( 0 != m_buffer )
    return m_buffer->CurrentPosition();

  return 0;
}

bool ON_BinaryArchiveBuffer::Internal_SeekFromCurrentPositionOverride(int offset)
{
  if ( 0 != m_buffer )
    return m_buffer->SeekFromCurrentPosition(offset);

  return false;
}

bool ON_BinaryArchiveBuffer::Internal_SeekToStartOverride()
{
  if ( 0 != m_buffer )
    return m_buffer->SeekFromStart(0);

  return false;
}

bool ON_BinaryArchiveBuffer::AtEnd() const
{
  if ( 0 != m_buffer )
    return m_buffer->AtEnd();

  return false;
}

size_t ON_BinaryArchiveBuffer::Internal_ReadOverride( size_t count, void* a )
{
  if ( 0 != m_buffer )
    return (size_t)m_buffer->Read(count,a);

  return 0;
}

size_t ON_BinaryArchiveBuffer::Internal_WriteOverride( size_t count, const void* a )
{
  if ( 0 != m_buffer )
    return (size_t)m_buffer->Write(count,a);

  return 0;
}

bool ON_BinaryArchiveBuffer::Flush()
{
  if ( 0 != m_buffer )
    return true;

  return false;
}

ON_3dmAnnotationContext::~ON_3dmAnnotationContext()
{
  // NOTE WELL:
  //  https://mcneel.myjetbrains.com/youtrack/issue/RH-57616
  //  ON_3dmAnnotationContext::Default is a global const instance.
  //  Compilers like VS 2019 16.5.0 set the memory for that instance to read-only.
  //  This destructor must not write to memory used by const instances.
  if ( this != &ON_3dmAnnotationContext::Default)
    Internal_Destroy();
}

ON_3dmAnnotationContext::ON_3dmAnnotationContext(const ON_3dmAnnotationContext& src)
{
  Internal_CopyFrom(src);
}

ON_3dmAnnotationContext& ON_3dmAnnotationContext::operator=(const ON_3dmAnnotationContext& src)
{
  if (this != &src)
  {
    Internal_Destroy();
    Internal_CopyFrom(src);
  }
  return *this;
}

void ON_3dmAnnotationContext::Internal_CopyFrom(const ON_3dmAnnotationContext& src)
{
  if (nullptr != src.m_managed_parent_dim_style)
  {
    m_managed_parent_dim_style = new ON_DimStyle(*src.m_managed_parent_dim_style);
    m_parent_dim_style = m_managed_parent_dim_style;
  }
  else
  {
    m_parent_dim_style = src.m_parent_dim_style;
  }

  if (nullptr != src.m_managed_override_dim_style)
  {
    m_managed_override_dim_style = new ON_DimStyle(*src.m_managed_override_dim_style);
    m_override_dim_style = m_managed_override_dim_style;
  }
  else
  {
    m_override_dim_style = src.m_override_dim_style;
  }

  if (nullptr != src.m_annotation_settings)
  {
    m_managed_annotation_settings = new ON_3dmAnnotationSettings(*src.m_managed_annotation_settings);
    m_annotation_settings = m_managed_annotation_settings;
  }
  else
  {
    m_annotation_settings = src.m_annotation_settings;
  }

  m_view_context = src.m_view_context;
  m_model_length_unit_system = src.m_model_length_unit_system;
  m_page_length_unit_system = src.m_page_length_unit_system;
  m_binary_archive = src.m_binary_archive;
  m_V5_3dm_archive_dim_style_index = src.m_V5_3dm_archive_dim_style_index;
}

void ON_3dmAnnotationContext::Internal_Destroy()
{
  SetReferencedAnnotationSettings(nullptr);
  SetReferencedDimStyle(nullptr,nullptr,ON_UNSET_INT_INDEX);
  m_view_context = ON_3dmAnnotationContext::Default.m_view_context;
  m_model_length_unit_system = ON_3dmAnnotationContext::Default.m_model_length_unit_system;
  m_page_length_unit_system = ON_3dmAnnotationContext::Default.m_page_length_unit_system;
  m_binary_archive = ON_3dmAnnotationContext::Default.m_binary_archive;
};

const ON_3dmAnnotationSettings& ON_3dmAnnotationContext::AnnotationSettings() const
{
  return
    (nullptr != m_annotation_settings)
    ? *m_annotation_settings
    : ON_3dmSettings::Default.m_AnnotationSettings;
}

void ON_3dmAnnotationContext::SetReferencedAnnotationSettings(
  const ON_3dmAnnotationSettings* annotation_settings
)
{
  if (nullptr != m_managed_annotation_settings)
  {
    delete m_managed_annotation_settings;
    m_managed_annotation_settings = nullptr;
  }
  m_annotation_settings = annotation_settings;
}

void ON_3dmAnnotationContext::SetManagedAnnotationSettings(
  const ON_3dmAnnotationSettings& annotation_settings
)
{
  SetReferencedAnnotationSettings(nullptr);
  m_managed_annotation_settings = new ON_3dmAnnotationSettings(annotation_settings);
  m_annotation_settings = m_managed_annotation_settings;
}

bool ON_3dmAnnotationContext::AnnotationSettingsAreSet() const
{
  return (nullptr != m_annotation_settings);
}

ON::active_space ON_3dmAnnotationContext::ViewContext() const
{
  return m_view_context;
}

void ON_3dmAnnotationContext::SetViewContext(
  ON::active_space view_context
)
{
  m_view_context = view_context;
}

ON::LengthUnitSystem ON_3dmAnnotationContext::ModelLengthUnitSystem() const
{
  return m_model_length_unit_system;
}
  
void ON_3dmAnnotationContext::SetModelLengthUnitSystem(
  ON::LengthUnitSystem model_length_unit_system
)
{
  m_model_length_unit_system = model_length_unit_system;
}

ON::LengthUnitSystem ON_3dmAnnotationContext::PageLengthUnitSystem() const
{
  return m_page_length_unit_system;
}
  
void ON_3dmAnnotationContext::SetPageLengthUnitSystem(
  ON::LengthUnitSystem page_length_unit_system
)
{
  m_page_length_unit_system = page_length_unit_system;
}


const ON_DimStyle& ON_3dmAnnotationContext::DimStyle() const
{
  return
    (nullptr != m_override_dim_style)
    ? *m_override_dim_style
    : ParentDimStyle();
}

const ON_DimStyle& ON_3dmAnnotationContext::ParentDimStyle() const
{
  return
    (nullptr != m_parent_dim_style)
    ? *m_parent_dim_style
    : ON_DimStyle::Default;
}

void ON_3dmAnnotationContext::UpdateReferencedDimStyle(
  const class ON_DimStyle* old_pointer,
  const class ON_DimStyle* new_pointer
)
{
  // this function is called to update referenced dimstyle pointers.
  if (nullptr == old_pointer || nullptr == new_pointer)
    return;

  if (nullptr == old_pointer || old_pointer == m_managed_parent_dim_style || old_pointer == m_managed_override_dim_style)
  {
    ON_ERROR("Invalid old_pointer value.");
    return;
  }

  if (m_parent_dim_style == old_pointer)
    m_parent_dim_style = new_pointer;
  if (m_override_dim_style == old_pointer)
    m_override_dim_style = new_pointer;
}

  
void ON_3dmAnnotationContext::SetReferencedDimStyle(
  const ON_DimStyle* parent_dim_style,
  const ON_DimStyle* override_dim_style,
  int V5_3dm_archive_index
)
{
  if (nullptr != m_managed_parent_dim_style)
  {
    delete m_managed_parent_dim_style;
    m_managed_parent_dim_style = nullptr;
  }
  if (nullptr != m_managed_override_dim_style)
  {
    delete m_managed_override_dim_style;
    m_managed_override_dim_style = nullptr;
  }
  m_parent_dim_style = parent_dim_style;
  m_override_dim_style
    = (nullptr != parent_dim_style && nullptr != override_dim_style && parent_dim_style->IdIsNotNil() && parent_dim_style->Id() == override_dim_style->ParentId() && override_dim_style->HasOverrides() )
    ? override_dim_style
    : nullptr;
  m_V5_3dm_archive_dim_style_index = V5_3dm_archive_index;
}

void ON_3dmAnnotationContext::SetManagedDimStyle(
  const ON_DimStyle& parent_dim_style,
  const ON_DimStyle* override_dim_style,
  int V5_3dm_archive_index
)
{
  if (nullptr != override_dim_style)
  {
    if (parent_dim_style.IdIsNil() || override_dim_style->ParentId() != parent_dim_style.Id() || false == override_dim_style->HasOverrides())
      override_dim_style = nullptr;
  }

  ON_DimStyle* managed_parent = new ON_DimStyle(parent_dim_style);
  ON_DimStyle* managed_override 
    = (nullptr == override_dim_style)
    ? nullptr
    : new ON_DimStyle(*override_dim_style);

  SetReferencedDimStyle(nullptr,nullptr,ON_UNSET_INT_INDEX);

  m_managed_parent_dim_style = managed_parent;
  m_managed_override_dim_style = managed_override;
}

bool ON_3dmAnnotationContext::DimStyleIsSet() const
{
  return (nullptr != m_parent_dim_style);
}

/*
Returns:
  If the dimstyle is not set or it has a nil parent id, then DimStyleId() is returned.
  Otherwise the parent id is returned.
*/
ON_UUID ON_3dmAnnotationContext::ParentDimStyleId() const
{
  return
    (nullptr != m_parent_dim_style)
    ? m_parent_dim_style->Id()
    : ON_nil_uuid;
}

int ON_3dmAnnotationContext::V5_ArchiveDimStyleIndex() const
{
  return m_V5_3dm_archive_dim_style_index;
}

bool ON_3dmAnnotationContext::IsOverrideDimStyle() const
{
  return (nullptr != m_override_dim_style);
}

const class ON_BinaryArchive* ON_3dmAnnotationContext::BinaryArchive() const
{
  return m_binary_archive;
}
  
void ON_3dmAnnotationContext::SetReferencedBinaryArchive(
  const class ON_BinaryArchive* binary_archive
)
{
  m_binary_archive = binary_archive;
}

bool ON_3dmAnnotationContext::BinaryArchiveIsSet() const
{
  return (nullptr != m_binary_archive);
}

