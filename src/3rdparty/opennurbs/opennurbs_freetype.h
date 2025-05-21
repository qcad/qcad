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

#if !defined(OPENNURBS_FREETYPE_INC_)
#define OPENNURBS_FREETYPE_INC_

#if defined(OPENNURBS_FREETYPE_SUPPORT)
// Look in opennurbs_system_rumtime.h for the correct place to define OPENNURBS_FREETYPE_SUPPORT.
// Do NOT define OPENNURBS_FREETYPE_SUPPORT here or in your project setting ("makefile").

#if defined(ON_COMPILER_MSC) ||defined(ON_RUNTIME_WIN)
#error FreeType is not used in Windows. It does not work as well as DirectWrite based tools.
#endif

#if defined(ON_RUNTIME_APPLE)
// Freetype is used to get single stroke font outlines.
// For everything else, use the CTFont based tools.
//#error FreeType is not used in MacOS and iOS builds. It does not work as well as CTFont based code.
#endif

/*
 Returns:
   Units per em in font design units.
*/
ON_DECL
unsigned int ON_FreeTypeGetFontUnitsPerM(
  const class ON_Font* font
  );

/*
Parameters:
  font_unit_font_metrics - [in]
    metrics in font units (freetype face loaded with FT_LOAD_NO_SCALE) unless
    it is a "tricky" font.
*/
ON_DECL
void ON_FreeTypeGetFontMetrics(
  const class ON_Font* font,
  class ON_FontMetrics& font_unit_font_metrics
  );

/*
Parameters:
  glyph_box - [out]
    glyph metrics infont units (freetype face loaded with FT_LOAD_NO_SCALE) unless
    it is a "tricky" font.
Returns:
  0 if box was not set.
  >0: font glyph index (or other non-zero value) when box is set
*/
ON_DECL
unsigned int ON_FreeTypeGetGlyphMetrics(
  const class ON_FontGlyph* glyph,
  class ON_TextBox& glyph_metrics_in_font_design_units
);

/*
Parameters:
  glyph - [in]
  bSingleStrokeFont - [in]
  outline - [out]
    outline and metrics in font design units
*/
ON_DECL
bool ON_FreeTypeGetGlyphOutline(
  const class ON_FontGlyph* glyph,
  ON_OutlineFigure::Type figure_type,
  class ON_Outline& outline
);

/*
Parameters:
  glyph - [in]
  glyph_index - [in]
    If known for certain, pass in the glyph index. If not known, pass in 0.
  figure_type - [in]
    If known for certain, pass in figure_type. Otherwise, pass in ON_OutlineFigure::Type::Unset.
  outline - [out]
    outline and metrics in font design units
*/
ON_DECL
bool ON_FreeTypeGetGlyphOutline(
  const class ON_FontGlyph* glyph,
  unsigned int glyph_index,
  ON_OutlineFigure::Type figure_type,
  class ON_Outline& outline
);

/*
Description:
  A wrapper for calculating parameters and calling FreeType library 
  functions FT_Set_Char_Size() FT_Load_Glyph().
Parameters:
  ft_face - [in]
    A pointer to and FT_Face. One way to get this value is to call ON_Font::FreeTypeFace()
  font_glyph_id - [in]
    font glyph id
Returns:
  True if glyph is available and loaded.
*/
ON_DECL
bool ON_FreeTypeLoadGlyph(
  ON__UINT_PTR ft_face,
  unsigned int font_glyph_index,
  bool bLoadRenderBitmap
);
#endif


#endif
