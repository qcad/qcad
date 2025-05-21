#include "opennurbs.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

// NOTE: 
//   /EHsc is used with compiling this file with Microsoft's CL
//   to handle the possible exceptions thrown by std::string.append().

////////////////////////////////////////////////////////////////
//
// UTF-8, UTF-16 and UTF-32 to std::string unicode conversion utilities
//

std::string ON_UTF8_to_std_string(
  int bTestByteOrder,
  const char* sUTF8,
  int sUTF8_count,
  unsigned int* error_status,
  unsigned int error_mask,
  ON__UINT32 error_code_point,
  const char** sNextUTF8
  ) ON_NOEXCEPT
{
  std::string str;
  char buffer[512];
  const int buffer_count = static_cast<int>(sizeof(buffer)/sizeof(buffer[0]));
  unsigned int es;
  const char* sNextIn;

  if ( -1 == sUTF8_count && 0 != sUTF8 )
  {
    for ( sUTF8_count = 0; 0 != sUTF8[sUTF8_count]; sUTF8_count++)
    {
      // empty for body
    }
  }

  buffer[buffer_count-1] = 0;

  if ( 0 != error_status )
    *error_status = 0;

  for(;;)
  {
    es = 0;
    sNextIn = 0;
    int rc = ON_ConvertUTF8ToUTF8(
      bTestByteOrder, sUTF8, sUTF8_count,
      buffer, buffer_count-1,
      &es, error_mask, error_code_point,
      &sNextIn
      );

    // insure buffer[] is null terminated.
    buffer[( rc >= 0 && rc < buffer_count) ? rc : 0] = 0;

    // in_count = number of input sUTF8[] elements that were processed
    int in_count = ( 0 != sNextIn && 0 != sUTF8 && sNextIn > sUTF8 )
      ? static_cast<int>(sNextIn - sUTF8)
      : 0;

    // out_count = number of UTF-8 output values
    int out_count = ( in_count > 0 && rc > 0 && rc < buffer_count) ? rc : 0;

    if ( out_count > 0 )
    {
       try {
        str.append(buffer,out_count);
      } catch (const std::exception& ) {
        es |= 2;
        in_count = 0;
        out_count = 0;
      }
    }

    sUTF8 += in_count;
    sUTF8_count -= in_count;

    if ( 0 != (0x02 & es) && in_count > 0 && out_count > 0 )
    {
      // buffer[] was not long enough and we made progress.
      // Clear bit 2 and allow further processing
      es &= 0xFFFFFFFD;
    }

    if ( 0 != error_status )
      *error_status |= es;

    if ( sUTF8_count > 0 && in_count > 0 && out_count > 0 && 0 == (es & 3) )
    {
      // There were no blocking errors, we made progress, and there is more input
      bTestByteOrder = false;
      continue;
    }

    break; // finished
  }

  if ( sNextUTF8 )
    *sNextUTF8 = sUTF8;

  // On modern compilers, this return will use an efficient rvalue reference.
  return str;
}


std::string ON_UTF16_to_std_string(
  int bTestByteOrder,
  const ON__UINT16* sUTF16,
  int sUTF16_count,
  unsigned int* error_status,
  unsigned int error_mask,
  ON__UINT32 error_code_point,
  const ON__UINT16** sNextUTF16
  ) ON_NOEXCEPT
{
  std::string str;
  char buffer[512];
  const int buffer_count = static_cast<int>(sizeof(buffer)/sizeof(buffer[0]));
  unsigned int es;
  const ON__UINT16* sNextIn;

  if ( -1 == sUTF16_count && 0 != sUTF16 )
  {
    for ( sUTF16_count = 0; 0 != sUTF16[sUTF16_count]; sUTF16_count++)
    {
      // empty for body
    }
  }

  buffer[buffer_count-1] = 0;

  if ( 0 != error_status )
    *error_status = 0;

  for(;;)
  {
    es = 0;
    sNextIn = 0;
    int rc = ON_ConvertUTF16ToUTF8(
      bTestByteOrder, sUTF16, sUTF16_count,
      buffer, buffer_count-1,
      &es, error_mask, error_code_point,
      &sNextIn
      );

    // insure buffer[] is null terminated.
    buffer[( rc >= 0 && rc < buffer_count) ? rc : 0] = 0;

    // in_count = number of input sUTF16[] elements that were processed
    int in_count = ( 0 != sNextIn && 0 != sUTF16 && sNextIn > sUTF16 )
      ? static_cast<int>(sNextIn - sUTF16)
      : 0;

    // out_count = number of UTF-8 output values
    int out_count = ( in_count > 0 && rc > 0 && rc < buffer_count) ? rc : 0;

    if ( out_count > 0 )
    {
      try {
        str.append(buffer,out_count);
      } catch (const std::exception& ) {
        es |= 2;
        in_count = 0;
        out_count = 0;
      }
    }

    sUTF16 += in_count;
    sUTF16_count -= in_count;

    if ( 0 != (0x02 & es) && in_count > 0 && out_count > 0 )
    {
      // buffer[] was not long enough and we made progress.
      // Clear bit 2 and allow further processing
      es &= 0xFFFFFFFD;
    }

    if ( 0 != error_status )
      *error_status |= es;

    if ( sUTF16_count > 0 && in_count > 0 && out_count > 0 && 0 == (es & 3) )
    {
      // There were no blocking errors, we made progress, and there is more input
      bTestByteOrder = false;
      continue;
    }

    break; // finished
  }

  if ( sNextUTF16 )
    *sNextUTF16 = sUTF16;

  // On modern compilers, this return will use an efficient rvalue reference.
  return str;
}

std::string ON_UTF32_to_std_string(
  int bTestByteOrder,
  const ON__UINT32* sUTF32,
  int sUTF32_count,
  unsigned int* error_status,
  unsigned int error_mask,
  ON__UINT32 error_code_point,
  const ON__UINT32** sNextUTF32
  ) ON_NOEXCEPT
{
  std::string str;
  char buffer[512];
  const int buffer_count = static_cast<int>(sizeof(buffer)/sizeof(buffer[0]));
  unsigned int es;
  const ON__UINT32* sNextIn;

  if ( -1 == sUTF32_count && 0 != sUTF32 )
  {
    for ( sUTF32_count = 0; 0 != sUTF32[sUTF32_count]; sUTF32_count++)
    {
      // empty for body
    }
  }

  buffer[buffer_count-1] = 0;

  if ( 0 != error_status )
    *error_status = 0;

  for(;;)
  {
    es = 0;
    sNextIn = 0;
    int rc = ON_ConvertUTF32ToUTF8(
      bTestByteOrder, sUTF32, sUTF32_count,
      buffer, buffer_count-1,
      &es, error_mask, error_code_point,
      &sNextIn
      );

    // insure buffer[] is null terminated.
    buffer[( rc >= 0 && rc < buffer_count) ? rc : 0] = 0;

    // in_count = number of input sUTF32[] elements that were processed
    int in_count = ( 0 != sNextIn && 0 != sUTF32 && sNextIn > sUTF32 )
      ? static_cast<int>(sNextIn - sUTF32)
      : 0;

    // out_count = number of UTF-8 output values
    int out_count = ( in_count > 0 && rc > 0 && rc < buffer_count) ? rc : 0;

    if ( out_count > 0 )
    {
      try {
        str.append(buffer,out_count);
      } catch (const std::exception& ) {
        es |= 2;
        in_count = 0;
        out_count = 0;
      }
    }

    sUTF32 += in_count;
    sUTF32_count -= in_count;

    if ( 0 != (0x02 & es) && in_count > 0 && out_count > 0 )
    {
      // buffer[] was not long enough and we made progress.
      // Clear bit 2 and allow further processing
      es &= 0xFFFFFFFD;
    }

    if ( 0 != error_status )
      *error_status |= es;

    if ( sUTF32_count > 0 && in_count > 0 && out_count > 0 && 0 == (es & 3) )
    {
      // There were no blocking errors, we made progress, and there is more input
      bTestByteOrder = false;
      continue;
    }

    break; // finished
  }

  if ( sNextUTF32 )
    *sNextUTF32 = sUTF32;

  // On modern compilers, this return will use an efficient rvalue reference.
  return str;
}

std::string ON_UTF_WideChar_to_std_string(
  int bTestByteOrder,
  const wchar_t* sInputUTF,
  int sInputUTF_count,
  unsigned int* error_status,
  unsigned int error_mask,
  ON__UINT32 error_code_point,
  int* end_element_index
  ) ON_NOEXCEPT
{
  std::string str;
  const wchar_t* sEndElement = sInputUTF;

  switch(sizeof(wchar_t))
  {
  case sizeof(char):
    str = ON_UTF8_to_std_string(
      bTestByteOrder,
      (const char*)sInputUTF,
      sInputUTF_count,
      error_status,
      error_mask,
      error_code_point,
      (const char**)&sEndElement
      );
    break;

  case sizeof(ON__UINT16):
    str = ON_UTF16_to_std_string(
      bTestByteOrder,
      (const ON__UINT16*)sInputUTF,
      sInputUTF_count,
      error_status,
      error_mask,
      error_code_point,
      (const ON__UINT16**)&sEndElement
      );
    break;

  case sizeof(ON__UINT32):
    str = ON_UTF32_to_std_string(
      bTestByteOrder,
      (const ON__UINT32*)sInputUTF,
      sInputUTF_count,
      error_status,
      error_mask,
      error_code_point,
      (const ON__UINT32**)&sEndElement
      );
    break;

  default:
    if ( 0 != error_status )
      *error_status = 1;
    break;
  }

  if ( 0 != end_element_index )
    *end_element_index = static_cast<int>(sEndElement - sInputUTF);

  return str;
}

////////////////////////////////////////////////////////////////
//
// UTF-8, UTF-16 and UTF-32 to std::wstring unicode conversion utilities
//

std::wstring ON_UTF8_to_std_wstring(
  int bTestByteOrder,
  const char* sUTF8,
  int sUTF8_count,
  unsigned int* error_status,
  unsigned int error_mask,
  ON__UINT32 error_code_point,
  const char** sNextUTF8
  ) ON_NOEXCEPT
{
  std::wstring str;
  wchar_t buffer[512];
  const int buffer_count = static_cast<int>(sizeof(buffer)/sizeof(buffer[0]));
  unsigned int es;
  const char* sNextIn;

  if ( -1 == sUTF8_count && 0 != sUTF8 )
  {
    for ( sUTF8_count = 0; 0 != sUTF8[sUTF8_count]; sUTF8_count++)
    {
      // empty for body
    }
  }

  buffer[buffer_count-1] = 0;

  if ( 0 != error_status )
    *error_status = 0;

  for(;;)
  {
    es = 0;
    sNextIn = 0;
    int rc = ON_ConvertUTF8ToWideChar(
      bTestByteOrder, sUTF8, sUTF8_count,
      buffer, buffer_count-1,
      &es, error_mask, error_code_point,
      &sNextIn
      );

    // insure buffer[] is null terminated.
    buffer[( rc >= 0 && rc < buffer_count) ? rc : 0] = 0;

    // in_count = number of input sUTF8[] elements that were processed
    int in_count = ( 0 != sNextIn && 0 != sUTF8 && sNextIn > sUTF8 )
      ? static_cast<int>(sNextIn - sUTF8)
      : 0;

    // out_count = number of UTF-8 output values
    int out_count = ( in_count > 0 && rc > 0 && rc < buffer_count) ? rc : 0;

    if ( out_count > 0 )
    {
       try {
        str.append(buffer,out_count);
      } catch (const std::exception& ) {
        es |= 2;
        in_count = 0;
        out_count = 0;
      }
    }

    sUTF8 += in_count;
    sUTF8_count -= in_count;

    if ( 0 != (0x02 & es) && in_count > 0 && out_count > 0 )
    {
      // buffer[] was not long enough and we made progress.
      // Clear bit 2 and allow further processing
      es &= 0xFFFFFFFD;
    }

    if ( 0 != error_status )
      *error_status |= es;

    if ( sUTF8_count > 0 && in_count > 0 && out_count > 0 && 0 == (es & 3) )
    {
      // There were no blocking errors, we made progress, and there is more input
      bTestByteOrder = false;
      continue;
    }

    break; // finished
  }

  if ( sNextUTF8 )
    *sNextUTF8 = sUTF8;

  // On modern compilers, this return will use an efficient rvalue reference.
  return str;
}


std::wstring ON_UTF16_to_std_wstring(
  int bTestByteOrder,
  const ON__UINT16* sUTF16,
  int sUTF16_count,
  unsigned int* error_status,
  unsigned int error_mask,
  ON__UINT32 error_code_point,
  const ON__UINT16** sNextUTF16
  ) ON_NOEXCEPT
{
  std::wstring str;
  wchar_t buffer[512];
  const int buffer_count = static_cast<int>(sizeof(buffer)/sizeof(buffer[0]));
  unsigned int es;
  const ON__UINT16* sNextIn;

  if ( -1 == sUTF16_count && 0 != sUTF16 )
  {
    for ( sUTF16_count = 0; 0 != sUTF16[sUTF16_count]; sUTF16_count++)
    {
      // empty for body
    }
  }

  buffer[buffer_count-1] = 0;

  if ( 0 != error_status )
    *error_status = 0;

  for(;;)
  {
    es = 0;
    sNextIn = 0;
    int rc = ON_ConvertUTF16ToWideChar(
      bTestByteOrder, sUTF16, sUTF16_count,
      buffer, buffer_count-1,
      &es, error_mask, error_code_point,
      &sNextIn
      );

    // insure buffer[] is null terminated.
    buffer[( rc >= 0 && rc < buffer_count) ? rc : 0] = 0;

    // in_count = number of input sUTF16[] elements that were processed
    int in_count = ( 0 != sNextIn && 0 != sUTF16 && sNextIn > sUTF16 )
      ? static_cast<int>(sNextIn - sUTF16)
      : 0;

    // out_count = number of UTF-8 output values
    int out_count = ( in_count > 0 && rc > 0 && rc < buffer_count) ? rc : 0;

    if ( out_count > 0 )
    {
      try {
        str.append(buffer,out_count);
      } catch (const std::exception& ) {
        es |= 2;
        in_count = 0;
        out_count = 0;
      }
    }

    sUTF16 += in_count;
    sUTF16_count -= in_count;

    if ( 0 != (0x02 & es) && in_count > 0 && out_count > 0 )
    {
      // buffer[] was not long enough and we made progress.
      // Clear bit 2 and allow further processing
      es &= 0xFFFFFFFD;
    }

    if ( 0 != error_status )
      *error_status |= es;

    if ( sUTF16_count > 0 && in_count > 0 && out_count > 0 && 0 == (es & 3) )
    {
      // There were no blocking errors, we made progress, and there is more input
      bTestByteOrder = false;
      continue;
    }

    break; // finished
  }

  if ( sNextUTF16 )
    *sNextUTF16 = sUTF16;

  // On modern compilers, this return will use an efficient rvalue reference.
  return str;
}

std::wstring ON_UTF32_to_std_wstring(
  int bTestByteOrder,
  const ON__UINT32* sUTF32,
  int sUTF32_count,
  unsigned int* error_status,
  unsigned int error_mask,
  ON__UINT32 error_code_point,
  const ON__UINT32** sEndElement
  ) ON_NOEXCEPT
{
  std::wstring str;
  wchar_t buffer[512];
  const int buffer_count = static_cast<int>(sizeof(buffer)/sizeof(buffer[0]));
  unsigned int es;
  const ON__UINT32* sNextElement;

  if ( -1 == sUTF32_count && 0 != sUTF32 )
  {
    for ( sUTF32_count = 0; 0 != sUTF32[sUTF32_count]; sUTF32_count++)
    {
      // empty for body
    }
  }

  buffer[buffer_count-1] = 0;

  if ( 0 != error_status )
    *error_status = 0;

  for(;;)
  {
    es = 0;
    sNextElement = 0;
    int rc = ON_ConvertUTF32ToWideChar(
      bTestByteOrder, sUTF32, sUTF32_count,
      buffer, buffer_count-1,
      &es, error_mask, error_code_point,
      &sNextElement
      );

    // insure buffer[] is null terminated.
    buffer[( rc >= 0 && rc < buffer_count) ? rc : 0] = 0;

    // in_count = number of input sUTF32[] elements that were processed
    int in_count = ( 0 != sNextElement && 0 != sUTF32 && sNextElement > sUTF32 )
      ? static_cast<int>(sNextElement - sUTF32)
      : 0;

    // out_count = number of UTF-8 output values
    int out_count = ( in_count > 0 && rc > 0 && rc < buffer_count) ? rc : 0;

    if ( out_count > 0 )
    {
      try {
        str.append(buffer,out_count);
      } catch (const std::exception& ) {
        es |= 2;
        in_count = 0;
        out_count = 0;
      }
    }

    sUTF32 += in_count;
    sUTF32_count -= in_count;

    if ( 0 != (0x02 & es) && in_count > 0 && out_count > 0 )
    {
      // buffer[] was not long enough and we made progress.
      // Clear bit 2 and allow further processing
      es &= 0xFFFFFFFD;
    }

    if ( 0 != error_status )
      *error_status |= es;

    if ( sUTF32_count > 0 && in_count > 0 && out_count > 0 && 0 == (es & 3) )
    {
      // There were no blocking errors, we made progress, and there is more input
      bTestByteOrder = false;
      continue;
    }

    break; // finished
  }

  if ( sEndElement )
    *sEndElement = sUTF32;

  // On modern compilers, this return will use an efficient rvalue reference.
  return str;
}


std::wstring ON_UTF_WideChar_to_std_wstring(
  int bTestByteOrder,
  const wchar_t* sInputUTF,
  int sInputUTF_count,
  unsigned int* error_status,
  unsigned int error_mask,
  ON__UINT32 error_code_point,
  int* end_element_index
  ) ON_NOEXCEPT
{
  std::wstring str;
  const wchar_t* sEndElement = sInputUTF;

  switch(sizeof(wchar_t))
  {
  case sizeof(char):
    str = ON_UTF8_to_std_wstring(
      bTestByteOrder,
      (const char*)sInputUTF,
      sInputUTF_count,
      error_status,
      error_mask,
      error_code_point,
      (const char**)&sEndElement
      );
    break;

  case sizeof(ON__UINT16):
    str = ON_UTF16_to_std_wstring(
      bTestByteOrder,
      (const ON__UINT16*)sInputUTF,
      sInputUTF_count,
      error_status,
      error_mask,
      error_code_point,
      (const ON__UINT16**)&sEndElement
      );
    break;

  case sizeof(ON__UINT32):
    str = ON_UTF32_to_std_wstring(
      bTestByteOrder,
      (const ON__UINT32*)sInputUTF,
      sInputUTF_count,
      error_status,
      error_mask,
      error_code_point,
      (const ON__UINT32**)&sEndElement
      );
    break;

  default:
    if ( 0 != error_status )
      *error_status = 1;
    break;
  }

  if ( 0 != end_element_index )
    *end_element_index = static_cast<int>(sEndElement - sInputUTF);

  return str;
}

std::string ON_UTF_std_wstring_to_std_string(
  int bTestByteOrder,
  const std::wstring& sInputUTF,
  int sInputUTF_count,
  unsigned int* error_status,
  unsigned int error_mask,
  ON__UINT32 error_code_point,
  int* end_element_index
  ) ON_NOEXCEPT
{
  std::string str;
  
  const int sUTF_length = static_cast<int>(sInputUTF.length());

  if ( sInputUTF_count > sUTF_length )
  {
    if ( 0 != end_element_index )
      *end_element_index = 0;
    if ( 0 != error_status )
      *error_status = 1;
    return str;
  }
  
  if ( -1 == sInputUTF_count )
    sInputUTF_count = sUTF_length;

  str = ON_UTF_WideChar_to_std_string(
    bTestByteOrder,
    sInputUTF.c_str(),
    sInputUTF_count,
    error_status,
    error_mask,
    error_code_point,
    end_element_index
    );

  return str;
}


std::wstring ON_UTF_std_string_to_std_wstring(
  int bTestByteOrder,
  const std::string& sInputUTF,
  int sInputUTF_count,
  unsigned int* error_status,
  unsigned int error_mask,
  ON__UINT32 error_code_point,
  int* end_element_index
  ) ON_NOEXCEPT
{
  std::wstring str;
  
  const int sUTF8_length = static_cast<int>(sInputUTF.length());

  if ( sInputUTF_count > sUTF8_length )
  {
    if ( 0 != end_element_index )
      *end_element_index = 0;
    if ( 0 != error_status )
      *error_status = 1;
    return str;
  }
  
  if ( -1 == sInputUTF_count )
    sInputUTF_count = sUTF8_length;

  const char* sInputUTFc_str = sInputUTF.c_str();
  const char* sEndElement = sInputUTFc_str;
  str = ON_UTF8_to_std_wstring(
    bTestByteOrder,
    sInputUTFc_str,
    sInputUTF_count,
    error_status,
    error_mask,
    error_code_point,
    &sEndElement
    );

  if ( 0 != end_element_index )
    *end_element_index = static_cast<int>(sEndElement - sInputUTFc_str);

  return str;
}
