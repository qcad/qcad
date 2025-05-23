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

////////////////////////////////////////////////////////////////
//
//   Definition of virtual parametric surface
//
////////////////////////////////////////////////////////////////

#if !defined(OPENNURBS_SURFACE_INC_)
#define OPENNURBS_SURFACE_INC_

class ON_Curve;
class ON_NurbsSurface;
class ON_SurfaceTree;

/* $Header: /src3/opennurbs/opennurbs_surface.h 3     9/17/01 4:21p Dalelear $ */
/* $NoKeywords: $ */
/*
//
// Copyright (c) 1993-2001 Robert McNeel & Associates. All rights reserved.
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

////////////////////////////////////////////////////////////////
//
//   Definition of virtual parametric surface
//
////////////////////////////////////////////////////////////////

class ON_Mesh;
class ON_MeshParameters;
class ON_PolyCurve;
class ON_CurveProxy;
class ON_Surface;

class ON_CLASS ON_Surface : public ON_Geometry
{
  ON_OBJECT_DECLARE(ON_Surface);

public:
  // virtual ON_Object::DestroyRuntimeCache override
  void DestroyRuntimeCache( bool bDelete = true );

  // pure virtual class for surface objects
public:

  // flags for isoparametric curves
  // note: odd values are all "x" = constant
  // and even values > 0 are all "y" = constant
  // ON_BrepTrim::m_iso uses these flags
  enum ISO 
  {
    not_iso = 0, // curve is not an isoparameteric curve
    x_iso   = 1, // curve is a "x" = constant (vertical) isoparametric
                 // curve in the interior of the surface's domain
    y_iso   = 2, // curve is a "y" = constant (horizontal) isoparametric
                 // curve in the interior of the surface's domain
    W_iso   = 3, // curve is a "x" = constant isoparametric curve
                 // along the west side of the surface's domain
    S_iso   = 4, // curve is a "y" = constant isoparametric curve
                 // along the south side of the surface's domain
    E_iso   = 5, // curve is a "x" = constant isoparametric curve
                 // along the east side of the surface's domain
    N_iso   = 6, // curve is a "y" = constant isoparametric curve
                 // along the north side of the surface's domain
    iso_count = 7
  };

public:
  ON_Surface();
  ON_Surface(const ON_Surface&);
  ON_Surface& operator=(const ON_Surface&);
  virtual ~ON_Surface();

  // virtual ON_Object::SizeOf override
  unsigned int SizeOf() const;

  // virtual ON_Geometry override
  bool EvaluatePoint( const class ON_ObjRef& objref, ON_3dPoint& P ) const;

  /*
  Description:
    Get a duplicate of the surface.
  Returns:
    A duplicate of the surface.  
  Remarks:
    The caller must delete the returned surface.
    For non-ON_SurfaceProxy objects, this simply duplicates the surface using
    ON_Object::Duplicate.
    For ON_SurfaceProxy objects, this duplicates the actual proxy surface 
    geometry and, if necessary, transposes the result to that
    the returned surfaces's parameterization and locus match the proxy surface's.
  */
  virtual
  ON_Surface* DuplicateSurface() const;

  //////////
  // override ON_Object::ObjectType() - returns ON::surface_object
  ON::object_type ObjectType() const;


  /////////////////////////////
  //
  // virtual ON_Geometry functions
  //

  /*
  Description:
    Overrides virtual ON_Geometry::HasBrepForm and returns true.
  Result:
    Returns true.
  See Also:
    ON_Brep::Create( ON_Surface&* )
  */
  ON_BOOL32 HasBrepForm() const;

  /*
  Description:
    Overrides virtual ON_Geometry::HasBrepForm.  
    Uses ON_Brep::Create( ON_Surface&* ) to create a brep
    form.  The surface is copied for use in the returned
    brep.
  Parameters:
    brep - [in] if not NULL, brep is used to store the brep
        form of the surface.
  Result:
    Returns a pointer to on ON_Brep or NULL.  If the brep
    parameter is not NULL, then brep is returned if the
    surface has a brep form and NULL is returned if the
    geometry does not have a brep form.
  Remarks:
    The caller is responsible for managing the brep memory.
  */
  ON_Brep* BrepForm( ON_Brep* brep = NULL ) const;

  ////////////////////////////////////////////////////////////////////
  // surface interface

  /*
  Description:
    Computes a polygon mesh approximation of the surface.    
  Parameters:
    mp - [in] meshing parameters
    mesh - [in] if not NULL, the surface mesh will be put
                into this mesh.
  Returns:
    A polygon mesh of the surface.
  Remarks:
    This virtual function works in the openNURBS that is
    part of the Rhino SDK.  The source code for this 
    functionallity is not provided in the free openNURBS
    toolkit.
  */
  virtual
  ON_Mesh* CreateMesh( 
             const ON_MeshParameters& mp,
             ON_Mesh* mesh = NULL
             ) const;

  ON_BOOL32 GetDomain( 
         int dir,              // 0 gets first parameter, 1 gets second parameter
         double* t0,
         double* t1
         ) const;

  bool SetDomain( 
    int dir, // 0 sets first parameter's domain, 1 gets second parameter's domain
    ON_Interval domain
    );

  virtual
  ON_BOOL32 SetDomain( 
    int dir, // 0 sets first parameter's domain, 1 gets second parameter's domain
    double t0, 
    double t1
    );

  virtual
  ON_Interval Domain(
    int dir // 0 gets first parameter's domain, 1 gets second parameter's domain
    ) const = 0;

  /*
  Description:
    Get an estimate of the size of the rectangle that would
    be created if the 3d surface where flattened into a rectangle.
  Parameters:
    width - [out]  (corresponds to the first surface parameter)
    height - [out] (corresponds to the first surface parameter)
  Example:

          // Reparameterize a surface to minimize distortion 
          // in the map from parameter space to 3d.
          ON_Surface* surf = ...;
          double width, height;
          if ( surf->GetSurfaceSize( &width, &height ) )
          {
            srf->SetDomain( 0, ON_Interval( 0.0, width ) );
            srf->SetDomain( 1, ON_Interval( 0.0, height ) );
          }

  Returns:
    true if successful.
  */
  virtual
  ON_BOOL32 GetSurfaceSize( 
      double* width, 
      double* height 
      ) const;


  virtual 
  int SpanCount(
    int dir // 0 gets first parameter's domain, 1 gets second parameter's domain
    ) const = 0; // number of smooth nonempty spans in the parameter direction

  virtual
  ON_BOOL32 GetSpanVector( // span "knots" 
        int dir, // 0 gets first parameter's domain, 1 gets second parameter's domain
        double* span_vector // array of length SpanCount() + 1 
        ) const = 0; // 

  //////////
  // If t is in the domain of the surface, GetSpanVectorIndex() returns the 
  // span vector index "i" such that span_vector[i] <= t <= span_vector[i+1].
  // The "side" parameter determines which span is selected when t is at the
  // end of a span.
  virtual
  ON_BOOL32 GetSpanVectorIndex(
        int dir , // 0 gets first parameter's domain, 1 gets second parameter's domain
        double t,      // [IN] t = evaluation parameter
        int side,         // [IN] side 0 = default, -1 = from below, +1 = from above
        int* span_vector_index,        // [OUT] span vector index
        ON_Interval* span_interval // [OUT] domain of the span containing "t"
        ) const;

  virtual 
  int Degree( // returns maximum algebraic degree of any span 
                  // ( or a good estimate if curve spans are not algebraic )
    int dir // 0 gets first parameter's domain, 1 gets second parameter's domain
    ) const = 0; 

  virtual ON_BOOL32 GetParameterTolerance( // returns tminus < tplus: parameters tminus <= s <= tplus
         int dir,        // 0 gets first parameter, 1 gets second parameter
         double t,       // t = parameter in domain
         double* tminus, // tminus
         double* tplus   // tplus
         ) const;

  /*
  Description:
    Test a 2d curve to see if it is iso parameteric in the surface's
    parameter space.
  Parameters:
    curve - [in] curve to test
    curve_domain = [in] optional sub domain of the curve
  Returns:
    Isoparametric status of the curve.
  Remarks:
    Because it may transpose domains, ON_SurfaceProxy overrides
    this function.  All other surface classes just use
    the base class implementation.
  */
  virtual
  ISO IsIsoparametric(
        const ON_Curve& curve,
        const ON_Interval* curve_domain = NULL
        ) const;

  /*
  Description:
    Test a 2d bounding box to see if it is iso parameteric in the surface's
    parameter space.
  Parameters:
    bbox - [in] bounding box to test
  Returns:
    Isoparametric status of the bounding box.
  Remarks:
    Because it may transpose domains, ON_SurfaceProxy overrides
    this function.  All other surface classes just use
    the base class implementation.
  */
  virtual
  ISO IsIsoparametric(
        const ON_BoundingBox& bbox
        ) const;

  /*
  Description:
    Test a surface to see if it is planar.
  Parameters:
    plane - [out] if not NULL and true is returned,
                  the plane parameters are filled in.
    tolerance - [in] tolerance to use when checking
  Returns:
    true if there is a plane such that the maximum distance from
    the surface to the plane is <= tolerance.
  */
  virtual
  ON_BOOL32 IsPlanar(
        ON_Plane* plane = NULL,
        double tolerance = ON_ZERO_TOLERANCE
        ) const;

  /*
  Description:
    Determine if the surface is a portion of a sphere.
  Parameters:
    sphere - [out] if not NULL and true is returned,
      then the sphere definition is returned.
    tolerance - [in]
      tolerance to use when checking
  Returns:
    True if the surface is a portion of a sphere.                   
  */
  bool IsSphere(
        ON_Sphere* sphere = NULL,
        double tolerance = ON_ZERO_TOLERANCE
        ) const;

  /*
  Description:
    Determine if the surface is a portion of a cylinder.
  Parameters:
    cylinder - [out] if not NULL and true is returned, 
      then the cylinder definition is returned.
    tolerance - [in]
      tolerance to use when checking
  Returns:
    True if the surface is a portion of a cylinder.                   
  */
  bool IsCylinder(
        ON_Cylinder* cylinder = NULL,
        double tolerance = ON_ZERO_TOLERANCE
        ) const;

  /*
  Description:
    Determine if the surface is a portion of a cone.
  Parameters:
    cone - [out] if not NULL and true is returned, 
      then the cone definition is returned.
    tolerance - [in]
      tolerance to use when checking
  Returns:
    True if the surface is a portion of a cone.                   
  */
  bool IsCone(
        ON_Cone* cone = NULL,
        double tolerance = ON_ZERO_TOLERANCE
        ) const;

  /*
  Description:
    Determine if the surface is a portion of a torus.
  Parameters:
    torus - [out] if not NULL and true is returned,
      then the torus definition is returned.
    tolerance - [in]
      tolerance to use when checking
  Returns:
    True if the surface is a portion of a torus.                   
  */
  bool IsTorus(
        ON_Torus* torus = NULL,
        double tolerance = ON_ZERO_TOLERANCE
        ) const;

  virtual 
  ON_BOOL32 IsClosed(   // true if surface is closed in direction
        int        // dir  0 = "s", 1 = "t"
        ) const;

  virtual 
  ON_BOOL32 IsPeriodic( // true if surface is periodic in direction (default is false)
        int        // dir  0 = "s", 1 = "t"
        ) const;

  virtual
  ON_BOOL32 IsSingular( // true if surface side is collapsed to a point
        int        // side of parameter space to test
                   // 0 = south, 1 = east, 2 = north, 3 = west
        ) const;

  /*
  Returns:
    True if the surface defines a solid, like a sphere or torus.
    False if the surface does not define a solid, like a plane or cone.
  */
  bool IsSolid() const;

  /*
  Description:
    Test if a surface parameter value is at a singularity.
  Parameters:
    s - [in] surface parameter to test
    t - [in] surface parameter to test
    bExact - [in] if true, test if s,t is exactly at a singularity
      if false, test if close enough to cause numerical problems.
  Returns:
    true if surface is singular at (s,t)
  */
  bool IsAtSingularity(
    double s, 
    double t, 
    bool bExact = true
    ) const;

  /*
  Description:
    Test if a surface parameter value is at a seam.
  Parameters:
    s - [in] surface parameter to test
    t - [in] surface parameter to test
  Returns:
    0 if not a seam,
    1 if s == Domain(0)[i] and srf(s, t) == srf(Domain(0)[1-i], t)
    2 if t == Domain(1)[i] and srf(s, t) == srf(s, Domain(1)[1-i])
    3 if 1 and 2 are true.
  */
  int IsAtSeam(
    double s,
    double t
    ) const;
  
  /*
  Description:
    Search for a derivatitive, tangent, or curvature 
    discontinuity.
  Parameters:
    dir - [in] If 0, then "u" parameter is checked.  If 1, then
               the "v" parameter is checked.
    c - [in] type of continity to test for.
    t0 - [in] Search begins at t0. If there is a discontinuity
              at t0, it will be ignored.  This makes it 
              possible to repeatedly call GetNextDiscontinuity
              and step through the discontinuities.
    t1 - [in] (t0 != t1)  If there is a discontinuity at t1 is 
              will be ingored unless c is a locus discontinuity
              type and t1 is at the start or end of the curve.
    t - [out] if a discontinuity is found, then *t reports the
          parameter at the discontinuity.
    hint - [in/out] if GetNextDiscontinuity will be called 
       repeatedly, passing a "hint" with initial value *hint=0
       will increase the speed of the search.       
    dtype - [out] if not NULL, *dtype reports the kind of 
        discontinuity found at *t.  A value of 1 means the first 
        derivative or unit tangent was discontinuous.  A value 
        of 2 means the second derivative or curvature was 
        discontinuous.  A value of 0 means teh curve is not
        closed, a locus discontinuity test was applied, and
        t1 is at the start of end of the curve.
    cos_angle_tolerance - [in] default = cos(1 degree) Used only
        when c is ON::G1_continuous or ON::G2_continuous.  If the
        cosine of the angle between two tangent vectors is 
        <= cos_angle_tolerance, then a G1 discontinuity is reported.
    curvature_tolerance - [in] (default = ON_SQRT_EPSILON) Used 
        only when c is ON::G2_continuous.  If K0 and K1 are 
        curvatures evaluated from above and below and 
        |K0 - K1| > curvature_tolerance, then a curvature 
        discontinuity is reported.
  Returns:
    Parametric continuity tests c = (C0_continuous, ..., G2_continuous):

      true if a parametric discontinuity was found strictly 
      between t0 and t1. Note well that all curves are 
      parametrically continuous at the ends of their domains.

    Locus continuity tests c = (C0_locus_continuous, ...,G2_locus_continuous):

      true if a locus discontinuity was found strictly between
      t0 and t1 or at t1 is the at the end of a curve.
      Note well that all open curves (IsClosed()=false) are locus
      discontinuous at the ends of their domains.  All closed 
      curves (IsClosed()=true) are at least C0_locus_continuous at 
      the ends of their domains.
  */
  virtual
  bool GetNextDiscontinuity( 
                  int dir,
                  ON::continuity c,
                  double t0,
                  double t1,
                  double* t,
                  int* hint=NULL,
                  int* dtype=NULL,
                  double cos_angle_tolerance=0.99984769515639123915701155881391,
                  double curvature_tolerance=ON_SQRT_EPSILON
                  ) const;

  /*
  Description:
    Test continuity at a surface parameter value.
  Parameters:
    c - [in] continuity to test for
    s - [in] surface parameter to test
    t - [in] surface parameter to test
    hint - [in] evaluation hint
    point_tolerance - [in] if the distance between two points is
        greater than point_tolerance, then the surface is not C0.
    d1_tolerance - [in] if the difference between two first derivatives is
        greater than d1_tolerance, then the surface is not C1.
    d2_tolerance - [in] if the difference between two second derivatives is
        greater than d2_tolerance, then the surface is not C2.
    cos_angle_tolerance - [in] default = cos(1 degree) Used only when
        c is ON::G1_continuous or ON::G2_continuous.  If the cosine
        of the angle between two normal vectors 
        is <= cos_angle_tolerance, then a G1 discontinuity is reported.
    curvature_tolerance - [in] (default = ON_SQRT_EPSILON) Used only when
        c is ON::G2_continuous.  If K0 and K1 are curvatures evaluated
        from above and below and |K0 - K1| > curvature_tolerance,
        then a curvature discontinuity is reported.
  Returns:
    true if the surface has at least the c type continuity at the parameter t.
  */
  virtual
  bool IsContinuous(
    ON::continuity c,
    double s, 
    double t, 
    int* hint = NULL,
    double point_tolerance=ON_ZERO_TOLERANCE,
    double d1_tolerance=ON_ZERO_TOLERANCE,
    double d2_tolerance=ON_ZERO_TOLERANCE,
    double cos_angle_tolerance=0.99984769515639123915701155881391,
    double curvature_tolerance=ON_SQRT_EPSILON
    ) const;

  virtual 
  ON_BOOL32 Reverse(  // reverse parameterizatrion, Domain changes from [a,b] to [-b,-a]
    int // dir  0 = "s", 1 = "t"
    ) = 0;

  virtual 
  ON_BOOL32 Transpose() = 0; // transpose surface parameterization (swap "s" and "t")

  // simple evaluation interface - no error handling
  ON_3dPoint  PointAt( double, double ) const;
  ON_3dVector NormalAt( double, double ) const;
  ON_BOOL32 FrameAt( double u, double v, ON_Plane& frame) const;

  ON_BOOL32 EvPoint( // returns false if unable to evaluate
         double u, double v,   // evaluation parameters
         ON_3dPoint& point,    // returns value of surface
         int quadrant = 0,     // optional - determines which side to evaluate from
                               //         0 = default
                               //         1 from NE quadrant
                               //         2 from NW quadrant
                               //         3 from SW quadrant
                               //         4 from SE quadrant
         int* hint = 0         // optional - evaluation hint (int[2]) used to speed
                               //            repeated evaluations
         ) const;

  ON_BOOL32 Ev1Der( // returns false if unable to evaluate
         double u, double v,   // evaluation parameters (s,t)
         ON_3dPoint& point,    // returns value of surface
         ON_3dVector& du,      // first partial derivatives (Ds)
         ON_3dVector& dv,      // (Dt)
         int quadrant = 0,     // optional - determines which side to evaluate from
                               //         0 = default
                               //         1 from NE quadrant
                               //         2 from NW quadrant
                               //         3 from SW quadrant
                               //         4 from SE quadrant
         int* hint = 0         // optional - evaluation hint (int[2]) used to speed
                               //            repeated evaluations
         ) const;

  ON_BOOL32 Ev2Der( // returns false if unable to evaluate
         double u, double v,   // evaluation parameters (s,t)
         ON_3dPoint& point,    // returns value of surface
         ON_3dVector& du,      // first partial derivatives (Ds)
         ON_3dVector& dv,      // (Dt)
         ON_3dVector& duu,     // second partial derivatives (Dss)
         ON_3dVector& duv,     // (Dst)
         ON_3dVector& dvv,     // (Dtt)
         int quadrant= 0,      // optional - determines which side to evaluate from
                               //         0 = default
                               //         1 from NE quadrant
                               //         2 from NW quadrant
                               //         3 from SW quadrant
                               //         4 from SE quadrant
         int* hint = 0         // optional - evaluation hint (int[2]) used to speed
                               //            repeated evaluations
         ) const;

  ON_BOOL32 EvNormal( // returns false if unable to evaluate
         double u, double v,   // evaluation parameters (s,t)
         ON_3dPoint& point,    // returns value of surface
         ON_3dVector& normal,  // unit normal
         int quadrant = 0,     // optional - determines which side to evaluate from
                               //         0 = default
                               //         1 from NE quadrant
                               //         2 from NW quadrant
                               //         3 from SW quadrant
                               //         4 from SE quadrant
         int* hint = 0         // optional - evaluation hint (int[2]) used to speed
                               //            repeated evaluations
         ) const;

  ON_BOOL32 EvNormal( // returns false if unable to evaluate
         double u, double v,   // evaluation parameters (s,t)
         ON_3dVector& normal,  // unit normal
         int quadrant = 0,     // optional - determines which side to evaluate from
                               //         0 = default
                               //         1 from NE quadrant
                               //         2 from NW quadrant
                               //         3 from SW quadrant
                               //         4 from SE quadrant
         int* hint = 0         // optional - evaluation hint (int[2]) used to speed
                               //            repeated evaluations
         ) const;

  ON_BOOL32 EvNormal( // returns false if unable to evaluate
         double u, double v,   // evaluation parameters (s,t)
         ON_3dPoint& point,    // returns value of surface
         ON_3dVector& du,      // first partial derivatives (Ds)
         ON_3dVector& dv,      // (Dt)
         ON_3dVector& normal,  // unit normal
         int = 0,              // optional - determines which side to evaluate from
                               //         0 = default
                               //         1 from NE quadrant
                               //         2 from NW quadrant
                               //         3 from SW quadrant
                               //         4 from SE quadrant
         int* = 0              // optional - evaluation hint (int[2]) used to speed
                               //            repeated evaluations
         ) const;

  // work horse evaluator
  virtual 
  ON_BOOL32 Evaluate( // returns false if unable to evaluate
         double u, double v,   // evaluation parameters
         int num_der,          // number of derivatives (>=0)
         int array_stride,     // array stride (>=Dimension())
         double* der_array,    // array of length stride*(ndir+1)*(ndir+2)/2
         int quadrant = 0,     // optional - determines which quadrant to evaluate from
                               //         0 = default
                               //         1 from NE quadrant
                               //         2 from NW quadrant
                               //         3 from SW quadrant
                               //         4 from SE quadrant
         int* hint = 0         // optional - evaluation hint (int[2]) used to speed
                               //            repeated evaluations
         ) const = 0;

  /*
  Description:
    Get isoparametric curve.
  Parameters:
    dir - [in] 0 first parameter varies and second parameter is constant
                 e.g., point on IsoCurve(0,c) at t is srf(t,c)
                 This is a horizontal line from left to right
               1 first parameter is constant and second parameter varies
                 e.g., point on IsoCurve(1,c) at t is srf(c,t
                 This is a vertical line from bottom to top

    c - [in] value of constant parameter 
  Returns:
    Isoparametric curve.
  Remarks:
    In this function "dir" indicates which direction the resulting
    curve runs.  0: horizontal, 1: vertical
    In the other ON_Surface functions that take a "dir"
    argument, "dir" indicates if "c" is a "u" or "v" parameter.
  */
  virtual
  ON_Curve* IsoCurve(
         int dir,
         double c
         ) const;

  /*
  Description:
    Compute a 3d curve that is the composite of a 2d curve
    and the surface map.
  Parameters:
    curve_2d - [in] a 2d curve whose image is in the surface's domain.
    tolerance - [in] the maximum acceptable distance from the returned
       3d curve to the image of curve_2d on the surface.
    curve_2d_subdomain - [in] optional subdomain for curve_2d
  Returns:
    3d curve.
  See Also:
    ON_Surface::IsoCurve
    ON_Surface::Pullback
  */
  virtual
  ON_Curve* Pushup( const ON_Curve& curve_2d,
                    double tolerance,
                    const ON_Interval* curve_2d_subdomain = NULL
                    ) const;

  /*
  Description:
    Pull a 3d curve back to the surface's parameter space.
  Parameters:
    curve_3d - [in] a 3d curve
    tolerance - [in] the maximum acceptable 3d distance between
       from surface(curve_2d(t)) to the locus of points on the
       surface that are closest to curve_3d.
    curve_3d_subdomain - [in] optional subdomain for curve_3d
    start_uv - [in] optional starting point (if known)
    end_uv - [in] optional ending point (if known)
  Returns:
    2d curve.
  See Also:
    ON_Surface::IsoCurve
    ON_Surface::Pushup
  */
  virtual
  ON_Curve* Pullback( const ON_Curve& curve_3d,
                    double tolerance,
                    const ON_Interval* curve_3d_subdomain = NULL,
                    ON_3dPoint start_uv = ON_UNSET_POINT,
                    ON_3dPoint end_uv = ON_UNSET_POINT
                    ) const;

  /*
  Description:
    Removes the portions of the surface outside of the specified interval.

  Parameters:
    dir - [in] 0  The domain specifies an sub-interval of Domain(0)
                  (the first surface parameter).
               1  The domain specifies an sub-interval of Domain(1)
                  (the second surface parameter).
    domain - [in] interval of the surface to keep. If dir is 0, then
        the portions of the surface with parameters (s,t) satisfying
        s < Domain(0).Min() or s > Domain(0).Max() are trimmed away.
        If dir is 1, then the portions of the surface with parameters
        (s,t) satisfying t < Domain(1).Min() or t > Domain(1).Max() 
        are trimmed away.
  */
  virtual
  ON_BOOL32 Trim(
         int dir,
         const ON_Interval& domain
         );

  /*
   Description:
     Pure virtual function. Default returns false.
     Where possible, analytically extends surface to include domain.
   Parameters:
     dir - [in] 0  new Domain(0) will include domain.
                   (the first surface parameter).
                1  new Domain(1) will include domain.
                   (the second surface parameter).
     domain - [in] if domain is not included in surface domain, 
     surface will be extended so that its domain includes domain.  
     Will not work if surface is closed in direction dir. 
     Original surface is identical to the restriction of the
     resulting surface to the original surface domain, 
   Returns:
     true if successful.
     */
  virtual
  bool Extend(
    int dir,
    const ON_Interval& domain
    );


  /*
  Description:
    Splits (divides) the surface into two parts at the 
    specified parameter.

  Parameters:
    dir - [in] 0  The surface is split vertically.  The "west" side
                  is returned in "west_or_south_side" and the "east"
                  side is returned in "east_or_north_side".
               1  The surface is split horizontally.  The "south" side
                  is returned in "west_or_south_side" and the "north"
                  side is returned in "east_or_north_side".
    c - [in] value of constant parameter in interval returned
               by Domain(dir)
    west_or_south_side - [out] west/south portion of surface returned here
    east_or_north_side - [out] east/north portion of surface returned here

  Example:

          ON_NurbsSurface srf = ...;
          int dir = 1;
          ON_NurbsSurface* south_side = 0;
          ON_NurbsSurface* north_side = 0;
          srf.Split( dir, srf.Domain(dir).Mid() south_side, north_side );

  */
  virtual
  ON_BOOL32 Split(
         int dir,
         double c,
         ON_Surface*& west_or_south_side,
         ON_Surface*& east_or_north_side
         ) const;

  /*
  Description:
    Get the parameters of the point on the surface that is closest to P.
  Parameters:
    P - [in] 
            test point
    s - [out]
    t - [out] 
            (*s,*t) = parameters of the surface point that 
            is closest to P.
    maximum_distance = 0.0 - [in] 
            optional upper bound on the distance from P to 
            the surface.  If you are only interested in 
            finding a point Q on the surface when 
            P.DistanceTo(Q) < maximum_distance, then set
            maximum_distance to that value.
    sdomain = 0 - [in] optional domain restriction
    tdomain = 0 - [in] optional domain restriction
  Returns:
    True if successful.  If false, the values of *s and *t
    are undefined.
  See Also:
    ON_Surface::GetLocalClosestPoint.
  */
  virtual
  bool GetClosestPoint( 
          const ON_3dPoint& P,
          double* s,
          double* t,
          double maximum_distance = 0.0,
          const ON_Interval* sdomain = 0,
          const ON_Interval* tdomain = 0
          ) const;

  //////////
  // Find parameters of the point on a surface that is locally closest to 
  // the test_point.  The search for a local close point starts at 
  // seed parameters. If a sub_domain parameter is not NULL, then
  // the search is restricted to the specified portion of the surface.
  //
  // true if returned if the search is successful.  false is returned if
  // the search fails.
  virtual
  ON_BOOL32 GetLocalClosestPoint( const ON_3dPoint&, // test_point
          double,double,     // seed_parameters
          double*,double*,   // parameters of local closest point returned here
          const ON_Interval* = NULL, // first parameter sub_domain
          const ON_Interval* = NULL  // second parameter sub_domain
          ) const;


  /*
  Description:
    Offset surface.
  Parameters:
    offset_distance - [in] offset distance
    tolerance - [in] Some surfaces do not have an exact offset that
      can be represented using the same class of surface definition.
      In that case, the tolerance specifies the desired accuracy.
    max_deviation - [out] If this parameter is not NULL, the maximum
      deviation from the returned offset to the true offset is returned
      here.  This deviation is zero except for cases where an exact
      offset cannot be computed using the same class of surface definition.
  Returns:
    Offset surface.
  */
  virtual
  ON_Surface* Offset(
        double offset_distance, 
        double tolerance, 
        double* max_deviation = NULL
        ) const;


  /*
  Description:
    Get a NURBS surface representation of this surface.
  Parameters:
    nurbs_surface - [out] NURBS representation returned here
    tolerance - [in] tolerance to use when creating NURBS
        representation.
    s_subdomain - [in] if not NULL, then the NURBS representation
        for this portion of the surface is returned.
    t_subdomain - [in] if not NULL, then the NURBS representation
        for this portion of the surface is returned.
  Returns:
    0   unable to create NURBS representation
        with desired accuracy.
    1   success - returned NURBS parameterization
        matches the surface's to wthe desired accuracy
    2   success - returned NURBS point locus matches
        the surface's to the desired accuracy and the
        domain of the NURBS surface is correct.  On
        However, This surface's parameterization and
        the NURBS surface parameterization may not 
        match to the desired accuracy.  This situation
        happens when getting NURBS representations of
        surfaces that have a transendental parameterization
        like spheres, cylinders, and cones.
  Remarks:
    This is a low-level virtual function.  If you do not need
    the parameterization information provided by the return code,
    then ON_Surface::NurbsSurface may be easier to use.
  See Also:
    ON_Surface::NurbsSurface
  */
  virtual
  int GetNurbForm(
        ON_NurbsSurface& nurbs_surface,
        double tolerance = 0.0
        ) const;


  /*
  Description:
    Is there a NURBS surface representation of this surface.
  Parameters:
  Returns:
    0   unable to create NURBS representation
        with desired accuracy.
    1   success - NURBS parameterization
        matches the surface's
    2   success - NURBS point locus matches
        the surface's and the
        domain of the NURBS surface is correct.  
        However, This surface's parameterization and
        the NURBS surface parameterization may not 
        match.  This situation
        happens when getting NURBS representations of
        surfaces that have a transendental parameterization
        like spheres, cylinders, and cones.
  Remarks:
    This is a low-level virtual function. 
  See Also:
    ON_Surface::GetNurbForm
    ON_Surface::NurbsSurface
  */
  virtual
  int HasNurbForm() const;

  // Description:
  //   Get a NURBS surface representation of this surface.
  // Parameters:
  //   pNurbsSurface - [in/out] if not NULL, this pNurbsSurface
  //   will be used to store the NURBS representation
  //   of the surface and will be returned.
  //   tolerance - [in] tolerance to use when creating NURBS
  //       surface representation.
  //   s_subdomain - [in] if not NULL, then the NURBS representation
  //       for this portion of the surface is returned.
  //   t_subdomain - [in] if not NULL, then the NURBS representation
  //       for this portion of the surface is returned.
  // Returns:
  //   NULL or a NURBS representation of the surface.
  // Remarks:
  //   See ON_Surface::GetNurbForm for important details about
  //   the NURBS surface parameterization.
  // See Also:
  //   ON_Surface::GetNurbForm
  ON_NurbsSurface* NurbsSurface(
        ON_NurbsSurface* pNurbsSurface = NULL,
        double tolerance = 0.0,
        const ON_Interval* s_subdomain = NULL,
        const ON_Interval* t_subdomain = NULL
        ) const;

  virtual
  bool GetSurfaceParameterFromNurbFormParameter(
        double nurbs_s, double nurbs_t,
        double* surface_s, double* surface_t
        ) const;

  virtual
  bool GetNurbFormParameterFromSurfaceParameter(
        double surface_s, double surface_t,
        double* nurbs_s,  double* nurbs_t
        ) const;


  // If the geometry surface is modified in any way, then
  // call DestroySurfaceTree().
  void DestroySurfaceTree();

  const ON_SurfaceTree* SurfaceTree() const;

  virtual
  ON_SurfaceTree* CreateSurfaceTree() const;

  /*
  Description:
    Calculate area mass properties of the surface.
  Parameters:
    mp - [out] 
    bArea - [in] true to calculate area
    bFirstMoments - [in] true to calculate area first moments,
                         area and area centroid.
    bSecondMoments - [in] true to calculate area second moments.
    bProductMoments - [in] true to calculate area product moments.
  Returns:
    True if successful.
  */
  bool AreaMassProperties(
    ON_MassProperties& mp,
    bool bArea = true,
    bool bFirstMoments = true,
    bool bSecondMoments = true,
    bool bProductMoments = true,
    double rel_tol = 1.0e-6,
    double abs_tol = 1.0e-6
    ) const;

  /*
  Description:
    Calculate volume mass properties of the surface.
  Parameters:
    mp - [out] 
    bVolume - [in] true to calculate volume
    bFirstMoments - [in] true to calculate volume first moments,
                         volume, and volume centroid.
    bSecondMoments - [in] true to calculate volume second moments.
    bProductMoments - [in] true to calculate volume product moments.
    base_point - [in] 
      If the surface is closed, then pass ON_UNSET_VALUE.

      This parameter is for expert users who are computing a
      volume whose boundary is defined by several non-closed
      breps, surfaces, and meshes.

      When computing the volume, volume centroid, or volume
      first moments of a volume whose boundary is defined by 
      several breps, surfaces, and meshes, pass the same 
      base_point to each call to VolumeMassProperties.  

      When computing the volume second moments or volume product
      moments of a volume whose boundary is defined by several
      breps, surfaces, and meshes, you MUST pass the entire 
      volume's centroid as the base_point and the input mp 
      parameter must contain the results of a previous call
      to VolumeMassProperties(mp,true,true,false,false,base_point).
      In particular, in this case, you need to make two sets of
      calls; use first set to calculate the volume centroid and
      the second set calculate the second moments and product 
      moments.
  Returns:
    True if successful.
  */
  bool VolumeMassProperties(
    ON_MassProperties& mp, 
    bool bVolume = true,
    bool bFirstMoments = true,
    bool bSecondMoments = true,
    bool bProductMoments = true,
    ON_3dPoint base_point = ON_UNSET_POINT,
    double rel_tol = 1.0e-6,
    double abs_tol = 1.0e-6
    ) const;

  /*
  Description:
    Intersect this surface with surfaceB.

  Parameters:
    surfaceB - [in]

    x - [out]
      Intersection events are appended to this array.

    intersection_tolerance - [in]
      If the input intersection_tolerance <= 0.0, then 0.001 is used.

    overlap_tolerance - [in]
      If positive, then overlap_tolerance must be 
      >= intersection_tolerance and is used to test for 
      overlapping regions. If the input 
      overlap_tolerance <= 0.0, then 2*intersection_tolerance 
      is used.

    fitting_tolerance - [in] 
      If fitting_tolerance is > 0 and >= intersection_tolerance,
      then the intersection curves are fit to this tolerance.
      If input fitting_tolerance <= 0.0 or < intersection_tolerance,
      then intersection_tolerance is used.

    surfaceA_udomain - [in]
      optional restriction on surfaceA u domain
    surfaceA_vdomain - [in] 
      optional restriction on surfaceA v domain

    surfaceB_udomain - [in]
      optional restriction on surfaceB u domain
    surfaceB_vdomain - [in] 
      optional restriction on surfaceB v domain
  Returns:
    Number of intersection events appended to x.
  */
  int IntersectSurface( 
          const ON_Surface* surfaceB,
          ON_ClassArray<ON_SSX_EVENT>& x,
          double intersection_tolerance = 0.0,
          double overlap_tolerance = 0.0,
          double fitting_tolerance = 0.0,
          const ON_Interval* surfaceA_udomain = 0,
          const ON_Interval* surfaceA_vdomain = 0,
          const ON_Interval* surfaceB_udomain = 0,
          const ON_Interval* surfaceB_vdomain = 0
          ) const;

  /*
  Description:
    Create a cubic nurbs surface that interpolates a list of curves.    

  Parameters:
    curve_count - [in]  >= 2 
      number of curves

    curve_list - [in]
      array of pointers to curves.  These curves define
      the location of the The returned surface's "v" parameter

    k - [in] (0.0 <= k) or k = ON_UNSET_VALUE
      k determines how the surface's m_knot[0] values
      are calculated. Most frequently, 0.0, 0.5, or 1.0 should be used.
        0.0: uniform
        0.5: sqrt(chord length)
        1.0: chord length
          In general, when k >= 0.0, then spacing is pow(d,k), where d is the
          average distance between the curves defining the span.
        ON_UNSET_VALUE: the intepolation knot vector is explicity specified.
          The knots in the interpolated direction are specified.  You must
          understand the mathematics of NURBS surfaces to use this option.
          To specify an explicit knot vector for the interpolation, the 
          nurbs_suface parameter must be non-null, and nurbs_surface->m_knot[0]
          must be an array of length 4+curve_count, and
          (nurbs_surface->m_knot[0][2], ..., nurbs_surface->m_knot[0][curve_count+1])
          must be a strictly increasing list of values.

    is_closed - [in]
      0: open
      1: closed
      2: periodic

    start_shape - [in]
    end_shape - [in]
      The start_shape and end_shape paramters determine the
      starting and ending shape of the lofted surface.
      Simple shapes:
        The simple end conditions calculate the rows of free
        control points based on the locations of the input
        curves and do not require additional input information.
          ON::cubic_loft_ec_quadratic: quadratic
          ON::cubic_loft_ec_linear: linear
          ON::cubic_loft_ec_cubic: cubic
          ON::cubic_loft_ec_natural: natrual (zero 2nd derivative)
      Explicit shapes:
        In order to specify explicit end conditions, curve_count must
        be at least 3, is_closed must be 0 or 1, the nurbs_surface
        parameter must be non-null, the nurbs_surface control
        points must be allocated, nurbs_surface->m_cv_count[0]
        must be curve_count+2, and the input curves must have nurbs
        curve formats with the same number of control points as 
        nurbs_surface->m_cv_count[1]. The values of the starting 
        shape points are specified in nurbs_surface->CV(1,...) and
        the values of ending shape points are specified in 
        nurbs_surface->CV(curve_count,...).
        N = curve_count
          ON::cubic_loft_ec_unit_tangent: unit tangent is specified
          ON::cubic_loft_ec_1st_derivative: first derivative is specified
          ON::cubic_loft_ec_2nd_derivative: second derivative is specified
          ON::cubic_loft_ec_free_cv: free control vertex is specified

    nurbs_surface - [in]
      If not null, the result will returned in this ON_NurbsSurface.
      Typically, this paramter is used when you want to store the
      result in an ON_NurbsSurface that is on the stack.  This
      paramter is also used when you want to specify the interpolation
      knots or end conditions.

  Returns:
    If successful, a pointer to the surface is returned. If the input
    nurbs_surface parameter was null, then this surface is on the heap
    and will need to be deleted to avoid memory leaks.  If the input
    is not valid, null is returned, even when nurbs_surface is not
    null.

  Example:
    
    // EXAMPLE 1: Loft a surface through a list of curves
      ON_SimpleArray< const ON_Curve* > curve_list = ....;
      ON_NurbsSurface* srf = ON_Surface::CreateCubicLoft(
                     curve_list.Count(),
                     curve_list,
                     0.5 // sqrt(chord length) spacing
                     );
    
    // EXAMPLE 2: Create adjacent surfaces with an identical shared edge.
      // First make two curve lists with 
      // curve_listA.Count() == curve_listB.Count() and
      // curve_listA[i]->PointAtEnd() == curve_listB[i]->PointAtStart()
      ON_SimpleArray< const ON_Curve* > curve_listA = ....;
      ON_SimpleArray< const ON_Curve* > curve_listB = ....;
      curve_count = curve_listA.Count(); 
      ON_NurbsSurface* srfA = 0;
      ON_NurbsSurface* srfB = 0;
      if ( curve_count == curve_listB.Count() )
      {
        srfA = ON_Surface::CreateCubicLoft(
                       curve_count,
                       curve_listA.Array(),
                       1.0 // chord length spacing
                       );
        if (0 != srfA)
        {
          srfB = new ON_NurbsSurface();
          int knot_count0 = srfA->KnotCount(0);
          srfB->ReserveKnotCapacity(0,knot_count0);
          memcpy(srfB->m_knot[0],srfA->m_knot[0],knot_count0*sizeof(srfB->m_knot[0][0]))
          if ( 0 == ON_Surface::CreateCubicLoft(
                         curve_count,
                         curve_listB.Array(),
                         ON_UNSET_VALUE, // knots specified in srfB->m_knot[0]
                         0, // open loft
                         ON::cubic_loft_ec_quadratic,
                         ON::cubic_loft_ec_quadratic,
                         srfB
                         ) )
         {
           // clean up to prevent memory leaks
           delete srfB;
           srfB = 0;
         }
       }
     }
  */
  static 
  class ON_NurbsSurface* CreateCubicLoft(
    int curve_count,
    const ON_Curve* const* curve_list,
    double k,
    int is_closed = 0,
    ON::cubic_loft_end_condition start_shape = ON::cubic_loft_ec_quadratic,
    ON::cubic_loft_end_condition end_shape   = ON::cubic_loft_ec_quadratic,
    class ON_NurbsSurface* nurbs_surface = 0
    );

protected:
  // Runtime only - ignored by Read()/Write()
  ON_SurfaceTree* m_stree;

protected:
  // Helper for ON_Surface::Pullback overrides that does a segment-by-segment
  // pullback.
  ON_Curve* PullbackPolyCurve( 
                  const ON_PolyCurve& polycurve_3d,
                  double tolerance,
                  const ON_Interval* curve_3d_subdomain,
                  ON_3dPoint start_uv,
                  ON_3dPoint end_uv
                  ) const;

  // Helper for ON_Surface::Pushup overrides that does a segment-by-segment
  // pushup.
  ON_Curve* PushupPolyCurve( const ON_PolyCurve& polycurve_2d,
                    double tolerance,
                    const ON_Interval* curve_2d_subdomain
                    ) const;


  // Helper for ON_Surface::Pullback overrides that handles "real" curve issues.
  ON_Curve* PullbackCurveProxy( 
                  const ON_CurveProxy& curveproxy_3d,
                  double tolerance,
                  const ON_Interval* curve_3d_subdomain,
                  ON_3dPoint start_uv,
                  ON_3dPoint end_uv
                  ) const;

  // Helper for ON_Surface::Pushup overrides that handles "real" curve issues.
  ON_Curve* PushupCurveProxy( const ON_CurveProxy& curveproxy_2d,
                    double tolerance,
                    const ON_Interval* curve_2d_subdomain
                    ) const;
};


#if defined(ON_DLL_TEMPLATE)
// This stuff is here because of a limitation in the way Microsoft
// handles templates and DLLs.  See Microsoft's knowledge base 
// article ID Q168958 for details.
#pragma warning( push )
#pragma warning( disable : 4231 )
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_Surface*>;
#pragma warning( pop )
#endif

class ON_CLASS ON_SurfaceArray : public ON_SimpleArray<ON_Surface*>
{
public:
  ON_SurfaceArray( int = 0 );
  ~ON_SurfaceArray();

  ON_BOOL32 Write( ON_BinaryArchive& ) const;
  ON_BOOL32 Read( ON_BinaryArchive& );

  void Destroy(); // deletes surfaces in array and sets count to 0

  ON_BOOL32 Duplicate( ON_SurfaceArray& ) const; // operator= copies the pointer values
                                     // duplicate copies the surfaces themselves
};

ON_DECL
double ON_ClosestPointAngle(const ON_Line&, const ON_Curve&, ON_Interval,const ON_3dPoint&,ON_3dPoint&, double*, double* );

#endif
