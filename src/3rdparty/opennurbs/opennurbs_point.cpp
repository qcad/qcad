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

#include "opennurbs.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

bool ON_IsValid(double x)
{
  return ON_IS_VALID(x);
}

bool ON_IsValidPositiveNumber(double x)
{
  return (x > 0.0 && x < ON_UNSET_POSITIVE_VALUE);
}

bool ON_IsValidNegativeNumber(double x)
{
  return (x > ON_UNSET_VALUE && x < 0.0);
}

int ON_CompareDouble(
  double a,
  double b
  )
{
  if (a < b)
    return -1;
  if (a > b)
    return 1;
  if (a == b)
    return 0;

  // below this point, a and/or b is a nan


  if (a == a)
    return -1; // b is a nan
  
  if (b == b)
    return 1; // ab is a nan

  return 0; // both a and b are nans
}


int ON_CompareFloat(
  float a,
  float b
  )
{
  if (a < b)
    return -1;
  if (a > b)
    return 1;
  if (a == b)
    return 0;

  // below this point, a and/or b is a nan


  if (a == a)
    return -1; // b is a nan
  
  if (b == b)
    return 1; // ab is a nan

  return 0; // both a and b are nans
}

static int Internal_DoubleArrayCompare(
  size_t count,
  const double* a,
  const double* b
  )
{
  const double* e = a + count;
  int rc = ON_CompareDouble(*a++, *b++);
  while( 0 == rc && a < e)
    rc = ON_CompareDouble(*a++, *b++);
  return rc;
}

static int Internal_FloatArrayCompare(
  size_t count,
  const float* a,
  const float* b
  )
{
  const float* e = a + count;
  int rc = ON_CompareFloat(*a++, *b++);
  while( 0 == rc && a < e)
    rc = ON_CompareFloat(*a++, *b++);
  return rc;
}

int ON_CompareDoubleArray(
  size_t count,
  const double* a,
  const double* b
  )
{
  if (count <= 0)
    return 0;
  if (a == b)
    return 0;
  if (nullptr == a)
    return 1;
  if (nullptr == b)
    return -1;
  return Internal_DoubleArrayCompare(count, a, b);
}

static bool Internal_IsUnsetFloat(
  size_t count,
  const float* a
)
{
  const float * e = a + count;
  while (a < e)
  {
    float x = *a++;
    if (ON_UNSET_FLOAT == x || ON_UNSET_POSITIVE_FLOAT == x)
      return true;
  }
  return false;
}

bool ON_2fPoint::IsUnset() const
{
  return Internal_IsUnsetFloat(2, &x);
}

bool ON_3fPoint::IsUnset() const
{
  return Internal_IsUnsetFloat(3, &x);
}

bool ON_4fPoint::IsUnset() const
{
  return Internal_IsUnsetFloat(4, &x);
}

bool ON_2fVector::IsUnset() const
{
  return Internal_IsUnsetFloat(2, &x);
}

bool ON_3fVector::IsUnset() const
{
  return Internal_IsUnsetFloat(3, &x);
}

static bool Internal_IsUnsetDouble(
  size_t count,
  const double* a
)
{
  const double * e = a + count;
  while (a < e)
  {
    double x = *a++;
    if (ON_UNSET_VALUE == x || ON_UNSET_POSITIVE_VALUE == x)
      return true;
  }
  return false;
}

static bool Internal_IsNanDouble(
  size_t count,
  const double* a
)
{
  const double * e = a + count;
  while (a < e)
  {
    double x = *a++;
    if (x == x)
      continue;
    return true;
  }
  return false;
}

bool ON_2dPoint::IsUnset() const
{
  return Internal_IsUnsetDouble(2, &x);
}

bool ON_2dPoint::IsNan() const
{
  return Internal_IsNanDouble(2, &x);
}

bool ON_2dPoint::IsUnsetOrNan() const
{
  return Internal_IsUnsetDouble(2, &x) || Internal_IsNanDouble(2, &x);
}

bool ON_3dPoint::IsUnset() const
{
  return Internal_IsUnsetDouble(3, &x);
}

bool ON_3dPoint::IsNan() const
{
  return Internal_IsNanDouble(3, &x);
}

bool ON_3dPoint::IsUnsetOrNan() const
{
  return Internal_IsUnsetDouble(3, &x) || Internal_IsNanDouble(3, &x);
}

bool ON_4dPoint::IsUnset() const
{
  return Internal_IsUnsetDouble(4, &x);
}

bool ON_4dPoint::IsNan() const
{
  return Internal_IsNanDouble(4, &x);
}

bool ON_4dPoint::IsUnsetOrNan() const
{
  return Internal_IsUnsetDouble(4, &x) || Internal_IsNanDouble(4, &x);
}

bool ON_2dVector::IsUnset() const
{
  return Internal_IsUnsetDouble(2, &x);
}

bool ON_2dVector::IsNan() const
{
  return Internal_IsNanDouble(2, &x);
}

bool ON_2dVector::IsUnsetOrNan() const
{
  return Internal_IsUnsetDouble(2, &x) || Internal_IsNanDouble(2, &x);
}

bool ON_3dVector::IsUnset() const
{
  return Internal_IsUnsetDouble(3, &x);
}

bool ON_3dVector::IsNan() const
{
  return Internal_IsNanDouble(3, &x);
}

bool ON_3dVector::IsUnsetOrNan() const
{
  return Internal_IsUnsetDouble(3, &x) || Internal_IsNanDouble(3, &x);
}

int ON_2dVector::Compare(
  const ON_2dVector& lhs,
  const ON_2dVector& rhs
  )
{
  return Internal_DoubleArrayCompare(2, &lhs.x, &rhs.x);
}

int ON_3dVector::Compare(
  const ON_3dVector& lhs,
  const ON_3dVector& rhs
  )
{
  return Internal_DoubleArrayCompare(3, &lhs.x, &rhs.x);
}

int ON_2dPoint::Compare(
  const ON_2dPoint& lhs,
  const ON_2dPoint& rhs
  )
{
  return Internal_DoubleArrayCompare(2, &lhs.x, &rhs.x);
}

int ON_3dPoint::Compare(
  const ON_3dPoint& lhs,
  const ON_3dPoint& rhs
  )
{
  return Internal_DoubleArrayCompare(3, &lhs.x, &rhs.x);
}

const ON_2dPoint ON_2dPoint::Midpoint(const ON_2dPoint& A, const ON_2dPoint& B)
{
  // avoids overflow and exact when coordinates are equal
  return ON_2dPoint(
    A.x == B.x ? A.x : (0.5 * A.x + 0.5 * B.x),
    A.y == B.y ? A.y : (0.5 * A.y + 0.5 * B.y)
    );
}

const ON_3dPoint ON_3dPoint::Midpoint(const ON_3dPoint& A, const ON_3dPoint& B)
{
  // avoids overflow and exact when coordinates are equal
  return ON_3dPoint(
    A.x == B.x ? A.x : (0.5 * A.x + 0.5 * B.x),
    A.y == B.y ? A.y : (0.5 * A.y + 0.5 * B.y),
    A.z == B.z ? A.z : (0.5 * A.z + 0.5 * B.z)
    );
}


const ON_2fPoint ON_2fPoint::Midpoint(const ON_2fPoint& A, const ON_2fPoint& B)
{
  // avoids overflow and exact when coordinates are equal
  return ON_2fPoint(
    A.x == B.x ? A.x : (0.5f * A.x + 0.5f * B.x),
    A.y == B.y ? A.y : (0.5f * A.y + 0.5f * B.y)
  );
}

const ON_3fPoint ON_3fPoint::Midpoint(const ON_3fPoint& A, const ON_3fPoint& B)
{
  // avoids overflow and exact when coordinates are equal
  return ON_3fPoint(
    A.x == B.x ? A.x : (0.5f * A.x + 0.5f * B.x),
    A.y == B.y ? A.y : (0.5f * A.y + 0.5f * B.y),
    A.z == B.z ? A.z : (0.5f * A.z + 0.5f * B.z)
  );
}

int ON_4dPoint::ProjectiveCompare(
  const ON_4dPoint& lhs,
  const ON_4dPoint& rhs
  )
{
  if (lhs.w == rhs.w)
  {
    // neither lhs.w nor rhs.w is a nan
    return Internal_DoubleArrayCompare(3, &lhs.x, &rhs.x);
  }

  if (0.0 != lhs.w && 0.0 != rhs.w)
  {
    // neither lhs.w nor rhs.w is a nan
    return ON_3dPoint::Compare(ON_3dPoint(lhs), ON_3dPoint(rhs));
  }

  if (0.0 != lhs.w && 0.0 == rhs.w)
  {
    // neither lhs.w nor rhs.w is a nan
    return -1;
  }

  if (0.0 == lhs.w && 0.0 != rhs.w)
  {
    // neither lhs.w nor rhs.w is a nan
    return 1;
  }

  if (lhs.w == lhs.w)
  {
    // rhs.w is a nan
    return -1; 
  }

  if (rhs.w == rhs.w)
  {
    // lhs.w is a nan
    return 1; 
  }

  // lhs.w and rhs.w are both nans
  return Internal_DoubleArrayCompare(3, &lhs.x, &rhs.x);
}

int ON_4dPoint::DictionaryCompare(
  const ON_4dPoint& lhs,
  const ON_4dPoint& rhs
  )
{
  return Internal_DoubleArrayCompare(4, &lhs.x, &rhs.x);
}

static double Internal_4dEuclideanCoordinate(double x, double w)
{
  return
    ((ON_IS_UNSET_DOUBLE(x) || ON_IS_UNSET_DOUBLE(w)) && x==x && w==w)
    ? ON_UNSET_VALUE
    : (x / w);
}

double ON_4dPoint::EuclideanX() const
{
  return Internal_4dEuclideanCoordinate(x,w);
}

double ON_4dPoint::EuclideanY() const
{
  return Internal_4dEuclideanCoordinate(y,w);
}

double ON_4dPoint::EuclideanZ() const
{
  return Internal_4dEuclideanCoordinate(z,w);
}

static float Internal_4fEuclideanCoordinate(float x, float w)
{
  return
    ((ON_IS_UNSET_FLOAT(x) || ON_IS_UNSET_FLOAT(w)) && x == x && w==w)
    ? ON_UNSET_FLOAT
    : (x / w);
}


float ON_4fPoint::EuclideanX() const
{
  return Internal_4fEuclideanCoordinate(x,w);
}

float ON_4fPoint::EuclideanY() const
{
  return Internal_4fEuclideanCoordinate(y,w);
}

float ON_4fPoint::EuclideanZ() const
{
  return Internal_4fEuclideanCoordinate(z,w);
}

int ON_2fVector::Compare(
  const ON_2fVector& lhs,
  const ON_2fVector& rhs
  )
{
  return Internal_FloatArrayCompare(2, &lhs.x, &rhs.x);
}

int ON_3fVector::Compare(
  const ON_3fVector& lhs,
  const ON_3fVector& rhs
  )
{
  return Internal_FloatArrayCompare(3, &lhs.x, &rhs.x);
}

int ON_2fPoint::Compare(
  const ON_2fPoint& lhs,
  const ON_2fPoint& rhs
  )
{
  return Internal_FloatArrayCompare(2, &lhs.x, &rhs.x);
}

int ON_3fPoint::Compare(
  const ON_3fPoint& lhs,
  const ON_3fPoint& rhs
  )
{
  return Internal_FloatArrayCompare(3, &lhs.x, &rhs.x);
}

int ON_4fPoint::DictionaryCompare(
  const ON_4fPoint& lhs,
  const ON_4fPoint& rhs
  )
{
  return Internal_FloatArrayCompare(4, &lhs.x, &rhs.x);
}

int ON_4fPoint::ProjectiveCompare(
  const ON_4fPoint& lhs,
  const ON_4fPoint& rhs
  )
{
  return ON_4dPoint::ProjectiveCompare(ON_4dPoint(lhs), ON_4dPoint(rhs));
}

bool ON_IsValidFloat(float x)
{
  return ON_IS_VALID_FLOAT(x);
}


ON_Interval::ON_Interval()
{
  m_t[0] = m_t[1] = ON_UNSET_VALUE; 
}

ON_Interval::ON_Interval(double t0, double t1)
{
  Set(t0,t1);
}

bool ON_Interval::operator!=(const ON_Interval& rhs) const
{
  // Intentionally returns false if any double is a nan.
  if (m_t[0] != rhs.m_t[0])
  {
    return (m_t[1] == m_t[1] && rhs.m_t[1] == rhs.m_t[1]);
  }

  return (m_t[0] == m_t[0] && m_t[1] != rhs.m_t[1]);
}

bool ON_Interval::operator==(const ON_Interval& rhs) const
{
  // Intentionally returns false if any double is a nan.
  return (m_t[0] == rhs.m_t[0] && m_t[1] == rhs.m_t[1]);
}


double&
ON_Interval::operator[](int i)
{
  return m_t[(i<=0)?0:1];
}

double
ON_Interval::operator[](int i) const
{
  return m_t[(i<=0)?0:1];
}

double&
ON_Interval::operator[](unsigned int i)
{
  return m_t[(i<=0)?0:1];
}

double
ON_Interval::operator[](unsigned int i) const
{
  return m_t[(i<=0)?0:1];
}

double
ON_Interval::Min() const
{
  if (m_t[0] <= m_t[1])
    return m_t[0];
  if (m_t[1] <= m_t[0])
    return m_t[1];
  return ON_DBL_QNAN;
}

const ON_Interval ON_Interval::Singleton(double t)
{
  return ON_Interval(t, t);
}


void ON_Interval::Destroy()
{
  *this = ON_Interval::EmptyInterval;
}

void ON_Interval::Set(double t0,double t1)
{
  m_t[0] = t0;
  m_t[1] = t1;
}

double ON_Interval::ParameterAt(double x) const
{
  if (m_t[0] == m_t[1])
    x = 0.0;
  return (ON_IS_VALID(x) ? ((1.0-x)*m_t[0] + x*m_t[1]) : ON_UNSET_VALUE);
}

double ON_Interval::ClampedParameterAt(
  double x
) const
{
  if (ON_IS_VALID(x) && ON_IS_VALID(m_t[0]) && ON_IS_VALID(m_t[1]))
  {

    if (x <= 0.0)
      return m_t[0];
    if (x >= 1.0)
      return m_t[1];
    if (m_t[0] == m_t[1])
      return m_t[0]; // no fuzz from a linear combination
    return ((1.0 - x) * m_t[0] + x * m_t[1]);
  }

  return ON_DBL_QNAN;
}

double ON_Interval::ClampedNormalizedParameterAt(
  double interval_parameter
) const
{
  if (ON_IS_VALID(interval_parameter) && ON_IS_VALID(m_t[0]) && ON_IS_VALID(m_t[1]))
  {
    if (m_t[0] < m_t[1])
    {
      // this is an increasing interval
      if (interval_parameter <= m_t[0])
        return 0.0;
      if (interval_parameter >= m_t[1])
        return 1.0;
    }
    else if (m_t[0] > m_t[1])
    {
      // this is a decreasing interval
      if (interval_parameter >= m_t[0])
        return 0.0;
      if (interval_parameter <= m_t[1])
        return 1.0;
    }
    else
    {
      // this is a singleton interval
      if (interval_parameter < m_t[0])
        return 0.0;
      if (interval_parameter > m_t[1])
        return 1.0;
      return 0.5;
    }

    // the interval_parameter is strictly between m_t[0] and m_t[1]
    return (interval_parameter - m_t[0]) / (m_t[1] - m_t[0]);
  }

  return ON_DBL_QNAN;
}

ON_Interval ON_Interval::ParameterAt(ON_Interval x) const
{
  return ON_Interval( ParameterAt(x[0]), ParameterAt(x[1]) );
}

double ON_Interval::NormalizedParameterAt( // returns x so that min*(1.0-x) + max*x = input
  double t
  ) const
{
  if (!ON_IS_VALID(t))
    return ON_UNSET_VALUE; // added 29 Sep 2006

  double x = 0.0;
  if ( m_t[0] != m_t[1] ) {
    x = ( t == m_t[1]) ? 1.0 : (t - m_t[0])/(m_t[1] - m_t[0]);
  }
  return x;
}

ON_Interval ON_Interval::NormalizedParameterAt( // returns x so that min*(1.0-x) + max*x = input
  ON_Interval t
  ) const
{
	return  ON_Interval(	NormalizedParameterAt(t[0]) , 
												NormalizedParameterAt(t[1]) );
}

double ON_Interval::TransformParameterTo(const ON_Interval& target, double t) const
{
  // 31-JAN-2025 MDvR:
  // This function was created to fix https://mcneel.myjetbrains.com/youtrack/issue/RH-85831
  // The bug was a result conversions of ON_PolyCurve parameters at PolyCurve segment ends
  // to/from Nurbs form curve parameters.
  if (!IsValid() || !target.IsValid())
  {
    return ON_DBL_QNAN;
  }

  if (*this == target)
  {
    return t;
  }

  double s = NormalizedParameterAt(t);
  double L1 = std::max<double>(std::abs(target.m_t[0]), std::abs(target.m_t[1]));
  double L2 = std::max<double>(std::abs(m_t[0]), std::abs(m_t[1]));
  double L  = std::max<double>(L1, L2);
  if (abs(s / L) < ON_EPSILON)
  {
    s = 0.0;
  }
  else if (abs((s - 1.0) / L) < ON_EPSILON)
  {
    s = 1.0;
  }
  return target.ParameterAt(s);
}

double
ON_Interval::Max() const
{
  if (m_t[0] >= m_t[1])
    return m_t[0];
  if (m_t[1] >= m_t[0])
    return m_t[1];
  return ON_DBL_QNAN;
}

double
ON_Interval::Mid() const
{
  return 0.5*(m_t[0]+m_t[1]);
}

double
ON_Interval::Length() const
{
  return ( ON_IS_VALID(m_t[0]) && ON_IS_VALID(m_t[1]) ) ? m_t[1]-m_t[0] : 0.0;
}

bool
ON_Interval::IsIncreasing() const
{
  return ( ON_UNSET_VALUE < m_t[0] && m_t[0] < m_t[1] && m_t[1] < ON_UNSET_POSITIVE_VALUE ) ? true : false;
}

bool
ON_Interval::IsDecreasing() const
{
  return (ON_UNSET_POSITIVE_VALUE > m_t[0] && m_t[0] > m_t[1] && m_t[1] > ON_UNSET_VALUE) ? true : false;
}

bool
ON_Interval::IsInterval() const
{
  return ( IsIncreasing() || IsDecreasing() ) ? true : false;
}


bool
ON_Interval::IsSingleton() const
{
  return (ON_UNSET_VALUE < m_t[0] && m_t[0] == m_t[1] && m_t[1] < ON_UNSET_POSITIVE_VALUE) ? true : false;
}

bool
ON_Interval::IsEmptyInterval() const
{
  return ( m_t[0] == ON_UNSET_VALUE && m_t[1] == ON_UNSET_VALUE ) ? true : false;
}

bool
ON_Interval::IsEmptySet() const
{
  return ( m_t[0] == ON_UNSET_VALUE && m_t[1] == ON_UNSET_VALUE ) ? true : false;
}

bool
ON_Interval::IsValid() const
{
  return (ON_UNSET_VALUE < m_t[0] && m_t[0] < ON_UNSET_POSITIVE_VALUE && ON_UNSET_VALUE < m_t[1] && m_t[1] < ON_UNSET_POSITIVE_VALUE);
}

bool 
ON_Interval::MakeIncreasing()		// returns true if resulting interval IsIncreasing() 
{
	if( IsDecreasing()){ 
		Swap();
		return true;
	}
	return IsIncreasing();
}

int ON_Interval::Compare(const ON_Interval& lhs, const ON_Interval& rhs)
{
  return Internal_DoubleArrayCompare(2, lhs.m_t, rhs.m_t);
}

bool
ON_Interval::Includes( double t, bool bTestOpenInterval) const
{
  bool rc = false;
  if ( ON_IS_VALID(t) && ON_IS_VALID(m_t[0]) && ON_IS_VALID(m_t[1]) )
  {
    int i = (m_t[0] <= m_t[1]) ? 0 : 1;
    if ( bTestOpenInterval )
    {
      rc = ( m_t[i] < t && t < m_t[1-i] ) ? true : false;
    }
    else
    {
      rc = ( m_t[i] <= t && t <= m_t[1-i] ) ? true : false;
    }
  }
  return rc;
}

bool
ON_Interval::Includes( const ON_Interval& other, bool bProperSubSet ) const
{
  bool rc = ( Includes( other.m_t[0] ) && Includes( other.m_t[1] ) ) ? true : false;
  if ( rc && bProperSubSet )
  {
    if ( !Includes( other.m_t[0], true ) && !Includes( other.m_t[1], true ) )
      rc = false;
  }
  return rc;
}

int 
ON_Interval::Clamp(double& v) const
{
  int rval = 0;
  if (v < m_t[0]) {
    v = m_t[0];
    rval = -1;
  }
  else if (v > m_t[1]) {
    v = m_t[1];
    rval = 1;
  }
  return rval;
}

bool
ON_Interval::IntervalsOverlap(const ON_Interval& A, const ON_Interval& B)

{
  ON_Interval C;
  C.Intersection(A, B);
  return C.IsEmptyInterval() ? false : true;
}

void
ON_Interval::Reverse()
{
  if ( !IsEmptyInterval() ) {
    const double x = -m_t[0];
    m_t[0] = -m_t[1];
    m_t[1] = x;
  }
}

void
ON_Interval::Swap()
{
  const double x = m_t[0];
  m_t[0] = m_t[1];
  m_t[1] = x;
}

//////////
// If the intersection is not empty, then 
// intersection = [max(this.Min(),arg.Min()), min(this.Max(),arg.Max())]
// Intersection() returns true if the intersection is not empty.
// The interval [ON_UNSET_VALUE,ON_UNSET_VALUE] is considered to be
// the empty set interval.  The result of any intersection involving an
// empty set interval or disjoint intervals is the empty set interval.
bool ON_Interval::Intersection( // this = this intersect arg
       const ON_Interval& other
       )
{
  bool rc = false;
  if (IsEmptyInterval() && other.IsEmptyInterval())
  {
    *this = ON_Interval::EmptyInterval;
  }
  else 
  {
    double a, b, mn, mx;
    a = Min();
    b = other.Min();
    mn = (a>=b) ? a : b;
    a = Max();
    b = other.Max();
    mx = (a<=b) ? a : b;
    if ( mn <= mx )
    {
      Set(mn,mx);
      rc = true;
    }
    else
    {
      *this = ON_Interval::EmptyInterval;
    }
  }
  return rc;
}

//////////
// If the intersection is not empty, then 
// intersection = [max(argA.Min(),argB.Min()), min(argA.Max(),argB.Max())]
// Intersection() returns true if the intersection is not empty.
// The interval [ON_UNSET_VALUE,ON_UNSET_VALUE] is considered to be
// the empty set interval.  The result of any intersection involving an
// empty set interval or disjoint intervals is the empty set interval.
bool ON_Interval::Intersection( // this = intersection of two args
       const ON_Interval& ain, 
       const ON_Interval& bin
       )
{
  bool rc = false;
  if ( ain.IsEmptyInterval() && bin.IsEmptyInterval() )
  {
    *this = ON_Interval::EmptyInterval;
  }
  else
  {
    double a, b, mn, mx;
    a = ain.Min();
    b = bin.Min();
    mn = (a >= b) ? a : b;
    a = ain.Max();
    b = bin.Max();
    mx = (a <= b) ? a : b;
    if (mn <= mx) 
    {
      Set(mn, mx);
      rc = true;
    }
    else
    {
      *this = ON_Interval::EmptyInterval;
    }
  }
  return rc;
}

//////////
  // The union of an empty set and an increasing interval is the increasing
  // interval.  The union of two empty sets is empty. The union of an empty
  // set an a non-empty interval is the non-empty interval.
  // The union of two non-empty intervals is
// union = [min(this.Min(),arg.Min()), max(this.Max(),arg.Max()),]
// Union() returns true if the union is not empty.
bool ON_Interval::Union( // this = this union arg
       const ON_Interval& other
       )
{
  bool rc = false;
  if ( other.IsEmptyInterval() )
  {
    // this may be increasing, decreasing, or empty
    Set( Min(), Max() );
    rc = !IsEmptyInterval();
  }
  else if ( IsEmptyInterval() ) 
  {
    // other may be increasing or decreasing
    Set( other.Min(), other.Max() );
    rc = true;
  }
  else {
    double a, b, mn, mx;
    a = Min();
    b = other.Min();
    mn = (a<=b) ? a : b;
    a = Max();
    b = other.Max();
    mx = (a>=b) ? a : b;
    if ( mn <= mx ) {
      Set(mn,mx);
      rc = true;
    }
    else
    {
      *this = ON_Interval::EmptyInterval;
    }
  }
  return rc;
}

bool ON_Interval::Union(
  int count,
  const double* t
  )
{
  bool rc = false;
  double a, mn, mx;

  if ( 0 != t )
  {
    while ( count > 0 && !ON_IsValid(*t) )
    {
      count--;
      t++;
    }
  }

  if ( count <= 0 || 0 == t )
  {
    // this may be increasing, decreasing, or empty
    if ( !IsEmptyInterval() )
    {
      mn = Min();
      mx = Max();
      if ( mn <= mx && ON_IsValid(mn) && ON_IsValid(mx) )
      {
        Set( mn, mx );
        rc = true;
      }
    }
  }
  else 
  {
    if ( IsEmptyInterval() ) 
    {
      a = *t++;
      Set( a, a );
      count--;
      rc = true;
    }
    mn = Min();
    mx = Max();
    while( count > 0 )
    {
      count--;
      a = *t++;
      if ( ON_IsValid(a) )
      {
        if ( a < mn )
          mn = a;
        else if ( a > mx )
          mx = a;
      }
    }
    if ( mn <= mx && ON_IsValid(mn) && ON_IsValid(mx) )
    {
      Set(mn,mx);
      rc = true;
    }
    else
    {
      *this = ON_Interval::EmptyInterval;
    }
  }
  return rc;
}

bool ON_Interval::Union(
       double t
       )
{
  return Union(1,&t);
}

//////////
  // The union of an empty set and an increasing interval is the increasing
  // interval.  The union of two empty sets is empty. The union of an empty
  // set an a non-empty interval is the non-empty interval.
  // The union of two non-empty intervals is
// union = [min(argA.Min(),argB.Min()), max(argA.Max(),argB.Max()),]
// Union() returns true if the union is not empty.
bool ON_Interval::Union( // this = union of two args
       const ON_Interval& ain, 
       const ON_Interval& bin
       )
{
  bool rc = false;
  if ( bin.IsEmptyInterval() )
  {
    // ain may be increasing, decreasing, or empty
    Set( ain.Min(), ain.Max() );
    rc = !IsEmptyInterval();
  }
  else if ( ain.IsEmptyInterval() )
  {
    // bin may be increasing or decreasing
    Set( bin.Min(), bin.Max() );
    rc = true;
  }
  else {
    double a, b, mn, mx;
    a = ain.Min();
    b = bin.Min();
    mn = (a<=b) ? a : b;
    a = ain.Max();
    b = bin.Max();
    mx = (a>=b) ? a : b;
    if ( mn <= mx ) {
      Set(mn,mx);
      rc = true;
    }
    else
    {
      *this = ON_Interval::EmptyInterval;
    }
  }
  return rc;
}


bool ON_Interval::Expand(double delta)
{
  m_t[0] -= delta;
  m_t[1] += delta;
  return IsIncreasing();
}

bool ON_3dVector::Decompose( // Computes a, b, c such that this vector = a*X + b*Y + c*Z
       //
       // If X,Y,Z is known to be an orthonormal frame,
       // then a = V*X, b = V*Y, c = V*Z will compute
       // the same result more quickly.
       const ON_3dVector& X,
       const ON_3dVector& Y,
       const ON_3dVector& Z,
       double* a,
       double* b,
       double* c
       ) const
{
  int rank;
  double pivot_ratio = 0.0;
  double row0[3], row1[3], row2[3];
  row0[0] = X*X;   row0[1] = X*Y;   row0[2] = X*Z;
  row1[0] = row0[1]; row1[1] = Y*Y;   row1[2] = Y*Z;
  row2[0] = row0[2]; row2[1] = row1[2]; row2[2] = Z*Z;
  rank = ON_Solve3x3( row0, row1, row2, 
                    (*this)*X, (*this)*Y, (*this)*Z,
                    a, b, c, &pivot_ratio );
  return (rank == 3) ? true : false;
}

int ON_3dVector::IsParallelTo( 
      // returns  1: this and other vectors are and parallel
      //         -1: this and other vectors are anti-parallel
      //          0: this and other vectors are not parallel
      //             or at least one of the vectors is zero
      const ON_3dVector& v,
      double angle_tolerance // (default=ON_DEFAULT_ANGLE_TOLERANCE) radians
      ) const
{
  int rc = 0;
  const double ll = Length()*v.Length();
  if ( ll > 0.0 ) {
    const double cos_angle = (x*v.x + y*v.y + z*v.z)/ll;
    const double cos_tol = cos(angle_tolerance);
    if ( cos_angle >= cos_tol )
      rc = 1;
    else if ( cos_angle <= -cos_tol )
      rc = -1;
  }
  return rc;
}

bool ON_3fVector::IsPerpendicularTo(
      // returns true:  this and other vectors are perpendicular
      //         false: this and other vectors are not perpendicular
      //                or at least one of the vectors is zero
      const ON_3fVector& v,
      double angle_tolerance // (default=ON_DEFAULT_ANGLE_TOLERANCE) radians
      ) const
{
  ON_3dVector V(*this);
  return V.IsPerpendicularTo(ON_3dVector(v),angle_tolerance);
}

bool ON_3dVector::IsPerpendicularTo(
      // returns true:  this and other vectors are perpendicular
      //         false: this and other vectors are not perpendicular
      //                or at least one of the vectors is zero
      const ON_3dVector& v,
      double angle_tolerance // (default=ON_DEFAULT_ANGLE_TOLERANCE) radians
      ) const
{
  bool rc = false;
  const double ll = Length()*v.Length();
  if ( ll > 0.0 ) {
    if ( fabs((x*v.x + y*v.y + z*v.z)/ll) <= sin(angle_tolerance) )
      rc = true;
  }
  return rc;
}

bool ON_3fVector::PerpendicularTo( const ON_3fVector& v )
{
  ON_3dVector V(*this);
  return V.IsPerpendicularTo(ON_3dVector(v));
}

const ON_3dVector ON_3dVector::Perpendicular(
  ON_3dVector failure_result
) const
{
  ON_3dVector perpendicular;
  return perpendicular.PerpendicularTo(*this) ? perpendicular : failure_result;
}

bool ON_3dVector::PerpendicularTo( const ON_3dVector& v )
{
  //bool rc = false;
  int i, j, k; 
  double a, b;
  k = 2;
  if ( fabs(v.y) > fabs(v.x) ) {
    if ( fabs(v.z) > fabs(v.y) ) {
      // |v.z| > |v.y| > |v.x|
      i = 2;
      j = 1;
      k = 0;
      a = v.z;
      b = -v.y;
    }
    else if ( fabs(v.z) >= fabs(v.x) ){
      // |v.y| >= |v.z| >= |v.x|
      i = 1;
      j = 2;
      k = 0;
      a = v.y;
      b = -v.z;
    }
    else {
      // |v.y| > |v.x| > |v.z|
      i = 1;
      j = 0;
      k = 2;
      a = v.y;
      b = -v.x;
    }
  }
  else if ( fabs(v.z) > fabs(v.x) ) {
    // |v.z| > |v.x| >= |v.y|
    i = 2;
    j = 0;
    k = 1;
    a = v.z;
    b = -v.x;
  }
  else if ( fabs(v.z) > fabs(v.y) ) {
    // |v.x| >= |v.z| > |v.y|
    i = 0;
    j = 2;
    k = 1;
    a = v.x;
    b = -v.z;
  }
  else {
    // |v.x| >= |v.y| >= |v.z|
    i = 0;
    j = 1;
    k = 2;
    a = v.x;
    b = -v.y;
  }
  double* this_v = &x;
  this_v[i] = b;
  this_v[j] = a;
  this_v[k] = 0.0;
  return (a != 0.0) ? true : false;
}

bool
ON_3dVector::PerpendicularTo( 
      const ON_3dPoint& P0, const ON_3dPoint& P1, const ON_3dPoint& P2
      )
{
  // Find a the unit normal to a triangle defined by 3 points
  *this = ON_3dVector::ZeroVector;

  ON_3dVector V0 = P2 - P1;
  ON_3dVector V1 = P0 - P2;
  ON_3dVector V2 = P1 - P0;

  ON_3dVector N0 = ON_CrossProduct( V1, V2 );
  if ( !N0.Unitize() )
    return false;
  ON_3dVector N1 = ON_CrossProduct( V2, V0 );
  if ( !N1.Unitize() )
    return false;
  ON_3dVector N2 = ON_CrossProduct( V0, V1 );
  if ( !N2.Unitize() )
    return false;

  const double s0 = 1.0/V0.Length();
  const double s1 = 1.0/V1.Length();
  const double s2 = 1.0/V2.Length();

  // choose normal with smallest total error
  const double e0 = s0*fabs(ON_DotProduct(N0,V0)) + s1*fabs(ON_DotProduct(N0,V1)) + s2*fabs(ON_DotProduct(N0,V2));
  const double e1 = s0*fabs(ON_DotProduct(N1,V0)) + s1*fabs(ON_DotProduct(N1,V1)) + s2*fabs(ON_DotProduct(N1,V2));
  const double e2 = s0*fabs(ON_DotProduct(N2,V0)) + s1*fabs(ON_DotProduct(N2,V1)) + s2*fabs(ON_DotProduct(N2,V2));

  if ( e0 <= e1 ) {
    if ( e0 <= e2 ) {
      *this = N0;
    }
    else {
      *this = N2;
    }
  }
  else if (e1 <= e2) {
    *this = N1;
  }
  else {
    *this = N2;
  }
  
  return true;
}

/*
  This formula does not suffer loss of accuracy in parallel, anti-parallel or perpendicular cases
  see https://people.eecs.berkeley.edu/~wkahan/Mindless.pdf
  To verify the formula consider a rhombus with sides A.Unitize() and B.unitize().
*/
double ON_3dVector::Angle(const ON_3dVector& A, const ON_3dVector& B)
{
  double lenA = A.Length();
  double lenB = B.Length();
  ON_3dVector sum =  lenB * A + lenA * B;
  ON_3dVector diff = lenB * A - lenA * B;
  return 2.0 * atan(diff.Length() / sum.Length());
}


void ON_2dPoint::Transform( const ON_Xform& xform )
{
  double xx,yy,ww;
  ww = xform.m_xform[3][0]*x + xform.m_xform[3][1]*y + xform.m_xform[3][3];
  if ( ww != 0.0 )
    ww = 1.0/ww;
  xx = ww*(xform.m_xform[0][0]*x + xform.m_xform[0][1]*y + xform.m_xform[0][3]);
  yy = ww*(xform.m_xform[1][0]*x + xform.m_xform[1][1]*y + xform.m_xform[1][3]);
  x = xx;
  y = yy;
}

void ON_3dPoint::Transform( const ON_Xform& xform )
{
  double xx,yy,zz,ww;
  ww = xform.m_xform[3][0]*x + xform.m_xform[3][1]*y + xform.m_xform[3][2]*z + xform.m_xform[3][3];
  if ( ww != 0.0 )
    ww = 1.0/ww;
  xx = ww*(xform.m_xform[0][0]*x + xform.m_xform[0][1]*y + xform.m_xform[0][2]*z + xform.m_xform[0][3]);
  yy = ww*(xform.m_xform[1][0]*x + xform.m_xform[1][1]*y + xform.m_xform[1][2]*z + xform.m_xform[1][3]);
  zz = ww*(xform.m_xform[2][0]*x + xform.m_xform[2][1]*y + xform.m_xform[2][2]*z + xform.m_xform[2][3]);
  x = xx;
  y = yy;
  z = zz;
}

void ON_4dPoint::Transform( const ON_Xform& xform )
{
  double xx,yy,zz,ww;
  xx = xform.m_xform[0][0]*x + xform.m_xform[0][1]*y + xform.m_xform[0][2]*z + xform.m_xform[0][3]*w;
  yy = xform.m_xform[1][0]*x + xform.m_xform[1][1]*y + xform.m_xform[1][2]*z + xform.m_xform[1][3]*w;
  zz = xform.m_xform[2][0]*x + xform.m_xform[2][1]*y + xform.m_xform[2][2]*z + xform.m_xform[2][3]*w;
  ww = xform.m_xform[3][0]*x + xform.m_xform[3][1]*y + xform.m_xform[3][2]*z + xform.m_xform[3][3]*w;
  x = xx;
  y = yy;
  z = zz;
  w = ww;
}

void ON_2fPoint::Transform( const ON_Xform& xform )
{
  double xx,yy,ww;
  ww = xform.m_xform[3][0]*x + xform.m_xform[3][1]*y + xform.m_xform[3][3];
  if ( ww != 0.0 )
    ww = 1.0/ww;
  xx = ww*(xform.m_xform[0][0]*x + xform.m_xform[0][1]*y + xform.m_xform[0][3]);
  yy = ww*(xform.m_xform[1][0]*x + xform.m_xform[1][1]*y + xform.m_xform[1][3]);
  x = (float)xx;
  y = (float)yy;
}

void ON_2fPoint::Rotate( 
      double angle,               // angle in radians
      const ON_2fPoint& center  // center of rotation
      )
{
  Rotate( sin(angle), cos(angle), center );
}

void ON_2fPoint::Rotate( 
      double sin_angle,           // sin(angle)
      double cos_angle,           // cos(angle)
      const ON_2fPoint& center  // center of rotation
      )
{
  ON_Xform rot;
  rot.Rotation( sin_angle, cos_angle, ON_3dVector::ZAxis, ON_3dPoint(center) );
  Transform(rot);
}

void ON_3fPoint::Rotate( 
      double angle,               // angle in radians
      const ON_3fVector& axis,  // axis of rotation
      const ON_3fPoint& center  // center of rotation
      )
{
  Rotate( sin(angle), cos(angle), axis, center );
}

void ON_3fPoint::Rotate( 
      double sin_angle,           // sin(angle)
      double cos_angle,           // cos(angle)
      const ON_3fVector& axis,  // axis of rotation
      const ON_3fPoint& center  // center of rotation
      )
{
  ON_Xform rot;
  rot.Rotation( sin_angle, cos_angle, ON_3dVector(axis), ON_3dPoint(center) );
  Transform(rot);
}

void ON_3fPoint::Transform( const ON_Xform& xform )
{
  const double ww = xform.m_xform[3][0]*x + xform.m_xform[3][1]*y + xform.m_xform[3][2]*z + xform.m_xform[3][3];
  if (0.0 == ww)
  {
    ON_ERROR("divide by zero.");
    *this = ON_3fPoint::NanPoint;
  }
  else
  {
    const double xx = (xform.m_xform[0][0] * x + xform.m_xform[0][1] * y + xform.m_xform[0][2] * z + xform.m_xform[0][3]) / ww;
    const double yy = (xform.m_xform[1][0] * x + xform.m_xform[1][1] * y + xform.m_xform[1][2] * z + xform.m_xform[1][3]) / ww;
    const double zz = (xform.m_xform[2][0] * x + xform.m_xform[2][1] * y + xform.m_xform[2][2] * z + xform.m_xform[2][3]) / ww;
    x = (float)xx;
    y = (float)yy;
    z = (float)zz;
  }
}

void ON_4fPoint::Transform( const ON_Xform& xform )
{
  const double xx = xform.m_xform[0][0]*x + xform.m_xform[0][1]*y + xform.m_xform[0][2]*z + xform.m_xform[0][3]*w;
  const double yy = xform.m_xform[1][0]*x + xform.m_xform[1][1]*y + xform.m_xform[1][2]*z + xform.m_xform[1][3]*w;
  const double zz = xform.m_xform[2][0]*x + xform.m_xform[2][1]*y + xform.m_xform[2][2]*z + xform.m_xform[2][3]*w;
  const double ww = xform.m_xform[3][0]*x + xform.m_xform[3][1]*y + xform.m_xform[3][2]*z + xform.m_xform[3][3]*w;
  x = (float)xx;
  y = (float)yy;
  z = (float)zz;
  w = (float)ww;
}

double ON_3fPoint::Fuzz( 
          double absolute_tolerance // (default =  ON_ZERO_TOLERANCE) 
          ) const
{
  double t = MaximumCoordinate()* ON_RELATIVE_TOLERANCE;
  return(t > absolute_tolerance) ? t : absolute_tolerance;
}

bool ON_4dPoint::Normalize()
{
  bool rc = false;
  const int i = MaximumCoordinateIndex();
  double f[4];
  f[0] = fabs(x);
  f[1] = fabs(y);
  f[2] = fabs(z);
  f[3] = fabs(w);
  const double c = f[i];
  if ( c > 0.0 ) {
    double len = 1.0/c;
    f[0] *= len;
    f[1] *= len;
    f[2] *= len;
    f[3] *= len;
    f[i] = 1.0;
		// GBA 7/1/04.  Fixed typo
    const double s = 1.0/( c*sqrt(f[0]*f[0] + f[1]*f[1] + f[2]*f[2] + f[3]*f[3]));
    x *= s;
    y *= s;
    z *= s;
    w *= s;
    rc = true;
  }
  return rc;
}

bool ON_4fPoint::Normalize()
{
  bool rc = false;
  const int i = MaximumCoordinateIndex();
  double f[4];
  f[0] = fabs(x);
  f[1] = fabs(y);
  f[2] = fabs(z);
  f[3] = fabs(w);
  const double c = f[i];
  if ( c > 0.0 ) {
    double len = 1.0/c;
    f[0] *= len;
    f[1] *= len;
    f[2] *= len;
    f[3] *= len;
    f[i] = 1.0;
		// GBA 7/1/04.  Fixed typo
    const double s = 1.0/(c*sqrt(f[0]*f[0] + f[1]*f[1] + f[2]*f[2] + f[3]*f[3]));
    x = (float)(s*x);
    y = (float)(s*y);
    z = (float)(s*z);
    w = (float)(s*w);
    rc = true;
  }
  return rc;
}

bool ON_2fVector::Decompose( // Computes a, b such that this vector = a*X + b*Y
       //
       // If X,Y is known to be an orthonormal frame,
       // then a = V*X, b = V*Y will compute
       // the same result more quickly.
       const ON_2fVector& X,
       const ON_2fVector& Y,
       double* a,
       double* b
       ) const
{
  ON_2dVector V(*this);
  return V.Decompose(ON_2dVector(X),ON_2dVector(Y),a,b);
}


bool ON_2dVector::Decompose( // Computes a, b such that this vector = a*X + b*Y
       //
       // If X,Y is known to be an orthonormal frame,
       // then a = V*X, b = V*Y will compute
       // the same result more quickly.
       const ON_2dVector& X,
       const ON_2dVector& Y,
       double* a,
       double* b
       ) const
{
  int rank;
  double pivot_ratio = 0.0;
  double XoY = X*Y;
  rank = ON_Solve2x2( X*X, XoY, Y*Y, XoY,
                    (*this)*X, (*this)*Y, 
                    a, b, &pivot_ratio );
  return (rank == 2) ? true : false;
}


int ON_2fVector::IsParallelTo( 
      // returns  1: this and other vectors are and parallel
      //         -1: this and other vectors are anti-parallel
      //          0: this and other vectors are not parallel
      //             or at least one of the vectors is zero
      const ON_2fVector& v,
      double angle_tolerance // (default=ON_DEFAULT_ANGLE_TOLERANCE) radians
      ) const
{
  ON_2dVector V(*this);
  return V.IsParallelTo(ON_2dVector(v),angle_tolerance);
}

int ON_2dVector::IsParallelTo( 
      // returns  1: this and other vectors are and parallel
      //         -1: this and other vectors are anti-parallel
      //          0: this and other vectors are not parallel
      //             or at least one of the vectors is zero
      const ON_2dVector& v,
      double angle_tolerance // (default=ON_DEFAULT_ANGLE_TOLERANCE) radians
      ) const
{
  int rc = 0;
  const double ll = Length()*v.Length();
  if ( ll > 0.0 ) {
    const double cos_angle = (x*v.x + y*v.y)/ll;
    const double cos_tol = cos(angle_tolerance);
    if ( cos_angle >= cos_tol )
      rc = 1;
    else if ( cos_angle <= -cos_tol )
      rc = -1;
  }
  return rc;
}


bool ON_2fVector::IsPerpendicularTo(
      // returns true:  this and other vectors are perpendicular
      //         false: this and other vectors are not perpendicular
      //                or at least one of the vectors is zero
      const ON_2fVector& v,
      double angle_tolerance // (default=ON_DEFAULT_ANGLE_TOLERANCE) radians
      ) const
{
  ON_2dVector V(*this);
  return V.IsPerpendicularTo(ON_2dVector(v),angle_tolerance);
}

bool ON_2dVector::IsPerpendicularTo(
      // returns true:  this and other vectors are perpendicular
      //         false: this and other vectors are not perpendicular
      //                or at least one of the vectors is zero
      const ON_2dVector& v,
      double angle_tolerance // (default=ON_DEFAULT_ANGLE_TOLERANCE) radians
      ) const
{
  bool rc = false;
  const double ll = Length()*v.Length();
  if ( ll > 0.0 ) {
    if ( fabs((x*v.x + y*v.y)/ll) <= sin(angle_tolerance) )
      rc = true;
  }
  return rc;
}

void ON_2dVector::Transform( const ON_Xform& xform )
{
  double xx,yy;
  xx = xform.m_xform[0][0]*x + xform.m_xform[0][1]*y;
  yy = xform.m_xform[1][0]*x + xform.m_xform[1][1]*y;
  x = xx;
  y = yy;
}

void ON_3fVector::Transform( const ON_Xform& xform )
{
  const double dx = x;
  const double dy = y;
  const double dz = z;
  double xx = xform.m_xform[0][0]*dx + xform.m_xform[0][1]*dy + xform.m_xform[0][2]*dz;
  double yy = xform.m_xform[1][0]*dx + xform.m_xform[1][1]*dy + xform.m_xform[1][2]*dz;
  double zz = xform.m_xform[2][0]*dx + xform.m_xform[2][1]*dy + xform.m_xform[2][2]*dz;
  x = (float)xx;
  y = (float)yy;
  z = (float)zz;
}

void ON_3dVector::Transform( const ON_Xform& xform )
{
  double xx,yy,zz;
  xx = xform.m_xform[0][0]*x + xform.m_xform[0][1]*y + xform.m_xform[0][2]*z;
  yy = xform.m_xform[1][0]*x + xform.m_xform[1][1]*y + xform.m_xform[1][2]*z;
  zz = xform.m_xform[2][0]*x + xform.m_xform[2][1]*y + xform.m_xform[2][2]*z;
  x = xx;
  y = yy;
  z = zz;
}

void ON_3dPoint::Rotate( 
      double angle,               // angle in radians
      const ON_3dVector& axis,  // axis of rotation
      const ON_3dPoint& center  // center of rotation
      )
{
  Rotate( sin(angle), cos(angle), axis, center );
}

void ON_3dPoint::Rotate( 
      double sin_angle,           // sin(angle)
      double cos_angle,           // cos(angle)
      const ON_3dVector& axis,  // axis of rotation
      const ON_3dPoint& center  // center of rotation
      )
{
  ON_Xform rot;
  rot.Rotation( sin_angle, cos_angle, axis, center );
  Transform(rot);
}

void ON_2dPoint::Rotate( 
      double angle,               // angle in radians
      const ON_2dPoint& center  // center of rotation
      )
{
  Rotate( sin(angle), cos(angle), center );
}

void ON_2dPoint::Rotate( 
      double sin_angle,           // sin(angle)
      double cos_angle,           // cos(angle)
      const ON_2dPoint& center  // center of rotation
      )
{
  ON_Xform rot;
  rot.Rotation( sin_angle, cos_angle, ON_3dVector::ZAxis, ON_3dPoint(center) );
  Transform(rot);
}

void ON_2dVector::Rotate( 
      double angle // angle in radians
      )
{
  Rotate( sin(angle), cos(angle) );
}

void ON_2dVector::Rotate( 
      double sin_angle, // sin(angle)
      double cos_angle  // cos(angle)
      )
{
  ON_Xform rot;
  rot.Rotation( sin_angle, cos_angle, ON_3dVector::ZAxis, ON_3dPoint::Origin );
  Transform(rot);
}

bool ON_IsOrthogonalFrame( const ON_2dVector& X,  const ON_2dVector& Y )
{
  // returns true if X, Y, Z is an orthogonal frame
  double lx = X.Length();
  double ly = Y.Length();
  if ( lx <=  ON_SQRT_EPSILON )
    return false;
  if ( ly <=  ON_SQRT_EPSILON )
    return false;
  lx = 1.0/lx;
  ly = 1.0/ly;
  double x = ON_DotProduct( X, Y )*lx*ly;
  if ( fabs(x) >  ON_SQRT_EPSILON )
    return false;
  return true;
}

bool ON_IsOrthonormalFrame( const ON_2dVector& X,  const ON_2dVector& Y )
{
  // returns true if X, Y, Z is an orthonormal frame
  if ( !ON_IsOrthogonalFrame( X, Y ) )
    return false;
  double x = X.Length();
  if ( fabs(x-1.0) >  ON_SQRT_EPSILON )
    return false;
  x = Y.Length();
  if ( fabs(x-1.0) >  ON_SQRT_EPSILON )
    return false;

  return true;
}

bool ON_IsRightHandFrame( const ON_2dVector& X,  const ON_2dVector& Y )
{
  // returns true if X, Y, Z is an orthonormal right hand frame
  if ( !ON_IsOrthonormalFrame(X,Y) )
    return false;
  double x = ON_DotProduct( ON_CrossProduct( X, Y ), ON_3dVector::ZAxis );
  if ( x <=  ON_SQRT_EPSILON )
    return false;
  return true;
}
void ON_3fVector::Rotate( 
      double angle,              // angle in radians
      const ON_3fVector& axis   // axis of rotation
      )
{
  Rotate( sin(angle), cos(angle), axis );
}

void ON_3fVector::Rotate( 
      double sin_angle,        // sin(angle)
      double cos_angle,        // cos(angle)
      const ON_3fVector& axis  // axis of rotation
      )
{
  //bool rc = false;
  ON_Xform rot;
  rot.Rotation( sin_angle, cos_angle, ON_3dVector(axis), ON_3dPoint::Origin );
  Transform(rot);
}

void ON_3dVector::Rotate( 
      double angle,              // angle in radians
      const ON_3dVector& axis   // axis of rotation
      )
{
  Rotate( sin(angle), cos(angle), axis );
}

void ON_3dVector::Rotate( 
      double sin_angle,        // sin(angle)
      double cos_angle,        // cos(angle)
      const ON_3dVector& axis  // axis of rotation
      )
{
  //bool rc = false;
  ON_Xform rot;
  rot.Rotation( sin_angle, cos_angle, axis, ON_3dPoint::Origin );
  Transform(rot);
}

bool ON_IsOrthogonalFrame( const ON_3dVector& X,  const ON_3dVector& Y,  const ON_3dVector& Z )
{
  // returns true if X, Y, Z is an orthogonal frame
  if (! X.IsValid() || !Y.IsValid() || !Z.IsValid() )
    return false;

  double lx = X.Length();
  double ly = Y.Length();
  double lz = Z.Length();
  if ( lx <=  ON_SQRT_EPSILON )
    return false;
  if ( ly <=  ON_SQRT_EPSILON )
    return false;
  if ( lz <=  ON_SQRT_EPSILON )
    return false;
  lx = 1.0/lx;
  ly = 1.0/ly;
  lz = 1.0/lz;
  double xy = (X.x*Y.x + X.y*Y.y + X.z*Y.z)*lx*ly;
  double yz = (Y.x*Z.x + Y.y*Z.y + Y.z*Z.z)*ly*lz;
  double zx = (Z.x*X.x + Z.y*X.y + Z.z*X.z)*lz*lx;
  if (    fabs(xy) > ON_SQRT_EPSILON 
       || fabs(yz) > ON_SQRT_EPSILON
       || fabs(zx) > ON_SQRT_EPSILON
     )
  {
    double t = 0.0000152587890625;
    if ( fabs(xy) >= t || fabs(yz)  >= t || fabs(zx) >= t )
      return false;

    // do a more careful (and time consuming check)
    // This fixes RR 22219 and 22276
    ON_3dVector V;
    V = (lx*ly)*ON_CrossProduct(X,Y);
    t = fabs((V.x*Z.x + V.y*Z.y + V.z*Z.z)*lz);
    if ( fabs(t-1.0) > ON_SQRT_EPSILON )
      return false;

    V = (ly*lz)*ON_CrossProduct(Y,Z);
    t = fabs((V.x*X.x + V.y*X.y + V.z*X.z)*lx);
    if ( fabs(t-1.0) > ON_SQRT_EPSILON )
      return false;

    V = (lz*lx)*ON_CrossProduct(Z,X);
    t = fabs((V.x*Y.x + V.y*Y.y + V.z*Y.z)*ly);
    if ( fabs(t-1.0) > ON_SQRT_EPSILON )
      return false;
  }
  return true;
}

bool ON_IsOrthonormalFrame( const ON_3dVector& X,  const ON_3dVector& Y,  const ON_3dVector& Z )
{
  // returns true if X, Y, Z is an orthonormal frame
  if ( !ON_IsOrthogonalFrame( X, Y, Z ) )
    return false;
  double x = X.Length();
  if ( fabs(x-1.0) >  ON_SQRT_EPSILON )
    return false;
  x = Y.Length();
  if ( fabs(x-1.0) >  ON_SQRT_EPSILON )
    return false;
  x = Z.Length();
  if ( fabs(x-1.0) >  ON_SQRT_EPSILON )
    return false;

  return true;
}

bool ON_IsRightHandFrame( const ON_3dVector& X,  const ON_3dVector& Y,  const ON_3dVector& Z )
{
  // returns true if X, Y, Z is an orthonormal right hand frame
  if ( !ON_IsOrthonormalFrame(X,Y,Z) )
    return false;
  double x = ON_DotProduct( ON_CrossProduct( X, Y ), Z );
  if ( x <=  ON_SQRT_EPSILON )
    return false;
  return true;
}

ON_2dPoint ON_2dPoint::operator*( const ON_Xform& xform ) const
{
  const double px = x; // optimizer should put px,py in registers
  const double py = y;
  double hx[2], w;
  const double* m = &xform.m_xform[0][0];
  hx[0] = m[0]*px + m[4]*py + m[12];
  hx[1] = m[1]*px + m[5]*py + m[13];
  w     = m[3]*px + m[7]*py + m[15];
  w = (w != 0.0) ? 1.0/w : 1.0;
  return ON_2dPoint( w*hx[0], w*hx[1] );
}

ON_3dPoint ON_3dPoint::operator*( const ON_Xform& xform ) const
{
  const double px = x; // optimizer should put px,py,pz in registers
  const double py = y;
  const double pz = z;
  double hx[3], w;
  const double* m = &xform.m_xform[0][0];
  hx[0] = m[0]*px + m[4]*py + m[ 8]*pz + m[12];
  hx[1] = m[1]*px + m[5]*py + m[ 9]*pz + m[13];
  hx[2] = m[2]*px + m[6]*py + m[10]*pz + m[14];
  w     = m[3]*px + m[7]*py + m[11]*pz + m[15];
  w = (w != 0.0) ? 1.0/w : 1.0;
  return ON_3dPoint( w*hx[0], w*hx[1], w*hx[2] );
}

double ON_3dPoint::Fuzz( 
          double absolute_tolerance // (default =  ON_ZERO_TOLERANCE) 
          ) const
{
  double t = MaximumCoordinate()* ON_RELATIVE_TOLERANCE;
  return(t > absolute_tolerance) ? t : absolute_tolerance;
}

ON_4dPoint ON_4dPoint::operator*( const ON_Xform& xform ) const
{
  const double px = x; // optimizer should put x,y,z,w in registers
  const double py = y;
  const double pz = z;
  const double pw = w;
  double hx[4];
  const double* m = &xform.m_xform[0][0];
  hx[0] = m[0]*px + m[4]*py + m[ 8]*pz + m[12]*pw;
  hx[1] = m[1]*px + m[5]*py + m[ 9]*pz + m[13]*pw;
  hx[2] = m[2]*px + m[6]*py + m[10]*pz + m[14]*pw;
  hx[3] = m[3]*px + m[7]*py + m[11]*pz + m[15]*pw;

  return ON_4dPoint( hx[0],hx[1],hx[2],hx[3] );
}

ON_2dVector ON_2dVector::operator*( const ON_Xform& xform ) const
{
  const double vx = x; // optimizer should put vx,vy in registers
  const double vy = y;
  double hx[2];
  const double* m = &xform.m_xform[0][0];
  hx[0] = m[0]*vx + m[4]*vy;
  hx[1] = m[1]*vx + m[5]*vy;
  return ON_2dVector( hx[0],hx[1] );
}

ON_3dVector ON_3dVector::operator*( const ON_Xform& xform ) const
{
  const double vx = x; // optimizer should put vx,vy,vz in registers
  const double vy = y;
  const double vz = z;
  double hx[3];
  const double* m = &xform.m_xform[0][0];
  hx[0] = m[0]*vx + m[4]*vy + m[ 8]*vz;
  hx[1] = m[1]*vx + m[5]*vy + m[ 9]*vz;
  hx[2] = m[2]*vx + m[6]*vy + m[10]*vz;
  return ON_3dVector( hx[0],hx[1],hx[2] );
}

double ON_3fVector::Fuzz(
          double absolute_tolerance // (default =  ON_ZERO_TOLERANCE) 
          ) const
{
  double t = MaximumCoordinate()* ON_RELATIVE_TOLERANCE;
  return(t > absolute_tolerance) ? t : absolute_tolerance;
}


double ON_3dVector::Fuzz(
          double absolute_tolerance // (default =  ON_ZERO_TOLERANCE) 
          ) const
{
  double t = MaximumCoordinate()* ON_RELATIVE_TOLERANCE;
  return(t > absolute_tolerance) ? t : absolute_tolerance;
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//
// ON_2fPoint
//

ON_2fPoint::ON_2fPoint( const double* p )
{
  if (p) {
    x = (float)p[0]; y = (float)p[1];
  }
  else {
    x = y = 0.0;
  }
}

ON_2fPoint::ON_2fPoint( const float* p )
{
  if (p) {
    x = p[0]; y = p[1];
  }
  else {
    x = y = 0.0;
  }
}

ON_2fPoint::ON_2fPoint(float xx,float yy)
{x=xx;y=yy;}

ON_2fPoint::ON_2fPoint(const ON_3fPoint& p)
{x=p.x;y=p.y;}

ON_2fPoint::ON_2fPoint(const ON_4fPoint& h)
{
  const float w = (h.w != 1.0f && h.w != 0.0f) ? 1.0f/h.w : 1.0f;
  x = w*h.x;
  y = w*h.y;
}

ON_2fPoint::ON_2fPoint(const ON_2fVector& v)
{x=v.x;y=v.y;}

ON_2fPoint::ON_2fPoint(const ON_3fVector& v)
{x=v.x;y=v.y;}

ON_2fPoint::ON_2fPoint(const ON_2dPoint& p)
{x=(float)p.x;y=(float)p.y;}

ON_2fPoint::ON_2fPoint(const ON_3dPoint& p)
{x=(float)p.x;y=(float)p.y;}

ON_2fPoint::ON_2fPoint(const ON_4dPoint& h)
{
  const double w = (h.w != 1.0 && h.w != 0.0) ? 1.0/h.w : 1.0;
  x = (float)(w*h.x);
  y = (float)(w*h.y);
}

ON_2fPoint::ON_2fPoint(const ON_2dVector& v)
{x=(float)v.x;y=(float)v.y;}

ON_2fPoint::ON_2fPoint(const ON_3dVector& v)
{x=(float)v.x;y=(float)v.y;}


ON_2fPoint::operator float*()
{
  return &x;
}

ON_2fPoint::operator const float*() const
{
  return &x;
}

ON_2fPoint& ON_2fPoint::operator=(const double* p)
{
  if ( p ) {
    x = (float)p[0];
    y = (float)p[1];
  }
  else {
    x = y = 0.0;
  }
  return *this;
}

ON_2fPoint& ON_2fPoint::operator=(const float* p)
{
  if ( p ) {
    x = p[0];
    y = p[1];
  }
  else {
    x = y = 0.0;
  }
  return *this;
}

ON_2fPoint& ON_2fPoint::operator=(const ON_3fPoint& p)
{
  x = p.x;
  y = p.y;
  return *this;
}

ON_2fPoint& ON_2fPoint::operator=(const ON_4fPoint& h)
{
  const float w = (h.w != 1.0f && h.w != 0.0f) ? 1.0f/h.w : 1.0f;
  x = w*h.x;
  y = w*h.y;
  return *this;
}

ON_2fPoint& ON_2fPoint::operator=(const ON_2fVector& v)
{
  x = v.x;
  y = v.y;
  return *this;
}

ON_2fPoint& ON_2fPoint::operator=(const ON_3fVector& v)
{
  x = v.x;
  y = v.y;
  return *this;
}

ON_2fPoint& ON_2fPoint::operator=(const ON_2dPoint& p)
{
  x = (float)p.x;
  y = (float)p.y;
  return *this;
}

ON_2fPoint& ON_2fPoint::operator=(const ON_3dPoint& p)
{
  x = (float)p.x;
  y = (float)p.y;
  return *this;
}

ON_2fPoint& ON_2fPoint::operator=(const ON_4dPoint& h)
{
  const double w = (h.w != 1.0 && h.w != 0.0) ? 1.0/h.w : 1.0;
  x = (float)(w*h.x);
  y = (float)(w*h.y);
  return *this;
}

ON_2fPoint& ON_2fPoint::operator=(const ON_2dVector& v)
{
  x = (float)v.x;
  y = (float)v.y;
  return *this;
}

ON_2fPoint& ON_2fPoint::operator=(const ON_3dVector& v)
{
  x = (float)v.x;
  y = (float)v.y;
  return *this;
}

ON_2fPoint& ON_2fPoint::operator*=(float d)
{
  x *= d;
  y *= d;
  return *this;
}

ON_2fPoint& ON_2fPoint::operator/=(float d)
{
  const float one_over_d = 1.0f/d;
  x *= one_over_d;
  y *= one_over_d;
  return *this;
}

ON_2fPoint& ON_2fPoint::operator+=(const ON_2fVector& v)
{
  x += v.x;
  y += v.y;
  return *this;
}

ON_2fPoint& ON_2fPoint::operator-=(const ON_2fVector& v)
{
  x -= v.x;
  y -= v.y;
  return *this;
}

ON_2fPoint ON_2fPoint::operator*( int d ) const
{
  return ON_2fPoint(x*d,y*d);
}

ON_2fPoint ON_2fPoint::operator*( float d ) const
{
  return ON_2fPoint(x*d,y*d);
}

ON_2dPoint ON_2fPoint::operator*( double d ) const
{
  return ON_2dPoint(x*d,y*d);
}

ON_2fPoint ON_2fPoint::operator/( int i ) const
{
  const float one_over_d = 1.0f/((float)i);
  return ON_2fPoint(x*one_over_d,y*one_over_d);
}

ON_2fPoint ON_2fPoint::operator/( float d ) const
{
  const float one_over_d = 1.0f/d;
  return ON_2fPoint(x*one_over_d,y*one_over_d);
}

ON_2dPoint ON_2fPoint::operator/( double d ) const
{
  const double one_over_d = 1.0/d;
  return ON_2dPoint(x*one_over_d,y*one_over_d);
}

ON_2fPoint ON_2fPoint::operator+( const ON_2fPoint& p ) const
{
  return ON_2fPoint(x+p.x,y+p.y);
}

ON_2fPoint ON_2fPoint::operator+( const ON_2fVector& v ) const
{
  return ON_2fPoint(x+v.x,y+v.y);
}

ON_2fVector ON_2fPoint::operator-( const ON_2fPoint& p ) const
{
  return ON_2fVector(x-p.x,y-p.y);
}

ON_2fPoint ON_2fPoint::operator-( const ON_2fVector& v ) const
{
  return ON_2fPoint(x-v.x,y-v.y);
}

ON_3fPoint ON_2fPoint::operator+( const ON_3fPoint& p ) const
{
  return ON_3fPoint(x+p.x,y+p.y,p.z);
}

ON_3fPoint ON_2fPoint::operator+( const ON_3fVector& v ) const
{
  return ON_3fPoint(x+v.x,y+v.y,v.z);
}

ON_3fVector ON_2fPoint::operator-( const ON_3fPoint& p ) const
{
  return ON_3fVector(x-p.x,y-p.y,-p.y);
}

ON_3fPoint ON_2fPoint::operator-( const ON_3fVector& v ) const
{
  return ON_3fPoint(x-v.x,y-v.y,-v.z);
}

ON_2dPoint ON_2fPoint::operator+( const ON_2dPoint& p ) const
{
  return ON_2dPoint(x+p.x,y+p.y);
}

ON_2dPoint ON_2fPoint::operator+( const ON_2dVector& v ) const
{
  return ON_2dPoint(x+v.x,y+v.y);
}

ON_2dVector ON_2fPoint::operator-( const ON_2dPoint& p ) const
{
  return ON_2dVector(x-p.x,y-p.y);
}

ON_2dPoint ON_2fPoint::operator-( const ON_2dVector& v ) const
{
  return ON_2dPoint(x-v.x,y-v.y);
}

ON_3dPoint ON_2fPoint::operator+( const ON_3dPoint& p ) const
{
  return ON_3dPoint(x+p.x,y+p.y,p.z);
}

ON_3dPoint ON_2fPoint::operator+( const ON_3dVector& v ) const
{
  return ON_3dPoint(x+v.x,y+v.y,v.z);
}

ON_3dVector ON_2fPoint::operator-( const ON_3dPoint& p ) const
{
  return ON_3dVector(x-p.x,y-p.y,-p.y);
}

ON_3dPoint ON_2fPoint::operator-( const ON_3dVector& v ) const
{
  return ON_3dPoint(x-v.x,y-v.y,-v.z);
}


float ON_2fPoint::operator*(const ON_2fPoint& h) const
{
  return x*h.x + y*h.y;
}

float ON_2fPoint::operator*(const ON_2fVector& h) const
{
  return x*h.x + y*h.y;
}

bool ON_2fPoint::operator==( const ON_2fPoint& p ) const
{
  return (x==p.x&&y==p.y)?true:false;
}

static bool Internal_NotEqualDoubleArray(size_t count, const double* lhs, const double* rhs)
{
  bool rc = false;
  const double* e = lhs + count; 
  while (lhs < e)
  {
    const double x = *lhs++;
    const double y = *rhs++;
    if (x != y)
    {
      // neither x nor y is a nan
      rc = true;
      continue;
    }
    if (!(x == x))
      return false; // nan
    if (!(y == y))
      return false; // nan
  }
  return rc;
}

static bool Internal_NotEqualFloatArray(size_t count, const float* lhs, const float* rhs)
{
  bool rc = false;
  const float* e = lhs + count; 
  while (lhs < e)
  {
    const float x = *lhs++;
    const float y = *rhs++;
    if (x != y)
    {
      // neither x nor y is a nan
      rc = true;
      continue;
    }
    if (!(x == x))
      return false; // nan
    if (!(y == y))
      return false; // nan
  }
  return rc;
}

bool ON_4fPoint::operator!=(const ON_4fPoint& rhs) const
{
  return Internal_NotEqualFloatArray(4, &x, &rhs.x);
}

bool ON_4fPoint::operator==(const ON_4fPoint& rhs) const
{
  return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w);
}

bool ON_2fPoint::operator!=( const ON_2fPoint& p ) const
{ 
  return Internal_NotEqualFloatArray(2, &x, &p.x);
}

bool ON_2fPoint::operator<=( const ON_2fPoint& p ) const
{
  // dictionary order
  return ( (x<p.x) ? true : ((x==p.x&&y<=p.y)?true:false) );
}

bool ON_2fPoint::operator>=( const ON_2fPoint& p ) const
{
  // dictionary order
  return ( (x>p.x) ? true : ((x==p.x&&y>=p.y)?true:false) );
}

bool ON_2fPoint::operator<( const ON_2fPoint& p ) const
{
  // dictionary order
  return ( (x<p.x) ? true : ((x==p.x&&y<p.y)?true:false) );
}

bool ON_2fPoint::operator>( const ON_2fPoint& p ) const
{
  // dictionary order
  return ( (x>p.x) ? true : ((x==p.x&&y>p.y)?true:false) );
}

float ON_2fPoint::operator[](int i) const
{
  return (i<=0) ? x : y;
}

float& ON_2fPoint::operator[](int i)
{
  float* pd = (i<=0)? &x : &y;
  return *pd;
}

float ON_2fPoint::operator[](unsigned int i) const
{
  return (i<=0) ? x : y;
}

float& ON_2fPoint::operator[](unsigned int i)
{
  float* pd = (i<=0)? &x : &y;
  return *pd;
}

double ON_2fPoint::DistanceTo( const ON_2fPoint& p ) const
{
  return ON_Length2d(p.x-x,p.y-y);
}

double ON_2fPoint::DistanceToSquared(const ON_2fPoint& p) const
{
  return ON_Length2dSquared(p.x - x, p.y - y);
}

int ON_2fPoint::MaximumCoordinateIndex() const
{
  return (fabs(y)>fabs(x)) ? 1 : 0;
}

double ON_2fPoint::MaximumCoordinate() const
{
  double c = fabs(x); if (fabs(y)>c) c=fabs(y);
  return c;
}

void ON_2fPoint::Zero()
{
  x = y = 0.0;
}

bool ON_2fPoint::IsZero() const
{
  return (x==0.0f && y==0.0f);
}

bool ON_2fPoint::IsNotZero() const
{
  return
    (x != 0.0f || y != 0.0f)
    && (x != ON_UNSET_FLOAT && y != ON_UNSET_FLOAT)
    && (x != ON_UNSET_POSITIVE_FLOAT && y != ON_UNSET_POSITIVE_FLOAT);
}

ON_2fPoint operator*(int d, const ON_2fPoint& p)
{
  return ON_2fPoint(d*p.x,d*p.y);
}

ON_2fPoint operator*(float d, const ON_2fPoint& p)
{
  return ON_2fPoint(d*p.x,d*p.y);
}

ON_2dPoint operator*(double d, const ON_2fPoint& p)
{
  return ON_2dPoint(d*p.x,d*p.y);
}

////////////////////////////////////////////////////////////////
//
// ON_3fPoint
//

ON_3fPoint::ON_3fPoint( const double* p )
{
  if (p) {
    x = (float)p[0]; y = (float)p[1]; z = (float)p[2];
  }
  else {
    x = y = z = 0.0;
  }
}

ON_3fPoint::ON_3fPoint( const float* p )
{
  if (p) {
    x = p[0]; y = p[1]; z = p[2];
  }
  else {
    x = y = z = 0.0;
  }
}

ON_3fPoint::ON_3fPoint(float xx,float yy,float zz)
{x=xx;y=yy;z=zz;}

ON_3fPoint::ON_3fPoint(const ON_2fPoint& p)
{x=p.x;y=p.y;z=0.0;}

ON_3fPoint::ON_3fPoint(const ON_4fPoint& p)
{
  const double w = (p.w != 1.0f && p.w != 0.0f) ? 1.0/((double)p.w) : 1.0;
  x = (float)(w*p.x);
  y = (float)(w*p.y);
  z = (float)(w*p.z);
}

ON_3fPoint::ON_3fPoint(const ON_2fVector& v)
{x=v.x;y=v.y;z=0.0f;}

ON_3fPoint::ON_3fPoint(const ON_3fVector& v)
{x=v.x;y=v.y;z=v.z;}

ON_3fPoint::ON_3fPoint(const ON_2dPoint& p)
{x=(float)p.x;y=(float)p.y;z=0.0;}

ON_3fPoint::ON_3fPoint(const ON_3dPoint& p)
{x=(float)p.x;y=(float)p.y;z=(float)p.z;}

ON_3fPoint::ON_3fPoint(const ON_4dPoint& p)
{
  const double w = (p.w != 1.0 && p.w != 0.0) ? 1.0/p.w : 1.0;
  x = (float)(w*p.x);
  y = (float)(w*p.y);
  z = (float)(w*p.z);
}

ON_3fPoint::ON_3fPoint(const ON_2dVector& v)
{x=(float)v.x;y=(float)v.y;z=0.0f;}

ON_3fPoint::ON_3fPoint(const ON_3dVector& v)
{x=(float)v.x;y=(float)v.y;z=(float)v.z;}

ON_3fPoint::operator float*()
{
  return &x;
}

ON_3fPoint::operator const float*() const
{
  return &x;
}

ON_3fPoint& ON_3fPoint::operator=(const double* p)
{
  if ( p ) {
    x = (float)p[0];
    y = (float)p[1];
    z = (float)p[2];
  }
  else {
    x = y = z = 0.0;
  }
  return *this;
}

ON_3fPoint& ON_3fPoint::operator=(const float* p)
{
  if ( p ) {
    x = p[0];
    y = p[1];
    z = p[2];
  }
  else {
    x = y = z = 0.0;
  }
  return *this;
}

ON_3fPoint& ON_3fPoint::operator=(const ON_2fPoint& p)
{
  x = p.x;
  y = p.y;
  z = 0.0;
  return *this;
}

ON_3fPoint& ON_3fPoint::operator=(const ON_4fPoint& p)
{
  const float w = (p.w != 1.0f && p.w != 0.0f) ? 1.0f/p.w : 1.0f;
  x = w*p.x;
  y = w*p.y;
  z = w*p.z;
  return *this;
}

ON_3fPoint& ON_3fPoint::operator=(const ON_2fVector& v)
{
  x = v.x;
  y = v.y;
  z = 0.0f;
  return *this;
}

ON_3fPoint& ON_3fPoint::operator=(const ON_3fVector& v)
{
  x = v.x;
  y = v.y;
  z = v.z;
  return *this;
}

ON_3fPoint& ON_3fPoint::operator=(const ON_2dPoint& p)
{
  x = (float)p.x;
  y = (float)p.y;
  z = 0.0f;
  return *this;
}

ON_3fPoint& ON_3fPoint::operator=(const ON_3dPoint& p)
{
  x = (float)p.x;
  y = (float)p.y;
  z = (float)p.z;
  return *this;
}

ON_3fPoint& ON_3fPoint::operator=(const ON_4dPoint& p)
{
  const double w = (p.w != 1.0 && p.w != 0.0) ? 1.0/p.w : 1.0;
  x = (float)(w*p.x);
  y = (float)(w*p.y);
  z = (float)(w*p.z);
  return *this;
}

ON_3fPoint& ON_3fPoint::operator=(const ON_2dVector& v)
{
  x = (float)v.x;
  y = (float)v.y;
  z = 0.0f;
  return *this;
}

ON_3fPoint& ON_3fPoint::operator=(const ON_3dVector& v)
{
  x = (float)v.x;
  y = (float)v.y;
  z = (float)v.z;
  return *this;
}

ON_3fPoint& ON_3fPoint::operator*=(float d)
{
  x *= d;
  y *= d;
  z *= d;
  return *this;
}

ON_3fPoint& ON_3fPoint::operator/=(float d)
{
  const float one_over_d = 1.0f/d;
  x *= one_over_d;
  y *= one_over_d;
  z *= one_over_d;
  return *this;
}

ON_3fPoint& ON_3fPoint::operator+=(const ON_3fVector& v)
{
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

ON_3fPoint& ON_3fPoint::operator-=(const ON_3fVector& v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

ON_3fPoint ON_3fPoint::operator*( int d ) const
{
  return ON_3fPoint(x*d,y*d,z*d);
}

ON_3fPoint ON_3fPoint::operator*( float d ) const
{
  return ON_3fPoint(x*d,y*d,z*d);
}

ON_3dPoint ON_3fPoint::operator*( double d ) const
{
  return ON_3dPoint(x*d,y*d,z*d);
}

ON_3fPoint ON_3fPoint::operator/( int d ) const
{
  const float one_over_d = 1.0f/((float)d);
  return ON_3fPoint(x*one_over_d,y*one_over_d,z*one_over_d);
}

ON_3fPoint ON_3fPoint::operator/( float d ) const
{
  const float one_over_d = 1.0f/d;
  return ON_3fPoint(x*one_over_d,y*one_over_d,z*one_over_d);
}

ON_3dPoint ON_3fPoint::operator/( double d ) const
{
  const double one_over_d = 1.0/d;
  return ON_3dPoint(x*one_over_d,y*one_over_d,z*one_over_d);
}

ON_3fPoint ON_3fPoint::operator+( const ON_3fPoint& p ) const
{
  return ON_3fPoint(x+p.x,y+p.y,z+p.z);
}

ON_3fPoint ON_3fPoint::operator+( const ON_3fVector& v ) const
{
  return ON_3fPoint(x+v.x,y+v.y,z+v.z);
}

ON_3fVector ON_3fPoint::operator-( const ON_3fPoint& p ) const
{
  return ON_3fVector(x-p.x,y-p.y,z-p.z);
}

ON_3fPoint ON_3fPoint::operator-( const ON_3fVector& v ) const
{
  return ON_3fPoint(x-v.x,y-v.y,z-v.z);
}


ON_3fPoint ON_3fPoint::operator+( const ON_2fPoint& p ) const
{
  return ON_3fPoint(x+p.x,y+p.y,z);
}

ON_3fPoint ON_3fPoint::operator+( const ON_2fVector& v ) const
{
  return ON_3fPoint(x+v.x,y+v.y,z);
}

ON_3fVector ON_3fPoint::operator-( const ON_2fPoint& p ) const
{
  return ON_3fVector(x-p.x,y-p.y,z);
}

ON_3fPoint ON_3fPoint::operator-( const ON_2fVector& v ) const
{
  return ON_3fPoint(x-v.x,y-v.y,z);
}

ON_3dPoint ON_3fPoint::operator+( const ON_3dPoint& p ) const
{
  return ON_3dPoint(x+p.x,y+p.y,z+p.z);
}

ON_3dPoint ON_3fPoint::operator+( const ON_3dVector& v ) const
{
  return ON_3dPoint(x+v.x,y+v.y,z+v.z);
}

ON_3dVector ON_3fPoint::operator-( const ON_3dPoint& p ) const
{
  return ON_3dVector(x-p.x,y-p.y,z-p.z);
}

ON_3dPoint ON_3fPoint::operator-( const ON_3dVector& v ) const
{
  return ON_3dPoint(x-v.x,y-v.y,z-v.z);
}


ON_3dPoint ON_3fPoint::operator+( const ON_2dPoint& p ) const
{
  return ON_3dPoint(x+p.x,y+p.y,z);
}

ON_3dPoint ON_3fPoint::operator+( const ON_2dVector& v ) const
{
  return ON_3dPoint(x+v.x,y+v.y,z);
}

ON_3dVector ON_3fPoint::operator-( const ON_2dPoint& p ) const
{
  return ON_3dVector(x-p.x,y-p.y,z);
}

ON_3dPoint ON_3fPoint::operator-( const ON_2dVector& v ) const
{
  return ON_3dPoint(x-v.x,y-v.y,z);
}


float ON_3fPoint::operator*(const ON_3fPoint& h) const
{
  return x*h.x + y*h.y + z*h.z;
}

float ON_3fPoint::operator*(const ON_3fVector& h) const
{
  return x*h.x + y*h.y + z*h.z;
}

bool ON_3fPoint::operator==( const ON_3fPoint& p ) const
{
  return (x==p.x&&y==p.y&&z==p.z)?true:false;
}

bool ON_3fPoint::operator!=( const ON_3fPoint& p ) const
{
  return Internal_NotEqualFloatArray(3, &x, &p.x);
}

bool ON_3fPoint::operator<=( const ON_3fPoint& p ) const
{
  // dictionary order
  return ((x<p.x)?true:((x==p.x)?((y<p.y)?true:(y==p.y&&z<=p.z)?true:false):false));
}

bool ON_3fPoint::operator>=( const ON_3fPoint& p ) const
{
  // dictionary order
  return ((x>p.x)?true:((x==p.x)?((y>p.y)?true:(y==p.y&&z>=p.z)?true:false):false));
}

bool ON_3fPoint::operator<( const ON_3fPoint& p ) const
{
  // dictionary order
  return ((x<p.x)?true:((x==p.x)?((y<p.y)?true:(y==p.y&&z<p.z)?true:false):false));
}

bool ON_3fPoint::operator>( const ON_3fPoint& p ) const
{
  // dictionary order
  return ((x>p.x)?true:((x==p.x)?((y>p.y)?true:(y==p.y&&z>p.z)?true:false):false));
}

float ON_3fPoint::operator[](int i) const
{
  return ( (i<=0)?x:((i>=2)?z:y) );
}

float& ON_3fPoint::operator[](int i)
{
  float* pd = (i<=0)? &x : ( (i>=2) ?  &z : &y);
  return *pd;
}

float ON_3fPoint::operator[](unsigned int i) const
{
  return ( (i<=0)?x:((i>=2)?z:y) );
}

float& ON_3fPoint::operator[](unsigned int i)
{
  float* pd = (i<=0)? &x : ( (i>=2) ?  &z : &y);
  return *pd;
}

double ON_3fPoint::DistanceTo( const ON_3fPoint& p ) const
{
  return ON_Length3d(p.x-x,p.y-y,p.z-z);
}

double ON_3fPoint::DistanceToSquared(const ON_3fPoint& p) const
{
  return ON_Length3dSquared(p.x - x, p.y - y, p.z - z);
}

int ON_3fPoint::MaximumCoordinateIndex() const
{
  return (fabs(y)>fabs(x)) ? ((fabs(z)>fabs(y))?2:1) : ((fabs(z)>fabs(x))?2:0);
}

double ON_3fPoint::MaximumCoordinate() const
{
  double c = fabs(x); if (fabs(y)>c) c=fabs(y); if (fabs(z)>c) c=fabs(z);
  return c;
}

void ON_3fPoint::Zero()
{
  x = y = z = 0.0;
}

bool ON_3fPoint::IsZero() const
{
  return (x==0.0f && y==0.0f && z==0.0f);
}

bool ON_3fPoint::IsNotZero() const
{
  // the && (x != ON_UNSET_FLOAT && y != ON_UNSET_FLOAT && z != ON_UNSET_FLOAT) insures no coordinate is a Nan.
  return
    (x != 0.0f || y != 0.0f || z != 0.0f)
    && (x != ON_UNSET_FLOAT && y != ON_UNSET_FLOAT && z != ON_UNSET_FLOAT)
    && (x != ON_UNSET_POSITIVE_FLOAT && y != ON_UNSET_POSITIVE_FLOAT && z != ON_UNSET_POSITIVE_FLOAT);
}

ON_3fPoint operator*(int d, const ON_3fPoint& p)
{
  return ON_3fPoint(d*p.x,d*p.y,d*p.z);
}

ON_3fPoint operator*(float d, const ON_3fPoint& p)
{
  return ON_3fPoint(d*p.x,d*p.y,d*p.z);
}

ON_3dPoint operator*(double d, const ON_3fPoint& p)
{
  return ON_3dPoint(d*p.x,d*p.y,d*p.z);
}

////////////////////////////////////////////////////////////////
//
// ON_4fPoint
//

ON_4fPoint::ON_4fPoint( const double* p )
{
  if (p) {
    x = (float)p[0]; y = (float)p[1]; z = (float)p[2]; w = (float)p[3];
  }
  else {
    x = y = z = 0.0; w = 1.0;
  }
}

ON_4fPoint::ON_4fPoint( const float* p )
{
  if (p) {
    x = p[0]; y = p[1]; z = p[2]; w = p[3];
  }
  else {
    x = y = z = 0.0; w = 1.0;
  }
}

ON_4fPoint::ON_4fPoint(float xx,float yy,float zz,float ww)
{x=xx;y=yy;z=zz;w=ww;}

ON_4fPoint::ON_4fPoint(const ON_2fPoint& p)
{x=p.x;y=p.y;z=0.0;w=1.0;}

ON_4fPoint::ON_4fPoint(const ON_3fPoint& p)
{
  x=p.x;y=p.y;z=p.z;w=1.0;
}

ON_4fPoint::ON_4fPoint(const ON_2fVector& v)
{x=v.x;y=v.y;z=w=0.0;}

ON_4fPoint::ON_4fPoint(const ON_3fVector& v)
{x=v.x;y=v.y;z=v.z;w=0.0;}

ON_4fPoint::ON_4fPoint(const ON_2dPoint& p)
{x=(float)p.x;y=(float)p.y;z=0.0f;w=1.0f;}

ON_4fPoint::ON_4fPoint(const ON_3dPoint& p)
{
  x=(float)p.x;y=(float)p.y;z=(float)p.z;w=1.0f;
}

ON_4fPoint::ON_4fPoint(const ON_4dPoint& p)
{
  x=(float)p.x;y=(float)p.y;z=(float)p.z;w=(float)p.w;
}

ON_4fPoint::ON_4fPoint(const ON_2dVector& v)
{x=(float)v.x;y=(float)v.y;z=w=0.0f;}

ON_4fPoint::ON_4fPoint(const ON_3dVector& v)
{x=(float)v.x;y=(float)v.y;z=(float)v.z;w=0.0f;}

ON_4fPoint::operator float*()
{
  return &x;
}

ON_4fPoint::operator const float*() const
{
  return &x;
}

ON_4fPoint& ON_4fPoint::operator=(const double* p)
{
  if ( p ) {
    x = (float)p[0];
    y = (float)p[1];
    z = (float)p[2];
    w = (float)p[3];
  }
  else {
    x = y = z = 0.0; w = 1.0;
  }
  return *this;
}

ON_4fPoint& ON_4fPoint::operator=(const float* p)
{
  if ( p ) {
    x = p[0];
    y = p[1];
    z = p[2];
    w = p[3];
  }
  else {
    x = y = z = 0.0; w = 1.0;
  }
  return *this;
}

ON_4fPoint& ON_4fPoint::operator=(const ON_2fPoint& p)
{
  x = p.x;
  y = p.y;
  z = 0.0;
  w = 1.0;
  return *this;
}

ON_4fPoint& ON_4fPoint::operator=(const ON_3fPoint& p)
{
  x = p.x;
  y = p.y;
  z = p.z;
  w = 1.0;
  return *this;
}

ON_4fPoint& ON_4fPoint::operator=(const ON_2fVector& v)
{
  x = v.x;
  y = v.y;
  z = 0.0;
  w = 0.0;
  return *this;
}

ON_4fPoint& ON_4fPoint::operator=(const ON_3fVector& v)
{
  x = v.x;
  y = v.y;
  z = v.z;
  w = 0.0;
  return *this;
}

ON_4fPoint& ON_4fPoint::operator=(const ON_2dPoint& p)
{
  x = (float)p.x;
  y = (float)p.y;
  z = 0.0;
  w = 1.0;
  return *this;
}

ON_4fPoint& ON_4fPoint::operator=(const ON_3dPoint& p)
{
  x = (float)p.x;
  y = (float)p.y;
  z = (float)p.z;
  w = 1.0;
  return *this;
}

ON_4fPoint& ON_4fPoint::operator=(const ON_4dPoint& p)
{
  x = (float)p.x;
  y = (float)p.y;
  z = (float)p.z;
  w = (float)p.w;
  return *this;
}

ON_4fPoint& ON_4fPoint::operator=(const ON_2dVector& v)
{
  x = (float)v.x;
  y = (float)v.y;
  z = 0.0;
  w = 0.0;
  return *this;
}

ON_4fPoint& ON_4fPoint::operator=(const ON_3dVector& v)
{
  x = (float)v.x;
  y = (float)v.y;
  z = (float)v.z;
  w = 0.0;
  return *this;
}

ON_4fPoint& ON_4fPoint::operator*=(float d)
{
  x *= d;
  y *= d;
  z *= d;
  w *= d;
  return *this;
}

ON_4fPoint& ON_4fPoint::operator/=(float d)
{
  const float one_over_d = 1.0f/d;
  x *= one_over_d;
  y *= one_over_d;
  z *= one_over_d;
  w *= one_over_d;
  return *this;
}

ON_4fPoint& ON_4fPoint::operator+=(const ON_4fPoint& p)
{
  // sum w = sqrt(w1*w2)
  if ( p.w == w ) {
    x += p.x;
    y += p.y;
    z += p.z;
  }
  else if (p.w == 0.0 ) {
    x += p.x;
    y += p.y;
    z += p.z;
  }
  else if ( w == 0.0 ) {
    x += p.x;
    y += p.y;
    z += p.z;
    w = p.w;
  }
  else {
    const double sw1 = (w>0.0) ? sqrt(w) : -sqrt(-w);
    const double sw2 = (p.w>0.0) ? sqrt(p.w) : -sqrt(-p.w);
    const double s1 = sw2/sw1;
    const double s2 = sw1/sw2;
    x = (float)(x*s1 + p.x*s2);
    y = (float)(y*s1 + p.y*s2);
    z = (float)(z*s1 + p.z*s2);
    w = (float)(sw1*sw2);
  }
  return *this;
}

ON_4fPoint& ON_4fPoint::operator-=(const ON_4fPoint& p)
{
  // difference w = sqrt(w1*w2)
  if ( p.w == w ) {
    x -= p.x;
    y -= p.y;
    z -= p.z;
  }
  else if (p.w == 0.0 ) {
    x -= p.x;
    y -= p.y;
    z -= p.z;
  }
  else if ( w == 0.0 ) {
    x -= p.x;
    y -= p.y;
    z -= p.z;
    w = p.w;
  }
  else {
    const double sw1 = (w>0.0) ? sqrt(w) : -sqrt(-w);
    const double sw2 = (p.w>0.0) ? sqrt(p.w) : -sqrt(-p.w);
    const double s1 = sw2/sw1;
    const double s2 = sw1/sw2;
    x = (float)(x*s1 - p.x*s2);
    y = (float)(y*s1 - p.y*s2);
    z = (float)(z*s1 - p.z*s2);
    w = (float)(sw1*sw2);
  }
  return *this;
}

ON_4fPoint ON_4fPoint::operator+( const ON_4fPoint& p ) const
{
  ON_4fPoint q(x,y,z,w);
  q+=p;
  return q;
}

ON_4fPoint ON_4fPoint::operator-( const ON_4fPoint& p ) const
{
  ON_4fPoint q(x,y,z,w);
  q-=p;
  return q;
}


ON_4fPoint ON_4fPoint::operator*( float d ) const
{
  return ON_4fPoint(x*d,y*d,z*d,w*d);
}

ON_4fPoint ON_4fPoint::operator/( float d ) const
{
  const float one_over_d = 1.0f/d;
  return ON_4fPoint(x*one_over_d,y*one_over_d,z*one_over_d,w*one_over_d);
}

float ON_4fPoint::operator[](int i) const
{
  return ((i<=0)?x:((i>=3)?w:((i==1)?y:z)));
}

float& ON_4fPoint::operator[](int i)
{
  float* pd = (i<=0) ? &x : ( (i>=3) ? &w : (i==1)?&y:&z);
  return *pd;
}

float ON_4fPoint::operator[](unsigned int i) const
{
  return ((i<=0)?x:((i>=3)?w:((i==1)?y:z)));
}

float& ON_4fPoint::operator[](unsigned int i)
{
  float* pd = (i<=0) ? &x : ( (i>=3) ? &w : (i==1)?&y:&z);
  return *pd;
}

int ON_4fPoint::MaximumCoordinateIndex() const
{
  const float* a = &x;
  int i = ( fabs(y) > fabs(x) ) ? 1 : 0;
  if (fabs(z) > fabs(a[i])) i = 2; if (fabs(w) > fabs(a[i])) i = 3;
  return i;
}

double ON_4fPoint::MaximumCoordinate() const
{
  double c = fabs(x); if (fabs(y)>c) c=fabs(y); if (fabs(z)>c) c=fabs(z); if (fabs(w)>c) c=fabs(w);
  return c;
}

ON_4fPoint operator*( float d, const ON_4fPoint& p )
{
  return ON_4fPoint( d*p.x, d*p.y, d*p.z, d*p.w );
}

ON_4dPoint operator*( double d, const ON_4fPoint& p )
{
  return ON_4dPoint( d*p.x, d*p.y, d*p.z, d*p.w );
}

////////////////////////////////////////////////////////////////
//
// ON_2fVector
//

// static
const ON_2fVector& ON_2fVector::UnitVector(int index)
{
  static ON_2fVector o(0.0,0.0);
  static ON_2fVector x(1.0,0.0);
  static ON_2fVector y(0.0,1.0);
  switch(index)
  {
  case 0:
    return x;
  case 1:
    return y;
  }
  return o;
}

ON_2fVector::ON_2fVector( const double* v )
{
  if (v) {
    x = (float)v[0]; y = (float)v[1];
  }
  else {
    x = y = 0.0;
  }
}

ON_2fVector::ON_2fVector( const float* v )
{
  if (v) {
    x = v[0]; y = v[1];
  }
  else {
    x = y = 0.0;
  }
}

ON_2fVector::ON_2fVector(float xx,float yy)
{x=xx;y=yy;}

ON_2fVector::ON_2fVector(const ON_3fVector& v)
{x=v.x;y=v.y;}

ON_2fVector::ON_2fVector(const ON_2fPoint& p)
{x=p.x;y=p.y;}

ON_2fVector::ON_2fVector(const ON_3fPoint& p)
{x=p.x;y=p.y;}

ON_2fVector::ON_2fVector(const ON_2dVector& v)
{x=(float)v.x;y=(float)v.y;}

ON_2fVector::ON_2fVector(const ON_3dVector& v)
{x=(float)v.x;y=(float)v.y;}

ON_2fVector::ON_2fVector(const ON_2dPoint& p)
{x=(float)p.x;y=(float)p.y;}

ON_2fVector::ON_2fVector(const ON_3dPoint& p)
{x=(float)p.x;y=(float)p.y;}

ON_2fVector::operator float*()
{
  return &x;
}

ON_2fVector::operator const float*() const
{
  return &x;
}

ON_2fVector& ON_2fVector::operator=(const double* v)
{
  if ( v ) {
    x = (float)v[0];
    y = (float)v[1];
  }
  else {
    x = y = 0.0;
  }
  return *this;
}

ON_2fVector& ON_2fVector::operator=(const float* v)
{
  if ( v ) {
    x = v[0];
    y = v[1];
  }
  else {
    x = y = 0.0;
  }
  return *this;
}

ON_2fVector& ON_2fVector::operator=(const ON_3fVector& v)
{
  x = v.x;
  y = v.y;
  return *this;
}

ON_2fVector& ON_2fVector::operator=(const ON_2fPoint& p)
{
  x = p.x;
  y = p.y;
  return *this;
}

ON_2fVector& ON_2fVector::operator=(const ON_3fPoint& p)
{
  x = p.x;
  y = p.y;
  return *this;
}


ON_2fVector& ON_2fVector::operator=(const ON_2dVector& v)
{
  x = (float)v.x;
  y = (float)v.y;
  return *this;
}

ON_2fVector& ON_2fVector::operator=(const ON_3dVector& v)
{
  x = (float)v.x;
  y = (float)v.y;
  return *this;
}

ON_2fVector& ON_2fVector::operator=(const ON_2dPoint& p)
{
  x = (float)p.x;
  y = (float)p.y;
  return *this;
}

ON_2fVector& ON_2fVector::operator=(const ON_3dPoint& p)
{
  x = (float)p.x;
  y = (float)p.y;
  return *this;
}

ON_2fVector ON_2fVector::operator-() const
{
  return ON_2fVector(-x,-y);
}

ON_2fVector& ON_2fVector::operator*=(float d)
{
  x *= d;
  y *= d;
  return *this;
}

ON_2fVector& ON_2fVector::operator/=(float d)
{
  const float one_over_d = 1.0f/d;
  x *= one_over_d;
  y *= one_over_d;
  return *this;
}

ON_2fVector& ON_2fVector::operator+=(const ON_2fVector& v)
{
  x += v.x;
  y += v.y;
  return *this;
}

ON_2fVector& ON_2fVector::operator-=(const ON_2fVector& v)
{
  x -= v.x;
  y -= v.y;
  return *this;
}

ON_2fVector ON_2fVector::operator*( int d ) const
{
  return ON_2fVector(x*d,y*d);
}

ON_2fVector ON_2fVector::operator*( float d ) const
{
  return ON_2fVector(x*d,y*d);
}

ON_2dVector ON_2fVector::operator*( double d ) const
{
  return ON_2dVector(x*d,y*d);
}

float ON_2fVector::operator*( const ON_2fVector& v ) const
{
  return (x*v.x + y*v.y);
}

float ON_2fVector::operator*( const ON_2fPoint& v ) const
{
  return (x*v.x + y*v.y);
}

double ON_2fVector::operator*( const ON_2dVector& v ) const
{
  return (x*v.x + y*v.y);
}

ON_2fVector ON_2fVector::operator/( int d ) const
{
  const float one_over_d = 1.0f/((float)d);
  return ON_2fVector(x*one_over_d,y*one_over_d);
}

ON_2fVector ON_2fVector::operator/( float d ) const
{
  const float one_over_d = 1.0f/d;
  return ON_2fVector(x*one_over_d,y*one_over_d);
}

ON_2dVector ON_2fVector::operator/( double d ) const
{
  const double one_over_d = 1.0/d;
  return ON_2dVector(x*one_over_d,y*one_over_d);
}

ON_2fVector ON_2fVector::operator+( const ON_2fVector& v ) const
{
  return ON_2fVector(x+v.x,y+v.y);
}

ON_2fPoint ON_2fVector::operator+( const ON_2fPoint& p ) const
{
  return ON_2fPoint(x+p.x,y+p.y);
}

ON_2fVector ON_2fVector::operator-( const ON_2fVector& v ) const
{
  return ON_2fVector(x-v.x,y-v.y);
}

ON_2fPoint ON_2fVector::operator-( const ON_2fPoint& v ) const
{
  return ON_2fPoint(x-v.x,y-v.y);
}

ON_3fVector ON_2fVector::operator+( const ON_3fVector& v ) const
{
  return ON_3fVector(x+v.x,y+v.y,v.z);
}

ON_3fPoint ON_2fVector::operator+( const ON_3fPoint& p ) const
{
  return ON_3fPoint(x+p.x,y+p.y,p.z);
}

ON_3fVector ON_2fVector::operator-( const ON_3fVector& v ) const
{
  return ON_3fVector(x-v.x,y-v.y,-v.z);
}

ON_3fPoint ON_2fVector::operator-( const ON_3fPoint& v ) const
{
  return ON_3fPoint(x-v.x,y-v.y,-v.z);
}

////


ON_2dVector ON_2fVector::operator+( const ON_2dVector& v ) const
{
  return ON_2dVector(x+v.x,y+v.y);
}

ON_2dPoint ON_2fVector::operator+( const ON_2dPoint& p ) const
{
  return ON_2dPoint(x+p.x,y+p.y);
}

ON_2dVector ON_2fVector::operator-( const ON_2dVector& v ) const
{
  return ON_2dVector(x-v.x,y-v.y);
}

ON_2dPoint ON_2fVector::operator-( const ON_2dPoint& v ) const
{
  return ON_2dPoint(x-v.x,y-v.y);
}

ON_3dVector ON_2fVector::operator+( const ON_3dVector& v ) const
{
  return ON_3dVector(x+v.x,y+v.y,v.z);
}

ON_3dPoint ON_2fVector::operator+( const ON_3dPoint& p ) const
{
  return ON_3dPoint(x+p.x,y+p.y,p.z);
}

ON_3dVector ON_2fVector::operator-( const ON_3dVector& v ) const
{
  return ON_3dVector(x-v.x,y-v.y,-v.z);
}

ON_3dPoint ON_2fVector::operator-( const ON_3dPoint& v ) const
{
  return ON_3dPoint(x-v.x,y-v.y,-v.z);
}

bool ON_2fVector::operator==( const ON_2fVector& v ) const
{
  return (x==v.x&&y==v.y)?true:false;
}

bool ON_2fVector::operator!=( const ON_2fVector& v ) const
{
  return Internal_NotEqualFloatArray(2, &x, &v.x);
}

bool ON_2fVector::operator<=( const ON_2fVector& v ) const
{
  // dictionary order
  return ((x<v.x)?true:((x==v.x&&y<=v.y)?true:false));
}

bool ON_2fVector::operator>=( const ON_2fVector& v ) const
{
  // dictionary order
  return ((x>v.x)?true:((x==v.x&&y>=v.y)?true:false));
}

bool ON_2fVector::operator<( const ON_2fVector& v ) const
{
  // dictionary order
  return ((x<v.x)?true:((x==v.x&&y<v.y)?true:false));
}

bool ON_2fVector::operator>( const ON_2fVector& v ) const
{
  // dictionary order
  return ((x>v.x)?true:((x==v.x&&y>v.y)?true:false));
}

float ON_2fVector::operator[](int i) const
{
  return ((i<=0)?x:y);
}

float& ON_2fVector::operator[](int i)
{
  float* pd = (i<=0)? &x : &y;
  return *pd;
}

float ON_2fVector::operator[](unsigned int i) const
{
  return ((i<=0)?x:y);
}

float& ON_2fVector::operator[](unsigned int i)
{
  float* pd = (i<=0)? &x : &y;
  return *pd;
}

int ON_2fVector::MaximumCoordinateIndex() const
{
  return ( (fabs(y)>fabs(x)) ? 1 : 0 );
}

double ON_2fVector::MaximumCoordinate() const
{
  double c = fabs(x); if (fabs(y)>c) c=fabs(y);
  return c;
}

double ON_2fVector::LengthSquared() const
{
  return (x*x + y*y);
}

double ON_2fVector::Length() const
{
  return ON_Length2d((double)x,(double)y);
}

void ON_2fVector::Reverse()
{
  x = -x;
  y = -y;
}

bool ON_2fVector::Unitize()
{
  bool rc = false;
  // Since x,y are floats, d will not be denormalized and the
  // ON_DBL_MIN tests in ON_2dVector::Unitize() are not needed.
  double d = Length();
  if ( d > 0.0 ) 
  {
    double dx = (double)x;
    double dy = (double)y;
    x = (float)(dx/d);
    y = (float)(dy/d);
    rc = true;
  }
  return rc;
}

ON_2fVector ON_2fVector::UnitVector() const
{
  ON_2fVector u(*this);
  u.Unitize();
  return u;
}

bool ON_2fVector::IsUnitVector() const
{
  return (x != ON_UNSET_FLOAT && y != ON_UNSET_FLOAT && fabs(Length() - 1.0) <= 1.0e-5);
}

bool ON_3fVector::IsUnitVector() const
{
  return (x != ON_UNSET_FLOAT && y != ON_UNSET_FLOAT && z != ON_UNSET_FLOAT && fabs(Length() - 1.0) <= 1.0e-5);
}

bool ON_2fVector::IsTiny( double tiny_tol ) const
{
  return (fabs(x) <= tiny_tol && fabs(y) <= tiny_tol );
}

void ON_2fVector::Zero()
{
  x = y = 0.0;
}

bool ON_2fVector::IsZero() const
{
  return (x==0.0f && y==0.0f);
}

bool ON_2fVector::IsNotZero() const
{
  // the && (x != ON_UNSET_FLOAT && y != ON_UNSET_FLOAT) insures no coordinate is a Nan.
  return
    (x != 0.0f || y != 0.0f)
    && (x != ON_UNSET_FLOAT && y != ON_UNSET_FLOAT)
    && (x != ON_UNSET_POSITIVE_FLOAT && y != ON_UNSET_POSITIVE_FLOAT);
}

// set this vector to be perpendicular to another vector
bool ON_2fVector::PerpendicularTo( // Result is not unitized. 
                      // returns false if input vector is zero
      const ON_2fVector& v
      )
{
  y = v.x;
  x = -v.y;
  return (x!= 0.0f || y!= 0.0f) ? true : false;
}

// set this vector to be perpendicular to a line defined by 2 points
bool ON_2fVector::PerpendicularTo( 
      const ON_2fPoint& p, 
      const ON_2fPoint& q
      )
{
  return PerpendicularTo(q-p);
}

ON_2fVector operator*(int d, const ON_2fVector& v)
{
  return ON_2fVector(d*v.x,d*v.y);
}

ON_2fVector operator*(float d, const ON_2fVector& v)
{
  return ON_2fVector(d*v.x,d*v.y);
}

ON_2dVector operator*(double d, const ON_2fVector& v)
{
  return ON_2dVector(d*v.x,d*v.y);
}

float ON_DotProduct( const ON_2fVector& a , const ON_2fVector& b )
{
  // inner (dot) product between 3d vectors
  return (a.x*b.x + a.y*b.y );
}

ON_3fVector ON_CrossProduct( const ON_2fVector& a , const ON_2fVector& b )
{
  return ON_3fVector(0.0, 0.0, a.x*b.y - b.x*a.y );
}

////////////////////////////////////////////////////////////////
//
// ON_3fVector
//

// static
const ON_3fVector& ON_3fVector::UnitVector(int index)
{
  static ON_3fVector o(0.0,0.0,0.0);
  static ON_3fVector x(1.0,0.0,0.0);
  static ON_3fVector y(0.0,1.0,0.0);
  static ON_3fVector z(0.0,0.0,1.0);
  switch(index)
  {
  case 0:
    return x;
  case 1:
    return y;
  case 2:
    return z;
  }
  return o;
}

ON_3fVector::ON_3fVector( const double* v )
{
  if (v) {
    x = (float)v[0]; y = (float)v[1]; z = (float)v[2];
  }
  else {
    x = y = z = 0.0;
  }
}

ON_3fVector::ON_3fVector( const float* v )
{
  if (v) {
    x = v[0]; y = v[1]; z = v[2];
  }
  else {
    x = y = z = 0.0;
  }
}

ON_3fVector::ON_3fVector(float xx,float yy,float zz)
{x=xx;y=yy;z=zz;}

ON_3fVector::ON_3fVector(const ON_2fVector& v)
{x=v.x;y=v.y;z=0.0f;}

ON_3fVector::ON_3fVector(const ON_2fPoint& p)
{x=p.x;y=p.y;z=0.0f;}

ON_3fVector::ON_3fVector(const ON_3fPoint& p)
{x=p.x;y=p.y;z=p.z;}

ON_3fVector::ON_3fVector(const ON_2dVector& v)
{x=(float)v.x;y=(float)v.y;z=(float)0.0f;}

ON_3fVector::ON_3fVector(const ON_3dVector& v)
{x=(float)v.x;y=(float)v.y;z=(float)v.z;}

ON_3fVector::ON_3fVector(const ON_2dPoint& p)
{x=(float)p.x;y=(float)p.y;z=(float)0.0f;}

ON_3fVector::ON_3fVector(const ON_3dPoint& p)
{x=(float)p.x;y=(float)p.y;z=(float)p.z;}

ON_3fVector::operator float*()
{
  return &x;
}

ON_3fVector::operator const float*() const
{
  return &x;
}

ON_3fVector& ON_3fVector::operator=(const double* v)
{
  if ( v ) {
    x = (float)v[0];
    y = (float)v[1];
    z = (float)v[2];
  }
  else {
    x = y = z = 0.0;
  }
  return *this;
}

ON_3fVector& ON_3fVector::operator=(const float* v)
{
  if ( v ) {
    x = v[0];
    y = v[1];
    z = v[2];
  }
  else {
    x = y = z = 0.0;
  }
  return *this;
}

ON_3fVector& ON_3fVector::operator=(const ON_2fVector& v)
{
  x = v.x;
  y = v.y;
  z = 0.0;
  return *this;
}

ON_3fVector& ON_3fVector::operator=(const ON_2fPoint& p)
{
  x = p.x;
  y = p.y;
  z = 0.0f;
  return *this;
}

ON_3fVector& ON_3fVector::operator=(const ON_3fPoint& p)
{
  x = p.x;
  y = p.y;
  z = p.z;
  return *this;
}


ON_3fVector& ON_3fVector::operator=(const ON_2dVector& v)
{
  x = (float)v.x;
  y = (float)v.y;
  z = 0.0f;
  return *this;
}

ON_3fVector& ON_3fVector::operator=(const ON_3dVector& v)
{
  x = (float)v.x;
  y = (float)v.y;
  z = (float)v.z;
  return *this;
}

ON_3fVector& ON_3fVector::operator=(const ON_2dPoint& p)
{
  x = (float)p.x;
  y = (float)p.y;
  z = 0.0f;
  return *this;
}

ON_3fVector& ON_3fVector::operator=(const ON_3dPoint& p)
{
  x = (float)p.x;
  y = (float)p.y;
  z = (float)p.z;
  return *this;
}

ON_3fVector ON_3fVector::operator-() const
{
  return ON_3fVector(-x,-y,-z);
}

ON_3fVector& ON_3fVector::operator*=(float d)
{
  x *= d;
  y *= d;
  z *= d;
  return *this;
}

ON_3fVector& ON_3fVector::operator/=(float d)
{
  const float one_over_d = 1.0f/d;
  x *= one_over_d;
  y *= one_over_d;
  z *= one_over_d;
  return *this;
}

ON_3fVector& ON_3fVector::operator+=(const ON_3fVector& v)
{
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

ON_3fVector& ON_3fVector::operator-=(const ON_3fVector& v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

ON_3fVector ON_3fVector::operator*( int d ) const
{
  return ON_3fVector(x*d,y*d,z*d);
}

ON_3fVector ON_3fVector::operator*( float d ) const
{
  return ON_3fVector(x*d,y*d,z*d);
}

ON_3dVector ON_3fVector::operator*( double d ) const
{
  return ON_3dVector(x*d,y*d,z*d);
}

float ON_3fVector::operator*( const ON_3fVector& v ) const
{
  return (x*v.x + y*v.y + z*v.z);
}

float ON_3fVector::operator*( const ON_3fPoint& v ) const
{
  return (x*v.x + y*v.y + z*v.z);
}

double ON_3fVector::operator*( const ON_3dVector& v ) const
{
  return (x*v.x + y*v.y + z*v.z);
}

ON_3fVector ON_3fVector::operator/( int d ) const
{
  const float one_over_d = 1.0f/((int)d);
  return ON_3fVector(x*one_over_d,y*one_over_d,z*one_over_d);
}

ON_3fVector ON_3fVector::operator/( float d ) const
{
  const float one_over_d = 1.0f/d;
  return ON_3fVector(x*one_over_d,y*one_over_d,z*one_over_d);
}

ON_3dVector ON_3fVector::operator/( double d ) const
{
  const double one_over_d = 1.0/d;
  return ON_3dVector(x*one_over_d,y*one_over_d,z*one_over_d);
}

ON_3fVector ON_3fVector::operator+( const ON_3fVector& v ) const
{
  return ON_3fVector(x+v.x,y+v.y,z+v.z);
}

ON_3fPoint ON_3fVector::operator+( const ON_3fPoint& p ) const
{
  return ON_3fPoint(x+p.x,y+p.y,z+p.z);
}

ON_3fVector ON_3fVector::operator-( const ON_3fVector& v ) const
{
  return ON_3fVector(x-v.x,y-v.y,z-v.z);
}

ON_3fPoint ON_3fVector::operator-( const ON_3fPoint& v ) const
{
  return ON_3fPoint(x-v.x,y-v.y,z-v.z);
}

ON_3fVector ON_3fVector::operator+( const ON_2fVector& v ) const
{
  return ON_3fVector(x+v.x,y+v.y,z);
}

ON_3fPoint ON_3fVector::operator+( const ON_2fPoint& p ) const
{
  return ON_3fPoint(x+p.x,y+p.y,z);
}

ON_3fVector ON_3fVector::operator-( const ON_2fVector& v ) const
{
  return ON_3fVector(x-v.x,y-v.y,z);
}

ON_3fPoint ON_3fVector::operator-( const ON_2fPoint& v ) const
{
  return ON_3fPoint(x-v.x,y-v.y,z);
}

/////


ON_3dVector ON_3fVector::operator+( const ON_3dVector& v ) const
{
  return ON_3dVector(x+v.x,y+v.y,z+v.z);
}

ON_3dPoint ON_3fVector::operator+( const ON_3dPoint& p ) const
{
  return ON_3dPoint(x+p.x,y+p.y,z+p.z);
}

ON_3dVector ON_3fVector::operator-( const ON_3dVector& v ) const
{
  return ON_3dVector(x-v.x,y-v.y,z-v.z);
}

ON_3dPoint ON_3fVector::operator-( const ON_3dPoint& v ) const
{
  return ON_3dPoint(x-v.x,y-v.y,z-v.z);
}

ON_3dVector ON_3fVector::operator+( const ON_2dVector& v ) const
{
  return ON_3dVector(x+v.x,y+v.y,z);
}

ON_3dPoint ON_3fVector::operator+( const ON_2dPoint& p ) const
{
  return ON_3dPoint(x+p.x,y+p.y,z);
}

ON_3dVector ON_3fVector::operator-( const ON_2dVector& v ) const
{
  return ON_3dVector(x-v.x,y-v.y,z);
}

ON_3dPoint ON_3fVector::operator-( const ON_2dPoint& v ) const
{
  return ON_3dPoint(x-v.x,y-v.y,z);
}

bool ON_3fVector::operator==( const ON_3fVector& v ) const
{
  return (x==v.x&&y==v.y&&z==v.z)?true:false;
}

bool ON_3fVector::operator!=( const ON_3fVector& v ) const
{
  return Internal_NotEqualFloatArray(3, &x, &v.x);
}

bool ON_3fVector::operator<=( const ON_3fVector& v ) const
{
  // dictionary order
  return ((x<v.x)?true:((x==v.x)?((y<v.y)?true:(y==v.y&&z<=v.z)?true:false):false));
}

bool ON_3fVector::operator>=( const ON_3fVector& v ) const
{
  // dictionary order
  return ((x>v.x)?true:((x==v.x)?((y>v.y)?true:(y==v.y&&z>=v.z)?true:false):false));
}

bool ON_3fVector::operator<( const ON_3fVector& v ) const
{
  // dictionary order
  return ((x<v.x)?true:((x==v.x)?((y<v.y)?true:(y==v.y&&z<v.z)?true:false):false));
}

bool ON_3fVector::operator>( const ON_3fVector& v ) const
{
  // dictionary order
  return ((x>v.x)?true:((x==v.x)?((y>v.y)?true:(y==v.y&&z>v.z)?true:false):false));
}

float ON_3fVector::operator[](int i) const
{
  return ( (i<=0)?x:((i>=2)?z:y) );
}

float& ON_3fVector::operator[](int i)
{
  float* pd = (i<=0)? &x : ( (i>=2) ?  &z : &y);
  return *pd;
}

float ON_3fVector::operator[](unsigned int i) const
{
  return ( (i<=0)?x:((i>=2)?z:y) );
}

float& ON_3fVector::operator[](unsigned int i)
{
  float* pd = (i<=0)? &x : ( (i>=2) ?  &z : &y);
  return *pd;
}

int ON_3fVector::MaximumCoordinateIndex() const
{
  return (fabs(y)>fabs(x)) ? ((fabs(z)>fabs(y))?2:1) : ((fabs(z)>fabs(x))?2:0);
}

double ON_3fVector::MaximumCoordinate() const
{
  double c = fabs(x); if (fabs(y)>c) c=fabs(y); if (fabs(z)>c) c=fabs(z);
  return c;
}

double ON_3fVector::LengthSquared() const
{
  return (x*x + y*y + z*z);
}

double ON_3fVector::Length() const
{
  return ON_Length3d((double)x,(double)y,(double)z);
}

void ON_3fVector::Reverse()
{
  x = -x;
  y = -y;
  z = -z;
}

bool ON_3fVector::Unitize()
{
  bool rc = false;
  // Since x,y,z are floats, d will not be denormalized and the
  // ON_DBL_MIN tests in ON_2dVector::Unitize() are not needed.
  double d = Length();
  if ( d > 0.0 ) 
  {
    double dx = x;
    double dy = y;
    double dz = z;
    x = (float)(dx/d);
    y = (float)(dy/d);
    z = (float)(dz/d);
    rc = true;
  }
  return rc;
}

ON_3fVector ON_3fVector::UnitVector() const
{
  ON_3fVector u(*this);
  u.Unitize();
  return u;
}

bool ON_3fVector::IsTiny( double tiny_tol ) const
{
  return (fabs(x) <= tiny_tol && fabs(y) <= tiny_tol && fabs(z) <= tiny_tol );
}

void ON_3fVector::Zero()
{
  x = y = z = 0.0;
}

bool ON_3fVector::IsZero() const
{
  return (x==0.0f && y==0.0f && z==0.0f);
}

bool ON_3fVector::IsNotZero() const
{
  // the && (x != ON_UNSET_FLOAT && y != ON_UNSET_FLOAT && z != ON_UNSET_FLOAT) insures no coordinate is a Nan.
  return
    (x != 0.0f || y != 0.0f || z != 0.0f) 
    && (x != ON_UNSET_FLOAT && y != ON_UNSET_FLOAT && z != ON_UNSET_FLOAT)
    && (x != ON_UNSET_POSITIVE_FLOAT && y != ON_UNSET_POSITIVE_FLOAT && z != ON_UNSET_POSITIVE_FLOAT);
}

ON_3fVector operator*(int d, const ON_3fVector& v)
{
  return ON_3fVector(d*v.x,d*v.y,d*v.z);
}

ON_3fVector operator*(float d, const ON_3fVector& v)
{
  return ON_3fVector(d*v.x,d*v.y,d*v.z);
}

ON_3dVector operator*(double d, const ON_3fVector& v)
{
  return ON_3dVector(d*v.x,d*v.y,d*v.z);
}

float ON_DotProduct( const ON_3fVector& a , const ON_3fVector& b )
{
  // inner (dot) product between 3d vectors
  return (a.x*b.x + a.y*b.y + a.z*b.z);
}

ON_3fVector ON_CrossProduct( const ON_3fVector& a , const ON_3fVector& b )
{
  return ON_3fVector(a.y*b.z - b.y*a.z, a.z*b.x - b.z*a.x, a.x*b.y - b.x*a.y );
}

ON_3fVector ON_CrossProduct( const float* a, const float* b )
{
  return ON_3fVector(a[1]*b[2] - b[1]*a[2], a[2]*b[0] - b[2]*a[0], a[0]*b[1] - b[0]*a[1] );
}

float ON_TripleProduct( const ON_3fVector& a, const ON_3fVector& b, const ON_3fVector& c )
{
  // = a o (b x c )
  return (a.x*(b.y*c.z - b.z*c.y) + a.y*(b.z*c.x - b.x*c.z) + a.z*(b.x*c.y - b.y*c.x));
}

float ON_TripleProduct( const float* a, const float* b, const float* c )
{
  // = a o (b x c )
  return (a[0]*(b[1]*c[2] - b[2]*c[1]) + a[1]*(b[2]*c[0] - b[0]*c[2]) + a[2]*(b[0]*c[1] - b[1]*c[0]));
}

////////////////////////////////////////////////////////////////
//
// ON_2dPoint
//


bool ON_2dPoint::IsCoincident(const ON_2dPoint& p) const
{
  return ON_PointsAreCoincident(2, false, *this, p);
}

ON_2dPoint::ON_2dPoint( const float* p )
{
  if (p) {
    x = (double)p[0]; y = (double)p[1];
  }
  else {
    x = y = 0.0;
  }
}

ON_2dPoint::ON_2dPoint( const double* p )
{
  if (p) {
    x = p[0]; y = p[1];
  }
  else {
    x = y = 0.0;
  }
}

ON_2dPoint::ON_2dPoint(double xx,double yy)
{x=xx;y=yy;}

ON_2dPoint::ON_2dPoint(const ON_3dPoint& p)
{x=p.x;y=p.y;}

ON_2dPoint::ON_2dPoint(const ON_4dPoint& h)
{
  x=h.x;y=h.y;
  const double w = (h.w != 1.0 && h.w != 0.0) ? 1.0/h.w : 1.0;
  x *= w;
  y *= w;
}

ON_2dPoint::ON_2dPoint(const ON_2dVector& v)
{x=v.x;y=v.y;}

ON_2dPoint::ON_2dPoint(const ON_3dVector& v)
{x=v.x;y=v.y;}

ON_2dPoint::ON_2dPoint(const ON_2fPoint& p)
{x=p.x;y=p.y;}

ON_2dPoint::ON_2dPoint(const ON_3fPoint& p)
{x=p.x;y=p.y;}

ON_2dPoint::ON_2dPoint(const ON_4fPoint& h)
{
  const double w = (h.w != 1.0f && h.w != 0.0f) ? 1.0/((double)h.w) : 1.0;
  x *= w*h.x;
  y *= w*h.y;
}

ON_2dPoint::ON_2dPoint(const ON_2fVector& v)
{x=v.x;y=v.y;}

ON_2dPoint::ON_2dPoint(const ON_3fVector& v)
{x=v.x;y=v.y;}

ON_2dPoint::operator double*()
{
  return &x;
}

ON_2dPoint::operator const double*() const
{
  return &x;
}

ON_2dPoint& ON_2dPoint::operator=(const float* p)
{
  if ( p ) {
    x = (double)p[0];
    y = (double)p[1];
  }
  else {
    x = y = 0.0;
  }
  return *this;
}

ON_2dPoint& ON_2dPoint::operator=(const double* p)
{
  if ( p ) {
    x = p[0];
    y = p[1];
  }
  else {
    x = y = 0.0;
  }
  return *this;
}

ON_2dPoint& ON_2dPoint::operator=(const ON_3dPoint& p)
{
  x = p.x;
  y = p.y;
  return *this;
}

ON_2dPoint& ON_2dPoint::operator=(const ON_4dPoint& h)
{
  const double w = (h.w != 1.0 && h.w != 0.0) ? 1.0/h.w : 1.0;
  x = w*h.x;
  y = w*h.y;
  return *this;
}

ON_2dPoint& ON_2dPoint::operator=(const ON_2dVector& v)
{
  x = v.x;
  y = v.y;
  return *this;
}

ON_2dPoint& ON_2dPoint::operator=(const ON_3dVector& v)
{
  x = v.x;
  y = v.y;
  return *this;
}

ON_2dPoint& ON_2dPoint::operator=(const ON_2fPoint& p)
{
  x = p.x;
  y = p.y;
  return *this;
}

ON_2dPoint& ON_2dPoint::operator=(const ON_3fPoint& p)
{
  x = p.x;
  y = p.y;
  return *this;
}

ON_2dPoint& ON_2dPoint::operator=(const ON_4fPoint& h)
{
  const double w = (h.w != 1.0f && h.w != 0.0f) ? 1.0/((double)h.w) : 1.0;
  x = w*h.x;
  y = w*h.y;
  return *this;
}

ON_2dPoint& ON_2dPoint::operator=(const ON_2fVector& v)
{
  x = v.x;
  y = v.y;
  return *this;
}

ON_2dPoint& ON_2dPoint::operator=(const ON_3fVector& v)
{
  x = v.x;
  y = v.y;
  y = v.z;
  return *this;
}

ON_2dPoint& ON_2dPoint::operator*=(double d)
{
  x *= d;
  y *= d;
  return *this;
}

ON_2dPoint& ON_2dPoint::operator/=(double d)
{
  const double one_over_d = 1.0/d;
  x *= one_over_d;
  y *= one_over_d;
  return *this;
}

ON_2dPoint& ON_2dPoint::operator+=(const ON_2dVector& v)
{
  x += v.x;
  y += v.y;
  return *this;
}

ON_2dPoint& ON_2dPoint::operator-=(const ON_2dVector& v)
{
  x -= v.x;
  y -= v.y;
  return *this;
}

ON_2dPoint ON_2dPoint::operator*( int i ) const
{
  double d = i;
  return ON_2dPoint(x*d,y*d);
}

ON_2dPoint ON_2dPoint::operator*( float f ) const
{
  double d = f;
  return ON_2dPoint(x*d,y*d);
}

ON_2dPoint ON_2dPoint::operator*( double d ) const
{
  return ON_2dPoint(x*d,y*d);
}

ON_2dPoint ON_2dPoint::operator/( int i ) const
{
  const double one_over_d = 1.0/((double)i);
  return ON_2dPoint(x*one_over_d,y*one_over_d);
}

ON_2dPoint ON_2dPoint::operator/( float f ) const
{
  const double one_over_d = 1.0/((double)f);
  return ON_2dPoint(x*one_over_d,y*one_over_d);
}

ON_2dPoint ON_2dPoint::operator/( double d ) const
{
  const double one_over_d = 1.0/d;
  return ON_2dPoint(x*one_over_d,y*one_over_d);
}

ON_2dPoint ON_2dPoint::operator+( const ON_2dPoint& p ) const
{
  return ON_2dPoint(x+p.x,y+p.y);
}

ON_2dPoint ON_2dPoint::operator+( const ON_2dVector& v ) const
{
  return ON_2dPoint(x+v.x,y+v.y);
}

ON_2dVector ON_2dPoint::operator-( const ON_2dPoint& p ) const
{
  return ON_2dVector(x-p.x,y-p.y);
}

ON_2dPoint ON_2dPoint::operator-( const ON_2dVector& v ) const
{
  return ON_2dPoint(x-v.x,y-v.y);
}


ON_3dPoint ON_2dPoint::operator+( const ON_3dPoint& p ) const
{
  return ON_3dPoint(x+p.x,y+p.y,p.z);
}

ON_3dPoint ON_2dPoint::operator+( const ON_3dVector& v ) const
{
  return ON_3dPoint(x+v.x,y+v.y,v.z);
}

ON_3dVector ON_2dPoint::operator-( const ON_3dPoint& p ) const
{
  return ON_3dVector(x-p.x,y-p.y,-p.z);
}

ON_3dPoint ON_2dPoint::operator-( const ON_3dVector& v ) const
{
  return ON_3dPoint(x-v.x,y-v.y,-v.z);
}

///////////////////////////////////////////////////


ON_2dPoint ON_2dPoint::operator+( const ON_2fPoint& p ) const
{
  return ON_2dPoint(x+p.x,y+p.y);
}

ON_2dPoint ON_2dPoint::operator+( const ON_2fVector& v ) const
{
  return ON_2dPoint(x+v.x,y+v.y);
}

ON_2dVector ON_2dPoint::operator-( const ON_2fPoint& p ) const
{
  return ON_2dVector(x-p.x,y-p.y);
}

ON_2dPoint ON_2dPoint::operator-( const ON_2fVector& v ) const
{
  return ON_2dPoint(x-v.x,y-v.y);
}


ON_3dPoint ON_2dPoint::operator+( const ON_3fPoint& p ) const
{
  return ON_3dPoint(x+p.x,y+p.y,p.z);
}

ON_3dPoint ON_2dPoint::operator+( const ON_3fVector& v ) const
{
  return ON_3dPoint(x+v.x,y+v.y,v.z);
}

ON_3dVector ON_2dPoint::operator-( const ON_3fPoint& p ) const
{
  return ON_3dVector(x-p.x,y-p.y,-p.z);
}

ON_3dPoint ON_2dPoint::operator-( const ON_3fVector& v ) const
{
  return ON_3dPoint(x-v.x,y-v.y,-v.z);
}


double ON_2dPoint::operator*(const ON_2dPoint& h) const
{
  return x*h.x + y*h.y;
}

double ON_2dPoint::operator*(const ON_2dVector& h) const
{
  return x*h.x + y*h.y;
}

bool ON_2dPoint::operator==( const ON_2dPoint& p ) const
{
  return (x==p.x&&y==p.y)?true:false;
}

bool ON_2dPoint::operator!=( const ON_2dPoint& p ) const
{
  return Internal_NotEqualDoubleArray(2, &x, &p.x);
}

bool ON_2dPoint::operator<=( const ON_2dPoint& p ) const
{
  // dictionary order
  return ( (x<p.x) ? true : ((x==p.x&&y<=p.y)?true:false) );
}

bool ON_2dPoint::operator>=( const ON_2dPoint& p ) const
{
  // dictionary order
  return ( (x>p.x) ? true : ((x==p.x&&y>=p.y)?true:false) );
}

bool ON_2dPoint::operator<( const ON_2dPoint& p ) const
{
  // dictionary order
  return ( (x<p.x) ? true : ((x==p.x&&y<p.y)?true:false) );
}

bool ON_2dPoint::operator>( const ON_2dPoint& p ) const
{
  // dictionary order
  return ( (x>p.x) ? true : ((x==p.x&&y>p.y)?true:false) );
}

double ON_2dPoint::operator[](int i) const
{
  return (i<=0) ? x : y;
}

double& ON_2dPoint::operator[](int i)
{
  double* pd = (i<=0)? &x : &y;
  return *pd;
}

double ON_2dPoint::operator[](unsigned int i) const
{
  return (i<=0) ? x : y;
}

double& ON_2dPoint::operator[](unsigned int i)
{
  double* pd = (i<=0)? &x : &y;
  return *pd;
}

double ON_2dPoint::DistanceTo( const ON_2dPoint& p ) const
{
  return ON_Length2d(p.x-x,p.y-y);
}

double ON_2dPoint::DistanceToSquared(const ON_2dPoint& p) const
{
  return ON_Length2dSquared(p.x - x, p.y - y);
}

int ON_2dPoint::MaximumCoordinateIndex() const
{
  return (fabs(y)>fabs(x)) ? 1 : 0;
}

double ON_2dPoint::MaximumCoordinate() const
{
  double c = fabs(x); if (fabs(y)>c) c=fabs(y);
  return c;
}

int ON_2dPoint::MinimumCoordinateIndex() const
{
  return (fabs(y)<fabs(x)) ? 1 : 0;
}

double ON_2dPoint::MinimumCoordinate() const
{
  double c = fabs(x); if (fabs(y)<c) c=fabs(y);
  return c;
}

void ON_2dPoint::Zero()
{
  x = y = 0.0;
}

bool ON_2dPoint::IsZero() const
{
  return (x==0.0 && y==0.0);
}

bool ON_2dPoint::IsNotZero() const
{
  // the && (x != ON_UNSET_VALUE && y != ON_UNSET_VALUE) insures no coordinate is a Nan.
  return
    (x != 0.0 || y != 0.0) 
    && (x != ON_UNSET_VALUE && y != ON_UNSET_VALUE)
    && (x != ON_UNSET_POSITIVE_VALUE && y != ON_UNSET_POSITIVE_VALUE)
    ;
}

ON_2dPoint operator*(int i, const ON_2dPoint& p)
{
  double d = i;
  return ON_2dPoint(d*p.x,d*p.y);
}

ON_2dPoint operator*(float f, const ON_2dPoint& p)
{
  double d = f;
  return ON_2dPoint(d*p.x,d*p.y);
}

ON_2dPoint operator*(double d, const ON_2dPoint& p)
{
  return ON_2dPoint(d*p.x,d*p.y);
}

////////////////////////////////////////////////////////////////
//
// ON_3dPoint
//

ON_3dPoint::ON_3dPoint( const float* p )
{
  if (p) {
    x = (double)p[0]; y = (double)p[1]; z = (double)p[2];
  }
  else {
    x = y = z = 0.0;
  }
}

ON_3dPoint::ON_3dPoint(const ON_2fPoint& p)
{x=(double)p.x;y=(double)p.y;z=0.0;}

ON_3dPoint::ON_3dPoint(const ON_3fPoint& p)
{x=(double)p.x;y=(double)p.y;z=(double)p.z;}

ON_3dPoint::ON_3dPoint(const ON_4fPoint& p)
{
  const double w = (p.w != 1.0f && p.w != 0.0f) ? 1.0/((double)p.w) : 1.0;
  x = w*((double)p.x);
  y = w*((double)p.y);
  z = w*((double)p.z);
}

ON_3dPoint::ON_3dPoint(const ON_2fVector& p)
{x=(double)p.x;y=(double)p.y;z=0.0;}

ON_3dPoint::ON_3dPoint(const ON_3fVector& p)
{x=(double)p.x;y=(double)p.y;z=(double)p.z;}

ON_3dPoint::ON_3dPoint( const double* p )
{
  if (p) {
    x = p[0]; y = p[1]; z = p[2];
  }
  else {
    x = y = z = 0.0;
  }
}

ON_3dPoint::ON_3dPoint(double xx,double yy,double zz)
{x=xx;y=yy;z=zz;}

ON_3dPoint::ON_3dPoint(const ON_2dPoint& p)
{x=p.x;y=p.y;z=0.0;}

ON_3dPoint::ON_3dPoint(const ON_4dPoint& p)
{
  x=p.x;y=p.y;z=p.z;
  const double w = (p.w != 1.0 && p.w != 0.0) ? 1.0/p.w : 1.0;
  x *= w;
  y *= w;
  z *= w;
}

ON_3dPoint::ON_3dPoint(const ON_2dVector& v)
{x=v.x;y=v.y;z=0.0;}

ON_3dPoint::ON_3dPoint(const ON_3dVector& v)
{x=v.x;y=v.y;z=v.z;}

ON_3dPoint::operator double*()
{
  return &x;
}

ON_3dPoint::operator const double*() const
{
  return &x;
}

ON_3dPoint& ON_3dPoint::operator=(const float* p)
{
  if ( p ) {
    x = (double)p[0];
    y = (double)p[1];
    z = (double)p[2];
  }
  else {
    x = y = z = 0.0;
  }
  return *this;
}

ON_3dPoint& ON_3dPoint::operator=(const double* p)
{
  if ( p ) {
    x = p[0];
    y = p[1];
    z = p[2];
  }
  else {
    x = y = z = 0.0;
  }
  return *this;
}

ON_3dPoint& ON_3dPoint::operator=(const ON_2dPoint& p)
{
  x = p.x;
  y = p.y;
  z = 0.0;
  return *this;
}

ON_3dPoint& ON_3dPoint::operator=(const ON_4dPoint& p)
{
  const double w = (p.w != 1.0 && p.w != 0.0) ? 1.0/p.w : 1.0;
  x = w*p.x;
  y = w*p.y;
  z = w*p.z;
  return *this;
}

ON_3dPoint& ON_3dPoint::operator=(const ON_2dVector& v)
{
  x = v.x;
  y = v.y;
  z = 0.0;
  return *this;
}

ON_3dPoint& ON_3dPoint::operator=(const ON_3dVector& v)
{
  x = v.x;
  y = v.y;
  z = v.z;
  return *this;
}

ON_3dPoint& ON_3dPoint::operator=(const ON_2fPoint& p)
{
  x = (double)p.x;
  y = (double)p.y;
  z = (double)0.0;
  return *this;
}

ON_3dPoint& ON_3dPoint::operator=(const ON_3fPoint& p)
{
  x = (double)p.x;
  y = (double)p.y;
  z = (double)p.z;
  return *this;
}

ON_3dPoint& ON_3dPoint::operator=(const ON_4fPoint& p)
{
  const double w = (p.w != 1.0f && p.w != 0.0f) ? 1.0/((double)p.w) : 1.0;
  x = w*((double)p.x);
  y = w*((double)p.y);
  z = w*((double)p.z);
  return *this;
}

ON_3dPoint& ON_3dPoint::operator=(const ON_2fVector& v)
{
  x = v.x;
  y = v.y;
  z = 0.0;
  return *this;
}

ON_3dPoint& ON_3dPoint::operator=(const ON_3fVector& v)
{
  x = v.x;
  y = v.y;
  z = v.z;
  return *this;
}


ON_3dPoint& ON_3dPoint::operator*=(double d)
{
  x *= d;
  y *= d;
  z *= d;
  return *this;
}

ON_3dPoint& ON_3dPoint::operator/=(double d)
{
  const double one_over_d = 1.0/d;
  x *= one_over_d;
  y *= one_over_d;
  z *= one_over_d;
  return *this;
}

ON_3dPoint& ON_3dPoint::operator+=(const ON_3dVector& v)
{
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

ON_3dPoint& ON_3dPoint::operator-=(const ON_3dVector& v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

ON_3dPoint ON_3dPoint::operator*( int i ) const
{
  double d = i;
  return ON_3dPoint(x*d,y*d,z*d);
}

ON_3dPoint ON_3dPoint::operator*( float f ) const
{
  double d = f;
  return ON_3dPoint(x*d,y*d,z*d);
}

ON_3dPoint ON_3dPoint::operator*( double d ) const
{
  return ON_3dPoint(x*d,y*d,z*d);
}

ON_3dPoint ON_3dPoint::operator/( int i ) const
{
  const double one_over_d = 1.0/((double)i);
  return ON_3dPoint(x*one_over_d,y*one_over_d,z*one_over_d);
}

ON_3dPoint ON_3dPoint::operator/( float f ) const
{
  const double one_over_d = 1.0/((double)f);
  return ON_3dPoint(x*one_over_d,y*one_over_d,z*one_over_d);
}

ON_3dPoint ON_3dPoint::operator/( double d ) const
{
  const double one_over_d = 1.0/d;
  return ON_3dPoint(x*one_over_d,y*one_over_d,z*one_over_d);
}

ON_3dPoint ON_3dPoint::operator+( const ON_3dPoint& p ) const
{
  return ON_3dPoint(x+p.x,y+p.y,z+p.z);
}

ON_3dPoint ON_3dPoint::operator+( const ON_3dVector& v ) const
{
  return ON_3dPoint(x+v.x,y+v.y,z+v.z);
}

ON_3dVector ON_3dPoint::operator-( const ON_3dPoint& p ) const
{
  return ON_3dVector(x-p.x,y-p.y,z-p.z);
}

ON_3dPoint ON_3dPoint::operator-( const ON_3dVector& v ) const
{
  return ON_3dPoint(x-v.x,y-v.y,z-v.z);
}

ON_3dPoint ON_3dPoint::operator+( const ON_2dPoint& p ) const
{
  return ON_3dPoint(x+p.x,y+p.y,z);
}

ON_3dPoint ON_3dPoint::operator+( const ON_2dVector& v ) const
{
  return ON_3dPoint(x+v.x,y+v.y,z);
}

ON_3dVector ON_3dPoint::operator-( const ON_2dPoint& p ) const
{
  return ON_3dVector(x-p.x,y-p.y,z);
}

ON_3dPoint ON_3dPoint::operator-( const ON_2dVector& v ) const
{
  return ON_3dPoint(x-v.x,y-v.y,z);
}

ON_3dPoint ON_3dPoint::operator+( const ON_3fPoint& p ) const
{
  return ON_3dPoint(x+p.x,y+p.y,z+p.z);
}

ON_3dPoint ON_3dPoint::operator+( const ON_3fVector& v ) const
{
  return ON_3dPoint(x+v.x,y+v.y,z+v.z);
}

ON_3dVector ON_3dPoint::operator-( const ON_3fPoint& p ) const
{
  return ON_3dVector(x-p.x,y-p.y,z-p.z);
}

ON_3dPoint ON_3dPoint::operator-( const ON_3fVector& v ) const
{
  return ON_3dPoint(x-v.x,y-v.y,z-v.z);
}

ON_3dPoint ON_3dPoint::operator+( const ON_2fPoint& p ) const
{
  return ON_3dPoint(x+p.x,y+p.y,z);
}

ON_3dPoint ON_3dPoint::operator+( const ON_2fVector& v ) const
{
  return ON_3dPoint(x+v.x,y+v.y,z);
}

ON_3dVector ON_3dPoint::operator-( const ON_2fPoint& p ) const
{
  return ON_3dVector(x-p.x,y-p.y,z);
}

ON_3dPoint ON_3dPoint::operator-( const ON_2fVector& v ) const
{
  return ON_3dPoint(x-v.x,y-v.y,z);
}

double ON_3dPoint::operator*(const ON_3dPoint& h) const
{
  return x*h.x + y*h.y + z*h.z;
}

double ON_3dPoint::operator*(const ON_3dVector& h) const
{
  return x*h.x + y*h.y + z*h.z;
}

bool operator==(const ON_3dPoint& a, const ON_3dPoint& b)
{
  // Properly handles nans.
  return (a.x==b.x && a.y==b.y && a.z==b.z);
}

bool operator!=(const ON_3dPoint& a, const ON_3dPoint& b)
{
  // Properly handles nans.
  return (a.x!=b.x || a.y!=b.y || a.z!=b.z);
}

bool ON_3dPoint::operator<=( const ON_3dPoint& p ) const
{
  // dictionary order
  return ((x<p.x)?true:((x==p.x)?((y<p.y)?true:(y==p.y&&z<=p.z)?true:false):false));
}

bool ON_3dPoint::operator>=( const ON_3dPoint& p ) const
{
  // dictionary order
  return ((x>p.x)?true:((x==p.x)?((y>p.y)?true:(y==p.y&&z>=p.z)?true:false):false));
}

bool ON_3dPoint::operator<( const ON_3dPoint& p ) const
{
  // dictionary order
  return ((x<p.x)?true:((x==p.x)?((y<p.y)?true:(y==p.y&&z<p.z)?true:false):false));
}

bool ON_3dPoint::operator>( const ON_3dPoint& p ) const
{
  // dictionary order
  return ((x>p.x)?true:((x==p.x)?((y>p.y)?true:(y==p.y&&z>p.z)?true:false):false));
}

double ON_3dPoint::operator[](int i) const
{
  return ( (i<=0)?x:((i>=2)?z:y) );
}

double& ON_3dPoint::operator[](int i)
{
  double* pd = (i<=0)? &x : ( (i>=2) ?  &z : &y);
  return *pd;
}

double ON_3dPoint::operator[](unsigned int i) const
{
  return ( (i<=0)?x:((i>=2)?z:y) );
}

double& ON_3dPoint::operator[](unsigned int i)
{
  double* pd = (i<=0)? &x : ( (i>=2) ?  &z : &y);
  return *pd;
}

double ON_3dPoint::DistanceTo( const ON_3dPoint& p ) const
{
  return ON_Length3d(p.x-x,p.y-y,p.z-z);
}

double ON_3dPoint::DistanceToSquared(const ON_3dPoint& p) const
{
  return ON_Length3dSquared(p.x - x, p.y - y, p.z - z);
}

int ON_3dPoint::MaximumCoordinateIndex() const
{
  return (fabs(y)>fabs(x)) ? ((fabs(z)>fabs(y))?2:1) : ((fabs(z)>fabs(x))?2:0);
}

double ON_3dPoint::MaximumCoordinate() const
{
  double c = fabs(x); if (fabs(y)>c) c=fabs(y); if (fabs(z)>c) c=fabs(z);
  return c;
}

int ON_3dPoint::MinimumCoordinateIndex() const
{
  return (fabs(y)<fabs(x)) ? ((fabs(z)<fabs(y))?2:1) : ((fabs(z)<fabs(x))?2:0);
}

double ON_3dPoint::MinimumCoordinate() const
{
  double c = fabs(x); if (fabs(y)<c) c=fabs(y); if (fabs(z)<c) c=fabs(z);
  return c;
}

void ON_3dPoint::Zero()
{
  x = y = z = 0.0;
}

bool ON_3dPoint::IsZero() const
{
  return x == 0.0 && y == 0.0 && z == 0.0;
}

bool ON_3dPoint::IsNotZero() const
{
  // the && (x != ON_UNSET_VALUE && y != ON_UNSET_VALUE && z != ON_UNSET_VALUE) insures no coordinate is a Nan.
  return
    (x != 0.0 || y != 0.0 || z != 0.0)
    && (x != ON_UNSET_VALUE && y != ON_UNSET_VALUE && z != ON_UNSET_VALUE)
    && (x != ON_UNSET_POSITIVE_VALUE && y != ON_UNSET_POSITIVE_VALUE && z != ON_UNSET_POSITIVE_VALUE);
}

bool ON_3dPoint::IsCoincident(const ON_3dPoint& p) const
{
  return ON_PointsAreCoincident(3, false, *this, p);
}

bool ON_PointsAreCoincident(const ON_3dPoint& P, const ON_3dPoint& Q)
{
  return ON_PointsAreCoincident(3, false, P, Q);
}

ON_3dPoint operator*(int i, const ON_3dPoint& p)
{
  double d = i;
  return ON_3dPoint(d*p.x,d*p.y,d*p.z);
}

ON_3dPoint operator*(float f, const ON_3dPoint& p)
{
  double d = f;
  return ON_3dPoint(d*p.x,d*p.y,d*p.z);
}

ON_3dPoint operator*(double d, const ON_3dPoint& p)
{
  return ON_3dPoint(d*p.x,d*p.y,d*p.z);
}

////////////////////////////////////////////////////////////////
//
// ON_4dPoint
//

bool ON_4dPoint::operator!=(const ON_4dPoint& rhs) const
{
  return Internal_NotEqualDoubleArray(4, &x, &rhs.x);
}

bool ON_4dPoint::operator==(const ON_4dPoint& rhs) const
{
  return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w);
}


double ON_4dPoint::InnerProduct(
  const ON_4dPoint& lhs,
  const ON_4dPoint& rhs
)
{
  return (lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z + lhs.w*rhs.w);
}

ON_4dPoint::ON_4dPoint( const float* p )
{
  if (p) {
    x = (double)p[0]; y = (double)p[1]; z = (double)p[2]; w = (double)p[3];
  }
  else {
    x = y = z = 0.0; w = 1.0;
  }
}

ON_4dPoint::ON_4dPoint( const double* p )
{
  if (p) {
    x = p[0]; y = p[1]; z = p[2]; w = p[3];
  }
  else {
    x = y = z = 0.0; w = 1.0;
  }
}

ON_4dPoint::ON_4dPoint(double xx,double yy,double zz,double ww)
{x=xx;y=yy;z=zz;w=ww;}

ON_4dPoint::ON_4dPoint(const ON_2dPoint& p)
{x=p.x;y=p.y;z=0.0;w=1.0;}

ON_4dPoint::ON_4dPoint(const ON_3dPoint& p)
{
  x=p.x;y=p.y;z=p.z;w=1.0;
}

ON_4dPoint::ON_4dPoint(const ON_2dVector& v)
{x=v.x;y=v.y;z=w=0.0;}

ON_4dPoint::ON_4dPoint(const ON_3dVector& v)
{x=v.x;y=v.y;z=v.z;w=0.0;}


ON_4dPoint::ON_4dPoint(const ON_2fPoint& p)
{x=p.x;y=p.y;z=0.0;w=1.0;}

ON_4dPoint::ON_4dPoint(const ON_3fPoint& p)
{
  x=p.x;y=p.y;z=p.z;w=1.0;
}

ON_4dPoint::ON_4dPoint(const ON_4fPoint& p)
{
  x=p.x;y=p.y;z=p.z;w=p.w;
}

ON_4dPoint::ON_4dPoint(const ON_2fVector& v)
{x=v.x;y=v.y;z=w=0.0;}

ON_4dPoint::ON_4dPoint(const ON_3fVector& v)
{x=v.x;y=v.y;z=v.z;w=0.0;}

ON_4dPoint::operator double*()
{
  return &x;
}

ON_4dPoint::operator const double*() const
{
  return &x;
}

ON_4dPoint& ON_4dPoint::operator=(const float* p)
{
  if ( p ) {
    x = (double)p[0];
    y = (double)p[1];
    z = (double)p[2];
    w = (double)p[3];
  }
  else {
    x = y = z = 0.0; w = 1.0;
  }
  return *this;
}

ON_4dPoint& ON_4dPoint::operator=(const double* p)
{
  if ( p ) {
    x = p[0];
    y = p[1];
    z = p[2];
    w = p[3];
  }
  else {
    x = y = z = 0.0; w = 1.0;
  }
  return *this;
}

ON_4dPoint& ON_4dPoint::operator=(const ON_2dPoint& p)
{
  x = p.x;
  y = p.y;
  z = 0.0;
  w = 1.0;
  return *this;
}

ON_4dPoint& ON_4dPoint::operator=(const ON_3dPoint& p)
{
  x = p.x;
  y = p.y;
  z = p.z;
  w = 1.0;
  return *this;
}

ON_4dPoint& ON_4dPoint::operator=(const ON_2dVector& v)
{
  x = v.x;
  y = v.y;
  z = 0.0;
  w = 0.0;
  return *this;
}

ON_4dPoint& ON_4dPoint::operator=(const ON_3dVector& v)
{
  x = v.x;
  y = v.y;
  z = v.z;
  w = 0.0;
  return *this;
}

ON_4dPoint& ON_4dPoint::operator=(const ON_2fPoint& p)
{
  x = (double)p.x;
  y = (double)p.y;
  z = 0.0;
  w = 1.0;
  return *this;
}

ON_4dPoint& ON_4dPoint::operator=(const ON_3fPoint& p)
{
  x = (double)p.x;
  y = (double)p.y;
  z = (double)p.z;
  w = 1.0;
  return *this;
}

ON_4dPoint& ON_4dPoint::operator=(const ON_4fPoint& p)
{
  x = (double)p.x;
  y = (double)p.y;
  z = (double)p.z;
  w = (double)p.w;
  return *this;
}

ON_4dPoint& ON_4dPoint::operator=(const ON_2fVector& v)
{
  x = (double)v.x;
  y = (double)v.y;
  z = 0.0;
  w = 0.0;
  return *this;
}

ON_4dPoint& ON_4dPoint::operator=(const ON_3fVector& v)
{
  x = (double)v.x;
  y = (double)v.y;
  z = (double)v.z;
  w = 0.0;
  return *this;
}


ON_4dPoint& ON_4dPoint::operator*=(double d)
{
  x *= d;
  y *= d;
  z *= d;
  w *= d;
  return *this;
}

ON_4dPoint& ON_4dPoint::operator/=(double d)
{
  const double one_over_d = 1.0/d;
  x *= one_over_d;
  y *= one_over_d;
  z *= one_over_d;
  w *= one_over_d;
  return *this;
}

ON_4dPoint& ON_4dPoint::operator+=(const ON_4dPoint& p)
{
  // sum w = sqrt(w1*w2)
  if ( p.w == w ) {
    x += p.x;
    y += p.y;
    z += p.z;
  }
  else if (p.w == 0.0 ) {
    x += p.x;
    y += p.y;
    z += p.z;
  }
  else if ( w == 0.0 ) {
    x += p.x;
    y += p.y;
    z += p.z;
    w = p.w;
  }
  else {
    const double sw1 = (w>0.0) ? sqrt(w) : -sqrt(-w);
    const double sw2 = (p.w>0.0) ? sqrt(p.w) : -sqrt(-p.w);
    const double s1 = sw2/sw1;
    const double s2 = sw1/sw2;
    x = x*s1 + p.x*s2;
    y = y*s1 + p.y*s2;
    z = z*s1 + p.z*s2;
    w = sw1*sw2;
  }
  return *this;
}

ON_4dPoint& ON_4dPoint::operator-=(const ON_4dPoint& p)
{
  // difference w = sqrt(w1*w2)
  if ( p.w == w ) {
    x -= p.x;
    y -= p.y;
    z -= p.z;
  }
  else if (p.w == 0.0 ) {
    x -= p.x;
    y -= p.y;
    z -= p.z;
  }
  else if ( w == 0.0 ) {
    x -= p.x;
    y -= p.y;
    z -= p.z;
    w = p.w;
  }
  else {
    const double sw1 = (w>0.0) ? sqrt(w) : -sqrt(-w);
    const double sw2 = (p.w>0.0) ? sqrt(p.w) : -sqrt(-p.w);
    const double s1 = sw2/sw1;
    const double s2 = sw1/sw2;
    x = x*s1 - p.x*s2;
    y = y*s1 - p.y*s2;
    z = z*s1 - p.z*s2;
    w = sw1*sw2;
  }
  return *this;
}

ON_4dPoint ON_4dPoint::operator+( const ON_4dPoint& p ) const
{
  ON_4dPoint q(x,y,z,w);
  q+=p;
  return q;
}

ON_4dPoint ON_4dPoint::operator-( const ON_4dPoint& p ) const
{
  ON_4dPoint q(x,y,z,w);
  q-=p;
  return q;
}

ON_4dPoint ON_4dPoint::operator*( double d ) const
{
  return ON_4dPoint(x*d,y*d,z*d,w*d);
}

ON_4dPoint ON_4dPoint::operator/( double d ) const
{
  const double one_over_d = 1.0/d;
  return ON_4dPoint(x*one_over_d,y*one_over_d,z*one_over_d,w*one_over_d);
}

double ON_4dPoint::operator[](int i) const
{
  return ((i<=0)?x:((i>=3)?w:((i==1)?y:z)));
}

double& ON_4dPoint::operator[](int i)
{
  double* pd = (i<=0) ? &x : ( (i>=3) ? &w : (i==1)?&y:&z);
  return *pd;
}

double ON_4dPoint::operator[](unsigned int i) const
{
  return ((i<=0)?x:((i>=3)?w:((i==1)?y:z)));
}

double& ON_4dPoint::operator[](unsigned int i)
{
  double* pd = (i<=0) ? &x : ( (i>=3) ? &w : (i==1)?&y:&z);
  return *pd;
}

int ON_4dPoint::MaximumCoordinateIndex() const
{
  const double* a = &x;
  int i = ( fabs(y) > fabs(x) ) ? 1 : 0;
  if (fabs(z) > fabs(a[i])) i = 2; if (fabs(w) > fabs(a[i])) i = 3;
  return i;
}

double ON_4dPoint::MaximumCoordinate() const
{
  double c = fabs(x); if (fabs(y)>c) c=fabs(y); if (fabs(z)>c) c=fabs(z); if (fabs(w)>c) c=fabs(w);
  return c;
}

int ON_4dPoint::MinimumCoordinateIndex() const
{
  const double* a = &x;
  int i = ( fabs(y) < fabs(x) ) ? 1 : 0;
  if (fabs(z) < fabs(a[i])) i = 2; if (fabs(w) < fabs(a[i])) i = 3;
  return i;
}

double ON_4dPoint::MinimumCoordinate() const
{
  double c = fabs(x); if (fabs(y)<c) c=fabs(y); if (fabs(z)<c) c=fabs(z); if (fabs(w)<c) c=fabs(w);
  return c;
}

ON_4dPoint operator*( double d, const ON_4dPoint& p )
{
  return ON_4dPoint( d*p.x, d*p.y, d*p.z, d*p.w );
}

////////////////////////////////////////////////////////////////
//
// ON_2dVector
//

// static
const ON_2dVector& ON_2dVector::UnitVector(int index)
{
  static ON_2dVector o(0.0,0.0);
  static ON_2dVector x(1.0,0.0);
  static ON_2dVector y(0.0,1.0);
  switch(index)
  {
  case 0:
    return x;
  case 1:
    return y;
  }
  return o;
}

ON_2dVector::ON_2dVector( const float* v )
{
  if (v) {
    x = (double)v[0]; y = (double)v[1];
  }
  else {
    x = y = 0.0;
  }
}

ON_2dVector::ON_2dVector( const double* v )
{
  if (v) {
    x = v[0]; y = v[1];
  }
  else {
    x = y = 0.0;
  }
}

ON_2dVector::ON_2dVector(double xx,double yy)
{x=xx;y=yy;}

ON_2dVector::ON_2dVector(const ON_3dVector& v)
{x=v.x;y=v.y;}

ON_2dVector::ON_2dVector(const ON_2dPoint& p)
{x=p.x;y=p.y;}

ON_2dVector::ON_2dVector(const ON_3dPoint& p)
{x=p.x;y=p.y;}

ON_2dVector::ON_2dVector(const ON_2fVector& v)
{x=v.x;y=v.y;}

ON_2dVector::ON_2dVector(const ON_3fVector& v)
{x=v.x;y=v.y;}

ON_2dVector::ON_2dVector(const ON_2fPoint& p)
{x=p.x;y=p.y;}

ON_2dVector::ON_2dVector(const ON_3fPoint& p)
{x=p.x;y=p.y;}


ON_2dVector::operator double*()
{
  return &x;
}

ON_2dVector::operator const double*() const
{
  return &x;
}

ON_2dVector& ON_2dVector::operator=(const float* v)
{
  if ( v ) {
    x = (double)v[0];
    y = (double)v[1];
  }
  else {
    x = y = 0.0;
  }
  return *this;
}

ON_2dVector& ON_2dVector::operator=(const double* v)
{
  if ( v ) {
    x = v[0];
    y = v[1];
  }
  else {
    x = y = 0.0;
  }
  return *this;
}

ON_2dVector& ON_2dVector::operator=(const ON_3dVector& v)
{
  x = v.x;
  y = v.y;
  return *this;
}

ON_2dVector& ON_2dVector::operator=(const ON_2dPoint& p)
{
  x = p.x;
  y = p.y;
  return *this;
}

ON_2dVector& ON_2dVector::operator=(const ON_3dPoint& p)
{
  x = p.x;
  y = p.y;
  return *this;
}

ON_2dVector& ON_2dVector::operator=(const ON_2fVector& v)
{
  x = v.x;
  y = v.y;
  return *this;
}

ON_2dVector& ON_2dVector::operator=(const ON_3fVector& v)
{
  x = v.x;
  y = v.y;
  return *this;
}

ON_2dVector& ON_2dVector::operator=(const ON_2fPoint& p)
{
  x = p.x;
  y = p.y;
  return *this;
}

ON_2dVector& ON_2dVector::operator=(const ON_3fPoint& p)
{
  x = p.x;
  y = p.y;
  return *this;
}

ON_2dVector ON_2dVector::operator-() const
{
  return ON_2dVector(-x,-y);
}

ON_2dVector& ON_2dVector::operator*=(double d)
{
  x *= d;
  y *= d;
  return *this;
}

ON_2dVector& ON_2dVector::operator/=(double d)
{
  const double one_over_d = 1.0/d;
  x *= one_over_d;
  y *= one_over_d;
  return *this;
}

ON_2dVector& ON_2dVector::operator+=(const ON_2dVector& v)
{
  x += v.x;
  y += v.y;
  return *this;
}

ON_2dVector& ON_2dVector::operator-=(const ON_2dVector& v)
{
  x -= v.x;
  y -= v.y;
  return *this;
}

ON_2dVector ON_2dVector::operator*( int i ) const
{
  double d = i;
  return ON_2dVector(x*d,y*d);
}

ON_2dVector ON_2dVector::operator*( float f ) const
{
  double d = f;
  return ON_2dVector(x*d,y*d);
}

ON_2dVector ON_2dVector::operator*( double d ) const
{
  return ON_2dVector(x*d,y*d);
}

double ON_2dVector::operator*( const ON_2dVector& v ) const
{
  return (x*v.x + y*v.y);
}

double ON_2dVector::operator*( const ON_2dPoint& v ) const
{
  return (x*v.x + y*v.y);
}

double ON_2dVector::operator*( const ON_2fVector& v ) const
{
  return (x*v.x + y*v.y);
}

ON_2dVector ON_2dVector::operator/( int i ) const
{
  const double one_over_d = 1.0/((double)i);
  return ON_2dVector(x*one_over_d,y*one_over_d);
}

ON_2dVector ON_2dVector::operator/( float f ) const
{
  const double one_over_d = 1.0/((double)f);
  return ON_2dVector(x*one_over_d,y*one_over_d);
}

ON_2dVector ON_2dVector::operator/( double d ) const
{
  const double one_over_d = 1.0/d;
  return ON_2dVector(x*one_over_d,y*one_over_d);
}

ON_2dVector ON_2dVector::operator+( const ON_2dVector& v ) const
{
  return ON_2dVector(x+v.x,y+v.y);
}

ON_2dPoint ON_2dVector::operator+( const ON_2dPoint& p ) const
{
  return ON_2dPoint(x+p.x,y+p.y);
}

ON_2dVector ON_2dVector::operator-( const ON_2dVector& v ) const
{
  return ON_2dVector(x-v.x,y-v.y);
}

ON_2dPoint ON_2dVector::operator-( const ON_2dPoint& v ) const
{
  return ON_2dPoint(x-v.x,y-v.y);
}


ON_3dVector ON_2dVector::operator+( const ON_3dVector& v ) const
{
  return ON_3dVector(x+v.x,y+v.y,v.z);
}

ON_3dPoint ON_2dVector::operator+( const ON_3dPoint& p ) const
{
  return ON_3dPoint(x+p.x,y+p.y,p.z);
}

ON_3dVector ON_2dVector::operator-( const ON_3dVector& v ) const
{
  return ON_3dVector(x-v.x,y-v.y,-v.z);
}

ON_3dPoint ON_2dVector::operator-( const ON_3dPoint& v ) const
{
  return ON_3dPoint(x-v.x,y-v.y,-v.z);
}

ON_2dVector ON_2dVector::operator+( const ON_2fVector& v ) const
{
  return ON_2dVector(x+v.x,y+v.y);
}

ON_2dPoint ON_2dVector::operator+( const ON_2fPoint& p ) const
{
  return ON_2dPoint(x+p.x,y+p.y);
}

ON_2dVector ON_2dVector::operator-( const ON_2fVector& v ) const
{
  return ON_2dVector(x-v.x,y-v.y);
}

ON_2dPoint ON_2dVector::operator-( const ON_2fPoint& v ) const
{
  return ON_2dPoint(x-v.x,y-v.y);
}


ON_3dVector ON_2dVector::operator+( const ON_3fVector& v ) const
{
  return ON_3dVector(x+v.x,y+v.y,v.z);
}

ON_3dPoint ON_2dVector::operator+( const ON_3fPoint& p ) const
{
  return ON_3dPoint(x+p.x,y+p.y,p.z);
}

ON_3dVector ON_2dVector::operator-( const ON_3fVector& v ) const
{
  return ON_3dVector(x-v.x,y-v.y,-v.z);
}

ON_3dPoint ON_2dVector::operator-( const ON_3fPoint& v ) const
{
  return ON_3dPoint(x-v.x,y-v.y,-v.z);
}

bool ON_2dVector::operator==( const ON_2dVector& v ) const
{
  return (x==v.x&&y==v.y)?true:false;
}

bool ON_2dVector::operator!=( const ON_2dVector& v ) const
{
  return Internal_NotEqualDoubleArray(2, &x, &v.x);
}

bool ON_2dVector::operator<=( const ON_2dVector& v ) const
{
  // dictionary order
  return ((x<v.x)?true:((x==v.x&&y<=v.y)?true:false));
}

bool ON_2dVector::operator>=( const ON_2dVector& v ) const
{
  // dictionary order
  return ((x>v.x)?true:((x==v.x&&y>=v.y)?true:false));
}

bool ON_2dVector::operator<( const ON_2dVector& v ) const
{
  // dictionary order
  return ((x<v.x)?true:((x==v.x&&y<v.y)?true:false));
}

bool ON_2dVector::operator>( const ON_2dVector& v ) const
{
  // dictionary order
  return ((x>v.x)?true:((x==v.x&&y>v.y)?true:false));
}

double ON_2dVector::operator[](int i) const
{
  return ((i<=0)?x:y);
}

double& ON_2dVector::operator[](int i)
{
  double* pd = (i<=0)? &x : &y;
  return *pd;
}

double ON_2dVector::operator[](unsigned int i) const
{
  return ((i<=0)?x:y);
}

double& ON_2dVector::operator[](unsigned int i)
{
  double* pd = (i<=0)? &x : &y;
  return *pd;
}

int ON_2dVector::MaximumCoordinateIndex() const
{
  return ( (fabs(y)>fabs(x)) ? 1 : 0 );
}

double ON_2dVector::MaximumCoordinate() const
{
  double c = fabs(x); if (fabs(y)>c) c=fabs(y);
  return c;
}

int ON_2dVector::MinimumCoordinateIndex() const
{
  return (fabs(y)<fabs(x)) ? 1: 0;
}

double ON_2dVector::MinimumCoordinate() const
{
  double c = fabs(x); if (fabs(y)<c) c=fabs(y);
  return c;
}

double ON_2dVector::LengthSquared() const
{
  return (x*x + y*y);
}

double ON_Length2d( double x, double y )
{
  double len;
  x = fabs(x);
  y = fabs(y);
  if ( y > x ) {
    len = x; x = y; y = len;
  }
 
  // 15 September 2003 Dale Lear
  //     For small denormalized doubles (positive but smaller
  //     than DBL_MIN), some compilers/FPUs set 1.0/fx to +INF.
  //     Without the ON_DBL_MIN test we end up with
  //     microscopic vectors that have infinite length!
  //
  //     This code is absolutely necessary.  It is a critical
  //     part of the bug fix for RR 11217.
  if ( x > ON_DBL_MIN )
  {
    y /= x;
    len = x*sqrt(1.0 + y*y);
  }
  else if ( x > 0.0 && ON_IS_FINITE(x) )
    len = x;
  else
    len = 0.0;

  return len;
}

double ON_Length2dSquared(double x, double y)
{
  return (x * x + y * y);
}

double ON_2dVector::Length() const
{
  return ON_Length2d(x,y);
}

double ON_2dVector::WedgeProduct(const ON_2dVector& B) const{
	return x*B.y - y*B.x;
}

void ON_2dVector::Reverse()
{
  x = -x;
  y = -y;
}

bool ON_2dVector::Unitize()
{
  // 15 September 2003 Dale Lear
  //     Added the ON_IS_FINITE and ON_DBL_MIN test.  See ON_2dVector::Length()
  //     for details.
  double d = Length();
  if ( ON_IS_FINITE(d) )
  {
    if ( d > ON_DBL_MIN ) 
    {
      x /= d;
      y /= d;
      return true;
    }
    
    if ( d > 0.0 )
    {
      // This code is rarely used and can be slow.
      // It multiplies by 2^1023 in an attempt to 
      // normalize the coordinates.
      // If the renormalization works, then we're
      // ok.  If the renormalization fails, we
      // return false.
      ON_2dVector tmp;
      tmp.x = x*8.9884656743115795386465259539451e+307;
      tmp.y = y*8.9884656743115795386465259539451e+307;
      d = tmp.Length();
      if ( ON_IS_FINITE(d) && d > ON_DBL_MIN )
      {
        x = tmp.x/d;
        y = tmp.y/d;
        return true;
      }
    }
  }

  x = 0.0;
  y = 0.0;

  return false;
}

ON_2dVector ON_2dVector::UnitVector() const
{
  ON_2dVector u(*this);
  u.Unitize();
  return u;
}

bool ON_2dVector::IsTiny( double tiny_tol ) const
{
  return (fabs(x) <= tiny_tol && fabs(y) <= tiny_tol );
}

void ON_2dVector::Zero()
{
  x = y = 0.0;
}

bool ON_2dVector::IsZero() const
{
  return (x==0.0 && y==0.0);
}

bool ON_2dVector::IsNotZero() const
{
{
  // the && (x != ON_UNSET_VALUE && y != ON_UNSET_VALUE) insures no coordinate is a Nan.
  return
    (x != 0.0 || y != 0.0)
    && (x != ON_UNSET_VALUE && y != ON_UNSET_VALUE)
    && (x != ON_UNSET_POSITIVE_VALUE && y != ON_UNSET_POSITIVE_VALUE);
}
}

bool ON_2dVector::IsUnitVector() const
{
  return (x != ON_UNSET_VALUE && y != ON_UNSET_VALUE && fabs(Length() - 1.0) <= ON_SQRT_EPSILON);
}

// set this vector to be perpendicular to another vector
bool ON_2dVector::PerpendicularTo( // Result is not unitized. 
                      // returns false if input vector is zero
      const ON_2dVector& v
      )
{
  y = v.x;
  x = -v.y;
  return (x!= 0.0 || y!= 0.0) ? true : false;
}

// set this vector to be perpendicular to a line defined by 2 points
bool ON_2dVector::PerpendicularTo( 
      const ON_2dPoint& p, 
      const ON_2dPoint& q
      )
{
  return PerpendicularTo(q-p);
}

double ON_2dVector::SignedAngle(const ON_2dVector& A, const ON_2dVector& B)
{
  return atan2(-A.x * B.y + A.y * B.x, A.x * B.x + A.y * B.y);
}

ON_2dVector operator*(int i, const ON_2dVector& v)
{
  double d = i;
  return ON_2dVector(d*v.x,d*v.y);
}

ON_2dVector operator*(float f, const ON_2dVector& v)
{
  double d = f;
  return ON_2dVector(d*v.x,d*v.y);
}

ON_2dVector operator*(double d, const ON_2dVector& v)
{
  return ON_2dVector(d*v.x,d*v.y);
}

double ON_DotProduct( const ON_2dVector& a , const ON_2dVector& b )
{
  // inner (dot) product between 3d vectors
  return (a.x*b.x + a.y*b.y );
}

double ON_WedgeProduct( const ON_2dVector& a , const ON_2dVector& b )
{
  // exterior (wedge) product between 2d vectors
  return (a.x*b.y - a.y*b.x );
}

ON_3dVector ON_CrossProduct( const ON_2dVector& a , const ON_2dVector& b )
{
  return ON_3dVector(0.0, 0.0, a.x*b.y - b.x*a.y );
}

////////////////////////////////////////////////////////////////
//
// ON_3dVector
//

// static
const ON_3dVector& ON_3dVector::UnitVector(int index)
{
  static ON_3dVector o(0.0,0.0,0.0);
  static ON_3dVector x(1.0,0.0,0.0);
  static ON_3dVector y(0.0,1.0,0.0);
  static ON_3dVector z(0.0,0.0,1.0);
  switch(index)
  {
  case 0:
    return x;
  case 1:
    return y;
  case 2:
    return z;
  }
  return o;
}

ON_3dVector::ON_3dVector( const float* v )
{
  if (v) {
    x = (double)v[0]; y = (double)v[1]; z = (double)v[2];
  }
  else {
    x = y = z = 0.0;
  }
}

ON_3dVector::ON_3dVector( const double* v )
{
  if (v) {
    x = v[0]; y = v[1]; z = v[2];
  }
  else {
    x = y = z = 0.0;
  }
}

ON_3dVector::ON_3dVector(double xx,double yy,double zz)
{x=xx;y=yy;z=zz;}

ON_3dVector::ON_3dVector(const ON_2dVector& v)
{x=v.x;y=v.y;z=0.0;}

ON_3dVector::ON_3dVector(const ON_2dPoint& p)
{x=p.x;y=p.y;z=0.0;}

ON_3dVector::ON_3dVector(const ON_3dPoint& p)
{x=p.x;y=p.y;z=p.z;}

ON_3dVector::ON_3dVector(const ON_2fVector& v)
{x=v.x;y=v.y;z=0.0;}

ON_3dVector::ON_3dVector(const ON_3fVector& v)
{x=v.x;y=v.y;z=v.z;}

ON_3dVector::ON_3dVector(const ON_2fPoint& p)
{x=p.x;y=p.y;z=0.0;}

ON_3dVector::ON_3dVector(const ON_3fPoint& p)
{x=p.x;y=p.y;z=p.z;}

ON_3dVector::operator double*()
{
  return &x;
}

ON_3dVector::operator const double*() const
{
  return &x;
}

ON_3dVector& ON_3dVector::operator=(const float* v)
{
  if ( v ) {
    x = (double)v[0];
    y = (double)v[1];
    z = (double)v[2];
  }
  else {
    x = y = z = 0.0;
  }
  return *this;
}

ON_3dVector& ON_3dVector::operator=(const double* v)
{
  if ( v ) {
    x = v[0];
    y = v[1];
    z = v[2];
  }
  else {
    x = y = z = 0.0;
  }
  return *this;
}

ON_3dVector& ON_3dVector::operator=(const ON_2dVector& v)
{
  x = v.x;
  y = v.y;
  z = 0.0;
  return *this;
}

ON_3dVector& ON_3dVector::operator=(const ON_2dPoint& p)
{
  x = p.x;
  y = p.y;
  z = 0.0;
  return *this;
}

ON_3dVector& ON_3dVector::operator=(const ON_3dPoint& p)
{
  x = p.x;
  y = p.y;
  z = p.z;
  return *this;
}


ON_3dVector& ON_3dVector::operator=(const ON_2fVector& v)
{
  x = v.x;
  y = v.y;
  z = 0.0;
  return *this;
}

ON_3dVector& ON_3dVector::operator=(const ON_3fVector& v)
{
  x = v.x;
  y = v.y;
  z = v.z;
  return *this;
}

ON_3dVector& ON_3dVector::operator=(const ON_2fPoint& p)
{
  x = p.x;
  y = p.y;
  z = 0.0;
  return *this;
}

ON_3dVector& ON_3dVector::operator=(const ON_3fPoint& p)
{
  x = p.x;
  y = p.y;
  z = p.z;
  return *this;
}

ON_3dVector ON_3dVector::operator-() const
{
  return ON_3dVector(-x,-y,-z);
}

ON_3dVector& ON_3dVector::operator*=(double d)
{
  x *= d;
  y *= d;
  z *= d;
  return *this;
}

ON_3dVector& ON_3dVector::operator/=(double d)
{
  const double one_over_d = 1.0/d;
  x *= one_over_d;
  y *= one_over_d;
  z *= one_over_d;
  return *this;
}

ON_3dVector& ON_3dVector::operator+=(const ON_3dVector& v)
{
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

ON_3dVector& ON_3dVector::operator-=(const ON_3dVector& v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

ON_3dVector ON_3dVector::operator*( int i ) const
{
  double d = i;
  return ON_3dVector(x*d,y*d,z*d);
}

ON_3dVector ON_3dVector::operator*( float f ) const
{
  double d = f;
  return ON_3dVector(x*d,y*d,z*d);
}

ON_3dVector ON_3dVector::operator*( double d ) const
{
  return ON_3dVector(x*d,y*d,z*d);
}

double ON_3dVector::operator*( const ON_3dVector& v ) const
{
  return (x*v.x + y*v.y + z*v.z);
}

double ON_3dVector::operator*( const ON_3dPoint& v ) const
{
  return (x*v.x + y*v.y + z*v.z);
}

double ON_3dVector::operator*( const ON_3fVector& v ) const
{
  return (x*v.x + y*v.y + z*v.z);
}

ON_3dVector ON_3dVector::operator/( int i ) const
{
  const double one_over_d = 1.0/((double)i);
  return ON_3dVector(x*one_over_d,y*one_over_d,z*one_over_d);
}

ON_3dVector ON_3dVector::operator/( float f ) const
{
  const double one_over_d = 1.0/((double)f);
  return ON_3dVector(x*one_over_d,y*one_over_d,z*one_over_d);
}

ON_3dVector ON_3dVector::operator/( double d ) const
{
  const double one_over_d = 1.0/d;
  return ON_3dVector(x*one_over_d,y*one_over_d,z*one_over_d);
}

ON_3dVector ON_3dVector::operator+( const ON_3dVector& v ) const
{
  return ON_3dVector(x+v.x,y+v.y,z+v.z);
}

ON_3dPoint ON_3dVector::operator+( const ON_3dPoint& p ) const
{
  return ON_3dPoint(x+p.x,y+p.y,z+p.z);
}

ON_3dVector ON_3dVector::operator-( const ON_3dVector& v ) const
{
  return ON_3dVector(x-v.x,y-v.y,z-v.z);
}

ON_3dPoint ON_3dVector::operator-( const ON_3dPoint& v ) const
{
  return ON_3dPoint(x-v.x,y-v.y,z-v.z);
}

ON_3dVector ON_3dVector::operator+( const ON_2dVector& v ) const
{
  return ON_3dVector(x+v.x,y+v.y,z);
}

ON_3dPoint ON_3dVector::operator+( const ON_2dPoint& p ) const
{
  return ON_3dPoint(x+p.x,y+p.y,z);
}

ON_3dVector ON_3dVector::operator-( const ON_2dVector& v ) const
{
  return ON_3dVector(x-v.x,y-v.y,z);
}

ON_3dPoint ON_3dVector::operator-( const ON_2dPoint& v ) const
{
  return ON_3dPoint(x-v.x,y-v.y,z);
}

ON_3dVector ON_3dVector::operator+( const ON_3fVector& v ) const
{
  return ON_3dVector(x+v.x,y+v.y,z+v.z);
}

ON_3dPoint ON_3dVector::operator+( const ON_3fPoint& p ) const
{
  return ON_3dPoint(x+p.x,y+p.y,z+p.z);
}

ON_3dVector ON_3dVector::operator-( const ON_3fVector& v ) const
{
  return ON_3dVector(x-v.x,y-v.y,z-v.z);
}

ON_3dPoint ON_3dVector::operator-( const ON_3fPoint& v ) const
{
  return ON_3dPoint(x-v.x,y-v.y,z-v.z);
}

ON_3dVector ON_3dVector::operator+( const ON_2fVector& v ) const
{
  return ON_3dVector(x+v.x,y+v.y,z);
}

ON_3dPoint ON_3dVector::operator+( const ON_2fPoint& p ) const
{
  return ON_3dPoint(x+p.x,y+p.y,z);
}

ON_3dVector ON_3dVector::operator-( const ON_2fVector& v ) const
{
  return ON_3dVector(x-v.x,y-v.y,z);
}

ON_3dPoint ON_3dVector::operator-( const ON_2fPoint& v ) const
{
  return ON_3dPoint(x-v.x,y-v.y,z);
}

bool ON_3dPoint::operator==( const ON_3dPoint& v ) const
{
  return (x==v.x&&y==v.y&&z==v.z)?true:false;
}

bool ON_3dPoint::operator!=( const ON_3dPoint& v ) const
{
  return Internal_NotEqualDoubleArray(3, &x, &v.x);
}

bool ON_3dVector::operator==( const ON_3dVector& v ) const
{
  return (x==v.x&&y==v.y&&z==v.z)?true:false;
}

bool ON_3dVector::operator!=( const ON_3dVector& v ) const
{
  return Internal_NotEqualDoubleArray(3, &x, &v.x);
}

bool ON_3dVector::operator<=( const ON_3dVector& v ) const
{
  // dictionary order
  return ((x<v.x)?true:((x==v.x)?((y<v.y)?true:(y==v.y&&z<=v.z)?true:false):false));
}

bool ON_3dVector::operator>=( const ON_3dVector& v ) const
{
  // dictionary order
  return ((x>v.x)?true:((x==v.x)?((y>v.y)?true:(y==v.y&&z>=v.z)?true:false):false));
}

bool ON_3dVector::operator<( const ON_3dVector& v ) const
{
  // dictionary order
  return ((x<v.x)?true:((x==v.x)?((y<v.y)?true:(y==v.y&&z<v.z)?true:false):false));
}

bool ON_3dVector::operator>( const ON_3dVector& v ) const
{
  // dictionary order
  return ((x>v.x)?true:((x==v.x)?((y>v.y)?true:(y==v.y&&z>v.z)?true:false):false));
}

double ON_3dVector::operator[](int i) const
{
  return ( (i<=0)?x:((i>=2)?z:y) );
}

double& ON_3dVector::operator[](int i)
{
  double* pd = (i<=0)? &x : ( (i>=2) ?  &z : &y);
  return *pd;
}

double ON_3dVector::operator[](unsigned int i) const
{
  return ( (i<=0)?x:((i>=2)?z:y) );
}

double& ON_3dVector::operator[](unsigned int i)
{
  double* pd = (i<=0)? &x : ( (i>=2) ?  &z : &y);
  return *pd;
}

int ON_3dVector::MaximumCoordinateIndex() const
{
  return (fabs(y)>fabs(x)) ? ((fabs(z)>fabs(y))?2:1) : ((fabs(z)>fabs(x))?2:0);
}

double ON_3dVector::MaximumCoordinate() const
{
  double c = fabs(x); if (fabs(y)>c) c=fabs(y); if (fabs(z)>c) c=fabs(z);
  return c;
}

int ON_3dVector::MinimumCoordinateIndex() const
{
  return (fabs(y)<fabs(x)) ? ((fabs(z)<fabs(y))?2:1) : ((fabs(z)<fabs(x))?2:0);
}

double ON_3dVector::MinimumCoordinate() const
{
  double c = fabs(x); if (fabs(y)<c) c=fabs(y); if (fabs(z)<c) c=fabs(z);
  return c;
}

double ON_3dVector::LengthSquared() const
{
  return (x*x + y*y + z*z);
}

double ON_Length3d(double x, double y, double z)
{
  double len;
  x = fabs(x);
  y = fabs(y);
  z = fabs(z);
  if ( y >= x && y >= z ) {
    len = x; x = y; y = len;
  }
  else if ( z >= x && z >= y ) {
    len = x; x = z; z = len;
  }

  // 15 September 2003 Dale Lear
  //     For small denormalized doubles (positive but smaller
  //     than DBL_MIN), some compilers/FPUs set 1.0/x to +INF.
  //     Without the ON_DBL_MIN test we end up with
  //     microscopic vectors that have infinite length!
  //
  //     This code is absolutely necessary.  It is a critical
  //     part of the bug fix for RR 11217.
  if ( x > ON_DBL_MIN ) 
  {
    y /= x;
    z /= x;
    len = x*sqrt(1.0 + y*y + z*z);
  }
  else if ( x > 0.0 && ON_IS_FINITE(x) )
    len = x;
  else
    len = 0.0;

  return len;
}

double ON_Length3dSquared(double x, double y, double z)
{
  return (x * x + y * y + z * z);
}

double ON_3dVector::Length() const
{
  return ON_Length3d(x,y,z);
}

void ON_3dVector::Reverse()
{
  x = -x;
  y = -y;
  z = -z;
}

bool ON_3dVector::Unitize()
{
  // 15 September 2003 Dale Lear
  //     Added the ON_IS_FINITE and ON_DBL_MIN test.  See ON_3dVector::Length()
  //     for details.
  double d = Length();

  if ( ON_IS_FINITE(d) )
  {
    if ( d > ON_DBL_MIN )
    {
      x /= d;
      y /= d;
      z /= d;
      return true;
    }
    
    if ( d > 0.0 )
    {
      // This code is rarely used and can be slow.
      // It multiplies by 2^1023 in an attempt to 
      // normalize the coordinates.
      // If the renormalization works, then we're
      // ok.  If the renormalization fails, we
      // return false.
      ON_3dVector tmp;
      tmp.x = x*8.9884656743115795386465259539451e+307;
      tmp.y = y*8.9884656743115795386465259539451e+307;
      tmp.z = z*8.9884656743115795386465259539451e+307;
      d = tmp.Length();
      if ( ON_IS_FINITE(d) && d > ON_DBL_MIN )
      {
        x = tmp.x/d;
        y = tmp.y/d;
        z = tmp.z/d;
        return true;
      }
    }
  }

  x = 0.0;
  y = 0.0;
  z = 0.0;

  return false;
}

ON_3dVector ON_3dVector::UnitVector() const
{
  ON_3dVector u(*this);
  u.Unitize();
  return u;
}

double ON_3dVector::LengthAndUnitize()
{
  double d;
  double len = Length();
  if ( len > ON_DBL_MIN )
  {
    d = 1.0/len;
    x *= d;
    y *= d;
    z *= d;
  }
  else if ( len > 0.0 && ON_IS_FINITE(len) )
  {
    // This code is rarely used and can be slow.
    // It multiplies by 2^1023 in an attempt to 
    // normalize the coordinates.
    // If the renormalization works, then we're
    // ok.  If the renormalization fails, we
    // return false.
    ON_3dVector tmp;
    tmp.x = x*8.9884656743115795386465259539451e+307;
    tmp.y = y*8.9884656743115795386465259539451e+307;
    tmp.z = z*8.9884656743115795386465259539451e+307;
    d = tmp.Length();
    if ( d > ON_DBL_MIN )
    {
      d = 1.0/d;
      x = tmp.x*d;
      y = tmp.y*d;
      z = tmp.z*d;
    }
    else
    {
      len = 0.0;
      x = 0.0;
      y = 0.0;
      z = 0.0;
    }
  }
  else
  {
    len = 0.0;
    x = 0.0;
    y = 0.0;
    z = 0.0;
  }

  return len;
}

bool ON_3dVector::IsTiny( double tiny_tol ) const
{
  return (fabs(x) <= tiny_tol && fabs(y) <= tiny_tol && fabs(z) <= tiny_tol );
}

void ON_3dVector::Zero()
{
  x = y = z = 0.0;
}

bool ON_3dVector::IsZero() const
{
  return (x==0.0 && y==0.0 && z==0.0);
}

bool ON_3dVector::IsNotZero() const
{
  // the UNSET tests also insure x, y, and z are not nans.
  return
    (x != 0.0 || y != 0.0 || z != 0.0)
    && x > ON_UNSET_VALUE && x < ON_UNSET_POSITIVE_VALUE
    && y > ON_UNSET_VALUE && y < ON_UNSET_POSITIVE_VALUE
    && z > ON_UNSET_VALUE && z < ON_UNSET_POSITIVE_VALUE
    ;
}

bool ON_3dVector::IsUnitVector() const
{
  return (x != ON_UNSET_VALUE && y != ON_UNSET_VALUE && z != ON_UNSET_VALUE && fabs(Length() - 1.0) <= ON_SQRT_EPSILON);
}

ON_3dVector operator*(int i, const ON_3dVector& v)
{
  double d = i;
  return ON_3dVector(d*v.x,d*v.y,d*v.z);
}

ON_3dVector operator*(float f, const ON_3dVector& v)
{
  double d = f;
  return ON_3dVector(d*v.x,d*v.y,d*v.z);
}

ON_3dVector operator*(double d, const ON_3dVector& v)
{
  return ON_3dVector(d*v.x,d*v.y,d*v.z);
}

double ON_DotProduct( const ON_3dVector& a , const ON_3dVector& b )
{
  // inner (dot) product between 3d vectors
  return (a.x*b.x + a.y*b.y + a.z*b.z);
}

ON_3dVector ON_CrossProduct( const ON_3dVector& a , const ON_3dVector& b )
{
  return ON_3dVector(a.y*b.z - b.y*a.z, a.z*b.x - b.z*a.x, a.x*b.y - b.x*a.y );
}

double ON_3dVector::DotProduct(
  ON_3dVector A,
  ON_3dVector B
)
{
  return (A.x * B.x + A.y * B.y + A.z * B.z);
}

const ON_3dVector ON_3dVector::CrossProduct(
  ON_3dVector A,
  ON_3dVector B
)
{
  return ON_3dVector(A.y * B.z - B.y * A.z, A.z * B.x - B.z * A.x, A.x * B.y - B.x * A.y);
}


ON_3dVector ON_CrossProduct( const double* a, const double* b )
{
  return ON_3dVector(a[1]*b[2] - b[1]*a[2], a[2]*b[0] - b[2]*a[0], a[0]*b[1] - b[0]*a[1] );
}

double ON_TripleProduct( const ON_3dVector& a, const ON_3dVector& b, const ON_3dVector& c )
{
  // = a o (b x c )
  return (a.x*(b.y*c.z - b.z*c.y) + a.y*(b.z*c.x - b.x*c.z) + a.z*(b.x*c.y - b.y*c.x));
}

double ON_TripleProduct( const double* a, const double* b, const double* c )
{
  // = a o (b x c )
  return (a[0]*(b[1]*c[2] - b[2]*c[1]) + a[1]*(b[2]*c[0] - b[0]*c[2]) + a[2]*(b[0]*c[1] - b[1]*c[0]));
}


bool ON_2dVector::IsValid() const
{
  return ( ON_IS_VALID(x) && ON_IS_VALID(y) ) ? true : false;
}

bool ON_3dVector::IsValid() const
{
  return ( ON_IS_VALID(x) && ON_IS_VALID(y) && ON_IS_VALID(z) ) ? true : false;
}

bool ON_2dPoint::IsValid() const
{
  return (ON_IS_VALID(x) && ON_IS_VALID(y)) ? true : false;
}

bool ON_3dPoint::IsValid() const
{
  return (ON_IS_VALID(x) && ON_IS_VALID(y) && ON_IS_VALID(z) ) ? true : false;
}

bool ON_4dPoint::IsValid() const
{
  return (ON_IS_VALID(x) && ON_IS_VALID(y) && ON_IS_VALID(z) && ON_IS_VALID(w)) ? true : false;
}


bool ON_2fVector::IsValid() const
{
  return ( ON_IS_VALID_FLOAT(x) && ON_IS_VALID_FLOAT(y) ) ? true : false;
}

bool ON_3fVector::IsValid() const
{
  return ( ON_IS_VALID_FLOAT(x) && ON_IS_VALID_FLOAT(y) && ON_IS_VALID_FLOAT(z) ) ? true : false;
}

bool ON_2fPoint::IsValid() const
{
  return (ON_IS_VALID_FLOAT(x) && ON_IS_VALID_FLOAT(y)) ? true : false;
}

bool ON_3fPoint::IsValid() const
{
  return (ON_IS_VALID_FLOAT(x) && ON_IS_VALID_FLOAT(y) && ON_IS_VALID_FLOAT(z) ) ? true : false;
}

bool ON_4fPoint::IsValid() const
{
  return (ON_IS_VALID_FLOAT(x) && ON_IS_VALID_FLOAT(y) && ON_IS_VALID_FLOAT(z) && ON_IS_VALID_FLOAT(w)) ? true : false;
}

void ON_2dPoint::Set(double xx, double yy)
{
  x = xx; y = yy;
}

void ON_3dPoint::Set(double xx, double yy, double zz)
{
  x = xx; y = yy; z = zz;
}


void ON_4dPoint::Set(double xx, double yy, double zz, double ww)
{
  x = xx; y = yy; z = zz; w = ww;
}

void ON_2dVector::Set(double xx, double yy)
{
  x = xx; y = yy;
}

void ON_3dVector::Set(double xx, double yy, double zz)
{
  x = xx; y = yy; z = zz;
}


void ON_2fPoint::Set(float xx, float yy)
{
  x = xx; y = yy;
}

void ON_3fPoint::Set(float xx, float yy, float zz)
{
  x = xx; y = yy; z = zz;
}


void ON_4fPoint::Set(float xx, float yy, float zz, float ww)
{
  x = xx; y = yy; z = zz; w = ww;
}

void ON_2fVector::Set(float xx, float yy)
{
  x = xx; y = yy;
}

void ON_3fVector::Set(float xx, float yy, float zz)
{
  x = xx; y = yy; z = zz;
}

bool ON_PlaneEquation::Create( ON_3dPoint P, ON_3dVector N )
{
  bool rc = false;
  if ( P.IsValid() && N.IsValid() )
  {
    x = N.x;
    y = N.y;
    z = N.z;
    ON_3dVector* v = (ON_3dVector*)&x;
    rc = (fabs(1.0 - v->Length()) > ON_ZERO_TOLERANCE) ? v->Unitize() : true;
    d = -(x*P.x + y*P.y + z*P.z);
  }
  return rc;
}

const ON_PlaneEquation ON_PlaneEquation::CreateFromThreePoints(
  ON_3dPoint pointA,
  ON_3dPoint pointB,
  ON_3dPoint pointC
)
{
  if (pointA.IsValid() && pointB.IsValid() && pointC.IsValid())
  {
    const ON_3dVector X = pointB - pointA;
    const ON_3dVector Y = pointC - pointA;
    return ON_PlaneEquation::CreateFromPointAndNormal(pointA, ON_3dVector::CrossProduct(X, Y));
  }
  return ON_PlaneEquation::NanPlaneEquation;
}

const ON_PlaneEquation ON_PlaneEquation::CreateFromPointAndNormal(
  ON_3dPoint point,
  ON_3dVector normal
)
{
  if (point.IsValid() && normal.IsValid())
  {
    const ON_3dVector N = normal.UnitVector();
    if (false == normal.IsUnitVector() || fabs(1.0 - N.Length()) < fabs(1.0 - normal.Length()) * (1.0 - ON_ZERO_TOLERANCE))
      normal = N; // N is a better unit vector
    if (normal.IsUnitVector())
    {
      ON_PlaneEquation e;
      e.x = normal.x;
      e.y = normal.y;
      e.z = normal.z;
      e.d = -(e.x * point.x + e.y * point.y + e.z * point.z);
      return e;
    }
  }
  return ON_PlaneEquation::NanPlaneEquation;
}

ON_PlaneEquation::ON_PlaneEquation()
  : x(0.0)
  , y(0.0)
  , z(0.0)
  , d(0.0)
{}

ON_PlaneEquation::ON_PlaneEquation(double xx, double yy, double zz, double dd)
  : x(xx)
  , y(yy)
  , z(zz)
  , d(dd)
{}

void ON_PlaneEquation::Set(ON_PlaneEquation& plane_equation, double x, double y, double z, double d)
{
  plane_equation.x = x;
  plane_equation.y = y;
  plane_equation.z = z;
  plane_equation.d = d;
}

double ON_PlaneEquation::MaximumCoefficient() const
{
  double m = fabs(x);
  if (fabs(y) > m)
    m = fabs(y);
  if (fabs(z) > m)
    m = fabs(z);
  if (fabs(d) > m)
    m = fabs(d);
  return m;
}

double& ON_PlaneEquation::operator[](int i)
{
  switch (i)
  {
  case 0:
    return x;
    break;
  case 1:
    return y;
    break;
  case 2:
    return z;
    break;
  case 3:
    return d;
    break;
  }

  ON_ERROR("Invalid coefficient index.");

  // send caller something that can be dereferenced without crashing.
  double* invalid_coefficient = (double*)onmalloc_forever(sizeof(*invalid_coefficient));
  *invalid_coefficient = ON_DBL_QNAN;
  return *invalid_coefficient;
}

double& ON_PlaneEquation::operator[](unsigned int i)
{
  switch (i)
  {
  case 0:
    return x;
    break;
  case 1:
    return y;
    break;
  case 2:
    return z;
    break;
  case 3:
    return d;
    break;
  }

  ON_ERROR("Invalid coefficient index.");

  // send caller something that can be dereferenced without crashing.
  double* invalid_coefficient = (double*)onmalloc_forever(sizeof(*invalid_coefficient));
  *invalid_coefficient = ON_DBL_QNAN;
  return *invalid_coefficient;
}

double ON_PlaneEquation::operator[](int i) const
{
  switch (i)
  {
  case 0:
    return x;
    break;
  case 1:
    return y;
    break;
  case 2:
    return z;
    break;
  case 3:
    return d;
    break;
  }

  ON_ERROR("Invalid coefficient index.");
  return ON_UNSET_VALUE;
}

double ON_PlaneEquation::operator[](unsigned int i) const
{
  switch (i)
  {
  case 0:
    return x;
    break;
  case 1:
    return y;
    break;
  case 2:
    return z;
    break;
  case 3:
    return d;
    break;
  }

  ON_ERROR("Invalid coefficient index.");
  return ON_UNSET_VALUE;
}

ON_PlaneEquation ON_PlaneEquation::NegatedPlaneEquation() const
{
  // do not negate ON_UNSET_VALUE or NaN
  return ON_PlaneEquation(ON_IS_VALID(x) ? -x : x, ON_IS_VALID(y) ? -y : y, ON_IS_VALID(z) ? -z : z, ON_IS_VALID(d) ? -d : d);
}


ON_PlaneEquation ON_PlaneEquation::UnitizedPlaneEquation() const
{
  if (IsSet())
  {
    // 15 September 2003 Dale Lear
    //     Added the ON_IS_FINITE and ON_DBL_MIN test.  See ON_3dVector::Length()
    //     for details.
    double dd = DirectionLength();

    if (ON_IS_FINITE(dd))
    {
      if (dd > ON_DBL_MIN)
      {
        return ON_PlaneEquation(x / dd, y / dd, z / dd, d / dd);
      }

      if (dd > 0.0)
      {
        // This code is rarely used and can be slow.
        // It multiplies by 2^1023 in an attempt to 
        // normalize the coordinates.
        // If the renormalization works, then we're
        // ok.  If the renormalization fails, we
        // return false.
        ON_PlaneEquation tmp(
          x*8.9884656743115795386465259539451e+307,
          y*8.9884656743115795386465259539451e+307,
          z*8.9884656743115795386465259539451e+307,
          d*8.9884656743115795386465259539451e+307
          );
        dd = tmp.DirectionLength();
        if (ON_IS_FINITE(dd) && dd > ON_DBL_MIN)
        {
          return ON_PlaneEquation(tmp.x / dd, tmp.y / dd, tmp.z / dd, tmp.d / dd);
        }
      }
    }
  }
  else if ( d == ON_UNSET_VALUE )
  {
    ON_3dVector v = Direction();
    if (v.IsValid() && v.Unitize())
    {
      return ON_PlaneEquation(v.x, v.y, v.z, ON_UNSET_VALUE);
    }
  }

  return ON_PlaneEquation::ZeroPlaneEquation;
}

bool ON_PlaneEquation::IsValid() const
{
  return ( ON_IS_VALID(x) && ON_IS_VALID(y) && ON_IS_VALID(z) && ON_IS_VALID(d) );
}

bool ON_PlaneEquation::IsSet() const
{
  return ( ON_IS_VALID(x) && ON_IS_VALID(y) && ON_IS_VALID(z) && ON_IS_VALID(d) 
           && (0.0 != x || 0.0 != y || 0.0 != z) 
         );
}

bool ON_PlaneEquation::IsUnitized() const
{
  return (IsSet() && ON_3dVector(x, y, z).IsUnitVector()) ? true : false;
}

ON_3dVector ON_PlaneEquation::Direction() const
{
  return ON_3dVector(x, y, z);
}

double ON_PlaneEquation::DirectionLength() const
{
  return ((const ON_3dVector*)&x)->Length();
}


ON_3dVector ON_PlaneEquation::UnitNormal() const
{
  ON_3dVector normal(x, y, z);
  if (false == normal.IsUnitVector() && false == normal.Unitize())
    normal = ON_3dVector::ZeroVector;
  return normal;
}

int ON_PlaneEquation::IsParallelTo(const ON_PlaneEquation& other, double angle_tolerance /*= ON_DEFAULT_ANGLE_TOLERANCE*/) const
{
	return ON_3dVector(x, y, z).IsParallelTo(ON_3dVector(other.x, other.y, other.z), angle_tolerance);
}

double ON_PlaneEquation::ZeroTolerance() const
{
  double zero_tolerance = 0.0;
  ON_3dVector N(x,y,z);
  if ( N.Unitize() && ON_IS_VALID(d) )
  {
    const ON_3dPoint P( -d*N.x, -d*N.y, -d*N.z  );

    zero_tolerance = fabs(ValueAt(P));

    ON_3dVector X;
    X.PerpendicularTo(N);
    X.Unitize();
    
    double t = fabs(ValueAt(P+X));
    if ( t > zero_tolerance )
      zero_tolerance = t;
    t = fabs(ValueAt(P-X));
    if ( t > zero_tolerance )
      zero_tolerance = t;
    t = fabs(ValueAt(P+d*X));
    if ( t > zero_tolerance )
      zero_tolerance = t;
    t = fabs(ValueAt(P-d*X));
    if ( t > zero_tolerance )
      zero_tolerance = t;

    ON_3dVector Y = ON_CrossProduct(N,X);
    Y.Unitize();

    t = fabs(ValueAt(P+Y));
    if ( t > zero_tolerance )
      zero_tolerance = t;
    t = fabs(ValueAt(P-Y));
    if ( t > zero_tolerance )
      zero_tolerance = t;
    t = fabs(ValueAt(P+d*Y));
    if ( t > zero_tolerance )
      zero_tolerance = t;
    t = fabs(ValueAt(P-d*Y));
    if ( t > zero_tolerance )
      zero_tolerance = t;
  }

  return zero_tolerance;
}

bool ON_PlaneEquation::Transform( const ON_Xform& xform )
{
  bool rc = IsValid();
  if ( rc )
  {
    // Apply the inverse transpose to the equation parameters
    ON_Xform T(xform);
    rc = T.Invert();
    if ( rc )
    {
      const double xx=x;
      const double yy=y;
      const double zz=z;
      const double dd=d;
      x = T.m_xform[0][0]*xx + T.m_xform[1][0]*yy + T.m_xform[2][0]*zz + T.m_xform[3][0]*dd;
      y = T.m_xform[0][1]*xx + T.m_xform[1][1]*yy + T.m_xform[2][1]*zz + T.m_xform[3][1]*dd;
      z = T.m_xform[0][2]*xx + T.m_xform[1][2]*yy + T.m_xform[2][2]*zz + T.m_xform[3][2]*dd;
      d = T.m_xform[0][3]*xx + T.m_xform[1][3]*yy + T.m_xform[2][3]*zz + T.m_xform[3][3]*dd;
    }
  }
  return rc;
}

double ON_PlaneEquation::ValueAt(ON_3dPoint P) const
{
  return (x*P.x + y*P.y + z*P.z + d);
}

double ON_PlaneEquation::ValueAt(ON_4dPoint P) const
{
  return (x*P.x + y*P.y + z*P.z + d*P.w);
}

double ON_PlaneEquation::ValueAt(ON_3dVector P) const
{
  return (x*P.x + y*P.y + z*P.z + d);
}

double ON_PlaneEquation::ValueAt(double xx, double yy, double zz) const
{
  return (x*xx + y*yy + z*zz + d);
}

double* ON_PlaneEquation::ValueAt(
      int Pcount,
      const ON_3fPoint* P,
      double* value,
      double value_range[2]
      ) const
{
  if ( Pcount <= 0 || 0 == P )
    return 0;

  int i;
  double s;
  const double* e = &x;

  if ( 0 == value )
    value =  (double*)onmalloc(Pcount * sizeof(*value) );
  if ( 0 == value )
    return 0;

  if ( 0 != value_range )
  {
    value[0] = s = e[0]*((double)P[0].x) + e[1]*((double)P[0].y) + e[2]*((double)P[0].z) + e[3];
    value_range[0] = s;
    value_range[1] = s;
    for ( i = 1; i < Pcount; i++ )
    {
      value[i] = s = e[0]*((double)P[i].x) + e[1]*((double)P[i].y) + e[2]*((double)P[i].z) + e[3];
      if ( s < value_range[0] )
        value_range[0] = s;
      else if ( s > value_range[1] )
        value_range[1] = s;
    }
  }
  else
  {
    for ( i = 0; i < Pcount; i++ )
    {
      value[i] = e[0]*((double)P[i].x) + e[1]*((double)P[i].y) + e[2]*((double)P[i].z) + e[3];
    }
  }

  return value;
}

double* ON_PlaneEquation::ValueAt(
      int Pcount,
      const ON_3dPoint* P,
      double* value,
      double value_range[2]
      ) const
{
  if ( Pcount <= 0 || 0 == P )
    return 0;

  int i;
  double s;
  const double* e = &x;

  if ( 0 == value )
    value =  (double*)onmalloc(Pcount * sizeof(*value) );
  if ( 0 == value )
    return 0;

  if ( 0 != value_range )
  {
    value[0] = s = e[0]*(P[0].x) + e[1]*(P[0].y) + e[2]*(P[0].z) + e[3];
    value_range[0] = s;
    value_range[1] = s;
    for ( i = 1; i < Pcount; i++ )
    {
      value[i] = s = e[0]*(P[i].x) + e[1]*(P[i].y) + e[2]*(P[i].z) + e[3];
      if ( s < value_range[0] )
        value_range[0] = s;
      else if ( s > value_range[1] )
        value_range[1] = s;
    }
  }
  else
  {
    for ( i = 0; i < Pcount; i++ )
    {
      value[i] = e[0]*(P[i].x) + e[1]*(P[i].y) + e[2]*(P[i].z) + e[3];
    }
  }

  return value;
}

ON_Interval ON_PlaneEquation::ValueRange(
  size_t point_list_count,
  const ON_3dPoint* point_list
  ) const
{
  ON_3dPointListRef vertex_list;
  vertex_list.SetFromDoubleArray(point_list_count,3,(const double*)point_list);
  return ValueRange(vertex_list);
}

ON_Interval ON_PlaneEquation::ValueRange(
  const ON_SimpleArray< ON_3dPoint >& point_list
  ) const
{
  return ValueRange(point_list.UnsignedCount(),point_list.Array());
}

ON_Interval ON_PlaneEquation::ValueRange(
  size_t point_list_count,
  const ON_3fPoint* point_list
  ) const
{
  ON_3dPointListRef vertex_list;
  vertex_list.SetFromFloatArray(point_list_count,3,(const float*)point_list);
  return ValueRange(vertex_list);
}

ON_Interval ON_PlaneEquation::ValueRange(
  const ON_SimpleArray< ON_3fPoint >& point_list
  ) const
{
  return ValueRange(point_list.UnsignedCount(),point_list.Array());
}

ON_Interval ON_PlaneEquation::ValueRange(
  const class ON_3dPointListRef& point_list
  ) const
{
  return ValueRange(point_list.PointCount(),0,point_list);
}


ON_Interval ON_PlaneEquation::ValueRange(
  size_t point_index_count,
  const unsigned int* point_index_list,
  const class ON_3dPointListRef& point_list
  ) const
{
  size_t point_index_stride = 1;

  return ValueRange(
    point_index_count,
    point_index_stride,
    point_index_list,
    point_list
    );
}

ON_Interval ON_PlaneEquation::ValueRange(
  size_t point_index_count,
  size_t point_index_stride,
  const unsigned int* point_index_list,
  const class ON_3dPointListRef& point_list
  ) const
{
  ON_Interval value_interval(ON_Interval::EmptyInterval);

  for(;;)
  {
    if ( false == IsValid() )
      break; // invalid plane equation;

    double h;
    const unsigned int vertex_count = point_list.PointCount();
    if ( 0 == vertex_count )
      break;
    const unsigned int point_count = (point_index_count > 0 && point_index_count < (size_t)ON_UNSET_UINT_INDEX)
                                   ? ((unsigned int)point_index_count)
                                   : 0;
    if ( 0 == point_count )
      break;

    if ( 0 != point_index_list )
    {
      const unsigned int point_stride = (point_index_stride > 0 && point_index_stride < (size_t)ON_UNSET_UINT_INDEX)
                                      ? ((unsigned int)point_index_stride)
                                      : 0;
      if ( 0 == point_stride )
        break;
      for ( unsigned int i = 0; i < point_count*point_stride; i += point_stride )
      {
        unsigned int j = point_index_list[i];
        if ( j >= vertex_count )
          continue;
        h = ValueAt(point_list[j]);
        if ( ON_IsValid(h) )
        {
          value_interval.Set(h,h);
          for (i++; i < point_count*point_stride; i+= point_stride )
          {
            unsigned int j_local = point_index_list[i];
            if ( j_local >= vertex_count )
              continue;
            h = ValueAt(point_list[j_local]);
            if ( ON_IsValid(h) )
            {
              if ( h < value_interval.m_t[0] )
                value_interval.m_t[0] = h;
              else if ( h > value_interval.m_t[1] )
                value_interval.m_t[1] = h;
            }
          }
          break;
        }
      }
    }
    else if ( point_count <= vertex_count )
    {
      for ( unsigned int i = 0; i < point_count; i++ )
      {        
        h = ValueAt(point_list[i]);
        if ( ON_IsValid(h) )
        {
          value_interval.Set(h,h);
          for (i++; i < point_count; i++ )
          {
            h = ValueAt(point_list[i]);
            if ( ON_IsValid(h) )
            {
              if ( h < value_interval.m_t[0] )
                value_interval.m_t[0] = h;
              else if ( h > value_interval.m_t[1] )
                value_interval.m_t[1] = h;
            }
          }
          break;
        }
      }
    }

    break;
  }
  return value_interval;
}

ON_3dPoint ON_PlaneEquation::ClosestPointTo( ON_3dPoint P ) const
{
  const double t = -(x*P.x + y*P.y + z*P.z + d)/(x*x+y*y+z*z);
  return ON_3dPoint( P.x + t*x, P.y + t*y, P.z + t*z);
}

double ON_PlaneEquation::MinimumValueAt(const ON_BoundingBox& bbox) const
{
  double xx, yy, zz, s;

  s = x*bbox.m_min.x;
  if ( s < (xx = x*bbox.m_max.x) ) xx = s;

  s = y*bbox.m_min.y;
  if ( s < (yy = y*bbox.m_max.y) ) yy = s;

  s = z*bbox.m_min.z;
  if ( s < (zz = z*bbox.m_max.z) ) zz = s;

  return (xx + yy + zz + d);
}

double ON_PlaneEquation::MaximumValueAt(const ON_BoundingBox& bbox) const
{
  double xx, yy, zz, s;

  s = x*bbox.m_min.x;
  if ( s > (xx = x*bbox.m_max.x) ) xx = s;

  s = y*bbox.m_min.y;
  if ( s > (yy = y*bbox.m_max.y) ) yy = s;

  s = z*bbox.m_min.z;
  if ( s > (zz = z*bbox.m_max.z) ) zz = s;

  return (xx + yy + zz + d);
}


double ON_PlaneEquation::MaximumAbsoluteValueAt(
  bool bRational,
  int point_count,
  int point_stride,
  const double* points,
  double stop_value
  ) const
{
  double value, max_value, w;

  if (    point_count < 1 
       || point_stride < (bRational?4:3) 
       || 0 == points
       )
  {
    return ON_UNSET_VALUE;
  }

  if ( ON_IsValid(stop_value) )
  {
    if ( bRational )
    {
      w = points[3];
      w = (0.0 != w) ? 1.0/w : 1.0;
      max_value = fabs(x*w*points[0]+y*w*points[1]+z*w*points[2]+points[3]);
      if ( max_value > stop_value )
        return max_value;
      for(point_count--; point_count--; /*empty iterator*/ )
      {
        points += point_stride;
        w = points[3];
        w = (0.0 != w) ? 1.0/w : 1.0;
        value = fabs(x*w*points[0]+y*w*points[1]+z*w*points[2]+points[3]);
        if ( value > max_value )
        {
          if ( (max_value = value) > stop_value )
            return max_value;
        }
      }
    }
    else
    {
      max_value = fabs(x*points[0]+y*points[1]+z*points[2]+d);
      if ( max_value > stop_value )
        return max_value;
      for(point_count--; point_count--; /*empty iterator*/ )
      {
        points += point_stride;
        value = fabs(x*points[0]+y*points[1]+z*points[2]+d);
        if ( value > max_value )
        {
          if ( (max_value = value) > stop_value )
            return max_value;
        }
      }
    }
  }
  else
  {
    if ( bRational )
    {
      w = points[3];
      w = (0.0 != w) ? 1.0/w : 1.0;
      max_value = fabs(x*w*points[0]+y*w*points[1]+z*w*points[2]+points[3]);
      for(point_count--; point_count--; /*empty iterator*/ )
      {
        points += point_stride;
        w = points[3];
        w = (0.0 != w) ? 1.0/w : 1.0;
        value = fabs(x*w*points[0]+y*w*points[1]+z*w*points[2]+points[3]);
        if ( value > max_value )
          max_value = value;
      }
    }
    else
    {
      max_value = fabs(x*points[0]+y*points[1]+z*points[2]+d);
      for(point_count--; point_count--; /*empty iterator*/ )
      {
        points += point_stride;
        value = fabs(x*points[0]+y*points[1]+z*points[2]+d);
        if ( value > max_value )
          max_value = value;
      }
    }
  }

  return max_value;
}

double ON_PlaneEquation::MaximumValueAt(
  bool bRational,
  int point_count,
  int point_stride,
  const double* points,
  double stop_value
  ) const
{
  double value, max_value, w;

  if (    point_count < 1 
       || point_stride < (bRational?4:3) 
       || 0 == points
       )
  {
    return ON_UNSET_VALUE;
  }

  if ( ON_IsValid(stop_value) )
  {
    if ( bRational )
    {
      w = points[3];
      w = (0.0 != w) ? 1.0/w : 1.0;
      max_value = x*w*points[0]+y*w*points[1]+z*w*points[2]+points[3];
      if ( max_value > stop_value )
        return max_value;
      for(point_count--; point_count--; /*empty iterator*/ )
      {
        points += point_stride;
        w = points[3];
        w = (0.0 != w) ? 1.0/w : 1.0;
        value = x*w*points[0]+y*w*points[1]+z*w*points[2]+points[3];
        if ( value > max_value )
        {
          if ( (max_value = value) > stop_value )
            return max_value;
        }
      }
    }
    else
    {
      max_value = x*points[0]+y*points[1]+z*points[2]+d;
      if ( max_value > stop_value )
        return max_value;
      for(point_count--; point_count--; /*empty iterator*/ )
      {
        points += point_stride;
        value = x*points[0]+y*points[1]+z*points[2]+d;
        if ( value > max_value )
        {
          if ( (max_value = value) > stop_value )
            return max_value;
        }
      }
    }
  }
  else
  {
    if ( bRational )
    {
      w = points[3];
      w = (0.0 != w) ? 1.0/w : 1.0;
      max_value = x*w*points[0]+y*w*points[1]+z*w*points[2]+points[3];
      for(point_count--; point_count--; /*empty iterator*/ )
      {
        points += point_stride;
        w = points[3];
        w = (0.0 != w) ? 1.0/w : 1.0;
        value = x*w*points[0]+y*w*points[1]+z*w*points[2]+points[3];
        if ( value > max_value )
          max_value = value;
      }
    }
    else
    {
      max_value = x*points[0]+y*points[1]+z*points[2]+d;
      for(point_count--; point_count--; /*empty iterator*/ )
      {
        points += point_stride;
        value = x*points[0]+y*points[1]+z*points[2]+d;
        if ( value > max_value )
          max_value = value;
      }
    }
  }

  return max_value;
}

double ON_PlaneEquation::MinimumValueAt(
  bool bRational,
  int point_count,
  int point_stride,
  const double* points,
  double stop_value
  ) const
{
  double value, min_value, w;

  if (    point_count < 1 
       || point_stride < (bRational?4:3) 
       || 0 == points
       )
  {
    return ON_UNSET_VALUE;
  }

  if ( ON_IsValid(stop_value) )
  {
    if ( bRational )
    {
      w = points[3];
      w = (0.0 != w) ? 1.0/w : 1.0;
      min_value = x*w*points[0]+y*w*points[1]+z*w*points[2]+points[3];
      if ( min_value < stop_value )
        return min_value;
      for(point_count--; point_count--; /*empty iterator*/ )
      {
        points += point_stride;
        w = points[3];
        w = (0.0 != w) ? 1.0/w : 1.0;
        value = x*w*points[0]+y*w*points[1]+z*w*points[2]+points[3];
        if ( value < min_value )
        {
          if ( (min_value = value) < stop_value )
            return min_value;
        }
      }
    }
    else
    {
      min_value = x*points[0]+y*points[1]+z*points[2]+d;
      if ( min_value < stop_value )
        return min_value;
      for(point_count--; point_count--; /*empty iterator*/ )
      {
        points += point_stride;
        value = x*points[0]+y*points[1]+z*points[2]+d;
        if ( value < min_value )
        {
          if ( (min_value = value) < stop_value )
            return min_value;
        }
      }
    }
  }
  else
  {
    if ( bRational )
    {
      w = points[3];
      w = (0.0 != w) ? 1.0/w : 1.0;
      min_value = x*w*points[0]+y*w*points[1]+z*w*points[2]+points[3];
      for(point_count--; point_count--; /*empty iterator*/ )
      {
        points += point_stride;
        w = points[3];
        w = (0.0 != w) ? 1.0/w : 1.0;
        value = x*w*points[0]+y*w*points[1]+z*w*points[2]+points[3];
        if ( value < min_value )
          min_value = value;
      }
    }
    else
    {
      min_value = x*points[0]+y*points[1]+z*points[2]+d;
      for(point_count--; point_count--; /*empty iterator*/ )
      {
        points += point_stride;
        value = x*points[0]+y*points[1]+z*points[2]+d;
        if ( value < min_value )
          min_value = value;
      }
    }
  }

  return min_value;
}


bool ON_PlaneEquation::IsNearerThan( 
        const ON_BezierCurve& bezcrv,
        double s0,
        double s1,
        int sample_count,
        double endpoint_tolerance,
        double interior_tolerance,
        double* smin,
        double* smax
        ) const
{
  int i, n;
  double smn, smx, vmn, vmx, s, v, w;
  ON_3dPoint P;
  P.z = 0.0; // for 2d curves

  sample_count--;
  s = 0.5*(s0+s1);
  bezcrv.Evaluate(s,0,3,&P.x);
  vmn = vmx = x*P.x + y*P.y + z*P.z + d;
  smn = smx = s;
  if ( vmn > interior_tolerance )
  {
    if ( smin )
      *smin = s;
    if ( smax )
      *smax = s;
    return false;
  }

  if ( endpoint_tolerance >= 0.0 )
  {
    bezcrv.Evaluate(s0,0,3,&P.x);
    v = x*P.x + y*P.y + z*P.z + d;
    if (v > endpoint_tolerance )
    {
      if ( smin )
        *smin = smn;
      if ( smax )
        *smax = s0;
      return false;
    }
    if ( v < vmn ) { vmn = v; smn = s0; } else if (v > vmx) { vmx = v; smx = s0; }

    bezcrv.Evaluate(s1,0,3,&P.x);
    v = x*P.x + y*P.y + z*P.z + d;
    if (v > endpoint_tolerance )
    {
      if ( smin )
        *smin = smn;
      if ( smax )
        *smax = s1;
      return false;
    }
    if ( v < vmn ) { vmn = v; smn = s1; } else if (v > vmx) { vmx = v; smx = s1; }
  }

  w = 0.5;
  for ( n = 4; sample_count > 0; n *= 2 )
  {
    w *= 0.5;
    for ( i = 1; i < n; i+= 2 ) // do not test sample_count here
    {
      s = w*i;
      s = (1.0-s)*s0 + s*s1;
      bezcrv.Evaluate(s,0,3,&P.x);
      v = x*P.x + y*P.y + z*P.z + d;

      if ( v < vmn ) 
      { 
        vmn = v; 
        smn = s; 
      } 
      else if (v > vmx) 
      { 
        vmx = v; 
        smx = s; 
        if ( vmx > interior_tolerance )
        {
          if ( smin )
            *smin = smn;
          if ( smax )
            *smax = s;
          return false;
        }
      }

      sample_count--;
    }
  }

  if ( smin )
    *smin = smn;
  if ( smax )
    *smax = smx;
  return true;
}

bool ON_PlaneEquation::operator==( const ON_PlaneEquation& eq ) const
{
  return (x==eq.x && y==eq.y && z==eq.z && d==eq.d)?true:false;
}

bool ON_PlaneEquation::operator!=( const ON_PlaneEquation& eq ) const
{
  return (x!=eq.x || y!=eq.y || z!=eq.z || d!=eq.d)?true:false;
}

const ON_PlaneEquation operator*(const ON_Xform& xform, const ON_PlaneEquation& e)
{
  ON_PlaneEquation xe(e);
  xe.Transform(xform);
  return xe;
}

// Find the maximum absolute value of a array of (possibly homogeneous) points 
double ON_MaximumCoordinate(const double* data, int dim, bool is_rat, int count)
{
  return ON_MaximumCoordinate(data, dim, is_rat, count, dim + is_rat);
}

// Find the maximum absolute value of an array with stride of (possibly homogeneous) points 
double ON_MaximumCoordinate(const double* data, int dim, bool is_rat, int count, int stride)
{
  double norm = 0;
  if (is_rat)
  {
    for (int i = 0; i < count; i++)
    {
      double w = fabs(data[i*stride + dim ]);
      double norm_i = 0;
      for (int j = 0; j < dim; j++)
        norm_i = ON_Max(norm_i, fabs(data[i*stride + j]));
      if (norm_i > norm * w && w>0)
        norm = norm_i / w;
    }
  }
  else
  {
    for (int i = 0; i < count; i++)
      for (int j=0; j<dim; j++)
        norm = ON_Max(norm, fabs(data[i*stride + j]));
  }
  return norm;
}

int ON_Get3dConvexHull( 
          const ON_SimpleArray<ON_3dPoint>& points, 
          ON_SimpleArray<ON_PlaneEquation>& hull 
          )
{
  // This is a slow and stupid way to get the convex hull.
  // It works for small point sets.  If you need something
  // that is efficient, look elsewhere.

  const int point_count = points.Count();
  if ( point_count < 3 )
    return 0;

  const int count0 = hull.Count();
  hull.Reserve(count0+4);

  int i,j,k,n;
  ON_3dPoint A,B,C;
  ON_PlaneEquation e;
  double d0,d1,h0,h1,d;
  bool bGoodSide;
  for ( i = 0; i < point_count; i++ )
  {
    A = points[i];
    for ( j = i+1; j < point_count; j++ )
    {
      B = points[j];
      for (k = j+1; k < point_count; k++ )
      {
        C = points[k];
        ON_3dVector* v = (ON_3dVector*)&e.x;
        v->operator=(ON_CrossProduct(B-A,C-A));
        if ( !v->Unitize() )
          continue;
        e.d = -(A.x*e.x + A.y*e.y + A.z*e.z);
        d0 = d1 = e.ValueAt(A);
        d = e.ValueAt(B); if ( d < d0 ) d0 = d; else if (d > d1) d1 = d;
        d = e.ValueAt(C); if ( d < d0 ) d0 = d; else if (d > d1) d1 = d;
        if ( d0 > -ON_ZERO_TOLERANCE )
          d0 = -ON_ZERO_TOLERANCE;
        if ( d1 < ON_ZERO_TOLERANCE )
          d1 = ON_ZERO_TOLERANCE;

        h0 = 0.0; h1 = 0.0;

        bGoodSide = true;
        for ( n = 0; n < point_count && bGoodSide; n++ )
        {
          d = e.ValueAt(points[n]);
          if ( d < h0 )
          {
            h0 = d;
            bGoodSide = (d0 <= h0 || h1 <= d1);
          }
          else if ( d > h1 )
          {
            h1 = d;
            bGoodSide = (d0 <= h0 || h1 <= d1);
          }
        }

        if ( bGoodSide )
        {
          if ( h1 <= d1 )
          {
            // all points are "below" the plane
            if ( d0 <= h0  )
            {
              // all points are also "above" the plane,
              hull.SetCount(count0);
              ON_PlaneEquation& e0 = hull.AppendNew();
              e0.x = -e.x;
              e0.y = -e.y;
              e0.z = -e.z;
              e0.d = -(e.d-h0);
            }
            ON_PlaneEquation& e1 = hull.AppendNew();
            e1.x = e.x;
            e1.y = e.y;
            e1.z = e.z;
            e1.d = (e.d-h1);
            if ( d0 <= h0  )
            {
              // points are (nearly) planar
              return 2;
            }
          }
          else if ( d0 <= h0  )
          {
            // all points are "above" the plane
            ON_PlaneEquation& e0 = hull.AppendNew();
            e0.x = -e.x;
            e0.y = -e.y;
            e0.z = -e.z;
            e0.d = -(e.d-h0);
          }
        }
      }
    }
  }

  if ( hull.Count() < count0 + 4 )
    hull.SetCount(count0);

  return hull.Count() - count0;
}


bool ON_IsDegenrateConicHelper(double A, double B, double C, double D, double E)
{
  //
  // The conic is degenerate (lines and/or points) if the 
  //
  //     A   B/2 D/2
  //     B/2 C   E/2
  //     D/2 E/2 F
  //
  // has rank < 3
  // (F = 0 in our case here.)

  // zero_tol was tuned by 
  //  1) testing sets of equally spaced collinear
  //     points with coordinate sizes ranging from 0.001 to 1.0e4 and
  //     segment lengths from 0.001 to 1000.0.
  //  2) testing ellipses with axes lengths ranging from 0.001 to 1000
  //     where the major/minor ration <= 2000 and the centers had coordinates
  //     from 0.001 to 1.0e4.
  //  Do not change zero_tol without extensive testing.
  const double zero_tol = 1.0e-9;

  double x, y;
  double M[3][3];
  int i0, i1, i2;

  // scale matrix coefficients so largest is 1 to
  // make checking for a zero pivot easier.
  x = fabs(A);
  if ( x < (y=fabs(B)) ) x = y;
  if ( x < (y=fabs(C)) ) x = y;
  if ( x < (y=fabs(D)) ) x = y;
  if ( x < (y=fabs(E)) ) x = y;
  if ( x <= 1.0e-12 )
    return true; // rank 0

  x = 1.0/x;

  // set up matrix
  M[0][0] = x*A;
  M[1][1] = x*C;
  x *= 0.5;
  M[0][1] = M[1][0] = x*B;
  M[0][2] = M[2][0] = x*D;
  M[1][2] = M[2][1] = x*E;
  M[2][2] = 0.0;

  // since M is symmetric, just use partial pivoting

  // get first pivot ic column M[][0]
  i0 = 0;
  x = fabs(M[0][0]);
  if ( x < (y=fabs(M[1][0])) ) {x=y;i0=1;}
  if ( x < (y=fabs(M[2][0])) ) {x=y;i0=2;}
  if ( x <= zero_tol )
    return true; // rank 0

  // first pivot row reduction
  x = 1.0/M[i0][0]; 
  M[i0][1] *= x; 
  M[i0][2] *= x;
  i1 = (i0+1)%3;
  if ( 0.0 != (y = -M[i1][0]) )
  {
    M[i1][1] += y*M[i0][1];
    M[i1][2] += y*M[i0][2];
  }
  i2 = (i0+2)%3;
  if ( 0.0 != (y = -M[i2][0]) )
  {
    M[i2][1] += y*M[i0][1]; 
    M[i2][2] += y*M[i0][2];
  }

  // get second pivot in column M[][1]
  if ( fabs(M[i1][1]) < fabs(M[i2][1]) )
  {
    i1 = i2;
    i2 = (i0+1)%3;
  }
  if ( fabs(M[i1][1]) <= zero_tol )
    return true; // rank 1

  // second pivot row reduction
  x = 1.0/M[i1][1]; 
  M[i1][2] *= x;
  if ( 0.0 != (y = -M[i2][1]) )
    M[i2][2] += y*M[i1][2];

  // test third and final pivot
  if ( fabs(M[i2][2]) <= zero_tol )
    return true;  // rank 2

  return false;
}

bool ON_GetConicEquationThrough6Points( 
        int stride, 
        const double* points2d, 
        double conic[6],
        double* max_pivot,
        double* min_pivot,
        double* zero_pivot
        )
{
  // Sets conic[] to the coefficients = (A,B,C,D,E,F),
  // such that A*x*x + B*x*y + C*y*y + D*x + E*y + F = 0
  // for each of the 6 input points.

  // This code is long and ugly.  The reason for unrolling the 
  // obvious loops is to make it as efficient as possible.  
  // Rhino calls this function in time critical situations.
  //

  ON_2dPoint pts[6], bboxmin, bboxmax;
  double scale, x, y, M[5][5], N[5][5], max_piv, min_piv;
  const double* p;
  int i, j, k;

  if ( 0 == conic )
    return false;
  memset(conic,0,6*sizeof(conic[0]));
  if ( max_pivot )
    *max_pivot = 0.0;
  if ( min_pivot )
    *min_pivot = 0.0;
  if ( zero_pivot )
    *zero_pivot = 0.0;

  // copy input points into pts[6] and calculate bounding box
  bboxmin.x = bboxmax.x = pts[0].x = points2d[0];
  bboxmin.y = bboxmax.y = pts[0].y = points2d[1];
  if ( !pts[0].IsValid() )
    return false;
  for ( i = 1; i < 6; i++ )
  {
    points2d += stride;
    pts[i].x = points2d[0];
    pts[i].y = points2d[1];
    if ( !pts[i].IsValid() )
      return false;
    if ( pts[i].x < bboxmin.x ) bboxmin.x = pts[i].x; 
    else if ( pts[i].x > bboxmax.x ) bboxmax.x = pts[i].x;
    if ( pts[i].y < bboxmin.y ) bboxmin.y = pts[i].y; 
    else if ( pts[i].y > bboxmax.y ) bboxmax.y = pts[i].y;
  }

  // translate and scale pts[] so pts[5] is at the origin and
  // (pts[0],...pts[4]) have and have a "diameter" near 1.
  // This keeps the starting coefficients in M[][] less than 5
  // with the largest generally near one.
  x = bboxmax.x-bboxmin.x;
  y = bboxmax.y-bboxmin.y;
  if ( x >= y )
  {
    if ( x > 0.0 )
    {
      y /= x;
      scale = x*sqrt(1.0 + y*y);
    }
    else
      return false;
  }
  else 
  {
    x /= y;
    scale = y*sqrt(1.0 + x*x);
  }
  if ( scale > 0.0 )
    scale = 1.0/scale;
  else
    return false;

  for ( i = 0; i < 5; i++ )
  {
    x = scale*(pts[i].x - pts[5].x);
    y = scale*(pts[i].y - pts[5].y);
    M[i][0] = x*x;
    M[i][1] = x*y;
    M[i][2] = y*y;
    M[i][3] = x;
    M[i][4] = y;
  }

  memset( N,0,sizeof(N) );
  N[0][0] = N[1][1] = N[2][2] = N[3][3] = N[4][4] = 1.0;

  // The conic (A,B,C,D,E) is the kernel of M.

  //////////////////////////////////////////////////////////
  //
  // find first pivot
  //
  j = 0;
  p = &M[0][0];
  x = fabs(*p);
  for ( i = 1; i < 25; i++ )
  {
    if ( x < (y = fabs(*(++p))) )
    {
      x = y;
      j = i;
    }
  }
  max_piv = min_piv = x;
  if ( 0.0 == x )
    return false; // all input points are equal
  i = j/5;
  j %= 5;

  if ( 0 != i )
  {
    // swap rows M[0][] and M[i][]
    // Do not modify N because row ops act on the left of M.
    for ( k = 0; k < 5; k++ )
    {
      y = M[0][k]; M[0][k] = M[i][k]; M[i][k] = y;
    }
  }
  if ( 0 != j )
  {
    // Swap columns M[][0] and M[][j]
    // Also swap N[][] columns because column swap
    // matrix acts on the right of M.
    for ( k = 0; k < 5; k++ )
    {
      y = M[k][0]; M[k][0] = M[k][j]; M[k][j] = y;
      y = N[k][0]; N[k][0] = N[k][j]; N[k][j] = y;
    }
  }

  // scale row M[0][] so that M[0][0] = 1.
  // Do not modify N because row ops act on the left of M.
  x = 1.0/M[0][0];
  M[0][0] = 1.0; 
  M[0][1] *= x; M[0][2] *= x; M[0][3] *= x; M[0][4] *= x;

  // kill column M[1,2,3,4][0]
  for ( i = 1; i < 5; i++)
  {
    if ( 0.0 != (y = -M[i][0]) )
    {
      // use row op M[i][] += y*M[0][]
      // Do not modify N because row ops act on the left of M.
      M[i][0] = 0.0; // set to zero so search for pivot is faster
      M[i][1] += y*M[0][1]; M[i][2] += y*M[0][2]; M[i][3] += y*M[0][3]; M[i][4] += y*M[0][4];
    }
  }


  //////////////////////////////////////////////////////////
  //
  // find second pivot
  //
  j = 6;
  p = &M[1][1];
  x = fabs(*p);
  for ( i = 7; i < 25; i++ )
  {
    if ( x < (y = fabs(*(++p))) )
    {
      x = y;
      j = i;
    }
  }
  if ( x > max_piv ) max_piv = x; else if ( x < min_piv ) min_piv = x;
  if ( 0.0 == x )
  {
    if ( 0 != max_pivot )
      *max_pivot = max_piv;
    return false; // two distinct points in input point list.
  }
  i = j/5;  // should always be >= 1
  j %= 5;   // should always be >= 1

  if ( i > 1 )
  {
    // swap rows M[1][] and M[i][]
    // Do not modify N because row ops act on the left of M.
    for ( k = 1; k < 5; k++ )
    {
      y = M[1][k]; M[1][k] = M[i][k]; M[i][k] = y;
    }
  }
  if ( j > 1 )
  {
    // Swap columns M[][1] and M[][j]
    // Also swap N[][] columns because column swap
    // matrix acts on the right of M.
    for ( k = 0; k < 5; k++ )
    {
      y = M[k][1]; M[k][1] = M[k][j]; M[k][j] = y;
      y = N[k][1]; N[k][1] = N[k][j]; N[k][j] = y;
    }
  }

  // scale row M[1][] so that M[1][1] = 1.
  // Do not modify N because row ops act on the left of M.
  x = 1.0/M[1][1];
  M[1][1] = 1.0; 
  M[1][2] *= x; M[1][3] *= x; M[1][4] *= x;

  // kill column M[2,3,4][1]
  for ( i = 2; i < 5; i++)
  {
    if ( 0.0 != (y = -M[i][1]) )
    {
      // use row op M[i][] += y*M[0][]
      // Do not modify N because row ops act on the left of M.
      M[i][1] = 0.0; // set to zero so search for pivot is faster
      M[i][2] += y*M[1][2]; M[i][3] += y*M[1][3]; M[i][4] += y*M[1][4];
    }
  }


  //////////////////////////////////////////////////////////
  //
  // find third pivot
  //
  j = 12;
  p = &M[2][2];
  x = fabs(*p);
  for ( i = 13; i < 25; i++ )
  {
    if ( x < (y = fabs(*(++p))) )
    {
      x = y;
      j = i;
    }
  }
  if ( x > max_piv ) max_piv = x; else if ( x < min_piv ) min_piv = x;
  if ( 0.0 == x )
  {
    if ( 0 != max_pivot )
      *max_pivot = max_piv;
    return false; // three distinct points in input point list.
  }
  i = j/5;  // should always be >= 2
  j %= 5;   // should always be >= 2

  if ( i > 2 )
  {
    // swap rows M[2][] and M[i][]
    // Do not modify N because row ops act on the left of M.
    for ( k = 2; k < 5; k++ )
    {
      y = M[2][k]; M[2][k] = M[i][k]; M[i][k] = y;
    }
  }
  if ( j > 2 )
  {
    // Swap columns M[][2] and M[][j]
    // Also swap N[][] columns because column swap
    // matrix acts on the right of M.
    for ( k = 0; k < 5; k++ )
    {
      y = M[k][2]; M[k][2] = M[k][j]; M[k][j] = y;
      y = N[k][2]; N[k][2] = N[k][j]; N[k][j] = y;
    }
  }

  // scale row M[2][] so that M[2][2] = 1.
  // Do not modify N because row ops act on the left of M.
  x = 1.0/M[2][2];
  M[2][2] = 1.0; M[2][3] *= x; M[2][4] *= x;

  // kill column M[3,4][2]
  for ( i = 3; i < 5; i++)
  {
    if ( 0.0 != (y = -M[i][2]) )
    {
      // use row op M[i][] += y*M[0][]
      // Do not modify N because row ops act on the left of M.
      M[i][2] = 0.0; // set to zero so search for pivot is faster
      M[i][3] += y*M[2][3]; M[i][4] += y*M[2][4];
    }
  }

  //////////////////////////////////////////////////////////
  //
  // find fourth pivot
  //
  i = j = 3;
  x = fabs(M[3][3]);
  if ( x < (y = fabs(M[3][4])) )
  {
    x = y; j = 4;
  }
  if ( x < (y = fabs(M[4][3])) )
  {
    x = y; i = 4; j = 3;
  }
  if ( x < (y = fabs(M[4][4])) )
  {
    x = y; i = j = 4;
  }
  if ( x > max_piv ) max_piv = x; else if ( x < min_piv ) min_piv = x;
  if ( 0.0 == x )
  {
    if ( 0 != max_pivot )
      *max_pivot = max_piv;
    return false; // four distinct points in the input point list.
  }

  if ( i > 3 )
  {
    // swap rows M[3][] and M[i][]
    // Do not modify N[][] because row ops act on the left of M.
    y = M[3][3]; M[3][3] = M[4][3]; M[4][3] = y;
    y = M[3][4]; M[3][4] = M[i][4]; M[4][4] = y;
  }
  if ( j > 3 )
  {
    // Swap columns M[][3] and M[][j]
    // Also swap N[][] columns because column swap
    // matrix acts on the right of M.
    for ( k = 0; k < 5; k++ )
    {
      y = M[k][3]; M[k][3] = M[k][4]; M[k][4] = y;
      y = N[k][3]; N[k][3] = N[k][4]; N[k][4] = y;
    }
  }

  // scale row M[3][] so that M[3][3] = 1.
  // Do not modify N because row ops act on the left of M.
  x = 1.0/M[3][3];
  M[3][3] = 1.0; 
  M[3][4] *= x;

  // kill column M[4][3]
  if ( 0.0 != M[4][3] )
  {
    // use row op M[i][] += y*M[3][]
    // Do not modify N because row ops act on the left of M.
    M[4][4] -= M[4][3]*M[3][4];
    M[4][3] = 0.0; // set to zero so search for pivot is faster
  }

  // By construction, M[][] is singular and M[4][4] should be nearly zero.
  // It should be upper triangular with diagonal 1,1,1,1,0-ish
  if ( max_pivot )
    *max_pivot = max_piv;
  if ( min_pivot )
    *min_pivot = max_piv;
  if ( zero_pivot )
    *zero_pivot = fabs(M[4][4]);

  // Use column operations to make M[][] the identity.
  // The operations must also be applied to N[][] in order to
  // calculate the kernel of the original M[][].
  for ( i = 0; i < 4; i++ )
  {
    for (j = i+1; j < 5; j++ )
    {
      if ( 0.0 != (y = -M[i][j]) )
      {
        // waste of time // M[i][j] = 0.0;
        for ( k = 0; k < 5; k++ )
        {
          //M[k][j] += y*M[k][i];
          N[k][j] += y*N[k][i];
        }
      }
    }
  }

  // At this point, M[][] should be reduced to a diagonal matrix with 
  // 1,1,1,1,0 on the diagonal. The vector (A,B,C,D,E) = N*Transpose(0,0,0,0,1)
  // will be in the kernel of the original M[][]. The conic through the 
  // six points( scale*(pts[0]-pts[5]),...,scale*(pts[4]-pts[5]),(0,0) ) 
  // is Ax^2 + Bxy + Cy^2 + Dx + Ey = 0.
  // We need to apply the inverse of the scale and then translate by 
  // (pts[5].x,pts[5].y) to get the equation of the conic through the 
  // input point list.

  double A = N[0][4];
  double B = N[1][4];
  double C = N[2][4];
  double D = N[3][4];
  double E = N[4][4];
  // F = 0

  // check for collinear point set
  if ( ON_IsDegenrateConicHelper(A,B,C,D,E) )
  {
    // points lie on one or two lines
    return false;
  }

  // points are not collinear

  // undo the scale we applied when we calculated M[][]
  x = scale*scale;
  A *= x;
  B *= x;
  C *= x;
  D *= scale;
  E *= scale;

  // undo the translation of pts[5] to (0,0) we applied when we calculated M[][]
  x = -pts[5].x;
  y = -pts[5].y;
  double F = A*x*x + B*x*y + C*y*y + D*x + E*y;
  D += 2.0*A*x + B*y;
  E += 2.0*C*y + B*x;

  if ( (fabs(A) >= fabs(C)) ? (A<0.0):(C<0.0) )
  {
    // Make the largest A/C coefficient positive.
    A = -A; B = -B; C = -C; D = -D; E = -E; F = -F;
  }

  conic[0] = A; conic[1] = B; conic[2] = C;
  conic[3] = D; conic[4] = E; conic[5] = F;

  //
  j = 0;
  x = fabs(conic[0]);
  for ( i = 0; i < 6; i++ )
  {
    if ( x < (y = fabs(conic[i])) )
    {
      x = y;
      j = i;
    }
  }
  if ( !(conic[j] != 0.0) )
    return false;
  y = 1.0/conic[j];
  conic[0] *= y; conic[1] *= y; conic[2] *= y; 
  conic[3] *= y; conic[4] *= y; conic[5] *= y; 
  conic[j] = 1.0;

  return true;
}

bool ON_IsConicEquationAnEllipse( 
        const double conic[6], 
        ON_2dPoint& center, 
        ON_2dVector& major_axis, 
        ON_2dVector& minor_axis, 
        double* major_radius, 
        double* minor_radius
        )
{
  double A, C, D, E, F, x0, y0;
  double X[2], Y[2], P[2];

  if (    !ON_IsValid(conic[0]) 
       || !ON_IsValid(conic[1]) 
       || !ON_IsValid(conic[2]) 
       || !ON_IsValid(conic[3]) 
       || !ON_IsValid(conic[4]) 
       || !ON_IsValid(conic[5]) 
     )
  {
    return false;
  }

  if ( fabs(conic[1]) > 1.0e-14*fabs(conic[0]+fabs(conic[2])) ) 
  {
    // "B" is non zero - remove "rotation" from conic equation
    const double alpha = 0.5*atan2(conic[1],conic[0]-conic[2]);
    const double s = sin(alpha);
    const double c = cos(alpha);
    X[0] =  c; X[1] = s;
    Y[0] = -s; Y[1] = c;

    A = conic[0]*c*c + conic[1]*c*s + conic[2]*s*s;
    // B = conic[1]*(c*c-s*s) + 2.0*(conic[2]-conic[0])*s*c; // (B = 0)
    C = conic[0]*s*s - conic[1]*c*s + conic[2]*c*c;
    D = conic[3]*c + conic[4]*s;
    E = conic[4]*c - conic[3]*s;
    // F = conic[5]; // F not changed by rotation
  }
  else
  {
    A = conic[0];
    // B = conic[1];
    C = conic[2];
    D = conic[3];
    E = conic[4];
    // F = conic[5]; 
    X[0] = 1.0; X[1] = 0.0;
    Y[0] = 0.0; Y[1] = 1.0;
  }

  F = conic[5];

  // the if (!(...)) insures we exit if A or C is a NaN
  if ( !((A > 0.0 && C > 0.0) || (A < 0.0 && C < 0.0)) )
    return false; // conic is not an ellipse 

  // set P = center
  x0 = -0.5*D/A;
  y0 = -0.5*E/C;
  P[0] = x0*X[0] + y0*Y[0];
  P[1] = x0*X[1] + y0*Y[1];

  // set A and C to ellipse axes lengths
  F = conic[5] -(A*x0*x0 + C*y0*y0);
  if ( !(0.0 != F) )
    return false; // F is 0.0 or a NaN

  // We know A and C have the same sign and F has the opposite sign.
  A = sqrt(-F/A);
  C = sqrt(-F/C);

  if ( A == C )
  {
    // circle
    major_axis.x = 1.0;
    major_axis.y = 0.0;
    minor_axis.x = 0.0;
    minor_axis.y = 1.0;
    *major_radius = A;
    *minor_radius = C;
  }
  else if ( A > C )
  {
    // X = major axis, Y = minor axis
    major_axis.x = X[0];
    major_axis.y = X[1];
    minor_axis.x = Y[0];
    minor_axis.y = Y[1];
    *major_radius = A;
    *minor_radius = C;
  }
  else if ( C > A )
  {
    // Y = major axis, -X = minor axis
    major_axis.x = Y[0];
    major_axis.y = Y[1];
    minor_axis.x = -X[0];
    minor_axis.y = -X[1];
    *major_radius = C;
    *minor_radius = A;
  }
  else
  {
    // A or C is a NaN
    return false;
  }

  center.x = P[0];
  center.y = P[1];

  return true;
}

bool ON_GetEllipseConicEquation( 
    double a, double b, 
    double x0, double y0, 
    double alpha,
    double conic[6]
    )
{
  if ( 0 == conic )
    return false;

  if ( !(a > 0.0 && b > 0.0 && ON_IsValid(x0) && ON_IsValid(y0) && ON_IsValid(alpha)) )
  {
    return false;
  }

  int k;
  double e, y;
  double a2 = a*a;
  double b2 = b*b;

  double A0 = 1.0/a2;                    // A*x*x
  double B0 = 0.0;                       // B*x*y
  double C0 = 1.0/b2;                    // C*y*y
  double D0 = 0.0;                       // D*x
  double E0 = 0.0;                       // E*y
  double F0 = -1.0;                      // F

  // rotate
  const double ca = cos(-alpha);
  const double sa = sin(-alpha);
  const double A = A0*ca*ca + B0*ca*sa + C0*sa*sa;
  const double B = B0*(ca*ca - sa*sa) + 2.0*(C0-A0)*sa*ca;
  const double C = C0*ca*ca - B0*sa*ca + A0*sa*sa; 
  const double D = D0*ca + E0*sa;
  const double E = E0*ca - D0*sa;
  const double F = F0;

  if ( !((A > 0.0 && C > 0.0) || (A < 0.0 && C < 0.0)) )
  {
    return false;
  }

  // translate center to (x0,y0)
  conic[0] = A;
  conic[1] = B;
  conic[2] = C;
  conic[3] = D - 2.0*A*x0 - B*y0;
  conic[4] = E - 2.0*C*y0 - B*x0;
  conic[5] = F + A*x0*x0 + B*x0*y0 + C*y0*y0 - D*x0 - E*y0;

  k = 0;
  e = fabs(conic[0]);
  if ( e < (y=fabs(conic[1])) ) {e=y;k=1;}
  if ( e < (y=fabs(conic[2])) ) {e=y;k=2;}
  if ( e < (y=fabs(conic[3])) ) {e=y;k=3;}
  if ( e < (y=fabs(conic[4])) ) {e=y;k=4;}
  if ( e < (y=fabs(conic[5])) ) {e=y;k=5;}
  e = 1.0/conic[k];
  conic[0] *= e; conic[1] *= e; conic[2] *= e;
  conic[3] *= e; conic[4] *= e; conic[5] *= e;
  conic[k] = 1.0;
  if ( conic[0] < 0.0 )
  {
    conic[0] = -conic[0]; conic[1] = -conic[1]; conic[2] = -conic[2];
    conic[3] = -conic[3]; conic[4] = -conic[4]; conic[5] = -conic[5];
  }

  return true;
}


ON_3dPointListRef::ON_3dPointListRef(
  const class ON_Mesh* mesh
  )
{
  *this = ON_3dPointListRef::FromMesh(mesh);
}

ON_3dPointListRef::ON_3dPointListRef(
  const class ON_SimpleArray<ON_3dPoint>& point_array
  )
{
  *this = ON_3dPointListRef::FromPointArray(point_array);
}

ON_3dPointListRef::ON_3dPointListRef(
  const class ON_SimpleArray<ON_3fPoint>& point_array
  )
{
  *this = ON_3dPointListRef::FromPointArray(point_array);
}

const ON_3dPointListRef ON_3dPointListRef::EmptyPointList;

unsigned int ON_3dPointListRef::SetFromDoubleArray(
    size_t point_count,
    size_t point_stride,
    const double* point_array
    )
{
  *this = ON_3dPointListRef::EmptyPointList;
  if ( point_count > 0 
       && point_count < (size_t)ON_UNSET_UINT_INDEX 
       && point_stride >= 3
       && point_stride < (size_t)ON_UNSET_UINT_INDEX 
       && 0 != point_array
       )
  {
    m_point_count = (unsigned int)point_count;
    m_point_stride = (unsigned int)point_stride;
    m_dP = point_array;
  }
  return m_point_count;
}

unsigned int ON_3dPointListRef::SetFromFloatArray(
    size_t point_count,
    size_t point_stride,
    const float* point_array
    )
{
  *this = ON_3dPointListRef::EmptyPointList;
  if ( point_count > 0 
       && point_count < (size_t)ON_UNSET_UINT_INDEX 
       && point_stride >= 3
       && point_stride < (size_t)ON_UNSET_UINT_INDEX 
       && 0 != point_array
       )
  {
    m_point_count = (unsigned int)point_count;
    m_point_stride = (unsigned int)point_stride;
    m_fP = point_array;
  }
  return m_point_count;
}


unsigned int ON_3dPointListRef::SetFromMesh(
  const class ON_Mesh* mesh
  )
{
  if ( 0 != mesh )
  {
    const unsigned int vertex_count = mesh->VertexUnsignedCount();
    if ( vertex_count > 0 )
    {
      return (mesh->HasDoublePrecisionVertices())
      ? SetFromDoubleArray(vertex_count,3,(const double*)(mesh->m_dV.Array()))
      : SetFromFloatArray(vertex_count,3,(const float*)(mesh->m_V.Array()));
    }
  }
  *this = ON_3dPointListRef::EmptyPointList;
  return m_point_count;
}

ON_3dPointListRef ON_3dPointListRef::FromDoubleArray(
  size_t point_count,
  size_t point_stride,
  const double* point_array
  )
{
  ON_3dPointListRef p;
  p.SetFromDoubleArray(point_count,point_stride,point_array);
  return p;
}

ON_3dPointListRef ON_3dPointListRef::FromFloatArray(
  size_t point_count,
  size_t point_stride,
  const float* point_array
  )
{
  ON_3dPointListRef p;
  p.SetFromFloatArray(point_count,point_stride,point_array);
  return p;
}

ON_3dPointListRef ON_3dPointListRef::FromPointArray(
  const class ON_SimpleArray<ON_3dPoint>& point_array
  )
{
  ON_3dPointListRef p;
  p.SetFromDoubleArray(point_array.UnsignedCount(),3,(const double*)point_array.Array());
  return p;
}

ON_3dPointListRef ON_3dPointListRef::FromPointArray(
  const class ON_SimpleArray<ON_3fPoint>& point_array
  )
{
  ON_3dPointListRef p;
  p.SetFromFloatArray(point_array.UnsignedCount(),3,(const float*)point_array.Array());
  return p;
}

ON_3dPointListRef ON_3dPointListRef::FromMesh(
  const class ON_Mesh* mesh
  )
{
  ON_3dPointListRef p;
  p.SetFromMesh(mesh);
  return p;
}

unsigned int ON_3dPointListRef::Precision() const
{
  if ( 0 != m_dP )
    return 2;
  if ( 0 != m_fP )
    return 1;
  return 0;
}

ON_SimpleArray<ON_3dPoint> ON_3dPointListRef::To3dPointArray() const
{
  ON_SimpleArray<ON_3dPoint> a;

  unsigned int i = m_point_count;
  if ( i > 0 )
  {
    a.Reserve(i);
    a.SetCount(i);
    double* dst = (double*)a.Array();
    if ( m_dP )
    {
      const double* src = m_dP;
      while(i--)
      {
        *dst++ = src[0];
        *dst++ = src[1];
        *dst++ = src[2];
        src += m_point_stride;
      }
    }
    else if ( m_fP )
    {
      const float* src = m_fP;
      while(i--)
      {
        *dst++ = src[0];
        *dst++ = src[1];
        *dst++ = src[2];
        src += m_point_stride;
      }
    }
  }

  // Note: 
  //  ON_SimpleArray<ON_3dPoint> has rvalue copy constructor
  //  and operator=, so this return does not create a copy.
  return a;
}

ON_SimpleArray<ON_3fPoint> ON_3dPointListRef::To3fPointArray() const
{
  ON_SimpleArray<ON_3fPoint> a;

  unsigned int i = m_point_count;
  if ( i > 0 )
  {
    a.Reserve(i);
    a.SetCount(i);
    float* dst = (float*)a.Array();
    if ( m_dP )
    {
      const double* src = m_dP;
      while(i--)
      {
        *dst++ = (float)src[0];
        *dst++ = (float)src[1];
        *dst++ = (float)src[2];
        src += m_point_stride;
      }
    }
    else if ( m_fP )
    {
      const float* src = m_fP;
      while(i--)
      {
        *dst++ = src[0];
        *dst++ = src[1];
        *dst++ = src[2];
        src += m_point_stride;
      }
    }
  }

  // Note: 
  //  ON_SimpleArray<ON_3fPoint> has rvalue copy constructor
  //  and operator=, so this return does not create a copy.
  return a;
}

/*
Returns:
  true if the points are double precision
*/
bool ON_3dPointListRef::DoublePrecision() const
{
  return (0 != m_dP);
}

/*
Returns:
  true if the points are single precision
*/
bool ON_3dPointListRef::SinglePrecision() const
{
  return (0 != m_dP);
}

unsigned int ON_3dPointListRef::GetMeshFacePoints(
  const class ON_MeshFace* mesh_face,
  ON_3dPoint face_points[4]
  ) const
{
  return (0 != mesh_face) 
         ? GetPoints(4U,(const unsigned int*)(mesh_face->vi),face_points) 
         : 0;
}

unsigned int ON_3dPointListRef::GetMeshNgonPoints(
  const class ON_MeshNgon* mesh_ngon,
  size_t ngon_points_capacity,
  class ON_3dPoint* ngon_points
  ) const
{
  return ( 0 != mesh_ngon && ((size_t)mesh_ngon->m_Vcount) <= ngon_points_capacity) 
    ? GetPoints(mesh_ngon->m_Vcount, mesh_ngon->m_vi, ngon_points)
    : 0;
}

unsigned int ON_3dPointListRef::GetMeshNgonPoints(
  const class ON_MeshNgon* mesh_ngon,
  ON_SimpleArray<ON_3dPoint>& ngon_points
  ) const
{
  if ( mesh_ngon && mesh_ngon->m_Vcount > 0 && 0 != mesh_ngon->m_vi )
  {
    ngon_points.Reserve(mesh_ngon->m_Vcount);
    ngon_points.SetCount(mesh_ngon->m_Vcount);
    return GetPoints(mesh_ngon->m_Vcount, mesh_ngon->m_vi, ngon_points.Array());
  }
  ngon_points.SetCount(0);
  return 0;
}

unsigned int ON_3dPointListRef::GetQuadPoints(
  const int quad_point_indices[4],
  class ON_3dPoint quad_points[4]
  ) const
{
  return GetPoints(4,quad_point_indices,quad_points);
}

unsigned int ON_3dPointListRef::GetQuadPoints(
  const unsigned int quad_point_indices[4],
  class ON_3dPoint quad_points[4]
  ) const
{
  return GetPoints(4,quad_point_indices,quad_points);
}

unsigned int ON_3dPointListRef::GetTrianglePoints(
  const int triangle_point_indices[3],
  class ON_3dPoint triangle_points[3]
  ) const
{
  return GetPoints(3,triangle_point_indices,triangle_points);
}

unsigned int ON_3dPointListRef::GetTrianglePoints(
  const unsigned int triangle_point_indices[3],
  class ON_3dPoint triangle_points[3]
  ) const
{
  return GetPoints(3,triangle_point_indices,triangle_points);
}

unsigned int ON_3dPointListRef::GetPoints(
  int point_index_count,
  const int* point_index_list,
  class ON_3dPoint* points
  ) const
{
  return GetPoints((unsigned int)point_index_count,(const unsigned int*)point_index_list,points);
}

unsigned int ON_3dPointListRef::GetPoints(
  unsigned int point_index_count,
  const unsigned int* point_index_list,
  class ON_3dPoint* points
  ) const
{
  unsigned int rc = 0;
  if ( 0 == point_index_list 
      || 0 == points
      || 0 == point_index_count
      || point_index_count >= m_point_count 
      )
  {
    return rc;
  }

  double* dst = &points[0].x;

  if ( m_dP )
  {
    rc = point_index_count;
    while(point_index_count--)
    {
      unsigned int i = *point_index_list++;
      if ( i < m_point_count )
      {
        const double* src = m_dP + i*m_point_stride;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src;
      }
      else
      {
        *dst++ = ON_UNSET_VALUE;
        *dst++ = ON_UNSET_VALUE;
        *dst++ = ON_UNSET_VALUE;
      }
    }
    return rc;
  }

  if ( m_fP )
  {
    rc = point_index_count;
    while(point_index_count--)
    {
      unsigned int i = *point_index_list++;
      if ( i < m_point_count )
      {
        const float* src = m_fP + i*m_point_stride;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src;
      }
      else
      {
        *dst++ = ON_UNSET_VALUE;
        *dst++ = ON_UNSET_VALUE;
        *dst++ = ON_UNSET_VALUE;
      }
    }
    return rc;
  }

  return rc;
}

unsigned int ON_3dPointListRef::GetPoints(
  const ON_SimpleArray<int>& point_index_list,
  ON_SimpleArray<ON_3dPoint>& points
  ) const
{
  points.Reserve(point_index_list.UnsignedCount());
  points.SetCount(point_index_list.UnsignedCount());
  unsigned int rc = GetPoints( point_index_list.UnsignedCount(),
                               (const unsigned int*)point_index_list.Array(),
                               points.Array()
                             );
  if ( rc < points.UnsignedCount() )
    points.SetCount(rc);

  return rc;
}


unsigned int ON_3dPointListRef::GetPoints(
  int point_index_count,
  const int* point_index_list,
  ON_SimpleArray<ON_3dPoint>& points
  ) const
{
  unsigned int rc = (point_index_count > 0) 
                  ? GetPoints((unsigned int)point_index_count,(const unsigned int*)point_index_list,points) 
                  : 0;

  if (rc < points.UnsignedCount())
    points.SetCount(rc);

  return rc;
}

unsigned int ON_3dPointListRef::GetPoints(
  unsigned int point_index_count,
  const unsigned int* point_index_list,
  ON_SimpleArray<ON_3dPoint>& points
  ) const
{
  unsigned int rc = 0;
  if ( point_index_count > 0 && 0 != point_index_list )
  {
    points.Reserve(point_index_count);
    points.SetCount(point_index_count);
    rc = GetPoints(point_index_count,point_index_list,points.Array());
  }

  if (rc < points.UnsignedCount())
    points.SetCount(rc);

  return rc;
}
  
static ON__UINT32 Internal_DoubleArrayDataCRC(
  ON__UINT32 current_remainder,
  size_t count,
  const double* a
)
{
  double x;
  char* byte_swap 
    = (ON::endian::big_endian == ON::Endian()) 
    ? ((char*)&x)
    : nullptr;
  char c;
  if (nullptr != a && count > 0)
  {
    const double* a1 = a + count;
    while (a < a1)
    {
      x = *a++;
      if (0.0 == x)
        x = 0.0; // change -0.0 into +0.0
      else if (false == (x == x))
        x = ON_DBL_QNAN; // change any nan into ON_DBL_QNAN.
      if (nullptr != byte_swap)
      {
        c = byte_swap[0]; byte_swap[0] = byte_swap[7]; byte_swap[7] = c;
        c = byte_swap[1]; byte_swap[1] = byte_swap[6]; byte_swap[6] = c;
        c = byte_swap[2]; byte_swap[2] = byte_swap[5]; byte_swap[5] = c;
        c = byte_swap[3]; byte_swap[3] = byte_swap[4]; byte_swap[4] = c;
      }
      current_remainder = ON_CRC32(current_remainder, sizeof(x), (const void*)&x);
    }
  }
  return current_remainder;
}

ON__UINT32 ON_2dPoint::DataCRC(ON__UINT32 current_remainder) const
{
  return Internal_DoubleArrayDataCRC(current_remainder, 2, &x);
}
  
ON__UINT32 ON_3dPoint::DataCRC(ON__UINT32 current_remainder) const
{
  return Internal_DoubleArrayDataCRC(current_remainder, 3, &x);
}
  
ON__UINT32 ON_4dPoint::DataCRC(ON__UINT32 current_remainder) const
{
  return Internal_DoubleArrayDataCRC(current_remainder, 4, &x);
}

ON__UINT32 ON_2dVector::DataCRC(ON__UINT32 current_remainder) const
{
  return Internal_DoubleArrayDataCRC(current_remainder, 2, &x);
}
  
ON__UINT32 ON_3dVector::DataCRC(ON__UINT32 current_remainder) const
{
  return Internal_DoubleArrayDataCRC(current_remainder, 3, &x);
}
  
ON__UINT32 ON_2fPoint::DataCRC(ON__UINT32 current_remainder) const
{
  const ON_2dPoint p(*this);
  return p.DataCRC(current_remainder);
}
  
ON__UINT32 ON_3fPoint::DataCRC(ON__UINT32 current_remainder) const
{
  const ON_3dPoint p(*this);
  return p.DataCRC(current_remainder);
}
  
ON__UINT32 ON_4fPoint::DataCRC(ON__UINT32 current_remainder) const
{
  const ON_4dPoint p(*this);
  return p.DataCRC(current_remainder);
}

ON__UINT32 ON_2fVector::DataCRC(ON__UINT32 current_remainder) const
{
  const ON_2dVector v(*this);
  return v.DataCRC(current_remainder);
}
  
ON__UINT32 ON_3fVector::DataCRC(ON__UINT32 current_remainder) const
{
  const ON_3dVector v(*this);
  return v.DataCRC(current_remainder);
}














// ON_2dSize

int ON_2dSize::Compare(
  const ON_2dSize& lhs,
  const ON_2dSize& rhs
)
{
  if (lhs.cx < rhs.cx)
    return -1;
  if (lhs.cx > rhs.cx)
    return 1;
  if (lhs.cy < rhs.cy)
    return -1;
  if (lhs.cy > rhs.cy)
    return 1;
  return 0;
}

int ON_2dSize::ComparePointer(
  const ON_2dSize* lhs,
  const ON_2dSize* rhs
)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return -1;
  if (nullptr == rhs)
    return 1;
  if (lhs->cx < rhs->cx)
    return -1;
  if (lhs->cx > rhs->cx)
    return 1;
  if (lhs->cy < rhs->cy)
    return -1;
  if (lhs->cy > rhs->cy)
    return 1;
  return 0;
}

ON_2dSize::ON_2dSize(double cxValue, double cyValue)
  : cx(cxValue)
  , cy(cyValue)
{}

bool ON_2dSize::IsSet() const
{
  return (ON_UNSET_VALUE != cx && ON_UNSET_VALUE != cy);
}

bool ON_2dSize::IsZero() const
{
  return (0 == cx && 0 == cy);
}

bool operator==(
  const ON_2dSize& lhs,
  const ON_2dSize& rhs
  )
{
  return (lhs.cx == rhs.cx && lhs.cy == rhs.cy);
}

bool operator!=(const ON_2dSize& lhs, const ON_2dSize& rhs)
{
  return (lhs.cx != rhs.cx || lhs.cy != rhs.cy);
}

// ON_4dRect
ON_4dRect::ON_4dRect(double leftValue, double topValue, double rightValue, double bottomValue)
  : left(leftValue)
  , top(topValue)
  , right(rightValue)
  , bottom(bottomValue)
{}

ON_4dRect::ON_4dRect(const ON_2dPoint topLeft, const ON_2dPoint& bottomRight)
	: left(topLeft.x)
	, top(topLeft.y)
	, right(bottomRight.x)
	, bottom(bottomRight.y)
{}

ON_4dRect::ON_4dRect(const ON_2dPoint& point, const ON_2dSize& size)
{
	left = point.x;
	top = point.y;
	right = left + size.cx;
	bottom = top + size.cy;
}

bool ON_4dRect::IsSet() const
{
  return (
    ON_UNSET_VALUE != left 
    && ON_UNSET_VALUE != top
    && ON_UNSET_VALUE != right
    && ON_UNSET_VALUE != bottom
    );
}

double ON_4dRect::Width(void) const { return fabs(right - left); }

double ON_4dRect::Height(void) const { return fabs(bottom - top); }

const ON_2dSize ON_4dRect::Size(void) const { return ON_2dSize(Width(), Height()); }

const ON_2dPoint ON_4dRect::CenterPoint(void) const { return ON_2dPoint((left + right) / 2.0, (top + bottom) / 2.0); }

const ON_2dPoint ON_4dRect::TopLeft(void) const { return ON_2dPoint(left, top); }

const ON_2dPoint ON_4dRect::BottomRight(void) const { return ON_2dPoint(right, bottom); }

bool ON_4dRect::IntersectRect(const ON_4dRect * r1, const ON_4dRect * r2)
{
  // The previous implementation was incorrect. The implementation for ON_4iRect::Intersect
  // was/is correct, so its implemenation is now used here.
  left = ON_Max(r1->left, r2->left);
  right = ON_Min(r1->right, r2->right);
  if (right > left)
  {
    top = ON_Max(r1->top, r2->top);
    bottom = ON_Min(r1->bottom, r2->bottom);
    if (bottom > top)
      return true;
  }

  // degenerate rectangle at this point...
  SetRectEmpty();
  return false;
}

bool ON_4dRect::IntersectRect(const ON_4dRect & r1, const ON_4dRect & r2) { return IntersectRect(&r1, &r2); }

bool ON_4dRect::IsRectEmpty(void) const 
{ 
	return 0 == Width() || 0 == Height(); 
}

bool ON_4dRect::IsRectNull(void) const
{ 
	return 0.0 == left &&
		   0.0 == top  &&
		   0.0 == bottom &&
		   0.0 == right; 
}

void ON_4dRect::SetRect(double l, double t, double r, double b) { left = l; top = t; right = r; bottom = b; }

bool ON_4dRect::PtInRect(const ON_2dPoint & pt) const
{
	return pt.x >= left && pt.y >= top && pt.x < right && pt.y < bottom;
}

void ON_4dRect::OffsetRect(double x, double y)
{
	left += x;
	right += x;
	top += y;
	bottom += y;
}

void ON_4dRect::OffsetRect(const ON_2dVector& v)
{
	left += v.x;
	right += v.x;
	top += v.y;
	bottom += v.y;
}

void ON_4dRect::InflateRect(double x, double y)
{
	left -= x;
	top -= y;
	right += x;
	bottom += y;
}

void ON_4dRect::InflateRect(double l, double t, double r, double b)
{
	left -= l;
	top -= t;
	right += r;
	bottom += b;
}

void ON_4dRect::DeflateRect(double x, double y)
{
	left += x;
	top += y;
	right -= x;
	bottom -= y;
}

bool ON_4dRect::SubtractRect(const ON_4dRect* rect1, const ON_4dRect* rect2)
{
	if (rect1 == nullptr)
		return false;

	*this = *rect1;

	if (rect1->IsRectEmpty() || rect2 == nullptr || rect2->IsRectEmpty())
	{
		return true;
	}

	if (rect2->top <= rect1->top && rect2->bottom >= rect1->bottom)
	{
		if (left < rect2->right)
		{
			left = ON_Min(rect2->right, right);
		}
		if (right > rect2->left)
		{
			right = ON_Max(left, rect2->left);
		}
	}

	if (rect2->left <= rect1->left && rect2->right >= rect1->right)
	{
		if (top < rect2->bottom)
		{
			top = ON_Min(rect2->bottom, bottom);
		}
		if (bottom > rect2->top)
		{
			bottom = ON_Max(top, rect2->top);
		}
	}

	return true;
}

void ON_4dRect::NormalizeRect()
{
	double nTemp;
	if (left > right)
	{
		nTemp = left;
		left = right;
		right = nTemp;
	}
	if (top > bottom)
	{
		nTemp = top;
		top = bottom;
		bottom = nTemp;
	}
}

bool ON_4dRect::IsZero() const
{
  return (0.0 == left && 0.0 == top && 0.0 == right && 0.0 == bottom);
}

void ON_4dRect::SetZero() { *this = Zero; }


bool operator==(const ON_4dRect& lhs, const ON_4dRect& rhs)
{
  return (lhs.left == rhs.left
    && lhs.top == rhs.top 
    && lhs.right == rhs.right
    && lhs.bottom == rhs.bottom);
}

bool operator!=(const ON_4dRect& lhs, const ON_4dRect& rhs)
{
  return (lhs.left != rhs.left
    || lhs.top != rhs.top 
    || lhs.right != rhs.right
    || lhs.bottom != rhs.bottom);
}


int ON_WindingNumber::WindingNumber() const
{
  int winding_number = m_left_crossing_number;
  if (abs(m_right_crossing_number) < abs(winding_number))
    winding_number = m_right_crossing_number;
  if (abs(m_above_crossing_number) < abs(winding_number))
    winding_number = m_above_crossing_number;
  if (abs(m_below_crossing_number) < abs(winding_number))
    winding_number = m_below_crossing_number;
  return winding_number;
}

const ON_2dPoint ON_WindingNumber::WindingPoint() const
{
  return m_winding_point;
}

unsigned int ON_WindingNumber::BoundarySegmentCount() const
{
  return m_boundary_segment_count;
}

const ON_2dPoint ON_WindingNumber::PreviousBoundaryPoint() const
{
  return m_prev_boundary_point;
}

bool ON_WindingNumber::Internal_HaveWindingPoint() const
{
  // m_point.x is a NAN when not initialized
  return (m_winding_point.x == m_winding_point.x);
}

void ON_WindingNumber::SetWindingPoint(double x, double y)
{
  return ON_WindingNumber::SetWindingPoint(ON_2dPoint(x, y));
}

void ON_WindingNumber::SetWindingPoint(ON_2dPoint winding_point)
{
  *this = ON_WindingNumber::Unset;
  if (winding_point.IsValid())
    m_winding_point = winding_point;
}

//bool ON_WindingNumber::Internal_IsLeft( const double* p, const  double* q )
//{
//  // Input: p and q are 2d points with p.y <= 0 and q.y > 0
//  //
//  // Returns:
//  //   true if the x coordinate of the intersection of the line segment from p to q and the x axis
//  //   is negative; i.e., the intersection point is to the left of the origin (0,0).
//  //
//  // Arithmetic:
//  //  L = segment from p to q.
//  //  L crosses the x-axis (y=0)
//  //  L(t) = (1-t)*P + t*Q;
//  //  When t = p.y/(p.y-q.y), L(t).y == 0
//  //  (1-t) = (-q.y/(p.y-q.y))
//  //  L(t).x = (-q.y/(p.y-q.y))*p.x + (p.y/(p.y-q.y))*q.x
//  //         = (p.y*q.x - p.x*q.y)/(p.y-q.y)
//  //  Since (p.y <= 0 and q.y > 0), (p.y-q.y) < 0
//  //  Therefore L(t).x < 0 if and only if (p.y*q.x - p.x*q.y) > 0.
//  //  Therefore L(t).x < 0 if and only if p.y*q.x > p.x*q.y.
//  return (p[1]*q[0]) > (p[0]*q[1]);
//}


int ON_WindingNumber::Internal_SignOfX(const ON_2dPoint& p, const ON_2dPoint& q)
{
  // Input: p and q are 2d points with p.y <= 0 and q.y > 0
  //
  // Returns:
  //   Sign of the x coordinate of the intersection of the line segment from p to q 
  //   and the x axis.
  //
  // Arithmetic:
  //  L = segment from p to q.
  //  L crosses the x-axis (y=0)
  //  L(t) = (1-t)*P + t*Q;
  //  When t = p.y/(p.y-q.y), L(t).y == 0
  //  (1-t) = (-q.y/(p.y-q.y))
  //  L(t).x = (-q.y/(p.y-q.y))*p.x + (p.y/(p.y-q.y))*q.x
  //         = (p.y*q.x - p.x*q.y)/(p.y-q.y)
  //  Since (p.y <= 0 and q.y > 0), (p.y-q.y) < 0
  //  Therefore 
  //     L(t).x < 0 if and only if (p.y*q.x - p.x*q.y) > 0.
  //     L(t).x > 0 if and only if (p.y*q.x - p.x*q.y) < 0.
  const double x = (p.y*q.x) - (p.x*q.y);
  if (x < 0.0)
    return 1;
  if (x > 0.0)
    return -1;
  return 0;
}

int ON_WindingNumber::Internal_SignOfY(const ON_2dPoint& p, const ON_2dPoint& q)
{
  // Input: p and q are 2d points with p.x <= 0 and q.x > 0
  //
  // Returns:
  //   Sign of the y coordinate of the intersection of the line segment from p to q 
  //   and the y axis.
  //
  // Arithmetic:
  //  L = segment from p to q.
  //  L crosses the y-axis (x=0)
  //  L(t) = (1-t)*P + t*Q;
  //  When t = p.x/(p.x-q.x), L(t).x == 0
  //  (1-t) = (-q.x/(p.x-q.x))
  //  L(t).y = (-q.x/(p.x-q.x))*p.y + (p.x/(p.x-q.x))*q.y
  //         = (p.x*q.y - p.y*q.x)/(p.x-q.x)
  //  Since (p.x <= 0 and q.x > 0), (p.x-q.x) < 0
  //  Therefore 
  //     L(t).y < 0 if and only if (p.x*q.y - p.y*q.x) > 0.
  //     L(t).y > 0 if and only if (p.x*q.y - p.y*q.x) < 0.
  const double y = (p.x*q.y) - (p.y*q.x);
  if (y < 0.0)
    return 1;
  if (y > 0.0)
    return -1;
  return 0;
}

void ON_WindingNumber::Internal_AddBoundarySegment(const double* p, const double* q)
{
  /////////////////////////////////////////////////////////////////////////
  // The calculation below is a modified version of a portion of wn_PnPoly()
  // with a bug fix for the case when m_winding_point is on the polyline.
  //
  // http://geomalgorithms.com/a03-_inclusion.html
  //
  // Copyright 2000 softSurfer, 2012 Dan Sunday
  // This code may be freely used and modified for any purpose
  // providing that this copyright notice is included with it.
  // SoftSurfer makes no warranty for this code, and cannot be held
  // liable for any real or imagined damage resulting from its use.
  // Users of this code must verify correctness for their application.
  /////////////////////////////////////////////////////////////////////////

  // calling function insures m_winding_point is set.
  // In the comments below H is the horizontal line through the winding point.
  const ON_2dPoint p0(p[0] - m_winding_point.x, p[1] - m_winding_point.y);
  const ON_2dPoint p1(q[0] - m_winding_point.x, q[1] - m_winding_point.y);
  int sign_of;

  if (p0.y <= 0.0)
  {   
    if (p1.y > 0.0)
    {
      // p0.y <= 0, p1.y > 0 (line segment goes "up") and ...
      sign_of = ON_WindingNumber::Internal_SignOfX(p0, p1);
      if ( sign_of < 0 )
      {
        // ... intersects the x-axis to the left of the origin.
        --m_left_crossing_number;
        m_status_bits |= 1;
      }
      else if (sign_of > 0)
      {
        // ... intersects the x-axis to the right of the origin.
        ++m_right_crossing_number;
        m_status_bits |= 2;
      }
    }
  }
  else
  {                
    if (p1.y <= 0.0)
    {
      // p1.y <= 0 and p0.y > 0 (line segment from p0 to p1 goes "down") ...
      sign_of = ON_WindingNumber::Internal_SignOfX(p1, p0); // YES, (p1, p0) is correct.
      if (sign_of < 0)
      {
        // ... and intersects the x-axis to the left of the origin.
        ++m_left_crossing_number;
        m_status_bits |= 1;
      }
      else if (sign_of > 0)
      {
        // ... and intersects the x-axis to the right of the origin.
        --m_right_crossing_number;
        m_status_bits |= 2;
      }
    }
  }


  if (p0.x <= 0.0)
  {   
    if (p1.x > 0.0)
    {
      // p0.x <= 0, p1.x > 0 (line segment from p0 to p1 goes "right") ...
      sign_of = ON_WindingNumber::Internal_SignOfY(p0, p1);
      if ( sign_of < 0 )
      {
        // ... and intersects the y-axis to the below of the origin.
        ++m_below_crossing_number;
        m_status_bits |= 4;
      }
      else if (sign_of > 0)
      {
        // ... and intersects the y-axis to the above of the origin.
        --m_above_crossing_number;
        m_status_bits |= 8;
      }
    }
  }
  else
  {                
    if (p1.x <= 0.0)
    {
      // p1.x <= 0 and p0.x > 0 (line segment from p0 to p1 goes "down") ...
      sign_of = ON_WindingNumber::Internal_SignOfY(p1, p0); // YES, (p1, p0) is correct.
      if (sign_of < 0)
      {
        // ... and intersects the y-axis to the left of the origin.
        --m_below_crossing_number;
        m_status_bits |= 4;
      }
      else if (sign_of > 0)
      {
        // ... and intersects the y-axis to the right of the origin.
        ++m_above_crossing_number;
        m_status_bits |= 8;
      }
    }
  }

  if (0.0 == p0.x && 0.0 == p1.x && p0.y != p1.y )
  {
    if ((p0.y <= 0.0 && p1.y >= 0.0) || (p0.y >= 0.0 && p1.y <= 0.0))
      m_status_bits |= 32; // vertical segment on winding point
  }
  else if (0.0 == p0.y && 0.0 == p1.y && p0.x != p1.x)
  {
    if ( (p0.x <= 0.0 && p1.x >= 0.0) || (p0.x >= 0.0 && p1.x <= 0.0) )
      m_status_bits |= 16; // horizontal segment on winding point
  }

  m_prev_boundary_point.x = q[0];
  m_prev_boundary_point.y = q[1];
  ++m_boundary_segment_count;
}

ON__UINT32 ON_WindingNumber::AddBoundary(ON_2dPoint p)
{
  const ON__UINT32 boundary_segment_count0 = m_boundary_segment_count;
  if (Internal_HaveWindingPoint())
  {
    if ( m_prev_boundary_point.x == m_prev_boundary_point.x )
      Internal_AddBoundarySegment(&m_prev_boundary_point.x, &p.x);
    else 
      m_prev_boundary_point = p;
  }
  return (m_boundary_segment_count - boundary_segment_count0);
}

ON__UINT32 ON_WindingNumber::AddBoundary(ON_2dPoint p, ON_2dPoint q)
{
  const ON__UINT32 boundary_segment_count0 = m_boundary_segment_count;
  if (Internal_HaveWindingPoint())
  {
    Internal_AddBoundarySegment(&p.x, &q.x);
  }
  return (m_boundary_segment_count - boundary_segment_count0);
}

ON__UINT32 ON_WindingNumber::AddBoundary(size_t point_count, size_t point_stride, const double* boundary_points, bool bCloseBoundary)
{
  const ON__UINT32 boundary_segment_count0 = m_boundary_segment_count;
  if (Internal_HaveWindingPoint() && point_count >= 2 && point_stride >= 2 && nullptr != boundary_points)
  {
    const double* last_point = boundary_points + ((point_count - 1)*point_stride);
    for (const double* p = boundary_points; p < last_point; p += point_stride)
    {
      Internal_AddBoundarySegment(p, p + point_stride);
    }
    if (bCloseBoundary)
    {
      Internal_AddBoundarySegment(last_point, boundary_points);
    }
  }
  return (m_boundary_segment_count - boundary_segment_count0);
}

ON__UINT32 ON_WindingNumber::AddBoundary(size_t point_count, size_t point_stride, const float* boundary_points, bool bCloseBoundary)
{
  const ON__UINT32 boundary_segment_count0 = m_boundary_segment_count;
  if (Internal_HaveWindingPoint() && point_count >= 2 && point_stride >= 2 && nullptr != boundary_points)
  {
    ON_2dPoint p0, p1;
    const float* pmax = boundary_points + (point_count*point_stride);
    p1.x = boundary_points[0];
    p1.y = boundary_points[1];
    for (const float* p = boundary_points+point_stride; p < pmax; p += point_stride)
    {
      p0 = p1;
      p1.x = p[0];
      p1.y = p[1];
      Internal_AddBoundarySegment(&p0.x, &p1.x);
    }
    if (bCloseBoundary)
    {
      p0.x = boundary_points[0];
      p0.y = boundary_points[1];
      Internal_AddBoundarySegment(&p1.x, &p0.x);
    }
  }
  return (m_boundary_segment_count - boundary_segment_count0);
}

ON__UINT32 ON_WindingNumber::AddBoundary(size_t point_count, size_t point_stride, const int* boundary_points, bool bCloseBoundary)
{
  const ON__UINT32 boundary_segment_count0 = m_boundary_segment_count;
  if (Internal_HaveWindingPoint() && point_count >= 2 && point_stride >= 2 && nullptr != boundary_points)
  {
    ON_2dPoint p0, p1;
    const int* pmax = boundary_points + (point_count*point_stride);
    p1.x = boundary_points[0];
    p1.y = boundary_points[1];
    for (const int* p = boundary_points+point_stride; p < pmax; p += point_stride)
    {
      p0 = p1;
      p1.x = p[0];
      p1.y = p[1];
      Internal_AddBoundarySegment(&p0.x, &p1.x);
    }
    if (bCloseBoundary)
    {
      p0.x = boundary_points[0];
      p0.y = boundary_points[1];
      Internal_AddBoundarySegment(&p1.x, &p0.x);
    }
  }
  return (m_boundary_segment_count - boundary_segment_count0);
}

ON__UINT32 ON_WindingNumber::AddBoundary(size_t point_count, const ON_2dPoint* boundary_points, bool bCloseBoundary)
{
  const double* p = (nullptr != boundary_points ? &boundary_points->x : nullptr);
  return AddBoundary(point_count, sizeof(boundary_points[0])/sizeof(p[0]), p, bCloseBoundary);
}

ON__UINT32 ON_WindingNumber::AddBoundary(size_t point_count, const ON_3dPoint* boundary_points, bool bCloseBoundary)
{
  const double* p = (nullptr != boundary_points ? &boundary_points->x : nullptr);
  return AddBoundary(point_count, sizeof(boundary_points[0])/sizeof(p[0]), p, bCloseBoundary);
}

ON__UINT32 ON_WindingNumber::AddBoundary(size_t point_count, const ON_2fPoint* boundary_points, bool bCloseBoundary)
{
  const float* p = (nullptr != boundary_points ? &boundary_points->x : nullptr);
  return AddBoundary(point_count, sizeof(boundary_points[0])/sizeof(p[0]), p, bCloseBoundary);
}

ON__UINT32 ON_WindingNumber::AddBoundary(size_t point_count, const ON_3fPoint* boundary_points, bool bCloseBoundary)
{
  const float* p = (nullptr != boundary_points ? &boundary_points->x : nullptr);
  return AddBoundary(point_count, sizeof(boundary_points[0])/sizeof(p[0]), p, bCloseBoundary);
}




ON_PeriodicDomain::ON_PeriodicDomain(const ON_Interval dom[2], const bool closed[2], double normband) :
	m_dom{ dom[0], dom[1] },
	m_closed{ closed[0],closed[1] },
	m_normband(normband),
	m_deck{ 0,0 }
{}

void ON_PeriodicDomain::Initialize(const ON_Interval dom[2], const bool closed[2], double normband)
{
	m_dom[0] = dom[0];
	m_dom[1] = dom[1];
	m_closed[0] = closed[0];
	m_closed[1] = closed[1];
	m_normband = normband;
	m_deck[0] = m_deck[1] = 0;
}

// Repeated application of LiftToCover maps a sequence in the domain covering space, 
//  Pin[i] to  Out[i].
// 
//  *  proj(Pin[i]) = proj(Out[i])
//  *  Out[0] = Pin[0]
//  *  Out[i+1] and Out[i] are in adjacent bands
ON_2dPoint ON_PeriodicDomain::LiftToCover(ON_2dPoint Pin, bool stealth )
{
	ON_2dPoint out = Pin;
	ON_2dPoint nnext;
	int deck_in[2] = { 0,0 };
	//  decompose Pin
	//     Pin = m_dom.ParameterAt( deck + nnext)
	// where nnext[i] is in [0.0, 1.0)
	for (int i = 0; i < 2; i++)
	{
		nnext[i] = m_dom[i].NormalizedParameterAt(out[i]);
		if (m_closed[i])
		{
			deck_in[i] = int(floor(nnext[i]));
			nnext[i] -= deck_in[i];
		}
	}


	if (m_nprev == ON_2dPoint::UnsetPoint)
	{
		if( !stealth)
		{ 
			m_nprev = nnext;
			m_deck[0] = deck_in[0];
			m_deck[1] = deck_in[1];
		}
		return Pin;
	}

	int deck[2] = { m_deck[0], m_deck[1] };
	for (int i = 0; i < 2; i++)
	{
		if (!m_closed[i])
			continue;
		if (m_nprev[i]<m_normband &&  nnext[i]>1.0 - m_normband)
			deck[i] --;
		else if (m_nprev[i] > 1.0 - m_normband && nnext[i] < m_normband)
			deck[i]++;
	}

	for (int i = 0; i < 2; i++)
		out[i] = m_dom[i].ParameterAt(deck[i] + nnext[i]);
	
	if (!stealth)
	{
		m_deck[0] = deck[0]; 
		m_deck[1] = deck[1];
		m_nprev = nnext;
	}

	return out;
}

ON_2dPoint ON_PeriodicDomain::LiftInverse(ON_2dPoint p)
{
	return ON_LiftInverse(p, m_dom, m_closed);
}

ON_SimpleArray<ON_2dPoint> ON_LiftToCover(
	const ON_SimpleArray<ON_2dPoint>& in,
	const ON_Interval dom[2], bool closed[2],
	double normband)
{
	ON_PeriodicDomain Cover(dom, closed, normband);
	ON_SimpleArray<ON_2dPoint> out(in.Count());
	for (int i = 0; i < in.Count(); i++)
		out.Append(Cover.LiftToCover(in[i]));

	return out;
}

ON_2dPoint ON_LiftInverse(ON_2dPoint P, ON_Interval dom[2], bool closed[2])
{
	ON_2dPoint Q = P;
	if (closed[0] || closed[1])
	{
		for (int di = 0; di < 2; di++)
		{
			if (closed[di])
				Q[di] -= floor((Q[di] - dom[di][0]) / dom[di].Length())*dom[di].Length();

		}
	}
	return Q;
}

