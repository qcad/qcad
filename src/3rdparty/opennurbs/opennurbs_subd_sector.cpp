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

#include "opennurbs_subd_data.h"

double ON_SubDSectorType::SectorCoefficientCalculationError()
{
  return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::ErrorSectorCoefficient);
}

bool ON_SubDSectorType::IsValid() const
{
  if ( 0 == m_hash)
    return ON_SUBD_RETURN_ERROR(false);

  if ( m_sector_face_count < ON_SubDSectorType::MinimumSectorFaceCount(m_vertex_tag))
    return ON_SUBD_RETURN_ERROR(false);

  if ( m_sector_face_count > ON_SubDVertex::MaximumFaceCount)
    return ON_SUBD_RETURN_ERROR(false);

  switch (m_vertex_tag)
  {
  case ON_SubDVertexTag::Smooth:
    if (!(m_corner_sector_angle_radians == ON_SubDSectorType::IgnoredCornerSectorAngle))
      return ON_SUBD_RETURN_ERROR(false);
    if (!(m_sector_coefficient == ON_SubDSectorType::IgnoredSectorCoefficient))
      return ON_SUBD_RETURN_ERROR(false);
    break;

  case ON_SubDVertexTag::Crease:
    if (!(m_corner_sector_angle_radians == ON_SubDSectorType::IgnoredCornerSectorAngle))
      return ON_SUBD_RETURN_ERROR(false);
    if (!(m_sector_coefficient == ON_SubDSectorType::CreaseSectorCoefficient(m_sector_face_count)))
      return ON_SUBD_RETURN_ERROR(false);
    break;

  case ON_SubDVertexTag::Corner:
    if (!(m_corner_sector_angle_radians > 0.0 && m_corner_sector_angle_radians <= ON_PI))
      return ON_SUBD_RETURN_ERROR(false);
    if (!(m_sector_coefficient == ON_SubDSectorType::CornerSectorCoefficient(m_sector_face_count,m_corner_sector_angle_radians)))
      return ON_SUBD_RETURN_ERROR(false);
    break;

  case ON_SubDVertexTag::Dart:
    if (!(m_corner_sector_angle_radians == ON_SubDSectorType::IgnoredCornerSectorAngle))
      return ON_SUBD_RETURN_ERROR(false);
    if (!(m_sector_coefficient == ON_SubDSectorType::DartSectorCoefficient(m_sector_face_count)))
      return ON_SUBD_RETURN_ERROR(false);
    break;

  default:
    return ON_SUBD_RETURN_ERROR(false);
    break;
  }

  return true;
}

ON_SubDVertexTag ON_SubDSectorType::VertexTag() const
{
  return m_vertex_tag;
}


unsigned int ON_SubDSectorType::FacetEdgeCount() const
{
  return 4;
}

double ON_SubDSectorType::CornerSectorAngleRadians() const
{
  return 
    (ON_SubDVertexTag::Corner == m_vertex_tag) 
    ? m_corner_sector_angle_radians
    : ON_SubDSectorType::ErrorCornerSectorAngle;
}

unsigned int ON_SubDSectorType::CornerSectorAngleIndex() const
{
  return (m_vertex_tag == ON_SubDVertexTag::Corner) ? m_corner_sector_angle_index : ON_UNSET_UINT_INDEX;
}

bool ON_SubDSectorType::IsSmoothSector() const
{
  return (m_vertex_tag == ON_SubDVertexTag::Smooth);
}


bool ON_SubDSectorType::IsDartSector() const
{
  return (m_vertex_tag == ON_SubDVertexTag::Dart);
}


bool ON_SubDSectorType::IsCreaseSector() const
{
  return (m_vertex_tag == ON_SubDVertexTag::Crease);
}

bool ON_SubDSectorType::IsCornerSector() const
{
  return (m_vertex_tag == ON_SubDVertexTag::Corner && m_corner_sector_angle_index <=  ON_SubDSectorType::MaximumCornerAngleIndex);
}

bool ON_SubDSectorType::IsConvexCornerSector() const
{
  return (m_vertex_tag == ON_SubDVertexTag::Corner && 2*m_corner_sector_angle_index >=  ON_SubDSectorType::MaximumCornerAngleIndex);
}

bool ON_SubDSectorType::IsConcaveCornerSector() const
{
  return (m_vertex_tag == ON_SubDVertexTag::Corner && 2*m_corner_sector_angle_index <=  ON_SubDSectorType::MaximumCornerAngleIndex);
}


unsigned int ON_SubDSectorType::EdgeCount() const
{
  if (m_sector_face_count >= ON_SubDSectorType::MinimumSectorFaceCount(m_vertex_tag))
  {
    switch (m_vertex_tag)
    {
    case ON_SubDVertexTag::Smooth:
      return m_sector_face_count;
      break;

    case ON_SubDVertexTag::Crease:
      return m_sector_face_count + 1;
      break;

    case ON_SubDVertexTag::Corner:
      return m_sector_face_count + 1;
      break;

    case ON_SubDVertexTag::Dart:
      return m_sector_face_count;
      break;

    default:
      break;
    }
  }
  return ON_SUBD_RETURN_ERROR(0);
}

unsigned int ON_SubDSectorType::FaceCount() const
{
  if ( m_sector_face_count >= ON_SubDSectorType::MinimumSectorFaceCount(m_vertex_tag))
    return m_sector_face_count;

  return ON_SUBD_RETURN_ERROR(0);
}

unsigned int ON_SubDSectorType::ComponentRingCount() const
{
  return 1 + m_sector_face_count + EdgeCount();
}

unsigned int ON_SubDSectorType::PointRingCount() const
{
  return ON_SubDSectorType::SectorPointRingCountFromFaceCount(
    m_vertex_tag,
    m_sector_face_count
    );
}

double ON_SubDSectorType::CreaseSectorTheta(
  unsigned int sector_face_count
  )
{
  if (sector_face_count >= 1) 
    return (ON_PI / ((double)sector_face_count));
  return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::ErrorSectorTheta);
}

double ON_SubDSectorType::DartSectorTheta(
  unsigned int sector_face_count
  )
{
  if (sector_face_count >= 2)
    return (ON_2PI / ((double)sector_face_count));
  return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::ErrorSectorTheta);
}

unsigned int ON_SubDSectorType::CornerAngleIndexFromCornerAngleRadians(
  double corner_sector_angle_radians
  )
{
  if (ON_SubDSectorType::IsValidCornerSectorAngleRadians(corner_sector_angle_radians))
  {
    if (corner_sector_angle_radians <= ON_SubDSectorType::MinimumCornerAngleRadians)
      return 1;
    if (corner_sector_angle_radians >= ON_SubDSectorType::MaximumCornerAngleRadians)
      return ON_SubDSectorType::MaximumCornerAngleIndex - 1;

    const double max_index = ON_SubDSectorType::MaximumCornerAngleIndex;
    unsigned int i = (unsigned int)floor(max_index*(corner_sector_angle_radians / ON_2PI));
    if (i >= ON_SubDSectorType::MaximumCornerAngleIndex - 1)
      i = ON_SubDSectorType::MaximumCornerAngleIndex - 1;
    else if (i < 1)
      i = 1;
    else if (i < ON_SubDSectorType::MaximumCornerAngleIndex-1)
    {
      double a0 = ON_SubDSectorType::AngleRadiansFromCornerAngleIndex(i);
      double a1 = ON_SubDSectorType::AngleRadiansFromCornerAngleIndex(i+1);
      double d0 = fabs(a0 - corner_sector_angle_radians);
      double d1 = fabs(a1 - corner_sector_angle_radians);
      if (d1 < d0)
        i++;
    }
    return i;
  }
  return ON_SUBD_RETURN_ERROR(ON_UNSET_UINT_INDEX);
}

double ON_SubDSectorType::AngleRadiansFromCornerAngleIndex(
  unsigned int corner_sector_angle_index
  )
{
  if (corner_sector_angle_index <= ON_SubDSectorType::MaximumCornerAngleIndex)
  {
    double corner_angle_radians;
    switch (corner_sector_angle_index)
    {
    case 0:
      corner_angle_radians = 0.0;
      break;
    case (ON_SubDSectorType::MaximumCornerAngleIndex/12):
      corner_angle_radians = ON_PI/6.0;
      break;
    case (ON_SubDSectorType::MaximumCornerAngleIndex/8):
      corner_angle_radians = 0.25*ON_PI;
      break;
    case (ON_SubDSectorType::MaximumCornerAngleIndex/6):
      corner_angle_radians = ON_PI/3.0;
      break;
    case (ON_SubDSectorType::MaximumCornerAngleIndex/4):
      corner_angle_radians = 0.5*ON_PI;
      break;
    case (ON_SubDSectorType::MaximumCornerAngleIndex/3):
      corner_angle_radians = ON_2PI/3.0;
      break;      
    case (3*ON_SubDSectorType::MaximumCornerAngleIndex*8):
      corner_angle_radians = 0.75*ON_PI;
      break;
    case (5*ON_SubDSectorType::MaximumCornerAngleIndex/12):
      corner_angle_radians = (5.0*ON_PI)/6.0;
      break;      
    case (ON_SubDSectorType::MaximumCornerAngleIndex/2):
      corner_angle_radians = ON_PI;
      break;
    case (5*ON_SubDSectorType::MaximumCornerAngleIndex/8):
      corner_angle_radians = 1.25*ON_PI;
      break;
    case (3*ON_SubDSectorType::MaximumCornerAngleIndex/2):
      corner_angle_radians = 1.5*ON_PI;
      break;
    case (7*ON_SubDSectorType::MaximumCornerAngleIndex/8):
      corner_angle_radians = 1.75*ON_PI;
      break;
    case ON_SubDSectorType::MaximumCornerAngleIndex:
      corner_angle_radians = ON_2PI;
      break;

    default:
      corner_angle_radians = ((double)(corner_sector_angle_index))*ON_SubDSectorType::MinimumCornerAngleRadians;
      break;
    }
    return corner_angle_radians;
  }
  return ON_SUBD_RETURN_ERROR(ON_UNSET_VALUE);
}

double ON_SubDSectorType::CornerSectorThetaFromCornerAngle(
    unsigned int sector_face_count,
    double corner_sector_angle_radians
    )
{
  // Concave corners are not allowed, all users of this functions should ensure that 0 <= angle <= Pi
  corner_sector_angle_radians = ON_SubDSectorType::ClampCornerSectorAngleRadians(corner_sector_angle_radians);
  if (sector_face_count >= ON_SubDSectorType::MinimumSectorFaceCount(ON_SubDVertexTag::Corner)
    && sector_face_count <= ON_SubDVertex::MaximumFaceCount
    )
  {
    unsigned int corner_index = ON_SubDSectorType::CornerAngleIndexFromCornerAngleRadians(corner_sector_angle_radians);
    if (corner_index <= ON_SubDSectorType::MaximumCornerAngleIndex)
    {
      return AngleRadiansFromCornerAngleIndex(corner_index)/((double)sector_face_count);
    }
  }
  return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::ErrorSectorTheta);
}

double ON_SubDSectorType::SectorTheta() const
{
  return m_sector_theta;
}

double ON_SubDSectorType::CornerSectorAngleRadiansFromEdges(
  ON_SubDEdgePtr sector_boundary_edge0_ptr,
  ON_SubDEdgePtr sector_boundary_edge1_ptr
  )
{
  const ON_SubDEdge* edges[2] = { ON_SUBD_EDGE_POINTER(sector_boundary_edge0_ptr.m_ptr), ON_SUBD_EDGE_POINTER(sector_boundary_edge1_ptr.m_ptr) };
  if (nullptr == edges[0] || nullptr == edges[1])
    return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::ErrorCornerSectorAngle);

  if (edges[0] == edges[1])
  {
    // occurs in nonmanifold cases like RH-49843
    // When an interior nonmanifold edge terminates a corner
    // and is the only crease edge is a sector for some
    // faces attached to the edge. 
    return ON_SubDSectorType::MaximumCornerAngleRadians;
    //return ON_SUBD_RETURN_ERROR(0.0);
  }

  ON__UINT_PTR edge_ends[2] = { ON_SUBD_EDGE_DIRECTION(sector_boundary_edge0_ptr.m_ptr), ON_SUBD_EDGE_DIRECTION(sector_boundary_edge1_ptr.m_ptr) };

  const ON_SubDVertex* V[2] = { edges[0]->m_vertex[1 - edge_ends[0]], edges[1]->m_vertex[1 - edge_ends[1]] };
  if (nullptr == V[0] || nullptr == V[1])
    return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::ErrorCornerSectorAngle);

  const ON_SubDVertex* corner_vertex = edges[0]->m_vertex[edge_ends[0]];
  if (nullptr == corner_vertex || corner_vertex != edges[1]->m_vertex[edge_ends[1]])
    return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::ErrorCornerSectorAngle);

  const double* cornerP = corner_vertex->m_P;

  const double* endP[2] = { V[0]->m_P, V[1]->m_P };

  // A = vector from cornerP to endP[0]
  ON_3dVector A(endP[0][0] - cornerP[0], endP[0][1] - cornerP[1], endP[0][2] - cornerP[2]);
  // B = vector from cornerP to endP[1]
  ON_3dVector B(endP[1][0] - cornerP[0], endP[1][1] - cornerP[1], endP[1][2] - cornerP[2]);

  // Unitize A and B
  A.Unitize();
  B.Unitize();

  // calculate angle between A and B
  // In reality, we will be lucky if we get 3 digits of precision in the trig functions
  // using the dot and cross of unitized differences.
  double cos_alpha = A*B;
  double sin_alpha = ON_CrossProduct(A, B).Length(); // NOTE WELL: sin_alpha >= 0.0 or is invalid
  if (sin_alpha < 0.0)
    return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::ErrorCornerSectorAngle);
  
  const double trig_zero_tol = 0.002;
  if (fabs(cos_alpha) <= trig_zero_tol)
    cos_alpha = 0.0;
  if (fabs(sin_alpha) <= trig_zero_tol)
    sin_alpha = 0.0;

  if ( fabs(cos_alpha*cos_alpha + sin_alpha*sin_alpha - 1.0) <= 0.125 )
  {
    // valid sin and cos and no NaNs
    const double trig_one_tol = 0.999;
    double alpha = ON_DBL_QNAN;

    if ( 0.0 == cos_alpha || fabs(sin_alpha) >= trig_one_tol)
      alpha = 0.5*ON_PI;
    else if ( 0.0 == sin_alpha || fabs(cos_alpha) >= trig_one_tol)
      alpha = (cos_alpha < 0.0) ? ON_PI : 0.0;
    else
    {
      alpha = atan2(sin_alpha, cos_alpha);

      // sin_alpha >= 0 and no NaNs means this should never happen
      if (!ON_IsValid(alpha))
        return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::ErrorCornerSectorAngle);
    }

    // sin_alpha >= 0 and no NaNs means this should always be true
    if (alpha >= 0.0 && alpha <= (1.0 + ON_EPSILON) * ON_PI)
    {
      if (alpha <= ON_SubDSectorType::MinimumCornerAngleRadians)
        alpha = ON_SubDSectorType::MinimumCornerAngleRadians;
      else if (alpha >= ON_SubDSectorType::MaximumCornerAngleRadians)
        alpha = ON_SubDSectorType::MaximumCornerAngleRadians;
      else if (fabs(alpha - ON_PI) <= 0.002)
      {
        // straight "corner"
        alpha = ON_PI;
      }

      return alpha;
    }
  }

  return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::ErrorCornerSectorAngle);
}

double ON_SubDSectorType::SectorCoefficientFromTheta(
  double sector_theta
  )
{
  if (!(sector_theta > 0.0 && sector_theta <= ON_PI))
    return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::ErrorSectorCoefficient);

  double cos_theta = cos(sector_theta);

  // If cos_theta is near 0, +1/2, -1/2, +1 or -1, then use those values
  // so the weights have the easily identified values associated with the
  // most common cases.
  const double cos_tol = 1e-6;
  const double abs_cos_theta = fabs(cos_theta);
  if (abs_cos_theta <= cos_tol)
    cos_theta = 0.0;
  else if (fabs(abs_cos_theta - 0.5) <= cos_tol)
    cos_theta = (cos_theta < 0.0) ? -0.5 : 0.5;
  else if (abs_cos_theta + cos_tol >= 1.0)
    cos_theta = (cos_theta < 0.0) ? -1.0 : 1.0;

  // Quadrangle case: w = 1/2 + 1/3*cos(theta);
  const double  wrange[2] = { 1.0 / 6.0, 5.0 / 6.0 };
  const double w = 0.5 + cos_theta / 3.0;
  if (w > wrange[0] && w < wrange[1])
    return w;
  if (w <= wrange[0])
    return wrange[0];
  if (w >= wrange[1])
    return wrange[1];

  return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::ErrorSectorCoefficient);
}

double ON_SubDSectorType::SectorCoefficient() const
{
  return m_sector_coefficient;
}

bool ON_SubDSectorType::IsValidSectorCoefficientValue(
  double coefficient_value,
  bool bAllowUnsetTaggedEndCoefficient
  )
{
  return (
    (coefficient_value >= 0.0 && coefficient_value < 1.0)
    || 
    (bAllowUnsetTaggedEndCoefficient 
      && ON_SubDSectorType::UnsetSectorCoefficient == coefficient_value)
    );
}

bool ON_SubDSectorType::IsValidCornerSectorAngleRadians(
  double corner_sector_angle_radians
  )
{
  return (corner_sector_angle_radians > 0.0 && corner_sector_angle_radians <= ON_PI);
}

double ON_SubDSectorType::ClampCornerSectorAngleRadians(
  double corner_sector_angle_radians
  )
{
  corner_sector_angle_radians = fabs(corner_sector_angle_radians);
  if ( corner_sector_angle_radians > ON_PI )
    corner_sector_angle_radians = ON_2PI - corner_sector_angle_radians;
  const double angle_tol = 0.25*(ON_PI/180.0); // 1/4 degree.
  if (corner_sector_angle_radians <= angle_tol)
    return 0;
  if (corner_sector_angle_radians >= ON_PI - angle_tol)
    return ON_PI;
  return corner_sector_angle_radians;
}


double ON_SubDSectorType::SmoothSectorCoefficient()
{
  return ON_SubDSectorType::IgnoredSectorCoefficient;
}

double ON_SubDSectorType::CreaseSectorCoefficient(
  unsigned int sector_face_count
  )
{
  if (sector_face_count < 1)
    return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::ErrorSectorCoefficient);
  double sector_theta = ON_SubDSectorType::CreaseSectorTheta(sector_face_count);
  return ON_SubDSectorType::SectorCoefficientFromTheta(sector_theta);
}

double ON_SubDSectorType::DartSectorCoefficient(
  unsigned int sector_face_count
  )
{
  if (sector_face_count < 2)
    return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::ErrorSectorCoefficient);
  double sector_theta = ON_SubDSectorType::DartSectorTheta(sector_face_count);
  return ON_SubDSectorType::SectorCoefficientFromTheta(sector_theta);
}

double ON_SubDSectorType::CornerSectorCoefficient(
  unsigned int sector_face_count,
  double corner_sector_angle_radians
  )
{
  const double sector_theta = ON_SubDSectorType::CornerSectorThetaFromCornerAngle(sector_face_count, corner_sector_angle_radians);
  if (sector_theta > 0.0 && sector_theta <= ON_PI)
    return ON_SubDSectorType::SectorCoefficientFromTheta(sector_theta);
  return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::ErrorSectorCoefficient);
}

double ON_SubDSectorType::CopyEdgeSectorCoefficient(
  const class ON_SubDEdge* edge,
  const class ON_SubDVertex* vertex,
  double error_return_value
)
{
  if ( nullptr != edge  && nullptr != vertex )
  {
    const int evi = (vertex == edge->m_vertex[0]) ? 0 : (vertex == edge->m_vertex[1] ? 1 : 2);
    if (evi < 2)
    {
      if (edge->IsSmooth())
      {
        if ( vertex->IsDartOrCreaseOrCorner() )
          return edge->m_sector_coefficient[evi];
        if ( vertex->IsSmooth() )
          return edge->m_sector_coefficient[evi];
      }
      else if ( edge->IsCrease() )
      {
        return ON_SubDSectorType::IgnoredSectorCoefficient;
      }
    }
  }

  // null pointers, unset tags, vertex and edge are not attached, 
  // or other conditions where returning a m_sector_coefficient[] 
  // is impossible or makes no sense.
  return error_return_value;
}

static int CompareUnsigned(unsigned int a, unsigned int b)
{
  if (a < b)
    return -1;
  if (a > b)
    return 1;
  return 0;
}

int ON_SubDSectorType::Compare(const ON_SubDSectorType* a, const ON_SubDSectorType* b)
{
  if ( a == b )
    return 0;
  if (nullptr == a)
    return -1;
  if (nullptr == b)
    return 1;
  
  int rc = 0;
  for (;;)
  {
    rc = CompareUnsigned((unsigned int)a->m_vertex_tag,(unsigned int)b->m_vertex_tag);
    if (0 != rc)
    {
      // bias towards valid tags
      if ( ON_SubDVertexTag::Unset == b->m_vertex_tag)
        rc = -1;
      else if ( ON_SubDVertexTag::Unset == a->m_vertex_tag)
        rc = 1;
      break;
    }
    rc = CompareUnsigned(a->m_sector_face_count,b->m_sector_face_count);
    if (0 != rc)
    {
      // bias towards valid m_sector_face_count bug small
      if ( 0 == b->m_sector_face_count)
        rc = -1;
      else if ( 0 == a->m_sector_face_count)
        rc = 1;
      break;
    }
    if (ON_SubDVertexTag::Corner == a->m_vertex_tag)
    {
      rc = CompareUnsigned(a->m_corner_sector_angle_index, b->m_corner_sector_angle_index);
      if (0 != rc)
        break;
    }

    return 0; // equal
  }

  return rc; // not equal
}


void ON_SubDSectorType::SetHash()
{
  unsigned int hash = 0;
  hash = ON_CRC32(hash,sizeof(m_vertex_tag),&m_vertex_tag);
  hash = ON_CRC32(hash,sizeof(m_sector_face_count),&m_sector_face_count);
  if ( ON_SubDVertexTag::Corner == m_vertex_tag)
    hash = ON_CRC32(hash,sizeof(m_corner_sector_angle_index),&m_corner_sector_angle_index);
  if ( 0 == hash )
    hash = 1;
  m_hash = hash;
}

unsigned int ON_SubDSectorType::SectorTypeHash() const
{
  return m_hash;
}

static bool ON_SubDSectorType_IsValidFaceCount(
  ON_SubDVertexTag vertex_tag,
  unsigned int sector_face_count
  )
{
  return (sector_face_count >= ON_SubDSectorType::MinimumSectorFaceCount(vertex_tag) && sector_face_count <= ON_SubDVertex::MaximumFaceCount);
}

static bool ON_SubDSectorType_IsValidFaceCountForCreate(
  ON_SubDVertexTag vertex_tag,
  unsigned int sector_face_count
  )
{
  return ( 0 == sector_face_count || ON_UNSET_UINT_INDEX == sector_face_count || ON_SubDSectorType_IsValidFaceCount(vertex_tag,sector_face_count));
}

ON_SubDSectorType ON_SubDSectorType::CreateSmoothSectorType(
  unsigned int sector_face_count
  )
{
  const ON_SubDVertexTag vertex_tag = ON_SubDVertexTag::Smooth;
  if (ON_SubDSectorType_IsValidFaceCountForCreate(vertex_tag,sector_face_count))
  {
    ON_SubDSectorType st;
    st.m_vertex_tag = vertex_tag;
    st.m_sector_face_count 
      = ON_SubDSectorType_IsValidFaceCount(vertex_tag,sector_face_count)
      ? sector_face_count
      : 0;
    st.m_sector_coefficient
      = (st.m_sector_face_count>0)
      ? ON_SubDSectorType::IgnoredSectorCoefficient
      :  ON_SubDSectorType::UnsetSectorCoefficient;
    st.m_sector_theta 
      = (st.m_sector_face_count>0)
      ? ON_SubDSectorType::SmoothSectorTheta
      : ON_SubDSectorType::UnsetSectorTheta;
    st.SetHash();
    return st;
  }
  return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::Empty);
}

ON_SubDSectorType ON_SubDSectorType::CreateCreaseSectorType(
  unsigned int sector_face_count
  )
{
  const ON_SubDVertexTag vertex_tag = ON_SubDVertexTag::Crease;
  if (ON_SubDSectorType_IsValidFaceCountForCreate(vertex_tag,sector_face_count))
  {
    ON_SubDSectorType st;
    st.m_vertex_tag = vertex_tag;
    st.m_sector_face_count 
      = ON_SubDSectorType_IsValidFaceCount(vertex_tag,sector_face_count)
      ? sector_face_count
      : 0;
    st.m_sector_coefficient
      = (st.m_sector_face_count>0)
      ? ON_SubDSectorType::CreaseSectorCoefficient(sector_face_count)
      : ON_SubDSectorType::UnsetSectorCoefficient;
    st.m_sector_theta 
      = (st.m_sector_face_count>0)
      ? ON_SubDSectorType::CreaseSectorTheta(sector_face_count)
      : ON_SubDSectorType::UnsetSectorTheta;
    st.SetHash();
    return st;
  }
  return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::Empty);
}


ON_SubDSectorType ON_SubDSectorType::CreateDartSectorType(
  unsigned int sector_face_count
  )
{
  const ON_SubDVertexTag vertex_tag = ON_SubDVertexTag::Dart;
  if ( ON_SubDSectorType_IsValidFaceCountForCreate(vertex_tag,sector_face_count) )
  {
    ON_SubDSectorType st;
    st.m_vertex_tag = vertex_tag;
    st.m_sector_face_count 
      = ON_SubDSectorType_IsValidFaceCount(vertex_tag,sector_face_count)
      ? sector_face_count
      : 0;
    st.m_sector_coefficient
      = (st.m_sector_face_count>0)
      ? ON_SubDSectorType::DartSectorCoefficient(sector_face_count)
      : ON_SubDSectorType::UnsetSectorCoefficient;
    st.m_sector_theta 
      = (st.m_sector_face_count>0)
      ? ON_SubDSectorType::DartSectorTheta(sector_face_count)
      : ON_SubDSectorType::UnsetSectorTheta;
    st.SetHash();
    return st;
  }
  return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::Empty);
}



ON_SubDSectorType ON_SubDSectorType::CreateCornerSectorType(
  unsigned int sector_face_count,
  double corner_sector_angle_radians
  )
{
  if (ON_SubDSectorType::ErrorCornerSectorAngle == corner_sector_angle_radians)
    return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::Empty);

  if (ON_SubDSectorType::UnsetCornerSectorAngle != corner_sector_angle_radians)
  {
    if (ON_UNSET_VALUE == corner_sector_angle_radians)
      corner_sector_angle_radians = ON_SubDSectorType::UnsetCornerSectorAngle;
    else
      corner_sector_angle_radians = ON_SubDSectorType::ClampCornerSectorAngleRadians(corner_sector_angle_radians);
  }

  if (ON_SubDSectorType::UnsetCornerSectorAngle == corner_sector_angle_radians
    || ON_SubDSectorType::IsValidCornerSectorAngleRadians(corner_sector_angle_radians)
    )
  {
    const ON_SubDVertexTag vertex_tag = ON_SubDVertexTag::Corner;
    if (ON_SubDSectorType_IsValidFaceCountForCreate(vertex_tag,sector_face_count))
    {
      unsigned int corner_sector_angle_index 
        = (ON_SubDSectorType::UnsetCornerSectorAngle == corner_sector_angle_radians)
        ? 0
        : ON_SubDSectorType::CornerAngleIndexFromCornerAngleRadians(corner_sector_angle_radians);
      if (corner_sector_angle_index <= ON_SubDSectorType::MaximumCornerAngleIndex)
      {
        ON_SubDSectorType st;
        st.m_vertex_tag = vertex_tag;
        st.m_sector_face_count 
          = ON_SubDSectorType_IsValidFaceCount(vertex_tag,sector_face_count)
          ? sector_face_count
          : 0;
        st.m_corner_sector_angle_index = (unsigned char)corner_sector_angle_index;
        st.m_corner_sector_angle_radians = corner_sector_angle_radians;
        st.m_sector_theta 
          = (st.m_sector_face_count > 0 && ON_SubDSectorType::UnsetCornerSectorAngle != corner_sector_angle_radians)
          ? ON_SubDSectorType::CornerSectorThetaFromCornerAngle(sector_face_count, corner_sector_angle_radians)
          : ON_SubDSectorType::UnsetSectorTheta;
        st.m_sector_coefficient
          = (st.m_sector_face_count > 0 && ON_SubDSectorType::UnsetCornerSectorAngle != corner_sector_angle_radians)
          ? ON_SubDSectorType::CornerSectorCoefficient( sector_face_count, corner_sector_angle_radians)
          : ON_SubDSectorType::UnsetSectorCoefficient;
        st.SetHash();
        return st;
      }
    }
  }
  return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::Empty);
}


ON_SubDSectorType ON_SubDSectorType::Create(
  ON_SubDVertexTag vertex_tag,
  unsigned int sector_face_count,
  double corner_sector_angle_radians
  )
{
  if (ON_SubDVertexTag::Unset == vertex_tag && 0 == sector_face_count)
    return ON_SubDSectorType::Empty;

  switch (vertex_tag)
  {
  case ON_SubDVertexTag::Smooth:
    return ON_SubDSectorType::CreateSmoothSectorType(sector_face_count);
    break;
  case ON_SubDVertexTag::Crease:
    return ON_SubDSectorType::CreateCreaseSectorType(sector_face_count);
    break;
  case ON_SubDVertexTag::Corner:
    return ON_SubDSectorType::CreateCornerSectorType(sector_face_count,corner_sector_angle_radians);
    break;
  case ON_SubDVertexTag::Dart:
    return ON_SubDSectorType::CreateDartSectorType(sector_face_count);
    break;
  default:
    break;
  }

  return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::Empty);
}

ON_SubDSectorType ON_SubDSectorType::Create(
  const ON_SubDSectorIterator& sit
  )
{
  const ON_SubDVertex* center_vertex = sit.CenterVertex();

  if (nullptr == center_vertex )
    return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::Empty);

  ON_SubDSectorIterator local_sit(sit);

  const ON_SubDVertexTag vertex_tag = center_vertex->m_vertex_tag;

  const ON_SubDFace* face0;
  ON_SubDEdgePtr edge0ptr = ON_SubDEdgePtr::Null;
  if (ON_SubDVertexTag::Smooth == vertex_tag)
  {
    face0 = local_sit.CurrentFace();
    if (nullptr == face0 )
      return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::Empty);
  }
  else
  {
    face0 = nullptr;
    if (nullptr == local_sit.IncrementToCrease(-1))
      return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::Empty);
    edge0ptr = local_sit.CurrentEdgePtr(0);
  }
  
  const unsigned int vertex_face_count = center_vertex->m_face_count;
  unsigned int sector_face_count = 0;
  while(sector_face_count < vertex_face_count)
  {
    sector_face_count++;
    if ( sector_face_count > vertex_face_count )
      return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::Empty);
    if (face0 == local_sit.NextFace(ON_SubDSectorIterator::StopAt::AnyCrease))
    {
      double corner_sector_angle_radians 
          = (ON_SubDVertexTag::Corner == vertex_tag)
          ? ON_SubDSectorType::CornerSectorAngleRadiansFromEdges(edge0ptr,local_sit.CurrentEdgePtr(0))
          : 0.0;
      return ON_SubDSectorType::Create(vertex_tag,sector_face_count,corner_sector_angle_radians);
    }
  }

  return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::Empty);
}

ON_SubDSectorType ON_SubDSectorType::Create(
  const class ON_SubDFace* face,
  unsigned int face_vertex_index
  )
{
  if (nullptr == face)
    return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::Empty);
  if (face_vertex_index >= face->m_edge_count)
    return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::Empty);
  ON_SubDSectorIterator sit;
  sit.Initialize(face,0,face_vertex_index);
  return ON_SubDSectorType::Create(sit);
}

ON_SubDSectorType ON_SubDSectorType::Create(
  const class ON_SubDFace* face,
  const class ON_SubDVertex* vertex
  )
{
  if (nullptr == face)
    return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::Empty);
  if (nullptr == vertex)
    return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::Empty);
  unsigned int face_vertex_index = face->VertexIndex(vertex);
  if (face_vertex_index >= face->m_edge_count)
    return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::Empty);
  return ON_SubDSectorType::Create(face,face_vertex_index);
}


ON_SubDSectorType ON_SubDSectorType::Create(
  const class ON_SubDEdge* edge,
  unsigned int edge_vertex_index
  )
{
  if (nullptr == edge)
    return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::Empty);
  const ON_SubDVertex* vertex = edge->Vertex(edge_vertex_index);
  if (nullptr == vertex)
    return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::Empty);
  const ON_SubDFace* face = edge->Face(0);
  if (nullptr == face)
    return ON_SUBD_RETURN_ERROR(ON_SubDSectorType::Empty);

  return ON_SubDSectorType::Create(face,vertex);
}
