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

#if !defined(ON_GEOMETRY_SURFACE_PLANE_INC_)
#define ON_GEOMETRY_SURFACE_PLANE_INC_

class ON_PlaneSurface;

class ON_CLASS ON_PlaneSurface : public ON_Surface
{
  ON_OBJECT_DECLARE(ON_PlaneSurface);

public:
  ON_PlaneSurface();
  ON_PlaneSurface(const ON_PlaneSurface&);
  ON_PlaneSurface& operator=(const ON_PlaneSurface&);

  ON_PlaneSurface(const ON_Plane&);
  ON_PlaneSurface& operator=(const ON_Plane&);

  virtual ~ON_PlaneSurface();

  // An ON_PlaneSurface is really a finite rectangle.
  // m_plane defines the plane and m_extents[] stores
  // the x and y intervals of the plane that define the
  // rectangle.  The m_domain[] intervals specify the
  // evaluation domain.  Changing the extents are domain
  // are INDEPENDENT of each other.  Use Domain() and
  // SetDomain() to control the evaluation domain.  Use
  // Extents() and SetExtents() to control the rectangle
  // extents.
  ON_Plane m_plane;

  /////////////////////////////////////////////////////////////////
  // ON_Object overrides

  // virtual ON_Object::SizeOf override
  unsigned int SizeOf() const override;

  // virtual ON_Object::DataCRC override
  ON__UINT32 DataCRC(ON__UINT32 current_remainder) const override;

  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  void Dump( ON_TextLog& ) const override; // for debugging

  bool Write(
         ON_BinaryArchive&  // open binary file
       ) const override;

  bool Read(
         ON_BinaryArchive&  // open binary file
       ) override;

  /////////////////////////////////////////////////////////////////
  // ON_Geometry overrides

  int Dimension() const override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

  bool Transform( 
         const ON_Xform&
         ) override;

  /////////////////////////////////////////////////////////////////
  // ON_Surface overrides


  /*
  Description:
    Computes a polygon mesh of the surface made of one quad.   
  Parameters:
    mesh - [in] if not nullptr, the surface mesh will be put
                into this mesh. Otherwise, operator new will be used.
  Returns:
    A polygon mesh of the surface.
  */
  ON_Mesh* CreateMesh(
    ON_Mesh* mesh = nullptr
  ) const;

  /*
  Description:
    Sets the evaluation domains.  Does not change the geometry.
  Parameters:
    dir - [in] 0 sets first parameter's domain
               1 sets second parameter's domain
    t0 - [in]
    t1 - [in] (t0 < t1) the interval (t0,t1) will be the new domain
  Returns:
    True if successful.
  See Also:
    ON_PlaneSurface::SetExtents
  */
  bool SetDomain( 
    int dir, 
    double t0, 
    double t1
    ) override;

  ON_Interval Domain(
    int // 0 gets first parameter's domain, 1 gets second parameter's domain
    ) const override;

  /*
  Description:
    Get an estimate of the size of the rectangle that would
    be created if the 3d surface where flattened into a rectangle.
  Parameters:
    width - [out]  (corresponds to the first surface parameter)
    height - [out] (corresponds to the first surface parameter)
  Remarks:
    overrides virtual ON_Surface::GetSurfaceSize
  Returns:
    true if successful.
  */
  bool GetSurfaceSize( 
      double* width, 
      double* height 
      ) const override;

  int SpanCount(
    int // 0 gets first parameter's domain, 1 gets second parameter's domain
    ) const override; // number of smooth spans in curve

  bool GetSpanVector( // span "knots" 
    int, // 0 gets first parameter's domain, 1 gets second parameter's domain
    double* // array of length SpanCount() + 1 
    ) const override; // 

  int Degree( // returns maximum algebraic degree of any span 
                  // ( or a good estimate if curve spans are not algebraic )
    int // 0 gets first parameter's domain, 1 gets second parameter's domain
    ) const override; 

  bool GetParameterTolerance( // returns tminus < tplus: parameters tminus <= s <= tplus
         int,     // 0 gets first parameter, 1 gets second parameter
         double,  // t = parameter in domain
         double*, // tminus
         double*  // tplus
         ) const override;

  /*
  Description:
    Test a surface to see if it is planar.
  Parameters:
    plane - [out] if not nullptr and true is returned,
                  the plane parameters are filled in.
    tolerance - [in] tolerance to use when checking
  Returns:
    true if there is a plane such that the maximum distance from
    the surface to the plane is <= tolerance.
  Remarks:
    Overrides virtual ON_Surface::IsPlanar.
  */
  bool IsPlanar(
        ON_Plane* plane = nullptr,
        double tolerance = ON_ZERO_TOLERANCE
        ) const override;

  bool IsClosed(   // true if surface is closed in direction
        int        // dir  0 = "s", 1 = "t"
        ) const override;

  bool IsPeriodic( // true if surface is periodic in direction
        int        // dir  0 = "s", 1 = "t"
        ) const override;

  bool IsSingular( // true if surface side is collapsed to a point
        int        // side of parameter space to test
                   // 0 = south, 1 = east, 2 = north, 3 = west
        ) const override;
  
  /*
  Description:
    Search for a derivative, tangent, or curvature
    discontinuity.
  Parameters:
    dir - [in] If 0, then "u" parameter is checked.  If 1, then
               the "v" parameter is checked.
    c - [in] type of continuity to test for.
    t0 - [in] Search begins at t0. If there is a discontinuity
              at t0, it will be ignored.  This makes it 
              possible to repeatedly call GetNextDiscontinuity
              and step through the discontinuities.
    t1 - [in] (t0 != t1)  If there is a discontinuity at t1 is 
              will be ignored unless c is a locus discontinuity
              type and t1 is at the start or end of the curve.
    t - [out] if a discontinuity is found, then *t reports the
          parameter at the discontinuity.
    hint - [in/out] if GetNextDiscontinuity will be called 
       repeatedly, passing a "hint" with initial value *hint=0
       will increase the speed of the search.       
    dtype - [out] if not nullptr, *dtype reports the kind of 
        discontinuity found at *t.  A value of 1 means the first 
        derivative or unit tangent was discontinuous.  A value 
        of 2 means the second derivative or curvature was 
        discontinuous.  A value of 0 means the curve is not
        closed, a locus discontinuity test was applied, and
        t1 is at the start of end of the curve.
    cos_angle_tolerance - [in] default = cos(1 degree) Used only
        when c is ON::continuity::G1_continuous or ON::continuity::G2_continuous.  If the
        cosine of the angle between two tangent vectors is 
        <= cos_angle_tolerance, then a G1 discontinuity is reported.
    curvature_tolerance - [in] (default = ON_SQRT_EPSILON) Used 
        only when c is ON::continuity::G2_continuous.  If K0 and K1 are 
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
  bool GetNextDiscontinuity( 
                  int dir,
                  ON::continuity c,
                  double t0,
                  double t1,
                  double* t,
                  int* hint=nullptr,
                  int* dtype=nullptr,
                  double cos_angle_tolerance=ON_DEFAULT_ANGLE_TOLERANCE_COSINE,
                  double curvature_tolerance=ON_SQRT_EPSILON
                  ) const override;

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
        c is ON::continuity::G1_continuous or ON::continuity::G2_continuous.  If the cosine
        of the angle between two normal vectors 
        is <= cos_angle_tolerance, then a G1 discontinuity is reported.
    curvature_tolerance - [in] (default = ON_SQRT_EPSILON) Used only when
        c is ON::continuity::G2_continuous.  If K0 and K1 are curvatures evaluated
        from above and below and |K0 - K1| > curvature_tolerance,
        then a curvature discontinuity is reported.
  Returns:
    true if the surface has at least the c type continuity at the parameter t.
  Remarks:
    Overrides virtual ON_Surface::IsContinuous
  */
  bool IsContinuous(
    ON::continuity c,
    double s, 
    double t, 
    int* hint = nullptr,
    double point_tolerance=ON_ZERO_TOLERANCE,
    double d1_tolerance=ON_ZERO_TOLERANCE,
    double d2_tolerance=ON_ZERO_TOLERANCE,
    double cos_angle_tolerance=ON_DEFAULT_ANGLE_TOLERANCE_COSINE,
    double curvature_tolerance=ON_SQRT_EPSILON
    ) const override;

  bool Reverse(  // reverse parameterization, Domain changes from [a,b] to [-b,-a]
    int // dir  0 = "s", 1 = "t"
    ) override;

  bool Transpose() override; // transpose surface parameterization (swap "s" and "t")


  bool Evaluate( // returns false if unable to evaluate
         double, double, // evaluation parameters
         int,            // number of derivatives (>=0)
         int,            // array stride (>=Dimension())
         double*,        // array of length stride*(ndir+1)*(ndir+2)/2
         int = 0,        // optional - determines which quadrant to evaluate from
                         //         0 = default
                         //         1 from NE quadrant
                         //         2 from NW quadrant
                         //         3 from SW quadrant
                         //         4 from SE quadrant
         int* = 0        // optional - evaluation hint (int[2]) used to speed
                         //            repeated evaluations
         ) const override;

  /*
  Description:
    Get isoparametric curve.
    Overrides virtual ON_Surface::IsoCurve.
  Parameters:
    dir - [in] 0 first parameter varies and second parameter is constant
                 e.g., point on IsoCurve(0,c) at t is srf(t,c)
               1 first parameter is constant and second parameter varies
                 e.g., point on IsoCurve(1,c) at t is srf(c,t)

    c - [in] value of constant parameter 
  Returns:
    Isoparametric curve.
  */
  ON_Curve* IsoCurve(
         int dir,         
         double c
         ) const override;


  /*
  Description:
    Removes the portions of the surface outside of the specified interval.
    Overrides virtual ON_Surface::Trim.

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
  bool Trim(
         int dir,
         const ON_Interval& domain
         ) override;

  /*
   Description:
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
  bool Extend(
    int dir,
    const ON_Interval& domain
    ) override;

  /*
  Description:
    Splits (divides) the surface into two parts at the 
    specified parameter.
    Overrides virtual ON_Surface::Split.

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

          ON_PlaneSurface srf = ...;
          int dir = 1;
          ON_PlaneSurface* south_side = 0;
          ON_PlaneSurface* north_side = 0;
          srf.Split( dir, srf.Domain(dir).Mid() south_side, north_side );

  */
  bool Split(
         int dir,
         double c,
         ON_Surface*& west_or_south_side,
         ON_Surface*& east_or_north_side
         ) const override;


  int GetNurbForm( // returns 0: unable to create NURBS representation
                   //            with desired accuracy.
                   //         1: success - returned NURBS parameterization
                   //            matches the surface's to wthe desired accuracy
                   //         2: success - returned NURBS point locus matches
                   //            the surfaces's to the desired accuracy but, on
                   //            the interior of the surface's domain, the 
                   //            surface's parameterization and the NURBS
                   //            parameterization may not match to the 
                   //            desired accuracy.
        ON_NurbsSurface&,
        double = 0.0
        ) const override;

  int HasNurbForm( // returns 0: unable to create NURBS representation
                   //            with desired accuracy.
                   //         1: success - returned NURBS parameterization
                   //            matches the surface's to wthe desired accuracy
                   //         2: success - returned NURBS point locus matches
                   //            the surfaces's to the desired accuracy but, on
                   //            the interior of the surface's domain, the 
                   //            surface's parameterization and the NURBS
                   //            parameterization may not match to the 
                   //            desired accuracy.
        ) const override;

  /*
  Description:
    Sets the extents of then rectangle.  Does not change the evaluation
    domain.
  Parameters:
    dir - [in] 0 sets plane's x coordinate extents
               1 sets plane's y coordinate extents
    extents - [in] increasing interval
    bSynchDomain - [in] if true, the corresponding evaluation interval
               domain is set so that it matches the extents interval
  Returns:
    True if successful.
  See Also:
    ON_PlaneSurface::SetDomain
  */
  bool SetExtents( 
         int dir,
         ON_Interval extents,
         bool bSynchDomain = false
         );

  /*
  Description:
    Gets the extents of the rectangle.
  Parameters:
    dir - [in] 0 gets plane's x coordinate extents
               1 gets plane's y coordinate extents
  Returns:
    Increasing interval
  See Also:
    ON_PlaneSurface::Domain
  */
  ON_Interval Extents(
         int dir
         ) const;

  /*
  Description:
    Create a plane that contains the projection of a bounding box.
  Parameters:
    plane_equation - [in]
    bbox - [in]
    padding - [in]
      amount of extra padding to add around the edges of the
      plane.  Default is 0.0625
  Returns:
    true if successful
  */
  bool CreatePseudoInfinitePlane( 
          ON_PlaneEquation plane_equation,
          const ON_BoundingBox& bbox,
          double padding = 0.0625
          );

  /*
  Description:
    Create a plane that contains the projection of a bounding box.
  Parameters:
    plane - [in]
    bbox - [in]
    padding - [in]
      amount of extra padding to add around the edges of the
      plane.  Default is 0.0625
  Returns:
    true if successful
  */
  bool CreatePseudoInfinitePlane( 
          const ON_Plane& plane,
          const ON_BoundingBox& bbox,
          double padding = 0.0625
          );

  /*
  Description:
    Create a plane that contains the intersection of a bounding box.
    This method uses box edges intersections rather than box vertices
    projections on the plane, which is what CreatePseudoInfinitePlane
    uses.
  Parameters:
    plane - [in]
    bbox - [in]
    padding - [in]
      amount of extra padding to add around the edges of the
      plane.  Default is 0.0625
  Returns:
    true if successful
  */
  bool CreatePlaneThroughBox(
    const ON_Plane& plane,
    const ON_BoundingBox& bbox,
    double padding = 0.0625
  );

    /*
  Description:
    Create a plane that contains the intersection of a bounding box.
    This method uses box edges intersections rather than box vertices
    projections on the plane, which is what CreatePseudoInfinitePlane
    uses.
  Parameters:
    plane - [in]
    bbox - [in]
    padding - [in]
      amount of extra padding to add around the edges of the
      plane.  Default is 0.0625
  Returns:
    true if successful
  */
  bool CreatePlaneThroughBox(
    const ON_PlaneEquation& plane,
    const ON_BoundingBox& bbox,
    double padding = 0.0625
  );

  /*
  Description:
    Create a plane that contains the projection of a list of points.
  Parameters:
    plane - [in]
    point_count - [in]
    point_list - [in]
    padding - [in]
      amount of extra padding to add around the edges of the
      plane.  Default is 0.0625
  Returns:
    true if successful
  */
  bool CreatePseudoInfinitePlane( 
          const ON_Plane& plane,
          int point_count,
          const ON_3dPoint* point_list,
          double padding = 0.0625
          );

protected:
  // evaluation domain (always increasing)
  ON_Interval m_domain[2]; // always increasing

  // rectangle extents (in m_plane x,y coordinates)
  ON_Interval m_extents[2];
};


class ON_CLASS ON_ClippingPlaneSurface : public ON_PlaneSurface
{
  ON_OBJECT_DECLARE(ON_ClippingPlaneSurface);
public:
  ON_ClippingPlaneSurface();
  ON_ClippingPlaneSurface(const ON_Plane& src);
  ON_ClippingPlaneSurface(const ON_PlaneSurface& src);
  ~ON_ClippingPlaneSurface();

  ON_ClippingPlaneSurface& operator=(const ON_Plane& src);
  ON_ClippingPlaneSurface& operator=(const ON_PlaneSurface& src);

  void Default();

  // override ON_Object::ObjectType() - returns ON::clipplane_object
  ON::object_type ObjectType() const override;

  // virtual ON_Object::SizeOf override
  unsigned int SizeOf() const override;

  // virtual ON_Object::DataCRC override
  ON__UINT32 DataCRC(ON__UINT32 current_remainder) const override;

  // virtual ON_Object::Dump override
  void Dump( ON_TextLog& ) const override; // for debugging

  // virtual ON_Object::Write override
  bool Write(
         ON_BinaryArchive&  // open binary file
       ) const override;

  // virtual ON_Object::Read override
  bool Read(
         ON_BinaryArchive&  // open binary file
       ) override;

  ON_ClippingPlane m_clipping_plane;
};


#endif
