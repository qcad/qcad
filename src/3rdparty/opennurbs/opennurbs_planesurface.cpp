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

bool ON_PlaneSurface::IsValid( ON_TextLog* text_log ) const
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

bool 
ON_PlaneSurface::Write(
       ON_BinaryArchive& file  // open binary file
     ) const
{
  bool rc = file.Write3dmChunkVersion(1,1);

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

bool 
ON_PlaneSurface::Read(
       ON_BinaryArchive& file // open binary file
     )
{
  int major_version = 0;
  int minor_version = 0;
  bool rc = file.Read3dmChunkVersion(&major_version,&minor_version);
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

bool ON_PlaneSurface::GetBBox( // returns true if successful
         double* boxmin,    // minimum
         double* boxmax,    // maximum
         bool bGrowBox
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

bool
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

bool ON_PlaneSurface::GetSurfaceSize( 
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


bool ON_PlaneSurface::GetSpanVector( int dir, double* s ) const
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

bool 
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

bool ON_PlaneSurface::IsPlanar( ON_Plane* plane, double tolerance ) const
{
  if ( plane )
    *plane = this->m_plane;
  return true;
}

bool 
ON_PlaneSurface::IsClosed( int dir ) const
{
  return false;
}

bool 
ON_PlaneSurface::IsPeriodic( int dir ) const
{
  return false;
}

bool 
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

bool
ON_PlaneSurface::Reverse( int dir )
{
  if ( dir < 0 || dir > 1 )
    return false;
  m_extents[dir].Reverse();
  m_domain[dir].Reverse();
  if (dir)
    m_plane.yaxis = -m_plane.yaxis;
  else
    m_plane.xaxis = -m_plane.xaxis;
  m_plane.zaxis = -m_plane.zaxis;
  m_plane.UpdateEquation();
  return true;
}

bool ON_PlaneSurface::IsContinuous(
    ON::continuity desired_continuity,
    double s, 
    double t, 
    int* hint, // default = nullptr,
    double point_tolerance, // default=ON_ZERO_TOLERANCE
    double d1_tolerance, // default==ON_ZERO_TOLERANCE
    double d2_tolerance, // default==ON_ZERO_TOLERANCE
    double cos_angle_tolerance, // default==ON_DEFAULT_ANGLE_TOLERANCE_COSINE
    double curvature_tolerance  // default==ON_SQRT_EPSILON
    ) const
{
  return true;
}

bool
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

bool 
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
  if ( (dir == 0 || dir == 1) && IsValid() ) 
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


bool ON_PlaneSurface::Trim(
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

bool ON_PlaneSurface::Split(
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


int ON_PlaneSurface::GetNurbForm( // returns 0: unable to create NURBS representation
                   //            with desired accuracy.
                   //         1: success - returned NURBS parameterization
                   //            matches the surface's to the desired accuracy
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
  bool rc = IsValid();

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
                   //            matches the surface's to the desired accuracy
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

bool ON_PlaneSurface::CreatePseudoInfinitePlane( 
        ON_PlaneEquation plane_equation,
        const ON_BoundingBox& bbox,
        double padding
        )
{

  ON_Plane plane(&plane_equation.x);
  return CreatePseudoInfinitePlane(plane,bbox,padding);
}

bool ON_PlaneSurface::CreatePseudoInfinitePlane( 
        const ON_Plane& plane,
        const ON_BoundingBox& bbox,
        double padding
        )
{
  ON_3dPoint bbox_corners[8];
  if ( !bbox.GetCorners(bbox_corners) )
    return false;
  return CreatePseudoInfinitePlane(plane,8,bbox_corners,padding);
}


bool ON_PlaneSurface::CreatePlaneThroughBox(
  const ON_Plane& plane,
  const ON_BoundingBox& bbox,
  double padding
)
{
  if (!plane.IsValid() || !bbox.IsValid())
    return false;

  ON_Interval uext(ON_DBL_PINF, ON_DBL_NINF);
  ON_Interval vext(ON_DBL_PINF, ON_DBL_NINF);
  double t, u, v;
  for (int i = 0; i < 12; i++)
  {
    ON_Line edge = bbox.Edge(i);
    if (!ON_Intersect(edge, plane.plane_equation, &t)) continue;
    if (t < 0.0 || t > 1.0) continue;
    ON_3dPoint pt = edge.PointAt(t);
    plane.ClosestPointTo(pt, &u, &v);
    if (u < uext[0]) uext[0] = u;
    if (u > uext[1]) uext[1] = u;
    if (v < vext[0]) vext[0] = v;
    if (v > vext[1]) vext[1] = v;
  }
  *this = plane;
  uext.Expand(padding * uext.Length() + padding);
  vext.Expand(padding * vext.Length() + padding);
  SetExtents(0, uext, true);
  SetExtents(1, vext, true);
  return true;
}


bool ON_PlaneSurface::CreatePlaneThroughBox(
  const ON_PlaneEquation& plane_equation,
  const ON_BoundingBox& bbox,
  double padding
)
{
  ON_Plane plane(plane_equation);
  ON_3dPoint center = plane.ClosestPointTo(bbox.Center());
  plane.origin = center;
  return CreatePlaneThroughBox(plane, bbox, padding);
}


bool ON_PlaneSurface::CreatePseudoInfinitePlane( 
        const ON_Plane& plane,
        int point_count,
        const ON_3dPoint* point_list,
        double padding
        )
{
  if ( !plane.IsValid() )
    return false;
  if ( point_count < 1 )
    return false;
  if ( 0 == point_list )
    return false;
  if ( !ON_IsValid(padding) || padding < 0.0 )
    return false;

  ON_Interval plane_domain[2];
  double s, t;
  s = ON_UNSET_VALUE;
  t = ON_UNSET_VALUE;
  if ( !plane.ClosestPointTo( point_list[0], &s, &t ) || !ON_IsValid(s) || !ON_IsValid(t) )
    return 0;
  plane_domain[0].m_t[1] = plane_domain[0].m_t[0] = s;
  plane_domain[1].m_t[1] = plane_domain[1].m_t[0] = t;
  
  for ( int i = 1; i < point_count; i++ )
  {
    s = ON_UNSET_VALUE;
    t = ON_UNSET_VALUE;
    if ( !plane.ClosestPointTo( point_list[i], &s, &t ) || !ON_IsValid(s) || !ON_IsValid(t) )
      return 0;
    if ( s < plane_domain[0].m_t[0] ) plane_domain[0].m_t[0] = s; else if ( s > plane_domain[0].m_t[1] ) plane_domain[0].m_t[1] = s;
    if ( t < plane_domain[1].m_t[0] ) plane_domain[1].m_t[0] = t; else if ( t > plane_domain[1].m_t[1] ) plane_domain[1].m_t[1] = t;
  }

  s = padding*plane_domain[0].Length() + padding;
  if ( !(s > 0.0) && !plane_domain[0].IsIncreasing() )
    s = 1.0;
  plane_domain[0].m_t[0] -= s;
  plane_domain[0].m_t[1] += s;

  t = padding*plane_domain[1].Length() + padding;
  if ( !(t > 0.0) && !plane_domain[1].IsIncreasing() )
    t = 1.0;
  plane_domain[1].m_t[0] -= t;
  plane_domain[1].m_t[1] += t;

  m_plane = plane;
  m_domain[0] = plane_domain[0];
  m_domain[1] = plane_domain[1];
  m_extents[0] = plane_domain[0];
  m_extents[1] = plane_domain[1];

  return IsValid()?true:false;
}

bool ON_PlaneSurface::SetDomain( 
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

ON_Mesh* ON_PlaneSurface::CreateMesh(
  ON_Mesh* mesh
) const
{
  ON_Mesh* rc = nullptr;

  if (m_plane.IsValid() && m_domain[0].IsValid() && m_domain[1].IsValid())
  {
    bool vn = false, fn = false, sp = true;

    if (mesh == nullptr) mesh = new ON_Mesh();
    else
    {
      if (!mesh->HasDoublePrecisionVertices()) mesh->UpdateDoublePrecisionVertices();
      if (mesh->HasVertexNormals()) vn = true;
      if (mesh->HasFaceNormals()) fn = true;
      if (mesh->HasMeshTopology()) mesh->DestroyTopology();
    }

    mesh->m_dV.Append(PointAt(m_domain[0][0], m_domain[1][0]));
    mesh->m_dV.Append(PointAt(m_domain[0][1], m_domain[1][0]));
    mesh->m_dV.Append(PointAt(m_domain[0][1], m_domain[1][1]));
    mesh->m_dV.Append(PointAt(m_domain[0][0], m_domain[1][1]));
    mesh->UpdateSinglePrecisionVertices();

    {
      ON_MeshFace mf;
      mf.vi[0] = mesh->VertexCount() - 4;
      mf.vi[1] = mesh->VertexCount() - 3;
      mf.vi[2] = mesh->VertexCount() - 2;
      mf.vi[3] = mesh->VertexCount() - 1;
      mesh->m_F.Append(mf);
    }

    if (vn)
    {
      mesh->m_N.Append((ON_3fVector)m_plane.Normal());
      mesh->m_N.Append((ON_3fVector)m_plane.Normal());
      mesh->m_N.Append((ON_3fVector)m_plane.Normal());
      mesh->m_N.Append((ON_3fVector)m_plane.Normal());
    }

    if (fn)
    {
      mesh->m_FN.Append((ON_3fVector)m_plane.Normal());
    }

    if (sp)
    {
      mesh->m_S.Append(ON_2dPoint(m_domain[0][0], m_domain[1][0]));
      mesh->m_S.Append(ON_2dPoint(m_domain[0][1], m_domain[1][0]));
      mesh->m_S.Append(ON_2dPoint(m_domain[0][1], m_domain[1][1]));
      mesh->m_S.Append(ON_2dPoint(m_domain[0][0], m_domain[1][1]));
    }

    rc = mesh;
  }
  return rc;
}

double ON_ClippingPlaneInfo::Depth() const
{
  return m_depth;
}
void ON_ClippingPlaneInfo::SetDepth(double depth)
{
  if (depth < 0.0)
    return;
  m_depth = (float)depth;
}

bool ON_ClippingPlaneInfo::DepthEnabled() const
{
  return m_depth_enabled;
}

void ON_ClippingPlaneInfo::SetDepthEnabled(bool on)
{
  m_depth_enabled = on;
}

void ON_ClippingPlaneInfo::Default()
{
  memset(this,0,sizeof(*this));
}

bool ON_ClippingPlaneInfo::Write( ON_BinaryArchive& file ) const
{
  // version 1.1 and 1.2 - write distance as a double
  // In version 1.1 we wrote -1 as the default value for m_distance.
  // This default has changed to ON_UNSET_POSITIVE_FLOAT. Bumping the minor
  // version so we can properly handle the default case when reading.
  //
  // 28 Mar 2023 S. Baer (RH-73816)
  // We went back to using a negative value to define "unset". We don't need
  // to adjust the minor version number for this
  // 6 April 2023 S. Baer (RH-74002)
  // version 1.3
  // Added a bool toggle to state if depth is being used. This frees up the depth
  // numeric value to be any number and not have reserved "unset" numbers
  bool rc = file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,3);
  if (!rc)
    return false;
  
  for(;;)
  {
    rc = file.WritePlaneEquation(m_plane_equation);
    if (!rc) break;

    rc = file.WriteUuid(m_plane_id);
    if (!rc) break;

    rc = file.WriteBool(m_bEnabled);
    if (!rc) break;

    rc = file.WriteDouble(m_depth);
    if (!rc) break;

    // version 1.3, add depth enabled bool
    rc = file.WriteBool(m_depth_enabled);
    if (!rc) break;

    break;
  }

  if ( !file.EndWrite3dmChunk() )
    rc = false;

  return rc;
}

bool ON_ClippingPlaneInfo::Read( ON_BinaryArchive& file )
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

    rc = file.ReadPlaneEquation(m_plane_equation);
    if (!rc) break;

    rc = file.ReadUuid(m_plane_id);
    if (!rc) break;

    rc = file.ReadBool(&m_bEnabled);
    if (!rc) break;

    if (minor_version > 0)
    {
      double d = 0;
      rc = file.ReadDouble(&d);
      if (!rc) break;

      if (1 == minor_version || 2 == minor_version)
      {
        if (d >= 0.0 && d != ON_UNSET_POSITIVE_FLOAT)
        {
          m_depth_enabled = true;
        }
        else
        {
          m_depth_enabled = false;
          d = 0.0;
        }
      }
      SetDepth(d);
    }

    if (minor_version >= 3)
    {
      rc = file.ReadBool(&m_depth_enabled);
      if (!rc) break;
    }

    break;
  }

  if ( !file.EndRead3dmChunk() )
    rc = false;

  return rc;
}

class ON_ClippingPlaneData
{
public:
  ON_ClippingPlaneData():m_object_id_list(0){}
  bool HasDefaultContent() const;

  unsigned int m_sn=0;
  double m_depth = 0;

  ON_UuidList m_object_id_list;
  ON_SimpleArray<int> m_layer_list;
  bool m_layer_list_is_sorted = true;
  bool m_is_exclusion_list = true;
};

bool ON_ClippingPlaneData::HasDefaultContent() const
{
  if (m_depth != 0.0)
    return false;
  
  if (m_object_id_list.Count()>0)
    return false;

  if (m_layer_list.Count() > 0)
    return false;
  
  if (!m_is_exclusion_list)
    return false;

  return true;
}

class ON_ClippingPlaneDataList
{
public:
  ON_ClippingPlaneDataList() = default;
  ~ON_ClippingPlaneDataList();
  
  ON_ClippingPlaneData* AppendNew();
  void DeleteEntry(unsigned int sn);
  ON_ClippingPlaneData* FromSerialNumber(unsigned int sn);
private:
  ON_SimpleArray<ON_ClippingPlaneData*> m_list;
};

static ON_ClippingPlaneDataList g_data_list;
static ON_SleepLock g_data_list_lock;

ON_ClippingPlaneDataList::~ON_ClippingPlaneDataList()
{
  for(int i=0; i<m_list.Count(); i++)
  {
    ON_ClippingPlaneData* data = m_list[i];
    if (data)
      delete data;
    m_list[i] = nullptr;
  }
}

void ON_ClippingPlaneDataList::DeleteEntry(unsigned int sn)
{
  int count = m_list.Count();
  for (int i=0; i<count; i++)
  {
    ON_ClippingPlaneData* data = m_list[i];
    if (data && data->m_sn == sn)
    {
      delete data;
      m_list.Remove(i);
      return;
    }
  }
}

ON_ClippingPlaneData* ON_ClippingPlaneDataList::AppendNew()
{
  static unsigned int serial_number = 1;
  ON_ClippingPlaneData* data = new ON_ClippingPlaneData();
  m_list.Append(data);
  data->m_sn = serial_number++;
  return data;
}

ON_ClippingPlaneData* ON_ClippingPlaneDataList::FromSerialNumber(unsigned int sn)
{
  if (0==sn)
    return nullptr;
  
  // TODO: use binary search
  int count = m_list.Count();
  for (int i=0; i<count; i++)
  {
    ON_ClippingPlaneData* data = m_list[i];
    if (data && data->m_sn == sn)
      return data;
  }
  return nullptr;
}

/*
static int CompareClippingPlaneData(const ON_ClippingPlaneData* a, const ON_ClippingPlaneData* b)
{
  if (a && b)
  {
    if (a->m_sn<b->m_sn)
      return -1;
    if (a->m_sn>b->m_sn)
      return 1;
    return 0;
  }
  if (a)
    return -1;
  if (b)
    return 1;
  return 0;
}
 */

static void DeleteClippingPlaneData(ON_ClippingPlaneDataStore& dataStore)
{
  const unsigned int serial_number = dataStore.m_sn;
  if (serial_number>0)
  {
    bool bReturnLock = g_data_list_lock.GetLock();
    dataStore.m_sn = 0;
    g_data_list.DeleteEntry(serial_number);
    if(bReturnLock)
      g_data_list_lock.ReturnLock();
  }
}

static ON_ClippingPlaneData* GetClippingPlaneData(unsigned int sn)
{
  if (0==sn)
    return nullptr;
  
  bool bReturnLock = g_data_list_lock.GetLock();
  ON_ClippingPlaneData* rc = g_data_list.FromSerialNumber(sn);
  if(bReturnLock)
    g_data_list_lock.ReturnLock();
  return rc;
}

static ON_ClippingPlaneData* GetClippingPlaneData(ON_ClippingPlaneDataStore& dataStore, bool createIfMissing)
{
  bool bReturnLock = g_data_list_lock.GetLock();

  ON_ClippingPlaneData* rc = g_data_list.FromSerialNumber(dataStore.m_sn);
  if (nullptr==rc && createIfMissing)
  {
    rc = g_data_list.AppendNew();
    if (rc)
      dataStore.m_sn = rc->m_sn;
  }
  if(bReturnLock)
    g_data_list_lock.ReturnLock();
  return rc;
}

ON_ClippingPlaneDataStore::ON_ClippingPlaneDataStore()
{
}

ON_ClippingPlaneDataStore::ON_ClippingPlaneDataStore(const ON_ClippingPlaneDataStore& src)
{
  ON_ClippingPlaneData* srcData = GetClippingPlaneData(src.m_sn);
  if (srcData)
  {
    ON_ClippingPlaneData* thisData = GetClippingPlaneData(*this, true);
    if (thisData)
    {
      thisData->m_depth = srcData->m_depth;
      thisData->m_object_id_list = srcData->m_object_id_list;
      thisData->m_is_exclusion_list = srcData->m_is_exclusion_list;
      thisData->m_layer_list = srcData->m_layer_list;
      thisData->m_layer_list_is_sorted = srcData->m_layer_list_is_sorted;
    }
  }
  
}

ON_ClippingPlaneDataStore::~ON_ClippingPlaneDataStore()
{
  DeleteClippingPlaneData(*this);
}

ON_ClippingPlaneDataStore& ON_ClippingPlaneDataStore::operator=(const ON_ClippingPlaneDataStore& src)
{
  if (0==src.m_sn)
  {
    DeleteClippingPlaneData(*this);
  }
  else
  {
    ON_ClippingPlaneData* srcData = GetClippingPlaneData(src.m_sn);
    if (nullptr==srcData)
    {
      DeleteClippingPlaneData(*this);
    }
    else
    {
      ON_ClippingPlaneData* thisData = GetClippingPlaneData(*this, true);
      if (thisData)
      {
        thisData->m_depth = srcData->m_depth;
        thisData->m_object_id_list = srcData->m_object_id_list;
        thisData->m_is_exclusion_list = srcData->m_is_exclusion_list;
        thisData->m_layer_list = srcData->m_layer_list;
        thisData->m_layer_list_is_sorted = srcData->m_layer_list_is_sorted;
      }
    }
  }
  return *this;
}


void ON_ClippingPlane::Default()
{
  m_plane = ON_xy_plane;
  m_viewport_ids.Empty();
  m_plane_id = ON_nil_uuid;
  m_bEnabled = true;
  m_depth_enabled = false;
  m_participation_lists_enabled = false;
  DeleteClippingPlaneData(m_data_store);
}

ON_ClippingPlane::ON_ClippingPlane()
{
  Default();
}

ON_ClippingPlane::~ON_ClippingPlane()
{
  DeleteClippingPlaneData(m_data_store);
}

ON_ClippingPlaneInfo ON_ClippingPlane::ClippingPlaneInfo() const
{
  ON_ClippingPlaneInfo info;
  info.m_plane_equation = m_plane.plane_equation;
  info.m_plane_id = m_plane_id;
  info.m_bEnabled = m_bEnabled;
  info.SetDepth(Depth());
  info.SetDepthEnabled(m_depth_enabled);
  return info;
}

double ON_ClippingPlane::Depth() const
{
  ON_ClippingPlaneData* data = GetClippingPlaneData(m_data_store.m_sn);
  if (data)
    return data->m_depth;
  return 0;
}
void ON_ClippingPlane::SetDepth(double depth)
{
  if (depth < 0.0)
    return;
  
  if (0.0 == depth)
  {
    ON_ClippingPlaneData* data = GetClippingPlaneData(m_data_store.m_sn);
    if (data)
    {
      data->m_depth = depth;
      if (data->HasDefaultContent())
      {
        DeleteClippingPlaneData(m_data_store);
      }
    }
    return;
  }
  
  ON_ClippingPlaneData* data = GetClippingPlaneData(m_data_store, true);
  if (data)
    data->m_depth = depth;
}

bool ON_ClippingPlane::ParticipationListsEnabled() const
{
  return m_participation_lists_enabled;
}
void ON_ClippingPlane::SetParticipationListsEnabled(bool on)
{
  m_participation_lists_enabled = on;
}

void ON_ClippingPlane::SetParticipationLists(const ON_SimpleArray<ON_UUID>* objectIds, const ON_SimpleArray<int>* layerIndices, bool isExclusionList)
{
  if ((nullptr == objectIds || objectIds->Count() < 1) &&
    (nullptr==layerIndices || layerIndices->Count()<1) &&
    isExclusionList)
  {
    // clear any existing list
    ON_ClippingPlaneData* data = GetClippingPlaneData(m_data_store.m_sn);
    if (data)
    {
      data->m_object_id_list.Empty();
      data->m_layer_list.Empty();
      data->m_layer_list_is_sorted = true;
      data->m_is_exclusion_list = isExclusionList;
      if (data->HasDefaultContent())
      {
        DeleteClippingPlaneData(m_data_store);
      }
    }
    return;
  }

  ON_ClippingPlaneData* data = GetClippingPlaneData(m_data_store, true);
  if (data)
  {
    data->m_object_id_list.Empty();
    data->m_layer_list.Empty();
    data->m_layer_list_is_sorted = true;
    if (objectIds)
    {
      for (int i = 0; i < objectIds->Count(); i++)
      {
        data->m_object_id_list.AddUuid((*objectIds)[i]);
      }
    }
    if (layerIndices && layerIndices->Count() > 0)
    {
      data->m_layer_list_is_sorted = false;
      data->m_layer_list = (*layerIndices);
    }
    data->m_is_exclusion_list = isExclusionList;
  }
}


const ON_UuidList* ON_ClippingPlane::ObjectClipParticipationList() const
{
  ON_ClippingPlaneData* data = GetClippingPlaneData(m_data_store.m_sn);
  if (data)
    return &(data->m_object_id_list);
  return nullptr;
}

const ON_SimpleArray<int>* ON_ClippingPlane::LayerClipParticipationList() const
{
  ON_ClippingPlaneData* data = GetClippingPlaneData(m_data_store.m_sn);
  if (data)
  {
    if (!data->m_layer_list_is_sorted)
    {
      data->m_layer_list.QuickSort(ON_CompareIncreasing<int>);
      data->m_layer_list_is_sorted = true;
    }
    return &(data->m_layer_list);
  }
  return nullptr;
}

bool ON_ClippingPlane::ClipParticipationListsAreExclusionLists() const
{
  ON_ClippingPlaneData* data = GetClippingPlaneData(m_data_store.m_sn);
  if (data)
    return data->m_is_exclusion_list;
  return true;
}


bool ON_ClippingPlane::DepthEnabled() const
{
  return m_depth_enabled;
}
void ON_ClippingPlane::SetDepthEnabled(bool on)
{
  m_depth_enabled = on;
}

enum ON_ClippingPlaneTypeCodes : unsigned char
{
  ClipParticipationObjectList = 10,
  ClipParticipationLayerList = 11,
  ClipParticipationIsExclusion = 12,
  ClipParticipationEnabled = 13,

  // add items here
  NextTypeCode
};

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

    if (minor_version > 1)
    {
      double d = -1;
      rc = file.ReadDouble(&d);
      if (!rc) break;

      if (minor_version < 4)
      {
        if (d >= 0.0 && d != ON_UNSET_POSITIVE_FLOAT)
        {
          m_depth_enabled = true;
        }
        else
        {
          m_depth_enabled = false;
          d = 0.0;
        }
      }

      SetDepth(d);
    }

    if (minor_version >= 4)
    {
      rc = file.ReadBool(&m_depth_enabled);
      if (!rc) break;
    }

    if (minor_version >= 5)
    {
      unsigned char itemid = 0xFF;
      rc = file.ReadChar(&itemid);
      if (!rc) break;
      if (0 == itemid)
        break;

      if (ON_ClippingPlaneTypeCodes::ClipParticipationObjectList == itemid) // 10
      {
        int count = 0;
        rc = file.ReadInt(&count);
        if (!rc) break;

        ON_ClippingPlaneData* data = GetClippingPlaneData(m_data_store, true);
        ON_UUID object_id = ON_nil_uuid;
        for (int i = 0; i < count; i++)
        {
          rc = file.Read3dmReferencedComponentId(ON_ModelComponent::Type::ModelGeometry, &object_id);
          if (!rc) break;
          if (data)
            data->m_object_id_list.AddUuid(object_id);
        }
        if (!rc) break;

        rc = file.ReadChar(&itemid);
        if (!rc || 0 == itemid) break;
      }
      if (ON_ClippingPlaneTypeCodes::ClipParticipationLayerList == itemid) // 11
      {
        int count = 0;
        rc = file.ReadInt(&count);
        if (!rc) break;

        ON_ClippingPlaneData* data = GetClippingPlaneData(m_data_store, true);
        for (int i = 0; i < count; i++)
        {
          int layer_index = 0;
          rc = file.Read3dmReferencedComponentIndex(ON_ModelComponent::Type::Layer, &layer_index);
          if (!rc) break;

          if (data)
          {
            data->m_layer_list.Append(layer_index);
            data->m_layer_list_is_sorted = false;
          }
        }
        if (!rc) break;

        rc = file.ReadChar(&itemid);
        if (!rc || 0 == itemid) break;
      }
      if (ON_ClippingPlaneTypeCodes::ClipParticipationIsExclusion == itemid) // 12
      {
        bool exclusion = true;
        rc = file.ReadBool(&exclusion);
        if (!rc) break;
        ON_ClippingPlaneData* data = GetClippingPlaneData(m_data_store, true);
        if (data)
          data->m_is_exclusion_list = exclusion;
        rc = file.ReadChar(&itemid);
        if (!rc || 0 == itemid) break;
      }
      if (ON_ClippingPlaneTypeCodes::ClipParticipationEnabled == itemid) // 13
      {
        rc = file.ReadBool(&m_participation_lists_enabled);
        if (!rc) break;
        rc = file.ReadChar(&itemid);
        if (!rc || 0 == itemid) break;
      }

      if (itemid >= ON_ClippingPlaneTypeCodes::NextTypeCode)
      {
        // we are reading file written with code newer
        // than this code (minor_version > 5)
        itemid = 0;
      }

      break;
    }

    break;
  }

  if ( !file.EndRead3dmChunk() )
    rc = false;

  return rc;
}

bool ON_ClippingPlane::Write( ON_BinaryArchive& file ) const
{
  // 20 May 2023 S. Baer (RH-74763)
  // version 1.5 - write clip participation
  bool rc = file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,5);
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

    //version 1.2 - write distance as double
    //version 1.3 - continue to write distance, but the reader now knows to
    //              interpret the distance value in a different way
    double depth = Depth();
    rc = file.WriteDouble(depth);
    if (!rc) break;

    //version 1.4 - write enabled flag for depth
    rc = file.WriteBool(m_depth_enabled);
    if (!rc) break;

    //version 1.5
    ON_ClippingPlaneData* data = GetClippingPlaneData(m_data_store.m_sn);

    if (data && data->m_object_id_list.Count() > 0)
    {
      const ON_UUID* ids = data->m_object_id_list.Array();
      if (ids)
      {
        unsigned char c = ON_ClippingPlaneTypeCodes::ClipParticipationObjectList; // 10
        rc = file.WriteChar(c);
        if (!rc) break;

        int count = data->m_object_id_list.Count();
        rc = file.WriteInt(count);
        if (!rc) break;

        for (int i = 0; i < count; i++)
        {
          rc = file.Write3dmReferencedComponentId(ON_ModelComponent::Type::ModelGeometry, ids[i]);
          if (!rc) break;
        }
        if (!rc) break;
      }
    }
    if (data && data->m_layer_list.Count() > 0)
    {
      unsigned char c = ON_ClippingPlaneTypeCodes::ClipParticipationLayerList; // 11
      rc = file.WriteChar(c);
      if (!rc) break;

      int count = data->m_layer_list.Count();
      rc = file.WriteInt(count);
      if (!rc) break;
      for (int i = 0; i < count; i++)
      {
        int layer_index = data->m_layer_list[i];
        rc = file.Write3dmReferencedComponentIndex(ON_ModelComponent::Type::Layer, layer_index);
        if (!rc) break;
      }
      if (!rc) break;
    }
    if (data && data->m_is_exclusion_list == false)
    {
      unsigned char c = ON_ClippingPlaneTypeCodes::ClipParticipationIsExclusion; // 12
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.WriteBool(data->m_is_exclusion_list);
      if (!rc) break;
    }
    if (m_participation_lists_enabled)
    {
      unsigned char c = ON_ClippingPlaneTypeCodes::ClipParticipationEnabled; // 13
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.WriteBool(m_participation_lists_enabled);
      if (!rc) break;
    }

    unsigned char lastTypeCode = 0;
    rc = file.WriteChar(lastTypeCode);
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

bool ON_ClippingPlaneSurface::Write( ON_BinaryArchive& file ) const
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

bool ON_ClippingPlaneSurface::Read( ON_BinaryArchive& file )
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

