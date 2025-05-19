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

#define STRING_COMPARE_PREAMBLE(CTYPE,LENGTH,S1,CT1,S2,CT2,EQ,LT,GT) \
  if ( (nullptr == S1 && 0 != CT1) || (nullptr == S2 && 0 != CT2) ) \
  { if ( S1 == S2 ) return EQ; if (nullptr == S1) return LT; if (nullptr == S2) return GT; } \
  const CTYPE null_terminator = 0; \
  if (CT1 < 0) CT1 = LENGTH(S1); \
  if (CT2 < 0) CT2 = LENGTH(S2); \
  if (0 == CT1) S1 = &null_terminator; \
  if (0 == CT2) S2 = &null_terminator; \
  if (S1 == S2 && CT1 == CT2) return EQ

#define WIDE_STRING_COMPARE_PREAMBLE(S1,CT1,S2,CT2) STRING_COMPARE_PREAMBLE(wchar_t,ON_wString::Length,S1,CT1,S2,CT2,0,-1,1)
#define CHAR_STRING_COMPARE_PREAMBLE(S1,CT1,S2,CT2) STRING_COMPARE_PREAMBLE(char,ON_String::Length,S1,CT1,S2,CT2,0,-1,1)

#define WIDE_STRING_EQUAL_PREAMBLE(S1,CT1,S2,CT2) STRING_COMPARE_PREAMBLE(wchar_t,ON_wString::Length,S1,CT1,S2,CT2,true,false,false)
#define CHAR_STRING_EQUAL_PREAMBLE(S1,CT1,S2,CT2) STRING_COMPARE_PREAMBLE(char,ON_String::Length,S1,CT1,S2,CT2,true,false,false)

ON_StringMapOrdinalType ON_StringMapOrdinalTypeFromStringMapType(
  ON_StringMapType map_type
  )
{
  switch (map_type)
  {
  case ON_StringMapType::UpperCase:
    return ON_StringMapOrdinalType::UpperOrdinal;
  case ON_StringMapType::LowerCase:
    return ON_StringMapOrdinalType::LowerOrdinal;
  case ON_StringMapType::Identity:
    return ON_StringMapOrdinalType::Identity;
  }
  return ON_StringMapOrdinalType::Identity;
}

static ON__UINT32 MapCodePointOrdinal(
  ON__UINT32 unicode_code_point,
  unsigned int maximum_singleton_value,
  ON_StringMapOrdinalType map_type
  )
{
  // Converts ordinal "char" and "wchar_t" element values in the
  // range 0x00 to maximum_singleton_value to "ignore case" ordinal equivalents.
  // The returned value is always <= input value.
  //
  // This is NOT linguistic and NOT culture invariant.
  //
  // For UTF-8 strings, maximum_singleton_value = 0x7FU
  // For UTF-16 strings, maximum_singleton_value = 0xFFFFU
  // For UTF-32 strings, maximum_singleton_value = 0xFFFFFFFFU

  // TODO
  //   Should ordinal ignore case compares this modify any values > 0x00FFU?

  if (unicode_code_point < 0x0041U || unicode_code_point > maximum_singleton_value)
    return unicode_code_point;

  if (unicode_code_point <= 0x005AU)
  {
    // unicode_code_points U+0041 = capital A to U+005A = capital Z
    if (ON_StringMapOrdinalType::LowerOrdinal == map_type)
    {
      return unicode_code_point + 0x20;
    }
    return unicode_code_point;
  }

  if (unicode_code_point < 0x0061U)
  {
    // unicode_code_points for the the six glyphs
    // U+005B [
    // U+005C \
    // U+005D ]
    // U+005E ^
    // U+005F _
    // U+0060 `
    // These are the ASCII symbols after capital Z and before lower case A (a)
    // that were inserted so that converting between A...Z and a...z
    // could be done by setting/clearing a single bit 0x20.
    // The first edition of the ASCII standard was published in 1963.
    return unicode_code_point;
  }

  if (unicode_code_point <= 0x007AU)
  {
    // unicode_code_points u+0061 = lower case A (a) to U+007A = lower case Z (z)

    if (ON_StringMapOrdinalType::UpperOrdinal == map_type)
    {
      return unicode_code_point - 0x20;
    }

    if (ON_StringMapOrdinalType::MinimumOrdinal == map_type)
    {
      return unicode_code_point - 0x20;
    }

    return unicode_code_point;
  }

  if ( unicode_code_point < 0x00C0U )
    return unicode_code_point;

  if (unicode_code_point <= 0x00DE)
  {
    // 0x00C0: LATIN CAPITAL LETTER A WITH GRAVE
    // ...
    // 0x00D7: MULTIPLICATION SIGN
    // ...
    // 0x00DE: LATIN CAPITAL LETTER THORN
    if ( unicode_code_point == 0x00D7 )
      return unicode_code_point; // MULTIPLICATION SIGN

    if ( ON_StringMapOrdinalType::LowerOrdinal == map_type)
      return unicode_code_point + 0x20;

    return unicode_code_point;
  }

  if (unicode_code_point < 0x00E0U)
    return unicode_code_point;

  if (unicode_code_point <= 0x00FEU)
  {
    // 0x00E0: LATIN SMALL LETTER A WITH GRAVE
    // ...
    // 0x00F7: DIVISION SIGN
    // ...
    // 0x00FE: LATIN SMALL LETTER THORN
    if (0x00F7U == unicode_code_point)
      return unicode_code_point; // DIVISION SIGN

    if ( ON_StringMapOrdinalType::MinimumOrdinal == map_type || ON_StringMapOrdinalType::UpperOrdinal == map_type )
      return unicode_code_point - 0x20;
    return unicode_code_point;
  }

  if (unicode_code_point <= 0x00FFU)
  {
    // 0x00FFU: LATIN SMALL LETTER Y WITH DIAERESIS
    if ( ON_StringMapOrdinalType::UpperOrdinal == map_type && 0x0178U <= maximum_singleton_value )
      return 0x0178U; // 0x0178U: LATIN CAPITAL LETTER Y WITH DIAERESIS
    return unicode_code_point;
  }

  if (unicode_code_point <= 0x017FU)
  {
    // Latin Extended-A

    // special cases
    switch (unicode_code_point)
    {
    case 0x0130U: // LATIN CAPITAL LETTER I WITH DOT ABOVE
      if (ON_StringMapOrdinalType::MinimumOrdinal == map_type || ON_StringMapOrdinalType::LowerOrdinal == map_type)
        return 0x0069U; // 0x0069U: LATIN SMALL LETTER i
      return unicode_code_point;
      break;

    case 0x0131U: // LATIN SMALL LETTER DOTLESS I
      if (ON_StringMapOrdinalType::MinimumOrdinal == map_type || ON_StringMapOrdinalType::UpperOrdinal == map_type)
        return 0x0049U; // 0x0049U LATIN CAPITAL LETTER I
      return unicode_code_point;
      break;

    case 0x0138U: // LATIN SMALL LETTER KRA
      // No upper case ordinal
      return unicode_code_point;
      break;

    case 0x0149U: // LATIN SMALL LETTER N PRECEDED BY APOSTROPHE
      if (ON_StringMapOrdinalType::MinimumOrdinal == map_type || ON_StringMapOrdinalType::UpperOrdinal == map_type)
        return 0x004EU; // 0x004EU LATIN CAPITAL LETTER N
      return unicode_code_point;
      break;

    case 0x0178U: // LATIN CAPITAL LETTER Y WITH DIAERESIS
      if ( ON_StringMapOrdinalType::MinimumOrdinal == map_type || ON_StringMapOrdinalType::LowerOrdinal == map_type )
        return 0x00FFU; // 0x00FFU: LATIN SMALL LETTER Y WITH DIAERESIS
      return unicode_code_point;
      break;

    case 0x017FU: // LATIN SMALL LETTER LONG S
      // No upper case ordinal
      return unicode_code_point;
      break;
    }

    if (unicode_code_point < 0x0138U || (unicode_code_point >= 0x014AU && unicode_code_point < 0x0178U) )
    {
      // CAPITALS are even and SMALL is CAPITAL+1
      if (0 == (unicode_code_point % 2))
      {
        // LATIN CAPITAL LETTER
        if (ON_StringMapOrdinalType::LowerOrdinal == map_type)
          return unicode_code_point + 1;
      }
      else
      {
        // LATIN SMALL LETTER
        if (ON_StringMapOrdinalType::MinimumOrdinal == map_type || ON_StringMapOrdinalType::UpperOrdinal == map_type)
          return unicode_code_point - 1;
      }
      return unicode_code_point;
    }
    else
    {
      // CAPITALS are odd and SMALL is CAPITAL+1
      if (1 == (unicode_code_point % 2))
      {
        // LATIN CAPITAL LETTER
        if (ON_StringMapOrdinalType::LowerOrdinal == map_type)
          return unicode_code_point + 1;
      }
      else
      {
        // LATIN SMALL LETTER
        if (ON_StringMapOrdinalType::MinimumOrdinal == map_type || ON_StringMapOrdinalType::UpperOrdinal == map_type)
          return unicode_code_point - 1;
      }
    }

    return unicode_code_point;
  }


  if (unicode_code_point <= 0x01FFU)
  {
    // Latin Extended-B

    // special cases
    switch (unicode_code_point)
    {
    case 0x0180U: // LATIN SMALL LETTER B WITH STROKE
      if (ON_StringMapOrdinalType::UpperOrdinal == map_type)
        return 0x0243U;
      return unicode_code_point;
      break;
    case 0x0193U: // LATIN CAPITAL LETTER G WITH HOOK
      if (ON_StringMapOrdinalType::LowerOrdinal == map_type)
        return 0x0260U;
      return unicode_code_point;
      break;
    case 0x0194U: // LATIN CAPITAL LETTER GAMMA
      if (ON_StringMapOrdinalType::LowerOrdinal == map_type)
        return 0x0263U;
      return unicode_code_point;
      break;
    case 0x0195U: // LATIN SMALL LETTER HV
      if (ON_StringMapOrdinalType::UpperOrdinal == map_type)
        return 0x01F6U;
      return unicode_code_point;
      break;
    case 0x0196U: // LATIN CAPITAL LETTER IOTA
      if (ON_StringMapOrdinalType::LowerOrdinal == map_type)
        return 0x0269U;
      return unicode_code_point;
      break;
    case 0x0197U: // LATIN CAPITAL LETTER I WITH STROKE
      if (ON_StringMapOrdinalType::LowerOrdinal == map_type)
        return 0x0268U;
      return unicode_code_point;
      break;
    }

    // TODO

    return unicode_code_point;
  }



  if (unicode_code_point < 0x0370)
    return unicode_code_point;

  if (unicode_code_point <= 0x03FF)
  {
    // Greek and Coptic
    if (unicode_code_point >= 0x0391 && unicode_code_point <= 0x03A9)
    {
      // GREEK CAPITAL LETTER ALPHA ... OMEGA
      if ( 0x03A2 == unicode_code_point )
        return unicode_code_point; // RESERVED
      if ( ON_StringMapOrdinalType::LowerOrdinal == map_type)
        return unicode_code_point + 0x20;
      return unicode_code_point;
    }

    if (unicode_code_point >= 0x03B1 && unicode_code_point <= 0x03C9)
    {
      // GREEK SMALL LETTER ALPHA ... OMEGA
      if ( 0x03C2 == unicode_code_point )
        return unicode_code_point; // GREEK SMALL LETTER FINAL SIGMA (stigma)
      if ( ON_StringMapOrdinalType::MinimumOrdinal == map_type || ON_StringMapOrdinalType::UpperOrdinal == map_type )
        return unicode_code_point - 0x20;
      return unicode_code_point;
    }

    if (unicode_code_point <= 0x377U)
    {
      if ( 0x0374U ==unicode_code_point || 0x0375U ==unicode_code_point )
        return unicode_code_point;
      if (0 == (unicode_code_point % 2))
      {
        // GREEK CAPITAL LETTER
        if ( ON_StringMapOrdinalType::LowerOrdinal == map_type)
          return unicode_code_point+1;
      }
      else
      {
        // GREEK SMALL LETTER
        if ( ON_StringMapOrdinalType::MinimumOrdinal == map_type || ON_StringMapOrdinalType::UpperOrdinal == map_type )
          return unicode_code_point-1;
      }
      return unicode_code_point;
    }

    if (unicode_code_point <= 0x037DU)
    {
      if (ON_StringMapOrdinalType::UpperOrdinal == map_type && unicode_code_point >= 0x037BU )
        return unicode_code_point + (0x03FDU - 0x037BU);
      return unicode_code_point;
    }

    if (unicode_code_point == 0x037FU || unicode_code_point == 0x03F3U )
    {
      if ( unicode_code_point == 0x037FU && ON_StringMapOrdinalType::LowerOrdinal == map_type )
        return 0x03F3U;
      if ( unicode_code_point == 0x03F3U && ( ON_StringMapOrdinalType::MinimumOrdinal == map_type || ON_StringMapOrdinalType::UpperOrdinal == map_type ) )
        return 0x03F3U;
      return unicode_code_point;
    }

    return unicode_code_point;
  }

  if ( unicode_code_point < 0x0400 )
    return unicode_code_point;

  if ( unicode_code_point <= 0x04FFU )
  {
    // Cyrillic
    if ( unicode_code_point < 0x0410U )
      return unicode_code_point;

    if (unicode_code_point <= 0x042FU)
    {
      // 0x0410: CYRILLIC CAPITAL LETTER A
      // 0x042F: CYRILLIC CAPITAL LETTER YA
      if ( ON_StringMapOrdinalType::LowerOrdinal == map_type )
        return unicode_code_point + 0x20;
      return unicode_code_point;
    }

    if (unicode_code_point <= 0x044FU)
    {
      // 0x0430: CYRILLIC SMALL LETTER A -> CYRILLIC CAPITAL LETTER A
      // 0x044F: CYRILLIC SMALL LETTER YA -> CYRILLIC CAPITAL LETTER YA
      if ( ON_StringMapOrdinalType::MinimumOrdinal == map_type || ON_StringMapOrdinalType::UpperOrdinal == map_type )
        return unicode_code_point - 0x20;
      return unicode_code_point;
    }

    return unicode_code_point;
  }

  if (unicode_code_point < 0xD800)
  {
    // TODO - deal with other codepoint values < 0xD800
    //  That should be reduced for ordinal ignore case compares
    return unicode_code_point;
  }

  if (unicode_code_point < 0xFF00U)
  {
    // surrogate pairs use values from 0xD800U to 0xDFFF
    //   No ordinal ignore conversion applies to surrogate pair values.
    //
    // 0xE000 to 0xF8FF = unicode private use area
    //   No ordinal ignore conversion applies to private use area values.
  }

  if (unicode_code_point < 0xF900)
  {
    // 0xF900 to 0xFAFF = CJK Compatibility Ideographs
    // 0xFB00... = Alphabetic Presentation Forms
    // ...
    // 0xFE00... = Variation Selectors
    return unicode_code_point;
  }

  if (unicode_code_point <= 0xFFEFU)
  {
    // Halfwidth and Fullwidth Forms
    if ( unicode_code_point < 0xFF21 )
      return unicode_code_point;

    if (unicode_code_point <= 0xFF3A)
    {
      // 0xFF22: FULLWIDTH LATIN CAPITAL LETTER A
      // 0xFF3A: FULLWIDTH LATIN CAPITAL LETTER Z
      if (ON_StringMapOrdinalType::LowerOrdinal == map_type)
      {
        return unicode_code_point + 0x20;
      }
      return unicode_code_point;
    }

    if (unicode_code_point <= 0xFF41)
      return unicode_code_point;

    if (unicode_code_point <= 0xFF5A)
    {
      if (ON_StringMapOrdinalType::MinimumOrdinal == map_type || ON_StringMapOrdinalType::UpperOrdinal == map_type)
      {
        // 0xFF41: FULLWIDTH LATIN SMALL LETTER A -> FULLWIDTH LATIN CAPITAL LETTER A
        // 0xFF5A: FULLWIDTH LATIN SMALL LETTER Z -> FULLWIDTH LATIN CAPITAL LETTER Z
        return unicode_code_point - 0x20;
      }
      return unicode_code_point;
    }

    return unicode_code_point;
  }

  // 0x10000U: Linear B Syllabary
  // 0x10100U: Aegean Numbers
  // ...
  // 0x10FFFFU: maximum valid unicode code point

  return unicode_code_point;
}

ON__UINT32 ON_UnicodeMapCodePointOrdinal(
  ON_StringMapOrdinalType map_type,
  ON__UINT32 unicode_code_point
  )
{
  return MapCodePointOrdinal(unicode_code_point,0x10FFFFU,map_type);
}

ON__UINT32 ON_UnicodeMapCodePoint(
  const ON_Locale& locale,
  ON_StringMapType map_type,
  ON__UINT32 unicode_code_point
  )
{
  if (locale.IsOrdinalOrInvariantCulture())
    return ON_UnicodeMapCodePointOrdinal(ON_StringMapOrdinalTypeFromStringMapType(map_type), unicode_code_point);

  wchar_t w[7] = { 0 };
  wchar_t mapped_w[7] = { 0 };
  int w_count = ON_EncodeWideChar(unicode_code_point, 6,  w);
  if (w_count > 0)
  {
    int mapped_count = ON_wString::MapString(locale, map_type, w, w_count, mapped_w, sizeof(mapped_w) / sizeof(mapped_w[0]) - 1);
    if (mapped_count > 0)
    {
      ON__UINT32 mapped_unicode_code_point = unicode_code_point;
      ON_UnicodeErrorParameters e;
      if ( mapped_count == ON_DecodeWideChar(w,w_count,&e,&mapped_unicode_code_point) )
        return mapped_unicode_code_point;
    }
  }

  return unicode_code_point;
}

static unsigned int OrdinalUnsignedToIgnoreCase(
  unsigned int c,
  unsigned int maximum_singleton_value
  )
{
  // RH-41224
  // map A -> a, ..., Z -> z so underbar is before any "letter".
  // The preserves the behavior of Rhino component name sorting
  // that used "ancient" C runtime ASCII sorts.
  const ON_StringMapOrdinalType map_type
    = ( c <= 0x7A && c >= 0x41 && maximum_singleton_value >= 0x7A )
    ? ON_StringMapOrdinalType::LowerOrdinal
    : ON_StringMapOrdinalType::MinimumOrdinal;
  return MapCodePointOrdinal(c, maximum_singleton_value, map_type);
}

static unsigned int OrdinalUTF8ToIgnoreCase(
  char c
  )
{
  return OrdinalUnsignedToIgnoreCase((unsigned int)c,0x7FU);
}

static unsigned int OrdinalUTF16ToIgnoreCase(
  ON__UINT16 c
  )
{
  return OrdinalUnsignedToIgnoreCase(c,0xFFFFU);
}

static unsigned int OrdinalUTF32ToIgnoreCase(
  ON__UINT32 c
  )
{
  return OrdinalUnsignedToIgnoreCase(c,0xFFFFFFFFU);
}

#if ( 2 == ON_SIZEOF_WCHAR_T )

static unsigned int OrdinalWideCharToIgnoreCase(
  wchar_t c
  )
{
  return OrdinalUTF16ToIgnoreCase((ON__UINT16)c);
}
#elif ( 4 == ON_SIZEOF_WCHAR_T )


static unsigned int OrdinalWideCharToIgnoreCase(
  wchar_t c
  )
{
  return OrdinalUTF32ToIgnoreCase((ON__UINT32)c);
}
#endif


int ON_StringCompareOrdinalUTF8(
  const char* string1,
  int element_count1,
  const char* string2,
  int element_count2,
  bool bOrdinalIgnoreCase
  )
{
  STRING_COMPARE_PREAMBLE(char,ON_String::Length,string1,element_count1,string2,element_count2,0,-1,1);

  unsigned int c1, c2;
  int i;
  const int element_count
    = (element_count1 <= element_count2)
    ? element_count1
    : element_count2;

  if (bOrdinalIgnoreCase)
  {
    for (i = 0; i < element_count; i++)
    {
      c1 = OrdinalUTF8ToIgnoreCase(*string1++);
      c2 = OrdinalUTF8ToIgnoreCase(*string2++);
      if ( c1 < c2 )
        return -1;
      if ( c1 > c2 )
        return 1;
    }
  }
  else
  {
    for (i = 0; i < element_count; i++)
    {
      c1 = (unsigned char)(*string1++);
      c2 = (unsigned char)(*string2++);
      if ( c1 < c2 )
        return -1;
      if ( c1 > c2 )
        return 1;
    }
  }

  for (/*empty init*/; i < element_count1; i++)
  {
    if ( 0 != (*string1++))
      return 1;
  }

  for (/*empty init*/; i < element_count2; i++)
  {
    if ( 0 != (*string2++))
      return -1;
  }

  return 0;
}

int ON_StringCompareOrdinalUTF16(
  const ON__UINT16* string1,
  int element_count1,
  const ON__UINT16* string2,
  int element_count2,
  bool bOrdinalIgnoreCase
  )
{
  STRING_COMPARE_PREAMBLE(ON__UINT16,ON_StringLengthUTF16,string1,element_count1,string2,element_count2,0,-1,1);

  unsigned int c1, c2;
  int i;
  const int element_count
    = (element_count1 <= element_count2)
    ? element_count1
    : element_count2;

  if (bOrdinalIgnoreCase)
  {
    for (i = 0; i < element_count; i++)
    {
      c1 = OrdinalUTF16ToIgnoreCase(*string1++);
      c2 = OrdinalUTF16ToIgnoreCase(*string2++);
      if ( c1 < c2 )
        return -1;
      if ( c1 > c2 )
        return 1;
    }
  }
  else
  {
    for (i = 0; i < element_count; i++)
    {
      c1 = (*string1++);
      c2 = (*string2++);
      if ( c1 < c2 )
        return -1;
      if ( c1 > c2 )
        return 1;
    }
  }

  for (/*empty init*/; i < element_count1; i++)
  {
    if ( 0 != (*string1++))
      return 1;
  }

  for (/*empty init*/; i < element_count2; i++)
  {
    if ( 0 != (*string2++))
      return -1;
  }

  return 0;
}

int ON_StringCompareOrdinalUTF32(
  const ON__UINT32* string1,
  int element_count1,
  const ON__UINT32* string2,
  int element_count2,
  bool bOrdinalIgnoreCase
  )
{
  STRING_COMPARE_PREAMBLE(ON__UINT32,ON_StringLengthUTF32,string1,element_count1,string2,element_count2,0,-1,1);

  unsigned int c1, c2;
  int i;
  const int element_count
    = (element_count1 <= element_count2)
    ? element_count1
    : element_count2;

  if (bOrdinalIgnoreCase)
  {
    for (i = 0; i < element_count; i++)
    {
      c1 = OrdinalUTF32ToIgnoreCase(*string1++);
      c2 = OrdinalUTF32ToIgnoreCase(*string2++);
      if ( c1 < c2 )
        return -1;
      if ( c1 > c2 )
        return 1;
    }
  }
  else
  {
    for (i = 0; i < element_count; i++)
    {
      c1 = (*string1++);
      c2 = (*string2++);
      if ( c1 < c2 )
        return -1;
      if ( c1 > c2 )
        return 1;
    }
  }

  for (/*empty init*/; i < element_count1; i++)
  {
    if ( 0 != (*string1++))
      return 1;
  }

  for (/*empty init*/; i < element_count2; i++)
  {
    if ( 0 != (*string2++))
      return -1;
  }

  return 0;
}

int ON_StringCompareOrdinalWideChar(
  const wchar_t* string1,
  int element_count1,
  const wchar_t* string2,
  int element_count2,
  bool bOrdinalIgnoreCase
  )
{
#if (1 == ON_SIZEOF_WCHAR_T)
    return ON_StringCompareOrdinalUTF8((const char*)string1, element_count1, (const char*)string2, element_count2, bOrdinalIgnoreCase);
#elif (2 == ON_SIZEOF_WCHAR_T)
  return ON_StringCompareOrdinalUTF16((const ON__UINT16*)string1, element_count1, (const ON__UINT16*)string2, element_count2, bOrdinalIgnoreCase);
#elif (4 == ON_SIZEOF_WCHAR_T)
  return ON_StringCompareOrdinalUTF32((const ON__UINT32*)string1, element_count1, (const ON__UINT32*)string2, element_count2, bOrdinalIgnoreCase);
#else
#error ON_SIZEOF_WCHAR_T is not defined or has an unexpected value
#endif
}

#define ON_UTF8_PATH_SEPARATOR '/'
static char ON_NormalizeUTF8PathSepartor(
  char c
  )
{
  return ((c == '/') || (c == '\\')) ? ON_UTF8_PATH_SEPARATOR : c;
}

#define ON_WCHAR_PATH_SEPARATOR ((wchar_t)ON_UTF8_PATH_SEPARATOR)
static wchar_t ON_NormalizeWideCharPathSepartor(
  wchar_t c
  )
{
  return ((c == ((wchar_t)'/')) || (c == ((wchar_t)'\\'))) ? ON_WCHAR_PATH_SEPARATOR : c;
}

bool ON_FileSystemPath::PlatformPathIgnoreCase()
{
  // 2015-June-15 Dale Lear
  //   The Windows file system ignores case.
  //
  //   Default OS X 10.10.3 installs ignore case - even the "UNIX" shell.
  //   User's can customize this setting.
  //
  //   For other OS's, devs can customize this code as they see fit.
  return true;
}

int ON_String::ComparePath(
  const char* other_path
  ) const
{
  return ON_String::ComparePath(m_s,-1,other_path,-1);
}

int ON_String::ComparePath(
  const char* path1,
  const char* path2
  )
{
  return ON_String::ComparePath(path1,-1,path2,-1);
}

int ON_String::ComparePath(
  const char* path1,
  int element_count1,
  const char* path2,
  int element_count2
  )
{
  CHAR_STRING_COMPARE_PREAMBLE(path1,element_count1,path2,element_count2);

  const bool bOrdinalIgnoreCase = ON_FileSystemPath::PlatformPathIgnoreCase();

  const char* b1 = path1;
  const char* b2 = path2;

  for(;;)
  {
    int count1 = 0;
    int count2 = 0;
    const char* a1 = b1;
    const char* a2 = b2;
    char c1, c2;
    for (;;)
    {
      if ((int)(b1 - path1) < element_count1)
      {
        c1 = ON_NormalizeUTF8PathSepartor(*b1++);
        if (null_terminator == c1 || ON_UTF8_PATH_SEPARATOR == c1)
          break;
      }
      else
      {
        c1 = null_terminator;
        break;
      }
      count1++;
    }

    for (;;)
    {
      if ((int)(b2 - path2) < element_count2)
      {
        c2 = ON_NormalizeUTF8PathSepartor(*b2++);
        if (null_terminator == c2 || ON_UTF8_PATH_SEPARATOR == c2)
          break;
      }
      else
      {
        c2 = null_terminator;
        break;
      }
      count2++;
    }

    if (count1 > 0 || count2 > 0)
    {
      // TODO
      //  At this point, we should apply a compare that uses the same UTF-8 string normalization
      //  as the file system on the current operating system.
      int rc = ON_StringCompareOrdinalUTF8(a1, count1, a2, count2, bOrdinalIgnoreCase);
      if (0 != rc)
        return rc;
    }

    if (null_terminator == c1 || null_terminator == c2)
    {
      if ( null_terminator != c2 )
        return -1;
      if ( null_terminator != c1 )
        return 1;
      return 0;
    }
  }
}

bool ON_String::EqualPath(
  const char* other_path
  ) const
{
  return ON_String::EqualPath(m_s,-1,other_path,-1);
}

bool ON_String::EqualPath(
  const char* path1,
  const char* path2
  )
{
  return ON_String::EqualPath(path1,-1,path2,-1);
}

bool ON_String::EqualPath(
  const char* path1,
  int element_count1,
  const char* path2,
  int element_count2
  )
{
  CHAR_STRING_EQUAL_PREAMBLE(path1,element_count1,path2,element_count2);

  unsigned int c1=0, c2=0;
  const int element_count
    = (element_count1 <= element_count2)
    ? element_count1
    : element_count2;
  int i;
  const bool bOrdinalIgnoreCase = ON_FileSystemPath::PlatformPathIgnoreCase();

  if (bOrdinalIgnoreCase)
  {
    for(i=0; i < element_count; i++)
    {
      c1 = ON_NormalizeUTF8PathSepartor((char)OrdinalUTF8ToIgnoreCase(*path1++));
      c2 = ON_NormalizeUTF8PathSepartor((char)OrdinalUTF8ToIgnoreCase(*path2++));
      if ( c1 != c2 )
        return false;
    }
  }
  else
  {
    for(i=0; i < element_count; i++)
    {
      c1 = ON_NormalizeUTF8PathSepartor(*path1++);
      c2 = ON_NormalizeUTF8PathSepartor(*path2++);
      if ( c1 != c2 )
        return false;
    }
  }

  for (/*empty init*/; i < element_count1; i++)
  {
    if ( 0 != (*path1++))
      return false;
  }

  for (/*empty init*/; i < element_count2; i++)
  {
    if ( 0 != (*path2++))
      return false;
  }

  return true;
}


int ON_wString::ComparePath(
  const wchar_t* other_path
  ) const
{
  return ON_wString::ComparePath(m_s,-1,other_path,-1);
}

int ON_wString::ComparePath(
  const wchar_t* sPath1,
  const wchar_t* sPath2
  )
{
  return ON_wString::ComparePath(sPath1,-1,sPath2,-1);
}

int ON_wString::ComparePath(
  const wchar_t* path1,
  int element_count1,
  const wchar_t* path2,
  int element_count2
  )
{
  WIDE_STRING_COMPARE_PREAMBLE(path1,element_count1,path2,element_count2);

  const bool bOrdinalIgnoreCase = ON_FileSystemPath::PlatformPathIgnoreCase();

  const wchar_t* b1 = path1;
  const wchar_t* b2 = path2;

  for(;;)
  {
    int count1 = 0;
    int count2 = 0;
    const wchar_t* a1 = b1;
    const wchar_t* a2 = b2;
    wchar_t c1, c2;
    for (;;)
    {
      if ((int)(b1 - path1) < element_count1)
      {
        c1 = ON_NormalizeWideCharPathSepartor(*b1++);
        if (null_terminator == c1 || ON_WCHAR_PATH_SEPARATOR == c1)
          break;
      }
      else
      {
        c1 = null_terminator;
        break;
      }
      count1++;
    }

    for (;;)
    {
      if ((int)(b2 - path2) < element_count2)
      {
        c2 = ON_NormalizeWideCharPathSepartor(*b2++);
        if (null_terminator == c2 || ON_WCHAR_PATH_SEPARATOR == c2)
          break;
      }
      else
      {
        c2 = null_terminator;
        break;
      }
      count2++;
    }

    if (count1 > 0 || count2 > 0)
    {
      // TODO
      //  At this point, we should apply a compare that uses the same UTF-8 string normalization
      //  as the file system on the current operating system.
      int rc = ON_StringCompareOrdinalWideChar(a1, count1, a2, count2, bOrdinalIgnoreCase);
      if (0 != rc)
        return rc;
      if (count1 < count2)
        return -1;
      if (count2 < count1)
        return 1;
    }

    if (null_terminator == c1 || null_terminator == c2)
    {
      if ( null_terminator != c2 )
        return -1;
      if ( null_terminator != c1 )
        return 1;
      return 0;
    }
  }
}

bool ON_wString::EqualPath(
  const wchar_t* other_path
  ) const
{
  return ON_wString::EqualPath(m_s,-1,other_path,-1);
}

bool ON_wString::EqualPath(
  const wchar_t* path1,
  const wchar_t* path2
  )
{
  return ON_wString::EqualPath(path1,-1,path2,-1);
}

bool ON_wString::EqualPath(
  const wchar_t* path1,
  int element_count1,
  const wchar_t* path2,
  int element_count2
  )
{
  WIDE_STRING_EQUAL_PREAMBLE(path1,element_count1,path2,element_count2);

  unsigned int c1=0, c2=0;
  const int element_count
    = (element_count1 <= element_count2)
    ? element_count1
    : element_count2;
  int i;
  const bool bOrdinalIgnoreCase = ON_FileSystemPath::PlatformPathIgnoreCase();

  if (bOrdinalIgnoreCase)
  {
    for(i=0; i < element_count; i++)
    {
      c1 = ON_NormalizeWideCharPathSepartor((wchar_t)OrdinalWideCharToIgnoreCase(*path1++));
      c2 = ON_NormalizeWideCharPathSepartor((wchar_t)OrdinalWideCharToIgnoreCase(*path2++));
      if ( c1 != c2 )
        return false;
    }
  }
  else
  {
    for(i=0; i < element_count; i++)
    {
      c1 = ON_NormalizeWideCharPathSepartor(*path1++);
      c2 = ON_NormalizeWideCharPathSepartor(*path2++);
      if ( c1 != c2 )
        return false;
    }
  }

  for (/*empty init*/; i < element_count1; i++)
  {
    if ( 0 != (*path1++))
      return false;
  }

  for (/*empty init*/; i < element_count2; i++)
  {
    if ( 0 != (*path2++))
      return false;
  }

  return true;
}


int ON_String::CompareAttributeName(
  const char* other_name
  ) const
{
  const char* name1 = static_cast< const char* >(*this);
  return ON_String::CompareAttributeName(name1, other_name );
}

int ON_String::CompareAttributeName(
  const char* name1,
  const char* name2
  )
{
  // TODO - normalize and then use a culture aware ignore case test
  return ON_String::CompareOrdinal(name1, -1, name2, -1, true);
}

int ON_wString::CompareAttributeName(
  const wchar_t* other_name
  ) const
{
  const wchar_t* name1 = static_cast< const wchar_t* >(*this);
  return ON_wString::CompareAttributeName(name1, other_name );
}

static unsigned int Internal_NameAttributeWideCharRank(
  wchar_t c,
  bool bIgnoreCase
)
{
  // Attribute names have ASCII symbols sorted this way

  // rank symbol
  //  1   (space)
  //  2 ! (exclamation point)
  //  3 " (double quote)
  //  4 # (hash)
  //  5 $ (dollar)
  //  6 % (percent)
  //  7 & (ampersand)
  //  8 ( (left paren)
  //  9 ) (right paren)
  // 10 * (asterisk)
  // 11 , (comma)
  // 12 . (period)
  // 13 / (slash)
  // 14 : (colon)
  // 15 ; (semicolon)
  // 16 ? (question mark)
  // 17 @ (at)
  // 18 [ (left bracket)
  // 19 \ (back slash)
  // 20 ] (right bracket)
  // 21 ^ (carrot)
  // 22 _ (underscore)
  // 23 ` (back tick)
  // 24 { (left brace)
  // 25 | (pipe)
  // 26 } (right brace)
  // 27 ~ (tilde)
  // 28 + (plus)
  // 29 < (less than)
  // 30 = (equal)
  // 31 > (greater than)
  // 32 0
  // 33 1
  // 34 2
  // 35 3
  // 36 4
  // 37 5
  // 38 6
  // 39 7
  // 40 8
  // 41 9
  // 42 ' (apostrophe)
  // 43 - (hyphen)
  // 44 A
  // 45 B
  // 46 C
  // ...
  // 69 Z
  // 70 a
  // ...
  // 95 z


  unsigned int code_point = (unsigned int)c;
  if (0 == code_point)
    return 0;

  if (code_point < 0x20 || code_point >= 0x7F)
    return ON_UNSET_UINT_INDEX; // no rank - sort some other way

  // 0 to 9
  if (code_point >= 0x30 && code_point <= 0x39)
    return (code_point - 0x30 + 32);

  // upper case A to Z
  if (code_point >= 0x41 && code_point <= 0x5A)
    return (code_point - 0x41 + 44);

  // lower case a to z
  if (code_point >= 0x61 && code_point <= 0x7A)
    return bIgnoreCase ? (code_point - 0x61 + 44) : (code_point - 0x61 + 70);

  unsigned int rank;
  switch (code_point)
  {
  case 0x20: //  1   (space)
    rank = 1;
    break;
  case 0x21: //  2 ! (exclamation point)
    rank = 2;
    break;
  case 0x22: //  3 " (double quote)
    rank = 3;
    break;
  case 0x23: //  4 # (hash)
    rank = 4;
    break;
  case 0x24: //  5 $ (dollar)
    rank = 5;
    break;
  case 0x25: //  6 % (percent)
    rank = 6;
    break;
  case 0x26: //  7 & (ampersand)
    rank = 7;
    break;
  case 0x28: //  8 ( (left paren)
    rank = 8;
    break;
  case 0x29: //  9 ) (right paren)
    rank = 9;
    break;
  case 0x2A: // 10 * (asterisk)
    rank = 10;
    break;
  case 0x2C: // 11 , (comma)
    rank = 11;
    break;
  case 0x2E: // 12 . (period)
    rank = 12;
    break;
  case 0x2F: // 13 / (slash)
    rank = 13;
    break;
  case 0x3A: // 14 : (colon)
    rank = 14;
    break;
  case 0x3B: // 15 ; (semicolon)
    rank = 15;
    break;
  case 0x3F: // 16 ? (question mark)
    rank = 16;
    break;
  case 0x40: // 17 @ (at)
    rank = 17;
    break;
  case 0x5B: // 18 [ (left bracket)
    rank = 18;
    break;
  case 0x5C: // 19 \ (back slash)
    rank = 19;
    break;
  case 0x5D: // 20 ] (right bracket)
    rank = 20;
    break;
  case 0x5E: // 21 ^ (carrot)
    rank = 21;
    break;
  case 0x5F: // 22 _ (underscore)
    rank = 22;
    break;
  case 0x60: // 23 ` (back tick)
    rank = 23;
    break;
  case 0x7B: // 24 { (left brace)
    rank = 24;
    break;
  case 0x7C: // 25 | (pipe)
    rank = 25;
    break;
  case 0x7D: // 26 } (right brace)
    rank = 26;
    break;
  case 0x7E: // 27 ~ (tilde)
    rank = 27;
    break;
  case 0x2B: // 28 + (plus)
    rank = 28;
    break;
  case 0x3C: // 29 < (less than)
    rank = 29;
    break;
  case 0x3D: // 30 = (equal)
    rank = 30;
    break;
  case 0x3E: // 31 > (greater than)
    rank = 31;
    break;

  // 32 to 41 numerals 0 to 9 handled before this switch

  case 0x27: // 42 ' (apostrophe)
    rank = 42;
    break;
  case 0x2D: // 43 - (hyphen)
    rank = 43;
    break;

  // 43 to 69 upper case A to Z handled before this switch

  // 43 to 69 lower case z to z handled before this switch

  default: // no rank - sort some other way
    rank = ON_UNSET_UINT_INDEX;
    break;
  }

  return rank;
}

int ON_wString::CompareAttributeName(
  const wchar_t* name1,
  const wchar_t* name2
  )
{
  if (name1 == name2)
    return 0;

  const bool bIgnoreCase = true;

  if ( nullptr != name1 && nullptr != name2 )
  {
    // Sort leading underbar before 'A'
    // https://mcneel.myjetbrains.com/youtrack/issue/RH-41224

    unsigned int rank1 = Internal_NameAttributeWideCharRank(*name1,bIgnoreCase);
    unsigned int rank2 = Internal_NameAttributeWideCharRank(*name2,bIgnoreCase);
    while (rank1 == rank2 && ON_UNSET_UINT_INDEX != rank1 && 0 != rank1)
    {
      name1++;
      name2++;
      rank1 = Internal_NameAttributeWideCharRank(*name1,bIgnoreCase);
      rank2 = Internal_NameAttributeWideCharRank(*name2,bIgnoreCase);
    }

    if (ON_UNSET_UINT_INDEX != rank1 || ON_UNSET_UINT_INDEX != rank2)
    {
      if (rank1 < rank2)
        return -1;
      if (rank1 > rank2)
        return 1;
      if (0 == rank1)
        return 0;
    }
  }

  // name1 or name2 is nullptr or begins with an unranked code point.
  return ON_wString::CompareOrdinal(name1, -1, name2, -1, bIgnoreCase);
}

bool ON_String::EqualAttributeName(
  const char* other_name
  ) const
{
  const char* name1 = static_cast< const char* >(*this);
  return ON_String::EqualAttributeName(name1, other_name );
}

bool ON_String::EqualAttributeName(
  const char* name1,
  const char* name2
  )
{
  // TODO - normalize and then use a culture aware ignore case test
  return ON_String::EqualOrdinal(name1, -1, name2, -1, true);
}

bool ON_wString::EqualAttributeName(
  const wchar_t* other_name
  ) const
{
  const wchar_t* name1 = static_cast< const wchar_t* >(*this);
  return ON_wString::EqualAttributeName(name1, other_name );
}

bool ON_wString::EqualAttributeName(
  const wchar_t* name1,
  const wchar_t* name2
  )
{
  // TODO - normalize and then use a culture aware ignore case test
  return ON_wString::EqualOrdinal(name1, -1, name2, -1, true);
}

int ON_String::Compare( const char* s ) const
{
  return CompareOrdinal(s,false);
}

int ON_String::Compare( const unsigned char* s) const
{
  return CompareOrdinal((const char*)s,false);
}

int ON_String::CompareNoCase( const char* s) const
{
  return CompareOrdinal(s,true);
}

int ON_String::CompareNoCase( const unsigned char* s) const
{
  return CompareOrdinal((const char*)s,true);
}

bool ON_String::Equal(
  const ON_String& other_string,
  const class ON_Locale& locale,
  bool bIgnoreCase
  ) const
{
  return ON_String::Equal(
    static_cast<const char*>(*this),
    this->Length(),
    static_cast<const char*>(other_string),
    other_string.Length(),
    locale,
    bIgnoreCase );
}

bool ON_String::Equal(
  const char* other_string,
  const class ON_Locale& locale,
  bool bIgnoreCase
  ) const
{
  return ON_String::Equal(
    static_cast<const char*>(*this),
    this->Length(),
    other_string,
    -1,
    locale,
    bIgnoreCase );
}

bool ON_String::Equal(
  const char* string1,
  const char* string2,
  const class ON_Locale& locale,
  bool bIgnoreCase
  )
{
  return ON_String::Equal( string1, -1, string2, -1, locale, bIgnoreCase );
}

bool ON_String::Equal(
  const char* string1,
  int element_count1,
  const char* string2,
  int element_count2,
  const class ON_Locale& locale,
  bool bIgnoreCase
  )
{
  if (locale.IsOrdinal())
    return ON_String::EqualOrdinal(string1,element_count1,string2,element_count2,bIgnoreCase);

#if defined(ON_RUNTIME_WIN)
  // TODO - replace with locale aware test
  return ON_String::EqualOrdinal(string1,element_count1,string2,element_count2,bIgnoreCase);
#elif defined(ON_RUNTIME_APPLE)
  // TODO - replace with locale aware test
  return ON_String::EqualOrdinal(string1,element_count1,string2,element_count2,bIgnoreCase);
#else
  // TODO - replace with locale aware test
  return ON_String::EqualOrdinal(string1,element_count1,string2,element_count2,bIgnoreCase);
#endif

}



int ON_String::Compare(
  const ON_String& other_string,
  const class ON_Locale& locale,
  bool bIgnoreCase
  ) const
{
  return ON_String::Compare(
    static_cast< const char* >(*this),
    this->Length(),
    static_cast< const char* >(other_string),
    other_string.Length(),
    locale,
    bIgnoreCase
    );
}


int ON_String::Compare(
  const char* other_string,
  const class ON_Locale& locale,
  bool bIgnoreCase
  ) const
{
  return ON_String::Compare(
    static_cast< const char* >(*this),
    this->Length(),
    other_string,
    -1,
    locale,
    bIgnoreCase
    );
}

int ON_String::Compare(
  const char* string1,
  const char* string2,
  const class ON_Locale& locale,
  bool bIgnoreCase
  )
{
  return ON_String::Compare( string1, -1, string2, -1, locale, bIgnoreCase );
}

int ON_String::Compare(
  const char* string1,
  int element_count1,
  const char* string2,
  int element_count2,
  const class ON_Locale& locale,
  bool bIgnoreCase
  )
{

 #if defined(ON_RUNTIME_WIN)
  // TODO
  //  Actually do an invariant culture compare
  //  This involves NFC normalization and then using the correct CE to compare values.
  //
  return ON_String::CompareOrdinal( string1, -1, string2, -1, bIgnoreCase );
  //int n = (element_count1 <= element_count2) ? element_count1 : element_count2;
  //int rc
  //  = bIgnoreCase
  //  ? _strnicmp_l(string1, string2, (size_t)n, locale.StringCollateAndMapLocalePtr())
  //  : _strncmp_l(string1, string2, n, locale.StringCollateAndMapLocalePtr());
  //if (0 == rc)
  //{
  //  if ( n < element_count1 )
  //    rc = ON_String::CompareOrdinal(string1+n,element_count1-n,"",0,bIgnoreCase);
  //  else if ( n < element_count2 )
  //    rc = ON_String::CompareOrdinal("", 0, string2+n, element_count2-n, bIgnoreCase);
  //}
  //return rc;
#elif defined(ON_RUNTIME_APPLE)
  // TODO
  //  Actually do an invariant culture compare
  //  This involves NFC normalization and then using the correct CE to compare values.
  //
  return ON_String::CompareOrdinal( string1, -1, string2, -1, bIgnoreCase );

  //int n = (element_count1 <= element_count2) ? element_count1 : element_count2;
  //int rc
  //  = bIgnoreCase
  //  ? strncasecmp_l(string1, string2, n, locale.StringCollateAndMapLocalePtr())
  //  : strncmp_l(string1, string2, n, locale.StringCollateAndMapLocalePtr());
  //if (0 == rc)
  //{
  //  if ( n < element_count1 )
  //    rc = ON_String::CompareOrdinal(string1+n,element_count1-n,"",0,bIgnoreCase);
  //  else if ( n < element_count2 )
  //    rc = ON_String::CompareOrdinal("", 0, string2+n, element_count2-n, bIgnoreCase);
  //}
  //return rc;
#else
  return ON_String::CompareOrdinal( string1, -1, string2, -1, bIgnoreCase );
#endif
}

bool ON_wString::Equal(
  const ON_wString& other_string,
  const class ON_Locale& locale,
  bool bIgnoreCase
  ) const
{
  return ON_wString::Equal(
    static_cast< const wchar_t* >(*this),
    this->Length(),
    static_cast< const wchar_t* >(other_string),
    other_string.Length(),
    locale,
    bIgnoreCase
    );
}

bool ON_wString::Equal(
  const wchar_t* other_string,
  const class ON_Locale& locale,
  bool bIgnoreCase
  ) const
{
  return ON_wString::Equal(
    static_cast< const wchar_t* >(*this),
    this->Length(),
    other_string,
    -1,
    locale,
    bIgnoreCase
    );
}

bool ON_wString::Equal(
  const wchar_t* string1,
  const wchar_t* string2,
  const class ON_Locale& locale,
  bool bIgnoreCase
  )
{
  return ON_wString::Equal(string1,-1,string2,-1,locale,bIgnoreCase);
}

bool ON_wString::Equal(
  const wchar_t* string1,
  int element_count1,
  const wchar_t* string2,
  int element_count2,
  const class ON_Locale& locale,
  bool bIgnoreCase
  )
{
  if ( locale.IsOrdinal() )
    return ON_wString::EqualOrdinal(string1, element_count1, string2, element_count2, bIgnoreCase );

#if defined(ON_RUNTIME_WIN)
  return (0 == ON_wString::Compare(string1, element_count1, string2, element_count2, locale, bIgnoreCase ));
#elif defined(ON_RUNTIME_APPLE)
  return (0 == ON_wString::Compare(string1, element_count1, string2, element_count2, locale, bIgnoreCase ));
#else
  return ON_wString::EqualOrdinal(string1, element_count1, string2, element_count2, bIgnoreCase );
#endif
}

int ON_wString::Compare(
  const ON_wString& other_string,
  const class ON_Locale& locale,
  bool bIgnoreCase
  ) const
{
  return ON_wString::Compare(
    static_cast< const wchar_t* >(*this),
    this->Length(),
    static_cast< const wchar_t* >(other_string),
    other_string.Length(),
    locale,
    bIgnoreCase
    );
}

int ON_wString::Compare(
  const wchar_t* other_string,
  const class ON_Locale& locale,
  bool bIgnoreCase
  ) const
{
  return ON_wString::Compare(
    static_cast< const wchar_t* >(*this),
    this->Length(),
    other_string,
    -1,
    locale,
    bIgnoreCase
    );
}

int ON_wString::Compare(
  const wchar_t* string1,
  const wchar_t* string2,
  const class ON_Locale& locale,
  bool bIgnoreCase
  )
{
  return ON_wString::Compare( string1, -1, string2, -1, locale, bIgnoreCase );
}

int ON_wString::Compare(
  const wchar_t* string1,
  int element_count1,
  const wchar_t* string2,
  int element_count2,
  const class ON_Locale& locale,
  bool bIgnoreCase
  )
{
  WIDE_STRING_COMPARE_PREAMBLE(string1, element_count1, string2, element_count2);

  if ( locale.IsOrdinal() )
    return ON_wString::CompareOrdinal(string1,element_count1,string2,element_count2,bIgnoreCase);

#if defined(ON_RUNTIME_WIN)
  const bool bIsIsInvariantCulture = locale.IsInvariantCulture();
  wchar_t buffer[ON_Locale::BUFFER_MAXIMUM_CAPACITY];
  const wchar_t* locale_name
    = bIsIsInvariantCulture
    ? LOCALE_NAME_INVARIANT
    : locale.GetWindowsLocaleName(buffer,sizeof(buffer)/sizeof(buffer[0]));

  const DWORD flags = ( bIgnoreCase )
    ? ((bIsIsInvariantCulture) ? NORM_IGNORECASE : LINGUISTIC_IGNORECASE)
    : 0;

  int rc = ::CompareStringEx(
    locale_name,
    flags,
    string1,
    element_count1,
    string2,
    element_count2,
    nullptr,
    nullptr,
    0);

  if (rc == CSTR_LESS_THAN)
    return -1;
  if (rc == CSTR_EQUAL)
    return 0;
  if (rc == CSTR_GREATER_THAN)
    return 1;


#elif defined(ON_RUNTIME_APPLE)

  // I need a tool that is similar to
  //
  //  wcscoll_l(const wchar_t*, const wchar_t*, locale_t )
  //
  // but it needs to take a count (n) and I need one that ignores case.
  //
  // It appears wcsncasecmp_l() does use locale to map case, but then does an ordinal compare.
  //
  //
  //int n = (element_count1 <= element_count2) ? element_count1 : element_count2;
  //int rc
  //  = bIgnoreCase
  //  ? wcsncasecmp_l(string1, string2, (size_t)n, locale.StringCollateAndMapLocalePtr())
  //  : wcsncmp(string1, string2, (size_t)n);
  //if (0 == rc)
  //{
  //  if ( n < element_count1 )
  //    rc = ON_wString::CompareOrdinal(string1+n,element_count1-n,L"",0,bIgnoreCase);
  //  else if ( n < element_count2 )
  //    rc = ON_wString::CompareOrdinal(L"", 0, string2+n, element_count2-n, bIgnoreCase);
  //}
  //return rc;

  return ON_wString::CompareOrdinal(string1,element_count1,string2,element_count2,bIgnoreCase);

#else

#endif

  return ON_wString::CompareOrdinal(string1,element_count1,string2,element_count2,bIgnoreCase);
}

///////////////////////////////////////////////////////////////////////////////
//
// ON_String operator ==, !=, <, >, <=, >=
//

bool operator==( const ON_String& lhs, const ON_String& rhs )
{
  const int length = lhs.Length();
  return
    (length == rhs.Length())
    &&  ON_String::EqualOrdinal(
    static_cast<const char*>(lhs),
    length,
    static_cast<const char*>(rhs),
    length,
    false
    );
}

bool operator==( const ON_String& lhs, const char* rhs )
{
  const int length = lhs.Length();

  return (length == ON_String::Length(rhs))
    && ON_String::EqualOrdinal(
    static_cast<const char*>(lhs),
    length,
    rhs,
    length,
    false
    );
}

bool operator==( const char* lhs, const ON_String& rhs )
{
  const int length = rhs.Length();

  return (length == ON_String::Length(lhs))
    && ON_String::EqualOrdinal(
    lhs,
    length,
    static_cast<const char*>(rhs),
    length,
    false
    );
}

bool operator!=(const ON_String& lhs, const ON_String& rhs)
{
  return !(lhs == rhs);
}

bool operator!=(const ON_String& lhs, const char* rhs)
{
  return !(lhs == rhs);
}

bool operator!=(const char* lhs, const ON_String& rhs)
{
  return !(lhs == rhs);
}

bool operator<( const ON_String& lhs, const ON_String& rhs )
{
  const int rc = ON_String::CompareOrdinal(
    static_cast<const char*>(lhs),
    lhs.Length(),
    static_cast<const char*>(rhs),
    rhs.Length(),
    false
    );
  return (rc < 0);
}

bool operator<( const ON_String& lhs, const char* rhs )
{
  const int rc = ON_String::CompareOrdinal(
    static_cast<const char*>(lhs),
    lhs.Length(),
    rhs,
    -1,
    false
    );
  return (rc < 0);
}

bool operator<( const char* lhs, const ON_String& rhs )
{
  const int rc = ON_String::CompareOrdinal(
    lhs,
    -1,
    static_cast<const char*>(rhs),
    rhs.Length(),
    false
    );
  return (rc < 0);
}

bool operator>( const ON_String& lhs, const ON_String& rhs )
{
  return operator<(rhs,lhs);
}

bool operator>( const ON_String& lhs, const char* rhs )
{
  return operator<(rhs,lhs);
}

bool operator>( const char* lhs, const ON_String& rhs )
{
  return operator<(rhs,lhs);
}

bool operator<=( const ON_String& lhs, const ON_String& rhs )
{
  return !operator<(rhs,lhs);
}

bool operator<=( const ON_String& lhs, const char* rhs )
{
  return !operator<(rhs,lhs);
}

bool operator<=( const char* lhs, const ON_String& rhs )
{
  return !operator<(rhs,lhs);
}

bool operator>=( const ON_String& lhs, const ON_String& rhs )
{
  return !operator<(lhs,rhs);
}

bool operator>=( const ON_String& lhs, const char* rhs )
{
  return !operator<(lhs,rhs);
}

bool operator>=( const char* lhs, const ON_String& rhs )
{
  return !operator<(lhs,rhs);
}


///////////////////////////////////////////////////////////////////////////////
//
// ON_wString operator ==, !=, <, >, <=, >=
//

bool operator==( const ON_wString& lhs, const ON_wString& rhs )
{
  const int length = lhs.Length();
  return   (length == rhs.Length())
    && ON_wString::EqualOrdinal(
    static_cast<const wchar_t*>(lhs),
    length,
    static_cast<const wchar_t*>(rhs),
    length,
    false
    );
}

bool operator==( const ON_wString& lhs, const wchar_t* rhs )
{
  const int length = lhs.Length();
  return (length == ON_wString::Length(rhs))
    && ON_wString::EqualOrdinal(
    static_cast<const wchar_t*>(lhs),
    length,
    rhs,
    length,
    false
    );
}

bool operator==( const wchar_t* lhs, const ON_wString& rhs )
{
  const int length = rhs.Length();
  return (length == ON_wString::Length(lhs))
    && ON_wString::EqualOrdinal(
    lhs,
    length,
    static_cast<const wchar_t*>(rhs),
    length,
    false
    );
}

bool operator!=(const ON_wString& lhs, const ON_wString& rhs)
{
  return !(lhs == rhs);
}

bool operator!=(const ON_wString& lhs, const wchar_t* rhs)
{
  return !(lhs == rhs);
}

bool operator!=(const wchar_t* lhs, const ON_wString& rhs)
{
  return !(lhs == rhs);
}

bool operator<( const ON_wString& lhs, const ON_wString& rhs )
{
  const int rc = ON_wString::CompareOrdinal(
    static_cast<const wchar_t*>(lhs),
    lhs.Length(),
    static_cast<const wchar_t*>(rhs),
    rhs.Length(),
    false
    );
  return (rc < 0);
}

bool operator<( const ON_wString& lhs, const wchar_t* rhs )
{
  const int rc = ON_wString::CompareOrdinal(
    static_cast<const wchar_t*>(lhs),
    lhs.Length(),
    rhs,
    -1,
    false
    );
  return (rc < 0);
}

bool operator<( const wchar_t* lhs, const ON_wString& rhs )
{
  const int rc = ON_wString::CompareOrdinal(
    lhs,
    -1,
    static_cast<const wchar_t*>(rhs),
    rhs.Length(),
    false
    );
  return (rc < 0);
}

bool operator>( const ON_wString& lhs, const ON_wString& rhs )
{
  return operator<(rhs,lhs);
}

bool operator>( const ON_wString& lhs, const wchar_t* rhs )
{
  return operator<(rhs,lhs);
}

bool operator>( const wchar_t* lhs, const ON_wString& rhs )
{
  return operator<(rhs,lhs);
}

bool operator<=( const ON_wString& lhs, const ON_wString& rhs )
{
  return !operator<(rhs,lhs);
}

bool operator<=( const ON_wString& lhs, const wchar_t* rhs )
{
  return !operator<(rhs,lhs);
}

bool operator<=( const wchar_t* lhs, const ON_wString& rhs )
{
  return !operator<(rhs,lhs);
}

bool operator>=( const ON_wString& lhs, const ON_wString& rhs )
{
  return !operator<(lhs,rhs);
}

bool operator>=( const ON_wString& lhs, const wchar_t* rhs )
{
  return !operator<(lhs,rhs);
}

bool operator>=( const wchar_t* lhs, const ON_wString& rhs )
{
  return !operator<(lhs,rhs);
}

///////////////////////////////////////////////////////////////////////////////
//
// ON_String::EqualOrdinal
//

bool ON_String::EqualOrdinal(
  const ON_String& other_string,
  bool bOrdinalIgnoreCase
  ) const
{
  const int length = Length();
  return
    (length == other_string.Length())
    && ON_String::EqualOrdinal(
    static_cast< const char* >(*this),
    length,
    static_cast< const char* >(other_string),
    length,
    bOrdinalIgnoreCase
    );
}

bool ON_String::EqualOrdinal(
  const char* other_string,
  bool bOrdinalIgnoreCase
  ) const
{
  const int length = Length();
  return (length == ON_String::Length(other_string))
    && ON_String::EqualOrdinal(
    static_cast< const char* >(*this),
    length,
    other_string,
    length,
    bOrdinalIgnoreCase
    );
}

bool ON_String::EqualOrdinal(
  const char* string1,
  const char* string2,
  bool bOrdinalIgnoreCase
  )
{
  return ON_String::EqualOrdinal(string1,-1,string2,-1,bOrdinalIgnoreCase);
}

bool ON_String::EqualOrdinal(
  const char* string1,
  int element_count1,
  const char* string2,
  int element_count2,
  bool bOrdinalIgnoreCase
  )
{
  CHAR_STRING_EQUAL_PREAMBLE(string1,element_count1,string2,element_count2);

  const int element_count = (element_count1 <= element_count2) ? element_count1 : element_count2;
  int i;
  if (bOrdinalIgnoreCase)
  {
    unsigned int c1, c2;
    for(i = 0; i < element_count; i++)
    {
      c1 = OrdinalUTF8ToIgnoreCase(*string1++);
      c2 = OrdinalUTF8ToIgnoreCase(*string2++);
      if ( c1 != c2 )
        return false;
    }
  }
  else
  {
    for(i = 0; i < element_count; i++)
    {
      if ((*string1++) != (*string2++))
        return false;
    }
  }

  for (/*empty init*/; i < element_count1; i++)
  {
    if ( 0 != (*string1++))
      return false;
  }

  for (/*empty init*/; i < element_count2; i++)
  {
    if ( 0 != (*string2++))
      return false;
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////
//
// ON_wString::EqualOrdinal
//

bool ON_wString::EqualOrdinal(
  const ON_wString& other_string,
  bool bOrdinalIgnoreCase
  ) const
{
  const int length = Length();
  return
    (length == other_string.Length())
    && ON_wString::EqualOrdinal(
    static_cast< const wchar_t* >(*this),
    length,
    static_cast< const wchar_t* >(other_string),
    length,
    bOrdinalIgnoreCase
    );
}

bool ON_wString::EqualOrdinal(
  const wchar_t* other_string,
  bool bOrdinalIgnoreCase
  ) const
{
  const int length = Length();
  return (length == ON_wString::Length(other_string))
    && ON_wString::EqualOrdinal(
    static_cast< const wchar_t* >(*this),
    length,
    other_string,
    length,
    bOrdinalIgnoreCase
    );
}

bool ON_wString::EqualOrdinal(
  const wchar_t* string1,
  const wchar_t* string2,
  bool bOrdinalIgnoreCase
  )
{
  return ON_wString::EqualOrdinal(string1,-1,string2,-1,bOrdinalIgnoreCase);
}

bool ON_wString::EqualOrdinal(
  const wchar_t* string1,
  int element_count1,
  const wchar_t* string2,
  int element_count2,
  bool bOrdinalIgnoreCase
  )
{
  WIDE_STRING_EQUAL_PREAMBLE(string1,element_count1,string2,element_count2);

  const int element_count = (element_count1 <= element_count2) ? element_count1 : element_count2;
  int i;
  if (bOrdinalIgnoreCase)
  {
    unsigned int c1, c2;
    for(i = 0; i < element_count; i++)
    {
      c1 = OrdinalWideCharToIgnoreCase(*string1++);
      c2 = OrdinalWideCharToIgnoreCase(*string2++);
      if ( c1 != c2 )
        return false;
    }
  }
  else
  {
    for(i = 0; i < element_count; i++)
    {
      if ((*string1++) != (*string2++))
        return false;
    }
  }

  for (/*empty init*/; i < element_count1; i++)
  {
    if ( 0 != (*string1++))
      return false;
  }

  for (/*empty init*/; i < element_count2; i++)
  {
    if ( 0 != (*string2++))
      return false;
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////
//
// ON_String::CompareOrdinal
//

int ON_String::CompareOrdinal(
  const ON_String& other_string,
  bool bOrdinalIgnoreCase
  ) const
{
  return ON_String::CompareOrdinal(
    static_cast< const char* >(*this),
    this->Length(),
    static_cast< const char* >(other_string),
    other_string.Length(),
    bOrdinalIgnoreCase
    );
}

int ON_String::CompareOrdinal(
  const char* other_string,
  bool bOrdinalIgnoreCase
  ) const
{
  return ON_String::CompareOrdinal(
    static_cast< const char* >(*this),
    this->Length(),
    other_string,
    -1,
    bOrdinalIgnoreCase
    );
}

int ON_String::CompareOrdinal(
  const char* string1,
  const char* string2,
  bool bOrdinalIgnoreCase
  )
{
  return ON_String::CompareOrdinal(string1, -1, string2, -1, bOrdinalIgnoreCase);
}

int ON_String::CompareOrdinal(
  const char* string1,
  int element_count1,
  const char* string2,
  int element_count2,
  bool bOrdinalIgnoreCase
  )
{
  return ON_StringCompareOrdinalUTF8(string1,element_count1,string2,element_count2,bOrdinalIgnoreCase);
}

///////////////////////////////////////////////////////////////////////////////
//
// ON_wString::CompareOrdinal
//

int ON_wString::CompareOrdinal(
  const ON_wString& other_string,
  bool bOrdinalIgnoreCase
  ) const
{
  return ON_wString::CompareOrdinal(
    static_cast< const wchar_t* >(*this),
    this->Length(),
    static_cast< const wchar_t* >(other_string),
    other_string.Length(),
    bOrdinalIgnoreCase
    );
}

int ON_wString::CompareOrdinal(
  const wchar_t* other_string,
  bool bOrdinalIgnoreCase
  ) const
{
  return ON_wString::CompareOrdinal(
    static_cast< const wchar_t* >(*this),
    this->Length(),
    other_string,
    -1,
    bOrdinalIgnoreCase
    );
}

int ON_wString::CompareOrdinal(
  const wchar_t* string1,
  const wchar_t* string2,
  bool bOrdinalIgnoreCase
  )
{
  return ON_wString::CompareOrdinal(string1, -1, string2, -1, bOrdinalIgnoreCase);
}

int ON_wString::CompareOrdinal(
  const wchar_t* string1,
  int element_count1,
  const wchar_t* string2,
  int element_count2,
  bool bOrdinalIgnoreCase
  )
{
  return ON_StringCompareOrdinalWideChar(string1,element_count1,string2,element_count2,bOrdinalIgnoreCase);
}

char ON_String::MapCharacterOrdinal(
  ON_StringMapOrdinalType map_type,
  char c
  )
{
  switch (map_type)
  {
  case ON_StringMapOrdinalType::UpperOrdinal:
  case ON_StringMapOrdinalType::MinimumOrdinal:
    if (c >= 'a' && c <= 'z')
      return c - 0x20;
    break;
  case ON_StringMapOrdinalType::LowerOrdinal:
    if (c >= 'A' && c <= 'Z')
      return c + 0x20;
    break;
  default:
    break;
  }

  return c;
}

ON_String ON_String::MapStringOrdinal(
  ON_StringMapOrdinalType map_type
  ) const
{
  ON_String mapped_string(*this);
  if (mapped_string.IsNotEmpty())
  {
    mapped_string.CopyArray();
    const int length = mapped_string.Length();
    ON_String::MapStringOrdinal(map_type, mapped_string.m_s, length, mapped_string.m_s, length);
  }
  return mapped_string;
}

int ON_String::MapStringOrdinal(
  ON_StringMapOrdinalType map_type,
  const char* string,
  int element_count,
  char* mapped_string,
  int mapped_string_capacity
  )
{
  if (0 != mapped_string_capacity)
  {
    if (nullptr == mapped_string || mapped_string_capacity <= 0)
      return 0;

    if (string != mapped_string)
      mapped_string[0] = 0;
  }

  if (element_count < 0)
  {
    element_count = ON_String::Length(string);
    if (element_count < 0)
      return 0;
    if ( 0 == mapped_string_capacity )
      return element_count+1; // +1 for null terminator
  }
  else if ( 0 == mapped_string_capacity )
    return element_count; // no +1 here

  if ( element_count > mapped_string_capacity )
    return 0;

  char c;
  const char* s1 = string + element_count;
  switch (map_type)
  {
  case ON_StringMapOrdinalType::UpperOrdinal:
  case ON_StringMapOrdinalType::MinimumOrdinal:
    while (string < s1)
    {
      c = *string++;
      if (c >= 'a' && c <= 'z')
        c -= 0x20;
      *mapped_string++ = c;
    }
    break;

  case ON_StringMapOrdinalType::LowerOrdinal:
    while (string < s1)
    {
      c = *string++;
      if (c >= 'A' && c <= 'Z')
        c += 0x20;
      *mapped_string++ = c;
    }
    break;

  default:
    while (string < s1)
      *mapped_string++ = *string++;
    break;
  }

  if ( element_count < mapped_string_capacity )
    *mapped_string = 0;

  return element_count;
}

wchar_t ON_wString::MapCharacterOrdinal(
  ON_StringMapOrdinalType map_type,
  wchar_t c
  )
{
  return (wchar_t)MapCodePointOrdinal( c, 0xFFFFU, map_type );
}


ON_wString ON_wString::MapStringOrdinal(
  ON_StringMapOrdinalType map_type
  ) const
{
  ON_wString mapped_string(*this);
  if (ON_StringMapOrdinalType::Identity != map_type && mapped_string.IsNotEmpty())
  {
    mapped_string.CopyArray();
    const int length = mapped_string.Length();
    ON_wString::MapStringOrdinal(map_type, mapped_string.m_s, length, mapped_string.m_s, length);
  }
  return mapped_string;
}

int ON_wString::MapStringOrdinal(
  ON_StringMapOrdinalType map_type,
  const wchar_t* string,
  int element_count,
  wchar_t* mapped_string,
  int mapped_string_capacity
  )
{
  if (0 != mapped_string_capacity)
  {
    if (nullptr == mapped_string || mapped_string_capacity <= 0)
      return 0;

    if (string != mapped_string)
      mapped_string[0] = 0;
  }

  if (element_count < 0)
  {
    element_count = ON_wString::Length(string);
    if (element_count < 0)
      return 0;
    if ( 0 == mapped_string_capacity )
      return element_count+1; // +1 for null terminator
  }
  else if ( 0 == mapped_string_capacity )
    return element_count; // no +1 here

  if ( element_count > mapped_string_capacity )
    return 0;

  const wchar_t* s1 = string + element_count;
  while (string < s1)
    *mapped_string++ = ON_wString::MapCharacterOrdinal(map_type,*string++);

  if ( element_count < mapped_string_capacity )
    *mapped_string = 0;

  return element_count;
}


ON_String ON_String::MapString(
  const class ON_Locale& locale,
  ON_StringMapType map_type
  ) const
{
  return ON_String::MapString(
    locale,
    map_type,
    static_cast< const char* >(*this),
    Length()
    );
}

ON_wString ON_wString::MapString(
  const class ON_Locale& locale,
  ON_StringMapType map_type
  ) const
{
  return ON_wString::MapString(
    locale,
    map_type,
    static_cast< const wchar_t* >(*this),
    Length()
    );
}

ON_String ON_String::MapString(
  const class ON_Locale& locale,
  ON_StringMapType map_type,
  const char* string,
  int element_count
  )
{
  bool bMappingNullTerminator;

  if (element_count < 0)
  {
    element_count = ON_String::Length(string);
    if ( element_count < 0 )
      return ON_String::EmptyString;
    bMappingNullTerminator = false;
  }
  else
  {
    bMappingNullTerminator
      = element_count > 0
      && nullptr != string
      && 0 == string[element_count-1]
      && (1 == element_count || 0 != string[element_count-2])
      ;
  }

  int mapped_string_capacity = ON_String::MapString(locale,map_type,string,element_count,nullptr,0);

  if (mapped_string_capacity > 0)
  {
    ON_String mapped_string;

    // reserves mapped_length+1 wchar_t elements in mapped_string.m_s[]
    // and sets mapped_string.m_s[mapped_length] = 0.
    mapped_string.ReserveArray(mapped_string_capacity);

    // Set mapped_string ON_wString header length value to mapped_length.
    int mapped_string_length
      = ( bMappingNullTerminator )
      ? (mapped_string_capacity-1)
      : mapped_string_capacity;
    mapped_string.SetLength(mapped_string_length);

    int rc = ON_String::MapString(locale,map_type,string,element_count,mapped_string.m_s,mapped_string_capacity);
    if ( rc == mapped_string_capacity )
      return mapped_string;
  }

  return ON_String::EmptyString;
}

ON_wString ON_wString::MapString(
  const class ON_Locale& locale,
  ON_StringMapType map_type,
  const wchar_t* string,
  int element_count
  )
{
  bool bMappingNullTerminator;

  if (element_count < 0)
  {
    element_count = ON_wString::Length(string);
    if ( element_count < 0 )
      return ON_wString::EmptyString;
    bMappingNullTerminator = false;
  }
  else
  {
    bMappingNullTerminator
      = element_count > 0
      && nullptr != string
      && 0 == string[element_count-1]
      && (1 == element_count || 0 != string[element_count-2])
      ;
  }

  int mapped_string_capacity = ON_wString::MapString(locale,map_type,string,element_count,nullptr,0);

  if (mapped_string_capacity > 0)
  {
    ON_wString mapped_string;

    // reserves mapped_length+1 wchar_t elements in mapped_string.m_s[]
    // and sets mapped_string.m_s[mapped_length] = 0.
    mapped_string.ReserveArray(mapped_string_capacity);

    // Set mapped_string ON_wString header length value to mapped_length.
    int mapped_string_length
      = ( bMappingNullTerminator )
      ? (mapped_string_capacity-1)
      : mapped_string_capacity;
    mapped_string.SetLength(mapped_string_length);

    int rc = ON_wString::MapString(locale,map_type,string,element_count,mapped_string.m_s,mapped_string_capacity);
    if ( rc == mapped_string_capacity )
      return mapped_string;
  }

  return ON_wString::EmptyString;
}

int ON_String::MapString(
  const class ON_Locale& locale,
  ON_StringMapType map_type,
  const char* string,
  int element_count,
  char* mapped_string,
  int mapped_string_capacity
  )
{
  if (mapped_string_capacity < 0)
  {
    ON_ERROR("mapped_string_capacity is < 0.");
    return 0;
  }

  if (0 == mapped_string_capacity)
    mapped_string = nullptr;
  else if (mapped_string_capacity > 0)
  {
    if (nullptr == mapped_string)
    {
      ON_ERROR("mapped_string is nullptr.");
      return 0;
    }
    if ( string != mapped_string )
      mapped_string[0] = 0;
  }

  if (element_count < 0)
  {
    element_count = ON_String::Length(string);
    if (element_count < 0 )
      return 0; // string has more than max int elements - probably missing a null terminator.
  }

  if ( 0 == element_count)
  {
    return 1;
  }

  if (nullptr == string)
  {
    ON_ERROR("string is nullptr.");
    return 0;
  }

  if (false == locale.IsOrdinal())
  {
    const char* s = string;
    const char* s1 = s + element_count;
    while (s < s1)
    {
      char c = *s++;
      if (c >= 0 && c <= 127)
        continue;

      // UTF-8 multi char element code point
      // No robust UTF-8 tools are available from the Windows or Mac API.
      // TODO - investigate using ICU to avoid UTF-8 -> wide char -> UTF-8 conversion
      const ON_wString wide_string(string, element_count);
      const ON_wString wide_mapped_string = wide_string.MapString(locale, map_type);
      int mapped_element_count = ON_ConvertWideCharToUTF8(
        false, // bTestByteOrder
        static_cast<const wchar_t*>(wide_mapped_string),
        wide_mapped_string.Length(),
        mapped_string,
        mapped_string_capacity,
        nullptr,
        0,
        0,
        nullptr
        );

      if (mapped_string_capacity > 0 && wide_mapped_string.Length() > mapped_string_capacity)
      {
        ON_ERROR("mapped_string_capacity too small.");
        return 0;
      }

      if (0 == string[element_count - 1] && mapped_element_count < mapped_string_capacity)
      {
        if (mapped_element_count < mapped_string_capacity)
        {
          mapped_string[mapped_element_count] = 0;
          mapped_element_count++; // count the null terminator
        }
        else
        {
          ON_ERROR("mapped_string_capacity too small.");
          return 0;
        }
      }
      return mapped_element_count;
    }
  }

  if ( 0 == mapped_string_capacity )
    return element_count;

  switch (map_type)
  {
  case ON_StringMapType::UpperCase:
    return ON_String::MapStringOrdinal(ON_StringMapOrdinalType::UpperOrdinal,string,element_count,mapped_string,mapped_string_capacity);
    break;
  case ON_StringMapType::LowerCase:
    return ON_String::MapStringOrdinal(ON_StringMapOrdinalType::LowerOrdinal,string,element_count,mapped_string,mapped_string_capacity);
    break;
  default:
    ON_ERROR("invalid map_type.");
    break;
  }

  return 0;
}

int ON_wString::MapString(
  const class ON_Locale& locale,
  ON_StringMapType map_type,
  const wchar_t* string,
  int element_count,
  wchar_t* mapped_string,
  int mapped_string_capacity
  )
{
  if (mapped_string_capacity < 0)
  {
    ON_ERROR("mapped_string_capacity is < 0.");
    return 0;
  }

  if (0 == mapped_string_capacity)
    mapped_string = nullptr;
  else if (mapped_string_capacity > 0)
  {
    if (nullptr == mapped_string)
    {
      ON_ERROR("mapped_string is nullptr.");
      return 0;
    }
    if ( string != mapped_string )
      mapped_string[0] = 0;
  }

  if (element_count < 0)
  {
    element_count = ON_wString::Length(string);
    if (element_count < 0 )
      return 0; // string has more than max int elements - probably missing a null terminator.
  }

  if ( 0 == element_count)
  {
    return 1;
  }

  if (nullptr == string)
  {
    ON_ERROR("string is nullptr.");
    return 0;
  }

  while (false == locale.IsOrdinal())
  {

#if defined(ON_RUNTIME_WIN)
    wchar_t buffer[ON_Locale::BUFFER_MAXIMUM_CAPACITY];
    const wchar_t* locale_name
      = locale.IsInvariantCulture()
      ? LOCALE_NAME_INVARIANT
      : locale.GetWindowsLocaleName(buffer,sizeof(buffer)/sizeof(buffer[0]));

    DWORD flags = 0;
    switch (map_type)
    {
    case ON_StringMapType::UpperCase:
      flags = LCMAP_UPPERCASE;
      break;
    case ON_StringMapType::LowerCase:
      flags = LCMAP_LOWERCASE;
      break;
    default:
      ON_ERROR("invalid map_type.");
      return 0;
    }

    const int mapped_length = LCMapStringEx(
      locale_name,
      flags,
      string,
      element_count,
      mapped_string, mapped_string_capacity,
      nullptr, nullptr, 0
      );

    if ( mapped_length < mapped_string_capacity && mapped_string_capacity > 0 && nullptr != mapped_string )
    {
      if ( mapped_length <= 0 )
        mapped_string[0] = 0;
      else if ( 0 != mapped_string[mapped_length-1] )
        mapped_string[mapped_length] = 0;
    }

    return (mapped_length < 0) ? 0 : mapped_length;


#elif defined(ON_RUNTIME_APPLE)

    if ( 0 == mapped_string_capacity )
      return (element_count > 0 && nullptr != string) ? element_count : 0;

    if ( mapped_string_capacity < element_count )
      return 0;

    ON_CRT_locale_t loc = locale.StringCollateAndMapLocalePtr();

    int mapped_length = 0;
    switch (map_type)
    {
    case ON_StringMapType::UpperCase:
      while (mapped_length < element_count)
      {
        mapped_string[mapped_length] = towupper_l(string[mapped_length], loc);
        mapped_length++;
      }
      break;

    case ON_StringMapType::LowerCase:
      while (mapped_length < element_count)
      {
        mapped_string[mapped_length] = tolower_l(string[mapped_length], loc);
        mapped_length++;
      }
      break;

    default:
      ON_ERROR("invalid map_type.");
      return 0;
    }

    if ( mapped_length < mapped_string_capacity )
      mapped_string[mapped_length] = 0;
    return mapped_length;

#else
    break;
#endif
  }

  switch (map_type)
  {
  case ON_StringMapType::UpperCase:
    return ON_wString::MapStringOrdinal(ON_StringMapOrdinalType::UpperOrdinal,string,element_count,mapped_string,mapped_string_capacity);
    break;
  case ON_StringMapType::LowerCase:
    return ON_wString::MapStringOrdinal(ON_StringMapOrdinalType::LowerOrdinal,string,element_count,mapped_string,mapped_string_capacity);
    break;
  default:
    ON_ERROR("invalid map_type.");
    break;
  }

  return 0;
}

void ON_wString::MakeUpper()
{
  MakeUpperOrdinal();
}

void ON_wString::MakeLower()
{
  MakeLowerOrdinal();
}

void ON_String::MakeUpper()
{
  MakeUpperOrdinal();
}

void ON_String::MakeLower()
{
  MakeLowerOrdinal();
}


void ON_wString::MakeUpperOrdinal()
{
 	CopyArray();
  const int length = Length();
  if (length > 0)
    ON_wString::MapStringOrdinal(
    ON_StringMapOrdinalType::UpperOrdinal,
    m_s,
    length,
    m_s,
    length
    );
}

void ON_wString::MakeLowerOrdinal()
{
 	CopyArray();
  const int length = Length();
  if (length > 0)
    ON_wString::MapStringOrdinal(
    ON_StringMapOrdinalType::LowerOrdinal,
    m_s,
    length,
    m_s,
    length
    );
}

void ON_String::MakeUpperOrdinal()
{
 	CopyArray();
  const int length = Length();
  if (length > 0)
    ON_String::MapStringOrdinal(
    ON_StringMapOrdinalType::UpperOrdinal,
    m_s,
    length,
    m_s,
    length
    );
}

void ON_String::MakeLowerOrdinal()
{
 	CopyArray();
  const int length = Length();
  if (length > 0)
    ON_String::MapStringOrdinal(
    ON_StringMapOrdinalType::LowerOrdinal,
    m_s,
    length,
    m_s,
    length
    );
}
