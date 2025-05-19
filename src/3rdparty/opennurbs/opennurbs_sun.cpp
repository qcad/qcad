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

// ShadowIntensity in the Sun and Skylight are currently unused. The only ShadowIntensity that's actually
// used is the one in the lights. See [SHADOW_INTENSITY_UNUSED]

static const wchar_t* XMLPath_Sun(void)
{
  return ON_RDK_DOCUMENT  ON_XML_SLASH  ON_RDK_SETTINGS  ON_XML_SLASH  ON_RDK_SUN;
}

static double Sin(double deg) { return sin(ON_RadiansFromDegrees(deg)); }
static double Cos(double deg) { return cos(ON_RadiansFromDegrees(deg)); }
static double Tan(double deg) { return tan(ON_RadiansFromDegrees(deg)); }

static double ArcSin(double sine)           { return ON_DegreesFromRadians(asin(sine)); }
static double ArcTan2(double dy, double dx) { return ON_DegreesFromRadians(atan2(dy, dx)); }
static double WorldToCompass(double d)      { return 90.0 - d; }
static double TwilightZone(void)            { return 3.0; }

static constexpr double c2 = 14388.0;
static constexpr double monitor_white = 5000.0;

static bool IsLeapYear(int year)
{
  // The year can only be a leap year if it is divisible by 4.
  if (0 != (year % 4))
    return false;

  // If the year is a century it is only a leap year if it is divisible by 400.
  if ((0 == (year % 100)) && (0 != (year % 400)))
    return false;

  return true;
}

static double Planck(double lambda, double temp)
{
  static const double E = 2.7182818284590452354;
  return (pow(double(lambda), -5.0) / (pow(E, c2 / (lambda * temp)) - 1.0));
}

static ON_4fColor ColorTemperature(double temperature)
{
  // Use a variant of Planck's equation to get values for the three CIE wavelengths.
  double temp = monitor_white;

  double er = Planck(0.60, temp);
  double eg = Planck(0.56, temp);
  double eb = Planck(0.44, temp);

  double es = 1.0 / std::max(er, std::max(eg, eb));

  const double r_white = er * es;
  const double g_white = eg * es;
  const double b_white = eb * es;

  temp = temperature;

  er = Planck(0.60, temp);
  eg = Planck(0.56, temp);
  eb = Planck(0.44, temp);

  es = 1.0 / std::max(er,std::max(eg, eb));

  const double r = er * es / r_white;
  const double g = eg * es / g_white;
  const double b = eb * es / b_white;

  es = 1.0 / std::max(r, std::max(g, b));

  const float rr = float(pow(r * es, 0.15));
  const float gr = float(pow(g * es, 0.15));
  const float br = float(pow(b * es, 0.15));

  return ON_4fColor(rr, gr, br, 1.0f);
}

template <typename T>
static ON__UINT32 UpdateCRC(ON__UINT32 crc, T x)
{
  return ON_CRC32(crc, sizeof(x), &x);
}

inline static double Int(double x)
{
  return (x < 0.0) ? ceil(x) : floor(x);
}

inline static double Frac(double x)
{
  return x - Int(x);
}

inline static double Unwind(double dDegrees)
{
  dDegrees = Frac(dDegrees / 360.0) * 360.0;
  if (dDegrees < 0.0)
    dDegrees += 360.0;

  return dDegrees;
}

static bool IsVectorEqual(const ON_3dVector& v1, const ON_3dVector& v2)
{
  return IsDoubleEqual(v1.x, v2.x) && IsDoubleEqual(v1.y, v2.y) && IsDoubleEqual(v1.z, v2.z);
}

static ON_3dVector PerpendicularVectorOnXYPlane(const ON_3dVector& vec)
{
  return ON_2dVector(vec.x, vec.y).IsTiny() ? ON_3dVector(vec.z, 0.0, -vec.x) : ON_3dVector(-vec.y, vec.x, 0.0);
}

static double AngleFromVectors(const ON_3dVector& v1, const ON_3dVector& v2, ON_3dVector normal)
{
  if (IsVectorEqual(v1, v2))
    return 0.0;

  normal.Unitize();

  const double numerator = v1 * v2;
  const double denominator = v1.Length() * v2.Length();

  auto cross = ON_CrossProduct(v1, v2);
  cross.Unitize();

  if (IsVectorEqual(cross, ON_3dVector::ZeroVector))
  {
    if (IsDoubleEqual(numerator, +1.0))
      return 0.0;

    if (IsDoubleEqual(numerator, -1.0))
      return ON_PI;
  }

  double division = numerator / denominator;

  if (division > 1.0)
      division = 1.0;
  else
  if (division < -1.0)
      division = -1.0;

  if (IsDoubleEqual(division, -1.0))
    return ON_PI;

  double angle = acos(division);

  // Check if cross is parallel or anti-parallel to normal vector. If anti-parallel then angle = 360 - angle.
  const double dot = cross * normal;
  if (IsDoubleEqual(dot, -1.0))
    angle = (ON_PI * 2.0) - angle;

  return angle;
}

// Reference: Jean Meeus - 'Astronomical Algorithms', second edition.

class ON_SunEngine::CImpl final
{
public:
  void UpdateIfModified(void);

  double JulianDay(void) const
  {
    return _local_julian_day - (_local_tz_hours + (_local_daylight_mins / 60.0)) / 24.0;
  }

public:
  double _azimuth = 0.0;
  double _altitude = 0.0;
  double _latitude = 0.0;
  double _longitude = 0.0;
  double _local_julian_day = 0.0;
  double _local_tz_hours = 0.0;
  int    _local_daylight_mins = 0;
  double _cache_right_ascension = 0.0;
  double _cache_sin_declination = 0.0;
  double _cache_cos_declination = 0.0;
  double _cache_tan_declination = 0.0;
  double _cache_sin_latitude = Sin(0.0);
  double _cache_cos_latitude = Cos(0.0);
  double _cache_greenwich_sidereal_time = 0.0;
  bool _modified = true;
	bool _julian_date_changed = true;
  Accuracy _accuracy = Accuracy::Minimum;

  // The obliquity of the ecliptic (the tilt of the earth's axis) is usually considered to be about 23.5
  // degrees, but it actually changes very slowly with the passing centuries. These rough values are used
  // when the accuracy is set to minimum.
  const double _rough_cos_obliquity = 0.91747714052291862;
  const double _rough_sin_obliquity = 0.39778850739794974;
};

void ON_SunEngine::CImpl::UpdateIfModified(void)
{
  if (!_modified)
    return;

  if (_julian_date_changed)
  {
    const auto dJulianDayUT = JulianDay();

    const auto dJulianDayUT2000  = dJulianDayUT - 2451545.0;
    const auto dJulianCenturies  = dJulianDayUT2000 / 36525.0;
    const auto dJulianCenturies2 = dJulianCenturies * dJulianCenturies;
    const auto dJulianCenturies3 = dJulianCenturies * dJulianCenturies2;

    // Calculate the sun's true and apparent ecliptic longitude.
    const auto dL0 = 280.46646 + 36000.76983 * dJulianCenturies + 0.0003032 * dJulianCenturies2;

    auto dC = 0.0;

    if ((Accuracy::Maximum == _accuracy))
    {
      const auto dMeanAnomaly = 357.52911 + 35999.05029 * dJulianCenturies - 0.0001537 * dJulianCenturies2;

      dC = Sin(dMeanAnomaly * 3.0) *  0.000289 +
           Sin(dMeanAnomaly * 2.0) * (0.019993 - 0.000101 * dJulianCenturies) +
           Sin(dMeanAnomaly      ) * (1.914602 - 0.004817 * dJulianCenturies  -
                                                 0.000014 * dJulianCenturies2);
    }

    const auto dTrueLongitude = Unwind(dL0 + dC);

    auto dApparentLongitude = dTrueLongitude - 0.00569;

    auto dSinObliquity = _rough_sin_obliquity;
    auto dCosObliquity = _rough_cos_obliquity;

    if ((Accuracy::Maximum == _accuracy))
    {
      // Include the effect of the moon.
      const auto dOmega = 125.04 - 1934.136 * dJulianCenturies;
      dApparentLongitude -= 0.00478 * Sin(dOmega);

      // Calculate the obliquity of the ecliptic (the tilt of the earth's axis).
      const auto dObliquity = 23.439291111 - (46.81500 * dJulianCenturies  -
                                              0.000590 * dJulianCenturies2 +
                                              0.001813 * dJulianCenturies3) / 3600.0 +
                                              0.002560 * Cos(dOmega);
      dSinObliquity = Sin(dObliquity);
      dCosObliquity = Cos(dObliquity);
    }

    // Calculate the sun's equatorial coordinates (right ascension and declination).
    const auto dSinApparentLongitude = Sin(dApparentLongitude);
    const auto dCosApparentLongitude = Cos(dApparentLongitude);

    const auto dDeclination = ArcSin(dSinApparentLongitude * dSinObliquity);

    _cache_right_ascension = Unwind(ArcTan2(dSinApparentLongitude * dCosObliquity, dCosApparentLongitude));
    _cache_sin_declination = Sin(dDeclination);
    _cache_cos_declination = Cos(dDeclination);
    _cache_tan_declination = Tan(dDeclination); // Declination is between -24 and +24 so no problem with Tan(90).

    // Calculate the sidereal time at Greenwich, expressed in degrees.
    const auto dTheta0 = 280.46061837 + (360.98564736629 * dJulianDayUT2000) +
                        (0.000387933 * dJulianCenturies2) - (dJulianCenturies3 / 38710000.0);

    _cache_greenwich_sidereal_time = Unwind(dTheta0);

    _julian_date_changed = false;
  }

  // Calculate the sun's local hour angle, expressed in degrees.
  const auto dLocalHourAngle = _cache_greenwich_sidereal_time + _longitude - _cache_right_ascension;

  // Calculate the sun's horizontal coordinates (azimuth and altitude).
  const auto dSinLocalHourAngle = Sin(dLocalHourAngle);
  const auto dCosLocalHourAngle = Cos(dLocalHourAngle);

  _azimuth = Unwind(180.0 + ArcTan2(dSinLocalHourAngle,
                                    dCosLocalHourAngle    * _cache_sin_latitude -
                                   _cache_tan_declination * _cache_cos_latitude));

  _altitude = ArcSin(_cache_sin_latitude * _cache_sin_declination +
                     _cache_cos_latitude * _cache_cos_declination * dCosLocalHourAngle);

  _modified = false;
}

ON_SunEngine::ON_SunEngine(Accuracy a)
{
  _impl = new CImpl;
  _impl->_accuracy = a;
}

ON_SunEngine::~ON_SunEngine()
{
  delete _impl;
  _impl = nullptr;
}

ON_SunEngine::ON_SunEngine(const ON_SunEngine& e)
{
  _impl = new CImpl;
  operator = (e);
}

const ON_SunEngine& ON_SunEngine::operator = (const ON_SunEngine& e)
{
  _impl->_accuracy                      = e._impl->_accuracy;
  _impl->_azimuth                       = e._impl->_azimuth;
  _impl->_altitude                      = e._impl->_altitude;
  _impl->_latitude                      = e._impl->_latitude;
  _impl->_longitude                     = e._impl->_longitude;
  _impl->_local_julian_day              = e._impl->_local_julian_day;
  _impl->_local_tz_hours                = e._impl->_local_tz_hours;
  _impl->_local_daylight_mins           = e._impl->_local_daylight_mins;
  _impl->_cache_right_ascension         = e._impl->_cache_right_ascension;
  _impl->_cache_sin_declination         = e._impl->_cache_sin_declination;
  _impl->_cache_cos_declination         = e._impl->_cache_cos_declination;
  _impl->_cache_tan_declination         = e._impl->_cache_tan_declination;
  _impl->_cache_sin_latitude            = e._impl->_cache_sin_latitude;
  _impl->_cache_cos_latitude            = e._impl->_cache_cos_latitude;
  _impl->_cache_greenwich_sidereal_time = e._impl->_cache_greenwich_sidereal_time;
  _impl->_modified                      = e._impl->_modified;
	_impl->_julian_date_changed           = e._impl->_julian_date_changed;

  return *this;
}

bool ON_SunEngine::operator == (const ON_SunEngine& e)
{
  if (_impl->_azimuth             != e._impl->_azimuth)             return false;
  if (_impl->_altitude            != e._impl->_altitude)            return false;
  if (_impl->_latitude            != e._impl->_latitude)            return false;
  if (_impl->_longitude           != e._impl->_longitude)           return false;
  if (_impl->_local_julian_day    != e._impl->_local_julian_day)    return false;
  if (_impl->_local_tz_hours      != e._impl->_local_tz_hours)      return false;
  if (_impl->_local_daylight_mins != e._impl->_local_daylight_mins) return false;

  return true;
}

bool ON_SunEngine::operator != (const ON_SunEngine& e)
{
  return !(operator == (e));
}

int ON_SunEngine::DaysInMonth(int month, int year) // Static.
{
  month = std::max(1, std::min(12, month));

  if ((2 == month) && IsLeapYear(year))
    return 29;

  static const int tab[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

  return tab[month];
}

double ON_SunEngine::Latitude(void) const
{
  return _impl->_latitude;
}

bool ON_SunEngine::SetLatitude(double lat)
{
  if ((lat < -90.0) || (lat > 90.0))
    return false;

  if (_impl->_latitude != lat)
  {
    _impl->_latitude = lat;
    _impl->_cache_sin_latitude = Sin(lat);
    _impl->_cache_cos_latitude = Cos(lat);
    _impl->_modified = true;
  }

  return true;
}

double ON_SunEngine::Longitude(void) const
{
  return _impl->_longitude;
}

bool ON_SunEngine::SetLongitude(double dLong)
{
  if ((dLong < -180.0) || (dLong > 180.0))
    return false;

  if (_impl->_longitude != dLong)
  {
    _impl->_longitude = dLong;
    _impl->_modified = true;
  }

  return true;
}

bool ON_SunEngine::SetTimeZoneHours(double dHours)
{
  if ((dHours < -12.0) || (dHours > 13.0))
    return false;

  const double dLocalTimeZoneHours = dHours;
  if (_impl->_local_tz_hours != dLocalTimeZoneHours)
  {
    _impl->_local_tz_hours = dLocalTimeZoneHours;
    _impl->_modified = true;
    _impl->_julian_date_changed = true;
  }

  return true;
}

bool ON_SunEngine::SetDaylightSavingMinutes(int iMinutes)
{
  if ((iMinutes < 0) || (iMinutes > 120))
    return false;

  const int iLocalDaylightMinutes = iMinutes;
  if (_impl->_local_daylight_mins != iLocalDaylightMinutes)
  {
    _impl->_local_daylight_mins = iLocalDaylightMinutes;
    _impl->_modified = true;
    _impl->_julian_date_changed = true;
  }

  return true;
}

bool ON_SunEngine::SetLocalDateTime(int iYear, int iMonth, int iDay, double dHours)
{
  if ((iYear < 1800) || (iYear > 2199) || (iMonth < 1) || (iMonth > 12))
    return false;

  if ((iDay < 1) || (iDay > DaysInMonth(iMonth, iYear)))
    return false;

  if ((dHours < 0.0) || (dHours > 24.0))
    return false;

  if (iMonth < 3)
  {
    iMonth += 12;
    iYear--;
  }

  const int a = iYear / 100;
  const int b = 2 - a + (a / 4);
  const int iJulianDay = (36525 * (iYear + 4716)) / 100 + (306 * (iMonth + 1)) / 10 + iDay + b - 1524;

  const double dJulianDay = iJulianDay + dHours / 24.0 - 0.5;

  return SetLocalJulianDay(dJulianDay);
}

void ON_SunEngine::LocalDateTime(int& iYear, int& iMonth, int& iDay, double& dHours) const
{
  const double jd = _impl->_local_julian_day + 0.5;
  int b = (int)Int(jd);
  const int a = (b * 100 - 186721625) / 3652425;
  b += 1 + a - (a / 4) + 1524;
  const int c = (b * 100 - 12210) / 36525;
  const int d = (365 * c) + (c / 4);
  const int e = (10000 * (b - d)) / 306001;
  iDay = (int)(b - d - ((306001 * e) / 10000));
  iMonth = (int)((e < 14) ? e - 1 : e - 13);
  iYear = (int)((iMonth > 2) ? c - 4716 : c - 4715);
  dHours = Frac(jd) * 24.0 + 1e-8;
}

bool ON_SunEngine::SetLocalJulianDay(double dLocalJulianDay)
{
  if ((dLocalJulianDay < 2378496.5) || (dLocalJulianDay > 2524593.499999999))
    return false;

  if (_impl->_local_julian_day != dLocalJulianDay)
  {
    _impl->_local_julian_day = dLocalJulianDay;
    _impl->_julian_date_changed = true;
    _impl->_modified = true;
  }

  return true;
}

double ON_SunEngine::Azimuth(void) const
{
  _impl->UpdateIfModified();

  return _impl->_azimuth;
}

double ON_SunEngine::Altitude(void) const
{
  _impl->UpdateIfModified();

  return _impl->_altitude;
}

double ON_SunEngine::JulianDay(void) const
{
  return _impl->JulianDay();
}

double ON_SunEngine::LocalJulianDay(void) const
{
  return _impl->_local_julian_day;
}

double ON_SunEngine::TimeZoneHours(void) const
{
  return _impl->_local_tz_hours;
}

int ON_SunEngine::DaylightSavingMinutes(void) const
{
  return _impl->_local_daylight_mins;
}

void ON_SunEngine::ConvertHorizonCoordsToSolarVector(double dAzimuth, double dAltitude, double* dVector) // Static.
{
  dVector[0] = -Cos(dAltitude) * Sin(dAzimuth);
  dVector[1] = -Cos(dAltitude) * Cos(dAzimuth);
  dVector[2] = -Sin(dAltitude);
}

void ON_SunEngine::ConvertSolarVectorToHorizonCoords(const double* dVector, double& dAzimuth, double& dAltitude) // Static.
{
  dAltitude = ArcSin(-dVector[2]);

  const double dY = dVector[0] / -Cos(dAltitude);
  const double dX = dVector[1] / -Cos(dAltitude);

  dAzimuth = ArcTan2(dY, dX);
  if (dAzimuth < 0.0)
    dAzimuth += 360.0;
}

static tm CurrentLocalTimeAsStructTM(void)
{
  const time_t time = ON_SecondsSinceJanOne1970UTC();

  tm ttm = { 0 };

#ifdef ON_RUNTIME_WIN
  _localtime64_s(&ttm, &time);
#else
  ttm = *localtime(&time);
#endif

  return ttm;
}

void ON_SunEngine::GetCurrentLocalDateTime(int& y, int& m, int& d, double& h)
{
  const tm ttm = CurrentLocalTimeAsStructTM();
  y = ttm.tm_year + 1900;
  m = ttm.tm_mon + 1;
  d = ttm.tm_mday;
  h = ttm.tm_hour + (ttm.tm_min / 60.0) + (ttm.tm_sec / 3600.0);
}

void ON_SunEngine::GetDefaultLocalDateTime(int& y, int& m, int& d, double& h)
{
  const tm ttm = CurrentLocalTimeAsStructTM();
  y = ttm.tm_year + 1900;
  m = 3;
  d = 21;
  h = 12.0;
}

class ON_Sun::CImpl : public ON_InternalXMLImpl
{
public:
  CImpl() { }
  CImpl(ON_XMLNode& n) : ON_InternalXMLImpl(&n) { }

  bool EnableAllowed(void) const;
  void SetEnableAllowed(bool allowed);
  bool EnableOn(void) const;
  void SetEnableOn(bool on);
  bool ManualControlAllowed(void) const;
  void SetManualControlAllowed(bool allowed);
  bool ManualControlOn(void) const;
  void SetManualControlOn(bool manual);
  double Azimuth(void) const;
  void SetAzimuth(double azi);
  double Altitude(void) const;
  void SetAltitude(double alt);
  double TimeZone(void) const;
  void SetTimeZone(double hours);
  double North(void) const;
  void SetNorth(double);
  double Latitude(void) const;
  void SetLatitude(double);
  double Longitude(void) const;
  void SetLongitude(double);
  bool DaylightSavingOn(void) const;
  void SetDaylightSavingOn(bool on);
  int DaylightSavingMinutes(void) const;
  void SetDaylightSavingMinutes(int minutes);
  void LocalDateTime(int& year, int& month, int& day, double& hours) const;
  bool SetLocalDateTime(int year, int month, int day, double hours);
  double Intensity(void) const;
  void SetIntensity(double d);
  double ShadowIntensity(void) const;
  void SetShadowIntensity(double d);
  bool IsUsingManualControl(void) const;

private:
  void UpdateAziAlt(void) const;
  void GetEarthAnchorPlane(ON_3dVector& anchor_north, ON_Plane& plane) const;

public:
  mutable double _azimuth = 0.0;
  mutable double _altitude = 0.0;
  mutable bool _calc_dirty = true;
  ON_EarthAnchorPoint* _earth_anchor_point = nullptr;
  ON_SunEngine::Accuracy _accuracy = ON_SunEngine::Accuracy::Minimum;
};

bool ON_Sun::CImpl::IsUsingManualControl(void) const
{
  // If manual control has been set on even if it's not 'allowed', consider it on anyway.
  // This makes it easier for clients that set manual control on without knowing they are supposed
  // to also allow it. I'm not even sure why it wouldn't be allowed nowadays. TODO: Ask Andy.
  return ManualControlOn();
}

void ON_Sun::CImpl::GetEarthAnchorPlane(ON_3dVector& anchor_north, ON_Plane& plane) const
{
  ON_3dVector anchor_east = _earth_anchor_point->ModelEast();

  anchor_north = _earth_anchor_point->ModelNorth();

  // Keeps original vector length if feasible.
  double east_len =  anchor_east .LengthAndUnitize();
  double north_len = anchor_north.LengthAndUnitize();

  // Compute normal of the plane P that contains m_model_east & m_model_north.
  plane.zaxis = ON_CrossProduct(anchor_east, anchor_north);

  if (plane.zaxis.IsTiny())
  {
    // Recompute a valid North and East vector.
    if (!anchor_north.IsTiny())
    {
      // North and east are equal or east is tiny.
      anchor_east = -PerpendicularVectorOnXYPlane(anchor_north);
      east_len = north_len;
    }
    else
    {
      if (!anchor_east.IsTiny())
      {
        // North and east are equal or north is tiny.
        anchor_north = PerpendicularVectorOnXYPlane(anchor_east);
        north_len = east_len;
      }
      else
      {
        // Both are identity.
        east_len = north_len = 1.0;
        anchor_east  = ON_3dVector::XAxis;
        anchor_north = ON_3dVector::YAxis;
      }
    }

    plane.zaxis = ON_CrossProduct(anchor_east, anchor_north);
  }

  plane.xaxis = PerpendicularVectorOnXYPlane(plane.zaxis);
  plane.yaxis = ON_CrossProduct(plane.zaxis, plane.xaxis);

  // Restores original vector length if were valid.
  plane.xaxis *= east_len;
  plane.yaxis *= north_len;
  plane.zaxis *= east_len * north_len;

  plane.origin = _earth_anchor_point->ModelPoint();
  plane.UpdateEquation();
}

void ON_Sun::CImpl::UpdateAziAlt(void) const
{
  if (_calc_dirty)
  {
    ON_SunEngine engine(_accuracy);
    engine.SetLatitude (Latitude());
    engine.SetLongitude(Longitude());
    engine.SetTimeZoneHours(TimeZone());

    const int dsm = DaylightSavingOn() ? DaylightSavingMinutes() : 0;
    engine.SetDaylightSavingMinutes(dsm);

    int y = 0, m = 0, d = 0; double h = 0.0;
    LocalDateTime(y, m, d, h);
    engine.SetLocalDateTime(y, m, d, h);

    _azimuth  = engine.Azimuth();
    _altitude = engine.Altitude();

    _calc_dirty = false;
  }
}

bool ON_Sun::CImpl::EnableAllowed(void) const
{
  return GetParameter(XMLPath_Sun(), ON_RDK_SUN_ENABLE_ALLOWED, false);
}

void ON_Sun::CImpl::SetEnableAllowed(bool allowed)
{
  SetParameter(XMLPath_Sun(), ON_RDK_SUN_ENABLE_ALLOWED, allowed);
}

bool ON_Sun::CImpl::EnableOn(void) const
{
  return GetParameter(XMLPath_Sun(), ON_RDK_SUN_ENABLE_ON, false);
}

void ON_Sun::CImpl::SetEnableOn(bool on)
{
  SetParameter(XMLPath_Sun(), ON_RDK_SUN_ENABLE_ON, on);
}

bool ON_Sun::CImpl::ManualControlAllowed(void) const
{
  return GetParameter(XMLPath_Sun(), ON_RDK_SUN_MANUAL_CONTROL_ALLOWED, false);
}

void ON_Sun::CImpl::SetManualControlAllowed(bool allowed)
{
  SetParameter(XMLPath_Sun(), ON_RDK_SUN_MANUAL_CONTROL_ALLOWED, allowed);
}

bool ON_Sun::CImpl::ManualControlOn(void) const
{
  return GetParameter(XMLPath_Sun(), ON_RDK_SUN_MANUAL_CONTROL_ON, false);
}

void ON_Sun::CImpl::SetManualControlOn(bool manual)
{
  SetParameter(XMLPath_Sun(), ON_RDK_SUN_MANUAL_CONTROL_ON, manual);
}

double ON_Sun::CImpl::Azimuth(void) const
{
  if (IsUsingManualControl())
    return GetParameter(XMLPath_Sun(), ON_RDK_SUN_AZIMUTH, 0.0).AsDouble();

  UpdateAziAlt();

  return _azimuth;
}

void ON_Sun::CImpl::SetAzimuth(double azimuth)
{
  SetParameter(XMLPath_Sun(), ON_RDK_SUN_AZIMUTH, azimuth);
}

double ON_Sun::CImpl::Altitude(void) const
{
  if (IsUsingManualControl())
    return GetParameter(XMLPath_Sun(), ON_RDK_SUN_ALTITUDE, 0.0).AsDouble();

  UpdateAziAlt();

  return _altitude;
}

void ON_Sun::CImpl::SetAltitude(double altitude)
{
  SetParameter(XMLPath_Sun(), ON_RDK_SUN_ALTITUDE, altitude);
}

double ON_Sun::CImpl::TimeZone(void) const
{
  return GetParameter(XMLPath_Sun(), ON_RDK_SUN_OBSERVER_TIMEZONE, 0.0);
}

void ON_Sun::CImpl::SetTimeZone(double hours)
{
  SetParameter(XMLPath_Sun(), ON_RDK_SUN_OBSERVER_TIMEZONE, hours);
  _calc_dirty = true;
}

bool ON_Sun::CImpl::DaylightSavingOn(void) const
{
  return GetParameter(XMLPath_Sun(), ON_RDK_SUN_DAYLIGHT_SAVING_ON, false);
}

void ON_Sun::CImpl::SetDaylightSavingOn(bool on)
{
  SetParameter(XMLPath_Sun(), ON_RDK_SUN_DAYLIGHT_SAVING_ON, on);
  _calc_dirty = true;
}

int ON_Sun::CImpl::DaylightSavingMinutes(void) const 
{
  return GetParameter(XMLPath_Sun(), ON_RDK_SUN_DAYLIGHT_SAVING_MINUTES, 0);
}

void ON_Sun::CImpl::SetDaylightSavingMinutes(int minutes)
{
  SetParameter(XMLPath_Sun(), ON_RDK_SUN_DAYLIGHT_SAVING_MINUTES, minutes);
  _calc_dirty = true;
}

void ON_Sun::CImpl::LocalDateTime(int& year, int& month, int& day, double& hours) const
{
  int dy = 0, dm = 0, dd = 0; double dh = 0.0;
  ON_SunEngine::GetDefaultLocalDateTime(dy, dm, dd, dh);

  const wchar_t* s = XMLPath_Sun();
  year  = GetParameter(s, ON_RDK_SUN_DATE_YEAR,  dy);
  month = GetParameter(s, ON_RDK_SUN_DATE_MONTH, dm);
  day   = GetParameter(s, ON_RDK_SUN_DATE_DAY,   dd);
  hours = GetParameter(s, ON_RDK_SUN_TIME_HOURS, dh);
}

bool ON_Sun::CImpl::SetLocalDateTime(int year, int month, int day, double hours)
{
  year  = std::max(MinYear(), std::min(MaxYear(), year));
  month = std::max(1, std::min(12, month));
  day   = std::max(1, std::min(ON_SunEngine::DaysInMonth(month, year), day));

  const wchar_t* s = XMLPath_Sun();
  SetParameter(s, ON_RDK_SUN_DATE_YEAR,  year);
  SetParameter(s, ON_RDK_SUN_DATE_MONTH, month);
  SetParameter(s, ON_RDK_SUN_DATE_DAY,   day);
  SetParameter(s, ON_RDK_SUN_TIME_HOURS, hours);

  _calc_dirty = true;

  return true;
}

double ON_Sun::CImpl::Intensity(void) const
{
  return GetParameter(XMLPath_Sun(), ON_RDK_SUN_INTENSITY, 1.0);
}

void ON_Sun::CImpl::SetIntensity(double d)
{
  SetParameter(XMLPath_Sun(), ON_RDK_SUN_INTENSITY, std::max(0.0, d));
}

double ON_Sun::CImpl::ShadowIntensity(void) const
{
  // ShadowIntensity is currently unused. See [SHADOW_INTENSITY_UNUSED]
  return GetParameter(XMLPath_Sun(), ON_RDK_SUN_SHADOW_INTENSITY, 1.0);
}

void ON_Sun::CImpl::SetShadowIntensity(double d)
{
  // ShadowIntensity is currently unused. See [SHADOW_INTENSITY_UNUSED]
  SetParameter(XMLPath_Sun(), ON_RDK_SUN_SHADOW_INTENSITY, std::max(0.0, std::min(1.0, d)));
}

double ON_Sun::CImpl::North(void) const
{
  if (nullptr != _earth_anchor_point)
  {
    // Calculate north angle from earth anchor point.
    ON_Plane plane;
    ON_3dVector true_north;
    GetEarthAnchorPlane(true_north, plane);
    return ON_DegreesFromRadians(AngleFromVectors(plane.xaxis, true_north, plane.zaxis));
  }

  // No earth anchor point is set; just return the value in the XML.
  return GetParameter(XMLPath_Sun(), ON_RDK_SUN_NORTH, 90.0).AsDouble();
}

void ON_Sun::CImpl::SetNorth(double north)
{
  // 28th February 2025 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-81036
  // Only set the north if it actually changes.
  if (north == North())
    return;

  if (nullptr != _earth_anchor_point)
  {
    // Store the north in the earth anchor point. This is more complicated than just setting one value.
    ON_Plane plane;
    ON_3dVector true_north;
    GetEarthAnchorPlane(true_north, plane);

    // 29 January 2013 - Kike: Don't use ON_Plane::Rotate without origin.
    // This function doesn't keep the vector length if the axis is the plane's z axis.
    plane.Rotate(ON_RadiansFromDegrees(north - 90.0), plane.zaxis, plane.origin);

    if (!IsVectorEqual(_earth_anchor_point->ModelEast(),  plane.xaxis) ||
        !IsVectorEqual(_earth_anchor_point->ModelNorth(), plane.yaxis))
    {
      _earth_anchor_point->SetModelEast (plane.xaxis);
      _earth_anchor_point->SetModelNorth(plane.yaxis);
    }

    // Make sure this value never appears in the XML. This will clean old documents that were
    // incorrectly saving this value in the XML as well as the earth anchor point.
    RemoveParameter(XMLPath_Sun(), ON_RDK_SUN_NORTH);
  }
  else
  {
    // No earth anchor point is set; store the value in the XML.
    SetParameter(XMLPath_Sun(), ON_RDK_SUN_NORTH, north);
  }

  _calc_dirty = true;
}

double ON_Sun::CImpl::Latitude(void) const
{
  if (nullptr != _earth_anchor_point)
  {
    // Retrieve the latitude from the earth anchor point.
    const double unset_latitude = 0.0;
    return _earth_anchor_point->Latitude(unset_latitude);
  }

  // No earth anchor point is set; just return the value in the XML.
  return GetParameter(XMLPath_Sun(), ON_RDK_SUN_OBSERVER_LATITUDE, 0.0).AsDouble();
}

void ON_Sun::CImpl::SetLatitude(double lat)
{
  // 28th February 2025 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-81036
  // Only set the latitude if it actually changes.
  if (lat == Latitude())
    return;

  if (nullptr != _earth_anchor_point)
  {
    // Store the latitude in the earth anchor point.
    _earth_anchor_point->SetLatitude(lat);

    // Make sure this value never appears in the XML. This will clean old documents that were
    // incorrectly saving this value in the XML as well as the earth anchor point.
    RemoveParameter(XMLPath_Sun(), ON_RDK_SUN_OBSERVER_LATITUDE);
  }
  else
  {
    // No earth anchor point is set; store the value in the XML.
    SetParameter(XMLPath_Sun(), ON_RDK_SUN_OBSERVER_LATITUDE, lat);
  }

  _calc_dirty = true;
}

double ON_Sun::CImpl::Longitude(void) const
{
  if (nullptr != _earth_anchor_point)
  {
    // Retrieve the longitude from the earth anchor point.
    const double unset_longitude = 0.0;
    return _earth_anchor_point->Longitude(unset_longitude);
  }

  // No earth anchor point is set; just return the value in the XML.
  return GetParameter(XMLPath_Sun(), ON_RDK_SUN_OBSERVER_LONGITUDE, 0.0).AsDouble();
}

void ON_Sun::CImpl::SetLongitude(double lon)
{
  // 28th February 2025 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-81036
  // Only set the longitude if it actually changes.
  if (lon == Longitude())
    return;

  if (nullptr != _earth_anchor_point)
  {
    // Store the longitude in the earth anchor point.
    _earth_anchor_point->SetLongitude(lon);

    // Make sure this value never appears in the XML. This will clean old documents that were
    // incorrectly saving this value in the XML as well as the earth anchor point.
    RemoveParameter(XMLPath_Sun(), ON_RDK_SUN_OBSERVER_LONGITUDE);
  }
  else
  {
    // No earth anchor point is set; store the value in the XML.
    SetParameter(XMLPath_Sun(), ON_RDK_SUN_OBSERVER_LONGITUDE, lon);
  }

  _calc_dirty = true;
}

ON_Sun::ON_Sun()
{
  _impl = new CImpl;
}

ON_Sun::ON_Sun(ON_EarthAnchorPoint& eap)
{
  _impl = new CImpl;
  _impl->_earth_anchor_point = &eap;
}

ON_Sun::ON_Sun(ON_XMLNode& model_node)
{
  _impl = new CImpl(model_node);
}

ON_Sun::ON_Sun(const ON_Sun& sun)
{
  _impl = new CImpl;
  operator = (sun);
}

ON_Sun::~ON_Sun()
{
  delete _impl;
  _impl = nullptr;
}

int ON_Sun::MinYear(void)
{
  return 1971;
}

int ON_Sun::MaxYear(void)
{
  return 2199;
}

const ON_Sun& ON_Sun::operator = (const ON_Sun& sun)
{
  if (this != &sun)
  {
    // When copying the object, we need to directly copy the underlying XML. So we can't allow
    // virtual overrides to execute because they might hide the real values we want to copy.
    ON_Sun::SetEnableOn             (sun.ON_Sun::EnableOn());
    ON_Sun::SetEnableAllowed        (sun.ON_Sun::EnableAllowed());
    ON_Sun::SetEnableOn             (sun.ON_Sun::EnableOn());
    ON_Sun::SetManualControlAllowed (sun.ON_Sun::ManualControlAllowed());
    ON_Sun::SetManualControlOn      (sun.ON_Sun::ManualControlOn());
    ON_Sun::SetNorth                (sun.ON_Sun::North());
    ON_Sun::SetDaylightSavingOn     (sun.ON_Sun::DaylightSavingOn());
    ON_Sun::SetDaylightSavingMinutes(sun.ON_Sun::DaylightSavingMinutes());
    ON_Sun::SetAzimuth              (sun.ON_Sun::Azimuth());
    ON_Sun::SetAltitude             (sun.ON_Sun::Altitude());
    ON_Sun::SetLatitude             (sun.ON_Sun::Latitude());
    ON_Sun::SetLongitude            (sun.ON_Sun::Longitude());
    ON_Sun::SetTimeZone             (sun.ON_Sun::TimeZone());
    ON_Sun::SetIntensity            (sun.ON_Sun::Intensity());
    ON_Sun::SetShadowIntensity      (sun.ON_Sun::ShadowIntensity());

    int y = 0, m = 0, d = 0; double h = 0.0;
    sun.ON_Sun::LocalDateTime(y, m, d, h);
    ON_Sun::SetLocalDateTime(y, m, d, h);

    _impl->_azimuth    = sun._impl->_azimuth;
    _impl->_altitude   = sun._impl->_altitude;
    _impl->_calc_dirty = sun._impl->_calc_dirty;
  }

  return *this;
}

bool ON_Sun::operator == (const ON_Sun& sun) const
{
  // When checking equality, we need to directly check the underlying storage. So we can't allow
  // virtual overrides to execute because they might hide the real values we want to check.

  if (ON_Sun::EnableAllowed()         != sun.ON_Sun::EnableAllowed())           return false;
  if (ON_Sun::EnableOn()              != sun.ON_Sun::EnableOn())                return false;
  if (ON_Sun::ManualControlAllowed()  != sun.ON_Sun::ManualControlAllowed())    return false;
  if (ON_Sun::ManualControlOn()       != sun.ON_Sun::ManualControlOn())         return false;
  if (ON_Sun::DaylightSavingOn()      != sun.ON_Sun::DaylightSavingOn())        return false;
  if (ON_Sun::DaylightSavingMinutes() != sun.ON_Sun::DaylightSavingMinutes())   return false;

  if (!IsDoubleEqual(ON_Sun::North()          , sun.ON_Sun::North()))           return false;
  if (!IsDoubleEqual(ON_Sun::Latitude()       , sun.ON_Sun::Latitude()))        return false;
  if (!IsDoubleEqual(ON_Sun::Longitude()      , sun.ON_Sun::Longitude()))       return false;
  if (!IsDoubleEqual(ON_Sun::TimeZone()       , sun.ON_Sun::TimeZone()))        return false;
  if (!IsDoubleEqual(ON_Sun::Intensity()      , sun.ON_Sun::Intensity()))       return false;
  if (!IsDoubleEqual(ON_Sun::ShadowIntensity(), sun.ON_Sun::ShadowIntensity())) return false;

  int y1, m1, d1, y2, m2, d2; double h1, h2;
  ON_Sun::LocalDateTime(y1, m1, d1, h1);
  sun.ON_Sun::LocalDateTime(y2, m2, d2, h2);

  if ((y1 != y2) || (m1 != m2) || (d1 != d2) || !IsDoubleEqual(h1, h2))
    return false;

  if (_impl->IsUsingManualControl())
  {
    if (!IsDoubleEqual(ON_Sun::Azimuth() , sun.ON_Sun::Azimuth()))  return false;
    if (!IsDoubleEqual(ON_Sun::Altitude(), sun.ON_Sun::Altitude())) return false;
  }

  return true;
}

bool ON_Sun::operator != (const ON_Sun& sun) const
{
  return !(operator == (sun));
}

bool ON_Sun::EnableAllowed(void) const
{
  return _impl->EnableAllowed();
}

bool ON_Sun::EnableOn(void) const
{
  return _impl->EnableOn();
}

bool ON_Sun::ManualControlAllowed(void) const
{
  return _impl->ManualControlAllowed();
}

bool ON_Sun::ManualControlOn(void) const
{
  return _impl->ManualControlOn();
}

double ON_Sun::Azimuth(void) const
{
  return _impl->Azimuth();
}

double ON_Sun::Altitude(void) const
{
  return _impl->Altitude();
}

double ON_Sun::TimeZone(void) const
{
  return _impl->TimeZone();
}

double ON_Sun::North(void) const
{
  return _impl->North();
}

double ON_Sun::Latitude(void) const
{
  return _impl->Latitude();
}

double ON_Sun::Longitude(void) const
{
  return _impl->Longitude();
}

bool ON_Sun::DaylightSavingOn(void) const
{
  return _impl->DaylightSavingOn();
}

int ON_Sun::DaylightSavingMinutes(void) const
{
  return _impl->DaylightSavingMinutes();
}

void ON_Sun::LocalDateTime(int& year, int& month, int& day, double& hours) const
{
  _impl->LocalDateTime(year, month, day, hours);
}

void ON_Sun::UTCDateTime(int& year, int& month, int& day, double& hours) const
{
  // Get the local date and time.
  LocalDateTime(year, month, day, hours);

  // Set the local time, timezone and daylight into a helper 'sun'.
  ON_SunEngine engine(_impl->_accuracy);
  engine.SetLocalDateTime(year, month, day, hours);
  engine.SetTimeZoneHours(TimeZone());
  engine.SetDaylightSavingMinutes(DaylightSavingOn() ? DaylightSavingMinutes() : 0);

  // Get the UTC JD and set it as 'local', then get the 'local' (Greenwich) time.
  engine.SetLocalJulianDay(engine.JulianDay());
  engine.LocalDateTime(year, month, day, hours);
}

double ON_Sun::Intensity(void) const
{
  return _impl->Intensity();
}

double ON_Sun::ShadowIntensity(void) const
{
  // ShadowIntensity is currently unused. See [SHADOW_INTENSITY_UNUSED]
  return _impl->ShadowIntensity();
}

void ON_Sun::SetEnableAllowed(bool allowed)
{
  _impl->SetEnableAllowed(allowed);
}

void ON_Sun::SetEnableOn(bool on)
{
  _impl->SetEnableOn(on);
}

void ON_Sun::SetManualControlAllowed(bool allowed)
{
  _impl->SetManualControlAllowed(allowed);
}

void ON_Sun::SetManualControlOn(bool manual)
{
  _impl->SetManualControlOn(manual);
}

void ON_Sun::SetAzimuth(double azi)
{
  _impl->SetAzimuth(azi);
}

void ON_Sun::SetAltitude(double alt)
{
  _impl->SetAltitude(alt);
}

void ON_Sun::SetTimeZone(double hours)
{
  _impl->SetTimeZone(hours);
}

void ON_Sun::SetNorth(double north)
{
  _impl->SetNorth(north);
}

void ON_Sun::SetLatitude(double latitude)
{
  _impl->SetLatitude(latitude);
}

void ON_Sun::SetLongitude(double longitude)
{
  _impl->SetLongitude(longitude);
}

void ON_Sun::SetDaylightSavingOn(bool on)
{
  return _impl->SetDaylightSavingOn(on);
}

void ON_Sun::SetDaylightSavingMinutes(int minutes)
{
  return _impl->SetDaylightSavingMinutes(minutes);
}

bool ON_Sun::SetLocalDateTime(int year, int month, int day, double hours)
{
  return _impl->SetLocalDateTime(year, month, day, hours);
}

bool ON_Sun::SetUTCDateTime(int year, int month, int day, double hours)
{
  // Set the UTC date and time into a helper 'sun' assuming 'local' means 'Greenwich' and get the UTC JD.
  ON_SunEngine engine(_impl->_accuracy);
  engine.SetLocalDateTime(year, month, day, hours);

  // Convert the UTC JD to local JD by adding the timezone and daylight offset,
  // and use the helper 'sun' to get the local date and time.
  const int dsm = DaylightSavingOn() ? DaylightSavingMinutes() : 0;
  engine.SetLocalJulianDay(engine.JulianDay() + (TimeZone() + (dsm / 60.0)) / 24.0);
  engine.LocalDateTime(year, month, day, hours);

  // Set the local date and time.
  return SetLocalDateTime(year, month, day, hours);
}

void ON_Sun::SetIntensity(double d)
{
  _impl->SetIntensity(d);
}

void ON_Sun::SetShadowIntensity(double d)
{
  // ShadowIntensity is currently unused. See [SHADOW_INTENSITY_UNUSED]
  _impl->SetShadowIntensity(d);
}

ON__UINT32 ON_Sun::DataCRC(ON__UINT32 crc) const
{
  // We need to calculate the CRC of the underlying storage, so we can't allow virtual overrides to
  // execute because they might hide the real values we want to use.

  crc = UpdateCRC(crc, ON_Sun::EnableAllowed());
  crc = UpdateCRC(crc, ON_Sun::EnableOn());
  crc = UpdateCRC(crc, ON_Sun::ManualControlAllowed());
  crc = UpdateCRC(crc, ON_Sun::ManualControlOn());
  crc = UpdateCRC(crc, ON_Sun::DaylightSavingOn());
  crc = UpdateCRC(crc, ON_Sun::DaylightSavingMinutes());
  crc = UpdateCRC(crc, Integerize(ON_Sun::Azimuth()));
  crc = UpdateCRC(crc, Integerize(ON_Sun::Altitude()));
  crc = UpdateCRC(crc, Integerize(ON_Sun::North()));
  crc = UpdateCRC(crc, Integerize(ON_Sun::Latitude()));
  crc = UpdateCRC(crc, Integerize(ON_Sun::Longitude()));
  crc = UpdateCRC(crc, Integerize(ON_Sun::TimeZone()));
  crc = UpdateCRC(crc, Integerize(ON_Sun::ShadowIntensity()));
  crc = UpdateCRC(crc, Integerize(ON_Sun::Intensity()));

  int y = 0, m = 0, d = 0; double h = 0.0;
  ON_Sun::LocalDateTime(y, m, d, h);
  crc = UpdateCRC(crc, y);
  crc = UpdateCRC(crc, m);
  crc = UpdateCRC(crc, d);
  crc = UpdateCRC(crc, Integerize(h));

  return crc;
}

#define SUN_ASSERT(x) ON_ASSERT(x); if (!(x)) return false;

bool ON_Sun::IsValid(void) const
{
  // Returns false if SUN_ASSERT fails.

  double hours = 0.0;
  int year = 0, month = 0, day = 0;
  LocalDateTime(year, month, day, hours);
  SUN_ASSERT(year >= MinYear());
  SUN_ASSERT(year <= MaxYear());
  SUN_ASSERT(month >= 1);
  SUN_ASSERT(month <= 12);
  SUN_ASSERT(day >= 1);
  SUN_ASSERT(day <= ON_SunEngine::DaysInMonth(month, year));
  SUN_ASSERT(hours >= 0.0);
  SUN_ASSERT(hours <= 24.0);

  SUN_ASSERT(Azimuth() >= 0.0);
  SUN_ASSERT(Azimuth() <= 360.0)
  SUN_ASSERT(Altitude() >= -90.0);
  SUN_ASSERT(Altitude() <= +90.0);
  SUN_ASSERT(North() >= 0.0);
  SUN_ASSERT(North() <= 360.0)
  SUN_ASSERT(Latitude() >= -90.0);
  SUN_ASSERT(Latitude() <= +90.0);
  SUN_ASSERT(Longitude() >= -180.0);
  SUN_ASSERT(Longitude() <= +180.0);
  SUN_ASSERT(TimeZone() >= -12.0);
  SUN_ASSERT(TimeZone() <= +13.0);
  SUN_ASSERT(DaylightSavingMinutes() >= 0);
  SUN_ASSERT(DaylightSavingMinutes() <= 120);
  SUN_ASSERT(Intensity() >= 0.0);
  SUN_ASSERT(ShadowIntensity() >= 0.0);
  SUN_ASSERT(ShadowIntensity() <= 1.0);

  return true;
}

void ON_Sun::LoadFromXMLNode(const ON_XMLNode& node)
{
  ON_XMLParameters p(node);

  int dy = 0, dm = 0, dd = 0; double dh = 0.0;
  ON_SunEngine::GetDefaultLocalDateTime(dy, dm, dd, dh);

  const auto y = p.GetParam(ON_RDK_SUN_DATE_YEAR,  dy).AsInteger();
  const auto m = p.GetParam(ON_RDK_SUN_DATE_MONTH, dm).AsInteger();
  const auto d = p.GetParam(ON_RDK_SUN_DATE_DAY,   dd).AsInteger();
  const auto h = p.GetParam(ON_RDK_SUN_TIME_HOURS, dh).AsDouble();
  SetLocalDateTime(y, m, d, h);

  SetEnableAllowed        (p.GetParam(ON_RDK_SUN_ENABLE_ALLOWED, false));
  SetEnableOn             (p.GetParam(ON_RDK_SUN_ENABLE_ON, false));
  SetManualControlAllowed (p.GetParam(ON_RDK_SUN_MANUAL_CONTROL_ALLOWED, false));
  SetManualControlOn      (p.GetParam(ON_RDK_SUN_MANUAL_CONTROL_ON, false));
  SetNorth                (p.GetParam(ON_RDK_SUN_NORTH, 90.0));
  SetAzimuth              (p.GetParam(ON_RDK_SUN_AZIMUTH, 0.0));
  SetAltitude             (p.GetParam(ON_RDK_SUN_ALTITUDE, 0.0));
  SetDaylightSavingOn     (p.GetParam(ON_RDK_SUN_DAYLIGHT_SAVING_ON, false));
  SetDaylightSavingMinutes(p.GetParam(ON_RDK_SUN_DAYLIGHT_SAVING_MINUTES, 0));
  SetLatitude             (p.GetParam(ON_RDK_SUN_OBSERVER_LATITUDE, 0.0));
  SetLongitude            (p.GetParam(ON_RDK_SUN_OBSERVER_LONGITUDE, 0.0));
  SetTimeZone             (p.GetParam(ON_RDK_SUN_OBSERVER_TIMEZONE, 0));
  SetShadowIntensity      (p.GetParam(ON_RDK_SUN_SHADOW_INTENSITY, 1.0));
  SetIntensity            (p.GetParam(ON_RDK_SUN_INTENSITY, 1.0));
}

void ON_Sun::SaveToXMLNode(ON_XMLNode& node) const
{
  ON_XMLParameters p(node);

  int y = 0, m = 0, d = 0; double h = 0.0;
  LocalDateTime(y, m, d, h);

  p.SetParam(ON_RDK_SUN_DATE_YEAR , y);
  p.SetParam(ON_RDK_SUN_DATE_MONTH, m);
  p.SetParam(ON_RDK_SUN_DATE_DAY  , d);
  p.SetParam(ON_RDK_SUN_TIME_HOURS, h);
  p.SetParam(ON_RDK_SUN_ENABLE_ALLOWED         , EnableAllowed());
  p.SetParam(ON_RDK_SUN_ENABLE_ON              , EnableOn());
  p.SetParam(ON_RDK_SUN_MANUAL_CONTROL_ALLOWED , ManualControlAllowed());
  p.SetParam(ON_RDK_SUN_MANUAL_CONTROL_ON      , ManualControlOn());
  p.SetParam(ON_RDK_SUN_NORTH                  , North());
  p.SetParam(ON_RDK_SUN_AZIMUTH                , Azimuth());
  p.SetParam(ON_RDK_SUN_ALTITUDE               , Altitude());
  p.SetParam(ON_RDK_SUN_DAYLIGHT_SAVING_ON     , DaylightSavingOn());
  p.SetParam(ON_RDK_SUN_DAYLIGHT_SAVING_MINUTES, DaylightSavingMinutes());
  p.SetParam(ON_RDK_SUN_OBSERVER_LATITUDE      , Latitude());
  p.SetParam(ON_RDK_SUN_OBSERVER_LONGITUDE     , Longitude());
  p.SetParam(ON_RDK_SUN_OBSERVER_TIMEZONE      , TimeZone());
  p.SetParam(ON_RDK_SUN_SHADOW_INTENSITY       , ShadowIntensity());
  p.SetParam(ON_RDK_SUN_INTENSITY              , Intensity());
}

ON_4fColor ON_Sun::SunColorFromAltitude(double altitude) // Static.
{
  ON_4fColor colDark(0, 0, 64, 255);

  if (altitude < -TwilightZone())
    return colDark;

  const double value = (30.0 * pow(std::max(0.0, altitude), 1.5)) + 500.0;
  auto temperature = std::min(5300.0, value);

  ON_4fColor col = ColorTemperature(temperature);

  if (altitude < 0.0)
  {
    const double dBlend = -altitude / TwilightZone();
    col.BlendTo(float(dBlend), colDark);
  }

  return col;
}

bool ON_Sun::IsValidDateTime(int y, int m, int d, int h, int n, int s) // Static.
{
	if ((h < 0) || (n < 0) || (s < 0))
		return false;

	if ((h > 23) || (n > 59) || (s > 59))
		return false;

	if ((y < ON_Sun::MinYear()) || (m < 1) || (d < 1))
		return false;

	if ((y > ON_Sun::MaxYear()) || (m > 12) || (d > ON_SunEngine::DaysInMonth(m, y)))
		return false;

	return true;
}

static ON_UUID uuidFeatureSun = { 0x62ee2cf6, 0xb855, 0x4549, { 0xa2, 0x77, 0xe2, 0xbb, 0xf6, 0x09, 0xf3, 0x28 } };

ON_Light ON_Sun::Light(void) const
{
  ON_Light light;
  light.Enable(false);
  light.SetStyle(ON::world_directional_light);
  light.SetLocation(ON_3dPoint(0.0, 0.0, 0.0));
  light.SetIntensity(Intensity());
  light.SetShadowIntensity(ShadowIntensity());

  if (IsValid())
  {
    const auto vec = CalculateVectorFromAzimuthAndAltitude();
    light.SetDirection(vec);

    const bool on = EnableOn();
    light.Enable(on);

    const auto col = SunColorFromAltitude(Altitude());
    light.SetDiffuse(col);
  }

  light.m_light_id = uuidFeatureSun;

  return light;
}

ON_3dVector ON_Sun::CalculateVectorFromAzimuthAndAltitude(void) const
{
	const double azimuth = Azimuth() + WorldToCompass(North());

	double d[3] = { 0 };
	ON_SunEngine::ConvertHorizonCoordsToSolarVector(azimuth, Altitude(), d);

	return ON_3dVector(d);
}

void ON_Sun::SetAzimuthAndAltitudeFromVector(const ON_3dVector& v)
{
  ON_3dVector vec = v;
  vec.Unitize();

  double azimuth = 0.0, altitude = 0.0;

  const double d[3] = { vec.x, vec.y, vec.z };
  ON_SunEngine::ConvertSolarVectorToHorizonCoords(d, azimuth, altitude);

  azimuth -= WorldToCompass(North());
  SetAzimuth(azimuth);

  SetAltitude(altitude);
}

void ON_Sun::SetXMLNode(ON_XMLNode& node) const
{
  _impl->SetModelNode(node);
}

void ON_Sun::UseEarthAnchorPoint(ON_EarthAnchorPoint& eap)
{
  _impl->_earth_anchor_point = &eap;
}

ON_SunEngine::Accuracy ON_Sun::Accuracy(void) const
{
  return _impl->_accuracy;
}

void ON_Sun::SetAccuracy(ON_SunEngine::Accuracy acc)
{
  _impl->_accuracy = acc;
}

void* ON_Sun::EVF(const wchar_t* func, void* data)
{
  return nullptr;
}

void ON_Sun::OnInternalXmlChanged(const ON_Sun* sun)
{
  if (nullptr != sun)
  {
    // The XML has been bulk-overwritten from other XML by the client code. We must now copy the
    // north, latitude and longitude values from the other sun into this one in case one or the
    // other sun is using the earth anchor point for those values instead of the XML.
    SetNorth(sun->North());
    SetLatitude(sun->Latitude());
    SetLongitude(sun->Longitude());
  }

  // 18th March 2025 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-86536
  // Since the XML has been bulk-overwritten, we need to make sure the sun calculation is done next time
  // Azimuth() or Altitude() is called. This bug was introduced by the fix for RH-81036 because that fix
  // prevented code which had the side-effect of setting _calc_dirty from being executed.
  _impl->_calc_dirty = true;
}

static const int SunVersion = 1;

bool ON_Sun::WriteToArchive(ON_BinaryArchive& archive) const
{
  if (!archive.WriteInt(SunVersion))
    return false;

  ON_XMLRootNode root;
  SaveToXMLNode(root);

  auto length_wide = root.WriteToStream(nullptr, 0);
  if (length_wide <= 0)
    return false;

  ON_wString sXML;
  sXML.ReserveArray(size_t(length_wide + 1));
  length_wide = root.WriteToStream(sXML.Array(), length_wide);
  if (length_wide <= 0)
    return false;

  const auto* wsz = static_cast<const wchar_t*>(sXML);

  const auto length_utf8 = ON_ConvertWideCharToUTF8(false, wsz, -1, nullptr, 0, nullptr, 0, 0, nullptr);
  auto utf8 = std::unique_ptr<char[]>(new char[length_utf8]);
  auto* pUTF8 = utf8.get();
  ON_ConvertWideCharToUTF8(false, wsz, -1, pUTF8, length_utf8, nullptr, 0, 0, nullptr);

  // Write the length of the UTF8 buffer to the archive.
  if (!archive.WriteInt(length_utf8))
    return false;

  // Write the UTF8 buffer to the archive.
  if (!archive.WriteChar(length_utf8, pUTF8))
    return false;

  return true;
}

bool ON_Sun::ReadFromArchive(ON_BinaryArchive& archive)
{
  int version = 0;
  if (!archive.ReadInt(&version))
    return false;

  if (SunVersion != version)
    return false;

  int length_utf8 = 0;
  if (!archive.ReadInt(&length_utf8))
    return false;

  auto utf8 = std::unique_ptr<char[]>(new char[size_t(length_utf8)+1]);
  auto* pUTF8 = utf8.get();

  if (!archive.ReadChar(length_utf8, pUTF8))
    return false;

  pUTF8[length_utf8] = 0; // Terminator.

  const auto length_wide = ON_ConvertUTF8ToWideChar(false, pUTF8, -1, nullptr, 0, nullptr, 0, 0, nullptr);
  auto wide = std::unique_ptr<wchar_t[]>(new wchar_t[length_wide + 1]);
  auto* pWide = wide.get();
  ON_ConvertUTF8ToWideChar(false, pUTF8, -1, pWide, length_wide + 1, nullptr, 0, 0, nullptr);

  ON_XMLRootNode root;
  root.ReadFromStream(pWide);
  LoadFromXMLNode(root);

  return true;
}

static void _DecimalHoursToHMS(double hours, int& hour, int& minute, int& second)
{
  while (hours >= 24.0)
    hours -= 24.0;

  while (hours < 0.0)
    hours += 24.0;

  hour = int(hours);

  const double min = (hours - hour) * 60.0;
  minute = int(min);

  const double sec = (min - minute) * 60.0;
  second = int(sec + 0.5); // 'second' could now be 60.
}

void ON_DecimalHoursToHMS(double hours, int& hour, int& minute, int& second)
{
  _DecimalHoursToHMS(hours, hour, minute, second);

  if (second > 59)
    second = 59;
}

void ON_DecimalHoursToHMS(double hours, int& hour, int& minute, int& second, int& year, int& month, int& day)
{
  _DecimalHoursToHMS(hours, hour, minute, second);

  if (second > 59)
  {
    second = 0;

    if (++minute > 59)
    {
      minute = 0;

      if (++hour > 23)
      {
        hour = 0;

        if (++day > int(ON_DaysInMonthOfGregorianYear(year, month)))
        {
          day = 1;

          if (++month > 12)
          {
            month = 1;
            year++;
          }
        }
      }
    }
  }
}

double ON_DecimalHoursFromHMS(int hour, int minute, int second)
{
  return hour + (minute / 60.0) + (second / 3600.0);
}
