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

ON_Polyline::ON_Polyline()
{
}

ON_Polyline::ON_Polyline(const ON_3dPointArray& src) : ON_3dPointArray(src)
{
}


bool ON_Polyline::IsValid( double tolerance ) const
{
  bool rc = (m_count>=2)?true:false;
  int i;
  if ( tolerance > 0.0 )
  {
    for ( i = 1; rc && i < m_count; i++ )
    {
      if (false == m_a[i].IsValid() || false == m_a[i-1].IsValid())
        rc = false;
      else if ( m_a[i].DistanceTo(m_a[i-1]) <= tolerance )
        rc = false;
    }
    if ( rc && m_count < 4 && m_a[0].DistanceTo(m_a[m_count-1]) <= tolerance )
      rc = false;
  }
  else 
  {
    for ( i = 1; rc && i < m_count && rc; i++ )
    {
      if (false == m_a[i].IsValid() || false == m_a[i - 1].IsValid())
        rc = false;
      else if ( m_a[i] == m_a[i-1] )
        rc = false;
    }
    if ( rc && m_count < 4 && m_a[0] == m_a[m_count-1] )
      rc = false;
  }
  return rc;
}

int ON_Polyline::Clean( double tolerance )
{
  // 14 January 2005 Dale Lear
  //     Fixed this cleaner so that it did not modify
  //     the start and end point.
  int count0 = m_count;

  if ( m_count > 2 )
  {
    int i,j;
    j = 0;
    for ( i = 1; i < m_count-1; i++ )
    {
       if ( m_a[j].DistanceTo(m_a[i]) <= tolerance )
         continue;
       j++;
       if ( i > j )
         m_a[j] = m_a[i];
    }

    if ( m_count > j+2 )
    {
      m_a[j+1] = m_a[m_count-1];
      m_count = j+2;
    }

    while ( m_count > 2 && m_a[m_count-2].DistanceTo(m_a[m_count-1]) <= tolerance )
    {
      m_a[m_count-2] = m_a[m_count-1];
      m_count--;
    }
  }

  return count0-m_count;
}

ON_Polyline& ON_Polyline::operator=(const ON_3dPointArray& src)
{
  ON_3dPointArray::operator=(src);
  return *this;
}

ON_Polyline::~ON_Polyline()
{
}

int ON_Polyline::PointCount() const
{
  return m_count;
}

int ON_Polyline::SegmentCount() const
{
  int i = m_count-1;
  if (i < 0 )
    i = 0;
  return i;
}


bool ON_Polyline::IsClosed( double tolerance ) const
{
  bool rc = false;
  const int count = m_count-1;
  int i;
  if ( count >= 3 )
  {
    if ( tolerance > 0.0 )
    {
      if ( m_a[0].DistanceTo(m_a[count]) <= tolerance ) {
        for ( i = 1; i < count; i++ ) {
          if (   m_a[i].DistanceTo(m_a[0]) > tolerance 
              && m_a[i].DistanceTo(m_a[count]) > tolerance ) 
          {
             rc = true;
             break;
          }
        }
      }
    }
    else
    {
      if ( ON_PointsAreCoincident(3,false,&m_a[0].x,&m_a[count].x) ) 
      {
        for ( i = 1; i < count; i++ ) {
          if (    !ON_PointsAreCoincident(3,false,&m_a[i].x,&m_a[0].x) 
               && !ON_PointsAreCoincident(3,false,&m_a[i].x,&m_a[count].x) 
             )
          {
            rc = true;
            break;
          }
        }
      }
    }
  }
  return rc;
}


double ON_Polyline::Length() const 
{
  const int count = m_count;
  double d = 0;
  int i;
  for ( i = 1; i < count; i++ ) 
  {
    d += m_a[i].DistanceTo(m_a[i-1]);
  }
  return d;
}

ON_Line ON_Polyline::Segment(int segment_index) const
{
  ON_Line line;
  if (segment_index >= 0 && segment_index < m_count - 1)
  {
    line.from = m_a[segment_index];
    line.to = m_a[segment_index + 1];
  }
  else
  {
    line = ON_Line::ZeroLine;
  }
  return line;
}

ON_3dVector ON_Polyline::SegmentDirection( int segment_index ) const
{
  ON_3dVector v;
  if ( segment_index >= 0 && segment_index < m_count-1 ) 
  {
    v = m_a[segment_index+1] - m_a[segment_index];
  }
  else 
  {
    v = ON_3dVector::ZeroVector;
  }
  return v;
}

ON_3dVector ON_Polyline::SegmentTangent( int segment_index ) const
{
  ON_3dVector v = SegmentDirection(segment_index);
  v.Unitize();
  return v;
}

ON_3dPoint ON_Polyline::PointAt( double t ) const
{
  const int count = m_count;
  int segment_index = 0;
  if ( count < 0 ) {
    return ON_3dPoint::Origin;
  }
  else if (count == 1 ) {
    return m_a[0];
  }
  else {
    segment_index = (int)floor(t);
    if ( segment_index < 0 ) {
      segment_index = 0;
      //t = 0.0;
    }
    else if ( segment_index >= count-1 ) {
      segment_index = count-2;
      t = 1.0;//Note: This is not correct if the input t is greater than count-1.  It needs to be adjusted.
    }
    else {
      t -= ((double)segment_index);
    }
  }

  return (1-t)*m_a[segment_index] + t*m_a[segment_index+1];
}

ON_3dVector ON_Polyline::DerivativeAt( double t ) const
{
  const int count = m_count;
  int segment_index = 0;
  if ( count < 2 )
    return ON_3dPoint::Origin;
  else {
    segment_index = (int)floor(t);
    if ( segment_index < 0 )
      segment_index = 0;
    else if ( segment_index >= count-1 )
      segment_index = count-2;
  }
  return m_a[segment_index+1]-m_a[segment_index];
}

ON_3dVector ON_Polyline::TangentAt( double t ) const
{
  ON_3dVector v = DerivativeAt(t);
  v.Unitize();
  return v;
}

bool ON_Polyline::ClosestPointTo( const ON_3dPoint& point, double *t, int segment_index0, int segment_index1 ) const
{
  bool rc = false;
  int segment_index;
  double segment_t, segment_d, best_t, best_d;
  best_t = 0.0; // to keep lint quiet
  best_d = 0.0; // to keep lint quiet
  if ( t ) {
    if ( segment_index0 < 0 )
      segment_index0 = 0;
    if ( segment_index1 > SegmentCount() )
      segment_index1 = SegmentCount();
    for ( segment_index = segment_index0; segment_index < segment_index1; segment_index++ ) {
      double seg_length = m_a[segment_index].DistanceTo(m_a[segment_index + 1]);
      if (seg_length < ON_EPSILON)
        segment_t = 0.0;
      else {
        const ON_3dVector D = SegmentTangent(segment_index);
        const int i = ( point.DistanceTo(m_a[segment_index]) <= point.DistanceTo(m_a[segment_index+1]) ) ? 0 : 1;
        segment_t = (point - m_a[segment_index+i])*D/seg_length;
        if ( i ) {
          segment_t = 1.0 + segment_t;
        }
        if ( segment_t < 0.0 )
          segment_t = 0.0;
        else if (segment_t > 1.0 )
          segment_t = 1.0;
      }
      segment_d = point.DistanceTo((1-segment_t)*m_a[segment_index] + segment_t*m_a[segment_index+1]);
      if ( !rc || segment_d < best_d ) 
      {
        best_t = segment_t + ((double)segment_index);
        best_d = segment_d;
      }
      rc = true;
    }
  }
  if (rc)
    *t = best_t;
  return rc;
}

bool ON_Polyline::ClosestPointTo( const ON_3dPoint& point, double *t ) const
{
  return ClosestPointTo( point, t, 0, SegmentCount() );
}

ON_3dPoint ON_Polyline::ClosestPointTo( const ON_3dPoint& point ) const
{
  double t;
  bool rc = ClosestPointTo( point, &t );
  if ( !rc )
    t = 0.0;
  return PointAt(t);
}

bool ON_Polyline::CreateInscribedPolygon(
  const ON_Circle& circle,
  int side_count
  )
{
  bool rc = ( circle.IsValid() && side_count >= 3 ) ? true : false;
  if ( rc )
  {
    SetCapacity(side_count+1);
    SetCount(side_count+1);
    double a = 2.0*ON_PI/side_count;
    int i;
    for ( i = 0; i < side_count; i++ )
    {
      m_a[i] = circle.PointAt(a*i);
    }
    m_a[side_count] = m_a[0];
  }
  else
    Destroy();
  return rc;
}

bool ON_Polyline::CreateCircumscribedPolygon(
            const ON_Circle& circle,
            int side_count
            )
{
  bool rc = ( circle.IsValid() && side_count >= 3 ) ? true : false;
  if ( rc )
  {
    SetCapacity(side_count+1);
    SetCount(side_count+1);
    double half_a = ON_PI/side_count;
    int i;
    ON_Circle c = circle;
    c.radius = circle.radius/cos(half_a);
    for ( i = 0; i < side_count; i++ )
    {
      m_a[i] = c.PointAt(half_a*(1+2*i));
    }
    m_a[side_count] = m_a[0];
  }
  else
    Destroy();
  return rc;
}

bool ON_Polyline::CreateStarPolygon(
            const ON_Circle& circle,
            double other_radius,
            int side_count
            )
{
  bool rc = ( circle.IsValid() && side_count >= 3 && other_radius >= 0.0 ) 
          ? true 
          : false;
  if ( rc )
  {
    SetCapacity(2*side_count+1);
    SetCount(2*side_count+1);
    double half_a = ON_PI/side_count;
    int i;
    ON_Circle other_circle = circle;
    other_circle.radius = other_radius;
    for ( i = 0; i < side_count; i++ )
    {
      m_a[i*2]   = circle.PointAt(half_a*2*i);
      m_a[i*2+1] = other_circle.PointAt(half_a*(1+2*i));
    }
    m_a[side_count*2] = m_a[0];
  }
  else
    Destroy();
  return rc;
}

bool ON_IsConvexPolyline(
  size_t point_dim,
  size_t point_count,
  const double* points,
  size_t point_stride,
  bool bStrictlyConvex
)
{
  if (point_dim < 2 || point_dim > 3 || point_count < 3 || nullptr == points || point_stride < point_dim)
    return false;

  const double* p;
  ON_3dPoint P[2];

  p = points + (point_stride*(point_count - 1));
  P[0] = ON_3dPoint(p[0], p[1], (3 == point_dim) ? p[2] : 0.0);

  p = points;
  P[1] = ON_3dPoint(points[0], p[1], (3 == point_dim) ? p[2] : 0.0);

  if (P[0] == P[1])
  {
    --point_count;
    if (point_count < 3)
      return false;
    p = points + (point_stride*(point_count - 1));
    P[0] = ON_3dPoint(p[0], p[1], (3 == point_dim) ? p[2] : 0.0);
  }

  ON_3dVector D[2] = { ON_3dVector::NanVector, P[1]-P[0]};
  if (false == D[1].IsNotZero())
    return false;
  ON_SimpleArray<ON_3dVector> C(point_count);
  ON_3dVector maxN = ON_3dVector::ZeroVector;
  double maxNlen = 0.0;
  for (size_t i = 0; i < point_count; ++i)
  {
    p = points + (point_stride*((i+1)%point_count));
    P[0] = P[1];
    P[1] = ON_3dPoint(p[0], p[1], (3 == point_dim) ? p[2] : 0.0);
    D[0] = D[1];
    D[1] = P[1] - P[0];
    if (false == D[1].IsNotZero())
      return false;
    const ON_3dVector N = ON_CrossProduct(D[0], D[1]);
    const double Nlen = N.Length();
    if (Nlen > maxNlen)
    {
      maxNlen = Nlen;
      maxN = N;
    }
    else if (false == (Nlen > 0.0))
    {
      if ( bStrictlyConvex || false == (D[0]*D[1] > 0.0) )
        return false;
    }
    C.Append(N.UnitVector());
  }

  maxN = maxN.UnitVector();
  for (size_t i = 0; i < point_count; ++i)
  {
#if defined(ON_RUNTIME_ANDROID) || defined(ON_RUNTIME_LINUX) || defined(ON_RUNTIME_WASM)
    double d = maxN * C[(unsigned int)i];
#else
    double d = maxN * C[i];
#endif
    if ( false == ((bStrictlyConvex) ? (d > 0.0) : (d >= 0.0)) )
      return false;
  }

  return true;
}

bool ON_IsConvexPolyline(
  const ON_SimpleArray<ON_3dPoint>& points,
  bool bStrictlyConvex
)
{
  return ON_IsConvexPolyline(
    3,
    points.UnsignedCount(),
    (const double*)(points.Array()),
    3,
    bStrictlyConvex
  );
}


bool ON_Polyline::IsConvexLoop(bool bStrictlyConvex) const
{
  if (false == IsClosed())
    return false;
  const ON_SimpleArray<ON_3dPoint>& points = *this;
  return ON_IsConvexPolyline(points, bStrictlyConvex);
}

