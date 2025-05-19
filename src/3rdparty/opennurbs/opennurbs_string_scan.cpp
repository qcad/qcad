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

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ON_String scanning
//

int ON_VARGS_FUNC_CDECL ON_String::Scan(
  const char* format,
  ...
  )
{
  va_list args;
  va_start(args, format);
  int rc = ON_String::ScanBufferVargs(Array(), format, args);
  va_end(args);
  return rc;
}

int ON_VARGS_FUNC_CDECL ON_String::Scan(
  const unsigned char* format,
  ...
  )
{
  va_list args;
  va_start(args, format);
  int rc = ON_String::ScanBufferVargs(Array(), (const char*)format, args);
  va_end(args);
  return rc;
}

int ON_VARGS_FUNC_CDECL ON_String::ScanBuffer(
  const char* buffer,
  const char* format,
  ...
  )
{
  va_list args;
  va_start(args, format);
  int rc = ON_String::ScanBufferVargs(buffer, format, args);
  va_end(args);
  return rc;
}

int ON_VARGS_FUNC_CDECL ON_String::ScanBuffer(
  const unsigned char* buffer,
  const unsigned char* format,
  ...
  )
{
  va_list args;
  va_start(args, format);
  int rc = ON_String::ScanBufferVargs(buffer, format, args);
  va_end(args);
  return rc;
}

int ON_String::ScanBufferVargs(
  const char* buffer,
  const char* format,
  va_list args
  )
{
#if defined(ON_COMPILER_CLANG) || defined(ON_RUNTIME_LINUX) || defined(ON_RUNTIME_WASM)
#if defined(ON_RUNTIME_ANDROID) || defined(ON_RUNTIME_LINUX) || defined(ON_RUNTIME_WASM)
  if (nullptr == buffer || nullptr == format)
    return -1;
  return vsscanf(buffer, format, args);
#else
  if (nullptr == buffer || nullptr == format || nullptr == args)
    return -1;
  return vsscanf_l(buffer, ON_Locale::InvariantCulture.NumericLocalePtr(), format, args);
#endif
#else
  if (nullptr == buffer || nullptr == format || nullptr == args)
    return -1;
  return _vsscanf_s_l(buffer, format, ON_Locale::InvariantCulture.NumericLocalePtr(), args);
#endif
}

int ON_String::ScanBufferVargs(
  const unsigned char* buffer,
  const unsigned char* format,
  va_list args
  )
{
  return ON_String::ScanBufferVargs((const char*)buffer, (const char*)format, args);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ON_wString scanning
//

int ON_VARGS_FUNC_CDECL ON_wString::Scan(
  const wchar_t* format,
  ...
  ) const
{
  va_list args;
  va_start(args, format);
  int rc = ON_wString::ScanBufferVargs(Array(), format, args);
  va_end(args);
  return rc;
}

int ON_VARGS_FUNC_CDECL ON_wString::ScanBuffer(
  const wchar_t* buffer,
  const wchar_t* format,
  ...
  )
{
  va_list args;
  va_start(args, format);
  int rc = ON_wString::ScanBufferVargs(buffer, format, args);
  va_end(args);
  return rc;
}

int ON_wString::ScanBufferVargs(
  const wchar_t* buffer,
  const wchar_t* format,
  va_list args
  )
{
  if (nullptr == buffer || nullptr == format)
    return -1;
  
#if defined(ON_RUNTIME_WIN)
  if (nullptr == args)
    return -1;
  return _vswscanf_s_l(buffer, format, ON_Locale::InvariantCulture.NumericLocalePtr(), args);
#elif defined(ON_RUNTIME_APPLE)
  if (nullptr == args)
    return -1;
  return swscanf_l(buffer, _c_locale, format, args);
#elif defined(ON_RUNTIME_ANDROID) || defined(ON_RUNTIME_LINUX) || defined(ON_RUNTIME_WASM)
  return swscanf(buffer, format, args);
#else
  return swscanf(buffer, format, args);
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ON_String::ToNumber
//

#define SIGNED_TO_NUMBER( cypte, strytpe, itype, min_limit, max_limit ) \
if (nullptr == value) return nullptr; \
ON__INT64 _i; \
const cypte* rc = strytpe::ToNumber(buffer, (ON__INT64)value_on_failure, &_i); \
if (nullptr != rc && _i >= min_limit && _i <= max_limit) *value = (itype)_i; \
else { rc = nullptr; *value = value_on_failure; } \
return rc

#define UNSIGNED_TO_NUMBER( cypte, strytpe, utype, max_limit ) \
if (nullptr == value) return nullptr; \
ON__UINT64 _u; \
const cypte* rc = strytpe::ToNumber(buffer, (ON__UINT64)value_on_failure, &_u); \
if (nullptr != rc && _u <= max_limit) *value = (unsigned utype)_u; \
else { rc = nullptr; *value = value_on_failure; } \
return rc

const char* ON_String::ToNumber(
  const char* buffer,
  char value_on_failure,
  char* value
  )
{
  SIGNED_TO_NUMBER(char, ON_String, char, -128, 127);
}

const char* ON_String::ToNumber(
  const char* buffer,
  unsigned char value_on_failure,
  unsigned char* value
  )
{
  UNSIGNED_TO_NUMBER(char, ON_String, char, 0xff);
}

const char* ON_String::ToNumber(
  const char* buffer,
  short value_on_failure,
  short* value
  )
{
  SIGNED_TO_NUMBER(char, ON_String, short, -32768, 32767);
}

const char* ON_String::ToNumber(
  const char* buffer,
  unsigned short value_on_failure,
  unsigned short* value
  )
{
  UNSIGNED_TO_NUMBER(char, ON_String, short, 0xffff);
}

const char* ON_String::ToNumber(
  const char* buffer,
  int value_on_failure,
  int* value
  )
{
  SIGNED_TO_NUMBER(char, ON_String, int, -2147483648LL, 2147483647LL);
}

const char* ON_String::ToNumber(
  const char* buffer,
  unsigned int value_on_failure,
  unsigned int* value
  )
{
  UNSIGNED_TO_NUMBER(char, ON_String, int, 0xffffffff);
}

const char* ON_String::ToNumber(
  const char* buffer,
  ON__INT64 value_on_failure,
  ON__INT64* value
  )
{
  if (nullptr == value)
    return nullptr;

  ON__INT64 i;
  ON__UINT64 u;
  const char* rc;
  if ('-' == buffer[0] && buffer[1] >= '0' && buffer[1] <= '9')
  {
    rc = ON_String::ToNumber(buffer + 1, 0, &u);
    if (nullptr != rc && u <= 9223372036854775808LLU)
    {
      i = -((ON__INT64)u);
    }
    else
    {
      i = value_on_failure;
      rc = nullptr;
    }
  }
  else
  {
    rc = ON_String::ToNumber(buffer, 0, &u);
    if (nullptr != rc && u <= 9223372036854775807LLU)
    {
      i = (ON__INT64)u;
    }
    else
    {
      i = value_on_failure;
      rc = nullptr;
    }
  }

  *value = i;
  return rc;
}

const char* ON_String::ToNumber(
  const char* buffer,
  ON__UINT64 value_on_failure,
  ON__UINT64* value
  )
{
  if (nullptr == value)
    return nullptr;

  ON__UINT64 u = value_on_failure;
  const char* rc = nullptr;

  if (nullptr != buffer)
  {
    if ('+' == buffer[0])
      buffer++;
    if (buffer[0] >= '0' && buffer[0] <= '9')
    {
      ON__UINT64 r = (ON__UINT64)(*buffer++ - '0');
      for (const char* s = buffer;/*empty test*/; s++)
      {
        if (*s >= '0' && *s <= '9')
        {
          ON__UINT64 d = ON__UINT64(*s - '0');
          ON__UINT64 r1 = r * 10LLU + d;
          if (r1 < r)
          {
            // overflow
            break;
          }
          r = r1;
          continue;
        }
        u = r;
        rc = s;
        break;
      }
    }
  }

  *value = u;
  return rc;
}

const char* ON_String::ToNumber(
  const char* buffer,
  double value_on_failure,
  double* value
  )
{
  if (nullptr == value)
    return nullptr;
  *value = value_on_failure;
  if (nullptr == buffer)
    return nullptr;

  char local_buffer[512];
  const size_t local_buffer_capacity = sizeof(local_buffer) / sizeof(local_buffer[0]);
  size_t local_buffer_count = 0;

  if ('-' == *buffer || '+' == *buffer)
    local_buffer[local_buffer_count++] = (char)(*buffer++);

  bool bHaveMantissa = false;
  while (buffer[0] >= '0' && buffer[0] <= '9')
  {
    if (local_buffer_count >= local_buffer_capacity)
      return nullptr;
    local_buffer[local_buffer_count++] = (char)(*buffer++);
    bHaveMantissa = true;
  }

  if ('.' == *buffer)
  {
    if (local_buffer_count >= local_buffer_capacity)
      return nullptr;
    local_buffer[local_buffer_count++] = (char)(*buffer++);

    while (buffer[0] >= '0' && buffer[0] <= '9')
    {
      if (local_buffer_count >= local_buffer_capacity)
        return nullptr;
      local_buffer[local_buffer_count++] = (char)(*buffer++);
      bHaveMantissa = true;
    }
  }

  if (false == bHaveMantissa)
    return nullptr;

  if ('e' == *buffer || 'E' == *buffer)
  {
    if (local_buffer_count >= local_buffer_capacity)
      return nullptr;
    local_buffer[local_buffer_count++] = (char)(*buffer++);

    if ('-' == *buffer || '+' == *buffer)
    {
      if (local_buffer_count >= local_buffer_capacity)
        return nullptr;
      local_buffer[local_buffer_count++] = (char)(*buffer++);
    }

    while (buffer[0] >= '0' && buffer[0] <= '9')
    {
      if (local_buffer_count >= local_buffer_capacity)
        return nullptr;
      local_buffer[local_buffer_count++] = (char)(*buffer++);
    }
  }

  local_buffer[local_buffer_count++] = 0;

  double x = value_on_failure;
#if defined(ON_COMPILER_CLANG) || defined(ON_RUNTIME_LINUX) || defined(ON_RUNTIME_WASM)
#if defined(ON_RUNTIME_ANDROID) || defined(ON_RUNTIME_LINUX) || defined(ON_RUNTIME_WASM)
  if (1 == sscanf(local_buffer, "%lg", &x))
  {
    *value = x;
    return buffer;
  }
#else
  if (1 == sscanf_l(local_buffer, ON_Locale::InvariantCulture.NumericLocalePtr(), "%lg", &x))
  {
    *value = x;
    return buffer;
  }
#endif
#else
  if (1 == _sscanf_s_l(local_buffer, "%lg", ON_Locale::InvariantCulture.NumericLocalePtr(), &x))
  {
    *value = x;
    return buffer;
  }
#endif
  *value = value_on_failure;
  return nullptr;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ON_wString::ToNumber
//

const wchar_t* ON_wString::ToNumber(
  const wchar_t* buffer,
  char value_on_failure,
  char* value
  )
{
  SIGNED_TO_NUMBER(wchar_t, ON_wString, char, -128, 127);
}

const wchar_t* ON_wString::ToNumber(
  const wchar_t* buffer,
  unsigned char value_on_failure,
  unsigned char* value
  )
{
  UNSIGNED_TO_NUMBER(wchar_t, ON_wString, char, 0xff);
}

const wchar_t* ON_wString::ToNumber(
  const wchar_t* buffer,
  short value_on_failure,
  short* value
  )
{
  SIGNED_TO_NUMBER(wchar_t, ON_wString, short, -32768, 32767);
}

const wchar_t* ON_wString::ToNumber(
  const wchar_t* buffer,
  unsigned short value_on_failure,
  unsigned short* value
  )
{
  UNSIGNED_TO_NUMBER(wchar_t, ON_wString, short, 0xffff);
}

const wchar_t* ON_wString::ToNumber(
  const wchar_t* buffer,
  int value_on_failure,
  int* value
  )
{
  SIGNED_TO_NUMBER(wchar_t, ON_wString, int, -2147483648LL, 2147483647LL);
}

const wchar_t* ON_wString::ToNumber(
  const wchar_t* buffer,
  unsigned int value_on_failure,
  unsigned int* value
  )
{
  UNSIGNED_TO_NUMBER(wchar_t, ON_wString, int, 0xffffffff);
}

const wchar_t* ON_wString::ToNumber(
  const wchar_t* buffer,
  ON__INT64 value_on_failure,
  ON__INT64* value
  )
{
  if (nullptr == value)
    return nullptr;

  ON__INT64 i = value_on_failure;
  ON__UINT64 u = 0;
  const wchar_t* rc = nullptr;

  const wchar_t c0 = buffer[0];
  const int sign = ON_wString::PlusOrMinusSignFromWideChar(c0, true, true, true);
  if (0 != sign)
    ++buffer; // c0 is some type of plus or minus sign.

  const bool b0 = ON_wString::IsDecimalDigit(buffer[0], true, false, false);
  const bool b1 = false == b0 && ON_wString::IsDecimalDigit(buffer[0], false, true, false);
  const bool b2 = false == b0 && false == b1 && ON_wString::IsDecimalDigit(buffer[0], false, false, true);

  if ((b0 || b1 || b2) && sign == ON_wString::PlusOrMinusSignFromWideChar(c0, b0, b1, b2))
  {
    if (sign < 0)
    {
      rc = ON_wString::ToNumber(buffer, 0, &u);
      if (nullptr != rc && u <= 9223372036854775808LLU)
      {
        i = -((ON__INT64)u);
      }
      else
      {
        i = value_on_failure;
        rc = nullptr;
      }
    }
    else
    {
      rc = ON_wString::ToNumber(buffer, 0, &u);
      if (nullptr != rc && u <= 9223372036854775807LLU)
      {
        i = (ON__INT64)u;
      }
      else
      {
        i = value_on_failure;
        rc = nullptr;
      }
    }
  }

  *value = i;
  return rc;
}

const wchar_t* ON_wString::ToNumber(
  const wchar_t* buffer,
  ON__UINT64 value_on_failure,
  ON__UINT64* value
  )
{
  if (nullptr == value)
    return nullptr;

  ON__UINT64 u = value_on_failure;
  const wchar_t* rc = nullptr;

  if (nullptr != buffer)
  {
    const wchar_t c0 = buffer[0];
    const int sign = ON_wString::PlusOrMinusSignFromWideChar(c0,true,true,true);
    if (sign > 0)
      ++buffer; // c0 is some type of plus sign.

    const bool b0 = ON_wString::IsDecimalDigit(buffer[0], true, false, false);
    const bool b1 = false == b0 && ON_wString::IsDecimalDigit(buffer[0], false, true, false);
    const bool b2 = false == b0 && false == b1 && ON_wString::IsDecimalDigit(buffer[0], false, false, true);

    if ((b0 || b1 || b2) && sign == ON_wString::PlusOrMinusSignFromWideChar(c0, b0, b1, b2))
    {
      ON__UINT64 r = 0;
      for (const wchar_t* s = buffer;/*empty test*/; s++)
      {
        const ON__UINT64 d = (ON__UINT64)ON_wString::DecimalDigitFromWideChar(*s, b0, b1, b2, 10);
        if (d < 10LLU)
        {
          const ON__UINT64 r1 = r * 10LLU + d;
          if (r1 < r)
          {
            // overflow
            break;
          }
          r = r1;
          continue;
        }
        u = r;
        rc = s;
        break;
      }
    }
  }

  *value = u;
  return rc;
}

const wchar_t* ON_wString::ToNumber(
  const wchar_t* buffer,
  double value_on_failure,
  double* value
  )
{
  if (nullptr == value)
    return nullptr;
  *value = value_on_failure;
  if (nullptr == buffer)
    return nullptr;

  char local_buffer[512];
  const size_t local_buffer_capacity = sizeof(local_buffer) / sizeof(local_buffer[0]);
  size_t local_buffer_count = 0;

  if ('-' == *buffer || '+' == *buffer)
    local_buffer[local_buffer_count++] = (char)(*buffer++);

  bool bHaveMantissa = false;
  while (buffer[0] >= '0' && buffer[0] <= '9')
  {
    if (local_buffer_count >= local_buffer_capacity)
      return nullptr;
    local_buffer[local_buffer_count++] = (char)(*buffer++);
    bHaveMantissa = true;
  }

  if ('.' == *buffer)
  {
    if (local_buffer_count >= local_buffer_capacity)
      return nullptr;
    local_buffer[local_buffer_count++] = (char)(*buffer++);

    while (buffer[0] >= '0' && buffer[0] <= '9')
    {
      if (local_buffer_count >= local_buffer_capacity)
        return nullptr;
      local_buffer[local_buffer_count++] = (char)(*buffer++);
      bHaveMantissa = true;
    }
  }

  if (false == bHaveMantissa)
    return nullptr;

  if ('e' == *buffer || 'E' == *buffer)
  {
    if (local_buffer_count >= local_buffer_capacity)
      return nullptr;
    local_buffer[local_buffer_count++] = (char)(*buffer++);

    if ('-' == *buffer || '+' == *buffer)
    {
      if (local_buffer_count >= local_buffer_capacity)
        return nullptr;
      local_buffer[local_buffer_count++] = (char)(*buffer++);
    }

    while (buffer[0] >= '0' && buffer[0] <= '9')
    {
      if (local_buffer_count >= local_buffer_capacity)
        return nullptr;
      local_buffer[local_buffer_count++] = (char)(*buffer++);
    }
  }

  local_buffer[local_buffer_count++] = 0;

  double x = value_on_failure;
#if defined(ON_COMPILER_CLANG) || defined(ON_RUNTIME_LINUX) || defined(ON_RUNTIME_WASM)
#if defined(ON_RUNTIME_ANDROID) || defined(ON_RUNTIME_LINUX) || defined(ON_RUNTIME_WASM)
  if (1 == sscanf(local_buffer, "%lg", &x))
  {
    *value = x;
    return buffer;
  }
#else
  if (1 == sscanf_l(local_buffer, ON_Locale::InvariantCulture.NumericLocalePtr(), "%lg", &x))
  {
    *value = x;
    return buffer;
  }
#endif
#else
  if (1 == _sscanf_s_l(local_buffer, "%lg", ON_Locale::InvariantCulture.NumericLocalePtr(), &x))
  {
    *value = x;
    return buffer;
  }
#endif
  *value = value_on_failure;
  return nullptr;
}

const ON_wString ON_wString::ToMemorySize(size_t size_in_bytes)
{
  if (size_in_bytes <= 0)
    return ON_wString(L"0 bytes");

  ON__UINT64 sz = (ON__UINT64)size_in_bytes;

  const wchar_t* units;
  const ON__UINT64 kb = 1024;
  const ON__UINT64 mb = kb * kb;
  const ON__UINT64 gb = kb * mb;
  const ON__UINT64 tb = kb * gb;
  const ON__UINT64 pb = kb * tb;
  if (sz >= pb)
  {
    // petabytes
    sz /= tb;
    units = L"PB";
  }
  else if (sz >= tb)
  {
    // terabytes
    sz /= gb;
    units = L"TB";
  }
  else if (sz >= gb)
  {
    // gigabytes
    sz /= mb;
    units = L"GB";
  }
  else if (sz >= mb)
  {
    // megaabytes
    sz /= kb;
    units = L"MB";
  }
  else if (sz >= kb)
  {
    // kilobytes
    units = L"KB";
  }
  else
  {
    // bytes
    return  (1==sz) ? ON_wString(L"1 byte") : ON_wString::FormatToString(L"%u bytes",(unsigned)sz);
  }

  const ON__UINT64 n = sz / kb;
  const ON__UINT64 r = sz % kb;
  if (r > 0 && n < 100)
  {
    const double x = ((double)sz)/((double)kb);
    if (0 == n)
      return ON_wString::FormatToString(L"%0.03f %ls", x, units);

    if (n >= 10)
      return ON_wString::FormatToString(L"%0.1f %ls", x, units);

    return ON_wString::FormatToString(L"%0.2f %ls", x, units);
  }

  return ON_wString::FormatToString(L"%u %ls", ((unsigned)n), units);
}

#undef SIGNED_TO_NUMBER
#undef UNSIGNED_TO_NUMBER
