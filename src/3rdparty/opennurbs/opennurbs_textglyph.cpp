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
////////////////////////////////////////////////////////////////

#include "opennurbs.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

#include "opennurbs_internal_glyph.h"

void ON_FontGlyph::Internal_CopyFrom(const ON_FontGlyph& src)
{
  // Do not call any other ON_FontGlyph functions or
  // you risk infinite recursion when managed glyphs are being manufactured.
  m_normalized_glyph_bbox = src.m_normalized_glyph_bbox;
  m_font_unit_glyph_bbox = src.m_font_unit_glyph_bbox;
  m_code_point = src.m_code_point;
  m_managed_font = src.m_managed_font;
  m_substitute = src.m_substitute;
  // Do not copy m_is_managed.
  m_font_glyph_index = src.m_font_glyph_index;
}

ON_FontGlyph::ON_FontGlyph(const ON_FontGlyph& src)
{
  // Do not copy m_is_managed.
  Internal_CopyFrom(src);
}

ON_FontGlyph& ON_FontGlyph::operator=(const ON_FontGlyph& src)
{
  if (this != &src)
  {
    // Do not copy m_is_managed.
    Internal_CopyFrom(src);
  }
  return *this;
}

void ON_FontGlyph::Internal_SetFontGlyphIndex(unsigned int font_glyph_index)
{
  m_font_glyph_index = font_glyph_index;
}

ON_FontGlyph::ON_FontGlyph(
  const ON_Font* font,
  ON__UINT32 code_point
)
{
  SetCodePoint(font, code_point);
}

const ON_Font* ON_FontGlyph::Font() const
{
  return m_managed_font;
}
  
int ON_FontGlyph::CompareCodePointAndFont(
  const ON_FontGlyph& lhs,
  const ON_FontGlyph& rhs
)
{
  if (lhs.m_managed_font != rhs.m_managed_font)
  {
    if (nullptr == lhs.m_managed_font)
      return -1;
    if (nullptr == rhs.m_managed_font)
      return 1;
    int rc = ON_Font::CompareFontCharacteristics(*lhs.m_managed_font, *rhs.m_managed_font);
    if (0 != rc)
      return rc;
    const unsigned int lhs_sn = lhs.m_managed_font->RuntimeSerialNumber();
    const unsigned int rhs_sn = rhs.m_managed_font->RuntimeSerialNumber();
    if (lhs_sn < rhs_sn)
      return -1;
    if (lhs_sn > rhs_sn)
      return 1;
  }

  if (lhs.m_code_point < rhs.m_code_point)
    return -1;

  if (lhs.m_code_point > rhs.m_code_point)
    return 1;

  return 0;
}

int ON_FontGlyph::GetGlyphList
(
  size_t code_point_count,
  ON__UINT32* code_points,
  const ON_Font* font,
  ON__UINT32 unicode_CRLF_code_point,
  ON_SimpleArray<const ON_FontGlyph*>& glyph_list,
  ON_TextBox& text_box
)
{
  glyph_list.SetCount(0);
  text_box = ON_TextBox::Unset;

  if (nullptr == code_points)
    return 0;

  while (code_point_count > 0)
  {
    const size_t i = code_point_count - 1;
    if (0 != code_points[i] && ON_IsValidUnicodeCodePoint(code_points[i]) && false == ON_FontGlyph::IsEndOfLineCodePoint(code_points[i]))
      break;
    code_point_count--;
  }

  while (code_point_count > 0)
  {
    // do not trim leading end of line code points.
    if (0 != code_points[0] && ON_IsValidUnicodeCodePoint(code_points[0]))
      break;
    code_points++;
    code_point_count--;
  }

  if (code_point_count <= 0)
    return 0;

  const int cp_count = (int)code_point_count;

  const ON_Font* managed_font
    = (nullptr != font)
    ? font->ManagedFont()
    : nullptr;

  if (nullptr == managed_font)
    managed_font = &ON_Font::Default;
  
  const bool bCondenseCRLF = ON_IsValidUnicodeCodePoint(unicode_CRLF_code_point) ? true : false;

  glyph_list.Reserve(cp_count + 1);
  glyph_list.SetCount(cp_count + 1);
  ON_FontGlyph const ** glyphs = glyph_list.Array();
  
  //////////////////////////////////////////////////////////
  //
  // Fill in glyphs[] with all the information needed to render the string.
  //
  ON__UINT32 cp1 = code_points[0];
  int glyph_count = 0;
  for (int i = 0; i < cp_count; i++)
  {
    glyphs[glyph_count] = nullptr;

    ON__UINT32 cp0 = cp1;
    cp1 = (i + 1 < cp_count) ? code_points[i + 1] : 0;
    if (0 == cp0)
      continue;
    if (false == ON_IsValidUnicodeCodePoint(cp0))
      continue;
    
    if (ON_FontGlyph::IsEndOfLineCodePoint(cp0))
    {
      if ( bCondenseCRLF && ON_FontGlyph::IsCarriageReturnAndLineFeed(cp0,cp1) )
      {
        cp0 = unicode_CRLF_code_point;
        i++; // skip the LF in (CR,LF) pair or the CR in a (LF,CR) pair.
        cp1 = (i + 1 < cp_count) ? code_points[i + 1] : 0;
      }
    }

    // Get all the glyph metric and freetype information required to render the
    // glyph for this codepoint in the correct location.
    ON_FontGlyph g;
    if (false == g.SetCodePoint(managed_font, cp0))
      continue;

    const ON_FontGlyph* managed_glyph = g.ManagedGlyph();
    if (nullptr == managed_glyph)
      continue;
      
    glyphs[glyph_count++] = managed_glyph;
  }

  while (glyph_count > 0 && glyphs[glyph_count - 1]->IsEndOfLineCodePoint() )
    glyph_count--;
  if (glyph_count <= 0)
  {
    glyph_list.SetCount(0);
    return 0;
  }
  glyph_list.SetCount(glyph_count);

  //////////////////////////////////////////////////////////
  //
  // Get the extents of the rendered text
  //
  int line_count = 0;
  const int line_height = managed_font->FontMetrics().LineSpace(); // >= 0

  int start_index = 0;
  for (int i = 0; i < glyph_count; i++)
  {
    const bool bEOL 
      = glyphs[i]->IsEndOfLineCodePoint() 
      || (bCondenseCRLF && unicode_CRLF_code_point == glyphs[i]->CodePoint());

    if (false == bEOL && i + 1 < glyph_count)
    {
      continue; // not at the end of a line
    }

    const int end_index = bEOL ? i-1 : i;
    const bool bEmptyLine 
      = end_index < 0
      || glyphs[end_index]->IsEndOfLineCodePoint()
      || (bCondenseCRLF && unicode_CRLF_code_point == glyphs[end_index]->CodePoint());
    if (false == bEmptyLine)
    {
      // get bounding box of line
      ON_TextBox line_box;
      line_box.m_advance = ON_2dex::Zero;
      for (int gdex = start_index; gdex <= end_index; gdex++)
      {
        const ON_FontGlyph* gi = glyphs[gdex];
        ON_TextBox glyph_box = gi->GlyphBox();
        if (false == glyph_box.IsSet())
          continue;
        const ON_2dex glyph_delta = line_box.m_advance;
        line_box.m_advance = ON_2dex::Zero;
        if (line_box.IsSet())
          line_box = ON_TextBox::Union(line_box, ON_TextBox::Translate(glyph_box,glyph_delta) );
        else
          line_box = glyph_box;
        line_box.m_advance = glyph_delta;
        line_box.m_advance.i += glyph_box.m_advance.i;
      }

      if (line_box.IsSet())
      {
        // grow text_box
        // At this location in the code, line_count = 0 on first line, 1 on second line, ...
        const ON_2dex line_delta = { 0, -(line_count*line_height) };
        const ON_2dex line_advance = line_box.m_advance;
        line_box.m_advance = ON_2dex::Zero;
        text_box.m_advance = ON_2dex::Zero;
        if (text_box.IsSet())
          text_box = ON_TextBox::Union( text_box, ON_TextBox::Translate(line_box,line_delta) );
        else
          text_box = line_box;
        text_box.m_advance.i = line_advance.i;
        text_box.m_advance.j = -line_delta.j; // line_delta.j < 0 and m_advance.j is always >= 0.
      }
    }

    line_count++;

    if (false == bCondenseCRLF
      && i + 1 < glyph_count
      && ON_FontGlyph::IsCarriageReturnAndLineFeed(glyphs[i]->CodePoint(), glyphs[i + 1]->CodePoint())
      )
    {
      // false == bCondenseCRLF means the caller wants to preserve (CR,LF) and (LF,CR) 
      // as two distinct code points/ in the output glyph_list[].
      // We currently have (glyphs[i],glyphs[i + 1]) as a (CR,LF) or (LF,CR) pair.
      // Skip the second code point in the pair so line_count value will be set correctly.
      i++;
    }

    start_index = i + 1;
  }

  return line_count;
}

int ON_FontGlyph::GetGlyphList
(
  const wchar_t* text,
  const ON_Font* font,
  ON__UINT32 unicode_CRLF_code_point,
  ON_SimpleArray<const ON_FontGlyph*>& glyph_list,
  ON_TextBox& text_box
)
{
  glyph_list.SetCount(0);
  text_box = ON_TextBox::Unset;

  if (nullptr == text || 0 == text[0])
    return 0;

  const int textlength = ON_wString::Length(text);
  if (textlength < 1)
    return 0;

  ON_SimpleArray< ON__UINT32 > code_points(textlength + 1);
  code_points.SetCount(textlength + 1);

  const int cp_count = ON_ConvertWideCharToUTF32(
    0, // bTestByteOrder = false
    text,
    textlength,
    code_points.Array(),
    textlength,
    nullptr,    // error status - ignored
    0xFFFFFFFF, // mask as many errors as possible
    ON_UnicodeCodePoint::ON_ReplacementCharacter,  // unicode error mark when string is incorrectly encoded
    nullptr     // pointer to end of parsed text is ignored
  );

  return GetGlyphList(cp_count, code_points.Array(), font, unicode_CRLF_code_point, glyph_list, text_box);
}

int ON_FontGlyph::GetGlyphListBoundingBox
(
  const wchar_t* text,
  const ON_Font* font,
  ON_TextBox& text_box
)
{
  const ON__UINT32 unicode_CRLF_code_point = ON_UnicodeCodePoint::ON_LineSeparator;
  ON_SimpleArray<const ON_FontGlyph*> glyph_list;
  return ON_FontGlyph::GetGlyphList(
    text,
    font,
    unicode_CRLF_code_point,
    glyph_list,
    text_box
  );
}

int ON_FontGlyph::GetGlyphListBoundingBox
(
  size_t code_point_count,
  ON__UINT32* code_points,
  const ON_Font* font,
  ON_TextBox& text_box
)
{
  const ON__UINT32 unicode_CRLF_code_point = ON_UnicodeCodePoint::ON_LineSeparator;
  ON_SimpleArray<const ON_FontGlyph*> glyph_list;
  return ON_FontGlyph::GetGlyphList(
    code_point_count,
    code_points,
    font,
    unicode_CRLF_code_point,
    glyph_list,
    text_box
  );
}

const ON__UINT32 ON_FontGlyph::CodePoint() const
{
  return m_code_point;
}

unsigned int ON_FontGlyph::FontGlyphIndex() const
{
  if (0 != m_font_glyph_index)
    return m_font_glyph_index;

  const ON_FontGlyph* managed_glyph = ManagedGlyph();
  return
    nullptr == managed_glyph
    ? 0
    : managed_glyph->m_font_glyph_index;
}


bool ON_FontGlyph::FontGlyphIndexIsSet() const
{
  return (0 != m_font_glyph_index);
}

const ON__UINT_PTR ON_FontGlyph::FontGlyphId() const
{
  return (ON__UINT_PTR)FontGlyphIndex();
}

bool ON_FontGlyph::FontGlyphIdIsSet() const
{
  return FontGlyphIndexIsSet();
}

bool ON_FontGlyph::IsEndOfLineCodePoint() const
{
  return ON_FontGlyph::IsEndOfLineCodePoint(m_code_point);
}

bool ON_FontGlyph::IsEndOfLineCodePoint(
  ON__UINT32 unicode_code_point
)
{
  switch (unicode_code_point)
  {
  case ON_UnicodeCodePoint::ON_LineFeed:
  case ON_UnicodeCodePoint::ON_VerticalTab:
  case ON_UnicodeCodePoint::ON_FormFeed:
  case ON_UnicodeCodePoint::ON_CarriageReturn:
  case ON_UnicodeCodePoint::ON_NextLine:
  case ON_UnicodeCodePoint::ON_LineSeparator:
  case ON_UnicodeCodePoint::ON_ParagraphSeparator:
    return true;
  default:
    break;
  }
  return false;
}

bool ON_FontGlyph::IsCarriageReturnAndLineFeed(
  ON__UINT32 cp0,
  ON__UINT32 cp1
)
{
  if (ON_UnicodeCodePoint::ON_CarriageReturn == cp0)
  {
    return (ON_UnicodeCodePoint::ON_LineFeed == cp1);
  }
 
  if (ON_UnicodeCodePoint::ON_LineFeed == cp0)
  {
    return (ON_UnicodeCodePoint::ON_CarriageReturn == cp1);
  }

  return false;
}

const ON_TextBox& ON_FontGlyph::GlyphBox() const
{
  return m_normalized_glyph_bbox;
}

const ON_TextBox& ON_FontGlyph::FontUnitGlyphBox() const
{
  return m_font_unit_glyph_bbox;
}

bool ON_FontGlyph::SetCodePoint(
  const ON_Font* font,
  ON__UINT32 code_point
)
{
  *this = ON_FontGlyph::Unset;
  const bool bValidCodePoint = (0 != ON_IsValidUnicodeCodePoint(code_point)) ? true : false;
  if ( bValidCodePoint)
    m_code_point = code_point;
  m_managed_font = (nullptr != font) ? font->ManagedFont() : nullptr;
  return (bValidCodePoint && nullptr != m_managed_font);
}

const ON_FontGlyph* ON_FontGlyph::RenderGlyph(
  bool bUseReplacementCharacter
) const
{
  if (CodePointIsSet())
  {
    for (int pass = 0; pass < (bUseReplacementCharacter ? 2 : 1); pass++)
    {
      const ON_FontGlyph* glyph
        = (0 == pass)
        ? this
        : ON_FontGlyph(this->m_managed_font, ON_UnicodeCodePoint::ON_ReplacementCharacter).ManagedGlyph();

      if (nullptr == glyph)
        continue;

      const ON_FontGlyph* managed_glyph = glyph->ManagedGlyph();
      if (nullptr == managed_glyph)
        continue;
      if (nullptr != managed_glyph->m_substitute)
        return managed_glyph->m_substitute;
      if (0 == glyph->m_font_glyph_index && bUseReplacementCharacter)
        continue;
      return glyph;
    }
  }
  return nullptr;
}


const ON_FontGlyph* ON_FontGlyph::SubstituteGlyph() const
{
  return m_substitute;
}

bool ON_FontGlyph::CodePointIsSet() const
{
  return (
    ON_IsValidUnicodeCodePoint(m_code_point)
    && nullptr != m_managed_font
    && m_managed_font->IsManagedFont()
    );
}

const ON_FontGlyph* ON_FontGlyph::ManagedGlyph() const
{
  if (IsManaged())
    return this;
  if (false == CodePointIsSet())
    return nullptr;
  return Font()->CodePointGlyph(CodePoint());
}

bool ON_FontGlyph::IsManaged() const
{
  return (m_is_managed ? true : false);
}

void ON_FontGlyph::Dump(
  bool bIncludeCharMaps,
  ON_TextLog& text_log
) const
{
  bool bIncludeFont = true;
  bool bIncludeSubstitute = true;
  bool bIncludeFontUnitTextBox = false;
  Dump(bIncludeFont, bIncludeCharMaps, bIncludeSubstitute, bIncludeFontUnitTextBox, text_log);
}

void ON_FontGlyph::Dump(
  bool bIncludeFont,
  bool bIncludeCharMaps,
  bool bIncludeSubstitute,
  bool bIncludeFontUnitTextBox,
  ON_TextLog& text_log
) const
{
  ON_wString s;
  const ON_FontGlyph* g[2] = { this, bIncludeSubstitute ? this->SubstituteGlyph() : nullptr };
  ON_wString apple_substitute_postscript_name;

#if defined (ON_RUNTIME_APPLE_CORE_TEXT_AVAILABLE)
  if (nullptr == g[1] )
  {
    // Apple glyph substitution is handled differently from Windows
    // because Apple's font SDK is more limited and finding the best
    // font from a codepoint is not easily done.
    const ON_Font* glyph_font = g[0]->Font();
    if (nullptr != glyph_font)
    {
      bool bIsSubstituteFont = false;
      CTFontRef apple_font = glyph_font->AppleCTFont(0.0, bIsSubstituteFont);
      if (bIsSubstituteFont && nullptr != apple_font)
      {
        apple_substitute_postscript_name = glyph_font->AppleCTFontPostScriptName(apple_font);
        apple_substitute_postscript_name.TrimLeftAndRight();
        if (apple_substitute_postscript_name.IsNotEmpty())
          g[1] = g[0];
      }
    }
  }
#endif

  const bool bAppleSubstitute = apple_substitute_postscript_name.IsNotEmpty();
  bool bPrintMaps = false;
  for (int pass = 0; pass < (nullptr != g[1] ? 2 : 1); pass++)
  {
    if (nullptr == g[pass])
      break;


    if (pass > 0)
      s += L" -> substitute: ";

    if ( ON_IsValidUnicodeCodePoint(g[pass]->CodePoint()) )
    {
      const unsigned int code_point = g[pass]->CodePoint();
      const unsigned int glyph_index = (1 == pass || false == bAppleSubstitute) ? g[pass]->FontGlyphIndex() : 0;
      wchar_t w[8] = { 0 };
      ON_EncodeWideChar(code_point, 7, w);
      const ON_Font* font = g[pass]->Font();
      s += ON_wString::FormatToString(
        L"[%ls] U+%04X",
        w,
        code_point
      );

      if (bIncludeFont)
      {
        if (nullptr != font)
        {
          const ON_wString font_description 
            = (1 == pass && bAppleSubstitute)
            ? apple_substitute_postscript_name
            : ((font) ? font->Description() : ON_wString::EmptyString);
          unsigned int font_sn = (font) ? font->RuntimeSerialNumber() : 0;
          s += ON_wString::FormatToString(
            L" %ls <%u>",
            static_cast<const wchar_t*>(font_description),
            font_sn
          );
        }
        else
        {
          s += L" (no font)";
        }
      }

      if (glyph_index > 0)
      {
        s += ON_wString::FormatToString(L" glyph index = %u", glyph_index);
        bPrintMaps = bIncludeCharMaps;
      }
      else
      {
        s += L" (no glyph)";
      }

      const ON_TextBox gbox = g[pass]->FontUnitGlyphBox();
      const bool bGlyphBoxIsSet = gbox.IsSet() || g[pass]->GlyphBox().IsSet();
      const bool bManagedGlyph = (g[pass]->IsManaged());
      if (bManagedGlyph)
      {
        if (false == bGlyphBoxIsSet)
          s += L" (unset box)";
      }
      else
      {
        s += (bGlyphBoxIsSet ? L" (unmanaged)" : L" (unmanaged, unset box)");
      }
      if (bIncludeFontUnitTextBox && gbox.IsSet())
      {
        s += ON_wString::FormatToString(
          L" bbmin(%d,%d) bbmax(%d,%d) advance(%d,%d)",
          gbox.m_bbmin.i,gbox.m_bbmin.j, 
          gbox.m_bbmax.i,gbox.m_bbmax.j, 
          gbox.m_advance.i,gbox.m_advance.j
        );
      }
    }
    else
    {
      s =+ L"ON_FontGlyph::Unset";
    }
    if (nullptr == g[1])
      break;

    bPrintMaps = false;
  }

  if (s.IsEmpty())
    s = L"ON_FontGlyph->this = nullptr";

  text_log.PrintString(s);
  text_log.PrintNewLine();

#if !defined(ON_RUNTIME_APPLE) && defined(OPENNURBS_FREETYPE_SUPPORT)
  // Look in opennurbs_system_rumtime.h for the correct place to define OPENNURBS_FREETYPE_SUPPORT.
  // Do NOT define OPENNURBS_FREETYPE_SUPPORT here or in your project setting ("makefile").
  if ( bPrintMaps && nullptr != g[0] )
  {
    text_log.PushIndent();
    g[nullptr != g[1] ? 1 : 0]->TestFreeTypeFaceCharMaps(&text_log);
    text_log.PopIndent();
  }
#endif

}


bool ON_TextBox::IsSet() const
{
  // m_advance values may be INT_MIN = ON_UNSET_INT_INDEX-1 for line feeds - more investigation required.
  return(
    ON_UNSET_INT_INDEX < m_bbmin.i && m_bbmin.i <= m_bbmax.i
    && ON_UNSET_INT_INDEX < m_bbmax.j && m_bbmin.j <= m_bbmax.j
    && ON_UNSET_INT_INDEX != m_max_basepoint.i
    && ON_UNSET_INT_INDEX != m_max_basepoint.j
    && ON_UNSET_INT_INDEX != m_advance.i
    && ON_UNSET_INT_INDEX != m_advance.j
    );
}

ON_TextBox::ON_TextBox(
  ON_2dPoint bbmin,
  ON_2dPoint bbmax
)
{
  if (bbmin.IsValid())
  {
    m_bbmin.i = (int)floor(bbmin.x);
    m_bbmin.j = (int)floor(bbmin.y);
  }
  if (bbmax.IsValid())
  {
    m_bbmax.i = (int)floor(bbmax.x);
    m_bbmax.j = (int)floor(bbmax.y);
  }  
}


const ON_TextBox ON_TextBox::Scale(
  const ON_TextBox& text_box,
  double scale
)
{
  ON_TextBox scaled_box = text_box;
  if ( scale > 0.0 && fabs(scale-1.0) > ON_ZERO_TOLERANCE )
  {
    if ( ON_UNSET_INT_INDEX != text_box.m_bbmin.i)
      scaled_box.m_bbmin.i = (int)floor(scale*text_box.m_bbmin.i);
    if ( ON_UNSET_INT_INDEX != text_box.m_bbmin.j)
      scaled_box.m_bbmin.j = (int)floor(scale*text_box.m_bbmin.j);
    if ( ON_UNSET_INT_INDEX != text_box.m_bbmax.i)
      scaled_box.m_bbmax.i = (int)ceil(scale*text_box.m_bbmax.i);
    if ( ON_UNSET_INT_INDEX != text_box.m_bbmax.j)
      scaled_box.m_bbmax.j = (int)ceil(scale*text_box.m_bbmax.j);

    if ( ON_UNSET_INT_INDEX != text_box.m_max_basepoint.i)
      scaled_box.m_max_basepoint.i = (int)ceil(scale*text_box.m_max_basepoint.i); // ceil is correct m_max_basepoint.i increases to the left
    if ( ON_UNSET_INT_INDEX != text_box.m_max_basepoint.j)
      scaled_box.m_max_basepoint.j = (int)floor(scale*text_box.m_max_basepoint.j); // floor is correct m_max_basepoint.j decreases with each line
    
    // currently rounding to nearest int
    if ( ON_UNSET_INT_INDEX != text_box.m_advance.i)
      scaled_box.m_advance.i = (int)floor(scale*text_box.m_advance.i + 0.5);
    if ( ON_UNSET_INT_INDEX != text_box.m_advance.j)
      scaled_box.m_advance.j = (int)floor(scale*text_box.m_advance.j + 0.5);
  }

  return scaled_box;
}

static int Internal_TextBoxMinMax(
  bool bMaximize,
  int lhs,
  int rhs
)
{
  int i = lhs;
  if (ON_UNSET_INT_INDEX == i)
    i = rhs;
  else if (ON_UNSET_INT_INDEX != rhs)
  {
    if (bMaximize)
    {
      if (i < rhs)
        i = rhs;
    }
    else
    {
      if (i > rhs)
        i = rhs;
    }
  }
  return i;
}

const ON_TextBox ON_TextBox::Union(
  const ON_TextBox& lhs,
  const ON_TextBox& rhs
)
{
  ON_TextBox u;

  u.m_bbmin.i = Internal_TextBoxMinMax(false, lhs.m_bbmin.i, rhs.m_bbmin.i);
  u.m_bbmin.j = Internal_TextBoxMinMax(false, lhs.m_bbmin.j, rhs.m_bbmin.j);

  u.m_bbmax.i = Internal_TextBoxMinMax(true, lhs.m_bbmax.i, rhs.m_bbmax.i);
  u.m_bbmax.j = Internal_TextBoxMinMax(true, lhs.m_bbmax.j, rhs.m_bbmax.j);

  u.m_max_basepoint.i = Internal_TextBoxMinMax(true,  lhs.m_max_basepoint.i, rhs.m_max_basepoint.i);
  u.m_max_basepoint.j = Internal_TextBoxMinMax(false, lhs.m_max_basepoint.j, rhs.m_max_basepoint.j);

  u.m_advance.i = 0;
  u.m_advance.j = 0;

  return u;
}

void ON_TextBox::Dump(ON_TextLog& text_log) const
{
  text_log.Print("BBbox: min = (%d,%d) max = (%d,%d)\n", m_bbmin.i, m_bbmin.j, m_bbmax.i, m_bbmax.j);
  text_log.Print("Advance: (%d,%d)\n", m_advance.i, m_advance.j);
}

const ON_TextBox ON_TextBox::Translate(
  const ON_TextBox& text_box,
  const ON_2dVector& delta
)
{
  // When delta components are not integer valued, 
  // the size of the box often increases by 1.
  ON_TextBox t = text_box;

  // Translate modifies point locations m_bbmin, m_bbmax, m_max_basepoint.
  // Translate does not modify the m_advance vector direction.

  if (ON_IsValid(delta.x) && 0.0 != delta.x)
  {
    if (ON_UNSET_INT_INDEX != t.m_bbmin.i)
      t.m_bbmin.i = (int)floor(t.m_bbmin.i + delta.x);
    if (ON_UNSET_INT_INDEX != t.m_bbmax.i)
      t.m_bbmax.i = (int)ceil(t.m_bbmax.i + delta.x);
    if (ON_UNSET_INT_INDEX != t.m_max_basepoint.i)
      t.m_max_basepoint.i = (int)ceil(t.m_max_basepoint.i + delta.x);
  }

  if (ON_IsValid(delta.y) && 0.0 != delta.y)
  {
    if (ON_UNSET_INT_INDEX != t.m_bbmin.j)
      t.m_bbmin.j = (int)floor(t.m_bbmin.j + delta.y);
    if (ON_UNSET_INT_INDEX != t.m_bbmax.j)
      t.m_bbmax.j = (int)ceil(t.m_bbmax.j + delta.y);
    if (ON_UNSET_INT_INDEX != t.m_max_basepoint.j)
      t.m_max_basepoint.j = (int)floor(t.m_max_basepoint.j + delta.y);
  }


  return t;
}

const ON_TextBox ON_TextBox::Translate(
  const ON_TextBox& text_box,
  const ON_2dex& delta
)
{
  ON_TextBox t = text_box;

  // Translate modifies point locations m_bbmin, m_bbmax, m_max_basepoint.
  // Translate does not modify the m_advance vector direction.

  if (ON_UNSET_INT_INDEX != delta.i && 0 != delta.i)
  {
    if (ON_UNSET_INT_INDEX != t.m_bbmin.i)
      t.m_bbmin.i += delta.i;
    if (ON_UNSET_INT_INDEX != t.m_bbmax.i)
      t.m_bbmax.i += delta.i;
    if (ON_UNSET_INT_INDEX != t.m_max_basepoint.i)
      t.m_max_basepoint.i += delta.i;
  }

  if (ON_UNSET_INT_INDEX != delta.j && 0 != delta.j)
  {
    if (ON_UNSET_INT_INDEX != t.m_bbmin.j)
      t.m_bbmin.j += delta.j;
    if (ON_UNSET_INT_INDEX != t.m_bbmax.j)
      t.m_bbmax.j += delta.j;
    if (ON_UNSET_INT_INDEX != t.m_max_basepoint.j)
      t.m_max_basepoint.j += delta.j;
  }

  // Translate does not modify the m_advance vector.

  return t;
}


//-----------------------------------------------------------------

ON_Internal_FontGlyphPool::ON_Internal_FontGlyphPool()
{
  ON_FixedSizePool::Create(sizeof(ON_FontGlyph), 0, 0);
}

ON_FontGlyph* ON_FontGlyph::Internal_AllocateManagedGlyph(
  const ON_FontGlyph& src
  )
{
  if ( false == src.CodePointIsSet() || src.IsManaged() )
  {
    ON_ERROR("invalid glyph parameter.");
    return nullptr;
  }

  // managed glyphs are app resources, allocated once per instance and never freed.
  ON_MemoryAllocationTracking disable_tracking(false); 

  ON_FontGlyph* managed_glyph = (ON_FontGlyph*)ON_Internal_FontGlyphPool::theGlyphItemPool.ThreadSafeAllocateElement();
  if (nullptr != managed_glyph)
  {
    managed_glyph = new (managed_glyph)ON_FontGlyph();
    *managed_glyph = src;
    managed_glyph->m_is_managed = 1;
  }
  return managed_glyph;
}

ON_GlyphMap::ON_GlyphMap()
{}

static int Internal_CompareGlyphItemCodepoint(const void* lhs, const void* rhs)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return -1;
  if (nullptr == rhs)
    return 1;
  const ON_FontGlyph* a = *((const ON_FontGlyph *const *)lhs);
  const ON_FontGlyph* b = *((const ON_FontGlyph *const *)rhs);
  if (a == b)
    return 0;
  if (nullptr == a)
    return -1;
  if (nullptr == b)
    return 1;

  const unsigned int a_code_point = a->CodePoint();
  const unsigned int b_code_point = b->CodePoint();
  if (a_code_point < b_code_point)
    return -1;
  if (a_code_point > b_code_point)
    return 1;

  return 0;
}

const ON_FontGlyph* ON_GlyphMap::FindGlyph(const ON__UINT32 unicode_codepoint) const
{
  if ( false == ON_IsValidUnicodeCodePoint(unicode_codepoint) )
    return nullptr; // invalid codepoint

  // The glyph map is a global resource. 
  // When multiple threads are simultaneously rendering text (very uncommon),
  // then they must take turns.
  ON_SleepLockGuard lock_guard(m_sleep_lock);

  const unsigned count = m_glyphs.UnsignedCount();
  if (unicode_codepoint < 256)
  {
    // codepoints up to 255 are saved by m_glyphs[] index.
    return
      (unicode_codepoint < count)
      ? m_glyphs[unicode_codepoint]
      : nullptr;
  }

  if (count > 256)
  {
    // binary search for codepoint values >= 256
    if (unicode_codepoint >= m_glyphs[256]->m_code_point && unicode_codepoint <= m_glyphs[count-1]->m_code_point)
    {
      ON_FontGlyph cp;
      cp.m_code_point = unicode_codepoint;
      const ON_FontGlyph* p = &cp;
      const ON_FontGlyph *const * a = m_glyphs.Array() + 256;
      const ON_FontGlyph *const * b = (const ON_FontGlyph *const *)bsearch(&p, a, count - 256, sizeof(*a), Internal_CompareGlyphItemCodepoint);
      const ON_FontGlyph* gi
        = (nullptr != b)
        ? *b
        : nullptr;

      return gi;
    }
  }

  return nullptr;
}

const ON_FontGlyph* ON_GlyphMap::InsertGlyph(const ON_FontGlyph& glyph )
{
  // managed glyphs are app resources - 1 per glpyh as needed and never freed.
  ON_MemoryAllocationTracking disable_tracking(false);

  if ( glyph.IsManaged() )
  {
    ON_ERROR("invalid glyph parameter");
    return nullptr;
  }

  if (false == glyph.CodePointIsSet())
  {
    ON_ERROR("glyph.CodePointIsSet() is false.");
    return nullptr;
  }

  const int base_count = 256;

  // The glyph map is a global resource. 
  // When multiple threads are simultaneously rendering text (very uncommon),
  // then they must take turns. 
  ON_SleepLockGuard lock_guard(m_sleep_lock);

  if (0 == m_glyphs.Count())
  {
    // codepoints 0 to base_count-1 are in m_glyphs[] by code point value.
    m_glyphs.Reserve(base_count);
    m_glyphs.SetCount(base_count);
    m_glyphs.Zero();
  }

  const int count = m_glyphs.Count();
  
  const ON__UINT32 code_point = glyph.m_code_point;
  int gdex;
  if (code_point < base_count)
  {
    gdex = (int)code_point;
    // codepoints up to 255 are saved by m_glyphs[] index.
    const ON_FontGlyph* gi = m_glyphs[gdex];
    if (nullptr != m_glyphs[gdex])
    {
      ON_ERROR("code point is already cached.");
      return gi; // codepoint already in the map
    }
  }
  else
  {
    for (gdex = base_count; gdex < count; gdex++)
    {
      const ON_FontGlyph* gi = m_glyphs[gdex];
      if (nullptr == gi)
        continue;
      if (gi->m_code_point == code_point)
      {
        ON_ERROR("code point is already cached.");
        return gi;  // codepoint already in the map
      }
      if (gi->m_code_point > code_point)
        break;
    }
  }

  ON_FontGlyph* managed_glyph = ON_FontGlyph::Internal_AllocateManagedGlyph(glyph);
  if (nullptr == managed_glyph)
  {
    ON_ERROR("theGlyphItemPool.AllocateUnsetGlyph() returned nullptr.");
    return nullptr;
  }

  if (gdex < base_count)
    m_glyphs[gdex] = managed_glyph;
  else if ( gdex < count )
    m_glyphs.Insert(gdex, managed_glyph);
  else
    m_glyphs.Append(managed_glyph);

  return managed_glyph;
}

unsigned int ON_GlyphMap::GlyphCount() const
{
  return m_glyph_count;
}

ON_OutlineFigurePoint::Type ON_OutlineFigurePoint::ContourPointTypeFromUnsigned(
  unsigned contour_point_type_as_unsigned
)
{
  switch (contour_point_type_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_OutlineFigurePoint::Type::Unset);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_OutlineFigurePoint::Type::BeginFigureUnknown);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_OutlineFigurePoint::Type::BeginFigureOpen);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_OutlineFigurePoint::Type::BeginFigureClosed);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_OutlineFigurePoint::Type::LineTo);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_OutlineFigurePoint::Type::QuadraticBezierPoint);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_OutlineFigurePoint::Type::CubicBezierPoint);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_OutlineFigurePoint::Type::EndFigureOpen);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_OutlineFigurePoint::Type::EndFigureClosed);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_OutlineFigurePoint::Type::Error);
  }

  ON_ERROR("Invalid contour_point_type_as_unsigned parameter.");
  return ON_OutlineFigurePoint::Type::Unset;
}

bool ON_OutlineFigurePoint::IsBeginFigurePointType(
  ON_OutlineFigurePoint::Type point_type
)
{
  if (
    ON_OutlineFigurePoint::Type::BeginFigureUnknown == point_type
    || ON_OutlineFigurePoint::Type::BeginFigureOpen == point_type
    || ON_OutlineFigurePoint::Type::BeginFigureClosed == point_type
    )
    return true;

  return false;
}

bool ON_OutlineFigurePoint::IsInteriorFigurePointType(
  ON_OutlineFigurePoint::Type point_type
)
{
  if (
    ON_OutlineFigurePoint::Type::LineTo == point_type
    || ON_OutlineFigurePoint::Type::QuadraticBezierPoint == point_type
    || ON_OutlineFigurePoint::Type::CubicBezierPoint == point_type
    )
    return true;

  return false;
}

bool ON_OutlineFigurePoint::IsEndFigurePointType(
  ON_OutlineFigurePoint::Type point_type
)
{
  if (
    ON_OutlineFigurePoint::Type::EndFigureClosed == point_type
    || ON_OutlineFigurePoint::Type::EndFigureOpen == point_type
    )
    return true;

  return false;
}

bool ON_OutlineFigurePoint::IsBeginFigurePoint() const
{
  return ON_OutlineFigurePoint::IsBeginFigurePointType(m_point_type);
}

bool ON_OutlineFigurePoint::IsInteriorFigurePoint() const
{
  return ON_OutlineFigurePoint::IsInteriorFigurePointType(m_point_type);
}

bool ON_OutlineFigurePoint::IsEndFigurePoint() const
{
  return ON_OutlineFigurePoint::IsEndFigurePointType(m_point_type);
}

static int Internal_FloatToInt(
  float f
)
{
  const float maxf = 999999.0f;
  if (f > -maxf && f < maxf)
  {
    float t = floor(f);
    if (f - t <= 0.5f)
      return (int)t;
    return (int)ceil(f);
  }
  return ON_UNSET_INT_INDEX;
}

const ON_2iPoint ON_OutlineFigurePoint::Point2i() const
{
  return ON_2iPoint(Internal_FloatToInt(m_point.x), Internal_FloatToInt(m_point.y));
}

const ON_2iPoint ON_OutlineFigurePoint::Point2iCeil() const
{
  const float maxf = 999999.0f;
  float t;
  ON_2iPoint p;
  t = ceil(m_point.x);
  p.x = (t > -maxf && t < maxf) ? ((int)t) : ON_UNSET_INT_INDEX;
  t = ceil(m_point.y);
  p.y = (t > -maxf && t < maxf) ? ((int)t) : ON_UNSET_INT_INDEX;
  return p;
}


const ON_2iPoint ON_OutlineFigurePoint::Point2iFloor() const
{
  const float maxf = 999999.0f;
  float t;
  ON_2iPoint p;
  t = floor(m_point.x);
  p.x = (t > -maxf && t < maxf) ? ((int)t) : ON_UNSET_INT_INDEX;
  t = floor(m_point.y);
  p.y = (t > -maxf && t < maxf) ? ((int)t) : ON_UNSET_INT_INDEX;
  return p;
}

ON_OutlineFigurePoint::Type ON_OutlineFigurePoint::PointType() const
{
  return m_point_type;
}

ON_OutlineFigurePoint::Proximity ON_OutlineFigurePoint::PointProximity() const
{
  return m_point_proximity;
}

bool ON_OutlineFigurePoint::IsOnFigure() const
{
  return (ON_OutlineFigurePoint::Proximity::OnFigure == m_point_proximity);
}

bool ON_OutlineFigurePoint::IsOffFigure() const
{
  return (ON_OutlineFigurePoint::Proximity::OffFigure == m_point_proximity);
}

ON__UINT16 ON_OutlineFigurePoint::FigureIndex() const
{
  return m_figure_index;
}

const ON_2fPoint ON_OutlineFigurePoint::Point() const
{
  return m_point;
}

const ON_2dPoint ON_OutlineFigurePoint::Point2d() const
{
  return ON_2dPoint(m_point);
}


bool ON_Annotation::GetTextGlyphContours(
  const ON_Viewport* vp,
  const ON_DimStyle* dimstyle,
  bool bApplyDimStyleDimScale,
  bool bSingleStrokeFont,
  ON_ClassArray< ON_ClassArray< ON_SimpleArray< ON_Curve* > > >& text_contours
) const
{
  const ON_TextContent* text_content = Text();
  if (nullptr == text_content)
    return false;

  double text_scale = 0.0;
  if (bApplyDimStyleDimScale && nullptr != dimstyle)
  {
    text_scale = dimstyle->DimScale();
  }
  if (false == (text_scale > 0.0 && ON_IsValid(text_scale)))
    text_scale = 1.0;


  ON_Xform text_xform = ON_Xform::IdentityTransformation;
  if (false == this->GetTextXform(vp, dimstyle, text_scale, text_xform))
    text_xform = ON_Xform::IdentityTransformation;

  const ON_Font* text_font = (nullptr != dimstyle) ? &dimstyle->Font() : nullptr;
  
  return text_content->GetGlyphContours(text_font, bSingleStrokeFont, text_xform, text_contours);
}

bool ON_TextContent::GetGlyphContours(
  const ON_Font* text_font,
  bool bSingleStrokeFont,
  double text_height,
  ON_ClassArray< ON_ClassArray< ON_SimpleArray< ON_Curve* > > >& text_contours
) const
{
  ON_Xform text_xform = ON_Xform::IdentityTransformation;

  double scale = 1.0;
  if (text_height > 0.0 && ON_IsValid(text_height) )
  {
    if (nullptr == text_font)
      text_font = &ON_Font::Default;
    scale = text_font->FontMetrics().GlyphScale(text_height);
    if (scale > 0.0)
      text_xform = ON_Xform::DiagonalTransformation(scale);
  }

  return this->GetGlyphContours(
    text_font,
    bSingleStrokeFont,
    text_xform,
    text_contours
  );
}


static const ON_FontGlyph* Internal_GetGlyphContours_SmallCapsGlyph(
  const ON_FontGlyph* glyph
)
{
  if (nullptr == glyph || false == glyph->CodePointIsSet() )
    return nullptr;
  const ON_FontGlyph* small_caps_glyph = nullptr;
  const ON__UINT32 code_point = glyph->CodePoint();
  const ON__UINT32 upper_ordinal_code_point = ON_UnicodeMapCodePointOrdinal(ON_StringMapOrdinalType::UpperOrdinal, code_point);
  if (
    upper_ordinal_code_point != code_point
    && upper_ordinal_code_point >= 'A'
    && ON_IsValidUnicodeCodePoint(upper_ordinal_code_point)
    )
  {
    small_caps_glyph = glyph->Font()->CodePointGlyph(upper_ordinal_code_point);
    if (nullptr != small_caps_glyph)
    {
      if (glyph->Font() != small_caps_glyph->Font() || small_caps_glyph != small_caps_glyph->RenderGlyph(false))
      {
        // do not permit font or glyph substitution when "small caps" are used.
        small_caps_glyph = nullptr;
      }
    }
  }
  return small_caps_glyph;
}

bool ON_FontGlyph::GetStringContours(
  const wchar_t* text_string,
  const ON_Font* font,
  bool bSingleStrokeFont,
  double text_height,
  double small_caps_scale,
  ON_ClassArray< ON_ClassArray< ON_SimpleArray< ON_Curve* > > >& string_contours
)
{
  // Dale Lear: https://mcneel.myjetbrains.com/youtrack/issue/RH-38183
  // Font substitution has to be used to get outlines for all code points.
  // I rewrote this entire function to support use of multiple fonts in a single string
  // to fix RH-38183.
  const bool bUseReplacementCharacter = true;

  if (nullptr == text_string || 0 == text_string[0])
    return false;
  
  const ON_Font* primary_font = (nullptr != font) ? font->ManagedFont() : ON_Font::Default.ManagedFont();
  if (nullptr == primary_font)
    return false;

  const ON_FontMetrics primary_fm = primary_font->FontMetrics();

  double scale = (text_height > ON_ZERO_TOLERANCE && text_height < 1.e38)
    ? primary_fm.GlyphScale(text_height)
    : 0.0;
  if (false == (scale > ON_ZERO_TOLERANCE && ON_IsValid(scale)) )
  {
    text_height = 0.0;
    scale = 1.0;
  }
  const double height_of_LF = scale*primary_fm.LineSpace();

  if (false == (text_height > ON_ZERO_TOLERANCE && text_height < 1.e38))
    text_height = 0.0;

  const double small_caps_text_height
    = (small_caps_scale > ON_ZERO_TOLERANCE && small_caps_scale < 1.0)
    ? small_caps_scale*text_height
    : text_height;

  ON_SimpleArray< const ON_FontGlyph* > glyph_list;
  ON_TextBox text_box;
  if (ON_FontGlyph::GetGlyphList(
    text_string,
    primary_font,
    ON_UnicodeCodePoint::ON_LineSeparator,
    glyph_list,
    text_box) <= 0)
  {
    return false;
  }
  
  double line_advance = 0.0;
  ON_3dPoint glyph_base_point = ON_3dPoint::Origin;

  unsigned int glyph_count = glyph_list.UnsignedCount();
  for ( unsigned int gdex = 0; gdex < glyph_count; gdex++ )
  {
    const ON_FontGlyph* glyph = glyph_list[gdex];
    if (nullptr == glyph)
      continue;
    if (glyph->IsEndOfLineCodePoint())
    {
      line_advance += height_of_LF;
      glyph_base_point.x = 0;
      glyph_base_point.y = line_advance;
      continue;
    }

    glyph = glyph->RenderGlyph(bUseReplacementCharacter);
    if (nullptr == glyph)
      continue;

    double glyph_text_height = text_height;

    const ON_FontGlyph* small_caps_glyph = 
      (small_caps_text_height > 0.0 &&  small_caps_text_height < text_height)
      ? Internal_GetGlyphContours_SmallCapsGlyph(glyph)
      : glyph;
    if (nullptr != small_caps_glyph)
    {
      glyph_text_height = small_caps_text_height;
      glyph = small_caps_glyph;
    }

    ON_BoundingBox glyph_contours_bbox = ON_BoundingBox::UnsetBoundingBox;
    ON_3dVector glyph_contours_advance = ON_3dVector::ZeroVector;
    ON_ClassArray< ON_SimpleArray< ON_Curve* > >& glyph_contours = string_contours.AppendNew();
    glyph->GetGlyphContours(bSingleStrokeFont, glyph_text_height, glyph_contours, &glyph_contours_bbox, &glyph_contours_advance);

    const ON_3dVector translate = glyph_base_point;
    glyph_base_point.x += glyph_contours_advance.x;

    const int contour_count = glyph_contours.Count();

    for (int li = 0; li < contour_count; li++)  // contours per glyph
    {
      const int curve_count = glyph_contours[li].Count();
      for (int ci = 0; ci < curve_count; ci++)
      {
        if (nullptr != glyph_contours[li][ci])
          glyph_contours[li][ci]->Translate(translate);
      }
    }
  }

  return true;
}

bool ON_TextRun::GetGlyphContours(
  const ON_Font* text_font,
  bool bSingleStrokeFont,
  const ON_Xform& text_xform,
  ON_ClassArray< ON_ClassArray< ON_SimpleArray< ON_Curve* > > >& run_contours
) const
{
  const ON_TextRun& run = *this;

  const ON_Font* run_font = run.Font();
  if (nullptr == run_font)
  {
    run_font = text_font;
    if (nullptr == run_font)
      run_font = &ON_Font::Default;
  }

  ON_Xform run_xf(text_xform);

  if (0.0 != run.m_offset.x || 0.0 != run.m_offset.y)
  {
    const ON_Xform run_offset(ON_Xform::TranslationTransformation(run.m_offset.x, run.m_offset.y, 0.0));
    run_xf = text_xform * run_offset;
  }

  double run_height = run.TextHeight();  // Specified height of text in Model units
  double I_height = run_font->FontMetrics().AscentOfCapital();
  double font_scale = run_height / I_height; // converts Font units to Model units, including text height
  ON_Xform scale_xf(ON_Xform::DiagonalTransformation(font_scale));
  run_xf = run_xf * scale_xf;

  if (run.IsStacked() == ON_TextRun::Stacked::kStacked && nullptr != run.m_stacked_text)
  {
    const ON_TextRun* stacked_runs[2] =
    {
      run.m_stacked_text->m_top_run,
      run.m_stacked_text->m_bottom_run,
    };
    bool rc = false;
    for (int i = 0; i < 2; i++)
    {
      if (nullptr == stacked_runs[i])
        continue;
      if (stacked_runs[i]->GetGlyphContours(
        run_font,
        bSingleStrokeFont,
        text_xform,
        run_contours
      ))
        rc = true;
    }

    //if (L'/' == run.m_stacked_text->m_separator)
    //{
    //  double h = 0.5 * I_height;
    //  double hs = (double)font->GetUnderscoreSize();
    //  double l = run.m_advance.x / font_scale;
    //  DrawFracLine(*this, run_xf, 0.0, h, hs, l, color);
    //}
    return rc;
  }


  // run->UnicodeString() returns the raw string which may have unevaluated fields.
  // run->DisplayString() returns the evaluated results of fields.
  const int run_contours_count0 = run_contours.Count();
  bool rc = ON_FontGlyph::GetStringContours(
    run.DisplayString(),
    run_font,
    bSingleStrokeFont,
    0.0, // text_height = 0.0 means get glyphs in opennurbs normalized font size
    0.0, // small_caps_scale,
    run_contours
  );

  const int run_contours_count1 = run_contours.Count();
  for (int gi = run_contours_count0; gi < run_contours_count1; gi++)
  {
    ON_ClassArray< ON_SimpleArray< ON_Curve* > >& countours = run_contours[gi];
    const int countour_count = countours.Count();
    for (int li = 0; li < countour_count; li++)
    {
      ON_SimpleArray< ON_Curve* >& curves = countours[li];
      const int curve_count = curves.Count();
      for (int ci = 0; ci < curve_count; ci++)
      {
        ON_Curve* curve = curves[ci];
        if (curve)
          curve->Transform(run_xf);
      }
    }
  }

  return rc;
}

bool ON_TextContent::GetGlyphContours(
  const ON_Font* text_font,
  bool bSingleStrokeFont,
  const ON_Xform& text_xform,
  ON_ClassArray< ON_ClassArray< ON_SimpleArray< ON_Curve* > > >& text_contours
) const
{
  if (nullptr == text_font)
    text_font = &ON_Font::Default;

  const ON_Xform xf = text_xform;

  const ON_TextRunArray* runs = TextRuns(false);
  if (nullptr != runs)
  {
    const int runcount = runs->Count();
    for (int ri = 0; ri < runcount; ri++)
    {
      const ON_TextRun* run = (*runs)[ri];
      if (nullptr == run)
        continue;
      if (ON_TextRun::RunType::kText != run->Type() && ON_TextRun::RunType::kField != run->Type())
        continue;

      const ON_Font* run_font = run->Font();
      if (nullptr == run_font)
        run_font = text_font;

      run->GetGlyphContours(run_font, bSingleStrokeFont, xf, text_contours);
    }
  }

  return false;
}

