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

#if !defined(ON_POLYLINE_INC_)
#define ON_POLYLINE_INC_

class ON_CLASS ON_Polyline : public ON_3dPointArray
{
public:
  ON_Polyline();
  ~ON_Polyline();
  ON_Polyline(const ON_3dPointArray&);
  ON_Polyline& operator=(const ON_3dPointArray&);


  // Description:
  //   Create a regular polygon inscribed in a circle.
  //   The vertices of the polygon will be on the circle.
  // Parameters:
  //   circle - [in]
  //   side_count - [in] (>=3) number of sides
  // Returns:
  //   true if successful.  false if circle is invalid or
  //   side_count < 3.
  bool CreateInscribedPolygon(
    const ON_Circle& circle,
    int side_count
    );

  // Description:
  //   Create a regular polygon circumscribe about a circle.
  //   The midpoints of the polygon's edges will be tangent to the
  //   circle.
  // Parameters:
  //   circle - [in]
  //   side_count - [in] (>=3) number of sides
  // Returns:
  //   true if successful.  false if circle is invalid or
  //   side_count < 3.
  bool CreateCircumscribedPolygon(
    const ON_Circle& circle,
    int side_count
    );

  // Description:
  //   Create a regular star polygon.
  //   The star begins at circle.PointAt(0) and the vertices alternate
  //   between being on circle and begin on a concentric circle of
  //   other_radius.
  // Parameters:
  //   circle - [in] circle star polygon starts on
  //   other_radius - [in] radius of other circle 
  //   corner_count - [in] (>=3) number of corners on circle
  //      There will be 2*corner_count sides and 2*corner_count
  //      vertices.
  // Returns:
  //   true if successful.  false if circle is invalid, other_radius < 0.0,
  //   or side_count < 3.
  bool CreateStarPolygon(
    const ON_Circle& circle,
    double other_radius,
    int side_count
    );

  // Description:
  //   Checks that polyline has at least two points
  //   and that sequential points are distinct.  If the
  //   polyline has 2 or 3 points, then the start and end
  //   point must be distinct.
  // Parameters:
  //   tolerance - [in] tolerance used to check for duplicate points.
  // Returns:
  //   true if polyline is valid.
  // See Also:
  //   ON_Polyline::Clean.
  bool IsValid(
    double tolerance = 0.0 
    ) const;

  // Description:
  //   Removes duplicate points that result in zero length segments.
  // Parameters:
  //   tolerance - [in] tolerance used to check for duplicate points.
  // Returns:
  //   Number of points removed.
  // Remarks:
  //   If the distance between points polyline[i] and polyline[i+1]
  //   is <= tolerance, then the point with index (i+1) is removed.
  int Clean( 
    double tolerance = 0.0 
    );

  // Returns:
  //   Number of points in the polyline.
  int PointCount() const;

  // Returns:
  //   Number of segments in the polyline.
  int SegmentCount() const;

  // Description:
  //   Test a polyline to see if it is closed.
  // Returns:
  //   true if polyline has 4 or more points, the distance between the
  //   start and end points is <= tolerance, and there is a
  //   point in the polyline whose distance from the start and end
  //   points is > tolerance.
  bool IsClosed(
    double tolerance = 0.0 
    ) const;

  /*
  Description:
    Determine if a polyline is convex.
  Parameters:
    bStrictlyConvex - [in]
      If false, collinear segments are considered convex.
  Returns
    True if the polyline is a closed, convex loop.
  */
  bool IsConvexLoop(
    bool bStrictlyConvex
  ) const;


  // Returns:
  //   Length of the polyline.
  double Length() const;


  // Parameters:
  //   segment_index - [in] zero based segment index
  // Returns:
  //   line = point[segment_index] -> point[segment_index+1]
  ON_Line Segment(
    int segment_index
  ) const;


  // Parameters:
  //   segment_index - [in] zero based segment index
  // Returns:
  //   vector = point[segment_index+1] - point[segment_index].
  ON_3dVector SegmentDirection (
    int segment_index
    ) const;

  // Parameters:
  //   segment_index - [in] zero based segment index
  // Returns:
  //   Unit vector in the direction of the segment
  ON_3dVector SegmentTangent (
    int segment_index
    ) const;

  // Description:
  //   Evaluate the polyline location at a parameter.
  // Parameters:
  //   t - [in] the i-th segment goes from i <= t < i+1
  ON_3dPoint PointAt( double t ) const;

  // Description:
  //   Evaluate the polyline first derivative at a parameter.
  // Parameters:
  //   t - [in] the i-th segment goes from i <= t < i+1
  ON_3dVector DerivativeAt( double t ) const;

  // Description:
  //   Evaluate the polyline unit tangent at a parameter.
  // Parameters:
  //   t - [in] the i-th segment goes from i <= t < i+1
  ON_3dVector TangentAt( double t ) const;

  // Description:
  //   Find a point on the polyline that is closest 
  //   to test_point.
  // Parameters:
  //   test_point - [in]
  //   t - [out] parameter for a point on the polyline that
  //             is closest to test_point.  If multiple solutions
  //             exist, then the smallest solution is returned.
  // Returns:
  //   true if successful.
  bool ClosestPointTo( 
        const ON_3dPoint& test_point, 
        double* t
        ) const;

  // Description:
  //   Find a point on the polyline that is closest 
  //   to test_point.
  // Parameters:
  //   test_point - [in]
  //   t - [out] parameter for a point on the polyline that
  //             is closest to test_point.  If multiple solutions
  //             exist, then the smallest solution is returned.
  //   segment_index0 - [in] index of segment where search begins
  //   segment_index1 - [in] index of segment where search ends
  //                         This segment is NOT searched.
  // Example:
  //   Search segments 3,4, and 5 for the point closest to (0,0,0).
  //   double t;
  //   ClosestPointTo( ON_3dPoint(0,0,0), &t, 3, 6 );
  // Returns:
  //   true if successful.
  bool ClosestPointTo( 
        const ON_3dPoint& test_point, 
        double* t, 
        int segment_index0, // index of segment where search begins
        int segment_index1 // index + 1 of segment where search stops
        ) const;

  // Description:
  //   Find a point on the polyline that is closest 
  //   to test_point.
  // Parameters:
  //   test_point - [in]
  // Returns:
  //   point on polyline.
  ON_3dPoint ClosestPointTo( 
       const ON_3dPoint& test_point
    ) const;

};

/*
Description:
  Join all contiguous polylines of an array of ON_Polylines.
Parameters:
  InPlines - [in] Array of polylines to be joined (not modified)
  OutPlines - [out] Resulting joined polylines and copies of polylines that were not joined to anything
                    are appended.
  join_tol - [in] Distance tolerance used to decide if endpoints are close enough. Curves or segments with length
                  less than join_tol are NOT collapsed and can cause problems when endpoints do not match exactly.
  kink_tol - [in] Angle in radians.  If > 0.0, then curves within join_tol will only be joined if the angle between them
                  is less than kink_tol. If <= 0, then the angle will be ignored and only join_tol will be used.
  bUseTanAngle - [in] If true, choose the best match using angle between tangents.  
                      If false, best match is the closest. This is used whether or not kink_tol is positive.
  bPreserveDirection - [in] If true, polylines endpoints will be compared to polylines startpoints.
                            If false, all start and endpoints will be compared, and copies of input 
                            curves may be reversed in output.
  key     -  [out] if key is not null, InPlines[i] was joined into OutPlines[key[i]].
Returns:
  Number of polylines added to OutPlines
Remarks:
  Closed polylines are copied to OutPlines. 
  Plines that cannot be joined to others are copied to OutPlines.  
  */
ON_DECL int ON_JoinPolylines(
  const ON_SimpleArray<const ON_Polyline*>& InPlines,
  ON_SimpleArray<ON_Polyline*>& OutPlines,
  double join_tol,
  double kink_tol,
  bool bUseTanAngle,
  bool bPreserveDirection = false,
  ON_SimpleArray<int>* key = 0
);


/*
Description:
  Join an array of lines into one or more polylines.
Parameters:
  InLines - [in] Array of lines to be joined (not modified)
  OutPolylines - [out] Array of resulting joined polylines.
  tolerance - [in] Distance tolerance used to decide if end points are close enough. 
                  Lines with length less than join_tol are NOT collapsed and can
                  cause problems when end points do not match exactly.
  bPreserveDirection - [in] If true, line end points will be compared to line start points.
                            If false, all start and end points will be compared, and copies
                            of input curves may be reversed in output.
  key     -  [out] if key is not nullptr, InLines[i] was joined into OutPolylines[key[i]].
Returns:
  Number of polylines added to OutPolylines
*/
ON_DECL int ON_JoinLines(
  const ON_SimpleArray<ON_Line>& InLines,
  ON_ClassArray<ON_Polyline>& OutPolylines,
  double tolerance,
  bool bPreserveDirection,
  ON_SimpleArray<int>* pKey
);

#endif
