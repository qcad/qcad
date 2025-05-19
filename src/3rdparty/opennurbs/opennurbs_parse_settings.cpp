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

void ON_ParseSettings::Internal_DefaultCtor()
{
  size_t i;
  for ( i = 0; i < sizeof(m_true_default_bits)/sizeof(m_true_default_bits[0]); i++ )
    m_true_default_bits[i] = 0;
  for ( i = 0; i < sizeof(m_false_default_bits)/sizeof(m_false_default_bits[0]); i++ )
    m_false_default_bits[i] = 0;
}

ON_ParseSettings::ON_ParseSettings()
{
  Internal_DefaultCtor();
}

ON_ParseSettings::ON_ParseSettings(
  const class ON_UnitSystem& context_length_unit_system,
  ON::AngleUnitSystem context_angle_unit_system,
  unsigned int context_locale_id
)
{
  Internal_DefaultCtor();
  SetContextLengthUnitSystem(context_length_unit_system.UnitSystem());
  SetContextAngleUnitSystem(context_angle_unit_system);
  SetContextLocaleId(context_locale_id);
}

ON_ParseSettings::ON_ParseSettings(
  ON::LengthUnitSystem context_length_unit_system,
  ON::AngleUnitSystem context_angle_unit_system,
  unsigned int context_locale_id
)
{
  Internal_DefaultCtor();
  SetContextLengthUnitSystem(context_length_unit_system);
  SetContextAngleUnitSystem(context_angle_unit_system);
  SetContextLocaleId(context_locale_id);
}

void ON_ParseSettings::SetAllToFalse()
{
  size_t i;
  *this = ON_ParseSettings::DefaultSettings;
  for ( i = 0; i < sizeof(m_true_default_bits)/sizeof(m_true_default_bits[0]); i++ )
    m_true_default_bits[i] = 0xFFFFFFFF;
}

const int ON_ParseSettings::Compare(
  const ON_ParseSettings* a,
  const ON_ParseSettings* b
  )
{
  size_t i;

  if ( 0 == a || 0 == b )
  {
    if ( 0 != b )
      return -1;
    if ( 0 != a )
      return 1;
    return 0;
  }
  
  for ( i = 0; i < sizeof(a->m_true_default_bits)/sizeof(a->m_true_default_bits[0]); i++ )
  {
    if ( a->m_true_default_bits[i] < b->m_true_default_bits[i] )
      return -1;
    if ( b->m_true_default_bits[i] < a->m_true_default_bits[i] )
      return 1;
  }
  
  for ( i = 0; i < sizeof(a->m_false_default_bits)/sizeof(a->m_false_default_bits[0]); i++ )
  {
    if ( a->m_false_default_bits[i] < b->m_false_default_bits[i] )
      return -1;
    if ( b->m_false_default_bits[i] < a->m_false_default_bits[i] )
      return 1;
  }

  if ( a->m_context_locale_id < b->m_context_locale_id )
    return -1;
  if ( b->m_context_locale_id < a->m_context_locale_id )
    return 1;

  if ( a->m_context_length_unit_system < b->m_context_length_unit_system )
    return -1;
  if ( b->m_context_length_unit_system < a->m_context_length_unit_system )
    return 1;

  if ( a->m_context_angle_unit_system < b->m_context_angle_unit_system )
    return -1;
  if ( b->m_context_angle_unit_system < a->m_context_angle_unit_system )
    return 1;

  return 0;
}

void ON_ParseSettings::SetAllExpressionSettingsToFalse()
{
  // parsing of things that have multiple numbers like
  // feet and inches, arc degrees minutes seconds,
  // integer-fraction and rational numbers uses
  // this helper to prevent "fancy" stuff when parsing
  // the "additional" numbers.
  SetParseExplicitFormulaExpression(false);
  SetParseArithmeticExpression(false);
  SetParseMultiplication(false);
  SetParseDivision(false);  
  SetParseAddition(false);
  SetParseSubtraction(false);
  SetParseMathFunctions(false);
  SetParsePairedParentheses(false);
}

const ON_ParseSettings ON_ParseSettings::DefaultSettings;

static ON_ParseSettings DefaultSettingsInRadiansHelper()
{
  ON_ParseSettings default_settings_in_radians(ON_ParseSettings::DefaultSettings);
  default_settings_in_radians.SetDefaultAngleUnitSystem(ON::AngleUnitSystem::Radians);
  return default_settings_in_radians;
}

const ON_ParseSettings ON_ParseSettings::DefaultSettingsInRadians(DefaultSettingsInRadiansHelper());

static ON_ParseSettings DefaultSettingsInDegreesHelper()
{
  ON_ParseSettings default_settings_in_degrees(ON_ParseSettings::DefaultSettings);
  default_settings_in_degrees.SetDefaultAngleUnitSystem(ON::AngleUnitSystem::Degrees);
  return default_settings_in_degrees;
}

const ON_ParseSettings ON_ParseSettings::DefaultSettingsInDegrees(DefaultSettingsInDegreesHelper());

static ON_ParseSettings FalseSettingsHelper()
{
  ON_ParseSettings false_settings;
  false_settings.SetAllToFalse();
  return false_settings;
}

const ON_ParseSettings ON_ParseSettings::FalseSettings(FalseSettingsHelper());

static ON_ParseSettings IntegerSettingsHelper()
{
  ON_ParseSettings integer_settings(ON_ParseSettings::FalseSettings);
  // do not enable parsing of leading white space here
  integer_settings.SetParseUnaryPlus(true);
  integer_settings.SetParseUnaryMinus(true);
  integer_settings.SetParseSignificandIntegerPart(true);
  return integer_settings;
}

const ON_ParseSettings ON_ParseSettings::IntegerNumberSettings(IntegerSettingsHelper());

static ON_ParseSettings RationalNumberSettingsHelper()
{
  ON_ParseSettings rational_number_settings(ON_ParseSettings::IntegerNumberSettings);
  // do not enable parsing of leading white space here
  rational_number_settings.SetParseRationalNumber(true);
  return rational_number_settings;
}

const ON_ParseSettings ON_ParseSettings::RationalNumberSettings(RationalNumberSettingsHelper());

static ON_ParseSettings DoubleNumberSettingsHelper()
{
  ON_ParseSettings double_number_settings(ON_ParseSettings::IntegerNumberSettings);
  // do not enable parsing of leading white space here
  double_number_settings.SetParseSignificandDecimalPoint(true);
  double_number_settings.SetParseSignificandFractionalPart(true);
  //double_number_settings.SetParseSignificandDigitSeparators(true);
  double_number_settings.SetParseScientificENotation(true);
  return double_number_settings;
}

const ON_ParseSettings ON_ParseSettings::DoubleNumberSettings(DoubleNumberSettingsHelper());

static ON_ParseSettings RealNumberSettingsHelper()
{
  ON_ParseSettings real_number_settings(ON_ParseSettings::DoubleNumberSettings);
  // do not enable parsing of leading white space here
  real_number_settings.SetParsePi(true);
  return real_number_settings;
}

const ON_ParseSettings ON_ParseSettings::RealNumberSettings(RealNumberSettingsHelper());

ON_ParseSettings& ON_ParseSettings::operator|=(const ON_ParseSettings& other)
{
  size_t i;

  for ( i = 0; i < sizeof(m_true_default_bits)/sizeof(m_true_default_bits[0]); i++ )
    m_true_default_bits[i] &= other.m_true_default_bits[i];

  for ( i = 0; i < sizeof(m_false_default_bits)/sizeof(m_false_default_bits[0]); i++ )
    m_false_default_bits[i] |= other.m_false_default_bits[i];

  if (0 == m_context_length_unit_system)
  {
    // "this" wins if it already has a locale id.
    // The reason is that the |= operator is used to add
    // a property to "this" when its current
    // property has a "false" value.
    m_context_length_unit_system = other.m_context_length_unit_system;
  }

  if (0 == m_context_angle_unit_system)
  {
    // "this" wins if it already has a locale id.
    // The reason is that the |= operator is used to add
    // a property to "this" when its current
    // property has a "false" value.
    m_context_angle_unit_system = other.m_context_angle_unit_system;
  }

  if (0 == m_context_locale_id)
  {
    // "this" wins if it already has a locale id.
    // The reason is that the |= operator is used to add
    // a property to "this" when its current
    // property has a "false" value.
    m_context_locale_id = other.m_context_locale_id;
  }

  return *this;
}

ON_ParseSettings& ON_ParseSettings::operator&=(const ON_ParseSettings& other)
{
  size_t i;

  for ( i = 0; i < sizeof(m_true_default_bits)/sizeof(m_true_default_bits[0]); i++ )
    m_true_default_bits[i] |= other.m_true_default_bits[i];
  
  for ( i = 0; i < sizeof(m_false_default_bits)/sizeof(m_false_default_bits[0]); i++ )
    m_false_default_bits[i] &= other.m_false_default_bits[i];
  
  if ( m_context_length_unit_system != other.m_context_length_unit_system )
  {
    m_context_length_unit_system = 0;
  }
  
  if ( m_context_angle_unit_system != other.m_context_angle_unit_system )
  {
    m_context_angle_unit_system = 0;
  }
  
  if ( m_context_locale_id != other.m_context_locale_id )
  {
    // If m_context_locale_id != other.m_context_locale_id 
    // identify the same language, then preserve the language.
    // This is useful when parsing unit names, particularly in
    // English where en-US SI unit names end in "er" and many 
    // other en-* SI unit names end in "re".  Setting 
    // m_context_locale_id to "en-ZERO" means that both
    // "meter" and "metre" will get parsed as ON::LengthUnitSystem::Meters.
    unsigned short this_language_id = (m_context_locale_id & 0x00FF);
    unsigned short other_language_id = (other.m_context_locale_id & 0x00FF);
    if ( this_language_id == other_language_id )
      m_context_locale_id = this_language_id;
    else
      m_context_locale_id = 0;
  }

  return *this;
}

bool operator==(
  const class ON_ParseSettings& a,
  const class ON_ParseSettings& b
  )
{
  return 0 == ON_ParseSettings::Compare(&a,&b);
}

bool operator!=(
  const class ON_ParseSettings& a,
  const class ON_ParseSettings& b
  )
{
  return 0 != ON_ParseSettings::Compare(&a,&b);
}

ON_ParseSettings operator||(
  const class ON_ParseSettings& a,
  const class ON_ParseSettings& b
  )
{
  ON_ParseSettings a_or_b(a);
  a_or_b |= b;
  return a_or_b;
}

ON_ParseSettings operator&&(
  const class ON_ParseSettings& a,
  const class ON_ParseSettings& b
  )
{
  ON_ParseSettings a_and_b(a);
  a_and_b &= b;
  return a_and_b;
}


#define ON_ParseNumberSettingsBitTrueDefault(n)  (0 == (m_true_default_bits[n/32]  & (1<<((unsigned int)(n%32)))))
#define ON_ParseNumberSettingsBitFalseDefault(n) (0 != (m_false_default_bits[n/32] & (1<<((unsigned int)(n%32)))))
#define ON_SetParseNumberSettingsBitTrueDefault(e,b)  unsigned int n = e; unsigned int mask = (1<<(n%32)); if (b) m_true_default_bits[n/32]  &= ~mask; else m_true_default_bits[n/32]  |=  mask
#define ON_SetParseNumberSettingsBitFalseDefault(e,b) unsigned int n = e; unsigned int mask = (1<<(n%32)); if (b) m_false_default_bits[n/32] |=  mask; else m_false_default_bits[n/32] &= ~mask

enum bitdex_true_default
{
  parse_leading_white_space,
  parse_arithmetic_expression,
  parse_explicit_formula_expression, // old style =(...) formula syntax
  parse_unary_minus,
  parse_unary_plus,
  parse_significand_integer_part,     // digits before the decimal point
  parse_significand_decimal_point,    // the decimal point
  parse_significand_fractional_part,  // digits after the decimal point
  parse_significand_digit_separators, // characters that delimit groups of digits
  parse_scientific_e_notation,
  parse_rational_number,
  parse_pi,
  parse_multiplication,
  parse_division,
  parse_addition,
  parse_subtraction,
  parse_math_functions,
  parse_paired_parentheses,
  parse_integer_dash_fraction,
  parse_feet_inches,
  parse_arc_degrees_minutes_seconds,
  parse_surveyors_notation,

  parse_full_stop_as_decimal_point,

  parse_hyphen_minus_as_number_dash,
  parse_whitespace_between_value_and_unit_system,
  parse_whitespace_between_feet_and_inches,

  // interior, leading, and trailing white space
  parse_horizontal_tab_as_whitespace,
  parse_space_as_whitespace,
  parse_nobreak_space_as_whitespace,
  parse_thin_space_as_whitespace,
  parse_nobreak_thin_space_as_whitespace,

  // leading white space
  parse_form_feed_as_leading_whitespace,
  parse_carriage_return_as_leading_whitespace,
  parse_line_feed_as_leading_whitespace,
  parse_vertical_tab_as_leading_whitespace,

  // trailing white space
  parse_form_feed_as_trailing_whitespace,
  parse_carriage_return_as_trailing_whitespace,
  parse_line_feed_as_trailing_whitespace,
  parse_vertical_tab_as_trailing_whitespace,

  // unary minus signs
  parse_hyphen_minus_as_unary_minus,
  parse_modifier_letter_minus_sign_as_unary_minus,
  parse_heavy_minus_sign_as_unary_minus,
  parse_small_hyphen_minus_as_unary_minus,
  parse_fullwidth_hyphen_minus_as_unary_minus,

  // unary plus signs
  parse_plus_as_unary_plus,
  parse_heavy_plus_as_unary_plus,
  parse_small_plus_as_unary_plus,
  parse_fullwidth_plus_as_unary_plus,

  // maximum 64 true default settings
};

enum bitdex_false_default
{
  parse_d_as_e_in_scientific_e_notation,

  parse_comma_as_decimal_point,

  parse_full_stop_as_digit_separator,
  parse_comma_as_digit_separator,
  parse_space_as_digit_separator,
  parse_thin_space_as_digit_separator,
  parse_nobreak_space_as_digit_separator,
  parse_nobreak_thin_space_as_digit_separator,

  parse_invalid_expression_error,
  parse_divide_by_zero_error,
  parse_overflow_error,

  parse_hyphen_as_number_dash,
  parse_nobreak_hyphen_as_number_dash,

  // maximum 64 false default settings
};

bool ON_ParseSettings::ParseLeadingWhiteSpace() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_leading_white_space);
}

bool ON_ParseSettings::ParseArithmeticExpression() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_arithmetic_expression);
}

bool ON_ParseSettings::ParseMathFunctions() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_math_functions);
}

bool ON_ParseSettings::ParseExplicitFormulaExpression() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_explicit_formula_expression);
}

bool ON_ParseSettings::ParseUnaryMinus() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_unary_minus);
}

bool ON_ParseSettings::ParseUnaryPlus() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_unary_plus);
}

bool ON_ParseSettings::ParseSignificandIntegerPart() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_significand_integer_part);
}

bool ON_ParseSettings::ParseSignificandDecimalPoint() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_significand_decimal_point);
}

bool ON_ParseSettings::ParseSignificandFractionalPart() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_significand_fractional_part);
}

bool ON_ParseSettings::ParseSignificandDigitSeparators() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_significand_digit_separators);
}

bool ON_ParseSettings::ParseDAsExponentInScientificENotation() const
{
  return ON_ParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_d_as_e_in_scientific_e_notation);
}

bool ON_ParseSettings::ParseScientificENotation() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_scientific_e_notation);
}

bool ON_ParseSettings::ParseFullStopAsDecimalPoint() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_full_stop_as_decimal_point);
}

bool ON_ParseSettings::ParseCommaAsDecimalPoint() const
{
  return ON_ParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_comma_as_decimal_point);
}

bool ON_ParseSettings::ParseFullStopAsDigitSeparator() const
{
  if ( ParseFullStopAsDecimalPoint() )
    return false;
  return ON_ParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_full_stop_as_digit_separator);
}

bool ON_ParseSettings::ParseCommaAsDigitSeparator() const
{
  if ( ParseCommaAsDecimalPoint() )
    return false;
  return ON_ParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_comma_as_digit_separator);
}

bool ON_ParseSettings::ParseSpaceAsDigitSeparator() const
{
  return ON_ParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_space_as_digit_separator);
}

bool ON_ParseSettings::ParseThinSpaceAsDigitSeparator() const
{
  return ON_ParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_thin_space_as_digit_separator);
}

bool ON_ParseSettings::ParseNoBreakSpaceAsDigitSeparator() const
{
  return ON_ParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_nobreak_space_as_digit_separator);
}

bool ON_ParseSettings::ParseNoBreakThinSpaceAsDigitSeparator() const
{
  return ON_ParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_nobreak_thin_space_as_digit_separator);
}

bool ON_ParseSettings::ParseHyphenMinusAsNumberDash() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_hyphen_minus_as_number_dash);
}

bool ON_ParseSettings::ParseHyphenAsNumberDash() const
{
  return ON_ParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_hyphen_as_number_dash);
}

bool ON_ParseSettings::ParseNoBreakHyphenAsNumberDash() const
{
  return ON_ParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_nobreak_hyphen_as_number_dash);
}

bool ON_ParseSettings::ParseRationalNumber() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_rational_number);
}

bool ON_ParseSettings::ParsePi() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_pi);
}

bool ON_ParseSettings::ParseMultiplication() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_multiplication);
}

bool ON_ParseSettings::ParseDivision() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_division);
}


bool ON_ParseSettings::ParseAddition() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_addition);
}

bool ON_ParseSettings::ParseSubtraction() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_subtraction);
}

bool ON_ParseSettings::ParsePairedParentheses() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_paired_parentheses);
}

bool ON_ParseSettings::ParseIntegerDashFraction() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_integer_dash_fraction);
}

bool ON_ParseSettings::ParseFeetInches() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_feet_inches);
}

bool ON_ParseSettings::ParseArcDegreesMinutesSeconds() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_arc_degrees_minutes_seconds);
}

bool ON_ParseSettings::ParseWhiteSpaceBetweenValueAndUnitSystem() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_whitespace_between_value_and_unit_system);
}

bool ON_ParseSettings::ParseWhiteSpaceBetweenFeetAndInches() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_whitespace_between_feet_and_inches);
}

bool ON_ParseSettings::ParseSurveyorsNotation() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_surveyors_notation);
}

unsigned int ON_ParseSettings::ContextLocaleId() const
{
  return m_context_locale_id;
}

unsigned int ON_ParseSettings::PreferedLocaleId() const
{
  return ContextLocaleId();
}

ON::LengthUnitSystem ON_ParseSettings::ContextLengthUnitSystem() const
{
  return ON::LengthUnitSystemFromUnsigned(m_context_length_unit_system);
}

ON::AngleUnitSystem ON_ParseSettings::ContextAngleUnitSystem() const
{
  return
    (m_context_angle_unit_system > 0)
    ? ON::AngleUnitSystemFromUnsigned(m_context_angle_unit_system)
    : ON::AngleUnitSystem::Radians;
}

ON::AngleUnitSystem ON_ParseSettings::DefaultAngleUnitSystem() const
{
  return ContextAngleUnitSystem();
}

void ON_ParseSettings::SetParseLeadingWhiteSpace(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_leading_white_space,bParse);
}

void ON_ParseSettings::SetParseArithmeticExpression(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_arithmetic_expression,bParse);
}

void ON_ParseSettings::SetParseMathFunctions(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_math_functions,bParse);
}

void ON_ParseSettings::SetParseExplicitFormulaExpression(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_explicit_formula_expression,bParse);
}

void ON_ParseSettings::SetParseUnaryMinus(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_unary_minus,bParse);
}

void ON_ParseSettings::SetParseUnaryPlus(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_unary_plus,bParse);
}

void ON_ParseSettings::SetParseSignificandIntegerPart(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_significand_integer_part,bParse);
}

void ON_ParseSettings::SetParseSignificandDecimalPoint(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_significand_decimal_point,bParse);
}

void ON_ParseSettings::SetParseSignificandFractionalPart(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_significand_fractional_part,bParse);
}

void ON_ParseSettings::SetParseSignificandDigitSeparators(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_significand_digit_separators,bParse);
}

void ON_ParseSettings::SetParseDAsExponentInScientificENotation(bool bParse)
{
  ON_SetParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_d_as_e_in_scientific_e_notation,bParse);
}

void ON_ParseSettings::SetParseScientificENotation(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_scientific_e_notation,bParse);
}

void ON_ParseSettings::SetParseFullStopAsDecimalPoint( bool bParse )
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_full_stop_as_decimal_point,bParse);
}

void ON_ParseSettings::SetParseFullStopAsDigitSeparator( bool bParse )  
{
  ON_SetParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_full_stop_as_digit_separator,bParse);
}

void ON_ParseSettings::SetParseCommaAsDecimalPoint( bool bParse )
{
  ON_SetParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_comma_as_decimal_point,bParse);
}

void ON_ParseSettings::SetParseCommaAsDigitSeparator( bool bParse )
{
  ON_SetParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_comma_as_digit_separator,bParse);
}

void ON_ParseSettings::SetParseSpaceAsDigitSeparator( bool bParse )
{
  ON_SetParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_space_as_digit_separator,bParse);
}

void ON_ParseSettings::SetParseThinSpaceAsDigitSeparator( bool bParse )
{
  ON_SetParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_thin_space_as_digit_separator,bParse);
}

void ON_ParseSettings::SetParseNoBreakSpaceAsDigitSeparator( bool bParse )
{
  ON_SetParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_nobreak_space_as_digit_separator,bParse);
}

void ON_ParseSettings::SetParseNoBreakThinSpaceAsDigitSeparator( bool bParse )
{
  ON_SetParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_nobreak_thin_space_as_digit_separator,bParse);
}

void ON_ParseSettings::SetParseHyphenMinusAsNumberDash( bool bParse )
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_hyphen_minus_as_number_dash,bParse);
}

void ON_ParseSettings::SetParseHyphenAsNumberDash( bool bParse )
{
  ON_SetParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_hyphen_as_number_dash,bParse);
}

void ON_ParseSettings::SetParseNoBreakHyphenAsNumberDash( bool bParse )
{
  ON_SetParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_nobreak_hyphen_as_number_dash,bParse);
}


void ON_ParseSettings::SetParseRationalNumber(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_rational_number,bParse);
}


void ON_ParseSettings::SetParsePi(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_pi,bParse);
}

void ON_ParseSettings::SetParseMultiplication(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_multiplication,bParse);
}

void ON_ParseSettings::SetParseDivision(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_division,bParse);
}

void ON_ParseSettings::SetParseAddition(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_addition,bParse);
}

void ON_ParseSettings::SetParseSubtraction(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_subtraction,bParse);
}

void ON_ParseSettings::SetParsePairedParentheses(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_paired_parentheses,bParse);
}

void ON_ParseSettings::SetParseIntegerDashFraction(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_integer_dash_fraction,bParse);
}

void ON_ParseSettings::SetParseFeetInches(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_feet_inches,bParse);
}

void ON_ParseSettings::SetParseArcDegreesMinutesSeconds(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_arc_degrees_minutes_seconds,bParse);
}


void ON_ParseSettings::SetParseWhiteSpaceBetweenValueAndUnitSystem(
  bool bParseWhiteSpaceBetweenValueAndUnitSystem
)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_whitespace_between_value_and_unit_system,bParseWhiteSpaceBetweenValueAndUnitSystem);
}


void ON_ParseSettings::SetParseWhiteSpaceBetweenFeetAndInches(
  bool bParseWhiteSpaceBetweenFeetAndInches
)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_whitespace_between_feet_and_inches,bParseWhiteSpaceBetweenFeetAndInches);
}

void ON_ParseSettings::SetParseSurveyorsNotation(bool bParse)
{
  ON_SetParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_surveyors_notation,bParse);
}

void ON_ParseSettings::SetContextLocaleId(
  unsigned int context_locale_id
  )
{
  m_context_locale_id = (context_locale_id <= 0xFFFF)
                       ? ((unsigned short)context_locale_id)
                       : 0;
}

void ON_ParseSettings::SetPreferedLocaleId(
  unsigned int context_locale_id
  )
{
  SetContextLocaleId(context_locale_id);
}

void ON_ParseSettings::SetContextLengthUnitSystem(
  ON::LengthUnitSystem context_length_unit_system
  )
{
  for (;;)
  {
    if (ON::LengthUnitSystem::None == context_length_unit_system || ON::LengthUnitSystem::Unset == context_length_unit_system)
      break;
    const unsigned int length_unit_system_as_unsigned = static_cast<unsigned int>(context_length_unit_system);
    if (length_unit_system_as_unsigned > 0xFFU)
      break;
    if (context_length_unit_system != ON::LengthUnitSystemFromUnsigned(length_unit_system_as_unsigned))
      break;
    m_context_length_unit_system = (ON__UINT8)length_unit_system_as_unsigned;
    return;
  }
  m_context_length_unit_system = 0; // no length unit system
}

void ON_ParseSettings::SetContextAngleUnitSystem(
  ON::AngleUnitSystem context_angle_unit_system
  )
{
  for (;;)
  {
    if (ON::AngleUnitSystem::None == context_angle_unit_system || ON::AngleUnitSystem::Unset == context_angle_unit_system)
      break;
    const unsigned int angle_unit_system_as_unsigned = static_cast<unsigned int>(context_angle_unit_system);
    if (angle_unit_system_as_unsigned > 0xFFU)
      break;
    if (context_angle_unit_system != ON::AngleUnitSystemFromUnsigned(angle_unit_system_as_unsigned))
      break;
    m_context_angle_unit_system = (ON__UINT8)angle_unit_system_as_unsigned;
    return;
  }
  m_context_angle_unit_system = 0; // radians
}

void ON_ParseSettings::SetDefaultAngleUnitSystem(
  ON::AngleUnitSystem context_angle_unit_system
  )
{
  SetContextAngleUnitSystem(context_angle_unit_system);
}

bool ON_ParseSettings::ParseSpaceAsWhiteSpace() const 
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_space_as_whitespace);
}

bool ON_ParseSettings::ParseNoBreakSpaceAsWhiteSpace() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_nobreak_space_as_whitespace);
}

bool ON_ParseSettings::ParseHorizontalTabAsWhiteSpace() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_horizontal_tab_as_whitespace);
}

bool ON_ParseSettings::ParseThinSpaceAsWhiteSpace() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_thin_space_as_whitespace);
}

bool ON_ParseSettings::ParseNoBreakThinSpaceAsWhiteSpace() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_nobreak_thin_space_as_whitespace);
}

bool ON_ParseSettings::ParseLineFeedAsLeadingWhiteSpace() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_line_feed_as_leading_whitespace);
}

bool ON_ParseSettings::ParseFormFeedAsLeadingWhiteSpace() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_form_feed_as_leading_whitespace);
}

bool ON_ParseSettings::ParseCarriageReturnAsLeadingWhiteSpace() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_carriage_return_as_leading_whitespace);
}

bool ON_ParseSettings::ParseVerticalTabAsLeadingWhiteSpace() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_vertical_tab_as_leading_whitespace);
}

bool ON_ParseSettings::ParseLineFeedAsTrailingWhiteSpace() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_line_feed_as_trailing_whitespace);
}

bool ON_ParseSettings::ParseFormFeedAsTrailingWhiteSpace() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_form_feed_as_trailing_whitespace);
}

bool ON_ParseSettings::ParseCarriageReturnAsTrailingWhiteSpace() const 
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_carriage_return_as_trailing_whitespace);
}

bool ON_ParseSettings::ParseVerticalTabAsTrailingWhiteSpace() const
{
  return ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_vertical_tab_as_trailing_whitespace);
}

void ON_ParseSettings::SetParseSpaceAsWhiteSpace( bool bParseAsWhiteSpace ) 
{
  ON_SetParseNumberSettingsBitTrueDefault( bitdex_true_default::parse_space_as_whitespace, bParseAsWhiteSpace );
}

void ON_ParseSettings::SetParseNoBreakSpaceAsWhiteSpace( bool bParseAsWhiteSpace )
{
  ON_SetParseNumberSettingsBitTrueDefault( bitdex_true_default::parse_nobreak_space_as_whitespace, bParseAsWhiteSpace );
}

void ON_ParseSettings::SetParseHorizontalTabAsWhiteSpace( bool bParseAsWhiteSpace )
{
  ON_SetParseNumberSettingsBitTrueDefault( bitdex_true_default::parse_horizontal_tab_as_whitespace, bParseAsWhiteSpace );
}

void ON_ParseSettings::SetParseThinSpaceAsWhiteSpace( bool bParseAsWhiteSpace )
{
  ON_SetParseNumberSettingsBitTrueDefault( bitdex_true_default::parse_thin_space_as_whitespace, bParseAsWhiteSpace );
}

void ON_ParseSettings::SetParseNoBreakThinSpaceAsWhiteSpace( bool bParseAsWhiteSpace )
{
  ON_SetParseNumberSettingsBitTrueDefault( bitdex_true_default::parse_nobreak_thin_space_as_whitespace, bParseAsWhiteSpace );
}

void ON_ParseSettings::SetParseLineFeedAsLeadingWhiteSpace( bool bParseAsWhiteSpace )
{
  ON_SetParseNumberSettingsBitTrueDefault( bitdex_true_default::parse_line_feed_as_leading_whitespace, bParseAsWhiteSpace );
}

void ON_ParseSettings::SetParseFormFeedAsLeadingWhiteSpace( bool bParseAsWhiteSpace )
{
  ON_SetParseNumberSettingsBitTrueDefault( bitdex_true_default::parse_form_feed_as_leading_whitespace, bParseAsWhiteSpace );
}

void ON_ParseSettings::SetParseCarriageReturnAsLeadingWhiteSpace( bool bParseAsWhiteSpace )
{
  ON_SetParseNumberSettingsBitTrueDefault( bitdex_true_default::parse_carriage_return_as_leading_whitespace, bParseAsWhiteSpace );
}

void ON_ParseSettings::SetParseVerticalTabAsLeadingWhiteSpace( bool bParseAsWhiteSpace )
{
  ON_SetParseNumberSettingsBitTrueDefault( bitdex_true_default::parse_vertical_tab_as_leading_whitespace, bParseAsWhiteSpace );
}

void ON_ParseSettings::SetParseLineFeedAsTrailingWhiteSpace( bool bParseAsWhiteSpace )
{
  ON_SetParseNumberSettingsBitTrueDefault( bitdex_true_default::parse_line_feed_as_trailing_whitespace, bParseAsWhiteSpace );
}

void ON_ParseSettings::SetParseFormFeedAsTrailingWhiteSpace( bool bParseAsWhiteSpace )
{
  ON_SetParseNumberSettingsBitTrueDefault( bitdex_true_default::parse_form_feed_as_trailing_whitespace, bParseAsWhiteSpace );
}

void ON_ParseSettings::SetParseCarriageReturnAsTrailingWhiteSpace( bool bParseAsWhiteSpace ) 
{
  ON_SetParseNumberSettingsBitTrueDefault( bitdex_true_default::parse_carriage_return_as_trailing_whitespace, bParseAsWhiteSpace );
}


void ON_ParseSettings::SetParseVerticalTabAsTrailingWhiteSpace( bool bParseAsWhiteSpace )
{
  ON_SetParseNumberSettingsBitTrueDefault( bitdex_true_default::parse_vertical_tab_as_trailing_whitespace, bParseAsWhiteSpace );
}

bool ON_ParseSettings::IsLeadingWhiteSpace(ON__UINT32 c) const
{
  if (IsInteriorWhiteSpace(c))
    return true;

  switch(c)
  {
  case 0x000A: // line feed
    if ( ParseLineFeedAsLeadingWhiteSpace() )
      return true;
    break;

  case 0x000B: // vertical tab
    if ( ParseVerticalTabAsLeadingWhiteSpace() )
      return true;
    break;

  case 0x000C: // form feed
    if ( ParseFormFeedAsLeadingWhiteSpace() )
      return true;
    break;

  case 0x000D: // carriage return
    if ( ParseCarriageReturnAsLeadingWhiteSpace() )
      return true;
    break;
  }

  return false;
}

bool ON_ParseSettings::IsTrailingWhiteSpace(ON__UINT32 c) const
{
  if (IsInteriorWhiteSpace(c))
    return true;

  switch(c)
  {
  case 0x000A: // line feed
    if ( ParseLineFeedAsTrailingWhiteSpace() )
      return true;
    break;

  case 0x000B: // vertical tab
    if ( ParseVerticalTabAsTrailingWhiteSpace() )
      return true;
    break;

  case 0x000C: // form feed
    if ( ParseFormFeedAsTrailingWhiteSpace() )
      return true;
    break;

  case 0x000D: // carriage return
    if ( ParseCarriageReturnAsTrailingWhiteSpace() )
      return true;
    break;
  }

  return false;}


bool ON_ParseSettings::IsInteriorWhiteSpace(ON__UINT32 c) const
{
  switch(c)
  {
  case 0x0009: // horizontal tab
    if ( ParseHorizontalTabAsWhiteSpace() )
      return true;
    break;

  case 0x0020: // space
    if ( ParseSpaceAsWhiteSpace() )
      return true;

  case 0x00A0: // no-break space
    return ParseNoBreakSpaceAsWhiteSpace();
    break;

  case 0x2008: // thin space
  case 0x2009: // thin space
  case 0x200A: // hair thin space
    return ParseThinSpaceAsWhiteSpace();
    break;

  case 0x202F: // narrow no-break
    return ParseNoBreakThinSpaceAsWhiteSpace();
    break;
  }

  return false;
}


bool ON_ParseSettings::IsUnaryMinus(ON__UINT32 c) const
{
  switch(c)
  {
  case 0x002D: // hyphen-minus
    if ( ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_hyphen_minus_as_unary_minus) )
      return true;
    break;

  case 0x02D7: // modifier letter minus sign
    if ( ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_modifier_letter_minus_sign_as_unary_minus) )
      return true;
    break;

  case 0x2796: // heavy minus sign
    if ( ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_heavy_minus_sign_as_unary_minus) )
      return true;
    break;

  case 0xFE63: // small hyphen-minus
    if ( ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_small_hyphen_minus_as_unary_minus) )
      return true;
    break;

  case 0xFF0D: // fullwidth hyphen-minus
    if ( ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_fullwidth_hyphen_minus_as_unary_minus) )
      return true;
    break;
  }
  return false;
}

bool ON_ParseSettings::IsUnaryPlus(ON__UINT32 c) const
{
  switch(c)
  {
  case 0x002B: // plus
    if ( ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_plus_as_unary_plus) )
      return true;
    break;

  case 0x2795: // heavy plus sign
    if ( ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_heavy_plus_as_unary_plus) )
      return true;
    break;

  case 0xFE62: // small plus sign
    if ( ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_small_plus_as_unary_plus) )
      return true;
    break;

  case 0xFE0B: // fullwidth plus sign
    if ( ON_ParseNumberSettingsBitTrueDefault(bitdex_true_default::parse_fullwidth_plus_as_unary_plus) )
      return true;
    break;
  }
  return false;
}

char ON_ParseSettings::IsDigit(ON__UINT32 c) const
{
  return ( c >= '0' && c <= '9' ) ? ((char)c) : 0;
}

bool ON_ParseSettings::IsDigitSeparator(ON__UINT32 c) const
{
  if ( IsDecimalPoint(c) )
    return false; // prohibit the same symbol from being used as a decimal point

  switch(c)
  {
  case 0x002C: // comma
    return ParseCommaAsDigitSeparator(); // default = true
    break;

  case 0x002E: // full stop (period)
    return ParseFullStopAsDigitSeparator(); // default = false
    break;

  case 0x0020: // space
    return ParseSpaceAsDigitSeparator(); // default = true
    break;

  case 0x00A0: // no-break space
    return ParseNoBreakSpaceAsDigitSeparator();
    break;

  case 0x2008: // thin space
  case 0x2009: // thin space
  case 0x200A: // hair thin space
    return ParseThinSpaceAsDigitSeparator();
    break;

  case 0x202F: // narrow no-break
    return ParseNoBreakThinSpaceAsDigitSeparator();
    break;

  case 0x066C: // UNICODE ARABIC THOUSANDS SEPARATOR
    // Intended to be used with eastern arabic numerals,
    // but its lexical function is always a thousands separator.
    return false;
    break;

  }

  return false;
}

bool ON_ParseSettings::IsDecimalPoint(ON__UINT32 c) const
{
  switch(c)
  {
  case 0x002C: // comma
    return ParseCommaAsDecimalPoint();
    break;

  case 0x002E: // full stop (period)
    return ParseFullStopAsDecimalPoint();
    break;

  case 0x2396: // UNICODE DECIMAL SEPARATOR KEY SYMBOL
    // Intended to be used as a symbol on keyboards,
    // but its lexical function is always a decimal point.
    return true;
    break;

  case 0x066B: // UNICODE ARABIC DECIMAL SEPARATOR
    // Intended to be used with eastern arabic numerals,
    // but its lexical function is always a decimal point.
    return true;
    break;
  }
  return false;
}


bool ON_ParseSettings::IsDecimalExponentSymbol(ON__UINT32 c) const
{
  switch(c)
  {
  case 'e': // lower case e
  case 'E': // capital E
  case 0x23E8: // decimal exponent symbol
    return true;
    break;

  case 'D': // capital D
  case 'd': // lower case d
    return ParseDAsExponentInScientificENotation();
    break;
  }
  return false;
}

bool ON_ParseSettings::IsGreekPi(ON__UINT32 c) const
{
  switch(c)
  {
  case 0x03A:
  case 0x03C:
    return true;
    break;
  }

  return false;
}

bool ON_ParseSettings::IsMultiplicationSymbol(ON__UINT32 c) const
{
  switch(c)
  {
  case '*':
  case 0x00D7: // unicode multiply by symbol
    return true;
    break;
  }

  return false;
}


bool ON_ParseSettings::IsDivisionSymbol(ON__UINT32 c) const
{
  switch(c)
  {
  case '/':
  case 0x00F7: // unicode divide by symbol
    return true;
    break;
  }

  return false;
}


bool ON_ParseSettings::IsAdditionSymbol(ON__UINT32 c) const
{
  switch(c)
  {
  case 0x002B: // unicode plus by symbol
    return true;
    break;
  }

  return false;
}

bool ON_ParseSettings::IsSubtractionSymbol(ON__UINT32 c) const
{
  switch(c)
  {
  case '-': // unicode hyphen minus
  case 0x2212: // unicode minus sign
    return true;
    break;
  }

  return false;
}

bool ON_ParseSettings::IsLeftParenthesisSymbol(ON__UINT32 c) const
{
  return ('(' == c);
}

bool ON_ParseSettings::IsRightParenthesisSymbol(ON__UINT32 c) const
{
  return (')' == c);
}

bool ON_ParseSettings::IsRationalNumberFractionBar(ON__UINT32 c) const
{
  return ('/' == c);
}

bool ON_ParseSettings::IsNumberDash(ON__UINT32 c) const
{
  switch(c)
  {
  case 0x002D: // hyphen-minus '-' <- BAD CHOICE, but very common because it's the easiest to type
    return this->ParseHyphenMinusAsNumberDash();
    break;
  case 0x2010: // unicode hyphen
    return this->ParseHyphenAsNumberDash();
    break;
  case 0x2011: // unicode non-breaking hyphen
    return this->ParseNoBreakHyphenAsNumberDash();
    break;
  case 0x2012: // unicode figure dash <- GOOD CHOICE See http://en.wikipedia.org/wiki/Dash
    return true;
    break;

  // NOTES:
  //  THe en dash 0x2013 is not offered as an option because it
  //  is commonly used as a minus sign because its with is the
  //  same as a plus sign.
  //  The em dash 0x2014 is not offered as an option because its
  //  length makes it unlikely that it would be used to indicate
  //  the dash in 1-3/4.
  //  See http://en.wikipedia.org/wiki/Dash for more information.
  }

  return false;
}

bool ON_ParseSettings::ParseError() const
{
  return    ParseDivideByZeroError() 
         || ParseOverflowError()
         || ParseInvalidExpressionError()
         ;
}

bool ON_ParseSettings::ParseDivideByZeroError() const
{
  return ON_ParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_divide_by_zero_error);
}

bool ON_ParseSettings::ParseOverflowError() const
{
  return ON_ParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_overflow_error);
}

bool ON_ParseSettings::ParseInvalidExpressionError() const
{
  return ON_ParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_invalid_expression_error);
}

void ON_ParseSettings::SetParseDivideByZeroError(
  bool bParseDivideByZeroError
  )
{
  ON_SetParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_divide_by_zero_error,bParseDivideByZeroError);
}

void ON_ParseSettings::SetParseOverflowError(
  bool bParseOverflowError
  )
{
  ON_SetParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_overflow_error,bParseOverflowError);
}

void ON_ParseSettings::SetParseInvalidExpressionError(
  bool bParseInvalidExpressionError
  )
{
  ON_SetParseNumberSettingsBitFalseDefault(bitdex_false_default::parse_invalid_expression_error,bParseInvalidExpressionError);
}

