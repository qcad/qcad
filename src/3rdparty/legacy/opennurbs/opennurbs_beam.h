#if !defined(OPENNURBS_EXTRUSION_INC_)
#define OPENNURBS_EXTRUSION_INC_

/*
Description:
  Get the transformation that maps the ON_Extrusion 
  2d xy profile to 3d world space.
Parameters:
  P - [in] start or end of path
  T - [in] unit tanget to path
  U - [in] unit up vector perpindicular to T
  Normal - [in] optional unit vector with Normal->x > 0 that
     defines the unit normal to the miter plane.
  xform - [out]
    transformation that maps the profile curve to 3d world space
  scale2d - [out]
    If not NULL, this is the scale part of the transformation.
    If there is no mitering, then this is the identity.
  rot2d - [out]
    If not null, this is the part of the transformation
    that rotates the xy plane into its 3d world location.
Returns:
  true if successful.
*/
ON_DECL
bool ON_GetEndCapTransformation(
          ON_3dPoint P, 
          ON_3dVector T, 
          ON_3dVector U, 
          const ON_3dVector* Normal,
          ON_Xform& xform, // = rot3d*scale2d
          ON_Xform* scale2d,
          ON_Xform* rot2d
          );

class ON_CLASS ON_Extrusion : public ON_Surface
{
  ON_OBJECT_DECLARE(ON_Extrusion);
public:
  ON_Extrusion();
  ON_Extrusion(const ON_Extrusion& src);
  ~ON_Extrusion();

  ON_Extrusion& operator=(const ON_Extrusion&);

  ////////////////////////////////////////////////////////////
  //
  // overrides of virtual ON_Object functions
  // 
  ON_BOOL32 IsValid( ON_TextLog* text_log = NULL ) const;
  void Dump( ON_TextLog& ) const;
  unsigned int SizeOf() const;
  ON__UINT32 DataCRC( ON__UINT32 current_remainder ) const;
  ON_BOOL32 Write( ON_BinaryArchive& binary_archive) const;
  ON_BOOL32 Read( ON_BinaryArchive& binary_archive );
  ON::object_type ObjectType() const;

  ////////////////////////////////////////////////////////////
  //
  // overrides of virtual ON_Geometry functions
  // 
  int Dimension() const;
  ON_BOOL32 GetBBox(
        double* boxmin,
        double* boxmax,
        int bGrowBox = false
        ) const;
	bool GetTightBoundingBox( 
        ON_BoundingBox& tight_bbox, 
        int bGrowBox = false,
        const ON_Xform* xform = 0
        ) const;
  ON_BOOL32 Transform( 
        const ON_Xform& xform
        );

  /*
  Description:
    Build a brep form of the extrusion.  The outer profile is always 
    the first face in the brep.  If there are inner profiles, 
    additional brep faces are created for each profile.  If the
    outer profile is closed, then end caps are added as the last
    two faces in the brep.
  Parameters:
    brep - [in]
      If the brep pointer is not null, then the brep form is constructed
      in brep.  If the brep pointer is null, then an ON_Brep is allocated
      on the heap.
  Returns:
    If successful, a pointer to the brep form.  If unsuccessful, null.
  */
  ON_Brep* BrepForm(
        ON_Brep* brep = NULL 
        ) const;

  /*
  Description:
    Build a brep form of the extrusion.  The outer profile is always 
    the first face in the brep.  If there are inner profiles, 
    additional brep faces are created for each profile.  If the
    outer profile is closed, then end caps are added as the last
    two faces in the brep.
  Parameters:
    brep - [in]
      If the brep pointer is not null, then the brep form is constructed
      in brep.  If the brep pointer is null, then an ON_Brep is allocated
      on the heap.
    bSplitKinkyFaces - [in]
      If true and the profiles have kinks, then the faces corresponding
      to those profiles are split so they will be G1.
  Returns:
    If successful, a pointer to the brep form.  If unsuccessful, null.
  */
  ON_Brep* BrepForm(
    ON_Brep* brep,
    bool bSplitKinkyFaces 
    ) const;

  ////////////////////////////////////////////////////////////
  //
  // overrides of virtual ON_Surface functions
  // 
  ON_Mesh* CreateMesh( 
        const ON_MeshParameters& mp,
        ON_Mesh* mesh = NULL
        ) const;
  ON_BOOL32 SetDomain( 
        int dir,
        double t0, 
        double t1
        );
  ON_Interval Domain(
        int dir
        ) const;
  ON_BOOL32 GetSurfaceSize( 
        double* width, 
        double* height 
        ) const;
  int SpanCount(
        int dir
        ) const;
  ON_BOOL32 GetSpanVector(
        int dir,
        double* span_vector
        ) const;
  ON_BOOL32 GetSpanVectorIndex(
        int dir,
        double t,
        int side,
        int* span_vector_index,
        ON_Interval* span_interval
        ) const;
  int Degree(
        int dir
        ) const; 
  ON_BOOL32 GetParameterTolerance(
         int dir,
         double t,
         double* tminus,
         double* tplus
         ) const;
  ISO IsIsoparametric(
        const ON_Curve& curve,
        const ON_Interval* curve_domain = NULL
        ) const;
  ON_BOOL32 IsPlanar(
        ON_Plane* plane = NULL,
        double tolerance = ON_ZERO_TOLERANCE
        ) const;
  ON_BOOL32 IsClosed(
        int
        ) const;
  ON_BOOL32 IsPeriodic(
        int
        ) const;
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
  ISO IsIsoparametric(
        const ON_BoundingBox& bbox
        ) const;
  ON_BOOL32 Reverse( int dir );
  ON_BOOL32 Transpose();
  ON_BOOL32 Evaluate(
         double u, double v,
         int num_der,
         int array_stride,
         double* der_array,
         int quadrant = 0,
         int* hint = 0
         ) const;
  ON_Curve* IsoCurve(
         int dir,
         double c
         ) const;
  ON_BOOL32 Trim(
         int dir,
         const ON_Interval& domain
         );
  bool Extend(
    int dir,
    const ON_Interval& domain
    );
  ON_BOOL32 Split(
         int dir,
         double c,
         ON_Surface*& west_or_south_side,
         ON_Surface*& east_or_north_side
         ) const;

  bool GetClosestPoint( 
          const ON_3dPoint& P,
          double* s,
          double* t,
          double maximum_distance = 0.0,
          const ON_Interval* sdomain = 0,
          const ON_Interval* tdomain = 0
          ) const;

  ON_BOOL32 GetLocalClosestPoint( const ON_3dPoint&, // test_point
          double,double,     // seed_parameters
          double*,double*,   // parameters of local closest point returned here
          const ON_Interval* = NULL, // first parameter sub_domain
          const ON_Interval* = NULL  // second parameter sub_domain
          ) const;

  //ON_Surface* Offset(
  //      double offset_distance, 
  //      double tolerance, 
  //      double* max_deviation = NULL
  //      ) const;

  int GetNurbForm(
        ON_NurbsSurface& nurbs_surface,
        double tolerance = 0.0
        ) const;
  int HasNurbForm() const;
  bool GetSurfaceParameterFromNurbFormParameter(
        double nurbs_s, double nurbs_t,
        double* surface_s, double* surface_t
        ) const;
  bool GetNurbFormParameterFromSurfaceParameter(
        double surface_s, double surface_t,
        double* nurbs_s,  double* nurbs_t
        ) const;

  ////////////////////////////////////////////////////////////
  //
  // ON_Extrusion interface
  // 
  void Destroy();

  /*
  Description:
    Sets m_path to (A,B), m_path_domain to [0,Length(AB)],
    and m_t to [0,1].
  Parameters:
    A - [in] path start
    B - [in] path end
  Returns:
    true  A and B are valid, the distance from A to B is larger
          than ON_ZERO_TOLERANCE, and the path was set.
    false A or B is not valid or the distance from A to B is
          at most ON_ZERO_TOLERANCE. In this case nothing is set.
  Remark:
    You must also set the up direction to be perpendicular to the path.
  */
  bool SetPath(ON_3dPoint A, ON_3dPoint B);

  /*
  Description:
    Sets m_path to (A,B), m_path_domain to [0,Length(AB)],
    m_t to [0,1], and m_up.
  Parameters:
    A - [in] path start
    B - [in] path end
    up - [in] up direction
      If up is a unit vector and perpindicular to the line 
      segment from A to B, then m_up is set to up.
      Otherwise up will be adjusted so it is perpendicular
      to the line segment from A to B and unitized.
  Returns:
    true  A and B are valid, the distance from A to B is larger
          than ON_ZERO_TOLERANCE, and the path was set.
    false A or B is not valid, or the distance from A to B is
          at most ON_ZERO_TOLERANCE, or up is invalid, or up
          is zero, or up is parallel to the line segment.
          In this case nothing is set.
  */
  bool SetPathAndUp(ON_3dPoint A, ON_3dPoint B, ON_3dVector up );

  /*
  Description:
    Get the surface parameter for the path.
  Returns:
    0: The first surface parameter corresponds to the path direction.
       (m_bTransposed = true)
    1: The second surface parameter corresponds to the path direction.
       (m_bTransposed = false)
  Remarks:
    The default ON_Extrusion constructor sets 
    m_bTransposed = false which corresponds to the 1 = PathParameter().
  */
  int PathParameter() const;

  ON_3dPoint PathStart() const;
  ON_3dPoint PathEnd() const;
  ON_3dVector PathTangent() const;

  /*
  Description:
    Set miter plane normal.
  Parameters:
    N - [in] If ON_UNSET_VECTOR or N is parallel to the z-axis,
             then the miter plane is the default plane 
             perpindicular to the path.
             If N is valid and the z coordinate of a unitized
             N is greater than m_Nz_tol, then the miter plane 
             normal is set.
    end - [in] 0 = set miter plane at the start of the path.
               1 = set miter plane at the end of the path.
  */
  bool SetMiterPlaneNormal(ON_3dVector N, int end);

  void GetMiterPlaneNormal(int end, ON_3dVector& N) const;

  /*
  Returns:
    0: not mitered.
    1: start of path is mitered.
    2: end of path is mitered.
    3: start and end are mitered.
  */
  int IsMitered() const;

  /*
  Returns:
    True if extrusion object is a capped solid.
  */
  bool IsSolid() const;

  /*
  Returns:
    0: no or profile is open
    1: bottom cap
    2: top cap
    3: both ends capped.
  */
  int IsCapped() const;

  /*
  Description:
    Get the transformation that maps the xy profile curve
    to its 3d location.
  Parameters:
    s - [in] 0.0 = starting profile
             1.0 = ending profile
  */
  bool GetProfileTransformation( double s, ON_Xform& xform ) const;

  /*
  Description:
    Get the the 3d plane containing the profile curve at a
    normalized path parameter.
  Parameters:
    s - [in] 0.0 = starting plane
             1.0 = ending plane
    plane - [out]
      Plane containing profile is returned in plane.  If
      false is returned, then the input value of plane
      is not changed.
  Returns:
    true if plane was set.  False if this is invalid and plane
    could not be set.
  Remarks:
    When no mitering is happening, GetPathPlane() and
    GetProfilePlane() return the same plane.
  */
  bool GetProfilePlane( double s, ON_Plane& plane ) const;


  /*
  Description:
    Get the the 3d plane perpindicular to the path at a
    normalized path parameter.
  Parameters:
    s - [in] 0.0 = starting plane
             1.0 = ending plane
    plane - [out]
      Plane is returned here.  If
      false is returned, then the input value of plane
      is not changed.
  Returns:
    true if plane was set.  False if this is invalid and plane
    could not be set.
  Remarks:
    When no mitering is happening, GetPathPlane() and
    GetProfilePlane() return the same plane.
  */
  bool GetPathPlane( double s, ON_Plane& plane ) const;

  /*
  Description:
    Set the outer profile of the extrusion.
  Paramters:
    outer_profile - [in] 
      curve in the xy plane or a 2d curve.
    bCap - [in]
      If outer_profile is a closed curve, then bCap
      determines if the extrusion has end caps.
      If outer_profile is an open curve, bCap is ignored.
  Returns:
    True if the profile was set. In this case the ON_Extrusion class
    manages the curve and ~ON_Extrusion will delete it.  If the outer
    profile is closed, then the extrusion may also have inner profiles.
    If the outer profile is open, the extrusion may not have inner
    profiles. If the extrusion already has a profile, the set will
    fail.
  Remarks:
    If needed, outer_profile will be converted to a 2d
    curve. If outer_curve is closed but not correctly oriented,
    it will reversed so it has a counter-clockwise orientation.
  */
  bool SetOuterProfile( ON_Curve* outer_profile, bool bCap );

  /*
  Description:
    Add an inner profile.
  Paramters:
    inner_profile - [in]
      closed curve in the xy plane or a 2d curve.
  Returns:
    True if the profile was set. In this case the 
    ON_Extrusion class  manages the curve and ~ON_Extrusion will 
    delete it. The extrusion must already have an outer profile.
    If the extrusion already has a profile, the set will
    fail.
  Remarks:
    If needed, innter_profile will be converted to a 2d
    curve. If inner_profile is not correctly oriented, it
    will be reversed so it has a clockwise orientation.
  */
  bool AddInnerProfile( ON_Curve* inner_profile );


  /*
  Returns:
    Number of profile curves.
  */
  int ProfileCount() const;


  /*
  Description:
    Get the surface parameter for the profile.
  Returns:
    0: The first surface parameter corresponds to the profile direction.
       (m_bTransposed = false)
    1: The second surface parameter corresponds to the profile direction.
       (m_bTransposed = true)
  Remarks:
    The default ON_Extrusion constructor sets 
    m_bTransposed = false which corresponds to the 0 = ProfileParameter().
  */
  int ProfileParameter() const;

  /*
  Paramters:
    profile_index - [in]
      0 <= profile_index < ProfileCount().
      The outer profile has index 0.
  Returns:
    Pointer to the i-th 2d profile.  The ON_Extrusion
    class manages this curve.  Do not delete it
    and do not use the pointer if the ON_Extrusion
    class changes.
  */
  const ON_Curve* Profile(int profile_index) const;

  /*
  Paramters:
    profile_index - [in]
      0 <= profile_index < ProfileCount().
      The outer profile has index 0.
    s - [in] ( 0.0 <= s <= 1.0 )
      A relative parameter controling which priofile
      is returned. s = 0.0 returns the bottom profile
      and s = 1.0 returns the top profile.
  Returns:
    NULL if the input parameters or the ON_Extrusion class is
    not valid.  Otherwise a pointer to a 3d curve for 
    the requested profile. This curve is on the heap and
    the caller is responsible for deleting this curve.
  */
  ON_Curve* Profile3d(int profile_index, double s ) const;

  /*
  Paramters:
    ci - [in]
      component index identifying a 3d extrusion profile curve.
  Returns:
    NULL if the component index or the ON_Extrusion class is
    not valid.  Otherwise a pointer to a 3d curve for 
    the requested profile. This curve is on the heap and
    the caller is responsible for deleting this curve.
  */
  ON_Curve* Profile3d( ON_COMPONENT_INDEX ci ) const;

  /*
  Returns:
    If m_profile_count >= 2 and m_profile is an ON_PolyCurve
    with m_profile_count segments defining outer and inner
    profiles, a pointer to the polycurve is returned.
    Otherwise null is returned.
  */
  const ON_PolyCurve* PolyProfile() const;

  /*
  Description:
    Get a list of the profile curves.
  Returns:
    Number of curves appended to the list.
  */
  int GetProfileCurves( ON_SimpleArray<const ON_Curve*>& profile_curves ) const;

  /*
  Description:
    Test a polycurve to determine if it meets the necessary 
    conditions to be used as a multi-segment profile in a extrusion.
  Returns:
    True if the returned polycurve can be used a a multi-segment 
    profile in a extrusion.
  */
  static bool IsValidPolyCurveProfile( const ON_PolyCurve& polycurve, ON_TextLog* text_log = 0 );

  /*
  Description:
    If possible, modify a polycurve so it meets the necessary conditions
    to be used as a multi-segment profile in a extrusion.
  Returns:
    True if the returned polycurve can be used a a multi-segment 
    profile in a extrusion.
  */
  static bool CleanupPolyCurveProfile( ON_PolyCurve& polycurve );

  // path definition:
  //   The line m_path must have length > m_path_length_min.
  //   The interval m_t must statisfy 0 <= m_t[0] < m_t[1] <= 1.
  //   The extrusion starts at m_path.PointAt(m_t[0]) and ends
  //   at m_path.PointAt(m_t[1]).
  //   The "up" direction m_up is a unit vector that must
  //   be perpindicular to m_path.Tangent().
  ON_Line m_path;
  ON_Interval m_t;
  ON_3dVector m_up;

  // profile information:
  //   In general, use SetOuterProfile() and AddInnerProfile()
  //   to set m_profile_count and m_profile.  If you are
  //   a glutton for punishment, then you might be interested
  //   in the following.
  //   The profile curves must be in the x-y plane.
  //   The profiles' "y" axis corresponds to m_up.
  //   The point (0,0) is extruded along the m_path line.
  //   If m_profile_count = 1, then m_profile can be any
  //   type of continous curve.  If m_profile_count > 1,
  //   then m_profile must be an ON_PolyCurve with
  //   m_profile_count segments, the domain of each segment
  //   must exactly match the polycurve's segment domain,
  //   every segment must be continuous and closed,
  //   the first segement curve must have counter-clockwise
  //   orientation, and the rest must have clockwise 
  //   orientations.
  int m_profile_count;
  ON_Curve* m_profile;

  // capped end information:
  //   If the profile is closed, then m_bCap[] determines
  //   if the ends are capped.
  bool m_bCap[2];

  // mitered end information:
  //   The normals m_N[] are with respect to the xy plane.
  //   A normal parallel to the z axis has no mitering.
  //   If m_bHaveN[i] is true, then m_N[i] must be a 3d unit
  //   vector with m_N[i].z > m_Nz_tol;  If m_bHaveN[i]
  //   is false, then m_N[i] is ignored.  The normal m_N[0]
  //   defines the start miter plane and m_N[1] defines the
  //   end miter plane.
  bool m_bHaveN[2];
  ON_3dVector m_N[2];

  // Surface parameterization information
  ON_Interval m_path_domain;
  bool m_bTransposed; // false: (s,t) = (profile,path)

  // The z coordinates of miter plane normals must be
  // greater than m_Nz_tol
  static const double m_Nz_min; // 1/64;

  // The length of the m_path line must be greater than
  // m_path_length_min
  static const double m_path_length_min; // ON_ZERO_TOLERANCE;

  /*
  Description:
    Get an ON_Exrusion form of a cylinder.
  Parameters:
    cylinder - [in] cylinder.IsFinite() must be true
    bCapBottom - [in] if true, the end at cylinder.m_height[0] will be capped
    bCapTop - [in] if true, the end at cylinder.m_height[1] will be capped
    extrusion - [in] 
      If the input extrusion pointer is null, one will be allocated on the heap
      and it is the caller's responsibility to delte it at an appropriate time.
      If the input point is not null, this extrusion will be used and the same
      pointer will be returned, provided the input is valid.
  Returns:
    If the input is valid, a pointer to an ON_Exrusion form of the cylinder.
    If the input is not valid, then null, even when the input extrusion
    object is not null.
  Example:

          ON_Cylinder cylinder = ...;
          bool bCapBottom = true;
          bool bCapTop = true;
          ON_Extrusion extrusion;
          if ( 0 == ON_Extrusion::Cylinder(cylinder,bCapBottom,bCapTop,&extrusion) )
          {
            // input is not valid - nothing set
            ...
          }
          else
          {
            // extrusion = cylinder
            ...
          }
  */
  static ON_Extrusion* Cylinder( 
    const ON_Cylinder& cylinder, 
    bool bCapBottom,
    bool bCapTop,
    ON_Extrusion* extrusion = 0 
    );

  /*
  Description:
    Get an ON_Exrusion form of a pipe.
  Parameters:
    cylinder - [in] cylinder.IsFinite() must be true
      The cylinder can be either the inner or outer wall of the pipe.
    other_radius - [in] ( != cylinder.Radius() )
      If cylinder.Radius() < other_radius, then the cylinder will be
      the inside of the pipe.  If cylinder.Radius() > other_radius, then
      the cylinder will be the outside of the pipe.
    bCapBottom - [in] if true, the end at cylinder.m_height[0] will be capped
    bCapTop - [in] if true, the end at cylinder.m_height[1] will be capped
    extrusion - [in] 
      If the input extrusion pointer is null, one will be allocated on the heap
      and it is the caller's responsibility to delte it at an appropriate time.
      If the input point is not null, this extrusion will be used and the same
      pointer will be returned, provided the input is valid.
  Returns:
    If the input is valid, a pointer to an ON_Exrusion form of the pipe.
    If the input is not valid, then null, even when the input extrusion
    object is not null.
  Example:

          ON_Cylinder cylinder = ...;
          double other_radius = cylinder.Radius()+1.0;
          bool bCapBottom = true;
          bool bCapTop = true;
          ON_Extrusion extrusion;
          if ( 0 == ON_Extrusion::Pipe(cylinder,other_radius,bCapBottom,bCapTop,&extrusion) )
          {
            // input is not valid - nothing set
            ...
          }
          else
          {
            // extrusion = pipe
            ...
          }
  */
  static ON_Extrusion* Pipe( 
    const ON_Cylinder& cylinder, 
    double other_radius,
    bool bCapBottom,
    bool bCapTop,
    ON_Extrusion* extrusion = 0 
    );
};

#endif

