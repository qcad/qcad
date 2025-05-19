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

static void SwapRow( double matrix[4][4], int i0, int i1 )
{
  double* p0;
  double* p1;
  double t;
  p0 = &matrix[i0][0];
  p1 = &matrix[i1][0];
  t = *p0; *p0++ = *p1; *p1++ = t;
  t = *p0; *p0++ = *p1; *p1++ = t;
  t = *p0; *p0++ = *p1; *p1++ = t;
  t = *p0; *p0   = *p1; *p1 = t;
}

static void SwapCol( double matrix[4][4], int j0, int j1 )
{
  double* p0;
  double* p1;
  double t;
  p0 = &matrix[0][j0];
  p1 = &matrix[0][j1];
  t = *p0; *p0 = *p1; *p1 = t;
  p0 += 4; p1 += 4;
  t = *p0; *p0 = *p1; *p1 = t;
  p0 += 4; p1 += 4;
  t = *p0; *p0 = *p1; *p1 = t;
  p0 += 4; p1 += 4;
  t = *p0; *p0 = *p1; *p1 = t;
}

//static void ScaleRow( double matrix[4][4], double c, int i )
//{
//  double* p = &matrix[i][0];
//  *p++ *= c;
//  *p++ *= c;
//  *p++ *= c;
//  *p   *= c;
//}
//
//static void InvScaleRow( double matrix[4][4], double c, int i )
//{
//  double* p = &matrix[i][0];
//  *p++ /= c;
//  *p++ /= c;
//  *p++ /= c;
//  *p   /= c;
//}

static void AddCxRow( double matrix[4][4], double c, int i0, int i1 )
{
  const double* p0;
  double* p1;
  p0 = &matrix[i0][0];
  p1 = &matrix[i1][0];
  *p1++ += c* *p0++;
  *p1++ += c* *p0++;
  *p1++ += c* *p0++;
  *p1   += c* *p0;
}

/*
static void AddCxCol( double matrix[4][4], double c, int j0, int j1 )
{
  const double* p0;
  double* p1;
  p0 = &matrix[0][j0];
  p1 = &matrix[0][j1];
  *p1 += c* *p0;
  p0 += 4; p1 += 4;
  *p1 += c* *p0;
  p0 += 4; p1 += 4;
  *p1 += c* *p0;
  p0 += 4; p1 += 4;
  *p1 += c* *p0;
}
*/

static int Inv( const double* src, double dst[4][4], double* determinant, double* pivot )
{
  // returns rank (0, 1, 2, 3, or 4), inverse, and smallest pivot

	double M[4][4], I[4][4], x, c, d;
	int i, j, ix, jx;
  int col[4] = {0,1,2,3};
  int swapcount = 0;
  int rank = 0;

  *pivot = 0.0;
  *determinant = 0.0;

  memset( I, 0, sizeof(I) );
  I[0][0] = I[1][1] = I[2][2] = I[3][3] = 1.0;

  memcpy( M, src, sizeof(M) );

  // some loops unrolled for speed

  ix = jx = 0;
	x = fabs(M[0][0]);
  for ( i = 0; i < 4; i++ ) for ( j = 0; j < 4; j++ ) {
    if ( fabs(M[i][j]) > x ) {
      ix = i;
      jx = j;
      x = fabs(M[i][j]);
    }
  }
  *pivot = x;
  if ( ix != 0 ) {
    SwapRow( M, 0, ix );
    SwapRow( I, 0, ix );
    swapcount++;
  }
  if ( jx != 0 ) {
    SwapCol( M, 0, jx );
    col[0] = jx;
    swapcount++;
  }

  if ( x > 0.0 ) {
    rank++;

    // 17 August 2011 Dale Lear
    //   The result is slightly more accurate when using division
    //   instead of multiplying by the inverse of M[0][0]. If there
    //   is any speed penalty at this point in history, the accuracy
    //   is more important than the additional clocks.
    //c = d = 1.0/M[0][0];
    //M[0][1] *= c; M[0][2] *= c; M[0][3] *= c;
    //ScaleRow( I, c, 0 );
    c = M[0][0];
    M[0][1] /= c; M[0][2] /= c; M[0][3] /= c;
    I[0][0] /= c; I[0][1] /= c; I[0][2] /= c; I[0][3] /= c;
    d = 1.0/c;

    x *=  ON_EPSILON;

	  if (fabs(M[1][0]) > x) {
		  c = -M[1][0];
      M[1][1] += c*M[0][1]; M[1][2] += c*M[0][2]; M[1][3] += c*M[0][3];
      AddCxRow( I, c, 0, 1 );
	  }
	  if (fabs(M[2][0]) >  x) {
		  c = -M[2][0];
      M[2][1] += c*M[0][1]; M[2][2] += c*M[0][2]; M[2][3] += c*M[0][3];
      AddCxRow( I, c, 0, 2 );
	  }
	  if (fabs(M[3][0]) >  x) {
		  c = -M[3][0];
      M[3][1] += c*M[0][1]; M[3][2] += c*M[0][2]; M[3][3] += c*M[0][3];
      AddCxRow( I, c, 0, 3 );
	  }

    ix = jx = 1;
	  x = fabs(M[1][1]);
    for ( i = 1; i < 4; i++ ) for ( j = 1; j < 4; j++ ) {
      if ( fabs(M[i][j]) > x ) {
        ix = i;
        jx = j;
        x = fabs(M[i][j]);
      }
    }
    if ( x < *pivot )
      *pivot = x;
    if ( ix != 1 ) {
      SwapRow( M, 1, ix );
      SwapRow( I, 1, ix );
      swapcount++;
    }
    if ( jx != 1 ) {
      SwapCol( M, 1, jx );
      col[1] = jx;
      swapcount++;
    }
    if ( x > 0.0 ) {
      rank++;

      // 17 August 2011 Dale Lear
      //   The result is slightly more accurate when using division
      //   instead of multiplying by the inverse of M[1][1]. If there
      //   is any speed penalty at this point in history, the accuracy
      //   is more important than the additional clocks.
      //c = 1.0/M[1][1];
      //d *= c;
      //M[1][2] *= c; M[1][3] *= c;
      //ScaleRow( I, c, 1 );
      c = M[1][1];
      M[1][2] /= c; M[1][3] /= c;
      I[1][0] /= c; I[1][1] /= c; I[1][2] /= c; I[1][3] /= c;
      d /= c;

      x *= ON_EPSILON;
      if (fabs(M[0][1]) >  x) {
        c = -M[0][1];
        M[0][2] += c*M[1][2]; M[0][3] += c*M[1][3];
        AddCxRow( I, c, 1, 0 );
      }
      if (fabs(M[2][1]) >  x) {
        c = -M[2][1];
        M[2][2] += c*M[1][2]; M[2][3] += c*M[1][3];
        AddCxRow( I, c, 1, 2 );
      }
      if (fabs(M[3][1]) >  x) {
        c = -M[3][1];
        M[3][2] += c*M[1][2]; M[3][3] += c*M[1][3];
        AddCxRow( I, c, 1, 3 );
      }

      ix = jx = 2;
	    x = fabs(M[2][2]);
      for ( i = 2; i < 4; i++ ) for ( j = 2; j < 4; j++ ) {
        if ( fabs(M[i][j]) > x ) {
          ix = i;
          jx = j;
          x = fabs(M[i][j]);
        }
      }
      if ( x < *pivot )
        *pivot = x;
      if ( ix != 2 ) {
        SwapRow( M, 2, ix );
        SwapRow( I, 2, ix );
        swapcount++;
      }
      if ( jx != 2 ) {
        SwapCol( M, 2, jx );
        col[2] = jx;
        swapcount++;
      }
      if ( x > 0.0 ) {
        rank++;

        // 17 August 2011 Dale Lear
        //   The result is slightly more accurate when using division
        //   instead of multiplying by the inverse of M[2][2]. If there
        //   is any speed penalty at this point in history, the accuracy
        //   is more important than the additional clocks.
        //c = 1.0/M[2][2];
        //d *= c;
        //M[2][3] *= c;
        //ScaleRow( I, c, 2 );
        c = M[2][2];
        M[2][3] /= c;
        I[2][0] /= c; I[2][1] /= c; I[2][2] /= c; I[2][3] /= c;
        d /= c;

        x *= ON_EPSILON;
        if (fabs(M[0][2]) >  x) {
          c = -M[0][2];
          M[0][3] += c*M[2][3];
          AddCxRow( I, c, 2, 0 );
        }
        if (fabs(M[1][2]) >  x) {
          c = -M[1][2];
          M[1][3] += c*M[2][3];
          AddCxRow( I, c, 2, 1 );
        }
        if (fabs(M[3][2]) >  x) {
          c = -M[3][2];
          M[3][3] += c*M[2][3];
          AddCxRow( I, c, 2, 3 );
        }

        x = fabs(M[3][3]);
        if ( x < *pivot )
          *pivot = x;

        if ( x > 0.0 ) {
          rank++;

          // 17 August 2011 Dale Lear
          //   The result is slightly more accurate when using division
          //   instead of multiplying by the inverse of M[3][3]. If there
          //   is any speed penalty at this point in history, the accuracy
          //   is more important than the additional clocks.
          //c = 1.0/M[3][3];
          //d *= c;
          //ScaleRow( I, c, 3 );
          c = M[3][3];
          I[3][0] /= c; I[3][1] /= c; I[3][2] /= c; I[3][3] /= c;
          d /= c;

          x *= ON_EPSILON;
          if (fabs(M[0][3]) >  x) {
            AddCxRow( I, -M[0][3], 3, 0 );
          }
          if (fabs(M[1][3]) >  x) {
            AddCxRow( I, -M[1][3], 3, 1 );
          }
          if (fabs(M[2][3]) >  x) {
            AddCxRow( I, -M[2][3], 3, 2 );
          }

          *determinant = (swapcount%2) ? -d : d;
        }
      }
    }
  }

  if ( col[3] != 3 )
    SwapRow( I, 3, col[3] );
  if ( col[2] != 2 )
    SwapRow( I, 2, col[2] );
  if ( col[1] != 1 )
    SwapRow( I, 1, col[1] );
  if ( col[0] != 0 )
    SwapRow( I, 0, col[0] );

  memcpy( dst, I, sizeof(I) );
	return rank;
}

///////////////////////////////////////////////////////////////
//
// ON_Xform constructors
//

ON_Xform::ON_Xform()
{
  memset( m_xform, 0, sizeof(m_xform) );
  m_xform[3][3] = 1.0;
}

ON_Xform::ON_Xform(
  double x
)
{
  memset( m_xform, 0, sizeof(m_xform) );
  m_xform[0][0] = x;
  m_xform[1][1] = x;
  m_xform[2][2] = x;
  m_xform[3][3] = 1.0;
}

const ON_Xform ON_Xform::DiagonalTransformation(
  double d
)
{
  return ON_Xform::DiagonalTransformation(d, d, d);
}

const ON_Xform ON_Xform::DiagonalTransformation(
  const ON_3dVector& diagnoal
)
{
  return ON_Xform::DiagonalTransformation(diagnoal.x, diagnoal.y, diagnoal.z);
}

const ON_Xform ON_Xform::DiagonalTransformation(
  double d0,
  double d1,
  double d2
)
{
  ON_Xform xform(ON_Xform::IdentityTransformation);
  xform.m_xform[0][0] = d0;
  xform.m_xform[1][1] = d1;
  xform.m_xform[2][2] = d2;
  return xform;
}

#if defined(ON_COMPILER_MSC)
ON_Xform::ON_Xform( double m[4][4] )
{
  memcpy( m_xform, m, sizeof(m_xform) );
}
#endif

ON_Xform::ON_Xform( const double m[4][4] )
{
  memcpy( m_xform, m, sizeof(m_xform) );
}

#if defined(ON_COMPILER_MSC)
ON_Xform::ON_Xform( float m[4][4] )
{
  m_xform[0][0] = (double)m[0][0];
  m_xform[0][1] = (double)m[0][1];
  m_xform[0][2] = (double)m[0][2];
  m_xform[0][3] = (double)m[0][3];

  m_xform[1][0] = (double)m[1][0];
  m_xform[1][1] = (double)m[1][1];
  m_xform[1][2] = (double)m[1][2];
  m_xform[1][3] = (double)m[1][3];

  m_xform[2][0] = (double)m[2][0];
  m_xform[2][1] = (double)m[2][1];
  m_xform[2][2] = (double)m[2][2];
  m_xform[2][3] = (double)m[2][3];

  m_xform[3][0] = (double)m[3][0];
  m_xform[3][1] = (double)m[3][1];
  m_xform[3][2] = (double)m[3][2];
  m_xform[3][3] = (double)m[3][3];
}
#endif

ON_Xform::ON_Xform( const float m[4][4] )
{
  m_xform[0][0] = (double)m[0][0];
  m_xform[0][1] = (double)m[0][1];
  m_xform[0][2] = (double)m[0][2];
  m_xform[0][3] = (double)m[0][3];

  m_xform[1][0] = (double)m[1][0];
  m_xform[1][1] = (double)m[1][1];
  m_xform[1][2] = (double)m[1][2];
  m_xform[1][3] = (double)m[1][3];

  m_xform[2][0] = (double)m[2][0];
  m_xform[2][1] = (double)m[2][1];
  m_xform[2][2] = (double)m[2][2];
  m_xform[2][3] = (double)m[2][3];

  m_xform[3][0] = (double)m[3][0];
  m_xform[3][1] = (double)m[3][1];
  m_xform[3][2] = (double)m[3][2];
  m_xform[3][3] = (double)m[3][3];
}

ON_Xform::ON_Xform( const double* m )
{
  memcpy( m_xform, m, sizeof(m_xform) );
}

ON_Xform::ON_Xform( const float* m )
{
  m_xform[0][0] = (double)m[0];
  m_xform[0][1] = (double)m[1];
  m_xform[0][2] = (double)m[2];
  m_xform[0][3] = (double)m[3];

  m_xform[1][0] = (double)m[4];
  m_xform[1][1] = (double)m[5];
  m_xform[1][2] = (double)m[6];
  m_xform[1][3] = (double)m[7];

  m_xform[2][0] = (double)m[8];
  m_xform[2][1] = (double)m[9];
  m_xform[2][2] = (double)m[10];
  m_xform[2][3] = (double)m[11];

  m_xform[3][0] = (double)m[12];
  m_xform[3][1] = (double)m[13];
  m_xform[3][2] = (double)m[14];
  m_xform[3][3] = (double)m[15];
}

ON_Xform::ON_Xform( const ON_3dPoint& P,
														 const ON_3dVector& X,
														 const ON_3dVector& Y,
														 const ON_3dVector& Z)
{
  m_xform[0][0] = X[0];
  m_xform[1][0] = X[1];
  m_xform[2][0] = X[2];
  m_xform[3][0] = 0;

  m_xform[0][1] = Y[0];
  m_xform[1][1] = Y[1];
  m_xform[2][1] = Y[2];
  m_xform[3][1] = 0;

  m_xform[0][2] = Z[0];
  m_xform[1][2] = Z[1];
  m_xform[2][2] = Z[2];
  m_xform[3][2] = 0;

  m_xform[0][3] = P[0];
  m_xform[1][3] = P[1];
  m_xform[2][3] = P[2];
  m_xform[3][3] = 1;
}

ON_Xform::ON_Xform( const ON_Matrix& m )
{
  *this = m;
}

///////////////////////////////////////////////////////////////
//
// ON_Xform operator[]
//


double* ON_Xform::operator[](int i)
{
  return ( i >= 0 && i < 4 ) ? &m_xform[i][0] : nullptr;
}

const double* ON_Xform::operator[](int i) const
{
  return ( i >= 0 && i < 4 ) ? &m_xform[i][0] : nullptr;
}

///////////////////////////////////////////////////////////////
//
// ON_Xform operator* operator- operator+
//
// All non-commutative operations have "this" as left hand side and
// argument as right hand side.
ON_Xform ON_Xform::operator*( const ON_Xform& rhs ) const
{
  double m[4][4];
  const double* p = &rhs.m_xform[0][0];

  m[0][0] = m_xform[0][0]*p[0] + m_xform[0][1]*p[4] + m_xform[0][2]*p[ 8] + m_xform[0][3]*p[12];
  m[0][1] = m_xform[0][0]*p[1] + m_xform[0][1]*p[5] + m_xform[0][2]*p[ 9] + m_xform[0][3]*p[13];
  m[0][2] = m_xform[0][0]*p[2] + m_xform[0][1]*p[6] + m_xform[0][2]*p[10] + m_xform[0][3]*p[14];
  m[0][3] = m_xform[0][0]*p[3] + m_xform[0][1]*p[7] + m_xform[0][2]*p[11] + m_xform[0][3]*p[15];

  m[1][0] = m_xform[1][0]*p[0] + m_xform[1][1]*p[4] + m_xform[1][2]*p[ 8] + m_xform[1][3]*p[12];
  m[1][1] = m_xform[1][0]*p[1] + m_xform[1][1]*p[5] + m_xform[1][2]*p[ 9] + m_xform[1][3]*p[13];
  m[1][2] = m_xform[1][0]*p[2] + m_xform[1][1]*p[6] + m_xform[1][2]*p[10] + m_xform[1][3]*p[14];
  m[1][3] = m_xform[1][0]*p[3] + m_xform[1][1]*p[7] + m_xform[1][2]*p[11] + m_xform[1][3]*p[15];

  m[2][0] = m_xform[2][0]*p[0] + m_xform[2][1]*p[4] + m_xform[2][2]*p[ 8] + m_xform[2][3]*p[12];
  m[2][1] = m_xform[2][0]*p[1] + m_xform[2][1]*p[5] + m_xform[2][2]*p[ 9] + m_xform[2][3]*p[13];
  m[2][2] = m_xform[2][0]*p[2] + m_xform[2][1]*p[6] + m_xform[2][2]*p[10] + m_xform[2][3]*p[14];
  m[2][3] = m_xform[2][0]*p[3] + m_xform[2][1]*p[7] + m_xform[2][2]*p[11] + m_xform[2][3]*p[15];

  m[3][0] = m_xform[3][0]*p[0] + m_xform[3][1]*p[4] + m_xform[3][2]*p[ 8] + m_xform[3][3]*p[12];
  m[3][1] = m_xform[3][0]*p[1] + m_xform[3][1]*p[5] + m_xform[3][2]*p[ 9] + m_xform[3][3]*p[13];
  m[3][2] = m_xform[3][0]*p[2] + m_xform[3][1]*p[6] + m_xform[3][2]*p[10] + m_xform[3][3]*p[14];
  m[3][3] = m_xform[3][0]*p[3] + m_xform[3][1]*p[7] + m_xform[3][2]*p[11] + m_xform[3][3]*p[15];

  return ON_Xform(m);
}

ON_Xform ON_Xform::operator+( const ON_Xform& rhs ) const
{
  double m[4][4];
  const double* p = &rhs.m_xform[0][0];

  m[0][0] = m_xform[0][0] + p[0];
  m[0][1] = m_xform[0][1] + p[1];
  m[0][2] = m_xform[0][2] + p[2];
  m[0][3] = m_xform[0][3] + p[3];

  m[1][0] = m_xform[1][0] + p[4];
  m[1][1] = m_xform[1][1] + p[5];
  m[1][2] = m_xform[1][2] + p[6];
  m[1][3] = m_xform[1][3] + p[7];

  m[2][0] = m_xform[2][0] + p[ 8];
  m[2][1] = m_xform[2][1] + p[ 9];
  m[2][2] = m_xform[2][2] + p[10];
  m[2][3] = m_xform[2][3] + p[11];

  m[3][0] = m_xform[3][0] + p[12];
  m[3][1] = m_xform[3][1] + p[13];
  m[3][2] = m_xform[3][2] + p[14];
  m[3][3] = m_xform[3][3] + p[15];

  return ON_Xform(m);
}

ON_Xform ON_Xform::operator-( const ON_Xform& rhs ) const
{
  double m[4][4];
  const double* p = &rhs.m_xform[0][0];

  m[0][0] = m_xform[0][0] - p[0];
  m[0][1] = m_xform[0][1] - p[1];
  m[0][2] = m_xform[0][2] - p[2];
  m[0][3] = m_xform[0][3] - p[3];

  m[1][0] = m_xform[1][0] - p[4];
  m[1][1] = m_xform[1][1] - p[5];
  m[1][2] = m_xform[1][2] - p[6];
  m[1][3] = m_xform[1][3] - p[7];

  m[2][0] = m_xform[2][0] - p[ 8];
  m[2][1] = m_xform[2][1] - p[ 9];
  m[2][2] = m_xform[2][2] - p[10];
  m[2][3] = m_xform[2][3] - p[11];

  m[3][0] = m_xform[3][0] - p[12];
  m[3][1] = m_xform[3][1] - p[13];
  m[3][2] = m_xform[3][2] - p[14];
  m[3][3] = m_xform[3][3] - p[15];

  return ON_Xform(m);
}
  
///////////////////////////////////////////////////////////////
//
// ON_Xform
//


void ON_Xform::Identity()
{
  memset( m_xform, 0, sizeof(m_xform) );
  m_xform[0][0] = m_xform[1][1] = m_xform[2][2] = m_xform[3][3] = 1.0;
}

void ON_Xform::Diagonal( double d )
{
  memset( m_xform, 0, sizeof(m_xform) );
  m_xform[0][0] = m_xform[1][1] = m_xform[2][2] = d;
  m_xform[3][3] = 1.0;
}

void ON_Xform::Scale( double x, double y, double z )
{
  memset( m_xform, 0, sizeof(m_xform) );
  m_xform[0][0] = x;
  m_xform[1][1] = y;
  m_xform[2][2] = z;
  m_xform[3][3] = 1.0;
}

void ON_Xform::Scale( const ON_3dVector& v )
{
  memset( m_xform, 0, sizeof(m_xform) );
  m_xform[0][0] = v.x;
  m_xform[1][1] = v.y;
  m_xform[2][2] = v.z;
  m_xform[3][3] = 1.0;
}


void ON_Xform::Scale
  (
  ON_3dPoint fixed_point,
  double scale_factor
  )
{
  *this = ON_Xform::ScaleTransformation(fixed_point, scale_factor);
}

const ON_Xform ON_Xform::ScaleTransformation(
  const ON_3dPoint& fixed_point,
  double scale_factor
)
{
  return ON_Xform::ScaleTransformation(fixed_point, scale_factor, scale_factor, scale_factor);
}

const ON_Xform ON_Xform::ScaleTransformation(
  const ON_3dPoint& fixed_point,
  double x_scale_factor,
  double y_scale_factor,
  double z_scale_factor
)
{
  const ON_Xform s(ON_Xform::DiagonalTransformation(x_scale_factor, y_scale_factor, z_scale_factor));
  if ( fixed_point.x == 0.0 && fixed_point.y == 0.0 && fixed_point.z == 0.0 )
  {
    return s;
  }

  const ON_3dVector delta = fixed_point - ON_3dPoint::Origin;
  ON_Xform t0(ON_Xform::TranslationTransformation(-delta));
  ON_Xform t1(ON_Xform::TranslationTransformation(delta));
  return (t1*s*t0);
}

void ON_Xform::Scale
(
  const ON_Plane& plane,
  double x_scale_factor,
  double y_scale_factor,
  double z_scale_factor
)
{
  *this = ON_Xform::ScaleTransformation(plane, x_scale_factor, z_scale_factor, y_scale_factor);
}

const ON_Xform ON_Xform::ScaleTransformation
  (
  const ON_Plane& plane,
  double x_scale_factor,
  double y_scale_factor,
  double z_scale_factor
  )
{
  return 
    (x_scale_factor == y_scale_factor && x_scale_factor == z_scale_factor)
    ? ON_Xform::ScaleTransformation(plane.origin,x_scale_factor)
    : ON_Xform::ShearTransformation( plane, x_scale_factor*plane.xaxis, y_scale_factor*plane.yaxis, z_scale_factor*plane.zaxis );
}

void ON_Xform::Shear
(
  const ON_Plane& plane,
  const ON_3dVector& x1,
  const ON_3dVector& y1,
  const ON_3dVector& z1
)
{
  *this = ON_Xform::ShearTransformation(plane, x1, y1, z1);
}

const ON_Xform ON_Xform::ShearTransformation(
    const ON_Plane& plane,
    const ON_3dVector& x1,
    const ON_3dVector& y1,
    const ON_3dVector& z1
  )
{
  const ON_3dVector delta = plane.origin - ON_3dPoint::Origin;
  const ON_Xform t0(ON_Xform::TranslationTransformation(-delta));
  const ON_Xform t1(ON_Xform::TranslationTransformation(delta));
  ON_Xform s0(ON_Xform::IdentityTransformation);
  ON_Xform s1(ON_Xform::IdentityTransformation);
  s0.m_xform[0][0] = plane.xaxis.x;
  s0.m_xform[0][1] = plane.xaxis.y;
  s0.m_xform[0][2] = plane.xaxis.z;
  s0.m_xform[1][0] = plane.yaxis.x;
  s0.m_xform[1][1] = plane.yaxis.y;
  s0.m_xform[1][2] = plane.yaxis.z;
  s0.m_xform[2][0] = plane.zaxis.x;
  s0.m_xform[2][1] = plane.zaxis.y;
  s0.m_xform[2][2] = plane.zaxis.z;
  s1.m_xform[0][0] = x1.x;
  s1.m_xform[1][0] = x1.y;
  s1.m_xform[2][0] = x1.z;
  s1.m_xform[0][1] = y1.x;
  s1.m_xform[1][1] = y1.y;
  s1.m_xform[2][1] = y1.z;
  s1.m_xform[0][2] = z1.x;
  s1.m_xform[1][2] = z1.y;
  s1.m_xform[2][2] = z1.z;
  return (t1*s1*s0*t0);
}

void ON_Xform::Translation( double dx, double dy, double dz )
{
  *this = ON_Xform::TranslationTransformation(dx,dy,dz);
}

void ON_Xform::Translation( const ON_3dVector& delta )
{
  *this = ON_Xform::TranslationTransformation(delta);
}

const ON_Xform ON_Xform::TranslationTransformation(
  const ON_2dVector& delta
)
{
  return ON_Xform::TranslationTransformation(delta.x, delta.y, 0.0);
}

const ON_Xform ON_Xform::TranslationTransformation(
  const ON_3dVector& delta
)
{
  return ON_Xform::TranslationTransformation(delta.x, delta.y, delta.z);
}

const ON_Xform ON_Xform::TranslationTransformation(
  double dx,
  double dy,
  double dz
)
{
  ON_Xform xform(ON_Xform::IdentityTransformation);
  xform.m_xform[0][3] = dx;
  xform.m_xform[1][3] = dy;
  xform.m_xform[2][3] = dz;
  return xform;
}

void ON_Xform::PlanarProjection( const ON_Plane& plane )
{
  int i, j;
  double x[3] = {plane.xaxis.x,plane.xaxis.y,plane.xaxis.z};
  double y[3] = {plane.yaxis.x,plane.yaxis.y,plane.yaxis.z};
  double p[3] = {plane.origin.x,plane.origin.y,plane.origin.z};
  double q[3];
  for ( i = 0; i < 3; i++ ) 
  {
    for ( j = 0; j < 3; j++ )
    {
      m_xform[i][j] = x[i]*x[j] + y[i]*y[j];
    }
    q[i] = m_xform[i][0]*p[0] + m_xform[i][1]*p[1] + m_xform[i][2]*p[2];
  }
  for ( i = 0; i < 3; i++ )
  {
    m_xform[3][i] = 0.0;
    m_xform[i][3] = p[i]-q[i];
  }
  m_xform[3][3] = 1.0;
}

///////////////////////////////////////////////////////////////
//
// ON_Xform
//

void ON_Xform::ActOnLeft(double x,double y,double z,double w,double v[4]) const
{
  if ( v )
  {
    v[0] = m_xform[0][0]*x + m_xform[0][1]*y + m_xform[0][2]*z + m_xform[0][3]*w;
    v[1] = m_xform[1][0]*x + m_xform[1][1]*y + m_xform[1][2]*z + m_xform[1][3]*w;
    v[2] = m_xform[2][0]*x + m_xform[2][1]*y + m_xform[2][2]*z + m_xform[2][3]*w;
    v[3] = m_xform[3][0]*x + m_xform[3][1]*y + m_xform[3][2]*z + m_xform[3][3]*w;
  }
}

void ON_Xform::ActOnRight(double x,double y,double z,double w,double v[4]) const
{
  if ( v )
  {
    v[0] = m_xform[0][0]*x + m_xform[1][0]*y + m_xform[2][0]*z + m_xform[3][0]*w;
    v[1] = m_xform[0][1]*x + m_xform[1][1]*y + m_xform[2][1]*z + m_xform[3][1]*w;
    v[2] = m_xform[0][2]*x + m_xform[1][2]*y + m_xform[2][2]*z + m_xform[3][2]*w;
    v[3] = m_xform[0][3]*x + m_xform[1][3]*y + m_xform[2][3]*z + m_xform[3][3]*w;
  }
}

const ON_Xform operator*(double c, const ON_Xform& xform)
{
  ON_Xform cx(xform);
  double* p = &cx.m_xform[0][0];
  double* p1 = p + 16;
  while (p < p1)
  {
    const double x = *p;
    *p++ = c*x;
  }
  return cx;
}

const ON_Xform operator*(const ON_Xform& xform, double c)
{
  ON_Xform xc(xform);
  double* p = &xc.m_xform[0][0];
  double* p1 = p + 16;
  while (p < p1)
  {
    const double x = *p;
    *p++ = x*c;
  }
  return xc;
}


ON_2dPoint ON_Xform::operator*( const ON_2dPoint& p ) const
{
  // Note well: The right hand column and bottom row have an important effect 
  // when transforming a Euclidean point and have no effect when transforming a vector. 
  // Be sure you understand the differences between vectors and points when applying a 4x4 transformation.
  const double x = p.x; // optimizer should put x,y in registers
  const double y = p.y;
  double xh[2], w;
  const double* m = &m_xform[0][0];
  xh[0] = m[ 0]*x + m[ 1]*y + m[ 3];
  xh[1] = m[ 4]*x + m[ 5]*y + m[ 7];
  w     = m[12]*x + m[13]*y + m[15];
  w = (w != 0.0) ? 1.0/w : 1.0;
  return ON_2dPoint( w*xh[0], w*xh[1] );
}

ON_3dPoint ON_Xform::operator*( const ON_3dPoint& p ) const
{
  // Note well: The right hand column and bottom row have an important effect 
  // when transforming a Euclidean point and have no effect when transforming a vector. 
  // Be sure you understand the differences between vectors and points when applying a 4x4 transformation.
  const double x = p.x; // optimizer should put x,y,z in registers
  const double y = p.y;
  const double z = p.z;
  double xh[3], w;
  const double* m = &m_xform[0][0];
  xh[0] = m[ 0]*x + m[ 1]*y + m[ 2]*z + m[ 3];
  xh[1] = m[ 4]*x + m[ 5]*y + m[ 6]*z + m[ 7];
  xh[2] = m[ 8]*x + m[ 9]*y + m[10]*z + m[11];
  w     = m[12]*x + m[13]*y + m[14]*z + m[15];
  w = (w != 0.0) ? 1.0/w : 1.0;
  return ON_3dPoint( w*xh[0], w*xh[1], w*xh[2] );
}

ON_4dPoint ON_Xform::operator*( const ON_4dPoint& h ) const
{
  const double x = h.x; // optimizer should put x,y,z,w in registers
  const double y = h.y;
  const double z = h.z;
  const double w = h.w;
  double xh[4];
  const double* m = &m_xform[0][0];
  xh[0] = m[ 0]*x + m[ 1]*y + m[ 2]*z + m[ 3]*w;
  xh[1] = m[ 4]*x + m[ 5]*y + m[ 6]*z + m[ 7]*w;
  xh[2] = m[ 8]*x + m[ 9]*y + m[10]*z + m[11]*w;
  xh[3] = m[12]*x + m[13]*y + m[14]*z + m[15]*w;
  return ON_4dPoint( xh[0],xh[1],xh[2],xh[3] );
}

ON_2dVector ON_Xform::operator*( const ON_2dVector& v ) const
{
  // Note well: The right hand column and bottom row have an important effect 
  // when transforming a Euclidean point and have no effect when transforming a vector. 
  // Be sure you understand the differences between vectors and points when applying a 4x4 transformation.
  const double x = v.x; // optimizer should put x,y in registers
  const double y = v.y;
  double xh[2];
  const double* m = &m_xform[0][0];
  xh[0] = m[0]*x + m[1]*y;
  xh[1] = m[4]*x + m[5]*y;
  return ON_2dVector( xh[0],xh[1] );
}

ON_3dVector ON_Xform::operator*( const ON_3dVector& v ) const
{
  // Note well: The right hand column and bottom row have an important effect 
  // when transforming a Euclidean point and have no effect when transforming a vector. 
  // Be sure you understand the differences between vectors and points when applying a 4x4 transformation.
  const double x = v.x; // optimizer should put x,y,z in registers
  const double y = v.y;
  const double z = v.z;
  double xh[3];
  const double* m = &m_xform[0][0];
  xh[0] = m[0]*x + m[1]*y + m[ 2]*z;
  xh[1] = m[4]*x + m[5]*y + m[ 6]*z;
  xh[2] = m[8]*x + m[9]*y + m[10]*z;
  return ON_3dVector( xh[0],xh[1],xh[2] );
}

const ON_SHA1_Hash ON_Xform::Hash() const
{
  ON_SHA1 sha1;
  sha1.AccumulateDoubleArray(16, &this->m_xform[0][0]);
  return sha1.Hash();
}

ON__UINT32 ON_Xform::CRC32(ON__UINT32 current_remainder) const
{
  const ON_SHA1_Hash hash = this->Hash();
  return ON_CRC32(current_remainder, sizeof(hash), &hash);
}

bool ON_Xform::IsValid() const
{
  const double* x = &m_xform[0][0];
  const double* x16 = x + 16;
  while ( x < x16 )
  {
    const double t = *x++;
    if (ON_IS_VALID(t))
      continue;
    return false; // t is not valid
  }
  return true;
}

bool ON_Xform::IsNan() const
{
  const double* x = &m_xform[0][0];
  const double* x16 = x + 16;
  while ( x < x16 )
  {
    const double t = *x++;
    if (!(t == t))
      return true; // t is a nan
  }
  return false;
}

bool ON_Xform::operator==(const ON_Xform& rhs) const
{
  // Intentionally returns false if any coefficient is a nan.
  const double* x = &m_xform[0][0];
  const double* x16 = x + 16;
  const double* y = &rhs.m_xform[0][0];
  while (x < x16)
  {
    if (*x++ == *y++)
      continue;
    return false; // not equal or a nan
  }
  return true;
}

bool ON_Xform::operator!=(const ON_Xform& rhs) const
{
  // Intentionally returns false if any coefficient is a nan.
  const double* x = &m_xform[0][0];
  const double* x16 = x + 16;
  const double* y = &rhs.m_xform[0][0];
  while (x < x16)
  {
    double a = *x++;
    double b = *y++;
    if (a == b)
      continue;
    if (a != b)
    {
      while (x < x16)
      {
        a = *x++;
        b = *y++;
        if (a == a && b == b)
          continue;
        return false; // a or b is a nan.
      }
      return true;  // no nans and at least one not equal equalcoefficient.
    }
  }
  return false; // nans or equal
}

bool ON_Xform::IsIdentity( double zero_tolerance ) const
{
  // The code below will return false if m_xform[][] contains
  // a nan value.

  if (!(zero_tolerance >= 0.0 && zero_tolerance < ON_UNSET_POSITIVE_VALUE))
    return false;

  const double* v = &m_xform[0][0];
  for ( int i = 0; i < 3; i++ )
  {
    if ( !(fabs(1.0 - *v++) <= zero_tolerance) )
      return false;
    if ( !(fabs(*v++) <= zero_tolerance) )
      return false;
    if ( !(fabs(*v++) <= zero_tolerance) )
      return false;
    if ( !(fabs(*v++) <= zero_tolerance) )
      return false;
    if ( !(fabs(*v++) <= zero_tolerance) )
      return false;
  }
  if ( !(fabs( 1.0 - *v ) <= zero_tolerance) )
    return false;

  return true;
}

bool ON_Xform::IsNotIdentity( double zero_tolerance ) const
{
  // It is intentional that this functions returns false if any coefficient is a nan or unset value.
  return (zero_tolerance >= 0.0  && zero_tolerance < ON_UNSET_POSITIVE_VALUE &&  false == ON_Xform::IsIdentity(zero_tolerance) && IsValid());
}

bool ON_Xform::IsValidAndNotZeroAndNotIdentity(
  double zero_tolerance
) const
{
  if (false == IsValid())
    return false;

  if (!(zero_tolerance >= 0.0 && zero_tolerance < ON_UNSET_POSITIVE_VALUE))
    return false;

  int one_count = 0;
  int zero_count = 0;
  const double* v = &m_xform[0][0];
  for ( int i = 0; i < 3; i++ )
  {
    if (fabs(1.0 - *v) <= zero_tolerance)
    {
      // this diagonal coefficient = 1
      one_count++;
      if (zero_count > 0)
        return true;
    }
    else if (fabs(*v) <= zero_tolerance)
    {
      // this diagonal coefficient = 0
      zero_count++;
      if (one_count > 0)
        return true;
    }
    else
    {
      // this diagonal coefficient != 1 and != 0
      return true;
    }

    // If any off diagonal coefficient is not zero, return true
    v++;
    if ( !(fabs(*v++) <= zero_tolerance) )
      return true;
    if ( !(fabs(*v++) <= zero_tolerance) )
      return true;
    if ( !(fabs(*v++) <= zero_tolerance) )
      return true;
    if ( !(fabs(*v++) <= zero_tolerance) )
      return true;
  }

  if (!(fabs(1.0 - *v) <= zero_tolerance))
  {
    if (3 == zero_count && fabs(1.0 - *v) <= zero_tolerance)
      return false; // every matrix coefficient = 0

    // otherwise, xform[3][3] != 1 so return true.
    return true;
  }

  if (3 == one_count || 3 == zero_count)
    return false;

  return true;
}


bool ON_Xform::IsTranslation( double zero_tolerance ) const
{
  if (!(zero_tolerance >= 0.0 && zero_tolerance < ON_UNSET_POSITIVE_VALUE))
    return false;

  const double* v = &m_xform[0][0];
  if ( fabs(1.0 - *v++) > zero_tolerance )
    return false;
  if ( fabs(*v++) >  zero_tolerance )
    return false;
  if ( fabs(*v++) >  zero_tolerance )
    return false;
  v++;
  if ( fabs(*v++) >  zero_tolerance )
    return false;
  if ( fabs(1.0 - *v++) > zero_tolerance )
    return false;
  if ( fabs(*v++) >  zero_tolerance )
    return false;
  v++;
  if ( fabs(*v++) >  zero_tolerance )
    return false;
  if ( fabs(*v++) >  zero_tolerance )
    return false;
  if ( fabs(1.0 - *v++) > zero_tolerance )
    return false;
  v++;
  if ( fabs(*v++) >  zero_tolerance )
    return false;
  if ( fabs(*v++) >  zero_tolerance )
    return false;
  if ( fabs(*v++) >  zero_tolerance )
    return false;
  if ( fabs( 1.0 - *v ) > zero_tolerance )
    return false;

  return IsValid();
}


int ON_Xform::Compare( const ON_Xform& rhs ) const
{
  const double* a = &m_xform[0][0];
  const double* b = &rhs.m_xform[0][0];
  const double* a16 = a + 16;
  while ( a < a16 )
  {
    const double x = *a++;
    const double y = *b++;
    if ( x < y )
      return -1;
    if ( x > y )
      return 1;
    if (x == y)
      continue;

    if (!(x == x))
    {
      // x is a nan
      if (!(y == y))
        continue; // x and y are nans
      return 1; // x is a nan and y is not.
    }

    // y is a nan and x is not a nan.
    return -1;
  }
  return 0;
}



static
ON_Interval BoundEVals( const ON_Xform& M )
{
	// assume M is Linear().
	// Bound the eigenvalues.  Spectrum ( M ) \in [emin, emax]
	// that is if lambda is a eigenvalue of M then emin<=Re(lambda)<=emax
	// Uses Gershgorin circle theorem.
	
	ON_Interval SpectrumHull; 
	for (int i = 0; i < 3; i++)
	{
		double R = 0.0;
		for (int j = 0; j < 3; j++)
			if (j != i) R += fabs( M[i][j] );
		ON_Interval GCircle ( M[i][i] - R , M[i][i] + R );
		if (i == 0)
			SpectrumHull = GCircle;
		else
			SpectrumHull.Union(GCircle);
	}
	return SpectrumHull;
}

// Given a Linear transformation L.  return an interval containing Spectrum(L^T *L)
static ON_Interval ApproxSpectrumLTL(const ON_Xform& L)
{
	// L.IsLinear() is a precondition

	// LTL = L^T * L
	ON_Xform LTL = L;
	LTL.Transpose();
	LTL = LTL * L;

	return  BoundEVals(LTL);
}

// Given a linear transformation bound distance to group of orthogonal transformations
//    dist ( L, O(3) ) < ApproxDist2Ortho(L)
// L = R * P   is the polar decomposition of L.  R is the closest rotation to L and
//   P = (L^T * L)^(-1/2)
// So || L-R || = || R*( P - I ) || = || P - I || = || (L^T L)^(1/2) - I || 
static double ApproxDist2Ortho(const ON_Xform& L)
{
	// L.IsLinear() is a precondition

	ON_Interval Spec = ApproxSpectrumLTL(L);
	if (Spec[0] < 0) Spec[0] = 0.0;
	Spec[0] = sqrt(Spec[0]) - 1.0;
	Spec[1] = sqrt(Spec[1]) - 1.0;		// contains Spectrum of (L^T L)^(-1/2) - I
	double dist = fabs(Spec[0]);
	if (dist < fabs(Spec[1]))
		dist = fabs(Spec[1]);

	return dist;
}

int ON_Xform::IsSimilarity() const
{
	return IsSimilarity(ON_ZERO_TOLERANCE);
}

int ON_Xform::IsSimilarity(double tol) const
{
	// This function does not construct a similarity transformation,
	// ( see ON_Xform::DecomposeSimilarity() for this ).  It merely
	// indicates that this transformation is sufficiently close to a similarity.
	// However using with a tight tolerance like tol<ON_ZERO_TOLERANCE 
	// Indicates that this is very close to being a similar transformation.
	// This calculations is based on approximations and is only  
	// reliable if tolerance << 1.0. 
	int rval = 0;
	if (IsAffine())
	{
		// L = Linear component of this. 
		// LTL = L^T * L
		//  *this is similar iff Spectrum(LTL) = lambda, for real lambda!=0.0
		ON_Xform L = (*this);
		L.Linearize();


		ON_Interval Spectrum = ApproxSpectrumLTL(L);
		double lambda = Spectrum.Mid();
		double dist = Spectrum.Length() / 2.0;
		if (dist < tol && fabs(lambda)>dist )
		{
			double det = L.Determinant();
			rval = (det > 0) ? 1 : -1;
		}
	}
	return rval;
}


int ON_Xform::DecomposeSimilarity(ON_3dVector& T, double& dilation, ON_Xform& R, double tolerance) const
{
	int rval = 0;
	if (IsAffine())
	{
		ON_Xform L;
		DecomposeAffine(T, L);

		/* Three cases:
		I. L is within OrthogonalTol of being orthogonal then just return R = Linear
		(this is an optimization to avoid doing an eigen solve)
		II. Linear<10*tolerance or tol>1.0 then find the closest orthogonal matrix R.
		test the final solution to see if |*this-R|<tolerance .
		III. Otherwise return 0
		*/
		const double OrthogonalTol = 100 * ON_EPSILON;

		ON_Interval Spectrum = ApproxSpectrumLTL(L);

		double dist = Spectrum.Length()/2.0;
		if (dist<OrthogonalTol)
		{
			// Case I.
			double det = L.Determinant();
			dilation = pow(fabs(det), 1.0 / 3.0);
			if (det < 0)
				dilation *= -1.0;
			R = ON_Xform(1.0 / dilation)*L;
			R.Orthogonalize(10*ON_EPSILON);			// tune-it up.
			rval = (det > 0) ? 1 : -1;
		}

		else if (dist < 10 * tolerance || tolerance>1.0)
		{
			// Case II.
			ON_Xform Q;		// ortho change of coordinate matrix
			ON_3dVector lambda;
			ON_3dVector Ttrash;
			if (L.DecomposeAffine(Ttrash, R, Q, lambda))
			{
				// Find the min and max eigen-values
				int mini=0, maxi=0;
				double l0 = ON_DBL_MAX;
				double l1 = ON_DBL_MIN;
				for (int i = 0; i < 3; i++)
				{
					if (lambda[i] < l0)
					{
						mini = i; l0 = lambda[i];
					}
					if (l1< lambda[i])
					{
						maxi = i; l1 = lambda[i];
					}
				}
				double err = (lambda[maxi] - lambda[mini]) / 2.0;
				if (err > tolerance)
					rval = 0;
				else
				{
					dilation = (lambda[mini] + lambda[maxi]) / 2.0;
					rval = (dilation > 0) ? 1 : -1;
					//dilation;
				}
			}			
		}
	}
	return rval;
}


bool ON_Xform::DecomposeSymmetric(ON_Xform& Q, ON_3dVector& diagonal) const
{
	bool rc = false;
	if (IsLinear())
	{
		bool symmetric  = ( m_xform[0][1] == m_xform[1][0] && 
			m_xform[0][2] == m_xform[2][0] && 
			m_xform[1][2] == m_xform[2][1]  );
		if (symmetric)
		{
			ON_3dVector evec[3];
			rc = ON_Sym3x3EigenSolver(m_xform[0][0], m_xform[1][1], m_xform[2][2],
				m_xform[0][1], m_xform[1][2], m_xform[0][2],
				&diagonal.x, evec[0],
				&diagonal.y, evec[1],
				&diagonal.z, evec[2]);
			if (rc)
			{
				Q = ON_Xform(ON_3dPoint::Origin, evec[0], evec[1], evec[2]);
			}
		}
	}
	return rc;
}


int ON_Xform::DecomposeRigid(ON_3dVector& T,  ON_Xform& R, double tolerance) const
{
	int rval = 0;
	if (IsAffine())
	{
		ON_Xform Linear;
		DecomposeAffine(T, Linear);

		
		/* Three cases:
			I. Linear is within OrthogonalTol of being orthogonal then just return R = Linear
				  (this is an optimization to avoid doing an eigen solve)
			II. Linear~~<10*tolerance or tol>1.0 then find the closest orthogonal matrix R.
					test the final solution to see if |*this-R|<tolerance .
			III. Otherwise return 0

			Note:
			A.  I and III are fast and do almost nothing, while II is more involved.
			B.  Use a large tolerance setting to find the nearest rigid motion to a this transformation.
		*/
		const double OrthogonalTol = ON_ZERO_TOLERANCE;

		double dist = ApproxDist2Ortho(Linear);
		if(dist<OrthogonalTol)
		{
			// Case I.
			R = Linear;
			R.Orthogonalize(.001);
			double det = Linear.Determinant();
			rval = (det > 0) ? 1: -1;
		}

		else if (dist < 10*tolerance || tolerance>1.0)
		{
			// Case II.
			// Closest orthogonal matrix is given by polar decomposition
			// BHP Horn, http://people.csail.mit.edu/bkph/articles/Nearest_Orthonormal_Matrix.pdf
			ON_Xform Q;
			ON_3dVector lambda;
			if (DecomposeAffine(T, R, Q, lambda))
			{
				// Is ||R - Linear|| = || R ( I -  Q lam QT ) || = || I -  Q lam QT ||= || Q QT - Q lam QT ||= || I - lam ||
				double err = 0.0;
				for (int i = 0; i < 3; i++)
				{
					double x = fabs(1.0 - lambda[i]);
					if (x > err)
						err = x;
				}
				if (err < tolerance)
				{
					double det = lambda[0] * lambda[1] * lambda[2];
					rval = (det > 0) ? 1 : -1;
				}
			}
		}
	}
	return rval;
}

int ON_Xform::IsRigid(double tolerance) const
{ 
	// This function does not construct a rigid transformation,
	// ( see ON_Xform::DecomposeRigid() for this ).  It merely
	// indicates that this transformation is sufficiently close to a rigid one.
	// However using with a tight tolerance like tol<ON_ZERO_TOLERANCE 
	// Indicates that this is very close to being a rigid transformation.
	// This calculations is based on approximations and is only  
	// reliable if tolerance << 1.0. 
	int rval = 0;
	if (IsAffine())
	{
		// L = Linearized version of this. 
		// LTL = L^T * L
		ON_Xform L = (*this);
		L.Linearize();

		double dist = ApproxDist2Ortho(L);

		rval = (dist < tolerance);
    if (rval)
    {
      double det = L.Determinant();
      if (det < 0)
        rval = -1;
    }
	}
	return rval;
}


bool ON_Xform::IsAffine() const
{
  return (
    0.0 == m_xform[3][0] 
    && 0.0 == m_xform[3][1] 
    && 0.0 == m_xform[3][2] 
    && 1.0 == m_xform[3][3] 
    && IsValid());
}

void ON_Xform::Affineize()
{
	m_xform[3][0] = m_xform[3][1] = m_xform[3][2] = 0.0;
	m_xform[3][3] = 1.0;
}


bool ON_Xform::IsLinear() const
{
	return (IsAffine() 
		&& 0.0 == m_xform[0][3]
		&& 0.0 == m_xform[1][3]
		&& 0.0 == m_xform[2][3]);
}

void ON_Xform::Linearize()
{
	Affineize();
	m_xform[0][3] = m_xform[1][3] = m_xform[2][3] = 0.0;
	m_xform[3][3] = 1.0;
}

bool ON_Xform::IsRotation() const
{
	bool rc = false;
	if (IsLinear())
	{
		ON_Xform RTR = (*this);
		RTR.Transpose();
		RTR = RTR * (*this);
		rc = RTR.IsIdentity(ON_ZERO_TOLERANCE) && Determinant()>0;
	}
	return rc;
}

bool ON_Xform::GetQuaternion(ON_Quaternion& Q) const
{
  bool rc = IsRotation();
  if (rc)
  {
    double theta = 0;
    ON_3dVector Axis(m_xform[2][1] - m_xform[1][2], m_xform[0][2] - m_xform[2][0], m_xform[1][0] - m_xform[0][1]);
    double Alen = Axis.Length();
    double trace = m_xform[0][0] + m_xform[1][1] + m_xform[2][2];

    theta = atan2(Alen, trace - 1);   // 0<= theta <= Pi/2

    if(Alen>0.0 && trace> -.999)
      Axis = 1.0 / Alen * Axis;
    else
    {
      if (theta == 0.0)
        Axis = ON_3dVector::ZAxis;      // case where axis is unspecified   
      else
      {
        // Form off diagonal elements of the symmetric matrix  (R+R^t)/2
        double S12 = (m_xform[1][2] + m_xform[2][1]) / 2;
        double S13 = (m_xform[1][2] + m_xform[3][1]) / 2;
        // double S23 = (m_xform[2][3] + m_xform[3][2]) / 2;

        double c = (1 - trace) / 2.0;   // cos(theta) should be ~-1.0
        // magnitude of axis coefficients are computed as such:
        for (int i = 0; i < 3; i++)
          Axis[i] = sqrt((m_xform[i][i] - c) / (1 - c));
        // need to set the signs
        if (S12 < 0) Axis[1] *= -1;
        if (S13 < 0) Axis[2] *= -1;
      }
    }
    Q.SetRotation(theta, Axis);
  }
  return rc;
}

bool ON_Xform::Orthogonalize(double tol)
{
	bool rc = false;
	if (IsAffine())
	{
		ON_3dVector T;
		ON_Xform L;
		DecomposeAffine(T, L);
		ON_Xform LTL = L;
		LTL.Transpose();
		LTL = LTL * L;
		if (!LTL.IsIdentity(tol))
		{
			// Gram - Schmidt
			ON_3dVector V[3];
			V[0] = ON_3dVector(m_xform[0]);
			V[1] = ON_3dVector(m_xform[1]);
			V[2] = ON_3dVector(m_xform[2]);
			rc = true;
			for (int i = 0; rc && i < 3; i++)
			{
				for (int j = 0; j < i; j++)
					V[i] -= V[i] * V[j] * V[j];
				rc = V[i].Unitize();
			}
			if (rc)
			{
				*(reinterpret_cast<ON_3dVector*>(m_xform[0])) = V[0];
				*(reinterpret_cast<ON_3dVector*>(m_xform[1])) = V[1];
				*(reinterpret_cast<ON_3dVector*>(m_xform[2])) = V[2];
			}
		}
		else
			rc = true;
	}
	return rc;
}


bool ON_Xform::DecomposeAffine(ON_3dVector& T, ON_Xform& R,
	ON_Xform& Q, ON_3dVector& lambda) const
{
	bool rc = false;
	if (IsAffine())
	{
		ON_Xform L;
		DecomposeAffine(T, L);
		ON_Xform LT = L;
		LT.Transpose();
		ON_Xform LTL = LT * L;

		rc = LTL.DecomposeSymmetric(Q, lambda);
		if (rc)
		{
			rc = (lambda[0] > 0 && lambda[1] > 0 && lambda[2] > 0);
			if(rc)
			{
				lambda[0] = sqrt(lambda[0]);
				lambda[1] = sqrt(lambda[1]);
				lambda[2] = sqrt(lambda[2]);
				ON_Xform QT = Q;
				QT.Transpose();
				ON_Xform Diag = ON_Xform::DiagonalTransformation(1.0 / lambda[0], 1.0 / lambda[1], 1.0 / lambda[2]);
				R = Q * Diag * QT;
				R = L * R;

				if (R.Determinant() < 0)
				{
					R = ON_Xform(-1) * R;
					lambda = -1 * lambda;
				}
				R.Orthogonalize(ON_ZERO_TOLERANCE);  // tune it up - tol should be <= that in 
																							// Is_Rotation()
			}
		}
	}
	return rc;
}




bool ON_Xform::DecomposeAffine(ON_3dVector& T, ON_Xform& L) const
{
	bool rc = IsAffine();
	if (rc)
	{
		T = ON_3dVector(m_xform[0][3], m_xform[1][3], m_xform[2][3]);
		L = (*this);
		L.m_xform[0][3] = L.m_xform[1][3] = L.m_xform[2][3] = 0.0;
	}
	return rc;
}


// Suppose the transformation is given by f(x) = Lx + B. If L is invertible then
// f(x) = L ( x + L^(-1) B) so T = L^(-1) B.
bool ON_Xform::DecomposeAffine(ON_Xform& L, ON_3dVector& T) const
{
	bool rc = IsAffine();
	if (rc)
	{
		ON_Xform Linv = *this;
		rc = Linv.Invert();
		if (rc)
		{
			T = - ON_3dVector( Linv[0][3], Linv[1][3], Linv[2][3] );
			L = (*this);
			L[0][3] = L[1][3] = L[2][3] = 0.0;
		}
		/*
			TODO: A more thorough solution would be to take a tolerance and
			compute the best approximate T using psuodoinvese and comparing it
			using the tolerance.
		*/
	}
	return rc;
}

void ON_Xform::DecomposeTextureMapping(ON_3dVector& offset, ON_3dVector& repeat, ON_3dVector& rotation) const
{
  // All angles in radians.

  ON_Xform xform = *this;

  repeat.x = sqrt(xform[0][0] * xform[0][0] + xform[0][1] * xform[0][1] + xform[0][2] * xform[0][2]);
  repeat.y = sqrt(xform[1][0] * xform[1][0] + xform[1][1] * xform[1][1] + xform[1][2] * xform[1][2]);
  repeat.z = sqrt(xform[2][0] * xform[2][0] + xform[2][1] * xform[2][1] + xform[2][2] * xform[2][2]);

  const ON_Xform S = TextureMapping(ON_3dVector::ZeroVector, repeat, ON_3dVector::ZeroVector).Inverse();

  xform = S * xform;

  const double dSinBeta = -xform[2][0];

  double dCosBeta = sqrt(1.0 - dSinBeta * dSinBeta);
  if (dCosBeta < 0.0)
  {
    dCosBeta = -dCosBeta;
  }

  double dSinAlpha, dCosAlpha, dSinGamma, dCosGamma;

  if (dCosBeta < 1e-6)
  {
    dSinAlpha = -xform[1][2];
    dCosAlpha = xform[1][1];
    dSinGamma = 0.0;
    dCosGamma = 1.0;
  }
  else
  {
    dSinAlpha = xform[2][1] / dCosBeta;
    dCosAlpha = xform[2][2] / dCosBeta;
    dSinGamma = xform[1][0] / dCosBeta;
    dCosGamma = xform[0][0] / dCosBeta;
  }

  rotation.x = atan2(dSinAlpha, dCosAlpha);
  rotation.y = atan2(dSinBeta,  dCosBeta);
  rotation.z = atan2(dSinGamma, dCosGamma);

  const ON_Xform R = TextureMapping(ON_3dVector::ZeroVector, repeat, rotation).Inverse();

  const ON_Xform T = R * *this;

  offset.x = -T[0][3];
  offset.y = -T[1][3];
  offset.z = -T[2][3];
}

//static
const ON_Xform ON_Xform::TextureMapping(const ON_3dVector& offset, const ON_3dVector& repeat, const ON_3dVector& rotation)
{
  // All angles in radians.

  ON_Xform S = ON_Xform::DiagonalTransformation(repeat.x, repeat.y, repeat.z);

  ON_Xform R;
  R.Rotation(rotation.x, ON_3dVector::XAxis, ON_3dPoint::Origin);

  ON_3dVector vRotate = ON_3dVector::YAxis;
  vRotate.Transform(R.Inverse());

  ON_Xform Ry;
  Ry.Rotation(rotation.y, vRotate, ON_3dPoint::Origin);

  R = R * Ry;

  vRotate = ON_3dVector::ZAxis;
  vRotate.Transform(R.Inverse());

  ON_Xform Rz;
  Rz.Rotation(rotation.z, vRotate, ON_3dPoint::Origin);

  R = R * Rz;

  const ON_Xform T = ON_Xform::TranslationTransformation(-offset.x, -offset.y, -offset.z);

  return S * R * T;
}


bool ON_Xform::IsZero() const
{
  const double* v = &m_xform[0][0];
  for ( int i = 0; i < 15; i++ )
  {
    if ( !(*v++ == 0.0 ) )
      return false; // nonzero or nan
  }
  return (m_xform[3][3] == m_xform[3][3]);
}

bool ON_Xform::IsZero4x4() const
{
  return (0.0 == m_xform[3][3] && IsZero());
}
  

bool ON_Xform::IsZero4x4(double tol) const
{
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (false == fabs(m_xform[i][j]) <= tol) return false;
  return true;
}

bool ON_Xform::IsZeroTransformation() const
{
	return IsZeroTransformation(0.0);
}

bool ON_Xform::IsZeroTransformation(double tol) const
{
	bool rc = true;
	for(int i=0; rc && i<4; i++)
		for (int j = 0; rc && j < 4; j++)
		{
			if (i == 3 && j == 3)
				continue;
			rc = fabs(m_xform[i][j]) <= tol;
		}
  return (rc && 1.0 == m_xform[3][3] );
}


void ON_Xform::Transpose()
{
  double t;
  t = m_xform[0][1]; m_xform[0][1] = m_xform[1][0]; m_xform[1][0] = t;
  t = m_xform[0][2]; m_xform[0][2] = m_xform[2][0]; m_xform[2][0] = t;
  t = m_xform[0][3]; m_xform[0][3] = m_xform[3][0]; m_xform[3][0] = t;
  t = m_xform[1][2]; m_xform[1][2] = m_xform[2][1]; m_xform[2][1] = t;
  t = m_xform[1][3]; m_xform[1][3] = m_xform[3][1]; m_xform[3][1] = t;
  t = m_xform[2][3]; m_xform[2][3] = m_xform[3][2]; m_xform[3][2] = t;
}

int ON_Xform::Rank( double* pivot ) const
{
  double I[4][4], d = 0.0, p = 0.0;
  int r = Inv( &m_xform[0][0], I, &d, &p );
  if ( pivot )
    *pivot = p;
  return r;
}

double ON_Xform::Determinant( double* pivot ) const
{
  double I[4][4], d = 0.0, p = 0.0;
  //int rank = 
  Inv( &m_xform[0][0], I, &d, &p );
  if ( pivot )
    *pivot = p;
  if (d != 0.0 )
    d = 1.0/d;

  return d;
}

int ON_Xform::SignOfDeterminant(bool bFastTest) const
{
  if (bFastTest)
  {
    if (
      (0.0 == m_xform[3][0] && 0.0 == m_xform[3][1] && 0.0 == m_xform[3][2])
      ||
      (0.0 == m_xform[0][3] && 0.0 == m_xform[1][3] && 0.0 == m_xform[2][3])
      )
    {
      // vast majority of the 4x4 cases in practice.

      if (0.0 == m_xform[3][3])
      {
        return 0; // 100% accurate result.
      }

      // Use the simple 3x3 formula with the fewest flops.
      const double x
        = m_xform[0][0] * (m_xform[1][1] * m_xform[2][2] - m_xform[1][2] * m_xform[2][1])
        + m_xform[0][1] * (m_xform[1][2] * m_xform[2][0] - m_xform[1][0] * m_xform[2][2])
        + m_xform[0][2] * (m_xform[1][0] * m_xform[2][1] - m_xform[1][1] * m_xform[2][0]);

      if (0.0 == x)
      {
        // It is very likely we had a simple case and, mathematically, det = 0.
        // (not a 100% safe assumption, but good enough for bFastTest = true case).
        return 0;
      }

      if (fabs(x) > 1e-8)
      {
        // x is big enough that it's very likely the sign is mathematically correct.
        // (not a 100% safe assumption, but good enough for bFastTest = true case).
        const int s = ((x < 0.0) ? -1 : 1) * ((m_xform[3][3] < 0.0) ? -1 : 1);
        return s;
      }
    }
  }

  // do it a very slow and careful way
  double min_pivot = 0.0;
  const double det = this->Determinant(&min_pivot);
  if (fabs(min_pivot) > ON_ZERO_TOLERANCE && fabs(det) > ON_ZERO_TOLERANCE)
  {
    return (det < 0.0) ? -1 : 1;
  }

  return 0;
}

bool ON_Xform::Invert( double* pivot )
{
  double mrofx[4][4], d = 0.0, p = 0.0;
  int rank = Inv( &m_xform[0][0], mrofx, &d, &p );
  memcpy( m_xform, mrofx, sizeof(m_xform) );
  if ( pivot )
    *pivot = p;
  return (rank == 4) ? true : false;
}

ON_Xform ON_Xform::Inverse( double* pivot ) const
{
  ON_Xform inv;
  double d = 0.0, p = 0.0;
  //int rank = 
  Inv( &m_xform[0][0], inv.m_xform, &d, &p );
  if ( pivot )
    *pivot = p;
  return inv;
}

double ON_Xform::GetSurfaceNormalXform( ON_Xform& N_xform ) const
{
  // since were are transforming vectors, we don't need
  // the translation column or bottom row.
  memcpy(&N_xform.m_xform[0][0],&m_xform[0][0], 3*sizeof(N_xform.m_xform[0][0]) );
  N_xform.m_xform[0][3] = 0.0;
  memcpy(&N_xform.m_xform[1][0],&m_xform[1][0], 3*sizeof(N_xform.m_xform[0][0]) );
  N_xform.m_xform[1][3] = 0.0;
  memcpy(&N_xform.m_xform[2][0],&m_xform[2][0], 3*sizeof(N_xform.m_xform[0][0]) );
  N_xform.m_xform[2][3] = 0.0;
  N_xform.m_xform[3][0] = 0.0;
  N_xform.m_xform[3][1] = 0.0;
  N_xform.m_xform[3][2] = 0.0;
  N_xform.m_xform[3][3] = 1.0;

  double mrofx[4][4], d = 0.0, p = 0.0;
  double dtol = ON_SQRT_EPSILON*ON_SQRT_EPSILON*ON_SQRT_EPSILON;
  if ( 4 == Inv( &N_xform.m_xform[0][0], mrofx, &d, &p ) 
       && fabs(d) > dtol 
       && fabs(d)*dtol < 1.0
       && fabs(p) > ON_EPSILON*fabs(d)
     )
  {
    // Set N_xform = transpose of mrofx (only upper 3x3 matters)
    N_xform.m_xform[0][0] = mrofx[0][0];
    N_xform.m_xform[0][1] = mrofx[1][0]; 
    N_xform.m_xform[0][2] = mrofx[2][0];

    N_xform.m_xform[1][0] = mrofx[0][1];
    N_xform.m_xform[1][1] = mrofx[1][1];
    N_xform.m_xform[1][2] = mrofx[2][1];

    N_xform.m_xform[2][0] = mrofx[0][2];
    N_xform.m_xform[2][1] = mrofx[1][2];
    N_xform.m_xform[2][2] = mrofx[2][2];
  }
  else
  {
    d = 0.0;
  }
  return d;
}

double ON_Xform::GetSurfaceNormalXformKeepLengthAndOrientation(ON_Xform& N_xform) const
{
  N_xform = *this;
  N_xform.Linearize();
  double pivot = 0;
  double det = N_xform.Determinant(&pivot);

  double tol = ON_SQRT_EPSILON * ON_SQRT_EPSILON * ON_SQRT_EPSILON;
  if (fabs(det) <= tol || fabs(det) * tol >= 1.0 || fabs(pivot) <= ON_EPSILON * fabs(det))
    return 0.;

  ON_3dVector translation{ ON_3dVector::NanVector };
  double scale{ ON_DBL_QNAN };
  ON_Xform rotation{ ON_Xform::Nan };
  const int is_similarity = N_xform.DecomposeSimilarity(translation, scale, rotation, ON_ZERO_TOLERANCE);
  // If it's a uniform scale, handle it, otherwise need to get the inverse.
  if (is_similarity != 0)
  {
    N_xform = rotation;
    if (det < 0)
    {
      N_xform = ON_Xform(-1.) * N_xform;
    }
    return det;
  }

  if (!N_xform.Invert()) return 0.;
  N_xform.Linearize();
  N_xform.Transpose();
  if (abs(abs(det) - 1) > ON_SQRT_EPSILON)
  {
    N_xform = ON_Xform(pow(det, -1. / 3.)) * N_xform;
  }

  return det;
}

double ON_Xform::GetMappingXforms( ON_Xform& P_xform, ON_Xform& N_xform ) const
{
  double d = 0.0, p = 0.0;
  double dtol = ON_SQRT_EPSILON*ON_SQRT_EPSILON*ON_SQRT_EPSILON;
  if ( 4 == Inv( &m_xform[0][0], P_xform.m_xform, &d, &p ) 
       && fabs(d) > dtol 
       && fabs(d)*dtol < 1.0
       && fabs(p) > ON_EPSILON*fabs(d)
     )
  {
    // Set N_xform = transpose of this (only upper 3x3 matters)
    N_xform.m_xform[0][0] = m_xform[0][0];
    N_xform.m_xform[0][1] = m_xform[1][0]; 
    N_xform.m_xform[0][2] = m_xform[2][0];
    N_xform.m_xform[0][3] = 0.0;

    N_xform.m_xform[1][0] = m_xform[0][1];
    N_xform.m_xform[1][1] = m_xform[1][1];
    N_xform.m_xform[1][2] = m_xform[2][1];
    N_xform.m_xform[1][3] = 0.0;

    N_xform.m_xform[2][0] = m_xform[0][2];
    N_xform.m_xform[2][1] = m_xform[1][2];
    N_xform.m_xform[2][2] = m_xform[2][2];
    N_xform.m_xform[2][3] = 0.0;

    N_xform.m_xform[3][0] = 0.0;
    N_xform.m_xform[3][1] = 0.0;
    N_xform.m_xform[3][2] = 0.0;
    N_xform.m_xform[3][3] = 1.0;
  }
  else
  {
    P_xform = ON_Xform::IdentityTransformation;
    N_xform = ON_Xform::IdentityTransformation;
    d = 0.0;
  }
  return d;
}


void ON_Xform::Rotation( 
        double angle,
        ON_3dVector axis,  // 3d nonzero axis of rotation
        ON_3dPoint center  // 3d center of rotation
        )
{
  Rotation( sin(angle), cos(angle), axis, center );
}

void ON_Xform::Rotation(
  ON_3dVector start_dir,
  ON_3dVector end_dir,
  ON_3dPoint rotation_center
  )
{
  if ( fabs(start_dir.Length()-1.0) > ON_SQRT_EPSILON )
    start_dir.Unitize();
  if ( fabs(end_dir.Length()-1.0) > ON_SQRT_EPSILON )
    end_dir.Unitize();
  double cos_angle = start_dir*end_dir;
  ON_3dVector axis = ON_CrossProduct(start_dir,end_dir);
  double sin_angle = axis.Length();
  if ( 0.0 == sin_angle || !axis.Unitize() )
  {
    axis.PerpendicularTo(start_dir);
    axis.Unitize();
    sin_angle = 0.0;
    cos_angle = (cos_angle < 0.0) ? -1.0 : 1.0;
  }
  Rotation(sin_angle,cos_angle,axis,rotation_center);
}

void ON_Xform::Rotation(  
        double sin_angle,
        double cos_angle,
        ON_3dVector axis,
        ON_3dPoint center
        )
{
  *this = ON_Xform::IdentityTransformation;

  for(;;)
  {
    // 29 June 2005 Dale Lear
    //     Kill noise in input
    if ( fabs(sin_angle) >= 1.0-ON_SQRT_EPSILON && fabs(cos_angle) <= ON_SQRT_EPSILON )
    {
      cos_angle = 0.0;
      sin_angle = (sin_angle < 0.0) ? -1.0 : 1.0; 
      break;
    }
    
    if ( fabs(cos_angle) >= 1.0-ON_SQRT_EPSILON && fabs(sin_angle) <= ON_SQRT_EPSILON )
    {
      cos_angle = (cos_angle < 0.0) ? -1.0 : 1.0; 
      sin_angle = 0.0;
      break;
    }
    
    if ( fabs(cos_angle*cos_angle + sin_angle*sin_angle - 1.0) > ON_SQRT_EPSILON )
    {
      ON_2dVector cs(cos_angle,sin_angle);
      if ( cs.Unitize() )
      {
        cos_angle = cs.x;
        sin_angle = cs.y;
        // no break here
      }
      else
      {
        ON_ERROR("sin_angle and cos_angle are both zero.");
        cos_angle = 1.0;
        sin_angle = 0.0;
        break;
      }
    }

    if ( fabs(cos_angle) > 1.0-ON_EPSILON || fabs(sin_angle) < ON_EPSILON )
    {
      cos_angle = (cos_angle < 0.0) ? -1.0 : 1.0; 
      sin_angle = 0.0;
      break;
    }

    if ( fabs(sin_angle) > 1.0-ON_EPSILON || fabs(cos_angle) < ON_EPSILON )
    {
      cos_angle = 0.0;
      sin_angle = (sin_angle < 0.0) ? -1.0 : 1.0; 
      break;
    }

    break;
  }

  if (sin_angle != 0.0 || cos_angle != 1.0) 
  {
    const double one_minus_cos_angle = 1.0 - cos_angle;
    ON_3dVector a = axis;
    if ( fabs(a.LengthSquared() - 1.0) >  ON_EPSILON )
      a.Unitize();

    m_xform[0][0] = a.x*a.x*one_minus_cos_angle + cos_angle;
    m_xform[0][1] = a.x*a.y*one_minus_cos_angle - a.z*sin_angle;
    m_xform[0][2] = a.x*a.z*one_minus_cos_angle + a.y*sin_angle;

    m_xform[1][0] = a.y*a.x*one_minus_cos_angle + a.z*sin_angle;
    m_xform[1][1] = a.y*a.y*one_minus_cos_angle + cos_angle;
    m_xform[1][2] = a.y*a.z*one_minus_cos_angle - a.x*sin_angle;

    m_xform[2][0] = a.z*a.x*one_minus_cos_angle - a.y*sin_angle;
    m_xform[2][1] = a.z*a.y*one_minus_cos_angle + a.x*sin_angle;
    m_xform[2][2] = a.z*a.z*one_minus_cos_angle + cos_angle;

    if ( center.x != 0.0 || center.y != 0.0 || center.z != 0.0 ) {
      m_xform[0][3] = -((m_xform[0][0]-1.0)*center.x + m_xform[0][1]*center.y + m_xform[0][2]*center.z);
      m_xform[1][3] = -(m_xform[1][0]*center.x + (m_xform[1][1]-1.0)*center.y + m_xform[1][2]*center.z);
      m_xform[2][3] = -(m_xform[2][0]*center.x + m_xform[2][1]*center.y + (m_xform[2][2]-1.0)*center.z);
    }

    m_xform[3][0] = m_xform[3][1] = m_xform[3][2] = 0.0;
    m_xform[3][3] = 1.0;
  }
}


void ON_Xform::Rotation(
  const ON_3dVector&  X0, // initial frame X (X,Y,Z = right handed orthonormal frame)
  const ON_3dVector&  Y0, // initial frame Y
  const ON_3dVector&  Z0, // initial frame Z
  const ON_3dVector&  X1, // final frame X (X,Y,Z = another right handed orthonormal frame)
  const ON_3dVector&  Y1, // final frame Y
  const ON_3dVector&  Z1  // final frame Z
  )
{
  // transformation maps X0 to X1, Y0 to Y1, Z0 to Z1

  // F0 changes x0,y0,z0 to world X,Y,Z
  ON_Xform F0;
  F0[0][0] = X0.x; F0[0][1] = X0.y; F0[0][2] = X0.z;
  F0[1][0] = Y0.x; F0[1][1] = Y0.y; F0[1][2] = Y0.z;
  F0[2][0] = Z0.x; F0[2][1] = Z0.y; F0[2][2] = Z0.z;
  F0[3][3] = 1.0;

  // F1 changes world X,Y,Z to x1,y1,z1
  ON_Xform F1;
  F1[0][0] = X1.x; F1[0][1] = Y1.x; F1[0][2] = Z1.x;
  F1[1][0] = X1.y; F1[1][1] = Y1.y; F1[1][2] = Z1.y;
  F1[2][0] = X1.z; F1[2][1] = Y1.z; F1[2][2] = Z1.z;
  F1[3][3] = 1.0;

  *this = F1*F0;
}

void ON_Xform::Rotation( 
  const ON_Plane& plane0,
  const ON_Plane& plane1
  )
{
  Rotation( 
    plane0.origin, plane0.xaxis, plane0.yaxis, plane0.zaxis,
    plane1.origin, plane1.xaxis, plane1.yaxis, plane1.zaxis
    );
}


void ON_Xform::Rotation(   // (not strictly a rotation)
                            // transformation maps P0 to P1, P0+X0 to P1+X1, ...
  const ON_3dPoint&   P0,  // initial frame center
  const ON_3dVector&  X0, // initial frame X
  const ON_3dVector&  Y0, // initial frame Y
  const ON_3dVector&  Z0, // initial frame Z
  const ON_3dPoint&   P1,  // final frame center
  const ON_3dVector&  X1, // final frame X
  const ON_3dVector&  Y1, // final frame Y
  const ON_3dVector&  Z1  // final frame Z
  )
{
  // transformation maps P0 to P1, P0+X0 to P1+X1, ...

  // T0 translates point P0 to (0,0,0)
  const ON_Xform T0(ON_Xform::TranslationTransformation(ON_3dPoint::Origin - P0));

  ON_Xform R;
  R.Rotation(X0,Y0,Z0,X1,Y1,Z1);

  // T1 translates (0,0,0) to point P1
  ON_Xform T1(ON_Xform::TranslationTransformation(P1 - ON_3dPoint::Origin));

  *this = T1*R*T0;
}

void  ON_Xform::RotationZYX(double yaw, double pitch, double roll)
{
	ON_Xform Rx;
	Rx.Rotation(roll, ON_3dVector::XAxis, ON_3dPoint::Origin);
	ON_Xform Ry;
	Ry.Rotation( pitch, ON_3dVector::YAxis, ON_3dPoint::Origin);
	ON_Xform Rz;
	Rz.Rotation(yaw, ON_3dVector::ZAxis, ON_3dPoint::Origin);
	(*this) = Rz * Ry * Rx;
}

void  ON_Xform::RotationZYZ(double alpha, double beta, double gamma)
{
	ON_Xform Rz;
	Rz.Rotation(gamma, ON_3dVector::ZAxis, ON_3dPoint::Origin);
	ON_Xform Ry;
	Ry.Rotation(beta, ON_3dVector::YAxis, ON_3dPoint::Origin);
	ON_Xform Rzz;
	Rzz.Rotation(alpha, ON_3dVector::ZAxis, ON_3dPoint::Origin);
	(*this) = Rzz * Ry * Rz;
}

bool ON_Xform::GetYawPitchRoll(double& yaw, double& pitch, double& roll)const
{
	bool rc = IsRotation();
	if (rc)
	{
		if(
       (m_xform[1][0] == 0.0 &&  m_xform[0][0] == 0.0)
       ||
			  (m_xform[2][1] == 0.0 &&  m_xform[2][2] == 0.0) ||
			  (fabs(m_xform[2][0])>=1.0) )
		{
			pitch = (m_xform[2][0] > 0) ? -ON_PI / 2.0 : ON_PI / 2.0;
			yaw = atan2(-m_xform[0][1], m_xform[1][1] );
			roll = 0.0;
		}
		else
		{
			yaw = atan2(m_xform[1][0], m_xform[0][0]);
			roll = atan2(m_xform[2][1], m_xform[2][2]);
			pitch = asin(-m_xform[2][0]);
		}
	}
	return rc;
}

bool ON_Xform::GetEulerZYZ(double& alpha, double& beta, double& gamma)const
{
	bool rc = IsRotation();
	if(rc)
	{
		if ((fabs(m_xform[2][2]) >= 1.0) ||
			(m_xform[1][2] == 0.0 &&  m_xform[0][2] == 0.0) ||
			(m_xform[2][1] == 0.0 &&  m_xform[2][0] == 0.0))
		{
			beta = (m_xform[2][2] > 0) ? 0.0 : ON_PI;
			alpha = atan2(-m_xform[0][1], m_xform[1][1]);
			gamma = 0.0;
		}
		else
		{
			beta = acos(m_xform[2][2]);
			alpha = atan2(m_xform[1][2], m_xform[0][2]);
			gamma = atan2(m_xform[2][1], -m_xform[2][0]);
		}
	}
	return rc;
}

bool ON_Xform::GetKMLOrientationAnglesRadians(double& heading_radians, double& tilt_radians, double& roll_radians ) const
{
  // NOTE: In KML, positive rotations are CLOCKWISE about the specified axis.
  // This is opposite the conventional "right hand rule."
  // https://developers.google.com/kml/documentation/kmlreference#orientation
  heading_radians = ON_DBL_QNAN;
  tilt_radians = ON_DBL_QNAN;
  roll_radians = ON_DBL_QNAN;

  bool rc = false;
  for (;;)
  {
    if (false == IsRotation())
      break;

    // sin(1 degree)^3 = 5e-6.
    const double zero_tol = ON_ZERO_TOLERANCE;
    ON_Xform clean(*this);
    for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j)
    {
      double x = (i < 3 && j < 3) ? m_xform[i][j] : ((3==i&&3==j) ? 1.0 : 0.0);
      if (fabs(x) <= zero_tol)
        x = 0.0;
      else if (fabs(x-1.0) <= zero_tol)
        x = 1.0;
      else if (fabs(x+1.0) <= zero_tol)
        x = -1.0;
      else 
        continue;
      clean.m_xform[i][j] = x;
    }
    if (false == clean.IsRotation())
      clean = *this;


    // Set: h = -heading angle, t = -tilt angle, r = -roll angle. 
    // (negatives because KML angles are opposite the right hand rule direction, and trig works the other way.)    // 
    // The KML specification says 0 <= heading <= 2pi, 0 <= tilt <= pi, 0 <= roll <= pi.
    // So, if this transformation is really a KML rotation, then we are looking for h,t,r 
    // in the ranges -2pi <= h <= 0, -pi <= t <= 0, and -pi <= r <= 0.
    // 
    // If you calculate the 3x3 KML orientation matrix M by hand,
    // then you get
    // M[1][0] = -sin(h)*cos(t)
    // M[1][1] = +cos(h)*cos(t)
    // M[2][0] = -cos(t)*sin(r)
    // M[2][1] = +sin(t)
    // M[2][2] = +cos(t)*cos(r)
    // So, a bit of trigonometry and you have h, t, and r.

    // NOTE WELL: When cos(t) is very near zero, but not equal to zero,
    // this calculation is unstable. In practice t is typically
    // a integer number of degrees between 0 and 180, and this
    // instability rarely matters.

    // tol = one half an arc second.
    // Should be way more precise than KML requires.
    const double zero_angle_tol = (0.5 / (60.0 * 60.0)) * ON_DEGREES_TO_RADIANS;
    double h = ON_DBL_QNAN;
    double r = ON_DBL_QNAN;
    double t = ON_DBL_QNAN;
    if (
      (0.0 == clean.m_xform[0][1] && 0.0 == clean.m_xform[1][1])
      ||
      (0.0 == clean.m_xform[2][0] && 0.0 == clean.m_xform[2][2]) 
      ||
      (1.0 == fabs(clean.m_xform[2][1]))
      )
    {
      // In this case, cos(tilt angle) = 0, clean.m_xform[2][1] = sin(tilt angle) = +1 or -1.
      // In this case it is impossible to distinguish between the initial rotation around
      // the y axis and the final rotation around the z axis
      // (tilt is the middle rotation around the x axis).
      // I'm choosing to set roll = 0 in this case.
      h = atan2(clean.m_xform[1][0], clean.m_xform[0][0]); // = atan2(clean.m_xform[0][1], -clean.m_xform[1][2])
      if (fabs(h) <= zero_angle_tol)
        h = 0.0;
      r = 0.0;
      t = clean.m_xform[2][1] < 0.0 ? -ON_HALFPI : ON_HALFPI; // t = asin(clean.m_xform[2][1]);
    }
    else
    {
      // KML wants -pi <= r <= 0, so sin(r) <= 0
      // clean.m_xform[2][0] = -cos(t)*sin(r)
      const double sign_cos_t = (clean.m_xform[2][0] < 0.0) ? -1.0 : 1.0;

      h = atan2(-sign_cos_t * clean.m_xform[0][1], sign_cos_t * clean.m_xform[1][1]);
      if (fabs(h) <= zero_angle_tol)
        h = 0.0;
      r = atan2(-sign_cos_t * clean.m_xform[2][0], sign_cos_t * clean.m_xform[2][2]);

      const double cos_h = cos(h);
      const double sin_h = sin(h);
      double cos_t
        = (fabs(sin_h) >= fabs(cos_h))
        ? (-clean.m_xform[0][1] / sin_h)
        : (clean.m_xform[1][1] / cos_h)
        ; 
      t = asin(clean.m_xform[2][1]);
      if (cos_t < 0.0)
      {
        // adjust the branch of t accordingly
        // cos_t could have a fair bit of noise in it
        // but the sign should generally be correct.
        if (0.0 == t)
        {
          // KML specification has -pi <= t <= 0
          if (cos_t < -0.99)
            t = -ON_PI;
        }
        else if (t > -ON_HALFPI && t < 0.0)
          t = -ON_PI - t;
      }
    }

    if (h == h && r == r && t == t)
    {
      // NOTE: In KML, positive rotations are CLOCKWISE about the specified axis.
      // This is opposite the conventional "right hand rule."
      // https://developers.google.com/kml/documentation/kmlreference#orientation
      heading_radians = -h;
      if (heading_radians < 0.0)
        heading_radians += ON_2PI; // KML wants headings >= 0.
      tilt_radians = -t;
      roll_radians = -r;

      // Specifying a 3D rotation as a sequence of rotations about fixed axes
      // requires restricting rotations to intervals in order to get a one-to-one
      // correspondence between the 3 angles and the rotation. KML specifies
      // 0 <= heading < 360
      // 0 <= tilt <= 180
      // 0 <= roll <= 180
      //  TODO - If the angles we have are not in the specified intervals, 
      //  adjust them to produce the same rotation and be in the specified intervals.
      rc = true;
    }

    break;
  }
  return rc;
}

static double Internal_RadiansToPrettyKMLDegrees(double r, double min_degrees)
{
  double d = r * ON_RADIANS_TO_DEGREES;
  double f = floor(d);
  if ( d-f > 0.5)
    f += 1.0;
  const double one_half_second_in_decimal_degrees = 0.5 / (60.0 * 60.0);
  if ( fabs(d - f) < one_half_second_in_decimal_degrees) // fabs(d-f)
    d = f;
  if (d < min_degrees)
    d += 360.0;
  if (fabs(d) < one_half_second_in_decimal_degrees)
    d = 0.0; // clean up -0.0
  return d;
}

bool ON_Xform::GetKMLOrientationAnglesDegrees(double& heading_degrees, double& tilt_degrees, double& roll_degrees) const
{
  double heading_radians = ON_DBL_QNAN;
  double tilt_radians = ON_DBL_QNAN;
  double roll_radians = ON_DBL_QNAN;
  const bool rc = ON_Xform::GetKMLOrientationAnglesRadians(heading_radians, tilt_radians, roll_radians);
  heading_degrees = Internal_RadiansToPrettyKMLDegrees(heading_radians, 0.0);
  tilt_degrees = Internal_RadiansToPrettyKMLDegrees(tilt_radians, -180.0);
  roll_degrees = Internal_RadiansToPrettyKMLDegrees(roll_radians, -180.0);
  return rc;
}

const ON_Xform ON_Xform::RotationTransformationFromKMLAnglesRadians(
  double heading_radians,
  double tilt_radians,
  double roll_radians
)
{
  // NOTE: In KML, positive rotations are CLOCKWISE looking down the specified axis towards the origin.
  // This is opposite the conventional "right hand rule."
  // https://developers.google.com/kml/documentation/kmlreference#orientation
  ON_Xform H, R, T;
  // Standard trigonometry functions (cosine, sine, ...) follow the right hand rule
  // convention, so the input angles must be negated.
  H.Rotation(-heading_radians, ON_3dVector::ZAxis, ON_3dPoint::Origin); // KML Earth z-axis = up
  T.Rotation(-tilt_radians, ON_3dVector::XAxis, ON_3dPoint::Origin); // KML Earth x-axis = east
  R.Rotation(-roll_radians, ON_3dVector::YAxis, ON_3dPoint::Origin); // KML Earth y-axis = north
  // KML specifies the rotation order as first R, second T, third H.
  // Since opennurbs ON_Xform acts on the left of points and vectors,
  // H*T*R is the correct order.
  // Example transformed_point = H*T*R*point (R is first, T is second, H is third).
  ON_Xform kml_orientation = H * T * R;

  // clean up -0, .99999999999999999, and other similar results that 
  // commonly occur and commonly disturb novices.
  for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j)
  {
    double x = kml_orientation.m_xform[i][j];
    if (fabs(x) <= ON_ZERO_TOLERANCE)
      x = 0.0;
    else if (fabs(x - 1.0) <= ON_ZERO_TOLERANCE)
      x = 1.0;
    else if (fabs(x + 1.0) <= ON_ZERO_TOLERANCE)
      x = -1.0;
    else
      continue;
    kml_orientation.m_xform[i][j] = x;
  }
  return kml_orientation;
}

const ON_Xform ON_Xform::RotationTransformationFromKMLAnglesDegrees(
  double heading_degrees,
  double tilt_degrees,
  double roll_degrees
  )
{
  return ON_Xform::RotationTransformationFromKMLAnglesRadians(
    heading_degrees * ON_DEGREES_TO_RADIANS,
    tilt_degrees * ON_DEGREES_TO_RADIANS,
    roll_degrees * ON_DEGREES_TO_RADIANS
    );
}

void ON_Xform::Mirror(
  ON_3dPoint point_on_mirror_plane,
  ON_3dVector normal_to_mirror_plane
  )
{
  ON_3dPoint P = point_on_mirror_plane;
  ON_3dVector N = normal_to_mirror_plane;
  N.Unitize();
  ON_3dVector V = (2.0*(N.x*P.x + N.y*P.y + N.z*P.z))*N;
  m_xform[0][0] = 1 - 2.0*N.x*N.x;
  m_xform[0][1] = -2.0*N.x*N.y;
  m_xform[0][2] = -2.0*N.x*N.z;
  m_xform[0][3] = V.x;

  m_xform[1][0] = -2.0*N.y*N.x;
  m_xform[1][1] = 1.0 -2.0*N.y*N.y;
  m_xform[1][2] = -2.0*N.y*N.z;
  m_xform[1][3] = V.y;

  m_xform[2][0] = -2.0*N.z*N.x;
  m_xform[2][1] = -2.0*N.z*N.y;
  m_xform[2][2] = 1.0 -2.0*N.z*N.z;
  m_xform[2][3] = V.z;

  m_xform[3][0] = 0.0;
  m_xform[3][1] = 0.0;
  m_xform[3][2] = 0.0;
  m_xform[3][3] = 1.0;
}

const ON_Xform ON_Xform::MirrorTransformation(
  ON_PlaneEquation mirror_plane
)
{
  const ON_PlaneEquation e = mirror_plane.UnitizedPlaneEquation();
  const ON_3dVector N(e.x, e.y, e.z);
  ON_3dVector V = (-2.0*e.d)*N;
  ON_Xform mirror;
  mirror.m_xform[0][0] = 1 - 2.0*N.x*N.x;
  mirror.m_xform[0][1] = -2.0*N.x*N.y;
  mirror.m_xform[0][2] = -2.0*N.x*N.z;
  mirror.m_xform[0][3] = V.x;

  mirror.m_xform[1][0] = -2.0*N.y*N.x;
  mirror.m_xform[1][1] = 1.0 - 2.0*N.y*N.y;
  mirror.m_xform[1][2] = -2.0*N.y*N.z;
  mirror.m_xform[1][3] = V.y;

  mirror.m_xform[2][0] = -2.0*N.z*N.x;
  mirror.m_xform[2][1] = -2.0*N.z*N.y;
  mirror.m_xform[2][2] = 1.0 - 2.0*N.z*N.z;
  mirror.m_xform[2][3] = V.z;

  mirror.m_xform[3][0] = 0.0;
  mirror.m_xform[3][1] = 0.0;
  mirror.m_xform[3][2] = 0.0;
  mirror.m_xform[3][3] = 1.0;

  return mirror;
}




bool ON_Xform::ChangeBasis( 
  // General: If you have points defined with respect to planes, this
  //          computes the transformation to change coordinates from
  //          one plane to another.  The predefined world plane
  //          ON_world_plane can be used as an argument.
  // Details: If P = plane0.Evaluate( a0,b0,c0 ) and
  //          {a1,b1,c1} = ChangeBasis(plane0,plane1)*ON_3dPoint(a0,b0,c0),
  //          then P = plane1.Evaluate( a1, b1, c1 )
  //          
  const ON_Plane& plane0, // initial plane
  const ON_Plane& plane1  // final plane
  )
{
  return ChangeBasis( 
    plane0.origin, plane0.xaxis, plane0.yaxis, plane0.zaxis,
    plane1.origin, plane1.xaxis, plane1.yaxis, plane1.zaxis
    );
}


bool ON_Xform::ChangeBasis(
  const ON_3dVector&  X0, // initial frame X (X,Y,Z = arbitrary basis)
  const ON_3dVector&  Y0, // initial frame Y
  const ON_3dVector&  Z0, // initial frame Z
  const ON_3dVector&  X1, // final frame X (X,Y,Z = arbitrary basis)
  const ON_3dVector&  Y1, // final frame Y
  const ON_3dVector&  Z1  // final frame Z
  )
{
  // Q = a0*X0 + b0*Y0 + c0*Z0 = a1*X1 + b1*Y1 + c1*Z1
  // then this transform will map the point (a0,b0,c0) to (a1,b1,c1)
  *this = ON_Xform::ZeroTransformation;

  double a,b,c,d;
  a = X1*Y1;
  b = X1*Z1;
  c = Y1*Z1;
  double R[3][6] = {{X1*X1,      a,      b,       X1*X0, X1*Y0, X1*Z0},
                    {    a,  Y1*Y1,      c,       Y1*X0, Y1*Y0, Y1*Z0},
                    {    b,      c,  Z1*Z1,       Z1*X0, Z1*Y0, Z1*Z0}};
  //double R[3][6] = {{X1*X1,      a,      b,       X0*X1, X0*Y1, X0*Z1},
  //                  {    a,  Y1*Y1,      c,       Y0*X1, Y0*Y1, Y0*Z1},
  //                  {    b,      c,  Z1*Z1,       Z0*X1, Z0*Y1, Z0*Z1}};

  // row reduce R
  int i0 = (R[0][0] >= R[1][1]) ? 0 : 1;
  if ( R[2][2] > R[i0][i0] )
    i0 = 2;
  int i1 = (i0+1)%3;
  int i2 = (i1+1)%3;
  if ( R[i0][i0] == 0.0 )
    return false;
  d = 1.0/R[i0][i0];
  R[i0][0] *= d;
  R[i0][1] *= d;
  R[i0][2] *= d;
  R[i0][3] *= d;
  R[i0][4] *= d;
  R[i0][5] *= d;
  R[i0][i0] = 1.0;
  if ( R[i1][i0] != 0.0 ) {
    d = -R[i1][i0];
    R[i1][0] += d*R[i0][0];
    R[i1][1] += d*R[i0][1];
    R[i1][2] += d*R[i0][2];
    R[i1][3] += d*R[i0][3];
    R[i1][4] += d*R[i0][4];
    R[i1][5] += d*R[i0][5];
    R[i1][i0] = 0.0;
  }
  if ( R[i2][i0] != 0.0 ) {
    d = -R[i2][i0];
    R[i2][0] += d*R[i0][0];
    R[i2][1] += d*R[i0][1];
    R[i2][2] += d*R[i0][2];
    R[i2][3] += d*R[i0][3];
    R[i2][4] += d*R[i0][4];
    R[i2][5] += d*R[i0][5];
    R[i2][i0] = 0.0;
  }

  if ( fabs(R[i1][i1]) < fabs(R[i2][i2]) ) {
    int i = i1; i1 = i2; i2 = i;
  }
  if ( R[i1][i1] == 0.0 )
    return false;
  d = 1.0/R[i1][i1];
  R[i1][0] *= d;
  R[i1][1] *= d;
  R[i1][2] *= d;
  R[i1][3] *= d;
  R[i1][4] *= d;
  R[i1][5] *= d;
  R[i1][i1] = 1.0;
  if ( R[i0][i1] != 0.0 ) {
    d = -R[i0][i1];
    R[i0][0] += d*R[i1][0];
    R[i0][1] += d*R[i1][1];
    R[i0][2] += d*R[i1][2];
    R[i0][3] += d*R[i1][3];
    R[i0][4] += d*R[i1][4];
    R[i0][5] += d*R[i1][5];
    R[i0][i1] = 0.0;
  }
  if ( R[i2][i1] != 0.0 ) {
    d = -R[i2][i1];
    R[i2][0] += d*R[i1][0];
    R[i2][1] += d*R[i1][1];
    R[i2][2] += d*R[i1][2];
    R[i2][3] += d*R[i1][3];
    R[i2][4] += d*R[i1][4];
    R[i2][5] += d*R[i1][5];
    R[i2][i1] = 0.0;
  }

  if ( R[i2][i2] == 0.0 )
    return false;
  d = 1.0/R[i2][i2];
  R[i2][0] *= d;
  R[i2][1] *= d;
  R[i2][2] *= d;
  R[i2][3] *= d;
  R[i2][4] *= d;
  R[i2][5] *= d;
  R[i2][i2] = 1.0;
  if ( R[i0][i2] != 0.0 ) {
    d = -R[i0][i2];
    R[i0][0] += d*R[i2][0];
    R[i0][1] += d*R[i2][1];
    R[i0][2] += d*R[i2][2];
    R[i0][3] += d*R[i2][3];
    R[i0][4] += d*R[i2][4];
    R[i0][5] += d*R[i2][5];
    R[i0][i2] = 0.0;
  }
  if ( R[i1][i2] != 0.0 ) {
    d = -R[i1][i2];
    R[i1][0] += d*R[i2][0];
    R[i1][1] += d*R[i2][1];
    R[i1][2] += d*R[i2][2];
    R[i1][3] += d*R[i2][3];
    R[i1][4] += d*R[i2][4];
    R[i1][5] += d*R[i2][5];
    R[i1][i2] = 0.0;
  }

  m_xform[0][0] = R[0][3];
  m_xform[0][1] = R[0][4];
  m_xform[0][2] = R[0][5];

  m_xform[1][0] = R[1][3];
  m_xform[1][1] = R[1][4];
  m_xform[1][2] = R[1][5];

  m_xform[2][0] = R[2][3];
  m_xform[2][1] = R[2][4];
  m_xform[2][2] = R[2][5];

  return true;
}

bool ON_Xform::ChangeBasis(
  const ON_3dPoint&   P0,  // initial frame center
  const ON_3dVector&  X0, // initial frame X (X,Y,Z = arbitrary basis)
  const ON_3dVector&  Y0, // initial frame Y
  const ON_3dVector&  Z0, // initial frame Z
  const ON_3dPoint&   P1,  // final frame center
  const ON_3dVector&  X1, // final frame X (X,Y,Z = arbitrary basis)
  const ON_3dVector&  Y1, // final frame Y
  const ON_3dVector&  Z1  // final frame Z
  )
{
  bool rc = false;
  // Q = P0 + a0*X0 + b0*Y0 + c0*Z0 = P1 + a1*X1 + b1*Y1 + c1*Z1
  // then this transform will map the point (a0,b0,c0) to (a1,b1,c1)

  ON_Xform F0(P0,X0,Y0,Z0);		// Frame 0

  // T1 translates by -P1
  ON_Xform T1(ON_Xform::TranslationTransformation(ON_3dPoint::Origin - P1));
	
  ON_Xform CB;
  rc = CB.ChangeBasis(ON_3dVector::XAxis, ON_3dVector::YAxis, ON_3dVector::ZAxis,X1,Y1,Z1);

  *this = CB*T1*F0;
  return rc;
}

void ON_Xform::WorldToCamera( 
         const ON_3dPoint& cameraLocation,
         const ON_3dVector& cameraX,
         const ON_3dVector& cameraY,
         const ON_3dVector& cameraZ
         )
{
  // see comments in tl2_xform.h for details.
  /* compute world to camera coordinate xform */
  m_xform[0][0] = cameraX.x; m_xform[0][1] = cameraX.y; m_xform[0][2] = cameraX.z;
  m_xform[0][3] = -(cameraX.x*cameraLocation.x + cameraX.y*cameraLocation.y + cameraX.z*cameraLocation.z);
  m_xform[1][0] = cameraY.x; m_xform[1][1] = cameraY.y; m_xform[1][2] = cameraY.z;
  m_xform[1][3] = -(cameraY.x*cameraLocation.x + cameraY.y*cameraLocation.y + cameraY.z*cameraLocation.z);
  m_xform[2][0] = cameraZ.x; m_xform[2][1] = cameraZ.y; m_xform[2][2] = cameraZ.z;
  m_xform[2][3] = -(cameraZ.x*cameraLocation.x + cameraZ.y*cameraLocation.y + cameraZ.z*cameraLocation.z);
  m_xform[3][0] = m_xform[3][1] = m_xform[3][2] = 0.0; m_xform[3][3] = 1.0;
}
  
void ON_Xform::CameraToWorld(
         const ON_3dPoint& cameraLocation,
         const ON_3dVector& cameraX,
         const ON_3dVector& cameraY,
         const ON_3dVector& cameraZ
         )
{
  // see comments in tl2_xform.h for details.
  /* compute camera to world coordinate m_xform */
  m_xform[0][0] = cameraX.x; m_xform[0][1] = cameraY.x; m_xform[0][2] = cameraZ.x; 
  m_xform[0][3] = cameraLocation.x;
  m_xform[1][0] = cameraX.y; m_xform[1][1] = cameraY.y; m_xform[1][2] = cameraZ.y; 
  m_xform[1][3] = cameraLocation.y;
  m_xform[2][0] = cameraX.z; m_xform[2][1] = cameraY.z; m_xform[2][2] = cameraZ.z; 
  m_xform[2][3] = cameraLocation.z;
  m_xform[3][0] = m_xform[3][1] = m_xform[3][2] = 0.0; m_xform[3][3] = 1.0;
}

bool ON_Xform::CameraToClip(
      bool bPerspective,
      double left,      double right,
      double bottom,    double top,
      double near_dist, double far_dist
      )
{
  double dd;

  if ( left == right || bottom == top || near_dist == far_dist )
    return false;

  if ( !bPerspective ) {
    // parallel projection
    //d = 1.0/(left-right);
    //m_xform[0][0] = -2.0*d; m_xform[0][3] = (left+right)*d; m_xform[0][1] = m_xform[0][2] = 0.0;
    //d = 1.0/(bottom-top);
    //m_xform[1][1] = -2.0*d; m_xform[1][3] = (bottom+top)*d; m_xform[1][0] = m_xform[1][2] = 0.0;
    //d = 1.0/(far_dist-near_dist);
    //m_xform[2][2] = 2.0*d;  m_xform[2][3] = (far_dist+near_dist)*d;   m_xform[2][0] = m_xform[2][1] = 0.0;
    //m_xform[3][0] = m_xform[3][1] = m_xform[3][2] = 0.0; m_xform[3][3] = 1.0;

    dd = (left-right);
    m_xform[0][0] = -2.0/dd; m_xform[0][3] = (left+right)/dd; m_xform[0][1] = m_xform[0][2] = 0.0;
    dd = (bottom-top);
    m_xform[1][1] = -2.0/dd; m_xform[1][3] = (bottom+top)/dd; m_xform[1][0] = m_xform[1][2] = 0.0;
    dd = (far_dist-near_dist);
    m_xform[2][2] = 2.0/dd;  m_xform[2][3] = (far_dist+near_dist)/dd;   m_xform[2][0] = m_xform[2][1] = 0.0;
    m_xform[3][0] = m_xform[3][1] = m_xform[3][2] = 0.0; m_xform[3][3] = 1.0;
  }
  else 
  {
    // OpenNURBS uses a "right handed" camera coordinate system.
    // The camera X axis points horizontally left to right.
    // The camera Y axis points vertically bottom to top.
    // The camera Y axis points vertically bottom to top.
    // The camera Z axis points from back to front.
    //
    // If n = frustum near distance, f = frustum far distance
    // and 0 < n < f, then the perspective projection matrix is:
    //
    //  2n/(r-l)     0        (r+l)/(r-l)     0
    //    0        2n/(t-b)   (t+b)/(t-b)     0
    //    0          0        (f+n)/(f-n)  2fn/(f-n)
    //    0          0            -1          0
    //
    // Note that the "near frustum plane" is camera Z = -n and
    // the far frustum plane is camera Z = -f. Put another way
    // the camera Z coordinate is negative "depth".
    //
    // If (X,Y,Z,W) denotes camera coordinates, then as the value of
    // camera Z/W coordinate approaches -infinity from above,
    // (depth approaches +infinity from below), the value of 
    // clipping z/w approaches -(f+n)/(f-n) from above. 
    //
    // As camera coordinate Z/W approaches zero from below, 
    // (depth approaches zero from above), the value of
    // clipping z/w approaches +infinity from below.
    //
    // The perspective projection transformation will map "points behind
    // the camera" (camera Z coordinate > 0) to a clipping coordinate
    // in the interval ( -infinity, -(f+n)/(f-n) ).
    //
    // To get a linear map from camera z to [-1,1], apply the linear
    // fractional transformation that maps [-1,1] -> [-1,1]
    //
    //   L(s): s -> (a*s + b)/(a + bs),
    //
    // where a = (n+f) and b = (f-n), to the z coordinate 
    // of the perspective projection transformation.
    //
    // Specifically, if M is the perspective transformation matrix above, 
    // and transpose(x,y,z,w) = M*transpose(X,Y,(1-s)*n + s*f,1), then
    // (a*z + b*w)/(a*w + b*z) = 1 - 2s. 
    //
    // Note that L(s) has a pole at s = -(f+n)/(f-n).
    //
    // The inverse of the linear fractional transformation L is G
    //
    //   G(t): t -> (a*t - b)/(a - b*t)
    //

    dd = (right-left);
    m_xform[0][0] = 2.0*near_dist/dd; 
    m_xform[0][2] = (right+left)/dd; 
    m_xform[0][1] = m_xform[0][3] = 0.0;

    dd = (top-bottom);
    m_xform[1][1] = 2.0*near_dist/dd; 
    m_xform[1][2] = (top+bottom)/dd; 
    m_xform[1][0] = m_xform[1][3] = 0.0;

    dd = (far_dist-near_dist);
    m_xform[2][2] = (far_dist+near_dist)/dd; 
    m_xform[2][3] = 2.0*near_dist*far_dist/dd; 
    m_xform[2][0] = m_xform[2][1] = 0.0;

    m_xform[3][0] = m_xform[3][1] = m_xform[3][3] = 0.0; 
    m_xform[3][2] = -1.0;
  }
  return true;
}

bool ON_Xform::ClipToCamera(
      bool bPerspective,
      double left,      double right,
      double bottom,    double top,
      double near_dist, double far_dist
      )
{
  // see comments in tl2_xform.h for details.
  double dd;
  if ( left == right || bottom == top || near_dist == far_dist )
    return false;

  if ( !bPerspective ) {
    // parallel projection
    m_xform[0][0] = 0.5*(right-left); m_xform[0][3] = 0.5*(right+left); m_xform[0][1] = m_xform[0][2] = 0.0;
    m_xform[1][1] = 0.5*(top-bottom); m_xform[1][3] = 0.5*(top+bottom); m_xform[1][0] = m_xform[1][2] = 0.0;
    m_xform[2][2] = 0.5*(far_dist-near_dist);   m_xform[2][3] = -0.5*(far_dist+near_dist);  m_xform[2][0] = m_xform[2][1] = 0.0;
    m_xform[3][0] = m_xform[3][1] = m_xform[3][2] = 0.0; m_xform[3][3] = 1.0;
  }
  else {
    // perspective projection
    //  (r-l)/(2n)       0            0       (r+l)/(2n)
    //    0         (t-b)/(2n)        0       (t+b)/(2n)
    //    0              0            0           -1
    //    0              0       (f-n)/(2fn)  (f+n)/(2fn)
    //d = 0.5/near_dist;
    //m_xform[0][0] = d*(right-left); 
    //m_xform[0][3] = d*(right+left); 
    //m_xform[0][1] = m_xform[0][2] = 0.0;

    //m_xform[1][1] = d*(top-bottom); 
    //m_xform[1][3] = d*(top+bottom); 
    //m_xform[1][0] = m_xform[1][2] = 0.0;

    //m_xform[2][0] = m_xform[2][1] = m_xform[2][2] = 0.0; m_xform[2][3] = -1.0;

    //d /= far_dist;
    //m_xform[3][2] = d*(far_dist-near_dist); 
    //m_xform[3][3] = d*(far_dist+near_dist); 
    //m_xform[3][0] = m_xform[3][1] = 0.0;

    dd = 2.0*near_dist;
    m_xform[0][0] = (right-left)/dd; 
    m_xform[0][3] = (right+left)/dd; 
    m_xform[0][1] = m_xform[0][2] = 0.0;

    m_xform[1][1] = (top-bottom)/dd; 
    m_xform[1][3] = (top+bottom)/dd; 
    m_xform[1][0] = m_xform[1][2] = 0.0;

    m_xform[2][0] = m_xform[2][1] = m_xform[2][2] = 0.0; m_xform[2][3] = -1.0;

    dd *= far_dist;
    m_xform[3][2] = (far_dist-near_dist)/dd; 
    m_xform[3][3] = (far_dist+near_dist)/dd; 
    m_xform[3][0] = m_xform[3][1] = 0.0;
  }

  return true;
}

bool ON_Xform::ClipToScreen(
      double left,   double right,
      double bottom, double top,
      double near_z, double far_z
      )
{
  // see comments in tl2_xform.h for details.
  if ( left == right || bottom == top )
    return false;

  m_xform[0][0] = 0.5*(right-left);
  m_xform[0][3] = 0.5*(right+left);
  m_xform[0][1] = m_xform[0][2] = 0.0;

  m_xform[1][1] = 0.5*(top-bottom);
  m_xform[1][3] = 0.5*(top+bottom);
  m_xform[1][0] = m_xform[1][2] = 0.0;

  if (far_z != near_z) {
    m_xform[2][2] = 0.5*(near_z-far_z);
    m_xform[2][3] = 0.5*(near_z+far_z);
  }
  else {
    m_xform[2][2] = 1.0;
    m_xform[2][3] = 0.0;
  }
  m_xform[2][0] = m_xform[2][1] = 0.0;

  m_xform[3][0] = m_xform[3][1] = m_xform[3][2] = 0.0; 
  m_xform[3][3] = 1.0;

  return true;
}

bool ON_Xform::ScreenToClip(
      double left,   double right,
      double bottom, double top,
      double near_z, double far_z
      )
{
  // see comments in tl2_xform.h for details.
  ON_Xform c2s;
  bool rc = c2s.ClipToScreen( left, right, bottom, top, near_z, far_z );
  if (rc) {
    m_xform[0][0] = 1.0/c2s[0][0]; m_xform[0][3] = -c2s[0][3]/c2s[0][0];
    m_xform[0][1] = m_xform[0][2] = 0.0;

    m_xform[1][1] = 1.0/c2s[1][1]; m_xform[1][3] = -c2s[1][3]/c2s[1][1];
    m_xform[1][0] = m_xform[1][2] = 0.0;

    m_xform[2][2] = 1.0/c2s[2][2]; m_xform[2][3] = -c2s[2][3]/c2s[2][2];
    m_xform[2][0] = m_xform[2][1] = 0.0;

    m_xform[3][0] = m_xform[3][1] = m_xform[3][2] = 0.0; 
    m_xform[3][3] = 1.0;
  }
  return rc;
}


int ON_Xform::ClipFlag4d( const double* point ) const
{
  if ( !point )
    return 1|2|4|8|16|32;
  int clip = 0;
  double x = m_xform[0][0]*point[0] + m_xform[0][1]*point[1] + m_xform[0][2]*point[2] + m_xform[0][3]*point[3];
  double y = m_xform[1][0]*point[0] + m_xform[1][1]*point[1] + m_xform[1][2]*point[2] + m_xform[1][3]*point[3];
  double z = m_xform[2][0]*point[0] + m_xform[2][1]*point[1] + m_xform[2][2]*point[2] + m_xform[2][3]*point[3];
  double w = m_xform[3][0]*point[0] + m_xform[3][1]*point[1] + m_xform[3][2]*point[2] + m_xform[3][3]*point[3];
  if ( point[3] < 0.0 ) {
    x = -x; y = -y; z = -z; w = -w;
  }
  if ( x <= -w )
    clip |= 1;
  else if ( x >= w )
    clip |= 2;
  if ( y <= -w )
    clip |= 4;
  else if ( y >= w )
    clip |= 8;
  if ( z <= -w )
    clip |= 16;
  else if ( z >= w )
    clip |= 32;
  return clip;
}

int ON_Xform::ClipFlag3d( const double* point ) const
{
  if ( !point )
    return 1|2|4|8|16|32;
  int clip = 0;
  const double x = m_xform[0][0]*point[0] + m_xform[0][1]*point[1] + m_xform[0][2]*point[2] + m_xform[0][3];
  const double y = m_xform[1][0]*point[0] + m_xform[1][1]*point[1] + m_xform[1][2]*point[2] + m_xform[1][3];
  const double z = m_xform[2][0]*point[0] + m_xform[2][1]*point[1] + m_xform[2][2]*point[2] + m_xform[2][3];
  const double w = m_xform[3][0]*point[0] + m_xform[3][1]*point[1] + m_xform[3][2]*point[2] + m_xform[3][3];
  if ( x <= -w )
    clip |= 1;
  else if ( x >= w )
    clip |= 2;
  if ( y <= -w )
    clip |= 4;
  else if ( y >= w )
    clip |= 8;
  if ( z <= -w )
    clip |= 16;
  else if ( z >= w )
    clip |= 32;
  return clip;
}

int ON_Xform::ClipFlag4d( int count, int stride, const double* point, 
                            bool bTestZ ) const
{
  int clip = 1|2|4|8;
  if ( bTestZ)
    clip |= (16|32);
  if ( point && ((count > 0 && stride >= 4) || count == 1) ) {
    for ( /*empty*/; clip && count--; point += stride ) {
      clip &= ClipFlag4d( point );
    }
  }
  return clip;
}

int ON_Xform::ClipFlag3d( int count, int stride, const double* point, 
                            bool bTestZ ) const
{
  int clip = 1|2|4|8;
  if ( bTestZ)
    clip |= (16|32);
  if ( point && ((count > 0 && stride >= 3) || count == 1) ) {
    for ( /*empty*/; clip && count--; point += stride ) {
      clip &= ClipFlag3d( point );
    }
  }
  return clip;
}

int ON_Xform::ClipFlag3dBox( const double* boxmin, const double* boxmax ) const
{
  int clip = 1|2|4|8|16|32;
  double point[3];
  int i,j,k;
  if ( boxmin && boxmax ) {
    for (i=0;i<2;i++) {
      point[0] = (i)?boxmax[0]:boxmin[0];
      for (j=0;j<2;j++) {
        point[1] = (j)?boxmax[1]:boxmin[1];
        for (k=0;k<2;k++) {
          point[2] = (k)?boxmax[2]:boxmin[2];
          clip &= ClipFlag3d(point);
          if ( !clip )
            return 0;
        }
      }
    }
  }
  return clip;
}

ON_Xform& ON_Xform::operator=(const ON_Matrix& src)
{
  int i,j;
  i = src.RowCount();
  const int maxi = (i>4)?4:i;
  j = src.ColCount();
  const int maxj = (j>4)?4:j;
  *this = ON_Xform::IdentityTransformation;
  for ( i = 0; i < maxi; i++ ) for ( j = 0; j < maxj; j++ ) {
    m_xform[i][j] = src.m[i][j];
  }
  return *this;
}

bool ON_Xform::IntervalChange(
  int dir,
  ON_Interval old_interval,
  ON_Interval new_interval
  )
{
  bool rc = false;

  *this = ON_Xform::IdentityTransformation;
  if (   dir >= 0 
       && dir <= 3 
       && old_interval[0] != ON_UNSET_VALUE
       && old_interval[1] != ON_UNSET_VALUE
       && new_interval[0] != ON_UNSET_VALUE
       && new_interval[1] != ON_UNSET_VALUE
       && old_interval.Length() != 0.0
       )
  {
    rc = true;
    if ( new_interval != old_interval )
    {
      double s = new_interval.Length()/old_interval.Length();;
      double d = (new_interval[0]*old_interval[1] - new_interval[1]*old_interval[0])/old_interval.Length();
      m_xform[dir][dir] = s;
      m_xform[dir][3] = d;
    }
  }
  return rc;
}
