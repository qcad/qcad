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

#include "opennurbs_parse.h"

#define ON_UNICODE_QUOTATION_MARK 0x0022
#define ON_WCHAR_QUOTATION_MARK L"\""

#define ON_UNICODE_APOSTROPHE 0x0027
#define ON_WCHAR_APOSTROPHE L"\'"

#define ON_UNICODE_LOW_LINE 0x005F

#define ON_UNICODE_DEGREE_SYMBOL 0x00B0
#define ON_WCHAR_DEGREE_SYMBOL L"\x00B0"

// The unicode masculine ordinal indicator (Spanish)
// is often mistakenly used as a degrees symbol.
#define ON_UNICODE_MASCULINE_ORDINAL_INDICATOR 0x00BA
#define ON_WCHAR_MASCULINE_ORDINAL_INDICATOR L"\x00BA"

#define ON_UNICODE_LATIN_SMALL_LETTER_SHARP_S 0x00DF
#define ON_WCHAR_LATIN_SMALL_LETTER_SHARP_S L"\x00DF"

#define ON_UNICODE_LATIN_CAPITAL_LETTER_U_WITH_RING_ABOVE 0x016E
#define ON_WCHAR_LATIN_CAPITAL_LETTER_U_WITH_RING_ABOVE L"\x016E"

#define ON_UNICODE_LATIN_SMALL_LETTER_U_WITH_RING_ABOVE 0x016F
#define ON_WCHAR_LATIN_SMALL_LETTER_U_WITH_RING_ABOVE L"\x016F"

#define ON_UNICODE_LATIN_CAPITAL_LETTER_SHARP_S 0x1E9E

#define ON_UNICODE_GREEK_CAPITAL_LETTER_TAU 0x03A4

#define ON_UNICODE_GREEK_SMALL_LETTER_TAU 0x03C4
#define ON_WCHAR_GREEK_SMALL_LETTER_TAU L"\x03C4"

#define ON_RHINO_LOCALE_ID 1
#define ON_INVALID_LOCALE_ID 2
#define ON_CS_CZ_LOCALE_ID ON_Locale::WindowsLCID::cs_CZ_LCID
#define ON_DE_DE_LOCALE_ID ON_Locale::WindowsLCID::de_DE_LCID
#define ON_EN_CA_LOCALE_ID ON_Locale::WindowsLCID::en_CA_LCID
#define ON_EN_US_LOCALE_ID ON_Locale::WindowsLCID::en_US_LCID
#define ON_ES_ES_LOCALE_ID ON_Locale::WindowsLCID::es_ES_LCID
#define ON_FR_FR_LOCALE_ID ON_Locale::WindowsLCID::fr_FR_LCID
#define ON_IT_IT_LOCALE_ID ON_Locale::WindowsLCID::it_IT_LCID
#define ON_PL_PL_LOCALE_ID ON_Locale::WindowsLCID::pl_PL_LCID
#define ON_PT_PT_LOCALE_ID ON_Locale::WindowsLCID::pt_PT_LCID

class ON_UnitName
{
public:
  // The size and field alignment of ON_UnitName must exactly match
  // that of ON_LengthUnitName and ON_AngleUnitName
  // Microsoft locale id // http://msdn.microsoft.com/en-us/library/ms912047(v=winembedded.10).aspx
  unsigned int m_locale_id; 

  // ON::LengthUnitSystem or ON::AngleUnitSystem enum value
  unsigned char m_unit_system;       

  bool m_bIsSingular;
  bool m_bIsPlural;

  const wchar_t* m_name;

};

class ON_UnitNameEx : public ON_UnitName
{
public:


  enum
  {
    m_utf32_name_capacity = 24
  };

  // Simplified name - used for speedy unit name searches.
  ON__UINT32 m_utf32_name[ON_UnitNameEx::m_utf32_name_capacity]; // null terminated utf-32 encoded lower case simple latin name string.
  unsigned int m_utf32_name_count; // number of nonzero wchar_t elements in m_name[] array

  /*
  Description:
    Parses m_name and sets the m_utf32_name[] and m_utf32_name_count
    fields.
  Returns:
    Number of elements of m_name that were parsed; 0 indicates failure.
  Remarks:
    m_name must contain a character that terminates unit system name parsing.
    This can be a null, digit, punctuation, arithmetic operator, or a
    unicode code point <= 0x0020 (0x0020 = space = 32 decimal).
  */
  int SetSimplifiedName();

  static int Compare(const ON_UnitNameEx*, const ON_UnitNameEx*);
  static int Compare_m_utf32_name(const ON_UnitNameEx*, const ON_UnitNameEx*);
  static int Compare_m_name(const ON_UnitNameEx*, const ON_UnitNameEx*);
};

static ON_UnitName si_length_units[] =
{
  //////////////////////////////////////////////////////////////
  //
  // SI length units universal
  //
  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), true, true, L"mm" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), true, true, L"cm" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), true, true,      L"m" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), true, true,  L"km" },

  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), true, true, L"_mm" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), true, true, L"_cm" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), true, true,      L"_m" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), true, true,  L"_km" },

  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), false, true, L"_millimeters" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), true, false, L"_millimeter" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), false, true, L"_centimeters" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), true, false, L"_centimeter" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), false, true,      L"_meters" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), true, false,      L"_meter"},
  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), false, true,  L"_kilometers" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), true, false,  L"_kilometer" },

  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), false, true, L"_millimetres" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), true, false, L"_millimetre" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), false, true, L"_centimetres" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), true, false, L"_centimetre" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), false, true,      L"_metres" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), true, false,      L"_metre" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), false, true,  L"_kilometres" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), true, false,  L"_kilometre" },


  //////////////////////////////////////////////////////////////
  //
  // SI length units cs-* Czech
  //
  {ON_CS_CZ_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), false, true, L"milimetr" ON_WCHAR_LATIN_SMALL_LETTER_U_WITH_RING_ABOVE },
  {ON_CS_CZ_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), false, true, L"milimetry" },
  {ON_CS_CZ_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), true, false, L"milimetr" },
  {ON_CS_CZ_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), false, true, L"centimetr" ON_WCHAR_LATIN_SMALL_LETTER_U_WITH_RING_ABOVE },
  {ON_CS_CZ_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), false, true, L"centimetry" },
  {ON_CS_CZ_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), true, false, L"centimetr" },
  {ON_CS_CZ_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), false, true,      L"metr" ON_WCHAR_LATIN_SMALL_LETTER_U_WITH_RING_ABOVE },
  {ON_CS_CZ_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), false, true,      L"metry" },
  {ON_CS_CZ_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), true, false,      L"metr" },
  {ON_CS_CZ_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), false, true,  L"kilometr" ON_WCHAR_LATIN_SMALL_LETTER_U_WITH_RING_ABOVE },
  {ON_CS_CZ_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), false, true,  L"kilometry" },
  {ON_CS_CZ_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), true, false,  L"kilometr" },

  //////////////////////////////////////////////////////////////
  //
  // SI length units de-* German
  //
  {ON_DE_DE_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), true, true, L"Millimeter" },
  {ON_DE_DE_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), true, true, L"Zentimeter" },
  {ON_DE_DE_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), true, true,      L"Meter" },
  {ON_DE_DE_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), true, true,  L"Kilometer" },
  // http://mcneel.myjetbrains.com/youtrack/issue/RH-34051
  // The words ending in n are not plural forms, they are inflected forms used in complete sentences.
  // They are included so information copied, possibly automatically, from documents into scripts will parse as expected.
  {ON_DE_DE_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), true, true, L"Millimetern" },
  {ON_DE_DE_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), true, true, L"Zentimetern" },
  {ON_DE_DE_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), true, true,      L"Metern" },
  {ON_DE_DE_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), true, true,  L"Kilometern" },
  // http://mcneel.myjetbrains.com/youtrack/issue/RH-34051
  // "zm" is not the way German speakers abbreviate zentimeter
  // NO // {ON_DE_DE_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), true, true,  L"zm" },

  //////////////////////////////////////////////////////////////
  //
  // SI length units en-CA (metric Canadian English)
  //
  {ON_EN_CA_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), false, true, L"millimetres" },
  {ON_EN_CA_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), true, false, L"millimetre" },
  {ON_EN_CA_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), false, true, L"centimetres" },
  {ON_EN_CA_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), true, false, L"centimetre" },
  {ON_EN_CA_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), false, true,      L"metres" },
  {ON_EN_CA_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), true, false,      L"metre" },
  {ON_EN_CA_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), false, true,  L"kilometres" },
  {ON_EN_CA_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), true, false,  L"kilometre" },

  //////////////////////////////////////////////////////////////
  //
  // SI length units en-US (metric American English)
  //
  {ON_EN_US_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), false, true, L"millimeters" },
  {ON_EN_US_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), true, false, L"millimeter" },
  {ON_EN_US_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), false, true, L"centimeters" },
  {ON_EN_US_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), true, false, L"centimeter" },
  {ON_EN_US_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), false, true,      L"meters" },
  {ON_EN_US_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), true, false,      L"meter" },
  {ON_EN_US_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), false, true,  L"kilometers" },
  {ON_EN_US_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), true, false,  L"kilometer" },

  //////////////////////////////////////////////////////////////
  //
  // SI length units es-* Spanish
  //
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), false, true, L"mil\x00EDmetros" },
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), true, false, L"mil\x00EDmetro" },
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), false, true, L"cent\x00EDmetros" },
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), true, false, L"cent\x00EDmetro" },
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), false, true, L"metros" },
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), true, false, L"metro" },
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), false, true, L"kil\x00F3metros" },
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), true, false, L"kil\x00F3metro" },

  //////////////////////////////////////////////////////////////
  //
  // SI length units fr-* French
  //
  {ON_FR_FR_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), false, true, L"millim\x00E8tres" },
  {ON_FR_FR_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), true, false, L"millim\x00E8tre" },
  {ON_FR_FR_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), false, true, L"centim\x00E8tres" },
  {ON_FR_FR_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), true, false, L"centim\x00E8tre" },
  {ON_FR_FR_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), false, true,      L"m\x00E8tres" },
  {ON_FR_FR_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), true, false,      L"m\x00E8tre" },
  {ON_FR_FR_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), false, true,  L"kilom\x00E8tres" },
  {ON_FR_FR_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), true, false,  L"kilom\x00E8tre" },

  //////////////////////////////////////////////////////////////
  //
  // SI length units it-* Italian
  //
  {ON_IT_IT_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), false, true, L"millimetri" },
  {ON_IT_IT_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), false, true, L"millimetro" },
  {ON_IT_IT_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), false, true, L"centimetri" },
  {ON_IT_IT_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), true, false, L"centimetro" },
  {ON_IT_IT_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), false, true,      L"metri" },
  {ON_IT_IT_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), true, false ,     L"metro"},
  {ON_IT_IT_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), false, true,  L"chilometri" },
  {ON_IT_IT_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), true, false,  L"chilometro" },
  // it-* abbreviation for chilometri is "km"

  //////////////////////////////////////////////////////////////
  //
  // SI length units pl-* Polish
  {ON_PL_PL_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), true, false, L"milimetr" },
  {ON_PL_PL_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), false, true, L"milimetr\x00F3w" },
  {ON_PL_PL_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), false, true, L"milimetry" },
  {ON_PL_PL_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), true, false, L"centymetr" },
  {ON_PL_PL_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), false, true, L"centymetr\x00F3w" },
  {ON_PL_PL_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), false, true, L"centymetry" },
  {ON_PL_PL_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), true, false,      L"metr" },
  {ON_PL_PL_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), false, true,      L"metr\x00F3w" },
  {ON_PL_PL_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), false, true,      L"metry" },
  {ON_PL_PL_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), true, false,  L"kilometr" },
  {ON_PL_PL_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), false, true,  L"kilometr\x00F3w" },
  {ON_PL_PL_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), false, true,  L"kilometry" },

  //////////////////////////////////////////////////////////////
  //
  // SI length units pt-* Portuguese
  {ON_PT_PT_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), false, true, L"mil\x00EDmetros" },
  {ON_PT_PT_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Millimeters), true, false, L"mil\x00EDmetro" },
  {ON_PT_PT_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), false, true, L"cent\x00EDmetros" },
  {ON_PT_PT_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Centimeters), true, false, L"cent\x00EDmetro" },
  {ON_PT_PT_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), false, true,      L"metros" },
  {ON_PT_PT_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Meters), true, false,      L"metro" },
  {ON_PT_PT_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), false, true,  L"quil\x00F4metros" },
  {ON_PT_PT_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), true, false,  L"quil\x00F4metro" },
  // "qm" uilometro is abbreviated in Brazil and Portugual
  // NO // {ON_PT_PT_LOCALE_ID, static_cast<unsigned char>(ON::LengthUnitSystem::Kilometers), true, true,   L"qm" },
};

static ON_UnitName en_US_customary_length_units[] =
{
  //////////////////////////////////////////////////////////////
  //
  // United States customary units (Rhino - all locales)
  //
  //   All conversions to meters are exact.
  //   microinch =    2.54e-8 meters (1.0e-6 inches)
  //   mil       =    2.54e-5 meters (0.001 inches)
  //   inch      =    0.0254  meters (1/12 foot)
  //   foot      =    0.3048  meters (12 inches)
  //   yard      =    0.9144  meters (3 feet, 36 inches)
  //   mile      = 1609.344   meters (5280 feet)
  //
  // United States customary units are supported in en-US for two reasons.
  // 1) There is a internationally accepted definition of US customary
  //    lengths in terms of meters.  The international yard and pound
  //    agreement of July 1, 1959 defined one yard to be exactly 
  //    0.9144 meters which implies one inch is exactly 0.0254 meters.
  //    http://www.ngs.noaa.gov/PUBS_LIB/FedRegister/FRdoc59-5442.pdf
  // 2) These customary units are currently and widely used in the 
  //    United States. 
  //
  // United States customary units are not supported in any other
  // language or culture because there are no internationally 
  // accepted and commonly used definitions in terms of meters
  // that match the ones used in the United States and the units
  // are not commonly used in precise digital models.
  //
  // For an inlking of the peril of assuming a length unit in
  // Czech, French, Italian, Portuguese or Spanish that linguistically
  // translates to English "inch", "foot", or "mile" has the same physical
  // length as the "United States customary unit", see the references below.
  //   http://en.wikipedia.org/wiki/Foot_(unit)
  //   http://en.wikipedia.org/wiki/German_obsolete_units_of_measurement
  //   http://en.wikipedia.org/wiki/Spanish_customary_units
  //   http://en.wikipedia.org/wiki/Portuguese_customary_units
  //   http://en.wikipedia.org/wiki/Units_of_measurement_in_France
  //   http://www.convert-me.com/en/convert/length
  //   http://www.wordreference.com/czen/palec
  //   http://www.onlineunitconversion.com/braccio.Italy_to_miglio.html
  //
  // All conversions to meters and other US customary units are exact.
  //
  // 1 microinch = 2.54e-8 meters (1.0e-6 inches)
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Microinches), false, true, L"microinches" }, 
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Microinches), true, false, L"microinch" },
  // 1 mil = 2.54e-5 meters (0.001 inches)
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Mils), false, true, L"mils" },     
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Mils), true, false, L"mil" },
  // 1 inch = 0.0254 meters = 1/12 foot
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Inches), false, true, L"inches" }, 
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Inches), true, false, L"inch" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Inches), false, true, L"ins" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Inches), true, true, L"in" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Inches), true, true, ON_WCHAR_QUOTATION_MARK },
  // 1 foot = 0.3048 meters = 12 inches
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Feet), false, true, L"feet" },     
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Feet), true, false, L"foot" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Feet), true, true, L"ft" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Feet), true, true, ON_WCHAR_APOSTROPHE },
  // 1 yard = 0.9144 meters = 3 feet = 36 inches
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Yards), false, true, L"yards" },   
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Yards), true, false, L"yard" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Yards), false, true, L"yds" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Yards), true, true, L"yd" },    
  // 1 US statute mile = 1609.34 meters = 5280 feet
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Miles), false, true, L"miles" }, 
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Miles), true, false, L"mile" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Miles), true, true, L"mi" },

  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Microinches), true, true, L"_microinches" }, 
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Microinches), true, true, L"_microinch" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Mils), false, true, L"_mils" },     
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Mils), true, false, L"_mil" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Inches), false, true, L"_inches" }, 
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Inches), true, false, L"_inch" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Inches), false, true, L"_ins" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Inches), true, true, L"_in" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Feet), false, true, L"_feet" },     
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Feet), true, false, L"_foot" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Feet), true, true, L"_ft" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Yards), false, true, L"_yards" },   
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Yards), true, false, L"_yard" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Yards), false, true, L"_yds" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Yards), true, true, L"_yd" },    
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Miles), false, true, L"_miles" }, 
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Miles), true, false, L"_mile" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::LengthUnitSystem::Miles), true, true, L"_mi" },
};

static ON_UnitName angle_no_units[] =
{
  // These entries prevent parsing the strings unless an
  // entry for a locale explicitly includes the string and
  // the parsing preferred local id matches exactly.
  // The purpose is to prevent incorrectly parsing strings
  // the define different unit systems in different 
  // locales.

  // Many strings that begin with "g" can mean degrees
  // in one locale and gradians in another locale.
  {ON_INVALID_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::None), true, true,  L"g" },
  {ON_INVALID_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::None), true, true,  L"gs" },
  {ON_INVALID_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::None), true, true,  L"gc" },
  {ON_INVALID_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::None), true, true,  L"gd" },
  {ON_INVALID_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::None), true, true, L"grad" },
  {ON_INVALID_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::None), true, true, L"grads" },

  // "s" could mean degrees in Czech or Polish and seconds in English.
  {ON_INVALID_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::None), true, true,  L"s" },
};

static ON_UnitName angle_radian_units[] =
{

  //////////////////////////////////////////////////////////////
  //
  // radian units universal
  //
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), false, true, L"radians" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), true, false, L"radian" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), false, true, L"rads" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), true, false, L"rad" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), true, true,  L"r" },

  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), false, true, L"_radians" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), true, false, L"_radian" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), false, true, L"_rads" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), true, false, L"_rad" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), true, true,  L"_r" },

  //////////////////////////////////////////////////////////////
  //
  // radian units cs-* Czech
  //
  {ON_CS_CZ_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), false, true, L"radi\x00E1ny" },
  {ON_CS_CZ_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), true, false, L"radi\x00E1n" },

  //////////////////////////////////////////////////////////////
  //
  // radian units en-* (radians English)
  //
  {ON_EN_US_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), false, true, L"radians" },
  {ON_EN_US_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), true, false, L"radian" },

  //////////////////////////////////////////////////////////////
  //
  // radian units de-* German
  //
  {ON_DE_DE_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), true, true, L"Bogenma" ON_WCHAR_LATIN_SMALL_LETTER_SHARP_S },

  //////////////////////////////////////////////////////////////
  //
  // radian units es-* Spanish
  //
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), false, true, L"radianes" },
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), true, false, L"radi\x00E1n" },

  //////////////////////////////////////////////////////////////
  //
  // radian units fr-* French
  //
  {ON_FR_FR_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), false, true, L"radians" },
  {ON_FR_FR_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), true, false, L"radian" },

  //////////////////////////////////////////////////////////////
  //
  // radian units it-* Italian
  //
  {ON_IT_IT_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), false, true, L"radianti" },
  {ON_IT_IT_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), true, false, L"radiante" },

  //////////////////////////////////////////////////////////////
  //
  // radian units pl-* Polish
  {ON_PL_PL_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), false, true, L"radiany" },
  {ON_PL_PL_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), true, false, L"radian" },

  //////////////////////////////////////////////////////////////
  //
  // radian units pt-* Portuguese
  {ON_PT_PT_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), false, true, L"radians" },
  {ON_PT_PT_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Radians), true, false, L"radian" },

};

static ON_UnitName angle_degree_units[] =
{
  //////////////////////////////////////////////////////////////
  //
  // arc degree unit abbreviations (Rhino - all locales)
  //
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, true, ON_WCHAR_DEGREE_SYMBOL },
  // The unicode masuline ordinal indicator (Spanish) 
  // is often mistakenlyused as a degrees symbol.
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, true, ON_WCHAR_MASCULINE_ORDINAL_INDICATOR },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), false, true, L"degrees" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, false, L"degree" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), false, true, L"degs" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, false, L"deg" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, true, L"d" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), false, true, L"_degrees" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, false, L"_degree" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), false, true, L"_degs" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, false, L"_deg" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, true, L"_d" },

  //////////////////////////////////////////////////////////////
  //
  // arc degree units cs-* (Czech)
  //
  {ON_CS_CZ_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, true, L"stupn\x011B" },
  {ON_CS_CZ_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, true, L"stupe\x0148" },
  {ON_CS_CZ_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, true, L"stup" },

  //////////////////////////////////////////////////////////////
  //
  // arc degree units en-* (English)
  //
  {ON_EN_US_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), false, true, L"degrees" },
  {ON_EN_US_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, false, L"degree" },

  //////////////////////////////////////////////////////////////
  //
  // arc degree units de-* (German)
  //
  {ON_DE_DE_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, true, L"Grad" },

  //////////////////////////////////////////////////////////////
  //
  // arc degree units es-* (Spanish)
  //
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), false, true, L"grados" },
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, false, L"grado" },
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), false, true, L"grads" },
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, false, L"grad" },

  //////////////////////////////////////////////////////////////
  //
  // arc degree units fr-* (French)
  //
  {ON_FR_FR_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), false, true, L"degr\x00E9s" },
  {ON_FR_FR_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, false, L"degr\x00E9" },

  //////////////////////////////////////////////////////////////
  //
  // arc degree units it-* (Italian)
  //
  {ON_IT_IT_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), false, true, L"gradisessagesimali" },
  {ON_IT_IT_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, false, L"gradosessagesimale" },
  {ON_IT_IT_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), false, true, L"gradi" },
  {ON_IT_IT_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, false, L"grado" },
  {ON_IT_IT_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, true,  L"gs" },

  //////////////////////////////////////////////////////////////
  //
  // arc degree units pl-* Polish
  {ON_PL_PL_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, true, L"stopnie" },
  {ON_PL_PL_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, true, L"stopie\x0144" },
  {ON_PL_PL_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, true, L"stop" },

  //////////////////////////////////////////////////////////////
  //
  // arc degree units pt-* (Portuguese)
  {ON_PT_PT_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), false, true, L"graus" },
  {ON_PT_PT_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Degrees), true, false, L"grau" },
};

static ON_UnitName angle_minute_units[] =
{
  //////////////////////////////////////////////////////////////
  //
  // arc minute unit abbreviations (Rhino - all locales)
  //
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Minutes), true, true,  ON_WCHAR_APOSTROPHE },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Minutes), false, true, L"mins" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Minutes), true, false, L"min" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Minutes), true, true,  L"m" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Minutes), false, true, L"_minutes" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Minutes), true, false, L"_minute" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Minutes), false, true, L"_mins" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Minutes), true, false, L"_min" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Minutes), true, true,  L"_m" },

  //////////////////////////////////////////////////////////////
  //
  // arc minute units cs-* (Czech)
  //

  //////////////////////////////////////////////////////////////
  //
  // arc minute units en-* (English)
  //
  {ON_EN_US_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Minutes), false, true, L"minutes" },
  {ON_EN_US_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Minutes), true, false, L"minute" },

  //////////////////////////////////////////////////////////////
  //
  // arc minute units de-* (German)
  //

  //////////////////////////////////////////////////////////////
  //
  // arc minute units es-* (Spanish)
  //

  //////////////////////////////////////////////////////////////
  //
  // arc minute units fr-* (French)
  //

  //////////////////////////////////////////////////////////////
  //
  // arc minute units it-* (Italian)
  //

  //////////////////////////////////////////////////////////////
  //
  // arc minute units pt-* (Portuguese)
};

static ON_UnitName angle_second_units[] =
{
  //////////////////////////////////////////////////////////////
  //
  // arc second unit abbreviations (Rhino - all locales)
  //
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Seconds), true, true,  ON_WCHAR_QUOTATION_MARK },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Seconds), false, true, L"seconds" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Seconds), true, false, L"second" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Seconds), false, true, L"secs" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Seconds), true, false, L"sec" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Seconds), false, true, L"_seconds" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Seconds), true, false, L"_second" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Seconds), false, true, L"_secs" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Seconds), true, false, L"_sec" },

  //////////////////////////////////////////////////////////////
  //
  // arc second units cs-* (Czech)
  //

  //////////////////////////////////////////////////////////////
  //
  // arc second units en-* (English)
  //
  {ON_EN_US_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Seconds), false, true, L"seconds" },
  {ON_EN_US_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Seconds), true, false, L"second" },
  {ON_EN_US_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Seconds), true, true,  L"s" },

  //////////////////////////////////////////////////////////////
  //
  // arc second units de-* (German)
  //

  //////////////////////////////////////////////////////////////
  //
  // arc second units es-* (Spanish)
  //

  //////////////////////////////////////////////////////////////
  //
  // arc second units fr-* (French)
  //

  //////////////////////////////////////////////////////////////
  //
  // arc second units it-* (Italian)
  //

  //////////////////////////////////////////////////////////////
  //
  // arc second units pt-* (Portuguese)
};

static ON_UnitName angle_turn_units[] =
{
  //////////////////////////////////////////////////////////////
  //
  // turn unit universal
  //
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Turns), true, true,  ON_WCHAR_GREEK_SMALL_LETTER_TAU }, // unicode small tau symbol
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Turns), false, true, L"turns" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Turns), true, false, L"turn" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Turns), true, true,  L"t" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Turns), true, true,  L"_t" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Turns), false, true, L"_turns" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Turns), true, false, L"_turn" },

  //////////////////////////////////////////////////////////////
  //
  // turn units cs-* Czech
  //

  //////////////////////////////////////////////////////////////
  //
  // turn units en-* English
  //
  {ON_EN_US_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Turns), false, true, L"turns" },
  {ON_EN_US_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Turns), true, false, L"turn" },

  //////////////////////////////////////////////////////////////
  //
  // turn units de-* German
  //

  //////////////////////////////////////////////////////////////
  //
  // turn units es-* Spanish
  //

  //////////////////////////////////////////////////////////////
  //
  // turn units fr-* French
  //

  //////////////////////////////////////////////////////////////
  //
  // turn units it-* Italian
  //

  //////////////////////////////////////////////////////////////
  //
  // turn units pt-* Portuguese

};

static ON_UnitName angle_gradian_units[] =
{
  //////////////////////////////////////////////////////////////
  //
  // gradian units universal
  //
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), false, true, L"gons" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, false, L"gon" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), false, true, L"_gons" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, false, L"_gon" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), false, true, L"_gradians" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, false, L"_gradian" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), false, true, L"_grads" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, false, L"_grad" },
  {ON_RHINO_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, true,  L"_g" },

  //////////////////////////////////////////////////////////////
  //
  // gradian units cs-* Czech
  //
  {ON_CS_CZ_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), false, true, L"gradi\x00E1ny" },
  {ON_CS_CZ_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, false, L"grad" },
  {ON_CS_CZ_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, true,  L"g" },

  //////////////////////////////////////////////////////////////
  //
  // gradian units en-* English
  //
  {ON_EN_CA_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), false, true, L"gradians" },
  {ON_EN_CA_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, false, L"gradian" },
  {ON_EN_US_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), false, true, L"gradians" },
  {ON_EN_US_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, false, L"gradian" },
  {ON_EN_US_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), false, true, L"grads" },
  {ON_EN_US_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, false, L"grad" },
  {ON_EN_US_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, true,  L"g" },

  //////////////////////////////////////////////////////////////
  //
  // gradian units de-* German
  //
  // German uses the universal "gon" which is in ON_RHINO_LOCALE_ID

  //////////////////////////////////////////////////////////////
  //
  // gradian units es-* Spanish
  //
  // https://es.wikipedia.org/wiki/Grado_centesimal
  // http://blog.utp.edu.co/adriamec/files/2012/10/NTC1000.pdf (document page 8, PDF page 11)
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), false, true, L"gradianes" },
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, false, L"gradi\x00E1n" },
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), false, true, L"gons" },
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, false, L"gon" },
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), false, true, L"gradoscent" },
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, false, L"gradcent" },
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), false, true, L"gonios" },
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, false, L"gonio" },
  {ON_ES_ES_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, true,  L"gd" },

  //////////////////////////////////////////////////////////////
  //
  // gradian units fr-* French
  //
  {ON_FR_FR_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), false, true, L"grades" },
  {ON_FR_FR_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, false, L"grade" },
  {ON_FR_FR_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, true,  L"g" },

  //////////////////////////////////////////////////////////////
  //
  // gradian units it-* Italian
  //
  {ON_IT_IT_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), false, true, L"gradicent" },
  {ON_IT_IT_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, false, L"gradocent" },
  {ON_IT_IT_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, true,  L"gc" },

  //////////////////////////////////////////////////////////////
  //
  // gradian units pl-* Polish
  {ON_PL_PL_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), false, true, L"grads" },
  {ON_PL_PL_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, false, L"grad" },
  {ON_PL_PL_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, true,  L"g" },

  //////////////////////////////////////////////////////////////
  //
  // gradian units pt-* Portuguese
  //
  {ON_PT_PT_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), false, true, L"grads" },
  {ON_PT_PT_LOCALE_ID, static_cast<unsigned int>(ON::AngleUnitSystem::Gradians), true, false, L"grad" },
};

static unsigned int MapPreferedLocaleId(
  unsigned int prefered_locale_id
  )
{
  switch (prefered_locale_id)
  {
  case ON_Locale::WindowsLCID::es_ES_tradnl_LCID:
    prefered_locale_id = ON_Locale::WindowsLCID::es_ES_LCID;
    break;
  }

  return prefered_locale_id;
}

static int CompareNullPointers(const void* a, const void* b)
{
  if ( 0 == a || 0 == b )
  {
    if ( 0 != b )
      return -1;
    if ( 0 != a )
      return 1;
  }
  return 0;
}

int ON_UnitNameEx::Compare(const ON_UnitNameEx* a, const ON_UnitNameEx* b)
{
  int  rc = Compare_m_utf32_name(a,b);
  if ( 0 == rc && 0 != a && 0 != b )
  {
    if ( a->m_locale_id < b->m_locale_id )
      rc = -1;
    else if ( a->m_locale_id > b->m_locale_id )
      rc = 1;
    else
      rc = Compare_m_name(a,b);
  }
  return rc;
}

int ON_UnitNameEx::Compare_m_utf32_name(const ON_UnitNameEx* a, const ON_UnitNameEx* b)
{
  int rc = CompareNullPointers(a,b);
  if ( 0 != rc || 0 == a )
    return rc;

  if ( a->m_utf32_name_count < b->m_utf32_name_count )
    return -1;

  if ( a->m_utf32_name_count > b->m_utf32_name_count )
    return 1;

  ON__UINT32 x, y;
  const unsigned int capacity = ON_UnitNameEx::m_utf32_name_capacity;
  unsigned int i;

  for ( i = 0; i < capacity; i++ )
  {
    x = a->m_utf32_name[i];
    y = b->m_utf32_name[i];
    if ( x < y )
      return -1;
    if ( y < x )
      return 1;
    if ( 0 == x )
      break;
  }

  return 0;
}

int ON_UnitNameEx::Compare_m_name(const ON_UnitNameEx* a, const ON_UnitNameEx* b)
{
  int rc = CompareNullPointers(a,b);
  if ( 0 != rc || 0 == a )
    return rc;

  rc = CompareNullPointers(a->m_name,b->m_name);
  if ( 0 != rc || 0 == a->m_name )
    return rc;

  wchar_t x, y;
  unsigned int i = 0;
  for(;;)
  {
    x = a->m_name[i];
    y = b->m_name[i];
    if ( x < y )
      return -1;
    if ( y < x )
      return 1;
    if ( 0 == x )
      break;
    i++;
  }
  return 0;
}

static ON__UINT32 ON_ToLower( ON__UINT32 c )
{
  // This is a specialized and fast version that converts selected 
  // unicode capital latin letter code points to the corresponding
  // unicode latin small letter code points.  It is designed to be
  // used in code that has to quickly parse common unit names
  // in English, Spanish, French, German, Portuguese and Czech.
  // If other languages need to be supported, this function
  // may need to be enhanced.  
  //
  // In many situations, "to lower" requires more context than a single
  // unicode code point.  If those cases need to be handled correctly,
  // then this function will need to be discarded.
  //
  // The reason this function exists is that there is not a robust
  // C library function that does "to lower" on wchar_t strings
  // that works on Microsoft's, Apple's, Google's or Gnu's
  // compilers.  There are solutions, but many depend on other
  // app state variables that define an app/machine locale.
  // This means the result is not "predictably consistent".
  if ( c < 'A' )
    return c;

  if ( c <= 'Z' )
    return c + 0x0020; // A to a, .... Z to z
 
  if ( c < 0x00C0 )
    return c;
  
 if ( c <= 0x00DE )
  {
    if ( 0x00D7 == c )
      return c; // multiplication sign
    return c + 0x0020;
  }
  
  if ( c < 0x0100 )
    return c;

  if ( c <= 0x0137 )
  {
    // add 1 if c is even
    c |= 0x0001;
    return c;
  }
  
  if ( c < 0x0139 )
    return c;  
  
  if ( c < 0x0148 )
  {
    if ( 0 != (c % 2) )
      c++;
    return c;
  }

  if ( c < 0x014A )
    return c;  

  if ( c < 0x0177 )
  {
    // add 1 if c is odd
    c |= 0x0001;
    return c;
  }

  if ( c < 0x0179 )
    return c;  

  if ( c < 0x017E )
  {
    if ( 0 != (c % 2) )
      c++;
    return c;
  }

  if ( c < ON_UNICODE_LATIN_CAPITAL_LETTER_SHARP_S )
  {
    // NOTE:
    //  This skips some "obvious" to lower conversions, but none 
    //  of these conversions are needed for common unit 
    //  names in English, Spanish, French, German, Portuguese
    //  or Czech.
    return c;
  }

  switch(c)
  {
  case ON_UNICODE_GREEK_CAPITAL_LETTER_TAU: // symbol for angle "turns"
    c = ON_UNICODE_GREEK_SMALL_LETTER_TAU;
    break;

  case ON_UNICODE_LATIN_CAPITAL_LETTER_SHARP_S:
    c = ON_UNICODE_LATIN_SMALL_LETTER_SHARP_S;
    break;
  }

  return c;
}

static ON__UINT32 ON_ToLatinAtoZ( ON__UINT32 c )
{
  // This is a specialized and fast version that converts selected 
  // unicode code points whose glyph is a latin letter A to Z with a 
  // diacritical mark to the corresponding latin A to Z letter.  
  // It also converts sharp s (eszett) to latin letter S and 
  // greek tau to to latin letter T.
  //
  // This code is designed to be used efficiently parse common unit
  // names in English, Spanish, French, German, Portuguese and Czech.
  // If other languages need to be supported, this function will need
  // to be enhanced, redone, or removed.  The unit names being parsed
  // by this code are often input on devices, like English language 
  // keyboards, where it is not convenient for the user to type a 
  // letter or symbol in the language being used.
  //
  // Discarding diacritical marks is a risky approach.  Specifically,
  // this function cannot be used in any context where different 
  // relevant words will be mapped to the same "A to Z" version.

  if ( c < 0x00C0 )
    return c;

  if ( c < 0x0100 )
  {
    if ( c >= 0x00C0 && c <= 0x00C5 )
      c = 'A'; // capital letter A with grave, acute, circumflex, tilde, diaeresis, ring above,
    else if ( c >= 0x00C8 && c <= 0x00CB )
      c = 'E'; // capital letter E with grave, acute, circumflex, diaeresis,
    else if ( c >= 0x00CC && c <= 0x00CF )
      c = 'I'; // capital letter I with grave, acute, circumflex, diaeresis,
    else if ( c >= 0x00D2 && c <= 0x00D6 )
      c = 'O'; // capital letter O with grave, acute, circumflex, tilde, diaeresis,
    else if ( c >= 0x00D9 && c <= 0x00DC )
      c = 'U'; // capital letter U with grave, acute, circumflex, diaeresis,
    else if ( c >= 0x00E0 && c <= 0x00E5 )
      c = 'a'; // small letter a with grave, acute, circumflex, tilde, diaeresis, ring above,
    else if ( c == 00E7 )
      c = 'c'; // small letter c with dedilla
    else if ( c >= 0x00E8 && c <= 0x00EB )
      c = 'e'; // small letter e with grave, acute, circumflex, tilde, diaeresis, ring above,
    else if ( c >= 0x00EC && c <= 0x00EF )
      c = 'i'; // small letter i with grave, acute, circumflex, tilde, diaeresis, ring above,
    else if ( c == 0x00F1 )
      c = 'n'; // small letter n with tilde
    else if ( c >= 0x00F2 && c <= 0x00F6 )
      c = 'o'; // small letter o with grave, acute, circumflex, tilde, diaeresis,
    else if ( c == 0x00F8 )
      c = 'o'; // small letter o with stroke
    else if ( c >= 0x00F9 && c <= 0x00FC )
      c = 'u'; // small letter u with grave, acute, circumflex, tilde, diaeresis,
    else if ( c == 0x00FD )
      c = 'y'; // small letter y with acute
    else if ( c == 0x00FF )
      c = 'y'; // small letter y with diaeresis
    else
    {
      switch (c)
      {
      case 0x00D0: // capital letter Eth
        c = 'D';
        break;
      case 0x00D1: // capital letter N with tilde
        c = 'N';
        break;
      case 0x00D8: // capital letter O with stroke
        c = 'O';
        break;
      case ON_UNICODE_LATIN_SMALL_LETTER_SHARP_S: // small sharp s (German eszet)
        c = 's';
        break;
      case 0x00C7: // capital letter C with cedilla
        c = 'C';
        break;
      case 0x00DD: // capital letter Y with acute
        c = 'Y';
        break;
      case 0x00E7: // small letter c with cedilla
        c = 'c';
        break;
      case 0x00F0: // small letter Eth
        c = 'd';
        break;
      }
    }
  }
  else if ( c < 0x0200 )
  {
    if ( c >= 0x0100 && c <= 0x0105 )
      c = ((0 != (1&c)) ? 'a' : 'A'); // odds -> small A
    else if ( c >= 0x0106 && c <= 0x010D )
      c = ((0 != (1&c)) ? 'c' : 'C'); // odds -> small C
    else if ( c >= 0x010E && c <= 0x0111 )
      c = ((0 != (1&c)) ? 'd' : 'D'); // odds -> small D
    else if ( c >= 0x0112 && c <= 0x011B )
      c = ((0 != (1&c)) ? 'e' : 'E'); // odds -> small E
    else if ( c >= 0x011C && c <= 0x0123 )
      c = ((0 != (1&c)) ? 'g' : 'G'); // odds -> small G
    else if ( c >= 0x0124 && c <= 0x0127 )
      c = ((0 != (1&c)) ? 'h' : 'H'); // odds -> small H
    else if ( c >= 0x0128 && c <= 0x0131 )
      c = ((0 != (1&c)) ? 'i' : 'I'); // odds -> small I
    else if ( c >= 0x0134 && c <= 0x0135 )
      c = ((0 != (1&c)) ? 'j' : 'J'); // odds -> small J
    else if ( c >= 0x0136 && c <= 0x0137 )
      c = ((0 != (1&c)) ? 'k' : 'K'); // odds -> small K
    else if ( c == 0x0138 )
      c = 'k'; // small kra
    else if ( c >= 0x0139 && c <= 0x0142 )
      c = ((0 != (1&c)) ? 'L' : 'l'); // odds -> capital L
    else if ( c >= 0x0143 && c <= 0x0148 )
      c = ((0 != (1&c)) ? 'N' : 'n'); // odds -> capital N
    else if ( c == 0x0149 )
      c = 'n'; //small n preceded by apostrophe
    else if ( c >= 0x014C && c <= 0x0151 )
      c = ((0 != (1&c)) ? 'o' : 'O'); // odds -> small O
    else if ( c >= 0x0154 && c <= 0x0159 )
      c = ((0 != (1&c)) ? 'r' : 'R'); // odds -> small R
    else if ( c >= 0x015A && c <= 0x0161 )
      c = ((0 != (1&c)) ? 's' : 'S'); // odds -> small S
    else if ( c >= 0x0162 && c <= 0x0167 )
      c = ((0 != (1&c)) ? 't' : 'T'); // odds -> small t
    else if ( c >= 0x0168 && c <= 0x0173 )
      c = ((0 != (1&c)) ? 'u' : 'U'); // odds -> small u
    else if ( c >= 0x0174 && c <= 0x0175 )
      c = ((0 != (1&c)) ? 'w' : 'W'); // odds -> small w
    else if ( c >= 0x0176 && c <= 0x0178 )
      c = ((0 != (1&c)) ? 'y' : 'Y'); // odds -> small y
    else if ( c >= 0x0179 && c <= 0x017E )
      c = ((0 != (1&c)) ? 'z' : 'Z'); // odds -> capital Z
  }
  else
  {
    switch (c)
    {
    case ON_UNICODE_GREEK_CAPITAL_LETTER_TAU: // (angle turn units)
      c = 'T';
      break;
    case ON_UNICODE_GREEK_SMALL_LETTER_TAU: // (angle turn units)
      c = 't';
      break;
    case ON_UNICODE_LATIN_CAPITAL_LETTER_SHARP_S: // (German eszett)
      c = 'S'; 
    }
  }

  return c;
}

/*
Description:
  This function is designed to be used to map common unit names
  and abbreviations in Czech, English, French, German, Spanish and
  Portuguese to a lower case latin name that has unicode code points
  'a' to 'z' that can be used in code that parses input streams 
  that specify angles, lengths or point coordinates.

Parameters:
  name - [in]
    String to test to see if it begins with a common 
    unit name or abbreviation in Czech, English, French,
    German, Italian, Portuguese or Spanish.
  utf32_small_simple_name - [out]
    A buffer where a null terminated UTF-32 encoded
    simplified small letter version of the input 
    unit name is returned.
  utf32_small_simple_name_capacity - [in]
    Number of elements that can be used in utf32_small_simple_name[]

Returns:
   0: name was not a unit recognized by this function.
  >0: number of elements of name[] that were parsed as a 
      unit name or abbreviation.

Remarks:
  This code is used to quickly parse optional embedded unit
  names, abbreviations in input streams that specify angles,
  lengths, points in cartesian coordinates, and points in
  polar coordinates.  
  
  The unit systems in the strings may be different from the
  language the applications user interface is using or the unit
  names may be entered on a device, like and english language
  keyboard, that does not provide easy access to latin letters
  with diacritical marks.
  
  If it becomes necessary to correctly handle languages like 
  Russian, Greek, Arabic, Hebrew, Asian languages or anything
  else that does not use latin-esque letters with diacritical
  marks, then this code will be useless and must be discarded.
*/
static
unsigned int ON_GetSmallSimpleUnitsName(
  const wchar_t* name,
  ON__UINT32* utf32_small_simple_name,
  size_t utf32_small_simple_name_capacity
  )
{
  ON_UnicodeErrorParameters e = {0};
  int decode_count;
  ON__UINT32 c, lower_c, simple_c;

  if ( 0 == utf32_small_simple_name || utf32_small_simple_name_capacity <= 0 )
  {
    // failure
    return 0;
  }

  if ( utf32_small_simple_name_capacity > 1 )
  {
    // check for common single glyph symbols that are used
    // when specify length and angle units
    switch(name[0])
    {
    case ON_UNICODE_QUOTATION_MARK:         // quote (inches, arc seconds)
    case ON_UNICODE_APOSTROPHE:             // apostrophe (feet, arc minutes)
    case ON_UNICODE_DEGREE_SYMBOL:          // degree symbol (arc degrees)
    case ON_UNICODE_GREEK_SMALL_LETTER_TAU: // small tau (turns)
      utf32_small_simple_name[0] = (ON__UINT32)(name[0]);
      utf32_small_simple_name[1] = 0;
      return 1;  
    case ON_UNICODE_GREEK_CAPITAL_LETTER_TAU: // capital tau (turns)
      // This is done so strings that have passed through 
      // a "toupper" converter will parse correctly.
      utf32_small_simple_name[0] = (ON__UINT32)ON_UNICODE_GREEK_SMALL_LETTER_TAU;
      utf32_small_simple_name[1] = 0;
      return 1;  
    case ON_UNICODE_MASCULINE_ORDINAL_INDICATOR: 
      // The unicode masculine ordinal indicator (Spanish)
      // is often mistakenly used as a degrees symbol.
      utf32_small_simple_name[0] = ON_UNICODE_DEGREE_SYMBOL;
      utf32_small_simple_name[1] = 0;
      return 1;  
    }
  }

  bool bLeadingUnderbar = false;

  utf32_small_simple_name[0] = 0;

  // return quickly when beginning code point cannot possibly
  // be a unit.

  if ( name[0] >= 0 && name[0] < 'A' )
  {
    return 0;
  }

  if ( name[0] > 'Z' && name[0] < 'a' )
  {
    // leading underbar is allowed
    if ( ON_UNICODE_LOW_LINE != name[0] )
      return 0;
    if ( name[1] >= 0 && name[1] < 'A' )
      return 0;
    if ( name[1] > 'Z' && name[1] < 'a' )
      return 0;
    if ( name[1] > 'z' && name[1] < 0x80 )
      return 0;
    bLeadingUnderbar = true;
  }

  if ( name[0] > 'z' && name[0] < 0x80 )
  {
    return 0;
  }

  size_t count = 0;  
  int name_index = 0;
  while ( count < utf32_small_simple_name_capacity && 0 != name[name_index] )
  {
    e.m_error_status = 0;
    c = 0xFFFFFFFF;

    if ( name[name_index] <= 127 && name[name_index] >= 0 )
    {
      // The code point value for all UTF-* encodings map 
      // values from 0 to 127 (ASCII) to the same code point
      // value. These values are common and this special case
      // handling speeds up parsing.
      c = (ON__UINT32)(name[name_index]);
      decode_count = 1;
    }
    else
    {
      switch(sizeof(wchar_t))
      {
      case 1: // assume name is UTF-8 encoded
        {
          int name_count = name_index+1;
          while( 0 != name[name_count] && 0 != (name[name_count] & 0x80) && name_count < name_index+6 )
            name_count++;
          decode_count = ON_DecodeUTF8((const char*)(name+name_index),name_count-name_index,&e,&c);
        }
        break;

      case 2: // assume name is UTF-16 encoded
        decode_count = ON_DecodeUTF16((const ON__UINT16*)(name+name_index),2,&e,&c);
        break;

      case 4: // assume name is UTF-32 encoded
        c = (ON__UINT32)(name[name_index]);
        decode_count = 1;
        break;

      default:
        // unsupported wchar_t size
        decode_count = 0;
        break;
      }
    }

    if ( decode_count < 1 || !ON_IsValidUnicodeCodePoint(c) )
    {
      count = 0;
      break;
    }

    lower_c = ON_ToLower(c);
    simple_c = ON_ToLatinAtoZ(lower_c);
    if (    (simple_c <= 0x40)
         || (simple_c >= 0x5B && simple_c <= 0x60)
         || (simple_c >= 0x7B && simple_c <= 0xB4)
         || (simple_c >= 0xB6 && simple_c <= 0xBF)
         || (0xD7 == simple_c)
         || (0xF7 == simple_c)
       )
    {
      // This character terminates parsing unless it is a leading underbar.
      if ( count != 0 || !bLeadingUnderbar || ON_UNICODE_LOW_LINE != simple_c )
        break;
    }

    name_index += decode_count;
    utf32_small_simple_name[count++] = simple_c;
  }

  if ( count >= utf32_small_simple_name_capacity )
    count = 0;

  utf32_small_simple_name[count] = 0;

  return ((count > 0 && name_index > 0) ? name_index : 0);
}

int ON_UnitNameEx::SetSimplifiedName()
{
  const unsigned int capacity = ON_UnitNameEx::m_utf32_name_capacity;
   m_utf32_name[capacity-1] = 0;
  const int name_index = ON_GetSmallSimpleUnitsName(m_name,m_utf32_name,capacity);
  unsigned int count = 0;
  if (    name_index > 0
        && 0 != m_utf32_name[0]
        && 0 == m_utf32_name[capacity-1]
        )
  {
    while ( 0 != m_utf32_name[count] )
      count++;
  }
  if ( count > 0 && count < capacity
       && 0 == m_utf32_name[count]
       && 0 != m_utf32_name[count-1]
     )
  {
    m_utf32_name_count = count;
  }
  else
  {
    m_utf32_name_count = 0;
  }
  for ( count = m_utf32_name_count; count < capacity; count++ )
    m_utf32_name[count] = 0;
  return (count > 0 && name_index > 0) ? name_index : 0;
}

class ON_UnitSystemNameCache
{
public:
  // m_unit_list[] has m_unit_list_count elements sorted
  // by ON_UnitNameEx.m_utf32_name_count (shortest first)
  // and then by ON_UnitNameEx.m_utf32_name
  const ON_UnitNameEx* m_unit_list;
  unsigned int m_unit_list_count;
  ON_2dex m_unit_index[ON_UnitNameEx::m_utf32_name_capacity];
};

static bool GetUnitSystemNameCache(
  unsigned int (*GetUnitDictionary)(size_t,ON_UnitName*,ON_UnitNameEx*,bool),
  bool bIncludeInvalidLocaleIdNames,
  ON_UnitSystemNameCache& cache
  )
{
  unsigned int i;

  const unsigned int utf32_name_capacity = ON_UnitNameEx::m_utf32_name_capacity;
  cache.m_unit_list = 0;
  cache.m_unit_list_count = 0;

  for ( i = 0; i < utf32_name_capacity; i++ )
  {
    cache.m_unit_index[i].i = 0;
    cache.m_unit_index[i].j = 0;
  }

  // make a list
  unsigned int capacity = GetUnitDictionary(0,0,0,bIncludeInvalidLocaleIdNames);
  if ( capacity <= 0 )
    return false;

  // Dale Lear September 16, 2016
  // https://mcneel.myjetbrains.com/youtrack/issue/RH-28754
  // This allocation appears as a leak but it is not.
  // This pointer is allocated once when needed, saved as cache.m_unit_list,
  // and is used for the lifetime of the application.
  ON_UnitNameEx* unit_list = new (std::nothrow) ON_UnitNameEx[capacity];

  if ( nullptr == unit_list )
    return false;
  capacity = GetUnitDictionary(capacity,0,unit_list,bIncludeInvalidLocaleIdNames);
  if ( capacity <= 0 )
  {
    delete[] unit_list;
    return false;
  }

  // Sort the returned list
  ON_qsort(
    unit_list,
    capacity,
    sizeof(unit_list[0]),
    (int (*)(const void*,const void*))ON_UnitNameEx::Compare
    );

  // Cull duplicates and set m_name = 0;
  unit_list[0].m_name = 0;
  unsigned int count = 0;

  for ( i = count+1; i < capacity; i++ )
  {
    unit_list[i].m_name = 0;
    if (    0 == ON_UnitNameEx::Compare_m_utf32_name(unit_list+count,unit_list+i) 
         && unit_list[count].m_locale_id == unit_list[i].m_locale_id
       )
    {
      continue;
    }
    count++;
    if (count < i )
    {
      unit_list[count] = unit_list[i];
    }
  }
  count++;

  // The array length_unit_list[] is sorted so the value of 
  // length_unit_list[].m_utf32_name_count increases.  
  // Use that fact to build an index based on the value of 
  // length_unit_list[].m_utf32_name_count so searches can
  // easily be restricted to the region of length_unit_list[]
  // where a possible match exists.
  for ( i = 0; i < count; i++ )
  {
    cache.m_unit_index[unit_list[i].m_utf32_name_count].i = (int)i;
    while(i+1 < count && unit_list[i].m_utf32_name_count == unit_list[i+1].m_utf32_name_count )
      i++;
    cache.m_unit_index[unit_list[i].m_utf32_name_count].j = (int)(i+1);
  }

  cache.m_unit_list = unit_list;

  if ( 0 != cache.m_unit_list )
    cache.m_unit_list_count = count;

  return (cache.m_unit_list_count > 0);
}

static unsigned char UnitSystemEnumValue(
  const ON_UnitSystemNameCache& cache,
  unsigned int prefered_locale_id,
  const ON_UnitNameEx* usname
  )
{
  prefered_locale_id = MapPreferedLocaleId(prefered_locale_id);

  if ( 0 == usname
       || usname->m_utf32_name_count <= 0
       || usname->m_utf32_name_count >= ON_UnitNameEx::m_utf32_name_capacity
       || 0 == usname->m_utf32_name[0] 
       || 0 != usname->m_utf32_name[ON_UnitNameEx::m_utf32_name_capacity-1] 
     )
  {
    return 0;
  }

  if ( 0 == cache.m_unit_list || cache.m_unit_list_count <= 0 )
  {
    return 0;
  }

  ON_2dex range = cache.m_unit_index[usname->m_utf32_name_count];
  // All m_utf32_name entries in s_length_unit_list[range.i,...,range.j-1]
  // have the same length as usname->m_utf32_name[] and they are sorted by
  // m_utf32_name.  Do a binary search on m_utf32_name after checking
  // that the first character indicates a match may exist.
  if (    range.i < range.j 
       && usname->m_utf32_name[0] >= cache.m_unit_list[range.i].m_utf32_name[0]
       && usname->m_utf32_name[0] <= cache.m_unit_list[range.j-1].m_utf32_name[0]
     )
  {
    // binary search on m_utf32_name[] value
    do
    {
      int k = (range.i+range.j)/2;
      int rc = ON_UnitNameEx::Compare_m_utf32_name(usname,cache.m_unit_list+k);
      if (rc < 0)
        range.j = k;
      else if (rc > 0)
        range.i = k+1;
      else
      {
        // string matches - make sure the locale id is valid
        if ( prefered_locale_id == cache.m_unit_list[k].m_locale_id )
          return cache.m_unit_list[k].m_unit_system;

        unsigned int common_angle_unit_system = cache.m_unit_list[k].m_unit_system;

        int k0 = k;
        while ( k0 > range.i
                && 0 == ON_UnitNameEx::Compare_m_utf32_name(usname,cache.m_unit_list+(k0-1))
              )
        {
          k0--;
          if ( prefered_locale_id == cache.m_unit_list[k0].m_locale_id )
            return cache.m_unit_list[k0].m_unit_system;
          if ( common_angle_unit_system != cache.m_unit_list[k0].m_unit_system )
            common_angle_unit_system = 0;
        }

        int k1 = k+1;
        while ( k1 < range.j
                && 0 == ON_UnitNameEx::Compare_m_utf32_name(usname,cache.m_unit_list+k1)
              )
        {
          if ( prefered_locale_id == cache.m_unit_list[k1].m_locale_id )
            return cache.m_unit_list[k1].m_unit_system;
          if ( common_angle_unit_system != cache.m_unit_list[k1].m_unit_system )
            common_angle_unit_system = 0;
          k1++;
        }

        // All matching strings specify the same unit system so
        // we don't care about locale id.
        if ( common_angle_unit_system != 0 )
        {
          return cache.m_unit_list[k].m_unit_system;
        }
        
        if ( k0+1 == k1 )
        {
          // There is a single entry for this string so
          // we don't care about locale id.
          return cache.m_unit_list[k].m_unit_system;
        }

        // If we get this far, there are 2 or more strings that
        // match usname and none of these exactly match the locale 
        // id.
        for ( k = k0; k < k1; k++ )
        {
          if ( ON_RHINO_LOCALE_ID ==  cache.m_unit_list[k].m_locale_id )
            return cache.m_unit_list[k].m_unit_system; // "universal" string

          if ( ON_INVALID_LOCALE_ID ==  cache.m_unit_list[k].m_locale_id )
            return 0; // this string requires an exact locale id match

          // Check for a language match; i.e., if cache.m_unit_list[] is
          // is for locale en-US and the preferred_locale_id is en-UK,
          // then use the en-US entry.  The "language" part of a locale id
          // is encoded in the low byte of the locale id.
          if ( (0xFF & prefered_locale_id) == (0xFF & cache.m_unit_list[k].m_locale_id) )
          {
            // the language part of the local matched
            return cache.m_unit_list[k].m_unit_system;
          }
        }

        return 0;
      }
    }
    while ( range.i < range.j );
  }

  return 0;
}


///////////////////////////////////////////////////////////////////////////////
//
// Length unit names
//

/*
  length_unit_system - [out]]
    If name is parsed as a length unit system name, then
    *length_unit_system is set to the corresponding length unit system.
    If name is not parsed, then *length_unit_system is set to 
    ON::LengthUnitSystem::None.
*/
unsigned int GetLengthUnitList( 
  size_t length_unit_list_capacity,
  ON_UnitName* length_unit_list, 
  ON_UnitNameEx* length_unit_ex_list,
  bool bIncludeInvalidLocaleIdNames
  )
{
  size_t si_length_units_count = sizeof(si_length_units)/sizeof(si_length_units[0]);
  size_t en_US_customary_length_units_count = sizeof(en_US_customary_length_units)/sizeof(en_US_customary_length_units[0]);

  size_t capacity = si_length_units_count
                  + en_US_customary_length_units_count;

  if (    0 == length_unit_list_capacity
       && 0 == length_unit_list
       && 0 == length_unit_ex_list
     )
  {
    return (unsigned int)capacity;
  }

  if (   (0 == length_unit_list  && 0 == length_unit_ex_list)
       || length_unit_list_capacity < capacity 
      )
  {
    return 0;
  }


  size_t count = 0;
  ON_UnitName unit_name;
  ON_UnitNameEx x;
  const ON_UnitName* input_list;
  size_t input_list_count;

  for ( size_t list_index = 0; list_index < 2; list_index++ )
  {
    switch(list_index)
    {
    case 0:
      input_list = si_length_units;
      input_list_count = si_length_units_count;
      break;
    case 1:
      input_list = en_US_customary_length_units;
      input_list_count = en_US_customary_length_units_count;
      break;
    default:
      input_list = 0;
      input_list_count = 0;
      break;
    }

    for ( size_t i = 0; i < input_list_count; i++ )
    {
      if ( 0 != length_unit_list )
      {
        length_unit_list[count++] = input_list[i];
      }
      else if ( 0 != length_unit_ex_list )
      {
        unit_name = input_list[i];
        x.m_locale_id   = unit_name.m_locale_id;
        x.m_unit_system = unit_name.m_unit_system;
        x.m_name        = unit_name.m_name;
        if ( x.SetSimplifiedName() > 0 
             && 0 != x.m_utf32_name_count > 0
             && 0 != x.m_utf32_name_count < ON_UnitNameEx::m_utf32_name_capacity
             && 0 != x.m_utf32_name[0] 
             && 0 != x.m_utf32_name[x.m_utf32_name_count-1] 
             && 0 == x.m_utf32_name[x.m_utf32_name_count] 
             && 0 == x.m_utf32_name[ON_UnitNameEx::m_utf32_name_capacity-1]
           )
        {
          length_unit_ex_list[count++] = x;
        }
        else
        {
          ON_ERROR("Length unit list conatins invalid element.");
        }
      }
    }
  }

  return (unsigned int)count;
}

unsigned int ON_LengthUnitName::GetLengthUnitNameList( 
  size_t length_unit_list_capacity,
  ON_LengthUnitName* length_unit_list
  )
{
  return GetLengthUnitList(length_unit_list_capacity,(ON_UnitName*)length_unit_list,0,false);
}

int ON_ParseLengthUnitName(
  const wchar_t* str,
  int str_count,
  int prefered_locale_id,
  ON::LengthUnitSystem* length_unit_system
)
{
  ON_ParseSettings parse_settings;
  parse_settings.SetPreferedLocaleId(prefered_locale_id);
  return ON_ParseLengthUnitName(str, str_count, parse_settings, length_unit_system);
}

int ON_ParseLengthUnitName( 
  const wchar_t* str,
  int str_count,
  ON_ParseSettings parse_settings,
  ON::LengthUnitSystem* length_unit_system
  )
{
  unsigned int prefered_locale_id = MapPreferedLocaleId(parse_settings.PreferedLocaleId());

  static ON_UnitSystemNameCache s_length_unit_cache = {0};

  if ( 0 != length_unit_system )
  {
    *length_unit_system = ON::LengthUnitSystem::None;
  }

  ON_UnitNameEx x;
  const unsigned int utf32_name_capacity = ON_UnitNameEx::m_utf32_name_capacity;
  unsigned int count = 0;
  int str_index = 0;
  x.m_locale_id = 0;
  x.m_unit_system = static_cast<unsigned int>(ON::LengthUnitSystem::None);
  x.m_name = str;
  x.m_utf32_name_count = 0;
  x.m_utf32_name[0] = 0;

  int whitespace_count = 0;

  for (;;)
  {
    if ( 0 == str_count || str_count < -1 )
      break;

    if ( nullptr == str )
      break;

    if (parse_settings.ParseLeadingWhiteSpace())
    {
      // skip over leading white space
      while ((-1 == str_count || whitespace_count < str_count) && parse_settings.IsLeadingWhiteSpace(str[str_index+whitespace_count]))
      {
        whitespace_count++;
      }
    }
    else if (parse_settings.ParseWhiteSpaceBetweenValueAndUnitSystem())
    {
      // skip over interior white space (needed to make ON_LengthValue() parsing work correctly
      while ((-1 == str_count || whitespace_count < str_count) && parse_settings.IsInteriorWhiteSpace(str[str_index+whitespace_count]))
      {
        whitespace_count++;
      }
    }
    str += whitespace_count;
    if (-1 != str_count)
      str_count -= whitespace_count;

    if (    str[0] >= 0 
         && str[0] < 'A' 
         && ON_UNICODE_QUOTATION_MARK != str[0] 
         && ON_UNICODE_APOSTROPHE != str[0]
       )
    {
      break;
    }

    if ( 0 == s_length_unit_cache.m_unit_list )
    {
      if ( !GetUnitSystemNameCache(GetLengthUnitList,true,s_length_unit_cache) )
        break;
    }

    if (ON_UNICODE_QUOTATION_MARK == str[0] )
    {
      // double quote = US inches abbreviation
      str_index = 1;
      x.m_name = str;
      x.m_unit_system = static_cast<unsigned int>(ON::LengthUnitSystem::Inches);
      x.m_utf32_name[0] = ON_UNICODE_QUOTATION_MARK;
      x.m_utf32_name[1] = 0;
      x.m_utf32_name_count = 1;
      break;
    }

    if (ON_UNICODE_APOSTROPHE == str[0] )
    {
      // apostrophe = US feet abbreviation
      str_index = 1;
      x.m_name = str;
      x.m_unit_system = static_cast<unsigned int>(ON::LengthUnitSystem::Feet);
      x.m_utf32_name[0] = ON_UNICODE_APOSTROPHE;
      x.m_utf32_name[1] = 0;
      x.m_utf32_name_count = 1;
      break;
    }

    str_index = ON_GetSmallSimpleUnitsName(str,x.m_utf32_name,utf32_name_capacity);
    if ( str_index <= 0 )
    {
      str_index = 0;
      break;
    }

    while (count < utf32_name_capacity && 0 != x.m_utf32_name[count] )
      count++;
    if ( count >= utf32_name_capacity )
    {
      str_index = 0;
      count = 0;
      break;
    }
    x.m_utf32_name_count = count;
    while (count < utf32_name_capacity)
      x.m_utf32_name[count++] = 0;

    x.m_unit_system = UnitSystemEnumValue(
      s_length_unit_cache,
      prefered_locale_id,
      &x);
    if ( static_cast<unsigned int>(ON::LengthUnitSystem::None) == x.m_unit_system )
    {
      str_index = 0;
      count = 0;
    }
    break;
  }

  if ( str_index > 0 && 0 != length_unit_system )
    *length_unit_system = ON::LengthUnitSystemFromUnsigned(x.m_unit_system);

  return (str_index > 0) ? (str_index+whitespace_count) : 0;
}



///////////////////////////////////////////////////////////////////////////////
//
// Angle unit names
//
static unsigned int GetAngleUnitList( 
  size_t angle_unit_list_capacity,
  ON_UnitName* angle_unit_list, 
  ON_UnitNameEx* angle_unit_ex_list,
  bool bIncludeInvalidLocaleIdNames
  )
{
  const size_t angle_radian_units_count = sizeof(angle_radian_units)/sizeof(angle_radian_units[0]);
  const size_t angle_degree_units_count = sizeof(angle_degree_units)/sizeof(angle_degree_units[0]);
  const size_t angle_minute_units_count = sizeof(angle_minute_units)/sizeof(angle_minute_units[0]);
  const size_t angle_second_units_count = sizeof(angle_second_units)/sizeof(angle_second_units[0]);
  const size_t angle_turn_units_count = sizeof(angle_turn_units)/sizeof(angle_turn_units[0]);
  const size_t angle_gradian_units_count = sizeof(angle_gradian_units)/sizeof(angle_gradian_units[0]);
  const size_t angle_no_units_count = sizeof(angle_no_units)/sizeof(angle_no_units[0]);

  const size_t capacity = angle_radian_units_count
                  + angle_degree_units_count
                  + angle_minute_units_count
                  + angle_second_units_count
                  + angle_turn_units_count
                  + angle_gradian_units_count
                  + (bIncludeInvalidLocaleIdNames ? angle_no_units_count : 0)
                  ;

  if ( 0 == angle_unit_list_capacity && 0 == angle_unit_list && 0 == angle_unit_ex_list )
    return (unsigned int)capacity;

  if (    angle_unit_list_capacity < capacity
       || (0 == angle_unit_list && 0 == angle_unit_ex_list)
     )
  {
    return 0;
  }

  if ( 0 != angle_unit_list && 0 != angle_unit_ex_list )
    return 0;

  size_t count = 0;
  ON_UnitName unit_name;
  ON_UnitNameEx x;
  const ON_UnitName* input_list;
  size_t input_list_count;

  for ( size_t list_index = 0; list_index < 7; list_index++ )
  {
    switch(list_index)
    {
    case 0:
      input_list = angle_radian_units;
      input_list_count = angle_radian_units_count;
      break;
    case 1:
      input_list = angle_turn_units;
      input_list_count = angle_turn_units_count;
      break;
    case 2:
      input_list = angle_degree_units;
      input_list_count = angle_degree_units_count;
      break;
    case 3:
      input_list = angle_minute_units;
      input_list_count = angle_minute_units_count;
      break;
    case 4:
      input_list = angle_second_units;
      input_list_count = angle_second_units_count;
      break;
    case 5:
      input_list = angle_gradian_units;
      input_list_count = angle_gradian_units_count;
      break;
    case 6:
      if ( bIncludeInvalidLocaleIdNames )
      {
        input_list = angle_no_units;
        input_list_count = angle_no_units_count;
      }
      else
      {
        input_list = 0;
        input_list_count = 0;
      }
      break;
    default:
      input_list = 0;
      input_list_count = 0;
      break;
    }

    for ( size_t i = 0; i < input_list_count; i++ )
    {
      if ( 0 != angle_unit_list )
      {
        angle_unit_list[count++] = input_list[i];
      }
      else
      {
        unit_name = input_list[i];
        x.m_locale_id = unit_name.m_locale_id;
        x.m_unit_system = unit_name.m_unit_system;
        x.m_name = unit_name.m_name;
        if (    x.SetSimplifiedName() > 0 
             && 0 != x.m_utf32_name_count > 0
             && 0 != x.m_utf32_name_count < ON_UnitNameEx::m_utf32_name_capacity
             && 0 != x.m_utf32_name[0] 
             && 0 != x.m_utf32_name[x.m_utf32_name_count-1] 
             && 0 == x.m_utf32_name[x.m_utf32_name_count] 
             && 0 == x.m_utf32_name[ON_UnitNameEx::m_utf32_name_capacity-1]
           )
        {
          angle_unit_ex_list[count++] = x;
        }
        else
        {
          ON_ERROR("Angle unit list conatins invalid element.");
        }
      }
    }
  }

  return (unsigned int)count;
}

int ON_ParseAngleUnitName(
  const wchar_t* str,
  int str_count,
  int prefered_locale_id,
  ON::AngleUnitSystem* angle_unit_system
)
{
  ON_ParseSettings parse_settings;
  parse_settings.SetPreferedLocaleId(prefered_locale_id);
  parse_settings.SetParseLeadingWhiteSpace(false);
  return ON_ParseAngleUnitName(str, str_count, parse_settings, angle_unit_system);
}

int ON_ParseAngleUnitName( 
  const wchar_t* str,
  int str_count,
  ON_ParseSettings parse_settings,
  ON::AngleUnitSystem* angle_unit_system
  )
{
  static ON_UnitSystemNameCache s_angle_unit_cache = {0};

  if ( 0 != angle_unit_system )
    *angle_unit_system = ON::AngleUnitSystem::None;

  unsigned int prefered_locale_id = MapPreferedLocaleId(parse_settings.PreferedLocaleId());

  ON_UnitNameEx x;
  const unsigned int utf32_name_capacity = ON_UnitNameEx::m_utf32_name_capacity;
  unsigned int count = 0;
  int str_index = 0;
  x.m_locale_id = 0;
  x.m_unit_system = static_cast<unsigned int>(ON::AngleUnitSystem::None);
  x.m_name = str;
  x.m_utf32_name_count = 0;
  x.m_utf32_name[0] = 0;
  
  int whitespace_count = 0;

  for (;;)
  {
    if ( 0 == str_count && str_count < -1 )
      break;

    if ( 0 == str )
      break;

    if (parse_settings.ParseLeadingWhiteSpace())
    {
      // skip over leading white space
      while ((-1 == str_count || whitespace_count < str_count) && parse_settings.IsLeadingWhiteSpace(str[str_index+whitespace_count]))
      {
        whitespace_count++;
      }
    }
    else if (parse_settings.ParseWhiteSpaceBetweenValueAndUnitSystem())
    {
      // skip over interior white space (needed to make ON_AngleValue() parsing work correctly
      while ((-1 == str_count || whitespace_count < str_count) && parse_settings.IsInteriorWhiteSpace(str[str_index+whitespace_count]))
      {
        whitespace_count++;
      }
    }
    str += whitespace_count;
    if (-1 != str_count)
      str_count -= whitespace_count;

    if (    str[0] >= 0 
         && str[0] < 'A' 
         && ON_UNICODE_QUOTATION_MARK != str[0] 
         && ON_UNICODE_APOSTROPHE != str[0]
       )
    {
      break;
    }


    if ( 0 == s_angle_unit_cache.m_unit_list )
    {
      if ( !GetUnitSystemNameCache(GetAngleUnitList,true,s_angle_unit_cache) )
        break;
    }

    if (ON_UNICODE_QUOTATION_MARK == str[0] )
    {
      // double quote = arc seconds
      str_index = 1;
      x.m_name = str;
      x.m_unit_system = static_cast<unsigned int>(ON::AngleUnitSystem::Seconds);
      x.m_utf32_name[0] = ON_UNICODE_QUOTATION_MARK;
      x.m_utf32_name[1] = 0;
      x.m_utf32_name_count = 1;
      break;
    }

    if ( ON_UNICODE_APOSTROPHE == str[0] )
    {
      // apostrophe = arc minutes
      str_index = 1;
      x.m_name = str;
      x.m_unit_system = static_cast<unsigned int>(ON::AngleUnitSystem::Minutes);
      x.m_utf32_name[0] = ON_UNICODE_APOSTROPHE;
      x.m_utf32_name[1] = 0;
      x.m_utf32_name_count = 1;
      break;
    }

    if ( ON_UNICODE_DEGREE_SYMBOL == str[0] )
    {
      // unicode degree symbol = arc degrees
      str_index = 1;
      x.m_name = str;
      x.m_unit_system = static_cast<unsigned int>(ON::AngleUnitSystem::Degrees);
      x.m_utf32_name[0] = ON_UNICODE_DEGREE_SYMBOL;
      x.m_utf32_name[1] = 0;
      x.m_utf32_name_count = 1;
      break;
    }

    if ( ON_UNICODE_MASCULINE_ORDINAL_INDICATOR == str[0] )
    {
      // The unicode masculine ordinal indicator (Spanish)
      // is often mistakenly used as a degrees symbol.
      str_index = 1;
      x.m_name = str;
      x.m_unit_system = static_cast<unsigned int>(ON::AngleUnitSystem::Degrees);
      x.m_utf32_name[0] = ON_UNICODE_DEGREE_SYMBOL; // correct - convert to degree symbol
      x.m_utf32_name[1] = 0;
      x.m_utf32_name_count = 1;
      break;
    }

    if ( ON_UNICODE_GREEK_SMALL_LETTER_TAU == str[0] )
    {
      // unicode greek tau = turns
      str_index = 1;
      x.m_name = str;
      x.m_unit_system = static_cast<unsigned int>(ON::AngleUnitSystem::Turns);
      x.m_utf32_name[0] = ON_UNICODE_GREEK_SMALL_LETTER_TAU;
      x.m_utf32_name[1] = 0;
      x.m_utf32_name_count = 1;
      break;
    }

    if ( ON_UNICODE_GREEK_CAPITAL_LETTER_TAU == str[0] )
    {
      // unicode capital greek tau = turns
      str_index = 1;
      x.m_name = str;
      x.m_unit_system = static_cast<unsigned int>(ON::AngleUnitSystem::Turns);
      x.m_utf32_name[0] = ON_UNICODE_GREEK_SMALL_LETTER_TAU; // correct - convert to lower case
      x.m_utf32_name[1] = 0;
      x.m_utf32_name_count = 1;
      break;
    }

    str_index = ON_GetSmallSimpleUnitsName(str,x.m_utf32_name,utf32_name_capacity);
    if ( str_index <= 0 )
    {
      str_index = 0;
      break;
    }

    while (count < utf32_name_capacity && 0 != x.m_utf32_name[count] )
      count++;
    if ( count >= utf32_name_capacity )
    {
      str_index = 0;
      count = 0;
      break;
    }
    x.m_utf32_name_count = count;
    while (count < utf32_name_capacity)
      x.m_utf32_name[count++] = 0;

    x.m_unit_system = UnitSystemEnumValue(
      s_angle_unit_cache,
      prefered_locale_id,
      &x
      );
    if ( static_cast<unsigned int>(ON::AngleUnitSystem::None) == x.m_unit_system )
    {
      str_index = 0;
      count = 0;
    }
    break;
  }

  if ( str_index > 0 && angle_unit_system )
    *angle_unit_system = ON::AngleUnitSystemFromUnsigned(x.m_unit_system);

  return (str_index > 0) ? (str_index+whitespace_count) : 0;
}

unsigned int ON_AngleUnitName::GetAngleUnitNameList( 
  size_t angle_unit_list_capacity,
  ON_AngleUnitName* angle_unit_list
  )
{
  return GetAngleUnitList(angle_unit_list_capacity,(ON_UnitName*)angle_unit_list,0,false);
}

static const wchar_t* ON_Internal_GetUnitsName(
  unsigned int locale_id,
  const unsigned int unit_system_as_unsigned,
  bool bPlural,
  size_t count,
  const ON_UnitName* names
  )
{
  if (count <= 0 || nullptr == names)
    return nullptr;

  const unsigned int special_id_limit = 2;

  if (locale_id <= special_id_limit && locale_id != ON_RHINO_LOCALE_ID)
  {
    if (0 == locale_id)
      locale_id = ON_Locale::CurrentCulture.WindowsLCID();
    if ( locale_id <= special_id_limit && locale_id != ON_RHINO_LOCALE_ID )
      locale_id = ON_RHINO_LOCALE_ID;
  }
  else if (locale_id > special_id_limit && ON_EN_US_LOCALE_ID != locale_id)
  {
    unsigned int prefered_locale_id = MapPreferedLocaleId(locale_id);
    if (locale_id != prefered_locale_id && prefered_locale_id > special_id_limit)
      locale_id = prefered_locale_id;
  }

  const wchar_t* singular_name = nullptr;
  const wchar_t* plural_name = nullptr;
  for (size_t i = 0; i < count; i++)
  {
    if (locale_id == names[i].m_locale_id && unit_system_as_unsigned == names[i].m_unit_system )
    {
      const wchar_t* name = names[i].m_name;
      if (nullptr != name && 0 != name[0])
      {
        if (nullptr == singular_name && names[i].m_bIsSingular)
        {
          if (!bPlural)
            return name;
          singular_name = name;
        }
        if (nullptr == singular_name && names[i].m_bIsPlural)
        {
          if (bPlural)
            return name;
          plural_name = name;
        }
      }
    }
  }

  if (nullptr != plural_name)
    return plural_name;
  if (nullptr != singular_name)
    return singular_name;

  if (ON_RHINO_LOCALE_ID == locale_id)
    return nullptr; // nothing left to try
  
  if (locale_id > special_id_limit && ON_EN_US_LOCALE_ID != locale_id)
  {
    // try English - US
    return ON_Internal_GetUnitsName(ON_EN_US_LOCALE_ID, unit_system_as_unsigned, bPlural, count, names);
  }

  // Try "rhino" locale
  return ON_Internal_GetUnitsName(ON_RHINO_LOCALE_ID, unit_system_as_unsigned, bPlural, count, names);
}


ON_LengthUnitName ON_LengthUnitName::Create(
  unsigned int locale_id,
  ON::LengthUnitSystem length_unit_system,
  bool bPlural
)
{
  if (0 == locale_id)
    locale_id = ON_Locale::CurrentCulture.WindowsLCID();

  size_t count = 0;
  const ON_UnitName* names = nullptr;

  length_unit_system = ON::LengthUnitSystemFromUnsigned(static_cast<unsigned int>(length_unit_system));

  switch (length_unit_system)
  {
  case ON::LengthUnitSystem::None:
    break;

  case ON::LengthUnitSystem::Angstroms:
  case ON::LengthUnitSystem::Nanometers:
  case ON::LengthUnitSystem::Microns:
  case ON::LengthUnitSystem::Millimeters:
  case ON::LengthUnitSystem::Centimeters:
  case ON::LengthUnitSystem::Decimeters:
  case ON::LengthUnitSystem::Meters:
  case ON::LengthUnitSystem::Dekameters:
  case ON::LengthUnitSystem::Hectometers:
  case ON::LengthUnitSystem::Kilometers:
  case ON::LengthUnitSystem::Megameters:
  case ON::LengthUnitSystem::Gigameters:
    names = si_length_units;
    count = sizeof(si_length_units)/sizeof(si_length_units[0]);    
    break;

  case ON::LengthUnitSystem::Microinches:
  case ON::LengthUnitSystem::Mils:
  case ON::LengthUnitSystem::Inches:
  case ON::LengthUnitSystem::Feet:
  case ON::LengthUnitSystem::Yards:
  case ON::LengthUnitSystem::Miles:
    names = en_US_customary_length_units;
    count = sizeof(en_US_customary_length_units)/sizeof(en_US_customary_length_units[0]);    
    break;
    
  case ON::LengthUnitSystem::PrinterPoints:
    break;
  case ON::LengthUnitSystem::PrinterPicas:
    break;
  case ON::LengthUnitSystem::NauticalMiles:
    break;
  case ON::LengthUnitSystem::AstronomicalUnits:
    break;
  case ON::LengthUnitSystem::LightYears:
    break;
  case ON::LengthUnitSystem::Parsecs:
    break;
  case ON::LengthUnitSystem::CustomUnits:
    break;
  case ON::LengthUnitSystem::Unset:
    break;
  default:
    ON_ERROR("Invalid length_unit_system parameter.");
    length_unit_system = ON::LengthUnitSystem::Unset;
    break;
  }


  ON_LengthUnitName length_unit_name;
  length_unit_name.m_locale_id = locale_id;
  length_unit_name.m_length_unit_system = length_unit_system;
  length_unit_name.m_bNameIsSingular = bPlural ? false : true;
  length_unit_name.m_bNameIsPlural = bPlural ? true : false;

  // attempt to get localized name
  length_unit_name.m_name = ON_Internal_GetUnitsName(
    locale_id,
    static_cast<unsigned int>(length_unit_system),
    bPlural,
    count,
    names
  );

  if (nullptr == length_unit_name.m_name || 0 == length_unit_name.m_name[0])
  {
    switch (length_unit_system)
    {
    case ON::LengthUnitSystem::None:
      break;

    case ON::LengthUnitSystem::Angstroms:
      length_unit_name.m_name = bPlural ? L"angstroms" : L"angstrom";
      break;
    case ON::LengthUnitSystem::Nanometers:
      length_unit_name.m_name = bPlural ? L"nanometers" : L"nanometer";
      break;
    case ON::LengthUnitSystem::Microns:
      length_unit_name.m_name = bPlural ? L"microns" : L"micron";
      break;
    case ON::LengthUnitSystem::Millimeters:
      length_unit_name.m_name = bPlural ? L"millimeters" : L"millimeter";
      break;
    case ON::LengthUnitSystem::Centimeters:
      length_unit_name.m_name = bPlural ? L"centimeters" : L"centimeter";
      break;
    case ON::LengthUnitSystem::Decimeters:
      length_unit_name.m_name = bPlural ? L"decimeters" : L"decimeter";
      break;
    case ON::LengthUnitSystem::Meters:
      length_unit_name.m_name = bPlural ? L"meters" : L"meter";
      break;
    case ON::LengthUnitSystem::Dekameters:
      length_unit_name.m_name = bPlural ? L"dekameters" : L"dekameter";
      break;
    case ON::LengthUnitSystem::Hectometers:
      length_unit_name.m_name = bPlural ? L"hectometers" : L"hectometer";
      break;
    case ON::LengthUnitSystem::Kilometers:
      length_unit_name.m_name = bPlural ? L"kilometers" : L"kilometer";
      break;
    case ON::LengthUnitSystem::Megameters:
      length_unit_name.m_name = bPlural ? L"megameters" : L"megameter";
      break;
    case ON::LengthUnitSystem::Gigameters:
      length_unit_name.m_name = bPlural ? L"gigameters" : L"gigameter";
      break;
    case ON::LengthUnitSystem::Microinches:
      length_unit_name.m_name = bPlural ? L"microinches" : L"microinche";
      break;
    case ON::LengthUnitSystem::Mils:
      length_unit_name.m_name = bPlural ? L"mils" : L"mil";
      break;
    case ON::LengthUnitSystem::Inches:
      length_unit_name.m_name = bPlural ? L"inches" : L"inch";
      break;
    case ON::LengthUnitSystem::Feet:
      length_unit_name.m_name = bPlural ? L"feet" : L"foot";
      break;
    case ON::LengthUnitSystem::Yards:
      length_unit_name.m_name = bPlural ? L"yards" : L"yard";
      break;
    case ON::LengthUnitSystem::Miles:
      length_unit_name.m_name = bPlural ? L"miles" : L"mile";
      break;
    case ON::LengthUnitSystem::PrinterPoints:
      length_unit_name.m_name = bPlural ? L"points" : L"point";
      break;
    case ON::LengthUnitSystem::PrinterPicas:
      length_unit_name.m_name = bPlural ? L"picas" : L"pica";
      break;
    case ON::LengthUnitSystem::NauticalMiles:
      length_unit_name.m_name = bPlural ? L"nauticalmiles" : L"nauticalmile"; // no spaces!
      break;
    case ON::LengthUnitSystem::AstronomicalUnits:
      length_unit_name.m_name = bPlural ? L"AUs" : L"AU"; // no spaces!
      break;
    case ON::LengthUnitSystem::LightYears:
      length_unit_name.m_name = bPlural ? L"lightyears" : L"lightyear"; // no spaces!
      break;
    case ON::LengthUnitSystem::Parsecs:
      length_unit_name.m_name = bPlural ? L"parsecs" : L"parsec";
      break;
    case ON::LengthUnitSystem::CustomUnits:
      break;
    case ON::LengthUnitSystem::Unset:
      break;
    }
  }



  return length_unit_name;
}

int ON_LengthUnitName::Internal_Compare(
  unsigned int order_selector,
  const ON_LengthUnitName& a,
  const ON_LengthUnitName& b
)
{
  if (1 == order_selector)
  {
    // locale id is first
    if (a.m_locale_id < b.m_locale_id)
      return -1;
    if (a.m_locale_id > b.m_locale_id)
      return 1;
  }

  unsigned int i = static_cast<unsigned int>(a.m_length_unit_system);
  unsigned int j = static_cast<unsigned int>(b.m_length_unit_system);
    if (i < j)
    return -1;
  if (i > j)
    return 1;

  if (1 != order_selector)
  {
    // locale id is second
    if (a.m_locale_id < b.m_locale_id)
      return -1;
    if (a.m_locale_id > b.m_locale_id)
      return 1;
  }

  i =  ON_wString::CompareOrdinal(a.m_name,b.m_name,false);
  if (i != 0)
  {
    // ignore case order is preferred
    j = ON_wString::CompareOrdinal(a.m_name, b.m_name, true);
    return (0 != j) ? j : i;
  }

  i = a.m_bNameIsSingular ? 1 : 0;
  j = b.m_bNameIsSingular ? 1 : 0;
  if (i < j)
    return -1;
  if (i > j)
    return 1;

  i = a.m_bNameIsPlural ? 1 : 0;
  j = b.m_bNameIsPlural ? 1 : 0;
  if (i < j)
    return -1;
  if (i > j)
    return 1;

  return 0;
}

int ON_LengthUnitName::CompareUnitSystemLocaleIdName(
  const ON_LengthUnitName& a,
  const ON_LengthUnitName& b
)
{
  return Internal_Compare(0, a, b);
}

int ON_LengthUnitName::CompareLocaleIdUnitSystemName(
  const ON_LengthUnitName& a,
  const ON_LengthUnitName& b
)
{
  return Internal_Compare(1, a, b);
}


unsigned int ON_LengthUnitName::LocaleId() const
{
  return m_locale_id;
}

ON::LengthUnitSystem ON_LengthUnitName::LengthUnit() const
{
  return m_length_unit_system;
}

bool ON_LengthUnitName::LengthUnitAndNameAreSet() const
{
  return LengthUnitIsSet() && LengthUnitNameIsNotEmpty();
}

bool ON_LengthUnitName::LengthUnitIsSet() const
{
  return (ON::LengthUnitSystem::Unset != m_length_unit_system && ON::LengthUnitSystem::None != m_length_unit_system);
}

bool ON_LengthUnitName::LengthUnitIsSetOrNone() const
{
  return (ON::LengthUnitSystem::Unset != m_length_unit_system);
}

const wchar_t* ON_LengthUnitName::LengthUnitName() const
{
  return (nullptr == m_name) ? static_cast<const wchar_t*>(ON_wString::EmptyString) : m_name;
}

bool ON_LengthUnitName::LengthUnitNameIsSingular() const
{
  return m_bNameIsSingular;
}

bool ON_LengthUnitName::LengthUnitNameIsPlural() const
{
  return m_bNameIsPlural;
}

bool ON_LengthUnitName::LengthUnitNameIsEmpty() const
{
  return (nullptr == m_name || 0 == m_name[0]);
}

bool ON_LengthUnitName::LengthUnitNameIsNotEmpty() const
{
  return (nullptr != m_name && 0 != m_name[0]);
}

bool operator==(
  const ON_LengthUnitName& a,
  const ON_LengthUnitName& b
  )
{
  return (0 == ON_LengthUnitName::CompareUnitSystemLocaleIdName(a, b));
}

bool operator!=(
  const ON_LengthUnitName& a,
  const ON_LengthUnitName& b
  )
{
  return (0 != ON_LengthUnitName::CompareUnitSystemLocaleIdName(a, b));
}

ON_AngleUnitName ON_AngleUnitName::Create(
  unsigned int locale_id,
  ON::AngleUnitSystem angle_unit_system,
  bool bPlural
)
{
  angle_unit_system = ON::AngleUnitSystemFromUnsigned(static_cast<unsigned int>(angle_unit_system));
  
  size_t count = 0;
  const ON_UnitName* names = nullptr;

  switch (angle_unit_system)
  {
  case ON::AngleUnitSystem::None:
    break;
  case ON::AngleUnitSystem::Turns:
    names = angle_turn_units;
    count = sizeof(angle_turn_units)/sizeof(angle_turn_units[0]);
    break;
  case ON::AngleUnitSystem::Radians:
    names = angle_radian_units;
    count = sizeof(angle_radian_units)/sizeof(angle_radian_units[0]);
    break;
  case ON::AngleUnitSystem::Degrees:
    names = angle_degree_units;
    count = sizeof(angle_degree_units)/sizeof(angle_degree_units[0]);
    break;
  case ON::AngleUnitSystem::Minutes:
    names = angle_minute_units;
    count = sizeof(angle_minute_units)/sizeof(angle_minute_units[0]);
    break;
  case ON::AngleUnitSystem::Seconds:
    names = angle_second_units;
    count = sizeof(angle_second_units)/sizeof(angle_second_units[0]);
    break;
  case ON::AngleUnitSystem::Gradians:
    names = angle_gradian_units;
    count = sizeof(angle_gradian_units)/sizeof(angle_gradian_units[0]);
    break;
  case ON::AngleUnitSystem::Unset:
    break;
  default:
    ON_ERROR("Invalid angle_unit_system parameter.");
    angle_unit_system = ON::AngleUnitSystem::Unset;
    break;
  }

  ON_AngleUnitName angle_unit_name;
  angle_unit_name.m_locale_id = locale_id;
  angle_unit_name.m_angle_unit_system = angle_unit_system;
  angle_unit_name.m_bNameIsSingular = bPlural ? false : true;
  angle_unit_name.m_bNameIsPlural = bPlural ? true : false;

  // attempt to get localized name
  angle_unit_name.m_name = ON_Internal_GetUnitsName(
    locale_id,
    static_cast<unsigned int>(angle_unit_system),
    bPlural,
    count,
    names
  );

  if (nullptr == angle_unit_name.m_name || 0 == angle_unit_name.m_name[0])
  {
    switch (angle_unit_system)
    {
    case ON::AngleUnitSystem::None:
      break;
    case ON::AngleUnitSystem::Turns:
      angle_unit_name.m_name = bPlural ? L"turns" : L"turn";
      break;
    case ON::AngleUnitSystem::Radians:
      angle_unit_name.m_name = bPlural ? L"radians" : L"radian";
      break;
    case ON::AngleUnitSystem::Degrees:
      angle_unit_name.m_name = bPlural ? L"degrees" : L"degree";
      break;
    case ON::AngleUnitSystem::Minutes:
      angle_unit_name.m_name = bPlural ? L"minutes" : L"minute";
      break;
    case ON::AngleUnitSystem::Seconds:
      angle_unit_name.m_name = bPlural ? L"seconds" : L"second";
      break;
    case ON::AngleUnitSystem::Gradians:
      angle_unit_name.m_name = bPlural ? L"gradians" : L"gradian";
      break;
    case ON::AngleUnitSystem::Unset:
      break;
    }
  }
   
  return angle_unit_name;
}

int ON_AngleUnitName::Internal_Compare(
  unsigned int order_selector,
  const ON_AngleUnitName& a,
  const ON_AngleUnitName& b
)
{
  if (1 == order_selector)
  {
    // locale id is first
    if (a.m_locale_id < b.m_locale_id)
      return -1;
    if (a.m_locale_id > b.m_locale_id)
      return 1;
  }

  unsigned int i = static_cast<unsigned int>(a.m_angle_unit_system);
  unsigned int j = static_cast<unsigned int>(b.m_angle_unit_system);
  if (i < j)
    return -1;
  if (i > j)
    return 1;

  if (1 != order_selector)
  {
    // localed id is second
    if (a.m_locale_id < b.m_locale_id)
      return -1;
    if (a.m_locale_id > b.m_locale_id)
      return 1;
  }

  i =  ON_wString::CompareOrdinal(a.m_name,b.m_name,false);
  if (i != 0)
  {
    // ignore case order is preferred
    j = ON_wString::CompareOrdinal(a.m_name, b.m_name, true);
    return (0 != j) ? j : i;
  }

  i = a.m_bNameIsSingular ? 1 : 0;
  j = b.m_bNameIsSingular ? 1 : 0;
  if (i < j)
    return -1;
  if (i > j)
    return 1;

  i = a.m_bNameIsPlural ? 1 : 0;
  j = b.m_bNameIsPlural ? 1 : 0;
  if (i < j)
    return -1;
  if (i > j)
    return 1;

  return 0;
}

int ON_AngleUnitName::CompareUnitSystemLocaleIdName(
  const ON_AngleUnitName& a,
  const ON_AngleUnitName& b
)
{
  return Internal_Compare(0, a, b);
}

int ON_AngleUnitName::CompareLocaleIdUnitSystemName(
  const ON_AngleUnitName& a,
  const ON_AngleUnitName& b
)
{
  return Internal_Compare(1, a, b);
}


unsigned int ON_AngleUnitName::LocaleId() const
{
  return m_locale_id;
}

ON::AngleUnitSystem ON_AngleUnitName::AngleUnit() const
{
  return m_angle_unit_system;
}

bool ON_AngleUnitName::AngleUnitAndNameAreSet() const
{
  return AngleUnitIsSet() && AngleUnitNameIsNotEmpty();
}

bool ON_AngleUnitName::AngleUnitIsSet() const
{
  return (ON::AngleUnitSystem::Unset != m_angle_unit_system && ON::AngleUnitSystem::None != m_angle_unit_system);
}

bool ON_AngleUnitName::AngleUnitIsSetOrNone() const
{
  return (ON::AngleUnitSystem::Unset != m_angle_unit_system);
}

const wchar_t* ON_AngleUnitName::AngleUnitName() const
{
  return (nullptr == m_name) ? static_cast<const wchar_t*>(ON_wString::EmptyString) : m_name;
}

bool ON_AngleUnitName::AngleUnitNameIsSingular() const
{
  return m_bNameIsSingular;
}

bool ON_AngleUnitName::AngleUnitNameIsPlural() const
{
  return m_bNameIsPlural;
}

bool ON_AngleUnitName::AngleUnitNameIsEmpty() const
{
  return (nullptr == m_name || 0 == m_name[0]);
}

bool ON_AngleUnitName::AngleUnitNameIsNotEmpty() const
{
  return (nullptr != m_name && 0 != m_name[0]);
}

bool operator==(
  const ON_AngleUnitName& a,
  const ON_AngleUnitName& b
  )
{
  return (0 == ON_AngleUnitName::CompareUnitSystemLocaleIdName(a, b));
}

bool operator!=(
  const ON_AngleUnitName& a,
  const ON_AngleUnitName& b
  )
{
  return (0 != ON_AngleUnitName::CompareUnitSystemLocaleIdName(a, b));
}
