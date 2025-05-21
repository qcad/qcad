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

#if !defined(ON_SUN_INC_)
#define ON_SUN_INC_

// Class ON_SunEngine is a sun astronomical calculation engine.

class ON_CLASS ON_SunEngine
{
public:
  enum class Accuracy
  {
    Minimum, // Suitable for doing many calculations when you just need rough results quickly.
    Maximum, // Suitable for generating accurate tables of sun positions (e.g., an ephemeris).
  };

  ON_SunEngine(Accuracy a);
  ON_SunEngine(const ON_SunEngine&);
  virtual ~ON_SunEngine();

  const ON_SunEngine& operator = (const ON_SunEngine&);

  bool operator == (const ON_SunEngine& e);
  bool operator != (const ON_SunEngine& e);

  // Return the latitude of the observer in degrees.
  virtual double Latitude(void) const;

  // Return the longitude of the observer in degrees.
  virtual double Longitude(void) const;

  // Set the latitude of the observer in degrees. Must be in the range -90 to +90.
  // This value is used by the calculation of the sun's azimuth and altitude.
  // Returns true if latitude is valid, else false.
  virtual bool SetLatitude(double dLat);

  // Set the longitude of the observer in degrees. Must be in the range -180 to +180.
  // This value is used by the calculation of the sun's azimuth and altitude.
  // Returns true if longitude is valid, else false.
  virtual bool SetLongitude(double dLong);

  // Set the time zone of the observer in hours. Must be in the range -12 to +13.
  // Returns true if hours is valid, else false.
  virtual bool SetTimeZoneHours(double dHours);

  // Set the daylight saving of the observer in minutes. Must be in the range 0 to 120.
  // Returns true if minutes is valid, else false.
  virtual bool SetDaylightSavingMinutes(int iMinutes);

  // Set the local date and time of the observer. The date must lie between 1800 and 2199 inclusive.
  // The time is supplied as decimal hours which must be in the range 0 to 24.
  // Returns true if date and time are valid, else false.
  virtual bool SetLocalDateTime(int iYear, int iMonth, int iDay, double dHours);

  // Set the local Julian Day of the observer. Optional alternative to calling SetLocalDateTime().
  // Returns true if Julian Day is valid, else false.
  virtual bool SetLocalJulianDay(double dLocalJulianDay);

  // Returns The azimuth of the sun in degrees.
  virtual double Azimuth(void) const;

  // Returns The altitude of the sun in degrees.
  virtual double Altitude(void) const;

  // Returns The Julian Day corresponding to Universal Time (UT ~ GMT).
  virtual double JulianDay(void) const;

  // Returns The Julian Day corresponding to local time.
  virtual double LocalJulianDay(void) const;

  // Returns The time zone of the observer in hours.
  virtual double TimeZoneHours(void) const;

  // Returns The daylight saving of the observer in minutes.
  virtual int DaylightSavingMinutes(void) const;

  // Gets the local date and time of the observer.
  // Param year accepts the year in the range 1800 to 2199.
  // Param month accepts the month in the range 1 to 12.
  // Param day accepts the day in the range 1 to 31.
  // Param hours accepts the hour in the range 0 to 24.
  virtual void LocalDateTime(int& year, int& month, int& day, double& hours) const;

  // Helper function; returns the number of days in a month for a specific year.
  static int DaysInMonth(int month, int year);

  // Helper function; converts azimuth and altitude to unit vector.
  static void ConvertHorizonCoordsToSolarVector(double dAzimuth, double dAltitude, double* dVector);

  // Helper function; converts unit vector to azimuth and altitude.
  static void ConvertSolarVectorToHorizonCoords(const double* dVector, double& dAzimuth, double& dAltitude);

  // Helper function; gets the current local date and time.
  static void GetCurrentLocalDateTime(int& y, int& m, int& d, double& h);

  // Helper function; gets the default local date and time.
  // This is March 21st of the current year at 12:00 noon local time.
  static void GetDefaultLocalDateTime(int& y, int& m, int& d, double& h);

private:
  class CImpl;
  CImpl* _impl;
};

// Class ON_Sun represents a 'sun'. It can calculate the apparent position of the sun in the sky
// at a particular instant for a particular location on the Earth's surface. It can also be used
// to get the sun's color, a light representing the sun, or to generate an ephemeris.

class ON_CLASS ON_Sun
{
public:
  ON_Sun();
  ON_Sun(ON_EarthAnchorPoint& eap);
  ON_Sun(ON_XMLNode& model_node);
  ON_Sun(const ON_Sun& sun);
  virtual ~ON_Sun();

  // Returns the minimum allowed year for sun methods.
  static int MinYear(void);

  // Returns the maximum allowed year for sun methods.
  static int MaxYear(void);

  virtual const ON_Sun& operator = (const ON_Sun& sun);

  virtual bool operator == (const ON_Sun& sun) const;
  virtual bool operator != (const ON_Sun& sun) const;

  // Returns true if enabling/disabling the sun is allowed, else false.
  virtual bool EnableAllowed(void) const;

  // Returns true if the sun is enabled, else false.
  virtual bool EnableOn(void) const;

  // Returns true if manual control of the sun position is allowed, else false.
  virtual bool ManualControlAllowed(void) const;

  // Returns true if manual control of the sun position is in effect, else false.
  virtual bool ManualControlOn(void) const;

  // Returns The world angle corresponding to North in degrees.
  // This angle is zero along the x-axis and increases anticlockwise.
  virtual double North(void) const;

  // Returns the azimuth of the sun in degrees. The value increases Eastwards with North as zero.
  // Note: This value is not affected by the direction of north. See North().
  virtual double Azimuth(void) const;

  // Returns the altitude of the sun in degrees.
  virtual double Altitude(void) const;

  // Returns the latitude of the observer.
  virtual double Latitude(void) const;

  // Returns the longitude of the observer.
  virtual double Longitude(void) const;

  // Returns the time zone of the observer in decimal hours.
  virtual double TimeZone(void) const;

  // Returns true if daylight saving is on, else false.
  virtual bool DaylightSavingOn(void) const;

  // Returns the daylight saving offset of the observer in minutes.
  virtual int DaylightSavingMinutes(void) const;

  // Retrieves the local date and time of the observer.
  // Param year accepts the year in the range MinYear() to MaxYear().
  // Param month accepts the month in the range 1 to 12.
  // Param day accepts the day in the range 1 to 31.
  // Param hours accepts the time expressed as decimal hours in the range 0 to 24.
  // Returns The local date and time of the observer.
  virtual void LocalDateTime(int& year, int& month, int& day, double& hours) const;

  // Returns the intensity to be used for the sun. This is 1.0 by default.
  virtual double Intensity(void) const;

  // This is currently unused.
  virtual double ShadowIntensity(void) const;

  // Set whether or not enabling/disabling the sun is allowed.
  virtual void SetEnableAllowed(bool allowed);

  // Set whether or not the sun is enabled.
  virtual void SetEnableOn(bool on);

  // Set whether or not manual control of the sun position is allowed.
  virtual void SetManualControlAllowed(bool allowed);

  // Set whether or not manual control of the sun position is in effect.
  virtual void SetManualControlOn(bool manual);

  // Set the azimuth corresponding to North.
  // north is the world angle corresponding to North in degrees in the range 0 to 360.
  // This angle is zero along the x-axis and increases anticlockwise.
  virtual void SetNorth(double north);

  // Set the azimuth of the sun when manual control is in effect.
  // Param azimuth is the sun's azimuth in degrees. The value increases Eastwards with North as zero.
  // Note: This value is not affected by the direction of north.
  virtual void SetAzimuth(double azimuth);

  // Set the sun's altitude when manual control is in effect.
  // Param altitude is the sun's altitude in degrees in the range -90 to +90.
  virtual void SetAltitude(double altitude);

  // Set the latitude of the observer.
  // Param latitude is the observer's latitude in degrees in the range -90 to +90.
  virtual void SetLatitude(double latitude);

  // Set the longitude of the observer.
  // Param longitude is the observer's longitude in degrees in the range -180 to +180.
  virtual void SetLongitude(double longitude);

  // Set the time zone of the observer in hours, in the range -12 to +13.
  virtual void SetTimeZone(double hours);

  // Set whether or not the observer is using daylight saving time.
  virtual void SetDaylightSavingOn(bool on);

  // Set the daylight saving of the observer in minutes, in the range 0 to 120.
  virtual void SetDaylightSavingMinutes(int minutes);

  // Set the local date and time of the observer.
  // Param year is the year which must lie between MinYear() to MaxYear() inclusive.
  // Param month is the month in the range 1 to 12.
  // Param day is the day in the range 1 to 31.
  // Param hours is the time expressed as decimal hours in the range 0 to 24.
  // Returns true if successful, false if the date is out of range.
  virtual bool SetLocalDateTime(int year, int month, int day, double hours);

  // This is currently unused.
  virtual void SetShadowIntensity(double intensity);

  // Set the intensity to be used for the sun.  This is 1.0 by default.
  virtual void SetIntensity(double intensity);

  // Returns the CRC of the sun state.
  virtual ON__UINT32 DataCRC(ON__UINT32 current_remainder) const;

  // Returns true if all the sun parameters are valid, or false if any value is invalid.
  virtual bool IsValid(void) const;

  // Load the sun properties from a 'sun' XML node.
	virtual void LoadFromXMLNode(const ON_XMLNode& node);

  // Save the sun properties to a 'sun' XML node.
	virtual void SaveToXMLNode(ON_XMLNode& node) const;

  // Write the sun properties to an archive.
  virtual bool WriteToArchive(ON_BinaryArchive& archive) const;

  // Read the sun properties from an archive that was created by WriteToArchive().
  virtual bool ReadFromArchive(ON_BinaryArchive& archive);

  // Emergency virtual function for future expansion.
  virtual void* EVF(const wchar_t* func, void* data);

  // For internal use only.
  virtual void OnInternalXmlChanged(const ON_Sun*);

  // Get the accuracy of the sun calculations. The default is minimum accuracy (for more speed).
  virtual ON_SunEngine::Accuracy Accuracy(void) const;

  // Set the accuracy of the sun calculations. The default is minimum accuracy (for more speed).
  virtual void SetAccuracy(ON_SunEngine::Accuracy acc);

  // Get a color for rendering a sun light when the sun is at a particular altitude in the sky.
  static ON_4fColor SunColorFromAltitude(double altitude);

  // Returns true if the specified time is within the range supported by ON_Sun.
  static bool IsValidDateTime(int year, int month, int day, int hour, int min, int sec);

public: // These utility methods are provided for convenience and perform calculations by using ON_SunEngine.

  // Get an ON_Light which represents the sun. Note that this does not actually calculate the sun's
  // azimuth or altitude from the place and time. It merely uses the stored azimuth and altitude values.
  virtual ON_Light Light(void) const;

  // Retrieves the date and time of the observer expressed in Coordinated Universal Time. This is the same
  // as the local date and time adjusted for the observer's time zone and daylight saving.
  // Param year accepts the year in the range MinYear() to MaxYear().
  // Param month accepts the month in the range 1 to 12.
  // Param day accepts the day in the range 1 to 31.
  // Param hours accepts the time expressed as decimal hours in the range 0 to 24.
  // Returns The UTC date and time of the observer.
  virtual void UTCDateTime(int& year, int& month, int& day, double& hours) const;

  // Set the date and time of the observer expressed in Coordinated Universal Time. This is the same
  // as the local date and time adjusted for the observer's time zone and daylight saving.
  // Param year is the year which must lie between MinYear() to MaxYear() inclusive.
  // Param month is the month in the range 1 to 12.
  // Param day is the day in the range 1 to 31.
  // Param hours is the time expressed as decimal hours in the range 0 to 24.
  // Returns true if successful, false if the date is out of range.
  virtual bool SetUTCDateTime(int year, int month, int day, double hours);

  // Returns The sun's direction vector in world space, taking into account the sun's azimuth and
  // altitude and the direction of north. Note that this does not actually calculate the azimuth or
  // altitude from the place and time; it merely uses the stored azimuth and altitude values.
  virtual ON_3dVector CalculateVectorFromAzimuthAndAltitude(void) const;

  // Calculates and sets the sun's azimuth and altitude taking into account the direction of north.
  virtual void SetAzimuthAndAltitudeFromVector(const ON_3dVector& v);

private: // For internal use only.
  friend class ON_3dmRenderSettingsPrivate;
  void SetXMLNode(ON_XMLNode& node) const;
  friend class ONX_Model;
  void UseEarthAnchorPoint(ON_EarthAnchorPoint& eap);

private:
  class CImpl;
  CImpl* _impl;
};

/*
Description:
  Converts a time specified as hour, minute and second to a decimal hours value.
  Example: hour=9, minute=30, second=0 -> result is 9.5
Parameters:
  hour   - [in] The hour value of the time.
  minute - [in] The minute value of the time.
  second - [in] The second value of the time.
Returns:
  The decimal hours value corresponding to the hour, minute and second.
*/
ON_DECL double ON_DecimalHoursFromHMS(int hour, int minute, int second);

/*
Description:
  Converts a time specified as decimal hours to hour, minute and second.
  Guaranteed to produce a valid hour, minute and second result.
  Example: hours=9.5 -> result is hour=9, minute=30, second=0.

Parameters:
  hours  - [in]  The decimal hours value of the time. If not in range 0..23 it will be 'unwound' to be in range.
  hour   - [out] The hour value of the time specified by 'hours'.
  minute - [out] The minute value of the time specified by 'hours'.
  second - [out] The second value of the time specified by 'hours'.
*/
ON_DECL void ON_DecimalHoursToHMS(double hours, int& hour, int& minute, int& second);

/*
Description:
  Converts a time specified as decimal hours to hour, minute and second.
  Guaranteed to produce a valid hour, minute and second result.
  Example: hours=9.5 -> result is hour=9, minute=30, second=0.
  Because of rounding, a value such as 23.99999 will come out as midnight the next day.
  Therefore, the year, month and day are also passed in so that they can be adjusted if necessary.
  Example: hours=23.99999 -> result is hour=0, minute=0, second=0 and date is incremented by one day.

Parameters:
  hours  - [in]  The decimal hours value of the time. If not in range 0..23 it will be 'unwound' to be in range.
  hour   - [out] The hour value of the time specified by 'hours'.
  minute - [out] The minute value of the time specified by 'hours'.
  second - [out] The second value of the time specified by 'hours'.
  year   - [in/out] The year value of the date, adjusted if necessary.
  month  - [in/out] The month value of the date, adjusted if necessary.
  day    - [in/out] The day value of the date, adjusted if necessary.
*/
ON_DECL void ON_DecimalHoursToHMS(double hours, int& hour, int& minute, int& second, int& year, int& month, int& day);

#endif
