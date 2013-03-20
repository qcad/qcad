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

#if !defined(OPENNURBS_X_INC_)
#define OPENNURBS_X_INC_

// The ON_X_EVENT class is used to report curve-curve and curve-surface
// intersection events.
class ON_CLASS ON_X_EVENT
{
  // NO VIRTUAL FUNCTIONS IN THIS CLASS
public:
  
  // Default construction sets everything to zero.
  ON_X_EVENT();

  // This class must use default copy constructor, operator=, and destructor.

  /*
  Description:
    Compares intersection events and sorts them in the 
    canonical order.
  Returns:
    @untitled table
    -1    this  < other
     0    this == other
    +1    this  > other
  Remarks:
    ON_CX_EVENT::Compare is used to sort intersection events into canonical
    order.
  */
  static
  int Compare( const ON_X_EVENT* a, const ON_X_EVENT* b );

  void Dump(ON_TextLog& text_log) const;

  /*
  Description:
    Check intersection event values to make sure they are valid.
  Parameters:
    text_log - [in] If not null and an error is found, then a description
                    of the error is printed to text_log.
    intersection_tolerance - [in] 
         0.0 or value used in intersection calculation.
    overlap_tolerance - [in] 
         0.0 or value used in intersection calculation.
    curveA - [in] 
         NULL or curveA passed to intersection calculation.
    curveA_domain - [in] 
         NULL or curveA domain used in intersection calculation.
    curveB - [in]
         NULL or curveB passed to intersection calculation.
    curveB_domain - [in]
         NULL or curveB domain used in intersection calculation.
    surfaceB - [in]
         NULL or surfaceB passed to intersection calculation.
    surfaceB_domain0 - [in]
         NULL or surfaceB "u" domain used in intersection calculation.
    surfaceB_domain1 - [in]
         NULL or surfaceB "v" domain used in intersection calculation.
  Returns:
    True if event is valid.
  */
  bool IsValid(
          ON_TextLog* text_log,
          double intersection_tolerance,
          double overlap_tolerance,
          const class ON_Curve* curveA,
          const class ON_Interval* curveA_domain,
          const class ON_Curve* curveB,
          const class ON_Interval* curveB_domain,
          const class ON_Surface* surfaceB,
          const class ON_Interval* surfaceB_domain0,
          const class ON_Interval* surfaceB_domain1
          ) const;


  /*
  Description:
    Expert user tool to copy portions of the itersection
    event information from one event to another.  
    If src.m_type is ON_X_EVENT::csx_*, then the
    m_b[] and m_nodeB_t[] values are treated as
    surface parameters, otherwise the values are
    treated as curve parameters.  The m_type field
    is not copied.
  Parameters:
    src - [in]
    src_end - [in] 0 or 1 (m_A[] source index)
    dst - [out]
    dst_end - [in] 0 or 1 (m_A[] destination index)
  */
  static 
  void CopyEventPart(
        const ON_X_EVENT& src, 
        int src_end,
        ON_X_EVENT& dst, 
        int dst_end 
        );

  /*
  Description:
    Expert user tool to cleanup a list of intersection 
    events.
  Parameters:
    event_tolerance - [in] If the distance between
      events is <= event_tolerance, they will
      be considered to be the same event.  Typically,
      event_tolerance is "small" and
      event_tolerance <= intersection_tolerance.

    overlap_tolerance - [in] minimum length for an
      intersection overlap segment. Typically,
      overlap_tolerance is "large" and
      overlap_tolerance > intersection_tolerance

    xevent_count - [in]
    xevent - [in/out]
  Returns:
    Length of cleaned list.
  */
  static
  int CleanList(
          double event_tolerance,
          double overlap_tolerance,
          int xevent_count,
          ON_X_EVENT* xevent
          );

  /*
  Description:
    Expert user tool to check a list of intersection events.
  Parameters:
    xevent_count - [in]
    xevent - [in]
    text_log - [in] NULL or place to describe errors.
    intersection_tolerance - [in]
    overlap_tolerance - [in]
    curveA - [in]
    curveA_domain - [in] (can be NULL)
    curveB - [in] (NULL for curve-surface intersection events)
    curveB_domain - [in] (can be NULL)
    surfaceB - [in] (NULL for curve-curve intersection events)
    surfaceB_domain0 - [in] (can be NULL)
    surfaceB_domain1 - [in] (can be NULL)
  Returns:
    True if list is valid.
  */
  static
  bool IsValidList(
          int xevent_count,
          const ON_X_EVENT* xevent,
          ON_TextLog* text_log,
          double intersection_tolerance,
          double overlap_tolerance,
          const class ON_Curve* curveA,
          const class ON_Interval* curveA_domain,
          const class ON_Curve* curveB,
          const class ON_Interval* curveB_domain,
          const class ON_Surface* surfaceB,
          const class ON_Interval* surfaceB_domain0,
          const class ON_Interval* surfaceB_domain1
          );

  /*
  Description:
    Do a quick and simple test to see if this curve
    lies on some portion of curveB.
  Parameters:
    curveA_domain - [in] non empty interval
    sample_count - [in] minimum number of test points
    overlap_tolerance - [in]
    cnodeA - [in]
    cnodeB - [in]
    curveB_domain - [in] optional domain restriction
  Returns:
    True if sections overlap.
  */
  static
  bool IsValidCurveCurveOverlap( 
        ON_Interval curveA_domain,
        int sample_count,
        double overlap_tolerance,
        const class ON_CurveTreeNode* cnodeA, 
        const class ON_CurveTreeNode* cnodeB,
        const ON_Interval* curveB_domain = 0
        );

  /*
  Description:
    Do a quick and simple test to see if this curve
    lies on the plane.
  Parameters:
    curveA_domain - [in]  non empty interval
    sample_count - [in] minimum number of test points
    endpont_tolerance - [in] tolerance to use when checking ends
    overlap_tolerance - [in] tolerance to use when checking interior
    cnodeA - [in]
    plane_equation - [in]
  Returns:
    True if curve lies on the plane
  */
  static 
  bool IsValidCurvePlaneOverlap( 
        ON_Interval curveA_domain,
        int sample_count,
        double endpoint_tolerance,
        double overlap_tolerance,
        const class ON_CurveTreeNode* cnodeA,
        const ON_PlaneEquation* plane_equation
        );

  /*
  Description:
    Do a quick and simple test to see if this curve
    lies on the surface.
  Parameters:
    curveA_domain - [in]  non empty interval
    sample_count - [in] minimum number of test points
    overlap_tolerance - [in]
    cnodeA - [in]
    snodeB - [in]
    surfaceB_udomain - [in] optional domain restriction
    surfaceB_vdomain - [in] optional domain restriction
  Returns:
    True if sections overlap.
  */
  static 
  bool IsValidCurveSurfaceOverlap( 
        ON_Interval curveA_domain,
        int sample_count,
        double overlap_tolerance,
        const class ON_CurveTreeNode* cnodeA, 
        const class ON_SurfaceTreeNode* snodeB,
        const ON_Interval* surfaceB_udomain = 0,
        const ON_Interval* surfaceB_vdomain = 0
        );

  /*
  Description:
    Convert input intersection tolerance to value used
    in calculations.
  Parameters:
    intersection_tolerance - [in]
  Returns:
    Value use in intersection calculations.
  */
  static
  double IntersectionTolerance( double intersection_tolerance );

  /*
  Description:
    Convert input intersection tolerance to value used
    in calculations.
  Parameters:
    intersection_tolerance - [in]
  Returns:
    Value use in intersection calculations.
  */
  static
  double OverlapTolerance( double intersection_tolerance, double overlap_tolerance );

  /*
  Returns:
    True if m_type is ccx_point or csx_point.
  */
  bool IsPointEvent() const;

  /*
  Returns:
    True if m_type is ccx_overlap or csx_overlap.
  */
  bool IsOverlapEvent() const;

  /*
  Returns:
    True if m_type is ccx_point or ccx_overlap
  */
  bool IsCCXEvent() const;

  /*
  Returns:
    True if m_type is csx_point or csx_overlap
  */
  bool IsCSXEvent() const;


  enum TYPE
  { 
    no_x_event  =  0,

    // Two valid event types for curve-curve intersections
    ccx_point   =  1, // curve-curve transverse intersection point
    ccx_overlap =  2, // curve-curve intersection overlap

    // Two valid event types for curve-surface intersections
    csx_point   =  3, // curve-surface transverse intersection point
    csx_overlap =  4  // curve-surface intersection overlap
  };

  // Event directions for use in the m_dirA[] and m_dirB[]
  // fields. The "x_from_*" values are used to report the 
  // behavior of the curve as it enters the intersection 
  // event. The "x_to_*" values are used to report the 
  // behavior of the curve as it leaves the intersection
  // event.
  enum DIRECTION
  { 
    no_x_dir       = 0, 

    at_end_dir     = 1, // event is at the start/end/side of object's
                        // parameter space

    from_above_dir = 2, // curve enters x-event from above surface/other curve
    from_below_dir = 3, // curve enters x-event from below surface/other curve
    from_on_dir    = 4, // curve enters x-event tangent surface/other curve

    to_above_dir   = 5, // curve leaves x-event above surface/other curve
    to_below_dir   = 6, // curve leaves x-event below surface/other curve
    to_on_dir      = 7  // curve leaves x-event tangent to surface/other curve
  };

  // This field is a scratch field for users.
  // The constructor sets it to zero and the 
  // intersectors never use it.
  ON_U m_user;

  // The m_type field determines how the values in the other
  // fields are interpreted.  See the detailed comment below
  // for complete informtion
  TYPE m_type;

  ON_3dPoint m_A[2]; // intersection points on first curve
  ON_3dPoint m_B[2]; // intersection points on second curve or surface
  double m_a[2];     // intersection parameters on first curve
  double m_b[4];     // intersection parameters on second curve or surface
  
  // There are cases when it is valuable to have direction
  // flags on intersection events.  The m_dirA[] and m_dirB[]
  // fields provide a place to store these flags.  Because this
  // information is rarely used, it is not computed by the
  // intersection routines.  You can use
  //   ON_SetCurveCurveIntersectionDir 
  // or
  //   ON_SetCurveSurfaceIntersectionDir
  // to fill in these fields.
  DIRECTION m_dirA[2];
  DIRECTION m_dirB[2];

  // tree nodes where the intersection events occured.
  const class ON_CurveTreeNode* m_cnodeA[2];
  double m_nodeA_t[2]; // nodeA bezier paramters corresponding to a[] values 
  const class ON_CurveTreeNode* m_cnodeB[2];
  const class ON_SurfaceTreeNode* m_snodeB[2];
  double m_nodeB_t[4]; // nodeB bezier paramters corresponding to b[] values.

  // Each intersection event is assigned a runtime serial number.
  unsigned int m_x_eventsn;

  /*
  The m_type field determines how the values in the other
  fields are interpreted.

    ccx_point events:
      a[0] = a[1] = first curve parameter
      A[0] = A[1] = intersection point on first curve
      b[0] = b[1] = second curve parmeter
      B[0] = B[1] = intersection point on second curve
      b[2] = b[3] = not used
      cnodeA[0] = cnodeA[1] = pointer to first curve's tree node
      cnodeB[0] = cnodeB[1] = pointer to second curve's tree node
      snodeB[0] = snodeB[1] = 0

    ccx_overlap events:
      (a[0],a[1]) = first curve parameter range (a[0] < a[1])
      A[0] = intersection start point on first curve
      A[1] = intersection end point on first curve
      (b[0],b[1]) = second curve parameter range (b[0] != b[1])
      B[0] = intersection start point on second curve
      B[1] = intersection end point on second curve
      b[2] = b[3] = not used
      cnodeA[0] = pointer to first curve's tree node for start point
      cnodeA[1] = pointer to first curve's tree node for end point
      cnodeB[0] = pointer to second curve's tree node for start point
      cnodeB[1] = pointer to second curve's tree node for end point
      snodeB[0] = snodeB[1] = 0
   
   csx_point events:
      a[0] = a[1] = curve parameter
      A[0] = A[1] = intersection point on curve
      (b[0],b[1]) = (b[2],b[3]) = surface parameter
      B[0] = B[1] intersection point on surface
      cnodeA[0] = cnodeA[1] = pointer to curve's tree node
      cnodeB[0] = cnodeB[1] = 0;
      snodeB[0] = snodeB[1] = pointer to surface's tree node

    csx_overlap events:
      (a[0],a[1]) = curve parmamter range (a[0] < a[1])
      A[0] = intersection start point on first curve
      A[1] = intersection end point on first curve
      (b[0],b[1]) = surface parameter for curve(a[0]).
      B[0] = intersection start point on surface
      (b[2],b[3]) = surface parameter for curve(a[1]).
      B[1] = intersection end point on surface
      cnodeA[0] = pointer to curve's tree node for start point
      cnodeA[1] = pointer to curve's tree node for end point
      snodeB[0] = pointer to surface's tree node for start point
      snodeB[1] = pointer to surface's tree node for end point
  */
};



/*
Description:
  Sets ON_X_EVENT m_dirA[] and m_dirB[] flags for in intersection
  of coplanar curves.  For each  m_dirA[]/m_dirB[] flag that is 
  set to ON_X_EVENT, the curve geometry at the itersection is
  examined to set the flags.
Parameters:
  N [in] normal to the plane
  xcount - [in] number of intersection events
  xevent - [in] array of xcount intersection events
  a0 - [in]
  a1 - [in] (a0,a1) = curveA intersection domain
  b0 - [in]
  b1 - [in] (b0,b1) = curveB intersection domain
See Also:
  ON_Curve::IntersectCurve
  ON_SetCurveSurfaceIntersectionDir
*/
ON_DECL
bool ON_SetCurveCurveIntersectionDir(
            ON_3dVector N,
            int xcount,
            ON_X_EVENT* xevent,
            double a0,
            double a1,
            double b0,
            double b1
            );


/*
Description:
  Sets ON_X_EVENT m_dirA[] and m_dirB[] flags for a curve surface
  intersection.  For each  m_dirA[]/m_dirB[] flag that is 
  set to ON_X_EVENT, the curve and surface geometry at the 
  itersection is examined to set the flags.
Parameters:
  xcount - [in] number of intersection events
  xevent - [in] array of xcount intersection events
  t0 - [in]
  t1 - [in] (t0,t1) = curveA intersection domain
  u0 - [in]
  u1 - [in] (u0,u1) = surfaceB u interesection domain
  v0 - [in]
  v1 - [in] (v0,v1) = surfaceB v interesection domain
Returns:
  << TODO: Add return codes here >>
See Also:
  ON_Curve::IntersectSurface
  ON_SetCurveCurveIntersectionDir
*/
ON_DECL
bool ON_SetCurveSurfaceIntersectionDir(
            int xcount,
            ON_X_EVENT* xevent,
            double t0,
            double t1,
            double u0,
            double u1,
            double v0,
            double v1
            );

// The ON_SSX_EVENT class is used to report surface-surface
// intersection events.
class ON_CLASS ON_SSX_EVENT
{
  // NO VIRTUAL FUNCTIONS IN THIS CLASS
public:
  ON_SSX_EVENT();
  ~ON_SSX_EVENT(); // deletes m_curveA, m_curveB, m_curve3d

  void Dump(ON_TextLog& text_log) const;

  /*
  Description:
    Check intersection event values to make sure they are valid.
  Parameters:
    text_log - [in] If not null and an error is found, then a description
                    of the error is printed to text_log.
    intersection_tolerance - [in] 
         0.0 or value used in intersection calculation.
    overlap_tolerance - [in] 
         0.0 or value used in intersection calculation.
    fitting_tolerance - [in] 
         0.0 or value used in intersection calculation.
    surfaceA - [in] 
         NULL or surfaceA passed to intersection calculation.
    surfaceA_domain0 - [in]
         NULL or surfaceA "u" domain used in intersection calculation.
    surfaceA_domain1 - [in]
         NULL or surfaceA "v" domain used in intersection calculation.
    surfaceB - [in]
         NULL or surfaceB passed to intersection calculation.
    surfaceB_domain0 - [in]
         NULL or surfaceB "u" domain used in intersection calculation.
    surfaceB_domain1 - [in]
         NULL or surfaceB "v" domain used in intersection calculation.
  Returns:
    True if event is valid.
  */
  bool IsValid(
          ON_TextLog* text_log,
          double intersection_tolerance,
          double overlap_tolerance,
          double fitting_tolerance,
          const class ON_Surface* surfaceA,
          const class ON_Interval* surfaceA_domain0,
          const class ON_Interval* surfaceA_domain1,
          const class ON_Surface* surfaceB,
          const class ON_Interval* surfaceB_domain0,
          const class ON_Interval* surfaceB_domain1
          ) const;

  /*
  Returns:
    True if m_type is ssx_transverse_point or ssx_tangent_point.
  See Also:
    ON_SSX_EVENT::IsCurveEvent
    ON_SSX_EVENT::IsTinyEvent
  */
  bool IsPointEvent() const;

  /*
  Returns:
    True if m_type is ssx_transverse or ssx_tangent.
  See Also:
    ON_SSX_EVENT::IsPointEvent
    ON_SSX_EVENT::IsTinyEvent
  */
  bool IsCurveEvent() const;

  /*
  Description:
    This function can be used to detect intersection events
    that are "nearly" points.
  Parameters:
    tiny_tolerance - [in]
  Returns:
    True if 
    m_type is ssx_transverse_point or ssx_tangent_point,
    or,
    m_type is ssx_transverse, ssx_tangent or ssx_overlap
    and length of the longest side of m_curve3d's
    bounding box is <= tiny_tolerance.
  See Also:
    ON_SSX_EVENT::IsPointEvent
    ON_SSX_EVENT::IsCurveEvent
  */
  bool IsTinyEvent(double tiny_tolerance) const;

  /*
  Returns:
    True if m_type is ssx_tangent,  or ssx_tangent_point.
  */
  bool IsTangentEvent() const;

  /*
  Returns:
    True if m_type is ssx_overlap.
  */
  bool IsOverlapEvent() const;

  // This field is a scratch field for users.
  // The constructor sets it to zero and the 
  // intersectors never use it.
  ON_U m_user;

  enum TYPE
  {
    no_ssx_event         = 0,
    ssx_transverse       = 1, // transverse surface-surface intersection curve
    ssx_tangent          = 2, // tangent surface-surface intersection curve
    ssx_overlap          = 3, // overlap surface-surface intersection curve
    ssx_transverse_point = 4, // transverse surface-surface intersection point
    ssx_tangent_point    = 5, // tangent surface-surface intersection point
    ssx_32bit_enum       = 0xFFFFFFFF
  };

  TYPE m_type;

  // If m_type = ssx_transverse, ssx_tangent, or ssx_overlap,
  // then the intersection curves are returned here.  
  // In all cases the 3 curves are compatibly oriented.
  // For ssx_transverse events, the 3d curve direction
  // agrees with SurfaceNormalB x SurfaceNormalA
  // For ssx_tangent events, the orientation is random.
  // For ssx_overlap events, the overlap is to the left of
  // m_curveA.  These curves are deleted by ~ON_SSX_EVENT().
  // If you want to harvest a curve for long term use, set 
  // the pointer to NULL.
  ON_Curve* m_curveA;  // 2d surface A parameter space curve
  ON_Curve* m_curveB;  // 2d surface B parameter space curve
  ON_Curve* m_curve3d; // 3d surface B parameter space curve

  // If m_type = ssx_transverse_point or ssx_tangent_point,
  // the the points are returned here
  ON_3dPoint m_pointA;  // 2d surfaceA parameter space point with z = 0
  ON_3dPoint m_pointB;  // 2d surfaceB parameter space point with z = 0
  ON_3dPoint m_point3d; // 3d intersection point
};

#endif
