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

#if !defined(ON_STD_STRING_INC_)
#define ON_STD_STRING_INC_

/*
When the predecessor of opennurbs was released in 1995, there was
no robust corss platform support for dynamic string classes.
In order to provide robust dynamic string support, openNURBS
had to implement ON_String and ON_wString.  

It's now 2013 and current C++ compilers from the
GNU Project (gcc 4.7), Microsoft (Visual C++ 11 (2012)), 
Google (Android NDK r8e) and Apple (LLVM 4.2)  provide
reasonable support for much of the C++11 standard and provide
working implementations std::basic_string, std:string and 
std::wstring classes.  

Over time, opennurbs will transition from using ON_String and
ON_wString to using std::string and std::wstring.

The tools in the opennurbs_std_string*.* files provide support
for string formatting and UTF conversion that are not available
from the standard C++ string classes.

These implementations assume the compiler has solid support for
std:basic_string, std::string, std::wstring, std::u16string, 
std::u32string and for using rvalue references to efficient
return dynamic strings.
*/

ON_DECL
std::string ON_VARGS_FUNC_CDECL ON_std_string_format(
  const char* format,
  ...
  ) ON_NOEXCEPT;

ON_DECL
std::wstring ON_VARGS_FUNC_CDECL ON_std_wstring_format(
  const wchar_t* format,
  ...
  ) ON_NOEXCEPT;

/*
Description:
  Convert a UTF-8 encoded char string to a UTF-8 encoded std::string.
  This function removes byte order marks (BOM) and can repair encoding
  errors.

Parameters:
  bTestByteOrder - [in]
    If bTestByteOrder is true and the the input buffer is a 
    byte order mark (BOM), then the BOM is skipped.  It the value
    of the BOM is byte swapped, then subsequent input elements are
    byte swapped before being decoded. Specifically:
    - If the size of an input buffer element is 1 byte and the
      values of the first three input elements are a UTF-8 BOM 
      (0xEF, 0xBB, 0xBF), then the first three input elements are
      ignored and decoding begins at the forth input element.
    - If the size of an input buffer element is 2 bytes and the value
      of the first element is a UTF-16 BOM (0xFEFF), then the first
      element is ignored and decoding begins with the second element.
    - If the size of an input buffer element is 2 bytes and the value
      of the first element is a byte swapped UTF-16 BOM (0xFFFE), 
      then the first element is ignored, decoding begins with the
      second element, and input element bytes are swapped before 
      being decoded.
    - If the size of an input buffer element is 4 bytes and the value
      of the first element is a UTF-32 BOM (0x0000FEFF), then the 
      first element is ignored and decoding begins with the second
      element.
    - If the size of an input buffer element is 4 bytes and the value
      of the first element is bytes swapped UTF-32 BOM (0xFFFE0000),
      then the first element is ignored, decoding begins with the 
      second element, and input element bytes are swapped before 
      being decoded.
    - In all other cases the first element of the input buffer is
      decoded and no byte swapping is performed.

  sInputUTF - [in]
    UTF-8 encoded char string to convert.

  sInputUTF_count - [in]
    If sInputUTF_count >= 0, then it specifies the number of
    elements in sInputUTF[] to convert.

    If sInputUTF_count == -1, then sInputUTF must be a zero 
    terminated array and all the elements up to the first zero 
    element are converted.

  error_status - [out]
    If error_status is not null, then bits of *error_status are
    set to indicate the success or failure of the conversion.  
    When the error_mask parameter is used to used to mask some
    conversion errors, multiple bits may be set.
       0: Successful conversion with no errors.
       1: The input parameters were invalid. 
          This error cannot be masked.
       2: The output buffer was not large enough to hold the converted
          string. As much conversion as possible is performed in this
          case and the error cannot be masked.
       4: When parsing a UTF-8 or UTF-32 string, the values of two
          consecutive encoding sequences formed a valid UTF-16 
          surrogate pair.           
          This error is masked if 0 != (4 & m_error_mask).
          If the error is masked, then the surrogate pair is
          decoded, the value of the resulting unicode code point
          is used, and parsing continues.
       8: An overlong UTF-8 encoding sequence was encountered and 
          the value of the overlong sUTF-8 sequence was a valid
          unicode code point.           
          This error is masked if 0 != (8 & m_error_mask).
          If the error is masked, then the unicode code point
          is used and parsing continues.
      16: An illegal UTF-8, UTF-16 or UTF-32 encoding sequence occurred
          or an invalid unicode code point value resulted from decoding
          a UTF-8 sequence. 
          This error is masked if 0 != (16 & m_error_mask).
          If the error is masked and the value of error_code_point is
          a valid unicode code point, then error_code_point is encoded
          in the output string and parsing continues.

  error_mask - [in]
    If 0 != (error_mask & 4), then type 4 errors are masked.
    If 0 != (error_mask & 8), then type 8 errors are masked.
    If 0 != (error_mask & 16) and error_code_point is a valid unicode
    code point value, then type 16 errors are masked.

  error_code_point - [in]
    Unicode code point value to use in when masking type 16 errors.
    If 0 == (error_mask & 16), then this parameter is ignored.
    0xFFFD is a popular choice for the error_code_point value.

  sEndElement - [out]
    If sEndElement is not null, then *sEndElement points to the
    element of sInputUTF[] were conversion stopped.

    If an error occurred and was not masked, then *sEndElement points
    to the element of sInputUTF[] where the conversion failed.  
    If no errors occurred or all errors were masked, then 
    *sEndElement = sInputUTF + sInputUTF_count or points to
    the zero terminator in sInputUTF[], depending on the input
    value of sInputUTF_count.

Returns:
  A UTF-8 encoded std::string. 
  The returned string does not have a byte order mark (BOM).
*/
ON_DECL
std::string ON_UTF8_to_std_string( 
  int bTestByteOrder,
  const char* sInputUTF,
  int sInputUTF_count,
  unsigned int* error_status,
  unsigned int error_mask,
  ON__UINT32 error_code_point,
  const char** sEndElement
  ) ON_NOEXCEPT;

/*
Description:
  Convert a UTF-16 encoded ON__UINT16 string to a UTF-8 encoded std:string.
  This function removes byte order marks (BOM) and can repair encoding
  errors.

Parameters:
  bTestByteOrder - [in]
    If bTestByteOrder is true and the the input buffer is a 
    byte order mark (BOM), then the BOM is skipped.  It the value
    of the BOM is byte swapped, then subsequent input elements are
    byte swapped before being decoded. Specifically:
    - If the size of an input buffer element is 1 byte and the
      values of the first three input elements are a UTF-8 BOM 
      (0xEF, 0xBB, 0xBF), then the first three input elements are
      ignored and decoding begins at the forth input element.
    - If the size of an input buffer element is 2 bytes and the value
      of the first element is a UTF-16 BOM (0xFEFF), then the first
      element is ignored and decoding begins with the second element.
    - If the size of an input buffer element is 2 bytes and the value
      of the first element is a byte swapped UTF-16 BOM (0xFFFE), 
      then the first element is ignored, decoding begins with the
      second element, and input element bytes are swapped before 
      being decoded.
    - If the size of an input buffer element is 4 bytes and the value
      of the first element is a UTF-32 BOM (0x0000FEFF), then the 
      first element is ignored and decoding begins with the second
      element.
    - If the size of an input buffer element is 4 bytes and the value
      of the first element is bytes swapped UTF-32 BOM (0xFFFE0000),
      then the first element is ignored, decoding begins with the 
      second element, and input element bytes are swapped before 
      being decoded.
    - In all other cases the first element of the input buffer is
      decoded and no byte swapping is performed.

  sInputUTF - [in]
    UTF-16 encoded ON__UINT16 string to convert.


  sInputUTF_count - [in]
    If sInputUTF_count >= 0, then it specifies the number of
    elements in sInputUTF[] to convert.

    If sInputUTF_count == -1, then sInputUTF must be a zero 
    terminated array and all the elements up to the first zero 
    element are converted.
    
  sUTF8 - [out]
    If sUTF8 is not null and sUTF8_count > 0, then the UTF-8
    encoded string is returned in this buffer. If there is room
    for the null terminator, the converted string will be null
    terminated. The null terminator is never included in the count 
    of returned by this function. The converted string is in the 
    CPU's native byte order. No byte order mark is prepended.

  sUTF8_count - [in]
    If sUTF8_count > 0, then it specifies the number of available
    ON__UINT8 elements in the sUTF8[] buffer.
    
    If sUTF8_count == 0, then the sUTF8 parameter is ignored.

  error_status - [out]
    If error_status is not null, then bits of *error_status are
    set to indicate the success or failure of the conversion.  
    When the error_mask parameter is used to used to mask some
    conversion errors, multiple bits may be set.
       0: Successful conversion with no errors.
       1: The input parameters were invalid. 
          This error cannot be masked.
       2: The output buffer was not large enough to hold the converted
          string. As much conversion as possible is performed in this
          case and the error cannot be masked.
       4: When parsing a UTF-8 or UTF-32 string, the values of two
          consecutive encoding sequences formed a valid UTF-16 
          surrogate pair.           
          This error is masked if 0 != (4 & m_error_mask).
          If the error is masked, then the surrogate pair is
          decoded, the value of the resulting unicode code point
          is used, and parsing continues.
       8: An overlong UTF-8 encoding sequence was encountered and 
          the value of the overlong sUTF-8 sequence was a valid
          unicode code point.           
          This error is masked if 0 != (8 & m_error_mask).
          If the error is masked, then the unicode code point
          is used and parsing continues.
      16: An illegal UTF-8, UTF-16 or UTF-32 encoding sequence occurred
          or an invalid unicode code point value resulted from decoding
          a UTF-8 sequence. 
          This error is masked if 0 != (16 & m_error_mask).
          If the error is masked and the value of error_code_point is
          a valid unicode code point, then error_code_point is encoded
          in the output string and parsing continues.

  error_mask - [in]
    If 0 != (error_mask & 4), then type 4 errors are masked.
    If 0 != (error_mask & 8), then type 8 errors are masked.
    If 0 != (error_mask & 16) and error_code_point is a valid unicode
    code point value, then type 16 errors are masked.

  error_code_point - [in]
    Unicode code point value to use in when masking type 16 errors.
    If 0 == (error_mask & 16), then this parameter is ignored.
    0xFFFD is a popular choice for the error_code_point value.

  sEndElement - [out]
    If sEndElement is not null, then *sEndElement points to the
    element of sInputUTF[] were conversion stopped.

    If an error occurred and was not masked, then *sEndElement points
    to the element of sInputUTF[] where the conversion failed.  
    If no errors occurred or all errors were masked, then 
    *sEndElement = sInputUTF + sInputUTF_count or points to
    the zero terminator in sInputUTF[], depending on the input
    value of sInputUTF_count.


Returns:
  A UTF-8 encoded std::string. 
  The returned string does not have a byte order mark (BOM).
*/
ON_DECL
std::string ON_UTF16_to_std_string( 
  int bTestByteOrder,
  const ON__UINT16* sInputUTF,
  int sInputUTF_count,
  unsigned int* error_status,
  unsigned int error_mask,
  ON__UINT32 error_code_point,
  const ON__UINT16** sEndElement
  ) ON_NOEXCEPT;

/*
Description:
  Convert a UTF-32 encoded ON__UINT16 string to a UTF-8 encoded std:string.
  This function removes byte order marks (BOM) and can repair encoding
  errors.

Parameters:
  bTestByteOrder - [in]
    If bTestByteOrder is true and the the input buffer is a 
    byte order mark (BOM), then the BOM is skipped.  It the value
    of the BOM is byte swapped, then subsequent input elements are
    byte swapped before being decoded. Specifically:
    - If the size of an input buffer element is 1 byte and the
      values of the first three input elements are a UTF-8 BOM 
      (0xEF, 0xBB, 0xBF), then the first three input elements are
      ignored and decoding begins at the forth input element.
    - If the size of an input buffer element is 2 bytes and the value
      of the first element is a UTF-16 BOM (0xFEFF), then the first
      element is ignored and decoding begins with the second element.
    - If the size of an input buffer element is 2 bytes and the value
      of the first element is a byte swapped UTF-16 BOM (0xFFFE), 
      then the first element is ignored, decoding begins with the
      second element, and input element bytes are swapped before 
      being decoded.
    - If the size of an input buffer element is 4 bytes and the value
      of the first element is a UTF-32 BOM (0x0000FEFF), then the 
      first element is ignored and decoding begins with the second
      element.
    - If the size of an input buffer element is 4 bytes and the value
      of the first element is bytes swapped UTF-32 BOM (0xFFFE0000),
      then the first element is ignored, decoding begins with the 
      second element, and input element bytes are swapped before 
      being decoded.
    - In all other cases the first element of the input buffer is
      decoded and no byte swapping is performed.

  sInputUTF - [in]
    UTF-32 encoded ON__UINT32 string to convert.

  sInputUTF_count - [in]
    If sInputUTF_count >= 0, then it specifies the number of
    elements in sInputUTF[] to convert.

    If sInputUTF_count == -1, then sInputUTF must be a zero 
    terminated array and all the elements up to the first zero 
    element are converted.

  error_status - [out]
    If error_status is not null, then bits of *error_status are
    set to indicate the success or failure of the conversion.  
    When the error_mask parameter is used to used to mask some
    conversion errors, multiple bits may be set.
       0: Successful conversion with no errors.
       1: The input parameters were invalid. 
          This error cannot be masked.
       2: The output buffer was not large enough to hold the converted
          string. As much conversion as possible is performed in this
          case and the error cannot be masked.
       4: When parsing a UTF-8 or UTF-32 string, the values of two
          consecutive encoding sequences formed a valid UTF-16 
          surrogate pair.           
          This error is masked if 0 != (4 & m_error_mask).
          If the error is masked, then the surrogate pair is
          decoded, the value of the resulting unicode code point
          is used, and parsing continues.
       8: An overlong UTF-8 encoding sequence was encountered and 
          the value of the overlong sUTF-8 sequence was a valid
          unicode code point.           
          This error is masked if 0 != (8 & m_error_mask).
          If the error is masked, then the unicode code point
          is used and parsing continues.
      16: An illegal UTF-8, UTF-16 or UTF-32 encoding sequence occurred
          or an invalid unicode code point value resulted from decoding
          a UTF-8 sequence. 
          This error is masked if 0 != (16 & m_error_mask).
          If the error is masked and the value of error_code_point is
          a valid unicode code point, then error_code_point is encoded
          in the output string and parsing continues.

  error_mask - [in]
    If 0 != (error_mask & 4), then type 4 errors are masked.
    If 0 != (error_mask & 8), then type 8 errors are masked.
    If 0 != (error_mask & 16) and error_code_point is a valid unicode
    code point value, then type 16 errors are masked.

  error_code_point - [in]
    Unicode code point value to use in when masking type 16 errors.
    If 0 == (error_mask & 16), then this parameter is ignored.
    0xFFFD is a popular choice for the error_code_point value.

  sEndElement - [out]
    If sEndElement is not null, then *sEndElement points to the
    element of sInputUTF[] were conversion stopped.

    If an error occurred and was not masked, then *sEndElement points
    to the element of sInputUTF[] where the conversion failed.  
    If no errors occurred or all errors were masked, then 
    *sEndElement = sInputUTF + sInputUTF_count or points to
    the zero terminator in sInputUTF[], depending on the input
    value of sInputUTF_count.

Returns:
  A UTF-8 encoded std::string. 
  The returned string does not have a byte order mark (BOM).
*/
ON_DECL
std::string ON_UTF32_to_std_string( 
  int bTestByteOrder,
  const ON__UINT32* sInputUTF,
  int sInputUTF_count,
  unsigned int* error_status,
  unsigned int error_mask,
  ON__UINT32 error_code_point,
  const ON__UINT32** sEndElement
  ) ON_NOEXCEPT;

/*
Description:
  Convert a UTF-XX encoded wchar_t string to a UTF-8 encoded std:string.
  This function removes byte order marks (BOM) and can repair encoding
  errors.
  
  The value of sizeof(wchar_t) determines which UTF-XX encoding is used.
    sizeof(wchar_t)  UTF-XX
      1              UTF-8
      2              UTF-16
      4              UTF-32

Parameters:
  bTestByteOrder - [in]
    If bTestByteOrder is true and the the input buffer is a 
    byte order mark (BOM), then the BOM is skipped.  It the value
    of the BOM is byte swapped, then subsequent input elements are
    byte swapped before being decoded. Specifically:
    - If the size of an input buffer element is 1 byte and the
      values of the first three input elements are a UTF-8 BOM 
      (0xEF, 0xBB, 0xBF), then the first three input elements are
      ignored and decoding begins at the forth input element.
    - If the size of an input buffer element is 2 bytes and the value
      of the first element is a UTF-16 BOM (0xFEFF), then the first
      element is ignored and decoding begins with the second element.
    - If the size of an input buffer element is 2 bytes and the value
      of the first element is a byte swapped UTF-16 BOM (0xFFFE), 
      then the first element is ignored, decoding begins with the
      second element, and input element bytes are swapped before 
      being decoded.
    - If the size of an input buffer element is 4 bytes and the value
      of the first element is a UTF-32 BOM (0x0000FEFF), then the 
      first element is ignored and decoding begins with the second
      element.
    - If the size of an input buffer element is 4 bytes and the value
      of the first element is bytes swapped UTF-32 BOM (0xFFFE0000),
      then the first element is ignored, decoding begins with the 
      second element, and input element bytes are swapped before 
      being decoded.
    - In all other cases the first element of the input buffer is
      decoded and no byte swapping is performed.

  sInputUTF - [in]
    UTF-XX encoded wchar_t string to convert.

  sInputUTF_count - [in]
    If sInputUTF_count >= 0, then it specifies the number of
    elements in sInputUTF[] to convert.

    If sInputUTF_count == -1, then sInputUTF must be a zero 
    terminated array and all the elements up to the first zero 
    element are converted.

  error_status - [out]
    If error_status is not null, then bits of *error_status are
    set to indicate the success or failure of the conversion.  
    When the error_mask parameter is used to used to mask some
    conversion errors, multiple bits may be set.
       0: Successful conversion with no errors.
       1: The input parameters were invalid. 
          This error cannot be masked.
       2: The output buffer was not large enough to hold the converted
          string. As much conversion as possible is performed in this
          case and the error cannot be masked.
       4: When parsing a UTF-8 or UTF-32 string, the values of two
          consecutive encoding sequences formed a valid UTF-16 
          surrogate pair.           
          This error is masked if 0 != (4 & m_error_mask).
          If the error is masked, then the surrogate pair is
          decoded, the value of the resulting unicode code point
          is used, and parsing continues.
       8: An overlong UTF-8 encoding sequence was encountered and 
          the value of the overlong sUTF-8 sequence was a valid
          unicode code point.           
          This error is masked if 0 != (8 & m_error_mask).
          If the error is masked, then the unicode code point
          is used and parsing continues.
      16: An illegal UTF-8, UTF-16 or UTF-32 encoding sequence occurred
          or an invalid unicode code point value resulted from decoding
          a UTF-8 sequence. 
          This error is masked if 0 != (16 & m_error_mask).
          If the error is masked and the value of error_code_point is
          a valid unicode code point, then error_code_point is encoded
          in the output string and parsing continues.

  error_mask - [in]
    If 0 != (error_mask & 4), then type 4 errors are masked.
    If 0 != (error_mask & 8), then type 8 errors are masked.
    If 0 != (error_mask & 16) and error_code_point is a valid unicode
    code point value, then type 16 errors are masked.

  error_code_point - [in]
    Unicode code point value to use in when masking type 16 errors.
    If 0 == (error_mask & 16), then this parameter is ignored.
    0xFFFD is a popular choice for the error_code_point value.

  end_element_index - [out]
    If end_element_index is not null, then *end_element_index is the
    index of the first element in sInputUTF that was not converted. 

    If an error occurred and was not masked, then *end_element_index
    is the index of the element of sInputUTF[] where the conversion
    failed.  
    If no errors occurred or all errors were masked, then 
    *end_element_index is the number of elements in sInputUTF[] that
    were converted.

Returns:
  A UTF-8 encoded std::string. 
  The returned string does not have a byte order mark (BOM).
*/
std::string ON_UTF_WideChar_to_std_string( 
  int bTestByteOrder,
  const wchar_t* sInputUTF,
  int sInputUTF_count,
  unsigned int* error_status,
  unsigned int error_mask,
  ON__UINT32 error_code_point,
  int* end_element_index
  ) ON_NOEXCEPT;

/*
Description:
  Convert a UTF-XX encoded std::wstring to a UTF-8 encoded std:string.
  This function removes byte order marks (BOM) and can repair encoding
  errors.
  
  The value of sizeof(wchar_t) determines which UTF-XX encoding is used.
    sizeof(wchar_t)  UTF-XX
      1              UTF-8
      2              UTF-16
      4              UTF-32

Parameters:
  bTestByteOrder - [in]
    If bTestByteOrder is true and the the input buffer is a 
    byte order mark (BOM), then the BOM is skipped.  It the value
    of the BOM is byte swapped, then subsequent input elements are
    byte swapped before being decoded. Specifically:
    - If the size of an input buffer element is 1 byte and the
      values of the first three input elements are a UTF-8 BOM 
      (0xEF, 0xBB, 0xBF), then the first three input elements are
      ignored and decoding begins at the forth input element.
    - If the size of an input buffer element is 2 bytes and the value
      of the first element is a UTF-16 BOM (0xFEFF), then the first
      element is ignored and decoding begins with the second element.
    - If the size of an input buffer element is 2 bytes and the value
      of the first element is a byte swapped UTF-16 BOM (0xFFFE), 
      then the first element is ignored, decoding begins with the
      second element, and input element bytes are swapped before 
      being decoded.
    - If the size of an input buffer element is 4 bytes and the value
      of the first element is a UTF-32 BOM (0x0000FEFF), then the 
      first element is ignored and decoding begins with the second
      element.
    - If the size of an input buffer element is 4 bytes and the value
      of the first element is bytes swapped UTF-32 BOM (0xFFFE0000),
      then the first element is ignored, decoding begins with the 
      second element, and input element bytes are swapped before 
      being decoded.
    - In all other cases the first element of the input buffer is
      decoded and no byte swapping is performed.

  sInputUTF - [in]
    UTF-XX encoded std::wstring to convert.  

  sInputUTF_count - [in]
    If sInputUTF_count >= 0, then it specifies the number of
    elements in sInputUTF[] to convert.

    If sInputUTF_count == -1, then sInputUTF must be a zero 
    terminated array and all the elements up to the first zero 
    element are converted.
    
  sUTF8 - [out]
    If sUTF8 is not null and sUTF8_count > 0, then the UTF-8
    encoded string is returned in this buffer. If there is room
    for the null terminator, the converted string will be null
    terminated. The null terminator is never included in the count 
    of returned by this function. The converted string is in the 
    CPU's native byte order. No byte order mark is prepended.

  sUTF8_count - [in]
    If sUTF8_count > 0, then it specifies the number of available
    ON__UINT8 elements in the sUTF8[] buffer.
    
    If sUTF8_count == 0, then the sUTF8 parameter is ignored.

  error_status - [out]
    If error_status is not null, then bits of *error_status are
    set to indicate the success or failure of the conversion.  
    When the error_mask parameter is used to used to mask some
    conversion errors, multiple bits may be set.
       0: Successful conversion with no errors.
       1: The input parameters were invalid. 
          This error cannot be masked.
       2: The output buffer was not large enough to hold the converted
          string. As much conversion as possible is performed in this
          case and the error cannot be masked.
       4: When parsing a UTF-8 or UTF-32 string, the values of two
          consecutive encoding sequences formed a valid UTF-16 
          surrogate pair.           
          This error is masked if 0 != (4 & m_error_mask).
          If the error is masked, then the surrogate pair is
          decoded, the value of the resulting unicode code point
          is used, and parsing continues.
       8: An overlong UTF-8 encoding sequence was encountered and 
          the value of the overlong sUTF-8 sequence was a valid
          unicode code point.           
          This error is masked if 0 != (8 & m_error_mask).
          If the error is masked, then the unicode code point
          is used and parsing continues.
      16: An illegal UTF-8, UTF-16 or UTF-32 encoding sequence occurred
          or an invalid unicode code point value resulted from decoding
          a UTF-8 sequence. 
          This error is masked if 0 != (16 & m_error_mask).
          If the error is masked and the value of error_code_point is
          a valid unicode code point, then error_code_point is encoded
          in the output string and parsing continues.

  error_mask - [in]
    If 0 != (error_mask & 4), then type 4 errors are masked.
    If 0 != (error_mask & 8), then type 8 errors are masked.
    If 0 != (error_mask & 16) and error_code_point is a valid unicode
    code point value, then type 16 errors are masked.

  error_code_point - [in]
    Unicode code point value to use in when masking type 16 errors.
    If 0 == (error_mask & 16), then this parameter is ignored.
    0xFFFD is a popular choice for the error_code_point value.

  end_element_index - [out]
    If end_element_index is not null, then *end_element_index is the
    index of the first element in sInputUTF that was not converted. 

    If an error occurred and was not masked, then *end_element_index
    is the index of the element of sInputUTF[] where the conversion
    failed.  
    If no errors occurred or all errors were masked, then 
    *end_element_index is the number of elements in sInputUTF[] that
    were converted.

Returns:
  A UTF-8 encoded std::string. 
  The returned string does not have a byte order mark (BOM).
*/
ON_DECL
std::string ON_UTF_std_wstring_to_std_string(
  int bTestByteOrder,
  const std::wstring& sInputUTF,
  int sInputUTF_count,
  unsigned int* error_status,
  unsigned int error_mask,
  ON__UINT32 error_code_point,
  int* end_element_index
  ) ON_NOEXCEPT;

/*
Description:
  Convert a UTF-8 encoded char string to a UTF-XX encoded std::wstring.
  This function removes byte order marks (BOM) and can repair encoding
  errors.
  
  The value of sizeof(wchar_t) determines which UTF-XX encoding is used.
    sizeof(wchar_t)  UTF-XX
      1              UTF-8
      2              UTF-16
      4              UTF-32

Parameters:
  bTestByteOrder - [in]
    If bTestByteOrder is true and the the input buffer is a 
    byte order mark (BOM), then the BOM is skipped.  It the value
    of the BOM is byte swapped, then subsequent input elements are
    byte swapped before being decoded. Specifically:
    - If the size of an input buffer element is 1 byte and the
      values of the first three input elements are a UTF-8 BOM 
      (0xEF, 0xBB, 0xBF), then the first three input elements are
      ignored and decoding begins at the forth input element.
    - If the size of an input buffer element is 2 bytes and the value
      of the first element is a UTF-16 BOM (0xFEFF), then the first
      element is ignored and decoding begins with the second element.
    - If the size of an input buffer element is 2 bytes and the value
      of the first element is a byte swapped UTF-16 BOM (0xFFFE), 
      then the first element is ignored, decoding begins with the
      second element, and input element bytes are swapped before 
      being decoded.
    - If the size of an input buffer element is 4 bytes and the value
      of the first element is a UTF-32 BOM (0x0000FEFF), then the 
      first element is ignored and decoding begins with the second
      element.
    - If the size of an input buffer element is 4 bytes and the value
      of the first element is bytes swapped UTF-32 BOM (0xFFFE0000),
      then the first element is ignored, decoding begins with the 
      second element, and input element bytes are swapped before 
      being decoded.
    - In all other cases the first element of the input buffer is
      decoded and no byte swapping is performed.

  sInputUTF - [in]
    UTF-8 encoded char string to convert.


  sInputUTF_count - [in]
    If sInputUTF_count >= 0, then it specifies the number of
    elements in sInputUTF[] to convert.

    If sInputUTF_count == -1, then sInputUTF must be a zero 
    terminated array and all the elements up to the first zero 
    element are converted.

  error_status - [out]
    If error_status is not null, then bits of *error_status are
    set to indicate the success or failure of the conversion.  
    When the error_mask parameter is used to used to mask some
    conversion errors, multiple bits may be set.
       0: Successful conversion with no errors.
       1: The input parameters were invalid. 
          This error cannot be masked.
       2: The output buffer was not large enough to hold the converted
          string. As much conversion as possible is performed in this
          case and the error cannot be masked.
       4: When parsing a UTF-8 or UTF-32 string, the values of two
          consecutive encoding sequences formed a valid UTF-16 
          surrogate pair.           
          This error is masked if 0 != (4 & m_error_mask).
          If the error is masked, then the surrogate pair is
          decoded, the value of the resulting unicode code point
          is used, and parsing continues.
       8: An overlong UTF-8 encoding sequence was encountered and 
          the value of the overlong sUTF-8 sequence was a valid
          unicode code point.           
          This error is masked if 0 != (8 & m_error_mask).
          If the error is masked, then the unicode code point
          is used and parsing continues.
      16: An illegal UTF-8, UTF-16 or UTF-32 encoding sequence occurred
          or an invalid unicode code point value resulted from decoding
          a UTF-8 sequence. 
          This error is masked if 0 != (16 & m_error_mask).
          If the error is masked and the value of error_code_point is
          a valid unicode code point, then error_code_point is encoded
          in the output string and parsing continues.

  error_mask - [in]
    If 0 != (error_mask & 4), then type 4 errors are masked.
    If 0 != (error_mask & 8), then type 8 errors are masked.
    If 0 != (error_mask & 16) and error_code_point is a valid unicode
    code point value, then type 16 errors are masked.

  error_code_point - [in]
    Unicode code point value to use in when masking type 16 errors.
    If 0 == (error_mask & 16), then this parameter is ignored.
    0xFFFD is a popular choice for the error_code_point value.

  sEndElement - [out]
    If sEndElement is not null, then *sEndElement points to the
    element of sInputUTF[] were conversion stopped.

    If an error occurred and was not masked, then *sEndElement points
    to the element of sInputUTF[] where the conversion failed.  
    If no errors occurred or all errors were masked, then 
    *sEndElement = sInputUTF + sInputUTF_count or points to
    the zero terminator in sInputUTF[], depending on the input
    value of sInputUTF_count.

Returns:
  A UTF-XX encoded std::wstring. 
  The returned string does not have a byte order mark (BOM).
*/
ON_DECL
std::wstring ON_UTF8_to_std_wstring( 
  int bTestByteOrder,
  const char* sInputUTF,
  int sInputUTF_count,
  unsigned int* error_status,
  unsigned int error_mask,
  ON__UINT32 error_code_point,
  const char** sEndElement
  ) ON_NOEXCEPT;

/*
Description:
  Convert a UTF-16 encoded ON__UINT16 string to a UTF-XX encoded std::wstring.
  This function removes byte order marks (BOM) and can repair encoding
  errors.
  
  The value of sizeof(wchar_t) determines which UTF-XX encoding is used.
    sizeof(wchar_t)  UTF-XX
      1              UTF-8
      2              UTF-16
      4              UTF-32

Parameters:
  bTestByteOrder - [in]
    If bTestByteOrder is true and the the input buffer is a 
    byte order mark (BOM), then the BOM is skipped.  It the value
    of the BOM is byte swapped, then subsequent input elements are
    byte swapped before being decoded. Specifically:
    - If the size of an input buffer element is 1 byte and the
      values of the first three input elements are a UTF-8 BOM 
      (0xEF, 0xBB, 0xBF), then the first three input elements are
      ignored and decoding begins at the forth input element.
    - If the size of an input buffer element is 2 bytes and the value
      of the first element is a UTF-16 BOM (0xFEFF), then the first
      element is ignored and decoding begins with the second element.
    - If the size of an input buffer element is 2 bytes and the value
      of the first element is a byte swapped UTF-16 BOM (0xFFFE), 
      then the first element is ignored, decoding begins with the
      second element, and input element bytes are swapped before 
      being decoded.
    - If the size of an input buffer element is 4 bytes and the value
      of the first element is a UTF-32 BOM (0x0000FEFF), then the 
      first element is ignored and decoding begins with the second
      element.
    - If the size of an input buffer element is 4 bytes and the value
      of the first element is bytes swapped UTF-32 BOM (0xFFFE0000),
      then the first element is ignored, decoding begins with the 
      second element, and input element bytes are swapped before 
      being decoded.
    - In all other cases the first element of the input buffer is
      decoded and no byte swapping is performed.

  sInputUTF - [in]
    UTF-16 encoded ON__UINT16 string to convert.

  sInputUTF_count - [in]
    If sInputUTF_count >= 0, then it specifies the number of
    elements in sInputUTF[] to convert.

    If sInputUTF_count == -1, then sInputUTF must be a zero 
    terminated array and all the elements up to the first zero 
    element are converted.
    
  sUTF8 - [out]
    If sUTF8 is not null and sUTF8_count > 0, then the UTF-8
    encoded string is returned in this buffer. If there is room
    for the null terminator, the converted string will be null
    terminated. The null terminator is never included in the count 
    of returned by this function. The converted string is in the 
    CPU's native byte order. No byte order mark is prepended.

  sUTF8_count - [in]
    If sUTF8_count > 0, then it specifies the number of available
    ON__UINT8 elements in the sUTF8[] buffer.
    
    If sUTF8_count == 0, then the sUTF8 parameter is ignored.

  error_status - [out]
    If error_status is not null, then bits of *error_status are
    set to indicate the success or failure of the conversion.  
    When the error_mask parameter is used to used to mask some
    conversion errors, multiple bits may be set.
       0: Successful conversion with no errors.
       1: The input parameters were invalid. 
          This error cannot be masked.
       2: The output buffer was not large enough to hold the converted
          string. As much conversion as possible is performed in this
          case and the error cannot be masked.
       4: When parsing a UTF-8 or UTF-32 string, the values of two
          consecutive encoding sequences formed a valid UTF-16 
          surrogate pair.           
          This error is masked if 0 != (4 & m_error_mask).
          If the error is masked, then the surrogate pair is
          decoded, the value of the resulting unicode code point
          is used, and parsing continues.
       8: An overlong UTF-8 encoding sequence was encountered and 
          the value of the overlong sUTF-8 sequence was a valid
          unicode code point.           
          This error is masked if 0 != (8 & m_error_mask).
          If the error is masked, then the unicode code point
          is used and parsing continues.
      16: An illegal UTF-8, UTF-16 or UTF-32 encoding sequence occurred
          or an invalid unicode code point value resulted from decoding
          a UTF-8 sequence. 
          This error is masked if 0 != (16 & m_error_mask).
          If the error is masked and the value of error_code_point is
          a valid unicode code point, then error_code_point is encoded
          in the output string and parsing continues.

  error_mask - [in]
    If 0 != (error_mask & 4), then type 4 errors are masked.
    If 0 != (error_mask & 8), then type 8 errors are masked.
    If 0 != (error_mask & 16) and error_code_point is a valid unicode
    code point value, then type 16 errors are masked.

  error_code_point - [in]
    Unicode code point value to use in when masking type 16 errors.
    If 0 == (error_mask & 16), then this parameter is ignored.
    0xFFFD is a popular choice for the error_code_point value.

  sEndElement - [out]
    If sEndElement is not null, then *sEndElement points to the
    element of sInputUTF[] were conversion stopped.

    If an error occurred and was not masked, then *sEndElement points
    to the element of sInputUTF[] where the conversion failed.  
    If no errors occurred or all errors were masked, then 
    *sEndElement = sInputUTF + sInputUTF_count or points to
    the zero terminator in sInputUTF[], depending on the input
    value of sInputUTF_count.

Returns:
  A UTF-XX encoded std::wstring. 
  The returned string does not have a byte order mark (BOM).
*/
ON_DECL
std::wstring ON_UTF16_to_std_wstring( 
  int bTestByteOrder,
  const ON__UINT16* sInputUTF,
  int sInputUTF_count,
  unsigned int* error_status,
  unsigned int error_mask,
  ON__UINT32 error_code_point,
  const ON__UINT16** sEndElement
  ) ON_NOEXCEPT;

/*
Description:
  Convert a UTF-32 encoded ON__UINT32 string to a UTF-XX encoded std::wstring.
  This function removes byte order marks (BOM) and can repair encoding
  errors.
  
  The value of sizeof(wchar_t) determines which UTF-XX encoding is used.
    sizeof(wchar_t)  UTF-XX
      1              UTF-8
      2              UTF-16
      4              UTF-32

Parameters:
  bTestByteOrder - [in]
    If bTestByteOrder is true and the the input buffer is a 
    byte order mark (BOM), then the BOM is skipped.  It the value
    of the BOM is byte swapped, then subsequent input elements are
    byte swapped before being decoded. Specifically:
    - If the size of an input buffer element is 1 byte and the
      values of the first three input elements are a UTF-8 BOM 
      (0xEF, 0xBB, 0xBF), then the first three input elements are
      ignored and decoding begins at the forth input element.
    - If the size of an input buffer element is 2 bytes and the value
      of the first element is a UTF-16 BOM (0xFEFF), then the first
      element is ignored and decoding begins with the second element.
    - If the size of an input buffer element is 2 bytes and the value
      of the first element is a byte swapped UTF-16 BOM (0xFFFE), 
      then the first element is ignored, decoding begins with the
      second element, and input element bytes are swapped before 
      being decoded.
    - If the size of an input buffer element is 4 bytes and the value
      of the first element is a UTF-32 BOM (0x0000FEFF), then the 
      first element is ignored and decoding begins with the second
      element.
    - If the size of an input buffer element is 4 bytes and the value
      of the first element is bytes swapped UTF-32 BOM (0xFFFE0000),
      then the first element is ignored, decoding begins with the 
      second element, and input element bytes are swapped before 
      being decoded.
    - In all other cases the first element of the input buffer is
      decoded and no byte swapping is performed.

  sInputUTF - [in]
    UTF-32 encoded ON__UINT32 string to convert.

  sInputUTF_count - [in]
    If sInputUTF_count >= 0, then it specifies the number of
    elements in sInputUTF[] to convert.

    If sInputUTF_count == -1, then sInputUTF must be a zero 
    terminated array and all the elements up to the first zero 
    element are converted.

  error_status - [out]
    If error_status is not null, then bits of *error_status are
    set to indicate the success or failure of the conversion.  
    When the error_mask parameter is used to used to mask some
    conversion errors, multiple bits may be set.
       0: Successful conversion with no errors.
       1: The input parameters were invalid. 
          This error cannot be masked.
       2: The output buffer was not large enough to hold the converted
          string. As much conversion as possible is performed in this
          case and the error cannot be masked.
       4: When parsing a UTF-8 or UTF-32 string, the values of two
          consecutive encoding sequences formed a valid UTF-16 
          surrogate pair.           
          This error is masked if 0 != (4 & m_error_mask).
          If the error is masked, then the surrogate pair is
          decoded, the value of the resulting unicode code point
          is used, and parsing continues.
       8: An overlong UTF-8 encoding sequence was encountered and 
          the value of the overlong sUTF-8 sequence was a valid
          unicode code point.           
          This error is masked if 0 != (8 & m_error_mask).
          If the error is masked, then the unicode code point
          is used and parsing continues.
      16: An illegal UTF-8, UTF-16 or UTF-32 encoding sequence occurred
          or an invalid unicode code point value resulted from decoding
          a UTF-8 sequence. 
          This error is masked if 0 != (16 & m_error_mask).
          If the error is masked and the value of error_code_point is
          a valid unicode code point, then error_code_point is encoded
          in the output string and parsing continues.

  error_mask - [in]
    If 0 != (error_mask & 4), then type 4 errors are masked.
    If 0 != (error_mask & 8), then type 8 errors are masked.
    If 0 != (error_mask & 16) and error_code_point is a valid unicode
    code point value, then type 16 errors are masked.

  error_code_point - [in]
    Unicode code point value to use in when masking type 16 errors.
    If 0 == (error_mask & 16), then this parameter is ignored.
    0xFFFD is a popular choice for the error_code_point value.

  sEndElement - [out]
    If sEndElement is not null, then *sEndElement points to the
    element of sInputUTF[] were conversion stopped.

    If an error occurred and was not masked, then *sEndElement points
    to the element of sInputUTF[] where the conversion failed.  
    If no errors occurred or all errors were masked, then 
    *sEndElement = sInputUTF + sInputUTF_count or points to
    the zero terminator in sInputUTF[], depending on the input
    value of sInputUTF_count.

Returns:
  A UTF-XX encoded std::wstring. 
  The returned string does not have a byte order mark (BOM).
*/
ON_DECL
std::wstring ON_UTF32_to_std_wstring( 
  int bTestByteOrder,
  const ON__UINT32* sInputUTF,
  int sInputUTF_count,
  unsigned int* error_status,
  unsigned int error_mask,
  ON__UINT32 error_code_point,
  const ON__UINT32** sEndElement
  ) ON_NOEXCEPT;

/*
Description:
  Convert a UTF-XX encoded wchar_t string to a UTF-XX encoded std::wstring.
  This function removes byte order marks (BOM) and can repair encoding
  errors.
  
  The value of sizeof(wchar_t) determines which UTF-XX encoding is used.
    sizeof(wchar_t)  UTF-XX
      1              UTF-8
      2              UTF-16
      4              UTF-32

Parameters:
  bTestByteOrder - [in]
    If bTestByteOrder is true and the the input buffer is a 
    byte order mark (BOM), then the BOM is skipped.  It the value
    of the BOM is byte swapped, then subsequent input elements are
    byte swapped before being decoded. Specifically:
    - If the size of an input buffer element is 1 byte and the
      values of the first three input elements are a UTF-8 BOM 
      (0xEF, 0xBB, 0xBF), then the first three input elements are
      ignored and decoding begins at the forth input element.
    - If the size of an input buffer element is 2 bytes and the value
      of the first element is a UTF-16 BOM (0xFEFF), then the first
      element is ignored and decoding begins with the second element.
    - If the size of an input buffer element is 2 bytes and the value
      of the first element is a byte swapped UTF-16 BOM (0xFFFE), 
      then the first element is ignored, decoding begins with the
      second element, and input element bytes are swapped before 
      being decoded.
    - If the size of an input buffer element is 4 bytes and the value
      of the first element is a UTF-32 BOM (0x0000FEFF), then the 
      first element is ignored and decoding begins with the second
      element.
    - If the size of an input buffer element is 4 bytes and the value
      of the first element is bytes swapped UTF-32 BOM (0xFFFE0000),
      then the first element is ignored, decoding begins with the 
      second element, and input element bytes are swapped before 
      being decoded.
    - In all other cases the first element of the input buffer is
      decoded and no byte swapping is performed.

  sInputUTF - [in]
    UTF-XX encoded wchar_t string to convert. 

  sInputUTF_count - [in]
    If sInputUTF_count >= 0, then it specifies the number of
    elements in sInputUTF[] to convert.

    If sInputUTF_count == -1, then sInputUTF must be a zero 
    terminated array and all the elements up to the first zero 
    element are converted.

  error_status - [out]
    If error_status is not null, then bits of *error_status are
    set to indicate the success or failure of the conversion.  
    When the error_mask parameter is used to used to mask some
    conversion errors, multiple bits may be set.
       0: Successful conversion with no errors.
       1: The input parameters were invalid. 
          This error cannot be masked.
       2: The output buffer was not large enough to hold the converted
          string. As much conversion as possible is performed in this
          case and the error cannot be masked.
       4: When parsing a UTF-8 or UTF-32 string, the values of two
          consecutive encoding sequences formed a valid UTF-16 
          surrogate pair.           
          This error is masked if 0 != (4 & m_error_mask).
          If the error is masked, then the surrogate pair is
          decoded, the value of the resulting unicode code point
          is used, and parsing continues.
       8: An overlong UTF-8 encoding sequence was encountered and 
          the value of the overlong sUTF-8 sequence was a valid
          unicode code point.           
          This error is masked if 0 != (8 & m_error_mask).
          If the error is masked, then the unicode code point
          is used and parsing continues.
      16: An illegal UTF-8, UTF-16 or UTF-32 encoding sequence occurred
          or an invalid unicode code point value resulted from decoding
          a UTF-8 sequence. 
          This error is masked if 0 != (16 & m_error_mask).
          If the error is masked and the value of error_code_point is
          a valid unicode code point, then error_code_point is encoded
          in the output string and parsing continues.

  error_mask - [in]
    If 0 != (error_mask & 4), then type 4 errors are masked.
    If 0 != (error_mask & 8), then type 8 errors are masked.
    If 0 != (error_mask & 16) and error_code_point is a valid unicode
    code point value, then type 16 errors are masked.

  error_code_point - [in]
    Unicode code point value to use in when masking type 16 errors.
    If 0 == (error_mask & 16), then this parameter is ignored.
    0xFFFD is a popular choice for the error_code_point value.

  end_element_index - [out]
    If end_element_index is not null, then *end_element_index is the
    index of the first element in sInputUTF that was not converted. 

    If an error occurred and was not masked, then *end_element_index
    is the index of the element of sInputUTF[] where the conversion
    failed.  
    If no errors occurred or all errors were masked, then 
    *end_element_index is the number of elements in sInputUTF[] that
    were converted.

Returns:
  A UTF-XX encoded std::wstring. 
  The returned string does not have a byte order mark (BOM).
*/
std::wstring ON_UTF_WideChar_to_std_wstring( 
  int bTestByteOrder,
  const wchar_t* sInputUTF,
  int sInputUTF_count,
  unsigned int* error_status,
  unsigned int error_mask,
  ON__UINT32 error_code_point,
  int* end_element_index
  ) ON_NOEXCEPT;

/*
Description:
  Convert a UTF-8 encoded std::string to a UTF-XX encoded std::wstring.
  This function removes byte order marks (BOM) and can repair encoding
  errors.
  
  The value of sizeof(wchar_t) determines which UTF-XX encoding is used.
    sizeof(wchar_t)  UTF-XX
      1              UTF-8
      2              UTF-16
      4              UTF-32

Parameters:
  bTestByteOrder - [in]
    If bTestByteOrder is true and the the input buffer is a 
    byte order mark (BOM), then the BOM is skipped.  It the value
    of the BOM is byte swapped, then subsequent input elements are
    byte swapped before being decoded. Specifically:
    - If the size of an input buffer element is 1 byte and the
      values of the first three input elements are a UTF-8 BOM 
      (0xEF, 0xBB, 0xBF), then the first three input elements are
      ignored and decoding begins at the forth input element.
    - If the size of an input buffer element is 2 bytes and the value
      of the first element is a UTF-16 BOM (0xFEFF), then the first
      element is ignored and decoding begins with the second element.
    - If the size of an input buffer element is 2 bytes and the value
      of the first element is a byte swapped UTF-16 BOM (0xFFFE), 
      then the first element is ignored, decoding begins with the
      second element, and input element bytes are swapped before 
      being decoded.
    - If the size of an input buffer element is 4 bytes and the value
      of the first element is a UTF-32 BOM (0x0000FEFF), then the 
      first element is ignored and decoding begins with the second
      element.
    - If the size of an input buffer element is 4 bytes and the value
      of the first element is bytes swapped UTF-32 BOM (0xFFFE0000),
      then the first element is ignored, decoding begins with the 
      second element, and input element bytes are swapped before 
      being decoded.
    - In all other cases the first element of the input buffer is
      decoded and no byte swapping is performed.

  sInputUTF - [in]
    UTF-8 encoded std::string to convert.
 

  sInputUTF_count - [in]
    If sInputUTF_count >= 0, then it specifies the number of
    elements in sInputUTF[] to convert.

    If sInputUTF_count == -1, then sInputUTF must be a zero 
    terminated array and all the elements up to the first zero 
    element are converted.
    
  sUTF8 - [out]
    If sUTF8 is not null and sUTF8_count > 0, then the UTF-8
    encoded string is returned in this buffer. If there is room
    for the null terminator, the converted string will be null
    terminated. The null terminator is never included in the count 
    of returned by this function. The converted string is in the 
    CPU's native byte order. No byte order mark is prepended.

  sUTF8_count - [in]
    If sUTF8_count > 0, then it specifies the number of available
    ON__UINT8 elements in the sUTF8[] buffer.
    
    If sUTF8_count == 0, then the sUTF8 parameter is ignored.

  error_status - [out]
    If error_status is not null, then bits of *error_status are
    set to indicate the success or failure of the conversion.  
    When the error_mask parameter is used to used to mask some
    conversion errors, multiple bits may be set.
       0: Successful conversion with no errors.
       1: The input parameters were invalid. 
          This error cannot be masked.
       2: The output buffer was not large enough to hold the converted
          string. As much conversion as possible is performed in this
          case and the error cannot be masked.
       4: When parsing a UTF-8 or UTF-32 string, the values of two
          consecutive encoding sequences formed a valid UTF-16 
          surrogate pair.           
          This error is masked if 0 != (4 & m_error_mask).
          If the error is masked, then the surrogate pair is
          decoded, the value of the resulting unicode code point
          is used, and parsing continues.
       8: An overlong UTF-8 encoding sequence was encountered and 
          the value of the overlong sUTF-8 sequence was a valid
          unicode code point.           
          This error is masked if 0 != (8 & m_error_mask).
          If the error is masked, then the unicode code point
          is used and parsing continues.
      16: An illegal UTF-8, UTF-16 or UTF-32 encoding sequence occurred
          or an invalid unicode code point value resulted from decoding
          a UTF-8 sequence. 
          This error is masked if 0 != (16 & m_error_mask).
          If the error is masked and the value of error_code_point is
          a valid unicode code point, then error_code_point is encoded
          in the output string and parsing continues.

  error_mask - [in]
    If 0 != (error_mask & 4), then type 4 errors are masked.
    If 0 != (error_mask & 8), then type 8 errors are masked.
    If 0 != (error_mask & 16) and error_code_point is a valid unicode
    code point value, then type 16 errors are masked.

  error_code_point - [in]
    Unicode code point value to use in when masking type 16 errors.
    If 0 == (error_mask & 16), then this parameter is ignored.
    0xFFFD is a popular choice for the error_code_point value.

  end_element_index - [out]
    If end_element_index is not null, then *end_element_index is the
    index of the first element in sInputUTF that was not converted. 

    If an error occurred and was not masked, then *end_element_index
    is the index of the element of sInputUTF[] where the conversion
    failed.  
    If no errors occurred or all errors were masked, then 
    *end_element_index is the number of elements in sInputUTF[] that
    were converted.

Returns:
  A UTF-XX encoded std::wstring. 
  The returned string does not have a byte order mark (BOM).
*/
ON_DECL
std::wstring ON_UTF_std_string_to_std_wstring(
  int bTestByteOrder,
  const std::string& sInputUTF,
  int sInputUTF_count,
  unsigned int* error_status,
  unsigned int error_mask,
  ON__UINT32 error_code_point,
  int* end_element_index
  ) ON_NOEXCEPT;

#endif
