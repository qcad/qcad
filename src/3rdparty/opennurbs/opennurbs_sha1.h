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

#if !defined(OPENNURBS_SHA1_INC_)
#define OPENNURBS_SHA1_INC_

class ON_CLASS ON_SHA1_Hash
{
public:
  static const ON_SHA1_Hash ZeroDigest;       // all digest bytes are zero
  static const ON_SHA1_Hash EmptyContentHash; // SHA-1 hash of zero bytes

  // The default constructor creates a zero digest sha1 hash
  ON_SHA1_Hash();

  ~ON_SHA1_Hash() = default;
  ON_SHA1_Hash(const ON_SHA1_Hash&) = default;
  ON_SHA1_Hash& operator=(const ON_SHA1_Hash&) = default;

  static int Compare(
    const ON_SHA1_Hash& a,
    const ON_SHA1_Hash& b
    );

  /*
  Parameters:
    buffer - [in]
    sizeof_buffer - [in]
      number of bytes in buffer
  Returns:
    SHA1-1 hash of the buffer.
  */
  static ON_SHA1_Hash BufferContentHash(
    const void* buffer,
    size_t sizeof_buffer
    );

  /*
  Parameters:
    file_name - [in]
      Name of file
    sizeof_file - [out]
      number of bytes in file
  Returns:
    SHA1-1 hash of the buffer.
  */
  static ON_SHA1_Hash FileContentHash(
    const wchar_t* file_name,
    ON__UINT64& sizeof_file
    );

  static ON_SHA1_Hash FileContentHash(
    const char* file_name,
    ON__UINT64& sizeof_file
    );
    
  /*
  Description:
    Return a hash of the file system path that is independent 
    of the size of wchar_t, constant across platforms, and 
    constant across variations in the way the path is formatted.

  Parameters:
    path - [in]
      File system path to a directory or file.

  Returns:
    SHA1-1 hash of the buffer.

  Example:
    These file system paths have identical values of FileSystemPathHash().
    /x/y/z/name.ext
    \x\y\z\name.ext
    /x//y//z/name.ext
    /x/y/a/b/c/../../../z/name.ext
    /X/Y/Z/NAME.EXT (When ON_ComparePathIgnoreCase() is true)

  Remarks:
    This function uses the value of ON_FileSystemPath::PlatformPathIgnoreCase()
    to determine  if case should be ignored. Use the version with a bIgnoreCase
    parameter if you want to explicitly control this decision.
  */
  static ON_SHA1_Hash FileSystemPathHash(
    const wchar_t* path
    );

  static ON_SHA1_Hash FileSystemPathHash(
    const char* path
    );

  static ON_SHA1_Hash FileSystemPathHash(
    const wchar_t* path,
    bool bIgnoreCase
    );

  static ON_SHA1_Hash FileSystemPathHash(
    const char* path,
    bool bIgnoreCase
    );

  /*
  Parameters:
    file - [in]
      File stream from ON_FileStream::Open(...,L"rb");
    sizeof_file - [out]
      number of bytes in file
  Returns:
    SHA1-1 hash of the file stream from the current
    offset to the end of the file.
  */
  static ON_SHA1_Hash FileContentHash(
    FILE* file,
    ON__UINT64& sizeof_file
    );

  /*
  Parameters:
    str - [in]
      string
    byte_count - [out]
      number of bytes in UTF-8 encoding of the string.
  Returns:
    SHA1-1 hash of the UTF-8 encoding of the string. (Platforms and endian independent.)
  */
  static ON_SHA1_Hash StringHash(
    const ON_wString& str,
    ON__UINT64& byte_count
    );

  static ON_SHA1_Hash StringHash(
    const wchar_t* str,
    size_t str_length,
    ON__UINT64& byte_count
    );

  static ON_SHA1_Hash StringHash(
    const wchar_t* null_terminated_string
    );

  /*
  Parameters:
    str - [in]
    byte_count - [out]
      number of bytes in the string.
  Returns:
    SHA1-1 hash of the UTF-8 encoding of the string. (Platforms and endian independent.)
  */
  static ON_SHA1_Hash StringHash(
    const ON_String& str,
    ON__UINT64& byte_count
    );

  static ON_SHA1_Hash StringHash(
    const char* str,
    size_t str_length,
    ON__UINT64& byte_count
    );


  static ON_SHA1_Hash StringHash(
    const char* null_terminated_string
    );

  /*
  Parameters:
    bUpperCaseHexadecimalDigits - [in]
      false - use 0-9, a-f
      true - use 0-9, A-F
  Returns:
    The SHA-1 hash value as a 40 hexadecimal digits.
    The first digit in the string is the hexadecimal value of m_digest[0].
  */
  const ON_String ToUTF8String(
    bool bUpperCaseHexadecimalDigits
    ) const;

  /*
  Parameters:
    bUpperCaseHexadecimalDigits - [in]
      false - use 0-9, a-f
      true - use 0-9, A-F
  Returns:
    The SHA-1 hash value as a 40 hexadecimal digits.
    The first digit in the string is the hexadecimal value of m_digest[0].
  */
  const ON_wString ToString(
    bool bUpperCaseHexadecimalDigits
  ) const;

  /*
  Description:
    Same as ToString but prints EmptyContentSHA1 or ZeroSHA1 for those two special cases. 
  */
  const ON_wString ToStringEx(
    bool bUpperCaseHexadecimalDigits
  ) const;

  /*
  Description:
    Parse a string of 40 hexadecimal digits to create a SHA-1 hash.
  Parameters:
    string_to_parse - [in]
    bParseLeadingSpaces - [in]
      If true, leading space characters are parsed.
      Otherwise leading space characters cause parsing to fail.
    bParseInteriorSpace - [in]
      If true, interior space characters are  parsed.
      Otherwise interior space characters cause parsing to fail.
    bParseInteriorHyphen - [in]
      If true, interior hyphen characters are  parsed.
      Otherwise interior hyphen characters cause parsing to fail.
    bIgnoreInternalSpaces - [in]
      If true, isolated hyphens are ignored until 40 hex digits are read.
    bIgnoreInternalHyphens - [in]
      If true, leading spaces and isolated interior spaces are ignored until 40 hex digits are read.
    failure_return_value - [in]
      Value to return if string_to_parse cannot be parsed as 40 hex digits.
  Returns:
    If parsing is successful, the value of the SHA-1 hash is returned.
    Otherwise failure_return_value is returned.
  */
  static const ON_SHA1_Hash FromString(
    const ON_wString string_to_parse,
    bool bParseLeasingSpaces,
    bool bParseInteriorSpace,
    bool bParseInteriorHyphen,
    ON_SHA1_Hash failure_return_value
  );

  bool Read(
    class ON_BinaryArchive& archive
    );

  bool Write(
    class ON_BinaryArchive& archive
    ) const;

  void Dump(
    class ON_TextLog& text_log
    ) const;

  /*
  Returns:
    True if this and ON_SHA1_Hash::ZeroDigest have identical digest values.
  */
  bool IsZeroDigest() const;

  /*
  Returns:
    True if this and ON_SHA1_Hash::EmptyContentHash have identical digest values.
  */
  bool IsEmptyContentHash() const;

  bool IsZeroDigestOrEmptyContentHash() const;

  ON_DEPRECATED_MSG("Use IsZeroDigestOrEmptyContentHash() instead. (Spelling error in this one's name.")
  bool IsZeroDigentOrEmptyContentHash() const;

  /*
  Returns:
    True if this hash is not equal to ON_SHA1_Hash::EmptyContentHash or ON_SHA1_Hash::ZeroDigest.
  Remarks:
    ON_SHA1_Hash::EmptyContentHash is the SHA1 of hashing zero bytes and has a non zero digest.
    ON_SHA1_Hash::ZeroDigest is 20 bytes of zeros. Opennurbs uses ON_SHA1_Hash::ZeroDigest to
    indicate a SHA1 has is not initialized.
  */
  bool IsSet() const;

  /// <summary>
  /// Calculating a SHA1 hash is faster than calculating a CRC on the same information.
  /// This function calculates the ON_CRC value of the 20 byte digest.
  /// Calculating a sha1 hash and then using CRC32(0) is an excellent and efficient way
  /// to get a high quality 4 byte CRC.
  /// </summary>
  /// <param name="current_remainder"> 
  /// Nonzero values are rare in this context. When in doubt, pass 0.
  /// </param>
  /// <returns>ON_CRC32(seed, 20, m_digest)</returns>
  ON__UINT32 CRC32(ON__UINT32 current_remainder) const;

  ON__UINT8 m_digest[20]; 
};



ON_DECL
bool operator==(const ON_SHA1_Hash& a, const ON_SHA1_Hash& b);

ON_DECL
bool operator!=(const ON_SHA1_Hash& a, const ON_SHA1_Hash& b);

/*
Description:
  ON_SHA1 is a small class for calculating the SHA-1 hash of a sequence of bytes.
  It may be use incrementally (the bytes do not have to be in a contiguous
  array in memory at one time).  
  
Remarks:
  The ON_SHA1 class cannot be used for cryptographic or security applications.
  The SHA-1 hash algorithm is not suitable for cryptographic or security applications.
  The ON_SHA1 class does not "wipe" intermediate results.

  If you have two different sequences of N bytes storing information (lower entropy
  than a random sequence) are you are not intentionally calculating the information
  to create a SHA-1 hash collision, then the probability that the sequences have
  the same SHA-1 hash is approximately 2^-80 ~ 10^-24.
*/
class ON_CLASS ON_SHA1
{
public:

	ON_SHA1() = default;
	~ON_SHA1() = default;
  ON_SHA1(const ON_SHA1&) = default;
  ON_SHA1& operator=(const ON_SHA1&) = default;

  /*
  Description:
    Make one or more calls to AccumulateBytes() as the sequence of bytes is available.

  Parameters:
    buffer - [in]
    sizeof_buffer - [in]
      number of bytes in buffer
  */
#if defined(ON_COMPILER_MSC) && defined(NDEBUG)
  // Reduces release build link time optimization by several hours for
  // large programs that make lots of calls to ON_SHA1.Accumulate*() functions.
  __declspec(noinline)
#endif
  void AccumulateBytes(
    const void* buffer,
    ON__UINT64 sizeof_buffer
    );

  /*
  Description:
    Add the double value to the SHA1 in a manner that
    -0.0 and +0.0 will generate identical SHA-1 values
    and the result is independent of endian byte order.
  */
  void AccumulateDouble(
    double x
    );

  /*
  Description:
    Add the double value to the SHA1 in a manner that
    -0.0 and +0.0 will generate identical SHA-1 values
    and the result is independent of endian byte order.
  */
  void AccumulateDoubleArray(
    size_t count,
    const double* a
    );

  /*
  Description:
    Add the double value to the SHA1 in a manner that
    -0.0 and +0.0 will generate identical SHA-1 values
    and the result is independent of endian byte order.
  */
  void AccumulateFloat(
    float x
  );

  /*
  Description:
    Add the double value to the SHA1 in a manner that
    -0.0 and +0.0 will generate identical SHA-1 values
    and the result is independent of endian byte order.
  */
  void AccumulateFloatArray(
    size_t count,
    const float* a
  );

  void Accumulate2fPoint(
    const class ON_2fPoint& point
  );

  void Accumulate3fPoint(
    const class ON_3fPoint& point
  );

  void Accumulate4fPoint(
    const class ON_4fPoint& point
  );

  void Accumulate2fVector(
    const class ON_2fVector& vector
  );

  void Accumulate3fVector(
    const class ON_3fVector& vector
  );

  void Accumulate2dPoint(
    const class ON_2dPoint& point
  );

  void Accumulate3dPoint(
    const class ON_3dPoint& point
  );

  void Accumulate4dPoint(
    const class ON_4dPoint& point
    );

  void Accumulate2dVector(
    const class ON_2dVector& vector
  );

  void Accumulate3dVector(
    const class ON_3dVector& vector
  );

  void AccumulateBoundingBox(
    const class ON_BoundingBox& bbox
  );

  void AccumulateUnitSystem(
    const class ON_UnitSystem& unit_system
  );

  void AccumulateLengthUnitSystem(
    const ON::LengthUnitSystem length_unit_system
  );

  /*
  Description:
    Accumulates the full and relative path names.
  */
  void AccumulateFileReference(
    const class ON_FileReference& file_reference
  );

  void AccumulateTransformation(
    const class ON_Xform& xform
  );
  
  void AccumulateInteger8(
    char i
  );

  void AccumulateInteger8(
    ON__INT8 i
    );
  
  void AccumulateUnsigned8(
    ON__UINT8 u
    );
    
  void AccumulateInteger16(
    ON__INT16 i
    );
  
  void AccumulateUnsigned16(
    ON__UINT16 u
    );

  void AccumulateInteger32(
    ON__INT32 i
    );

  void AccumulateInteger32Array(
    size_t count,
    const ON__INT32* a
  );
  
  void AccumulateUnsigned32(
    ON__UINT32 u
    );

  void AccumulateInteger64(
    ON__INT64 i
    );
  
  void AccumulateUnsigned64(
    ON__UINT64 u
    );


  void AccumulateBool(
    bool b
    );


  void AccumulateString(
    const class ON_String& str
    );

  void AccumulateString(
    const class ON_wString& str
    );

  void AccumulateId(
    const ON_UUID& id
  );

  void AccumulateString(
    const char* sUTF8,
    int element_count,
    ON_StringMapOrdinalType mapping
    );

  void AccumulateString(
    const wchar_t* sUTF8,
    int element_count,
    ON_StringMapOrdinalType mapping
    );

  void AccumulateString(
    const class ON_String& str,
    ON_StringMapOrdinalType mapping
    );

  void AccumulateString(
    const class ON_wString& str,
    ON_StringMapOrdinalType mapping
    );


  void AccumulateSubHash(
    const class ON_SHA1_Hash& sub_hash
    );

private:
  void Internal_SwapBigEndianUpdate(
    const void* buffer,
    ON__UINT64 sizeof_buffer
  );

public:
  /*
  Returns:
    Total number of bytes passed to Update().
  */
  ON__UINT64 ByteCount() const;

  /*
  Returns:
    SHA-1 hash value of the sequence of ByteCount() bytes that have been
    passed to this ON_SHA1 class's Update() function since construction
    or the last call to Reset().
  Remarks:
    You may use Hash() to compute intermediate SHA-1 hash values. 
    
    Put another way, you may call Update() zero or more times passing in N1 bytes, 
    call Digest() to get the SHA-1 hash of those N1 bytes, make zero or more additional
    calls to Update() passing in N2 additional bytes, call digest to get the SHA-1 hash
    of the sequence of (N1 + N2) bytes, and so on.
  */
  ON_SHA1_Hash Hash() const;

  /*
  Description:
    Reset this ON_SHA1 class so it can be reused.  
  */
  void Reset();

  /*
  Description:
    This is a static function that uses ON_SHA1 to compute SHA-1 hash values
    of sequences of bytes with known SHA-1 hash values and compares the 
    results from ON_SHA1 with the known SHA-1 hash values.

    This function can be used to validate the ON_SHA1 class compiled correctly.

  Returns:
    true 
      All validation tests passed.
    false 
      At least one validation test failed.
  */
  static bool Validate();

private:
  void Internal_Accumulate(const ON__UINT8* input, ON__UINT32 length);
  void set_final_hash();

  ON__UINT64 m_byte_count = 0; // number of bytes that have passed through calls to update().
  // if 1 == m_status_bits & 1, then update has been called at least once (perhaps with 0 bytes).
  // if 2 == m_status_bits & 2, then m_sha1_hash is current.
  mutable ON__UINT32 m_status_bits = 0;
  ON__UINT32 m_reserved = 0;  

  // current "remainder"
  ON__UINT8 m_buffer[64] = {};      // bytes that didn't fit in last 64 byte chunk
	ON__UINT32 m_bit_count[2] = {};   // number of bits (lo, hi)
	ON__UINT32 m_state[5] = {};       // current state

  // cached SHA1 hash - valid if 2 = (2 & m_status_bits)
	mutable ON_SHA1_Hash m_sha1_hash;
};

/*
Description:
  Test speeds of various hash algorithms.
Parameters:
  byte_count - [in]
    Number of bytes to hash. This number is rounded up to the nearest multiple of 1024.
  crc16 - [in/out]
    If crc16 is not nullptr, then 16 bit CRC hashing is tested using function ON_CRC16().
  crc32 - [in/out]
    If crc32 is not nullptr, then 32 bit CRC hashing is tested using function ON_CRC32().
  md5_hash - [in/out]
    If md5_hash is not nullptr, then MD5 hashing is tested using class ON_MD5.
  sha1_hash - [in/out]
    If sha1_hash is not nullptr, then SHA-1 hashing is tested class ON_SHA1.
  elapsed_time_in_seconds - [out]
    elapsed_time_in_seconds[0] = 16 bit CRC hash time in seconds.
    elapsed_time_in_seconds[1] = 32 bit CRC hash time in seconds.
    elapsed_time_in_seconds[2] = MD5 hash time in seconds.
    elapsed_time_in_seconds[3] = SHA-1 hash time in seconds.
    If a hash was tested, then number of seconds it took to compute the hash is returned.
    Otherwise ON_DBL_QNAN is returned.
*/
ON_DECL
void ON_TestHashSpeed(
  size_t byte_count,
  ON__UINT16* crc16,
  ON__UINT32* crc32,
  ON_MD5_Hash* md5_hash,
  ON_SHA1_Hash* sha1_hash,
  double elapsed_time_in_seconds[4]
);

/*
Description:
  Test speeds of various hash algorithms and use text_log to print the results.
Parameters:
  byte_count - [in]
    Number of bytes to hash. This number is rounded up to the nearest multiple of 1024.
  bCRC16 - [in]
    True to test 16 bit CRC hashing speed.
  bCRC32 - [in]
    True to test 32 bit CRC hashing speed.
  bMD5 - [in]
    True to test MD5 hashing speed.
  bSHA1 - [in]
    True to test SHA-1 hashing speed.
  text_log - [in]
    Test results are printed using text_log.
*/
ON_DECL
void ON_TestHashSpeed(
  size_t byte_count,
  bool bTestCRC16,
  bool bTestCRC32,
  bool bTestMD5,
  bool bTestSHA1,
  ON_TextLog& text_log
);

ON_DECL
void ON_TestHashSpeed(
  size_t byte_count,
  ON_TextLog& text_log
);

#endif
