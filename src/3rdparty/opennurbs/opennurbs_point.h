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

////////////////////////////////////////////////////////////////
//
//   defines double precision point, vector, and array classes
//
////////////////////////////////////////////////////////////////
#if !defined(ON_POINT_INC_)
#define ON_POINT_INC_

class ON_BoundingBox;
class ON_Xform;
class ON_Line;
class ON_Plane;

class ON_2dPoint;
class ON_3dPoint;
class ON_4dPoint;

class ON_2dVector;
class ON_3dVector;

class ON_2fVector;
class ON_3fVector;

class ON_Interval;

////////////////////////////////////////////////////////////////
//
//   ON_Interval
//
class ON_CLASS ON_Interval
{
public:
  static const ON_Interval EmptyInterval; // (ON_UNSET_VALUE,ON_UNSET_VALUE)
  static const ON_Interval ZeroToOne; // (0.0, 1.0)
  static const ON_Interval ZeroToTwoPi; // (0.0, 2.0*ON_PI)
  static const ON_Interval Nan; // (ON_DBL_QNAN,ON_DBL_QNAN)
  
public:
  // The default constructor creates ON_Interval::EmptyInterval (ON_UNSET_VALUE,ON_UNSET_VALUE)
  ON_Interval();
  ~ON_Interval() = default;
  ON_Interval(const ON_Interval&) = default;
  ON_Interval& operator=(const ON_Interval&) = default;

  ON_Interval(double t0,double t1);

  /*
  Returns:
    ON_Interval(t,t).
  */
  static const ON_Interval Singleton(double t);

public:
  // Interval = (m_t[0], m_t[1])
  double m_t[2];

#if defined(OPENNURBS_WALL)
  // Goal is to eventually require = as the only way to modify ON_Interval values.
  ON_DEPRECATED_MSG("Use interval = ON_Interval::EmptyInterval;")
#endif
  void Destroy();

  /*
  Description:
    Sets interval to [t0,t1]
  Parameters:
    t0 - [in]
    t1 - [in]
  See Also:
    ON_Interval::ON_Interval( double, double )
  */
  void Set(
    double t0, 
    double t1
    );

  /// <summary>
  /// Convert a normalized parameter to an interval value.
  /// The interval can be increasing, decreasing, or a singleton.
  /// </summary>
  /// <param name="normalized_parameter">
  /// The normalized parameter can have any value.
  /// </param>
  /// <returns>
  /// a*(1.0-normalized_parameter) + b*normalized_parameter
  /// where a = the value at the beginning of this interval
  /// and b = the value at the end of this interval.
  /// </returns>
  double ParameterAt (
    double normalized_parameter
    ) const; 

  /// <summary>
  /// Convert a a pair of normalized parameter values to 
  /// a pair of interval values.
  /// This interval can be increasing, decreasing, or a singleton.
  /// </summary>
  /// <param name="normalized_interval">
  /// The normalized parameters can have any value.
  /// </param>
  /// <returns>
  /// a*(1.0-normalized_parameter) + b*normalized_parameter
  /// where a = the value at the beginning of this interval
  /// and b = the value at the end of this interval.
  ON_Interval ParameterAt (
    ON_Interval normalized_interval
    ) const; 

  /// <summary>
  /// Returns the interval's value at a clamped normalized parameter.
  /// This interval may be increasing, decreasing, or a singleton.
  /// </summary>
  /// <param name="normalized_parameter">
  /// normalized_parameter may have any value but it is clamped
  /// to be between 0 and 1 before the corresponding interval
  /// value is evaluated.
  /// </param>
  /// <returns>
  /// Set a = the value at the beginning of this interval and
  /// b = the value at the end of this interval.
  /// If a, b or normalized_parameter is unset or nan, ON_DBL_QNAN is returned. 
  /// If normalized_parameter &lt;= 0.0, a is returned.
  /// If normalized_parameter &gt;= 1.0, b is returned.
  /// Otherwise (1.0-normalized_parameter)*a + normalized_parameter*b is returned.
  /// </returns>
  double ClampedParameterAt(
    double normalized_parameter
  ) const;
  
  /*
  Description:
    Convert interval value, or pair of values, to normalized parameter.
  Parameters:
    interval_parameter - [in] value in interval
  Returns:
    Normalized parameter x so that 
    min*(1.0-x) + max*x = interval_parameter.
  See Also:
    ON_Interval::ParameterAt
  */
  double NormalizedParameterAt (
    double interval_parameter
    ) const;
  ON_Interval NormalizedParameterAt (
    ON_Interval interval_parameter
    ) const;

  /// <summary>
  /// Returns a clamped normalized parameter from an interval value.
  /// This interval may be increasing, decreasing, or a singleton.
  /// </summary>
  /// <param name="interval_parameter">
  /// interval_parameter may have any value but it is clamped
  /// to be in the interval before the normalized parameter is evaluated.
  /// </param>
  /// <returns>
  /// Set a = the value at the beginning of this interval and
  /// b = the value at the end of this interval.
  /// If a, b or interval_parameter is unset or nan, ON_DBL_QNAN is returned. 
  /// If interval_parameter is in this interval, the corresponding normalized
  /// parameter is returned.
  /// If interval_parameter is outside the interval, the normalized parameter for
  /// the end closest to interval_parameter is returned.
  /// </returns>
  double ClampedNormalizedParameterAt(
    double interval_parameter
  ) const;


  /// <summary>
  /// Transforms a parameter from the current interval to the target interval.
  /// It is effectively target.ParameterAt(this.NormalizedParameterAt(t))
  /// with additional checks when t is very close to the end of this interval.
  /// It is useful when the calculation of t may have introduced rounding errors.
  ///
  /// Specifically, there are cases where t is extremely close to and end of
  /// this interval, target.ParameterAt(this.NormalizedParameterAt(t))
  /// will return values that are very near but not exactly at the end of
  /// the target interval, and
  /// TransformParameterTo() will return a parameter at the exact end of the
  /// target interval. This behavior is desired in some cases like
  /// converting ON_PolyCurve parameters to NurbsForm parameters when the
  /// polycurve parameter is at a segment.
  /// </summary>
  /// <param name="target">Target interval</param>
  /// <param name="t">Input parameter</param>
  /// <returns>
  /// The input parameter in the target interval.
  /// Returns input paramter unchanged if both intervals are identical.
  /// Returns ON_DBL_QNAN if either interval is not valid.
  /// </returns>
  double TransformParameterTo(const ON_Interval& target, double t) const;


  double& operator[](int); // returns (index<=0) ? m_t[0] : m_t[1]
  double operator[](int) const; // returns (index<=0) ? m_t[0] : m_t[1]
  double& operator[](unsigned int); // returns (index<=0) ? m_t[0] : m_t[1]
  double operator[](unsigned int) const; // returns (index<=0) ? m_t[0] : m_t[1]

  double Min() const; // returns smaller of m_t[0] and m_t[1]
  double Max() const; // returns larger of m_t[0] and m_t[1]
  double Mid() const; // returns 0.5*(m_t[0] + m_t[1])
  double Length() const;  // returns signed length, m_t[1]-m_t[0]

  bool IsIncreasing() const; // returns true if m_t[0] < m_t[1]
  bool IsDecreasing() const; // returns true if m_t[0] > m_t[0];
  bool IsInterval() const;   // returns truc if m_t[0] != m_t[1]
  bool IsSingleton() const;  // returns true if m_t[0] == m_t[1] != ON_UNSET_VALUE
  bool IsEmptyInterval() const;   // returns true if m_t[0] == m_t[1] == ON_UNSET_VALUE
  bool IsValid() const;      // returns ON_IsValid(m_t[0]) && ON_IsValid(m_t[1])

#if defined(OPENNURBS_WALL)
  ON_DEPRECATED_MSG("Use IsEmptyInterval()")
#endif
  bool IsEmptySet() const;   // returns true if m_t[0] == m_t[1] == ON_UNSET_VALUE

	bool MakeIncreasing();		// returns true if resulting interval IsIncreasing() 

  /*
  Description:
    A well ordered dictionary compare function that is nan aware and can
    be used for robust sorting.
  */
  static int Compare(
    const ON_Interval& lhs, 
    const ON_Interval& rhs
  );


  /*
  Returns:
    True if (lhs.m_t[0] != rhs.m_t[0]) or (lhs.m_t[1] != rhs.m_t[1]) and
    no values are nans.
  */
  bool operator!=(const ON_Interval& rhs) const;

  /*
  Returns:
    True if (lhs.m_t[0] == rhs.m_t[0]) and (lhs.m_t[1] === rhs.m_t[1]).
  */
  bool operator==(const ON_Interval& rhs) const;

  /* 
  Description:
    Test a value t to see if it is inside the interval.
  Parameters:
    t - [in] value to test
    bTestOpenInterval - [in] 
        If false, t is tested to see if it satisfies min <= t <= max.
        If true, t is tested to see if it satisfies min < t < max.
  Returns:
    true if t is in the interval and false if t is not
    in the interval.
  */
  bool Includes(
    double t,
    bool bTestOpenInterval = false
    ) const;

  /* 
  Description:
    Test an interval to see if it is contained in this interval.
  Parameters:
    other - [in] interval to test
    bProperSubSet - [in] if true, then the test is for a proper subinterval.
  Returns:
    If bProperSubSet is false, then the result is true when
    this->Min() <= other.Min() and other.Max() <= this->Max().
    If bProperSubSet is true, then the result is true when
    this->Min() <= other.Min() and other.Max() <= this->Max()
    and at least one of the inequalities is strict.
  */
  bool Includes( 
    const ON_Interval& other,
    bool bProperSubSet = false
    ) const;

  /*
  Description:
    value is clamped to the range of this interval.  
    Assumes this interval is not Decreasing().
  Parameters:
    value -[in/out]  value is set to x in interval 
        such that |x - value|<= |x - y| for all y in this interval
  Returns:
    -1 if value<Min()
    0  if value in interval
    +1 if value>Max()
  */
  int Clamp(double& value) const;

  /* 
  Description:
    Test a pair of interval to see if they have a non-empty intersection.
  Parameters:
    A - [in] interval to test
    B - [in] interval to test
  Returns:
    true if the intersection is non-empty, 
    including if the intersection is a single point.
    false otherwise. 
  */
  static bool IntervalsOverlap(const ON_Interval& A, const ON_Interval& B);

  /*
  Description:
    Changes interval to [-m_t[1],-m_t[0]].
  */
  void Reverse();

  /*
  Description:
    Swaps m_t[0] and m_t[1].
  */
  void Swap();

  //////////
  // If the intersection is not empty, then 
  // intersection = [max(this.Min(),arg.Min()), min(this.Max(),arg.Max())]
  // Intersection() returns true if the intersection is not empty.
  // The interval [ON_UNSET_VALUE,ON_UNSET_VALUE] is considered to be
  // the empty set interval.  The result of any intersection involving an
  // empty set interval or disjoint intervals is the empty set interval.
  bool Intersection( // this = this intersect arg
         const ON_Interval&
         );

  //////////
  // If the intersection is not empty, then 
  // intersection = [max(argA.Min(),argB.Min()), min(argA.Max(),argB.Max())]
  // Intersection() returns true if the intersection is not empty.
  // The interval [ON_UNSET_VALUE,ON_UNSET_VALUE] is considered to be
  // the empty set interval.  The result of any intersection involving an
  // empty set interval or disjoint intervals is the empty set interval.
  bool Intersection( // this = intersection of two args
         const ON_Interval&, 
         const ON_Interval&
         );

  //////////
  // The union of an empty set and an increasing interval is the increasing
  // interval.  The union of two empty sets is empty. The union of an empty
  // set an a non-empty interval is the non-empty interval.
  // The union of two non-empty intervals is
  // union = [min(this.Min(),arg.Min()), max(this.Max(),arg.Max()),]
  // Union() returns true if the union is not empty.
  bool Union( // this = this union arg
         const ON_Interval&
         );

  bool Union( // this = this union arg
         double t
         );

  bool Union( // this = this union arg
         int count,
         const double* t
         );

  //////////
  // The union of an empty set and an increasing interval is the increasing
  // interval.  The union of two empty sets is empty. The union of an empty
  // set an a non-empty interval is the non-empty interval.
  // The union of two non-empty intervals is
  // union = [min(argA.Min(),argB.Min()), max(argA.Max(),argB.Max()),]
  // Union() returns true if the union is not empty.
  bool Union( // this = union of two args
         const ON_Interval&, 
         const ON_Interval&
         );

  /////////////////////////
  // Expand the interval by adding delta to m_t[1] and subtracting
  // it from m_t[0].  So, when delta is positive and the interval is 
  // increasing this function expands the interval on each side.
  // returns true if the result is increasing.  
  bool Expand(double delta);
};


////////////////////////////////////////////////////////////////
//
//   ON_2dPoint
//
class ON_CLASS ON_2dPoint
{
public:
  double x, y;

public:
  // x,y not initialized
  ON_2dPoint() = default;
  ~ON_2dPoint() = default;
  ON_2dPoint(const ON_2dPoint&) = default;
  ON_2dPoint& operator=(const ON_2dPoint&) = default;

public:
  static const ON_2dPoint Origin;     // (0.0,0.0)
  static const ON_2dPoint UnsetPoint; // (ON_UNSET_VALUE,ON_UNSET_VALUE)
  static const ON_2dPoint NanPoint; // (ON_DBL_QNAN,ON_DBL_QNAN)

  /*
  Description:
    A well ordered dictionary compare function that is nan aware and can
    be used for robust sorting.
  */
  static int Compare(
    const ON_2dPoint& lhs,
    const ON_2dPoint& rhs
    );

  /*
  In  opennurbs points within ON_ZERO_TOLERANCE are generally considered
  to be the same.
  Returns:
    True if for each coordinate pair,
    |a-b| <= ON_ZERO_TOLERANCE
    or |a-b| <= (fabs(a)+fabs(b))*ON_RELATIVE_TOLERANCE.
  */
  bool IsCoincident(const ON_2dPoint& P) const;

  /*
  Returns:
    (A+B)/2
  Remarks:
    Exact when coordinates are equal and prevents overflow.
  */
  static const ON_2dPoint Midpoint(const ON_2dPoint& A, const ON_2dPoint& B);


  explicit ON_2dPoint(double x,double y);
#if defined(OPENNURBS_WALL)
  // Goal is to eventually have all constructors that discard information be explicit.
  explicit 
#endif
  ON_2dPoint(const ON_3dPoint& );       // from 3d point

  explicit ON_2dPoint(const ON_4dPoint& h);       // from 4d point - h.w must be non-zero
  ON_2dPoint(const ON_2dVector& );      // from 2d vector
  explicit ON_2dPoint(const ON_3dVector& );      // from 3d vector

  explicit ON_2dPoint(const double*);            // from double[2] array

  ON_2dPoint(const class ON_2fPoint&);  // from 2f point
  explicit ON_2dPoint(const class ON_3fPoint&);  // from 3f point
  explicit ON_2dPoint(const class ON_4fPoint& h);  // from 4f point - h.w must be non-zero
  explicit ON_2dPoint(const class ON_2fVector&); // from 2f vector
  explicit ON_2dPoint(const class ON_3fVector&); // from 3f vector

  explicit ON_2dPoint(const float*);             // from float[2] array

  // (double*) conversion operators
  operator double*();
  operator const double*() const;

  // use implicit operator=(const ON_2dPoint&)
  ON_2dPoint& operator=(const ON_3dPoint&);
  ON_2dPoint& operator=(const ON_4dPoint&);
  ON_2dPoint& operator=(const ON_2dVector&);
  ON_2dPoint& operator=(const ON_3dVector&);
  ON_2dPoint& operator=(const double*); // point = double[2] support

  ON_2dPoint& operator=(const ON_2fPoint&);
  ON_2dPoint& operator=(const ON_3fPoint&);
  ON_2dPoint& operator=(const ON_4fPoint&);
  ON_2dPoint& operator=(const ON_2fVector&);
  ON_2dPoint& operator=(const ON_3fVector&);
  ON_2dPoint& operator=(const float*);  // point = float[2] support

  ON_2dPoint& operator*=(double);
  ON_2dPoint& operator/=(double);
  ON_2dPoint& operator+=(const ON_2dVector&);
  ON_2dPoint& operator-=(const ON_2dVector&);

  ON_2dPoint  operator*(int) const;
  ON_2dPoint  operator/(int) const;
  ON_2dPoint  operator*(float) const;
  ON_2dPoint  operator/(float) const;
  ON_2dPoint  operator*(double) const;
  ON_2dPoint  operator/(double) const;

  ON_2dPoint  operator+(const ON_2dPoint&) const;
  ON_2dPoint  operator+(const ON_2dVector&) const;
  ON_2dVector operator-(const ON_2dPoint&) const;
  ON_2dPoint  operator-(const ON_2dVector&) const;
  ON_3dPoint  operator+(const ON_3dPoint&) const;
  ON_3dPoint  operator+(const ON_3dVector&) const;
  ON_3dVector operator-(const ON_3dPoint&) const;
  ON_3dPoint  operator-(const ON_3dVector&) const;

  ON_2dPoint  operator+(const ON_2fPoint&) const;
  ON_2dPoint  operator+(const ON_2fVector&) const;
  ON_2dVector operator-(const ON_2fPoint&) const;
  ON_2dPoint  operator-(const ON_2fVector&) const;
  ON_3dPoint  operator+(const ON_3fPoint&) const;
  ON_3dPoint  operator+(const ON_3fVector&) const;
  ON_3dVector operator-(const ON_3fPoint&) const;
  ON_3dPoint  operator-(const ON_3fVector&) const;

  double operator*(const ON_2dPoint&) const; // dot product for points acting as vectors
  double operator*(const ON_2dVector&) const; // dot product for points acting as vectors

  ON_2dPoint operator*(const ON_Xform&) const;

  bool operator==(const ON_2dPoint&) const;
  bool operator!=(const ON_2dPoint&) const;

  // dictionary order comparisons
  bool operator<=(const ON_2dPoint&) const;
  bool operator>=(const ON_2dPoint&) const;
  bool operator<(const ON_2dPoint&) const;
  bool operator>(const ON_2dPoint&) const;

  // index operators mimic double[2] behavior
  double& operator[](int);
  double operator[](int) const;
  double& operator[](unsigned int);
  double operator[](unsigned int) const;

  /*
  Returns:
    False if any coordinate is infinite, a nan, or ON_UNSET_VALUE.
  */
  bool IsValid() const;

  /*
  Returns:
    True if any coordinate is ON_UNSET_VALUE or ON_UNSET_POSITIVE_VALUE
  */
  bool IsUnset() const;

  /*
  Returns:
    True if any coordinate is a nan.
  */
  bool IsNan() const;

  /*
  Returns:
    True if any coordinate is ON_UNSET_VALUE, ON_UNSET_POSITIVE_VALUE, or a nan
  */
  bool IsUnsetOrNan() const;

  // set 2d point value
  void Set(double x,double y);

  double DistanceTo( const ON_2dPoint& ) const;
  double DistanceToSquared(const ON_2dPoint&) const;

  int MaximumCoordinateIndex() const;
  double MaximumCoordinate() const; // absolute value of maximum coordinate

  int MinimumCoordinateIndex() const;
  double MinimumCoordinate() const; // absolute value of minimum coordinate

  ON_DEPRECATED_MSG("Use p = ON_2dPoint::Origin;")
  void Zero(); // set all coordinates to zero;

  /*
  Returns:
    true if all coordinates are not zero and no coordinates are nans.
    false otherwise.
  */
  bool IsZero() const;

  /*
  Returns:
    true if at lease one coordinate is not zero and no coordinates are unset or nans.
  */
  bool IsNotZero() const;

  // These transform the point in place. The transformation matrix acts on
  // the left of the point; i.e., result = transformation*point
  void Transform( 
        const ON_Xform&
        );

  void Rotate( // rotation in XY plane
        double angle,              // angle in radians
        const ON_2dPoint& center   // center of rotation
        );

  void Rotate( // rotation in XY plane
        double sin_angle,          // sin(angle)
        double cos_angle,          // cos(angle)
        const ON_2dPoint& center   // center of rotation
        );

  ON__UINT32 DataCRC(ON__UINT32 current_remainder) const;
};

ON_DECL
ON_2dPoint operator*(int, const ON_2dPoint&);

ON_DECL
ON_2dPoint operator*(float, const ON_2dPoint&);

ON_DECL
ON_2dPoint operator*(double, const ON_2dPoint&);

////////////////////////////////////////////////////////////////
//
//   ON_3dPoint
//
class ON_CLASS ON_3dPoint
{
public:
  double x, y, z;

public:
  // x,y,z not initialized
  ON_3dPoint() = default;
  ~ON_3dPoint() = default;
  ON_3dPoint(const ON_3dPoint&) = default;
  ON_3dPoint& operator=(const ON_3dPoint&) = default;

public:
  static const ON_3dPoint Origin;     // (0.0,0.0,0.0)
  static const ON_3dPoint UnsetPoint; // (ON_UNSET_VALUE,ON_UNSET_VALUE,ON_UNSET_VALUE)
  static const ON_3dPoint NanPoint; // (ON_DBL_QNAN,ON_DBL_QNAN,ON_DBL_QNAN)

  /*
  Description:
    A well ordered dictionary compare function that is nan aware and can
    be used for robust sorting.
  */
  static int Compare(
    const ON_3dPoint& lhs,
    const ON_3dPoint& rhs
    );

  /*
  Returns:
    (A+B)/2
  Remarks:
    Exact when coordinates are equal and prevents overflow.
  */
  static const ON_3dPoint Midpoint(const ON_3dPoint& A, const ON_3dPoint& B);

public:
  explicit ON_3dPoint(double x,double y,double z);
#if defined(OPENNURBS_WALL)
  // Goal is to eventually have all constructors that discard information be explicit.
  explicit 
#endif
  ON_3dPoint(const ON_2dPoint& );       // from 2d point
  explicit ON_3dPoint(const ON_4dPoint& h); // from 4d point - h.w must be non-zero
  explicit ON_3dPoint(const ON_2dVector& );      // from 2d vector
  ON_3dPoint(const ON_3dVector& );      // from 3d vector
  explicit ON_3dPoint(const double*);            // from double[3] array

  explicit ON_3dPoint(const class ON_2fPoint&);  // from 2f point
  ON_3dPoint(const class ON_3fPoint&);  // from 3f point
  explicit ON_3dPoint(const class ON_4fPoint& h );  // from 4f point- h.w must be non-zero
  explicit ON_3dPoint(const class ON_2fVector&); // from 2f point
  explicit ON_3dPoint(const class ON_3fVector&); // from 3f point
  explicit ON_3dPoint(const float*);             // from float[3] array

  // (double*) conversion operators
  operator double*();
  operator const double*() const;

  // use implicit operator=(const ON_3dPoint&)
  ON_3dPoint& operator=(const ON_2dPoint&);
  ON_3dPoint& operator=(const ON_4dPoint&);
  ON_3dPoint& operator=(const ON_2dVector&);
  ON_3dPoint& operator=(const ON_3dVector&);
  ON_3dPoint& operator=(const double*); // point = double[3] support

  ON_3dPoint& operator=(const class ON_2fPoint&);
  ON_3dPoint& operator=(const class ON_3fPoint&);
  ON_3dPoint& operator=(const class ON_4fPoint&);
  ON_3dPoint& operator=(const class ON_2fVector&);
  ON_3dPoint& operator=(const class ON_3fVector&);
  ON_3dPoint& operator=(const float*);  // point = float[3] support

  ON_3dPoint& operator*=(double);
  ON_3dPoint& operator/=(double);
  ON_3dPoint& operator+=(const ON_3dVector&);
  ON_3dPoint& operator-=(const ON_3dVector&);

  ON_3dPoint  operator*(int) const;
  ON_3dPoint  operator/(int) const;
  ON_3dPoint  operator*(float) const;
  ON_3dPoint  operator/(float) const;
  ON_3dPoint  operator*(double) const;
  ON_3dPoint  operator/(double) const;

  ON_3dPoint  operator+(const ON_3dPoint&) const;
  ON_3dPoint  operator+(const ON_3dVector&) const;
  ON_3dVector operator-(const ON_3dPoint&) const;
  ON_3dPoint  operator-(const ON_3dVector&) const;
  ON_3dPoint  operator+(const ON_2dPoint&) const;
  ON_3dPoint  operator+(const ON_2dVector&) const;
  ON_3dVector operator-(const ON_2dPoint&) const;
  ON_3dPoint  operator-(const ON_2dVector&) const;

  ON_3dPoint  operator+(const ON_3fPoint&) const;
  ON_3dPoint  operator+(const ON_3fVector&) const;
  ON_3dVector operator-(const ON_3fPoint&) const;
  ON_3dPoint  operator-(const ON_3fVector&) const;
  ON_3dPoint  operator+(const ON_2fPoint&) const;
  ON_3dPoint  operator+(const ON_2fVector&) const;
  ON_3dVector operator-(const ON_2fPoint&) const;
  ON_3dPoint  operator-(const ON_2fVector&) const;

  double operator*(const ON_3dPoint&) const; // dot product for points acting as vectors
  double operator*(const ON_3dVector&) const; // dot product for points acting as vectors
  
  ON_3dPoint operator*(const ON_Xform&) const;

  bool operator==(const ON_3dPoint&) const;
  bool operator!=(const ON_3dPoint&) const;

  // dictionary order comparisons
  bool operator<=(const ON_3dPoint&) const;
  bool operator>=(const ON_3dPoint&) const;
  bool operator<(const ON_3dPoint&) const;
  bool operator>(const ON_3dPoint&) const;

  // index operators mimic double[3] behavior
  double& operator[](int);
  double operator[](int) const;
  double& operator[](unsigned int);
  double operator[](unsigned int) const;

  /*
  Returns:
    False if any coordinate is infinite, a nan, or ON_UNSET_VALUE.
  */
  bool IsValid() const;

  /*
  Returns:
    True if any coordinate is ON_UNSET_VALUE or ON_UNSET_POSITIVE_VALUE
  */
  bool IsUnset() const;

  /*
  Returns:
    True if any coordinate is a nan.
*/
  bool IsNan() const;

  /*
  Returns:
    True if any coordinate is ON_UNSET_VALUE, ON_UNSET_POSITIVE_VALUE, or a nan
  */
  bool IsUnsetOrNan() const;

  // set 3d point value
  void Set(double x,double y,double z);

  double DistanceTo( const ON_3dPoint& ) const;
  double DistanceToSquared(const ON_3dPoint&) const;

  int MaximumCoordinateIndex() const;
  double MaximumCoordinate() const; // absolute value of maximum coordinate
  
  int MinimumCoordinateIndex() const;
  double MinimumCoordinate() const; // absolute value of minimum coordinate

  double Fuzz( double tolerance = ON_ZERO_TOLERANCE ) const; // tolerance to use when comparing 3d points

#if defined(OPENNURBS_WALL)
  // Goal is to eventually remove all functions that modify points in place.
  ON_DEPRECATED_MSG("Use p = ON_3dPoint::Origin;")
#endif
  void Zero(); // set all coordinates to zero;

  /*
  Returns:
    true if all coordinates are not zero and no coordinates are nans.
    false otherwise.
  */
  bool IsZero() const;

  /*
  Returns:
    true if at lease one coordinate is not zero and no coordinates are unset or nans.
  */
  bool IsNotZero() const;

  /*
  In  opennurbs points within ON_ZERO_TOLERANCE are generally considered
  to be the same.
  Returns:
    True if for each coordinate pair,
    |a-b| <= ON_ZERO_TOLERANCE 
    or |a-b| <= (fabs(a)+fabs(b))*ON_RELATIVE_TOLERANCE.
  */
  bool IsCoincident(const ON_3dPoint& P) const;

  // These transform the point in place. The transformation matrix acts on
  // the left of the point; i.e., result = transformation*point
  void Transform( 
        const ON_Xform&
        );

  void Rotate( 
        double angle,             // angle in radians
        const ON_3dVector& axis,  // axis of rotation
        const ON_3dPoint& center  // center of rotation
        );

  void Rotate( 
        double sin_angle,         // sin(angle)
        double cos_angle,         // cos(angle)
        const ON_3dVector& axis,  // axis of rotation
        const ON_3dPoint& center  // center of rotation
        );

  ON__UINT32 DataCRC(ON__UINT32 current_remainder) const;
};
ON_DECL
bool ON_PointsAreCoincident(const ON_3dPoint&, const ON_3dPoint&);

ON_DECL
ON_3dPoint operator*(int, const ON_3dPoint&);

ON_DECL
ON_3dPoint operator*(float, const ON_3dPoint&);

ON_DECL
ON_3dPoint operator*(double, const ON_3dPoint&);

////////////////////////////////////////////////////////////////
//
//   ON_4dPoint (homogeneous coordinates)
//
class ON_CLASS ON_4dPoint
{
public:
  double x, y, z, w;

  /*
  Returns:
    ON_UNSET_VALUE, if x or w is ON_UNSET_VALUE or ON_UNSET_POSITIVE_VALUE
    and neither x nor w is a nan.
    x/w, otherwise
  Remarks:
    If w is 0.0 or nan, the result will be a nan.
  */
  double EuclideanX() const;

  /*
  Returns:
    ON_UNSET_VALUE, if y or w is ON_UNSET_VALUE or ON_UNSET_POSITIVE_VALUE
    and neither y nor w is a nan.
    y/w, otherwise
  Remarks:
    If w is 0.0 or nan, the result will be a nan.
  */
  double EuclideanY() const;

  /*
  Returns:
    ON_UNSET_VALUE, if z or w is ON_UNSET_VALUE or ON_UNSET_POSITIVE_VALUE
    and neither z nor w is a nan.
    z/w, otherwise
  Remarks:
    If w is 0.0 or nan, the result will be a nan.
  */
  double EuclideanZ() const;

public:
  // x,y,z,w not initialized
  ON_4dPoint() = default;
  ~ON_4dPoint() = default;
  ON_4dPoint(const ON_4dPoint&) = default;
  ON_4dPoint& operator=(const ON_4dPoint&) = default;

public:
  static const ON_4dPoint Zero; // (0,0,0,0)
  static const ON_4dPoint Nan; // (ON_DBL_QNAN,ON_DBL_QNAN,ON_DBL_QNAN,ON_DBL_QNAN)

  explicit ON_4dPoint(double x,double y,double z,double w);

  // These constructors are not explicit because no information is lost.
  ON_4dPoint(const ON_2dPoint& );     // from 2d point (z,y,0,1)
  ON_4dPoint(const ON_3dPoint& );     // from 3d point (x,y,z,1)
  ON_4dPoint(const ON_2dVector& );    // from 2d vector (x,y,0,0)
  ON_4dPoint(const ON_3dVector& );    // from 3d vector (x,y,z,0)

  explicit ON_4dPoint(const double*);          // from double[4] array

  // These constructors are not explicit because no information is lost.
  ON_4dPoint(const ON_2fPoint& );     // from 2f point (z,y,0,1)
  ON_4dPoint(const ON_3fPoint& );     // from 3f point (x,y,z,1)
  ON_4dPoint(const ON_4fPoint& );     // from 4f point
  ON_4dPoint(const ON_2fVector& );    // from 2f vector (z,y,0,0)
  ON_4dPoint(const ON_3fVector& );    // from 3f vector (x,y,z,0)

  explicit ON_4dPoint(const float*);           // from float[4] array

  /*
  Description:
    This function is provided because in rare cases it makes sense.
    If you are not certain why you want this value, think carefully
    or work with vectors and points in Euclidean coordinates.
  Returns:
    lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z + lhs.w*rhs.w;
  Remark:
    It is intentional that there is no operator* override for ON_4dPoint.
    This intentional omission helps people pause and think before calling
    ON_4dPoint::InnerProduct().
  */
  static double InnerProduct(
    const ON_4dPoint& lhs,
    const ON_4dPoint& rhs
  );

  // (double*) conversion operators
  operator double*();
  operator const double*() const;

  // use implicit operator=(const ON_4dPoint&)
  ON_4dPoint& operator=(const ON_2dPoint&);
  ON_4dPoint& operator=(const ON_3dPoint&);
  ON_4dPoint& operator=(const ON_2dVector&);
  ON_4dPoint& operator=(const ON_3dVector&);
  ON_4dPoint& operator=(const double*); // point = double[4] support

  ON_4dPoint& operator=(const class ON_2fPoint&);
  ON_4dPoint& operator=(const class ON_3fPoint&);
  ON_4dPoint& operator=(const class ON_4fPoint&);
  ON_4dPoint& operator=(const class ON_2fVector&);
  ON_4dPoint& operator=(const class ON_3fVector&);
  ON_4dPoint& operator=(const float*);  // point = float[4] support

  ON_4dPoint& operator*=(double);
  ON_4dPoint& operator/=(double);
  ON_4dPoint& operator+=(const ON_4dPoint&); // sum w = sqrt(|w1*w2|)
  ON_4dPoint& operator-=(const ON_4dPoint&); // difference w = sqrt(|w1*w2|)

  ON_4dPoint  operator*(double) const;
  ON_4dPoint  operator/(double) const;
  ON_4dPoint  operator+(const ON_4dPoint&) const; // sum w = sqrt(|w1*w2|)
  ON_4dPoint  operator-(const ON_4dPoint&) const; // difference w = sqrt(|w1*w2|)

  ON_4dPoint operator*(const ON_Xform&) const;

  /*
  Description:
    A well ordered projective compare function that is nan aware and can
    be used for robust sorting.
  Remarks:
    double c = non-nan value.
    ON_4dPoint h0 = ...;
    ON_4dPoint h1(c*h0.x,c*h0.x,c*h0.x,c*h0.x);
    0 == ON_4dPoint::ProjectiveCompare(h0,ha);
  */
  static int ProjectiveCompare(
    const ON_4dPoint& lhs,
    const ON_4dPoint& rhs
  );

  /*
  Description:
    A well ordered dictionary compare function that is nan aware and can
    be used for robust sorting.
  */
  static int DictionaryCompare(
    const ON_4dPoint& lhs,
    const ON_4dPoint& rhs
  );

  /*
  Returns:
    True if (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w).
  */
  bool operator==(const ON_4dPoint& rhs) const;

  /*
  Returns:
    True if lhs.* != rhs.* for some coordinate and no values are nans.
  */
  bool operator!=(const ON_4dPoint& rhs) const;

public:
  // index operators mimic double[4] behavior
  double& operator[](int);
  double operator[](int) const;
  double& operator[](unsigned int);
  double operator[](unsigned int) const;

  /*
  Returns:
    False if any coordinate is infinite, a nan, or ON_UNSET_VALUE.
  */
  bool IsValid() const;

  /*
  Returns:
    True if any coordinate is ON_UNSET_VALUE or ON_UNSET_POSITIVE_VALUE
  */
  bool IsUnset() const;

  /*
  Returns:
    True if any coordinate is a nan.
*/
  bool IsNan() const;

  /*
  Returns:
    True if any coordinate is ON_UNSET_VALUE, ON_UNSET_POSITIVE_VALUE, or a nan
  */
  bool IsUnsetOrNan() const;

  // set 4d point value
  void Set(double x,double y,double z,double w);

  int MaximumCoordinateIndex() const;
  double MaximumCoordinate() const; // absolute value of maximum coordinate

  int MinimumCoordinateIndex() const;
  double MinimumCoordinate() const; // absolute value of minimum coordinate

  bool Normalize(); // set so x^2 + y^2 + z^2 + w^2 = 1

  // These transform the point in place. The transformation matrix acts on
  // the left of the point; i.e., result = transformation*point
  void Transform( 
        const ON_Xform&
        );

  ON__UINT32 DataCRC(ON__UINT32 current_remainder) const;
};

ON_DECL
ON_4dPoint operator*(double, const ON_4dPoint&);

////////////////////////////////////////////////////////////////
//
//   ON_2dVector
//
class ON_CLASS ON_2dVector
{
public:
  double x, y;
  
public:
  // x,y not initialized
  ON_2dVector() = default;
  ~ON_2dVector() = default;
  ON_2dVector(const ON_2dVector&) = default;
  ON_2dVector& operator=(const ON_2dVector&) = default;

public:
  static const ON_2dVector ZeroVector;  // (0.0,0.0)
  static const ON_2dVector XAxis;       // (1.0,0.0)
  static const ON_2dVector YAxis;       // (0.0,1.0)
  static const ON_2dVector UnsetVector; // (ON_UNSET_VALUE,ON_UNSET_VALUE)
  static const ON_2dVector NanVector;   // (ON_DBL_QNAN,ON_DBL_QNAN)

  /*
  Description:
    A well ordered dictionary compare function that is nan aware and can
    be used for robust sorting.
  */
  static int Compare(
    const ON_2dVector& lhs,
    const ON_2dVector& rhs
    );

  // Description:
  //   A index driven function to get unit axis vectors.
  // Parameters:
  //   index - [in] 0 returns (1,0), 1 returns (0,1)
  // Returns:
  //   Unit 2d vector with vector[i] = (i==index)?1:0;
  static const ON_2dVector& UnitVector(
    int // index
    );

  explicit ON_2dVector(double x,double y);

  explicit ON_2dVector(const ON_3dVector& ); // from 3d vector
  ON_2dVector(const ON_2dPoint& );  // from 2d point
  explicit ON_2dVector(const ON_3dPoint& );  // from 3d point
  explicit ON_2dVector(const double*);       // from double[2] array

  ON_2dVector(const ON_2fVector& ); // from 2f vector
  explicit ON_2dVector(const ON_3fVector& ); // from 3f vector
  explicit ON_2dVector(const ON_2fPoint& );  // from 2f point
  explicit ON_2dVector(const ON_3fPoint& );  // from 3f point
  explicit ON_2dVector(const float*);        // from double[2] array

  // (double*) conversion operators
  operator double*();
  operator const double*() const;

  // use implicit operator=(const ON_2dVector&)
  ON_2dVector& operator=(const ON_3dVector&);
  ON_2dVector& operator=(const ON_2dPoint&);
  ON_2dVector& operator=(const ON_3dPoint&);
  ON_2dVector& operator=(const double*); // vector = double[2] support

  ON_2dVector& operator=(const ON_2fVector&);
  ON_2dVector& operator=(const ON_3fVector&);
  ON_2dVector& operator=(const ON_2fPoint&);
  ON_2dVector& operator=(const ON_3fPoint&);
  ON_2dVector& operator=(const float*);  // vector = float[2] support

  ON_2dVector  operator-() const;

  ON_2dVector& operator*=(double);
  ON_2dVector& operator/=(double);
  ON_2dVector& operator+=(const ON_2dVector&);
  ON_2dVector& operator-=(const ON_2dVector&);
  // DO NOT ADD ANY MORE overrides of += or -=

  double operator*(const ON_2dVector&) const; // inner (dot) product
  double operator*(const ON_2dPoint&) const; // inner (dot) product (point acting as vector)
  double operator*(const ON_2fVector&) const; // inner (dot) product	

  ON_2dVector  operator*(int) const;
  ON_2dVector  operator/(int) const;
  ON_2dVector  operator*(float) const;
  ON_2dVector  operator/(float) const;
  ON_2dVector  operator*(double) const;
  ON_2dVector  operator/(double) const;

  ON_2dVector  operator+(const ON_2dVector&) const;
  ON_2dPoint   operator+(const ON_2dPoint&) const;
  ON_2dVector  operator-(const ON_2dVector&) const;
  ON_2dPoint   operator-(const ON_2dPoint&) const;
  ON_3dVector  operator+(const ON_3dVector&) const;
  ON_3dPoint   operator+(const ON_3dPoint&) const;
  ON_3dVector  operator-(const ON_3dVector&) const;
  ON_3dPoint   operator-(const ON_3dPoint&) const;

  ON_2dVector  operator+(const ON_2fVector&) const;
  ON_2dPoint   operator+(const ON_2fPoint&) const;
  ON_2dVector  operator-(const ON_2fVector&) const;
  ON_2dPoint   operator-(const ON_2fPoint&) const;
  ON_3dVector  operator+(const ON_3fVector&) const;
  ON_3dPoint   operator+(const ON_3fPoint&) const;
  ON_3dVector  operator-(const ON_3fVector&) const;
  ON_3dPoint   operator-(const ON_3fPoint&) const;

  ON_2dVector operator*(const ON_Xform&) const;

  bool operator==(const ON_2dVector&) const;
  bool operator!=(const ON_2dVector&) const;

  // dictionary order comparisons
  bool operator<=(const ON_2dVector&) const;
  bool operator>=(const ON_2dVector&) const;
  bool operator<(const ON_2dVector&) const;
  bool operator>(const ON_2dVector&) const;

  // index operators mimic double[2] behavior
  double& operator[](int);
  double operator[](int) const;
  double& operator[](unsigned int);
  double operator[](unsigned int) const;

  /*
  Returns:
    False if any coordinate is infinite, a nan, or ON_UNSET_VALUE.
  */
  bool IsValid() const;

  /*
  Returns:
    True if any coordinate is ON_UNSET_VALUE or ON_UNSET_POSITIVE_VALUE
  */
  bool IsUnset() const;

  /*
  Returns:
    True if any coordinate is a nan.
*/
  bool IsNan() const;

  /*
  Returns:
    True if any coordinate is ON_UNSET_VALUE, ON_UNSET_POSITIVE_VALUE, or a nan
  */
  bool IsUnsetOrNan() const;

  // set 2d vector value
  void Set(double x,double y);

  int MaximumCoordinateIndex() const;
  double MaximumCoordinate() const; // absolute value of maximum coordinate

  int MinimumCoordinateIndex() const;
  double MinimumCoordinate() const; // absolute value of minimum coordinate

  double LengthSquared() const;
  double Length() const;

	// Signed area of the parallelogram.  The volume element.
	// returns x*B.y - y*B.x
	double WedgeProduct(const ON_2dVector& B) const;

  bool Decompose( // Computes a, b such that this vector = a*X + b*Y
         // Returns false if unable to solve for a,b.  This happens
         // when X,Y is not really a basis.
         //
         // If X,Y is known to be an orthonormal frame,
         // then a = V*X, b = V*Y will compute
         // the same result more quickly.
         const ON_2dVector&, // X
         const ON_2dVector&, // Y
         double*, // a
         double*  // b
         ) const;

  int IsParallelTo( 
        // returns  1: this and other vectors are parallel
        //         -1: this and other vectors are anti-parallel
        //          0: this and other vectors are not parallel
        //             or at least one of the vectors is zero
        const ON_2dVector& other,                           // other vector     
        double angle_tolerance = ON_DEFAULT_ANGLE_TOLERANCE // optional angle tolerance (radians)
        ) const;

  bool IsPerpendicularTo(
        // returns true:  this and other vectors are perpendicular
        //         false: this and other vectors are not perpendicular
        //                or at least one of the vectors is zero
        const ON_2dVector& other,                           // other vector     
        double angle_tolerance = ON_DEFAULT_ANGLE_TOLERANCE // optional angle tolerance (radians)
        ) const;

  ON_DEPRECATED_MSG("Use v = ON_2dVector::ZeroVector;")
  void Zero(); // set all coordinates to zero;

  ON_DEPRECATED_MSG("Use v = -v;")
  void Reverse(); // negate all coordinates

  bool Unitize();  // returns false if vector has zero length

  /*
  Returns:
  If this is a valid non-zero vector, a unit vector parallel to this is returned.
  Otherwise the zero vector is returned.
  */
  ON_2dVector UnitVector() const;


  // Description:
  //   Test a vector to see if it is very short
  //
  // Parameters:
  //   tiny_tol - [in] (default = ON_ZERO_TOLERANCE) a nonzero
  //              value used as the coordinate zero tolerance.
  //
  // Returns:
  //   ( fabs(x) <= tiny_tol && fabs(y) <= tiny_tol )
  //
  bool IsTiny(
         double tiny_tol = ON_ZERO_TOLERANCE // tiny_tol
         ) const;

  // Returns:
  //   true if vector is the zero vector.
  bool IsZero() const;

  /*
  Returns:
    true if at lease one coordinate is not zero and no coordinates are unset or nans.
  */
  bool IsNotZero() const;

  // Returns:
  //   true if vector is valid and has length 1.
  bool IsUnitVector() const;

  // set this vector to be perpendicular to another vector
  bool PerpendicularTo( // Result is not unitized. 
                        // returns false if input vector is zero
        const ON_2dVector& 
        );

  // set this vector to be perpendicular to a line defined by 2 points
  bool PerpendicularTo( 
        const ON_2dPoint&, 
        const ON_2dPoint& 
        );
  /*
   Signed Angle (in radians) to A from B. A and B must be non-zero vectors.
  Returns
    -ON_PI <= angle <= ON_PI
   Note: The function is anti-symmetric, i.e Angle(A,B) = -  Angle(A,B)
 */
  static double SignedAngle(const ON_2dVector& A, const ON_2dVector& B);

  // These transform the vector in place. The transformation matrix acts on
  // the left of the vector; i.e., result = transformation*vector
  void Transform( 
        const ON_Xform& // can use ON_Xform here
        );

  void Rotate( 
        double angle            // angle in radians
        );

  void Rotate( 
        double sin_angle,       // sin(angle)
        double cos_angle        // cos(angle)
        );

  ON__UINT32 DataCRC(ON__UINT32 current_remainder) const;
};

ON_DECL
ON_2dVector operator*(int, const ON_2dVector&);

ON_DECL
ON_2dVector operator*(float, const ON_2dVector&);

ON_DECL
ON_2dVector operator*(double, const ON_2dVector&);

///////////////////////////////////////////////////////////////
//
// ON_2dVector utilities
//

ON_DECL
double 
ON_DotProduct( 
    const ON_2dVector&, 
    const ON_2dVector& 
    );

ON_DECL
ON_3dVector 
ON_CrossProduct(
    const ON_2dVector&, 
    const ON_2dVector& 
    );

ON_DECL
double			 
ON_WedgeProduct(		// signed area of the parallelogram.  Volume element.
    const ON_2dVector& A, // returns A.x * B.y - A.y * B.x 
    const ON_2dVector& B 
    );

ON_DECL
bool 
ON_IsOrthogonalFrame( // true if X, Y are nonzero and mutually perpendicular
    const ON_2dVector&, // X
    const ON_2dVector&  // Y
    );

ON_DECL
bool 
ON_IsOrthonormalFrame( // true if X, Y are orthogonal and unit length
    const ON_2dVector&, // X
    const ON_2dVector&  // Y
    );

ON_DECL
bool 
ON_IsRightHandFrame( // true if X, Y are orthonormal and right handed
    const ON_2dVector&, // X
    const ON_2dVector&  // Y
    );

////////////////////////////////////////////////////////////////
//
//   ON_3dVector
//
class ON_CLASS ON_3dVector
{
public:
  double x, y, z;

public:
  // x,y,z not initialized
  ON_3dVector() = default;
  ~ON_3dVector() = default;
  ON_3dVector(const ON_3dVector&) = default;
  ON_3dVector& operator=(const ON_3dVector&) = default;

public:
  static const ON_3dVector ZeroVector;  // (0.0,0.0,0.0)
  static const ON_3dVector XAxis;       // (1.0,0.0,0.0)
  static const ON_3dVector YAxis;       // (0.0,1.0,0.0)
  static const ON_3dVector ZAxis;       // (0.0,0.0,1.0)
  static const ON_3dVector UnsetVector; // (ON_UNSET_VALUE,ON_UNSET_VALUE,ON_UNSET_VALUE)
  static const ON_3dVector NanVector; // (ON_DBL_QNAN,ON_DBL_QNAN,ON_DBL_QNAN)
  
  /*
  Description:
    A well ordered dictionary compare function that is nan aware and can
    be used for robust sorting.
  */
  static int Compare(
    const ON_3dVector& lhs,
    const ON_3dVector& rhs
    );

  // Description:
  //   A index driven function to get unit axis vectors.
  // Parameters:
  //   index - [in] 0 returns (1,0,0), 1 returns (0,1,0), 
  //                2 returns (0,0,1)
  // Returns:
  //   Unit 3d vector with vector[i] = (i==index)?1:0;
  static const ON_3dVector& UnitVector(
    int // index
    );

  explicit ON_3dVector(double x,double y,double z);
#if defined(OPENNURBS_WALL)
  // Goal is to eventually have all constructors that change dimension be explicit.
  explicit 
#endif
  ON_3dVector(const ON_2dVector& );  // from 2d vector
  explicit ON_3dVector(const ON_2dPoint& );   // from 2d point
  ON_3dVector(const ON_3dPoint& );   // from 3d point
  explicit ON_3dVector(const double*);        // from double[3] array

  explicit ON_3dVector(const ON_2fVector& );  // from 2f vector
  ON_3dVector(const ON_3fVector& );  // from 3f vector
  explicit ON_3dVector(const ON_2fPoint& );   // from 2f point
  explicit ON_3dVector(const ON_3fPoint& );   // from 3f point
  explicit ON_3dVector(const float*);         // from float[3] array

  // (double*) conversion operators
  operator double*();
  operator const double*() const;

  // use implicit operator=(const ON_3dVector&)
  ON_3dVector& operator=(const ON_2dVector&);
  ON_3dVector& operator=(const ON_2dPoint&);
  ON_3dVector& operator=(const ON_3dPoint&);
  ON_3dVector& operator=(const double*); // vector = double[3] support
  
  ON_3dVector& operator=(const ON_2fVector&);
  ON_3dVector& operator=(const ON_3fVector&);
  ON_3dVector& operator=(const ON_2fPoint&);
  ON_3dVector& operator=(const ON_3fPoint&);
  ON_3dVector& operator=(const float*);  // vector = float[3] support

  ON_3dVector  operator-() const;

  ON_3dVector& operator*=(double);
  ON_3dVector& operator/=(double);
  ON_3dVector& operator+=(const ON_3dVector&);
  ON_3dVector& operator-=(const ON_3dVector&);
  // DO NOT ADD ANY MORE overrides of += or -=

  double operator*(const ON_3dVector&) const; // inner (dot) product
  double operator*(const ON_3dPoint&) const; // inner (dot) product
  double operator*(const ON_3fVector&) const; // inner (dot) product

  ON_3dVector  operator*(int) const;
  ON_3dVector  operator/(int) const;
  ON_3dVector  operator*(float) const;
  ON_3dVector  operator/(float) const;
  ON_3dVector  operator*(double) const;
  ON_3dVector  operator/(double) const;

  ON_3dVector  operator+(const ON_3dVector&) const;
  ON_3dPoint   operator+(const ON_3dPoint&) const;
  ON_3dVector  operator-(const ON_3dVector&) const;
  ON_3dPoint   operator-(const ON_3dPoint&) const;
  ON_3dVector  operator+(const ON_2dVector&) const;
  ON_3dPoint   operator+(const ON_2dPoint&) const;
  ON_3dVector  operator-(const ON_2dVector&) const;
  ON_3dPoint   operator-(const ON_2dPoint&) const;

  ON_3dVector  operator+(const ON_3fVector&) const;
  ON_3dPoint   operator+(const ON_3fPoint&) const;
  ON_3dVector  operator-(const ON_3fVector&) const;
  ON_3dPoint   operator-(const ON_3fPoint&) const;
  ON_3dVector  operator+(const ON_2fVector&) const;
  ON_3dPoint   operator+(const ON_2fPoint&) const;
  ON_3dVector  operator-(const ON_2fVector&) const;
  ON_3dPoint   operator-(const ON_2fPoint&) const;

  ON_3dVector operator*(const ON_Xform&) const;

  bool operator==(const ON_3dVector&) const;
  bool operator!=(const ON_3dVector&) const;

  // dictionary order comparisons
  bool operator<=(const ON_3dVector&) const;
  bool operator>=(const ON_3dVector&) const;
  bool operator<(const ON_3dVector&) const;
  bool operator>(const ON_3dVector&) const;

  // index operators mimic double[3] behavior
  double& operator[](int);
  double operator[](int) const;
  double& operator[](unsigned int);
  double operator[](unsigned int) const;

  static double DotProduct(
    ON_3dVector A,
    ON_3dVector B
  );

  static const ON_3dVector CrossProduct(
    ON_3dVector A,
    ON_3dVector B
  );

  /*
  Returns:
    False if any coordinate is infinite, a nan, or ON_UNSET_VALUE.
  */
  bool IsValid() const;

  /*
  Returns:
    True if any coordinate is ON_UNSET_VALUE or ON_UNSET_POSITIVE_VALUE
  */
  bool IsUnset() const;

  /*
  Returns:
    True if any coordinate is a nan.
  */
  bool IsNan() const;

  /*
  Returns:
    True if any coordinate is ON_UNSET_VALUE, ON_UNSET_POSITIVE_VALUE, or a nan
  */
  bool IsUnsetOrNan() const;

  // set 3d vector value
  void Set(double x,double y,double z);

  int MaximumCoordinateIndex() const;
  double MaximumCoordinate() const; // absolute value of maximum coordinate

  int MinimumCoordinateIndex() const;
  double MinimumCoordinate() const; // absolute value of minimum coordinate

  double LengthSquared() const;
  double Length() const;

  bool Decompose( // Computes a, b, c such that this vector = a*X + b*Y + c*Z
         // Returns false if unable to solve for a,b,c.  This happens
         // when X,Y,Z is not really a basis.
         //
         // If X,Y,Z is known to be an orthonormal frame,
         // then a = V*X, b = V*Y, c = V*Z will compute
         // the same result more quickly.
         const ON_3dVector&, // X
         const ON_3dVector&, // Y
         const ON_3dVector&, // Z
         double*, // a
         double*, // b
         double*  // c
         ) const;

  int IsParallelTo( 
        // returns  1: this and other vectors are parallel
        //         -1: this and other vectors are anti-parallel
        //          0: this and other vectors are not parallel
        //             or at least one of the vectors is zero
        const ON_3dVector& other,                           // other vector     
        double angle_tolerance = ON_DEFAULT_ANGLE_TOLERANCE // optional angle tolerance (radians)
        ) const;

  bool IsPerpendicularTo(
        // returns true:  this and other vectors are perpendicular
        //         false: this and other vectors are not perpendicular
        //                or at least one of the vectors is zero
        const ON_3dVector& other,                           // other vector     
        double angle_tolerance = ON_DEFAULT_ANGLE_TOLERANCE // optional angle tolerance (radians)
        ) const;

  double Fuzz( double tolerance = ON_ZERO_TOLERANCE ) const; // tolerance to use when comparing 3d vectors

#if defined(OPENNURBS_WALL)
  // Goal is to eventually remove all functions that modify vectors in place.
  ON_DEPRECATED_MSG("Use v = ON_3dVector::ZeroVector;")
#endif
  void Zero(); // set all coordinates to zero;

#if defined(OPENNURBS_WALL)
  // Goal is to eventually remove all functions that modify vectors in place.
  ON_DEPRECATED_MSG("Use v = -v;")
#endif
  void Reverse(); // negate all coordinates

  bool Unitize();  // returns false if vector has zero length
  double LengthAndUnitize(); // unitizes and returns initial length

  /*
  Returns:
    If this is a valid non-zero vector, a unit vector parallel to this is returned.
    Otherwise the zero vector is returned.
  */
  ON_3dVector UnitVector() const;

  // Description:
  //   Test a vector to see if it is very short
  //
  // Parameters:
  //   tiny_tol - [in] (default = ON_ZERO_TOLERANCE) a nonzero
  //              value used as the coordinate zero tolerance.
  //
  // Returns:
  //   ( fabs(x) <= tiny_tol && fabs(y) <= tiny_tol && fabs(z) <= tiny_tol )
  //
  bool IsTiny(
         double tiny_tol = ON_ZERO_TOLERANCE // tiny_tol
         ) const;

  // Returns:
  //   true if vector is the zero vector.
  bool IsZero() const;

  /*
  Returns:
    true if at lease one coordinate is not zero and no coordinates are unset or nans.
  */
  bool IsNotZero() const;


  // Returns:
  //   true if vector is valid and has length 1.
  bool IsUnitVector() const;

  // set this vector to be perpendicular to another vector
  bool PerpendicularTo( // Result is not unitized. 
                        // returns false if input vector is zero
        const ON_3dVector& 
        );

  // set this vector to be perpendicular to a plane defined by 3 points
  bool PerpendicularTo(
               // about 3 times slower than
               //    ON_3dVector N = ON_CrossProduct(P1-P0,P2-P0); 
               //    N.Unitize();
               // returns false if points are coincident or collinear
         const ON_3dPoint&, const ON_3dPoint&, const ON_3dPoint& 
         );

  /*
  Parameters:
    failure_result - [in]
      vector to return if this is zero or unset.
      When in doubt, pass ON_3dVector::NanVector.
  Returns:
    If this is nonzero, a vector perpendicular to this.
    The returned vector is not unitized.
    Otherwise failure_result is returned.
  */
  const ON_3dVector Perpendicular(
    ON_3dVector failure_result
  ) const;

  /*
    Angle (in radians) between two vectors. A and B must be non-zero vectors
   Returns 
     0<= angle <= ON_PI
    Note: The function is symmetric, i.e Angle(A,B) = Angle(B,A)
          This function is always accurate, in particular for nearly parallel,
          anti-parallel or  perpendicular vectors
  */
  static double Angle(const ON_3dVector& A, const ON_3dVector& B);

  // These transform the vector in place. The transformation matrix acts on
  // the left of the vector; i.e., result = transformation*vector
  void Transform( 
        const ON_Xform& // can use ON_Xform here
        );

  void Rotate( 
        double angle,           // angle in radians
        const ON_3dVector& axis // axis of rotation
        );

  void Rotate( 
        double sin_angle,        // sin(angle)
        double cos_angle,        // cos(angle)
        const ON_3dVector& axis  // axis of rotation
        );

  ON__UINT32 DataCRC(ON__UINT32 current_remainder) const;
};

class ON_CLASS ON_3dRay
{
public:
  ON_3dPoint  m_P;
  ON_3dVector m_V;
};

/*
Description:
  Typically the vector portion is a unit vector and
  m_d = -(x*P.x + y*P.y + z*P.z) for a point P on the plane.
*/
class ON_CLASS ON_PlaneEquation
{
public:
  // C++ defaults for construction, destruction, copies, and operator=
  // work fine.

  static const ON_PlaneEquation UnsetPlaneEquation; // (ON_UNSET_VALUE,ON_UNSET_VALUE,ON_UNSET_VALUE,ON_UNSET_VALUE)
  static const ON_PlaneEquation ZeroPlaneEquation; // (0.0,0.0,0.0,0.0)
  static const ON_PlaneEquation NanPlaneEquation; // (ON_DBL_QNAN,ON_DBL_QNAN,ON_DBL_QNAN,ON_DBL_QNAN)

  static const ON_PlaneEquation WorldXY; // (0,0,1,0)
  static const ON_PlaneEquation WorldYZ; // (1,0,0,0)
  static const ON_PlaneEquation WorldZX; // (0,1,0,0)

  /*
  Returns:
    If the three points are valid and not collinear, a unitized plane equation is returned.
    Otherwise ON_PlaneEquation::NanPlaneEquation is returned.
  */
  static const ON_PlaneEquation CreateFromThreePoints(
    ON_3dPoint pointA,
    ON_3dPoint pointB,
    ON_3dPoint pointC
    );

  /*
  Returns:
    If point is valid and normal is nonzero, a unitized plane equation is returned.
    Otherwise ON_PlaneEquation::NanPlaneEquation is returned.
  */
  static const ON_PlaneEquation CreateFromPointAndNormal(
    ON_3dPoint point,
    ON_3dVector normal
    );

  ON_PlaneEquation();

  ON_PlaneEquation(
    double xx, double yy, double zz, double dd
    );

  static void Set(
    ON_PlaneEquation& plane_equation,
    double x, double y, double z, double d
    );

  double MaximumCoefficient() const;

  /*
  Returns:
    The plane equation whose coefficient values are 
    the negative of the coefficient values in this,
    provided the coefficient value is valid. Any invalid
    coefficient values are copied.
  */
  ON_PlaneEquation NegatedPlaneEquation() const;


  /*
  Returns:
    The plane equation whose first three coefficient values 
    are a unit vector.
  */
  ON_PlaneEquation UnitizedPlaneEquation() const;



  /*
  Description:
    returns true if x, y, z, d are valid, finite doubles.
  Remarks:
    this function will return true if x, y and z are all zero.
  See Also:
    ON_PlaneEquation::IsSet().
  */
  bool IsValid() const;

  /*
  Description:
    returns true if x, y, z, d are valid, finite doubles and at least one of x, y or z is not zero.
  */
  bool IsSet() const;

  /*
  Description:
    returns true if x, y, z, d are valid, finite doubles and x^2 + y^2 + z^2 = 1.
  */
  bool IsUnitized() const;

  /*
  Description:
    Sets (x,y,z) to a unitized N and then sets
    d = -(x*P.x + y*P.y + z*P.z).
  Parameters:
    P - [in] point on the plane
    N - [in] vector perpendicular to the plane
  Returns:
     true if input is valid.
  */
  bool Create( ON_3dPoint P, ON_3dVector N );

  // index operators mimic double[4] behavior
  // Return null refs or ON_UNSET_VALUE for out-of-range indices
  double& operator[](int);
  double& operator[](unsigned int);
  double operator[](int) const;
  double operator[](unsigned int) const;

  /*
  Returns:
    Direction (x,y,z)
  */
  ON_3dVector Direction() const;

  double DirectionLength() const;

  /*
  Returns:
    Unitized direction or zero vector if not set.
  */
  ON_3dVector UnitNormal() const;

  /*
    Returns  1: this and other vectors are parallel
            -1: this and other vectors are anti-parallel
             0: this and other vectors are not parallel
                or at least one of the vectors is zero
  */
  int IsParallelTo( 
        const ON_PlaneEquation& other,                      // other plane equation
        double angle_tolerance = ON_DEFAULT_ANGLE_TOLERANCE // optional angle tolerance (radians)
        ) const;

  /*
  Description:
    Evaluate the plane at a point.
  Parameters:
    P - [in]
  Returns:
    x*P.x + y*P.y + z*P.z + d;
  */
  double ValueAt(ON_3dPoint P) const;
  double ValueAt(ON_4dPoint P) const;
  double ValueAt(ON_3dVector P) const;
  double ValueAt(double x, double y, double z) const;

  /*
  Returns:
    ON_Interval::EmptyInterval if input is not valid.
  */
  ON_Interval ValueRange(
    size_t point_list_count,
    const ON_3dPoint* point_list
    ) const;

  /*
  Returns:
    ON_Interval::EmptyInterval if input is not valid.
  */
  ON_Interval ValueRange(
    const ON_SimpleArray< ON_3dPoint >& point_list
    ) const;

  /*
  Returns:
    ON_Interval::EmptyInterval if input is not valid.
  */
  ON_Interval ValueRange(
    size_t point_list_count,
    const ON_3fPoint* point_list
    ) const;

  /*
  Returns:
    ON_Interval::EmptyInterval if input is not valid.
  */
  ON_Interval ValueRange(
    const ON_SimpleArray< ON_3fPoint >& point_list
    ) const;

  /*
  Returns:
    ON_Interval::EmptyInterval if input is not valid.
  */
  ON_Interval ValueRange(
    const class ON_3dPointListRef& point_list
    ) const;

  /*
  Returns:
    ON_Interval::EmptyInterval if input is not valid.
  */
  ON_Interval ValueRange(
    size_t point_index_count,
    const unsigned int* point_index_list,
    const class ON_3dPointListRef& point_list
    ) const;

  ON_Interval ValueRange(
    size_t point_index_count,
    size_t point_index_stride,
    const unsigned int* point_index_list,
    const class ON_3dPointListRef& point_list
    ) const;

  /*
  Description:
    Evaluate the plane at a list of point values.
  Parameters:
    Pcount - [in]
      number of points
    P - [in]
      points
    value - [in]
      If not null, value[] must be an array of length at least Pcount.
      The values will be stored in this array.  If null, the an array
      will be allocated with onmalloc() and returned.
    value_range - [out]
      If not null, the range of values will be returned here.
  Returns:
    An array of Pcount values.  If the input parameter value was null,
    then the array is allocated on the heap using onmalloc() and the 
    caller is responsible for calling onfree() when finished.  If the 
    input is not valid, null is returned.
  */
  double* ValueAt(
        int Pcount,
        const ON_3fPoint* P,
        double* value,
        double value_range[2]
        ) const;

  double* ValueAt(
        int Pcount,
        const ON_3dPoint* P,
        double* value,
        double value_range[2]
        ) const;

  /*
  Description:
    This function calculates and evaluates points that 
    would be exactly on the plane if double precision
    arithmetic were mathematically perfect and returns
    the largest value of the evaluations.
  */
  double ZeroTolerance() const;

  /*
  Description:
    Transform the plane equation so that, if e0 is the initial
    equation, e1 is transformed equation and P is a point,
    then e0.ValueAt(P) = e1.ValueAt(xform*P).
  Parameters:
    xform - [in]
      Invertable transformation.
  Returns:
    True if the plane equation was successfully transformed.
    False if xform is not invertable or the equation is not
    valid.
  Remarks:
    This function has to invert xform.  If you have apply the
    same transformation to a bunch of planes, then it will be
    more efficient to calculate xform's inverse transpose
    and apply the resulting transformation to the equation's
    coefficients as if they were 4d point coordinates.
  */
  bool Transform( const ON_Xform& xform );

  /*
  Description:
    Get point on plane that is closest to a given point.
  Parameters:
    point - [in]
  Returns:
    A 3d point on the plane that is closest to the input point.
  */
  ON_3dPoint ClosestPointTo( ON_3dPoint point ) const;

  /*
  Description:
    Get the minimum value of the plane equation
    on a bounding box.
  Parameters:
    bbox - [in] 
  Returns:
    Minimum value of the plane equation on the bounding box.
  */
  double MinimumValueAt(const ON_BoundingBox& bbox) const;

  /*
  Description:
    Get the maximum value of the plane equation
    on a bounding box.
  Parameters:
    bbox - [in] 
  Returns:
    Maximum value of the plane equation on the bounding box.
  */
  double MaximumValueAt(const ON_BoundingBox& bbox) const;


  /*
  Description:
    Get the maximum value of the plane equation on a set of 3d points.
  Parameters:
    bRational - [in]
      False if the points are euclidean (x,y,z)
      True if the points are homogeneous rational (x,y,z,w)
      (x/w,y/w,z/w) is used to evaluate the value.
    point_count - [in]
    point_stride - [in]
      i-th point's x coordinate = points[i*point_stride]
    points - [in]
      coordinates of points
    stop_value - [in]
      If stop_value is valid and not ON_UNSET_VALUE, then the 
      evaluation stops if a value > stop_value is found. 
      If stop_value = ON_UNSET_VALUE, then stop_value is ignored.
  Returns:
    Maximum value of the plane equation on the point list.
    If the input is not valid, then ON_UNSET_VALUE is returned.
  */
  double MaximumValueAt(
    bool bRational,
    int point_count,
    int point_stride,
    const double* points,
    double stop_value
    ) const;

  /*
  Description:
    Get the minimum value of the plane equation on a set of 3d points.
  Parameters:
    bRational - [in]
      False if the points are euclidean (x,y,z)
      True if the points are homogeneous rational (x,y,z,w)
      (x/w,y/w,z/w) is used to evaluate the value.
    point_count - [in]
    point_stride - [in]
      i-th point's x coordinate = points[i*point_stride]
    points - [in]
      coordinates of points
    stop_value - [in]
      If stop_value is valid and not ON_UNSET_VALUE, then the 
      evaluation stops if a value < stop_value is found. 
      If stop_value = ON_UNSET_VALUE, then stop_value is ignored.
  Returns:
    Maximum value of the plane equation on the point list.
    If the input is not valid, then ON_UNSET_VALUE is returned.
  */
  double MinimumValueAt(
    bool bRational,
    int point_count,
    int point_stride,
    const double* points,
    double stop_value
    ) const;

  /*
  Description:
    Get the maximum absolute value of the plane equation 
    on a set of 3d points.
  Parameters:
    bRational - [in]
      False if the points are euclidean (x,y,z)
      True if the points are homogeneous rational (x,y,z,w)
      (x/w,y/w,z/w) is used to evaluate the value.
    point_count - [in]
    point_stride - [in]
      i-th point's x coordinate = points[i*point_stride]
    points - [in]
      coordinates of points
    stop_value - [in]
      If stop_value >= 0.0, then the evaluation stops if an
      absolute value > stop_value is found. If stop_value < 0.0 
      or stop_value is invalid, then stop_value is ignored.
  Returns:
    Maximum value of the plane equation on the point list.
    If the input is not valid, then ON_UNSET_VALUE is returned.
  */
  double MaximumAbsoluteValueAt(
    bool bRational,
    int point_count,
    int point_stride,
    const double* points,
    double stop_value
    ) const;

  /*
  Description:
    Test points on a bezier curve to see if they are near the plane.
  Parameters:
    bezcrv - [in]
    s0 - [in]
    s1 - [in] the interval from s0 to s1 is tested (s0 < s1)
    sample_count - [in] number of interior points to test.  
                Numbers like 1, 3, 7, 15, ... work best.
    endpoint_tolerance - [in] If >= 0, then the end points are 
              tested to see if the distance from the endpoints 
              is <= endpoint_tolerance.
    interior_tolerance - [in] (>=0 and >=endpoint_tolerance) 
              This tolerance is used to test the interior sample points.
    smin - [put]  If not nullptr, *smin = bezier parameter of nearest
                  test point.
    smax - [put]  If not nullptr, *smax = bezier parameter of farthest
                  test point.  If false is returned, this is the
                  parameter of the test point that failed.
  Returns:
    True if all the tested points passed the tolerance test.
    False if at least one tested point failed the tolerance test.
    (The test terminates when the first failure is encountered.)
  */
  bool IsNearerThan( 
          const class ON_BezierCurve& bezcrv,
          double s0,
          double s1,
          int sample_count,
          double endpoint_tolerance,
          double interior_tolerance,
          double* smin,
          double* smax
          ) const;
  
  bool operator==(const ON_PlaneEquation&) const;
  bool operator!=(const ON_PlaneEquation&) const;

  double x;
  double y;
  double z;
  double d; // 4th coefficient of the plane equation.

  void Dump(class ON_TextLog&) const;
};

ON_DECL
const ON_PlaneEquation operator*(const ON_Xform&, const ON_PlaneEquation&);


#if defined(ON_DLL_TEMPLATE)

ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_PlaneEquation>;

#endif

ON_DECL
ON_3dVector operator*(int, const ON_3dVector&);

ON_DECL
ON_3dVector operator*(float, const ON_3dVector&);

ON_DECL
ON_3dVector operator*(double, const ON_3dVector&);

///////////////////////////////////////////////////////////////
//
// ON_3dVector utilities
//

ON_DECL
double 
ON_DotProduct( 
    const ON_3dVector&, 
    const ON_3dVector& 
    );


ON_DECL
ON_3dVector 
ON_CrossProduct(
    const ON_3dVector&, 
    const ON_3dVector& 
    );

ON_DECL
ON_3dVector 
ON_CrossProduct( // 3d cross product for old fashioned arrays
    const double*, // array of 3d doubles
    const double*  // array of 3d doubles
    );

ON_DECL
double 
ON_TripleProduct( 
    const ON_3dVector&,
    const ON_3dVector&,
    const ON_3dVector&
    );

ON_DECL
double 
ON_TripleProduct(  // 3d triple product for old fashioned arrays
    const double*, // array of 3d doubles
    const double*, // array of 3d doubles
    const double*  // array of 3d doubles
    );

ON_DECL
bool 
ON_IsOrthogonalFrame( // true if X, Y, Z are nonzero and mutually perpendicular
    const ON_3dVector&, // X
    const ON_3dVector&, // Y
    const ON_3dVector&  // Z 
    );

ON_DECL
bool 
ON_IsOrthonormalFrame( // true if X, Y, Z are orthogonal and unit length
    const ON_3dVector&, // X
    const ON_3dVector&, // Y
    const ON_3dVector&  // Z 
    );

ON_DECL
bool 
ON_IsRightHandFrame( // true if X, Y, Z are orthonormal and right handed
    const ON_3dVector&, // X
    const ON_3dVector&, // Y
    const ON_3dVector&  // Z 
    );

// Find the largest absolute value of coordinates from an array of points (possibly homogeneous).
ON_DECL
double ON_MaximumCoordinate(const double* data, int dim, bool is_rat, int count);
ON_DECL
double ON_MaximumCoordinate(const double* data, int dim, bool is_rat, int count, int stride);   // stride>=dim+is_rat

///////////////////////////////////////////////////////////////
//
// common points and vectors
//
// ON_unset_point is obsolete - use ON_3dPoint::UnsetPoint
#if !defined(OPENNURBS_WALL)

// OBSOLETE - use ON_3dPoint::UnsetPoint
#define ON_unset_point ON_3dPoint::UnsetPoint
// OBSOLETE - use ON_3dPoint::UnsetPoint
#define ON_UNSET_POINT ON_3dPoint::UnsetPoint
// OBSOLETE - use ON_3dPoint::UnsetVector
#define ON_UNSET_VECTOR ON_3dVector::UnsetVector
// OBSOLETE - use ON_3dPoint::Origin
#define ON_origin ON_3dPoint::Origin
// OBSOLETE - use ON_3dVector::XAxis
#define ON_xaxis ON_3dVector::XAxis
// OBSOLETE - use ON_3dVector::YAxis
#define ON_yaxis ON_3dVector::YAxis
// OBSOLETE - use ON_3dVector::ZAxis
#define ON_zaxis ON_3dVector::ZAxis
// OBSOLETE  - use ON_3fPoint::Origin
#define ON_forigin ON_3fPoint::Origin
// OBSOLETE  - use ON_3fVector::XAxis
#define ON_fxaxis ON_3fVector::XAxis
// OBSOLETE  - use ON_3fVector::YAxis
#define ON_fyaxis ON_3fVector::YAxis
// OBSOLETE  - use ON_3fVector::ZAxis
#define ON_fzaxis ON_3fVector::ZAxis

#endif

#include "opennurbs_fpoint.h"

////////////////////////////////////////////////////////////////
//
//   ON_SurfaceCurvature
//
class ON_CLASS ON_SurfaceCurvature
{
public:

  /// <summary>
  /// Create an ON_SurfaceCurvature from the principal curvature values.
  /// The principal curvature values are the most fundamental curvature properties
  /// of a surface. Other curvatures are calculated from them. For example
  /// gaussian curvature = k1 * k2 and mean curvature = (k1 + k2)/2.
  /// </summary>
  /// <param name="k1"></param>
  /// <param name="k2"></param>
  /// <returns>
  /// An ON_SurfaceCurvature with the specified principal curvatures.
  /// </returns>
  static const ON_SurfaceCurvature CreateFromPrincipalCurvatures(
    double k1,
    double k2
  );


  /// <summary>
  /// Create an ON_SurfaceCurvature from a gaussian and mean curvature values using the relationship
  /// between the principal curvatures, gaussian and mean.
  /// k1 = mean + sqrt(mean*mean - gaussian)
  /// k2 = mean - sqrt(mean*mean - gaussian)
  /// If the radicand is negative, we assume we're dealing with a bit of numerical noise or
  /// estimates and set the principal curvatures
  /// k1 = k2 = sign(mean)*sqrt(gaussian)
  /// </summary>
  /// <param name="gaussian_curvature"></param>
  /// Gaussian curvature = k1*k2 (product of principal curvatures).
  /// <param name="mean_curvature">
  /// Mean curvature = (k1+k2)/2 (average of principal curvatures).
  /// </param>
  /// <returns>
  /// A surface curvature with GaussianCurvature() = gaussian_curvature 
  /// and MeanCurvature() = gaussian_curvature.
  /// </returns>
  static const ON_SurfaceCurvature CreateFromGaussianAndMeanCurvatures(
    double gaussian_curvature,
    double mean_curvature
  );

  /// <summary>
  /// The sign of the principal curvatures are with respect to a choice
  /// of surface orientation. This function returns the principal curvatures
  /// of the surface with opposite choice of orientation.
  /// </summary>
  /// <returns>
  /// ON_SurfaceCurvature::CreateFromPrincipalCurvatures(-this->k2, -this->k1);
  /// </returns>
  const ON_SurfaceCurvature FlipSurfaceOrientation() const;

  /// <summary>
  /// Dictionary compare k1 and k2. Values with nans sort last.
  /// </summary>
  /// <param name="lhs"></param>
  /// <param name="rhs"></param>
  /// <returns>-1, 0 or +1.</returns>
  static int Compare(const ON_SurfaceCurvature& lhs, const ON_SurfaceCurvature& rhs);

  /// <summary>
  /// Dictionary compare lhs.MaximumPrincipalCurvature() and rhs.MaximumPrincipalCurvature(). 
  /// Values with nans sort last.
  /// </summary>
  /// <param name="lhs"></param>
  /// <param name="rhs"></param>
  /// <returns>-1, 0 or +1.</returns>
  static int CompareMaximumAndMinimumPrincipalCurvatures(const ON_SurfaceCurvature& lhs, const ON_SurfaceCurvature& rhs);

  /// <summary>
  /// Compare lhs.MaximumPrincipalCurvature() and rhs.MaximumPrincipalCurvature(). 
  /// Values with nans sort last.
  /// </summary>
  /// <param name="lhs"></param>
  /// <param name="rhs"></param>
  /// <returns>-1, 0 or +1.</returns>
  static int CompareMaximumPrincipalCurvature(const ON_SurfaceCurvature& lhs, const ON_SurfaceCurvature& rhs);

  /// <summary>
  /// Compare lhs.MinimumPrincipalCurvature() and rhs.MinimumPrincipalCurvature(). 
  /// Values with nans sort last.
  /// </summary>
  /// <param name="lhs"></param>
  /// <param name="rhs"></param>
  /// <returns>-1, 0 or +1.</returns>
  static int CompareMinimumPrincipalCurvature(const ON_SurfaceCurvature& lhs, const ON_SurfaceCurvature& rhs);

  /// <summary>
  /// Compare lhs.MaximumRadius() and rhs.MaximumRadius(). 
  /// Values with nans sort last.
  /// </summary>
  /// <param name="lhs"></param>
  /// <param name="rhs"></param>
  /// <returns>-1, 0 or +1.</returns>
  static int CompareMaximumRadius(const ON_SurfaceCurvature& lhs, const ON_SurfaceCurvature& rhs);

  /// <summary>
  /// Compare lhs.MinimumRadius() and rhs.MinimumRadius(). 
  /// Values with nans sort last.
  /// </summary>
  /// <param name="lhs"></param>
  /// <param name="rhs"></param>
  /// <returns>-1, 0 or +1.</returns>
  static int CompareMinimumRadius(const ON_SurfaceCurvature& lhs, const ON_SurfaceCurvature& rhs);

  /// <summary>
  /// Compare lhs.GaussianCurvature() and rhs.GaussianCurvature(). 
  /// Values with nans sort last.
  /// </summary>
  /// <param name="lhs"></param>
  /// <param name="rhs"></param>
  /// <returns>-1, 0 or +1.</returns>
  static int CompareGaussianCurvature(const ON_SurfaceCurvature& lhs, const ON_SurfaceCurvature& rhs);

  /// <summary>
  /// Compare lhs.MeanCurvature() and rhs.MeanCurvature(). 
  /// Values with nans sort last.
  /// </summary>
  /// <param name="lhs"></param>
  /// <param name="rhs"></param>
  /// <returns>-1, 0 or +1.</returns>
  static int CompareMeanCurvature(const ON_SurfaceCurvature& lhs, const ON_SurfaceCurvature& rhs);

  /// <summary>
  /// k1 = k2 = ON_DBL_QNAN
  /// </summary>
  static const ON_SurfaceCurvature Nan;

  /// <summary>
  /// k1 = k2 = 0
  /// </summary>
  static const ON_SurfaceCurvature Zero;

  /// <summary>
  /// Value used to indicate a radius of curvature is infinite (1e300).
  /// </summary>
  static const double InfinteRadius;

public:
  double k1, k2; // principal curvatures

public:

  /// <returns>True if k1 and k2 are both valid finite values.</returns>
  bool IsSet() const;

  /// <returns>True if k1 and k2 are both zero.</returns>
  bool IsZero() const;

  /// <returns>True if either of k1 or k2 is not a valid finite value.</returns>
  bool IsUnset() const;

  /// <returns>True if either of k1 or k2 is a nan.</returns>
  bool IsNan() const;

public:
  /// <summary>
  /// The Gaussian curvature is k1*k2.
  /// </summary>
  /// <returns>
  /// If this is set, the Gausian curvature is returned.
  /// Otherwise ON_DBL_QNAN is returned.
  /// </returns>
  double GaussianCurvature() const;

  /// <summary>
  /// The mean curvature is (k1+k2)/2.
  /// </summary>
  /// <returns>
  /// If this is set, the signed mean curvature is returned.
  /// Otherwise ON_DBL_QNAN is returned.
  /// </returns>
  double MeanCurvature() const;

  /// <summary>
  /// The minimum radius of curvature is 1/max(fabs(k1),fabs(k2)).
  /// Infinite radius values are returned as ON_SurfaceCurvature::InfiniteRadius.
  /// </summary>
  /// <returns>
  /// Minimum radius of curvature up to a maximum of 1e300. 
  /// If both k1 and k2 are zero, then 1e300 is returned.
  /// </returns>
  double MinimumRadius() const;

  /// <summary>
  /// If a principal curvature value is zero 
  /// or the principal curvatures have opposite signs,
  /// then the maximum radius of curvature is infinite 
  /// and ON_SurfaceCurvature::InfiniteRadius is returned.
  /// Otherwise the maximum radius of curvature is 1/min(fabs(k1),fabs(k2)).
  /// </summary>
  /// <returns>
  /// IF k1 and k2 are valid, the maximum radius of curvature is returned. 
  /// Otherwise ON_DBL_QNAN is returned.
  /// </returns>
  double MaximumRadius() const;

  /// <summary>
  /// Calculate one of the four typical curvature values associated
  /// with the two principal curvatures and frequently used in false
  /// color curvature analysis.
  /// </summary>
  /// <param name="kappa_style">
  /// Specifies which type curvature (Gaussian, mean, ...) value to calculate from the principal curvatures.
  /// The Gausian curvature can be positive or negative. The other curvatures are are &gt;= 0.
  /// In particular, ON::curvature_style::mean_curvature return fabs(this->MeanCurvature()).
  /// </param>
  /// <returns>
  /// If kappa_style and the principal curvatures are valid, the specified
  /// type of curvature value is returned. 
  /// Infinite radii are returned as ON_SurfaceCurvature::InfiniteRadius.
  /// Otherwise ON_DBL_QNAN is returned.
  /// </returns>
  double KappaValue(ON::curvature_style kappa_style) const;

  /// <returns>
  /// If this is set, the maximum of k1 and k2 is returned.
  /// Otherwise ON_DBL_QNAN is returned.
  /// </returns>
  double MaximumPrincipalCurvature() const;

  /// <returns>
  /// If this is set, the minimum of k1 and k2.
  /// Otherwise ON_DBL_QNAN is returned.
  /// </returns>
  double MinimumPrincipalCurvature() const;
};

ON_DECL
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns>
/// Returns (lhs.k1==rhs.k1 && lhs.k2==rhs.k2)
/// Note that if any principal curvature is a nan, then false is returned.
/// </returns>
bool operator==(
  const ON_SurfaceCurvature& lhs,
  const ON_SurfaceCurvature& rhs
  );

ON_DECL
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns>
/// Returns (lhs.k1 != rhs.k1 || lhs.k2!=rhs.k2) || (lhs.IsNan() && rhs.IsNan()).
/// </returns>
bool operator!=(
  const ON_SurfaceCurvature& lhs,
  const ON_SurfaceCurvature& rhs
  );

/// <summary>
/// ON_SurfaceValues stores surface evaluation values (point, normal, curvatures, derivatives) in a single class
/// </summary>
class ON_WIP_CLASS ON_SurfaceValues
{
public:

  enum : unsigned
  {
    /// <summary>
    /// The maximum order of a partial derivative that
    /// an ON_SurfaceValues class can possibly store is 15.
    /// </summary>
    MaximumDerivativeOrder = 15
  };

  /// <summary>
  /// NOTE WELL: CreateFromLocalArray is for experts dealing with unusual situations.
  /// Create a ON_SurfaceValues where the storage for derivative values is managed externally.
  /// This is typically used by experts to easily get surface evaluation results stored in value_array[] when 
  /// the evaluation function returns the results in a ON_SurfaceValues class.
  /// The caller is responsible for ensuring that the value_array[] memory is not freed or deleted
  /// while the returned ON_SurfaceValues class is in scope. 
  /// Any copy of the returned values will not reference value_array[].
  /// </summary>
  /// <param name="derivative_order">
  /// 0 &lt;= derivative_order &lt;= ON_SurfaceValues::MaximumDerivativeOrder
  /// derivative_order = maximum order of a partial derivative that can be stored in value_array[].
  /// 1 for point and 1st partial derivatives (value_array[] has at least 3*value_array_stride doubles).
  /// 2 for point, 1st and 2nd partial derivatives (value_array[] has at least 6*value_array_stride doubles).
  /// And so on.
  /// </param>
  /// <param name="value_array_stride">
  /// value_array_stride &gt;= 3.
  /// </param>
  /// <param name="value_array">
  /// An array with a capacity of at least 
  /// value_array_stride * ((order_capacity + 1) * (order_capacity + 2) / 2) 
  /// doubles.
  /// </param>
  /// <param name="values">
  /// After the call, values will use value_array to store point and derivative evaluations.
  /// </param>
  /// <returns>
  /// True if successful.
  /// </returns>
  static bool CreateFromLocalArrayForExperts(
    unsigned maximum_derivative_order,
    size_t value_array_stride,
    double* value_array,
    ON_SurfaceValues& values
  );

  /// <summary>
  /// NOTE WELL: CreateFromVectorArray is for experts dealing with unusual situations.
  /// Create a ON_SurfaceValues where the storage for the values is derivative values is managed externally.
  /// This is typically used by experts to easily get surface evaluation results stored in value_array[] 
  /// when the evaluation function returns the results in a ON_SurfaceValues class. 
  /// The caller is responsible for ensuring that the value_array[] memory is not freed or deleted 
  /// while the returned ON_SurfaceValues class is in scope. 
  /// Any copy of the returned values will not reference value_array[].
  /// </summary>
  /// <param name="order_capacity">
  /// 0 &lt;= derivative_order &lt;= ON_SurfaceValues::MaximumDerivativeOrder
  /// derivative_order = maximum order of a partial derivative that can be stored in value_array[].
  /// 1 for point and 1st partial derivatives (value_array[] has at least 3*value_array_stride doubles).
  /// 2 for point, 1st and 2nd partial derivatives (value_array[] has at least 6*value_array_stride doubles).
  /// And so on.
  /// </param>
  /// <param name="value_array">
  /// The capacity and count of value_array[] will be set to ((order_capacity + 1) * (order_capacity + 2) / 2).
  /// </param>
  /// <param name="values">
  /// After the call, values will use value_array to store point and derivative evaluations.
  /// Note that if values is copied, all derivative information will be lost. 
  /// This class is for experts dealing with unusual situations.
  /// </param>
  /// <returns>
  /// True if successful.
  /// </returns>
  static bool CreateFromVectorArrayForExperts(
    unsigned order_capacity,
    ON_SimpleArray<ON_3dVector>& value_array,
    ON_SurfaceValues& values
  );

  /// <summary>
  /// 
  /// </summary>
  /// <param name="order_capacity">
  /// 0 &lt;= derivative_order &lt;= ON_SurfaceValues::MaximumDerivativeOrder
  /// derivative_order = maximum order of a partial derivative that can be stored in value_array[].
  /// 1 for point and 1st partial derivatives (value_array[] has at least 3*value_array_stride doubles).
  /// 2 for point, 1st and 2nd partial derivatives (value_array[] has at least 6*value_array_stride doubles).
  /// And so on.
  /// </param>
  /// <returns>
  /// True if the capacity to store derivatives was reserved.
  /// </returns>
  bool ReserveDerivativeOrderCapacity(
    unsigned order_capacity
  );

  /// <summary>
  /// The order of the partial derivative returned by Derivative(i, j) is i + j.
  /// The memory to store partial derivatives can be allocated by calling
  /// ReserveDerivativeOrderCapacity(max_order).
  /// </summary>
  /// <returns>
  /// Returns the maximum order of a partial derivative 
  /// that can be stored.
  /// </returns>
  unsigned DerivativeOrderCapacity() const;

  ON_SurfaceValues() = default;
  ~ON_SurfaceValues();
  ON_SurfaceValues(const ON_SurfaceValues& src);
  ON_SurfaceValues operator=(const ON_SurfaceValues& src);

  static const ON_SurfaceValues Nan;

  void SetPoint(ON_3dPoint P);
  void ClearPoint();
  const ON_3dPoint Point() const;
  bool PointIsSet() const;

  void SetNormal(ON_3dVector N);
  void ClearNormal();
  const ON_3dVector Normal() const;
  bool NormalIsSet() const;

  void SetPrincipalCurvatures(double kappa1, double kappa2);
  void SetPrincipalCurvatures(ON_SurfaceCurvature kappa);
  void ClearPrincipalCurvatures();
  bool PrincipalCurvaturesSet() const;
  const ON_SurfaceCurvature PrincipalCurvatures() const;

  //void SetPrincipalVectorCurvatures(
  //  ON_3dVector K1, 
  //  ON_3dVector K2
  //);
  //void ClearPrincipalVectorCurvatures();
  //bool PrincipalVectorCurvaturesAreSet() const;
  //const ON_3dVector PrincipalVectorCurvature(unsigned i) const;

  void SetDerivative(unsigned i, unsigned j, ON_3dVector D);
  void ClearDerivative(unsigned i, unsigned j);
  void ClearDerivatives();
  bool DerivativeIsSet(unsigned i, unsigned j) const;
  bool DerivativesAreSet(unsigned order) const;

  /// <summary>
  /// If (u,v) are the surface parameters, then
  /// Derivative(0,0) = point,
  /// Derivative(1,0) = 1st partial with respect to u (D/Du).
  /// Derivative(0,1) = 1st partial with respect to v (D/Dv).
  /// Derivative(2,0) = 2nd partial with respect to u (D/Du^2).
  /// Derivative(1,1) = 2nd mixed partial (D/DuDv).
  /// Derivative(0,2) = 2nd partial with respect to v (D/Dv^2).
  /// Derivative(i,j) = (i+j)-th order partial D/Du^iDv^j.
  /// </summary>
  /// <param name="i">
  /// Number of partial derivatives in the 1st surface parameter.
  /// </param>
  /// <param name="j">
  /// Number of partial derivatives in the 2nd surface parameter.
  /// </param>
  /// <returns>Specified partial derivative.</returns>
  const ON_3dVector Derivative(unsigned i, unsigned j) const;

  /// <summary>
  /// Unsets all surface evaluation values.
  /// </summary>
  void Clear();

  /// <summary>
  /// Used by experts when calling legacy bispan evaluation code that takes (num_der, stride, ders) parameters.
  /// Pretend this does not exist.
  /// </summary>
  /// <param name="derivative_order_capacity">
  /// The returned value is the maximum order of a partial derivative that can be stored in derivative_values.
  /// </param>
  /// <param name="stride">
  /// Returns the number of doubles between successive partial derivatives.
  /// </param>
  /// <param name="derivative_values">
  /// Returns a pointer to an array of stride*(derivative_order_capacity + 1)*(derivative_order_capacity + 2)/2 doubles.
  /// </param>
  /// <returns>
  /// True if the returned information can be passed to a legacy bispan evaluator.
  /// </returns>
  bool GetDerivativeArrayForExperts(
    unsigned& derivative_order_capacity,
    size_t& stride,
    double*& derivative_values
  );

  /// <summary>
  /// Used by experts when calling legacy bispan evaluation code that takes (num_der, stride, ders) parameters.
  /// Pretend this does not exist.  
  /// </summary>
  /// <param name="max_derivative_order"></param>
  /// <param name="stride"></param>
  /// <param name="derivative_values"></param>
  void SetDerivativeArrayForExperts(
    unsigned max_derivative_order, 
    size_t stride, 
    const double* derivative_values
  );

private:
  /// <returns>
  /// True if this class should manage the m_values array.
  /// </returns>
  bool Internal_DerivativeMemoryIsManaged() const;

  /// <returns>
  /// True if and expert is managing the memory m_derivatives
  /// points at and that expert has made sure the memory will
  /// exist for the duration of this class's scope.
  /// </returns>
  bool Internal_DerivativeMemoryIsExternal() const;

  unsigned Internal_DerivativeOrderCapacity() const;

  unsigned Internal_DerivativeVectorCount() const;

  unsigned Internal_DerivativeVectorCapacity() const;

  /// <returns>
  /// Number of partial derivatives with order &;t;=max_order.
  /// (max_order+1)*(max_order+2)/2
  /// </returns>
  static unsigned Internal_DerivativeVectorCount(unsigned max_order);

  /// </param>
  /// <param name="derivative_order_capacity">
  /// derivative_order_capacity = maximum derivative order that can be stored.
  /// </param>
  void Internal_AllocateManagedDerivativeMemory(unsigned derivative_order_capacity);

  double* Internal_Derivative(unsigned i, unsigned j, bool bSet) const;
  void Internal_CopyFrom(const ON_SurfaceValues& src);
  void Internal_Destroy();

  enum MasksAndBits : unsigned char
  {
    /// <summary>
    ///  point_set bit is used in m_derivatives_count_etc
    /// </summary>
    point_set = 0x80u,

    /// <summary>
    ///  normal_set bit is used in m_derivatives_count_etc
    /// </summary>
    normal_set = 0x40u,

    /// <summary>
    ///  principal_curvatures_set bit is used in m_derivatives_count_etc
    /// </summary>
    principal_curvatures_set = 0x20u,

    ///// <summary>
    /////  principal_vector_curvatures_set bit is used in m_derivatives_count_etc
    ///// </summary>
    //principal_vector_curvatures_set = 0x10u,

    /// <summary>
    ///  derivatives_count_mask maxk is used with m_derivatives_count_etc AND m_derivatives_capacity_etc
    /// </summary>
    derivatives_count_mask = 0x0Fu,

    /// <summary>
    ///  derivatives_managed bit is used in m_derivatives_capacity_etc
    /// </summary>
    derivatives_managed = 0x10u,
  };

  // maximum derivative order set = (MasksAndBits::derivatives_count_mask & m_derivatives_count_etc);
  unsigned char m_derivatives_count_etc = 0;

  // maximum derivative order capacity = (MasksAndBits::derivatives_count_mask & m_derivatives_capacity_etc);
  // this class manages m_derivatives = (0 != (MasksAndBits::derivatives_managed & m_derivatives_capacity_etc));
  unsigned char m_derivatives_capacity_etc = 0;

  unsigned short m_reserved = 0;
  unsigned m_derivatives_stride = 0;

  // If (0 != (MasksAndBits::derivatives_managed & m_derivatives_capacity_etc)), 
  // then this class manages the memory m_derivatives points at.  
  // Otherwise the memory is expertly managed outside this class.
  // If nullptr != m_derivatives, then m_derivatives points to an array
  // of at least m_derivatives_stride*Internal_DerivativeVectorCapacity() doubles, where N = Internal_DerivativeCapacity();
  double* m_derivatives = nullptr;

  ON_3dPoint m_P;
  ON_3dPoint m_N;
  // ON_3dVector m_K[2]; // principal vector curvatures
  ON_SurfaceCurvature m_kappa; // principal scalar curvatures
};


#if defined(ON_DLL_TEMPLATE)

ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_2dPoint>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_3dPoint>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_4dPoint>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_2dVector>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_3dVector>;

ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_2fPoint>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_3fPoint>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_4fPoint>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_2fVector>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_3fVector>;

ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_Color>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_SurfaceCurvature>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_Interval>;

ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_2dex>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_3dex>;

ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_COMPONENT_INDEX>;

#endif

/////////////////////////////////////////////////////////////////
//

class ON_CLASS ON_2dPointArray : public ON_SimpleArray<ON_2dPoint>
{
public:
  // see ON_SimpleArray class definition comments for constructor documentation
  ON_2dPointArray();
  ON_2dPointArray(int);
  ON_2dPointArray( const ON_2dPointArray& );
  ON_2dPointArray& operator=( const ON_2dPointArray& );

  bool GetBBox( // returns true if successful
         double boxmin[2],
         double boxmax[2],
         bool bGrowBox = false  // true means grow box
         ) const;

  bool Transform( const ON_Xform& );
  bool SwapCoordinates(int,int);
};


/////////////////////////////////////////////////////////////////
//

class ON_CLASS ON_2fPointArray : public ON_SimpleArray<ON_2fPoint>
{
public:
  // see ON_SimpleArray class definition comments for constructor documentation
  ON_2fPointArray();
  ON_2fPointArray(int);
  ON_2fPointArray(const ON_2fPointArray&);
  ON_2fPointArray& operator=( const ON_2fPointArray& );

  bool GetBBox( // returns true if successful
         float boxmin[2],
         float boxmax[2],
         bool bGrowBox = false  // true means grow box
         ) const;
  bool Transform( const ON_Xform& );
  bool SwapCoordinates(int,int);
};


/////////////////////////////////////////////////////////////////
//

class ON_CLASS ON_3dPointArray : public ON_SimpleArray<ON_3dPoint>
{
public:
  // see ON_SimpleArray class definition comments for constructor documentation
  ON_3dPointArray();
  ON_3dPointArray(int);
  ON_3dPointArray(const ON_SimpleArray<ON_3dPoint>&);
  ON_3dPointArray& operator=( const ON_3dPointArray& );
  ON_3dPointArray(const ON_SimpleArray<ON_3fPoint>&);
  ON_3dPointArray& operator=( const ON_SimpleArray<ON_3fPoint>& );

  // Description:
  //   Create 3d point list
  // Parameters:
  //   point_dimension - [in] dimension of input points (2 or 3)
  //   bRational - [in] true if points are in homogeneous rational form
  //   point_count - [in] number of points
  //   point_stride - [in] number of doubles to skip between points
  //   points - [in] array of point coordinates
  bool Create(
    int point_dimension,
    int bRational,
    int point_count,
    int point_stride,
    const double* points
    );

  // Description:
  //   Create 3d point list
  // Parameters:
  //   point_dimension - [in] dimension of input points (2 or 3)
  //   bRational - [in] true if points are in homogeneous rational form
  //   point_count - [in] number of points
  //   point_stride - [in] number of doubles to skip between points
  //   points - [in] array of point coordinates
  bool Create(
    int point_dimension,
    int bRational,
    int point_count,
    int point_stride,
    const float* points
    );

  // Description: 
  //   Get 3d axis aligned bounding box.
  // Returns:
  //   3d bounding box of point list.
  ON_BoundingBox BoundingBox() const;

  // Description: 
  //   Get 3d axis aligned bounding box
  //   of a subset of the points.
  // Parameters:
  //   from - [in] start of the box calculation
  //   count - [in] number of items computed
  // Returns:
  //   3d bounding box of point list.
  ON_BoundingBox BoundingBox(int from, int count) const;

  // Description:
  //   Get 3d axis aligned bounding box or the union
  //   of the input box with the point list's bounding box.
  // Parameters:
  //   bbox - [in/out] 3d axis aligned bounding box
  //   bGrowBox - [in] (default=false) 
  //     If true, then the union of the input bbox and the 
  //     point list's bounding box is returned in bbox.  
  //     If false, the point list's bounding box is returned in bbox.
  // Returns:
  //   true if successful.
  bool GetBoundingBox( 
    ON_BoundingBox& bbox,
    int bGrowBox = false
    ) const;

  // Description:
  //   Get axis aligned bounding box.
  // Parameters:
  //   boxmin - [in/out] array of 3 doubles
  //   boxmax - [in/out] array of 3 doubles
  //   bGrowBox - [in] (default=false) 
  //     If true, then the union of the input bounding box and the 
  //     object's bounding box is returned.
  //     If false, the object's bounding box is returned.
  // Returns:
  //   true if object has bounding box and calculation was successful
  bool GetBBox(
         double boxmin[3],
         double boxmax[3],
         bool bGrowBox = false
         ) const;

  /*
	Description:
    Get tight bounding box of the point list.
	Parameters:
		tight_bbox - [in/out] tight bounding box
		bGrowBox -[in]	(default=false)			
      If true and the input tight_bbox is valid, then returned
      tight_bbox is the union of the input tight_bbox and the 
      tight bounding box of the point list.
		xform -[in] (default=nullptr)
      If not nullptr, the tight bounding box of the transformed
      point list is calculated.  The point list is not modified.
	Returns:
    True if the returned tight_bbox is set to a valid 
    bounding box.
  */
	bool GetTightBoundingBox( 
			ON_BoundingBox& tight_bbox, 
      bool bGrowBox = false,
			const ON_Xform* xform = nullptr
      ) const;

  // Description:
  //   Transform points by applying xform to each point.
  // Parameters:
  //   xform - [in] transformation matrix
  // Returns:
  //   true if successful.
  bool Transform( 
    const ON_Xform& xform 
    );

  // Description:
  //   Swaps point coordinate values with indices i and j.
  // Parameters:
  //   i - [in] coordinate index
  //   j - [in] coordinate index
  // Returns:
  //   true if successful.
  // Example:
  //   The call SwapCoordinates(0,2) would swap the x and z
  //   coordinates of each point in the array.
  bool SwapCoordinates(
    int i,
    int j
    );

  // Description:
  //   Rotate points about a center and axis.  A positive angle
  //   results in a counter-clockwise rotation about the axis
  //   of rotation.
  // Parameters:
  //   sin_angle - [in] sine of rotation angle
  //   cos_angle - [in] cosine of rotation angle
  //   axis_of_rotation - [in] axis of rotation
  //   center_of_rotation - [in] center (fixed point) of rotation
  // Returns:
  //   true if successful.
  bool Rotate(
        double sin_angle,
        double cos_angle,
        const ON_3dVector& axis_of_rotation,
        const ON_3dPoint& center_of_rotation
        );

  // Description:
  //   Rotate points about a center and axis.  A positive angle
  //   results in a counter-clockwise rotation about the axis
  //   of rotation.
  // Parameters:
  //   angle - [in] angle in radians.  Polsine of rotation angle
  //   cos_angle - [in] cosine of rotation angle
  //   axis_of_rotation - [in] axis of rotation
  //   center_of_rotation - [in] center (fixed point) of rotation
  // Returns:
  //   true if successful.
  bool Rotate(
        double angle_in_radians,
        const ON_3dVector& axis_of_rotation,
        const ON_3dPoint& center_of_rotation
        );

  // Description:
  //   Translate a polyline
  // Parameters:
  //   delta - [in] translation vectorsine of rotation angle
  // Returns:
  //   true if successful.
  bool Translate(
        const ON_3dVector& delta
        );

  /*
  Description:
    Get the index of the point in the array that is closest
    to P.
  Parameters:
    P - [in]
    closest_point_index - [out]
    maximum_distance - [in] optional distance constraint.
        If maximum_distance > 0, then only points Q with
        |P-Q| <= maximum_distance are returned.
  Returns:
    True if a point is found; in which case *closest_point_index
    is the index of the point.  False if no point is found
    or the input is not valid.
  See Also:
    ON_GetClosestPointInPointList
    ON_PointCloud::GetClosestPoint
  */
  bool GetClosestPoint( 
          ON_3dPoint P,
          int* closest_point_index,
          double maximum_distance = 0.0
          ) const;


};


/////////////////////////////////////////////////////////////////
//

class ON_CLASS ON_3fPointArray : public ON_SimpleArray<ON_3fPoint>
{
public:
  // see ON_SimpleArray class definition comments for constructor documentation
  ON_3fPointArray();
  ON_3fPointArray(int);
  ON_3fPointArray(const ON_3fPointArray&);
  ON_3fPointArray& operator=( const ON_3fPointArray& );

  bool GetBBox(
         float boxmin[3],
         float boxmax[3],
         bool bGrowBox = false
         ) const;

  bool Transform( const ON_Xform& );

  bool SwapCoordinates(int,int);
};


/////////////////////////////////////////////////////////////////
//

class ON_CLASS ON_4dPointArray : public ON_SimpleArray<ON_4dPoint>
{
public:
  // see ON_SimpleArray class definition comments for constructor documentation
  ON_4dPointArray();
  ON_4dPointArray(int);
  ON_4dPointArray(const ON_4dPointArray&);
  ON_4dPointArray& operator=( const ON_4dPointArray& );

  bool Transform( const ON_Xform& );
  bool SwapCoordinates(int,int);
};


/////////////////////////////////////////////////////////////////
//

class ON_CLASS ON_4fPointArray : public ON_SimpleArray<ON_4fPoint>
{
public:
  // see ON_SimpleArray class definition comments for constructor documentation
  ON_4fPointArray();
  ON_4fPointArray(int);
  ON_4fPointArray(const ON_4fPointArray&);
  ON_4fPointArray& operator=( const ON_4fPointArray& );

  bool Transform( const ON_Xform& );
  bool SwapCoordinates(int,int);
};


/////////////////////////////////////////////////////////////////
//

class ON_CLASS ON_2dVectorArray : public ON_SimpleArray<ON_2dVector>
{
public:
  // see ON_SimpleArray class definition comments for constructor documentation
  ON_2dVectorArray();
  ON_2dVectorArray(int);
  ON_2dVectorArray(const ON_2dVectorArray&);
  ON_2dVectorArray& operator=( const ON_2dVectorArray& );

  bool GetBBox(
         double boxmin[2],
         double boxmax[2],
         bool bGrowBox = false
         ) const;

  bool Transform( const ON_Xform& );
  bool SwapCoordinates(int,int);
};


/////////////////////////////////////////////////////////////////
//

class ON_CLASS ON_2fVectorArray : public ON_SimpleArray<ON_2fVector>
{
public:
  // see ON_SimpleArray class definition comments for constructor documentation
  ON_2fVectorArray();
  ON_2fVectorArray(int);
  ON_2fVectorArray(const ON_2fVectorArray&);
  ON_2fVectorArray& operator=( const ON_2fVectorArray& );

  bool GetBBox(
         float boxmin[2],
         float boxmax[2],
         bool = false
         ) const;

  bool Transform( const ON_Xform& );
  bool SwapCoordinates(int,int);
};


/////////////////////////////////////////////////////////////////
//

class ON_CLASS ON_3dVectorArray : public ON_SimpleArray<ON_3dVector>
{
public:
  ON_3dVectorArray();
  ON_3dVectorArray(int);
  ON_3dVectorArray(const ON_3dVectorArray&);
  ON_3dVectorArray& operator=( const ON_3dVectorArray& );

  bool GetBBox(
         double boxmin[3],
         double boxmax[3],
         bool bGrowBow = false
         ) const;

  bool Transform( const ON_Xform& );
  bool SwapCoordinates(int,int);
};

/////////////////////////////////////////////////////////////////
//

class ON_CLASS ON_3fVectorArray : public ON_SimpleArray<ON_3fVector>
{
public:
  ON_3fVectorArray();
  ON_3fVectorArray(int);
  ON_3fVectorArray(const ON_3fVectorArray&);
  ON_3fVectorArray& operator=( const ON_3fVectorArray& );

  bool GetBBox(
         float boxmin[3],
         float boxmax[3],
         bool bGrowBox = false
         ) const;

  bool Transform( const ON_Xform& );
  bool SwapCoordinates(int,int);
};

class ON_CLASS ON_3dPointListRef
{
public:


  ON_3dPointListRef()
    : m_point_count(0)
    , m_point_stride(0)
    , m_dP(0)
    , m_fP(0)
  {}

  /*
  Description:
    Construct a point list that references the mesh vertex list.
  Remarks:
    If the mesh has double precision vertices, then the point
    list will refer to them; otherwise, the point list will
    refer to the single precision vertices.
  */
  ON_3dPointListRef(
    const class ON_Mesh* mesh
    );

  /*
  Description:
    Construct a point list that references the points
    in a simple array of ON_3dPoint objects.
  */
  ON_3dPointListRef(
    const class ON_SimpleArray<ON_3dPoint>& point_array
    );

  /*
  Description:
    Construct a point list that references the points
    in a simple array of ON_3fPoint objects.
  */
  ON_3dPointListRef(
    const class ON_SimpleArray<ON_3fPoint>& point_array
    );

  static const ON_3dPointListRef EmptyPointList;

  static
  ON_3dPointListRef FromDoubleArray(
    size_t point_count,
    size_t point_stride,
    const double* point_array
    );

  static
  ON_3dPointListRef FromFloatArray(
    size_t point_count,
    size_t point_stride,
    const float* point_array
    );

  static
  ON_3dPointListRef FromPointArray(
    const class ON_SimpleArray<ON_3dPoint>& point_array
    );

  static
  ON_3dPointListRef FromPointArray(
    const class ON_SimpleArray<ON_3fPoint>& point_array
    );

  static
  ON_3dPointListRef FromMesh(
    const class ON_Mesh* mesh
    );

  /*
  Returns:
    A copy of the referenced points in an ON_SimpleArray<ON_3dPoint>.
  */
  ON_SimpleArray<ON_3dPoint> To3dPointArray() const;

  /*
  Returns:
    A copy of the referenced points in an ON_SimpleArray<ON_3fPoint>.
  */
  ON_SimpleArray<ON_3fPoint> To3fPointArray() const;

  /*
  Description:
    Set this point list to reference points with double coordinates.
  Parameters:
    point_count - [in]
      number of points
    point_stride - [in] (>= 3)
      number of doubles between points.
    point_array - [in]
      pointer to the first coordinate of the first point.
  Returns:
    Number of points in the list.
  */
  unsigned int SetFromDoubleArray(
    size_t point_count,
    size_t point_stride,
    const double* point_array
    );

  /*
  Description:
    Set this point list to reference points with float coordinates.
  Parameters:
    point_count - [in]
      number of points
    point_stride - [in] (>= 3)
      number of floats between points.
    point_array - [in]
      pointer to the first coordinate of the first point.
  Returns:
    Number of points in the list.
  */
  unsigned int SetFromFloatArray(
    size_t point_count,
    size_t point_stride,
    const float* point_array
    );

  /*
  Description:
    Set this point list to reference a mesh vertex list.
  Parameters:
    mesh - [in]
  Returns:
    Number of points in the list.
  */
  unsigned int SetFromMesh(
    const class ON_Mesh* mesh
    );

  /*
  Returns:
    0: no points
    1: single precision points (float coordinates)
    2: double precision points (double coordinates)
  */
  unsigned int Precision() const;

  /*
  Returns:
    true if the points are double precision
  */
  bool DoublePrecision() const;

  /*
  Returns:
    true if the points are single precision
  */
  bool SinglePrecision() const;

  /*
  Description:
    Copy point location into buffer and return it as an ON_3dPoint.
  Parameters:
    point_index - [in]
    buffer - [out]
      If point_index is a valid index, the point coordinates
      are copied to buffer[]; otherwise the buffer coordinates
      are set to ON_UNSET_VALUE.
      You must insure buffer is not null, has proper alignment
      for storing doubles, and is large enough to store three
      doubles.
  Returns:
    A reference to an ON_3dPoint which is a cast of buffer.
  Remarks:
    This is the fastest and most efficient way to get a the
    location of a point into memory you are managing.
  */
  inline const class ON_3dPoint& GetPoint(
    unsigned int point_index, 
    double buffer[3]
    ) const
  {
    if ( point_index < m_point_count )
    {
      if ( m_dP )
      {
        const double* p = m_dP + (point_index*m_point_stride);
        buffer[0]  = *p++;
        buffer[1]  = *p++;
        buffer[2]  = *p;
      }
      else
      {
        const float* p = m_fP + (point_index*m_point_stride);
        buffer[0]  = *p++;
        buffer[1]  = *p++;
        buffer[2]  = *p;
      }
    }
    else
    {
      buffer[0] = buffer[1] = buffer[2] = ON_UNSET_VALUE;
    }
    return *((const ON_3dPoint*)buffer);
  }

  /*
  Parameters:
    point_index - [in]
  Returns:
    If point_index is a valid index, the point location is returned.
    Otherwise ON_3dPoint::UnsetPoint is returned.
  */
  inline ON_3dPoint Point(
    unsigned int point_index
    ) const
  {
    double buffer[3];
    if ( point_index < m_point_count )
    {
      if ( m_dP )
      {
        const double* p = m_dP + (point_index*m_point_stride);
        buffer[0]  = *p++;
        buffer[1]  = *p++;
        buffer[2]  = *p;
      }
      else
      {
        const float* p = m_fP + (point_index*m_point_stride);
        buffer[0]  = *p++;
        buffer[1]  = *p++;
        buffer[2]  = *p;
      }
    }
    else
    {
      buffer[0] = buffer[1] = buffer[2] = ON_UNSET_VALUE;
    }
    return *((const ON_3dPoint*)buffer);
  }

  inline ON_3dPoint operator[](int point_index) const
  {
    double buffer[3];
    if ( point_index >= 0 && ((unsigned int)point_index) < m_point_count )
    {
      if ( m_dP )
      {
        const double* p = m_dP + (point_index*m_point_stride);
        buffer[0]  = *p++;
        buffer[1]  = *p++;
        buffer[2]  = *p;
      }
      else
      {
        const float* p = m_fP + (point_index*m_point_stride);
        buffer[0]  = *p++;
        buffer[1]  = *p++;
        buffer[2]  = *p;
      }
    }
    else
    {
      buffer[0] = buffer[1] = buffer[2] = ON_UNSET_VALUE;
    }
    return *((const ON_3dPoint*)buffer);  
  }

  inline ON_3dPoint operator[](unsigned int point_index) const
  {
    double buffer[3];
    if ( point_index < m_point_count )
    {
      if ( m_dP )
      {
        const double* p = m_dP + (point_index*m_point_stride);
        buffer[0]  = *p++;
        buffer[1]  = *p++;
        buffer[2]  = *p;
      }
      else
      {
        const float* p = m_fP + (point_index*m_point_stride);
        buffer[0]  = *p++;
        buffer[1]  = *p++;
        buffer[2]  = *p;
      }
    }
    else
    {
      buffer[0] = buffer[1] = buffer[2] = ON_UNSET_VALUE;
    }
    return *((const ON_3dPoint*)buffer);
  }

  inline ON_3dPoint operator[](ON__INT64 point_index) const
  {
    double buffer[3];
    if ( point_index >= 0 && ((ON__UINT64)point_index) < m_point_count )
    {
      if ( m_dP )
      {
        const double* p = m_dP + (point_index*m_point_stride);
        buffer[0]  = *p++;
        buffer[1]  = *p++;
        buffer[2]  = *p;
      }
      else
      {
        const float* p = m_fP + (point_index*m_point_stride);
        buffer[0]  = *p++;
        buffer[1]  = *p++;
        buffer[2]  = *p;
      }
    }
    else
    {
      buffer[0] = buffer[1] = buffer[2] = ON_UNSET_VALUE;
    }
    return *((const ON_3dPoint*)buffer);  
  }

  inline ON_3dPoint operator[](ON__UINT64 point_index) const
  {
    double buffer[3];
    if ( point_index < m_point_count )
    {
      if ( m_dP )
      {
        const double* p = m_dP + (point_index*m_point_stride);
        buffer[0]  = *p++;
        buffer[1]  = *p++;
        buffer[2]  = *p;
      }
      else
      {
        const float* p = m_fP + (point_index*m_point_stride);
        buffer[0]  = *p++;
        buffer[1]  = *p++;
        buffer[2]  = *p;
      }
    }
    else
    {
      buffer[0] = buffer[1] = buffer[2] = ON_UNSET_VALUE;
    }
    return *((const ON_3dPoint*)buffer);  
  }

  inline unsigned int PointCount() const
  {
    return m_point_count;
  }

  inline unsigned int PointStride() const
  {
    return m_point_stride;
  }

  inline const double* PointDoubleArray() const
  {
    return m_dP;
  }

  inline const float* PointFloatArray() const
  {
    return m_fP;
  }

  /*
  Returns:
    Number of points copied to face_points[] array.
  */
  unsigned int GetMeshFacePoints(
    const class ON_MeshFace* mesh_face,
    ON_3dPoint face_points[4]
    ) const;

  /*
  Returns:
    Number of points copied to ngon_points[] array.
  */
  unsigned int GetMeshNgonPoints(
    const class ON_MeshNgon* mesh_ngon,
    size_t ngon_points_capacity,
    class ON_3dPoint* ngon_points
    ) const;

  /*
  Returns:
    Number of points copied to ngon_points[] array.
  */
  unsigned int GetMeshNgonPoints(
    const class ON_MeshNgon* mesh_ngon,
    ON_SimpleArray<ON_3dPoint>& ngon_points
    ) const;

  /*
  Returns:
    Number of points copied to quad_points[] array.
  */
  unsigned int GetQuadPoints(
    const int quad_point_indices[4],
    class ON_3dPoint quad_points[4]
    ) const;

  /*
  Returns:
    Number of points copied to quad_points[] array.
  */
  unsigned int GetQuadPoints(
    const unsigned int quad_point_indices[4],
    class ON_3dPoint quad_points[4]
    ) const;

  /*
  Returns:
    Number of points copied to triangle_points[] array.
  */
  unsigned int GetTrianglePoints(
    const int triangle_point_indices[3],
    class ON_3dPoint triangle_points[3]
    ) const;

  /*
  Returns:
    Number of points copied to triangle_points[] array.
  */
  unsigned int GetTrianglePoints(
    const unsigned int triangle_point_indices[3],
    class ON_3dPoint triangle_points[3]
    ) const;  

  /*
  Returns:
    Number of points copied to points[] array.
  */
  unsigned int GetPoints(
    int point_index_count,
    const int* point_index_list,
    class ON_3dPoint* points
    ) const;

  /*
  Returns:
    Number of points copied to points[] array.
  */
  unsigned int GetPoints(
    unsigned int point_index_count,
    const unsigned int* point_index_list,
    class ON_3dPoint* points
    ) const;

  /*
  Returns:
    Number of points copied to points[] array.
  */
  unsigned int GetPoints(
    const ON_SimpleArray<int>& point_index_list,
    ON_SimpleArray<ON_3dPoint>& points
    ) const;

  /*
  Returns:
    Number of points copied to points[] array.
  */
  unsigned int GetPoints(
    int point_index_count,
    const int* point_index_list,
    ON_SimpleArray<ON_3dPoint>& points
    ) const;

  /*
  Returns:
    Number of points copied to points[] array.
  */
  unsigned int GetPoints(
    unsigned int point_index_count,
    const unsigned int* point_index_list,
    ON_SimpleArray<ON_3dPoint>& points
    ) const;
  
private:
  unsigned int m_point_count;
  unsigned int m_point_stride;
  const double* m_dP;
  const float* m_fP;
};


/*
Class ON_2dSize
*/
class ON_CLASS ON_2dSize
{
public:
  // Default construction intentionally leaves x and y uninitialized.
  // Use something like
  //   ON_2dSize pt(1.0,2.0);
  // or 
  //  ON_2dSize pt = ON_2dSize::Zero;
  // when you need an initialized ON_2dSize.
  ON_2dSize() = default;

  ~ON_2dSize() = default;
  ON_2dSize(const ON_2dSize& ) = default;
  ON_2dSize& operator=(const ON_2dSize& ) = default;

  ON_2dSize(
    double cx,
    double cy
  );

  /*
  Dictionary compare.
  Returns: 
  -1: lhs < rhs
   0: lsh == rsh
  +1: lhs > rhs
  */
  static int Compare(
    const ON_2dSize& lhs,
    const ON_2dSize& rhs
  );

  /*
  Dictionary compare.
  Returns: 
  -1: lhs < rhs
   0: lsh == rsh
  +1: lhs > rhs
  */
  static int ComparePointer(
    const ON_2dSize* lhs,
    const ON_2dSize* rhs
  );

public:
  static const ON_2dSize Zero;  // (0.0,0.0)
  static const ON_2dSize Unset; // (ON_UNSET_DOUBLE,ON_UNSET_DOUBLE)
  
public:
  /*
  Returns:
    true if both cx and cy are 0.0
  */
  bool IsZero() const;

  /*
  Returns:
    true if neither cx nor cy are ON_UNSET_DOUBLE.
  */
  bool IsSet() const;
  
public:
  double cx;
  double cy;
};

ON_DECL
bool operator==(
  const ON_2dSize& lhs,
  const ON_2dSize& rhs
  );

ON_DECL
bool operator!=(
  const ON_2dSize& lhs,
  const ON_2dSize& rhs
  );

#if defined(ON_DLL_TEMPLATE)

ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_2dSize>;

#endif

/*
Class ON_4iRect
  For those situations where a Windows SDK RECT or MFC CRect 
  value needs to be used in code that does not link with MFC.
  If you want a traditional bounding box, use ON_2dBoundingBox.
*/
class ON_CLASS ON_4dRect
{
public:
  // Default construction intentionally leaves x and y uninitialized.
  // Use something like
  //   ON_4dRect pt(1.0,2.0,3.0,4.0);
  // or 
  //  ON_4dRect pt = ON_4dRect::Zero;
  // when you need an initialized ON_4dRect.
  ON_4dRect() = default;

  ~ON_4dRect() = default;
  ON_4dRect(const ON_4dRect& ) = default;
  ON_4dRect& operator=(const ON_4dRect& ) = default;

  ON_4dRect(
  double left,
  double top,
  double right,
  double bottom
  );

  ON_4dRect(const ON_2dPoint topLeft, const ON_2dPoint& bottomRight);
  ON_4dRect(const ON_2dPoint& point, const ON_2dSize& size);

public:
  static const ON_4dRect Zero;  // (0.0,0.0,0.0,0.0)
  static const ON_4dRect Unset; // (ON_UNSET_INT_INDEX,ON_UNSET_INT_INDEX,ON_UNSET_INT_INDEX,ON_UNSET_INT_INDEX)

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

  double Width(void) const;
  double Height(void) const;

  const ON_2dSize Size(void) const;
  
  const ON_2dPoint CenterPoint(void) const;
  const ON_2dPoint TopLeft(void) const;
  const ON_2dPoint BottomRight(void) const;

  bool  IntersectRect(const ON_4dRect* r1, const ON_4dRect* r2);
  bool  IntersectRect(const ON_4dRect& r1, const ON_4dRect& r2);

  bool IsRectEmpty(void) const;
  bool IsRectNull(void) const;
  void SetRectEmpty(void) { *this = Zero; }
  void SetRect(double l, double t, double r, double b);

  bool PtInRect(const ON_2dPoint& pt) const;

  void OffsetRect(double, double);
  void OffsetRect(const ON_2dVector&);
  void InflateRect(double, double);
  void InflateRect(double, double, double, double);
  void DeflateRect(double, double);
  bool SubtractRect(const ON_4dRect* rect1, const ON_4dRect* rect2);

  void NormalizeRect();

public:
  double left;
  double top;
  double right;
  double bottom;
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_4dRect>;
#endif


ON_DECL
bool operator==(const ON_4dRect&, const ON_4dRect&);

ON_DECL
bool operator!=(const ON_4dRect&, const ON_4dRect&);

/*
Description:
  Tool for efficiently calculating a boundary polyline winding number 
  with input tools that do not require the boundary polyline to be
  a contiguous array of points.
*/
class ON_CLASS ON_WindingNumber
{
public:
  ON_WindingNumber() = default;
  ~ON_WindingNumber() = default;
  ON_WindingNumber(const ON_WindingNumber&) = default;
  ON_WindingNumber& operator=(const ON_WindingNumber&) = default;

public:
  static const ON_WindingNumber Unset;

public:
  /*
  Description:
    The calculation of the winding number begins with a call to SetWindingPoint().
  Parameters:
    x - [in]
    y - [in]
      The coordinates of the winding point are (x,y).
  Remarks:
    Calling SetWindingPoint() erases results of any previous calculations.
  */
  void SetWindingPoint(double x, double y);

  /*
  Description:
    The calculation of the winding number begins with a call to SetWindingPoint().
  Parameters:
    winding_point - [in]
  Remarks:
    Calling SetWindingPoint() erases results of any previous calculations.
  */
  void SetWindingPoint(ON_2dPoint winding_point);

  /*
  Description:
    After calling SetWindingPoint(), the boundary may be specified by one or more calls to
    various AddBoundary functions.
    The boundary may be specified one point at a time, one edge at a time, portions of the boundary
    at a time, or the entire boundary in a single call. The edges may be added in any order.
    The caller is responsible for insuring the collection calls to AddBoundary() results in a
    a continuous, oriented, and closed polyline.
  Parameters:
    p - [in]
      next point in boundary.
  Returns:
    Number of boundary edge segments added.
  */
  ON__UINT32 AddBoundary(ON_2dPoint p);

  /*
  Description:
    After calling SetWindingPoint(), the boundary may be specified by one or more calls to
    various AddBoundary functions.
    The boundary may be specified one point at a time, one edge at a time, portions of the boundary
    at a time, or the entire boundary in a single call. The edges may be added in any order.
    The caller is responsible for insuring the collection calls to AddBoundary() results in a
    a continuous, oriented, and closed polyline.
  Parameters:
    p - [in]
      start of edge segment. 
      Caller is responsible for insuring coordinates of p are valid doubles.
    q - [in]
      end of edge segment
      Caller is responsible for insuring coordinates of q are valid doubles.
      The calculation tolerates p==q.
  Returns:
    Number of boundary edge segments added.
  */
  ON__UINT32 AddBoundary(ON_2dPoint p, ON_2dPoint q);

  /*
  Description:
    After calling SetWindingPoint(), the boundary may be specified by one or more calls to
    various AddBoundary functions.
    The boundary may be specified one point at a time, one edge at a time, portions of the boundary
    at a time, or the entire boundary in a single call. The edges may be added in any order.
    The caller is responsible for insuring the collection calls to AddBoundary() results in a
    a continuous, oriented, and closed polyline.
  Parameters:
    point_count - [in] >= 2
      number of points in boundary_points[] array.
    point_stride - [in] >= 2
      The i-th point has coordinates (boundary_points[i*point_stride],boundary_points[i*point_stride+1]).
    boundary_points - [in]
      Boundary points.
    bCloseBoundary - [in]
      If true, an edge segment is added from the last boundary point to the first boundary point.
  Returns:
    Number of boundary edge segments added.
  Remarks:
    The calculation tolerates zero length edge segments. The caller is responsible for insuring the
    coordinates in boundary_points[] are valid doubles.
  */
  ON__UINT32 AddBoundary(size_t point_count, size_t point_stride, const double* boundary_points, bool bCloseBoundary);

  /*
  Description:
    After calling SetWindingPoint(), the boundary may be specified by one or more calls to
    various AddBoundary functions.
    The boundary may be specified one point at a time, one edge at a time, portions of the boundary
    at a time, or the entire boundary in a single call. The edges may be added in any order.
    The caller is responsible for insuring the collection calls to AddBoundary() results in a
    a continuous, oriented, and closed polyline.
  Parameters:
    point_count - [in] >= 2
      number of points in boundary_points[] array.
    point_stride - [in] >= 2
      The i-th point has coordinates (boundary_points[i*point_stride],boundary_points[i*point_stride+1]).
    boundary_points - [in]
      Boundary points.
    bCloseBoundary - [in]
      If true, an edge segment is added from the last boundary point to the first boundary point.
  Returns:
    Number of boundary edge segments added.
  Remarks:
    The calculation tolerates zero length edge segments. The caller is responsible for insuring the
    coordinates in boundary_points[] are valid doubles.
  */
  ON__UINT32 AddBoundary(size_t point_count, size_t point_stride, const float* boundary_points, bool bCloseBoundary);

  /*
  Description:
    After calling SetWindingPoint(), the boundary may be specified by one or more calls to
    various AddBoundary functions.
    The boundary may be specified one point at a time, one edge at a time, portions of the boundary
    at a time, or the entire boundary in a single call. The edges may be added in any order.
    The caller is responsible for insuring the collection calls to AddBoundary() results in a
    a continuous, oriented, and closed polyline.
  Parameters:
    point_count - [in] >= 2
      number of points in boundary_points[] array.
    point_stride - [in] >= 2
      The i-th point has coordinates (boundary_points[i*point_stride],boundary_points[i*point_stride+1]).
    boundary_points - [in]
      Boundary points.
    bCloseBoundary - [in]
      If true, an edge segment is added from the last boundary point to the first boundary point.
  Returns:
    Number of boundary edge segments added.
  Remarks:
    The calculation tolerates zero length edge segments. The caller is responsible for insuring the
    coordinates in boundary_points[] are valid doubles.
  */
  ON__UINT32 AddBoundary(size_t point_count, size_t point_stride, const int* boundary_points, bool bCloseBoundary);

  /*
  Description:
    After calling SetWindingPoint(), the boundary may be specified by one or more calls to
    various AddBoundary functions.
    The boundary may be specified one point at a time, one edge at a time, portions of the boundary
    at a time, or the entire boundary in a single call. The edges may be added in any order.
    The caller is responsible for insuring the collection calls to AddBoundary() results in a
    a continuous, oriented, and closed polyline.
  Parameters:
    point_count - [in] >= 2
      number of points in boundary_points[] array.
    boundary_points - [in]
      Boundary points.
    bCloseBoundary - [in]
      If true, an edge segment is added from the last boundary point to the first boundary point.
  Returns:
    Number of boundary edge segments added.
  Remarks:
    The calculation tolerates zero length edge segments. The caller is responsible for insuring the
    coordinates in boundary_points[] are valid doubles.
  */
  ON__UINT32 AddBoundary(size_t point_count, const ON_2dPoint* boundary_points, bool bCloseBoundary);

  /*
  Description:
    After calling SetWindingPoint(), the boundary may be specified by one or more calls to
    various AddBoundary functions.
    The boundary may be specified one point at a time, one edge at a time, portions of the boundary
    at a time, or the entire boundary in a single call. The edges may be added in any order.
    The caller is responsible for insuring the collection calls to AddBoundary() results in a
    a continuous, oriented, and closed polyline.
  Parameters:
    point_count - [in] >= 2
      number of points in boundary_points[] array.
    boundary_points - [in]
      Boundary points.
    bCloseBoundary - [in]
      If true, an edge segment is added from the last boundary point to the first boundary point.
  Returns:
    Number of boundary edge segments added.
  Remarks:
    The calculation tolerates zero length edge segments. The caller is responsible for insuring the
    coordinates in boundary_points[] are valid doubles.
  */
  ON__UINT32 AddBoundary(size_t point_count, const ON_3dPoint* boundary_points, bool bCloseBoundary);

  /*
  Description:
    After calling SetWindingPoint(), the boundary may be specified by one or more calls to
    various AddBoundary functions.
    The boundary may be specified one point at a time, one edge at a time, portions of the boundary
    at a time, or the entire boundary in a single call. The edges may be added in any order.
    The caller is responsible for insuring the collection calls to AddBoundary() results in a
    a continuous, oriented, and closed polyline.
  Parameters:
    point_count - [in] >= 2
      number of points in boundary_points[] array.
    boundary_points - [in]
      Boundary points.
    bCloseBoundary - [in]
      If true, an edge segment is added from the last boundary point to the first boundary point.
  Returns:
    Number of boundary edge segments added.
  Remarks:
    The calculation tolerates zero length edge segments. The caller is responsible for insuring the
    coordinates in boundary_points[] are valid doubles.
  */
  ON__UINT32 AddBoundary(size_t point_count, const ON_2fPoint* boundary_points, bool bCloseBoundary);

  /*
  Description:
    After calling SetWindingPoint(), the boundary may be specified by one or more calls to
    various AddBoundary functions.
    The boundary may be specified one point at a time, one edge at a time, portions of the boundary
    at a time, or the entire boundary in a single call. The edges may be added in any order.
    The caller is responsible for insuring the collection calls to AddBoundary() results in a
    a continuous, oriented, and closed polyline.
  Parameters:
    point_count - [in] >= 2
      number of points in boundary_points[] array.
    boundary_points - [in]
      Boundary points.
    bCloseBoundary - [in]
      If true, an edge segment is added from the last boundary point to the first boundary point.
  Returns:
    Number of boundary edge segments added.
  Remarks:
    The calculation tolerates zero length edge segments. The caller is responsible for insuring the
    coordinates in boundary_points[] are valid doubles.
  */
  ON__UINT32 AddBoundary(size_t point_count, const ON_3fPoint* boundary_points, bool bCloseBoundary);

  /*
  Returns:
    The winding number of the boundary about the winding point.
  */
  ON__INT32 WindingNumber() const;

  /*
  Returns:
    The winding point.
  */
  const ON_2dPoint WindingPoint() const;

  /*
  Returns:
    Number of segments in the boundary.
  */
  ON__UINT32 BoundarySegmentCount() const;

  /*
  Returns:
    The end of the previous call to AddBoundary()
  */
  const ON_2dPoint PreviousBoundaryPoint() const;

private:
  // Location of the winding point.
  ON_2dPoint m_winding_point = ON_2dPoint::NanPoint;

  // Location of the last boundary point added. This is used 
  // by AddBoundary(ON_2dPoint p) to generate a segment
  // from m_prev_boundary_point to p in situations where
  // points are streamed so the caller doesn't have to
  // deal with accumulating the previous point and can
  // mix streamed points with other forms of boundary input.
  ON_2dPoint m_prev_boundary_point = ON_2dPoint::NanPoint;

  // Number of boundary segments in the polyline
  ON__UINT32 m_boundary_segment_count = 0;

  // In the comments below, H is the horizontal line through the winding point
  // and V is the vertical line through the winding point.

  // signed net number of times polyline crosses H to the left of the winding point.
  // A below to above crossing is -1.
  ON__INT32 m_left_crossing_number = 0;

  // signed net number of times polyline crosses H to the right of the winding point.
  // A below to above crossing is +1.
  ON__INT32 m_right_crossing_number = 0;

  // signed net number of times polyline crosses V to the below of the winding point.
  // A left to right crossing is +1.
  ON__INT32 m_below_crossing_number = 0;

  // signed net number of times polyline crosses V to the above of the winding point.
  // A left to right crossing is -1.
  ON__INT32 m_above_crossing_number = 0;

  // 0 != (m_status_bits & 1): left crossing occurred
  // 0 != (m_status_bits & 2): right crossing occurred
  // 0 != (m_status_bits & 4): below crossing occurred
  // 0 != (m_status_bits & 8): above crossing occurred
  // 0 != (m_status_bits & 16): winding point on horizontal segment
  // 0 != (m_status_bits & 32): winding point on vertical segment
  ON__INT32 m_status_bits = 0;

  void Internal_AddBoundarySegment(const double* p, const double* q);

  // Input: p and q are 2d points with p.y <= 0 and q.y > 0
  //
  // Returns:
  //   Sign of the x coordinate of the intersection of the line segment from p to q 
  //   and the x axis.
  static int Internal_SignOfX(const ON_2dPoint& p, const ON_2dPoint& q);

  // Input: p and q are 2d points with p.x <= 0 and q.x > 0
  //
  // Returns:
  //   Sign of the y coordinate of the intersection of the line segment from p to q 
  //   and the y axis.
  static int Internal_SignOfY(const ON_2dPoint& p, const ON_2dPoint& q);

  bool Internal_HaveWindingPoint() const;
};


/*
ON_PeriodicDomain is a helper class for dealing with closed or periodic surfaces using the idea of a covering space.

If a surface is closed in the u-direction (or v respectively),  a curve on the surface that crosses the seam
will not have a continuous pull back to parameter space.  However, if we extend the surface domain
in the u-coordinates and allow the surface to cover itself periodicly, i.e S(u,v) = S(u + T, v) with period T,  then  we
can pull back the curve to the domain covering space (-inf,inf) x dom[1].

*/
class ON_CLASS ON_PeriodicDomain
{
public:
	ON_PeriodicDomain() = default;
	ON_PeriodicDomain(const ON_Interval dom[2], const bool closed[2], double normband = 1.0 / 3.0);
	void Initialize(const ON_Interval dom[2], const bool closed[2], double normband = 1.0 / 3.0);
	/*
	Construction or Initialization
	Parameters:
		dom -[in] surface domain
		closed -[in] closed[0] is true if the surface is closed in u direction (similarly for 1 and v)
						Use  ON_IsG1Closed(...) to test for G1-closed surfaces.
		normband - [in] 0<normband<.5 is a normalized coordinate defining a band on each side of the seam.
						The bands are {(u,v): dom[0].NormalizedParameterAt(u)< normband } and
													{(u,v): dom[0].NormalizedParameterAt(u)> 1.0 - normband }
	The point sequence crosses the seam if consecutive points are in opposite bands along the seam.
	*/

	// Repeatedly call LiftToCover( Pin) with Pin in the domain covering space.  The resulting 
	// output sequence will be lifted to the domain covering space, and will be 'continuous' in that 
	// consecutive points will be in the same or an adjacent band.
	// Use stealth=true to lift this point without affecting the state,  this allows one to compute a trial end 
	// of sequence.  
	// see also ON_LiftToCover(...).
	ON_2dPoint LiftToCover(ON_2dPoint Pin, bool stealth = false);

	// The projection from covering space back to domain.  LiftInverse(LiftToCover(p))==p
	ON_2dPoint LiftInverse(ON_2dPoint p);

	ON_Interval m_dom[2];
  bool m_closed[2] = {};
	double m_normband = ON_DBL_QNAN;
private:
  int m_deck[2] = {};
	ON_2dPoint m_nprev = ON_2dPoint::UnsetPoint;
};


/*
Lift a sequence of surface points to the covering space.

If a surface is closed in the u-direction (or v respectively),  a curve on the surface that crosses the seam
will not have a continuous pull back to parameter space.  However, if we extend the surface domain
in the u-coordinates and allow the surface to cover itself periodiclly  then  we
we can pull back the curve to the covering space (-inf,inf) x dom[1].
Parameters
in - [in] surface parameter points in dom[0] x dom[1]
dom -[in] surface domain
closed -[in] closed[0] is true if the surface is closed in u direction (similarly for 1 and v)
normband - [in] 0<normband<.5 is a normalized coordinate defining a band on each side of the seam.
The point sequence crosses the seam if consecutive points are in opposite bands
along the seam.
Returns
A sequence out with out[0] = in[0] and out.Count()==in.Count()
*/
ON_DECL
ON_SimpleArray<ON_2dPoint> ON_LiftToCover(
	const ON_SimpleArray<ON_2dPoint>& in,
	const ON_Interval dom[2], bool closed[2],
	double normband = 1.0 / 3.0);

/*
LiftInverse is the projection map that inverts ON_LiftToCover 
Parameters
	P -[in]  A point in the domain covering space.
Returns a point in dom.  
*/
ON_2dPoint ON_DECL ON_LiftInverse(ON_2dPoint P, ON_Interval dom[2], bool closed[2]);

#endif

