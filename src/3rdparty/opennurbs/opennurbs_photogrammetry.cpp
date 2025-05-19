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

ON_AerialPhotoImage::ON_AerialPhotoImage()
: m_id(ON_nil_uuid)
, m_image_width_pixels(0)
, m_image_height_pixels(0)
{
}

void ON_AerialPhotoImage::Unset()
{
  m_name.Destroy();
  m_id = ON_nil_uuid;
  m_camera_position.Unset();
  m_image_frustum.Unset();
  m_image_file_name.Destroy();
  m_image_width_pixels = 0;
  m_image_height_pixels = 0;
}

void ON_AerialPhotoImage::SetName(
  const wchar_t* name
  )
{
  m_name = name;
}

void ON_AerialPhotoImage::GetName(
  ON_wString& name
  ) const
{
  name = m_name.Array();
}

void ON_AerialPhotoImage::SetId( ON_UUID id )
{
  m_id = id;
}

ON_UUID ON_AerialPhotoImage::Id() const
{
  return m_id;
}


bool ON_AerialPhotoImage::CameraPositionIsSet() const
{
  return m_camera_position.IsSet();
}

bool ON_AerialPhotoImage::CameraLocationIsSet() const
{
  return m_camera_position.LocationIsSet();
}

bool ON_AerialPhotoImage::CameraOrientationIsSet() const
{
  return m_camera_position.OrientationIsSet();
}


void ON_AerialPhotoImage::SetCameraPosition(
  ON_AerialPhotoCameraPosition camera_position
  )
{
  m_camera_position = camera_position;
}

void ON_AerialPhotoImage::GetCameraPosition(
  ON_AerialPhotoCameraPosition& camera_position
  ) const
{
  camera_position = m_camera_position;
}

void ON_AerialPhotoImage::UnsetCameraPosition()
{
  m_camera_position.Unset();
}
  
/////////////////////////////////////////////////////////
//
// Image frustum interface
//
bool ON_AerialPhotoImage::ImageFrustumIsSet() const
{
  return m_image_frustum.IsSet();
}

void ON_AerialPhotoImage::SetImageFrustum(
  ON_AerialPhotoImageFrustum image_frustum
  )
{
  m_image_frustum = image_frustum;
}

void ON_AerialPhotoImage::GetImageFrustum(
  ON_AerialPhotoImageFrustum& image_frustum
  ) const
{
  image_frustum = m_image_frustum;
}

void ON_AerialPhotoImage::UnsetImageFrustum()
{
  m_image_frustum.Unset();
}

bool ON_AerialPhotoImage::ImageFileNameIsSet() const
{
  return (m_image_file_name.Length() > 0);
}


bool ON_AerialPhotoImage::ImageSizeIsSet() const
{
  return (m_image_width_pixels > 0 && m_image_height_pixels > 0);
}

bool ON_AerialPhotoImage::SetImageSize(
  int image_width_pixels,
  int image_height_pixels
  )
{
  bool rc = false;
  if ( image_width_pixels > 0 && image_height_pixels > 0 )
  {
    m_image_width_pixels = image_width_pixels;
    m_image_height_pixels = image_height_pixels;
    rc = true;
  }
  else
    UnsetImageSize();

  return rc;
}


bool ON_AerialPhotoImage::GetImageSize(
  int* width_pixels,
  int* height_pixels
  ) const
{
  if ( 0 != width_pixels )
    *width_pixels = m_image_width_pixels;
  if ( 0 != height_pixels )
    *height_pixels = m_image_height_pixels;
  
  return ImageSizeIsSet();
}

void ON_AerialPhotoImage::UnsetImageSize()
{
  m_image_width_pixels = 0;
  m_image_height_pixels = 0;
}

void ON_AerialPhotoImage::SetImageFileName(
  const wchar_t* image_file_name
  )
{
  m_image_file_name = image_file_name;
}

void ON_AerialPhotoImage::GetImageFileName(
  ON_wString& image_file_name
  ) const
{
  // copy array
  const wchar_t* s = static_cast< const wchar_t* >(m_image_file_name);
  image_file_name = s;
}

void ON_AerialPhotoImage::UnsetImageFileName()
{
  m_image_file_name.Destroy();
}


ON_AerialPhotoImageFrustum::ON_AerialPhotoImageFrustum()
{
  Unset();
}

bool ON_AerialPhotoImageFrustum::IsSet() const
{
  return HeightIsSet() && CornersAreSet() && UnitSystemIsSet();
}

void ON_AerialPhotoImageFrustum::Unset()
{
  m_height = ON_UNSET_VALUE;
  m_corners[0] = ON_2dPoint::UnsetPoint;
  m_corners[1] = ON_2dPoint::UnsetPoint;
  m_corners[2] = ON_2dPoint::UnsetPoint;
  m_corners[3] = ON_2dPoint::UnsetPoint;
  m_unit_system = ON_UnitSystem::None;
}

bool ON_AerialPhotoImageFrustum::HeightIsSet() const
{
  return (m_height > 0.0 && ON_IsValid(m_height));
}

bool ON_AerialPhotoImageFrustum::CornersAreSet() const
{
  for(;;)
  {
    if ( !m_corners[0].IsValid() )
      break;
    if ( !m_corners[1].IsValid() )
      break;
    if ( !m_corners[2].IsValid() )
      break;
    if ( !m_corners[3].IsValid() )
      break;

    // corners must form a non-empty convex 2d region and
    // be in counter-clockwise order.  They can be a 
    // the corners of a 3 or 4 sided region.
    double max_z = 0.0;
    double z;
    ON_2dVector A, B;
    for ( int i = 0; i < 4; i++ )
    {
      A = m_corners[(i+3)%4] - m_corners[i];
      B = m_corners[(i+1)%4] - m_corners[i];
      z = B.x*A.y - A.x*B.y;
      if (z >= 0.0 && ON_IsValid(z))
      {
        if ( z > max_z )
          max_z = z;
        continue;
      }
      return false;
    }

    if ( max_z > 0.0 )
      return true;

    break;
  }

  return false;
}

bool ON_AerialPhotoImageFrustum::UnitSystemIsSet() const
{
  return (m_unit_system.IsSet());
}


ON_AerialPhotoCameraPosition::ON_AerialPhotoCameraPosition()
: m_status(0)
{
  Unset();
}

void ON_AerialPhotoCameraPosition::Unset()
{
  UnsetUnitSystem();
  UnsetLocation();
  UnsetOrientation();
}

bool ON_AerialPhotoCameraPosition::IsSet() const
{
  return UnitSystemIsSet() && LocationIsSet() && OrientationIsSet();
}


bool ON_AerialPhotoCameraPosition::UnitSystemIsSet() const
{
  return m_unit_system.IsSet();
}

bool ON_AerialPhotoCameraPosition::SetUnitSystem( ON::LengthUnitSystem unit_system )
{
  if (    ON::LengthUnitSystem::None != unit_system
       && ON::LengthUnitSystem::CustomUnits != unit_system
       && unit_system == ON::LengthUnitSystemFromUnsigned(static_cast<unsigned int>(unit_system))
     )
  {
    m_unit_system = ON_UnitSystem(unit_system);
  }
  else
    Unset();

  return UnitSystemIsSet();
}

bool ON_AerialPhotoCameraPosition::SetUnitSystem ( ON_UnitSystem unit_system )
{
  if ( unit_system.IsSet() )
    m_unit_system = unit_system;
  else
    Unset();

  return UnitSystemIsSet();
}

ON_UnitSystem ON_AerialPhotoCameraPosition::UnitSystem() const
{
  return m_unit_system;
}

bool ON_AerialPhotoCameraPosition::GetUnitSystem( ON_UnitSystem& unit_system ) const
{
  unit_system = m_unit_system;
  return UnitSystemIsSet();
}

void ON_AerialPhotoCameraPosition::UnsetUnitSystem()
{
  m_unit_system = ON_UnitSystem(ON::LengthUnitSystem::None);
}

bool ON_AerialPhotoCameraPosition::LocationIsSet() const
{
  return m_location.IsValid();
}

bool ON_AerialPhotoCameraPosition::SetLocation( 
  ON_3dPoint camera_location 
  )
{
  const bool rc = camera_location.IsValid();
  
  if (rc)
    m_location = camera_location;
  else
    UnsetLocation();

  return rc;
}

bool ON_AerialPhotoCameraPosition::GetLocation(
  ON_3dPoint& camera_location
  ) const
{
  camera_location = Location();
  return LocationIsSet();
}

ON_3dPoint ON_AerialPhotoCameraPosition::Location() const
{
  return m_location;
}

void ON_AerialPhotoCameraPosition::UnsetLocation()
{
  m_status &= 0xFE; // clear bit 1
  m_location = ON_3dPoint::UnsetPoint;
}

bool ON_AerialPhotoCameraPosition::OrientationIsSet() const
{
  return ( 0 != (m_status & 2) 
           && m_orientation_angles_radians.IsValid() 
           && m_orientation_angles_degrees.IsValid()
           && m_orientation_right.IsValid()
           && m_orientation_up.IsValid()
           && m_orientation_direction.IsValid()
           && m_orientation_rotation.IsValid()
         );
}

void ON_AerialPhotoCameraPosition::UnsetOrientation()
{
  m_status &= 0xFD; // clear bit 2

  m_orientation_angles_radians.Set(ON_UNSET_VALUE,ON_UNSET_VALUE,ON_UNSET_VALUE);
  m_orientation_angles_degrees.Set(ON_UNSET_VALUE,ON_UNSET_VALUE,ON_UNSET_VALUE);

  m_orientation_rotation = ON_Xform::Zero4x4;

  m_orientation_right = ON_3dVector::ZeroVector;
  m_orientation_up = ON_3dVector::ZeroVector;
  m_orientation_direction = ON_3dVector::ZeroVector;
}

bool ON_AerialPhotoCameraPosition::GetOrientationRotation(
  ON_Xform& camera_rotaion 
  ) const
{
  camera_rotaion = m_orientation_rotation;
  return (0 != (m_status & 2));
}

/*
Description:
  Get a right handed ortho normal camera frame.
Parameters:
  camera_X - [out]
    world coordinate unit vector pointing to the right in the camera image
    = OrientationRotation * (1,0,0)
  camera_Y - [out]
    world coordinate unit vector in the camera up direction.
    = OrientationRotation * (0,1,0)
  camera_Z - [out]
    world coordinate unit vector pointing into the camera (from the
    image toward the camera).
    = OrientationRotation * (0,0,1)
*/
bool ON_AerialPhotoCameraPosition::GetOrientationFrame(
  ON_3dVector& camera_X,
  ON_3dVector& camera_Y,
  ON_3dVector& camera_Z
  ) const
{
  camera_X.x = m_orientation_rotation.m_xform[0][0];
  camera_X.y = m_orientation_rotation.m_xform[1][0];
  camera_X.z = m_orientation_rotation.m_xform[2][0];

  camera_Y.x = m_orientation_rotation.m_xform[0][1];
  camera_Y.y = m_orientation_rotation.m_xform[1][1];
  camera_Y.z = m_orientation_rotation.m_xform[2][1];

  camera_Z.x = m_orientation_rotation.m_xform[0][2];
  camera_Z.y = m_orientation_rotation.m_xform[1][2];
  camera_Z.z = m_orientation_rotation.m_xform[2][2];

  return (0 != (m_status & 2));
}


ON_Xform ON_AerialPhotoCameraPosition::OrientationRotation() const
{
  return m_orientation_rotation;
}


bool ON_AerialPhotoCameraPosition::SetOrientationVectors(
    ON_3dVector camera_up,
    ON_3dVector camera_right,
    ON_3dVector camera_direction
    )
{
  ON_3dVector X(camera_right);
  ON_3dVector Y(camera_up);
  ON_3dVector Z(-camera_direction);

  bool bHaveX = ( X.IsValid() && X.Unitize() );
  bool bHaveY = ( Y.IsValid() && Y.Unitize() );
  bool bHaveZ = ( Z.IsValid() && Z.Unitize() );
  
  if ( !bHaveX && bHaveY && bHaveZ )
  {
    X = ON_CrossProduct(Y,Z);
    bHaveX = X.Unitize();
    if ( bHaveX )
      camera_right = X;
  }
  else if ( !bHaveY && bHaveZ && bHaveX )
  {
    Y = ON_CrossProduct(Z,X);
    bHaveY = Y.Unitize();
    if ( bHaveY )
      camera_up = Y;
  }
  else if ( !bHaveZ && bHaveX && bHaveY )
  {
    Z = ON_CrossProduct(X,Y);
    bHaveZ = Z.Unitize();
    if ( bHaveZ )
      camera_direction = -Z;
  }

  bool rc = false;
  for (;;)
  {
    if ( !bHaveX || !bHaveY || !bHaveZ )
      break;

    double max_dot = 0.0;
    double d = fabs(X*Y);
    if ( d > max_dot )
      max_dot = d;
    d = fabs(Y*Z);
    if ( d > max_dot )
      max_dot = d;
    d = fabs(Z*X);
    if ( d > max_dot )
      max_dot = d;

    if ( max_dot > 1.0e-8 )
      break;

    d = Z*ON_CrossProduct(X,Y);
    if ( !(d > 0.0) )
      break;

    ON_Xform R;
    R.m_xform[0][0] = X.x; R.m_xform[0][1] = Y.x; R.m_xform[0][2] = Z.x; R.m_xform[0][3] = 0.0;
    R.m_xform[1][0] = X.y; R.m_xform[1][1] = Y.y; R.m_xform[1][2] = Z.y; R.m_xform[1][3] = 0.0;
    R.m_xform[2][0] = X.z; R.m_xform[2][1] = Y.z; R.m_xform[2][2] = Z.z; R.m_xform[2][3] = 0.0;
    R.m_xform[3][0] = 0.0; R.m_xform[3][1] = 0.0; R.m_xform[3][2] = 0.0; R.m_xform[3][3] = 1.0;

    rc = SetOrientationRotation(R);

    if (rc)
    {
      // preserve exact values of input parameters
      m_orientation_right = camera_right;
      m_orientation_up = camera_up;
      m_orientation_direction = camera_direction;
    }

    break;
  }

  if (!rc)
  {
    UnsetOrientation();
  }

  return rc;
}

bool ON_AerialPhotoCameraPosition::SetOrientationRotation(
    ON_Xform camera_rotation
    )
{
  m_orientation_rotation = camera_rotation;

  const ON_3dVector X(camera_rotation.m_xform[0][0],camera_rotation.m_xform[1][0],camera_rotation.m_xform[2][0]);
  const ON_3dVector Y(camera_rotation.m_xform[0][1],camera_rotation.m_xform[1][1],camera_rotation.m_xform[2][1]);
  const ON_3dVector Z(camera_rotation.m_xform[0][2],camera_rotation.m_xform[1][2],camera_rotation.m_xform[2][2]);

  m_orientation_right = X;
  m_orientation_up = Y;
  m_orientation_direction = -Z;

  double s1, c1, s2, c2, s3, c3;

  s2 = Z.x;
  double a = 1.0 - s2*s2;
  c2 = (a > 0.0) ? sqrt(a) : 0.0;
  if ( fabs(c2) <= ON_EPSILON || fabs(s2) >= 1.0-ON_EPSILON )
  {
    s2 = (s2 < 0.0) ? -1.0 : 1.0;
    c2 = 0.0;
  }
  else if ( fabs(s2) <= ON_EPSILON || fabs(c2) >= 1.0-ON_EPSILON )
  {
    c2 = (c2 < 0.0) ? -1.0 : 1.0;
    s2 = 0.0;
  }

  if ( c2 > 0.0 )
  {
    s1 = -Z.y/c2;
    c1 =  Z.z/c2;
    s3 = -Y.x/c2;
    c3 =  X.x/c2;
  }
  else
  {
    s1 = 0.0;
    c1 = 1.0;
    s3 = ( X.y ==  Y.z ) ? X.y : 0.5*(X.y + Y.z);
    c3 = ( Y.y == -X.z ) ? Y.y : 0.5*(Y.y - X.z);
  }

  m_orientation_angles_radians.x = atan2(s1,c1);
  m_orientation_angles_radians.y = atan2(s2,c2);
  m_orientation_angles_radians.z = atan2(s2,c3);

  m_orientation_angles_degrees.x = m_orientation_angles_radians.x*180.0/ON_PI;
  m_orientation_angles_degrees.y = m_orientation_angles_radians.y*180.0/ON_PI;
  m_orientation_angles_degrees.z = m_orientation_angles_radians.z*180.0/ON_PI;

  m_status |= 2;

  return true;
}

bool ON_AerialPhotoCameraPosition::SetOrientationAnglesDegrees(
    double omega_degrees, 
    double phi_degrees, 
    double kappa_degrees
    )
{
  bool rc = false;
  if ( ON_IsValid(omega_degrees) && ON_IsValid(phi_degrees) && ON_IsValid(kappa_degrees) )
  {
    rc = SetOrientationAnglesRadians(omega_degrees*ON_PI/180.0,phi_degrees*ON_PI/180.0,kappa_degrees*ON_PI/180.0);
    // Directly set m_camera_angles_degrees after SetCameraAnglesRadians()
    // so we don't loose a few bits of precision lost by converting to radians
    // and then converting back to degrees.
    m_orientation_angles_degrees.Set(omega_degrees,phi_degrees,kappa_degrees);
  }
  else
  {
    UnsetOrientation();
  }
  return rc;
}

bool ON_AerialPhotoCameraPosition::SetOrientationAnglesRadians(
    double omega_radians, 
    double phi_radians, 
    double kappa_radians
    )
{
  bool rc = false;

  if ( ON_IsValid(omega_radians) && ON_IsValid(phi_radians) && ON_IsValid(kappa_radians) )
  {
    m_orientation_angles_radians.Set(omega_radians,phi_radians,kappa_radians);
    m_orientation_angles_degrees.Set(omega_radians*180.0/ON_PI,phi_radians*180.0/ON_PI,kappa_radians*180.0/ON_PI);

    const double c1 = cos(omega_radians);
    const double s1 = sin(omega_radians);
  
    const double c2 = cos(phi_radians);
    const double s2 = sin(phi_radians);
  
    const double c3 = cos(kappa_radians);
    const double s3 = sin(kappa_radians);

    const ON_3dVector X( c3*c2,  s3*c1 + c3*s2*s1,  s3*s1 - c3*s2*c1);
    const ON_3dVector Y(-s3*c2,  c3*c1 - s3*s2*s1,  c3*s1 + s3*s2*c1);
    const ON_3dVector Z(    s2,            -c2*s1,             c2*c1);

    ON_Xform R;
    R.m_xform[0][0] = X.x; R.m_xform[0][1] = Y.x; R.m_xform[0][2] = Z.x; R.m_xform[0][3] = 0.0;
    R.m_xform[1][0] = X.y; R.m_xform[1][1] = Y.y; R.m_xform[1][2] = Z.y; R.m_xform[1][3] = 0.0;
    R.m_xform[2][0] = X.z; R.m_xform[2][1] = Y.z; R.m_xform[2][2] = Z.z; R.m_xform[2][3] = 0.0;
    R.m_xform[3][0] = 0.0; R.m_xform[3][1] = 0.0; R.m_xform[3][2] = 0.0; R.m_xform[3][3] = 1.0;

    m_orientation_rotation = R;

    m_orientation_right = X;
    m_orientation_up = Y;
    m_orientation_direction = -Z;

    m_status |= 2;

    rc = true;

    {
      // Debugging validation tests

      const ON_3dVector x0(1.0,0.0,0.0);
      const ON_3dVector y0(0.0,1.0,0.0);
      const ON_3dVector z0(0.0,0.0,1.0);

      const ON_3dVector x1 = x0;
      const ON_3dVector y1 =  c1*y0 + s1*z0;
      const ON_3dVector z1 = -s1*y0 + c1*z0;

      const ON_3dVector y2 = y1;
      const ON_3dVector z2 = s2*x1 + c2*z1;
      const ON_3dVector x2 = c2*x1 - s2*z1;

      const ON_3dVector z3 =  z2;
      const ON_3dVector x3 =  c3*x2 + s3*y2;
      const ON_3dVector y3 = -s3*x2 + c3*y2;

      /*
      const ON_3dVector x1 = x0;
      const ON_3dVector y1 = (0.0,  c1,  s1);
      const ON_3dVector z1 = (0.0, -s1,  c1);

      const ON_3dVector x2 = (c2,  s2*s1, -s2*c1); // c2*x1 - s2*z1;
      const ON_3dVector y2 = (0.0,    c1,     s1);
      const ON_3dVector z2 = (s2, -c2*s1,  c2*c1); // s2*x1 + c2*z1
      */


      ON_Xform r1;
      r1.Rotation(omega_radians,x0,ON_3dPoint::Origin);
      ON_3dVector r1y0 = r1*y0;

      ON_Xform r2;
      r2.Rotation(phi_radians,r1y0,ON_3dPoint::Origin);
      ON_3dVector r2r1z0 = r2*r1*z0;

      ON_Xform r3;
      r3.Rotation(kappa_radians,r2r1z0,ON_3dPoint::Origin);

      ON_Xform r321 = r3*r2*r1;


      ON_Xform zero = r321 - R;

      double a, b;
      double max_zero = 0.0;
      for ( int i = 0; i < 4; i++ ) for ( int j = 0; j < 4; j++ )
      {
        a = fabs(zero[i][j]);
        if (a > max_zero )
          max_zero = a;
      }
      b = fabs((x3-X).MaximumCoordinate());
      if ( b > max_zero )
        max_zero = b;
      b = fabs((y3-Y).MaximumCoordinate());
      if ( b > max_zero )
        max_zero = b;
      b = fabs((z3-Z).MaximumCoordinate());
      if ( b > max_zero )
        max_zero = b;


      if ( max_zero > 1.0e-15 )
        ON_ERROR("Transform trauma");
    }
  }
  else
  {
    UnsetOrientation();
  }

  return rc;
}

bool ON_AerialPhotoImage::GetViewProjection( 
  ON_BoundingBox target_bbox,
  ON_Viewport& viewport
  ) const
{
  viewport = ON_Viewport::DefaultTopViewYUp;

  if ( !this->ImageSizeIsSet() )
    return false;

  const int image_width_pixels   = m_image_width_pixels;
  const int image_height_pixels = m_image_height_pixels;

  const ON_AerialPhotoImageFrustum& pg_if( m_image_frustum );
  if ( !pg_if.IsSet() )
    return false;

  const ON_AerialPhotoCameraPosition& pg_cp( m_camera_position );
  if ( !pg_cp.LocationIsSet() )
    return false;
  if ( !pg_cp.OrientationIsSet() )
    return false;

  ON_3dPoint camera_location;
  if ( !pg_cp.GetLocation(camera_location) || !camera_location.IsValid() )
    return false;

  ON_Xform camera_rotation;
  if (    !pg_cp.GetOrientationRotation(camera_rotation) 
       || !camera_rotation.IsValid() 
     )
    return false;

  ON_Plane camera_plane;
  if (!pg_cp.GetOrientationFrame(camera_plane.xaxis,camera_plane.yaxis,camera_plane.zaxis))
    return false;
  camera_plane.origin = camera_location;
  camera_plane.UpdateEquation();

  const double frustum_to_position_unit_scale = ON::UnitScale( pg_if.m_unit_system, pg_cp.UnitSystem() );
  if (    !ON_IsValid(frustum_to_position_unit_scale) 
       || !(frustum_to_position_unit_scale > 0.0) 
     )
    return false;

  // The values of frus_near and frus_far are adjusted later
  // so the view's frustum contains the region in target_bbox.

  double frus_near = pg_if.m_height*frustum_to_position_unit_scale;
  if ( !ON_IsValid(frus_near) || !(frus_near > 0.0) )
    return false;

  double frus_far = 128.0*frus_near; 

  double frus_left, frus_right;
  double frus_bottom, frus_top;
  frus_left = frus_right = pg_if.m_corners[0].x;
  frus_bottom = frus_top = pg_if.m_corners[0].y;
  for ( size_t i = 1; i < sizeof(pg_if.m_corners)/sizeof(pg_if.m_corners[0]); i++ )
  {
    if ( pg_if.m_corners[i].x < frus_left )
      frus_left = pg_if.m_corners[i].x;
    else if ( pg_if.m_corners[i].x > frus_right )
      frus_right = pg_if.m_corners[i].x;
    if ( pg_if.m_corners[i].y < frus_bottom )
      frus_bottom = pg_if.m_corners[i].y;
    else if ( pg_if.m_corners[i].y > frus_top )
      frus_top = pg_if.m_corners[i].y;
  }
  frus_left   *= frustum_to_position_unit_scale;
  frus_right  *= frustum_to_position_unit_scale;
  frus_bottom *= frustum_to_position_unit_scale;
  frus_top    *= frustum_to_position_unit_scale;
  
  bool rc = false;

  ON_Viewport vp;
  for(;;)
  {
    if ( !vp.SetProjection( ON::perspective_view ) )
      break;
  
    if ( !vp.SetCameraLocation( pg_cp.Location() ) )
      break;
  
    if ( !vp.SetCameraDirection( -camera_plane.zaxis ) )
      break;
  
    if ( !vp.SetCameraUp( camera_plane.yaxis ) )
      break;

    if ( !vp.SetFrustum(frus_left,frus_right,frus_bottom,frus_top,frus_near,frus_far) )
      break;
    
    if ( !vp.SetScreenPort(0,image_width_pixels,0,image_height_pixels) )
      break;

    double bbox_near = ON_UNSET_VALUE;
    double bbox_far  = ON_UNSET_VALUE;
    if ( vp.GetBoundingBoxDepth(target_bbox,&bbox_near,&bbox_far,false) )
    {
      if ( frus_near > 0.0 && ON_IsValid(bbox_near) && frus_near < bbox_near )
      {
        double s = 1.0;
        while ( 2.0*s*frus_near <= bbox_near )
          s *= 2.0;

        if ( s >= 2.0 )
        {
          frus_near   *= s;
          frus_left   *= s;
          frus_right  *= s;
          frus_bottom *= s;
          frus_top    *= s;
          frus_far = 1.0625*frus_near;
        }
      }
            
      if ( ON_IsValid(bbox_far) && frus_far < bbox_far )
      {
        frus_far = 1.0625*bbox_far;
        const double max_frus_far = 67108864.0*frus_near; // 2^26 * frus_near
        if ( !(frus_far <= max_frus_far) )
          frus_far = max_frus_far;
      }

      if ( !vp.SetFrustum(frus_left,frus_right,frus_bottom,frus_top,frus_near,frus_far) )
        break;
    }

    rc = vp.IsValid() ? true : false;
    if ( rc )
      viewport = vp;

    break;
  }

  return rc;
}
