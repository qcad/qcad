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

#ifndef OPENNURBS_TEXTCONTEXT_H_INCLUDED
#define OPENNURBS_TEXTCONTEXT_H_INCLUDED


//----------------------------------------------------------
class ON_CLASS ON_TextContext
{
  ON_TextContext();
public:
  // Use ON_FontGlyph::GetGlyphList to measure strings.
  static int ConvertCodepointsToString(int cplen, const ON__UINT32* cp, ON_wString& str);
  static int ConvertStringToCodepoints(const wchar_t* str, ON__UINT32*& cp);


  static const ON_wString FormatRtfString(const wchar_t* rtfstr,
    const ON_DimStyle* dimstyle,
    bool clear_bold, bool set_bold,
    bool clear_italic, bool set_italic,
    bool clear_underline, bool set_underline,
    bool clear_facename, bool set_facename, const wchar_t* override_facename);

  static bool RtfFirstCharProperties(const wchar_t* rtfstr,
    bool& bold, bool& italic, bool& underline, ON_wString& facename);
};




#endif


                                                                            
