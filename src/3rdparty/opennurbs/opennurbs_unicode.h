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

#if !defined(OPENNURBS_UNICODE_INC_)
#define OPENNURBS_UNICODE_INC_

ON_BEGIN_EXTERNC

enum ON_UnicodeEncoding
{
  ON_UTF_unset=0, // 
  ON_not_UTF,     // not a UTF encoding
  ON_UTF_8,       // UTF-8 big endian byte order
  ON_UTF_16,      // UTF-16 in native CPU byte order
  ON_UTF_16BE,    // UTF-16 big endian byte order
  ON_UTF_16LE,    // UTF-16 little endian byte order
  ON_UTF_32,      // UTF-32 in native CPU byte order
  ON_UTF_32BE,    // UTF-32 big endian byte order
  ON_UTF_32LE     // UTF-32 little endian CPU byte order
};

// UTF-8 encodings:
//   The UTF-8 encoding for codepoint values from 0 to 127 is a single single byte (char).  
//   The UTF-8 encoding for codepoint values >= 128 require multiple bytes.
// UTF-16 encodings:
//   The UTF-16 encoding of every codepoint in this enum except Wastebasket is a single word (unsigned short).



/// <summary>
/// Unicode code point values for that are hard to include in code or
/// are useful for testing encoding and glyph rendering.
/// Code points &gt;= U+0080 require UTF-8 multiple byte encodings.
/// Code points &gt;= U+10000 require UTF-16 surrogate pair encodings.
/// </summary>
enum ON_UnicodeCodePoint
{
  /// <summary>nullptr control U+0000</summary>
  ON_NullCodePoint = 0x00,

  /// <summary>BACKSPACE control U+0008</summary>
  ON_Backspace = 0x08,

  /// <summary>CHARACTER TABULATION control U+0009</summary>
  ON_Tab = 0x09,

  /// <summary>LINE FEED control U+000A</summary>
  ON_LineFeed = 0x0A,

  /// <summary>LINE TABULATION control U+000B</summary>
  ON_VerticalTab = 0x0B,

  /// <summary>FORM FEED control U+000C</summary>
  ON_FormFeed = 0x0C,

  /// <summary>CARRIAGE RETURN control U+000D</summary>
  ON_CarriageReturn = 0x0D,

  /// <summary>ESCAPE control U+001B</summary>
  ON_Escape = 0x1B,

  /// <summary>SPACE U+0020</summary>
  ON_Space = 0x20,

  /// <summary>DELETE U+007F</summary>
  ON_Delete = 0x7F,

  /// <summary>NO-BREAK SPACE (NBSP) U+00A0</summary>
  ON_NoBreakSpace = 0x00A0,

  /// <summary>OGHAM SPACE MARK U+1680</summary>
  ON_OghamSpaceMark = 0x1680,

  /// <summary>EN QUAD SPACE U+2000</summary>
  ON_EnQuad = 0x2000,

  /// <summary>EM QUAD SPACE U+2001</summary>
  ON_EmQuad = 0x2001,

  /// <summary>EN SPACE U+2002 Also known as a nut. (About 1/2 EM SPACE)</summary>
  ON_EnSpace = 0x2002,

  /// <summary>EM SPACE U+2003 Also known as a mutton.</summary>
  ON_EmSpace = 0x2003,

  /// <summary>3 per EM SPACE U+2004 (1/3 EM SPACE)</summary>
  ON_ThreePerEmSpace = 0x2004,

  /// <summary>4 per EM SPACE U+2005 (1/4 EM SPACE)</summary>
  ON_FourPerEmSpace = 0x2005,

  /// <summary>6 per EM SPACE U+2006 (1/6 EM SPACE)</summary>
  ON_SixPerEmSpace = 0x2006,

  /// <summary>FIGURE SPACE U+2007 Average digit width.</summary>
  ON_FigureSpace = 0x2007,

  /// <summary>PUNCTUATION SPACE U+2008</summary>
  ON_PunctuationSpace = 0x2008,

  /// <summary>THIN SPACE U+2009 (1/5 to 1/6 EM SPACE)</summary>
  ON_ThinSpace = 0x2009,

  /// <summary>HAIR SPACE U+200A (Narrower than THIN SPACE)</summary>
  ON_HairSpace = 0x200A,

  /// <summary>ZERO WIDTH SPACE (ZWSP) U+200B</summary>
  ON_ZeroWidthSpace = 0x200B,

  /// <summary>MEDIUM MATHEMATICAL SPACE U+2025 (about 2/9 EM SPACE)</summary>
  ON_MediumMathematicalSpace = 0x205F,

  /// <summary>IDEOGRAPHIC SPACE U+3000 The width of ideographic (Chinese, Japanese, Korean) characters.</summary>
  ON_IdeographicSpace = 0x3000,

  /// <summary>zero with non-joiner (ZWNJ) U+200C</summary>
  ON_ZeroWidthNonJoiner = 0x200C,

  /// <summary>zero with joiner (ZWJ) U+200D</summary>
  ON_ZeroWidthJoiner = 0x200D,

  /// <summary>NARROW NO-BREAK SPACE (NNBSP) U+202F</summary>
  ON_NarrowNoBreakSpace = 0x202F,

  /// <summary>QUOTATION MARK U+0022 (&quot;)</summary>
  ON_QuotationMark = 0x22,

  /// <summary>NUMBER SIGN U+0023 (#)</summary>
  ON_NumberSign = 0x23,

  /// <summary>PERCENT SIGN U+0025 (%)</summary>
  ON_PercentSign = 0x25,

  /// <summary>AMPERSAND U+0026 (&amp;)</summary>
  ON_Ampersand = 0x26,

  /// <summary>APOSTROPHE U+0027 (&apos;)</summary>
  ON_Apostrophe = 0x27,

  /// <summary>COMMA U+002C (,)</summary>
  ON_Comma = 0x2C,

  /// <summary>HYPHEN-MINUS U+002D (-)</summary>
  ON_HyphenMinus = 0x2D,

  /// <summary>UNAMBIGUOUS HYPHEN U+2010 (&#x2010;)</summary>
  ON_UnambiguousHyphen = 0x2010,

  /// <summary>NON-BREAKING HYPHEN U+2011</summary>
  ON_NoBreakHyphen = 0x2011,

  /// <summary>SMALL HYPHEN U+FE63 (&#xFE63;)</summary>
  ON_SmallHyphen = 0xFE63,

  /// <summary>UNAMBIGUOUS MINUS U+2212 (&#x2212;)</summary>
  ON_UnambiguousMinus = 0x2212,

  /// <summary>UNAMBIGUOUS MINUS U+2012 (&#x2012;)</summary>
  ON_FigureDash = 0x2012,

  /// <summary>EN DASH U+2013 (&#x2013;)</summary>
  ON_EnDash = 0x2013,

  /// <summary>EM DASH U+2014 (&#x2014;)</summary>
  ON_EmDash = 0x2014,

  /// <summary>PERIOD U+002E (decimal 46) (.)</summary>
  ON_Period = 0x2E,

  /// <summary>SOLIDUS U+002F (&#x2f;)</summary>
  ON_Slash = 0x2F,

  /// <summary>FRACTION SLASH U+2044 (&#x2044;)</summary>
  ON_FractionSlash = 0x2044,

  /// <summary>DIVISION SLASH U+2215 (&#x2215;)</summary>
  ON_DivisionSlash = 0x2215,

  /// <summary>MATHEMATICAL RISING DIAGONAL U+27CB (&#x27CB;)</summary>
  ON_MathimaticalSlash = 0x27CB,

  /// <summary>COLON U+003A (:)</summary>
  ON_Colon = 0x3A,

  /// <summary>SEMICOLON U+003B (;)</summary>
  ON_Semicolon = 0x3B,

  /// <summary>LESS-THAN SIGN U+003C (&#x3c;)</summary>
  ON_LessThanSign = 0x3C,

  /// <summary>GREATER-THAN SIGN U+003E (&#x3e;)</summary>
  ON_GreaterThanSign = 0x3E,

  /// <summary>REVERSE SOLIDUS U+005C (&#x5c;)</summary>
  ON_Backslash = 0x5C,

  /// <summary>// Unicode LOW LINE U+005F (_)</summary>
  ON_Underscore = 0x5F,

  /// <summary>VERTICAL LINE U+007C (&#x7c;)</summary>
  ON_Pipe = 0x7C,

  /// <summary>TILDE U+007E (&#x7e;)</summary>
  ON_Tilde = 0x7E,

  /// <summary>NEXT LINE (NEL) control U+0085</summary>
  ON_NextLine = 0x0085,

  /// <summary>LATIN CAPITAL LETTER R U+0052 (decimal 82) (Rhino annotation radius symbol)</summary>
  ON_RadiusSymbol = 0x0052,

  /// <summary>DEGREE SIGN U+00B0 (X&#xb0;) (Rhino annotation degree symbol)</summary>
  ON_DegreeSymbol = 0x00B0,

  /// <summary>PLUS-MINUS SIGN U+00B1 (&#xb1;) (Rhino annotation plus/minus symbol)</summary>
  ON_PlusMinusSymbol = 0x00B1,

  /// <summary>SUPERSCRIPT TWO U+00B2 (X&#xb2;) (Rhino annotation length squared symbol)</summary>
  ON_Superscript2 = 0x00B2,

  /// <summary>SUPERSCRIPT THREE U+00B3 (X&#xb3;) (Rhino annotation length cubed symbol)</summary>
  ON_Superscript3 = 0x00B3,

  /// <summary>LATIN CAPITAL LETTER O WITH STROKE U+00D8 (&#xd8;) (Rhino annotation diametersymbol)</summary>
  ON_DiameterSymbol = 0x00D8,

  /// <summary>LINE SEPARATOR U+2028 unambiguous line separator</summary>
  ON_LineSeparator = 0x2028,

  /// <summary>PARAGRAPH SEPARATOR U+2028 unambiguous paragraph separator</summary>
  ON_ParagraphSeparator = 0x2029,

  /// <summary>GREEK CAPITAL LETTER ALPHA U+0391 (&#x391;)</summary>
  ON_GreekCapitalAlpha = 0x0391,

  /// <summary>GREEK SMALL LETTER ALPHA U+03B1 (&#x3b1;)</summary>
  ON_GreekAlpha = 0x03B1,

  /// <summary>GREEK CAPITAL LETTER SIGMA U+03A3 (&#x3a3;)</summary>
  ON_GreekCapitalSigma = 0x03A3,

  /// <summary>GREEK SMALL LETTER SIGMA U+03C3 (&#x3c3;)</summary>
  ON_GreekSigma = 0x03C3,

  /// <summary>GREEK CAPITAL LETTER OMEGA U+03A9 (&#x3a9;)</summary>
  ON_GreekCapitalOmega = 0x03A9,

  /// <summary>GREEK SMALL LETTER OMEGA U+03C9 (&#x3c9;)</summary>
  ON_GreekOmega = 0x03C9,

  /// <summary>CYRILLIC CAPITAL LETTER YU U+042E (&#x42e;) (Used in Cyrillic code point tests)</summary>
  ON_CyrillicCapitalYu = 0x042E,
  
  /// <summary>Place of interest sign/looped square. (Used to indicate the command key on Mac)</summary>
  ON_PlaceOfInterestSign = 0x2318,
  
  /// <summary>Simplified Chinese logogram for tree U+6881 (&#x6881;) (Used in CJK code point tests)</summary>
  ON_SimplifiedChineseTree = 0x6881,

  /// <summary>Traditional Chinese logogram for tree U+6A39 (&#x6a39;) (Used in CJK code point tests)</summary>
  ON_TraditionalChineseTree = 0x6A39,

  /// <summary>Japanese logogram for rhinoceros U+7280 (&#x7280;) (Used in CJK code point tests)</summary>
  ON_JapaneseRhinoceros = 0x7280,

  /// <summary>Japanese logogram for tree U+6728 (&#x6728;) (Used in CJK code point tests)</summary>
  ON_JapaneseTree = 0x6728,

  /// <summary>Korean HAN U+D55C (&#xd55c;) (Used in CJK code point tests)</summary>
  ON_KoreanHan = 0xD55C,

  /// <summary>Korean JEONG U+C815 (&#xc815;) (Used in CJK code point tests)</summary>
  ON_KoreanJeong = 0xC815,

  /// <summary>DOLLAR SIGN U+0024 ($)</summary>
  ON_DollarSign = 0x0024,

  /// <summary>CENT SIGN U+00A2 (&#xa2;)</summary>
  ON_CentSign = 0x00A2,

  /// <summary>POUND SIGN U+00A3 (&#xa3;)</summary>
  ON_PoundSign = 0x00A3,

  /// <summary>CURRENCY SIGN U+00A4 (&#xa4;)</summary>
  ON_CurrencySign = 0x00A4,

  /// <summary>YEN SIGN U+00A5 (Chinese yuan, Japanese yen) (&#xa5;)</summary>
  ON_YenSign = 0x00A5,

  /// <summary>EURO SIGN U+20AC (&#x20ac;)</summary>
  ON_EuroSign = 0x20AC,

  /// <summary>PESO SIGN U+20B1 (&#x20b1;)</summary>
  ON_PesoSign = 0x20B1,

  /// <summary>RUBLE SIGN U+20BD (&#x20bd;)</summary>
  ON_RubleSign = 0x20BD,

  /// <summary>INFINITY SYMBOL U+221E (&#x221e;)</summary>
  ON_InfinitySymbol = 0x221E,

  /// <summary>
  /// UNIVERSAL RECYCLING SYMBOL U+2672 (&#x2672;)
  /// This is a good cold point for testing glyph substitution.
  /// </summary>
  ON_RecyclingSymbol = 0x2672,

  /// <summary>
  /// BLACK UNIVERSAL RECYCLING SYMBOL U+267B (&#x267b;)
  /// This is a good cold point for testing glyph substitution.
  /// </summary>
  ON_BlackRecyclingSymbol = 0x267B,

  /// <summary>WARNING SIGN U+26A0 (&#x26a0;)</summary>
  ON_WarningSign = 0x26A0,

  /// <summary>CHECK MARK U+2713 (&#x2713;)</summary>
  ON_CheckMark = 0x2713,

  /// <summary>
  /// REPLACEMENT CHARACTER U+FFFD (&#xfffd;)
  /// By convention, U+FFFD is used to mark string elements where 
  /// an invalid UTF code point encoding was encountered.
  /// </summary>
  ON_ReplacementCharacter = 0xFFFD,

  /// <summary>
  /// BYTE ORDER MARK (BOM) U+FEFF 
  /// 0xFEFF is used at the beginning of UTF encoded text to indicate the 
  /// byte order being used. It is valid for UTF-8 encoded text to begin
  /// with the UTF-8 encoding of U+FEFF (0xEF,0xBB,0xBF). 
  /// This sometimes used to mark a char string as UTF-8 encoded.
  /// and also occurs when UTF-16 and UTF-32 encoded text with a byte 
  /// order mark is converted to UTF-8 encoded text.
  /// The Unicode specification states that the 0xFFFE is &ltnot a character&gt.
  /// </summary>
  ON_ByteOrderMark = 0xFEFF,

  /// <summary>
  /// WASTEBASKET U+1F5D1 (&#x1f5d1;)
  /// The wastebasket is a good code point to test glyph rendering and UTF-16 surrogate pair encodings.
  /// UTF-8 encoding = (0xF0, 0x9F, 0x97, 0x91)
  /// UTF-16 encoding = ( 0xD83D, 0xDDD1 ) (UTF-16surrogate pair)
  /// </summary>
  ON_Wastebasket = 0x1F5D1,

  /// <summary>
  /// The maximum valid unicode code point value is 0x10FFFF.
  /// The Unicode specification states that 0x10FFFF is &ltnot a character&gt.
  /// </summary>
  ON_MaximumCodePoint = 0x10FFFF,
  
  /// <summary>
  /// The maximum valid unicode code point value is 0x10FFFF.
  /// See ON_IsValidUnicodeCodepoint() for additional restrictions.
  /// </summary>
  ON_InvalidCodePoint = 0x110000
};

/*
Returns:
  ON_UTF_16BE 
    The byte order on where the function was run is big endian.
  ON_UTF_16L
    The byte order on where the function was run is little endian.
*/
ON_DECL
enum ON_UnicodeEncoding ON_UnicodeNativeCPU_UTF16();

/*
Returns:
  ON_UTF_32BE 
    The byte order on where the function was run is big endian.
  ON_UTF_32LE
    The byte order on where the function was run is little endian.
*/
ON_DECL
enum ON_UnicodeEncoding ON_UnicodeNativeCPU_UTF32();

/*
Description:
  Determine if the buffer has the values of a UTF BOM (byte order mark)
Parameters:
  buffer - [in]
    buffer to test
  sizeof_buffer - [in]
    number of bytes that can be examined in the buffer
Returns:
  ON_UTF_unset (0)
    buffer is not a UTF BOM
  ON_UTF_8
    sizeof_buffer >= 3 and the values fo the first three bytes
    are 0xEF, 0xBB, 0xBF.
  ON_UTF_16BE
    sizeof_buffer >= 2 and the values of the first two bytes
    are 0xFE, 0xFF and, if sizeof_buffer >= 4, the value of
    one of the third or forth byte is not zero.
  ON_UTF_16LE
    sizeof_buffer >= 2 and the values of the first two bytes
    are 0xFE, 0xFF
  ON_UTF_32BE
    sizeof_buffer >= 4 and the values of the first four bytes
    are 0x00, 0x00, 0xFE, 0xFF.
  ON_UTF_32LE
    sizeof_buffer >= 4 and the values of the first four bytes
    are 0xFF, 0xFE, 0x00, 0x00.
*/
ON_DECL
enum ON_UnicodeEncoding ON_IsUTFByteOrderMark(
  const void* buffer,
  size_t sizeof_buffer
  );

/*
Parameters:
  e - [in]
Returns:
  Number of bytes in byte order mark for the specified encoding.
*/
ON_DECL
unsigned int ON_UTFSizeofByteOrderMark(
  enum ON_UnicodeEncoding e
  );

/*
Description:
  Test a value to determine if it is a valid Unicode code point value.
Parameters:
  u - [in] value to test
Returns:
  If u is valid Unicode code point, then true is returned. Otherwise false is returned.
Remarks:
  This function returns true for the Unicode byte order mark U+FFFE.
*/
ON_DECL
int ON_IsValidUnicodeCodePoint(
  ON__UINT32 unicode_code_point
);

/*
Returns:
  True if u is ON_UnicodeCodePoint::ON_Space, or a space character U+2000 - u+200B.
Remarks:
  Additional space code points may be added in the future. 
  The goal is to detect code points that separate words.
*/
ON_DECL
int ON_IsUnicodeSpaceCodePoint(
  ON__UINT32 u
);


/*
Returns:
  True if u is some type of space or control code point. Examples include 
  C0 code points ( <= u+001F ), ON_UnicodeCodePoint::ON_Space, ON_UnicodeCodePoint::ON_Delete,
  ON_UnicodeCodePoint::ON_NoBreakSpace, ON_UnicodeCodePoint::ON_NarrowNoBreakSpace,  
  ON_UnicodeCodePoint::ON_ZeroWidthSpace, and C1 code points.
Remarks:
  Additional space code points may be added in the future. 
  The goal is to detect code points that should be used as
  separators when isolating text tokens in a string.
  
  Ligatures (ZWNJ U+200C, ZWJ U+200D) return false because they control formatting in a token.
*/
ON_DECL
int ON_IsUnicodeSpaceOrControlCodePoint(
  ON__UINT32 u
);


/*
Returns:
  True if u >= U+0080 and u <= U+009F.
Remarks:
  Additional space code points may be added in the future. 
  The goal is to  detect code points that separate words.
*/
ON_DECL
int ON_IsUnicodeC1ControlCodePoint(
  ON__UINT32 u
);

/*
Description:
  Test a value to determine if it is a valid unicode code point value.
Parameters:
  w - [in] value to test
Returns:
  true: 
    w is a valid single wchar_t value
  false: 
    w is not a valid single wchar_t value. 
    It may be a completely invalid value for a string.
    When sizeof(w) < 4, is may also b a value used in a 
    multiple element encoding like a surrogate pair value.
Remarks:
  Valid 1 byte wchar_t UTF-8 unicode code points are
    (0 <= w && w <= 0x7F)
  Valid 2 byte wchar_t UTF-16 unicode code points are
    (0 <= w && w <= 0xD7FF) || (0xE000 <= w && w <= 0xFFFF)
  Valid 4 bytes wchar_t UTF-32 unicode code points are
    (0 <= u && u <= 0xD7FF) || (0xE000 <= u && u <= 0x10FFFF)
*/
ON_DECL
int ON_IsValidSingleElementWideCharValue(
  wchar_t w
  );

ON_DECL
int ON_IsValidUTF16SurrogatePair(
  unsigned int w1,
  unsigned int w2
  );

/*
Parameters:
  w1 - [in]
  w2 - in]
  error_code_point - [in]
    Value returned when (w1,w2) is not a value UTF-16 surrogate pair.
    Depending on what you are doing, good choices are
    0, 
    ON_UnicodeCodePoint::ON_ReplacementCharacter, and
    and ON_UnicodeCodePoint::ON_InvalidCodePoint
Returns:
  If (w1,w2) is a valid UTF-16 surrogate pair, the corresponding 
  unicode code point is returned. This value is always > 0.
  Otherwise, error_code_point is returned.
*/
ON_DECL
unsigned int ON_DecodeUTF16SurrogatePair(
  unsigned int u1,
  unsigned int u2,
  unsigned int error_code_point
);



/*
Description:
  Test a value to determine if it is a valid UTF-32 value.
Parameters:
  c - [in] value to test
Returns:
  true: c is a valid UTF-32 value
  false: c is not a valid UTF-32 value
Remarks:
  Valid single element UTF-32 values are
  (0 <= u && u <= 0xD7FF) || (0xE000 <= u && u <= 0x10FFFF)
*/
ON_DECL
int ON_IsValidUTF32Value(
  ON__UINT32 c
  );


/*
Description:
    Test a value to determine if it is a valid single element UTF-16 value.
Parameters:
    c - [in] value to test
Returns:
  true: c is a valid single wchar_t unicode code point
  false: c is not a valid unicode code point
  w is not a valid single element UTF-16 value.
  It may be a completely invalid value or it
  may be a value used in a surrogate pair.
Remarks:
  Valid single element UTF-16 values are
  (0 <= c && c <= 0xD7FF) || (0xE000 <= c && c <= 0xFFFF)
*/
ON_DECL
int ON_IsValidUTF16Singleton(
  ON__UINT32 c
  );

// ON_DEPRECATED
ON_DECL
int ON_IsValidSingleElementUTF16Value(
ON__UINT32 c
);



/*
Description:
  Test a value to determine if it is a valid single byte UTF-8 value.
Parameters:
  c - [in] value to test
Returns:
  true: c is a valid single byte UTF-8 value
  false: c is not a valid single byte UTF-8 value
Remarks:
  Valid single byte UTF-8 values are (0 <= w && w <= 0x7F)
*/
ON_DECL
int ON_IsValidUTF8SingletonChar(
  char c
  );
// ON_DEPRECATED
ON_DECL
int ON_IsValidSingleByteUTF8CharValue(
  char c
  );


/*
Description:
  Test a value to determine if it is a valid single byte UTF-8 value.
Parameters:
  c - [in] value to test
Returns:
true: c is a valid single byte UTF-8 value
false: c is not a valid single byte UTF-8 value
Remarks:
  Valid single byte UTF-8 values are (0 <= c && c <= 0x7F)
*/
ON_DECL
int ON_IsValidUTF8Singleton(
  ON__UINT32 c
  );

// ON_DEPRECATED
ON_DECL
int ON_IsValidSingleElementUTF8Value(
  ON__UINT32 c
  );


struct ON_CLASS ON_UnicodeErrorParameters
{
#if defined(ON_CPLUSPLUS)
  // 
  static const ON_UnicodeErrorParameters MaskErrors; // m_error_status = 0, m_error_mask = 0xFFFFFFFF, m_error_code_point = ON_UnicodeCodePoint::ON_ReplacementCharacter
  static const ON_UnicodeErrorParameters FailOnErrors; // m_error_status = 0, m_error_mask = 0, m_error_code_point = ON_UnicodeCodePoint::ON_ReplacementCharacter
#endif

  /*
  If an error occurs, then bits of error_status are
  set to indicate what type of error occurred.

  Error types:
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

   16: An illegal UTF-8, UTF-16 or UTF-32 sequence occurred, 
      or an unsupported or invalid Windows code page value,      
      or an invalid unicode code point value resulted from 
      decoding a UTF-8 sequence. 

       This error is masked if 0 != (16 & m_error_mask).
       If the error is masked and the value of m_error_code_point is
       a valid unicode code point, then m_error_code_point is used
       and parsing continues.
  */
  unsigned int m_error_status;

  /*
  If 0 != (error_mask & 4), then type 4 errors are masked.
  If 0 != (error_mask & 8), then type 8 errors are masked.
  If 0 != (error_mask & 16) and m_error_code_point is a valid unicode
  code point value, then type 16 errors are masked.
  */
  unsigned int m_error_mask;

  /*
  Unicode code point value to use in when masking type 16 errors.
  If 0 == (error_mask & 16), then this parameter is ignored.
  ON_UnicodeCodePoint::ON_ReplacementCharacter (U+FFFD) 
  is a popular choice for the m_error_code_point value.
  */
  ON__UINT32 m_error_code_point;
};

/*
Description:
  Decode a UTF-32 little endian byte order string to get a single unicode code point.
Parameters:
  sUTF32 - [in]
    UTF-32 little byte order string to convert.

  sUTF32_count - [in]
    number of ON__UINT32 elements in sUTF32[].

  e - [in/out] 
    If e is null, errors are not masked and parsing is performed
    to the point where the first error occurs.
    If e is not null, all errors are reported by setting the appropriate
    e->m_error_status bits and errors are handled as described in the
    definition of the ON_UnicodeErrorParameters struct.

    ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::MaskErrors;
    or
    ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::FailOnErrors;
    are good ways to initialize the input values.

  unicode_code_point - [out]
    The unicode_code_point pointer must not be null.
    If a nonzero value is returned, then *unicode_code_point is
    a valid unicode code point value in the CPU's native byte order.
Returns:
  Number of elements of sUTF32 that were parsed.
  0: 
     Nothing was decoded. The input value of *unicode_code_point
     is not changed.  See e->m_error_status.
  1: 
     If no error occurred, then sUTF32[0] was decoded was a valid 
     UTF-32 value. See e for masked errors.
  2:
      sUTF32[0],sUTF32[1] had values of a valid UTF-16 surrogate pair
      and e indicated to mask this error.  The UTF-16 code point
      value was returned and e was set to indicate the error occurred.
*/
ON_DECL
int ON_DecodeUTF32LE(
    const ON__UINT32* sUTF32,
    int sUTF32_count,
    struct ON_UnicodeErrorParameters* e,
    ON__UINT32* unicode_code_point
    );

/*
Description:
  Decode a UTF-32 big endian byte order string to get a single unicode code point.
Parameters:
  sUTF32 - [in]
    UTF-32 big byte order string to convert.

  sUTF32_count - [in]
    number of ON__UINT32 elements in sUTF32[].

  e - [in/out] 
    If e is null, errors are not masked and parsing is performed
    to the point where the first error occurs.
    If e is not null, all errors are reported by setting the appropriate
    e->m_error_status bits and errors are handled as described in the
    definition of the ON_UnicodeErrorParameters struct.

    ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::MaskErrors;
    or
    ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::FailOnErrors;
    are good ways to initialize the input values.

  unicode_code_point - [out]
    The unicode_code_point pointer must not be null.
    If a nonzero value is returned, then *unicode_code_point is
    a valid unicode code point value in the CPU's native byte order.
Returns:
  Number of elements of sUTF32 that were parsed.
  0: 
     Nothing was decoded. The input value of *unicode_code_point
     is not changed.  See e->m_error_status.
  1: 
     If no error occurred, then sUTF32[0] was decoded was a valid 
     UTF-32 value. See e for masked errors.
  2:
      sUTF32[0],sUTF32[1] had values of a valid UTF-16 surrogate pair
      and e indicated to mask this error.  The UTF-16 code point
      value was returned and e was set to indicate the error occurred.
*/
ON_DECL
int ON_DecodeUTF32BE(
    const ON__UINT32* sUTF32,
    int sUTF32_count,
    struct ON_UnicodeErrorParameters* e,
    ON__UINT32* unicode_code_point
    );


/*
Description:
  Decode a UTF-32 native byte order string to get a single unicode code point.
Parameters:
  sUTF32 - [in]
    UTF-32 native byte order string to convert.

  sUTF32_count - [in]
    number of ON__UINT32 elements in sUTF32[].

  e - [in/out] 
    If e is null, errors are not masked and parsing is performed
    to the point where the first error occurs.
    If e is not null, all errors are reported by setting the appropriate
    e->m_error_status bits and errors are handled as described in the
    definition of the ON_UnicodeErrorParameters struct.

    ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::MaskErrors;
    or
    ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::FailOnErrors;
    are good ways to initialize the input values.

  unicode_code_point - [out]
    The unicode_code_point pointer must not be null.
    If a nonzero value is returned, then *unicode_code_point is
    a valid unicode code point value in the CPU's native byte order.
Returns:
  Number of elements of sUTF32 that were parsed.
  0: 
     Nothing was decoded. The input value of *unicode_code_point
     is not changed.  See e->m_error_status.
  1: 
     If no error occurred, then sUTF32[0] was decoded was a valid 
     UTF-32 value. See e for masked errors.
  2:
      sUTF32[0],sUTF32[1] had values of a valid UTF-16 surrogate pair
      and e indicated to mask this error.  The UTF-16 code point
      value was returned and e was set to indicate the error occurred.
*/
ON_DECL
int ON_DecodeUTF32(
    const ON__UINT32* sUTF32,
    int sUTF32_count,
    struct ON_UnicodeErrorParameters* e,
    ON__UINT32* unicode_code_point
    );

/*
Description:
  Decode a UTF-32 string whose elements have byte order
  opposite the native CPU's to get a single unicode code point.
Parameters:
  sUTF32 - [in]
    UTF-32 string to convert with byte order opposite the
    CPU's native byte order.

  sUTF32_count - [in]
    number of ON__UINT32 elements in sUTF32[].

  e - [in/out] 
    If e is null, errors are not masked and parsing is performed
    to the point where the first error occurs.
    If e is not null, all errors are reported by setting the appropriate
    e->m_error_status bits and errors are handled as described in the
    definition of the ON_UnicodeErrorParameters struct.

    ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::MaskErrors;
    or
    ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::FailOnErrors;
    are good ways to initialize the input values.

  unicode_code_point - [out]
    The unicode_code_point pointer must not be null.
    If a nonzero value is returned, then *unicode_code_point is
    a valid unicode code point value in the CPU's native byte order.
Returns:
  Number of elements of sUTF32 that were parsed.
  0: 
     Nothing was decoded. The input value of *unicode_code_point
     is not changed.  See e->m_error_status.
  1: 
     If no error occurred, then sUTF32[0] was decoded was a valid 
     UTF-32 value. See e for masked errors.
  2:
      sUTF32[0],sUTF32[1] had values of a valid UTF-16 surrogate pair
      and e indicated to mask this error.  The UTF-16 code point
      value was returned and e was set to indicate the error occurred.
*/
ON_DECL
int ON_DecodeSwapByteUTF32(
    const ON__UINT32* sUTF32,
    int sUTF32_count,
    struct ON_UnicodeErrorParameters* e,
    ON__UINT32* unicode_code_point
    );

/*
Description:
  Convert valid unicode code point values to its UTF-8 form and use the 
  same encoding calculation for other integers with values <= 0x7FFFFFFF.
  When strict UTF-8 encoding is desired, the caller is responsible for 
  insuring the value of u is a valid unicode codepoint.
Parameters:
  u - [in]
    Integer in the CPU's native byte order in the interval [0,2147483647].
  sUTF8 - [out]
    sUTF8 is a buffer of 6 char elements and the UTF-8 form
    is returned in sUTF8[]. The returned value specifies how 
    many elements of sUTF8[] are set.
Returns:
  0: u is too large (>=2^31) to be encode.
     No changes are made to the sUTF8[] values.
  1: the UTF-8 form of u is 1 byte returned in sUTF8[0].
  2: the UTF-8 form of u is 2 bytes returned in sUTF8[0],sUTF8[1].
  3: the UTF-8 form of u is 3 bytes returned in sUTF8[0],sUTF8[1],sUTF8[2].
  4: the UTF-8 form of u is 4 bytes returned in sUTF8[0],sUTF8[1],sUTF8[2],sUTF8[3].
     Note: The maximum valid unicode codepoint is 0x10FFFF.  Values of u > 0x10FFFF
     and u <= 0x1FFFFF are encoded to 4 bytes using the same algorithm.
  5: the Universal Character Set form of u 
     is 5 bytes returned in sUTF8[0],sUTF8[1],sUTF8[2],sUTF8[3],sUTF8[4].
  6: the Universal Character Set form of u
     is 6 bytes returned in sUTF8[0],sUTF8[1],sUTF8[2],sUTF8[3],sUTF8[4],sUTF8[5].
  For return values requiring less than 6 bytes, no changes
  are made to the unused bytes in sUTF8[].
Remarks:
  Any integer in the range 0 to 2^31 - 1 can be encoded.
  When a unicode string is being encoded take steps to ensure that
  u is a valid unicode code point value.  
  The function ON_IsValidUnicodeCodePoint() can be used to determine
  if u is a valid unicode code point value.
*/
ON_DECL
int ON_EncodeUTF8( ON__UINT32 u, char sUTF8[6] );

/*
Description:
  Decode a UTF-8 encode string to get a single unicode code point.
Parameters:
  sUTF8 - [in]
    UTF-8 string to convert.

  sUTF8_count - [in]
    number of char elements in sUTF8[].

   e - [in/out] 
    If e is null, errors are not masked and parsing is performed
    to the point where the first error occurs.
    If e is not null, all errors are reported by setting the appropriate
    e->m_error_status bits and errors are handled as described in the
    definition of the ON_UnicodeErrorParameters struct.

    ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::MaskErrors;
    or
    ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::FailOnErrors;
    are good ways to initialize the input values.

  unicode_code_point - [out]
    The unicode_code_point pointer must not be null.
    If a nonzero value is returned, then *unicode_code_point is
    a valid unicode code point value.
Returns:
  Number of elements of sUTF8 that were parsed.
  0 indicates failure.
*/
ON_DECL
int ON_DecodeUTF8(
    const char* sUTF8,
    int sUTF8_count,
    struct ON_UnicodeErrorParameters* e,
    ON__UINT32* unicode_code_point
    );

/*
Description:
  Convert a 4 byte unicode code point value to its UTF-16 form.
Parameters:
  unicode_code_point - [in]
    4 byte unicode code point value in the CPU's native byte order.
    Valid values are in the interval [0,0xD7FF] or the 
    interval [0xE000,0x10FFFF].
  sUTF16 - [out]
    sUTF16 is buffer of 2 ON__UINT16 elements. If the UTF-16 form
    is a single value, it is returned in sUTF16[0]. If the UTF-16
    is a surrogate pair, the first code unit (high surrogate) 
    is returned sUTF16[0] and the second unit (low surrogate) is
    returned in sUTF16[1].  The returned values are in
    the CPU's native byte order.
Returns:
  0: u is not a valid Unicode code point. No changes are
     made to the sUTF16[] values.
  1: u is a valid Unicode code point with a UTF-16 form 
     consisting of the single value returned in sUTF16[0].
  2: u is a valid Unicode code point with a UTF-16 form 
     consisting of a surrogate pair returned in sUTF16[0] and sUTF16[1].
*/
ON_DECL
int ON_EncodeUTF16( ON__UINT32 unicode_code_point, ON__UINT16 sUTF16[2] );

/*
Description:
  Decode a UTF-16 little endian byte order string to get a single unicode code point.
Parameters:
  sUTF16 - [in]
    UTF-16 little endian byte order string to convert.

  sUTF16_count - [in]
    number of ON__UINT16 elements in sUTF16[].

  e - [in/out] 
    If e is null, errors are not masked and parsing is performed
    to the point where the first error occurs.
    If e is not null, all errors are reported by setting the appropriate
    e->m_error_status bits and errors are handled as described in the
    definition of the ON_UnicodeErrorParameters struct.

    ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::MaskErrors;
    or
    ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::FailOnErrors;
    are good ways to initialize the input values.

  unicode_code_point - [out]
    The unicode_code_point pointer must not be null.
    If a nonzero value is returned, then *unicode_code_point is
    a valid unicode code point value in the CPU's native byte order.
Returns:
  Number of elements of sUTF16 that were parsed.
  0: 
     Nothing was decoded. The input value of *unicode_code_point
     is not changed.  See e->m_error_status.
  1: 
     If no error occurred, then sUTF16[0] was decoded as a valid 
     UTF-16 singleton. See e for masked errors.
  2: 
     If no error occurred, then sUTF16[0],sUTF16[1] was decoded 
     as a valid UTF-16 surrogate pair.
     See e for masked errors.
  n >= 3:
      sUTF16[0],..,sUTF16[n-1] did not form a valid UTF-16 encoding
      and were parsed as reasonably as possible.
      See e for masked errors.
*/
ON_DECL
int ON_DecodeUTF16LE(
    const ON__UINT16* sUTF16,
    int sUTF16_count,
    struct ON_UnicodeErrorParameters* e,
    ON__UINT32* unicode_code_point
    );

/*
Description:
  Decode a UTF-16 big endian byte order string to get a single unicode code point.
Parameters:
  sUTF16 - [in]
    UTF-16 big endian byte order string to convert.

  sUTF16_count - [in]
    number of ON__UINT16 elements in sUTF16[].

  e - [in/out] 
    If e is null, errors are not masked and parsing is performed
    to the point where the first error occurs.
    If e is not null, all errors are reported by setting the appropriate
    e->m_error_status bits and errors are handled as described in the
    definition of the ON_UnicodeErrorParameters struct.

    ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::MaskErrors;
    or
    ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::FailOnErrors;
    are good ways to initialize the input values.

  unicode_code_point - [out]
    The unicode_code_point pointer must not be null.
    If a nonzero value is returned, then *unicode_code_point is
    a valid unicode code point value in the CPU's native byte order.
Returns:
  Number of elements of sUTF16 that were parsed.
  0: 
     Nothing was decoded. The input value of *unicode_code_point
     is not changed.  See e->m_error_status.
  1: 
     If no error occurred, then sUTF16[0] was decoded as a valid 
     UTF-16 singleton. See e for masked errors.
  2: 
     If no error occurred, then sUTF16[0],sUTF16[1] was decoded 
     as a valid UTF-16 surrogate pair.
     See e for masked errors.
  n >= 3:
      sUTF16[0],..,sUTF16[n-1] did not form a valid UTF-16 encoding
      and were parsed as reasonably as possible.
      See e for masked errors.
*/
ON_DECL
int ON_DecodeUTF16BE(
    const ON__UINT16* sUTF16,
    int sUTF16_count,
    struct ON_UnicodeErrorParameters* e,
    ON__UINT32* unicode_code_point
    );

/*
Description:
  Decode a UTF-16 string in native byte order to get a single unicode code point.
Parameters:
  sUTF16 - [in]
    UTF-16 string in native byte order to convert.

  sUTF16_count - [in]
    number of ON__UINT16 elements in sUTF16[].

  e - [in/out] 
    If e is null, errors are not masked and parsing is performed
    to the point where the first error occurs.
    If e is not null, all errors are reported by setting the appropriate
    e->m_error_status bits and errors are handled as described in the
    definition of the ON_UnicodeErrorParameters struct.

    ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::MaskErrors;
    or
    ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::FailOnErrors;
    are good ways to initialize the input values.

  unicode_code_point - [out]
    The unicode_code_point pointer must not be null.
    If a nonzero value is returned, then *unicode_code_point is
    a valid unicode code point value in the CPU's native byte order.
Returns:
  Number of elements of sUTF16 that were parsed.
  0: 
     Nothing was decoded. The input value of *unicode_code_point
     is not changed.  See e->m_error_status.
  1: 
     If no error occurred, then sUTF16[0] was decoded as a valid 
     UTF-16 singleton. See e for masked errors.
  2: 
     If no error occurred, then sUTF16[0],sUTF16[1] was decoded 
     as a valid UTF-16 surrogate pair.
     See e for masked errors.
  n >= 3:
      sUTF16[0],..,sUTF16[n-1] did not form a valid UTF-16 encoding
      and were parsed as reasonably as possible.
      See e for masked errors.
*/
ON_DECL
int ON_DecodeUTF16(
    const ON__UINT16* sUTF16,
    int sUTF16_count,
    struct ON_UnicodeErrorParameters* e,
    ON__UINT32* unicode_code_point
    );

/*
Description:
  Decode a UTF-16 encode string whose elements have byte order
  opposite native byte order  to get a single unicode code point.
Parameters:
  sUTF16 - [in]
    UTF-16 string to convert with byte order opposite the
    CPU's native byte order.

  sUTF16_count - [in]
    number of ON__UINT16 elements in sUTF16[].

  e - [in/out] 
    If e is null, errors are not masked and parsing is performed
    to the point where the first error occurs.
    If e is not null, all errors are reported by setting the appropriate
    e->m_error_status bits and errors are handled as described in the
    definition of the ON_UnicodeErrorParameters struct.

    ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::MaskErrors;
    or
    ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::FailOnErrors;
    are good ways to initialize the input values.

  unicode_code_point - [out]
    The unicode_code_point pointer must not be null.
    If a nonzero value is returned, then *unicode_code_point is
    a valid unicode code point value in the CPU's native byte order.
Returns:
  Number of elements of sUTF16 that were parsed.
  0: 
     Nothing was decoded. The input value of *unicode_code_point
     is not changed.  See e->m_error_status.
  1: 
     If no error occurred, then sUTF16[0] was decoded as a valid 
     UTF-16 singleton. See e for masked errors.
  2: 
     If no error occurred, then sUTF16[0],sUTF16[1] was decoded 
     as a valid UTF-16 surrogate pair.
     See e for masked errors.
  n >= 3:
      sUTF16[0],..,sUTF16[n-1] did not forma valid UTF-16 encoding
      and were parsed as reasonably as possible.
      See e for masked errors.
*/
ON_DECL
int ON_DecodeSwapByteUTF16(
    const ON__UINT16* sUTF16,
    int sUTF16_count,
    struct ON_UnicodeErrorParameters* e,
    ON__UINT32* unicode_code_point
    );

/*
Description:
  Decode a UTF-16 encode string whose elements have byte order
  opposite the native CPU's to get a single unicode code point.
Parameters:
  sWideChar - [in]
    wchar_t string to convert.

  sWideChar_count - [in]
    number of wchar_t elements in sWideChar[].

  e - [in/out] 
    If e is null, errors are not masked and parsing is performed
    to the point where the first error occurs.
    If e is not null, all errors are reported by setting the appropriate
    e->m_error_status bits and errors are handled as described in the
    definition of the ON_UnicodeErrorParameters struct.

    ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::MaskErrors;
    or
    ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::FailOnErrors;
    are good ways to initialize the input values.

  unicode_code_point - [out]
    The unicode_code_point pointer must not be null.
    If a nonzero value is returned, then *unicode_code_point is
    a valid unicode code point value in the CPU's native byte order.
Returns:
  Number of elements of sUTF16 that were parsed.
  0: 
     Nothing was decoded. The input value of *unicode_code_point
     is not changed.  See e->m_error_status.
  1: 
     If no error occurred, then sWideChar[0] was decoded as a valid 
     wchar_t singleton. See e for masked errors.
  n>=2: 
     If no error occurred, then sWideChar[0],..,sWideChar[n-1] was decoded 
     as a valid wchar_t multi-element encoding.
     Typically, UTF-16 surrogate pair or UTF-8 multi-byte sequence.
     See e for masked errors.
*/
ON_DECL
int ON_DecodeWideChar(
    const wchar_t* sWideChar,
    int sWideChar_count,
    struct ON_UnicodeErrorParameters* e,
    ON__UINT32* unicode_code_point
    );


/*
Description:
  Convert an RFT charset value to a Windows code page.
  This conversion is part of the process to get a UNICODE encoding of strings in RTF files.

Parameters:
  rtf_charset - [in]
    The RTF charset specified by /fcharsetN in the RTF font table.
  default_code_page - [out]
    Value to return if none is associated with the input rtf_charset value.

Returns:
  code page

Example:

  The RTF:
      ...
      {\fonttbl
      ...
      {\f2\fcharset129 Malgun Gothic;}
      ...
      }
      ...
      {\f2 {\ltrch \'c7\'d1\'b1\'db...}
      ...

  Uses RTF charset 129 which maps to Windows code page 949. This means
  {0xC7,0xD1,0xB1,0xBD, ... } needs to be parsed as a code page 949 multibyte encoding.
  The function ON_MapWindowsCodePage949ToUnicode() can be used to convert
  Windows code page 949 values to UNICODE code point values.

    code page 949 0xC7D1 -> U+D55C #HANGUL SYLLABLE HIEUH A NIEUN
    code page 949 0xB1BD -> U+AD75 #HANGUL SYLLABLE KIYEOK U RIEULKIYEOK

  NOTE WELL: 
  The Windows code page 949 encoding uses both single and double byte encodings.
  When the initial byte has a value < 0x80, it is a single byte encoding.
  When the initial byte has a value > 0x80, it is a double byte encoding.

Remarks:
  Conversions are based on the Rich Text Format (RTF) Specification Version 1.9.1
*/
ON_DECL
ON__UINT32 ON_MapRTFcharsetToWindowsCodePage(
  ON__UINT32 rtf_charset,
  ON__UINT32 default_code_page
);

/*
Description:
  Get a pointer to an array of 128 UNICODE code point values that are the best fit
  for Microsoft single byte code page encodings of 0x80 to 0xFF inclusive.

Parameters:
  code_page - [in]
    A Microsoft single byte code page value. (1252, 10000, etc)
Returns:
  If code_page identifies a supported single byte code page, then an array 
  of 128 UNICODE code points sorted by single byte encoding is returned.
  If a the single byte encoding is not defined, the corresponding element
  Otherwise nullptr is returned.

Example:

      const ON__UINT32 code_page = ...;
      ON__UINT32 cp_encoding = ...;
      const ON__UINT32* cp_to_unicode = ON_MSSBCP_0x80_0xFF_Unicode(code_page);
      ON__UINT32 unicode_code_point
      = (nullptr != cp_to_unicode && cp_encoding >= 0x80 && cp_encoding <= 0xFF)
      ? cp_to_unicode[cp_encoding - 0x80]
      : ON_UnicodeCodePoint::ON_ReplacementCharacter;

*/
ON_DECL
const ON__UINT32* ON_MSSBCP_0x80_0xFF_Unicode(
  ON__UINT32 code_page
  );

/*
Description:
  Convert a Microsoft single byte code page value to a UNICODE code point.
  Values 0x20 to 0x7E are the same as the ASCII encoding.

Parameters:
  code_page - [in]
    A Microsoft single byte code page value. (1252, 10000, etc)
  code_page_single_byte_encoding - [in]
    A single byte encoding of the desired glyph.

Returns:
  If cod page and code_page_single_byte_encoding are valid, then
  the best fit unicode code point is returned.
  Otherwise ON_UnicodeCodePoint::ON_ReplacementCharacter ( 0xFFFD ) is returned.
*/
ON_DECL
ON__UINT32 ON_MapMSSBCPToUnicode(
  ON__UINT32 code_page,
  ON__UINT32 code_page_single_byte_encoding
);

/*
Description:
  Convert a Unicode code point to a Microsoft code page 1252 character value.
  Windows code page 1252 is a single byte encoding.
  Values 0x20 to 0x7E are the same as the ASCII encoding.

  This function is used to find fonts where glyphs are identified by code page 1252 values.

Parameters:
  code_page - [in]
    A Microsoft single byte code page value. (1252, 10000, etc)
  unicode_code_point - [in]
    UNICODE code point

Returns:
  If unicode_code_point has a corresponding single byte encoding on the specified code page,
  then the single byte encoding is returned.
  Otherwise 0xFFFFFFFF is returned.
*/
ON_DECL
ON__UINT32 ON_MapUnicodeToMSSBCP(
  ON__UINT32 code_page,
  ON__UINT32 unicode_code_point
);

/*
Description:
  Convert unicode code point values to its wide char form.
Parameters:
  code_point - [in]
    Unicode code point in the CPU's native byte order.
  w_capacity - [in]
    If the platform wchar_t encoding is UTF-32, then w_capacity >= 1 is sufficient.
    If the platform wchar_t encoding is UTF-16, then w_capacity >= 2 is sufficient.
    If the platform wchar_t encoding is UTF-8, then w_capacity >= 6 is sufficient.
  w - [out]
    w is a buffer of w_capacity wchar_t elements and the wide char
    encoding of code_point is returned in w[].
    The returned value specifies how  many elements of w[] are set.
    When w_capacity > the returned value, the encoding is null terminated.
Returns:
  0: Invalid input (code_point is not a valid Unicode code point or
     w is nullptr).
     No changes are made to the w[] values.
  1: the wchar_t encoding of code_point is 1 wchar_t element returned in w[0].
  2: the wchar_t encoding form of code_point is 2 wchar_t element returned in w[0],w[1].
  3: the UTF-8 wchar_t encoding form of code_point is 3 wchar_t element returned in w[0],w[1],w[2].
  4: the UTF-8 wchar_t encoding form of code_point is 4 wchar_t element returned in w[0],w[1],w[2],w[3].
  5: the UTF-8 wchar_t encoding form of code_point is 5 wchar_t element returned in w[0],w[1],w[2],w[3],w[4].
  6: the UTF-8 wchar_t encoding form of code_point is 6 wchar_t element returned in w[0],w[1],w[2],w[3],w[4],w[5].
*/
ON_DECL
int ON_EncodeWideChar( 
  ON__UINT32 code_point, 
  size_t w_capacity,
  wchar_t* w
  );

/*
Description:
  Convert a unicode string from a UTF-8 encoded char array
  into a UTF-8 encoded char array.  This function can be
  used to clean UTF-8 strings that have a leading
  byte-order-mark (BOM) or contain encoding errors.

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

  sInputUTF8 - [in]
    UTF-8 encoded string to convert.

  sInputUTF8_count - [in]
    If sInputUTF8_count >= 0, then it specifies the number of
    char elements in sInputUTF8[] to convert.

    If sInputUTF8_count == -1, then sInputUTF8 must be a null
    terminated string and all the elements up to the first 
    null element are converted.

  sOutputUTF8 - [out]
    If sOutputUTF8 is not null and sOutputUTF8_count > 0, then 
    the output UTF-8 encoded string is returned in this buffer. 
    If there is room for the null terminator, the converted string
    will be null terminated. The null terminator is never included
    in the count returned by this function. No byte order mark is
    prepended.

  sOutputUTF8_count - [in]
    If sOutputUTF8_count > 0, then it specifies the number of available
    char elements in the sOutputUTF8[] buffer.
    
    If sOutputUTF8_count == 0, then the sOutputUTF8 parameter is ignored.

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
    ON_UnicodeCodePoint::ON_ReplacementCharacter (U+FFFD) 
    is a popular choice for the error_code_point value.

  sNextInputUTF8 - [out]
    If sNextInputUTF8 is not null, then *sNextInputUTF8 points to
    the first element in the input sInputUTF8[] buffer that was not 
    converted. 

    If an error occurs and is not masked, then *sNextInputUTF8 points
    to the element of sInputUTF8[] where the conversion failed.
    If no errors occur or all errors are masked, then 
    *sNextInputUTF8 points to sInputUTF8 + sInputUTF8_count.

Returns:
  If sOutputUTF8_count > 0, the return value is the number of char
  elements written to sOutputUTF8[].  When the return value < sOutputUTF8_count,
  a null terminator is written to sOutputUTF8[return value].

  If sOutputUTF8_count == 0, the return value is the minimum number of
  char elements that are needed to hold the converted string.
  The return value does not include room for a null terminator.  
  Increment the return value by one if you want to have an element
  to use for a null terminator.
*/
ON_DECL
int ON_ConvertUTF8ToUTF8(
    int bTestByteOrder,
    const char* sInputUTF8,
    int sInputUTF8_count,
    char* sOutputUTF8,
    int sOutputUTF8_count,
    unsigned int* error_status,
    unsigned int error_mask,
    ON__UINT32 error_code_point,
    const char** sNextInputUTF8
    );

/*
Description:
  Convert a unicode string from a UTF-8 encoded char array
  into a UTF-16 encoded ON__UINT16 array.

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

  sUTF8 - [in]
    UTF-8 string to convert.

  sUTF8_count - [in]
    If sUTF8_count >= 0, then it specifies the number of
    char elements in sUTF8[] to convert.

    If sUTF8_count == -1, then sUTF8 must be a null terminated
    string and all the elements up to the first null element are
    converted.

  sUTF16 - [out]
    If sUTF16 is not null and sUTF16_count > 0, then the UTF-16
    encoded string is returned in this buffer. If there is room
    for the null terminator, the converted string will be null
    terminated. The null terminator is never included in the count 
    of returned by this function. The converted string is in the 
    CPU's native byte order. No byte order mark is prepended.

  sUTF16_count - [in]
    If sUTF16_count > 0, then it specifies the number of available
    ON__UINT16 elements in the sUTF16[] buffer.
    
    If sUTF16_count == 0, then the sUTF16 parameter is ignored.

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
    ON_UnicodeCodePoint::ON_ReplacementCharacter (U+FFFD) 
    is a popular choice for the error_code_point value.

  sNextUTF8 - [out]
    If sNextUTF8 is not null, then *sNextUTF8 points to the first
    element in the input sUTF8[] buffer that was not converted. 

    If an error occurs and is not masked, then *sNextUTF8 points to
    the element of sUTF8[] where the conversion failed.  If no errors
    occur or all errors are masked, then *sNextUTF8 points to
    sUTF8 + sUTF8_count.

Returns:
  If sUTF16_count > 0, the return value is the number of ON__UINT16
  elements written to sUTF16[].  When the return value < sUTF16_count,
  a null terminator is written to sUTF16[return value].

  If sUTF16_count == 0, the return value is the minimum number of
  ON__UINT16 elements that are needed to hold the converted string.
  The return value does not include room for a null terminator.  
  Increment the return value by one if you want to have an element
  to use for a null terminator.
*/
ON_DECL
int ON_ConvertUTF8ToUTF16(
    int bTestByteOrder,
    const char* sUTF8,
    int sUTF8_count,
    ON__UINT16* sUTF16,
    int sUTF16_count,
    unsigned int* error_status,
    unsigned int error_mask,
    ON__UINT32 error_code_point,
    const char** sNextUTF8
    );

/*
Description:
  Convert a unicode string from a UTF-8 encoded char array
  into a UTF-32 encoded ON__UINT32 array.

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

  sUTF8 - [in]
    UTF-8 string to convert.

  sUTF8_count - [in]
    If sUTF8_count >= 0, then it specifies the number of
    char elements in sUTF8[] to convert.

    If sUTF8_count == -1, then sUTF8 must be a null terminated
    string and all the elements up to the first null element are
    converted.

  sUTF32 - [out]
    If sUTF32 is not null and sUTF32_count > 0, then the UTF-32
    encoded string is returned in this buffer. If there is room
    for the null terminator, the converted string will be null
    terminated. The null terminator is never included in the count 
    of returned by this function. The converted string is in the 
    CPU's native byte order. No byte order mark is prepended.

  sUTF32_count - [in]
    If sUTF32_count > 0, then it specifies the number of available
    ON__UINT32 elements in the sUTF32[] buffer.
    
    If sUTF32_count == 0, then the sUTF32 parameter is ignored.

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
    ON_UnicodeCodePoint::ON_ReplacementCharacter (U+FFFD) 
    is a popular choice for the error_code_point value.

  sNextUTF8 - [out]
    If sNextUTF8 is not null, then *sNextUTF8 points to the first
    element in the input sUTF8[] buffer that was not converted. 

    If an error occurs and is not masked, then *sNextUTF8 points to
    the element of sUTF8[] where the conversion failed.  If no errors
    occur or all errors are masked, then *sNextUTF8 points to
    sUTF8 + sUTF8_count.

Returns:
  If sUTF32_count > 0, the return value is the number of ON__UINT32
  elements written to sUTF32[].  When the return value < sUTF32_count,
  a null terminator is written to sUTF32[return value].

  If sUTF32_count == 0, the return value is the minimum number of
  ON__UINT32 elements that are needed to hold the converted string.
  The return value does not include room for a null terminator.  
  Increment the return value by one if you want to have an element
  to use for a null terminator.
*/
ON_DECL
int ON_ConvertUTF8ToUTF32(
    int bTestByteOrder,
    const char* sUTF8,
    int sUTF8_count,
    ON__UINT32* sUTF32,
    int sUTF32_count,
    unsigned int* error_status,
    unsigned int error_mask,
    ON__UINT32 error_code_point,
    const char** sNextUTF8
    );

/*
Description:
  Convert a unicode string from a UTF-16 encoded ON__UINT16 array
  into a UTF-8 encoded char array.

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

  sUTF16 - [in]
    UTF-16 string to convert.  
    
    If bTestByteOrder is true and the first element of sUTF16[]
    is 0xFEFF, then this element is skipped and it is assumed 
    that sUTF16[] is in the CPU's native byte order.
    
    If bTestByteOrder is true and the first element of sUTF16[]
    is 0xFFFE, then this element is skipped and it is assumed 
    that sUTF16[] is not in the CPU's native byte order and bytes
    are swapped before characters are converted.

    If bTestByteOrder is false or the first character of sUTF16[]
    is neither 0xFEFF nor 0xFFFE, then the sUTF16 string must match
    the CPU's byte order.

  sUTF16_count - [in]
    If sUTF16_count >= 0, then it specifies the number of
    ON__UINT16 elements in sUTF16[] to convert.

    If sUTF16_count == -1, then sUTF16 must be a null terminated
    string and all the elements up to the first null element are
    converted.
    
  sUTF8 - [out]
    If sUTF8 is not null and sUTF8_count > 0, then the UTF-8
    encoded string is returned in this buffer. If there is room
    for the null terminator, the converted string will be null
    terminated. The null terminator is never included in the count 
    of returned by this function. The converted string is in the 
    CPU's native byte order. No byte order mark is prepended.

  sUTF8_count - [in]
    If sUTF8_count > 0, then it specifies the number of available
    char elements in the sUTF8[] buffer.
    
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
    ON_UnicodeCodePoint::ON_ReplacementCharacter (U+FFFD) 
    is a popular choice for the error_code_point value.

  sNextUTF16 - [out]
    If sNextUTF16 is not null, then *sNextUTF16 points to the first
    element in the input sUTF16[] buffer that was not converted. 

    If an error occurs and is not masked, then *sNextUTF16 points to
    the element of sUTF16[] where the conversion failed.  If no errors
    occur or all errors are masked, then *sNextUTF16 points to
    sUTF16 + sUTF16_count.

Returns:
  If sUTF8_count > 0, the return value is the number of char
  elements written to sUTF8[].  When the return value < sUTF8_count,
  a null terminator is written to sUTF8[return value].

  If sUTF8_count == 0, the return value is the minimum number of
  char elements that are needed to hold the converted string.
  The return value does not include room for a null terminator.  
  Increment the return value by one if you want to have an element
  to use for a null terminator.
*/
ON_DECL
int ON_ConvertUTF16ToUTF8(
    int bTestByteOrder,
    const ON__UINT16* sUTF16,
    int sUTF16_count,
    char* sUTF8,
    int sUTF8_count,
    unsigned int* error_status,
    unsigned int error_mask,
    ON__UINT32 error_code_point,
    const ON__UINT16** sNextUTF16
    );

/*
Description:
  Convert a unicode string from a UTF-16 encoded ON__UINT16 array
  into a UTF-16 encoded ON__UINT16 array. This is not simply
  a copy in the case when the input has a byte order mark (BOM),
  different byte ordering or contains errors.  This function can
  be used to validate UTF-16 encoded strings.

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

  sInputUTF16 - [in]
    UTF-16 encoded string to convert.

  sInputUTF16_count - [in]
    If sInputUTF16_count >= 0, then it specifies the number of
    ON__UINT16 elements in sInputUTF16[] to convert.

    If sInputUTF16_count == -1, then sInputUTF16 must be a null
    terminated array and all the elements up to the first 
    null element are converted.

  sOutputUTF16 - [out]
    If sOutputUTF16 is not null and sOutputUTF16_count > 0, then 
    the output UTF-16 encoded string is returned in this buffer. 
    If there is room for the null terminator, the converted string
    will be null terminated. The null terminator is never included
    in the count returned by this function. No byte order mark is
    prepended.

  sOutputUTF16_count - [in]
    If sOutputUTF16_count > 0, then it specifies the number of available
    ON__UINT16 elements in the sOutputUTF16[] buffer.
    
    If sOutputUTF16_count == 0, then the sOutputUTF16 parameter is ignored.

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
    ON_UnicodeCodePoint::ON_ReplacementCharacter (U+FFFD) 
    is a popular choice for the error_code_point value.

  sNextInputUTF16 - [out]
    If sNextInputUTF16 is not null, then *sNextInputUTF16 points to
    the first element in the input sInputUTF16[] buffer that was not 
    converted. 

    If an error occurs and is not masked, then *sNextInputUTF16 points
    to the element of sInputUTF16[] where the conversion failed.
    If no errors occur or all errors are masked, then 
    *sNextInputUTF16 points to sInputUTF16 + sInputUTF16_count.

Returns:
  If sOutputUTF16_count > 0, the return value is the number of ON__UINT16
  elements written to sOutputUTF16[].  When the return value < sOutputUTF16_count,
  a null terminator is written to sOutputUTF16[return value].

  If sOutputUTF16_count == 0, the return value is the minimum number of
  ON__UINT16 elements that are needed to hold the converted string.
  The return value does not include room for a null terminator.  
  Increment the return value by one if you want to have an element
  to use for a null terminator.
*/
ON_DECL
int ON_ConvertUTF16ToUTF16(
    int bTestByteOrder,
    const ON__UINT16* sInputUTF16,
    int sInputUTF16_count,
    ON__UINT16* sOutputUTF16,
    int sOutputUTF16_count,
    unsigned int* error_status,
    unsigned int error_mask,
    ON__UINT32 error_code_point,
    const ON__UINT16** sNextInputUTF16
    );

/*
Description:
  Convert a unicode string from a UTF-16 encoded ON__UINT16 array
  into a UTF-32 encoded ON__UINT32 array.

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

  sUTF16 - [in]
    UTF-16 string to convert.  
    
    If bTestByteOrder is true and the first element of sUTF16[]
    is 0xFEFF, then this element is skipped and it is assumed 
    that sUTF16[] is in the CPU's native byte order.
    
    If bTestByteOrder is true and the first element of sUTF16[]
    is 0xFFFE, then this element is skipped and it is assumed 
    that sUTF16[] is not in the CPU's native byte order and bytes
    are swapped before characters are converted.

    If bTestByteOrder is false or the first character of sUTF16[]
    is neither 0xFEFF nor 0xFFFE, then the sUTF16 string must match
    the CPU's byte order.

  sUTF16_count - [in]
    If sUTF16_count >= 0, then it specifies the number of
    ON__UINT16 elements in sUTF16[] to convert.

    If sUTF16_count == -1, then sUTF16 must be a null terminated
    string and all the elements up to the first null element are
    converted.

  sUTF32 - [out]
    If sUTF32 is not null and sUTF32_count > 0, then the UTF-32
    encoded string is returned in this buffer. If there is room
    for the null terminator, the converted string will be null
    terminated. The null terminator is never included in the count 
    of returned by this function. The converted string is in the 
    CPU's native byte order. No byte order mark is prepended.

  sUTF32_count - [in]
    If sUTF32_count > 0, then it specifies the number of available
    ON__UINT32 elements in the sUTF32[] buffer.
    
    If sUTF32_count == 0, then the sUTF32 parameter is ignored.

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
    ON_UnicodeCodePoint::ON_ReplacementCharacter (U+FFFD) 
    is a popular choice for the error_code_point value.

  sNextUTF16 - [out]
    If sNextUTF16 is not null, then *sNextUTF16 points to the first
    element in the input sUTF16[] buffer that was not converted. 

    If an error occurs and is not masked, then *sNextUTF16 points to
    the element of sUTF16[] where the conversion failed.  If no errors
    occur or all errors are masked, then *sNextUTF16 points to
    sUTF16 + sUTF16_count.

Returns:
  If sUTF32_count > 0, the return value is the number of ON__UINT32
  elements written to sUTF32[].  When the return value < sUTF32_count,
  a null terminator is written to sUTF32[return value].

  If sUTF32_count == 0, the return value is the minimum number of
  ON__UINT32 elements that are needed to hold the converted string.
  The return value does not include room for a null terminator.  
  Increment the return value by one if you want to have an element
  to use for a null terminator.
*/
ON_DECL
int ON_ConvertUTF16ToUTF32(
    int bTestByteOrder,
    const ON__UINT16* sUTF16,
    int sUTF16_count,
    unsigned int* sUTF32,
    int sUTF32_count,
    unsigned int* error_status,
    unsigned int error_mask,
    ON__UINT32 error_code_point,
    const ON__UINT16** sNextUTF16
    );

/*
Description:
  Convert a unicode string from a UTF-32 encoded ON__UINT32 array
  into a UTF-8 encoded char array.

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

  sUTF32 - [in]
    UTF-32 string to convert.  
    
    If bTestByteOrder is true and the first element of sUTF32[]
    is 0x0000FEFF, then this element is skipped and it is assumed 
    that sUTF32[] is in the CPU's native byte order.
    
    If bTestByteOrder is true and the first element of sUTF32[]
    is 0xFFFE0000, then this element is skipped and it is assumed 
    that sUTF32[] is not in the CPU's native byte order and bytes
    are swapped before characters are converted.

    If bTestByteOrder is false or the first character of sUTF32[]
    is neither 0x0000FEFF nor 0xFFFE0000, then the sUTF32 string 
    must match the CPU's byte order.

  sUTF32_count - [in]
    If sUTF32_count >= 0, then it specifies the number of
    ON__UINT32 elements in sUTF32[] to convert.

    If sUTF32_count == -1, then sUTF32 must be a null terminated
    string and all the elements up to the first null element are
    converted.
    
  sUTF8 - [out]
    If sUTF8 is not null and sUTF8_count > 0, then the UTF-8
    encoded string is returned in this buffer. If there is room
    for the null terminator, the converted string will be null
    terminated. The null terminator is never included in the count 
    of returned by this function. The converted string is in the 
    CPU's native byte order. No byte order mark is prepended.

  sUTF8_count - [in]
    If sUTF8_count > 0, then it specifies the number of available
    char elements in the sUTF8[] buffer.
    
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
    ON_UnicodeCodePoint::ON_ReplacementCharacter (U+FFFD) 
    is a popular choice for the error_code_point value.

  sNextUTF32 - [out]
    If sNextUTF32 is not null, then *sNextUTF32 points to the first
    element in the input sUTF32[] buffer that was not converted. 

    If an error occurs and is not masked, then *sNextUTF32 points to
    the element of sUTF32[] where the conversion failed.  If no errors
    occur or all errors are masked, then *sNextUTF32 points to
    sUTF32 + sUTF32_count.

Returns:
  If sUTF8_count > 0, the return value is the number of char
  elements written to sUTF8[].  When the return value < sUTF8_count,
  a null terminator is written to sUTF8[return value].

  If sUTF8_count == 0, the return value is the minimum number of
  char elements that are needed to hold the converted string.
  The return value does not include room for a null terminator.  
  Increment the return value by one if you want to have an element
  to use for a null terminator.
*/
ON_DECL
int ON_ConvertUTF32ToUTF8(
    int bTestByteOrder,
    const ON__UINT32* sUTF32,
    int sUTF32_count,
    char* sUTF8,
    int sUTF8_count,
    unsigned int* error_status,
    unsigned int error_mask,
    ON__UINT32 error_code_point,
    const ON__UINT32** sNextUTF32
    );

/*
Description:
  Convert a unicode string from a UTF-32 encoded ON__UINT32 array
  into a UTF-16 encoded ON__UINT16 array.

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

  sUTF32 - [in]
    UTF-32 string to convert.  
    
    If bTestByteOrder is true and the first element of sUTF32[]
    is 0x0000FEFF, then this element is skipped and it is assumed 
    that sUTF32[] is in the CPU's native byte order.
    
    If bTestByteOrder is true and the first element of sUTF32[]
    is 0xFFFE0000, then this element is skipped and it is assumed 
    that sUTF32[] is not in the CPU's native byte order and bytes
    are swapped before characters are converted.

    If bTestByteOrder is false or the first character of sUTF32[]
    is neither 0x0000FEFF nor 0xFFFE0000, then the sUTF32 string 
    must match the CPU's byte order.

  sUTF32_count - [in]
    If sUTF32_count >= 0, then it specifies the number of
    ON__UINT32 elements in sUTF32[] to convert.

    If sUTF32_count == -1, then sUTF32 must be a null terminated
    string and all the elements up to the first null element are
    converted.

  sUTF16 - [out]
    If sUTF16 is not null and sUTF16_count > 0, then the UTF-16
    encoded string is returned in this buffer. If there is room
    for the null terminator, the converted string will be null
    terminated. The null terminator is never included in the count 
    of returned by this function. The converted string is in the 
    CPU's native byte order. No byte order mark is prepended.

  sUTF16_count - [in]
    If sUTF16_count > 0, then it specifies the number of available
    ON__UINT16 elements in the sUTF16[] buffer.
    
    If sUTF16_count == 0, then the sUTF16 parameter is ignored.

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
    ON_UnicodeCodePoint::ON_ReplacementCharacter (U+FFFD) 
    is a popular choice for the error_code_point value.

  sNextUnicode - [out]
    If sNextUnicode is not null, then *sNextUnicode points to the first
    byte in the input sNextUnicode[] buffer that was not converted. 

    If an error occurs and is not masked, then this unsigned int
    will be an illegal unicode code point value.

    If an error does not occur, then (*sNextUnicode - sUnicode) 
    is the number of values converted.

Returns:
  If sUTF16_count > 0, the return value is the number of ON__UINT16
  elements written to sUTF16[].  When the return value < sUTF16_count,
  a null terminator is written to sUTF16[return value].

  If sUTF16_count == 0, the return value is the minimum number of
  ON__UINT16 elements that are needed to hold the converted string.
  The return value does not include room for a null terminator.  
  Increment the return value by one if you want to have an element
  to use for a null terminator.
*/
ON_DECL
int ON_ConvertUTF32ToUTF16(
    int bTestByteOrder,
    const ON__UINT32* sUTF32,
    int sUTF32_count,
    ON__UINT16* sUTF16,
    int sUTF16_count,
    unsigned int* error_status,
    unsigned int error_mask,
    ON__UINT32 error_code_point,
    const ON__UINT32** sNextUTF32
    );

/*
Description:
  Convert a unicode string from a UTF-32 encoded ON__UINT32 array
  into a UTF-32 encoded ON__UINT32 array.  This is not simply
  a copy in the case when the input has a byte order mark (BOM),
  different byte ordering or contains errors.  This function can
  be used to validate UTF-32 encoded strings.

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

  sInputUTF32 - [in]
    UTF-32 string to convert.  
    
    If bTestByteOrder is true and the first element of sInputUTF32[]
    is 0x0000FEFF, then this element is skipped and it is assumed 
    that sInputUTF32[] is in the CPU's native byte order.
    
    If bTestByteOrder is true and the first element of sInputUTF32[]
    is 0xFFFE0000, then this element is skipped and it is assumed 
    that sInputUTF32[] is not in the CPU's native byte order and bytes
    are swapped before characters are converted.

    If bTestByteOrder is false or the first character of sUTF32[]
    is neither 0x0000FEFF nor 0xFFFE0000, then the sUTF32 string 
    must match the CPU's byte order.

  sInputUTF32_count - [in]
    If sInputUTF32_count >= 0, then it specifies the number of
    ON__UINT32 elements in sInputUTF32[] to convert.

    If sInputUTF32_count == -1, then sInputUTF32 must be a null 
    terminated string and all the elements up to the first null
    element are converted.

  sOutputUTF32 - [out]
    If sOutputUTF32 is not null and sOutputUTF32_count > 0, then
    the UTF-32 encoded string is returned in this buffer. If there
    is room for the null terminator, the converted string will be null
    terminated. The null terminator is never included in the count 
    of returned by this function. The converted string is in the 
    CPU's native byte order. No byte order mark is prepended.

  sOutputUTF32_count - [in]
    If sOutputUTF32_count > 0, then it specifies the number of available
    ON__UINT32 elements in the sOutputUTF32[] buffer.
    
    If sOutputUTF32_count == 0, then the sOutputUTF32 parameter
    is ignored.  This is useful when you want to validate a UTF-32
    formatted string.

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
    ON_UnicodeCodePoint::ON_ReplacementCharacter (U+FFFD) 
    is a popular choice for the error_code_point value.

  sNextInputUTF32 - [out]
    If sNextInputUTF32 is not null, then *sNextInputUTF32 points to
    the first element in the input sInputUTF32[] buffer that was not
    converted. 

    If an error occurs and is not masked, then this unsigned int
    will be an illegal unicode code point value.

    If an error does not occur, then (*sNextInputUTF32 - sInputUTF32) 
    is the number of values converted.

Returns:
  If sOutputUTF32_count > 0, the return value is the number of ON__UINT32
  elements written to sOutputUTF32[].  
  When the return value < sOutputUTF32_count,
  a null terminator is written to sOutputUTF32[return value].

  If sOutputUTF32_count == 0, the return value is the minimum number of
  ON__UINT32 elements that are needed to hold the converted string.
  The return value does not include room for a null terminator.  
  Increment the return value by one if you want to have an element
  to use for a null terminator.
*/
ON_DECL
int ON_ConvertUTF32ToUTF32(
    int bTestByteOrder,
    const ON__UINT32* sInputUTF32,
    int sInputUTF32_count,
    ON__UINT32* sOuputUTF32,
    int sOutputUTF32_count,
    unsigned int* error_status,
    unsigned int error_mask,
    ON__UINT32 error_code_point,
    const ON__UINT32** sNextInputUTF32
    );

/*
Description:
  Convert a wchar_t string using the native platform's most common
  encoding into a unicode string encoded as a UTF-8 char array.

  If 1 = sizeof(wchar_t), then the wchar_t array is assumed to be
  a UTF-8 encoded string.

  If 2 = sizeof(wchar_t), then the wchar_t array is assumed to be
  a UTF-16 encoded string. This is the case with current versions
  of Microsoft Windows.

  If 4 = sizeof(wchar_t), then the wchar_t array is assumed to be
  a UTF-32 encoded string. This is the case with current versions
  of Apple OSX.

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

  sWideChar - [in]
    wchar_t input string to convert.  
    
  sWideChar_count - [in]
    If sWideChar_count >= 0, then it specifies the number of
    wchar_t elements in sWideChar[] to convert.

    If sWideChar_count == -1, then sWideChar must be a null terminated
    array and all the elements up to the first null element are
    converted.
    
  sUTF8 - [out]
    If sUTF8 is not null and sUTF8_count > 0, then the UTF-8
    encoded string is returned in this buffer. If there is room
    for the null terminator, the converted string will be null
    terminated. The null terminator is never included in the count 
    of returned by this function. The converted string is in the 
    CPU's native byte order. No byte order mark is prepended.

  sUTF8_count - [in]
    If sUTF8_count > 0, then it specifies the number of available
    char elements in the sUTF8[] buffer.
    
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
    ON_UnicodeCodePoint::ON_ReplacementCharacter (U+FFFD) 
    is a popular choice for the error_code_point value.

  sNextWideChar - [out]
    If sNextWideChar is not null, then *sNextWideChar points to the first
    element in the input sWideChar[] buffer that was not converted. 

    If an error occurs and is not masked, then *sNextWideChar points to
    the element of sWideChar[] where the conversion failed.  If no errors
    occur or all errors are masked, then *sNextWideChar points to
    sWideChar + sWideChar_count.

  If sUTF8_count > 0, the return value is the number of char
  elements written to sUTF8[].  When the return value < sUTF8_count,
  a null terminator is written to sUTF8[return value].

  If sUTF8_count == 0, the return value is the minimum number of
  char elements that are needed to hold the converted string.
  The return value does not include room for a null terminator.  
  Increment the return value by one if you want to have an element
  to use for a null terminator.
*/
ON_DECL
int ON_ConvertWideCharToUTF8(
    int bTestByteOrder,
    const wchar_t* sWideChar,
    int sWideChar_count,
    char* sUTF8,
    int sUTF8_count,
    unsigned int* error_status,
    unsigned int error_mask,
    ON__UINT32 error_code_point,
    const wchar_t** sNextWideChar
    );

/*
Description:
  Convert a wchar_t string using the native platform's most common
  encoding into a unicode string encoded as a UTF-16 ON__UINT16 array.

  If 1 = sizeof(wchar_t), then the wchar_t array is assumed to be
  a UTF-8 encoded string.

  If 2 = sizeof(wchar_t), then the wchar_t array is assumed to be
  a UTF-16 encoded string. This is the case with current versions
  of Microsoft Windows.

  If 4 = sizeof(wchar_t), then the wchar_t array is assumed to be
  a UTF-32 encoded string. This is the case with current versions
  of Apple OS X.

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

  sWideChar - [in]
    wchar_t input string to convert.  
    
  sWideChar_count - [in]
    If sWideChar_count >= 0, then it specifies the number of
    wchar_t elements in sWideChar[] to convert.

    If sWideChar_count == -1, then sWideChar must be a null terminated
    array and all the elements up to the first null element are
    converted.
    
  sUTF16 - [out]
    If sUTF16 is not null and sUTF16_count > 0, then the UTF-16
    encoded string is returned in this buffer. If there is room
    for the null terminator, the converted string will be null
    terminated. The null terminator is never included in the count 
    of returned by this function. The converted string is in the 
    CPU's native byte order. No byte order mark is prepended.

  sUTF16_count - [in]
    If sUTF16_count > 0, then it specifies the number of available
    ON__UINT16 elements in the sUTF16[] buffer.
    
    If sUTF16_count == 0, then the sUTF16 parameter is ignored.

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
    ON_UnicodeCodePoint::ON_ReplacementCharacter (U+FFFD) 
    is a popular choice for the error_code_point value.

  sNextWideChar - [out]
    If sNextWideChar is not null, then *sNextWideChar points to the first
    element in the input sWideChar[] buffer that was not converted. 

    If an error occurs and is not masked, then *sNextWideChar points to
    the element of sWideChar[] where the conversion failed.  If no errors
    occur or all errors are masked, then *sNextWideChar points to
    sWideChar + sWideChar_count.

  If sUTF16_count > 0, the return value is the number of ON__UINT16
  elements written to sUTF16[].  When the return value < sUTF16_count,
  a null terminator is written to sUTF16[return value].

  If sUTF16_count == 0, the return value is the minimum number of
  ON__UINT16 elements that are needed to hold the converted string.
  The return value does not include room for a null terminator.  
  Increment the return value by one if you want to have an element
  to use for a null terminator.
*/
ON_DECL
int ON_ConvertWideCharToUTF16(
    int bTestByteOrder,
    const wchar_t* sWideChar,
    int sWideChar_count,
    ON__UINT16* sUTF16,
    int sUTF16_count,
    unsigned int* error_status,
    unsigned int error_mask,
    ON__UINT32 error_code_point,
    const wchar_t** sNextWideChar
    );


/*
Description:
  Convert a wchar_t string using the native platform's most common
  encoding into a unicode string encoded as a UTF-32 char array.

  If 1 = sizeof(wchar_t), then the wchar_t array is assumed to be
  a UTF-8 encoded string.

  If 2 = sizeof(wchar_t), then the wchar_t array is assumed to be
  a UTF-16 encoded string. This is the case with current versions
  of Microsoft Windows.

  If 4 = sizeof(wchar_t), then the wchar_t array is assumed to be
  a UTF-32 encoded string. This is the case with current versions
  of Apple OSX.

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

  sWideChar - [in]
    wchar_t string to convert.  

  sWideChar_count - [in]
    If sWideChar_count >= 0, then it specifies the number of
    wchar_t elements in sWideChar[] to convert.

    If sWideChar_count == -1, then sWideChar must be a null terminated
    string and all the elements up to the first null element are
    converted.
    
  sUTF32 - [out]
    If sUTF32 is not null and sUTF32_count > 0, then the UTF-32
    encoded string is returned in this buffer. If there is room
    for the null terminator, the converted string will be null
    terminated. The null terminator is never included in the count 
    of returned by this function. The converted string is in the 
    CPU's native byte order. No byte order mark is prepended.

  sUTF32_count - [in]
    If sUTF32_count > 0, then it specifies the number of available
    ON__UINT32 elements in the sUTF32[] buffer.
    
    If sUTF32_count == 0, then the sUTF32 parameter is ignored.

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
    ON_UnicodeCodePoint::ON_ReplacementCharacter (U+FFFD) 
    is a popular choice for the error_code_point value.

  sNextWideChar - [out]
    If sNextWideChar is not null, then *sNextWideChar points to the first
    element in the input sWideChar[] buffer that was not converted. 

    If an error occurs and is not masked, then *sNextWideChar points to
    the element of sWideChar[] where the conversion failed.  If no errors
    occur or all errors are masked, then *sNextWideChar points to
    sWideChar + sWideChar_count.

  If sUTF32_count > 0, the return value is the number of ON__UINT32
  elements written to sUTF32[].  When the return value < sUTF32_count,
  a null terminator is written to sUTF32[return value].

  If sUTF32_count == 0, the return value is the minimum number of
  ON__UINT32 elements that are needed to hold the converted string.
  The return value does not include room for a null terminator.  
  Increment the return value by one if you want to have an element
  to use for a null terminator.
*/
ON_DECL
int ON_ConvertWideCharToUTF32(
    int bTestByteOrder,
    const wchar_t* sWideChar,
    int sWideChar_count,
    ON__UINT32* sUTF32,
    int sUTF32_count,
    unsigned int* error_status,
    unsigned int error_mask,
    ON__UINT32 error_code_point,
    const wchar_t** sNextWideChar
    );


/*
Description:
  Convert a UTF-8 encoded char string to wchar_t string using
  the native platform's most common encoding.

  If 1 = sizeof(wchar_t), then UTF-8 encoding is used for the
  output string.

  If 2 = sizeof(wchar_t), then UTF-16 encoding is used for the
  output string. This is the case with current versions of
  Microsoft Windows.

  If 4 = sizeof(wchar_t), then UTF-32 encoding is used for the
  output string. This is the case with current versions of
  Apple OSX.

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

  sUTF8 - [in]
    UTF-8 string to convert.

  sUTF8_count - [in]
    If sUTF8_count >= 0, then it specifies the number of
    char elements in sUTF8[] to convert.

    If sUTF8_count == -1, then sUTF8 must be a null terminated
    string and all the elements up to the first null element are
    converted.

  sWideChar - [out]
    If sWideChar is not null and sWideChar_count > 0, then the
    output string is returned in this buffer. If there is room
    for the null terminator, the converted string will be null
    terminated. The null terminator is never included in the count 
    of returned by this function. The converted string is in the 
    CPU's native byte order. No byte order mark is prepended.

  sWideChar_count - [in]
    If sWideChar_count > 0, then it specifies the number of available
    wchar_t elements in the sWideChar[] buffer.
    
    If sWideChar_count == 0, then the sWideChar parameter is ignored.

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
    ON_UnicodeCodePoint::ON_ReplacementCharacter (U+FFFD) 
    is a popular choice for the error_code_point value.

  sNextUTF8 - [out]
    If sNextUTF8 is not null, then *sNextUTF8 points to the first
    element in the input sUTF8[] buffer that was not converted. 

    If an error occurs and is not masked, then *sNextUTF8 points to
    the element of sUTF8[] where the conversion failed.  If no errors
    occur or all errors are masked, then *sNextUTF8 points to
    sUTF8 + sUTF8_count.

Returns:
  If sWideChar_count > 0, the return value is the number of wchar_t
  elements written to sWideChar[].  When the return value < sWideChar_count,
  a null terminator is written to sWideChar[return value].

  If sWideChar_count == 0, the return value is the minimum number of
  wchar_t elements that are needed to hold the converted string.
  The return value does not include room for a null terminator.  
  Increment the return value by one if you want to have an element
  to use for a null terminator.
*/
ON_DECL
int ON_ConvertUTF8ToWideChar(
    int bTestByteOrder,
    const char* sUTF8,
    int sUTF8_count,
    wchar_t* sWideChar,
    int sWideChar_count,
    unsigned int* error_status,
    unsigned int error_mask,
    ON__UINT32 error_code_point,
    const char** sNextUTF8
    );

/*
Description:
  Convert a UTF-16 encoded string to wchar_t string using
  the native platform's most common encoding.

  If 1 = sizeof(wchar_t), then UTF-8 encoding is used for the
  output string.

  If 2 = sizeof(wchar_t), then UTF-16 encoding is used for the
  output string. This is the case with current versions of
  Microsoft Windows.

  If 4 = sizeof(wchar_t), then UTF-32 encoding is used for the
  output string. This is the case with current versions of
  Apple OSX.

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

  sUTF16 - [in]
    UTF-16 string to convert.

  sUTF16_count - [in]
    If sUTF16_count >= 0, then it specifies the number of
    ON__UINT16 elements in sUTF16[] to convert.

    If sUTF16_count == -1, then sUTF16 must be a null terminated
    string and all the elements up to the first null element are
    converted.

  sWideChar - [out]
    If sWideChar is not null and sWideChar_count > 0, then the
    output string is returned in this buffer. If there is room
    for the null terminator, the converted string will be null
    terminated. The null terminator is never included in the count 
    of returned by this function. The converted string is in the 
    CPU's native byte order. No byte order mark is prepended.

  sWideChar_count - [in]
    If sWideChar_count > 0, then it specifies the number of available
    wchar_t elements in the sWideChar[] buffer.
    
    If sWideChar_count == 0, then the sWideChar parameter is ignored.

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
    ON_UnicodeCodePoint::ON_ReplacementCharacter (U+FFFD) 
    is a popular choice for the error_code_point value.

  sNextUTF16 - [out]
    If sNextUTF16 is not null, then *sNextUTF16 points to the first
    element in the input sUTF16[] buffer that was not converted. 

    If an error occurs and is not masked, then *sNextUTF8 points to
    the element of sUTF16[] where the conversion failed.  If no errors
    occur or all errors are masked, then *sNextUTF16 points to
    sUTF16 + sUTF16_count.

Returns:
  If sWideChar_count > 0, the return value is the number of wchar_t
  elements written to sWideChar[].  When the return value < sWideChar_count,
  a null terminator is written to sWideChar[return value].

  If sWideChar_count == 0, the return value is the minimum number of
  wchar_t elements that are needed to hold the converted string.
  The return value does not include room for a null terminator.  
  Increment the return value by one if you want to have an element
  to use for a null terminator.
*/
ON_DECL
int ON_ConvertUTF16ToWideChar(
    int bTestByteOrder,
    const ON__UINT16* sUTF16,
    int sUTF16_count,
    wchar_t* sWideChar,
    int sWideChar_count,
    unsigned int* error_status,
    unsigned int error_mask,
    ON__UINT32 error_code_point,
    const ON__UINT16** sNextUTF16
    );

/*
Description:
  Convert a UTF-32 encoded string to wchar_t string using
  the native platform's most common encoding.

  If 1 = sizeof(wchar_t), then UTF-8 encoding is used for the
  output string.

  If 2 = sizeof(wchar_t), then UTF-16 encoding is used for the
  output string. This is the case with current versions of
  Microsoft Windows.

  If 4 = sizeof(wchar_t), then UTF-32 encoding is used for the
  output string. This is the case with current versions of
  Apple OSX.

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

  sUTF32 - [in]
    UTF-32 string to convert.

  sUTF32_count - [in]
    If sUTF32_count >= 0, then it specifies the number of
    ON__UINT32 elements in sUTF32[] to convert.

    If sUTF32_count == -1, then sUTF32 must be a null terminated
    string and all the elements up to the first null element are
    converted.

  sWideChar - [out]
    If sWideChar is not null and sWideChar_count > 0, then the
    output string is returned in this buffer. If there is room
    for the null terminator, the converted string will be null
    terminated. The null terminator is never included in the count 
    of returned by this function. The converted string is in the 
    CPU's native byte order. No byte order mark is prepended.

  sWideChar_count - [in]
    If sWideChar_count > 0, then it specifies the number of available
    wchar_t elements in the sWideChar[] buffer.
    
    If sWideChar_count == 0, then the sWideChar parameter is ignored.

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
    ON_UnicodeCodePoint::ON_ReplacementCharacter (U+FFFD) 
    is a popular choice for the error_code_point value.

  sNextUTF32 - [out]
    If sNextUTF32 is not null, then *sNextUTF32 points to the first
    element in the input sUTF32[] buffer that was not converted. 

    If an error occurs and is not masked, then *sNextUTF8 points to
    the element of sUTF32[] where the conversion failed.  If no errors
    occur or all errors are masked, then *sNextUTF32 points to
    sUTF32 + sUTF32_count.

Returns:
  If sWideChar_count > 0, the return value is the number of wchar_t
  elements written to sWideChar[].  When the return value < sWideChar_count,
  a null terminator is written to sWideChar[return value].

  If sWideChar_count == 0, the return value is the minimum number of
  wchar_t elements that are needed to hold the converted string.
  The return value does not include room for a null terminator.  
  Increment the return value by one if you want to have an element
  to use for a null terminator.
See Also:
  ON_wString::FromUnicodeCodePoints()
*/
ON_DECL
int ON_ConvertUTF32ToWideChar(
    int bTestByteOrder,
    const ON__UINT32* sUTF32,
    int sUTF32_count,
    wchar_t* sWideChar,
    int sWideChar_count,
    unsigned int* error_status,
    unsigned int error_mask,
    ON__UINT32 error_code_point,
    const ON__UINT32** sNextUTF32
    );

/*
Description:
  Convert a string from a Microsoft multibyte code page encoding 
  to a wide string using UTF-8 / UTF-16 / UTF-32 encoding 
  (depending on the size of wchar_t).
  This function is designed to be used to parse portions of 
  rich text RTF in ON_TextContent, strings from outside sources
  with known MBCS encodings, and some user interface code. 

  Opennurbs assumes all other char strings are UTF-8 encoded.

  If 1 = sizeof(wchar_t), then UTF-8 encoding is used for the
  output string.

  If 2 = sizeof(wchar_t), then UTF-16 encoding is used for the
  output string. This is the case with current versions of
  Microsoft Windows.

  If 4 = sizeof(wchar_t), then UTF-32 encoding is used for the
  output string. This is the case with current versions of
  Apple OSX.

Parameters:
  windows_code_page - [in]
    The windows code page specifies the encoding of the sMBCS string.

  sMBCS - [in]
    Windows multibyte string with encoding identified by windows_code_page.

  sMBCS_count - [in]
    If sMBCS_count >= 0, then it specifies the number of
    char elements (bytes) in sMBCS[] to convert.

    If sMBCS_count == -1, then sMBCS must be a null terminated
    string and all the elements up to the first null element are
    converted.

  sWideChar - [out]
    If sWideChar is not null and sWideChar_count > 0, then the
    output string is returned in this buffer. If there is room
    for the null terminator, the converted string will be null
    terminated. The null terminator is never included in the count 
    of returned by this function. The converted string is in the 
    CPU's native byte order. No byte order mark is prepended.

  sWideChar_capacity - [in]
    If sWideChar_capacity > 0, then it specifies the number of available
    wchar_t elements in the sWideChar[] buffer.
    
    If sWideChar_count == 0, then the sWideChar parameter is ignored.

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
      16: An illegal encoding sequence occurred.
          The illegal sequence is replaced with
          a single ON_wString::ReplacementCharacter in the output string
          and parsing continues.

Returns:
  If sWideChar_capacity > 0, the return value is the number of wchar_t
  elements written to sWideChar[].  When the return value < sWideChar_capacity,
  a null terminator is written to sWideChar[return value].

  If sWideChar_count == 0, the return value is the minimum number of
  wchar_t elements that are needed to hold the converted string.
  The return value does not include room for a null terminator.  
  Increment the return value by one if you want to have an element
  to use for a null terminator.
*/
ON_DECL
int ON_ConvertMSMBCPToWideChar(
    ON__UINT32 windows_code_page,
    const char* sMBCS,
    int sMBCS_count,
    wchar_t* sWideChar,
    int sWideChar_capacity,
    unsigned int* error_status
    );


/*
Description:
  Convert a string from UTF-8/UTF=16/UTF-32 encoding (depending on size of wchar_t)
  to a Microsoft multibyte code page encoding.

  This function is designed to be used to create strings that will
  be used write files that require non-UTF encoded char strings.
  
  Opennurbs assumes all other char strings are UTF-8 encoded.

  If 1 = sizeof(wchar_t), then sWideChar must be UTF-8 encoded.

  If 2 = sizeof(wchar_t), then sWideChar must be UTF-16 encoded.

  If 4 = sizeof(wchar_t), then sWideChar must be UTF-16 or UTF-32 encoded.

Parameters:
  windows_code_page - [in]
    THe windows code page specifies the encoding of the sMBCS string.

  sWideChar - [out]
    The input UTF encoded string. If sWideChar_count is -1, this string
    must be null terminated. If sWideChar_count > 0, the string
    must has sWideChar_count wchar_t elements that are a UTF encoding.

  sWideChar_count - [in]
    If sWideChar_capacity > 0, then it specifies the number of wchar_t
    elements in the sWideChar[] to convert.

    If sWideChar_count == -1, then sWideChar must be a null terminated
    string and all the elements up to the first null element are
    converted.

  sMBCS - [out]
    If sMBCS is not null and sMBCS_count > 0, then the
    output MBCS encoded string is returned in this buffer. 
    If there is room for the null terminator, the converted string 
    will be null terminated. The null terminator is never included
    in the count  of returned by this function. 

  sMBCS_capacity - [in]
    If sWideChar_capacity > 0, then it specifies the number of available
    char elements (bytes) in the sMBCS[] buffer.

    If sMBCS_capacity == 0, then the sMBCS parameter is ignored.

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
      16: An illegal encoding sequence occurred or a UNICODE codepoint
          was encountered that cannot be encoded in the code page
          specified by windows_code_page. In either case, a
          a single question mark (?) in the output string
          and parsing continues.

Returns:
  If sMBCS_capacity > 0, the return value is the number
  MBCS encoded char elements written to sWideChar[]. 
  When the return value < sMBCSChar_capacity,
  a null terminator is written to sWideChar[return value].

  If sMBCS_count == 0, the return value is the minimum number of
  char elements that are needed to hold the MBCS encode string.
  The return value does not include room for a null terminator.
  Increment the return value by one if you want to have an element
  to use for a null terminator.
*/
ON_DECL
int ON_ConvertWideCharToMSMBCP(
  const wchar_t* sWideChar,
  int sWideChar_count,
  ON__UINT32 windows_code_page,
  char* sMBCS,
  int sMBCS_capacity,
  unsigned int* error_status
);

ON_END_EXTERNC

#if defined(ON_CPLUSPLUS)
ON_DECL
ON__UINT32 ON_Test_MSSBCP(
  const ON__UINT32 code_page,
  const ON__UINT32 char_encoding,
  bool bWindowsAPITest,
  ON_TextLog& text_log
);

ON_DECL
bool ON_Test_MSSBCP(
  const ON__UINT32 code_page,
  bool bWindowsAPITest,
  ON_TextLog& text_log
);

ON_DECL
bool ON_Test_MSSBCP(
  bool bWindowsAPITest,
  ON_TextLog& text_log
);

ON_DECL
bool ON_Test_PrintPlatformMSSBCPToUnicodeTable(
  const ON__UINT32 code_page,
  ON__UINT32 char_encoding0,
  ON__UINT32 char_encoding1,
  ON_TextLog& text_log
);

/*
Description:
  Test a value to determine if it is a Unicode code point reserved for
  private use (can be user defined).
Parameters:
  unicode_code_point - [in] value to test
Returns:
  If unicode_code_point is a private use Unicode code point, then true is returned. Otherwise false is returned.
*/
ON_DECL
bool ON_IsPrivateUseUnicodeCodePoint(
  ON__UINT32 unicode_code_point
);

/*
Description:
  Test a value to determine if it is a standard Unicode code point.
Parameters:
  unicode_code_point - [in] value to test
Returns:
  If unicode_code_point is a valid Unicode code point that is not reserved for private use
  and not the Unicode byte order mark (U+FFFE), then true is returned.
  Otherwise false is returned.
*/
ON_DECL
bool ON_IsStandardUnicodeCodePoint(
  ON__UINT32 unicode_code_point
);


/*
Parameters:
  code_point - [in]
    value to test
  bNullReturnValue
    value to return if 0 == code_point
Returns:
  true if the code_point is a control code point 
  (> 0 && < U+0020)
  or ( >=  U+007F && <= U+00A0)
  or ( ==  U+00AD)
  or ...
*/
ON_DECL
bool ON_IsUnicodeControlCodePoint(
  ON__UINT32 code_point,
  bool bNullReturnValue
);

/// <summary>
/// When possible, converts a code point to a superscript code point. Note that many common fonts
/// typecast the Unicode digit superscripts as vulgar fraction numerators rather than a proper superscript.
/// </summary>
/// <param name="cp">
/// Unicode code point for which a superscript is desired.
/// </param>
/// <param name="no_superscript_cp">
/// When in doubt, pass cp.
/// </param>
/// <returns>
/// If the code point cp has a Unicode superscript, the code point of the superscript is returned.
/// Otherwise no_superscript_cp is returned.
/// </returns>
ON_DECL
unsigned ON_UnicodeSuperscriptFromCodePoint(
  unsigned cp,
  unsigned no_superscript_cp
);

/// <summary>
/// Get the Unicode code point for a decimal digit superscript.
/// </summary>
/// <param name="decimal_digit">
/// 0 &lt;= decimal_digit &lt;= 9
/// </param>
/// <returns>
/// If 0 &lt;= decimal_digit &lt;= 9, then the Unicode code point for the superscript digit is returned.
/// Otherwise 0 is returned.
/// </returns>
ON_DECL
unsigned ON_UnicodeSuperscriptFromDigit(
  unsigned decimal_digit
);


/// <summary>
/// When possible, converts a code point to a subscript code point. Note that many common fonts
/// typecast the Unicode digit subscripts as vulgar fraction denominators rather than a proper subscript.
/// </summary>
/// <param name="cp">
/// Unicode code point for which a subscript is desired.
/// </param>
/// <param name="no_subscript_cp">
/// When in doubt, pass cp.
/// </param>
/// <returns>
/// If the code point cp has a Unicode subscript, the code point of the subscript is returned.
/// Otherwise no_subscript_cp is returned.
/// </returns>
ON_DECL
unsigned ON_UnicodeSubcriptFromCodePoint(
  unsigned cp,
  unsigned no_subscript_cp
);

/// <summary>
/// Get the Unicode code point for a decimal digit subscript.
/// </summary>
/// <param name="decimal_digit">
/// 0 &lt;= decimal_digit &lt;= 9
/// </param>
/// <returns>
/// If 0 &lt;= decimal_digit &lt;= 9, then the Unicode code point for the subscript digit is returned.
/// Otherwise 0 is returned.
/// </returns>
ON_DECL
unsigned ON_UnicodeSubscriptFromDigit(
  unsigned decimal_digit
);

/// <summary>
/// ON_UnicodeShortCodePoint is a tool to use when working with Unicode code points 
/// with values &lt=0xFFFF.
/// Note that valid Unicode code point values can be as large as 0x10FFFD. 
/// (0x10FFFE and 0x10FFFF are specified as &ltnot a character&gt by the Unicode Standard code chart
/// https://www.unicode.org/charts/PDF/U10FF80.pdf)
/// This class is used when converting between Unicode and BIG5 encodings and in other settings
/// where Unicode code points &gt 0xFFFF are not encountered
/// and the 2 byte size of ON_UnicodeShortCodePoint
/// appreciably more  efficient that a 4 byte size of an unsigned int.
/// </summary>
class ON_CLASS ON_UnicodeShortCodePoint
{
public:
  ON_UnicodeShortCodePoint() = default;
  ~ON_UnicodeShortCodePoint() = default;
  ON_UnicodeShortCodePoint(const ON_UnicodeShortCodePoint&) = default;
  ON_UnicodeShortCodePoint& operator=(const ON_UnicodeShortCodePoint&) = default;

public:
  /// <summary>
  /// ON_UnicodeShortCodePoint::NUll has a code point value = 0.
  /// </summary>
  static const ON_UnicodeShortCodePoint Null;

  /// <summary>
  /// ON_UnicodeShortCodePoint::ReplacementCharacter has a code point = U+FFFD.
  /// </summary>
  static const ON_UnicodeShortCodePoint ReplacementCharacter;

  /// <summary>
  /// ON_UnicodeShortCodePoint::ByteOrderMark has a code point value = 0xFFFE.
  /// (0xFFFE is not a Unicode character code point.)
  /// </summary>
  static const ON_UnicodeShortCodePoint ByteOrderMark;

  /// <summary>
  /// ON_UnicodeShortCodePoint::Error has a code point value = 0xFFFF.
  /// (0xFFFF is not a Unicode character code point.)
  /// </summary>
  static const ON_UnicodeShortCodePoint Error;
    
  /// <summary>
  /// Creates a Unicode code point with the specified code point value. 
  /// </summary>
  /// <param name="unicode_code_point">
  /// A valid Unicode code point.
  /// </param>
  /// <returns>
  /// If unicode_code_point is &lt= 0xFFFE and a valid Unicode code point or
  /// is the Unicode byte order mark (0xFFFE), then an instance with that
  /// value as code point is returned.
  /// Otherwise ON_UnicodeShortCodePoint::Error is returned.
  /// Notes:
  /// 1. Valid Unicode code points can be as large as 0x10FFFD and
  /// ON_UnicodeShortCodePoint cannot accommodate code points &gt= U+10000.
  /// 2. Values &gt= 0xD800 and &lt 0xE000 are not valid Unicode code points.
  /// These values are used in UTF-16 surrogate pair encodings of code points &gt= U+10000.
  /// </returns>
  static const ON_UnicodeShortCodePoint Create(unsigned int unicode_code_point);

  /// <summary>
  /// Find a Unicode code point with the same character as big5_code_point.
  /// </summary>
  /// <param name="big5_code_point"></param>
  /// <param name="not_available">Value to return when big5_code_point is valid but does not map to a Unicode code point.</param>
  /// <returns>
  /// If there is a corresponding BIG5 or ASCII code point, that code point is returned.
  /// Otherwise, if big5_code_point is valid, not_available is returned. 
  /// Otherwise ON_UnicodeShortCodePoint::Error is returned.
  /// </returns>
  static const ON_UnicodeShortCodePoint CreateFromBig5(
    unsigned int big5_code_point,
    ON_UnicodeShortCodePoint not_available
  );

  /// <summary>
  /// Find a Unicode code point with the same character as big5_code_point.
  /// </summary>
  /// <param name="big5_code_point"></param>
  /// <param name="not_available">Value to return when big5_code_point is valid but does not map to a Unicode code point.</param>
  /// <returns>
  /// If there is a corresponding BIG5 or ASCII code point, that code point is returned.
  /// Otherwise, if big5_code_point is valid, not_available is returned. 
  /// Otherwise ON_UnicodeShortCodePoint::Error is returned.
  /// </returns>
  static const ON_UnicodeShortCodePoint CreateFromBig5(
    const class ON_Big5CodePoint& big5_code_point,
    ON_UnicodeShortCodePoint not_available
  );

  /// <summary>
  /// Determine if this Unicode code point is 0.
  /// </summary>
  /// <returns>True if the code point value is 0.</returns>
  bool IsNull() const;

  /// <summary>
  /// The Unicode is a extension of ASCII encoding and code points &lt= 0x7F are valid Unicode code points.
  /// </summary>
  /// <param name="bNullIsASCII">
  /// Value to return if this Unicode code point equal to ON_UnicodeShortCodePoint::Null. </param>
  /// <returns>
  /// True if the code point value &le= 0x7F.
  /// </returns>
  bool IsASCII(bool bNullIsASCII) const;

  /// <summary>
  /// Determine if the Unicode code point is valid. 
  /// </summary>
  /// <param name="bNullIsValid">
  /// Value to return if the code point value is 0.
  /// </param>
  /// <param name="bByteOrderMarkIsValid">
  /// Value to return if the code point value is 0xFFFE.
  /// </param>
  /// <returns>True if the code point value is a valid Unicode code point.</returns>
  bool IsValid(bool bNullIsValid, bool bByteOrderMarkIsValid) const;

  /// <summary>
  /// Unicode code points are separated into standard and private use (user defined) code points.
  /// </summary>
  /// <param name="bNullIsValid">
  /// Value to return if the code point value is 0.
  /// </param>
  /// <returns>Returns true this Unicode code point is a standard code point.</returns>
  bool IsStandard(bool bNullIsValid) const;

  /// <summary>
  /// Unicode code points are separated into standard and private use (user defined) code points.
  /// </summary>
  /// <returns>True if this Unicode code point is a private use (user defined) code point.</returns>
  bool IsPrivateUse() const;

  /// <summary>
  /// The Unicode code point U+FFFD is called the replacement character.
  /// It is typically a light question mark with a dark diamond background.
  /// It is often used to indicate a character is unknown, unavailable, does
  /// not exist, or an error occurred when creating that code point.
  /// </summary>
  /// <returns>True if this Unicode code point is U+FFFD.</returns>
  bool IsReplacementCharacter() const;

  /// <summary>
  /// The Unicode code point value 0xFFFE os not a character and is used as a byte order mark.
  /// </summary>
  /// <returns>True if this Unicode code point value is 0xFFFE.</returns>
  bool IsByteOrderMark() const;

  unsigned int UnicodeCodePoint() const;

  static int Compare(const ON_UnicodeShortCodePoint* lhs, const ON_UnicodeShortCodePoint* rhs);
private:
  ON__UINT16 m_unicode_code_point = 0;
};

ON_DECL bool operator==(ON_UnicodeShortCodePoint lhs, ON_UnicodeShortCodePoint rhs);
ON_DECL bool operator!=(ON_UnicodeShortCodePoint lhs, ON_UnicodeShortCodePoint rhs);
ON_DECL bool operator<=(ON_UnicodeShortCodePoint lhs, ON_UnicodeShortCodePoint rhs);
ON_DECL bool operator>=(ON_UnicodeShortCodePoint lhs, ON_UnicodeShortCodePoint rhs);
ON_DECL bool operator<(ON_UnicodeShortCodePoint lhs, ON_UnicodeShortCodePoint rhs);
ON_DECL bool operator>(ON_UnicodeShortCodePoint lhs, ON_UnicodeShortCodePoint rhs);


/// <summary>
/// ON_Big5CodePoint is a tool to use when working with BIG5 encoded strings.
/// </summary>
class ON_CLASS ON_Big5CodePoint
{
public:
  /// <summary>
  /// ON_Big5CodePoint::NUll has a code point value = 0.
  /// </summary>
  static const ON_Big5CodePoint Null;

  /// <summary>
  /// ON_Big5CodePoint::Error has a code point value = 0xA3E1.
  /// 0xA3E1 is in the BIG5 reserved section but old versions of Windows 
  /// mapped it to the Euro currency symbol. The main use of this code is to translate
  /// from legacy BIG5 to Unicode, so this anomaly is supported.
  /// </summary>
  static const ON_Big5CodePoint WindowsEuro;

  /// <summary>
  /// ON_Big5CodePoint::Error has a code point value = 0xFFFF.
  /// (0xFFFF is not a valid BIG5 code point value.)
  /// </summary>
  static const ON_Big5CodePoint Error;

  static const char* Decode(
    const char* buffer,
    size_t buffer_count,
    bool bParseNull,
    bool bParseASCII,
    ON_Big5CodePoint* big5_code_point
  );

  enum : unsigned int
  {
    MinimumCodePoint = 0x8140,
    MinimumPrivateUseCodePoint = 0x8140,
    MinimumStandardCodePoint = 0x8140,
    MaximumStandardCodePoint = 0xF9D5,
    MaximumPrivateUseCodePoint = 0xFEFE,
    MaximumCodePoint = 0xFEFE
  };

  int Encode(
    char* buffer,
    size_t buffer_capacity
  ) const;

  ON_Big5CodePoint() = default;
  ~ON_Big5CodePoint() = default;
  ON_Big5CodePoint(const ON_Big5CodePoint&) = default;
  ON_Big5CodePoint& operator=(const ON_Big5CodePoint&) = default;

  /// <summary>
  /// Creates a BIG5 code point with the specified code point value. 
  /// </summary>
  /// <param name="big5_code_point">
  /// A valid BIG5 code point, ASCII code point (0x00-0x7E), or the
  /// old Windows Euro currency symbol code point 0xA3E1 in the reserved area.
  /// </param>
  /// <returns>
  /// If big5_code_point is valid BIG5 code point or an ASCII code point,
  /// then a ON_Big5CodePoint instance with that value as code point is returned.
  /// Otherwise ON_Big5CodePoint::Error is returned.
  /// </returns>
  static const ON_Big5CodePoint Create(unsigned int big5_code_point);

  /// <summary>
  /// Find a BIG5 code point with the same character as unicode_code_point.
  /// </summary>
  /// <param name="unicode_code_point"></param>
  /// <param name="not_available">Value to return when unicode_code_point is valid but does not mapt to a BIG5 code point.</param>
  /// <returns>
  /// If there is a corresponding BIG5 or ASCII code point, that code point is returned.
  /// Otherwise, if unicode_code_point is valid, not_available is returned. 
  /// Otherwise ON_Big5CodePoint::Error is returned.
  /// </returns>
  static const ON_Big5CodePoint CreateFromUnicode(
    unsigned int unicode_code_point,
    ON_Big5CodePoint not_available
  );

  /// <summary>
  /// Find a BIG5 code point with the same character as unicode_code_point.
  /// </summary>
  /// <param name="unicode_code_point"></param>
  /// <param name="not_available">Value to return when unicode_code_point is valid but does not mapt to a BIG5 code point.</param>
  /// <returns>
  /// If there is a corresponding BIG5 or ASCII code point, that code point is returned.
  /// Otherwise, if unicode_code_point is valid, not_available is returned. 
  /// Otherwise ON_Big5CodePoint::Error is returned.
  /// </returns>
  static const ON_Big5CodePoint CreateFromUnicode(
    const class ON_UnicodeShortCodePoint& unicode_code_point,
    ON_Big5CodePoint not_available
  );

  /// <summary>
  /// Determine if this BIG5 code point is 0.
  /// </summary>
  /// <returns>True if the code point value is 0.</returns>
  bool IsNull() const;

  /// <summary>
  /// Strictly speaking, BIG5 does not extend ASCII, but it is common to mix 
  /// single bytes ASCII and double byte BIG5 encodings in the same char string.
  /// BIG5 is a double byte string encoding with the first byte in the range 0x81 to 0xFE, the
  /// minimum BIG5 code point is 0x8140 and the maximum BIG5 code point is 0xFEFE.
  /// Thus it is possible to mix ASCII and BIG5 encodings in the same char string.
  /// </summary>
  /// <param name="bNullIsASCII">
  /// Value to return if this BIG5 code point equal to ON_Big5CodePoint::Null. </param>
  /// <returns>
  /// True if the code point value &le= 0x7F.
  /// </returns>
  bool IsASCII(bool bNullIsASCII) const;

  /// <summary>
  /// Determine if the pair of code points is valid. 
  /// If the values for BIG5 and Unicode code point values are &lt 0xFF and equal, the pair is considered valid. 
  /// Use IsASCII() if you need to treat nonzero ASCII code points differently.
  /// </summary>
  /// <param name="bNullIsValid">
  /// Value to return if the code point value is 0.
  /// </param>
  /// <param name="bASCIICodePointIsValid">
  /// Value to return if the code point value is an ASCII code point (&lt= 0x7F).
  /// </param>
  /// <returns>True if the code point value is a valid BIG5 code point.</returns>
  bool IsValid(bool bNullIsValid, bool bASCIICodePointIsValid) const;

  /// <summary>
  /// BIG5 code points in the ranges0xA140-0xA3Bf, 0xA440-0xC67E, and 0xC940-0xF9D5 
  /// are standard code points.
  /// </summary>
  /// <param name="bNullIsValid">
  /// Value to return if the code point value is 0.
  /// </param>
  /// <param name="bASCIICodePointIsValid">
  /// Value to return if the code point value is an ASCII code point (&lt= 0x7F).
  /// </param>
  /// <returns>Returns true this BIG5 code point is a standard code point.</returns>
  bool IsStandard(bool bNullIsValid, bool bASCIICodePointIsValid) const;

  /// <summary>
  /// BIG5 code points in the ranges 0xC6A1-0xC8FE, 0xC6A1-0xC8FE, and 0xF9D6-0xFEFE 
  /// are for private use (user defined characters).
  /// </summary>
  /// <returns>True if this BIG5 code point is a private use (user defined) code point.</returns>
  bool IsPrivateUse() const;

  unsigned int Big5CodePoint() const;

  static int Compare(const ON_Big5CodePoint* lhs, const ON_Big5CodePoint* rhs);

private:
  ON__UINT16 m_big5_code_point = 0;
};

ON_DECL bool operator==(ON_Big5CodePoint lhs, ON_Big5CodePoint rhs);
ON_DECL bool operator!=(ON_Big5CodePoint lhs, ON_Big5CodePoint rhs);
ON_DECL bool operator<=(ON_Big5CodePoint lhs, ON_Big5CodePoint rhs);
ON_DECL bool operator>=(ON_Big5CodePoint lhs, ON_Big5CodePoint rhs);
ON_DECL bool operator<(ON_Big5CodePoint lhs, ON_Big5CodePoint rhs);
ON_DECL bool operator>(ON_Big5CodePoint lhs, ON_Big5CodePoint rhs);

#endif
#endif
