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

ON_SHA1_Hash::ON_SHA1_Hash()
{
  memset(m_digest, 0, sizeof(m_digest));
}

bool operator==(const ON_SHA1_Hash& a, const ON_SHA1_Hash& b)
{
  return memcmp(a.m_digest, b.m_digest, sizeof(a.m_digest)) == 0;
}

bool operator!=(const ON_SHA1_Hash& a, const ON_SHA1_Hash& b)
{
  return memcmp(a.m_digest, b.m_digest, sizeof(a.m_digest)) != 0;
}

const ON_String ON_SHA1_Hash::ToUTF8String(
  bool bUpperCaseHexadecimalDigits
  ) const
{
  return ON_String::HexadecimalFromBytes(m_digest, sizeof(m_digest),bUpperCaseHexadecimalDigits,false);
}

const ON_wString ON_SHA1_Hash::ToString(
  bool bUpperCaseHexadecimalDigits
  ) const
{
  return ON_wString::HexadecimalFromBytes(m_digest, sizeof(m_digest),bUpperCaseHexadecimalDigits,false);
}

const ON_wString ON_SHA1_Hash::ToStringEx(bool bUpperCaseHexadecimalDigits) const
{
  if (this->IsEmptyContentHash())
    return ON_wString(L"EmptyContentSHA1");
  if (this->IsZeroDigest())
    return ON_wString(L"ZeroSHA1");
  return ToString(bUpperCaseHexadecimalDigits);
}

const ON_SHA1_Hash ON_SHA1_Hash::FromString(
  const ON_wString string_to_parse,
  bool bParseLeasingSpaces,
  bool bParseInteriorSpace,
  bool bParseInteriorHyphen,
  ON_SHA1_Hash failure_return_value
)
{
  const wchar_t* s = static_cast<const wchar_t*>(string_to_parse);
  if (nullptr == s)
    return failure_return_value;

  unsigned digit_count = 0;
  int digits[40] = {};
  const wchar_t* skipped = nullptr;
  const int len = string_to_parse.Length();
  int sdex = 0;
  for (/* empty init */; sdex < len && digit_count < 40; ++sdex)
  {
    const int c = (int)s[sdex];
    if (c >= '0' && c <= '9')
    {
      digits[digit_count++] = (c - '0');
    }
    else if (c >= 'A' && c <= 'F')
    {
      digits[digit_count++] = (c - 'A') + 10;
    }
    else if (c >= 'a' && c <= 'f')
    {
      digits[digit_count++] = (c - 'a') + 10;
    }
    else  if ((int)(ON_wString::Space) == c)
    {
      if (bParseLeasingSpaces && 0 == digit_count)
        continue; // skip leading white space

      if (bParseInteriorSpace && digit_count > 0 && skipped != s - 1)
        skipped = s;
      else
        break;
    }
    else  if ((int)(ON_wString::HyphenMinus) == c)
    {
      if (bParseInteriorHyphen && digit_count > 0 && skipped != s - 1)
        skipped = s;
      else
        break;
    }
    else
      break;
  }

  if (40 != digit_count || sdex > len || (sdex < len && true == ON_wString::IsHexDigit(s[sdex])))
    return failure_return_value;

  ON_SHA1_Hash h;
  int i = 0;
  for(int j = 0; j < 20; ++j, ++i, ++i)
    h.m_digest[j] = (ON__UINT8)(16 * digits[i] + digits[i + 1]);
  return h;
}

  
bool ON_SHA1_Hash::Read(
  class ON_BinaryArchive& archive
  )
{
  *this = ON_SHA1_Hash::ZeroDigest;
  bool rc = false;
  int major_version = 0;
  int minor_version = 0;
  if (!archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version))
    return rc;
  for (;;)
  {
    if ( 1 != major_version )
      break;
    if (!archive.ReadByte(20,m_digest))
      break;
    rc = true;
    break;
  }
  if (!archive.EndRead3dmChunk())
    rc = false;
  return rc;
}


bool ON_SHA1_Hash::Write(
  class ON_BinaryArchive& archive
  ) const
{
  if (!archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0))
    return false;
  bool rc = archive.WriteByte(20,m_digest);
  if (!archive.EndWrite3dmChunk())
    rc = false;
  return rc;
}

void ON_SHA1_Hash::Dump(
class ON_TextLog& text_log
  ) const
{
  ON_wString sha1_hash;
  if ( ON_SHA1_Hash::ZeroDigest == *this )
    sha1_hash = L"ZeroDigest";
  else if ( ON_SHA1_Hash::EmptyContentHash == *this )
    sha1_hash = L"EmptyContentHash";
  else 
    sha1_hash = ToString(true);
  text_log.Print(L"ON_SHA1_Hash::%ls",static_cast<const wchar_t*>(sha1_hash));
}

bool ON_SHA1_Hash::IsZeroDigest() const
{
  return 0 == ON_SHA1_Hash::Compare(*this, ON_SHA1_Hash::ZeroDigest);
}

bool ON_SHA1_Hash::IsEmptyContentHash() const
{
  return 0 == ON_SHA1_Hash::Compare(*this, ON_SHA1_Hash::EmptyContentHash);
}

bool ON_SHA1_Hash::IsZeroDigestOrEmptyContentHash() const
{
  return IsZeroDigest() || IsEmptyContentHash();
}

bool ON_SHA1_Hash::IsSet() const
{
  return IsZeroDigestOrEmptyContentHash() ? false : true;
}

// OBSOLETE - spelling error in name Digent instead of Digest
bool ON_SHA1_Hash::IsZeroDigentOrEmptyContentHash() const
{
  return IsZeroDigestOrEmptyContentHash();
}

ON__UINT32 ON_SHA1_Hash::CRC32(ON__UINT32 current_remainder) const
{
  return ON_CRC32(current_remainder, sizeof(m_digest) / sizeof(m_digest[0]), m_digest);
}


int ON_SHA1_Hash::Compare(
  const ON_SHA1_Hash& a,
  const ON_SHA1_Hash& b
  )
{
  for (int i = 0; i < 20; i++)
  {
    if (a.m_digest[i] < b.m_digest[i])
      return -1;
    if (a.m_digest[i] > b.m_digest[i])
      return 1;
  }
  return 0;
}

ON_SHA1_Hash ON_SHA1_Hash::BufferContentHash(
  const void* buffer,
  size_t sizeof_buffer
  )
{
  if ( nullptr == buffer || sizeof_buffer <= 0 )
    return ON_SHA1_Hash::EmptyContentHash;
  ON_SHA1 sha1;
  sha1.AccumulateBytes(buffer,sizeof_buffer);
  return sha1.Hash();
}

ON_SHA1_Hash ON_SHA1_Hash::FileContentHash(
  const wchar_t* filename,
  ON__UINT64& sizeof_file
  )
{
  FILE* fp = 
    ( nullptr == filename ||  0 == filename[0] )
    ? nullptr
    : ON_FileStream::Open(filename, L"rb");
  ON_SHA1_Hash sha1_hash = ON_SHA1_Hash::FileContentHash(fp,sizeof_file);
  ON_FileStream::Close(fp);
  return sha1_hash;
}

ON_SHA1_Hash ON_SHA1_Hash::FileContentHash(
  const char* filename,
  ON__UINT64& sizeof_file
  )
{
  FILE* fp = 
    ( nullptr == filename ||  0 == filename[0] )
    ? nullptr
    : ON_FileStream::Open(filename, "rb");
  ON_SHA1_Hash sha1_hash = ON_SHA1_Hash::FileContentHash(fp,sizeof_file);
  ON_FileStream::Close(fp);
  return sha1_hash;
}

ON_SHA1_Hash ON_SHA1_Hash::FileContentHash(
  FILE* file,
  ON__UINT64& sizeof_file
  )
{
  sizeof_file = 0;
  if ( nullptr == file )
    return ON_SHA1_Hash::EmptyContentHash;
  size_t sizeof_buffer = 1024;
  void* buffer = onmalloc(sizeof_buffer);
  ON_SHA1 sha1;
  for (ON__UINT64 byte_count = ON_FileStream::Read(file, sizeof_buffer, buffer);
    byte_count > 0;
    byte_count = ON_FileStream::Read(file, sizeof_buffer, buffer)
    )
  {
    sha1.AccumulateBytes(buffer,byte_count);
  }
  onfree(buffer);
  sizeof_file = sha1.ByteCount();
  return sha1.Hash();
}

ON_SHA1_Hash ON_SHA1_Hash::FileSystemPathHash(
  const wchar_t* path
  )
{
  return ON_SHA1_Hash::FileSystemPathHash(path, ON_FileSystemPath::PlatformPathIgnoreCase());
}

ON_SHA1_Hash ON_SHA1_Hash::FileSystemPathHash(
  const char* path
  )
{
  return ON_SHA1_Hash::FileSystemPathHash(path, ON_FileSystemPath::PlatformPathIgnoreCase());
}

ON_SHA1_Hash ON_SHA1_Hash::FileSystemPathHash(
  const wchar_t* path,
  bool bIgnoreCase
  )
{
  const bool bTrimLeft = false;
  const bool bTrimRight = false;
  const bool bAllowWindowsUNCHostNameOrDiskLetter = true;
  const bool bDeleteWindowsUNCHostNameOrDiskLetter = false;
  const wchar_t directory_separator = ON_wString::Slash;
  const ON_StringMapOrdinalType string_map
    = bIgnoreCase
    ? ON_StringMapOrdinalType::MinimumOrdinal
    : ON_StringMapOrdinalType::Identity;

  const ON_wString clean_path = ON_FileSystemPath::CleanPath(
    bTrimLeft,
    bTrimRight,
    bAllowWindowsUNCHostNameOrDiskLetter,
    bDeleteWindowsUNCHostNameOrDiskLetter,
    directory_separator,
    path
    ).MapStringOrdinal(string_map);

  ON__UINT64 byte_count = 0;
  return ON_SHA1_Hash::StringHash( clean_path, byte_count );
}

ON_SHA1_Hash ON_SHA1_Hash::FileSystemPathHash(
  const char* path,
  bool bIgnoreCase
  )
{
  ON_wString wide_path(path);
  return ON_SHA1_Hash::FileSystemPathHash(
    static_cast<const wchar_t*>(wide_path),
    bIgnoreCase
    );
}

ON_SHA1_Hash ON_SHA1_Hash::StringHash(
  const ON_wString& str,
  ON__UINT64& byte_count
  )
{
  // Do not permit corrupt strings to crash this code.
  str.IsValid(false);

  return ON_SHA1_Hash::StringHash(
    static_cast<const wchar_t*>(str),
    (size_t)str.Length(),
    byte_count
    );
}

ON_SHA1_Hash ON_SHA1_Hash::StringHash(
  const wchar_t* str,
  size_t str_length,
  ON__UINT64& byte_count
  )
{
  byte_count = 0;
  if ( nullptr == str || str_length <= 0 )
    return ON_SHA1_Hash::EmptyContentHash;

  ON_SHA1 sha1;
  const int UTF8buffer_capacity = 1024;
  char* UTF8buffer = (char*)onmalloc(UTF8buffer_capacity);

  const int bTestByteOrder = false;
  const ON__UINT32 error_code_point = ON_UnicodeCodePoint::ON_ReplacementCharacter;
  const unsigned int error_mask = 0xFFFFFFFFU;
  while (str_length > 0)
  {
    const wchar_t* sNextWideChar = nullptr;
    unsigned int error_status = 0;
    int UTF8_count = ON_ConvertWideCharToUTF8(
      bTestByteOrder,
      str,
      (int)str_length,
      UTF8buffer,
      UTF8buffer_capacity,
      &error_status,
      error_mask,
      error_code_point,
      &sNextWideChar
      );
    if ( UTF8_count > UTF8buffer_capacity)
      break;
    
    if ( UTF8_count > 0 && UTF8_count <= UTF8buffer_capacity)
      sha1.AccumulateBytes(UTF8buffer,UTF8_count);

    if ( nullptr == sNextWideChar )
      break;
    if ( sNextWideChar <= str )
      break;
    size_t parsed_count = (str - sNextWideChar);
    if ( parsed_count <= 0 || parsed_count >= str_length)
      break;
    str_length -= parsed_count;
    if ( nullptr == sNextWideChar )
      break;
  }

  onfree(UTF8buffer);
  byte_count = sha1.ByteCount();
  return sha1.Hash();
}

ON_SHA1_Hash ON_SHA1_Hash::StringHash(
  const ON_String& str,
  ON__UINT64& byte_count
  )
{
  // Do not permit corrupt strings to crash this code.
  str.IsValid(false);

  return ON_SHA1_Hash::StringHash(
    static_cast<const char*>(str),
    (size_t)str.Length(),
    byte_count
    );
}

ON_SHA1_Hash ON_SHA1_Hash::StringHash(
  const char* str,
  size_t str_length,
  ON__UINT64& byte_count
  )
{
  byte_count = (nullptr != str && str_length > 0) ? ((ON__UINT64)str_length) : 0;
  return ON_SHA1_Hash::BufferContentHash(str,str_length);
}

ON_SHA1_Hash ON_SHA1_Hash::StringHash(
  const char* null_terminated_string
  )
{
  ON__UINT64 byte_count = 0;
  return ON_SHA1_Hash::StringHash(null_terminated_string,ON_String::Length(null_terminated_string),byte_count);
}

ON_SHA1_Hash ON_SHA1_Hash::StringHash(
  const wchar_t* null_terminated_string
  )
{
  ON__UINT64 byte_count = 0;
  return ON_SHA1_Hash::StringHash(null_terminated_string,ON_wString::Length(null_terminated_string),byte_count);
}

/*
The ON_SHA1 class is based on code from Code Project
  http://www.codeproject.com/Articles/2463/CSHA-A-C-Class-Implementation-of-the-SHA-Hash-A

  100% free public domain implementation of the SHA-1 algorithm
  by Dominik Reichl <dominik.reichl@t-online.de>
  Web: http://www.dominik-reichl.de/
*/


// Rotate p_val32 by p_nBits bits to the left
#ifndef ROL32
#ifdef _MSC_VER
#define ROL32(p_val32,p_nBits) _rotl(p_val32,p_nBits)
#else
#define ROL32(p_val32,p_nBits) (((p_val32)<<(p_nBits))|((p_val32)>>(32-(p_nBits))))
#endif
#endif

#if defined(ON_LITTLE_ENDIAN)
#define SHABLK0(i) (workspace16[i] = \
	(ROL32(workspace16[i],24) & 0xFF00FF00) | (ROL32(workspace16[i],8) & 0x00FF00FF))
#else
#define SHABLK0(i) (workspace16[i])
#endif

#define SHABLK(i) (workspace16[i&15] = ROL32(workspace16[(i+13)&15] ^ \
	workspace16[(i+8)&15] ^ workspace16[(i+2)&15] ^ workspace16[i&15],1))

// SHA-1 rounds
#define S_R0(v,w,x,y,z,i) {z+=((w&(x^y))^y)+SHABLK0(i)+0x5A827999+ROL32(v,5);w=ROL32(w,30);}
#define S_R1(v,w,x,y,z,i) {z+=((w&(x^y))^y)+SHABLK(i)+0x5A827999+ROL32(v,5);w=ROL32(w,30);}
#define S_R2(v,w,x,y,z,i) {z+=(w^x^y)+SHABLK(i)+0x6ED9EBA1+ROL32(v,5);w=ROL32(w,30);}
#define S_R3(v,w,x,y,z,i) {z+=(((w|x)&y)|(w&x))+SHABLK(i)+0x8F1BBCDC+ROL32(v,5);w=ROL32(w,30);}
#define S_R4(v,w,x,y,z,i) {z+=(w^x^y)+SHABLK(i)+0xCA62C1D6+ROL32(v,5);w=ROL32(w,30);}

void ON_SHA1::Reset()
{
  m_status_bits = 0;
  m_byte_count = 0;

	m_bit_count[0] = 0;
	m_bit_count[1] = 0;

  // SHA1 initialization constants
	m_state[0] = 0x67452301;
	m_state[1] = 0xEFCDAB89;
	m_state[2] = 0x98BADCFE;
	m_state[3] = 0x10325476;
	m_state[4] = 0xC3D2E1F0;

  m_status_bits = 1;
}

static void SHA1_transform(ON__UINT32 state[5], const ON__UINT8 block[64])
{
	ON__UINT32 a = state[0], b = state[1], c = state[2], d = state[3], e = state[4];
  ON__UINT32 workspace16[16];

	memcpy(workspace16, block, 64);

	// 4 rounds of 20 operations each, loop unrolled
	S_R0(a,b,c,d,e, 0); S_R0(e,a,b,c,d, 1); S_R0(d,e,a,b,c, 2); S_R0(c,d,e,a,b, 3);
	S_R0(b,c,d,e,a, 4); S_R0(a,b,c,d,e, 5); S_R0(e,a,b,c,d, 6); S_R0(d,e,a,b,c, 7);
	S_R0(c,d,e,a,b, 8); S_R0(b,c,d,e,a, 9); S_R0(a,b,c,d,e,10); S_R0(e,a,b,c,d,11);
	S_R0(d,e,a,b,c,12); S_R0(c,d,e,a,b,13); S_R0(b,c,d,e,a,14); S_R0(a,b,c,d,e,15);
	S_R1(e,a,b,c,d,16); S_R1(d,e,a,b,c,17); S_R1(c,d,e,a,b,18); S_R1(b,c,d,e,a,19);
	S_R2(a,b,c,d,e,20); S_R2(e,a,b,c,d,21); S_R2(d,e,a,b,c,22); S_R2(c,d,e,a,b,23);
	S_R2(b,c,d,e,a,24); S_R2(a,b,c,d,e,25); S_R2(e,a,b,c,d,26); S_R2(d,e,a,b,c,27);
	S_R2(c,d,e,a,b,28); S_R2(b,c,d,e,a,29); S_R2(a,b,c,d,e,30); S_R2(e,a,b,c,d,31);
	S_R2(d,e,a,b,c,32); S_R2(c,d,e,a,b,33); S_R2(b,c,d,e,a,34); S_R2(a,b,c,d,e,35);
	S_R2(e,a,b,c,d,36); S_R2(d,e,a,b,c,37); S_R2(c,d,e,a,b,38); S_R2(b,c,d,e,a,39);
	S_R3(a,b,c,d,e,40); S_R3(e,a,b,c,d,41); S_R3(d,e,a,b,c,42); S_R3(c,d,e,a,b,43);
	S_R3(b,c,d,e,a,44); S_R3(a,b,c,d,e,45); S_R3(e,a,b,c,d,46); S_R3(d,e,a,b,c,47);
	S_R3(c,d,e,a,b,48); S_R3(b,c,d,e,a,49); S_R3(a,b,c,d,e,50); S_R3(e,a,b,c,d,51);
	S_R3(d,e,a,b,c,52); S_R3(c,d,e,a,b,53); S_R3(b,c,d,e,a,54); S_R3(a,b,c,d,e,55);
	S_R3(e,a,b,c,d,56); S_R3(d,e,a,b,c,57); S_R3(c,d,e,a,b,58); S_R3(b,c,d,e,a,59);
	S_R4(a,b,c,d,e,60); S_R4(e,a,b,c,d,61); S_R4(d,e,a,b,c,62); S_R4(c,d,e,a,b,63);
	S_R4(b,c,d,e,a,64); S_R4(a,b,c,d,e,65); S_R4(e,a,b,c,d,66); S_R4(d,e,a,b,c,67);
	S_R4(c,d,e,a,b,68); S_R4(b,c,d,e,a,69); S_R4(a,b,c,d,e,70); S_R4(e,a,b,c,d,71);
	S_R4(d,e,a,b,c,72); S_R4(c,d,e,a,b,73); S_R4(b,c,d,e,a,74); S_R4(a,b,c,d,e,75);
	S_R4(e,a,b,c,d,76); S_R4(d,e,a,b,c,77); S_R4(c,d,e,a,b,78); S_R4(b,c,d,e,a,79);

	// Add the working vars back into state
	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
	state[4] += e;
}

void ON_SHA1::Internal_Accumulate(const ON__UINT8* input, ON__UINT32 length)
{
	ON__UINT32 j = ((m_bit_count[0] >> 3) & 0x3F);

	if((m_bit_count[0] += (length << 3)) < (length << 3))
		++m_bit_count[1]; // Overflow

	m_bit_count[1] += (length >> 29);

	ON__UINT32 i;
	if((j + length) > 63)
	{
		i = 64 - j;
		memcpy(&m_buffer[j], input, i);
		SHA1_transform(m_state, m_buffer);

		for( ; (i + 63) < length; i += 64)
			SHA1_transform(m_state, &input[i]);

		j = 0;
	}
	else i = 0;

	if((length - i) != 0)
		memcpy(&m_buffer[j], &input[i], length - i);
}

void ON_SHA1::set_final_hash()
{
  ON__UINT32 i;
  ON__UINT32 bit_count;
  ON__UINT8 pbFinalCount[8];
  bit_count = m_bit_count[1];
  for (i = 0; i < 4; ++i)
    pbFinalCount[i] = static_cast<ON__UINT8>((bit_count >> ((3 - (i & 3)) * 8)) & 0xFF); // Endian independent
  bit_count = m_bit_count[0];
  for (i = 4; i < 8; ++i)
    pbFinalCount[i] = static_cast<ON__UINT8>((bit_count >> ((3 - (i & 3)) * 8)) & 0xFF); // Endian independent

  //update((ON__UINT8*)"\200", 1);
  const ON__UINT8 byte_80 = 0x80U;
  Internal_Accumulate(&byte_80, 1);

  const ON__UINT8 byte_00 = 0U;
  while ((m_bit_count[0] & 504) != 448)
    Internal_Accumulate(&byte_00, 1);
    //Internal_Accumulate((ON__UINT8*)"\0", 1);

  Internal_Accumulate(pbFinalCount, 8); // Cause a transform()

  for (i = 0; i < 20; ++i)
    m_sha1_hash.m_digest[i] = static_cast<ON__UINT8>((m_state[i >> 2] >> ((3 - (i & 3)) * 8)) & 0xFF);
}

void ON_SHA1::AccumulateBool(
  bool b
)
{
  unsigned char c = b ? 1 : 0;
  AccumulateBytes(&c, sizeof(c));
}

void ON_SHA1::AccumulateInteger8(
  char i
)
{
  AccumulateBytes(&i, 1);
}

void ON_SHA1::AccumulateInteger8(
  ON__INT8 i
)
{
  AccumulateBytes(&i,1);
}

void ON_SHA1::AccumulateUnsigned8(
  ON__UINT8 u
)
{
  AccumulateBytes(&u,1);
}

void ON_SHA1::AccumulateInteger16(
  ON__INT16 i
)
{
  Internal_SwapBigEndianUpdate(&i, sizeof(i) );
}

void ON_SHA1::AccumulateUnsigned16(
  ON__UINT16 u
)
{
  Internal_SwapBigEndianUpdate(&u, sizeof(u) );
}

void ON_SHA1::AccumulateInteger32(
  ON__INT32 i
)
{
  Internal_SwapBigEndianUpdate(&i, sizeof(i) );
}

void ON_SHA1::AccumulateUnsigned32(
  ON__UINT32 u
)
{
  Internal_SwapBigEndianUpdate(&u, sizeof(u) );
}

void ON_SHA1::AccumulateInteger64(
  ON__INT64 i
)
{
  Internal_SwapBigEndianUpdate(&i, sizeof(i) );
}

void ON_SHA1::AccumulateUnsigned64(
  ON__UINT64 u
)
{
  Internal_SwapBigEndianUpdate(&u, sizeof(u) );
}

void ON_SHA1::AccumulateId(
  const ON_UUID& id
)
{
#if defined(ON_RUNTIME_WIN)
  if (ON::Endian() == ON::endian::little_endian)
  {
#endif
    AccumulateBytes(&id, sizeof(ON_UUID));
#if defined(ON_RUNTIME_WIN)
  }
  else
  {
    AccumulateUnsigned32(id.Data1);
    AccumulateUnsigned16(id.Data2);
    AccumulateUnsigned16(id.Data3);
    AccumulateBytes(id.Data4, 8);
  }
#endif
}

void ON_SHA1::AccumulateSubHash(
  const class ON_SHA1_Hash& sub_hash
  )
{
  AccumulateBytes(sub_hash.m_digest, 20);
}

void ON_SHA1::AccumulateDouble(
  double x
)
{
  // -0.0 and +0.0 are identical as double values but have different bit pattern.
  const double v = (0.0 == x ? 0.0 : x);
  Internal_SwapBigEndianUpdate( &v, sizeof(v) );
}

void ON_SHA1::AccumulateDoubleArray(
  size_t count,
  const double* a
)
{
  if (count > 0 && nullptr != a)
  {
    double x, v;
    const double* a1 = a+count;
    while( a < a1)
    {
      x = *a++;
      v = (0.0 == x ? 0.0 : x);
      Internal_SwapBigEndianUpdate( &v, sizeof(v) );
    }
  }
}

void ON_SHA1::AccumulateFloat(
  float x
)
{
  const float v = (0.0f == x ? 0.0f : x);
  Internal_SwapBigEndianUpdate(&v, sizeof(v));
}


void ON_SHA1::AccumulateFloatArray(
  size_t count,
  const float* a
)
{
  if (count > 0 && nullptr != a)
  {
    float x, v;
    const float* a1 = a + count;
    while (a < a1)
    {
      x = *a++;
      v = (0.0f == x ? 0.0f : x);
      Internal_SwapBigEndianUpdate(&v, sizeof(v));
    }
  }
}

void ON_SHA1::AccumulateInteger32Array(size_t count, const ON__INT32* a)
{
  if (count > 0 && nullptr != a)
  {
    const ON__INT32* a1 = a + count;
    ON__INT32 i;
    while (a < a1)
    {
      i = *a++;
      Internal_SwapBigEndianUpdate(&i, sizeof(i));
    }
  }
}

void ON_SHA1::Accumulate2fPoint(
  const class ON_2fPoint& point
)
{
  AccumulateFloatArray(2, &point.x);
}

void ON_SHA1_Accumulate2fPointArray(
  class ON_SHA1& sha1,
  const ON_SimpleArray<ON_2fPoint>& a
)
{
  const ON_2fPoint* aa = a.Array();
  const float* f = (nullptr != aa) ? &aa[0].x : nullptr;
  const size_t count = a.UnsignedCount() * sizeof(aa[0]) / sizeof(f[0]);
  sha1.AccumulateFloatArray(count, f);
}

void ON_SHA1::Accumulate3fPoint(
  const class ON_3fPoint& point
)
{
  AccumulateFloatArray(3, &point.x);
}

void ON_SHA1_Accumulate3fPointArray(
  class ON_SHA1& sha1,
  const ON_SimpleArray<ON_3fPoint>& a
)
{
  const ON_3fPoint* aa = a.Array();
  const float* f = (nullptr != aa) ? &aa[0].x : nullptr;
  const size_t count = a.UnsignedCount() * sizeof(aa[0]) / sizeof(f[0]);
  sha1.AccumulateFloatArray(count, f);
}

void ON_SHA1::Accumulate4fPoint(
  const class ON_4fPoint& point
)
{
  AccumulateFloatArray(4, &point.x);
}

void ON_SHA1_Accumulate4fPointArray(
  class ON_SHA1& sha1,
  const ON_SimpleArray<ON_4fPoint>& a
)
{
  const ON_4fPoint* aa = a.Array();
  const float* f = (nullptr != aa) ? &aa[0].x : nullptr;
  const size_t count = a.UnsignedCount() * sizeof(aa[0]) / sizeof(f[0]);
  sha1.AccumulateFloatArray(count, f);
}

void ON_SHA1::Accumulate2fVector(
  const class ON_2fVector& vector
)
{
  AccumulateFloatArray(2, &vector.x);
}

void ON_SHA1_Accumulate2fVectorArray(
  class ON_SHA1& sha1,
  const ON_SimpleArray<ON_2fVector>& a
)
{
  const ON_2fVector* aa = a.Array();
  const float* f = (nullptr != aa) ? &aa[0].x : nullptr;
  const size_t count = a.UnsignedCount() * sizeof(aa[0]) / sizeof(f[0]);
  sha1.AccumulateFloatArray(count, f);
}

void ON_SHA1::Accumulate3fVector(
  const class ON_3fVector& vector
)
{
  AccumulateFloatArray(3, &vector.x);
}

void ON_SHA1_Accumulate3fVectorArray(
  class ON_SHA1& sha1,
  const ON_SimpleArray<ON_3fVector>& a
)
{
  const ON_3fVector* aa = a.Array();
  const float* f = (nullptr != aa) ? &aa[0].x : nullptr;
  const size_t count = a.UnsignedCount() * sizeof(aa[0]) / sizeof(f[0]);
  sha1.AccumulateFloatArray(count, f);
}


void ON_SHA1::Accumulate2dPoint(
  const ON_2dPoint& point
  )
{
  AccumulateDoubleArray(2,&point.x);
}

void ON_SHA1_Accumulate2dPointArray(
  class ON_SHA1& sha1,
  const ON_SimpleArray<ON_2dPoint>& a
)
{
  const ON_2dPoint* aa = a.Array();
  const double* d = (nullptr != aa) ? &aa[0].x : nullptr;
  const size_t count = a.UnsignedCount() * sizeof(aa[0]) / sizeof(d[0]);
  sha1.AccumulateDoubleArray(count, d);
}

void ON_SHA1::Accumulate3dPoint(
  const ON_3dPoint& point
  )
{
  AccumulateDoubleArray(3,&point.x);
}

void ON_SHA1_Accumulate3dPointArray(
  class ON_SHA1& sha1,
  const ON_SimpleArray<ON_3dPoint>& a
)
{
  const ON_3dPoint* aa = a.Array();
  const double* d = (nullptr != aa) ? &aa[0].x : nullptr;
  const size_t count = a.UnsignedCount() * sizeof(aa[0]) / sizeof(d[0]);
  sha1.AccumulateDoubleArray(count, d);
}

void ON_SHA1::Accumulate4dPoint(
  const ON_4dPoint& point
  )
{
  AccumulateDoubleArray(4,&point.x);
}

void ON_SHA1_Accumulate4dPointArray(
  class ON_SHA1& sha1,
  const ON_SimpleArray<ON_4dPoint>& a
)
{
  const ON_4dPoint* aa = a.Array();
  const double* d = (nullptr != aa) ? &aa[0].x : nullptr;
  const size_t count = a.UnsignedCount() * sizeof(aa[0]) / sizeof(d[0]);
  sha1.AccumulateDoubleArray(count, d);
}

void ON_SHA1::Accumulate2dVector(
  const ON_2dVector& vector
  )
{
  AccumulateDoubleArray(2,&vector.x);
}

void ON_SHA1_Accumulate2dVectorArray(
  class ON_SHA1& sha1,
  const ON_SimpleArray<ON_2dVector>& a
)
{
  const ON_2dVector* aa = a.Array();
  const double* d = (nullptr != aa) ? &aa[0].x : nullptr;
  const size_t count = a.UnsignedCount() * sizeof(aa[0]) / sizeof(d[0]);
  sha1.AccumulateDoubleArray(count, d);
}

void ON_SHA1::Accumulate3dVector(
  const ON_3dVector& vector
  )
{
  AccumulateDoubleArray(3,&vector.x);
}

void ON_SHA1_Accumulate3dVectorArray(
  class ON_SHA1& sha1,
  const ON_SimpleArray<ON_3dVector>& a
)
{
  const ON_3dVector* aa = a.Array();
  const double* d = (nullptr != aa) ? &aa[0].x : nullptr;
  const size_t count = a.UnsignedCount() * sizeof(aa[0]) / sizeof(d[0]);
  sha1.AccumulateDoubleArray(count, d);
}

void ON_SHA1::AccumulateUnitSystem
(
  const class ON_UnitSystem& unit_system
)
{
  const ON::LengthUnitSystem length_unit_system = unit_system.UnitSystem();
  AccumulateLengthUnitSystem(length_unit_system);
  if (ON::LengthUnitSystem::CustomUnits == length_unit_system)
  {
    AccumulateDouble(unit_system.MetersPerUnit(ON_DBL_QNAN));
    AccumulateString(unit_system.UnitSystemName());
  }
}

void ON_SHA1::AccumulateLengthUnitSystem
(
  const ON::LengthUnitSystem length_unit_system
)
{
  AccumulateUnsigned8(static_cast<unsigned char>(length_unit_system));
}

void ON_SHA1::AccumulateFileReference(
  const class ON_FileReference& file_reference
)
{
  AccumulateString(file_reference.FullPath());
  AccumulateString(file_reference.RelativePath());
}

void ON_SHA1::AccumulateBoundingBox(
  const class ON_BoundingBox& bbox
)
{
  if (bbox.IsSet())
  {
    Accumulate3dPoint(bbox.m_min);
    Accumulate3dPoint(bbox.m_max);
  }
  else
  {
    Accumulate3dPoint(ON_BoundingBox::UnsetBoundingBox.m_min);
    Accumulate3dPoint(ON_BoundingBox::UnsetBoundingBox.m_max);
  }
}
  
void ON_SHA1::AccumulateTransformation(
  const class ON_Xform& xform
)
{
  AccumulateDoubleArray(16,&xform.m_xform[0][0]);
}

void ON_SHA1::Internal_SwapBigEndianUpdate(
  const void* buffer,
  ON__UINT64 sizeof_buffer
)
{
  if (ON::Endian() == ON::endian::big_endian && nullptr != buffer && sizeof_buffer > 0)
  {
    unsigned char reversed_buffer[32];
    const ON__UINT64 reversed_buffer_capacity = (ON__UINT64)sizeof(reversed_buffer);
    ON__UINT64 sizeof_reversed_buffer;
    const char* p0 = (const char*)buffer;
    const char* p1 = p0 + sizeof_buffer;
    while (p0 < p1)
    {
      for (sizeof_reversed_buffer = 0; sizeof_reversed_buffer < reversed_buffer_capacity; sizeof_reversed_buffer++)
      {
        reversed_buffer[sizeof_reversed_buffer] = *--p1;
        if (p0 == p1)
          break;
      }
      AccumulateBytes( reversed_buffer, sizeof_reversed_buffer );
    }
  }
  else
  {
    AccumulateBytes(buffer, sizeof_buffer);
  }
}


void ON_SHA1::AccumulateBytes(
  const void* buffer,
  ON__UINT64 sizeof_buffer
  )
{
  if (nullptr != buffer && sizeof_buffer > 0)
  {
    if (1 != (1 & m_status_bits))
      Reset();
    m_status_bits = 1; // invalidate any intermediate cached m_digest value.
    m_byte_count += sizeof_buffer;
    const ON__UINT32 max_length = 0x0FFFFFFFU;
    const ON__UINT8* p = (const ON__UINT8*)buffer;
    while (sizeof_buffer > max_length)
    {
      Internal_Accumulate(p,max_length);
      sizeof_buffer -= max_length;
      p += max_length;
    }
    Internal_Accumulate(p,(ON__UINT32)sizeof_buffer);
  }
}


ON_SHA1_Hash ON_SHA1::Hash() const
{
  if (2 != (2 & m_status_bits))
  {
    ON_SHA1 tmp(*this);
    if (1 != (1 & m_status_bits))
      tmp.Reset();
    tmp.set_final_hash();
    m_sha1_hash = tmp.m_sha1_hash;
    m_status_bits |= 2;
  }
  return m_sha1_hash;
}

ON__UINT64 ON_SHA1::ByteCount() const
{
  return m_byte_count;
}

static bool SHA1_ValidateHelper(
  const char* str,
  const ON__UINT8 standard[20]
  )
{
  const int str_length = ON_String::Length(str);
  ON_SHA1 sha1;
  sha1.AccumulateBytes(str, str_length);
  const ON_SHA1_Hash sha1_digest(sha1.Hash());
  if ( 0 != memcmp(standard, &sha1_digest, 20) )
    return false;

  bool rc = true;
  for (int i = 0; i <= str_length && rc; i++)
  {
    for (int j = 0; i+j <= str_length && rc; j++)
    {
      sha1.Reset();
      sha1.AccumulateBytes(str, i);
      sha1.Hash();
      sha1.AccumulateBytes(str+i, j);
      sha1.Hash();
      sha1.AccumulateBytes(str+i+j, str_length-i-j);
      ON_SHA1_Hash sha1_digest1(sha1.Hash());
      rc = ( sha1_digest == sha1_digest1 );
    }
  }

  if (rc)
  {
    if ( (ON__UINT64)str_length != sha1.ByteCount() )
      rc = false;
  }

  return rc;
}

bool ON_SHA1::Validate()
{
  // "" (empty string)
  // da39a3ee 5e6b4b0d 3255bfef 95601890 afd80709
  const ON__UINT8 empty_string[20] = {
    0xda, 0x39, 0xa3, 0xee,
    0x5e, 0x6b, 0x4b, 0x0d,
    0x32, 0x55, 0xbf, 0xef,
    0x95, 0x60, 0x18, 0x90,
    0xaf, 0xd8, 0x07, 0x09 
  };
  if (false == SHA1_ValidateHelper("",empty_string))
    return false;

  
  if (0 != memcmp(&ON_SHA1_Hash::EmptyContentHash ,empty_string, sizeof(empty_string)))
    return false;

  // "abc"
  // a9993e36 4706816a ba3e2571 7850c26c 9cd0d89d
  const ON__UINT8 abc[20]  = { 
    0xa9, 0x99, 0x3e, 0x36,
    0x47, 0x06, 0x81, 0x6a,
    0xba, 0x3e, 0x25, 0x71,
    0x78, 0x50, 0xc2, 0x6c,
    0x9c, 0xd0, 0xd8, 0x9d  
  };
  if (false == SHA1_ValidateHelper("abc",abc))
    return false;

  // "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"
  // 84983e44 1c3bd26e baae4aa1 f95129e5 e54670f1
  const ON__UINT8 abc_x[20] = { 
    0x84, 0x98, 0x3e, 0x44,
    0x1c, 0x3b, 0xd2, 0x6e,
    0xba, 0xae, 0x4a, 0xa1,
    0xf9, 0x51, 0x29, 0xe5,
    0xe5, 0x46, 0x70, 0xf1 
  };
  if (false == SHA1_ValidateHelper("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",abc_x))
    return false;

  // "The quick brown fox jumps over the lazy dog"
  // 2fd4e1c6 7a2d28fc ed849ee1 bb76e739 1b93eb12
  const ON__UINT8 quickfox[20] = {
    0x2f, 0xd4, 0xe1, 0xc6,
    0x7a, 0x2d, 0x28, 0xfc,
    0xed, 0x84, 0x9e, 0xe1,
    0xbb, 0x76, 0xe7, 0x39,
    0x1b, 0x93, 0xeb, 0x12 
  };
  if (false == SHA1_ValidateHelper("The quick brown fox jumps over the lazy dog",quickfox))
    return false;

  // "The quick brown fox jumps over the lazy cog"
  // de9f2c7f d25e1b3a fad3e85a 0bd17d9b 100db4b3
  const ON__UINT8 lazycog[20] = {
    0xde, 0x9f, 0x2c, 0x7f,
    0xd2, 0x5e, 0x1b, 0x3a,
    0xfa, 0xd3, 0xe8, 0x5a,
    0x0b, 0xd1, 0x7d, 0x9b,
    0x10, 0x0d, 0xb4, 0xb3 
  };
  if (false == SHA1_ValidateHelper("The quick brown fox jumps over the lazy cog",lazycog))
    return false;

  // "The quick brown fox jumps over the lazy dog."
  // 408d9438 4216f890 ff7a0c35 28e8bed1 e0b01621
  const ON__UINT8 quickfoxperiod[20] = {
    0x40, 0x8d, 0x94, 0x38,
    0x42, 0x16, 0xf8, 0x90,
    0xff, 0x7a, 0x0c, 0x35,
    0x28, 0xe8, 0xbe, 0xd1,
    0xe0, 0xb0, 0x16, 0x21 
  };
  if (false == SHA1_ValidateHelper("The quick brown fox jumps over the lazy dog.",quickfoxperiod))
    return false;

  // 1,000,000 repetitions of the character "a".
  // 34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F
  const ON__UINT8 millionXa[20] = {
    0x34, 0xAA, 0x97, 0x3C,
    0xD4, 0xC4, 0xDA, 0xA4,
    0xF6, 0x1E, 0xEB, 0x2B,
    0xDB, 0xAD, 0x27, 0x31,
    0x65, 0x34, 0x01, 0x6F 
  };

  const size_t one_million = 1000000;
  ON__UINT8 a[200];
  const size_t a_count = sizeof(a) / sizeof(a[0]);
  for ( size_t i = 0; i < a_count; i++)
    a[i] = 'a';  
  ON_SHA1 sha1;
  size_t total_count = 0;
  for (total_count = 0; total_count < one_million; total_count += a_count)
  {
    sha1.AccumulateBytes(a, a_count);
    if (sha1.ByteCount() != (ON__UINT64)(total_count+a_count))
      return false;
  }
  
  ON_SHA1_Hash sha1_digest(sha1.Hash());

  if (0 != memcmp(&sha1_digest,millionXa,sizeof(millionXa)))
    return false;

  sha1.Reset();
  ON_RandomNumberGenerator rng;
  total_count = 0; 
  const size_t min_count = (a_count >= 10000) ? a_count/1000 : 100;
  while (total_count < one_million)
  {
    size_t count = min_count + (rng.RandomNumber() % (ON__UINT32)min_count);
    if ( total_count + count > one_million )
      count = one_million - total_count;
    sha1.AccumulateBytes(a, count);
    total_count += count;
    if (sha1.ByteCount() != (ON__UINT64)total_count)
      return false;
  }

  
  ON_SHA1_Hash sha1_digestx(sha1.Hash());

  if (0 != memcmp(&sha1_digestx,millionXa,sizeof(millionXa)))
    return false;

  return true;
}
