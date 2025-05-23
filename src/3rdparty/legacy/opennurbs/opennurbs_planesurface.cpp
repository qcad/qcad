/* $NoKeywords: $ */
/*
//
// Copyright (c) 1993-2007 Robert McNeel & Associates. All rights reserved.
// Rhinoceros is a registered trademark of Robert McNeel & Assoicates.
//
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
// ALL IMPLIED WARRANTIES OF FITNESS FOR ANY PARTICULAR PURPOSE AND OF
// MERCHANTABILITY ARE HEREBY DISCLAIMED.
//				
// For complete openNURBS copyright information see <http://www.opennurbs.org>.
//
////////////////////////////////////////////////////////////////
*/

#include "opennurbs.h"

ON_OBJECT_IMPLEMENT(ON_PlaneSurface,ON_Surface,"4ED7D4DF-E947-11d3-BFE5-0010830122F0");
ON_OBJECT_IMPLEMENT(ON_ClippingPlaneSurface,ON_PlaneSurface,"DBC5A584-CE3F-4170-98A8-497069CA5C36");


ON_PlaneSurface::ON_PlaneSurface()
{}

ON_PlaneSurface::ON_PlaneSurface( const ON_PlaneSurface& src )
{
  *this = src;
}

ON_PlaneSurface& ON_PlaneSurface::operator=( const ON_PlaneSurface& src )
{
  if ( this != &src ) {
    ON_Surface::operator=(src);
    m_plane = src.m_plane;
    m_domain[0] = src.m_domain[0];
    m_domain[1] = src.m_domain[1];
    m_extents[0] = src.m_extents[0];
    m_extents[1] = src.m_extents[1];
  }
  return *this;
}

ON_PlaneSurface::ON_PlaneSurface( const ON_Plane& src )
{
  *this = src;
}


unsigned int ON_PlaneSurface::SizeOf() const
{
  unsigned int sz = ON_Surface::SizeOf();
  sz += (sizeof(*this) - sizeof(ON_Surface));
  return sz;
}

ON__UINT32 ON_PlaneSurface::DataCRC(ON__UINT32 current_remainder) const
{
  current_remainder = ON_CRC32(current_remainder,sizeof(m_plane),&m_plane);
  current_remainder = ON_CRC32(current_remainder,2*sizeof(m_domain[0]),&m_domain[0]);
  current_remainder = ON_CRC32(current_remainder,2*sizeof(m_extents[0]),&m_extents[0]);
  return current_remainder;
}


ON_PlaneSurface& ON_PlaneSurface::operator=( const ON_Plane& src )
{
  m_plane = src;
  m_domain[0].Set(0.0,1.0);
  m_domain[1].Set(0.0,1.0);
  m_extents[0] = m_domain[0];
  m_extents[1] = m_domain[1];
  return *this;
}

ON_PlaneSurface::~ON_PlaneSurface()
{}

ON_BOOL32
ON_PlaneSurface::IsValid( ON_TextLog* text_log ) const
{
  return (   m_plane.IsValid() 
           && m_domain[0].IsIncreasing() && m_domain[1].IsIncreasing() 
           && m_extents[0].IsIncreasing() && m_extents[1].IsIncreasing() 
           ) ? true : false;
}

void
ON_PlaneSurface::Dump( ON_TextLog& dump ) const
{
  dump.Print("ON_PlaneSurface\n");
}

ON_BOOL32 
ON_PlaneSurface::Write(
       ON_BinaryArchive& file  // open binary file
     ) const
{
  ON_BOOL32 rc = file.Write3dmChunkVersion(1,1);

  // version 1.0 chunks
  if (rc)
    rc = file.WritePlane( m_plane );
  if (rc)
    rc = file.WriteInterval( m_domain[0] );
  if (rc)
    rc = file.WriteInterval( m_domain[1] );
  
  // added to version 1.1 chunks
  if (rc)
    rc = file.WriteInterval( m_extents[0] );
  if (rc)
    rc = file.WriteInterval( m_extents[1] );
  return rc;
}

ON_BOOL32 
ON_PlaneSurface::Read(
       ON_BinaryArchive& file // open binary file
     )
{
  int major_version = 0;
  int minor_version = 0;
  ON_BOOL32 rc = file.Read3dmChunkVersion(&major_version,&minor_version);
  if (rc && major_version == 1) {
    // common to all 1.x formats
    if (rc)
      rc = file.ReadPlane( m_plane );
    if (rc)
      rc = file.ReadInterval( m_domain[0] );
    if (rc)
      rc = file.ReadInterval( m_domain[1] );
    m_extents[0] = m_domain[0];
    m_extents[1] = m_domain[1];
    if ( minor_version >= 1 )
    {
      if (rc)
        rc = file.ReadInterval( m_extents[0] );
      if (rc)
        rc = file.ReadInterval( m_extents[1] );
    }
  }
  return rc;
}

int 
ON_PlaneSurface::Dimension() const
{
  return 3;
}

ON_BOOL32 
ON_PlaneSurface::GetBBox( // returns true if successful
         double* boxmin,    // minimum
         double* boxmax,    // maximum
         ON_BOOL32 bGrowBox
         ) const
{
  int i,j,k=0;
  ON_3dPoint corner[4];
  for ( i = 0; i < 2; i++ ) for ( j = 0; j < 2; j++ ) {
    corner[k++] = PointAt( m_domain[0].m_t[i], m_domain[1].m_t[j] );
  }
  return ON_GetPointListBoundingBox( 3, 0, 4, 3, 
                                     &corner[0].x, 
                                     boxmin, 
                                     boxmax, bGrowBox?true:false );
}

ON_BOOL32
ON_PlaneSurface::Transform( const ON_Xform& xform )
{
  TransformUserData(xform);
  ON_3dPoint p = m_plane.origin + m_extents[0][0]*m_plane.xaxis + m_extents[1][0]*m_plane.yaxis;
  ON_3dPoint q = m_plane.origin + m_extents[0][1]*m_plane.xaxis + m_extents[1][1]*m_plane.yaxis;
  bool rc = m_plane.Transform( xform )?true:false;
  if (rc && fabs(fabs(xform.Determinant())-1.0) > ON_SQRT_EPSILON )
  {
    p = xform*p;
    q = xform*q;
    double x0, x1, y0, y1;
    rc = false;
    if ( m_plane.ClosestPointTo(p,&x0,&y0) && m_plane.ClosestPointTo(q,&x1,&y1) )
    {
      if ( x0 < x1 && y0 < y1 )
      {
        m_extents[0].Set(x0,x1);
        m_extents[1].Set(y0,y1);
        rc = true;
      }
    }
  }
  return rc;
}

ON_Interval ON_PlaneSurface::Domain( int dir ) const
{
  // evaluation domain - do not confuse with m_extents
  return dir ? m_domain[1] : m_domain[0];
}

int ON_PlaneSurface::SpanCount( int dir ) const
{
  return 1;
}

ON_BOOL32 ON_PlaneSurface::GetSurfaceSize( 
    double* width, 
    double* height 
    ) const
{
  if ( width ) 
    *width = Extents(0).Length();
  if ( height ) 
    *height = Extents(1).Length();
  return true;
}


ON_BOOL32 ON_PlaneSurface::GetSpanVector( int dir, double* s ) const
{
  ON_Interval d = Domain(dir);
  s[0] = d.Min();
  s[1] = d.Max();
  return d.IsIncreasing();
}

int ON_PlaneSurface::Degree( int dir ) const
{
  return 1;
}

ON_BOOL32 
ON_PlaneSurface::GetParameterTolerance(
         int dir,
         double t,  // t = parameter in domain
         double* tminus, // tminus
         double* tplus   // tplus
         ) const
{
  dir = (dir)?1:0;
  return ON_GetParameterTolerance( m_domain[dir][0], m_domain[dir][1], t, tminus, tplus );
}

ON_BOOL32 ON_PlaneSurface::IsPlanar( ON_Plane* plane, double tolerance ) const
{
  if ( plane )
    *plane = this->m_plane;
  return true;
}

ON_BOOL32 
ON_PlaneSurface::IsClosed( int dir ) const
{
  return false;
}

ON_BOOL32 
ON_PlaneSurface::IsPeriodic( int dir ) const
{
  return false;
}

ON_BOOL32 
ON_PlaneSurface::IsSingular( int side ) const
{
  return false;
}

bool ON_PlaneSurface::GetNextDiscontinuity( 
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
  return ON_Surface::GetNextDiscontinuity(dir,c,t0,t1,t,hint,dtype,cos_angle_tolerance,curvature_tolerance);
}

ON_BOOL32
ON_PlaneSurface::Reverse( int dir )
{
  if ( dir < 0 || dir > 1 )
    return false;
  m_extents[dir].Reverse();
  m_domain[dir].Reverse();
  if ( dir )
    m_plane.yaxis.Reverse();
  else
    m_plane.xaxis.Reverse();
  m_plane.zaxis.Reverse();
  m_plane.UpdateEquation();
  return true;
}

bool ON_PlaneSurface::IsContinuous(
    ON::continuity desired_continuity,
    double s, 
    double t, 
    int* hint, // default = NULL,
    double point_tolerance, // default=ON_ZERO_TOLERANCE
    double d1_tolerance, // default==ON_ZERO_TOLERANCE
    double d2_tolerance, // default==ON_ZERO_TOLERANCE
    double cos_angle_tolerance, // default==0.99984769515639123915701155881391
    double curvature_tolerance  // default==ON_SQRT_EPSILON
    ) const
{
  return true;
}

ON_BOOL32
ON_PlaneSurface::Transpose()
{
  // swaps x and y axes and reverses zaxis
  m_plane.Flip();

  ON_Interval i = m_domain[0];
  m_domain[0] = m_domain[1];
  m_domain[1] = i;

  i = m_extents[0];
  m_extents[0] = m_extents[1];
  m_extents[1] = i;

  return true;
}

ON_BOOL32 
ON_PlaneSurface::Evaluate( // returns false if unable to evaluate
       double s, double t, // evaluation parameters
       int der_count,  // number of derivatives (>=0)
       int v_stride,   // v[] array stride (>=Dimension())
       double* v,      // v[] array of length stride*(ndir+1)
       int side,       // optional - determines which side to evaluate from
                       //         0 = default
                       //      <  0 to evaluate from below, 
                       //      >  0 to evaluate from above
       int* hint       // optional - evaluation hint (int) used to speed
                       //            repeated evaluations
       ) const
{
  double ds = 1.0;
  double dt = 1.0;
  if ( m_extents[0] != m_domain[0] )
  {
    s = m_extents[0].ParameterAt( m_domain[0].NormalizedParameterAt(s) );
    ds = m_extents[0].Length()/m_domain[0].Length();
  }
  if ( m_extents[1] != m_domain[1] )
  {
    t = m_extents[1].ParameterAt( m_domain[1].NormalizedParameterAt(t) );
    dt = m_extents[1].Length()/m_domain[1].Length();
  }
  ON_3dPoint P = m_plane.PointAt( s, t );
  v[0] = P.x;
  v[1] = P.y;
  v[2] = P.z;
  v += v_stride;
  if ( der_count >= 1 ) 
  {
    v[0] = ds*m_plane.xaxis.x;
    v[1] = ds*m_plane.xaxis.y;
    v[2] = ds*m_plane.xaxis.z;
    v += v_stride;

    v[0] = dt*m_plane.yaxis.x;
    v[1] = dt*m_plane.yaxis.y;
    v[2] = dt*m_plane.yaxis.z;
    v += v_stride;

    if ( der_count > 1 ) 
    {
      // zero higher partials
      memset( v, 0, (((der_count+1)*(der_count+2)/2-4)*v_stride+3)*sizeof(*v) );
    }
  }
  return true;
}

ON_Curve* ON_PlaneSurface::IsoCurve( int dir, double c ) const
{
  ON_LineCurve* line_curve = 0;
  if ( dir == 0 || dir == 1 && IsValid() ) 
  {
    ON_Line line;
    ON_Interval domain = Domain(dir);
    if ( dir == 1 )
    {
      line.from = PointAt( c, domain[0] );
      line.to = PointAt( c, domain[1] );
    }
    else
    {
      line.from = PointAt( domain[0], c );
      line.to = PointAt( domain[1], c );
    }
    line_curve = new ON_LineCurve(line);
    line_curve->m_dim = 3;
    line_curve->m_t = domain;
  }
  return line_curve;
}

ON_Curve* ON_PlaneSurface::Pushup( const ON_Curve& curve_2d,
                  double tolerance,
                  const ON_Interval* curve_2d_subdomain
                  ) const
{
  // see if it's an easy iso curve
  ON_Curve* curve = ON_Surface::Pushup( curve_2d, tolerance, curve_2d_subdomain );

  if ( 0 == curve )
  {
    const ON_PolyCurve* polycurve = ON_PolyCurve::Cast(&curve_2d);
    if ( 0 != polycurve )
    {
      return PushupPolyCurve( *polycurve, tolerance, curve_2d_subdomain );
    }

    const ON_CurveProxy* proxycurve = ON_CurveProxy::Cast(&curve_2d);
    if ( 0 != proxycurve )
    {
      return PushupCurveProxy( *proxycurve, tolerance, curve_2d_subdomain );
    }

    ON_NurbsCurve* nurbs_curve = new ON_NurbsCurve();
    if ( curve_2d.GetNurbForm(*nurbs_curve,0.0,curve_2d_subdomain) )
    {
      ON_Xform xform;
      xform.ChangeBasis( m_plane, ON_xy_plane );
      nurbs_curve->ChangeDimension(3);
      // kill z coordinate if somebody passed in a fat curve_2d.
      for ( int i = 0; i < nurbs_curve->m_cv_count; i++ )
        nurbs_curve->CV(i)[2] = 0.0;
      if ( m_domain[0] != m_extents[0] || m_domain[1] != m_extents[1] )
      {
        // transform curve to plane's coordinate system;
        ON_Xform cs_change(1);
        ON_Interval s = Domain(0);
        ON_Interval t = Domain(1);
        ON_Interval x = Extents(0);
        ON_Interval y = Extents(1);
        if ( s != x )
        {
          double ds = s.Length();
          double dx = x.Length();
          cs_change.m_xform[0][0] = dx/ds;
          cs_change.m_xform[0][3] = (s[1]*x[0] - s[0]*x[1])/ds;
        }
        if ( t != y )
        {
          double dt = t.Length();
          double dy = y.Length();
          cs_change.m_xform[1][1] = dy/dt;
          cs_change.m_xform[1][3] = (t[1]*y[0] - t[0]*y[1])/dt;
        }
        xform = xform*cs_change;
      }
      nurbs_curve->Transform(xform);

      // TODO check for and remove degenerate spans created by projecting
      //      spans that are perp to the plane.

      curve = nurbs_curve;
    }
    if (0 == curve)
      delete nurbs_curve;
  }

  return curve;
}

ON_Curve* ON_Surface::PushupPolyCurve( 
                  const ON_PolyCurve& polycurve, // 2d polycurve
                  double tolerance,
                  const ON_Interval* curve_2d_subdomain
                  ) const
{
  ON_Curve* pushup = 0;
  
  ON_PolyCurve* polycurve_pushup = 0;

  ON_Curve* segment_pushup = 0;
  const ON_Curve* segment_curve = 0;
  ON_Interval segment_curve_domain;

  ON_3dPoint prev_segment_2d_end = ON_UNSET_POINT;

  int i, count = polycurve.Count();
  for ( i = 0; i < count; i++ )
  {
    segment_pushup=0;
    segment_curve = polycurve.SegmentCurve(i);
    ON_Interval segment_domain = polycurve.SegmentDomain(i); // polycurve parameters
    
    if ( 0 != curve_2d_subdomain )
    {
      if ( curve_2d_subdomain->Max() <= segment_domain[0] ) 
        continue;
      if ( curve_2d_subdomain->Min() >= segment_domain[1] ) 
        continue;
    }

    if ( 0 != segment_curve )
    {
      // get sub-domain of this segment to pushup
      segment_curve_domain = segment_curve->Domain();
      if ( 0 != curve_2d_subdomain )
      {
        ON_Interval d0 = segment_domain;
        d0.Intersection( *curve_2d_subdomain );
        if ( !d0.IsIncreasing() )
          continue;
        if ( d0 != segment_domain )
        {
          if ( segment_domain == segment_curve_domain )
            segment_curve_domain = d0;
          else
          {
            double t0 = segment_curve_domain.ParameterAt(segment_domain.NormalizedParameterAt(d0[0]));
            double t1 = segment_curve_domain.ParameterAt(segment_domain.NormalizedParameterAt(d0[1]));
            segment_curve_domain.Intersection(ON_Interval(t0,t1));
            if ( !segment_curve_domain.IsIncreasing() )
              continue;
          }
          segment_domain = d0;
        }
      }

      segment_pushup = Pushup(*segment_curve,tolerance,&segment_curve_domain);

      if (prev_segment_2d_end.x != ON_UNSET_VALUE && 0 != pushup && 0 != segment_pushup )
      {
        ON_3dPoint this_segment_2d_start = segment_curve->PointAt(segment_curve_domain[0]);
        if ( 0 == ON_ComparePoint( 3, 0, &this_segment_2d_start.x, &prev_segment_2d_end.x ) )
        {
          // ends of input curve match - make sure pushups also match
          ON_3dPoint prev_pushup_end = pushup->PointAtEnd();
          ON_3dPoint this_pushup_start = segment_pushup->PointAtStart();
          if ( ON_ComparePoint( 3, 0, &prev_pushup_end.x, &this_pushup_start.x ) )
          {
            pushup->SetEndPoint(this_pushup_start);
          }
        }
      }

      prev_segment_2d_end = segment_curve->PointAt(segment_curve_domain[1]);
    }

    if ( 0 == segment_pushup )
    {
      if ( 0 != pushup )
      {
        delete pushup;
        pushup = 0;
        polycurve_pushup = 0;
      }
      break;
    }

    segment_pushup->SetDomain( segment_domain[0], segment_domain[1] );
    if ( 0 == pushup )
    {
      pushup = segment_pushup;
    }
    else
    {
      if ( 0 == polycurve_pushup )
      {
        polycurve_pushup = new ON_PolyCurve();
        polycurve_pushup->Append(pushup);
        pushup = polycurve_pushup;
      }      
      polycurve_pushup->Append(segment_pushup);
    }
  }

  return pushup;    
}


static int PullbackSegOnSeam( const ON_Interval& udom, const ON_Interval& vdom,
                               ON_BOOL32 bClosedU, ON_BOOL32 bClosedV,
                               const ON_Curve* segment_pullback
                               )
{
  int seg_on_seam = 0;
  if ( 0 != segment_pullback )
  {
    if ( bClosedU || bClosedV )
    {
      const double side_tol = 0.0001;
      ON_BoundingBox bbox = segment_pullback->BoundingBox();
      if ( bbox.IsValid() )
      {
        double u0 = udom.NormalizedParameterAt(bbox.m_min.x);
        double u1 = udom.NormalizedParameterAt(bbox.m_max.x);
        double v0 = vdom.NormalizedParameterAt(bbox.m_min.y);
        double v1 = vdom.NormalizedParameterAt(bbox.m_max.y);

        if ( v1 <= side_tol && bClosedV  )
          seg_on_seam = 1; // south side
        else if ( v0 >= 1.0-side_tol && bClosedV )
          seg_on_seam = 3; // north side

        if ( u1 <= side_tol && bClosedU  )
        {
          if ( 0 == seg_on_seam )
            seg_on_seam = 4; // west side
          else
            seg_on_seam = 0;
        }
        else if ( u0 >= 1.0-side_tol && bClosedU  )
        {
          if ( 0 == seg_on_seam )
            seg_on_seam = 1; // east side
          else
            seg_on_seam = 0;
        }
      }
    }
  }
  return seg_on_seam;
}


ON_Curve* ON_Surface::PullbackPolyCurve( 
                  const ON_PolyCurve&  polycurve,
                  double tolerance,
                  const ON_Interval* curve_3d_subdomain,
                  ON_3dPoint start_uv,
                  ON_3dPoint end_uv
                  ) const
{
  // tool for ON_Surface::Pullback overrides to call to pullback
  // polycurves segment-by-segment
  
  ON_Curve* pullback = 0;
  
  ON_PolyCurve* polycurve_pullback = 0;

  ON_Curve* segment_pullback = 0;
  const ON_Curve* segment_curve = 0;
  ON_Interval segment_curve_domain;

  ON_3dPoint segment_start_uv = ON_UNSET_POINT;
  ON_3dPoint segment_end_uv = ON_UNSET_POINT;
  ON_3dPoint prev_segment_3d_end = ON_UNSET_POINT;
  bool bUseStartPoint = true;
  bool bLastSegment = false;
  int first_seg_on_seam = 0; // 0 = no, 1 = south side, 2 = east, 3 = north, 4 = west
  ON_Interval first_seg_pullback_domain; // used for backup pullback
  const ON_Curve* first_seg_3d_curve = 0;

  ON_BOOL32 bClosedU = false;
  ON_BOOL32 bClosedV = false;
  const ON_Interval udom = Domain(0);
  const ON_Interval vdom = Domain(1);

  int i, count = polycurve.Count();
  for ( i = 0; i < count; i++ )
  {
    segment_pullback=0;
    segment_curve = polycurve.SegmentCurve(i);
    ON_Interval segment_domain = polycurve.SegmentDomain(i); // polycurve parameters
    
    if ( 0 != curve_3d_subdomain )
    {
      if ( curve_3d_subdomain->Max() <= segment_domain[0] ) 
        break;

      if ( curve_3d_subdomain->Min() >= segment_domain[1] ) 
        continue;

      if ( i == count-1 || curve_3d_subdomain->Max() <= segment_domain[1] )
        bLastSegment = true;
    }
    else if ( i == count-1 )
      bLastSegment = true;

    if ( 0 != segment_curve )
    {
      // get sub-domain of this segment to pullback
      segment_curve_domain = segment_curve->Domain();
      if ( 0 != curve_3d_subdomain )
      {
        ON_Interval d0 = segment_domain;
        d0.Intersection( *curve_3d_subdomain );
        if ( !d0.IsIncreasing() )
          continue;
        if ( d0 != segment_domain )
        {
          if ( segment_domain == segment_curve_domain )
            segment_curve_domain = d0;
          else
          {
            double t0 = segment_curve_domain.ParameterAt(segment_domain.NormalizedParameterAt(d0[0]));
            double t1 = segment_curve_domain.ParameterAt(segment_domain.NormalizedParameterAt(d0[1]));
            segment_curve_domain.Intersection(ON_Interval(t0,t1));
            if ( !segment_curve_domain.IsIncreasing() )
              continue;
          }
          segment_domain = d0;
        }
      }

      // start start uv
      segment_start_uv = ON_UNSET_POINT;

      //use start point if this is the first segment with domain intersecting subdom
      //if ( i == 0 )
      if (bUseStartPoint)
      {
        segment_start_uv = start_uv;
        bUseStartPoint = false;
      }
      else if ( prev_segment_3d_end.x != ON_UNSET_VALUE && 0 != pullback )
      {
        double d = segment_curve->PointAt(segment_curve_domain[0]).DistanceTo(prev_segment_3d_end);
        if ( d <= tolerance )
        {
          segment_start_uv = pullback->PointAtEnd();
        }
      }

      // set end uv

      //use end point if this is the last segment with domain intersecting subdom
      //segment_end_uv = ( i == count-1 ) ? end_uv : ON_UNSET_POINT;
      segment_end_uv = bLastSegment ? end_uv : ON_UNSET_POINT;

      segment_pullback = Pullback(*segment_curve,tolerance,&segment_curve_domain,segment_start_uv,segment_end_uv);
      prev_segment_3d_end = segment_curve->PointAt(segment_curve_domain[1]);
      if ( 0 == pullback
           && count > 1 
           && 0 != segment_pullback 
           && ON_UNSET_VALUE == segment_start_uv.x 
           && ON_UNSET_VALUE == segment_end_uv.x )
      {
        // 19 September 2003 Dale Lear
        //     Add more seam side detection to fix bugs like RR 10464 DE 12061.
        //     This is the first segment we have pulled back and we don't know where
        //     it starts or ends.  If first_seg_on_seam is set to 1,2,3, or 4, then
        //     the result lies along a surface seam.  It is possible that we choose
        //     the wrong side of parameter space and we need to double check when we
        //     pullback the next segment.
        bClosedU = IsClosed(0);
        bClosedV = IsClosed(1);
        first_seg_on_seam = PullbackSegOnSeam( udom, vdom,bClosedU, bClosedV,segment_pullback);
        if ( 0 != first_seg_on_seam )
        {
          // save the information we need if we have to 
          // redo this pullback below.
          first_seg_3d_curve = segment_curve;
          first_seg_pullback_domain = segment_curve_domain;
        }
      }
      else if ( 0 != pullback && 0 == polycurve_pullback
                && 0 != first_seg_on_seam 
                && 0 != segment_pullback 
                && ON_IsValid(segment_start_uv.x)
                && ON_IsValid(segment_start_uv.y)
                && (! segment_end_uv.IsValid() || segment_end_uv != end_uv )
                )
      {
        // This is the second segment we have pulled back.  The firt segment
        // was on a seam.  If the 2nd segment is not on a seam, we will run
        // a few tests to make sure the first segment is on the correct side
        // of parameter space.
        int second_seg_on_seam = PullbackSegOnSeam( udom, vdom,bClosedU, bClosedV,segment_pullback);
        if ( 0 == second_seg_on_seam )
        {
          // 19 September 2003 Dale Lear
          //     Add more seam side detection to fix bugs like RR 10464 DE 12061.
          //     This is the second segment we have pulled back.  This segment starts
          //     on a surface seam but we were not certain which side of parameter space
          //     the start point was on.   This code double checks the answer by pulling back the
          //     second segment without the suggested start point.

          ON_Curve* test_pullback = Pullback(*segment_curve,tolerance,&segment_curve_domain,ON_UNSET_POINT,ON_UNSET_POINT);
          if ( 0 != test_pullback && 0 == PullbackSegOnSeam( udom, vdom,bClosedU, bClosedV,test_pullback) )
          {
            bool bUseTestSegment = false;
            ON_3dPoint new_first_seg_end_uv = test_pullback->PointAtStart();
            new_first_seg_end_uv.z = 0.0;

            // See if the starts of segment_pullback and test_pullback are on opposite 
            // sides of parameter space.
            ON_3dPoint segStart = segment_pullback->PointAtStart();
            ON_3dPoint testStart = test_pullback->PointAtStart();
            double startSeg_t, testSeg_t;
            const double on_side_tol = 0.0001;
            switch ( first_seg_on_seam )
            {
            case 1: // first seg was on south side
              startSeg_t = vdom.NormalizedParameterAt(segStart.y);
              testSeg_t = vdom.NormalizedParameterAt(testStart.y);
              if ( startSeg_t <= on_side_tol && testSeg_t >= 1.0-on_side_tol )
              {
                // first seg should be on north side
                new_first_seg_end_uv.y = vdom[1];
                bUseTestSegment = true;
              }
              break;
            case 2: // first seg was on east side
              startSeg_t = vdom.NormalizedParameterAt(segStart.x);
              testSeg_t = vdom.NormalizedParameterAt(testStart.x);
              if ( startSeg_t >= 1.0-on_side_tol && testSeg_t <= on_side_tol )
              {
                // first seg should be on west side
                new_first_seg_end_uv.x = udom[0];
                bUseTestSegment = true;
              }
              break;
            case 3: // first seg was on north side
              startSeg_t = vdom.NormalizedParameterAt(segStart.y);
              testSeg_t = vdom.NormalizedParameterAt(testStart.y);
              if ( startSeg_t >= 1.0-on_side_tol && testSeg_t <= on_side_tol )
              {
                // first seg should be on south side
                new_first_seg_end_uv.y = vdom[0];
                bUseTestSegment = true;
              }
              break;
            case 4: // first seg was on west side
              startSeg_t = vdom.NormalizedParameterAt(segStart.x);
              testSeg_t = vdom.NormalizedParameterAt(testStart.x);
              if ( startSeg_t <= on_side_tol && testSeg_t >= 1.0-on_side_tol )
              {
                // first seg should be on east side
                new_first_seg_end_uv.x = udom[1];
                bUseTestSegment = true;
              }
              break;
            }

            if ( bUseTestSegment 
                 && 0 != first_seg_3d_curve
                 && first_seg_pullback_domain.IsIncreasing()
                 )
            {
              // We put the first segment on the wrong side of parameter space.
              // Fix things up here.
              ON_Curve* new_first_seg_pullback = Pullback(*first_seg_3d_curve,tolerance,
                                                 &first_seg_pullback_domain,
                                                 ON_UNSET_POINT,
                                                 new_first_seg_end_uv
                                                 );
              if ( 0 != new_first_seg_pullback )
              {
                // Replace what we had with a polycurve that has
                // new_first_pullback + test_pullback as the initial
                // segments.
                ON_Interval dom = pullback->Domain();
                delete pullback;
                pullback = new_first_seg_pullback;
                pullback->SetDomain(dom[0],dom[1]);
                new_first_seg_pullback = 0;
                
                delete segment_pullback;
                segment_pullback = test_pullback;
                test_pullback = 0;       
              }
            }
          }
          
          if ( 0 != test_pullback )
          {
            // clean up unused test segment
            delete test_pullback;
          }
        }
      }
    }
    
    if ( 0 == segment_pullback )
    {
      if ( 0 != pullback )
      {
        delete pullback;
        pullback = 0;
        polycurve_pullback = 0;
      }
      break;
    }

    segment_pullback->SetDomain( segment_domain[0], segment_domain[1] );
    if ( 0 == pullback )
    {
      pullback = segment_pullback;
    }
    else
    {
      if ( 0 == polycurve_pullback )
      {
        polycurve_pullback = new ON_PolyCurve();
        polycurve_pullback->Append(pullback);
        pullback = polycurve_pullback;
      }      
      polycurve_pullback->Append(segment_pullback);
    }
  }

  return pullback;    
} 


ON_Curve* ON_Surface::PullbackCurveProxy( 
                const ON_CurveProxy& curveproxy_3d,
                double tolerance,
                const ON_Interval* curve_3d_subdomain,
                ON_3dPoint start_uv,
                ON_3dPoint end_uv
                ) const
{
  bool bRev = curveproxy_3d.ProxyCurveIsReversed();

  const ON_Curve* real_curve = curveproxy_3d.ProxyCurve();
  if ( 0 == real_curve || real_curve == &curveproxy_3d)
    return 0;

  ON_Interval real_dom = curveproxy_3d.ProxyCurveDomain();
  ON_Interval dom = curveproxy_3d.Domain();
  const ON_Interval* real_c_subdom = 0;
  if ( 0 != curve_3d_subdomain )
  {
    ON_Interval tmp = *curve_3d_subdomain;
    if ( tmp.IsDecreasing() )
    {
      bRev = !bRev;
      tmp.Swap();
    }
    tmp.Intersection(dom);
    if ( !tmp.IsIncreasing() )
      return 0;

    if ( dom.Includes(tmp,true) )
    {
      if ( real_dom == dom )
        real_dom = tmp;
      else
      {
        double a = real_dom.ParameterAt(dom.NormalizedParameterAt(tmp[0]));
        double b = real_dom.ParameterAt(dom.NormalizedParameterAt(tmp[1]));
        real_dom.Set(a,b);
      }
      if ( !real_dom.IsIncreasing() )
        return 0;
      real_c_subdom = &real_dom;
      dom = tmp;
    }
    else real_c_subdom = &real_dom;
  }
  else if (real_dom != real_curve->Domain())
    real_c_subdom = &real_dom;

  if ( bRev )
  {
    ON_3dPoint p = start_uv; start_uv = end_uv; end_uv = p;
  }

  ON_Curve* p2dCrv = Pullback( *real_curve, tolerance, real_c_subdom, start_uv, end_uv );
  if ( 0 != p2dCrv )
  {
    if ( bRev )
      p2dCrv->Reverse();
    p2dCrv->SetDomain(dom);
  }

  return p2dCrv;
}

ON_Curve* ON_Surface::PushupCurveProxy( const ON_CurveProxy& curveproxy_2d,
                  double tolerance,
                  const ON_Interval* curve_2d_subdomain
                  ) const
{
  bool bRev = curveproxy_2d.ProxyCurveIsReversed();

  const ON_Curve* real_curve = curveproxy_2d.ProxyCurve();
  if ( 0 == real_curve || real_curve == &curveproxy_2d)
    return 0;

  ON_Interval real_dom = curveproxy_2d.ProxyCurveDomain();
  ON_Interval dom = curveproxy_2d.Domain();
  const ON_Interval* real_c_subdom = 0;
  if ( 0 != curve_2d_subdomain )
  {
    ON_Interval tmp = *curve_2d_subdomain;
    if ( tmp.IsDecreasing() )
    {
      bRev = !bRev;
      tmp.Swap();
    }
    tmp.Intersection(dom);
    if ( !tmp.IsIncreasing() )
      return 0;

    if ( dom.Includes(tmp,true) )
    {
      if ( real_dom == dom )
        real_dom = tmp;
      else
      {
        double a = real_dom.ParameterAt(dom.NormalizedParameterAt(tmp[0]));
        double b = real_dom.ParameterAt(dom.NormalizedParameterAt(tmp[1]));
        real_dom.Set(a,b);
      }
      if ( !real_dom.IsIncreasing() )
        return 0;
      real_c_subdom = &real_dom;
      dom = tmp;
    }
  }

  ON_Curve* p3dCrv = Pushup( *real_curve, tolerance, real_c_subdom );
  if ( 0 != p3dCrv )
  {
    if ( bRev )
      p3dCrv->Reverse();
    p3dCrv->SetDomain(dom);
  }

  return p3dCrv;
}


ON_Curve* ON_PlaneSurface::Pullback( const ON_Curve& curve_3d,
                  double tolerance,
                  const ON_Interval* curve_3d_subdomain,
                  ON_3dPoint start_uv,
                  ON_3dPoint end_uv
                  ) const
{
  const ON_PolyCurve* polycurve = ON_PolyCurve::Cast(&curve_3d);
  if ( 0 != polycurve )
  {
    return PullbackPolyCurve( *polycurve, tolerance, curve_3d_subdomain, start_uv, end_uv );
  }

  const ON_CurveProxy* proxycurve = ON_CurveProxy::Cast(&curve_3d);
  if ( 0 != proxycurve )
  {
    return PullbackCurveProxy( *proxycurve, tolerance, 
                               curve_3d_subdomain, 
                               start_uv, end_uv );
  }

  // Do not call ON_Surface::Pullback().  The projection done below
  // is exact.

  ON_NurbsCurve* nurbs_curve = new ON_NurbsCurve();
  if ( curve_3d.GetNurbForm( *nurbs_curve, tolerance, curve_3d_subdomain ) < 1 )
  {
    delete nurbs_curve;
    nurbs_curve = 0;
  }
  else
  {
    ON_Xform xform;
    xform.ChangeBasis(ON_xy_plane,m_plane);
    if ( m_domain[0] != m_extents[0] || m_domain[1] != m_extents[1] )
    {
      // transform curve to plane's evaluation coordinates
      ON_Xform cs_change(1);
      ON_Interval s = Domain(0);
      ON_Interval t = Domain(1);
      ON_Interval x = Extents(0);
      ON_Interval y = Extents(1);
      if ( s != x )
      {
        double ds = s.Length();
        double dx = x.Length();
        cs_change.m_xform[0][0] = ds/dx;
        cs_change.m_xform[0][3] = (x[1]*s[0] - x[0]*s[1])/dx;
      }
      if ( t != y )
      {
        double dt = t.Length();
        double dy = y.Length();
        cs_change.m_xform[1][1] = dt/dy;
        cs_change.m_xform[1][3] = (y[1]*t[0] - y[0]*t[1])/dy;
      }
      xform = cs_change*xform;
    }
    nurbs_curve->ClampEnd(2);
    nurbs_curve->Transform(xform);

    ON_BOOL32 is_rat = nurbs_curve->IsRational();
    if ( start_uv != ON_UNSET_POINT )
    {
      start_uv.z = 0.0;
      double w = 1.0;
      if (is_rat){
        w = nurbs_curve->Weight(0);
        start_uv *= w;
      }
      nurbs_curve->SetCV(0,start_uv);
      if (is_rat)
        nurbs_curve->SetWeight(0,w);
    }
    if ( end_uv != ON_UNSET_POINT )
    {
      double w = 1.0;
      if (is_rat){
        w = nurbs_curve->Weight(nurbs_curve->m_cv_count-1);
        end_uv *= w;
      }
      end_uv.z = 0.0;
      nurbs_curve->SetCV(nurbs_curve->m_cv_count-1,end_uv);
      if (is_rat)
        nurbs_curve->SetWeight(nurbs_curve->m_cv_count-1,w);
    }
    nurbs_curve->ChangeDimension(2);
  }
  return nurbs_curve;
}

ON_BOOL32 ON_PlaneSurface::Trim(
       int dir,
       const ON_Interval& domain
       )
{
  if ( dir < 0 || dir > 1 )
    return false;
  ON_Interval current_domain = Domain(dir);
  if ( current_domain[0] == ON_UNSET_VALUE && current_domain[1] == ON_UNSET_VALUE )
    current_domain = domain;
  ON_Interval trim_domain, trim_extents = m_extents[dir];
  trim_domain.Intersection(domain, Domain(dir) );
  if ( !trim_domain.IsIncreasing() )
    return false;
  if ( m_domain[dir] == m_extents[dir] )
    trim_extents = trim_domain;
  else
  {
    double x0 = m_extents[dir].ParameterAt( m_domain[dir].NormalizedParameterAt( trim_domain[0] ) );
    double x1 = m_extents[dir].ParameterAt( m_domain[dir].NormalizedParameterAt( trim_domain[1] ) );
    trim_extents.Set(x0,x1);
  }
  if ( !trim_extents.IsIncreasing() )
    return false;
  m_extents[dir] = trim_extents;
  m_domain[dir] = trim_domain;
  return true;
}

bool ON_PlaneSurface::Extend(
      int dir,
      const ON_Interval& domain
      )
{
  if ( dir < 0 || dir > 1 ) return false;
  bool changed = false;
  ON_Interval tdom = Domain(dir);
  ON_Interval xdom = m_extents[dir];

  if (domain[0] < Domain(dir)[0]){
    changed = true;
    tdom[0] = domain[0];
    xdom[0] = m_extents[dir].ParameterAt( m_domain[dir].NormalizedParameterAt(domain[0]));
  }
  if (domain[1] > Domain(dir)[1]){
    changed = true;
    tdom[1] = domain[1];
    xdom[1] = m_extents[dir].ParameterAt( m_domain[dir].NormalizedParameterAt(domain[1]));
  }
  if (!changed) return false;
  DestroySurfaceTree();

  m_domain[dir] = tdom;
  m_extents[dir] = xdom;
  return true;
}

ON_BOOL32 ON_PlaneSurface::Split(
       int dir,
       double c,
       ON_Surface*& west_or_south_side,
       ON_Surface*& east_or_north_side
       ) const
{
  ON_PlaneSurface* ws_side = 0;
  ON_PlaneSurface* en_side = 0;

  if ( dir < 0 || dir > 1 )
    return false;
  if ( !Domain(dir).Includes(c,true) )
    return false;

  double t;
  if ( Domain(dir) == Extents(dir) )
    t = c;
  else
  {
    t = Extents(dir).ParameterAt( Domain(dir).NormalizedParameterAt(c) );
    if ( !Extents(dir).Includes(t,true) )
      return false;
  }

  if ( west_or_south_side )
  {
    if ( west_or_south_side == east_or_north_side )
      return false;
    ws_side = ON_PlaneSurface::Cast(west_or_south_side);
    if ( !ws_side )
      return false;
  }

  if ( east_or_north_side )
  {
    en_side = ON_PlaneSurface::Cast(east_or_north_side);
    if ( !en_side )
      return false;
  }

  if ( !ws_side )
    ws_side = new ON_PlaneSurface();
  if ( !en_side )
    en_side = new ON_PlaneSurface();

  *ws_side = *this;
  *en_side = *this;
  ws_side->m_domain[dir].m_t[1] = c;
  en_side->m_domain[dir].m_t[0] = c;
  ws_side->m_extents[dir].m_t[1] = t;
  en_side->m_extents[dir].m_t[0] = t;

  west_or_south_side = ws_side;
  east_or_north_side = en_side;

  return true;
}

bool ON_PlaneSurface::GetClosestPoint( const ON_3dPoint& test_point,
        double* s,double* t,  // parameters of local closest point returned here
        double maximum_distance,
        const ON_Interval* sdomain, // first parameter sub_domain
        const ON_Interval* tdomain  // second parameter sub_domain
        ) const
{
  double u = 0.0, v=0.0;

	ON_Interval sdom = Domain(0);
	ON_Interval tdom = Domain(1);
	if(sdomain==NULL)
		sdomain = &sdom;
	if(tdomain==NULL)
		tdomain = &tdom;

  bool rc = m_plane.ClosestPointTo( test_point, &u, &v );
  if ( rc ) 
  {
    // convert m_plane coordinates to ON_Surface coordinates
    if ( m_domain[0] != m_extents[0] )
    {
      u = m_domain[0].ParameterAt( m_extents[0].NormalizedParameterAt(u) );
    }
    if ( m_domain[1] != m_extents[1] )
    {
      v = m_domain[1].ParameterAt( m_extents[1].NormalizedParameterAt(v) );
    }

    if ( u < sdomain->Min() )
      u = sdomain->Min();
    else if ( u > sdomain->Max() )
      u = sdomain->Max();

    if ( v < tdomain->Min() )
      v = tdomain->Min();
    else if ( v > tdomain->Max() )
      v = tdomain->Max();

    if ( s )
      *s = u;
    if ( t )
      *t = v;
    if (maximum_distance > 0.0) 
    {
      ON_3dPoint pt = PointAt(u,v);
      if ( test_point.DistanceTo(pt) > maximum_distance )
        rc = false;
    }
  }
  return rc;
}

//////////
// Find parameters of the point on a surface that is locally closest to 
// the test_point.  The search for a local close point starts at 
// seed parameters. If a sub_domain parameter is not NULL, then
// the search is restricted to the specified portion of the surface.
//
// true if returned if the search is successful.  false is returned if
// the search fails.
ON_BOOL32 ON_PlaneSurface::GetLocalClosestPoint( const ON_3dPoint& test_point, // test_point
        double s0, double t0,     // seed_parameters
        double* s,double* t,   // parameters of local closest point returned here
        const ON_Interval* sdomain, // first parameter sub_domain
        const ON_Interval* tdomain  // second parameter sub_domain
        ) const
{
  // for planes, global serach is fast and returns same answer as local search
  return GetClosestPoint(test_point,s,t,0.0,sdomain,tdomain);
}


ON_Surface* ON_PlaneSurface::Offset(
      double offset_distance, 
      double tolerance, 
      double* max_deviation
      ) const
{
  if ( max_deviation )
    *max_deviation = 0.0;
  ON_PlaneSurface* offset_srf = new ON_PlaneSurface(*this);
  ON_3dVector delta = offset_srf->m_plane.zaxis;
  double d = delta.Length();
  if ( fabs(1.0-d) <= ON_SQRT_EPSILON )
    d = 1.0;
  d = offset_distance/d;
  offset_srf->m_plane.origin = offset_srf->m_plane.origin + (d*delta);
  offset_srf->m_plane.UpdateEquation();
  return offset_srf;
}


int 
ON_PlaneSurface::GetNurbForm( // returns 0: unable to create NURBS representation
                   //            with desired accuracy.
                   //         1: success - returned NURBS parameterization
                   //            matches the surface's to wthe desired accuracy
                   //         2: success - returned NURBS point locus matches
                   //            the surfaces's to the desired accuracy but, on
                   //            the interior of the surface's domain, the 
                   //            surface's parameterization and the NURBS
                   //            parameterization may not match to the 
                   //            desired accuracy.
        ON_NurbsSurface& nurbs,
        double tolerance
        ) const
{
  ON_BOOL32 rc = IsValid();

  if( !rc )
  {
    if (    m_plane.origin.x != ON_UNSET_VALUE 
         && m_plane.xaxis.x != ON_UNSET_VALUE 
         && m_plane.yaxis.x != ON_UNSET_VALUE
         && m_domain[0].IsIncreasing() && m_domain[1].IsIncreasing()
         && m_extents[0].Length() > 0.0 && m_extents[1].Length() > 0.0
         )
    {
      ON_3dVector N = ON_CrossProduct(m_plane.xaxis,m_plane.yaxis);
      if ( N.Length() <= 1.0e-4 )
      {
        ON_WARNING("ON_PlaneSurface::GetNurbForm - using invalid surface.");
        rc = true;
      }
    }
  }

  if ( rc ) 
  {
    nurbs.m_dim = 3;
    nurbs.m_is_rat = 0;
    nurbs.m_order[0] = nurbs.m_order[1] = 2;
    nurbs.m_cv_count[0] = nurbs.m_cv_count[1] = 2;
    nurbs.m_cv_stride[1] = nurbs.m_dim;
    nurbs.m_cv_stride[0] = nurbs.m_cv_stride[1]*nurbs.m_cv_count[1];
    nurbs.ReserveCVCapacity(12);
    nurbs.ReserveKnotCapacity(0,2);
    nurbs.ReserveKnotCapacity(1,2);
    nurbs.m_knot[0][0] = m_domain[0][0];
    nurbs.m_knot[0][1] = m_domain[0][1];
    nurbs.m_knot[1][0] = m_domain[1][0];
    nurbs.m_knot[1][1] = m_domain[1][1];
    nurbs.SetCV( 0, 0, PointAt( m_domain[0][0], m_domain[1][0] ));
    nurbs.SetCV( 0, 1, PointAt( m_domain[0][0], m_domain[1][1] ));
    nurbs.SetCV( 1, 0, PointAt( m_domain[0][1], m_domain[1][0] ));
    nurbs.SetCV( 1, 1, PointAt( m_domain[0][1], m_domain[1][1] ));
  }

  return rc;
}

int 
ON_PlaneSurface::HasNurbForm( // returns 0: unable to create NURBS representation
                   //            with desired accuracy.
                   //         1: success - returned NURBS parameterization
                   //            matches the surface's to wthe desired accuracy
                   //         2: success - returned NURBS point locus matches
                   //            the surfaces's to the desired accuracy but, on
                   //            the interior of the surface's domain, the 
                   //            surface's parameterization and the NURBS
                   //            parameterization may not match to the 
                   //            desired accuracy.
        ) const

{
  if (!IsValid())
    return 0;
  return 1;
}

bool ON_PlaneSurface::SetExtents( 
       int dir,
       ON_Interval extents,
       bool bSyncDomain
       )
{
  if ( dir < 0 || dir > 1 || !extents.IsIncreasing() )
    return false;
  m_extents[dir] = extents;
  if ( bSyncDomain )
    m_domain[dir] = m_extents[dir];
  return true;
}

ON_Interval ON_PlaneSurface::Extents(
       int dir
       ) const
{
  // rectangle extents - do not confuse with m_domain
  return dir ? m_extents[1] : m_extents[0];
}

ON_BOOL32 ON_PlaneSurface::SetDomain( 
  int dir, 
  double t0, 
  double t1
  )
{
  bool rc = false;
  if ( dir >= 0 && dir <= 1 && t0 < t1 )
  {
    rc = true;
    m_domain[dir].Set(t0,t1);
    DestroySurfaceTree();
  }
  return rc;
}

void ON_ClippingPlane::Default()
{
  m_plane = ON_xy_plane;
  m_viewport_ids.Empty();
  m_plane_id = ON_nil_uuid;
  m_bEnabled = true;
}

ON_ClippingPlane::ON_ClippingPlane()
{
  Default();
}

ON_ClippingPlane::~ON_ClippingPlane()
{
}

ON_ClippingPlaneInfo ON_ClippingPlane::ClippingPlaneInfo() const
{
  ON_ClippingPlaneInfo info;
  info.m_plane_equation = m_plane.plane_equation;
  info.m_plane_id = m_plane_id;
  info.m_bEnabled = m_bEnabled;
  return info;
}

bool ON_ClippingPlane::Read( ON_BinaryArchive& file )
{
  Default();

  int major_version = 0;
  int minor_version = 0;
  
  bool rc = file.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
  if (!rc)
    return false;

  for(;;)
  {
    rc = (1 == major_version);
    if (!rc) break;

    ON_UUID viewport_id;
    rc = file.ReadUuid(viewport_id);
    if(!rc) break;

    if( 0 == minor_version )
      m_viewport_ids.AddUuid( viewport_id );

    rc = file.ReadUuid(m_plane_id);
    if (!rc) break;

    rc = file.ReadPlane(m_plane);
    if (!rc) break;

    rc = file.ReadBool(&m_bEnabled);
    if (!rc) break;

    if( minor_version > 0 )
    {
      rc = m_viewport_ids.Read(file);
      if (!rc) break;
    }

    break;
  }

  if ( !file.EndRead3dmChunk() )
    rc = false;

  return rc;
}

bool ON_ClippingPlane::Write( ON_BinaryArchive& file ) const
{
  bool rc = file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,1);
  if (!rc)
    return false;

  for(;;)
  {
    //version 1.1 - write list of viewport uuids instead of single uuid
    ON_UUID viewport_id = ::ON_nil_uuid;
    if( m_viewport_ids.Count() > 0 )
      viewport_id = *(m_viewport_ids.Array());
    rc = file.WriteUuid(viewport_id);
    if (!rc) break;

    rc = file.WriteUuid(m_plane_id);
    if (!rc) break;

    rc = file.WritePlane(m_plane);
    if (!rc) break;

    rc = file.WriteBool(m_bEnabled);
    if (!rc) break;

    //version 1.1 - write list of viewport uuids instead of single uuid
    rc = m_viewport_ids.Write(file);
    if (!rc) break;

    break;
  }

  if ( !file.EndWrite3dmChunk() )
    rc = false;

  return rc;
}


void ON_ClippingPlaneSurface::Default()
{
  m_clipping_plane.Default();
  m_plane = m_clipping_plane.m_plane;
  m_domain[0].Set(0.0,1.0);
  m_domain[1].Set(0.0,1.0);
  m_extents[0].Set(-1.0,1.0);
  m_extents[1].Set(-1.0,1.0);
}


ON::object_type ON_ClippingPlaneSurface::ObjectType() const
{
  return ON::clipplane_object;
}

ON_ClippingPlaneSurface::ON_ClippingPlaneSurface()
{
  Default();
}

ON_ClippingPlaneSurface::~ON_ClippingPlaneSurface()
{
}

ON_ClippingPlaneSurface::ON_ClippingPlaneSurface(const ON_PlaneSurface& src)
                        : ON_PlaneSurface(src)
{
  m_clipping_plane.m_plane = m_plane;
}

ON_ClippingPlaneSurface::ON_ClippingPlaneSurface(const ON_Plane& src)
                        : ON_PlaneSurface(src)
{
  m_clipping_plane.m_plane = m_plane;
}

ON_ClippingPlaneSurface& ON_ClippingPlaneSurface::operator=(const ON_Plane& src)
{
  m_plane = src;
  m_clipping_plane.m_plane = m_plane;
  return *this;
}

ON_ClippingPlaneSurface& ON_ClippingPlaneSurface::operator=(const ON_PlaneSurface& src)
{
  if ( this != &src )
  {
    ON_PlaneSurface::operator=(src);
    m_clipping_plane.m_plane = m_plane;
  }
  return *this;
}

unsigned int ON_ClippingPlaneSurface::SizeOf() const
{
  return ON_PlaneSurface::SizeOf() + sizeof(m_clipping_plane);
}

ON__UINT32 ON_ClippingPlaneSurface::DataCRC(ON__UINT32 current_remainder) const
{
  ON__UINT32 crc = ON_PlaneSurface::DataCRC(current_remainder);
  crc = ON_CRC32(crc,sizeof(m_clipping_plane),&m_clipping_plane);
  return crc;
}

void ON_ClippingPlaneSurface::Dump( ON_TextLog& text_log ) const
{
  text_log.Print("Clipping plane surface\n");
  text_log.PushIndent();  
  text_log.Print("Enabled = %d",m_clipping_plane.m_bEnabled);
  text_log.Print("View IDs =\n");
  {
    text_log.PushIndent();
    ON_SimpleArray<ON_UUID> uuid_list;
    m_clipping_plane.m_viewport_ids.GetUuids(uuid_list);
    for( int i=0; i<uuid_list.Count(); i++ )
    {
      text_log.Print( uuid_list[i] );
      text_log.Print("\n");
    }
    text_log.PopIndent();
  }
  text_log.Print("Plane ID = ");
  text_log.Print(m_clipping_plane.m_plane_id);
  text_log.Print("\n");  

  text_log.Print("Plane surface\n");
  text_log.PushIndent();  
  ON_PlaneSurface::Dump(text_log);
  text_log.PopIndent();  
  text_log.PopIndent();  
}

ON_BOOL32 ON_ClippingPlaneSurface::Write( ON_BinaryArchive& file ) const
{
  bool rc = file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0);
  if (!rc)
    return false;

  for(;;)
  {
    rc = file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,0);
    if (rc)
    {
      rc = ON_PlaneSurface::Write(file)?true:false;
      if (!file.EndWrite3dmChunk())
        rc = false;
    }
    if (!rc) break;

    rc = m_clipping_plane.Write(file);
    if (rc) break;

    break;
  }

  if (!file.EndWrite3dmChunk() )
    rc = false;

  return rc;
}

ON_BOOL32 ON_ClippingPlaneSurface::Read( ON_BinaryArchive& file )
{
  Default();

  int major_version = 0;
  int minor_version = 0;

  bool rc = file.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
  if (!rc)
    return false;

  for(;;)
  {
    rc =  ( 1 == major_version );
    if (!rc) break;

    ON__UINT32 tcode = 0;
    ON__INT64 big_value = 0;

    rc = file.BeginRead3dmBigChunk(&tcode,&big_value)?true:false;
    if (rc)
    {
      rc = (TCODE_ANONYMOUS_CHUNK == tcode);
      if (rc)
        rc = (ON_PlaneSurface::Read(file)?true:false);
      if (!file.EndRead3dmChunk())
        rc = false;
    }
    if (!rc) break;

    rc = m_clipping_plane.Read(file);
    if (rc) break;

    break;
  }

  if (!file.EndRead3dmChunk() )
    rc = false;

  return rc;
}

