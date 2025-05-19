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

#include "opennurbs_textiterator.h"

static bool IsAtoZ(ON__UINT32 ch)
{
  return ( ch < 0xD800 && iswalpha((wchar_t)ch)) ? true : false;
}

//static bool IsHexDigit(ON__UINT32 ch)
//{
//  if ( '0' <= ch && ch <= '9')
//    return true;
//  if ( 'A' <= ch && ch <= 'F')
//    return true;
//  if ( 'a' <= ch && ch <= 'f')
//    return true;
//  return false;
//}

static bool IsDigit(ON__UINT32 ch)
{
  return ( ch < 0xD800 && iswdigit((wchar_t)ch)) ? true : false;
}

// Rtf tagnames
static const wchar_t* tagRtf                 = L"rtf";
static const wchar_t* tagFontTable           = L"fonttbl";
static const wchar_t* tagDefaultFont         = L"deff";
static const wchar_t* tagFont                = L"f";
static const wchar_t* tagFontSize            = L"fs";
static const wchar_t* tagCharSet             = L"fcharset";
static const wchar_t* tagCodePage            = L"cpg";

static const wchar_t* tagNewline             = L"line";
static const wchar_t* tagParagraph           = L"par";
static const wchar_t* tagParagraphDefaults   = L"pard";
static const wchar_t* tagSection             = L"sect";
static const wchar_t* tagTabulator           = L"tab";
                                    
static const wchar_t* tagBold                = L"b";
static const wchar_t* tagItalic              = L"i";
static const wchar_t* tagUnderLine           = L"ul";
static const wchar_t* tagUnderLineNone       = L"ulnone";
static const wchar_t* tagStrikeThrough       = L"strike";
                                    
static const wchar_t* tagSuperscript         = L"super";
static const wchar_t* tagSubscript           = L"sub";
static const wchar_t* tagNoSuperSub          = L"nosupersub";
                                    
//static const wchar_t* tagAlignLeft           = L"ql";
//static const wchar_t* tagAlignCenter         = L"qc";
//static const wchar_t* tagAlignRight          = L"qr";
//static const wchar_t* tagAlignJustify        = L"qj";
                                    
static const wchar_t* tagColorTable          = L"colortbl";
static const wchar_t* tagColorRed            = L"red";
static const wchar_t* tagColorGreen          = L"green";
static const wchar_t* tagColorBlue           = L"blue";
static const wchar_t* tagColorForeground     = L"cf";
static const wchar_t* tagColorBackground     = L"cb";
//static const wchar_t* tagColorBackgroundWord = L"chcbpat";
//static const wchar_t* tagColorHighlight      = L"highlight";

// Some Rhino specific optional tags
//static const wchar_t* tagExColorTable        = L"expandedcolortbl";
//static const wchar_t* tagTextHeight          = L"h";      // not rtf
static const wchar_t* tagStackFraction       = L"stackheight"; // not rtf - scale factor for text height in stacked text
static const wchar_t* tagStackText           = L"stack";  // not rtf - begin stacked fraction
static const wchar_t* tagStackEnd            = L"stnone"; // not rtf - end stacked fraction
static const wchar_t* tagField               = L"field";

static const wchar_t* tagUniCpCount          = L"uc";     // #bytes used following \uN for codepage code of equivalenet char

static const wchar_t* tagUniCharDec          = L"u";      // UNICODE UTF-16 encoded value as a signed short (0x8...) will be -....
                                                          // NOTE WELL: When a single UNICODE code point requires a UTF-16
                                                          // surrogate pair encoding, there will be TWO \uXXXX? values for that code point.
                                                          // For example, the single UNICODE code point 
                                                          // ON_UnicodeCodePoint::Wastebasket U+1F5D1 (decimal 128465)
                                                          // The UTF-16 surrogate pair for U+1F5D1 is (0xD83D, 0xDDD1) and this 
                                                          // value in RTF looks like ...{\ltrch \u-10179?\u-8751?}...
                                                          // -10179 as a signed 2 byte short has the same bits as unsigned short 0xD83D.
                                                          // -8751 as a signed 2 byte short has the same bits as unsigned short 0xDDD1.
                                                          // Many "emoji glyphs" UNICODE code points require UTF-16 surrogate pair encodings.

static const wchar_t* tagUniTwoDest          = L"upr";    // two embedded unicode destinations

static const wchar_t* tagUniDest             = L"ud";     // unicode destination

// Characters typed with Alt+0123
// \lquote \rquote  \ldblquote  \rdblquote  \bullet  \endash  \emdash
static const wchar_t* taglquote              = L"lquote";        // left quote
static const wchar_t* tagrquote              = L"rquote";        // right quote
static const wchar_t* tagldblquote           = L"ldblquote";     // left double quote
static const wchar_t* tagrdblquote           = L"rdblquote";     // right double quote
static const wchar_t* tagbullet              = L"bullet";        // bullet
static const wchar_t* tagendash              = L"endash";        // endash
static const wchar_t* tagemdash              = L"emdash";        // emdash


#pragma region TextIterator

ON_TextIterator::ON_TextIterator(const ON_wString& str)
  : m_text(str.Array())
  , m_length(str.Length())
{
  Step(); //  Make first character in the string current
}

ON_TextIterator::ON_TextIterator(const wchar_t* str, size_t length)
  : m_text(str)
  , m_length(length)
{
  Step(); //  Make first character in the string current
}

bool ON_TextIterator::Step()
{
  // Get the next UNICODE code point encoded in m_text beginning at m_text[m_next_text_ci];
  // Save this code point in m_cur_codepoint.
  if(m_next_text_ci < m_length)
  {
    m_ue.m_error_status = 0;
    ON__UINT32 codepoint = 0;
    
    // Works on Windows, Apple, and any other platform.
    const int ci = ON_DecodeWideChar((m_text+m_next_text_ci), (int)(m_length-m_next_text_ci), &m_ue, &codepoint);

    if(ci > 0)
    {
      m_prev_text_ci = m_cur_text_ci;
      m_cur_text_ci = m_next_text_ci;
      m_next_text_ci = m_next_text_ci+ci;
      m_prev_codepoint = m_cur_codepoint;
      m_cur_codepoint = codepoint;
      return true;
    }
  }

  m_prev_codepoint = m_cur_codepoint;
  m_cur_codepoint = 0;

  return false;
}

bool ON_TextIterator::PeekCodePoint(ON__UINT32& unicode_code_point) const
{
  unicode_code_point = m_cur_codepoint;
  return (0 != unicode_code_point);
}

bool ON_TextIterator::ReadCodePoint(ON__UINT32& unicode_code_point)
{
  unicode_code_point = m_cur_codepoint;
  Step();
  return (0 != unicode_code_point);
}

bool ON_TextIterator::Back()
{
  if(m_prev_text_ci == m_cur_text_ci)
  {
    // fancy backup in wchar_t string
  }
  m_next_text_ci = m_cur_text_ci;
  m_cur_text_ci = m_prev_text_ci;
  m_cur_codepoint = m_prev_codepoint;
  return true;
}

static bool Internal_IsHexDigit(ON__UINT32 x)
{
  return ((x >= '0' && x <= '9') || (x >= 'A' && x <= 'F') || (x >= 'a' && x <= 'f'));
}

static ON__UINT32 Internal_IsHexValue(ON__UINT32 x)
{
  if (x >= '0' && x <= '9')
    return (x - '0');
  if (x >= 'A' && x <= 'F')
    return x - 'A' + 10;
  if (x >= 'a' && x <= 'f')
    return x - 'a' + 10;
  return 0xFFFFFFFF;
}

bool ON_TextIterator::AtBackslashTic() const
{
  return (
    ON_UnicodeCodePoint::ON_Backslash == m_cur_codepoint
    && m_next_text_ci < m_length
    && '\'' == m_text[m_next_text_ci]
    );
}

bool ON_TextIterator::ReadCharValue(
  unsigned char& c
)
{
  for(;;)
  {
    ON__UINT32 buffer[4];
    if (false == ReadCodePoint(buffer[0]))
      break;
    if (ON_UnicodeCodePoint::ON_Backslash != buffer[0])
      break;
    if (false == ReadCodePoint(buffer[1]))
      break;
    if ('\'' != buffer[1])
      break;
    if (false == ReadCodePoint(buffer[2]))
      break;
    if (false == Internal_IsHexDigit(buffer[2]))
      break;
    if (false == ReadCodePoint(buffer[3]))
      break;
    if (false == Internal_IsHexDigit(buffer[3]))
      break;
    ON__UINT32 x = 16 * Internal_IsHexValue(buffer[2]) + Internal_IsHexValue(buffer[3]);
    if (x > 255)
      break;
    c = (unsigned char)x;
    return true;
  }
  c = 0;
  return false;
}

ON__UINT32 ON_RtfParser::Internal_ParseMBCSString( const ON__UINT32 windows_code_page )
{
  ON__UINT32 count = 0;
  bool bParsed = false;
  ON_String mbcs;
  mbcs.ReserveArray(64);
  while (m_ti.AtBackslashTic())
  {
    count++;
    unsigned char c;
    bParsed = m_ti.ReadCharValue(c);
    if (false == bParsed)
      break;
    mbcs.Append((const char*)(&c), 1);
  }

  const char* sMBCS = static_cast<const char*>(mbcs);
  int sMBCS_count = mbcs.Length();
  wchar_t* sWideChar = nullptr;
  int sWideChar_capacity = 0;
  unsigned int error_status = 0;

  if (nullptr != sMBCS && 0 != sMBCS[0] && sMBCS_count > 0)
  {
    const int sWideChar_count0 = ON_ConvertMSMBCPToWideChar(
      windows_code_page,
      sMBCS,
      sMBCS_count,
      sWideChar,
      sWideChar_capacity,
      &error_status
    );

    if (sWideChar_count0 > 0)
    {
      sWideChar_capacity = sWideChar_count0 + 2;
      sWideChar = new wchar_t[sWideChar_capacity];
      if (nullptr != sWideChar)
      {
        memset(sWideChar, 0, sWideChar_capacity * sizeof(sWideChar[0]));
      }
      error_status = 0;
      const int sWideChar_count1 = ON_ConvertMSMBCPToWideChar(
        windows_code_page,
        sMBCS,
        sMBCS_count,
        sWideChar,
        sWideChar_capacity-1,
        &error_status
      );

      if (sWideChar_count1 > 0 && 0 != sWideChar[0] && 0 == sWideChar[sWideChar_capacity - 1])
      {
        int delta_i = sWideChar_count1;
        for (int i = 0; i < sWideChar_count1; i += delta_i)
        {
          struct ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::MaskErrors;
          ON__UINT32 unicode_code_point = ON_UnicodeCodePoint::ON_ReplacementCharacter;
          delta_i = ON_DecodeWideChar(sWideChar + i, sWideChar_count1 - i, &e, &unicode_code_point);
          if (delta_i <= 0)
          {
            bParsed = false;
            break;
          }
          m_builder.AppendCodePoint(unicode_code_point);
        }
      }
      delete[] sWideChar;
      sWideChar = nullptr;
    }
  }

  if (false == bParsed)
    m_builder.AppendCodePoint(ON_UnicodeCodePoint::ON_ReplacementCharacter);

  return count;
}

#pragma endregion TextIterator

#pragma region TextBuilder

ON_TextBuilder::~ON_TextBuilder()
{}

ON_TextBuilder::ON_TextBuilder()
  : m_current_codepoints(16)
{
  m_current_UTF16_buffer_count = 0;
  m_current_UTF16_buffer[0] = 0;
  m_current_UTF16_buffer[1] = 0;
}

void ON_TextBuilder::InitBuilder(const ON_Font* default_font)
{
  m_in_run = 0;
  m_level = 0;
  m_font_table_level = 100000;
  m_current_codepoints.Empty();
}

void ON_TextBuilder::GroupBegin()
{
  m_level++;
}

void ON_TextBuilder::GroupEnd()
{
  //if(m_font_table_level >= m_level)
  //  m_font_table_level = -1;
  m_level--;
}

void ON_TextBuilder::RunBegin()
{
}

void ON_TextBuilder::RunEnd()
{
}

bool ON_TextBuilder::ReadingFontTable()
{
  return (m_level >= m_font_table_level);
}

bool ON_TextBuilder::ReadingFontDefinition()
{
  return m_bReadingFontDefinition;
}

void ON_TextBuilder::SetReadingFontDefinition(bool b)
{
  m_bReadingFontDefinition = b;
}

void ON_TextBuilder::FinishFontDef()
{
  SetReadingFontDefinition(false);
}

void ON_TextBuilder::FlushText(size_t count, ON__UINT32* cp)
{
}

void ON_TextBuilder::BeginFontTable()
{
  m_font_table_level = m_level;
}

void ON_TextBuilder::BeginHeader()
{
}

// Sets m_default_font_index when \deffn is read.
void ON_TextBuilder::DefaultFont(const wchar_t* value)
{
  ON__INT32 nval = -1;
  const wchar_t* sp = ON_wString::ToNumber(value, nval, &nval);
  if(nval >= 0 && sp > value)
    m_default_font_index = nval;
}

// Process a rtf \fn tag to set the current font to the nth font in the rtf font table
void ON_TextBuilder::FontTag(const wchar_t* value)
{
  ON__INT32 nval = -1;
  const wchar_t* sp = ON_wString::ToNumber(value, nval, &nval);
  if(nval >= 0 && sp > value)
  {
    //if(m_font_table_level >= 0 && 
    //   m_level >= m_font_table_level)
    if(ReadingFontTable())
    {
      // Defining a font in the font table
      // n in \fn is the rtf index of the font currently being read from the table
      // store a mapping from \fn to font
      // when the font for this font table entry is made
      m_font_index = nval;
      // next will be a face name that will be read and put in a fontdef run
    }
    //else
    //{
    //  // Not defining the font table. Rather, setting a font current
    //  // Set current font to font corresponding to font_index
    //}
  }
  return;
}

const ON_wString ON_TextBuilder::FaceNameFromMap(int nval)
{
  int count = m_facename_map.Count();
  for (int mi = 0; mi < count; mi++)
  {
    if (m_facename_map[mi].m_rtf_font_index == nval)
      return m_facename_map[mi].m_rtf_font_name;
  }
  return ON_wString::EmptyString;
}

unsigned int ON_TextBuilder::CodePageFromMap(int nval)
{
  int count = m_facename_map.Count();
  for (int mi = 0; mi < count; mi++)
  {
    if (m_facename_map[mi].m_rtf_font_index == nval)
      return m_facename_map[mi].m_codepage;
  }
  return 1252;
}

unsigned int ON_TextBuilder::CharSetFromMap(int nval)
{
  int count = m_facename_map.Count();
  for (int mi = 0; mi < count; mi++)
  {
    if (m_facename_map[mi].m_rtf_font_index == nval)
      return m_facename_map[mi].m_charset;
  }
  return 0;
}

void ON_TextBuilder::FontSize(const wchar_t* value)
{
}

void ON_TextBuilder::CharSet(const wchar_t* value)  // \fcharsetN
{
  unsigned int charset = 0;
  const wchar_t* sp = ON_wString::ToNumber(value, charset, &charset);
  if (sp > value)
  {
    //if (m_font_table_level >= 0 && m_level >= m_font_table_level)
    if(ReadingFontDefinition())
    {
      // This is a charset specification in a font definition in the font table
      // the value is convertible to a codepage to use for interpreting the text chars
      // using this font into unicode points
      m_current_props.SetCharSet(charset, true);
    }
  }
}

void ON_TextBuilder::CodePage(const wchar_t* value)  // \cpgN
{
  unsigned int codepage = 0;
  const wchar_t* sp = ON_wString::ToNumber(value, codepage, &codepage);
  if (sp > value)
  {
    //if (m_font_table_level >= 0 && m_level >= m_font_table_level)
    if(ReadingFontDefinition())
    {
      // This is a codepage specification in a font definition in the font table
      m_current_props.SetCodePage(codepage);
    }
  }
}

void ON_TextBuilder::Newline()
{
}

void ON_TextBuilder::Paragraph()
{
}

void ON_TextBuilder::ParagraphDefaults()
{
}

void ON_TextBuilder::Section()
{
}

void ON_TextBuilder::Tab()
{
}

void ON_TextBuilder::Bold(const wchar_t* value)
{
}

void ON_TextBuilder::Italic(const wchar_t* value)
{
}

void ON_TextBuilder::UnderlineOn()
{
}

void ON_TextBuilder::UnderlineOff()
{
}

void ON_TextBuilder::Strikethrough(const wchar_t* value)
{
}

void ON_TextBuilder::Superscript()
{
}

void ON_TextBuilder::Subscript()
{
}

void ON_TextBuilder::NoSuperSub()
{
}

void ON_TextBuilder::BeginColorTable()
{
}

void ON_TextBuilder::ColorRed(const wchar_t* value)
{
}

void ON_TextBuilder::ColorGreen(const wchar_t* value)
{
}

void ON_TextBuilder::ColorBlue(const wchar_t* value)
{
}

void ON_TextBuilder::ColorForeground(const wchar_t* value)
{
}

void ON_TextBuilder::ColorBackground(const wchar_t* value)
{
}

void ON_TextBuilder::SetStackScale(const wchar_t* value)
{
}

void ON_TextBuilder::StackFraction(const wchar_t* value)
{
}

void ON_TextBuilder::StackEnd()
{
}

void ON_TextBuilder::TextField(const wchar_t* name)
{
}

ON__UINT32* ON_TextBuilder::RunCodePoints(const ON_TextRun& run)
{
  return run.m_codepoints;
}

void ON_TextBuilder::UniCpCount(const wchar_t* value)
{
  // Dale Lear April 2018 - This code does absolutely nothing useful- commenting all of it out.

  //// #bytes used following \uN for codepage code of equivalenet char
  //short count = 1, d = ON_DBL_QNAN;
  //const wchar_t* sp = ON_wString::ToNumber(value, d, &d);
  //if (sp > value)
  //  count = d;
}

void ON_TextBuilder::UniDecimal(const wchar_t* value)
{
  // UTF-16 encoding value as a decimal, possibly signed negative
  // unicode char in decimal followed by ascii char(s) (to skip if unicode can't be digested) :
  // \u1472? means char at unicode point 1472, or '?' as a fallback ascii char to substitute.
  // the decimal value may be written as a negative number: \u-2671? and should be cast to unsigned.

  ON__UINT16 u = 0;
  const wchar_t* sp = nullptr;
  for (;;)
  {
    // For example, the single UNICODE code point ON_UnicodeCodePoint::Wastebasket U+1F5D1 (decimal 128465)
    //
    // As of March 2018:
    //  RTF from Windows 10 controls are using signed shorts with question mark as the ASCII fallback char
    //    Wastebasket = "\u-10179?\u-8751?"
    //      \u-10179? -> unsigned short 0xD83D
    //      \u-8751?  -> unsigned short 0xDDD1
    //      UTF-16 surrogate pair is (0xD83D, 0xDDD1) -> U+1F5D1 = UNICODE wastebasket glyph
    //  RTF from MacOS controls are using unsigned shorts with a space as the ASCII fallback char
    //    Wastebasket = "\u55357 \u56785 "
    //      \u55357  -> unsigned short 0xD83D
    //      \u56785  -> unsigned short 0xDDD1
    //      UTF-16 surrogate pair is (0xD83D, 0xDDD1) -> UNICODE code point U+1F5D1 = wastebasket glyph

    short signed_short = 0;
    sp = ON_wString::ToNumber(value, signed_short, &signed_short);
    if (nullptr != sp && sp > value)
    {
      // value is either positive or a negative in short range
      u = (unsigned short)signed_short;
      break;
    }
    
    unsigned short unsigned_short = 0;
    sp = ON_wString::ToNumber(value, unsigned_short, &unsigned_short);
    if (nullptr != sp && sp > value && unsigned_short > 32767)
    {
      // value is a unsigned short too large to be a signed short.
      u = unsigned_short;
      break;
    }

    if (0 == m_current_UTF16_buffer_count)
    {
      // No doubt, we will eventually encounter RTF will using unsigned UTF-32 values.
      unsigned int u32 = 0;
      sp = ON_wString::ToNumber(value, u32, &u32);
      if (nullptr != sp && sp > value && u32 > 0xffff && ON_IsValidUnicodeCodePoint(u32) )
      {
        // value is a unsigned int too large to be an unsigned short.
        AppendCodePoint(u32);
        return;
      }
    }

    // probably an error in the RTF or a bug in this parsing code.
    sp = nullptr;
    break;
  }

  // Often *sp = '?' (question mark) on Windows and ' ' (space) on MacOS, 
  // but that is not required if some other ASCII fallback char is used.
  if (nullptr != sp && sp > value)
  {
    bool bError = false;
    const ON__UINT32 error_cp = ON_UnicodeCodePoint::ON_ReplacementCharacter;

    const ON__UINT16 waiting_mark = ON_TextBuilder::m_UFT16_waiting_mark;
    const ON__UINT16 unused_mark  = ON_TextBuilder::m_UFT16_unused_mark;

    const bool bHaveFirstSurrogate
      = (1 == m_current_UTF16_buffer_count
        && m_current_UTF16_buffer[0] >= 0xD800
        && m_current_UTF16_buffer[0] < 0xDC00
        && waiting_mark == m_current_UTF16_buffer[1]);

    ON__UINT32 cp = 0;
    // Mar 3, 2017 Dale Lear
    //   Attempt to support handling of UTF-16 surrogate pairs without
    //   rewriting the RTF parser.
    // For example, the single UNICODE code point ON_UnicodeCodePoint::Wastebasket U+1F5D1 (decimal 128465)
    // is in the RTF string as ...{\ltrch \u-10179?\u-8751?}...
    // The UTF-16 surrogate pair is (0xD83D, 0xDDD1) and this value decodes to the single UNICODE code point U+1F5D1
    //   \u-10179? -> unsigned short 0xD83D
    //   \u-8751?  -> unsigned short 0xDDD1
    if (u >= 0xD800 && u < 0xDC00)
    {
      if (bHaveFirstSurrogate)
      {
        // never got the second value for the pair
        //m_current_codepoints.Append(error_cp);
        AppendCodePoint(error_cp);
      }

      if (0 == m_current_UTF16_buffer_count)
      {
        m_current_UTF16_buffer_count = 1;
        m_current_UTF16_buffer[0] = u;
        m_current_UTF16_buffer[1] = waiting_mark;
        return; // we need the second surrogate pair value before we can decode
      }

      bError = true;
    }
    else if (u >=  0xDC00 && u < 0xE000)
    {
      if (bHaveFirstSurrogate)
      {
        m_current_UTF16_buffer_count = 2;
        m_current_UTF16_buffer[1] = u;
      }
      else
      {
        // We should have gotten the second value for the pair
        bError = true;
      }
    }
    else
    {
      if (bHaveFirstSurrogate)
      {
        // never got the second value for the pair
        m_current_codepoints.Append(error_cp);
      }
      m_current_UTF16_buffer_count = 1;
      m_current_UTF16_buffer[0] = u;
      m_current_UTF16_buffer[1] = unused_mark;
    }

    if (false == bError)
    {
      ON_UnicodeErrorParameters e;
      e.m_error_code_point = error_cp;
      e.m_error_mask = 16;
      e.m_error_status = 0;
      const int rc = ON_DecodeUTF16(m_current_UTF16_buffer, m_current_UTF16_buffer_count, &e, &cp);
      bError = (m_current_UTF16_buffer_count != rc || false == ON_IsValidUnicodeCodePoint(cp));
    }

    if (bError)
      cp = error_cp;
    //m_current_codepoints.Append(cp);
    AppendCodePoint(cp);

    m_current_UTF16_buffer_count = 0;
    m_current_UTF16_buffer[0] = unused_mark;
    m_current_UTF16_buffer[1] = unused_mark;
  }
}

void ON_TextBuilder::UniEmbeddedDest(const wchar_t* value)
{
  // two embedded unicode destinations - footnote, etc in rtf document
}

void ON_TextBuilder::UniDest(const wchar_t* value)
{
  // unicode destination
}

void ON_TextBuilder::LQuote()
{
  m_current_codepoints.Append(0x2018);
}

void ON_TextBuilder::RQuote()
{
  m_current_codepoints.Append(0x2019);
}

void ON_TextBuilder::LDblQuote()
{
  m_current_codepoints.Append(0x201c);
}

void ON_TextBuilder::RDblQuote()
{
  m_current_codepoints.Append(0x201d);
}

void ON_TextBuilder::Bullet()
{
  m_current_codepoints.Append(0x2022);
}

void ON_TextBuilder::EnDash()
{
  m_current_codepoints.Append(0x2013);
}

void ON_TextBuilder::EmDash()
{
  m_current_codepoints.Append(0x2014);
}

bool ON_TextBuilder::AppendCodePoint(ON__UINT32 codept)
{
  m_current_codepoints.Append(codept);
  return true;
}

void ON_TextBuilder::FormatChange()
{

}

#pragma endregion  // TextBuilder



#pragma region TextRunBuilder

ON_TextRunBuilder::~ON_TextRunBuilder()
{}

ON_TextRunBuilder::ON_TextRunBuilder(
  ON_TextContent& text,
  ON_TextRunArray& runs,
  const ON_DimStyle* dimstyle,
  double height,
  ON_Color color)
  : m_runs(runs)
  , m_text(text)
{
  m_current_UTF16_buffer_count = 0;
  m_current_UTF16_buffer[0] = 0;
  m_current_UTF16_buffer[1] = 0;

  if (nullptr == dimstyle)
    dimstyle = &ON_DimStyle::Default;
  const ON_Font& style_font = dimstyle->Font();  // this is always a managed font
  double stackscale = dimstyle->StackHeightScale();
  ON_DimStyle::stack_format stackformat = dimstyle->StackFractionFormat();
  bool bold = dimstyle->Font().IsBoldInQuartet();
  bool italic = dimstyle->Font().IsItalic();
  bool underlined = dimstyle->Font().IsUnderlined();
  bool strikethrough = dimstyle->Font().IsStrikethrough();

  this->SetCurrentFont(&style_font);
  m_current_props.SetColor(color);
  m_current_props.SetHeight(height);
  m_current_props.SetStackScale(stackscale);
  m_current_props.SetStackFormat(stackformat);
  m_current_props.SetBold(bold);
  m_current_props.SetItalic(italic);
  m_current_props.SetUnderlined(underlined);
  m_current_props.SetStrikethrough(strikethrough);

  m_current_run.Init(
    CurrentFont(),
    height,
    stackscale,
    color,
    bold,
    italic,
    underlined,
    strikethrough);
}

void ON_TextRunBuilder::InitBuilder(const ON_Font* default_font)
{
  if (nullptr == default_font)
    default_font = &ON_Font::Default;
  if (nullptr == default_font)
    return;
  this->SetCurrentFont(default_font);  // copy of default_font

  m_in_run = 0;
  m_level = 0;
  m_font_table_level = 10000;
  m_runs = ON_TextRunArray::EmptyArray;
  m_current_run.Init(this->CurrentFont(), m_current_props.Height(), m_current_props.StackScale(), m_current_props.Color(),
    m_current_props.IsBold(), m_current_props.IsItalic(), m_current_props.IsUnderlined(), m_current_props.IsStrikethrough());
  // Array for accumulating text codepoints
  m_current_codepoints.Empty();
}

void ON_TextRunBuilder::AppendCurrentRun()
{
  //if(m_current_run.IsValid())
  {
    ON_TextRun* run = ON_TextRun::GetManagedTextRun(m_current_run);
    if (0 != run)
    {
      m_runs.AppendRun(run);
    }
    m_current_run.Init(this->CurrentFont(), m_current_props.Height(), m_current_props.StackScale(), m_current_props.Color(),
      m_current_props.IsBold(), m_current_props.IsItalic(), m_current_props.IsUnderlined(), m_current_props.IsStrikethrough());
  }
}

bool ON_TextRunBuilder::AppendCodePoint(ON__UINT32 codept)
{
  if (m_current_codepoints.Count() == 0 && m_current_run.IsStacked() != ON_TextRun::Stacked::kStacked)
  {
    const ON_TextRun::Stacked stacked = m_current_run.IsStacked();

    // First codepoint in a run after format changes
    m_current_run.Init(this->CurrentFont(), m_current_props.Height(), m_current_props.StackScale(), m_current_props.Color(),
      m_current_props.IsBold(), m_current_props.IsItalic(), m_current_props.IsUnderlined(), m_current_props.IsStrikethrough());

    if (ON_TextRun::Stacked::kTop == stacked || ON_TextRun::Stacked::kBottom == stacked)
    {
      m_current_run.SetStacked(stacked);
    }
  }
  m_current_codepoints.Append(codept);
  return true;
}

void ON_TextRunBuilder::FormatChange()
{
  int cp32_count = m_current_codepoints.Count();
  if (cp32_count > 0)
  {
    FlushText(cp32_count, m_current_codepoints.Array());
    m_current_codepoints.Empty();
    FinishCurrentRun();
  }
}

#ifndef ON_TEXT_BRACKET_FRACTION
static bool FindFrac(const wchar_t* wstr, int start, int spos, int& topstart, int& bottomend)
{
  if (spos < start + 1)
    return false;
  int len = (int)wcslen(wstr);
  if (spos > len - 2)
    return false;
  topstart = spos;
  bottomend = spos;
  for (int i = spos; i > start && isdigit(wstr[i - 1]); i--)
  {
    topstart = i - 1;
  }
  bottomend = spos;
  for (int i = spos; i < len - 1 && isdigit(wstr[i + 1]); i++)
  {
    bottomend = i + 1;
  }
  if (topstart == spos || bottomend == spos)
    return false;

  if (topstart > start + 2 && isdigit(wstr[topstart - 2]))
  {//drop leading space
  }
  if (bottomend < len - 2 && isdigit(wstr[bottomend + 2]))
  {// drop trailing space
  }
  return true;
}

typedef struct tagFract
{
  int start;
  int slash;
  int end;
} Fraction;

static void FindFractions(ON_TextRun* run, ON_SimpleArray<Fraction>& fractlist)
{
  if (nullptr == run)
    return;
  size_t cpcount = ON_TextRun::CodepointCount(run->UnicodeString());
  if (0 != cpcount)
  {
    ON_wString str;
    ON_TextContext::ConvertCodepointsToString((int)cpcount, run->UnicodeString(), str);
    if (!str.IsEmpty())
    {
      const wchar_t* wstr = str.Array();
      int len = str.Length();
      int start = 0;
      int topstart = -1;
      int bottomend = -1;
      int i = 0;
      while (i < len && 0 != wstr[i])
      {
        if (wstr[i] == L'/')
        {
          if (FindFrac(wstr, start, i, topstart, bottomend))
          {
            Fraction& fract = fractlist.AppendNew();
            fract.start = topstart;
            fract.end = bottomend;
            fract.slash = i;
            i = bottomend;
            start = bottomend + 1;
          }
        }
        i++;
      }
    }
  }
}
#endif

void ON_TextRunBuilder::FinishCurrentRun()
{
  //int cplen = m_current_run.m_codepoint_idx.j - m_current_run.m_codepoint_idx.i;
  if (m_current_run.Type() == ON_TextRun::RunType::kText ||
    m_current_run.Type() == ON_TextRun::RunType::kField ||
    m_current_run.Type() == ON_TextRun::RunType::kNewline ||
    m_current_run.Type() == ON_TextRun::RunType::kParagraph)
  {
    // Finish off the text run - 
    // Text string is already stored in m_codepoints
    // Find or make a managed font like the current one
    // and store that pointer on the run
    if (nullptr == this->CurrentFont())
      this->SetCurrentFont(&ON_Font::Default);

    const ON_Font* pManagedFont = this->CurrentFont()->ManagedFont();

    if (nullptr != pManagedFont)
    {
      m_current_run.SetFont(pManagedFont);
      m_current_run.SetColor(m_current_props.Color());
      m_current_run.SetTextHeight(m_current_props.Height());
      m_current_run.SetStackFractionHeight(m_current_props.StackScale());
    }
#ifndef ON_TEXT_BRACKET_FRACTION
    ON_SimpleArray<Fraction> fractlist;
    int fcount = 0;
    if (ON_DimStyle::stack_format::None != m_current_props.StackFormat())
    {
      FindFractions(&m_current_run, fractlist);
      fcount = fractlist.Count();
    }
    if (0 < fcount)
    {
      int cpos = 0;
      int cpcount = (int)ON_TextRun::CodepointCount(m_current_run.m_codepoints);
      ON__UINT32* cpts = (ON__UINT32*)onmalloc((1 + cpcount) * sizeof(ON__UINT32));
      memcpy(cpts, m_current_run.m_codepoints, (1 + cpcount) * sizeof(ON__UINT32));
      for (int i = 0; i < fcount; i++)
      {
        Fraction& f = fractlist[i];
        if (f.start >= cpos)
        {
          int k = f.start;
          // If the last char before the fraction is a space
          // and the char before that is a digit, drop the space
          if (f.start > 1 && isdigit(cpts[f.start - 1]))
            k = f.start - 1;
          m_current_run.SetUnicodeString(k - cpos, cpts + cpos);
          AppendCurrentRun();

          cpos = f.start;
          m_current_run.SetUnicodeString(f.end - f.start + 1, cpts + cpos);
          if (m_current_props.StackFormat() != ON_DimStyle::stack_format::None)
            m_current_run.SetStacked(ON_TextRun::Stacked::kStacked);
          else
            m_current_run.SetStacked(ON_TextRun::Stacked::kNone);
          AppendCurrentRun();
          m_current_run.SetStacked(ON_TextRun::Stacked::kNone);
          cpos = f.end + 1;
        }
      }
      if (cpos < cpcount)
      {
        m_current_run.SetUnicodeString(cpcount - cpos, cpts + cpos);
        AppendCurrentRun();
      }
    }
    else

#endif // 0
      AppendCurrentRun();
  }
}

static bool IsValidFontName(const ON_wString&  name)
{
  // Test to prevent making fonts named "(varies)"
  if (L'(' == name[0] && L')' == name[name.Length()-1])
    return false;
  return true;
}

void ON_TextRunBuilder::FinishFontDef()
{
  if (ReadingFontDefinition())
  {
    int cp32_count = m_current_codepoints.Count();
    if (cp32_count > 0)
    {
      FlushText(cp32_count, m_current_codepoints.Array());
      m_current_codepoints.Empty();
    }
    // String is a font "facename" (In reality the "facename" it can be a PostScript name, a LOGFONT.lfFaceName,
    // or a DWrite family name - depending on who is making the RTF). 
    // Make a font with that facename and a font definition run 
    size_t cpcount = ON_TextRun::CodepointCount(RunCodePoints(m_current_run));
    if (0 != cpcount)
    {
      ON_wString rtf_fontname_string;
      ON_TextContext::ConvertCodepointsToString((int)cpcount, RunCodePoints(m_current_run), rtf_fontname_string);
      if (!rtf_fontname_string.IsEmpty())
      {
        rtf_fontname_string.Remove(L';');  // facename delimiter from rtf

        if (!IsValidFontName(rtf_fontname_string))
        {
          ON_ERROR("Invalid font name found in rtf string");
          rtf_fontname_string = ON_Font::Default.RichTextFontName();
          if (rtf_fontname_string.IsEmpty())
            rtf_fontname_string = L"Arial";
        }

        // Dale Lear - March 2021 - RH-62974
        // There are multiple places in the text run, rich text parsing, and Rhino UI code
        // that need find a font from rich text properties.
        // They must all do it the same way. If for some reason, you must change this call,
        // please take the time to create a single function that replaces this call, search
        // for all the places ON_Font::FontFromRichTextProperties is called in
        //  src4/rhino/... 
        //  opennurbs_textrun.cpp
        //  opennurbs_textiterator.cpp
        // and replace every call to ON_Font::FontFromRichTextProperties with a call to
        // your new function.
        // 
        // This needs to be the regular face of the rich text quartet.
        const ON_Font* managed_font = ON_Font::FontFromRichTextProperties(rtf_fontname_string,false,false,false,false);

        if (nullptr == managed_font)
          managed_font = &ON_Font::Default;

        rtf_fontname_string = managed_font->RichTextFontName();

        ON_FaceNameKey& fn_key = m_facename_map.AppendNew();
        fn_key.m_rtf_font_index = m_font_index;
        fn_key.m_rtf_font_name = rtf_fontname_string;
        fn_key.m_codepage = m_current_props.CodePage();
        fn_key.m_charset = m_current_props.CharSet();
      }
    }

    if (m_current_run.Type() == ON_TextRun::RunType::kFontdef && m_level == m_font_table_level)
    {
      if (m_font_stack.Count() > 0 && m_prop_stack.Count() > 0)
      {
        this->SetCurrentFont(*m_font_stack.Last());  // pop
        m_font_stack.Remove();
        m_current_props = *m_prop_stack.Last(); // pop
        m_prop_stack.Remove();
      }
      m_current_run.Init(this->CurrentFont(), m_current_props.Height(), m_current_props.StackScale(), m_current_props.Color(),
        m_current_props.IsBold(), m_current_props.IsItalic(), m_current_props.IsUnderlined(), m_current_props.IsStrikethrough());
    }
    SetReadingFontDefinition(false);
  }
}

void ON_TextRunBuilder::GroupBegin()  // {
{
  int cp32_count = m_current_codepoints.Count();
  if (cp32_count > 0)
  {
    FlushText(cp32_count, m_current_codepoints.Array());
    m_current_codepoints.Empty();
  }
  FinishCurrentRun();

  m_level++;
  // m_current_font starts out as the value from the text object
  m_font_stack.Append(this->CurrentFont());    // push prev current font
  m_prop_stack.Append(m_current_props);   // push prev current height and color

  m_current_run.Init(this->CurrentFont(), m_current_props.Height(), m_current_props.StackScale(), m_current_props.Color(),
    m_current_props.IsBold(), m_current_props.IsItalic(), m_current_props.IsUnderlined(), m_current_props.IsStrikethrough());
}


void ON_TextRunBuilder::GroupEnd()   // '}'
{
  int cp32_count = m_current_codepoints.Count();
  if (cp32_count > 0)
  {
    FlushText(cp32_count, m_current_codepoints.Array());
    m_current_codepoints.Empty();
  }
  FinishCurrentRun();
  // Pop font and set up for next run
  if (m_font_stack.Count() > 0 && m_prop_stack.Count() > 0)
  {
    this->SetCurrentFont(*m_font_stack.Last());  // pop
    m_font_stack.Remove();
    m_current_props = *m_prop_stack.Last(); // pop
    m_prop_stack.Remove();
  }
  m_current_run.Init(this->CurrentFont(), m_current_props.Height(), m_current_props.StackScale(), m_current_props.Color(),
    m_current_props.IsBold(), m_current_props.IsItalic(), m_current_props.IsUnderlined(), m_current_props.IsStrikethrough());

  if (m_level <= m_font_table_level)
    m_font_table_level = 10000;
  m_level--;
}

void ON_TextRunBuilder::RunBegin()  // like { with no pushing properties
{
  int cp32_count = m_current_codepoints.Count();
  if (cp32_count > 0)
  {
    FlushText(cp32_count, m_current_codepoints.Array());
    m_current_codepoints.Empty();
  }
  FinishCurrentRun();

  m_current_run.Init(this->CurrentFont(), m_current_props.Height(), m_current_props.StackScale(), m_current_props.Color(),
  m_current_props.IsBold(), m_current_props.IsItalic(), m_current_props.IsUnderlined(), m_current_props.IsStrikethrough());
}


void ON_TextRunBuilder::RunEnd()   // like '}' with no popping properties
{
  int cp32_count = m_current_codepoints.Count();
  if (cp32_count > 0)
  {
    FlushText(cp32_count, m_current_codepoints.Array());
    m_current_codepoints.Empty();
  }
  FinishCurrentRun();
  
  m_current_run.Init(this->CurrentFont(), m_current_props.Height(), m_current_props.StackScale(), m_current_props.Color(),
    m_current_props.IsBold(), m_current_props.IsItalic(), m_current_props.IsUnderlined(), m_current_props.IsStrikethrough());

  if (m_level <= m_font_table_level)
    m_font_table_level = 10000;
}

void ON_TextRunBuilder::FlushText(size_t count, ON__UINT32* cp)
{
  if (count < 1 || 0 == cp || 0 == cp[0])
    return;

  m_current_run.SetUnicodeString(count, cp);
  if(ReadingFontDefinition())
  {
    // String is a rich text facename. Make a font from that rich text facename and a font definition run 
    m_current_run.SetType(ON_TextRun::RunType::kFontdef);

    ON_wString str;
    ON_TextContext::ConvertCodepointsToString((int)count, cp, str);
    if (!str.IsEmpty())
    {
      str.Remove(L';');  // facename delimiter from rtf
      m_current_run.SetType(ON_TextRun::RunType::kFontdef);
      // This is a face name in the rich text font definition table.
      // We do not have an bold/italic/underline/strikethrough attributes to apply at this stage.
      const ON_Font* rtf_fonttbl_font = ON_Font::FontFromRichTextProperties(str,false,false,false,false);
      if (nullptr != rtf_fonttbl_font)
        this->SetCurrentFont(rtf_fonttbl_font);
    }
  }
  else
  {
    // String is for a text run
    m_current_run.SetType(ON_TextRun::RunType::kText);
  }

#if defined(ON_DEBUG) && defined(ON_COMPILER_MSC)
  if (m_current_run.IsStacked() == ON_TextRun::Stacked::kStacked)
    count = count; // good place for a breakpoint
#endif
}

void ON_TextRunBuilder::BeginFontTable()
{
  m_font_table_level = m_level;
}

void ON_TextRunBuilder::BeginHeader()
{
  m_current_run.SetType(ON_TextRun::RunType::kHeader);
}

// Sets m_default_font_index when \deffn is read.
void ON_TextRunBuilder::DefaultFont(const wchar_t* value)
{
  ON__INT32 nval = -1;
  const wchar_t* sp = ON_wString::ToNumber(value, nval, &nval);
  if (nval >= 0 && sp > value)
    m_default_font_index = nval;
}

static const ON_Font* Internal_UpdateManagedFont(
  const ON_Font* current_managed_font,
  const ON_wString rtf_font_name,
  bool rtf_bBold,
  bool rtf_bItalic,
  bool rtf_bUnderlined,
  bool rtf_bStrikethrough
)
{
  // insure bool compares work as expected.
  if (false != rtf_bBold)
    rtf_bBold = true;
  if (false != rtf_bItalic)
    rtf_bItalic = true;
  if (false != rtf_bUnderlined)
    rtf_bUnderlined = true;
  if (false != rtf_bStrikethrough)
    rtf_bStrikethrough = true;

  if (nullptr != current_managed_font && false == current_managed_font->IsManagedFont())
    current_managed_font = current_managed_font->ManagedFont();
  if (nullptr == current_managed_font)
    current_managed_font = &ON_Font::Default;

  ON_wString local_rtf_name(rtf_font_name);
  local_rtf_name.TrimLeftAndRight();
  if (local_rtf_name.IsEmpty())
    local_rtf_name = ON_Font::RichTextFontName(current_managed_font, true);

  const ON_Font* new_managed_font = nullptr;

  const bool bChangeFont = ON_wString::EqualOrdinal(local_rtf_name, ON_Font::RichTextFontName(current_managed_font, false), true)
    ? false // rich text face name did not change
    : true // rich text face name changed.
    ;
  const bool bChangeBold = (rtf_bBold?1:0) != (current_managed_font->IsBoldInQuartet()?1:0);
  const bool bChangeItalic = (rtf_bItalic ? 1 : 0) != (current_managed_font->IsItalicInQuartet() ? 1 : 0);
  const bool bChangeUnderlined = (rtf_bUnderlined?1:0) != (current_managed_font->IsUnderlined()?1:0);
  const bool bChangeStrikethrough = (rtf_bStrikethrough?1:0) != (current_managed_font->IsStrikethrough()?1:0);

  if (bChangeFont || bChangeBold || bChangeItalic)
  {
    // Dale Lear - March 2021 - RH-62974
    // There are multiple places in the text run, rich text parsing, and Rhino UI code
    // that need find a font from rich text properties.
    // They must all do it the same way. If for some reason, you must change this call,
    // please take the time to create a single function that replaces this call, search
    // for all the places ON_Font::FontFromRichTextProperties is called in
    //  src4/rhino/... 
    //  opennurbs_textrun.cpp
    //  opennurbs_textiterator.cpp
    // and replace every call to ON_Font::FontFromRichTextProperties with a call to
    // your new function.
    // 
    //
    // Changing rich text quartet or member in some way must always
    // be done using ON_Font::FontFromRichTextProperties().
    // Otherwise this code will not work right for missing fonts.
    new_managed_font = ON_Font::FontFromRichTextProperties(
      local_rtf_name,
      rtf_bBold,
      rtf_bItalic,
      rtf_bUnderlined,
      rtf_bStrikethrough
    );
  }
  else if (bChangeUnderlined || bChangeStrikethrough)
  {
    // The same rich text quartet member with different underline/strikethrough  rendering effects.
    ON_Font f(*current_managed_font);
    f.SetUnderlined(rtf_bUnderlined);
    f.SetStrikethrough(rtf_bStrikethrough);
    new_managed_font = f.ManagedFont();
  }

  if (nullptr != new_managed_font)
    return new_managed_font;

  return current_managed_font;
}


// Process a rtf \fn tag to set the current font to the nth font in the rtf font table
void ON_TextRunBuilder::FontTag(const wchar_t* value)
{
  ON__INT32 nval = -1;
  const wchar_t* sp = ON_wString::ToNumber(value, nval, &nval);
  if (nval >= 0 && sp > value)
  {
    if(ReadingFontTable())
    {
      SetReadingFontDefinition(true);
      // Defining a font in the font table
      // n in \fn is the rtf index of the font currently being read from the table
      // store a mapping from \fn to font
      // when the font for this font table entry is made
      m_font_index = nval;
      // next will be a face name that will be read and put in a fontdef run
    }
    else
    {
      // Not defining the font table. Rather, setting a font current
      // Set current font to font corresponding to font_index
      //const ON_Font* pManagedFont = FindFontInMap(nval);

      const ON_Font* pManagedFont = (nullptr == this->CurrentFont())
        ? &ON_Font::Default 
        : this->CurrentFont()->ManagedFont()
        ;

      ON_wString rft_font_name = FaceNameFromMap(nval);
      rft_font_name.TrimLeftAndRight();
      const bool rtf_bBold = m_current_props.IsBold();
      const bool rtf_bItalic = m_current_props.IsItalic();
      const bool rtf_bUnderlined = m_current_props.IsUnderlined();
      const bool rtf_bStrikethrough = m_current_props.IsStrikethrough();

      pManagedFont = Internal_UpdateManagedFont(
        pManagedFont,
        rft_font_name,
        rtf_bBold,
        rtf_bItalic,
        rtf_bUnderlined,
        rtf_bStrikethrough
      );

      if (nullptr != pManagedFont)
      {
        this->SetCurrentFont(pManagedFont);
        // Use the rtf settings to update m_current_props
        // to because the current computer may not have an exact font match.
        m_current_props.SetBold(rtf_bBold);
        m_current_props.SetItalic(rtf_bItalic);
        m_current_props.SetUnderlined(rtf_bUnderlined);
        m_current_props.SetStrikethrough(rtf_bStrikethrough);
      }

      unsigned int charset = CharSetFromMap(nval);
      m_current_props.SetCharSet(charset, true);
    }
  }

  return;  // error - need font index      
}

void ON_TextRunBuilder::FontSize(const wchar_t* value)
{
  // Even though there is supposed to be a way
  // to decode control font height to 3d text height,
  // This always uses the TextHeight from the ON_TextContent object
  m_current_run.SetTextHeight(m_current_props.Height());


  //wchar_t* eptr = const_cast< wchar_t* >(value);
  //ON__UINT32 fs = ON_wString::ToNumber(value, &eptr, 10);
  //double d = 1.0;
  //if(eptr != value && fs > 0)
  //  d = MapControlFontSizeTo3dFontSize(fs);

  //m_current_run.SetHeight(d);
  //m_current_props.m_height = d;
}

void ON_TextRunBuilder::Newline()
{
  m_current_run.SetType(ON_TextRun::RunType::kNewline);
}

void ON_TextRunBuilder::Paragraph()
{
  m_current_run.SetType(ON_TextRun::RunType::kParagraph);
}

void ON_TextRunBuilder::ParagraphDefaults()
{
}

void ON_TextRunBuilder::Section()
{
}

void ON_TextRunBuilder::Tab()
{
  for(int i = 0; i < 8; i++) AppendCodePoint((ON__UINT32)' ');
  m_in_run = true;
}

void ON_TextRunBuilder::Bold(const wchar_t* value)
{
  bool on = true;
  if (nullptr != value)
  {
    if ('1' == value[0] || 0 == value[0])
      on = true;
    else if ('0' == value[0])
      on = false;
  }

  if (nullptr == this->CurrentFont())
    this->SetCurrentFont(&ON_Font::Default);

  const ON_Font* current_font = this->CurrentFont();
  if (false == current_font->IsManagedFont() || on != current_font->IsBoldInQuartet())
  {
    const ON_Font* managed_font = this->CurrentFont()->ManagedFamilyMemberWithRichTextProperties(
      on,
      current_font->IsItalicInQuartet(),
      current_font->IsUnderlined(),
      current_font->IsStrikethrough()
    );
    if (nullptr != managed_font)
      this->SetCurrentFont(managed_font);
  }
  m_current_props.SetBold(on);
}

void ON_TextRunBuilder::Italic(const wchar_t* value)
{
  bool on = true;
  if (nullptr != value)
  {
    if ('1' == value[0] || 0 == value[0])
      on = true;
    else if ('0' == value[0])
      on = false;
  }

  if (nullptr == this->CurrentFont())
    this->SetCurrentFont(&ON_Font::Default);

  const ON_Font* current_font = this->CurrentFont();
  if (false == current_font->IsManagedFont() || on != current_font->IsItalicInQuartet())
  {
    const ON_Font* managed_font = current_font->ManagedFamilyMemberWithRichTextProperties(
      current_font->IsBoldInQuartet(),
      on,
      current_font->IsUnderlined(),
      current_font->IsStrikethrough()
    );
    if (nullptr != managed_font)
      this->SetCurrentFont(managed_font);
  }
  m_current_props.SetItalic(on);
}

void ON_TextRunBuilder::UnderlineOn()
{
  if (nullptr == this->CurrentFont())
    this->SetCurrentFont(&ON_Font::Default);

  const ON_Font* current_font = this->CurrentFont();
  if ( false == current_font->IsManagedFont() || false == current_font->IsUnderlined() )
  {
    const ON_Font* managed_font = current_font->ManagedFamilyMemberWithRichTextProperties(
      current_font->IsBoldInQuartet(),
      current_font->IsItalicInQuartet(),
      true,
      current_font->IsStrikethrough()
    );
    if (nullptr != managed_font)
      this->SetCurrentFont(managed_font);
  }
  m_current_props.SetUnderlined(true);
}

void ON_TextRunBuilder::UnderlineOff()
{
  if (nullptr == this->CurrentFont())
    this->SetCurrentFont(&ON_Font::Default);

  const ON_Font* current_font = this->CurrentFont();
  if ( false == current_font->IsManagedFont() || current_font->IsUnderlined() )
  {
    const ON_Font* managed_font = current_font->ManagedFamilyMemberWithRichTextProperties(
      current_font->IsBoldInQuartet(),
      current_font->IsItalicInQuartet(),
      false,
      current_font->IsStrikethrough()
    );
    if (nullptr != managed_font)
      this->SetCurrentFont(managed_font);
  }
  m_current_props.SetUnderlined(false);
}

void ON_TextRunBuilder::Strikethrough(const wchar_t* value)
{
  bool on = true;
  if (nullptr != value)
  {
    if ('1' == value[0] || 0 == value[0])
      on = true;
    else if ('0' == value[0])
      on = false;
  }
  if (nullptr == this->CurrentFont())
    this->SetCurrentFont(&ON_Font::Default);

  const ON_Font* current_font = this->CurrentFont();
  if ( false == current_font->IsManagedFont() || on != current_font->IsStrikethrough() )
  {
    const ON_Font* managed_font = current_font->ManagedFamilyMemberWithRichTextProperties(
      current_font->IsBoldInQuartet(),
      current_font->IsItalicInQuartet(),
      current_font->IsUnderlined(),
      on
    );
    if (nullptr != managed_font)
      this->SetCurrentFont(managed_font);
  }
  m_current_props.SetStrikethrough(on);
}

void ON_TextRunBuilder::Superscript()
{
  m_current_run.SetStacked(ON_TextRun::Stacked::kTop);
}

void ON_TextRunBuilder::Subscript()
{
  m_current_run.SetStacked(ON_TextRun::Stacked::kBottom);
}

void ON_TextRunBuilder::NoSuperSub()
{
}

void ON_TextRunBuilder::BeginColorTable()
{
}

void ON_TextRunBuilder::ColorRed(const wchar_t* value)
{
}

void ON_TextRunBuilder::ColorGreen(const wchar_t* value)
{
}

void ON_TextRunBuilder::ColorBlue(const wchar_t* value)
{
}

void ON_TextRunBuilder::ColorForeground(const wchar_t* value)
{
}

void ON_TextRunBuilder::ColorBackground(const wchar_t* value)
{
}

void ON_TextRunBuilder::SetStackScale(const wchar_t* value)
{
  double stackscale = ON_TextRun::DefaultStackFractionHeight();
  ON_wString::ToNumber(value, stackscale, &stackscale);
  m_current_run.SetStackFractionHeight(stackscale);
  m_current_props.SetStackScale(stackscale);
}

void ON_TextRunBuilder::StackFraction(const wchar_t* value)
{
  m_current_run.SetType(ON_TextRun::RunType::kText);
  m_current_run.SetStacked(ON_TextRun::Stacked::kStacked);
  if (nullptr != m_current_run.m_stacked_text)
    delete m_current_run.m_stacked_text;
  m_current_run.m_stacked_text = new ON_StackedText;
  if (nullptr != value)
    m_current_run.m_stacked_text->m_separator = (wchar_t)wcstol(value, 0, 10);
  else
    m_current_run.m_stacked_text->m_separator = L'/';
}

void ON_TextRunBuilder::StackEnd()
{
  m_current_run.SetStackedOff();
}

void ON_TextRunBuilder::TextField(const wchar_t* name)
{
  m_current_run.SetType(ON_TextRun::RunType::kField);
}

void ON_TextRunBuilder::UniEmbeddedDest(const wchar_t* value)
{
  // two embedded unicode destinations - footnote, etc in rtf document
}

void ON_TextRunBuilder::UniDest(const wchar_t* value)
{
  // unicode destination
}

#pragma endregion  // TextRunBuilder



#pragma region RtfStringBuilder

ON_RtfStringBuilder::~ON_RtfStringBuilder()
{}

ON_RtfStringBuilder::ON_RtfStringBuilder(
  const ON_DimStyle* dimstyle,
  double height,
  ON_Color color)
{
  InitStringBuilder(dimstyle);
}


void ON_RtfStringBuilder::InitStringBuilder(const ON_DimStyle* dimstyle)
{
  if (nullptr == dimstyle)
    dimstyle = &ON_DimStyle::Default;
  const ON_Font& style_font = dimstyle->Font();
  ON_FaceNameKey& fnkey = m_facename_map.AppendNew();
  fnkey.m_rtf_font_name = ON_Font::RichTextFontName(&style_font, true);
  fnkey.m_rtf_font_index = 0;

  bool bold = style_font.IsBoldInQuartet();
  bool italic = style_font.IsItalic();
  bool underlined = style_font.IsUnderlined();
  bool strikethrough = style_font.IsStrikethrough();

  m_run_stack.Empty();

  m_current_run.SetFontIndex(fnkey.m_rtf_font_index);
  m_current_run.SetBold(bold);
  m_current_run.SetItalic(italic);
  m_current_run.SetUnderlined(underlined);
  m_current_run.SetStrikeThrough(strikethrough);

  m_in_run = 0;
  m_level = 0;
  m_font_table_level = 10000;
  m_current_codepoints.Empty();
}

void ON_RtfStringBuilder::PushRun(TextRun& run)
{
  m_run_stack.Append(run);
}
ON_RtfStringBuilder::TextRun ON_RtfStringBuilder::PopRun()
{
  if (m_run_stack.Count() > 0)
  {
    TextRun run = *m_run_stack.Last();
    m_run_stack.Remove();
    return run;
  }
  return m_current_run;
}

bool ON_RtfStringBuilder::InColorTable()
{
  return m_in_color_table;
}
void ON_RtfStringBuilder::SetInColorTable(bool b)
{
  m_in_color_table = b;
}

void ON_RtfStringBuilder::SetSkipColorTbl(bool b)
{
  m_skip_color_tbl = b;
}
void ON_RtfStringBuilder::SetSkipBold(bool b)
{
  m_skip_bold = b;
}
void ON_RtfStringBuilder::SetSkipItalic(bool b)
{
  m_skip_italic = b;
}
void ON_RtfStringBuilder::SetSkipUnderline(bool b)
{
  m_skip_underline = b;
}
void ON_RtfStringBuilder::SetSkipFacename(bool b)
{
  m_skip_facename = b;
}

bool ON_RtfStringBuilder::SkipColorTbl()
{
  return m_skip_color_tbl;
}
bool ON_RtfStringBuilder::SkipBold()
{
  return m_skip_bold;
}
bool ON_RtfStringBuilder::SkipItalic()
{
  return m_skip_italic;
}
bool ON_RtfStringBuilder::SkipUnderline()
{
  return m_skip_underline;
}
bool ON_RtfStringBuilder::SkipFacename()
{
  return m_skip_facename;
}

void ON_RtfStringBuilder::SetMakeBold(bool b)
{
  if(b)
    m_skip_bold = true;
  m_make_bold = b;
}
void ON_RtfStringBuilder::SetMakeItalic(bool b)
{
  if(b)
    m_skip_italic = true;
  m_make_italic = b;
}
void ON_RtfStringBuilder::SetMakeUnderline(bool b)
{
  if (b)
    m_skip_underline = true;
  m_make_underline = b;
}
void ON_RtfStringBuilder::SetMakeFacename(bool b)
{
  if (b)
    m_skip_facename = true;
  m_make_facename = b;
}

bool ON_RtfStringBuilder::MakeBold()
{
  return m_make_bold;
}
bool ON_RtfStringBuilder::MakeItalic()
{
  return m_make_italic;
}
bool ON_RtfStringBuilder::MakeUnderline()
{
  return m_make_underline;
}

bool ON_RtfStringBuilder::MakeFacename()
{
  return m_make_facename;
}

void ON_RtfStringBuilder::SetDefaultFacename(const wchar_t* facename)
{
  m_default_facename = (nullptr == facename) ? L"" : facename;
}

void ON_RtfStringBuilder::SetOverrideFacename(const wchar_t* facename)
{
  m_override_facename = (nullptr == facename) ? L"" : facename;
}

bool ON_RtfStringBuilder::SkippingFacename()
{
  return (m_skip_facename && !m_make_facename);
}

bool ON_RtfStringBuilder::SettingFacename()
{
  return (m_make_facename && !m_default_facename.IsEmpty());
}



void ON_RtfStringBuilder::GroupBegin()
{
  // not skipping the color table or we're not in it
  if (!SkipColorTbl() || m_current_run.Type() != ON_TextRun::RunType::kColortbl)
    m_string_out += m_current_run.TextString();

  m_current_run.EmptyText();
  m_current_run.SetTerminated(true);

  PushRun(m_current_run);
  
  m_current_run.AddControl(L"{");
  m_current_run.SetType(ON_TextRun::RunType::kText);
  m_current_run.ClearHasContent();
  m_have_rtf = true;
  m_level++;
}

void ON_RtfStringBuilder::GroupEnd()
{
  if (m_current_run.Type() != ON_TextRun::RunType::kColortbl)
  {
    if (m_level >= 0)
    {
      m_current_run.AddControl(L"}");
      m_level--;
      if (m_current_run.Type() == ON_TextRun::RunType::kFonttbl)
      {
        if (SkippingFacename())
        {
          m_current_run.AddControl(L"{\\f0 ");
          m_level++;
        }
        else if (SettingFacename())
        {
          // Add \\fn ofter font table run
          ON_wString temp;
          temp.Format(L"{\\f%d ", m_font_index);
          m_current_run.AddControl(temp.Array());
          m_level++;
        }
        m_font_table_level = 10000;
      }
      m_string_out = m_string_out + m_current_run.TextString();
      m_current_run.EmptyText();
    }
  }

  if (m_current_run.Type() == ON_TextRun::RunType::kColortbl)
    SetInColorTable(false);

  m_current_run = PopRun();
}

void ON_RtfStringBuilder::RunBegin()
{
  // not skipping the color table or we're not in it
  if (!SkipColorTbl() || m_current_run.Type() != ON_TextRun::RunType::kColortbl)
    m_string_out += m_current_run.TextString();

  m_current_run.EmptyText();
  m_current_run.SetTerminated(true);

  m_current_run.SetType(ON_TextRun::RunType::kText);
  m_current_run.ClearHasContent();
  m_have_rtf = true;
}

void ON_RtfStringBuilder::RunEnd()
{
  if (m_current_run.Type() != ON_TextRun::RunType::kColortbl)
  {
    if (m_level >= 0)
    {
      if (m_current_run.Type() == ON_TextRun::RunType::kFonttbl)
      {
        m_font_table_level = 10000;
      }
      m_string_out = m_string_out + m_current_run.TextString();
      m_current_run.EmptyText();
    }
  }

  if (m_current_run.Type() == ON_TextRun::RunType::kColortbl)
    SetInColorTable(false);
}

void ON_RtfStringBuilder::BeginFontTable()
{
  m_font_table_level = m_level;
  m_current_run.SetType(ON_TextRun::RunType::kFonttbl);

  if (SkippingFacename())
    return;

  ON_wString temp;
  //temp.Format(L"\\fonttbl{\\f0 %s;}", m_default_facename.Array());
  temp.Format(L"\\fonttbl");
  m_current_run.AddText(temp.Array());
  if (SettingFacename() && !m_default_facename.EqualOrdinal(m_override_facename, true))
  {
    temp.Format(L"{\\f1 %s;}", m_override_facename.Array());
    m_current_run.AddText(temp.Array());
  }
}

void ON_RtfStringBuilder::BeginHeader()
{
  m_current_run.SetType(ON_TextRun::RunType::kHeader);
  m_current_run.AddControl(L"\\rtf1");
}

// Sets m_default_font_index when \deffn is read.
void ON_RtfStringBuilder::DefaultFont(const wchar_t* value)
{
  if (m_skip_facename || (m_make_facename && !m_default_facename.IsEmpty()))
    m_default_font_index = 0;
  else
  {
    ON__INT32 nval = -1;
    const wchar_t* sp = ON_wString::ToNumber(value, nval, &nval);
    if (nval >= 0 && sp > value)
      m_default_font_index = nval;
  }
  ON_wString temp;

  temp.Format(L"\\deff%d", m_default_font_index);
  m_current_run.AddControl(temp.Array());
}

const ON_wString ON_RtfStringBuilder::OutputString()
{
  m_string_out.Replace(L"{}", L"");
  return m_string_out;
}


// Process a rtf \fn tag to set the current font to the nth font in the rtf font table
// or to store the definition for the nth font in the font table
void ON_RtfStringBuilder::FontTag(const wchar_t* value)
{
  if (SkippingFacename())
    return;

  ON__INT32 nval = -1;
  const wchar_t* sp = ON_wString::ToNumber(value, nval, &nval);
  if (nval >= 0 && sp > value) // got a number
  {
    if (ReadingFontTable())
    {
      if (m_current_run.Type() == ON_TextRun::RunType::kFonttbl && m_level == m_font_table_level)
      {
        m_string_out += m_current_run.TextString();
        m_current_run.EmptyText();
        m_current_run.SetTerminated(true);
        PushRun(m_current_run);
        m_have_rtf = true;
      }
      m_current_run.SetType(ON_TextRun::RunType::kFontdef);
      if (!SettingFacename())
      {
        // Defining a font in the font table
        // n in \fn is the rtf index of the font currently being read from the table
        // store a mapping from \fn to font
        // when the font for this font table entry is made
        m_font_index = nval;
        // next will be a face name that will be read and put in a fontdef run
        ON_wString temp;
        temp.Format(L"\\f%d", nval);
        m_current_run.AddControl(temp.Array());
      }
    }
    else
    {
      // Not defining the font table. Rather, setting a font current
      // Set current font to font corresponding to font_index
      if (SkippingFacename() || SettingFacename())
        m_current_run.AddControl(L"\\f1");
      else if (m_current_run.FontIndex() != nval)
      {
        ON_wString temp;
        temp.Format(L"\\f%d", nval);
        m_current_run.AddControl(temp.Array());
        m_current_run.SetFontIndex(nval);
      }
      if (MakeBold())
        m_current_run.AddControl(L"\\b");
      if (MakeItalic())
        m_current_run.AddControl(L"\\i");
      if (MakeUnderline())
        m_current_run.AddControl(L"\\ul");
    }
  }

  return;      
}

void ON_RtfStringBuilder::FontSize(const wchar_t* value)
{
  // We ignore font height
  ON__INT32 nval = -1;
  const wchar_t* sp = ON_wString::ToNumber(value, nval, &nval);
  if (nval >= 0 && sp > value) // got a number
  {
    ON_wString temp;
    temp.Format(L"\\fs%d", nval);
    m_current_run.AddControl(temp.Array());
  }
}

void ON_RtfStringBuilder::Newline()
{
  m_current_run.AddControl(L"\\par");
}

void ON_RtfStringBuilder::Paragraph()
{
  m_current_run.AddControl(L"\\par");
}

void ON_RtfStringBuilder::ParagraphDefaults()
{
  m_current_run.AddControl(L"\\pard");
}

void ON_RtfStringBuilder::Section()
{
}

void ON_RtfStringBuilder::Tab()
{
  for (int i = 0; i < 8; i++) AppendCodePoint((ON__UINT32)' ');
  m_in_run = true;
}

void ON_RtfStringBuilder::Bold(const wchar_t* value)
{
  if (!SkipBold())
  {
    bool bold = m_current_run.IsBold();
    bool on = true;
    if (nullptr != value)
    {
      if ('1' == value[0] || 0 == value[0])
        on = true;
      else if ('0' == value[0])
        on = false;
    }
    if (on != bold)
    {
      ON_wString temp;
      if ('0' == value[0])
        temp.Format(L"\\b0");
      else
        temp.Format(L"\\b");

      m_current_run.AddControl(temp.Array());
      m_current_run.SetBold(on);
    }
  }
}

void ON_RtfStringBuilder::Italic(const wchar_t* value)
{
  if (!SkipItalic())
  {
    bool italic = m_current_run.IsItalic();
    bool on = true;
    if (nullptr != value)
    {
      if ('1' == value[0] || 0 == value[0])
        on = true;
      else if ('0' == value[0])
        on = false;
    }
    if (on != italic)
    {
      ON_wString temp;
      if ('0' == value[0])
        temp.Format(L"\\i0");
      else
        temp.Format(L"\\i");

      m_current_run.AddControl(temp.Array());
      m_current_run.SetItalic(on);
    }
  }
}

void ON_RtfStringBuilder::UnderlineOn()
{
  if (!SkipUnderline())
  {
    bool under = m_current_run.IsUnderlined();
    bool on = true;
    if (on != under)
    {
      m_current_run.AddControl(L"\\ul");
      m_current_run.SetUnderlined(true);
    }
  }
}

void ON_RtfStringBuilder::UnderlineOff()
{
  if (!SkipUnderline())
  {
    bool under = m_current_run.IsUnderlined();
    bool on = false;
    if (on != under)
    {
      m_current_run.AddControl(L"\\ul0");
      m_current_run.SetUnderlined(true);
    }
  }
}

void ON_RtfStringBuilder::Strikethrough(const wchar_t* value)
{
}

void ON_RtfStringBuilder::Superscript()
{
}

void ON_RtfStringBuilder::Subscript()
{
}

void ON_RtfStringBuilder::NoSuperSub()
{
}

void ON_RtfStringBuilder::BeginColorTable()
{
  m_current_run.SetType(ON_TextRun::RunType::kColortbl);
  m_current_run.AddControl(L"\\colortbl");
  SetInColorTable(true);
}

void ON_RtfStringBuilder::ColorRed(const wchar_t* value)
{
}

void ON_RtfStringBuilder::ColorGreen(const wchar_t* value)
{
}

void ON_RtfStringBuilder::ColorBlue(const wchar_t* value)
{
}

void ON_RtfStringBuilder::ColorForeground(const wchar_t* value)
{
}

void ON_RtfStringBuilder::ColorBackground(const wchar_t* value)
{
}

void ON_RtfStringBuilder::TextField(const wchar_t* name)
{
  m_current_run.SetType(ON_TextRun::RunType::kField);
}

void ON_RtfStringBuilder::UniEmbeddedDest(const wchar_t* value)
{
  // two embedded unicode destinations - footnote, etc in rtf document
}

void ON_RtfStringBuilder::UniDecimal(const wchar_t* value)
{
  m_current_run.AddText(L"\\u");
  m_current_run.AddText(value);
  m_current_run.AddText(L"?");
}

void ON_RtfStringBuilder::UniDest(const wchar_t* value)
{
  // unicode destination
}

bool ON_RtfStringBuilder::AppendCodePoint(ON__UINT32 codept)
{
  if ((SettingFacename() || SkippingFacename()) && m_current_run.Type() == ON_TextRun::RunType::kFontdef)
    return true;

  if (m_current_run.Type() == ON_TextRun::RunType::kText)
  {
    if (MakeBold() && !m_current_run.IsBold())
    {
      m_current_run.AddControl(L"\\b");
      m_current_run.SetBold(true);
    }
    if (MakeItalic() && !m_current_run.IsItalic())
    {
      m_current_run.AddControl(L"\\i");
      m_current_run.SetItalic(true);
    }
    if (MakeUnderline() && !m_current_run.IsUnderlined())
    {
      m_current_run.AddControl(L"\\ul");
      m_current_run.SetUnderlined(true);
    }
    m_have_rtf = true;
  }

  ON_wString str;
  ON_TextContext::ConvertCodepointsToString(1, &codept, str);
  if (codept == ON_UnicodeCodePoint::ON_Backslash || codept == L'{' || codept == L'}')
    m_current_run.AddText(L"\\");
  m_current_run.AddText(str.Array());

  m_current_codepoints.Append(codept);
  return true;
}



#pragma endregion  // RtfStringBuilder



#ifdef RTFFIRSTCHAR

#pragma region RtfFirstChar

ON_RtfFirstChar::~ON_RtfFirstChar()
{}

ON_RtfFirstChar::ON_RtfFirstChar(
  const ON_DimStyle* dimstyle,
  double height,
  ON_Color color)
{
  InitStringBuilder(dimstyle);
}


void ON_RtfFirstChar::InitStringBuilder(const ON_DimStyle* dimstyle)
{
  if (nullptr == dimstyle)
    dimstyle = &ON_DimStyle::Default;
  const ON_Font& style_font = dimstyle->Font();
  ON_FaceNameKey& fnkey = m_facename_map.AppendNew();
  fnkey.m_rtf_font_name = style_font.FamilyName();
  fnkey.m_rtf_font_index = -1;

  bool bold = dimstyle->Font().IsBoldInQuartet();
  bool italic = dimstyle->Font().IsItalic();
  bool underlined = dimstyle->Font().IsUnderlined();
  bool strikethrough = dimstyle->Font().IsStrikethrough();

  m_run_stack.Empty();

  m_current_run.SetFontIndex(fnkey.m_rtf_font_index);
  m_current_run.SetBold(bold);
  m_current_run.SetItalic(italic);
  m_current_run.SetUnderlined(underlined);
  m_current_run.SetStrikeThrough(strikethrough);

  m_in_run = 0;
  m_level = 0;
  m_font_table_level = 10000;
}

void ON_RtfFirstChar::PushRun(TextRun& run)
{
  m_run_stack.Append(run);
}
ON_RtfFirstChar::TextRun ON_RtfFirstChar::PopRun()
{
  if (m_run_stack.Count() > 0)
  {
    TextRun run = *m_run_stack.Last();
    m_run_stack.Remove();
    return run;
  }
  return m_current_run;
}

bool ON_RtfFirstChar::InColorTable()
{
  return m_in_color_table;
}
void ON_RtfFirstChar::SetInColorTable(bool b)
{
  m_in_color_table = b;
}


void ON_RtfFirstChar::GroupBegin()
{
  PushRun(m_current_run);
  m_have_rtf = true;
  m_level++;
}

void ON_RtfFirstChar::GroupEnd()
{
  if (m_current_run.Type() == ON_TextRun::RunType::kFonttbl)
    m_font_table_level = 10000;

  if (m_current_run.Type() == ON_TextRun::RunType::kColortbl)
    SetInColorTable(false);

  if (m_current_run.Type() == ON_TextRun::RunType::kFontdef)
  {
    // String is a font facename. Make a font with that facename
    // and a font definition run 
    ON_wString str;
    str = m_current_run.Text();
    if (!str.IsEmpty())
    {
      str.Remove(L';');  // facename delimiter from rtf
      ON_FaceNameKey& fn_key = m_facename_map.AppendNew();
      fn_key.m_rtf_font_index = m_font_index;
      fn_key.m_rtf_font_name = str;
      fn_key.m_charset = m_current_props.CharSet();
      fn_key.m_codepage = m_current_props.CodePage();
    }
  }

  m_current_run = PopRun();

  m_level--;
}

void ON_RtfFirstChar::RunBegin()
{
  m_have_rtf = true;
}

void ON_RtfFirstChar::RunEnd()
{
  if (m_current_run.Type() == ON_TextRun::RunType::kFontdef)
  {
    // String is a font facename. Make a font with that facename
    // and a font definition run
    ON_wString str;
    str = m_current_run.Text();
    if (!str.IsEmpty())
    {
      str.Remove(L';');  // facename delimiter from rtf
      ON_FaceNameKey& fn_key = m_facename_map.AppendNew();
      fn_key.m_rtf_font_index = m_font_index;
      fn_key.m_rtf_font_name = str;
      fn_key.m_charset = m_current_props.CharSet();
      fn_key.m_codepage = m_current_props.CodePage();
    }
  }
}

void ON_RtfFirstChar::BeginFontTable()
{
  m_font_table_level = m_level;
  m_current_run.SetType(ON_TextRun::RunType::kFonttbl);
}

void ON_RtfFirstChar::BeginHeader()
{
  m_current_run.SetType(ON_TextRun::RunType::kHeader);
}

void ON_RtfFirstChar::BeginColorTable()
{
  m_current_run.SetType(ON_TextRun::RunType::kColortbl);
  SetInColorTable(true);
}

void ON_RtfFirstChar::TextField(const wchar_t* name)
{
  m_current_run.SetType(ON_TextRun::RunType::kField);
}

bool ON_RtfFirstChar::AppendCodePoint(ON__UINT32 codept)
{
  if (!m_have_rtf)
    m_have_rtf = true;
  // First char not in a table or tag - return false to stop parsing
  if (!InColorTable() && !ReadingFontTable())
    return false;

  ON_wString str;
  ON_TextContext::ConvertCodepointsToString(1, &codept, str);
  m_current_run.AddText(str.Array());

  m_current_codepoints.Append(codept);

  return true;
}

void ON_RtfFirstChar::FontTag(const wchar_t* value)
{
    if (ReadingFontTable())
      m_current_run.SetType(ON_TextRun::RunType::kFontdef);

  ON__INT32 nval = -1;
  const wchar_t* sp = ON_wString::ToNumber(value, nval, &nval);
  if (nval >= 0 && sp > value) // got a number
  {
    if (ReadingFontTable())
    {
      SetReadingFontDefinition(true);
      // Defining a font in the font table
      // n in \fn is the rtf index of the font currently being read from the table
      // store a mapping from \fn to font
      // when the font for this font table entry is made
      m_font_index = nval;
      // next will be a face name that will be read and put in a fontdef run
    }
    else
    {
      // Not defining the font table. Rather, setting a font current
      // Set current font to font corresponding to font_index
      if (m_current_run.FontIndex() != nval)
        m_current_run.SetFontIndex(nval);
    }
  }
  return;
}

void ON_RtfFirstChar::Bold(const wchar_t* value)
{
  bool bold = m_current_run.IsBold();
  bool on = true;
  if (nullptr != value)
  {
    if ('1' == value[0] || 0 == value[0])
      on = true;
    else if ('0' == value[0])
      on = false;
  }
  if (on != bold)
  {
    m_current_run.SetBold(on);
  }
}

void ON_RtfFirstChar::Italic(const wchar_t* value)
{
  bool italic = m_current_run.IsItalic();
  bool on = true;
  if (nullptr != value)
  {
    if ('1' == value[0] || 0 == value[0])
      on = true;
    else if ('0' == value[0])
      on = false;
  }
  if (on != italic)
    m_current_run.SetItalic(on);
}

void ON_RtfFirstChar::UnderlineOn()
{
    bool under = m_current_run.IsUnderlined();
    bool on = true;
    if (on != under)
      m_current_run.SetUnderlined(true);
}

void ON_RtfFirstChar::UnderlineOff()
{
  bool under = m_current_run.IsUnderlined();
  bool on = false;
  if (on != under)
    m_current_run.SetUnderlined(false);
}

void ON_RtfFirstChar::Strikethrough(const wchar_t* value)
{
}




#pragma endregion  // RtfFirstChar

#endif // RTFFIRSTCHAR



ON_RtfParser::ON_RtfParser(ON_TextIterator& iter, ON_TextBuilder& builder)
  : m_ti(iter)
  , m_builder(builder)
{
}

bool ON_RtfParser::ProcessTag(const wchar_t* name, const wchar_t* value, bool optional)
{
  ON_wString tagname(name);
  if( tagname.IsEmpty() )
    return false;

  bool rc = true;

  const bool bOrdinalIgnoreCase = true;

if (0 == tagname.CompareOrdinal(tagRtf, bOrdinalIgnoreCase))
{
  m_in_real_rtf = true;
  m_builder.BeginHeader();
}
else if (0 == tagname.CompareOrdinal(tagFontTable, bOrdinalIgnoreCase))
m_builder.BeginFontTable();
else if (0 == tagname.CompareOrdinal(tagDefaultFont, bOrdinalIgnoreCase) && 0 != value && 0 != value[0])
m_builder.DefaultFont(value);
else if (0 == tagname.CompareOrdinal(tagFont, bOrdinalIgnoreCase) && 0 != value && 0 != value[0])
m_builder.FontTag(value);
else if (0 == tagname.CompareOrdinal(tagFontSize, bOrdinalIgnoreCase) && 0 != value && 0 != value[0])
m_builder.FontSize(value);
else if (0 == tagname.CompareOrdinal(tagCharSet, bOrdinalIgnoreCase) && 0 != value && 0 != value[0])
m_builder.CharSet(value);
else if (0 == tagname.CompareOrdinal(tagCodePage, bOrdinalIgnoreCase) && 0 != value && 0 != value[0])
m_builder.CodePage(value);

else if (0 == tagname.CompareOrdinal(tagNewline, bOrdinalIgnoreCase))
m_builder.Newline();
else if (0 == tagname.CompareOrdinal(tagParagraph, bOrdinalIgnoreCase))
m_builder.Paragraph();
else if (0 == tagname.CompareOrdinal(tagParagraphDefaults, bOrdinalIgnoreCase))
m_builder.ParagraphDefaults();
else if (0 == tagname.CompareOrdinal(tagSection, bOrdinalIgnoreCase))
m_builder.Section();
else if (0 == tagname.CompareOrdinal(tagTabulator, bOrdinalIgnoreCase))
m_builder.Tab();

else if (0 == tagname.CompareOrdinal(tagBold, bOrdinalIgnoreCase))
m_builder.Bold(value);
else if (0 == tagname.CompareOrdinal(tagItalic, bOrdinalIgnoreCase))
m_builder.Italic(value);
else if (0 == tagname.CompareOrdinal(tagUnderLine, bOrdinalIgnoreCase))
{
  if ((*value) == L'0')
    m_builder.UnderlineOff();
  else
    m_builder.UnderlineOn();
}
else if (0 == tagname.CompareOrdinal(tagUnderLineNone, bOrdinalIgnoreCase))
m_builder.UnderlineOff();
else if (0 == tagname.CompareOrdinal(tagStrikeThrough, bOrdinalIgnoreCase))
m_builder.Strikethrough(value);

else if (0 == tagname.CompareOrdinal(tagSuperscript, bOrdinalIgnoreCase))
m_builder.Superscript();
else if (0 == tagname.CompareOrdinal(tagSubscript, bOrdinalIgnoreCase))
m_builder.Subscript();
else if (0 == tagname.CompareOrdinal(tagNoSuperSub, bOrdinalIgnoreCase))
m_builder.NoSuperSub();

else if (0 == tagname.CompareOrdinal(tagColorTable, bOrdinalIgnoreCase))
m_builder.BeginColorTable();
else if (0 == tagname.CompareOrdinal(tagColorRed, bOrdinalIgnoreCase) && 0 != value && 0 != value[0])
m_builder.ColorRed(value);
else if (0 == tagname.CompareOrdinal(tagColorGreen, bOrdinalIgnoreCase) && 0 != value && 0 != value[0])
m_builder.ColorGreen(value);
else if (0 == tagname.CompareOrdinal(tagColorBlue, bOrdinalIgnoreCase) && 0 != value && 0 != value[0])
m_builder.ColorBlue(value);
else if (0 == tagname.CompareOrdinal(tagColorForeground, bOrdinalIgnoreCase) && 0 != value && 0 != value[0])
m_builder.ColorForeground(value);
else if (0 == tagname.CompareOrdinal(tagColorBackground, bOrdinalIgnoreCase) && 0 != value && 0 != value[0])
m_builder.ColorBackground(value);

else if (0 == tagname.CompareOrdinal(tagStackFraction, bOrdinalIgnoreCase))
m_builder.SetStackScale(value);
else if (0 == tagname.CompareOrdinal(tagStackText, bOrdinalIgnoreCase))
m_builder.StackFraction(value);
else if (0 == tagname.CompareOrdinal(tagStackEnd, bOrdinalIgnoreCase))
m_builder.StackEnd();

else if (0 == ON_wString::CompareOrdinal(name, tagField, bOrdinalIgnoreCase))
m_builder.TextField(value);

else if (0 == ON_wString::CompareOrdinal(name, tagUniCpCount, bOrdinalIgnoreCase))
m_builder.UniCpCount(value);
else if (0 == ON_wString::CompareOrdinal(name, tagUniCharDec, bOrdinalIgnoreCase))
m_builder.UniDecimal(value);
else if (0 == ON_wString::CompareOrdinal(name, tagUniTwoDest, bOrdinalIgnoreCase))
m_builder.UniEmbeddedDest(value);
else if (0 == ON_wString::CompareOrdinal(name, tagUniDest, bOrdinalIgnoreCase))
m_builder.UniDest(value);

else if (0 == ON_wString::CompareOrdinal(name, taglquote, bOrdinalIgnoreCase))
m_builder.LQuote();
else if (0 == ON_wString::CompareOrdinal(name, tagrquote, bOrdinalIgnoreCase))
m_builder.RQuote();
else if (0 == ON_wString::CompareOrdinal(name, tagldblquote, bOrdinalIgnoreCase))
m_builder.LDblQuote();
else if (0 == ON_wString::CompareOrdinal(name, tagrdblquote, bOrdinalIgnoreCase))
m_builder.RDblQuote();
else if (0 == ON_wString::CompareOrdinal(name, tagbullet, bOrdinalIgnoreCase))
m_builder.Bullet();
else if (0 == ON_wString::CompareOrdinal(name, tagendash, bOrdinalIgnoreCase))
m_builder.EnDash();
else if (0 == ON_wString::CompareOrdinal(name, tagemdash, bOrdinalIgnoreCase))
m_builder.EmDash();
else
rc = false;

  return rc;
}

// Called after '\\*' is read
// '\\tagname<value> ...  ;' follows optional tag.
// optional tags can be skipped, and terminate with ';'
// the first tagname following '\\*\\' is the name of the optional tag and
// additional tags and tokens can follow, up to a terminating ';'
// tags can contain up to 32 chars in the name optionally followed by a number
bool ON_RtfParser::ReadOptionalTag()
{
  bool rc = false;
  bool end_of_tag = false;
  ON__UINT32 cp = 0;

  while (!end_of_tag)
  {
    if (false == m_ti.ReadCodePoint(cp))
    {
      end_of_tag = true;
      break;
    }
    switch (cp)
    {
    case ON_UnicodeCodePoint::ON_Backslash:
      rc = ReadTag(true);
      if (!rc && m_suspend_to_close == 0)
        m_suspend_to_close = 1;
      break;
    default:   // terminates an optional tag
      end_of_tag = true;
      // Terminating chars other than these are eaten here
      if ('\\' == cp || '{' == cp || '}' == cp)
        m_ti.Back();

      break;
    }
  }
  return rc;
}

// Called after '\\' is read
// tags can contain up to 32 chars in the name optionally followed by a number
bool ON_RtfParser::ReadTag(bool optional)
{
  wchar_t name[64];  // These are limited to 32 chars in the rtf spec
  wchar_t value[64];
  memset(name, 0, 64*sizeof(wchar_t));
  memset(value, 0, 64*sizeof(wchar_t));
  int namecnt = 0, valcnt = 0;
  bool in_name = true;
  bool end_of_tag = false;
  ON__UINT32 cp = 0;
  bool rc = false;

  while(!end_of_tag)
  {
    if( false == m_ti.ReadCodePoint(cp) )
    {
      end_of_tag = true;
      break;
    }
    if(in_name && IsAtoZ(cp) && namecnt < 63)  // Tag name is all alpha chars
    {
      name[namecnt++] = (wchar_t)cp;
    }
    else if((IsDigit(cp) || '.' == cp || ('-' == cp && valcnt == 0)) && valcnt < 63)  // digits following name is tag parameter
    {
      in_name = false;
      value[valcnt++] = (wchar_t)cp;
    }
    else   // tag name terminated by any non-alphabetic char, tag parameter argument terminated by non-digit char
    {
      end_of_tag = true;
      if(0 != ON_wString::CompareOrdinal(name, tagUniCharDec, true))
        m_builder.FormatChange();
      rc = ProcessTag(name, value, optional);

      // Terminating chars other than these are eaten here
      if('\\' == cp || '{' == cp || '}' == cp)
        m_ti.Back();
    }
  }
  return rc;
}


// input: cp_array is an array of codepoints
// Encodes to UTF16 to make string for text in the run
bool ON_RtfParser::FlushCurText(ON_SimpleArray< ON__UINT32 >& cp_array)
{
  // Calling this with an empty array does nothing
  int cp32_count = cp_array.Count();
  if(cp32_count <= 0)
    return false;

  m_builder.FlushText(cp32_count, cp_array.Array());
  cp_array.Empty();
  return true;
}

bool ON_RtfParser::Parse()
{
  bool rc = true;
  bool end_of_string = false;
  bool optional_tag = false;
  ON__UINT32 rtf_code_point;

  while(!end_of_string)
  {
    if (m_suspend_to_close <= 0 && m_ti.AtBackslashTic())
    {
      // parse the entire contiguous MBCS string up to <OTHER>
      // \`XX\`XX...\`XX<OTHER>
      // <OTHER> != \`, XX = hex digit 0 to FF.
      // This string is a Windows MBCS string with code page identified by
      // 
      const ON__UINT32 char_count = Internal_ParseMBCSString( m_builder.m_current_props.CodePage() );
      if (char_count > 0)
        continue;
    }

    if(false == m_ti.ReadCodePoint(rtf_code_point))
      break;

    if (m_suspend_to_close > 0)
    {
      switch (rtf_code_point)
      {
      case L'}':
        m_suspend_to_close--;
        break;
      case L'{':
        m_suspend_to_close++;
        break;
      }
      if (m_suspend_to_close == 0)
        m_ti.Back();
      continue;
    }

    // Found a single byte character
    switch (rtf_code_point)
    {
    case ON_UnicodeCodePoint::ON_Backslash:
      {
        if ( m_ti.ReadCodePoint(rtf_code_point) )
        {
          // character following '\\'
          // Its a tag of some kind, or a literal char
          // These are special characters that follow '\\'
          switch (rtf_code_point)
          {
            // Literal escaped  '\' or '{' or '}'
            // Append to current text string
          case ON_UnicodeCodePoint::ON_Backslash:
          case L'{':
          case L'}':
            m_builder.AppendCodePoint(rtf_code_point);
            break;

            // Paragraph tag when following '\\'
          case ON_UnicodeCodePoint::ON_LineFeed:
          case ON_UnicodeCodePoint::ON_CarriageReturn:
          case ON_UnicodeCodePoint::ON_LineSeparator:
          case ON_UnicodeCodePoint::ON_ParagraphSeparator:
            FlushCurText(m_builder.m_current_codepoints);
            m_builder.RunEnd();
            ProcessTag(L"par", nullptr, false);
            m_builder.RunBegin();
            break;

          case '\'':
            // This case should never occur - it is handled by
            // Internal_ParseMBCSString at the beginning of this while statement.
            ON_ERROR("Bug in RTF parsing code.");
            break;

            // Symbol tags...
          case '~':  // non-break space
            if (!m_builder.AppendCodePoint((ON__UINT32)' '))
              return true;
            break;
          case '-':  // optional hyphen
            break;
          case '_':  // non-break hyphen
            if (!m_builder.AppendCodePoint((ON__UINT32)'-'))
              return true;
            break;
          case '|':
          case ':':
            break;
          case '*':
            ReadOptionalTag();
            break;
          //case 'n':
          //  //FlushCurText(m_builder.m_current_codepoints);
          //  m_builder.GroupEnd();
          //  ProcessTag(L"par", nullptr, false);
          //  m_builder.GroupBegin();
          //  break;
          default:
            // Tag names are always low ascii alphabetic
            m_ti.Back();
            ReadTag(false);
            //// Breaks reading unicode text like A<\u26085?\u26412?\u12398?\u12469?\u12452?>
            //// m_builder.m_current_codepoints.Empty();
            optional_tag = false;
          }
        }
      }
      break;

      // Character not immediately following '\\'
      // Skip newline characters if this is a real rtf string - just white space
      // If this is one of our recomposed plain text strings, \n means newline
    case ON_UnicodeCodePoint::ON_LineFeed:
    case ON_UnicodeCodePoint::ON_LineSeparator:
      if (!m_in_real_rtf)
      {
        FlushCurText(m_builder.m_current_codepoints);
        m_builder.GroupEnd();
        ProcessTag(L"par", nullptr, false);
        m_builder.GroupBegin();
      }
      break;

    case ON_UnicodeCodePoint::ON_NoBreakSpace:
    case ON_UnicodeCodePoint::ON_NarrowNoBreakSpace:
    case ON_UnicodeCodePoint::ON_ZeroWidthSpace:
      if (!m_builder.AppendCodePoint((ON__UINT32)' '))
        return true;
      break;

    case ON_UnicodeCodePoint::ON_CarriageReturn:
      break;

    case ON_UnicodeCodePoint::ON_Tab:
      // '\tab' tag
      //      ProcessTag(new RtfTag(tagTabulator));
      break;

      // Start group
    case '{':
      //FlushCurText(m_builder.m_current_codepoints);
      m_builder.GroupBegin();
      m_p_level++;
      break;

    case '}':
      //FlushCurText(m_builder.m_current_codepoints);
      m_builder.GroupEnd();
      if (m_p_level > 0)
      {
        m_p_level--;
      }
      else
      {
        // {} underflow
      }
      break;

    default:
      // Normal single byte text character not in a tag name
      // Could be argument to a tag, like a font name in fonttbl
      // AppendCodePoint() returns false to stop parsing
      if (m_builder.ReadingFontDefinition() && rtf_code_point == L';')
        m_builder.FinishFontDef();
      else
      {
        if (!m_builder.AppendCodePoint(rtf_code_point))
          return true;
      }
      break;
    }
  }  // end of big loop for whole string

  FlushCurText(m_builder.m_current_codepoints);
  m_builder.GroupEnd();

  return rc;
}

// This has to make a string that the text control can digest
// and that's short and simple as possible so it can be put in the file
unsigned int RtfComposer::GetFacenameKey(const ON_Font* font, ON_ClassArray< ON_wString >& fonttable)
{
  if (nullptr == font)
    return 0;
  // Depending on what created the RTF, the face name in the RTF can be a 
  // PostScript name, LOGFONT.lfFaceName, IDWriteFont family name, ...
  const ON_wString rtf_facename = font->QuartetName(ON_Font::NameLocale::English);

  if (rtf_facename.IsEmpty())
    return 0;
#if defined(ON_RUNTIME_WIN)
  if (rtf_facename.Length() > 33)
    ON_ERROR("rtf_facename is longer than Windows LogfontName\n");
#endif

  return RtfComposer::GetFacenameKey(rtf_facename.Array(), fonttable);
}

unsigned int RtfComposer::GetFacenameKey(const wchar_t* facename, ON_ClassArray< ON_wString >& fonttable)
{
  if(nullptr == facename || 0 == facename[0])
    return 0;
  int count = fonttable.Count();
  for(int i = 0; i < count; i++)
  {
    if (nullptr == fonttable[i] || 0 == fonttable[i][0])
      continue;
    if(ON_wString::EqualOrdinal(facename, fonttable[i], true))
      return i;
  }

  fonttable.AppendNew() = facename;
  return count;
}
unsigned int RtfComposer::GetColorKey(ON_Color color, ON_SimpleArray< unsigned int >& colortable)
{
  int count = colortable.Count();
  for(int i = 0; i < count; i++)
  {
    if(color == colortable[i])
      return i;
  }
  colortable.Append((unsigned int)color);
  return count;
}
bool RtfComposer::FormatTextHeight(double height, ON_wString& str)
{
  str.Format(L"\\*h%lf", height);
  return true;
}

bool IsSpecial(const wchar_t ch)
{
  if (L'\\' == ch) return true;
  if (L'}' == ch) return true;
  if (L'{' == ch) return true;
  return false;
}


static bool GetRunText(ON_TextRun* run, ON_wString& text_out, bool& foundunicodepoint)
{
  if (nullptr == run)
    return false;
  // Have to convert codepoints directly instead of
  // calling DisplayString() because of field evaluation
  // and because RTF uses a "signed UTF-16" encoding and converting the run
  // into RTF has to work on Apple platforms where wchar_t strings 
  // are UTF-32 encoded strings. (Ask Dale Lear if you have questions).
  const ON__UINT32* run_code_points = run->UnicodeString(); // null terminated
  if (nullptr != run_code_points && 0 != run_code_points[0])
  {
    for (int ci = 0; 0 != run_code_points[ci]; ci++)
    {
      const ON__UINT32 code_point = run_code_points[ci];

      // works on Windows and Apple
      ON__UINT16 utf16[2] = { 0 };
      const int utf16_count = ON_EncodeUTF16(code_point, utf16);
      if (utf16_count < 0 || utf16_count > 2 || 0 == utf16[0])
        continue;

      if (code_point > 0x80 || 1 != utf16_count || code_point != (ON__UINT32)utf16[0])
      {
        // When we write RTF, we do not specify what encoding is used for values in the range 0x80 - 0xFF.
        // 
        // The ON_wString temp should to have UTF-16 encoding on Windows platforms
        // and UTF-32 encoding on Apple platforms.
        //
        // There are 27 "tricky values" in this range 0x80 - 0xFF where Windows-1252 maps the value to a glyph and 
        // and UNICODE maps the value to a control that typically has no printable glyph.
        // These "tricky values" are all in the range 0x80 ... 0x9F.
        // An example is the Euro sign (Windows-1252 0x80 = Euro sign, UNICODE U+0080 = xxx control,
        // UNICODE U+20AC = Euro sign).
        //
        // The RTF we get from Windows controls, like the "Text" command dialog box,
        // typically specifies it is using Windows-1252 and encodes the Euro sign as \`80.
        // So, if we have one of these "euro like" values, we will explicitly write it as a UNICODE value
        // to avoid the possibility of something defaulting to using Windows-1252.
        // https://mcneel.myjetbrains.com/youtrack/issue/RH-38205
        //
        // See ON_DecodeWindowsCodePage1252Value() for more details.
        //
        // UNICODE code points that require UTF-16 surrogate pair encodings have
        // two RTF values TWO \uN?\uN? values. 
        // For example, UNICODE code point U+1F5D1 has UTF-16 encodeing (0xD83D, 0xDDD1)
        // and the RTF looks like ...{\ltrch \u-10179?\u-8751?}.
        for (int utf16i = 0; utf16i < utf16_count; utf16i++)
        {
          ON_wString n;
          const ON__INT16 signed_rtf_utf16_value = (ON__INT16)utf16[utf16i]; // will be negative when utf16[utf16i] >= 0x8000;
          const int signed_string_format_param = (int)signed_rtf_utf16_value;
          n.Format(L"\\u%d?", signed_string_format_param);
          text_out += n;
          foundunicodepoint = true;
        }
      }
      else
      {
        // code_point < 0x80 (ASCII value range) and casting to wchar_t will work
        // on any platform;
        wchar_t ascii_value = (wchar_t)code_point;
        if (IsSpecial(ascii_value))
        {
          text_out += L'\\';
        }
        text_out += ascii_value;
      }
    }
  }
  return true;
}

bool RtfComposer::Compose(
  const ON_TextContent* text,
  ON_wString& rtf,
  bool bForceRtf)
{
  if (0 == text)
    return false;

  if (!RtfComposer::RecomposeRTF())
  {
    rtf = text->RtfText();
    return true;
  }

  ON_TextRunArray* runs = text->TextRuns(true);
  if (nullptr == runs)
    return false;

  const ON_Font& style_font = text->DefaultFont();
  const ON_wString style_fontname = style_font.RichTextFontName();
  if (style_fontname.IsEmpty())
    return false;

  bool style_bold = style_font.IsBoldInQuartet();
  bool style_italic = (ON_Font::Style::Italic == style_font.FontStyle());
  bool style_underline = style_font.IsUnderlined();
  bool style_strikeout = style_font.IsStrikethrough();

  bool chg_bold = false;
  bool chg_italic = false;
  bool chg_underline = false;
  bool chg_strikeout = false;
  bool chg_facename = false;

  // First facename is from the ON_TextContent (style_font)
  // Any after that are from runs
  ON_ClassArray< ON_wString > fonttable(8);

  // Creates a fonttable entry if the font isn't in the fonttable
  // Returns the table index if it is
  unsigned int stylefont_key = GetFacenameKey(style_fontname, fonttable);

  int runcount = runs->Count();
  int nlcount = 0;

  // See if this is multi-line text
  bool multiline = false;
  for (int ri = 0; ri < runcount; ri++)
  {
    ON_TextRun* run = (*runs)[ri];
    if (nullptr != run)
    {
      if (ON_TextRun::RunType::kText == run->Type() && 0 < nlcount)
      {
        multiline = true;
        break;
      }
      else if (ON_TextRun::RunType::kNewline == run->Type() ||
        ON_TextRun::RunType::kParagraph == run->Type())
        nlcount++;
    }
  }

  bool make_rtf = bForceRtf;
  ON_SimpleArray< ON_TextRun* > runholders;
  for (int ri = 0; ri < runcount; ri++)
  {
    ON_TextRun* run = (*runs)[ri];
    if (nullptr != run)
    {
      if (
        ON_TextRun::RunType::kText == run->Type() ||
        ON_TextRun::RunType::kField == run->Type()
        )
      {
        const ON_Font* run_font = run->Font();
        if (nullptr != run_font)
        {
          runholders.AppendNew() = run;
          if (!chg_bold)
            chg_bold = run_font->IsBoldInQuartet() != style_bold;
          if (!chg_italic)
            chg_italic = run_font->IsItalic() != style_italic;
          if (!chg_underline)
            chg_underline = run_font->IsUnderlined() != style_underline;
          if (!chg_strikeout)
            chg_strikeout = run_font->IsStrikethrough() != style_strikeout;

          const ON_wString run_fontname = run_font->RichTextFontName();
          if (run_fontname.IsEmpty())
            return false;
          unsigned int run_font_key = GetFacenameKey(run_fontname, fonttable);

          if (!chg_facename)
            chg_facename = run_font_key != stylefont_key;
        }
        const ON__UINT32* run_codepoints = run->UnicodeString();
        if (!make_rtf && nullptr != run_codepoints)
        {
          for (int i = 0; run_codepoints[i] != 0; i++)
          {
            if (run_codepoints[i] > 127
              || run_codepoints[i] == '\\'
              || run_codepoints[i] == '{'
              || run_codepoints[i] == '}'
              )
            {
              make_rtf = true;
              break;
            }
          }
        }
      }
      else if (
        ON_TextRun::RunType::kParagraph == run->Type() ||
        ON_TextRun::RunType::kNewline == run->Type()
        )
      {
        runholders.AppendNew() = run;
        const ON_Font* run_font = run->Font();
        if (nullptr != run_font)
        {
          const ON_wString run_fontname = run_font->RichTextFontName();
          if (!run_fontname.IsEmpty())
          {
            unsigned int run_font_key = GetFacenameKey(run_fontname, fonttable);
            if (!chg_facename)
              chg_facename = run_font_key != stylefont_key;
          }
        }
      }
    }
  } // end of getting runinfo

  if (chg_bold || chg_italic || chg_underline || chg_strikeout || chg_facename)
    make_rtf = true;

  ON_wString run_strings;
  ON_wString temp;
  runcount = runholders.Count();
  for (int ri = 0; ri < runcount; ri++)
  {
    ON_TextRun* run = runholders[ri];
    if (nullptr == run)
      continue;

    if (
      ON_TextRun::RunType::kText == run->Type() ||
      ON_TextRun::RunType::kField == run->Type()
      )
    {
      if (make_rtf || (run->IsStacked() == ON_TextRun::Stacked::kStacked && run->m_stacked_text != 0))
      {
        unsigned int run_font_key = ON_UNSET_UINT_INDEX;
        if (make_rtf)
        {
          const ON_Font* run_font = run->Font();
          if (nullptr == run_font)
            continue;

          // add properties for this string
          run_strings += L"{";
          bool addspace = false;

          run_font_key = GetFacenameKey(run_font, fonttable);
          temp.Format(L"\\f%d", run_font_key);
          run_strings += temp;
          addspace = true;
          
          if (run_font->IsBoldInQuartet())
          {
            run_strings += L"\\b";
            addspace = true;
          }
          else if (style_bold)
          {
            run_strings += L"\\b0";
            addspace = true;
          }
          if (run_font->IsItalic())
          {
            run_strings += L"\\i";
            addspace = true;
          }
          else if (style_italic)
          {
            run_strings += L"\\i0";
            addspace = true;
          }
          if (run_font->IsUnderlined())
          {
            run_strings += L"\\ul";
            addspace = true;
          }
          else if (style_underline)
          {
            run_strings += L"\\ul0";
            addspace = true;
          }

          if (run->IsStacked() == ON_TextRun::Stacked::kBottom)
          {
            run_strings += L"\\sub";
            addspace = true;
          }
          if (run->IsStacked() == ON_TextRun::Stacked::kTop)
          {
            run_strings += L"\\super";
            addspace = true;
          }

          if (addspace)
            run_strings += L" ";
        }

        if (ON_TextRun::RunType::kField != run->Type() && run->IsStacked() == ON_TextRun::Stacked::kStacked && run->m_stacked_text != 0)
        {
          // RH-64720 - Only do this if the stack isn't from a field  
          run_strings += L"[[";
          GetRunText(run->m_stacked_text->m_top_run, run_strings, make_rtf);
          run_strings += run->m_stacked_text->m_separator;
          GetRunText(run->m_stacked_text->m_bottom_run, run_strings, make_rtf);
          run_strings += L"]]";
        }
        else if (ON_TextRun::RunType::kField == run->Type())
        {
          //run_strings += L"%<";
          //GetRunText(run, run_strings, make_rtf);
          //run_strings += L">%";
        }
        else
        {
          GetRunText(run, run_strings, make_rtf);
        }

        if (ri < runcount - 1)
        {
          ON_TextRun* par_run = runholders[ri+1];
          if (nullptr != par_run && (ON_TextRun::RunType::kNewline == par_run->Type() || ON_TextRun::RunType::kParagraph == par_run->Type()))
          {
            const ON_Font* par_run_font = par_run->Font();
            if (nullptr != par_run_font)
            {
              unsigned int par_run_font_key = GetFacenameKey(par_run_font, fonttable);
              if (par_run_font_key == run_font_key)
              {
                run_strings += L"\\par";
                ri++;
              }
            }
          }
        }
        if (make_rtf)
          run_strings += L"}";
      }
      else // not making rtf, just collect text from runs
      {
        GetRunText(run, run_strings, make_rtf);
      }
    }
    else if (ON_TextRun::RunType::kNewline == run->Type() || ON_TextRun::RunType::kParagraph == run->Type())
    {
      if (make_rtf)
      {
        temp = L"{\\par}";
        const ON_Font* par_run_font = run->Font();
        if (nullptr != par_run_font)
        {
          unsigned int par_run_font_key = GetFacenameKey(par_run_font, fonttable);
          if(par_run_font_key != stylefont_key)
          temp.Format(L"{\\f%d \\par}", par_run_font_key);
        }
        run_strings += temp;
      }
      else if(ri < runcount - 1 && multiline)   // not making rtf
        run_strings += L"\n";
    }
  }  // end of collecting run text

  int nfont = fonttable.Count();
  // Any time the font for the annotation's style has 
  // bold, italic or underline set, we have to write rtf 
  // even if there are no changes in the string itself
  if (run_strings.Length() > 0 && make_rtf)
  {
    // deff0 means use font0 for the default font throughout the string.
    // If we include font0 in the font table, when we send
    // the string back to the RTF control, the font listed as
    // font0 will be used instead of the default font for the 
    // style.
    // So the default font is listed as 0 and there is no
    // entry in the table for font0.

    rtf.Format(L"{\\rtf1");
    if (0 < nfont)
    {
      ON_wString fonttable_string;
      temp.Format(L"\\deff%d", stylefont_key);
      rtf += temp;
      fonttable_string = L"{\\fonttbl";
      for (int fi = 0; fi < nfont; fi++)
      {
        // 
        temp.Format(L"{\\f%d %s;}", fi, fonttable[fi].Array());
        fonttable_string += temp;
      }
      rtf += fonttable_string;

    }

    if (!RtfComposer::ComposeFS())
      temp.Format(L"}\\f%d", stylefont_key);
    else
      temp.Format(L"}\\f%d \\fs%d", stylefont_key, RtfComposer::TextEditorFontSize());

    rtf += temp;

    if (style_bold)
      rtf += L"\\b";
    if (style_italic)
      rtf += L"\\i";
    if (style_underline)
      rtf += L"\\ul";

    rtf += run_strings;
    // backing out the change made for RH-49725 because it causes the problem reported in RH-50733
    rtf += L"}";
  }
  else
  {
    rtf = run_strings;
  }
  return true;
}

// Turns on or off composing for debugging
bool RtfComposer::m_bComposeRTF = true;
bool RtfComposer::RecomposeRTF()
{
  return RtfComposer::m_bComposeRTF;
}
void RtfComposer::SetRecomposeRTF(bool b)
{
  RtfComposer::m_bComposeRTF = b;
}

// Turns on or off adding \FS40 to composed strings
bool RtfComposer::m_bComposeFS = true;
bool RtfComposer::ComposeFS()
{
  return RtfComposer::m_bComposeFS;
}
void RtfComposer::SetComposeFS(bool b)
{
  RtfComposer::m_bComposeFS = b;
}

int RtfComposer::m_TextEditorSize = 0;
int RtfComposer::TextEditorFontSize()
{
  if (0 < RtfComposer::m_TextEditorSize)
    return RtfComposer::m_TextEditorSize;
  else
    return 18;
}

void RtfComposer::SetTextEditorFontSize(unsigned int size)
{
  RtfComposer::m_TextEditorSize = size;
}

static const ON_wString Internal_PostScriptNameIfAvailable(const ON_Font& managed_font)
{
  ON_wString style_fontname = managed_font.PostScriptName();
  if (style_fontname.IsNotEmpty())
    return style_fontname;

  return ON_wString::FormatToString(L"Postscript-name-not-available-%u", managed_font.ManagedFontSerialNumber());
}

const ON_wString RtfComposer::ComposeAppleRTF(
  const ON_TextContent* text)
{
  ON_wString rtf_string;

  if (0 == text)
    return rtf_string;

  ON_TextRunArray* runs = text->TextRuns(true);
  if (nullptr == runs)
    return rtf_string;


  const ON_Font& style_font = text->DefaultFont();
  const ON_wString style_fontname = Internal_PostScriptNameIfAvailable(style_font);

  // First facename is from the ON_TextContent
  // Any after that are from runs
  ON_ClassArray< ON_wString > fonttable(8);

  // Creates a fonttable entry the first time
  unsigned int deffont_key = GetFacenameKey(style_fontname, fonttable);

  int runcount = runs->Count();
  int nlcount = 0;

  // See if this is multi-line text
  bool multiline = false;
  for (int ri = 0; ri < runcount; ri++)
  {
    ON_TextRun* run = (*runs)[ri];
    if (nullptr != run)
    {
      if (ON_TextRun::RunType::kText == run->Type() && 0 < nlcount)
        multiline = true;
      else if (ON_TextRun::RunType::kNewline == run->Type() ||
        ON_TextRun::RunType::kParagraph == run->Type())
        nlcount++;
    }
  }

  ON_SimpleArray< ON_TextRun* > runholders;
  for (int ri = 0; ri < runcount; ri++)
  {
    ON_TextRun* run = (*runs)[ri];
    if (nullptr != run)
    {
      if (
        ON_TextRun::RunType::kText == run->Type() ||
        ON_TextRun::RunType::kField == run->Type()
        )
      {
        const ON_Font* run_font = run->Font();
        if (nullptr != run_font)
        {
          runholders.AppendNew() = run;
        }
      }
      else if (
        ON_TextRun::RunType::kParagraph == run->Type() ||
        ON_TextRun::RunType::kNewline == run->Type()
        )
      {
        runholders.AppendNew() = run;
      }
    }
  } // end of getting runinfo

  ON_wString run_strings;
  ON_wString temp;
  runcount = runholders.Count();
  for (int ri = 0; ri < runcount; ri++)
  {
    ON_TextRun* run = runholders[ri];
    if (nullptr == run)
      continue;

    if (
      ON_TextRun::RunType::kText == run->Type() ||
      ON_TextRun::RunType::kField == run->Type()
      )
    {
      const ON_Font* run_font = run->Font();
      if (nullptr == run_font)
        continue;

      const ON_wString& run_fontname = Internal_PostScriptNameIfAvailable(*run_font);

      // add properties for this string
      run_strings += L"{";
      bool addspace = false;

      unsigned int run_font_key = GetFacenameKey(run_fontname, fonttable);
      temp.Format(L"\\f%d", run_font_key);
      run_strings += temp;
      addspace = true;
      
      if (run_font->IsBoldInQuartet())
      {
        run_strings += L"\\b";
        addspace = true;
      }
      if (run_font->IsItalic())
      {
        run_strings += L"\\i";
        addspace = true;
      }
      if (run_font->IsUnderlined())
      {
        run_strings += L"\\ul";
        addspace = true;
      }
      if (addspace)
        run_strings += L" ";

      bool true_bool = true;
      if (run->IsStacked() == ON_TextRun::Stacked::kStacked && run->m_stacked_text != 0)
      {
        run_strings += L"[[";
        GetRunText(run->m_stacked_text->m_top_run, run_strings, true_bool);
        run_strings += run->m_stacked_text->m_separator;
        GetRunText(run->m_stacked_text->m_bottom_run, run_strings, true_bool);
        run_strings += L"]]";
      }
      else if (ON_TextRun::RunType::kField == run->Type())
      {
        run_strings += L"%<";
        GetRunText(run, run_strings, true_bool);
        run_strings += L">%";
      }
      else
      {
        GetRunText(run, run_strings, true_bool);
      }

      if (ri < runcount - 2)
      {
        ON_TextRun* par_run = runholders[ri + 1];
        if (nullptr != par_run && (ON_TextRun::RunType::kNewline == par_run->Type() || ON_TextRun::RunType::kParagraph == par_run->Type()))
        {
          const ON_Font* par_run_font = par_run->Font();
          if (nullptr != par_run_font)
          {
            const ON_wString& par_run_fontname = Internal_PostScriptNameIfAvailable(*par_run_font);
            if (!par_run_fontname.IsEmpty())
            {
              unsigned int par_run_font_key = GetFacenameKey(par_run_fontname, fonttable);
              if (par_run_font_key == run_font_key)
              {
                run_strings += L"\\\n";
                ri++;
              }
            }
          }
        }
      }

      run_strings += L"}";
    }
    else if (ri < runcount - 1 && multiline && (ON_TextRun::RunType::kNewline == run->Type() || ON_TextRun::RunType::kParagraph == run->Type()))
    {
      temp = L"{\\par}";
      const ON_Font* run_font = run->Font();
      if (nullptr != run_font)
      {
        const ON_wString run_fontname = Internal_PostScriptNameIfAvailable(*run_font);
        unsigned int run_font_key = GetFacenameKey(run_fontname, fonttable);
        if(run_font_key != deffont_key)
          temp.Format(L"{\\f%d \\par}", run_font_key);
      }
      run_strings += temp;
    }
  }  // end of collecting run text

  int nfont = fonttable.Count();
  if (run_strings.Length() > 0)
  {
    rtf_string.Format(L"{\\rtf1");
    if (0 < nfont)
    {
      ON_wString fonttable_string;
      temp.Format(L"\\deff%d", deffont_key);
      rtf_string += temp;
      fonttable_string = L"{\\fonttbl";
      for (int fi = 0; fi < nfont; fi++)
      {
        temp.Format(L"{\\f%d %s;}", fi, fonttable[fi].Array());
        fonttable_string += temp;
      }
      rtf_string += fonttable_string;
    }

    if (!RtfComposer::ComposeFS())
      temp.Format(L"}\\f%d", deffont_key);
    else
      temp.Format(L"}\\f%d \\fs%d", deffont_key, RtfComposer::TextEditorFontSize());

    rtf_string += temp;

    rtf_string += run_strings;
    rtf_string += L"}";
  }
  return rtf_string;
}
