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


ON_LengthValue::StringFormat ON_LengthValue::LengthStringFormatFromUnsigned(
  unsigned int string_format_as_unsigned
)
{
  switch (string_format_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_LengthValue::StringFormat::ExactDecimal);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_LengthValue::StringFormat::ExactProperFraction);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_LengthValue::StringFormat::ExactImproperFraction);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_LengthValue::StringFormat::CleanDecimal);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_LengthValue::StringFormat::CleanProperFraction);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_LengthValue::StringFormat::CleanImproperFraction);
  }
  ON_ERROR("Invalid string_format_as_unsigned value.");
  return (ON_LengthValue::Unset.m_string_format);
}


ON_AngleValue::StringFormat ON_AngleValue::AngleStringFormatFromUnsigned(
  unsigned int string_format_as_unsigned
)
{
  switch (string_format_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_AngleValue::StringFormat::ExactDecimal);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_AngleValue::StringFormat::ExactFraction);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_AngleValue::StringFormat::CleanDecimal);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_AngleValue::StringFormat::CleanFraction);
  }
  ON_ERROR("Invalid string_format_as_unsigned value.");
  return (ON_AngleValue::Unset.m_string_format);
}

const ON_LengthValue ON_LengthValue::RemoveUnitSystem() const
{
  if (
    ON::LengthUnitSystem::Unset == this->LengthUnitSystem().UnitSystem()
    || ON::LengthUnitSystem::None == this->LengthUnitSystem().UnitSystem()
    )
  {
    return *this;
  }

  ON_LengthValue rc(*this);
  rc.m_length_unit_system = ON_UnitSystem::None;

  const ON_ParseSettings parse_settings = rc.LengthStringParseSettings();
  const wchar_t* str = static_cast<const wchar_t*>(rc.m_length_as_string);
  const int str_count = rc.m_length_as_string.Length();
  ON_ParseSettings parse_results;
  double x = ON_DBL_QNAN;
  int str_index = ON_ParseNumberExpression(str, str_count, parse_settings, &parse_results, &x);
  if (str_index > 0 && str_index <= str_count && x == m_length)
  {
    rc.m_length_as_string.SetLength(str_index);
    rc.m_length_as_string.TrimLeftAndRight();
  }
  else
  {
    rc = ON_LengthValue::Create(m_length, ON_LengthUnitName::None, m_string_format);
    if (!(rc.m_length == m_length))
    {
      ON_ERROR("Unable to remove unit system");
      return *this;
    }
  }
  return rc;
}

const ON_LengthValue ON_LengthValue::ChangeLength(
  double length_value
) const
{
  ON_LengthValue rc(*this);
  if (!ON_IsValid(length_value))
  {
    rc.m_length_as_string = ON_wString::EmptyString;
    rc.m_length = ON_LengthValue::Unset.m_length;
  }
  else
  {
    rc = ON_LengthValue::Create(length_value, m_length_unit_system, m_context_locale_id, m_string_format);
  }
  return rc;
}


ON_LengthValue ON_LengthValue::CreateFromString(
  ON_ParseSettings parse_settings,
  const wchar_t* string
)
{
  if ( nullptr == string || 0 == string[0] )
    return ON_LengthValue::Unset;

  const wchar_t* string_end = nullptr;
  const ON_LengthValue length_value = ON_LengthValue::CreateFromSubString(parse_settings, string, -1, &string_end);
  if (nullptr == string_end || !(string < string_end))
  {
    // Calling ON_ERROR here causes .NET trauma when ON_LengthValue::CreateFromString() is used for 
    // input validation.
    //ON_ERROR("Invalid input parameters.");
    return ON_LengthValue::Unset;
  }

  return length_value;
}

ON_LengthValue ON_LengthValue::CreateFromSubString(
    ON_ParseSettings parse_settings,
    const wchar_t* string,
    int string_count,
    const wchar_t** string_end
  )
{
  // All calls to some version of ON_LengthValue::CreateFrom*String(...) end up here.
  if (nullptr != string_end && &string != string_end)
    *string_end = string;

  if (string_count < -1)
  {
    ON_ERROR("Invalid string_count parameter.");
    return ON_LengthValue::Unset;
  }

  if (nullptr == string || 0 == string_count || 0 == string[0] )
  {
    // empty string fails silently.
    return ON_LengthValue::Unset;
  }

  double length_value = ON_DBL_QNAN;
  ON_ParseSettings parse_results;
  ON::LengthUnitSystem string_length_unit_system = ON::LengthUnitSystem::Unset;
  const int parse_count = ON_ParseLengthExpression(
    string,
    string_count,
    parse_settings, 
    &length_value,
    &parse_results,
    &string_length_unit_system
  );

  if ( parse_count <= 0 
    || (parse_count > string_count && string_count >= 0)
    || false == (length_value == length_value) 
    ) 
  {
    // Calling ON_ERROR HERE .NET wrapper trauma when CreateFromSubString() is used for string validation.
    // ON_ERROR("Input string parameter is not valid.");
    return ON_LengthValue::Unset;
  }

  ON_LengthValue rc;

  rc.m_length = length_value;

  if (ON::LengthUnitSystem::Unset != string_length_unit_system && ON::LengthUnitSystem::None != string_length_unit_system)
    rc.m_length_unit_system = ON_UnitSystem(string_length_unit_system);
  else
    rc.m_length_unit_system = ON_UnitSystem(parse_settings.ContextLengthUnitSystem());

  rc.m_context_angle_unit_system = parse_settings.ContextAngleUnitSystem();
  rc.m_context_locale_id = parse_settings.ContextLocaleId();

  rc.m_length_as_string = ON_wString(string, parse_count);
  rc.m_length_as_string.TrimLeftAndRight();

  if (nullptr != string_end)
    *string_end = string + parse_count;

  return rc;
}

static 
double ON_CleanValueTolerance(
  double value,
  double clean_value_tolerance
)
{
  if (clean_value_tolerance > 1.0 / 512.0)
    clean_value_tolerance = 1.0 / 512.0;
  const double a = fabs(value);
  // The relative tolerance 256.0*ON_EPSILON*a is required in order for all (1+/- ON_EPSILON)*value where
  // value is one of the rational numbers with denominators
  // 2,3,4,8,10,16,32,64,128 and numerators from 1 to 2*denominator to be "cleaned up}
  // to numerator/denominator.
  const double relative_tolerance = 256.0*ON_EPSILON*a;
  return (clean_value_tolerance > relative_tolerance) ? clean_value_tolerance : relative_tolerance;
}

static
double ON_CleanNumber(
  double value,
  double clean_value_tolerance
)
{
  if (!ON_IsValid(value))
    return value;

  const double tol = ON_CleanValueTolerance(value, clean_value_tolerance);
  if (fabs(value) <= tol)
    return 0.0;

  const double s = (value < 0.0) ? -1.0 : 1.0;
  const double a = fabs(value);
  double i = 0.0;
  const double f = modf(a, &i);
  if (f <= tol)
    return s*i;
  if ((1.0-f) <= tol)
    return s*(i+1.0);

  // terminate these lists with 0.0.
  const double d1[] = { 2.0, 3.0, 4.0, 8.0, 10.0, 16.0, 32.0, 64.0, 128.0, 0.0 };
  const double d2[] = { 5.0, 6.0, 7.0, 9.0, 12.0, 0.0 };
  const double* d[2] = { d1, d2 };
  for (int pass = 0; pass < 2; pass++)
  {
    for (size_t k = 0; d[pass][k] > 0.0; k++)
    {
      const double y = d[pass][k] * f;
      double x = floor(y);
      if (y - x > 0.5)
        x += 1.0;
      if (fabs(x - y) <= tol)
      {
        // (i*d[pass][k] + x) / d[pass][k] is more precise (repeatable)
        // than i + x/d[pass][k]
        return s*(i*d[pass][k] + x) / d[pass][k];
      }
    }
  }

  return value;
}

const ON_wString& ON_NTimesPowerOf10AsStringFail(const ON_wString& g_format, bool bLogError)
{
  // The number being formatted might be bogus.
  // This can occur when values are not properly initialized.
  if (bLogError) // <- good place for debugging breakpoint
  {
    ON_ERROR("Unexpected result."); 
  }

  // g_format is a valid string representation of the input value, so
  // the user is seeing something that is correct, but may have
  // scientific notation or lots of digits.
  return g_format;
}

static
const ON_wString ON_NTimesPowerOf10AsString(
  double value,
  double tol,
  const ON_wString& g_format,
  ON__UINT64 n,
  int e,
  double* clean_value
)
{
  if (nullptr != clean_value)
    *clean_value = value;

  if ( false == ON_IsValid(value) )
    return ON_NTimesPowerOf10AsStringFail(g_format,false); // value is a nan or UNSET value.

  // ON__UINT64 range is 0 to 18,446,744,073,709,551,615 = 1.8...e19
  const double max_pretty_value = 1.0e18; // must be <= 18,446,744,073,709,551,615 ( 20 decimal digits )
  const double min_pretty_value = 1.0 / max_pretty_value;
  if (fabs(value) >= max_pretty_value || fabs(value) <= min_pretty_value)
    return ON_NTimesPowerOf10AsStringFail(g_format,false); // value is too big or too small for a "pretty" format.
  

  // returns n*(10^e) as a "pretty" string - no exponential notation that disturbs users.
  ON__UINT64 q = 1;
  ON__UINT64 i = 0;
  ON__UINT64 f = 0;

  if (e >= 0)
  {
    for (int ie = 0; ie < e; ie++)
      q *= 10;

    if (fabs((double)n)*fabs((double)q) >= max_pretty_value)
      return ON_NTimesPowerOf10AsStringFail(g_format,false);

    i = n*q;
    f = 0;
  }
  else
  {
    // e is negative
    for (int ie = 0; ie > e; ie--)
      q *= 10;
    if (fabs((double)n) <= min_pretty_value*fabs((double)q))
      return ON_NTimesPowerOf10AsStringFail(g_format,false);

    i = n / q;
    f = n % q;
  }

  const double x = ((double)i) + ((double)f) / ((double)q);
  if (fabs(x - value) <= tol)
  {
    if (0 == f)
    {
      if (nullptr != clean_value)
        *clean_value = x;
      return ON_wString::FormatToString(L"%llu", i);
    }
    wchar_t sf[32] = { 0 }; // 32 is more than enough to hold the maximum of 20 digits
    size_t sf_capacity = sizeof(sf) / sizeof(sf[i]);
    size_t sfi = 0;
    for (ON__UINT64 r = q / 10; r > 0 && sfi < sf_capacity; r /= 10)
    {
      sf[sfi++] = (wchar_t)(int((f / r)%10) + '0');
    }
    const ON_wString value_as_string = ON_wString::FormatToString(L"%llu.%ls", i, sf);
    double y = ON_DBL_QNAN;
    const int scan_count = value_as_string.Scan( L"%lf", &y );
    if (1 == scan_count && fabs(y - value) <= tol)
    {
      if (nullptr != clean_value)
        *clean_value = y;
      return value_as_string;
    }
  }

  return ON_NTimesPowerOf10AsStringFail(g_format,false);
}


static
const ON_wString ON_CleanNumberToString(
  double value,
  double clean_value_tolerance,
  double* clean_value
)
{
  if (nullptr != clean_value)
    *clean_value = value;
  if (!ON_IsValid(value))
    return ON_wString::EmptyString;

  // replace any -0.0 value with 0.0
  if (0.0 == value)
  {
    value = 0.0;
    if (nullptr != clean_value)
      *clean_value = value;
  }

  const double tol = ON_CleanValueTolerance(value, clean_value_tolerance);
  if (fabs(value) <= tol)
  {
    if (nullptr != clean_value)
      *clean_value = 0.0;
    return ON_wString(L"0");
  }

  const ON_wString g_format = ON_wString::FormatToString(L"%.17g", value);
  const ON_wString e_format = ON_wString::FormatToString(L"%.17e", value);
  const wchar_t* s0 = static_cast<const wchar_t*>(e_format);
  if ('-' == s0[0] || '+' == s0[0])
    s0++;
  if ( s0[0] < '0' || s0[0] > '9')
  {
    ON_ERROR("Unexpected double string format.");
    return g_format;
  }

  if ('.' != s0[1])
  {
    return g_format;
  }
  
  const wchar_t* decimal = s0;
  while (0 != *decimal && '.' != *decimal)
    decimal++;
  if ( '.' != decimal[0] || decimal[1] < '0' || decimal[1] > '9')
  {
    return g_format;
  }


  const wchar_t* exponent = s0 + 2;
  while (0 != *exponent && 'e' != *exponent && 'E' != *exponent)
    exponent++;
  if (0 == exponent[0])
    return g_format;

  int e = 0;
  if (0 != exponent[0])
  {
    for (int i = ('+' == exponent[1] || '-' == exponent[1]) ? 2 : 1; 0 != exponent[i]; i++)
    {
      if (exponent[i] < '0' || exponent[i] > '9')
      {
        ON_ERROR("Unexpected double string format.");
        return g_format;
      }
      e = 10 * e + ((int)(exponent[i] - '0'));
    }
    if (e > 0 && '-' == exponent[1])
      e = -e;
  }
  
  const unsigned int max_count = 3;
  unsigned int zero_count = 0;
  unsigned int nine_count = 0;
  const wchar_t* first_nine = nullptr;
  const wchar_t* first_zero = nullptr;

  const ON__UINT64 ten = 10;
  ON__UINT64 n = 0;
  e++; // e is unconditionally decremented when n is initialized.

  for ( const wchar_t* s = s0; s < exponent; s++)
  {
    if ('.' == *s)
      continue;
    if ('0' == *s)
    {
      if (nullptr != first_nine)
      {
        while (first_nine < s)
        {
          n = ten*n + ((ON__UINT64)(*first_nine++ - '0'));
          e--;
        }
        first_nine = nullptr;
        nine_count = 0;
      }
      if (nullptr == first_zero)
        first_zero = s;
      zero_count++;
      if (max_count == zero_count)
      {
        double x = ((double)n)*pow(10.0, e);
        if (fabs(x - value) <= tol)
        {
          return ON_NTimesPowerOf10AsString(value, tol, g_format, n, e, clean_value);
        }
      }
    }
    else if ('9' == *s)
    {
      if (nullptr != first_zero)
      {
        while (first_zero < s)
        {
          n = ten*n + ((ON__UINT64)(*first_zero++ - '0'));
          e--;
        }
        first_zero = nullptr;
        zero_count = 0;
      }
      if (nullptr == first_nine)
        first_nine = s;
      nine_count++;
      if (max_count == nine_count)
      {
        double x = ((double)(n+1))*pow(10.0, e);
        if (fabs(x - value) <= tol)
        {
          return ON_NTimesPowerOf10AsString(value, tol, g_format, n+1, e, clean_value);
        }
        nine_count--;
        n = ten*n + ((ON__UINT64)(*first_nine++ - '0'));
        e--;
      }
    }
    else
    {
      n = ten*n + ((ON__UINT64)(*s - '0'));
      e--;
    }
  }

  return g_format;
}

/*
Parameters:
  value - [in]
    value to test
  
  bImproperFraction - [in]
    True if the returned value can be an improper fraction 
    (1.25 will be 5/4, proper = 0, numerator = 5, denominator = 4).
    False if the returned value should be a proper fraction 
    (1.25 will be 1-1/4, proper = 1, numerator = 1, denominator = 4).

  sign - [out]
    +1.0, -1.0 or 0.0.



Returns:
  True: 
    value is a rational number with a denominator commonly used in annotation.
    value = sign*(proper + numerator/denominator);
  False:
    value is not a rational number with a denominator commonly used in annotation.
*/
static
bool ON_IsAnnotationFractionNumber(
  double value,
  bool bImproperFraction,
  double* sign,
  double* proper,
  double* numerator,
  double* denominator
)
{
  if (nullptr != sign)
    *sign = (value < 0.0) ? -1.0 : ((value > 0.0) ? 1.0 : 0.0);
  if (nullptr != proper)
    *proper = 0.0;
  if (nullptr != numerator)
    *numerator = value;
  if (nullptr != denominator)
    *denominator = 1.0;
  if (!ON_IsValid(value))
    return false;

  const double a = fabs(value);
  double i = 0.0;
  const double f = modf(a, &i);

  const double tol = 4.0*ON_EPSILON*a;

  if ( !(f > tol) )
    return false;

  // terminate this list with 0.0.
  const double d[] = { 2.0, 3.0, 4.0, 8.0, 10.0, 16.0, 32.0, 64.0, 128.0, 0.0 };
  for (size_t k = 0; d[k] > 0.0; k++)
  {
    const double y = d[k] * f;
    double x = floor(y);
    if (y - x > 0.5)
      x += 1.0;
    if (!(fabs(x - y) <= tol))
      continue;
    if (false == bImproperFraction && i >= 1.0)
    {
      if (nullptr != proper)
        *proper = i;
      i = 0.0;
    }
    if (nullptr != numerator)
      *numerator = i*d[k] + x;
    if (nullptr != denominator)
      *denominator = d[k];
    return true;
  }

  return false;
}

ON_LengthValue ON_LengthValue::Create(
    double length_value,
    const class ON_UnitSystem& length_unit_system,
    unsigned int locale_id,
    ON_LengthValue::StringFormat string_format
    //,    double clean_format_tolerance
)
{
  const double clean_format_tolerance = 0.0; // == ON_ZERO_TOLERANCE
  ON_LengthValue rc;
  rc.m_string_format = string_format;
  for (;;)
  {
    bool bFraction = false;
    bool bImproperFraction = false;
    bool bClean = false;
    switch (string_format)
    {
    case ON_LengthValue::StringFormat::ExactDecimal:
      break;
    case ON_LengthValue::StringFormat::ExactProperFraction:
      bFraction = true;
      break;
    case ON_LengthValue::StringFormat::ExactImproperFraction:
      bFraction = true;
      bImproperFraction = true;
      break;
    case ON_LengthValue::StringFormat::CleanDecimal:
      bClean = true;
      break;
    case ON_LengthValue::StringFormat::CleanProperFraction:
      bClean = true;
      bFraction = true;
      break;
    case ON_LengthValue::StringFormat::CleanImproperFraction:
      bClean = true;
      bFraction = true;
      bImproperFraction = true;
      break;
    default:
      break;
    }
    if (false == (length_value == length_value))
      break;
    if (ON::LengthUnitSystem::Unset == length_unit_system.UnitSystem())
      break;
    rc.m_length 
      = bClean
      ? ON_CleanNumber(length_value,clean_format_tolerance)
      : length_value;
    rc.m_length_unit_system = length_unit_system;
    const ON_LengthUnitName name = ON_LengthUnitName::Create(locale_id, length_unit_system.UnitSystem(), length_value > 1.0);

    // DO NOT USE A "PRETTY" FORMAT!
    // It is critical that this string scan back to rc.m_length exactly.
    double sign = ON_DBL_QNAN;
    double proper = ON_DBL_QNAN;
    double numerator = ON_DBL_QNAN;
    double denominator = ON_DBL_QNAN;
    if (
      bFraction 
      && ON_IsAnnotationFractionNumber(rc.m_length, bImproperFraction, &sign, &proper, &numerator, &denominator)
      )
    {
      // (proper*denominator + numerator)/denominator is more precise (repeatable)
      // than proper + numerator/denominator
      rc.m_length = sign*(proper*denominator + numerator)/denominator;
      if (proper != 0.0)
      {
        if (name.LengthUnitNameIsNotEmpty())
          rc.m_length_as_string.Format(L"%0.17g-%0.17g/%0.17g %ls", sign*proper, numerator, denominator, name.LengthUnitName());
        else
          rc.m_length_as_string.Format(L"%0.17g-%0.17g/%0.17g", sign*proper, numerator, denominator);
      }
      else
      {
        if (name.LengthUnitNameIsNotEmpty())
          rc.m_length_as_string.Format(L"%0.17g/%0.17g %ls", numerator, denominator, name.LengthUnitName());
        else
          rc.m_length_as_string.Format(L"%0.17g/%0.17g", numerator, denominator);
      }
    }
    else
    {
      double clean_length = ON_DBL_QNAN;
      const ON_wString clean_length_as_string = ON_CleanNumberToString(rc.m_length, 0.0, &clean_length);
      if (bClean || clean_length == rc.m_length)
      {
        rc.m_length = clean_length;
        if (name.LengthUnitNameIsNotEmpty())
          rc.m_length_as_string.Format(L"%ls %ls", static_cast<const wchar_t*>(clean_length_as_string), name.LengthUnitName());
        else
          rc.m_length_as_string = clean_length_as_string;
      }
      else if (name.LengthUnitNameIsNotEmpty())
        rc.m_length_as_string.Format(L"%0.17g %ls", rc.m_length, name.LengthUnitName());
      else
        rc.m_length_as_string.Format(L"%0.17g", rc.m_length);
    }

    rc.m_context_angle_unit_system = ON::AngleUnitSystem::Radians;
    rc.m_context_locale_id = name.LocaleId();

    return rc;
  }
  return ON_LengthValue::Unset;
}

ON_LengthValue ON_LengthValue::Create(
  double length_value,
  const ON::LengthUnitSystem length_unit_system,
  unsigned int locale_id,
  ON_LengthValue::StringFormat string_format
  //,  double clean_format_tolerance
)
{
  return ON_LengthValue::Create(
    length_value,
    ON_UnitSystem(length_unit_system),
    locale_id,
    string_format
    //,    clean_format_tolerance
  );
}

ON_LengthValue ON_LengthValue::Create(
  double length_value,
  const ON_LengthUnitName& length_unit_system,
  ON_LengthValue::StringFormat string_format
  //,  double clean_format_tolerance
)
{
  return ON_LengthValue::Create(
    length_value,
    length_unit_system.LengthUnit(),
    length_unit_system.LocaleId(),
    string_format
  );
}

double ON_LengthValue::Length(
  const ON_UnitSystem& context_unit_system
) const
{
  if ( ON::LengthUnitSystem::None == context_unit_system.UnitSystem())
    return m_length;
  if ( 
    m_length_unit_system.MetersPerUnit(ON_DBL_QNAN) == context_unit_system.MetersPerUnit(ON_DBL_QNAN)
    && ON::LengthUnitSystem::Unset != context_unit_system.UnitSystem() 
    )
    return m_length;
  return m_length*ON::UnitScale(m_length_unit_system, context_unit_system);
}


double ON_LengthValue::Length(
  ON::LengthUnitSystem context_unit_system
) const
{
  if ( ON::LengthUnitSystem::None == context_unit_system)
    return m_length;
  if ( m_length_unit_system.UnitSystem() == context_unit_system && ON::LengthUnitSystem::Unset != context_unit_system)
    return m_length;
  return m_length*ON::UnitScale(m_length_unit_system, context_unit_system);
}

const ON_UnitSystem& ON_LengthValue::LengthUnitSystem() const
{
  return m_length_unit_system;
}

const ON_wString& ON_LengthValue::LengthAsString() const
{
  m_length_as_string.IsValid(true);
  return m_length_as_string;
}

const wchar_t* ON_LengthValue::LengthAsStringPointer() const
{
  m_length_as_string.IsValid(true);
  return static_cast<const wchar_t*>(m_length_as_string);
}

bool ON_LengthValue::IsUnset() const
{
  return IsSet() ? false : true;
}

bool ON_LengthValue::IsSet() const
{
  return (
    m_length_unit_system.UnitSystem() != ON::LengthUnitSystem::Unset
    && (ON_UNSET_VALUE < m_length && m_length < ON_UNSET_POSITIVE_VALUE)
    && m_length_as_string.IsNotEmpty()
    );
}

bool ON_LengthValue::Write(
  class ON_BinaryArchive& archive
) const
{
  const int content_version = 1;
  if (!archive.BeginWrite3dmAnonymousChunk(content_version))
    return false;

  bool rc = false;
  for (;;)
  {
    // content version = 0
    if (!archive.WriteDouble(m_length))
      break;
    if (!m_length_unit_system.Write(archive))
      break;
    if (!archive.WriteInt(static_cast<unsigned int>(m_context_angle_unit_system)))
      break;
    if (!archive.WriteInt(m_context_locale_id))
      break;
    m_length_as_string.IsValid(true);
    if (!archive.WriteString(m_length_as_string))
      break;

    // content version 1 added m_string_format
    const unsigned int u = static_cast<unsigned char>(m_string_format);
    if (!archive.WriteInt(u))
      break;

    rc = true;
    break;
  }

  if (!archive.EndWrite3dmChunk())
    rc = false;
  return rc;
}

bool ON_LengthValue::Read(
  class ON_BinaryArchive& archive
)
{
  *this = ON_LengthValue::Unset;

  int content_version = 0;
  if (!archive.BeginRead3dmAnonymousChunk(&content_version))
    return false;

  bool rc = false;
  for (;;)
  {
    if (!archive.ReadDouble(&m_length))
      break;
    if (!m_length_unit_system.Read(archive))
      break;

    unsigned int context_angle_unit_system_as_unsigned = static_cast<unsigned int>(m_context_angle_unit_system);
    if (!archive.ReadInt(&context_angle_unit_system_as_unsigned))
      break;
    m_context_angle_unit_system = ON::AngleUnitSystemFromUnsigned(context_angle_unit_system_as_unsigned);
    if (ON::AngleUnitSystem::None == m_context_angle_unit_system || ON::AngleUnitSystem::Unset == m_context_angle_unit_system)
      m_context_angle_unit_system = ON::AngleUnitSystem::Radians;
    if (!archive.ReadInt(&m_context_locale_id))
      break;

    if (!archive.ReadString(m_length_as_string))
      break;

    if (content_version >= 1)
    {
      // content version 1 added m_string_format
      unsigned int u = static_cast<unsigned char>(m_string_format);
      if (!archive.ReadInt(&u))
        break;
      m_string_format = ON_LengthValue::LengthStringFormatFromUnsigned(u);
    }

    rc = true;
    break;
  }
  if (!archive.EndRead3dmChunk())
    rc = false;
  return rc;
}



ON_AngleValue ON_AngleValue::CreateFromString(
  ON_ParseSettings parse_settings,
  const wchar_t* string
)
{
  if ( nullptr == string || 0 == string[0] )
    return ON_AngleValue::Unset;

  const wchar_t* string_end = nullptr;
  const ON_AngleValue angle_value = ON_AngleValue::CreateFromSubString(parse_settings, string, -1, &string_end);
  if (nullptr == string_end || !(string < string_end))
  {
    ON_ERROR("Invalid input parameters.");
    return ON_AngleValue::Unset;
  }

  return angle_value;
}

ON_AngleValue ON_AngleValue::CreateFromSubString(
  ON_ParseSettings parse_settings,
  const wchar_t* string,
  int string_count,
  const wchar_t** string_end
  )
{
  // All calls to some version of ON_AngleValue::CreateFrom*String(...) end up here.
  if (nullptr != string_end && &string != string_end)
    *string_end = string;

  if (string_count < -1)
  {
    ON_ERROR("Invalid string_count parameter.");
    return ON_AngleValue::Unset;
  }

  if (nullptr == string || 0 == string_count || 0 == string[0] )
  {
    // empty string fails silently.
    return ON_AngleValue::Unset;
  }
  
  double angle_value = ON_DBL_QNAN;
  ON_ParseSettings parse_results;
  ON::AngleUnitSystem string_angle_unit_system = ON::AngleUnitSystem::Unset;
  const int parse_count = ON_ParseAngleExpression(
    string,
    string_count,
    parse_settings, 
    &angle_value,
    &parse_results,
    &string_angle_unit_system
  );

  if ( parse_count <= 0 
    || (parse_count > string_count && string_count >= 0)
    || false == (angle_value == angle_value) 
    ) 
  {
    // non-empty string failure generates debugger error.
    ON_ERROR("Input string parameter is not valid.");
    return ON_AngleValue::Unset;
  }

  ON_AngleValue rc;

  rc.m_angle = angle_value;

  if (ON::AngleUnitSystem::Unset != string_angle_unit_system && ON::AngleUnitSystem::None != string_angle_unit_system)
    rc.m_angle_unit_system = string_angle_unit_system;
  else
    rc.m_angle_unit_system = parse_settings.DefaultAngleUnitSystem();

  rc.m_context_length_unit_system = parse_settings.ContextLengthUnitSystem();
  rc.m_context_locale_id = parse_settings.ContextLocaleId();

  rc.m_angle_as_string = ON_wString(string, parse_count);
  rc.m_angle_as_string.TrimLeftAndRight();
  
  if (nullptr != string_end)
    *string_end = string + parse_count;

  return rc;
}


ON_AngleValue ON_AngleValue::Create(
  double angle_value,
  const class ON_AngleUnitName& angle_unit_system,
  ON_AngleValue::StringFormat string_format
)
{
  return ON_AngleValue::Create(
    angle_value,
    angle_unit_system.AngleUnit(),
    angle_unit_system.LocaleId(),
    string_format
  );
}


ON_AngleValue ON_AngleValue::Create(
  double angle_value,
  ON::AngleUnitSystem angle_unit_system,
  unsigned int locale_id,
  ON_AngleValue::StringFormat string_format
)
{
  ON_AngleValue rc;
  for (;;)
  {
    bool bFraction = false;
    bool bClean = false;
    switch (string_format)
    {
    case ON_AngleValue::StringFormat::ExactDecimal:
      break;
    case ON_AngleValue::StringFormat::ExactFraction:
      bFraction = true;
      break;
    case ON_AngleValue::StringFormat::CleanDecimal:
      bClean = true;
      break;
    case ON_AngleValue::StringFormat::CleanFraction:
      bClean = true;
      bFraction = true;
      break;
    default:
      string_format = ON_AngleValue::StringFormat::ExactDecimal;
      break;
    }

    if (false == (angle_value == angle_value))
      break;
    if (ON::AngleUnitSystem::Unset == angle_unit_system)
      break;
    rc.m_angle = angle_value;
    rc.m_angle_unit_system = angle_unit_system;
    const ON_AngleUnitName name = ON_AngleUnitName::Create(locale_id, angle_unit_system, angle_value > 1.0);

    // DO NOT USE A "PRETTY" FORMAT!
    // It is critical that this string scan back to rc.m_angle exactly.
    double sign = ON_DBL_QNAN;
    double proper = ON_DBL_QNAN;
    double numerator = ON_DBL_QNAN;
    double denominator = ON_DBL_QNAN;
    if (
      bFraction 
      && ON_IsAnnotationFractionNumber(rc.m_angle, true, &sign, &proper, &numerator, &denominator)
      )
    {
      rc.m_angle = sign*numerator/denominator;
      if (name.AngleUnitNameIsNotEmpty() )
        rc.m_angle_as_string.Format(L"%0.17g/%0.17g %ls", numerator, denominator, name.AngleUnitName());
      else
        rc.m_angle_as_string.Format(L"%0.17g/%0.17g", numerator, denominator);
    }
    else
    {
      if (name.AngleUnitNameIsNotEmpty())
        rc.m_angle_as_string.Format(L"%0.17g %ls", rc.m_angle, name.AngleUnitName());
      else
        rc.m_angle_as_string.Format(L"%0.17g", rc.m_angle);
    }

    rc.m_context_length_unit_system = ON::LengthUnitSystem::None;
    rc.m_context_locale_id = name.LocaleId();

    return rc;
  }
  return ON_AngleValue::Unset;
}

double ON_AngleValue::Angle(
  ON::AngleUnitSystem context_unit_system
) const
{
  if ( ON::AngleUnitSystem::None == context_unit_system)
    return m_angle;
  if ( m_angle_unit_system == context_unit_system )
    return m_angle;
  return m_angle*ON::AngleUnitScale(m_angle_unit_system, context_unit_system);
}


ON::AngleUnitSystem ON_AngleValue::AngleUnitSystem() const
{
  return m_angle_unit_system;
}

const ON_wString& ON_AngleValue::AngleAsString() const
{
  return m_angle_as_string;
}

const wchar_t* ON_AngleValue::AngleAsStringPointer() const
{
  return static_cast<const wchar_t*>(m_angle_as_string);
}

bool ON_AngleValue::IsUnset() const
{
  return IsSet() ? false : true;
}

bool ON_AngleValue::IsSet() const
{
  return (
    m_angle_unit_system != ON::AngleUnitSystem::Unset
    && (ON_UNSET_VALUE < m_angle && m_angle < ON_UNSET_POSITIVE_VALUE)
    && m_angle_as_string.IsNotEmpty()
    );
}

bool ON_AngleValue::Write(
  class ON_BinaryArchive& archive
) const
{
  const int content_version = 1;
  if (!archive.BeginWrite3dmAnonymousChunk(content_version))
    return false;

  bool rc = false;
  for (;;)
  {
    if (!archive.WriteDouble(m_angle))
      break;
    if (!archive.WriteInt(static_cast<unsigned int>(m_angle_unit_system)))
      break;
    if (!archive.WriteInt(static_cast<unsigned int>(m_context_length_unit_system)))
      break;
    if (!archive.WriteInt(m_context_locale_id))
      break;
    if (!archive.WriteString(m_angle_as_string))
      break;

    // content version 1 added m_string_format
    const unsigned int u = static_cast<unsigned char>(m_string_format);
    if (!archive.WriteInt(u))
      break;

    rc = true;
    break;
  }
  if (!archive.EndWrite3dmChunk())
    rc = false;
  return rc;
}

bool ON_AngleValue::Read(
  class ON_BinaryArchive& archive
)
{
  *this = ON_AngleValue::Unset;
  int content_version = 0;
  if (!archive.BeginRead3dmAnonymousChunk(&content_version))
    return false;

  bool rc = false;
  for (;;)
  {
    if (!archive.ReadDouble(&m_angle))
      break;
    unsigned int angle_unit_system_as_unsigned = static_cast<unsigned int>(m_angle_unit_system);
    if (!archive.ReadInt(&angle_unit_system_as_unsigned))
      break;
    m_angle_unit_system = ON::AngleUnitSystemFromUnsigned(angle_unit_system_as_unsigned);

    unsigned int context_length_unit_system_as_unsigned = static_cast<unsigned int>(m_context_length_unit_system);
    if (!archive.ReadInt(&context_length_unit_system_as_unsigned))
      break;
    m_context_length_unit_system = ON::LengthUnitSystemFromUnsigned(context_length_unit_system_as_unsigned);
    if (ON::LengthUnitSystem::Unset == m_context_length_unit_system)
      m_context_length_unit_system = ON::LengthUnitSystem::None;
    if (!archive.ReadInt(&m_context_locale_id))
      break;

    if (!archive.ReadString(m_angle_as_string))
      break;

    if (content_version >= 1)
    {
      // content version 1 added m_string_format
      unsigned int u = static_cast<unsigned char>(m_string_format);
      if (!archive.ReadInt(&u))
        break;
      m_string_format = ON_AngleValue::AngleStringFormatFromUnsigned(u);
    }


    rc = true;
    break;
  }
  if (!archive.EndRead3dmChunk())
    rc = false;
  return rc;
}

ON_ScaleValue ON_ScaleValue::CreateFromString(
  ON_ParseSettings parse_settings,
  const wchar_t* string
  )
{
  if ( nullptr == string || 0 == string[0] )
    return ON_ScaleValue::Unset;

  const wchar_t* string_end = nullptr;
  const ON_ScaleValue scale_value = ON_ScaleValue::CreateFromSubString(parse_settings, string, -1, &string_end);
  if (nullptr == string_end || !(string < string_end))
  {
    ON_ERROR("Invalid input parameters.");
    return ON_ScaleValue::Unset;
  }

  return scale_value;
}

ON_ScaleValue ON_ScaleValue::CreateFromSubString(
  ON_ParseSettings parse_settings,
  const wchar_t* string,
  int string_count,
  const wchar_t** string_end
)
{
  // All calls to some version of ON_AngleValue::CreateFrom*String(...) end up here.
  if (nullptr != string_end && &string != string_end)
    *string_end = string;

  if (string_count < -1)
  {
    ON_ERROR("Invalid string_count parameter.");
    return ON_ScaleValue::Unset;
  }

  if (nullptr == string || 0 == string_count || 0 == string[0] )
  {
    // empty string fails silently.
    return ON_ScaleValue::Unset;
  }

  const wchar_t* left_side_string_end = nullptr;
  ON_ParseSettings left_side_parse_settings = parse_settings;

  const ON_LengthValue left_side = ON_LengthValue::CreateFromSubString( left_side_parse_settings, string, string_count, &left_side_string_end);

  if (left_side.IsUnset() || nullptr == left_side_string_end || !(string < left_side_string_end))
    return ON_ScaleValue::Unset;

  const size_t left_side_count = left_side_string_end - string;
  if ( -1 != string_count )
  {
    string_count -= (int)left_side_count;
    // 0 = string_count may be ok - conditions checked later.
    if (string_count < 0)
    {
      ON_ERROR("Invalid input parameters.");
      return ON_ScaleValue::Unset;
    }
  }

  const double left_side_length = left_side.Length(ON::LengthUnitSystem::None);
  const ON::LengthUnitSystem left_side_unit_system = left_side.LengthUnitSystem().UnitSystem();

  // look for equal, colon or fraction;
  ON_ScaleValue::ScaleStringFormat format_preference = ON_ScaleValue::ScaleStringFormat::Unset;
  const wchar_t* separator_string = left_side_string_end;
  const wchar_t* separator_string_end = separator_string;
  for (int i = 0; -1 == string_count || i < string_count; i++)
  {
    if (parse_settings.IsInteriorWhiteSpace(separator_string[i]))
      continue;

    switch (separator_string[i])
    {
    case ':':
      format_preference = ON_ScaleValue::ScaleStringFormat::RatioFormat;
      break;

    case '=':
      format_preference = ON_ScaleValue::ScaleStringFormat::EquationFormat;
      break;

    case '/':
      format_preference = ON_ScaleValue::ScaleStringFormat::FractionFormat;
      break;
    }

    if (ON_ScaleValue::ScaleStringFormat::Unset != format_preference)
    {
      for (i++; -1 == string_count || i < string_count; i++)
      {
        if (false == parse_settings.IsInteriorWhiteSpace(separator_string[i]))
          break;
      }
    }
    separator_string_end = separator_string + i;
    break;
  }

  const size_t separator_count = separator_string_end - separator_string;
  if ( -1 != string_count )
  {
    string_count -= (int)separator_count;
    if (string_count <= 0)
    {
      ON_ERROR("Invalid input parameters.");
      return ON_ScaleValue::Unset;
    }
  }

  const wchar_t* right_side_string = separator_string_end;
  const wchar_t* right_side_string_end = right_side_string;
  ON_LengthValue right_side;

  if (ON_ScaleValue::ScaleStringFormat::Unset == format_preference)
  {
    // A single value scanned.
    if (ON::LengthUnitSystem::None != left_side_unit_system)
      return ON_ScaleValue::Unset;
    right_side = ON_LengthValue::Create(1.0, ON::LengthUnitSystem::None, 0, ON_LengthValue::StringFormat::ExactDecimal);

    format_preference
      = (left_side_length == floor(left_side_length) && ON::LengthUnitSystem::None == left_side_unit_system)
        ? ON_ScaleValue::ScaleStringFormat::RatioFormat
        : ON_ScaleValue::ScaleStringFormat::EquationFormat;
  }
  else
  {
    // parse right side
    ON_ParseSettings right_side_parse_settings = parse_settings;
    right_side_parse_settings.SetParseLeadingWhiteSpace(false);
    right_side = ON_LengthValue::CreateFromSubString( right_side_parse_settings, right_side_string, string_count, &right_side_string_end );
  }

  if (right_side.IsUnset())
  {
    ON_ERROR("Invalid input parameters.");
    return ON_ScaleValue::Unset;
  }

  ON_ScaleValue scale_value = ON_ScaleValue::Create(
    left_side,
    right_side,
    format_preference
  );

  if (scale_value.IsUnset() || !(right_side_string_end > string))
  {
    ON_ERROR("Invalid input parameters.");
    return ON_ScaleValue::Unset;
  }

  scale_value.m_scale_as_string = ON_wString(string, (int)(right_side_string_end - string));
  scale_value.m_scale_as_string.TrimLeftAndRight();

  if (nullptr != string_end)
    *string_end = right_side_string_end;

  return scale_value;
}

static double ON_InternalDefuzz( double rel_tol, double x)
{
  if (!(rel_tol >= 4.0*ON_EPSILON))
    rel_tol = 4.0*ON_EPSILON;
  const double s = 256.0;
  const double a = s*fabs(x);
  if (!(a > 255.0))
    return x;

  double ia = floor(a);
  double fa = a - ia;
  if (fa > 0.5)
    ia += 1.0;
  const double y
    = (fabs(a - ia) <= a*rel_tol)
    ? (((x < 0.0) ? -ia : ia)/s)
    : x;

  return y;
}

static double ON_InternalQuotient(
  double rel_tol,
  double numerator,
  double denominator
)
{
  if (numerator == numerator && denominator != 0.0)
  {
    const double r = ON_InternalDefuzz(rel_tol, numerator / denominator);
    const double s = (numerator != 0.0) ? ON_InternalDefuzz(rel_tol, denominator / numerator ) : 0.0;
    return
      (s >= 2.0 && s == floor(s))
      ? (1.0 / s)
      : r;
  }
  ON_ERROR("Invalid input.");
  return ON_DBL_QNAN;
}

static bool ON_Internal_RemoveCommonFactors(const double rel_zero_tol, const double factor, double& x, double& y)
{
  if (false == (x > 0.0 && y > 0.0 && factor > 0.0 && rel_zero_tol >= 0.0 && rel_zero_tol < 0.01))
  {
    ON_ERROR("Invalid input parameters.");
    return false;
  }
  if (1.0 == factor)
    return true; // nothing to do

  if (!(x < 1.0 / ON_EPSILON && y < 1.0 / ON_EPSILON))
  {
    // x or y is too big for this code to work with IEEE double arithmetic.
    return false;
  }

  const double fat_eps = 4.0*ON_EPSILON;
  const double factor_tol = (rel_zero_tol > fat_eps) ? rel_zero_tol : fat_eps;
  if (!(factor > x*factor_tol && factor > y*factor_tol))
  {
    // factor is too small for the ON_ScaleValue context where this
    // function is designed to be used.
    return false;
  }

  bool rc = false;
  for (;;)
  {
    const double s = ON_InternalQuotient(factor_tol,x,factor);
    if (!(s == floor(s)))
      break;


    const double t = ON_InternalQuotient(factor_tol,y,factor);
    if (!(t == floor(t)))
      break;
    
    if (factor >= 1.0)
    {
      if (!(s < x && t < y))
        break;
    }

    rc = true;
    x = s;
    y = t;

    if ( !(factor >= 2.0 && x >= factor*(1.0-fat_eps) && y >= factor*(1.0-fat_eps)) )
      break;
  }

  return rc;
}

static bool ON_Internal_SimplifyRatio(double& x, double& y)
{
  // returns true if the output values of x and y are both integers.
  const double rel_zero_tol = 1.0e-14;
  if (!(x > 0.0 && y > 0.0))
    return false;

  if (fabs(x / y - 1.0) <= rel_zero_tol || fabs(y / x - 1.0) <= rel_zero_tol)
  {
    x = 1.0;
    y = 1.0;
    return true;
  }

  if ( x < y )
    ON_Internal_RemoveCommonFactors(rel_zero_tol, x, x, y);
  else if ( y < x )
    ON_Internal_RemoveCommonFactors(rel_zero_tol, y, y, x);

  const double factors[] = { 2.0, 3.0, 5.0 };
  for ( size_t i = 0; i < sizeof(factors)/sizeof(factors[0]); i++ )
    ON_Internal_RemoveCommonFactors(rel_zero_tol, factors[i], y, x);

  return (x == floor(x) && y == floor(y));
}
  
ON_ScaleValue ON_ScaleValue::Create(
  const class ON_LengthValue& left_side_length,
  const class ON_LengthValue& right_side_length,
  ON_ScaleValue::ScaleStringFormat string_format_preference
)
{
  ON_ScaleValue scale_value = ON_ScaleValue::Unset;

  scale_value.m_left_length = left_side_length;
  scale_value.m_right_length = right_side_length;
  scale_value.m_string_format_preference = string_format_preference;

  if (scale_value.m_left_length.IsUnset() || scale_value.m_right_length.IsUnset())
    return scale_value;

  ON::LengthUnitSystem left_length_unit_system = scale_value.m_left_length.LengthUnitSystem().UnitSystem();
  ON::LengthUnitSystem right_length_unit_system = scale_value.m_right_length.LengthUnitSystem().UnitSystem();
  const double left_length = scale_value.m_left_length.Length(left_length_unit_system);
  const double right_length = scale_value.m_right_length.Length(right_length_unit_system);
  if (false == (left_length > 0.0 && right_length > 0.0))
  {
    // one or both of left_length and right_length is a NAN or negative
    ON_ERROR("Invalid input");
    return scale_value;
  }

  // Dale Lear http://mcneel.myjetbrains.com/youtrack/issue/RH-34709
  // Turns out that stripping unit system information when one side is None
  // was a bad idea. After using ON_ScaleValue in the ON_DimStyle
  // class, preserving the unit systems works better when one
  // is None.
  ////if (ON::LengthUnitSystem::None == left_length_unit_system
  ////  && ON::LengthUnitSystem::None != right_length_unit_system
  ////  )
  ////{
  ////  // remove units from right side 
  ////  scale_value.m_right_length = scale_value.m_right_length.RemoveUnitSystem();
  ////  right_length_unit_system = ON::LengthUnitSystem::None;
  ////}

  ////if (ON::LengthUnitSystem::None != left_length_unit_system
  ////  && ON::LengthUnitSystem::None == right_length_unit_system
  ////  )
  ////{
  ////  // remove units from left side 
  ////  scale_value.m_left_length = scale_value.m_left_length.RemoveUnitSystem();
  ////  left_length_unit_system = ON::LengthUnitSystem::None;
  ////}

  const double left_to_right_scale = ON::UnitScale(scale_value.m_left_length.LengthUnitSystem(), scale_value.m_right_length.LengthUnitSystem());
  const double right_to_left_scale = ON::UnitScale(scale_value.m_right_length.LengthUnitSystem(), scale_value.m_left_length.LengthUnitSystem());

  if (false == (left_to_right_scale > 0.0 && right_to_left_scale > 0.0 && 1.0 == ON_InternalDefuzz(1.0e-14,left_to_right_scale*right_to_left_scale)) )
  {
    // one or both of left_to_right_scale and right_to_left_scale is a NAN or not set correctly
    ON_ERROR("Invalid input");
    ON_InternalDefuzz(1.0e-14, left_to_right_scale*right_to_left_scale);
    return scale_value;
  }
  
  double x = left_length;
  double y = right_length;
  if (left_to_right_scale > right_to_left_scale)
    x *= left_to_right_scale;
  else if ( right_to_left_scale > left_to_right_scale)
    y *= right_to_left_scale;

  if (false == (x > 0.0 && y > 0.0))
  {
    // one or both of x and y is a NAN or not set correctly
    ON_ERROR("Invalid input");
    return scale_value;
  }

  if (!ON_Internal_SimplifyRatio(x, y))
    string_format_preference = ON_ScaleValue::ScaleStringFormat::EquationFormat;

  scale_value.m_left_to_right_scale = ON_InternalQuotient(0.0,x,y);
  scale_value.m_right_to_left_scale = ON_InternalQuotient(0.0,y,x);

  if (scale_value.m_left_to_right_scale >= 2.0 && floor(scale_value.m_left_to_right_scale) == scale_value.m_left_to_right_scale)
  {
    scale_value.m_right_to_left_scale = 1.0 / scale_value.m_left_to_right_scale;
  }
  else if (scale_value.m_right_to_left_scale >= 2.0 && floor(scale_value.m_right_to_left_scale) == scale_value.m_right_to_left_scale)
  {
    scale_value.m_left_to_right_scale = 1.0 / scale_value.m_right_to_left_scale;
  }

  switch (string_format_preference)
  {
  case ON_ScaleValue::ScaleStringFormat::RatioFormat:
    // Do NOT dumb down the %.17g in the format string.
    // If you don't like the format, then make your own string and call
    // ON_ScaleValue::CreateFromString(). It is critical that 
    // the values in the formatted string exactly match the double values.
    scale_value.m_scale_as_string.Format(L"%.17g:%.17g", x, y);
    break;
  case ON_ScaleValue::ScaleStringFormat::FractionFormat:
    // Do NOT dumb down the %.17g in the format string.
    // If you don't like the format, then make your own string and call
    // ON_ScaleValue::CreateFromString(). It is critical that 
    // the values in the formatted string exactly match the double values.
    scale_value.m_scale_as_string.Format(L"%.17g/%.17g", x, y);
    break;
  case ON_ScaleValue::ScaleStringFormat::EquationFormat:
    // no break here
  default:
    scale_value.m_scale_as_string.Format(L"%ls = %ls",
      scale_value.m_left_length.LengthAsStringPointer(), 
      scale_value.m_right_length.LengthAsStringPointer()
    );
    break;
  }

  scale_value.m_string_format_preference = string_format_preference;


  return scale_value;
}

double ON_ScaleValue::LeftToRightScale() const
{
  return m_left_to_right_scale;
}

double ON_ScaleValue::RightToLeftScale() const
{
  return m_right_to_left_scale;
}

const class ON_LengthValue& ON_ScaleValue::LeftLengthValue() const
{
  return m_left_length;
}

const class ON_LengthValue& ON_ScaleValue::RightLengthValue() const
{
  return m_right_length;
}

const ON_wString& ON_ScaleValue::ScaleAsString() const
{
  m_scale_as_string.IsValid(true);
  return m_scale_as_string;
}

const wchar_t* ON_ScaleValue::ScaleAsStringPointer() const
{
  m_scale_as_string.IsValid(true);
  return static_cast<const wchar_t*>(m_scale_as_string);
}

bool ON_ScaleValue::IsUnset() const
{
  return IsSet() ? false : true;
}

bool ON_ScaleValue::IsSet() const
{
  return (
    m_left_length.IsSet()
    && m_right_length.IsSet()
    && (ON_UNSET_VALUE < m_left_to_right_scale && m_left_to_right_scale < ON_UNSET_POSITIVE_VALUE)
    && (ON_UNSET_VALUE < m_right_to_left_scale && m_right_to_left_scale < ON_UNSET_POSITIVE_VALUE)
    && m_scale_as_string.IsNotEmpty()
    );
}

bool ON_ScaleValue::Write(
  class ON_BinaryArchive& archive
) const
{
  const int content_version = 1;
  if (!archive.BeginWrite3dmAnonymousChunk(content_version))
    return false;

  bool rc = false;
  for (;;)
  {
    // content_version = 0
    if (!archive.WriteDouble(m_left_to_right_scale))
      break;
    if (!archive.WriteDouble(m_right_to_left_scale))
      break;
    if (!archive.WriteInt(m_context_locale_id))
      break;
    if (!archive.WriteInt(static_cast<unsigned int>(m_context_length_unit_system)))
      break;
    if (!archive.WriteInt(static_cast<unsigned int>(m_context_angle_unit_system)))
      break;
    m_scale_as_string.IsValid(true);
    if (!archive.WriteString(m_scale_as_string))
      break;
    if (!m_left_length.Write(archive))
      break;
    if (!m_right_length.Write(archive))
      break;

    // content version 1 added m_string_format_preference
    unsigned int u = static_cast<unsigned char>(m_string_format_preference);
    if (!archive.WriteInt(u))
      break;

    rc = true;
    break;
  }

  if (!archive.EndWrite3dmChunk())
    rc = false;
  return rc;
}

ON_ScaleValue::ScaleStringFormat ON_ScaleValue::ScaleStringFormatFromUnsigned(
  unsigned int scale_string_format_as_unsigned
)
{
  switch (scale_string_format_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_ScaleValue::ScaleStringFormat::None);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_ScaleValue::ScaleStringFormat::RatioFormat);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_ScaleValue::ScaleStringFormat::EquationFormat);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_ScaleValue::ScaleStringFormat::FractionFormat);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_ScaleValue::ScaleStringFormat::Unset);
  }
  ON_ERROR("Invalid scale_string_format_as_unsigned value.");
  return (ON_ScaleValue::Unset.m_string_format_preference);
}

bool ON_ScaleValue::Read(
  class ON_BinaryArchive& archive
)
{
  *this = ON_ScaleValue::Unset;

  int content_version = 0;
  if (!archive.BeginRead3dmAnonymousChunk(&content_version))
    return false;

  bool rc = false;
  for (;;)
  {
    if (!archive.ReadDouble(&m_left_to_right_scale))
      break;
    if (!archive.ReadDouble(&m_right_to_left_scale))
      break;
    if (!archive.ReadInt(&m_context_locale_id))
      break;

    unsigned int u;

    u = static_cast<unsigned int>(m_context_length_unit_system);
    if (!archive.ReadInt(&u))
      break;
    m_context_length_unit_system = ON::LengthUnitSystemFromUnsigned(u);

    u = static_cast<unsigned int>(m_context_angle_unit_system);
    if (!archive.ReadInt(&u))
      break;
    m_context_angle_unit_system = ON::AngleUnitSystemFromUnsigned(u);

    if (!archive.ReadString(m_scale_as_string))
      break;

    if (!m_left_length.Read(archive))
      break;
    if (!m_right_length.Read(archive))
      break;

    if (content_version >= 1)
    {
      // content version 1 added m_string_format_preference
      u = static_cast<unsigned char>(m_string_format_preference);
      if (!archive.ReadInt(&u))
        break;
      m_string_format_preference = ON_ScaleValue::ScaleStringFormatFromUnsigned(u);
    }

    rc = true;
    break;
  }

  if (!archive.EndRead3dmChunk())
    rc = false;
  return rc;
}

ON_LengthValue::StringFormat ON_LengthValue::LengthStringFormat() const
{
  return m_string_format;
}

unsigned int ON_LengthValue::ContextLocaleId() const
{
  return m_context_locale_id;
}

ON::AngleUnitSystem ON_LengthValue::ContextAngleUnitSystem() const
{
  return m_context_angle_unit_system;
}

const ON_ParseSettings ON_LengthValue::LengthStringParseSettings() const
{
  return ON_ParseSettings(m_length_unit_system.UnitSystem(), m_context_angle_unit_system, m_context_locale_id);
}

ON_ParseSettings const ON_AngleValue::AngleStringParseSettings() const
{
  return ON_ParseSettings(m_context_length_unit_system, m_angle_unit_system, m_context_locale_id);
}

const ON_ParseSettings ON_ScaleValue::ScaleStringParseSettings() const
{
  return ON_ParseSettings(m_context_length_unit_system, m_context_angle_unit_system, m_context_locale_id);
}

void ON_ScaleValue::SwapLeftAndRight()
{
  double x = m_left_to_right_scale;
  m_left_to_right_scale = m_right_to_left_scale;
  m_right_to_left_scale = x;

  ON_LengthValue t = m_left_length;
  m_left_length = m_right_length;
  m_right_length = t;

  // TODO: properly reverse string
  m_scale_as_string = ON_ScaleValue::Create(m_left_length,m_right_length,ON_ScaleValue::ScaleStringFormat::None).ScaleAsString();
}


const ON_SHA1_Hash ON_ScaleValue::ContentHash() const
{
  ON_SHA1 sha1;
  sha1.AccumulateDouble(m_left_to_right_scale);
  sha1.AccumulateDouble(m_right_to_left_scale);
  sha1.AccumulateUnsigned32(m_context_locale_id);
  sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_context_length_unit_system));
  sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_context_angle_unit_system));
  sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_string_format_preference));
  m_scale_as_string.IsValid(true);
  sha1.AccumulateString(m_scale_as_string);
  ON_SHA1_Hash h = m_left_length.ContentHash();
  sha1.AccumulateSubHash(h);
  h = m_right_length.ContentHash();
  sha1.AccumulateSubHash(h);
  return sha1.Hash();
}

int ON_ScaleValue::Compare(
  const ON_ScaleValue& lhs,
  const ON_ScaleValue& rhs
)
{
  double x = lhs.RightToLeftScale();
  double y = rhs.RightToLeftScale();
  if (x < y)
    return -1;
  if (x > y)
    return 1;
  return ON_SHA1_Hash::Compare(lhs.ContentHash(), rhs.ContentHash());
}

const ON_SHA1_Hash ON_LengthValue::ContentHash() const
{
  ON_SHA1 sha1;
  sha1.AccumulateUnsigned32(m_context_locale_id);
  sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_context_angle_unit_system));
  sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_string_format));
  sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_length_unit_system.UnitSystem()));
  m_length_as_string.IsValid(true);
  sha1.AccumulateString(m_length_as_string);
  return sha1.Hash();
}

int ON_LengthValue::Compare(
  const ON_LengthValue& lhs,
  const ON_LengthValue& rhs
)
{
  if (lhs.m_length < rhs.m_length)
    return -1;
  if (lhs.m_length > rhs.m_length)
    return 1;
  return ON_SHA1_Hash::Compare(lhs.ContentHash(), rhs.ContentHash());
}
