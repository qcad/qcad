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


#if !defined(OPENNURBS_IPOINT_INC_)
#define OPENNURBS_IPOINT_INC_

/*
A 2 dimensional point with integer coordinates.
Clear code will distinguish between situation where (x,y) is a 
location (ON_2iPoint) or a direction (ON_2iVector) and use 
the appropriate class.
*/
class ON_CLASS ON_2iPoint
{
public:
  // Default construction intentionally leaves x and y uninitialized.
  // Use something like
  //   ON_2iPoint pt(1,2);
  // or 
  //  ON_2iPoint pt = ON_2iPoint::Origin;
  // when you need an initialized ON_2iPoint.
  ON_2iPoint() = default;

  ~ON_2iPoint() = default;
  ON_2iPoint(const ON_2iPoint& ) = default;
  ON_2iPoint& operator=(const ON_2iPoint& ) = default;

  ON_2iPoint(
    int x,
    int y
  );

public:
  static const ON_2iPoint Origin; // (0,0)
  static const ON_2iPoint Unset;  // (ON_UNSET_INT_INDEX,ON_UNSET_INT_INDEX)

  /*
  Dictionary order compare.
  */
  static int Compare(
    const ON_2iPoint& lhs,
    const ON_2iPoint& rhs
  );

public:
  ON_2iPoint& operator+=(const class ON_2iVector&);
  ON_2iPoint& operator-=(const class ON_2iVector&);

  // It is intentional that points are not added to points to encourage
  // code that is clear about what is a location and what is displacement.

public:
  /*
  For those times when a location was incorrectly represented by a vector.
  It is intentional that there is not an ON_2iPoint constructor from an ON_2iVector.
  */
  static const ON_2iPoint FromVector(const class ON_2iVector& v);

  static const ON_2iPoint From2dex(const class ON_2dex& src);

public:
  /*
  Returns:
    (0 == x && 0 == y)
  */
  bool IsOrigin() const;

  /*
  Returns:
    (ON_UNSET_INT_INDEX == x || ON_UNSET_INT_INDEX ==y)
  */
  bool IsSet() const;

public:
  ON__INT32 x;
  ON__INT32 y;
};

ON_DECL
bool operator==(const ON_2iPoint&, const ON_2iPoint&);

ON_DECL
bool operator!=(const ON_2iPoint&, const ON_2iPoint&);


/*
A 2 dimensional vector with integer coordinates.
Clear code will distinguish between situation where (x,y) is a 
location (ON_2iPoint) or a direction (ON_2iVector) and use 
the appropriate class.
*/
class ON_CLASS ON_2iVector
{
public:
  // Default construction intentionally leaves x and y uninitialized.
  // Use something like
  //   ON_2iVector pt(1,2);
  // or 
  //  ON_2iVector pt = ON_2iVector::Zero;
  // when you need an initialized ON_2iVector.
  ON_2iVector() = default;

  ~ON_2iVector() = default;
  ON_2iVector(const ON_2iVector& ) = default;
  ON_2iVector& operator=(const ON_2iVector& ) = default;

  ON_2iVector(
    int x,
    int y
  );
  
  /*
  For those times when a direction was incorrectly represented by a point.
  It is intentional that there is not an ON_2iVector constructor from an ON_2iPoint.
  */
  static const ON_2iVector FromPoint(const class ON_2iPoint& p);

  static const ON_2iVector From2dex(const class ON_2dex& src);

public:
  static const ON_2iVector Zero; // (0,0)
  static const ON_2iVector UnitX; // (1,0)
  static const ON_2iVector UnitY; // (0,1)
  static const ON_2iVector Unset;  // (ON_UNSET_INT_INDEX,ON_UNSET_INT_INDEX)
  
  /*
  Dictionary order compare.
  */
  static int Compare(
    const ON_2iVector& lhs,
    const ON_2iVector& rhs
  );

public:
  ON_2iVector& operator+=(const class ON_2iVector&);
  ON_2iVector& operator-=(const class ON_2iVector&);
  ON_2iVector& operator*=(int);

  ON_2iVector operator-() const;
  
public:
  /*
  Returns:
    (0 == x && 0 == y)
  */
  bool IsZero() const;

  /*
  Returns:
    IsSet() && (0 != x || 0 != y)
  */
  bool IsNotZero() const;

  /*
  Returns:
    (ON_UNSET_INT_INDEX == x || ON_UNSET_INT_INDEX ==y)
  */
  bool IsSet() const;

public:
  ON__INT32 x;
  ON__INT32 y;
};

ON_DECL
bool operator==(const ON_2iVector&, const ON_2iVector&);

ON_DECL
bool operator!=(const ON_2iVector&, const ON_2iVector&);

ON_DECL
ON_2iPoint operator+(const ON_2iPoint&, const ON_2iVector&);

ON_DECL
ON_2iPoint operator-(const ON_2iPoint&, const ON_2iVector&);

ON_DECL
ON_2iVector operator+(const ON_2iVector&, const ON_2iVector&);

ON_DECL
ON_2iVector operator-(const ON_2iVector&, const ON_2iVector&);

ON_DECL
ON_2iVector operator*(int, const ON_2iVector&);

class ON_CLASS ON_2iBoundingBox
{
public:
  // Default construction intentionally leaves m_min and m_max uninitialized.
  // Use something like
  //   ON_2iBoundingBox bbox(min_pt,max_pt);
  // or 
  //  ON_2iBoundingBox bbox = ON_2iBoundingBox::Unset;
  ON_2iBoundingBox() = default;

  ~ON_2iBoundingBox() = default;
  ON_2iBoundingBox(const ON_2iBoundingBox& ) = default;
  ON_2iBoundingBox& operator=(const ON_2iBoundingBox& ) = default;

  ON_2iBoundingBox(
    const class ON_2iPoint bbox_min,
    const class ON_2iPoint bbox_max
  );

public:
  static const ON_2iBoundingBox Zero; // (ON_2iPoint::Origin,ON_2iPoint::Origin);
  static const ON_2iBoundingBox Unset;  // (ON_2iPoint::Unset,ON_2iPoint::Unset)
  
public:
  /*
  Returns:
    m_min.IsSet() && m_max.IsSet() && m_min.x <= m_max.x && m_min.y <= m_max.y.
  */
  bool IsSet() const;

  const ON_2iPoint Min() const;
  const ON_2iPoint Max() const;

public:
  ON_2iPoint m_min;
  ON_2iPoint m_max;
};

ON_DECL
bool operator==(const ON_2iBoundingBox&, const ON_2iBoundingBox&);

ON_DECL
bool operator!=(const ON_2iBoundingBox&, const ON_2iBoundingBox&);

/*
Class ON_2iSize
  For those situations where a Windows SDK SIZE or MFC CSize 
  value needs to be used in code that does not link with MFC.
*/
class ON_CLASS ON_2iSize
{
public:
  // Default construction intentionally leaves x and y uninitialized.
  // Use something like
  //   ON_2iSize pt(1,2);
  // or 
  //  ON_2iSize pt = ON_2iSize::Zero;
  // when you need an initialized ON_2iSize.
  ON_2iSize() = default;

  ~ON_2iSize() = default;
  ON_2iSize(const ON_2iSize& ) = default;
  ON_2iSize& operator=(const ON_2iSize& ) = default;

  ON_2iSize(
    int cx,
    int cy
  );

  /*
  Dictionary compare.
  Returns: 
  -1: lhs < rhs
   0: lsh == rsh
  +1: lhs > rhs
  */
  static int Compare(
    const ON_2iSize& lhs,
    const ON_2iSize& rhs
  );

  /*
  Dictionary compare.
  Returns: 
  -1: lhs < rhs
   0: lsh == rsh
  +1: lhs > rhs
  */
  static int ComparePointer(
    const ON_2iSize* lhs,
    const ON_2iSize* rhs
  );

public:
  static const ON_2iSize Zero;  // (0,0)
  static const ON_2iSize Unset; // (ON_UNSET_INT_INDEX,ON_UNSET_INT_INDEX)
  
public:
  /*
  Returns:
    true if both cx and cy are 0.
  */
  bool IsZero() const;

  /*
  Returns:
    true if neither cx nor cy are ON_UNSET_INT_INDEX.
  */
  bool IsSet() const;
  
public:
  ON__INT32 cx;
  ON__INT32 cy;
};

ON_DECL
bool operator==(
  const ON_2iSize& lhs,
  const ON_2iSize& rhs
  );

ON_DECL
bool operator!=(
  const ON_2iSize& lhs,
  const ON_2iSize& rhs
  );

#if defined(ON_DLL_TEMPLATE)

ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_2iSize>;

#endif

/*
Class ON_4iRect
  For those situations where a Windows SDK RECT or MFC CRect 
  value needs to be used in code that does not link with MFC.
  If you want a traditional bounding box, use ON_2dBoundingBox.
*/
class ON_CLASS ON_4iRect
{
public:
  // Default construction intentionally leaves x and y uninitialized.
  // Use something like
  //   ON_4iRect pt(1,2,3,4);
  // or 
  //  ON_4iRect pt = ON_4iRect::Zero;
  // when you need an initialized ON_4iRect.
  ON_4iRect() = default;

  ~ON_4iRect() = default;
  ON_4iRect(const ON_4iRect& ) = default;
  ON_4iRect& operator=(const ON_4iRect& ) = default;

  ON_4iRect(
  int left,
  int top,
  int right,
  int bottom
  );

  ON_4iRect(const ON_2iPoint topLeft, const ON_2iPoint& bottomRight);
  ON_4iRect(const ON_2iPoint& point, const ON_2iSize& size);

public:
  static const ON_4iRect Zero;  // (0,0,0,0)
  static const ON_4iRect Unset; // (ON_UNSET_INT_INDEX,ON_UNSET_INT_INDEX,ON_UNSET_INT_INDEX,ON_UNSET_INT_INDEX)

public:
  /*
  Returns:
    true if all of left, top, right, and bottom are set to 0.
  */
  bool IsZero() const;

  void SetZero();

  /*
  Returns:
    true if none of left, top, right, or bottom is set to ON_UNSET_INT_INDEX
  */
  bool IsSet() const;

  int Width(void) const;
  int Height(void) const;

  const ON_2iSize Size(void) const;
  
  const ON_2iPoint CenterPoint(void) const;
  const ON_2iPoint TopLeft(void) const;
  const ON_2iPoint BottomRight(void) const;

  bool  IntersectRect(const ON_4iRect* r1, const ON_4iRect* r2);
  bool  IntersectRect(const ON_4iRect& r1, const ON_4iRect& r2);

  bool IsRectEmpty(void) const;
  bool IsRectNull(void) const;
  void SetRectEmpty(void) { *this = Zero; }
  void SetRect(int l, int t, int r, int b);

  bool PtInRect(const ON_2iPoint& pt) const;

  void OffsetRect(int, int);
  void OffsetRect(const ON_2iVector&);
  void InflateRect(int, int);
  void InflateRect(int, int, int, int);
  void DeflateRect(int, int);
  bool SubtractRect(const ON_4iRect* rect1, const ON_4iRect* rect2);

  void NormalizeRect();

public:
  // NOTE WELL:
  // Windows 2d integer device coordinates have a 
  // strong y-down bias and it is common for top < bottom.
  // General 2d bounding boxes have a strong lower < upper / min < max bias.
  // Take care when converting between ON_2iBoundingBox and ON_4iRect.
  // It is intentional that no automatic conversion between bounding box
  // and ON_4iRect is supplied because each case must be carefully considered.
  ON__INT32 left;
  ON__INT32 top;
  ON__INT32 right;
  ON__INT32 bottom;
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_4iRect>;
#endif


ON_DECL
bool operator==(const ON_4iRect&, const ON_4iRect&);

ON_DECL
bool operator!=(const ON_4iRect&, const ON_4iRect&);

#endif
