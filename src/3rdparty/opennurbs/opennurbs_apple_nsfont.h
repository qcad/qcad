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

#if !defined(OPENNURBS_APPLE_NSFONT_INC_)
#define OPENNURBS_APPLE_NSFONT_INC_

#if defined(ON_RUNTIME_APPLE_CORE_TEXT_AVAILABLE)

ON_DECL
unsigned int ON_AppleFontGlyphIndex(
  CTFontRef appleFont,
  unsigned int unicode_code_point
);

ON_DECL
bool ON_AppleFontGetGlyphMetrics(
  CTFontRef appleFont,
  unsigned int font_design_units_per_M,
  unsigned int glyphIndex,
  class ON_TextBox& glyph_metrics
);

ON_DECL
bool ON_AppleFontGetGlyphOutline(
  CTFontRef appleFont,
  unsigned int font_design_units_per_M,
  unsigned int glyphIndex,
  ON_OutlineFigure::Type figure_type,
  class ON_Outline& outline
);
#endif

#endif
