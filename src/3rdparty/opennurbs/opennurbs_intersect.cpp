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

bool ON_IntersectLineLine(
          const ON_Line& lineA, 
          const ON_Line& lineB, 
          double* a,
          double* b,
          double tolerance,
          bool bIntersectSegments
          )
{
  bool rc = ON_Intersect(lineA,lineB,a,b) ? true : false;
  if (rc)
  {
    if ( bIntersectSegments )
    {
      if ( *a < 0.0 )
        *a = 0.0;
      else if ( *a > 1.0 )
        *a = 1.0;
      if ( *b < 0.0 )
        *b = 0.0;
      else if ( *b > 1.0 )
        *b = 1.0;
    }
    if ( tolerance > 0.0 )
    {
      rc = (lineA.PointAt(*a).DistanceTo(lineB.PointAt(*b)) <= tolerance);
    }
  }
  return rc;
}


bool ON_Intersect( const ON_BoundingBox& bbox, 
                   const ON_Line& line, 
                   double tol,
                   ON_Interval* line_parameters)
{
  double a,b,d,mn,mx,s0,s1, t0, t1;
  const double M = 1.0e308;

  // i,j,k are indices of coordinates to trim.
  // trim the direction with the biggest line deltas first
  ON_3dVector v = line.Direction();
  const int i = v.MaximumCoordinateIndex();

  // guard against ON_UNSET_VALUE as input
  if ( !(tol >= 0.0) )
    tol = 0.0;

  // clip i-th coordinate
  a = line.from[i];
  b = line.to[i];
  mn = bbox.m_min[i];
  mx = bbox.m_max[i];
  if ( !(mn <= mx) )
    return false;
  mn -= (tol+a);
  mx += (tol-a);
  if ( !(mn <= mx) )
    return false;
  d = b-a;
  if ( 0.0 == d )
  {
    // happens when line.from == line.to
    if ( 0.0 < mn || 0.0 > mx )
    {
      // point is in box
      if ( line_parameters )
      {
        // setting parameters makes no sense - just use 0.0
        // so it's clear we have a point
        line_parameters->Set(0.0,0.0);
      }
      return true;
    }
    return false; // point is outside box
  }
  if ( fabs(d) < 1.0 && (fabs(mn) >= fabs(d)*M || fabs(mx) >= fabs(d)*M) )
  {
    // the value of mn/d or mx/d is too large for a realistic answer to be computed
    return false;
  }
  d = 1.0/d;
  t0 = mn*d;
  t1 = mx*d;

  // set "chord" = line segment that begins and ends on the
  // i-th coordinate box side planes.
  ON_Line chord(line.PointAt(t0),line.PointAt(t1));

  // test j-th coordinate direction
  const int j = (i + (fabs(v[(i+1)%3])>fabs(v[(i+2)%3])?1:2) ) % 3;
  a = chord.from[j];
  b = chord.to[j];
  mn = bbox.m_min[j];
  mx = bbox.m_max[j];
  if ( !(mn <= mx) )
    return false;
  mn -= (tol+a);
  mx += (tol-a);
  if ( !(mn <= mx) )
    return false;
  d = b-a;
  if ( (0.0 < mn && d < mn) || (0.0 > mx && d > mx) )
  {
    // chord lies outside the box
    return false;
  }

  while ( fabs(d) >= 1.0 || (fabs(mn) <= fabs(d)*M && fabs(mx) <= fabs(d)*M) )
  {
    // The chord is not (nearly) parallel to the j-th sides.
    // See if the chord needs to be trimmed by the j-th sides.
    d = 1.0/d;
    s0 = mn*d;
    s1 = mx*d;
    if ( s0 > 1.0 )
    {
      if ( s1 > 1.0 )
      {
        // unstable calculation happens when
        // fabs(d) is very tiny and chord is
        // on the j-th side.
        break;
      }
      s0 = 1.0;
    }
    else if ( s0 < 0.0 )
    {
      if (s1 < 0.0)
      {
        // unstable calculation happens when
        // fabs(d) is very tiny and chord is
        // on the j-th side.
        break;
      }
      s0 = 0.0;
    }
    if ( s1 < 0.0 ) s1 = 0.0; else if ( s1 > 1.0 ) s1 = 1.0;
    d = (1.0-s0)*t0 + s0*t1;
    t1 = (1.0-s1)*t0 + s1*t1;
    t0 = d;
    v = chord.PointAt(s0);
    chord.to = chord.PointAt(s1);
    chord.from = v;
    break;
  }
  
  // test k-th coordinate direction
  const int k = (i&&j) ? 0 : ((i!=1&&j!=1)?1:2);
  a = chord.from[k];
  b = chord.to[k];
  mn = bbox.m_min[k];
  mx = bbox.m_max[k];
  if ( !(mn <= mx) )
    return false;
  mn -= (tol+a);
  mx += (tol-a);
  if ( !(mn <= mx) )
    return false;
  d = b-a;
  if ( (0.0 < mn && d < mn) || (0.0 > mx && d > mx) )
  {
    // chord does not intersect the rectangle
    return false;
  }

  if ( line_parameters )
  {

    while ( fabs(d) >= 1.0 || (fabs(mn) <= fabs(d)*M && fabs(mx) <= fabs(d)*M) )
    {
      // The chord is not (nearly) parallel to the k-th sides.
      // See if the chord needs to be trimmed by the k-th sides.
      d = 1.0/d;
      s0 = mn*d;
      s1 = mx*d;
      if ( s0 > 1.0 )
      {
        if ( s1 > 1.0 )
        {
          // unstable calculation happens when
          // fabs(d) is very tiny and chord is
          // on the k-th side.
          break;
        }
        s0 = 1.0;
      }
      else if ( s0 < 0.0 )
      {
        if (s1 < 0.0)
        {
          // unstable calculation happens when
          // fabs(d) is very tiny and chord is
          // on the k-th side.
          break;
        }
        s0 = 0.0;
      }

      if ( s1 < 0.0 ) s1 = 0.0; else if ( s1 > 1.0 ) s1 = 1.0;
      d = (1.0-s0)*t0 + s0*t1;
      t1 = (1.0-s1)*t0 + s1*t1;
      t0 = d;
      break;
    }

    if (t0 > t1 )
    {
      line_parameters->Set(t1,t0);
    }
    else
    {
      line_parameters->Set(t0,t1);
    }
  }

  return true;
}



bool ON_Intersect( const ON_Line& lineA, const ON_Line& lineB, 
                double* lineA_parameter, 
                double* lineB_parameter
                )
{
  // If you are looking at this code because you don't like an
  // answer you are getting, then the first thing to try is
  // to read the header file comments and try calling 
  // ON_IntersectLineLine.
  bool rc = false;
  double M_zero_tol = 0.0;
  int i, rank;
  double pr_tolerance, pivot, X[2], Y[2];

  ON_3dVector A = lineA.Direction();
  ON_3dVector B = lineB.Direction();
  ON_3dVector C = lineB[0] - lineA[0];
  
  ON_Matrix M(2,2);
  M[0][0] =  ON_DotProduct( A, A );
  M[1][1] =  ON_DotProduct( B, B );
  M[0][1] = M[1][0] = -ON_DotProduct( A, B );

  // this swap done to get row+col pivot accuracy
  if ( M[0][0] < M[1][1] ) {
    M.SwapCols(0,1);
    i = 1;
  }
  else {
    i = 0;
  }
  // 2021-07-21, Pierre, RH-65014
  // It does not make much sense to use a tolerance lower than ON_EPSILON on the
  // result of arithmetic on doubles. If M[1][1] is smaller than 1, we need to
  // bound M_zero_tol to ON_EPSILON or ON_Intersect will wrongly return true on
  // many near-parallel cases. pr_tolerance also needs to be bounded as it
  // cannot be smaller than M_zero_tolerance.
  //
  // Before that change, lines
  // Line A = (5.4301839655138417, -9.5, 0, -0.6, -9.5, 0)
  // Line B = (5.2373595635311068, 10.5, 0, 5.6603292194932395, 10.5, 0)
  // would be found as intersecting, with pivot ~= 2 * M_zero_tolerance
  if (fabs(M[1][1]) > 1.) {
    pr_tolerance = fabs(M[1][1]) * ON_SQRT_EPSILON;
    M_zero_tol = fabs(M[1][1]) * ON_EPSILON;
  } else {
    pr_tolerance = ON_SQRT_EPSILON;
    M_zero_tol = ON_EPSILON;
  }

  Y[0] =  ON_DotProduct( A, C );
  Y[1] = -ON_DotProduct( B, C );

  rank = M.RowReduce( M_zero_tol, Y, &pivot );
  if ( rank == 2 ) 
  {
    // 19 November 2003 Dale Lear and Chuck
    //   Added lineA.from/to == lineB.from/to tests
    //   so exact answer gets returned when people
    //   expect it.
    rc = true;
    if ( lineA.from == lineB.from )
    {
      if ( lineA_parameter )
        *lineA_parameter = 0.0;
      if ( lineB_parameter )
        *lineB_parameter = 0.0;
    }
    else if ( lineA.from == lineB.to )
    {
      if ( lineA_parameter )
        *lineA_parameter = 0.0;
      if ( lineB_parameter )
        *lineB_parameter = 1.0;
    }
    else if ( lineA.to == lineB.from )
    {
      if ( lineA_parameter )
        *lineA_parameter = 1.0;
      if ( lineB_parameter )
        *lineB_parameter = 0.0;
    }
    else if ( lineA.to == lineB.to )
    {
      if ( lineA_parameter )
        *lineA_parameter = 1.0;
      if ( lineB_parameter )
        *lineB_parameter = 1.0;
    }
    else
    {
      rc = M.BackSolve( 0.0, 2, Y, X );
      if ( rc ) 
      {
        if ( lineA_parameter )
          *lineA_parameter = X[i];
        if ( lineB_parameter )
          *lineB_parameter = X[1-i];
        if ( fabs(pivot) <= pr_tolerance ) 
        {
          // test answer because matrix was close to singular
          // (This test is slow but it is rarely used.)
          ON_3dPoint pA = lineA.PointAt(X[i]);
          ON_3dPoint pB = lineB.PointAt(X[1-i]);
          double d = pA.DistanceTo(pB);
          if ( d > pr_tolerance && d > ON_ZERO_TOLERANCE ) { 
            ON_3dPoint qA = lineA.ClosestPointTo(pB);
            ON_3dPoint qB = lineB.ClosestPointTo(pA);
            double dA = pA.DistanceTo(qB);
            double dB = pB.DistanceTo(qA);
            if ( 1.1*dA < d ) {
              rc = false;
            }
            else if ( 1.1*dB < d ) {
              rc = false;
            }
          }
        }
      }
    }
  }
  
  return rc;
}


bool ON_Intersect( 
  const ON_Line& line,
  const ON_PlaneEquation& plane_equation,  
  double* line_parameter 
  )
{
  bool rc = false;
  double a, b, d, fd, t;

  a = plane_equation.ValueAt(line.from);
  b = plane_equation.ValueAt(line.to);
  d = a-b;
  if ( d == 0.0 )
  {
    if ( fabs(a) < fabs(b) )
      t = 0.0;
    else if ( fabs(b) < fabs(a) )
      t = 1.0;
    else
      t = 0.5;
  }
  else
  {
    d = 1.0/d;
    fd = fabs(d);
    if ( fd > 1.0 && (fabs(a) >= ON_DBL_MAX/fd || fabs(b) >= ON_DBL_MAX/fd ) )
    {
      // double overflow - line may be (nearly) parallel to plane
      t = 0.5;
    }
    else 
    {
      t = a/(a-b); // = a*d;  a/(a-b) has more precision than a*d
      rc = true;
    }
  }

  if ( line_parameter )
    *line_parameter = t;

  return rc;
}

bool ON_Intersect(
  const ON_Line& line,
  const ON_Plane& plane,  
  double* line_parameter 
  )
{
  return ON_Intersect( line, plane.plane_equation, line_parameter );
}



bool ON_Intersect( const ON_Plane& R, const ON_Plane& S,
                   ON_Line& L )
{
  ON_3dVector d = ON_CrossProduct( S.zaxis, R.zaxis );
  ON_3dPoint p = 0.5*(R.origin + S.origin);
  ON_Plane T( p, d );
  bool rc = ON_Intersect( R, S, T, L.from );
  L.to = L.from + d;
  return rc;
}


bool ON_Intersect( const ON_Plane& R, const ON_Plane& S, const ON_Plane& T,
                ON_3dPoint& P )
{
  double pr = 0.0;
  const int rank = ON_Solve3x3( 
                &R.plane_equation.x, &S.plane_equation.x, &T.plane_equation.x, 
                -R.plane_equation.d, -S.plane_equation.d, -T.plane_equation.d, 
                &P.x, &P.y, &P.z, &pr );
  return (rank == 3) ? true : false;
}


int ON_Intersect(
        const ON_Plane& plane,
        const ON_Sphere& sphere, 
        ON_Circle& circle
        )
{
  // 16 April 2011 Dale Lear
  //   Prior to this date, this function did not return the correct answer.

  int rc = 0;
  const double sphere_radius = fabs(sphere.radius);
  double tol = sphere_radius*ON_SQRT_EPSILON;
  if ( !(tol >= ON_ZERO_TOLERANCE) )
    tol = ON_ZERO_TOLERANCE;
  const ON_3dPoint sphere_center = sphere.Center();
  ON_3dPoint circle_center = plane.ClosestPointTo(sphere_center);
  double d = circle_center.DistanceTo(sphere_center);

  circle.radius = 0.0;

  if ( ON_IsValid(sphere_radius) && ON_IsValid(d) && d <= sphere_radius + tol )
  {
    if ( sphere_radius > 0.0 )
    {
      d /= sphere_radius;
      d = 1.0 - d*d;
      // The d > 4.0*ON_EPSILON was picked by testing spheres with
      // radius = 1 and center = (0,0,0).  Do not make 4.0*ON_EPSILON 
      // any smaller and please discuss changes with Dale Lear.
      circle.radius = (d > 4.0*ON_EPSILON) ? sphere_radius*sqrt(d) : 0.0;
    }
    else
      circle.radius = 0.0;

    if ( circle.radius <= ON_ZERO_TOLERANCE )
    {
      // return a single point
      rc = 1;
      
      circle.radius = 0.0;

      //  When tolerance is in play, put the point on the sphere.
      //  If the caller prefers the plane, then they can adjust the
      //  returned answer to get the plane.
      ON_3dVector R = circle_center - sphere_center;
      double r0 = R.Length();
      if ( r0 > 0.0 )
      {
        R.Unitize();
        ON_3dPoint C1 = sphere_center + sphere_radius*R;
        double r1 = C1.DistanceTo(sphere_center);
        if ( fabs(sphere.radius-r1) < fabs(sphere.radius-r0) )
          circle_center = C1;
      }
    }
    else 
    {
      // return a circle
      rc = 2;
    }
  }

  // Update circle's plane here in case the input plane 
  // is the circle's plane member.
  circle.plane = plane;
  circle.plane.origin = circle_center;
  circle.plane.UpdateEquation();

  return rc;
}



int ON_Intersect(
        const ON_Line& line,
        const ON_Sphere& sphere,
        ON_3dPoint& A,
        ON_3dPoint& B // intersection point(s) returned here
        )
{
  int rc = 0;
  const ON_3dPoint sphere_center = sphere.plane.origin;
  const double sphere_radius = fabs(sphere.radius);
  double tol = sphere_radius*ON_SQRT_EPSILON;
  if ( tol < ON_ZERO_TOLERANCE )
    tol = ON_ZERO_TOLERANCE;
  ON_3dPoint line_center = line.ClosestPointTo(sphere_center);
  double d = line_center.DistanceTo(sphere_center);
  if ( d >= sphere_radius-tol ) {
    rc = ( d <= sphere_radius-tol ) ? 1 : 0;
    A = line_center;
    B = sphere.ClosestPointTo(line_center);
  }
  else {
    d /= sphere_radius;
    double h = sphere_radius*sqrt(1.0 - d*d);
    ON_3dVector V = line.Direction();
    V.Unitize();
    A = sphere.ClosestPointTo(line_center - h*V);
    B = sphere.ClosestPointTo(line_center + h*V);
    d = A.DistanceTo(B);
    if ( d <= ON_ZERO_TOLERANCE ) {
      A = line_center;
      B = sphere.ClosestPointTo(line_center);
      rc = 1;
    }
    else
      rc = 2;
  }
  return rc;
}

static
int Intersect2dLineCircle(
        ON_2dPoint line_from, // 2d line from point
        ON_2dPoint line_to,
        double r,
        double tol,
        double* t0,
        double* t1
        )
{
  // returns 0 = line is degenerate
  // 1 = one intersection returned, 
  // 2 = 2 intersections returned
  // 3 = 1 closest point returned
  int xcnt = 0;
  bool bRev;
  double t, d, c, s, x, y, dx, dy;
  ON_2dVector v;

  if ( line_from.x*line_from.x + line_from.y*line_from.y > line_to.x*line_to.x + line_to.y*line_to.y )
  {
    v = line_from;
    line_from = line_to;
    line_to = v;
    bRev = true;
  }
  else
    bRev = false;
  dx = line_to.x - line_from.x;
  dy = line_to.y - line_from.y;
  if ( fabs(dx) >= fabs(dy) )
  {
    if ( dx == 0.0 )
    {
      *t0 = 0.0;
      *t1 = 0.0;
      return 0;
    }
    else
    {
      d = dy/dx;
      d = fabs(dx)*sqrt(1.0+d*d);
    }
  }
  else
  {
    d = dx/dy;
    d = fabs(dy)*sqrt(1.0+d*d);
  }
  c = dx/d;
  s = dy/d;

  // change coordinates so line is horizontal
  x = line_from.x; 
  y = line_from.y;
  line_from.x = c*x + s*y;
  line_from.y = c*y - s*x;

  x = line_to.x; 
  y = line_to.y;
  line_to.x = c*x + s*y;
  line_to.y = c*y - s*x;



  dx = line_to.x - line_from.x; // should be length of line
  if ( dx == 0.0 )
  {
    *t0 = 0.0;
    *t1 = 0.0;
    return 0;
  }
  dy = line_to.y - line_from.y; // should be zero
  t = -line_from.x/dx;
  x = (1.0-t)*line_from.x + t*line_to.x;
  y = (1.0-t)*line_from.y + t*line_to.y;
  d = fabs(y);
  if ( d < r-tol )
  {
    // two intersection points
    d /= r;
    d = r*sqrt(1.0-d*d);
    x = -(d + line_from.x)/dx;
    y =  (d - line_from.x)/dx;
    if ( bRev )
    {
      x = 1.0-x;
      y = 1.0-y;
    }
    if (x<=y)
    {
      *t0 = x;
      *t1 = y;
    }
    else
    {
      *t0 = y;
      *t1 = x;
    }
    xcnt = ( x == y ) ? 1 : 2;
  }
  else if ( d > r+tol )
  {
    // closest point returned
    xcnt = 3;
    if ( bRev )
      t = 1.0-t;
    *t0 = t;
    *t1 = t;
  }
  else
  {
    // one intersection point returned
    xcnt = 1;
    if ( bRev )
      t = 1.0-t;
    *t0 = t;
    *t1 = t;
  }
  return xcnt;
}




int ON_Intersect(
        const ON_Line& line, 
        const ON_Cylinder& cylinder, // if cylinder.height[0]==cylinder.height[1],
                                     // then infinite cyl is used.  Otherwise
                                     // finite cyl is used.
        ON_3dPoint& A, ON_3dPoint& B // intersection point(s) returned here
        )
{
  bool bFiniteCyl = true;
  int rc = 0;
  const double cylinder_radius = fabs(cylinder.circle.radius);
  double tol = cylinder_radius*ON_SQRT_EPSILON;
  if ( tol < ON_ZERO_TOLERANCE )
    tol = ON_ZERO_TOLERANCE;

  ON_Line axis;
  axis.from = cylinder.circle.plane.origin + cylinder.height[0]*cylinder.circle.plane.zaxis;
  axis.to   = cylinder.circle.plane.origin + cylinder.height[1]*cylinder.circle.plane.zaxis;
  if ( axis.Length() <= tol ) {
    axis.to = cylinder.circle.plane.origin + cylinder.circle.plane.zaxis;
    bFiniteCyl = false;
  }


  //bool bIsParallel = false;
  double line_t, axis_t;
  if ( !ON_Intersect(line,axis,&line_t,&axis_t) ) {
    axis.ClosestPointTo( cylinder.circle.plane.origin, &axis_t );
    line.ClosestPointTo( cylinder.circle.plane.origin, &line_t );
  }
  ON_3dPoint line_point = line.PointAt(line_t);
  ON_3dPoint axis_point = axis.PointAt(axis_t);
  double d = line_point.DistanceTo(axis_point);
  if ( bFiniteCyl ) {
    if ( axis_t < 0.0 )
      axis_t = 0.0;
    else if ( axis_t > 1.0 )
      axis_t = 1.0;
    axis_point = axis.PointAt(axis_t);
  }
  
  if ( d >= cylinder_radius-tol) {
    rc = ( d <= cylinder_radius+tol ) ? 1 : 0;
    A = line_point;
    ON_3dVector V = line_point - axis_point;
    if ( bFiniteCyl ) {
      V = V - (V*cylinder.circle.plane.zaxis)*cylinder.circle.plane.zaxis;
    }
    V.Unitize();
    B = axis_point + cylinder_radius*V;
    if ( rc == 1 ) {
      // check for overlap
      ON_3dPoint P = axis.ClosestPointTo(line.from);
      d = P.DistanceTo(line.from);
      if ( fabs(d-cylinder_radius) <= tol ) {
        P = axis.ClosestPointTo(line.to);
        d = P.DistanceTo(line.to);
        if ( fabs(d-cylinder_radius) <= tol ) {
          rc = 3;
          A = cylinder.ClosestPointTo(line.from);
          B = cylinder.ClosestPointTo(line.to);
        }
      }
    }
  }
  else {
    // transform to coordinate system where equation of cyl
    // is x^2 + y^2 = R^2 and solve for line parameter(s).
    ON_Xform xform;
    xform.Rotation( cylinder.circle.plane, ON_xy_plane );
    ON_Line L = line;
    L.Transform(xform);

    const double x0 = L.from.x;
    const double x1 = L.to.x;
    const double x1mx0 = x1-x0;
    double ax = x1mx0*x1mx0;
    double bx = 2.0*x1mx0*x0;
    double cx = x0*x0;

    const double y0 = L.from.y;
    const double y1 = L.to.y;
    const double y1my0 = y1-y0;
    double ay = y1my0*y1my0;
    double by = 2.0*y1my0*y0;
    double cy = y0*y0;

    double t0, t1;
    int qerc = ON_SolveQuadraticEquation(ax+ay, bx+by, cx+cy-cylinder_radius*cylinder_radius,
                                         &t0,&t1);
    if ( qerc == 2 ) {
      // complex roots - ignore (tiny) imaginary part caused by computational noise.
      t1 = t0;
    }
    A = cylinder.ClosestPointTo(line.PointAt(t0));
    B = cylinder.ClosestPointTo(line.PointAt(t1));

    d = A.DistanceTo(B);
    if ( d <= ON_ZERO_TOLERANCE ) {
      A = line_point;
      ON_3dVector V = line_point - axis_point;
      if ( bFiniteCyl ) {
        V = V - (V*cylinder.circle.plane.zaxis)*cylinder.circle.plane.zaxis;
      }
      V.Unitize();
      B = axis_point + cylinder_radius*V;
      rc = 1;
    }    
    else
      rc = 2;
  }
  return rc;
}


int ON_Intersect(
      const ON_Line& line, 
      const ON_Circle& circle,
      double* line_t0,
      ON_3dPoint& circle_point0,
      double* line_t1,
      ON_3dPoint& circle_point1
      )
{
  // transform to coordinate system where equation of circle
  // is x^2 + y^2 = R^2 and solve for line parameter(s).
  ON_Xform xform;
  xform.ChangeBasis( circle.plane, ON_xy_plane );
  xform.ChangeBasis( ON_xy_plane, circle.plane );
  ON_Line L = line;
  L.Transform(xform);
  double r = fabs(circle.radius);
  double tol = (circle.Center().MaximumCoordinate()+ r)*ON_RELATIVE_TOLERANCE;
  if ( tol < ON_ZERO_TOLERANCE )
    tol = ON_ZERO_TOLERANCE;
  int xcnt;
  if (    fabs(L.from.x - L.to.x) <= tol 
       && fabs(L.from.y - L.to.y) <= tol
       && fabs(L.from.z - L.to.z) > tol )
  {
    if (fabs(L.from.x * L.from.x + L.from.y * L.from.y - r*r) < tol)
    {
      *line_t0 = -L.from.z / (L.to.z - L.from.z);
      xcnt = 1;
    }
    else
     xcnt = 0;
  }
  else
  {
    xcnt = Intersect2dLineCircle( ON_2dPoint(L.from), ON_2dPoint(L.to), r, tol, line_t0, line_t1 );
    if ( xcnt == 3 )
      xcnt = 1;
  }
 
  int rcnt = 0;  // actual number of intersections within tol
  if (xcnt > 0)
  {
    ON_3dPoint line_point1, line_point0 = line.PointAt(*line_t0);
    circle_point0 = circle.ClosestPointTo(line_point0);
    bool x0 = circle_point0.IsCoincident(line_point0);
    bool x1 = false;

    if (xcnt == 2)
    {
      line_point1 = line.PointAt(*line_t1);
      circle_point1 = circle.ClosestPointTo(line_point1);
      x1 = circle_point1.IsCoincident(line_point1);
    }
 

    if(x0)
      rcnt ++;
      
    if (x1)
    {
      rcnt++;
      if (rcnt == 1)
      {
        circle_point0 = circle_point1;
        line_t0 = line_t1;
      }
    }
  }

  return rcnt;
}

int ON_Intersect(
  const ON_Plane& plane,
  const ON_Circle& circle,
  ON_3dPoint& point0,
  ON_3dPoint& point1
                  )
{
  int rval = -1;
  ON_Line xline;
	double a,b;
  bool rc = ON_Intersect(plane, circle.Plane(), xline);
	if(rc)
  {
    rval = ON_Intersect(xline, circle, &a, point0, &b, point1);
  }
  else
  {
		double d = plane.plane_equation.ValueAt( circle.Center() );
		if(d<ON_ZERO_TOLERANCE)
			rval =3;
    else
      rval = 0;
  }
  return rval;
}

int ON_Intersect(
  const ON_Plane& plane,
  const ON_Arc& arc,
  ON_3dPoint& point0,
  ON_3dPoint& point1
                  )
{
  int rval = -1;
  ON_Line xline;
	double a,b;
  bool rc = ON_Intersect(plane, arc.Plane(), xline);
	if(rc)
  {
    rval = ON_Intersect(xline, arc, &a, point0, &b, point1);
  }
  else
  {
		double d = plane.plane_equation.ValueAt( arc.StartPoint() );
		if(d<ON_ZERO_TOLERANCE)
			rval =3;
    else
      rval = 0;
  }
  return rval;
}


int ON_Intersect(
  const ON_Circle& C0,
  const ON_Circle& C1,
  ON_3dPoint& P0,
  ON_3dPoint& P1)
{
  P0 = P1 = ON_3dPoint::UnsetPoint;
  int xcnt = -1;

  const double costol = ON_ZERO_TOLERANCE;
  double scale0 = C0.MaximumCoordinate();
  double abstol = C1.MaximumCoordinate();
  if (abstol < scale0)
    abstol = scale0;
  abstol *= ON_RELATIVE_TOLERANCE;
  if (abstol < ON_ZERO_TOLERANCE)
    abstol = ON_ZERO_TOLERANCE;
  

  bool parallel = (fabs(C0.plane.Normal() * C1.plane.Normal()) > 1 - costol);   // todo pretty loose and insensitive
  bool coplanar = parallel && (C0.plane.DistanceTo(C1.plane.origin) < abstol);
  if (coplanar)
  {
    const ON_Circle* C[2] = { &C0, &C1 };
    if (C1.Radius() >= C0.Radius())
    {
      C[0] = &C1;
      C[1] = &C0;
    }
    double R0 = C[0]->Radius();       // largest radius
    double R1 = C[1]->Radius();

    ON_3dVector D = C[1]->Center() - C[0]->Center();
    double d = D.Length();

    if (d > abstol)
    {
      D.Unitize();
      ON_3dVector Dperp = ON_CrossProduct(D, C[0]->Normal());

      if (d > R0 + R1 + abstol)
        xcnt = 0;                 // disks are disjoint
      else if (d + R1 + abstol < R0)
        xcnt = 0;                 // small disk is in interior of large disk
      else
      {
        double d1 = (R0 * R0 - R1 * R1 + d * d) / (2 * d);
        double a1 = R0 * R0 - d1 * d1;
        if (a1 < 0)
          a1 = 0;
       
        a1 = sqrt(a1);

        if (a1 < .5 * abstol)
        {
          xcnt = 1;
          P0 = C[0]->Center() + d1 * D;
        }
        else
        {
          xcnt = 2;
          P0 = C[0]->Center() + d1 * D + a1 * Dperp;
          P1 = C[0]->Center() + d1 * D - a1 * Dperp;
        }
      }
    }
    else if (R0 - R1 < abstol)
      xcnt = 3;
    else
      xcnt = 0;
  }
  else if (!parallel)
  {
    ON_Line  PxP;
    if (ON_Intersect(C0.plane, C1.plane, PxP))
    {
      ON_3dPoint CxL[2][2]; 

      double t0, t1;
      int x0 = ON_Intersect( PxP, C0,  &t0, CxL[0][0], &t1, CxL[0][1] );
      int x1 = ON_Intersect( PxP, C1,  &t0, CxL[1][0], &t1, CxL[1][1] );
      xcnt = 0;
      for (int i = 0; i < x0; i++)
      {
        int j;
        for (j = 0; j < x1; j++)
        {
          if(ON_PointsAreCoincident(3,false,CxL[0][i], CxL[1][j]))
            break;
        }
        if (j < x1)
        {
          (xcnt?P0:P1) = CxL[0][i];
          xcnt++;
        }
      }

    }
  }
  return xcnt;
}



int ON_Intersect(
  const ON_Arc& A0,
  const ON_Arc& A1,
  ON_3dPoint& P0,
  ON_3dPoint& P1)
{
  P0 = P1 = ON_3dPoint::UnsetPoint;
  ON_3dPoint* P[] = { &P0, &P1 };
  int xcnt = 0;

  double scale0 = A0.MaximumCoordinate();
  double abstol = A1.MaximumCoordinate();
  if (abstol < scale0)
    abstol = scale0;
  abstol *= ON_RELATIVE_TOLERANCE;
  if (abstol < ON_ZERO_TOLERANCE)
    abstol = ON_ZERO_TOLERANCE;


  ON_3dPoint CCX[2];
  int cxcnt = ON_Intersect(static_cast<const ON_Circle&>(A0), static_cast<const ON_Circle&>(A1), CCX[0], CCX[1]);
  if ( cxcnt < 3)
  {
    for (int i = 0; i < cxcnt; i++)
    {
      double t;
      if (A0.ClosestPointTo(CCX[i], &t))
      {
        if (CCX[i].DistanceTo(A0.PointAt(t)) < abstol)
        {
          if (A1.ClosestPointTo(CCX[i], &t))
          {
            if (CCX[i].DistanceTo(A1.PointAt(t)) < abstol)
              *P[xcnt++] = CCX[i];
          }
        }
      }
    }
  }
  else if (cxcnt == 3)
  {
    // circle doesn't degenerate to a point
    // order arcs by size
    const  ON_Arc* Size[] = { &A0, &A1 };     //Size[0]<=Size[1]
    if (A0.Domain().Length() > A1.Domain().Length())
    {
      Size[0] = &A1;
      Size[1] = &A0;
    }

    // Match ends of smaller to larger arc
    double LittleEndMatch[2];  // relative to Big ArcBig,  0-start, 1-end , .5 (interior),  -1 ( exterior)

    ON_Interval BigInterior = Size[1]->Domain();    // interior domain of big arc
    if (!BigInterior.Expand(-abstol / Size[1]->Radius()))         // circles are not degenerate
      BigInterior = ON_Interval::Singleton(Size[1]->Domain().Mid());
    
    for (int ei = 0; ei < 2; ei++)
    {
      double t;
      ON_3dPoint LittleEnd = ei ? Size[0]->EndPoint() : Size[0]->StartPoint();
      if (Size[1]->ClosestPointTo(LittleEnd, &t))
      {
        switch (BigInterior.Clamp(t))
        {
        case(-1):
          if (Size[1]->StartPoint().DistanceTo(LittleEnd) < abstol)
            LittleEndMatch[ei] = 0;   // start
          else
            LittleEndMatch[ei] = -1;  // exterior
          break;
        case(0):
          LittleEndMatch[ei] = .5;    // interior
          break;
        case(1):
          if (Size[1]->EndPoint().DistanceTo(LittleEnd) < abstol)
            LittleEndMatch[ei] = 1;       // end
          else
            LittleEndMatch[ei] = -1;     // exterior
          break;
        }
      }
    }

    if (LittleEndMatch[0] == .5 || LittleEndMatch[1] == .5)
      xcnt = 3;     // an interior match means an overlap
    else if (LittleEndMatch[0] == -1 && LittleEndMatch[1] == -1)
      xcnt = 0;     // both points exterior means  intersection is empty
    else if (LittleEndMatch[0] == -1)
      *P[xcnt++] = Size[0]->EndPoint();    // if start is exterior end must be an intersection point
    else if (LittleEndMatch[1] == -1)
      *P[xcnt++] = Size[0]->StartPoint();
    else
    {
      // Both endpoints match endpoints of Big
      // LittleEndMatch[ei] \in { 0, 1 }
      bool Orientation_agree = (A0.Normal() * A1.Normal() > 0);     // true if  the orientations agree
      if (LittleEndMatch[0] != LittleEndMatch[1])
      {
        if (Orientation_agree == (LittleEndMatch[0] == 1.0))
        {
          *P[xcnt++] = Size[0]->StartPoint();
          *P[xcnt++] = Size[0]->EndPoint();
        }
        else
          xcnt = 3;
      }
      else
      {
        // Degenerate cases
        if (Size[0]->StartPoint().DistanceTo(Size[0]->EndPoint()) < abstol)
          *P[xcnt++] = Size[0]->StartPoint();
        else
          xcnt = 3;
      }
    }
  }
  
  return xcnt;
}

int ON_Intersect(
      const ON_Line& line, 
      const ON_Arc& arc,
      double* line_t0,
      ON_3dPoint& arc_point0,
      double* line_t1,
      ON_3dPoint& arc_point1
      )
{
  // RH-48633 In V7 and earlier there were cases where 1 was returned and the 
  // returned arc_point0 is the closest point on the arc to the line but not an
  // intersection point
  ON_Circle c = arc;
  ON_3dPoint p[2];
  double t[2], a[2], s;
  bool b[2] = {false,false};
  int i, xcnt = ON_Intersect( line, c, &t[0], p[0], &t[1], p[1] );
 
  if ( xcnt > 0 )
  {
    // make sure points are on the arc;
    ON_Interval arc_domain = arc.DomainRadians();
    for ( i = 0; i < xcnt; i++ )
    {
      b[i] = c.ClosestPointTo(p[i], &a[i]);
      if ( b[i] )
      {
        s = arc_domain.NormalizedParameterAt(a[i]);
        if ( s < 0.0 )
        {
          if ( s >= -ON_SQRT_EPSILON )
          {
            a[i] = arc_domain[0];
            p[i] = c.PointAt(a[i]);
            b[i] = line.ClosestPointTo( p[i], &t[i] );
          }
          else
            b[i] = false;
        }
        else if ( s > 1.0 )
        {
          if ( s <= 1.0+ON_SQRT_EPSILON )
          {
            a[i] = arc_domain[1];
            p[i] = c.PointAt(a[i]);
            b[i] = line.ClosestPointTo( p[i], &t[i] );
          }
          else
            b[i] = false;
        }
      }
    }
    if ( !b[0] && !b[1] )
      xcnt = 0;

    if ( xcnt == 2 )
    {
      if ( !b[1] )
        xcnt = 1;
      if ( !b[0] )
      {
        xcnt = 1;
        b[0] = b[1];
        t[0] = t[1];
        a[0] = a[1];
        p[0] = p[1];
        b[1] = 0;
      }
      if ( xcnt == 2 && t[0] == t[1] )
      {
        xcnt = 1;
        b[1] = 0;
        ON_3dPoint q = line.PointAt(t[0]);
        if ( p[0].DistanceTo(q) > p[1].DistanceTo(q) )
        {
          a[0] = a[1];
          t[0] = t[1];
          p[0] = p[1];
        }
      }
    }
    if  ( xcnt == 1 && !b[0] )
      xcnt = 0;
    if ( xcnt >= 1 )
    {
      if ( line_t0 )
        *line_t0 = t[0];
      arc_point0 = p[0];
    }
    if ( xcnt == 2 )
    {
      if ( line_t1 )
        *line_t1 = t[1];
      arc_point1 = p[1];
    }
  }
  return xcnt;
}

int ON_Intersect( const ON_Sphere& sphere0, 
                  const ON_Sphere& sphere1, 
                  ON_Circle& circle
                 )

{
  double r0 = sphere0.Radius();
  double r1 = sphere1.Radius();
  ON_3dPoint C0 = sphere0.Center();
  ON_3dPoint C1 = sphere1.Center();
  ON_3dVector D = C1-C0;
  double d = D.Length();
  if (!D.Unitize()){
    if (fabs(r1-r0) > ON_ZERO_TOLERANCE)
      return 0;//Same center, different radii
    return 3;//Same sphere.
  }

  //Spheres are apart.
  if (d > r0 + r1)
    return 0;

  //Spheres tangent and apart
  if (d == r0+r1){
    ON_3dPoint P = C0 + r0*D;
    circle.Create(P, 0.0);
    return 1;
  }

  //Spheres tangent, one inside the other
  if (d == fabs(r0-r1)){
    ON_3dPoint P = (r0 > r1) ? C0 + r0*D : C0 - r0*D;
    circle.Create(P, 0.0);
    return 1;
  }

  //Spheres don't intersect, one inside the other.
  if (d < fabs(r0-r1))
    return 0;

  //Intersection is a circle
  double x = 0.5*(d*d + r0*r0 - r1*r1)/d;
  if (x >= r0){//Shouldn't happen
    ON_3dPoint P = C0 + r0*D;
    circle.Create(P, 0.0);
    return 1;
  }
  if (x <= -r0){//Shouldn't happen
    ON_3dPoint P = C0 - r0*D;
    circle.Create(P, 0.0);
    return 1;
  }
  double y = r0*r0 - x*x;
  if (y < 0.0)//Shouldn't happen
    return 0;
  y = sqrt(y);

  ON_3dPoint P = C0 + x*D;
  ON_Plane plane(P, D);
  circle.Create(plane, y);
  return 2;
}


