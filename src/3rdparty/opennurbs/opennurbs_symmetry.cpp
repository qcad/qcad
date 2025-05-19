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

ON_Symmetry::Type ON_Symmetry::SymmetryTypeFromUnsigned(unsigned int symmetry_type_as_unsigned)
{
  switch (symmetry_type_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Symmetry::Type::Unset);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Symmetry::Type::Reflect);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Symmetry::Type::Rotate);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Symmetry::Type::ReflectAndRotate);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Symmetry::Type::Inversion);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Symmetry::Type::Cyclic);
  }

  ON_ERROR("Invalid type_as_unsigned parameter");
  return ON_Symmetry::Type::Unset;
}

const ON_wString ON_Symmetry::SymmetryTypeToString(ON_Symmetry::Type symmetry_type)
{
  const wchar_t* s;
  switch (symmetry_type)
  {
  case ON_Symmetry::Type::Unset:
    s = L"Unset";
    break;
  case ON_Symmetry::Type::Reflect:
    s = L"Reflect";
    break;
  break;  case ON_Symmetry::Type::Rotate:
    s = L"Rotate";
    break;
  case ON_Symmetry::Type::ReflectAndRotate:
    s = L"ReflectAndRotate";
    break;
  case ON_Symmetry::Type::Inversion:
    s = L"Inversion";
    break;
  case ON_Symmetry::Type::Cyclic:
    s = L"Cyclic";
    break;
  default:
    s = nullptr;
    break;
  }
  return ON_wString(s);
}

ON_Symmetry::Region ON_Symmetry::SymmetryRegionFromUnsigned(unsigned int region_as_unsigned)
{
  switch (region_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Symmetry::Region::Unset);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Symmetry::Region::AboveReflectionPlane);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Symmetry::Region::OnRotationAxis);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Symmetry::Region::OnReflectionPlane);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Symmetry::Region::CrossesReflectionPlane);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Symmetry::Region::BelowReflectionPlane);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Symmetry::Region::OffRotationAxis);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Symmetry::Region::OnReflectionHalfPlane);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Symmetry::Region::OnSupplementalHalfPlane);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Symmetry::Region::OnRotateAndReflectHalfPlane);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Symmetry::Region::InsideRotateAndReflect);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Symmetry::Region::OutsideRotateAndReflect);
  }

  ON_ERROR("Invalid region_as_unsigned parameter");
  return ON_Symmetry::Region::Unset;
}


const ON_wString SymmetryRegionToString(ON_Symmetry::Region r)
{
  switch (r)
  {
  case ON_Symmetry::Region::Unset:
    return ON_wString(L"Unset");
    break;
  case ON_Symmetry::Region::AboveReflectionPlane:
    return ON_wString(L"AboveReflectionPlane");
    break;
  case ON_Symmetry::Region::OnRotationAxis:
    return ON_wString(L"OnRotationAxis");
    break;
  case ON_Symmetry::Region::OffRotationAxis:
    return ON_wString(L"OffRotationAxis");
    break;
  case ON_Symmetry::Region::OnReflectionPlane:
    return ON_wString(L"OnReflectionPlane");
    break;
  case ON_Symmetry::Region::CrossesReflectionPlane:
    return ON_wString(L"CrossesReflectionPlane");
    break;
  case ON_Symmetry::Region::BelowReflectionPlane:
    return ON_wString(L"BelowReflectionPlane");
    break;
  case ON_Symmetry::Region::OnReflectionHalfPlane:
    return ON_wString(L"OnReflectionHalfPlane");
    break;
  case ON_Symmetry::Region::OnSupplementalHalfPlane:
    return ON_wString(L"OnSupplementalHalfPlane");
    break;
  case ON_Symmetry::Region::OnRotateAndReflectHalfPlane:
    return ON_wString(L"OnRotateAndReflectHalfPlane");
    break;
  case ON_Symmetry::Region::InsideRotateAndReflect:
    return ON_wString(L"InsideRotateAndReflect");
    break;
  case ON_Symmetry::Region::OutsideRotateAndReflect:
    return ON_wString(L"OutsideRotateAndReflect");
    break;
  }
  return ON_wString::EmptyString;
}

ON_Symmetry::Region ON_Symmetry::PointRegion(ON_3dPoint point, bool bUseCleanupTolerance) const
{
  for(;;)
  {
    if (false == point.IsValid())
      break;

    const double tol = bUseCleanupTolerance ? CleanupTolerance() : ON_Symmetry::ZeroTolerance;
    if (false == ON_IsValid(tol))
      break;

    double h[2];
    switch (m_type)
    {
    case ON_Symmetry::Type::Reflect:
      h[0] = ReflectionPlane().ValueAt(point);
      if (h[0] < -tol)
        return ON_Symmetry::Region::BelowReflectionPlane;
      if (h[0] <= tol)
        return ON_Symmetry::Region::OnReflectionPlane;
      if (h[0] > tol)
        return ON_Symmetry::Region::AboveReflectionPlane;

      // ... else nans
      break;

    case ON_Symmetry::Type::Rotate:
    {
      const ON_Line axis = RotationAxis();
      const ON_3dPoint A = axis.ClosestPointTo(point);
      const double d = fabs((point - A).MaximumCoordinate());
      if (d <= tol)
        return ON_Symmetry::Region::OnRotationAxis;
      if (d > tol)
        return ON_Symmetry::Region::OffRotationAxis;

      // ... else nans
    }
    break;

    case ON_Symmetry::Type::ReflectAndRotate:
    {
      const ON_Line axis = RotationAxis();
      const ON_3dPoint A = axis.ClosestPointTo(point);
      const double d = fabs((point - A).MaximumCoordinate());
      if (d <= tol)
        return ON_Symmetry::Region::OnRotationAxis;

      const ON_PlaneEquation M = ReflectAndRotatePlane(0); // reflection plane
      const ON_PlaneEquation S = ReflectAndRotatePlane(1); // supplental plane
      h[0] = M.ValueAt(point);
      h[1] = S.ValueAt(point);
      if (h[0] > tol && h[1] > tol)
        return ON_Symmetry::Region::InsideRotateAndReflect;
      if (fabs(h[0]) <= tol && fabs(h[0]) <= fabs(h[1]))
      {
        return (h[1] >= 0.0) ? ON_Symmetry::Region::OnReflectionHalfPlane : ON_Symmetry::Region::OnRotateAndReflectHalfPlane;
      }
      if (fabs(h[1]) <= tol)
      {
        return (h[0] >= 0.0) ? ON_Symmetry::Region::OnSupplementalHalfPlane : ON_Symmetry::Region::OnRotateAndReflectHalfPlane;
      }

      if (h[0] == h[0] && h[1] == h[1])
      {
        const ON_Xform R = this->RotationTransformation();
        const unsigned Rcount = this->RotationCount();
        for (unsigned i = 0; i < Rcount; ++i)
        {
          point = R * point;
          h[0] = S.ValueAt(point);
          if (fabs(h[0]) <= tol)
            return ON_Symmetry::Region::OnRotateAndReflectHalfPlane;
          h[0] = M.ValueAt(point);
          if (fabs(h[0]) <= tol)
            return ON_Symmetry::Region::OnRotateAndReflectHalfPlane;
        }
        return ON_Symmetry::Region::OutsideRotateAndReflect;
      }
      

      // ... else nans
    }
    break;

    default:
      break;
    }

    break;
  }

  // When the point is not valid, the symmetry is not set, or an evaluation produces nans, then return ON_Symmetry::Region::Unset.
  return ON_Symmetry::Region::Unset; 
}

bool ON_Symmetry::SymmetryRegionHasFixedPoints(ON_Symmetry::Region symmetry_region)
{
  return
    ON_Symmetry::Region::OnRotationAxis == symmetry_region
    || ON_Symmetry::Region::OnReflectionPlane == symmetry_region
    || ON_Symmetry::Region::OnReflectionHalfPlane == symmetry_region
    || ON_Symmetry::Region::OnSupplementalHalfPlane == symmetry_region
    || ON_Symmetry::Region::OnRotateAndReflectHalfPlane == symmetry_region
    ;
}

ON_Symmetry::Coordinates ON_Symmetry::SymmetryCoordinatesFromUnsigned(unsigned int symmetry_coordinates_as_unsigned)
{
  switch (symmetry_coordinates_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Symmetry::Coordinates::Unset);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Symmetry::Coordinates::Object);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Symmetry::Coordinates::World);
  }

  ON_ERROR("Invalid symmetry_coordinates_as_unsigned parameter");
  return ON_Symmetry::Coordinates::Unset;
}

const ON_wString ON_Symmetry::SymmetryCoordinatesToString(ON_Symmetry::Coordinates symmetry_coordinates)
{
  const wchar_t* s;
  switch (symmetry_coordinates)
  {
  case ON_Symmetry::Coordinates::Unset:
    s = L"Unset";
    break;
  case ON_Symmetry::Coordinates::Object:
    s = L"Object";
    break;
  case ON_Symmetry::Coordinates::World:
    s = L"World";
    break;
  default:
    s = nullptr;
    break;
  }
  return ON_wString(s);
}

bool ON_Symmetry::Write(ON_BinaryArchive& archive) const
{
  if (false == archive.BeginWrite3dmAnonymousChunk(4))
    return false;

  bool rc = false;
  for (;;)
  {
    const ON_Symmetry::Type symmetry_type = IsSet() ? SymmetryType() : ON_Symmetry::Type::Unset;
    const unsigned char utype = static_cast<unsigned char>(symmetry_type);
    if (false == archive.WriteChar(utype))
      break;
    if (ON_Symmetry::Type::Unset ==  symmetry_type)
    {
      rc = true;
      break;
    }
    if (false == archive.WriteInt(m_inversion_order))
      break;
    if (false == archive.WriteInt(m_cyclic_order))
      break;
    if (false == archive.WriteUuid(m_id))
      break;

    if (archive.BeginWrite3dmAnonymousChunk(3))
    {
      switch (m_type)
      {
      case ON_Symmetry::Type::Unset:
        break;
      case ON_Symmetry::Type::Reflect:
        rc = archive.WritePlaneEquation(m_fixed_plane);
        break;
      case ON_Symmetry::Type::Rotate:
        // The plane is written but not read so the files saved afeter June 15, 2021 
        // can be read by code compiled before June 15, 2021.
        rc = archive.WriteLine(m_rotation_axis) && archive.WritePlaneEquation(ON_PlaneEquation::NanPlaneEquation);
        break;
      case ON_Symmetry::Type::ReflectAndRotate:
        rc = archive.WritePlaneEquation(m_fixed_plane) && archive.WriteLine(m_rotation_axis);
        break;
      case ON_Symmetry::Type::Inversion:
        // fixed plane added for chunk version >= 2
        rc = archive.WriteXform(m_inversion_transform) && archive.WritePlaneEquation(m_fixed_plane);
        break;
      case ON_Symmetry::Type::Cyclic:
        // fixed plane added for chunk version >= 2
        rc = archive.WriteXform(m_cyclic_transform) && archive.WritePlaneEquation(m_fixed_plane);
        break;
      default:
        ON_ERROR("You added a new enum value but failed to update archive IO code.");
        break;
      }
      if (false == archive.EndWrite3dmChunk())
        rc = false;
    }

    // ON_Symmetry::Coordinates added Dec 16, 2019 chunk version 2
    const ON_Symmetry::Coordinates symmetry_coordinates = IsSet() ? SymmetryCoordinates() : ON_Symmetry::Coordinates::Unset;
    const unsigned char ucoordinates = static_cast<unsigned char>(symmetry_coordinates);
    if (false == archive.WriteChar(ucoordinates))
      break;

    // m_symmetric_object_content_serial_number added Feb 11, 2020 chunk version 3
    if ( false == archive.WriteBigInt(this->m_symmetric_object_content_serial_number) )
      break;

    // m_symmetric_object_topology_hash added March 29, 2021 chunk version 4
    if (false == this->m_symmetric_object_topology_hash.Write(archive))
      break;
    // m_symmetric_object_geometry_hash added March 29, 2021 chunk version 4
    if (false == this->m_symmetric_object_geometry_hash.Write(archive))
      break;

    rc = true;
    break;
  }
  if (false == archive.EndWrite3dmChunk())
    rc = false;
  return rc;
}

bool ON_Symmetry::IsValidCyclicTranformation(
  ON_Xform transformation,
  unsigned transformation_order
)
{
  if (transformation_order < 2)
    return false;
  if (transformation_order > ON_Symmetry::MaximumOrder)
    return false;
  if (false == transformation.IsValid())
    return false;

  // In the comments below, 
  //   I = identity transformation,
  //   n = transformation_order, 
  //   T = transformation.
  // 
  // 
  // Verify I = T^n, I != T^i when i<n, and calculate some fixed points F[].
  ON_Xform x = transformation;
  ON_Xform y = transformation;
  ON_Xform A = ON_Xform::IdentityTransformation;
  ON_Xform B = ON_Xform::IdentityTransformation;
  for (unsigned j = 1; j < transformation_order; ++j)
  {
    // Here, x = T^j, y = T^j and 1 <= j < n
    if (x.IsIdentity(ON_Symmetry::ZeroTolerance))
      return false; // transformation_order is too small or transformation is unstable
    if (y.IsIdentity(ON_Symmetry::ZeroTolerance))
      return false; // transformation_order is too small or transformation is unstable
    A = A + x;
    B = B + y;
    x = x * transformation; // x = transformation^(j+1)
    y = transformation * y; // y = transformation^(j+1)
  }
  if (false == x.IsIdentity(ON_Symmetry::ZeroTolerance))
    return false; // transformation_order is too large or transformation is unstable
  if (false == y.IsIdentity(ON_Symmetry::ZeroTolerance))
    return false; // transformation_order is too large or transformation is unstable

  const ON_Xform ZA = A - A * transformation;
  if (false == ZA.IsZero4x4(ON_Symmetry::ZeroTolerance))
    return false;

  const ON_Xform ZB = B - transformation * B;
  if (false == ZB.IsZero4x4(ON_Symmetry::ZeroTolerance))
    return false;

  return true;
}

bool ON_Symmetry::IsValidFixedPlane(ON_Xform transformation, ON_PlaneEquation fixed_plane)
{
  if (false == fixed_plane.IsSet())
    return false;

  if (false == transformation.IsValid())
    return false;

  // Get a scattering of points on the plane.
  const ON_3dPoint P[]{
    fixed_plane.ClosestPointTo(ON_3dPoint(0,0,0)),
    fixed_plane.ClosestPointTo(ON_3dPoint(1,0,0)),
    fixed_plane.ClosestPointTo(ON_3dPoint(0,1,0)),
    fixed_plane.ClosestPointTo(ON_3dPoint(0,0,1)),
    fixed_plane.ClosestPointTo(ON_3dPoint(1,1,0)),
    fixed_plane.ClosestPointTo(ON_3dPoint(0,1,1)),
    fixed_plane.ClosestPointTo(ON_3dPoint(1,0,1)),
    fixed_plane.ClosestPointTo(ON_3dPoint(1,1,1))
  };
  const size_t Pcount = sizeof(P) / sizeof(P[0]);

  // Test both fixed_plane and a unitized version
  const ON_PlaneEquation e = fixed_plane.UnitizedPlaneEquation();
  double maxd = 0.0;
  for (size_t i = 0; i < Pcount && maxd <= ON_Symmetry::ZeroTolerance; ++i)
  {
    const double d0 = fabs(fixed_plane.ValueAt(P[i]));
    if (d0 > maxd)
      maxd = d0;
    else if (d0 != d0)
      maxd = ON_DBL_QNAN;

    const double d1 = fabs(e.ValueAt(P[i]));
    if (d1 > maxd)
      maxd = d1;
    else if (d1 != d1)
      maxd = ON_DBL_QNAN;

    const ON_3dPoint Q = transformation * P[i];
    const double d2 = (P[i] - Q).MaximumCoordinate();
    if (d2 > maxd)
      maxd = d2;
    else if (d2 != d2)
      maxd = ON_DBL_QNAN;
  }

  return maxd <= ON_Symmetry::ZeroTolerance;

}

bool ON_Symmetry::IsValidReflectionTranformationAndFixedPlane(ON_Xform reflection, ON_PlaneEquation reflection_plane)
{
  return ON_Symmetry::IsValidCyclicTranformation(reflection, 2) && ON_Symmetry::IsValidFixedPlane(reflection, reflection_plane);
}

bool ON_Symmetry::IsMotifBoundarySubDVertex(const class ON_SubDVertex* v, bool bUseCleanupTolerance) const
{
  if (nullptr == v)
    return false;
  if (false == v->IsCreaseOrCorner())
    return false;

  const ON_Symmetry::Type symmetry_type = this->SymmetryType();
  if (false == v->HasBoundaryVertexTopology())
  {
    switch (symmetry_type)
    {
    case ON_Symmetry::Type::Reflect:
      return false; // easy case.
      break;

    case ON_Symmetry::Type::Rotate:
      if (v->HasInteriorVertexTopology())
        return false;
      if (ON_SubDVertexTag::Corner != v->m_vertex_tag)
        return false;
      // We have to keep nonmanifold corners - RH-63789
      break;

    case ON_Symmetry::Type::ReflectAndRotate:
      return false; 

    default:
      return false;
      break;
    }
  }

  const ON_3dPoint P = v->ControlNetPoint();
  const double tol = bUseCleanupTolerance ? this->CleanupTolerance() : ON_Symmetry::ZeroTolerance;
  
  switch (symmetry_type)
  {
  case ON_Symmetry::Type::Reflect:
  {
    const double d = fabs(this->ReflectionPlane().ValueAt(P));
    return (d <= tol);
  }
  break;

  case ON_Symmetry::Type::Rotate:
    // All boundary vertices must be eligible for joining.
    // The pinwheel motifs in RH-63376 shows why.
    return true;
    break;

  case ON_Symmetry::Type::ReflectAndRotate:
    // The ReflectAndRotatePlane(2) test makes sure we are in the correct half space
    // where the ReflectAndRotate reflection plane is active.
    if ( this->ReflectAndRotatePlane(2).ValueAt(P) >= -tol )
    {
      // The d0 test is correct for certain
      const double d0 = fabs(this->ReflectAndRotatePlane(0).ValueAt(P));
      if (d0 <= tol)
        return true;

      // The d1 test is probably correct
      const double d1 = fabs(this->ReflectAndRotatePlane(1).ValueAt(P));
      if (d1 <= tol)
        return true;
    }
    break;

  default:
    break;
  }

  return false;
}

bool ON_Symmetry::IsFixedSubDComponent(
  const class ON_SubDComponentPtr& subd_component,
  bool bUseCleanupTolerance
) const
{
  const unsigned motif_count = this->MotifCount();
  if (motif_count < 2 || motif_count > ON_Symmetry::MaximumOrder)
    return false;

  const ON_SubDVertex* v = nullptr;
  const ON_SubDEdge* e = nullptr;
  const ON_SubDFace* f = nullptr;
  ON_3dPoint C = ON_3dPoint::NanPoint;

  switch (subd_component.ComponentType())
  {
  case ON_SubDComponentPtr::Type::Vertex:
    v = subd_component.Vertex();
    if (nullptr != v)
      C = v->ControlNetPoint();
    break;

  case ON_SubDComponentPtr::Type::Edge:
    e = subd_component.Edge();
    if (nullptr != e)
      C = e->ControlNetCenterPoint();
    break;

  case ON_SubDComponentPtr::Type::Face:
    f = subd_component.Face();
    if (nullptr != f)
      C = f->ControlNetCenterPoint();
    break;

  default:
    break;
  }

  if (false == C.IsValid())
    return false;

  const double dtol = bUseCleanupTolerance ? this->CleanupTolerance() : ON_Symmetry::ZeroTolerance;
  // quick test of center point
  double d = C.DistanceTo(this->MotifTransformation(1) * C);
  if (false == (d <= dtol))
    return false;

  ON_SimpleArray<ON_3dPoint> P(nullptr != f ? f->EdgeCount() : 2U);
  if (nullptr != f)
  {
    for (unsigned short fvi = 0; fvi < f->m_edge_count; ++fvi)
      P.Append(f->ControlNetPoint(fvi));
  }
  else if (nullptr != e)
  {
    P.Append(e->ControlNetPoint(0));
    P.Append(e->ControlNetPoint(1));
  }
  else if (nullptr != v)
  {
    P.Append(C);
  }

  const unsigned Pcount = P.UnsignedCount();
  ON_SimpleArray<bool> hit_array(Pcount);
  hit_array.SetCount(Pcount);
  bool* bHit = hit_array.Array();

  for (unsigned j = 1; j < motif_count; ++j)
  {
    const ON_Xform& motif_xform = this->MotifTransformation(j);
    hit_array.Zero();
    unsigned hit_count = 0;
    for (unsigned i = 0; i < Pcount; ++i)
    {
      const ON_3dPoint Q = motif_xform * P[i];
      for (unsigned k = 0; k < Pcount; ++k)
      {
        if (false == bHit[k])
        {
          d = Q.DistanceTo(P[k]);
          if (d <= dtol)
          {
            bHit[k] = true;
            ++hit_count;
          }
        }
      }
    }
    if (hit_count != Pcount)
      return false;
  }

  return true;
}

bool ON_Symmetry::IsValidRotationAxis(
  ON_Line rotation_axis,
  unsigned int rotation_count
)
{
  for (;;)
  {
    if (rotation_count < 2)
      break;
    if (rotation_count > ON_Symmetry::MaximumOrder)
      break;
    if (false == rotation_axis.IsValid())
      break;
    if (false == (rotation_axis.Length() > ON_Symmetry::ZeroTolerance))
      break;

    // Make sure a unitized axis can be reliably used for evaluations.
    const ON_Line unit_axis(rotation_axis.from, rotation_axis.from + rotation_axis.Tangent());
    if (false == unit_axis.IsValid())
      break;
    const double d0 = unit_axis.DistanceTo(rotation_axis.to);
    if (false == (d0 <= ON_Symmetry::ZeroTolerance))
      break;
    const double d1 = rotation_axis.DistanceTo(unit_axis.to);
    if (false == (d1 <= ON_Symmetry::ZeroTolerance))
      break;

    return true;
  }

  return false;
}

bool ON_Symmetry::IsValidRotationAxisAndFixedPlane(
  ON_Line rotation_axis,
  unsigned int rotation_count,
  ON_PlaneEquation fixed_plane
)
{
  for (;;)
  {
    if (rotation_count < 2)
      return false;
    if (rotation_count > ON_Symmetry::MaximumOrder)
      return false;
    if (false == rotation_axis.IsValid())
      break;
    if (false == (rotation_axis.Length() > ON_Symmetry::ZeroTolerance))
      break;

    if (false == fixed_plane.IsSet())
      break;
    
    // Test both fixed_plane and a unitized version just in case
    // fixed_plane has a very short (x,y,z) part. 
    // The idea of all symmetry validation is to prohibit getting
    // started with any sort of garbage input.
    const ON_PlaneEquation e = fixed_plane.UnitizedPlaneEquation();
    const double h[] =
    {
      fixed_plane.ValueAt(rotation_axis.from),
      fixed_plane.ValueAt(rotation_axis.to),
      e.ValueAt(rotation_axis.from),
      e.ValueAt(rotation_axis.to)
    };
    
    double maxd = 0.0;
    for (size_t i = 0; i < sizeof(h)/sizeof(h[0]) && maxd <= ON_Symmetry::ZeroTolerance; ++i)
    {
      const double d = fabs(h[i]);
      if (d > maxd)
        maxd = d;
      else if (d != d)
        maxd = ON_DBL_QNAN;
    }
    if (maxd <= ON_Symmetry::ZeroTolerance)
      return true;

    // The rotation axis must lie in the fixed plane.
    break;
  }
  return false;
}




static bool Internal_CreateAndValidateFixedPlane(
  ON_3dPoint P,
  ON_3dVector N,
  ON_PlaneEquation& fixed_plane,
  const double zero_tolerance,
  const size_t Fcount,
  const ON_3dPoint* F
)
{
  for (;;)
  {
    // create
    if (false == N.IsUnitVector())
      N = N.UnitVector();
    if (false == fixed_plane.Create(P, N))
      break;
    if (false == fixed_plane.IsValid())
      break;

    // validate
    double d = 0.0;
    for (size_t i = 0; i < Fcount && d <= zero_tolerance; ++i)
      d = fabs(fixed_plane.ValueAt(F[i]));

    if (d <= zero_tolerance)
      return true; // no nans and all F[] close enough to fixed_plane.

    break;
  }

  // P and N do not define a valid fixed plane
  fixed_plane = ON_PlaneEquation::NanPlaneEquation;
  return false;
}

static bool Internal_InventSymmetryFixedPlane(const double zero_tolerance, ON_Xform xform, unsigned xform_order, ON_PlaneEquation& fixed_plane)
{
  for(;;)
  {
    if (xform_order < 2)
      break;
    if (false == xform.IsNotIdentity())
      break;

    // Set F[] = some fixed points of the xform.
    ON_3dPoint P[] = { ON_3dPoint(0,0,0), ON_3dPoint(1,0,0), ON_3dPoint(0,1,0), ON_3dPoint(0,0,1) };
    ON_3dPoint F[sizeof(P) / sizeof(P[0])];
    const size_t Pcount = sizeof(P) / sizeof(P[0]);
    for (size_t i = 0; i < Pcount; ++i)
      F[i] = P[i];
    ON_Xform x(xform);
    for (unsigned j = 1; j < xform_order; ++j)
    {
      for (size_t i = 0; i < Pcount; ++i)
        F[i] += x * P[i];
      x = x * xform;
    }
    if (false == x.IsIdentity(zero_tolerance))
      break;

    // validate fixed points
    double fdist = 0.0;
    for (size_t i = 0; i < Pcount; ++i)
    {
      F[i] = F[i] / ((double)xform_order);
      double d = F[i].DistanceTo(xform * F[i]);
      if (d > fdist)
        fdist = d;
      else if (d != d)
      {
        fdist = ON_DBL_QNAN;
        break;
      }
    }
    if (false == (fdist <= zero_tolerance))
      break; // xform doesn't have fixed points.

    size_t i0 = 0;
    size_t j0 = 0;
    double maxd = 0.0;
    for (size_t i = 1; i < Pcount; ++i)
    {
      const double d = F[0].DistanceTo(F[i]);
      if (d >= maxd)
      {
        maxd = d;
        j0 = i0;
        i0 = i;
      }
      else if (maxd != maxd)
      {
        maxd = ON_DBL_QNAN;
        break;
      }
    }
    if (maxd != maxd)
      break; // nan

    if (maxd <= zero_tolerance)
    {
      // xform has a fixed point (like DiagonalTransformation(neg,neg,neg)).
      if (Internal_CreateAndValidateFixedPlane(F[0], ON_3dVector::ZAxis, fixed_plane,zero_tolerance,Pcount,F) )
        return true;
      break;
    }

    if (0 == i0)
      break;

    const ON_Line fixed_line(F[0], F[i0]);
    if (false == fixed_line.IsValid())
      break;
    const ON_3dVector T = fixed_line.Tangent();

    // fixed_line is in the fixed plane
    maxd = 0.0;
    for (size_t i = 1; i < Pcount; ++i)
    {
      const ON_3dPoint Q = fixed_line.ClosestPointTo(F[i]);
      const double d = F[i].DistanceTo(Q);
      if (d > maxd)
        maxd = d;
      else if (d != d)
      {
        maxd = ON_DBL_QNAN;
        break;
      }
    }
    if (maxd != maxd)
      break; // nan


    if (maxd <= zero_tolerance)
    {
      // xform has a fixed line (like a rotation)
      if ( Internal_CreateAndValidateFixedPlane(F[0], T.Perpendicular(ON_3dVector::NanVector), fixed_plane, zero_tolerance, Pcount, F) )
        return true;
      break;
    }

    if (0 == j0 || i0 == j0)
      break;

    const ON_3dVector Y = F[j0] - F[0];
    const ON_3dVector N = ON_3dVector::CrossProduct(T, Y).UnitVector();
    if (Internal_CreateAndValidateFixedPlane(F[0], N, fixed_plane, zero_tolerance, Pcount, F))
      return true;

    break;
  }

  fixed_plane = ON_PlaneEquation::NanPlaneEquation;
  return false;
}

////static bool Internal_InventRotationFixedPlane(const double zero_tolerance, const ON_Line rotation_axis, unsigned cyclic_order, ON_PlaneEquation& fixed_plane)
////{
////  const ON_3dPoint F[2] = { rotation_axis.from, rotation_axis.to };
////  const ON_3dVector N = rotation_axis.Tangent().Perpendicular(ON_3dVector::NanVector);
////  return Internal_CreateAndValidateFixedPlane(F[0], N, fixed_plane, zero_tolerance, 2, F);
////}

bool ON_Symmetry::Read(ON_BinaryArchive& archive)
{
  *this = ON_Symmetry::Unset;
  int chunk_version = 0;
  if (false == archive.BeginRead3dmAnonymousChunk(&chunk_version))
    return false;

  ON_Symmetry::Type symmetry_type = ON_Symmetry::Type::Unset;
  unsigned int inversion_order = 0;
  unsigned int cyclic_order = 0;
  ON_UUID symmetry_id = ON_nil_uuid;
  ON_Xform inversion_transform = ON_Xform::Nan;
  ON_Xform cyclic_transform = ON_Xform::Nan;
  ON_PlaneEquation fixed_plane = ON_PlaneEquation::NanPlaneEquation;
  ON_Line rotation_axis = ON_Line::NanLine;

  bool rc = false;
  for (;;)
  {
    if (chunk_version <= 0)
      break;

    unsigned char utype = 0;
    if (false == archive.ReadChar(&utype))
      break;

    bool bNewRotatePrototype = false;
    if (113 == utype)
    {
      // There was a period of time in June 2021 when ON_Symmetry::Type::NewRotate = 113
      // was used to prototype a replacement for an earlier version of rotate
      // that did not work well.  The protyped replacement worked much better
      // and became the standard rotate on June 15, 2021.
      bNewRotatePrototype = true;
      utype = static_cast<unsigned char>(ON_Symmetry::Type::Rotate);
    }
    symmetry_type = ON_Symmetry::SymmetryTypeFromUnsigned(utype);
    if (ON_Symmetry::Type::Unset == symmetry_type)
    {
      rc = true;
      break;
    }

    if (false == archive.ReadInt(&inversion_order))
      break;
    if (false == archive.ReadInt(&cyclic_order))
      break;
    if (false == archive.ReadUuid(symmetry_id))
      break;

    // Before June 1, 2021: Chunk version 2 for rotations that had a rotation plane.
    // June 1, 2021: Chunk version 3 for symmetry_type=113 prototyping rotations with no rotation plane
    // Future: Chunk version 4 for final rotations not using a rotation plane.
    int inner_chunk_version = 0;
    if (false == archive.BeginRead3dmAnonymousChunk(&inner_chunk_version))
      break;

    ON_Symmetry symmetry;

    ON_Symmetry::Coordinates symmetry_coordinates = ON_Symmetry::Coordinates::Object;

    switch (symmetry_type)
    {
    case ON_Symmetry::Type::Unset:
      break;

    case ON_Symmetry::Type::Reflect:
      rc = archive.ReadPlaneEquation(fixed_plane);
      if (rc)
        symmetry = ON_Symmetry::CreateReflectSymmetry(fixed_plane, symmetry_coordinates);
      break;

    case ON_Symmetry::Type::Rotate:
      rc = archive.ReadLine(rotation_axis);
      if (inner_chunk_version >= 2 && false == bNewRotatePrototype)
        rc = archive.ReadPlaneEquation(fixed_plane);
      if (rc)
      {
        // the fixed plane is intentionally ignored.
        symmetry = ON_Symmetry::CreateRotateSymmetry(rotation_axis, cyclic_order, symmetry_coordinates);
      }
      break;

    case ON_Symmetry::Type::ReflectAndRotate:
      rc = archive.ReadPlaneEquation(fixed_plane) && archive.ReadLine(rotation_axis);
      if (rc)
        symmetry = ON_Symmetry::CreateReflectAndRotateSymmetry(fixed_plane, rotation_axis, cyclic_order, symmetry_coordinates);
      break;

    case ON_Symmetry::Type::Inversion:
      rc = archive.ReadXform(inversion_transform);
      if (inner_chunk_version >= 2)
        rc = archive.ReadPlaneEquation(fixed_plane);
      else
        rc = Internal_InventSymmetryFixedPlane(ON_Symmetry::ZeroTolerance, inversion_transform, 2, fixed_plane);
      if (rc)
        symmetry = ON_Symmetry::Internal_CreateInversionSymmetry(symmetry_id, inversion_transform, fixed_plane, symmetry_coordinates);
      break;

    case ON_Symmetry::Type::Cyclic:
      rc = archive.ReadXform(cyclic_transform);
      if (inner_chunk_version >= 2)
        rc = archive.ReadPlaneEquation(fixed_plane);
      else
        rc = Internal_InventSymmetryFixedPlane(ON_Symmetry::ZeroTolerance, cyclic_transform, cyclic_order, fixed_plane);
      if (rc)
        symmetry = ON_Symmetry::Internal_CreateCyclicSymmetry(symmetry_id, cyclic_transform, cyclic_order, fixed_plane, symmetry_coordinates);
      break;

    default:
      // Old code reading a file containing a future type.
      symmetry_type = ON_Symmetry::Type::Unset;
      rc = true; // means no media reading error
      break;
    }

    if (
      rc
      && ON_Symmetry::Type::Unset != symmetry_type
      && symmetry.SymmetryType() == symmetry_type
      && symmetry.InversionOrder() == inversion_order
      && symmetry.CyclicOrder() == cyclic_order
      && symmetry.SymmetryId() == symmetry_id
      )
    {
      *this = symmetry;
    }

    if (false == archive.EndRead3dmChunk())
      rc = false;

    if (chunk_version < 2)
      break;

    unsigned char ucoordinates = 0;
    rc = archive.ReadChar(&ucoordinates);
    if (false == rc)
      break;
    symmetry_coordinates = ON_Symmetry::SymmetryCoordinatesFromUnsigned(ucoordinates);
    if (ON_Symmetry::Coordinates::Unset != symmetry_coordinates && m_coordinates != symmetry_coordinates)
      m_coordinates = symmetry_coordinates;
    
    if (chunk_version < 3)
      break;

    ON__UINT64 symmetric_object_content_serial_number = 0;
    rc = archive.ReadBigInt(&symmetric_object_content_serial_number);
    if (rc)
      this->m_symmetric_object_content_serial_number = symmetric_object_content_serial_number;

    if (chunk_version < 4)
      break;

    // m_symmetric_object_topology_hash added March 29, 2021 chunk version 4
    rc = rc && this->m_symmetric_object_topology_hash.Read(archive);

    // m_symmetric_object_geometry_hash added March 29, 2021 chunk version 4
    rc = rc && this->m_symmetric_object_geometry_hash.Read(archive);

    break;
  }

  if (false == archive.EndRead3dmChunk())
    rc = false;

  return rc;
}

void ON_PlaneEquation::Dump(class ON_TextLog& text_log) const
{
  // print -0 as 0.
  const double c[4] = { (0.0 == x) ? 0.0 : x,(0.0 == y) ? 0.0 : y,(0.0 == z) ? 0.0 : z,(0.0 == d) ? 0.0 : d };
  if ( ON_IS_VALID(c[0]) && ON_IS_VALID(c[1]) && ON_IS_VALID(c[2]) && ON_IS_VALID(c[3]) )
  {
    for (int i = 0; i < 3; ++i)
    {
      if (false == (0.0 != c[i] && 0.0 == c[(i + 1) % 3] && 0.0 == c[(i + 2) % 3]))
        continue;
      const char* coord = (0 == i) ? "x" : ((1 == i) ? "y" : "z");
      if (0.0 == c[3])
        text_log.Print("%s = 0", coord);
      else if (1.0 == c[i])
        text_log.Print("%s = %g", coord, -c[3]);
      else if (-1.0 == c[i])
        text_log.Print("-%s = %g", coord, -c[3]);
      else
        text_log.Print("%g*%s = %g", c[i], coord, -c[3]);
      return;
    }
  }

  // general case
  text_log.Print("%g*x + %g*y + %g*z + %g = 0", c[0], c[1], c[2], c[3]);
}

void ON_Symmetry::Dump(ON_TextLog& text_log) const
{
  ToText(true, text_log);
}

void ON_Symmetry::ToText(
  bool bIncludeSymmetricObject,
  class ON_TextLog& text_log
) const
{
  const ON_wString type = ON_Symmetry::SymmetryTypeToString(m_type);
  const ON_wString coordinates = ON_Symmetry::SymmetryCoordinatesToString(m_coordinates);
  text_log.Print(L"%ls %ls symmetry\n",static_cast<const wchar_t*>(type), static_cast<const wchar_t*>(coordinates));
  if (IsUnset())
    return;

  text_log.Print(L"Motif count: %u\n", MotifCount());

  switch (m_type)
  {
  case ON_Symmetry::Type::Unset:
    break;

  case ON_Symmetry::Type::Reflect:
  {
    text_log.Print(L"plane: ");
    ReflectionPlane().Dump(text_log);
    text_log.PrintNewLine();
  }
  break;

  case ON_Symmetry::Type::Rotate:
  {
    text_log.Print(L"rotation count: %u (%g degrees)\n", RotationCount(), RotationAngleDegrees());
    const ON_Line axis = RotationAxis();
    text_log.Print(L"axis: ");
    text_log.Print(axis.from);
    text_log.Print(L", ");
    text_log.Print(axis.to);
    text_log.PrintNewLine();
  }
  break;

  case ON_Symmetry::Type::ReflectAndRotate:
  {
    text_log.Print(L"plane: ");
    ReflectionPlane().Dump(text_log);
    text_log.PrintNewLine();
    text_log.Print(L"rotation count: %u (%g degrees)\n", RotationCount(), RotationAngleDegrees());
    const ON_Line axis = RotationAxis();
    text_log.Print(L"axis: ");
    text_log.Print(axis.from);
    text_log.Print(L", ");
    text_log.Print(axis.to);
    text_log.PrintNewLine();
  }
  break;

  case ON_Symmetry::Type::Inversion:
  {
    const ON_Line line = RotationAxis();
    text_log.Print(InversionTransformation());
    text_log.PrintNewLine();
  }
  break;

  case ON_Symmetry::Type::Cyclic:
  {
    const ON_Line line = RotationAxis();
    text_log.Print(CyclicTransformation());
    text_log.PrintNewLine();
  }
  break;

  default:
    break;
  }

  if (bIncludeSymmetricObject && 0 != m_symmetric_object_content_serial_number)
  {
    text_log.Print("Symmetric object hashes:\n");
    const ON_TextLogIndent indent1(text_log);
    text_log.Print(L"content serial number: %u\n", m_symmetric_object_content_serial_number);
    text_log.PrintString(ON_wString(L"topology hash: ") + this->m_symmetric_object_topology_hash.ToStringEx(true));
    text_log.PrintNewLine();
    text_log.PrintString(ON_wString(L"geometry hash: ") + this->m_symmetric_object_geometry_hash.ToStringEx(true));
    text_log.PrintNewLine();
  }
}

const ON_Symmetry ON_Symmetry::TransformConditionally(const ON_Xform& xform) const
{
  return
    (ON_Symmetry::Coordinates::Object == SymmetryCoordinates())
    ? ON_Symmetry::TransformUnconditionally(xform)
    : ON_Symmetry(*this);
}

const ON_Symmetry ON_Symmetry::TransformUnconditionally(const ON_Xform& xform) const
{
  switch (m_type)
  {
  case ON_Symmetry::Type::Unset:
    break;

  case ON_Symmetry::Type::Reflect:
  {
    if (false == m_fixed_plane.IsValid())
      break;
    ON_PlaneEquation e = m_fixed_plane;
    e.Transform(xform);
    if (false == e.IsValid())
      break;
    return ON_Symmetry::CreateReflectSymmetry(e, m_coordinates);
  }
  break;


  case ON_Symmetry::Type::Rotate:
  {
    if (false == m_rotation_axis.IsValid())
      break;
    ON_Line a = m_rotation_axis;
    a.Transform(xform);
    if (false == a.IsValid())
      break;
    return ON_Symmetry::CreateRotateSymmetry(a, RotationCount(), m_coordinates);
  }
  break;

  case ON_Symmetry::Type::ReflectAndRotate:
  {
    if (false == m_fixed_plane.IsValid())
      break;
    if (false == m_rotation_axis.IsValid())
      break;
    ON_PlaneEquation e = m_fixed_plane;
    e.Transform(xform);
    if (false == e.IsValid())
      break;
    ON_Line a = m_rotation_axis;
    a.Transform(xform);
    if (false == a.IsValid())
      break;
    return ON_Symmetry::CreateReflectAndRotateSymmetry(e, a, RotationCount(), m_coordinates);
  }
  break;

  case ON_Symmetry::Type::Inversion:
  {
    const ON_Xform xform_inverse = xform.Inverse();
    const ON_Xform inversion_xform = xform * InversionTransformation()*xform_inverse;
    if (false == m_fixed_plane.IsValid())
      break;
    ON_PlaneEquation e = m_fixed_plane;
    e.Transform(xform);
    if (false == e.IsValid())
      break;
    return ON_Symmetry::Internal_CreateInversionSymmetry(SymmetryId(), inversion_xform, e, m_coordinates);
  }
  break;

  case ON_Symmetry::Type::Cyclic:
  {
    const ON_Xform xform_inverse = xform.Inverse();
    const ON_Xform cyclic_xform = xform * CyclicTransformation()*xform_inverse;
    if (false == m_fixed_plane.IsValid())
      break;
    ON_PlaneEquation e = m_fixed_plane;
    e.Transform(xform);
    if (false == e.IsValid())
      break;
    return ON_Symmetry::Internal_CreateCyclicSymmetry(SymmetryId(), cyclic_xform, CyclicOrder(), e, m_coordinates);
  }
  break;

  default:
    break;
  }
  return ON_Symmetry::Unset;
}

static bool Internal_SamePlane(const ON_Symmetry* lhs, const ON_Symmetry* rhs, double zero_tolerance)
{
  const ON_PlaneEquation lhs_e = lhs->ReflectionPlane().UnitizedPlaneEquation();
  const ON_PlaneEquation rhs_e = rhs->ReflectionPlane().UnitizedPlaneEquation();
  return
    fabs(lhs_e.x - rhs_e.x) <= zero_tolerance
    && fabs(lhs_e.y - rhs_e.y) <= zero_tolerance
    && fabs(lhs_e.z - rhs_e.z) <= zero_tolerance
    && fabs(lhs_e.d - rhs_e.d) <= zero_tolerance
    ;
}

static bool Internal_SameRotation(const ON_Symmetry* lhs, const ON_Symmetry* rhs, double zero_tolerance)
{
  const ON_Line lhs_l = lhs->RotationAxis();
  const ON_Line rhs_l = rhs->RotationAxis();
  if (
    lhs_l.DistanceTo(rhs_l.from) <= zero_tolerance
    && lhs_l.DistanceTo(rhs_l.to) <= zero_tolerance
    && rhs_l.DistanceTo(lhs_l.from) <= zero_tolerance
    && rhs_l.DistanceTo(lhs_l.to) <= zero_tolerance
    )
  {
    const ON_3dVector lhs_t = lhs->RotationAxis().Tangent();
    const ON_3dVector rhs_t = lhs->RotationAxis().Tangent();
    const double lhs_a = lhs->RotationAngleRadians();
    const double rhs_a = ((lhs_t * rhs_t < 0.0) ? -1.0 : 1.0) * rhs->RotationAngleRadians();
    if (fabs(lhs_a - rhs_a) <= zero_tolerance)
    {
      // a point 1 unit from the common axis will rotate within zero tolerance
      return true;
    }
  }
  return false;
}

static bool Internal_SameTransformation(const ON_Xform lhs_x, const ON_Xform rhs_x, double zero_tolerance)
{
  return (lhs_x * rhs_x.Inverse()).IsIdentity(zero_tolerance) && (rhs_x * lhs_x.Inverse()).IsIdentity(zero_tolerance);
}

static bool Internal_SameTransformation(const ON_Symmetry* lhs, const ON_Symmetry* rhs, double zero_tolerance)
{
  ON_Xform lhs_x;
  ON_Xform rhs_x;
  if (lhs->InversionOrder() != rhs->InversionOrder())
    return false;
  if (lhs->CyclicOrder() != rhs->CyclicOrder())
    return false;
  if (lhs->InversionOrder() > 1 && false == Internal_SameTransformation(lhs->InversionTransformation(), rhs->InversionTransformation(), zero_tolerance))
    return false;
  if (lhs->CyclicOrder() > 1 && false == Internal_SameTransformation(lhs->CyclicTransformation(), rhs->CyclicTransformation(), zero_tolerance))
    return false;
  return true;
}


int ON_Symmetry::CompareSymmetryTransformation(const ON_Symmetry* lhs, const ON_Symmetry* rhs, double zero_tolerance)
{
  for (;;)
  {
    const ON_Symmetry::Type lhs_type = (nullptr != lhs) ? lhs->SymmetryType() : ON_Symmetry::Type::Unset;
    const ON_Symmetry::Type rhs_type = (nullptr != rhs) ? rhs->SymmetryType() : ON_Symmetry::Type::Unset;
    if (lhs_type != rhs_type)
      break;

    if (ON_Symmetry::Type::Unset == lhs_type)
      return 0; // both are unset

    if (false == (zero_tolerance >= 0.0 && zero_tolerance < ON_UNSET_POSITIVE_FLOAT))
      zero_tolerance = ON_Symmetry::ZeroTolerance;

    switch (lhs_type)
    {
    case ON_Symmetry::Type::Unset:
      break;

    case ON_Symmetry::Type::Reflect:
      if (Internal_SamePlane(lhs, rhs, zero_tolerance))
        return 0;
      break;

    case ON_Symmetry::Type::Rotate:
      if (Internal_SameRotation(lhs, rhs, zero_tolerance))
        return 0;
      break;

    case ON_Symmetry::Type::ReflectAndRotate:
      if (Internal_SamePlane(lhs, rhs, zero_tolerance) && Internal_SameRotation(lhs, rhs, zero_tolerance))
        return 0;
      break;

    case ON_Symmetry::Type::Inversion:
    case ON_Symmetry::Type::Cyclic:
      if (Internal_SameTransformation(lhs, rhs, zero_tolerance))
        return 0;

    default:
      break;
    }
  }

  return ON_Symmetry::Compare(lhs, rhs);
}


const ON_PlaneEquation ON_Symmetry::Internal_UnitizePlaneEquationParameter(ON_PlaneEquation e)
{
  for (;;)
  {
    if (false == e.IsSet())
      break;
    if (e.IsUnitized())
      return e;
    const ON_PlaneEquation u = e.UnitizedPlaneEquation();
    if (u.IsUnitized())
      return u;
    break;
  }
  return ON_PlaneEquation::NanPlaneEquation;
}

const ON_Symmetry ON_Symmetry::Internal_CreateInversionSymmetry(
  ON_UUID symmetry_id, 
  ON_Xform inversion_transform, 
  ON_PlaneEquation fixed_plane,
  ON_Symmetry::Coordinates symmetry_coordinates
)
{
  for (;;)
  {
    const double det = inversion_transform.Determinant();
    if (false == (det < 0.0))
      break;
    if (false == ON_Symmetry::IsValidCyclicTranformation(inversion_transform, 2))
      break;

    if (false == (ON_nil_uuid == symmetry_id) )
    {
      // prohibit using built-in ids
      if (ON_Symmetry::ReflectId == symmetry_id)
        break;
      if (ON_Symmetry::RotateId == symmetry_id)
        break;
      if (ON_Symmetry::ReflectAndRotateId == symmetry_id)
        break;
    }

    ON_Symmetry symmetry;
    symmetry.m_type = ON_Symmetry::Type::Inversion;
    symmetry.m_coordinates = symmetry_coordinates;
    symmetry.m_inversion_order = 2;
    symmetry.m_cyclic_order = 1;
    symmetry.m_id = symmetry_id;
    symmetry.m_inversion_transform = inversion_transform;
    symmetry.m_fixed_plane = fixed_plane;
    symmetry.m_cyclic_transform = ON_Xform::IdentityTransformation;
    return symmetry;
  }

  return ON_Symmetry::Unset;
}

const ON_Symmetry ON_Symmetry::Internal_CreateCyclicSymmetry(
  ON_UUID symmetry_id,
  ON_Xform cyclic_transform,
  unsigned int cyclic_order,
  ON_Line fixed_line,
  ON_Symmetry::Coordinates symmetry_coordinates
)
{
  for (;;)
  {
    if (false == fixed_line.IsValid())
      break;

    const ON_Line unit_axis(fixed_line.from, fixed_line.from + fixed_line.Tangent());
    if (false == unit_axis.IsValid())
      break;

    if (false == ON_Symmetry::IsValidCyclicTranformation(cyclic_transform, cyclic_order))
      break;

    const double det = cyclic_transform.Determinant();
    if (2 == cyclic_order || 1 == (cyclic_order % 2))
    {
      if (false == (det > 0.0))
        break;
    }
    else
    {
      if (false == (det != 0.0))
        break;
    }

    if (false == (ON_nil_uuid == symmetry_id))
    {
      // prohibit using built-in ids
      if (ON_Symmetry::ReflectId == symmetry_id)
        break;
      if (ON_Symmetry::RotateId == symmetry_id)
        break;
      if (ON_Symmetry::ReflectAndRotateId == symmetry_id)
        break;
    }


    // Make sure cyclic_transform fixes the axis.
    const ON_3dPoint P[3] = { fixed_line.from, fixed_line.to, unit_axis.to };
    const unsigned Pcount = (unsigned)(sizeof(P) / sizeof(P[0]));
    ON_Xform T = cyclic_transform;
    for (unsigned int i = 0; i < cyclic_order; ++i)
    {
      for (unsigned j = 0; j < Pcount; ++j)
      {
        const ON_3dPoint Q = T * P[j];
        const double d = P[j].DistanceTo(Q);
        if (false == (d <= ON_Symmetry::ZeroTolerance))
          return ON_Symmetry::Unset;
      }
      T = T * cyclic_transform;
    }

    ON_Symmetry symmetry;
    symmetry.m_type = ON_Symmetry::Type::Cyclic;
    symmetry.m_coordinates = symmetry_coordinates;
    symmetry.m_inversion_order = 1;
    symmetry.m_cyclic_order = cyclic_order;
    symmetry.m_id = symmetry_id;
    symmetry.m_inversion_transform = ON_Xform::IdentityTransformation;
    symmetry.m_cyclic_transform = cyclic_transform;
    symmetry.m_fixed_plane = ON_PlaneEquation::NanPlaneEquation;
    return symmetry;
  }

  return ON_Symmetry::Unset;
}

const ON_Symmetry ON_Symmetry::Internal_CreateCyclicSymmetry(
  ON_UUID symmetry_id, 
  ON_Xform cyclic_transform,
  unsigned int cyclic_order,
  ON_PlaneEquation zero_plane,
  ON_Symmetry::Coordinates symmetry_coordinates
)
{
  for (;;)
  {
    zero_plane = ON_Symmetry::Internal_UnitizePlaneEquationParameter(zero_plane);
    if (false == zero_plane.IsSet())
      break;

    if (false == ON_Symmetry::IsValidCyclicTranformation(cyclic_transform, cyclic_order))
      break;

    const double det = cyclic_transform.Determinant();
    if (2 == cyclic_order || 1 == (cyclic_order % 2))
    {
      if (false == (det > 0.0))
        break;
    }
    else
    {
      if (false == (det != 0.0))
        break;
    }

    if (false == (ON_nil_uuid == symmetry_id))
    {
      // prohibit using built-in ids
      if (ON_Symmetry::ReflectId == symmetry_id)
        break;
      if (ON_Symmetry::RotateId == symmetry_id)
        break;
      if (ON_Symmetry::ReflectAndRotateId == symmetry_id)
        break;
    }

    ON_Symmetry symmetry;
    symmetry.m_type = ON_Symmetry::Type::Cyclic;
    symmetry.m_coordinates = symmetry_coordinates;
    symmetry.m_inversion_order = 1;
    symmetry.m_cyclic_order = cyclic_order;
    symmetry.m_id = symmetry_id;
    symmetry.m_inversion_transform = ON_Xform::IdentityTransformation;
    symmetry.m_cyclic_transform = cyclic_transform;
    symmetry.m_fixed_plane = zero_plane;
    return symmetry;
  }

  return ON_Symmetry::Unset;
}

const ON_Symmetry ON_Symmetry::CreateReflectSymmetry(
  ON_PlaneEquation reflection_plane, 
  ON_Symmetry::Coordinates symmetry_coordinates
)
{
  for (;;)
  {
    reflection_plane = ON_Symmetry::Internal_UnitizePlaneEquationParameter(reflection_plane);
    if (false == reflection_plane.IsSet())
      break;
    ON_PlaneEquation e = reflection_plane.UnitizedPlaneEquation();
    if (false == e.IsSet())
      break;
    const ON_Xform xform(ON_Xform::MirrorTransformation(reflection_plane));
    if (false == ON_Symmetry::IsValidReflectionTranformationAndFixedPlane(xform, reflection_plane))
      break;
    ON_Symmetry symmetry = ON_Symmetry::Internal_CreateInversionSymmetry(ON_nil_uuid, xform, reflection_plane, symmetry_coordinates);
    if (ON_Symmetry::Type::Inversion != symmetry.m_type)
      break;
    symmetry.m_type = ON_Symmetry::Type::Reflect;
    symmetry.m_id = ON_Symmetry::ReflectId;
    return symmetry;
  }
  return ON_Symmetry::Unset;
}

const ON_Symmetry ON_Symmetry::CreateRotateSymmetry(
  ON_Line rotation_axis,
  unsigned int rotation_count,
  ON_Symmetry::Coordinates symmetry_coordinates
)
{
  for (;;)
  {
    if (false == ON_Symmetry::IsValidRotationAxis(rotation_axis, rotation_count))
      break;
    const ON_Xform R = Internal_RotationXform(rotation_axis, 1, rotation_count);
    ON_Symmetry symmetry = ON_Symmetry::Internal_CreateCyclicSymmetry(ON_nil_uuid, R, rotation_count, rotation_axis, symmetry_coordinates);
    if (ON_Symmetry::Type::Cyclic != symmetry.m_type)
      break;
    symmetry.m_type = ON_Symmetry::Type::Rotate;
    symmetry.m_id = ON_Symmetry::RotateId;
    symmetry.m_rotation_axis = rotation_axis;
    return symmetry;
  }
  return ON_Symmetry::Unset;
}

const ON_Symmetry ON_Symmetry::CreateReflectAndRotateSymmetry(
  ON_PlaneEquation reflection_plane,
  ON_Line rotation_axis, 
  unsigned int rotation_count,
  ON_Symmetry::Coordinates symmetry_coordinates
)
{
  for (;;)
  {
    reflection_plane = ON_Symmetry::Internal_UnitizePlaneEquationParameter(reflection_plane);

    const ON_Symmetry reflection = CreateReflectSymmetry(reflection_plane, symmetry_coordinates);
    if (ON_Symmetry::Type::Reflect != reflection.SymmetryType())
      break;

    const ON_Symmetry rotation = CreateRotateSymmetry(rotation_axis,rotation_count, symmetry_coordinates);
    if (ON_Symmetry::Type::Rotate != rotation.SymmetryType())
      break;

    ON_Symmetry symmetry;
    symmetry.m_type = ON_Symmetry::Type::ReflectAndRotate;
    symmetry.m_coordinates = symmetry_coordinates;
    symmetry.m_inversion_order = reflection.m_inversion_order;
    symmetry.m_cyclic_order = rotation.m_cyclic_order;
    symmetry.m_id = ON_Symmetry::ReflectAndRotateId;
    symmetry.m_inversion_transform = reflection.m_inversion_transform;
    symmetry.m_cyclic_transform = rotation.m_cyclic_transform;
    symmetry.m_fixed_plane = reflection.m_fixed_plane;
    symmetry.m_rotation_axis = rotation.m_rotation_axis;
    return symmetry;
  }
  return ON_Symmetry::Unset;
}

int ON_Symmetry::Internal_CompareDouble(const double* lhs, const double* rhs, size_t count)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  for (size_t i = 0; i < count; ++i)
  {
    const double x = lhs[i];
    const double y = rhs[i];
    if (x < y)
      return -1;
    if (x > y)
      return 1;
    const bool xok = (x == x) ? true : false;
    const bool yok = (y == y) ? true : false;
    if (xok == yok)
      continue;
    if (false == xok)
      return 1; // lhs is a nan
    if (false == yok)
      return -1; // rhs is a nan
  }
  return 0;
}

int ON_Symmetry::Compare(const ON_Symmetry* lhs, const ON_Symmetry* rhs)
{
  if (lhs == rhs)
    return 0;

  // sort nulls to end
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;

  if (static_cast<unsigned char>(lhs->m_type) < static_cast<unsigned char>(rhs->m_type))
    return -1;
  if (static_cast<unsigned char>(lhs->m_type) > static_cast<unsigned char>(rhs->m_type))
    return 1;
  if (ON_Symmetry::Type::Unset == lhs->m_type)
    return 0;

  if (static_cast<unsigned char>(lhs->m_coordinates) < static_cast<unsigned char>(rhs->m_coordinates))
    return -1;
  if (static_cast<unsigned char>(lhs->m_coordinates) > static_cast<unsigned char>(rhs->m_coordinates))
    return 1;


  if (lhs->m_inversion_order < rhs->m_inversion_order)
    return -1;
  if (lhs->m_inversion_order > rhs->m_inversion_order)
    return 1;

  if (lhs->m_cyclic_order < rhs->m_cyclic_order)
    return -1;
  if (lhs->m_cyclic_order > rhs->m_cyclic_order)
    return 1;

  if (0U == lhs->m_inversion_order || 0U == lhs->m_cyclic_order)
    return 0;
   
  if (lhs->Internal_RequiresFixedPlane() || rhs->Internal_RequiresFixedPlane())
  {
    const int rc = ON_Symmetry::Internal_CompareDouble(&lhs->m_fixed_plane.x, &rhs->m_fixed_plane.x, 4);
    if (0 != rc)
      return rc;
  }

  if (lhs->Internal_RequiresRotationAxis() || rhs->Internal_RequiresRotationAxis())
  {
    const int rc = ON_Symmetry::Internal_CompareDouble(&lhs->m_rotation_axis.from.x, &rhs->m_rotation_axis.from.x, 6);
    if (0 != rc)
      return rc;
  }

  if (lhs->Internal_IsStandardType() && rhs->Internal_IsStandardType())
    return 0;

  if (lhs->m_inversion_order > 1)
  {
    const int rc = ON_Symmetry::Internal_CompareDouble(&lhs->m_inversion_transform.m_xform[0][0], &rhs->m_inversion_transform.m_xform[0][0], 16);
    if (0 != rc)
      return rc;
  }

  if (lhs->m_cyclic_order > 1)
  {
    const int rc = ON_Symmetry::Internal_CompareDouble(&lhs->m_inversion_transform.m_xform[0][0], &rhs->m_inversion_transform.m_xform[0][0], 16);
    if (0 != rc)
      return rc;
  }

  // Do NOT compare the symmetric object settings in this function.

  return 0;
}

ON_Symmetry::Type ON_Symmetry::SymmetryType() const
{
  return m_type;
}

bool ON_Symmetry::IsRotate() const
{
  return ON_Symmetry::Type::Rotate == m_type;
}

bool ON_Symmetry::IsReflect() const
{
  return ON_Symmetry::Type::Reflect == m_type;
}

bool ON_Symmetry::IsReflectAndRotate() const
{
  return ON_Symmetry::Type::ReflectAndRotate == m_type;
}

ON_Symmetry::Coordinates ON_Symmetry::SymmetryCoordinates() const
{
  return m_coordinates;
}

const ON_UUID ON_Symmetry::SymmetryId() const
{
  return m_id;
}

void ON_Symmetry::Clear()
{
  *this = ON_Symmetry::Unset;
}

bool ON_Symmetry::IsSet() const
{
  return 
    ON_Symmetry::Type::Unset != m_type
    && (1 == m_inversion_order || 2 == m_inversion_order)
    && m_cyclic_order >= 1
    && MotifCount() >= 2
    ;
}

bool ON_Symmetry::IsUnset() const
{
  return (false == IsSet());
}

unsigned int ON_Symmetry::MotifCount() const
{
  return InversionOrder()*CyclicOrder();
}


unsigned int ON_Symmetry::InversionOrder() const
{
  return m_inversion_order;
}


unsigned int ON_Symmetry::CyclicOrder() const
{
  return m_cyclic_order;
}

const ON_Xform ON_Symmetry::InversionTransformation() const
{
  return IsSet() ? m_inversion_transform : ON_Xform::Nan;
}

const ON_Xform ON_Symmetry::CyclicTransformation() const
{
  return IsSet() ? m_cyclic_transform : ON_Xform::Nan;
}

const ON_SHA1_Hash ON_Symmetry::Hash() const
{
  for(;;)
  {
    if (false == IsSet())
      break;
    
    ON_SHA1 sha1;

    const unsigned char t = static_cast<unsigned char>(m_type);
    sha1.AccumulateBytes(&t, sizeof(t));

    const unsigned char c = static_cast<unsigned char>(m_coordinates);
    sha1.AccumulateBytes(&c, sizeof(c));

    sha1.AccumulateInteger32(InversionOrder());
    sha1.AccumulateInteger32(CyclicOrder());

    if ( this->Internal_RequiresFixedPlane())
      sha1.AccumulateDoubleArray(4, &m_fixed_plane.x);

    if ( this->Internal_RequiresRotationAxis() )
      sha1.AccumulateDoubleArray(6, &m_rotation_axis.from.x);

    if ( false == this->Internal_IsStandardType() )
    {
      if (InversionOrder() > 1)
        sha1.AccumulateDoubleArray(16, &m_inversion_transform.m_xform[0][0]);
      if (CyclicOrder() > 1)
        sha1.AccumulateDoubleArray(16, &m_cyclic_transform.m_xform[0][0]);
    }
    return sha1.Hash();
  }

  return ON_SHA1_Hash::EmptyContentHash;
}

const ON_PlaneEquation ON_Symmetry::ReflectionPlane() const
{
  return (ON_Symmetry::Type::Reflect == m_type || ON_Symmetry::Type::ReflectAndRotate == m_type)
    ? FixedPlane()
    : ON_PlaneEquation::NanPlaneEquation;
}

const ON_PlaneEquation ON_Symmetry::ReflectAndRotatePlane(
  unsigned int plane_index
) const
{
  if ( (IsSet() && ON_Symmetry::Type::ReflectAndRotate == m_type) || (plane_index >= 0 && plane_index <= 2))
  {
    const ON_PlaneEquation fixed_plane = FixedPlane();
    if (0 == plane_index)
      return fixed_plane;

    // 2nd plane
    ON_Xform R;
    const double a = (1 == plane_index) ? -0.5 * RotationAngleRadians() : 0.5 * ON_PI;
    R.Rotation(a, RotationAxisTangent(), RotationAxisPoint());
    ON_PlaneEquation e = fixed_plane;
    e.Transform(R);
    return (1 == plane_index) ? e.NegatedPlaneEquation() : e;
  }

  return ON_PlaneEquation::NanPlaneEquation;
}

bool ON_Symmetry::OnReflectAndRotateFixedPlane( ON_3dPoint P, bool bUseCleanupTolerance) const
{
  if (ON_Symmetry::Type::ReflectAndRotate != m_type)
    return false;
  if (false == P.IsValid())
    return false;
  const double tol = this->Tolerance(bUseCleanupTolerance);
  
  const ON_PlaneEquation M = this->ReflectAndRotatePlane(0);
  double h = M.ValueAt(P);
  if (fabs(h) <= tol)
    return true;
  
  const ON_PlaneEquation S = this->ReflectAndRotatePlane(1);
  h = S.ValueAt(P);
  if (fabs(h) <= tol)
    return true;

  const unsigned Rcount = this->RotationCount();
  if (Rcount > 2)
  {
    const ON_Xform R = this->RotationTransformation();
    for (unsigned i = 1; i < Rcount; ++i)
    {
      P = R * P;
      h = S.ValueAt(P);
      if (fabs(h) <= tol)
        return true;
      h = M.ValueAt(P);
      if (fabs(h) <= tol)
        return true;
    }
  }

  return false;
}

const ON_Xform ON_Symmetry::ReflectionTransformation() const
{
  return (ON_Symmetry::Type::Reflect == m_type || ON_Symmetry::Type::ReflectAndRotate == m_type)
    ? MotifTransformation(1)
    : ON_Xform::Nan;
}

const ON_PlaneEquation ON_Symmetry::FixedPlane() const
{
  return (ON_Symmetry::Type::Unset != m_type)
    ? m_fixed_plane
    : ON_PlaneEquation::NanPlaneEquation;
}

bool ON_Symmetry::Internal_RequiresRotationAxis() const
{
  return (ON_Symmetry::Type::Rotate == m_type || ON_Symmetry::Type::ReflectAndRotate == m_type);
}

bool ON_Symmetry::Internal_RequiresFixedPlane() const
{
  return (ON_Symmetry::Type::Reflect == m_type || ON_Symmetry::Type::ReflectAndRotate == m_type);
}

bool ON_Symmetry::Internal_IsStandardType() const
{
  return (ON_Symmetry::Type::Reflect == m_type || ON_Symmetry::Type::Rotate == m_type || ON_Symmetry::Type::ReflectAndRotate == m_type);
}

const ON_Line ON_Symmetry::RotationAxis() const
{
  return (Internal_RequiresRotationAxis())
    ? m_rotation_axis
    : ON_Line::NanLine;
}

const ON_3dPoint ON_Symmetry::RotationAxisPoint() const
{
  return (Internal_RequiresRotationAxis())
    ? m_rotation_axis.from
    : ON_3dPoint::NanPoint;
}

const ON_3dVector ON_Symmetry::RotationAxisDirection() const
{
  return (Internal_RequiresRotationAxis())
    ? m_rotation_axis.Direction()
    : ON_3dVector::NanVector;
}

const ON_3dVector ON_Symmetry::RotationAxisTangent() const
{
  return (Internal_RequiresRotationAxis())
    ? m_rotation_axis.Tangent()
    : ON_3dVector::NanVector;
}

unsigned int ON_Symmetry::RotationCount() const
{
  return (Internal_RequiresRotationAxis())
    ? m_cyclic_order
    : 0U;
}

double ON_Symmetry::RotationAngleDegrees() const
{
  return (Internal_RequiresRotationAxis())
    ? (360.0 / ((double)RotationCount()))
    : ON_DBL_QNAN;
}

double ON_Symmetry::RotationAngleRadians() const
{
  return (Internal_RequiresRotationAxis())
    ? ((2.0*ON_PI) / ((double)RotationCount()))
    : ON_DBL_QNAN;
}


const ON_Xform ON_Symmetry::RotationTransformation() const
{
  if ( ON_Symmetry::Type::Rotate == m_type )
  {
    return MotifTransformation(1);
  }
  if (ON_Symmetry::Type::ReflectAndRotate == m_type)
  {
    return MotifTransformation(2);
  }
  return ON_Xform::Nan;
}

const ON_Xform ON_Symmetry::Internal_RotationXform(
  int rotation_index, 
  int rotation_count
) const
{
  if (rotation_index < 0 || rotation_index >= rotation_count)
    return ON_Xform::Nan;
  if (0 == rotation_index)
    return ON_Xform::IdentityTransformation;
  if (1 == rotation_index)
    return m_cyclic_transform;

  return ON_Symmetry::Internal_RotationXform(m_rotation_axis, rotation_index, rotation_count);
}

const ON_Xform ON_Symmetry::Internal_RotationXform(
  ON_Line rotation_axis,
  int rotation_index,
  int rotation_count
)
{
  if (rotation_index < 0 || rotation_index >= rotation_count)
    return ON_Xform::Nan;
  if (0 == rotation_index)
    return ON_Xform::IdentityTransformation;

  // calculate from trig functions for maximum precision
  double sin_sign = 1.0;
  if (2 * rotation_index > rotation_count)
  {
    rotation_index = rotation_count - rotation_index;
    sin_sign = -1.0;
  }

  double cos_angle = ON_DBL_QNAN;
  double sin_angle = ON_DBL_QNAN;

  if (2 * rotation_index == rotation_count)
  {
    // angle = pi
    sin_angle = 0.0;
    cos_angle = -1.0;
  }
  else if (3 * rotation_index == rotation_count)
  {
    // angle = 2pi/3
    sin_angle = 0.5*sqrt(3.0);
    cos_angle = -0.5;
  }
  else if (4 * rotation_index == rotation_count)
  {
    // angle = pi/2
    sin_angle = 1.0;
    cos_angle = 0.0;
  }
  else if (6 * rotation_index == rotation_count)
  {
    // angle = pi/3
    sin_angle = 0.5*sqrt(3.0);
    cos_angle = 0.5;
  }
  else if (8 * rotation_index == rotation_count)
  {
    // angle = pi/4
    sin_angle = cos_angle = 1.0 / sqrt(2.0);
  }
  else if (12 * rotation_index == rotation_count)
  {
    // angle = pi/3
    sin_angle = 0.5;
    cos_angle = 0.5*sqrt(3.0);
  }
  else
  {
    const double a = (rotation_index*(2.0*ON_PI)) / ((double)rotation_count);
    sin_angle = sin(a);
    cos_angle = cos(a);
  }

  ON_Xform r;
  r.Rotation(sin_sign*sin_angle, cos_angle, rotation_axis.Direction(), rotation_axis.from);
  return r;
}

const ON_Xform ON_Symmetry::MotifTransformation(
  int index
) const
{
  const int count = MotifCount();
  if ( count <= 1)
    return ON_Xform::Nan;

  // convert index to be >= 0
  index = ((index % count) + count) % count;
  
  ON_Xform x = ON_Xform::Nan;
  switch (m_type)
  {
  case ON_Symmetry::Type::Unset:
    break;

  case ON_Symmetry::Type::Reflect:
    x = (0 == index)
      ? ON_Xform::IdentityTransformation
      : m_inversion_transform;
    break;

  case ON_Symmetry::Type::Rotate:
    x = Internal_RotationXform(index, count);
    break;

  case ON_Symmetry::Type::ReflectAndRotate:
    if (0 == index)
      x = ON_Xform::IdentityTransformation;
    else if (1 == index)
      x = m_inversion_transform;
    else if (2 == index)
      x = m_cyclic_transform;
    else if ( index > 2 )
      x = Internal_ReflectAndRotateTransformation((unsigned)index);
    break;

  case ON_Symmetry::Type::Inversion:
    x = (0 == index)
      ? ON_Xform::IdentityTransformation
      : m_inversion_transform;
    break;

  case ON_Symmetry::Type::Cyclic:
    if (0 == index)
    {
      x = ON_Xform::IdentityTransformation;
    }
    else if (1 == index)
    {
      x = m_cyclic_transform;
    }
    else if (index >= 2)
    {
      x = m_cyclic_transform * m_cyclic_transform;
      for (int i = 2; i < index; i++)
        x = m_cyclic_transform * x;
    }
    break;

  default:
    break;
  }
  return x;
}

unsigned ON_Symmetry::GetMotifTransformations(
  bool bIncludeIdentity,
  ON_SimpleArray<ON_Xform>& motif_transformations
) const
{
  motif_transformations.SetCount(0);
  const unsigned motif_count = MotifCount();
  if (motif_count <= 0)
    return 0;
  motif_transformations.Reserve(bIncludeIdentity ? motif_count : (motif_count - 1));
  for (unsigned i = bIncludeIdentity ? 0 : 1; i < motif_count; ++i)
  {
    const ON_Xform x = this->MotifTransformation(i);
    motif_transformations.Append(x);
  }
  return motif_count;
}

const ON_Xform ON_Symmetry::Internal_ReflectAndRotateTransformation(unsigned index) const
{
  ON_Xform r = Internal_RotationXform(index / 2, m_cyclic_order);
  if (1 == index % 2)
    r = r * m_inversion_transform;
  return r;
}

const ON_SHA1_Hash ON_Symmetry::SymmetryHash() const
{
  ON_SHA1 sha1;
  sha1.AccumulateBytes(&m_type, sizeof(m_type));
  sha1.AccumulateBytes(&m_coordinates, sizeof(m_coordinates));
  sha1.AccumulateUnsigned8(m_inversion_order);
  sha1.AccumulateInteger32(m_cyclic_order);
  sha1.AccumulateId(m_id);
  sha1.AccumulateDoubleArray(16, &m_inversion_transform.m_xform[0][0]);
  sha1.AccumulateDoubleArray(16, &m_cyclic_transform.m_xform[0][0]);
  sha1.AccumulateDoubleArray(4,&m_fixed_plane.x);
  sha1.Accumulate3dPoint(m_rotation_axis.from);
  sha1.Accumulate3dPoint(m_rotation_axis.to);
  return sha1.Hash();
}

void ON_Symmetry::ClearSymmetricObject() const
{
  m_symmetric_object_content_serial_number = 0U;
  m_symmetric_object_geometry_hash = ON_SHA1_Hash::ZeroDigest;
  m_symmetric_object_topology_hash = ON_SHA1_Hash::ZeroDigest;
}

void ON_Symmetry::SetCleanupTolerance(
  double cleanup_tolerance
)
{
  if (cleanup_tolerance > ON_Symmetry::ZeroTolerance && cleanup_tolerance < ON_UNSET_POSITIVE_VALUE)
    m_cleanup_tolerance = cleanup_tolerance;
  else
    m_cleanup_tolerance = 0.0; // See ON_Symmetry::CleanupTolerance().
}


double ON_Symmetry::CleanupTolerance() const
{
  // The default constructor sets m_cleanup_tolerance = 0.0.
  // Handling m_cleanup_tolerance this way insures that ON_Symmetry::CleanupTolerance()
  // will always return ON_Symmetry::ZeroTolerance (which may change), even with class definitions
  // read from old archives.
  return (m_cleanup_tolerance >= ON_Symmetry::ZeroTolerance) ? m_cleanup_tolerance : ON_Symmetry::ZeroTolerance;
}

double ON_Symmetry::Tolerance(bool bUseCleanupTolerance) const
{
  return bUseCleanupTolerance ? CleanupTolerance() : ON_Symmetry::ZeroTolerance;
}
