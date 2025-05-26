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

ON_VIRTUAL_OBJECT_IMPLEMENT(ON_Surface,ON_Geometry,"4ED7D4E1-E947-11d3-BFE5-0010830122F0");

ON_Surface::ON_Surface() : m_stree(0)
{}

ON_Surface::ON_Surface(const ON_Surface& src) : ON_Geometry(src), m_stree(0)
{}

unsigned int ON_Surface::SizeOf() const
{
  unsigned int sz = ON_Geometry::SizeOf();
  sz += (sizeof(*this) - sizeof(ON_Geometry));
  // Currently, the size of m_stree is not included
  // because this is cached runtime information.
  // Applications that care about object size are 
  // typically storing "inactive" objects for potential
  // future use and should call DestroyRuntimeCache(true)
  // to remove any runtime cache information.
  return sz;
}

ON_Surface& ON_Surface::operator=(const ON_Surface& src)
{
  DestroySurfaceTree();
  ON_Geometry::operator=(src);
  return *this;
}

ON_Surface::~ON_Surface()
{
  // Do not call the (virtual) DestroyRuntimeCache or 
  // DestroySurfaceTree (which calls DestroyRuntimeCache()
  // because it opens the potential for crashes in a
  // "dirty" destructors of classes derived from ON_Surface
  // that to not use DestroyRuntimeCache() in their
  // destructors and to not set deleted pointers to zero.
  if ( m_stree ) 
  {
#if defined(OPENNURBS_PLUS_INC_)
    delete m_stree;
#endif
    m_stree = 0;
  }
}

ON_Surface* ON_Surface::DuplicateSurface() const
{
  return Duplicate();
}

ON::object_type ON_Surface::ObjectType() const
{
  return ON::surface_object;
}

ON_BOOL32 ON_Surface::GetDomain( int dir, double* t0, double* t1 ) const
{
  ON_Interval d = Domain(dir);
  if ( t0 ) *t0 = d[0];
  if ( t1 ) *t1 = d[1];
  return d.IsIncreasing();
}

ON_BOOL32 ON_Surface::GetSurfaceSize( 
    double* width, 
    double* height 
    ) const
{
  if ( width )
    *width = 0.0;
  if ( height )
    *height = 0.0;
  return false;
}

bool ON_Surface::SetDomain( int dir, ON_Interval domain )
{
  return ( dir >= 0 
           && dir <= 1 
           && domain.IsIncreasing() 
           && SetDomain( dir, domain[0], domain[1] )) ? true : false;
}

ON_BOOL32 ON_Surface::SetDomain( 
  int, // 0 sets first parameter's domain, 1 gets second parameter's domain
  double, double 
  )
{
  // TODO make this pure virutual when all the source code is available
  return false;
}

//////////
// If t is in the domain of the surface, GetSpanVectorIndex() returns the 
// span vector index "i" such that span_vector[i] <= t <= span_vector[i+1].
// The "side" parameter determines which span is selected when t is at the
// end of a span.
//
//virtual
ON_BOOL32 ON_Surface::GetSpanVectorIndex(
      int dir, // 0 gets first parameter's domain, 1 gets second parameter's domain
      double t,      // [IN] t = evaluation parameter
      int side,         // [IN] side 0 = default, -1 = from below, +1 = from above
      int* span_vector_i,        // [OUT] span vector index
      ON_Interval* span_domain // [OUT] domain of the span containing "t"
      ) const
{
  ON_BOOL32 rc = false;
  int i;
  int span_count = SpanCount(dir);
  if ( span_count > 0 ) {
    double* span_vector = (double*)onmalloc((span_count+1)*sizeof(span_vector[0]));
    rc = GetSpanVector( dir, span_vector );
    if (rc) {
      i = ON_NurbsSpanIndex( 2, span_count, span_vector, t, side, 0 );
      if ( i >= 0 && i <= span_count ) {
        if ( span_vector_i )
          *span_vector_i = i;
        if ( span_domain )
          span_domain->Set( span_vector[i], span_vector[i+1] );
      }
      else
        rc = false;
    }
    onfree(span_vector);
  }
  return rc;
}

ON_BOOL32 ON_Surface::GetParameterTolerance( // returns tminus < tplus: parameters tminus <= s <= tplus
       int dir,
       double t,       // t = parameter in domain
       double* tminus, // tminus
       double* tplus   // tplus
       ) const
{
  ON_BOOL32 rc = false;
  ON_Interval d = Domain( dir );
  if ( d.IsIncreasing() )
    rc = ON_GetParameterTolerance( d.Min(), d.Max(), t, tminus, tplus );
  return rc;
}

ON_Surface::ISO
ON_Surface::IsIsoparametric( const ON_Curve& curve, const ON_Interval* subdomain ) const
{
  ISO iso = not_iso;

  if ( subdomain )
  {
    ON_Interval cdom = curve.Domain();
    double t0 = cdom.NormalizedParameterAt(subdomain->Min());
    double t1 = cdom.NormalizedParameterAt(subdomain->Max());
    if ( t0 < t1-ON_SQRT_EPSILON )
    {
      if ( (t0 > ON_SQRT_EPSILON && t0 < 1.0-ON_SQRT_EPSILON) || (t1 > ON_SQRT_EPSILON && t1 < 1.0-ON_SQRT_EPSILON) )
      {
        cdom.Intersection(*subdomain);
        if ( cdom.IsIncreasing() )
        {
          ON_NurbsCurve nurbs_curve;
          if ( curve.GetNurbForm( nurbs_curve, 0.0,&cdom) )
          {
            return IsIsoparametric( nurbs_curve, 0 );
          }
        }
      }
    }
  }


  ON_BoundingBox bbox;
  double tolerance = 0.0;
  const int dim = curve.Dimension();
  if ( (dim == 2 || dim==3) && curve.GetBoundingBox(bbox) ) 
  {
    iso = IsIsoparametric( bbox );
    switch (iso) {
    case x_iso:
    case W_iso:
    case E_iso:
      // make sure curve is a (nearly) vertical line
      // and weed out vertical scribbles
      tolerance = bbox.m_max.x - bbox.m_min.x;
      if ( tolerance < ON_ZERO_TOLERANCE && ON_ZERO_TOLERANCE*1024.0 <= (bbox.m_max.y-bbox.m_min.y) )
      {
        // 26 March 2007 Dale Lear
        //    If tolerance is tiny, then use ON_ZERO_TOLERANCE
        //    This fixes cases where iso curves where not getting
        //    the correct flag because tol=1e-16 and the closest
        //    point to line had calculation errors of 1e-15.
        tolerance = ON_ZERO_TOLERANCE;
      }
      if ( !curve.IsLinear( tolerance ) )
        iso = not_iso;
      break;
    case y_iso:
    case S_iso:
    case N_iso:
      // make sure curve is a (nearly) horizontal line
      // and weed out horizontal scribbles
      tolerance = bbox.m_max.y - bbox.m_min.y;
      if ( tolerance < ON_ZERO_TOLERANCE && ON_ZERO_TOLERANCE*1024.0 <= (bbox.m_max.x-bbox.m_min.x) )
      {
        // 26 March 2007 Dale Lear
        //    If tolerance is tiny, then use ON_ZERO_TOLERANCE
        //    This fixes cases where iso curves where not getting
        //    the correct flag because tol=1e-16 and the closest
        //    point to line had calculation errors of 1e-15.
        tolerance = ON_ZERO_TOLERANCE;
      }
      if ( !curve.IsLinear( tolerance ) )
        iso = not_iso;
      break;
    default:
      // nothing here
      break;
    }
  }
  return iso;
}

ON_Surface::ISO 
ON_Surface::IsIsoparametric( const ON_BoundingBox& bbox ) const
{
  ISO iso = not_iso;
  if ( bbox.m_min.z == bbox.m_max.z ) {
    const double ds = bbox.m_max.x - bbox.m_min.x;
    const double dt = bbox.m_max.y - bbox.m_min.y;
    double a, b, s0, s1, t0, t1;
    ON_Interval d = Domain(0);
    s0 = d.Min();
    s1 = d.Max();
    d = Domain(1);
    t0 = d.Min();
    t1 = d.Max();
    double stol = (s1-s0)/32.0;
    double ttol = (t1-t0)/32.0;
    if ( s0 < s1 && t0 < t1 && ( ds <= stol || dt <= ttol) ) 
    {
      if ( ds*(t1-t0) <= dt*(s1-s0) ) 
      {
        // check for s = constant iso
        if ( bbox.m_max.x <= s0+stol ) 
        {
          // check for west side iso
          GetParameterTolerance( 0, s0, &a, &b);
          if ( a <= bbox.m_min.x && bbox.m_max.x <= b  ) 
            iso = W_iso;
        }
        else if ( bbox.m_min.x >= s1-stol ) 
        {
          // check for east side iso
          GetParameterTolerance( 0, s1, &a, &b);
          if ( a <= bbox.m_min.x && bbox.m_max.x <= b  )
            iso = E_iso;
        }

        if ( iso == not_iso && (s0 < bbox.m_max.x || bbox.m_min.x < s1) )
        {
          // check for interior "u = constant" iso
          GetParameterTolerance( 0, 0.5*(bbox.m_min.x+bbox.m_max.x), &a, &b);
          if ( a <= bbox.m_min.x && bbox.m_max.x <= b  )
            iso = x_iso;
        }
      }
      else
      {
        // check for t = constant iso
        if ( bbox.m_max.y <= t0+ttol ) 
        {
          // check for south side iso
          GetParameterTolerance( 1, t0, &a, &b);
          if ( a < bbox.m_min.y && bbox.m_max.y <= b  )
            iso = S_iso;
        }
        else if ( bbox.m_min.y >= t1-ttol ) 
        {
          // check for north side iso
          GetParameterTolerance( 1, t1, &a, &b);
          if ( a < bbox.m_min.y && bbox.m_max.y <= b  )
            iso = N_iso;
        }

        if ( iso == not_iso && (t0 < bbox.m_max.x || bbox.m_min.x < t1) )
        {
          // check for interior "t = constant" iso
          GetParameterTolerance( 1, 0.5*(bbox.m_min.y+bbox.m_max.y), &a, &b);
          if ( a < bbox.m_min.y && bbox.m_max.y <= b  )
            iso = y_iso;
        }
      }
    }
  }
  return iso;
}


ON_BOOL32 ON_Surface::IsPlanar( ON_Plane* plane, double tolerance ) const
{
  return false;
}

ON_BOOL32 
ON_Surface::IsClosed(int dir) const
{
  ON_Interval d = Domain(dir);
  if ( d.IsIncreasing() && Dimension() <= 3 ) {
    const int span_count = SpanCount(dir?0:1);
    const int span_degree = Degree(dir?0:1);
    if ( span_count > 0 && span_degree > 0 ) {
      ON_SimpleArray<double> s(span_count+1);
      s.SetCount(span_count+1);
      int n = 2*span_degree+1;
      double delta = 1.0/n;
      ON_3dPoint P, Q;
      P.Zero();
      Q.Zero();
      int hintP[2] = {0,0};
      int hintQ[2] = {0,0};
      double *u0, *u1, *v0, *v1;
      double t;
      ON_Interval sp;
      if ( dir ) {
        v0 = &d.m_t[0];
        v1 = &d.m_t[1];
        u0 = &t;
        u1 = &t;
      }
      else {
        u0 = &d.m_t[0];
        u1 = &d.m_t[1];
        v0 = &t;
        v1 = &t;
      }
      if ( GetSpanVector( dir?0:1, s.Array() ) ) {
        int span_index, i;
        for ( span_index = 0; span_index < span_count; span_index++ ) {
          sp.Set(s[span_index],s[span_index+1]);
          for ( i = 0; i < n; i++ ) {
            t = sp.ParameterAt(i*delta);
            if ( !Evaluate( *u0, *v0, 1, 3, P, 0, hintP ) )
              return false;
            if ( !Evaluate( *u1, *v1, 2, 3, Q, 0, hintQ ) )
              return false;
            if ( ON_ComparePoint( 3, 0, &P.x, &Q.x ) )
              return false;
          }
        }
      }
    }
  }
  return false;
}

ON_BOOL32 ON_Surface::IsPeriodic(int dir) const
{
  return false;
}

bool ON_Surface::GetNextDiscontinuity( 
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
  // 28 Jan 2005 - untested code

  // this function must be overridden by surface objects that
  // can have parametric discontinuities on the interior of the curve.

  bool rc = false;

  // using tmp_dtype means I don't have to keep checking for a null dtype;
  int tmp_dtype = 0;
  if ( !dtype )
    dtype = &tmp_dtype;
  *dtype = 0;
  
  if ( t0 != t1 )
  {
    bool bTestC0 = false;
    bool bTestD1 = false;
    bool bTestD2 = false;
    bool bTestT = false;
    bool bTestK = false;
    switch(c)
    {
    case ON::C0_locus_continuous:
      bTestC0 = true;
      break;
    case ON::C1_locus_continuous:
      bTestC0 = true;
      bTestD1 = true;
      break;
    case ON::C2_locus_continuous:
      bTestC0 = true;
      bTestD1 = true;
      bTestD2 = true;
      break;
    case ON::G1_locus_continuous:
      bTestC0 = true;
      bTestT  = true;
      break;
    case ON::G2_locus_continuous:
      bTestC0 = true;
      bTestT  = true;
      bTestK  = true;
      break;
    default:
      // other values ignored on purpose.
      break;
    }

    if ( bTestC0 )
    {
      // 20 March 2003 Dale Lear:
      //   Have to look for locus discontinuities at ends.
      //   Must test both ends becuase t0 > t1 is valid input.
      //   In particular, for ON_CurveProxy::GetNextDiscontinuity() 
      //   to work correctly on reversed "real" curves, the 
      //   t0 > t1 must work right.
      int hinta[2], hintb[2], span_index, j;
      ON_Interval domain = Domain(dir);
      ON_Interval span_domain;
      ON_2dPoint st0, st1;
      ON_3dVector Da[6], Db[6];
      ON_3dVector& D1a = Da[1+dir];
      ON_3dVector& D1b = Db[1+dir];
      ON_3dVector& D2a = Da[3+2*dir];
      ON_3dVector& D2b = Db[3+2*dir];

      if ( t0 < domain[1] && t1 >= domain[1] )
        t1 = domain[1];
      else if ( t0 > domain[0] && t1 <= domain[0] )
        t1 = domain[0];

      if ( (t0 < domain[1] && t1 >= domain[1]) || (t0 > domain[0] && t1 <= domain[0]) )
      {
        if ( IsClosed(dir) )
        {
          int span_count = SpanCount(1-dir);
          double* span_vector = (span_count>0) ? ((double*)onmalloc((span_count+1)*sizeof(*span_vector))) : 0;
          if (!GetSpanVector(1-dir,span_vector))
            span_count = 0;
          st0[dir] = domain[0];
          st1[dir] = domain[1];

          for ( span_index = 0; span_index < span_count && 1 != *dtype; span_index++ )
          {
            span_domain.Set(span_vector[span_index],span_vector[span_index+1]);
            for ( j = (span_index?1:0); j <= 2 && 1 != *dtype; j++ )
            {
              st0[1-dir] = span_domain.ParameterAt(0.5*j);
              st1[1-dir] = st0[1-dir];
              if ( bTestD1 || bTestT )
              {
                // need to check locus continuity at start/end of closed surface.
                if (    Evaluate(st0.x,st0.y,2,3,&Da[0].x,1,hinta) 
                     && Evaluate(st1.x,st1.y,2,3,&Db[0].x,2,hintb) )
                {
                  if ( bTestD1 )
                  {
                    if ( !(D1a-D1b).IsTiny(D1b.MaximumCoordinate()*ON_SQRT_EPSILON ) )
                    {
                      if ( dtype )
                        *dtype = 1;
                      *t = t1;
                      rc = true;
                    }
                    else if ( bTestD2 && !(D2a-D2b).IsTiny(D2b.MaximumCoordinate()*ON_SQRT_EPSILON) )
                    {
                      if ( dtype )
                        *dtype = 2;
                      *t = t1;
                      rc = true;
                    }

                  }
                  else if ( bTestT )
                  {
                    ON_3dVector Ta, Tb, Ka, Kb;
                    ON_EvCurvature( D1a, D2a, Ta, Ka );
                    ON_EvCurvature( D1b, D2b, Tb, Kb );
                    if ( Ta*Tb < cos_angle_tolerance )
                    {
                      if ( dtype )
                        *dtype = 1;
                      *t = t1;
                      rc = true;
                    }
                    else if ( bTestK && (Ka-Kb).Length() > curvature_tolerance )
                    {
                      if ( dtype )
                        *dtype = 2;
                      *t = t1;
                      rc = true;
                    }
                  }
                }
              }
            }
          }

          if ( span_vector)
          {
            onfree(span_vector);
          }
        }
        else
        {
          // open curves are not locus continuous at ends.
          *dtype = 0; // locus C0 discontinuity
          *t = t1;
          rc = true;
        }
      }
    }
  }

  return rc;
}

bool ON_Surface::IsContinuous(
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
  int qi, span_count[2];
  span_count[0] = SpanCount(0);
  span_count[1] = SpanCount(1);
  if ( span_count[0] <= 1 && span_count[1] <= 1 )
    return true;

  ON_3dPoint P[4];
  ON_3dVector Ds[4], Dt[4], Dss[4], Dst[4], Dtt[4], N[4], K1[4], K2[4];
  double gauss[4], mean[4], kappa1[4], kappa2[4], sq[4], tq[4];


  switch ( desired_continuity )
  {
  case ON::C0_locus_continuous:
  case ON::C1_locus_continuous:
  case ON::C2_locus_continuous:
  case ON::G1_locus_continuous:
  case ON::G2_locus_continuous:
    {
      // 7 April 2005 Dale Lear
      //    This locus continuity test was added.  Prior to
      //    this time, this function ignored the word "locus".
      //    The reason for the change is that Chuck's filleting code
      //    needs to query the continuity at the seams of closed surfaces.

      // See ON::continuity comments.  The different sq[] values
      // must NOT be used when s == Domain(0)[0] and must always
      // be used when s == Domain(0)[1].  In particular, if a surface
      // is not closed in the "s" direction and s == Domain(1)[1], then
      // the answer to any locus query is false.
      ON_Interval d = Domain(0);
      if ( s == d[1] )
      {
        sq[0] = sq[1] = d[0];
        sq[2] = sq[3] = d[1];
      }
      else
      {
       sq[0] = sq[1] = sq[2] = sq[3] = s;
      }

      d = Domain(1);
      // See ON::continuity comments.  The different tq[] values
      // must NOT be used when t == Domain(1)[0] and must always
      // be used when t == Domain(1)[1].  In particular, if a surface
      // is not closed in the "t" direction and t == Domain(1)[1], then
      // the answer to any locus query is false.
      if ( t == d[1] )
      {
        tq[0] = tq[3] = d[0];
        tq[1] = tq[2] = d[1];
      }
      else
      {
       tq[0] = tq[1] = tq[2] = tq[3] = t;
      }
    }
    break;

  default:
    sq[0] = sq[1] = sq[2] = sq[3] = s;
    tq[0] = tq[1] = tq[2] = tq[3] = t;
    break;
  }

  desired_continuity = ON::ParametricContinuity(desired_continuity);

  // this is slow and uses evaluation
  // virtual overrides on curve classes that can have multiple spans
  // are much faster because the avoid evaluation
  switch ( desired_continuity )
  {

  case ON::C0_continuous:  
    for ( qi = 0; qi < 4; qi++ )
    {
      if ( !EvPoint( sq[qi], tq[qi], P[qi], qi+1 ) )
        return false;
      if ( qi )
      {
        if ( !(P[qi]-P[qi-1]).IsTiny(point_tolerance) )
          return false;
      }
    }
    if ( !(P[3]-P[0]).IsTiny(point_tolerance) )
      return false;
    break;

  case ON::C1_continuous:
    for ( qi = 0; qi < 4; qi++ )
    {
      if ( !Ev1Der( sq[qi], tq[qi], P[qi], Ds[qi], Dt[qi], qi+1, hint ) )
        return false;
      if ( qi )
      {
        if ( !(P[qi]-P[qi-1]).IsTiny(point_tolerance) )
          return false;
        if ( !(Ds[qi]-Ds[qi-1]).IsTiny(d1_tolerance) )
          return false;
        if ( !(Dt[qi]-Dt[qi-1]).IsTiny(d1_tolerance) )
          return false;
      }
    }
    if ( !(P[3]-P[0]).IsTiny(point_tolerance) )
      return false;
    if ( !(Ds[3]-Ds[0]).IsTiny(d1_tolerance) )
      return false;
    if ( !(Dt[3]-Dt[0]).IsTiny(d1_tolerance) )
      return false;
    break;

  case ON::C2_continuous:
    for ( qi = 0; qi < 4; qi++ )
    {
      if ( !Ev2Der( sq[qi], tq[qi], P[qi], Ds[qi], Dt[qi], 
                    Dss[qi], Dst[qi], Dtt[qi], 
                    qi+1, hint ) )
        return false;
      if ( qi )
      {
        if ( !(P[qi]-P[qi-1]).IsTiny(point_tolerance) )
          return false;
        if ( !(Ds[qi]-Ds[qi-1]).IsTiny(d1_tolerance) )
          return false;
        if ( !(Dt[qi]-Dt[qi-1]).IsTiny(d1_tolerance) )
          return false;
        if ( !(Dss[qi]-Dss[qi-1]).IsTiny(d2_tolerance) )
          return false;
        if ( !(Dst[qi]-Dst[qi-1]).IsTiny(d2_tolerance) )
          return false;
        if ( !(Dtt[qi]-Dtt[qi-1]).IsTiny(d2_tolerance) )
          return false;
      }
    }
    if ( !(P[3]-P[0]).IsTiny(point_tolerance) )
      return false;
    if ( !(Ds[3]-Ds[0]).IsTiny(d1_tolerance) )
      return false;
    if ( !(Dt[3]-Dt[0]).IsTiny(d1_tolerance) )
      return false;
    if ( !(Dss[3]-Dss[0]).IsTiny(d2_tolerance) )
      return false;
    if ( !(Dst[3]-Dst[0]).IsTiny(d2_tolerance) )
      return false;
    if ( !(Dtt[3]-Dtt[0]).IsTiny(d2_tolerance) )
      return false;
    break;

  case ON::G1_continuous:
    for ( qi = 0; qi < 4; qi++ )
    {
      if ( !EvNormal( sq[qi], tq[qi], P[qi], N[qi], qi+1 ) )
        return false;
      if ( qi )
      {
        if ( !(P[qi]-P[qi-1]).IsTiny(point_tolerance) )
          return false;
        if ( N[qi]*N[qi-1] < cos_angle_tolerance )
          return false;
      }
    }
    if ( !(P[3]-P[0]).IsTiny(point_tolerance) )
      return false;
    if ( N[3]*N[0] < cos_angle_tolerance )
      return false;
    break;

  case ON::G2_continuous:
    for ( qi = 0; qi < 4; qi++ )
    {
      if ( !Ev2Der( sq[qi], tq[qi], P[qi], Ds[qi], Dt[qi], 
                    Dss[qi], Dst[qi], Dtt[qi], 
                    qi+1, hint ) )
        return false;
      ON_EvPrincipalCurvatures( Ds[qi], Dt[qi], Dss[qi], Dst[qi], Dtt[qi], N[qi],
                                &gauss[qi], &mean[qi], &kappa1[qi], &kappa2[qi], 
                                K1[qi], K2[qi] );
      if ( qi )
      {
        if ( !(P[qi]-P[qi-1]).IsTiny(point_tolerance) )
          return false;
        if ( N[qi]*N[qi-1] < cos_angle_tolerance )
          return false;
        if ( fabs(kappa1[qi] - kappa1[qi-1]) > curvature_tolerance )
          return false;
        if ( fabs(kappa2[qi] - kappa2[qi-1]) > curvature_tolerance )
          return false;
      }
      if ( !(P[3]-P[0]).IsTiny(point_tolerance) )
        return false;
      if ( N[3]*N[0] < cos_angle_tolerance )
        return false;
      if ( fabs(kappa1[3] - kappa1[0]) > curvature_tolerance )
        return false;
      if ( fabs(kappa2[3] - kappa2[0]) > curvature_tolerance )
        return false;
    }
    break;

  default:
    // intentionally ignoring other ON::continuity enum values
    break;

  }

  return true;
}

ON_BOOL32 
ON_Surface::IsSingular(int side) const
{
  return false;
}

bool ON_Surface::IsSolid() const
{
  const bool bIsClosed0 = ( IsClosed(0) || ( IsSingular(1) && IsSingular(3) ) );
  const bool bIsClosed1 = ( IsClosed(1) || ( IsSingular(0) && IsSingular(2) ) );

  if ( bIsClosed0 && bIsClosed1 )
    return true;

  const ON_Extrusion* extrusion = ON_Extrusion::Cast(this);
  if ( 0 != extrusion && extrusion->IsSolid() )
    return true;

  return false;
}


bool 
ON_Surface::IsAtSingularity(double s, double t,
                            bool bExact //true by default
                            ) const

{
  if (bExact){
    if (s == Domain(0)[0]){
      if (IsSingular(3))
        return true;
    }
    else if (s == Domain(0)[1]){
      if (IsSingular(1))
        return true;
    }
    if (t == Domain(1)[0]){
      if (IsSingular(0))
        return true;
    }
    else if (t == Domain(1)[1]){
      if (IsSingular(2))
        return true;
    }
    return false;
  }

  if (IsAtSingularity(s, t, true))
    return true;

  bool bCheckPartials[2] = {false, false};
  int i;

  double m[2];
  for (i=0; i<2; i++)
    m[i] = Domain(i).Mid();
  if (s < m[0]){
    if (IsSingular(3))
      bCheckPartials[1] = true;
  }
  else {
    if (IsSingular(1))
      bCheckPartials[1] = true;
  }
  if (!bCheckPartials[0] && !bCheckPartials[1]){
    if (t < m[1]){
      if (IsSingular(0))
        bCheckPartials[0] = true;
    }
    else {
      if (IsSingular(2))
        bCheckPartials[0] = true;
    }
  }

  if (!bCheckPartials[0] && !bCheckPartials[1])
    return false;

  ON_3dPoint P;
  ON_3dVector M[2], S[2];
  if (!Ev1Der(s, t, P, S[0], S[1]))
    return false;
  if (!Ev1Der(m[0], m[1], P, M[0], M[1]))
    return false;

  for (i=0; i<2; i++){
    if (!bCheckPartials[i])
      continue;
    if (S[i].Length() < 1.0e-6 * M[i].Length())
      return true;
  }

  return false;

}

int ON_Surface::IsAtSeam(double s, double t) const

{
  int rc = 0;
  int i;
  for (i=0; i<2; i++){
    if (!IsClosed(i))
      continue;
    double p = (i) ? t : s;
    if (p == Domain(i)[0] || p == Domain(i)[1])
      rc += (i+1);
  }

  return rc;
}


ON_3dPoint
ON_Surface::PointAt( double s, double t ) const
{
  ON_3dPoint p(0.0,0.0,0.0);
  EvPoint( s, t, p );
  return p;
}

ON_3dVector
ON_Surface::NormalAt( double s, double t ) const
{
  ON_3dVector N(0.0,0.0,0.0);
  EvNormal( s, t, N );
  return N;
}

ON_BOOL32 ON_Surface::FrameAt( double u, double v, ON_Plane& frame) const
{
  ON_BOOL32 rc = false;
  ON_3dPoint origin;
  ON_3dVector udir, vdir, normal;
  if( EvNormal( u, v, origin, udir, vdir, normal))
  {
    if ( udir.Unitize() )
      vdir = ON_CrossProduct( normal, udir);
    else if ( vdir.Unitize() )
      udir = ON_CrossProduct( vdir, normal);
    frame.CreateFromFrame( origin, udir, vdir);
    rc = frame.IsValid();
  }
  return rc;
}



ON_BOOL32 
ON_Surface::EvPoint( // returns false if unable to evaluate
       double s, double t, // evaluation parameters
       ON_3dPoint& point,
       int side,        // optional - determines which side to evaluate from
                       //         0 = default
                       //         1 from NE quadrant
                       //         2 from NW quadrant
                       //         3 from SW quadrant
                       //         4 from SE quadrant
       int* hint       // optional - evaluation hint (int[2]) used to speed
                       //            repeated evaluations
       ) const
{
  ON_BOOL32 rc = false;
  double ws[128];
  double* v;
  if ( Dimension() <= 3 ) {
    v = &point.x;
    point.x = 0.0;
    point.y = 0.0;
    point.z = 0.0;
  }
  else if ( Dimension() <= 128 ) {
    v = ws;
  }
  else {
    v = (double*)onmalloc(Dimension()*sizeof(*v));
  }
  rc = Evaluate( s, t, 0, Dimension(), v, side, hint );
  if ( Dimension() > 3 ) {
    point.x = v[0];
    point.y = v[1];
    point.z = v[2];
    if ( Dimension() > 128 )
      onfree(v);
  }
  return rc;
}

ON_BOOL32
ON_Surface::Ev1Der( // returns false if unable to evaluate
       double s, double t, // evaluation parameters
       ON_3dPoint& point,
       ON_3dVector& ds,
       ON_3dVector& dt,
       int side,        // optional - determines which side to evaluate from
                       //         0 = default
                       //         1 from NE quadrant
                       //         2 from NW quadrant
                       //         3 from SW quadrant
                       //         4 from SE quadrant
       int* hint       // optional - evaluation hint (int[2]) used to speed
                       //            repeated evaluations
       ) const
{
  ON_BOOL32 rc = false;
  const int dim = Dimension();
  double ws[3*32];
  double* v;
  point.x = 0.0;
  point.y = 0.0;
  point.z = 0.0;
  ds.x = 0.0;
  ds.y = 0.0;
  ds.z = 0.0;
  dt.x = 0.0;
  dt.y = 0.0;
  dt.z = 0.0;
  if ( dim <= 32 ) {
    v = ws;
  }
  else {
    v = (double*)onmalloc(3*dim*sizeof(*v));
  }
  rc = Evaluate( s, t, 1, dim, v, side, hint );
  point.x = v[0];
  ds.x = v[dim];
  dt.x = v[2*dim];
  if ( dim > 1 ) {
    point.y = v[1];
    ds.y = v[dim+1];
    dt.y = v[2*dim+1];
    if ( dim > 2 ) {
      point.z = v[2];
      ds.z = v[dim+2];
      dt.z = v[2*dim+2];
      if ( dim > 32 )
        onfree(v);
    }
  }

  return rc;
}

ON_BOOL32 
ON_Surface::Ev2Der( // returns false if unable to evaluate
       double s, double t, // evaluation parameters
       ON_3dPoint& point,
       ON_3dVector& ds,
       ON_3dVector& dt,
       ON_3dVector& dss,
       ON_3dVector& dst,
       ON_3dVector& dtt,
       int side,        // optional - determines which side to evaluate from
                       //         0 = default
                       //         1 from NE quadrant
                       //         2 from NW quadrant
                       //         3 from SW quadrant
                       //         4 from SE quadrant
       int* hint       // optional - evaluation hint (int[2]) used to speed
                       //            repeated evaluations
       ) const
{
  ON_BOOL32 rc = false;
  const int dim = Dimension();
  double ws[6*16];
  double* v;
  point.x = 0.0;
  point.y = 0.0;
  point.z = 0.0;
  ds.x = 0.0;
  ds.y = 0.0;
  ds.z = 0.0;
  dt.x = 0.0;
  dt.y = 0.0;
  dt.z = 0.0;
  dss.x = 0.0;
  dss.y = 0.0;
  dss.z = 0.0;
  dst.x = 0.0;
  dst.y = 0.0;
  dst.z = 0.0;
  dtt.x = 0.0;
  dtt.y = 0.0;
  dtt.z = 0.0;
  if ( dim <= 16 ) {
    v = ws;
  }
  else {
    v = (double*)onmalloc(6*dim*sizeof(*v));
  }
  rc = Evaluate( s, t, 2, dim, v, side, hint );
  point.x = v[0];
  ds.x = v[dim];
  dt.x = v[2*dim];
  dss.x = v[3*dim];
  dst.x = v[4*dim];
  dtt.x = v[5*dim];
  if ( dim > 1 ) {
    point.y = v[1];
    ds.y = v[dim+1];
    dt.y = v[2*dim+1];
    dss.y = v[3*dim+1];
    dst.y = v[4*dim+1];
    dtt.y = v[5*dim+1];
    if ( dim > 2 ) {
      point.z = v[2];
      ds.z = v[dim+2];
      dt.z = v[2*dim+2];
      dss.z = v[3*dim+2];
      dst.z = v[4*dim+2];
      dtt.z = v[5*dim+2];
      if ( dim > 16 )
        onfree(v);
    }
  }

  return rc;
}


ON_BOOL32
ON_Surface::EvNormal( // returns false if unable to evaluate
         double s, double t, // evaluation parameters (s,t)
         ON_3dVector& normal, // unit normal
         int side,       // optional - determines which side to evaluate from
                         //         0 = default
                         //         1 from NE quadrant
                         //         2 from NW quadrant
                         //         3 from SW quadrant
                         //         4 from SE quadrant
         int* hint       // optional - evaluation hint (int[2]) used to speed
                         //            repeated evaluations
         ) const
{
  ON_3dPoint point;
  ON_3dVector ds, dt;
  return EvNormal( s, t, point, ds, dt, normal, side, hint );
}

ON_BOOL32
ON_Surface::EvNormal( // returns false if unable to evaluate
         double s, double t, // evaluation parameters (s,t)
         ON_3dPoint& point,  // returns value of surface
         ON_3dVector& normal, // unit normal
         int side,       // optional - determines which side to evaluate from
                         //         0 = default
                         //         1 from NE quadrant
                         //         2 from NW quadrant
                         //         3 from SW quadrant
                         //         4 from SE quadrant
         int* hint       // optional - evaluation hint (int[2]) used to speed
                         //            repeated evaluations
         ) const
{
  ON_3dVector ds, dt;
  return EvNormal( s, t, point, ds, dt, normal, side, hint );
}

ON_BOOL32
ON_Surface::EvNormal( // returns false if unable to evaluate
         double s, double t, // evaluation parameters (s,t)
         ON_3dPoint& point,  // returns value of surface
         ON_3dVector& ds, // first partial derivatives (Ds)
         ON_3dVector& dt, // (Dt)
         ON_3dVector& normal, // unit normal
         int side,       // optional - determines which side to evaluate from
                         //         0 = default
                         //         1 from NE quadrant
                         //         2 from NW quadrant
                         //         3 from SW quadrant
                         //         4 from SE quadrant
         int* hint       // optional - evaluation hint (int[2]) used to speed
                         //            repeated evaluations
         ) const
{
  // simple cross product normal - override to support singular surfaces
  ON_BOOL32 rc = Ev1Der( s, t, point, ds, dt, side, hint );
  if ( rc ) {
    const double len_ds = ds.Length();
    const double len_dt = dt.Length();

    // do not reduce the tolerance used here - there is a retry in the code
    // below.
    if ( len_ds >  ON_SQRT_EPSILON*len_dt && len_dt >  ON_SQRT_EPSILON*len_ds ) 
    {
      ON_3dVector a = ds/len_ds;
      ON_3dVector b = dt/len_dt;
      normal = ON_CrossProduct( a, b );
      rc = normal.Unitize();
    }
    else 
    {
      // see if we have a singular point 
      double v[6][3];
      int normal_side = side;
      ON_BOOL32 bOnSide = false;
      ON_Interval sdom = Domain(0);
      ON_Interval tdom = Domain(1);
		  if (s == sdom.Min()) {
			  normal_side = (normal_side >= 3) ? 4 : 1;
        bOnSide = true;
		  }
		  else if (s == sdom.Max()) {
			  normal_side = (normal_side >= 3) ? 3 : 2;
        bOnSide = true;
		  }
		  if (t == tdom.Min()) {
			  normal_side = (normal_side == 2 || normal_side == 3) ? 2 : 1;
        bOnSide = true;
		  }
		  else if (t == tdom.Max()) {
			  normal_side = (normal_side == 2 || normal_side == 3) ? 3 : 4;
        bOnSide = true;
		  }
      if ( !bOnSide )
      {
        // 2004 November 11 Dale Lear 
        //  Added a retry again with a more generous tolerance
        if ( len_ds >  ON_EPSILON*len_dt && len_dt >  ON_EPSILON*len_ds ) 
        {
          ON_3dVector a = ds/len_ds;
          ON_3dVector b = dt/len_dt;
          normal = ON_CrossProduct( a, b );
          rc = normal.Unitize();
        }
        else
        {
          rc = false;
        }
      }
      else {
        rc = Evaluate( s, t, 2, 3, &v[0][0], normal_side, hint );
        if ( rc ) {
	        rc = ON_EvNormal( normal_side, v[1], v[2], v[3], v[4], v[5], normal);
        }
      }
    }
  }
  if ( !rc ) {
    normal.Zero();
  }
  return rc;
}

//virtual
ON_Curve* ON_Surface::IsoCurve(
       int dir,    // 0 first parameter varies and second parameter is constant
                   //   e.g., point on IsoCurve(0,c) at t is srf(t,c)
                   // 1 first parameter is constant and second parameter varies
                   //   e.g., point on IsoCurve(1,c) at t is srf(c,t)
       double c    // value of constant parameter 
       ) const
{
  return NULL;
}

ON_Curve* ON_Surface::Pushup( const ON_Curve& curve_2d,
                  double tolerance,
                  const ON_Interval* curve_2d_subdomain
                  ) const
{
  // virtual overrides do the real work

  // if the 2d curve is an isocurve, then ON_Surface::Pushup
  // will return the answer.  Otherwise, the virtual override
  // will have to do the real work.
  ON_Curve* curve = NULL;
  ISO iso = IsIsoparametric(curve_2d,curve_2d_subdomain);
  int dir = -1;
  switch (iso)
  {
  case x_iso:
  case W_iso:
  case E_iso:
    dir = 1;
    break;
  case y_iso:
  case S_iso:
  case N_iso:
    dir = 0;
    break;
  default:
    // intentionally ignoring other ON_Surface::ISO enum values
    break;
  }
  if ( dir >= 0 )
  {
    double c;
    ON_Interval c2_dom = curve_2d.Domain();
    if ( !curve_2d_subdomain )
      curve_2d_subdomain = &c2_dom;
    ON_3dPoint p0 = curve_2d.PointAt( curve_2d_subdomain->Min() );
    ON_3dPoint p1 = curve_2d.PointAt( curve_2d_subdomain->Max() );
    ON_Interval c3_dom( p0[dir], p1[dir] );
    ON_BOOL32 bRev = c3_dom.IsDecreasing();
    if ( bRev )
      c3_dom.Swap();
    if ( c3_dom.IsIncreasing() )
    {
      if ( p0[1-dir] == p1[1-dir] )
        c = p0[1-dir];
      else
        c = 0.5*(p0[1-dir] + p1[1-dir]);
      curve = IsoCurve( dir, c );
      if ( curve && curve->Domain() != c3_dom )
      {
        if ( !curve->Trim( c3_dom ) )
        {
          delete curve;
          curve = 0;
        }
      }
      if ( curve ) {
        if ( bRev )
          curve->Reverse();
        curve->SetDomain( curve_2d_subdomain->Min(), curve_2d_subdomain->Max() );
      }
    }
  }
  return curve;
} 

static bool CheckPullbackPoint( 
                        const ON_Surface* srf,
                        double u, double v, 
                        int* srf_hint, // array of 2 ints
                        const ON_Curve& curve_3d,
                        double t, 
                        int* crv_hint, // pointer to 1 int
                        const ON_3dVector& lineDir,
                        int* check_hint, // pointer to 1 int
                        double tolerance,
                        double* point_dist)
{
  // returns true if the point srf(u,v) is a valid pullback
  // of the point crv(t).  The value of the returned
  // *point_dist = distance from crv(t) to srf(u,v). 
  // It is possible for true to be returned and have
  // *point_dist > tolerance.  This happens when the curve
  // is not on the surface.  (See the careful test section.)
  bool rc = false;
  ON_3dPoint srfP, crvP;
  ON_3dVector Du, Dv, Duu, Duv, Dvv, T;
  if ( 2 != *check_hint )
  {
    // try quick eval test
    srf->Ev1Der( u, v, srfP, Du, Dv, 0, srf_hint );
    curve_3d.Ev1Der( t, crvP, T, 0, crv_hint );
  }
  else
  {
    srf->Ev2Der( u, v, srfP, Du, Dv, Duu, Duv, Dvv, 0, srf_hint );
    curve_3d.EvTangent( t, crvP, T, 0, crv_hint );
  }
  *point_dist = crvP.DistanceTo(srfP);

  double d = crvP.DistanceTo(srfP);
  if ( d <= tolerance )
  {
    // simple direction test will suffice
    rc = true;
    d = (lineDir.x*Du + lineDir.y*Dv)*T;
    rc = (d >= 0.0); // accept 0 for collapsed span support
    *check_hint = 1; // try quick eval next time
  }
  else
  {
    // careful test is required
    //   check projected distance and test pullback tangent
    if ( 2 != *check_hint )
    {
      // get full derviative information
      srf->Ev2Der( u, v, srfP, Du, Dv, Duu, Duv, Dvv, 0, srf_hint );
      curve_3d.EvTangent( t, crvP, T, 0, crv_hint );
      *check_hint = 2;
    }
    ON_3dVector N(0,0,0);
    ON_EvNormal( 0, Du, Dv, Duu, Duv, Dvv, N );
    ON_3dVector V = (crvP - srfP);
    double normal_dist = V*N;
    d = (V - normal_dist*N).Length();
    rc = ( d <= tolerance );
    if (rc)
    {
      ON_2dVector uvT(0,0);
      ON_Pullback3dVector( T, normal_dist, Du, Dv, Duu, Duv, Dvv, uvT );
      d = uvT.x*lineDir.x + uvT.y*lineDir.y;
      rc = (d >= 0.0); // accept 0 for collapsed span support
    }
  }

  return rc;
}

static bool CheckPullbackLineEnds( const ON_Surface* srf, 
                               const ON_3dPoint& start_uv,
                               const ON_3dPoint& end_uv,
                               const ON_Curve& curve_3d,
                               ON_Interval crv_dom,
                               double tolerance,
                               bool bTestMidPoint,
                               double* dist
                             )
{
  // Used to check a pullback candidate when the surface
  // is closed or singular.
  //
  // Returning false means the line cannot be used.
  //
  // Returning true means that, in the crudest possbile sense,
  // the line is in the right direction.  The dist
  // value can be used to choose the best line from a 
  // set of candidates.  The line still needs to be carefully
  // tested.  This test happens at the end of ON_Surface::Pullback().

  // 20 November 2003 Dale Lear - statck corruption crash fix - srf_hint is an array of 2 ints (not a single int)
  int srf_hint[2]; 

  int crv_hint = 0;
  int check_hint = 0;

  srf_hint[0] = 0;
  srf_hint[1] = 0;

  ON_Line uv(start_uv,end_uv);
  uv.from.z = 0.0;
  uv.to.z = 0.0;
  ON_3dVector lineT = uv.Tangent();
  if ( lineT.x == 0.0 && lineT.y == 0.0 )
    return false;

  double dist0=0.0, dist1=0.0, dist2 = 0.0;

  if ( !CheckPullbackPoint( srf,
          start_uv.x, start_uv.y, srf_hint,
          curve_3d, crv_dom[0], &crv_hint,
          lineT, &check_hint, tolerance, &dist0 ) )
  {
    return false;
  }

  if ( !CheckPullbackPoint( srf,
          end_uv.x, end_uv.y, srf_hint,
          curve_3d, crv_dom[1], &crv_hint,
          lineT, &check_hint, tolerance, &dist1 ))
  {
    return false;
  }

  if ( bTestMidPoint )
  {
    // on surfaces that are closed (like cylinders and tori), 
    // this midpoint test is needed to weed out edge curves
    // connecting the wrong corners.
    ON_3dPoint uv = ON_Line( start_uv,end_uv).PointAt(0.5);
    if ( !CheckPullbackPoint( srf,
            uv.x, uv.y, srf_hint,
            curve_3d, crv_dom.ParameterAt(0.5), &crv_hint,
            lineT, &check_hint, tolerance, &dist2 ))
    {
      return false;
    }
  }

  // set *dist = largest distance from a curve
  // test point end to the surface.  It is ok if this is
  // > tolerance in the case when the curve
  // is not on the surface.
  *dist = (dist0 < dist1) ? ((dist1<dist2)?dist2:dist1) : ((dist0<dist2)?dist2:dist0);

  return true;
}

ON_Curve* ON_Surface::Pullback( const ON_Curve& curve_3d,
                  double tolerance,
                  const ON_Interval* curve_3d_subdomain,
                  ON_3dPoint start_uv,
                  ON_3dPoint end_uv
                  ) const
{
  // 3 April 2003 Dale Lear:
  //    The virtual overrides to the real work. This
  //    base class handes the simple isocurve case and
  //    is called by the fancier Pullback() overrides.
  //ON_3dPoint mid_uv;
  //ON_3dPoint start_srf, mid_srf, end_srf;

  // set dom to an increasing interval of the
  // portion of curve_3d to pullback.
  ON_Interval crv_dom = curve_3d.Domain();
  if ( 0 != curve_3d_subdomain )
  {
    if ( !curve_3d_subdomain->IsIncreasing() )
      return NULL;
    if ( !crv_dom.Intersection(*curve_3d_subdomain) )
      return NULL;
  }
  if ( !crv_dom.IsIncreasing() )
    return NULL;

  const ON_3dPoint start_crv = curve_3d.PointAt(crv_dom[0]);
  const ON_3dPoint end_crv   = curve_3d.PointAt(crv_dom[1]);

  bool bStartFixed = false;
  bool bEndFixed = false;

  start_uv.z = 0.0;
  end_uv.z = 0.0;

  if ( start_uv.IsValid() )
  {
    bStartFixed = true;
  }
  else
  {
    if ( !GetClosestPoint( start_crv, &start_uv.x, &start_uv.y ) )
      return NULL;
  }

  if ( end_uv.IsValid() )
  {
    bEndFixed = true;
  }
  else
  {
    if ( !GetClosestPoint( end_crv, &end_uv.x, &end_uv.y ) )
      return NULL;
  }

  ON_Interval udom = Domain(0);
  ON_Interval vdom = Domain(1);

  if ( !bStartFixed || !bEndFixed )
  {
    // This entire claus attempts to handle surface
    // parameter ambiguities that happen at seams 
    // and singular points.

    ON_BOOL32 bClosedU = IsClosed(0);
    ON_BOOL32 bClosedV = IsClosed(1);
    const double reltol = 0.001;
    ON_BOOL32 bSingS = false;
    ON_BOOL32 bSingE = false;
    ON_BOOL32 bSingN = false;
    ON_BOOL32 bSingW = false;
    int sing_start = 0; // 1 = S, 2 = E, 3 = N, 4 = W;
    int sing_end   = 0; // 1 = S, 2 = E, 3 = N, 4 = W;
    double s, e;

    // resolve ambiguities that happen at singular points
    if ( !bClosedU )
    {
      s = udom.NormalizedParameterAt( start_uv.x);
      e = udom.NormalizedParameterAt( end_uv.x );
      bSingW = IsSingular(3);
      bSingE = IsSingular(1);
      if ( bSingW )
      {
        if ( s <= reltol )
          sing_start = 4;
        if ( e <= reltol )
          sing_end = 4;
      }
      if ( bSingE )
      {
        if ( s >= 1.0-reltol )
          sing_start = 2;
        if ( e >= 1.0-reltol )
          sing_end = 2;
      }

      if ( sing_start && sing_end && sing_start != sing_end && !bStartFixed && !bEndFixed )
      {
        double xx = ON_UNSET_VALUE;
        double yy = ON_UNSET_VALUE;
        if ( GetClosestPoint( curve_3d.PointAt(crv_dom.ParameterAt(0.5)), &xx, &yy ) )
        {
          if ( yy != ON_UNSET_VALUE )
          {
            start_uv.y = yy;
            end_uv.y = yy;
          }
        }
      }
      else if ( sing_start && !bStartFixed && (!sing_end || bEndFixed) )
      {
        start_uv.y = end_uv.y;
      }
      else if ( sing_end && !bEndFixed && (!sing_start || bStartFixed) )
      {
        end_uv.y = start_uv.y;
      }
    }

    if ( !bClosedV )
    {
      s = vdom.NormalizedParameterAt( start_uv.y );
      e = vdom.NormalizedParameterAt( end_uv.y );
      bSingS = IsSingular(0);
      bSingN = IsSingular(2);
      if ( bSingS )
      {
        if ( s <= reltol )
          sing_start = 1;
        if ( e <= reltol )
          sing_end = 1;
      }
      if ( bSingN )
      {
        if ( s >= 1.0-reltol )
          sing_start = 3;
        if ( e >= 1.0-reltol )
          sing_end = 3;
      }

      if ( sing_start && sing_end && sing_start != sing_end && !bStartFixed && !bEndFixed )
      {
        double xx = ON_UNSET_VALUE;
        double yy = ON_UNSET_VALUE;
        if ( GetClosestPoint( curve_3d.PointAt(crv_dom.ParameterAt(0.5)), &xx, &yy ) )
        {
          if (xx != ON_UNSET_VALUE )
          {
            start_uv.x = xx;
            end_uv.x = xx;
          }
        }
      }
      else if ( sing_start && !bStartFixed && (!sing_end || bEndFixed) )
      {
        start_uv.x = end_uv.x;
      }
      else if ( sing_end && !bEndFixed && (!sing_start || bStartFixed) )
      {
        end_uv.x = start_uv.x;
      }

    }

    if ( bClosedU || bClosedV )
    {
      // resolve ambiguities that happen at seams
      double start_u[4];
      int start_u_count=0;
      double start_v[4];
      int start_v_count=0;

      double end_u[4];
      int end_u_count=0;
      double end_v[4];
      int end_v_count=0;

      start_u[start_u_count++] = start_uv.x;
      start_v[start_v_count++] = start_uv.y;
      end_u[end_u_count++] = end_uv.x;
      end_v[end_v_count++] = end_uv.y;

      if ( bClosedU )
      {
        if ( !bStartFixed )
        {
          s = udom.NormalizedParameterAt(start_uv.x);
          if ( s <= reltol )
            start_u[start_u_count++] = udom[1];
          else if ( s >= 1.0-reltol )
            start_u[start_u_count++] = udom[0];
        }
        if ( !bEndFixed )
        {
          e = udom.NormalizedParameterAt(end_uv.x);
          if ( e <= reltol )
            end_u[end_u_count++] = udom[1];
          else if ( e >= 1.0-reltol )
            end_u[end_u_count++] = udom[0];
        }
      }

      if ( bClosedV )
      {
        if ( !bStartFixed )
        {
          s = vdom.NormalizedParameterAt(start_uv.y);
          if ( s <= 0.001 )
            start_v[start_v_count++] = vdom[1];
          else if ( s >= .999 )
            start_v[start_v_count++] = vdom[0];
        }
        if ( !bEndFixed )
        {
          e = vdom.NormalizedParameterAt(end_uv.y);
          if ( e <= 0.001 )
            end_v[end_v_count++] = vdom[1];
          else if ( e >= .999 )
            end_v[end_v_count++] = vdom[0];
        }
      }

      // check all posibilities and choose the best
      {
        int sx0 = 0;
        int sy0 = 0;
        int ex0 = 0;
        int ey0 = 0;
        int si, sj, ei, ej;
        ON_3dPoint suv, euv;
        double dist0 = 1.0e300, dist;

        bool bTestMidPoint = ((bClosedU&&bClosedV)
                              || start_u_count>1 
                              || start_v_count>1 
                              || end_u_count>1 
                              || end_v_count>1
                              );

        bool bHaveCandidate = CheckPullbackLineEnds( this, start_uv, end_uv, curve_3d, crv_dom,
                                                     tolerance, bTestMidPoint,  &dist0 );
        suv.z = 0.0;
        euv.z = 0.0;
        for ( si = 0; si < start_u_count; si++ )
        {
          suv.x = start_u[si];
          for ( sj = 0; sj < start_v_count; sj++ )
          {
            suv.y = start_v[sj];
            for ( ei = 0; ei < end_u_count; ei++ )
            {
              euv.x = end_u[ei];
              for ( ej = 0; ej < end_v_count; ej++ )
              {
                if ( si || sj || ei || ej )
                {
                  euv.y = end_v[ej];
                  dist = dist0;
                  if ( CheckPullbackLineEnds( this, suv, euv, curve_3d, crv_dom, 
                                              tolerance, bTestMidPoint, &dist ) )
                  {
                    if ( dist < dist0 || !bHaveCandidate )
                    {
                      sx0 = si;
                      sy0 = sj;
                      ex0 = ei;
                      ey0 = ej;
                      dist0 = dist;
                      bHaveCandidate = true;
                    }
                  }
                }
              }
            }
          }
        }

        start_uv.x = start_u[sx0];
        start_uv.y = start_v[sy0];
        end_uv.x = end_u[ex0];
        end_uv.y = end_v[ey0];
      }

    }
  }

  double u = (start_uv.x <= end_uv.x) ? start_uv.x : end_uv.x;
  double v = (start_uv.y <= end_uv.y) ? start_uv.y : end_uv.y;

  ON_3dPoint start_srf = PointAt(start_uv.x,start_uv.y);
  ON_3dPoint end_srf   = PointAt(end_uv.x,  end_uv.y);

  ON_3dPoint srfP = PointAt(u,start_uv.y);
  double d1 = start_srf.DistanceTo(srfP);
  srfP = PointAt(u,end_uv.y);
  double d2 = end_srf.DistanceTo(srfP);
  bool bIsoU = ( d1 <= tolerance && d2 <= tolerance );

  srfP = PointAt(start_uv.x,v);
  d1 = start_srf.DistanceTo(srfP);
  srfP = PointAt(end_uv.x,v);
  d2 = end_srf.DistanceTo(srfP);
  bool bIsoV = ( d1 <= tolerance && d2 <= tolerance );

  ON_Line line(start_uv,end_uv);

  if ( start_uv.x == end_uv.x && start_uv.y != end_uv.y )
  {
    bIsoU = true;
    bIsoV = false;
  }
  else if ( start_uv.y == end_uv.y && start_uv.x != end_uv.x )
  {
    bIsoU = false;
    bIsoV = true;
  }
  else if ( bIsoU && !bIsoV )
  {
    // see if a constant u isocurve will work
    if ( !bStartFixed )
    {
      line.from.x = u;
      start_srf = PointAt(line.from.x,line.from.y);
    }
    if ( !bEndFixed )
    {
      line.to.x = u;
      end_srf = PointAt(line.to.x,line.to.y);
    }
  }
  else if ( bIsoV && !bIsoU )
  {
    // see if a constant v isocurve will work
    if ( !bStartFixed )
    {
      line.from.y = v;
      start_srf = PointAt(line.from.x,line.from.y);
    }
    if ( !bEndFixed )
    {
      line.to.y = v;
      end_srf = PointAt(line.to.x,line.to.y);
    }
  }
  else
  {
    // virtual overrides will have to do the pullback
    return NULL;
  }

  // test 65 points on the line
  {
    const int test_count = 64; // must be a power of 2
    double t[test_count+1], s, d;
    t[0] = crv_dom[0];
    t[test_count] = crv_dom[1];
    ON_Interval in;
    int i, j, k, i0, i1, i2;

    int srf_hint[2];
    srf_hint[0] = 0;
    srf_hint[1] = 0;

    int crv_hint = 0;
    int check_hint = 0;

    ON_3dPoint srf_uv;   // surface 2d point
    ON_3dVector lineDir = line.Tangent();

    // check start
    if ( !CheckPullbackPoint( this, line.from.x, line.from.y, srf_hint,
                              curve_3d, crv_dom[0], &crv_hint,
                              lineDir, &check_hint, tolerance, &d ) )
    {
      return NULL;
    }

    // check end
    if ( !CheckPullbackPoint( this, line.to.x, line.to.y, srf_hint,
                              curve_3d, crv_dom[1], &crv_hint,
                              lineDir, &check_hint, tolerance, &d ) )
    {
      return NULL;
    }

    // check interior points
    for ( i = 2; i <= test_count; i *= 2 )
    {
      crv_hint = 0;
      k = (2*test_count)/i; // 64, 32, 16, 8, 4, 2
      i2 = 0;
      for ( j = 1; j < i; j += 2 )
      {
        i0 = i2;
        i2 += k;
        i1 = (i0+i2)/2;
        s = ((double)j)/((double)i);
        srf_uv = line.PointAt(s);
        Evaluate( srf_uv.x, srf_uv.y, 0, 3, &srfP.x, 0, srf_hint );
        in.Set(t[i0],t[i2]);

        // get point on curve_3d that is closest to srfP
        if ( i > 8 )
        {
          // faster local search
          if ( !curve_3d.GetLocalClosestPoint( srfP, in.ParameterAt(0.5), 
                                               &t[i1], &in ) )
            return NULL;
        }
        else
        {
          // slower but more robust global search
          if ( !curve_3d.GetClosestPoint( srfP, &t[i1], 0.0, &in ) )
            return NULL;
        }

        if ( !CheckPullbackPoint( this, srf_uv.x, srf_uv.y, srf_hint,
                                  curve_3d, t[i1], &crv_hint,
                                  lineDir, &check_hint, tolerance, &d ) )
        {
          if ( i > 8 )
          {
            // global double check to make sure local solution
            // was the best possible
            if ( !curve_3d.GetClosestPoint( srfP, &t[i1], 0.0, &in ) )
              return NULL;
            if ( !CheckPullbackPoint( this, srf_uv.x, srf_uv.y, srf_hint,
                                      curve_3d, t[i1], &crv_hint,
                                      lineDir, &check_hint, tolerance, &d ) )
            {
              return NULL;
            }
          }
          else
          {
            return NULL;
          }
        }
      }
    }

    // 18 June 2003 Dale Lear - fix 10136
    // make sure t's generally increase
    int pcnt = 0;
    for ( i = 0; i < test_count; i++ )
    {
      if ( t[i] < t[i+1] )
        pcnt++;
    }
    if ( 2*pcnt <  test_count )
      return NULL;

    {
      // This test is done to make sure the parameter space
      // line segment we've finished validating is not subset
      // of the entire pullback.  The test is done here becuase
      // is uses the more expensive closest point to surface
      // call.  The cases when we get this far are rare so this
      // test should be quick.
      ON_3dPoint crvP, isoP, iso_uv;
      d = 1.0;

      for ( k = 2; k <= 8; k *= 2 )
      {
        d *= 0.5;
        crv_hint = 0;
        for ( i = 1; i < k; i += 2 )
        {
          curve_3d.Evaluate( crv_dom.ParameterAt(i*d), 0, 3, &crvP.x, 0, &crv_hint );
          if ( !GetClosestPoint( crvP, &srf_uv.x, &srf_uv.y ) )
            return NULL;
          Evaluate( srf_uv.x, srf_uv.y, 0, 3, &srfP.x, 0, srf_hint );
          s = 0.5;
          line.ClosestPointTo(srf_uv,&s);
          if ( s < 0.0 ) s = 0.0; else if (s > 1.0) s = 1.0;
          iso_uv = line.PointAt(s);
          Evaluate( iso_uv.x, iso_uv.y, 0, 3, &isoP.x, 0, srf_hint );
          if ( isoP.DistanceTo(srfP) > tolerance )
            return NULL;
        }
      }
    }
  }
  
  // the line works
  ON_LineCurve* pullback = new ON_LineCurve( line );
  pullback->ChangeDimension(2);
  pullback->SetDomain( crv_dom[0], crv_dom[1] );

  return pullback;
}



//virtual
ON_BOOL32 ON_Surface::Trim(
       int dir,
       const ON_Interval& domain
       )
{
  return false;
}

//virtual
bool ON_Surface::Extend(
      int dir,
      const ON_Interval& domain
      )
{
  return false;
}

//virtual
ON_BOOL32 ON_Surface::Split(
       int dir,
       double c,
       ON_Surface*& west_or_south_side,
       ON_Surface*& east_or_north_side
       ) const
{
  return false;
}


bool ON_Surface::GetClosestPoint( 
        const ON_3dPoint& P,
        double* s,
        double* t,
        double maximum_distance,
        const ON_Interval* sdomain,
        const ON_Interval* tdomain
        ) const
{
  bool rc = false;

#if defined(OPENNURBS_PLUS_INC_)
	const ON_SurfaceTree* tree = SurfaceTree();
	while ( tree && tree->m_root )
  {
    ON_3dPoint Q;
	  const ON_Interval* sdom = sdomain;
	  const ON_Interval* tdom = tdomain;
    ON_Interval tempdom[2];
    double u,v;
    const ON_SurfaceTreeNode* node;
    const bool bAdjustParameter = tree->m_root->AdjustParameter();

    if ( bAdjustParameter && (sdom || tdom) )
    {
      // change domains to the tree's parameterization
      tempdom[0] = sdomain ? *sdomain : Domain(0);
      tempdom[1] = tdomain ? *tdomain : Domain(1);
      if ( !GetNurbFormParameterFromSurfaceParameter(tempdom[0][0],tempdom[1][0],&tempdom[0].m_t[0],&tempdom[1].m_t[0]) )
        break;
      if ( !GetNurbFormParameterFromSurfaceParameter(tempdom[0][1],tempdom[1][1],&tempdom[0].m_t[1],&tempdom[1].m_t[1]) )
        break;
      if ( sdom )
        sdom = &tempdom[0];
      if ( tdom )
        tdom = &tempdom[1];
    }
  	
    // NOTE: ON_SurfaceTreeNode::ON_SurfaceTreeNode works in Rhino but not in free opennurbs.
	  node = tree->m_root->GetClosestPoint( P, s, t, &Q, maximum_distance, sdom, tdom );

    if ( !node )
      return false;

    if (bAdjustParameter)
    {
		  // change (*s,*t) to the surface's parameterization
      u = *s;
      v = *t;
      if ( !GetSurfaceParameterFromNurbFormParameter(u,v,s,t) )
        break;

      // With all the parameterization juggling, make sure conversion
      // is exact on the boundaries of any domain restrictions.
      if ( sdomain )
      {
        if ( u <= sdom->m_t[0] || u >= sdom->m_t[1] )
          *s = sdomain->m_t[(u <= sdom->m_t[0])?0:1];
        else if ( *s < sdomain->m_t[0] ) 
          *s = sdomain->m_t[0]; 
        else if (*s > sdomain->m_t[1]) 
          *s = sdomain->m_t[1];
      }

      if ( tdomain )
      {
        if ( v <= tdom->m_t[0] || v >= tdom->m_t[1] )
          *t = tdomain->m_t[(v <= tdom->m_t[0])?0:1];
		    else if ( *t < tdomain->m_t[0] )
          *t = tdomain->m_t[0]; 
        else if (*t > tdomain->m_t[1]) 
          *t = tdomain->m_t[1];
      }
    }

    rc = true;

    break;
  }

#endif

	return rc;
}

//virtual
ON_BOOL32 ON_Surface::GetLocalClosestPoint( const ON_3dPoint&, // test_point
        double,double,     // seed_parameters
        double*,double*,   // parameters of local closest point returned here
        const ON_Interval*, // first parameter sub_domain
        const ON_Interval*  // second parameter sub_domain
        ) const
{
  return false;
}

/*
static ON_Surface* ON_Surface_OffsetHelper( 
          const ON_Surface* base_surface,
          double offset_distance, 
          double tolerance, 
          double* max_deviation
          )
{
  // This returns NULL in for users of the free OpenNURBS toolkit
  // and works for Rhino plug-ins.
  ON_Surface* offset_srf = NULL;
  if ( base_surface->ClassId() != &ON_NurbsSurface::m_ON_NurbsSurface_class_id )
    offset_srf = base_surface->Offset( offset_distance, tolerance, max_deviation );
  return offset_srf;
}
*/

//virtual
ON_Surface* ON_Surface::Offset(
      double offset_distance, 
      double tolerance, 
      double* max_deviation
      ) const
{
  ON_Surface* offset_srf = NULL;
  if ( max_deviation )
    *max_deviation = 0.0;
  if ( !ON_NurbsSurface::Cast(this) )
  {
    // This works when openNURBS is used in Rhino
    const ON_Surface* proxy = NULL;
    ON_NurbsSurface ns;
    int rc = GetNurbForm( ns, 0.25*tolerance );
    if ( rc > 0 )
    {
      proxy = &ns;
      if ( rc >= 3 )
        tolerance *= 0.75; // ns locus is approximation
    }
    // MUST call Offset() via proxy pointer
    if ( proxy )
      offset_srf = proxy->Offset( offset_distance, tolerance, max_deviation );
  }
  return offset_srf;
}


// virtual
int ON_Surface::GetNurbForm(
      ON_NurbsSurface& nurbs_surface,
      double tolerance
      ) const
{
  return 0;
}

// virtual
int ON_Surface::HasNurbForm( ) const
{
  return 0;
}

bool ON_Surface::GetSurfaceParameterFromNurbFormParameter(
      double nurbs_s, double nurbs_t,
      double* surface_s, double* surface_t
      ) const
{
  // NOTE: ON_SumSurface and ON_RevSurface override this virtual function
  *surface_s = nurbs_s;
  *surface_t = nurbs_t;
  return true;
}

bool ON_Surface::GetNurbFormParameterFromSurfaceParameter(
      double surface_s, double surface_t,
      double* nurbs_s,  double* nurbs_t
      ) const
{
  // NOTE: ON_SumSurface and ON_RevSurface override this virtual function
  *nurbs_s = surface_s;
  *nurbs_t = surface_t;
  return true;
}


ON_NurbsSurface* ON_Surface::NurbsSurface(
      ON_NurbsSurface* pNurbsSurface,
      double tolerance,
      const ON_Interval* s_subdomain,
      const ON_Interval* t_subdomain
      ) const
{
  ON_NurbsSurface* nurbs_surface = pNurbsSurface;
  if ( !nurbs_surface )
    nurbs_surface = new ON_NurbsSurface();
  int rc = GetNurbForm( *nurbs_surface, tolerance );
  if ( !rc )
  {
    if (!pNurbsSurface)
      delete nurbs_surface;
    nurbs_surface = NULL;
  }
  return nurbs_surface;
}



ON_SurfaceArray::ON_SurfaceArray( int initial_capacity )
                   : ON_SimpleArray<ON_Surface*>(initial_capacity)
{}

ON_SurfaceArray::~ON_SurfaceArray()
{
  Destroy();
}

void ON_SurfaceArray::Destroy()
{
  int i = m_capacity;
  while ( i-- > 0 ) {
    if ( m_a[i] ) {
      delete m_a[i];
      m_a[i] = NULL;
    }
  }
  Empty();
}

ON_BOOL32 ON_SurfaceArray::Duplicate( ON_SurfaceArray& dst ) const
{
  dst.Destroy();
  dst.SetCapacity( Capacity() );

  const int count = Count();
  int i;
  ON_Surface* surface;
  for ( i = 0; i < count; i++ ) 
  {
    surface = 0;
    if ( m_a[i] ) 
    {
      surface = m_a[i]->Duplicate();
    }
    dst.Append(surface);      
  }
  return true;
}

ON_BOOL32 ON_SurfaceArray::Write( ON_BinaryArchive& file ) const
{
  ON_BOOL32 rc = file.BeginWrite3dmChunk( TCODE_ANONYMOUS_CHUNK, 0 );
  if (rc) rc = file.Write3dmChunkVersion(1,0);
  if (rc ) {
    int i;
    rc = file.WriteInt( Count() );
    for ( i = 0; rc && i < Count(); i++ ) {
      if ( m_a[i] ) {
        rc = file.WriteInt(1);
        if ( rc ) 
          rc = file.WriteObject( *m_a[i] ); // polymorphic surfaces
      }
      else {
        // NULL surface
        rc = file.WriteInt(0);
      }
    }
    if ( !file.EndWrite3dmChunk() )
      rc = false;
  }
  return rc;
}


ON_BOOL32 ON_SurfaceArray::Read( ON_BinaryArchive& file )
{
  int major_version = 0;
  int minor_version = 0;
  ON__UINT32 tcode = 0;
  ON__INT64 big_value = 0;
  int flag;
  Destroy();
  ON_BOOL32 rc = file.BeginRead3dmBigChunk( &tcode, &big_value );
  if (rc) 
  {
    rc = ( tcode == TCODE_ANONYMOUS_CHUNK );
    if (rc) rc = file.Read3dmChunkVersion(&major_version,&minor_version);
    if (rc && major_version == 1) {
      ON_Object* p;
      int count;
      ON_BOOL32 rc = file.ReadInt( &count );
      if (rc) {
        SetCapacity(count);
        SetCount(count);
        Zero();
        int i;
        for ( i = 0; rc && i < count && rc; i++ ) {
          flag = 0;
          rc = file.ReadInt(&flag);
          if (rc && flag==1) {
            p = 0;
            rc = file.ReadObject( &p ); // polymorphic surfaces
            m_a[i] = ON_Surface::Cast(p);
            if ( !m_a[i] )
              delete p;
          }
        }
      }
    }
    else {
      rc = false;
    }
    if ( !file.EndRead3dmChunk() )
      rc = false;
  }
  return rc;
}

ON_BOOL32 ON_Surface::HasBrepForm() const
{
  return true;
}

ON_Brep* ON_Surface::BrepForm( ON_Brep* brep ) const
{
  ON_Brep* pBrep = NULL;
  if ( brep )
    brep->Destroy();
  // 26 August 2008 Dale Lear - fixed bug
  //    When this function was called on an ON_SurfaceProxy
  //ON_Surface* pSurface = Duplicate();
  ON_Surface* pSurface = DuplicateSurface();
  if ( pSurface )
  {
    if ( brep )
      pBrep = brep;
    else
      pBrep = new ON_Brep();
    if ( !pBrep->Create(pSurface) )
    {
      if ( pSurface )
      {
        delete pSurface;
        pSurface = NULL;
      }
      if ( !brep )
        delete pBrep;
      pBrep = NULL;
    }
  }
  return pBrep;
}

void ON_Surface::DestroySurfaceTree()
{
  DestroyRuntimeCache(true);
}

const ON_SurfaceTree* ON_Surface::SurfaceTree() const
{
  if ( !m_stree ) 
  {
    const_cast<ON_Surface*>(this)->m_stree = CreateSurfaceTree();
  }
  return m_stree;
}



