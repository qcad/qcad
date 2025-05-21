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

#include "opennurbs_internal_glyph.h"
#include "opennurbs_win_dwrite.h"
#include "opennurbs_apple_nsfont.h"

// Do not put this class in a public header file or SDK.
// It will be modified at unexpected times in unexpected ways. Any code outside of this file
// that uses the implementation will crash unexpectedly.
class ON_FontListImpl
{
public:
  ON_FontListImpl() = default;
  ~ON_FontListImpl() = default;

private:
  ON_FontListImpl(const ON_FontListImpl&) = delete;
  ON_FontListImpl& operator=(const ON_FontListImpl&) = delete;

public:
  // List of fonts sorted by FontCharacteristics hash
  // (Recently added fonts may be in m_unsorted[])
  mutable ON_SimpleArray< const ON_Font* > m_by_font_characteristics_hash;

  // List of fonts sorted by PostScript name 
  // (Recently added fonts may be in m_unsorted[])
  mutable ON_SimpleArray< const ON_Font* > m_by_postscript_name;

  // List of fonts sorted by Windows LOGFONT.lfFaceName name
  // (Recently added fonts may be in m_unsorted[])
  mutable ON_SimpleArray< const ON_Font* > m_by_windows_logfont_name;

  // List of fonts sorted by Family name, then FaceName
  // (Recently added fonts may be in m_unsorted[])
  mutable ON_SimpleArray< const ON_Font* > m_by_family_name;


  // List of fonts sorted by English PostScript name
  // Only fonts with m_en_postscript_name != m_loc_postscript_name are included here
  // (Recently added fonts may be in m_unsorted[])
  mutable ON_SimpleArray< const ON_Font* > m_by_english_postscript_name;

  // List of fonts sorted by English Windows LOGFONT.lfFaceName name
  // Only fonts with m_en_windows_logfont_name != m_loc_windows_logfont_name are included here
  // (Recently added fonts may be in m_unsorted[])
  mutable ON_SimpleArray< const ON_Font* > m_by_english_windows_logfont_name;

  // List of fonts sorted by English Family name, then English FaceName
  // Only fonts with m_en_family_name != m_loc_family_name are included here
  // (Recently added fonts may be in m_unsorted[])
  mutable ON_SimpleArray< const ON_Font* > m_by_english_family_name;

  mutable ON_SimpleArray< const ON_Font* > m_by_quartet_name;
};


ON_PANOSE1::FamilyKind ON_PANOSE1::FamilyKindFromUnsigned(
  unsigned int unsigned_panose_family_kind
)
{
  switch (unsigned_panose_family_kind)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_PANOSE1::FamilyKind::Any);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_PANOSE1::FamilyKind::NoFit);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_PANOSE1::FamilyKind::LatinText);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_PANOSE1::FamilyKind::LatinScript);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_PANOSE1::FamilyKind::LatinDecorative);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_PANOSE1::FamilyKind::LatinSymbol);
  default:
    break;
  }
  ON_ERROR("unsigned_pannos1_classification is not valid");
  return ON_PANOSE1::FamilyKind::Any;
}
const wchar_t*  ON_PANOSE1::FamilyKindToWideString(
  ON_PANOSE1::FamilyKind family_kind
)
{
  const wchar_t* s;
  switch (family_kind)
  {
  case ON_PANOSE1::FamilyKind::Any: 
    s = L"Any";
    break;
  case ON_PANOSE1::FamilyKind::NoFit:
    s = L"No fit";
    break;
  case ON_PANOSE1::FamilyKind::LatinText:
    s = L"Latin Text"; 
    break;
  case ON_PANOSE1::FamilyKind::LatinScript:
    s = L"Latin Script"; 
    break;
  case ON_PANOSE1::FamilyKind::LatinDecorative: 
    s = L"Latin Decorative";
    break;
  case ON_PANOSE1::FamilyKind::LatinSymbol:
    s = L"Latin Symbol";
    break;
  default:
    s = L"";
    break;
  }
  return s;
}


bool ON_PANOSE1::IsZero() const
{
  const ON__UINT8* p = TenBytes();
  for (int i = 0; i < 10; i++)
  {
    if (0 != p[i])
      return false;
  }
  return true;
}

bool ON_PANOSE1::IsZeroOrOne() const
{
  const ON__UINT8* p = TenBytes();
  for (int i = 0; i < 10; i++)
  {
    if (p[i] > 1)
      return false;
  }
  return true;
}

bool ON_PANOSE1::IsSet() const
{
  return IsZeroOrOne() ? false : true;
}

ON_PANOSE1::FamilyKind ON_PANOSE1::PANOSE1FamilyKind() const
{
  return m_family_kind;
}

const ON__UINT8* ON_PANOSE1::TenBytes() const
{
  return (const ON__UINT8*)(&m_family_kind);
}

void ON_PANOSE1::SetTenBytes(const ON__UINT8* panose1_ten_bytes)
{
  SetNineBytes(ON_PANOSE1::FamilyKindFromUnsigned(panose1_ten_bytes[0]), panose1_ten_bytes + 1);
}

void ON_PANOSE1::SetNineBytes(
  ON_PANOSE1::FamilyKind family_kind,
  const ON__UINT8* panose1_properties_bytes
)
{
  const ON__UINT8 b0 = static_cast<ON__UINT8>(family_kind);
  if ( b0 > 5)
  {
    *this = ON_PANOSE1::Zero;
  }
  else
  {
    m_family_kind = family_kind;
    m_prop1 = panose1_properties_bytes[0];
    m_prop2 = panose1_properties_bytes[1];
    m_prop3 = panose1_properties_bytes[2];
    m_prop4 = panose1_properties_bytes[3];
    m_prop5 = panose1_properties_bytes[4];
    m_prop6 = panose1_properties_bytes[5];
    m_prop7 = panose1_properties_bytes[6];
    m_prop8 = panose1_properties_bytes[7];
    m_prop9 = panose1_properties_bytes[8];
  }
}

void ON_PANOSE1::Dump(
  class ON_TextLog& text_log
) const
{
  if (IsZero())
  {
    text_log.Print(L"PANOSE1::Zero\n");
  }
  else
  {
    ON_wString family = FamilyKindToWideString(m_family_kind);
    if (family.IsEmpty())
      family = ON_wString::FormatToString(L"%u", (unsigned int)m_family_kind);
    text_log.Print(L"PANOSE1: %ls (%u, %u, %u, %u, %u, %u, %u, %u, %u)\n",
      static_cast<const wchar_t*>(family),
      (unsigned int)m_prop1,
      (unsigned int)m_prop2,
      (unsigned int)m_prop3,
      (unsigned int)m_prop4,
      (unsigned int)m_prop5,
      (unsigned int)m_prop6,
      (unsigned int)m_prop7,
      (unsigned int)m_prop8,
      (unsigned int)m_prop9
    );
  }
}

bool ON_PANOSE1::Write(
  class ON_BinaryArchive& archive
) const
{  
  if (false == archive.BeginWrite3dmAnonymousChunk(1))
    return false;

  bool rc = false;
  for(;;)
  {
    if (!archive.WriteByte(1, &m_family_kind))
      break;
    if (!archive.WriteByte(1, &m_prop1))
      break;
    if (!archive.WriteByte(1, &m_prop2))
      break;
    if (!archive.WriteByte(1, &m_prop3))
      break;
    if (!archive.WriteByte(1, &m_prop4))
      break;
    if (!archive.WriteByte(1, &m_prop5))
      break;
    if (!archive.WriteByte(1, &m_prop6))
      break;
    if (!archive.WriteByte(1, &m_prop7))
      break;
    if (!archive.WriteByte(1, &m_prop8))
      break;
    if (!archive.WriteByte(1, &m_prop9))
      break;
    rc = true;
    break;
  }
  if (!archive.EndWrite3dmChunk())
    rc = false;
  return rc;
}

bool ON_PANOSE1::Read(
  class ON_BinaryArchive& archive
)
{
  int version = 0;
  if (false == archive.BeginRead3dmAnonymousChunk(&version))
    return false;

  bool rc = false;
  for (;;)
  {
    if (version < 1)
      break;
    if (!archive.ReadByte(1, &m_family_kind))
      break;
    if (!archive.ReadByte(1, &m_prop1))
      break;
    if (!archive.ReadByte(1, &m_prop2))
      break;
    if (!archive.ReadByte(1, &m_prop3))
      break;
    if (!archive.ReadByte(1, &m_prop4))
      break;
    if (!archive.ReadByte(1, &m_prop5))
      break;
    if (!archive.ReadByte(1, &m_prop6))
      break;
    if (!archive.ReadByte(1, &m_prop7))
      break;
    if (!archive.ReadByte(1, &m_prop8))
      break;
    if (!archive.ReadByte(1, &m_prop9))
      break;
    if (version <= 1)
    {
      rc = true;
      break;
    }

    rc = true;
    break;
  }
  if (!archive.EndRead3dmChunk())
    rc = false;
  return rc;
}



int ON_FontMetrics::Ascent() const
{
  return m_ascent;
}

int ON_FontMetrics::Descent() const
{
  return m_descent;
}

int ON_FontMetrics::LineSpace() const
{
  return m_line_space;
}

int ON_FontMetrics::UPM() const
{
  return m_UPM;
}

int ON_FontMetrics::AscentOfI() const
{
  return AscentOfCapital();
}

int ON_FontMetrics::AscentOfCapital() const
{
  return (int)m_ascent_of_capital;
}

int ON_FontMetrics::AscentOfx() const
{
  return (int)m_ascent_of_x;
}

double ON_FontMetrics::GlyphScale(double text_height) const
{
  // Please consult Dale Lear and the ON_FontGlyph 
  // bounding box, outline, and advance calculation code
  // before making any modifications to this function.
  const double y = (double)AscentOfCapital();
  return (text_height > 0.0
    && text_height < ON_UNSET_POSITIVE_FLOAT 
    && y > 0.0
    && y < ON_UNSET_POSITIVE_FLOAT
    )
    ? (text_height / y) 
    : 1.0;
}

int ON_FontMetrics::StrikeoutThickness() const
{
  return m_strikeout_thickness;
}

int ON_FontMetrics::StrikeoutPosition() const
{
  return m_strikeout_position;
}

int ON_FontMetrics::UnderscoreThickness() const
{
  return m_underscore_thickness;
}

int ON_FontMetrics::UnderscorePosition() const
{
  return m_underscore_position;
}

bool ON_FontMetrics::AscentDescentAndUPMAreValid() const
{
  const int max_valid = 0xFFFF;
  const int min_valid = -max_valid;
  // basic validation
  if (m_UPM <= 0 || m_UPM >= max_valid)
    return false;
  if (0 == m_ascent && 0 == m_descent)
    return false;
  if (m_ascent <= min_valid || m_ascent >= max_valid)
    return false;
  if (m_descent <= min_valid || m_descent >= max_valid)
    return false;
  if (m_ascent <= m_descent)
    return false;

  return true;
}


bool ON_FontMetrics::HeightsAreValid() const
{
  // basic validation
  if (false == AscentDescentAndUPMAreValid() )
    return false;

  // sanity check
  if (m_line_space < m_ascent - m_descent)
    return false;
  if (((int)m_ascent_of_capital) > m_ascent)
    return false;
  if (((int)m_ascent_of_x) > m_ascent)
    return false;

  return true;
}

bool ON_FontMetrics::IsSetAndValid() const
{
  return (m_ascent_of_capital > 0 && HeightsAreValid());
}

void ON_FontMetrics::SetHeights(
  int ascent,
  int descent,
  int UPM,
  int line_space
)
{
  if (ON_UNSET_INT_INDEX < descent && descent < ascent && ascent < -ON_UNSET_INT_INDEX)
  {
    m_ascent = ascent;
    m_descent = descent;
  }
  else
  {
    m_ascent = 0;
    m_descent = 0;
  }
  m_UPM = (UPM > 0 && UPM < -ON_UNSET_INT_INDEX) ? UPM : 0;
  m_line_space = (line_space > 0 && line_space < -ON_UNSET_INT_INDEX)? line_space : 0;
  if (
    m_line_space > 0
    && m_ascent > 0
    && m_descent <= m_ascent
    && m_line_space < m_ascent - m_descent
    && m_line_space >= m_ascent - m_descent - 1
    )
  {
    // Probably sloppy rounding - just make it work
    m_line_space = m_ascent - m_descent;
  }
}

void ON_FontMetrics::SetAscentOfI(
  int ascent_of_capital
)
{
  SetAscentOfCapital(ascent_of_capital);
}

void ON_FontMetrics::SetAscentOfCapital(
  int ascent_of_capital
)
{
  m_ascent_of_capital = (ascent_of_capital > 0 && ascent_of_capital <= 0xFFFF) ?  ((unsigned short)ascent_of_capital) : 0;
}

void ON_FontMetrics::SetAscentOfx(
  int ascent_of_x
)
{
  m_ascent_of_x = (ascent_of_x > 0 && ascent_of_x <= 0xFFFF) ?  ((unsigned short)ascent_of_x) : 0;
}

void ON_FontMetrics::SetStrikeout(
  int strikeout_position,
  int strikeout_thickness
)
{
  m_strikeout_position = strikeout_position;
  m_strikeout_thickness = strikeout_thickness;
}
  
void ON_FontMetrics::SetUnderscore(
  int underscore_position,
  int underscore_thickness
)
{
  m_underscore_position = underscore_position;
  m_underscore_thickness = underscore_thickness;
}

static int Internal_FontMetricCeil(
  double x
)
{
  const double m = (double)0xFFFFFF;
  if (x >= -m && x <= m)
  {
    double i = ceil(x);
    return (int)(((i - x) > 0.9375) ? (i - 1.0) : i);
  }
  return 0;
}

static int Internal_FontMetricFloor(
  double x
)
{
  const double m = (double)0xFFFFFF;
  if (x >= -m && x <= m)
  {
    double i = floor(x);
    return (int)(((x - i) > 0.9375) ? (i + 1.0) : i);
  }
  return 0;
}


static int Internal_FontMetricNearest(
  double x
)
{
  const double m = (double)0xFFFFFF;
  if (x >= -m && x <= m)
  {
    double i = floor(x);
    return (int)(((x - i) > 0.5) ? (i + 1.0) : i);
  }
  return 0;
}

void ON_FontMetrics::SetHeights(
  double ascent,
  double descent,
  double UPM,
  double line_space
)
{
  int iascent = Internal_FontMetricCeil(ascent);
  int idescent = Internal_FontMetricFloor(descent);
  int iUPM = Internal_FontMetricCeil(UPM);
  int iline_space = Internal_FontMetricCeil(line_space);
  if (
    iascent > 0
    && idescent <= iascent
    && iline_space < iascent - idescent
    && line_space >= (ascent - descent - 1.0)
    )
  {
    iline_space = iascent - idescent;
  }
  SetHeights(iascent, idescent, iUPM, iline_space);
}

void ON_FontMetrics::SetAscentOfCapital(
  double ascent_of_capital
)
{
  int iascent_of_capital = Internal_FontMetricCeil(ascent_of_capital);
  //// Dale Lear Feb 2021 - Huh? The condition is never true unless m_ascent - 1 overflows to a positive number.
  ////if (m_ascent < 0 && iascent_of_capital > m_ascent && iascent_of_capital <= m_ascent - 1)
  ////  iascent_of_capital = m_ascent;
  SetAscentOfCapital(iascent_of_capital);
}

void ON_FontMetrics::SetAscentOfx(
  double ascent_of_x
)
{
  int iascent_of_x = Internal_FontMetricCeil(ascent_of_x);
  //// Dale Lear Feb 2021 - Huh? The condition is never true unless m_ascent - 1 overflows to a positive number.
  ////if (m_ascent < 0 && iascent_of_x > m_ascent && iascent_of_x <= m_ascent - 1)
  ////  iascent_of_x = m_ascent;
  SetAscentOfx(iascent_of_x);
}
  
void ON_FontMetrics::SetStrikeout(
  double strikeout_position,
  double strikeout_thickness
)
{
  int istrikeout_thickness = 
    (strikeout_thickness > 0.0)
    ? Internal_FontMetricCeil(strikeout_thickness)
    : 0;
  if (0 == istrikeout_thickness && strikeout_thickness > 0.0)
    istrikeout_thickness = 1;
  SetStrikeout(Internal_FontMetricNearest(strikeout_position), istrikeout_thickness);
}
  
void ON_FontMetrics::SetUnderscore(
  double underscore_position,
  double underscore_thickness
)
{
  int iunderscore_thickness = 
    (underscore_thickness > 0.0)
    ? Internal_FontMetricCeil(underscore_thickness)
    : 0;
  if (0 == iunderscore_thickness && underscore_thickness > 0.0)
    iunderscore_thickness = 1;
  SetUnderscore(Internal_FontMetricFloor(underscore_position), iunderscore_thickness);
}

static int Internal_ScaleInt(double scale, int i)
{
  return (int)((i >= 0) ? ceil(scale*i) : floor(scale*i));
}

const ON_FontMetrics ON_FontMetrics::Scale(
  const ON_FontMetrics& font_metrics,
  double scale
)
{
  ON_FontMetrics scaled_font_metrics = font_metrics;

  if (scale > 0.0 && 1.0 != scale)
  {
    scaled_font_metrics.m_UPM = Internal_ScaleInt(scale, scaled_font_metrics.m_UPM);
    scaled_font_metrics.m_ascent = Internal_ScaleInt(scale, scaled_font_metrics.m_ascent);
    scaled_font_metrics.m_descent = Internal_ScaleInt(scale, scaled_font_metrics.m_descent);

    scaled_font_metrics.SetAscentOfCapital(Internal_ScaleInt(scale, scaled_font_metrics.m_ascent_of_capital));
    scaled_font_metrics.SetAscentOfx(Internal_ScaleInt(scale, scaled_font_metrics.m_ascent_of_x));

    if (font_metrics.m_line_space == Internal_ScaleInt(ON_FontMetrics::DefaultLineFeedRatio,font_metrics.AscentOfCapital()))
      scaled_font_metrics.m_line_space = Internal_ScaleInt(ON_FontMetrics::DefaultLineFeedRatio,scaled_font_metrics.AscentOfCapital());
    else
      scaled_font_metrics.m_line_space = Internal_ScaleInt(scale, scaled_font_metrics.m_line_space);

    scaled_font_metrics.m_strikeout_thickness = Internal_ScaleInt(scale, scaled_font_metrics.m_strikeout_thickness);
    scaled_font_metrics.m_strikeout_position = Internal_ScaleInt(scale, scaled_font_metrics.m_strikeout_position);

    scaled_font_metrics.m_underscore_thickness = Internal_ScaleInt(scale, scaled_font_metrics.m_underscore_thickness);
    scaled_font_metrics.m_underscore_position = Internal_ScaleInt(scale, scaled_font_metrics.m_underscore_position);
  }

  return scaled_font_metrics;
}

const ON_FontMetrics ON_FontMetrics::Normalize(
  const ON_FontMetrics& font_metrics
)
{
  if (font_metrics.m_UPM == ON_Font::AnnotationFontCellHeight)
    return font_metrics;

  if (font_metrics.m_UPM <= 0)
    return ON_FontMetrics::Unset;

  const double scale
    = ((double)ON_Font::AnnotationFontCellHeight / ((double)font_metrics.m_UPM));
  return ON_FontMetrics::Scale(font_metrics, scale);
}

ON_ManagedFonts::ON_ManagedFonts(ON__UINT_PTR zero)
  : m_default_font_ptr(zero)
  , m_managed_fonts(true)
  , m_installed_fonts(false)
{}

ON_ManagedFonts::~ON_ManagedFonts()
{

  ON_SimpleArray<const ON_Font*> managed_fonts(m_installed_fonts.m_by_index);
  managed_fonts.Append(m_managed_fonts.m_by_index.Count(),m_managed_fonts.m_by_index.Array());

  m_installed_fonts.Internal_EmptyLists();
  m_managed_fonts.Internal_EmptyLists();

  // last created first deleted - it shouldn't really matter.
  for(int i = managed_fonts.Count()-1; i >= 0; i--)
  {
    ON_Font* managed_font = const_cast<ON_Font*>(managed_fonts[i]);
    if (nullptr == managed_font)
      continue;

    if (m_default_font_ptr == (ON__UINT_PTR)managed_font)
    {
      // ON_Font::Default is constructed after ON_ManagedFonts::List 
      // and destructed before the destruction of ON_ManagedFonts::List.
      // This continue prevents calling delete on 
      continue;
    }
    if (1 == managed_font->m_runtime_serial_number)
    {
      // ON_Font::Default.m_runtime_serial_number = 1 and it is the only instance of a font
      // with m_runtime_serial_number = 1.  
      // However, the managed_font pointer points to ON_Font::Default, which was destroyed a few milliseconds ago.
      // See opennurbs_statics.cpp and observe that construction order is
      // ..., ON_ManagedFonts::List, ON_Font::Unset, ON_Font::Default, ...
      // and destruction order is
      // ..., ON_Font::Default, ON_Font::Unset, ON_ManagedFonts::List, ...
      ON_ERROR("The m_default_font_ptr test above should have detected ON_Font::Default.");
      continue;
    }

    // The reset needs to happen for all fonts, including ON_Font::Default
    // Otherwise we get unpredictable crashes when closing because the
    // order in which ON_Font::Default, ON_GlyphMap::GlyphPool and ON_ManagedFonts::List
    // is not predictable.
    managed_font->m_font_glyph_cache.reset();


    delete managed_font;
  }
}

class ON_FontGlyphCache
{
public:
  static ON_FontGlyphCache* New();

  void SetFontMetrics(
    const ON_FontMetrics& font_unit_metrics
  );

#if defined(ON_OS_WINDOWS_GDI)
  // primary installed font used to get glyphs
  // When the current (Windows) device has a font that
  // matches the ON_Font, this is matching installed font.
  struct IDWriteFont* m_dwrite_font = 0;
#endif

  // See ON_Font.FontMetrics() documentation for a discussion
  // of normalized and unnormalized metrics and scales.
  // Both scale values are stored to reduce rounding errors.
  double m_font_unit_to_normalized_scale = 1.0;
  double m_normalized_to_font_unit_scale = 1.0;

  // Font metrics in the units from the system font definition.
  // UPM = font design cell height (often 1000 for PostScript, 2014 for TrueType, ...)
  ON_FontMetrics m_font_unit_metrics;

  // Font metrics normalized so UPM = ON_Font::Constants::AnnotationFontCellHeight
  ON_FontMetrics m_normalized_metrics;

  // Array of glyphs with sizes and display info
  std::shared_ptr<ON_GlyphMap> m_glyphmap;
};

ON_FontGlyphCache* ON_FontGlyphCache::New()
{
  ON_FontGlyphCache* font_cache = new ON_FontGlyphCache();
  font_cache->m_glyphmap = std::make_shared<ON_GlyphMap>();
  return font_cache;
}

void ON_FontGlyphCache::SetFontMetrics(
  const ON_FontMetrics& font_unit_metrics
)
{
  m_font_unit_metrics = font_unit_metrics;

  m_normalized_to_font_unit_scale 
    = font_unit_metrics.UPM() > 0
    ? (((double)font_unit_metrics.UPM()) / ((double)ON_Font::Constants::AnnotationFontCellHeight))
    : 0.0;
  m_font_unit_to_normalized_scale
    = m_normalized_to_font_unit_scale > 0.0
    ? (((double)ON_Font::Constants::AnnotationFontCellHeight) / ((double)font_unit_metrics.UPM()))
    : 0.0;

  m_normalized_metrics
    = (m_font_unit_to_normalized_scale > 0.0 && 1.0 != m_font_unit_to_normalized_scale)
    ? ON_FontMetrics::Scale(m_font_unit_metrics, m_font_unit_to_normalized_scale)
    : m_font_unit_metrics;
}

static const ON_Font* Internal_BinarySearchForManagedFontSerialNumber( unsigned int key, const ON_Font*const* base, size_t nel )
{
  if (nel > 0 && nullptr != base )
  {
    size_t i;
    const ON_Font* font;
    unsigned int d;

    // The end tests are not necessary, but they
    // seem to provide overall speed improvement
    // for the types of searches that call this
    // function.
    font = base[0];
    d = font->RuntimeSerialNumber();
    if ( key < d )
      return nullptr;
    if ( key == d )
      return font;

    font = base[nel-1];
    d = font->RuntimeSerialNumber();
    if ( key > d )
      return nullptr;
    if ( key == d )
      return font;

    while ( nel > 0 )
    {
      i = nel/2;
      font = base[i];
      d = font->RuntimeSerialNumber();
      if ( key < d )
      {
        nel = i;
      }
      else if ( key > d )
      {
        i++;
        base += i;
        nel -= i;
      }
      else
      {
        return font;
      }
    }
  }
  return nullptr;
}

const ON_Font* ON_ManagedFonts::GetFromSerialNumber(
  unsigned int managed_font_serial_number
  )
{
  if (0 == m_managed_fonts.Count())
  {
    // Put ON_Font::Default as the first entry in this list.
    Internal_AddManagedFont(&ON_Font::Default, nullptr);
  }
  if (managed_font_serial_number < 1)
  {
    ON_ERROR("managed_font_serial_number parameter must be >= 1");
    return nullptr;
  }

  if ( managed_font_serial_number == ON_Font::Default.RuntimeSerialNumber() )
    return &ON_Font::Default;

  const ON_Font* const * managed_fonts = m_managed_fonts.m_by_index.Array();
  const unsigned int font_count = m_managed_fonts.m_by_index.UnsignedCount();

  if (managed_font_serial_number <= font_count
    && managed_font_serial_number == managed_fonts[managed_font_serial_number - 1]->RuntimeSerialNumber())
  {
    // This test should always find the managed font as long as the current numbering scheme is used.
    return managed_fonts[managed_font_serial_number - 1];
  }
  
  return
    (font_count > 0)
    ? Internal_BinarySearchForManagedFontSerialNumber(managed_font_serial_number, managed_fonts, font_count)
    : nullptr;
}

const ON_Font* ON_ManagedFonts::GetFromFontCharacteristics(
  const ON_Font& font_characteristics,
  bool bCreateIfNotFound
)
{
  if ( 0 == m_managed_fonts.Count() )
  {
    // Put ON_Font::Default as the first entry in this list.
    Internal_AddManagedFont( &ON_Font::Default, nullptr );
  }

  if (font_characteristics.IsManagedFont())
    return &font_characteristics;


  const bool bIsUnderlined = font_characteristics.IsUnderlined();
  const bool bIsStrikethrough = font_characteristics.IsStrikethrough();
  const double point_size
    = ON_Font::IsValidPointSize(font_characteristics.PointSize())
    ? font_characteristics.PointSize()
    : 0.0;

  const ON_Font* set_font_characteristics = &font_characteristics;

  std::unique_ptr< ON_Font > fup;
  if (false == font_characteristics.IsInstalledFont())
  {
    bool bHaveName
      = font_characteristics.PostScriptName().IsNotEmpty()
      || font_characteristics.WindowsLogfontName().IsNotEmpty()
      || font_characteristics.FamilyName().IsNotEmpty();
    if ( false == bHaveName || font_characteristics.HasUnsetProperties(false, false) )
    {
      fup = std::make_unique< ON_Font >(font_characteristics);
      ON_Font* temporary_font = fup.get();
      if (nullptr != temporary_font)
      {
        if (false == bHaveName)
        {
          *temporary_font = ON_Font::Default;
        }
        else
        {
          temporary_font->SetUnsetProperties(ON_Font::Default, true);
        }
        temporary_font->SetUnderlined(bIsUnderlined);
        temporary_font->SetStrikethrough(bIsStrikethrough);
        temporary_font->SetPointSize(point_size);
        set_font_characteristics = temporary_font;
      }
    }

    if (false == set_font_characteristics->IsValid())
      return &ON_Font::Default;
  }

  ON_Font::NameLocale name_locale = ON_Font::NameLocale::LocalizedFirst;

  for (;;)
  {
    // quick test for default font that occurs often enough to warrant the special checking
    if (bIsUnderlined)
      break;
    if (bIsStrikethrough)
      break;
    if (0.0 != point_size && point_size != ON_Font::Default.m_point_size)
      break;

    if (false == ON_Font::EqualWeightStretchStyle(&ON_Font::Default, set_font_characteristics, false))
      break; // there are multiple weight-stretch-style settings for the same family name and same LOGFONT.lfFaceName.

    ON_wString name = set_font_characteristics->PostScriptName(name_locale);
    if (name.IsNotEmpty())
    {
      if (ON_wString::EqualOrdinal(name, ON_Font::Default.PostScriptName(name_locale), true))
      {
        return &ON_Font::Default;
      }
      break; // Different PostScript names
    }

    name = set_font_characteristics->WindowsLogfontName(name_locale);
    if (name.IsNotEmpty())
    {
      if (ON_wString::EqualOrdinal(name, ON_Font::Default.WindowsLogfontName(name_locale), true))
      {
        return &ON_Font::Default;
      }
      break; // Different LOGFONT settings
    }

    name = set_font_characteristics->FamilyName(name_locale);
    if (name.IsNotEmpty())
    {
      if (ON_wString::EqualOrdinal(name, ON_Font::Default.FamilyName(name_locale), true))
      {
        name = set_font_characteristics->FaceName(name_locale);
        if (
          name.IsEmpty()
          || ON_wString::EqualOrdinal(name, ON_Font::Default.FaceName(name_locale), true)
          )
        {
          return &ON_Font::Default;
        }
      }
      break; // Different faces
    }

    break;
  }

  const ON_Font* managed_font = m_managed_fonts.FromFontProperties(
    set_font_characteristics,
    true,
    true,
    bIsUnderlined,
    bIsStrikethrough,
    point_size
    );

  if (nullptr == managed_font && (bIsUnderlined || bIsStrikethrough))
  {
    ON_Font undecorated(*set_font_characteristics);
    undecorated.SetUnderlined(false);
    undecorated.SetStrikethrough(false);
    managed_font = m_managed_fonts.FromFontProperties(
      &undecorated,
      true,
      true,
      false, // ignore bIsUnderlined
      false, // ignore bIsStrikethrough
      point_size
    );
  }

  unsigned int managed_font_wss_dev = ON_Font::WeightStretchStyleDeviation(
    set_font_characteristics, 
    managed_font
  );

  // Lowell - Added additional check for matching underline and strikethrough settings RH-60947
  unsigned int managed_font_us_dev = ON_Font::UnderlinedStrikethroughDeviation(
    set_font_characteristics, 
    managed_font
  );

  if (
    nullptr != managed_font 
    && 0 == managed_font_wss_dev
    && 0 == managed_font_us_dev
    && point_size == managed_font->PointSize()
    )
  {
    return managed_font;
  }


  for(;;)
  {
    if (set_font_characteristics->IsInstalledFont())
      break;

    const ON_Font* installed_font
      = m_installed_fonts.FromFontProperties(
        set_font_characteristics,
        true,
        true
      );
    if (nullptr == installed_font)
      break;

    set_font_characteristics = installed_font;
    if (bIsUnderlined || bIsStrikethrough || point_size > 0.0)
    {
      // Need a copy to set underlined/strikethrough/point_size
      fup = std::make_unique< ON_Font >(*installed_font);
      ON_Font* temporary_font = fup.get();
      if (nullptr != temporary_font)
      {
        temporary_font->SetUnderlined(bIsUnderlined);
        temporary_font->SetStrikethrough(bIsStrikethrough);
        temporary_font->SetPointSize(point_size);
        set_font_characteristics = temporary_font;
      }
    }

    // Look again now that we have settings known to be correct.
    managed_font = m_managed_fonts.FromFontProperties(
      set_font_characteristics,
      true,
      true,
      bIsUnderlined,
      bIsStrikethrough,
      point_size
      );

    managed_font_wss_dev = ON_Font::WeightStretchStyleDeviation(
      set_font_characteristics->FontWeight(), 
      set_font_characteristics->FontStretch(), 
      set_font_characteristics->FontStyle(), 
      managed_font
    );

    // RH - 60947
    managed_font_us_dev = ON_Font::UnderlinedStrikethroughDeviation(
      set_font_characteristics->IsUnderlined(),
      set_font_characteristics->IsStrikethrough(),
      managed_font
    );


    if (nullptr != managed_font 
      && 0 == managed_font_wss_dev
      && 0 == managed_font_us_dev
      )
      return managed_font;

    break;
  }

  if (false == bCreateIfNotFound)
    return nullptr;

  // The managed font constructor does not copy user data, m_font_index, m_font_id, m_gonna_change_font_cache
  ON_MemoryAllocationTracking disable_tracking(false);
  const ON_FontMetrics* font_metrics = nullptr;
  const ON_FontGlyphCache* font_glyph_cache = set_font_characteristics->m_font_glyph_cache.get();
  if (nullptr != font_glyph_cache)
    font_metrics = &font_glyph_cache->m_font_unit_metrics;
  managed_font = Internal_AddManagedFont(
    new ON_Font( ON_Font::FontType::ManagedFont, *set_font_characteristics),
    font_metrics
  );

  return managed_font;
}

static void Internal_AddManagedFontSingleRefCountString(
  const ON_wString& s
)
{
  const ON_wString dirty(s);
  ON_wString& clean = const_cast<ON_wString&>(s);
  clean.Destroy();
  clean = static_cast<const wchar_t*>(dirty);
}

const ON_Font* ON_ManagedFonts::Internal_AddManagedFont(
  const ON_Font* managed_font,
  const ON_FontMetrics* managed_font_metrics_in_font_design_units
  )
{
  // All memory allocated for managed fonts is permanent app workspace memory.
  ON_MemoryAllocationTracking disable_tracking(false);

  if (0 == m_default_font_ptr && 1 == managed_font->m_runtime_serial_number)
  {
    // ON_Font::Default is constructed after ON_ManagedFonts::List and
    // destroyed before ON_ManagedFonts::List. Therefore ~ON_ManagedFonts()
    // has a pointer to ON_Font::Default that must be ignored during
    // destruction.
    m_default_font_ptr = (ON__UINT_PTR)managed_font;
  }

  const ON_Font* installed_font = InstalledFonts().FromFontProperties(managed_font, true, true);
  if (nullptr != installed_font)
  {
    // This managed font matches an installed font.
    ON_Font::Internal_SetManagedFontInstalledFont(managed_font, installed_font, false);
  }
  else
  {
    // Feb 22, 2021 RH-62974
    // This managed font is not installed on this device.
    // After prototyping several approaches permitting various types
    // of user configured font substitution, Lowell and Dale Lear
    // concluded that using the default font was the best option.
    // If this is a problem for lots of users, then we need a way
    // for users to configure the choice of default font.
    // Current settings:
    // Windows: Arial
    // Apple: Helvetic Neue

    // managed_font is a missing font.
    // We have to substitute the correct quartet member (regular/bold/italic/bold-italic).
    // Since managed_font references a font that is not installed on this device,
    // IsItalicInQuartet() and IsBoldInQuartet() will probably fall through to
    // the fallback best guess sections of those functions.
    const bool bBoldInQuartet = managed_font->IsBoldInQuartet();
    const bool bItalicInQuartet = managed_font->IsItalicInQuartet();
    if (ON_FontFaceQuartet::Member::Unset == managed_font->m_quartet_member)
      managed_font->m_quartet_member = ON_FontFaceQuartet::MemberFromBoldAndItalic(bBoldInQuartet, bItalicInQuartet);

    const ON_FontFaceQuartet default_quartet = ON_Font::Default.InstalledFontQuartet(); // only look at installed quartet!
    installed_font = default_quartet.ClosestFace(bBoldInQuartet, bItalicInQuartet);
    if (nullptr == installed_font)
      installed_font = &ON_Font::Default;
    ON_Font::Internal_SetManagedFontInstalledFont(managed_font, installed_font, true);
  }

  ON_FontGlyphCache* font_cache = managed_font->m_font_glyph_cache.get();
  if (nullptr == font_cache)
  {
    /////////////////////
    //
    // Put the cached glyph information here so we only have one set for each font
    //
    font_cache = ON_FontGlyphCache::New();
    managed_font->m_font_glyph_cache = std::shared_ptr<ON_FontGlyphCache>(font_cache);
  }

  if (nullptr != font_cache)
  {
    if (false == font_cache->m_font_unit_metrics.HeightsAreValid())
    {
      ON_FontMetrics font_metrics_in_font_design_units;

      if (
        nullptr != managed_font_metrics_in_font_design_units
        && managed_font_metrics_in_font_design_units->HeightsAreValid()
        )
      {
        font_metrics_in_font_design_units = *managed_font_metrics_in_font_design_units;
      }
      else
      {
        ON_ManagedFonts::GetFontMetricsInFontDesignUnits(
          managed_font,
          font_metrics_in_font_design_units
        );
      }

      font_cache->SetFontMetrics(font_metrics_in_font_design_units);
    }
  }
  
  // Insulate strings in managed fonts from outside damage.
  Internal_AddManagedFontSingleRefCountString(managed_font->m_locale_name);
  Internal_AddManagedFontSingleRefCountString(managed_font->m_loc_postscript_name);
  Internal_AddManagedFontSingleRefCountString(managed_font->m_en_postscript_name);
  Internal_AddManagedFontSingleRefCountString(managed_font->m_loc_family_name);
  Internal_AddManagedFontSingleRefCountString(managed_font->m_en_family_name);
  Internal_AddManagedFontSingleRefCountString(managed_font->m_loc_face_name);
  Internal_AddManagedFontSingleRefCountString(managed_font->m_en_face_name);
  Internal_AddManagedFontSingleRefCountString(managed_font->m_loc_windows_logfont_name);
  Internal_AddManagedFontSingleRefCountString(managed_font->m_loc_windows_logfont_name);

  m_managed_fonts.AddFont(managed_font,false);

  return managed_font;
}

#define ON_MANAGED_FONT_CHECK(falure_return_value) {if (0 != m_managed_font) (ON_ERROR("Cannot modify managed fonts."); return (falure_return_value);}}

//
// END list of managed ON_Fonts
//
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//
// BEGIN list of platform ON_Fonts
//


#if defined(ON_RUNTIME_WIN)

////static bool ON_Internal_WindowsGetGlyphMetricsEx(
////  LOGFONT& logfont,
////  int logfont_height,
////  //MAT2 mat2,
////  ON__UINT32 unicode_code_point,
////  class ON_TextBox& font_unit_glyph_box
////)
////{
////  font_unit_glyph_box = ON_TextBox::Unset;
////
////  if (logfont_height <= 0)
////    logfont_height = ON_Font::Constants::AnnotationFontCellHeight;
////
////  if (false == ON_IsValidUnicodeCodePoint(unicode_code_point) )
////    return false;
////
////  if (0 == logfont.lfFaceName[0] )
////    return false;
////
////  wchar_t w[8] = { 0 };
////  const size_t w_capacity = (sizeof(w) / sizeof(w[0])) - 1;
////  const int w_count = ON_EncodeWideChar(unicode_code_point, w_capacity, w);
////  if ( 0 == w[0] || w_count <= 0 || w_count > (int)w_capacity )
////    return false;
////  
////  HDC font_hdc = nullptr;
////  HFONT hfont = nullptr;
////  HGDIOBJ hfont0 = nullptr;
////
////  for (;;)
////  {
////    font_hdc = ON_Font::CreateWindowsLogfontDeviceContext();
////    if (nullptr == font_hdc)
////      break;
////
////    LOGFONT lf = logfont;
////    lf.lfHeight = logfont_height;
////    hfont = ::CreateFontIndirect(&lf);
////    if (nullptr == hfont)
////      break;
////    hfont0 = ::SelectObject(font_hdc, hfont);
////
////    ON__UINT16 glyphindex[sizeof(w)/sizeof(w[0])] = { 0 };
////    const DWORD gicount = ::GetGlyphIndices(font_hdc, w, w_count, glyphindex, GGI_MARK_NONEXISTING_GLYPHS);
////    if (GDI_ERROR == gicount)
////      break;
////    if (0xffff == glyphindex[0] || 0xffff == glyphindex[1])
////    {
////      // March 2017 Dale Lear
////      // https://mcneel.myjetbrains.com/youtrack/issue/RH-38377
////      //
////      // The GGI_MARK_NONEXISTING_GLYPHS flag causes GetGlyphIndices()
////      // to set glyphindex[] values to 0xFFFF for missing glyphs.
////      //
////      // GetGlyphIndices() is not capable of getting this glyph in the hdc font.
////      // This often happes for surrogate pair encodings, even when the 
////      // glyph does exist in the font.
////      //
////      // GetGlyphIndices cannot find glyph in the font
////      // Often a surrogate pair and we probably need to be using 
////      // Windows newer Uniscribe API instead of the tired old
////      // GetGlyphIndices + GetGlyphOutlineW stuff.
////      break; 
////    }
////
////    MAT2 mat2;
////    memset(&mat2, 0, sizeof(mat2));
////    mat2.eM11.fract = 0;
////    mat2.eM11.value = 1;
////    mat2.eM12.fract = 0;
////    mat2.eM12.value = 0;
////    mat2.eM21.fract = 0;
////    mat2.eM21.value = 0;
////    mat2.eM22.fract = 0;
////    mat2.eM22.value = 1;
////
////    GLYPHMETRICS glm;
////    memset(&glm, 0, sizeof(glm));
////    const DWORD cb_size = ::GetGlyphOutlineW(font_hdc, glyphindex[0], GGO_NATIVE | GGO_GLYPH_INDEX, &glm, 0, nullptr, &mat2);
////    if (GDI_ERROR == cb_size)
////      break;
////
////    font_unit_glyph_box.m_advance.i = glm.gmCellIncX;
////    font_unit_glyph_box.m_advance.j = glm.gmCellIncY;
////    if (cb_size == 0)
////    {
////      // Non-printing char - nothing to draw
////      font_unit_glyph_box.m_bbmin.i = 0;
////      font_unit_glyph_box.m_bbmin.j = 0;
////      font_unit_glyph_box.m_bbmax.i = font_unit_glyph_box.m_advance.i;
////      font_unit_glyph_box.m_bbmax.j = font_unit_glyph_box.m_advance.j;
////    }
////    else
////    {
////      font_unit_glyph_box.m_bbmin.i = glm.gmptGlyphOrigin.x;
////      font_unit_glyph_box.m_bbmin.j = glm.gmptGlyphOrigin.y - (int)glm.gmBlackBoxY;
////      font_unit_glyph_box.m_bbmax.i = (int)glm.gmBlackBoxX + glm.gmptGlyphOrigin.x;
////      font_unit_glyph_box.m_bbmax.j = glm.gmptGlyphOrigin.y;
////    }
////
////    break;
////  }
////
////  if (nullptr != font_hdc)
////  {
////    if (nullptr != hfont)
////    {
////      ::SelectObject(font_hdc, hfont0);
////      ::DeleteObject(hfont);
////    }
////    ON_Font::DeleteWindowsLogfontDeviceContext(font_hdc);
////  }
////
////  return font_unit_glyph_box.IsSet();
////}



class ON_InternalLogFontAndTextMetric
{
public:
  ON_InternalLogFontAndTextMetric() = default;
  ~ON_InternalLogFontAndTextMetric() = default;
  ON_InternalLogFontAndTextMetric(const ON_InternalLogFontAndTextMetric&) = default;
  ON_InternalLogFontAndTextMetric& operator=(const ON_InternalLogFontAndTextMetric&) = default;

  static const ON_InternalLogFontAndTextMetric Unset;

public:
  ON_SHA1_Hash m_font_hash = ON_SHA1_Hash::ZeroDigest;
  LOGFONT m_lfX;
  TEXTMETRIC m_tmX;
};

ON_InternalLogFontAndTextMetric Internal_InitUnset()
{
  ON_InternalLogFontAndTextMetric lftm;
  memset(&lftm, 0, sizeof(lftm));
  return lftm;
}

const ON_InternalLogFontAndTextMetric ON_InternalLogFontAndTextMetric::Unset(Internal_InitUnset());

////class ON_Font_Windows_LFTM_UserData : public ON_UserData
////{
////public:
////  static void Set(
////    const LOGFONT& lf,
////    const TEXTMETRIC& tm,
////    ON_Font* font
////  )
////  {
////    if (nullptr == font || 0 == lf.lfFaceName[0])
////      return;
////    ON_UserData* ud = font->GetUserData(ON_Font_Windows_LFTM_UserData::Id);
////    ON_Font_Windows_LFTM_UserData* lftm = ON_Font_Windows_LFTM_UserData::Cast(ud);
////    if (nullptr == lftm)
////    {
////      if (nullptr != ud)
////        delete ud;
////      ud = nullptr;
////      lftm = new ON_Font_Windows_LFTM_UserData();
////    }
////    lftm->m_font_hash = font->FontCharacteristicsHash();
////    lftm->m_lf = lf;
////    lftm->m_lftm = tm;
////    if (nullptr == ud)
////    {
////      if (false == font->AttachUserData(lftm))
////        delete lftm;
////    }
////    return;
////  }
////
////  static ON_InternalLogFontAndTextMetric Get(
////    const ON_Font* font
////  );
////
////  ON_Font_Windows_LFTM_UserData()
////  {
////    m_userdata_uuid = ON_Font_Windows_LFTM_UserData::Id;
////    m_userdata_copycount = 1;
////  }
////  ~ON_Font_Windows_LFTM_UserData() = default;
////  ON_Font_Windows_LFTM_UserData(const ON_Font_Windows_LFTM_UserData&) = default;
////  ON_Font_Windows_LFTM_UserData& operator=(const ON_Font_Windows_LFTM_UserData&) = default;
////
////  ON_OBJECT_DECLARE(ON_Font_Windows_LFTM_UserData);
////
////private:
////// {452ADA1A-49F0-4FAF-8E14-73DABE21FC5C}
////  static const ON_UUID Id;
////
////private:
////  ON_SHA1_Hash m_font_hash = ON_SHA1_Hash::ZeroDigest;
////  ON_InternalLogFontAndTextMetric m_lftm = ON_InternalLogFontAndTextMetric::Unset;
////};
////
////// {452ADA1A-49F0-4FAF-8E14-73DABE21FC5C}
////const ON_UUID ON_Font_Windows_LFTM_UserData::Id = { 0x452ada1a, 0x49f0, 0x4faf, { 0x8e, 0x14, 0x73, 0xda, 0xbe, 0x21, 0xfc, 0x5c } };
////ON_OBJECT_IMPLEMENT(ON_Font_Windows_LFTM_UserData, ON_UserData, "452ADA1A-49F0-4FAF-8E14-73DABE21FC5C");
////
////void ON_Font_Windows_LFTM_UserData::Set(
////  const LOGFONT& lf,
////  const TEXTMETRIC& tf,
////  ON_Font* font
////)
////{
////}
////
////ON_InternalLogFontAndTextMetric ON_Font_Windows_LFTM_UserData::Get(
////  const ON_Font* font
////)
////{
////}

static int CALLBACK Internal_GetPlatformWindowsLogfontFontList_CallbackProc(
  const LOGFONT *lf,
  const TEXTMETRIC *ignored_tm,
  DWORD font_type,
  LPARAM lParam
)
{
  for (;;)
  {
    if (nullptr == lf )
      break;
    if (font_type != TRUETYPE_FONTTYPE)
      break;
    if (0 == lParam)
      break;
    if (L'@' == lf->lfFaceName[0])
      break;

    ((ON_SimpleArray<LOGFONT>*)lParam)->AppendNew() = *lf;
    break;
  }

  return 1;
}

static void Internal_CleanLOGFONT(
  LOGFONT& lf,
  bool bZero
)
{
  lf.lfHeight = 0;
  lf.lfWidth = 0;
  lf.lfEscapement = 0;
  lf.lfOrientation = 0;
  if (bZero)
  {
    lf.lfWeight = 0;
    lf.lfItalic = 0;
    lf.lfUnderline = 0;
    lf.lfStrikeOut = 0;
    lf.lfCharSet = DEFAULT_CHARSET;
    lf.lfOutPrecision = 0;
    lf.lfClipPrecision = 0;
    lf.lfQuality = 0;
    lf.lfPitchAndFamily = 0;
  }
  else
  {
    // do not change lfWeight
    if (0 != lf.lfItalic)
      lf.lfItalic = 1;
    if (0 != lf.lfUnderline)
      lf.lfUnderline = 1;
    if (0 != lf.lfStrikeOut)
      lf.lfStrikeOut = 1;
    if (SYMBOL_CHARSET != lf.lfCharSet)
      lf.lfCharSet = DEFAULT_CHARSET;
    lf.lfOutPrecision = ON_Font::WindowsConstants::logfont_out_precis;
    lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    lf.lfQuality = ON_Font::WindowsConstants::logfont_quality;
    lf.lfPitchAndFamily = ON_Font::WindowsConstants::logfont_pitch_and_family;
  }
}

static int Internal_CompareLogfont(const LOGFONT* lhs, const LOGFONT* rhs)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  
  // compare font family name
  const size_t face_name_capacity = sizeof(lhs->lfFaceName) / sizeof(lhs->lfFaceName[0]);  
  int rc = ON_wString::CompareOrdinal(
    lhs->lfFaceName,
    ON_wString::Length(lhs->lfFaceName,face_name_capacity), 
    rhs->lfFaceName, 
    ON_wString::Length(rhs->lfFaceName,face_name_capacity), 
    true
  );
  if (0 != rc)
    return rc;

  // Compare style (upright, italic, ...)
  const int lhs_italic = (0 != lhs->lfItalic) ? 1 : 0;
  const int rhs_italic = (0 != rhs->lfItalic) ? 1 : 0;
  rc = lhs_italic - rhs_italic;
  if (0 != rc)
    return rc;

  // compare weight (normal, bold, ...)
  if (lhs->lfWeight < rhs->lfWeight)
    return -1;
  if (lhs->lfWeight > rhs->lfWeight)
    return 1;

  // compare charset last - SYMBOL_CHARSET require special treatment
  const int lhs_charset = (SYMBOL_CHARSET == lhs->lfCharSet) ? 1 : 0;
  const int rhs_charset = (SYMBOL_CHARSET == rhs->lfCharSet) ? 1 : 0;
  rc = lhs_charset - rhs_charset;
  if (0 != rc)
    return rc;
  
  return 0;
}


unsigned int ON_Font::GetInstalledWindowsLogFonts(
  ON_SimpleArray<LOGFONT>& logfont_list
)
{
  logfont_list.SetCount(0);
  // https://en.wikipedia.org/wiki/List_of_typefaces_included_with_Microsoft_Windows

  HDC font_hdc = ON_Font::CreateWindowsLogfontDeviceContext();
  if (nullptr == font_hdc)
    return 0;
  const DWORD flags = 0;

  // To enumerate all installed Windows LOGFONT values

  // Get list of font family names
  LOGFONT lf;
  memset(&lf, 0, sizeof(lf));
  lf.lfCharSet = DEFAULT_CHARSET;
  ON_SimpleArray<LOGFONT> font_family_list(1000);
  ::EnumFontFamiliesEx(
    font_hdc, 
    &lf,
    Internal_GetPlatformWindowsLogfontFontList_CallbackProc,
    (LPARAM)(&font_family_list), 
    flags
  );

  // remove duplicates
  for (int i = 0; i < font_family_list.Count(); i++)
  {
    Internal_CleanLOGFONT(font_family_list[i], true);
  }
  font_family_list.QuickSort(Internal_CompareLogfont);
  memset(&lf, 0, sizeof(lf));
  int font_family_count = 0;
  for (int i = 0; i < font_family_list.Count(); i++)
  {
    if (0 != Internal_CompareLogfont(&lf, &font_family_list[i]))
    {
      lf = font_family_list[i];
      font_family_list[font_family_count++] = lf;
    }
  }
  font_family_list.SetCount(font_family_count);

  // Get complete list of fonts - family and face (..., Arial(Normal , Bold, Italic, Bold Italic, ...), ...
  logfont_list.Reserve(3 * font_family_count);
  for (int i = 0; i < font_family_count; i++)
  {

    // Append a list of all faces in this font family
    lf = font_family_list[i];
    if (0 == lf.lfFaceName[0])
      continue;
    int count0 = logfont_list.Count();
    bool bAddFamilyLOGFONT = true;
    lf.lfCharSet = DEFAULT_CHARSET;
    ::EnumFontFamiliesEx(
      font_hdc, 
      &lf,
      Internal_GetPlatformWindowsLogfontFontList_CallbackProc,
      (LPARAM)(&logfont_list), 
      flags
    );

    // remove duplicates
    const int count1 = logfont_list.Count();
    for (int j = count0; j < count1; j++)
    {
      Internal_CleanLOGFONT(logfont_list[j], false);
    }
    ON_qsort((void*)(logfont_list.Array() + count0), count1 - count0, sizeof(LOGFONT), (int (*)(const void*,const void*))Internal_CompareLogfont);
    memset(&lf, 0, sizeof(lf));
    for (int j = count0; j < count1; j++)
    {
      LOGFONT lfj = logfont_list[j];
      if (0 == Internal_CompareLogfont(&lf, &lfj))
        continue;
      // Add logfont_list[j] to the culled list fonts.
      lf = logfont_list[j];
      logfont_list[count0++] = lf;
      bAddFamilyLOGFONT = false;
    }

    if (bAddFamilyLOGFONT)
    {
      logfont_list[count0++] = font_family_list[i];
    }
    logfont_list.SetCount(count0);
  }

  ON_Font::DeleteWindowsLogfontDeviceContext(font_hdc);
  font_hdc = nullptr;

  return logfont_list.UnsignedCount();
}


void ON_ManagedFonts::Internal_GetWindowsInstalledFonts(
  ON_SimpleArray<const ON_Font*>& platform_font_list
)
{
  // As of May 2016, Rhino 6 requires WIndows 7 SP2 and DWrite works better.

  // ON_Font::GetInstalledWindowsLogFonts() uses the 2 pass EnumFontFamiliesEx() technique.
  // It has at least 5 failures
  //   It fails to mark "HoloLens MDL Assets" as a symbol font (lfCharSet = SYMBOL_CHARSET)
  //   It fails to mark "Segoe MDL Assets" as a symbol font (lfCharSet = SYMBOL_CHARSET)
  //   It fails to include "Source Sans Pro Black"
  //   It fails to include simulated fonts.
  //   It fails to get PostScript font names.
  ////ON_SimpleArray<LOGFONT> logfont_list;
  ////ON_Font::GetInstalledWindowsLogFonts(logfont_list);
  ////for (int i = 0; i < logfont_list.Count(); i++)
  ////{
  ////  LOGFONT lf = logfont_list[i];
  ////  lf.lfHeight = 0;
  ////  ON_Font* font = new ON_Font();
  ////  if (false == font->SetFromWindowsLogFont( 0, nullptr, lf ) )
  ////  {
  ////    delete font;
  ////    continue;
  ////  }
  ////  platform_font_list.Append(font);
  ////}

  platform_font_list.SetCount(0);

  ON_SimpleArray<ON_WindowsDWriteFontInformation> dwrite_font_list;
  // freetype cannot support simulated fonts. If freetype is not used, we can include simulated fonts.
  const bool bIncludeSimulatedFontFaces = true;
  const bool bKeepDWriteFont = true;
  ON_Font::GetInstalledWindowsDWriteFonts(
    L"GetUserDefaultLocaleName",
    bIncludeSimulatedFontFaces,
    true,
    dwrite_font_list
  );

  platform_font_list.Reserve(dwrite_font_list.Count());

  ON_SHA1_Hash prev_installed_font_hash = ON_SHA1_Hash::ZeroDigest;

  for (int i = 0; i < dwrite_font_list.Count(); i++)
  {
    //const bool bSimulated 
    //  = dwrite_font_list[i].m_bSimulatedBold 
    //  || dwrite_font_list[i].m_bSimulatedOblique 
    //  || dwrite_font_list[i].m_bSimulatedOther;
    //if (bSimulated)
    //{
    //  if (false == bIncludeSimulatedFontFaces)
    //    continue;
    //  if (ON_Font::IsSingleStrokeFontName(dwrite_font_list[i].m_postscript_name))
    //    continue;
    //}

    struct IDWriteFont* dwrite_font = dwrite_font_list[i].m_dwrite_font;
    if (nullptr == dwrite_font)
      continue;

    for (;;)
    {
      ON_Font* installed_font = new ON_Font(ON_Font::FontType::InstalledFont, dwrite_font_list[i]);

      if (
        installed_font->WindowsLogfontName().IsEmpty()
        && installed_font->PostScriptName().IsEmpty()
        && installed_font->FamilyName().IsEmpty()
        && installed_font->QuartetName().IsEmpty()
        )
      {
        // No reliable way to identify this font.
        delete installed_font;
        break;
      }

      platform_font_list.Append(installed_font);
      break;
    }
    dwrite_font_list[i].m_dwrite_font = nullptr;
    dwrite_font->Release();
  }
}
#endif

ON_FontFaceQuartet::ON_FontFaceQuartet(
  const wchar_t* quartet_name,
  const ON_Font* regular,
  const ON_Font* bold,
  const ON_Font* italic,
  const ON_Font* bold_italic
)
  : m_quartet_name(quartet_name)
  , m_regular(regular)
  , m_bold(bold)
  , m_italic(italic)
  , m_bold_italic(bold_italic)
{
  m_quartet_name.TrimLeftAndRight();
}

int ON_FontFaceQuartet::CompareQuartetName(
  const ON_FontFaceQuartet* lhs,
  const ON_FontFaceQuartet* rhs
)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  return ON_wString::CompareOrdinal(lhs->m_quartet_name, rhs->m_quartet_name, true);
}

ON::RichTextStyle ON::RichTextStyleFromUnsigned(unsigned int u)
{
  switch (u)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON::RichTextStyle::Unset);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::RichTextStyle::Windows10SDK);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::RichTextStyle::AppleOSXSDK);
  };
  ON_ERROR("Invalid ON::RichTextStyle value.");
  return ON::RichTextStyle::Unset;
}

ON::RichTextStyle ON::RichTextStyleFromCurrentPlatform()
{
  return
#if defined(ON_RUNTIME_WIN)
    ON::RichTextStyle::Windows10SDK
#elif defined(ON_RUNTIME_APPLE)
    ON::RichTextStyle::AppleOSXSDK
#else
    ON::RichTextStyle::Unset
#endif
    ;
}

const ON_wString ON_FontFaceQuartet::RichTextSample(
  ON::RichTextStyle rich_text_style
) const
{
  const wchar_t* quartet_name = static_cast<const wchar_t*>(m_quartet_name);
  if (nullptr == quartet_name)
    return ON_wString::EmptyString;
  if ( nullptr == m_regular && nullptr == m_bold && nullptr == m_italic && nullptr == m_bold_italic)
    return ON_wString::EmptyString;

  const ON_wString regular_ps = (nullptr != m_regular) ? m_regular->PostScriptName() : ON_wString::EmptyString;
  const ON_wString bold_ps = (nullptr != m_bold) ? m_bold->PostScriptName() : ON_wString::EmptyString;
  const ON_wString italic_ps = (nullptr != m_italic) ? m_italic->PostScriptName() : ON_wString::EmptyString;
  const ON_wString bold_italic_ps = (nullptr != m_bold_italic) ? m_bold_italic->PostScriptName() : ON_wString::EmptyString;

  const ON_wString not_available(L"Not available.");
  const ON_wString regular = regular_ps.IsNotEmpty() ? regular_ps : not_available;
  const ON_wString bold = bold_ps.IsNotEmpty() ? bold_ps : not_available;
  const ON_wString italic = italic_ps.IsNotEmpty() ? italic_ps : not_available;
  const ON_wString bold_italic = bold_italic_ps.IsNotEmpty() ? bold_italic_ps : not_available;

  ON_wString sample;
  switch (rich_text_style)
  {
  case ON::RichTextStyle::Unset:
    break;

  case ON::RichTextStyle::Windows10SDK:
    // font table uses Windows LOGFONT name and \b \i to select faces
    sample = ON_wString::FormatToString(L"{\\rtf1\\deff0{\\fonttbl{\\f0 %ls;}}\\fs40", quartet_name);
    sample += ON_wString::FormatToString(L"{\\f0 Windows 10 LOGFONT Quartet: %ls}{\\par}", quartet_name);
    if (nullptr != m_regular)
      sample += ON_wString::FormatToString(L"{\\f0 Regular: %ls}{\\par}", static_cast<const wchar_t*>(regular_ps));
    if (nullptr != m_bold)
      sample += ON_wString::FormatToString(L"{\\f0\\b Bold: %ls}{\\par}", static_cast<const wchar_t*>(bold_ps));
    if (nullptr != m_italic)
      sample += ON_wString::FormatToString(L"{\\f0\\i Italic: %ls}{\\par}", static_cast<const wchar_t*>(italic_ps));
    if (nullptr != m_bold_italic)
      sample += ON_wString::FormatToString(L"{\\f0\\b\\i Bold Italic: %ls}{\\par}", static_cast<const wchar_t*>(bold_italic_ps));
    sample += ON_wString(L"\\par}");
    break;

  case ON::RichTextStyle::AppleOSXSDK:
    // font table uses unique PostScript names for each face
    if (regular_ps.IsNotEmpty() || bold_ps.IsNotEmpty() || italic_ps.IsNotEmpty() || bold_italic_ps.IsNotEmpty())
    {
      sample = ON_wString::FormatToString(L"{\\rtf1\\deff0{\\fonttbl");
      int fdex = 0;
      if (regular_ps.IsNotEmpty())
        sample += ON_wString::FormatToString(L"{\\f%d %ls;}", fdex++, static_cast<const wchar_t*>(regular_ps));
      if (bold_ps.IsNotEmpty())
        sample += ON_wString::FormatToString(L"{\\f%d %ls;}", fdex++, static_cast<const wchar_t*>(bold_ps));
      if (italic_ps.IsNotEmpty())
        sample += ON_wString::FormatToString(L"{\\f%d %ls;}", fdex++, static_cast<const wchar_t*>(italic_ps));
      if (bold_italic_ps.IsNotEmpty())
        sample += ON_wString::FormatToString(L"{\\f%d %ls;}", fdex++, static_cast<const wchar_t*>(bold_italic_ps));
      sample += ON_wString(L"}\\fs40");

      sample += ON_wString::FormatToString(L"{\\f0 Apple OS X Fake Quartet: %ls}{\\par}", quartet_name);
      fdex = 0;
      if (nullptr != m_regular)
        sample += ON_wString::FormatToString(L"{\\f%d Regular: %ls}{\\par}", fdex++, static_cast<const wchar_t*>(regular_ps));
      if (nullptr != m_bold)
        sample += ON_wString::FormatToString(L"{\\f%d\\b Bold: %ls}{\\par}", fdex++, static_cast<const wchar_t*>(bold_ps));
      if (nullptr != m_italic)
        sample += ON_wString::FormatToString(L"{\\f%d\\i Italic: %ls}{\\par}", fdex++, static_cast<const wchar_t*>(italic_ps));
      if (nullptr != m_bold_italic)
        sample += ON_wString::FormatToString(L"{\\f%d\\b\\i Bold Italic: %ls}{\\par}", fdex++, static_cast<const wchar_t*>(bold_italic_ps));
      sample += ON_wString(L"\\par}");
    }
    break;

  default:
    break;
  }
  return sample;
}


bool ON_FontFaceQuartet::HasRegularFace() const
{
  return (nullptr != RegularFace());
}

bool ON_FontFaceQuartet::HasBoldFace() const
{
  return (nullptr != BoldFace());
}

bool ON_FontFaceQuartet::HasItalicFace() const
{
  return (nullptr != ItalicFace());
}

bool ON_FontFaceQuartet::HasBoldItalicFace() const
{
  return (nullptr != BoldItalicFace());
}

bool ON_FontFaceQuartet::HasAllFaces() const
{
  return HasRegularFace() && HasBoldFace() && HasItalicFace() && HasBoldItalicFace();
}

bool ON_FontFaceQuartet::IsEmpty() const
{
  return IsNotEmpty() ? false : true;
}


bool ON_FontFaceQuartet::IsNotEmpty() const
{
  return (HasRegularFace() || HasBoldFace() || HasItalicFace() || HasBoldItalicFace());
}

const ON_wString ON_FontFaceQuartet::QuartetName() const
{
  return m_quartet_name;
}

const ON_Font* ON_FontFaceQuartet::RegularFace() const
{
  return m_regular;
}

const ON_Font* ON_FontFaceQuartet::BoldFace() const
{
  return m_bold;
}

const ON_Font* ON_FontFaceQuartet::ItalicFace() const
{
  return m_italic;
}

const ON_Font* ON_FontFaceQuartet::BoldItalicFace() const
{
  return m_bold_italic;
}

ON_FontFaceQuartet::Member ON_FontFaceQuartet::QuartetMember(
  const ON_Font* font
) const
{
  if (nullptr == font || m_quartet_name.IsEmpty())
    return ON_FontFaceQuartet::Member::Unset;
  
  if (
    false == m_quartet_name.EqualOrdinal(font->QuartetName(ON_Font::NameLocale::Localized), true)
    && false == m_quartet_name.EqualOrdinal(font->QuartetName(ON_Font::NameLocale::English), true)
    )
    return ON_FontFaceQuartet::Member::Unset;
  
  ON_FontFaceQuartet::Member m[2] = { ON_FontFaceQuartet::Member ::Unset,ON_FontFaceQuartet::Member::Unset};
  if ( font->IsItalicOrOblique() )
  {
    m[0] = ON_FontFaceQuartet::Member::Italic;
    m[1] = ON_FontFaceQuartet::Member::BoldItalic;
  }
  else 
  {
    m[0] = ON_FontFaceQuartet::Member::Regular;
    m[1] = ON_FontFaceQuartet::Member::Bold;
  }
  
  const ON_Font* q[2] = { Face(m[0]),Face(m[1]) };
  
  if (font == q[0])
    return m[0];
  if (font == q[1])
    return m[1];

  ON_wString s[4];
  for (int i = 0; i < 2; i++)
  {
    if (nullptr == q[i])
      continue;

#if defined(ON_RUNTIME_WIN)
    // style, weight, and LOGFONT name is the most reliable way to uniquely identify quartet members on Windows.
    // We've already matched style.
    if (q[i]->FontWeight() != font->FontWeight())
      continue;
    s[0] = q[i]->WindowsLogfontName(ON_Font::NameLocale::Localized);
    s[1] = q[i]->WindowsLogfontName(ON_Font::NameLocale::English);
    s[2] = font->WindowsLogfontName(ON_Font::NameLocale::Localized);
    s[3] = font->WindowsLogfontName(ON_Font::NameLocale::English);
#else
    // style and PostScript name is the most reliable way to uniquely identify quartet members on Mac OS.
    // We've already matched style.
    s[0] = q[i]->PostScriptName(ON_Font::NameLocale::Localized);
    s[1] = q[i]->PostScriptName(ON_Font::NameLocale::English);
    s[2] = font->PostScriptName(ON_Font::NameLocale::Localized);
    s[3] = font->PostScriptName(ON_Font::NameLocale::English);
#endif
    if (s[0].IsNotEmpty() && (s[0].EqualOrdinal(s[2], true) || s[0].EqualOrdinal(s[3], true)))
      return m[i];
    if (s[1].IsNotEmpty() && (s[1].EqualOrdinal(s[2], true) || s[1].EqualOrdinal(s[3], true)))
      return m[i];
  }
  return ON_FontFaceQuartet::Member::Unset;
}

const ON_Font* ON_FontFaceQuartet::Face(
  ON_FontFaceQuartet::Member member
) const
{
  switch (member)
  {
  case ON_FontFaceQuartet::Member::Regular:
    return m_regular;
  case ON_FontFaceQuartet::Member::Bold:
    return m_bold;
  case ON_FontFaceQuartet::Member::Italic:
    return m_italic;
  case ON_FontFaceQuartet::Member::BoldItalic:
    return m_bold_italic;
  case ON_FontFaceQuartet::Member::Unset:
    break;
  }
  return nullptr;
}

const ON_Font* ON_FontFaceQuartet::ClosestFace(
  ON_FontFaceQuartet::Member member
) const
{
  bool bPreferBold = false;
  bool bPreferItalic = false;
  switch (member)
  {
  case ON_FontFaceQuartet::Member::Regular:
    break;
  case ON_FontFaceQuartet::Member::Bold:
    bPreferBold = true;
    break;
  case ON_FontFaceQuartet::Member::Italic:
    bPreferItalic = true;
    break;
  case ON_FontFaceQuartet::Member::BoldItalic:
    bPreferItalic = true;
    bPreferBold = true;
    break;
  default:
    return nullptr;
  }
  return ClosestFace(bPreferBold,bPreferItalic);
}


const ON_Font* ON_FontFaceQuartet::Face(
  bool bBold,
  bool bItalic
) const
{
  return (bItalic)
    ? (bBold ? BoldItalicFace() : ItalicFace())
    : (bBold ? BoldFace() : RegularFace());
}

unsigned int ON_FontFaceQuartet::FaceCount() const
{
  unsigned count = 0;
  const ON_Font* f[4] = { m_regular,m_bold,m_italic,m_bold_italic };
  for (unsigned i = 0; i < 4U; ++i)
  {
    if (nullptr != f[i])
      ++count;
  }
  return count;
}

unsigned int ON_FontFaceQuartet::NotInstalledFaceCount() const
{
  unsigned count = 0;
  const ON_Font* f[4] = { m_regular,m_bold,m_italic,m_bold_italic };
  for (unsigned i = 0; i < 4U; ++i)
  {
    if (nullptr != f[i] && f[i]->IsManagedSubstitutedFont())
      ++count;
  }
  return count;
}

unsigned int ON_FontFaceQuartet::SimulatedFaceCount() const
{
  unsigned count = 0;
  const ON_Font* f[4] = { m_regular,m_bold,m_italic,m_bold_italic };
  for (unsigned i = 0; i < 4U; ++i)
  {
    if (nullptr != f[i] && f[i]->IsSimulated())
      ++count;
  }
  return count;
}


const ON_Font* ON_FontFaceQuartet::ClosestFace(
  bool bPreferedBold,
  bool bPreferedItalic
) const
{
  const ON_Font* f = Face(bPreferedBold, bPreferedItalic);
  if (nullptr != f)
    return f;

  if (IsEmpty())
    return nullptr;

  if (nullptr == m_bold && nullptr == m_bold_italic)
    bPreferedBold = false;
  else if (nullptr == m_regular && nullptr == m_italic)
    bPreferedBold = true;

  if (nullptr == m_italic && nullptr == m_bold_italic)
    bPreferedItalic = false;
  else if (nullptr == m_regular && nullptr == m_bold)
    bPreferedItalic = true;

  f = Face(bPreferedBold, bPreferedItalic);
  if (nullptr != f)
    return f;
  if (nullptr != m_regular)
    return m_regular;
  if (nullptr != m_bold)
    return m_bold;
  if (nullptr != m_italic)
    return m_italic;
  return m_bold_italic;
}

const ON_wString ON_FontFaceQuartet::MemberToString(
  ON_FontFaceQuartet::Member member
)
{
  switch (member)
  {
  case ON_FontFaceQuartet::Member::Unset:
    return ON_wString(L"Unset");
    break;
  case ON_FontFaceQuartet::Member::Regular:
    return ON_wString(L"Regular");
    break;
  case ON_FontFaceQuartet::Member::Bold:
    return ON_wString(L"Bold");
    break;
  case ON_FontFaceQuartet::Member::Italic:
    return ON_wString(L"Italic");
    break;
  case ON_FontFaceQuartet::Member::BoldItalic:
    return ON_wString(L"Bold-Italic");
    break;
  }
  return ON_wString::EmptyString;
}

ON_FontFaceQuartet::Member ON_FontFaceQuartet::MemberFromUnsigned(
  unsigned int member_as_unsigned
)
{
  switch (member_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_FontFaceQuartet::Member::Unset);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_FontFaceQuartet::Member::Regular);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_FontFaceQuartet::Member::Bold);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_FontFaceQuartet::Member::Italic);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_FontFaceQuartet::Member::BoldItalic);
  }
  return ON_FontFaceQuartet::Member::Unset;
}

ON_FontFaceQuartet::Member ON_FontFaceQuartet::MemberFromBoldAndItalic(
  bool bMemberIsBold,
  bool bMemberIsItalic
  )
{
  return
    bMemberIsBold
    ? (bMemberIsItalic ? ON_FontFaceQuartet::Member::BoldItalic : ON_FontFaceQuartet::Member::Bold)
    : (bMemberIsItalic ? ON_FontFaceQuartet::Member::Italic : ON_FontFaceQuartet::Member::Regular)
    ;
}

unsigned ON_FontFaceQuartet::BoldItalicDeviation(
  ON_FontFaceQuartet::Member desired_member, 
  ON_FontFaceQuartet::Member available_member
)
{
  if (desired_member == available_member)
    return 0;

  unsigned distance = 0;

  if (ON_FontFaceQuartet::Member::Unset == desired_member)
  {
    distance += 4;
    desired_member = ON_FontFaceQuartet::Member::Regular;
  }

  if (ON_FontFaceQuartet::Member::Unset == available_member)
  {
    distance += 4;
    available_member = ON_FontFaceQuartet::Member::Regular;
  }

  const bool bDesiredBold = (ON_FontFaceQuartet::Member::Bold == desired_member || ON_FontFaceQuartet::Member::BoldItalic == desired_member);
  const bool bDesiredItalic = (ON_FontFaceQuartet::Member::Italic == desired_member || ON_FontFaceQuartet::Member::BoldItalic == desired_member);

  const bool bAvailableBold = (ON_FontFaceQuartet::Member::Bold == available_member || ON_FontFaceQuartet::Member::BoldItalic == available_member);
  const bool bAvailableItalic = (ON_FontFaceQuartet::Member::Italic == available_member || ON_FontFaceQuartet::Member::BoldItalic == available_member);

  if (bDesiredBold != bAvailableBold)
    distance += 1;
  if (bDesiredItalic != bAvailableItalic)
    distance += 2;

  return distance;
}

const ON_wString ON_Font::WidthWeightSlantDescription(ON_Font::Stretch width, ON_Font::Weight weight, ON_Font::Style slant)
{
  ON_wString wws;
  if (ON_Font::Stretch::Unset != width)
  {
    if (wws.IsNotEmpty())
      wws += ON_wString(L"-");
    wws += ON_Font::StretchToWideString(width);
  }
  if (ON_Font::Weight::Unset != weight)
  {
    if (wws.IsNotEmpty())
      wws += ON_wString(L"-");
    wws += ON_Font::WeightToWideString(weight);
  }
  if (ON_Font::Style::Unset != slant)
  {
    if (wws.IsNotEmpty())
      wws += ON_wString(L"-");
    wws += ON_Font::StyleToWideString(slant);
  }
  return wws;
}

const ON_wString ON_Font::WidthWeightSlantDescription() const
{
  return ON_Font::WidthWeightSlantDescription(this->FontStretch(), this->FontWeight(), this->FontStyle());
}

void ON_FontFaceQuartet::Dump(ON_TextLog& text_log) const
{
  ON_wString quartet_name = this->QuartetName();
  quartet_name.TrimLeftAndRight();
  if (this->IsEmpty() && quartet_name.IsEmpty())
  {
    text_log.Print(L"Empty Quartet\n");
    return;
  }

  const ON_wString quartet_face[4] = {
    ON_FontFaceQuartet::MemberToString(ON_FontFaceQuartet::Member::Regular),
    ON_FontFaceQuartet::MemberToString(ON_FontFaceQuartet::Member::Bold),
    ON_FontFaceQuartet::MemberToString(ON_FontFaceQuartet::Member::Italic),
    ON_FontFaceQuartet::MemberToString(ON_FontFaceQuartet::Member::BoldItalic)
  };
  const ON_Font* quartet_font[4] = {
    RegularFace(),
    BoldFace(),
    ItalicFace(),
    BoldItalicFace()
  };
  const bool bFaceNotAvailable[4] = {
    nullptr == quartet_font[0],
    nullptr == quartet_font[1],
    nullptr == quartet_font[2],
    nullptr == quartet_font[3]
  };
  const bool bFaceNotInstalled[4] = {
    nullptr != quartet_font[0] && quartet_font[0]->IsManagedSubstitutedFont(),
    nullptr != quartet_font[1] && quartet_font[1]->IsManagedSubstitutedFont(),
    nullptr != quartet_font[2] && quartet_font[2]->IsManagedSubstitutedFont(),
    nullptr != quartet_font[3] && quartet_font[3]->IsManagedSubstitutedFont()
  };

  const bool bQuartetNotAvailable 
    = bFaceNotAvailable[0]
    && bFaceNotAvailable[1]
    && bFaceNotAvailable[2]
    && bFaceNotAvailable[3]
    ;
  const bool bQuartetNotInstalled
    = (bFaceNotAvailable[0] || bFaceNotInstalled[0])
    && (bFaceNotAvailable[1] || bFaceNotInstalled[1])
    && (bFaceNotAvailable[2] || bFaceNotInstalled[2])
    && (bFaceNotAvailable[3] || bFaceNotInstalled[3])
    ;

  ON_wString quartet_decription(L"Quartet");
  if (quartet_name.IsNotEmpty())
  {
    quartet_decription += ON_wString(L" ");
    quartet_decription += quartet_name;
  }
  quartet_decription += ON_wString(L":");
  if (bQuartetNotAvailable)
  {
    quartet_decription += ON_wString(L" <not available>");
  }
  else if (bQuartetNotInstalled)
  {
    quartet_decription += ON_wString(L" (not installed)");
  }

  text_log.PrintString(quartet_decription);
  text_log.PrintNewLine();
  text_log.PushIndent();
  for (int i = 0; i < 4; i++)
  {
    ON_wString description(quartet_face[i]);
    description += ON_wString(':');
    const ON_Font* font = quartet_font[i];
    if (nullptr == font)
      description += ON_wString(L" <not available>");
    else
    {
      const ON_wString family_name = font->FamilyName();
      if (family_name.IsNotEmpty())
      {
        description += ON_wString(L" ");
        description += family_name;
        const ON_wString face_name = font->FaceName();
        if (face_name.IsNotEmpty())
        {
          description += ON_wString(L" ");
          description += face_name;
        }
      }

#if defined(ON_RUNTIME_APPLE)
      const ON_wString postscript_name = font->PostScriptName();
      if (postscript_name.IsNotEmpty())
      {
        description += ON_wString(L" (PostScript name=");
        description += postscript_name;
        description += ON_wString(L")");
      }
#endif

      const ON_wString wws = font->WidthWeightSlantDescription();
      if (wws.IsNotEmpty())
      {
        description += ON_wString(L" ");
        description += wws;
      }

      if (font->IsManagedSubstitutedFont())
        description += ON_wString(L" (not installed)");
      else if (font->IsInstalledFont() && font->IsSimulated())
        description += ON_wString(L" (simulated)");
    }
    text_log.PrintString(description);
    text_log.PrintNewLine();
  }
  text_log.PopIndent();
}


#define ON_ManagedFonts_CompareFontPointer(lhs,rhs) \
if (lhs == rhs) return 0; if (nullptr == lhs) return 1; if (nullptr == rhs) return -1; \
const ON_Font* lhs_font = *lhs; const ON_Font* rhs_font = *rhs; \
if (lhs_font == rhs_font) return 0; if (nullptr == lhs_font) return 1; if (nullptr == rhs_font) return -1

int ON_ManagedFonts::CompareFontPointer(ON_Font const* const* lhs, ON_Font const* const* rhs)
{
  ON_ManagedFonts_CompareFontPointer(lhs, rhs);
  return 0;
}

int ON_FontList::ComparePostScriptName(ON_Font const* const* lhs, ON_Font const* const* rhs)
{
  ON_ManagedFonts_CompareFontPointer(lhs, rhs);
  return ON_wString::CompareOrdinal(
    lhs_font->PostScriptName(ON_Font::NameLocale::LocalizedFirst), 
    rhs_font->PostScriptName(ON_Font::NameLocale::LocalizedFirst),
    true
  );
}

int ON_FontList::CompareFamilyName(ON_Font const* const* lhs, ON_Font const* const* rhs)
{
  ON_ManagedFonts_CompareFontPointer(lhs, rhs);
  return ON_wString::CompareOrdinal(
    lhs_font->FamilyName(ON_Font::NameLocale::LocalizedFirst), 
    rhs_font->FamilyName(ON_Font::NameLocale::LocalizedFirst),
    true
  );
}

int ON_FontList::CompareFamilyAndFaceName(ON_Font const* const* lhs, ON_Font const* const* rhs)
{
  ON_ManagedFonts_CompareFontPointer(lhs, rhs);
  int rc = ON_wString::CompareOrdinal(
    lhs_font->FamilyName(ON_Font::NameLocale::LocalizedFirst), 
    rhs_font->FamilyName(ON_Font::NameLocale::LocalizedFirst),
    true
  );
  if ( 0 == rc )
    rc = ON_wString::CompareOrdinal(
    lhs_font->FaceName(ON_Font::NameLocale::LocalizedFirst), 
    rhs_font->FaceName(ON_Font::NameLocale::LocalizedFirst),
    true
  );
  return rc;
}

int ON_FontList::CompareFamilyAndWindowsLogfontName(ON_Font const* const* lhs, ON_Font const* const* rhs)
{
  ON_ManagedFonts_CompareFontPointer(lhs, rhs);
  int rc = ON_wString::CompareOrdinal(
    lhs_font->FamilyName(ON_Font::NameLocale::LocalizedFirst),
    rhs_font->FamilyName(ON_Font::NameLocale::LocalizedFirst),
    true
  );
  if (0 == rc)
    rc = ON_wString::CompareOrdinal(
      lhs_font->WindowsLogfontName(ON_Font::NameLocale::LocalizedFirst),
      rhs_font->WindowsLogfontName(ON_Font::NameLocale::LocalizedFirst),
      true
    );
  return rc;
}

int ON_FontList::CompareWindowsLogfontName(ON_Font const* const* lhs, ON_Font const* const* rhs)
{
  ON_ManagedFonts_CompareFontPointer(lhs, rhs);
  return ON_wString::CompareOrdinal(
    lhs_font->WindowsLogfontName(ON_Font::NameLocale::LocalizedFirst), 
    rhs_font->WindowsLogfontName(ON_Font::NameLocale::LocalizedFirst),
    true
  );
}




int ON_FontList::CompareEnglishPostScriptName(ON_Font const* const* lhs, ON_Font const* const* rhs)
{
  ON_ManagedFonts_CompareFontPointer(lhs, rhs);
  return ON_wString::CompareOrdinal(
    lhs_font->PostScriptName(ON_Font::NameLocale::English), 
    rhs_font->PostScriptName(ON_Font::NameLocale::English),
    true
  );
}

int ON_FontList::CompareEnglishFamilyName(ON_Font const* const* lhs, ON_Font const* const* rhs)
{
  ON_ManagedFonts_CompareFontPointer(lhs, rhs);
  return ON_wString::CompareOrdinal(
    lhs_font->FamilyName(ON_Font::NameLocale::English), 
    rhs_font->FamilyName(ON_Font::NameLocale::English),
    true
  );
}

int ON_FontList::CompareEnglishFamilyAndFaceName(ON_Font const* const* lhs, ON_Font const* const* rhs)
{
  ON_ManagedFonts_CompareFontPointer(lhs, rhs);
  int rc = ON_wString::CompareOrdinal(
    lhs_font->FamilyName(ON_Font::NameLocale::English), 
    rhs_font->FamilyName(ON_Font::NameLocale::English),
    true
  );
  if ( 0 == rc )
    rc = ON_wString::CompareOrdinal(
    lhs_font->FaceName(ON_Font::NameLocale::English), 
    rhs_font->FaceName(ON_Font::NameLocale::English),
    true
  );
  return rc;
}

int ON_FontList::CompareEnglishWindowsLogfontName(ON_Font const* const* lhs, ON_Font const* const* rhs)
{
  ON_ManagedFonts_CompareFontPointer(lhs, rhs);
  return ON_wString::CompareOrdinal(
    lhs_font->WindowsLogfontName(ON_Font::NameLocale::LocalizedFirst), 
    rhs_font->WindowsLogfontName(ON_Font::NameLocale::LocalizedFirst),
    true
  );
}

int ON_FontList::CompareQuartetName(ON_Font const* const* lhs, ON_Font const* const* rhs)
{
  ON_ManagedFonts_CompareFontPointer(lhs, rhs);
  return ON_wString::CompareOrdinal(
    lhs_font->QuartetName(), 
    rhs_font->QuartetName(),
    true
  );
}

int ON_FontList::CompareWeightStretchStyle(
  ON_Font const* const* lhs, 
  ON_Font const* const* rhs
  )
{
  ON_ManagedFonts_CompareFontPointer(lhs, rhs);

  int rc;

  // Upright first, Italic 2nd, Oblique last

  // slope
  const int lhs_font_style = (int)static_cast<unsigned char>(lhs_font->FontStyle());
  const int rhs_font_style = (int)static_cast<unsigned char>(rhs_font->FontStyle());
  rc = (lhs_font_style - rhs_font_style);
  if (0 != rc)
    return rc;

  // width
  const int lhs_font_stretch = (int)static_cast<unsigned char>(lhs_font->FontStretch());
  const int rhs_font_stretch = (int)static_cast<unsigned char>(rhs_font->FontStretch());
  rc = (lhs_font_stretch - rhs_font_stretch);
  if (0 != rc)
    return rc;

  // weight
  const int lhs_font_weight = lhs_font->WindowsLogfontWeight();
  const int rhs_font_weight = rhs_font->WindowsLogfontWeight();
  rc = (lhs_font_weight - rhs_font_weight);
  if (0 != rc)
    return rc;

  return 0;
}


int ON_FontList::CompareStretch(
  ON_Font const* const* lhs, 
  ON_Font const* const* rhs
  )
{
  ON_ManagedFonts_CompareFontPointer(lhs, rhs);
  const int lhs_font_stretch = (int)static_cast<unsigned char>(lhs_font->FontStretch());
  const int rhs_font_stretch = (int)static_cast<unsigned char>(rhs_font->FontStretch());
  const int rc = (lhs_font_stretch - rhs_font_stretch);
  return rc;
}

int ON_FontList::CompareUnderlinedStrikethroughPointSize(
  ON_Font const* const* lhs, 
  ON_Font const* const* rhs
  )
{
  ON_ManagedFonts_CompareFontPointer(lhs, rhs);

  // underlined
  const int lhs_font_underlined = lhs_font->IsUnderlined() ? 1 : 0;
  const int rhs_font_underlined = rhs_font->IsUnderlined() ? 1 : 0;
  int rc = (lhs_font_underlined - rhs_font_underlined);
  if (0 != rc)
    return rc;

  // underlined
  const int lhs_font_strikethrough = lhs_font->IsStrikethrough() ? 1 : 0;
  const int rhs_font_strikethrough = rhs_font->IsStrikethrough() ? 1 : 0;
  rc = (lhs_font_strikethrough - rhs_font_strikethrough);
  if (0 != rc)
    return rc;

  const double lhs_font_point_size = lhs_font->PointSize();
  const double rhs_font_point_size = rhs_font->PointSize();
  if (lhs_font_point_size < rhs_font_point_size)
    return -1;
  if (lhs_font_point_size > rhs_font_point_size)
    return 1;

  return 0;
}

int ON_FontList::CompareFontCharacteristicsHash(
  ON_Font const* const* lhs,
  ON_Font const* const* rhs
)
{
  ON_ManagedFonts_CompareFontPointer(lhs, rhs);
  return ON_SHA1_Hash::Compare(lhs_font->FontCharacteristicsHash(), rhs_font->FontCharacteristicsHash());
}

//
// END list of platform ON_Fonts
//
//////////////////////////////////////////////////////////////////////////


bool ON_Font::ModificationPermitted(
    const char* function_name,
    const char* file_name,
    int line_number
  ) const
{
  if (this == &ON_Font::Default)
    ON_ErrorEx(file_name, line_number, function_name, "ON_Font::Default cannot be modified.");
  else if (this == &ON_Font::Unset)
    ON_ErrorEx(file_name, line_number, function_name, "ON_Font::Unset cannot be modified.");
  else if (IsManagedFont())
    ON_ErrorEx(file_name, line_number, function_name, "Managed fonts cannot be modified.");
  else
  {
    // Modification of this font means the managed information it references
    // will not be valid.  A reference to the correct cached information
    // will be generated when it is actually needed.
    m_font_glyph_cache.reset();
    return true;
  }

  return false;
}

#define ON_FONT_MODIFICATION_PERMITTED this->ModificationPermitted(OPENNURBS__FUNCTION__,__FILE__,__LINE__)

//// V6 files 4F0F51FB-35D0-4865-9998-6D2C6A99721D is the class id for ON_TextStyle
////ON_OBJECT_IMPLEMENT( ON_Font, ON_Object, "4F0F51FB-35D0-4865-9998-6D2C6A99721D" );
//ON_OBJECT_IMPLEMENT( ON_Font, ON_Object, "5F7476D1-798A-4953-B359-4A37699CD6F4" );

const ON_Font* ON_Font::ManagedFont() const
{
  return 
    IsManagedFont()
    ? this
    : ON_Font::GetManagedFont(*this, true);
}

const ON_FontGlyph* ON_Font::CodePointGlyph(
  ON__UINT32 unicode_codepoint
) const
{
  const ON_Font* managed_font = ManagedFont();
  if (nullptr == managed_font)
    return nullptr;

  bool bCreateIfMissing = true;
  bool bFindSubstitutes = true;
  return managed_font->Internal_ManagedCodePointGlyph(unicode_codepoint,bCreateIfMissing,bFindSubstitutes);
}

const ON_Font* ON_Font::GetManagedFont(
  const ON_Font& font_characteristics,
  bool bCreateIfNotFound
)
{
  if (font_characteristics.IsManagedFont())
  {
    // No need to look it up and return itself.
    return &font_characteristics;
  }
  
  return ON_ManagedFonts::List.GetFromFontCharacteristics(font_characteristics,bCreateIfNotFound);
}

const ON_Font* ON_Font::GetManagedFontFromSerialNumber(
  unsigned int managed_font_runtime_serial_number
  )
{
  return ON_ManagedFonts::List.GetFromSerialNumber(managed_font_runtime_serial_number);
}

unsigned int ON_Font::GetManagedFontList(
  ON_SimpleArray< const ON_Font* >& managed_fonts
  )
{
  const ON_SimpleArray< const ON_Font* >& a = ON_ManagedFonts::ManagedFonts().ByIndex();
  if (&a != &managed_fonts)
    managed_fonts = a;
  return managed_fonts.UnsignedCount();
}

unsigned int ON_Font::GetInstalledFontList(
  ON_SimpleArray< const ON_Font* >& installed_fonts
  )
{
  const ON_SimpleArray< const ON_Font* >& a = ON_ManagedFonts::InstalledFonts().ByFamilyName();
  if (&a != &installed_fonts)
    installed_fonts = a;
  return installed_fonts.UnsignedCount();
}

unsigned int ON_Font::GetInstalledFontFamily(
  const wchar_t* font_family_name,
  ON_SimpleArray< const ON_Font* >& installed_fonts
)
{
  installed_fonts.SetCount(0);
  if (nullptr == font_family_name || 0 == font_family_name[0])
    return 0;

  const ON_FontList& installed_font_list = ON_ManagedFonts::InstalledFonts();

  if (0 == installed_font_list.FontListFromNames( nullptr, nullptr, font_family_name, nullptr, installed_fonts) )
    installed_font_list.FontListFromNames(font_family_name, font_family_name, nullptr, nullptr, installed_fonts);

  return installed_fonts.UnsignedCount();
}

static const wchar_t* Internal_NameOverLapSkipNoise(
  const wchar_t* s,
  bool bNoiseFilter
)
{
  if (false == bNoiseFilter)
    return s;

  if (nullptr == s)
    return nullptr;

  while (0 != *s)
  {
    if (*s >= 'A' && *s <= 'Z')
      return s;
    if (*s >= 'a' && *s <= 'z')
      return s;
    if (*s >= 0x80)
      return s;
    s++;
  }
  return s;
}

static const ON_wString Internal_NameOverlapCleanName(
  const wchar_t* s,
  bool bNoiseFilter
)
{
  if (nullptr == s || 0 == s[0])
    return ON_wString::EmptyString;

  ON_wString clean_name;
  wchar_t buffer[128];
  int buffer_count = 0;
  for (wchar_t c = *(s = Internal_NameOverLapSkipNoise(s,bNoiseFilter)); 0 != c; c = *(s = Internal_NameOverLapSkipNoise(++s,bNoiseFilter)))
  {
    buffer[buffer_count++] = ON_wString::MapCharacterOrdinal(ON_StringMapOrdinalType::MinimumOrdinal, c);
    if (127 == buffer_count)
    {
      buffer[buffer_count] = 0;
      clean_name += buffer;
      buffer_count = 0;
    }
  }
  buffer[buffer_count] = 0;
  clean_name += buffer;
  return clean_name;
}

static int Internal_NameOverLap(
  const ON_wString& clean_name,
  const wchar_t* s,
  bool bNoiseFilter
)
{
  if (nullptr == s)
    return 0;
  const wchar_t* clean_s = static_cast<const wchar_t*>(clean_name);
  int overlap_count = 0;
  for (
    s = Internal_NameOverLapSkipNoise(s,bNoiseFilter);
    0 != *clean_s && *clean_s == ON_wString::MapCharacterOrdinal(ON_StringMapOrdinalType::LowerOrdinal,*s);
    s = Internal_NameOverLapSkipNoise(s,bNoiseFilter)
    )
  {
    overlap_count++;
    clean_s++;
    s++;
  }
  return overlap_count;
}

static bool Internal_EqualLogfontName(
  const ON_wString& clean_logfont_name,
  const ON_Font* candidate_font
)
{
  if (nullptr == candidate_font)
    return false;
  if (clean_logfont_name.IsEmpty())
    return false;
  const ON_wString installed_font_logfont_name = Internal_NameOverlapCleanName(candidate_font->WindowsLogfontName(ON_Font::NameLocale::LocalizedFirst),true);
  const bool bEqualLogfontName = ON_wString::EqualOrdinal(clean_logfont_name, installed_font_logfont_name, true);
  return bEqualLogfontName;
}

static bool Internal_EqualFamilyName(
  const ON_wString& clean_family_name,
  const ON_Font* installed_font,
  ON_wString& installed_font_family_name
)
{
  if (nullptr == installed_font)
    return false;
  installed_font_family_name = Internal_NameOverlapCleanName(installed_font->FamilyName(),true);
  const bool bEqualFamileName = ON_wString::EqualOrdinal(clean_family_name, installed_font_family_name, true);
  return bEqualFamileName;
}

class Internal_FontDelta
{
  // Internal_FontDelta is a simple minded attempt at measuring the difference between a target font and a candidate font.
  // It is probably a poor substitute for something fancier like PANOSE information.
  // Unfortunately, we generally do not have PANOSE information about the target font.

public:
  Internal_FontDelta() = default;
  ~Internal_FontDelta() = default;
  Internal_FontDelta(const Internal_FontDelta&) = default;
  Internal_FontDelta& operator= (const Internal_FontDelta&) = default;

  // Initialize this to be a measure of the difference between target_font and candidate_font
  // The target_clean_*_name values take some time to compute, so they are pre-calculated and
  // passed in. There are generally multiple candidate fonts.
  Internal_FontDelta(
    const ON_Font& target_font,
    const ON_wString& target_clean_logfont_name,
    const ON_wString& target_clean_family_name,
    const ON_Font* candidate_font
  )
    : m_candidate_font(candidate_font)
  {
    if (nullptr == m_candidate_font)
    {
      m_hash_delta = 6;
      return;
    }

    // When we have identical PostScript names, we assume they
    // are correct and assume font family, weight, stretch, and style 
    // are exact matches.
    const ON_wString target_postscript_name = target_font.PostScriptName();
    const bool bEqualPostScriptName
      = target_postscript_name.IsNotEmpty()
      && ON_wString::EqualOrdinal(target_postscript_name, m_candidate_font->PostScriptName(), true);

    const bool bEqualLogfontName
      = bEqualPostScriptName
      || (
         ON_Font::Origin::WindowsFont == target_font.FontOrigin()
         && ON_Font::Origin::WindowsFont == candidate_font->FontOrigin()
         && target_clean_logfont_name.IsNotEmpty()
         && Internal_EqualLogfontName(target_clean_logfont_name, candidate_font)
         );

    m_weight_delta 
      = bEqualPostScriptName
      ? 0
      : abs(((int)static_cast<unsigned int>(target_font.FontWeight())) - ((int)static_cast<unsigned int>(candidate_font->FontWeight())));
    m_stretch_delta 
      = bEqualPostScriptName
      ? 0
      : abs(((int)static_cast<unsigned int>(target_font.FontStretch())) - ((int)static_cast<unsigned int>(candidate_font->FontStretch())));
    m_style_delta 
      = bEqualPostScriptName
      ? 0
      : abs(((int)static_cast<unsigned int>(target_font.FontStyle())) - ((int)static_cast<unsigned int>(candidate_font->FontStyle())));

    ON_wString candidate_clean_family_name;
    const bool bEqualFamilyName 
      = bEqualLogfontName 
      || Internal_EqualFamilyName(target_clean_family_name, candidate_font, candidate_clean_family_name);      

    if (target_font.IsUnderlined() != candidate_font->IsUnderlined())
      m_underline_and_strikethrough_delta++;
    if (target_font.IsStrikethrough() != candidate_font->IsStrikethrough())
      m_underline_and_strikethrough_delta++;

    m_family_name_delta = 0;


    if (
      bEqualFamilyName
      && 0 == m_weight_delta
      && 0 == m_stretch_delta
      && 0 == m_style_delta
      )
    {
      // This is either an exact match (m_hash_delta = 0) or a very close match (m_hash_delta = 1).
      m_hash_delta 
        = (0 == m_underline_and_strikethrough_delta && target_font.FontCharacteristicsHash() == candidate_font->FontCharacteristicsHash()) 
        ? 0
        : 1;
      return;
    }

    // If PANOSE information were available for target_font and candidate_font, it would be useful here.

    if (
      bEqualLogfontName 
      && 0 == m_stretch_delta 
      && m_style_delta <= 1
      )
    {
      // There are at most 4 "faces" with the same WINDOWS LOGFONT.lfFaceName and the differences
      // among the four "faces" are almost always in weight (normal or bold) or style (upright or italic). 
      // Fonts with larger differences in weight or style or any significant difference in stretch 
      // typically have different values of LOGFONT.lfFaceName.
      // (Underlined and Strikethrough are not "faces").
      m_hash_delta = 2;
      return;
    }

    if (bEqualFamilyName)
    {
      // A family, like "Arial", can have manu faces with a wide variety of weights, stretches, and styles.
      // The LOGFONTs with lfFaceName = "Arial", "Arial Narrow", "Arial Black", ... are all in the "Arial" family.
      m_hash_delta = 3;
      return;
    }

    // Differences below here (m_hash_delta >= 4) are generally visually significant.
    // Calculate font family name overlap
    int name_overlap = Internal_NameOverLap(target_clean_family_name, candidate_clean_family_name, true);
    m_family_name_delta = target_clean_family_name.Length() - name_overlap;
    if (0 == m_family_name_delta)
    {
      // clean_font_family_name.Length() = name_overlap means that
      // clean_font_family_name.Length() <= installed_font_family_name.Length()
      // and installed_font_family_name begins with clean_font_family_name.
      // If installed_font_family_name.Length() > clean_font_family_name.Length(),
      // m_name_delta < 0 and it measures how much tail was not matched
      m_family_name_delta = target_clean_family_name.Length() - candidate_clean_family_name.Length();
    }

    m_hash_delta 
      = (0 == m_style_delta || ON_Font::Style::Upright != target_font.FontStyle())
      ? 4
      : 5;
  }

  bool IsExactMatch() const
  {
    return (nullptr != m_candidate_font && 0 == m_hash_delta );
  }

  // If Compare(lhs,rhs) < 0, then lhs is a better match for the target font passed to the constructor.
  static int Compare(const Internal_FontDelta& lhs, const Internal_FontDelta& rhs)
  {
    if (lhs.m_candidate_font == rhs.m_candidate_font)
      return 0;
    if (nullptr == rhs.m_candidate_font)
      return -1; // lhs is better because it has a candidate font
    if (nullptr == lhs.m_candidate_font)
      return 1; // rhs is better because it has a candidate font

    // m_hash_delta >= 0 and smaller values of m_hash_delta indicate better matches
    int rc = (lhs.m_hash_delta - rhs.m_hash_delta);
    if (0 != rc)
      return rc;

    rc = (lhs.m_family_name_delta - rhs.m_family_name_delta);
    if (0 != rc)
    {
      if (0 == lhs.m_family_name_delta)
        return -1; // lhs is in the same family

      if (0 == rhs.m_family_name_delta)
        return 1; // rhs is in the same family

      if (lhs.m_family_name_delta < 0 && rhs.m_family_name_delta < 0)
      {
        // When both values of m_name_delta are negative, it
        // means their font family names both began with the
        // family name we are searching for. In this 
        // case the shortest tail is best.
        // The length of that tail is -m_name_delta,
        // so the least negative m_delta is the best match.
        return -rc;
      }
      // If at least one value of m_delta > 0, then the
      // smallest value of m_delta is the best match.
      return rc;
    }

    rc = (lhs.m_style_delta - rhs.m_style_delta);
    if (0 != rc)
      return rc;

    rc = (lhs.m_weight_delta - rhs.m_weight_delta);
    if (0 != rc)
      return rc;

    rc = (lhs.m_stretch_delta - rhs.m_stretch_delta);
    if (0 != rc)
      return rc;

    rc = (lhs.m_underline_and_strikethrough_delta - rhs.m_underline_and_strikethrough_delta);
    if (0 != rc)
      return rc;      

    return 0;
  }

  // Points to a candidate for matching the original font
  const ON_Font* m_candidate_font = nullptr;

  // 0: exact match
  // 1: same family, weight, stretch, style match - different hash
  // 2: same LOGFONT.lfName -  different weight,stretch,style
  // 3: same family name - different LOGFONT.lfFaceName, weight,stretch,style
  // 4: some overlap in family name
  // 5: least favorable match
  int m_hash_delta = 0;

  // m_family_name_delta
  // <0: partial overlap
  //  0: exact match
  // >0: installed font family name is longer but exact match with start
  int m_family_name_delta = 0;

  // m_logfont_name_delta
  // <0: partial overlap
  //  0: exact match
  // >0: installed font LOGFONT.lfFaceName name is longer but exact match with start
  int m_logfont_name_delta = 0;

  // Weight delta = absolute value of difference between weights.
  int m_weight_delta = 0;

  // Stretch (width) delta = absolute value of difference between stretch.
  int m_stretch_delta = 0; 

  // Style (slope) delta = absolute value of difference between font styles.
  int m_style_delta = 0;  

  // Underlined and strikethrough delta = number of different bools.
  int m_underline_and_strikethrough_delta = 0;
};

const ON_Font* ON_Font::BestMatch(
  ON_Font const*const* candidate_font_list,
  size_t candidate_font_count
) const
{
  if (nullptr == candidate_font_list || candidate_font_count < 1)
    return nullptr;

  if (1 == candidate_font_count)
    return candidate_font_list[0];

  const ON_wString target_clean_logfont_name = Internal_NameOverlapCleanName(WindowsLogfontName(),true);
  const ON_wString target_clean_family_name = Internal_NameOverlapCleanName(FamilyName(),true);
 
  Internal_FontDelta best_match;
  
  for (size_t i = 0; i < candidate_font_count; i++)
  {
    const ON_Font* candidate_font = candidate_font_list[i];
    if (nullptr == candidate_font)
      continue;

    const Internal_FontDelta delta(
      *this,
      target_clean_logfont_name,
      target_clean_family_name,
      candidate_font
      );  

    if (delta.IsExactMatch())
      return candidate_font;

    if (nullptr == best_match.m_candidate_font || Internal_FontDelta::Compare(delta, best_match) < 0 )
      best_match = delta;
  }

  return best_match.m_candidate_font;
}

unsigned int ON_Font::WeightStretchStyleDeviation(
  ON_Font::Weight prefered_weight,
  ON_Font::Stretch prefered_stretch,
  ON_Font::Style prefered_style,
  ON_Font::Weight available_weight,
  ON_Font::Stretch available_stretch,
  ON_Font::Style available_style
)
{
  if (ON_Font::Weight::Unset == prefered_weight)
    prefered_weight = available_weight;
  if (ON_Font::Stretch::Unset == prefered_stretch)
    prefered_stretch = available_stretch;
  if (ON_Font::Style::Unset == prefered_style)
    prefered_style = available_style;
  const unsigned int weight_delta = abs(((int)prefered_weight) - ((int)available_weight));
  const unsigned int stretch_delta = abs(((int)prefered_stretch) - ((int)available_stretch));
  const unsigned int style_delta = abs(((int)prefered_style) - ((int)available_style));
  return 4*(1000U * style_delta + 20U * weight_delta + stretch_delta);
}

unsigned int ON_Font::WeightStretchStyleDeviation(
  ON_Font::Weight prefered_weight,
  ON_Font::Stretch prefered_stretch,
  ON_Font::Style prefered_style,
  const ON_Font* available_font
)
{
  if (nullptr == available_font)
    return 0xFFFFFFF;

  return ON_Font::WeightStretchStyleDeviation(
    prefered_weight, 
    prefered_stretch, 
    prefered_style,
    available_font->FontWeight(),
    available_font->FontStretch(),
    available_font->FontStyle()
  );
}

unsigned int ON_Font::WeightStretchStyleDeviation(
  const ON_Font* prefered_weight_stretch_style,
  const ON_Font* available_font
)
{
  if (nullptr == prefered_weight_stretch_style)
    prefered_weight_stretch_style = &ON_Font::Default;
  ON_Font::Weight prefered_weight = prefered_weight_stretch_style->FontWeight();
  ON_Font::Stretch prefered_stretch = prefered_weight_stretch_style->FontStretch();
  ON_Font::Style prefered_style = prefered_weight_stretch_style->FontStyle();
  return ON_Font::WeightStretchStyleDeviation(prefered_weight, prefered_stretch, prefered_style, available_font);
}

unsigned int ON_Font::UnderlinedStrikethroughDeviation(
  bool bPreferedUnderline,
  bool bPreferedStrikethrough,
  bool bAvailableUnderline,
  bool bAvailableStrikethrough
)
{
  const unsigned int underlined_dev = (unsigned int)abs((int)(bPreferedUnderline ? 1 : 0) - (int)(bAvailableUnderline ? 1 : 0));
  const unsigned int strikethrough_dev = (unsigned int)abs((int)(bPreferedStrikethrough ? 1 : 0) - (int)(bAvailableStrikethrough ? 1 : 0));
  return 2 * underlined_dev + strikethrough_dev;
}

unsigned int ON_Font::UnderlinedStrikethroughDeviation(
  bool bPreferedUnderline,
  bool bPreferedStrikethrough,
  const ON_Font* available_font
)
{
  return ON_Font::UnderlinedStrikethroughDeviation(
    bPreferedUnderline,
    bPreferedStrikethrough,
    (nullptr == available_font) ? false : available_font->IsUnderlined(),
    (nullptr == available_font) ? false : available_font->IsStrikethrough()
  );
}

unsigned int ON_Font::UnderlinedStrikethroughDeviation(
  const ON_Font* prefered_underlined_strikethrough,
  const ON_Font* available_font
)
{
  return ON_Font::UnderlinedStrikethroughDeviation(
    (nullptr == prefered_underlined_strikethrough) ? false : prefered_underlined_strikethrough->IsUnderlined(),
    (nullptr == prefered_underlined_strikethrough) ? false : prefered_underlined_strikethrough->IsStrikethrough(),
    (nullptr == available_font) ? false : available_font->IsUnderlined(),
    (nullptr == available_font) ? false : available_font->IsStrikethrough()
  );
}

unsigned int ON_Font::RichTextPropertyDeviation(
    bool bPreferedRtfBold,
    bool bPreferedItalic,
    bool bPreferedUnderline,
    bool bPreferedStrikethrough,
    const ON_Font* available_font
)
{
  if (nullptr == available_font)
    return 0xFFFFFFFF;
  return ON_Font::RichTextPropertyDeviation(
    bPreferedRtfBold,
    bPreferedItalic,
    bPreferedUnderline,
    bPreferedStrikethrough,
    available_font->IsBold(),
    available_font->IsItalic(),
    available_font->IsUnderlined(),
    available_font->IsStrikethrough()
  );
}

unsigned int ON_Font::RichTextPropertyDeviation(
    bool bPreferedRtfBold,
    bool bPreferedItalic,
    bool bPreferedUnderline,
    bool bPreferedStrikethrough,
    bool bAvailableRtfBold,
    bool bAvailableItalic,
    bool bAvailableUnderline,
    bool bAvailableStrikethrough
)
{
  const ON_Font::Weight prefered_weight = bPreferedRtfBold ? ON_Font::Weight::Bold : ON_Font::Weight::Normal;
  const ON_Font::Weight available_weight = bAvailableRtfBold ? ON_Font::Weight::Bold : ON_Font::Weight::Normal;

  const ON_Font::Style prefered_style = bPreferedItalic ? ON_Font::Style::Italic : ON_Font::Style::Upright;
  const ON_Font::Style available_style = bPreferedItalic ? ON_Font::Style::Italic : ON_Font::Style::Upright;

  const unsigned int wss_dev = ON_Font::WeightStretchStyleDeviation(
    prefered_weight, ON_Font::Stretch::Medium, prefered_style,
    available_weight, ON_Font::Stretch::Medium, available_style
  );

  const unsigned int us_dev = ON_Font::UnderlinedStrikethroughDeviation(
    bPreferedUnderline,
    bPreferedStrikethrough,
    bAvailableUnderline,
    bAvailableStrikethrough
  );
  return wss_dev + us_dev;
}

const ON_Font* ON_Font::Internal_BestMatchWeightStretchStyle(
  ON_Font::Weight prefered_weight,
  ON_Font::Stretch prefered_stretch,
  ON_Font::Style prefered_style,
  ON_Font const * const * font_list, 
  size_t font_count
)
{
  if (nullptr == font_list || font_count <= 0)
    return nullptr;

  const ON_Font* best_font = nullptr;
  unsigned int best_delta = 0xFFFFFFFF;
  for (size_t i = 0; i < font_count; i++)
  {
    const ON_Font* font = font_list[i];
    if (nullptr == font)
      continue;
    const unsigned int delta = ON_Font::WeightStretchStyleDeviation(
      prefered_weight, 
      prefered_stretch, 
      prefered_style,
      font
    );
    if (0 == delta)
      return font;
    if (nullptr == best_font || delta < best_delta)
    {
      best_font = font;
      best_delta = delta;
    }
  }

  return best_font;
}

const ON_Font* ON_Font::BestMatch(
  const ON_SimpleArray< const ON_Font* >& font_list
) const
{
  return BestMatch(
    font_list.Array(),
    font_list.UnsignedCount()
  );
}

const ON_FontList& ON_Font::ManagedFontList()
{
  return ON_ManagedFonts::ManagedFonts();
}

const ON_FontList& ON_Font::InstalledFontList()
{
  return ON_ManagedFonts::InstalledFonts();
}

const ON_Font* ON_Font::InstalledFontFromRichTextProperties(
  const wchar_t* rtf_font_name,
  bool bRtfBold,
  bool bRtfItalic
)
{
  ON_wString local_rtf_font_name(rtf_font_name);
  local_rtf_font_name.TrimLeftAndRight();
  if (local_rtf_font_name.IsEmpty())
    local_rtf_font_name = ON_Font::Default.RichTextFontName();
  rtf_font_name = local_rtf_font_name;

  // It is critical that bRequireFaceMatch because the input name must
  // clearly identify a font in some way. The search below allows for this
  // name to appear in various contexts (LOGFONT, PostScript, Family+Face, Family).
  const bool bRequireFaceMatch = true;

  // It is critical that bRequireStyleMatch = false. See below
  const bool bRequireStyleMatch = false;

  // The preferred_weight is a bias used to pick between faces that have matching name properties.
  // An exact match is not required because bRequireStyleMatch = false;
  const ON_Font::Weight preferred_weight = bRtfBold ? ON_Font::Weight::Semibold : ON_Font::Weight::Medium;

  // The preferred_style is a bias used to pick between faces that have matching name properties.
  // An exact match is not required because bRequireStyleMatch = false;
  const ON_Font::Style preferred_style = bRtfItalic ? ON_Font::Style::Italic : ON_Font::Style::Upright;

  const bool bUnderlined = false;
  const bool bStrikethrough = false;
  const wchar_t* ignore_postscript_name = nullptr;
  const wchar_t* ignore_windows_logfont_name = nullptr;
  const wchar_t* ignore_family_name = nullptr;
  const wchar_t* ignore_prefered_face_name = nullptr;


  // 1st: Try LOGFONT name. For Windows this is the very best choice.
  // For MacOS this works the best in practice. If it fails, we move onto PostScript.
  const ON_Font* installed_font = ON_Font::InstalledFontList().FromNames(
    ignore_postscript_name,
    rtf_font_name, // windows_logfont_name,
    ignore_family_name,
    ignore_prefered_face_name,
    preferred_weight, ON_Font::Stretch::Unset, preferred_style,
    bRequireFaceMatch, bRequireStyleMatch, bUnderlined, bStrikethrough,
    0.0
  );

  while (nullptr == installed_font)
  {

    // 2nd: Try PostScript name
    installed_font = ON_Font::InstalledFontList().FromNames(
      rtf_font_name, // postscript_name,
      ignore_windows_logfont_name,
      ignore_family_name,
      ignore_prefered_face_name,
      preferred_weight, ON_Font::Stretch::Unset, preferred_style,
      bRequireFaceMatch, bRequireStyleMatch, bUnderlined, bStrikethrough,
      0.0
    );
    if (nullptr != installed_font)
      break;

    // 3rd: Try Family + Face name
    const wchar_t hyphen[2] = {ON_wString::HyphenMinus,0};
    for (const wchar_t* separator = rtf_font_name + 1; 0 != *separator; ++separator)
    {
      if (ON_wString::Space != *separator && ON_wString::HyphenMinus != *separator)
        continue;
      ON_wString family_name(rtf_font_name, (int)(separator - rtf_font_name));
      family_name.TrimLeftAndRight();
      family_name.TrimLeftAndRight(hyphen);
      family_name.TrimLeftAndRight();
      if (family_name.IsEmpty())
        continue;
      ON_wString face_name(separator + 1);
      face_name.TrimLeftAndRight();
      face_name.TrimLeftAndRight(hyphen);
      face_name.TrimLeftAndRight();
      if (face_name.IsEmpty())
        continue;

      installed_font = ON_Font::InstalledFontList().FromNames(
        ignore_postscript_name,
        ignore_windows_logfont_name,
        family_name, face_name,
        preferred_weight, ON_Font::Stretch::Unset, preferred_style,
        bRequireFaceMatch, bRequireStyleMatch, bUnderlined, bStrikethrough,
        0.0
      );
      if (nullptr != installed_font)
        break;
    }
    if (nullptr != installed_font)
      break;


    // 4th: Try Family name
    installed_font = ON_Font::InstalledFontList().FromNames(
      ignore_postscript_name,
      ignore_windows_logfont_name,
      rtf_font_name, // family name
      ignore_prefered_face_name,
      preferred_weight, ON_Font::Stretch::Unset, preferred_style,
      bRequireFaceMatch, bRequireStyleMatch, bUnderlined, bStrikethrough,
      0.0
    );
    if (nullptr != installed_font)
      break;

    // No installed font comes close to matching the input name parameter 
    break;
  }

  if (nullptr != installed_font)
  {
    const ON_FontFaceQuartet q = installed_font->InstalledFontQuartet(); // only look at installed quartet!
    const ON_Font* f = q.ClosestFace(bRtfBold, bRtfItalic);
    return (nullptr != f) ? f : installed_font;
  }

  return nullptr;
}

static void Internal_SetFakeNamesFromExistingNames(
  ON_wString loc_existing,
  ON_wString en_existing,
  ON_wString& loc_fake,
  ON_wString& en_fake
)
{
  loc_existing.TrimLeftAndRight();
  en_existing.TrimLeftAndRight();
  if (loc_existing.IsEmpty())
    loc_existing = en_existing;
  else if (en_existing.IsEmpty())
    en_existing = loc_existing;
  if (loc_existing.IsNotEmpty())
    loc_fake = loc_existing;
  if (en_existing.IsNotEmpty())
    en_fake = en_existing;
}


const ON_Font* ON_Font::Internal_DecoratedFont(
  bool bUnderlined,
  bool bStrikethrough
) const
{
  // Underline and strikethrough are font rendering effects and are not  designed into the font glyphs.
  if (false == bUnderlined && false == bStrikethrough)
    return this;

  if (bUnderlined ? 0 : 1 == this->IsUnderlined() ? 0 : 1 && bStrikethrough ? 0 : 1 == this->IsStrikethrough() ? 0 : 1)
    return this;

  ON_Font decorated(*this);
  decorated.SetUnderlined(bUnderlined);
  decorated.SetStrikethrough(bStrikethrough);
  const ON_Font* decorated_font = decorated.ManagedFont();
  if (nullptr != decorated_font && ON_FontFaceQuartet::Member::Unset == decorated_font->m_quartet_member)
  {
    // Decorated faces are not explicitly in quartets,
    // but when dealing with rich text, we need to know what quartet member they are decorating.
    decorated_font->m_quartet_member = this->m_quartet_member;
  }

  return (nullptr != decorated_font) ? decorated_font : this;
}

const ON_Font* ON_Font::FontFromRichTextProperties(
  ON_wString rich_text_font_name,
  bool bBoldQuartetMember,
  bool bItalicQuartetMember,
  bool bUnderlined,
  bool bStrikethrough
)
{
  rich_text_font_name.TrimLeftAndRight();
  if (rich_text_font_name.IsEmpty())
    rich_text_font_name = ON_Font::Default.RichTextFontName();

  const ON_FontFaceQuartet::Member rich_text_quartet_face = ON_FontFaceQuartet::MemberFromBoldAndItalic(bBoldQuartetMember, bItalicQuartetMember);

  ON_FontFaceQuartet installed_quartet = ON_ManagedFonts::InstalledFonts().QuartetFromQuartetName(rich_text_font_name);
  if ( installed_quartet.IsNotEmpty() )
  {
    // Installed font quartets use ClosestFace() because we know all the faces 
    // the real font contains.
    // If you don't get what you want, your asking for something that does not exist.
    // You may need to fix some user interface to not offer the choice that led you here.
    const ON_Font* installed_font = installed_quartet.ClosestFace(rich_text_quartet_face); // DO NOT CHANGE TO Face()
    if (nullptr != installed_font)
      return installed_font->Internal_DecoratedFont( bUnderlined, bStrikethrough);
  }

  const ON_FontFaceQuartet managed_substitute_quartet = ON_ManagedFonts::ManagedFonts().QuartetFromQuartetName(rich_text_font_name);
  if (managed_substitute_quartet.IsNotEmpty())
  {
    // Missing font quartets use Face() because we don't know what the real font quartet looks like.
    const ON_Font* managed_quartet_face = managed_substitute_quartet.Face(rich_text_quartet_face); // DO NOT CHANGE TO ClosestFace()
    if (nullptr != managed_quartet_face)
      return managed_quartet_face->Internal_DecoratedFont(bUnderlined, bStrikethrough); // this missing face has already been added to the quartet
  }

  // We will need to make a new managed font and put it in  a reasonable managed quartet.

  // All memory allocated for managed fonts is permanent app workspace memory.
  ON_MemoryAllocationTracking disable_tracking(false);
  {
    // convert the name to untracked memory so it doesn't look like a leak
    const ON_wString local_str(rich_text_font_name);
    rich_text_font_name = ON_wString::EmptyString;
    rich_text_font_name = ON_wString(static_cast<const wchar_t*>(local_str));
  }

  const ON_Font* installed_font = nullptr;
  installed_font = ON_Font::InstalledFontFromRichTextProperties(rich_text_font_name, bBoldQuartetMember, bItalicQuartetMember);
  if (nullptr == installed_font)
  {
#if defined(ON_RUNTIME_APPLE)
    if (nullptr == installed_font)
      installed_font = ON_Font::InstalledFontList().FromPostScriptName(rich_text_font_name);
#endif
    if (nullptr == installed_font)
      installed_font = ON_Font::InstalledFontList().FromWindowsLogfontName(rich_text_font_name);
#if !defined(ON_RUNTIME_APPLE)
    if (nullptr == installed_font)
      installed_font = ON_Font::InstalledFontList().FromPostScriptName(rich_text_font_name);
#endif
    if (nullptr == installed_font)
      installed_font = ON_Font::InstalledFontList().FromFamilyName(rich_text_font_name, ON_FontFaceQuartet::MemberToString(ON_FontFaceQuartet::Member::Regular) );
    if (nullptr != installed_font)
    {
      installed_quartet = installed_font->InstalledFontQuartet(); // only look at installed quartet!
      const ON_Font* installed_rtfface = installed_quartet.ClosestFace(bBoldQuartetMember, bItalicQuartetMember);
      if (nullptr != installed_rtfface)
        installed_font = installed_rtfface;
    }
  }

  if (nullptr != installed_font)
  {
    // The font is installed on this device.
    return installed_font->Internal_DecoratedFont(bUnderlined, bStrikethrough);
  }


  ON_wString loc_quartet_name = rich_text_font_name;
  ON_wString en_quartet_name = rich_text_font_name;

  ON_wString loc_family_name = rich_text_font_name;
  ON_wString en_family_name = rich_text_font_name;

  ON_wString loc_windows_logfont_name = rich_text_font_name;
  ON_wString en_windows_logfont_name = rich_text_font_name;

  ON_Font::Weight fake_normal_weight = ON_Font::Weight::Unset;
  ON_Font::Weight fake_bold_weight = ON_Font::Weight::Unset;

  if (managed_substitute_quartet.IsNotEmpty())
  {
    // get known names and guesses at weights from the existing parts of the quartet.

    const ON_Font* normal_weight_font = managed_substitute_quartet.Face(ON_FontFaceQuartet::Member::Regular);
    if ( nullptr == normal_weight_font)
      normal_weight_font = managed_substitute_quartet.Face(ON_FontFaceQuartet::Member::Italic);

    const ON_Font* bold_weight_font = managed_substitute_quartet.Face(ON_FontFaceQuartet::Member::Bold);
    if (nullptr == bold_weight_font)
      bold_weight_font = managed_substitute_quartet.Face(ON_FontFaceQuartet::Member::BoldItalic);

    const ON_Font* names_font = (nullptr != normal_weight_font) ? normal_weight_font : bold_weight_font;

    if (nullptr != names_font)
    {
      Internal_SetFakeNamesFromExistingNames(
        names_font->QuartetName(ON_Font::NameLocale::Localized),
        names_font->QuartetName(ON_Font::NameLocale::English),
        loc_quartet_name,
        en_quartet_name
      );

      Internal_SetFakeNamesFromExistingNames(
        names_font->FamilyName(ON_Font::NameLocale::Localized),
        names_font->FamilyName(ON_Font::NameLocale::English),
        loc_family_name,
        en_family_name
      );

      Internal_SetFakeNamesFromExistingNames(
        names_font->WindowsLogfontName(ON_Font::NameLocale::Localized),
        names_font->WindowsLogfontName(ON_Font::NameLocale::English),
        loc_windows_logfont_name,
        en_windows_logfont_name
      );
    }

    if (nullptr != normal_weight_font)
      fake_normal_weight = normal_weight_font->FontWeight();
    if (nullptr != bold_weight_font)
      fake_bold_weight = bold_weight_font->FontWeight();

    const unsigned normal_unsigned = static_cast<unsigned>(fake_normal_weight);
    const unsigned bold_unsigned = static_cast<unsigned>(fake_bold_weight);
    const unsigned default_normal_unsigned = static_cast<unsigned>(ON_Font::Weight::Normal);
    const unsigned default_bold_unsigned = static_cast<unsigned>(ON_Font::Weight::Bold);
    const unsigned min_weight = static_cast<unsigned>(ON_Font::Weight::Thin);
    const unsigned max_weight = static_cast<unsigned>(ON_Font::Weight::Heavy);

    if (ON_Font::Weight::Unset != fake_normal_weight && ON_Font::Weight::Unset == fake_bold_weight)
    {
      // have to guess at a bold weight
      fake_bold_weight
        = normal_unsigned < default_bold_unsigned
        ? ON_Font::Weight::Bold
        : ((normal_unsigned + 2 <= max_weight) ? ON_Font::FontWeightFromUnsigned(normal_unsigned + 2) : ON_Font::Weight::Heavy)
        ;
    }

    if (ON_Font::Weight::Unset != fake_bold_weight && ON_Font::Weight::Unset == fake_normal_weight)
    {
      // have to guess at a normal weight
      fake_normal_weight
        = bold_unsigned > default_normal_unsigned
        ? ON_Font::Weight::Normal
        : ((min_weight + 2 <= bold_unsigned) ? ON_Font::FontWeightFromUnsigned(bold_unsigned - 2) : ON_Font::Weight::Thin)
        ;
    }
  }

  if (ON_Font::Weight::Unset == fake_normal_weight)
    fake_normal_weight = ON_Font::Weight::Normal;
  if (ON_Font::Weight::Unset == fake_bold_weight)
    fake_bold_weight = ON_Font::Weight::Bold;

  const double point_size = 0.0;
  const unsigned int logfont_charset = ON_Font::Default.LogfontCharSet();

  ON_Font fake_font;
  fake_font.SetFontCharacteristics(
    point_size,
    rich_text_font_name,
    bBoldQuartetMember ? fake_bold_weight : fake_normal_weight,
    bItalicQuartetMember ? ON_Font::Style::Italic : ON_Font::Style::Upright,
    ON_Font::Stretch::Medium,
    false, // DO NOT PASS bUnderlined here
    false, // DO NOT PASS bStrikethrough here
    ON_FontMetrics::DefaultLineFeedRatio,
    logfont_charset
  );

  fake_font.m_loc_family_name = loc_family_name;
  fake_font.m_en_family_name = en_family_name;

  fake_font.m_loc_windows_logfont_name = loc_windows_logfont_name;
  fake_font.m_en_windows_logfont_name = en_windows_logfont_name;

  // There is no reliable way to get the face name  - we fake it by using the quartet face name below
  fake_font.m_loc_face_name = ON_FontFaceQuartet::MemberToString(rich_text_quartet_face);
  fake_font.m_en_face_name = fake_font.m_loc_face_name;

  // There is no reliable way to get the PostScript name 
  fake_font.m_loc_postscript_name = ON_wString::EmptyString;
  fake_font.m_en_postscript_name = ON_wString::EmptyString;

  fake_font.m_quartet_member = rich_text_quartet_face;

  // When reading 3dm files created on a device with other fonts
  // Frequently a managed font is added when a dimstyle is read.
  // Later on annotation objects are read and rich text requests
  // regular/bold/italic/bold-italic faces from the dimstyle font's 
  // quartet. When existing_managed_font is not nullptr, we need
  // to create a fake quartet containing that font.
  // When existing_managed_font is nullptr, we need to create
  // a fake quartet based on only the rtf_font_name.
  // (Sure wish we had not dumped the V5 font table, sigh.)
  const ON_Font* existing_managed_font = ON_Font::GetManagedFont(fake_font, false);

  if (nullptr != existing_managed_font)
  {
    Internal_SetFakeNamesFromExistingNames(
      existing_managed_font->QuartetName(ON_Font::NameLocale::Localized),
      existing_managed_font->QuartetName(ON_Font::NameLocale::English),
      loc_quartet_name,
      en_quartet_name
    );

    Internal_SetFakeNamesFromExistingNames(
      existing_managed_font->FamilyName(ON_Font::NameLocale::Localized),
      existing_managed_font->FamilyName(ON_Font::NameLocale::English),
      loc_family_name,
      en_family_name
    );

    Internal_SetFakeNamesFromExistingNames(
      existing_managed_font->WindowsLogfontName(ON_Font::NameLocale::Localized),
      existing_managed_font->WindowsLogfontName(ON_Font::NameLocale::English),
      loc_windows_logfont_name,
      en_windows_logfont_name
    );

    fake_font.m_loc_family_name = loc_family_name;
    fake_font.m_en_family_name = en_family_name;

    fake_font.m_loc_face_name = ON_FontFaceQuartet::MemberToString(rich_text_quartet_face);
    fake_font.m_en_face_name = fake_font.m_loc_face_name;

    fake_font.m_loc_windows_logfont_name = loc_windows_logfont_name;
    fake_font.m_en_windows_logfont_name = en_windows_logfont_name;
  }

  // Need to make a fake rich text quartet of managed fonts so rich text 
  // bold and italic faces work as expected.

  // creating a managed fake font resets the fake quartets
  // and this fake will get added to the quartets next time
  // they are needed.
  const ON_Font* managed_fake_font = ON_Font::GetManagedFont(fake_font, true);

  if (nullptr == managed_fake_font)
  {
    // should never happen
    return ON_Font::Default.Internal_DecoratedFont(bUnderlined, bStrikethrough);
  }

  if (managed_fake_font->IsInstalledFont())
  {
    return managed_fake_font->Internal_DecoratedFont(bUnderlined, bStrikethrough);
  }

  // set installed substitute used to render the missing font
  const ON_Font* installed_substitute = managed_fake_font->SubstituteFont();
  if (nullptr == installed_substitute || false == installed_substitute->IsInstalledFont() || rich_text_quartet_face != installed_substitute->m_quartet_member)
  {
    // We have better information to select the correct substitute than inside the ON_Font::GetManagedFont(fake_font, true) call above.
    // Use this information to specify a better substitute font.
    installed_substitute = ON_Font::Default.InstalledFontQuartet().ClosestFace(rich_text_quartet_face); // only look at installed quartet
    if (nullptr == installed_substitute)
      installed_substitute = &ON_Font::Default;
    const bool bInstalledFontIsASubstitute = true;
    ON_Font::Internal_SetManagedFontInstalledFont(
      managed_fake_font,
      installed_substitute,
      bInstalledFontIsASubstitute
    );
  }

  return managed_fake_font->Internal_DecoratedFont(bUnderlined, bStrikethrough);
}

const ON_wString ON_Font::RichTextPropertiesToString(
  bool bRtfBold,
  bool bRtfItalic,
  bool bRtfUnderlined,
  bool bRtfStrikethrough
)
{
  return ON_wString::FormatToString(
    L"%ls%ls%ls",
    (bRtfBold ? (bRtfItalic ? L"Bold Italic" : L"Bold") : (bRtfItalic ? L"Italic" : L"Regular")),
    (bRtfUnderlined ? L" Underlined" : L""),
    (bRtfStrikethrough ? L" Strikethrough" : L"")
  );
}

const ON_wString ON_Font::RichTextPropertiesToString(
  ON_Font::Weight rtf_weight,
  ON_Font::Style rtf_style,
  bool bRtfUnderlined,
  bool bRtfStrikethrough
)
{
  return RichTextPropertiesToString(
    ON_Font::IsBoldWeight(rtf_weight), 
    ON_Font::Style::Italic == rtf_style,
    bRtfUnderlined,
    bRtfStrikethrough
  );
}

const ON_wString ON_Font::RichTextPropertiesToString(
  const ON_Font* font
)
{
  if (font == nullptr)
    font = &ON_Font::Default;
  return RichTextPropertiesToString(
    font->FontWeight(),
    font->FontStyle(),
    font->IsUnderlined(),
    font->IsStrikethrough()
  );
}

const ON_Font* ON_Font::ManagedFontFromRichTextProperties(
  const wchar_t* rtf_font_name,
  bool bRtfBold,
  bool bRtfItalic,
  bool bRftUnderlined,
  bool bRftStrikethrough
)
{
  // ON_Font::ManagedFontFromRichTextProperties() is deprecated.
  // ON_Font::FontFromRichTextProperties() is a single point source for
  // converting rich text font properties into a managed font.
  return ON_Font::FontFromRichTextProperties(rtf_font_name, bRtfBold, bRtfItalic, bRftUnderlined, bRftStrikethrough);
}

const ON_2dex ON_FontList::Internal_SearchSortedList(
  const ON_Font* key,
  ON_FontPtrCompareFunc compare_func,
  const ON_SimpleArray< const ON_Font* >& sorted_font_list
)
{
  for (;;)
  {
    if (nullptr == key || nullptr == compare_func)
      break;
    const int sorted_count = sorted_font_list.Count();
    if (sorted_count <= 0)
      break;
    const int k = sorted_font_list.BinarySearch(&key, compare_func);
    if (k < 0 || k >= sorted_count)
      break;
    int i0 = k;
    while (i0 > 0 && 0 == compare_func(&key, &(sorted_font_list[i0 - 1]) ))
      i0--;
    int i1 = k+1;
    while (i1 < sorted_count && 0 == compare_func(&key, &(sorted_font_list[i1]) ))
      i1++;
    return ON_2dex(i0, i1);
  }

  return ON_2dex(ON_UNSET_INT_INDEX,ON_UNSET_INT_INDEX);

}

void ON_FontList::Internal_EmptyLists()
{
  m_by_index.SetCount(0);
  m_unsorted.SetCount(0);
  m_sorted.m_by_font_characteristics_hash.SetCount(0);
  m_sorted.m_by_postscript_name.SetCount(0);
  m_sorted.m_by_windows_logfont_name.SetCount(0);
  m_sorted.m_by_family_name.SetCount(0);
  m_sorted.m_by_english_postscript_name.SetCount(0);
  m_sorted.m_by_english_windows_logfont_name.SetCount(0);
  m_sorted.m_by_english_family_name.SetCount(0);
  m_sorted.m_by_quartet_name.SetCount(0);
  m_quartet_list.Destroy();
}

static int Internal_CompareLogfontNameEtc(ON_Font const* const* lhs, ON_Font const* const* rhs)
{
  int rc = ON_FontList::CompareWindowsLogfontName(lhs, rhs);
  if (0 != rc)
    return rc;

  rc = ON_FontList::CompareWeightStretchStyle(lhs, rhs);
  if (0 != rc)
    return rc;

  rc = ON_FontList::CompareUnderlinedStrikethroughPointSize(lhs, rhs);
  if (0 != rc)
    return rc;

  rc = ON_FontList::CompareFontCharacteristicsHash(lhs, rhs);
  if (0 != rc)
    return rc;

  return 0;
}

static int Internal_CompareFamilyNameEtc(ON_Font const* const* lhs, ON_Font const* const* rhs)
{
  int rc = ON_FontList::CompareFamilyAndFaceName(lhs, rhs);
  if (0 != rc)
    return rc;

  return Internal_CompareLogfontNameEtc(lhs, rhs);
}

static int Internal_ComparePostScriptNameEtc(ON_Font const* const* lhs, ON_Font const* const* rhs)
{
  int rc = ON_FontList::ComparePostScriptName(lhs, rhs);
  if (0 != rc)
    return rc;

  return Internal_CompareFamilyNameEtc(lhs, rhs);
}


static int Internal_CompareEnglishLogfontNameEtc(ON_Font const* const* lhs, ON_Font const* const* rhs)
{
  int rc = ON_FontList::CompareEnglishWindowsLogfontName(lhs, rhs);
  if (0 != rc)
    return rc;

  rc = ON_FontList::CompareWeightStretchStyle(lhs, rhs);
  if (0 != rc)
    return rc;

  rc = ON_FontList::CompareUnderlinedStrikethroughPointSize(lhs, rhs);
  if (0 != rc)
    return rc;

  return ON_FontList::CompareFontCharacteristicsHash(lhs, rhs);
}

static int Internal_CompareEnglishFamilyNameEtc(ON_Font const* const* lhs, ON_Font const* const* rhs)
{
  int rc = ON_FontList::CompareEnglishFamilyAndFaceName(lhs, rhs);
  if (0 != rc)
    return rc;

  return Internal_CompareEnglishLogfontNameEtc(lhs, rhs);
}

static int Internal_CompareEnglishPostScriptNameEtc(ON_Font const* const* lhs, ON_Font const* const* rhs)
{
  int rc = ON_FontList::CompareEnglishPostScriptName(lhs, rhs);
  if (0 != rc)
    return rc;

  return Internal_CompareEnglishFamilyNameEtc(lhs, rhs);
}


static int Internal_CompareQuartetNameEtc(ON_Font const* const* lhs, ON_Font const* const* rhs)
{
  int rc = ON_FontList::CompareQuartetName(lhs, rhs);
  if (0 != rc)
    return rc;

  rc = ON_FontList::CompareWeightStretchStyle(lhs, rhs);
  if (0 != rc)
    return rc;

  rc = ON_FontList::CompareUnderlinedStrikethroughPointSize(lhs, rhs);
  if (0 != rc)
    return rc;

  return ON_FontList::CompareFontCharacteristicsHash(lhs, rhs);
}


static int Internal_CompareFontCharacteristicsHashEtc(ON_Font const* const* lhs, ON_Font const* const* rhs)
{
  int rc = ON_FontList::CompareFontCharacteristicsHash(lhs, rhs);
  if (0 != rc)
    return rc;

  return Internal_CompareFamilyNameEtc(lhs, rhs);
}

void ON_FontList::Internal_UpdateSortedLists() const
{
  const int unsorted_count = m_unsorted.Count();
  if (unsorted_count <= 0)
    return;

  ON_SimpleArray< const ON_Font* >* sorted_lists[8] =
  {
    &m_sorted.m_by_postscript_name,
    &m_sorted.m_by_windows_logfont_name,
    &m_sorted.m_by_family_name,
    &m_sorted.m_by_english_postscript_name,
    &m_sorted.m_by_english_windows_logfont_name,
    &m_sorted.m_by_english_family_name,
    &m_sorted.m_by_quartet_name,
    &m_sorted.m_by_font_characteristics_hash,
  };

  ON_FontPtrCompareFunc compare_funcs[8] =
  {
    Internal_ComparePostScriptNameEtc,
    Internal_CompareLogfontNameEtc,
    Internal_CompareFamilyNameEtc,

    Internal_CompareEnglishPostScriptNameEtc,
    Internal_CompareEnglishLogfontNameEtc,
    Internal_CompareEnglishFamilyNameEtc,

    Internal_CompareQuartetNameEtc,

    Internal_CompareFontCharacteristicsHashEtc
  };

  const int array_dex_max = (int)(sizeof(sorted_lists) / sizeof(sorted_lists[0]));

  for (int array_dex = 0; array_dex < array_dex_max; array_dex++)
  {
    ON_SimpleArray< const ON_Font* >& sorted_list = *(sorted_lists[array_dex]);

    bool bNeedSort = false;
    sorted_list.Reserve(sorted_list.Count() + unsorted_count);
    for (int j = 0; j < unsorted_count; j++)
    {
      const ON_Font* font = m_unsorted[j];
      if (nullptr == font)
        continue;
      if (0 == array_dex)
      {
        if (font->PostScriptName(m_name_locale).IsEmpty())
          continue;
      }
      else if (1 == array_dex)
      {
        if (font->WindowsLogfontName(m_name_locale).IsEmpty())
          continue;
      }
      else if (2 == array_dex)
      {
        if (font->FamilyName(m_name_locale).IsEmpty())
          continue;
      }
      else if (3 == array_dex)
      {
        const ON_wString en = font->PostScriptName(ON_Font::NameLocale::English);
        if (en.IsEmpty())
          continue;
        if (ON_wString::EqualOrdinal(en, font->PostScriptName(ON_Font::NameLocale::English), true))
          continue;
      }
      else if (4 == array_dex)
      {
        const ON_wString en = font->WindowsLogfontName(ON_Font::NameLocale::English);
        if (en.IsEmpty())
          continue;
        if (ON_wString::EqualOrdinal(en, font->WindowsLogfontName(ON_Font::NameLocale::English), true))
          continue;
      }
      else if (5 == array_dex)
      {
        const ON_wString en = font->FamilyName(ON_Font::NameLocale::English);
        if (en.IsEmpty())
          continue;
        if (ON_wString::EqualOrdinal(en, font->FamilyName(ON_Font::NameLocale::English), true))
          continue;
      }      
      else if (6 == array_dex)
      {
        const ON_wString qname = font->QuartetName();
        if (qname.IsEmpty())
          continue;
        // m_quartet_list[] will get remade when it's needed
        m_quartet_list.SetCount(0);
      }
      else if (7 == array_dex)
      {
        const ON_SHA1_Hash sha1 = font->FontCharacteristicsHash();
        if (sha1.IsZeroDigestOrEmptyContentHash())
          continue; // no valid font wil have either one of these hashes.
      }
      else
      {
        ON_ERROR("When you add an array to ON_FontListImpl, you must add a corresponding if clause here.");
      }

      sorted_list.Append(font);
      bNeedSort = true;
    }

    if ( bNeedSort )
      sorted_list.QuickSort(compare_funcs[array_dex]);
  }

  m_unsorted.SetCount(0);
}

ON_FontList::ON_FontList()
  : m_sorted(*(new ON_FontListImpl()))
{}

ON_FontList::ON_FontList(
  bool bMatchUnderlineAndStrikethrough
)
  : m_bMatchUnderlineStrikethroughAndPointSize(bMatchUnderlineAndStrikethrough)
  , m_sorted(*(new ON_FontListImpl()))
{}

ON_FontList::~ON_FontList()
{
  ON_FontListImpl* ptr = &m_sorted;
  if (nullptr != ptr)
  {
    delete ptr;
  }
}


unsigned int ON_FontList::Count() const
{
  return m_by_index.UnsignedCount();
}

ON_Font::NameLocale ON_FontList::NameLocale() const
{
  return m_name_locale;
}

const ON_Font* ON_FontList::FromFontCharacteristicsHash(
  ON_SHA1_Hash font_characteristics_hash, 
  bool bReturnFirst) const
{
  if (font_characteristics_hash.IsZeroDigestOrEmptyContentHash())
    return nullptr;

  const ON_SimpleArray<const ON_Font*>& by_hash = ByFontCharacteristicsHash();

  // ON_FontList::CompareFontCharacteristicsHash() only looks at m_font_characteristics_hash
  // and m_font_characteristics_hash must not be zero content hash (handled above).
  const ON_Font keyf;
  keyf.m_font_characteristics_hash = font_characteristics_hash;
  const ON_Font* key = &keyf;

  const int i = by_hash.BinarySearch(&key, ON_FontList::CompareFontCharacteristicsHash);
  const int count = by_hash.Count();
  if (i < 0 || i >= count)
    return nullptr;

  int i0 = i;
  while (i0 > 0 && 0 == ON_FontList::CompareFontCharacteristicsHash(&key, &by_hash[i0 - 1]))
    --i0;

  int i1 = i;
  while (i1 + 1 < count && 0 == ON_FontList::CompareFontCharacteristicsHash(&key, &by_hash[i1 + 1]))
    ++i1;
  
  if (i0 == i1)
  {
    // The unique installed font with this hash.
    return by_hash[i0];
  }

  if (bReturnFirst)
  {
    // the first of multiple fonts with this hash.
    return by_hash[i0];
  }

  return nullptr;

}


const ON_Font* ON_FontList::FromPostScriptName(
  const wchar_t* postscript_name
) const
{
  return FromPostScriptName(postscript_name, ON_Font::Weight::Normal, ON_Font::Stretch::Condensed, ON_Font::Style::Upright, false, false);
}
  
const ON_Font* ON_FontList::FromPostScriptName(
  const wchar_t* postscript_name,
  ON_Font::Weight prefered_weight,
  ON_Font::Stretch prefered_stretch,
  ON_Font::Style prefered_style
) const
{
  return FromNames(
    postscript_name,
    nullptr,
    nullptr,
    nullptr,
    prefered_weight,
    prefered_stretch,
    prefered_style,
    false,
    false
  );
}
  
const ON_Font* ON_FontList::FromPostScriptName(
  const wchar_t* postscript_name,
  ON_Font::Weight prefered_weight,
  ON_Font::Stretch prefered_stretch,
  ON_Font::Style prefered_style,
  bool bUnderlined,
  bool bStrikethrough
) const
{
  return FromNames(
    postscript_name,
    nullptr,
    nullptr,
    nullptr,
    prefered_weight,
    prefered_stretch,
    prefered_style,
    false,
    false,
    bUnderlined,
    bStrikethrough,
    0.0
  );
}
  
const ON_Font* ON_FontList::FromWindowsLogfontName(
  const wchar_t* windows_logfont_name
) const
{
  return FromWindowsLogfontName(windows_logfont_name, ON_Font::Weight::Normal, ON_Font::Stretch::Condensed, ON_Font::Style::Upright);
}

const ON_Font* ON_FontList::FromWindowsLogfontName(
  const wchar_t* windows_logfont_name,
  ON_Font::Weight prefered_weight,
  ON_Font::Stretch prefered_stretch,
  ON_Font::Style prefered_style
) const
{
  return FromNames(
    nullptr,
    windows_logfont_name,
    nullptr,
    nullptr,
    prefered_weight,
    prefered_stretch,
    prefered_style,
    false,
    false
  );
}

const ON_Font* ON_FontList::FromWindowsLogfontName(
  const wchar_t* windows_logfont_name,
  ON_Font::Weight prefered_weight,
  ON_Font::Stretch prefered_stretch,
  ON_Font::Style prefered_style,
  bool bUnderlined,
  bool bStrikethrough
) const
{
  return FromNames(
    nullptr,
    windows_logfont_name,
    nullptr,
    nullptr,
    prefered_weight,
    prefered_stretch,
    prefered_style,
    false,
    false,
    bUnderlined,
    bStrikethrough,
    0.0
  );
}
  
const ON_Font* ON_FontList::FromFamilyName(
  const wchar_t* family_name,
  const wchar_t* prefered_face_name
) const
{
  return FromFamilyName(family_name, prefered_face_name, ON_Font::Weight::Normal, ON_Font::Stretch::Medium, ON_Font::Style::Upright);
}
  
const ON_Font* ON_FontList::FromFamilyName(
  const wchar_t* family_name,
  const wchar_t* prefered_face_name,
  ON_Font::Weight prefered_weight,
  ON_Font::Stretch prefered_stretch,
  ON_Font::Style prefered_style
) const
{
  return FromNames(
    nullptr,
    nullptr,
    family_name,
    prefered_face_name,
    prefered_weight,
    prefered_stretch,
    prefered_style,
    false,
    false
  );
}
  
const ON_Font* ON_FontList::FromFamilyName(
  const wchar_t* family_name,
  const wchar_t* prefered_face_name,
  ON_Font::Weight prefered_weight,
  ON_Font::Stretch prefered_stretch,
  ON_Font::Style prefered_style,
  bool bUnderlined,
  bool bStrikethrough
) const
{
  return FromNames(
    nullptr,
    nullptr,
    family_name,
    prefered_face_name,
    prefered_weight,
    prefered_stretch,
    prefered_style,
    false,
    false,
    bUnderlined,
    bStrikethrough,
    0.0
  );
}

const ON_Font* ON_FontList::FromRichTextProperties(
  const wchar_t* rtf_font_name,
  bool bRtfBold,
  bool bRtfItalic,
  bool bUnderlined,
  bool bStrikethrough
) const
{
  // ballpark weight and stretch values. Closest match is returned.
  const ON_Font::Weight prefered_weight = bRtfBold ? ON_Font::Weight::Bold : ON_Font::Weight::Normal;
  const ON_Font::Stretch prefered_stretch = ON_Font::Stretch::Medium;
  const ON_Font::Style prefered_style = bRtfItalic ? ON_Font::Style::Italic : ON_Font::Style::Upright;

  bool bRequireFaceMatch = false;
  bool bRequireStyleMatch = true;

  return FromNames(
    rtf_font_name, // PostScript guess
    rtf_font_name, // Windows LOGFONT.lfFaceName guess
    rtf_font_name, // Family name guess
    nullptr,
    prefered_weight,
    prefered_stretch,
    prefered_style,
    bRequireFaceMatch,
    bRequireStyleMatch,
    bUnderlined,
    bStrikethrough,
    0.0
  );
}

const ON_Font* ON_FontList::FromNames(
  const wchar_t* postscript_name,
  const wchar_t* windows_logfont_name,
  const wchar_t* family_name,
  const wchar_t* prefered_face_name,
  ON_Font::Weight prefered_weight,
  ON_Font::Stretch prefered_stretch,
  ON_Font::Style prefered_style,
  bool bRequireFaceMatch,
  bool bRequireStyleMatch
) const
{
  const bool bMatchUnderlineStrikethroughAndPointSize = false;
  return Internal_FromNames(
    postscript_name,
    windows_logfont_name,
    family_name,
    prefered_face_name,
    prefered_weight,
    prefered_stretch,
    prefered_style,
    bRequireFaceMatch,
    bRequireStyleMatch,
    bMatchUnderlineStrikethroughAndPointSize,
    false,
    false,
    0.0
  );
}

const ON_Font* ON_FontList::FromNames(
  const wchar_t* postscript_name,
  const wchar_t* windows_logfont_name,
  const wchar_t* family_name,
  const wchar_t* prefered_face_name,
  ON_Font::Weight prefered_weight,
  ON_Font::Stretch prefered_stretch,
  ON_Font::Style prefered_style,
  bool bRequireFaceMatch,
  bool bRequireStyleMatch,
  bool bUnderlined,
  bool bStrikethrough,
  double point_size
) const
{
  bool bMatchUnderlineStrikethroughAndPointSize = true;
  return Internal_FromNames(
    postscript_name,
    windows_logfont_name,
    family_name,
    prefered_face_name,
    prefered_weight,
    prefered_stretch,
    prefered_style,
    bRequireFaceMatch,
    bRequireStyleMatch,
    bMatchUnderlineStrikethroughAndPointSize,
    bUnderlined,
    bStrikethrough,
    point_size
  );
}


const ON_Font* ON_FontList::Internal_FromNames(
  const wchar_t* postscript_name,
  const wchar_t* windows_logfont_name,
  const wchar_t* family_name,
  const wchar_t* prefered_face_name,
  ON_Font::Weight prefered_weight,
  ON_Font::Stretch prefered_stretch,
  ON_Font::Style prefered_style,
  bool bRequireFaceMatch,
  bool bRequireStyleMatch,
  bool bMatchUnderlineStrikethroughAndPointSize,
  bool bUnderlined,
  bool bStrikethrough,
  double point_size
) const
{
  if (ON_Font::Stretch::Unset == prefered_stretch)
    bRequireStyleMatch = false;

  if (bUnderlined)
    bUnderlined = true;

  if (bStrikethrough)
    bStrikethrough = true;

  if (!(point_size > 0.0 && point_size < ON_UNSET_POSITIVE_FLOAT))
    point_size = 0.0;

  if (false == m_bMatchUnderlineStrikethroughAndPointSize)
    bMatchUnderlineStrikethroughAndPointSize = false;
  
  const ON_SimpleArray< const ON_Font* > * sorted_lists[16] = {};

  ON_FontPtrCompareFunc compare_funcs[16] = { 0 };

  ON_Font key;

  key.m_loc_postscript_name = postscript_name;
  key.m_loc_postscript_name.TrimLeftAndRight();
  key.m_en_postscript_name = key.m_loc_postscript_name;

  key.m_loc_windows_logfont_name = windows_logfont_name;
  key.m_loc_windows_logfont_name.TrimLeftAndRight();
  key.m_en_windows_logfont_name = key.m_loc_windows_logfont_name;

  key.m_loc_family_name = family_name;
  key.m_loc_family_name.TrimLeftAndRight();
  key.m_en_family_name = key.m_loc_family_name;

  key.m_loc_face_name = prefered_face_name;
  key.m_loc_face_name.TrimLeftAndRight();
  key.m_en_face_name = key.m_loc_face_name;

  key.m_font_weight = prefered_weight;
  key.m_font_stretch = prefered_stretch;
  key.m_font_style = prefered_style;
  
  const bool bKeyHasFamilyAndFace = key.m_loc_family_name.IsNotEmpty() && key.m_loc_face_name.IsNotEmpty();
  const bool bKeyHasPostScriptName = key.m_loc_postscript_name.IsNotEmpty();
  const bool bKeyWindowsLogfontName = key.m_loc_windows_logfont_name.IsNotEmpty();

  if (false == bKeyHasFamilyAndFace)
    bRequireFaceMatch = false;

  int pass_count = 0;

  int postscript_name_pass[2] = { -1, -1 };

  // First compare family AND face name. In general, there will not be multiple
  // fonts with the same family and face name combination.
  if (bKeyHasFamilyAndFace)
  {
    sorted_lists[pass_count] = &m_sorted.m_by_family_name;
    compare_funcs[pass_count] = ON_FontList::CompareFamilyAndFaceName;
    pass_count++;

    sorted_lists[pass_count] = &m_sorted.m_by_english_family_name;
    compare_funcs[pass_count] = ON_FontList::CompareEnglishFamilyAndFaceName;
    pass_count++;
  }

#if defined(ON_RUNTIME_WIN)
  // On Windows, check LOGFONT.lfFaceName before PostScript
  // It is common for 4 distinct faces to have the same LOGFONT lfFaceName.
  if (bKeyWindowsLogfontName)
  {
    sorted_lists[pass_count] = &m_sorted.m_by_windows_logfont_name;
    compare_funcs[pass_count] = ON_FontList::CompareWindowsLogfontName;
    pass_count++;

    sorted_lists[pass_count] = &m_sorted.m_by_english_windows_logfont_name;
    compare_funcs[pass_count] = ON_FontList::CompareEnglishWindowsLogfontName;
    pass_count++;
  }
#endif

  // Check PostScript name
  // On Windows, when simulated fonts or OpenType variable face fonts are in use,
  // it is very common for distict faces to have the same PostScript font name.
  // It is less common in MacOS.
  if (bKeyHasPostScriptName)
  {
    sorted_lists[pass_count] = &m_sorted.m_by_postscript_name;
    compare_funcs[pass_count] = ON_FontList::ComparePostScriptName;
    postscript_name_pass[0] = pass_count;
    pass_count++;

    sorted_lists[pass_count] = &m_sorted.m_by_english_postscript_name;
    compare_funcs[pass_count] = ON_FontList::CompareEnglishPostScriptName;
    postscript_name_pass[1] = pass_count;
    pass_count++;
  }

#if !defined(ON_RUNTIME_WIN)
  // Windows LOGFONT.lfFaceName checked after PostScript
  // It is common for 4 distinct faces to have the same LOGFONT lfFaceName.
  if (bKeyWindowsLogfontName)
  {
    sorted_lists[pass_count] = &m_sorted.m_by_windows_logfont_name;
    compare_funcs[pass_count] = ON_FontList::CompareWindowsLogfontName;
    pass_count++;

    sorted_lists[pass_count] = &m_sorted.m_by_english_windows_logfont_name;
    compare_funcs[pass_count] = ON_FontList::CompareEnglishWindowsLogfontName;
    pass_count++;
  }
#endif

  // The final passes search by Family name.
  // It is generally the case that multiple faces have the same family name.
  if (key.m_loc_family_name.IsNotEmpty())
  {
    sorted_lists[pass_count] = &m_sorted.m_by_family_name;
    compare_funcs[pass_count] = ON_FontList::CompareFamilyName;
    pass_count++;

    sorted_lists[pass_count] = &m_sorted.m_by_english_family_name;
    compare_funcs[pass_count] = ON_FontList::CompareEnglishFamilyName;
    pass_count++;
  }

  if (pass_count <= 0)
    return nullptr;

  // Move any unsorted fonts into the sorted lists.
  Internal_UpdateSortedLists();

  const ON_Font* font = nullptr;
  unsigned int font_dev = 0xFFFFFFFF;

  const ON_Font* pkey = &key;

  const ON_Font* postscript_name_match_candidate = nullptr;

  for (int pass = 0; pass < pass_count; pass++)
  {
    ON_FontPtrCompareFunc compare_func = compare_funcs[pass];
    if (nullptr == compare_func)
      continue;

    const ON_Font* candidate = nullptr;
    unsigned int candidate_dev = 0xFFFFFFFF;

    for (int list_dex = 0; list_dex < 2; list_dex++)
    {
      if (1 == list_dex)
      {
        if (nullptr == sorted_lists[pass])
          continue;
      }

      const ON_SimpleArray< const ON_Font* >& sorted_list 
        = (1==list_dex)
        ? *(sorted_lists[pass])
        : m_unsorted;

      const ON_2dex subset 
        = (1==list_dex)
        ? ON_FontList::Internal_SearchSortedList(&key, compare_func, sorted_list)
        : ON_2dex(0,m_unsorted.Count())
        ;
      if (subset.i < 0 || subset.j <= 0)
        continue;

      for (int i = subset.i; i < subset.j; i++)
      {
        candidate = sorted_list[i];
        if (nullptr == candidate)
          continue;

        if (0 == list_dex)
        {
          if (0 != compare_func(&pkey, &candidate))
            continue;
        }

        // If we're on a Mac, the PostScript name is the most reliable identification
        // and it overrides the subsequent name tests when we have a single installed font that is an exact match.
        const bool bUniquePostScriptNameMatch 
          = (subset.i+1 == subset.j)
          && (pass == postscript_name_pass[0] || pass == postscript_name_pass[1])
          ;
        if (bUniquePostScriptNameMatch)
        {
          if (nullptr == postscript_name_match_candidate)
            postscript_name_match_candidate = candidate;
          else if (postscript_name_match_candidate != candidate)
          {
            // localized and english names produced different candidates.
            postscript_name_match_candidate = nullptr;
          }
        }

        if (bMatchUnderlineStrikethroughAndPointSize)
        {
          if (candidate->IsUnderlined() != bUnderlined)
            continue;
          if (candidate->IsStrikethrough() != bStrikethrough)
            continue;
          if (candidate->PointSize() != point_size)
            continue;
        }
        if (bRequireStyleMatch && prefered_style != candidate->FontStyle())
          continue;
        
        const bool bCandidateFamilyAndFaceMatch 
          = bKeyHasFamilyAndFace
          && (ON_Font::EqualFontFamilyAndFace(&key, candidate) || 0 == ON_FontList::CompareEnglishFamilyAndFaceName(&pkey,&candidate));

        if (bRequireFaceMatch && candidate->FamilyName().IsNotEmpty() && false == bCandidateFamilyAndFaceMatch)
          continue;

        const bool bFontFamilyAndFaceMatch 
          = bKeyHasFamilyAndFace
          && (nullptr != font) 
          && (ON_Font::EqualFontFamilyAndFace(&key, font) || 0 == ON_FontList::CompareEnglishFamilyAndFaceName(&pkey,&candidate));

        if (bFontFamilyAndFaceMatch && false == bCandidateFamilyAndFaceMatch)
          continue;

        candidate_dev = ON_Font::WeightStretchStyleDeviation(prefered_weight, prefered_stretch, prefered_style, candidate);
        // On Apple, we need to try all passes to make sure we check the postscript name.
      // On Apple platforms we have to keep testing
        if (0 == candidate_dev)
        {
#if defined(ON_RUNTIME_APPLE)
          if (postscript_name_match_candidate == candidate)
            return candidate;
#else
          if ( bCandidateFamilyAndFaceMatch || false == bKeyHasFamilyAndFace)
            return candidate;
#endif
        }

        if (
          nullptr == font 
          || (bCandidateFamilyAndFaceMatch && false == bFontFamilyAndFaceMatch)
          || candidate_dev < font_dev
          )
        {
          font = candidate;
          font_dev = candidate_dev;
        }
      }
    }
  }

  if (nullptr != postscript_name_match_candidate && font != postscript_name_match_candidate)
  {
    if (nullptr == font)
    {
      font = postscript_name_match_candidate;
    }
#if defined(ON_RUNTIME_APPLE)
    else
    {
      // ON Apple platforms, the postscript name is the most reliable indentification
      if (false == ON_wString::EqualOrdinal(font->PostScriptName(), postscript_name_match_candidate->PostScriptName(), true))
        font = postscript_name_match_candidate;
    }
#endif
  }

  return font;
}

unsigned int ON_FontList::FontListFromNames(
  const wchar_t* postscript_name,
  const wchar_t* windows_logfont_name,
  const wchar_t* family_name,
  const wchar_t* face_name,
  ON_SimpleArray< const ON_Font* >& font_list
) const
{
  const unsigned int font_list_count0 = font_list.UnsignedCount();

  ON_Font key;

  key.m_loc_postscript_name = postscript_name;
  key.m_loc_postscript_name.TrimLeftAndRight();
  key.m_en_postscript_name = key.m_loc_postscript_name;

  key.m_loc_windows_logfont_name = windows_logfont_name;
  key.m_loc_windows_logfont_name.TrimLeftAndRight();
  key.m_en_windows_logfont_name = key.m_loc_windows_logfont_name;

  key.m_loc_family_name = family_name;
  key.m_loc_family_name.TrimLeftAndRight();
  key.m_en_family_name = key.m_loc_family_name;

  Internal_UpdateSortedLists();

  for (int pass = 0; pass < 3; pass++)
  {
    ON_SimpleArray< const ON_Font* >* sorted_list = nullptr;
    ON_2dex subset(-1, -1);
    switch (pass)
    {
    case 0:
      if (key.m_loc_postscript_name.IsEmpty())
        continue;
      sorted_list = &m_sorted.m_by_postscript_name;
      subset = Internal_SearchSortedList(&key, ON_FontList::ComparePostScriptName, *sorted_list);
      break;

    case 1:
      if (key.m_loc_windows_logfont_name.IsEmpty())
        continue;
      sorted_list = &m_sorted.m_by_windows_logfont_name;
      subset = Internal_SearchSortedList(&key, ON_FontList::CompareWindowsLogfontName, *sorted_list);
      break;

    case 2:
      if (key.m_loc_family_name.IsEmpty())
        continue;
      sorted_list = &m_sorted.m_by_family_name;
      subset = Internal_SearchSortedList(&key, ON_FontList::CompareFamilyName, *sorted_list);
      break;
    }

    if (subset.j <= 0)
      break;

    const ON_Font* pkey = &key;
    for (int i = subset.i; i < subset.j; i++)
    {
      const ON_Font* font = (*sorted_list)[i];
      if (
        pass < 1
        && key.m_loc_windows_logfont_name.IsNotEmpty()
        && 0 != ON_FontList::CompareWindowsLogfontName(&pkey, &font)
        )
        continue;
      if (key.m_loc_family_name.IsNotEmpty())
      {
        if (0 != ON_FontList::CompareFamilyName(&pkey, &font))
          continue;
        if (key.m_loc_face_name.IsNotEmpty()
          && false == ON_wString::EqualOrdinal(key.FaceName(m_name_locale), font->FaceName(m_name_locale), true)
          )
          continue;
      }
      font_list.Append(font);
    }

    break;
  }

  return font_list.UnsignedCount() - font_list_count0;
}

const ON_Font* ON_FontList::FromFontProperties(
  const ON_Font* font_properties,
  bool bRequireFaceMatch,
  bool bRequireStyleMatch
) const
{
  return FromNames(
    font_properties->PostScriptName(m_name_locale),
    font_properties->WindowsLogfontName(m_name_locale),
    font_properties->FamilyName(m_name_locale),
    font_properties->FaceName(m_name_locale),
    font_properties->FontWeight(),
    font_properties->FontStretch(),
    font_properties->FontStyle(),
    bRequireFaceMatch,
    bRequireStyleMatch
  );
}

const ON_Font* ON_FontList::FromFontProperties(
  const ON_Font* font_properties,
  bool bRequireFaceMatch,
  bool bRequireStyleMatch,
  bool bUnderlined,
  bool bStrikethrough,
  double point_size
) const
{
  return FromNames(
    font_properties->PostScriptName(m_name_locale),
    font_properties->WindowsLogfontName(m_name_locale),
    font_properties->FamilyName(m_name_locale),
    font_properties->FaceName(m_name_locale),
    font_properties->FontWeight(),
    font_properties->FontStretch(),
    font_properties->FontStyle(),
    bRequireFaceMatch,
    bRequireStyleMatch,
    bUnderlined,
    bStrikethrough,
    point_size
  );
}

const ON_Font* ON_FontList::FamilyMemberWithWeightStretchStyle(
  const wchar_t* family_name,
  ON_Font::Weight desired_weight,
  ON_Font::Stretch desired_stretch,
  ON_Font::Style desired_style
) const
{
  ON_Font key;
  key.m_loc_family_name = family_name;
  key.m_loc_family_name.TrimLeftAndRight();
  if (key.m_loc_family_name.IsEmpty())
    key.m_loc_family_name = ON_Font::DefaultFamilyName();
  else
    key.m_en_family_name = key.m_loc_family_name;

  key.m_font_weight = desired_weight;
  key.m_font_stretch = desired_stretch;
  key.m_font_style = desired_style;

  const ON_2dex subdex = Internal_SearchSortedList(&key, ON_FontList::CompareFamilyName, m_sorted.m_by_family_name);
  if (subdex.j <= 0)
    return nullptr;
  const ON_Font* candidate = nullptr;
  unsigned int candidate_dev = 0xFFFFFFFF;
  for (int i = subdex.i; i < subdex.j; i++)
  {
    const ON_Font* font = m_sorted.m_by_family_name[i];
    if (nullptr == font)
      continue;
    unsigned int font_dev = ON_Font::WeightStretchStyleDeviation(&key, font);    
    if (nullptr == candidate || font_dev < candidate_dev)
    {
      candidate = font;
      candidate_dev = font_dev;
    }
  }
  return candidate;
}
  
const ON_Font* ON_FontList::FamilyMemberWithWeightStretchStyle(
  const ON_Font* font,
  ON_Font::Weight desired_weight,
  ON_Font::Stretch desired_stretch,
  ON_Font::Style desired_style
) const
{
  if (nullptr == font)
    font = &ON_Font::Default;
  else if ( font->FamilyName().IsEmpty() && font->FaceName().IsEmpty() && font->WindowsLogfontName().IsEmpty() )
    font = &ON_Font::Default;

  if (ON_Font::Weight::Unset == desired_weight)
    desired_weight = font->FontWeight();
  if (ON_Font::Stretch::Unset == desired_stretch)
    desired_stretch = font->FontStretch();
  if (ON_Font::Style::Unset == desired_style)
    desired_style = font->FontStyle();

  ON_wString family_name = font->FamilyName();
  if (family_name.IsEmpty())
  {
    const ON_SimpleArray< const ON_Font* > * sorted_lists[2] = { &m_sorted.m_by_windows_logfont_name, &m_sorted.m_by_postscript_name };
    ON_FontPtrCompareFunc compare_funcs[2] = {ON_FontList::CompareWindowsLogfontName,ON_FontList::ComparePostScriptName};
    const bool bNameIsEmpty[2] = { font->WindowsLogfontName().IsEmpty(),font->PostScriptName().IsEmpty() };
    const int k1 = (int)(sizeof(bNameIsEmpty) / sizeof(bNameIsEmpty[0]));
    for (int k = 0; k < k1 && family_name.IsEmpty(); k++)
    {
      if (bNameIsEmpty[k])
        continue;
      const ON_SimpleArray< const ON_Font* >& sorted_list = *sorted_lists[k];
      const ON_2dex subdex = Internal_SearchSortedList(font, compare_funcs[k], sorted_list);
      if (subdex.j <= 0)
        continue;
      for (int i = subdex.i; i < subdex.j && family_name.IsEmpty(); i++)
      {
        const ON_Font* f = sorted_list[i];
        if (nullptr == f)
          continue;
        family_name = f->FamilyName();
        if (family_name.IsNotEmpty())
          break;
      }
    }
  }

  const ON_Font* family_member = FamilyMemberWithWeightStretchStyle(family_name, desired_weight, desired_stretch, desired_style);
  return family_member;
}

const ON_Font* ON_Font::InstalledFamilyMemberWithWeightStretchStyle(
  ON_Font::Weight desired_weight,
  ON_Font::Stretch desired_stretch,
  ON_Font::Style desired_style
) const
{
  return ON_Font::InstalledFontList().FamilyMemberWithWeightStretchStyle(
    this,
    desired_weight,
    desired_stretch,
    desired_style
  );
}


const ON_Font* ON_Font::ManagedFamilyMemberWithRichTextProperties(
  bool bBold,
  bool bItalic,
  bool bUnderlined,
  bool bStrikethrough
) const
{
  // If this doesn't work, do not add code here.
  // 
  // 1. If there's an obvious bug in ON_Font::ManagedFontFromRichTextProperties(), fix it.
  // 
  // 2. If this is an installed font and the Platform is Mac and you don't like the results,
  // then you probably need to hand tweak the fake Apple quartets we create in 
  // ON_ManagedFonts::Internal_SetFakeWindowsLogfontNames(). That code is Apple specific.
  // 
  // 3. If this is an installed font and the Platform is Windows and you don't like the results,
  // then your input font is probably generating a garbage for this->RichTextFontName() and
  // that issue should be fixed upstream.
  // 
  // 4. Ask Dale Lear for help.
  return ON_Font::FontFromRichTextProperties(this->RichTextFontName(), bBold, bItalic, bUnderlined, bStrikethrough);
}

const ON_Font* ON_Font::ManagedFamilyMemberWithWeightStretchStyle(
  ON_Font::Weight desired_weight,
  ON_Font::Stretch desired_stretch,
  ON_Font::Style desired_style,
  bool bUnderlined, 
  bool bStrikethrough
) const
{
  if (ON_Font::Weight::Unset == desired_weight)
    desired_weight = FontWeight();
  if (ON_Font::Stretch::Unset == desired_stretch)
    desired_stretch = FontStretch();
  if (ON_Font::Style::Unset == desired_style)
    desired_style = FontStyle();

  bool bChangeWeight = (desired_weight != FontWeight());
  bool bChangeStretch = (desired_stretch != FontStretch());
  bool bChangeStyle = (desired_style != FontStyle());
  bool bChangeUnderlined = ((bUnderlined ? true : false) != IsUnderlined());
  bool bChangeStrikethrough = ((bStrikethrough ? true : false) != IsStrikethrough());

  bool bChangeSomething
    = bChangeWeight
    || bChangeStretch
    || bChangeStyle
    || bChangeUnderlined
    || bChangeStrikethrough;

  const ON_Font* font = this;

  if ( bChangeWeight || bChangeStretch || bChangeStyle )
  {
    const ON_Font* installed_font = InstalledFamilyMemberWithWeightStretchStyle(desired_weight, desired_stretch, desired_style);
    if (nullptr != installed_font)
    {
      font = installed_font;
      bChangeWeight = false;
      bChangeStretch = false;
      bChangeStyle = false;
      bChangeUnderlined = (bUnderlined ? true : false) != installed_font->IsUnderlined();
      bChangeStrikethrough = ((bStrikethrough ? true : false) != installed_font->IsStrikethrough());      
      bChangeSomething
        = bChangeWeight
        || bChangeStretch
        || bChangeStyle
        || bChangeUnderlined
        || bChangeStrikethrough;
    }
  }

  if (false == bChangeSomething)
    return font->ManagedFont();

  ON_Font changed_font(*font);

  if (bChangeWeight && ON_Font::Weight::Unset != desired_weight)
    changed_font.SetFontWeight(desired_weight);

  if (bChangeStretch && ON_Font::Stretch::Unset != desired_stretch)
    changed_font.SetFontStretch(desired_stretch);

  if (bChangeStyle && ON_Font::Style::Unset != desired_style)
    changed_font.SetFontStyle(desired_style);

  if (bChangeUnderlined)
    changed_font.SetUnderlined(bUnderlined);

  if (bChangeStrikethrough)
    changed_font.SetStrikethrough(bStrikethrough);

  return changed_font.ManagedFont();
}

const ON_SimpleArray< const class ON_Font* >& ON_FontList::ByPostScriptName() const
{
  Internal_UpdateSortedLists();
  return m_sorted.m_by_postscript_name;
}

const ON_SimpleArray< const class ON_Font* >& ON_FontList::ByWindowsLogfontName() const
{
  Internal_UpdateSortedLists();
  return m_sorted.m_by_windows_logfont_name;
}

const ON_SimpleArray< const class ON_Font* >& ON_FontList::ByFamilyName() const
{
  Internal_UpdateSortedLists();
  return m_sorted.m_by_family_name;
}

const ON_SimpleArray< const class ON_Font* >& ON_FontList::ByQuartetName() const
{
  Internal_UpdateSortedLists();
  return m_sorted.m_by_quartet_name;
}

const ON_SimpleArray< const class ON_Font* >& ON_FontList::ByFontCharacteristicsHash() const
{
  Internal_UpdateSortedLists();
  return m_sorted.m_by_font_characteristics_hash;
}

const ON_SimpleArray< const class ON_Font* >& ON_FontList::ByIndex() const
{
  return m_by_index;
}

// 24 Oct 2022 A. Cormier (RH-64285)
// This functions attempts to find the local name of a font when having the english name.
// A binary search would be better than a for loop but a binary search doesn't work when searching
// for an english  name
static ON_wString ON_FontList__EnNameToLocName(const ON_wString& english_name)
{
  const ON_SimpleArray<const ON_Font*>& fonts = ON_Font::InstalledFontList().ByIndex();
  for (int i = 0; i < fonts.Count(); i++)
  {
    const ON_Font* font = fonts[i];
    if (nullptr == font)
      continue;
    ON_wString en_qname = font->QuartetName(ON_Font::NameLocale::English);
    if (ON_wString::CompareOrdinal(english_name, en_qname, true) == 0)
    {
      return font->QuartetName();
    }
  }
  return ON_wString::EmptyString;
}

const ON_FontFaceQuartet ON_FontList::QuartetFromQuartetName(
  const wchar_t* quartet_name
) const
{
  for (;;)
  {
    ON_FontFaceQuartet qname(quartet_name, nullptr, nullptr, nullptr, nullptr);
    if (qname.QuartetName().IsEmpty())
      break;

    const ON_ClassArray<ON_FontFaceQuartet>& quartet_list = ON_FontList::QuartetList();
    const int quartet_list_count = quartet_list.Count();
    int i = quartet_list.BinarySearch(&qname, ON_FontFaceQuartet::CompareQuartetName);

    bool failedOnFirstTry = i < 0 || i >= quartet_list_count;
    if (failedOnFirstTry)
    {
      //  ... then find the localized name and try again.
      // The QuartetNames in the QuartetList above are localized but sometimes the quartet_name passed to
      // this function is in english. In many cases the localized name and the english name are the same
      // so there is no problem. It is a problem for Japanese and Chinese languages for example. RH-64285
      ON_wString locName = ON_FontList__EnNameToLocName(quartet_name);
      if (locName.IsEmpty())
      {
        break;
      }
      qname = ON_FontFaceQuartet(locName, nullptr, nullptr, nullptr, nullptr);
      i = quartet_list.BinarySearch(&qname, ON_FontFaceQuartet::CompareQuartetName);
      if (i < 0 || i >= quartet_list_count)
      {
        break;
      }
    }

    while (i > 0 && 0 == ON_FontFaceQuartet::CompareQuartetName(&qname, &quartet_list[i - 1]))
      i--;
    return quartet_list[i];
  }
  return ON_FontFaceQuartet::Empty;
}

const ON_Font* ON_FontList::FontFromQuartetProperties(
  const wchar_t* quartet_name,
  bool bBold,
  bool bItalic
) const
{
  const ON_FontFaceQuartet qname(quartet_name, nullptr, nullptr, nullptr, nullptr);
  if (qname.QuartetName().IsEmpty())
    return nullptr;

  const ON_ClassArray< ON_FontFaceQuartet >& quartet_list = ON_FontList::QuartetList();
  const int quartet_list_count = quartet_list.Count();
  int i = quartet_list.BinarySearch(&qname, ON_FontFaceQuartet::CompareQuartetName);
  if (i < 0 || i >= quartet_list_count)
    return nullptr;

  while (i > 0 && 0 == ON_FontFaceQuartet::CompareQuartetName(&qname, &quartet_list[i - 1]))
    i--;
  
  do
  {
    const ON_FontFaceQuartet& q = quartet_list[i];
    if (0 != ON_FontFaceQuartet::CompareQuartetName(&qname, &q))
      break;
    const ON_Font* font = q.Face(bBold, bItalic);
    if (nullptr != font)
      return font;
    i++;
  } while (i < quartet_list_count);

  return nullptr;
}

ON_3udex Internal_StretchSlantWeightDex(unsigned max_stretch_dex, unsigned max_weight_dex, const ON_Font* f)
{
  for (;;)
  {
    if (nullptr == f)
      break;
    const unsigned stretch_dex = static_cast<unsigned char>(f->FontStretch());
    if (stretch_dex < 1 || stretch_dex >= max_stretch_dex)
      break;
    const unsigned slant_dex = (ON_Font::Style::Italic == f->FontStyle() || ON_Font::Style::Oblique == f->FontStyle())
      ? 1U
      : 0U;
    const unsigned weight_dex = static_cast<unsigned char>(f->FontWeight());
    if (weight_dex < 1 || weight_dex >= max_weight_dex)
      break;
    return ON_3udex(stretch_dex, slant_dex, weight_dex);
  }
  return ON_3udex(ON_UNSET_UINT_INDEX, ON_UNSET_UINT_INDEX, ON_UNSET_UINT_INDEX);
}

const ON_ClassArray< ON_FontFaceQuartet >& ON_FontList::QuartetList() const
{
  // call ByQuartetName() first to insure m_quartet_list[] is set correctly.
  const ON_SimpleArray<const ON_Font*>& a = this->ByQuartetName();
  
  if (m_quartet_list.Count() > 0)
    return m_quartet_list;

  const unsigned int font_count = a.UnsignedCount();
  m_quartet_list.Reserve(32 + font_count / 4);

  const ON_Font* f = nullptr;
  const unsigned max_stretch_dex = 10;
  const unsigned max_weight_dex = 10;

  // fonts_by_ssw[stretch_dex][upright,italic][weight_dex]
  // = all fonts with the same quartet name arranged by stretch, slant, and weight.
  const ON_Font* fonts_by_ssw[11][2][11] = {};

  // weight_count[stretch_dex][upright,italic] = number of weights available for that stretch and slant
  unsigned int weight_count[10][2] = {};

  // stretch values range from min stretch = stretch_dex_range[0] to max stretch = stretch_dex_range[1].
  unsigned stretch_dex_range[2] = { 0U,0U };

  // Fonts with stretch < medium_stretch_dex are "compressed"
  // Fonts with stretch > medium_stretch_dex are "expanded"
  // When we have multiple candidates to choose from, we opt for ones closest to medium.
  const unsigned medium_stretch_dex = (unsigned)static_cast<unsigned char>(ON_Font::Stretch::Medium);

  ON_SimpleArray<const ON_Font*> regular_faces(8);
  ON_SimpleArray<const ON_Font*> bold_faces(8);
  ON_SimpleArray<const ON_Font*> italic_faces(8);
  ON_SimpleArray<const ON_Font*> bolditalic_faces(8);

  unsigned next_i = 0U;
  for (unsigned i = 0; i < font_count; i = (i < next_i) ? next_i : (i+1))
  {
    f = a[i];
    if (nullptr == f)
      continue;

    const ON_wString quartet_name = f->QuartetName();
    if (quartet_name.IsEmpty())
      continue;

    // fonts_by_ssw_count = total number of undecorated fonts with the same QuartetName()
    unsigned fonts_by_ssw_count = 0;

    // total number of fonts with underline or striketrough rendering effects enabled.
    unsigned decorated_fonts_count = 0;

    // fonts_by_ssw[][][] = all the "clean" fonts with the same quartet name sorted by stretch-slant-weight
    memset(fonts_by_ssw, 0, sizeof(fonts_by_ssw));
    memset(weight_count, 0, sizeof(weight_count));
    memset(stretch_dex_range, 0, sizeof(stretch_dex_range));
    regular_faces.SetCount(0);
    bold_faces.SetCount(0);
    italic_faces.SetCount(0);
    bolditalic_faces.SetCount(0);

    unsigned int upright_face_count = 0;
    unsigned int slanted_face_count = 0;
    const ON_Font* upright_faces[2] = {}; // room to save up to 2 upright faces
    const ON_Font* slanted_faces[2] = {}; // room to save up to 2 slanted faces

    // This for() loop sets the array limits for the fonts with the same quartet name
    // and determines how many passes are needed (substitutes are ignored in favor of
    // non substitutes).
    unsigned pass_count = 1;
    for (next_i = i; next_i < font_count; ++next_i)
    {
      f = a[next_i];
      if (nullptr == f)
        break;
      if (false == quartet_name.EqualOrdinal(f->QuartetName(), true))
        break; // f has a different quartet name - we're done getting the fonts in this quartet
      if (f->IsManagedSubstitutedFont())
        pass_count = 2;
    }
    
    // This for() loop gets all the fonts with the same QuartetName() and puts them in fonts_by_ssw[][][]. 
    // While doing that it get ranges of values stretch, counts the number of fonts that have each weight, ...
    for ( unsigned pass = 0; pass < pass_count; ++pass) for ( unsigned j = i; j < next_i; ++j)
    {
      f = a[j];
      if (nullptr == f)
        continue;
      if (f->IsUnderlined() || f->IsStrikethrough())
      {
        // these are rendering effects and we should have a "clean" version in this list too
        ++decorated_fonts_count;
        continue; 
      }
      if (pass != (f->IsManagedSubstitutedFont() ? 1U : 0U))
        continue;

      const ON_FontFaceQuartet::Member fm = f->m_quartet_member;

      // use f's stretch-slant-weight to add it to the fonts_by_ssw[][][] array.
      const ON_3udex ssw_dex = Internal_StretchSlantWeightDex(max_stretch_dex, max_weight_dex, f);

      const unsigned stretch_dex = ssw_dex.i;
      if (stretch_dex < 1 || stretch_dex >= max_stretch_dex)
        continue;

      const unsigned slant_dex = ssw_dex.j;

      const unsigned weight_dex = ssw_dex.k;
      if (weight_dex < 1 || weight_dex >= max_weight_dex)
        continue;

      if (nullptr != fonts_by_ssw[stretch_dex][slant_dex][weight_dex])
      {
        // We already found one font with he same quartet name, stretch, slant, and weight.
        // The first one wins and that's why we use two passes when substitute fonts are involved.
        continue;
      }

      ++fonts_by_ssw_count;
      fonts_by_ssw[stretch_dex][slant_dex][weight_dex] = f;

      // add this font's stretch, weight, and slant to the tally for this quartet name.
      if (1 == fonts_by_ssw_count)
      {
        stretch_dex_range[0] = stretch_dex;
        stretch_dex_range[1] = stretch_dex;
      }
      else if (stretch_dex < stretch_dex_range[0])
        stretch_dex_range[0] = stretch_dex;
      else if (stretch_dex > stretch_dex_range[1])
        stretch_dex_range[1] = stretch_dex;

      ++weight_count[stretch_dex][slant_dex];

      if (0 == slant_dex)
      {
        if (upright_face_count < 2)
          upright_faces[upright_face_count] = f;
        ++upright_face_count;
      }
      else if (1 == slant_dex)
      {
        if (slanted_face_count < 2)
          slanted_faces[slanted_face_count] = f;
        ++slanted_face_count;
      }

      // if f's role in the quartet is known, add it to the appropriate x_faces[] array.
      switch (fm)
      {
      case ON_FontFaceQuartet::Member::Regular:
        regular_faces.Append(f);
        break;
      case ON_FontFaceQuartet::Member::Bold:
        bold_faces.Append(f);
        break;
      case ON_FontFaceQuartet::Member::Italic:
        italic_faces.Append(f);
        break;
      case ON_FontFaceQuartet::Member::BoldItalic:
        bolditalic_faces.Append(f);
        break;
      case ON_FontFaceQuartet::Member::Unset:
        break;
      };
    }

    // fonts_by_ssw_count = number of usable fonts with the same quartet name.
    // Pointers to these fonts are someplace in the fonts_by_ssw[][][] array.
    if (0 == fonts_by_ssw_count)
      continue; // nothing usable

    // The goal is to look at the fonts in fonts_by_ssw[][][] and select
    // the best choice for a rich text quartet (which may have 1 to 4 faces).
    const ON_Font* quartet_faces[2][2] = {};
    bool bHaveQuartetFaces = false;

    const unsigned regular_count = regular_faces.UnsignedCount();
    const unsigned bold_count = bold_faces.UnsignedCount();
    const unsigned italic_count = italic_faces.UnsignedCount();
    const unsigned bolditalic_count = bolditalic_faces.UnsignedCount();
    if (
      fonts_by_ssw_count == (regular_count + bold_count + italic_count + bolditalic_count)
      && regular_count <= 1 && bold_count <= 1 && italic_count <= 1 && bolditalic_count <= 1)
    {
      // Best case - every font with this quartet name knows the role it plays in the quartet and there are no contradictions.
      quartet_faces[0][0] = 1 == regular_count ? regular_faces[0] : nullptr;
      quartet_faces[0][1] = 1 == bold_count ? bold_faces[0] : nullptr;
      quartet_faces[1][0] = 1 == italic_count ? italic_faces[0] : nullptr;
      quartet_faces[1][1] = 1 == bolditalic_count ? bolditalic_faces[0] : nullptr;
      bHaveQuartetFaces = true;
    }
    else if (fonts_by_ssw_count == upright_face_count + slanted_face_count
      && upright_face_count <= 2
      && slanted_face_count <= 2
      && stretch_dex_range[0] == stretch_dex_range[1]
      )
    {
      if (2 == upright_face_count && ON_Font::CompareWeight(upright_faces[0]->FontWeight(), upright_faces[1]->FontWeight()) > 0)
      {
        f = upright_faces[0];
        upright_faces[0] = upright_faces[1];
        upright_faces[1] = f;
      }
      if (2 == slanted_face_count && ON_Font::CompareWeight(slanted_faces[0]->FontWeight(), slanted_faces[1]->FontWeight()) > 0)
      {
        f = slanted_faces[0];
        slanted_faces[0] = slanted_faces[1];
        slanted_faces[1] = f;
      }
      quartet_faces[0][0] = upright_faces[0];
      quartet_faces[0][1] = upright_faces[1];
      quartet_faces[1][0] = slanted_faces[0];
      quartet_faces[1][1] = slanted_faces[1];
      bHaveQuartetFaces = true;
    }

    if (false == bHaveQuartetFaces)
    {
      // 1. Most Windows installed fonts have the Windows LOGFONT name reliably set
      // from Windows LOGFONT information when we create installed ON_Fonts from 
      // DirectWrite fonts in opennurbs_win_dwrite.cpp. The Windows LOGFONTs partition
      // families into quartets. These end up with bUsePairCandidate = true.
      // 
      // 2. In rare cases on Windows, font foundaries or authors fail to specify a LOGFONT name
      // in the ttc / ttf / postscript / ... file. 
      // If we are able to make a reasonable guess, then we set the member here.
      // 
      // 3. Apple installed fonts are created from CTFont in opennurbs_apple_nsfont.cpp
      // and the LOGFONT information from ttc / ttf / postscript files cannot be retrieved.
      // There are no Mac OS tools that reliably paritition large font families into
      // quartets.
      // 
      // 4. Missing fonts that are created in ON_Font::FontFromRichTextProperties() have the quartet
      // member set to the specified rich text regular/bold/italic/bold-italic property.
      //
      // Attempt to find something usable in this mess ...

      unsigned stretch_dex = medium_stretch_dex;
      if (stretch_dex_range[0] < stretch_dex_range[1])
      {
        // Need to pick the stretch_dex with the most members.
        // This happens on Mac OS (where no reliable "LOGFONT" name exists) and
        // with damaged Windows fonts that don't have a "LOFGONT" name set.
        // Pick the one closest to ON_Font::Stretch::Medium with the most faces        
        for (unsigned k = 1; k <= medium_stretch_dex; ++k)
        {
          const unsigned k0 = medium_stretch_dex - k;
          const unsigned k1 = medium_stretch_dex + k;
          if (k0 > 0 && (weight_count[k0][0] + weight_count[k0][1]) > (weight_count[stretch_dex][0] + weight_count[stretch_dex][1]))
            stretch_dex = k0;
          if (k1 < max_stretch_dex && (weight_count[k1][0] + weight_count[k1][1]) >(weight_count[stretch_dex][0] + weight_count[stretch_dex][1]))
            stretch_dex = k1;
        }
      }
      else
      {
        stretch_dex = stretch_dex_range[0];
      }
      if (stretch_dex < 1 || stretch_dex >= max_stretch_dex)
        continue;

      if (weight_count[stretch_dex][0] + weight_count[stretch_dex][1] <= 0)
        continue;

      const unsigned normal_weight_dex = (unsigned)static_cast<unsigned char>(ON_Font::Weight::Normal);
      const unsigned medium_weight_dex = (unsigned)static_cast<unsigned char>(ON_Font::Weight::Medium);
      const unsigned bold_weight_dex = (unsigned)static_cast<unsigned char>(ON_Font::Weight::Bold);

      for (unsigned slant_dex = 0; slant_dex < 2; slant_dex++)
      {
        if (weight_count[stretch_dex][slant_dex] <= 2)
        {
          // 0, 1 or 2 available weights.
          // If there is 1 face it must be the "Regular" face.
          // If there are 2 faces, the lightest will be "Regular" and the heaviest will be bold.
          int pair_dex = 0;
          for (int j = 1; j < max_weight_dex && pair_dex < 2; ++j)
          {
            if (nullptr != fonts_by_ssw[stretch_dex][slant_dex][j])
              quartet_faces[slant_dex][pair_dex++] = fonts_by_ssw[stretch_dex][slant_dex][j];
          }
          continue;
        }

        // 3 or more available weights (Bahnshrift, Helvetica Neue, ...)
        unsigned regular_dex
          = (nullptr != fonts_by_ssw[stretch_dex][slant_dex][normal_weight_dex])
          ? normal_weight_dex
          : medium_weight_dex;
        while (nullptr == fonts_by_ssw[stretch_dex][slant_dex][regular_dex] && regular_dex > 0)
          --regular_dex;

        unsigned bold_dex
          = (nullptr != fonts_by_ssw[stretch_dex][slant_dex][bold_weight_dex])
          ? bold_weight_dex
          : regular_dex + 1;
        while (nullptr == fonts_by_ssw[stretch_dex][slant_dex][bold_dex] && bold_dex < max_weight_dex)
          ++bold_dex;

        if (nullptr != fonts_by_ssw[stretch_dex][slant_dex][regular_dex] && nullptr == fonts_by_ssw[stretch_dex][slant_dex][bold_dex])
        {
          if (regular_dex > 0)
          {
            for (unsigned j = regular_dex - 1; j > 0; --j)
            {
              if (nullptr == fonts_by_ssw[stretch_dex][slant_dex][j])
                continue;
              bold_dex = regular_dex;
              regular_dex = j;
              break;
            }
          }
        }
        else if (nullptr == fonts_by_ssw[stretch_dex][slant_dex][regular_dex] && nullptr != fonts_by_ssw[stretch_dex][slant_dex][bold_dex])
        {
          if (bold_dex > 0)
          {
            for (unsigned j = bold_dex - 1; j > 0; --j)
            {
              if (nullptr == fonts_by_ssw[stretch_dex][slant_dex][j])
                continue;
              regular_dex = j;
              break;
            }
          }
        }

        quartet_faces[slant_dex][0] = fonts_by_ssw[stretch_dex][slant_dex][regular_dex];
        quartet_faces[slant_dex][1] = fonts_by_ssw[stretch_dex][slant_dex][bold_dex];
      }
    }

    if (nullptr == quartet_faces[0][0] && nullptr == quartet_faces[0][1])
    {
      // Fonts like Monotype Corsiva have only slanted faces.
      // A quartet name + regular/bold/italic/italic-bold user interface should offer
      // a regular and bold member in this situation.
      quartet_faces[0][0] = quartet_faces[1][0];
      quartet_faces[0][1] = quartet_faces[1][1];
      quartet_faces[1][0] = nullptr;
      quartet_faces[1][1] = nullptr;
    }

    if (nullptr == quartet_faces[0][0] && nullptr == quartet_faces[1][0])
    {
      // This might happen if buggy code encounters a heavy font like Arial Black
      // and incorrectly specifies the heavy regular/italic faces as bold.
      // A quartet name + regular/bold/italic/italic-bold user interface should offer
      // a regular and italic member in this situation.
      quartet_faces[0][0] = quartet_faces[0][1];
      quartet_faces[1][0] = quartet_faces[1][1];
      quartet_faces[0][1] = nullptr;
      quartet_faces[1][1] = nullptr;
    }

    // If ON_Font.m_quartet_member is not set or set incorrectly, 
    // then set it now so we get consistent answers going forward.
    // (Managed quartets are recomputed as new missing fonts are added and in complex cases, the quartet member can change).
    // Installed font quartet members are set once and never change.
    const ON_FontFaceQuartet::Member member[2][2] = {
      {ON_FontFaceQuartet::Member::Regular,ON_FontFaceQuartet::Member::Bold},
      {ON_FontFaceQuartet::Member::Italic,ON_FontFaceQuartet::Member::BoldItalic}
    };
    for (int ii = 0; ii < 2; ++ii) for (int jj = 0; jj < 2; ++jj)
    {
      f = quartet_faces[ii][jj];
      if (nullptr != f)
      {
        const ON_FontFaceQuartet::Member m = f->m_quartet_member;
        if (ON_FontFaceQuartet::Member::Unset == m)
          f->m_quartet_member = member[ii][jj];
        else if (m != member[ii][jj])
        {
          if (ON_Font::FontType::InstalledFont != f->m_font_type)
            quartet_faces[ii][jj]->m_quartet_member = member[ii][jj];
        }
      }
    }

    // Unset the m_quartet_member on unsed fonts with this quartet name.
    for (unsigned j = i; j < next_i; ++j)
    {
      f = a[j];
      if (nullptr == f)
        continue;
      if (f == quartet_faces[0][0] || f == quartet_faces[0][1] || f == quartet_faces[1][0] || f == quartet_faces[1][1])
        continue;
      if (f->IsUnderlined() || f->IsStrikethrough())
        continue; // dealt with below

      const ON_FontFaceQuartet::Member fm = f->m_quartet_member;
      if (ON_FontFaceQuartet::Member::Unset == fm)
        continue;
      if (ON_Font::FontType::InstalledFont != f->m_font_type)
        continue;

      // m_quartet_member incorrectly set. 
      // If you are debugging and this is causing a problem, the bug is not here; 
      // it is in the code above that fills in quartet_faces[][].
      f->m_quartet_member = ON_FontFaceQuartet::Member::Unset;
    }

    if (decorated_fonts_count > 0)
    {
      // This for() loop copies the clean font quartet settings to decorated  (underlined and strikethrough) fonts
      for (unsigned j = i; j < next_i; ++j)
      {
        f = a[j];
        if (nullptr == f)
          continue;
        if (false == f->IsUnderlined() && false == f->IsStrikethrough())
          continue;

        // f is underlined or strikethrough - find the clean version in fonts_by_ssw[][][]
        const ON_3udex ssw_dex = Internal_StretchSlantWeightDex(max_stretch_dex, max_weight_dex, f);
        const ON_Font* cleanf = (
          ssw_dex.i >= 1 && ssw_dex.i < max_stretch_dex
          && ssw_dex.j >= 0 && ssw_dex.j < 2
          && ssw_dex.k >= 1 && ssw_dex.k < max_weight_dex
          )
          ? fonts_by_ssw[ssw_dex.i][ssw_dex.k][ssw_dex.k]
          : nullptr;
        if (nullptr != cleanf)
        {
          const ON_FontFaceQuartet::Member fm = cleanf->m_quartet_member;
          f->m_quartet_member = fm;
        }
      }
    }

    // Now convert managed to installed when that makes sense.
    for (int ii = 0; ii < 2; ++ii) for (int jj = 0; jj < 2; ++jj)
    {
      f = quartet_faces[ii][jj];
      if (nullptr == f)
        continue;
      if (ON_Font::FontType::InstalledFont == f->m_font_type)
        continue;
      if (f->IsManagedSubstitutedFont())
        continue; // common - f is a managed font that is missing from this device.

      if (false == f->IsManagedFont())
        continue; // troubling situation ...
      if (f->IsUnderlined() || f->IsStrikethrough())
        continue; // troubling situation ... 

      // There are 2 lists of fonts.
      // All installed fonts - this list is made once when an application starts.
      // Managed fonts - this list grows as an application needs fonts
      // and is used to handle missing fonts and fonts with effects like underlined and strikethrough.
      // 
      // This is a case where a managed font, like ON_Font::Default, 
      // the default engraving font, 
      // and more complicated cases that arise is rich text parsing, 
      // has an identical font that is installed.
      const ON_Font* installed_font = f->Internal_ManagedFontToInstalledFont();
      if (nullptr == installed_font)
        continue;
      if (false == installed_font->IsInstalledFont())
        continue; // bad mojo happened sometime earlier in the life of this app instance.
      if (false == quartet_name.EqualOrdinal(installed_font->QuartetName(), true))
        continue; // troubling situation ...

      // It is often the case that the installed quartet has faces not in the managed font list.
      // ON_Font::Default is a good example. 
      // If there 
      ON_FontFaceQuartet installed_font_quartet = installed_font->InstalledFontQuartet();
      if (false == quartet_name.EqualOrdinal(installed_font_quartet.QuartetName(), true))
        continue;

      if (installed_font_quartet.HasRegularFace())
        quartet_faces[0][0] = installed_font_quartet.RegularFace();
      if (installed_font_quartet.HasBoldFace())
        quartet_faces[0][1] = installed_font_quartet.BoldFace();
      if (installed_font_quartet.HasItalicFace())
        quartet_faces[1][0] = installed_font_quartet.ItalicFace();
      if (installed_font_quartet.HasBoldItalicFace())
        quartet_faces[1][1] = installed_font_quartet.BoldItalicFace();
    }

    const ON_FontFaceQuartet q(quartet_name, quartet_faces[0][0], quartet_faces[0][1], quartet_faces[1][0], quartet_faces[1][1]);
    if (q.IsEmpty())
      continue;

    m_quartet_list.Append(q);
  }

  return m_quartet_list;
}


unsigned int ON_FontList::AddFont(
  const ON_Font* font,
  bool bCheckforDuplicates
)
{
  if (nullptr == font)
    return false;

  if (
    font->PostScriptName(m_name_locale).IsEmpty()
    && font->WindowsLogfontName(m_name_locale).IsEmpty()
    && font->FamilyName(m_name_locale).IsEmpty()
    )
    return false;

  if (
    ON_Font::Weight::Unset == font->FontWeight()
    || ON_Font::Stretch::Unset == font->FontStretch()
    || ON_Font::Style::Unset == font->FontStyle()
    )
    return false;

  if (bCheckforDuplicates)
  {
    const ON_Font* f = FromFontProperties(font, true, true);
    if (
      nullptr != f
      && f->FontWeight() == font->FontWeight()
      && f->FontStretch() == font->FontStretch()
      && f->FontStyle() == font->FontStyle()
      && f->IsUnderlined() == font->IsUnderlined()
      && f->IsStrikethrough() == font->IsStrikethrough()
      && ON_wString::EqualOrdinal(f->PostScriptName(m_name_locale), font->PostScriptName(m_name_locale), true)
      && ON_wString::EqualOrdinal(f->WindowsLogfontName(m_name_locale), font->WindowsLogfontName(m_name_locale), true)
      && ON_wString::EqualOrdinal(f->FamilyName(m_name_locale), font->FamilyName(m_name_locale), true)
      && ON_wString::EqualOrdinal(f->FaceName(m_name_locale), font->FaceName(m_name_locale), true)
      )
    {
      return false;
    }
  }

  m_by_index.Append(font);

  int count = m_by_index.Count();
  if (count > 1)
  {
    for (int i = count - 2; i <= 0; i--)
    {
      // font = m_by_index[i+1]
      const ON_Font* a = m_by_index[i];
      if (a->RuntimeSerialNumber() <= font->RuntimeSerialNumber())
        break;

      // almost never happens so bubble insertion is ok
      m_by_index[i] = font;
      m_by_index[i + 1] = a;
    }
  }

  m_unsorted.Append(font);
  m_quartet_list.SetCount(0);

  return 1;
}

unsigned int ON_FontList::AddFonts(
  const ON_SimpleArray< const ON_Font* >& fonts
)
{
  const size_t font_count = fonts.UnsignedCount();
  const ON_Font * const * font_list = fonts.Array();
  return AddFonts(font_count,font_list);
}

unsigned int ON_FontList::AddFonts(
  size_t font_count,
  const ON_Font * const * font_list
)
{
  if (nullptr == font_list || font_count <= 0)
    return 0;

  unsigned int rc = 0;
  for (size_t i = 0; i < font_count; i++)
  {
    rc += AddFont(font_list[i],false);
  }
  return rc;
}

const ON_Font* ON_Font::InstalledFont(
  bool bAllowBestMatch
) const
{
  return IsInstalledFont()
    ? this
    : ON_ManagedFonts::InstalledFonts().FromFontProperties(this, !bAllowBestMatch, !bAllowBestMatch);
}

bool ON_Font::IsManagedFont() const
{
  return ( 0 != m_runtime_serial_number );
}

bool ON_Font::IsInstalledFont() const
{
  bool rc;
  switch (m_font_type)
  {
  case ON_Font::FontType::InstalledFont:
    rc = true;
    break;
  case ON_Font::FontType::ManagedFont:
    rc = IsManagedInstalledFont();
    break;
  default:
    rc = false;
    break;
  }
  return rc;
}

bool ON_Font::IsManagedInstalledFont() const
{
  const ON__UINT_PTR bits = 3;
  return IsManagedFont() && (1 == (m_managed_installed_font_and_bits & bits));
}

bool ON_Font::IsManagedSubstitutedFont() const
{
  const ON__UINT_PTR bits = 3;
  return IsManagedFont() && (2 == (m_managed_installed_font_and_bits & bits));
}

void ON_Font::Internal_SetManagedFontInstalledFont(
  const ON_Font* managed_font,
  const ON_Font* installed_font,
  bool bInstalledFontIsASubstitute
)
{
  if (nullptr != managed_font)
  {
    ON__UINT_PTR x = 0;
    if (nullptr != installed_font)
    {
      const ON__UINT_PTR bits = bInstalledFontIsASubstitute ? 2 : 1;
      const ON__UINT_PTR ptr = (ON__UINT_PTR)installed_font;
      x = ptr | bits;
    }
    managed_font->m_managed_installed_font_and_bits = x;
  }
}


const ON_Font* ON_Font::SubstituteFont() const
{
  if (IsManagedSubstitutedFont())
  {
    return Internal_ManagedFontToInstalledFont();
  }
  return nullptr;
}


const ON_Font* ON_Font::Internal_ManagedFontToInstalledFont() const
{
  const ON__UINT_PTR bits = 3;
  ON__UINT_PTR ptr = m_managed_installed_font_and_bits & (~bits);
  return ((const ON_Font*)ptr);
}


const ON_Font* ON_Font::GetManagedFont(
  const wchar_t* face_name
)
{
  return ON_Font::GetManagedFont(0.0, face_name);
}

const ON_Font* ON_Font::GetManagedFont(
  double point_size,
  const wchar_t* face_name
  )
{
  const bool bBold = false;
  const bool bItalic = false;

  return ON_Font::GetManagedFont(
    point_size,
    face_name,
    bBold,
    bItalic
    );
}

const ON_Font* ON_Font::GetManagedFont(
  const wchar_t* face_name,
  bool bBold
)
{
  return ON_Font::GetManagedFont(0.0, face_name, bBold);
}

const ON_Font* ON_Font::GetManagedFont(
  double point_size,
  const wchar_t* face_name,
  bool bBold
  )
{
  const bool bItalic = false;
  return ON_Font::GetManagedFont( point_size, face_name, bBold, bItalic );
}

const ON_Font* ON_Font::GetManagedFont(
  const wchar_t* face_name,
  bool bBold,
  bool bItalic
)
{
  return ON_Font::GetManagedFont(0.0, face_name, bBold, bItalic);
}

const ON_Font* ON_Font::GetManagedFont(
  double point_size,
  const wchar_t* name,
  bool bBold,
  bool bItalic
  )
{
  return ON_Font::GetManagedFont(
    point_size,
    name,
    bBold ? ON_Font::Weight::Bold : ON_Font::Default.FontWeight(),
    bItalic ? ON_Font::Style::Italic : ON_Font::Default.FontStyle()
    );
}

const ON_Font* ON_Font::GetManagedFont(
  const wchar_t* face_name,
  ON_Font::Weight font_weight,
  ON_Font::Style font_style
)
{
  return ON_Font::GetManagedFont(0.0, face_name, font_weight, font_style);
}

const ON_Font* ON_Font::GetManagedFont(
  double point_size,
  const wchar_t* name,
  ON_Font::Weight font_weight,
  ON_Font::Style font_style
  )
{
  // Using ON_Font::InstalledFontFromRichTextProperties() fixes lots 
  // of RTF parsing bugs including RH-49028 and "Arial Black" bugs.
  // Depending on the context, name can be LOGFONT, PostScript, Family+Face, Family, ...
  // The font_weight parameter is typically a "face" indication. 
  // Treating it as a literal value causes more bugs than it fixes.
  const ON_Font* installed_font = ON_Font::InstalledFontFromRichTextProperties(
    name, 
    ON_Font::IsBoldWeight(font_weight), 
    (ON_Font::Style::Italic == font_style)
  );
  if (nullptr != installed_font)
  {
    if (point_size > 0.0 && point_size < ON_Font::AnnotationFontApplePointSize)
    {
      ON_Font f(*installed_font);
      f.m_point_size = point_size;
      return f.ManagedFont();
    }
    return installed_font->ManagedFont();
  }

  // Less reliable approach
  const unsigned int logfont_charset = static_cast<unsigned int>(ON_Font::WindowsLogfontCharSetFromFaceName(name));

  return ON_Font::GetManagedFont(
    point_size,
    name, 
    font_weight,
    font_style,
    ON_Font::Default.m_font_stretch,
    ON_Font::Default.m_font_bUnderlined,
    ON_Font::Default.m_font_bStrikethrough,
    ON_FontMetrics::DefaultLineFeedRatio,
    logfont_charset
    );
}

const ON_Font* ON_Font::GetManagedFont(
  const wchar_t* face_name,
  ON_Font::Weight font_weight,
  ON_Font::Style font_style,
  ON_Font::Stretch font_stretch,
  bool bUnderlined,
  bool bStrikethrough,
  double linefeed_ratio,
  unsigned int logfont_charset
)
{
  return ON_Font::GetManagedFont(
    0.0, // point_size
    face_name,
    font_weight,
    font_style,
    font_stretch,
    bUnderlined,
    bStrikethrough,
    linefeed_ratio,
    logfont_charset
  );
}

const ON_Font* ON_Font::GetManagedFont(
  double point_size,
  const wchar_t* face_name, 
  ON_Font::Weight font_weight,
  ON_Font::Style font_style,
  ON_Font::Stretch font_stretch,
  bool bUnderlined, 
  bool bStrikethrough,
  double linefeed_ratio,
  unsigned int logfont_charset
  )
{
  ON_Font font_characteristics;
  if ( false == font_characteristics.SetFontCharacteristics(
    point_size,
    face_name, 
    font_weight,
    font_style,
    font_stretch,
    bUnderlined, 
    bStrikethrough,
    linefeed_ratio,
    logfont_charset
    ))
    return nullptr;
  return font_characteristics.ManagedFont();
}

#if defined(ON_OS_WINDOWS_GDI)

const ON_Font* ON_Font::GetManagedFontFromWindowsLogfont(
  int map_mode,
  HDC hdc,
  const LOGFONT& logfont
  )
{
  ON_Font font_characteristics;
  if (false == font_characteristics.SetFromWindowsLogFont(map_mode, hdc,logfont))
    return nullptr;
  return font_characteristics.ManagedFont();
}

#endif

const ON_Font* ON_Font::GetManagedFontFromFontDescription(
  const wchar_t* font_description
  )
{
  ON_Font font_characteristics;
  if ( false == font_characteristics.SetFromFontDescription(font_description) )
    return nullptr;
  return font_characteristics.ManagedFont();
}

bool ON_Font::IsNotAppleFontName(
  const wchar_t* font_description
  )
{
  if (nullptr == font_description || 0 == font_description[0])
    return true;
  if ( ON_wString::EqualOrdinal(L"Default",font_description,true) )
    return true;
  // In RH-35535 Marlin reports that Arial is shipped with OS X.
  //if ( ON_wString::EqualOrdinal(L"Arial",font_description,true) )
  //  return true;
  return false;
}

const ON_Font* ON_Font::GetManagedFontFromAppleFontName(
  const char* postscript_name
  )
{
  return ON_Font::GetManagedFontFromPostScriptName(postscript_name);
}

const ON_Font* ON_Font::GetManagedFontFromAppleFontName(
  const wchar_t* postscript_name
  )
{
  return ON_Font::GetManagedFontFromPostScriptName(postscript_name);
}


const ON_Font* ON_Font::GetManagedFontFromPostScriptName(
  const char* postscript_name
  )
{
  const ON_wString wide_string_postscript_name(postscript_name);
  return ON_Font::GetManagedFontFromPostScriptName(wide_string_postscript_name);
}

const ON_Font* ON_Font::GetManagedFontFromPostScriptName(
  const wchar_t* postscript_name
  )
{
  ON_wString buffer(postscript_name);
  buffer.TrimLeftAndRight();
  postscript_name = buffer;
  if (nullptr == postscript_name || 0 == postscript_name[0])
    return &ON_Font::Default;

  const ON_Font* managed_font = ON_Font::ManagedFontList().FromPostScriptName(postscript_name);
  if (nullptr != managed_font)
    return managed_font;

  const ON_Font* installed_font = ON_Font::InstalledFontList().FromPostScriptName(postscript_name);
  if (nullptr != installed_font)
    return installed_font->ManagedFont();

  // This font is not installed.
  ON_Font font(ON_Font::Unset);

  // preferred weight/stretch/style since this font is not installed
  font.SetFontWeight(ON_Font::Weight::Normal);
  font.SetFontStretch(ON_Font::Stretch::Medium);
  font.SetFontStyle(ON_Font::Style::Upright);
  font.m_loc_postscript_name = postscript_name;
  font.m_en_postscript_name = font.m_loc_postscript_name;

  return font.ManagedFont();
}

int ON_Font::WindowsLogfontWeightFromWeight(
  ON_Font::Weight font_weight
  )
{
  int logfont_weight = (int)(100U*static_cast<unsigned int>(font_weight));
  if ( logfont_weight < 50 )
    logfont_weight = 400;
  if ( logfont_weight < 150 )
    logfont_weight = 100;
  else if ( logfont_weight >= 850 )
    logfont_weight = 900;
  else if (0 != logfont_weight % 100)
  {
    int delta = logfont_weight %100;
    if (delta < 50)
      logfont_weight -= delta;
    else
      logfont_weight += (100-delta);
  }
  return logfont_weight;
}

int ON_Font::AppleWeightOfFontFromWeight(
  ON_Font::Weight font_weight
  )
{
  return ON_Font::WindowsLogfontWeightFromWeight(font_weight)/100;
}

double ON_Font::AppleFontWeightTraitFromWeight(
  ON_Font::Weight font_weight
)
{
  // These values are selected to optimize conversion of font weights between Windows and Apple platforms.
  // https://mcneel.myjetbrains.com/youtrack/issue/RH-37075


  const double default_apple_font_weight_trait = 0.0;

  double w = ((double)((int)static_cast<unsigned char>(font_weight)) - 400.0) / 750.0;
  if (w < -1.0)
    w = -1.0;
  else if (w > 1.0)
    w = 1.0;
  if (!(-1.0 <= w && w < 1.0))
    w = default_apple_font_weight_trait;
  
  double apple_font_weight_trait;
  switch (font_weight)
  {
  case ON_Font::Weight::Unset:
    apple_font_weight_trait = default_apple_font_weight_trait;
    break;
  case ON_Font::Weight::Thin:
    apple_font_weight_trait = -0.4;
    break;
  case ON_Font::Weight::Ultralight:
    apple_font_weight_trait = w;
    break;
  case ON_Font::Weight::Light:
    apple_font_weight_trait = w;
    break;
  case ON_Font::Weight::Normal:
    apple_font_weight_trait = 0.0;
    break;
  case ON_Font::Weight::Medium:
    apple_font_weight_trait = w;
    break;
  case ON_Font::Weight::Semibold:
    apple_font_weight_trait = w;
    break;
  case ON_Font::Weight::Bold:
    apple_font_weight_trait = 0.4;
    break;
  case ON_Font::Weight::Ultrabold:
    apple_font_weight_trait = w;
    break;
  case ON_Font::Weight::Heavy:
    apple_font_weight_trait = w;
    break;
  default:
    apple_font_weight_trait = default_apple_font_weight_trait;
    break;
  }

  // The valid value range is from -1.0 to 1.0. The value of 0.0 corresponds to the regular or medium font weight.
  return 
    (-1.0 <= apple_font_weight_trait && apple_font_weight_trait <= 1.0) 
    ? apple_font_weight_trait 
    : default_apple_font_weight_trait;
}

ON_Font::Weight ON_Font::WeightFromWindowsLogfontWeight(
  int windows_logfont_weight
  )
{
  if ( windows_logfont_weight <= 0 || windows_logfont_weight > 1000 )
    return ON_Font::Weight::Normal;

  if ( windows_logfont_weight < 150 )
    return ON_Font::Weight::Thin;

  if ( windows_logfont_weight >= 850 )
    return ON_Font::Weight::Heavy;

  const ON_Font::Weight weights[] = 
  {
    ON_Font::Weight::Thin, // = 1
    ON_Font::Weight::Ultralight, // = 2
    ON_Font::Weight::Light, // = 3
    ON_Font::Weight::Normal, // = 4
    ON_Font::Weight::Medium, // = 5
    ON_Font::Weight::Semibold, // = 6
    ON_Font::Weight::Bold, // = 7
    ON_Font::Weight::Ultrabold, // = 8
    ON_Font::Weight::Heavy, // = 9
  };

  const size_t weight_count = sizeof(weights) / sizeof(weights[0]);
  ON_Font::Weight font_weight = ON_Font::Weight::Normal;
  int delta = std::abs(static_cast<int>(ON_Font::WindowsLogfontWeightFromWeight(font_weight)) - windows_logfont_weight);

  for (size_t i = 0; 0 != delta && i < weight_count; i++)
  {
    // look for a closer match
    int d = std::abs(static_cast<int>(ON_Font::WindowsLogfontWeightFromWeight(weights[i])) - windows_logfont_weight);
    if (d < delta)
    {
      font_weight = weights[i];
      delta = d;
    }
  }

  return font_weight;
}

ON_Font::Weight ON_Font::WeightFromAppleWeightOfFont(
  int apple_weight_of_font
  )
{
  return ON_Font::WeightFromWindowsLogfontWeight(apple_weight_of_font*100);
}

ON_Font::Weight ON_Font::WeightFromAppleFontWeightTrait(
  double apple_font_weight_trait
)
{
  if (false == ON_IsValid(apple_font_weight_trait))
    return ON_Font::Weight::Unset;

  const double x = (-1.0 <= apple_font_weight_trait && apple_font_weight_trait <= 1.0) ? apple_font_weight_trait : 0.0;
  int windows_logfont_weight = (int)(400.0 + 750.0*x);
  if (windows_logfont_weight < 1)
    windows_logfont_weight = 1;
  else if (windows_logfont_weight > 1000)
    windows_logfont_weight = 1000;
  return ON_Font::WeightFromWindowsLogfontWeight(windows_logfont_weight);
}

void ON_Font::Internal_CopyFrom(
    const ON_Font& src
    )
{
  if ( 0 == ((ON__UINT_PTR)(&src)) )
  {
    ON_ERROR("nullptr is target of ON_Font copy ctor or operator=. Crash is imminent or already happened.");
    return;
  }
  
  const bool bThisIsManagedFont = (ON_Font::FontType::ManagedFont == m_font_type);

  if ( bThisIsManagedFont )
  {
    if (0 == m_runtime_serial_number)
    {
      ON_ERROR("Invalid parameters: true == bThisIsManagedFont and 0 == m_runtime_serial_number.");
      return;
    }
  }
  else
  {
    if (0 != m_runtime_serial_number && ON_Font::FontType::ManagedFont != m_font_type)
    {
      ON_ERROR("Invalid parameters: false == bThisIsManagedFont and 0 != m_runtime_serial_number.");
      return;
    }
  }
  
  if ( ((ON__UINT_PTR)(&src)) <= ON_PTR_SEMAPHORE_MAX )
  {
    // If 8 == ((ON__UINT_PTR)(&src)), Initializing ON_Font::Unset (and m_runtime_serial_number is 0 )
    // If 16 == ((ON__UINT_PTR)(&src)), Initializing ON_Font::Default (and m_runtime_serial_number is already set to 1)
    // (Multiples of 8 are used so that runtime pointer alignment checkers don't get alarmed.)
    const bool bDefaultFont = (m_runtime_serial_number > 0);

    m_font_weight  = bDefaultFont ? ON_Font::Weight::Normal  : ON_Font::Weight::Unset;
    m_font_stretch = bDefaultFont ? ON_Font::Stretch::Medium : ON_Font::Stretch::Unset;
    m_font_style   = bDefaultFont ? ON_Font::Style::Upright  : ON_Font::Style::Unset;

    m_loc_family_name = (bDefaultFont ? ON_wString(ON_Font::DefaultFamilyName()) : ON_wString::EmptyString);
    m_en_family_name  = (bDefaultFont ? ON_wString(ON_Font::DefaultFamilyName()) : ON_wString::EmptyString);

    m_loc_face_name   = (bDefaultFont ? ON_wString(ON_Font::DefaultFaceName()) : ON_wString::EmptyString);
    m_en_face_name    = (bDefaultFont ? ON_wString(ON_Font::DefaultFaceName()) : ON_wString::EmptyString);

    m_loc_windows_logfont_name = (bDefaultFont ? ON_wString(ON_Font::DefaultWindowsLogfontName()) : ON_wString::EmptyString);
    m_en_windows_logfont_name = (bDefaultFont ? ON_wString(ON_Font::DefaultWindowsLogfontName()) : ON_wString::EmptyString);

    m_quartet_member = bDefaultFont ? ON_FontFaceQuartet::Member::Regular  : ON_FontFaceQuartet::Member::Unset;

    m_loc_postscript_name = (bDefaultFont ? ON_wString(ON_Font::DefaultPostScriptName()) : ON_wString::EmptyString);
    m_en_postscript_name = (bDefaultFont ? ON_wString(ON_Font::DefaultPostScriptName()) : ON_wString::EmptyString);

    m_font_bUnderlined = false;
    m_font_bStrikethrough = false;

    m_apple_font_weight_trait = 0.0;

    m_windows_logfont_weight = 400;
    m_logfont_charset = ON_Font::WindowsConstants::logfont_default_charset;

    m_point_size = 0.0;

    m_font_origin
      = bDefaultFont
      ? 
#if defined(ON_RUNTIME_WIN)
      ON_Font::Origin::WindowsFont
#elif defined(ON_RUNTIME_APPLE)
      ON_Font::Origin::AppleFont
#else
      ON_Font::Origin::Unknown
#endif
      : ON_Font::Origin::Unset;
    
    const ON_Font* installed_font
      = bDefaultFont
      ? ON_Font::InstalledFontList().FromFontProperties(this, true, true)
      : nullptr;

    if (
      nullptr != installed_font
      && ON_Font::EqualFontFamily(this, installed_font)
      && m_font_style == installed_font->FontStyle()
      )
    {
      if (
        ON_Font::FontType::ManagedFont == this->m_font_type
        && this->m_runtime_serial_number > 0
        && 0 == this->m_managed_installed_font_and_bits)
      {
        // When 1 == m_runtime_serial_number, this font is ON_Font::Default 
        // and its face is installed on this device. Otherwise
        // this is a managed font being created by some other process.
        //
        // See RH-58472 for rare cases when this is required. (A V5 file being read at Rhino startup).
        ON_Font::Internal_SetManagedFontInstalledFont(this, installed_font, false);
      }

      // Set stretch from installed font.
      m_font_stretch = installed_font->FontStretch();

      // want an exact name match
      if ( installed_font->m_loc_postscript_name.IsNotEmpty() )
        m_loc_postscript_name = installed_font->m_loc_postscript_name;
      if ( installed_font->m_en_postscript_name.IsNotEmpty() )
        m_en_postscript_name = installed_font->m_en_postscript_name;

      if ( installed_font->m_loc_family_name.IsNotEmpty() )
        m_loc_family_name = installed_font->m_loc_family_name;
      if ( installed_font->m_en_family_name.IsNotEmpty() )
        m_en_family_name = installed_font->m_en_family_name;

#if defined(ON_RUNTIME_WIN)
      if ( installed_font->m_loc_face_name.IsNotEmpty() )
        m_loc_face_name = installed_font->m_loc_face_name;
      if ( installed_font->m_en_face_name.IsNotEmpty() )
        m_en_face_name = installed_font->m_en_face_name;

      if ( installed_font->m_loc_windows_logfont_name.IsNotEmpty() )
        m_loc_windows_logfont_name = installed_font->m_loc_windows_logfont_name;
      if ( installed_font->m_en_windows_logfont_name.IsNotEmpty() )
        m_en_windows_logfont_name = installed_font->m_en_windows_logfont_name;

      if (m_loc_windows_logfont_name.IsNotEmpty() || m_en_windows_logfont_name.IsNotEmpty())
        m_quartet_member = installed_font->m_quartet_member;
      else
        m_quartet_member = ON_FontFaceQuartet::Member::Unset;

      m_logfont_charset = installed_font->m_logfont_charset;
#endif

      // exact platform weight match
      m_windows_logfont_weight = installed_font->m_windows_logfont_weight;
      m_apple_font_weight_trait = installed_font->m_apple_font_weight_trait;

      m_panose1 = installed_font->m_panose1;

      // share glyph cache
      m_font_glyph_cache = installed_font->m_font_glyph_cache;
    }
  }
  else
  {
    m_font_weight = src.m_font_weight;
    m_windows_logfont_weight = src.m_windows_logfont_weight;
    m_apple_font_weight_trait = src.m_apple_font_weight_trait;

    m_font_style = src.m_font_style;
    m_font_stretch = src.m_font_stretch;
    m_font_bUnderlined = src.m_font_bUnderlined;
    m_font_bStrikethrough = src.m_font_bStrikethrough;
    m_logfont_charset = src.m_logfont_charset;

    m_locale_name = src.m_locale_name;

    m_loc_postscript_name = src.m_loc_postscript_name;
    m_en_postscript_name = src.m_en_postscript_name;

    m_loc_family_name = src.m_loc_family_name;
    m_en_family_name = src.m_en_family_name;

    m_loc_face_name = src.m_loc_face_name;
    m_en_face_name = src.m_en_face_name;

    m_loc_windows_logfont_name = src.m_loc_windows_logfont_name;
    m_en_windows_logfont_name = src.m_en_windows_logfont_name;
    if (m_loc_windows_logfont_name.IsNotEmpty() || m_en_windows_logfont_name.IsNotEmpty())
      m_quartet_member = src.m_quartet_member;
    else
      m_quartet_member = ON_FontFaceQuartet::Member::Unset;


    bool bCopyCache = (0 == m_runtime_serial_number && ON_Font::FontType::Unset == m_font_type);
    if (
      false == bCopyCache
      && ON_Font::FontType::ManagedFont == m_font_type
      && ON_Font::FontType::InstalledFont == src.m_font_type
      && nullptr != src.m_font_glyph_cache.get()
      && nullptr == m_font_glyph_cache.get()
      )
    {
      // destination font is managed and src font is installed
      bCopyCache = true;
    }
    if (bCopyCache)
      m_font_glyph_cache = src.m_font_glyph_cache;

    m_point_size = src.m_point_size;

    m_font_origin = src.m_font_origin;    

    m_panose1 = src.m_panose1;

    m_simulated = src.m_simulated;
  }

  m_font_characteristics_hash = ON_SHA1_Hash::ZeroDigest;

}

ON_Font::ON_Font()
{
  ////const size_t sz = sizeof(*this);
  ////const char* p0 = (const char*)this;
  ////const char* p1 = (const char*)(&this->m_outline_figure_type);
  ////const char* p2 = (const char*)(&this->m_quartet_member);
  ////const char* p3 = (const char*)(&this->m_reserved2);
  ////const char* p4 = (const char*)(this + 1);
  ////const size_t sz1 = (p1 - p0);
  ////const size_t sz2 = (p2 - p0);
  ////const size_t sz3 = (p3 - p0);
  ////const size_t sz4 = (p4 - p0);
  ////if (sz != sz4 || sz1 <= 0 && sz2 <= sz1 && sz3 <= sz4 || sz4 != sz)
  ////  ON_TextLog::Null.PrintNewLine();
  /*
    sz1	144	const unsigned __int64
    sz2	145	const unsigned __int64
    sz3	146	const unsigned __int64
    sz4	192	const unsigned __int64
    sz	192	const unsigned __int64
  */
}

ON_Font::ON_Font(
  ON_Font::FontType font_type,
  const ON_Font& src
  )
  : m_runtime_serial_number(
    (ON_Font::FontType::ManagedFont == font_type)
    ? (++ON_Font::__runtime_serial_number_generator) // only managed fonts have non-zero m_runtime_serial_number
    : 0
  )
  , m_font_type(font_type)
{
  // This is a private constructor used to create managed fonts.
  Internal_CopyFrom(src);
}

ON_Font::ON_Font(const ON_Font& src)
  : m_runtime_serial_number(  (ON_PTR_SEMAPHORE2 == ((ON__UINT_PTR)&src)) ? 1 : 0)
  , m_font_type( (ON_PTR_SEMAPHORE2 == ((ON__UINT_PTR)&src)) ? ON_Font::FontType::ManagedFont : ON_Font::FontType::Unset)
{
  // (ON_PTR_SEMAPHORE1 == ((ON__UINT_PTR)&src)) means we are constructing ON_Font::Unset.
  // (ON_PTR_SEMAPHORE2 == ((ON__UINT_PTR)&src)) means we are constructing ON_Font::Default.
  // Otherwise "this" should be an ordinary and unmanaged font.
  // See opennurbs_statics.cpp and ON_Font::CopyHelper() for more information.
  Internal_CopyFrom(src);
}

ON_Font& ON_Font::operator=(const ON_Font& src)
{
  if (this != &src)
  {
    if (IsManagedFont() )
    {
      // managed fonts can never be modified
      if ( false == ON_Font::EqualFontCharacteristics(*this, src) )
      {
        ON_ERROR("Attempt to modify a managed font");
      }
    }
    else
    {
      Internal_CopyFrom(src);
    }
  }
  return *this;
}


bool ON_Font::SetFontCharacteristics(
  const wchar_t* gdi_logfont_name,
  bool bBold,
  bool bItalic,
  bool bUnderlined,
  bool bStrikethrough
  )
{
  return SetFontCharacteristics(
    0.0,
    gdi_logfont_name,
    bBold,
    bItalic,
    bUnderlined,
    bStrikethrough
  );
}

bool ON_Font::SetFontCharacteristics(
  double point_size,
  const wchar_t * gdi_logfont_name,
  bool bBold,
  bool bItalic, 
  bool bUnderlined,
  bool bStrikethrough
)
{
  if (nullptr == gdi_logfont_name || 0 == gdi_logfont_name[0])
  {
    gdi_logfont_name = ON_Font::Default.m_loc_windows_logfont_name;
  }
  return SetFontCharacteristics(
    point_size,
    gdi_logfont_name,
    (bBold ? ON_Font::Weight::Bold :  ON_Font::Weight::Normal),
    (bItalic ? ON_Font::Style::Italic : ON_Font::Style::Upright),
    ON_Font::Default.m_font_stretch,
    bUnderlined,
    bStrikethrough,
    ON_FontMetrics::DefaultLineFeedRatio,
    ON_Font::WindowsLogfontCharSetFromFaceName(gdi_logfont_name)
    );
}

bool ON_Font::SetFontCharacteristicsForExperts(
  double point_size,
  const ON_wString postscript_name,
  const ON_wString quartet_name,
  ON_FontFaceQuartet::Member quartet_member,
  const ON_wString family_name,
  const ON_wString face_name,
  ON_Font::Weight font_weight,
  ON_Font::Style font_style,
  ON_Font::Stretch font_stretch,
  bool bUnderlined,
  bool bStrikethrough,
  unsigned char logfont_charset,
  int windows_logfont_weight,
  double apple_font_weight_trait,
  ON_PANOSE1 panose1
)
{
  this->m_point_size = point_size;

  this->m_windows_logfont_weight = windows_logfont_weight;
  this->m_apple_font_weight_trait = apple_font_weight_trait;

  this->m_en_windows_logfont_name = quartet_name.Duplicate();
  this->m_en_windows_logfont_name.TrimLeftAndRight();

  this->m_quartet_member = quartet_member;

  this->m_en_postscript_name = postscript_name.Duplicate();
  this->m_en_postscript_name.TrimLeftAndRight();
  this->m_loc_postscript_name = this->m_en_postscript_name;

  this->m_en_family_name = family_name.Duplicate();
  this->m_en_family_name.TrimLeftAndRight();
  this->m_loc_family_name = this->m_en_family_name;

  this->m_en_face_name = face_name.Duplicate();
  this->m_en_face_name.TrimLeftAndRight();
  this->m_loc_face_name = this->m_en_face_name;

  this->m_font_weight = font_weight;
  this->m_font_stretch = font_stretch;
  this->m_font_style = font_style;

  this->m_font_bUnderlined = bUnderlined;
  this->m_font_bStrikethrough = bStrikethrough;

  this->m_logfont_charset = logfont_charset;

  this->m_panose1 = panose1;

  this->m_font_origin = ON_Font::Origin::Unset;
  this->m_simulated = 0;
  this->m_font_characteristics_hash = ON_SHA1_Hash::ZeroDigest;

  return this->IsValid();
}

bool ON_Font::IsValidFaceName(
  const wchar_t* face_name
  )
{
  if ( nullptr == face_name || 0 == face_name[0] || ON_wString::Space == face_name[0])
    return false;
  
  int i = 0;
  while (i < 32 && 0 != face_name[i])
  {
    if (face_name[i] < ON_wString::Space )
      return false;
    switch (face_name[i])
    {
    case ';':
    case '"':
    case '\'':
    case '`':
    case '=':
    case '#':
      // lots more
      return false;
    //case '@': - There are valid fonts like @Gulim with '@' in the name.
    // case '.' - Many apple font names begin with a period
    // case '-' - A hyphen is common in PostScript names
    // case ' ' - A space is common in many names
    default:
      break;
    }
    
    i++;
  }

  if (0 != face_name[i])
    return false;

  return true;
}

ON_Font::Weight ON_Font::FontWeightFromUnsigned(
  unsigned int unsigned_font_weight
  )
{
  switch (unsigned_font_weight)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Weight::Unset);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Weight::Thin);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Weight::Ultralight);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Weight::Light);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Weight::Normal);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Weight::Medium);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Weight::Semibold);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Weight::Bold);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Weight::Ultrabold);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Weight::Heavy);
  default:
    break;
  }
  ON_ERROR("unsigned_font_weight is not valid");
  return ON_Font::Weight::Unset;
}

bool ON_Font::EqualWeightStretchStyle(
  const ON_Font* lhs,
  const ON_Font* rhs,
  bool bUnsetIsEqual
)
{
  return
    ON_Font::EqualWeight(lhs, rhs, bUnsetIsEqual)
    && ON_Font::EqualStretch(lhs, rhs, bUnsetIsEqual)
    && ON_Font::EqualStyle(lhs, rhs, bUnsetIsEqual);
}

bool ON_Font::EqualWeight(
  const ON_Font* lhs,
  const ON_Font* rhs,
  bool bUnsetIsEqual
)
{
  if (nullptr == lhs || nullptr == rhs)
    return false;
  if (lhs->m_font_weight != rhs->m_font_weight)
  {
    if (false == bUnsetIsEqual)
      return false;
    if (ON_Font::Weight::Unset != lhs->m_font_weight && ON_Font::Weight::Unset != rhs->m_font_weight)
      return false;
  }
  return true;
}

bool ON_Font::EqualStretch(
  const ON_Font* lhs,
  const ON_Font* rhs,
  bool bUnsetIsEqual
)
{
  if (nullptr == lhs || nullptr == rhs)
    return false;
  if (lhs->m_font_stretch != rhs->m_font_stretch)
  {
    if (false == bUnsetIsEqual)
      return false;
    if (ON_Font::Stretch::Unset != lhs->m_font_stretch && ON_Font::Stretch::Unset != rhs->m_font_stretch)
      return false;
  }
  return true;
}

bool ON_Font::EqualStyle(
  const ON_Font* lhs,
  const ON_Font* rhs,
  bool bUnsetIsEqual
)
{
  if (nullptr == lhs || nullptr == rhs)
    return false;
  if (lhs->m_font_style != rhs->m_font_style)
  {
    if (false == bUnsetIsEqual)
      return false;
    if (ON_Font::Style::Unset != lhs->m_font_style && ON_Font::Style::Unset != rhs->m_font_style)
      return false;
  }
  return true;
}

int ON_Font::CompareWeight(
  ON_Font::Weight weight_a,
  ON_Font::Weight weight_b
  )
{
  unsigned int a = static_cast<unsigned int>(weight_a);
  unsigned int b = static_cast<unsigned int>(weight_b);
  if ( a < b )
    return -1;
  if ( a < b )
    return 1;
  return 0;
}

ON_Font::Style ON_Font::FontStyleFromUnsigned(
  unsigned int unsigned_font_style
  )
{
  switch (unsigned_font_style)
  {
  ON_ENUM_FROM_UNSIGNED_CASE( ON_Font::Style::Upright);
  ON_ENUM_FROM_UNSIGNED_CASE( ON_Font::Style::Italic);
  ON_ENUM_FROM_UNSIGNED_CASE( ON_Font::Style::Oblique);
  default:
    break;
  }
  ON_ERROR("unsigned_font_style is not valid");
  return ON_Font::Style::Upright;
}

bool ON_Font::IsBoldWeight(
  ON_Font::Weight weight
)
{
  return (static_cast<unsigned int>(weight) >= static_cast<unsigned int>(ON_Font::Weight::Semibold));
}

const wchar_t* ON_Font::WeightToWideString(
  ON_Font::Weight font_weight
)
{
  const wchar_t* s;
  switch (font_weight)
  {
  case ON_Font::Weight::Unset:
    s = L"Unsetweight";
    break;
  case ON_Font::Weight::Thin:
    s = L"Thin";
    break;
  case ON_Font::Weight::Ultralight:
    s = L"Ultralight";
    break;
  case ON_Font::Weight::Light:
    s = L"Light";
    break;
  case ON_Font::Weight::Normal:
    s = L"Normal";
    break;
  case ON_Font::Weight::Medium:
    s = L"Medium";
    break;
  case ON_Font::Weight::Semibold:
    s = L"Semibold";
    break;
  case ON_Font::Weight::Bold:
    s = L"Bold";
    break;
  case ON_Font::Weight::Ultrabold:
    s = L"Ultrabold";
    break;
  case ON_Font::Weight::Heavy:
    s = L"Heavy";
    break;
  default:
    s = L"";
    break;
  }
  return s;
}

const wchar_t* ON_Font::StretchToWideString(
  ON_Font::Stretch font_stretch
)
{
  const wchar_t* s;
  switch (font_stretch)
  {
  case ON_Font::Stretch::Unset:
    s = L"Unsetstretch";
    break;
  case ON_Font::Stretch::Ultracondensed:
    s = L"Ultracondensed";
    break;
  case ON_Font::Stretch::Extracondensed:
    s = L"Extracondensed";
    break;
  case ON_Font::Stretch::Condensed:
    s = L"Condensed";
    break;
  case ON_Font::Stretch::Semicondensed:
    s = L"Semicondensed";
    break;
  case ON_Font::Stretch::Medium:
    s = L"Medium";
    break;
  case ON_Font::Stretch::Semiexpanded:
    s = L"Semiexpanded";
    break;
  case ON_Font::Stretch::Expanded:
    s = L"Expanded";
    break;
  case ON_Font::Stretch::Extraexpanded:
    s = L"Extraexpanded";
    break;
  case ON_Font::Stretch::Ultraexpanded:
    s = L"Ultraexpanded";
    break;
  default:
    s = L"";
    break;
  }
  return s;
}

const wchar_t* ON_Font::StyleToWideString(
  ON_Font::Style font_style
)
{
  const wchar_t* s;
  switch (font_style)
  {
  case ON_Font::Style::Unset:
    s = L"Unsetstyle";
    break;
  case ON_Font::Style::Upright:
    s = L"Upright";
    break;
  case ON_Font::Style::Italic:
    s = L"Italic";
    break;
  case ON_Font::Style::Oblique:
    s = L"Oblique";
    break;
  default:
    s = L"";
    break;
  }
  return s;
}

ON_Font::Stretch ON_Font::FontStretchFromUnsigned(
  unsigned int unsigned_font_stretch
  )
{
  switch (unsigned_font_stretch)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Stretch::Unset);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Stretch::Ultracondensed);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Stretch::Extracondensed);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Stretch::Condensed);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Stretch::Semicondensed);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Stretch::Medium);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Stretch::Semiexpanded);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Stretch::Expanded);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Stretch::Extraexpanded);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Stretch::Ultraexpanded);
  default:
    break;
  }
  ON_ERROR("unsigned_font_stretch is not valid");
  return ON_Font::Stretch::Unset;
}

unsigned int ON_Font::FontCharacteristicsAsUnsigned() const
{
  return ON_Font::Internal_FontCharacteristicsAsUnsigned(
    FontWeight(),
    FontStyle(),
    FontStretch(),
    m_font_bUnderlined,
    m_font_bStrikethrough
    );
}

unsigned int ON_Font::Internal_FontCharacteristicsAsUnsigned(
  ON_Font::Weight font_weight,
  ON_Font::Style font_style,
  ON_Font::Stretch font_stretch,
  bool bUnderlined,
  bool bStrikethrough
  )
{
  unsigned int a[][2]
    = {
      { 2U, 1U }, // insures 0 is not a valid FontCharacteristicsAsUnsigned() value.
      { 10U, static_cast<unsigned int>(font_weight) },
      { 4U, static_cast<unsigned int>(font_style) },
      { 10U, static_cast<unsigned int>(font_stretch) },
      // The static_cast<unsigned int> in b ? 1U : 0U is to work around a CLang compiler bug.
      { 2U, static_cast<unsigned int>(bUnderlined ? 1U : 0U) },
      { 2U, static_cast<unsigned int>(bStrikethrough ? 1U : 0U) }
      // insert new information below this line.
  };

  const int count = (int)(sizeof(a) / sizeof(a[0]));
  int i = count-1;
  unsigned int u = a[i][1] % a[i][0];

  for (i--; i >= 0; i--)
  {
    u = (u * a[i][0]) + (a[i][1] % a[i][0]);
  }

  return u;
}
    
void ON_Font::Internal_GetFontCharacteristicsFromUnsigned(
  unsigned int font_characteristics_as_unsigned,
  ON_Font::Weight& font_weight,
  ON_Font::Stretch& font_stretch,
  ON_Font::Style& font_style,
  bool& bUnderlined,
  bool& bStrikethrough
)
{
  unsigned int u = font_characteristics_as_unsigned;
  const unsigned int u_one = u % 2;
  u /= 2;
  const unsigned int u_font_weight = u % 10;
  u /= 10;
  const unsigned int u_font_style = u % 4;
  u /= 4;
  const unsigned int u_font_stretch = u % 10;
  u /= 10;
  const unsigned int u_bUnderlined = u % 2;
  u /= 2;
  const unsigned int u_bStrikethrough = u % 2;
  u /= 2;
  // extract new information below this line

  font_weight = (1U == u_one && u_font_weight > 0) ? ON_Font::FontWeightFromUnsigned(u_font_weight) : ON_Font::Default.FontWeight();
  font_style = (1U == u_one) ? ON_Font::FontStyleFromUnsigned(u_font_style) : ON_Font::Default.FontStyle();
  font_stretch = (1U == u_one) ? ON_Font::FontStretchFromUnsigned(u_font_stretch) : ON_Font::Default.FontStretch();
  bUnderlined = (1U == u_one) ? (1 == u_bUnderlined) : ON_Font::Default.IsUnderlined();
  bStrikethrough = (1U == u_one) ? (1 == u_bStrikethrough) : ON_Font::Default.IsStrikethrough();
}

bool ON_Font::Internal_SetFontCharacteristicsFromUnsigned(
  unsigned int font_characteristics_as_unsigned
  )
{
  ON_Font::Weight font_weight = ON_Font::Weight::Normal;
  ON_Font::Stretch font_stretch = ON_Font::Stretch::Medium;
  ON_Font::Style font_style = ON_Font::Style::Upright;
  bool bUnderlined = false;
  bool bStrikethrough = false;

  ON_Font::Internal_GetFontCharacteristicsFromUnsigned(
    font_characteristics_as_unsigned,
    font_weight,
    font_stretch,
    font_style,
    bUnderlined,
    bStrikethrough
    );


  const ON_wString windows_logfont_name = WindowsLogfontName();

  bool rc = SetFontCharacteristics(
    windows_logfont_name,
    font_weight,
    font_style,
    font_stretch,
    bUnderlined,
    bStrikethrough
  );

  return rc;
}

unsigned int ON_Font::CRC32(
   bool bIgnoreNameOrdinalCase
  ) const
{
  unsigned int u = FontCharacteristicsAsUnsigned();

  const ON_wString windows_logfont_name = WindowsLogfontName();
  const ON_wString windows_logfont_name_crc
    = bIgnoreNameOrdinalCase
    ? windows_logfont_name.MapStringOrdinal(ON_StringMapOrdinalType::MinimumOrdinal)
    : windows_logfont_name;

  // Should probably include PostScript name as well.

  ON__UINT32 hash = ON_CRC32(0, sizeof(u), &u );
  hash = ON_CRC32(hash,windows_logfont_name_crc.Length()*sizeof(wchar_t),static_cast<const wchar_t*>(windows_logfont_name_crc));

#if defined(ON_RUNTIME_WIN) 
  if ( m_point_size > 0.0 )
    hash = ON_CRC32(hash, sizeof(m_point_size), &m_point_size);
#endif

  return hash;
}

bool ON_Font::SetFontCharacteristics(
  const wchar_t* gdi_logfont_name,
  ON_Font::Weight font_weight,
  ON_Font::Style font_style,
  ON_Font::Stretch font_stretch,
  bool bUnderlined,
  bool bStrikethrough
)
{
  return SetFontCharacteristics(
    0.0,
    gdi_logfont_name,
    font_weight,
    font_style,
    font_stretch,
    bUnderlined,
    bStrikethrough
  );
}

bool ON_Font::SetFontCharacteristics(
  double point_size,
  const wchar_t* gdi_logfont_name,
  ON_Font::Weight font_weight,
  ON_Font::Style font_style,
  ON_Font::Stretch font_stretch,
  bool bUnderlined,
  bool bStrikethrough
  )
{
  const unsigned char logfont_charset = ON_Font::WindowsLogfontCharSetFromFaceName(gdi_logfont_name);

  double linefeed_ratio = ON_FontMetrics::DefaultLineFeedRatio;

  return SetFontCharacteristics(
    point_size,
    gdi_logfont_name,
    font_weight,
    font_style,
    font_stretch,
    bUnderlined,
    bStrikethrough,
    linefeed_ratio,
    logfont_charset
    );
}

bool ON_Font::SetFontCharacteristics(
  const wchar_t* gdi_logfont_name,
  ON_Font::Weight font_weight,
  ON_Font::Style font_style,
  ON_Font::Stretch font_stretch,
  bool bUnderlined,
  bool bStrikethrough,
  double linefeed_ratio,
  unsigned int logfont_charset
)
{
  return SetFontCharacteristics(
    0.0,
    gdi_logfont_name,
    font_weight,
    font_style,
    font_stretch,
    bUnderlined,
    bStrikethrough,
    linefeed_ratio,
    logfont_charset
  );
}

bool ON_Font::SetFontCharacteristics(
  double point_size,
  const wchar_t* gdi_logfont_name,
  ON_Font::Weight font_weight,
  ON_Font::Style font_style,
  ON_Font::Stretch font_stretch,
  bool bUnderlined,
  bool bStrikethrough,
  double linefeed_ratio,
  unsigned int logfont_charset
  )
{
  if ( false == ON_FONT_MODIFICATION_PERMITTED )
    return false;

  // Save face_name - it often points to this->m_face_name
  // and *this = ON_Font::Unset will set this->m_face_name to the empty string.
  ON_wString local_face_name(gdi_logfont_name);
  local_face_name.TrimLeftAndRight();
  gdi_logfont_name = static_cast<const wchar_t*>(local_face_name);

  *this = ON_Font::Unset;

  if (false == ON_Font::IsValidFaceName(gdi_logfont_name))
    return false;

  if (logfont_charset >= 256)
    return false;

  ON_Font new_characteristics(ON_Font::Unset);
  
  new_characteristics.m_loc_windows_logfont_name = gdi_logfont_name;
  new_characteristics.m_en_windows_logfont_name = new_characteristics.m_loc_windows_logfont_name;

  new_characteristics.m_font_weight = ON_Font::FontWeightFromUnsigned(static_cast<unsigned char>(font_weight));
  new_characteristics.m_point_size 
    = (point_size > 0.0 && point_size < 2147483640.0)
    ? point_size
    : 0.0;
  new_characteristics.m_windows_logfont_weight = ON_Font::WindowsLogfontWeightFromWeight(new_characteristics.m_font_weight);
  new_characteristics.m_apple_font_weight_trait = ON_Font::AppleFontWeightTraitFromWeight(new_characteristics.m_font_weight);
  new_characteristics.m_font_style = font_style;
  new_characteristics.m_font_stretch = font_stretch;
  new_characteristics.m_font_bUnderlined = bUnderlined ? true : false;
  new_characteristics.m_font_bStrikethrough = bStrikethrough;

  new_characteristics.m_loc_family_name = ON_Font::FamilyNameFromDirtyName(gdi_logfont_name);
  new_characteristics.m_en_family_name = new_characteristics.m_loc_family_name;

  if (
    ON_wString::EqualOrdinal(L"CityBlueprint", -1, gdi_logfont_name, -1, true)
    || ON_wString::EqualOrdinal(L"CountryBlueprint", -1, gdi_logfont_name, -1, true)
    )
  {
    // These two fonts were distributed with ACAD for decades.
    // Thy have several errors in their definition including being
    // marked as SYMBOL_CHARSET rather than ANSI_CHARSET.
    logfont_charset = ON_Font::WindowsConstants::logfont_symbol_charset;
  }
  else if (ON_Font::logfont_symbol_charset == logfont_charset)
  {
    // verify this is correct.
    logfont_charset = ON_Font::WindowsLogfontCharSetFromFaceName(new_characteristics.WindowsLogfontName());
  }
  else
  {
    logfont_charset = ON_Font::WindowsConstants::logfont_default_charset;
  }

  new_characteristics.m_logfont_charset 
    = (ON_Font::WindowsConstants::logfont_symbol_charset == (unsigned char)logfont_charset)
    ? ON_Font::WindowsConstants::logfont_symbol_charset
    : ON_Font::WindowsConstants::logfont_default_charset;

  if ( 
    // 3 fast checks to avoid time consuming hash calculation
    false == ON_wString::EqualOrdinal(WindowsLogfontName(),new_characteristics.WindowsLogfontName(),false)
    || false == ON_wString::EqualOrdinal(PostScriptName(),new_characteristics.PostScriptName(),false)
    || false == ON_wString::EqualOrdinal(FamilyName(),new_characteristics.FamilyName(),false)
    || false == ON_wString::EqualOrdinal(FaceName(),new_characteristics.FaceName(),false)
    || m_font_weight != new_characteristics.m_font_weight
    || m_font_stretch != new_characteristics.m_font_stretch
    || m_font_style != new_characteristics.m_font_style
    || FontCharacteristicsHash() != new_characteristics.FontCharacteristicsHash() 
    )
  {
    Internal_CopyFrom(new_characteristics);
    if (0 == m_runtime_serial_number)
    {
      // destination font is not managed
      m_font_glyph_cache = nullptr;
    }

    if (
      ON_Font::Stretch::Medium == m_font_stretch
      && (ON_Font::Weight::Normal == m_font_weight || ON_Font::Weight::Bold == m_font_weight)
      && (ON_Font::Style::Upright == m_font_style || ON_Font::Style::Italic == m_font_style)
      )
    {
      const ON_wString logfontName = WindowsLogfontName();
      ON_wString postscript_suffix;
      bool bSetMakePostScriptName = false;
      if (
        ON_wString::EqualOrdinal(L"Arial", logfontName, true)
        )
      {
        // Because Arial is common and its PostScript name has "MT" appended,
        // the post script name is set here so the font will readily work
        // in situation that key off the PostScript name.
        bSetMakePostScriptName = true;
        postscript_suffix = L"MT";
      }
      else if (ON_wString::EqualOrdinal(L"Segoe Print", logfontName, true))
      {
        bSetMakePostScriptName = true;
      }
      else if (ON_wString::EqualOrdinal(L"Segoe Script", logfontName, true))
      {
        bSetMakePostScriptName = true;
      }
      else if (ON_wString::EqualOrdinal(L"Segoe UI", logfontName, true))
      {
        bSetMakePostScriptName = true;
      }
      else if (ON_wString::EqualOrdinal(L"Microsoft YaHei", logfontName, true))
      {
        bSetMakePostScriptName = true;
      }
      else if (ON_wString::EqualOrdinal(L"Microsoft YaHei UI", logfontName, true))
      {
        bSetMakePostScriptName = true;
      }

      for (;;)
      {
        if (false == bSetMakePostScriptName)
          break;

        // The fonts listed above all remove spaces from m_face_name to get
        // the beginning of the postscript name.
        ON_wString postscript_name = logfontName;
        postscript_name.TrimLeftAndRight();
        postscript_name.Remove(ON_wString::Space);
        if (postscript_name.IsEmpty())
          break;
        
        // add -<Weight><Style>
        ON_wString postscript_face;
        if (ON_Font::Weight::Bold == m_font_weight)
          postscript_face += L"Bold";
        if (ON_Font::Style::Italic == m_font_style)
          postscript_face += L"Italic";
        if (postscript_face.IsNotEmpty())
        {
          postscript_name += ON_wString::HyphenMinus;
          postscript_name += postscript_face;
        }

        // Add suffix
        postscript_name += postscript_suffix;

        m_loc_postscript_name = postscript_name;
        m_en_postscript_name = postscript_name;
        break;
      }
    }

    Internal_AfterModification();
  }

  return true;
}



bool ON_Font::SetFromAppleFontName(
  const wchar_t* apple_font_name
)
{
  return SetFromAppleFontName(apple_font_name, 0.0);
}

bool ON_Font::SetFromAppleFontName(
  const wchar_t* apple_font_name,
  double point_size
)
{
  ON_wString local_apple_font_name(apple_font_name);
  local_apple_font_name.TrimLeftAndRight();
  if (local_apple_font_name.IsEmpty())
    return false;

  apple_font_name = static_cast<const wchar_t*>(local_apple_font_name);

  const bool bAnnotationFont
  = ON_Font::IsValidPointSize(point_size) && point_size < ON_Font::AnnotationFontCellHeight
    ? false
    : true;

  bool rc = false;
#if defined (ON_RUNTIME_APPLE_CORE_TEXT_AVAILABLE)
  // If the current computer has the same Apple font, this will return the highest fidelity match.
  bool bIsSubstituteFont = false;
  CTFontRef appleFont = ON_Font::AppleCTFont(apple_font_name,point_size, bIsSubstituteFont);
  if (nullptr != appleFont)
  {
    // In some cases, the NSfont.fontName is different from apple_font_name
    // For example, when apple_font_name = "Arial", NSfont.fontName = "ArialMT".
    const bool b = SetFromAppleCTFont(appleFont, bAnnotationFont);
    CFRelease(appleFont);
    if(b)
      return true;
  }
#endif
  rc = SetFromFontDescription(apple_font_name, apple_font_name);

  if (false == rc)
  {
    // Assume this name is valid but the particular font is not
    // installed on this computer and unconditionally set m_postscript_font_name
    m_loc_postscript_name = local_apple_font_name;
    m_loc_family_name = ON_Font::FamilyNameFromDirtyName(m_loc_postscript_name);

    m_en_postscript_name = m_loc_postscript_name;
    m_en_family_name = m_loc_family_name;
  }
  
  m_point_size
    = bAnnotationFont
    ? 0.0 // indicates annotation font point size on all platforms
    : point_size;

  // Not running on an Apple platform
  Internal_AfterModification();

  return rc;
}

bool Internal_EqualName(
  const ON_wString& lhs,
  const ON_wString& rhs
)
{
  return (lhs.IsNotEmpty() && ON_wString::EqualOrdinal(lhs, rhs, true));
}

bool ON_Font::EqualFontFamily(
  const ON_Font* lhs,
  const ON_Font* rhs
)
{
  if (nullptr == lhs || nullptr == rhs)
    return false;
  if (lhs == rhs)
    return true;

  if (Internal_EqualName(lhs->m_en_family_name, rhs->m_en_family_name))
    return true;
  if (Internal_EqualName(lhs->FamilyName(ON_Font::NameLocale::LocalizedFirst), rhs->FamilyName(ON_Font::NameLocale::LocalizedFirst)))
    return true;
  if (lhs->FaceName().IsNotEmpty() && rhs->FamilyName().IsNotEmpty())
    return false; // both lhs and rhs have non-empty family names.

  // Testing PostScript, and LOGFONT names handles cases where the family name is missing.
  const bool rc
    = Internal_EqualName(lhs->m_en_postscript_name, rhs->m_en_postscript_name)
    || Internal_EqualName(lhs->m_en_windows_logfont_name, rhs->m_en_windows_logfont_name)
    || Internal_EqualName(lhs->PostScriptName(ON_Font::NameLocale::LocalizedFirst),rhs->PostScriptName(ON_Font::NameLocale::LocalizedFirst))
    || Internal_EqualName(lhs->WindowsLogfontName(ON_Font::NameLocale::LocalizedFirst),rhs->WindowsLogfontName(ON_Font::NameLocale::LocalizedFirst))
    ;
  return rc;
}

bool ON_Font::EqualFontFamilyAndFace(
  const ON_Font* lhs,
  const ON_Font* rhs
)
{
  if (nullptr == lhs || nullptr == rhs)
    return false;
  if (lhs == rhs)
    return true;
  
  bool rc = EqualFontFamily(lhs,rhs);
  if (rc)
  {
    rc = Internal_EqualName(lhs->m_en_face_name, rhs->m_en_face_name)
      || Internal_EqualName(lhs->FaceName(ON_Font::NameLocale::LocalizedFirst), rhs->FaceName(ON_Font::NameLocale::LocalizedFirst))
      ;
  }

  return rc;
}

const ON_wString ON_Font::Locale() const
{
  return m_locale_name;
}

const wchar_t* ON_Font::AppleFontNameAsPointer() const
{
  return ON_Font::Internal_GetName(ON_Font::NameLocale::LocalizedFirst, m_loc_postscript_name, m_en_postscript_name).Array();
}

const ON_wString& ON_Font::AppleFontName() const
{
  return
    m_loc_postscript_name.IsNotEmpty()
    ? m_loc_postscript_name
    : m_en_postscript_name;
}

const wchar_t* ON_Font::PostScriptNameAsPointer() const
{
  return ON_Font::Internal_GetName(ON_Font::NameLocale::LocalizedFirst, m_loc_postscript_name, m_en_postscript_name).Array();
}

const ON_wString ON_Font::PostScriptName(ON_Font::NameLocale name_locale) const
{
  return ON_Font::Internal_GetName(name_locale, m_loc_postscript_name, m_en_postscript_name);
}

const ON_wString ON_Font::PostScriptName() const
{
  return ON_Font::Internal_GetName(ON_Font::NameLocale::LocalizedFirst, m_loc_postscript_name, m_en_postscript_name);
}

const ON_wString ON_Font::FamilyName(ON_Font::NameLocale name_locale) const
{
  return ON_Font::Internal_GetName(name_locale, m_loc_family_name, m_en_family_name);
}

const ON_wString ON_Font::FamilyName() const
{
  return FamilyName(ON_Font::NameLocale::LocalizedFirst);
}

const ON_wString ON_Font::FaceName(
  ON_Font::NameLocale name_locale
) const
{
  return ON_Font::Internal_GetName(name_locale, m_loc_face_name, m_en_face_name);
}

const ON_wString ON_Font::FaceName() const
{
  return FaceName(ON_Font::NameLocale::LocalizedFirst);
}

const ON_wString ON_Font::WindowsLogfontName(
  ON_Font::NameLocale name_locale
) const
{
  return ON_Font::Internal_GetName(name_locale, m_loc_windows_logfont_name, m_en_windows_logfont_name);
}

const ON_wString ON_Font::WindowsLogfontName() const
{
  return WindowsLogfontName(ON_Font::NameLocale::LocalizedFirst);
}

class Internal_FakeWindowsLogfontName
{
public:
  ~Internal_FakeWindowsLogfontName() = default;
  Internal_FakeWindowsLogfontName(const Internal_FakeWindowsLogfontName&) = default;
  Internal_FakeWindowsLogfontName() = default;
  Internal_FakeWindowsLogfontName& operator=(const Internal_FakeWindowsLogfontName&) = default;

  Internal_FakeWindowsLogfontName(
    const wchar_t* family_name,
    const wchar_t* postscript_name,
    const wchar_t* fake_logfont_name,
    ON_FontFaceQuartet::Member quartet_member
  )
  : m_fake_logfont_name(fake_logfont_name)
  , m_family_and_postcript_name_hash(Internal_FakeWindowsLogfontName::NameHash(family_name, postscript_name))
  , m_quartet_member(quartet_member)
  // for debugging
  //, m_family_name(family_name)
  //, m_postscript_name(postscript_name)
  {
    m_fake_logfont_name.TrimLeftAndRight();
    if (
      m_fake_logfont_name.EqualOrdinal(family_name, true)
      || (ON_FontFaceQuartet::Member::Unset != quartet_member && m_fake_logfont_name.IsEmpty())
      || m_family_and_postcript_name_hash.IsZeroDigestOrEmptyContentHash()
      )
    {
      ON_ERROR("Invalid input.");
      m_fake_logfont_name = ON_wString::EmptyString;
      m_family_and_postcript_name_hash = ON_SHA1_Hash::EmptyContentHash;
      m_quartet_member = ON_FontFaceQuartet::Member::Unset;
    }
  }

  static const ON_SHA1_Hash NameHash(
    const wchar_t* family_name,
    const wchar_t* postscript_name
  )
  {
    if (nullptr == family_name || 0 == family_name[0])
      return ON_SHA1_Hash::EmptyContentHash;
    if (nullptr == postscript_name || 0 == postscript_name[0])
      return ON_SHA1_Hash::EmptyContentHash;

    ON_wString s1(family_name);
    s1.Remove(ON_wString::Space);
    s1.Remove(ON_wString::HyphenMinus);
    s1.TrimLeftAndRight();
    if (s1.IsEmpty())
      return ON_SHA1_Hash::EmptyContentHash;
        
    ON_wString s2(postscript_name);
    s2.Remove(ON_wString::Space);
    s2.Remove(ON_wString::HyphenMinus);
    s2.TrimLeftAndRight();
    if (s2.IsEmpty())
      return ON_SHA1_Hash::EmptyContentHash;

    // add a hyphen between family and postscript name
    // to insure hash for Family = A and postscript = BC
    // is different from hash for Family = AB and postscript = C
    s1 += ON_wString::HyphenMinus;
    s1 += s2;
       
    return s1.ContentHash(ON_StringMapOrdinalType::MinimumOrdinal);
  }

  static int CompareFamilyAndPostscriptNameHash(
    const Internal_FakeWindowsLogfontName* lhs,
    const Internal_FakeWindowsLogfontName* rhs
    )
  {
    if (lhs == rhs)
      return 0;
    // nulls sort last
    if (nullptr == lhs)
      return 1;
    if (nullptr == rhs)
      return -1;
    return ON_SHA1_Hash::Compare(lhs->m_family_and_postcript_name_hash, rhs->m_family_and_postcript_name_hash);
  }

  const ON_SHA1_Hash QuartetFamilyAndPostscriptNameHash() const
  {
    return m_family_and_postcript_name_hash;
  }
  
  ON_FontFaceQuartet::Member QuartetMember() const
  {
    return m_quartet_member;
  }

  const ON_wString FakeWindowsLogfontName() const
  {
    return m_fake_logfont_name;
  }

private:
  ON_SHA1_Hash m_family_and_postcript_name_hash = ON_SHA1_Hash::EmptyContentHash;
  ON_wString m_fake_logfont_name = ON_wString::EmptyString;
  ON_FontFaceQuartet::Member m_quartet_member = ON_FontFaceQuartet::Member::Unset;

  // for debugging
  //const ON_wString m_family_name = ON_wString::EmptyString;
  //const ON_wString m_postscript_name = ON_wString::EmptyString;
};

const ON_wString ON_Font::FakeWindowsLogfontNameFromFamilyAndPostScriptNames(
  ON_wString family_name,
  ON_wString postscript_name
)
{
  // This function is used to partition Apple fonts into groups with
  // at most 4 faces and assign a face windows logfont name to the group.
  //
  // This is required for archaic font selection interfaces, like ones in Rhino 6 and 7, 
  // that use quartets of regular/italic/bold/bold-italic to specify fonts.
  //
  // Because modern fonts can have many faces (Helvetica Neue has 14 as of 2019)
  // and those faces dont' fit the 1970's LOGFONT model of regular/italic/bold/bold-italic.
  // American Typewriter and Avenir are other example of commonly used fonts that have 
  // more than 4 faces and don't have fit well into the regular/italic/bold/bold-italic UI.
  //
  // It fixes bugs like
  // https://mcneel.myjetbrains.com/youtrack/issue/RH-37074
  // https://mcneel.myjetbrains.com/youtrack/issue/RH-53129
  // https://mcneel.myjetbrains.com/youtrack/issue/RH-53430
  //

  family_name.TrimLeftAndRight();
  postscript_name.TrimLeftAndRight();
  if (family_name.IsEmpty() || postscript_name.IsEmpty())
    return ON_wString::EmptyString;

  static Internal_FakeWindowsLogfontName fake_names[] = 
  {
    // Quartets that need a fake LOGFONT name different from family_name in order to 
    // appear in an archaic quartet name + regular/bold/italic/bold-italic UI
    //
    // Internal_FakeWindowsLogfontName(family_name,postscript_name,fake_logfont_name,member);

    // Combinations that are not explicitly specified are correctly handled by using the family name as the fake logfont name.
    // The explicitly fake logfont name should always be different from the family name.
    Internal_FakeWindowsLogfontName(L"American Typewriter", L"AmericanTypewriter-Light",          L"American Typewriter Light", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"American Typewriter", L"AmericanTypewriter-Semibold",       L"American Typewriter Semibold", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"American Typewriter", L"AmericanTypewriter-CondensedLight", L"American Typewriter Condensed Light", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"American Typewriter", L"AmericanTypewriter-Condensed",      L"American Typewriter Condensed", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"American Typewriter", L"AmericanTypewriter-CondensedBold",  L"American Typewriter Condensed", ON_FontFaceQuartet::Member::Bold),

    Internal_FakeWindowsLogfontName(L"Apple Braille", L"AppleBraille-Outline6Dot",  L"Apple Braille Outline 6 Dot", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Apple Braille", L"AppleBraille-Outline8Dot",  L"Apple Braille Outline 8 Dot", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Apple Braille", L"AppleBraille-Pinpoint6Dot", L"Apple Braille Pinpoint 6 Dot", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Apple Braille", L"AppleBraille-Pinpoint8Dot", L"Apple Braille Pinpoint 8 Dot", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"Apple SD Gothic Neo", L"AppleSDGothicNeo-Thin", L"Apple SD Gothic Neo Thin", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Apple SD Gothic Neo", L"AppleSDGothicNeo-UltraLight", L"Apple SD Gothic Neo Ultralight", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Apple SD Gothic Neo", L"AppleSDGothicNeo-Light", L"Apple SD Gothic Neo Light", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Apple SD Gothic Neo", L"AppleSDGothicNeo-Medium", L"Apple SD Gothic Neo Medium", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Apple SD Gothic Neo", L"AppleSDGothicNeo-SemiBold", L"Apple SD Gothic Neo Semibold", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Apple SD Gothic Neo", L"AppleSDGothicNeo-ExtraBold", L"Apple SD Gothic Neo Extra Bold", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Apple SD Gothic Neo", L"AppleSDGothicNeo-Heavy", L"Apple SD Gothic Neo Heavy", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"Arial Hebrew", L"ArialHebrew-Light", L"Arial Hebrew Light", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"Arial Hebrew Scholar", L"ArialHebrewScholar-Light", L"Arial Hebrew Scholar Light", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"Avenir", L"Avenir-Book",          L"Avenir Book", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Avenir", L"Avenir-BookOblique",   L"Avenir Book", ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Avenir", L"Avenir-Light",         L"Avenir Light", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Avenir", L"Avenir-LightOblique",  L"Avenir Light", ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Avenir", L"Avenir-Medium",        L"Avenir Medium", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Avenir", L"Avenir-MediumOblique", L"Avenir Medium", ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Avenir", L"Avenir-Heavy",         L"Avenir Heavy", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Avenir", L"Avenir-HeavyOblique",  L"Avenir Heavy", ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Avenir", L"Avenir-Black",         L"Avenir Black", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Avenir", L"Avenir-BlackOblique",  L"Avenir-Black", ON_FontFaceQuartet::Member::Italic),

    Internal_FakeWindowsLogfontName(L"Avenir Next", L"AvenirNext-UltraLight", L"Avenir Next Ultralight", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Avenir Next", L"AvenirNext-UltraLightItalic", L"Avenir Next Ultralight", ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Avenir Next", L"AvenirNext-Medium", L"Avenir Next Medium", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Avenir Next", L"AvenirNext-MediumItalic", L"Avenir Next Medium", ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Avenir Next", L"AvenirNext-DemiBold", L"Avenir Next Demibold", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Avenir Next", L"AvenirNext-DemiBoldItalic", L"Avenir Next Demibold", ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Avenir Next", L"AvenirNext-Heavy", L"Avenir Next Heavy", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Avenir Next", L"AvenirNext-HeavyItalic", L"Avenir Next Heavy", ON_FontFaceQuartet::Member::Italic),

    Internal_FakeWindowsLogfontName(L"Avenir Next Condensed", L"AvenirNextCondensed-UltraLight", L"Avenir Next Condensed Ultralight", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Avenir Next Condensed", L"AvenirNextCondensed-UltraLightItalic", L"Avenir Next Condensed Ultralight", ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Avenir Next Condensed", L"AvenirNextCondensed-Medium", L"Avenir Next Condensed Medium", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Avenir Next Condensed", L"AvenirNextCondensed-MediumItalic", L"Avenir Next Condensed Medium", ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Avenir Next Condensed", L"AvenirNextCondensed-DemiBold", L"Avenir Next Condensed Demibold", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Avenir Next Condensed", L"AvenirNextCondensed-DemiBoldItalic", L"Avenir Next Condensed Demibold", ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Avenir Next Condensed", L"AvenirNextCondensed-Heavy", L"Avenir Next Condensed Heavy", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Avenir Next Condensed", L"AvenirNextCondensed-HeavyItalic", L"Avenir Next Condensed Heavy", ON_FontFaceQuartet::Member::Italic),

    Internal_FakeWindowsLogfontName(L"Baskerville", L"Baskerville-SemiBold", L"Baskerville Semibold", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Baskerville", L"Baskerville-SemiBoldItalic", L"Baskerville Semibold", ON_FontFaceQuartet::Member::Italic),

    Internal_FakeWindowsLogfontName(L"Chalkboard SE", L"ChalkboardSE-Light", L"Chalkboard SE Light", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"Charter", L"Charter-Black", L"Charter Black", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Charter", L"Charter-BlackItalic", L"Charter Black", ON_FontFaceQuartet::Member::Italic),

    Internal_FakeWindowsLogfontName(L"Copperplate", L"Copperplate-Light", L"Copperplate Light", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"Damascus", L"DamascusLight", L"Damascus Light", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Damascus", L"DamascusMedium", L"Damascus Medium", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Damascus", L"DamascusSemiBold", L"Damascus Semibold", ON_FontFaceQuartet::Member::Regular),

    // DINPro https://mcneel.myjetbrains.com/youtrack/issue/RH-54627
    // DO NOT try making a fake quartet that combines regular/bold.
    // The last parameter for all DINPro "fake quartets" must be ON_FontFaceQuartet::Member::Regular.
    // When text is created and then later edited the, the Mac RTF used by Eto and the "composed" RTF used by Rhino 
    // are not currently capable looking at the "fake quartet" information and preserving the font. So the Mac users get
    // to see 5 "fake quartets" for DINPro. The "fix" is to return to the Rhino 5 Mac font UI.
    Internal_FakeWindowsLogfontName(L"DINPro", L"DINPro-Regular", L"DINPro Regular", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"DINPro", L"DINPro-Bold",    L"DINPro Bold", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"DINPro", L"DINPro-Light",   L"DINPro Light", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"DINPro", L"DINPro-Medium",  L"DINPro Medium", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"DINPro", L"DINPro-Black",   L"DINPro Black", ON_FontFaceQuartet::Member::Regular),

    // Futura https://mcneel.myjetbrains.com/youtrack/issue/RH-56085
    // DO NOT try making a fake quartet that combines regular/bold.
    // The last parameter for all Futura "fake quartets" must be ON_FontFaceQuartet::Member::Regular.
    // When text is created and then later edited the, the Mac RTF used by Eto and the "composed" RTF used by Rhino 
    // are not currently capable looking at the "fake quartet" information and preserving the font. So the Mac users get
    // to see 5 "fake quartets" for Futura. The "fix" is to return to the Rhino 5 Mac font UI.
    Internal_FakeWindowsLogfontName(L"Futura", L"Futura-Medium",             L"Futura Medium", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Futura", L"Futura-Bold",               L"Futura Bold", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Futura", L"Futura-MediumItalic",       L"Futura Medium Italic", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Futura", L"Futura-CondensedMedium",    L"Futura Condensed Medium", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Futura", L"Futura-CondensedExtraBold", L"Futura Condensed ExtraBold", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"Gill Sans", L"GillSans-Light", L"Gill Sans Light", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Gill Sans", L"GillSans-LightItalic", L"Gill Sans Light", ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Gill Sans", L"GillSans-SemiBold", L"Gill Sans Semibold", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Gill Sans", L"GillSans-SemiBoldItalic", L"Gill Sans Semibold", ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Gill Sans", L"GillSans-UltraBold", L"Gill Sans Ultrabold", ON_FontFaceQuartet::Member::Regular),

    // Gill Sans Std https://mcneel.myjetbrains.com/youtrack/issue/RH-57050
    //  Gill Sans Std is a customize version of Gill Sans that some customer was using.
    //  It is not the Gill Sans that ships with modern versions of Mac OS or Windows.
    //  The next line insures the fake Mac LOGFONT name is the same as the one
    //  Windows uses and insures a file created on Mac/Windows and then read on Windows/Mac 
    //  will have identical Rhino RTF in the .3dm file.
    //  This is a cosmetic change that will reduce confusion when developers are looking
    //  at text that uses this rare font and will feel more comfortable if the name Windows
    //  automatically assigns to the LOGFONT is an exact match with the fake LOGFONT name
    //  used in Mac OS. 
    Internal_FakeWindowsLogfontName(L"Gill Sans Std", L"GillSansStd-Light", L"Gill Sans Std Light", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"Helvetica", L"Helvetica-Light", L"Helvetica Light", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Helvetica", L"Helvetica-LightOblique", L"Helvetica Light", ON_FontFaceQuartet::Member::Italic),

    Internal_FakeWindowsLogfontName(L"Helvetica Neue", L"HelveticaNeue-UltraLight",       L"Helvetica Neue Ultralight", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Helvetica Neue", L"HelveticaNeue-UltraLightItalic", L"Helvetica Neue Ultralight",  ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Helvetica Neue", L"HelveticaNeue-Thin",             L"Helvetica Neue Thin", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Helvetica Neue", L"HelveticaNeue-ThinItalic",       L"Helvetica Neue Thin", ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Helvetica Neue", L"HelveticaNeue-Light",            L"Helvetica Neue Light", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Helvetica Neue", L"HelveticaNeue-LightItalic",      L"Helvetica Neue Light", ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Helvetica Neue", L"HelveticaNeue-Medium",           L"Helvetica Neue Medium", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Helvetica Neue", L"HelveticaNeue-MediumItalic",     L"Helvetica Neue Medium", ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Helvetica Neue", L"HelveticaNeue-CondensedBold",    L"Helvetica Neue Condensed", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Helvetica Neue", L"HelveticaNeue-CondensedBlack",   L"Helvetica Neue Condensed", ON_FontFaceQuartet::Member::Bold),

    Internal_FakeWindowsLogfontName(L"Hiragino Sans", L"HiraginoSans-W3", L"Hiragino Sans W3", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Hiragino Sans", L"HiraginoSans-W6", L"Hiragino Sans W6", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Hiragino Sans", L"HiraginoSans-W0", L"Hiragino Sans W0", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Hiragino Sans", L"HiraginoSans-W1", L"Hiragino Sans W1", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Hiragino Sans", L"HiraginoSans-W2", L"Hiragino Sans W2", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Hiragino Sans", L"HiraginoSans-W4", L"Hiragino Sans W4", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Hiragino Sans", L"HiraginoSans-W5", L"Hiragino Sans W5", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Hiragino Sans", L"HiraginoSans-W7", L"Hiragino Sans W7", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Hiragino Sans", L"HiraginoSans-W8", L"Hiragino Sans W8", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Hiragino Sans", L"HiraginoSans-W9", L"Hiragino Sans W9", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"Hoefler Text", L"HoeflerText-Ornaments", L"Hoefler Text Ornaments", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"ITF Devanagari", L"ITFDevanagari-Light", L"ITF Devanagari Light", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"ITF Devanagari", L"ITFDevanagari-Medium", L"ITF Devanagari Medium", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"ITF Devanagari", L"ITFDevanagari-Demi", L"ITF Devanagari Demibold", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"ITF Devanagari Marathi", L"ITFDevanagariMarathi-Light", L"ITF Devanagari Marathi Light", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"ITF Devanagari Marathi", L"ITFDevanagariMarathi-Medium", L"ITF Devanagari Marathi Medium", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"ITF Devanagari Marathi", L"ITFDevanagariMarathi-Demi", L"ITF Devanagari Marathi Demibold", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"Kohinoor Bangla", L"KohinoorBangla-Light", L"Kohinoor Bangla Light", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Kohinoor Bangla", L"KohinoorBangla-Medium", L"Kohinoor Bangla Medium", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Kohinoor Bangla", L"KohinoorBangla-Semibold", L"Kohinoor Bangla Semibold", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"Kohinoor Devanagari", L"KohinoorDevanagari-Light", L"Kohinoor Devanagari Light", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Kohinoor Devanagari", L"KohinoorDevanagari-Medium", L"Kohinoor Devanagari Medium", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Kohinoor Devanagari", L"KohinoorDevanagari-Semibold", L"Kohinoor Devanagari Semibold", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"Kohinoor Telugu", L"KohinoorTelugu-Light", L"Kohinoor Telugu Light", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Kohinoor Telugu", L"KohinoorTelugu-Medium", L"Kohinoor Telugu Medium", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Kohinoor Telugu", L"KohinoorTelugu-Semibold", L"Kohinoor Telugu Semibold", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"Muna", L"MunaBlack", L"Muna Black", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"Optima", L"Optima-ExtraBlack", L"Optima Black", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"Papyrus", L"Papyrus-Condensed", L"Papyrus Condensed", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"Phosphate", L"Phosphate-Inline", L"Phosphate Inline", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Phosphate", L"Phosphate-Solid", L"Phosphate Solid", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"PingFang HK", L"PingFangHK-Ultralight", L"PingFang HK Ultralight", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"PingFang HK", L"PingFangHK-Thin", L"PingFang HK Thin", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"PingFang HK", L"PingFangHK-Light", L"PingFang HK Light", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"PingFang HK", L"PingFangHK-Medium", L"PingFang HK Medium", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"PingFang SC", L"PingFangSC-Ultralight", L"PingFang SC Ultralight", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"PingFang SC", L"PingFangSC-Thin", L"PingFang SC Thin", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"PingFang SC", L"PingFangSC-Light", L"PingFang SC Light", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"PingFang SC", L"PingFangSC-Medium", L"PingFang SC Medium", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"PingFang TC", L"PingFangTC-Ultralight", L"PingFang TC Ultralight", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"PingFang TC", L"PingFangTC-Thin", L"PingFang TC Thin", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"PingFang TC", L"PingFangTC-Light", L"PingFang TC Light", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"PingFang TC", L"PingFangTC-Medium", L"PingFang TC Medium", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"Skia", L"Skia-Regular_Light", L"Skia Light", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Skia", L"Skia-Regular_Black", L"Skia Black", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Skia", L"Skia-Regular_Condensed", L"Skia Condensed", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Skia", L"Skia-Regular_Black-Condensed", L"Skia Condensed Black", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Skia", L"Skia-Regular_Light-Condensed", L"Skia Condensed Light", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Skia", L"Skia-Regular_Extended", L"Skia Extended", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Skia", L"Skia-Regular_Black-Extended", L"Skia Extended Black", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Skia", L"Skia-Regular_Light-Extended", L"Skia Extended Light", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"Songti SC", L"STSongti-SC-Light", L"Songti SC Light", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Songti SC", L"STSongti-SC-Black", L"Songti SC Black", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"Songti TC", L"STSongti-TC-Light", L"Songti TC Light", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"Sukhumvit Set", L"SukhumvitSet-Light", L"Sukhumvit Set Light", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Sukhumvit Set", L"SukhumvitSet-Medium", L"Sukhumvit Set Medium", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Sukhumvit Set", L"SukhumvitSet-SemiBold", L"Sukhumvit Set Semibold", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Sukhumvit Set", L"SukhumvitSet-Thin", L"Sukhumvit Set Thin", ON_FontFaceQuartet::Member::Regular),

    Internal_FakeWindowsLogfontName(L"Thonburi", L"Thonburi-Light", L"Thonburi Light", ON_FontFaceQuartet::Member::Regular),

    // RH-68433
    Internal_FakeWindowsLogfontName(L"Graphik", L"Graphik-Black",            L"Graphik Black",      ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Graphik", L"Graphik-BlackItalic",      L"Graphik Black",      ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Graphik", L"Graphik-Bold",             L"Graphik Bold",       ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Graphik", L"Graphik-BoldItalic",       L"Graphik Bold",       ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Graphik", L"Graphik-Extralight",       L"Graphik Extralight", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Graphik", L"Graphik-ExtralightItalic", L"Graphik Extralight", ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Graphik", L"Graphik-Light",            L"Graphik Light",      ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Graphik", L"Graphik-LightItalic",      L"Graphik Light",      ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Graphik", L"Graphik-Medium",           L"Graphik Medium",     ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Graphik", L"Graphik-MediumItalic",     L"Graphik Medium",     ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Graphik", L"Graphik-Regular",          L"Graphik Regular",    ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Graphik", L"Graphik-RegularItalic",    L"Graphik Regular",    ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Graphik", L"Graphik-Semibold",         L"Graphik Semibold",   ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Graphik", L"Graphik-SemiboldItalic",   L"Graphik Semibold",   ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Graphik", L"Graphik-Super",            L"Graphik Super",      ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Graphik", L"Graphik-SuperItalic",      L"Graphik Super",      ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Graphik", L"Graphik-Thin",             L"Graphik Thin",       ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Graphik", L"Graphik-ThinItalic",       L"Graphik Thin",       ON_FontFaceQuartet::Member::Italic),

    // RH-68539
    Internal_FakeWindowsLogfontName(L"Neue Haas Grotesk Display Pro", L"NHaasGroteskDSPro-15UltTh",   L"NeueHaasGroteskDisp UltTh", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Neue Haas Grotesk Display Pro", L"NHaasGroteskDSPro-16UltThIt", L"NeueHaasGroteskDisp UltTh", ON_FontFaceQuartet::Member::Italic),

    Internal_FakeWindowsLogfontName(L"Neue Haas Grotesk Display Pro", L"NHaasGroteskDSPro-25Th",      L"NeueHaasGroteskDisp Pro Thin", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Neue Haas Grotesk Display Pro", L"NHaasGroteskDSPro-26ThIt",    L"NeueHaasGroteskDisp Pro Thin", ON_FontFaceQuartet::Member::Italic),

    Internal_FakeWindowsLogfontName(L"Neue Haas Grotesk Display Pro", L"NHaasGroteskDSPro-35XLt",     L"NeueHaasGroteskDisp Pro XLt", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Neue Haas Grotesk Display Pro", L"NHaasGroteskDSPro-36XLtIt",   L"NeueHaasGroteskDisp Pro XLt", ON_FontFaceQuartet::Member::Italic),

    Internal_FakeWindowsLogfontName(L"Neue Haas Grotesk Display Pro", L"NHaasGroteskDSPro-45Lt",      L"NeueHaasGroteskDisp Pro Lt", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Neue Haas Grotesk Display Pro", L"NHaasGroteskDSPro-46LtIt",    L"NeueHaasGroteskDisp Pro Lt", ON_FontFaceQuartet::Member::Italic),

    Internal_FakeWindowsLogfontName(L"Neue Haas Grotesk Display Pro", L"NHaasGroteskDSPro-55Rg",      L"NeueHaasGroteskDisp Pro", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Neue Haas Grotesk Display Pro", L"NHaasGroteskDSPro-56It",      L"NeueHaasGroteskDisp Pro", ON_FontFaceQuartet::Member::Italic),
    Internal_FakeWindowsLogfontName(L"Neue Haas Grotesk Display Pro", L"NHaasGroteskDSPro-75Bd",      L"NeueHaasGroteskDisp Pro", ON_FontFaceQuartet::Member::Bold),
    Internal_FakeWindowsLogfontName(L"Neue Haas Grotesk Display Pro", L"NHaasGroteskDSPro-76BdIt",    L"NeueHaasGroteskDisp Pro", ON_FontFaceQuartet::Member::BoldItalic),

    Internal_FakeWindowsLogfontName(L"Neue Haas Grotesk Display Pro", L"NHaasGroteskDSPro-65Md",      L"NeueHaasGroteskDisp Pro Md", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Neue Haas Grotesk Display Pro", L"NHaasGroteskDSPro-66MdIt",    L"NeueHaasGroteskDisp Pro Md", ON_FontFaceQuartet::Member::Italic),

    Internal_FakeWindowsLogfontName(L"Neue Haas Grotesk Display Pro", L"NHaasGroteskDSPro-95Blk",     L"NeueHaasGroteskDisp Pro Blk", ON_FontFaceQuartet::Member::Regular),
    Internal_FakeWindowsLogfontName(L"Neue Haas Grotesk Display Pro", L"NHaasGroteskDSPro-96BlkIt",   L"NeueHaasGroteskDisp Pro Blk", ON_FontFaceQuartet::Member::Italic),
  };

  static bool bFakeNamesAreSorted = false;
  if (false == bFakeNamesAreSorted)
  {
    bFakeNamesAreSorted = true;
    qsort(fake_names, sizeof(fake_names) / sizeof(fake_names[0]), sizeof(fake_names[0]), (int(*)(const void*,const void*))Internal_FakeWindowsLogfontName::CompareFamilyAndPostscriptNameHash);
  }
  
  const Internal_FakeWindowsLogfontName key(family_name, postscript_name, L"", ON_FontFaceQuartet::Member::Unset);
  const Internal_FakeWindowsLogfontName* fake_name 
    = (const Internal_FakeWindowsLogfontName*)bsearch((const void*)&key, (const void*)fake_names, sizeof(fake_names) / sizeof(fake_names[0]), sizeof(fake_names[0]), (int(*)(const void*, const void*))Internal_FakeWindowsLogfontName::CompareFamilyAndPostscriptNameHash);
  if (
      fake_name
      && ON_FontFaceQuartet::Member::Unset != fake_name->QuartetMember()
      && false == fake_name->QuartetFamilyAndPostscriptNameHash().IsZeroDigestOrEmptyContentHash()
      && fake_name->FakeWindowsLogfontName().IsNotEmpty()
      )
  {
    // this family is complicated enough that it
    // has to be partitioned into multiple fake Windows LOGFONT quartets.
    return fake_name->FakeWindowsLogfontName();
  }

  return family_name; // use family_name as the fake LOGFONT name
}

static bool Internal_TestInstalledFontsFailure()
{
  return false; // <- breakpoint here
}

bool ON_Font::TestInstalledFontList(ON_TextLog& text_log)
{
  const class ON_FontList& font_list = ON_Font::InstalledFontList();
  const unsigned font_count = font_list.Count();
  if (font_count <= 0)
  {
    text_log.Print("ERROR: 0 = ON_Font::InstalledFontList().Count()\n");
    return Internal_TestInstalledFontsFailure();
  }

  const ON_SimpleArray< const class ON_Font* >& by_hash = font_list.ByFontCharacteristicsHash();
  if (font_count != by_hash.UnsignedCount())
  {
    text_log.Print("ERROR: nullptr = ON_Font::InstalledFontList()..FromFontCharacteristicsHash(ON_Font::Default.FontCharacteristicsHash(),false)\n");
    return Internal_TestInstalledFontsFailure();
  }

  const bool bReturnFirst = false;
  bool bPassedTest = true;

  text_log.Print("Testing %u installed fonts:\n", font_count);
  {
    const ON_TextLogIndent indent1(text_log);


    text_log.Print(L"FromFontCharacteristicsHash() tests ...");
    {
      ON_TextLogIndent indent2(text_log);
      unsigned error_count = 0;
      for (unsigned i = 0; i < font_count; ++i)
      {
        const ON_Font* f = by_hash[i];
        const ON_SHA1_Hash h = f->FontCharacteristicsHash();

        const ON_Font* f1 = f = font_list.FromFontCharacteristicsHash(h, bReturnFirst);
        if (f != f1)
        {
          if (0 == error_count)
            text_log.PrintNewLine();
          ++error_count;
          text_log.Print("ERROR: nullptr = ON_Font::InstalledFontList().FromFontCharacteristicsHash(by_hash[%u],false).\n", i);
          bPassedTest = false;
        }
      }
      if (error_count > 0)
        text_log.Print("FAILED. %u errors.\n", error_count);
      else
        text_log.Print(" passed.\n");
    }

    {
      const ON_Font* f = font_list.FromFontCharacteristicsHash(ON_Font::Default.FontCharacteristicsHash(), bReturnFirst);
      if (nullptr == f)
      {
        text_log.Print("ERROR: nullptr = ON_Font::InstalledFontList()..FromFontCharacteristicsHash(ON_Font::Default.FontCharacteristicsHash(),false)\n");
        bPassedTest = false;
      }
    }
  }

  const ON_ClassArray< ON_FontFaceQuartet >& quartet_list = font_list.QuartetList();
  const unsigned quartet_count = quartet_list.UnsignedCount();
  text_log.Print("Testing %u quartets:\n", quartet_count);
  {
    const ON_TextLogIndent indent1(text_log);

    unsigned error_count = 0;
    for (unsigned i = 0; i < quartet_count; ++i)
    {
      const ON_FontFaceQuartet& q = quartet_list[i];
      const ON_wString qname = q.QuartetName();
      if (qname.IsEmpty())
      {
        ++error_count;
        text_log.Print("ERROR: nullptr = quartet_list[%u].QuartetName() is empty\n", i);
        bPassedTest = false;
        continue;
      }
      const ON_FontFaceQuartet q1 = font_list.QuartetFromQuartetName(qname);
      bool bQuartetFromQuartetNamePass = q.QuartetName() == q1.QuartetName();
      const ON_Font* f[4] = { q.RegularFace(),q.BoldFace(),q.ItalicFace(),q.BoldItalicFace() };
      const ON_Font* f1[4] = { q1.RegularFace(),q1.BoldFace(),q1.ItalicFace(),q1.BoldItalicFace() };
      const bool bExpectedIsBoldInQuartet[4] = { false,true,false,true };
      const bool bExpectedIsItalicInQuartet[4] = { false,false,true,true };
      const ON_wString qface[4] = { ON_wString(L"regular"), ON_wString(L"bold"), ON_wString(L"italic"), ON_wString(L"bolditalic") };
      for (unsigned k = 0; k < 4; ++k)
      {
        if (bQuartetFromQuartetNamePass && f[k] != f1[k])
          bQuartetFromQuartetNamePass = false;
        if (nullptr != f[k])
        {
          ON_wString qname1 = qname;
          qname1 += L" (";
          qname1 += qface[k];
          qname1 += L")";
          const ON_SHA1_Hash h = f[k]->FontCharacteristicsHash();
          const ON_Font* f2 = font_list.FromFontCharacteristicsHash(h, bReturnFirst);
          if (f2 != f[k])
          {
            ++error_count;
            text_log.Print("ERROR: nullptr = ON_Font::InstalledFontList().FromFontCharacteristicsHash(%ls,false).\n", qname1.Array());
            bPassedTest = false;
          }
          const bool bIsBoldInQuartet = f[k]->IsBoldInQuartet();
          const bool bIsItalicInQuartet = f[k]->IsItalicInQuartet();
          if (bIsBoldInQuartet != bExpectedIsBoldInQuartet[k])
          {
            ++error_count;
            text_log.Print("ERROR: IsBoldInQuartet(%ls) = %ls.\n", qname1.Array(), bIsBoldInQuartet?L"true":L"false");
            bPassedTest = false;
          }
          if (bIsItalicInQuartet != bExpectedIsItalicInQuartet[k])
          {
            ++error_count;
            text_log.Print("ERROR: IsItalicInQuartet(%ls) = %ls.\n", qname1.Array(), bIsItalicInQuartet ? L"true" : L"false");
            bPassedTest = false;
          }
        }
      }
      if (false == bQuartetFromQuartetNamePass)
      {
        ++error_count;
        text_log.Print(L"ERROR: QuartetFromQuartetName(%ls) failed.\n",static_cast<const wchar_t*>(qname));
      }
    }
    if (error_count > 0)
      text_log.Print("FAILED. %u quartet errors.\n", error_count);
    else
      text_log.Print("Passed.\n");
  }

  return bPassedTest;
}


const ON_wString ON_Font::QuartetName(
  ON_Font::NameLocale name_locale
) const
{
  // The Windows OS partitions a font family (which can have many face) into
  // subsets with at most 4 faces that can be tagged regular/italic/bold/bold-italic
  // and assigns each subset a unique "LOGFONT" name. Note that some subsets may
  // have fewer than 4 faces because there isn't an italic or bold member.
  // There are Windows OS font picking tools that use
  // LOGFONT name + regular/italic/bold/bold-italic to select a particular face
  // and these work ok because Windows OS generates the quartets and all applications
  // choosing to use the archaic regular/italic/bold/bold-italic font UI have consistent
  // quartets.
  //
  // Modern Mac OS does not have native font selection UI that uses the 
  // archaic regular/italic/bold/bold-italic approach.
  //
  // On Mac OS, opennurbs generates a fake LOGFONT name because Rhino 6 and 7 use
  // the archaic regular/italic/bold/bold-italic font UI on oth Windows and Mac.
  // Helvetica Neue, American Typewriter, and Avenir are examples of common
  // Mac OS font families that do not fit well with the 
  // archaic regular/italic/bold/bold-italic font UI. Code in
  // opennurbs_apple_nsfont.cpp is used to assign fake LOGFONT names for fonts
  // like these.
  return WindowsLogfontName(name_locale);
}

ON_FontFaceQuartet::Member ON_Font::QuartetFaceMember() const
{
  // DO NOT call any other code to guess the anser. 
  // This value is set only when the quartet member is known with 100% certainty.
  // See IsBoldInQuartet() or IsItalicInQuartet() for code that starts
  // guessing when m_quartet_member is Unset.
  return this->m_quartet_member;
}

const ON_wString ON_Font::QuartetName() const
{
  return ON_Font::QuartetName(ON_Font::NameLocale::LocalizedFirst);
}

const ON_wString ON_Font::QuartetDescription() const
{
  ON_wString s = this->QuartetName();
  if (s.IsEmpty())
    return ON_wString::EmptyString;
  if (s.IsNotEmpty())
  {
    const ON_FontFaceQuartet::Member m = ON_Font::QuartetFaceMember();
    if (ON_FontFaceQuartet::Member::Unset != m)
    {
      s += L" (";
      s += ON_FontFaceQuartet::MemberToString(m);
      s += L")";
    }
  }
  return s;
}

bool ON_Font::IsBoldInQuartet() const
{
  if (ON_FontFaceQuartet::Member::Unset != this->m_quartet_member)
  {
    return ON_FontFaceQuartet::Member::Bold == this->m_quartet_member || ON_FontFaceQuartet::Member::BoldItalic == this->m_quartet_member;
  }

  // ... sigh, start guessing from imperfect information
  const ON_Font::Weight font_weight = this->FontWeight();

  ON_FontFaceQuartet q = FontQuartet();

  if (q.IsEmpty())
  {
    // this font is not associated with a quartet. 
    // The best we can do is look at the unreliable m_font_weight setting.
    // This will be wrong for light, heavy, black, ... fonts.
    return ON_Font::IsBoldWeight(font_weight);
  }

  const bool bProbablyItalic = (ON_Font::Style::Italic == m_font_style || ON_Font::Style::Oblique == m_font_style);

  const ON_Font* regular2[2] = { q.Face(false,bProbablyItalic), q.Face(false,!bProbablyItalic) };
  const ON_Font* bold2[2] = { q.Face(true,bProbablyItalic), q.Face(true,!bProbablyItalic) };

  if (this == regular2[0] || this == regular2[1])
    return false;
  if (this == bold2[0] || this == bold2[1])
    return false;

  const ON_SHA1_Hash this_hash = this->FontCharacteristicsHash();


  if (nullptr != regular2[0] && regular2[0]->FontCharacteristicsHash() == this_hash)
    return false;
  if (nullptr != regular2[1] && regular2[1]->FontCharacteristicsHash() == this_hash)
    return false;

  if (nullptr != bold2[0] && bold2[0]->FontCharacteristicsHash() == this_hash)
    return true;
  if (nullptr != bold2[1] && bold2[1]->FontCharacteristicsHash() == this_hash)
    return true;

  if (this->IsInstalledFont())
  {
    // Doesn't work with managed fonts (missing) because their quartets are typically not completely filled in.
    // NOTE The q.IsEmpty() test above insures at least one of regular2[] or bold2[] has a non nullptr.
    if (nullptr == bold2[0] && nullptr == bold2[1])
      return false; // every face in this quartet is regular.
    if (nullptr == regular2[0] && nullptr == regular2[1])
      return true; // every face in this quartet is bold.
  }

  if (ON_Font::Weight::Unset == this->FontWeight())
    return false; // who knows?

  if (nullptr == regular2[0])
    regular2[0] = regular2[1];
  if (nullptr == bold2[0])
    bold2[0] = bold2[1];

  unsigned int regular_weight;
  if (nullptr != regular2[0] && ON_Font::Weight::Unset != regular2[0]->FontWeight())
    regular_weight = static_cast<unsigned>(regular2[0]->FontWeight());
  else if (nullptr != bold2[0] && ON_Font::Weight::Unset != bold2[0]->FontWeight())
    regular_weight = static_cast<unsigned>(bold2[0]->FontWeight())-1;
  else
    regular_weight = static_cast<unsigned>(ON_Font::Weight::Normal);

  return static_cast<unsigned>(font_weight) > regular_weight;
}


bool ON_Font::IsItalicInQuartet() const
{
  if (ON_FontFaceQuartet::Member::Unset != this->m_quartet_member)
  {
    return ON_FontFaceQuartet::Member::Italic == this->m_quartet_member || ON_FontFaceQuartet::Member::BoldItalic == this->m_quartet_member;
  }

  const bool bProbablyItalic = (ON_Font::Style::Italic == m_font_style || ON_Font::Style::Oblique == m_font_style);

  const ON_FontFaceQuartet q = InstalledFontQuartet(); // only look at installed quartets for italic query
  if (q.IsEmpty())
    return bProbablyItalic; // this font is not in a quartet

  const ON_SHA1_Hash this_hash = this->FontCharacteristicsHash();

  const ON_Font* upright2[2] = { q.RegularFace(), q.BoldFace() };
  if (nullptr != upright2[0] && upright2[0]->FontCharacteristicsHash() == this_hash)
    return false;
  if (nullptr != upright2[1] && upright2[1]->FontCharacteristicsHash() == this_hash)
    return false;


  const ON_Font* italic2[2] = { q.ItalicFace(), q.BoldItalicFace() };
  if (nullptr != italic2[0] && italic2[0]->FontCharacteristicsHash() == this_hash)
    return true;
  if (nullptr != italic2[1] && italic2[1]->FontCharacteristicsHash() == this_hash)
    return true;

  // NOTE The q.IsEmpty() test above insures at least one of upright2[] or italic2[] has a non nullptr.

  if (nullptr == italic2[0] && nullptr == italic2[1])
    return false; // every font in htis quartet is upright.

  if (nullptr == upright2[0] && nullptr == upright2[1])
    return true; // every font in this quartet is italic.

  bool bBoldInQuartet = this->IsBoldInQuartet();
  const ON_Font* upright = upright2[bBoldInQuartet ? 1 : 0];
  const ON_Font* italic = italic2[bBoldInQuartet ? 1 : 0];
  if (nullptr == upright && nullptr == italic)
  {
    // Assume regular/bold is not reliable
    upright = upright2[bBoldInQuartet ? 0 : 1];
    italic = italic2[bBoldInQuartet ? 0 : 1];
  }

  if (nullptr == italic)
    return false; // No italic with same regular/bold in this quartet.

  if (nullptr == upright)
    return true; // No upright with same regular/bold in this quartet.

  return bProbablyItalic; // best we can do
}

const ON_FontFaceQuartet ON_Font::FontQuartet() const
{
  const ON_wString quartet_name[2] = { QuartetName(), this->RichTextFontName() };
  const ON_SHA1_Hash quartet_name_hash[2] = { ON_Font::FontNameHash(quartet_name[0],false), ON_Font::FontNameHash(quartet_name[1],false) };
  
  const int imin = quartet_name[0].IsNotEmpty() ? 0 : 1;
  const int imax = (quartet_name[1].IsNotEmpty() && (quartet_name[0].IsEmpty() || quartet_name_hash[0] != quartet_name_hash[1])) ? 1 : 0;

  for (int i = imin; i <= imax; ++i)
  {
    ON_FontFaceQuartet installed_quartet = ON_Font::InstalledFontList().QuartetFromQuartetName(quartet_name[i]);
    if (installed_quartet.IsNotEmpty())
      return installed_quartet;
  }

  for (int i = imin; i <= imax; ++i)
  {
    ON_FontFaceQuartet managed_quartet = ON_Font::ManagedFontList().QuartetFromQuartetName(quartet_name[i]);
    if (managed_quartet.IsNotEmpty())
      return managed_quartet;
  }

  return ON_FontFaceQuartet::Empty;
}

const ON_FontFaceQuartet ON_Font::InstalledFontQuartet() const
{
  return InstalledFontList().QuartetFromQuartetName(QuartetName());
}


const ON_wString& ON_Font::Internal_GetName(
  ON_Font::NameLocale name_locale,
  const ON_wString& localized_name,
  const ON_wString& english_name
)
{
  if (ON_Font::NameLocale::Localized == name_locale)
    return localized_name;
  if (ON_Font::NameLocale::English == name_locale)
    return english_name;
  return localized_name.IsNotEmpty() ? localized_name : english_name;
}

const ON_wString Internal_RichTextCleaner
(
  const wchar_t* dirty_name
)
{
  ON_wString clean_name(dirty_name);
  clean_name.TrimLeftAndRight();
  clean_name.Remove(ON_wString::Space);
  clean_name.Remove(ON_wString::HyphenMinus);
  return clean_name;
}

const ON_wString ON_Font::RichTextFontName() const
{
  return ON_Font::RichTextFontName(this, false);
}

const ON_wString ON_Font::RichTextFontName(
  const ON_Font* font,
  bool bDefaultIfEmpty
)
{
  // Depending on what created the RTF or what will be parsing the RTF,
  // the face name in the RTF can be a PostScript name, LOGFONT.lfFaceName,
  // IDWriteFont family name, ..., and probably several other choices.

  // The complete PostScript name is a bad choice. It doesn't work for
  // WIndows RTF readers.  Opennurbs relies on a hueristic to convert
  // PostScript names to family names.
  //
  // The Windows LOGFONT.lfFaceName is a bad choice. It doesn't work for
  // Apple RTF readers but it works better on Windows readers than
  // the proper family name for faces like "Arial Narrow" and "Arial Black"
  // In these cases. "Arial" is the family name, but there are generally 
  // not enough details in RTF files and the code that parses it to recover
  // and select the Narrow or Black face if the family is set to Arial.
  //
  // For fonts that have only the 4 standard faces (regular, bold, italic,
  // and bold-italic), the ON_Font::FamilyName() generally works well both
  // platforms. However, it is not easy to determine when a font will only
  // be published with the 4 standard faces and popular fonts often have
  // more than 4 faces so they can offer a wider variety of weight,
  // stretch/width, and style/slope options.
  //
  // The more general problem is that modern fonts and font rendering 
  // has outgrown the limitations codes that parse RTF.

  const ON_Font* fonts[2]{ font, bDefaultIfEmpty ? &ON_Font::Default : nullptr };
  ON_wString rtf_font_name;
  for (int i = 0; i < 2; i++)
  {
    const ON_Font* f = fonts[i];
    if (nullptr == f)
      continue;

    // It is important to use the WindowsLogfontName
    // before resorting to family name. This gives the best
    // results for getting the right answer from font faces 
    // like "Arial Narrow" and "Arial Black". In both cases,
    // "Arial" is the more correct choice of a family name
    // but there are generally not enough details in RTF files
    // and the code that parses it to use the Narrow or Black
    // face if the family is set to Arial.
    rtf_font_name = f->WindowsLogfontName();
    if (rtf_font_name.IsNotEmpty())
      break;

    rtf_font_name = f->FamilyName();
    if (rtf_font_name.IsNotEmpty())
      break;

    rtf_font_name = ON_Font::FamilyNameFromDirtyName(f->PostScriptName());
    if (rtf_font_name.IsNotEmpty())
      break;

    // DO NOT USE FACE NAME - it is a term like "Regular" / "Bold" / ...and is useless.
  }

  if (rtf_font_name.IsEmpty() && bDefaultIfEmpty)
  {
    rtf_font_name = ON_Font::DefaultFamilyName();
  }

  return rtf_font_name;
}

/*
InternalHashToName is used to map hash values from
a ON_Font::FontNameHash() to the corresponding correct font Family name.
*/
class InternalHashToName
{
public:
  InternalHashToName() = default;
  ~InternalHashToName() = default;
  InternalHashToName(const InternalHashToName&) = default;
  InternalHashToName& operator=(const InternalHashToName&) = default;

public:
  InternalHashToName
  (
    const wchar_t* dirty_name,
    const wchar_t* clean_family_name
  )
    : m_dirty_name_hash(ON_Font::FontNameHash(dirty_name,true))
    , m_family_name(clean_family_name)
  {}

  InternalHashToName
  (
    const wchar_t* clean_family_name
  )
    : m_dirty_name_hash(ON_Font::FontNameHash(clean_family_name,false))
    , m_family_name(clean_family_name)
  {}

public:
  static int CompareHash(const void* lhs, const void* rhs)
  {
    return ON_SHA1_Hash::Compare(((const InternalHashToName*)lhs)->m_dirty_name_hash, ((const InternalHashToName*)rhs)->m_dirty_name_hash);
  }

  static size_t SortAndCullByHash(InternalHashToName* a, size_t a_count)
  {
    if (nullptr == a || a_count <= 0)
      return 0;

    ON_qsort(a, a_count, sizeof(a[0]), InternalHashToName::CompareHash);
    size_t culled_count = 1;
    const InternalHashToName* k1 = &a[0];
    for (size_t i = 1; i < a_count; i++)
    {
      if (0 == InternalHashToName::CompareHash(k1, &a[i]) )
        continue;
      a[culled_count] = a[i];
      k1 = &a[culled_count];
      culled_count++;
    }
    return culled_count;
  }
public:
  ON_SHA1_Hash m_dirty_name_hash = ON_SHA1_Hash::ZeroDigest;
  const wchar_t* m_family_name = nullptr;
};

static ON_OutlineFigure::Type Internal_FigureTypeFromHashedFontName(
  const InternalHashToName* key
)
{
  static InternalHashToName single_stroke_name_map[] = 
  {
    // Known single stroke fonts names
                                                   
    // Machine Tool
    InternalHashToName(L"Machine Tool Gothic"), // Family
    InternalHashToName(L"MachineToolGothic"), // PostScript
    InternalHashToName(L"Machine Tool Grenadier"), // Family
    InternalHashToName(L"MachineToolGrenadier"), // PostScript
    InternalHashToName(L"Machine Tool Handscript"), // Family
    InternalHashToName(L"MachineToolHandscript"), // PostScript
    InternalHashToName(L"Machine Tool SanSerif"), // Family
    InternalHashToName(L"MachineToolSanSerif"), // PostScript
    InternalHashToName(L"Machine Tool Script"), // Family
    InternalHashToName(L"MachineToolScript"), // PostScript

    // MecSoft
    InternalHashToName(L"MecSoft_Font-1"), // Family
    InternalHashToName(L"MecSoft_Font-1"), // PostScript

    // Orach Technic 1L
    InternalHashToName(L"OrachTech1Lotf"), // Family
    InternalHashToName(L"OrachTech1Lotf"), // PostScript
    InternalHashToName(L"OrachTechDemo1Lotf"), // Family
    InternalHashToName(L"OrachTechDemo1Lotf"), // PostScript
    InternalHashToName(L"OrachTech1Lttf"), // Family
    InternalHashToName(L"OrachTech1Lttf"), // PostScript
    InternalHashToName(L"OrachTechDemo1Lttf"), // Family
    InternalHashToName(L"OrachTechDemo1Lttf"), // PostScript

    // Rhino Single Stroke by Lowell Walmsley 
    InternalHashToName(L"RHSS"), // Family
    InternalHashToName(L"RhSS-Normal"), // PostScript

    // SD Stroke Open Type Font
    InternalHashToName(L"SDstroke"), // Family
    InternalHashToName(L"SDstroke-latin"), // PostScript


    // Single line fonts
    // Included here for now until 
    // https://mcneel.myjetbrains.com/youtrack/issue/RH-57328
    // Gets fonts with the field 10 description set.
    InternalHashToName(L"SLF-RHN Architect"), // Family
    InternalHashToName(L"SLF-RHN-Architect"), // PostScript

    InternalHashToName(L"SLF-RHN Industrial"), // Family
    InternalHashToName(L"SLF-RHN-Industrial"), // PostScript

    InternalHashToName(L"SLF-RHN White Linen"), // Family
    InternalHashToName(L"SLF-RHN-WhiteLiinen"), // PostScript

    // https://mcneel.myjetbrains.com/youtrack/issue/RH-67652
    InternalHashToName(L"AVGauge Engraving"), // Family
    InternalHashToName(L"AVGauge_Engraving"), // PostScript
  };

  static InternalHashToName double_stroke_name_map[] = 
  {
    // Known double stroke fonts names
    //  If a double stroke font is treated as a single stroke font,
    //  then the "TrueType" automatic closure segment is dropped
    //  and glyphs for code points like o O 8 Q, ... have missing segments.
   
    // CamBam Stick fonts
    InternalHashToName(L"1CamBam_Stick_1"), // Family
    InternalHashToName(L"1CamBamStick1-normal"), // PostScript
    InternalHashToName(L"1CamBam_Stick_2"), // Family
    InternalHashToName(L"1CamBamStick2-normal"), // PostScript
    InternalHashToName(L"1CamBam_Stick_3"), // Family
    InternalHashToName(L"1CamBamStick3-normal"), // PostScript
    InternalHashToName(L"1CamBam_Stick_4"), // Family
    InternalHashToName(L"1CamBamStick4-normal"), // PostScript
    InternalHashToName(L"1CamBam_Stick_5"), // Family
    InternalHashToName(L"1CamBamStick5-normal"), // PostScript
    InternalHashToName(L"1CamBam_Stick_6"), // Family
    InternalHashToName(L"1CamBamStick6-normal"), // PostScript
    InternalHashToName(L"1CamBam_Stick_7"), // Family
    InternalHashToName(L"1CamBamStick7-normal"), // PostScript
    InternalHashToName(L"1CamBam_Stick_8"), // Family
    InternalHashToName(L"1CamBamStick8-normal"), // PostScript
    InternalHashToName(L"1CamBam_Stick_9"), // Family
    InternalHashToName(L"1CamBamStick9"), // PostScript

    // CNC Vector
    InternalHashToName(L"CNC Vector"), // Family
    InternalHashToName(L"CNCVector"), // PostScript
    InternalHashToName(L"CNC Vector Mirror"), // Family
    InternalHashToName(L"CNCVectorMirror"), // PostScript

    // NOTE WELL: 
    //  Orach Technic 2L fonts are NOT a double stroke fonts.
    //  The figure outlines are simple closed perimenters
    //  that contain postive areas. 
    //  The behave poorly in simulated bold face.
  };

  static InternalHashToName perimeter_name_map[] = 
  {
    // Known perimeter stroke fonts names
    //  In fact, almost every TrueType, PostScript, and OpenType font
    //  has periemter figures. The list below contains fonts
    //  that some people might think are single or double stroke
    //  and common fonts so we don't keep checking.

    // Common
    InternalHashToName(L"Arial"),
    InternalHashToName(L"Bahnschrift"),
    InternalHashToName(L"CityBlueprint"),
    InternalHashToName(L"CountryBlueprint"),
    InternalHashToName(L"Courier"),
    InternalHashToName(L"Courier New"),
    InternalHashToName(L"Franklin Gothic"),
    InternalHashToName(L"Helvetica"),
    InternalHashToName(L"Helvetica Neue"),
    InternalHashToName(L"Segoe UI"),
    InternalHashToName(L"Times New Roman"),
    InternalHashToName(L"Tecnnic"),
    InternalHashToName(L"ArialMT"),
    InternalHashToName(L"CourierNewPS"),
    InternalHashToName(L"CourierNewPSMT"),
    InternalHashToName(L"FranklinGothic"),
    InternalHashToName(L"HelveticaNeue"),
    InternalHashToName(L"TimesNewRomanPS"),
    InternalHashToName(L"TimesNewRomanPSMT"),
   
    // Orach Technic 1L
    InternalHashToName(L"OrachTech2Lotf"), // Family
    InternalHashToName(L"OrachTech2Lotf"), // PostScript
    InternalHashToName(L"OrachTechDemo2Lotf"), // Family
    InternalHashToName(L"OrachTechDemo2Lotf"), // PostScript
    InternalHashToName(L"OrachTech2Lttf"), // Family
    InternalHashToName(L"OrachTech2Lttf"), // PostScript
    InternalHashToName(L"OrachTechDemo2Lttf"), // Family
    InternalHashToName(L"OrachTechDemo2Lttf"), // PostScript
  };

  static size_t single_stroke_name_map_count = 0;
  static size_t double_stroke_name_map_count = 0;
  static size_t perimeter_name_map_count = 0;

  if ( nullptr == key)
    return ON_OutlineFigure::Type::Unknown;

  const InternalHashToName* e;
  const size_t sizeof_e = sizeof(*e);

  if (0 == single_stroke_name_map_count)
  {
    single_stroke_name_map_count = InternalHashToName::SortAndCullByHash(single_stroke_name_map, (sizeof(single_stroke_name_map) / sizeof_e));
    double_stroke_name_map_count = InternalHashToName::SortAndCullByHash(double_stroke_name_map, (sizeof(double_stroke_name_map) / sizeof_e));
    perimeter_name_map_count = InternalHashToName::SortAndCullByHash(perimeter_name_map, (sizeof(perimeter_name_map) / sizeof_e));
  }


  e = (const InternalHashToName*)bsearch(key, single_stroke_name_map, single_stroke_name_map_count, sizeof_e, InternalHashToName::CompareHash);
  if (nullptr != e)
    return ON_OutlineFigure::Type::SingleStroke;

  e = (const InternalHashToName*)bsearch(key, double_stroke_name_map, double_stroke_name_map_count, sizeof_e, InternalHashToName::CompareHash);
  if (nullptr != e)
    return ON_OutlineFigure::Type::DoubleStroke;

  e = (const InternalHashToName*)bsearch(key, perimeter_name_map, perimeter_name_map_count, sizeof_e, InternalHashToName::CompareHash);
  if (nullptr != e)
    return ON_OutlineFigure::Type::Perimeter;

  // return Unset instead of Unknown in this internal tool
  return ON_OutlineFigure::Type::Unset;
}

static bool Internal_IsEngravingFont(
  const InternalHashToName* key
)
{

  // The structure of the font is a "perimeter", but the intended use
  // is for engraving. The OrachTech*2* fonts behave poorly when used
  // as perimeter fonts.
  static InternalHashToName double_line_name_map[] = 
  {  
    // Orach Technic 2L
    InternalHashToName(L"OrachTech2Lotf"), // Family
    InternalHashToName(L"OrachTech2Lotf"), // PostScript
    InternalHashToName(L"OrachTechDemo2Lotf"), // Family
    InternalHashToName(L"OrachTechDemo2Lotf"), // PostScript
    InternalHashToName(L"OrachTech2Lttf"), // Family
    InternalHashToName(L"OrachTech2Lttf"), // PostScript
    InternalHashToName(L"OrachTechDemo2Lttf"), // Family
    InternalHashToName(L"OrachTechDemo2Lttf"), // PostScript
  };

  static size_t double_line_name_map_count = 0;

  const InternalHashToName* e;
  const size_t sizeof_e = sizeof(*e);

  if (0 == double_line_name_map_count)
  {
    double_line_name_map_count = InternalHashToName::SortAndCullByHash(double_line_name_map, (sizeof(double_line_name_map) / sizeof_e));
  }

  e = (const InternalHashToName*)bsearch(key, double_line_name_map, double_line_name_map_count, sizeof_e, InternalHashToName::CompareHash);
  if (nullptr != e)
    return true;

  ON_OutlineFigure::Type outline_type = Internal_FigureTypeFromHashedFontName(key);
  if (ON_OutlineFigure::Type::SingleStroke == outline_type)
    return true;
  if (ON_OutlineFigure::Type::DoubleStroke == outline_type)
    return true;

  return false;
}


const wchar_t* ON_OutlineFigure::OrientationToWideString(
  ON_OutlineFigure::Orientation orientation
)
{
  const wchar_t* s;

  switch (orientation)
  {
  case ON_OutlineFigure::Orientation::Unset:
    s = L"Unset";
    break;
  case ON_OutlineFigure::Orientation::CounterClockwise:
    s = L"CounterClockwise";
    break;
  case ON_OutlineFigure::Orientation::Clockwise:
    s = L"Clockwise";
    break;
  case ON_OutlineFigure::Orientation::NotOriented:
    s = L"NotOriented";
    break;
  case ON_OutlineFigure::Orientation::Error:
    s = L"Error";
    break;
  default:
    s = L"<INVALID>";
    break;
  }

  return s;
}


ON_OutlineFigure::Type ON_OutlineFigure::FigureTypeFromFontName(
  const wchar_t* font_name
)
{
  if (nullptr == font_name || 0 == font_name[0])
    return ON_OutlineFigure::Type::Unset; // better than unknown when name is empty

  const InternalHashToName key(font_name, nullptr);
  return Internal_FigureTypeFromHashedFontName(&key);
}

ON_OutlineFigure::Type ON_OutlineFigure::FigureTypeFromField10Description(
  const ON_wString field_10_description
)
{
  ON_wString description(field_10_description);

  // ignore white space and hyphens
  description.Remove(ON_wString::Space);
  description.Remove(ON_wString::Tab);
  description.Remove(ON_wString::HyphenMinus);

  const int description_len = description.Length();

  if (description_len > 0)
  {
    description.MakeLowerOrdinal();
    const ON_wString s[2] = {
      ON_wString(L"singlestroke"),
      ON_wString(L"doublestroke")
    };
    const ON_OutlineFigure::Type t[2] = {
      ON_OutlineFigure::Type::SingleStroke,
      ON_OutlineFigure::Type::DoubleStroke
    };
    size_t count = sizeof(t) / sizeof(t[0]);
    for (size_t i = 0; i < count; ++i)
    {
      if (description.Find(s[i]) >= 0)
        return t[i];
    }
  }

  return ON_OutlineFigure::Type::Unset;
}

ON_OutlineFigure::Type ON_Font::OutlineFigureType() const
{
  if (m_outline_figure_type != ON_OutlineFigure::Type::Unset)
    return m_outline_figure_type;

  const ON_wString names[] =
  {
    FamilyName(),
    FamilyName(ON_Font::NameLocale::English),
    PostScriptName(),
    PostScriptName(ON_Font::NameLocale::English)
  };
  
  InternalHashToName key[sizeof(names)/sizeof(names[0])];

  const int name_count = (int)(sizeof(names) / sizeof(names[0]));
  int key_count = 0;
  for (int i = 0; i < name_count; i++)
  {
    const ON_wString& name = names[i];
    if (name.IsEmpty())
      continue;

    // computing the hash is much more expensive than checking for duplicate names (which is common)
    bool bSkipName = name.IsEmpty();
    for (int j = 0; false == bSkipName && j < i; j++)
      bSkipName = (name == names[j]);
    if (bSkipName)
      continue;

    // compute name hash
    key[key_count] = InternalHashToName(name, nullptr);

    // searching for a duplicate hash is more expensive than checking for duplicate hash 
    // (which is common because of space and hyphen differences between family and postscript names)
    for (int j = 0; false == bSkipName && j < key_count; j++)
      bSkipName = (key[key_count].m_dirty_name_hash == key[i].m_dirty_name_hash);
    if (bSkipName)
      continue;

    // search for matching name hash is lists of known single stroke and double stroke fonts
    ON_OutlineFigure::Type figure_type = Internal_FigureTypeFromHashedFontName(&key[key_count]);
    key_count++;
    if (
      ON_OutlineFigure::Type::Unset != figure_type
      && ON_OutlineFigure::Type::Unknown != figure_type
      && ON_OutlineFigure::Type::Mixed != figure_type
      )
      return figure_type;
  }
  return ON_OutlineFigure::Type::Unknown; // unknown means don't try again
}


bool ON_Font::IsSingleStrokeFont() const
{
  return ON_OutlineFigure::Type::SingleStroke == OutlineFigureType();
}


bool ON_Font::IsDoubleStrokeFont() const
{
  return ON_OutlineFigure::Type::DoubleStroke == OutlineFigureType();
}

bool ON_Font::IsSingleStrokeOrDoubleStrokeFont() const
{
  const ON_OutlineFigure::Type figure_type = OutlineFigureType();
  return (
    ON_OutlineFigure::Type::SingleStroke == figure_type
    || ON_OutlineFigure::Type::DoubleStroke == figure_type
    );
}

const ON_Font* ON_Font::DefaultEngravingFont()
{
  // The PostScript name works on Widows and is the best way on Apple.
  /*
   Font description = "SLF-RHN Architect Regular"
      Family name = "SLF-RHN Architect"
      Face name = "Regular"
      PostScript name = "SLFRHNArchitect-Regular"
      Quartet = SLF-RHN Architect (Regular)
      Windows LOGFONT name = "SLF-RHN Architect"
      Rich text name = "SLF-RHN Architect"
      Origin = Windows Font
      Outline type = Engraving - single stroke
      PointSize = annotation default
      Quartet: SLF-RHN Architect (Regular member)
      Weight = Normal
      Stretch = Medium
      Style = Upright
      Underlined = false
      Strikethrough = false
      Symbol font = false
      Engraving font = Single-stroke
      Font characteristics SHA-1 hash = E5527949C70756BFBC586AB04A9CFAD9FB5D9038
      LOGFONT
  */
  static const ON_Font* default_engraving_font = nullptr;

  if (nullptr == default_engraving_font)
  {
    default_engraving_font = ON_Font::InstalledFontList().FromNames(
      L"SLFRHNArchitect-Regular", // postscript_name,
      L"SLF-RHN Architect", // windows_logfont_name,
      L"SLF-RHN Architect", // family_name,
      L"Regular", // prefered_face_name,
      ON_Font::Weight::Normal,  // prefered_weight,
      ON_Font::Stretch::Medium, // prefered_stretch,
      ON_Font::Style::Upright,   // prefered_style,
      false, // bRequireFaceMatch,
      false, // bRequireStyleMatch,
      false, // bUnderlined,
      false, // bStrikethrough,
      0.0 // point_size
    );
  }

  return default_engraving_font;
}

bool ON_Font::IsEngravingFont() const
{
  const ON_wString names[] =
  {
    FamilyName(),
    FamilyName(ON_Font::NameLocale::English),
    PostScriptName(),
    PostScriptName(ON_Font::NameLocale::English)
  };
  
  InternalHashToName key[sizeof(names)/sizeof(names[0])];

  const int name_count = (int)(sizeof(names) / sizeof(names[0]));
  int key_count = 0;
  for (int i = 0; i < name_count; i++)
  {
    const ON_wString& name = names[i];
    if (name.IsEmpty())
      continue;

    // computing the hash is much more expensive than checking for duplicate names (which is common)
    bool bSkipName = name.IsEmpty();
    for (int j = 0; false == bSkipName && j < i; j++)
      bSkipName = (name == names[j]);
    if (bSkipName)
      continue;

    // compute name hash
    key[key_count] = InternalHashToName(name, nullptr);

    // searching for a duplicate hash is more expensive than checking for duplicate hash 
    // (which is common because of space and hyphen differences between family and postscript names)
    for (int j = 0; false == bSkipName && j < key_count; j++)
      bSkipName = (key[key_count].m_dirty_name_hash == key[i].m_dirty_name_hash);
    if (bSkipName)
      continue;

    // search for matching name hash is lists of known single stroke and double stroke fonts
    bool bIsEngravingFont = Internal_IsEngravingFont(&key[key_count]);
    key_count++;
    if (bIsEngravingFont)
      return true;
  }
  return false;
}


const ON_wString ON_Font::FamilyNameFromDirtyName(
  const wchar_t* dirty_name
)
{
  if (nullptr == dirty_name
    || 0 == dirty_name[0]
    || ON_wString::HyphenMinus == dirty_name[0])
  {
    return ON_wString::EmptyString;
  }

  // incredibly common query
  if (ON_wString::EqualOrdinal(ON_Font::DefaultFamilyName(), dirty_name, true))
  {
    return ON_wString(ON_Font::DefaultFamilyName());
  }

  static bool bInitialized = false;
  static ON_SimpleArray<InternalHashToName> clean_names;
  static ON_SimpleArray<InternalHashToName> dirty_names;

  const size_t sizeof_name = sizeof(clean_names[0]);

  if (false == bInitialized)
  {
    bInitialized = true;
    ON_MemoryAllocationTracking disable_tracking(false);
    ON_SimpleArray<const ON_Font*> installed_fonts;
    ON_Font::GetInstalledFontList(installed_fonts);
    size_t installed_count = installed_fonts.UnsignedCount();
    clean_names.Reserve(16 + installed_count);
    dirty_names.Reserve(16 + 2*installed_count);

    // Append known clean family names that contain a hypen.
    clean_names.Append(InternalHashToName(L"AvenirLT-Roman"));
    clean_names.Append(InternalHashToName(L"MecSoft_Font-1"));
    clean_names.Append(InternalHashToName(L"MingLiU_HKSCS-ExtB"));
    clean_names.Append(InternalHashToName(L"MingLiU-ExtB"));
    clean_names.Append(InternalHashToName(L"OCR-A II"));
    clean_names.Append(InternalHashToName(L"PMingLiU-ExtB"));
    clean_names.Append(InternalHashToName(L"SimSun-ExtB"));

    // Append known clean family names that end in "MT"
    clean_names.Append(InternalHashToName(L"Brush Script MT"));
    clean_names.Append(InternalHashToName(L"Devanagari MT"));
    clean_names.Append(InternalHashToName(L"French Script MT"));
    clean_names.Append(InternalHashToName(L"Gujarati MT"));
    clean_names.Append(InternalHashToName(L"Gurmukhi MT"));
    clean_names.Append(InternalHashToName(L"New Peninim MT"));
    clean_names.Append(InternalHashToName(L"OCR B MT"));

    // Append common clean family names (in case they are not installed on this computer)
    clean_names.Append(InternalHashToName(L"Arial"));
    clean_names.Append(InternalHashToName(L"Bahnschrift"));
    clean_names.Append(InternalHashToName(L"CityBlueprint"));    // common in ACAD dwg files
    clean_names.Append(InternalHashToName(L"CountryBlueprint")); // common in ACAD dwg files
    clean_names.Append(InternalHashToName(L"Courier"));
    clean_names.Append(InternalHashToName(L"Courier New"));
    clean_names.Append(InternalHashToName(L"Franklin Gothic"));
    clean_names.Append(InternalHashToName(L"Helvetica"));
    clean_names.Append(InternalHashToName(L"Helvetica Neue"));
    clean_names.Append(InternalHashToName(L"Segoe UI"));
    clean_names.Append(InternalHashToName(L"Times New Roman"));
    clean_names.Append(InternalHashToName(L"Tecnnic")); // common in ACAD dwg files

    // Append common dirty names (in case they are not installed on this computer)
    dirty_names.Append(InternalHashToName(L"ArialMT", L"Arial"));
    dirty_names.Append(InternalHashToName(L"CourierNewPS", L"Courier New")); // Handles all CourierNewPS-...MT names
    dirty_names.Append(InternalHashToName(L"CourierNewPSMT", L"Courier New"));
    dirty_names.Append(InternalHashToName(L"FranklinGothic", L"Franklin Gothic"));
    dirty_names.Append(InternalHashToName(L"HelveticaNeue", L"Helvetica Neue"));  // Handles all PostScript "HelveticaNeue-..." names
    dirty_names.Append(InternalHashToName(L"TimesNewRomanPS", L"Times New Roman")); // Handles all TimesNewRomanPS-...MT names
    dirty_names.Append(InternalHashToName(L"TimesNewRomanPSMT", L"Times New Roman"));

    const wchar_t* prev_clean_family_name = nullptr;
    for (size_t i = 0; i < installed_count; i++)
    {
#if defined(ON_RUNTIME_ANDROID) || defined(ON_RUNTIME_LINUX) || defined(ON_RUNTIME_WASM)
      const ON_Font* font = installed_fonts[(int)i];
#else
      const ON_Font* font = installed_fonts[i];
#endif
      if (nullptr == font)
        continue;

      // NOTE:
      //  font and the clean_family_name pointer persist for the lifetime of the application.
      const wchar_t* clean_family_name = static_cast<const wchar_t*>(font->FamilyName());
      if (nullptr == clean_family_name || 0 == clean_family_name[0])
        continue;

      // Add clean_family_name to clean_names[]
      if (false == ON_wString::EqualOrdinal(clean_family_name, prev_clean_family_name, true))
      {
        // Since the installed font list is sorted by family name, we can limit the sorting
        // and culling time for clean_names[] by keeping track of prev_clean_family_name
        clean_names.Append(InternalHashToName(clean_family_name));
        prev_clean_family_name = clean_family_name;
      }

      // Add PostScript name and LOGFONT.lfFaceName to dirty_names[]
      for (int j = 0; j < 2; j++)
      {
        // NOTE:
        //  font and the other_name pointer persist for the lifetime of the application.
        //
        //  Do NOT use the font->Description() string. That string does not persist
        //  And it adds to additional functionallity because it has the form <clean family name>-...
        const wchar_t* other_name
          = (0 == j)
          ? static_cast<const wchar_t*>(font->PostScriptName())
          : static_cast<const wchar_t*>(font->WindowsLogfontName());
        if (nullptr == other_name || 0 == other_name[0])
          continue;
        if (ON_wString::EqualOrdinal(clean_family_name, other_name, true))
        {
          // LOGFONT.lfFaceName or PostScript name = clean family name
          // and does not need to be in the "dirty" list. If this name
          // is ever passed in, it woll be handled by the clean_list[] entry.
          continue;  
        }
        dirty_names.Append(InternalHashToName(other_name,clean_family_name));
      }
    }

    // cull duplicates and ambiguous cases
    for (int adex = 0; adex < 2; adex++)
    {
      ON_SimpleArray<InternalHashToName>& a
        = (0 == adex)
        ? clean_names
        : dirty_names;

      const size_t count0 = a.UnsignedCount();

      ON_qsort(a.Array(), count0, sizeof_name, InternalHashToName::CompareHash);
      int count1 = 0;
      InternalHashToName candidate;
      for (size_t i = 0; i < count0; i++)
      {
#if defined(ON_RUNTIME_ANDROID) || defined(ON_RUNTIME_LINUX) || defined(ON_RUNTIME_WASM)
        InternalHashToName e = a[(int)i];
#else
        InternalHashToName e = a[i];
#endif
        if (candidate.m_dirty_name_hash == e.m_dirty_name_hash)
        {
          if (nullptr == candidate.m_family_name)
            continue;

          if (ON_wString::EqualOrdinal(candidate.m_family_name, e.m_family_name, true))
            continue; // duplicate

          // rare ambiguous case
          // Fonts with different family names have the same dirty name.
          candidate.m_family_name = nullptr;
          continue;
        }

        if (candidate.m_family_name)
        {
          a[count1++] = candidate;
        }
        candidate = e;
      }
      if (candidate.m_family_name)
      {
        a[count1++] = candidate;
      }
      a.SetCount(count1);
      a.Shrink();
    }
  }

  const InternalHashToName* e = nullptr;
  const InternalHashToName clean_key(dirty_name);
  e = (const InternalHashToName*)bsearch(&clean_key, clean_names.Array(), clean_names.UnsignedCount(), sizeof_name, InternalHashToName::CompareHash);
  if (nullptr != e)
  {
    // Ignoring case, spaces, and hyphens, dirty_name is a clean family.
    return ON_wString(e->m_family_name);
  }

  const InternalHashToName dirty_key(dirty_name, dirty_name);
  e = (const InternalHashToName*)bsearch(&dirty_key, dirty_names.Array(), dirty_names.UnsignedCount(), sizeof_name, InternalHashToName::CompareHash);
  if (nullptr != e)
  {
    // Ignoring case, spaces, and hyphens, dirty_name is a PostScript or LOGFONT.lfFaceName
    // and we know the corresponding clean family name.
    return ON_wString(e->m_family_name);
  }

  // No clean family name is exlicity known for the dirty_name parameter.
  // Truncate the input dirty_name at the first hypen to remove PostScript face descriptions.
  // (This is the reason we explicty add all known faces with hypens above).
  ON_wString best_guess(dirty_name);
  for (const wchar_t* c = dirty_name; 0 != *c; c++)
  {
    if (ON_wString::HyphenMinus != *c)
      continue;

    // Truncate dirty_name at the first hyphen
    int len = (int)(c - dirty_name);

    if (len >= 6 && 'M' == dirty_name[len - 2] && 'T' == dirty_name[len - 1])
    {
      // dirty_name = "...MT-...". Assume that we are dealing with a PostScript name
      // and the clean family name does not include the MT.
      // Above we have explicity handled known clean family names that end in MT.
      len -= 2;
    }

    best_guess.SetLength(len);
    break;
  }

  return best_guess;
}

const ON_String ON_Font::CleanFontName(
  const wchar_t* dirty_font_name,
  ON_StringMapOrdinalType map
)
{
  ON_wString clean_font_name(dirty_font_name);
  wchar_t* s0 = clean_font_name.Array();
  wchar_t* s1 = s0;
  const bool bMap = (ON_StringMapOrdinalType::Identity != map);
  for (wchar_t* s = s0, c = *s++; 0 != c; c = *s++)
  {
    if (
      ON_wString::Space == c
      || ON_wString::HyphenMinus == c
      || ON_wString::Underscore == c
      )
    {
      // PostScript, DWrite, LOGFONT all treat spaces, underbars and hyphens
      // differently. The purpose of this function is to get a string that
      // can be used to search for matching fonts. Ignoring spaces, underbars and hyphens
      // makes it possible to find installed fonts using a "dirty name" from another computer.
      continue;
    }
    if (bMap)
      c = ON_wString::MapCharacterOrdinal(map, c);
    *s1++ = c;
  }
  *s1 = 0;
  clean_font_name.SetLength(s1 - s0);
  if (map != ON_StringMapOrdinalType::Identity)
  {
    return clean_font_name.MapStringOrdinal(map);
  }
  return clean_font_name;
}

const ON_SHA1_Hash ON_Font::FontNameHash(
  const wchar_t* font_name,
  bool bStopAtHyphen
)
{
  ON_SHA1 sha1;
  const wchar_t* font_name0 = font_name;
  for (wchar_t c = (nullptr != font_name) ? *font_name++ : 0; 0 != c; c = *font_name++)
  {
    if (ON_wString::Space == c)
      continue;
    if (ON_wString::Underscore == c)
      continue;
    if (ON_wString::HyphenMinus == c)
    {
      if (bStopAtHyphen)
      {
        // The hyphens in these special cases are integral parts of the 
        // family part of the PostScript name and cannot terminate hashing.
        if (font_name == (font_name0 + 6) && ON_wString::EqualOrdinal(L"Arial-Black", 11, font_name0, 11, true))
          continue;
        if (font_name == (font_name0 + 3) && ON_wString::EqualOrdinal(L"MS-", 3, font_name0, 3, true))
          continue;
        if (font_name == (font_name0 + 4) && ON_wString::EqualOrdinal(L"OCR-A", 5, font_name0, 5, true))
          continue;
        if (font_name == (font_name0 + 9) && ON_wString::EqualOrdinal(L"AvenirLT-Roman", 14, font_name0, 14, true))
          continue;
        if (font_name == (font_name0 + 12) && ON_wString::EqualOrdinal(L"MecSoftFont-1", 13, font_name0, 13, true))
          continue;
        if (font_name == (font_name0 + 13) && ON_wString::EqualOrdinal(L"MecSoft_Font-1", 14, font_name0, 14, true))
          continue;

        // Single Line Font face names include the following. The hypen after SLF and the hyphen after RHN-
        // are part of the face name.
        // SLF-RHN-Architect
        // SLF-RHN-Industrial
        // SLF-RHN-WhiteLiinen (yup, Linen with ii)
        if (font_name == (font_name0 + 4) && ON_wString::EqualOrdinal(L"SLF-", 4, font_name0, 4, true))
          continue;
        if (font_name == (font_name0 + 8) && ON_wString::EqualOrdinal(L"SLF-RHN-", 8, font_name0, 8, true))
          continue;

        // Terminate hashing at this hypen because it separates the family name from the face name in a postscript name.
        break;
      }
      continue;
    }
    ON__UINT32 cp = ON_DecodeUTF16SurrogatePair(c, *font_name, 0);
    if (0 != cp)
    {
      // (c,*font_name) is a UTF-16 surrogate pair for unicode codepoint cp
      font_name++;
    }
    else
    {
      cp = ON_UnicodeMapCodePointOrdinal(ON_StringMapOrdinalType::MinimumOrdinal, (ON__UINT32)c);
    }
    sha1.AccumulateUnsigned32(cp);
  }
  return sha1.Hash();
}

int ON_Font::CompareFontName(const ON_wString& lhs, const ON_wString& rhs)
{
  return ON_Font::CompareFontNameWideChar(lhs,rhs);
}

int ON_Font::CompareFontNameWideChar(const wchar_t* lhs, const wchar_t* rhs)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  if (ON_Font::FontNameHash(lhs, false) == ON_Font::FontNameHash(rhs, false))
    return 0;
  return ON_wString::CompareOrdinal(lhs, rhs, true);
}

int ON_Font::CompareFontNamePointer(const ON_wString* lhs, const ON_wString* rhs)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  return ON_Font::CompareFontName(*lhs, *rhs);
}


int ON_Font::CompareFontNameToHyphen(const ON_wString& lhs, const ON_wString& rhs)
{
  return ON_Font::CompareFontNameToHyphenWideChar(lhs, rhs);
}

int ON_Font::CompareFontNameToHyphenWideChar(const wchar_t* lhs, const wchar_t* rhs)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  if (ON_Font::FontNameHash(lhs, true) == ON_Font::FontNameHash(rhs, true))
    return 0;
  return ON_wString::CompareOrdinal(lhs, rhs, true);
}

int ON_Font::CompareFontNameToHyphenPointer(const ON_wString* lhs, const ON_wString* rhs)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  return ON_Font::CompareFontNameToHyphen(*lhs, *rhs);
}


static bool IsAtoZ(
  const wchar_t* s
  )
{
  return (nullptr != s && ((s[0] >= 'A' && s[0] <= 'Z') || (s[0] >= 'a' && s[0] <= 'z')));
}

static const unsigned int ParseToken(
  const wchar_t*& s,
  size_t count,
  const wchar_t*const* token,
  const unsigned int* token_rc,
  unsigned int token_not_found_rc
  )
{
  if (IsAtoZ(s))
  {
    for (size_t i = 0; i < count; i++)
    {
      const int len = (int)ON_wString::Length(token[i]);
      if (ON_wString::EqualOrdinal(token[i], len, s, len, true))
      {
        s += len;
        return token_rc[i];
      }
    }
  }
  return token_not_found_rc;
}

static bool SkipSeparator(bool bSkipSpace, const wchar_t*& s)
{
  if (nullptr == s)
    return false;
  bool rc = false;
  switch (s[0])
  {
  case '-':
  case '_':
  case ',':
  case ';':
  case '.':
    rc = true;
    break;
  default:
    if (bSkipSpace && ON_wString::Space == s[0])
      rc = true;
    break;
  }
  if (rc)
    s++;
  return rc;
}

static bool ParseStretch(
  const wchar_t*& s,
  ON_Font::Stretch& font_stretch
  )
{
  if (false == IsAtoZ(s))
    return false;

  const wchar_t* s1 = s;

  const wchar_t* prefix_token[] = { L"SEMI", L"DEMI", L"EXTRA", L"ULTRA" };
  const size_t prefix_count = sizeof(prefix_token) / sizeof(prefix_token[0]);
  unsigned int prefix_rc[prefix_count] = { 1, 1, 2, 3 };
  const unsigned int prefix_id = ParseToken(s1, prefix_count, prefix_token, prefix_rc, 0);
  
  if ( 0 != prefix_id )
    SkipSeparator(true,s1);

  const unsigned int medium_rc = (0 != prefix_id) ? 0 : 2;
  const wchar_t* name_token[] = { L"CONDENSED", L"MEDIUM", L"NORMAL", L"EXPANDED",  };
  const size_t name_count = sizeof(name_token) / sizeof(name_token[0]);
  unsigned int name_rc[name_count] = { 1,medium_rc,medium_rc,3 };
  const unsigned int name_id = ParseToken(s1, name_count, name_token, name_rc, 0);
  if (0 == name_id)
    return false;


  bool rc = false;
  switch (name_id)
  {
  case 1: // Condensed
    switch (prefix_id)
    {
    case 0: // no prefix
      font_stretch = ON_Font::Stretch::Condensed;
      rc = true;
      break;
    case 1: // semi
      font_stretch = ON_Font::Stretch::Semicondensed;
      rc = true;
      break;
    case 2: // extra
      font_stretch = ON_Font::Stretch::Extracondensed;
      rc = true;
      break;
    case 3: // ultra
      font_stretch = ON_Font::Stretch::Ultracondensed;
      rc = true;
      break;
    }
    break;
  case 2: // Medium
    switch (prefix_id)
    {
    case 0: // no prefix
      font_stretch = ON_Font::Stretch::Medium;
      rc = true;
      break;
    }
    break;
  case 3: // Expanded
    switch (prefix_id)
    {
    case 0: // no prefix
      font_stretch = ON_Font::Stretch::Expanded;
      rc = true;
      break;
    case 1: // semi
      font_stretch = ON_Font::Stretch::Semiexpanded;
      rc = true;
      break;
    case 2: // extra
      font_stretch = ON_Font::Stretch::Extraexpanded;
      rc = true;
      break;
    case 3: // ultra
      font_stretch = ON_Font::Stretch::Ultraexpanded;
      rc = true;
      break;
    }
    break;
  }

  if (rc)
  {
    s = s1;
    return true;
  }

  return false;
}


static bool ParseWeight(
  const wchar_t*& s,
  ON_Font::Weight& font_weight
  )
{
  if (false == IsAtoZ(s))
    return false;

  const wchar_t* s1 = s;

  const wchar_t* prefix_token[] = { L"SEMI", L"DEMI", L"EXTRA", L"ULTRA" };
  const size_t prefix_count = sizeof(prefix_token) / sizeof(prefix_token[0]);
  unsigned int prefix_rc[prefix_count] = { 1, 1, 2, 2 };
  const unsigned int prefix_id = ParseToken(s1, prefix_count, prefix_token, prefix_rc, 0);
  
  if ( prefix_id > 0 )
    SkipSeparator(true,s1);

  const unsigned int medium_rc = (0 != prefix_id) ? 0 : 3;
  const unsigned int normal_rc = (0 != prefix_id) ? 0 : 4;

  const wchar_t* name_token[] = { L"THIN", L"LIGHT", L"NORMAL", L"REGULAR", L"MEDIUM", L"BOLD", L"HEAVY", L"BLACK" };
  const size_t name_count = sizeof(name_token) / sizeof(name_token[0]);
  unsigned int name_rc[name_count] = { 1, 2, normal_rc, normal_rc, medium_rc, 5, 6, 6 };
  const unsigned int name_id = ParseToken(s1, name_count, name_token, name_rc, 0);
  if (0 == name_id)
     return false;

  bool rc = false;
  switch (name_id)
  {
  case 1: // Thin
    font_weight = ON_Font::Weight::Thin;
    rc = true;
    break;

  case 2: // Light
    switch (prefix_id)
    {
    case 0:
      font_weight = ON_Font::Weight::Light;
      rc = true;
    case 1: // Semi
      font_weight = ON_Font::Weight::Light;
      rc = true;
    case 2: // Ultra
      font_weight = ON_Font::Weight::Ultralight;
      rc = true;
      break;
    }
    break;

  case 3: // Normal
    font_weight = ON_Font::Weight::Normal;
    rc = true;
    break;

  case 4: // Medium
    font_weight = ON_Font::Weight::Medium;
    rc = true;
    break;

  case 5: // Bold
    switch (prefix_id)
    {
    case 0:
      font_weight = ON_Font::Weight::Bold;
      rc = true;
    case 1: // Semi
      font_weight = ON_Font::Weight::Semibold;
      rc = true;
    case 2: // Ultra
      font_weight = ON_Font::Weight::Ultrabold;
      rc = true;
      break;
    }
    break;

  case 6: // Heavy
    font_weight = ON_Font::Weight::Heavy;
    rc = true;
    break;
  }

  if (rc)
  {
    s = s1;
    return true;
  }

  return false;
}

static bool ParseStyle(
  const wchar_t*& s,
  ON_Font::Style& font_style
  )
{
  if (false == IsAtoZ(s))
    return false;

  const wchar_t* s1 = s;

  const wchar_t* name_token[] = { L"UPRIGHT", L"ROMAN", L"ITALIC", L"OBLIQUE" };
  const size_t name_count = sizeof(name_token) / sizeof(name_token[0]);
  unsigned int name_rc[name_count] = { 1,1,2,3 };
  const unsigned int name_id = ParseToken(s1, name_count, name_token, name_rc, 0);
  if (0 == name_id)
     return false;

  bool rc = false;
  switch (name_id)
  {
  case 1: // Upright
    font_style = ON_Font::Style::Upright;
    rc = true;
    break;

  case 2: // Italic
    font_style = ON_Font::Style::Italic;
    rc = true;
    break;

  case 3: // Oblique
    font_style = ON_Font::Style::Oblique;
    rc = true;
    break;
  }

  if (rc)
  {
    s = s1;
    return true;
  }

  return false;
}

bool ON_Font::SetFromPostScriptName(
  const wchar_t* postscript_font_name
)
{
  if ( false == ON_FONT_MODIFICATION_PERMITTED)
    return false;

  // Save name in local memory before clearing this
  ON_wString local_postscript_font_name(postscript_font_name);
  local_postscript_font_name.TrimLeftAndRight();
  postscript_font_name = static_cast<const wchar_t*>(local_postscript_font_name);

  *this = ON_Font::Unset;

  if (nullptr == postscript_font_name || 0 == postscript_font_name[0])
    return false;

#if defined(ON_RUNTIME_WIN)
  // TODO: Get Windows IDWriteFont with matching post_script_name

#elif defined (ON_RUNTIME_APPLE_CORE_TEXT_AVAILABLE)
  // If the current computer has the same font, this will return the
  // highest fidelity match.
  // NOTE WELL: The NSFont API fails for some valid PostScript names.
  // For example, the some of the 14 or so faces Helvetica Neue 
  // are not round tripped using the NSFont by name creation and
  // are round tripped by using the CTFont API.
  bool bIsSubstituteFont = false;
  CTFontRef apple_font = ON_Font::AppleCTFont(postscript_font_name,0.0, bIsSubstituteFont);
  if (nullptr != apple_font)
  {
    return SetFromAppleCTFont(apple_font,true);
  }
#endif

  return SetFromFontDescription(nullptr, postscript_font_name);
}

bool ON_Font::SetFromFontDescription(
  const wchar_t* font_description
)
{
  const wchar_t* postscript_font_name = nullptr;
  return SetFromFontDescription(
    font_description,
    postscript_font_name
  );
}

bool ON_Font::SetFromFontDescription(
  const wchar_t* font_description,
  const wchar_t* postscript_name
  )
{
  ON_wString local_font_description(font_description);
  local_font_description.TrimLeftAndRight();
  font_description = static_cast<const wchar_t*>(local_font_description);

  ON_wString local_postscript_name(postscript_name);
  local_postscript_name.TrimLeftAndRight();
  postscript_name = static_cast<const wchar_t*>(local_postscript_name);

  if (nullptr == font_description || font_description[0] <= ON_wString::Space)
  {
    font_description = local_postscript_name;
    local_font_description = local_postscript_name;
    if (nullptr == font_description || font_description[0] <= ON_wString::Space)
      return false;
  }

  // As names are discovered that do not work in the code below,
  // add a special case here.  These are typically fonts that have
  // words like Upright, Italic, Oblique, Regular, Semi, Demi, Extra, Ultra, Medium
  // Black, Heavy, ... as part of the face name and those words must not
  // be parsed as possible weight, style or stretch characteristics applied
  // to a root face name.
  const wchar_t* special_cases[] = {
    // Apple's "Times New Roman" and "Times New Roman Bold Italic" is an example of why
    // special cases are required.  The face name is "Times New Roman" and "Roman" no
    // longer indicates an upright style.
    // However, Apple's "Avenir Roman" and "Avenir Oblique" fonts provide an example
    // where "Roman" is style and "Avenir" is a face name.  The default parsing
    // handles Avenir and any other font names that are using Roman as a style.
    L"Times New Roman", 

    // Put new special case names above this nullptr which terminates the special_cases[] list.
    nullptr
  };

  // NOTE WELL: 
  //  It is important that local_face_name be created from a pointer
  //  so that it's string buffer is not shared with other ON_wStrings.
  //  wchar_t values in local_face_name are modifed via const_cast<> below.
  ON_wString local_face_name = static_cast<const wchar_t*>(font_description);
  const wchar_t* characteristics = nullptr;
  int face_name_length = local_face_name.Length();
  for (int i = 0; nullptr != special_cases[i]; i++)
  {
    const int special_case_length = ON_wString::Length(special_cases[i]);
    if (special_case_length > face_name_length)
      continue;
    
    if (special_case_length < face_name_length && local_face_name[special_case_length] > ON_wString::Space )
      continue;
    
    if (false == ON_wString::EqualOrdinal(special_cases[i], special_case_length, font_description, special_case_length, true))
      continue;

    characteristics = static_cast<const wchar_t*>(local_face_name) + special_case_length;
    break;
  }

  if (nullptr == characteristics)
    characteristics = static_cast<const wchar_t*>(local_face_name) + 1;

  const wchar_t x = (wchar_t)1;

  ON_Font::Weight font_weight = ON_Font::Default.m_font_weight;
  for (wchar_t* s0 = const_cast<wchar_t*>(characteristics); 0 != *s0; s0++)
  {
    const wchar_t* s1 = s0;
    if (ParseWeight(s1, font_weight))
    {
      while ( s0 < s1 )
        *s0++ = x; // NOTE - modifies local_face_name content
      break;
    }
  }

  ON_Font::Style font_style = ON_Font::Default.m_font_style;
  for (wchar_t* s0 = const_cast<wchar_t*>(characteristics); 0 != *s0; s0++)
  {
    const wchar_t* s1 = s0;
    if (ParseStyle(s1, font_style))
    {
      while ( s0 < s1 )
        *s0++ = x; // NOTE - modifies local_face_name content
      break;
    }
  }

  ON_Font::Stretch font_stretch = ON_Font::Default.m_font_stretch;
  for (wchar_t* s0 = const_cast<wchar_t*>(characteristics); 0 != *s0; s0++)
  {
    const wchar_t* s1 = s0;
    if (ParseStretch(s1, font_stretch))
    {
      while ( s0 < s1 )
        *s0++ = x; // NOTE - modifies local_face_name content
      break;
    }
  }

  face_name_length = 0;
  for (const wchar_t* s = static_cast<const wchar_t*>(local_face_name); 0 != *s; s++)
  {
    if (*s >= ON_wString::Space)
      face_name_length++;
    else
    {
      while (*s > 0 && *s <= ON_wString::Space)
        s++;
      break;
    }
  }
  local_face_name.SetLength(face_name_length);
  local_face_name.TrimLeftAndRight();
  const wchar_t* face_name = static_cast<const wchar_t*>(local_face_name);

  bool rc = SetFontCharacteristics(
    face_name,
    font_weight,
    font_style,
    font_stretch,
    false,
    false,
    ON_FontMetrics::DefaultLineFeedRatio,
    ON_Font::WindowsConstants::logfont_default_charset
    );

  if (rc)
  {
    m_loc_postscript_name = local_postscript_name;
    m_en_postscript_name = m_loc_postscript_name;
  }  

  return rc;
}

//////////////////////////////////////////////////////////////////////
//
// ON_Object overrides

bool ON_Font::IsValid(ON_TextLog* text_log) const
{
  return (    
    (FamilyName().IsNotEmpty() || WindowsLogfontName().IsNotEmpty() || PostScriptName().IsNotEmpty())
    && ON_Font::Weight::Unset != m_font_weight
    && ON_Font::Style::Unset != m_font_style
    && ON_Font::Stretch::Unset != m_font_stretch
    );
}

void ON_Font::Dump(ON_TextLog& dump) const
{
  const bool bTextHash = dump.IsTextHash();

  ON_wString s;

  if (bTextHash)
  {
    dump.Print(L"Font family name = ...\n");
    dump.PushIndent();
    dump.Print(
      L"The font face name and other properties depend on the platform \n"
      "or the fonts installed on a particular computer. Information like \n"
      "this is omitted from dumps used for SHA-1 hash caluculations so \n"
      "hash values from different platforms and computers can be compared. \n"
    );
  }
  else
  {
    const ON_wString description = Description();
    dump.Print(L"Font description = \"%ls\"\n", static_cast<const wchar_t*>( description ));
    dump.PushIndent();
    
    const ON_wString family_name = FamilyName();
    dump.Print(L"Family name = \"%ls\"\n", static_cast<const wchar_t*>(family_name ));
    const ON_wString en_family_name = FamilyName(ON_Font::NameLocale::English);
    if ( en_family_name.IsNotEmpty() && en_family_name != family_name)
      dump.Print(L"Family name (English)= \"%ls\"\n", static_cast<const wchar_t*>(en_family_name ));

    const ON_wString face_name = FaceName();
    dump.Print(L"Face name = \"%ls\"\n", static_cast<const wchar_t*>( face_name ));
    const ON_wString en_face_name = FaceName(ON_Font::NameLocale::English);
    if ( en_face_name.IsNotEmpty() && en_face_name != face_name)
      dump.Print(L"Face name (English)= \"%ls\"\n", static_cast<const wchar_t*>(en_face_name ));

    const ON_wString postscript_name = PostScriptName();
    dump.Print(L"PostScript name = \"%ls\"\n", static_cast<const wchar_t*>(postscript_name));
    const ON_wString en_postscript_name = PostScriptName(ON_Font::NameLocale::English);
    if ( en_postscript_name.IsNotEmpty() && en_postscript_name != postscript_name)
      dump.Print(L"PostScript name (English)= \"%ls\"\n", static_cast<const wchar_t*>(en_postscript_name ));

    const ON_wString quartet_description = this->QuartetDescription();
    if (quartet_description.IsNotEmpty())
      dump.Print(L"Quartet = %ls\n", static_cast<const wchar_t*>(quartet_description));

    const ON_wString windows_logfont_name = WindowsLogfontName();
    dump.Print(L"Windows LOGFONT name = \"%ls\"\n", static_cast<const wchar_t*>(windows_logfont_name));
    const ON_wString en_windows_logfont_name = WindowsLogfontName(ON_Font::NameLocale::English);
    if ( en_windows_logfont_name.IsNotEmpty() && en_windows_logfont_name != windows_logfont_name)
      dump.Print(L"Windows LOGFONT name (English)= \"%ls\"\n", static_cast<const wchar_t*>(en_windows_logfont_name ));

    const ON_wString rich_text_name = ON_Font::RichTextFontName(this, false);
    dump.Print(L"Rich text name = \"%ls\"\n", static_cast<const wchar_t*>(rich_text_name));

    if (this->IsManagedSubstitutedFont())
    {
      const ON_Font* substitute = this->SubstituteFont();
      if (nullptr != substitute)
        dump.Print(L"Installed substitute = %ls\n", static_cast<const wchar_t*>(substitute->Description()));
    }

    s = ON_wString::EmptyString;
    switch (this->FontOrigin())
    {
    case ON_Font::Origin::Unset: break;
    case ON_Font::Origin::Unknown: s = L"Unknown"; break;
    case ON_Font::Origin::WindowsFont: s = L"Windows Font"; break;
    case ON_Font::Origin::AppleFont: s = L"Apple Font";  break;
    default: s = ON_wString::FormatToString(L"%u", static_cast<unsigned int>(this->FontOrigin())); break;
    };

    if (s.IsNotEmpty())
    {
      dump.Print(L"Origin = %ls\n", static_cast<const wchar_t*>(s));
    }
       
    s = ON_wString::EmptyString;
    const ON_OutlineFigure::Type outline_figure_type = this->OutlineFigureType();
    switch (outline_figure_type)
    {
    case ON_OutlineFigure::Type::Unset: break;
    case ON_OutlineFigure::Type::Unknown: break;
    case ON_OutlineFigure::Type::SingleStroke: s = L"Engraving - single stroke"; break;
    case ON_OutlineFigure::Type::DoubleStroke: s = L"Engraving - double stroke"; break;
    case ON_OutlineFigure::Type::Perimeter: s = L"Perimeter"; break;
    case ON_OutlineFigure::Type::NotPerimeter: s = L"Not a perimeter"; break;
    case ON_OutlineFigure::Type::Mixed: s = L"Mixed"; break;
    default: s = ON_wString::FormatToString(L"%u", static_cast<unsigned int>(outline_figure_type)); break;
    };

    if (s.IsNotEmpty())
    {
      dump.Print(L"Outline type = %ls\n", static_cast<const wchar_t*>(s));
    }
  }

  if (ON_Font::IsValidPointSize(m_point_size))
  {
    dump.Print(L"PointSize = %g\n", m_point_size);
  }
  else
  {
    dump.Print(L"PointSize = annotation default\n");
  }

  const ON_FontFaceQuartet q = this->FontQuartet();
  const ON_FontFaceQuartet::Member m = q.QuartetMember(this);
  switch (m)
  {
  case ON_FontFaceQuartet::Member::Regular:
    dump.Print("Quartet: %ls (Regular member)\n", static_cast<const wchar_t*>(q.QuartetName()));
    break;
  case ON_FontFaceQuartet::Member::Bold:
    dump.Print("Quartet: %ls (Bold member)\n", static_cast<const wchar_t*>(q.QuartetName()));
    break;
  case ON_FontFaceQuartet::Member::Italic:
    dump.Print("Quartet: %ls (Italic member)\n", static_cast<const wchar_t*>(q.QuartetName()));
    break;
  case ON_FontFaceQuartet::Member::BoldItalic:
    dump.Print("Quartet: %ls (Bold-Italic member)\n", static_cast<const wchar_t*>(q.QuartetName()));
    break;
  case ON_FontFaceQuartet::Member::Unset:
  default:
    dump.Print("Quartet: None\n");
    break;
  }


  s = ON_Font::WeightToWideString(FontWeight());
  if( s.IsEmpty())
    s = ON_wString::FormatToString(L"%u", static_cast<unsigned int>(this->FontWeight()));
  if (SimulatedWeight())
    s += L" (simulated)";
  dump.Print(L"Weight = %ls\n", static_cast<const wchar_t*>(s));

  s = ON_Font::StretchToWideString(FontStretch());
  if( s.IsEmpty())
    s = ON_wString::FormatToString(L"%u", static_cast<unsigned int>(this->FontStretch()));
  if (SimulatedStretch())
    s += L" (simulated)";
  dump.Print(L"Stretch = %ls\n", static_cast<const wchar_t*>(s));

  s = ON_Font::StyleToWideString(FontStyle());
  if( s.IsEmpty())
    s = ON_wString::FormatToString(L"%u", static_cast<unsigned int>(this->FontStyle()));
  if (SimulatedStyle())
    s += L" (simulated)";
  dump.Print(L"Style = %ls\n", static_cast<const wchar_t*>(s));

  dump.Print(L"Underlined = %ls\n", this->IsUnderlined() ? L"true" : L"false");

  dump.Print(L"Strikethrough = %ls\n", this->IsStrikethrough() ? L"true" : L"false");

  dump.Print(L"Symbol font = %ls\n", this->IsSymbolFont() ? L"true" : L"false");

  const ON_OutlineFigure::Type font_figure_type = this->OutlineFigureType();
  if (ON_OutlineFigure::Type::SingleStroke == font_figure_type)
    dump.Print(L"Engraving font = Single-stroke\n");
  else if (ON_OutlineFigure::Type::DoubleStroke == font_figure_type)
    dump.Print(L"Engraving font = Double-stroke\n");

  if ( 
    ON_PANOSE1::FamilyKind::Any != m_panose1.PANOSE1FamilyKind()
    && ON_PANOSE1::FamilyKind::NoFit != m_panose1.PANOSE1FamilyKind()
    )
  {
    // PANOSE1 may contains some useful information
    m_panose1.Dump(dump);
  }


  if (false == bTextHash)
  {
    const ON_wString characteristics_hash = FontCharacteristicsHash().ToString(true);
    dump.Print(L"Font characteristics SHA-1 hash = %ls\n", static_cast<const wchar_t*>(characteristics_hash));

    unsigned int runtime_sn = RuntimeSerialNumber();
    if (runtime_sn >= 1)
    {
      if (this == &ON_Font::Default)
        dump.Print(L"Managed font <%u> (ON_Font::Default)\n", runtime_sn);
      else if (IsInstalledFont())
      {
        dump.Print(L"Managed font <%u> (face installed on device)\n", runtime_sn);
      }
      else
      {
        dump.Print(L"Managed font <%u> (face not installed on device)\n", runtime_sn);
      }

      for (int fm_pass = 0; fm_pass < 1; fm_pass++)
      {
        const bool bNormalized = (1 == fm_pass);
        const ON_FontMetrics fm
          = bNormalized
          ? FontMetrics()
          : FontUnitFontMetrics();
        dump.Print(bNormalized ? L"Normalized font metrics:" : L"Font metrics:");
        if (fm.IsSet())
        {
          dump.PrintNewLine();
          dump.PushIndent();
          fm.Dump(dump);
          dump.PopIndent();
        }
        else
        {
          dump.Print(L" Unset\n");
        }
      }
    }

#if defined(ON_OS_WINDOWS_GDI)
    {
      const LOGFONT logfont = this->WindowsLogFont(0, nullptr);
      ON_Font::DumpLogfont(&logfont, dump);
    }
#elif defined (ON_RUNTIME_APPLE_CORE_TEXT_AVAILABLE)
    {
      bool bIsSubstituteFont = false;
      CTFontRef apple_font = AppleCTFont(bIsSubstituteFont);
      if (bIsSubstituteFont)
        dump.Print(L"Apple Core Text font (substitute):\n");
      else
        dump.Print(L"Apple Core Text font:\n");
      dump.PushIndent();
      ON_Font::DumpCTFont(apple_font, dump);
      dump.PopIndent();
      if (nullptr != apple_font && ON_Font::Origin::AppleFont == m_font_origin)
      {
        if (m_apple_font_weight_trait >= -1.0 && m_apple_font_weight_trait <= 1.0)
          dump.Print(L"Apple font weight trait = %g\n", m_apple_font_weight_trait);
        if (m_apple_font_width_trait >= -1.0 && m_apple_font_width_trait <= 1.0)
          dump.Print(L"Apple font width trait = %g\n", m_apple_font_width_trait);
      }
    }
#elif defined(OPENNURBS_FREETYPE_SUPPORT)
// Look in opennurbs_system_rumtime.h for the correct place to define OPENNURBS_FREETYPE_SUPPORT.
// Do NOT define OPENNURBS_FREETYPE_SUPPORT here or in your project setting ("makefile").
    if (runtime_sn >= 1)
    {
      // Free Type font details
      DumpFreeType(dump);
    }
#endif
  }
  dump.PopIndent();
}

bool ON_FontMetrics::IsUnset() const
{
  return (
    0 == m_UPM
    && 0 == m_ascent
    && 0 == m_descent
    && 0 == m_line_space
    && 0 == m_ascent_of_capital
    && 0 == m_ascent_of_x
    && 0 == m_strikeout_thickness
    && 0 == m_strikeout_position
    && 0 == m_underscore_thickness
    && 0 == m_underscore_position
    );
}

bool ON_FontMetrics::IsSet() const
{
  return IsUnset() ? false : true;
}

void ON_FontMetrics::Dump(class ON_TextLog& text_log) const
{
  text_log.Print("Units per EM = %d\n", m_UPM);
  text_log.Print("Ascent = %d\n", m_ascent);
  text_log.Print("Descent = %d\n", m_descent);
  text_log.Print("Distance between baselines = %d\n", m_line_space);
  text_log.Print("Ascent of capital = %d\n", AscentOfCapital());
  text_log.Print("Ascent of x = %d\n", AscentOfx());
  text_log.Print("Strikeout thickness = %d\n", m_strikeout_thickness);
  text_log.Print("Strikeout position = %d\n", m_strikeout_position);
  text_log.Print("Underscore thickness = %d\n", m_underscore_thickness);
  text_log.Print("Underscore position = %d\n", m_underscore_position);
}

#if defined(ON_OS_WINDOWS_GDI)

#define INTERNAL_CASE_STRING(c) case c: s = #c; break

static const ON_String Internal_WindowsLogFontCharSet(
  BYTE charSet
)
{
  ON_String s;
  switch (charSet)
  {
  INTERNAL_CASE_STRING(ANSI_CHARSET);
  INTERNAL_CASE_STRING(DEFAULT_CHARSET);
  INTERNAL_CASE_STRING(SYMBOL_CHARSET);
  INTERNAL_CASE_STRING(SHIFTJIS_CHARSET);
  INTERNAL_CASE_STRING(HANGEUL_CHARSET);
  INTERNAL_CASE_STRING(GB2312_CHARSET);
  INTERNAL_CASE_STRING(CHINESEBIG5_CHARSET);
  INTERNAL_CASE_STRING(OEM_CHARSET);
#if(WINVER >= 0x0400)
  INTERNAL_CASE_STRING(JOHAB_CHARSET);
  INTERNAL_CASE_STRING(HEBREW_CHARSET);
  INTERNAL_CASE_STRING(ARABIC_CHARSET);
  INTERNAL_CASE_STRING(GREEK_CHARSET);
  INTERNAL_CASE_STRING(TURKISH_CHARSET);
  INTERNAL_CASE_STRING(VIETNAMESE_CHARSET);
  INTERNAL_CASE_STRING(THAI_CHARSET);
  INTERNAL_CASE_STRING(EASTEUROPE_CHARSET);
  INTERNAL_CASE_STRING(RUSSIAN_CHARSET);
  INTERNAL_CASE_STRING(MAC_CHARSET);
  INTERNAL_CASE_STRING(BALTIC_CHARSET);
#endif
  default:
    s = ON_String::FormatToString("%u", (unsigned char)charSet);
    break;
  }
  return s;
}


static const ON_String Internal_WindowsLogFontFamily(
  BYTE pitchAndFamily
)
{
  ON_String s;
  const BYTE family = (0xF0 & pitchAndFamily);
  switch (family)
  {
  INTERNAL_CASE_STRING(FF_DONTCARE);
  INTERNAL_CASE_STRING(FF_ROMAN);
  INTERNAL_CASE_STRING(FF_SWISS);
  INTERNAL_CASE_STRING(FF_MODERN);
  INTERNAL_CASE_STRING(FF_SCRIPT);
  INTERNAL_CASE_STRING(FF_DECORATIVE);
  default:
    s = ON_String::FormatToString("%02X", family);
    break;
  };
  return s;
}

static const ON_String Internal_WindowsLogFontQuality(
  const BYTE lfQuality
)
{
  ON_String s;
  switch (lfQuality)
  {
  INTERNAL_CASE_STRING(DEFAULT_QUALITY);
  INTERNAL_CASE_STRING(DRAFT_QUALITY);
  INTERNAL_CASE_STRING(PROOF_QUALITY);
#if(WINVER >= 0x0400)
  INTERNAL_CASE_STRING(NONANTIALIASED_QUALITY);
  INTERNAL_CASE_STRING(ANTIALIASED_QUALITY);
#endif /* WINVER >= 0x0400 */

#if (_WIN32_WINNT >= _WIN32_WINNT_WINXP)
  INTERNAL_CASE_STRING(CLEARTYPE_QUALITY);
  INTERNAL_CASE_STRING(CLEARTYPE_NATURAL_QUALITY);
#endif
  default:
    s = ON_String::FormatToString("%u", (unsigned int)lfQuality);
    break;
  }
  return s;
}

static const ON_String Internal_WindowsLogFontOutPrecision(
  const BYTE lfOutPrecision
)
{
  ON_String s;
  switch (lfOutPrecision)
  {
  INTERNAL_CASE_STRING(OUT_DEFAULT_PRECIS);
  INTERNAL_CASE_STRING(OUT_STRING_PRECIS);
  INTERNAL_CASE_STRING(OUT_CHARACTER_PRECIS);
  INTERNAL_CASE_STRING(OUT_STROKE_PRECIS);
  INTERNAL_CASE_STRING(OUT_TT_PRECIS);
  INTERNAL_CASE_STRING(OUT_DEVICE_PRECIS);
  INTERNAL_CASE_STRING(OUT_RASTER_PRECIS);
  INTERNAL_CASE_STRING(OUT_TT_ONLY_PRECIS);
  INTERNAL_CASE_STRING(OUT_OUTLINE_PRECIS);
  INTERNAL_CASE_STRING(OUT_SCREEN_OUTLINE_PRECIS);
  INTERNAL_CASE_STRING(OUT_PS_ONLY_PRECIS);
  default:
    s = ON_String::FormatToString("%u", (unsigned int)lfOutPrecision);
    break;
  }
  return s;
}

static const ON_String Internal_WindowsLogFontClipPrecision(
  const BYTE lfClipPrecision
)
{
  ON_String s;
  switch (lfClipPrecision)
  {
  INTERNAL_CASE_STRING(CLIP_DEFAULT_PRECIS);
  INTERNAL_CASE_STRING(CLIP_CHARACTER_PRECIS);
  INTERNAL_CASE_STRING(CLIP_STROKE_PRECIS);
  INTERNAL_CASE_STRING(CLIP_MASK);
  INTERNAL_CASE_STRING(CLIP_LH_ANGLES);
  INTERNAL_CASE_STRING(CLIP_TT_ALWAYS);
#if (_WIN32_WINNT >= _WIN32_WINNT_LONGHORN)
  INTERNAL_CASE_STRING(CLIP_DFA_DISABLE);
#endif
  INTERNAL_CASE_STRING(CLIP_EMBEDDED);
  default:
    s = ON_String::FormatToString("%u", (unsigned int)lfClipPrecision);
    break;
  }
  return s;
}

void ON_Font::DumpLogfont(
  const LOGFONT* logfont,
  ON_TextLog& text_log
)
{
  if (nullptr == logfont)
  {
    text_log.Print(L"LOGFONT = nullptr\n");
    return;
  }

  text_log.Print(L"LOGFONT\n");
  text_log.PushIndent();
  ON_wString sFaceName = logfont->lfFaceName;

  text_log.Print(L"lfFaceName = %ls\n",static_cast<const wchar_t*>(sFaceName));
  text_log.Print("lfHeight = %d\n", logfont->lfHeight);
  text_log.Print("lfWidth = %d\n", logfont->lfWidth);
  text_log.Print("lfEscapement = %d.%d degrees\n", (logfont->lfEscapement)/10, (logfont->lfEscapement)%10);
  text_log.Print("lfOrientation = %d.%d degrees\n",  (logfont->lfOrientation)/10, (logfont->lfOrientation)%10);

  ON_String s;

  switch (logfont->lfWeight)
  {
  case FW_DONTCARE: s = L"FW_DONTCARE"; break;
  case FW_THIN: s = "FW_THIN"; break;
  case FW_EXTRALIGHT: s = "FW_EXTRALIGHT"; break; //  = FW_ULTRALIGHT
  case FW_LIGHT: s = "FW_LIGHT"; break;
  case FW_NORMAL: s = "FW_NORMAL"; break; //  = FW_REGULAR
  case FW_MEDIUM: s = "FW_MEDIUM"; break;
  case FW_SEMIBOLD: s = "FW_SEMIBOLD"; break; //  = FW_DEMIBOLD
  case FW_BOLD: s = "FW_BOLD"; break;
  case FW_EXTRABOLD: s = "FW_EXTRABOLD"; break; //  = FW_ULTRABOLD
  case FW_HEAVY: s = "FW_HEAVY"; break; //  = FW_BLACK
  default: s = ON_String::EmptyString; break;
  }
  if (s.IsNotEmpty())
    s += " = ";
  s += ON_String::FormatToString("%d", logfont->lfWeight);
  text_log.Print("lfWeight = %s\n", static_cast<const char*>(s));


  text_log.Print("lfItalic = %s\n", logfont->lfItalic ? "true" : "false");
  text_log.Print("lfUnderline = %s\n", logfont->lfUnderline ? "true" : "false");
  text_log.Print("lfStrikeOut = %s\n", logfont->lfStrikeOut ? "true" : "false");

  s = Internal_WindowsLogFontCharSet(logfont->lfCharSet);
  text_log.Print("lfCharSet = %s\n", static_cast<const char*>(s));

  s = Internal_WindowsLogFontOutPrecision(logfont->lfOutPrecision);
  text_log.Print("lfOutPrecision = %s\n", static_cast<const char*>(s));

  s = Internal_WindowsLogFontClipPrecision(logfont->lfClipPrecision);
  text_log.Print("lfClipPrecision = %s\n", static_cast<const char*>(s));

  s = Internal_WindowsLogFontQuality(logfont->lfQuality);
  text_log.Print("lfQuality = %s\n", static_cast<const char*>(s));

  const unsigned int pitch = (logfont->lfPitchAndFamily & 0x03);
  const unsigned int family = (logfont->lfPitchAndFamily & 0xF);
  switch (pitch)
  {
  case DEFAULT_PITCH: s = "DEFAULT_PITCH"; break;
  case FIXED_PITCH: s = "FIXED_PITCH"; break;
  case VARIABLE_PITCH: s = "VARIABLE_PITCH"; break;
  default: s = ON_String::FormatToString("0x%02x", pitch);
  };
  s += " | ";
  s += Internal_WindowsLogFontFamily(logfont->lfPitchAndFamily);
  if (s.IsNotEmpty())
    s += L" = ";
  s += ON_wString::FormatToString(L"0x%02x", (unsigned int)logfont->lfPitchAndFamily);
  text_log.Print("lfPitchAndFamily = %s\n", static_cast<const char*>(s));
  text_log.PopIndent();
}

void ON_Font::DumpTextMetric(
  const TEXTMETRIC* tm,
  ON_TextLog& text_log
)
{
  if (nullptr == tm)
  {
    text_log.Print("TEXTMETRIC = nullptr\n");
    return;
  }

  text_log.Print("TEXTMETRIC\n");
  text_log.PushIndent();

  text_log.Print("tmHeight = %d\n",tm->tmHeight);
  text_log.Print("tmAscent = %d\n",tm->tmAscent);
  text_log.Print("tmDescent = %d\n",tm->tmDescent);

  text_log.Print("tmInternalLeading = %d\n",tm->tmInternalLeading);
  text_log.Print("tmExternalLeading = %d\n",tm->tmExternalLeading);

  text_log.Print("tmAveCharWidth = %d\n",tm->tmAveCharWidth);
  text_log.Print("tmMaxCharWidth = %d\n",tm->tmMaxCharWidth);

  text_log.Print("tmWeight = %d\n",tm->tmWeight);
  text_log.Print("tmOverhang = %d\n",tm->tmOverhang);

  text_log.Print("tmDigitizedAspectX = %d\n",tm->tmDigitizedAspectX);
  text_log.Print("tmDigitizedAspectY = %d\n",tm->tmDigitizedAspectY);

  text_log.Print(L"tmFirstChar = U+%04X\n",(ON__UINT32)tm->tmFirstChar);
  text_log.Print(L"tmLastChar = U+%04X\n",(ON__UINT32)tm->tmLastChar);
  text_log.Print(L"tmDefaultChar = U+%04X\n",(ON__UINT32)tm->tmDefaultChar);
  text_log.Print(L"tmBreakChar = U+%04X\n",(ON__UINT32)tm->tmBreakChar);

  text_log.Print("tmItalic = %s\n",tm->tmItalic?"true":"false");
  text_log.Print("tmUnderlined = %s\n",tm->tmUnderlined?"true":"false");
  text_log.Print("tmStruckOut = %s\n",tm->tmStruckOut?"true":"false");

  ON_String s;

  const BYTE pitch = (0x0F & tm->tmPitchAndFamily);
  if (0 != (TMPF_FIXED_PITCH & pitch))
  {
    if (s.IsNotEmpty())
      s += " | ";
    s += "TMPF_FIXED_PITCH";
  }
  if (0 != (TMPF_VECTOR & pitch))
  {
    if (s.IsNotEmpty())
      s += " | ";
    s += "TMPF_VECTOR";
  }
  if (0 != (TMPF_TRUETYPE & pitch))
  {
    if (s.IsNotEmpty())
      s += " | ";
    s += "TMPF_TRUETYPE";
  }
  if (0 != (TMPF_DEVICE & pitch))
  {
    if (s.IsNotEmpty())
      s += " | ";
    s += "TMPF_DEVICE";
  }

  if (s.IsNotEmpty())
    s += " | ";
  s += Internal_WindowsLogFontFamily(tm->tmPitchAndFamily);
  if (s.IsNotEmpty())
    s += " = ";
  s += ON_wString::FormatToString(L"0x%02X", (unsigned int)tm->tmPitchAndFamily);
  text_log.Print("tmPitchAndFamily = %s\n", static_cast<const char*>(s));


  s = Internal_WindowsLogFontCharSet(tm->tmCharSet);
  text_log.Print("tmCharSet = %s\n", static_cast<const char*>(s));

  text_log.PopIndent();
}

const ON_wString ON_WindowsDWriteFontInformation::FamilyName() const
{
  return m_loc_family_name.IsNotEmpty() ? m_loc_family_name : m_en_family_name;
}

const ON_wString ON_WindowsDWriteFontInformation::FaceName() const
{
  return m_loc_face_name.IsNotEmpty() ? m_loc_face_name : m_en_face_name;
}

const ON_wString ON_WindowsDWriteFontInformation::PostScriptName() const
{
  return m_loc_postscript_name.IsNotEmpty() ? m_loc_postscript_name : m_en_postscript_name;
}

const ON_wString ON_WindowsDWriteFontInformation::WindowsLogfontName() const
{
  return m_loc_gdi_family_name.IsNotEmpty() ? m_loc_gdi_family_name : m_en_gdi_family_name;
}

int ON_WindowsDWriteFontInformation::CompareFamilyName(
  const ON_WindowsDWriteFontInformation* lhs,
  const ON_WindowsDWriteFontInformation* rhs)
{
  if (lhs == rhs) return 0;
  if (nullptr == lhs) return 1;
  if (nullptr == rhs) return -1;
  return ON_wString::CompareOrdinal(lhs->m_loc_family_name, rhs->m_loc_family_name, true);
}

int ON_WindowsDWriteFontInformation::CompareFamilyNameFaceNameWeightStretchStyle(
  const ON_WindowsDWriteFontInformation* lhs, 
  const ON_WindowsDWriteFontInformation* rhs)
{
  if (lhs == rhs) return 0;
  if (nullptr == lhs) return 1;
  if (nullptr == rhs) return -1;
  int rc = ON_wString::CompareOrdinal(lhs->FamilyName(), rhs->FamilyName(), true);
  if (0 != rc)
    return rc;
  rc = ON_wString::CompareOrdinal(lhs->FaceName(), rhs->FaceName(), true);
  if (0 != rc)
    return rc;
  rc = lhs->m_weight - rhs->m_weight;
  if (0 != rc)
    return rc;
  rc = lhs->m_stretch - rhs->m_stretch;
  if (0 != rc)
    return rc;
  rc = lhs->m_style - rhs->m_style;
  if (0 != rc)
    return rc;
  return 0;
}

int ON_WindowsDWriteFontInformation::ComparePostScriptName(
  const ON_WindowsDWriteFontInformation* lhs, 
  const ON_WindowsDWriteFontInformation* rhs)
{
  if (lhs == rhs) return 0;
  if (nullptr == lhs) return 1;
  if (nullptr == rhs) return -1;
  return ON_wString::CompareOrdinal(lhs->PostScriptName(), rhs->PostScriptName(), true);
}


unsigned char ON_Font::WindowsLogfontCharSetFromLogfont(
  const LOGFONT* logfont,
  bool bValidateSymbolFont
)
{
  for (;;)
  {
    if (nullptr == logfont)
      break;
    if (0 == logfont->lfFaceName[0])
      break;
    const int logfont_capacity = (int)(sizeof(logfont->lfFaceName) / sizeof(logfont->lfFaceName[0]));
    if ( ON_wString::EqualOrdinal(L"CityBlueprint", -1, logfont->lfFaceName, logfont_capacity, true))
       return ON_Font::WindowsConstants::logfont_symbol_charset;
    if ( ON_wString::EqualOrdinal(L"CountryBlueprint", -1, logfont->lfFaceName, logfont_capacity, true))
       return ON_Font::WindowsConstants::logfont_symbol_charset;
    if (ON_Font::WindowsConstants::logfont_symbol_charset != logfont->lfCharSet)
      break;
    if (bValidateSymbolFont
      && ON_Font::WindowsConstants::logfont_symbol_charset != ON_Font::WindowsLogfontCharSetFromFaceName(logfont->lfFaceName)
      )
      break;
    return ON_Font::WindowsConstants::logfont_symbol_charset;
  }

  return ON_Font::WindowsConstants::logfont_default_charset;
}




ON_Font::ON_Font(
  ON_Font::FontType font_type,
  const class ON_WindowsDWriteFontInformation& dwrite_font_information
)
  : m_runtime_serial_number((ON_Font::FontType::ManagedFont == font_type)?++ON_Font::__runtime_serial_number_generator:0)
  , m_font_type(font_type)
{
  const LOGFONT logfont = dwrite_font_information.m_gdi_interop_logfont;
  m_windows_logfont_weight = logfont.lfWeight;
  m_font_weight = ON_Font::WeightFromWindowsLogfontWeight(m_windows_logfont_weight);
  m_apple_font_weight_trait = ON_Font::AppleFontWeightTraitFromWeight(m_font_weight);
  m_point_size = 0.0;

  m_font_style = (0 != logfont.lfItalic) ? ON_Font::Style::Italic : ON_Font::Style::Upright;

  m_font_stretch = ON_Font::FontStretchFromDWriteStretch(dwrite_font_information.m_stretch,ON_Font::Stretch::Medium);

  m_font_bUnderlined = false;
  m_font_bStrikethrough = false;

  m_logfont_charset = ON_Font::WindowsLogfontCharSetFromLogfont(&logfont,false);

  m_font_origin = ON_Font::Origin::WindowsFont;

  m_locale_name = dwrite_font_information.m_prefered_locale;

  m_loc_postscript_name = dwrite_font_information.m_loc_postscript_name;
  m_en_postscript_name = dwrite_font_information.m_en_postscript_name;

  m_loc_family_name = dwrite_font_information.m_loc_family_name;    
  m_en_family_name = dwrite_font_information.m_en_family_name;    

  m_loc_face_name = dwrite_font_information.m_loc_face_name;    
  m_en_face_name = dwrite_font_information.m_en_face_name;    

  m_loc_windows_logfont_name = dwrite_font_information.m_loc_gdi_family_name;
  m_en_windows_logfont_name = dwrite_font_information.m_en_gdi_family_name;
  for(;;)
  {
    // For simulated fonts, the DWrite GDI family name is sometimes too long for a valid logfont name.
    if (
      m_loc_windows_logfont_name.IsNotEmpty() && m_loc_windows_logfont_name.Length() <= 32
      && m_en_windows_logfont_name.IsNotEmpty() && m_en_windows_logfont_name.Length() <= 32
      )
    {
      break;
    }
    if (0 == dwrite_font_information.m_gdi_interop_logfont.lfFaceName[0])
      break;
    // logfont_name[] = logfont lfFaceName we are cetain is null terminated.
    wchar_t logfont_name[1 + (sizeof(dwrite_font_information.m_gdi_interop_logfont.lfFaceName) / sizeof(dwrite_font_information.m_gdi_interop_logfont.lfFaceName[0]))];
    const size_t logfont_name_capacity = (sizeof(logfont_name)/sizeof(logfont_name[0])) - 1;
    memcpy(logfont_name, dwrite_font_information.m_gdi_interop_logfont.lfFaceName, logfont_name_capacity*sizeof(logfont_name[0]));
    logfont_name[logfont_name_capacity] = 0;
    if (m_en_windows_logfont_name.IsEmpty() || m_en_windows_logfont_name.Length() > 32)
      m_en_windows_logfont_name = logfont_name;
    if (m_loc_windows_logfont_name.IsEmpty() || m_loc_windows_logfont_name.Length() > 32)
      m_loc_windows_logfont_name = logfont_name;
    break;
  }


  m_panose1 = dwrite_font_information.m_panose1;

  m_outline_figure_type = dwrite_font_information.m_outline_figure_type;

  this->SetSimulated(
    dwrite_font_information.m_bSimulatedBold,
    false,
    dwrite_font_information.m_bSimulatedOblique,
    dwrite_font_information.m_bSimulatedOther
  );

  if ( ON_Font::FontType::ManagedFont == font_type ||  ON_Font::FontType::InstalledFont == font_type )
  {
    ON_FontGlyphCache* font_cache = ON_FontGlyphCache::New();
#if defined(ON_OS_WINDOWS_GDI)
    font_cache->m_dwrite_font = dwrite_font_information.m_dwrite_font;
    dwrite_font_information.m_dwrite_font->AddRef();
#endif
    if (dwrite_font_information.m_font_metrics.HeightsAreValid())
    {
      font_cache->SetFontMetrics(dwrite_font_information.m_font_metrics);
    }
    m_font_glyph_cache = std::shared_ptr<ON_FontGlyphCache>(font_cache);
  }
}

#endif

bool ON_Font::Write(
  ON_BinaryArchive& file // serialize definition to binary archive
  ) const
{

  if (file.Archive3dmVersion() < 60 
    || file.ArchiveOpenNURBSVersion() < ON_TextStyle::binary_archive_opennurbs_version
    )
  {
    ON_WARNING("This font should probably be an ON_TextStyle.");
    return WriteV5(
      RuntimeSerialNumber(),
      ON_nil_uuid,
      file
      );
  }


  if (!file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,6))
    return false;

  bool rc = false;
  for (;;)
  {
    // version 1.0
    unsigned int fc = FontCharacteristicsAsUnsigned();
    if (!file.WriteInt(fc))
      break;

    // Windows LOGFONT.lfFaceName
    if ( !file.WriteWideString(WindowsLogfontName()) )
      break;

    // PostScript name
    if (!file.WriteString(PostScriptName()))
      break;

    // version 1.1 added font_description August 2016
    ON_wString obsolete_font_description = PostScriptName();
    if (obsolete_font_description.IsEmpty())
      obsolete_font_description = FamilyName();
    if (obsolete_font_description.IsEmpty())
      obsolete_font_description = WindowsLogfontName();
    if (!file.WriteString(obsolete_font_description))
      break;

    // version 1.2 added m_windows_logfont_weight and m_apple_font_weight_trait
    if (!file.WriteInt(m_windows_logfont_weight))
      break;

    if (!file.WriteDouble(m_apple_font_weight_trait))
      break;

    // version 1.3 added additional m_point_size and m_LOGFONT_* values.
    if (!file.WriteDouble(m_point_size))
      break;

    const bool bOBSOLETEBool = false;
    if (!file.WriteBool(bOBSOLETEBool))
      break;
    
    // version 1.4 explicit Family name
    if (!file.WriteString(FamilyName()))
      break;

    // version 1.5 explicit names in loc and en and PANOSE1 settings
    if (!file.WriteString(m_locale_name))
      break;

    bool bFontNamesSaved = false;
    for(;;)
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
      // All fonts in the Family with MISSING_FONT_TEST_valid_family_name 
      // will be saved as a family named missing_family_name.
      const ON_wString MISSING_FONT_TEST_valid_font_family_name(L"Courier New");
      if (MISSING_FONT_TEST_valid_font_family_name == FamilyName() && FaceName().IsNotEmpty())
      {
        // Write Missing Font names
        const ON_wString missing_font_family_name(L"Missing Font Test");
        const ON_wString missing_font_face_name(FaceName());
        const ON_wString missing_font_logfont_name(missing_font_family_name);
        ON_wString missing_font_postscript_name = missing_font_family_name + L"-" + missing_font_face_name;
        missing_font_postscript_name.Remove(ON_wString::Space);
        // local and english postscript name
        if (!file.WriteString(missing_font_postscript_name))
          break;
        if (!file.WriteString(missing_font_postscript_name))
          break;
        // local and english logfont name
        if (!file.WriteString(missing_font_logfont_name))
          break;
        if (!file.WriteString(missing_font_logfont_name))
          break;
        // local and english family name
        if (!file.WriteString(missing_font_family_name))
          break;
        if (!file.WriteString(missing_font_family_name))
          break;
        // local and english face name
        if (!file.WriteString(missing_font_face_name))
          break;
        if (!file.WriteString(missing_font_face_name))
          break;

        bFontNamesSaved = true;
        break;
      }
#endif

      // write correct names
      if (!file.WriteString(m_loc_postscript_name))
        break;
      if (!file.WriteString(m_en_postscript_name))
        break;
      if (!file.WriteString(m_loc_windows_logfont_name))
        break;
      if (!file.WriteString(m_en_windows_logfont_name))
        break;
      if (!file.WriteString(m_loc_family_name))
        break;
      if (!file.WriteString(m_en_family_name))
        break;
      if (!file.WriteString(m_loc_face_name))
        break;
      if (!file.WriteString(m_en_face_name))
        break;

      bFontNamesSaved = true;
      break;
    }

    if (false == bFontNamesSaved)
      break; // errors writing font names


    if (!m_panose1.Write(file))
      break;

    // version 1.6 rich text quartet member (regular/bold/italic/bold-italic)
    const unsigned char quartet_member_as_unsigned = static_cast<unsigned char>(this->m_quartet_member);
    if (!file.WriteByte(1,&quartet_member_as_unsigned))
      break;

    rc = true;
    break;
  }

  if (!file.EndWrite3dmChunk())
    rc = false;

  return rc;
}

bool ON_Font::WriteV5(
  int V5_font_index,
  ON_UUID V5_font_id,
  ON_BinaryArchive& file // serialize definition to binary archive
  ) const
{
  bool rc = file.Write3dmChunkVersion(1, 2);
  while(rc)
  {
    rc = file.Write3dmReferencedComponentIndex(ON_ModelComponent::Type::TextStyle,V5_font_index);
    if(!rc) 
      break;

    // Mac Rhino 5 uses the V5 "m_font_description" field to store Apple font names because
    // there was no other appropriate place to save the information in a V5 file format.
    ON_wString description = PostScriptName();
    if (description.IsEmpty())
      description = FamilyName();
    if (description.IsEmpty())
      description = WindowsLogfontName();

    rc = file.WriteString(description);
    if(!rc) 
      break;

    {
      // 18 October 2002 Dale Lear:
      //   This is a result of a bug in old code. 
      //   The Windows LOGFONT.lfFaceName was written as an array of 64 unsigned shorts.
      unsigned short sh[64];
      memset(sh, 0, sizeof(sh));
      const ON_wString logfont_name = WindowsLogfontName();
      const int logfont_name_len = logfont_name.Length();
      const wchar_t* logfont_name_str = static_cast<const wchar_t*>(logfont_name);

      int i;
      for(i = 0; i < 64 && i < logfont_name_len; i++)
        sh[i] = (unsigned short)(logfont_name_str[i]);
      rc = file.WriteShort(64, sh);
      if(!rc) break;
    }

    // 1.1 additions
    int windows_logfont_weight = ON_Font::WindowsLogfontWeightFromWeight(m_font_weight);
    if (file.Archive3dmVersion() < 60)
    {
      // V5 and earlier files had 4 permitted weights
      //  Light  = 300
      //  Normal = 400
      //  Medium = 500
      //  Bold   = 700
      if ( windows_logfont_weight <= 0 )
        windows_logfont_weight = 400;
      if ( windows_logfont_weight < 350 )
        windows_logfont_weight = 300;
      else if ( windows_logfont_weight < 450 )
        windows_logfont_weight = 400;
      else if ( windows_logfont_weight < 600 )
        windows_logfont_weight = 500;
      else if ( windows_logfont_weight <= 1000 )
        windows_logfont_weight = 700;
      else
        windows_logfont_weight = 400;
    }
    
    rc = file.WriteInt(static_cast<int>(windows_logfont_weight));
    if(!rc) break;
    rc = file.WriteInt(ON_Font::Style::Italic == m_font_style);
    if(!rc) break;
    rc = file.WriteDouble(ON_FontMetrics::DefaultLineFeedRatio);
    if(!rc) break;

    // 1.2 addition
    rc = file.WriteUuid(V5_font_id);
    if(!rc) break;

    break;
  }

  return rc;
}

bool ON_Font::Read(
  ON_BinaryArchive& file // restore definition from binary archive
  )
{
  // On September 16, 2015 the "V5" ON_Font was split into
  //   ON_TextStyle (a document object) and
  //   ON_Font (a current runtime resource)
  *this = ON_Font::Unset;

  ON__UINT32 typecode = 0;
  ON__INT64 big_value = 0;
  if (file.Archive3dmVersion() < 60
    || file.ArchiveOpenNURBSVersion() < ON_TextStyle::binary_archive_opennurbs_version
    || (file.PeekAt3dmBigChunkType(&typecode,&big_value) && 1 == typecode)
    )
  {
    ON_WARNING("Should probably be reading an ON_TextStyle");
    int font_index = -1;
    ON_UUID font_id = ON_nil_uuid;
    return ReadV5(
      file,
      &font_index,
      &font_id
      );
  }

  int major_verision = 0;
  int minor_verision = 0;
  if (!file.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK, &major_verision, &minor_verision))
  {
    *this = ON_Font::Default;
    return false;
  }

  bool rc = false;
  for (;;)
  {
    if ( 1 != major_verision )
      break;

    unsigned int fc = 0;
    if (!file.ReadInt(&fc))
      break;

    ON_Font::Weight font_weight = ON_Font::Weight::Normal;
    ON_Font::Stretch font_stretch = ON_Font::Stretch::Medium;
    ON_Font::Style font_style = ON_Font::Style::Upright;
    bool bUnderlined = false;
    bool bStrikethrough = false;
    ON_Font::Internal_GetFontCharacteristicsFromUnsigned(
      fc,
      font_weight,
      font_stretch,
      font_style,
      bUnderlined,
      bStrikethrough
    );
      
    ON_wString windows_logfont_name;
    if ( !file.ReadWideString(windows_logfont_name) )
      break;

    ON_wString postscript_name;
    if (!file.ReadString(postscript_name))
      break;

    if (ON::RuntimeEnvironment::Windows == file.ArchiveRuntimeEnvironment())
    {
      // Dale Lear - August 16, 2016.
      // The value of m_postscript_font_name is damaged in many archives written by Windows Rhino.
      // It has values like "Font 01". So, I'm going to clean it
      // during read and we will get it right going forward.
      // This value is not saved in V5 files.
      const unsigned int broken_apple_font_name_version = ON_VersionNumberConstruct(6, 0, 2016, 8, 18, 0);
      const unsigned int archive_version = file.Archive3dmVersion();
      const unsigned int archive_opennurbs_version = file.ArchiveOpenNURBSVersion();
      if (
        archive_version < 60
        || (60 == archive_version && archive_opennurbs_version <= broken_apple_font_name_version)
        )
      {
        postscript_name = ON_wString::EmptyString;
      }
    }

    const ON_Font* installed_font = ON_Font::InstalledFontList().FromNames(
      postscript_name,
      windows_logfont_name,
      windows_logfont_name,
      nullptr,
      font_weight,
      font_stretch,
      font_style,
      false,
      true
    );

    if (nullptr != installed_font)
    {
      *this = *installed_font;
      this->m_font_bUnderlined = bUnderlined;
      this->m_font_bStrikethrough = bStrikethrough;
    }
    else
    {
      // Either the information in the .3dm file is junk or the font is not installed on this device.
      if (windows_logfont_name.IsNotEmpty())
        SetWindowsLogfontName(windows_logfont_name);
      else
        *this = ON_Font::Default;
      Internal_SetFontCharacteristicsFromUnsigned(fc);
      if (postscript_name.IsNotEmpty())
      {
        m_loc_postscript_name = postscript_name;
        m_en_postscript_name = postscript_name;
      }
    }

    if (minor_verision <= 0)
    {
      rc = true;
      break;
    }

    // version 1.1 added m_font_description August 2016
    ON_wString obsolete_font_description;
    if ( !file.ReadString(obsolete_font_description) )
      break;

    if (minor_verision <= 1)
    {
      // m_windows_logfont_weight and  m_apple_font_weight_trait
      // are set above in the call to SetFontCharacteristicsFromUnsigned().
      rc = true;
      break;
    }

    // version 1.2 added m_windows_logfont_weight and m_apple_font_weight_trait
    int windows_logfont_weight = 0;
    if (!file.ReadInt(&windows_logfont_weight))
      break;
    const bool bSetLogfontWeight
      =
#if defined(ON_RUNTIME_WIN)
      (nullptr == installed_font)
#else
      (ON::RuntimeEnvironment::Windows == file.ArchiveRuntimeEnvironment())
#endif
    ;
    if (bSetLogfontWeight)
      m_windows_logfont_weight = windows_logfont_weight;

    double apple_font_weight_trait = 0.0;
    if (!file.ReadDouble(&apple_font_weight_trait))
      break;
    const bool bSetAppleFontWeightTrait
      =
#if defined(ON_RUNTIME_WIN)
      (ON::RuntimeEnvironment::Apple == file.ArchiveRuntimeEnvironment())
#else
      (nullptr == installed_font)
#endif
    ;
    if (bSetAppleFontWeightTrait)
      m_apple_font_weight_trait = apple_font_weight_trait;
    
    if (minor_verision <= 2)
    {
      rc = true;
      break;
    }

    // version 1.3 added additional m_point_size and m_LOGFONT_* values.
    if (!file.ReadDouble(&m_point_size))
      break;

    bool bOBSOLETE_Bool = false;
    if (!file.ReadBool(&bOBSOLETE_Bool))
      break;
    if (bOBSOLETE_Bool)
    {
      unsigned char obsolete_c = 0;
      if (!file.ReadChar(&obsolete_c))
        break;
      if (!file.ReadChar(&obsolete_c))
        break;
      if (!file.ReadChar(&obsolete_c))
        break;
      if (!file.ReadChar(&obsolete_c))
        break;
      int obsolete_i = 0;
      if (!file.ReadInt(&obsolete_i))
        break;
      if (!file.ReadInt(&obsolete_i))
        break;
      if (!file.ReadInt(&obsolete_i))
        break;
      if (!file.ReadInt(&obsolete_i))
        break;
    }

    if (minor_verision <= 3)
    {
      rc = true;
      break;
    }

    // version 1.4 added explicit Family name
    ON_wString family_name;
    if (!file.ReadString(family_name))
      break;

    if (nullptr == installed_font)
    {
      m_loc_family_name = family_name;
      m_en_family_name = family_name;
    }

    if (minor_verision <= 4)
    {
      rc = true;
      break;
    }

    // version 1.5 explicit names in loc and en and PANOSE1 settings
    if (!file.ReadString(m_locale_name))
      break;
    if (!file.ReadString(m_loc_postscript_name))
      break;
    if (!file.ReadString(m_en_postscript_name))
      break;
    if (!file.ReadString(m_loc_windows_logfont_name))
      break;
    if (!file.ReadString(m_en_windows_logfont_name))
      break;
    if (!file.ReadString(m_loc_family_name))
      break;
    if (!file.ReadString(m_en_family_name))
      break;
    if (!file.ReadString(m_loc_face_name))
      break;
    if (!file.ReadString(m_en_face_name))
      break;
    if (!m_panose1.Read(file))
      break;


    if (minor_verision <= 5)
    {
      rc = true;
      break;
    }

    // version 1.6 rich text quartet member (regular/bold/italic/bold-italic)
    unsigned char quartet_member_as_unsigned = static_cast<unsigned char>(this->m_quartet_member);
    if (!file.ReadByte(1,&quartet_member_as_unsigned))
      break;
    this->m_quartet_member = ON_FontFaceQuartet::MemberFromUnsigned(quartet_member_as_unsigned);

    if (minor_verision <= 6)
    {
      rc = true;
      break;
    }

    rc = true;
    break;
  }

  if (
    false == rc
    || (WindowsLogfontName().IsEmpty()
    && PostScriptName().IsEmpty()
    && FamilyName().IsEmpty())
    )
  {
    *this = ON_Font::Default;
  }

  if (!file.EndRead3dmChunk())
    rc = false;

  return rc;
}

bool ON_Font::ReadV5(
  ON_BinaryArchive& file, // restore definition from binary archive
  int* V5_font_index,
  ON_UUID* V5_font_id
  )
{
  *this = ON_Font::Unset;

  if ( nullptr != V5_font_index )
    *V5_font_index = -1;
  if ( nullptr != V5_font_id )
    *V5_font_id = ON_nil_uuid;
  
  int major_version = 0;
  int minor_version = 0;
  if (!file.Read3dmChunkVersion(&major_version, &minor_version))
  {
    *this = ON_Font::Default;
    return false;
  }

  bool rc = false;

  ON_wString windows_logfont_name;
  ON_wString postscript_name;
  ON_Font::Weight font_weight = ON_Font::Weight::Normal;
  ON_Font::Stretch font_stretch = ON_Font::Stretch::Unset;
  ON_Font::Style font_style = ON_Font::Style::Upright;
  int logfont_weight = 0;

  for (;;)
  {
    if ( 1 != major_version )
      break;
    int i;
    if (!file.ReadInt(&i))
      break;
    if ( nullptr != V5_font_index )
      *V5_font_index = i;

    ON_wString corrupt_information_font_description;
    if (!file.ReadString(corrupt_information_font_description))
      break;

    if ( false == ON_Font::IsNotAppleFontName(corrupt_information_font_description)  )
    {
      if (ON::RuntimeEnvironment::Apple == file.ArchiveRuntimeEnvironment())
      {
        // Files written by Mac Rhino 5 for Mac have the Apple font name stored in this string.
        postscript_name = corrupt_information_font_description;
      }
      else if ( file.ArchiveOpenNURBSVersion() > ON_VersionNumberConstruct(6, 2, 2018, 2, 23, 0) )
      {
        postscript_name = corrupt_information_font_description;
      }
    }
 
    // 18 October 2002 Dale Lear:
    //   This code deals with an old bug.
    //   The Windows LOGFONT.lfFaceName was written as an array of 64 unsigned shorts.
    unsigned short sh[64];
    if (!file.ReadShort(64, sh))
      break;

    wchar_t facename[65];
    for(i = 0; i < 64; i++)
      facename[i] = sh[i];
    facename[64] = 0;
    windows_logfont_name = facename;

    m_logfont_charset = ON_Font::WindowsLogfontCharSetFromFaceName(WindowsLogfontName());
    if (minor_version >= 1)
    {
      if (!file.ReadInt(&logfont_weight))
        break;

      if (logfont_weight >= 100 && logfont_weight <= 1000)
      {
        font_weight = ON_Font::WeightFromWindowsLogfontWeight(logfont_weight);
      }

      int bItalic = 0;
      if (!file.ReadInt(&bItalic))
        break;
      if ( 0 != bItalic )
        font_style = ON_Font::Style::Italic;

      double obsolete_linefeed_ratio = ON_FontMetrics::DefaultLineFeedRatio;
      if (!file.ReadDouble(&obsolete_linefeed_ratio))
        break;

      if (minor_version >= 2)
      {
        ON_UUID uuid = ON_nil_uuid;
        if (!file.ReadUuid(uuid))
          break;
        if ( nullptr != V5_font_id )
          *V5_font_id = uuid;
      }
    }

    rc = true;
    break;
  }

  const ON_Font* installed_font = ON_Font::InstalledFontList().FromNames(
    postscript_name,
    windows_logfont_name,
    nullptr,
    nullptr,
    font_weight,
    font_stretch,
    font_style,
    false,
    true
  );

  if (nullptr != installed_font)
  {
    *this = *installed_font;
  }
  else if (rc)
  {
    SetWindowsLogfontName(windows_logfont_name);
    Internal_SetFontWeightTrio(
      font_weight,
      logfont_weight,
      ON_UNSET_VALUE,
      false
    );
    m_loc_postscript_name = postscript_name;
    m_en_postscript_name = m_loc_postscript_name;
    m_loc_family_name = ON_Font::FamilyNameFromDirtyName(m_loc_windows_logfont_name);
    m_en_family_name = ON_Font::FamilyNameFromDirtyName(m_en_windows_logfont_name);
  }
  else
  {
    *this = ON_Font::Default;
  }

  return rc;
}

unsigned int ON_Font::RuntimeSerialNumber() const
{
  return m_runtime_serial_number;
}

unsigned int ON_Font::ManagedFontSerialNumber() const
{
  if (0 != m_runtime_serial_number)
    return m_runtime_serial_number;
  const ON_Font* mananged_font = this->ManagedFont();
  return (nullptr == mananged_font) ? 0 : mananged_font->RuntimeSerialNumber();
}

#if defined(ON_OS_WINDOWS_GDI)
static
int CALLBACK ON__IsSymbolCharSetFontFaceNameHelper(ENUMLOGFONTEX* lf, NEWTEXTMETRICEX* tm, DWORD font_type, LPARAM)
{
  // If the fontname in the logfont structure has
  // a corresponding symbol font on the system, 
  // set the  lfCharSet member to SYMBOL_CHARSET, 
  // otherwise DEFAULT_CHARSET
  // The input logfont structure may be modified.
  return 7;
}
#endif

unsigned char ON_Font::WindowsLogfontCharSetFromFaceName(
  const wchar_t* face_name
  )
{
  unsigned char logfont_charset = ON_Font::WindowsConstants::logfont_default_charset;


  if( nullptr != face_name && face_name[0] > ON_wString::Space )
  {
    // Problem fonts
    if (ON_wString::EqualOrdinal(L"CityBlueprint", -1, face_name, -1, true))
      return ON_Font::WindowsConstants::logfont_symbol_charset;

    if (ON_wString::EqualOrdinal(L"CountryBlueprint", -1, face_name, -1, true))
      return ON_Font::WindowsConstants::logfont_symbol_charset;

#if defined(ON_OS_WINDOWS_GDI)
    HDC font_hdc = ON_Font::CreateWindowsLogfontDeviceContext();
    if(nullptr != font_hdc)
    {
      // See if there is a font with this facename that has the symbol charset 
      LOGFONT logfont;
      memset(&logfont, 0, sizeof(logfont));
      for(int i = 0; i < LF_FACESIZE && face_name[i]; i++)
        logfont.lfFaceName[i] = face_name[i];

      // Dale lear - set logfont.lfOutPrecision May 2017
      logfont.lfOutPrecision = ON_Font::WindowsConstants::logfont_out_precis;

      // Is it a SYMBOL_CHARSET font?
      logfont.lfCharSet = ON_Font::WindowsConstants::logfont_symbol_charset;
      if (7 == ::EnumFontFamiliesEx(font_hdc, &logfont, (FONTENUMPROC)ON__IsSymbolCharSetFontFaceNameHelper, 0, 0))
      {
        // Yes, this facename is a "symbol font"
        logfont_charset = ON_Font::WindowsConstants::logfont_symbol_charset;
      }
      ON_Font::DeleteWindowsLogfontDeviceContext(font_hdc);
    }
#endif
  }

  return logfont_charset;
}

const ON_wString& ON_Font::FontDescription() const
{
  return
    m_loc_postscript_name.IsNotEmpty()
    ? m_loc_postscript_name
    : m_en_postscript_name;
}

bool ON_Font::SetFontDescriptionForExperts(
  const wchar_t* ignored_parameter
)
{
  // OBSOLETE V6 function.
  return true;
}

const wchar_t* ON_Font::FontDescriptionAsPointer() const
{
  return static_cast<const wchar_t*>(PostScriptName());
}

const ON_wString ON_Font::Description(
) const
{
  return Description(ON_Font::NameLocale::LocalizedFirst, ON_wString::HyphenMinus, ON_wString::Space, true);
}


const ON_wString ON_Font::Description(
  ON_Font::NameLocale name_local,
  wchar_t family_separator,
  wchar_t weight_width_slope_separator,
  bool bIncludeUndelinedAndStrikethrough
) const
{
  // Do not change bIncludeNotOnDevice to false.
  // If you have a situation where you do not want the
  // missing font description, then use the override that
  // has bIncludeNotOnDevice as a parameter.
  const bool bIncludeNotOnDevice = true;

  return this->Description(
    name_local,
    family_separator,
    weight_width_slope_separator,
    bIncludeUndelinedAndStrikethrough,
    bIncludeNotOnDevice
  );
}

const ON_wString ON_Font::Description(
  ON_Font::NameLocale name_local,
  wchar_t family_separator,
  wchar_t weight_width_slope_separator,
  bool bIncludeUndelinedAndStrikethrough,
  bool bIncludeNotOnDevice
) const
{
  ON_wString description;

  if (bIncludeNotOnDevice && this->IsManagedSubstitutedFont())
  {
    description += ON_wString(L"[Not on device] ");
  }

  ON_wString family_name = FamilyName();
  family_name.TrimLeftAndRight();
  ON_wString logfont_name = WindowsLogfontName();
  logfont_name.TrimLeftAndRight();
  if (family_name.IsEmpty() && logfont_name.IsNotEmpty())
  {
    // LOGFONT (width-weight-slant)
    description += logfont_name;

    const ON_wString wws = this->WidthWeightSlantDescription();
    if (wws.IsNotEmpty())
    {
      description += ON_wString(L" (");
      description += wws;
      description += ON_wString(L")");
    }
  }
  else if (family_name.IsNotEmpty() )
  {
    // family face
    description += family_name;
    ON_wString face_name = FaceName();
    face_name.TrimLeftAndRight();
    if ( face_name.IsNotEmpty() )
    {
      description += ON_wString(L" ");
      description += face_name;
    }
  }
  else
  {
    ON_wString postscript_name = PostScriptName();
    postscript_name.TrimLeftAndRight();
    if (postscript_name.IsNotEmpty())
      description += postscript_name;
  }

  if (description.IsEmpty())
    description = this->WidthWeightSlantDescription();

  if (description.IsNotEmpty())
  {
    const bool bUnderlined = IsUnderlined();
    const bool bStrikethrough = IsStrikethrough();
    if (bUnderlined && bStrikethrough)
      description += ON_wString(L" (underlined,strikethrough)");
    else if (bUnderlined)
      description += ON_wString(L" (underlined)");
    else if (bStrikethrough)
      description += ON_wString(L" (strikethrough)");
  }

  return description;
}

double ON_Font::LinefeedRatio() const
{
  return ON_FontMetrics::DefaultLineFeedRatio;
}

bool ON_Font::HasUnsetProperties(
    bool bCheckFamilyName,
    bool bCheckPostScriptName
) const
{
  if (ON_Font::Style::Unset == m_font_style)
    return true;
  if (ON_Font::Weight::Unset == m_font_weight)
    return true;
  if (ON_Font::Stretch::Unset == m_font_stretch)
    return true;

  if (bCheckFamilyName && FamilyName().IsEmpty() && WindowsLogfontName().IsEmpty())
    return true;

  if (bCheckPostScriptName && PostScriptName().IsEmpty())
    return true;

  return false;
}

unsigned int ON_Font::SetUnsetProperties(
  const ON_Font& source,
  bool bUpdateDescription
)
{
  if (false == ON_FONT_MODIFICATION_PERMITTED)
    return 0;

  unsigned int changed_property_count = 0;

  if (ON_Font::Weight::Unset == m_font_weight
    && ON_Font::Weight::Unset != source.m_font_weight
    )
  {
    m_windows_logfont_weight = source.m_windows_logfont_weight;
    m_apple_font_weight_trait = source.m_apple_font_weight_trait;
    m_font_weight = source.m_font_weight;
    changed_property_count++;
  }

  if (ON_Font::Style::Unset == m_font_style
    && ON_Font::Style::Unset == source.m_font_style
    )
  {
    m_font_style = source.m_font_style;
    changed_property_count++;
  }

  if (ON_Font::Stretch::Unset == m_font_stretch
    && ON_Font::Stretch::Unset != source.m_font_stretch
    )
  {
    m_font_stretch = source.m_font_stretch;
    changed_property_count++;
  }

  const bool bEqualWeightStretch
    = ON_Font::Weight::Unset != m_font_weight
    && ON_Font::Stretch::Unset != m_font_stretch
    && m_font_weight == source.m_font_weight
    && m_font_stretch == source.m_font_stretch
    ;

  const bool bEqualWeightStretchStyle 
    = bEqualWeightStretch
    && ON_Font::Style::Unset != m_font_style
    && m_font_style == source.m_font_style;

  bool bSameFamily = ON_Font::EqualFontFamily(this, &source);

  bool bCopyFamilyName = false;
  bool bCopyLOGFONTFaceName = false;
  bool bCopyPostScriptName = false;
  if ( FamilyName().IsEmpty() && WindowsLogfontName().IsEmpty() && PostScriptName().IsEmpty() )
  {
    bCopyFamilyName = source.FamilyName().IsNotEmpty();
    bCopyLOGFONTFaceName = source.WindowsLogfontName().IsNotEmpty();
    bCopyPostScriptName = source.PostScriptName().IsNotEmpty();
  }
  else if ( bSameFamily )
  {

    // at least one of m_family_name or m_face_name is set.
    bCopyFamilyName = FamilyName().IsEmpty();

    // If "this" and source have the same m_family_name[], weight, and stretch, 
    // then copy source.m_face_name. 
    //
    // NOTE WELL:
    //   Both "this" and source must have the same weight and stretch because 
    //   is is common for LOGFONT name to be used to distigush between weight
    //   and/or stretch in the same family.
    //   Generally, this situation is a result of LOGFONT GDI restrictions
    //   and occures when a family has more than the four standard faces
    //   (regular, bold, italic, bold-italic).
    //   Example:
    //      Family = "Arial"
    //        LOGFONTs face names include "Arial", "Arial Narrow" (different stretch), "Arial Black" (different weight)
    //      Family = "Segoe UI"
    //        Many LOGFONTs with various weights and stretches.
    bCopyLOGFONTFaceName
      = source.WindowsLogfontName().IsNotEmpty()
      && bEqualWeightStretch
      ;

    bCopyPostScriptName =
      source.PostScriptName().IsNotEmpty()
      && bEqualWeightStretchStyle
      ;
  }

  if (bCopyFamilyName)
  {
    m_loc_family_name = source.m_loc_family_name;
    m_en_family_name = source.m_en_family_name;
    m_loc_face_name = source.m_loc_face_name;
    m_en_face_name = source.m_en_face_name;
    changed_property_count++;
  }

  if (bCopyLOGFONTFaceName)
  {
    m_loc_windows_logfont_name = source.m_loc_windows_logfont_name;
    m_en_windows_logfont_name = source.m_en_windows_logfont_name;
    changed_property_count++;
  }

  // The PostScript name identifies the complete face (family, weight, stretch, style).
  if ( bCopyPostScriptName)
  {
    m_loc_postscript_name = source.m_loc_postscript_name;
    m_en_postscript_name = source.m_en_postscript_name;
    changed_property_count++;
  }
  
  if (changed_property_count > 0)
  {
    m_simulated = 0;
    m_managed_installed_font_and_bits = 0;
    Internal_AfterModification();
  }

  return changed_property_count;
}

bool ON_Font::SetFontFaceName(
  const wchar_t* windows_logfont_name
)
{
  return SetWindowsLogfontName(windows_logfont_name);
}

bool ON_Font::SetFamilyName(
  const wchar_t* family_name
)
{
  ON_wString local_family_name = ON_Font::FamilyNameFromDirtyName(family_name);
  local_family_name.TrimLeftAndRight();
  family_name = local_family_name;

  if ( ON_wString::EqualOrdinal(family_name, FamilyName(), false) )
  {
    return true;
  }

  if ( false == ON_FONT_MODIFICATION_PERMITTED )
    return false;  
  
  Internal_ClearName(true, true, true, true);
  
  m_logfont_charset = ON_Font::WindowsConstants::logfont_default_charset;

  m_loc_family_name = family_name;  
  m_en_family_name = m_loc_family_name;  

  Internal_AfterModification();
  return true;
}

bool ON_Font::SetWindowsLogfontName(
  const wchar_t* windows_logfont_name
  )
{
  if (false == ON_Font::IsValidFaceName(windows_logfont_name))
    return false;

  const ON_Font::Weight font_weight = ON_Font::Weight::Normal;
  const ON_Font::Style font_style = ON_Font::Style::Upright;
  const ON_Font::Stretch font_stretch = ON_Font::Stretch::Medium;

  const ON_Font* installed_font =
    ON_Font::InstalledFontList().FromNames(
      nullptr,
      windows_logfont_name,
      nullptr,
      nullptr,
      font_weight,
      font_stretch,
      font_style,
      false,
      false
    );

  if (nullptr != installed_font)
  {
    *this = *installed_font;
  }
  else
  {
    const unsigned char logfont_charset = ON_Font::WindowsLogfontCharSetFromFaceName(windows_logfont_name);

    const ON_wString family_name = ON_Font::FamilyNameFromDirtyName(windows_logfont_name);

    if (
      ON_wString::EqualOrdinal(windows_logfont_name, m_loc_windows_logfont_name, false)
      && family_name == m_loc_family_name
      && font_weight == m_font_weight
      && font_style == m_font_style
      && font_stretch == m_font_stretch
      && logfont_charset == m_logfont_charset
      && ON_Font::Origin::Unknown == m_font_origin
      )
    {
      return true;
    }

    if (false == ON_FONT_MODIFICATION_PERMITTED)
      return false;

    // TODO - better support for generating PostScript names from LOGFONT.lfFaceNames
    //  This code at least handles the 4 most common names passed to this setter.
    if (ON_wString::EqualOrdinal(L"Arial", windows_logfont_name, true))
      m_loc_postscript_name = L"ArialMT";
    else if (ON_wString::EqualOrdinal(L"Segoe UI", windows_logfont_name, true)
      || ON_wString::EqualOrdinal(L"SegoeUI", windows_logfont_name, true))
    {
      m_loc_postscript_name = L"SegoeUI";
    }
    else if (ON_wString::EqualOrdinal(L"Helvetica Neue", windows_logfont_name, true)
      || ON_wString::EqualOrdinal(L"HelveticaNeue", windows_logfont_name, true))
      m_loc_postscript_name = L"HelveticaNeue";
    else if (ON_wString::EqualOrdinal(L"Helvetica", windows_logfont_name, true))
      m_loc_postscript_name = L"Helvetica";
    else
      m_loc_postscript_name = ON_wString::EmptyString;

    m_en_postscript_name = m_loc_postscript_name;

    m_loc_family_name = family_name;
    m_en_family_name = m_loc_family_name;

    m_loc_windows_logfont_name = windows_logfont_name;
    m_en_windows_logfont_name = m_loc_windows_logfont_name;

    m_logfont_charset = logfont_charset;
    m_font_weight = font_weight;
    m_font_style = font_style;
    m_font_stretch = font_stretch;
    m_font_origin = ON_Font::Origin::Unknown;
  }
  
  Internal_AfterModification();

  return true;
}

const wchar_t* ON_Font::FontFaceName() const
{
  // Was never a "real" face name. 
  // Always returned a value from or used in a Windows GDI LOGFONT.lfFaceName[].
  return
    m_loc_windows_logfont_name.IsNotEmpty()
    ? static_cast<const wchar_t*>(m_loc_windows_logfont_name)
    : static_cast<const wchar_t*>(m_en_windows_logfont_name);
}

const wchar_t* ON_Font::WindowsLogfontNameAsPointer() const
{
  return 
    m_loc_windows_logfont_name.IsNotEmpty()
    ? static_cast<const wchar_t*>(m_loc_windows_logfont_name)
    : static_cast<const wchar_t*>(m_en_windows_logfont_name);
}

ON_Font::Weight ON_Font::FontWeight() const
{
  return m_font_weight;
}

bool ON_Font::IsLight() const
{
  const int font_weight = ON_Font::WindowsLogfontWeightFromWeight(m_font_weight);
  const int normal_weight = ON_Font::WindowsLogfontWeightFromWeight(ON_Font::Weight::Normal);
  return (font_weight < normal_weight && m_font_weight != ON_Font::Weight::Unset);
}

bool ON_Font::IsNormalWeight() const
{
  return (ON_Font::Weight::Normal == m_font_weight || ON_Font::Weight::Medium == m_font_weight);
}

bool ON_Font::IsBold() const
{
  return ON_Font::IsBoldWeight(m_font_weight);
}

bool ON_Font::IsItalic() const
{
  return (ON_Font::Style::Italic == m_font_style);
}

bool ON_Font::IsUpright() const
{
  return (ON_Font::Style::Upright == m_font_style);
}

bool ON_Font::IsItalicOrOblique() const
{
  return (ON_Font::Style::Italic == m_font_style || ON_Font::Style::Oblique == m_font_style);
}

bool ON_Font::IsOblique()
{
  return (ON_Font::Style::Oblique == m_font_style);
}

void ON_Font::Internal_AfterModification(
)
{
  // This occures when a characteristic like PostScriptName(), weight, facename, style is changed
  // on a font that was original set from complete platform information.
  // It means the ON_Font may or may not have valid settings in platform specific
  // fields. In particular the Apple font name is typically no longer valid.
  if (ON_Font::Origin::Unset != m_font_origin && ON_Font::Origin::Unknown != m_font_origin)
    m_font_origin = ON_Font::Origin::Unknown;
  m_panose1 = ON_PANOSE1::Zero;
  m_simulated = 0;
  m_font_glyph_cache.reset();
}
void ON_Font::Internal_ClearAllNames()
{
  Internal_ClearName(true, true, true, true);
}

void ON_Font::Internal_ClearName(
  bool bClearFamilyName,
  bool bClearFaceName,
  bool bClearPostScriptName,
  bool bClearWindowsLogfontName
)
{
  if (bClearFamilyName)
  {
    m_loc_family_name = ON_wString::EmptyString;
    m_en_family_name = ON_wString::EmptyString;
  }
  if (bClearFaceName)
  {
    m_loc_face_name = ON_wString::EmptyString;
    m_en_face_name = ON_wString::EmptyString;
  }
  if (bClearPostScriptName)
  {
    m_loc_postscript_name = ON_wString::EmptyString;
    m_en_postscript_name = ON_wString::EmptyString;
  }
  if (bClearWindowsLogfontName)
  {
    m_loc_windows_logfont_name = ON_wString::EmptyString;
    m_en_windows_logfont_name = ON_wString::EmptyString;
    m_quartet_member = ON_FontFaceQuartet::Member::Unset;
  }
}


bool ON_Font::Internal_SetFontWeightTrio(
  ON_Font::Weight font_weight,
  int windows_logfont_weight,
  double apple_font_weight_trait,
  bool bUpdateFontDescription
)
{
  if (ON_Font::Weight::Unset == font_weight)
  {
    if (windows_logfont_weight > 0 && windows_logfont_weight <= 1000)
    {
      font_weight = ON_Font::WeightFromWindowsLogfontWeight(windows_logfont_weight);
    }
    else if (-1.0 <= apple_font_weight_trait && apple_font_weight_trait <= 1.0)
    {
      font_weight = ON_Font::WeightFromAppleFontWeightTrait(apple_font_weight_trait);
    }
  }

  font_weight = ON_Font::FontWeightFromUnsigned((unsigned int)static_cast<unsigned char>(font_weight));
  if (ON_Font::Weight::Unset == font_weight)
    return false;

  if (false == (1 <= windows_logfont_weight && windows_logfont_weight <= 1000))
    windows_logfont_weight = ON_Font::WindowsLogfontWeightFromWeight(font_weight);

  if (false == (-1.0 <= apple_font_weight_trait && apple_font_weight_trait <= 1.0) )
    apple_font_weight_trait = ON_Font::AppleFontWeightTraitFromWeight(font_weight);
  
  if ( 
    font_weight != m_font_weight
    || false == (apple_font_weight_trait == m_apple_font_weight_trait) // handles nans correctly
    || windows_logfont_weight != m_windows_logfont_weight
    )
  {
    if (false == ON_FONT_MODIFICATION_PERMITTED)
      return false;
    
    if (font_weight != m_font_weight)
    {
      m_font_weight = font_weight;
    }

    if (false == (apple_font_weight_trait == m_apple_font_weight_trait))
      m_apple_font_weight_trait = apple_font_weight_trait;

    if (windows_logfont_weight != m_windows_logfont_weight)
      m_windows_logfont_weight = windows_logfont_weight;

    Internal_AfterModification();
  }

  return true;
}


bool ON_Font::SetFontWeight(ON_Font::Weight font_weight)
{
  return Internal_SetFontWeightTrio(
    font_weight, 
    -1, 
    ON_UNSET_VALUE,
    font_weight != m_font_weight
  );
}


bool ON_Font::SetWindowsLogfontWeight(
  int windows_logfont_weight
)
{
  const ON_Font::Weight font_weight = ON_Font::WeightFromWindowsLogfontWeight(windows_logfont_weight);
  return Internal_SetFontWeightTrio(
    font_weight, 
    windows_logfont_weight, 
    ON_UNSET_VALUE,
    windows_logfont_weight != m_windows_logfont_weight
  );
}

int ON_Font::WindowsLogfontWeight() const
{
  return
    (100 <= m_windows_logfont_weight && m_windows_logfont_weight <= 1000)
    ? m_windows_logfont_weight
    : ON_Font::WindowsLogfontWeightFromWeight(FontWeight());
}

bool ON_Font::SetAppleWeightOfFont(
  int apple_weight_of_font
)
{
  const ON_Font::Weight font_weight = ON_Font::WeightFromAppleWeightOfFont(apple_weight_of_font);
  double apple_font_weight_trait = ON_Font::AppleFontWeightTraitFromWeight(font_weight);
  if (0 <= apple_weight_of_font && apple_weight_of_font <= 9)
  {
    apple_font_weight_trait = (1.0 - apple_weight_of_font) / 7.5;
    if (apple_font_weight_trait < -1.0)
      apple_font_weight_trait = -1.0;
    else if (apple_font_weight_trait > 1.0)
      apple_font_weight_trait = 1.0;    
  }
  return Internal_SetFontWeightTrio(
    font_weight, 
    -1, 
    apple_font_weight_trait,
    PostScriptName().IsEmpty()
  );
}

int ON_Font::AppleWeightOfFont() const
{
  return WindowsLogfontWeight() / 100;
}

bool ON_Font::SetAppleFontWeightTrait(
  double apple_font_weight_trait
)
{
  if (false == ON_IsValid(apple_font_weight_trait))
    return false; // nan or unset value

  const ON_Font::Weight font_weight = ON_Font::WeightFromAppleFontWeightTrait(apple_font_weight_trait);

  return Internal_SetFontWeightTrio(
    font_weight, 
    -1, 
    apple_font_weight_trait,
    PostScriptName().IsEmpty()
  );
}

double ON_Font::AppleFontWeightTrait() const
{
  // old function that cannot be changed because it would break the SDK.
  return
    (m_apple_font_weight_trait >= -1.0 && m_apple_font_weight_trait <= 1.0)
    ? m_apple_font_weight_trait
    : ON_Font::AppleFontWeightTraitFromWeight(this->FontWeight());
}

double ON_Font::AppleFontWeightTraitEx() const
{
  return
    ON_Font::Origin::AppleFont == FontOrigin()
    && m_apple_font_weight_trait >= -1.0
    && m_apple_font_weight_trait <= 1.0
    ? m_apple_font_weight_trait
    : ON_UNSET_VALUE;
}

double ON_Font::AppleFontWidthTrait() const
{
  return
    ON_Font::Origin::AppleFont == FontOrigin()
    && m_apple_font_width_trait >= -1.0
    && m_apple_font_width_trait <= 1.0
    ? m_apple_font_width_trait
    : ON_UNSET_VALUE;
}

bool ON_Font::IsValidPointSize(
  double point_size
)
{
  return (point_size > 0.0 && point_size < 1.0e10);
}

double ON_Font::PointSize() const
{
  return m_point_size;
}

bool ON_Font::SetPointSize(
  double point_size
)
{
  double x 
    = ON_Font::IsValidPointSize(point_size) 
    ? point_size
    : 0.0;
  if (!(m_point_size == x))
  {
    if ( false == ON_FONT_MODIFICATION_PERMITTED )
      return false;
    m_point_size = x;
    // Do not call Internal_AfterModification() here - the source of the fundamental font definition is the same.
    m_font_characteristics_hash = ON_SHA1_Hash::ZeroDigest;
  }
  return true;
}

ON_Font::Style ON_Font::FontStyle() const
{
  return m_font_style;
}

bool ON_Font::SetFontStyle(
  ON_Font::Style font_style
  )
{
  if (m_font_style != font_style)
  {
    if ( false == ON_FONT_MODIFICATION_PERMITTED )
      return false;

    m_font_style = font_style;
    Internal_AfterModification();
  }
  return true;
}

ON_Font::Stretch ON_Font::FontStretch() const
{
  return m_font_stretch;
}

bool ON_Font::SetFontStretch(
  ON_Font::Stretch font_stretch
  )
{
  if (m_font_stretch != font_stretch)
  {
    if ( false == ON_FONT_MODIFICATION_PERMITTED )
      return false;

    m_font_stretch = font_stretch;
    Internal_AfterModification();
  }
  return true;
}
  
bool ON_Font::IsUnderlined() const
{
  return m_font_bUnderlined;
}

bool ON_Font::SetUnderlined(bool bUnderlined)
{
  if( m_font_bUnderlined != (bUnderlined?true:false))
  {
    if ( false == ON_FONT_MODIFICATION_PERMITTED )
      return false;
    m_font_bUnderlined = (bUnderlined?true:false);
    m_font_characteristics_hash = ON_SHA1_Hash::ZeroDigest;
  }
  return true;
}

bool ON_Font::IsStrikethrough() const
{
  return m_font_bStrikethrough;
}

bool ON_Font::SetStrikethrough(bool bStrikethrough)
{
  if(m_font_bStrikethrough != (bStrikethrough?true:false))
  {
    if ( false == ON_FONT_MODIFICATION_PERMITTED )
      return false;
    m_font_bStrikethrough = (bStrikethrough?true:false);
    m_font_characteristics_hash = ON_SHA1_Hash::ZeroDigest;
  }
  return true;
}

bool ON_Font::IsSymbolFont() const
{
  return (ON_Font::WindowsConstants::logfont_symbol_charset == m_logfont_charset);
}

const ON_PANOSE1 ON_Font::PANOSE1() const
{
  return m_panose1;
}

void ON_Font::SetPANOSE1(
  ON_PANOSE1 panose1
)
{
  m_panose1 = panose1;
}

unsigned char ON_Font::LogfontCharSet() const
{
  return m_logfont_charset;
}

bool ON_Font::SetLogfontCharSet(unsigned char logfont_charset)
{
  if (ON_Font::WindowsConstants::logfont_symbol_charset != logfont_charset)
    logfont_charset = ON_Font::WindowsConstants::logfont_default_charset;
  if(logfont_charset != m_logfont_charset)
  {
    if ( false == ON_FONT_MODIFICATION_PERMITTED )
      return false;
    m_logfont_charset = logfont_charset;
  }
  return true;
}

const ON_FontMetrics& ON_Font::FontMetrics() const
{
  class ON_FontGlyphCache* font_cache = FontGlyphCache(true);
  if (nullptr != font_cache)
    return font_cache->m_normalized_metrics;
  return ON_FontMetrics::Unset;
}

const ON_FontMetrics& ON_Font::FontUnitFontMetrics() const
{
  class ON_FontGlyphCache* font_cache = FontGlyphCache(true);
  if (nullptr != font_cache)
    return font_cache->m_font_unit_metrics;
  return ON_FontMetrics::Unset;
}

double ON_Font::FontUnitToNormalizedScale() const
{
  class ON_FontGlyphCache* font_cache = FontGlyphCache(true);
  if (nullptr != font_cache)
    return font_cache->m_font_unit_to_normalized_scale;
  return 1.0;
}
  
double ON_Font::NormalizedToFontUnitScale() const
{
  class ON_FontGlyphCache* font_cache = FontGlyphCache(true);
  if (nullptr != font_cache)
    return font_cache->m_normalized_to_font_unit_scale;
  return 1.0;
}


int ON_Font::HeightOfI() const
{
  return FontMetrics().AscentOfCapital();
}

int ON_Font::HeightOfLinefeed() const
{
  return FontMetrics().LineSpace();
}

double ON_Font::HeightScale(double text_height) const
{
  return FontMetrics().GlyphScale(text_height);
}

int ON_Font::GetStrikeoutSize() const
{
  return FontMetrics().StrikeoutThickness();
}

int ON_Font::GetStrikeoutPosition() const
{
  return FontMetrics().StrikeoutPosition();
}

int ON_Font::GetUnderscoreSize() const
{
  return FontMetrics().UnderscoreThickness();
}

int ON_Font::GetUnderscorePosition() const
{
  return FontMetrics().UnderscorePosition();
}

const class ON_SHA1_Hash& ON_Font::FontCharacteristicsHash() const
{
  if (m_font_characteristics_hash.IsZeroDigest())
  {
    ON_SHA1 sha1;

    sha1.AccumulateUnsigned64(sizeof(*this));

    // Even on Apple OS, we need to accumulate the WindowsLogfontName()
    // because it is what is used for the fake regular/bold/italic/bold-italic
    // user interface the Rhino uses on Apple.
    ON_SHA1_Hash string_hash;
    const ON_wString windows_logfont_name = WindowsLogfontName();
    if ( windows_logfont_name.IsNotEmpty() )
    {
      string_hash = ON_SHA1_Hash::StringHash(windows_logfont_name);
      sha1.AccumulateSubHash(string_hash);
    }
    sha1.AccumulateUnsigned8(static_cast<ON__UINT8>(m_font_weight));
    sha1.AccumulateUnsigned8(static_cast<ON__UINT8>(m_font_style));
    sha1.AccumulateUnsigned8(static_cast<ON__UINT8>(m_font_stretch));
    sha1.AccumulateBool(m_font_bUnderlined);
    sha1.AccumulateBool(m_font_bStrikethrough);
    sha1.AccumulateUnsigned8(static_cast<ON__UINT8>(m_logfont_charset));

    const ON_wString family_name = FamilyName();
    if (family_name.IsNotEmpty())
    {
      string_hash = ON_SHA1_Hash::StringHash(family_name);
      sha1.AccumulateSubHash(string_hash);
    }

    if (m_point_size > 0)
    {
      sha1.AccumulateDouble(m_point_size);
    }

#if defined(ON_RUNTIME_WIN)  
    sha1.AccumulateInteger32(m_windows_logfont_weight);
#endif

#if defined(ON_RUNTIME_APPLE)     

    // The PostScript name is not hashed on Windows because
    // it is not predictable with simulated fonts.
    // The PostScript name is critical on Apple OS and
    // is the most reliable way to uniquely identify
    // a font on Apple OS.
    sha1.AccumulateDouble(m_apple_font_weight_trait);
    const ON_wString postscript_name = PostScriptName();
    if (postscript_name.IsNotEmpty())
    {
      string_hash = ON_SHA1_Hash::StringHash(postscript_name);
      sha1.AccumulateSubHash(string_hash);
    }
#endif

    m_font_characteristics_hash = sha1.Hash();
  }

  return m_font_characteristics_hash;
}


int ON_Font::CompareFontCharacteristicsForExperts(
  bool bComparePlatformSpecificCharacteristics,
  bool bIgnoreUnsetCharacteristics,
  const ON_Font& lhs,
  const ON_Font& rhs
)
{
  int i = 0;
  int j = 0;

  for (;;)
  {
    const ON_wString lhs_family_name = lhs.FamilyName();
    const ON_wString rhs_family_name = rhs.FamilyName();
    const bool bCompareFamilyName =
      false == bIgnoreUnsetCharacteristics
      || (0 != lhs_family_name.IsNotEmpty() && 0 != rhs_family_name.IsNotEmpty());
    if (bCompareFamilyName)
    {
      i = ON_wString::CompareOrdinal(lhs_family_name, rhs_family_name, true);
      j = 0;
      if ( i != j )
        break;
    }

    const ON_wString lhs_logfont_name = lhs.WindowsLogfontName();
    const ON_wString rhs_logfont_name = rhs.WindowsLogfontName();
    const bool bCompareWindowsLogfontName =
      false == bIgnoreUnsetCharacteristics
      || (lhs_logfont_name.IsNotEmpty() && rhs_logfont_name.IsNotEmpty());
    if (bCompareWindowsLogfontName)
    {
      i = ON_wString::CompareOrdinal(lhs_logfont_name, rhs_logfont_name, true);
      j = 0;
      if ( i != j )
        break;
    }

    const ON_Font::Weight lhs_weight = lhs.m_font_weight;
    const ON_Font::Weight rhs_weight = rhs.m_font_weight;
    const bool bCompareWeight =
      false == bIgnoreUnsetCharacteristics
      || (ON_Font::Weight::Unset != lhs_weight && ON_Font::Weight::Unset != rhs_weight);
    if (bCompareWeight)
    {
      i = ON_Font::WindowsLogfontWeightFromWeight(lhs_weight);
      j = ON_Font::WindowsLogfontWeightFromWeight(rhs_weight);
      if (i != j)
        break;
    }

    const ON_Font::Style lhs_style = lhs.m_font_style;
    const ON_Font::Style rhs_style = rhs.m_font_style;
    const bool bCompareStyle =
      false == bIgnoreUnsetCharacteristics
      || (ON_Font::Style::Unset != lhs_style && ON_Font::Style::Unset != rhs_style);
    if (bCompareStyle)
    {
      i = static_cast<int>(lhs_style);
      j = static_cast<int>(rhs_style);
      if (i != j)
        break;
    }

    const ON_Font::Stretch lhs_stretch = lhs.m_font_stretch;
    const ON_Font::Stretch rhs_stretch = rhs.m_font_stretch;
    const bool bCompareStretch =
      false == bIgnoreUnsetCharacteristics
      || (ON_Font::Stretch::Unset != lhs_stretch && ON_Font::Stretch::Unset != rhs_stretch);
    if (bCompareStretch)
    {
      i = static_cast<int>(lhs_stretch);
      j = static_cast<int>(rhs_stretch);
      if (i != j)
        break;
    }

    i = lhs.m_font_bUnderlined ? 1 : 0;
    j = rhs.m_font_bUnderlined ? 1 : 0;
    if ( i != j )
      break;

    i = lhs.m_font_bStrikethrough ? 1 : 0;
    j = rhs.m_font_bStrikethrough ? 1 : 0;
    if ( i != j )
      break;

    const double lhs_point_size = ON_Font::IsValidPointSize(lhs.m_point_size) ? lhs.m_point_size : 0.0;
    const double rhs_point_size = ON_Font::IsValidPointSize(rhs.m_point_size) ? rhs.m_point_size : 0.0;
    j = 0;
    if (lhs_point_size < rhs_point_size)
      i = -1;
    else if (rhs_point_size < lhs_point_size)
      i = 1;
    else
      i = 0;
    if (i != j)
      break;
 
    if (false == bComparePlatformSpecificCharacteristics)
      break;
 
#if defined(ON_RUNTIME_WIN) 
    i = (ON_Font::WindowsConstants::logfont_symbol_charset == lhs.m_logfont_charset) ? 1 : 0;
    j = (ON_Font::WindowsConstants::logfont_symbol_charset == rhs.m_logfont_charset) ? 1 : 0;
    if ( i != j )
      break;
#endif


#if defined(ON_RUNTIME_APPLE)     
  const ON_wString lhs_postscript_name = lhs.PostScriptName();
  const ON_wString rhs_postscript_name = rhs.PostScriptName();
    const bool bComparePostScriptName =
      false == bIgnoreUnsetCharacteristics
      || (lhs_postscript_name.IsNotEmpty() && rhs_postscript_name.IsNotEmpty());
    if (bComparePostScriptName)
    {
      i = ON_wString::CompareOrdinal(lhs_postscript_name, rhs_postscript_name, false);
      if (0 == i)
      {
        if (lhs.m_apple_font_weight_trait < rhs.m_apple_font_weight_trait)
          i = -1;
        else if (lhs.m_apple_font_weight_trait > rhs.m_apple_font_weight_trait)
          i = 1;
      }
      j = 0;
      if (i != j)
        break;
    }
#endif

    break;
  }

  if (i < j)
    return -1;
  if (i > j)
    return 1;

  return 0;
}


int ON_Font::CompareFontCharacteristics(
  const ON_Font& lhs,
  const ON_Font& rhs
)
{
  const bool bComparePlatformSpecificCharacteristics = true;
  const bool bIgnoreUnsetCharacteristics = false;
  return ON_Font::CompareFontCharacteristicsForExperts(
    bComparePlatformSpecificCharacteristics,
    bIgnoreUnsetCharacteristics,
    lhs,
    rhs
  );
}

bool ON_Font::EqualFontCharacteristics(
  const ON_Font& a,
  const ON_Font& b
  )
{
  return (0 == ON_Font::CompareFontCharacteristics(a,b));
}


ON_Font::Origin ON_Font::FontOriginFromUnsigned(
  unsigned int unsigned_font_origin
)
{
  switch (unsigned_font_origin)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Origin::Unset);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Origin::Unknown);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Origin::WindowsFont);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_Font::Origin::AppleFont);
  };

  ON_ERROR("Invalid unsigned_font_origin value.");
  return ON_Font::Origin::Unset;
}

ON_Font::Origin ON_Font::FontOrigin() const
{
  return m_font_origin;
}
  
void ON_Font::SetFontOrigin(
  ON_Font::Origin font_origin
)
{
  m_font_origin = font_origin;
}

bool ON_Font::IsSimulated() const
{
  return 0 != m_simulated;
}

bool ON_Font::SimulatedWeight() const
{
  return (0 != (m_simulated & 2));
}

bool ON_Font::SimulatedStretch() const
{
  return (0 != (m_simulated & 4));
}

bool ON_Font::SimulatedStyle() const
{
  return (0 != (m_simulated & 8));
}

void ON_Font::SetSimulated(
  bool bSimulatedWeight,
  bool bSimulatedStretch,
  bool bSimulatedStyle,
  bool bSimulatedOther
)
{
  ON__UINT8 s = 0;
  if (bSimulatedWeight)
    s |= 2;
  if (bSimulatedStretch)
    s |= 4;
  if (bSimulatedStyle)
    s |= 8;
  if (bSimulatedOther)
    s |= 1;
  m_simulated = s;
}

#if defined(ON_RUNTIME_WIN)

static int ON_InternalVerticalPixelScale(
  HDC hdc,
  bool bDCtoLP,
  int y0
)
{
  int y1 = -1;

  for (;;)
  {
    POINT origin{ 0,0 };
    POINT pt{ 0, y0 };
    if (bDCtoLP)
    {
      if (0 == ::DPtoLP(hdc, &pt, 1))
        break;
      if (0 == ::DPtoLP(hdc, &origin, 1))
        break;
    }
    else
    {
      if (0 == ::LPtoDP(hdc, &pt, 1))
        break;
      if (0 == ::LPtoDP(hdc, &origin, 1))
        break;
    }
    y1 = std::abs(pt.y - origin.y);
    break;
  }

  return y1;
}


bool ON_Font::GetWindowsDeviceToLogicalHeightScales(
  HDC hdc,
  double* device_to_logical_scale,
  double* logical_to_device_scale
)
{
  if (nullptr != device_to_logical_scale)
    *device_to_logical_scale = 1.0;
  if (nullptr != logical_to_device_scale)
    *logical_to_device_scale = 1.0;

  int device_coordinate = 0;
  int logical_coordinate = 0;

  // see which is larger, device or logical
  const int thousand = 1000;
  const int device_to_logical_1000x = ON_InternalVerticalPixelScale(hdc, true, thousand);
  const int logical_to_device_1000x = ON_InternalVerticalPixelScale(hdc, false, thousand);
  if (device_to_logical_1000x <= 0 && logical_to_device_1000x <= 0)
  {
    ON_ERROR("DPtoLP(hdc, ...) and LPtoDP(hdc, ...) failed.");
    return false;
  }

  if (thousand == device_to_logical_1000x && thousand == logical_to_device_1000x)
  {
    // vertical logical pixels are the same size as device pixels
    device_coordinate = 1;
    logical_coordinate = 1;
  }
  else
  {
    // bDCtoLP = true if logical pixels are smaller than device pixels
    const bool bDCtoLP = (device_to_logical_1000x >= logical_to_device_1000x);
    const int s1000 = bDCtoLP ? device_to_logical_1000x : logical_to_device_1000x;
    int y0 = 0;
    int y1 = 0;
    const int s1024 = ON_InternalVerticalPixelScale(hdc, bDCtoLP, 1024);
    for (y0 = 1; y0 <= 100; y0++)
    {
      y1 = ON_InternalVerticalPixelScale(hdc, bDCtoLP, y0);
      if (y0*s1000 == y1*thousand || y0*s1024 == y1*1024)
      {
        break;
      }
      y1 = 0;
    }
    if (0 == y1)
    {
      y0 = thousand;
      y1 = s1000;
    }
    if (bDCtoLP)
    {
      device_coordinate = y0;
      logical_coordinate = y1;
    }
    else
    {
      device_coordinate = y1;
      logical_coordinate = y0;
    }
  }

  if (nullptr != device_to_logical_scale)
  {
    *device_to_logical_scale = ((double)logical_coordinate) / ((double)device_coordinate);
  }

  if (nullptr != logical_to_device_scale)
  {
    *logical_to_device_scale = ((double)device_coordinate) / ((double)logical_coordinate);
  }

  return true;
}

HDC ON_Font::CreateWindowsLogfontDeviceContext()
{
  return ::CreateCompatibleDC(nullptr);
}

void ON_Font::DeleteWindowsLogfontDeviceContext(
  HDC hdc
)
{
  if ( nullptr != hdc )
    ::DeleteDC(hdc);
}

bool ON_Font::GetWindowsTextMetrics(
  int map_mode,
  HDC hdc,
  const LOGFONT& logfont,
  TEXTMETRIC& textmetric
)
{
  bool rc = false;

  TEXTMETRIC tm;
  memset(&tm, 0, sizeof(tm));
  textmetric = tm;

  // need to get TEXTMETRICS tmInternalLeading
  const bool bValidMapModeParameter = (map_mode >= MM_MIN && map_mode <= MM_MAX);
  const bool bNeedDeviceContext = (false == bValidMapModeParameter || MM_TEXT == map_mode);
  HDC font_hdc = nullptr;

  const int savedDC
    = (nullptr != hdc)
    ? ::SaveDC(hdc)
    : 0;

  HFONT hfont = 0;

  for (;;)
  {
    if (nullptr == hdc)
    {
      font_hdc = ON_Font::CreateWindowsLogfontDeviceContext();
      hdc = font_hdc;
      if (nullptr == hdc)
        break;
    }

    const int hdc_mm = ::GetMapMode(hdc);

    int mm
      = bValidMapModeParameter
      ? map_mode
      : ((nullptr != hdc) ? hdc_mm : 0);

    const bool bValidMM = (mm >= MM_MIN && mm <= MM_MAX);

    if (false == bValidMM)
    {
      if (ON_Font::MAP_MODE_ZERO_ERROR_SUPPRESS != map_mode)
      {
        ON_ERROR("GetMapMode(hdc) failed.");
      }
      break;
    }

    if (hdc_mm != mm && bValidMM)
    {
      ::SetMapMode(hdc, mm);
    }

    hfont = ::CreateFontIndirect(&logfont);
    if (0 == hfont)
      break;

    ::SelectObject(hdc, hfont);

    if (0 == ::GetTextMetrics(hdc, &tm))
    {
      if (ON_Font::MAP_MODE_ZERO_ERROR_SUPPRESS != map_mode)
      {
        ON_ERROR("GetTextMetrics(hdc,...) failed.");
      }
      break;
    }

    textmetric = tm;

    rc = true;
    break;
  }  

  if (nullptr != font_hdc)
    ON_Font::DeleteWindowsLogfontDeviceContext(font_hdc);
  else if ( nullptr != hdc)
    ::RestoreDC(hdc, savedDC);

  if (0 != hfont)
    ::DeleteObject(hfont);

  return rc;
}

int ON_Font::WindowsLogfontCharacterHeight(
  int map_mode,
  HDC hdc,
  const LOGFONT& logfont
)
{
  if (logfont.lfHeight <= 0)
    return logfont.lfHeight;

  int logfont_lfHeight = 0;

  for (;;)
  {
    TEXTMETRIC tm;
    memset(&tm, 0, sizeof(tm));
    bool bHaveTextMetric = ON_Font::GetWindowsTextMetrics(
      map_mode,
      hdc,
      logfont,
      tm
    );

    if (false == bHaveTextMetric)
    {
      if (ON_Font::MAP_MODE_ZERO_ERROR_SUPPRESS != map_mode)
      {
        ON_ERROR("ON_Font::GetWindowsTextMetrics...) failed.");
      }
      break;
    }

    const int cellHeight = tm.tmAscent + tm.tmDescent;
    const int characterHeight = cellHeight - tm.tmInternalLeading;
    if (cellHeight <= 0 || characterHeight <= 0)
    {
      ON_ERROR("tm.tmInternalLeading >= cellHeight.");
      break;
    }



    // logfont_lfHeight is negative to indicate it is character height.
    // (positive values are cell height)
    logfont_lfHeight = -characterHeight;
    break;
  }

  return logfont_lfHeight;
}

int ON_Font::WindowsLogfontCellHeight(
  int map_mode,
  HDC hdc,
  const LOGFONT& logfont
)
{
  if (logfont.lfHeight >= 0)
    return logfont.lfHeight;

  int logfont_lfHeight = 0;

  for (;;)
  {
    TEXTMETRIC tm;
    memset(&tm, 0, sizeof(tm));
    bool bHaveTextMetric = ON_Font::GetWindowsTextMetrics(
      map_mode,
      hdc,
      logfont,
      tm
    );

    if (false == bHaveTextMetric)
    {
      ON_ERROR("ON_Font::GetWindowsTextMetrics...) failed.");
      break;
    }

    const int cellHeight = tm.tmAscent + tm.tmDescent;
    if (cellHeight <= 0)
    {
      ON_ERROR("tm.tmAscent + tm.tmDescent < 0.");
      break;
    }

    // logfont_lfHeight is positive to indicate it is cell height.
    // (negative values are character height)
    logfont_lfHeight = cellHeight;
    break;
  }

  return logfont_lfHeight;
}


int ON_Font::WindowsLogfontCharacterHeightFromPointSize(
  int map_mode,
  HDC hdc,
  double point_size
)
{
  int logfont_lfHeight = 0;

  const bool bValidMapModeParameter = (map_mode >= MM_MIN && map_mode <= MM_MAX);
  const bool bNeedDeviceContext = (false == bValidMapModeParameter || MM_TEXT == map_mode);
  HDC font_hdc = nullptr;

  for (;;)
  {
    if (0 == point_size)
      break;

    if (!(point_size > 0.0 && point_size < 21474836.47))
    {
      ON_ERROR("Invalid point_size parameter.");
      break;
    }

    if (bNeedDeviceContext && nullptr == hdc)
    {
      font_hdc = ON_Font::CreateWindowsLogfontDeviceContext();
      hdc = font_hdc;
      if (nullptr == hdc)
        break;
    }

    const int mm
      = bValidMapModeParameter
      ? map_mode
      : ((nullptr != hdc) ? ::GetMapMode(hdc) : 0);

    if (mm < MM_MIN || mm > MM_MAX)
    {
      ON_ERROR("GetMapMode(hdc) failed.");
      break;
    }

    double points_to_lfHeight = 0.0;
    switch (mm)
    {
    case MM_TEXT:
      // Each logical unit is mapped to one device pixel. Positive x is to the right; positive y is down.
      if(nullptr != hdc)
      {
        const int device_pixels_per_logical_inch = ::GetDeviceCaps(hdc, LOGPIXELSY);
        if (device_pixels_per_logical_inch <= 0)
        {
          ON_ERROR("GetDeviceCaps(hdc, LOGPIXELSY) failed.");
          break;
        }

        double device_to_logical_scale = 1.0;
        if (false == ON_Font::GetWindowsDeviceToLogicalHeightScales(hdc, &device_to_logical_scale, nullptr) )
        {
          ON_ERROR("ON_Font::GetWindowsDeviceToLogicalHeightScales(hdc, ...) failed.");
          break;
        }

        // MM_TEXT points_to_lfHeight units 
        // = ((device pixel height)/(logical inch)) * (logical pixel height) / ( (points/inch)*(device pixel height) )
        // = ( (logical pixel height) / points ) * (inch / (logical inch))
        points_to_lfHeight = ((static_cast<double>(device_pixels_per_logical_inch)*device_to_logical_scale)) / 72.0;
      }
      break;
    case MM_LOMETRIC:
      // Each logical unit is mapped to 0.1 millimeter. Positive x is to the right; positive y is up.
      // (254 tenths of a mm/inch)/(72 points/inch)
      points_to_lfHeight = 254.0/72.0;
      break;
    case MM_HIMETRIC:
      // Each logical unit is mapped to 0.01 millimeter. Positive x is to the right; positive y is up.
      // (2540 hundredths of a mm/inch)/(72 points/inch)
      points_to_lfHeight = 2540.0/72.0;
      break;
    case MM_LOENGLISH:
      // Each logical unit is mapped to 0.01 inch. Positive x is to the right; positive y is up.
      // (100 hundredths of a inch/inch)/(72 points/inch)
      points_to_lfHeight = 1.0/0.72;
      break;
    case MM_HIENGLISH:
      // Each logical unit is mapped to 0.001 inch. Positive x is to the right; positive y is up.
      // (1000 thousandths of a inch/inch)/(72 points/inch)
      points_to_lfHeight = 1.0/0.072;
      break;
    case MM_TWIPS:
      // Each logical unit is mapped to one twentieth of a printer's point (1/1440 inch, also called a "twip"). Positive x is to the right; positive y is up.
      // 20 twips / point
      points_to_lfHeight = 20.0;
      break;
    case MM_ISOTROPIC:
      // Logical units are mapped to arbitrary units with equally scaled axes; 
      // that is, one unit along the x-axis is equal to one unit along the y-axis. 
      // Use the SetWindowExtEx and SetViewportExtEx functions to specify the units
      // and the orientation of the axes. Graphics device interface makes adjustments
      // as necessary to ensure the x and y units remain the same size. 
      // (When the windows extent is set, the viewport will be adjusted to keep
      // the units isotropic).
      ON_ERROR("GetMapMode(hdc) returned MM_ISOTROPIC mapping mode.");
      break;
    case MM_ANISOTROPIC:
      // Logical units are mapped to arbitrary units with arbitrarily scaled axes. 
      // Use the SetWindowExtEx and SetViewportExtEx functions to specify the units, 
      // orientation, and scaling required.
      ON_ERROR("GetMapMode(hdc) returned MM_ANISOTROPIC mapping mode.");
      break;
    default:
      ON_ERROR("GetMapMode(hdc) returned undocumented mapping mode.");
    }

    if (0 != points_to_lfHeight)
    {
      logfont_lfHeight = -static_cast<int>(fabs(points_to_lfHeight*point_size + 0.5));
      if (0 == logfont_lfHeight)
        logfont_lfHeight = -1;
    }
    break;
  }

  if (nullptr != font_hdc)
  {
    ON_Font::DeleteWindowsLogfontDeviceContext(font_hdc);
  }

  return logfont_lfHeight;
}

double ON_Font::PointSizeFromWindowsLogfontCharacterHeight(
  int map_mode,
  HDC hdc,
  int logfont_character_height
)
{
  double point_size = 0.0;

  const bool bValidMapModeParameter = (map_mode >= MM_MIN && map_mode <= MM_MAX);

  const bool bNeedDeviceContext = (false == bValidMapModeParameter || MM_TEXT == map_mode);

  HDC font_hdc = 0;

  // Windows LOGFONT.lfHeight is negative when
  // the value is a character height. This
  // function allow the user to pass in a positive value.
  const int logfont_lfHeight
    = (logfont_character_height <= 0)
    ? logfont_character_height
    : -logfont_character_height;

  for (;;)
  {
    if (logfont_lfHeight >= 0)
      break;

    if (bNeedDeviceContext && nullptr == hdc )
    {
      font_hdc = ON_Font::CreateWindowsLogfontDeviceContext();
      hdc = font_hdc;
      if (nullptr == hdc)
        break;
    }

    const int mm
      = bValidMapModeParameter
      ? map_mode
      : ((nullptr != hdc) ? ::GetMapMode(hdc) : 0);

    if (mm < MM_MIN || mm > MM_MAX)
    {
      ON_ERROR("GetMapMode(hdc) failed.");
      break;
    }

    double lfHeight_to_points = 0.0;
    switch (mm)
    {
    case MM_TEXT:
      // Each logical unit is mapped to one device pixel. Positive x is to the right; positive y is down.
      if(nullptr != hdc)
      {
        const int device_pixels_per_logical_inch = ::GetDeviceCaps(hdc, LOGPIXELSY);
        if (device_pixels_per_logical_inch <= 0)
        {
          ON_ERROR("GetDeviceCaps(hdc, LOGPIXELSY) failed.");
          break;
        }

        double logical_to_device_scale = 1.0;
        if (false == ON_Font::GetWindowsDeviceToLogicalHeightScales(hdc, nullptr, &logical_to_device_scale))
        {
          ON_ERROR("ON_Font::GetWindowsDeviceToLogicalHeightScales(hdc, ...) failed.");
          break;
        }

        // MM_TEXT lfHeight_to_points units 
        // = ( (points/inch) * (device pixel height) ) / ( ((device pixel height)/(logical inch)) * (logical pixel height)   )
        // = ( points / (logical pixel height) ) * ( (logical inch)/inch )
        lfHeight_to_points = (72.0*logical_to_device_scale) / static_cast<double>(device_pixels_per_logical_inch);
      }
      break;
    case MM_LOMETRIC:
      // Each logical unit is mapped to 0.1 millimeter. Positive x is to the right; positive y is up.
      // 72 points/inch / (254 tenths of a mm/inch)
      lfHeight_to_points = 72.0 / 254.0;
      break;
    case MM_HIMETRIC:
      // Each logical unit is mapped to 0.01 millimeter. Positive x is to the right; positive y is up.
      // 72 points/inch / (2540 hundredths of a mm/inch)
      lfHeight_to_points = 72.0 / 2540.0;
      break;
    case MM_LOENGLISH:
      // Each logical unit is mapped to 0.01 inch. Positive x is to the right; positive y is up.
      // 72 points/inch / (100 hundredths of a inch/inch)
      lfHeight_to_points = 0.72;
      break;
    case MM_HIENGLISH:
      // Each logical unit is mapped to 0.001 inch. Positive x is to the right; positive y is up.
      // 72 points/inch / (1000 thousandths of a inch/inch)
      lfHeight_to_points = 0.072;
      break;
    case MM_TWIPS:
      // Each logical unit is mapped to one twentieth of a printer's point (1/1440 inch, also called a "twip"). Positive x is to the right; positive y is up.
      // 1 point / 20 twips
      lfHeight_to_points = 1.0/20.0;
      break;
    case MM_ISOTROPIC:
      // Logical units are mapped to arbitrary units with equally scaled axes; 
      // that is, one unit along the x-axis is equal to one unit along the y-axis. 
      // Use the SetWindowExtEx and SetViewportExtEx functions to specify the units
      // and the orientation of the axes. Graphics device interface makes adjustments
      // as necessary to ensure the x and y units remain the same size. 
      // (When the windows extent is set, the viewport will be adjusted to keep
      // the units isotropic).
      ON_ERROR("GetMapMode(hdc) returned MM_ISOTROPIC mapping mode.");
      break;
    case MM_ANISOTROPIC:
      // Logical units are mapped to arbitrary units with arbitrarily scaled axes. 
      // Use the SetWindowExtEx and SetViewportExtEx functions to specify the units, 
      // orientation, and scaling required.
      ON_ERROR("GetMapMode(hdc) returned MM_ANISOTROPIC mapping mode.");
      break;
    default:
      ON_ERROR("GetMapMode(hdc) returned undocumented mapping mode.");
    }

    point_size = fabs(lfHeight_to_points*static_cast<double>(logfont_lfHeight));

    for (;;)
    {
      // Because LOGFONT lfHeight is an integer and point_size is typically
      // an integer and sometimes a multiple of 0.5, the following rouding
      // is performed so point_size will round trip.
      double i0 = floor(point_size);
      if (i0 == point_size)
        break;

      if (lfHeight_to_points < 0.5 && 2.0*point_size == floor(2.0*point_size))
        break;

      double i1 = ceil(point_size);
      if (i1 >= 1.0)
      {
        if (i0 >= 1.0 && fabs(i0 - point_size) < fabs(i1 - point_size) && fabs(i0 - point_size) < lfHeight_to_points)
        {
          if (logfont_lfHeight == ON_Font::WindowsLogfontCharacterHeightFromPointSize(map_mode, hdc, i0))
          {
            point_size = i0;
            break;
          }
        }
        else if (fabs(i1 - point_size) < fabs(i0 - point_size) && fabs(i1 - point_size) < lfHeight_to_points)
        {
          if (logfont_lfHeight == ON_Font::WindowsLogfontCharacterHeightFromPointSize(map_mode, hdc, i1))
          {
            point_size = i1;
            break;
          }
        }

        if (lfHeight_to_points < 0.25 && fabs(point_size - 0.5*(i0 + i1)) < lfHeight_to_points)
        {
          if (logfont_lfHeight == ON_Font::WindowsLogfontCharacterHeightFromPointSize(map_mode, hdc, 0.5*(i0 + i1)))
          {
            point_size = 0.5*(i0 + i1);
            break;
          }
        }
      }
      
      break;
    }

    break;
  }

  if (nullptr != font_hdc)
  {
    ON_Font::DeleteWindowsLogfontDeviceContext(font_hdc);
  }

  return point_size;
}

bool ON_Font::SetFromWindowsLogFont(
  int map_mode,
  HDC hdc,
  const LOGFONT& dirty_logfont
)
{
  if ( false == ON_FONT_MODIFICATION_PERMITTED )
    return false;

  *this = ON_Font::Unset;

  const bool bUnderlined = (0 != dirty_logfont.lfUnderline) ? true : false;
  const bool bStrikethrough = (0 != dirty_logfont.lfStrikeOut) ? true : false;

  LOGFONT logfont = dirty_logfont;
  logfont.lfWidth = 0;
  logfont.lfEscapement = 0;
  logfont.lfOrientation = 0;
  logfont.lfUnderline = 0;
  logfont.lfStrikeOut = 0;
  logfont.lfCharSet = ON_Font::WindowsLogfontCharSetFromLogfont(&logfont, true);
  logfont.lfOutPrecision = ON_Font::WindowsConstants::logfont_out_precis;
  logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
  logfont.lfQuality = ON_Font::WindowsConstants::logfont_quality;
  logfont.lfPitchAndFamily = ON_Font::WindowsConstants::logfont_pitch_and_family;
  int face_name_capacity = (int)((sizeof(logfont.lfFaceName) / sizeof(logfont.lfFaceName[0])));
  for (int i = 0; i < face_name_capacity; i++)
  {
    if (0 == logfont.lfFaceName[i])
    {
      for (i++; i < face_name_capacity; i++)
        logfont.lfFaceName[i] = 0;
    }
  }
  logfont.lfFaceName[face_name_capacity-1] = 0;

  // Calculate point size
  // If logfont.lfHeight > 0, +lfHeight = cell height.
  // If logfont.lfHeight < 0, -lfHeight = character height = cell height - TEXTMETRIC.tmInternalLeading.
  // PointSize() calculations require a character height.
  const int logfont_lfHeight
    = (0 != logfont.lfHeight)
    ? ON_Font::WindowsLogfontCharacterHeight(map_mode, hdc, logfont)
    : 0;

  const double point_size
    = (logfont_lfHeight < 0)
    ? ON_Font::PointSizeFromWindowsLogfontCharacterHeight(map_mode, hdc, logfont_lfHeight)
    : 0.0;

  logfont.lfHeight = ON_Font::Constants::AnnotationFontCellHeight;

  // TODO - use DWrite gdi interop to get an IDWriteFont and use it to set the ON_Font.
  
  const ON_Font::Weight font_weight = ON_Font::WeightFromWindowsLogfontWeight(logfont.lfWeight);
  const ON_Font::Style font_style = (0 != logfont.lfItalic) ? ON_Font::Style::Italic : ON_Font::Style::Upright;
  const ON_Font::Stretch font_stretch = ON_Font::Stretch::Medium;
  const double linefeed_ratio = ON_FontMetrics::DefaultLineFeedRatio;
  
  bool rc = SetFontCharacteristics(
    point_size,
    logfont.lfFaceName,
    font_weight,
    font_style,
    font_stretch,
    bUnderlined,
    bStrikethrough,
    linefeed_ratio,
    logfont.lfCharSet
    );

  if (rc)
  {
    rc = Internal_SetFontWeightTrio(
      font_weight, 
      logfont.lfWeight, 
      ON_UNSET_VALUE,
      false
    );
  }

  // Do last because other setters sometimes unset the orgin.
  SetFontOrigin(ON_Font::Origin::WindowsFont);

  return rc;
}

const LOGFONT ON_Font::WindowsLogFont(
  int map_mode,
  HDC hdc
  ) const
{
  LOGFONT logfont;

  memset(&logfont, 0, sizeof(LOGFONT));

  logfont.lfHeight 
    = (m_point_size > 0.0)
    ? ON_Font::WindowsLogfontCharacterHeightFromPointSize(map_mode,hdc,m_point_size)
    : ON_Font::Constants::AnnotationFontCellHeight;

  logfont.lfWidth = 0;
  logfont.lfEscapement = 0;
  logfont.lfOrientation = 0;
  
  const ON_Font::Weight font_weight_from_windows_logfont_weight = ON_Font::WeightFromWindowsLogfontWeight(m_windows_logfont_weight);
  logfont.lfWeight 
    = (m_windows_logfont_weight > 0 && m_windows_logfont_weight <= 1000 && font_weight_from_windows_logfont_weight == m_font_weight)
    ? m_windows_logfont_weight
    : ON_Font::WindowsLogfontWeightFromWeight(m_font_weight);

  logfont.lfItalic = (ON_Font::Style::Italic == m_font_style) ? 1 : 0;
  logfont.lfUnderline = m_font_bUnderlined ? 1 : 0;
  logfont.lfStrikeOut = m_font_bStrikethrough ? 1 : 0;
  logfont.lfCharSet = m_logfont_charset;
  logfont.lfOutPrecision = ON_Font::WindowsConstants::logfont_out_precis;
  logfont.lfClipPrecision = 0;
  logfont.lfQuality = ON_Font::WindowsConstants::logfont_quality;
  logfont.lfPitchAndFamily = ON_Font::WindowsConstants::logfont_pitch_and_family;

  const ON_wString windows_logfont_name = WindowsLogfontName();
  const int windows_logfont_name_len = windows_logfont_name.Length();
  const wchar_t* s = static_cast<const wchar_t*>(windows_logfont_name);

  for(int i = 0; i < windows_logfont_name_len && i < LF_FACESIZE; i++)
    logfont.lfFaceName[i] = s[i];
  logfont.lfFaceName[LF_FACESIZE - 1] = 0;

  return logfont;
}

const MAT2 ON_Font::WindowsFontMat2() const
{
  MAT2 mat2;
  memset(&mat2, 0, sizeof(mat2));

  mat2.eM11.fract = 0;
  mat2.eM11.value = 1;

  mat2.eM12.fract = 0;
  mat2.eM12.value = 0;

  mat2.eM21.fract = 0;
  mat2.eM21.value = 0;

  mat2.eM22.fract = 0;
  mat2.eM22.value = 1;

  double eM11 = 1.0;

  switch (FontStretch())
  {
  case ON_Font::Stretch::Ultracondensed:
    eM11 = 0.2;
    break;
  case ON_Font::Stretch::Extracondensed:
    eM11 = 0.3;
    break;
  case ON_Font::Stretch::Condensed:
    eM11 = 0.5;
    break;
  case ON_Font::Stretch::Semicondensed:
    eM11 = 0.75;
    break;
  case ON_Font::Stretch::Medium:
    eM11 = 1.0;
    break;
  case ON_Font::Stretch::Semiexpanded:
    eM11 = 1.25;
    break;
  case ON_Font::Stretch::Expanded:
    eM11 = 1.5;
    break;
  case ON_Font::Stretch::Extraexpanded:
    eM11 = 2.0;
    break;
  case ON_Font::Stretch::Ultraexpanded:
    eM11 = 3.0;
    break;
  }

  if (eM11 > 0.0 && 1.0 != eM11)
  {
    FIXED fx = { 1, 0 };
    double ffrac = fmod(eM11, 1.0);
    if (ffrac != ffrac)
      ffrac = 0.0;
    fx.fract = static_cast<unsigned short>(floor(65535.0 * ffrac));
    fx.value = static_cast<short>(eM11 - ffrac);
    mat2.eM11 = fx;
  }

  return mat2;
}


#endif

void ON_Font::DestroyFontGlyphCache()
{
  m_font_glyph_cache.reset();
}

class ON_FontGlyphCache* ON_Font::FontGlyphCache(
  bool bCreateIfMissing
  ) const
{  
  ON_FontGlyphCache* font_cache = m_font_glyph_cache.get();
  if(nullptr == font_cache)
  {
    // get the static ON_Font that matches this one
    const ON_Font* managed_font = this->ManagedFont();
    if(nullptr != managed_font)
    {
      // The first call to ON_Font::GetManagedFont() adds
      // &ON_Font::Default and calculates its font metric
      // and glyph information. The this != managed_font
      // text below prevents a silly copy in this case
      // and in other unanticipated cases.
      if ( this != managed_font)
        m_font_glyph_cache = managed_font->m_font_glyph_cache;
      font_cache = m_font_glyph_cache.get();
    }
  }
  return font_cache;
}

// static
void ON_Font::GetRunBounds(
  const ON_Font& font,
  const wchar_t* text,
  double font_height_pixels,
  ON::TextHorizontalAlignment horizontal_alignment,
  ON::TextVerticalAlignment vertical_alignment,
  ON_2dPoint& bounds_min,
  ON_2dPoint& bounds_max, 
  int& line_count
)
{
  line_count = 0;
  bounds_min = ON_2dPoint::Origin;
  bounds_max = ON_2dPoint::Origin;

  ON_wString run = text;
  int textlength = run.Length();
  if(textlength < 1)
    return;

  const ON_Font* managed_font = font.ManagedFont();
  if (nullptr == managed_font)
    managed_font = &ON_Font::Default;

  const ON_FontMetrics& fm = managed_font->FontMetrics();

  const int height_of_I = fm.AscentOfCapital();
  const int height_of_LF = fm.LineSpace();

  ON_TextBox text_box;
  line_count = ON_FontGlyph::GetGlyphListBoundingBox(text, managed_font, text_box);
  if ( line_count < 0 || false == text_box.IsSet())
    return;

  bounds_min.x = text_box.m_bbmin.i;
  bounds_min.y = text_box.m_bbmin.j;

  bounds_max.x = text_box.m_bbmax.i;
  bounds_max.y = text_box.m_bbmax.j;

  // in text_box coordinate system (0.0) = left most baseline point of first line.
  const ON_2dPoint first_line_basepoint = ON_2dPoint::Origin;
  const ON_2dPoint last_line_basepoint(first_line_basepoint.x, -(line_count - 1)*height_of_LF);

  ON_2dVector offset = ON_2dVector::ZeroVector;

  switch (horizontal_alignment)
  {
  case ON::TextHorizontalAlignment::Left:
    offset.x = -first_line_basepoint.x;
    break;

  case ON::TextHorizontalAlignment::Center:
    // Text command uses m_max_basepoint (not bbmax)
    offset.x = -first_line_basepoint.x - 0.5*text_box.m_max_basepoint.i;
    break;

  case ON::TextHorizontalAlignment::Right:
    // Text command uses m_max_basepoint (not bbmax)
    offset.x = -first_line_basepoint.x - text_box.m_max_basepoint.i;
    break;
  default:
    break;
  }

  switch (vertical_alignment)
  {
  case ON::TextVerticalAlignment::Top:
    // (*,0) is at the top of an "I" on the first line.
    offset.y = -first_line_basepoint.y - height_of_I;
    break;
  case ON::TextVerticalAlignment::MiddleOfTop:
    // (*,0) is at the middle of an "I" on the first line.
    offset.y = -first_line_basepoint.y - 0.5*height_of_I;
    break;
  case ON::TextVerticalAlignment::BottomOfTop:
    // (*,0) is at the baseline of the first line.
    offset.y = -first_line_basepoint.y;
    break;

  case ON::TextVerticalAlignment::Middle:
    {
      // (*,0) is the vertical middle of lines (not vertical middle of glyph bounding box)
      double h = (line_count - 1)*height_of_LF + height_of_I;
      offset.y = -last_line_basepoint.y + 0.5*h;
    }
    break;

  case ON::TextVerticalAlignment::MiddleOfBottom:
    // (*,0) is at the middle of an "I" on the last line.
    offset.y = -last_line_basepoint.y  - 0.5*height_of_I;
    break;
  case ON::TextVerticalAlignment::Bottom:
    // (*,0) is at the basline of the last line.
    offset.y = -last_line_basepoint.y;
    break;
  case ON::TextVerticalAlignment::BottomOfBoundingBox:
    // (*,0) is on the bottom the the glyphs' bounding box
    offset.y = -bounds_min.y;
    break;
  default:
    break;
  }

  bounds_min += offset;
  bounds_max += offset;

  // scale is applied last.
  const double scale = font_height_pixels / (double)ON_Font::Constants::AnnotationFontCellHeight;
  if (scale > 0.0)
  {
    bounds_min.x = scale * text_box.m_bbmin.i;
    bounds_max.x = scale * text_box.m_bbmax.i;
    bounds_min.y = scale * text_box.m_bbmin.j;
    bounds_max.y = scale * text_box.m_bbmax.j;
  }
}

const ON_FontGlyph* ON_Font::Internal_ManagedCodePointGlyph(
  ON__UINT32 unicode_code_point,
  bool bCreateIfMissing,
  bool bFindSubstitutes
) const
{
  if ( false == ON_IsValidUnicodeCodePoint(unicode_code_point) )
  {
    // valid UNICODE codepoint values are <= 0x10FFFF
    ON_ERROR("invalid codepoint parameter.");
    return nullptr;
  }

  if (false == IsManagedFont())
  {
    ON_ERROR("this->IsManagedFont() must be true.");
    return nullptr; 
  }
  
  // First see if we already have the glyph in the cache
  ON_FontGlyphCache* font_cache = FontGlyphCache(true);
  ON_GlyphMap* glyph_map
    = (nullptr == font_cache)
    ? nullptr
    : font_cache->m_glyphmap.get();
  if (nullptr == glyph_map)
  {
    ON_ERROR("Unable to create ON_FontGlyphCache.");
    return nullptr;
  }

  const ON_FontGlyph* managed_glyph = glyph_map->FindGlyph(unicode_code_point);
  if (nullptr != managed_glyph)
    return managed_glyph;

  if (false == bCreateIfMissing)
    return nullptr;

  ON_FontGlyph glyph;
  glyph.SetCodePoint(this, unicode_code_point);

  // Call external function to get glyph details
  ON_TextBox font_unit_glyph_box = ON_TextBox::Unset;
  const unsigned int font_glyph_index = ON_ManagedFonts::GetGlyphMetricsInFontDesignUnits(this, unicode_code_point, font_unit_glyph_box);
  if (0 != font_glyph_index)
  {
    if (font_unit_glyph_box.IsSet())
    {
      glyph.m_font_unit_glyph_bbox = font_unit_glyph_box;
      // Save a normalized box as well.
      const double normalize_scale = this->FontUnitToNormalizedScale();
      ON_TextBox normalized_glyph_box = font_unit_glyph_box;
      if (normalize_scale > 0.0)
        normalized_glyph_box = ON_TextBox::Scale(font_unit_glyph_box, normalize_scale);
      glyph.m_normalized_glyph_bbox = normalized_glyph_box;
    }
    glyph.Internal_SetFontGlyphIndex(font_glyph_index);
    bFindSubstitutes = false;
  }


  return glyph_map->InsertGlyph(glyph);
}

#if defined(ON_RUNTIME_WIN)

static bool ON_Internal_WindowsGetGlyphMetricsEx(
  const ON_Font* font,
  int logfont_height,
  ON__UINT32 unicode_code_point,
  class ON_TextBox& font_unit_glyph_box
)
{
  font_unit_glyph_box = ON_TextBox::Unset;

  if (logfont_height <= 0)
    logfont_height = ON_Font::Constants::AnnotationFontCellHeight;

  if (false == ON_IsValidUnicodeCodePoint(unicode_code_point) )
    return false;
  if (nullptr == font)
    return false;
  font = font->ManagedFont();
  if (nullptr == font)
    return false;

  wchar_t w[8] = { 0 };
  const size_t w_capacity = (sizeof(w) / sizeof(w[0])) - 1;
  const int w_count = ON_EncodeWideChar(unicode_code_point, w_capacity, w);
  if ( 0 == w[0] || w_count <= 0 || w_count > (int)w_capacity )
    return false;
  
  HDC font_hdc = nullptr;
  HFONT hfont = nullptr;
  HGDIOBJ hfont0 = nullptr;

  for (;;)
  {
    font_hdc = ON_Font::CreateWindowsLogfontDeviceContext();
    if (nullptr == font_hdc)
      break;

    LOGFONT lf = font->WindowsLogFont(0,nullptr);
    lf.lfHeight = logfont_height;
    hfont = ::CreateFontIndirect(&lf);
    if (nullptr == hfont)
      break;
    hfont0 = ::SelectObject(font_hdc, hfont);

    ON__UINT16 glyphindex[sizeof(w)/sizeof(w[0])] = { 0 };
    const DWORD gicount = ::GetGlyphIndices(font_hdc, w, w_count, glyphindex, GGI_MARK_NONEXISTING_GLYPHS);
    if (GDI_ERROR == gicount)
      break;
    if (0xffff == glyphindex[0] || 0xffff == glyphindex[1])
    {
      // March 2017 Dale Lear
      // https://mcneel.myjetbrains.com/youtrack/issue/RH-38377
      //
      // The GGI_MARK_NONEXISTING_GLYPHS flag causes GetGlyphIndices()
      // to set glyphindex[] values to 0xFFFF for missing glyphs.
      //
      // GetGlyphIndices() is not capable of getting this glyph in the hdc font.
      // This often happes for surrogate pair encodings, even when the 
      // glyph does exist in the font.
      //
      // GetGlyphIndices cannot find glyph in the font
      // Often a surrogate pair and we probably need to be using 
      // Windows newer Uniscribe API instead of the tired old
      // GetGlyphIndices + GetGlyphOutlineW stuff.
      break; 
    }

    GLYPHMETRICS glm;
    memset(&glm, 0, sizeof(glm));
    MAT2 mat2 = font->WindowsFontMat2();
    const DWORD cb_size = ::GetGlyphOutlineW(font_hdc, glyphindex[0], GGO_NATIVE | GGO_GLYPH_INDEX, &glm, 0, nullptr, &mat2);
    if (GDI_ERROR == cb_size)
      break;

    ////bool ul = false, so = false;
    ////int ulsize = 0, ulpos = 0, sosize = 0, sopos = 0;
    ////HGDIOBJ hfont = GetCurrentObject(hdc, OBJ_FONT);
    ////LOGFONT lf = { 0 };
    ////if (sizeof(lf) == GetObject(hfont, sizeof(lf), &lf))
    ////{
    ////  ul = lf.lfUnderline ? true : false;
    ////  so = lf.lfStrikeOut ? true : false;
    ////}

    ////if (ul || so)
    ////{
    ////  OUTLINETEXTMETRIC otm = { 0 };
    ////  if (0 != ::GetOutlineTextMetrics(hdc, sizeof(OUTLINETEXTMETRIC), &otm))
    ////  {
    ////    sosize = otm.otmsStrikeoutSize;
    ////    sopos = otm.otmsStrikeoutPosition;
    ////    ulsize = otm.otmsUnderscoreSize;
    ////    ulpos = otm.otmsUnderscorePosition;
    ////  }
    ////}

    font_unit_glyph_box.m_advance.i = glm.gmCellIncX;
    font_unit_glyph_box.m_advance.j = glm.gmCellIncY;
    if (cb_size == 0)
    {
      // Non-printing char - nothing to draw
      font_unit_glyph_box.m_bbmin.i = 0;
      font_unit_glyph_box.m_bbmin.j = 0;
      font_unit_glyph_box.m_bbmax.i = font_unit_glyph_box.m_advance.i;
      font_unit_glyph_box.m_bbmax.j = font_unit_glyph_box.m_advance.j;
    }
    else
    {
      font_unit_glyph_box.m_bbmin.i = glm.gmptGlyphOrigin.x;
      font_unit_glyph_box.m_bbmin.j = glm.gmptGlyphOrigin.y - (int)glm.gmBlackBoxY;
      font_unit_glyph_box.m_bbmax.i = (int)glm.gmBlackBoxX + glm.gmptGlyphOrigin.x;
      font_unit_glyph_box.m_bbmax.j = glm.gmptGlyphOrigin.y;
    }

    break;
  }

  if (nullptr != font_hdc)
  {
    if (nullptr != hfont)
    {
      ::SelectObject(font_hdc, hfont0);
      ::DeleteObject(hfont);
    }
    ON_Font::DeleteWindowsLogfontDeviceContext(font_hdc);
  }

  return font_unit_glyph_box.IsSet();
}

bool ON_WindowsGetGlyphMetrics(
  const ON_Font* font,
  ON__UINT32 unicode_code_point,
  class ON_TextBox& font_unit_glyph_box
)
{
  return ON_Internal_WindowsGetGlyphMetricsEx(font, 0, unicode_code_point, font_unit_glyph_box);
}

#endif

void ON_Font::SetCustomMeasurementFunctions(
  ON_GetGlyphMetricsFuncType measureGlyphFunc,
  ON_GetFontMetricsFuncType metricsFunc
)
{
  ON_Font::Internal_CustomGetGlyphMetricsFunc = measureGlyphFunc;
  ON_Font::Internal_CustomGetFontMetricsFunc = metricsFunc;
}

unsigned int ON_ManagedFonts::GetGlyphMetricsInFontDesignUnits(
  const class ON_Font* font,
  ON__UINT32 unicode_code_point,
  class ON_TextBox& glyph_metrics_in_font_design_units
)
{
  unsigned int glyph_index = 0;

  const ON_FontGlyph g(font, unicode_code_point);

  if (nullptr != ON_Font::Internal_CustomGetGlyphMetricsFunc)
  {
    glyph_index = ON_Font::Internal_CustomGetGlyphMetricsFunc(&g, glyph_metrics_in_font_design_units);
    if (0 != glyph_index)
      return glyph_index;
  }

#if defined(ON_OS_WINDOWS_GDI)
  glyph_index = ON_WindowsDWriteGetGlyphMetrics(&g, glyph_metrics_in_font_design_units);
#elif defined(ON_RUNTIME_APPLE_CORE_TEXT_AVAILABLE)
  glyph_index = ON_AppleFontGetGlyphMetrics(&g, glyph_metrics_in_font_design_units);
#elif defined(OPENNURBS_FREETYPE_SUPPORT)
  // Look in opennurbs_system_rumtime.h for the correct place to define OPENNURBS_FREETYPE_SUPPORT.
  // Do NOT define OPENNURBS_FREETYPE_SUPPORT here or in your project setting ("makefile").
  glyph_index = ON_FreeTypeGetGlyphMetrics(&g, glyph_metrics_in_font_design_units);
#endif

  if (0 != glyph_index)
    return glyph_index;

  glyph_metrics_in_font_design_units = ON_TextBox::Unset;
  return 0;
}

bool ON_ManagedFonts::GetFontMetricsInFontDesignUnits(
  const ON_Font* font,
  ON_FontMetrics& font_metrics_in_font_design_units
)
{
  if (nullptr == font)
  {
    font_metrics_in_font_design_units = ON_FontMetrics::LastResortMetrics;
    return false;
  }

  const ON_FontGlyphCache* font_glyph_cache = font->m_font_glyph_cache.get();
  if (nullptr != font_glyph_cache && font_glyph_cache->m_font_unit_metrics.HeightsAreValid())
  {
    if (font_glyph_cache->m_font_unit_metrics.HeightsAreValid())
    {
      font_metrics_in_font_design_units = font_glyph_cache->m_font_unit_metrics;
      return true;
    }
  }

  ON_FontMetrics fm(ON_FontMetrics::Unset);
  for (;;)
  {
    if (nullptr != ON_Font::Internal_CustomGetFontMetricsFunc)
    {
      ON_Font::Internal_CustomGetFontMetricsFunc(font, fm);
      if (fm.AscentDescentAndUPMAreValid())
        break;
    }

#if defined(ON_OS_WINDOWS_GDI)
    ON_WindowsDWriteGetFontMetrics(font, fm);
#elif defined(ON_RUNTIME_APPLE_CORE_TEXT_AVAILABLE)
    ON_AppleFontGetFontMetrics(font, fm);
#elif defined(OPENNURBS_FREETYPE_SUPPORT)
    // Look in opennurbs_system_rumtime.h for the correct place to define OPENNURBS_FREETYPE_SUPPORT.
    // Do NOT define OPENNURBS_FREETYPE_SUPPORT here or in your project setting ("makefile").
    ON_FreeTypeGetFontMetrics(font, fm);
#endif
    
    break;
  }

  if (false == fm.AscentDescentAndUPMAreValid())
  {
    font_metrics_in_font_design_units = ON_FontMetrics::LastResortMetrics;
    return false;
  }

  if (fm.HeightsAreValid() && (fm.AscentOfCapital() > 0 || fm.Ascent() <= 0))
  {
    font_metrics_in_font_design_units = fm;
    return true;
  }

  const int UPM = fm.UPM();
  const int ascent = fm.Ascent();
  const int descent = fm.Descent();
  const int line_space =
    (fm.LineSpace() >= (ascent - descent) && fm.LineSpace() < 0xFFFF)
    ? fm.LineSpace()
    : (int)ceil(ON_FontMetrics::DefaultLineFeedRatio*(ascent - descent));
  const int ascent_of_capital = fm.AscentOfCapital();
  const int ascent_of_x = fm.AscentOfx();

  fm.SetHeights(ascent, descent, UPM, line_space);
  fm.SetAscentOfCapital((ascent_of_capital > 0 && ascent_of_capital <= ascent) ? ascent_of_capital : ascent);
  fm.SetAscentOfx((ascent_of_x > 0 && ascent_of_x <= ascent) ? ascent_of_x : 0);

  font_metrics_in_font_design_units
    = (fm.HeightsAreValid())
    ? fm
    : ON_FontMetrics::LastResortMetrics;

  return false;
}

void ON_ManagedFonts::Internal_SetFakeWindowsLogfontName(
  const ON_Font * font,
  const ON_wString fake_loc_logfont_name, 
  const ON_wString fake_en_logfont_name
)
{
  if (nullptr == font)
    return;
  const_cast<ON_Font * >(font)->m_loc_windows_logfont_name = fake_loc_logfont_name;
  const_cast<ON_Font * >(font)->m_en_windows_logfont_name = fake_en_logfont_name;
}

void ON_ManagedFonts::Internal_SetFakeWindowsLogfontNames(
  ON_SimpleArray<const ON_Font*>& device_list
)
{
  // Windows divides font families (which can have many faces) 
  // into LOGFONT subsets identified by a logfont name.
  // A LOGFONT subset can have at most 4 faces and typically 
  // they are regular/bold/italic/bold-italic variations of 
  // a face and all have matching stretch.
  //
  // This all goes back to the 1970's and early user interfaces
  // that selected fonts based on a name, bold=true/false, italic=true/false
  // style inteface. This type of archaic font selection interface is way 
  // too simple to accomodate the rich font families are currently in use.
  // Newer font families can have dozens of faces with severeal weights,
  // several widths, and an upright and italic version of each of these.
  // However, that does not prevent applications like Rhino 6/7 
  // from attempting to use the inadequate and archic bold/italic font
  // selection interface to select a font from a rich list of modern fonts.
  //
  // This function is used on non Windows platforms to partition 
  // the installed font families into subsets with the same
  // width and set a unique fake LOGFONT name. Later sorting will
  // choose up to four faces from each subset to use as the 
  // regular/bold/italic/bold-italic representatives.

  // Assign a fake logfont name.
  const unsigned int font_count = device_list.UnsignedCount();
  for (unsigned int i = 0; i < font_count; ++i)
  {
    const ON_Font* f0 = device_list[i];
    if (nullptr == f0)
      continue;

    ON_wString fake_loc_logfont_name = ON_Font::FakeWindowsLogfontNameFromFamilyAndPostScriptNames(
      f0->FamilyName(ON_Font::NameLocale::LocalizedFirst),
      f0->PostScriptName(ON_Font::NameLocale::LocalizedFirst)
    );
    if (fake_loc_logfont_name.IsEmpty())
      continue;
    ON_wString fake_en_logfont_name = ON_Font::FakeWindowsLogfontNameFromFamilyAndPostScriptNames(
      f0->FamilyName(ON_Font::NameLocale::English),
      f0->PostScriptName(ON_Font::NameLocale::English)
    );
    if (fake_en_logfont_name.IsEmpty())
      fake_en_logfont_name = fake_loc_logfont_name;
    else if (false == fake_loc_logfont_name.EqualOrdinal(fake_en_logfont_name, true))
    {
      const bool bLocalFaceIsFamilyName = fake_loc_logfont_name.EqualOrdinal(f0->FamilyName(ON_Font::NameLocale::LocalizedFirst), true);
      const bool bEnglishFaceIsFamilyName = fake_en_logfont_name.EqualOrdinal(f0->FamilyName(ON_Font::NameLocale::English), true);
      if (bLocalFaceIsFamilyName && false == bEnglishFaceIsFamilyName)
        fake_loc_logfont_name = fake_en_logfont_name;
      else if (bEnglishFaceIsFamilyName && false == bLocalFaceIsFamilyName)
        fake_en_logfont_name = fake_loc_logfont_name;
    }

    ON_ManagedFonts::Internal_SetFakeWindowsLogfontName(
      f0,
      fake_loc_logfont_name,
      fake_en_logfont_name
    );
  }

  // Sort device_list by font family and current fake LOGFONT name
  device_list.QuickSort(ON_FontList::CompareFamilyAndWindowsLogfontName);
  ON_SimpleArray<const ON_Font*> quartet_candidates(128);
  bool bSortAgain = false;
  for (unsigned int i = 0; i < font_count; ++i)
  {
    const ON_Font* f0 = device_list[i];
    if (nullptr == f0)
      continue;

    quartet_candidates.SetCount(0);
    quartet_candidates.Append(f0);
    while( (i + 1) < font_count )
    {
      const ON_Font* f = device_list[i + 1];
      if (nullptr == f || 0 != ON_FontList::CompareFamilyAndWindowsLogfontName(&f0, &f))
        break;
      quartet_candidates.Append(f);
      ++i;
    }
    const unsigned int quartet_candidate_count = quartet_candidates.UnsignedCount();
    if (quartet_candidate_count < 2)
      continue;

    // members in a fake LOGFONT quartet should have the same stretch
    quartet_candidates.QuickSort(ON_FontList::CompareStretch);

    // See which subset of family gets to use the family name as 
    // the fake logfont name.
    const int medium_stretch = (int)((unsigned)(ON_Font::Stretch::Medium));
    ON_Font::Stretch stretch0 = quartet_candidates[0]->FontStretch();
    int delta_stretch = abs(medium_stretch - ((int)((unsigned)(stretch0))));
    bool bNeedToModifyFakeName = false;
    for (unsigned int j = 0; j < quartet_candidate_count; ++j)
    {
      const ON_Font::Stretch stretch = quartet_candidates[j]->FontStretch();
      int ds = abs(medium_stretch - ((int)((unsigned)(stretch))));
      if (ds < delta_stretch)
      {
        stretch0 = stretch;
        delta_stretch = ds;
        bNeedToModifyFakeName = true;
      }
    }

    if (false == bNeedToModifyFakeName)
      continue; // we cannot use stretch to distinguish between family members

    // If a family member's stretch is not stretch0, modify its names.
    for (unsigned int j = 0; j < quartet_candidate_count; ++j)
    {
      const ON_Font* f = quartet_candidates[j];
      const ON_Font::Stretch stretch = f->FontStretch();
      if (stretch == stretch0)
        continue;
      ON_wString suffix = L" (";
      suffix += ON_Font::StretchToWideString(stretch);
      if (suffix.Length() < 3)
        continue;
      suffix += L")";
      const ON_wString loc_name = f->m_loc_windows_logfont_name+suffix;
      const ON_wString en_name = f->m_en_windows_logfont_name+suffix;
      ON_ManagedFonts::Internal_SetFakeWindowsLogfontName(f,loc_name,en_name);
      bSortAgain = true;
    }
  }

  if (bSortAgain)
    device_list.QuickSort(ON_FontList::CompareFamilyAndWindowsLogfontName);

}

const ON_FontList& ON_ManagedFonts::InstalledFonts()
{
  if (0 == List.m_installed_fonts.Count())
  {
    ON_MemoryAllocationTracking disable_tracking(false);
    ON_SimpleArray<const ON_Font*> device_list;
#if defined(ON_OS_WINDOWS_GDI)
    ON_ManagedFonts::Internal_GetWindowsInstalledFonts(device_list);
#elif defined (ON_RUNTIME_APPLE_CORE_TEXT_AVAILABLE)
    ON_ManagedFonts::Internal_GetAppleInstalledCTFonts(device_list);
    ON_ManagedFonts::Internal_SetFakeWindowsLogfontNames(device_list);
#endif
    if (device_list.Count() > 0)
    {
      // Cull exact duplicates which occur in fonts like SLF..., Noto Emoji", ...
      const int count = device_list.Count();
      ON_SimpleArray<int> index(count);
      for (int i = 0; i < count; ++i)
        index.Append(i);
      ON_Sort(ON::sort_algorithm::quick_sort, index.Array(), device_list.Array(), device_list.Count(), sizeof(ON__UINT_PTR), (int (*)(const void*, const void*))ON_FontList::CompareFontCharacteristicsHash);
      int j0 = index[0];
      bool bCullNulls = false;
      for (int i = 1; i < count; ++i)
      {
        int j1 = index[i];
        if (j0 == j1)
          continue;
        const ON_Font* f0 = device_list[j0];
        const ON_Font* f1 = device_list[j1];
        if (0 == ON_FontList::CompareFontCharacteristicsHash(&f0, &f1))
        {
          // duplicate font - keep the first one the platform delivered.
          if (j0 < j1)
          {
            device_list[j1] = nullptr;
            delete const_cast<ON_Font*>(f1);
            bCullNulls = true;
          }
          else if (j0 > j1)
          {
            device_list[j0] = nullptr;
            delete const_cast<ON_Font*>(f0);
            j0 = j1;
            bCullNulls = true;
          }
        }
        else
          j0 = j1;
      }

      if (bCullNulls)
      {
        int count1 = 0;
        for (int i = 0; i < count; ++i)
        {
          const ON_Font* f = device_list[i];
          if (nullptr == f)
            continue;
          device_list[count1++] = f;
        }
        device_list.SetCount(count1);
      }
      
      List.m_installed_fonts.AddFonts(device_list);
      List.m_installed_fonts.Internal_UpdateSortedLists();
    }
  }

  if (List.m_installed_fonts.Count() > 0)
  {
    // Calling List.m_installed_fonts.QuartetList() sets ON_Font::m_quartet_member
    // for all installled font on Apple and for damaged installed fonts on Windows.
    // See comments near the end of ON_FontList::QuartetList().
     List.m_installed_fonts.QuartetList();
  }

  return List.m_installed_fonts;
}

