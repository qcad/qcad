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

int ON_ParseAngleExpression( 
  const wchar_t* str,
  int str_count,
  ON_ParseSettings parse_settings,
  const ON::AngleUnitSystem angle_value_unit_system,
  double* angle_value,
  ON_ParseSettings* parse_results,
  ON::AngleUnitSystem* str_angle_unit_system
  )
{
  ON::AngleUnitSystem parsed_angle_us = ON::AngleUnitSystem::None;

  double x = ON_UNSET_VALUE;
  int parsed_element_count = ON_ParseAngleExpression(
    str,
    str_count,
    parse_settings,
    &x,
    parse_results,
    &parsed_angle_us
    );

  if ( parsed_element_count > 0 )
  {
    if (    parsed_angle_us != angle_value_unit_system 
         && ON::AngleUnitSystem::None != angle_value_unit_system
         && ON::AngleUnitSystem::None != parsed_angle_us
         )
    {
      double s = ON::AngleUnitScale(parsed_angle_us,angle_value_unit_system);
      x *= s;
    }
  }

  if ( 0 != str_angle_unit_system )
    *str_angle_unit_system = parsed_angle_us;
  if ( 0 != angle_value )
    *angle_value = x;

  return parsed_element_count;
}

int ON_ParseAngleRadiansExpression( 
  const wchar_t* str,
  int str_count,
  ON::AngleUnitSystem default_str_angle_unit_system,
  double* angle_value_in_radians
  )
{
  ON_ParseSettings ps(ON_ParseSettings::DefaultSettings);
  ps.SetDefaultAngleUnitSystem(default_str_angle_unit_system);

  int parsed_element_count = ON_ParseAngleExpression(
    str,
    str_count,
    ps,
    ON::AngleUnitSystem::Radians, // specify radians as the unit system for the returned value
    angle_value_in_radians,
    nullptr,
    nullptr
    );

  return parsed_element_count;
}

int ON_ParseAngleArcDegreesExpression( 
  const wchar_t* str,
  int str_count,
  ON::AngleUnitSystem default_str_angle_unit_system,
  double* angle_value_in_arc_degrees
  )
{
  ON_ParseSettings ps(ON_ParseSettings::DefaultSettings);
  ps.SetDefaultAngleUnitSystem(default_str_angle_unit_system);

  int parsed_element_count = ON_ParseAngleExpression(
    str,
    str_count,
    ps,
    ON::AngleUnitSystem::Degrees, // specify arc_degrees as the unit system for the returned value
    angle_value_in_arc_degrees,
    nullptr,
    nullptr
    );

  return parsed_element_count;
}
