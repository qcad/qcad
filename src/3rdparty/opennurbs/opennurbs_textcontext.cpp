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

// static
int ON_TextContext::ConvertCodepointsToString(int cplen, const ON__UINT32* cp, ON_wString& str_out)
{
  str_out.Empty();
  bool b = sizeof(wchar_t) == sizeof(*cp);
  if (b)
  {
    str_out.Append((wchar_t*)cp, cplen);
    return cplen;
  }

  unsigned int error_status = 0;
  int wc_count = ON_ConvertUTF32ToWideChar(
      0,                 //int bTestByteOrder,
      cp,                //const ON__UINT32* sUTF32,
      cplen,             //int sUTF32_count,
      0,                 //wchar_t* sWideChar,
      0,                 //int sWideChar_count,
      &error_status,     //unsigned int* error_status,
      0xFFFFFFFF,        //unsigned int error_mask,
      0xFFFD,            //ON__UINT32 error_code_point,
      0                  //const ON__UINT32** sNextUTF32
      );
  if(0 < wc_count)
  {
    str_out.ReserveArray(wc_count + 1);
    error_status = 0;
    int ok = ON_ConvertUTF32ToWideChar(
      0,                 //int bTestByteOrder,
      cp,                //const ON__UINT32* sUTF32,
      cplen,             //int sUTF32_count,
      str_out.Array(),       //wchar_t* sWideChar,
      wc_count + 1,      //int sWideChar_count,
      &error_status,     //unsigned int* error_status,
      0xFFFFFFFF,        //unsigned int error_mask,
      0xFFFD,            //ON__UINT32 error_code_point,
      0                  //const ON__UINT32** sNextUTF32
      );
    if (0 < ok)
    {
      str_out.SetLength(wc_count);
    }
  }
  return str_out.Length();
}

//static
int ON_TextContext::ConvertStringToCodepoints(const wchar_t* str, ON__UINT32*& cp)
{
  if (nullptr == str)
    return 0;
  int wcnt = (int)wcslen(str);
  if (0 == wcnt)
    return 0;


  // number of code points is always <= number of wchar_t's.  the +1 is for a null terminator.
  int cpcnt = wcnt + 1;

  ON__UINT32* cp_local = cp;
  cp = nullptr;
  cp_local = (ON__UINT32*)onrealloc(cp_local, cpcnt*sizeof(cp_local[0]));
  if(nullptr == cp_local)
    return 0;

  unsigned int error_status = 0;
  int cnt = ON_ConvertWideCharToUTF32(
    0,             //int bTestByteOrder,
    str,           //const wchar_t* sWideChar,
    wcnt,          //int sWideChar_count,
    cp_local,      //ON__UINT32* sUTF32,
    cpcnt,         //int sUTF32_count,
    &error_status, //unsigned int* error_status,
    0xFFFFFFFF,    //unsigned int error_mask,
    0xFFFD,        //ON__UINT32 error_code_point,
    nullptr        // wchar_t** sNextWideChar
    );

  cp = cp_local;
  return cnt;
}


//static
const ON_wString ON_TextContext::FormatRtfString(
  const wchar_t* rtf_string,
  const ON_DimStyle* dimstyle,
  bool clear_bold, bool set_bold,
  bool clear_italic, bool set_italic,
  bool clear_underline, bool set_underline,
  bool clear_facename, bool set_facename, const wchar_t* override_facename)
{
  ON_wString string_out;
  if (nullptr == rtf_string || 0 == rtf_string[0])
    return string_out;
  size_t len = wcslen(rtf_string);
  if (0 == len)
    return string_out;
  if (nullptr == dimstyle)
    dimstyle = &ON_DimStyle::Default;
  const ON_wString rtf_font_name = ON_Font::RichTextFontName(&dimstyle->Font(),true);

  ON_wString rtf_wstring(rtf_string);
  int rtf = rtf_wstring.Find("rtf1");
  if (-1 == rtf)  // Input is plain text string
  {
    ON_wString font_table_str;
    ON_wString rtf_text_str;
    ON_wString fmts;
    // Keep dimstyle font as f0 in the font table even if we don't need itg here 
    if (set_facename && !rtf_font_name.EqualOrdinal(override_facename, true))
    {
      font_table_str.Format(L"{\\fonttbl{\\f0 %ls;}{\\f1 %ls;}}", rtf_font_name.Array(), override_facename);
      fmts = L"\\f1";
    }
    else  // Use style facename
    {
      font_table_str.Format(L"{\\fonttbl{\\f0 %ls;}}", rtf_font_name.Array());
      fmts = L"\\f0";
    }
    if (set_bold)
      fmts += L"\\b";
    if (set_italic)
      fmts += L"\\i";
    if (set_underline)
      fmts += "L\\ul";

    rtf_wstring.Replace(L"\\", L"\\\\");
    rtf_text_str.Format(L"{%ls %ls}", fmts.Array(), rtf_wstring.Array());
    ON_wString par;
    par.Format(L"}{\\par}{%ls ", fmts.Array());
    rtf_text_str.Replace(L"\n", par.Array());

    rtf_wstring.Format(L"{\\rtf1\\deff0%ls%ls}", font_table_str.Array(), rtf_text_str.Array());
    return rtf_wstring;
  }

  // else Input is RTF string

  ON_RtfStringBuilder builder(dimstyle, 1.0, ON_UNSET_COLOR);
  builder.SetSkipColorTbl(true);

  builder.SetSkipBold(clear_bold);
  builder.SetSkipItalic(clear_italic);
  builder.SetSkipUnderline(clear_underline);
  builder.SetSkipFacename(clear_facename);
  builder.SetMakeBold(set_bold);
  builder.SetMakeItalic(set_italic);
  builder.SetMakeUnderline(set_underline);
  builder.SetMakeFacename(set_facename);
  builder.SetOverrideFacename(override_facename);
  builder.SetDefaultFacename(rtf_font_name);

  if (builder.SettingFacename())
  {
    int ftbl = rtf_wstring.Find(L"fonttbl");
    if (-1 == ftbl)
    {
      ON_wString temp;
      len = rtf_wstring.Length();
      ON_wString str = rtf_wstring.Right(((int)len) - 7);
      temp.Format(L"{\\rtf1{\\fonttbl}%ls", str.Array());
      rtf_wstring = temp;
    }
  }
  len = rtf_wstring.Length();

  ON_TextIterator iter(rtf_wstring.Array(), len);

  ON_RtfParser parser(iter, builder);
  bool rc = parser.Parse();
  if (rc)
    string_out = builder.OutputString();

  return string_out;
}

//static
bool ON_TextContext::RtfFirstCharProperties(const wchar_t* rtf_string,
  bool& bold, bool& italic, bool& underline, ON_wString& facename)
{
  if (nullptr == rtf_string || 0 == rtf_string[0])
    return false;
  size_t len = wcslen(rtf_string);
  if (0 == len)
    return false;

  ON_RtfFirstChar builder(nullptr, 1.0, ON_UNSET_COLOR);

  ON_wString rtf_wstring(rtf_string);
  int rtf = rtf_wstring.Find("rtf1");
  if (-1 == rtf)
    return false;

  len = rtf_wstring.Length();
  ON_TextIterator iter(rtf_wstring.Array(), len);

  ON_RtfParser parser(iter, builder);
  bool rc = parser.Parse();
  if (rc)
  {
    bold = builder.m_current_run.IsBold();
    italic = builder.m_current_run.IsItalic();
    underline = builder.m_current_run.IsUnderlined();
    int fi = builder.m_current_run.FontIndex();
    if (-1 != fi)
      facename = builder.FaceNameFromMap(fi);
  }
  return rc;
}

const ON_Font* ON_TextContent::FirstCharFont() const
{
  ON_TextRunArray* runs = TextRuns(true);
  if (nullptr != runs)
  {
    for (int i = 0; i < runs->Count(); i++)
    {
      if (ON_TextRun::RunType::kText == (*runs)[i]->Type() ||
        ON_TextRun::RunType::kField == (*runs)[i]->Type())
      {
        return (*runs)[i]->Font();
      }
    }
  }
  return &ON_Font::Default;
}

//static
bool ON_TextContent::GetRichTextFontTable(
  const ON_wString rich_text,
  ON_ClassArray< ON_wString >& font_table
) 
{
  int table_pos = rich_text.Find(L"\\fonttbl");
  if (table_pos < 0)
    return false;

  const wchar_t* rtf = rich_text.Array();
  int open = 1;
  int table_len = 0;
  int len = rich_text.Length();
  for (int i = table_pos + 8; i < len && open > 0; i++)
  {
    if (L'{' == rich_text[i])
    {
      open++;
    }
    else if (L'}' == rich_text[i])
    {
      open--;
      table_len = i;
    }
  }

  for (int i = table_pos + 8; i < table_len; i++)
  {
    int font_pos = rich_text.Find(L"\\f", i);
    if (font_pos > i)
    {
      for (int j = font_pos + 2; j < table_len; j++)
      {
        if (rtf[j] == L' ')
        {
          for (int si = 0; si + j < table_len; si++)
          {
            if (rich_text[si + j] != L' ')
            {
              j += si;
              break;
            }
          }
          for (int ni = 1; ni + j < table_len; ni++)
          {
            if (rtf[ni + j] == L';' || rtf[ni + j] == L'}')
            {
              font_table.AppendNew() = rich_text.SubString(j, ni);
              i = ni + j;
              j = len;
              break;
            }
          }
        }
      }
    }
  }
  return true;
}



//--------------------------------------------------------------------
