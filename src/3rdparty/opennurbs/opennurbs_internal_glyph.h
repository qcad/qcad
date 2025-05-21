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

#if !defined(OPENNURBS_INTERNAL_GLYPH_INC_)
#define OPENNURBS_INTERNAL_GLYPH_INC_

class ON_Internal_FontGlyphPool : private ON_FixedSizePool
{
private:
  friend class ON_FontGlyph;
  friend class ON_GlyphMap;
  ON_Internal_FontGlyphPool();
  ~ON_Internal_FontGlyphPool() = default;
  ON_Internal_FontGlyphPool(const ON_Internal_FontGlyphPool&) = delete;
  ON_Internal_FontGlyphPool operator=(const ON_Internal_FontGlyphPool&) = delete;
  static ON_Internal_FontGlyphPool theGlyphItemPool;
};

class ON_ManagedFonts
{
public:
  // List is the only instance of this class.
  static ON_ManagedFonts List;

  static const ON_FontList& InstalledFonts();

  static const ON_FontList& ManagedFonts()
  {
    return List.m_managed_fonts;
  }

  const ON_Font* GetFromFontCharacteristics(
    const ON_Font& font_characteristics,
    bool bCreateIfNotFound
    );

  const ON_Font* GetFromSerialNumber(
    unsigned int managed_font_runtime_serial_number
    );

#if defined(ON_OS_WINDOWS_GDI)
  static void Internal_GetWindowsInstalledFonts(ON_SimpleArray<const ON_Font*>&);
#endif

#if defined (ON_RUNTIME_APPLE_CORE_TEXT_AVAILABLE)
  static void Internal_GetAppleInstalledCTFonts(ON_SimpleArray<const ON_Font*>& platform_font_list);
#endif

private:
  static void Internal_SetFakeWindowsLogfontNames(
    ON_SimpleArray<const ON_Font*>& device_list
  );
  static void Internal_SetFakeWindowsLogfontName(
    const ON_Font* font,
    const ON_wString fake_loc_logfont_name,
    const ON_wString fake_en_logfont_name
  );
public:

  // sorts nulls to end of lists
  static int CompareFontPointer(ON_Font const* const* lhs, ON_Font const* const* rhs);

  /*
  Returns:
    0: failure
    >0: success font glyph index
  */
  static unsigned int GetGlyphMetricsInFontDesignUnits(
    const class ON_Font* font, 
    ON__UINT32 unicode_code_point,
    class ON_TextBox& glyph_metrics_in_font_design_units
    );

  /*
  Parameters:
    font - [in]
    font_metrics_in_font_design_units - [out]
  Returns:
    True: 
      font_metrics_in_font_design_units set from a font installed on the
      current device.
    False:
      ON_FontMetrics::LastResortMetrics used or other corrections applied.
  */

  static bool GetFontMetricsInFontDesignUnits(
    const ON_Font* font,
    ON_FontMetrics& font_metrics_in_font_design_units
    );

private:
  // The purpose of this nondefault constructor is to create ON_ManagedFonts::List 
  // in opennurbs_statics.cpp in a way that Apple's CLang will actually compile.
  // The only instance of ON_ManagedFonts is ON_ManagedFonts::List.
  ON_ManagedFonts(ON__UINT_PTR zero);

  ~ON_ManagedFonts();

private:
  ON_ManagedFonts() = delete;
  ON_ManagedFonts(const ON_ManagedFonts&) = delete;
  ON_ManagedFonts& operator=(const ON_ManagedFonts&) = delete;

private:
  /*
  Parameters:
    managed_font_metrics_in_font_design_units - [in]
      Pass nullptr if not available.
      If not nullptr, then the values are assumed to be accurate
      and the units are the font design units (not normalized).
  */
  const ON_Font* Internal_AddManagedFont(
    const ON_Font* managed_font,
    const ON_FontMetrics* managed_font_metrics_in_font_design_units // can be nullptr
    );

private:
  ON__UINT_PTR m_default_font_ptr = 0;

private:
  // Managed fonts used in annotation, etc.
  // They may or may not be installed on this device
  ON_FontList m_managed_fonts;


private:
  // Fonts installed on this device
  ON_FontList m_installed_fonts;
};

class ON_CLASS ON_GlyphMap
{
public:
  ON_GlyphMap();
  ~ON_GlyphMap() = default;

public:
  const class ON_FontGlyph* FindGlyph(
    const ON__UINT32 unicode_code_point
  ) const;

  // returns pointer to the persistent glyph item
  const ON_FontGlyph* InsertGlyph(
    const ON_FontGlyph& glyph
  );

  unsigned int GlyphCount() const;

private:
  friend class ON_Font;
  friend class ON_FontGlyph;
  unsigned int m_glyph_count = 0;
  mutable ON_SleepLock m_sleep_lock;
  ON_SimpleArray< const class ON_FontGlyph* > m_glyphs;
};

#if defined(ON_OS_WINDOWS_GDI)
/*
Parameters:
  glyph - [in]
  font_metrics - [out]
    font metrics in font design units
Returns:
  >0: glyph index
  0: failed
*/
ON_DECL
void ON_WindowsDWriteGetFontMetrics(
  const ON_Font* font,
  ON_FontMetrics& font_metrics
);

/*
Parameters:
  glyph - [in]
  glyph_metrics - [out]
    Returns glyph metrics in font design units
Returns:
  >0: glyph index
  0: failed
*/
ON_DECL
unsigned int ON_WindowsDWriteGetGlyphMetrics(
  const ON_FontGlyph* glyph,
  ON_TextBox& glyph_metrics
);

/*
Parameters:
  glyph - [in]
  bSingleStrokeFont - [in]
  outline - [out]
    outline and metrics in font design units
*/
ON_DECL
bool ON_WindowsDWriteGetGlyphOutline(
  const ON_FontGlyph* glyph,
  ON_OutlineFigure::Type figure_type,
  class ON_Outline& outline
);
#endif

#if defined(ON_RUNTIME_APPLE_CORE_TEXT_AVAILABLE)
/*
Parameters:
  glyph - [in]
  font_metrics - [out]
    font metrics in font design units
Returns:
  >0: glyph index
  0: failed
*/
ON_DECL
void ON_AppleFontGetFontMetrics(
  const ON_Font* font,
  ON_FontMetrics& font_metrics
);

/*
Parameters:
  glyph - [in]
  glyph_metrics - [out]
    Returns glyph metrics in font design units
Returns:
  >0: glyph index
  0: failed
*/
ON_DECL
unsigned int ON_AppleFontGetGlyphMetrics(
  const ON_FontGlyph* glyph,
  ON_TextBox& glyph_metrics
);

/*
Parameters:
  glyph - [in]
  figure_type - [in]
    Pass ON_OutlineFigure::Type::Unset if not known.
  outline - [out]
    outline and metrics in font design units
*/
ON_DECL
bool ON_AppleFontGetGlyphOutline(
  const ON_FontGlyph* glyph,
  ON_OutlineFigure::Type figure_type,
  class ON_Outline& outline
);
#endif

#endif
