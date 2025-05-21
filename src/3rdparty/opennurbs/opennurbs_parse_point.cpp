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

int ON_ParsePointExpression(
  const wchar_t* str,
  int str_count,
  ON::AngleUnitSystem default_str_angle_unit_system,
  ON::LengthUnitSystem point_value_unit_system,
  ON_3dPoint* point_value
  )
{
  ON_ParseSettings ps(ON_ParseSettings::DefaultSettingsInRadians);
  ps.SetDefaultAngleUnitSystem(default_str_angle_unit_system);
  return ON_ParsePointExpression(
    str,str_count,
    ps,
    point_value_unit_system,point_value,
    0);
}

int ON_ParsePointExpression(
  const wchar_t* str,
  int str_count,
  ON::AngleUnitSystem default_str_angle_unit_system,
  const ON_UnitSystem& point_value_unit_system,
  ON_3dPoint* point_value
  )
{
  ON_ParseSettings ps(ON_ParseSettings::DefaultSettingsInRadians);
  ps.SetDefaultAngleUnitSystem(default_str_angle_unit_system);
  return ON_ParsePointExpression(
    str,str_count,
    ps,
    point_value_unit_system,point_value,
    0);
}

int ON_ParsePointExpression(
  const wchar_t* str,
  int str_count,
  ON_ParseSettings parse_settings,
  const ON_UnitSystem& point_value_unit_system,
  ON_3dPoint* point_value,
  ON_ParseSettings* parse_results
  )
{
  ON::LengthUnitSystem pt_unit_system;
  double pt_scale = 1.0;
  switch(point_value_unit_system.UnitSystem())
  {
  case ON::LengthUnitSystem::CustomUnits:
    pt_unit_system = ON::LengthUnitSystem::Meters;
    pt_scale = ON::UnitScale(pt_unit_system,point_value_unit_system);
    break;
  default:
    pt_unit_system = point_value_unit_system.UnitSystem();
    pt_scale = 1.0;
    break;
  }

  const int str_index = ON_ParsePointExpression(
    str, str_count,
    parse_settings,
    pt_unit_system,
    point_value,
    parse_results
    );

  if ( point_value && str_index > 0 && 1.0 != pt_scale )
  {
    if ( ON_IsValid(point_value->x) )
      point_value->x *= pt_scale;
    if ( ON_IsValid(point_value->y) )
      point_value->y *= pt_scale;
    if ( ON_IsValid(point_value->z) )
      point_value->z *= pt_scale;
  }

  return str_index;
}

ON_2dVector CosineAndSine(double a)
{
  ON_2dVector v;

  if ( ON_IsValid(a) )
  {
    v.x = cos(a);
    v.y = sin(a);
    if ( fabs(v.x) >= ON_EPSILON || fabs(v.y) <= ON_EPSILON )
    {
      v.x = (v.x < 0.0) ? -1.0 : 1.0;
      v.y = 0.0;
    }
    else if ( fabs(v.y) >= ON_EPSILON || fabs(v.x) <= ON_EPSILON )
    {
      v.y = (v.y < 0.0) ? -1.0 : 1.0;
      v.x = 0.0;
    }
  }
  else
  {
    v = ON_2dVector::NanVector;
  }

  return v;
}

int ON_ParsePointExpression(
  const wchar_t* str,
  int str_count,
  ON_ParseSettings parse_settings,
  ON::LengthUnitSystem point_value_unit_system,
  ON_3dPoint* point_value,
  ON_ParseSettings* parse_results
  )
{
  ON_2dVector cos_sin_a0, cos_sin_a1;
  double x = ON_UNSET_VALUE, y = ON_UNSET_VALUE, z = 0.0;
  double r = ON_UNSET_VALUE, polar_angle = ON_UNSET_VALUE, spherical_angle = ON_UNSET_VALUE;

  if ( point_value )
    *point_value = ON_3dPoint::Origin;
  if ( parse_results)
    *parse_results = ON_ParseSettings::FalseSettings;

  ON_ParseSettings prx(ON_ParseSettings::FalseSettings);
  ON_ParseSettings pry(ON_ParseSettings::FalseSettings);
  ON_ParseSettings prz(ON_ParseSettings::FalseSettings);

  int str_index = 0;

  bool bPolarAngle = false;

  for(;;)
  {
    if ( -1 == str_count )
      str_count = ON_ParseSettings::max_expression_str_count;

    if ( str_count <= 0 )
      break;

    int i0 = 0;
    if ( parse_settings.ParseLeadingWhiteSpace() )
    {
      while ( i0 < str_count && parse_settings.IsLeadingWhiteSpace(str[i0]) )
        i0++;
      if ( i0 >= str_count )
        break;
     parse_settings.SetParseLeadingWhiteSpace(false);
    }

    int i1 = ON_ParseLengthExpression(
      str+i0, str_count-i0,
      parse_settings,
      point_value_unit_system,
      &x,
      &prx,
      0
      );
    if ( i1 < 1)
      break;

    i1 += i0;
    if ( i1 == str_count && i0+1 == i1 && '0' == str[i0] && 0.0 == x )
    {
      // world origin specified as a single zero.
      y = 0.0;
      z = 0.0;
      str_index = i0+i1;
      break;
    }

    if ( i1 >= str_count )
      break;

    if ( i1+2 <= str_count && str[i1] == ',' && str[i1+1] == '<' )
    {
      // It is a common for people to type "d,<a" instead of "d<a"
      // and this clause allows them to do it.
      i1++;
      if ( i1 >= str_count)
        break;
    }

    int i2;
    if ( str[i1] != ',' )
    {
      i1++;
      if ( i1 >= str_count )
        break;
      i2 = ON_ParseLengthExpression(
            str+i1, str_count-i1,
            parse_settings,
            point_value_unit_system,
            &y,
            &pry,
            0
            );
      if ( i2 > 0 && i1+i0 <= str_count && ON_IsValid(x) && ON_IsValid(y) )
      {
        r = ON_2dVector(x,y).Length();
      }
    }
    else if ( str[i1] == '<' )
    {
      bPolarAngle = true;
      r = x;
      x = ON_UNSET_VALUE;
      i1++;
      if ( i1 >= str_count )
        break;
      i2 = ON_ParseAngleExpression(
            str+i1, str_count-i1,
            parse_settings,
            ON::AngleUnitSystem::Radians,
            &polar_angle,
            &pry,
            0
            );
      if ( i2 > 0 && i1+i0 <= str_count && ON_IsValid(polar_angle) && ON_IsValid(r) )
      {
        cos_sin_a0 = CosineAndSine(polar_angle);
        x = r*cos_sin_a0.x;
        y = r*cos_sin_a0.y;
      }
      else
      {
        break;
      }
    }
    else if ( i0+1 == i1 && '0' == str[i0] && 0.0 == x )
    {
      // single 0 for origin
      y = 0.0;
      str_index = i1;
      pry = ON_ParseSettings::FalseSettings;
      break;
    }
    else
    {
      i2 = 0;
    }

    if ( i2 <= 0 )
      break;

    i2 += i1;

    if ( i2 >= str_count )
    {
      // 2d point
      str_index = i2;
      break;
    }

    if ( i2+2 <= str_count && str[i2] == ',' && str[i2+1] == '<' )
    {
      // It is a common for people to type "x,y,<a" instead of "x,y<a"
      // and this clause allows them to do it.
      i2++;
      if ( i2 >= str_count )
        break;
    }

    int i3;
    if ( str[i2] == ',' ) 
    {
      i2++;
      if ( i2 >= str_count )
        break;
      i3 = ON_ParseLengthExpression(
        str+i2, str_count-i2,
        parse_settings,
        point_value_unit_system,
        &z,
        &prz,
        0
        );
    }
    else if (  str[i2] == '<' )
    {
      // spherical angle
      i3 = ON_ParseAngleExpression(
        str+i2, str_count-i2,
        parse_settings,
        ON::AngleUnitSystem::Radians,
        &spherical_angle,
        &prz,
        0
        );
      if ( i3 <= 0 || i2+i3 > str_count )
        break;
      if ( !ON_IsValid(spherical_angle) || !ON_IsValid(r) || !(r >= 0.0) )
        break;
      cos_sin_a1 = CosineAndSine(spherical_angle);
      if ( bPolarAngle )
      {
        // spherical coordinates (r<a<e)
        if ( cos_sin_a1.x >= 0.0 )
        {
          x = r*cos_sin_a1.x; 
          y = r*cos_sin_a1.x;
          z = r*cos_sin_a1.y;
        }
        else
        {
          break;
        }
      }
      else if ( cos_sin_a1.x > 0.0 )
      {
        // elevation (x,y<e)
        double tan_a = tan(spherical_angle);
        if ( ON_IsValid(tan_a) )
          z = r*tan_a;
        else
          break;
      }
      else
      {
        break;
      }
    }
    else
    {
      // 2d point
      str_index = i2;
      break;
    }

    if ( i3 <= 0 )
      break;
    i3 += i2;
    if ( i3 > str_count )
      break;

    str_index = i3;
    break;
  }

  if ( str_index > 0 )
  {
    if ( point_value )
    {
      point_value->x = x;
      point_value->y = y;
      point_value->z = z;
    }
  }
  else
  {
    if ( !prx.ParseError() )
      prx = ON_ParseSettings::FalseSettings;
    if ( !pry.ParseError() )
      pry = ON_ParseSettings::FalseSettings;
    if ( !prz.ParseError() )
      prz = ON_ParseSettings::FalseSettings;
  }

  if ( parse_results )
  {
    *parse_results = (prx || pry || prz);
  }

  return str_index;
}
