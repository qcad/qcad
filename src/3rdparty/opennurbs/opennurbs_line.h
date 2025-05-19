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

#if !defined(ON_LINE_INC_)
#define ON_LINE_INC_

class ON_CLASS ON_Line
{
public:

  static const ON_Line ZeroLine;   // (ON_3dPoint::Origin, ON_3dPoint::Origin)
  static const ON_Line UnsetLine;  // (ON_3dPoint::UnsetPoint, ON_3dPoint::UnsetPoint)
  static const ON_Line NanLine;    // (ON_3dPoint::NanPoint, ON_3dPoint::NanPoint)

  // Default constructor sets from = to = ON_3dPoint::Origin
  ON_Line();
  ~ON_Line();

  explicit ON_Line(
    ON_3dPoint start,
    ON_3dPoint end 
    );

  explicit ON_Line(
    ON_2dPoint start,
    ON_2dPoint end 
    );

  /*
  Returns:
    True if from != to and both from and to are valid.
  */
  bool IsValid() const;

  // line[0] = start point line[1] = end point
  ON_3dPoint& operator[](int);
  const ON_3dPoint& operator[](int) const;


  // Description:
  //   Create a line from two points.
  // Parameters:
  //   start - [in] point at start of line segment
  //   end - [in] point at end of line segment
  // Returns:
  //   true if start and end are distinct points.
  bool Create( 
    const ON_3dPoint start, 
    const ON_3dPoint end
    );
  bool Create( 
    const ON_2dPoint start, 
    const ON_2dPoint end
    );

  /*
  Description: 
    Get line's 3d axis aligned bounding box.
  Returns:
    3d bounding box.
  */
  ON_BoundingBox BoundingBox() const;

  /*
  Description:
    Get line's 3d axis aligned bounding box or the
    union of the input box with the object's bounding box.
  Parameters:
    bbox - [in/out] 3d axis aligned bounding box
    bGrowBox - [in] (default=false) 
      If true, then the union of the input bbox and the 
      object's bounding box is returned in bbox.  
      If false, the object's bounding box is returned in bbox.
  Returns:
    true if object has bounding box and calculation was successful.
  */
  bool GetBoundingBox(
         ON_BoundingBox& bbox,
         int bGrowBox = false
         ) const;

  /*
	Description:
    Get tight bounding box.
	Parameters:
		tight_bbox - [in/out] tight bounding box
		bGrowBox -[in]	(default=false)			
      If true and the input tight_bbox is valid, then returned
      tight_bbox is the union of the input tight_bbox and the 
      line's tight bounding box.
		xform -[in] (default=nullptr)
      If not nullptr, the tight bounding box of the transformed
      line is calculated.  The line is not modified.
	Returns:
    True if a valid tight_bbox is returned.
  */
	bool GetTightBoundingBox( 
			ON_BoundingBox& tight_bbox, 
      bool bGrowBox = false,
			const ON_Xform* xform = nullptr
      ) const;

  /*
  Description:
    Get a plane that contains the line.
  Parameters:
    plane - [out] a plane that contains the line.  The origin
       of the plane is at the start of the line.  The distance
       from the end of the line to the plane is <= tolerance.
       If possible a plane parallel to the world xy, yz or zx
       plane is returned.
    tolerance - [in]
  Returns:
    true if a coordinate of the line's direction vector is
    larger than tolerance.
  */
  bool InPlane( ON_Plane& plane, double tolerance = 0.0 ) const;

  // Returns:
  //   Length of line
  double Length() const;

  // Returns:
  //   direction vector = line.to - line.from
  // See Also:
  //   ON_Line::Tangent
  ON_3dVector Direction() const;

  // Returns:
  //   Unit tangent vector.
  // See Also:
  //   ON_Line::Direction
  ON_3dVector Tangent() const;

  /*
  Description:
    Evaluate point on (infinite) line.
  Parameters:
    t - [in] evaluation parameter. t=0 returns line.from
             and t=1 returns line.to.
  Returns:
    (1-t)*line.from + t*line.to.
  See Also:
    ON_Line::Direction
    ON_Line::Tangent
  */
  ON_3dPoint PointAt( 
    double t 
    ) const;

  /*
  Description:
    Find the point on the (infinite) line that is
    closest to the test_point.
  Parameters:
    test_point - [in]
    t - [out] line.PointAt(*t) is the point on the line 
              that is closest to test_point.
  Returns:
    true if successful.
  */
  bool ClosestPointTo( 
    const ON_3dPoint& test_point, 
    double* t
    ) const;

  /*
  Description:
    Find the point on the (infinite) line that is
    closest to the test_point.
  Parameters:
    test_point - [in]
  Returns:
    The point on the line that is closest to test_point.
  */
  ON_3dPoint ClosestPointTo( 
    const ON_3dPoint& test_point
    ) const;

  /*
  Description:
    Find the point on the (infinite) line that is
    closest to the test_point.
  Parameters:
    test_point - [in]
  Returns:
    distance from the point on the line that is closest
    to test_point.
  See Also:
    ON_3dPoint::DistanceTo
    ON_Line::ClosestPointTo
  */
  double DistanceTo( ON_3dPoint test_point ) const;


  /*
  Description:
    Finds the shortest distance between the line as a finite
    chord and the other object.
  Parameters:
    P - [in]
    L - [in] (another finite chord)
  Returns:
    A value d such that if Q is any point on 
    this line and P is any point on the other object, 
    then d <= Q.DistanceTo(P).
  */
  double MinimumDistanceTo( const ON_3dPoint& P ) const;
  double MinimumDistanceTo( const ON_Line& L ) const;

  /*
  Description:
    Finds the longest distance between the line as a finite
    chord and the other object.
  Parameters:
    P - [in]
    L - [in] (another finite chord)
  Returns:
    A value d such that if Q is any point on this line and P is any
    point on the other object, then d >= Q.DistanceTo(P).
  */
  double MaximumDistanceTo( const ON_3dPoint& P ) const;
  double MaximumDistanceTo( const ON_Line& other ) const;


  /*
  Description:
    Quickly determine if the shortest distance from
    this line to the other object is greater than d.
  Parameters:
    d - [in] distance (> 0.0)
    P - [in] 
    L - [in] 
  Returns:
    True if if the shortest distance from this line
    to the other object is greater than d.
  */
  bool IsFartherThan( double d, const ON_3dPoint& P ) const;
  bool IsFartherThan( double d, const ON_Line& L ) const;


  // For intersections see ON_Intersect();

  // Description:
  //   Reverse line by swapping from and to.
  void Reverse();

  bool Transform( 
    const ON_Xform& xform
    );

  // rotate line about a point and axis
  bool Rotate(
        double sin_angle,
        double cos_angle,
        const ON_3dVector& axis_of_rotation,
        const ON_3dPoint& center_of_rotation
        );

  bool Rotate(
        double angle_in_radians,
        const ON_3dVector& axis_of_rotation,
        const ON_3dPoint& center_of_rotation
        );

  bool Translate(
        const ON_3dVector& delta
        );

  // Maximum absolute coordinate of from and to.
  double MaximumCoordinate() const; 


public:
  ON_3dPoint from; // start point
  ON_3dPoint to;   // end point
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_Line>;
#endif

/*
Returns:
  True if a and be are identical and no coordinate is a nan.
*/
ON_DECL
bool operator==(const ON_Line& a, const ON_Line& b);

/*
Returns:
  True if a and be are not identical.
Remarks:
  If a nan is involved in every coordinate compare,
  the result will be false.
*/
ON_DECL
bool operator!=(const ON_Line& a, const ON_Line& b);



class ON_CLASS ON_Triangle
{
public:

	static const ON_Triangle ZeroTriangle;   // {ON_3dPoint::Origin, ON_3dPoint::Origin, ON_3dPoint::Origin}
	static const ON_Triangle UnsetTriangle;  // {ON_3dPoint::UnsetPoint, ON_3dPoint::UnsetPoint, ON_3dPoint::UnsetPoint}
	static const ON_Triangle NanTriangle;    // {ON_3dPoint::NanPoint, ON_3dPoint::NanPoint, ON_3dPoint::NanPoint}
												
	ON_Triangle() = default;				// Default constructor is uninitialized
	ON_Triangle(const ON_3dPoint vertices[3]);
	ON_Triangle(const ON_3dPoint& a, const ON_3dPoint& b, const ON_3dPoint& c);
	ON_Triangle(double x);					// Allows Triangle(0.0)  ZeroTriangle 
  ON_Triangle(const double vertices[9]);

	ON_Triangle(const ON_Triangle& tri) = default;
	ON_Triangle& operator=(const ON_Triangle& tri) = default;
	~ON_Triangle() = default;

	operator ON_3dPoint*();
	operator const ON_3dPoint*() const;

	/*
	Returns:
		True if m_V[i].IsValid() for all i
	*/
	bool IsValid() const;

	// Triangle[i] = Triangle.m_V[i] 
	ON_3dPoint& operator[](int);
	const ON_3dPoint& operator[](int) const;


	// Description:
	//   Create a Triangle from three points.
	// Parameters:
	//   vertices - [in] vertices
	void Create(const ON_3dPoint vertices[3]);

	// Description:
	//   Create a Triangle from three points.
	// Parameters:
	//   a,b,c - [in] vertices
	void Create(const ON_3dPoint& a, const ON_3dPoint& b, const ON_3dPoint& c);

	/*
	Description:
		Get Triangles 3d axis aligned bounding box.
	Returns:
		3d bounding box.
	*/
	ON_BoundingBox BoundingBox() const;

	/*
	Description:
		Get line's 3d axis aligned bounding box or the
		union of the input box with the object's bounding box.
	Parameters:
		bbox - [in/out] 3d axis aligned bounding box
		bGrowBox - [in] (default=false)
			If true, then the union of the input bbox and the
			object's bounding box is returned in bbox.
			If false, the object's bounding box is returned in bbox.
	Returns:
		true if object has bounding box and calculation was successful.
	*/
	bool GetBoundingBox(
		ON_BoundingBox& bbox,
		int bGrowBox = false
	) const;

	/*
	Description:
		Get tight bounding box with respect to a given frame
	Parameters:
		tight_bbox - [in/out] tight bounding box
		bGrowBox -[in]	(default=false)
			If true and the input tight_bbox is valid, then returned
			tight_bbox is the union of the input tight_bbox and the
			line's tight bounding box.
		xform -[in] (default=nullptr)
			If not nullptr, the tight bounding box of the transformed
			triangle is calculated.  The triangle is not modified.
	Returns:
			True if a valid tight_bbox is returned.
	*/
	bool GetTightBoundingBox(
		ON_BoundingBox& tight_bbox,
		bool bGrowBox = false,
		const ON_Xform* xform = nullptr
	) const;

  // Returns:
  //   Index of edge opposite to m_V[i] that is longest.
  //   When lengths are equal, lowest index has priority.
  unsigned char LongestEdge() const;

  // Returns:
  //   Index of edge opposite to m_V[i] that is shortest.
  //   When lengths are equal, lowest index has priority.
  unsigned char ShortestEdge() const;

	// Returns:
	//   Edge opposite m_V[i]
	// Specifically, 
	//   ON_Line( m_V[(i+1)%3 ], m_V[(i+2)%3 ] )
	ON_Line Edge(int i) const;

	// Returns:
	//   true if Area()< tol
	// Note:
	//	Recall Area = .5* base * height.  So this degeneracy tests for 
	//  a combination long enough and high enough.
	// See Also:
	//   ON_Triangle::Area()
	bool IsDegenerate(double tol = ON_ZERO_TOLERANCE) const;

	// Returns:
	//   Area of triangle
	double Area() const;


	// Returns:
	//   N = ( b-a) X ( c-a)
	// where a,b,c are the vertices 
	// See Also:
	//   ON_Triangle UnitNormal()
	ON_3dVector Normal() const;

	// Returns:
	//   Normal().Unitize()
	// Notes:
	//		Ensure !IsDegenerate() to guarantee that UnitNormal().Length()==1
	//		and the result is not just a bunch of noise.  Can return zero vector 
	//    in some degenerate cases.
	ON_3dVector UnitNormal() const;

	// Returns:
	//	Plane containing Triangle with normal given by UnitNormal().
	// Notes:
	//	Ensure !IsDegenerate() to guarantee meaningful result
	ON_PlaneEquation PlaneEquation() const;

	/*
	Description:
		Evaluate point on triangle.
	Parameters:
		s1, s2 - [in] evaluation parameter. 
	Returns:
		(1-s1-s2)* m_V[0] + s1*m_V[1] + s2*m_V[2]
	Notes:
		Point is in the triangle iff s1>=0, s2>=0 and s1 + s2<=1.
		Other values produce points on the plane of the triangle.
	*/
	ON_3dPoint PointAt(
		double s1, double s2
	) const;

	// Returns:
	//	Evaluation of PointAt(1/3.0, 1/3.0);
	ON_3dPoint Centroid() const;

	/*
	Description:
		Find the point on the triangle that is
		closest to the test_point.
	Parameters:
		test_point - [in]
		s1, s2 - [out]	PointAt( *s1, *s2) is the point on the
										triangle  closest to test_point.
	Returns:
		true if successful.
	*/
	bool ClosestPointTo(
		const ON_3dPoint& test_point,
		double* s1, double *s2
	) const;

  	/*
	Description:
		Find the point that is closest to the test_point.
	Parameters:
		test_point - [in]
    constrainInside[in] - if true, variable are inside triangle
		s1, s2 - [out]	PointAt( *s1, *s2) is the point on the
										triangle  closest to test_point.

	Returns:
		true if successful.
	*/
	bool GetBarycentricCoordinates(
		const ON_3dPoint& test_point,
    bool constrainInside,
		double* s1, double *s2
	) const;

	/*
	Description:
		Find the point on the triangle that is
		closest to the test_point.
	Parameters:
		test_point - [in]
	Returns:
		The point on the line that is closest to test_point.
	*/
	ON_3dPoint ClosestPointTo(
		const ON_3dPoint& test_point
	) const;

	/*
	Description:
		Find the point on the triangle that is
		closest to the test_point.
	Parameters:
		test_point -[in]
	Returns:
		distance from the point on triangle that is closest
		to test_point.
	See Also:
	ON_3dPoint::DistanceTo
	ON_Line::ClosestPointTo
	*/
	double DistanceTo(const ON_3dPoint& test_point) const;


	// Description:
	//   Reverse endpoints of Edge[i].
	void Reverse(int i);

	bool Transform(
		const ON_Xform& xform
	);

	// rotate line about a point and axis
	bool Rotate(
		double sin_angle,
		double cos_angle,
		const ON_3dVector& axis_of_rotation,
		const ON_3dPoint& center_of_rotation
	);

	bool Rotate(
		double angle_in_radians,
		const ON_3dVector& axis_of_rotation,
		const ON_3dPoint& center_of_rotation
	);

	bool Translate(
		const ON_3dVector& delta
	);

  // Description:
  //   Split the triangles into two, by choosing an edge and a new point that will appear along the edge.
  // Parameters:
  //   edge - [in] Edge index as defined in Edge()
  //   pt - [in] Point to add as splitter along edge
  //   out_a - [out] First triangle
  //   out_b - [out] Second triangle
  void Split(unsigned char edge, ON_3dPoint pt, ON_Triangle& out_a, ON_Triangle& out_b) const;

  // Description:
  //   Flip the normal of the triangle, by swapping the points of an edge.
  // Parameters:
  //   edge - [in] The edge, as defined in the Edge() method. I.e., edge 0 swaps m_V[1] and m_V[2]
  void Flip(unsigned char edge = 0);

  // Description:
  //   Circle the order of points in the triangle, without any influence to any geometric property.
  // Parameters:
  //   move - [in] Amounts of rotations in the order of the three points.
  //               By means of examples, "move" of 1 will move m_V[0] to m_V[1],
  //               m_V[1] to m_V[2] and m_V[2] to m_V[0].
  void Spin(unsigned char move);

public:
	ON_3dPoint m_V[3]; // vertices
};

/*
Returns:
True if a and be are identical and no coordinate is a nan.
*/
ON_DECL
bool operator==(const ON_Triangle& a, const ON_Triangle& b);

/*
Returns:
True if a and be are not identical.
Remarks:
If a nan is involved in every coordinate compare,
the result will be false.
*/
ON_DECL
bool operator!=(const ON_Triangle& a, const ON_Triangle& b);

#endif
