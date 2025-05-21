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
#include "opennurbs_internal_defines.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

bool ON_Color::IsSet() const
{
  return IsUnset() ? false : true;
}

bool ON_Color::IsUnset() const
{
  return ON_Color::UnsetColor == *this;
}

const ON_Color ON_Color::RandomColor()
{
  return RandomColor(ON_RandomNumberGenerator::RandomSeed());
}


const ON_Color ON_Color::RandomColor(
  ON_Interval hue_range,
  ON_Interval saturation_range,
  ON_Interval value_range
)
{
  return RandomColor(ON_RandomNumberGenerator::RandomSeed(), hue_range, saturation_range, value_range);
}

const ON_Color ON_Color::RandomColor(
  ON__UINT32 seed
)
{
  return ON_Color::RandomColor(seed, ON_Interval::ZeroToTwoPi, ON_Interval::Singleton(1.0), ON_Interval::Singleton(1.0));
}

const ON_Color ON_Color::RandomColor(
  ON__UINT32 seed,
  ON_Interval hue_range,
  ON_Interval saturation_range,
  ON_Interval value_range
)
{
  ON_RandomNumberGenerator rg;
  rg.Seed(seed + 1U); // the +1 is so the colors for seeds (0,1,2,3,4,5 are more visually distinct)
  const double h = hue_range.IsSingleton() ? hue_range.m_t[0] : rg.RandomDouble(hue_range);
  double s = saturation_range.IsSingleton() ? saturation_range.m_t[0] : rg.RandomDouble(saturation_range);
  if (s > ON_UNSET_VALUE && s < ON_UNSET_POSITIVE_VALUE)
  {
    if (s < 0.0)
      s = 0.0;
    else if (s > 1.0)
      s = 1.0;
  }
  else
    s = 1.0;
  double v = value_range.IsSingleton() ? value_range.m_t[0] : rg.RandomDouble(value_range);
  if (v > ON_UNSET_VALUE && v < ON_UNSET_POSITIVE_VALUE)
  {
    if (v < 0.0)
      v = 0.0;
    else if (v > 1.0)
      v = 1.0;
  }
  else
    v = 1.0;
  ON_Color color = ON_Color::UnsetColor;
  if (ON_IsValid(h) && ON_IsValid(s) && ON_IsValid(v))
    color.SetHSV( fmod(h,ON_2PI), s, v );
  return color;
}

const ON_Color ON_Color::FromHueInRadians(
  double hue_in_radians
)
{
  ON_Color c;
  c.SetHSV(hue_in_radians, 1.0, 1.0);
  return c;
}

ON_Color::ON_Color(unsigned int colorref)
  : m_color(colorref)
{
  // No adjustments are required on big endian computers because all
  // unsigned int conversion and all IO preserves the order of the
  // ON_Color::m_RGBA[4] bytes.
}

ON_Color::ON_Color(int r, int g, int b)
{
  SetRGB(r,g,b);
}

ON_Color::ON_Color(int r, int g, int b, int a)
{
  SetRGBA(r,g,b,a);
}

unsigned int ON_Color::WindowsRGB() const
{
  ON_Color RGB = ON_Color(Red(),Green(),Blue());
  return RGB;
}

ON_Color::operator unsigned int() const
{
  // No adjustments are required on big endian computers because all
  // unsigned int conversion and all IO preserves the order of the
  // ON_Color::m_RGBA[4] bytes.
  return m_color;
}

int ON_Color::Compare( const ON_Color& b ) const
{
  int ac = (int)m_color;
  int bc = (int)b.m_color;
#if defined(ON_BIG_ENDIAN)
  unsigned char* swapper = (unsigned char*)&ac;
  unsigned char c = swapper[0]; swapper[0] = swapper[3]; swapper[3] = c;
  c = swapper[1]; swapper[1] = swapper[2]; swapper[2] = c;
  swapper = (unsigned char*)&bc;
  c = swapper[0]; swapper[0] = swapper[3]; swapper[3] = c;
  c = swapper[1]; swapper[1] = swapper[2]; swapper[2] = c;
#endif
  return ac-bc; // overflow roll over is fine - important thing is that answer is consistent.
}

int ON_Color::Red() const
{ return m_RGBA[ON_Color::kRedByteIndex];}

int ON_Color::Green() const
{ return m_RGBA[ON_Color::kGreenByteIndex];}

int ON_Color::Blue() const
{ return m_RGBA[ON_Color::kBlueByteIndex];}

int ON_Color::Alpha() const
{ return m_RGBA[ON_Color::kAlphaByteIndex];}

double ON_Color::FractionRed() const
{
  //return Red()/255.0;
  return m_RGBA[ON_Color::kRedByteIndex]*0.003921568627450980392156862745; // better fodder for optimizer
}

double ON_Color::FractionGreen() const
{
  //return Green()/255.0;
  return m_RGBA[ON_Color::kGreenByteIndex]*0.003921568627450980392156862745; // better fodder for optimizer
}

double ON_Color::FractionBlue() const
{
  //return Blue()/255.0;
  return m_RGBA[ON_Color::kBlueByteIndex]*0.003921568627450980392156862745; // better fodder for optimizer
}

double ON_Color::FractionAlpha() const
{
  //return Alpha()/255.0;
  return m_RGBA[ON_Color::kAlphaByteIndex]*0.003921568627450980392156862745; // better fodder for optimizer
}

void ON_Color::SetRGB(int r,int g,int b) // 0 to 255
{
  SetRGBA(r,g,b,0);
}

void ON_Color::SetFractionalRGB(double r,double g,double b)
{
  SetFractionalRGBA(r,g,b,0.0);
}

void ON_Color::SetAlpha(int alpha)
{
	if (alpha < 0 ) alpha = 0; else if ( alpha > 255 ) alpha = 255;
	m_RGBA[ON_Color::kAlphaByteIndex] = (unsigned char)alpha;
}

void ON_Color::SetFractionalAlpha(double alpha)
{
	if (alpha < 0.0 ) alpha = 0.0; else if ( alpha > 1.0 ) alpha = 1.0;
  SetAlpha((int)(alpha*255.0));
}

void
ON_Color::SetRGBA( int red, int green, int blue, int alpha )
{
	if (red   < 0 ) red   = 0; else if ( red   > 255 ) red   = 255;
	if (green < 0 ) green = 0; else if ( green > 255 ) green = 255;
	if (blue  < 0 ) blue  = 0; else if ( blue  > 255 ) blue  = 255;
	if (alpha < 0 ) alpha = 0; else if ( alpha > 255 ) alpha = 255;
  m_RGBA[ON_Color::kRedByteIndex] = (unsigned char)red;
  m_RGBA[ON_Color::kGreenByteIndex] = (unsigned char)green;
  m_RGBA[ON_Color::kBlueByteIndex] = (unsigned char)blue;
  m_RGBA[ON_Color::kAlphaByteIndex] = (unsigned char)alpha;
}

void
ON_Color::SetFractionalRGBA( double red, double green, double blue, double alpha )
{
  int r,g,b,a;
	if (red   < 0.0 ) red   = 0.0; else if ( red   > 1.0 ) red   = 1.0;
	if (green < 0.0 ) green = 0.0; else if ( green > 1.0 ) green = 1.0;
	if (blue  < 0.0 ) blue  = 0.0; else if ( blue  > 1.0 ) blue  = 1.0;
	if (alpha < 0.0 ) alpha = 0.0; else if ( alpha > 1.0 ) alpha = 1.0;

  red   *= 255.0;
  green *= 255.0;
  blue  *= 255.0;
  alpha *= 255.0;

  r = (int)red;
  g = (int)green;
  b = (int)blue;
  a = (int)alpha;

  // round to closest int
  if( (red-r)>=0.5 ) r++;
  if( (green-g)>=0.5 ) g++;
  if( (blue-b)>=0.5 ) b++;
  if( (alpha-a)>=0.5 ) a++;

  SetRGBA( r, g, b, a );
}

double ON_Color::Hue() const
{
  // returns 0 to 2*pi
  // 0    = red,  pi/3   = yellow, 2*pi/3 = green,
  // pi   = cyan, 4*pi/3 = blue,   5*pi/3 = magenta,
  // 2*pi = red
  double h;
  int r = Red();
  int g = Green();
  int b = Blue();
  int minrgb, maxrgb;
  if ( r <= g ) {minrgb = r; maxrgb = g;} else {minrgb = g; maxrgb = r;}
  if (minrgb > b) minrgb = b; else if (maxrgb < b ) maxrgb = b;
  if ( maxrgb != minrgb ) {
    double d = 1.0/(maxrgb - minrgb);
    if ( r == maxrgb) {
      h = (g - b)*d;
      if ( h < 0.0 )
        h += 6.0;
    }
    else if ( g == maxrgb)
      h = 2.0 + (b - r)*d;
    else
      h = 4.0 + (r - g)*d;
    h *= ON_PI/3.0;
  }
  else
    h = 0.0;
  return h;
}

double ON_Color::Saturation() const
{
  // 0.0 to 1.0    0.0 = gray,  1.0 = saturated
  double s;
  int r = Red();
  int g = Green();
  int b = Blue();
  int minrgb, maxrgb;
  if ( r <= g ) {minrgb = r; maxrgb = g;} else {minrgb = g; maxrgb = r;}
  if (minrgb > b) minrgb = b; else if (maxrgb < b ) maxrgb = b;
  if ( maxrgb > 0 ) {
    s = ((double)(maxrgb - minrgb))/((double)maxrgb);
  }
  else
    s = 0.0;
  return s;
}

double ON_Color::Value() const
{
  // 0.0 to 1.0    0.0 = black, 1.0 = white
  int r = Red();
  int g = Green();
  int b = Blue();
  int maxrgb = ( r <= g ) ? g : r; if ( maxrgb < b ) maxrgb = b;
  return (maxrgb/255.0);
}

void ON_Color::SetHSV(
       double hue,         // hue in radians
       double saturation, // saturation 0.0 = gray, 1.0 = saturated
       double value       // value
       )
{
  if ( hue > ON_UNSET_FLOAT && hue < ON_UNSET_POSITIVE_FLOAT
    && saturation > ON_UNSET_FLOAT && saturation < ON_UNSET_POSITIVE_FLOAT
    && value > ON_UNSET_FLOAT && value < ON_UNSET_POSITIVE_FLOAT
    )
  {
    double r, g, b;
    if (value < 0.0)
      value = 0.0;
    else if (value > 1.0)
      value = 1.0;
    if (saturation <= 1.0 / 256.0)
    {
      r = value;
      g = value;
      b = value;
    }
    else
    {
      if (saturation > 1.0)
        saturation = 1.0;
      hue *= 3.0 / ON_PI;  // (6.0 / 2.0 * ON_PI);
      int i = (int)floor(hue);
      if (i < 0 || i > 5) {
        hue = fmod(hue, 6.0);
        if (hue < 0.0)
          hue += 6.0;
        i = (int)floor(hue);
      }
      const double f = hue - i;
      const double p = value * (1.0 - saturation);
      const double q = value * (1.0 - (saturation * f));
      const double t = value * (1.0 - (saturation * (1.0 - f)));
      switch (i)
      {
      case 0:
        r = value; g = t; b = p; break;
      case 1:
        r = q; g = value; b = p; break;
      case 2:
        r = p; g = value; b = t; break;
      case 3:
        r = p; g = q; b = value; break;
      case 4:
        r = t; g = p; b = value; break;
      case 5:
        r = value; g = p; b = q; break;
      default:
        r = 0; g = 0; b = 0; break; // to keep lint quiet
      }
    }
    SetFractionalRGB(r, g, b);
  }
  else
    *this = ON_Color::UnsetColor;
}


const ON_wString ON_Color::ToString(
  ON_Color::TextFormat format,
  wchar_t separator,
  bool bFormatUnsetColor
) const
{
  ON_wString s;
  if (ON_Color::UnsetColor == *this)
  {
    if (bFormatUnsetColor)
      s = L"ON_Color::UnsetColor";
  }
  else
  {
    if (0 != Alpha())
    {
      // handle conditional alpha case
      switch (format)
      {
      case ON_Color::TextFormat::FractionalRGBa:
        format = ON_Color::TextFormat::FractionalRGBA;
        break;
      case ON_Color::TextFormat::DecimalRGBa:
        format = ON_Color::TextFormat::DecimalRGBA;
        break;
      case ON_Color::TextFormat::HexadecimalRGBa:
        format = ON_Color::TextFormat::HexadecimalRGBA;
        break;
      case ON_Color::TextFormat::HSVa:
        format = ON_Color::TextFormat::HSVA;
        break;
      case ON_Color::TextFormat::HashRGBa:
        format = ON_Color::TextFormat::HashRGBA;
        break;
      default:
        break;
      }
    }

    if (0 == separator)
      separator = ',';

    switch (format)
    {
    case ON_Color::TextFormat::Unset:
      // intentionally returns empty string.
      break;
    case ON_Color::TextFormat::FractionalRGB:
    case ON_Color::TextFormat::FractionalRGBa: // nonzero alpha handled above
      s = ON_wString::FormatToString(L"%g%lc%g%lc%g", FractionRed(), separator, FractionGreen(), separator, FractionBlue());
      break;
    case ON_Color::TextFormat::FractionalRGBA:
      s = ON_wString::FormatToString(L"%g%lc%g%lc%g%lc%g", FractionRed(), separator, FractionGreen(), separator, FractionBlue(), separator, FractionAlpha());
      break;
    case ON_Color::TextFormat::DecimalRGB:
    case ON_Color::TextFormat::DecimalRGBa: // nonzero alpha handled above
      s = ON_wString::FormatToString(L"%d%lc%d%lc%d", Red(), separator, Green(), separator, Blue());
      break;
    case ON_Color::TextFormat::DecimalRGBA:
      s = ON_wString::FormatToString(L"%d%lc%d%lc%d%lc%d", Red(), separator, Green(), separator, Blue(), separator, Alpha());
      break;
    case ON_Color::TextFormat::HexadecimalRGB:
    case ON_Color::TextFormat::HexadecimalRGBa: // nonzero alpha handled above
      s = ON_wString::FormatToString(L"%02x%lc%02x%lc%02x", Red(), separator, Green(), separator, Blue());
      break;
    case ON_Color::TextFormat::HexadecimalRGBA:
      s = ON_wString::FormatToString(L"%02x%lc%02x%lc%02x%lc%02x", Red(), separator, Green(), separator, Blue(), separator, Alpha());
      break;
    case ON_Color::TextFormat::HSV:
    case ON_Color::TextFormat::HSVa: // nonzero alpha handled above
      s = ON_wString::FormatToString(L"%g%lc%g%lc%g", Hue(), separator, Saturation(), separator, Value());
      break;
    case ON_Color::TextFormat::HSVA:
      s = ON_wString::FormatToString(L"%g%lc%g%lc%g%lc%g", Hue(), separator, Saturation(), separator, Value(), separator, FractionAlpha());
      break;
    case ON_Color::TextFormat::HashRGB:
    case ON_Color::TextFormat::HashRGBa: // nonzero alpha handled above
      s = ON_wString::FormatToString(L"#%02x%02x%02x", Red(), Green(), Blue());
      break;
    case ON_Color::TextFormat::HashRGBA:
      s = ON_wString::FormatToString(L"#%02x%02x%02x%02x", Red(), Green(), Blue(), Alpha());
      break;
    }
  }
  return s;
}

const ON_wString ON_Color::ToString(
  ON_Color::TextFormat format,
  wchar_t separator,
  bool bFormatUnsetColor,
  class ON_TextLog& text_log
) const
{
  return ON_Color::ToString(format, separator, bFormatUnsetColor);
}

void ON_Color::ToText(
  ON_Color::TextFormat format,
  wchar_t separator,
  bool bFormatUnsetColor,
  class ON_TextLog& text_log
) const
{
  const ON_wString s = ToString(format, separator, bFormatUnsetColor, text_log);
  if (s.IsNotEmpty())
    text_log.Print(L"%ls", static_cast<const wchar_t*>(s));
}

enum { R, G, B, A };

ON_4fColor::ON_4fColor()
{
  for (int i = 0; i < 4; i++)
  {
    m_color[i] = ON_UNSET_FLOAT;
  }
}

ON_4fColor::ON_4fColor(int r, int g, int b, int a)
{
  SetRGBA(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

ON_4fColor::ON_4fColor(float r, float g, float b, float a)
{
  SetRGBA(r, g, b, a);
}

// Note that this function will set the alpha correctly from ON_Color's 'inverted' alpha.
ON_4fColor::ON_4fColor(const ON_Color& in)
{
  *this = in;
}

ON_4fColor& ON_4fColor::operator = (const ON_Color& in)
{
  SetRed  (       float(in.FractionRed()));
  SetGreen(       float(in.FractionGreen()));
  SetBlue (       float(in.FractionBlue()));
  SetAlpha(1.0f - float(in.FractionAlpha()));

  return *this;
}

bool ON_4fColor::operator == (const ON_4fColor& other)
{
  return Compare(other) == 0;
}

bool ON_4fColor::operator != (const ON_4fColor& other)
{
  return Compare(other) != 0;
}

// Will invert the opacity alpha to transparency.
ON_4fColor::operator ON_Color(void) const
{
  ON_Color out;
  out.SetFractionalRGBA(Red(), Green(), Blue(), 1.0 - Alpha());

  return out;
}

float ON_4fColor::Red(void) const
{
  return m_color[R];
}

void ON_4fColor::SetRed(float f)
{
  m_color[R] = f;
}

float ON_4fColor::Green(void) const
{
  return m_color[G];
}

void ON_4fColor::SetGreen(float f)
{
  m_color[G] = f;
}

float ON_4fColor::Blue(void) const
{
  return m_color[B];
}

void ON_4fColor::SetBlue(float f)
{
  m_color[B] = f;
}

float ON_4fColor::Alpha(void) const
{
  return m_color[A];
}

void ON_4fColor::SetAlpha(float f)
{
  m_color[A] = f;
}

void ON_4fColor::SetRGBA(float r, float g, float b, float a)
{
  m_color[R] = r;
  m_color[G] = g;
  m_color[B] = b;
  m_color[A] = a;
}

bool ON_4fColor::IsValid(class ON_TextLog*) const
{
  for (int i = 0; i < 4; i++)
  {
    if (ON_IS_UNSET_FLOAT(m_color[i]))
      return false;
  }
  return true;
}


ON_ColorStop::ON_ColorStop(const ON_Color& color, double position)
  : m_color(color)
  , m_position(position)
{
}

bool ON_ColorStop::Write(ON_BinaryArchive& archive) const
{
  bool rc = archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK, 1, 0);
  if (!rc)
    return false;

  for (;;)
  {
    rc = archive.WriteColor(m_color);
    if (!rc) break;
    rc = archive.WriteDouble(m_position);
    if (!rc) break;

    break;
  }

  if (!archive.EndWrite3dmChunk())
    rc = false;

  return rc;
}

bool ON_ColorStop::Read(ON_BinaryArchive& file)
{
  int major_version = 0;
  int minor_version = 0;
  bool rc = file.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK, &major_version, &minor_version);
  if (!rc)
    return false;
  for (;;)
  {
    rc = (1 == major_version);
    if (!rc) break;
    rc = file.ReadColor(m_color);
    if (!rc) break;
    rc = file.ReadDouble(&m_position);
    if (!rc) break;

    break;
  }
  if (!file.EndRead3dmChunk())
    rc = false;

  return rc;
}

static int CompareNans(double a, double b)
{
  if (a == a)
  {
    if (b == b)
    {
      return ((a < b) ? -1 : ((a > b) ? 1 : 0));
    }
    // a is not a NAN, b is a NAN
    return -1; // a < b - NAN's are last
  }
  else if (b == b)
  {
    // a is a NAN, b is not a NAN
    return -1; // b < a - NAN's are last
  }
  return 0; // a and b are both NaNs
}

static int CompareDouble(double a, double b)
{
  return ((a < b) ? -1 : ((a > b) ? 1 : (a == b ? 0 : CompareNans(a, b))));
}

int ON_4fColor::Compare(const ON_4fColor& b) const
{
  int rc = CompareDouble(Red(), b.Red());
  if (0 != rc)
    return rc;

  rc = CompareDouble(Green(), b.Green());
  if (0 != rc)
    return rc;

  rc = CompareDouble(Blue(), b.Blue());
  if (0 != rc)
    return rc;

  rc = CompareDouble(Alpha(), b.Alpha());

  return rc;
}

void ON_4fColor::BlendTo(float t, const ON_4fColor& col, bool bClampAlpha)
{
  const auto t01 = std::max(0.0f, std::min(1.0f, t));

  for (int i = 0; i < 4; i++)
  {
    m_color[i] = Lerp(t01, m_color[i], col.m_color[i]);
  }

  if (bClampAlpha)
  {
    m_color[A] = std::max(0.0f, std::min(1.0f, m_color[A]));
  }
}

float* ON_4fColor::FloatArray(void)
{
  return m_color;
}

const float* ON_4fColor::FloatArray(void) const
{
  return m_color;
}
