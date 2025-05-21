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

#if !defined(ON_OFFSETSURFACE_INC_)
#define ON_OFFSETSURFACE_INC_

class ON_CLASS ON_BumpFunction
{
public:
  ON_BumpFunction();
  ~ON_BumpFunction() = default;
  ON_BumpFunction(const ON_BumpFunction&) = default;
  ON_BumpFunction& operator=(const ON_BumpFunction&) = default;

public:
  double ValueAt(
    double s,
    double t
    ) const;

  void Evaluate(
    double s,
    double t,
    int der_count,
    double* value
    ) const;

public:
  ON_2dPoint m_point = ON_2dPoint::NanPoint; // center of bump
  int m_type[2];//  // = {0,0}  // 1 = linear, 5 = quintic, else linear;

public:
  // numbers used in evaluation
  double m_x0 = 0.0;
  double m_y0 = 0.0;
  double m_sx[2]; // = {0.0, 0.0} // 1/(support radius)
  double m_sy[2]; // = {0.0, 0.0} // 1/(support radius)
  double m_a = 0.0;  // evaluation coefficient

private:
  void Internal_EvaluateLinearBump(double t, double dt, int der_count, double* value) const;
  void Internal_EvaluateQuinticBump(double t, double dt, int der_count, double* value) const;
};


class ON_CLASS ON_OffsetSurfaceValue
{
public:
  ON_OffsetSurfaceValue() = default;
  ~ON_OffsetSurfaceValue() = default;
  ON_OffsetSurfaceValue(const ON_OffsetSurfaceValue&) = default;
  ON_OffsetSurfaceValue& operator=(const ON_OffsetSurfaceValue&) = default;
public:
  double m_s = ON_DBL_QNAN;
  double m_t = ON_DBL_QNAN;
  double m_distance = ON_DBL_QNAN;
  double m_radius = ON_DBL_QNAN;
  int m_index = ON_UNSET_INT_INDEX;
};


#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_BumpFunction>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_OffsetSurfaceValue>;
#endif


class ON_CLASS ON_OffsetSurfaceFunction
{
public:
  ON_OffsetSurfaceFunction();
  ~ON_OffsetSurfaceFunction();

  /*
  Description:
    Sets base surface for the offset function.
  Parameters:
    srf - [in] pointer to the base surface.
               This surface must remain valid while
               the ON_OffsetSurfaceFunction class is used.
  Returns:
    True if successful.
  */
  bool SetBaseSurface(
    const ON_Surface* srf 
    );

  /*
  Returns:
    Base surface specified SetBaseSurface().
  */
  const ON_Surface* BaseSurface() const;

  /*
  Description:
    Use set SetSideTangency if you want the offset 
    surface and base surface to have the same unit
    normals along a side of the surfaces's parameter
    spaces.
  Parameters:
    side - [in]
               0 = south side
               1 = east side
               2 = north side
               3 = west side
    bEnable - [in] true to enable tangency,
                   false to disable tangency
  Returns:
    True if successful.
  */
  bool SetSideTangency(
    int side,
    bool bEnable
    );

  /*
  Parameters:
    side - [in]
               0 = south side
               1 = east side
               2 = north side
               3 = west side
  Returns:
    True if side tangency is enabled.
  */
  bool SideTangency(int side) const;

  /*
  Description:
    Sets the offset distance at a point.  Call this function
    once for each point where the user specifies an offset.
  Parameters:
    s - [in]
    t - [in] (s,t) is a base surface evaluation parameter
    distance - [in] distance is the offset distance.
    radius - [in] if radius>0, then this value will be the
                  the approximate radius of the offset "bump".
  */
  bool SetOffsetPoint(
    double s,
    double t,
    double distance,
    double radius = 0.0
    );

  /*
  Description:
    Sets the surface parameters of an existing offset point.
  Parameters:
    index - [in] index of the point to set
    s - [in]
    t - [in] (s,t) is a base surface evaluation parameter
  */
  bool SetPoint( 
    int index, 
    double s, 
    double t
    );


  /*
  Description: 
    Set the offset distance for an existing point
  Parameters:
    index - [in] index of the point to set
    distance - [in] new distance
  */
  bool SetDistance( 
    int index, 
    double distance);


  /*
  Returns:
    Number of points specified using SetOffsetPoint().
  */
  int OffsetPointCount() const;

  /*
  Parameters:
    i - [in] an index >= 0 and < OffsetPointCount()
  Returns:
    Surface parameter specified using SetOffsetPoint().
  */
  ON_2dPoint OffsetSurfaceParameter(int i) const;

  /*
  Parameters:
    i - [in] an index >= 0 and < OffsetPointCount()
  Returns:
    Offset distance specified using SetOffsetPoint().
  */
  double OffsetDistance(int i) const;

  /*
  Description:
    Value of the offset distance at any surface parameter.
  Parameters:
    s - [in]
    t - [in] (s,t) is a base surface evaluation parameter
  Returns:
    offset distance at the surface parameter
  */
  double DistanceAt(
    double s,
    double t
    ) const;

  /*
  Description:
    Value of the offset distance at any surface parameter.
  Parameters:
    s - [in]
    t - [in] (s,t) is a base surface evaluation parameter
    num_der - [in] number of derivatives
    value - [out] value and derivatives of distance function
                  value[0] = distance, value[1] = 1rst derivative,
                  value[2] = 2nd derivative, ...
  Returns:
    True if successful
  */
  bool EvaluateDistance(
        double s,
        double t,
        int num_der,
        double* value
        ) const;

  /*
  Description:
    Value of the offset function at any surface parameter.
  Parameters:
    s - [in]
    t - [in] (s,t) is a base surface evaluation parameter
  Returns:
    Point on the offset surface.
  */
  ON_3dPoint PointAt(
    double s,
    double t
    ) const;

  /*
  Description:
    Resets this class if you want to reuse it.
  */
  void Destroy();

private:
  friend class ON_OffsetSurface;
  bool Initialize();

  const ON_Surface* m_srf;

  ON_Interval m_domain[2];

  bool m_bZeroSideDerivative[4];   // S,E,N,W side

  ON_SimpleArray<ON_OffsetSurfaceValue> m_offset_value;


  ON_SimpleArray<class ON_BumpFunction> m_bumps;

  bool m_bValid;
};

class ON_CLASS ON_OffsetSurface : public ON_SurfaceProxy
{
  // This is still a work in progress.  In particular,
  // this surface class can not be saved in files, used
  // as a brep surface, added to Rhino, etc.
  //
  // As of January 2004, it is useful for calculating
  // offset meshes and any other fitting and approximation
  // tools that requires a surface evaluator but do not need
  // NURBS forms, isocurves, and so on.
  ON_OBJECT_DECLARE(ON_OffsetSurface);
public:
  ON_OffsetSurface();
  ~ON_OffsetSurface();
  ON_OffsetSurface( const ON_OffsetSurface& src);
  ON_OffsetSurface& operator=(const ON_OffsetSurface& src);

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

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
    Sets base surface to a surface that is not managed
    by the ON_OffsetSurface class.
  Parameters:
    base_surface - [in] points to a base surface the
       caller insures will exist for the lifetimes
       of the ON_OffsetSurface class.
  Returns:
    True if successful.
  */
  bool SetBaseSurface(
    const ON_Surface* base_surface
    );

  /*
  Description:
    Sets base surface to a surface that is optionally managed
    by the ON_OffsetSurface class.
  Parameters:
    base_surface - [in] points to a base surface the
       caller insures will exist for the lifetimes
       of the ON_OffsetSurface class.
    bManage - [in] if true, the base_surface must point
       to a surface that is on the heap and the surface
       will be deleted by ~ON_OffsetSurface.
  Returns:
    True if successful.
  */
  bool SetBaseSurface(
        ON_Surface* base_surface, 
        bool bManage
        );

  /*
  Returns:
    Base surface;
  */
  const ON_Surface* BaseSurface() const;

  ON_OffsetSurfaceFunction& OffsetFunction();
  const ON_OffsetSurfaceFunction& OffsetFunction() const;

private:
  // If not nullptr, this points to the base surface
  ON_Surface* m__pSrf;
  ON_OffsetSurfaceFunction m_offset_function;
};


#endif
