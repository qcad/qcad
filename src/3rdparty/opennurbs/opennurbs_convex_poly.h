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

#if !defined(ON_CONVEX_POLY_INC_)
#define ON_CONVEX_POLY_INC_


// A Simplex in 3d
class ON_CLASS ON_3dSimplex
{
public:
  ON_3dSimplex();																							// An empty simplex
  explicit ON_3dSimplex(const ON_3dPoint& a);																	//  0-simplex in 3d
  ON_3dSimplex(const ON_3dPoint& a, const ON_3dPoint& b);										//  1-simplex
  ON_3dSimplex(const ON_3dPoint& a, const ON_3dPoint& b, const ON_3dPoint& c);			//  2-simplex
  ON_3dSimplex(const ON_3dPoint& a, const ON_3dPoint& b, const ON_3dPoint& c, const ON_3dPoint& d);		//  3-simplex

  ON_3dSimplex(const ON_3dSimplex& rhs) = default;
  ON_3dSimplex& operator=(const ON_3dSimplex& rhs) = default;
  ~ON_3dSimplex() = default;

  int Count() const;				// Number of Vertices <=4
  bool IsValid(double eps) const;			// true if the Vertices are affinely independent

  /* 
  Description:
    Evaluate a point in a Simplex from a barycentric coordinate b.
  Returns:
    The point
        b[0] * Vertex[0] + ... + b[Count()-1] * Vertex[Count()-1]
  Notes:
    If b[0] + ... + b[Count()-1] = 1 and b[i]>=0 for i=0 to Count()-1 then the
    returned point is on the simplex
  */
  ON_3dPoint Evaluate(const double* b) const;
  ON_3dPoint Evaluate(const ON_4dPoint& b) const;

  /*
  Description:
    Find Closest Point to this simplex from a base point P0 or the Origin.
    If true is returned then Evaluate(Bary) is the closest point on the Simplex.
  maximum_distance - optional upperbound on closest point.  If maximum_distance>=0 is specified and
            Dist(P0, Simplex)>maximum_distance then false is returned.
  */
  bool GetClosestPoint(const ON_3dPoint& P0, ON_4dPoint& Bary, double maximum_distance = ON_DBL_MAX) const;
  bool GetClosestPointToOrigin(ON_4dPoint& Bary) const;

  /*
  Count()     Volume() returns
  0           0.0
  1           0.0
  2          length >=0
  3          area   >=0
  4          volume >=0
  */
  double Volume() const;
  double SignedVolume() const; // returns ON_UNSET_VALUE if Count()<4 else the signed volume

  /*
    FaceNormal(noti) is the oriented face normal obtained by omitting vertex noti.
    FaceNormal returns ON_UNSET_VALUE if Count()<3 or Count()==4 noti not 0,1,2 or 3.
    FaceUnitNormal returns ON_UNSET_VALUE if Count()<3 or Count()==4 noti not 0,1,2 or 3 or if FaceNormal(noti)=Zero_Vector
  */
  ON_3dVector FaceNormal(int noti = 0) const;
  ON_3dVector FaceUnitNormal(int noti = 0) const;

  /*
  Edge vector from Vertex(e0) to Vertex(e1)
  */
  ON_3dVector Edge(int e0, int e1)const;

  /* If 0<=i<Count() modify this simplex by removing Vertex[i], specifically,  
     Vertex[k] is fixed for k<i  , and
     Vertex[k] <- Vertex[k+1] for i<= k= Count()-2
  */
  bool RemoveVertex(int i);

  /* append new vertex at end*/
  bool AddVertex(const ON_3dPoint&);

  /* Modify a vertex. i<Count() */
  bool SetVertex(int i, ON_3dPoint P);

  // Returns a Vertex or a reference to one when 0<=i<Count()
  ON_3dPoint& operator[](int);
  const ON_3dPoint& operator[](int i) const;

  ON_3dPoint Vertex(int i) const;
  ON_3dPoint& Vertex(int i);

  /* Maximum absolute value of vertex coordinates*/
  double MaximumCoordinate() const;

  /*
  Description:
    Get Simplex's 3d axis aligned bounding box.
  Returns:
    3d bounding box.
  */
  ON_BoundingBox BoundingBox() const;

  /*
  Description:
    Get simplexes 3d axis aligned bounding box or the
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

private:
  int m_n;									//  Number of points stored in m_V.  0<= m_n <= 4
  ON_3dVector m_V[4];

  bool Closest3plex(ON_4dPoint& Bary) const;
  bool Closest2plex(ON_4dPoint& Bary) const;
  bool Closest1plex(ON_4dPoint& Bary) const;
  static bool RoundBarycentricCoordinate(ON_4dPoint& Bary);
};


/*
This is a base class for a convex polytope in 3d space, i.e. the convex hull of a
finite set of points called vertices.

This is the base type in the implementation of the GJK algorithm
ClosestPoint(ON_ConvexPoly& A, ON_ConvexPoly& B, ...)

*/
class ON_CLASS ON_ConvexPoly
{
public:
  /*
  Returns: Number of vertices >=0
  */
  virtual int Count() const = 0;
   /* 
   Returns: Vertex[i] for i=0,...,Count()-1 
   */
  virtual ON_3dVector Vertex(int i) const = 0;

  /*
  Description:
    Let K be this ON_ConvexPoly then for a non-zero vector W the support Support(W) are point in K defined by
       arg max     x * W
        x \in K
     This  method returns one of these points in Support(W). 
     i0 is an optional initial index seed value.  It may provide a performance enhancement toward finding
     a minimizer.
   */
  ON_3dPoint Support(ON_3dVector W, int i0 =0) const
  {
    return Vertex(SupportIndex(W, i0));
  }

  /*
  Description:
  For any vector W there is a vertex that is Support(W)
  SupportIndex( W, i0) returns a vertex index for a vertex that is the support.
  Veretx( K.SupportIndex( W ))  = K.Support(W );
  */
  virtual int SupportIndex(ON_3dVector W, int i0=0) const = 0;

 /*
 Description:
   Points in a Convex Polytope are parameterized , not necessarily uniquely,
   by an ON_4dex of vertex indices and a 4d barycentric point B
    Evaluate(Ind, B ) = Sum_{i=0,..,3} Vertex(Ind[i])*B[i], where the sum is taken over i such that Ind[i]>=0
   If B is a barycentric coordinate
  		 B[i]>=0 and B[0] + B[1] + B[2] + B[3] = 1.0
   then Evaluate( Ind, B) is a point in the convex polytope
  */
  ON_3dPoint Evaluate(ON_4dex dex, ON_4dPoint B)const
  {
    ON_3dVector v(0, 0, 0);
    if (dex.i >= 0)
      v = B[0] * Vertex(dex.i);
    if (dex.j >= 0)
      v += B[1] * Vertex(dex.j);
    if (dex.k >= 0)
      v += B[2] * Vertex(dex.k);
    if (dex.l >= 0)
      v += B[3] * Vertex(dex.l);
    return v;
  };

  /*
Description:
  Computes the closest point on this convex polytope from a point P0.
Parameters:
  P0 - [in]  Base Point for closest point
  dex -[out] 
  bary - [out] Evaluate(dex,bary) is the closest point on this polyhedron
  maximum_distance - [in ] optional upper bound on distance

Returns:
   Returns true if a closest point is found and it is within optional maximum_distance bound;

Details:
  Setting maximum_distance can speedup the calculation in cases where dist(P0, *this)>maximum_distance.
*/
  bool GetClosestPoint( ON_3dPoint P0,
    ON_4dex& dex, ON_4dPoint& bary, 
    double maximum_distance = ON_DBL_MAX) const;

   // Expert version of GetClosestPoint. 
  // dex is used at  input to seed search algorithm.
  // the points of *this singled out by dex must define a nondegenerate simplex
  bool GetClosestPointSeeded(ON_3dPoint P0,
    ON_4dex& dex, ON_4dPoint& Bary,
    double maximum_distance = ON_DBL_MAX) const;

  /*
  Description:
    Computes a pair of points on *this and BHull that achieve the minimum distance between
    the two convex polytopes.
  Parameters:
    BHull - [in]  the other convex polytope 
    adex, bdex -[out]   Evaluate(adex,bary) is the closest point on this polyhedron
    bary - [out]        BHull.Evaluate(bdex,bary) is the closest point on BHull.
    maximum_distance - [in ] optional upper bound on distance

Returns:
   Returns true if a closest points are found and they are within optional maximum_distance bound;

Details:
  Setting maximum_distance can speedup the calculation in cases where dist(*this, BHull)>maximum_distance.
 */
  bool GetClosestPoint(const ON_ConvexPoly& BHull,
    ON_4dex& Adex, ON_4dex& Bdex, ON_4dPoint& bary, 
    double maximum_distance = ON_DBL_MAX) const;

  // Expert version of GetClosestPoint. 
// Adex and Bdex are used at  input to seed search algorithm.
// the points of this-Bhull singled out by Adex and Bdex must define a nondegenerate simplex
  bool GetClosestPointSeeded(const ON_ConvexPoly& BHull,
    ON_4dex& Adex, ON_4dex& Bdex, ON_4dPoint& bary,
    double maximum_distance = ON_DBL_MAX) const;

  /*
  Description:
    This is a bound on the collection of vertices.
    Vertex(i).MaximumCoordinate()<= MaximumCoordinate() for all i
  */
  virtual double MaximumCoordinate() const = 0;

  /*
  Description:
    A point represented by a ON_4dex D and a barycentric coordinate B
    can be put in a standard form so that non-negative elements of D are unique and
    corresponding coordinates are positive.  Furthermore, the non-negative
    indices are all listed before the unset ( negative ) values
  */
  static bool  Standardize(ON_4dex& D, ON_4dPoint& B);

  /*
  Returns:
    true if d[i]<n for i=0..3  a valid ON_4dex for a point in a ON_ConvexPolyBase with Count()=n 
  */
  static bool IsValid4DexN(const ON_4dex& D, int n)
  {
    for (int i = 0; i < 4; i++) {
      if (D[i] > n) return false;
    }
    return true;
  }
  bool IsValid4Dex(const ON_4dex& D) const { return IsValid4DexN(D, Count()); };

  virtual ~ON_ConvexPoly() {};
};

// 3d convex hull defined by an explicit collection of points called vertices.
// Note: vertices need not be extreme points

// WARNING:  Points are referenced not stored for optimal performance in'
//           some applications.
//           The list of points must remain alive and in there initial location 
//           For the duration of this object. 
//
// This is an improved version of ON_ConvexHullRef that includes support for 2d point lists.
class ON_CLASS ON_ConvexHullRefEx : public ON_ConvexPoly
{
public:
  ON_ConvexHullRefEx() { m_n = 0; m_dim = 0;  m_is_rat = false; m_stride = 3; };
  ON_ConvexHullRefEx(const ON_3dVector* V0, int  count);		// a 3d point array
  ON_ConvexHullRefEx(const ON_3dPoint* V0, int  count);		// a 3d point array
  ON_ConvexHullRefEx(const ON_4dPoint* V0, int count);			// a array of homogeneous points
  ON_ConvexHullRefEx(const double* v0, bool is_rat, int n, int dim=3);		// v0 is an array of 2d or 3d points in either euclidean or homogeneous  coordinates. dim<4.
  ON_ConvexHullRefEx(const double* v0, bool is_rat, int n, int dim , int stride);		// As above with a stride to the array. dim <4.

  void Initialize(const ON_3dVector* V0, int  count);
  void Initialize(const ON_4dPoint* V0, int  count);
  void Initialize(const double* V0, ON::point_style style, int  count);  // style must be either not_rational or homogeneous_rational = 2,

  int Count() const override { return m_n; }
  ON_3dVector Vertex(int j) const override;

  // Support map
  virtual int SupportIndex(ON_3dVector W, int i0) const override;
  virtual double MaximumCoordinate() const override;

  virtual ~ON_ConvexHullRefEx() override {};
private:

  int m_n = 0;
  int m_dim = 3;      // must be <4.  
  bool m_is_rat = false;
  const double* m_v = nullptr;
  int m_stride = 3;
};

// 3d convex hull defined by an explicit collection of points called vertices.
// Note: vertices need not be extreme points

// WARNING:  Points are referenced not stored for optimal performance in'
//           some applications.
//           The list of points must remain alive and in there initial location 
//           For the duration of this object.      
//      
// GBA 02-Nov-23 	This class  is DEPRECATED and will be removed in the future.
//					Use ON_ConvexHullRefEx instead.                                   
class ON_CLASS ON_ConvexHullRef : public ON_ConvexPoly
{
public:
  ON_ConvexHullRef() { m_n = 0; m_is_rat = false; m_stride = 3; };
  ON_ConvexHullRef(const ON_3dVector* V0, int  count);		// a 3d point array
  ON_ConvexHullRef(const ON_3dPoint* V0, int  count);		// a 3d point array
  ON_ConvexHullRef(const ON_4dPoint* V0, int count);			// a array of homogeneous points
  ON_ConvexHullRef(const double* v0, bool is_rat, int n);		// v0 is an array of 3dpoints or homo 4d points
  ON_ConvexHullRef(const double* v0, bool is_rat, int n, int stride);		// v0 is an array of 3dpoints or homo 4d points

  void Initialize(const ON_3dVector* V0, int  count);
	void Initialize(const ON_4dPoint* V0, int  count);
	void Initialize(const double* V0, ON::point_style style, int  count);  // style must be either not_rational or homogeneous_rational = 2,

  int Count() const override { return m_n; }
  ON_3dVector Vertex(int j) const override;

  // Support map
  virtual int SupportIndex(ON_3dVector W, int i0) const override;
  virtual double MaximumCoordinate() const override;

  virtual ~ON_ConvexHullRef() override {};
private:

  int m_n = 0;
  bool m_is_rat= false;
  const double* m_v = nullptr;
  int m_stride=3;
};

// 3d convex hull defined by an explicit collection of points called vertices.
// Note: vertices need not be extreme points     
class ON_CLASS ON_ConvexHullPoint2 : public ON_ConvexPoly
{
public:
  ON_ConvexHullPoint2() = default;
  ON_ConvexHullPoint2(int init_capacity) : m_Vert(init_capacity) {};

  virtual int Count() const override { return m_Vert.Count(); }
  virtual ON_3dVector Vertex(int j) const override { return m_Vert[j]; }

  // Support map
  virtual int SupportIndex(ON_3dVector W, int i0) const override {
    return Ref.SupportIndex(W, i0);
  };

  virtual double MaximumCoordinate() const override;

  virtual ~ON_ConvexHullPoint2() override {};

  int AppendVertex(const ON_3dPoint& P); // return index of new vertex.  must set Adjacent Indices.
	void Empty();

  bool SetCapacity(int vcnt) {
    m_Vert.SetCapacity(vcnt);
    return true;
  };

private:
  ON_ConvexHullRefEx Ref;
  ON_SimpleArray<ON_3dVector> m_Vert;
};



/*
	Compute Convex hull of 2d points
	Parameters:
	 Pnt - array of points.
	 HUll - the sequence Hull[0], HUll[1]...  ,*Hull.Last() == Hull[0] defines the convex hull with a positive orientation when  returns 2.
	 PntInd - optional array to be filled in so that Hull[i] = Pnt[ PntInd[i]] .
	Returns
	 dimension of the convex hull
	 2 - Hull is 2 dimensional
	 1 - Hull is a line segment
	 0 - hull is a point
	 <0 error
*/
ON_DECL
int ON_ConvexHull2d(const ON_SimpleArray<ON_2dPoint>& Pnt, ON_SimpleArray<ON_2dPoint>& Hull, ON_SimpleArray< int>* PntInd = nullptr);

#endif


