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

/*
Description:
  ON_MD5 is a small class for calculating the MD5 hash of a sequence of bytes.
  It may be use incrementally (the bytes do not have to be in a contiguous
  array in memory at one time).

Remarks:
  Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All rights reserved.
 
  License to copy and use this software is granted provided that it
  is identified as the "RSA Data Security, Inc. MD5 Message-Digest
  Algorithm" in all material mentioning or referencing this software
  or this function.
 
  License is also granted to make and use derivative works provided
  that such works are identified as "derived from the RSA Data
  Security, Inc. MD5 Message-Digest Algorithm" in all material
  mentioning or referencing the derived work.
 
  RSA Data Security, Inc. makes no representations concerning either
  the merchantability of this software or the suitability of this
  software for any particular purpose. It is provided "as is"
  without express or implied warranty of any kind.
 
  These notices must be retained in any copies of any part of this
  documentation and/or software.
*/

ON_MD5_Hash::ON_MD5_Hash()
{
  ON__UINT32* p = (ON__UINT32*)m_digest;
  p[0] = 0U;
  p[1] = 0U;
  p[2] = 0U;
  p[3] = 0U;
}

bool operator==(const ON_MD5_Hash& a, const ON_MD5_Hash& b)
{
  const ON__UINT32* ai = (const ON__UINT32*)&a;
  const ON__UINT32* bi = (const ON__UINT32*)&b;
  return (ai[0] == bi[0] && ai[1] == bi[1] && ai[2] == bi[2] && ai[3] == bi[3]);
}

bool operator!=(const ON_MD5_Hash& a, const ON_MD5_Hash& b)
{
  const ON__UINT32* ai = (const ON__UINT32*)&a;
  const ON__UINT32* bi = (const ON__UINT32*)&b;
  return (ai[0] != bi[0] || ai[1] != bi[1] || ai[2] != bi[2] || ai[3] != bi[3]);
}

int ON_MD5_Hash::Compare(
  const ON_MD5_Hash& a,
  const ON_MD5_Hash& b
  )
{
  for (int i = 0; i < 16; i++)
  {
    if (a.m_digest[i] < b.m_digest[i])
      return -1;
    if (a.m_digest[i] > b.m_digest[i])
      return 1;
  }
  return 0;
}

const ON_String ON_MD5_Hash::ToUTF8String(
  bool bUpperCaseHexadecimalDigits
  ) const
{
  return ON_String::HexadecimalFromBytes(m_digest, sizeof(m_digest),bUpperCaseHexadecimalDigits,false);
}

const ON_wString ON_MD5_Hash::ToString(
  bool bUpperCaseHexadecimalDigits
  ) const
{
  return ON_wString::HexadecimalFromBytes(m_digest, sizeof(m_digest),bUpperCaseHexadecimalDigits,false);
}
  
bool ON_MD5_Hash::Read(
  class ON_BinaryArchive& archive
  )
{
  *this = ON_MD5_Hash::ZeroDigest;
  bool rc = false;
  int major_version = 0;
  int minor_version = 0;
  if (!archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version))
    return rc;
  for (;;)
  {
    if ( 1 != major_version )
      break;
    if (!archive.ReadByte(16,m_digest))
      break;
    rc = true;
    break;
  }
  if (!archive.EndWrite3dmChunk())
    rc = false;
  return rc;
}


bool ON_MD5_Hash::Write(
  class ON_BinaryArchive& archive
  ) const
{
  if (!archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0))
    return false;
  bool rc = archive.WriteByte(16,m_digest);
  if (!archive.EndWrite3dmChunk())
    rc = false;
  return rc;
}

  void ON_MD5_Hash::Dump(
class ON_TextLog& text_log
  ) const
{
  const ON_wString md5_hash(ToString(true));
  text_log.Print(L"MD5 hash = %ls\n",static_cast<const wchar_t*>(md5_hash));
}


ON_MD5_Hash ON_MD5_Hash::BufferHash(
  const void* buffer,
  size_t sizeof_buffer
  )
{
  if ( nullptr == buffer || sizeof_buffer <= 0 )
    return ON_MD5_Hash::EmptyContentHash;
  ON_MD5 md5;
  md5.AccumulateBytes(buffer,sizeof_buffer);
  return md5.Hash();
}

ON_MD5_Hash ON_MD5_Hash::FileHash(
  const wchar_t* filename,
  ON__UINT64& sizeof_file
  )
{
  FILE* fp = 
    ( nullptr == filename ||  0 == filename[0] )
    ? nullptr
    : ON_FileStream::Open(filename, L"rb");
  ON_MD5_Hash md5_hash = ON_MD5_Hash::FileHash(fp,sizeof_file);
  ON_FileStream::Close(fp);
  return md5_hash;
}

ON_MD5_Hash ON_MD5_Hash::FileHash(
  const char* filename,
  ON__UINT64& sizeof_file
  )
{
  FILE* fp = 
    ( nullptr == filename ||  0 == filename[0] )
    ? nullptr
    : ON_FileStream::Open(filename, "rb");
  ON_MD5_Hash md5_hash = ON_MD5_Hash::FileHash(fp,sizeof_file);
  ON_FileStream::Close(fp);
  return md5_hash;
}

ON_MD5_Hash ON_MD5_Hash::FileHash(
  FILE* file,
  ON__UINT64& sizeof_file
  )
{
  sizeof_file = 0;
  if ( nullptr == file )
    return ON_MD5_Hash::EmptyContentHash;
  size_t sizeof_buffer = 1024;
  void* buffer = onmalloc(sizeof_buffer);
  ON_MD5 md5;
  for (ON__UINT64 byte_count = ON_FileStream::Read(file, sizeof_buffer, buffer);
    byte_count > 0;
    byte_count = ON_FileStream::Read(file, sizeof_buffer, buffer)
    )
  {
    md5.AccumulateBytes(buffer,byte_count);
  }
  onfree(buffer);
  sizeof_file = md5.ByteCount();
  return md5.Hash();
}

ON_MD5_Hash ON_MD5_Hash::StringHash(
  const ON_wString& str,
  ON__UINT64& byte_count
  )
{
  return ON_MD5_Hash::StringHash(
    static_cast<const wchar_t*>(str),
    (size_t)str.Length(),
    byte_count
    );
}

ON_MD5_Hash ON_MD5_Hash::StringHash(
  const wchar_t* str,
  size_t str_length,
  ON__UINT64& byte_count
  )
{
  byte_count = 0;
  if ( nullptr == str || str_length <= 0 )
    return ON_MD5_Hash::EmptyContentHash;

  ON_MD5 md5;
  const int UTF8buffer_capacity = 1024;
  char* UTF8buffer = (char*)onmalloc(UTF8buffer_capacity);

  const int bTestByteOrder = false;
  const ON__UINT32 error_code_point = 0xFFFD;
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
      md5.AccumulateBytes(UTF8buffer,UTF8_count);

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
  byte_count = md5.ByteCount();
  return md5.Hash();
}

ON_MD5_Hash ON_MD5_Hash::StringHash(
  const ON_String& str,
  ON__UINT64& byte_count
  )
{
  return ON_MD5_Hash::StringHash(
    static_cast<const char*>(str),
    (size_t)str.Length(),
    byte_count
    );
}

ON_MD5_Hash ON_MD5_Hash::StringHash(
  const char* str,
  size_t str_length,
  ON__UINT64& byte_count
  )
{
  byte_count = (nullptr != str && str_length > 0) ? ((ON__UINT64)str_length) : 0;
  return ON_MD5_Hash::BufferHash(str,str_length);
}

// Constants for MD5Transform routine.
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21
 
///////////////////////////////////////////////
 
// F, G, H and I are basic MD5 functions.
static ON__UINT32 MD5_F(ON__UINT32 x, ON__UINT32 y, ON__UINT32 z) 
{
  return (x&y) | (~x&z);
}
 
static ON__UINT32 MD5_G(ON__UINT32 x, ON__UINT32 y, ON__UINT32 z)
{
  return (x&z) | (y&~z);
}
 
static ON__UINT32 MD5_H(ON__UINT32 x, ON__UINT32 y, ON__UINT32 z)
{
  return x^y^z;
}
 
static ON__UINT32 MD5_I(ON__UINT32 x, ON__UINT32 y, ON__UINT32 z)
{
  return y ^ (x | ~z);
}
 
// rotate_left rotates x left n bits.
static ON__UINT32 MD5_rotate_left(ON__UINT32 x, int n)
{
  return (x << n) | (x >> (32-n));
}
 
// FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
// Rotation is separate from addition to prevent recomputation.
static void MD5_FF(ON__UINT32 &a, ON__UINT32 b, ON__UINT32 c, ON__UINT32 d, ON__UINT32 x, ON__UINT32 s, ON__UINT32 ac) 
{
  a = MD5_rotate_left(a+ MD5_F(b,c,d) + x + ac, s) + b;
}
 
static void MD5_GG(ON__UINT32 &a, ON__UINT32 b, ON__UINT32 c, ON__UINT32 d, ON__UINT32 x, ON__UINT32 s, ON__UINT32 ac)
{
  a = MD5_rotate_left(a + MD5_G(b,c,d) + x + ac, s) + b;
}
 
static void MD5_HH(ON__UINT32 &a, ON__UINT32 b, ON__UINT32 c, ON__UINT32 d, ON__UINT32 x, ON__UINT32 s, ON__UINT32 ac) 
{
  a = MD5_rotate_left(a + MD5_H(b,c,d) + x + ac, s) + b;
}
 
static void MD5_II(ON__UINT32 &a, ON__UINT32 b, ON__UINT32 c, ON__UINT32 d, ON__UINT32 x, ON__UINT32 s, ON__UINT32 ac) 
{
  a = MD5_rotate_left(a + MD5_I(b,c,d) + x + ac, s) + b;
}
 
//////////////////////////////////////////////
 
 
//////////////////////////////////////////////
 
//// nifty shortcut ctor, compute MD5 for string and finalize it right away
//MD5::MD5(const std::string &text)
//{
//  init();
//  update(text.c_str(), text.length());
//  finalize();
//}
 
//////////////////////////////

static bool MD5_ValidateHelper(
  const char* str,
  const ON__UINT8 standard[16]
  )
{
  const int str_length = ON_String::Length(str);
  ON_MD5 md5;
  md5.AccumulateBytes(str, str_length);
  const ON_MD5_Hash md5_digest(md5.Hash());
  if ( 0 != memcmp(standard, &md5_digest, 16) )
    return false;

  bool rc = true;
  for (int i = 0; i <= str_length && rc; i++)
  {
    for (int j = 0; i+j <= str_length && rc; j++)
    {
      md5.Reset();
      md5.AccumulateBytes(str, i);
      md5.Hash();
      md5.AccumulateBytes(str+i, j);
      md5.Hash();
      md5.AccumulateBytes(str+i+j, str_length-i-j);
      ON_MD5_Hash md5_digest1(md5.Hash());
      rc = ( md5_digest == md5_digest1 );
    }
  }

  if (rc)
  {
    if ( (ON__UINT64)str_length != md5.ByteCount() )
      rc = false;
  }

  return rc;
}

bool ON_MD5::Validate()
{
  // http://onlinemd5.com/

  // "" (empty string)
  // d41d8cd9 8f00b204 e9800998 ecf8427e
  const ON__UINT8 empty_string[16] = {
    0xd4, 0x1d, 0x8c, 0xd9,
    0x8f, 0x00, 0xb2, 0x04,
    0xe9, 0x80, 0x09, 0x98,
    0xec, 0xf8, 0x42, 0x7e };
  if (false == MD5_ValidateHelper("",empty_string))
    return false;

  
  if (0 != memcmp(&ON_MD5_Hash::EmptyContentHash ,empty_string, sizeof(empty_string)))
    return false;

  // "abc"
  // 90015098 3CD24FB0 D6963F7D 28E17F72
  const ON__UINT8 abc[16]  = { 
    0x90, 0x01, 0x50, 0x98,
    0x3C, 0xD2, 0x4F, 0xB0,
    0xD6, 0x96, 0x3F, 0x7D,
    0x28, 0xE1, 0x7F, 0x72  };
  if (false == MD5_ValidateHelper("abc",abc))
    return false;

  // "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"
  // 8215EF07 96A20BCA AAE116D3 876C664A
  const ON__UINT8 abc_x[16] = { 
    0x82, 0x15, 0xEF, 0x07,
    0x96, 0xA2, 0x0B, 0xCA,
    0xAA, 0xE1, 0x16, 0xD3,
    0x87, 0x6C, 0x66, 0x4A };
  if (false == MD5_ValidateHelper("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",abc_x))
    return false;

  // "The quick brown fox jumps over the lazy dog"
  // 9E107D9D 372BB682 6BD81D35 42A419D6
  const ON__UINT8 quickfox[16] = {
    0x9E, 0x10, 0x7D, 0x9D,
    0x37, 0x2B, 0xB6, 0x82,
    0x6B, 0xD8, 0x1D, 0x35,
    0x42, 0xA4, 0x19, 0xD6 };
  if (false == MD5_ValidateHelper("The quick brown fox jumps over the lazy dog",quickfox))
    return false;

  // "The quick brown fox jumps over the lazy dog."
  // E4D909C2 90D0FB1C A068FFAD DF22CBD0
  const ON__UINT8 quickfoxperiod[16] = {
    0xE4, 0xD9, 0x09, 0xC2,
    0x90, 0xD0, 0xFB, 0x1C,
    0xA0, 0x68, 0xFF, 0xAD,
    0xDF, 0x22, 0xCB, 0xD0 };
  if (false == MD5_ValidateHelper("The quick brown fox jumps over the lazy dog.",quickfoxperiod))
    return false;

  // 1,000,000 repetitions of the character "a".
  // 7707D6AE 4E027C70 EEA2A935 C2296F21.
  const ON__UINT8 millionXa[16] = {
    0x77, 0x07, 0xD6, 0xAE,
    0x4E, 0x02, 0x7C, 0x70,
    0xEE, 0xA2, 0xA9, 0x35,
    0xC2, 0x29, 0x6F, 0x21 };

  const size_t one_million = 1000000;
  ON__UINT8 a[200];
  const size_t a_count = sizeof(a) / sizeof(a[0]);
  for ( size_t i = 0; i < a_count; i++)
    a[i] = 'a';  
  ON_MD5 md5;
  size_t total_count = 0;
  for (total_count = 0; total_count < one_million; total_count += a_count)
  {
    md5.AccumulateBytes(a, a_count);
    if (md5.ByteCount() != (ON__UINT64)(total_count+a_count))
      return false;
  }
  
  ON_MD5_Hash md5_digest(md5.Hash());

  if (0 != memcmp(&md5_digest,millionXa,sizeof(millionXa)))
    return false;

  md5.Reset();
  ON_RandomNumberGenerator rng;
  total_count = 0; 
  const size_t min_count = (a_count >= 10000) ? a_count/1000 : 100;
  while (total_count < one_million)
  {
    size_t count = min_count + (rng.RandomNumber() % (ON__UINT32)min_count);
    if ( total_count + count > one_million )
      count = one_million - total_count;
    md5.AccumulateBytes(a, count);
    total_count += count;
    if (md5.ByteCount() != (ON__UINT64)total_count)
      return false;
  }

  ON_MD5_Hash md5_digestx(md5.Hash());
  if (0 != memcmp(&md5_digestx,millionXa,sizeof(millionXa)))
    return false;


  return true;
}
 
ON__UINT64 ON_MD5::ByteCount() const
{
  return m_byte_count;
}

void ON_MD5::Reset()
{
  m_status_bits = 0;
  m_byte_count = 0;

  m_bit_count[0] = 0;
  m_bit_count[1] = 0;

  // MD5 initialization constants
  m_state[0] = 0x67452301;
  m_state[1] = 0xefcdab89;
  m_state[2] = 0x98badcfe;
  m_state[3] = 0x10325476;

  m_status_bits = 1;
}

ON_MD5_Hash ON_MD5::Hash() const
{
  if (2 != (2 & m_status_bits))
  {
    ON_MD5 tmp(*this);
    if (1 != (1 & m_status_bits))
      tmp.Reset();
    tmp.set_final_hash();
    m_md5_hash = tmp.m_md5_hash;
    m_status_bits |= 2;
  }
  return m_md5_hash;
}

void ON_MD5::AccumulateBytes(
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

 
//////////////////////////////
 
// decodes input (unsigned char) into output (ON__UINT32). Assumes len is a multiple of 4.
static void  MD5_decode(ON__UINT32 output[], const ON__UINT8 input[], ON__UINT32 len)
{
  for (unsigned int i = 0, j = 0; j < len; i++, j += 4)
    output[i] = ((ON__UINT32)input[j]) | (((ON__UINT32)input[j+1]) << 8) |
      (((ON__UINT32)input[j+2]) << 16) | (((ON__UINT32)input[j+3]) << 24);
}
 
//////////////////////////////
 
// encodes input (ON__UINT32) into output (unsigned char). Assumes len is
// a multiple of 4.
static void MD5_encode(ON__UINT8 output[], const ON__UINT32 input[], ON__UINT32 len)
{
  for (ON__UINT32 i = 0, j = 0; j < len; i++, j += 4) {
    output[j] = input[i] & 0xff;
    output[j+1] = (input[i] >> 8) & 0xff;
    output[j+2] = (input[i] >> 16) & 0xff;
    output[j+3] = (input[i] >> 24) & 0xff;
  }
}
 
//////////////////////////////
 
// apply MD5 algo on a block
static void MD5_transform(const ON__UINT8 block[64], ON__UINT32 state[4])
{
  ON__UINT32 a = state[0], b = state[1], c = state[2], d = state[3], x[16];
  MD5_decode (x, block, 64);
 
  /* Round 1 */
  MD5_FF (a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
  MD5_FF (d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
  MD5_FF (c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
  MD5_FF (b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
  MD5_FF (a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
  MD5_FF (d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
  MD5_FF (c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
  MD5_FF (b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
  MD5_FF (a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
  MD5_FF (d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
  MD5_FF (c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
  MD5_FF (b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
  MD5_FF (a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
  MD5_FF (d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
  MD5_FF (c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
  MD5_FF (b, c, d, a, x[15], S14, 0x49b40821); /* 16 */
 
  /* Round 2 */
  MD5_GG (a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
  MD5_GG (d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
  MD5_GG (c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
  MD5_GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
  MD5_GG (a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
  MD5_GG (d, a, b, c, x[10], S22,  0x2441453); /* 22 */
  MD5_GG (c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
  MD5_GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
  MD5_GG (a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
  MD5_GG (d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
  MD5_GG (c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
  MD5_GG (b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
  MD5_GG (a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
  MD5_GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
  MD5_GG (c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
  MD5_GG (b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */
 
  /* Round 3 */
  MD5_HH (a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
  MD5_HH (d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
  MD5_HH (c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
  MD5_HH (b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
  MD5_HH (a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
  MD5_HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
  MD5_HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
  MD5_HH (b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
  MD5_HH (a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
  MD5_HH (d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
  MD5_HH (c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
  MD5_HH (b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
  MD5_HH (a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
  MD5_HH (d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
  MD5_HH (c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
  MD5_HH (b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */
 
  /* Round 4 */
  MD5_II (a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
  MD5_II (d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
  MD5_II (c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
  MD5_II (b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
  MD5_II (a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
  MD5_II (d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
  MD5_II (c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
  MD5_II (b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
  MD5_II (a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
  MD5_II (d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
  MD5_II (c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
  MD5_II (b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
  MD5_II (a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
  MD5_II (d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
  MD5_II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
  MD5_II (b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */
 
  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;
}
 
void ON_MD5::Internal_Accumulate(const ON__UINT8* input, ON__UINT32 length)
{
  // MD5 block update operation. Continues an MD5 message-digest
  // operation, processing another message block.

  // compute number of bytes mod 64
  ON__UINT32 index = m_bit_count[0] / 8 % 64;
 
  // Update number of bits
  if ((m_bit_count[0] += (length << 3)) < (length << 3))
    m_bit_count[1]++;
  m_bit_count[1] += (length >> 29);
 
  // number of bytes we need to fill in buffer
  ON__UINT32 firstpart = 64 - index;
 
  ON__UINT32 i;
 
  // transform as many times as possible.
  if (length >= firstpart)
  {
    // fill buffer first, transform
    memcpy(&m_buffer[index], input, firstpart);
    MD5_transform(m_buffer, m_state);
 
    // transform chunks of blocksize (64 bytes)
    for (i = firstpart; i + 64 <= length; i += 64)
      MD5_transform(&input[i], m_state);
 
    index = 0;
  }
  else
    i = 0;
 
  // buffer remaining input
  memcpy(&m_buffer[index], &input[i], length-i);
}
 
void ON_MD5::set_final_hash()
{
  // MD5 finalization. 
  // Ends an MD5 message-digest operation and writes the message digest.
  static unsigned char padding[64] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };

  // Save number of bits
  unsigned char bits[8];
  MD5_encode(bits, m_bit_count, 8);
 
  // pad out to 56 mod 64.
  const ON__UINT32 index = (m_bit_count[0] / 8) % 64;
  const ON__UINT32 padLen = (index < 56) ? (56 - index) : (120 - index);
  Internal_Accumulate(padding, padLen);
 
  // Append length (before padding)
  Internal_Accumulate(bits, 8);
 
  // Store final state in digest
  MD5_encode(m_md5_hash.m_digest, m_state, 16);
}
 
