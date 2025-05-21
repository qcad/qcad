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


bool operator==(const ON_Line& a, const ON_Line& b)
{
  // Properly handles nans.
  return (a.from == b.from && a.to == b.to);
}

bool operator!=(const ON_Line& a, const ON_Line& b)
{
  // Properly handles nans.
  return (a.from != b.from || a.to != b.to);
}


ON_Line::ON_Line()
  : from(ON_3dPoint::Origin)
  , to(ON_3dPoint::Origin)
{
}

ON_Line::ON_Line( ON_3dPoint from_pt, ON_3dPoint to_pt )
  : from(from_pt)
  , to(to_pt)
{}

ON_Line::ON_Line( ON_2dPoint from_pt, ON_2dPoint to_pt )
  : from(from_pt)
  , to(to_pt)
{}

ON_Line::~ON_Line()
{
}

ON_3dPoint& ON_Line::operator[](int i)
{
  return (i<=0) ? from : to;
}

const ON_3dPoint& ON_Line::operator[](int i) const
{
  return (i<=0) ? from : to;
}

bool ON_Line::Create( const ON_3dPoint from_pt, const ON_3dPoint to_pt )
{
  from = from_pt;
  to = to_pt;
  return IsValid();
}

bool ON_Line::Create( const ON_2dPoint from_pt, const ON_2dPoint to_pt )
{
  from = ON_3dPoint(from_pt);
  to = ON_3dPoint(to_pt);
  return IsValid();
}


bool ON_Line::IsValid() const
{
  bool from_rc = ON_CV_COORDINATE_IS_VALID(from.x) && ON_CV_COORDINATE_IS_VALID(from.y) && ON_CV_COORDINATE_IS_VALID(from.z);
  bool to_rc = ON_CV_COORDINATE_IS_VALID(to.x) && ON_CV_COORDINATE_IS_VALID(to.y) && ON_CV_COORDINATE_IS_VALID(to.z);
  return (from != to && true == from_rc && true == to_rc);
}

double ON_Line::Length() const
{
  return from.DistanceTo(to);
}

ON_3dVector ON_Line::Direction() const
{
  return (ON_UNSET_VALUE < to.x && to.x < ON_UNSET_POSITIVE_VALUE && ON_UNSET_VALUE <from.x && from.x < ON_UNSET_POSITIVE_VALUE) 
    ? (to-from)
    : (ON_3dPoint::UnsetPoint == from && ON_3dPoint::UnsetPoint == to ? ON_3dVector::UnsetVector : ON_3dVector::NanVector)
    ;
}

ON_3dVector ON_Line::Tangent() const
{
  ON_3dVector V = Direction();
  V.Unitize();
  return V;
}

ON_3dPoint ON_Line::PointAt( double t ) const
{
  // 26 Feb 2003 Dale Lear
  //     Changed 
  //          return (1-t)*from + t*to;
  //     to the following so that axis aligned lines will
  //     return exact answers for large values of t.  
  //     See RR 9683.
 

  //08 May 2022 - Greg. Mikko, Chuck.  This is more accurate than the parameterwise 
  //(1-t)*from + t*to with fudging.  Note that if any coordinate of from is the same as that of to,
  //the answer will be exact in that coord.
  return  (t < 0.5) ? from + t*(to-from) : to + (1.0-t)*(from-to);
}

void ON_Line::Reverse()
{
  ON_3dPoint tmp = from;
  from = to;
  to = tmp;
}

bool ON_Line::ClosestPointTo( const ON_3dPoint& point, double *t ) const
{
  bool rc = false;
  if ( t ) {
    const ON_3dVector D = Direction();
    const double DoD = D.LengthSquared();
    if ( DoD > 0.0 ) {
      if ((point - from).LengthSquared() <= (point - to).LengthSquared()) {
        *t = ((point - from)*D)/DoD;
      }
      else {
        *t = 1.0 + ((point - to)*D)/DoD;
      }
      rc = true;
    }
    else {
      *t = 0.0;
			rc = true;			// (GBA) Closet point to a degenerate line works as well
    }
  }
  return rc;
}

ON_3dPoint ON_Line::ClosestPointTo( const ON_3dPoint& point ) const
{
  double t;
  ClosestPointTo( point, &t );
  return PointAt(t);
}

double ON_Line::DistanceTo( ON_3dPoint test_point ) const
{
  return test_point.DistanceTo(ClosestPointTo(test_point));
}


bool ON_Line::Transform( const ON_Xform& tr )
{
  from = tr*from;
  to = tr*to;
  // 5 June 2003 Dale Lear RR 10493
  //    Always return true.
  //return (from != to) ? true : false;
  return true;
}

// rotate line about a point and axis
bool ON_Line::Rotate(
      double sin_angle,                  // sin(angle)
      double cos_angle,                  // cos(angle)
      const ON_3dVector& axis,  // axis of rotation
      const ON_3dPoint& center  // center of rotation
      )
{
  ON_Xform rot;
  rot.Rotation( sin_angle, cos_angle, axis, center );
  const bool bFixP0 = (from==center);
  const bool bFixP1 = (to==center);
  const bool rc = Transform( rot );
  if ( bFixP0 )
    from = center;
  if ( bFixP1 )
    to = center;
  return rc;
}

bool ON_Line::Rotate(
      double a,                 // angle in radians
      const ON_3dVector& axis, // axis of rotation
      const ON_3dPoint& center // center of rotation
      )
{
  return Rotate( sin(a), cos(a), axis, center );
}

bool ON_Line::Translate(
      const ON_3dVector& delta
      )
{
  const ON_Xform tr(ON_Xform::TranslationTransformation( delta ));
  return Transform( tr );
}


double ON_Line::MaximumCoordinate() const
{
  return  fmax( from.MaximumCoordinate(), to.MaximumCoordinate());
}

int ON_ArePointsOnLine( // returns 0=no, 1 = yes, 2 = pointset is (to tolerance) a single point on the line
        int dim,     // 2 or 3
        bool is_rat,
        int count, 
        int stride, const double* point,
        const ON_BoundingBox& bbox, // if needed, use ON_GetBoundingBox(dim,is_rat,count,stride,point)
        const ON_Line& line,  // line to test
        double tolerance
        )
{
  double w;
  int i, j, k;

  if ( count < 1 )
    return 0;

  if ( !line.IsValid() )
  {
    ON_ERROR("line parameter not valid");
    return 0;
  }
  if ( !bbox.IsValid() )
  {
    ON_ERROR("bbox parameter not valid");
    return 0;
  }
  if ( !ON_IsValid(tolerance) || tolerance < 0.0 )
  {
    ON_ERROR("tolerance parameter not valid");
    return 0;
  }
  if ( dim < 2 || dim > 3 )
  {
    ON_ERROR("dim parameter not valid");
    return 0;
  }
  if ( 0 == point )
  {
    ON_ERROR("point parameter not valid");
    return 0;
  }
  if ( stride < (is_rat?(dim+1):dim) )
  {
    ON_ERROR("stride parameter not valid");
    return 0;
  }

  int rc = 0;

  if ( tolerance == 0.0 ) {
    tolerance = bbox.Tolerance();
  }

  ON_3dPoint Q(ON_3dPoint::Origin);

  // test bounding box to quickly detect the common coordinate axis cases
  rc = (count == 1 || bbox.Diagonal().Length() <= tolerance) ? 2 : 1;
  for ( i = 0; rc && i < 2; i++ ) {
    Q.x = bbox[i].x;
    for ( j = 0; rc && j < 2; j++) {
      Q.y = bbox[j].y;
      for ( k = 0; rc && k < 2; k++) {
        Q.z = bbox[k].z;
        if ( Q.DistanceTo( line.ClosestPointTo( Q ) ) > tolerance )
          rc = 0;
      }
    }
  }

  if ( !rc ) {
    // test points one by one
    Q = ON_3dPoint::Origin;
    rc = (count == 1 || bbox.Diagonal().Length() <= tolerance) ? 2 : 1;
    if ( is_rat ) {
      for ( i = 0; i < count; i++ ) {
        w = point[dim];
        if ( w == 0.0 ) {
          ON_ERROR("rational point has zero weight");
          return 0;
        }
        ON_ArrayScale( dim, 1.0/w, point, &Q.x );
        if ( Q.DistanceTo( line.ClosestPointTo( Q ) ) > tolerance ) {
          rc = 0;
          break;
        }
        point += stride;
      }
    }
    else {
      for ( i = 0; i < count; i++ ) {
        memcpy( &Q.x, point, dim*sizeof(Q.x) );
        if ( Q.DistanceTo( line.ClosestPointTo( Q ) ) > tolerance ) {
          rc = 0;
          break;
        }
        point += stride;
      }
    }
  }

  return rc;
}


ON_BoundingBox ON_Line::BoundingBox() const
{
  ON_BoundingBox bbox;
  bbox.Set( 3, false, 2, 3, &from.x, false );
  return bbox;
}

bool ON_Line::GetBoundingBox(
       ON_BoundingBox& bbox,
       int bGrowBox
       ) const
{
  bbox.Set( 3, false, 2, 3, &from.x, bGrowBox );
  return true;
}

bool ON_Line::InPlane( ON_Plane& plane, double tolerance ) const
{
  const ON_3dVector v = to-from;
  const bool bTinyX = fabs(v.x) <= tolerance;
  const bool bTinyY = fabs(v.y) <= tolerance;
  const bool bTinyZ = fabs(v.z) <= tolerance;
  bool rc = true;
  ON_3dVector X;
  ON_3dVector Y;
  if ( bTinyZ && ( !bTinyX || !bTinyY ) )
  {
    X = ON_3dVector::XAxis;
    Y = ON_3dVector::YAxis;
  }
  else if ( bTinyX && ( !bTinyY || !bTinyZ ) )
  {
    X = ON_3dVector::YAxis;
    Y = ON_3dVector::ZAxis;
  }
  else if ( bTinyY && ( !bTinyZ || !bTinyX ) )
  {
    X = ON_3dVector::ZAxis;
    Y = ON_3dVector::XAxis;
  }
  else
  {
    X = v;
    X.Unitize();
    Y.PerpendicularTo(X);
    if ( bTinyX && bTinyY && bTinyZ )
    {
      rc = false;
      if ( X.IsZero() )
      {
        X = ON_3dVector::XAxis;
        Y = ON_3dVector::YAxis;
      }
    }
  }
  plane.CreateFromFrame( from, X, Y );
  return rc;
}

double ON_Line::MinimumDistanceTo( const ON_3dPoint& P ) const
{
  double d, t;
  if (ClosestPointTo(P,&t))
  {
    if ( t < 0.0 ) t = 0.0; else if (t > 1.0) t = 1.0;
    d = PointAt(t).DistanceTo(P);
  }
  else
  {
    // degenerate line
    d = from.DistanceTo(P);
    t = to.DistanceTo(P);
    if ( t < d )
      d = t;
  }
  return d;
}

double ON_Line::MinimumDistanceTo( const ON_Line& L ) const
{
  ON_3dPoint A, B;
  double a, b, t, x, d;
  bool bCheckA, bCheckB;

  bool bGoodX = ON_Intersect(*this,L,&a,&b);

  bCheckA = true;
  if ( a < 0.0) a = 0.0; else if (a > 1.0) a = 1.0; else bCheckA=!bGoodX;
  bCheckB = true;
  if ( b < 0.0) b = 0.0; else if (b > 1.0) b = 1.0; else bCheckB=!bGoodX;

  A = PointAt(a);
  B = L.PointAt(b);
  d = A.DistanceTo(B);

  if ( bCheckA )
  {
    L.ClosestPointTo(A,&t);
    if (t<0.0) t = 0.0; else if (t > 1.0) t = 1.0;
    x = L.PointAt(t).DistanceTo(A);
    if ( x < d )
      d = x;
  }

  if ( bCheckB )
  {
    ClosestPointTo(B,&t);
    if (t<0.0) t = 0.0; else if (t > 1.0) t = 1.0;
    x = PointAt(t).DistanceTo(B);
    if (x < d )
      d = x;
  }
 
  return d;
}

double ON_Line::MaximumDistanceTo( const ON_3dPoint& P ) const
{
  double a, b;
  a = from.DistanceTo(P);
  b = to.DistanceTo(P);
  return ((a<b)?b:a);
}

double ON_Line::MaximumDistanceTo( const ON_Line& L ) const
{
  double a, b;
  a = MaximumDistanceTo(L.from);
  b = MaximumDistanceTo(L.to);
  return ((a<b)?b:a);
}

bool ON_Line::IsFartherThan( double d, const ON_3dPoint& P ) const
{
  if ( P.x > to.x+d && P.x > from.x+d )
  {
    return true;
  }
  if ( P.x < to.x-d && P.x < from.x-d )
  {
    return true;
  }
  if ( P.y > to.y+d && P.y > from.y+d )
  {
    return true;
  }
  if ( P.y < to.y-d && P.y < from.y-d )
  {
    return true;
  }
  if ( P.z > to.z+d && P.z > from.z+d )
  {
    return true;
  }
  if ( P.z < to.z-d && P.z < from.z-d )
  {
    return true;
  }
  return (MinimumDistanceTo(P) > d);
}


bool ON_Line::IsFartherThan( double d, const ON_Line& L ) const
{
  ON_3dPoint A, B;
  double a, b, t, x;
  bool bCheckA, bCheckB;

  a = from.x; if (to.x < a) {b=a; a = to.x;} else b = to.x;
  if ( b+d < L.from.x && b+d < L.to.x )
    return true;
  if ( a-d > L.from.x && a-d > L.to.x )
    return true;

  a = from.y; if (to.y < a) {b=a; a = to.y;} else b = to.y;
  if ( b+d < L.from.y && b+d < L.to.y )
    return true;
  if ( a-d > L.from.y && a-d > L.to.y )
    return true;

  a = from.z; if (to.z < a) {b=a; a = to.z;} else b = to.z;
  if ( b+d < L.from.z && b+d < L.to.z )
    return true;
  if ( a-d > L.from.z && a-d > L.to.z )
    return true;

  if ( !ON_Intersect(*this,L,&a,&b) )
  {
    // lines are parallel or anti parallel
    if ( Direction()*L.Direction() >= 0.0 )
    {
      // lines are parallel
      a = 0.0;
      L.ClosestPointTo(from,&b);
      // If ( b >= 0.0), then this->from and L(b) are a pair of closest points.
      if ( b < 0.0 )
      {
        // Otherwise L.from and this(a) are a pair of closest points.
        b = 0.0;
        ClosestPointTo(L.from,&a);
      }
    }
    else
    {
      // lines are anti parallel
      a = 1.0;
      L.ClosestPointTo(to,&b);
      // If ( b >= 0.0), then this->to and L(b) are a pair of closest points.
      if ( b < 0.0 )
      {
        // Otherwise L.to and this(a) are a pair of closest points.
        b = 0.0;
        ClosestPointTo(L.from,&a);
      }
    }
  }

  A = PointAt(a);
  B = L.PointAt(b);
  x = A.DistanceTo(B);
  if (x > d)
    return true;

  bCheckA = true;
  if ( a < 0.0) a = 0.0; else if (a > 1.0) a = 1.0; else bCheckA=false;
  if (bCheckA )
  {
    A = PointAt(a);
    L.ClosestPointTo(A,&t);
    if (t<0.0) t = 0.0; else if (t > 1.0) t = 1.0;
    x = L.PointAt(t).DistanceTo(A);
  }

  bCheckB = true;
  if ( b < 0.0) b = 0.0; else if (b > 1.0) b = 1.0; else bCheckB=false;
  if ( bCheckB )
  {
    B = L.PointAt(b);
    ClosestPointTo(B,&t);
    if (t<0.0) t = 0.0; else if (t > 1.0) t = 1.0;
    t = PointAt(t).DistanceTo(B);
    if ( bCheckA )
    {
      if ( t<x ) x = t;
    }
    else
    {
      x = t;
    }
  }
 
  return (x > d);
}

ON_Triangle::ON_Triangle(const ON_3dPoint vertices[3])
{
	for(int i=0; i<3; i++)
		m_V[i] = vertices[i];
}

ON_Triangle::ON_Triangle(const ON_3dPoint & a, const ON_3dPoint & b, const ON_3dPoint & c)
{
	m_V[0]= a; m_V[1] = b; m_V[2] = c;
}

ON_Triangle::ON_Triangle(double x)
{
	// Note this constructor overload is useful so that ON_Triangle(0) doesn't
	// get interpreted as ON_Triangle(nullptr)
	ON_3dPoint p(x, x, x);
	m_V[0] = m_V[1] = m_V[2] = p;
}

ON_Triangle::ON_Triangle(const double vertices[9])
{
  m_V[0] = ON_3dPoint(vertices);
  m_V[1] = ON_3dPoint(vertices ? vertices+3 : vertices);
  m_V[2] = ON_3dPoint(vertices ? vertices+6 : vertices);
}

ON_Triangle::operator ON_3dPoint*()
{
	return m_V;
}

ON_Triangle::operator const ON_3dPoint*() const
{
	return m_V;
}

bool ON_Triangle::IsValid() const
{
	return m_V[0].IsValid() && m_V[1].IsValid() && m_V[2].IsValid();
}

ON_3dPoint& ON_Triangle::operator[](int i)
{
	return m_V[i];
}

const ON_3dPoint& ON_Triangle::operator[](int i) const
{
	return m_V[i];
}

void ON_Triangle::Create(const ON_3dPoint  vertices[3])
{
	for (int i = 0; i < 3; i++)
		m_V[i] = vertices[i];
}

void ON_Triangle::Create(const ON_3dPoint & a, const ON_3dPoint & b, const ON_3dPoint & c)
{
	m_V[0] = a;
	m_V[1] = b; 
	m_V[2] = c;
}

ON_BoundingBox ON_Triangle::BoundingBox() const
{
	ON_BoundingBox bbox;
	bbox.Set(3, false, 3, 3, m_V[0], false);
	return bbox;
}

bool ON_Triangle::GetBoundingBox(
	ON_BoundingBox& bbox,
	int bGrowBox
) const
{
	bbox.Set(3, false, 3, 3, m_V[0], bGrowBox);
	return true;
}

bool ON_Triangle::GetTightBoundingBox(
	ON_BoundingBox& tight_bbox,
	bool bGrowBox,
	const ON_Xform* xform ) const
{
	if (bGrowBox && !tight_bbox.IsValid())
	{
		bGrowBox = false;
	}

	bool rc = true;
	if (xform && !xform->IsIdentity())
	{
		for (int i = 0; i < 3; i++)
		{
			ON_3dPoint P = (*xform)*m_V[i];
			rc = tight_bbox.Set(P, bGrowBox) && rc;
			bGrowBox = true;
		}
	}
	else
	{
		rc =GetBoundingBox(tight_bbox, bGrowBox);
	}

	return rc;
}

unsigned char ON_Triangle::LongestEdge() const
{
  double l0 = (m_V[1] - m_V[2]).LengthSquared();
  double l1 = (m_V[2] - m_V[0]).LengthSquared();
  double l2 = (m_V[0] - m_V[1]).LengthSquared();

  return l1 < l2 ? ((l2 <= l0) ? 0 : 2) : ((l1 <= l0) ? 0 : 1);
}

unsigned char ON_Triangle::ShortestEdge() const
{
  double l0 = (m_V[1] - m_V[2]).LengthSquared();
  double l1 = (m_V[2] - m_V[0]).LengthSquared();
  double l2 = (m_V[0] - m_V[1]).LengthSquared();

  return l2 < l1 ? ((l2 < l0) ? 2 : 0) : ((l1 < l0) ? 1 : 0);
}

ON_Line ON_Triangle::Edge(int i) const
{
	return  ON_Line(m_V[(i + 1) % 3], m_V[(i + 2) % 3]);
}

ON_3dVector ON_Triangle::Normal() const
{
	int i0 = 0; // base vetex for computation s/b opposite longest side
									 // too minimize roundoff 
									 // ( see Kahan https://people.eecs.berkeley.edu/~wkahan/MathH110/Cross.pdf).
	double max_len = -1;
	for (int i = 0; i < 3; i++)
	{
		ON_3dVector V = Edge(i).Direction();
		double normV = V.MaximumCoordinate();
		if (normV > max_len)
		{
			max_len = normV;
			i0 = i;
		}
	}

	ON_3dVector V = m_V[(i0 + 1)%3] - m_V[i0];
	ON_3dVector W = m_V[(i0 + 2)%3] - m_V[i0];

	return ON_CrossProduct(V, W);
}

double ON_Triangle::Area() const
{
	return .5 * Normal().Length();
}


bool ON_Triangle::IsDegenerate(double area_tol) const
{
	return (Area() < area_tol);
}

ON_3dVector ON_Triangle::UnitNormal() const
{
	auto V =  Normal();
	V.Unitize();
	return V;
}

ON_PlaneEquation ON_Triangle::PlaneEquation() const
{
	auto U = UnitNormal();
	double d = U*m_V[0];
	return ON_PlaneEquation(U.x, U.y, U.z, d);
}

ON_3dPoint ON_Triangle::PointAt(double s1, double s2) const
{
	return (1 - s1 - s2)* m_V[0] + s1*m_V[1] + s2*m_V[2];
}

ON_3dPoint ON_Triangle::Centroid() const
{
	return PointAt(1.0/3.0, 1.0/3.0);
}

bool ON_Triangle::GetBarycentricCoordinates(
  const ON_3dPoint& P,
  bool constrainInside,
  double* s1, double* s2
) const
{
	bool rc = false;
	// Choose  base vertex v[i0] is closest to P
	int i0 = 0;
	double Min_norm = ON_DBL_MAX;
	for (int i = 0; i < 3; i++)
	{
		ON_3dVector V = P - m_V[i];
		double d = V.MaximumCoordinate();
		if (d < Min_norm)
		{
			i0 = i;
			Min_norm = d;
		}
	}

	ON_3dVector VP = P - m_V[i0];
	ON_3dVector V = m_V[(i0 + 1) % 3] - m_V[i0];
	ON_3dVector W = m_V[(i0 + 2) % 3] - m_V[i0];
	ON_3dPoint s(0, 0, 0);		// set to barycentric coordinates of solution

	if (ON_DecomposeVector(VP, V, W, &s[(i0 + 1) % 3], &s[(i0 + 2) % 3]))
	{
		// use decomposition
		s[i0] = 1 - s[(i0 + 1) % 3] - s[(i0 + 2) % 3];

    if (constrainInside)
		  for (int i = 0; i < 3; i++)
			  if (s[i] < 0)
			  {
				  double t;
				  if (Edge(i).ClosestPointTo(P, &t))	
				  {
					  s = ON_3dPoint( 0,0,0 );
					  if (t < 0)
					  {
						  s[(i + 1) % 3] = 1.0;
					  }

					  else if (t >= 1.0)
					  {
						  s[(i + 2) % 3] = 1.0;
					  }
					  else
					  {
						  s[(i + 1) % 3] = 1 - t;
						  s[(i + 2) % 3] = t;
					  }
				  }
				  break;
			  }
		rc = true;
	}
	else
	{
		// decomposition failed:
		// Find closest point to longest edge i0
		double max = Edge(0).Direction().LengthSquared();
    i0 = 0;
		for (int i = 1; i < 3; i++)
		{
			double lensq = Edge(i).Direction().LengthSquared();
			if (max < lensq)
			{
				i0 = i;
				max = lensq;
			}
		}
		double t;
		if (Edge(i0).ClosestPointTo(P, &t))
		{
			s[(i0 + 1) % 3] = (1 - t);
			s[(i0 + 2) % 3] = t;
			rc = true;
		}
	
	}
	if (s1)
		*s1 = s[1];
	if (s2)
		*s2 = s[2];
	return rc;
}

bool ON_Triangle::ClosestPointTo(const ON_3dPoint & P, double * s1, double * s2) const
{
  return GetBarycentricCoordinates(P, true, s1, s2);
}


ON_3dPoint ON_Triangle::ClosestPointTo(const ON_3dPoint& P) const
{
	ON_3dPoint s(0, 0, 0);
	ClosestPointTo(P, &s[1], &s[2]);
	return PointAt(s[1], s[2]);
}

double ON_Triangle::DistanceTo(const ON_3dPoint& P) const
{
	return P.DistanceTo(ClosestPointTo(P));
}

void ON_Triangle::Reverse(int i)
{
	auto temp = m_V[(i + 1) % 3];
	m_V[(i + 1) % 3] = m_V[(i + 2) % 3];
	m_V[(i + 2) % 3] = temp;
}

bool ON_Triangle::Transform(const ON_Xform & xform)
{
	for (int i = 0; i < 3; i++) m_V[i] = xform * m_V[i];
	return true;
}

bool ON_Triangle::Rotate(double sin_angle, double cos_angle, 
			const ON_3dVector & axis_of_rotation, 
			const ON_3dPoint & center_of_rotation)
{
	ON_Xform R;
	R.Rotation(sin_angle, cos_angle, axis_of_rotation, center_of_rotation);
	return Transform(R);
}

bool ON_Triangle::Rotate(double angle_in_radians, const ON_3dVector & axis_of_rotation, const ON_3dPoint & center_of_rotation)
{
	ON_Xform R;
	R.Rotation(angle_in_radians, axis_of_rotation, center_of_rotation);
	return Transform(R);
}

bool ON_Triangle::Translate(const ON_3dVector & delta)
{
	const ON_Xform T(ON_Xform::TranslationTransformation(delta));
	return Transform(T);
}

void ON_Triangle::Split(unsigned char edge, ON_3dPoint pt, ON_Triangle& out_a, ON_Triangle& out_b) const
{
  switch (edge % 3)
  {
  case 0:
    out_a.m_V[0] = m_V[0];
    out_a.m_V[1] = m_V[1];
    out_a.m_V[2] = pt;
    out_b.m_V[0] = m_V[0];
    out_b.m_V[1] = pt;
    out_b.m_V[2] = m_V[2];
    break;
  case 1:
    out_a.m_V[0] = m_V[0];
    out_a.m_V[1] = m_V[1];
    out_a.m_V[2] = pt;
    out_b.m_V[0] = pt;
    out_b.m_V[1] = m_V[1];
    out_b.m_V[2] = m_V[2];
    break;
  default: //2
    out_a.m_V[0] = m_V[0];
    out_a.m_V[1] = pt;
    out_a.m_V[2] = m_V[2];
    out_b.m_V[0] = pt;
    out_b.m_V[1] = m_V[1];
    out_b.m_V[2] = m_V[2];
    break;
  }
}

void ON_Triangle::Flip(unsigned char edge)
{
  switch (edge % 3)
  {
  case 0:
    std::swap(m_V[1], m_V[2]);
    break;
  case 1:
    std::swap(m_V[2], m_V[0]);
    break;
  default: //2
    std::swap(m_V[0], m_V[1]);
    break;
  }
}

void ON_Triangle::Spin(unsigned char move)
{
  ON_3dPoint tmp;
  switch (move % 3)
  {
  case 0:
    break;
  case 1:
    tmp = m_V[0];
    m_V[0] = m_V[2];
    m_V[2] = m_V[1];
    m_V[1] = tmp;
    break;
  default: //2
    tmp = m_V[0];
    m_V[0] = m_V[1];
    m_V[1] = m_V[2];
    m_V[2] = tmp;
    break;
  }
}


bool operator==(const ON_Triangle & a, const ON_Triangle & b)
{
	// Properly handles nans.
	return (a.m_V[0] == b.m_V[0] &&
					a.m_V[1] == b.m_V[1] &&
					a.m_V[2] == b.m_V[2]);
}

bool operator!=(const ON_Triangle & a, const ON_Triangle & b)
{
	// Properly handles nans.
	return (a.m_V[0] != b.m_V[0] ||
					a.m_V[1] != b.m_V[1] ||
					a.m_V[2] != b.m_V[2]);
}

