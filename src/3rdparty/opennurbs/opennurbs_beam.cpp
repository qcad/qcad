#include "opennurbs.h"

bool ON_Extrusion::IsValidPolyCurveProfile( const ON_PolyCurve& polycurve, ON_TextLog* text_log )
{
  const bool bAllowGaps = true;
  bool rc = polycurve.IsValid(bAllowGaps,text_log) ? true : false;
  if (!rc)
    return false;

  const int profile_count = polycurve.Count();

  if ( profile_count < 1 )
  {
    if ( text_log )
    {
      text_log->Print("polycurve has < 1 segments.\n");
    }
    return false;
  }

  if ( 2 != polycurve.Dimension() )
  {
    if ( 3 != polycurve.Dimension() )
    {
      if ( text_log )
      {
        text_log->Print("polycurve dimension = %d (should be 2).\n",polycurve.Dimension());
      }
      return false;
    }
    ON_BoundingBox bbox = polycurve.BoundingBox();
    if ( !bbox.IsValid() )
    {
      if ( text_log )
      {
        text_log->Print("polycurve.BoundingBox() is not valid.\n");
      }
      return false;
    }
    if ( !( 0.0 == bbox.m_min.z) || !(0.0 == bbox.m_max.z) )
    {
      if ( text_log )
      {
        text_log->Print("polycurve.BoundingBox() z values are not both 0.0.\n");
      }
      return false;
    }
  }

  if ( 1 == profile_count )
    return true;

  if ( profile_count > 1 )
  {
    for ( int i = 0; i < profile_count; i++ )
    {
      const ON_Curve* segment = polycurve.SegmentCurve(i);
      if ( 0 == segment )
      {
        if ( text_log )
        {
          text_log->Print("polycurve.SegmentCurve(%d) is null.\n",i);
        }
        return false;
      }
      if ( !segment->IsClosed() )
      {
        if ( text_log )
        {
          text_log->Print("polycurve.SegmentCurve(%d) is not closed.\n",i);
        }
        return false;
      }
      if ( segment->Domain() != polycurve.SegmentDomain(i) )
      {
        if ( text_log )
        {
          text_log->Print("polycurve.Segment(%d).Domain() does not match polycurve.SegmentDomain(%d).\n",i,i);
        }
        return false;
      }
    }
  }
  return true;
}

bool ON_Extrusion::CleanupPolyCurveProfile( ON_PolyCurve& polycurve )
{
  if ( !ON_Extrusion::IsValidPolyCurveProfile(polycurve) )
  {
    // see if we can fix it
    int i;
    const int old_count = polycurve.Count();
    if ( old_count <= 1 )
      return false;

    // make segments 2d 
    for ( i = 0; i < old_count; i++ )
    {
      ON_Curve* old_segment = polycurve.SegmentCurve(i);
      if ( 0 == old_segment )
        return false;
      if ( 2 != old_segment->Dimension() && !old_segment->ChangeDimension(2) )
        return false;
    }

    // make segment domains match the polycurve's m_t[] array
    polycurve.SynchronizeSegmentDomains();

    // make each segment a closed curve
    ON_SimpleArray<ON_PolyCurve*> new_polycurves(old_count);
    ON_SimpleArray<ON_Curve*> new_segments(old_count);
    ON_PolyCurve* new_segment = 0;
    bool rc = true;
    for ( i = 0; i < old_count && rc; i++ )
    {
      ON_Curve* old_segment = polycurve.SegmentCurve(i);
      if ( old_segment->IsClosed() )
      {
        if ( 0 != new_segment )
        {
          rc = false;
          break;
        }
        new_segments.Append(old_segment);
      }
      else if ( 0 == new_segment )
      {
        new_segment = new ON_PolyCurve();
        new_polycurves.Append(new_segment);
        new_segment->Append(old_segment);
      }
      else
      {
        new_segment->Append(old_segment);
        if ( new_segment->HasGap() )
        {
          rc = false;
          break;
        }
        if ( new_segment->IsClosed() )
        {
          new_segments.Append(new_segment);
          new_segment = 0;
        }
      }
    }

    if ( 0 != new_segment )
    {
      rc = false;
    }

    if ( !rc )
    {
      // unable to fix polycurve. Delete the new stuff we allocated.
      for ( i = 0; i < new_polycurves.Count(); i++ )
      {
        new_segment = new_polycurves[i];
        if ( new_segment )
        {
          for ( int j =  new_segment->Count()-1; j >= 0; j-- )
          {
            new_segment->HarvestSegment(j); // do not delete parts of input polycurve
          }
          delete new_segment;
        }
      }
      return false;
    }

    for ( i = 0; i < new_polycurves.Count(); i++ )
    {
      new_polycurves[i]->RemoveNesting();
    }

    for ( i = old_count-1; i >= 0; i-- )
    {
      polycurve.HarvestSegment(i);
      polycurve.Remove(i);
    }
    for ( i = 0; i < new_segments.Count(); i++ )
    {
      polycurve.Append(new_segments[i]);
    }
  }
  else
  {
    polycurve.ChangeDimension(2);
  }
  return true;
}


bool ON_GetEndCapTransformation(ON_3dPoint P, ON_3dVector T, ON_3dVector U, 
                                const ON_3dVector* Normal, 
                                ON_Xform& xform,
                                ON_Xform* scale2d,
                                ON_Xform* rot3d
                                )
{
  if ( scale2d )
    scale2d->Identity();
  if ( rot3d )
    rot3d->Identity();
  if ( !T.IsUnitVector() && !T.Unitize() )
    return false;
  if ( !U.IsUnitVector() && !U.Unitize() )
    return false;
  ON_3dVector N(0.0,0.0,0.0);
  if ( Normal )
  {
    N = *Normal;
    if ( !N.IsUnitVector() && !N.Unitize() )
      N.Zero();
  }

  ON_Plane p0;
  p0.origin = P;
  p0.zaxis = T;
  p0.yaxis = U;
  p0.xaxis = ON_CrossProduct(U,T);
  if ( !p0.xaxis.IsUnitVector() )
    p0.xaxis.Unitize();
  p0.UpdateEquation();
  xform.Rotation(ON_xy_plane,p0);
  if ( rot3d )
    *rot3d = xform;
  if ( N.z > ON_Extrusion::m_Nz_min && N.IsUnitVector() )
  {
    //double cosa = T.x*N.x + T.y*N.y + T.z*N.z; // N is relative to T
    double cosa = N.z; // N is relative to xy plane.
    for(;;)
    {
      //ON_3dVector A = ON_CrossProduct(T,N); // N is relative to T
      ON_3dVector A(-N.y,N.x,0.0); // N is relative to xy plane.
      if ( !A.IsValid() )
        break;
      double sina = A.Length();
      if ( !ON_IsValid(sina) )
        break;
      if ( !A.Unitize() )
        break;
      //ON_3dVector B = ON_CrossProduct(N,A);
      ON_3dVector B(-N.z*A.x,-N.z*A.y,N.x*A.y-N.y*A.x);
      if ( !B.IsUnitVector() && !B.Unitize() )
        break;
      
      // A,B,N is a right handed orthonormal frame
      
      // S is a non-uniform scale that maps A to A and perpA to 1/cosa*perpA.
      // The scale distorts the profile so that after it is rotated
      // into the miter plane, the projection of the rotated profile
      // onto the xy-plane matches the original profile.
      ON_Xform S(0.0);
      const double c = 1.0 - 1.0/cosa;
      S.m_xform[0][0] = 1.0 - c*A.y*A.y;
      S.m_xform[0][1] = c*A.x*A.y;

      S.m_xform[1][0] = S.m_xform[0][1];
      S.m_xform[1][1] = 1.0 - c*A.x*A.x;

      S.m_xform[2][2] = 1.0;

      S.m_xform[3][3] = 1.0;
      if (scale2d)
        *scale2d = S;

      // R rotates the profile plane so its normal is equal to N
      ON_Xform R;
      R.Rotation(sina,cosa,A,ON_origin);
      if ( rot3d )
        *rot3d = xform*R;

      xform = xform*R*S;
      break;
    }
  }
  return true;
}

static void ON_ExtrusionInitializeHelper(ON_Extrusion& extrusion)
{
  extrusion.m_path.from.Zero();
  extrusion.m_path.to.Zero();
  extrusion.m_t.m_t[0] = 0.0;
  extrusion.m_t.m_t[1] = 1.0;
  extrusion.m_up.Zero();
  extrusion.m_profile_count = 0;
  extrusion.m_profile = 0;
  extrusion.m_bCap[0] = false;
  extrusion.m_bCap[1] = false;
  extrusion.m_bHaveN[0] = false;
  extrusion.m_bHaveN[1] = false;
  extrusion.m_N[0].Zero();
  extrusion.m_N[1].Zero();
  extrusion.m_path_domain.m_t[0] = 0.0;
  extrusion.m_path_domain.m_t[1] = 1.0;
  extrusion.m_bTransposed = false;
}

static void ON_ExtrusionCopyHelper(const ON_Extrusion& src,ON_Extrusion& dst)
{
  if ( &src != &dst )
  {
    if ( dst.m_profile )
    {
      delete dst.m_profile;
      dst.m_profile = 0;
    }
    dst.m_path = src.m_path;
    dst.m_t = src.m_t;
    dst.m_up = src.m_up;
    dst.m_profile_count = src.m_profile_count;
    dst.m_profile = src.m_profile 
                  ? src.m_profile->DuplicateCurve() 
                  : 0;
    dst.m_bCap[0] = src.m_bCap[0];
    dst.m_bCap[1] = src.m_bCap[1];
    dst.m_bHaveN[0] = src.m_bHaveN[0];
    dst.m_bHaveN[1] = src.m_bHaveN[1];
    dst.m_N[0] = src.m_N[0];
    dst.m_N[1] = src.m_N[1];
    dst.m_path_domain = src.m_path_domain;
    dst.m_bTransposed  = src.m_bTransposed;
  }
}

bool ON_Extrusion::SetPath(ON_3dPoint A, ON_3dPoint B)
{
  double distAB = 0.0;
  bool rc =    A.IsValid() && B.IsValid() 
            && (distAB = A.DistanceTo(B)) > ON_ZERO_TOLERANCE;
  if (rc)
  {
    m_path.from = A;
    m_path.to = B;
    m_t.Set(0.0,1.0);
    m_path_domain.Set(0.0,distAB);
  }
  return rc;
}

bool ON_Extrusion::SetPathAndUp( ON_3dPoint A, ON_3dPoint B, ON_3dVector up )
{
  double distAB = 0.0;

  bool rc =    up.IsValid() 
            && up.Length() > ON_ZERO_TOLERANCE
            && A.IsValid() 
            && B.IsValid() 
            && (distAB = A.DistanceTo(B)) > ON_ZERO_TOLERANCE;

  if (rc)
  {
    ON_3dVector D = A-B;
    D.Unitize();
    double d = up*D;
    if ( !up.IsUnitVector() || fabs(d) > distAB*ON_SQRT_EPSILON*0.015625 )
    {
      // need to make up perpindicular to the line segment
      // and unitize.
      D.Unitize();
      up = up - d*D;
      up.Unitize();
      // validate up
      d = up*D;
      rc = ( up.IsUnitVector() && fabs(d) <= ON_SQRT_EPSILON );
    }

    if (rc)
    {
      m_path.from = A;
      m_path.to = B;
      m_t.Set(0.0,1.0);
      m_path_domain.Set(0.0,distAB);
      m_up = up;
    }
  }

  return rc;
}

int ON_Extrusion::PathParameter() const
{
  return m_bTransposed ? 0 : 1;
}

int ON_Extrusion::ProfileParameter() const
{
  return m_bTransposed ? 1 : 0;
}

ON_3dPoint ON_Extrusion::PathStart() const
{
  ON_3dPoint P(ON_UNSET_POINT);
  const double t = m_t.m_t[0];
  if ( 0.0 <= t && t <= 1.0 && m_path.IsValid() )
    P = m_path.PointAt(t);
  return P;
}

ON_3dPoint ON_Extrusion::PathEnd() const
{
  ON_3dPoint P(ON_UNSET_POINT);
  const double t = m_t.m_t[1];
  if ( 0.0 <= t && t <= 1.0 && m_path.IsValid() )
    P = m_path.PointAt(t);
  return P;
}

ON_3dVector ON_Extrusion::PathTangent() const
{
  ON_3dVector T(ON_UNSET_VECTOR);
  if ( m_path.IsValid() )
    T = m_path.Tangent();
  return T;
}

void ON_Extrusion::Destroy()
{
  if ( m_profile)
  {
    delete m_profile;
    m_profile = 0;
  }
  ON_ExtrusionInitializeHelper(*this);
  DestroyRuntimeCache();
  PurgeUserData();
}

bool ON_Extrusion::SetMiterPlaneNormal(ON_3dVector N, int end)
{
  bool rc = false;
  if ( end >= 0 && end <= 1 )
  {
    if (    N.IsValid() 
         && N.z > ON_Extrusion::m_Nz_min
         && (N.IsUnitVector() || N.Unitize())
       )
    {
      if (fabs(N.x) <= ON_SQRT_EPSILON && fabs(N.y) <= ON_SQRT_EPSILON)
        N.Set(0.0,0.0,1.0);
      m_N[end] = N;
      m_bHaveN[end] = (N.z != 1.0);
      rc = true;
    }
    else if ( N.IsZero() || ON_UNSET_VECTOR == N )
    {
      m_bHaveN[end] = false;
      rc = true;
    }
  }
  return rc;
}

void ON_Extrusion::GetMiterPlaneNormal(int end, ON_3dVector& N) const
{
  if ( end >= 0 && end <= 1 && m_bHaveN[end] )
    N = m_N[end];
  else
    N.Set(0.0,0.0,1.0);
}

int ON_Extrusion::IsMitered() const
{
  int rc = 0;
  if ( m_bHaveN[0] && m_N[0].IsUnitVector() && m_N[0].z > m_Nz_min && (m_N[0].x != 0.0 || m_N[0].y != 0.0) )
    rc += 1;
  if ( m_bHaveN[1] && m_N[1].IsUnitVector() && m_N[1].z > m_Nz_min && (m_N[1].x != 0.0 || m_N[1].y != 0.0) )
    rc += 2;
  return rc;
}

int ON_Extrusion::IsCapped() const
{
  // 0 = no caps, 1 = bottom cap, 2 = top cap, 3 = both caps

  if ( !m_bCap[0] && !m_bCap[1] )
    return 0;

  if ( m_profile_count < 1 || 0 == m_profile )
    return 0;

  if ( 1 == m_profile_count )
  {
    if ( !m_profile->IsClosed() )
      return 0;
  }
  else if ( m_profile_count > 1 )
  {
    const ON_PolyCurve* p = ON_PolyCurve::Cast(m_profile);
    if ( 0 == p )
      return 0;
    const ON_Curve* outer_profile = p->SegmentCurve(0);
    if ( 0 == outer_profile )
      return 0;
    if ( !outer_profile->IsClosed() )
      return 0;
  }

  return (m_bCap[0] ? (m_bCap[1] ? 3 : 1) : 2);
}


bool ON_Extrusion::IsSolid() const
{
  if ( !m_bCap[0] || !m_bCap[1] )
    return false;
  return 3 == IsCapped();
}

bool ON_Extrusion::GetPathPlane( double s, ON_Plane& plane ) const
{
  ON_Plane p;
  p.origin = ON_3dPoint::Origin;
  p.zaxis = PathTangent();
  p.yaxis = m_up;
  p.xaxis = ON_CrossProduct(p.yaxis,p.zaxis);
  if ( !p.xaxis.Unitize() )
    return false;
  if ( !p.yaxis.Unitize() )
    return false;
  p.UpdateEquation();
  if ( !p.IsValid() )
  {
    p.yaxis = ON_CrossProduct(p.zaxis,p.xaxis);
    p.yaxis.Unitize();
    if ( !p.IsValid() )
      return false;
  }
  p.origin = m_path.PointAt(m_t.ParameterAt(s));
  p.UpdateEquation();
  plane = p;
  return plane.IsValid();
}

bool ON_Extrusion::GetProfilePlane( double s, ON_Plane& plane ) const
{
  ON_Plane p;
  p.origin = ON_3dPoint::Origin;
  p.zaxis = PathTangent();
  p.yaxis = m_up;
  p.xaxis = ON_CrossProduct(p.yaxis,p.zaxis);
  if ( !p.xaxis.Unitize() )
    return false;
  if ( !p.yaxis.Unitize() )
    return false;
  p.UpdateEquation();
  if ( !p.IsValid() )
  {
    p.yaxis = ON_CrossProduct(p.zaxis,p.xaxis);
    p.yaxis.Unitize();
    if ( !p.IsValid() )
      return false;
  }
  if (    (!m_bHaveN[0] || (0.0 == m_N[0].x && 0.0 == m_N[0].y)) 
       && (!m_bHaveN[1] || (0.0 == m_N[1].x && 0.0 == m_N[1].y)) 
     )
  {
    p.origin = m_path.PointAt(m_t.ParameterAt(s));
    p.UpdateEquation();
    plane = p;
  }
  else
  {
    ON_Xform xform;
    if ( !GetProfileTransformation(s,xform) )
      return false;
    if (!p.Transform(xform))
      return false;
    plane = p;
  }
  return plane.IsValid();
}


bool ON_Extrusion::GetProfileTransformation( double s, ON_Xform& xform ) const
{
  //const ON_3dVector* N = (end?(m_bHaveN[1]?&m_N[1]:0):(m_bHaveN[0]?&m_N[0]:0));
  const ON_3dVector T = m_path.Tangent();
  if ( 0.0 == s )
  {
    return ON_GetEndCapTransformation(m_path.PointAt(m_t.m_t[0]),T,m_up,m_bHaveN[0]?&m_N[0]:0,xform,0,0);
  }
  if ( 1.0 == s )
  {
    return ON_GetEndCapTransformation(m_path.PointAt(m_t.m_t[1]),T,m_up,m_bHaveN[1]?&m_N[1]:0,xform,0,0);
  }
  ON_Xform xform0, xform1;
  if ( !ON_GetEndCapTransformation(m_path.PointAt(m_t.m_t[0]),T,m_up,m_bHaveN[0]?&m_N[0]:0,xform0,0,0) )
    return false;
  if ( !ON_GetEndCapTransformation(m_path.PointAt(m_t.m_t[1]),T,m_up,m_bHaveN[1]?&m_N[1]:0,xform1,0,0) )
    return false;

  const double s0 = 1.0-s;
  xform.m_xform[0][0] = s0*xform0.m_xform[0][0] + s*xform1.m_xform[0][0];
  xform.m_xform[0][1] = s0*xform0.m_xform[0][1] + s*xform1.m_xform[0][1];
  xform.m_xform[0][2] = s0*xform0.m_xform[0][2] + s*xform1.m_xform[0][2];
  xform.m_xform[0][3] = s0*xform0.m_xform[0][3] + s*xform1.m_xform[0][3];
  xform.m_xform[1][0] = s0*xform0.m_xform[1][0] + s*xform1.m_xform[1][0];
  xform.m_xform[1][1] = s0*xform0.m_xform[1][1] + s*xform1.m_xform[1][1];
  xform.m_xform[1][2] = s0*xform0.m_xform[1][2] + s*xform1.m_xform[1][2];
  xform.m_xform[1][3] = s0*xform0.m_xform[1][3] + s*xform1.m_xform[1][3];
  xform.m_xform[2][0] = s0*xform0.m_xform[2][0] + s*xform1.m_xform[2][0];
  xform.m_xform[2][1] = s0*xform0.m_xform[2][1] + s*xform1.m_xform[2][1];
  xform.m_xform[2][2] = s0*xform0.m_xform[2][2] + s*xform1.m_xform[2][2];
  xform.m_xform[2][3] = s0*xform0.m_xform[2][3] + s*xform1.m_xform[2][3];
  xform.m_xform[3][0] = s0*xform0.m_xform[3][0] + s*xform1.m_xform[3][0];
  xform.m_xform[3][1] = s0*xform0.m_xform[3][1] + s*xform1.m_xform[3][1];
  xform.m_xform[3][2] = s0*xform0.m_xform[3][2] + s*xform1.m_xform[3][2];
  xform.m_xform[3][3] = s0*xform0.m_xform[3][3] + s*xform1.m_xform[3][3];

  return true;
}

static bool ProfileHelper( int desired_orientation, ON_Curve* profile )
{
  // desired_orientation  0: outer profile that can be open or closed.
  // desired_orientation  1: outer profile that must be closed
  // desired_orientation -1: inner profile

  if ( 0 == profile )
  {
    ON_ERROR("ON_Extrusion::Set/Add Profile - null input curve pointer.");
    return false;
  }
  ON_BoundingBox bbox = profile->BoundingBox();
  if ( !bbox.IsValid() )
  {
    ON_ERROR("ON_Extrusion::Set/Add Profile - profile->BoundingBox() failed.");
    return false;
  }
  if ( fabs(bbox.m_min.z) > ON_ZERO_TOLERANCE || fabs(bbox.m_max.z) > ON_ZERO_TOLERANCE )
  {
    ON_ERROR("ON_Extrusion::Set/Add Profile - profile->BoundingBox() is not in the world xy plane.");
    return false;
  }
  if ( !profile->ChangeDimension(2) )
  {
    ON_ERROR("ON_Extrusion::Set/Add Profile - profile->ChangeDimension(2) failed.");
    return false;
  }

  if ( profile->IsClosed() )
  {
    int profile_orientation = ON_ClosedCurveOrientation(*profile,0);
    switch(desired_orientation)
    {
    case 1:
    case 0:
      if ( -1 == profile_orientation )
      {
        if ( !profile->Reverse() )
        {
          ON_ERROR("ON_Extrusion::SetOuterProfile() - profile->Reverse() failed.");
          return false;
        }
        profile_orientation = 1;
      }
      if ( 1 == desired_orientation && 1 != profile_orientation )
      {
        ON_ERROR("ON_Extrusion::SetOuterProfile() - profile has wrong orientation.");
        return false;
      }
      break;
    case -1:
      if ( 1 == profile_orientation )
      {
        if ( !profile->Reverse() )
        {
          ON_ERROR("ON_Extrusion::AddInnerProfile() - profile->Reverse() failed.");
          return false;
        }
        profile_orientation = -1;
      }
      if ( -1 != profile_orientation )
      {
        ON_ERROR("ON_Extrusion::AddInnerProfile() - profile has wrong orientation.");
        return false;
      }
      break;
    default:
      {
        ON_ERROR("ON_Extrusion::Set/Add Profile - invalid desired_orientation parameter.");
        return false;
      }
      break;
    }
  }
  else if ( 0 != desired_orientation )
  {
    ON_ERROR("ON_Extrusion::Set/Add Profile - profile is an open curve.");
    return false;
  }

  ON_PolyCurve* polycurve = ON_PolyCurve::Cast(profile);
  if ( 0 != polycurve )
  {
    polycurve->RemoveNesting();
    for ( int i = 0; i < polycurve->Count(); i++ )
    {
      ON_Curve* segment = polycurve->SegmentCurve(i);
      if ( 0 == segment )
      {
        ON_ERROR("ON_Extrusion::Set/Add Profile - ON_PolyCurve has null segment.");
        return false;
      }
      if ( !segment->SetDomain( polycurve->SegmentDomain(i) ) )
      {
        ON_ERROR("ON_Extrusion::Set/Add Profile - segment->SetDomain() failed.");
        return false;
      }
    }
  }

  return true;
}

bool ON_Extrusion::SetOuterProfile( ON_Curve* outer_profile, bool bCap )
{
  if ( 0 != m_profile )
  {
    ON_ERROR("ON_Extrusion::SetOuterProfile() called when m_profile is already not null.");
    return false;
  }

  if ( !ProfileHelper( 0, outer_profile ) )
    return false;

  m_profile_count = 1;
  m_profile = outer_profile;

  if ( outer_profile->IsClosed() )
  {
    m_bCap[0] = m_bCap[1] = (bCap ? true : false);
  }
  else
  {
    m_bCap[0] = m_bCap[1] = false;
  }

  return true;
}

bool ON_Extrusion::AddInnerProfile( ON_Curve* inner_profile )
{
  if ( m_profile_count < 1 )
  {
    ON_ERROR("ON_Extrusion::AddInnerProfile() called when m_profile_count < 1.");
    return false;
  }
  if ( 0 == m_profile )
  {
    ON_ERROR("ON_Extrusion::AddInnerProfile() called when m_profile is null.");
    return false;
  }

  if ( 1 == m_profile_count && !m_profile->IsClosed() )
  {
    ON_ERROR("ON_Extrusion::AddInnerProfile() called when outer profile is not closed.");
    return false;
  }

  ON_PolyCurve* polycurve = ON_PolyCurve::Cast(m_profile);
  if (  m_profile_count > 1 && 0 == polycurve )
  {
    ON_ERROR("ON_Extrusion::AddInnerProfile() called when  m_profile_count > 1 but m_profile is not an ON_PolyCurve.");
    return false;
  }
  if ( m_profile_count > 1 && m_profile_count != polycurve->Count() )
  {
    ON_ERROR("ON_Extrusion::AddInnerProfile() called when  m_profile_count > 1 but m_profile_count != m_profile->Count().");
    return false;
  }

  if ( !ProfileHelper( -1, inner_profile ) )
    return false;

  if ( 1 == m_profile_count )
  {
    if ( 0 != polycurve )
    {
      polycurve->RemoveNesting();
    }

    if ( 0 == polycurve || 1 != polycurve->Count() )
    {
      polycurve = new ON_PolyCurve();
      polycurve->Append(m_profile);
      m_profile = polycurve;
    }
  }

  polycurve->Append(inner_profile);
  if ( polycurve->SegmentDomain(m_profile_count) != inner_profile->Domain() )
  {
    inner_profile->SetDomain( polycurve->SegmentDomain(m_profile_count) );

    // If inner_profile is itself a polycurve, clean up segment domains
    // so we don't get bugs caused by fuzz as we adjust parameters when evaluating.
    polycurve = ON_PolyCurve::Cast(inner_profile);
    if ( 0 != polycurve )
    {
      polycurve->SynchronizeSegmentDomains();
    }
  }
  m_profile_count++;

 
  return true;
}

const ON_PolyCurve* ON_Extrusion::PolyProfile() const
{
  if ( m_profile_count <= 1 )
    return 0;
  const ON_PolyCurve* poly_profile = ON_PolyCurve::Cast(m_profile);
  return (0 != poly_profile && m_profile_count == poly_profile->Count() ) ? poly_profile : 0;
}

const ON_Curve* ON_Extrusion::Profile(int profile_index) const
{
  if ( 0 == profile_index && 1 == m_profile_count )
    return m_profile;
  if ( profile_index < 0 || profile_index > m_profile_count )
    return 0;
  const ON_PolyCurve* poly_profile = PolyProfile();
  return ( 0 != poly_profile ? poly_profile->SegmentCurve(profile_index) : 0 );
}

ON_Curve* ON_Extrusion::Profile3d( ON_COMPONENT_INDEX ci ) const
{
  double s = ON_UNSET_VALUE;
  if ( ON_COMPONENT_INDEX::extrusion_bottom_profile == ci.m_type )
    s = 0.0;
  else if ( ON_COMPONENT_INDEX::extrusion_top_profile == ci.m_type )
    s = 1.0;
  else
    return 0;
  return Profile3d(ci.m_index,s);
}

ON_Curve* ON_Extrusion::Profile3d( int profile_index, double s ) const
{
  if ( profile_index < 0 || !(0.0 <= s && s <= 1.0) || 0 == m_profile )
    return 0;

  ON_Xform xform;
  if ( !GetProfileTransformation(s,xform) )
    return 0;

  const ON_Curve* profile2d = Profile(profile_index);
  if ( 0 == profile2d )
    return 0;

  ON_Curve* profile3d = profile2d->DuplicateCurve();
  if ( 0 == profile3d )
    return 0;

  if (    !profile3d->ChangeDimension(3) 
       || !profile3d->Transform(xform)
     )
  {
    delete profile3d;
    return 0;
  }

  return profile3d;
}


int ON_Extrusion::ProfileCount() const
{
  if ( !m_profile )
    return 0;

  if ( m_profile_count < 1 )
    return 0;

  if ( m_profile_count > 1 )
  {
    const ON_PolyCurve* polycurve = ON_PolyCurve::Cast(m_profile);
    if ( 0 == polycurve )
      return 0;
    if ( polycurve->Count() != m_profile_count )
      return 0;
  }

  return m_profile_count;
}


int ON_Extrusion::GetProfileCurves( ON_SimpleArray< const ON_Curve* >& profile_curves ) const
{
  if ( !m_profile )
    return 0;

  if ( m_profile_count < 1 )
    return 0;

  if ( 1 == m_profile_count )
  {
    profile_curves.Reserve(profile_curves.Count()+1);
    profile_curves.Append(m_profile);
  }
  else
  {
    const ON_PolyCurve* polycurve = ON_PolyCurve::Cast(m_profile);
    if ( 0 == polycurve )
      return 0;
    if ( polycurve->Count() != m_profile_count )
      return 0;
    const int count0 = profile_curves.Count();
    profile_curves.Reserve(count0+m_profile_count);
    for ( int i = 0; i < m_profile_count; i++ )
    {
      const ON_Curve* segment = polycurve->SegmentCurve(i);
      if ( 0 == segment )
      {
        profile_curves.SetCount(count0);
        return 0;
      }
      profile_curves.Append(segment);
    }
  }

  return m_profile_count;
}


const double ON_Extrusion::m_Nz_min = 1.0/64.0;

const double ON_Extrusion::m_path_length_min = ON_ZERO_TOLERANCE;

ON_OBJECT_IMPLEMENT(ON_Extrusion,ON_Surface,"36F53175-72B8-4d47-BF1F-B4E6FC24F4B9");

ON_Extrusion::ON_Extrusion()
{
  ON_ExtrusionInitializeHelper(*this);
}

ON_Extrusion::ON_Extrusion(const ON_Extrusion& src) : ON_Surface(src), m_profile(0)
{
  ON_ExtrusionCopyHelper(src,*this);
}

ON_Extrusion::~ON_Extrusion()
{
  if ( m_profile)
  {
    delete m_profile;
  }
}

ON_Extrusion& ON_Extrusion::operator=(const ON_Extrusion& src)
{
  if ( this != &src )
  {
    Destroy();
    ON_Surface::operator=(src);
    ON_ExtrusionCopyHelper(src,*this);
  }
  return *this;
}

static
void ON_Extrusion_IsNotValidMessage( ON_TextLog* text_log, const char* msg )
{
  // this is a good place for a breakpoint
  if ( text_log && msg && msg[0] )
    text_log->Print("%s\n",msg);
}

ON_BOOL32 ON_Extrusion::IsValid( ON_TextLog* text_log ) const
{
  // check m_profile
  if ( m_profile_count < 1 )
  {
    ON_Extrusion_IsNotValidMessage(text_log,"m_profile_count < 1.");
    return false;
  }
  if ( !m_profile )
  {
    ON_Extrusion_IsNotValidMessage(text_log,"m_profile is NULL.");
    return false;
  }
  if ( m_profile_count > 1 )
  {
    const ON_PolyCurve* c = ON_PolyCurve::Cast(m_profile);
    if ( 0 == c )
    {
      ON_Extrusion_IsNotValidMessage(text_log,"m_profile_count > 1 but m_profile is not an ON_PolyCurve.");
      return false;
    }
    if ( m_profile_count != c->Count() )
    {
      ON_Extrusion_IsNotValidMessage(text_log,"m_profile_count > 1 but m_profile_count != m_profile->SegmentCount().");
      return false;
    }

    if ( !ON_Extrusion::IsValidPolyCurveProfile(*c,text_log) )
    {
      ON_Extrusion_IsNotValidMessage(text_log,"m_profile is not a valid ON_PolyCurve.");
      return false;
    }
    for ( int i = 0; i < m_profile_count; i++ )
    {
      const ON_Curve* segment = c->SegmentCurve(i);
      if ( 0 == segment )
      {
        ON_Extrusion_IsNotValidMessage(text_log,"m_profile_count > 1 but a m_profile_count->SegmentCurve() is null.");
        return false;
      }
      if ( !segment->IsClosed() )
      {
        ON_Extrusion_IsNotValidMessage(text_log,"m_profile_count > 1 but a m_profile_count->SegmentCurve() is not closed.");
        return false;
      }
    }
  }
  else if ( !m_profile->IsValid(text_log) )
  {
    ON_Extrusion_IsNotValidMessage(text_log,"m_profile is not valid.");
    return false;
  }

  // check m_path
  if ( !m_path.IsValid() )
  {
    ON_Extrusion_IsNotValidMessage(text_log,"m_path is not valid.");
    return false;
  }
  ON_3dVector D = m_path.to - m_path.from;
  double len = D.Length();
  if ( !ON_IsValid(len) || len <= 0.0 )
  {
    ON_Extrusion_IsNotValidMessage(text_log,"m_path has zero length.");
    return false;
  }
  if ( !ON_IsValid(len) || len <= ON_Extrusion::m_path_length_min )
  {
    if ( text_log )
      text_log->Print("m_path has zero length <= ON_Extrusion::m_path_length_min.");
    return false;
  }
  if ( !D.Unitize() || !D.IsUnitVector() )
  {
    ON_Extrusion_IsNotValidMessage(text_log,"m_path has zero direction.");
    return false;
  }
  
  // check m_t
  if ( !(0.0 <= m_t.m_t[0] && m_t.m_t[0] < m_t.m_t[1] && m_t.m_t[1] <= 1.0) )
  {
    ON_Extrusion_IsNotValidMessage(text_log,"m_t does not satisfy 0<=m_t[0]<m_t[1]<=1");
    return false;
  }

  // check m_up
  if ( !m_up.IsUnitVector() )
  {
   ON_Extrusion_IsNotValidMessage(text_log,"m_up is not a unit vector.");
    return false;
  }
  len = m_up*D;
  if ( fabs(len) > ON_SQRT_EPSILON )
  {
    ON_Extrusion_IsNotValidMessage(text_log,"m_up is not perpindicular to m_path.");
    return false;
  }

  // validate ends
  if ( m_bHaveN[0] )
  {
    if ( !m_N[0].IsUnitVector() )
    {
      ON_Extrusion_IsNotValidMessage(text_log,"m_N[0] is not a unit vector.");
      return false;
    }
    if ( !(m_N[0].z > ON_Extrusion::m_Nz_min) )
    {
      ON_Extrusion_IsNotValidMessage(text_log,"m_N[0].z is too small (<=ON_Extrusion::m_Nz_min) or negative");
      return false;
    }
  }
  if ( m_bHaveN[1] )
  {
    if ( !m_N[1].IsUnitVector() )
    {
      ON_Extrusion_IsNotValidMessage(text_log,"m_N[1] is not a unit vector.");
      return false;
    }
    if ( !(m_N[1].z > ON_Extrusion::m_Nz_min) )
    {
      ON_Extrusion_IsNotValidMessage(text_log,"m_N[1].z is too small (<=ON_Extrusion::m_Nz_min) or negative");
      return false;
    }
  }

  return true;
}

void ON_Extrusion::Dump( ON_TextLog& text_log ) const
{
  text_log.Print("Path: ");
  text_log.Print(m_path.PointAt(m_t[0]));
  text_log.Print(" ");
  text_log.Print(m_path.PointAt(m_t[1]));
  text_log.Print("\n");
  text_log.Print("Up: ");
  text_log.Print(m_up);
  text_log.Print("\n");
  text_log.Print("Profile:\n");
  text_log.PushIndent();
  if ( !m_profile )
    text_log.Print("NULL");
  else
    m_profile->Dump(text_log);
  text_log.PopIndent();
  return;
}

unsigned int ON_Extrusion::SizeOf() const
{
  unsigned int sz = sizeof(*this) - sizeof(ON_Surface);
  if ( m_profile )
    sz += m_profile->SizeOf();
  return sz;
}

ON__UINT32 ON_Extrusion::DataCRC(ON__UINT32 current_remainder) const
{
  if ( m_profile )
    current_remainder = m_profile->DataCRC(current_remainder);
  current_remainder = ON_CRC32(current_remainder,sizeof(m_path),&m_path);
  current_remainder = ON_CRC32(current_remainder,sizeof(m_t),&m_t);
  current_remainder = ON_CRC32(current_remainder,sizeof(m_up),&m_up);
  current_remainder = ON_CRC32(current_remainder,sizeof(m_bHaveN[0]), &m_bHaveN[0]);
  current_remainder = ON_CRC32(current_remainder,sizeof(m_bHaveN[1]), &m_bHaveN[1]);
  current_remainder = ON_CRC32(current_remainder,sizeof(m_N[0]), &m_N[0]);
  current_remainder = ON_CRC32(current_remainder,sizeof(m_N[1]), &m_N[1]);
  current_remainder = ON_CRC32(current_remainder,sizeof(m_path_domain), &m_path_domain);
  current_remainder = ON_CRC32(current_remainder,sizeof(m_bTransposed), &m_bTransposed);
  current_remainder = ON_CRC32(current_remainder,sizeof(m_profile_count), &m_profile_count);
  current_remainder = ON_CRC32(current_remainder,sizeof(m_bCap[0]), &m_bCap[0]);
  current_remainder = ON_CRC32(current_remainder,sizeof(m_bCap[1]), &m_bCap[1]);
  if ( m_profile )
    current_remainder = m_profile->DataCRC(current_remainder);
  return current_remainder;
}

ON_BOOL32 ON_Extrusion::Write(
       ON_BinaryArchive& binary_archive
     ) const
{
  bool rc = binary_archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,2);
  if (!rc)
    return false;
  for (;;)
  {
    rc = binary_archive.WriteObject(m_profile);
    if (!rc) break;
    rc = binary_archive.WriteLine(m_path);
    if (!rc) break;
    rc = binary_archive.WriteInterval(m_t);
    if (!rc) break;
    rc = binary_archive.WriteVector(m_up);
    if (!rc) break;
    rc = binary_archive.WriteBool(m_bHaveN[0]);
    if (!rc) break;
    rc = binary_archive.WriteBool(m_bHaveN[1]);
    if (!rc) break;
    rc = binary_archive.WriteVector(m_N[0]);
    if (!rc) break;
    rc = binary_archive.WriteVector(m_N[1]);
    if (!rc) break;
    rc = binary_archive.WriteInterval(m_path_domain);
    if (!rc) break;
    rc = binary_archive.WriteBool(m_bTransposed);
    if (!rc) break;
    // 1.1 
    rc = binary_archive.WriteInt(m_profile_count);
    if (!rc) break;
    // 1.2
    rc = binary_archive.WriteBool(m_bCap[0]);
    if (!rc) break;
    rc = binary_archive.WriteBool(m_bCap[1]);
    if (!rc) break;

    break;
  }
  if ( !binary_archive.EndWrite3dmChunk() )
    rc = false;
  return rc;
}


ON_BOOL32 ON_Extrusion::Read(
       ON_BinaryArchive& binary_archive
     )
{
  Destroy();
  int major_version = 0;
  int minor_version = 0;
  bool rc = binary_archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
  if (!rc)
    return false;
  for (;;)
  {
    rc = (1 == major_version);
    if (!rc) break;
    ON_Object* obj = 0;
    rc = (1==binary_archive.ReadObject(&obj));
    if (!rc) break;
    if ( obj )
    {
      m_profile = ON_Curve::Cast(obj);
      if ( !m_profile )
      {
        delete obj;
        rc = false;
        break;
      }
    }
    rc = binary_archive.ReadLine(m_path);
    if (!rc) break;
    rc = binary_archive.ReadInterval(m_t);
    if (!rc) break;
    rc = binary_archive.ReadVector(m_up);
    if (!rc) break;
    rc = binary_archive.ReadBool(&m_bHaveN[0]);
    if (!rc) break;
    rc = binary_archive.ReadBool(&m_bHaveN[1]);
    if (!rc) break;
    rc = binary_archive.ReadVector(m_N[0]);
    if (!rc) break;
    rc = binary_archive.ReadVector(m_N[1]);
    if (!rc) break;
    rc = binary_archive.ReadInterval(m_path_domain);
    if (!rc) break;
    rc = binary_archive.ReadBool(&m_bTransposed);
    if (!rc) break;

    // set profile count if extrusion was read from an old file.
    m_profile_count = (0 != m_profile) ? 1 : 0;

    if ( minor_version >= 1 )
    {
      // 1.1 
      rc = binary_archive.ReadInt(&m_profile_count);
      if (!rc) break;

      if ( minor_version >= 2 )
      {
        // 1.2
        rc = binary_archive.ReadBool(&m_bCap[0]);
        if (!rc) break;
        rc = binary_archive.ReadBool(&m_bCap[1]);
        if (!rc) break;
      }
    }

    if ( minor_version < 2 )
    {
      const ON_Curve* outer_profile = Profile(0);
      if ( 0 != outer_profile && outer_profile->IsClosed() )
      {
        m_bCap[0] = m_bCap[1] = true;
      }
    }

    break;
  }
  if ( !binary_archive.EndRead3dmChunk() )
    rc = false;
  return rc;
}

ON::object_type ON_Extrusion::ObjectType() const
{
  return ON::extrusion_object;
}



int ON_Extrusion::Dimension() const
{
  return 3;
}

static 
bool GetBoundingBoxHelper(const ON_Extrusion& extrusion, 
                          ON_BoundingBox& bbox,
                          const ON_Xform* xform
                          )
{
  // input bbox = profile curve bounding box.
  ON_3dPoint corners[8];
  bbox.m_min.z = 0.0;
  bbox.m_max.z = 0.0;
  corners[0] = corners[1] = bbox.m_min;
  corners[1].x = bbox.m_max.x;
  corners[2] = corners[3] = bbox.m_max;
  corners[3].x = bbox.m_min.x;
  corners[4] = corners[0];
  corners[5] = corners[1];
  corners[6] = corners[2];
  corners[7] = corners[3];

  const ON_3dVector T = extrusion.m_path.Tangent();
  ON_Xform xform0;
  if ( !extrusion.GetProfileTransformation(0,xform0) )
    return false;
  ON_Xform xform1;
  if ( !extrusion.GetProfileTransformation(1,xform1) )
    return false;
  if ( xform && !xform->IsIdentity() )
  {
    xform0 = (*xform)*xform0;
    xform1 = (*xform)*xform1;
  }
  corners[0] = xform0*corners[0];
  corners[1] = xform0*corners[1];
  corners[2] = xform0*corners[2];
  corners[3] = xform0*corners[3];
  corners[4] = xform1*corners[4];
  corners[5] = xform1*corners[5];
  corners[6] = xform1*corners[6];
  corners[7] = xform1*corners[7];
  bbox.Set(3,0,8,3,&corners[0].x,false);
  return true;
}

ON_BOOL32 ON_Extrusion::GetBBox(double* boxmin,double* boxmax,int bGrowBox) const
{
  bool rc = false;
  if ( m_path.IsValid() && m_profile )
  {
    ON_BoundingBox bbox;
    if ( m_profile->GetTightBoundingBox(bbox) && GetBoundingBoxHelper(*this,bbox,0) )
    {
      rc = true;
      if ( bGrowBox )
      {
        bGrowBox =  ( boxmin[0] <= boxmax[0] 
                      && boxmin[1] <= boxmax[1] 
                      && boxmin[2] <= boxmax[2]
                      && ON_IsValid(boxmax[0]) 
                      && ON_IsValid(boxmax[1]) 
                      && ON_IsValid(boxmax[2]));
      }
      if ( bGrowBox )
      {
        if ( boxmin[0] > bbox.m_min.x ) boxmin[0] = bbox.m_min.x;
        if ( boxmin[1] > bbox.m_min.y ) boxmin[1] = bbox.m_min.y;
        if ( boxmin[2] > bbox.m_min.z ) boxmin[2] = bbox.m_min.z;
        if ( boxmax[0] < bbox.m_max.x ) boxmax[0] = bbox.m_max.x;
        if ( boxmax[1] < bbox.m_max.y ) boxmax[1] = bbox.m_max.y;
        if ( boxmax[2] < bbox.m_max.z ) boxmax[2] = bbox.m_max.z;
      }
      else
      {
        boxmin[0] = bbox.m_min.x;
        boxmin[1] = bbox.m_min.y;
        boxmin[2] = bbox.m_min.z;
        boxmax[0] = bbox.m_max.x;
        boxmax[1] = bbox.m_max.y;
        boxmax[2] = bbox.m_max.z;
      }
    }
  }
  return rc;
}


bool ON_Extrusion::GetTightBoundingBox(ON_BoundingBox& tight_bbox, int bGrowBox, const ON_Xform* xform ) const
{
  bool rc = false;
  if ( m_path.IsValid() && m_profile )
  {
    ON_BoundingBox bbox;
    if ( m_profile->GetTightBoundingBox(bbox) && GetBoundingBoxHelper(*this,bbox,xform) )
    {
      if ( bGrowBox )
        tight_bbox.Union(bbox);
      else
        tight_bbox = bbox;
      rc = true;
    }
  }
  return rc;
}

ON_BOOL32 ON_Extrusion::Transform( const ON_Xform& xform )
{
  bool rc = false;
  if ( !m_path.IsValid() )
    return false;

  ON_3dPoint Q0 = xform*m_path.from;
  ON_3dPoint Q1 = xform*m_path.to;
  if ( !Q0.IsValid() )
    return false;
  if ( !Q1.IsValid() )
    return false;
  ON_3dVector T = m_path.Tangent();
  ON_3dVector QT = Q1-Q0;
  if ( !QT.Unitize() )
    return false;
  if ( fabs(QT*T - 1.0) <= ON_SQRT_EPSILON )
    QT = T;
  ON_3dVector X = ON_CrossProduct(m_up,T);
  if ( !X.IsUnitVector() && !X.Unitize() )
    return false;
  
  ON_3dPoint X0 = xform*(m_path.from + X);
  ON_3dPoint Y0 = xform*(m_path.from + m_up);
  ON_3dPoint X1 = xform*(m_path.to + X);
  ON_3dPoint Y1 = xform*(m_path.to + m_up);

  ON_3dVector QU = Y0-Q0;
  if ( !QU.Unitize() )
    return false;
  if ( fabs(QU*m_up - 1.0) <= ON_SQRT_EPSILON )
    QU = m_up;
  if ( !(fabs(QU*QT) <= ON_SQRT_EPSILON) )
    return false;

  double s0 = Q0.DistanceTo(X0);
  double t0 = Q0.DistanceTo(Y0);
  double s1 = Q1.DistanceTo(X1);
  double t1 = Q1.DistanceTo(Y1);
  if ( fabs(s0-s1) > ON_SQRT_EPSILON*(s0+s1) )
    return false;
  if ( fabs(t0-t1) > ON_SQRT_EPSILON*(t0+t1) )
    return false;
  if ( fabs(s0-1.0) <= ON_SQRT_EPSILON )
    s0 = 1.0;
  if ( fabs(t0-1.0) <= ON_SQRT_EPSILON )
    t0 = 1.0;
  if ( fabs(s0-t0) <= ON_SQRT_EPSILON*(s0+t0) )
  {
    if ( 1.0 == s0 )
      t0 = 1.0;
    else
      s0 = t0;
  }
  m_path.from = Q0;
  m_path.to = Q1;
  m_up = QU;
  if ( s0 != 1.0 || t0 != 1.0 )
  {
    // scale profile curve
    ON_Xform profile_scale(1.0);
    profile_scale.m_xform[0][0] = s0;
    profile_scale.m_xform[1][1] = t0;
    if ( s0 != t0 && !m_profile->IsDeformable() )
    {
      ON_NurbsCurve* c = m_profile->NurbsCurve();
      if ( c )
      {
        c->CopyUserData(*m_profile);
        if ( !m_profile->Transform(profile_scale) )
        {
          if( c->Transform(profile_scale) )
          {
            rc = true;
            delete m_profile;
            m_profile = c;
          }
        }
        else
        {
          delete c;
        }
      }
    }
    else
    {
      rc = m_profile->Transform(profile_scale)?true:false;
    }
  }

  return true;
}

class CMyBrepIsSolidSetter : public ON_Brep
{
public:
  void SetIsSolid(int i) {m_is_solid = i;}
};

struct ON_Extrusion_BrepForm_FaceInfo
{
  void Init();
  const ON_Extrusion* m_extrusion_srf;
  int m_face_index;
  int m_vid[4];
  int m_eid[4];
  ON_BOOL32 m_bRev3d[4];
  bool m_bClosedProfile;
  int m_profile_orientation;
  int m_cap_trim_index_count;
  int m_cap_trim_index[2]; 
};

void ON_Extrusion_BrepForm_FaceInfo::Init()
{
  m_extrusion_srf = 0;
  m_face_index = -1;
  m_vid[0] = m_vid[1] = m_vid[2] = m_vid[3] = -1;
  m_eid[0] = m_eid[1] = m_eid[2] = m_eid[3] = -1;
  m_bRev3d[0] = m_bRev3d[1] = m_bRev3d[2] = m_bRev3d[3] = 0;
  m_bClosedProfile = false;
  m_profile_orientation = 0;
  m_cap_trim_index_count = 0;
  m_cap_trim_index[0] = m_cap_trim_index[1] = -1;
}

ON_Brep* ON_Extrusion::BrepForm( ON_Brep* brep ) const
{
  return BrepForm(brep,true);
}

ON_Brep* ON_Extrusion::BrepForm( ON_Brep* brep, bool bSplitKinkyFaces ) const
{
  if ( brep )
    brep->Destroy();

  ON_SimpleArray<const ON_Curve*> profile_curves;
  const int profile_count = GetProfileCurves(profile_curves );
  if ( profile_count < 1 || profile_count != profile_curves.Count() )
    return 0;

  // get end cap transformation information

  const ON_3dVector T = m_path.Tangent();
  if ( !T.IsUnitVector() )
    return 0;

  ON_Xform xform0(1.0), xform1(1.0), scale0(1.0), scale1(1.0), rot0(1.0), rot1(1.0);
  if ( !ON_GetEndCapTransformation(m_path.PointAt(m_t.m_t[0]),T,m_up,m_bHaveN[0]?&m_N[0]:0,xform0,&scale0,&rot0) )
    return 0;

  if ( !ON_GetEndCapTransformation(m_path.PointAt(m_t.m_t[1]),T,m_up,m_bHaveN[1]?&m_N[1]:0,xform1,&scale1,&rot1) )
    return 0;

  ON_Brep* newbrep = brep ? brep : ON_Brep::New();

  if ( 0 == newbrep )
    return 0;

  int is_capped = IsCapped();
  if ( is_capped < 0 || is_capped > 3 )
    is_capped = 0; // don't let future changes or bugs in IsCapped() crash this code.

  int cap_count = (3==is_capped) ? 2 : (0 != is_capped ? 1 : 0);

  newbrep->m_S.Reserve(profile_count + cap_count);
  newbrep->m_F.Reserve(profile_count + cap_count);
  newbrep->m_L.Reserve((1 + cap_count)*profile_count);
  newbrep->m_C2.Reserve((4 + cap_count)*profile_count);
  newbrep->m_T.Reserve((4 + cap_count)*profile_count);
  newbrep->m_C3.Reserve(4*profile_count);
  newbrep->m_E.Reserve(4*profile_count);

  bool bHaveKinkyProfile = false;
  // Do NOT change ON_DEFAULT_ANGLE_TOLERANCE to another value.
  // See comments in CRhinoDoc::AddObject() for details.
  const double kink_angle_tol = ON_DEFAULT_ANGLE_TOLERANCE;
  const double cos_kink_angle_tol = cos(kink_angle_tol);

  ON_SimpleArray< struct ON_Extrusion_BrepForm_FaceInfo > finfo(profile_count);
  for ( int profile_index = 0; profile_index < profile_count; profile_index++ )
  {
    const ON_Curve* profile_segment = profile_curves[profile_index];
    if ( 0 == profile_segment )
    {
      if (newbrep != brep )
        delete newbrep;
      return 0;
    }

    ON_Curve* newprofile = profile_segment->DuplicateCurve();
    if ( 0 == newprofile )
    {
      if (newbrep != brep )
        delete newbrep;
      return 0;
    }

    if ( bSplitKinkyFaces && !bHaveKinkyProfile )
    {
      double t0 = ON_UNSET_VALUE;
      double t1 = ON_UNSET_VALUE;
      if ( !newprofile->GetDomain(&t0,&t1) 
           || !ON_IsValid(t0)
           || !ON_IsValid(t1) 
           || !(t0 < t1)
         )
      {
        delete newprofile;
        if (newbrep != brep )
          delete newbrep;
        return 0;
      }
      if (  newprofile->GetNextDiscontinuity(
                            ON::G1_continuous,
                            t0,t1,&t0,
                            0,0,
                            cos_kink_angle_tol,
                            ON_SQRT_EPSILON
                            ) )
      {
        bHaveKinkyProfile = true;
      }
    }

    // create an extrusion that represents a single surface
    // to store in the brep.
    ON_Extrusion* extrusion = new ON_Extrusion();
    if ( 0 == extrusion )
    {
      delete newprofile;
      if (newbrep != brep )
        delete newbrep;
      return 0;
    }
    extrusion->m_path = m_path;
    extrusion->m_t = m_t;
    extrusion->m_up = m_up;
    extrusion->m_profile_count = 1;
    extrusion->m_profile = newprofile;
    extrusion->m_bCap[0] = false;
    extrusion->m_bCap[1] = false;
    extrusion->m_bHaveN[0] = m_bHaveN[0];
    extrusion->m_bHaveN[1] = m_bHaveN[1];
    extrusion->m_N[0] = m_N[0];
    extrusion->m_N[1] = m_N[1];
    extrusion->m_path_domain = m_path_domain;
    extrusion->m_bTransposed = m_bTransposed;

    ON_Extrusion_BrepForm_FaceInfo& fi = finfo.AppendNew();
    fi.Init();
    fi.m_extrusion_srf = extrusion;
    fi.m_bClosedProfile = extrusion->m_profile->IsClosed() ? true : false;
    fi.m_profile_orientation = ( fi.m_bClosedProfile )
                             ? ON_ClosedCurveOrientation(*extrusion->m_profile,0)
                             : 0;
    if ( 0 != is_capped 
         && fi.m_profile_orientation != (0 == profile_index ? 1 : -1)
       )
    {
      is_capped = 0;
      cap_count = 0;
    }

    const ON_BrepFace* face = newbrep->NewFace(extrusion,fi.m_vid,fi.m_eid,fi.m_bRev3d);
    if ( 0 == face )
    {
      delete newprofile;
      if (newbrep != brep )
        delete newbrep;
      return 0;
    }
    fi.m_face_index = face->m_face_index;

    extrusion = 0;

    if ( 0 == is_capped )
      continue;

    const ON_BrepLoop* loop = (1 == face->LoopCount()) ? face->OuterLoop() : 0;
    if ( 0 == loop || 4 != loop->TrimCount() )
    {
      is_capped = 0;
      cap_count = 0;
      continue;
    }
    
    int capti[2] = {-1,-1};
    int seam_count = 0;
    int capti_count = 0;
    int other_count = 0;
    for ( int lti = 0; lti < 4; lti++ )
    {
      const ON_BrepTrim* trim = loop->Trim(lti);
      if ( 0 == trim )
      {
        is_capped = 0;
        cap_count = 0;
        break;
      }
      switch ( trim->m_type )
      {
      case ON_BrepTrim::seam:
        seam_count++;
        break;
      case ON_BrepTrim::boundary:
        if ( capti_count < 2 )
          capti[capti_count] = trim->m_trim_index;
        capti_count++;
        break;
      default:
        other_count++;
        break;
      }
    }
    if (   0 != other_count
        || 2 != seam_count
        || 2 != capti_count 
        || ON_Surface::S_iso != newbrep->m_T[capti[0]].m_iso 
        || ON_Surface::N_iso != newbrep->m_T[capti[1]].m_iso 
        )
    {
      is_capped = 0;
      cap_count = 0;
    }
    else
    {
      fi.m_cap_trim_index_count = 2;
      fi.m_cap_trim_index[0] = capti[0];
      fi.m_cap_trim_index[1] = capti[1];
    }
  }

  if ( profile_count != finfo.Count() )
  {
    is_capped = 0;
    cap_count = 0;
  }

  while ( is_capped > 0 && cap_count == ((3 == is_capped) ? 2 : 1) )
  {
    // Add end caps.
    const ON_Extrusion_BrepForm_FaceInfo& fi0 = finfo[0];

    if ( 2 != fi0.m_cap_trim_index_count )
    {
      is_capped = 0;
      cap_count = 0;
      break;
    }
    ON_BrepEdge* outer_edge0 = newbrep->m_T[fi0.m_cap_trim_index[0]].Edge();
    ON_BrepEdge* outer_edge1 = newbrep->m_T[fi0.m_cap_trim_index[1]].Edge();
    if ( 0 == outer_edge0 || 0 == outer_edge1 )
    {
      is_capped = 0;
      cap_count = 0;
      break;
    }

    int bReverseProfile = (-1 == fi0.m_profile_orientation);
    if ( bReverseProfile )
      newbrep->FlipFace(newbrep->m_F[fi0.m_face_index]);

    int cap_fi[2] = {-1,-1};
    ON_NurbsCurve* c20 = 0;
    ON_NurbsCurve* c21 = 0;

    c20 = fi0.m_extrusion_srf->m_profile->NurbsCurve();
    if ( !c20 )
    {
      break;
    }
    if ( bReverseProfile )
      c20->Reverse();
    c20->ChangeDimension(2);

    if ( 2 == is_capped )
    {
      c21 = c20;
      c20 = 0;
    }
    else if ( 3 == is_capped )
    {
      c21 = c20->Duplicate();
      if ( !c21 )
      {
        delete c20;
        c20 = 0;
        break;
      }
    }

    newbrep->m_S.Reserve(newbrep->m_S.Count()+cap_count);
    newbrep->m_F.Reserve(newbrep->m_F.Count()+cap_count);
    newbrep->m_C2.Reserve(newbrep->m_C2.Count()+cap_count*profile_count);
    newbrep->m_L.Reserve(newbrep->m_L.Count()+cap_count*profile_count);
    newbrep->m_T.Reserve(newbrep->m_T.Count()+cap_count*profile_count);

    if ( 0 != c20 )
    {
      if ( !scale0.IsIdentity() )
        c20->Transform(scale0);
      ON_BoundingBox bbox;
      if ( !c20->GetTightBoundingBox(bbox) )
        bbox = c20->BoundingBox();
      ON_Interval u0(bbox.m_min.x,bbox.m_max.x);
      ON_Interval v0(bbox.m_min.y,bbox.m_max.y);
      double d = u0.Length()*0.125; u0.m_t[0] -= d; u0.m_t[1] += d;
      d = v0.Length()*0.125; v0.m_t[0] -= d; v0.m_t[1] += d;

      ON_PlaneSurface* plane0 = new ON_PlaneSurface(ON_xy_plane);
      plane0->SetExtents(0,u0,true);
      plane0->SetExtents(1,v0,true);
      if ( !rot0.IsIdentity() )
        plane0->Transform(rot0);

      const int c2i = newbrep->AddTrimCurve(c20);
      c20 = 0;
      const int si = newbrep->AddSurface(plane0);
      plane0 = 0;
      ON_BrepFace& face0 = newbrep->NewFace(si);
      face0.m_bRev = true;
      ON_BrepLoop& loop0 = newbrep->NewLoop(ON_BrepLoop::outer,face0);
      ON_BrepTrim& trim0 = newbrep->NewTrim(*outer_edge0, bReverseProfile,loop0,c2i);
      trim0.m_tolerance[0] = trim0.m_tolerance[1] = 0.0;
      cap_fi[0] = face0.m_face_index;
    }

    if ( 0 != c21 )
    {
      if ( !scale1.IsIdentity() )
        c21->Transform(scale1);
      ON_BoundingBox bbox;
      if ( !c21->GetTightBoundingBox(bbox) )
        bbox = c21->BoundingBox();
      ON_Interval u1(bbox.m_min.x,bbox.m_max.x);
      ON_Interval v1(bbox.m_min.y,bbox.m_max.y);
      double d = u1.Length()*0.125; u1.m_t[0] -= d; u1.m_t[1] += d;
      d = v1.Length()*0.125; v1.m_t[0] -= d; v1.m_t[1] += d;

      ON_PlaneSurface* plane1 = new ON_PlaneSurface(ON_xy_plane);
      plane1->SetExtents(0,u1,true);
      plane1->SetExtents(1,v1,true);
      if ( !rot1.IsIdentity() )
        plane1->Transform(rot1);

      const int c2i = newbrep->AddTrimCurve(c21);
      c21 = 0;
      const int si = newbrep->AddSurface(plane1);
      plane1 = 0;
      ON_BrepFace& face1 = newbrep->NewFace(si);
      ON_BrepLoop& loop1 = newbrep->NewLoop(ON_BrepLoop::outer,face1);
      ON_BrepTrim& trim1 = newbrep->NewTrim(*outer_edge1,!bReverseProfile,loop1,c2i);
      trim1.m_tolerance[0] = trim1.m_tolerance[1] = 0.0;
      cap_fi[1] = face1.m_face_index;
    }

    for ( int profile_index = 1; profile_index < profile_count; profile_index++ )
    {
      c20 = 0;
      c21 = 0;

      // add interior holes
      const ON_Extrusion_BrepForm_FaceInfo& fi = finfo[profile_index];

      if ( 2 != fi.m_cap_trim_index_count )
      {
        is_capped = 0;
        cap_count = 0;
        break;
      }
      ON_BrepEdge* inner_edge0 = newbrep->m_T[fi.m_cap_trim_index[0]].Edge();
      ON_BrepEdge* inner_edge1 = newbrep->m_T[fi.m_cap_trim_index[1]].Edge();
      if ( 0 == inner_edge0 || 0 == inner_edge1 )
      {
        is_capped = 0;
        cap_count = 0;
        break;
      }

      int bReverseProfile = (1 == fi.m_profile_orientation);
      if ( bReverseProfile )
        newbrep->FlipFace(newbrep->m_F[fi.m_face_index]);

      c20 = fi.m_extrusion_srf->m_profile->NurbsCurve();
      if ( !c20 )
      {
        break;
      }
      if ( bReverseProfile )
        c20->Reverse();
      c20->ChangeDimension(2);
      c21 = 0;
      if ( 2 == is_capped )
      {
        c21 = c20;
        c20 = 0;
      }
      else if ( 3 == is_capped )
      {
        c21 = c20->Duplicate();
        if ( !c21 )
        {
          delete c20;
          c20 = 0;
          break;
        }
      }

      if ( 0 != c20 )
      {
        if ( !scale0.IsIdentity() )
          c20->Transform(scale0);
        const int c2i = newbrep->AddTrimCurve(c20);
        c20 = 0;
        ON_BrepLoop& inner_loop0 = newbrep->NewLoop(ON_BrepLoop::inner,newbrep->m_F[cap_fi[0]]);
        ON_BrepTrim& inner_trim0 = newbrep->NewTrim(*inner_edge0, bReverseProfile,inner_loop0,c2i);
        inner_trim0.m_tolerance[0] = inner_trim0.m_tolerance[1] = 0.0;
      }

      if ( 0 != c21 )
      {
        if ( !scale1.IsIdentity() )
          c21->Transform(scale1);
        const int c2i = newbrep->AddTrimCurve(c21);
        c21 = 0;
        ON_BrepLoop& inner_loop1 = newbrep->NewLoop(ON_BrepLoop::inner,newbrep->m_F[cap_fi[1]]);
        ON_BrepTrim& inner_trim1 = newbrep->NewTrim(*inner_edge1,!bReverseProfile,inner_loop1,c2i);
        inner_trim1.m_tolerance[0] = inner_trim1.m_tolerance[1] = 0.0;
      }
    }

    if ( 2 == cap_count && 3 == is_capped )
      ((CMyBrepIsSolidSetter*)newbrep)->SetIsSolid(1);

    break;
  }

  if ( 0 == is_capped || 0 == cap_count )
  {
    // remove any partially constructed caps
    for ( int face_index = newbrep->m_F.Count()-1; face_index >= profile_count; face_index-- )
      newbrep->DeleteFace(newbrep->m_F[face_index],true);
  }

#if defined(ON_DEBUG)
  if ( !newbrep->IsValid() )
  {
    newbrep->IsValid(); // breakpoint here
  }
#endif

  if ( newbrep && bSplitKinkyFaces && bHaveKinkyProfile)
  {
    newbrep->SplitKinkyFaces(kink_angle_tol,true);
#if defined(ON_DEBUG)
    if ( !newbrep->IsValid() )
    {
      newbrep->IsValid(); // breakpoint here
    }
#endif
  }

  if ( newbrep )
  {
    ON_BoundingBox brep_bbox = newbrep->BoundingBox();
    ON_BoundingBox extr_bbox = BoundingBox();
    ON_BoundingBox bbox;
    bbox.Intersection(brep_bbox,extr_bbox);
  }

  return newbrep;
}

static void KinkEvalHelper( const ON_Curve* profile,
                            double kminus, double kink_param, double kplus,
                            ON_3dPoint& P, ON_3dVector& T0, ON_3dVector& T1,
                            int* hint
                            )
{
  ON_3dPoint Q;
  profile->EvTangent(kink_param,Q,T0,-1,hint);
  profile->EvTangent(kink_param,P,T1,+1,hint);
  if ( T0*T1 >= 1.0-ON_SQRT_EPSILON)
  {
    // When the curve is a polycurve or proxycurve,
    // sometimes the reparameterization adds
    // enough fuzz to the kink_param that we have
    // to use the minus/plus approach.
    profile->EvTangent(kminus,Q,T0,-1,hint);
    profile->EvTangent(kplus, Q,T1,+1,hint);
  }
  P.z = 0.0;
  T0.z = 0.0;
  T1.z = 0.0;
}

static bool FindNextKinkHelper( const ON_Curve* profile,
                                double t0, double t1,
                                double* kminus, double* kink_param, double* kplus
                               )
{
  bool rc = profile->GetNextDiscontinuity(ON::G1_continuous,t0,t1,kink_param);
  if (rc && *kink_param > t0 && *kink_param < t1 )
  {
    profile->GetParameterTolerance(*kink_param,kminus,kplus);
  }
  else
  {
    rc = false;
    *kink_param = ON_DBL_MAX;
    *kminus = ON_DBL_MAX;
    *kplus = ON_DBL_MAX;
  }
  return rc;
}

class CVertexInfo
{
  // Helper class used in ON_Extrusion::CreateMesh()
  // It is declared out here to keep gcc happy.
public:
  ON_3dPoint P;  // profile 2d point
  ON_3dVector T; // profile 3d tangent
  double t;      // profile parameter
  int vi[2];     // mesh->m_V[] indices
};

static void AddCapTrianglesHelper(
  int cap_index, // 0 = bottom, 1 = top
  int captri_count,
  const ON_3dex* captri_list,
  const ON_2dex* capV_list,
  const ON_3dVector FN,
  ON_Mesh* mesh
  )
{
  int i;

  i = mesh->m_F.Count() + captri_count;
  mesh->m_F.Reserve(i);
  mesh->m_FN.Reserve(i);

  /*
  if ( 2 == captri_count )
  {
    // see if a single quad will work
    const ON_3dex& tri0 = captri_list[0];
    const ON_3dex& tri1 = captri_list[1];
    ON_MeshFace f0,f1,f;
    f0.vi[0] = capV_list[2*tri0.i];
    f0.vi[1] = capV_list[2*tri0.k];
    f0.vi[2] = capV_list[2*tri0.j];
    f0.vi[3] = f0.vi[2];
    f1.vi[0] = capV_list[2*tri1.i];
    f1.vi[1] = capV_list[2*tri1.k];
    f1.vi[2] = capV_list[2*tri1.j];
    f1.vi[3] = f1.vi[2];

    for ( i = 0; i < 3; i++ ) for ( j = 0; j < 3; j++ )
    {
      if (    f0.vi[i] == f1.vi[(j+1)%3] 
           && f0.vi[(i+1)%3] == f1.vi[j] 
         )
      {
        // set f = quad candidate
        f.vi[0] = f0.vi[(i+2)%3];
        f.vi[1] = f0.vi[i];
        f.vi[2] = f1.vi[(j+2)%3];
        f.vi[3] = f0.vi[(i+1)%3];

        // force exit nested for loop
        i = 86;
        j = 86;

        // verify f is a valid convext quad
        if ( !f.IsValid(mesh->m_V.Count()) )
          break;
        ON_3dVector A,B,C;
        ON_3dPoint P[4] = {mesh->m_V[f.vi[0]],mesh->m_V[f.vi[1]],mesh->m_V[f.vi[2]],mesh->m_V[f.vi[3]]};
        A = P[2]-P[1];
        B = P[0]-P[1];
        C = ON_CrossProduct(A,B);
        C.Unitize();
        if ( !(C*FN > 0.99) )
          break;
        A = P[0]-P[3];
        B = P[2]-P[3];
        C = ON_CrossProduct(A,B);
        C.Unitize();
        if ( !(C*FN > 0.99) )
          break;

        // a single quad will work
        mesh->m_F.Append(f);
        mesh->m_FN.Append(FN);
        return;
      }
    }
  }
  */

  // add triangles
  if ( 0 == cap_index )
  {
    // add triangles for the bottom cap
    for ( i = 0; i < captri_count; i++ )
    {
      const ON_3dex& tri = captri_list[i];
      ON_MeshFace& f = mesh->m_F.AppendNew();
      f.vi[0] = capV_list[tri.i].i;
      f.vi[1] = capV_list[tri.k].i;
      f.vi[2] = capV_list[tri.j].i;
      f.vi[3] = f.vi[2];
      mesh->m_FN.Append(FN);
    }
  }
  else if ( 1 == cap_index )
  {
    // add triangles for the top cap
    for ( i = 0; i < captri_count; i++ )
    {
      const ON_3dex& tri = captri_list[i];
      ON_MeshFace& f = mesh->m_F.AppendNew();
      f.vi[0] = capV_list[tri.i].j;
      f.vi[1] = capV_list[tri.j].j;
      f.vi[2] = capV_list[tri.k].j;
      f.vi[3] = f.vi[2];
      mesh->m_FN.Append(FN);
    }
  }
}

ON_Mesh* ON_Extrusion::CreateMesh( 
           const ON_MeshParameters& mp,
           ON_Mesh* mesh
           ) const
{
  ON_Workspace ws;

  int is_capped = IsCapped();
  if ( is_capped < 0 || is_capped > 3 )
    is_capped = 0; // don't let future changes or bug in IsCapped() crash this code

  // Make sure extrusion is well defined
  ON_SimpleArray<const ON_Curve*> profile_curves(m_profile_count);
  const int profile_count = GetProfileCurves(profile_curves);
  if ( profile_count < 1 || profile_count != profile_curves.Count() )
    return 0;

  // set curve meshing paramters
  ON_MeshCurveParameters mcp;
  mcp.m_max_ang_radians = mp.m_refine_angle;
  mcp.m_max_chr = mp.m_relative_tolerance;
  mcp.m_max_aspect = mp.m_grid_aspect_ratio;
  mcp.m_tolerance = mp.m_tolerance;
  mcp.m_min_edge_length = mp.m_min_edge_length;
  mcp.m_max_edge_length = mp.m_max_edge_length;

  const ON_3dVector pathT = m_path.Tangent();
  ON_Xform xform0(1.0), xform1(1.0), rot0(1.0), rot1(1.0), xformT(1.0);

  if ( !ON_GetEndCapTransformation(m_path.PointAt(m_t.m_t[0]),pathT,m_up,m_bHaveN[0]?&m_N[0]:0,xform0,0,&rot0) )
    return 0;
  if ( !ON_GetEndCapTransformation(m_path.PointAt(m_t.m_t[1]),pathT,m_up,m_bHaveN[1]?&m_N[1]:0,xform1,0,&rot1) )
    return 0;
  if ( !ON_GetEndCapTransformation(ON_origin,pathT,m_up,0,xformT,0,0) )
    return 0;

  // Get a polyline that approximates the profile;
  bool bFlipMesh = false;
  ON_PolylineCurve polyline;
  ON_SimpleArray<bool> polyline_bIsClosed(profile_count);
  ON_SimpleArray<int> polyline_point_count(profile_count);
  ON_SimpleArray<int> VInfo_point_count(profile_count);
  int profile_index, i;
  ON_SimpleArray<CVertexInfo> Vinfo_list;
  CVertexInfo Vinfo;
  memset(&Vinfo,0,sizeof(Vinfo));
  int hint = 0;
  double profile_length = 0.0;
  for ( profile_index = 0; profile_index < profile_count; profile_index++ )
  {
    const ON_Curve* profile = profile_curves[profile_index];
    if ( 0 == profile )
      return 0;
    polyline.m_t.SetCount(0);
    polyline.m_pline.SetCount(0);
    polyline.m_dim = 2;
    if ( !profile->IsPolyline(&polyline.m_pline,&polyline.m_t) )
    {
      mcp.m_tolerance = mp.m_tolerance;
      if ( mp.m_relative_tolerance > 0.0 )
      {
        ON_BoundingBox bbox = profile->BoundingBox();
        if ( bbox.IsValid() )
        {
          bbox.m_min.z = bbox.m_max.z = 0.0;
          double d = bbox.Diagonal().Length();
          double tol = ON_MeshParameters::Tolerance(mp.m_relative_tolerance,d);
          if ( tol > 0.0 )
          {
            if ( tol < 1.0e-4 )
              tol = 1.0e-4;
            if ( tol < mp.m_min_tolerance )
              tol = mp.m_min_tolerance;
            if ( tol > 0.0 && (tol < mcp.m_tolerance || mcp.m_tolerance <= 0.0 || !ON_IsValid(mcp.m_tolerance) ) )
              mcp.m_tolerance = tol;
          }
        }
      }
      if ( 0 == profile->MeshCurve(mcp,&polyline,false,0) )
        return 0;
    }
    int count = polyline.m_pline.Count();
    if ( count < 2 )
      return 0;
    bool bIsClosed = false;
    if ( count >= 4 && (polyline.IsClosed() || profile->IsClosed()) )
    {
      bIsClosed = true;
      *polyline.m_pline.Last() = polyline.m_pline[0];
      if ( 0 == profile_index )
      {
        // see if outer polyline is going clockwise
        int tcount = polyline.m_t.Count();
        ON_3dPoint p0,p1;
        double a = 0.0;
        p1 = polyline.m_pline[0];
        for ( i = 1; i < tcount; i++ )
        {
          p0 = p1;
          p1 = polyline.m_pline[i];
          a += (p0.x-p1.x)*(p0.y+p1.y);
        }
        if ( a < 0.0 )
        {
          bFlipMesh = true;
        }
      }
    }
    else 
    {
      bIsClosed = false;
      is_capped = 0;
    }

    polyline_bIsClosed.Append(bIsClosed);
    polyline_point_count.Append(count);


    // Convert polyline information into information needed
    // to create mesh vertex, texture, and normal arrays.
    Vinfo_list.Reserve( Vinfo_list.Count() + count + profile->SpanCount() );

    ON_3dVector T1;

    // See if there are kinks in the profile
    double kink_param, kminus, kplus;
    const double kink_max = *polyline.m_t.Last();
    bool bKinkyProfile = FindNextKinkHelper( profile,polyline.m_t[0],kink_max,&kminus,&kink_param,&kplus);

    const int Vinfo_list_count0 = Vinfo_list.Count();
    for ( i = 0; i < count; i++ )
    {
      Vinfo.t = polyline.m_t[i];
      polyline.m_pline[i].z = 0.0;
      if (    bKinkyProfile
           && Vinfo_list.Count() > Vinfo_list_count0 
           && Vinfo_list.Last()->t < kminus 
           && kplus < Vinfo.t 
         )
      {
        while ( bKinkyProfile && kplus < Vinfo.t )
        {
          // add kinks between previous and current polyline0 point
          KinkEvalHelper( profile,kminus,kink_param,kplus,Vinfo.P,Vinfo.T,T1,&hint);
          Vinfo.t = kink_param;
          Vinfo_list.Append(Vinfo);
          Vinfo.T = T1;
          Vinfo_list.Append(Vinfo);
          bKinkyProfile = FindNextKinkHelper( profile,kplus,kink_max,&kminus,&kink_param,&kplus);
        }
        Vinfo.t = polyline.m_t[i];
      }

      if (    bKinkyProfile
           && kminus <= Vinfo.t && Vinfo.t <= kplus 
           && i < count-1 && polyline.m_t[i+1] > kink_param )
      {
        // polyline0.m_t[i] is at a kink
        KinkEvalHelper( profile,kminus,kink_param,kplus,Vinfo.P,Vinfo.T,T1,&hint);
        Vinfo.t = kink_param;
        Vinfo_list.Append(Vinfo);
        Vinfo.T = T1;
        Vinfo_list.Append(Vinfo);
        bKinkyProfile = FindNextKinkHelper( profile,kplus,kink_max,&kminus,&kink_param,&kplus);
      }
      else
      {
        // no kink at polyline0.m_t[i]
        Vinfo.t = polyline.m_t[i];
        m_profile->EvTangent(Vinfo.t,Vinfo.P,Vinfo.T,(count-1 == i) ? -1 : 1,&hint);
        Vinfo.P.z = 0;
        Vinfo.T.z = 0;
        Vinfo_list.Append(Vinfo);
      }
    }

    count = Vinfo_list.Count();
    if ( count < Vinfo_list_count0 + 2 )
      return 0;

    if ( bIsClosed )
      Vinfo_list.Last()->P = Vinfo_list[Vinfo_list_count0].P;

    VInfo_point_count.Append(Vinfo_list.Count());

    double len = 0.0;
    if ( polyline.GetLength(&len) )
      profile_length += len;
  }

  ON_3dPoint P;

  ON_SimpleArray<ON_3dex> cap_triangles;
  polyline.m_pline.SetCount(0);
  polyline.m_t.SetCount(0);
  int capV_count = 0;
  int captri_count = 0;
  ON_2dex* capV_list = 0;
  const ON_3dex* captri_list = 0;

  if ( 0 != is_capped )
  {
    ON_SimpleArray<ON_2dex> edge_list(Vinfo_list.Count()+1);
    ON_2dex edge;

    polyline.m_pline.Reserve(Vinfo_list.Count());
    polyline.m_t.Reserve(Vinfo_list.Count());
    for ( profile_index = 0; profile_index < profile_count; profile_index++ )
    {
      const int i0 =  profile_index > 0 ? VInfo_point_count[profile_index-1] : 0;
      const int polyline_count0 =  polyline.PointCount();
      Vinfo = Vinfo_list[i0];
      P = Vinfo.P;
      P.z = i0;
      polyline.m_pline.Append(P);
      polyline.m_t.Append(Vinfo.t);
      edge.j = polyline_count0;
      const bool bIsClosed = polyline_bIsClosed[profile_index];
      const int i1 = VInfo_point_count[profile_index] - (bIsClosed?1:0);
      for (i = i0+1 ; i < i1; i++)
      {
        const CVertexInfo& VI = Vinfo_list[i];
        if ( VI.t > Vinfo.t )
        {
          Vinfo = VI;
          P = Vinfo.P;
          P.z = i;
          edge.i = edge.j;
          edge.j = polyline.PointCount();
          edge_list.Append(edge);
          polyline.m_pline.Append(P);
          polyline.m_t.Append(Vinfo.t);
        }
      }
      if ( bIsClosed )
      {
        edge.i = edge.j;
        edge.j = polyline_count0;
        edge_list.Append(edge);
      }
    }

    // calculate triangles that fill in the end cap
    ON_Mesh2dRegion( polyline.PointCount(), 
                     3,
                     &polyline.m_pline.Array()->x,
                     edge_list.Count(),
                     2,
                     &edge_list.Array()->i,
                     0,
                     cap_triangles);

    if ( cap_triangles.Count() > 0 )
    {
      capV_count = polyline.PointCount();
      captri_count = cap_triangles.Count();
      if ( captri_count > 0 )
      {
        ON_2dex* vv = (ON_2dex*)ws.GetIntMemory(2*capV_count);
        for ( i = 0; i < capV_count; i++ )
        {
          // set vv[i].j = Vinfo[] index for point polyline0.m_pline[i]
          vv[i].i = -1;
          vv[i].j = (int)(polyline.m_pline[i].z); // vv[i].j = Vinfo_list[] index
        }
        capV_list = vv;
        captri_list = cap_triangles.Array();
      }
    }

    for ( i = 0; i < polyline.m_pline.Count(); i++ )
    {
      polyline.m_pline[i].z = 0.0;
    }
  }

  if ( !mesh )
    mesh = new ON_Mesh();
  else
    mesh->Destroy();

  const int count = Vinfo_list.Count();

  int path_dir = PathParameter();
  int vcount_reserve = 2*count;
  switch( is_capped )
  {
  case 1:
  case 2:
    vcount_reserve += capV_count;
    break;
  case 3:
    vcount_reserve += 2*capV_count;
    break;
  }
  mesh->m_V.Reserve(vcount_reserve);
  mesh->m_N.Reserve(vcount_reserve);
  mesh->m_S.Reserve(vcount_reserve);
  mesh->m_T.Reserve(vcount_reserve);
  mesh->m_srf_domain[0] = Domain(0);
  mesh->m_srf_domain[1] = Domain(1);
  mesh->m_srf_scale[path_dir]   = m_path.Length();
  mesh->m_srf_scale[1-path_dir] = profile_length;
  mesh->m_packed_tex_domain[0].Set(0.0,1.0);
  mesh->m_packed_tex_domain[1].Set(0.0,1.0);
  mesh->m_packed_tex_rotate = false;
  ON_2dPoint S;
  ON_3dVector N, T;
  ON_2fPoint tex;
  int quad_count = 0;
  double t0 = Vinfo_list[0].t;
  for ( i = 0; i < count; i++ )
  {
    CVertexInfo& VI = Vinfo_list[i];
    if ( t0 < VI.t )
    {
      quad_count++;
      t0 = VI.t;
    }
    VI.P.z = 0.0;
    VI.T.z = 0.0;
    P = xform0*VI.P;
    T = xformT*VI.T;
    N = ON_CrossProduct(T,pathT);
    if ( m_bTransposed )
      N.Reverse();
    if ( !N.IsUnitVector() && !N.Unitize() )
      N.Zero();
    S[1-path_dir] = VI.t;
    S[path_dir] = m_path_domain[0];
    tex.x = (float)mesh->m_srf_domain[0].NormalizedParameterAt(S.x);
    tex.y = (float)mesh->m_srf_domain[1].NormalizedParameterAt(S.y);
    VI.vi[0] = mesh->m_V.Count();
    mesh->m_V.AppendNew() = P;
    mesh->m_N.AppendNew() = N;
    mesh->m_S.Append(S);
    mesh->m_T.Append(tex);

    P = xform1*VI.P;
    S[path_dir] = m_path_domain[1];
    tex[path_dir] = (float)mesh->m_srf_domain[path_dir].NormalizedParameterAt(S[path_dir]);
    VI.vi[1] = mesh->m_V.Count();
    mesh->m_V.AppendNew() = P;
    mesh->m_N.AppendNew() = N;
    mesh->m_S.Append(S);
    mesh->m_T.Append(tex);
  }

  // add quads
  int fvi1, fvi3;
  if ( m_bTransposed )
  {
    fvi1 = 3;
    fvi3 = 1;
  }
  else
  {
    fvi1 = 1;
    fvi3 = 3;
  }
  mesh->m_F.Reserve(quad_count + 2*captri_count);
  for ( i = 1; i < count; i++ )
  {
    const CVertexInfo& Vinfo0 = Vinfo_list[i-1];
    const CVertexInfo& Vinfo1 = Vinfo_list[i];
    if ( Vinfo0.t < Vinfo1.t )
    {
      ON_MeshFace& f = mesh->m_F.AppendNew();
      f.vi[0] = Vinfo0.vi[0];
      f.vi[fvi1] = Vinfo1.vi[0];
      f.vi[2] = Vinfo1.vi[1];
      f.vi[fvi3] = Vinfo0.vi[1];      
    }
  }
  mesh->m_FN.Reserve(mesh->m_F.Count() + 2*captri_count);
  mesh->ComputeFaceNormals();

  if ( captri_count > 0 && capV_count > 0 )
  {
    // add end caps
    ON_3dVector N0, N1;
    if ( m_bHaveN[0] )
    {
      N0 = rot0*ON_zaxis;
      if ( !N0.Unitize() )
        N0 = -pathT;
      else
        N0.Reverse();
    }
    else
    {
      N0 = -pathT;
    }
    if ( m_bHaveN[1] )
    {
      N1 = rot1*ON_zaxis;
      if ( !N1.Unitize() )
        N1 = pathT;
    }
    else
    {
      N1 = pathT;
    }

    if ( bFlipMesh )
    {
      N0.Reverse();
      N1.Reverse();
    }

    vcount_reserve = mesh->m_V.Count()+(3==is_capped?2:1)*capV_count;
    mesh->m_V.Reserve(vcount_reserve);
    mesh->m_S.Reserve(vcount_reserve);
    mesh->m_N.Reserve(vcount_reserve);
    mesh->m_T.Reserve(vcount_reserve);

    if ( 1 == is_capped || 3 == is_capped )
    {
      // add vertices for the bottom cap
      for ( i = 0; i < capV_count; i++ )
      {
        // capV_list[i].j = Vinfo_list[] index
        const CVertexInfo& VI = Vinfo_list[capV_list[i].j];
        // set capV_list[i].i = mesh->m_V[] index
        capV_list[i].i = mesh->m_V.Count();
        mesh->m_V.Append(mesh->m_V[VI.vi[0]]);
        mesh->m_S.Append(mesh->m_S[VI.vi[0]]);
        mesh->m_T.Append(mesh->m_T[VI.vi[0]]);
        mesh->m_N.AppendNew() = N0;
      }
    }

    if ( 2 == is_capped || 3 == is_capped )
    {
      // add vertices for the top cap
      for ( i = 0; i < capV_count; i++ )
      {
        // capV_list[i].j = Vinfo_list[] index
        const CVertexInfo& VI = Vinfo_list[capV_list[i].j];
        // set capV_list[i].j = mesh->m_V[] index
        capV_list[i].j = mesh->m_V.Count();
        mesh->m_V.Append(mesh->m_V[VI.vi[1]]);
        mesh->m_S.Append(mesh->m_S[VI.vi[1]]);
        mesh->m_T.Append(mesh->m_T[VI.vi[1]]);
        mesh->m_N.AppendNew() = N1;
      }
    }

    int fcount_reserve = mesh->m_F.Count() + (3==is_capped ? 2 : 1)*captri_count;

    mesh->m_F.Reserve(fcount_reserve);
    mesh->m_FN.Reserve(fcount_reserve);

    if ( 1 == is_capped || 3 == is_capped )
    {
      // add triangles for the bottom cap
      AddCapTrianglesHelper(0,captri_count,captri_list,capV_list,N0,mesh);

      //for ( i = 0; i < captri_count; i++ )
      //{
      //  const ON_3dex& tri = captri_list[i];
      //  ON_MeshFace& f = mesh->m_F.AppendNew();
      //  f.vi[0] = capV_list[tri.i].i;
      //  f.vi[1] = capV_list[tri.k].i;
      //  f.vi[2] = capV_list[tri.j].i;
      //  f.vi[3] = f.vi[2];
      //  mesh->m_FN.AppendNew() = N0;
      //}
    }

    if ( 2 == is_capped || 3 == is_capped )
    {
      // add triangles for the top cap
      AddCapTrianglesHelper(1,captri_count,captri_list,capV_list,N1,mesh);

      //for ( i = 0; i < captri_count; i++ )
      //{
      //  const ON_3dex& tri = captri_list[i];
      //  ON_MeshFace& f = mesh->m_F.AppendNew();
      //  f.vi[0] = capV_list[tri.i].j;
      //  f.vi[1] = capV_list[tri.j].j;
      //  f.vi[2] = capV_list[tri.k].j;
      //  f.vi[3] = f.vi[2];
      //  mesh->m_FN.AppendNew() = N1;
      //}
    }
  }

  if ( 0 != mesh && bFlipMesh )
    mesh->Flip();

  if ( mesh )
    mesh->SetMeshParameters(mp);

  return mesh;
}

ON_BOOL32 ON_Extrusion::SetDomain( 
  int dir, // 0 sets first parameter's domain, 1 gets second parameter's domain
  double t0, 
  double t1
  )
{
  bool rc = false;
  if ( ON_IsValid(t0) && ON_IsValid(t1) && t0 < t1 )
  {
    const int path_dir = PathParameter();
    if ( path_dir == dir )
    {
      m_path_domain.Set(t0,t1);
      rc = true;
    }
    else if ( 1-path_dir == dir )
    {
      rc = m_profile->SetDomain(t0,t1)?true:false;
    }
  }
  return rc;
}

ON_Interval ON_Extrusion::Domain(
  int dir // 0 gets first parameter's domain, 1 gets second parameter's domain
  ) const 
{
  const int path_dir = PathParameter();
  return (path_dir == dir ) 
         ? m_path_domain 
         : ((1-path_dir == dir && m_profile) ? m_profile->Domain() : ON_Interval());
}

ON_BOOL32 ON_Extrusion::GetSurfaceSize( 
    double* width, 
    double* height 
    ) const
{
  bool rc = true;
  //int path_dir = PathParameter();
  if ( PathParameter() )
  {
    double* p = width;
    width = height;
    height = p;
  }
  if ( width )
  {
    if ( m_path.IsValid() && m_t.IsIncreasing() )
      *width = m_path.Length()*m_t.Length();
    else
    {
      *width = 0.0;
      rc = false;
    }
  }
  if (height)
  {
    if ( m_profile )
    {
      rc = m_profile->GetLength(height)?true:false;
    }
    else 
    {
      rc = false;
      *height = 0.0;
    }
  }
  return rc;
}

int ON_Extrusion::SpanCount(
  int dir // 0 gets first parameter's domain, 1 gets second parameter's domain
  ) const // number of smooth nonempty spans in the parameter direction
{
  const int path_dir = PathParameter();
  if ( path_dir == dir )
    return 1;
  if ( 1-path_dir == dir && m_profile )
    return m_profile->SpanCount();
  return 0;
}

ON_BOOL32 ON_Extrusion::GetSpanVector( // span "knots" 
      int dir, // 0 gets first parameter's domain, 1 gets second parameter's domain
      double* span_vector // array of length SpanCount() + 1 
      ) const  // 
{
  if ( span_vector )
  {
    const int path_dir = PathParameter();
    if ( path_dir == dir )
    {
      span_vector[0] = m_path_domain[0];
      span_vector[1] = m_path_domain[1];
      return true;
    }
    if ( 1-path_dir == dir && m_profile )
    {
      return m_profile->GetSpanVector(span_vector);
    }
  }
  return false;
}

ON_BOOL32 ON_Extrusion::GetSpanVectorIndex(
      int dir , // 0 gets first parameter's domain, 1 gets second parameter's domain
      double t,      // [IN] t = evaluation parameter
      int side,         // [IN] side 0 = default, -1 = from below, +1 = from above
      int* span_vector_index,        // [OUT] span vector index
      ON_Interval* span_interval // [OUT] domain of the span containing "t"
      ) const
{
  const int path_dir = PathParameter();
  if ( path_dir == dir )
  {
    if ( span_vector_index )
      *span_vector_index = 0;
    if ( span_interval )
      *span_interval = m_path_domain;
    return true;
  }
  if ( 1-path_dir == dir && m_profile )
  {
    return m_profile->GetSpanVectorIndex(t,side,span_vector_index,span_interval);
  }
  return false;
}

int ON_Extrusion::Degree( // returns maximum algebraic degree of any span 
                // ( or a good estimate if curve spans are not algebraic )
  int dir // 0 gets first parameter's domain, 1 gets second parameter's domain
  ) const  
{
  const int path_dir = PathParameter();
  if ( path_dir == dir )
    return 1;
  if ( 1-path_dir == dir && m_profile )
    return m_profile->Degree();
  return 0;
}

ON_BOOL32 ON_Extrusion::GetParameterTolerance( // returns tminus < tplus: parameters tminus <= s <= tplus
       int dir,        // 0 gets first parameter, 1 gets second parameter
       double t,       // t = parameter in domain
       double* tminus, // tminus
       double* tplus   // tplus
       ) const
{
  const int path_dir = PathParameter();
  if ( path_dir == dir )
    return ON_Surface::GetParameterTolerance(dir,t,tminus,tplus);
  if ( 1-path_dir==dir && m_profile)
    return m_profile->GetParameterTolerance(t,tminus,tplus);
  return false;
}

ON_Surface::ISO ON_Extrusion::IsIsoparametric(
      const ON_Curve& curve,
      const ON_Interval* curve_domain
      ) const
{
  return ON_Surface::IsIsoparametric(curve,curve_domain);
}

ON_BOOL32 ON_Extrusion::IsPlanar(
      ON_Plane* plane,
      double tolerance
      ) const
{
  if ( m_profile && m_profile->IsLinear(tolerance) )
  {
    if ( plane )
    {
      ON_3dPoint P0 = m_profile->PointAtStart();
      ON_3dPoint P1 = m_profile->PointAtEnd();
      ON_3dVector pathT = m_path.Tangent();
      ON_3dVector Y = m_up;
      ON_3dVector X = ON_CrossProduct(Y,pathT);
      if ( !X.IsUnitVector() )
        X.Unitize();
      ON_3dPoint Q0 = m_path.from + P0.x*X + P0.y*Y;
      ON_3dPoint Q1 = m_path.from + P1.x*X + P1.y*Y;
      ON_3dVector N = ON_CrossProduct(pathT,Q1-Q0);
      N.Unitize();
      plane->origin = P0;
      if ( m_bTransposed )
      {
        plane->yaxis = pathT;
        plane->zaxis = -N;
        plane->xaxis = ON_CrossProduct(plane->yaxis,plane->zaxis);
        plane->xaxis.Unitize();
      }
      else
      {
        plane->xaxis = pathT;
        plane->zaxis = N;
        plane->yaxis = ON_CrossProduct(plane->zaxis,plane->xaxis);
        plane->yaxis.Unitize();
      }
      plane->UpdateEquation();
    }    
    return true;
  }
  return false;
}

ON_BOOL32 ON_Extrusion::IsClosed(int dir) const
{
  const int path_dir = PathParameter();
  if ( 1-path_dir == dir && m_profile )
    return m_profile->IsClosed();
  return false;
}

ON_BOOL32 ON_Extrusion::IsPeriodic( int dir ) const
{
  const int path_dir = PathParameter();
  if ( 1-path_dir == dir && m_profile )
    return m_profile->IsPeriodic();
  return false;
}

//ON_BOOL32 ON_Extrusion::IsSingular( // true if surface side is collapsed to a point
//      int        // side of parameter space to test
//                 // 0 = south, 1 = east, 2 = north, 3 = west
//      ) const
bool ON_Extrusion::GetNextDiscontinuity( 
                int dir,
                ON::continuity c,
                double t0,
                double t1,
                double* t,
                int* hint,
                int* dtype,
                double cos_angle_tolerance,
                double curvature_tolerance
                ) const
{
  const int path_dir = PathParameter();
  if ( path_dir == dir )
  {
    return ON_Surface::GetNextDiscontinuity(dir,c,t0,t1,t,hint,dtype,cos_angle_tolerance,curvature_tolerance);
  }
  if ( 1-path_dir==dir && m_profile)
  {
    return m_profile->GetNextDiscontinuity(c,t0,t1,t,hint,dtype,cos_angle_tolerance,curvature_tolerance);
  }
  return false;
}

bool ON_Extrusion::IsContinuous(
  ON::continuity c,
  double s, 
  double t, 
  int* hint,
  double point_tolerance,
  double d1_tolerance,
  double d2_tolerance,
  double cos_angle_tolerance,
  double curvature_tolerance
  ) const
{
  if ( !m_profile )
    return false;
  int* crv_hint = 0;
  double curvet;
  if ( m_bTransposed )
  {
    curvet = s;
    crv_hint = hint;
  }
  else
  {
    curvet = t;
    crv_hint = hint ? hint+1 : 0;
  }
  return m_profile->IsContinuous(c,curvet,crv_hint,point_tolerance,d1_tolerance,d2_tolerance,cos_angle_tolerance,curvature_tolerance);
}

ON_Surface::ISO ON_Extrusion::IsIsoparametric(
      const ON_BoundingBox& bbox
      ) const
{
  return ON_Surface::IsIsoparametric(bbox);
}

ON_BOOL32 ON_Extrusion::Reverse( int dir )
{
  const int path_dir = PathParameter();
  if ( path_dir == dir )
  {
    m_path_domain.Reverse();
    return true;
  }
  if ( 1-path_dir == dir && m_profile )
  {
    return m_profile->Reverse();
  }
  return false;
}

ON_BOOL32 ON_Extrusion::Transpose() // transpose surface parameterization (swap "s" and "t")
{
  m_bTransposed = m_bTransposed?false:true;
  return true;
}

ON_BOOL32 ON_Extrusion::Evaluate( // returns false if unable to evaluate
       double u, double v,   // evaluation parameters
       int num_der,          // number of derivatives (>=0)
       int array_stride,     // array stride (>=Dimension())
       double* der_array,    // array of length stride*(ndir+1)*(ndir+2)/2
       int quadrant ,     // optional - determines which quadrant to evaluate from
                             //         0 = default
                             //         1 from NE quadrant
                             //         2 from NW quadrant
                             //         3 from SW quadrant
                             //         4 from SE quadrant
       int* hint          // optional - evaluation hint (int[2]) used to speed
                             //            repeated evaluations
       ) const 
{
  if ( !m_profile )
    return false;

  double x,y,dx,dy;
  //int side = 0;
  if ( m_bTransposed ) 
  {
    x = u; u = v; v = x;
    if ( 4 == quadrant )
      quadrant = 2;
    else if ( 2 == quadrant )
      quadrant = 4;
  }

  if ( !m_profile->Evaluate( u, num_der, array_stride, der_array,
                             (1==quadrant||4==quadrant)?1:((2==quadrant||3==quadrant)?-1:0),
                               hint) 
     )
  {
    return false;
  }

  // TODO: After testing, add special case that avoids
  //       two calls to GetProfileTransformation() when 
  //       mitering is trivial.
  const double t1 = m_path_domain.NormalizedParameterAt(v);
  const double t0 = 1.0-t1;
  ON_Xform xform0, xform1;
  const ON_3dVector T = m_path.Tangent();
  if ( 0.0 != t0 || num_der > 0 )
  {
    if ( !ON_GetEndCapTransformation(m_path.PointAt(m_t.m_t[0]),T,m_up,m_bHaveN[0]?&m_N[0]:0,xform0,0,0) )
      return false;
  }
  else
  {
    xform0.Zero();
  }
  if ( 0.0 != t1 || num_der > 0 )
  {
    if ( !ON_GetEndCapTransformation(m_path.PointAt(m_t.m_t[1]),T,m_up,m_bHaveN[1]?&m_N[1]:0,xform1,0,0) )
      return false;
  }
  else
  {
    xform1.Zero();
  }

  double xformP[3][3], xformD[3][3];
  xformP[0][0] = t0*xform0.m_xform[0][0] + t1*xform1.m_xform[0][0];
  xformP[0][1] = t0*xform0.m_xform[0][1] + t1*xform1.m_xform[0][1];
  xformP[0][2] = t0*xform0.m_xform[0][3] + t1*xform1.m_xform[0][3];
  xformP[1][0] = t0*xform0.m_xform[1][0] + t1*xform1.m_xform[1][0];
  xformP[1][1] = t0*xform0.m_xform[1][1] + t1*xform1.m_xform[1][1];
  xformP[1][2] = t0*xform0.m_xform[1][3] + t1*xform1.m_xform[1][3];
  xformP[2][0] = t0*xform0.m_xform[2][0] + t1*xform1.m_xform[2][0];
  xformP[2][1] = t0*xform0.m_xform[2][1] + t1*xform1.m_xform[2][1];
  xformP[2][2] = t0*xform0.m_xform[2][3] + t1*xform1.m_xform[2][3];

  int i,j;
  i = num_der+1;
  double* d1 = der_array + array_stride*(i*(i+1)/2 - 1);
  const double* d0 = der_array + array_stride*(i - 1);
  x = d0[0];
  y = d0[1];
  if ( num_der > 0 )
  {
    double d = m_path_domain.m_t[1] - m_path_domain.m_t[0];
    if ( d > 0.0 )
      d = 1.0/d;
    xformD[0][0] = d*(xform1.m_xform[0][0] - xform0.m_xform[0][0]);
    xformD[0][1] = d*(xform1.m_xform[0][1] - xform0.m_xform[0][1]);
    xformD[0][2] = d*(xform1.m_xform[0][3] - xform0.m_xform[0][3]);
    xformD[1][0] = d*(xform1.m_xform[1][0] - xform0.m_xform[1][0]);
    xformD[1][1] = d*(xform1.m_xform[1][1] - xform0.m_xform[1][1]);
    xformD[1][2] = d*(xform1.m_xform[1][3] - xform0.m_xform[1][3]);
    xformD[2][0] = d*(xform1.m_xform[2][0] - xform0.m_xform[2][0]);
    xformD[2][1] = d*(xform1.m_xform[2][1] - xform0.m_xform[2][1]);
    xformD[2][2] = d*(xform1.m_xform[2][3] - xform0.m_xform[2][3]);

    for ( i = num_der; i > 0; i-- )
    {
      dx = x;
      dy = y;
      d0 -= array_stride;
      x = d0[0];
      y = d0[1];

      // all partials involving two or more derivatives with
      // respect to "v" are zero.
      j = i;
      while ( --j )
      {
        d1[0] = d1[1] = d1[2] = 0.0;
        d1 -= array_stride;
      }    

      // The partial involving a single derivative with respect to "v"
      if ( 1 == i )
      {
        // xformD transform is applied to curve location ((x,y) = point)
        d1[0] = xformD[0][0]*x + xformD[0][1]*y + xformD[0][2];
        d1[1] = xformD[1][0]*x + xformD[1][1]*y + xformD[1][2];
        d1[2] = xformD[2][0]*x + xformD[2][1]*y + xformD[2][2];
      }
      else
      {
        // xformD transform is applied to a curve derivative ((x,y) = vector)
        d1[0] = xformD[0][0]*x + xformD[0][1]*y;
        d1[1] = xformD[1][0]*x + xformD[1][1]*y;
        d1[2] = xformD[2][0]*x + xformD[2][1]*y;
      }
      d1 -= array_stride;

      // The partial involving a all derivatives with respect to "u"
      // xformP transformation is applied to a curve derivative ((x,y) = vector)
      d1[0] = xformP[0][0]*dx + xformP[0][1]*dy;
      d1[1] = xformP[1][0]*dx + xformP[1][1]*dy;
      d1[2] = xformP[2][0]*dx + xformP[2][1]*dy;
      d1 -= array_stride;
    }
  }
  // xformP transformation is applied curve location ((x,y) = point)
  d1[0] = xformP[0][0]*x + xformP[0][1]*y + xformP[0][2];
  d1[1] = xformP[1][0]*x + xformP[1][1]*y + xformP[1][2];
  d1[2] = xformP[2][0]*x + xformP[2][1]*y + xformP[2][2];

  return true;
}

ON_Curve* ON_Extrusion::IsoCurve(
       int dir,
       double c
       ) const
{
  // dir 0 first parameter varies and second parameter is constant
  //       e.g., point on IsoCurve(0,c) at t is srf(t,c)
  //     1 first parameter is constant and second parameter varies
  //       e.g., point on IsoCurve(1,c) at t is srf(c,t)

  if ( !m_profile )
    return 0;

  if ( m_bTransposed )
    dir = 1-dir;
  const ON_3dVector T = m_path.Tangent();

  ON_Xform xform0, xform1;
  if ( !ON_GetEndCapTransformation(m_path.PointAt(m_t.m_t[0]),T,m_up,m_bHaveN[0]?&m_N[0]:0,xform0,0,0) )
    return 0;
  if ( !ON_GetEndCapTransformation(m_path.PointAt(m_t.m_t[1]),T,m_up,m_bHaveN[1]?&m_N[1]:0,xform1,0,0) )
    return 0;

  ON_Curve*  isocurve = 0;
  if ( 1 == dir )
  {
    ON_3dPoint P = m_profile->PointAt(c);
    ON_LineCurve* line_curve = new ON_LineCurve();
    line_curve->m_t = m_path_domain;
    line_curve->m_dim = 3;
    line_curve->m_line.from = xform0*P;
    line_curve->m_line.to = xform1*P;
    isocurve = line_curve;
  }
  else if ( 0 == dir )
  {
    double s1 = m_path_domain.NormalizedParameterAt(c);
    const double s0 = 1.0-s1;
    xform1.m_xform[0][0] = s0*xform0.m_xform[0][0] + s1*xform1.m_xform[0][0];
    xform1.m_xform[0][1] = s0*xform0.m_xform[0][1] + s1*xform1.m_xform[0][1];
    xform1.m_xform[0][2] = s0*xform0.m_xform[0][2] + s1*xform1.m_xform[0][2];
    xform1.m_xform[0][3] = s0*xform0.m_xform[0][3] + s1*xform1.m_xform[0][3];

    xform1.m_xform[1][0] = s0*xform0.m_xform[1][0] + s1*xform1.m_xform[1][0];
    xform1.m_xform[1][1] = s0*xform0.m_xform[1][1] + s1*xform1.m_xform[1][1];
    xform1.m_xform[1][2] = s0*xform0.m_xform[1][2] + s1*xform1.m_xform[1][2];
    xform1.m_xform[1][3] = s0*xform0.m_xform[1][3] + s1*xform1.m_xform[1][3];

    xform1.m_xform[2][0] = s0*xform0.m_xform[2][0] + s1*xform1.m_xform[2][0];
    xform1.m_xform[2][1] = s0*xform0.m_xform[2][1] + s1*xform1.m_xform[2][1];
    xform1.m_xform[2][2] = s0*xform0.m_xform[2][2] + s1*xform1.m_xform[2][2];
    xform1.m_xform[2][3] = s0*xform0.m_xform[2][3] + s1*xform1.m_xform[2][3];

    xform1.m_xform[3][0] = s0*xform0.m_xform[3][0] + s1*xform1.m_xform[3][0];
    xform1.m_xform[3][1] = s0*xform0.m_xform[3][1] + s1*xform1.m_xform[3][1];
    xform1.m_xform[3][2] = s0*xform0.m_xform[3][2] + s1*xform1.m_xform[3][2];
    xform1.m_xform[3][3] = s0*xform0.m_xform[3][3] + s1*xform1.m_xform[3][3];

    isocurve = m_profile->DuplicateCurve();
    if ( isocurve )
    {
      isocurve->ChangeDimension(3);
      if ( !isocurve->Transform(xform1) )
      {
        // isocurve is probably a circle
        ON_NurbsCurve* nurbs_curve = isocurve->NurbsCurve();
        delete isocurve;
        isocurve = nurbs_curve;
        nurbs_curve = 0;
        if ( isocurve )
          isocurve->Transform(xform1);
      }
    }
  }

  return isocurve;
}


//ON_Curve* ON_Extrusion::Pushup( const ON_Curve& curve_2d,
//                  double tolerance,
//                  const ON_Interval* curve_2d_subdomain = NULL
//                  ) const
//ON_Curve* ON_Extrusion::Pullback( const ON_Curve& curve_3d,
//                  double tolerance,
//                  const ON_Interval* curve_3d_subdomain = NULL,
//                  ON_3dPoint start_uv = ON_UNSET_POINT,
//                  ON_3dPoint end_uv = ON_UNSET_POINT
//                  ) const
ON_BOOL32 ON_Extrusion::Trim(
       int dir,
       const ON_Interval& domain
       )
{
  bool rc = false;
  if (!domain.IsIncreasing())
    return false;
  if ( m_bTransposed )
    dir = 1-dir;
  if ( 1 == dir )
  {
    rc = m_path_domain.IsIncreasing();
    if ( rc && m_path_domain != domain )
    {
      ON_Interval dom;
      dom.Intersection(domain,m_path_domain);
      rc = dom.IsIncreasing();
      if (rc)
      {
        double s0 = m_path_domain.NormalizedParameterAt(dom[0]);
        double s1 = m_path_domain.NormalizedParameterAt(dom[1]);
        double t0 = (1.0-s0)*m_t[0] + s0*m_t[1];
        double t1 = (1.0-s1)*m_t[0] + s1*m_t[1];
        rc = (s0 < s1 && 0.0 <= t0 && t0 < t1 && t1 <= 1.0);
        if (rc)
        {
          bool bChanged = false;
          if (t0 != m_t[0] && t0 > 0.0 )
          {
            bChanged = true;
            m_t[0] = t0;
            m_bHaveN[0] = false;
          }
          if ( t1 != m_t[1] && t1 < 1.0 )
          {
            bChanged = true;
            m_t[1] = t1;
            m_bHaveN[1] = false;
          }
          if ( bChanged )
          {
            m_path_domain = dom;
            DestroySurfaceTree();
          }
        }
      }
    }
  }
  else if ( 0 == dir )
  {
    if ( m_profile )
    {
      rc = m_profile->Trim(domain)?true:false;
      DestroySurfaceTree();
    }
  }
  return rc;
}

bool ON_Extrusion::Extend(
  int dir,
  const ON_Interval& domain
  )
{
  bool rc = false;
  if ( 1 == dir )
  {
    rc = domain.IsIncreasing() && m_path_domain.IsIncreasing();
    if ( rc )
    {
      double s0 = m_path_domain.NormalizedParameterAt(domain[0]);
      if ( s0 > 0.0 )
        s0 = 0.0;
      double s1 = m_path_domain.NormalizedParameterAt(domain[1]);
      if ( s1 < 1.0 )
        s1 = 1.0;
      double t0 = (1.0-s0)*m_t[0] + s0*m_t[1];
      double t1 = (1.0-s1)*m_t[0] + s1*m_t[1];
      bool bChanged = false;
      ON_3dPoint P0 = m_path.from;
      ON_3dPoint P1 = m_path.to;
      if ( t0 < m_t[0] )
      {
        bChanged = true;
        m_path_domain.m_t[0] = domain[0];
        if ( t0 < 0.0 )
        {
          P0 = m_path.PointAt(t0);
          m_t[0] = 0.0;
        }
        else
          m_t[0] = t0;
      }
      if ( t1 > m_t[1] )
      {
        bChanged = true;
        m_path_domain.m_t[1] = domain[1];
        if ( t1 > 1.0 )
        {
          P1 = m_path.PointAt(t1);
          m_t[1] = 1.0;
        }
        else
          m_t[1] = t1;
      }
      if ( bChanged )
      {
        m_path.from = P0;
        m_path.to = P1;
        DestroySurfaceTree();
      }
    }
  }
  else if ( 0 == dir )
  {
    if ( m_profile )
    {
      rc = m_profile->Extend(domain);
      if (rc) 
        DestroySurfaceTree();
    }
  }
  return rc;
}

ON_BOOL32 ON_Extrusion::Split(
       int dir,
       double c,
       ON_Surface*& west_or_south_side,
       ON_Surface*& east_or_north_side
       ) const
{
  if ( dir < 0 || dir > 1 || !ON_IsValid(c) )
    return false;
  if ( 0 != west_or_south_side && west_or_south_side == east_or_north_side )
    return false;

  ON_Interval domain = Domain(dir);
  double s = domain.NormalizedParameterAt(c);
  if ( s <= 0.0 || s >= 1.0 )
    return false;
  if (c <= domain[0] || c >= domain[1] )
    return false;

  ON_Extrusion* left = 0;
  ON_Extrusion* right = 0;
  if ( west_or_south_side )
  {
    left = ON_Extrusion::Cast(west_or_south_side);
    if ( !left )
      return false;
  }
  if ( east_or_north_side )
  {
    right = ON_Extrusion::Cast(east_or_north_side);
    if ( !right )
      return false;
  }

  const int path_dir = PathParameter();
  bool rc = false;
  if ( dir == path_dir )
  {
    // split path
    ON_Line left_path, right_path;
    ON_Interval left_domain, right_domain;
    ON_Interval left_t, right_t;

    const double t0 = m_t[0];
    const double t1 = m_t[1];
    const double t = (1.0-s)*t0 + s*t1;
    if ( !ON_IsValid(t) || t <= t0 || t >= t1 )
      return false;

    ON_3dPoint P = m_path.PointAt(s);
    left_path.from = m_path.from;
    left_path.to = P;
    right_path.from = P;
    right_path.to = m_path.to;
    left_domain.Set(domain[0],c);
    right_domain.Set(c,domain[1]);
    left_t.Set(t0,t);
    right_t.Set(t,t1);
    if ( !left_path.IsValid() || left_path.Length() <= m_path_length_min )
      return false;
    if ( !right_path.IsValid() || right_path.Length() <= m_path_length_min )
      return false;

    // return result
    if ( !left )
      left = new ON_Extrusion(*this);
    else if ( left != this )
      left->operator =(*this);
    else
      left->DestroyRuntimeCache();
    if ( !right )
      right = new ON_Extrusion(*this);
    else if ( right != this )
      right->operator =(*this);
    else
      right->DestroyRuntimeCache();
    left->m_path = left_path;
    left->m_path_domain = left_domain;
    left->m_t = left_t;
    right->m_path = right_path;
    right->m_path_domain = right_domain;
    right->m_t = right_t;

    west_or_south_side = left;
    east_or_north_side = right;
    rc = true;
  }
  else
  {
    if ( 0 == m_profile )
      return false;
    ON_Curve* left_profile = 0;
    ON_Curve* right_profile = 0;

    if ( left == this )
    {
      left_profile = left->m_profile;
      left->DestroyRuntimeCache();
    }
    else if ( 0 != left && 0 != left->m_profile )
    {
      delete left->m_profile;
      left->m_profile = 0;
    }

    if ( right == this )
    {
      right_profile = right->m_profile;
      right->DestroyRuntimeCache();
    }
    else if ( 0 != right && 0 != right->m_profile )
    {
      delete right->m_profile;
      right->m_profile = 0;
    }

    if ( !m_profile->Split(c,left_profile,right_profile) )
      return false;
    if ( 0 == left_profile || 0 == right_profile )
    {
      if ( 0 != left_profile && m_profile != left_profile )
        delete left_profile;
      if ( 0 != right_profile && m_profile != right_profile )
        delete right_profile;
      return false;
    }

    ON_Curve* this_profile = 0;
    if ( left_profile != m_profile && right_profile != m_profile )
    {
      if ( left == this || right == this )
      {
        delete m_profile;
      }
      else
      {
        this_profile = m_profile;
      }
    }

    // Prevent this m_profile from being copied
    const_cast<ON_Extrusion*>(this)->m_profile = 0;

    // Create new left and right sides with NULL profiles
    if ( !left )
      left = new ON_Extrusion(*this);
    else if ( left != this )
      left->operator =(*this);
    if ( !right )
      right = new ON_Extrusion(*this);
    else if ( right != this )
      right->operator =(*this);

    // Restore this m_profile
    const_cast<ON_Extrusion*>(this)->m_profile = this_profile;

    // Set left and right profiles
    left->m_profile = left_profile;
    right->m_profile = right_profile;

    west_or_south_side = left;
    east_or_north_side = right;
    rc = true;
  }

  return rc;
}

bool ON_Extrusion::GetClosestPoint( 
        const ON_3dPoint& P,
        double* s,
        double* t,
        double maximum_distance,
        const ON_Interval* sdomain,
        const ON_Interval* tdomain
        ) const
{
  if ( 0 == m_profile )
    return false;

  if ( !P.IsValid() )
    return false;

  if ( m_bTransposed ) 
  {
    double* p1 = s; s=t; t = p1;
    const ON_Interval* p2=sdomain;sdomain=tdomain;tdomain=p2;
  }


  ON_Interval profile_domain = m_profile->Domain();
  if ( 0 != sdomain )
  {
    if ( !sdomain->IsValid() || sdomain->IsDecreasing() )
      return false;
    if (    sdomain->m_t[0] <= profile_domain.m_t[0] 
         && sdomain->m_t[1] >= profile_domain.m_t[1] )
    {
      sdomain = 0;
    }
    else
    {
      if ( sdomain->m_t[0] > profile_domain.m_t[0] )
        profile_domain.m_t[0] = sdomain->m_t[0];
      if ( sdomain->m_t[1] < profile_domain.m_t[1] )
        profile_domain.m_t[1] = sdomain->m_t[1];
      if ( !profile_domain.IsValid() || profile_domain.IsDecreasing() )
        return false;
      sdomain = &profile_domain;
    }
  }

  ON_Interval path_domain = m_path_domain;
  if ( 0 != tdomain )
  {
    if ( !tdomain->IsValid() || tdomain->IsDecreasing() )
      return false;
    if (    tdomain->m_t[0] <= path_domain.m_t[0] 
         && tdomain->m_t[1] >= path_domain.m_t[1] )
    {
      tdomain = 0;
    }
    else
    {
      if ( tdomain->m_t[0] > path_domain.m_t[0] )
        path_domain.m_t[0] = tdomain->m_t[0];
      if ( tdomain->m_t[1] < path_domain.m_t[1] )
        path_domain.m_t[1] = tdomain->m_t[1];
      if ( !path_domain.IsValid() || path_domain.IsDecreasing() )
        return false;
      tdomain = &path_domain;
    }
  }

  // Use the ON_Line "m_path" to get a "profile_2dP", a 2d point, to used 
  // to calculate the profile parameter.
  double elevation_t = ON_UNSET_VALUE;
  if ( !m_path.ClosestPointTo(P,&elevation_t) || !ON_IsValid(elevation_t) )
    return false;
  const ON_3dPoint elevation_P = m_path.PointAt(elevation_t);
  const ON_3dVector zaxis = m_path.Tangent();
  const ON_3dVector yaxis = m_up;
  ON_3dVector xaxis = ON_CrossProduct(yaxis,zaxis);
  if ( !xaxis.IsUnitVector() )
    xaxis.Unitize();
  const ON_3dPoint profile_2dP(xaxis*(P - elevation_P),yaxis*(P - elevation_P),0.0);
  if ( !profile_2dP.IsValid() )
    return false;
  double profile_parameter = ON_UNSET_VALUE;
  if ( 0 != sdomain && sdomain->IsSingleton() )
  {
    profile_parameter = sdomain->m_t[0];
  }
  else if ( !m_profile->GetClosestPoint(profile_2dP,&profile_parameter,maximum_distance,sdomain) 
            || !ON_IsValid(profile_parameter)
           )
  {
    return false;
  }
  const ON_3dPoint Q2d = m_profile->PointAt(profile_parameter);
  if ( !Q2d.IsValid() )
    return false;

  // now calsulate "L", the extrusion line for the profile point.
  ON_Line L;
  const ON_3dPoint path_start = PathStart();
  if ( !path_start.IsValid() )
    return false;
  const ON_3dPoint path_end = PathEnd();
  if ( !path_end.IsValid() )
    return false;
  if ( IsMitered() )
  {
    ON_Xform xform0, xform1;
    if ( !ON_GetEndCapTransformation(path_start, zaxis, m_up, m_bHaveN[0]?&m_N[0]:0, xform0, 0,0) )
      return false;
    if ( !ON_GetEndCapTransformation(path_end,   zaxis, m_up, m_bHaveN[1]?&m_N[1]:0, xform1, 0,0) )
      return false;
    L.from = xform0*Q2d;
    L.to   = xform1*Q2d;
  }
  else
  {
    const ON_3dVector D = Q2d.x*xaxis + Q2d.y*yaxis;
    L.from = path_start + D;
    L.to   = path_end   + D;
  }
  
  // ... and find the point on "L" closest to P.
  double L_parameter = ON_UNSET_VALUE;
  if ( !L.ClosestPointTo(P,&L_parameter) || !ON_IsValid(L_parameter) )
    return false;
  if ( L_parameter < 0.0 )
    L_parameter = 0.0;
  else if ( L_parameter > 1.0 )
    L_parameter = 1.0;

  // convert L_paramter into a path_paramter and make sure
  // path_parameter satisfies any domain restrictions.
  double path_parameter = m_path_domain.ParameterAt(L_parameter);
  if ( 0 != tdomain )
  {
    // "path_domain" is a sub-domain of "m_path_domain".
    if ( path_parameter < path_domain[0] )
    {
      path_parameter = path_domain[0];
      // use m_path_domain to restrict L_paramter
      L_parameter = m_path_domain.NormalizedParameterAt(path_parameter);
    }
    else if ( path_parameter > path_domain[1] )
    {
      path_parameter = path_domain[1];
      // use m_path_domain to restrict L_paramter
      L_parameter = m_path_domain.NormalizedParameterAt(path_parameter);
    }
  }

  if ( maximum_distance > 0.0 )
  {
    ON_3dPoint Q = L.PointAt(L_parameter);
    double d = Q.DistanceTo(P);
    if ( d > maximum_distance )
      return false;
  }
  if ( s )
    *s = profile_parameter;
  if ( t )
    *t = path_parameter;

  return true;
}

ON_BOOL32 ON_Extrusion::GetLocalClosestPoint( 
    const ON_3dPoint& test_point,
    double s0, double t0,     // seed_parameters
    double* s, double* t,   // parameters of local closest point returned here
    const ON_Interval* sdomain, // first parameter sub_domain
    const ON_Interval* tdomain  // second parameter sub_domain
    ) const
{
  if ( s )
    *s = s0;
  if ( t )
    *t = t0;

  if ( 0 == m_profile || !ON_IsValid(s0) || !ON_IsValid(t0) )
    return false;

  ON_NurbsSurface NS;
  const int rc = GetNurbForm(NS);
  if ( rc <= 0 ) 
    return false;

  double a = s0;
  double b = t0;

	// Domain restrictions must be transformed to nurbs parameter space
	const ON_Interval* pNdom[2]={sdomain,tdomain};
	ON_Interval NSdom;
	ON_Interval NTdom;

  const int profile_index = PathParameter();

  double profile_input_parameter = ON_UNSET_VALUE;
  double* profile_local_parameter = 0;
  double* profile_output_parameter = 0;
  const ON_Interval* profile_input_domain = 0;
  ON_Interval* profile_local_domain = 0;

  if ( 2 == rc )
  {
    if ( 0 == profile_index )
    {
      profile_input_parameter = s0;
      profile_output_parameter = s;
      profile_local_parameter = &a;
      profile_input_domain = sdomain;
      profile_input_domain = &NSdom;
    }
    else if (1 == profile_index )
    {
      profile_input_parameter = t0;
      profile_output_parameter = t;
      profile_local_parameter = &b;
      profile_input_domain = tdomain;
      profile_local_domain = &NTdom;
    }
    else
    {
      return false;
    }
    *profile_local_parameter = profile_input_parameter;
    if (!m_profile->GetNurbFormParameterFromCurveParameter(profile_input_parameter, profile_local_parameter))
      return false;
		if ( 0 != profile_input_domain && 0 != profile_local_domain )
		{
      *profile_local_domain = *profile_input_domain;
			if(!m_profile->GetNurbFormParameterFromCurveParameter(profile_input_domain->m_t[0], &profile_local_domain->m_t[0]))
				return false;
			if(!m_profile->GetNurbFormParameterFromCurveParameter(profile_input_domain->m_t[1], &profile_local_domain->m_t[1]))
				return false;
      pNdom[profile_index] = profile_local_domain;
		}
  }

  if (!NS.GetLocalClosestPoint(test_point, a, b, &a, &b, pNdom[0], pNdom[1]))
    return false;

  if ( s ) 
    *s = a;
  if ( t ) 
    *t = b;

  if ( 2 == rc 
       && 0 != profile_local_parameter 
       && 0 != profile_output_parameter 
     )
  {
    if (!m_profile->GetCurveParameterFromNurbFormParameter(*profile_local_parameter, profile_output_parameter))
      return false;
  }

  return true;
}


//ON_BOOL32 ON_Extrusion::GetLocalClosestPoint( const ON_3dPoint&, // test_point
//        double,double,     // seed_parameters
//        double*,double*,   // parameters of local closest point returned here
//        const ON_Interval* = NULL, // first parameter sub_domain
//        const ON_Interval* = NULL  // second parameter sub_domain
//        ) const
//ON_Surface* ON_Extrusion::Offset(
//      double offset_distance, 
//      double tolerance, 
//      double* max_deviation = NULL
//      ) const
int ON_Extrusion::GetNurbForm(
      ON_NurbsSurface& nurbs_surface,
      double tolerance
      ) const
{
  if ( !m_profile )
    return 0;

  ON_Xform xform0,xform1;
  const ON_3dVector pathT = m_path.Tangent();
  if ( !GetProfileTransformation(0,xform0) )
    return false;
  if ( !GetProfileTransformation(1,xform1) )
    return false;

  ON_NurbsCurve nc0;
  int rc = m_profile->GetNurbForm(nc0,tolerance);
  if ( rc <= 0 )
    return rc;
  if ( 3 != nc0.m_dim )
    nc0.ChangeDimension(3);
  ON_NurbsCurve nc1 = nc0;
  nc0.Transform(xform0);
  nc1.Transform(xform1);

  nurbs_surface.Create(3,nc0.m_is_rat,nc0.m_order,2,nc0.m_cv_count,2);
  memcpy(nurbs_surface.m_knot[0],nc0.m_knot,nurbs_surface.KnotCount(0)*sizeof(nurbs_surface.m_knot[0][0]));
  nurbs_surface.m_knot[1][0] = m_path_domain[0];
  nurbs_surface.m_knot[1][1] = m_path_domain[1];
  for ( int i = 0; i < nurbs_surface.m_cv_count[0]; i++ )
  {
    nurbs_surface.SetCV(i,0,ON::intrinsic_point_style,nc0.CV(i));
    nurbs_surface.SetCV(i,1,ON::intrinsic_point_style,nc1.CV(i));
  }

  return rc;
}

int ON_Extrusion::HasNurbForm() const
{
  return m_profile ? m_profile->HasNurbForm() : 0;
}

bool ON_Extrusion::GetSurfaceParameterFromNurbFormParameter(
      double nurbs_s, double nurbs_t,
      double* surface_s, double* surface_t
      ) const
{
  bool rc = true;
  if ( m_bTransposed )
  {
    double* p = surface_s; 
    surface_s = surface_t; 
    surface_t = p;
    double t = nurbs_s;
    nurbs_s = nurbs_t;
    nurbs_t = t;
  }
  if ( surface_s )
  {
    rc = m_profile 
       ? (m_profile->GetCurveParameterFromNurbFormParameter(nurbs_s,surface_s)?true:false) 
       : false;
  }
  if ( surface_t )
    *surface_t = nurbs_t;
  return rc;
}

bool ON_Extrusion::GetNurbFormParameterFromSurfaceParameter(
      double surface_s, double surface_t,
      double* nurbs_s,  double* nurbs_t
      ) const
{
  bool rc = true;
  if ( m_bTransposed )
  {
    double p = surface_s; 
    surface_s = surface_t; 
    surface_t = p;
    double* t = nurbs_s;
    nurbs_s = nurbs_t;
    nurbs_t = t;
  }
  if ( nurbs_s )
  {
    rc = m_profile 
      ? (m_profile->GetNurbFormParameterFromCurveParameter(surface_s,nurbs_s)?true:false)
      : false;
  }
  if ( nurbs_t )
    *nurbs_t = surface_t;
  return rc;
}



ON_Extrusion* ON_Extrusion::Cylinder( 
  const ON_Cylinder& cylinder, 
  bool bCapBottom,
  bool bCapTop,
  ON_Extrusion* extrusion
  )
{
  if ( !cylinder.IsValid() || !cylinder.IsFinite() )
    return 0;

  ON_Line path;
  path.from = cylinder.circle.plane.PointAt(0.0,0.0,cylinder.height[0]);
  path.to   = cylinder.circle.plane.PointAt(0.0,0.0,cylinder.height[1]);
  if ( !path.IsValid() || !(path.Length() > ON_ZERO_TOLERANCE) )
    return 0;

  ON_3dVector up = cylinder.circle.plane.yaxis;
  if (    !up.IsValid()
       || !up.IsUnitVector()
       || fabs(up*path.Tangent()) > ON_SQRT_EPSILON 
       )
    return 0;

  ON_ArcCurve* circle_curve = new ON_ArcCurve(cylinder.circle);
  circle_curve->m_arc.plane = ON_Plane::World_xy;
  circle_curve->m_dim = 2;
  if ( !circle_curve->IsValid() )
  {
    delete circle_curve;
    return 0;
  }

  ON_Extrusion* extrusion_cylinder = 0;
  if ( extrusion )
  {
    extrusion->Destroy();
    extrusion_cylinder = extrusion;
  }
  else
  {
    extrusion_cylinder = new ON_Extrusion();
  }

  if (    !extrusion_cylinder->SetPathAndUp(path.from,path.to,up)
       || !extrusion_cylinder->SetOuterProfile(circle_curve,false)
       || !extrusion_cylinder->IsValid()
       || !extrusion_cylinder->SetDomain(extrusion_cylinder->PathParameter(),cylinder.height[0],cylinder.height[1])
     )
  {
    if ( 0 == extrusion )
      delete extrusion_cylinder;
    return 0;
  }

  extrusion_cylinder->m_bCap[0] = bCapBottom ? true : false;
  extrusion_cylinder->m_bCap[1] = bCapTop    ? true : false;

  if ( !extrusion_cylinder->IsValid() )
  {
    if ( 0 == extrusion )
      delete extrusion_cylinder;
    return 0;
  }

  return extrusion_cylinder;
}



ON_Extrusion* ON_Extrusion::Pipe( 
  const ON_Cylinder& cylinder, 
  double other_radius,
  bool bCapBottom,
  bool bCapTop,
  ON_Extrusion* extrusion
  )
{
  if (    !cylinder.IsValid() 
       || !ON_IsValid(other_radius)
       || !(fabs(other_radius - cylinder.circle.Radius()) > ON_ZERO_TOLERANCE)
       )
  {
    return 0;
  }

  double inner_radius = (other_radius < cylinder.circle.radius)
                      ? other_radius
                      : cylinder.circle.radius;
  double outer_radius = (other_radius < cylinder.circle.radius)
                      ? cylinder.circle.radius
                      : other_radius;
  if (    !ON_IsValid(inner_radius) 
       || !ON_IsValid(outer_radius)
       || !(outer_radius - inner_radius > ON_ZERO_TOLERANCE)
     )
  {
    return 0;
  }

  ON_Cylinder outer_cylinder = cylinder;
  outer_cylinder.circle.radius = outer_radius;

  ON_Circle inner_circle(ON_Plane::World_xy,inner_radius);
  ON_ArcCurve* inner_profile = new ON_ArcCurve(inner_circle);
  inner_profile->m_dim = 2;
  if ( !inner_profile->IsValid() )
  {
    delete inner_profile;
    return 0;
  }

  ON_Extrusion* extrusion_pipe = ON_Extrusion::Cylinder(outer_cylinder,bCapBottom,bCapTop,extrusion);
  if ( 0 == extrusion_pipe )
  {
    delete inner_profile;
    return 0;
  }

  if ( !extrusion_pipe->IsValid() )
  {
    if ( 0 == extrusion )
      delete extrusion_pipe;
    delete inner_profile;
    return 0;
  }

  if ( !extrusion_pipe->AddInnerProfile(inner_profile) )
  {
    if ( 0 == extrusion )
      delete extrusion_pipe;
    delete inner_profile;
    return 0;
  }

  if ( !extrusion_pipe->IsValid() )
  {
    if ( 0 == extrusion )
      delete extrusion_pipe;
    return 0;
  }

  return extrusion_pipe;
}

