
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

#pragma region DistanceFormat

void ON_NumberFormatter::Fraction(double value_in, int& wholenumber, int& numerator, int& denominator, int precision)
{
  int sign = 1;
  if (0 > value_in)
  {
    value_in = -value_in;
    sign = -1;
  }
  denominator = 1 << precision;
  double value = double(int(value_in * denominator + 0.5)) / double(denominator);
  wholenumber = int(floor(value));
  numerator = int((value - wholenumber) * double(denominator));
  while ((numerator % 2) == 0 && (numerator != 0))
  {
    numerator /= 2;
    denominator /= 2;
  }
  wholenumber *= sign;
}

double ON_NumberFormatter::RoundOff(double n, double r)
{
  if (0.0 == r)
    return n;

  if (0.0 > r)
    r = -r;

  if (2.0 * ON_ZERO_TOLERANCE < r)
  {
    double d = n;
    double sign = 1.0;
    if (d < 0.0)
    {
      sign = -1.0;
      d = -d;
    }
    // Increase input by 1/2 of round-off
    double k = d + (r / 2.0);
    double m = fmod(k, r);
    if (m == m)  // fmod can return NaN
    {
      n = k - m;
      n *= sign;
    }
  }
  return n;
}

void ON_NumberFormatter::SuppressZeros(
  ON_wString& dist,
  ON_DimStyle::suppress_zero sz)
{
  switch (sz)
  {
  default:
  case ON_DimStyle::suppress_zero::None:
    break;
  case ON_DimStyle::suppress_zero::SuppressLeading:
    if (1 < dist.Length() && L'0' == dist[0])
      dist = dist.Right(dist.Length() - 1);
    break;
  case ON_DimStyle::suppress_zero::SuppressLeadingAndTrailing:
  case ON_DimStyle::suppress_zero::SuppressTrailing:
  {
    int zero = dist.ReverseFind(L"0");
    int dot = dist.ReverseFind(L".");
    if (dot > 0 && zero > dot)
    {
      dist.TrimRight(L"0");
      dist.TrimRight(L".");
    }
    if (ON_DimStyle::suppress_zero::SuppressLeadingAndTrailing == sz 
       && 1 < dist.Length() && L'0' == dist[0])
      dist = dist.Right(dist.Length() - 1);
  }
    break;
  case ON_DimStyle::suppress_zero::SuppressZeroFeet:
    if (dist.Left(3).EqualOrdinal(L"0\'-", true))
      dist = dist.Right(dist.Length() - 3);
    break;
  case ON_DimStyle::suppress_zero::SuppressZeroFeetAndZeroInches:
    if (dist.Left(3).EqualOrdinal(L"0\'-", true))
      dist = dist.Right(dist.Length() - 3);
  case ON_DimStyle::suppress_zero::SuppressZeroInches:
    if (dist.Right(3).EqualOrdinal(L"-0\"", true))
      dist = dist.Left(dist.Length() - 3);
    break;
  }
}


// bFormatIsAccurate sets numeric display to pretty or accurate.
bool ON_NumberFormatter::bFormatIsAccurate = false;


bool ON_NumberFormatter::FormatNumber(
  double inputdistance,
  ON_DimStyle::OBSOLETE_length_format output_lengthformat,
  double round_off,
  int precision,
  ON_DimStyle::suppress_zero zero_suppress,
  bool bracket_fractions,
  ON_wString& output)
{
  const int max_string_length = 30; // maximum number of characters before %g is used

  if (!ON_IsValid(inputdistance))
  {
    if (ON_UNSET_VALUE == inputdistance)
      output = "unset number";
    else
      output = "invalid number";
    return false;
  }

  if (bFormatIsAccurate)
  {
    output.Format(L"%.17g", inputdistance);
    return true;
  }

  if (0 > precision)
    precision = 0;

  double distance = inputdistance;

  bool is_negative = false;
  if (distance < 0.0)
  {
    is_negative = true;
    distance = -distance;
    output += L'-';
  }

  distance = RoundOff(distance, round_off);

  ON_wString sFormat, sFormat2;
  switch (output_lengthformat)
  {
  default:
  case(ON_DimStyle::OBSOLETE_length_format::Decimal):
  {
    if (precision >= 1 && precision < 10)
    {
      // 7 July 2006 Lowell and Dale L. (From old RhFormatNumber())
      // number like .1495 end up being  .149499999999999999999999999
      // and get rounded to .149 instead of .150.
      // By adding a bit or two at the end we hide this problem.  Since precision < 10,
      // we are several decimal places away from modifying anything that matters.
      // (Note: input * ON_EPSILON didn't work)
      double e = fabs(distance)*1.0e-12;
      distance += e;
    }
    sFormat2.Format(L"%%.%df", precision);
    sFormat.Format(sFormat2, distance);

    // Look for garbage in Format result
    if (sFormat.Length() > max_string_length)
      sFormat = ON_wString::FromNumber(distance);

    ON_NumberFormatter::SuppressZeros(sFormat, zero_suppress);
    break;
  }

  case(ON_DimStyle::OBSOLETE_length_format::Fractional):
  {
    int numerator = 0;
    int denominator = 1 << precision;
    double decimal, wholenumber;

    decimal = modf(distance, &wholenumber);

    // check that fractional part is more than 1/2 of denominator
    // otherwise there's no fraction to print
    decimal *= denominator;
    if (decimal > 0.5)
    {
      decimal += .5;
      numerator = (int)floor(decimal);
      if (numerator != 0)
      {
        if (numerator == denominator)
        {
          numerator = 0;
          wholenumber++;
        }
        else
        {
          //finds lowest form of fraction if divisor is even
          while ((numerator % 2 == 0) && (denominator % 2 == 0))
          {
            numerator /= 2;
            denominator /= 2;
          }
        }
      }

      if (0 == wholenumber && 0 == numerator)
        sFormat.Format(L"0");
      else
      {
        if (0 != wholenumber)
        {
          if (0 != numerator)
            // RH-71619, removed space
            //sFormat.Format(L"%d ", (int)wholenumber);
            sFormat.Format(L"%d", (int)wholenumber);
          else
            sFormat.Format(L"%d", (int)wholenumber);
        }

        if (0 != numerator)
        {
          // RH-80143, no spaces for bracketed (stacked) fractions,
          // a single space for normal fractions.
          if (bracket_fractions)
            sFormat2.Format(L"[[%d/%d]]", numerator, denominator);
          else
            sFormat2.Format(L" %d/%d", numerator, denominator);
          sFormat += sFormat2;
        }
      }
    }
    else
    {
      sFormat.Format(L"%d", (int)wholenumber);
    }
    if (sFormat.Length() > max_string_length)
    {
      sFormat = ON_wString::FromNumber(distance);
    }
    break;
  }

  case(ON_DimStyle::OBSOLETE_length_format::FeetInches):
  {
    // Units for distance have to be feet here
    int numerator = 0;
    int denominator = 1 << precision;
    double decfeet = 0.0;
    double decinches = modf(distance, &decfeet);
    double decfrac = modf(decinches * 12.0, &decinches);
    int wholeinches = (int)decinches;
    int wholefeet = (int)decfeet;

    // decimal is the fractional remainder to make a fraction of an inch
    decfrac *= denominator;
    if (decfrac > 0.5)
    {
      decfrac += .5;
      numerator = (int)floor(decfrac);

      if (0 != numerator)
      {
        while ((numerator % 2 == 0) && (denominator % 2 == 0)) // reduce fraction
        {
          numerator /= 2;
          denominator /= 2;
        }
      }
      if (0 != numerator && numerator == denominator)
      {
        numerator = 0;
        wholeinches++;
      }
      if (wholeinches >= 12)
      {
        wholeinches = 0;
        wholefeet++;
      }
    }

    ON_wString sInches;
    bool include_feet = (0 != wholefeet ||
      (ON_DimStyle::suppress_zero::SuppressZeroFeet != zero_suppress &&
        ON_DimStyle::suppress_zero::SuppressZeroFeetAndZeroInches != zero_suppress));

    bool include_inches = (0 != wholeinches || 0 != numerator ||
      (ON_DimStyle::suppress_zero::SuppressZeroInches != zero_suppress &&
        ON_DimStyle::suppress_zero::SuppressZeroFeetAndZeroInches != zero_suppress));

    if (include_feet)
    {
      sFormat.Format(L"%d\'", wholefeet);
      if (include_inches)
        sFormat += L'-';
    }
    if (include_inches)
    {
      if (0 != numerator)
      {
        if (wholeinches > 0 || include_feet)
        {
          if (bracket_fractions)
            // RH-71619, removed space
            //sInches.Format(L"%d [[%d/%d]]\"", wholeinches, numerator, denominator);
            sInches.Format(L"%d[[%d/%d]]\"", wholeinches, numerator, denominator);
          else
            sInches.Format(L"%d %d/%d\"", wholeinches, numerator, denominator);
        }
        else
        {
          if (bracket_fractions)
            sInches.Format(L"[[%d/%d]]\"", numerator, denominator);
          else
            sInches.Format(L"%d/%d\"", numerator, denominator);
        }
      }
      else
      {
        sInches.Format(L"%d\"", wholeinches);
      }
      sFormat += sInches;
    }
    break;
  }
  }
  if (sFormat.Length() > max_string_length)
  {
    sFormat = ON_wString::FromNumber(distance);
  }
  output += sFormat;
  return true;
}

bool ON_NumberFormatter::FormatLength(
  double inputdistance,
  ON_DimStyle::LengthDisplay output_lengthdisplay,
  double round_off,
  int precision,
  ON_DimStyle::suppress_zero zero_suppress,
  bool bracket_fractions,
  ON_wString& output)
{
  ON_DimStyle::OBSOLETE_length_format output_lengthformat = ON_DimStyle::OBSOLETE_length_format::Decimal;
  if (output_lengthdisplay == ON_DimStyle::LengthDisplay::FeetAndInches)
    output_lengthformat = ON_DimStyle::OBSOLETE_length_format::FeetInches;
  else if (output_lengthdisplay == ON_DimStyle::LengthDisplay::InchesFractional)
    output_lengthformat = ON_DimStyle::OBSOLETE_length_format::Fractional;

  return ON_NumberFormatter::FormatNumber(
    inputdistance,
    output_lengthformat,
    round_off,
    precision,
    zero_suppress,
    bracket_fractions,
    output);
}

#pragma endregion DistanceFormat

#pragma region AngleFormat


bool ON_NumberFormatter::FormatAngleStringDMS(double angle_radians, ON_wString& formatted_string)
{
  return ON_NumberFormatter::FormatAngleStringDMS(angle_radians, 2, formatted_string);
  //bool rc = false;

  //int sign = 1;
  //int degrees = 0;
  //int minutes = 0;
  //int seconds = 0;
  //formatted_string.Empty();

  //double angle_degrees = ON_RADIANS_TO_DEGREES * angle_radians;
  //if (ON_IsValid(angle_degrees))
  //{
  //  double d_seconds;

  //  if (angle_degrees < 0.0)
  //  {
  //    sign = -1;
  //    angle_degrees = -angle_degrees;
  //  }

  //  d_seconds = angle_degrees * 3600;
  //  seconds = (int)(d_seconds + 0.5);
  //  minutes = seconds / 60;
  //  seconds = seconds % 60;
  //  degrees = minutes / 60;
  //  minutes = minutes % 60;

  //  degrees *= sign;
  //  formatted_string.Format(L"%d%lc %d\' %d\"", degrees, ON_wString::DegreeSymbol, minutes, seconds);
  //  rc = true;
  //}
  //return rc;
}

bool ON_NumberFormatter::FormatAngleStringDMS(double angle_radians, int resolution, ON_wString& formatted_string)
{
  bool rc = false;
  formatted_string.Empty();
  int idegrees = 0;
  int iminutes = 0;
  int iseconds = 0;

  double angle_degrees = ON_RADIANS_TO_DEGREES * angle_radians;
  int sign = 1;
  if (angle_degrees < 0.0)
  {
    sign = -1;
    angle_degrees = -angle_degrees;
  }
  angle_degrees = RoundOff(angle_degrees, 1e-8);
  double minutes = (angle_degrees - floor(angle_degrees));
  minutes *= 60.0;
  double seconds = (minutes - floor(minutes));
  seconds *= 60.0;

  if (resolution < 0)
    resolution = 0;
  if (resolution > 6)
    resolution = 6;

  if (resolution == 0)
  {
    idegrees = (int)floor(angle_degrees + 0.5);
    idegrees *= sign;
    rc = formatted_string.Format(L"%d%lc", idegrees, ON_wString::DegreeSymbol);
  }
  else
  {
    idegrees = (int)floor(angle_degrees);
    if (resolution == 1)
    {
      iminutes = (int)floor(minutes + 0.5);
      rc = formatted_string.Format(L"%d%lc %d\'", idegrees, ON_wString::DegreeSymbol, iminutes);
    }
    else
    {
      iminutes = (int)floor(minutes);
      if (resolution == 2)
      {
        iseconds = (int)floor(seconds + 0.5);
        if (iseconds >= 60)
        {
          iseconds -= 60;
          iminutes += 1;
        }
        if (iminutes >= 60)
        {
          iminutes -= 60;
          idegrees += 1;
        }
        rc = formatted_string.Format(L"%d%lc %d\' %d\"", idegrees, ON_wString::DegreeSymbol, iminutes, iseconds);
      }
      else 
      {
        if (seconds >= 60.0)
        {
          seconds -= 60.0;
          iminutes += 1;
        }
        if (iminutes >= 60)
        {
          iminutes -= 60;
          idegrees += 1;
        }
        ON_wString fmt;
        fmt.Format(L"%%d%%lc %%d\' %%.%dlf\"", resolution - 2);
        rc = formatted_string.Format(fmt.Array(), idegrees, ON_wString::DegreeSymbol, iminutes, seconds);
      }
    }
  }
  return rc;
}

bool ON_NumberFormatter::FormatAngleStringDecimal(
  double angle,
  int resolution,
  double roundoff,
  ON_DimStyle::suppress_zero zero_suppress,
  ON_wString& formatted_string)
{
  formatted_string.Empty();
  
  return ON_NumberFormatter::FormatNumber(
    angle,
    ON_DimStyle::OBSOLETE_length_format::Decimal,
    roundoff,
    resolution,
    zero_suppress,
    false,
    formatted_string);
}





#pragma endregion
