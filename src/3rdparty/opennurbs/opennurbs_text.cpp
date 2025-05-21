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

#include "opennurbs_textiterator.h"

ON_OBJECT_IMPLEMENT(ON_TextContent, ON_Geometry, "4F0F51FB-35D0-9998-4865-9721D6D2C6A9");

//-----------------------------------------------------------------
ON::object_type ON_TextContent::ObjectType() const
{
  return ON::annotation_object;
}

void ON_TextContent::Internal_Destroy()
{
  m__runs = ON_TextRunArray::EmptyArray;
  Internal_DeleteWrappedRuns();
  DestroyRuntimeCache();

  m_annotation_type = ON_TextContent::Empty.m_annotation_type;
  m_dimstyle_text_position_properties_hash = ON_TextContent::Empty.m_dimstyle_text_position_properties_hash;
  Internal_ClearTextContentHash();
  m_default_font = &ON_Font::Default;
}

ON_TextContent::~ON_TextContent()
{
  Internal_Destroy();
}

void ON_TextContent::Internal_DeleteWrappedRuns() const
{
  if (nullptr != m__wrapped_runs)
  {
    delete m__wrapped_runs;
    m__wrapped_runs = nullptr;
  }
}

void ON_TextContent::Internal_CopyFrom(
  const ON_TextContent& src
)
{
  m_text = src.m_text;
  m_rect_width = src.m_rect_width;
  m_rotation_radians = src.m_rotation_radians;
  m_h_align = src.m_h_align;
  m_v_align = src.m_v_align;
  m__runs = src.m__runs;
  m_run_evaluation_sn = src.m_run_evaluation_sn;

  m_annotation_type = src.m_annotation_type;
  m_dimstyle_text_position_properties_hash = src.m_dimstyle_text_position_properties_hash;
  m_text_content_sub_hash = src.m_text_content_sub_hash;
  m_text_content_bbox = src.m_text_content_bbox;

  SetTextIsWrapped(src.m_bWrapText);
  if (src.TextIsWrapped() && nullptr != src.m__wrapped_runs)
  {
    m__wrapped_runs = new ON_TextRunArray(*src.m__wrapped_runs);
  }

  m_default_font = src.m_default_font;

  m_runtime_halign = src.m_runtime_halign;
}

ON_TextContent::ON_TextContent(const ON_TextContent& src)
  : ON_Geometry(src)
{
  Internal_CopyFrom(src);
}

// Duplicates text string and runs
ON_TextContent& ON_TextContent::operator=(const ON_TextContent& src)
{
  if (this != &src)
  {
    Internal_Destroy();
    ON_Geometry::operator=(src);
    Internal_CopyFrom(src);
  }
  return *this;
}

static bool ON_V6_Text_IsNotIsValid()
{
  return false; // <- breakpoint here to detect invalid ON_TextContent objects.
}

bool ON_TextContent::IsValid(ON_TextLog* text_log) const
{
  int runcount = m__runs.Count();

  bool has_valid_text_run = false;
  for (int i = 0; i < runcount; i++)
  {
    const ON_TextRun* run = m__runs[i];
    if (nullptr == run)
      return ON_V6_Text_IsNotIsValid();
    if (!run->IsValid())
      return ON_V6_Text_IsNotIsValid();
    if (ON_TextRun::RunType::kText == run->Type())
      has_valid_text_run = true;
  }

  if (nullptr != m__wrapped_runs)
  {
    int wruncount = m__wrapped_runs->Count();
    for (int i = 0; i < wruncount; i++)
    {
      const ON_TextRun* run = (*m__wrapped_runs)[i];
      if (nullptr == run)
        return ON_V6_Text_IsNotIsValid();
      if (!run->IsValid())
        return ON_V6_Text_IsNotIsValid();
    }
  }
  return true;
}


// At least for now, before text is parsed as RTF, 
// strings like [[xxx|xxx]] are replaced with custom RTF tags
// to represent stacked fractions.  
// After "[[", the characters up to "|" are the top of the fraction 
// and after "|" up to "]]" are the bottom of the fraction
// "[[123/456]]" becomes "{\\stack47 123/456}"
static bool SubstituteStackTags(const wchar_t* text_string, ON_wString& text, int length, int start, int& end, int depth)
{
  int i = start;
  bool stacking = false; // flag to defeat recursive stacking until CreateStackedText() and MeasureTextRun() can handle it (if ever).
  wchar_t stack_delimiter = L'/';

  bool in_field = false;
  while (i < length && text_string[i])
  {
    if (!stacking && !in_field && text_string[i] == L'%' && text_string[i + 1] == L'<')  // start of a field
    {
      text.Append(text_string + start, i - start);  // string up to here
      text += L"{\\field %<";  // start field
      i += 2;  // skip "%<"
      in_field = true;
      start = i;
      continue;
    }
    else if (in_field && text_string[i] == L'>' && text_string[i + 1] == L'%') // field end
    {
      text.Append(text_string + start, i - start);
      text += L">%}";
      i += 2;
      start = i;
      in_field = false;
      continue;
    }
    else if (!in_field)
    {
      if (!stacking && text_string[i] == L'[' && text_string[i + 1] == L'[')  // stack start
      {
        if (i < length - 2 && text_string[i + 2] == L'[')
          i++;
        else
        {
          text.Append(text_string + start, i - start);  // string up to here
          text += L"{\\stack";  // start stack
          i += 2;  // skip "[["
          if (L'/' == text_string[i] || L'|' == text_string[i])
          {
            stack_delimiter = text_string[i];
            i++;
          }
          wchar_t code[8] = { 0 };

#if defined (ON_RUNTIME_WIN)
          wsprintf(code, L"%d", (int)stack_delimiter);
#endif
#if defined (ON_RUNTIME_APPLE)
          swprintf(code, sizeof(code), L"%d", (int)stack_delimiter);
#endif
          text += code;
          text += L" ";

          stacking = true;
          // Recursive stacking 
          // SubstituteStackTags(text_string, text, length, i, end, depth + 1);  // read stack section
          //i = end;
          start = i;
          continue;
        }
      }
      else if (stack_delimiter == text_string[i])  // stack separator
      {
        text.Append(text_string + start, i - start); // text for current top
        text += stack_delimiter;
        i++;
        start = i;
        continue;
      }
      else if (stacking && text_string[i] == L']' && text_string[i + 1] == L']') // stack end
      {
        text.Append(text_string + start, i - start);  // text from bottom 
        text += L"}";
        i += 2;
        start = i;
        stacking = false;
        continue;
      }
      else
        i++;
    }
    else
      i++;
  }
  text.Append(text_string + start, i - start);  // remaining text
  end = length;
  return true;
}

// sets the m_dimstyle_text_position_properties_hash
bool ON_TextContent::Internal_SetText(
  const wchar_t* rtf_string,
  const ON_DimStyle* dimstyle)
{
  const bool bComposeAndUpdateRtf = true;
  bool rc = Internal_ParseRtf(rtf_string, dimstyle, bComposeAndUpdateRtf);
  return rc;
}

bool ON_TextContent::Internal_ParseRtfDefault(
  const wchar_t* rtf_string,
  bool bComposeAndUpdateRtf
)
{
  const ON_DimStyle* dim_style = nullptr;
  return Internal_ParseRtf(rtf_string, dim_style, bComposeAndUpdateRtf);
}

bool ON_TextContent::Internal_ParseRtf(
  const wchar_t* rtf_string,
  const ON_DimStyle* dimstyle,
  bool bComposeAndUpdateRtf
)
{
  const ON_wString rtf_w_string(rtf_string);
  if (rtf_w_string.IsEmpty())
    return false;

  dimstyle = &ON_DimStyle::DimStyleOrDefault(dimstyle);

  m_dimstyle_text_position_properties_hash
    = (nullptr != dimstyle)
    ? dimstyle->TextPositionPropertiesHash()
    : ON_TextContent::Empty.DimStyleTextPositionPropertiesHash();

  // Turn off recomposing a rtf string for the text
  // so that the source string stored on the text is 
  // what the edit control produced
  // bComposeAndUpdateRtf = false;

  // Call SubstituteStackTags() to change strings like  ABC [[1/2]] DEF
  // to ABC {\stack47 1/2} DEF
  // to encode stacked fractions into a custom rtf tag
  // 47 is the ascii code of the delimiter '/'
  // Do this in a string other than m_text to avoid changing 
  // the text definition while parsing it

  ON_wString text_string;
  int end = 0;
  int length = (int)rtf_w_string.Length();
  if (!SubstituteStackTags(rtf_w_string.Array(), text_string, length, 0, end, 0))
    text_string = rtf_w_string;
  m_text = rtf_w_string;

  m__runs = ON_TextRunArray::EmptyArray;
  Internal_DeleteWrappedRuns();

  ON_TextIterator iter(text_string);
  ON_TextRunBuilder builder(*this, m__runs, dimstyle, dimstyle->TextHeight(), ON_UNSET_COLOR);
  ON_RtfParser parser(iter, builder);
  ON_wString str;
  bool rc = parser.Parse();
  if (rc)
    rc = ON_TextContent::MeasureTextContent(this, true, false);
  if (rc)
    m_default_font = &dimstyle->ParentDimStyleFont();
  if (rc && bComposeAndUpdateRtf)
  {
    rc = RtfComposer::Compose(this, str, false);
    if (rc)
    {
      m_text = str;
    }
  }

  return rc;
}

const ON_wString ON_TextContent::RichText() const
{
  return m_text;
}

const ON_wString ON_TextContent::RichTextFromRuns(ON::RichTextStyle rich_text_style) const
{
  ON_wString rich_text;

  switch (rich_text_style)
  {
  case ON::RichTextStyle::Windows10SDK:
    if (!RtfComposer::Compose(this, rich_text, true))
      rich_text.Empty();
    break;

  case ON::RichTextStyle::AppleOSXSDK:
    rich_text = RtfComposer::ComposeAppleRTF(this);
    break;

  default:
    break;
  };

  return rich_text;
}

const ON_wString ON_TextContent::PlatformRichTextFromRuns() const
{
  return RichTextFromRuns(ON::RichTextStyleFromCurrentPlatform());
}

const ON_wString ON_TextContent::PlainTextWithFields() const
{
  return Internal_GetPlainText(false, false);
}

const ON_wString ON_TextContent::PlainTextWithFields(ON_SimpleArray<ON_3dex>* runmap) const
{
  return Internal_GetPlainText(false, false, runmap);
}


const ON_wString ON_TextContent::PlainText() const
{
  return Internal_GetPlainText(true, false);
}

const ON_wString ON_TextContent::WrappedPlainTextWithFields() const
{
  return Internal_GetPlainText(false, true);
}


const ON_wString ON_TextContent::WrappedPlainText() const
{
  return Internal_GetPlainText(true, true);
}



ON_SHA1_Hash ON_TextRunArray::TextRunArrayContentHash() const
{
  return TextRunArrayContentHash(true);
}

/*
Parameters:
  bEvaluateFields - [in]
    true - hash text with fields evaluated
    false - hash text with fields unevaluated
Returns:
  A hash of the information that determines the text content
  without evaluating the fields.
*/
ON_SHA1_Hash ON_TextRunArray::TextRunArrayContentHash(
  bool bEvaluateFields
) const
{
  const int count = Count();
  ON_SHA1 sha1;
  for (int i = 0; i < count; i++)
  {
    const ON_TextRun* run = m_a[i];
    if (nullptr == run)
      continue;
    const ON_SHA1_Hash run_hash = run->TextRunContentHash(bEvaluateFields);
    sha1.AccumulateSubHash(run_hash);
  }
  return sha1.Hash();
}

ON_SHA1_Hash ON_TextContent::TextContentHash() const
{
  size_t size = sizeof(*this);
  size_t runs_offset = ((bool*)&m__runs) - ((bool*)this);
  size_t wrap_offset = ((bool*)&m_bWrapText) - ((bool*)this);
  size = size; // 216
  runs_offset = runs_offset; // 56
  wrap_offset = wrap_offset; // 50

  return TextContentHash(true, true);
}

void ON_TextContent::Internal_ClearTextContentHash() const
{
  m_text_content_sub_hash = ON_SHA1_Hash::ZeroDigest;
  m_text_content_bbox_hash = ON_SHA1_Hash::ZeroDigest;
  m_text_content_bbox = ON_BoundingBox::EmptyBoundingBox;
}

ON_SHA1_Hash ON_TextContent::Internal_TextContentSubHash() const
{
  if (ON_SHA1_Hash::ZeroDigest == m_text_content_sub_hash)
  {
    ON_SHA1 sha1;
    sha1.AccumulateString(m_text);
    sha1.AccumulateSubHash(m_dimstyle_text_position_properties_hash);
    if (m_bWrapText && m_rect_width > 0 && m_rect_width < 1.0e300)
    {
      sha1.AccumulateDouble(m_rect_width);
    }
    if ( 0.0 != m_rotation_radians)
    {
      sha1.AccumulateDouble(m_rotation_radians);
    }
    sha1.AccumulateUnsigned8(static_cast<unsigned char>(m_h_align));
    sha1.AccumulateUnsigned8(static_cast<unsigned char>(m_v_align));
    m_text_content_sub_hash = sha1.Hash();
  }
  return m_text_content_sub_hash;
}

ON_SHA1_Hash ON_TextContent::TextContentHash(
    bool bApplyWrapping,
    bool bEvaluateFields
  ) const
{
  // At this point in time, runs are modified
  // without calling "set" functions on ON_TextContent
  // so the sha1 needs to be calculated as follows:
  ON_SHA1 sha1;

  // hash of information we can watch get changed.
  ON_SHA1_Hash text_content_sub_hash = Internal_TextContentSubHash();


  sha1.AccumulateSubHash(text_content_sub_hash);
  sha1.AccumulateSubHash(m_dimstyle_text_position_properties_hash);

  // hash of run information that sometimes gets changed
  // without calling an ON_TextContent setter function.
  bool bRaw = (false == bApplyWrapping);
  const ON_TextRunArray* runs = TextRuns(bRaw);
  const int run_count
    = (nullptr != runs)
    ? runs->Count()
    : 0;

  for (int i = 0; i < run_count; i++)
  {
    const ON_TextRun* run = (*runs)[i];
    if (nullptr == run)
      continue;
    const ON_SHA1_Hash run_hash = run->TextRunContentHash(bEvaluateFields);
    sha1.AccumulateInteger32(i);
    sha1.AccumulateSubHash(run_hash);
  }

  return sha1.Hash();
}

const ON_wString ON_TextContent::Internal_GetPlainText(bool evaluate_fields, bool wrapped) const
{
  return Internal_GetPlainText(evaluate_fields, wrapped, nullptr);
}

const ON_wString ON_TextContent::Internal_GetPlainText(bool evaluate_fields, bool wrapped, ON_SimpleArray<ON_3dex>* runmap) const
{
  ON_wString plaintext;
  ON_TextRunArray* runs = TextRuns(!wrapped);
  if (nullptr == runs)
    return plaintext;
  if (nullptr != runmap)
    runmap->Empty();

  int runcount = runs->Count();
  int nlcount = 0;
  bool multiline = false;
  for (int ri = 0; ri < runcount; ri++)
  {
    ON_TextRun* run = (*runs)[ri];
    if (0 != run)
    {
      if (ON_TextRun::RunType::kText == run->Type() && 0 < nlcount)
        multiline = true;
      else if (ON_TextRun::RunType::kNewline == run->Type() ||
        ON_TextRun::RunType::kParagraph == run->Type())
        nlcount++;
      else if (wrapped && ON_TextRun::RunType::kSoftreturn == run->Type())
        nlcount++;
    }
  }
  for (int ri = 0; ri < runcount; ri++)
  {
    ON_TextRun* run = (*runs)[ri];
    if (0 != run)
    {
      if (ON_TextRun::RunType::kText == run->Type() ||
        ON_TextRun::RunType::kField == run->Type())
      {
        const wchar_t* str = evaluate_fields
          ? run->DisplayString()
          : run->TextString();
        if (nullptr != str)
        {
          if (nullptr != runmap)
          {
            ON_3dex& map = runmap->AppendNew();
            map.i = ri;
            map.j = plaintext.Length();
            map.k = (int)wcslen(str);
          }
          plaintext += str;
        }
      }
      else if (multiline)
      {
        if (ON_TextRun::RunType::kNewline == run->Type() || ON_TextRun::RunType::kParagraph == run->Type())
        {
          if (!wrapped)
            plaintext += L'\r';
          plaintext += L'\n';
        }
        else if (wrapped && ON_TextRun::RunType::kSoftreturn == run->Type())
        {
          plaintext += L'\n';
        }
      }
    }
  }
  return plaintext;
}

bool ON_TextContent::Create(
  const wchar_t* RtfString,
  ON::AnnotationType annotation_type,
  const ON_DimStyle* dimstyle
)
{
  bool bWrapped = false;
  const double rect_width = ON_TextContent::Empty.FormattingRectangleWidth();
  const double text_rotation_radians = ON_TextContent::Empty.TextRotationRadians();
  return Create(
    RtfString,
    annotation_type,
    dimstyle,
    bWrapped,
    rect_width,
    text_rotation_radians
  );
}

bool ON_TextContent::Create(
  const wchar_t* RtfString,
  ON::AnnotationType annotation_type,
  const ON_DimStyle* dimstyle,
  bool bWrapped,
  double rect_width,
  double text_rotation_radians
)
{
  //if (fabs(plane.origin.DistanceTo(ON_3dPoint::Origin)) > ON_ZERO_TOLERANCE)
  //  bWrapped = bWrapped;
  ON::AnnotationType alignment_annotation_type = ON_TextContent::Internal_AlignmentAnnotationType(annotation_type);
  *this = ON_TextContent::Empty;

  dimstyle = &ON_DimStyle::DimStyleOrDefault(dimstyle);

  const double text_height = dimstyle->TextHeight();

  ON::TextHorizontalAlignment h_align = ON::TextHorizontalAlignment::Center;
  ON::TextVerticalAlignment v_align = ON::TextVerticalAlignment::Middle;

  switch (alignment_annotation_type)
  {
  case ON::AnnotationType::Leader:
    h_align = dimstyle->LeaderTextHorizontalAlignment();
    v_align = dimstyle->LeaderTextVerticalAlignment();
    break;
  case ON::AnnotationType::Text:
    h_align = dimstyle->TextHorizontalAlignment();
    v_align = dimstyle->TextVerticalAlignment();
    break;
  case ON::AnnotationType::Diameter:
  case ON::AnnotationType::Radius:
    h_align = dimstyle->LeaderTextHorizontalAlignment();
    v_align = ON::TextVerticalAlignment::MiddleOfTop; //dimstyle->LeaderTextVerticalAlignment();
    break;
  default:
    break;
  }

  // Parse string, create runs, find font, set plane & height
  //SetHeight(text_height); // Has to come later after runs are made: Rh-36167
  m_h_align = h_align;
  m_v_align = v_align;
  SetTextIsWrapped(bWrapped);
  m_rect_width
    = (rect_width > 0.0 && rect_width < ON_TextContent::Empty.FormattingRectangleWidth())
    ? rect_width
    : 0.0;
  m_rotation_radians
    = (text_rotation_radians > -2.0*ON_PI && text_rotation_radians < 2.0*ON_PI)
    ? text_rotation_radians
    : 0.0;
  m_annotation_type = annotation_type;

  // This call sets the m_dimstyle_text_position_properties_hash
  // on this text to match the one on the dimstyle
  bool rc = Internal_SetText(RtfString, dimstyle);
  if (rc)
  {
    if (TextIsWrapped() && (m_rect_width == m_rect_width) && 0 < m_rect_width) // NAN test
      WrapText(m_rect_width);
    // This line has to come after there are some runs, here made by Internal_SetText()
    // Otherwise, it sets the m_textheight variable and leaves the runs are then 
    // sized according to the dimstyle text height  Rh-36167
    Internal_SetRunTextHeight(text_height);
  }
  else
    Internal_Destroy();

  return rc;
}

bool ON_TextContent::ReplaceTextString(
  const wchar_t* RtfString,
  ON::AnnotationType annotation_type,
  const ON_DimStyle* dimstyle
)
{
  if (annotation_type == ON::AnnotationType::Unset)
    ON_ERROR("Annotation type should not be Unset here\n");
  Internal_Destroy();
  bool rc = Create(RtfString, annotation_type, dimstyle, m_bWrapText, m_rect_width, m_rotation_radians);
  return rc;
}

bool ON_TextContent::RebuildRuns(
  ON::AnnotationType annotation_type,
  const ON_DimStyle* dimstyle
)
{
  ON_wString rtfstring = RtfText();
  Internal_Destroy();
  bool rc = Create(rtfstring, annotation_type, dimstyle, m_bWrapText, m_rect_width, m_rotation_radians);
  return rc;
}


bool ON_TextContent::RunReplaceString(
  const wchar_t* repl_str,
  int start_run_idx,
  int start_run_pos,
  int end_run_idx,
  int end_run_pos)
{
  if (nullptr == repl_str)
    repl_str = L"";
  const ON_TextRunArray* text_runs = TextRuns(true);
  if (nullptr == text_runs)
    return false;
  if (0 > start_run_idx || 0 > start_run_pos || start_run_idx > end_run_idx || end_run_idx >= text_runs->Count())
    return false;
  const ON_TextRun* start_run = (*text_runs)[start_run_idx];
  const ON_TextRun* end_run = (*text_runs)[end_run_idx];
  if (nullptr == start_run || nullptr == end_run)
    return false;
  if (start_run->Type() != ON_TextRun::RunType::kText && start_run->Type() != ON_TextRun::RunType::kField)
    return false;
  if (end_run->Type() != ON_TextRun::RunType::kText && end_run->Type() != ON_TextRun::RunType::kField)
    return false;
  ON_wString start_run_string = start_run->TextString();
  ON_wString end_run_string = end_run->TextString();
  int start_string_length = start_run_string.Length();
  int end_string_length = end_run_string.Length();
  if (start_run_pos >= start_string_length || end_run_pos >= end_string_length)
    return false;

  ON_wString new_string;
  if (start_run_pos > 0)
    new_string = start_run_string.Left(start_run_pos);
  new_string += repl_str;
  if (end_run_idx == start_run_idx)
    new_string += start_run_string.Right(end_string_length - end_run_pos - 1);

  ON__UINT32* cp = nullptr;
  int cpcount = ON_TextContext::ConvertStringToCodepoints(new_string, cp);

  ON_TextContent* new_text_content = Duplicate();
  ON_TextRunArray* new_text_runs = new_text_content->TextRuns(true);
  ON_TextRun* new_start_run = ON_TextRun::GetManagedTextRun(*(*text_runs)[start_run_idx]);
  new_start_run->SetUnicodeString(cpcount, cp);
  new_text_runs->RemoveRun(start_run_idx);
  new_text_runs->InsertRun(start_run_idx, new_start_run);

  int remcount = 0;
  for (int ri = start_run_idx+1; ri < end_run_idx; ri++)
  {
    new_text_runs->RemoveRun(ri);
    remcount++;
  }
  end_run_idx -= remcount;

  if (end_run_idx > start_run_idx)
  {
    if (end_run_pos < end_string_length - 1)
    {
      new_string = end_run_string.Right(end_string_length - end_run_pos - 1);
      ON_TextRun* new_end_run = ON_TextRun::GetManagedTextRun(*(*text_runs)[end_run_idx]);

      cp = nullptr;
      cpcount = ON_TextContext::ConvertStringToCodepoints(new_string, cp);
      new_end_run->SetUnicodeString(cpcount, cp);
      new_text_runs->RemoveRun(end_run_idx);
      new_text_runs->InsertRun(end_run_idx, new_end_run);
    }
    else
      new_text_runs->RemoveRun(end_run_idx);
  }

  m__runs = *new_text_runs;

  return true;
}


//-----------------------

void ON_TextContent::Internal_SetRunTextHeight(double height)
{
  const bool wrapped = (nullptr != m__wrapped_runs);
  Internal_DeleteWrappedRuns();
  DestroyRuntimeCache();
  Internal_ClearTextContentHash();
  double w = FormattingRectangleWidth();
  m__runs.SetTextHeight(height);
  ON_TextContent::MeasureTextContent(this, true, false);
  if (wrapped)
    WrapText(w);
}


ON::TextHorizontalAlignment ON_TextContent::RuntimeHorizontalAlignment() const
{
  return m_runtime_halign;
}

void ON_TextContent::SetRuntimeHorizontalAlignment(ON::TextHorizontalAlignment halign) const
{
  m_runtime_halign = halign;
}

void ON_TextContent::GetAlignment(ON::TextHorizontalAlignment& horz, ON::TextVerticalAlignment& vert) const
{
  horz = m_h_align;
  vert = m_v_align;
}

void ON_TextContent::SetAlignment(
  ON::TextHorizontalAlignment horz,
  ON::TextVerticalAlignment vert
)
{
  if (vert != m_v_align)
  {
    m_h_align = horz;
    m_v_align = vert;
  }
  else if (horz != m_h_align)
  {
    RealignTextRuns(horz);
  }

  m_h_align = horz;
  m_v_align = vert;
  MeasureTextContent(this, true, m_bWrapText);
  Internal_ClearTextContentHash();
}

double ON_TextContent::FormattingRectangleWidth() const
{
  return m_rect_width;
}

void ON_TextContent::SetFormattingRectangleWidth(double width)
{
  if (ON_IsValid(width) && !isnan(width))
  {
    m_rect_width = width;
  }
}

double ON_TextContent::TextRotationRadians() const
{
  return m_rotation_radians;
}

void ON_TextContent::SetTextRotationRadians(double rotation)
{
  if (ON_IsValid(rotation) && !isnan(rotation))
  {
    double twopi = ON_PI * 2.0;
    if (fabs(rotation) >= twopi)
      rotation = fmod(rotation, twopi);
    m_rotation_radians = rotation;
  }
}

double ON_TextContent::TextRotationDegrees() const
{
  return TextRotationRadians() * ON_RADIANS_TO_DEGREES;
}

void ON_TextContent::SetTextRotationDegrees(double rotation)
{
  SetTextRotationRadians(rotation * ON_DEGREES_TO_RADIANS);
}

unsigned int ON_TextContent::EvaluationSerialNumber() const
{
  return m_run_evaluation_sn;
}

void ON_TextContent::SetEvaluationSerialNumber(unsigned int sn) const
{
  m_run_evaluation_sn = sn;
}

// This realigns from current horizontal alignment to new horizontal alignment
static void RealignTextRunArray(ON_TextRunArray& runs, ON::TextHorizontalAlignment current_h_align, ON::TextHorizontalAlignment new_h_align)
{
  if (current_h_align != new_h_align)
  {
    double dx = 0.0;
    int runcount = runs.Count();
    for (int i = 0; i < runcount; i++)
    {
      ON_TextRun* run = runs[i];
      if (nullptr != run)
      {
        const ON_BoundingBox& box = run->BoundingBox();
        double w = box.m_max.x - box.m_min.x;
        if (w > dx)
          dx = w;
      }
    }
    if (ON::TextHorizontalAlignment::Left == current_h_align)
    {
      if (ON::TextHorizontalAlignment::Center == new_h_align)
        dx = -dx / 2.0;
      else if (ON::TextHorizontalAlignment::Right == new_h_align)
        dx = -dx;
    }
    else if (ON::TextHorizontalAlignment::Center == current_h_align)
    {
      if (ON::TextHorizontalAlignment::Left == new_h_align)
        dx = dx / 2.0;
      else if (ON::TextHorizontalAlignment::Right == new_h_align)
        dx = -dx / 2.0;
    }
    else if (ON::TextHorizontalAlignment::Right == current_h_align)
    {
#if defined(ON_DEBUG) && defined(ON_COMPILER_MSC)
      if (ON::TextHorizontalAlignment::Left == new_h_align)
        dx = dx; // good place for a breakpoint
#endif
      if (ON::TextHorizontalAlignment::Center == new_h_align)
        dx = dx / 2.0;
    }
    for (int i = 0; i < runcount; i++)
    {
      ON_TextRun* run = runs[i];
      if (nullptr != run)
      {
        ON_2dVector o = run->Offset();
        o.x += dx;
        run->SetOffset(o);
        //ON_BoundingBox box = run->BoundingBox();
        //ON_2dPoint p0 = box.m_min;
        //ON_2dPoint p1 = box.m_max;
        //p0.x += dx;  
        //p1.x += dx;
        //run->SetBoundingBox(p0, p1);
      }
    }
  }
}

void ON_TextContent::RealignTextRuns(ON::TextHorizontalAlignment new_h_align)
{
  RealignTextRunArray(m__runs, m_h_align, new_h_align);
  if (nullptr != m__wrapped_runs)
    RealignTextRunArray(*m__wrapped_runs, m_h_align, new_h_align);
}

bool ON_TextContent::HasWrappedRuns() const
{
  return (nullptr != m__wrapped_runs && m__wrapped_runs->Count() > 0);
}

bool ON_TextContent::TextIsWrapped() const
{
  return (m_bWrapText);
}

void ON_TextContent::SetTextIsWrapped(bool wrapped)
{
  if (wrapped != m_bWrapText)
  {
    Internal_ClearTextContentHash();
    m_bWrapText = wrapped;
  }
}

// Wrap text to a specified width in model space
bool ON_TextContent::WrapText(double wrapwidth) const
{
  bool rc = false;
  Internal_DeleteWrappedRuns();
  Internal_ClearTextContentHash();
  if (0 < m__runs.Count() && wrapwidth == wrapwidth && wrapwidth > 0.0 && this->TextIsWrapped())
  {
    m__wrapped_runs = new ON_TextRunArray;
    if (nullptr != m__wrapped_runs)
    {
      int newcount = 0;
      int runcount = m__runs.Count();
      double linewidth = 0.0;
      double y_offset = 0.0;
      for (int i = 0; i < runcount; i++)
      {
        newcount += m__runs[i]->WrapTextRun(1, 0, wrapwidth, y_offset, linewidth, *m__wrapped_runs);
      }
      if (runcount <= newcount)
      {
        const_cast<ON_TextContent*>(this)->SetTextIsWrapped(true);
        rc = ON_TextContent::MeasureTextContent(const_cast<ON_TextContent*>(this), false, true);
      }
      else
      {
        delete m__wrapped_runs;
        m__wrapped_runs = nullptr;
      }
    }
  }
  return rc;
}

// virtual
void ON_TextContent::Dump(ON_TextLog& text_log) const // for debugging
{}

bool ON_TextContent::Write(
  ON_BinaryArchive&  archive
) const
{
  const int content_version = 0;
  if (false == archive.BeginWrite3dmAnonymousChunk(content_version))
    return false;
  
  bool rc = false;
  for (;;)
  {
    bool bRichTextStringSaved = false;
    for (;;)
    {
      // NEVER commit code with this define set.
      //
      // This code is used by developers to create files used to test
      // code and UI for handing situations when a font is not installed
      // on a device.
      //
      // To create a missing font test .3dm file, you must modify code 
      // int opennurbs_font.cpp and in opennurbs_text.cpp. 
      // Search for CREATE_MISSING_FONT_TEST_3DM_FILE to find the locations.
//#define CREATE_MISSING_FONT_TEST_3DM_FILE
#if defined(CREATE_MISSING_FONT_TEST_3DM_FILE)
      if (m_text.Length() > 7 && ON_wString::EqualOrdinal( L"{\\rtf1\\", 7, static_cast<const wchar_t*>(m_text), 7, false) )
      {
        // All fonts in the LOGFONT with MISSING_FONT_TEST_valid_logfont_name 
        // will be saved as a family named missing_family_name. 
        // The initial space and terminating ;} are a hack to get the entry in the rtf font table.
        // Keep in mind this is developer hack code for creating files to test
        // handling of missing fonts. Customers never run this code.
        const ON_wString MISSING_FONT_TEST_valid_font_rtf_name(L" Courier New;}");
        if (m_text.Find(static_cast<const wchar_t*>(MISSING_FONT_TEST_valid_font_rtf_name)))
        {
          const ON_wString missing_font_rtf_name(L" Missing Font Test;}");
          ON_wString modified_text(static_cast<const wchar_t*>(m_text));
          if (modified_text.Replace(static_cast<const wchar_t*>(MISSING_FONT_TEST_valid_font_rtf_name), static_cast<const wchar_t*>(missing_font_rtf_name)) > 0)
          {
            if (!archive.WriteString(modified_text))
              break;
            bRichTextStringSaved = true;
            break;
          }
        }
      }
#endif
      // write correct m_text
      if (!archive.WriteString(m_text))
        break;

      bRichTextStringSaved = true;
      break;
    }

    if (false == bRichTextStringSaved)
      break;

    // obsolete plane was always world xy
    if (!archive.WritePlane(ON_Plane::World_xy))
      break;

    if (!archive.WriteDouble(m_rect_width))
      break;
    if (!archive.WriteDouble(m_rotation_radians))
      break;
    unsigned int u = static_cast<unsigned int>(m_h_align);
    if (!archive.WriteInt(u))
      break;
    u = static_cast<unsigned int>(m_v_align);
    if (!archive.WriteInt(u))
      break;

    // OBSOLETE text height
    if (!archive.WriteDouble(1.0))
      break;

    // If performance is an issue, we can start saving m__runs, m__wrapped_runs and m_bbox
    const bool bWrapText = TextIsWrapped();
    if (!archive.WriteBool(bWrapText))
      break;
    rc = true;
    break;
  }
  if (!archive.EndWrite3dmChunk())
    rc = false;
  return rc;

}

bool ON_TextContent::Read(
  ON_BinaryArchive&  archive
)
{
  *this = ON_TextContent::Empty;

  bool bWrappedText = false;

  int content_version = 0;
  if (false == archive.BeginRead3dmAnonymousChunk(&content_version))
    return false;

  bool rc = false;
  rc = false;
  for (;;)
  {
    if (!archive.ReadString(m_text))
      break;
    ON_Plane obsolete_plane;
    if (!archive.ReadPlane(obsolete_plane))
      break;
    if (!archive.ReadDouble(&m_rect_width))
      break;
    if (!archive.ReadDouble(&m_rotation_radians))
      break;
    unsigned int u;
    u = static_cast<unsigned int>(m_h_align);
    if (!archive.ReadInt(&u))
      break;
    m_h_align = ON::TextHorizontalAlignmentFromUnsigned(u);
    u = static_cast<unsigned int>(m_v_align);
    if (!archive.ReadInt(&u))
      break;
    m_v_align = ON::TextVerticalAlignmentFromUnsigned(u);

    double obsolete_textheight;
    if (!archive.ReadDouble(&obsolete_textheight))
      break;
    // If performance is an issue, we can start saving m__runs, m__wrapped_runs and m_bbox
    // Do not set m_bWrappedText here.  The call to WrapText() will set it.
    if (!archive.ReadBool(&bWrappedText))
      break;
    SetTextIsWrapped(bWrappedText);

    rc = true;
    break;
  }

  if (!rc)
    *this = ON_TextContent::Empty;
  if (!archive.EndRead3dmChunk())
    rc = false;
  return rc;

}

int ON_TextContent::Dimension() const
{
  return 3;
}


const ON_BoundingBox ON_TextContent::TextContentBoundingBox() const
{
  ON_TextRunArray* runs = const_cast<ON_TextContent*>(this)->TextRuns(false);
  const int run_count = (nullptr != runs) ? runs->Count() : 0;

  // 28 Aug 2023 S. Baer
  // Computing a content hash takes longer than just computing the bounding box
  // for simple single run situations. Only use the cached bbox when there are
  // more than one run.
  if ( run_count > 1 &&
       m_text_content_bbox.IsValid() &&
       m_text_content_bbox_hash == TextContentHash())
  {
    return m_text_content_bbox;
  }

  m_text_content_bbox_hash = ON_SHA1_Hash::ZeroDigest;
  m_text_content_bbox = ON_BoundingBox::EmptyBoundingBox;

  ON_BoundingBox bbox;

  int nonempty_run_count = 0;
  for (int i = 0; i < run_count; i++)
  {
    ON_TextRun* run = (*runs)[i];
    if (nullptr == run)
      continue;

    if (ON_TextRun::RunType::kText == run->Type() ||
      ON_TextRun::RunType::kField == run->Type())
    {
      ON_BoundingBox runbox = run->BoundingBox();
      if (false == runbox.IsValid())
        continue;

      const ON_2dVector& runoffset = run->Offset();
      if (runoffset.IsValid())
      {
        runbox.m_min.x = runbox.m_min.x + runoffset.x;
        runbox.m_min.y = runbox.m_min.y + runoffset.y;
        runbox.m_max.x = runbox.m_max.x + runoffset.x;
        runbox.m_max.y = runbox.m_max.y + runoffset.y;
      }

      if (0 == nonempty_run_count)
      {
        bbox = runbox;
      }
      else
      {
        if (bbox.m_min.x > runbox.m_min.x)
          bbox.m_min.x = runbox.m_min.x;
        if (bbox.m_min.y > runbox.m_min.y)
          bbox.m_min.y = runbox.m_min.y;
        if (bbox.m_max.x < runbox.m_max.x)
          bbox.m_max.x = runbox.m_max.x;
        if (bbox.m_max.y < runbox.m_max.y)
          bbox.m_max.y = runbox.m_max.y;
      }

      nonempty_run_count++;
    }
  }

  if (0 == nonempty_run_count)
    return ON_BoundingBox::EmptyBoundingBox;

  bbox.m_min.z = 0.0;
  bbox.m_max.z = 0.0;

  if (run_count>1 && bbox.IsValid())
  {
    m_text_content_bbox = bbox;
    m_text_content_bbox_hash = TextContentHash();
  }

  return bbox;
}

bool ON_TextContent::GetBBox(
  double* bmin,
  double* bmax,
  bool grow
) const
{
  if (nullptr == bmin || nullptr == bmax)
    grow = false;

  const ON_BoundingBox text_content_bbox = TextContentBoundingBox();

  ON_BoundingBox bbox;
  if (grow)
  {
    bbox.m_min[0] = bmin[0];
    bbox.m_min[1] = bmin[1];
    bbox.m_min[2] = bmin[2];
    bbox.m_max[0] = bmax[0];
    bbox.m_max[1] = bmax[1];
    bbox.m_max[2] = bmax[2];
    if (bbox.IsValid())
      bbox.Union(text_content_bbox);
    else
      bbox = text_content_bbox;
  }
  else
  {
    bbox = text_content_bbox;
  }

  if (nullptr != bmin)
  {
    for (int i = 0; i < 3; i++)
    {
      bmin[i] = bbox.m_min[i];
    }
  }

  if (nullptr != bmax)
  {
    for (int i = 0; i < 3; i++)
    {
      bmax[i] = bbox.m_max[i];
    }
  }

  return bbox.IsValid();
}



void ON_TextContent::ClearBoundingBox()
{
  Internal_ClearTextContentHash();
}

static void ScaleTextRunHeight(ON_TextRun* run, double htscale)
{
  if (0 == run)
    return;
  run->m_height_scale *= htscale;

  run->SetTextHeight(run->TextHeight() * htscale);
  run->SetOffset(run->Offset() * htscale);
  run->SetAdvance(run->Advance() * htscale);
  ON_BoundingBox box = run->BoundingBox();
  run->SetBoundingBox(ON_2dPoint(box.m_min.x * htscale, box.m_min.y * htscale), ON_2dPoint(box.m_max.x * htscale, box.m_max.y * htscale));


}

bool ON_TextContent::Transform(const ON_Xform& xform)
{
  ON_ERROR("DARN! - wish we never called this function.");
  TransformUserData(xform);

  int runcount = m__runs.Count();

  ON_3dVector ht(0.0, 1.0, 0.0);
  ht.Transform(xform);
  double r = ht.Length();
  double run_text_height = 1.0;
  for (int i = 0; i < runcount; i++)
  {
    const ON_TextRun* run = m__runs[i];
    if (nullptr != run && run->TextHeight() > 0.0)
    {
      run_text_height = run->TextHeight();
      break;
    }
  }
  double l = r * run_text_height;
  if (ON_ZERO_TOLERANCE < fabs(1.0 - r) && ON_ZERO_TOLERANCE < l)
  {
    //run_text_height = l;

    for (int i = 0; i < runcount; i++)
      ScaleTextRunHeight(m__runs[i], r);

    if (nullptr != m__wrapped_runs)
    {
      runcount = m__wrapped_runs->Count();
      for (int i = 0; i < runcount; i++)
        ScaleTextRunHeight((*m__wrapped_runs)[i], r);
    }
  }
  Internal_ClearTextContentHash();
  return true;
}

bool ON_TextContent::GetRun3dCorners(const ON_TextRun* run, ON_3dPoint corners[4]) const
{
  if (nullptr == corners)
    return false;
  if (nullptr == run)
    return false;

  const ON_2dVector offset = run->Offset();
  const ON_BoundingBox run_bbox = run->BoundingBox();

  corners[0] = ON_Plane::World_xy.PointAt(run_bbox.m_min.x + offset.x, run_bbox.m_min.y + offset.y);
  corners[1] = ON_Plane::World_xy.PointAt(run_bbox.m_max.x + offset.x, run_bbox.m_min.y + offset.y);
  corners[2] = ON_Plane::World_xy.PointAt(run_bbox.m_max.x + offset.x, run_bbox.m_max.y + offset.y);
  corners[3] = ON_Plane::World_xy.PointAt(run_bbox.m_min.x + offset.x, run_bbox.m_max.y + offset.y);

  return true;
}


ON_Mesh* ON_TextContent::Get2dPickMesh() const
{
  const ON_TextRunArray* runs = TextRuns(false);
  if (nullptr == runs)
    return nullptr;
  // create a mesh with one tight bounding quad per non-empty line of text
  int runcount = runs->Count();
  if (0 == runcount)
    return nullptr;

  ON_Mesh* mesh = new ON_Mesh(runcount, 4 * runcount, false, false);
  if (nullptr == mesh)
    return nullptr;

  //mesh->EnableDoublePrecisionVertices(true);
  int vi = 0;
  int fi = 0;

  ON_3dPoint p;
  for (int ri = 0; ri < runcount; ri++)
  {
    const ON_TextRun* run = (*runs)[ri];
    if (nullptr == run || ON_TextRun::RunType::kText != run->Type())
      continue;

    const ON_2dVector offset = run->Offset();
    const ON_BoundingBox run_bbox = run->BoundingBox();

    p.Set(run_bbox.m_min.x + offset.x, run_bbox.m_min.y + offset.y, 0.0);
    mesh->SetVertex(vi, p);
    p.Set(run_bbox.m_max.x + offset.x, run_bbox.m_min.y + offset.y, 0.0);
    mesh->SetVertex(vi + 1, p);
    p.Set(run_bbox.m_max.x + offset.x, run_bbox.m_max.y + offset.y, 0.0);
    mesh->SetVertex(vi + 2, p);
    p.Set(run_bbox.m_min.x + offset.x, run_bbox.m_max.y + offset.y, 0.0);
    mesh->SetVertex(vi + 3, p);
    mesh->SetQuad(fi++, vi, vi + 1, vi + 2, vi + 3);
    vi += 4;
  }
  return mesh;
}

ON_Mesh* ON_TextContent::Get3dPickMesh() const
{
  ON_Mesh* mesh = Get2dPickMesh();
  return mesh;
}

ON_Mesh* ON_TextContent::Get3dMaskPickMesh(double maskoffset) const
{
  ON_3dPoint corners[4];
  if (Get3dMaskCorners(maskoffset, corners))
  {
    ON_Mesh* mesh = new ON_Mesh(1, 4, false, false);
    if (nullptr != mesh)
    {
      mesh->SetVertex(0, corners[0]);
      mesh->SetVertex(1, corners[1]);
      mesh->SetVertex(2, corners[2]);
      mesh->SetVertex(3, corners[3]);
      mesh->SetQuad(0, 0, 1, 2, 3);
      return mesh;
    }
  }
  return Get3dPickMesh();
}


bool ON_TextContent::Get2dSize(bool raw, double& width, double& height) const
{
  ON_2dPoint corners[4];
  const ON_TextRunArray* runs = TextRuns(raw);
  if (nullptr != runs && runs->Get2dCorners(corners))
  {
    width = corners[1].x - corners[0].x;
    height = corners[3].y - corners[0].y;
    return true;
  }
  return false;
}

bool ON_TextContent::Get2dCorners
(ON_2dPoint corners[4]) const
{
  if (nullptr == corners)
    return false;
  const ON_TextRunArray* runs = TextRuns(false);
  if (nullptr == runs)
    return false;

  return runs->Get2dCorners(corners);
}

bool ON_TextContent::Get3dCorners(ON_3dPoint corners[4]) const
{
  if (nullptr == corners)
    return false;
  bool rc = false;  ON_2dPoint corners2d[4];
  if (Get2dCorners(corners2d))
  {
    corners[0] = ON_Plane::World_xy.PointAt(corners2d[0].x, corners2d[0].y);
    corners[1] = ON_Plane::World_xy.PointAt(corners2d[1].x, corners2d[1].y);
    corners[2] = ON_Plane::World_xy.PointAt(corners2d[2].x, corners2d[2].y);
    corners[3] = ON_Plane::World_xy.PointAt(corners2d[3].x, corners2d[3].y);
    rc = true;
  }
  return rc;
}

bool ON_TextContent::Get3dMaskCorners(double border, ON_3dPoint corners[4]) const
{
  if (nullptr == corners)
    return false;
  bool rc = false;
  ON_2dPoint corners2d[4];
  if (Get2dCorners(corners2d))
  {
    corners[0] = ON_Plane::World_xy.PointAt(corners2d[0].x - border, corners2d[0].y - border);
    corners[1] = ON_Plane::World_xy.PointAt(corners2d[1].x + border, corners2d[1].y - border);
    corners[2] = ON_Plane::World_xy.PointAt(corners2d[2].x + border, corners2d[2].y + border);
    corners[3] = ON_Plane::World_xy.PointAt(corners2d[3].x - border, corners2d[3].y + border);
    rc = true;
  }
  return rc;
}

bool ON_TextContent::Get3dUnderline(ON_3dPoint ends[2], double scaled_gap) const
{
  if (nullptr == ends)
    return false;
  bool rc = false;
  ON_2dPoint corners2d[4];
  if (Get2dCorners(corners2d))
  {
    ends[0] = ON_Plane::World_xy.PointAt(corners2d[0].x, corners2d[0].y - scaled_gap);
    ends[1] = ON_Plane::World_xy.PointAt(corners2d[1].x, corners2d[1].y - scaled_gap);
    rc = true;
  }
  return rc;
}

// returns the base point and with grip using the current alignments
void ON_TextContent::GetGripPoints(ON_2dPoint& base, ON_2dPoint& width) const
{
  ON_2dPoint p[4];
  base.Set(0.0, 0.0);
  width.Set(0.0, 1.0);
  Get2dCorners(p);
  switch (m_h_align)
  {
  default: //case ON::TextHorizontalAlignment::Left:
  {
    width = (p[1] + p[2]) / 2.0;
    switch (m_v_align)
    {
    default: //case ON::TextVerticalAlignment::Bottom:
      base = p[0];
      break;
    case ON::TextVerticalAlignment::Middle:
      base = (p[0] + p[3]) / 2.0;
      break;
    case ON::TextVerticalAlignment::Top:
      base = p[3];
      break;
    }
    break;
  }
  case ON::TextHorizontalAlignment::Center:
  {
    width = (p[1] + p[2]) / 2.0;
    switch (m_v_align)
    {
    default: //case ON::TextVerticalAlignment::Bottom:
      base = (p[0] + p[1]) / 2.0;
      break;
    case ON::TextVerticalAlignment::Middle:
      base = (p[0] + p[2]) / 2.0;
      break;
    case ON::TextVerticalAlignment::Top:
      base = (p[2] + p[3]) / 2.0;
      break;
    }
  }
  break;
  case ON::TextHorizontalAlignment::Right:
  {
    width = (p[0] + p[3]) / 2.0;
    switch (m_v_align)
    {
    default: //case ON::TextVerticalAlignment::Bottom:
      base = p[1];
      break;
    case ON::TextVerticalAlignment::Middle:
      base = (p[1] + p[2]) / 2.0;
      break;
    case ON::TextVerticalAlignment::Top:
      base = p[2];
      break;
    }
  }
  break;
  }
}


//static
int ON_TextContent::FindAndStackFractions(ON_TextRunArray* runs, int i, ON_wString wstr)
{
  if (nullptr == runs || 0 > i || runs->Count() - 1 < i
    || wstr.IsEmpty() || ON_TextRun::RunType::kText != (*runs)[i]->Type())
    return 0;

  int added = 0;
  ON_TextRun* run = (*runs)[i];
  run->SetDisplayString(wstr);
  int start = wstr.Find(L"[[");
  if (wstr.Length() < start + 5)
    return 0;

  while (0 <= start && !wstr.IsEmpty())
  {
    int delim = wstr.Find(L'/', start + 3);
    if (0 <= delim)
    {
      int end = wstr.Find(L"]]", delim + 2);
      if (0 <= end)
      {
        // Found a fraction...
        if (0 < start)
        {
          ON_wString startstr = wstr.Left(start);
          run->SetDisplayString(startstr);
        }

        ON_TextRun* stackedrun = ON_TextRun::GetManagedTextRun();
        *stackedrun = *run;
        ON_wString str = wstr.Left(end).Right(end - start - 2);
        stackedrun->SetStacked(ON_TextRun::Stacked::kStacked);
        stackedrun->SetDisplayString(str);
        ON__UINT32* cp = nullptr;
        int cpcount = ON_TextContext::ConvertStringToCodepoints(str, cp);
        ON_TextContent::CreateStackedText(stackedrun, cpcount, cp);
        stackedrun->SetType(ON_TextRun::RunType::kField);
        runs->InsertRun(i + 1, stackedrun);
        added++;

        wstr = wstr.Right(wstr.Length() - end - 2);
        if (!wstr.IsEmpty())
        {
          start = wstr.Find(L"[[");
          if (-1 == start)
          {
            // no more fractions
            ON_TextRun* endrun = ON_TextRun::GetManagedTextRun();
            *endrun = *run;
            endrun->SetDisplayString(wstr);
            endrun->SetType(ON_TextRun::RunType::kField);
            runs->InsertRun(i + 2, endrun);
            added++;
          }
        }
      }
    }
    else
      break;
  }
  return added;
}


bool ON_TextContent::CreateStackedText(ON_TextRun* run)
{

  int cpcount = (int)run->CodepointCount(run->UnicodeString());
  const ON__UINT32* cp = run->UnicodeString();
  return ON_TextContent::CreateStackedText(run, cpcount, cp);

}

bool ON_TextContent::CreateStackedText(ON_TextRun* run, int cpcount, const ON__UINT32* cp, ON__UINT32 stack_delimiter)
{
  if (0 == run)
    return false;

  if (ON_TextRun::RunType::kText != run->Type() && ON_TextRun::RunType::kField != run->Type())
    return false;
  const ON_TextRun::Stacked stacked = run->IsStacked();
  if (ON_TextRun::Stacked::kNone == stacked)
    return false;

  const ON_Font* font = run->Font();
  if (nullptr == font)
    return false;
  // Make 2 runs for the top and bottom of the stack
  ON_TextRun* top_run = nullptr;
  ON_TextRun* bottom_run = nullptr;
  if (nullptr != run->m_stacked_text)
  {
    if (nullptr != run->m_stacked_text->m_top_run)
    {
      *run->m_stacked_text->m_top_run = ON_TextRun::Empty;
    }
    if (nullptr != run->m_stacked_text->m_bottom_run)
    {
      *run->m_stacked_text->m_bottom_run = ON_TextRun::Empty;
    }
    stack_delimiter = run->m_stacked_text->m_separator;
  }
  if (nullptr == top_run)
    top_run = ON_TextRun::GetManagedTextRun();
  if (nullptr == bottom_run)
    bottom_run = ON_TextRun::GetManagedTextRun();

  *top_run = *run;
  *bottom_run = *run;
  top_run->SetStacked(ON_TextRun::Stacked::kNone);
  bottom_run->SetStacked(ON_TextRun::Stacked::kNone);

  if (nullptr != top_run->m_stacked_text)
    delete top_run->m_stacked_text;
  if (nullptr != bottom_run->m_stacked_text)
    delete bottom_run->m_stacked_text;

  top_run->m_stacked_text = nullptr;
  bottom_run->m_stacked_text = nullptr;
  top_run->SetUnicodeString(0, nullptr);
  bottom_run->SetUnicodeString(0, nullptr);
  // break the string into top and bottom strings
  bool foundseparator = false;
  int top_len = 0;

  //int cpcount = (int)run->CodepointCount(run->UnicodeString());
  //const ON__UINT32* cp = run->UnicodeString();
  if (ON_TextRun::Stacked::kTop == stacked)
  {
    top_len = cpcount;
  }
  else if (ON_TextRun::Stacked::kBottom == stacked)
  {
    top_len = 0;
  }
  else
  {
    for (int i = 0; i < cpcount; i++)
    {
      if (stack_delimiter == cp[i])
      {
        top_len = i;
        foundseparator = true;
        break;
      }
    }
  }

  if (ON_TextRun::Stacked::kTop == stacked || ON_TextRun::Stacked::kStacked == stacked)
    top_run->SetUnicodeString(top_len, cp);
  if (ON_TextRun::Stacked::kBottom == stacked)
    bottom_run->SetUnicodeString(cpcount, cp);
  if (ON_TextRun::Stacked::kStacked == stacked)
    bottom_run->SetUnicodeString(cpcount - top_len - 1, cp + top_len + 1);
  top_run->TextString();
  bottom_run->TextString();

  const ON_FontMetrics& fm = font->FontMetrics();

  double font_scale = fm.GlyphScale(run->TextHeight());
  double separator_height = fm.AscentOfI() / 2.0 * font_scale;
  //double separator_height = font->m_strikeout_position * font_scale;
  double separator_size = fm.UnderscoreThickness() * font_scale;
  double height_frac = run->StackHeightFraction();
  double frac_run_height = height_frac * run->TextHeight();

  top_run->SetTextHeight(frac_run_height);
  bottom_run->SetTextHeight(frac_run_height);
  MeasureTextRun(top_run);
  MeasureTextRun(bottom_run);
  //ON_BoundingBox top_box = top_run->BoundingBox();
  //ON_BoundingBox bottom_box = bottom_run->BoundingBox();

  // make a bounding box for the total stack
  double top_width = top_run->BoundingBox().m_max.x - top_run->BoundingBox().m_min.x;
  double bottom_width = bottom_run->BoundingBox().m_max.x - bottom_run->BoundingBox().m_min.x;
  double stack_width = top_width;
  if (bottom_width > top_width)
    stack_width = bottom_width;

  // add separator_size to the right and left edges of total run
  if (ON_TextRun::Stacked::kStacked == stacked)
    stack_width += 2.0 * separator_size;

  double top_dy = separator_height + 1.5 * separator_size;
  double bottom_dy = separator_height - 1.5 * separator_size - (bottom_run->BoundingBox().m_max.y - bottom_run->BoundingBox().m_min.y);

  ON_2dPoint box[2];  // total stacked run bounding box
  box[0].Set(top_run->BoundingBox().m_min.x, bottom_dy);
  box[1].Set(stack_width, top_dy + top_run->BoundingBox().m_max.y);

  if (bottom_run->BoundingBox().m_min.x < box[0].x)
    box[0].x = bottom_run->BoundingBox().m_min.x;

  run->SetBoundingBox(box[0], box[1]);

  // Set up offsets for top and bottom strings
  // from the current point from the previous run.
  // Advance width for the parent run is width of the longest fraction part
  // plus separator size
  ON_2dVector V(0.0, 0.0);
  V.x = stack_width + separator_size;
  run->SetAdvance(V);
  V.x = (stack_width - top_width) / 2.0 - top_run->BoundingBox().m_min.x;
  V.y = top_dy;
  top_run->SetOffset(V);
  V.x = (stack_width - bottom_width) / 2.0 - bottom_run->BoundingBox().m_min.x;
  V.y = bottom_dy;
  bottom_run->SetOffset(V);

  if (nullptr == run->m_stacked_text)
    run->m_stacked_text = new ON_StackedText;
  run->m_stacked_text->m_top_run = top_run;
  run->m_stacked_text->m_bottom_run = bottom_run;
  run->m_stacked_text->m_parent_run = run;
  run->m_stacked_text->m_separator = (wchar_t)stack_delimiter;

  return true;
}

ON_SHA1_Hash ON_TextContent::DimStyleTextPositionPropertiesHash() const
{
  return m_dimstyle_text_position_properties_hash;
}

ON::AnnotationType ON_TextContent::Internal_AlignmentAnnotationType(
  ON::AnnotationType annotation_type
)
{
  switch (annotation_type)
  {
  case ON::AnnotationType::Text:
  case ON::AnnotationType::Leader:
  case ON::AnnotationType::Diameter:
  case ON::AnnotationType::Radius:
    return annotation_type;
  default:
    break;
  }
  return ON::AnnotationType::Unset;
}

bool ON_TextContent::EqualTextPositionProperties(
  ON::AnnotationType annotation_type,
  const class ON_DimStyle* dimstyle
) const
{
  return (
    ON_TextContent::Internal_AlignmentAnnotationType(m_annotation_type) == ON_TextContent::Internal_AlignmentAnnotationType(annotation_type)
    && m_dimstyle_text_position_properties_hash == ON_DimStyle::DimStyleOrDefault(dimstyle).TextPositionPropertiesHash()
    );
}


ON_TextRunArray* ON_TextContent::TextRuns(bool bRaw) const
{

  if (false == bRaw && nullptr != m__wrapped_runs)
    return m__wrapped_runs;

  return &m__runs;
}

const wchar_t* ON_TextContent::RtfText() const
{
  return m_text;
}

const ON_Font& ON_TextContent::DefaultFont() const
{
  if (nullptr != m_default_font)
    return *m_default_font;
  else
    return ON_Font::Default;
}

bool ON_TextContent::ComposeText()
{
  ON_wString rtf;
  ON_wString nothing;
  if (RtfComposer::Compose(this, rtf, false))
  {
    m_text = rtf;
    return true;
  }
  return false;
}

// Sets Run Bounding Box and Advance to Model units
// Those sizes are still subject to scaling for display 
// at annotative scales in details, etc.
// static
bool ON_TextContent::MeasureTextRun(ON_TextRun* run)
{
  if (0 == run)
    return false;

  if (ON_TextRun::RunType::kText != run->Type())
    return false;

  const ON_Font* font = run->Font();
  if (0 == font)
    return false;

  ON_TextBox text_box;
  const int line_count = ON_FontGlyph::GetGlyphListBoundingBox(run->DisplayString(), font, text_box);
  bool rc = (line_count > 0 && text_box.IsSet());
  if (line_count == 0 && ON_TextRun::RunType::kText == run->Type())
    run->SetBoundingBox(ON_2dPoint(0,0), ON_2dPoint(0,0));

  if (rc)
  {
    // Uses text height in WCS and character (I) height in font units to 
    // Convert Font units to Model units
    double height_scale = run->HeightScale(font);

    ON_Xform scale_xform(ON_Xform::DiagonalTransformation(height_scale));

    ON_2dPoint minpt(text_box.m_bbmin.i, text_box.m_bbmin.j), maxpt(text_box.m_bbmax.i, text_box.m_bbmax.j);
    ON_2dVector advance(text_box.m_advance.i, text_box.m_advance.j);
    minpt.Transform(scale_xform);
    maxpt.Transform(scale_xform);
    advance.Transform(scale_xform);
    // Store bbox and advance on ON_TextRun in Model units not scaled by annotation scale
    if (ON_TextRun::RunType::kText == run->Type())
      run->SetBoundingBox(minpt, maxpt);
    run->SetAdvance(advance);
  }
  return rc;
}

double ON_TextContent::GetLinefeedHeight(ON_TextRun& run)
{
  double lfht = ON_FontMetrics::DefaultLineFeedRatio; // (1.6)
  if (nullptr != run.Font())
  {
    // March 2017 Dale Lear asks:
    //   Why not use run.Font()->FontMetrics().LineSpace() instead
    //   of this?
    const double text_height = run.TextHeight();
    const double legacy_lfht = ON_FontMetrics::DefaultLineFeedRatio * text_height;

    // September 2018 Dale Lear
    // Fix for https://mcneel.myjetbrains.com/youtrack/issue/RH-48824
    //
    // In an attempt to cause minimal distruption to the line spacing
    // in existing files using common fonts 
    // (Arial, Klavika, Helvetica, City/Country Blueprint, ...)
    // AND fix the bug for fonts like Microsoft Himalaya, I am switching
    // to using line spacing value from the font metrics, BUT, I use
    // this value only when it is substantually larger than the
    // "1.6*HeightOfI" value we've been using since Rhino 4.
    //
    const ON_FontMetrics& fm = run.m_managed_font->FontMetrics();
    const double ascent_of_I = fm.AscentOfCapital(); // legacy "height of I"
    const double font_line_space = fm.LineSpace(); // font designer's line spacing
    const double font_metric_lfht
      = (ascent_of_I > 0.0)
      ? (text_height / ascent_of_I)*font_line_space
      : 0.0;

    // The 1.25 threshold value was picked so that the fonts
    // Arial, Arial Black, City Blueprint, Country Blueprint, Klavika*,
    // Helvetica, Technic, Bahnschrift, Segoe UI, Courier, Franklin Gothic,
    // Malgun Gothic, Futura, Lucida, Tahoma will continue to use line spacing
    // that the have in Rhino 4, 5, 6 (up to Setp 2018). These fonts are common
    // and lots of existing files have drawings with text blocks that will
    // have incorrect spacing if we use the font designer's spacing.
    // The font Microsoft Himalaya has font_metric_lfht/legacy_lfht = 1.4
    // so it will use the new spacing and be readable. More generally,
    // if font_metric_lfht/legacy_lfht > 1.25, and the font designer set
    // fm.LineSpace() to a reasonable value, then it is likely that
    // multiline text will have overlapping glyphs.
    lfht
      = (font_metric_lfht > 1.25*legacy_lfht)
      ? font_metric_lfht // this fixes https://mcneel.myjetbrains.com/youtrack/issue/RH-48824
      : legacy_lfht;

    if (!(lfht == legacy_lfht))
      ON_TextLog::Null.Print(L"Break");
  }


  return lfht;
}

static void SetLineOffsets(const ON_TextRunArray* runs, int ri, int ri0, ON::TextHorizontalAlignment h_align, double max_line_width, ON_2dVector offset)
{
  if (nullptr == runs)
    return;

  double width = 0.0;
  double osx = 0.0;
  // Get width of this line
  for (int i = ri0; i < ri; i++)
  {
    width += (*runs)[i]->Advance().x;
  }
  if (h_align == ON::TextHorizontalAlignment::Right)
    osx = max_line_width - width;
  else if (h_align == ON::TextHorizontalAlignment::Center)
    osx = (max_line_width - width) / 2.0;

  for (int i = ri0; i < ri; i++)
  {
    if (i == ri0)
      offset.x += osx;
    ON_TextRun* text_run = const_cast<ON_TextRun*>(runs->operator[](i));
    if (nullptr != text_run)
    {
      text_run->SetOffset(offset);
      offset.x += text_run->Advance().x;
    }
  }
}

//static
bool ON_TextContent::MeasureTextContent(ON_TextContent* text, bool raw, bool wrapped)
{
  if (0 == text)
    return false;
  if (!raw && !wrapped)
    return false;

  bool rc0 = false, rc1 = false;
  ON_TextRunArray* runs = nullptr;
  if (raw)
  {
    runs = text->TextRuns(true);
    if (nullptr != runs)
      rc0 = ON_TextContent::MeasureTextRunArray(runs, text->m_v_align, text->m_h_align);
  }

  if (wrapped)
  {
    ON_TextRunArray* wruns = text->TextRuns(false);

    if (nullptr != wruns && wruns != runs)
      rc1 = ON_TextContent::MeasureTextRunArray(wruns, text->m_v_align, text->m_h_align);
  }

  ON_BoundingBox bbox;
  //text->GetBBox(&bbox.m_min.x, &bbox.m_max.x, false);

  if (raw && !rc0)
    return false;
  if (wrapped && !rc1)
    return false;
  return true;
}

//static
bool ON_TextContent::MeasureTextRunArray(
  ON_TextRunArray* runs,
  ON::TextVerticalAlignment v_align,
  ON::TextHorizontalAlignment h_align)
{
  if (0 == runs)
    return false;

  bool rc = true;

  int line_index = 0;
  ON_2dPoint bbmin(1e300, 1e300), bbmax(-1e300, -1e300);
  double max_line_width = 0.0, line_width = 0.0;
  double max_line_height = 0.0, line_height = 0.0;
  double total_height = 0.0, linefeed_height = 0.0;
  bool line_start = true;  // at the start of a line of text
  bool line_end = true;    // last run produced a newline


  int run_count = runs->Count();
  ON_2dPoint current_point(0.0, 0.0);
  //double os_width = 0.0;
  ON_TextRun* last_text_run = 0;

  // Find the width of the longest run
  // and total height of all lines
  for (int ri = 0; rc && ri < run_count; ri++)
  {
    ON_TextRun* run = (*runs)[ri];
    if (0 != run)
    {
      run->m_line_index = line_index;
      run->SetOffset(ON_2dVector(0.0, 0.0));
      if (ON_TextRun::RunType::kNewline == run->Type() ||
        ON_TextRun::RunType::kSoftreturn == run->Type() ||
        ON_TextRun::RunType::kParagraph == run->Type())
      {
        // When a linefeed is found, set the advance.y of the run to the linefeed height
        // and if there is an accumulated width wider than the current linewidth, save it.
        total_height += line_height;  // max height for the line
        double lfh = ON_TextContent::GetLinefeedHeight(*run);
        if (lfh > linefeed_height)
          linefeed_height = lfh;
        // Set advance of newline run to linefeed height
        double y = linefeed_height;  // max lf height for the line
                                     // Add just the extra for the line spacing to the height
        total_height += (y - line_height);
        run->SetAdvance(ON_2dVector(0.0, -y));

        // See if this was the longest line
        if (line_width > max_line_width)
          max_line_width = line_width;
        line_width = 0.0;
        line_index++;
        line_start = true;
        line_end = true;
        current_point = current_point + run->Advance();
      }
      else if (ON_TextRun::RunType::kText == run->Type())
      {
        if (run->IsStacked() != ON_TextRun::Stacked::kNone)
        {
          ON_TextContent::CreateStackedText(run);
        }
        else
        {
          // MeasureTextRun() sets Run Bounding Box and Advance
          ON_TextContent::MeasureTextRun(run);
        }

        line_width += run->Advance().x;  // Add width of this run
        if (run->TextHeight() > line_height)
          line_height = run->TextHeight();   // Increase height if this is highest run so far in this line
        double lfh = ON_TextContent::GetLinefeedHeight(*run);
        if (line_start || lfh > linefeed_height)
          linefeed_height = lfh;         // Increase linefeed height if this is the highest so far in this line
        line_start = false;
        line_end = false;
        last_text_run = run;
      }
      if (max_line_height == 0.0)
        max_line_height = line_height;
    }
  }
  if (!line_end) // last run was text (not a linefeed or paragraph run)
  {
    // Add just the extra for the line spacing to the height
    total_height += linefeed_height;

    // See if this was the longest line
    if (line_width > max_line_width)
      max_line_width = line_width;
  }

  int ri0 = 0, ri1 = 0;
  ON_2dVector offset(0.0, 0.0);
  for (int ri = 0; rc && ri < run_count; ri++)
  {
    ri0 = ri;
    ON_TextRun* run = (*runs)[ri];
    if (nullptr != run)
    {
      if (ON_TextRun::RunType::kNewline == run->Type() ||
        ON_TextRun::RunType::kSoftreturn == run->Type() ||
        ON_TextRun::RunType::kParagraph == run->Type())
      {
        SetLineOffsets(runs, ri0, ri1, h_align, max_line_width, offset);
        offset.x = 0.0;
        offset.y += run->Advance().y;
        ri1 = ri0 + 1;
      }
    }
  }
  if (!line_end) // last run was text so do the last line
    SetLineOffsets(runs, ri0 + 1, ri1, h_align, max_line_width, offset);

  double osy = 0.0, osx = 0.0;

  if (v_align == ON::TextVerticalAlignment::Top)
    osy = -max_line_height;
  else if (v_align == ON::TextVerticalAlignment::Bottom)
    osy = total_height - linefeed_height;
  else if (v_align == ON::TextVerticalAlignment::Middle)
    osy = (total_height - max_line_height - linefeed_height) / 2.0;

  if (h_align == ON::TextHorizontalAlignment::Right)
    osx = -max_line_width;
  else if (h_align == ON::TextHorizontalAlignment::Center)
    osx = -max_line_width / 2.0;

  for (int ri = 0; rc && ri < run_count; ri++)
  {
    ON_TextRun* run = (*runs)[ri];
    if (0 != run) // && run->Type() == kText
    {
      ON_2dVector o = run->Offset();
      o.x += osx;
      o.y += osy;
      run->SetOffset(o);
      if (run->IsStacked() != ON_TextRun::Stacked::kNone && run->m_stacked_text)
      {
        ON_TextRun* srun = run->m_stacked_text->m_top_run;
        if (srun)
        {
          ON_2dVector V(o);
          ON_2dVector sro = srun->Offset();
          V.x += sro.x;
          V.y += sro.y;
          srun->SetOffset(V);
        }

        srun = run->m_stacked_text->m_bottom_run;
        if (srun)
        {
          ON_2dVector V(o);
          ON_2dVector sro = srun->Offset();
          V.x += sro.x;
          V.y += sro.y;
          srun->SetOffset(V);
        }
      }
    }
  }
  return rc;
}


// Dimension text formatting

bool ON_TextContent::FormatTolerance(
  double distance,
  ON::LengthUnitSystem units_in,
  const ON_DimStyle* dimstyle,
  bool alt,
  ON_wString& formatted_string)
{
  ON_wString sDist;
#ifndef ON_TEXT_BRACKET_FRACTION  // Stacked fraction bracket
  bool bracket_stack_frac = false;
#endif

  if (nullptr == dimstyle)
    dimstyle = &ON_DimStyle::Default;

  const ON_DimStyle::LengthDisplay dim_length_display =
    alt
    ? dimstyle->AlternateDimensionLengthDisplay()
    : dimstyle->DimensionLengthDisplay();

  const ON::LengthUnitSystem dim_us
    = alt
    ? dimstyle->AlternateDimensionLengthDisplayUnit(0)
    : dimstyle->DimensionLengthDisplayUnit(0);

  bool bracket_stack_frac = ON_DimStyle::stack_format::None != dimstyle->StackFractionFormat();
  ON_DimStyle::tolerance_format tolstyle = dimstyle->ToleranceFormat();

  int tolprecision = alt ? dimstyle->AlternateToleranceResolution() : dimstyle->ToleranceResolution();
  ON_DimStyle::suppress_zero zs = alt ? dimstyle->AlternateZeroSuppress() : dimstyle->ZeroSuppress();


  double length_factor = 1.0; // dimstyle->LengthFactor();  RH-63775
  double unit_length_factor = ON::UnitScale(units_in, dim_us);
  length_factor *= unit_length_factor;
  if (alt)
  {
    length_factor *= dimstyle->AlternateLengthFactor();
  }

  switch (tolstyle)
  {
  case ON_DimStyle::tolerance_format::None:
    break;

  case ON_DimStyle::tolerance_format::Symmetrical:
  {
    ON_wString sTol;
    double tol_uv = dimstyle->ToleranceUpperValue();
    tol_uv *= length_factor;

    wchar_t decimal_char = dimstyle->DecimalSeparator();
    if (ON_TextContent::FormatLength(tol_uv, dim_length_display, 0.0, tolprecision, zs, bracket_stack_frac, decimal_char, sTol))
    {
      formatted_string += ON_wString::PlusMinusSymbol;
      formatted_string += sTol;
    }
    break;
  }
  case ON_DimStyle::tolerance_format::Deviation:
  {
    double tol_uv = dimstyle->ToleranceUpperValue();
    double tol_lv = dimstyle->ToleranceLowerValue();
    wchar_t tol_uv_sign = L'+';
    wchar_t tol_lv_sign = L'-';

    tol_uv *= length_factor;
    tol_lv *= length_factor;

    if (tol_uv >= 0.0)
      tol_uv_sign = L'+';
    else
      tol_uv_sign = L'-';
    tol_uv = fabs(tol_uv);

    if (tol_lv >= 0.0)
      tol_lv_sign = L'-';
    else
      tol_lv_sign = L'+';
    tol_lv = fabs(tol_lv);

    wchar_t decimal_char = dimstyle->DecimalSeparator();
    ON_wString sTol_uv, sTol_lv;
    // Can't use stacked fractions in tolerances because run stacking isn't recursive in ON_Text
    if (ON_TextContent::FormatLength(tol_uv, dim_length_display, 0.0, tolprecision, zs, false, decimal_char, sTol_uv) &&
      ON_TextContent::FormatLength(tol_lv, dim_length_display, 0.0, tolprecision, zs, false, decimal_char, sTol_lv))
    {
      formatted_string += L" [[";
      formatted_string += L"|";
      formatted_string += tol_uv_sign;
      formatted_string += sTol_uv;
      formatted_string += L"|";
      formatted_string += tol_lv_sign;
      formatted_string += sTol_lv;
      formatted_string += L"]]";
    }
    break;
  }
  case ON_DimStyle::tolerance_format::Limits:
  {
    double tol_uv = dimstyle->ToleranceUpperValue();
    double tol_lv = dimstyle->ToleranceLowerValue();
    
    tol_uv *= length_factor;
    tol_lv *= length_factor;
    
    tol_uv = distance + tol_uv;
    tol_lv = distance - tol_lv;

    wchar_t decimal_char = dimstyle->DecimalSeparator();
    ON_wString sDist_u, sDist_l;
    // Can't use stacked fractions in tolerances because run stacking isn't recursive in ON_Text
    if (ON_TextContent::FormatLength(tol_uv, dim_length_display, 0.0, tolprecision, zs, false, decimal_char, sDist_u) &&
      ON_TextContent::FormatLength(tol_lv, dim_length_display, 0.0, tolprecision, zs, false, decimal_char, sDist_l))
    {
      formatted_string += L" [[";
      formatted_string += L"|";
      formatted_string += sDist_u;
      formatted_string += L"|";
      formatted_string += sDist_l;
      formatted_string += L"]]";
    }
    break;
  }
  }
  return true;
}

bool ON_TextContent::FormatDistance(
  double distance_in,
  ON::LengthUnitSystem units_in,
  const ON_DimStyle* dimstyle,
  bool alt,
  ON_wString& formatted_string)
{
  ON_wString sDist;
#ifndef ON_TEXT_BRACKET_FRACTION  // Stacked fraction bracket
  bool bracket_stack_frac = false;
#endif

  double distance = distance_in;

  if (nullptr == dimstyle)
    dimstyle = &ON_DimStyle::Default;

  const ON_DimStyle::LengthDisplay dim_length_display =
    alt
    ? dimstyle->AlternateDimensionLengthDisplay()
    : dimstyle->DimensionLengthDisplay();

  const ON::LengthUnitSystem dim_us
    = alt
    ? dimstyle->AlternateDimensionLengthDisplayUnit(0)
    : dimstyle->DimensionLengthDisplayUnit(0);

  double length_factor = 
    alt
    ? dimstyle->AlternateLengthFactor()
    : dimstyle->LengthFactor();

  double unit_length_factor = ON::UnitScale(units_in, dim_us);
  distance = unit_length_factor * length_factor * distance_in;

  bool bracket_stack_frac = ON_DimStyle::stack_format::None != dimstyle->StackFractionFormat();

  double roundoff = alt ? dimstyle->AlternateRoundOff() : dimstyle->RoundOff();
  int precision = alt ? dimstyle->AlternateLengthResolution() : dimstyle->LengthResolution();
  ON_DimStyle::suppress_zero zs = alt ? dimstyle->AlternateZeroSuppress() : dimstyle->ZeroSuppress();

  // Fixes rounding error (0.00098 -> 0.001)
  if (fabs(distance) < pow(10.0, -(precision + 1)))
    distance = 0.0;

  wchar_t decimal_char = dimstyle->DecimalSeparator();
  ON_TextContent::FormatLength(distance, dim_length_display, roundoff, precision, zs, bracket_stack_frac, decimal_char, formatted_string);
  return true;
}


bool ON_TextContent::FormatDistanceAndTolerance(
  double distance_in,
  ON::LengthUnitSystem units_in,
  const ON_DimStyle* dimstyle,
  bool alt,
  ON_wString& formatted_string)
{
  if (ON_DimStyle::tolerance_format::Limits != dimstyle->ToleranceFormat())
    ON_TextContent::FormatDistance(distance_in, units_in, dimstyle, alt, formatted_string);
  if (ON_DimStyle::tolerance_format::None != dimstyle->ToleranceFormat())
    ON_TextContent::FormatTolerance(distance_in, units_in, dimstyle, alt, formatted_string);
  
  return true;

}

// static
bool ON_TextContent::FormatDistanceMeasurement(
  double distance_in,
  ON::LengthUnitSystem units_in,
  const ON_DimStyle* dimstyle,
  const wchar_t* user_text,         // Replace "<>" in user_text with formatted dimension
  ON_wString& formatted_string)     // Output
{
  if (nullptr == dimstyle)
    return false;

  formatted_string.Empty();
  if (nullptr == user_text || 0 == user_text[0])
    user_text = L"<>";
  ON_wString user_string(user_text);
  int cpi = user_string.Find(L"<>");

  if (-1 != cpi)
  {
    if (nullptr != dimstyle->Prefix())
      formatted_string += dimstyle->Prefix();

    int len = user_string.Length();
    for (int i = 0; i < len; i++)
    {
      if (i == cpi)
      {
        FormatDistanceAndTolerance(distance_in, units_in, dimstyle, false, formatted_string);
        if (nullptr != dimstyle->Suffix())
          formatted_string += dimstyle->Suffix();
        if (dimstyle->Alternate()) // text alternate units
        {
          if (dimstyle->AlternateBelow())
            formatted_string += L"{\\par}";
          formatted_string += dimstyle->AlternatePrefix();
          FormatDistanceAndTolerance(distance_in, units_in, dimstyle, true, formatted_string);
          formatted_string += dimstyle->AlternateSuffix();
        }
        i++; // skips past the < in <>
      }
      else
        formatted_string += user_string[i];
    }
  }
  else // no "<>" in the string
  {
    //if (nullptr != dimstyle->Prefix())
    //  formatted_string += dimstyle->Prefix();

    int ix = user_string.ReverseFind(L"\\par");
    if (ix >= 0)
    {
      formatted_string += user_string.Left(ix);
      int il = user_string.Length() - ix - 4;
      formatted_string += user_string.Right(il);
    }
    else
    {
      formatted_string += user_string;
    }
    ON_TextContent::FormatTolerance(distance_in, units_in, dimstyle, false, formatted_string);

    //if (nullptr != dimstyle->Suffix())
    //  formatted_string += dimstyle->Suffix();

    if (dimstyle->Alternate()) // text alternate units
    {
      if (dimstyle->AlternateBelow())
        formatted_string += L"{\\par}";
      formatted_string += dimstyle->AlternatePrefix();
      FormatDistanceAndTolerance(distance_in, units_in, dimstyle, true, formatted_string);
      formatted_string += dimstyle->AlternateSuffix();
    }
  }
  return true;
}

// Converts measurement to string, including scale factor, tolerances, pre- and postfix ...
// static
bool ON_TextContent::FormatAngleMeasurement(
  double angle_radians,
  const ON_DimStyle* dimstyle,
  const wchar_t* user_text,
  ON_wString& formatted_string)
{
  if (nullptr == dimstyle)
    return false;

  formatted_string.Empty();
  if (nullptr == user_text || 0 == user_text[0])
    user_text = L"<>";

  ON_wString user_string(user_text);
  ON_wString sNumber(L"");
  int cpi = user_string.Find(L"<>");

  if (-1 == cpi) // No <> token to replace - just print the user text - no substitution
  {
    formatted_string = user_string;
  }
  else
  {
    int len = user_string.Length();
    for (int i = 0; i < len; i++)
    {
      if (i == cpi)
      {
        ON_wString sAngle;

        if (ON_DimStyle::angle_format::DecimalDegrees == dimstyle->AngleFormat() ||
          ON_DimStyle::angle_format::Radians == dimstyle->AngleFormat() ||
          ON_DimStyle::angle_format::Grads == dimstyle->AngleFormat())
        {
          double angle = angle_radians;
          if (ON_DimStyle::angle_format::DecimalDegrees == dimstyle->AngleFormat())
            angle = ON_RADIANS_TO_DEGREES * angle_radians;
          else if (ON_DimStyle::angle_format::Grads == dimstyle->AngleFormat())
            angle = angle_radians * 200.0 / ON_PI;

          double roundoff = dimstyle->AngleRoundOff();
          int resolution = dimstyle->AngleResolution();
          ON_DimStyle::suppress_zero suppress = dimstyle->AngleZeroSuppress();

          wchar_t decimal_char = dimstyle->DecimalSeparator();
          ON_TextContent::FormatAngleStringDecimal(angle, resolution, roundoff, suppress, decimal_char, sAngle);
          if (ON_DimStyle::angle_format::DecimalDegrees == dimstyle->AngleFormat())
            sAngle += ON_wString::DegreeSymbol;
          else if (ON_DimStyle::angle_format::Radians == dimstyle->AngleFormat())
            sAngle += L'r';
          else if (ON_DimStyle::angle_format::Grads == dimstyle->AngleFormat())
            sAngle += L'g';
        }
        else if (ON_DimStyle::angle_format::DegMinSec == dimstyle->AngleFormat())
        {
          wchar_t decimal_char = dimstyle->DecimalSeparator();
          int resolution = dimstyle->AngleResolution();
          ON_TextContent::FormatAngleStringDMS(angle_radians, decimal_char, resolution, sAngle);
        }

        formatted_string += sAngle;

        i++; // skips past the < in <>
      }
      else
        formatted_string += user_string[i];
    }
  }
  return true;
}

bool ON_TextContent::FormatLength(
  double distance,
  ON_DimStyle::LengthDisplay output_lengthdisplay,
  double round_off,
  int resolution,
  ON_DimStyle::suppress_zero zero_suppress,
  bool bracket_fractions,
  wchar_t decimal_char,
  ON_wString & output)
{
  bool rc = ON_NumberFormatter::FormatLength( distance, output_lengthdisplay,  round_off,  resolution, zero_suppress,  bracket_fractions, output);
  if (rc && ON_wString::DecimalAsPeriod != decimal_char)
    output.Replace(ON_wString::DecimalAsPeriod, decimal_char);
  return rc;
}

bool ON_TextContent::FormatAngleStringDMS(
  double angle_degrees,
  wchar_t decimal_char,
  ON_wString& formatted_string)
{
  return ON_TextContent::FormatAngleStringDMS(angle_degrees, decimal_char, 2, formatted_string);
}

bool ON_TextContent::FormatAngleStringDMS(
  double angle_degrees,
  wchar_t decimal_char,
  int resolution,
  ON_wString& formatted_string)
{
  bool rc = ON_NumberFormatter::FormatAngleStringDMS(angle_degrees, resolution, formatted_string);
  if (rc && ON_wString::DecimalAsPeriod != decimal_char)
    formatted_string.Replace(ON_wString::DecimalAsPeriod, decimal_char);
  return rc;
}

bool ON_TextContent::FormatAngleStringDecimal(
  double angle_radians,
  int resolution,
  double roundoff,
  ON_DimStyle::suppress_zero zero_suppression,
  wchar_t decimal_char,
  ON_wString& formatted_string)
{
  bool rc = ON_NumberFormatter::FormatAngleStringDecimal(angle_radians, resolution, roundoff, zero_suppression, formatted_string);
  if (rc && ON_wString::DecimalAsPeriod != decimal_char)
    formatted_string.Replace(ON_wString::DecimalAsPeriod, decimal_char);
  return rc;
}

bool ON_TextContent::FormatArea(
  double area_in,
  ON::LengthUnitSystem units_in,
  const ON_DimStyle* dimstyle,
  bool alt,
  ON_wString& formatted_string)
{
  return ON_TextContent::FormatAreaOrVolume(area_in, true, units_in, dimstyle, alt, formatted_string);
}

bool ON_TextContent::FormatVolume(
  double volume_in,
  ON::LengthUnitSystem units_in,
  const ON_DimStyle* dimstyle,
  bool alt,
  ON_wString& formatted_string)
{
  return ON_TextContent::FormatAreaOrVolume(volume_in, false, units_in, dimstyle, alt, formatted_string);
}

bool ON_TextContent::FormatAreaOrVolume(
  double area_or_volume_in,
  bool format_area,
  ON::LengthUnitSystem units_in,
  const ON_DimStyle* dimstyle,
  bool alt,
  ON_wString& formatted_string)
{
  double value = area_or_volume_in;

  if (nullptr == dimstyle)
    dimstyle = &ON_DimStyle::Default;

  const ON::LengthUnitSystem dim_us
    = alt
    ? dimstyle->AlternateDimensionLengthDisplayUnit(0)
    : dimstyle->DimensionLengthDisplayUnit(0);

  double length_factor =
    alt
    ? dimstyle->AlternateLengthFactor()
    : dimstyle->LengthFactor();

  double unit_length_factor = ON::UnitScale(units_in, dim_us);
  value = format_area ? 
    unit_length_factor * unit_length_factor * length_factor * area_or_volume_in :
    unit_length_factor * unit_length_factor * unit_length_factor * length_factor * area_or_volume_in;

  double roundoff = alt ? dimstyle->AlternateRoundOff() : dimstyle->RoundOff();
  int precision = alt ? dimstyle->AlternateLengthResolution() : dimstyle->LengthResolution();
  ON_DimStyle::suppress_zero zs = alt ? dimstyle->AlternateZeroSuppress() : dimstyle->ZeroSuppress();

  if (fabs(value) < pow(10.0, -(precision + 1)))
    value = 0.0;

  wchar_t decimal_char = dimstyle->DecimalSeparator();

  ON_DimStyle::OBSOLETE_length_format output_format = ON_DimStyle::OBSOLETE_length_format::Decimal;

  bool rc = ON_NumberFormatter::FormatNumber(
    value,
    output_format,
    roundoff,
    precision,
    zs,
    false,
    formatted_string);

  if (rc && ON_wString::DecimalAsPeriod != decimal_char)
    formatted_string.Replace(ON_wString::DecimalAsPeriod, decimal_char);

  return rc;
}

ON::TextVerticalAlignment ON::TextVerticalAlignmentFromUnsigned(
  unsigned int vertical_alignment_as_unsigned
)
{
  switch (vertical_alignment_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON::TextVerticalAlignment::Top);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::TextVerticalAlignment::MiddleOfTop);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::TextVerticalAlignment::BottomOfTop);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::TextVerticalAlignment::Middle);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::TextVerticalAlignment::MiddleOfBottom);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::TextVerticalAlignment::Bottom);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::TextVerticalAlignment::BottomOfBoundingBox);
  }
  ON_ERROR("invalid vertical_alignment_as_unsigned parameter.");
  return (ON::TextVerticalAlignment::Top);
}

ON::TextHorizontalAlignment ON::TextHorizontalAlignmentFromUnsigned(
  unsigned int horizontal_alignment_as_unsigned
)
{
  switch (horizontal_alignment_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON::TextHorizontalAlignment::Left);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::TextHorizontalAlignment::Center);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::TextHorizontalAlignment::Right);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::TextHorizontalAlignment::Auto);
  }
  ON_ERROR("invalid vertical_alignment_as_unsigned parameter.");
  return (ON::TextHorizontalAlignment::Left);
}

ON::TextOrientation ON::TextOrientationFromUnsigned(
  unsigned int orientation_as_unsigned
)
{
  switch (orientation_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON::TextOrientation::InPlane);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::TextOrientation::InView);
  }
  ON_ERROR("invalid orientation_as_unsigned parameter.");
  return (ON::TextOrientation::InPlane);
}





