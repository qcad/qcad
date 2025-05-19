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

//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmUnitsAndTolerances
//

static double ON_Internal_UnitSystemCtorMetersPerUnit(
  ON::LengthUnitSystem length_unit_system
)
{
  double meters_per_unit;
  switch (length_unit_system)
  {
  case ON::LengthUnitSystem::None:
    meters_per_unit = 1.0;
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
  case ON::LengthUnitSystem::Microinches:
  case ON::LengthUnitSystem::Mils:
  case ON::LengthUnitSystem::Inches:
  case ON::LengthUnitSystem::Feet:
  case ON::LengthUnitSystem::Yards:
  case ON::LengthUnitSystem::Miles:
  case ON::LengthUnitSystem::PrinterPoints:
  case ON::LengthUnitSystem::PrinterPicas:
  case ON::LengthUnitSystem::NauticalMiles:
  case ON::LengthUnitSystem::AstronomicalUnits:
  case ON::LengthUnitSystem::LightYears:
  case ON::LengthUnitSystem::Parsecs:
    meters_per_unit = ON::UnitScale(length_unit_system, ON::LengthUnitSystem::Meters);
    break;
  case ON::LengthUnitSystem::CustomUnits:
    meters_per_unit = 1.0;
    break;
  case ON::LengthUnitSystem::Unset:
    meters_per_unit = ON_DBL_QNAN;
    break;
  default:
    meters_per_unit = ON_DBL_QNAN;
    break;
  }
  return meters_per_unit;
}


ON_UnitSystem::ON_UnitSystem(ON::LengthUnitSystem length_unit_system)
: m_unit_system(ON::LengthUnitSystemFromUnsigned(static_cast<unsigned int>(length_unit_system)))
, m_meters_per_custom_unit(ON_Internal_UnitSystemCtorMetersPerUnit(m_unit_system))
{}

ON_UnitSystem& ON_UnitSystem::operator=(
  ON::LengthUnitSystem length_unit_system
  )
{
  *this = ON_UnitSystem(length_unit_system);
  return *this;
}


bool ON_UnitSystem::operator==(const ON_UnitSystem& other) const
{
  if ( m_unit_system != other.m_unit_system )
    return false;

  if ( ON::LengthUnitSystem::CustomUnits == m_unit_system )
  {
    if ( !(m_meters_per_custom_unit == other.m_meters_per_custom_unit) )
      return false;
    if ( false == m_custom_unit_name.EqualOrdinal(other.m_custom_unit_name,false) )
      return false;
  }

  return true;
}

bool ON_UnitSystem::operator!=(const ON_UnitSystem& other) const
{
  if ( m_unit_system != other.m_unit_system )
    return true;

  if ( ON::LengthUnitSystem::CustomUnits == m_unit_system )
  {
    if (m_meters_per_custom_unit != other.m_meters_per_custom_unit)
      return true;
    if ( false == m_custom_unit_name.EqualOrdinal(other.m_custom_unit_name,false) )
      return true;
  }

  return false;
}

bool ON_UnitSystem::IsValid() const
{
  if ( m_unit_system != ON::LengthUnitSystemFromUnsigned(static_cast<unsigned int>(m_unit_system)) )
  {
    // invalid enum value
    return false;
  }

  if (ON::LengthUnitSystem::Unset == m_unit_system)
    return false;

  if (ON::LengthUnitSystem::CustomUnits == m_unit_system)
  {
    if (false == ON_IsValidPositiveNumber(m_meters_per_custom_unit))
      return false;
  }

  return true;
}

bool ON_UnitSystem::IsSet() const
{
  return (ON::LengthUnitSystem::Unset != m_unit_system && ON::LengthUnitSystem::None != m_unit_system && IsValid() );
}

bool ON_UnitSystem::IsCustomUnitSystem() const
{
  return (ON::LengthUnitSystem::CustomUnits == m_unit_system && IsSet());
}

void ON_UnitSystem::SetUnitSystem(
  ON::LengthUnitSystem us
  )
{
  *this = ON_UnitSystem(us);
}

ON_UnitSystem ON_UnitSystem::CreateCustomUnitSystem(
  const wchar_t* custom_unit_name,
  double meters_per_custom_unit
)
{
  ON_UnitSystem custom_unit_system = ON_UnitSystem::Unset;
  custom_unit_system.SetCustomUnitSystem(custom_unit_name, meters_per_custom_unit);
  return custom_unit_system;
}

void ON_UnitSystem::SetCustomUnitSystem(
  const wchar_t* custom_unit_name,
  double meters_per_custom_unit
  )
{
  ON_wString local_str(custom_unit_name);
  local_str.TrimLeftAndRight();
  m_unit_system = ON::LengthUnitSystem::CustomUnits;
  m_custom_unit_name = local_str;
  if ( ON_IsValidPositiveNumber(meters_per_custom_unit) )
  {
    m_meters_per_custom_unit = meters_per_custom_unit;
  }
  else
  {
    ON_ERROR("Invalid meters_per_custom_unit parameter");
    m_meters_per_custom_unit = 1.0; // must be > 0.0 and < ON_UNSET_POSITIVE_VALUE
  }
}

void ON_UnitSystem::SetCustomUnitSystemName(
  const wchar_t* custom_unit_name
  )
{
  const bool bIsCustomUnitSystem = (ON::LengthUnitSystem::CustomUnits == m_unit_system);
  ON_wString local_name(custom_unit_name);
  local_name.TrimLeftAndRight();
  if (local_name.IsNotEmpty() || bIsCustomUnitSystem)
  {
    const double meters_per_custom_unit
      = bIsCustomUnitSystem
      ? m_meters_per_custom_unit
      : 1.0;
    SetCustomUnitSystem(local_name, meters_per_custom_unit);
  }
}

void ON_UnitSystem::SetCustomUnitSystemScale(
  double meters_per_custom_unit
  )
{
  if (ON_IsValidPositiveNumber(meters_per_custom_unit))
  {
    const bool bIsCustomUnitSystem = (ON::LengthUnitSystem::CustomUnits == m_unit_system);
    if (false == (meters_per_custom_unit == m_meters_per_custom_unit) || bIsCustomUnitSystem)
    {
      const ON_wString unit_system_name
        = (ON::LengthUnitSystem::CustomUnits == m_unit_system)
        ? m_custom_unit_name
        : ON_wString::EmptyString;
      SetCustomUnitSystem(unit_system_name, meters_per_custom_unit);
    }
  }
}

double ON_UnitSystem::MetersPerUnit(
  double unset_return_value
) const
{
  switch (m_unit_system)
  {
  case ON::LengthUnitSystem::None:
    return 1.0;
    break;
  case ON::LengthUnitSystem::CustomUnits:
    return m_meters_per_custom_unit;
    break;
  case ON::LengthUnitSystem::Unset:
    return unset_return_value;
    break;
  default:
    break;
  }
  return ON::UnitScale(m_unit_system, ON::LengthUnitSystem::Meters);
}

double ON_UnitSystem::MillimetersPerUnit(
  double unset_return_value
) const
{
  switch (m_unit_system)
  {
  case ON::LengthUnitSystem::None:
    return 1.0;
    break;
  case ON::LengthUnitSystem::CustomUnits:
    return 1000.0*m_meters_per_custom_unit;
    break;
  case ON::LengthUnitSystem::Unset:
    return unset_return_value;
    break;
  default:
    break;
  }
  return ON::UnitScale(m_unit_system, ON::LengthUnitSystem::Millimeters);
}

double ON_UnitSystem::MetersPerUnit() const
{
  // NOTE WELL:
  //   https://mcneel.myjetbrains.com/youtrack/issue/RH-60700
  //   For standard units, this function returns the WRONG value (inverse of the correct value).
  //   The reason is the Rhino 6 VRay plug-in assumes the incorrect value is returned
  //   and V6 VRay does not work correctly in Rhino 7 if the correct value is returned.
  //   After some discussion (see the bug above), we will leave the inverse bug in
  //   ON_UnitSystem::MetersPerUnit(), deprecate ON_UnitSystem::MetersPerUnit(),
  //   and add a new function that returns the correct answer.
  if (ON::LengthUnitSystem::CustomUnits == m_unit_system)
  {
    // correct answer for custom units - V6 behavior.
    return m_meters_per_custom_unit; //
  }


  // For standard units, the inverse of the correct answer is returned
  // to preserve V6 bug so VRay works in Rhino 7.
  return 1.0/ON_UnitSystem::MetersPerUnit(ON_DBL_QNAN);
}

ON::LengthUnitSystem ON_UnitSystem::UnitSystem() const
{
  return m_unit_system;
}

static void ON_Internal_InitUnitSystemName(
  const wchar_t* name,
  ON_wString& local_storage
  )
{
  if (local_storage.IsEmpty())
    local_storage = name;
}

const ON_wString& ON_UnitSystem::UnitSystemName() const
{
  switch (m_unit_system)
  {
  case ON::LengthUnitSystem::None:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"no units",s_name);
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::Angstroms:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"angstroms",s_name);
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::Nanometers:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"nanometers",s_name);
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::Microns:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"microns",s_name);
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::Millimeters:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"millimeters",s_name);
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::Decimeters:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"decimeters",s_name);
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::Centimeters:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"centimeters",s_name);
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::Meters:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"meters",s_name);
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::Dekameters:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"dekameters",s_name);
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::Hectometers:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"hectometers",s_name);
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::Kilometers:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"kilometers",s_name);
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::Megameters:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"megameters",s_name);
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::Gigameters:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"gigameters",s_name);
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::Microinches:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"microinches",s_name);
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::Mils:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"mils",s_name);// (= 0.001 inches)";
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::Inches:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"inches",s_name);
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::Feet:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"feet",s_name);
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::Yards:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"yards",s_name);
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::Miles:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"miles",s_name);
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::PrinterPoints:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"points",s_name); // (1/72 inch)";
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::PrinterPicas:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"picas",s_name); // (1/6 inch)";
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::NauticalMiles:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"nautical miles",s_name);
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::AstronomicalUnits:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"astronomical units",s_name);
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::LightYears:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"light years",s_name);
      return s_name;
    }
    break;
  case ON::LengthUnitSystem::Parsecs:
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"parsecs",s_name);
      return s_name;
    }
    break;

  case ON::LengthUnitSystem::CustomUnits:
    if (m_custom_unit_name.IsEmpty())
    {
      static ON_wString s_name;
      ON_Internal_InitUnitSystemName(L"custom units", s_name);
      return s_name;
    }
    return m_custom_unit_name;
    break;

  case ON::LengthUnitSystem::Unset:
    {
    static ON_wString s_name;
    ON_Internal_InitUnitSystemName(L"unset", s_name);
    return s_name;
    }
    break;
  }

  return ON_wString::EmptyString;
}


bool ON_UnitSystem::Read( ON_BinaryArchive& file )
{
  *this = ON_UnitSystem::None;

  int major_version = 0;
  int minor_version = 0;
  
  if ( !file.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version) )
    return false;

  ON::LengthUnitSystem us = ON::LengthUnitSystem::None;
  double meters_per_unit  = 0.0;
  ON_wString custom_unit_name;
  bool rc = false;
  for (;;)
  {

    if (1 != major_version)
      break;
    unsigned int i = ON_UNSET_UINT_INDEX;
    if (false == file.ReadInt(&i))
      break;
    us = ON::LengthUnitSystemFromUnsigned(i);
    if (false == file.ReadDouble(&meters_per_unit))
      break;
    if (false == file.ReadString(custom_unit_name))
      break;
    rc = true;
    break;
  }

  if (!file.EndRead3dmChunk())
  {
    rc = false;
  }
  else
  {
    if (ON::LengthUnitSystem::CustomUnits == us)
    {
      m_unit_system = us;
      m_custom_unit_name = custom_unit_name;
      m_meters_per_custom_unit = meters_per_unit;
    }
    else
    {
      *this = ON_UnitSystem(us);
    }
  }

  return rc;
}

bool ON_UnitSystem::Write( ON_BinaryArchive& file ) const
{
  if ( !file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0) )
    return false;


  // values saved in the file
  //no_unit_system =  0, 
  //microns        =  1,  // 1.0e-6 meters
  //millimeters    =  2,  // 1.0e-3 meters
  //centimeters    =  3,  // 1.0e-2 meters
  //meters         =  4,
  //kilometers     =  5,  // 1.0e+3 meters
  //microinches    =  6,  // 1.0e-6 inches
  //mils           =  7,  // 1.0e-3 inches
  //inches         =  8,  // 0.0254 meters
  //feet           =  9,  // 12 inches
  //miles          = 10,  // 63360 inches
  //custom_unit_system = 11, // x meters with x defined in ON_3dmUnitsAndTolerances.m_custom_unit_scale

  bool rc = false;
  for (;;)
  {
    if (!file.WriteInt(static_cast<unsigned int>(m_unit_system)))
      break;
    if (!file.WriteDouble(ON::LengthUnitSystem::CustomUnits == m_unit_system ? m_meters_per_custom_unit : ON::UnitScale(m_unit_system, ON::LengthUnitSystem::Meters)))
      break;
    if (!file.WriteString(ON::LengthUnitSystem::CustomUnits == m_unit_system ? m_custom_unit_name : ON_wString::EmptyString))
      break;
    rc = true;
    break;
  }

  if ( !file.EndWrite3dmChunk() )
    rc = false;

  return rc;
}

const ON_wString ON_UnitSystem::ToString() const
{
  ON_wString str(UnitSystemName());
  if (ON::LengthUnitSystem::CustomUnits == m_unit_system)
  {
    ON_wString meters_per_unit;
    meters_per_unit.Format(L" (= %g meters )", m_meters_per_custom_unit);
    str += meters_per_unit;
  }
  return str;

}

void ON_UnitSystem::Dump( ON_TextLog& dump ) const
{
  const ON_wString sUnitSystem(ToString());
  dump.Print("Unit system: %ls\n",static_cast<const wchar_t*>(sUnitSystem));
}

bool ON_3dmUnitsAndTolerances::operator==(const ON_3dmUnitsAndTolerances& other) const
{
  bool equal = m_unit_system == other.m_unit_system
    && m_absolute_tolerance == other.m_absolute_tolerance
    && m_angle_tolerance == other.m_angle_tolerance
    && m_relative_tolerance == other.m_relative_tolerance
    && m_distance_display_mode == other.m_distance_display_mode
    && m_distance_display_precision == other.m_distance_display_precision;
  return equal;
}

bool ON_3dmUnitsAndTolerances::operator!=(const ON_3dmUnitsAndTolerances& other) const
{
  return !(*this == other);
}

bool ON_3dmUnitsAndTolerances::Write( ON_BinaryArchive& file ) const
{
  const int version = 102;
  unsigned int i;

  // version 100 ON_3dmUnitsAndTolerances settings
  bool rc = file.WriteInt( version );
  i = static_cast<unsigned int>(m_unit_system.UnitSystem());
  if ( rc ) rc = file.WriteInt( i );
  if ( rc ) rc = file.WriteDouble( m_absolute_tolerance );
  if ( rc ) rc = file.WriteDouble( m_angle_tolerance );
  if ( rc ) rc = file.WriteDouble( m_relative_tolerance );

  // added in version 101
  i = static_cast<unsigned int>(m_distance_display_mode);
  if ( rc ) rc = file.WriteInt( i );
  i = m_distance_display_precision;
  if ( i > 20 ) 
  {
    ON_ERROR("ON_3dmUnitsAndTolerances::Write() - m_distance_display_precision out of range.");
    i = 3;
  }
  if ( rc ) rc = file.WriteInt( i );

  // added in version 102
  if ( rc ) rc = file.WriteDouble( m_unit_system.MetersPerUnit(ON_DBL_QNAN));
  if ( rc ) rc = file.WriteString( (ON::LengthUnitSystem::CustomUnits == m_unit_system.UnitSystem() ? m_unit_system.UnitSystemName() : ON_wString::EmptyString) );
  return rc;
}

bool ON_3dmUnitsAndTolerances::Read( ON_BinaryArchive& file )
{
  *this = ON_3dmUnitsAndTolerances::Millimeters;
  int version = 0;
  bool rc = file.ReadInt( &version );
  if ( rc && version >= 100 && version < 200 )
  {
    ON::LengthUnitSystem us = ON::LengthUnitSystem::None;
    double meters_per_unit = 1.0;
    ON_wString custom_unit_name;

    int i = ON_UNSET_UINT_INDEX;
    rc = file.ReadInt( &i );
    if ( rc )
      us = ON::LengthUnitSystemFromUnsigned(i);
    if ( rc ) rc = file.ReadDouble( &m_absolute_tolerance );
    if ( rc ) rc = file.ReadDouble( &m_angle_tolerance );
    if ( rc ) rc = file.ReadDouble( &m_relative_tolerance );
    if ( version >= 101 ) 
    {
      unsigned int dm = static_cast<unsigned int>(ON::OBSOLETE_DistanceDisplayMode::Decimal);
      if ( rc ) rc = file.ReadInt( &dm );
      if ( rc ) m_distance_display_mode = ON::DistanceDisplayModeFromUnsigned(dm);
      if ( rc ) rc = file.ReadInt( &m_distance_display_precision );
      if ( m_distance_display_precision < 0 || m_distance_display_precision > 20 )
        m_distance_display_precision = 3; // some beta files had bogus values stored in file
      if ( version >= 102 ) 
      {
        if ( rc ) rc = file.ReadDouble( &meters_per_unit );
        if ( rc ) rc = file.ReadString( custom_unit_name );
      }
    }
    if ( ON::LengthUnitSystem::CustomUnits == us )
      m_unit_system.SetCustomUnitSystem(custom_unit_name,meters_per_unit);
    else
      m_unit_system.SetUnitSystem(us);
  }
  return rc;
}

void ON_3dmUnitsAndTolerances::Dump( ON_TextLog& dump) const
{
  m_unit_system.Dump(dump);
  dump.Print("Absolute tolerance: %g\n",m_absolute_tolerance);
  dump.Print("Angle tolerance: %g\n",m_angle_tolerance);
}

double ON_3dmUnitsAndTolerances::Scale( ON::LengthUnitSystem us ) const
{
  // Example: If us = meters and m_unit_system = centimeters,
  // then Scale() returns 100.
  return ON::UnitScale( us, m_unit_system );
}

bool ON_3dmUnitsAndTolerances::IsValid() const
{
  for (;;)
  {
    // April 17, 2023 - Tim
    // Changed upper limit to 8 so we can use the display precision
    // stuff found in the annotation code for V8
    // Fixes https://mcneel.myjetbrains.com/youtrack/issue/RH-74242
    if (!(m_distance_display_precision >= 0 && m_distance_display_precision <= 8))
      break;

    if (!((int)m_distance_display_mode >= 0 && (int)m_distance_display_mode <= 3))
      break;

    if (!TolerancesAreValid())
      break;

    return true;
  }
  return false;
}

double ON_3dmUnitsAndTolerances::AbsoluteTolerance() const
{
  return m_absolute_tolerance;
}

void ON_3dmUnitsAndTolerances::SetAbsoluteTolerance(double absolute_tolerance)
{
  if (absolute_tolerance > 0.0)
    m_absolute_tolerance = absolute_tolerance;
}

double ON_3dmUnitsAndTolerances::AngleTolerance() const
{
  return m_angle_tolerance;
}

void ON_3dmUnitsAndTolerances::SetAngleTolerance(double angle_tolerance)
{
  if (angle_tolerance > 0.0 && angle_tolerance <= ON_PI)
    m_angle_tolerance = angle_tolerance;
}

double ON_3dmUnitsAndTolerances::RelativeTolerance() const
{
  return m_relative_tolerance;
}

void ON_3dmUnitsAndTolerances::SetRelativeTolerance(double relative_tolerance)
{
  if (relative_tolerance > 0.0 && relative_tolerance < 1.0)
    m_relative_tolerance = relative_tolerance;
}

ON::OBSOLETE_DistanceDisplayMode ON_3dmUnitsAndTolerances::DistanceDisplayMode() const
{
  return m_distance_display_mode;
}

void ON_3dmUnitsAndTolerances::SetDistanceDisplayMode(ON::OBSOLETE_DistanceDisplayMode distance_display_mode)
{
  m_distance_display_mode = distance_display_mode;
}

int ON_3dmUnitsAndTolerances::DistanceDisplayPrecision() const
{
  return m_distance_display_precision;
}

void ON_3dmUnitsAndTolerances::SetDistanceDisplayPrecision(int distance_display_precision)
{
  // April 17, 2023 - Tim
  // Changed upper limit to 8 so we can use the display precision
  // stuff found in the annotation code for V8
  // Fixes https://mcneel.myjetbrains.com/youtrack/issue/RH-74242
  if (distance_display_precision >= 0 && distance_display_precision <= 8)
    m_distance_display_precision = distance_display_precision;
}

bool ON_3dmUnitsAndTolerances::TolerancesAreValid() const
{
  for (;;)
  {
    if (!(m_absolute_tolerance > 0.0))
      break;

    if (!(m_angle_tolerance > 0.0 && m_angle_tolerance <= ON_PI))
      break;

    if (!(m_relative_tolerance > 0.0 && m_relative_tolerance < 1.0))
      break;

    return true;
  }
  return false;
}

unsigned int ON_3dmUnitsAndTolerances::SetInvalidTolerancesToDefaultValues()
{
  unsigned int rc = 0;

  if ( !(m_absolute_tolerance > 0.0) )
  {
    rc |= 1;
    // Do NOT apply scaling from mm to current units.
    m_absolute_tolerance = ON_3dmUnitsAndTolerances::Millimeters.m_absolute_tolerance;
  }

  if ( !(m_angle_tolerance > 0.0 && m_angle_tolerance <= ON_PI) )
  {
    rc |= 2;
    m_angle_tolerance = ON_3dmUnitsAndTolerances::Millimeters.m_angle_tolerance;
  }

  if ( !( m_relative_tolerance > 0.0 && m_relative_tolerance < 1.0) )
  {
    rc |= 4;
    m_relative_tolerance = ON_3dmUnitsAndTolerances::Millimeters.m_relative_tolerance;
  }

  return rc;
}

//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmRenderSettings
//

static const wchar_t* XMLPathBack360(void) // Not used for 'override'.
{
  return ON_RDK_DOCUMENT  ON_XML_SLASH  ON_RDK_CURRENT_CONTENT;
}

static const wchar_t* XMLPathReflRefr(void)
{
  return ON_RDK_DOCUMENT  ON_XML_SLASH  ON_RDK_SETTINGS  ON_XML_SLASH  ON_RDK_RENDERING;
}

static const wchar_t* XMLPathSkylight(void)
{
  return ON_RDK_DOCUMENT  ON_XML_SLASH  ON_RDK_SETTINGS  ON_XML_SLASH  ON_RDK_SUN;
}

ON_EnvironmentsImpl::ON_EnvironmentsImpl(const ON_EnvironmentsImpl& ei)
{
  operator = (ei);
}

ON_EnvironmentsImpl& ON_EnvironmentsImpl::operator = (const ON_EnvironmentsImpl& ep)
{
  if (this != &ep)
  {
    SetBackgroundRenderEnvironmentId       (ep.BackgroundRenderEnvironmentId());
    SetSkylightingRenderEnvironmentOverride(ep.SkylightingRenderEnvironmentOverride());
    SetSkylightingRenderEnvironmentId      (ep.SkylightingRenderEnvironmentId());
    SetReflectionRenderEnvironmentOverride (ep.ReflectionRenderEnvironmentOverride());
    SetReflectionRenderEnvironmentId       (ep.ReflectionRenderEnvironmentId());
  }

  return *this;
}

bool ON_EnvironmentsImpl::operator == (const ON_EnvironmentsImpl& ep)
{
  if (BackgroundRenderEnvironmentId()        != ep.BackgroundRenderEnvironmentId())        return false;
  if (SkylightingRenderEnvironmentOverride() != ep.SkylightingRenderEnvironmentOverride()) return false;
  if (SkylightingRenderEnvironmentId()       != ep.SkylightingRenderEnvironmentId())       return false;
  if (ReflectionRenderEnvironmentOverride()  != ep.ReflectionRenderEnvironmentOverride())  return false;
  if (ReflectionRenderEnvironmentId()        != ep.ReflectionRenderEnvironmentId())        return false;

  return true;
}

ON_UUID ON_EnvironmentsImpl::BackgroundRenderEnvironmentId(void) const
{
  return GetParameter_NoType(XMLPathBack360(), ON_RDK_BACKGROUND_ENVIRONMENT, L"uuid", ON_nil_uuid).AsUuid();
}

void ON_EnvironmentsImpl::SetBackgroundRenderEnvironmentId(const ON_UUID& id)
{
  SetParameter_NoType(XMLPathBack360(), ON_RDK_BACKGROUND_ENVIRONMENT, id);
}

bool ON_EnvironmentsImpl::SkylightingRenderEnvironmentOverride(void) const
{
  return GetParameter(XMLPathSkylight(), ON_RDK_SUN_SKYLIGHT_ENVIRONMENT_OVERRIDE, false);
}

void ON_EnvironmentsImpl::SetSkylightingRenderEnvironmentOverride(bool on)
{
  SetParameter(XMLPathSkylight(), ON_RDK_SUN_SKYLIGHT_ENVIRONMENT_OVERRIDE, on);
}

ON_UUID ON_EnvironmentsImpl::SkylightingRenderEnvironmentId(void) const
{
  return GetParameter_NoType(XMLPathSkylight(), ON_RDK_SUN_SKYLIGHT_ENVIRONMENT_ID, L"uuid", ON_nil_uuid).AsUuid();
}

void ON_EnvironmentsImpl::SetSkylightingRenderEnvironmentId(const ON_UUID& id)
{
  SetParameter_NoType(XMLPathSkylight(), ON_RDK_SUN_SKYLIGHT_ENVIRONMENT_ID, id);
}

bool ON_EnvironmentsImpl::ReflectionRenderEnvironmentOverride(void) const
{
  return GetParameter(XMLPathReflRefr(), ON_RDK_CUSTOM_REFLECTIVE_ENVIRONMENT_ON, false);
}

void ON_EnvironmentsImpl::SetReflectionRenderEnvironmentOverride(bool on)
{
  SetParameter(XMLPathReflRefr(), ON_RDK_CUSTOM_REFLECTIVE_ENVIRONMENT_ON, on);
}

ON_UUID ON_EnvironmentsImpl::ReflectionRenderEnvironmentId(void) const
{
  return GetParameter_NoType(XMLPathReflRefr(), ON_RDK_CUSTOM_REFLECTIVE_ENVIRONMENT, L"uuid", ON_nil_uuid).AsUuid();
}

void ON_EnvironmentsImpl::SetReflectionRenderEnvironmentId(const ON_UUID& id)
{
  SetParameter_NoType(XMLPathReflRefr(), ON_RDK_CUSTOM_REFLECTIVE_ENVIRONMENT, id);
}

ON_OBJECT_IMPLEMENT(ON_3dmRenderSettings, ON_Object, "58A5953A-57C5-4FD3-84F5-7D4240478D15");

ON_DECL ON_XMLNode& ON_GetRdkDocNode(const ON_3dmRenderSettings& rs)
{
  return ON_3dmRenderSettingsPrivate::Get(rs)._rdk_document_data;
}

ON_DECL ON__UINT_PTR ON_GetDocumentObjectSpecializer(const ON_3dmRenderSettings& rs)
{
  return ON__UINT_PTR(&ON_3dmRenderSettingsPrivate::Get(rs));
}

ON_DECL void ON_SpecializeDocumentObjects(ON__UINT_PTR specializer,
             ON_GroundPlane& gp, ON_LinearWorkflow& lw, ON_Sun& sun)
{
  auto* priv = reinterpret_cast<ON_3dmRenderSettingsPrivate*>(specializer);
  ON_ASSERT(nullptr != priv);
  if (nullptr != priv)
  {
    priv->SpecializeGroundPlane(gp);
    priv->SpecializeLinearWorkflow(lw);
    priv->SpecializeSun(sun);
  }
}

ON_3dmRenderSettingsPrivate::ON_3dmRenderSettingsPrivate()
{
  CreateDocumentObjects();

  // 26th January 2023 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-71396
  // Populate the RDK document data with defaults. The previous fix for this did it in RdkDocNode()
  // which was the wrong place. We have to do it even if the RDK isn't being used.
  ON_RdkDocumentDefaults dd(ON::VersionMajor(), ON_RdkDocumentDefaults::ValueSets::All);
  dd.CopyDefaultsTo(_rdk_document_data);
}

ON_3dmRenderSettingsPrivate::ON_3dmRenderSettingsPrivate(const ON_3dmRenderSettingsPrivate& p)
{
  CreateDocumentObjects();
  operator = (p);
}

ON_3dmRenderSettingsPrivate::~ON_3dmRenderSettingsPrivate()
{
  delete _ground_plane;
  delete _dithering;
  delete _safe_frame;
  delete _skylight;
  delete _linear_workflow;
  delete _render_channels;
  delete _sun;
  delete _environments;
  delete _post_effects;
}

const ON_3dmRenderSettingsPrivate& ON_3dmRenderSettingsPrivate::operator = (const ON_3dmRenderSettingsPrivate& p)
{
  if (this != &p)
  {
    // Copy the entire document XML.
    _rdk_document_data = p._rdk_document_data;

    // Notify the document objects that the XML has changed. Some of these objects maintain caches and
    // other data structures that must be kept in synch with the XML. This gives them a chance to update
    // any such information. Note that the pointers to these objects are never null because they are
    // created in every constructor. See CreateDocumentObjects().
    // It's critical that the document objects do not get deleted or recreated here because there can be
    // clients storing temporary pointers to them around this call. What's more, this function can never
    // change the class of the document objects. For example, if the ground plane is a specialized one,
    // it will always be the _same_ specialized one. They never get deleted during the lifetime of this.
    _ground_plane   ->OnInternalXmlChanged(p._ground_plane   );
    _dithering      ->OnInternalXmlChanged(p._dithering      );
    _safe_frame     ->OnInternalXmlChanged(p._safe_frame     );
    _skylight       ->OnInternalXmlChanged(p._skylight       );
    _linear_workflow->OnInternalXmlChanged(p._linear_workflow);
    _render_channels->OnInternalXmlChanged(p._render_channels);
    _sun            ->OnInternalXmlChanged(p._sun            );
    _post_effects   ->OnInternalXmlChanged(p._post_effects   );

#ifdef _DEBUG // See https://mcneel.myjetbrains.com/youtrack/issue/RH-77284

    // Check that all the document objects now have matching properties.
    ON_ASSERT(*_ground_plane    == *p._ground_plane);
    ON_ASSERT(*_dithering       == *p._dithering);
    ON_ASSERT(*_safe_frame      == *p._safe_frame);
    ON_ASSERT(*_skylight        == *p._skylight);
    ON_ASSERT(*_linear_workflow == *p._linear_workflow);
    ON_ASSERT(*_render_channels == *p._render_channels);
    ON_ASSERT(*_sun             == *p._sun);
    ON_ASSERT(*_environments    == *p._environments);

    // We can't check post effects because they may be different in terms of the _is_populated flag.
    // After a lot of thinking, I simply cannot figure out how to solve this.
    //_ASSERT(*_post_effects    == *p._post_effects);
#endif
  }

  return *this;
}

ON_3dmRenderSettings::~ON_3dmRenderSettings()
{
  if (nullptr != m_private)
  {
    delete m_private;
    m_private = nullptr;
  }
}

void ON_3dmRenderSettingsPrivate::CreateDocumentObjects(void)
{
  // This function must be called from every constructor.
  _ground_plane    = new ON_GroundPlane     (_rdk_document_data);
  _dithering       = new ON_Dithering       (_rdk_document_data);
  _safe_frame      = new ON_SafeFrame       (_rdk_document_data);
  _skylight        = new ON_Skylight        (_rdk_document_data);
  _linear_workflow = new ON_LinearWorkflow  (_rdk_document_data);
  _render_channels = new ON_RenderChannels  (_rdk_document_data);
  _sun             = new ON_Sun             (_rdk_document_data);
  _environments    = new ON_EnvironmentsImpl(_rdk_document_data);
  _post_effects    = new ON_PostEffects     (_rdk_document_data);
}

ON_3dmRenderSettingsPrivate& ON_3dmRenderSettingsPrivate::Get(const ON_3dmRenderSettings& rs)
{
  if (nullptr == rs.m_private)
    rs.m_private = new ON_3dmRenderSettingsPrivate;

  return *rs.m_private;
}

ON_3dmRenderSettings::ON_3dmRenderSettings(const ON_3dmRenderSettings& rs)
{
  operator = (rs);
}

ON_3dmRenderSettings& ON_3dmRenderSettings::operator = (const ON_3dmRenderSettings& rs)
{
  if (this != &rs)
  {
    ON_Object::operator = (rs);

    if (nullptr != rs.m_private)
    {
      if (nullptr == m_private)
      {
        m_private = new ON_3dmRenderSettingsPrivate(*rs.m_private);
      }
      else
      {
        *m_private = *rs.m_private;
      }
    }
    else
    {
      if (nullptr != m_private)
      {
        // We can't delete the private because it might have specialized document objects (gp etc).
        // So don't delete it, but set it to defaults because the incoming one doesn't exist which
        // is essentially the same as the incoming one being an implied default one.
        m_private->SetToDefaults();
      }
    }

    m_ambient_light              = rs.m_ambient_light;
    m_antialias_style            = rs.m_antialias_style;
    m_background_bitmap_filename = rs.m_background_bitmap_filename;
    m_background_bottom_color    = rs.m_background_bottom_color;
    m_background_color           = rs.m_background_color;
    m_background_style           = rs.m_background_style;
    m_bCustomImageSize           = rs.m_bCustomImageSize;
    m_bDepthCue                  = rs.m_bDepthCue;
    m_bFlatShade                 = rs.m_bFlatShade;
    m_bForceViewportAspectRatio  = rs.m_bForceViewportAspectRatio;
    m_bRenderAnnotation          = rs.m_bRenderAnnotation;
    m_bRenderBackfaces           = rs.m_bRenderBackfaces;
    m_bRenderCurves              = rs.m_bRenderCurves;
    m_bRenderIsoparams           = rs.m_bRenderIsoparams;
    m_bRenderMeshEdges           = rs.m_bRenderMeshEdges;
    m_bRenderPoints              = rs.m_bRenderPoints;
    m_bScaleBackgroundToFit      = rs.m_bScaleBackgroundToFit;
    m_bTransparentBackground     = rs.m_bTransparentBackground;
    m_bUseHiddenLights           = rs.m_bUseHiddenLights;
    m_bUsesAmbientAttr           = rs.m_bUsesAmbientAttr;
    m_bUsesAnnotationAttr        = rs.m_bUsesAnnotationAttr;
    m_bUsesBackfaceAttr          = rs.m_bUsesBackfaceAttr;
    m_bUsesBackgroundAttr        = rs.m_bUsesBackgroundAttr;
    m_bUsesCurvesAttr            = rs.m_bUsesCurvesAttr;
    m_bUsesHiddenLightsAttr      = rs.m_bUsesHiddenLightsAttr;
    m_bUsesIsoparmsAttr          = rs.m_bUsesIsoparmsAttr;
    m_bUsesMeshEdgesAttr         = rs.m_bUsesMeshEdgesAttr;
    m_bUsesPointsAttr            = rs.m_bUsesPointsAttr;
    m_embedded_image_file_id     = rs.m_embedded_image_file_id;
    m_image_dpi                  = rs.m_image_dpi;
    m_image_height               = rs.m_image_height;
    m_image_us                   = rs.m_image_us;
    m_image_width                = rs.m_image_width;
    m_named_view                 = rs.m_named_view;
    m_rendering_source           = rs.m_rendering_source;
    m_reserved1                  = rs.m_reserved1;
    m_reserved3                  = rs.m_reserved3;
    m_reserved4                  = rs.m_reserved4;
    m_reserved5                  = rs.m_reserved5;
    m_reserved6                  = rs.m_reserved6;
    m_reserved7                  = rs.m_reserved7;
    m_reserved8                  = rs.m_reserved8;
    m_shadowmap_height           = rs.m_shadowmap_height;
    m_shadowmap_offset           = rs.m_shadowmap_offset;
    m_shadowmap_style            = rs.m_shadowmap_style;
    m_shadowmap_width            = rs.m_shadowmap_width;
    m_snapshot                   = rs.m_snapshot;
    m_specific_viewport          = rs.m_specific_viewport;
  }

  return *this;
}

void ON_3dmRenderSettingsPrivate::SetToDefaults(void)
{
  ON_RdkDocumentDefaults dd(ON::VersionMajor(), ON_RdkDocumentDefaults::ValueSets::All);
  dd.CopyDefaultsTo(_rdk_document_data);
}

void ON_3dmRenderSettingsPrivate::SpecializeGroundPlane(ON_GroundPlane& gp)
{
  // This is called from ON_SpecializeDocumentObjects() and is only called once during the lifetime of this.
  ON_ASSERT(!_gp_specialized);

  // Make the incoming object use the document data of this.
  gp.SetXMLNode(_rdk_document_data);

  // Replace the vanilla ground plane with the incoming object. This takes ownership of it.
  delete _ground_plane;
  _ground_plane = &gp;

  _gp_specialized = true;
}

void ON_3dmRenderSettingsPrivate::SpecializeLinearWorkflow(ON_LinearWorkflow& lw)
{
  // This is called from ON_SpecializeDocumentObjects() and is only called once during the lifetime of this.
  ON_ASSERT(!_lw_specialized);

  // Make the incoming object use the document data of this.
  lw.SetXMLNode(_rdk_document_data);

  // Replace the vanilla linear workflow with the incoming object. This takes ownership of it.
  delete _linear_workflow;
  _linear_workflow = &lw;

  _lw_specialized = true;
}

void ON_3dmRenderSettingsPrivate::SpecializeSun(ON_Sun& sun)
{
  // This is called from ON_SpecializeDocumentObjects() and is only called once during the lifetime of this.
  ON_ASSERT(!_sun_specialized);

  // Make the incoming object use the document data of this.
  sun.SetXMLNode(_rdk_document_data);

  // Replace the vanilla sun with the incoming object. This takes ownership of it.
  delete _sun;
  _sun = &sun;

  _sun_specialized = true;
}

void ON_3dmRenderSettings::Dump( ON_TextLog& text_log ) const
{
  text_log.Print("m_bCustomImageSize = %s\n",m_bCustomImageSize?"true":"false");
  text_log.Print("m_image_width = %d\n",m_image_width);
  text_log.Print("m_image_height = %d\n",m_image_height);
  text_log.Print("m_image_dpi = %g\n",m_image_dpi);
  text_log.Print("m_image_us = %d\n",m_image_us);
  text_log.Print("m_ambient_light rgb = ");text_log.PrintRGB(m_ambient_light);text_log.Print("\n");
  text_log.Print("m_background_style = %d\n",m_background_style);
  text_log.Print("m_background_color rgb = ");text_log.PrintRGB(m_background_color);text_log.Print("\n");
  text_log.Print("m_background_bitmap_filename = ");text_log.Print(m_background_bitmap_filename);text_log.Print("\n");
  text_log.Print("m_bUseHiddenLights = %s\n",m_bUseHiddenLights?"true":"false");
  text_log.Print("m_bDepthCue = %s\n",m_bDepthCue?"true":"false");
  text_log.Print("m_bFlatShade = %s\n",m_bFlatShade?"true":"false");
  text_log.Print("m_bRenderBackfaces = %s\n",m_bRenderBackfaces?"true":"false");
  text_log.Print("m_bRenderPoints = %s\n",m_bRenderPoints?"true":"false");
  text_log.Print("m_bRenderCurves = %s\n",m_bRenderCurves?"true":"false");
  text_log.Print("m_bRenderIsoparams = %s\n",m_bRenderIsoparams?"true":"false");
  text_log.Print("m_bRenderMeshEdges = %s\n",m_bRenderMeshEdges?"true":"false");
  text_log.Print("m_bRenderAnnotation = %s\n",m_bRenderAnnotation?"true":"false");

  text_log.Print("m_antialias_style = %d\n",m_antialias_style);
  text_log.Print("m_shadowmap_style = %d\n",m_shadowmap_style);
  text_log.Print("m_shadowmap_width = %d\n",m_shadowmap_width);
  text_log.Print("m_shadowmap_height = %d\n",m_shadowmap_height);
  text_log.Print("m_shadowmap_offset = %g\n",m_shadowmap_offset);

  text_log.Print("m_bScaleBackgroundToFit = %s\n",m_bScaleBackgroundToFit?"true":"false");

  text_log.Print(L"m_rendering_source = %u\n", int(m_rendering_source));
  text_log.Print(L"m_specific_viewport = %s\n", (const wchar_t*)m_specific_viewport);
  text_log.Print(L"m_named_view = %s\n", (const wchar_t*)m_named_view);
  text_log.Print(L"m_snapshot = %s\n", (const wchar_t*)m_snapshot);

  text_log.Print("m_bForceViewportAspectRatio = %s\n", m_bForceViewportAspectRatio ? "true" : "false");

  // 19th April 2023 John Croudy. I thought it would be handy to add the RDK XML for debugging.
  // I didn't know that the state of the text log is checked with a hash by the OpenNURBS tests.
  // Since the RDK XML can change textually (e.g., different property order), the string is never
  // guaranteed to be the same for the same actual XML state. Therefore, this broke the OpenNURBS tests.
  //const auto& priv = ON_3dmRenderSettingsPrivate::Get(*this);
  //const auto s = priv._rdk_document_data.NodeForRead().String();
  //text_log.Print("RDK XML = ");
  //text_log.PrintString(s);
}

bool ON_3dmRenderSettings::UseV5ReadWrite(const ON_BinaryArchive& file)
{
  if ( file.Archive3dmVersion() <= 50 )
    return true;
  
  if ( file.Archive3dmVersion() > 60 )
    return false;

  // Prior to  November 5, 2013, version 6 files used the old V5 format.
  unsigned int v6_2013_11_05_version = ON_VersionNumberConstruct(6,0,2013,11,5,0);
  unsigned int archive_opennurbs_version = file.ArchiveOpenNURBSVersion();
  return (archive_opennurbs_version < v6_2013_11_05_version);
}

bool ON_3dmRenderSettings::Write( ON_BinaryArchive& file ) const
{
  if ( ON_3dmRenderSettings::UseV5ReadWrite(file) )
    return WriteV5(file);

  // November 5, 2013 V6 files and later
  // March 11th 2016 "1.1"- adds focal blur data
  // June  20th 2017 "1.2"- adds rendering source data
  if ( !file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,3) )
    return false;

  bool rc = false;
  for(;;)
  {
    if ( !file.WriteBool( m_bCustomImageSize ) ) break;
    if ( !file.WriteInt( m_image_width ) ) break;
    if ( !file.WriteInt( m_image_height ) ) break;

    if ( !file.WriteDouble( m_image_dpi ) ) break;
    if ( !file.WriteInt( (int)m_image_us ) ) break;

    if ( !file.WriteColor( m_ambient_light ) ) break;

    if ( !file.WriteInt( m_background_style ) ) break;
    if ( !file.WriteColor( m_background_color ) ) break;
    if ( !file.WriteColor( m_background_bottom_color ) ) break;
    if ( !file.WriteString( m_background_bitmap_filename ) ) break;

    if ( !file.WriteBool( m_bUseHiddenLights ) ) break;
    if ( !file.WriteBool( m_bDepthCue ) ) break;
    if ( !file.WriteBool( m_bFlatShade ) ) break;
    if ( !file.WriteBool( m_bRenderBackfaces ) ) break;
    if ( !file.WriteBool( m_bRenderPoints ) ) break;
    if ( !file.WriteBool( m_bRenderCurves ) ) break;
    if ( !file.WriteBool( m_bRenderIsoparams ) ) break;
    if ( !file.WriteBool( m_bRenderMeshEdges ) ) break;
    if ( !file.WriteBool( m_bRenderAnnotation ) ) break;
    if ( !file.WriteBool( m_bScaleBackgroundToFit ) ) break;
    if ( !file.WriteBool( m_bTransparentBackground ) ) break;

    if ( !file.WriteInt( m_antialias_style ) ) break;
    if ( !file.WriteInt( m_shadowmap_style ) ) break;
    if ( !file.WriteInt( m_shadowmap_width ) ) break;
    if ( !file.WriteInt( m_shadowmap_height ) ) break;
    if ( !file.WriteDouble( m_shadowmap_offset ) ) break;

	// March 11th 2016 "1.1"- adds focal blur data
	// ALB. June 24th 2017 - this information is now on ON_3dmView.  Write default values.  Note, these values were never in Rhino 5.0 files.
	//http://mcneel.myjetbrains.com/youtrack/issue/RH-32342
	if (!file.WriteInt((int)0)) break;
	if (!file.WriteDouble(100.0)) break;
	if (!file.WriteDouble(64.0)) break;
	if (!file.WriteDouble(0.1)) break;
	if (!file.WriteInt(10)) break;

	// June 20th 2017 "1.2"- adds rendering source data
	//https://mcneel.myjetbrains.com/youtrack/issue/RH-39593
	if (!file.WriteInt((int)m_rendering_source)) break;
	if (!file.WriteString(m_specific_viewport)) break;
	if (!file.WriteString(m_named_view)) break;
	if (!file.WriteString(m_snapshot)) break;

  // September 28th 2017 "1.3"- adds aspect ratio lock
  if (!file.WriteBool(m_bForceViewportAspectRatio)) break;

    rc = true;
    break;
  }  

  if ( !file.EndWrite3dmChunk() )
    rc = false;

  return rc;
}

bool ON_3dmRenderSettings::WriteV5( ON_BinaryArchive& file ) const
{
  unsigned int i;
  // version 103: 11 November 2010
  const int version = 103;
  bool rc = file.WriteInt( version );
  // version >= 100
  if (rc) rc = file.WriteInt( m_bCustomImageSize );
  if (rc) rc = file.WriteInt( m_image_width );
  if (rc) rc = file.WriteInt( m_image_height );
  if (rc) rc = file.WriteColor( m_ambient_light );
  if (rc) rc = file.WriteInt( m_background_style );
  if (rc) rc = file.WriteColor( m_background_color );
  if (rc) rc = file.WriteString( m_background_bitmap_filename );
  if (rc) rc = file.WriteInt( m_bUseHiddenLights );
  if (rc) rc = file.WriteInt( m_bDepthCue );
  if (rc) rc = file.WriteInt( m_bFlatShade );

  // 26 August 2003 Dale Lear:
  //     When saving V2 files, turn on backfaces. RR 11656
  //
  i = (file.Archive3dmVersion() >= 3) ? m_bRenderBackfaces : 1;
  if (rc) rc = file.WriteInt( i );

  if (rc) rc = file.WriteInt( m_bRenderPoints );
  if (rc) rc = file.WriteInt( m_bRenderCurves );
  if (rc) rc = file.WriteInt( m_bRenderIsoparams );
  if (rc) rc = file.WriteInt( m_bRenderMeshEdges );
  if (rc) rc = file.WriteInt( m_bRenderAnnotation );
  if (rc) rc = file.WriteInt( m_antialias_style );
  if (rc) rc = file.WriteInt( m_shadowmap_style );
  if (rc) rc = file.WriteInt( m_shadowmap_width );
  if (rc) rc = file.WriteInt( m_shadowmap_height );
  if (rc) rc = file.WriteDouble( m_shadowmap_offset );
  // version >= 101 begins here
  if (rc) rc = file.WriteDouble( m_image_dpi );
  i = static_cast<unsigned int>(m_image_us);
  if (rc) rc = file.WriteInt( i );
  // version >= 102 begins here
  if (rc) rc = file.WriteColor( m_background_bottom_color );

  // version >= 103 begins here - added 11 November 2010
  if (rc) rc = file.WriteBool( m_bScaleBackgroundToFit );

  return rc;
}

bool ON_3dmRenderSettings::Read( ON_BinaryArchive& file )
{
  *this = ON_3dmRenderSettings::Default;
  if ( ON_3dmRenderSettings::UseV5ReadWrite(file) )
    return ReadV5(file);

  // November 5, 2013 V6 files and later
  int major_version = 0;
  int minor_version = 0;
  if ( !file.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version) )
    return false;

  bool rc = false;
  int i;
  for(;;)
  {
    if ( 1 != major_version ) break;

    if ( !file.ReadBool( &m_bCustomImageSize ) ) break;
    if ( !file.ReadInt( &m_image_width ) ) break;
    if ( !file.ReadInt( &m_image_height ) ) break;

    if ( !file.ReadDouble( &m_image_dpi ) ) break;
    i = ON_UNSET_UINT_INDEX;
    if ( !file.ReadInt( &i ) ) break;
    m_image_us = ON::LengthUnitSystemFromUnsigned(i);

    if ( !file.ReadColor( m_ambient_light ) ) break;

    if ( !file.ReadInt( &m_background_style ) ) break;
    if ( !file.ReadColor( m_background_color ) ) break;
    if ( !file.ReadColor( m_background_bottom_color ) ) break;
    if ( !file.ReadString( m_background_bitmap_filename ) ) break;

    if ( !file.ReadBool( &m_bUseHiddenLights ) ) break;
    if ( !file.ReadBool( &m_bDepthCue ) ) break;
    if ( !file.ReadBool( &m_bFlatShade ) ) break;
    if ( !file.ReadBool( &m_bRenderBackfaces ) ) break;
    if ( !file.ReadBool( &m_bRenderPoints ) ) break;
    if ( !file.ReadBool( &m_bRenderCurves ) ) break;
    if ( !file.ReadBool( &m_bRenderIsoparams ) ) break;
    if ( !file.ReadBool( &m_bRenderMeshEdges ) ) break;
    if ( !file.ReadBool( &m_bRenderAnnotation ) ) break;
    if ( !file.ReadBool( &m_bScaleBackgroundToFit ) ) break;
    if ( !file.ReadBool( &m_bTransparentBackground ) ) break;

    if ( !file.ReadInt( &m_antialias_style ) ) break;
    if ( !file.ReadInt( &m_shadowmap_style ) ) break;
    if ( !file.ReadInt( &m_shadowmap_width ) ) break;
    if ( !file.ReadInt( &m_shadowmap_height ) ) break;
    if ( !file.ReadDouble( &m_shadowmap_offset ) ) break;

	// March 11th 2016 "1.1"- adds focal blur data
	//http://mcneel.myjetbrains.com/youtrack/issue/RH-32342
	if (minor_version >= 1)
	{
		// ALB. June 24th 2017 - this information is now on ON_3dmView.  Reads the values out, but doesn't store them.
		i = ON_UNSET_UINT_INDEX;
		double d;
		if (!file.ReadInt( &i)) break;

		if (!file.ReadDouble(&d)) break;
		if (!file.ReadDouble(&d)) break;
		if (!file.ReadDouble(&d)) break;
		if (!file.ReadInt(&i)) break;
	}

	// June 20th 2017 "1.2"- adds rendering source data
	// https://mcneel.myjetbrains.com/youtrack/issue/RH-39593
	if (minor_version >= 2)
	{
		i = ON_UNSET_UINT_INDEX;
		if (!file.ReadInt( &i)) break;
		m_rendering_source = (RenderingSources)i;

		if (!file.ReadString(m_specific_viewport)) break;
		if (!file.ReadString(m_named_view)) break;
		if (!file.ReadString(m_snapshot)) break;
	}

  // September 28th 2017 "1.3"- adds aspect ratio lock
  // https://mcneel.myjetbrains.com/youtrack/issue/RH-41608
  if (minor_version >= 3)
  {
    if (!file.ReadBool(&m_bForceViewportAspectRatio)) break;
  }

    rc = true;
    break;
  }  

  if ( !file.EndRead3dmChunk() )
    rc = false;

  return rc;
}

bool ON_3dmRenderSettings::ReadV5( ON_BinaryArchive& file )
{
  bool rc;
  int b, i;
  int version;
  rc = false;
  for(;;)
  {
    version = 0;
    if ( !file.ReadInt( &version ) )
      break;
    if ( version < 100 )
      break;
    if ( version >= 200 )
      break;
    if ( !file.ReadInt( &b ) )
      break;
    m_bCustomImageSize = (0 != b);
    if ( !file.ReadInt( &m_image_width ) )
      break;
    if ( !file.ReadInt( &m_image_height ) )
      break;
    if ( !file.ReadColor( m_ambient_light ) )
      break;
    if ( !file.ReadInt( &m_background_style ) )
      break;
    if ( !file.ReadColor( m_background_color ) )
      break;
    if ( !file.ReadString( m_background_bitmap_filename ) )
      break;
    if ( !file.ReadInt( &b ) )
      break;
    m_bUseHiddenLights = (0 != b);
    if ( !file.ReadInt( &b ) )
      break;
    m_bDepthCue = (0 != b);
    if ( !file.ReadInt( &b ) )
      break;
    m_bFlatShade = (0 != b);
    if ( !file.ReadInt( &b ) )
      break;
    m_bRenderBackfaces = (0 != b);
    if ( !file.ReadInt( &b ) )
      break;
    m_bRenderPoints = (0 != b);
    if ( !file.ReadInt( &b ) )
      break;
    m_bRenderCurves = (0 != b);
    if ( !file.ReadInt( &b ) )
      break;
    m_bRenderIsoparams = (0 != b);
    if ( !file.ReadInt( &b ) )
      break;
    m_bRenderMeshEdges = (0 != b);
    if ( !file.ReadInt( &b ) )
      break;
    m_bRenderAnnotation = (0 != b);
    if ( !file.ReadInt( &m_antialias_style ) )
      break;
    if ( !file.ReadInt( &m_shadowmap_style ) )
      break;
    if ( !file.ReadInt( &m_shadowmap_width ) )
      break;
    if ( !file.ReadInt( &m_shadowmap_height ) )
      break;
    if ( !file.ReadDouble( &m_shadowmap_offset ) )
      break;
    
    if ( version < 101 )
    {
      rc = true;
      break;
    }
    if ( !file.ReadDouble( &m_image_dpi ) )
      break;
    if ( !file.ReadInt(&i) )
      break;
    m_image_us = ON::LengthUnitSystemFromUnsigned(i);
     
    
    if ( version < 102 )
    {
      rc = true;
      break;
    }
    if ( !file.ReadColor( m_background_bottom_color ) )
      break;

    if ( version < 103 )
    {
      rc = true;
      break;
    }
    if ( !file.ReadBool( &m_bScaleBackgroundToFit ) )
      break;

    rc = true;
    break;
  }

  return rc;
}

ON_3dmRenderSettings::RenderingSources ON_3dmRenderSettings::RenderingSource(void) const
{
	return m_rendering_source;
}

void ON_3dmRenderSettings::SetRenderingSource(ON_3dmRenderSettings::RenderingSources rs)
{
	m_rendering_source = rs;
}

ON_wString ON_3dmRenderSettings::SpecificViewport(void) const
{
	return m_specific_viewport;
}

void ON_3dmRenderSettings::SetSpecificViewport(const ON_wString& s)
{
	m_specific_viewport = s;
}

ON_wString ON_3dmRenderSettings::NamedView(void) const
{
	return m_named_view;
}

void ON_3dmRenderSettings::SetNamedView(const ON_wString& s)
{
	m_named_view = s;
}

ON_wString ON_3dmRenderSettings::Snapshot(void) const
{
	return m_snapshot;
}

void ON_3dmRenderSettings::SetSnapshot(const ON_wString& s)
{
	m_snapshot = s;
}

bool ON_3dmRenderSettings::ScaleBackgroundToFit() const
{
  return m_bScaleBackgroundToFit;
}

void ON_3dmRenderSettings::SetScaleBackgroundToFit( bool bScaleBackgroundToFit )
{
  // The "? true : false" is here to prevent hacks from using a bool
  // to store settings besides 1 and 0.
  m_bScaleBackgroundToFit = bScaleBackgroundToFit?true:false;
}

ON_GroundPlane& ON_3dmRenderSettings::GroundPlane(void)
{
  ON_3dmRenderSettingsPrivate::Get(*this);

  // The pointer is never null.
  ON_ASSERT(nullptr != m_private->_ground_plane);

  return *m_private->_ground_plane;
}

const ON_GroundPlane& ON_3dmRenderSettings::GroundPlane(void) const
{
  return const_cast<ON_3dmRenderSettings*>(this)->GroundPlane();
}

ON_Dithering& ON_3dmRenderSettings::Dithering(void)
{
  ON_3dmRenderSettingsPrivate::Get(*this);

  // The pointer is never null.
  ON_ASSERT(nullptr != m_private->_dithering);

  return *m_private->_dithering;
}

const ON_Dithering& ON_3dmRenderSettings::Dithering(void) const
{
  return const_cast<ON_3dmRenderSettings*>(this)->Dithering();
}

ON_SafeFrame& ON_3dmRenderSettings::SafeFrame(void)
{
  ON_3dmRenderSettingsPrivate::Get(*this);

  // The pointer is never null.
  ON_ASSERT(nullptr != m_private->_safe_frame);

  return *m_private->_safe_frame;
}

const ON_SafeFrame& ON_3dmRenderSettings::SafeFrame(void) const
{
  return const_cast<ON_3dmRenderSettings*>(this)->SafeFrame();
}

ON_Skylight& ON_3dmRenderSettings::Skylight(void)
{
  ON_3dmRenderSettingsPrivate::Get(*this);

  // The pointer is never null.
  ON_ASSERT(nullptr != m_private->_skylight);

  return *m_private->_skylight;
}

const ON_Skylight& ON_3dmRenderSettings::Skylight(void) const
{
  return const_cast<ON_3dmRenderSettings*>(this)->Skylight();
}

ON_LinearWorkflow& ON_3dmRenderSettings::LinearWorkflow(void)
{
  ON_3dmRenderSettingsPrivate::Get(*this);

  // The pointer is never null.
  ON_ASSERT(nullptr != m_private->_linear_workflow);

  return *m_private->_linear_workflow;
}

const ON_LinearWorkflow& ON_3dmRenderSettings::LinearWorkflow(void) const
{
  return const_cast<ON_3dmRenderSettings*>(this)->LinearWorkflow();
}

ON_RenderChannels& ON_3dmRenderSettings::RenderChannels(void)
{
  ON_3dmRenderSettingsPrivate::Get(*this);

  // The pointer is never null.
  ON_ASSERT(nullptr != m_private->_render_channels);

  return *m_private->_render_channels;
}

const ON_RenderChannels& ON_3dmRenderSettings::RenderChannels(void) const
{
  return const_cast<ON_3dmRenderSettings*>(this)->RenderChannels();
}

ON_Sun& ON_3dmRenderSettings::Sun(void)
{
  ON_3dmRenderSettingsPrivate::Get(*this);

  // The pointer is never null.
  ON_ASSERT(nullptr != m_private->_sun);

  return *m_private->_sun;
}

const ON_Sun& ON_3dmRenderSettings::Sun(void) const
{
  return const_cast<ON_3dmRenderSettings*>(this)->Sun();
}

bool ON_3dmRenderSettings::RenderEnvironmentOverride(EnvironmentUsage usage) const
{
  ON_3dmRenderSettingsPrivate::Get(*this);

  // The pointer is never null.
  ON_ASSERT(nullptr != m_private->_environments);

  const auto& e = *m_private->_environments;
  switch (usage)
  {
  default:
  case EnvironmentUsage::Background:  return m_background_style == 3;
  case EnvironmentUsage::Reflection:  return e.ReflectionRenderEnvironmentOverride();
  case EnvironmentUsage::Skylighting: return e.SkylightingRenderEnvironmentOverride();
  }
}

void ON_3dmRenderSettings::SetRenderEnvironmentOverride(EnvironmentUsage usage, bool on)
{
  ON_3dmRenderSettingsPrivate::Get(*this);

  // The pointer is never null.
  ON_ASSERT(nullptr != m_private->_environments);

  auto& e = *m_private->_environments;
  switch (usage)
  {
  default:
  case EnvironmentUsage::Background:  ON_ASSERT(false);                              break;
  case EnvironmentUsage::Reflection:  e.SetReflectionRenderEnvironmentOverride(on);  break;
  case EnvironmentUsage::Skylighting: e.SetSkylightingRenderEnvironmentOverride(on); break;
  }
}

ON_UUID ON_3dmRenderSettings::RenderEnvironmentId(EnvironmentUsage usage, EnvironmentPurpose purpose) const
{
  ON_3dmRenderSettingsPrivate::Get(*this);

  // The pointer is never null.
  ON_ASSERT(nullptr != m_private->_environments);

  const auto& e = *m_private->_environments;

  if (EnvironmentPurpose::Standard == purpose)
  {
    switch (usage)
    {
    default:
    case EnvironmentUsage::Background:  return e.BackgroundRenderEnvironmentId();
    case EnvironmentUsage::Reflection:  return e.ReflectionRenderEnvironmentId();
    case EnvironmentUsage::Skylighting: return e.SkylightingRenderEnvironmentId();
    }
  }
  else
  if (EnvironmentPurpose::ForRendering == purpose)
  {
    switch (usage)
    {
    default:
    case EnvironmentUsage::Background:
      {
      if (m_background_style != 3)
        return ON_nil_uuid;

      const auto uuid_env = e.BackgroundRenderEnvironmentId();
      if (ON_UuidIsNotNil(uuid_env))
        return uuid_env;

      return ON_UuidDefaultEnvironmentInstance;
      }

    case EnvironmentUsage::Reflection:
      if (e.ReflectionRenderEnvironmentOverride())
        return e.ReflectionRenderEnvironmentId();

      return RenderEnvironmentId(EnvironmentUsage::Background, purpose);

    case EnvironmentUsage::Skylighting:
      if (!Skylight().Enabled())
        return ON_nil_uuid;

      if (e.SkylightingRenderEnvironmentOverride())
        return e.SkylightingRenderEnvironmentId();

      return RenderEnvironmentId(EnvironmentUsage::Background, purpose);
    }
  }

  ON_ASSERT(false);
  return ON_nil_uuid;
}

void ON_3dmRenderSettings::SetRenderEnvironmentId(EnvironmentUsage usage, const ON_UUID& id)
{
  ON_3dmRenderSettingsPrivate::Get(*this);

  // The pointer is never null.
  ON_ASSERT(nullptr != m_private->_environments);

  auto& e = *m_private->_environments;
  switch (usage)
  {
  default:
  case EnvironmentUsage::Background:  e.SetBackgroundRenderEnvironmentId(id);  break;
  case EnvironmentUsage::Reflection:  e.SetReflectionRenderEnvironmentId(id);  break;
  case EnvironmentUsage::Skylighting: e.SetSkylightingRenderEnvironmentId(id); break;
  }
}

ON_PostEffects& ON_3dmRenderSettings::PostEffects(void)
{
  ON_3dmRenderSettingsPrivate::Get(*this);

  // The pointer is never null.
  ON_ASSERT(nullptr != m_private->_post_effects);

  return *m_private->_post_effects;
}

const ON_PostEffects& ON_3dmRenderSettings::PostEffects(void) const
{
  return const_cast<ON_3dmRenderSettings*>(this)->PostEffects();
}

void ON_3dmRenderSettings::InvalidateCaches(void) const
{
  m_private->_ground_plane->OnInternalXmlChanged(nullptr);
  m_private->_dithering->OnInternalXmlChanged(nullptr);
  m_private->_safe_frame->OnInternalXmlChanged(nullptr);
  m_private->_skylight->OnInternalXmlChanged(nullptr);
  m_private->_linear_workflow->OnInternalXmlChanged(nullptr);
  m_private->_render_channels->OnInternalXmlChanged(nullptr);
  m_private->_sun->OnInternalXmlChanged(nullptr);
  m_private->_post_effects->OnInternalXmlChanged(nullptr);
}

#ifdef RDK_RENDER_PRESETS

extern ON_UUID uuidRenderPreset_Studio;
extern ON_UUID uuidRenderPreset_Custom;
extern ON_UUID uuidRenderPreset_Exterior;
extern ON_UUID uuidRenderPreset_Interior;

static const wchar_t* rendering = ON_RDK_DOCUMENT  ON_XML_SLASH  ON_RDK_SETTINGS  ON_XML_SLASH  ON_RDK_RENDERING;

ON_UUID ON_3dmRenderSettings::CurrentRenderPreset(void) const
{
  const auto* node = ON_GetRdkDocNode(*this).GetNodeAtPath(rendering);
  if (nullptr != node)
  {
    ON_XMLParameters p(*node);
    ON_XMLVariant value;
    if (p.GetParam(ON_RDK_CURRENT_RENDER_PRESET, value))
      return value.AsUuid();
  }

  return ON_nil_uuid;
}

void ON_3dmRenderSettings::SetCurrentRenderPreset(const ON_UUID& uuid)
{
  ON_ASSERT((uuidRenderPreset_Studio   == uuid) || (uuidRenderPreset_Custom   == uuid) ||
            (uuidRenderPreset_Exterior == uuid) || (uuidRenderPreset_Interior == uuid));

  auto* node = ON_GetRdkDocNode(*this).GetNodeAtPath(rendering);
  if (nullptr != node)
  {
    ON_XMLParameters p(*node);
    p.SetParam(ON_RDK_CURRENT_RENDER_PRESET, uuid);
  }
}

void ON_3dmRenderSettings::GetRenderPresetList(ON_SimpleArray<ON_UUID>& presets) const
{
  presets.Append(uuidRenderPreset_Studio);
  presets.Append(uuidRenderPreset_Exterior);
  presets.Append(uuidRenderPreset_Interior);
  presets.Append(uuidRenderPreset_Custom);
}
#endif

//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmAnnotationSettingsPrivate
//

class ON_3dmAnnotationSettingsPrivate
{
public:
  ON_3dmAnnotationSettingsPrivate() = default;
  ~ON_3dmAnnotationSettingsPrivate() = default;
  bool operator==(const ON_3dmAnnotationSettingsPrivate&) const;
  bool operator!=(const ON_3dmAnnotationSettingsPrivate&) const;

public:
  float m_world_view_text_scale = 1.0f;
  float m_world_view_hatch_scale = 1.0f;
  bool m_use_dimension_layer = false;
  ON_UUID m_dimension_layer_id = ON_nil_uuid;
};

static const ON_3dmAnnotationSettingsPrivate Default3dmAnnotationSettingsPrivate;

bool ON_3dmAnnotationSettingsPrivate::operator==(const ON_3dmAnnotationSettingsPrivate& other) const
{
  if (this == &other)
    return true;

  if (m_world_view_text_scale != other.m_world_view_text_scale)
    return false;

  if (m_world_view_hatch_scale != other.m_world_view_hatch_scale)
    return false;

  if (m_use_dimension_layer != other.m_use_dimension_layer)
    return false;

  if (0 != ON_UuidCompare(m_dimension_layer_id, other.m_dimension_layer_id))
    return false;

  return true;
}

bool ON_3dmAnnotationSettingsPrivate::operator!=(const ON_3dmAnnotationSettingsPrivate& other) const
{
  return !ON_3dmAnnotationSettingsPrivate::operator==(other);
}

//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmAnnotationSettings
//

void ON_3dmAnnotationSettings::Internal_CopyFrom(const ON_3dmAnnotationSettings& src)
{
  m_dimscale = src.m_dimscale;
  m_textheight = src.m_textheight;
  m_dimexe = src.m_dimexe;
  m_dimexo = src.m_dimexo;
  m_arrowlength = src.m_arrowlength;
  m_arrowwidth = src.m_arrowwidth;
  m_centermark = src.m_centermark;
  
  m_b_V5_EnableAnnotationScaling = src.m_b_V5_EnableAnnotationScaling;
  m_bEnableModelSpaceAnnotationScaling = src.m_bEnableModelSpaceAnnotationScaling;
  m_bEnableLayoutSpaceAnnotationScaling = src.m_bEnableLayoutSpaceAnnotationScaling;
  m_bEnableHatchScaling = src.m_bEnableHatchScaling;
  
  m_reserved1 = src.m_reserved1;
  m_reserved2 = src.m_reserved2;
  m_reserved3 = src.m_reserved3;
  m_reserved4 = src.m_reserved4;
  
  m_dimunits = src.m_dimunits;
  m_arrowtype = src.m_arrowtype;
  m_angularunits = src.m_angularunits;
  m_lengthformat = src.m_lengthformat;
  m_angleformat = src.m_angleformat;
  m_resolution = src.m_resolution;
  m_facename = src.m_facename;

  if (src.m_private)
  {
    m_private = new ON_3dmAnnotationSettingsPrivate();
    *m_private = *src.m_private;
  }
}

void ON_3dmAnnotationSettings::Internal_Destroy()
{
  if (m_private)
  {
    delete m_private;
    m_private = nullptr;
  }
}

ON_3dmAnnotationSettings::~ON_3dmAnnotationSettings()
{
  // NOTE WELL:
  //  ON_3dmAnnotationSettings::Default is a global const instance.
  //  Compilers like VS 2019 16.5.0 set the memory for that instance to read-only.
  //  This destructor must not write to memory used by const instances.
  if (this != &ON_3dmAnnotationSettings::Default)
  {
    Internal_Destroy();
  }
}

ON_3dmAnnotationSettings::ON_3dmAnnotationSettings(const ON_3dmAnnotationSettings& src)
{
  Internal_CopyFrom(src);
}

ON_3dmAnnotationSettings& ON_3dmAnnotationSettings::operator=(const ON_3dmAnnotationSettings& src)
{
  if (this != &src)
  {
    Internal_Destroy();
    Internal_CopyFrom(src);
  }
  return *this;
}

void ON_3dmAnnotationSettings::Dump(ON_TextLog& text_log) const
{
  // TODO
}

double ON_3dmAnnotationSettings::WorldViewTextScale() const
{
  double world_view_text_scale = Default3dmAnnotationSettingsPrivate.m_world_view_text_scale;
  if (this != &ON_3dmAnnotationSettings::Default)
  {
    if (m_private)
      world_view_text_scale = m_private->m_world_view_text_scale;
  }
  return world_view_text_scale;
}

double ON_3dmAnnotationSettings::WorldViewHatchScale() const
{
  double world_view_hatch_scale = Default3dmAnnotationSettingsPrivate.m_world_view_hatch_scale;
  if (this != &ON_3dmAnnotationSettings::Default)
  {
    if (m_private)
      world_view_hatch_scale = m_private->m_world_view_hatch_scale;
  }
  return world_view_hatch_scale;
}

void ON_3dmAnnotationSettings::SetWorldViewTextScale(double world_view_text_scale )
{
  if (this == &ON_3dmAnnotationSettings::Default)
    return;
  if (ON_IsValid(world_view_text_scale) && world_view_text_scale > 0.0)
  {
    if (WorldViewTextScale() != world_view_text_scale)
    {
      if (nullptr == m_private)
        m_private = new ON_3dmAnnotationSettingsPrivate();
      m_private->m_world_view_text_scale = (float)world_view_text_scale;
    }
  }
}

void ON_3dmAnnotationSettings::SetWorldViewHatchScale(double world_view_hatch_scale)
{
  if (this == &ON_3dmAnnotationSettings::Default)
    return;
  if (ON_IsValid(world_view_hatch_scale) && world_view_hatch_scale > 0.0)
  {
    if (WorldViewHatchScale() != world_view_hatch_scale)
    {
      if (nullptr == m_private)
        m_private = new ON_3dmAnnotationSettingsPrivate();
      m_private->m_world_view_hatch_scale = (float)world_view_hatch_scale;
    }
  }
}

bool ON_3dmAnnotationSettings::UseDimensionLayer() const
{
  bool use_dimension_layer = Default3dmAnnotationSettingsPrivate.m_use_dimension_layer;
  if (this != &ON_3dmAnnotationSettings::Default)
  {
    if (m_private)
      use_dimension_layer = m_private->m_use_dimension_layer;
  }
  return use_dimension_layer;
}

void ON_3dmAnnotationSettings::EnableUseDimensionLayer(bool use_dimension_layer)
{
  if (this == &ON_3dmAnnotationSettings::Default)
    return;
  if (UseDimensionLayer() != use_dimension_layer)
  {
    if (nullptr == m_private)
      m_private = new ON_3dmAnnotationSettingsPrivate();
    m_private->m_use_dimension_layer = use_dimension_layer;
  }
}

ON_UUID ON_3dmAnnotationSettings::DimensionLayerId() const
{
  ON_UUID layer_id = Default3dmAnnotationSettingsPrivate.m_dimension_layer_id;
  if (this != &ON_3dmAnnotationSettings::Default)
  {
    if (m_private)
      layer_id = m_private->m_dimension_layer_id;
  }
  return layer_id;
}

void ON_3dmAnnotationSettings::SetDimensionLayerId(const ON_UUID& dimension_layer_id)
{
  if (this == &ON_3dmAnnotationSettings::Default)
    return;
  if (DimensionLayerId() != dimension_layer_id)
  {
    if (nullptr == m_private)
      m_private = new ON_3dmAnnotationSettingsPrivate();
    m_private->m_dimension_layer_id = dimension_layer_id;
  }
}

bool ON_3dmAnnotationSettings::Is_V5_AnnotationScalingEnabled() const
{
  return m_b_V5_EnableAnnotationScaling?true:false;
}

void ON_3dmAnnotationSettings::Enable_V5_AnnotationScaling( bool bEnable )
{
  m_b_V5_EnableAnnotationScaling = bEnable?1:0;
}

bool ON_3dmAnnotationSettings::IsModelSpaceAnnotationScalingEnabled() const
{
  return m_bEnableModelSpaceAnnotationScaling ? true : false;
}

void ON_3dmAnnotationSettings::EnableModelSpaceAnnotationScaling(bool bEnable)
{
  m_bEnableModelSpaceAnnotationScaling = bEnable ? 1 : 0;
}


bool ON_3dmAnnotationSettings::IsLayoutSpaceAnnotationScalingEnabled() const
{
  return m_bEnableLayoutSpaceAnnotationScaling ? true : false;
}

void ON_3dmAnnotationSettings::EnableLayoutSpaceAnnotationScaling(bool bEnable)
{
  m_bEnableLayoutSpaceAnnotationScaling = bEnable ? 1 : 0;
}

bool ON_3dmAnnotationSettings::IsHatchScalingEnabled() const
{
  return m_bEnableHatchScaling?true:false;
}

void ON_3dmAnnotationSettings::EnableHatchScaling( bool bEnable )
{
  m_bEnableHatchScaling = bEnable?1:0;
}

bool ON_3dmAnnotationSettings::Read( ON_BinaryArchive& file )
{
  *this = ON_3dmAnnotationSettings::Default;

  int major_version = 0;
  int minor_version = 0;
  bool rc = file.Read3dmChunkVersion(&major_version,&minor_version);
  if ( major_version == 1 ) {
    if (minor_version >= 0) {
      if (rc) rc = file.ReadDouble(&m_dimscale);
      if (rc) rc = file.ReadDouble(&m_textheight);
      if (rc) rc = file.ReadDouble(&m_dimexe);
      if (rc) rc = file.ReadDouble(&m_dimexo);
      if (rc) rc = file.ReadDouble(&m_arrowlength);
      if (rc) rc = file.ReadDouble(&m_arrowwidth);
      if (rc) rc = file.ReadDouble(&m_centermark);

      {
        unsigned int i;
        if (rc)
        {
          rc = file.ReadInt(&i);
          if (rc)
            m_dimunits = ON::LengthUnitSystemFromUnsigned(i);
        }
      }

      if (rc) rc = file.ReadInt(&m_arrowtype);
      if (rc) rc = file.ReadInt(&m_angularunits);
      if (rc) rc = file.ReadInt(&m_lengthformat);
      if (rc) rc = file.ReadInt(&m_angleformat);

      unsigned int obsolete_value = 0;
      if (rc) rc = file.ReadInt(&obsolete_value);

      if (rc) rc = file.ReadInt(&m_resolution);

      if (rc) rc = file.ReadString(m_facename);

      bool bV6orLater = file.Archive3dmVersion() >= 60;
      bool bV5 = !bV6orLater && file.Archive3dmVersion() >= 5;

      if (bV6orLater)
      {
        // files that do not contain m_bEnableAnnotationScaling,
        // set m_bEnableAnnotationScaling = false so the display 
        // image does not change.
        m_b_V5_EnableAnnotationScaling = 1;

        // files that do not contain m_bEnableModelSpaceAnnotationScaling,
        // set m_bEnableModelSpaceAnnotationScaling = true so the display 
        // image does not change.
        //*********** This is probably right for v5 files, but not for pre-V5 *************
        m_bEnableModelSpaceAnnotationScaling = 1;

        // files that do not contain m_bEnableLayoutSpaceAnnotationScaling,
        // set m_bEnableLayoutAnnotationScaling = false so the display 
        // image does not change.
        // ********** This should be set from m_b_V5_EnableAnnotationScaling for V5 files   *************
        m_bEnableLayoutSpaceAnnotationScaling = 1;
      }
      else if (bV5)
      {
        m_bEnableModelSpaceAnnotationScaling = 1;
      }
      else
      {
        // v4 or earlier - no layout or model space scaling
        m_b_V5_EnableAnnotationScaling = 0;
        m_bEnableModelSpaceAnnotationScaling = 0;
        m_bEnableLayoutSpaceAnnotationScaling = 0;
      }

      // files that do not contain m_bEnableHatchScaling,
      // set m_bEnableHatchScaling = false so the display
      // image does not change.
      m_bEnableHatchScaling = 0;

      if ( minor_version >= 1 )
      {
        // Added 25 August 2010 chunk version 1.1
        double d = WorldViewTextScale();
        if (rc) rc = file.ReadDouble(&d);
        if (rc && ON_IsValid(d) && d >= 0.0) SetWorldViewTextScale(d);
        if (rc) rc = file.ReadChar(&m_b_V5_EnableAnnotationScaling);
        if (rc)
        {
          if (m_b_V5_EnableAnnotationScaling)
          {
            m_bEnableLayoutSpaceAnnotationScaling = 1;
          }
          else
          {
            m_bEnableLayoutSpaceAnnotationScaling = 0;
          }
        }

        if ( minor_version >= 2 )
        {
          d = WorldViewHatchScale();
          if (rc) rc = file.ReadDouble(&d);
          if (rc && ON_IsValid(d) && d >= 0.0) SetWorldViewHatchScale(d);
          if (rc) rc = file.ReadChar(&m_bEnableHatchScaling);
          if (minor_version >= 3)
          {
            // [Lowell 3-28-2013] New fields for V6
            if (rc) rc = file.ReadChar(&m_bEnableModelSpaceAnnotationScaling);
            if (rc) rc = file.ReadChar(&m_bEnableLayoutSpaceAnnotationScaling);

            //  Added 17 April 2023 chunk version 1.4
            if (minor_version >= 4)
            {
              bool b = false;
              ON_UUID s = ON_nil_uuid;
              if (rc) rc = file.ReadBool(&b);
              if (rc) EnableUseDimensionLayer(b);
              if (rc) rc = file.ReadUuid(s);
              if (rc) SetDimensionLayerId(s);
            }
          }
        }
      }
    }
  }
  else {
    rc = false;
  }
  return rc;
}

bool ON_3dmAnnotationSettings::Write( ON_BinaryArchive& file ) const
{
  int minor_version
    = file.Archive3dmVersion() >= 60
    ? 4
    : 2;

  unsigned int i;
  bool rc = file.Write3dmChunkVersion(1, minor_version);
  // March 22, 2010 - Global DimScale abandoned and moved into DimStyles, so now
  // in older files, the dimscale values are multiplied into the DimStyle lengths and
  // DimScale is written as 1.0

  // March 2017 Add
  /*
    unsigned char m_b_V5_EnableAnnotationScaling = 1;

  // [Lowell 3-28-2013] New fields for V6
  unsigned char m_bEnableModelSpaceAnnotationScaling = 1;
  unsigned char m_bEnableLayoutSpaceAnnotationScaling = 1;
  */
  if (rc) rc = file.WriteDouble(1.0);

  if (rc) rc = file.WriteDouble(m_textheight);
  if (rc) rc = file.WriteDouble(m_dimexe);
  if (rc) rc = file.WriteDouble(m_dimexo);
  if (rc) rc = file.WriteDouble(m_arrowlength);
  if (rc) rc = file.WriteDouble(m_arrowwidth);
  if (rc) rc = file.WriteDouble(m_centermark);

  i = static_cast<unsigned int>(m_dimunits);
  if (rc) rc = file.WriteInt( i );
  if (rc) rc = file.WriteInt( m_arrowtype );
  if (rc) rc = file.WriteInt( m_angularunits );
  if (rc) rc = file.WriteInt( m_lengthformat );
  if (rc) rc = file.WriteInt( m_angleformat );

  const unsigned int textalign 
    = (file.Archive3dmVersion() <= 2)
    ? 0
    : 2;
  if (rc) rc = file.WriteInt( textalign );

  if (rc) rc = file.WriteInt( m_resolution );

  if (rc) rc = file.WriteString( m_facename );

  // Added 25 August 2010 chunk version 1.1
  double d = WorldViewTextScale();
  if (rc) rc = file.WriteDouble(d);
  if (rc) rc = file.WriteChar(m_b_V5_EnableAnnotationScaling);

  // Added 14 January 2011 chunk version 1.2
  d = WorldViewHatchScale();
  if (rc) rc = file.WriteDouble(d);
  if (rc) rc = file.WriteChar(m_bEnableHatchScaling);

  // Added 28 March 2013 chunk version 1.3
  if (minor_version >= 3)
  {
    // [Lowell 3-28-2013] New fields for V6
    if (rc) rc = file.WriteChar(m_bEnableModelSpaceAnnotationScaling);
    if (rc) rc = file.WriteChar(m_bEnableLayoutSpaceAnnotationScaling);
  }

  //  Added 17 April 2023 chunk version 1.4
  if (minor_version >= 4)
  {
    if (rc) rc = file.WriteBool(UseDimensionLayer());
    if (rc) rc = file.WriteUuid(DimensionLayerId());
  }

  return rc;
}

//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmConstructionPlane
//
ON_3dmConstructionPlane::ON_3dmConstructionPlane()
{
  Default();
}

ON_3dmConstructionPlane::ON_3dmConstructionPlane(const ON_Plane& plane)
{
  Default();
  m_plane = plane;
}

ON_3dmConstructionPlane::~ON_3dmConstructionPlane()
{
}

// default copy constructor and operator= work fine
/*
ON_3dmConstructionPlane::ON_3dmConstructionPlane(const ON_3dmConstructionPlane& src)
{
  Default();
  *this = src;
}
ON_3dmConstructionPlane& ON_3dmConstructionPlane::operator=(const ON_3dmConstructionPlane& src)
{
  if ( this != &src ) 
  {
    m_plane = src.m_plane;
    m_grid_spacing = src.m_grid_spacing;
    m_snap_spacing = src.m_snap_spacing;
    m_grid_line_count = src.m_grid_line_count;
    m_grid_thick_frequency = src.m_grid_thick_frequency;
    m_name = src.m_name;
    m_bDepthBuffer = src.m_bDepthBuffer;
  }
  return *this;
}
*/

void ON_3dmConstructionPlane::Dump( ON_TextLog& text_log ) const
{
  // TODO
}

void ON_3dmConstructionPlane::Default()
{
  m_name.Destroy();
  m_plane = ON_xy_plane;

  // construction grid appearance
	m_grid_spacing = 1.0;   // distance between grid lines
	m_snap_spacing = 1.0;   // distance between grid snap points
	m_grid_line_count = 70;     // number of grid lines in each direction
  m_grid_thick_frequency = 5; // thick line frequency
  m_bDepthBuffer = true;
}

bool ON_3dmConstructionPlane::Write( ON_BinaryArchive& file ) const
{
  bool rc = file.Write3dmChunkVersion(1,1);

  if (rc) rc = file.WritePlane(m_plane);
  if (rc) rc = file.WriteDouble(m_grid_spacing);
  if (rc) rc = file.WriteDouble(m_snap_spacing);
  if (rc) rc = file.WriteInt(m_grid_line_count);
  if (rc) rc = file.WriteInt(m_grid_thick_frequency);
  if (rc) rc = file.WriteString(m_name);

  // added for version 1.1 chunks
  if (rc) rc = file.WriteBool(m_bDepthBuffer);

  return rc;
}

bool ON_3dmConstructionPlane::Read( ON_BinaryArchive& file )
{
  Default();
  int major_version = 0;
  int minor_version = 0;
  bool rc = file.Read3dmChunkVersion(&major_version,&minor_version);
  if (rc && major_version==1) 
  {
    if (rc) rc = file.ReadPlane(m_plane);
    if (rc) rc = file.ReadDouble(&m_grid_spacing);
    if (rc) rc = file.ReadDouble(&m_snap_spacing);
    if (rc) rc = file.ReadInt(&m_grid_line_count);
    if (rc) rc = file.ReadInt(&m_grid_thick_frequency);
    if (rc) rc = file.ReadString(m_name);

    if ( minor_version >= 1 )
    {
      if (rc) rc = file.ReadBool(&m_bDepthBuffer);
    }
  }
  return rc;
}

//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmConstructionPlaneGridDefaults
//


void ON_3dmConstructionPlaneGridDefaults::Dump(ON_TextLog& text_log) const
{
  // TODO
}

bool ON_3dmConstructionPlaneGridDefaults::Write( ON_BinaryArchive& file ) const
{
  bool rc = file.Write3dmChunkVersion(1,0);
  if (rc) rc = file.WriteDouble(m_grid_spacing);
  if (rc) rc = file.WriteDouble(m_snap_spacing);
  if (rc) rc = file.WriteInt(m_grid_line_count);
  if (rc) rc = file.WriteInt(m_grid_thick_frequency);
  if (rc) rc = file.WriteInt(m_bShowGrid?1:0);
  if (rc) rc = file.WriteInt(m_bShowGridAxes?1:0);
  if (rc) rc = file.WriteInt(m_bShowWorldAxes?1:0);
  return rc;
}

bool ON_3dmConstructionPlaneGridDefaults::Read( ON_BinaryArchive& file )
{
  int major_version = 0;
  int minor_version = 0;
  
  bool rc = file.Read3dmChunkVersion(&major_version,&minor_version);
  
  if (rc && major_version==1) 
  {
    if (rc) rc = file.ReadDouble(&m_grid_spacing);
    if (rc) rc = file.ReadDouble(&m_snap_spacing);
    if (rc) rc = file.ReadInt(&m_grid_line_count);
    if (rc) rc = file.ReadInt(&m_grid_thick_frequency);
    
    int b = m_bShowGrid ? 1 : 0;
    if (rc) rc = file.ReadInt(&b);
    m_bShowGrid = (b != 0);
    
    b = m_bShowGridAxes ? 1 : 0;
    if (rc) rc = file.ReadInt(&b);
    m_bShowGridAxes = (b != 0);
    
    b = m_bShowWorldAxes ? 1 : 0;
    if (rc) rc = file.ReadInt(&b);
    m_bShowWorldAxes = (b != 0);
  }

  return rc;
}



//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmViewPosition
//
ON_3dmViewPosition::ON_3dmViewPosition()
{
  Default();
}

ON_3dmViewPosition::~ON_3dmViewPosition()
{
}

ON_3dmViewPosition::ON_3dmViewPosition(const ON_3dmViewPosition& src)
{
  Default();
  *this = src;
}

ON_3dmViewPosition& ON_3dmViewPosition::operator=(const ON_3dmViewPosition& src)
{
  if ( this != &src ) {
    m_wnd_left   = src.m_wnd_left;
    m_wnd_right  = src.m_wnd_right;
    m_wnd_top    = src.m_wnd_top;
    m_wnd_bottom = src.m_wnd_bottom;
    m_bMaximized = src.m_bMaximized;
    m_floating_viewport = src.m_floating_viewport;

    // reserved fields are not used
    // m_reserved_1 = src.m_reserved_1;
    // m_reserved_2 = src.m_reserved_2;
    // m_reserved_3 = src.m_reserved_3;
  }
  return *this;
}

void ON_3dmViewPosition::Default()
{
  m_wnd_left   = 0.0;
  m_wnd_right  = 1.0;
  m_wnd_top    = 0.0;
  m_wnd_bottom = 1.0;
  m_bMaximized = false;

  m_floating_viewport = 0;
  m_reserved_1 = 0;
  m_reserved_2 = 0;
  m_reserved_3 = 0;
}

bool ON_3dmViewPosition::Write( ON_BinaryArchive& file ) const
{
  int minor_version =  ( file.Archive3dmVersion() >= 5 ) ? 1 : 0;

  bool rc = file.Write3dmChunkVersion(1,minor_version);
  if (rc) 
  {
    int i = m_bMaximized ? 1 : 0;
    if (rc) rc = file.WriteInt( i );
    if (rc) rc = file.WriteDouble( m_wnd_left );
    if (rc) rc = file.WriteDouble( m_wnd_right );
    if (rc) rc = file.WriteDouble( m_wnd_top );
    if (rc) rc = file.WriteDouble( m_wnd_bottom );

    if ( minor_version >= 1 )
    {
      // 13 March 2009 S. Baer
      // version 1.1 added support for m_floating_viewport
      // in V5 files.  This info is not in V4 files because
      // they might use this to write userdata.
      if (rc) rc = file.WriteChar( m_floating_viewport );
    }
  }
  return rc;
}

bool ON_3dmViewPosition::Read( ON_BinaryArchive& file )
{
  int major_version = 0;
  int minor_version = 0;
  bool rc = file.Read3dmChunkVersion(&major_version,&minor_version);
  double x;
  Default();
  if (rc && major_version==1) 
  {
    int i = m_bMaximized ? 1 : 0;
    if (rc) rc = file.ReadInt( &i );
    if (rc) m_bMaximized = (i != 0) ? true : false;
    if (rc) rc = file.ReadDouble( &m_wnd_left );
    if (rc) rc = file.ReadDouble( &m_wnd_right );
    if (rc) rc = file.ReadDouble( &m_wnd_top );
    if (rc) rc = file.ReadDouble( &m_wnd_bottom );

    // 13 March 2009 S. Baer
    // version 1.1 added support for m_floating_viewport
    if( rc && minor_version >= 1 )
    {
      rc = file.ReadChar( &m_floating_viewport );
    }
  }

  // if people put bogus values in a file, tune them up to something that will work
  if ( m_wnd_left > m_wnd_right ) {
    x = m_wnd_left; m_wnd_left = m_wnd_right; m_wnd_right = x;
  }
  if ( m_wnd_left  < 0.0 ) 
    m_wnd_left  = 0.0; 
  if ( m_wnd_right >= 1.0 ) 
    m_wnd_right = 1.0;
  if ( m_wnd_left >= m_wnd_right ) {
    m_wnd_left = 0.0;
    m_wnd_right = 1.0;
  }
  
  if ( m_wnd_top > m_wnd_bottom ) {
    x = m_wnd_top; m_wnd_top = m_wnd_bottom; m_wnd_bottom = x;
  }
  if ( m_wnd_top  < 0.0 ) 
    m_wnd_top  = 0.0; 
  if ( m_wnd_bottom >= 1.0 )
    m_wnd_bottom = 1.0;
  if ( m_wnd_top >= m_wnd_bottom ) {
    m_wnd_top = 0.0;
    m_wnd_bottom = 1.0;
  }

  return rc;
}

//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmViewTraceImage
//
ON_3dmViewTraceImage::ON_3dmViewTraceImage()
{
  Default();
}

ON_3dmViewTraceImage::~ON_3dmViewTraceImage()
{
}

void ON_3dmViewTraceImage::Default()
{
  m_plane = ON_xy_plane;
  m_width = 0.0;
  m_height = 0.0;
  m_image_file_reference = ON_FileReference::Unset;
  m_bGrayScale = true;
  m_bHidden = false;
  m_bFiltered = false;
}

bool ON_3dmViewTraceImage::Write( ON_BinaryArchive& file ) const
{
  // opennurbs version  < 200307300 - version 1.0 or 1.1 chunk
  // opennurbs version >= 200307300 - version 1.2 chunk
  const int minor_version = (file.Archive3dmVersion() >= 60) ? 4 : 3;
  bool rc = file.Write3dmChunkVersion(1,minor_version);
  if (rc) 
  {
    if (rc) rc = file.WriteString( m_image_file_reference.FullPath() );
    if (rc) rc = file.WriteDouble( m_width );
    if (rc) rc = file.WriteDouble( m_height );
    if (rc) rc = file.WritePlane( m_plane );

    // version 1.1
    if (rc) rc = file.WriteBool( m_bGrayScale );

    // version 1.2
    if (rc) rc = file.WriteBool( m_bHidden );
    
    // version 1.3
    if (rc) rc = file.WriteBool( m_bFiltered );

    if (rc && minor_version >= 4)
    {
      // version 1.4
      if (rc) rc = m_image_file_reference.Write(true, file);
    }
  }
  return rc;
}


bool ON_3dmViewTraceImage::Read( ON_BinaryArchive& file )
{
  // opennurbs version  < 200307300 - version 1.0 or 1.1 chunk
  // opennurbs version >= 200307300 - version 1.2 chunk
  int major_version = 0;
  int minor_version = 0;
  bool rc = file.Read3dmChunkVersion(&major_version,&minor_version);
  if (rc && major_version==1)
  {
    ON_wString bitmap_filename;
    if (rc) rc = file.ReadString( bitmap_filename );
    if (rc)
      m_image_file_reference.SetFullPath(bitmap_filename, false);
    if (rc) rc = file.ReadDouble( &m_width );
    if (rc) rc = file.ReadDouble( &m_height );
    if (rc) rc = file.ReadPlane( m_plane );
    if ( minor_version >= 1 )
    {
      if (rc) rc = file.ReadBool(&m_bGrayScale);
      
      if ( minor_version >= 2 )
      {
        if (rc) rc = file.ReadBool(&m_bHidden);
        
        if ( minor_version >= 3 )
        {
          if (rc) rc = file.ReadBool( &m_bFiltered );

          if (rc && minor_version >= 4)
          {
            rc = m_image_file_reference.Read(file);
          }
        }
      }
    }
  }
  else
    rc = false;
  return rc;
}


bool ON_3dmViewTraceImage::operator==( const ON_3dmViewTraceImage& other ) const
{
  if ( m_plane != other.m_plane )
    return false;
  if ( m_width != other.m_width )
    return false;
  if ( m_height != other.m_height )
    return false;
  if( m_image_file_reference.FullPathHash() != other.m_image_file_reference.FullPathHash() )
    return false;
  if ( m_bHidden != other.m_bHidden )
    return false;
  if ( m_bGrayScale != other.m_bGrayScale )
    return false;
  if ( m_bFiltered != other.m_bFiltered )
    return false;
    
  return true;
}

bool ON_3dmViewTraceImage::operator!=( const ON_3dmViewTraceImage& other ) const
{
  return operator==(other) ? false : true;
}


ON_3dmWallpaperImage::ON_3dmWallpaperImage()
{
  Default();
}

ON_3dmWallpaperImage::~ON_3dmWallpaperImage()
{
}

bool ON_3dmWallpaperImage::operator==( const ON_3dmWallpaperImage& other ) const
{
  if ( m_image_file_reference.FullPathHash() != other.m_image_file_reference.FullPathHash() )
    return false;
  if ( m_bHidden != other.m_bHidden )
    return false;
  return ( m_bGrayScale == other.m_bGrayScale );
}

bool ON_3dmWallpaperImage::operator!=( const ON_3dmWallpaperImage& other ) const
{
  return operator==(other) ? false : true;
}

void ON_3dmWallpaperImage::Default()
{
  m_image_file_reference = ON_FileReference::Unset;
  m_bGrayScale = true;
  m_bHidden = false;
}

bool ON_3dmWallpaperImage::Write( ON_BinaryArchive& file ) const
{
  // version  < 200307300 - version 1.0 chunk
  // version >= 200307300 - version 1.1 chunk
  const int minor_version = (file.Archive3dmVersion() >= 60) ? 2 : 1;
  bool rc = file.Write3dmChunkVersion(1,minor_version);
  if (rc) 
  {
    if (rc) rc = file.WriteString( m_image_file_reference.FullPath() );
    if (rc) rc = file.WriteBool( m_bGrayScale );

    if (rc) rc = file.WriteBool( m_bHidden ); // added in 1.1 chunk

    if (rc && minor_version >= 2)
    {
      rc = m_image_file_reference.Write(true, file);
    }
  }
  return rc;
}

bool ON_3dmWallpaperImage::Read( ON_BinaryArchive& file )
{
  // version  < 200307300 - version 1.0 chunk
  // version >= 200307300 - version 1.1 chunk
  Default();
  int major_version = 0;
  int minor_version = 0;
  bool rc = file.Read3dmChunkVersion(&major_version,&minor_version);
  if (rc && major_version==1)
  {
    ON_wString bitmap_filename;
    if (rc) rc = file.ReadString( bitmap_filename );
    if (rc)
      m_image_file_reference.SetFullPath(bitmap_filename,false);
    if (rc) rc = file.ReadBool( &m_bGrayScale );

    if ( minor_version >= 1 )
    {
      if (rc) rc = file.ReadBool( &m_bHidden );
      if (rc && minor_version >= 2)
      {
        rc = m_image_file_reference.Read(file);
      }
    }
  }
  else
    rc = false;
  return rc;
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmView
//

ON_3dmPageSettings::ON_3dmPageSettings()
{
  Default();
}

ON_3dmPageSettings::~ON_3dmPageSettings()
{
}

void ON_3dmPageSettings::Default()
{
  m_page_number = 0;

  m_width_mm  = 0.0;
  m_height_mm = 0.0;

  m_left_margin_mm   = 0.0;
  m_right_margin_mm  = 0.0;
  m_top_margin_mm    = 0.0;
  m_bottom_margin_mm = 0.0;

  m_printer_name.Destroy();
}


bool ON_3dmPageSettings::IsValid( ON_TextLog* text_log ) const
{
  bool rc = true;

  if ( m_width_mm != 0.0 || m_height_mm != 0.0 )
  {
    if ( !ON_IsValid(m_width_mm) || m_width_mm <= 0.0 )
    {
      if ( text_log )
      {
        text_log->Print("ON_3dmPageSettings has m_width_mm = %g (should be > 0.0).\n",m_width_mm);
      }
      rc = false;
    }
    if ( !ON_IsValid(m_height_mm) || m_height_mm <= 0.0 )
    {
      if ( text_log )
      {
        text_log->Print("ON_3dmPageSettings has m_height_mm = %g (should be > 0.0).\n",m_height_mm);
      }
      rc = false;
    }
    if ( !ON_IsValid(m_top_margin_mm) || m_top_margin_mm < 0.0 )
    {
      if ( text_log )
      {
        text_log->Print("ON_3dmPageSettings has m_top_margin_mm = %g (should be >= 0.0).\n",m_top_margin_mm);
      }
      rc = false;
    }
    if ( !ON_IsValid(m_bottom_margin_mm) || m_bottom_margin_mm < 0.0 )
    {
      if ( text_log )
      {
        text_log->Print("ON_3dmPageSettings has m_bottom_margin_mm = %g (should be >= 0.0).\n",m_bottom_margin_mm);
      }
      rc = false;
    }
    if ( !ON_IsValid(m_left_margin_mm) || m_left_margin_mm < 0.0 )
    {
      if ( text_log )
      {
        text_log->Print("ON_3dmPageSettings has m_left_margin_mm = %g (should be >= 0.0).\n",m_left_margin_mm);
      }
      rc = false;
    }
    if ( !ON_IsValid(m_right_margin_mm) || m_right_margin_mm < 0.0 )
    {
      if ( text_log )
      {
        text_log->Print("ON_3dmPageSettings has m_right_margin_mm = %g (should be >= 0.0).\n",m_right_margin_mm);
      }
      rc = false;
    }
    if ( m_left_margin_mm + m_right_margin_mm >= m_width_mm )
    {
      if ( text_log )
      {
        text_log->Print("ON_3dmPageSettings has m_left_margin_mm+m_right_margin_mm = %g > %g = m_width_mm.\n",m_left_margin_mm + m_right_margin_mm, m_width_mm);
      }
      rc = false;
    }
    if ( m_top_margin_mm + m_bottom_margin_mm >= m_height_mm )
    {
      if ( text_log )
      {
        text_log->Print("ON_3dmPageSettings has m_top_margin_mm+m_bottom_margin_mm = %g > %g = m_height_mm.\n",m_top_margin_mm + m_bottom_margin_mm, m_height_mm);
      }
      rc = false;
    }
  }
  else
  {
    if ( m_top_margin_mm != 0.0 )
    {
      if ( text_log )
      {
        text_log->Print("ON_3dmPageSettings has m_top_margin_mm = %g (should be 0.0).\n",m_top_margin_mm);
      }
      rc = false;
    }
    if ( m_bottom_margin_mm != 0.0 )
    {
      if ( text_log )
      {
        text_log->Print("ON_3dmPageSettings has m_bottom_margin_mm = %g (should be 0.0).\n",m_bottom_margin_mm);
      }
      rc = false;
    }
    if ( m_left_margin_mm != 0.0 )
    {
      if ( text_log )
      {
        text_log->Print("ON_3dmPageSettings has m_left_margin_mm = %g (should be 0.0).\n",m_left_margin_mm);
      }
      rc = false;
    }
    if ( m_right_margin_mm != 0.0 )
    {
      if ( text_log )
      {
        text_log->Print("ON_3dmPageSettings has m_right_margin_mm = %g (should be 0.0).\n",m_right_margin_mm);
      }
      rc = false;
    }
  }

  return rc;
}

bool ON_3dmPageSettings::Write(ON_BinaryArchive& archive) const
{
  bool rc = archive.BeginWrite3dmChunk( TCODE_ANONYMOUS_CHUNK, 1, 0 );
  if ( !rc )
    return false;

  for(;;)
  {
    rc = archive.WriteInt( m_page_number );
    if (!rc) break;

    rc = archive.WriteDouble(m_width_mm);
    if ( !rc) break;

    rc = archive.WriteDouble(m_height_mm);
    if ( !rc) break;

    rc = archive.WriteDouble(m_left_margin_mm);
    if ( !rc) break;

    rc = archive.WriteDouble(m_right_margin_mm);
    if ( !rc) break;

    rc = archive.WriteDouble(m_top_margin_mm);
    if ( !rc) break;

    rc = archive.WriteDouble(m_bottom_margin_mm);
    if ( !rc) break;

    rc = archive.WriteString(m_printer_name);
    if (!rc) break;

    break;
  }

  if ( !archive.EndWrite3dmChunk() )
    rc = false;

  return rc;
}

bool ON_3dmPageSettings::Read(ON_BinaryArchive& archive)
{
  int major_version = 0;
  int minor_version = 0;
  bool rc = archive.BeginRead3dmChunk( TCODE_ANONYMOUS_CHUNK, &major_version, &minor_version );
  if ( !rc )
    return false;

  for(;;)
  {
    rc = (1 == major_version);
    if (!rc) break;

    rc = archive.ReadInt(&m_page_number );
    if (!rc) break;

    rc = archive.ReadDouble(&m_width_mm);
    if ( !rc) break;

    rc = archive.ReadDouble(&m_height_mm);
    if ( !rc) break;

    rc = archive.ReadDouble(&m_left_margin_mm);
    if ( !rc) break;

    rc = archive.ReadDouble(&m_right_margin_mm);
    if ( !rc) break;

    rc = archive.ReadDouble(&m_top_margin_mm);
    if ( !rc) break;

    rc = archive.ReadDouble(&m_bottom_margin_mm);
    if ( !rc) break;

    rc = archive.ReadString(m_printer_name);
    if (!rc) break;

    break;
  }

  if ( !archive.EndRead3dmChunk() )
    rc = false;

  return rc;
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_StandardDisplayModeId
//



bool ON_StandardDisplayModeId::IsStandardDisplayModeId(
    ON_UUID id
    )
{
  if ( ON_StandardDisplayModeId::Wireframe == id )
    return true;
  if ( ON_StandardDisplayModeId::Shaded == id )
    return true;
  if ( ON_StandardDisplayModeId::Rendered == id )
    return true;
  if ( ON_StandardDisplayModeId::Ghosted == id )
    return true;
  if ( ON_StandardDisplayModeId::XrayShade == id )
    return true;
  if ( ON_StandardDisplayModeId::RenderedShadows == id )
    return true;
  if ( ON_StandardDisplayModeId::Technical == id )
    return true;
  if ( ON_StandardDisplayModeId::Artistic == id )
    return true;
  if ( ON_StandardDisplayModeId::Pen == id )
    return true;
  if (ON_StandardDisplayModeId::Monochrome == id)
    return true;
  if ( ON_StandardDisplayModeId::AmbientOcclusion == id)
    return true;
  if ( ON_StandardDisplayModeId::Raytraced == id)
    return true;

  return false;
}


ON::v3_display_mode ON_StandardDisplayModeId::ToV3DisplayMode(
  ON_UUID id
  )
{
  if ( ON_nil_uuid == id )
    return ON::v3_default_display;

  if ( ON_StandardDisplayModeId::Wireframe == id )
    return ON::v3_wireframe_display;

  if ( ON_StandardDisplayModeId::Shaded == id )
    return ON::v3_shaded_display;

  if ( ON_StandardDisplayModeId::Rendered == id )
    return ON::v3_renderpreview_display;

  if ( ON_StandardDisplayModeId::IsStandardDisplayModeId(id) )
    return ON::v3_shaded_display;

  return ON::v3_default_display;
}

ON_UUID ON_StandardDisplayModeId::FromV3DisplayMode(
  ON::v3_display_mode dm
  )
{
  ON_UUID id;
  switch ( dm )
  {
  case ON::v3_default_display:
    id = ON_nil_uuid;
    break;

  case ON::v3_wireframe_display:
    id = ON_StandardDisplayModeId::Wireframe;
    break;

  case ON::v3_shaded_display:
    id = ON_StandardDisplayModeId::Shaded;
    break;

  case ON::v3_renderpreview_display:
    id = ON_StandardDisplayModeId::Rendered;
    break;

  default:
    id = ON_nil_uuid;
    break;
  }

  return id;
}

//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmView
//
ON_3dmView::ON_3dmView()
{
  Default();
} 

ON_3dmView::~ON_3dmView()
{
}

void ON_3dmView::Dump( ON_TextLog& dump ) const
{
  const wchar_t* wsViewName = static_cast< const wchar_t* >(m_name);
  if ( !wsViewName )
    wsViewName = L"";
  ON::view_projection proj = m_vp.Projection();
  

  ON_3dPoint camLoc;
  ON_3dVector camX, camY, camZ;
  bool bValidCamera = m_vp.GetCameraFrame( camLoc, camX, camY, camZ );
  double frus_left,frus_right,frus_bottom,frus_top,frus_near,frus_far;
  bool bValidFrustum = m_vp.GetFrustum(&frus_left,&frus_right,&frus_bottom,&frus_top,&frus_near,&frus_far);
  int port_left, port_right, port_bottom, port_top, port_near, port_far;
  bool bValidPort = m_vp.GetScreenPort(&port_left,&port_right,&port_bottom,&port_top,&port_near,&port_far);

  const char* sProjectionName;
  switch(proj)
  {
  case ON::parallel_view: sProjectionName = "parallel"; break;
  case ON::perspective_view: sProjectionName = "perspective"; break;
  case ON::unknown_view:
  default: 
    sProjectionName = "unknown";
    break;
  }
  dump.Print("Viewport: name = \"%ls\" projection = %s\n",wsViewName,sProjectionName);

  dump.PushIndent();

  if ( bValidCamera ) 
  {
    dump.Print("viewport camera frame\n"
           "  location = %g, %g, %g\n"
           "  X = %g, %g, %g\n"
           "  Y = %g, %g, %g\n"
           "  Z = %g, %g, %g\n",
           camLoc.x,camLoc.y,camLoc.z,
           camX.x,camX.y,camX.z,
           camY.x,camY.y,camY.z,
           camZ.x,camZ.y,camZ.z
           );
    ON_3dPoint target_point = TargetPoint();
    double target_distance = target_point.DistanceTo( camLoc );
    dump.Print("camera target\n"
               "  distance = %g\n"
               "  point = %g,%g,%g\n",
               target_distance,
               target_point.x,target_point.y,target_point.z
               );
  }


  if ( bValidFrustum ) {
    dump.Print("view frustum\n"
           "  left   = %g, right = %g\n"
           "  bottom = %g, top   = %g\n"
           "  near   = %g, far   = %g\n",
           frus_left,frus_right,
           frus_bottom,frus_top,
           frus_near,frus_far
           );
  }

  if ( bValidPort ) {
    // location of viewport window on screen
    dump.Print("viewport window screen location\n"
           "  left   = %4d, right = %4d\n"
           "  bottom = %4d, top   = %4d\n"
           "  near   = %4d, far   = %4d\n",
           port_left,port_right,
           port_bottom,port_top,
           port_near,port_far
           );
  }


  // relative position of viewport window in application main frame
  double rel_left,rel_right,rel_bottom,rel_top;
  rel_left = m_position.m_wnd_left;
  rel_right = m_position.m_wnd_right;
  rel_bottom = m_position.m_wnd_bottom;
  rel_top = m_position.m_wnd_top;
  dump.Print("relative viewport window position in application frame window\n"
             "  left   = %6.2f%%, right = %6.2f%%\n"
             "  bottom = %6.2f%%, top   = %6.2f%%\n",
             100.0*rel_left, 100.0*rel_right,
             100.0*rel_bottom, 100.0*rel_top
             );

  dump.PopIndent();

}

void ON_3dmView::Default()
{
  m_name.Destroy();

  m_vp = ON_Viewport::DefaultTopViewYUp;

  m_cplane.Default();
  m_display_mode_id = ON_nil_uuid;
  m_view_type = ON::model_view_type;
  m_position.Default();
  if ( m_vp.Projection() == ON::parallel_view ) {
    m_cplane.m_plane.CreateFromFrame( m_cplane.m_plane.origin, m_vp.CameraX(), m_vp.CameraY() );
  }
  m_bShowConstructionGrid = true;
  m_bShowConstructionAxes = true;
  m_bShowWorldAxes = true;
  m_bShowConstructionZAxis = false;

  m_trace_image.Default();
  m_wallpaper_image.Default();

  m_page_settings.Default();

  m_named_view_id = ON_nil_uuid;

  m_bLockedProjection = false;

  m_dFocalBlurDistance = 100.0;
  m_dFocalBlurAperture = 64.0;
  m_dFocalBlurJitter = 0.1;
  m_uFocalBlurSampleCount = 10;
  m_FocalBlurMode = ON_FocalBlurModes::None;
  m_sizeRendering.cx = 640;
  m_sizeRendering.cy = 480;
}

ON::ViewSectionBehavior ON_3dmView::SectionBehavior() const
{
  return m_section_behavior;
}
void ON_3dmView::SetSectionBehavior(ON::ViewSectionBehavior behavior)
{
  m_section_behavior = behavior;
}


ON_3dPoint ON_3dmView::TargetPoint() const
{
  // This function must return the valid saved on m_vp.m_target_point.
  // Do not modify that value here.
  return m_vp.TargetPoint();
}

bool ON_3dmView::SetTargetPoint(ON_3dPoint target_point)
{
  return m_vp.SetTargetPoint(target_point);
}

bool ON_3dmView::IsValid(ON_TextLog* text_log) const
{
  bool rc = m_vp.IsValid(text_log)?true:false;
  while(rc)
  {
    switch(m_view_type)
    {
    case ON::model_view_type:
      if ( m_page_settings.m_width_mm != 0.0 || m_page_settings.m_height_mm != 0.0 )
      {
        if ( text_log )
        {
          text_log->Print("ON_3dmView has m_view_type = ON::model_view_type but m_page_settings width,height = (%g,%g) (both should be zero).\n",
                          m_page_settings.m_width_mm,
                          m_page_settings.m_height_mm);
        }
        rc = false;
      }
      //if (    m_nested_view_position.m_min.x != 0.0 || m_nested_view_position.m_max.x != 0.0
      //     || m_nested_view_position.m_min.y != 0.0 || m_nested_view_position.m_max.y != 0.0
      //     || m_nested_view_position.m_min.z != 0.0 || m_nested_view_position.m_max.z != 0.0 )
      //{
      //  if ( text_log )
      //  {
      //    text_log->Print("ON_3dmView has m_view_type = ON::model_view_type and m_nested_view_position is not identically zero.\n");
      //  }
      //  rc = false;
      //}
      //if ( !ON_UuidIsNil(m_parent_viewport_id) )
      //{
      //  if ( text_log )
      //  {
      //    text_log->Print("ON_3dmView has m_view_type = ON::model_view_type and m_parent_viewport_id is not nil\n");
      //  }
      //  rc = false;
      //}
      break;
    case ON::page_view_type:
      //if (    m_nested_view_position.m_min.x != 0.0 || m_nested_view_position.m_max.x != 0.0
      //     || m_nested_view_position.m_min.y != 0.0 || m_nested_view_position.m_max.y != 0.0
      //     || m_nested_view_position.m_min.z != 0.0 || m_nested_view_position.m_max.z != 0.0 )
      //{
      //  if ( text_log )
      //  {
      //    text_log->Print("ON_3dmView has m_view_type = ON::page_view_type and m_nested_view_position is not identically zero.\n");
      //  }
      //  rc = false;
      //}
      //if ( !ON_UuidIsNil(m_parent_viewport_id) )
      //{
      //  if ( text_log )
      //  {
      //    text_log->Print("ON_3dmView has m_view_type = ON::page_view_type and m_parent_viewport_id is not nil\n");
      //  }
      //  rc = false;
      //}
      if ( m_page_settings.m_width_mm <= 0.0 || m_page_settings.m_height_mm <= 0.0 )
      {
        if ( text_log )
        {
          text_log->Print("ON_3dmView has m_view_type = ON::page_view_type but page width,height = (%g,%g)\n",
                          m_page_settings.m_width_mm,
                          m_page_settings.m_height_mm);
        }
        rc = false;
      }
      break;

    case ON::nested_view_type:
      if ( m_page_settings.m_width_mm != 0.0 || m_page_settings.m_height_mm != 0.0 )
      {
        if ( text_log )
        {
          text_log->Print("ON_3dmView has m_view_type = ON::nested_view_type but m_page_settings width,height = (%g,%g) (both should be zero).\n",
                          m_page_settings.m_width_mm,
                          m_page_settings.m_height_mm);
        }
        rc = false;
      }
      //if ( ON_UuidIsNil(m_parent_viewport_id) )
      //{
      //  if ( text_log )
      //  {
      //    text_log->Print("ON_3dmView has m_view_type = ON::nested_view_type and m_parent_viewport_id is nil.\n");
      //  }
      //  rc = false;
      //}

      //if ( !m_nested_view_position.IsValid() 
      //     || m_nested_view_position.m_min.x >= m_nested_view_position.m_max.x
      //     || m_nested_view_position.m_min.y >= m_nested_view_position.m_max.y
      //     || m_nested_view_position.m_min.z != m_nested_view_position.m_max.z )
      //{
      //  if ( text_log )
      //  {
      //    text_log->Print("ON_3dmView has m_view_type = ON::nested_view_type and m_nested_view_position is bogus.\n");
      //  }
      //  rc = false;
      //}
      break;

    case ON::uveditor_view_type:
      break;

    case ON::blockeditor_view_type:
      break;

    default:
      if ( text_log )
      {
        text_log->Print("ON_3dmView m_view_type = %d (illegal enum value)\n",m_view_type);
      }
      rc = false;
      break;
    }
    if (rc)
      break;




    break;
  }
  return rc;
}

bool ON_3dmView::Write( ON_BinaryArchive& file ) const
{
  // Everything in a view is in a subchunk so new records can 
  // be added to a view and old I/O code will still
  // work.
  bool rc = true;

  // 27 June 2008 Dale Lear
  //   I added support for saving userdata attached to
  //   the m_vp ON_Viewport.  Ideally, I would just call
  //   file.WriteObject(m_vp), but userdata support is being
  //   added years after millions of files have been written
  //   by calling m_vp.Write().
  if(rc) {
    rc = file.BeginWrite3dmChunk( TCODE_VIEW_VIEWPORT, 0 );
    if(rc) {
      rc = m_vp.Write(file)?true:false;
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }
  if(rc && file.Archive3dmVersion() >= 4 && file.ObjectHasUserDataToWrite(&m_vp) ) 
  {
    rc = file.BeginWrite3dmChunk( TCODE_VIEW_VIEWPORT_USERDATA, 0 );
    if(rc) 
    {
      rc = file.WriteObjectUserData(m_vp);
      // write a "fake" TCODE_OPENNURBS_CLASS_END end of class 
      // mark so I can use
      // ON_BinaryArchive::ReadObjectUserData() 
      // to read this user data.
      if ( file.BeginWrite3dmChunk( TCODE_OPENNURBS_CLASS_END, 0 ) ) 
      {
        if ( !file.EndWrite3dmChunk() )
          rc = false;
      }
      else
      {
        rc = false;
      }
      if ( !file.EndWrite3dmChunk() ) // end of TCODE_VIEW_VIEWPORT_USERDATA
        rc = false;
    }
  }
  if(rc) {
    rc = file.BeginWrite3dmChunk( TCODE_VIEW_CPLANE, 0 );
    if(rc) {
      rc = m_cplane.Write(file);
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }
  if(rc) {
    rc = file.BeginWrite3dmChunk( TCODE_VIEW_TARGET, 0 );
    if(rc) {
      ON_3dPoint target_point = TargetPoint();
      if(rc) rc = file.WritePoint(target_point);
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }
  if(rc) {
    ON::v3_display_mode dm = ON_StandardDisplayModeId::ToV3DisplayMode( m_display_mode_id );
    rc = file.BeginWrite3dmChunk( TCODE_VIEW_V3_DISPLAYMODE, dm );
    if(rc) {
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }
  if(rc) {
    rc = file.BeginWrite3dmChunk( TCODE_VIEW_POSITION, 0 );
    if(rc) {
      if(rc) rc = m_position.Write(file);
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }
  if(rc) {
    rc = file.BeginWrite3dmChunk( TCODE_VIEW_SHOWCONGRID, m_bShowConstructionGrid );
    if(rc) {
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }
  if(rc) {
    rc = file.BeginWrite3dmChunk( TCODE_VIEW_SHOWCONAXES, m_bShowConstructionAxes );
    if(rc) {
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }
  if(rc) {
    rc = file.BeginWrite3dmChunk( TCODE_VIEW_SHOWWORLDAXES, m_bShowWorldAxes );
    if(rc) {
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }
  if(rc) {
    rc = file.BeginWrite3dmChunk( TCODE_VIEW_NAME, 0 );
    if(rc) {
      if(rc) rc = file.WriteString(m_name);
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }
  if(rc) {
    rc = file.BeginWrite3dmChunk( TCODE_VIEW_TRACEIMAGE, 0 );
    if(rc) 
    {
      if(rc) 
        rc = m_trace_image.Write(file);
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }
  if(rc) 
  {
    rc = file.BeginWrite3dmChunk( TCODE_VIEW_WALLPAPER, 0 );
    if(rc) 
    {
      if(rc) rc = file.WriteString(m_wallpaper_image.m_image_file_reference.FullPath());
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }
  if(rc && file.Archive3dmVersion() >= 3 ) 
  {
    // Added 5 June 2003 to support additional wallpaper attributes.
    // Older versions of Rhino/opennurbs
    // will just skip this chunk and get filename from the
    // TCODE_VIEW_WALLPAPER chunk written above.
    rc = file.BeginWrite3dmChunk( TCODE_VIEW_WALLPAPER_V3, 0 );
    if(rc) 
    {
      if(rc) 
        rc = m_wallpaper_image.Write(file);
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }

  if (rc && file.Archive3dmVersion() >= 4)
  {
    // 23 March 2005 Dale Lear:
    //   The "chunks" above trace their history back to Rhino 1.0;
    //   The TCODE_VIEW_ATTRIBUTES chunk uses a chunk version so that
    //   new view information can be added without inventing a new 
    //   TCODE for each new piece of information.

    rc = file.BeginWrite3dmChunk( TCODE_VIEW_ATTRIBUTES, 0 );
    if (rc)
    {
      rc = file.Write3dmChunkVersion( 1, 9 ); // (there are no 1.0 fields)

      while(rc)
      {
        // 1.1 fields (there are no 1.0 fields)
        rc = file.WriteInt( m_view_type );
        if (!rc) break;
        
        // obsolete values - superceded by m_page_settings
        rc = file.WriteDouble( m_page_settings.m_width_mm );
        if (!rc) break;

        rc = file.WriteDouble( m_page_settings.m_height_mm );
        if (!rc) break;

        ON_UUID obsolete_parent_viewport_id;
        memset(&obsolete_parent_viewport_id,0,sizeof(obsolete_parent_viewport_id));
        rc = file.WriteUuid( obsolete_parent_viewport_id );
        if (!rc) break;

        ON_BoundingBox obsolete_nested_view_position;
        rc = file.WriteBoundingBox( obsolete_nested_view_position );
        if (!rc) break;

        // 28 feb 2006 version 1.2 fields
        rc = file.WriteUuid(m_display_mode_id);
        if (!rc) break;

        rc = m_page_settings.Write(file);
        if (!rc) break;

        // 7 March 2006 version 1.3 fields
        rc = file.WriteBool(m_bLockedProjection);
        if (!rc) break;

        // 12 December 2010 version 1.4
        rc = file.WriteArray(m_clipping_planes);
        if (!rc) break;

        // 13 June 2013 version 1.5
        rc = file.WriteUuid(m_named_view_id);
        if (!rc) break;

        // 8 Dec 2016 version 1.6 (ALB)
        rc = file.WriteBool(m_bShowConstructionZAxis);
        if (!rc) break;

        // 6 June 2017 - Andy.  version 1.7 fields
        rc = file.WriteDouble(m_dFocalBlurDistance);
        if (!rc) break;

        rc = file.WriteDouble(m_dFocalBlurAperture);
        if (!rc) break;

        rc = file.WriteDouble(m_dFocalBlurJitter);
        if (!rc) break;

        rc = file.WriteInt(m_uFocalBlurSampleCount);
        if (!rc) break;

        rc = file.WriteInt((int)m_FocalBlurMode);
        if (!rc) break;

        // 4 August 2017 - Andy.  version 1.8 fields
        rc = file.WriteInt(m_sizeRendering.cx);
        if (!rc) break;

        rc = file.WriteInt(m_sizeRendering.cy);
        if (!rc) break;

        // 10 July 2022 - S. Baer version 1.9 fields
        rc = file.WriteChar((unsigned char)SectionBehavior());
        if (!rc) break;

        break;
      }

      // Since BeginWrite3dmChunk() returned true, EndWrite3dmChunk()
      // must be called even when rc is false
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }

  // required TCODE_ENDOFTABLE chunk - marks end of view table
  if ( rc ) {
    rc = file.BeginWrite3dmChunk( TCODE_ENDOFTABLE, 0 );
    if ( rc ) {
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }
  return rc;
}

bool ON_3dmView::Read( ON_BinaryArchive& file )
{
  // Everything in a view is in a subchunk so new records can 
  // be added to a view and old I/O code will still
  // work.
  ON_3dPoint obsolete_target_point = ON_3dPoint::UnsetPoint;
  unsigned int tcode = 0;
  ON__INT64 big_value = 0;
  int i32;
  bool rc = true;

  Default();

  while(rc) {
    rc = file.BeginRead3dmBigChunk(&tcode,&big_value);
    if (!rc)
      break;
    switch(tcode) 
    {
    case TCODE_VIEW_CPLANE:
      rc = m_cplane.Read(file);
      break;
    case TCODE_VIEW_VIEWPORT:
      rc = m_vp.Read(file)?true:false;
      break;
    case TCODE_VIEW_VIEWPORT_USERDATA:
      // 27 June 2008 Dale Lear
      //   I added support for saving userdata attached to
      //   the m_vp ON_Viewport.  Ideally, the ON_Viewport
      //   would be read by calling file.ReadObject(), but
      //   userdata support is being added years after 
      //   millions of files have been written by calling
      //   m_vp.Write()/Read().
      rc = file.ReadObjectUserData(m_vp);
      break;
    case TCODE_VIEW_SHOWCONGRID:
      m_bShowConstructionGrid = big_value?true:false;
      break;
    case TCODE_VIEW_SHOWCONAXES:
      m_bShowConstructionAxes = big_value?true:false;
      break;
    case TCODE_VIEW_SHOWWORLDAXES:
      m_bShowWorldAxes = big_value?true:false;
      break;
    case TCODE_VIEW_TRACEIMAGE:
      rc = m_trace_image.Read(file);
      break;
    case TCODE_VIEW_WALLPAPER:
      // used prior to 5 June 2003 and still written
      // after 5 June 2003 so older Rhinos/opennurbs
      // will not loose the filename information.
      {
        ON_wString bitmap_filename;
        rc = file.ReadString(bitmap_filename);
        m_wallpaper_image.m_image_file_reference.SetFullPath(bitmap_filename,false);
      }
      m_wallpaper_image.m_bGrayScale = true;
      break;
    case TCODE_VIEW_WALLPAPER_V3:
      // Added 5 June 2003 to support additional wallpaper attributes.
      rc = m_wallpaper_image.Read(file);
      break;
    case TCODE_VIEW_TARGET:
      // 13 June 2013
      // This point has been obsolete for more than 5 years 
      // and is now ignored.  The target point is on ON_Viewport.
      rc = file.ReadPoint(obsolete_target_point);
      break;
    case TCODE_VIEW_V3_DISPLAYMODE:
      if ( ON_nil_uuid == m_display_mode_id )
      {
        i32 = (int)big_value;
        ON::v3_display_mode dm = ON::V3DisplayMode(i32);
        m_display_mode_id = ON_StandardDisplayModeId::FromV3DisplayMode(dm);
      }
      break;
    case TCODE_VIEW_NAME:
      rc = file.ReadString(m_name);
      break;
    case TCODE_VIEW_POSITION:
      rc = m_position.Read(file);
      break;

    case TCODE_VIEW_ATTRIBUTES:
      {
        int major_version = 0;
        int minor_version = 0;
        rc = file.Read3dmChunkVersion(&major_version,&minor_version);
        // there are no 1.0 fields in this chunk
        while ( rc 
                && major_version == 1 && minor_version >= 1 
                && file.Archive3dmVersion() >= 4 
                && file.ArchiveOpenNURBSVersion() >= 200503170 )
        {
          // Added 23 March 2005 Dale Lear
          // 1.1 fields (there are no 1.0 fields)
          i32 = 0;
          rc = file.ReadInt( &i32 );
          if (!rc) break;
          m_view_type = ON::ViewType(i32);
          
          rc = file.ReadDouble( &m_page_settings.m_width_mm );
          if (!rc) break;

          rc = file.ReadDouble( &m_page_settings.m_height_mm );
          if (!rc) break;

          ON_UUID obsolete_parent_viewport_id;
          rc = file.ReadUuid( obsolete_parent_viewport_id );
          if (!rc) break;

          ON_BoundingBox obsolete_nested_view_position;
          rc = file.ReadBoundingBox( obsolete_nested_view_position );
          if (!rc) break;

          if ( minor_version >= 2 )
          {
            // 28 feb 2006 version 1.2 field
            rc = file.ReadUuid(m_display_mode_id);
            if (!rc) break;

            rc = m_page_settings.Read(file);
            if (!rc) break;

            if ( minor_version >= 3 )
            {
              rc = file.ReadBool(&m_bLockedProjection);
              if (!rc) break;

              if ( minor_version >= 4 )
              {
                rc = file.ReadArray(m_clipping_planes);
                if (!rc) break;
                if ( minor_version >= 5 )
                {
                  // 13 June 2013 version 1.5 field
                  rc = file.ReadUuid(m_named_view_id);
                  if (!rc) break;
                  if (minor_version >= 6)
                  {
                    // 8 Dec 2016 version 1.6 field (ALB)
                    rc = file.ReadBool(&m_bShowConstructionZAxis);
                    if (!rc) break;
                    if (minor_version >= 7)
                    {
                      // 11 May 2016 - Andy.  version 1.7 fields
                      rc = file.ReadDouble(&m_dFocalBlurDistance);
                      if (!rc) break;

                      rc = file.ReadDouble(&m_dFocalBlurAperture);
                      if (!rc) break;

                      rc = file.ReadDouble(&m_dFocalBlurJitter);
                      if (!rc) break;

                      rc = file.ReadInt((int*)&m_uFocalBlurSampleCount);
                      if (!rc) break;

                      rc = file.ReadInt((int*)&m_FocalBlurMode);
                      if (!rc) break;
                      if (minor_version >= 8)
                      {
                        // 4 August 2017 - Andy.  version 1.8 fields
                        rc = file.ReadInt(&m_sizeRendering.cx);
                        if (!rc) break;
                        rc = file.ReadInt(&m_sizeRendering.cy);
                        if (!rc) break;
                      }
                      if (minor_version >= 9)
                      {
                        // 9 July 2022 S. Baer add section behaviour
                        unsigned char c = 0;
                        rc = file.ReadChar(&c);
                        if (!rc) break;
                        SetSectionBehavior(ON::ViewSectionBehaviorFromUnsigned(c));
                      }
                    }
                  }
                }
              }
            }
          }

          // Add new information here - ask Dale Lear for help.

          break;
        }
      }
      break;
    }

    if (!file.EndRead3dmChunk())
      rc = false;
    if ( tcode == TCODE_ENDOFTABLE )
      break;
  }

  if ( obsolete_target_point.IsValid() && m_vp.TargetPoint().IsUnset() )
    m_vp.SetTargetPoint(obsolete_target_point);

  return rc;
}

double ON_3dmView::FocalBlurDistance(void) const
{
  return m_dFocalBlurDistance;
}

void ON_3dmView::SetFocalBlurDistance(double d)
{
  m_dFocalBlurDistance = d;
}

double ON_3dmView::FocalBlurAperture(void) const
{
  return m_dFocalBlurAperture;
}

void ON_3dmView::SetFocalBlurAperture(double d)
{
  m_dFocalBlurAperture = d;
}

double ON_3dmView::FocalBlurJitter(void) const
{
  return m_dFocalBlurJitter;
}

void ON_3dmView::SetFocalBlurJitter(double d)
{
  m_dFocalBlurJitter = d;
}

unsigned int ON_3dmView::FocalBlurSampleCount(void) const
{
  return m_uFocalBlurSampleCount;
}

void ON_3dmView::SetFocalBlurSampleCount(unsigned int sc)
{
  m_uFocalBlurSampleCount = sc;
}

ON_FocalBlurModes ON_3dmView::FocalBlurMode(void) const
{
  return m_FocalBlurMode;
}

void ON_3dmView::SetFocalBlurMode(ON_FocalBlurModes m)
{
  m_FocalBlurMode = m;
}


ON_2iSize ON_3dmView::RenderingSize() const
{
  return m_sizeRendering;
}

void ON_3dmView::SetRenderingSize(const ON_2iSize& size)
{
  m_sizeRendering = size;
}

int ON_EarthAnchorPoint::CompareEarthLocation(const ON_EarthAnchorPoint* a, const ON_EarthAnchorPoint* b)
{
  if ( !a )
  {
    return b ? -1 : 0;
  }
  if (!b)
  {
    return 1;
  }

  double xa = a->m_earth_longitude;
  double xb = b->m_earth_longitude;
  if ( !ON_IsValid(xa) )
  {
    if ( ON_IsValid(xb) ) return -1;
  }
  else if ( !ON_IsValid(xb) )
  {
    return 1;
  }
  else
  {
    while(xa <= 0.0)
      xa += 360.0;
    while(xa > 360.0)
      xa -= 360.0;
    while(xb <= 0.0)
      xb += 360.0;
    while(xb > 360.0)
      xb -= 360.0;
    if ( xa < xb ) return -1;
    if ( xa > xb ) return 1;
  }

  xa = a->m_earth_latitude;
  xb = b->m_earth_latitude;
  if ( !ON_IsValid(xa) )
  {
    if ( ON_IsValid(xb) ) return -1;
  }
  else if ( !ON_IsValid(xb) )
  {
    return 1;
  }
  else
  {
    while(xa <= 0.0)
      xa += 360.0;
    while(xa > 360.0)
      xa -= 360.0;
    while(xb <= 0.0)
      xb += 360.0;
    while(xb > 360.0)
      xb -= 360.0;
    if ( xa < xb ) return -1;
    if ( xa > xb ) return 1;
  }

  const unsigned int aecs = static_cast<unsigned char>(a->m_earth_coordinate_system);
  const unsigned int becs = static_cast<unsigned char>(a->m_earth_coordinate_system);
  if (aecs < becs)
    return -1;
  if (aecs > becs)
    return 1;

  xa = a->m_earth_elevation_meters;
  xb = b->m_earth_elevation_meters;
  if ( !ON_IsValid(xa) )
  {
    if ( ON_IsValid(xb) ) return -1;
  }
  else if ( !ON_IsValid(xb) )
  {
    return 1;
  }
  else
  {
    if ( xa < xb ) return -1;
    if ( xa > xb ) return 1;
  }

  return 0;   
}

int ON_EarthAnchorPoint::CompareModelDirection(const ON_EarthAnchorPoint* a, const ON_EarthAnchorPoint* b)
{
  if ( !a )
  {
    return b ? -1 : 0;
  }
  if (!b)
  {
    return 1;
  }

  int i = ON_ComparePoint(3,false,&a->m_model_point.x,&b->m_model_point.x);
  if ( !i )
  {
    i = ON_ComparePoint(3,false,&a->m_model_north.x,&b->m_model_north.x);
    if ( !i )
    {
      i = ON_ComparePoint(3,false,&a->m_model_east.x,&b->m_model_east.x);
    }
  }
  return i;  
}

int ON_EarthAnchorPoint::CompareIdentification(const ON_EarthAnchorPoint* a, const ON_EarthAnchorPoint* b)
{
  if ( !a )
  {
    return b ? -1 : 0;
  }
  if (!b)
  {
    return 1;
  }

  int i = ON_UuidCompare(a->m_id,b->m_id);
  if ( !i)
  {
    i = a->m_name.CompareOrdinal(b->m_name,false);
    if (!i)
    {
      i = a->m_description.CompareOrdinal(b->m_description,false);
      if (!i)
      {
        i = a->m_url.CompareOrdinal(b->m_url,true);
        if ( !i)
        {
          i = a->m_url_tag.CompareOrdinal(b->m_url_tag,false);
        }
      }
    }
  }
  return i;  
}

int ON_EarthAnchorPoint::Compare(const ON_EarthAnchorPoint* a, const ON_EarthAnchorPoint* b)
{
  int i = ON_EarthAnchorPoint::CompareEarthLocation(a,b);
  if ( !i)
  {
    i = ON_EarthAnchorPoint::CompareModelDirection(a,b);
    if (!i)
    {
      i = ON_EarthAnchorPoint::CompareIdentification(a,b);
    }
  }
  return i;
}

bool ON_EarthAnchorPoint::Read( ON_BinaryArchive& file )
{
  *this = ON_EarthAnchorPoint::Unset;
  
  int major_version = 0;
  int minor_version = 0;
  bool rc = file.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
  if ( !rc )
    return false;

  for(;;)
  {
    rc = (1 == major_version);
    if (!rc) break;

    rc = file.ReadDouble(&m_earth_latitude);
    if (!rc) break;
    rc = file.ReadDouble(&m_earth_longitude);
    if (!rc) break;
    rc = file.ReadDouble(&m_earth_elevation_meters);
    if (!rc) break;

    if (
      minor_version < 2 
      && 0.0 == m_earth_latitude
      && 0.0 == m_earth_longitude 
      && 0.0 == m_earth_elevation_meters
      && file.ArchiveOpenNURBSVersion() <= 2348834428
      )
    {
      m_earth_latitude = ON_EarthAnchorPoint::Unset.m_earth_latitude;
      m_earth_longitude = ON_EarthAnchorPoint::Unset.m_earth_longitude;
      m_earth_elevation_meters = ON_EarthAnchorPoint::Unset.m_earth_elevation_meters;
    }


    rc = file.ReadPoint(m_model_point);
    if (!rc) break;
    rc = file.ReadVector(m_model_north);
    if (!rc) break;
    rc = file.ReadVector(m_model_east);
    if (!rc) break;
   
    if ( minor_version >= 1 )
    {
      // 1.1 fields
      int earth_basepoint_elevation_zero = ON_UNSET_INT_INDEX;
      rc = file.ReadInt(&earth_basepoint_elevation_zero);
      if (!rc) break;
      switch (earth_basepoint_elevation_zero)
      {
      case 0:
        m_earth_coordinate_system = ON::EarthCoordinateSystem::GroundLevel;
        break;
      case 1:
        m_earth_coordinate_system = ON::EarthCoordinateSystem::MeanSeaLevel;
        break;
      case 2:
        m_earth_coordinate_system = ON::EarthCoordinateSystem::CenterOfEarth;
        break;
      default:
        break;
      }
      rc = file.ReadUuid(m_id);
      if (!rc) break;
      rc = file.ReadString(m_name);
      if (!rc) break;
      rc = file.ReadString(m_description);
      if (!rc) break;
      rc = file.ReadString(m_url);
      if (!rc) break;
      rc = file.ReadString(m_url_tag);
      if (!rc) break;

      if (minor_version >= 2)
      {
        unsigned int u;
        
        u = static_cast<unsigned char>(ON_EarthAnchorPoint::Unset.EarthCoordinateSystem());
        rc = file.ReadInt(&u);
        if (!rc) break;
        m_earth_coordinate_system = ON::EarthCoordinateSystemFromUnsigned(u);
      }
    }

    break;
  }

  if ( !file.EndRead3dmChunk() )
    rc = false;

  return rc;
}

static double Internal_UnsetToZeroInV5Files(
  const ON_BinaryArchive& file,
  double value
)
{
  // http://mcneel.myjetbrains.com/youtrack/issue/RH-34700
  // V5 RDK sun dialog expects 0.0 for unset latitude and longitude values
  // and crashes if it encounters ON_UNSET_VALUE.
  return (file.Archive3dmVersion() < 60 && ON_UNSET_VALUE == value)
      ? 0.0
      : value;
}

bool ON_EarthAnchorPoint::Write( ON_BinaryArchive& file ) const
{
  bool rc = file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,2);
  if ( !rc )
    return false;

  for(;;)
  {
    const double earth_latitude = Internal_UnsetToZeroInV5Files(file, m_earth_latitude);
    const double earth_longitude = Internal_UnsetToZeroInV5Files(file, m_earth_longitude);
    rc = file.WriteDouble(earth_latitude);
    if (!rc) break;
    rc = file.WriteDouble(earth_longitude);
    if (!rc) break;
    rc = file.WriteDouble(m_earth_elevation_meters);
    if (!rc) break;
    rc = file.WritePoint(m_model_point);
    if (!rc) break;
    rc = file.WriteVector(m_model_north);
    if (!rc) break;
    rc = file.WriteVector(m_model_east);
    if (!rc) break;

    // 1.1 fields
    int earth_basepoint_elevation_zero;
    switch (m_earth_coordinate_system)
    {
    case ON::EarthCoordinateSystem::GroundLevel:
      earth_basepoint_elevation_zero = 0;
      break;
    case ON::EarthCoordinateSystem::MeanSeaLevel:
      earth_basepoint_elevation_zero = 1;
      break;
    case ON::EarthCoordinateSystem::CenterOfEarth:
      earth_basepoint_elevation_zero = 2;
      break;
    default:
      earth_basepoint_elevation_zero = 0;
      break;
    }
    rc = file.WriteInt(earth_basepoint_elevation_zero); // legacy value for old files
    if (!rc) break;
    rc = file.WriteUuid(m_id);
    if (!rc) break;
    rc = file.WriteString(m_name);
    if (!rc) break;
    rc = file.WriteString(m_description);
    if (!rc) break;
    rc = file.WriteString(m_url);
    if (!rc) break;
    rc = file.WriteString(m_url_tag);
    if (!rc) break;

    // 1.2 fields
    unsigned int u;
    u = static_cast<unsigned char>(ON_EarthAnchorPoint::Unset.EarthCoordinateSystem());
    rc = file.WriteInt(u);
    if (!rc) break;

    break;
  }

  if ( !file.EndWrite3dmChunk() )
    rc = false;

  return rc;
}


bool ON_EarthAnchorPoint::GetModelCompass(ON_Plane& model_compass) const
{
  ON_Plane mc;
  mc.xaxis = m_model_east;
  mc.yaxis = m_model_north;
  if ( fabs(mc.xaxis.Length() - 1.0) > ON_SQRT_EPSILON )
  {
    if ( !mc.xaxis.Unitize() )
      return false;
  }
  if ( fabs(mc.yaxis.Length() - 1.0) > ON_SQRT_EPSILON )
  {
    if ( !mc.yaxis.Unitize() )
      return false;
  }
  double d = mc.xaxis*mc.yaxis;
  if ( fabs(d) > ON_SQRT_EPSILON )
  {
    // assume north is correct
    mc.xaxis.x -= d*mc.yaxis.x;
    mc.xaxis.y -= d*mc.yaxis.y;
    mc.xaxis.z -= d*mc.yaxis.z;
    if( !mc.xaxis.Unitize() )
      return false;
  }
  mc.zaxis = ON_CrossProduct(mc.xaxis,mc.yaxis);
  if ( fabs(mc.zaxis.Length() - 1.0) > ON_SQRT_EPSILON )
  {
    if ( !mc.zaxis.Unitize() )
      return false;
  }
  mc.origin = m_model_point;
  mc.UpdateEquation();
  model_compass = mc;
  return model_compass.IsValid();
}

bool ON_EarthAnchorPoint::EarthLocationIsSet() const
{
  return (
    ON_IsValid(m_earth_latitude)
    && ON_IsValid(m_earth_longitude)
    && ON_IsValid(m_earth_elevation_meters)
  );
}


bool ON_EarthAnchorPoint::ModelLocationIsSet() const
{
  return (
    m_model_point.IsValid()
    && m_model_north.IsNotZero()
    && m_model_east.IsNotZero()
    && m_model_north.Length() > ON_ZERO_TOLERANCE
    && m_model_east.Length() > ON_ZERO_TOLERANCE
    && fabs(m_model_north.UnitVector()* m_model_east.UnitVector()) <= 1e-8
  );
}

bool ON_EarthAnchorPoint::GetModelToEarthXform(
          const ON_UnitSystem& model_unit_system,
          ON_Xform& model_to_earth
          ) const
{
  if (false == EarthLocationIsSet() || false == ModelLocationIsSet())
  {
    model_to_earth = ON_Xform::IdentityTransformation;
    return false;
  }

  // The orient_model rotates the model so that
  //   xaxis runs from west to east
  //   yaxis runs from south to north
  //   zaxis points "up"
  ON_Plane model_compass;
  bool rc = GetModelCompass( model_compass );
  model_compass.origin = m_model_point;
  model_compass.UpdateEquation();
  ON_Xform orient_model;
  orient_model.Rotation( model_compass, ON_xy_plane  );

  ON_Xform coord_change(ON_Xform::IdentityTransformation);

  const double lat_radians = m_earth_latitude/180.0*ON_PI;
  const double cos_lat = cos(lat_radians);
  const double sin_lat = sin(lat_radians);
  
  // get radius of earth at this latitude
  const double earth_polar_radius      = 6356750.0; // Earth's radius at poles (meters)
  const double earth_equatorial_radius = 6378135.0; // Earth's radius at equator (meters)
  ON_2dVector r;
  r.x = cos_lat;
  r.y = sin_lat*(earth_equatorial_radius/earth_polar_radius);
  double earth_radius = earth_equatorial_radius/r.Length();
  if ( earth_radius > earth_equatorial_radius )
    earth_radius = earth_equatorial_radius;
  else if ( earth_radius < earth_polar_radius )
    earth_radius = earth_polar_radius;

  const double meters_per_degree_latitude = earth_radius*ON_PI/180.0; // meters per degree of latitude

  const double model_to_meters_scale = ON::UnitScale(model_unit_system, ON::LengthUnitSystem::Meters);
  const double north_south_scale  = model_to_meters_scale/meters_per_degree_latitude;
  const double east_west_scale = ( 1.0e100*cos_lat < north_south_scale )
                               ? north_south_scale
                               : north_south_scale/cos_lat;

  coord_change.m_xform[0][0] = east_west_scale;
  coord_change.m_xform[0][3] = m_earth_longitude;
  coord_change.m_xform[1][1] = north_south_scale;
  coord_change.m_xform[1][3] = m_earth_latitude;
  coord_change.m_xform[2][2] = model_to_meters_scale;
  coord_change.m_xform[3][2] = m_earth_elevation_meters;

  model_to_earth = coord_change*orient_model;

  return rc;
}


ON::EarthCoordinateSystem ON::EarthCoordinateSystemFromUnsigned(
  unsigned int earth_location_standard_as_unsigned
)
{
  switch (earth_location_standard_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON::EarthCoordinateSystem::Unset);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::EarthCoordinateSystem::GroundLevel);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::EarthCoordinateSystem::MeanSeaLevel);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::EarthCoordinateSystem::CenterOfEarth);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::EarthCoordinateSystem::WGS1984);
    ON_ENUM_FROM_UNSIGNED_CASE(ON::EarthCoordinateSystem::EGM2008);
  };
  ON_ERROR("Invalid earth_location_standard_as_unsigned parameter value");
  return ON::EarthCoordinateSystem::Unset;

}

void ON_EarthAnchorPoint::SetEarthLocation(
  ON::EarthCoordinateSystem earth_coordinate_system,
  const class ON_UnitSystem& elevation_unit_system,
  double latitude_degrees,
  double longitude_degrees,
  double elevation
)
{
  m_earth_coordinate_system = earth_coordinate_system;
  SetLatitudeAndLongitude(latitude_degrees,longitude_degrees);
  SetElevation(elevation_unit_system, elevation);
}

void ON_EarthAnchorPoint::SetEarthLocation(
  ON::EarthCoordinateSystem earth_coordinate_system,
  ON::LengthUnitSystem elevation_unit_system,
  double latitude_degrees,
  double longitude_degrees,
  double elevation
)
{
  ON_UnitSystem us(elevation_unit_system);
  SetEarthLocation(earth_coordinate_system, us, latitude_degrees, longitude_degrees, elevation);
}


ON_3dPoint ON_EarthAnchorPoint::EarthLocation() const
{
  return ON_3dPoint(m_earth_latitude, m_earth_longitude, m_earth_elevation_meters);
}

ON_3dPoint ON_EarthAnchorPoint::EarthLocation(
  ON_3dPoint unset_location
) const
{
  return (EarthLocationIsSet() ? EarthLocation() : unset_location);
}


double ON_EarthAnchorPoint::Latitude() const
{
  return m_earth_latitude;
}

double ON_EarthAnchorPoint::Latitude(
  double unset_latitude
) const
{
  return (m_earth_latitude > -360.0 && m_earth_latitude < 360.0) ? m_earth_latitude : unset_latitude;
}

void ON_EarthAnchorPoint::SetLatitudeAndLongitude(
  double latitude_degrees,
  double longitude_degrees
)
{
  const double tol = ON_ZERO_TOLERANCE;
  const bool bSetLatitude = ON_IsValid(latitude_degrees) && fabs(latitude_degrees) <= 10000.0;
  const bool bSetLongitude = ON_IsValid(longitude_degrees) && fabs(longitude_degrees) <= 10000.0;
  double x, y;
  if (bSetLatitude)
  {
    y = latitude_degrees;

    x = 0.0;
    while (y > 180.0)
    {
      x -= 360.0;
      y = latitude_degrees + x;
    }

    x = 0.0;
    while (y < -180.0)
    {
      x += 360.0;
      y = latitude_degrees + x;
    }
    if (y != latitude_degrees)
    {
      if (fabs(y - 180.0) <= tol)
        y = 180.0;
      if (fabs(y + 180.0) <= tol)
        y = -180.0;
    }

    if ( bSetLongitude && fabs(y) > 90.0 )
    {
      if (y > 90.0)
        y = 180.0 - y;
      else
        y = -180.0 - y;
      longitude_degrees += 180.0;
    }

    if (y != latitude_degrees)
    {
      if (fabs(y) <= tol)
        y = 0.0;
      if (fabs(y - 90.0) <= tol)
        y = 90.0;
      else if (fabs(y + 90.0) <= tol)
        y = -90.0;
    }

    m_earth_latitude = y;
  }
  else
  {
    m_earth_latitude = ON_EarthAnchorPoint::Unset.m_earth_latitude;
  }

  if (bSetLongitude)
  {
    y = longitude_degrees;

    x = 0.0;
    while (y >= 360.0)
    {
      x -= 360.0;
      y = longitude_degrees + x;
    }

    x = 0.0;
    while (y <= -360.0)
    {
      x += 360.0;
      y = longitude_degrees + x;
    }

    if (y != longitude_degrees)
    {
      if (fabs(y) <= tol)
        y = 0.0;
      if (fabs(y-360.0) <= tol)
        y = 0.0;
      else if (fabs(y+360.0) <= tol)
        y = 0.0;
    }

    m_earth_longitude = y;
  }
  else
  {
    m_earth_longitude = ON_EarthAnchorPoint::Unset.m_earth_longitude;
  }
}

void ON_EarthAnchorPoint::SetLatitude(
  double latitude_degrees
)
{
  const double x = m_earth_longitude;
  SetLatitudeAndLongitude(latitude_degrees, ON_UNSET_VALUE);
  m_earth_longitude = x;
}


double ON_EarthAnchorPoint::Longitude() const
{
  return m_earth_longitude;
}

double ON_EarthAnchorPoint::Longitude(
  double unset_longitude
) const
{
  return (m_earth_longitude > -360.0 && m_earth_longitude < 360.0) ? m_earth_longitude : unset_longitude;
}

  
void ON_EarthAnchorPoint::SetLongitude(
  double longitude_degrees
)
{
  const double x = m_earth_latitude;
  SetLatitudeAndLongitude(ON_UNSET_VALUE, longitude_degrees);
  m_earth_latitude = x;
}


ON::EarthCoordinateSystem ON_EarthAnchorPoint::EarthCoordinateSystem() const
{
  return m_earth_coordinate_system;
}

void ON_EarthAnchorPoint::SetEarthCoordinateSystem(
  ON::EarthCoordinateSystem earth_coordinate_system
)
{
  m_earth_coordinate_system = earth_coordinate_system;
}

double ON_EarthAnchorPoint::ElevationInMeters() const
{
  return m_earth_elevation_meters;
}

double ON_EarthAnchorPoint::Elevation(
  const class ON_UnitSystem& elevation_unit_system
  ) const
{
  if (ON_IsValid(m_earth_elevation_meters && 0.0 != m_earth_elevation_meters && ON::LengthUnitSystem::Meters != elevation_unit_system.UnitSystem()))
  {
    return m_earth_elevation_meters*ON::UnitScale(elevation_unit_system, ON_UnitSystem::Meters);
  }
  return m_earth_elevation_meters;
}

double ON_EarthAnchorPoint::Elevation(
  ON::LengthUnitSystem elevation_unit_system
  ) const
{
  ON_UnitSystem us(elevation_unit_system);
  return Elevation(us);
}

double ON_EarthAnchorPoint::Elevation(
  const class ON_UnitSystem& elevation_unit_system,
  double unset_elevation
) const
{
  return ON_IsValid(m_earth_elevation_meters) ? Elevation(elevation_unit_system) : unset_elevation;
}

double ON_EarthAnchorPoint::Elevation(
  ON::LengthUnitSystem elevation_unit_system,
  double unset_elevation
) const
{
  return ON_IsValid(m_earth_elevation_meters) ? Elevation(elevation_unit_system) : unset_elevation;
}

void ON_EarthAnchorPoint::SetElevation(
  const class ON_UnitSystem& elevation_unit_system,
  double elevation
)
{
  if (ON_IsValid(elevation))
  {
    if (ON::LengthUnitSystem::Meters == elevation_unit_system.UnitSystem())
      m_earth_elevation_meters = elevation;
    else
      m_earth_elevation_meters = elevation*ON::UnitScale(elevation_unit_system, ON_UnitSystem::Meters);
  }
  else
  {
    m_earth_elevation_meters = ON_EarthAnchorPoint::Unset.m_earth_elevation_meters;
  }
}

void ON_EarthAnchorPoint::SetElevation(
  ON::LengthUnitSystem elevation_unit_system,
  double elevation
)
{
  ON_UnitSystem us(elevation_unit_system);
  SetElevation(us, elevation);
}

const ON_3dPoint& ON_EarthAnchorPoint::ModelPoint() const
{
  return m_model_point;
}

const ON_3dVector& ON_EarthAnchorPoint::ModelNorth() const
{
  return m_model_north;
}

const ON_3dVector& ON_EarthAnchorPoint::ModelEast() const
{
  return m_model_east;
}


void ON_EarthAnchorPoint::SetModelPoint(
  ON_3dPoint model_point
)
{
  m_model_point = model_point;
}

void ON_EarthAnchorPoint::SetModelNorth(
  ON_3dVector model_north
)
{
  m_model_north = model_north;
}

void ON_EarthAnchorPoint::SetModelEast(
  ON_3dVector model_east
)
{
  m_model_east = model_east;
}

void ON_EarthAnchorPoint::SetModelLocation(
  ON_3dPoint model_point,
  ON_3dVector model_north,
  ON_3dVector model_east
  )
{
  SetModelPoint(model_point);
  SetModelNorth(model_north);
  SetModelEast(model_east);
}

const ON_Xform ON_EarthAnchorPoint::Internal_KMLOrientationXform() const
{
  if (false == this->ModelLocationIsSet())
  {
    ON_ERROR("Corrupt model location.");
    return ON_Xform::Nan;
  }

  ON_Plane model_directions;
  if (false == model_directions.CreateFromFrame(ON_3dPoint::Origin, ModelEast(), ModelNorth()))
    return ON_Xform::Nan;
  if (false == model_directions.IsValid())
    return ON_Xform::Nan;

  // The KML orientation moves the model so that
  // east = x-axis
  // north = Y-axis
  // up = Z-axis
  // https://developers.google.com/kml/documentation/kmlreference#orientation
  // "Describes rotation of a 3D model's coordinate system to position the object in Google Earth."

  ON_Xform KMLorientation;
  KMLorientation.Rotation(model_directions, ON_Plane::World_xy);

  const ON_3dPoint M[4] = {
    ON_3dPoint::Origin,
    ON_3dPoint::Origin + ModelEast().UnitVector(),
    ON_3dPoint::Origin + ModelNorth().UnitVector(),
    ON_3dPoint::Origin + ON_CrossProduct(ModelEast().UnitVector(), ModelNorth().UnitVector())
  };
  const ON_3dPoint E[sizeof(M)/sizeof(M[0])] = {
    ON_3dPoint::Origin,
    ON_3dPoint::Origin + ON_3dVector::XAxis,
    ON_3dPoint::Origin + ON_3dVector::YAxis,
    ON_3dPoint::Origin + ON_3dVector::ZAxis
  };
  ON_3dPoint rM[sizeof(M) / sizeof(M[0])] = {};
  double err[sizeof(M) / sizeof(M[0])] = {};
  double maxerr = 0.0;
  for (size_t i = 0; i < sizeof(M) / sizeof(M[0]); ++i)
  {
    rM[i] = KMLorientation * M[i];
    double d = E[i].DistanceTo(rM[i]);
    if (d != d || d > err[i])
      err[i] = d;
    if (err[i] != err[i] || err[i] > maxerr)
      maxerr = err[i];
  }

  if (false == maxerr <= ON_ZERO_TOLERANCE)
  {
    ON_ERROR("Sloppy rotation matrix.");
  }

  return KMLorientation;
}

bool ON_EarthAnchorPoint::GetKMLOrientationAnglesRadians(double& heading_radians, double& tilt_radians, double& roll_radians) const
{
  heading_radians = ON_DBL_QNAN;
  tilt_radians = ON_DBL_QNAN;
  roll_radians = ON_DBL_QNAN;
  const ON_Xform rot = Internal_KMLOrientationXform();
  return rot.GetKMLOrientationAnglesRadians(heading_radians, tilt_radians, roll_radians);
}

bool ON_EarthAnchorPoint::GetKMLOrientationAnglesDegrees(double& heading_degrees, double& tilt_degrees, double& roll_degrees) const
{
  heading_degrees = ON_DBL_QNAN;
  tilt_degrees = ON_DBL_QNAN;
  roll_degrees = ON_DBL_QNAN;
  const ON_Xform rot = Internal_KMLOrientationXform();
  return rot.GetKMLOrientationAnglesDegrees(heading_degrees, tilt_degrees, roll_degrees);
}

const double ON_EarthAnchorPoint::KMLOrientationHeadingAngleRadians() const
{
  double heading_radians = ON_DBL_QNAN;
  double tilt_radians = ON_DBL_QNAN;
  double roll_radians = ON_DBL_QNAN;
  const bool rc = GetKMLOrientationAnglesRadians(heading_radians, tilt_radians, roll_radians);
  return rc ? heading_radians : ON_DBL_QNAN;
}

const double ON_EarthAnchorPoint::KMLOrientationTiltAngleRadians() const
{
  double heading_radians = ON_DBL_QNAN;
  double tilt_radians = ON_DBL_QNAN;
  double roll_radians = ON_DBL_QNAN;
  const bool rc = GetKMLOrientationAnglesRadians(heading_radians, tilt_radians, roll_radians);
  return rc ? tilt_radians : ON_DBL_QNAN;
}

const double ON_EarthAnchorPoint::KMLOrientationRollAngleRadians() const
{
  double heading_radians = ON_DBL_QNAN;
  double tilt_radians = ON_DBL_QNAN;
  double roll_radians = ON_DBL_QNAN;
  const bool rc = GetKMLOrientationAnglesRadians(heading_radians, tilt_radians, roll_radians);
  return rc ? roll_radians : ON_DBL_QNAN;
}

const double ON_EarthAnchorPoint::KMLOrientationHeadingAngleDegrees() const
{
  double heading_degrees = ON_DBL_QNAN;
  double tilt_degrees = ON_DBL_QNAN;
  double roll_degrees = ON_DBL_QNAN;
  const bool rc = GetKMLOrientationAnglesDegrees(heading_degrees, tilt_degrees, roll_degrees);
  return rc ? heading_degrees : ON_DBL_QNAN;
}

const double ON_EarthAnchorPoint::KMLOrientationTiltAngleDegrees() const
{
  double heading_degrees = ON_DBL_QNAN;
  double tilt_degrees = ON_DBL_QNAN;
  double roll_degrees = ON_DBL_QNAN;
  const bool rc = GetKMLOrientationAnglesDegrees(heading_degrees, tilt_degrees, roll_degrees);
  return rc ? tilt_degrees : ON_DBL_QNAN;
}

const double ON_EarthAnchorPoint::KMLOrientationRollAngleDegrees() const
{
  double heading_degrees = ON_DBL_QNAN;
  double tilt_degrees = ON_DBL_QNAN;
  double roll_degrees = ON_DBL_QNAN;
  const bool rc = GetKMLOrientationAnglesDegrees(heading_degrees, tilt_degrees, roll_degrees);
  return rc ? roll_degrees : ON_DBL_QNAN;
}

//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmSettings
//

void ON_3dmSettings::SetCurrentLayerId(
  ON_UUID layer_id
  )
{
  m_current_layer_id = layer_id;
  m_V5_current_layer_index = ON_UNSET_INT_INDEX;
}

void ON_3dmSettings::SetV5CurrentLayerIndex(
  int V5_current_layer_index
)
{
  m_V5_current_layer_index = V5_current_layer_index;
}

int ON_3dmSettings::CurrentLayerIndex() const
{
  return m_V5_current_layer_index;
}

ON_UUID ON_3dmSettings::CurrentLayerId() const
{
  return m_current_layer_id;
}

void ON_3dmSettings::SetCurrentMaterialId(
  ON_UUID render_material_id
  )
{
  m_current_render_material_id = render_material_id;
  m_V5_current_render_material_index = ON_UNSET_INT_INDEX;
}

int ON_3dmSettings::CurrentMaterialIndex() const
{
  return m_V5_current_render_material_index;
}

ON_UUID ON_3dmSettings::CurrentMaterialId() const
{
  return m_current_render_material_id;
}


void ON_3dmSettings::SetCurrentDimensionStyleId(
  ON_UUID dimension_style_id
  )
{
  m_current_dimension_style_id = dimension_style_id;
  m_V5_current_dimension_style_index = ON_UNSET_INT_INDEX;
}

int ON_3dmSettings::CurrentDimensionStyleIndex() const
{
  return m_V5_current_dimension_style_index;
}

ON_UUID ON_3dmSettings::CurrentDimensionStyleId() const
{
  return m_current_dimension_style_id;
}

void ON_3dmSettings::SetCurrentTextStyleId(
  ON_UUID text_style_id
  )
{
  m_current_text_style_id = text_style_id;
  m_V5_current_text_style_index = ON_UNSET_INT_INDEX;
}

int ON_3dmSettings::CurrentTextStyleIndex() const
{
  return m_V5_current_text_style_index;
}

ON_UUID ON_3dmSettings::CurrentTextStyleId() const
{
  return m_current_text_style_id;
}

void ON_3dmSettings::SetCurrentLinePatternId(
  ON_UUID line_pattern_id
  )
{
  m_current_line_pattern_id = line_pattern_id;
  m_V5_current_line_pattern_index = ON_UNSET_INT_INDEX;
}

int ON_3dmSettings::CurrentLinePatternIndex() const
{
  return m_V5_current_line_pattern_index;
}

ON_UUID ON_3dmSettings::CurrentLinePatternId() const
{
  return m_current_line_pattern_id;
}

void ON_3dmSettings::SetCurrentHatchPatternId(
  ON_UUID hatch_pattern_id
  )
{
  m_current_hatch_pattern_id = hatch_pattern_id;
}

ON_UUID ON_3dmSettings::CurrentHatchPatternId() const
{
  return m_current_hatch_pattern_id;
}


//void ON_3dmSettings::Default()
//{
//  // default properties
//  m_model_URL.Destroy();
//  m_model_basepoint.Set(0.0,0.0,0.0);
//  m_earth_anchor_point.Default();
//  m_ModelUnitsAndTolerances = ON_3dmUnitsAndTolerances::Millimeters;
//  m_PageUnitsAndTolerances = ON_3dmUnitsAndTolerances::Millimeters;
//
//  m_RenderMeshSettings = ON_MeshParameters::DefaultMesh;
//  m_CustomRenderMeshSettings = ON_MeshParameters::DefaultMesh;
//  m_AnalysisMeshSettings = ON_MeshParameters::DefaultAnalysisMesh;
//
//  m_IO_settings.Default();
//  
//  m_AnnotationSettings.Default();
//  m_named_cplanes.Empty();
//  m_named_views.Empty();
//  m_views.Empty();
//  m_active_view_id = ON_nil_uuid;
//
//  m_V5_current_layer_index = ON_UNSET_INT_INDEX;
//  m_current_layer_id = ON_nil_uuid;
//
//  m_V5_current_render_material_index = ON_UNSET_INT_INDEX;
//  m_current_render_material_id = ON_nil_uuid;
//
//
//  m_V5_current_text_style_index = ON_UNSET_INT_INDEX;
//  m_current_text_style_id = ON_nil_uuid;
//
//  m_V5_current_dimension_style_index = 0;
//  m_current_dimension_style_id = ON_nil_uuid;
//
//  m_current_color.SetRGB(0,0,0);
//  m_current_color_source = ON::color_from_layer;
//
//  m_V5_current_line_pattern_index = ON_UNSET_INT_INDEX;
//  m_current_line_pattern_id = ON_nil_uuid;
//
//  m_current_plot_color = ON_UNSET_COLOR;
//  m_current_plot_color_source = ON::plot_color_from_layer;
//
//  m_current_wire_density = 1;
//
//  m_RenderSettings = ON_3dmRenderSettings::Default;
//
//  m_GridDefaults.Default();
//
//  m_linetype_display_scale = 1.0;
//
//  m_plugin_list.Destroy();
//}


ON_MeshParameters::MESH_STYLE ON_3dmSettings::RenderMeshStyle(
  ON_MeshParameters::MESH_STYLE no_match_found_result
  ) const
{
  return m_RenderMeshSettings.GeometrySettingsRenderMeshStyle(
     &m_CustomRenderMeshSettings,
     no_match_found_result
    );
}


bool ON_3dmIOSettings::Read(ON_BinaryArchive& file)
{
  *this = ON_3dmIOSettings::Default;

  int major_version = 0;
  int minor_version = 0;
  bool rc = file.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
  if (!rc)
    return false;

  for(;;)
  {
    rc = ( 1 == major_version );
    if (!rc) break;

    rc = file.ReadBool(&m_bSaveTextureBitmapsInFile);
    if(!rc) break;

    rc = file.ReadInt(&m_idef_link_update);
    if(!rc) break;

    if ( 0 == m_idef_link_update && file.Archive3dmVersion() >= 5 )
    {
      // 7 February 2011 - old 0 value is no longer an option.
      m_idef_link_update = 1;
    }

    break;
  }

  if ( !file.EndRead3dmChunk() )
    rc = false;

  return rc;
}

bool ON_3dmIOSettings::Write(ON_BinaryArchive& file) const
{
  bool rc = file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0);
  if (!rc)
    return false;
  for(;;)
  {
    rc = file.WriteBool(m_bSaveTextureBitmapsInFile);
    if(!rc) break;

    int i = m_idef_link_update;
    if ( 0 == i && file.Archive3dmVersion() >= 5 )
    {
      // 7 February 2011 - old 0 value is no longer an option.
      i = 1;
    }
    rc = file.WriteInt(i);
    if(!rc) break;

    break;
  }
  if ( !file.EndWrite3dmChunk() )
    rc = false;

  return rc;
}


static bool ON_3dmSettings_Read_v1_TCODE_NAME(ON_BinaryArchive& file, ON_wString& str )
{
  // reads legacy 1.0 named view TCODE_NAME chunk
  str.Empty();
  int len = 0;
  bool rc = file.ReadInt( &len );
  if (rc && len > 0) {
    char* name = (char*)oncalloc( 1, len + 1);
    rc = file.ReadString( len, name );
    if (rc)
      str = name; // ASCII -> UNICODE
    if (name)
      onfree(name);
  }
  return rc;
}

static bool ON_3dmSettings_Read_v1_TCODE_CPLANE(ON_BinaryArchive& file, ON_3dmConstructionPlane& cplane)
{
  // reads legacy 1.0 named view TCODE_CPLANE chunk

  // do NOT call cplane.Default() here
  bool rc = true;
	ON_3dPoint origin;
	ON_3dVector xaxis, yaxis;
	double gridsize;
	int gridsections, gridthicksections;
  if (rc) rc = file.ReadPoint( origin );
  if (rc) rc = file.ReadVector( xaxis );
  if (rc) rc = file.ReadVector( yaxis );
  if (rc) 
  {
    rc = file.ReadDouble(&gridsize);
    if (rc) 
    {
      rc = file.ReadInt(&gridsections);
      if (rc) 
      {
        rc = file.ReadInt(&gridthicksections);
        if (rc) 
        {
          cplane.m_plane.CreateFromFrame(origin,xaxis,yaxis);
          cplane.m_grid_line_count = gridsections;
          cplane.m_grid_thick_frequency = gridthicksections;
          cplane.m_grid_spacing = gridsize;
          cplane.m_snap_spacing = gridsize;
        }
        }
    }
  }
  return rc;
}

static bool ON_3dmSettings_Read_v1_TCODE_VIEW(ON_BinaryArchive& file, ON_3dmView& view)
{
  // reads legacy 1.0 named view TCODE_VIEW chunk
  // do NOT call view.Default() here
  bool rc = true;

	int projection, valid;
	double angle1, angle2, angle3, viewsize, cameradist;
  ON_3dPoint target_point;
  while(rc)
  {
    rc = file.ReadInt(&projection);
    if (!rc) break;
    rc = file.ReadInt(&valid);
    if (!rc) break;
    rc = file.ReadPoint( target_point );
    if (!rc) break;
    rc = file.ReadDouble( &angle1 );
    if (!rc) break;
    rc = file.ReadDouble( &angle2 );
    if (!rc) break;
    rc = file.ReadDouble( &angle3 );
    if (!rc) break;
    rc = file.ReadDouble( &viewsize );
    if (!rc) break;
    rc = file.ReadDouble( &cameradist );
    if (!rc) break;

    if( cameradist <= 0.0 || cameradist >= ( DBL_MAX / 2.0 ))
      cameradist = 100.0;
    if( viewsize <= 0.0 || viewsize >= ( DBL_MAX / 2.0 ))
      viewsize = 0.125;
    ON_ViewportFromRhinoView(
          projection == 2 ? ON::perspective_view : ON::parallel_view,
          target_point,
          angle1,
          angle2,
          angle3,
          viewsize,
          cameradist,
          100, // screen_width, 
          100, // screen_height,
          view.m_vp
          );
    break;
  }

  return rc;
}

static bool ON_3dmSettings_Read_v1_TCODE_NAMED_VIEW(ON_BinaryArchive& file, ON_3dmView& view)
{
  // reads legacy 1.0 named view TCODE_NAMED_VIEW chunk
  view.Default();
  bool rc = true;
  unsigned int tcode;
  ON__INT64 big_value;

  while(rc) 
  {
    rc = file.BeginRead3dmBigChunk( &tcode, &big_value );
    if (!rc )
      break;
    switch(tcode) {

    case TCODE_NAME:
      rc = ON_3dmSettings_Read_v1_TCODE_NAME(file,view.m_name);
      break;

    case TCODE_CPLANE:
      rc = ON_3dmSettings_Read_v1_TCODE_CPLANE(file,view.m_cplane);
      break;

    case TCODE_VIEW:
      rc = ON_3dmSettings_Read_v1_TCODE_VIEW( file, view );
      break;

    case TCODE_SHOWGRID:
      view.m_bShowConstructionGrid = big_value?true:false;
      break;
						
    case TCODE_SHOWGRIDAXES:
      view.m_bShowConstructionAxes = big_value?true:false;
      break;
						
    case TCODE_SHOWWORLDAXES:
      view.m_bShowWorldAxes = big_value?true:false;
      break; 			
      
    }
    if ( !file.EndRead3dmChunk() )
      rc = false;
    if ( tcode == TCODE_ENDOFTABLE )
      break;
  }
  return rc;
}

static bool ON_3dmSettings_Read_v1_TCODE_NAMED_CPLANE(ON_BinaryArchive& file, ON_3dmConstructionPlane& cplane)
{
  // reads legacy 1.0 named construction plane TCODE_NAMED_CPLANE chunk
  cplane.Default();

  bool rc = true;
  unsigned int tcode;
  ON__INT64 big_value;

  while(rc) 
  {
    rc = file.BeginRead3dmBigChunk( &tcode, &big_value );
    if (!rc )
      break;
    switch(tcode) {

    case TCODE_NAME:
      rc = ON_3dmSettings_Read_v1_TCODE_NAME(file, cplane.m_name );
      break;

    case TCODE_CPLANE:
      rc = ON_3dmSettings_Read_v1_TCODE_CPLANE(file, cplane );
      break;
    }
    if ( !file.EndRead3dmChunk() )
      rc = false;
    if ( tcode == TCODE_ENDOFTABLE )
      break;
  }
  return rc;
}

static bool ON_3dmSettings_Read_v1_TCODE_UNIT_AND_TOLERANCES(
  ON_BinaryArchive& file, 
  ON_3dmUnitsAndTolerances& UnitsAndTolerances 
  )
{
  bool rc = true;
  int v = 0;
  int us = 0;
  UnitsAndTolerances = ON_3dmUnitsAndTolerances::Millimeters;
  if (rc) 
    rc = file.ReadInt( &v ); // should get v = 1
  if (rc) 
    rc = file.ReadInt( &us );
  switch (us) 
  {
  case 0: // NO_UNIT_SYSTEM:
    UnitsAndTolerances.m_unit_system.SetUnitSystem(ON::LengthUnitSystem::None);
    break;
  case 1: // MICRONS:
    UnitsAndTolerances.m_unit_system.SetUnitSystem(ON::LengthUnitSystem::Microns);
    break;
  case 2: // MILLIMETERS:
    UnitsAndTolerances.m_unit_system.SetUnitSystem(ON::LengthUnitSystem::Millimeters);
    break;
  case 3: // CENTIMETERS:
    UnitsAndTolerances.m_unit_system.SetUnitSystem(ON::LengthUnitSystem::Centimeters);
    break;
  case 4: // METERS:
    UnitsAndTolerances.m_unit_system.SetUnitSystem(ON::LengthUnitSystem::Meters);
    break;
  case 5: // KILOMETERS:
    UnitsAndTolerances.m_unit_system.SetUnitSystem(ON::LengthUnitSystem::Kilometers);
    break;
  case 6: // MICROINCHES:
    UnitsAndTolerances.m_unit_system.SetUnitSystem(ON::LengthUnitSystem::Microinches);
    break;
  case 7: // MILS:
    UnitsAndTolerances.m_unit_system.SetUnitSystem(ON::LengthUnitSystem::Mils);
    break;
  case 8: // INCHES:
    UnitsAndTolerances.m_unit_system.SetUnitSystem(ON::LengthUnitSystem::Inches);
    break;
  case 9: // FEET:
    UnitsAndTolerances.m_unit_system.SetUnitSystem(ON::LengthUnitSystem::Feet);
    break;
  case 10: // MILES:
    UnitsAndTolerances.m_unit_system.SetUnitSystem(ON::LengthUnitSystem::Miles);
    break;
  default: // NO_UNIT_SYSTEM:
    UnitsAndTolerances.m_unit_system.SetUnitSystem(ON::LengthUnitSystem::None);
    break;
  }
  if (rc) rc = file.ReadDouble( &UnitsAndTolerances.m_absolute_tolerance );
  if (rc) rc = file.ReadDouble( &UnitsAndTolerances.m_relative_tolerance );
  if (rc) rc = file.ReadDouble( &UnitsAndTolerances.m_angle_tolerance );
  return rc;
}

static bool ON_3dmSettings_Read_v1_TCODE_VIEWPORT(ON_BinaryArchive& file, ON_3dmView& view)
{
  // reads legacy 1.0 named construction plane TCODE_VIEWPORT chunk
  view.Default();
  bool rc = true;
  ON__UINT32 tcode;
  ON__INT64 big_value;

  double clipdist = 0.0;
  double snapsize = 0.0;

  int chunk_count = 0;// debugging counter
  for ( chunk_count = 0; rc; chunk_count++ )
  {
    rc = file.BeginRead3dmBigChunk( &tcode, &big_value );
    if (!rc )
      break;
    switch(tcode) {

    case TCODE_NEAR_CLIP_PLANE:
      rc = file.ReadDouble(&clipdist);
      break;

    case TCODE_SNAPSIZE:
      rc = file.ReadDouble(&snapsize);
      break;
      
    case TCODE_NAME:
      rc = ON_3dmSettings_Read_v1_TCODE_NAME(file,view.m_name);
      break;

    case TCODE_CPLANE:
      rc = ON_3dmSettings_Read_v1_TCODE_CPLANE(file,view.m_cplane);
      break;

    case TCODE_VIEW:
      rc = ON_3dmSettings_Read_v1_TCODE_VIEW( file, view );
      break;

    case TCODE_SHOWGRID:
      view.m_bShowConstructionGrid = big_value?true:false;
      break;
						
    case TCODE_SHOWGRIDAXES:
      view.m_bShowConstructionAxes = big_value?true:false;
      break;
						
    case TCODE_SHOWWORLDAXES:
      view.m_bShowWorldAxes = big_value?true:false;
      break; 			
      
    case TCODE_VIEWPORT_POSITION:
      rc = file.ReadDouble(&view.m_position.m_wnd_left);
      rc = file.ReadDouble(&view.m_position.m_wnd_top);
      rc = file.ReadDouble(&view.m_position.m_wnd_right);
      rc = file.ReadDouble(&view.m_position.m_wnd_bottom);
      break;
						
    case TCODE_VIEWPORT_TRACEINFO:
      {
        ON_3dPoint origin;
        ON_3dVector xaxis, yaxis;
        if (rc) rc = file.ReadPoint( origin );
        if (rc) rc = file.ReadVector( xaxis );
        if (rc) rc = file.ReadVector( yaxis );
        view.m_trace_image.m_plane.CreateFromFrame(origin,xaxis,yaxis);
        if (rc) rc = file.ReadDouble(&view.m_trace_image.m_width);
        if (rc) rc = file.ReadDouble(&view.m_trace_image.m_height);
        if (rc)
        {
          ON_wString bitmap_filename;
          rc = ON_3dmSettings_Read_v1_TCODE_NAME(file, bitmap_filename);
          if (rc) view.m_trace_image.m_image_file_reference.SetFullPath(bitmap_filename,false);
        }
      }
      break;
      
    case TCODE_VIEWPORT_WALLPAPER:
      {
        ON_wString bitmap_filename;
        rc = ON_3dmSettings_Read_v1_TCODE_NAME(file, bitmap_filename);
        if (rc)
          view.m_wallpaper_image.m_image_file_reference.SetFullPath(bitmap_filename,false);
      }
      break;
						
    case TCODE_HIDE_TRACE:
      // TCODE_HIDE_TRACE was used in early 1.0 betas.  
      // It should have add the short bit set and it is no longer used.
      // This case is here so that these old files will read correctly.
      tcode |= TCODE_SHORT; // so goo skip will work
      break;
      
    case TCODE_MAXIMIZED_VIEWPORT:
      if ( big_value )
        view.m_position.m_bMaximized = true;
      break; 

    case TCODE_VIEWPORT_V1_DISPLAYMODE: // short TCODE with display mode value
      if ( ON_nil_uuid == view.m_display_mode_id )
      {
        switch ( big_value ) 
        {
        case 0: // wireframe working mode
          view.m_display_mode_id = ON_StandardDisplayModeId::Wireframe;
          break;
        case 1: // shaded working mode
          view.m_display_mode_id = ON_StandardDisplayModeId::Shaded;
          break;
        }
      }
      break;
						
    }
    if ( !file.EndRead3dmChunk() )
      rc = false;
    if ( tcode == TCODE_ENDOFTABLE )
      break;
  }
  return rc;
}

bool ON_3dmSettings::Read_v1( ON_BinaryArchive& file )
{
  //bool bGotSomething = false;
  bool rc = false;
  // read settings from old version 1 file
  ON__UINT64 pos0 = file.CurrentPosition();

  // need to start at the beginning of the file
  ON__UINT32 tcode;
  ON__INT64 big_value;
  rc = file.SeekFromStart(32)?true:false; // skip 32 byte header
  
  int chunk_count = 0; // debugging counter
  for ( chunk_count = 0; rc; chunk_count++ )
  {
    rc = file.BeginRead3dmBigChunk( &tcode, &big_value );
    if (!rc)
    {
      rc = true;
      break; // assume we are at the end of the file
    }

    switch(tcode) {
    case TCODE_VIEWPORT:
      //bGotSomething = true;
      {
        ON_3dmView view;
        rc = ON_3dmSettings_Read_v1_TCODE_VIEWPORT(file, view);
        if (rc)
          m_views.Append(view);
      }
      break;

    case TCODE_NAMED_CPLANE:
      //bGotSomething = true;
      {
        ON_3dmConstructionPlane cplane;
        rc = ON_3dmSettings_Read_v1_TCODE_NAMED_CPLANE(file,cplane);
        if (rc)
          m_named_cplanes.Append(cplane);
      }
      break;

    case TCODE_NAMED_VIEW:
      //bGotSomething = true;
      {
        ON_3dmView view;
        rc = ON_3dmSettings_Read_v1_TCODE_NAMED_VIEW(file, view);
        if (rc)
          m_named_views.Append(view);
      }
      break;
    
    case TCODE_UNIT_AND_TOLERANCES:
      //bGotSomething = true;
      rc = ON_3dmSettings_Read_v1_TCODE_UNIT_AND_TOLERANCES(file,m_ModelUnitsAndTolerances);
      break;
    }

    rc = file.EndRead3dmChunk();
  }

  if (false == file.SeekFromStart(pos0))
    rc = false;

  return rc;
}

bool ON_3dmSettings::Read_v2(ON_BinaryArchive& file )
{
  bool rc = true;
  ON__UINT32 tcode;
  ON__INT64 big_value;

  bool bHave3dmRenderSettings = false;

  while(rc) 
  {
    tcode = 0;
    big_value = 0;
    rc = file.BeginRead3dmBigChunk( &tcode, &big_value );
    if ( !rc )
      break;

    switch(tcode) 
    {
    case TCODE_SETTINGS_PLUGINLIST: 
      {
        int major_version = 0, minor_version = 0, count = 0, i;
        rc = file.Read3dmChunkVersion(&major_version,&minor_version);
        if (rc && 1 == major_version && minor_version >= 0 )
        {
          rc = file.ReadInt( &count );
          if ( count > 0 )
          {
            for ( i = 0; rc && i < count; i++ )
            {
              rc = m_plugin_list.AppendNew().Read(file);
            }
          }
        }
      }
      break;
      
    case TCODE_SETTINGS_UNITSANDTOLS: // units and tolerances
      rc = m_ModelUnitsAndTolerances.Read(file);
      // Copy model settings to page settings so reading old files
      // will work right.  If the file is new enough to have page
      // units and tolerances in it, they get read later.
      m_PageUnitsAndTolerances = m_ModelUnitsAndTolerances;
      break;
      
    case TCODE_SETTINGS_RENDERMESH:
      rc = m_RenderMeshSettings.Read(file);
      break;
      
    case TCODE_SETTINGS_ANALYSISMESH:
      rc = m_AnalysisMeshSettings.Read(file);
      break;
      
    case TCODE_SETTINGS_ANNOTATION:
      rc = m_AnnotationSettings.Read(file);
      break;
      
    case TCODE_SETTINGS_NAMED_CPLANE_LIST: // named cplanes
      {
        m_named_cplanes.Empty();
        ON__UINT32 subtcode = 0;
        ON__INT64 subvalue = 0;
        int count, i;
        rc = file.ReadInt(&count);
        for ( i = 0; i < count && rc ; i++ ) {
          rc = file.BeginRead3dmBigChunk( &subtcode, &subvalue );
          if (rc ) {
            if ( subtcode != TCODE_VIEW_CPLANE )
              rc = false;
            else {
              ON_3dmConstructionPlane& cplane = m_named_cplanes.AppendNew();
              rc = cplane.Read(file);
            }
            if ( !file.EndRead3dmChunk() ) {
              rc = false;
            }
          }
        }
      }
      break;
      
    case TCODE_SETTINGS_NAMED_VIEW_LIST: // named views
      {
        m_named_views.Empty();
        ON__UINT32 subtcode = 0;
        ON__INT64 subvalue = 0;
        int count, i;
        rc = file.ReadInt(&count);
        for ( i = 0; i < count && rc ; i++ ) 
        {
          rc = file.BeginRead3dmBigChunk( &subtcode, &subvalue );
          if (rc ) 
          {
            if ( subtcode != TCODE_VIEW_RECORD )
              rc = false;
            else 
            {
              ON_3dmView& namedView = m_named_views.AppendNew();
              rc = namedView.Read(file);

			  //Named views were attached to the named view table without an id.
			  //the documentation says it will always have one, so this code ensures that the ids are non-nil.
			  //http://mcneel.myjetbrains.com/youtrack/issue/RH-19520
			  if (ON_nil_uuid == namedView.m_named_view_id)
			  {
				  ON_CreateUuid(namedView.m_named_view_id);
			  }
            }
            if ( !file.EndRead3dmChunk() )
            {
              rc = false;
            }
          }
        }
      }
      break;
      
    case TCODE_SETTINGS_VIEW_LIST: // active view is first in list
      {
        m_views.Empty();
        ON__UINT32 subtcode = 0;
        ON__INT64 subvalue = 0;
        int count, i;
        rc = file.ReadInt(&count);
        m_views.Reserve(count);
        for ( i = 0; i < count && rc ; i++ ) 
        {
          rc = file.BeginRead3dmBigChunk( &subtcode, &subvalue );
          if (rc ) 
          {
            if ( subtcode != TCODE_VIEW_RECORD )
              rc = false;
            else 
            {
              ON_3dmView& view = m_views.AppendNew();
              rc = view.Read(file);
            }
            if ( !file.EndRead3dmChunk() )
            {
              rc = false;
            }
          }
        }
      }
      break;
      
    case TCODE_SETTINGS__NEVER__USE__THIS:
      {
        if ( 28 == big_value )
        {
          // 23 March 2005 Dale Lear - this was the ON_LineStyle
          //                           and a linesytlesource int
          //                           that never got used.
          unsigned char b[24];
          if (rc) rc = file.ReadByte(24,b);
          // The other 4 bytes are a 32 bit chunk crc
          // that gets read by EndRead3dmChunk()
        }
      }
      break;

    case TCODE_SETTINGS_CURRENT_LAYER_INDEX:
      if ( big_value < -1 || big_value > 0x7FFFFFFF )
      {
        ON_ERROR("ON_3dmSettings::Read_v2() - TCODE_SETTINGS_CURRENT_LAYER_INDEX - invalid layer index value");
      }
      else
      {
        m_V5_current_layer_index = (int)big_value;
        m_current_layer_id = ON_nil_uuid;
      }
      break;
      
    case TCODE_SETTINGS_CURRENT_FONT_INDEX:
      if ( big_value < -1 || big_value > 0x7FFFFFFF )
      {
        ON_ERROR("ON_3dmSettings::Read_v2() - TCODE_SETTINGS_CURRENT_FONT_INDEX - invalid font index value");
      }
      else
      {
        // in archives with opennurbs version >= 200106100
        m_V5_current_text_style_index = (int)big_value;
        m_current_text_style_id = ON_nil_uuid;
      }
      break;
      
    case TCODE_SETTINGS_CURRENT_DIMSTYLE_INDEX:
      if ( big_value < -1 || big_value > 0x7FFFFFFF )
      {
        ON_ERROR("ON_3dmSettings::Read_v2() - TCODE_SETTINGS_CURRENT_DIMSTYLE_INDEX - invalid dimstyle index value");
      }
      else
      {
        // in archives with opennurbs version >= 200106100
        m_V5_current_dimension_style_index = (int)big_value;
        m_current_dimension_style_id = ON_nil_uuid;
      }
      break;
      
    case TCODE_SETTINGS_CURRENT_MATERIAL_INDEX:
      {
        int i32 = 0;
        if (rc) rc = file.ReadInt( &m_V5_current_render_material_index );
        if (rc) rc = file.ReadInt( &i32 );
        if (rc) m_current_material_source = ON::ObjectMaterialSource(i32);
        m_current_render_material_id = ON_nil_uuid;
      }
      break;
      
    case TCODE_SETTINGS_CURRENT_COLOR:
      {
        int i32 = 0;
        if (rc) rc = file.ReadColor( m_current_color );
        if (rc) rc = file.ReadInt( &i32 );
        if (rc) m_current_color_source = ON::ObjectColorSource(i32);
      }
      break;
      
    case TCODE_SETTINGS_CURRENT_WIRE_DENSITY:
      if ( big_value < -2 || big_value > 0x7FFFFFFF )
      {
        ON_ERROR("ON_3dmSettings::Read_v2() - TCODE_SETTINGS_CURRENT_WIRE_DENSITY - invalid current_wire_density value");
      }
      else
      {
        m_current_wire_density = (int)big_value;
      }
      break;
      
    case TCODE_SETTINGS_RENDER:
      rc = m_RenderSettings.Read(file)?true:false;
      if (rc)
        bHave3dmRenderSettings = true;
      break;

      
    case TCODE_SETTINGS_RENDER_USERDATA:
      if (bHave3dmRenderSettings)
      {
        // 2016-Nov-28 RH-33298 Dale Lear
        // ON_3dmRenderSettings user data in ON_3dmSettings
        //   I added support for saving userdata attached to the m_RenderSettings ON_3dmRenderSettings.
        //   Ideally, the ON_3dmRenderSettings would be read by calling file.ReadObject(), but
        //   userdata support is being added years after millions of files have been written by calling
        //   ON_3dmRenderSettings.Write()/Read().
        rc = file.ReadObjectUserData(m_RenderSettings);
      }
      break;

    case TCODE_SETTINGS_GRID_DEFAULTS:
      rc = m_GridDefaults.Read(file);
      break;

    case TCODE_SETTINGS_MODEL_URL: // added 21 June 2001
      rc = file.ReadString(m_model_URL);
      break;

    case TCODE_SETTINGS_ATTRIBUTES:
      {
        int major_version = 0;
        int minor_version = 0;
        for(;;)
        {
          rc = file.Read3dmChunkVersion(&major_version,&minor_version);
          if (!rc) break;
          if ( 1 == major_version )
          {
            // version 1.0 fields 23 March 2005
            rc = file.ReadDouble( &m_linetype_display_scale );
            if (!rc) break;

            rc = file.ReadColor(m_current_plot_color);
            if (!rc) break;
  
            int i;
            rc = file.ReadInt(&i);
            if (!rc) break;
            m_current_plot_color_source = ON::PlotColorSource(i);

            m_current_line_pattern_id = ON_nil_uuid;
            rc = file.ReadInt(&m_V5_current_line_pattern_index);
            if (!rc) break;

            rc = file.ReadInt(&i);
            if (!rc) break;
            m_current_linetype_source = ON::ObjectLinetypeSource(i);

            if ( minor_version >= 1 )
            {
              // Added 6 Feb 2006
              int mjv = 1, mnv = 1;
              rc = file.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&mjv,&mnv);
              if (rc)
              {
                rc = m_PageUnitsAndTolerances.Read(file);
                if ( !file.EndRead3dmChunk() )
                  rc = false;
              }


              if ( minor_version >= 2 )
              {
                // 1 Mar 2006 1.2 fields
                rc = file.ReadUuid(m_active_view_id);
                if (!rc) break;

                if ( minor_version >= 3 )
                {
                  rc = file.ReadPoint( m_model_basepoint);
                  if (!rc) break;
                  rc = m_earth_anchor_point.Read(file);
                  if (!rc) break;

                  if ( minor_version >= 4 )
                  {
                    rc = file.ReadBool(&m_IO_settings.m_bSaveTextureBitmapsInFile);
                    if (rc && minor_version >= 5)
                    {
                      rc = m_IO_settings.Read(file);
                      if (rc && minor_version >= 6 )
                      {
                        // 7 June 2006
                        m_CustomRenderMeshSettings.Read(file);

                        if (rc && minor_version >= 7 )
                        {
                          // V6 and later files use ids for the "current" table elements.
                          m_V5_current_layer_index = ON_UNSET_INT_INDEX;
                          m_V5_current_render_material_index = ON_UNSET_INT_INDEX;
                          m_V5_current_line_pattern_index = ON_UNSET_INT_INDEX;
                          m_V5_current_text_style_index = ON_UNSET_INT_INDEX;
                          m_V5_current_dimension_style_index = ON_UNSET_INT_INDEX;
                          // 30 September 2015
                          rc = file.ReadUuid(m_current_layer_id);
                          if (!rc) break;
                          rc = file.ReadUuid(m_current_render_material_id);
                          if (!rc) break;
                          rc = file.ReadUuid(m_current_line_pattern_id);
                          if (!rc) break;
                          rc = file.ReadUuid(m_current_text_style_id);
                          if (!rc) break;
                          rc = file.ReadUuid(m_current_dimension_style_id);
                          if (!rc) break;
                          rc = file.ReadUuid(m_current_hatch_pattern_id);
                          if (!rc) break;
                        }
                      }
                    }
                  }
                }
              }
            }

          }

          break;
        }
      }
      break;

    default:
      // information added in future will be skipped by file.EndRead3dmChunk()
      break;
    }

    if ( !file.EndRead3dmChunk() )
      rc = false;
    if ( TCODE_ENDOFTABLE == tcode )
      break;
  }

  return rc;
}

bool ON_3dmSettings::Read(ON_BinaryArchive& file )
{
  bool rc = false;

  *this = ON_3dmSettings::Default;

  if (60 > file.Archive3dmVersion())
  {
    m_AnnotationSettings.EnableLayoutSpaceAnnotationScaling(false);
    m_AnnotationSettings.EnableModelSpaceAnnotationScaling(false);
    m_AnnotationSettings.EnableHatchScaling(false);
    m_AnnotationSettings.Enable_V5_AnnotationScaling(false);
  }



  if ( 1 == file.Archive3dmVersion() ) 
  {
    rc = Read_v1(file); 
  }
  else
  {
    rc = Read_v2(file); 
  }

  return rc;
}


static bool ON_3dmSettings_Write_v1_TCODE_UNIT_AND_TOLERANCES(ON_BinaryArchive& file, const ON_3dmUnitsAndTolerances& UnitsAndTolerances )
{
  bool rc = true;
  int v = 1, us = 0;
  if (rc) rc = file.WriteInt( v ); // v = 1
  switch (UnitsAndTolerances.m_unit_system.UnitSystem()) 
  {
  case ON::LengthUnitSystem::None: 
    us=0; // NO_UNIT_SYSTEM
    break;
  case ON::LengthUnitSystem::Microns: 
    us=1; // MICRONS
    break;
  case ON::LengthUnitSystem::Millimeters:
    us=2; // MILLIMETERS
    break;
  case ON::LengthUnitSystem::Centimeters:
    us=3; // CENTIMETERS
    break;
  case ON::LengthUnitSystem::Meters:
    us=4; // METERS
    break;
  case ON::LengthUnitSystem::Kilometers:
    us=5; // KILOMETERS
    break;
  case ON::LengthUnitSystem::Microinches:
    us=6; // MICROINCHES
    break;
  case ON::LengthUnitSystem::Mils:
    us=7; // MILS
    break;
  case ON::LengthUnitSystem::Inches:
    us=8; // INCHES
    break;
  case ON::LengthUnitSystem::Feet:
    us=9; // FEET
    break;
  case ON::LengthUnitSystem::Miles:
    us=10; // MILES
    break;
  default:
    us=0; // NO_UNIT_SYSTEM
    break;
  }
  if (rc) rc = file.WriteInt( us );
  if (rc) rc = file.WriteDouble( UnitsAndTolerances.m_absolute_tolerance );
  if (rc) rc = file.WriteDouble( UnitsAndTolerances.m_relative_tolerance );
  if (rc) rc = file.WriteDouble( UnitsAndTolerances.m_angle_tolerance );

  return rc;
}

bool ON_3dmSettings::Write_v1(ON_BinaryArchive& file) const
{
  bool rc = true;

  // version 1 units and tolerances chunk
  rc = file.BeginWrite3dmChunk(TCODE_UNIT_AND_TOLERANCES,0);
  if (rc) {
    rc = ON_3dmSettings_Write_v1_TCODE_UNIT_AND_TOLERANCES( file, m_ModelUnitsAndTolerances );
    if (!file.EndWrite3dmChunk())
      rc = false;
  }

  return rc;
}

bool ON_3dmSettings::Write_v2(ON_BinaryArchive& file) const
{
  int i;
  bool rc = true;

  // TCODE_SETTINGS_PLUGINLIST - plugins that may have saved userdata in the file
  if (rc && file.Archive3dmVersion() >= 4 && m_plugin_list.Count() > 0 )
  {
    // The plug-in list chunk needs to be first, so the plug-ins that save
    // userdata on views can be loaded as needed.
    rc = file.BeginWrite3dmChunk(TCODE_SETTINGS_PLUGINLIST,0);
    if ( rc ) 
    {
      if (rc) rc = file.Write3dmChunkVersion(1,0);
      if (rc) rc = file.WriteInt( m_plugin_list.Count() );
      for ( i = 0; rc && i < m_plugin_list.Count(); i++ )
      {
        rc = m_plugin_list[i].Write(file);
      }

      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }

  // TCODE_PROPERTIES_UNITSANDTOLS - units and tolerances
  if ( rc  ) {
    rc = file.BeginWrite3dmChunk(TCODE_SETTINGS_UNITSANDTOLS,0);
    if ( rc ) {
      rc = m_ModelUnitsAndTolerances.Write(file);
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }

  // TCODE_SETTINGS_RENDERMESH - rendering defaults
  if ( rc  ) {
    rc = file.BeginWrite3dmChunk(TCODE_SETTINGS_RENDERMESH,0);
    if ( rc ) {
      rc = m_RenderMeshSettings.Write(file);
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }

  // TCODE_SETTINGS_ANALYSISMESH - analysis mesh defaults
  if ( rc  ) {
    rc = file.BeginWrite3dmChunk(TCODE_SETTINGS_ANALYSISMESH,0);
    if ( rc ) {
      rc = m_AnalysisMeshSettings.Write(file);
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }

  // TCODE_SETTINGS_ANNOTATION - annotation settings
  if ( rc  ) {
    rc = file.BeginWrite3dmChunk(TCODE_SETTINGS_ANNOTATION,0);
    if ( rc ) {
      rc = m_AnnotationSettings.Write(file);
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }

  // TCODE_SETTINGS_NAMED_CPLANE_LIST
  if ( rc  ) {
    rc = file.BeginWrite3dmChunk(TCODE_SETTINGS_NAMED_CPLANE_LIST,0);
    if ( rc ) {
      const int count = m_named_cplanes.Count();
      rc = file.WriteInt(count);
      for ( i = 0; i < count && rc; i++ ) {
        rc = file.BeginWrite3dmChunk( TCODE_VIEW_CPLANE, 0 );
        if (rc ) {
          rc = m_named_cplanes[i].Write(file);
          if ( !file.EndWrite3dmChunk() )
            rc = false;
        }
      }
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }

  // TCODE_SETTINGS_NAMED_VIEW_LIST
  if ( rc  ) {
    rc = file.BeginWrite3dmChunk(TCODE_SETTINGS_NAMED_VIEW_LIST,0);
    if ( rc ) {
      const int count = m_named_views.Count();
      rc = file.WriteInt(count);
      for ( i = 0; i < count && rc; i++ ) {
        rc = file.BeginWrite3dmChunk( TCODE_VIEW_RECORD, 0 );
        if (rc ) {
          rc = m_named_views[i].Write(file);
          if ( !file.EndWrite3dmChunk() )
            rc = false;
        }
      }
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }

  // TCODE_SETTINGS_VIEW_LIST
  if ( rc  ) {
    rc = file.BeginWrite3dmChunk(TCODE_SETTINGS_VIEW_LIST,0);
    if ( rc ) {
      const int count = m_views.Count();
      rc = file.WriteInt(count);
      for ( i = 0; i < count && rc; i++ ) {
        rc = file.BeginWrite3dmChunk( TCODE_VIEW_RECORD, 0 );
        if (rc ) {
          rc = m_views[i].Write(file);
          if ( !file.EndWrite3dmChunk() )
            rc = false;
        }
      }
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }

  // TCODE_SETTINGS_CURRENT_LAYER_INDEX
  if (rc) {
    int V5_index = m_V5_current_layer_index >= 0 ? m_V5_current_layer_index : 0;
    rc = file.BeginWrite3dmChunk( TCODE_SETTINGS_CURRENT_LAYER_INDEX, V5_index );
    if ( !file.EndWrite3dmChunk() )
      rc = false;
  }

  // TCODE_SETTINGS_CURRENT_MATERIAL_INDEX
  if (rc) {
    rc = file.BeginWrite3dmChunk( TCODE_SETTINGS_CURRENT_MATERIAL_INDEX, 0 );
    if (rc) {
      int V5_index = m_V5_current_render_material_index >= 0 ? m_V5_current_render_material_index : -1;
      rc = file.WriteInt( V5_index );
      i = m_current_material_source;
      if (rc) rc = file.WriteInt( i );
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }

  // TCODE_SETTINGS_CURRENT_COLOR
  if (rc) {
    rc = file.BeginWrite3dmChunk( TCODE_SETTINGS_CURRENT_COLOR, 0 );
    if (rc) {
      rc = file.WriteColor( m_current_color );
      i = m_current_color_source;
      if (rc) rc = file.WriteInt( i );
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }


  // TCODE_SETTINGS_CURRENT_WIRE_DENSITY
  if (rc) {
    rc = file.BeginWrite3dmChunk( TCODE_SETTINGS_CURRENT_WIRE_DENSITY, m_current_wire_density );
    if (rc) {
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }

  // TCODE_SETTINGS_RENDER
  if (rc) 
  {
    rc = file.BeginWrite3dmChunk( TCODE_SETTINGS_RENDER, 0 );
    if (rc) 
    {
      rc = m_RenderSettings.Write(file)?true:false;
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
    if (rc && file.Archive3dmVersion() >= 60 && file.ObjectHasUserDataToWrite(&m_RenderSettings) )
    {
      // 2016-Nov-28 RH-33298 Dale Lear
      // ON_3dmRenderSettings user data in ON_3dmSettings
      //   I added support for saving userdata attached to the m_RenderSettings ON_3dmRenderSettings.
      //   Ideally, the ON_3dmRenderSettings would be read by calling file.WriteObject(), but
      //   userdata support is being added years after millions of files have been written by calling
      //   ON_3dmRenderSettings.Write()/Read().
      rc = file.BeginWrite3dmChunk( TCODE_SETTINGS_RENDER_USERDATA, 0 );
      if(rc) 
      {
        rc = file.WriteObjectUserData(m_RenderSettings);
        // write a "fake" TCODE_OPENNURBS_CLASS_END end of class mark so I can use
        // ON_BinaryArchive::ReadObjectUserData() to read the m_RenderSettings user data.
        if ( file.BeginWrite3dmChunk( TCODE_OPENNURBS_CLASS_END, 0 ) ) 
        {
          if ( !file.EndWrite3dmChunk() )
            rc = false;
        }
        else
        {
          rc = false;
        }
        if ( !file.EndWrite3dmChunk() ) // end of TCODE_SETTINGS_RENDER_USERDATA
          rc = false;
      }
    }
  }

  // TCODE_SETTINGS_GRID_DEFAULTS
  if (rc) {
    rc = file.BeginWrite3dmChunk( TCODE_SETTINGS_GRID_DEFAULTS, 0 );
    if (rc) {
      rc = m_GridDefaults.Write(file);
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }

  // TCODE_SETTINGS_MODEL_URL - added 21 June 2001
  if (rc && m_model_URL.Length() > 0 ) {
    rc = file.BeginWrite3dmChunk( TCODE_SETTINGS_MODEL_URL, 0 );
    if (rc) {
      rc = file.WriteString(m_model_URL);
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }

  // TCODE_SETTINGS_CURRENT_FONT_INDEX - added 10 June 2002
  if (rc) {
    int V5_index = m_V5_current_text_style_index >= 0 ? m_V5_current_text_style_index : 0;
    rc = file.BeginWrite3dmChunk( TCODE_SETTINGS_CURRENT_FONT_INDEX, V5_index );
    if ( !file.EndWrite3dmChunk() )
      rc = false;
  }
    
  // TCODE_SETTINGS_CURRENT_DIMSTYLE_INDEX - added 10 June 2002
  if (rc) {
    int V5_index = m_V5_current_dimension_style_index >= 0 ? m_V5_current_dimension_style_index : 0;
    rc = file.BeginWrite3dmChunk( TCODE_SETTINGS_CURRENT_DIMSTYLE_INDEX, V5_index );
    if ( !file.EndWrite3dmChunk() )
      rc = false;
  }

  // TCODE_SETTINGS_ATTRIBUTES
  if (rc && file.Archive3dmVersion() >= 4 )
  {
    // 23 March 2005 Dale Lear
    rc = file.BeginWrite3dmChunk(TCODE_SETTINGS_ATTRIBUTES, 0 );
    if (rc)
    {
      for(;;)
      {
        // 1.0 - 23 March 2005
        // 1.1 -  6 Feb   2006
        // 1.2 -  1 March 2006
        // 1.3 - 29 March 2006
        // 1.4 - 18 April 2006
        // 1.5 - 21 April 2006
        // 1.6 -  7 June  2006
        // 1.7 - 30 September 2015
        rc = file.Write3dmChunkVersion(1,7);

        // version 1.0 fields 
        rc = file.WriteDouble( m_linetype_display_scale );
        if (!rc) break;

        rc = file.WriteColor(m_current_plot_color);
        if (!rc) break;

        rc = file.WriteInt(m_current_plot_color_source);
        if (!rc) break;

        int V5_index = m_V5_current_line_pattern_index >= 0 ? m_V5_current_line_pattern_index : -1;
        rc = file.WriteInt(V5_index);
        if (!rc) break;

        rc = file.WriteInt(m_current_linetype_source);
        if (!rc) break;

        // 6 Feb 2006, 1.1 fields

        // the units and tols has to be inside a chunk
        rc = file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0);
        if (rc)
        {
          rc = m_PageUnitsAndTolerances.Write(file);
          if ( !file.EndWrite3dmChunk() )
            rc = false;
        }
        if (!rc) break;

        // 1 Mar 2006 1.2 fields
        rc = file.WriteUuid(m_active_view_id);
        if (!rc) break;

        // 29 March 2006 1.3 fields
        rc = file.WritePoint( m_model_basepoint);
        if (!rc) break;
        rc = m_earth_anchor_point.Write(file);
        if (!rc) break;

        // 18 April 2006 1.4 fields
        rc = file.WriteBool(m_IO_settings.m_bSaveTextureBitmapsInFile);
        if (!rc) break;

        // 21 April 2006 1.5 fields
        rc = m_IO_settings.Write(file);
        if (!rc) break;

        // 7 June 2006 1.6 fields
        rc = m_CustomRenderMeshSettings.Write(file);
        if (!rc) break;

        // 1.7 - 30 September 2015
        //  switching from indices to ids
        rc = file.WriteUuid(m_current_layer_id);
        if (!rc) break;
        rc = file.WriteUuid(m_current_render_material_id);
        if (!rc) break;
        rc = file.WriteUuid(m_current_line_pattern_id);
        if (!rc) break;
        rc = file.WriteUuid(m_current_text_style_id);
        if (!rc) break;
        rc = file.WriteUuid(m_current_dimension_style_id);
        if (!rc) break;
        rc = file.WriteUuid(m_current_hatch_pattern_id);
        if (!rc) break;

        break;
      }

      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }

  // required TCODE_ENDOFTABLE chunk - marks end of settings table
  if ( rc ) {
    rc = file.BeginWrite3dmChunk( TCODE_ENDOFTABLE, 0 );
    if ( rc ) {
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }


  return rc;
}

bool ON_3dmSettings::Write(ON_BinaryArchive& file) const
{
  bool rc = false;
  if ( 1 == file.Archive3dmVersion() ) 
  {
    rc = Write_v1(file); 
  }
  else
  {
    rc = Write_v2(file); 
  }
  return rc;
}

void ON_3dmSettings::Dump( ON_TextLog& dump ) const
{
  int i;

  const wchar_t* model_URL = static_cast< const wchar_t* >(m_model_URL);
  if ( model_URL && *model_URL ) 
  {
    dump.Print("Model URL: %ls\n",model_URL);
  }
  dump.Print("Model space units and tolerances:\n");
  dump.PushIndent();
  m_ModelUnitsAndTolerances.Dump(dump);
  dump.PopIndent();

  dump.Print("Page space units and tolerances:\n");
  dump.PushIndent();
  m_PageUnitsAndTolerances.Dump(dump);
  dump.PopIndent();

  dump.Print("Render mesh settings:\n");
  dump.PushIndent();
  m_RenderMeshSettings.Dump(dump);
  dump.PopIndent();

  dump.Print("Analysis mesh settings:\n");
  dump.PushIndent();
  m_AnalysisMeshSettings.Dump(dump);
  dump.PopIndent();

  dump.Print("Render settings:\n");
  dump.PushIndent();
  m_RenderSettings.Dump(dump);
  dump.PopIndent();

  dump.Print("Annotation settings:\n");
  dump.PushIndent();
  m_AnnotationSettings.Dump(dump);
  dump.PopIndent();

  dump.Print("Construction plane grid defaults:\n");
  dump.PushIndent();
  m_GridDefaults.Dump(dump);
  dump.PopIndent();

  dump.Print("Named construction planes:\n");
  dump.PushIndent();
  for ( i = 0; i < m_named_cplanes.Count(); i++ )
  {
    dump.Print("named construction plane %d:\n");
    dump.PushIndent();
    m_named_cplanes[i].Dump(dump);
    dump.PopIndent();
  }
  dump.PopIndent();

  dump.Print("Named views:\n");
  dump.PushIndent();
  for ( i = 0; i < m_named_views.Count(); i++ )
  {
    dump.Print("named view %d:\n",i);
    dump.PushIndent();
    m_named_views[i].Dump(dump);
    dump.PopIndent();
  }
  dump.PopIndent();

  dump.Print("Model views:\n");
  dump.PushIndent();
  for ( i = 0; i < m_views.Count(); i++ )
  {
    dump.Print("model view %d:\n",i);
    dump.PushIndent();
    m_views[i].Dump(dump);
    dump.PopIndent();
  }
  dump.PopIndent();

  dump.Print("New object attributes:\n");
  dump.PushIndent();
  {
    dump.Print("Current display color rgb");dump.PrintRGB(m_current_color); dump.Print(":\n");
    dump.Print("Current display color source = %d\n",m_current_color_source);
    dump.Print("Current plot color rgb");dump.PrintRGB(m_current_plot_color); dump.Print(":\n");
    dump.Print("Current plot color source = %d\n",m_current_plot_color_source);
    if ( ON_UNSET_INT_INDEX != m_V5_current_render_material_index)
      dump.Print("Current V5 material index = %d\n",m_V5_current_render_material_index);
    dump.Print("Current material source = %d\n",m_current_material_source);
    if ( ON_UNSET_INT_INDEX != m_V5_current_line_pattern_index)
      dump.Print("Current V5 linetype index = %d\n",m_V5_current_line_pattern_index);
    dump.Print("Current linetype source = %d\n",m_current_linetype_source);
    if ( ON_UNSET_INT_INDEX != m_V5_current_layer_index)
      dump.Print("Current V5 layer index = %d\n",m_V5_current_layer_index);
    if (false == dump.IsTextHash())
    {
      // The legacy m_V5_current_text_style_index varies
      // depending on what application writes the file.
      // It must be ignored when comparing content.
      if (ON_UNSET_INT_INDEX != m_V5_current_text_style_index)
        dump.Print("Current font index = %d\n", m_V5_current_text_style_index);
    }
    if ( ON_UNSET_INT_INDEX != m_V5_current_dimension_style_index)
      dump.Print("Current V5 dimstyle index = %d\n",m_V5_current_dimension_style_index);
    dump.Print("Current wire density = %d\n",m_current_wire_density);
    dump.Print("Linetype diaplay scale = %g\n",m_linetype_display_scale);
  }
  dump.PopIndent();

  dump.Print("Plug-in list\n");
  dump.PushIndent();
  for ( i = 0; i < m_plugin_list.Count(); i++ )
  {
    dump.Print("plug-in %d:\n",i);
    dump.PushIndent();
    m_plugin_list[i].Dump(dump);
    dump.PopIndent();
  }
  dump.PopIndent();

}


//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmAnimationProperties
//

const ON_3dmAnimationProperties ON_3dmAnimationProperties::Default;

bool ON_3dmAnimationProperties::Read(ON_BinaryArchive& archive)
{
  //*this = ON_3dmAnimationProperties::Default;

// If the file archive version is not 4,
  // just return.
  if( archive.Archive3dmVersion() < 4 )
    return true;

  if (archive.Archive3dmVersion() == 4)
  {
    // This fixes bugs like RH-35784
    // It appears that the current code in CAnimationToolsPlugIn::ReadDocument()
    // is not capable of reading information saved by the V4 version of this plug-in.

    return true;
  }

  // Read the major and minor version of the
  // document data
  int major = 0, minor = 0;
  if( !archive.Read3dmChunkVersion(&major, &minor) )
    return false;

  // At this point, if we've changed the format of
  // our document data, we'll want to compare the
  // major and minor revision numbers and read our
  // data accordingly.

	//READ camera and target points count
	int cp_count = 0;
  if( !archive.ReadInt(&cp_count) )
    return false;
	int tp_count = 0;
  if( !archive.ReadInt(&tp_count) )
    return false;
	if( cp_count < 1 || tp_count < 1 )
		return true;

	m_aCameraPoints.SetCount(0);
	m_aTargetPoints.SetCount(0);

	for( int i = 0; i < cp_count; i++ )
	{
		//read camera points
		ON_3dPoint pt = ON_3dPoint::UnsetPoint;
		if( !archive.ReadPoint( pt )  )
			return false;
		m_aCameraPoints.Append( pt );
	}
	for( int i = 0; i < tp_count; i++ )
	{
		//read camera points
		ON_3dPoint pt = ON_3dPoint::UnsetPoint;
		if( !archive.ReadPoint( pt )  )
			return false;
		m_aTargetPoints.Append( pt );
	}

	//READ OTHER PARAMETERS
	int act = 5;//none
	if( !archive.ReadInt( &act ) )
		return false;
	if( act < 0 || act > 5 )
		return true;
	m_CaptureTypes = static_cast<CaptureTypes>(act);

	if( !archive.ReadString(m_sFileExtension))
		return false;
	if( !archive.ReadString(m_sCaptureMethod))
		return false;
	if( !archive.ReadUuid(m_idDisplayMode))
		return false;
	if( !archive.ReadString(m_sHtmlFilename))
		return false;
	if( !archive.ReadString(m_sViewport))
		return false;
	if( !archive.ReadInt(&m_iFrameCount))
		return false;
	if( !archive.ReadInt(&m_iCurrentFrame))
		return false;
	if( !archive.ReadUuid(m_idCameraPath))
		return false;
	if( !archive.ReadUuid(m_idTargetPath))
		return false;
	if( !archive.ReadDouble(&m_dLatitude))
		return false;
	if( !archive.ReadDouble(&m_dLongitude))
		return false;
	if( !archive.ReadDouble(&m_dNorthAngle))
		return false;
	if( !archive.ReadInt(&m_iStartDay))
		return false;
	if( !archive.ReadInt(&m_iStartMonth))
		return false;
	if( !archive.ReadInt(&m_iStartYear))
		return false;
	if( !archive.ReadInt(&m_iEndDay)  )
		return false;
	if( !archive.ReadInt(&m_iEndMonth))
		return false;
	if( !archive.ReadInt(&m_iEndYear))
		return false;
	if( !archive.ReadInt(&m_iStartHour))
		return false;
	if( !archive.ReadInt(&m_iStartMinutes))
		return false;
	if( !archive.ReadInt(&m_iStartSeconds))
		return false;
	if( !archive.ReadInt(&m_iEndHour))
		return false;
	if( !archive.ReadInt(&m_iEndMinutes))
		return false;
	if( !archive.ReadInt(&m_iEndSeconds))
		return false;
	if( !archive.ReadInt(&m_iDaysBetweenFrames))
		return false;
	if( !archive.ReadInt(&m_iMinutesBetweenFrames))
		return false;
	if( !archive.ReadString(m_sFolderName))
		return false;
	if( !archive.ReadInt(&m_iLightIndex))
		return false;
	if( !archive.ReadBool(&m_bRenderFull))
		return false;
	if( !archive.ReadBool(&m_bRenderPreview))
		return false;
	
  return true;
}

bool ON_3dmAnimationProperties::Write(ON_BinaryArchive& archive) const
{
  int cp_count = CameraPoints().Count();
  int tp_count = TargetPoints().Count();

	//Added by Rajaa - May 2, 2009 - next 2 lines commented out (test added to CallWriteDocument)
	// Bug # 48383 - all validation happens on CallWriteDocument and not WriteDocument

	if( cp_count < 1 || tp_count < 1)
		return true;

  if( !archive.WriteInt( cp_count ) )//Count of camera points
    return true;
  if( !archive.WriteInt( tp_count ) )// count of target points
    return false;

	for( int i = 0; i < cp_count; i++ )
	{
		//write camera points
		if( !archive.WritePoint( m_aCameraPoints[i] )  )
			return false;
	}
	for( int i = 0; i < tp_count; i++ )
	{
		//write camera points
		if( !archive.WritePoint( m_aTargetPoints[i] )  )
			return false;
	}

	//SAVE OTHER PARAMETERS
//	ARecord::AType AnimationCaptureType;
	const int iCaptureType = static_cast<int>(m_CaptureTypes);
	if( !archive.WriteInt(iCaptureType))
		return false;
	if( !archive.WriteString(m_sFileExtension))
		return false;
	if( !archive.WriteString(m_sCaptureMethod))
		return false;
	if( !archive.WriteUuid(m_idDisplayMode))
		return false;
	if( !archive.WriteString(m_sHtmlFilename))
		return false;
	if( !archive.WriteString(m_sViewport))
		return false;
	if( !archive.WriteInt(m_iFrameCount))
		return false;
	if( !archive.WriteInt(m_iCurrentFrame))
		return false;
	if( !archive.WriteUuid(m_idCameraPath))
		return false;
	if( !archive.WriteUuid(m_idTargetPath))
		return false;
	if( !archive.WriteDouble(m_dLatitude))
		return false;
	if( !archive.WriteDouble(m_dLongitude))
		return false;
	if( !archive.WriteDouble(m_dNorthAngle))
		return false;
	if( !archive.WriteInt(m_iStartDay))
		return false;
	if( !archive.WriteInt(m_iStartMonth))
		return false;
	if( !archive.WriteInt(m_iStartYear))
		return false;
	if( !archive.WriteInt(m_iEndDay))
		return false;
	if( !archive.WriteInt(m_iEndMonth))
		return false;
	if( !archive.WriteInt(m_iEndYear))
		return false;
	if( !archive.WriteInt(m_iStartHour))
		return false;
	if( !archive.WriteInt(m_iStartMinutes))
		return false;
	if( !archive.WriteInt(m_iStartSeconds))
		return false;
	if( !archive.WriteInt(m_iEndHour))
		return false;
	if( !archive.WriteInt(m_iEndMinutes))
		return false;
	if( !archive.WriteInt(m_iEndSeconds))
		return false;
	if( !archive.WriteInt(m_iDaysBetweenFrames))
		return false;
	if( !archive.WriteInt(m_iMinutesBetweenFrames))
		return false;
	if( !archive.WriteString(m_sFolderName))
		return false;
	if( !archive.WriteInt(m_iLightIndex))
		return false;
	if( !archive.WriteBool(m_bRenderFull))
		return false;
	if( !archive.WriteBool(m_bRenderPreview))
		return false;

  return true;
}

ON_3dmAnimationProperties::CaptureTypes ON_3dmAnimationProperties::CaptureType(void) const
{
  return m_CaptureTypes;
}

void ON_3dmAnimationProperties::SetCaptureType(CaptureTypes type)
{
  m_CaptureTypes = type;
}

ON_wString ON_3dmAnimationProperties::FileExtension(void) const
{
  return m_sFileExtension;
}

void ON_3dmAnimationProperties::SetFileExtension(const ON_wString& s)
{
  m_sFileExtension = s;
}

ON_UUID ON_3dmAnimationProperties::DisplayMode(void) const
{
  return m_idDisplayMode;
}

void ON_3dmAnimationProperties::SetDisplayMode(const ON_UUID& id)
{
  m_idDisplayMode = id;
}

ON_wString ON_3dmAnimationProperties::ViewportName(void) const
{
  return m_sViewport;
}

void ON_3dmAnimationProperties::SetViewportName(const ON_wString& s)
{
  m_sViewport = s;
}

ON_wString ON_3dmAnimationProperties::HtmlFilename(void) const
{
  return m_sHtmlFilename;
}

void ON_3dmAnimationProperties::SetHtmlFilename(const ON_wString& s)
{
  m_sHtmlFilename = s;
}

ON_wString ON_3dmAnimationProperties::CaptureMethod(void) const
{
  return m_sCaptureMethod;
}

void ON_3dmAnimationProperties::SetCaptureMethod(const ON_wString& s)
{
  m_sCaptureMethod = s;
}

ON_3dPointArray& ON_3dmAnimationProperties::CameraPoints(void)
{
  return m_aCameraPoints;
}

const ON_3dPointArray& ON_3dmAnimationProperties::CameraPoints(void) const
{
  return m_aCameraPoints;
}

ON_3dPointArray& ON_3dmAnimationProperties::TargetPoints(void)
{
  return m_aTargetPoints;
}

const ON_3dPointArray& ON_3dmAnimationProperties::TargetPoints(void) const
{
  return m_aTargetPoints;
}

int ON_3dmAnimationProperties::FrameCount(void) const
{
  return m_iFrameCount;
}

void ON_3dmAnimationProperties::SetFrameCount(int i)
{
  m_iFrameCount = i;
}

int ON_3dmAnimationProperties::CurrentFrame(void) const
{
  return m_iCurrentFrame;
}

void ON_3dmAnimationProperties::SetCurrentFrame(int i)
{
  m_iCurrentFrame = i;
}

ON_UUID ON_3dmAnimationProperties::CameraPathId(void) const
{
  return m_idCameraPath;
}

void ON_3dmAnimationProperties::SetCameraPathId(const ON_UUID& id)
{
  m_idCameraPath = id;
}

ON_UUID ON_3dmAnimationProperties::TargetPathId(void) const
{
  return m_idTargetPath;
}

void ON_3dmAnimationProperties::SetTargetPathId(const ON_UUID& id)
{
  m_idTargetPath = id;
}

double ON_3dmAnimationProperties::Latitude(void) const
{
  return m_dLatitude;
}

void ON_3dmAnimationProperties::SetLatitude(double d)
{
  m_dLatitude = d;
}

double ON_3dmAnimationProperties::Longitude(void) const
{
  return m_dLongitude;
}

void ON_3dmAnimationProperties::SetLongitude(double d)
{
  m_dLongitude = d;
}

double ON_3dmAnimationProperties::NorthAngle(void) const
{
  return m_dNorthAngle;
}

void ON_3dmAnimationProperties::SetNorthAngle(double d)
{
  m_dNorthAngle = d;
}

int ON_3dmAnimationProperties::StartDay(void) const
{
  return m_iStartDay;
}

void ON_3dmAnimationProperties::SetStartDay(int i)
{
  m_iStartDay = i;
}

int ON_3dmAnimationProperties::StartMonth(void) const
{
  return m_iStartMonth;
}

void ON_3dmAnimationProperties::SetStartMonth(int i)
{
  m_iStartMonth = i;
}

int ON_3dmAnimationProperties::StartYear(void) const
{
  return m_iStartYear;
}

void ON_3dmAnimationProperties::SetStartYear(int i)
{
  m_iStartYear = i;
}

int ON_3dmAnimationProperties::EndDay(void) const
{
  return m_iEndDay;
}

void ON_3dmAnimationProperties::SetEndDay(int i)
{
  m_iEndDay = i;
}

int ON_3dmAnimationProperties::EndMonth(void) const
{
  return m_iEndMonth;
}

void ON_3dmAnimationProperties::SetEndMonth(int i)
{
  m_iEndMonth= i;
}

int ON_3dmAnimationProperties::EndYear(void) const
{
  return m_iEndYear;
}

void ON_3dmAnimationProperties::SetEndYear(int i)
{
  m_iEndYear = i;
}

int ON_3dmAnimationProperties::StartHour(void) const
{
  return m_iStartHour;
}

void ON_3dmAnimationProperties::SetStartHour(int i)
{
  m_iStartHour = i;
}

int ON_3dmAnimationProperties::StartMinutes(void) const
{
  return m_iStartMinutes;
}

void ON_3dmAnimationProperties::SetStartMinutes(int i)
{
  m_iStartMinutes = i;
}

int ON_3dmAnimationProperties::StartSeconds(void) const
{
  return m_iStartSeconds;
}

void ON_3dmAnimationProperties::SetStartSeconds(int i)
{
  m_iStartSeconds = i;
}

int ON_3dmAnimationProperties::EndHour(void) const
{
  return m_iEndHour;
}

void ON_3dmAnimationProperties::SetEndHour(int i)
{
  m_iEndHour = i;
}

int ON_3dmAnimationProperties::EndMinutes(void) const
{
  return m_iEndMinutes;
}

void ON_3dmAnimationProperties::SetEndMinutes(int i)
{
  m_iEndMinutes = i;
}

int ON_3dmAnimationProperties::EndSeconds(void) const
{
  return m_iEndSeconds;
}

void ON_3dmAnimationProperties::SetEndSeconds(int i)
{
  m_iEndSeconds = i;
}

int ON_3dmAnimationProperties::DaysBetweenFrames(void) const
{
  return m_iDaysBetweenFrames;
}

void ON_3dmAnimationProperties::SetDaysBetweenFrames(int i)
{
  m_iDaysBetweenFrames = i;
}

int ON_3dmAnimationProperties::MinutesBetweenFrames(void) const
{
  return m_iMinutesBetweenFrames;
}

void ON_3dmAnimationProperties::SetMinutesBetweenFrames(int i)
{
  m_iMinutesBetweenFrames = i;
}

int ON_3dmAnimationProperties::LightIndex(void) const
{
  return m_iLightIndex;
}

void ON_3dmAnimationProperties::SetLightIndex(int i)
{
  m_iLightIndex = i;
}

ON_wString ON_3dmAnimationProperties::FolderName(void) const
{return m_sFolderName;
}

void ON_3dmAnimationProperties::SetFolderName(const ON_wString& s)
{
  m_sFolderName = s;
}

const ON_ClassArray<ON_wString>& ON_3dmAnimationProperties::Images(void) const
{
  return m_aImages;
}

ON_ClassArray<ON_wString>& ON_3dmAnimationProperties::Images(void)
{
  return m_aImages;
}

ON_ClassArray<ON_wString>& ON_3dmAnimationProperties::Dates(void)
{
  return m_aDates;
}

const ON_ClassArray<ON_wString>& ON_3dmAnimationProperties::Dates(void) const
{
  return m_aDates;
}

bool ON_3dmAnimationProperties::RenderFull(void) const
{
  return m_bRenderFull;
}

void ON_3dmAnimationProperties::SetRenderFull(bool b)
{
  m_bRenderFull = b;
}

bool ON_3dmAnimationProperties::RenderPreview(void) const
{
  return m_bRenderPreview;
}

void ON_3dmAnimationProperties::SetRenderPreview(bool b)
{
  m_bRenderPreview = b;
}
