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

bool ON_NameHash::IsValidAndNotEmpty() const
{
  return (
    (m_flags & ON_NameHash::flags_length_mask) > 0 
    && ON_SHA1_Hash::EmptyContentHash != m_sha1_hash
    );
}

bool ON_NameHash::IsEmptyNameHash() const
{
  return (ON_SHA1_Hash::EmptyContentHash == m_sha1_hash);
}

bool ON_NameHash::IsInvalidNameHash() const
{
  return (ON_SHA1_Hash::ZeroDigest == m_sha1_hash);
}

bool ON_NameHash::IgnoreCase() const
{
  return (0 != m_flags && ON_NameHash::flags_file_path != m_flags && 0 == (m_flags & ON_NameHash::flags_case_sensitive));
}

ON__UINT32 ON_NameHash::MappedNameCodePointCount() const
{
  return 
    (m_flags != ON_NameHash::flags_file_path)
    ? (m_flags & ON_NameHash::flags_length_mask)
    : 0U;
}

ON_UUID ON_NameHash::ParentId() const
{
  return m_parent_id;
}

// SHA-1 hash of mapped name
ON_SHA1_Hash ON_NameHash::MappedNameSha1Hash() const
{
  return m_sha1_hash;
}

// 32 bit hash of mapped name
ON__UINT32 ON_NameHash::DataCRC(ON__UINT32 current_remainder) const
{
  current_remainder = IdCRC(current_remainder);
  current_remainder= NameCRC(current_remainder);
  return current_remainder;
}

ON__UINT32 ON_NameHash::IdCRC(ON__UINT32 current_remainder) const
{
  return ON_CRC32(current_remainder,sizeof(m_parent_id),&m_parent_id);
}

ON__UINT32 ON_NameHash::NameCRC(ON__UINT32 current_remainder) const
{
  current_remainder = ON_CRC32(current_remainder,sizeof(m_flags),&m_flags);
  return ON_CRC32(current_remainder,sizeof(m_sha1_hash),&m_sha1_hash);
}

int ON_NameHash::CompareNameSHA1(
  const ON_NameHash& a,
  const ON_NameHash& b
  )
{
  if ( a.m_flags < b.m_flags )
    return -1;
  if ( a.m_flags > b.m_flags )
    return 1;
  return ON_SHA1_Hash::Compare(a.m_sha1_hash,b.m_sha1_hash);
}

int ON_NameHash::CompareNameSHA1Ptr(
  const ON_NameHash* a,
  const ON_NameHash* b
  )
{
  if (nullptr == a)
    a = &ON_NameHash::EmptyNameHash;
  if (nullptr == b)
    b = &ON_NameHash::EmptyNameHash;
  return ON_NameHash::CompareNameSHA1(*a,*b);
}

int ON_NameHash::CompareParentId(
  const ON_NameHash& a,
  const ON_NameHash& b
  )
{
  return ON_UuidCompare(a.m_parent_id,b.m_parent_id);
}

int ON_NameHash::CompareParentIdPtr(
  const ON_NameHash* a,
  const ON_NameHash* b
  )
{
  if (nullptr == a)
    a = &ON_NameHash::EmptyNameHash;
  if (nullptr == b)
    b = &ON_NameHash::EmptyNameHash;
  return ON_NameHash::CompareParentId(*a,*b);
}

int ON_NameHash::Compare(
  const ON_NameHash& a,
  const ON_NameHash& b
  )
{
  if ( a.m_flags < b.m_flags )
    return -1;
  if ( a.m_flags > b.m_flags )
    return 1;
  int rc = ON_UuidCompare(a.m_parent_id,b.m_parent_id);
  if ( 0 == rc )
    rc = ON_SHA1_Hash::Compare(a.m_sha1_hash,b.m_sha1_hash);
  return rc;
}

int ON_NameHash::ComparePtr(
  const ON_NameHash* a,
  const ON_NameHash* b
  )
{
  if (nullptr == a)
    a = &ON_NameHash::EmptyNameHash;
  if (nullptr == b)
    b = &ON_NameHash::EmptyNameHash;
  return ON_NameHash::Compare(*a,*b);
}

bool operator==(
  const ON_NameHash& a,
  const ON_NameHash& b
  )
{
  return (ON_NameHash::Compare(a,b) == 0);
}

bool operator!=(
  const ON_NameHash& a,
  const ON_NameHash& b
  )
{
  return (ON_NameHash::Compare(a,b) != 0);
}

bool operator<(
  const ON_NameHash& a,
  const ON_NameHash& b
  )
{
  return (ON_NameHash::Compare(a,b) < 0);
}

bool operator<=(
  const ON_NameHash& a,
  const ON_NameHash& b
  )
{
  return (ON_NameHash::Compare(a,b) <= 0);
}

bool operator>(
  const ON_NameHash& a,
  const ON_NameHash& b
  )
{
  return (ON_NameHash::Compare(a,b) > 0);
}

bool operator>=(
  const ON_NameHash& a,
  const ON_NameHash& b
  )
{
  return (ON_NameHash::Compare(a,b) >= 0);
}

ON_NameHash ON_NameHash::Create(
  const ON_wString& name
  )
{
  return ON_NameHash::Create(ON_nil_uuid, name);
}

ON_NameHash ON_NameHash::Create(
  const ON_wString& name,
  bool bIgnoreCase
  )
{
  return ON_NameHash::Create(ON_nil_uuid, name, bIgnoreCase);
}

ON_NameHash ON_NameHash::Create(
  const wchar_t* name
  )
{
  return ON_NameHash::Create(ON_nil_uuid, name);
}

ON_NameHash ON_NameHash::Create(
  const wchar_t* name,
  bool bIgnoreCase
  )
{
  return ON_NameHash::Create(ON_nil_uuid, name, bIgnoreCase);
}

ON_NameHash ON_NameHash::Create(
  size_t length,
  const wchar_t* name
  )
{
  return ON_NameHash::Create(ON_nil_uuid, length, name);
}

ON_NameHash ON_NameHash::Create(
  size_t length,
  const wchar_t* name,
  bool bIgnoreCase
  )
{
  return ON_NameHash::Create(ON_nil_uuid, length, name, bIgnoreCase);
}

ON_NameHash ON_NameHash::Create(
  const ON_String& name
  )
{
  return ON_NameHash::Create(ON_nil_uuid, name);
}

ON_NameHash ON_NameHash::Create(
  const ON_String& name,
  bool bIgnoreCase
  )
{
  return ON_NameHash::Create(ON_nil_uuid, name, bIgnoreCase);
}

ON_NameHash ON_NameHash::Create(
  const char* name
  )
{
  return ON_NameHash::Create(ON_nil_uuid, name);
}

ON_NameHash ON_NameHash::Create(
  const char* name,
  bool bIgnoreCase
  )
{
  return ON_NameHash::Create(ON_nil_uuid, name, bIgnoreCase);
}

ON_NameHash ON_NameHash::Create(
  size_t length,
  const char* name
  )
{
  return ON_NameHash::Create(ON_nil_uuid, length, name);
}

ON_NameHash ON_NameHash::Create(
  size_t length,
  const char* name,
  bool bIgnoreCase
  )
{
  return ON_NameHash::Create(ON_nil_uuid, length, name, bIgnoreCase);
}

ON_NameHash ON_NameHash::Create(
  const ON_UUID& name_parent_id,
  const ON_wString& name
  )
{
  return ON_NameHash::Create(name_parent_id, name.UnsignedLength(), name.Array());
}

ON_NameHash ON_NameHash::Create(
  const ON_UUID& name_parent_id,
  const ON_wString& name,
  bool bIgnoreCase
  )
{
  return ON_NameHash::Create(name_parent_id, name.UnsignedLength(), name.Array(), bIgnoreCase);
}

ON_NameHash ON_NameHash::Create(
  const ON_UUID& name_parent_id,
  const wchar_t* name
  )
{
  return ON_NameHash::Create(name_parent_id, ON_wString::Length(name), name);
}

ON_NameHash ON_NameHash::Create(
  const ON_UUID& name_parent_id,
  const wchar_t* name,
  bool bIgnoreCase
  )
{
  return ON_NameHash::Create(name_parent_id, ON_wString::Length(name), name, bIgnoreCase);
}

bool ON_NameHash::IsFilePathHash() const
{
  return (m_flags == ON_NameHash::flags_file_path && m_sha1_hash != ON_SHA1_Hash::ZeroDigest);
}

ON_NameHash ON_NameHash::CreateFilePathHash(
  const class ON_FileReference& file_reference
  )
{
  ON_NameHash hash;
  if (file_reference.IsSet())
  {
    hash.m_flags = ON_NameHash::flags_file_path;
    hash.m_sha1_hash = file_reference.FullPathHash();
  }
  else
  {
    hash.m_sha1_hash = ON_SHA1_Hash::EmptyContentHash;
  }

  return hash;
}

ON_NameHash ON_NameHash::CreateFilePathHash(
  const wchar_t* file_path
  )
{
  ON_FileReference file_reference;
  file_reference.SetFullPath(file_path, false);
  return ON_NameHash::CreateFilePathHash(file_reference);
}

ON_NameHash ON_NameHash::CreateFilePathHash(
  const char* file_path
  )
{
  ON_FileReference file_reference;
  file_reference.SetFullPath(file_path, false);
  return ON_NameHash::CreateFilePathHash(file_reference);
}


void ON_SHA1::AccumulateString(
  const char* sUTF8,
  int element_count,
  ON_StringMapOrdinalType mapping
)
{
  const ON::endian context_endian = ON::Endian();
  ON__UINT32 sUTF32[64];
  const size_t sUTF32_capacity = sizeof(sUTF32)/sizeof(sUTF32[0]);
  unsigned int UTF32_length = 0;
  bool bEmpty = true;

  const int char_count
    = (nullptr != sUTF8 && element_count >= 0)
    ? element_count
    : ON_StringLengthUTF8(sUTF8);

  if ( char_count <= 0 )
    return;

  size_t length = (size_t)char_count;

  for (;;)
  {
    const char* next = nullptr;
    int UTF32_count = ON_ConvertUTF8ToUTF32(
      false,
      sUTF8,
      (int)length,
      sUTF32,
      sUTF32_capacity,
      nullptr,
      0xFFFFFFFFU,
      0xFFFD,
      &next
      );

    size_t parsed_length
      = (nullptr != next && next > sUTF8)
      ? (next - sUTF8)
      : 0;

    if (parsed_length <= 0 || parsed_length > length )
      break;

    if (UTF32_count > 0)
    {
      UTF32_length += ((unsigned int)UTF32_count);

      for (int i = 0; i < UTF32_count; i++)
      {
        if ( ON_StringMapOrdinalType::Identity != mapping )
          sUTF32[i] = ON_UnicodeMapCodePointOrdinal(mapping, sUTF32[i]);
        if ( 0 != sUTF32[i] )
          bEmpty = false;
      }

      const size_t sz = ((size_t)UTF32_count) * sizeof(sUTF32[0]);

      if (ON::endian::big_endian == context_endian)
      {
        // swap bytes so the SHA-1 value is independent of endian byte order
		    unsigned char* b = (unsigned char*)sUTF32;
        unsigned char* b1 = b + sz;
		    unsigned char  c;
		    while(b < b1) 
        {
			    c = b[0]; b[0] = b[3]; b[3] = c;
			    c = b[1]; b[1] = b[2]; b[2] = c;
			    b += sizeof(sUTF32[0]);
		    }
      }

      this->AccumulateBytes(sUTF32,sz);
    }

    sUTF8 += parsed_length;
    length -= parsed_length;
    if (0 == length)
      break;
  }
}

void ON_SHA1::AccumulateString(
  const class ON_String& str,
  ON_StringMapOrdinalType mapping
)
{
  // Do not permit corrupt strings to crash this code.
  str.IsValid(false);

  AccumulateString( str.Array(), str.Length(), mapping);
}

void ON_SHA1::AccumulateString(
  const class ON_String& str
)
{
  AccumulateString(str, ON_StringMapOrdinalType::Identity);
}

const ON_SHA1_Hash ON_StringContentHash(
  const char* sUTF8,
  int element_count,
  ON_StringMapOrdinalType mapping
)
{
  ON_SHA1 sha1;
  sha1.AccumulateString(sUTF8, element_count, mapping);
  return sha1.Hash();
}

void ON_SHA1::AccumulateString(
  const wchar_t* sWideString,
  int element_count,
  ON_StringMapOrdinalType mapping
)
{
  const ON::endian context_endian = ON::Endian();
  ON__UINT32 sUTF32[64];
  const size_t sUTF32_capacity = sizeof(sUTF32)/sizeof(sUTF32[0]);
  unsigned int UTF32_length = 0;
  bool bEmpty = true;

  const int wchar_count
    = (nullptr != sWideString && element_count >= 0)
    ? element_count
    : ON_StringLengthWideChar(sWideString);

  if ( wchar_count <= 0 )
    return;

  size_t length = (size_t)wchar_count;

  for (;;)
  {
    const wchar_t* next = nullptr;
    int UTF32_count = ON_ConvertWideCharToUTF32(
      false,
      sWideString,
      (int)length,
      sUTF32,
      sUTF32_capacity,
      nullptr,
      0xFFFFFFFFU,
      0xFFFD,
      &next
      );

    size_t parsed_length
      = (nullptr != next && next > sWideString)
      ? (next - sWideString)
      : 0;

    if (parsed_length <= 0 || parsed_length > length )
      break;

    if (UTF32_count > 0)
    {
      UTF32_length += ((unsigned int)UTF32_count);

      for (int i = 0; i < UTF32_count; i++)
      {
        if ( ON_StringMapOrdinalType::Identity != mapping )
          sUTF32[i] = ON_UnicodeMapCodePointOrdinal(mapping, sUTF32[i]);
        if ( 0 != sUTF32[i] )
          bEmpty = false;
      }

      const size_t sz = ((size_t)UTF32_count) * sizeof(sUTF32[0]);

      if (ON::endian::big_endian == context_endian)
      {
        // swap bytes so the SHA-1 value is independent of endian byte order
		    unsigned char* b = (unsigned char*)sUTF32;
        unsigned char* b1 = b + sz;
		    unsigned char  c;
		    while(b < b1) 
        {
			    c = b[0]; b[0] = b[3]; b[3] = c;
			    c = b[1]; b[1] = b[2]; b[2] = c;
			    b += sizeof(sUTF32[0]);
		    }
      }

      this->AccumulateBytes(sUTF32,sz);
    }

    sWideString += parsed_length;
    length -= parsed_length;
    if (0 == length)
      break;
  }
}

void ON_SHA1::AccumulateString(
  const class ON_wString& str,
  ON_StringMapOrdinalType mapping
)
{
  // Do not permit corrupt strings to crash this code.
  str.IsValid(false);

  AccumulateString( str.Array(), str.Length(), mapping);
}

void ON_SHA1::AccumulateString(
  const class ON_wString& str
)
{
  AccumulateString(str, ON_StringMapOrdinalType::Identity);
}

const ON_SHA1_Hash ON_StringContentHash(
  const wchar_t* sWideString,
  int element_count,
  ON_StringMapOrdinalType mapping
)
{
  ON_SHA1 sha1;
  sha1.AccumulateString(sWideString, element_count, mapping);
  return sha1.Hash();
}


const ON_SHA1_Hash ON_String::ContentHash(
  ON_StringMapOrdinalType mapping
) const
{
  const char* sUTF8 = this->Array();
  int length = this->Length();
  return ON_StringContentHash(sUTF8, length, mapping);
}

const ON_SHA1_Hash ON_wString::ContentHash(
  ON_StringMapOrdinalType mapping
) const
{
  const wchar_t* sWideString = this->Array();
  int length = this->Length();
  return ON_StringContentHash(sWideString, length, mapping);
}


ON_NameHash ON_NameHash::Create(
  const ON_UUID& name_parent_id,
  size_t length,
  const wchar_t* name
)
{
  const bool bIgnoreCase = true;
  return ON_NameHash::Create(name_parent_id, length, name, bIgnoreCase);
}

ON_NameHash ON_NameHash::Create(
  const ON_UUID& name_parent_id,
  size_t length, 
  const wchar_t* name,
  bool bIgnoreCase
  )
{
  ON_NameHash hash;

  if (0 == length || nullptr == name)
  {
    // Do not return ON_NameHash::EmptyNameHash because
    // this code is used to initialize that static member.
    hash.m_sha1_hash = ON_SHA1_Hash::EmptyContentHash;
    return hash;
  }
  
  if (false == ON_ModelComponent::IsValidComponentName(name))
    return ON_NameHash::UnsetNameHash;

  const ON::endian context_endian = ON::Endian();
  ON__UINT32 sUTF32[64];
  const size_t sUTF32_capacity = sizeof(sUTF32)/sizeof(sUTF32[0]);
  unsigned int UTF32_length = 0;
  bool bEmpty = true;
  ON_SHA1 sha1;

  for (;;)
  {
    const wchar_t* next = nullptr;
    int UTF32_count = ON_ConvertWideCharToUTF32(
      false,
      name,
      (int)length,
      sUTF32,
      sUTF32_capacity,
      nullptr,
      0xFFFFFFFFU,
      0xFFFD,
      &next
      );

    size_t parsed_length
      = (nullptr != next && next > name)
      ? (next - name)
      : 0;

    if (parsed_length <= 0 || parsed_length > length )
      break;

    if (UTF32_count > 0)
    {
      UTF32_length += ((unsigned int)UTF32_count);

      if (bEmpty)
      {
        for (int i = 0; i < UTF32_count; i++)
        {
          if (0 != sUTF32[i])
          {
            bEmpty = false;
            break;
          }
        }
      }

      if (bIgnoreCase)
      {
        for (int i = 0; i < UTF32_count; i++)
        {
          if (ON_IsUnicodeSpaceCodePoint(sUTF32[i]))
            sUTF32[i] = ON_UnicodeCodePoint::ON_Space;
          else
            sUTF32[i] = ON_UnicodeMapCodePointOrdinal(ON_StringMapOrdinalType::MinimumOrdinal, sUTF32[i]);
        }
      }
      else
      {
        for (int i = 0; i < UTF32_count; i++)
        {
          if (ON_IsUnicodeSpaceCodePoint(sUTF32[i]))
            sUTF32[i] = ON_UnicodeCodePoint::ON_Space;
        }
      }

      const size_t sz = ((size_t)UTF32_count) * sizeof(sUTF32[0]);

      if (ON::endian::big_endian == context_endian)
      {
        // swap bytes so the SHA-1 value is independent of endian byte order
		    unsigned char* b = (unsigned char*)sUTF32;
        unsigned char* b1 = b + sz;
		    unsigned char  c;
		    while(b < b1) 
        {
			    c = b[0]; b[0] = b[3]; b[3] = c;
			    c = b[1]; b[1] = b[2]; b[2] = c;
			    b += sizeof(sUTF32[0]);
		    }
      }

      sha1.AccumulateBytes(sUTF32,sz);
    }

    name += parsed_length;
    length -= parsed_length;
    if (0 == length)
      break;
  }

  if ( bEmpty )
    return ON_NameHash::EmptyNameHash;

  hash.m_parent_id = name_parent_id;
  hash.m_flags = (UTF32_length & ON_NameHash::flags_length_mask);
  if (false == bIgnoreCase)
    hash.m_flags |= ON_NameHash::flags_case_sensitive;
  hash.m_sha1_hash = sha1.Hash();

  return hash;
}

ON_NameHash ON_NameHash::Create(
  const ON_UUID& name_parent_id,
  const ON_String& name
  )
{
  return ON_NameHash::Create(name_parent_id,(size_t)name.Length(), name.Array());
}


ON_NameHash ON_NameHash::Create(
  const ON_UUID& name_parent_id,
  const ON_String& name,
  bool bIgnoreCase
  )
{
  return ON_NameHash::Create(name_parent_id,(size_t)name.Length(), name.Array(), bIgnoreCase);
}

ON_NameHash ON_NameHash::Create(
  const ON_UUID& name_parent_id,
  const char* name
  )
{
  return ON_NameHash::Create(name_parent_id,ON_String::Length(name), name);
}

ON_NameHash ON_NameHash::Create(
  const ON_UUID& name_parent_id,
  const char* name,
  bool bIgnoreCase
  )
{
  return ON_NameHash::Create(name_parent_id,ON_String::Length(name), name, bIgnoreCase);
}


ON_NameHash ON_NameHash::Create(
  const ON_UUID& name_parent_id,
  size_t length,
  const char* name
)
{
  const bool bIgnoreCase = true;
  return ON_NameHash::Create( name_parent_id, length, name, bIgnoreCase);
}

ON_NameHash ON_NameHash::Create(
  const ON_UUID& name_parent_id,
  size_t length, 
  const char* name,
  bool bIgnoreCase
  )
{
  const ON::endian context_endian = ON::Endian();

  ON_NameHash hash;
  if (length <= 0 || nullptr == name)
  {
    // Do not return ON_NameHash::EmptyNameHash because
    // this code is used to initialize that static member.
    hash.m_sha1_hash = ON_SHA1_Hash::EmptyContentHash;
    return hash;
  }

  ON__UINT32 sUTF32[64];
  const size_t sUTF32_capacity = sizeof(sUTF32)/sizeof(sUTF32[0]);
  unsigned int UTF32_length = 0;
  bool bEmpty = true;
  ON_SHA1 sha1;

  for (;;)
  {
    const char* next = nullptr;
    int UTF32_count = ON_ConvertUTF8ToUTF32(
      false,
      name,
      (int)length,
      sUTF32,
      sUTF32_capacity,
      nullptr,
      0xFFFFFFFFU,
      0xFFFD,
      &next
      );

    size_t parsed_length
      = (nullptr != next && next > name)
      ? (next - name)
      : 0;

    if (parsed_length <= 0 || parsed_length > length )
      break;

    if (UTF32_count > 0)
    {
      UTF32_length += ((unsigned int)UTF32_count);

      if (bEmpty)
      {
        for (int i = 0; i < UTF32_count; i++)
        {
          if (0 != sUTF32[i])
          {
            bEmpty = false;
            break;
          }
        }
      }

      if (bIgnoreCase)
      {
        for (int i = 0; i < UTF32_count; i++)
        {
          sUTF32[i] = ON_UnicodeMapCodePointOrdinal(ON_StringMapOrdinalType::MinimumOrdinal, sUTF32[i]);
        }
      }

      if (ON::endian::big_endian == context_endian)
      {
        // swap bytes so the SHA-1 value is independent of endian byte order
		    unsigned char* b = (unsigned char*)sUTF32;
        unsigned char* b1 = b + UTF32_length*sizeof(sUTF32[0]);
		    unsigned char  c;
		    while(b < b1) 
        {
			    c = b[0]; b[0] = b[3]; b[3] = c;
			    c = b[1]; b[1] = b[2]; b[2] = c;
			    b += sizeof(sUTF32[0]);
		    }
      }

      sha1.AccumulateBytes(sUTF32,UTF32_length*sizeof(sUTF32[0]));
    }

    name += parsed_length;
    length -= parsed_length;
    if (0 == length)
      break;
  }

  if ( bEmpty )
    return ON_NameHash::EmptyNameHash;

  hash.m_parent_id = name_parent_id;
  hash.m_flags = (UTF32_length & ON_NameHash::flags_length_mask);
  if (false == bIgnoreCase)
    hash.m_flags |= ON_NameHash::flags_case_sensitive;
  hash.m_sha1_hash = sha1.Hash();

  return hash;
}

ON_NameHash ON_NameHash::CreateIdAndEmptyName(
  const ON_UUID& parent_id
  )
{
  ON_NameHash hash;
  hash.m_sha1_hash = ON_SHA1_Hash::EmptyContentHash;
  hash.m_parent_id = parent_id;
  return hash;
}

ON_NameHash ON_NameHash::CreateIdAndUnsetName(
  const ON_UUID& parent_id
  )
{
  ON_NameHash hash;
  hash.m_sha1_hash = ON_SHA1_Hash::ZeroDigest;
  hash.m_parent_id = parent_id;
  return hash;
}

ON_NameHash ON_NameHash::Internal_DotNetInterfaceSet(
  const ON_UUID& parent_id,
  const ON_SHA1_Hash& sha1_hash,
  const ON__UINT32 flags
)
{
  // The parent_id, sha1_hash and flags values must be exact 
  // copies of values saved from a valid instance of 
  // a ON_NameHash instantiation.
  // Any other use will likely result in the creation of an invalid ON_NameHash class.
  ON_NameHash hash;
  hash.m_flags = flags;
  hash.m_sha1_hash = sha1_hash;
  hash.m_parent_id = parent_id;
  return hash;
}

ON__UINT32 ON_NameHash::Internal_DotNetInterfaceGetFlags() const
{
  return m_flags;
}

class ON_ComponentManifestItem_PRIVATE : public ON_ComponentManifestItem
{
public:
  ON_ComponentManifestItem_PRIVATE() = default;
  ~ON_ComponentManifestItem_PRIVATE() = default;
  ON_ComponentManifestItem_PRIVATE(const ON_ComponentManifestItem_PRIVATE&) = default;
  ON_ComponentManifestItem_PRIVATE& operator=(const ON_ComponentManifestItem_PRIVATE&) = default;

  ON_ComponentManifestItem_PRIVATE(
    const ON_ComponentManifestItem& item
    )
    : ON_ComponentManifestItem(item)
  {}

public:
  unsigned int m_manifest_table_sn = 0;
  unsigned int m_manifest_impl_sn = 0;
  ON_ComponentManifestItem_PRIVATE* m_next = nullptr;
  ON_ComponentManifestItem_PRIVATE* m_prev = nullptr;
};

class ON_ComponentManifestHash32TableItem : public ON_Hash32TableItem
{
public:
  const ON_ComponentManifestItem_PRIVATE* m_manifest_item = nullptr;
};

class ON_ManifestHash32TableItemFixedSizePool : private ON_FixedSizePool
{
public:
  ON_ManifestHash32TableItemFixedSizePool() = default;
  ~ON_ManifestHash32TableItemFixedSizePool() = default;
private:
  ON_ManifestHash32TableItemFixedSizePool(const ON_ManifestHash32TableItemFixedSizePool&) = delete;
  ON_ManifestHash32TableItemFixedSizePool& operator=(const ON_ManifestHash32TableItemFixedSizePool&) = delete;

public:
  class ON_ComponentManifestHash32TableItem* AllocateHashTableItem(const ON_ComponentManifestItem_PRIVATE* manifest_item)
  {
    if (0 == this->SizeofElement())
      Create(sizeof(ON_ComponentManifestHash32TableItem),0,0);
    // Must use AllocateElement() instead of AllocateDirtyElement() because the actual item 
    // may be derived from ON_ComponentManifestHash32TableItem.
    ON_ComponentManifestHash32TableItem* hash_table_item = (ON_ComponentManifestHash32TableItem*)AllocateElement();
    hash_table_item->m_manifest_item = manifest_item;
    return hash_table_item;
  }

  void ReturnHashTableItem(
  class ON_ComponentManifestHash32TableItem* hash_table_item
    )
  {
    if (nullptr != hash_table_item)
    {
      hash_table_item->m_manifest_item = nullptr;
      ReturnElement(hash_table_item);
    }
  }
};

class ON_ComponentNameHash32Table : private ON_Hash32Table
{
public:
  ON_ComponentNameHash32Table(
    ON_ManifestHash32TableItemFixedSizePool& fsp
    )
    : m_fsp(fsp)
  {}

  ~ON_ComponentNameHash32Table() = default;

private:
  ON_ComponentNameHash32Table() = delete;
  ON_ComponentNameHash32Table(const ON_ComponentNameHash32Table&) = delete;
  ON_ComponentNameHash32Table& operator=(const ON_ComponentNameHash32Table&) = delete;

private:
  ON_ManifestHash32TableItemFixedSizePool& m_fsp;

  static ON__UINT32 Hash32(
    ON_ModelComponent::Type component_type,
    const ON_NameHash& name_hash
    )
  {
    // Using the static_cast<unsigned int>(component_type) as the seed 
    // is done so objects of different types with the same name will
    // generally have a different 32-bit hash.
    return name_hash.DataCRC(static_cast<unsigned int>(component_type));
  }

  static ON__UINT32 Hash32(
    const ON_ComponentManifestItem& manifest_item
    )
  {
    return Hash32(manifest_item.ComponentType(),manifest_item.NameHash());
  }

public:
  const ON_ComponentManifestHash32TableItem* AddManifestItem(
    const class ON_ComponentManifestItem_PRIVATE* manifest_item
    )
  {
    if (nullptr != manifest_item && manifest_item->NameHash().IsValidAndNotEmpty() )
    {
      ON_ComponentManifestHash32TableItem* hash_table_item = m_fsp.AllocateHashTableItem(manifest_item);
      ON__UINT32 hash32 = ON_ComponentNameHash32Table::Hash32(*manifest_item);
      if ( AddItem( hash32, hash_table_item ) )
        return hash_table_item;
      m_fsp.ReturnHashTableItem(hash_table_item);
    }
    return nullptr;
  }

  bool RemoveManifestItem(
    ON__UINT32 hash32,
    const class ON_ComponentManifestItem_PRIVATE* manifest_item
    )
  {
    if ( nullptr != manifest_item )
    {
      for (const ON_Hash32TableItem* hash_table_item = FirstItemWithHash(hash32); nullptr != hash_table_item; hash_table_item = NextItemWithHash(hash_table_item))
      {
        if (manifest_item == ((const ON_ComponentManifestHash32TableItem*)hash_table_item)->m_manifest_item)
        {
          if (RemoveItem(const_cast<ON_Hash32TableItem*>(hash_table_item)))
          {
            m_fsp.ReturnHashTableItem((ON_ComponentManifestHash32TableItem*)hash_table_item);
            return true;
          }
        }
      }
    }
    return false;
  }

  bool RemoveManifestItem(
    const class ON_ComponentManifestItem_PRIVATE* manifest_item
    )
  {
    if ( nullptr != manifest_item && manifest_item->NameHash().IsValidAndNotEmpty() )
      return RemoveManifestItem(Hash32(*manifest_item),manifest_item);
    return false;
  }

  const ON_ComponentManifestHash32TableItem* FirstManifestItemWithName(
    ON_ModelComponent::Type component_type,
    const ON_NameHash& name_hash
    ) const
  {
    if (false == name_hash.IsValidAndNotEmpty())
      return nullptr;
    const ON__UINT32 hash32 = ON_ComponentNameHash32Table::Hash32(component_type,name_hash);
    for (const ON_Hash32TableItem* hash_table_item = FirstItemWithHash(hash32); nullptr != hash_table_item; hash_table_item = NextItemWithHash(hash_table_item))
    {
      const ON_ComponentManifestItem_PRIVATE* manifest_item = static_cast<const ON_ComponentManifestHash32TableItem*>(hash_table_item)->m_manifest_item;
      if (component_type == manifest_item->ComponentType() && name_hash == manifest_item->NameHash() )
        return (const ON_ComponentManifestHash32TableItem*)hash_table_item;
    }
    return nullptr;
  }

  bool NameInUse(
    ON_ModelComponent::Type component_type,
    const ON_NameHash& name_hash,
    bool bIgnoreParentId
    ) const
  {
    // Do not test "system" component names.
    // They can generally be reused by model components.
    if (false == name_hash.IsValidAndNotEmpty())
      return false;

    if (false == bIgnoreParentId || false == ON_ModelComponent::UniqueNameIncludesParent(component_type))
      return (nullptr != FirstManifestItemWithName(component_type,name_hash));

    // slow search when parent id must be ignored (layer names for example)
    for (const ON_Hash32TableItem* hash_table_item = FirstTableItem(); nullptr != hash_table_item; hash_table_item = NextTableItem(hash_table_item))
    {
      const ON_ComponentManifestItem_PRIVATE* manifest_item = static_cast<const ON_ComponentManifestHash32TableItem*>(hash_table_item)->m_manifest_item;
      if (component_type == manifest_item->ComponentType() && ON_NameHash::CompareNameSHA1(name_hash,manifest_item->NameHash()) )
        return true;
    }
    return false;
  }

  const ON_ComponentManifestHash32TableItem* NextManifestItemWithName(
    const ON_ComponentManifestHash32TableItem* current_manifest_item
    ) const
  {
    if ( nullptr == current_manifest_item || nullptr == current_manifest_item->m_manifest_item )
      return nullptr;
    const ON_NameHash name_hash = current_manifest_item->m_manifest_item->NameHash();
    if ( false == name_hash.IsValidAndNotEmpty() )
      return nullptr;
    const ON_ModelComponent::Type component_type = current_manifest_item->m_manifest_item->ComponentType();
    for (const ON_Hash32TableItem* hash_table_item = NextItemWithHash(current_manifest_item); nullptr != hash_table_item; hash_table_item = NextItemWithHash(hash_table_item))
    {
      if ( component_type == ((const ON_ComponentManifestHash32TableItem*)hash_table_item)->m_manifest_item->ComponentType()
        && name_hash == ((const ON_ComponentManifestHash32TableItem*)hash_table_item)->m_manifest_item->NameHash() 
        )
        return (const ON_ComponentManifestHash32TableItem*)hash_table_item;
    }
    return nullptr;
  }
};


class ON_ComponentIdHash32Table : private ON_Hash32Table
{
public:
  ON_ComponentIdHash32Table(
    ON_ManifestHash32TableItemFixedSizePool& fsp
    )
    : m_fsp(fsp)
  {}

  ~ON_ComponentIdHash32Table() = default;

private:
  ON_ComponentIdHash32Table() = delete;
  ON_ComponentIdHash32Table(const ON_ComponentIdHash32Table&) = delete;
  ON_ComponentIdHash32Table& operator=(const ON_ComponentIdHash32Table&) = delete;

private:
  static ON_UUID IdFromManifestItem(
    const class ON_ComponentManifestItem* manifest_item
    ) 
  {
    return (nullptr != manifest_item) ? manifest_item->Id() : ON_nil_uuid;
  }

private:
  static ON__UINT32 IdHash32(
    const ON_UUID& id
    )
  {
    return ON_CRC32(0, sizeof(ON_UUID), &id);
  }

  ON_ManifestHash32TableItemFixedSizePool& m_fsp;

public:
  unsigned int ItemCount() const
  {
    return ON_Hash32Table::ItemCount();
  }

  const ON_ComponentManifestHash32TableItem* AddManifestItem(
    const class ON_ComponentManifestItem_PRIVATE* manifest_item
    )
  {
    const ON_UUID id = IdFromManifestItem(manifest_item);
    if ( ON_nil_uuid == id )
      return nullptr;
    const ON__UINT32 hash32 = ON_ComponentIdHash32Table::IdHash32(id);
    
    ON_ComponentManifestHash32TableItem* hash_table_item = m_fsp.AllocateHashTableItem(manifest_item);
    if ( AddItem( hash32, hash_table_item ) )
      return hash_table_item;

    m_fsp.ReturnHashTableItem(hash_table_item);
    return nullptr;
  }

  bool RemoveManifestItem(
    const class ON_ComponentManifestItem_PRIVATE* manifest_item
    )
  {
    const ON_UUID id = IdFromManifestItem(manifest_item);
    if ( ON_nil_uuid == id )
      return false;
    const ON__UINT32 hash32 = ON_ComponentIdHash32Table::IdHash32(id);

    for (const ON_Hash32TableItem* hash_table_item = FirstItemWithHash(hash32); nullptr != hash_table_item; hash_table_item = NextItemWithHash(hash_table_item))
    {
      if (manifest_item == ((const ON_ComponentManifestHash32TableItem*)hash_table_item)->m_manifest_item)
      {
        if (RemoveItem(const_cast<ON_Hash32TableItem*>(hash_table_item)))
        {
          m_fsp.ReturnHashTableItem((ON_ComponentManifestHash32TableItem*)hash_table_item);
          return true;
        }
      }
    }

    return false;
  }

  const ON_ComponentManifestHash32TableItem* FirstManifestItemWithId(
    ON_UUID id
    ) const
  {
    if (ON_nil_uuid == id)
      return nullptr;
    const ON__UINT32 hash32 = ON_ComponentIdHash32Table::IdHash32(id);
    for (const ON_Hash32TableItem* hash_table_item = FirstItemWithHash(hash32); nullptr != hash_table_item; hash_table_item = NextItemWithHash(hash_table_item))
    {
      if (id == IdFromManifestItem(((const ON_ComponentManifestHash32TableItem*)hash_table_item)->m_manifest_item) )
        return (const ON_ComponentManifestHash32TableItem*)hash_table_item;
    }
    return nullptr;
  }

  const ON_ComponentManifestHash32TableItem* NextManifestItemWithId(
    const ON_ComponentManifestHash32TableItem* current_manifest_item
    ) const
  {
    if ( nullptr == current_manifest_item)
      return nullptr;
    const ON_UUID id = IdFromManifestItem(current_manifest_item->m_manifest_item);
    if ( ON_nil_uuid == id )
      return nullptr;
    for (const ON_Hash32TableItem* hash_table_item = NextItemWithHash(current_manifest_item); nullptr != hash_table_item; hash_table_item = NextItemWithHash(hash_table_item))
    {
      if (id == IdFromManifestItem(((const ON_ComponentManifestHash32TableItem*)hash_table_item)->m_manifest_item) )
        return (const ON_ComponentManifestHash32TableItem*)hash_table_item;
    }
    return nullptr;
  }
};

//////////////////////////////////////////////////////////////////////////////////////
//
// ON_ManifestMap hash table tools
//

bool operator==(const ON_ManifestMapItem& lhs, const ON_ManifestMapItem& rhs)
{
  return (0 == ON_ManifestMapItem::Compare(lhs, rhs));
}

bool operator!=(const ON_ManifestMapItem& lhs, const ON_ManifestMapItem& rhs)
{
  return (0 != ON_ManifestMapItem::Compare(lhs, rhs));
}

int ON_ManifestMapItem::Compare(
  const ON_ManifestMapItem& a,
  const ON_ManifestMapItem& b)
{
  int rc = ON_ManifestMapItem::CompareTypeAndSourceIndex(a, b);
  if (0 != rc)
    return rc;
  rc = ON_ManifestMapItem::CompareTypeAndDestinationIndex(a, b);
  if (0 != rc)
    return rc;
  rc = ON_UuidCompare(a.m_source_id, b.m_source_id);
  if (0 != rc)
    return rc;
  return ON_UuidCompare(a.m_destination_id, b.m_destination_id);
}


int ON_ManifestMapItem::CompareTypeAndSourceId(
  const ON_ManifestMapItem& a,
  const ON_ManifestMapItem& b
  )
{
  const unsigned int at = static_cast<unsigned int>(a.m_component_type);
  const unsigned int bt = static_cast<unsigned int>(b.m_component_type);
  if (at < bt)
    return -1;
  if (at > bt)
    return 1;
  return ON_UuidCompare(a.m_source_id, b.m_source_id);
}

int ON_ManifestMapItem::CompareTypeAndDestinationId(
  const ON_ManifestMapItem& a,
  const ON_ManifestMapItem& b
  )
{
  const unsigned int at = static_cast<unsigned int>(a.m_component_type);
  const unsigned int bt = static_cast<unsigned int>(b.m_component_type);
  if (at < bt)
    return -1;
  if (at > bt)
    return 1;
  return ON_UuidCompare(a.m_destination_id, b.m_destination_id);
}

int ON_ManifestMapItem::CompareTypeAndSourceIdAndIndex(
  const ON_ManifestMapItem& a,
  const ON_ManifestMapItem& b
  )
{
  const unsigned int at = static_cast<unsigned int>(a.m_component_type);
  const unsigned int bt = static_cast<unsigned int>(b.m_component_type);
  if (at < bt)
    return -1;
  if (at > bt)
    return 1;
  if (a.m_source_index < b.m_source_index)
    return -1;
  if (a.m_source_index > b.m_source_index)
    return 1;
  return ON_UuidCompare(a.m_source_id, b.m_source_id);
}

int ON_ManifestMapItem::CompareTypeAndDestinationIdAndIndex(
  const ON_ManifestMapItem& a,
  const ON_ManifestMapItem& b
  )
{
  const unsigned int at = static_cast<unsigned int>(a.m_component_type);
  const unsigned int bt = static_cast<unsigned int>(b.m_component_type);
  if (at < bt)
    return -1;
  if (at > bt)
    return 1;
  if (a.m_destination_index < b.m_destination_index)
    return -1;
  if (a.m_destination_index > b.m_destination_index)
    return 1;
  return ON_UuidCompare(a.m_destination_id, b.m_destination_id);
}


int ON_ManifestMapItem::CompareTypeAndSourceIndex(
  const ON_ManifestMapItem& a,
  const ON_ManifestMapItem& b)
{
  const unsigned int at = static_cast<unsigned int>(a.m_component_type);
  const unsigned int bt = static_cast<unsigned int>(b.m_component_type);
  if (at < bt)
    return -1;
  if (at > bt)
    return 1;
  if (a.m_source_index < b.m_source_index)
    return -1;
  if (a.m_source_index > b.m_source_index)
    return 1;
  return 0;
}

int ON_ManifestMapItem::CompareTypeAndDestinationIndex(
  const ON_ManifestMapItem& a,
  const ON_ManifestMapItem& b)
{
  const unsigned int at = static_cast<unsigned int>(a.m_component_type);
  const unsigned int bt = static_cast<unsigned int>(b.m_component_type);
  if (at < bt)
    return -1;
  if (at > bt)
    return 1;
  if (a.m_destination_index < b.m_destination_index)
    return -1;
  if (a.m_destination_index > b.m_destination_index)
    return 1;
  return 0;
}

ON__UINT32 ON_ManifestMapItem::SourceIdHash32(
  const ON_UUID& source_component_id
  )
{
  return ON_CRC32(0, sizeof(ON_UUID), &source_component_id);
}

ON__UINT32 ON_ManifestMapItem::SourceIndexHash32(
  ON_ModelComponent::Type component_type,
  int source_component_index
  )
{
  ON__UINT32 hash32 = ON_CRC32(0, sizeof(component_type), &component_type);
  hash32 = ON_CRC32(hash32, sizeof(source_component_index), &source_component_index);
  return hash32;
}

bool ON_ManifestMapItem::SourceIsSet() const
{
  if (ON_ModelComponent::Type::Unset == m_component_type)
    return false;
  if (ON_nil_uuid == m_source_id)
    return false;
  if (ON_ModelComponent::IndexRequired(m_component_type) && ON_UNSET_INT_INDEX == m_source_index)
    return false;
  return true;
}

bool ON_ManifestMapItem::SourceIsUnset() const
{
  return SourceIsSet() ? false : true;
}

bool ON_ManifestMapItem::DestinationIsSet() const
{
  if (ON_ModelComponent::Type::Unset == m_component_type)
    return false;
  if (ON_nil_uuid == m_destination_id)
    return false;
  if (ON_ModelComponent::IndexRequired(m_component_type) && ON_UNSET_INT_INDEX == m_destination_index)
    return false;
  return true;
}

bool ON_ManifestMapItem::DestinationIsUnset() const
{
  return DestinationIsSet() ? false : true;
}

bool ON_ManifestMapItem::SourceAndDestinationAreSet() const
{
  if (ON_ModelComponent::Type::Unset == m_component_type)
    return false;
  if (ON_nil_uuid == m_source_id)
    return false;
  if (ON_nil_uuid == m_destination_id)
    return false;
  if (ON_ModelComponent::IndexRequired(m_component_type))
  {
    if (ON_UNSET_INT_INDEX == m_source_index)
      return false;
    if (ON_UNSET_INT_INDEX == m_destination_index)
      return false;
  }
  return true;
}

bool ON_ManifestMapItem::SourceOrDestinationIsUnset() const
{
  return SourceAndDestinationAreSet() ? false : true;
}

class ON_ManifestMap_Hash32TableItem : public ON_Hash32TableItem
{
public:
  ON_ManifestMap_Hash32TableItem() = default;
  ~ON_ManifestMap_Hash32TableItem() = default;
  ON_ManifestMap_Hash32TableItem(const ON_ManifestMap_Hash32TableItem&) = default;
  ON_ManifestMap_Hash32TableItem& operator=(const ON_ManifestMap_Hash32TableItem&) = default;

public:
  ON_ManifestMapItem m_map_item;
};

/*
ON_ManifestMap_Hash32TableItemFixedSizePool is used to allocate hash table items for 
ON_ManifestMap_Hash32Table,
ON_ManifestMap_SourceIdHash32Table, and ON_ManifestMap_SourceIndexHash32Table
*/
class ON_ManifestMap_Hash32TableItemFixedSizePool : public ON_FixedSizePool
{
public:
  ON_ManifestMap_Hash32TableItemFixedSizePool() = default;
  ~ON_ManifestMap_Hash32TableItemFixedSizePool() = default;
private:
  ON_ManifestMap_Hash32TableItemFixedSizePool(const ON_ManifestMap_Hash32TableItemFixedSizePool&) = delete;
  ON_ManifestMap_Hash32TableItemFixedSizePool& operator=(const ON_ManifestMap_Hash32TableItemFixedSizePool&) = delete;

public:
  class ON_ManifestMap_Hash32TableItem* AllocateHashTableItem(
    const ON_ManifestMapItem& map_item
    )
  {
    if (0 == this->SizeofElement())
      Create(sizeof(ON_ManifestMap_Hash32TableItem),0,0);
    // Must use AllocateElement() instead of AllocateDirtyElement() because the actual item 
    // may be derived from ON_ComponentManifestHash32TableItem.
    ON_ManifestMap_Hash32TableItem* hash_table_item = (ON_ManifestMap_Hash32TableItem*)AllocateElement();
    hash_table_item->m_map_item = map_item;
    return hash_table_item;
  }

  void ReturnHashTableItem(
    class ON_ManifestMap_Hash32TableItem* hash_table_item
    )
  {
    if (nullptr != hash_table_item)
    {
      hash_table_item->m_map_item = ON_ManifestMapItem::Unset;
      ReturnElement(hash_table_item);
    }
  }
};


/*
ON_ManifestMap_Hash32Table is a pure virtual base class for
ON_ManifestMap_SourceIdHash32Table and ON_ManifestMap_SourceIndexHash32Table
*/
class ON_ManifestMap_Hash32Table : public ON_Hash32Table
{
protected:
  ON_ManifestMap_Hash32Table(ON_ManifestMap_Hash32TableItemFixedSizePool& fsp)
    :m_fsp(fsp)
  {}
  
  virtual ~ON_ManifestMap_Hash32Table() {} // = default;

private:
  ON_ManifestMap_Hash32Table() = delete;
  ON_ManifestMap_Hash32Table(const ON_ManifestMap_Hash32Table&) = delete;
  ON_ManifestMap_Hash32Table& operator=(const ON_ManifestMap_Hash32Table&) = delete;

protected:
  virtual ON__UINT32 MapItemHash32(
    const class ON_ManifestMapItem& map_item
    ) const = 0;

public:
  const ON_ManifestMap_Hash32TableItem* AddManifestMapItem(
    const ON_ManifestMapItem& map_item
    )
  {
    ON_ManifestMap_Hash32TableItem* hash_table_item = m_fsp.AllocateHashTableItem(map_item);
    const ON__UINT32 hash32 = MapItemHash32(hash_table_item->m_map_item);
    if (AddItem(hash32, hash_table_item))
      return hash_table_item;

    m_fsp.ReturnHashTableItem(hash_table_item);
    return nullptr;
  }

private:
  ON_ManifestMap_Hash32TableItemFixedSizePool& m_fsp;
};

class ON_ManifestMap_SourceIdHash32Table : public ON_ManifestMap_Hash32Table
{
public:
  ON_ManifestMap_SourceIdHash32Table(ON_ManifestMap_Hash32TableItemFixedSizePool& fsp)
    :ON_ManifestMap_Hash32Table(fsp)
  {}
  ~ON_ManifestMap_SourceIdHash32Table() = default;

private:
  ON_ManifestMap_SourceIdHash32Table() = delete;
  ON_ManifestMap_SourceIdHash32Table(const ON_ManifestMap_SourceIdHash32Table&) = delete;
  ON_ManifestMap_SourceIdHash32Table& operator=(const ON_ManifestMap_SourceIdHash32Table&) = delete;

protected:
    ON__UINT32 MapItemHash32(
      const class ON_ManifestMapItem& map_item
      ) const override
    {
      return ON_ManifestMapItem::SourceIdHash32(map_item.SourceId());
    }

public:
  const ON_ManifestMap_Hash32TableItem* FirstManifestMapItemWithSourceId(
    ON_UUID source_component_id
    ) const
  {
    if (ON_nil_uuid == source_component_id)
      return nullptr;
    const ON__UINT32 hash32 = ON_ManifestMapItem::SourceIdHash32(source_component_id);
    for (const ON_Hash32TableItem* hash_table_item = FirstItemWithHash(hash32); nullptr != hash_table_item; hash_table_item = NextItemWithHash(hash_table_item))
    {
      if (source_component_id == ((const ON_ManifestMap_Hash32TableItem*)hash_table_item)->m_map_item.SourceId() )
        return (const ON_ManifestMap_Hash32TableItem*)hash_table_item;
    }
    return nullptr;
  }

  const ON_ManifestMap_Hash32TableItem* NextManifestMapItemWithSourceId(
    const ON_ManifestMap_Hash32TableItem* current_manifest_item
    ) const
  {
    if ( nullptr == current_manifest_item)
      return nullptr;
    const ON_UUID source_component_id = current_manifest_item->m_map_item.SourceId();
    if ( ON_nil_uuid == source_component_id )
      return nullptr;
    for (const ON_Hash32TableItem* hash_table_item = NextItemWithHash(current_manifest_item); nullptr != hash_table_item; hash_table_item = NextItemWithHash(hash_table_item))
    {
      if (source_component_id == ((const ON_ManifestMap_Hash32TableItem*)hash_table_item)->m_map_item.SourceId() )
        return (const ON_ManifestMap_Hash32TableItem*)hash_table_item;
    }
    return nullptr;
  }
};


class ON_ManifestMap_SourceIndexHash32Table : public ON_ManifestMap_Hash32Table
{
public:
  ON_ManifestMap_SourceIndexHash32Table(ON_ManifestMap_Hash32TableItemFixedSizePool& fsp)
    :ON_ManifestMap_Hash32Table(fsp)
  {}
  virtual ~ON_ManifestMap_SourceIndexHash32Table() {} // = default;

private:
  ON_ManifestMap_SourceIndexHash32Table() = delete;
  ON_ManifestMap_SourceIndexHash32Table(const ON_ManifestMap_SourceIndexHash32Table&) = delete;
  ON_ManifestMap_SourceIndexHash32Table& operator=(const ON_ManifestMap_SourceIndexHash32Table&) = delete;

protected:
    ON__UINT32 MapItemHash32(
      const class ON_ManifestMapItem& map_item
    ) const override
    {
      return ON_ManifestMapItem::SourceIndexHash32(map_item.ComponentType(),map_item.SourceIndex());
    }

public:
  const ON_ManifestMap_Hash32TableItem* FirstManifestMapItemWithSourceIndex(
    ON_ModelComponent::Type component_type,
    int source_component_index
    ) const
  {
    if (ON_ModelComponent::Type::Unset == component_type)
      return nullptr;
    const ON__UINT32 hash32 = ON_ManifestMapItem::SourceIndexHash32(component_type,source_component_index);
    for ( const ON_Hash32TableItem* hash_table_item = FirstItemWithHash(hash32); nullptr != hash_table_item; hash_table_item = NextItemWithHash(hash_table_item) )
    {
      const ON_ManifestMapItem& map_item = ((const ON_ManifestMap_Hash32TableItem*)hash_table_item)->m_map_item;
      if (component_type == map_item.ComponentType() && source_component_index == map_item.SourceIndex() )
        return (const ON_ManifestMap_Hash32TableItem*)hash_table_item;
    }
    return nullptr;
  }

  const ON_ManifestMap_Hash32TableItem* NextManifestMapItemWithSourceIndex(
    const ON_ManifestMap_Hash32TableItem* current_manifest_item
    ) const
  {
    if ( nullptr == current_manifest_item)
      return nullptr;
    const ON_ModelComponent::Type component_type = current_manifest_item->m_map_item.ComponentType();
    const int source_component_index = current_manifest_item->m_map_item.SourceIndex();
    if ( ON_ModelComponent::Type::Unset == component_type || ON_UNSET_INT_INDEX == source_component_index)
      return nullptr;
    for (const ON_Hash32TableItem* hash_table_item = NextItemWithHash(current_manifest_item); nullptr != hash_table_item; hash_table_item = NextItemWithHash(hash_table_item))
    {
      const ON_ManifestMapItem& map_item = ((const ON_ManifestMap_Hash32TableItem*)hash_table_item)->m_map_item;
      if (component_type == map_item.ComponentType() && source_component_index == map_item.SourceIndex() )
        return (const ON_ManifestMap_Hash32TableItem*)hash_table_item;
    }
    return nullptr;
  }
};


class ON_ManifestMapImpl
{
public:
  ON_ManifestMapImpl()
    : m_source_id_hash_table(m_fsp)
    , m_source_index_hash_table(m_fsp)
  {}

  ~ON_ManifestMapImpl() = default;

  ON_ManifestMapImpl(const ON_ManifestMapImpl& src)
    : m_source_id_hash_table(m_fsp)
    , m_source_index_hash_table(m_fsp)
  {
    Internal_Copy(src);
  }

  ON_ManifestMapImpl& operator=(const ON_ManifestMapImpl&);

  unsigned int MapItemCountImpl() const
  {
    return m_source_id_hash_table.ItemCount();
  }

private:
  // Allocates ON_ManifestIdentificationMapItem classes
  ON_ManifestMap_Hash32TableItemFixedSizePool m_fsp;

public:
  // Every item has a m_source_id_hash_table.
  ON_ManifestMap_SourceIdHash32Table m_source_id_hash_table;

  // In addition, some of the items in m_source_id_hash_table have a corresponding
  // m_source_index_hash_table entry.
  ON_ManifestMap_SourceIndexHash32Table m_source_index_hash_table;

private:
  void Internal_Copy(const ON_ManifestMapImpl& src);
  void Internal_Destroy();
};

void ON_ManifestMapImpl::Internal_Copy(const ON_ManifestMapImpl& src)
{
  if (src.m_source_id_hash_table.ItemCount() > 0)
  {
    const ON__UINT32 src_hash_table_sn = src.m_source_id_hash_table.HashTableSerialNumber();
    ON_FixedSizePoolIterator fit(src.m_fsp);
    for (const ON_ManifestMap_Hash32TableItem* src_item = static_cast<const ON_ManifestMap_Hash32TableItem*>(fit.FirstElement());
      nullptr != src_item;
      src_item = static_cast<const ON_ManifestMap_Hash32TableItem*>(fit.NextElement())
      )
    {
      if (src_hash_table_sn != src_item->HashTableSerialNumber())
        continue; // item not active
      const ON_ManifestMapItem& map_item = src_item->m_map_item;
      if (ON_ModelComponent::Type::Unset == map_item.ComponentType())
      {
        ON_ERROR("Invalid map_item in src.m_source_id_hash_table.");
        continue;
      }
      m_source_id_hash_table.AddManifestMapItem(map_item);
      if ( ON_UNSET_INT_INDEX != map_item.SourceIndex() )
        m_source_index_hash_table.AddManifestMapItem(map_item);
    }
  }
}
void ON_ManifestMapImpl::Internal_Destroy()
{
  m_source_index_hash_table.RemoveAllItems();
  m_source_id_hash_table.RemoveAllItems();
  m_fsp.ReturnAll();
}


ON_ManifestMapImpl& ON_ManifestMapImpl::operator=(const ON_ManifestMapImpl& src)
{
  if (this != &src)
  {
    Internal_Destroy();
    Internal_Copy(src);
  }
  return *this;
}

ON_ManifestMapImpl* ON_ManifestMap::Impl()
{
  if (nullptr == m_impl)
    m_impl = new ON_ManifestMapImpl();
  return m_impl;
}

ON_ManifestMap::ON_ManifestMap() ON_NOEXCEPT
{
  // explicity implementation to work around a bug in Apple's CLANG
}

ON_ManifestMap::~ON_ManifestMap()
{
  if (nullptr != m_impl)
  {
    delete m_impl;
    m_impl = nullptr;
  }
}

bool ON_ManifestMap::UpdatetMapItemDestination(
  const class ON_ManifestMapItem& map_item
)
{
  const bool bIgnoreSourceIndex = false;
  return UpdatetMapItemDestination(map_item, bIgnoreSourceIndex);
}

bool ON_ManifestMap::UpdatetMapItemDestination(
    const class ON_ManifestMapItem& map_item,
    bool bIgnoreSourceIndex
    )
{
  if (map_item.SourceIsUnset())
  {
    ON_ERROR("map_item source is not set.");
    return false;
  }
  
  if (ON_nil_uuid == map_item.DestinationId())
  {
    // empty destination 
    if (ON_UNSET_INT_INDEX != map_item.DestinationIndex())
    {
      ON_ERROR("map_item destination index or id is incorrectly set.");
      return false;
    }
  }
  else if (ON_ModelComponent::IndexRequired(map_item.ComponentType()))
  {
    if (ON_UNSET_INT_INDEX == map_item.DestinationIndex())
    {
      ON_ERROR("map_item destination index or id is incorrectly set.");
      return false;
    }
  }

  // map_item_id = item in this manifest map for the SourceId().
  // map_item_id must be valid and have a matching type and id.
  const class ON_ManifestMapItem& map_item_id = MapItemFromSourceId(map_item.SourceId());

  if (ON_nil_uuid == map_item_id.SourceId())
  {
    ON_ERROR("map_item.SourceId() is not in the ON_ManifestMap as a source id.");
    return false;
  }
  if ( 0 != ON_ManifestMapItem::CompareTypeAndSourceId(map_item_id,map_item) )
  {
    ON_ERROR("map_item type is not equal to corresponding ON_ManifestMap item source type.");
    return false;
  }
  if (
    false == bIgnoreSourceIndex
    && map_item_id.SourceIndex() != map_item.SourceIndex()
    )
  {
    ON_ERROR("map_item source index is not equal to corresponding ON_ManifestMap item source index.");
    return false;
  }

  const class ON_ManifestMapItem& map_item_index
    = (ON_UNSET_INT_INDEX != map_item_id.SourceIndex())
    ? MapItemFromSourceIndex(map_item_id.ComponentType(),map_item_id.SourceIndex())
    : map_item_id;
  if (
    map_item_index.ComponentType() != map_item.ComponentType()
    || map_item_index.SourceId() != map_item.SourceId()
    || (false == bIgnoreSourceIndex && map_item_index.SourceIndex() != map_item.SourceIndex())
    )
  {
    ON_ERROR("map_item source settings are not equal to corresponding ON_ManifestMap item source settings.");
    return false;
  }

  if ( map_item_id.SourceIsSet() )
    const_cast<ON_ManifestMapItem&>(map_item_id).SetDestinationIdentification(&map_item);
  if ( map_item_index.SourceIsSet() && &map_item_index != &map_item_id )
    const_cast<ON_ManifestMapItem&>(map_item_index).SetDestinationIdentification(&map_item);

  return true;
}

ON_ManifestMap::ON_ManifestMap(const ON_ManifestMap& src)
{
  if (nullptr != src.m_impl)
    m_impl = new ON_ManifestMapImpl(*src.m_impl);
}

ON_ManifestMap& ON_ManifestMap::operator=(const ON_ManifestMap& src)
{
  if (m_impl != src.m_impl)
  {
    if (nullptr != m_impl)
    {
      delete m_impl;
      m_impl = nullptr;
    }
    if (nullptr != src.m_impl)
    {
      m_impl = new ON_ManifestMapImpl(*src.m_impl);
    }
  }
  return *this;
}


bool ON_ManifestMap::IsEmpty() const
{
  return (0 == MapItemCount());
}

bool ON_ManifestMap::IsNotEmpty() const
{
  return (MapItemCount() > 0);
}

unsigned int ON_ManifestMap::MapItemCount() const
{
  return ( (nullptr != m_impl) ? m_impl->MapItemCountImpl() : 0U );

}


bool ON_ManifestMap::AddMapItem(
  const ON_ManifestMapItem& map_item
  )
{
  if (ON_ModelComponent::Type::Unset == map_item.ComponentType())
  {
    ON_ERROR("map_item.ComponentType() must be set.");
    return false;
  }

  if (ON_nil_uuid == map_item.SourceId())
  {
    ON_ERROR("map_item.SourceId() must be set.");
    return false;
  }

  ON_ManifestMapImpl* impl = Impl();
  const ON_ManifestMap_Hash32TableItem* source_id_hash_table_item = impl->m_source_id_hash_table.AddManifestMapItem(map_item);
  if (nullptr == source_id_hash_table_item)
    return false;

  if (ON_UNSET_INT_INDEX != source_id_hash_table_item->m_map_item.SourceIndex())
    impl->m_source_index_hash_table.AddManifestMapItem(source_id_hash_table_item->m_map_item);

  return true;
}

const class ON_ManifestMapItem& ON_ManifestMap::MapItemFromSourceId(
  const ON_UUID& source_item_id
  ) const
{
  for (;;)
  {
    if ( ON_nil_uuid == source_item_id )
      break;
    if (nullptr == m_impl)
      break;
    const ON_ManifestMap_Hash32TableItem* hash_table_item = m_impl->m_source_id_hash_table.FirstManifestMapItemWithSourceId(source_item_id);
    if (nullptr == hash_table_item)
      break;
    return hash_table_item->m_map_item;
  }
  return ON_ManifestMapItem::Unset;
}

const class ON_ManifestMapItem& ON_ManifestMap::MapItemFromSourceIndex(
  ON_ModelComponent::Type component_type,
  int source_component_index
  ) const
{
  for (;;)
  {
    if ( ON_ModelComponent::Type::Unset == component_type )
      break;
    if ( ON_UNSET_INT_INDEX == source_component_index )
      break;
    if (nullptr == m_impl)
      break;
    const ON_ManifestMap_Hash32TableItem* hash_table_item = m_impl->m_source_index_hash_table.FirstManifestMapItemWithSourceIndex(component_type,source_component_index);
    if (nullptr == hash_table_item)
      break;
    return hash_table_item->m_map_item;
  }
  return ON_ManifestMapItem::Unset;
}

bool ON_ManifestMapItem::DestinationInManifest(
  const ON_ComponentManifest& destination_manifest
  ) const
{
  if (ON_ModelComponent::Type::Unset == m_component_type)
    return false;
  if (ON_nil_uuid == m_destination_id)
    return false;
  const ON_ComponentManifestItem& manifest_item = destination_manifest.ItemFromId(m_component_type, m_destination_id);
  if (manifest_item.ComponentType() != m_component_type)
    return false;
  if (manifest_item.Id() != m_destination_id)
    return false;
  if (manifest_item.Index() != m_destination_index)
    return false;
  return true;
}

ON_ManifestMapItem ON_ManifestMapItem::SwapSourceAndDestiation() const
{
  ON_ManifestMapItem swap;
  swap.m_component_type = m_component_type;
  swap.m_source_index = m_destination_index;
  swap.m_destination_index = m_source_index;
  swap.m_source_id = m_destination_id;
  swap.m_destination_id = m_source_id;
  return swap;
}

bool ON_ManifestMapItem::ClearSourceIdentification()
{
  return SetSourceIdentification(ON_ModelComponent::Type::Unset, ON_nil_uuid, ON_UNSET_INT_INDEX);
}

bool ON_ManifestMapItem::ClearDestinationIdentification()
{
  return SetDestinationIdentification(ON_ModelComponent::Type::Unset, ON_nil_uuid, ON_UNSET_INT_INDEX);
}

bool ON_ManifestMapItem::Internal_SetSourceOrDestinationIdentification(
  unsigned int which_identification, // 0 = source, 1 = destination
  ON_ModelComponent::Type component_type,
  ON_UUID id,
  int index
)
{
  if (0 != which_identification && 1 != which_identification)
  {
    ON_ERROR("Invalid which_identification parameter");
    return false;
  }

  ON_UUID* this_id[2] = { &m_source_id, &m_destination_id };
  int* this_index[2] = { &m_source_index, &m_destination_index };

  if (
    (ON_ModelComponent::Type::Unset == component_type  || m_component_type == component_type)
    && ON_nil_uuid == id 
    && ON_UNSET_INT_INDEX == index
    )
  {
    *(this_id[which_identification]) = ON_nil_uuid;
    *(this_index[which_identification]) = ON_UNSET_INT_INDEX;
    if (ON_nil_uuid == *(this_id[1-which_identification]))
    {
      m_component_type = ON_ModelComponent::Type::Unset;
      *(this_index[1-which_identification]) = ON_UNSET_INT_INDEX;
    }
    return true;
  }

  if (ON_nil_uuid == id)
  {
    if (ON_UNSET_INT_INDEX != index)
    {
      if (0 == which_identification)
      {
        ON_ERROR("source id is nil and source index is not ON_UNSET_INT_INDEX");
      }
      else
      {
        ON_ERROR("destination id is nil and destination index is not ON_UNSET_INT_INDEX");
      }
      return false;
    }
  }
  else if ( 
    ON_ModelComponent::IndexRequired(component_type) 
    && ON_UNSET_INT_INDEX == index 
    )
  {
    if (ON_ModelComponent::Type::InstanceDefinition != component_type)
    {
      if (0 == which_identification)
      {
        ON_ERROR("A valid source index is required.");
      }
      else
      {
        ON_ERROR("A valid destination index is required.");
      }
      return false;
    }
  }

  if (m_component_type != component_type)
  {
    if (ON_ModelComponent::Type::Unset != m_component_type)
    {
      ON_ERROR("source and destination component types not equal.");
      return false;
    }
    m_component_type = component_type;
  }
  *(this_id[which_identification]) = id;
  *(this_index[which_identification]) = index;

  return true;
}

bool ON_ManifestMapItem::SetSourceIdentification(
  ON_ModelComponent::Type component_type,
  ON_UUID source_id,
  int source_index
)
{
  return Internal_SetSourceOrDestinationIdentification(0, component_type, source_id, source_index);
}


bool ON_ManifestMapItem::SetDestinationIdentification(
  ON_ModelComponent::Type component_type,
  ON_UUID destination_id,
  int destination_index
)
{
  return Internal_SetSourceOrDestinationIdentification(1, component_type, destination_id, destination_index);
}

bool ON_ManifestMapItem::SetSourceIdentification(
  const class ON_ModelComponent* model_component
  )
{
  if (nullptr == model_component)
    return ClearSourceIdentification();
  return SetSourceIdentification(model_component->ComponentType(), model_component->Id(), model_component->Index());
}

bool ON_ManifestMapItem::SetDestinationIdentification(
  const class ON_ModelComponent* model_component
  )
{
  if (nullptr == model_component)
    return ClearDestinationIdentification();
  return SetDestinationIdentification(model_component->ComponentType(), model_component->Id(), model_component->Index());
}


bool ON_ManifestMapItem::SetSourceIdentification(
  const class ON_ComponentManifestItem* manifest_item
  )
{
  if (nullptr == manifest_item)
    return ClearSourceIdentification();
  return SetSourceIdentification(manifest_item->ComponentType(), manifest_item->Id(), manifest_item->Index());
}


bool ON_ManifestMapItem::SetDestinationIdentification(
  const class ON_ComponentManifestItem* manifest_item
  )
{
  if (nullptr == manifest_item)
    return ClearDestinationIdentification();
  return SetDestinationIdentification(manifest_item->ComponentType(), manifest_item->Id(), manifest_item->Index());
}

bool ON_ManifestMapItem::SetSourceIdentification(
  const class ON_ManifestMapItem* map_item
 )
{
  if (nullptr == map_item)
    return ClearSourceIdentification();
  return SetSourceIdentification(map_item->ComponentType(), map_item->SourceId(), map_item->SourceIndex());
}

bool ON_ManifestMapItem::SetDestinationIdentification(
  const class ON_ManifestMapItem* map_item
  )
{
  if (nullptr == map_item)
    return ClearDestinationIdentification();
  return SetDestinationIdentification(map_item->ComponentType(), map_item->DestinationId(), map_item->DestinationIndex());
}


ON_ModelComponent::Type ON_ManifestMapItem::ComponentType() const
{
  return m_component_type;
}

const ON_UUID& ON_ManifestMapItem::SourceId() const
{
  return m_source_id;
}

const ON_UUID& ON_ManifestMapItem::DestinationId() const
{
  return m_destination_id;
}

int ON_ManifestMapItem::SourceIndex() const
{
  return m_source_index;
}

int ON_ManifestMapItem::DestinationIndex() const
{
  return m_destination_index;
}

bool ON_ManifestMapItem::SourceInManifest(
  const ON_ComponentManifest& source_manifest
  ) const
{
  if (ON_ModelComponent::Type::Unset == m_component_type)
    return false;
  if (ON_nil_uuid == m_source_id)
    return false;
  const ON_ComponentManifestItem& manifest_item = source_manifest.ItemFromId(m_component_type, m_source_id);
  if (manifest_item.ComponentType() != m_component_type)
    return false;
  if (manifest_item.Id() != m_source_id)
    return false;
  if (manifest_item.Index() != m_source_index)
    return false;
  return true;
}

bool ON_ManifestMap::GetAndValidateDestinationIndex(
  ON_ModelComponent::Type component_type,
  int source_component_index,
  const ON_ComponentManifest& destination_manifest,
  int* destination_component_index
  ) const
{
  bool rc = false;
  int i = source_component_index;
  for (;;)
  {
    if (ON_ModelComponent::Type::Unset == component_type)
      break;
    const ON_ManifestMapItem& map_item = MapItemFromSourceIndex(component_type, source_component_index);
    if (map_item.SourceOrDestinationIsUnset())
      break;
    
    rc =
      (&destination_manifest == &ON_ComponentManifest::Empty)
      ? true
      : map_item.DestinationInManifest(destination_manifest);

    if (rc)
      i = map_item.DestinationIndex();
    break;
  }
  if (nullptr != destination_component_index)
    *destination_component_index = i;
  return rc;
}

bool ON_ManifestMap::GetAndValidateDestinationIndex(
  ON_ModelComponent::Type component_type,
  const ON_UUID& source_component_id,
  const ON_ComponentManifest& destination_manifest,
  int* destination_component_index
  ) const
{
  bool rc = false;
  int i = ON_UNSET_INT_INDEX;
  for (;;)
  {
    if (ON_ModelComponent::Type::Unset == component_type)
      break;
    const ON_ManifestMapItem& map_item = MapItemFromSourceId(source_component_id);
    if (map_item.SourceOrDestinationIsUnset())
      break;
    if (component_type != map_item.ComponentType())
      break;
    rc = map_item.DestinationInManifest(destination_manifest);
    if (rc)
      i = map_item.DestinationIndex();
    break;
  }
  if (nullptr != destination_component_index)
    *destination_component_index = i;
  return rc;
}

bool ON_ManifestMap::GetAndValidateDestinationId(
  ON_ModelComponent::Type component_type,
  const ON_UUID& source_component_id,
  const ON_ComponentManifest& destination_manifest,
  ON_UUID* destination_component_id
  ) const
{
  bool rc = false;
  ON_UUID id = ON_nil_uuid;
  for (;;)
  {
    if (ON_ModelComponent::Type::Unset == component_type)
      break;
    const ON_ManifestMapItem& map_item = MapItemFromSourceId(source_component_id);
    if (map_item.SourceOrDestinationIsUnset())
      break;
    if (component_type != map_item.ComponentType())
      break;
    rc = map_item.DestinationInManifest(destination_manifest);
    if (rc)
      id = map_item.DestinationId();
    break;
  }
  if (nullptr != destination_component_id)
    *destination_component_id = id;
  return rc;
}

int ON_ComponentManifestItem::CompareComponentType(
  const ON_ComponentManifestItem* a,
  const ON_ComponentManifestItem* b
  )
{
  const unsigned int a_type = static_cast<unsigned int>(a->m_component_type);
  const unsigned int b_type = static_cast<unsigned int>(b->m_component_type);
  if (a_type < b_type)
    return -1;
  if (a_type > b_type)
    return 1;
  return 0;
}

int ON_ComponentManifestItem::CompareIndex(
  const ON_ComponentManifestItem*const* a,
  const ON_ComponentManifestItem*const* b
  )
{
  const ON_ComponentManifestItem* a_item = *a;
  const ON_ComponentManifestItem* b_item = *b;
  int rc = ON_ComponentManifestItem::CompareComponentType(a_item,b_item);
  if (0 != rc)
    return rc;
  const auto a_index = a_item->m_index;
  const auto b_index = b_item->m_index;
  if ( a_index < b_index )
    return -1;
  if ( a_index > b_index )
    return 1;
  return 0;
}


int ON_ComponentManifestItem::CompareId(
  const ON_ComponentManifestItem*const* a, 
  const ON_ComponentManifestItem*const* b
  )
{
  const ON_ComponentManifestItem* a_item = *a;
  const ON_ComponentManifestItem* b_item = *b;
  int rc = ON_ComponentManifestItem::CompareComponentType(a_item,b_item);
  if (0 == rc)
    rc = ON_UuidCompare(a_item->m_id,b_item->m_id);
  return rc;
}

int ON_ComponentManifestItem::CompareNameHash(
  const ON_ComponentManifestItem*const* a,
  const ON_ComponentManifestItem*const* b
  )
{
  const ON_ComponentManifestItem* a_item = *a;
  const ON_ComponentManifestItem* b_item = *b;
  int rc = ON_ComponentManifestItem::CompareComponentType(a_item,b_item);
  if (0 == rc)
    rc = ON_NameHash::Compare(a_item->m_name_hash,b_item->m_name_hash);
  return rc;
}

ON_ComponentManifestItem::ON_ComponentManifestItem(
  const class ON_ModelComponent& component
  )
  : m_component_type(component.ComponentType())
  , m_index(component.Index())
  , m_component_runtime_serial_number(component.RuntimeSerialNumber())
  , m_id(component.Id())
  , m_name_hash(component.NameHash())
{}


ON_ComponentManifestItem::ON_ComponentManifestItem(
  const class ON_ModelComponent& component,
  const ON_UUID& manifest_id,
  const class ON_NameHash& manifest_name_hash
  )
  : m_component_type(component.ComponentType())
  , m_component_runtime_serial_number(component.RuntimeSerialNumber())
  , m_id(manifest_id)
  , m_name_hash(manifest_name_hash)
{}

ON_ComponentManifestItem::ON_ComponentManifestItem(
  ON_ModelComponent::Type component_type,
  ON__UINT64 component_runtime_serial_number,
  const ON_UUID& manifest_id,
  const class ON_NameHash& manifest_name_hash
  )
  : m_component_type(component_type)
  , m_component_runtime_serial_number(component_runtime_serial_number)
  , m_id(manifest_id)
  , m_name_hash(manifest_name_hash)
{}


ON_ComponentManifestItem::ON_ComponentManifestItem(
  const class ON_ModelComponent& component,
  int manifest_index,
  const ON_UUID& manifest_id,
  const class ON_NameHash& manifest_name_hash
  )
  : m_component_type(component.ComponentType())
  , m_index(manifest_index)
  , m_component_runtime_serial_number(component.RuntimeSerialNumber())
  , m_id(manifest_id)
  , m_name_hash(manifest_name_hash)
{}

ON_ComponentManifestItem::ON_ComponentManifestItem(
  ON_ModelComponent::Type component_type,
  ON__UINT64 component_runtime_serial_number,
  int manifest_index,
  const ON_UUID& manifest_id,
  const class ON_NameHash& manifest_name_hash
  )
  : m_component_type(component_type)
  , m_index(manifest_index)
  , m_component_runtime_serial_number(component_runtime_serial_number)
  , m_id(manifest_id)
  , m_name_hash(manifest_name_hash)
{}

bool ON_ComponentManifestItem::IsValid() const
{
  return ( ON_ModelComponent::Type::Unset != m_component_type && ON_nil_uuid != m_id);
}

bool ON_ComponentManifestItem::IsUnset() const
{
  return ( ON_ModelComponent::Type::Unset == m_component_type || ON_nil_uuid == m_id);
}

bool ON_ComponentManifestItem::IsDeleted() const
{
  return 0 != (m_status_bits & 0x01U);
}

bool ON_ComponentManifestItem::IsSystemComponent() const
{
  return 0 != (m_status_bits & 0x02U);
}

int ON_ComponentManifestItem::Index() const
{
  return m_index;
}

void ON_ComponentManifestItem::SetIndex( int index )
{
  m_index = index;
}

ON_UUID ON_ComponentManifestItem::Id() const
{
  return m_id;
}

void ON_ComponentManifestItem::SetId(ON_UUID id)
{
  m_id = id;
}

ON_ModelComponent::Type ON_ComponentManifestItem::ComponentType() const
{
  return m_component_type;
}

void ON_ComponentManifestItem::SetComponentType(
  ON_ModelComponent::Type component_type
)
{
  m_component_type = component_type;
}

const ON_NameHash& ON_ComponentManifestItem::NameHash() const
{
  return m_name_hash;
}

void ON_ComponentManifestItem::SetNameHash(
  const ON_NameHash& name_hash
)
{
  m_name_hash = name_hash;
}

ON__UINT64 ON_ComponentManifestItem::ComponentRuntimeSerialNumber() const
{
  return m_component_runtime_serial_number;
}

void ON_ComponentManifestItem::SetComponentRuntimeSerialNumber(
  ON__UINT64 component_runtime_serial_number
)
{
  m_component_runtime_serial_number = component_runtime_serial_number;
}

void ON_ComponentManifestItem::Internal_SetDeletedState(
  bool bDeleted
  )
{
  ON__UINT32 deleted_status_bit = 0x01U;
  if (bDeleted)
  {
    m_status_bits |= deleted_status_bit;
    if (false == m_name_hash.IsEmptyNameHash())
      m_name_hash = ON_NameHash::CreateIdAndUnsetName(m_name_hash.ParentId());
  }
  else
    m_status_bits &= ~deleted_status_bit;
}

////class ON_ModelComponentIndexChange
////{
////public:
////  ON_ModelComponentIndexChange() = default;
////  ~ON_ModelComponentIndexChange() = default;
////  ON_ModelComponentIndexChange(const ON_ModelComponentIndexChange&) = default;
////  ON_ModelComponentIndexChange& operator=(const ON_ModelComponentIndexChange&) = default;
////
////  ON_ModelComponentIndexChange(
////    int original_index,
////    unsigned int manifest_index
////    );
////
////  static const ON_ModelComponentIndexChange Unset;
////
////  static int CompareOriginalIndex(
////    const ON_ModelComponentIndexChange* a,
////    const ON_ModelComponentIndexChange* b
////    );
////
////  static int CompareOriginalIndexAndManifestIndex(
////    const ON_ModelComponentIndexChange* a,
////    const ON_ModelComponentIndexChange* b
////    );
////
////  int m_original_index = ON_ComponentManifest::UnsetComponentIndex;
////  unsigned int m_manifest_index = ON_ComponentManifest::UnsetManifestItemIndex;
////};
////
////const ON_ModelComponentIndexChange ON_ModelComponentIndexChange::Unset;
////
////ON_ModelComponentIndexChange::ON_ModelComponentIndexChange(
////  int original_index,
////  unsigned int manifest_index
////  )
////  : m_original_index(original_index)
////  , m_manifest_index(manifest_index)
////{}
////
////int ON_ModelComponentIndexChange::CompareOriginalIndex(
////  const ON_ModelComponentIndexChange* a,
////  const ON_ModelComponentIndexChange* b
////  )
////{
////  if ( a == b )
////    return 0;
////  if ( nullptr == a )
////    return 1;
////  if ( nullptr == b)
////    return -1;
////  if ( a->m_original_index < b->m_original_index )
////    return -1;
////  if ( a->m_original_index > b->m_original_index )
////    return 1;
////  return 0;
////}

////int ON_ModelComponentIndexChange::CompareOriginalIndexAndManifestIndex(
////  const ON_ModelComponentIndexChange* a,
////  const ON_ModelComponentIndexChange* b
////  )
////{
////  if ( a == b )
////    return 0;
////  if ( nullptr == a )
////    return 1;
////  if ( nullptr == b)
////    return -1;
////  if (ON_ComponentManifest::UnsetManifestItemIndex == a->m_manifest_index)
////  {
////    if ( ON_ComponentManifest::UnsetManifestItemIndex != b->m_manifest_index )
////      return 1; // a is removed and b is not removed
////  }
////  if (ON_ComponentManifest::UnsetManifestItemIndex == b->m_manifest_index)
////    return -1; // b is removed and a is not removed.
////  if ( a->m_original_index < b->m_original_index )
////    return -1;
////  if ( a->m_original_index > b->m_original_index )
////    return 1;
////  if ( a->m_manifest_index < b->m_manifest_index )
////    return -1;
////  if ( a->m_manifest_index > b->m_manifest_index )
////    return 1;
////  return 0;
////}


////class ON_ModelComponentReindexMap
////{
////public:
////  ON_ModelComponentReindexMap() = default;
////  ~ON_ModelComponentReindexMap() = default;
////  ON_ModelComponentReindexMap(const ON_ModelComponentReindexMap&) = default;
////  ON_ModelComponentReindexMap& operator=(const ON_ModelComponentReindexMap&) = default;
////
////  bool AddIndexChange(
////    int original_index,
////    unsigned int manifest_index
////    );
////
////  bool RemoveIndexChange(
////    int original_index
////    );
////
////  /*
////  Returns:
////    If original_index has been remapped, then the remapped value is returned.
////    If original_index is not remapped and original_index >= 0, then original_index is returned.
////    Otherwise ON_ComponentManifest::UnsetManifestItemIndex is returned.
////  */
////  unsigned int FirstManifestIndexFromOriginalIndex(
////    int original_index,
////    bool bUniqueItemRequired
////    ) const;
////
////  void RemoveAll()
////  {
////    m_most_recent_change = ON_ModelComponentIndexChange::Unset;
////    m_sorted_count = 0;
////    m_removed_count = 0;
////    m_reindex_map.Empty();
////  }
////
////private:
////  ON_ModelComponentIndexChange m_most_recent_change = ON_ModelComponentIndexChange::Unset;
////  mutable unsigned int m_sorted_count = 0;
////  mutable unsigned int m_removed_count = 0;
////  mutable ON_SimpleArray<ON_ModelComponentIndexChange> m_reindex_map;
////
////  unsigned int SortList() const;
////};
////
////bool ON_ModelComponentReindexMap::AddIndexChange(
////  int original_index,
////  unsigned int manifest_index
////  )
////{
////  ON_ModelComponentIndexChange index_change(original_index,manifest_index);
////  if (index_change.m_original_index >= 0 && ((unsigned int)index_change.m_original_index) == index_change.m_manifest_index)
////    return false;
////  if ( ON_ModelComponentIndexChange::Unset.m_original_index == index_change.m_original_index )
////    return false;
////  if ( ON_ModelComponentIndexChange::Unset.m_manifest_index == index_change.m_manifest_index )
////    return false;
////
////  if (0 == m_reindex_map.Capacity())
////    m_reindex_map.Reserve(32);
////
////  const unsigned int count = m_reindex_map.UnsignedCount();
////  if ( 0 == count || (count == m_sorted_count  && ON_ModelComponentIndexChange::CompareOriginalIndexAndManifestIndex(&m_reindex_map[count-1], &index_change) <= 0 ) )
////    m_sorted_count++;
////  m_reindex_map.Append(index_change);
////
////  m_most_recent_change = index_change;
////
////  return true;
////}
////
////
////bool ON_ModelComponentReindexMap::RemoveIndexChange(
////  int original_index
////  )
////{
////  if ( m_most_recent_change.m_original_index == original_index )
////    m_most_recent_change = ON_ModelComponentIndexChange::Unset;
////
////  const unsigned int count = m_reindex_map.UnsignedCount();
////  if ( count <= 0 )
////    return false;
////
////  ON_ModelComponentIndexChange* a = m_reindex_map.Array();
////  for (unsigned int i = m_sorted_count; i < count - 1; i++)
////  {
////    if (original_index == a[i].m_original_index)
////    {
////      if ( a[i].m_manifest_index == ON_ComponentManifest::UnsetManifestItemIndex )
////        return false;
////      m_removed_count++;
////      a[i].m_manifest_index = ON_ComponentManifest::UnsetManifestItemIndex;
////      return true;
////    }
////  }
////
////  const ON_ModelComponentIndexChange key(original_index,ON_ComponentManifest::UnsetManifestItemIndex);
////
////  a = (ON_ModelComponentIndexChange*)bsearch(
////    &key,
////    a,
////    m_sorted_count,
////    sizeof(key),
////    (int(*)(const void *, const void *)) ON_ModelComponentIndexChange::CompareOriginalIndex
////    );
////  if (nullptr != a)
////  {
////    if ( a->m_manifest_index == ON_ComponentManifest::UnsetManifestItemIndex )
////      return false;
////    m_removed_count++;
////    a->m_manifest_index = ON_ComponentManifest::UnsetManifestItemIndex;
////    return true;
////  }
////
////  return false;
////}
////
////
////unsigned int ON_ModelComponentReindexMap::FirstManifestIndexFromOriginalIndex(
////  int original_index,
////  bool bUniqueItemRequired
////  ) const
////{
////  unsigned int manifest_index = ON_ComponentManifest::UnsetManifestItemIndex;
////
////  // Frequently the most recently added item is searched for.
////  if (
////    original_index == m_most_recent_change.m_original_index 
////    && ON_ComponentManifest::UnsetManifestItemIndex != m_most_recent_change.m_manifest_index
////    )
////  {
////    if (!bUniqueItemRequired)
////      return m_most_recent_change.m_manifest_index;
////    manifest_index = m_most_recent_change.m_manifest_index;
////  }
////
////  const unsigned int count = SortList();
////  if (count <= m_removed_count)
////  {
////    // no index remapping is present.
////    return 
////      (original_index >= 0)
////      ? ((unsigned int)original_index) // original index not remapped when added to manifest
////      : ON_ComponentManifest::UnsetManifestItemIndex;
////  }
////
////  const ON_ModelComponentIndexChange* a = m_reindex_map.Array();
////  for (unsigned int i = m_sorted_count; i < count; i++)
////  {
////    if (original_index == a[i].m_original_index && ON_ComponentManifest::UnsetManifestItemIndex != a[i].m_manifest_index)
////    {
////      if ( !bUniqueItemRequired )
////        return a[i].m_manifest_index;
////      if (ON_ComponentManifest::UnsetManifestItemIndex == manifest_index)
////        manifest_index = a[i].m_manifest_index;
////      else if (manifest_index != a[i].m_manifest_index)
////        return ON_ComponentManifest::UnsetManifestItemIndex; // not unique
////    }
////  }
////
////  if (m_sorted_count > 0)
////  {
////    const ON_ModelComponentIndexChange key(original_index, ON_ComponentManifest::UnsetManifestItemIndex);
////
////    const ON_ModelComponentIndexChange* f = (const ON_ModelComponentIndexChange*)bsearch(
////      &key,
////      a,
////      m_sorted_count,
////      sizeof(key),
////      (int(*)(const void *, const void *)) ON_ModelComponentIndexChange::CompareOriginalIndex
////      );
////
////    if (nullptr != f)
////    {
////      const ON_ModelComponentIndexChange* a1 = a + (m_sorted_count-1);
////      while (f > a && f[-1].m_original_index == original_index)
////        f--;
////      while (f < a1 && ON_ComponentManifest::UnsetManifestItemIndex == f->m_manifest_index && f[1].m_original_index == original_index)
////        f++;
////      if (ON_ComponentManifest::UnsetManifestItemIndex != f->m_manifest_index)
////      {
////        if (!bUniqueItemRequired)
////          return f->m_manifest_index;
////        if (ON_ComponentManifest::UnsetManifestItemIndex == manifest_index)
////          manifest_index = f->m_manifest_index;
////        else if (f->m_manifest_index != manifest_index)
////          return ON_ComponentManifest::UnsetManifestItemIndex;
////        for (const ON_ModelComponentIndexChange* p = f; p <= a1; p++)
////        {
////          if (p->m_original_index != original_index)
////            break;
////          if (p->m_manifest_index != manifest_index && ON_ComponentManifest::UnsetManifestItemIndex != p->m_manifest_index)
////            return ON_ComponentManifest::UnsetManifestItemIndex; // original index used multiple times
////        }
////      }
////    }
////  }
////
////  if ( ON_ComponentManifest::UnsetManifestItemIndex != manifest_index )
////    return manifest_index;  // original index was remapped when added to manifest
////
////  return 
////    (original_index >= 0)
////    ? ((unsigned int)original_index) // original index not remapped when added to manifest
////    : ON_ComponentManifest::UnsetManifestItemIndex;
////}
////
////unsigned int ON_ModelComponentReindexMap::SortList() const
////{
////  unsigned int count = m_reindex_map.UnsignedCount();
////  if (m_removed_count >= count)
////  {
////    m_reindex_map.SetCount(0);
////    return 0;
////  }
////  if (m_sorted_count + 4 >= count && m_removed_count <= m_sorted_count/16)
////    return count;
////  
////  ON_ModelComponentIndexChange* a = const_cast<ON_ModelComponentIndexChange*>(m_reindex_map.Array());
////
////  const unsigned int unsorted_count = count-m_sorted_count;
////  if ( m_sorted_count <= 32 || unsorted_count > count/2 || m_removed_count > 0 )
////  {
////    ON_qsort(a, count, sizeof(a[0]), (int(*)(const void*, const void*))ON_ModelComponentIndexChange::CompareOriginalIndexAndManifestIndex);
////    if (m_removed_count > 0)
////    {
////      count -= m_removed_count;
////      m_removed_count = 0;
////      m_reindex_map.SetCount(count);
////    }
////    m_sorted_count = count;
////    return count;
////  }
////
////  // The sorted portion of item_list[] is at least as large as the unsorted portion.
////  // Sort the unsorted portion of item_list[] and shuffle it into the sorted portion.
////  // The assumption is that this will be faster that simply sorting the entire list
////  // again. For some value of sorted_count and count, this will be true. 
////  // The threshhold ( m_sorted_count <= 32 || unsorted_count > count/2 )
////  // is a guess and needs testing and tuning to be optimal.
////  else
////  {
////    // copy unsorted items to buffer[]
////    ON_ModelComponentIndexChange stack_buffer[64];
////    const size_t sizeof_buffer = unsorted_count*sizeof(stack_buffer[0]);
////    ON_ModelComponentIndexChange* buffer 
////      = (sizeof(stack_buffer) >= sizeof_buffer)
////      ? stack_buffer
////      : (ON_ModelComponentIndexChange*)onmalloc(sizeof_buffer);
////    memcpy(buffer,a+m_sorted_count,sizeof_buffer);
////
////    // sort buffer[]
////    ON_qsort(buffer, unsorted_count, sizeof(buffer[0]), (int(*)(const void*, const void*))ON_ModelComponentIndexChange::CompareOriginalIndexAndManifestIndex);
////
////    // shuffle sorted portion of a[] and sorted buffer[] together in order.
////    ON_ModelComponentIndexChange* e = a + m_sorted_count - 1;      // e = last element in original sorted array.
////    ON_ModelComponentIndexChange* f = buffer + m_sorted_count - 1; // f = last element in new sorted bufffer[]
////    ON_ModelComponentIndexChange* dst = a + count;
////    while(dst-- > a)
////    {
////      if (ON_ModelComponentIndexChange::CompareOriginalIndexAndManifestIndex(e, f) <= 0)
////      {
////        *dst = *f;
////        if ( buffer == f )
////          break;
////        f--;
////      }
////      else
////      {
////        *dst = *e;
////        if (a == e)
////        {
////          memcpy(a, buffer, ((f - buffer) + 1)*sizeof(a[0]));
////          break;
////        }
////        e--;
////      }
////    }
////    if ( buffer != stack_buffer )
////      onfree(buffer);
////  }
////  m_sorted_count = count;
////  return count;
////}
////

class ON_ComponentManifestTableIndex
{
public:
  ON_ComponentManifestTableIndex();
  ~ON_ComponentManifestTableIndex() = default;

private:
  ON_ComponentManifestTableIndex(const ON_ComponentManifestTableIndex&) = delete;
  ON_ComponentManifestTableIndex& operator=(const ON_ComponentManifestTableIndex&) = delete;

public:
  /*
  Description:
    For indexed item, manifest indices are >= 0 and < IndexLimit().
  Returns 
    manifest index limit.
  */
  int IndexLimit() const
  {
    return m_item_list.Count();
  }

  /*
    Returns number of active, deleted, and system items.
  */
  unsigned int TotalItemCount() const
  {
    return m_active_and_deleted_item_count + m_system_item_count;
  }

  /*
    Returns number of active and deleted items.
  */
  unsigned int ActiveAndDeletedItemCount() const
  {
    return m_active_and_deleted_item_count;
  }

  /*
    Returns number of active and deleted items.
  */
  unsigned int ActiveItemCount() const
  {
    return 
      (m_active_and_deleted_item_count > m_deleted_item_count)
      ? (m_active_and_deleted_item_count - m_deleted_item_count)
      : 0;
  }

  /*
    Returns number of active items.
  */
  unsigned int DeletedItemCount() const
  {
    return m_deleted_item_count;
  }

  /*
    Returns number of system items.
  */
  unsigned int SystemItemCount() const
  {
    return m_system_item_count;
  }

  bool AddSystemItem(
    ON_ComponentManifestItem_PRIVATE* system_item
    );


  ON_ModelComponent::Type ComponentType() const
  {
    return m_component_type;
  }

  bool AddItemAndSetManifestIndex(
    ON_ComponentManifestItem_PRIVATE* item
    );

  void IncrementDeletedCount()
  {
    m_deleted_item_count++;
  }

  bool DecrementDeletedCount()
  {
    if (m_deleted_item_count > 0)
    {
      m_deleted_item_count--;
      return true;
    }

    ON_ERROR("No items are deleted.");
    return false;
  }

  const ON_ComponentManifestItem_PRIVATE* SystemItemFromIndex(
    int system_item_index
    ) const; 

  const ON_ComponentManifestItem_PRIVATE* ItemFromManifestItemIndex(
    int manifest_item_index
    ) const
  {
    return
      ( manifest_item_index >= 0 && manifest_item_index < m_item_list.Count() )
      ? m_item_list[manifest_item_index]
      : nullptr;
  }

  const ON_ComponentManifestItem_PRIVATE* FirstItem() const
  {
    return m_first_item;
  }

  const ON_ComponentManifestItem_PRIVATE* LastItem() const
  {
    return m_last_item;
  }

  const ON_ComponentManifestItem_PRIVATE* NextItem(
    const ON_ComponentManifestItem_PRIVATE* item
    ) const
  {
    return
      ( nullptr != item && m_manifest_table_sn == item->m_manifest_table_sn)
      ? item->m_next
      : nullptr;
  }

  const ON_ComponentManifestItem_PRIVATE* PreviousItem(
    const ON_ComponentManifestItem_PRIVATE* item
    ) const
  {
    return
      ( nullptr != item && m_manifest_table_sn == item->m_manifest_table_sn)
      ? item->m_prev
      : nullptr;
  }

  bool RemoveItem(
    const ON_ComponentManifestItem_PRIVATE* item
    );

  bool ItemInTable(
    const ON_ComponentManifestItem_PRIVATE* item
    ) const
  {
    return ( nullptr != item && m_manifest_table_sn == item->m_manifest_table_sn);
  }

  void RemoveAllItems(
    bool bResetManifestIndex
    );

  bool SetComponentType(
    ON_ModelComponent::Type component_type
    );

private:
  const unsigned int m_manifest_table_sn;
  ON_ModelComponent::Type m_component_type = ON_ModelComponent::Type::Unset;
  bool m_bIndexedComponent = false;

  unsigned int m_system_item_count = 0; // "system" components
  unsigned int m_active_and_deleted_item_count = 0; // model components (includes deleted components)
  unsigned int m_deleted_item_count = 0; // deleted components

  // linked list of active and deleted model components.
  ON_ComponentManifestItem_PRIVATE* m_first_item = nullptr;
  ON_ComponentManifestItem_PRIVATE* m_last_item = nullptr;

  // linked list of system model components.
  ON_ComponentManifestItem_PRIVATE* m_first_system_item = nullptr;
  ON_ComponentManifestItem_PRIVATE* m_last_system_item = nullptr;

  // Used for indexed items
  // m_item_list[] is always complete and sorted by item->m_index for
  // entries that are not nullptr. Includes active, deleted, and system components.
  ON_SimpleArray<const ON_ComponentManifestItem_PRIVATE*> m_item_list;
};

static unsigned int ON_ComponentManifestTableIndex_sn_generator=0;

ON_ComponentManifestTableIndex::ON_ComponentManifestTableIndex()
  : m_manifest_table_sn(++ON_ComponentManifestTableIndex_sn_generator)
{}

bool ON_ComponentManifestTableIndex::SetComponentType(
  ON_ModelComponent::Type component_type
  )
{
  if (ON_ModelComponent::Type::Unset != m_component_type || false != m_bIndexedComponent)
  {
    ON_ERROR("component type is already set.");
    return false;
  }
  if (ON_ModelComponent::Type::Unset == component_type)
  {
    ON_ERROR("invalid  component_type parameter.");
    return false;
  }
  if (ON_ModelComponent::Type::Mixed == component_type)
  {
    ON_ERROR("invalid  component_type parameter.");
    return false;
  }

  m_component_type = component_type;
  m_bIndexedComponent = ON_ModelComponent::IndexRequired(component_type);

  return true;
}


bool ON_ComponentManifestTableIndex::AddSystemItem(
  ON_ComponentManifestItem_PRIVATE* system_item
  )
{
  if ( nullptr != system_item
    && system_item->ComponentType() == m_component_type
    && nullptr == SystemItemFromIndex(system_item->Index())
    && 0 == system_item->m_manifest_table_sn
    && ON_ModelComponent::Type::Unset != m_component_type
    )
  {
    const bool bValidSystemComponentIndex
      = m_bIndexedComponent
      ? (system_item->Index() < 0 && system_item->Index() > ON_UNSET_INT_INDEX)
      : (ON_UNSET_INT_INDEX == system_item->Index());
    if (bValidSystemComponentIndex)
    {
      system_item->m_prev = m_last_system_item;
      system_item->m_next = nullptr;
      if (nullptr != m_last_system_item)
        m_last_system_item->m_next = system_item;
      else
        m_first_system_item = system_item;
      m_last_system_item = system_item;
      m_system_item_count++;
      system_item->m_manifest_table_sn = m_manifest_table_sn;
      return true;
    }
  }
  ON_ERROR("Invalid system item parameter.");
  return false;
}


bool ON_ComponentManifestTableIndex::AddItemAndSetManifestIndex(
  ON_ComponentManifestItem_PRIVATE* item
  )
{
  if ( nullptr == item )
    return false;

  if (0 != item->m_manifest_table_sn)
  {
    ON_ERROR("item is already in a table");
    return false;
  }
  
  if (m_component_type != item->ComponentType() || ON_ModelComponent::Type::Unset == m_component_type)
  {
    ON_ERROR("Item has component type.");
    return false;
  }

  if (m_bIndexedComponent)
  {
    item->SetIndex(m_item_list.Count());
    m_item_list.Append(item);
  }
  else
  {
    item->SetIndex(ON_UNSET_INT_INDEX);
  }
  
  if (nullptr == m_last_item)
  {
    m_first_item = item;
    item->m_prev = nullptr;
  }
  else
  {
    m_last_item->m_next = item;
    item->m_prev = m_last_item;
  }
  m_last_item = item;
  item->m_next = nullptr;
  
  item->m_manifest_table_sn = m_manifest_table_sn;
  m_active_and_deleted_item_count++;

  if (item->IsDeleted())
    IncrementDeletedCount();

  return true;
}

const ON_ComponentManifestItem_PRIVATE* ON_ComponentManifestTableIndex::SystemItemFromIndex(
  int sytem_item_index
  ) const
{
  if (m_bIndexedComponent && sytem_item_index < 0 && sytem_item_index > ON_UNSET_INT_INDEX )
  {
    // The linked list of system items is always short - hash tables and sorting are a waste of time
    for (const ON_ComponentManifestItem_PRIVATE* system_item = m_first_system_item; nullptr != system_item; system_item = system_item->m_next)
    {
      if ( system_item->Index() == sytem_item_index )
        return system_item;
    }
  }

  return nullptr;
}

bool ON_ComponentManifestTableIndex::RemoveItem(
  const ON_ComponentManifestItem_PRIVATE* item
  )
{
  if ( 
    nullptr != item 
    && m_manifest_table_sn == item->m_manifest_table_sn
    && m_active_and_deleted_item_count > 0 
    )
  {
    if (m_bIndexedComponent)
    {
      if (item->Index() >= 0 && item->Index() < m_item_list.Count() && item == m_item_list[item->Index()])
      {
        m_item_list[item->Index()] = nullptr;
      }
      else
      {
        ON_ERROR("item cannot be removed.");
        return false;
      }
    }

    if (item->m_prev)
      item->m_prev->m_next = item->m_next;
    else
      m_first_item = item->m_next;
    if ( item->m_next )
      item->m_next->m_prev = item->m_prev;
    else
      m_last_item = item->m_prev;
    
    const_cast<ON_ComponentManifestItem_PRIVATE*>(item)->m_next = nullptr;
    const_cast<ON_ComponentManifestItem_PRIVATE*>(item)->m_prev = nullptr;
    const_cast<ON_ComponentManifestItem_PRIVATE*>(item)->m_manifest_table_sn = 0;

    m_active_and_deleted_item_count--;
    if (item->IsDeleted())
      DecrementDeletedCount();
    return true;
  }

  ON_ERROR("item cannot be removed.");

  return false;
}

void ON_ComponentManifestTableIndex::RemoveAllItems(
  bool bResetManifestIndex
  )
{
  m_item_list.Zero();
  if ( bResetManifestIndex )
    m_item_list.SetCount(0);
  
  m_active_and_deleted_item_count = 0;
  m_deleted_item_count = 0;

  m_first_item = nullptr;
  m_last_item = nullptr;

  m_system_item_count = 0;
  m_first_system_item = nullptr;
  m_last_system_item = nullptr;
}

class ON_ComponentManifestImpl
{
public:
  ON_ComponentManifestImpl() ON_NOEXCEPT;
  ~ON_ComponentManifestImpl() = default;

private:
  ON_ComponentManifestImpl(const ON_ComponentManifestImpl&) = delete;
  ON_ComponentManifestImpl& operator=(const ON_ComponentManifestImpl&) = delete;

public:
  int IndexLimit(
    ON_ModelComponent::Type component_type
    ) const;

  // All items (including system and deleted items)
  unsigned int ItemCountImpl() const;

  // Number of items of a specific type.
  // Includes active, deleted, and system items.
  unsigned int TotalItemCountImpl(
    ON_ModelComponent::Type component_type
    ) const;

  // Number of items of a specific type.
  // Includes deleted items.
  // Excludes system items.
  unsigned int ActiveAndDeletedItemCountImpl(
    ON_ModelComponent::Type component_type
    ) const;

  // Number of items of a specific type.
  // Includes deleted items.
  // Excludes system items.
  unsigned int ActiveItemCountImpl(
    ON_ModelComponent::Type component_type
    ) const;

  unsigned int DeletedItemCountImpl(
    ON_ModelComponent::Type component_type
    ) const;

  // Number of system items.
  unsigned int SystemItemCountImpl(
    ON_ModelComponent::Type component_type
    ) const;

  ON_UUID UnusedId(
    ON_UUID candidate_id
    ) const
  {
    if ( false == (ON_nil_uuid == candidate_id) && IdIsAvailable(candidate_id) )
      return candidate_id;
    return ON_CreateId();
  }

  bool IdIsAvailable(
    ON_UUID id
    ) const
  {
    for (;;)
    {
      if ( ON_nil_uuid == id )
        break;
      if (nullptr != m_manifest_id_hash_table.FirstManifestItemWithId(id))
        break;
      return true;
    }
    return false;
  }

  const ON_wString UnusedName(
    ON_ModelComponent::Type component_type,
    const wchar_t* candidate_name,
    const wchar_t* base_name,
    const wchar_t* suffix_separator,
    unsigned int suffix0,
    unsigned int* suffix_value
    ) const;

  bool NameIsAvailable(
    ON_ModelComponent::Type component_type,
    const ON_NameHash& candidate_name_hash
    ) const
  {
    const ON_ComponentNameHash32Table& name_hash_table = ComponentNameHash32TableConst(component_type);
    return nullptr == name_hash_table.FirstManifestItemWithName(component_type,candidate_name_hash);
  }

  const ON_ComponentManifestItem_PRIVATE* AddItem(
    const ON_ComponentManifestItem& item,
    const ON_UUID& component_parent_id,
    bool bResolveIdAndNameCollisions,
    const wchar_t* candidate_name,
    ON_wString* assigned_name
    );

  const ON_ComponentManifestItem_PRIVATE* AddSystemItem(
    const ON_ComponentManifestItem& item
    );

  const ON_ComponentManifestItem_PRIVATE* ItemFromManifestIndex(
    ON_ModelComponent::Type component_type,
    int manifest_item_index
    ) const;

  const ON_ComponentManifestItem_PRIVATE* ItemFromManifestId(
    const ON_UUID& manifest_item_id
    ) const;

  const ON_ComponentManifestItem_PRIVATE* ItemFromNameHash(
    ON_ModelComponent::Type component_type,
    const ON_NameHash& manifest_item_name_hash
    ) const;

  const ON_ComponentManifestItem_PRIVATE* ItemFromComponentRuntimeSerialNumber(
    ON__UINT64 component_runtime_serial_number
    ) const;

  const ON_ComponentManifestItem_PRIVATE* ChangeItemNameHash(
    const ON_UUID& manifest_item_id,
    const ON_NameHash& new_name_hash
    );

  const ON_ComponentManifestItem_PRIVATE* DeleteItem(
    const ON_ComponentManifestItem_PRIVATE* manifest_item
    );

  const ON_ComponentManifestItem_PRIVATE* UndeleteItem(
    const ON_ComponentManifestItem_PRIVATE* manifest_item,
    const ON_UUID& parent_id,
    const wchar_t* candidate_name,
    ON_wString& assigned_name
    );

  const ON_ComponentManifestItem_PRIVATE* ChangeItemComponentRuntimeSerialNumber(
    const ON_ComponentManifestItem_PRIVATE* manifest_item,
    ON__UINT64 new_component_runtime_serial_number
    );

  bool RemoveItem(
    const ON_ComponentManifestItem_PRIVATE* item
    );

  bool RemoveAllItems(
    ON_ModelComponent::Type component_type,
    bool bResetManifestIndex
    );

  const ON_ComponentManifestItem_PRIVATE* SystemItemFromIndex(
    ON_ModelComponent::Type component_type,
    int system_item_index
    ) const;

  const ON_ComponentManifestItem_PRIVATE* SystemItemFromNameHash(
    ON_ModelComponent::Type component_type,
    const ON_NameHash& system_item_name_hash
    ) const;

  const class ON_ComponentManifestItem_PRIVATE* FirstItem(
    ON_ModelComponent::Type component_type
    ) const;

  const class ON_ComponentManifestItem_PRIVATE* LastItem(
    ON_ModelComponent::Type component_type
    ) const;

  const class ON_ComponentManifestItem_PRIVATE* NextItem(
    const class ON_ComponentManifestItem* item
    ) const;

  const class ON_ComponentManifestItem_PRIVATE* PreviousItem(
    const class ON_ComponentManifestItem* item
    ) const;

  const class ON_ComponentManifestItem_PRIVATE* ManagedItemFromItem(
    const class ON_ComponentManifestItem* item
    ) const
  {
    // First guess is that the id is the best choice.
    // Note that item may be from anyplace including a stack variable
    if ( nullptr == item )
      return nullptr;
    const ON_ComponentManifestHash32TableItem* hash_item = m_manifest_id_hash_table.FirstManifestItemWithId(item->m_id);
    return ( nullptr != hash_item && nullptr != hash_item->m_manifest_item && item->m_component_type == hash_item->m_manifest_item->m_component_type)
      ? hash_item->m_manifest_item
      : nullptr;
  }

  ON__UINT64 ManifestContentVersionNumber() const
  {
    return m_manifest_content_version_number;
  }

private:
  mutable ON__UINT64 m_manifest_content_version_number = 0;

  // One for each ON_ModelComponent type.
  ON_ComponentManifestTableIndex* TableIndexFromType(
    ON_ModelComponent::Type component_type
    );

  const ON_ComponentManifestTableIndex* TableIndexFromTypeConst(
    ON_ModelComponent::Type component_type
    ) const;

public:
  enum : unsigned int
  {
    TableCount = (unsigned int)ON_ModelComponent::Type::NumOf
  };

private:
  ON_ComponentManifestTableIndex m_table_index[ON_ComponentManifestImpl::TableCount];

public:
  const unsigned int m_manifest_impl_sn;

private:
  // Fixed size pool for managing ON_ComponentManifestItem_PRIVATE memory
  ON_ComponentManifestItem_PRIVATE* AllocateItem();
  ON_ComponentManifestItem_PRIVATE* AllocateItem(
    const ON_ComponentManifestItem& src
    );
  void DeallocateItem(ON_ComponentManifestItem_PRIVATE*);
  ON_FixedSizePool m_item_PRIVATE__fsp;

private:
  // Fixed size pool for the following hash tables
  ON_ManifestHash32TableItemFixedSizePool m_hash_table_item_fsp;
  
  // Temporary - Hash table used for component ids. 
  //   When all components are derived from ON_ModelComponent,
  //   m_manifest_id_hash_table can be removed and 
  //   m_component_serial_number_map can be used to store
  //   the manifest id values.
  //  Currently Rhino CRhinoDoc model geometry and model lights are not derived from ON_ModelComponent.
  ON_ComponentIdHash32Table m_manifest_id_hash_table;

  ON_ComponentNameHash32Table& ComponentNameHash32Table(
    ON_ModelComponent::Type component_type
    );

  ON_SerialNumberMap m_component_serial_number_map;

public:
  const ON_ComponentNameHash32Table& ComponentNameHash32TableConst(
    ON_ModelComponent::Type component_type
    ) const;

private:
  // Hash table used for model components that require unique names
  // A model component may have the same name as a system component.
  ON_ComponentNameHash32Table m_unique_name_hash_table;

  // Hash table used for model components that have nonunique names
  ON_ComponentNameHash32Table m_nonunique_name_hash_table;

  // Hash table used for system components that require unique names
  ON_ComponentNameHash32Table m_system_name_hash_table;
};

int ON_ComponentManifestImpl_TableCount(void)
{
  return ON_ComponentManifestImpl::TableCount;
}

static unsigned int ON_ComponentManifestImpl_SerialNumberGenerator()
{
  static unsigned int manifest_impl_sn = 0;
  return ++manifest_impl_sn;
}

ON_ComponentManifestImpl::ON_ComponentManifestImpl() ON_NOEXCEPT
  : m_manifest_impl_sn(ON_ComponentManifestImpl_SerialNumberGenerator())
  , m_manifest_id_hash_table(m_hash_table_item_fsp)
  , m_unique_name_hash_table(m_hash_table_item_fsp)
  , m_nonunique_name_hash_table(m_hash_table_item_fsp)
  , m_system_name_hash_table(m_hash_table_item_fsp)
{
  m_item_PRIVATE__fsp.Create(sizeof(ON_ComponentManifestItem_PRIVATE),0,0);
  for (unsigned int i = 0; i < TableCount; i++)
  {
    ON_ModelComponent::Type component_type = ON_ModelComponent::ComponentTypeFromUnsigned(i);
    if ( ON_ModelComponent::Type::Unset == component_type)
      continue;
    if ( ON_ModelComponent::Type::Mixed == component_type)
      continue;
    m_table_index[i].SetComponentType(component_type);
  }
}

ON_ComponentManifestItem_PRIVATE* ON_ComponentManifestImpl::AllocateItem()
{
  ON_ComponentManifestItem_PRIVATE* manifest_item = new (m_item_PRIVATE__fsp.AllocateDirtyElement()) ON_ComponentManifestItem_PRIVATE();
  manifest_item->m_manifest_impl_sn = m_manifest_impl_sn;
  return manifest_item;
}

ON_ComponentManifestItem_PRIVATE* ON_ComponentManifestImpl::AllocateItem(
  const ON_ComponentManifestItem& item
  )
{
  ON_ComponentManifestItem_PRIVATE* manifest_item = new (m_item_PRIVATE__fsp.AllocateDirtyElement()) ON_ComponentManifestItem_PRIVATE(item);
  manifest_item->m_manifest_impl_sn = m_manifest_impl_sn;
  return manifest_item;
}

void ON_ComponentManifestImpl::DeallocateItem(
  ON_ComponentManifestItem_PRIVATE* item
  )
{
  if (nullptr != item)
  {
    if (m_manifest_impl_sn != item->m_manifest_impl_sn)
    {
      ON_ERROR("item memory corruption.");
    }
    else
    {
      item->m_manifest_impl_sn = 0;
      item->m_manifest_table_sn = 0;
      m_item_PRIVATE__fsp.ReturnElement(item);
    }
  }
}

const ON_wString ON_ComponentManifestImpl::UnusedName(
  ON_ModelComponent::Type component_type,
  const wchar_t* candidate_name,
  const wchar_t* base_name,
  const wchar_t* suffix_separator,
  unsigned int suffix0,
  unsigned int* suffix_value
  ) const
{
  if ( nullptr != suffix_value )
    *suffix_value = suffix0;
  if (ON_UNSET_UINT_INDEX == suffix0)
    suffix0 = ActiveAndDeletedItemCountImpl(component_type);

  if (false == ON_ModelComponent::ComponentTypeIsValidAndNotMixed(component_type))
  {
    ON_ERROR("Invalid component_type parameter.");
    return ON_wString::EmptyString;
  }

  const ON_ComponentNameHash32Table& hash_table = ComponentNameHash32TableConst(component_type);

  const bool bIgnoreParentId = (false == ON_ModelComponent::UniqueNameIncludesParent(component_type));
  const bool bIgnoreCase = ON_ModelComponent::UniqueNameIgnoresCase(component_type);

  ON_NameHash name_hash;
  ON_wString unused_component_name(candidate_name);
  unused_component_name.TrimLeftAndRight();
  if (unused_component_name.IsNotEmpty() )
  {
    name_hash = ON_NameHash::Create(ON_nil_uuid,candidate_name,bIgnoreCase);
    if ( name_hash.IsValidAndNotEmpty() )
    {
      if ( 
        false == hash_table.NameInUse(component_type, name_hash, bIgnoreParentId)
        && false == m_system_name_hash_table.NameInUse(component_type, name_hash, bIgnoreParentId)
        )
      {
        return unused_component_name;
      }
    }
    else
    {
      ON_ERROR("Invalid candidate_name parameter.");
    }
    name_hash = ON_NameHash::EmptyNameHash;
    unused_component_name = ON_wString::EmptyString;
  }
  
  ON_wString local_base_name(base_name);
  ON_wString s;
  if (local_base_name.IsEmpty())
  {
    if (nullptr == base_name)
    {
      local_base_name = candidate_name;
      local_base_name.TrimLeftAndRight();
      local_base_name.TrimRight(L"0123456789 _-");
    }
    if (local_base_name.IsEmpty() || false == ON_ModelComponent::IsValidComponentName(local_base_name))
      local_base_name = ON_ModelComponent::ComponentTypeToString(component_type);
  }
  else
  {
    s = local_base_name;
    s += 'X';
    s.TrimLeftAndRight();
    if (s.Length() > 1 && ON_ModelComponent::IsValidComponentName(s))
    {
      s.SetLength(s.Length()-1);
      local_base_name = s;
    }
    else
    {
      ON_ERROR("Invalid base_name parameter.");
      local_base_name = ON_ModelComponent::ComponentTypeToString(component_type);
    }
  }
  
  if (nullptr == suffix_separator || 0 != suffix_separator[0])
  {
    // suffix separator is either the default or needs to be validated.
    if (nullptr != suffix_separator)
    {
      s = local_base_name;
      s += suffix_separator;
      if (s.Length() > local_base_name.Length())
      {
        s += 'X';
        if (ON_ModelComponent::IsValidComponentName(s))
          local_base_name += suffix_separator;
        else
        {
          ON_ERROR("Invalid suffix_separator parameter.");
          suffix_separator = nullptr;
        }
      }
    }
    if (nullptr == suffix_separator)
      suffix_separator = L" ";
  }

  const unsigned int index_limit = IndexLimit(component_type);
  const unsigned int item_count = ActiveAndDeletedItemCountImpl(component_type);
  const int max_attempt_count = ((index_limit >= item_count) ? index_limit : item_count) + 20;
  for (int pass = 0; pass < 3; pass++)
  {
    ON_RandomNumberGenerator RNG;
    if ( 1 == pass)
      RNG.Seed();
    for (int attempt_count = 0; attempt_count < max_attempt_count; attempt_count++)
    {
      switch (pass)
      {
      case 0:
        unused_component_name.Format(L"%ls%ls%02u", static_cast<const wchar_t*>(local_base_name), suffix_separator, ++suffix0);
        break;
      case 1:
        unused_component_name.Format(L"%ls%ls%08X", static_cast<const wchar_t*>(local_base_name), suffix_separator, RNG.RandomNumber());
        break;
      default:
        {
          ON_wString id;
          ON_UuidToString(ON_CreateId(),id);
          id.Remove('-');
          unused_component_name.Format(L"%ls%ls%ls", static_cast<const wchar_t*>(local_base_name), suffix_separator, static_cast<const wchar_t*>(id));
        }
        break;
      }
      name_hash = ON_NameHash::Create(ON_nil_uuid, unused_component_name);
      if ( hash_table.NameInUse(component_type, name_hash, bIgnoreParentId) )
        continue;
      if ( m_system_name_hash_table.NameInUse(component_type, name_hash, bIgnoreParentId) )
        continue;
      if (suffix_value)
        *suffix_value = suffix0;
      return unused_component_name;
    }
  }

  // It is likely there is a bug in this function or the manifest searching code.
  ON_ERROR("Unable to find a unique name.");
  return ON_wString::EmptyString;
}

ON_ComponentNameHash32Table& ON_ComponentManifestImpl::ComponentNameHash32Table(
  ON_ModelComponent::Type component_type
  )
{
  return
    (ON_ModelComponent::UniqueNameRequired(component_type) || ON_ModelComponent::Type::Image == component_type)
    ? m_unique_name_hash_table
    : m_nonunique_name_hash_table;
}
  
const ON_ComponentNameHash32Table& ON_ComponentManifestImpl::ComponentNameHash32TableConst(
  ON_ModelComponent::Type component_type
  ) const
{
  return const_cast<ON_ComponentManifestImpl*>(this)->ComponentNameHash32Table(component_type);
}

ON_ComponentManifestTableIndex* ON_ComponentManifestImpl::TableIndexFromType(
  ON_ModelComponent::Type component_type
  ) 
{
  return const_cast<ON_ComponentManifestTableIndex*>(TableIndexFromTypeConst(component_type));
}

const ON_ComponentManifestTableIndex* ON_ComponentManifestImpl::TableIndexFromTypeConst(
  ON_ModelComponent::Type component_type
  ) const
{
  const unsigned int i = static_cast<unsigned int>(component_type);
  if ( i < ON_ComponentManifestImpl::TableCount )
    return &m_table_index[i];

  ON_ERROR("component_type is not valid");
  return nullptr;
}

int ON_ComponentManifestImpl::IndexLimit(
  ON_ModelComponent::Type component_type
  ) const
{
  const ON_ComponentManifestTableIndex* table_index = TableIndexFromTypeConst(component_type);
  return (nullptr == table_index) ? 0 : table_index->IndexLimit();
}

unsigned int ON_ComponentManifestImpl::ItemCountImpl() const
{
  return m_manifest_id_hash_table.ItemCount();
}

unsigned int ON_ComponentManifestImpl::SystemItemCountImpl(
  ON_ModelComponent::Type component_type
) const
{
  unsigned int count = 0;
  if (ON_ModelComponent::ComponentTypeIsValidAndNotMixed(component_type))
  {
    const ON_ComponentManifestTableIndex* table_index = TableIndexFromTypeConst(component_type);
    count
      = (nullptr == table_index) 
      ? 0
      : table_index->SystemItemCount();
  }
  else
  {
    ON_ModelComponentTypeIterator type_it = ON_ModelComponentTypeIterator::ExplicitComponentTypes;
    for (ON_ModelComponent::Type t = type_it.FirstType(); ON_ModelComponent::Type::Unset != t; t = type_it.NextType())
    {
      if (ON_ModelComponent::ComponentTypeIsValidAndNotMixed(t))
       count += SystemItemCountImpl(t);
    }
  }
  return count;
}

unsigned int ON_ComponentManifestImpl::TotalItemCountImpl(
  ON_ModelComponent::Type component_type
  ) const
{
  unsigned int count = 0;
  if (ON_ModelComponent::ComponentTypeIsValidAndNotMixed(component_type))
  {
    const ON_ComponentManifestTableIndex* table_index = TableIndexFromTypeConst(component_type);
    count
      = (nullptr == table_index) 
      ? 0
      : table_index->TotalItemCount();
  }
  else
  {
    ON_ModelComponentTypeIterator type_it = ON_ModelComponentTypeIterator::ExplicitComponentTypes;
    for (ON_ModelComponent::Type t = type_it.FirstType(); ON_ModelComponent::Type::Unset != t; t = type_it.NextType())
    {
      if (ON_ModelComponent::ComponentTypeIsValidAndNotMixed(t))
       count += TotalItemCountImpl(t);
    }
  }
  return count;
}

unsigned int ON_ComponentManifestImpl::ActiveAndDeletedItemCountImpl(
  ON_ModelComponent::Type component_type
  ) const
{
  unsigned int count = 0;
  if (ON_ModelComponent::ComponentTypeIsValidAndNotMixed(component_type))
  {
    const ON_ComponentManifestTableIndex* table_index = TableIndexFromTypeConst(component_type);
    count
      = (nullptr == table_index) 
      ? 0
      : table_index->ActiveAndDeletedItemCount();
  }
  else
  {
    ON_ModelComponentTypeIterator type_it = ON_ModelComponentTypeIterator::ExplicitComponentTypes;
    for (ON_ModelComponent::Type t = type_it.FirstType(); ON_ModelComponent::Type::Unset != t; t = type_it.NextType())
    {
      if (ON_ModelComponent::ComponentTypeIsValidAndNotMixed(t))
       count += ActiveAndDeletedItemCountImpl(t);
    }
  }
  return count;
}

unsigned int ON_ComponentManifestImpl::ActiveItemCountImpl(
  ON_ModelComponent::Type component_type
  ) const
{
  unsigned int count = 0;
  if (ON_ModelComponent::ComponentTypeIsValidAndNotMixed(component_type))
  {
    const ON_ComponentManifestTableIndex* table_index = TableIndexFromTypeConst(component_type);
    count
      = (nullptr == table_index) 
      ? 0
      : table_index->ActiveItemCount();
  }
  else
  {
    ON_ModelComponentTypeIterator type_it = ON_ModelComponentTypeIterator::ExplicitComponentTypes;
    for (ON_ModelComponent::Type t = type_it.FirstType(); ON_ModelComponent::Type::Unset != t; t = type_it.NextType())
    {
      if (ON_ModelComponent::ComponentTypeIsValidAndNotMixed(t))
       count += ActiveItemCountImpl(t);
    }
  }
  return count;
}

unsigned int ON_ComponentManifestImpl::DeletedItemCountImpl(
  ON_ModelComponent::Type component_type
  ) const
{
  unsigned int count = 0;
  if (ON_ModelComponent::ComponentTypeIsValidAndNotMixed(component_type))
  {
    const ON_ComponentManifestTableIndex* table_index = TableIndexFromTypeConst(component_type);
    count
      = (nullptr == table_index) 
      ? 0
      : table_index->DeletedItemCount();
  }
  else
  {
    ON_ModelComponentTypeIterator type_it = ON_ModelComponentTypeIterator::ExplicitComponentTypes;
    for (ON_ModelComponent::Type t = type_it.FirstType(); ON_ModelComponent::Type::Unset != t; t = type_it.NextType())
    {
      if (ON_ModelComponent::ComponentTypeIsValidAndNotMixed(t))
       count += DeletedItemCountImpl(t);
    }
  }
  return count;
}

const ON_ComponentManifestItem_PRIVATE* ON_ComponentManifestImpl::AddItem(
  const ON_ComponentManifestItem& item,
  const ON_UUID& component_parent_id,
  bool bResolveIdAndNameCollisions,
  const wchar_t* candidate_name,
  ON_wString* assigned_name
  )
{
  ON_ComponentManifestItem_PRIVATE* manifest_item = nullptr;
  ON__UINT64 component_serial_number = 0;

  for (;;)
  {
    const ON_ModelComponent::Type component_type = item.m_component_type;
    ON_ComponentManifestTableIndex* table_index = TableIndexFromType(component_type);
    if (nullptr == table_index)
    {
      ON_ERROR("Invalid component type.");
      break;
    }

    const bool bIndexRequired = ON_ModelComponent::IndexRequired(component_type);
    const unsigned int assigned_index = IndexLimit(component_type);
    if (bIndexRequired && assigned_index >= 0x7FFFFFFFU)
    {
      ON_ERROR("unable to assign component index.");
      break;
    }


    ON_UUID id = item.m_id;
    if ( false == IdIsAvailable(id) )
    {
      if (false == bResolveIdAndNameCollisions)
      {
        ON_ERROR("component id is in use.");
        break;
      }
      id = ON_CreateId();
    }

    ON_NameHash name_hash = item.m_name_hash;

    const bool bIsFilePathHash = (ON_ModelComponent::Type::Image == component_type && name_hash.IsFilePathHash());
    ON_wString name;
    const bool bUniqueNameRequired = bIsFilePathHash || ON_ModelComponent::UniqueNameRequired(component_type);
    if (ON_ModelComponent::Type::Image == component_type)
    {
      if (false == bIsFilePathHash )
      {
        ON_ERROR("Embedded files require a non-empty file path name hash.");
        break;
      }
    }
    else
    {
      if (bIsFilePathHash)
      {
        ON_ERROR("Ordinary components cannot have a file path name hash.");
        break;
      }
    }

    if ( bUniqueNameRequired )
    {
      bool bAssignNewName = false;
      if (false == item.m_name_hash.IsValidAndNotEmpty())
      {
        if (bIsFilePathHash)
        {
          ON_ERROR("embedded file path is not valid.");
          break;
        }
        if (false == bResolveIdAndNameCollisions)
        {
          ON_ERROR("component name is not valid.");
          break;
        }
        bAssignNewName = true;
      }
      else if (nullptr != m_unique_name_hash_table.FirstManifestItemWithName(component_type, item.m_name_hash))
      {
        if ( bIsFilePathHash )
        {
          // embedded file - cannot change name
          ON_ERROR("embedded file name is in use.");
          break;
        }
        if (false == bResolveIdAndNameCollisions)
        {
          ON_ERROR("component name is in use.");
          break;
        }
        bAssignNewName = true;
      }

      if (bAssignNewName && false == bIsFilePathHash )
      {
        ON_wString local_candidate_name(candidate_name);
        local_candidate_name.TrimLeftAndRight();
        if (false == ON_ModelComponent::IsValidComponentName(local_candidate_name))
          local_candidate_name = ON_wString::EmptyString;
        ON_wString base_name(local_candidate_name);
        base_name.TrimRight(L"0123456789 _-");
        const ON_UUID name_parent_id 
          = ON_ModelComponent::UniqueNameIncludesParent(component_type)
          ? component_parent_id
          : ON_nil_uuid;
        name = UnusedName(component_type,local_candidate_name,base_name,nullptr,ON_UNSET_UINT_INDEX,nullptr);
        if ( name.IsEmpty() )
        {
          ON_ERROR("unable to assign component name.");
          break;
        }
        name_hash = ON_NameHash::Create(name_parent_id,name);
      }
    }

    ON_SerialNumberMap::SN_ELEMENT* e = nullptr;
    if (0 != item.m_component_runtime_serial_number)
    {
      component_serial_number = item.m_component_runtime_serial_number;
      e = m_component_serial_number_map.AddSerialNumber(component_serial_number);
      if (nullptr != e->m_value.m_u.ptr)
      {
        ON_ERROR("item.m_component_runtime_serial_number is already in the manifest.");
        component_serial_number = 0;
        break;
      }
    }
    
    m_manifest_content_version_number++;
    manifest_item = AllocateItem(item);
    manifest_item->m_next = nullptr;
    manifest_item->m_prev = nullptr;
    manifest_item->m_name_hash = name_hash;
    manifest_item->m_id = id;
    if (false == table_index->AddItemAndSetManifestIndex(manifest_item))
      break;

    m_manifest_id_hash_table.AddManifestItem(manifest_item);

    if ( bUniqueNameRequired )
      m_unique_name_hash_table.AddManifestItem(manifest_item);
    else if ( manifest_item->m_name_hash.IsValidAndNotEmpty())
      m_nonunique_name_hash_table.AddManifestItem(manifest_item);

    if ( nullptr != assigned_name )
      *assigned_name = name;

    if (nullptr != e)
    {
      e->m_value.m_u_type = static_cast<unsigned int>(manifest_item->m_component_type);
      e->m_value.m_u.ptr = (void*)manifest_item;
    }

    return manifest_item;
  }

  // failure
  if (nullptr != manifest_item)
    DeallocateItem(manifest_item);

  if ( nullptr != assigned_name )
    *assigned_name = ON_wString::EmptyString;

  if (0 != component_serial_number)
  {
    ON_SerialNumberMap::SN_ELEMENT* e = m_component_serial_number_map.RemoveSerialNumberAndId(component_serial_number);
    if (nullptr != e)
    {
      e->m_value.m_u_type = 0;
      e->m_value.m_u.u64 = 0;
    }
  }

  return nullptr;
}

const ON_ComponentManifestItem_PRIVATE* ON_ComponentManifestImpl::ChangeItemNameHash(
  const ON_UUID& manifest_item_id,
  const ON_NameHash& new_name_hash
  )
{
  if (new_name_hash.IsInvalidNameHash())
  {
    ON_ERROR("new_name_hash parameter is not valid.");
    return nullptr;
  }

  ON_ComponentManifestItem_PRIVATE* item = const_cast<ON_ComponentManifestItem_PRIVATE*>(ItemFromManifestId(manifest_item_id));

  if (nullptr == item)
  {
    ON_ERROR("id not valid.");
    return nullptr;
  }

  const ON_NameHash old_name_hash = item->m_name_hash;
  
  if ( old_name_hash == new_name_hash )
    return item;
  
  const bool bUniqueNameRequired = ON_ModelComponent::UniqueNameRequired(item->m_component_type);
  if (bUniqueNameRequired)
  {
    if (false == new_name_hash.IsValidAndNotEmpty())
    {
      ON_ERROR("new_name_hash must be valid and not empty.");
      return nullptr;
    }
    const ON_ComponentManifestHash32TableItem* hash_item = m_unique_name_hash_table.FirstManifestItemWithName(item->m_component_type,new_name_hash);
    if (nullptr != hash_item )
    {
      ON_ERROR("new name is in use.");
      return nullptr;
    }
  }

  ON_ComponentNameHash32Table& name_hash_table = ComponentNameHash32Table(item->m_component_type);

  if (old_name_hash.IsValidAndNotEmpty())
  {
    if (false == name_hash_table.RemoveManifestItem(item))
    {
      ON_ERROR("old name not in manifest.");
    }
  }

  m_manifest_content_version_number++;
  item->m_name_hash = new_name_hash;
  if ( new_name_hash.IsValidAndNotEmpty() )
    name_hash_table.AddManifestItem(item);

  return item;
}

const ON_ComponentManifestItem_PRIVATE* ON_ComponentManifestImpl::ChangeItemComponentRuntimeSerialNumber(
  const ON_ComponentManifestItem_PRIVATE* manifest_item,
  ON__UINT64 new_component_runtime_serial_number
  )
{
  if (nullptr == manifest_item)
  {
    ON_ERROR("manifest_item is nullptr.");
    return nullptr;
  }

  if (this->m_manifest_impl_sn != manifest_item->m_manifest_impl_sn )
  {
    ON_ERROR("manifest_item is corrupt.");
    return nullptr;
  }

  if ( manifest_item->m_component_runtime_serial_number == new_component_runtime_serial_number )
    return manifest_item;

  ON_SerialNumberMap::SN_ELEMENT* e;
  if (0 != new_component_runtime_serial_number)
  {
    e = m_component_serial_number_map.FindSerialNumber(new_component_runtime_serial_number);
    if (nullptr != e)
    {
      ON_ERROR("new_component_runtime_serial_number is already in the manifest.");
      return nullptr;
    }
  }

  ON_SerialNumberMap::SN_ELEMENT e0;
  memset(&e0, 0, sizeof(e0));
  if (0 != manifest_item->m_component_runtime_serial_number)
  {
    e = m_component_serial_number_map.RemoveSerialNumberAndId(manifest_item->m_component_runtime_serial_number);
    if (nullptr == e)
    {
      ON_ERROR("component not in m_component_serial_number_map.");
    }
    else
    {
      e0 = *e;
      if (e->m_value.m_u.ptr != manifest_item)
      {
        ON_ERROR("m_component_serial_number_map id corrupt.");
      }
    }
  }

  e = m_component_serial_number_map.AddSerialNumber(new_component_runtime_serial_number);
  if (nullptr != e->m_value.m_u.ptr)
  {
    ON_ERROR("new_component_runtime_serial_number is already in the manifest.");
    return nullptr;
  }
  e->m_value.m_u.ptr = (void*)manifest_item;
  const_cast<ON_ComponentManifestItem_PRIVATE*>(manifest_item)->m_component_runtime_serial_number = new_component_runtime_serial_number;

  m_manifest_content_version_number++;

  return manifest_item;
}

bool ON_ComponentManifestImpl::RemoveItem(
  const ON_ComponentManifestItem_PRIVATE* manifest_item
  )
{
  if ( nullptr == manifest_item )
    return false;
  
  if (this->m_manifest_impl_sn != manifest_item->m_manifest_impl_sn )
  {
    ON_ERROR("manifest_item is corrupt.");
    return false;
  }

  ON_ComponentManifestItem_PRIVATE* item = const_cast<ON_ComponentManifestItem_PRIVATE*>(manifest_item);
  m_manifest_content_version_number++;
  ON_ComponentManifestTableIndex* table_index = TableIndexFromType(item->m_component_type);
  if (nullptr != table_index)
    table_index->RemoveItem(item);
  if ( 0 != item->m_component_runtime_serial_number )
    m_component_serial_number_map.RemoveSerialNumberAndId(item->m_component_runtime_serial_number);
  if (ON_UuidIsNotNil(item->m_id))
    m_manifest_id_hash_table.RemoveManifestItem(item);
  if (item->m_name_hash.IsValidAndNotEmpty())
   ComponentNameHash32Table(item->m_component_type).RemoveManifestItem(item);
  DeallocateItem(item);
  return true;
}

bool ON_ComponentManifestImpl::RemoveAllItems(
  ON_ModelComponent::Type component_type,
  bool bResetManifestIndex
  )
{
  ON_ComponentManifestTableIndex* table_index = TableIndexFromType(component_type);
  if (nullptr == table_index)
    return false;
  ON_ComponentManifestItem_PRIVATE* next_item = const_cast<ON_ComponentManifestItem_PRIVATE*>(table_index->FirstItem());
  ON_ComponentNameHash32Table& name_hash_table = ComponentNameHash32Table(component_type);
  while (nullptr != next_item)
  {
    ON_ComponentManifestItem_PRIVATE* item = next_item;
    next_item = next_item->m_next;
    if ( 0 != item->m_component_runtime_serial_number )
      m_component_serial_number_map.RemoveSerialNumberAndId(item->m_component_runtime_serial_number);
    if (ON_UuidIsNotNil(item->m_id))
      m_manifest_id_hash_table.RemoveManifestItem(item);
    if (item->m_name_hash.IsValidAndNotEmpty())
      name_hash_table.RemoveManifestItem(item);
    DeallocateItem(item);
  }
  table_index->RemoveAllItems(bResetManifestIndex);
  return true;
}

const ON_ComponentManifestItem_PRIVATE* ON_ComponentManifestImpl::DeleteItem(
  const ON_ComponentManifestItem_PRIVATE* manifest_item
  )
{
  if ( nullptr == manifest_item )
    return nullptr;

  if ( manifest_item->IsSystemComponent() )
  {
    ON_ERROR("cannot delete system components.");
    return nullptr;
  }

  if (m_manifest_impl_sn != manifest_item->m_manifest_impl_sn)
  {
    ON_ERROR("manifest_item is corrupt.");
    return nullptr;
  }

  ON_ComponentManifestItem_PRIVATE* item = const_cast<ON_ComponentManifestItem_PRIVATE*>(manifest_item);
  if ( nullptr == item )
    return nullptr;
  if (item->IsDeleted())
    return item;
  if (item->m_name_hash.IsValidAndNotEmpty())
  {
    // remove name;
    if (ON_ModelComponent::UniqueNameRequired(item->m_component_type))
    {
      m_unique_name_hash_table.RemoveManifestItem(item);
      if ( ON_ModelComponent::UniqueNameIncludesParent(item->m_component_type) )
        item->m_name_hash = ON_NameHash::CreateIdAndUnsetName(item->m_name_hash.ParentId());
      else
        item->m_name_hash = ON_NameHash::UnsetNameHash;
    }
    else
    {
      m_nonunique_name_hash_table.RemoveManifestItem(item);
      item->m_name_hash = ON_NameHash::EmptyNameHash;
    }
  }
  
  item->Internal_SetDeletedState(true);
  if (item->IsDeleted())
  {
    ON_ComponentManifestTableIndex* table_index = TableIndexFromType(item->ComponentType());
    if (nullptr != table_index)
      table_index->IncrementDeletedCount();
  }

  return item;
}

const ON_ComponentManifestItem_PRIVATE* ON_ComponentManifestImpl::UndeleteItem(
  const ON_ComponentManifestItem_PRIVATE* manifest_item,
  const ON_UUID& parent_id,
  const wchar_t* candidate_name,
  ON_wString& assigned_name
  )
{
  ON_wString name(candidate_name);
  assigned_name = ON_wString::EmptyString;

  if ( nullptr == manifest_item )
    return nullptr;

  if (m_manifest_impl_sn != manifest_item->m_manifest_impl_sn)
  {
    ON_ERROR("manifest_item is corrupt");
    return nullptr;
  }

  ON_ComponentManifestItem_PRIVATE* item = const_cast<ON_ComponentManifestItem_PRIVATE*>(manifest_item);

  const ON_UUID name_parent_id
    = ON_ModelComponent::UniqueNameRequired(item->m_component_type)
    ? parent_id
    : ON_nil_uuid;

  name.TrimLeftAndRight();
  ON_NameHash name_hash = ON_NameHash::Create(name_parent_id,name);
  if (false == name_hash.IsValidAndNotEmpty())
    name_hash = ON_NameHash::EmptyNameHash;

  if (item->IsDeleted())
  {
    ON_ComponentManifestTableIndex* table_index = TableIndexFromType(item->ComponentType());
    if (nullptr != table_index)
      table_index->DecrementDeletedCount();
  }
  else if (name_hash == item->m_name_hash)
  {
    assigned_name = name;
    return item;
  }

  item->Internal_SetDeletedState(false);

  if (ON_ModelComponent::UniqueNameRequired(item->m_component_type))
  {
    if (name_hash.IsValidAndNotEmpty()
      && nullptr == m_unique_name_hash_table.FirstManifestItemWithName(item->m_component_type, name_hash))
    {
      assigned_name = name;
    }
    else
    {
      // need a unique name
      assigned_name = UnusedName(
        item->m_component_type,
        candidate_name,
        nullptr,
        nullptr,
        ON_UNSET_UINT_INDEX,
        nullptr
        );
      name_hash = ON_NameHash::Create(name_parent_id,assigned_name);
    }
    item->m_name_hash = name_hash;
    m_unique_name_hash_table.AddManifestItem(item);
  }
  else 
  {
    m_nonunique_name_hash_table.RemoveManifestItem(item);
    assigned_name = name;
    item->m_name_hash = name_hash;
    m_nonunique_name_hash_table.AddManifestItem(item);
  }


  return item;
}

const ON_ComponentManifestItem_PRIVATE* ON_ComponentManifestImpl::SystemItemFromIndex(
  ON_ModelComponent::Type component_type,
  int system_item_index
  ) const
{
 const  ON_ComponentManifestTableIndex* table_index = TableIndexFromTypeConst(component_type);
  if (nullptr != table_index)
    return table_index->SystemItemFromIndex(system_item_index);
  return nullptr;
}

const ON_ComponentManifestItem_PRIVATE* ON_ComponentManifestImpl::ItemFromManifestId(
  const ON_UUID& manifest_item_id
  ) const
{
  if ( ON_nil_uuid == manifest_item_id )
    return nullptr;
  const ON_ComponentManifestHash32TableItem* hash_item = m_manifest_id_hash_table.FirstManifestItemWithId(manifest_item_id);
  return (nullptr != hash_item) ? hash_item->m_manifest_item : nullptr;
}

const ON_ComponentManifestItem_PRIVATE* ON_ComponentManifestImpl::ItemFromNameHash(
  ON_ModelComponent::Type component_type,
  const ON_NameHash& component_name_hash
  ) const
{
  const ON_ComponentNameHash32Table& name_hash_table = ComponentNameHash32TableConst(component_type);
  const ON_ComponentManifestHash32TableItem* hash_item = name_hash_table.FirstManifestItemWithName(component_type,component_name_hash);
  return (nullptr != hash_item) ? hash_item->m_manifest_item : nullptr;
}

const ON_ComponentManifestItem_PRIVATE* ON_ComponentManifestImpl::SystemItemFromNameHash(
  ON_ModelComponent::Type component_type,
  const ON_NameHash& system_item_name_hash
  ) const
{
  const ON_ComponentManifestHash32TableItem* hash_item = m_system_name_hash_table.FirstManifestItemWithName(component_type,system_item_name_hash);
  return (nullptr != hash_item) ? hash_item->m_manifest_item : nullptr;
}

const ON_ComponentManifestItem_PRIVATE* ON_ComponentManifestImpl::ItemFromComponentRuntimeSerialNumber(
  ON__UINT64 component_runtime_serial_number
  ) const
{
  const ON_SerialNumberMap::SN_ELEMENT* e = m_component_serial_number_map.FindSerialNumber(component_runtime_serial_number);
  if ( nullptr == e )
    return nullptr;
  const ON_ComponentManifestItem_PRIVATE* item = (const ON_ComponentManifestItem_PRIVATE*)e->m_value.m_u.ptr;
  if (nullptr == item || item->m_component_runtime_serial_number != component_runtime_serial_number )
  {
    ON_ERROR("m_component_serial_number_map is corrupt.");
    return nullptr;
  }
  return item;
}


const ON_ComponentManifestItem_PRIVATE* ON_ComponentManifestImpl::ItemFromManifestIndex(
  ON_ModelComponent::Type component_type,
  int manifest_item_index
   ) const
{
  if (manifest_item_index >= 0)
  {
    const ON_ComponentManifestTableIndex* table_index = TableIndexFromTypeConst(component_type);
    if (nullptr != table_index)
      return table_index->ItemFromManifestItemIndex(manifest_item_index);
  }
  return nullptr;
}


const class ON_ComponentManifestItem_PRIVATE* ON_ComponentManifestImpl::FirstItem(
  ON_ModelComponent::Type component_type
  ) const
{
  const ON_ComponentManifestTableIndex* table = TableIndexFromTypeConst(component_type); 
  return (nullptr != table) ? table->FirstItem() : nullptr;
}

const class ON_ComponentManifestItem_PRIVATE* ON_ComponentManifestImpl::LastItem(
  ON_ModelComponent::Type component_type
  ) const
{
  const ON_ComponentManifestTableIndex* table = TableIndexFromTypeConst(component_type); 
  return (nullptr != table) ? table->LastItem() : nullptr;
}

const class ON_ComponentManifestItem_PRIVATE* ON_ComponentManifestImpl::NextItem(
  const class ON_ComponentManifestItem* item
  ) const
{
  const ON_ComponentManifestItem_PRIVATE* manifest_item = ManagedItemFromItem(item);
  return (nullptr != manifest_item ) ? manifest_item->m_next : nullptr;
}

const class ON_ComponentManifestItem_PRIVATE* ON_ComponentManifestImpl::PreviousItem(
  const class ON_ComponentManifestItem* item
  ) const
{
  const ON_ComponentManifestItem_PRIVATE* manifest_item = ManagedItemFromItem(item);
  return (nullptr != manifest_item ) ? manifest_item->m_prev : nullptr;
}

ON_ComponentManifest::ON_ComponentManifest() ON_NOEXCEPT
{
  // explicity implementation to work around a bug in Apple's CLANG
}

ON_ComponentManifest::~ON_ComponentManifest()
{
  Reset();
}

class ON_ComponentManifestImpl* ON_ComponentManifest::Impl() const
{
  if ( nullptr == m_impl )
    m_impl = new ON_ComponentManifestImpl();
  return m_impl;
}


void ON_ComponentManifest::Reset()
{
  if (nullptr != m_impl)
  {
    delete m_impl;
    m_impl = nullptr;
  }
}

ON__UINT64 ON_ComponentManifest::ManifestContentVersionNumber() const
{
  return 
    (nullptr != m_impl)
    ? m_impl->ManifestContentVersionNumber()
    : 0;
}

unsigned int ON_ComponentManifest::ItemCount() const
{
  return (nullptr == m_impl) ? 0 : m_impl->ItemCountImpl();
}

unsigned int ON_ComponentManifest::ActiveComponentCount(
  ON_ModelComponent::Type component_type
  ) const
{
  return (nullptr == m_impl) ? 0 : m_impl->ActiveItemCountImpl(component_type);
}

unsigned int ON_ComponentManifest::TotalComponentCount(
  ON_ModelComponent::Type component_type
) const
{
  return (nullptr == m_impl) ? 0 : m_impl->TotalItemCountImpl(component_type);
}

unsigned int ON_ComponentManifest::ActiveAndDeletedComponentCount(
  ON_ModelComponent::Type component_type
  ) const
{
  return (nullptr == m_impl) ? 0 : m_impl->ActiveAndDeletedItemCountImpl(component_type);
}

unsigned int ON_ComponentManifest::DeletedComponentCount(
  ON_ModelComponent::Type component_type
  ) const
{
  return (nullptr == m_impl) ? 0 : m_impl->DeletedItemCountImpl(component_type);
}

unsigned int ON_ComponentManifest::SystemComponentCount(
  ON_ModelComponent::Type component_type
) const
{
  return (nullptr == m_impl) ? 0 : m_impl->SystemItemCountImpl(component_type);
}

int ON_ComponentManifest::ComponentIndexLimit(
  ON_ModelComponent::Type component_type
  ) const
{
  return (nullptr == m_impl) ? 0 : m_impl->IndexLimit(component_type);
}

const class ON_ComponentManifestItem* ON_ComponentManifest::Internal_AddItem(
  class ON_ComponentManifestItem& item,
  ON_UUID component_parent_id,
  bool bResolveIdAndNameCollisions,
  const wchar_t* candidate_name,
  ON_wString* assigned_name
  )
{
  if (ON_ModelComponent::Type::Unset == item.ComponentType())
  {
    if (nullptr != assigned_name )
      *assigned_name = ON_wString::EmptyString;
    return nullptr;
  }

  return Impl()->AddItem(
    item,
    component_parent_id,
    bResolveIdAndNameCollisions,
    candidate_name,
    assigned_name
    );
}


const class ON_ComponentManifestItem& ON_ComponentManifest::AddComponentToManifest(
  ON_ModelComponent::Type component_type,
  ON__UINT64 component_serial_number,
  ON_UUID manifest_id,
  const ON_NameHash& component_name_hash
  )
{
  ON_ComponentManifestItem item(
      component_type,
      component_serial_number,
      manifest_id,
      component_name_hash
      );
  const bool bResolveIdAndNameCollisions = false;
  const ON_ComponentManifestItem* manifest_item = Internal_AddItem(
    item,
    component_name_hash.ParentId(),
    bResolveIdAndNameCollisions,
    nullptr,
    nullptr
    );
  return (nullptr != manifest_item) ? *manifest_item : ON_ComponentManifestItem::UnsetItem;
}

const class ON_ComponentManifestItem& ON_ComponentManifest::AddComponentToManifest(
  ON_ModelComponent::Type component_type,
  ON__UINT64 component_serial_number,
  ON_UUID component_parent_id,
  ON_UUID original_id,
  const wchar_t* original_name,
  ON_wString& assigned_name
  )
{
  ON_UUID name_parent_id
    = ON_ModelComponent::UniqueNameIncludesParent(component_type)
    ? component_parent_id
    : ON_nil_uuid;
  return AddComponentToManifest(
    component_type,
    component_serial_number,
    component_parent_id,
    original_id,
    ON_NameHash::Create(name_parent_id,original_name),
    original_name,
    assigned_name
    );
}


const class ON_ComponentManifestItem& ON_ComponentManifest::AddComponentToManifest(
  ON_ModelComponent::Type component_type,
  ON__UINT64 component_serial_number,
  ON_UUID component_parent_id,
  ON_UUID component_id,
  const ON_NameHash& component_name_hash,
  const wchar_t* candidate_name,
  ON_wString& assigned_name
  )
{
  ON_ComponentManifestItem item(
      component_type,
      component_serial_number,
      component_id,
      component_name_hash
      );
  const bool bResolveIdAndNameCollisions = true;
  const ON_ComponentManifestItem* manifest_item = Internal_AddItem(
    item,
    component_parent_id,
    bResolveIdAndNameCollisions,
    candidate_name,
    &assigned_name
    );
  return (nullptr != manifest_item) ? *manifest_item : ON_ComponentManifestItem::UnsetItem;
}

const ON_ComponentManifestItem_PRIVATE* ON_ComponentManifestImpl::AddSystemItem(
  const ON_ComponentManifestItem& item
  )
{
  ON_ComponentManifestItem_PRIVATE* manifest_item = nullptr;
  ON__UINT64 component_serial_number = 0;

  for (;;)
  {
    const ON_ModelComponent::Type component_type = item.m_component_type;
    ON_ComponentManifestTableIndex* table_index = TableIndexFromType(component_type);
    if (nullptr == table_index)
    {
      ON_ERROR("Invalid component type.");
      break;
    }

    if (0 == item.m_component_runtime_serial_number)
    {
      ON_ERROR("Invalid system component runtime serial number.");
      break;
    }

    const ON_UUID id = item.m_id;
    if (ON_UuidIsNil(id))
    {
      ON_ERROR("Invalid system component id.");
      break;
    }

    if ( false == IdIsAvailable(id) )
    {
      ON_ERROR("component id is in use.");
      break;
    }
    
    if (ON_ModelComponent::IndexRequired(component_type))
    {
      if (item.m_index >= 0 || item.m_index <= ON_UNSET_INT_INDEX )
      {
        ON_ERROR("index must negative and set.");
        break;
      }
    }
    else
    {
      if (ON_UNSET_INT_INDEX != item.m_index)
      {
        ON_ERROR("index must be unset.");
        break;
      }
    }

    const ON_NameHash name_hash = item.m_name_hash;
    if (ON_UuidIsNotNil(name_hash.ParentId()))
    {
      ON_ERROR("system component name cannot have parent id.");
      break;
    }

    const bool bUniqueNameRequired = ON_ModelComponent::UniqueNameRequired(component_type);
    if (bUniqueNameRequired)
    {
      if (false == name_hash.IsValidAndNotEmpty())
      {
        ON_ERROR("name must be set.");
        break;
      }
      if (nullptr != m_system_name_hash_table.FirstManifestItemWithName(component_type, name_hash))
      {
        ON_ERROR("system component name must be unique.");
        break;
      }
    }
    else
    {
      if (false == name_hash.IsEmptyNameHash())
      {
        ON_ERROR("name must be empty.");
        break;
      }
    }

    component_serial_number = item.m_component_runtime_serial_number;
    ON_SerialNumberMap::SN_ELEMENT* e = m_component_serial_number_map.AddSerialNumber(component_serial_number);
    if (nullptr != e->m_value.m_u.ptr)
    {
      ON_ERROR("item.m_component_runtime_serial_number is already in the manifest.");
      component_serial_number = 0;
      break;
    }
    
    m_manifest_content_version_number++;
    manifest_item = AllocateItem(item);
    manifest_item->m_next = nullptr;
    manifest_item->m_prev = nullptr;
    manifest_item->m_name_hash = name_hash;
    manifest_item->m_id = id;
    manifest_item->m_status_bits = 0x02U;
    if (false == table_index->AddSystemItem(manifest_item))
    {
      break;
    }

    m_manifest_id_hash_table.AddManifestItem(manifest_item);

    if ( bUniqueNameRequired )
      m_system_name_hash_table.AddManifestItem(manifest_item);

    e->m_value.m_u_type = static_cast<unsigned int>(manifest_item->m_component_type);
    e->m_value.m_u.ptr = (void*)manifest_item;

    return manifest_item;
  }

  // failure
  if (nullptr != manifest_item)
    DeallocateItem(manifest_item);

  if (0 != component_serial_number)
  {
    ON_SerialNumberMap::SN_ELEMENT* e = m_component_serial_number_map.RemoveSerialNumberAndId(component_serial_number);
    if (nullptr != e)
    {
      e->m_value.m_u_type = 0;
      e->m_value.m_u.u64 = 0;
    }
  }

  return nullptr;
}

const ON_ComponentManifestItem& ON_ComponentManifest::AddSystemComponentToManifest(
  const class ON_ModelComponent& component
  )
{
  if (false == component.IsSystemComponent())
  {
    ON_ERROR("component cannot be a system component.");
    return ON_ComponentManifestItem::UnsetItem;
  }

  const ON_ComponentManifestItem system_item(component);

  const ON_ComponentManifestItem_PRIVATE* manifest_item = Impl()->AddSystemItem(system_item);

  return 
    (nullptr != manifest_item)
    ? *manifest_item
    : ON_ComponentManifestItem::UnsetItem;
}

const ON_ComponentManifestItem& ON_ComponentManifest::AddComponentToManifest(
  const class ON_ModelComponent& component,
  bool bResolveIdAndNameCollisions,
  ON_wString* assigned_name
  )
{
  ON_ModelComponent::Type component_type = component.ComponentType();
  ON__UINT64 component_serial_number = component.RuntimeSerialNumber();
  ON_UUID component_id = component.Id();
  ON_UUID component_parent_id = component.ParentId();

  const ON_Bitmap* embedded_file = nullptr;
  bool bIsEmbeddedFile = ON_ModelComponent::Type::Image == component_type && nullptr != (embedded_file =ON_Bitmap::Cast(&component));

  const ON_NameHash component_name_hash 
    = (bIsEmbeddedFile)
    ? ON_NameHash::CreateFilePathHash(embedded_file->FileReference())
    : component.NameHash();

  if (bResolveIdAndNameCollisions)
  {
    // modify component identification information as required
    ON_wString manifest_assigned_name;
    const class ON_ComponentManifestItem& manifest_item = AddComponentToManifest(
      component_type,
      component_serial_number,
      component_parent_id,
      component_id,
      component_name_hash,
      component.NameAsPointer(),
      manifest_assigned_name
      );
    if (nullptr != assigned_name)
    {
      if ( manifest_item.NameHash() == component_name_hash )
        *assigned_name = component.Name();
      else
        *assigned_name = manifest_assigned_name;
    }
    return manifest_item;
  }

  // do not modify component identification information
  if ( nullptr != assigned_name )
    *assigned_name = component.Name();
  return AddComponentToManifest(
    component_type,
    component_serial_number,
    component_id,
    component_name_hash
    );
}

bool ON_ComponentManifest::RemoveComponent(
  const ON_ModelComponent& component
  )
{
  return RemoveComponent(component.RuntimeSerialNumber());
}

bool ON_ComponentManifest::RemoveComponent(
  ON__UINT64 component_runtime_serial_number
)
{
  if ( nullptr == m_impl )
    return false;
  const ON_ComponentManifestItem_PRIVATE* manifest_item = m_impl->ItemFromComponentRuntimeSerialNumber(component_runtime_serial_number);
  if ( nullptr == manifest_item )
    return false;
  return m_impl->RemoveItem(manifest_item);
}

bool ON_ComponentManifest::RemoveComponent(
  ON_UUID manifest_id
  )
{
  if ( nullptr == m_impl )
    return false;
  const ON_ComponentManifestItem_PRIVATE* manifest_item = m_impl->ItemFromManifestId(manifest_id);
  if ( nullptr == manifest_item )
    return false;
  return m_impl->RemoveItem(manifest_item);
}

bool ON_ComponentManifest::RemoveIndexedComponent(
  ON_ModelComponent::Type component_type,
  int manifest_item_index
  )
{
  if ( nullptr == m_impl )
    return false;
  const ON_ComponentManifestItem_PRIVATE* manifest_item = m_impl->ItemFromManifestIndex(component_type,manifest_item_index);
  if ( nullptr == manifest_item )
    return false;
  return m_impl->RemoveItem(manifest_item);
}

bool ON_ComponentManifest::RemoveAllComponents(
  ON_ModelComponent::Type component_type,
  bool bResetManifestIndex
  )
{
  if ( nullptr == m_impl )
    return false;
  return m_impl->RemoveAllItems(component_type,bResetManifestIndex);
}


const class ON_ComponentManifestItem& ON_ComponentManifest::ChangeComponentName(
  const class ON_ModelComponent& component
)
{
  return ChangeComponentName(
    component.Id(),
    component.ComponentType(),
    component.ParentId(),
    component.Name()
  );
}

const ON_ComponentManifestItem& ON_ComponentManifest::ChangeComponentName(
  ON_UUID manifest_item_id,
  ON_ModelComponent::Type component_type,
  ON_UUID component_parent_id,
  const wchar_t* name
  )
{
  if (nullptr == m_impl)
    return ON_ComponentManifestItem::UnsetItem;

  ON_UUID name_parent_id
    = ON_ModelComponent::UniqueNameIncludesParent(component_type)
    ? component_parent_id
    : ON_nil_uuid;
  const bool bIgnoreCase = ON_ModelComponent::UniqueNameIgnoresCase(component_type);

  const ON_NameHash new_name_hash = ON_NameHash::Create(name_parent_id,name,bIgnoreCase);
  
  const ON_ComponentManifestItem_PRIVATE* manifest_item = m_impl->ChangeItemNameHash(
    manifest_item_id,
    new_name_hash
    );

  return (nullptr != manifest_item) ? *manifest_item : ON_ComponentManifestItem::UnsetItem;
}

const ON_ComponentManifestItem& ON_ComponentManifest::ChangeComponentNameHash(
  ON_UUID manifest_item_id,
  const ON_NameHash& component_name_hash
  )
{
  if (nullptr == m_impl)
    return ON_ComponentManifestItem::UnsetItem;

  const ON_ComponentManifestItem_PRIVATE* manifest_item = m_impl->ChangeItemNameHash(
    manifest_item_id,
    component_name_hash
    );

  return (nullptr != manifest_item) ? *manifest_item : ON_ComponentManifestItem::UnsetItem;
}

const ON_ComponentManifestItem& ON_ComponentManifest::DeleteComponent(
  ON_UUID manifest_item_id
  )
{
  if (nullptr == m_impl)
    return ON_ComponentManifestItem::UnsetItem;

  const ON_ComponentManifestItem_PRIVATE* manifest_item = m_impl->DeleteItem(
    m_impl->ItemFromManifestId(manifest_item_id)
    );

  return (nullptr != manifest_item) ? *manifest_item : ON_ComponentManifestItem::UnsetItem;
}


const ON_ComponentManifestItem& ON_ComponentManifest::DeleteComponent(
  ON__UINT64 component_runtime_serial_number
  )
{
  if (nullptr == m_impl)
    return ON_ComponentManifestItem::UnsetItem;

  const ON_ComponentManifestItem_PRIVATE* manifest_item = m_impl->DeleteItem(
    m_impl->ItemFromComponentRuntimeSerialNumber(component_runtime_serial_number)
    );

  return (nullptr != manifest_item) ? *manifest_item : ON_ComponentManifestItem::UnsetItem;
}

const ON_ComponentManifestItem& ON_ComponentManifest::UndeleteComponent(
  ON_UUID manifest_item_id,
  ON_UUID parent_id,
  const wchar_t* candidate_name,
  ON_wString& assigned_name
  )
{
  if (nullptr == m_impl)
    return ON_ComponentManifestItem::UnsetItem;

  const ON_ComponentManifestItem_PRIVATE* manifest_item = m_impl->UndeleteItem(
    m_impl->ItemFromManifestId(manifest_item_id),
    parent_id,
    candidate_name,
    assigned_name
    );

  return (nullptr != manifest_item) ? *manifest_item : ON_ComponentManifestItem::UnsetItem;
}

const class ON_ComponentManifestItem& ON_ComponentManifest::UndeleteComponentAndChangeRuntimeSerialNumber(
  ON_UUID item_id,
  ON_UUID parent_id,
  ON__UINT64 new_component_runtime_serial_number,
  const wchar_t* candidate_name,
  ON_wString& assigned_name
)
{
  if (0 != new_component_runtime_serial_number)
  {
    const ON_ComponentManifestItem& item_from_sn = ItemFromComponentRuntimeSerialNumber(new_component_runtime_serial_number);
    if (item_from_sn.IsValid() && item_from_sn.Id() != item_id)
    {
      ON_ERROR("new_component_runtime_serial_number in use.");
      return ON_ComponentManifestItem::UnsetItem;
    }
  }
  const ON_ComponentManifestItem& manifest_item = UndeleteComponent(
    item_id,
    parent_id,
    candidate_name,
    assigned_name
  );
  if ( manifest_item.IsValid() 
    && item_id == manifest_item.Id()
    && new_component_runtime_serial_number != manifest_item.ComponentRuntimeSerialNumber() 
    )
  {
    this->ChangeComponentRuntimeSerialNumber(
      item_id,
      new_component_runtime_serial_number
    );
  }
  return manifest_item;
}

const class ON_ComponentManifestItem& ON_ComponentManifest::ChangeComponentRuntimeSerialNumber(
  ON_UUID manifest_item_id,
  ON__UINT64 component_runtime_serial_number
  )
{
  if (nullptr == m_impl)
    return ON_ComponentManifestItem::UnsetItem;

  const ON_ComponentManifestItem_PRIVATE* manifest_item = m_impl->ChangeItemComponentRuntimeSerialNumber(
    m_impl->ItemFromManifestId(manifest_item_id),
    component_runtime_serial_number
    );

  return (nullptr != manifest_item) ? *manifest_item : ON_ComponentManifestItem::UnsetItem;
}

bool ON_ComponentManifest::NameIsAvailable(
  ON_ModelComponent::Type component_type,
  const ON_NameHash& candidate_name_hash
  ) const
{
  if (false == candidate_name_hash.IsValidAndNotEmpty() )
    return false;

  if (nullptr == m_impl)
    return true;

  return m_impl->NameIsAvailable(component_type,candidate_name_hash);
}

const ON_wString ON_ComponentManifest::UnusedName(
  const ON_ModelComponent& model_component
  ) const
{
  return UnusedName(
    model_component.ComponentType(),
    model_component.ParentId(),
    model_component.NameAsPointer(),
    nullptr,
    nullptr,
    0,
    nullptr
  );
}

const ON_wString ON_ComponentManifest::UnusedName(
  ON_ModelComponent::Type component_type,
  ON_UUID component_parent_id,
  const wchar_t* candidate_name,
  const wchar_t* base_name,
  const wchar_t* suffix_separator,
  unsigned int suffix0,
  unsigned int* suffix_value
  ) const
{
  if ( nullptr != suffix_value )
    *suffix_value = suffix0;

  if (false == ON_ModelComponent::ComponentTypeIsValidAndNotMixed(component_type))
  {
    ON_ERROR("Invalid component_type parameter.");
    return ON_wString::EmptyString;
  }

  if (
    ON_ModelComponent::UniqueNameIncludesParent(component_type)
    && ON_UuidIsNotNil(component_parent_id)
    && nullptr != candidate_name
    && 0 != candidate_name[0]
    )
  {
    // See if candidate name  with parent specified is valid and not in use.
    ON_wString local_candidate_name(candidate_name);
    local_candidate_name.TrimLeftAndRight();
    const bool bIgnoreCase = ON_ModelComponent::UniqueNameIgnoresCase(component_type);
    ON_NameHash candidate_name_hash = ON_NameHash::Create(component_parent_id,local_candidate_name,bIgnoreCase);
    if (candidate_name_hash.IsValidAndNotEmpty())
    {
      if (ItemFromNameHash(component_type, candidate_name_hash).IsUnset())
        return local_candidate_name;
    }
    ON_wString local_base_name(base_name);
    local_base_name.TrimLeftAndRight();
    if (local_base_name.IsEmpty())
    {
      base_name = candidate_name;
    }
    candidate_name = nullptr;
  }

  return Impl()->UnusedName(
    component_type,
    candidate_name,
    base_name,
    suffix_separator,
    suffix0,
    suffix_value
    );
}


ON_UUID ON_ComponentManifest::UnusedId(
  ON_UUID candidate_id
  ) const
{
  return
     ( !(ON_nil_uuid == candidate_id) && IdIsAvailable(candidate_id))
     ? candidate_id
     : ON_CreateId();
}

bool ON_ComponentManifest::IdIsAvailable(
  ON_UUID id
  ) const
{
  if (ON_nil_uuid == id)
    return false;
  if ( nullptr == m_impl )
    return true;
  return m_impl->IdIsAvailable(id);
}

const class ON_ComponentManifestItem& ON_ComponentManifest::SystemItemFromNameHash(
  ON_ModelComponent::Type component_type,
  const ON_NameHash& system_item_name_hash
  ) const
{
  const ON_ComponentManifestItem_PRIVATE* item
    = (nullptr != m_impl)
    ? m_impl->SystemItemFromNameHash(component_type,system_item_name_hash)
    : nullptr;
  return
    (nullptr != item )
    ? *item
    : ON_ComponentManifestItem::UnsetItem;
}


const class ON_ComponentManifestItem& ON_ComponentManifest::SystemItemFromIndex(
  ON_ModelComponent::Type component_type,
  int system_item_index
  ) const
{
  const ON_ComponentManifestItem_PRIVATE* item
    = (nullptr != m_impl)
    ? m_impl->SystemItemFromIndex(component_type,system_item_index)
    : nullptr;
  return
    (nullptr != item )
    ? *item
    : ON_ComponentManifestItem::UnsetItem;
}

const class ON_ComponentManifestItem& ON_ComponentManifest::ItemFromComponentRuntimeSerialNumber(
  ON__UINT64 component_runtime_serial_number
  ) const
{
  const ON_ComponentManifestItem_PRIVATE* item
    = (nullptr != m_impl)
    ? m_impl->ItemFromComponentRuntimeSerialNumber(component_runtime_serial_number)
    : nullptr;
  return
    (nullptr != item )
    ? *item
    : ON_ComponentManifestItem::UnsetItem;
}

const class ON_ComponentManifestItem& ON_ComponentManifest::ItemFromId(
  ON_UUID manifest_item_id
  ) const
{
  const ON_ComponentManifestItem_PRIVATE* item
    = (nullptr != m_impl)
    ? m_impl->ItemFromManifestId(manifest_item_id)
    : nullptr;
  return
    (nullptr != item )
    ? *item
    : ON_ComponentManifestItem::UnsetItem;
}

const class ON_ComponentManifestItem& ON_ComponentManifest::ItemFromId(
  ON_ModelComponent::Type component_type,
  ON_UUID manifest_item_id
  ) const
{
  const ON_ComponentManifestItem& manifest_item = ItemFromId(manifest_item_id);
  if ( manifest_item.ComponentType() == component_type )
    return manifest_item;
  return ON_ComponentManifestItem::UnsetItem;
}

const class ON_ComponentManifestItem& ON_ComponentManifest::ItemFromName(
  const class ON_ModelComponent* model_component
) const
{
  return
    (nullptr != model_component)
    ? ON_ComponentManifest::ItemFromNameHash(model_component->ComponentType(), model_component->NameHash())
    : ON_ComponentManifestItem::UnsetItem;
}

const class ON_ComponentManifestItem& ON_ComponentManifest::ItemFromName(
  ON_ModelComponent::Type component_type,
  ON_UUID parent_id,
  const wchar_t* name
) const
{
  const bool bIgnoreCase = ON_ModelComponent::UniqueNameIgnoresCase(component_type);
  const ON_UUID parent_id_or_nil
    = ON_ModelComponent::UniqueNameIncludesParent(component_type)
    ? parent_id
    : ON_nil_uuid;
  const ON_NameHash component_name_hash = ON_NameHash::Create(parent_id_or_nil, name, bIgnoreCase);
  return ON_ComponentManifest::ItemFromNameHash(component_type, component_name_hash);
}

const class ON_ComponentManifestItem& ON_ComponentManifest::ItemFromNameHash(
  ON_ModelComponent::Type component_type,
  const ON_NameHash& component_name_hash
  ) const
{
  const ON_ComponentManifestItem_PRIVATE* item
    = (nullptr != m_impl)
    ? m_impl->ItemFromNameHash(component_type,component_name_hash)
    : nullptr;
  return
    (nullptr != item )
    ? *item
    : ON_ComponentManifestItem::UnsetItem;
}


const class ON_ComponentManifestItem& ON_ComponentManifest::ItemFromIndex(
  ON_ModelComponent::Type component_type,
  int manifest_item_index
  ) const
{
  const ON_ComponentManifestItem_PRIVATE* item
    = (nullptr != m_impl)
    ? m_impl->ItemFromManifestIndex(component_type,manifest_item_index)
    : nullptr;
  return
    (nullptr != item )
    ? *item
    : ON_ComponentManifestItem::UnsetItem;
}

const class ON_ComponentManifestItem& ON_ComponentManifest::ItemFromUnsignedIndex(
  ON_ModelComponent::Type component_type,
  unsigned int unsigned_manifest_item_index
  ) const
{
  return 
    (unsigned_manifest_item_index <= 2147483647 )
    ? ItemFromIndex(component_type,(int)unsigned_manifest_item_index)
    : ON_ComponentManifestItem::UnsetItem;
}

const class ON_ComponentManifestItem* ON_ComponentManifest::FirstItem(
  ON_ModelComponent::Type component_type
  ) const
{
  return
    (nullptr != m_impl)
    ? m_impl->FirstItem(component_type)
    : nullptr;
}

const class ON_ComponentManifestItem* ON_ComponentManifest::LastItem(
  ON_ModelComponent::Type component_type
  ) const
{
  return
    (nullptr != m_impl)
    ? m_impl->LastItem(component_type)
    : nullptr;
}


const class ON_ComponentManifestItem* ON_ComponentManifest::NextItem(
  const class ON_ComponentManifestItem* item
  ) const
{
  return
    (nullptr != m_impl)
    ? m_impl->NextItem(item)
    : nullptr;
}

const class ON_ComponentManifestItem* ON_ComponentManifest::PreviousItem(
  const class ON_ComponentManifestItem* item
  ) const
{
  return
    (nullptr != m_impl)
    ? m_impl->PreviousItem(item)
    : nullptr;
}

const class ON_ComponentManifestItem* ON_ComponentManifest::NextItem(
  ON_UUID manifest_item_id
  ) const
{
  const ON_ComponentManifestItem_PRIVATE* item
    = (nullptr != m_impl)
    ? m_impl->ItemFromManifestId(manifest_item_id)
    : nullptr;
  return
    (nullptr != item )
    ? item->m_next
    : nullptr;
}

const class ON_ComponentManifestItem* ON_ComponentManifest::PreviousItem(
  ON_UUID manifest_item_id
  ) const
{
  const ON_ComponentManifestItem_PRIVATE* item
    = (nullptr != m_impl)
    ? m_impl->ItemFromManifestId(manifest_item_id)
    : nullptr;
  return
    (nullptr != item )
    ? item->m_prev
    : nullptr;
}
