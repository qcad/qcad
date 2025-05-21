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

#if !defined(ON_EVALUATE_NURBS_INC_)
#define ON_EVALUATE_NURBS_INC_

ON_DECL
bool ON_IncreaseBezierDegree(
        int,    // dimension 
        bool,   // true if Bezier is rational
        int,    // order (>=2)
        int,    // cv_stride (>=dim+1)
        double* // cv[(order+1)*cv_stride] array
        );

ON_DECL
bool ON_RemoveBezierSingAt0( // input bezier is rational with 0/0 at start
        int,    // dimension 
        int,    // order (>=2)
        int,    // cv_stride (>=dim+1)
        double* // cv[order*cv_stride] array
        );

ON_DECL
bool ON_RemoveBezierSingAt1( // input bezier is rational with 0/0 at end
        int,    // dimension 
        int,    // order (>=2)
        int,    // cv_stride (>=dim+1)
        double* // cv[order*cv_stride] array
        );

ON_DECL
double ON_EvaluateBernsteinBasis( // returns (i choose d)*(1-t)^(d-i)*t^i
        int, // degree, 
        int, // 0 <= i <= degree
        double //  t
        );

ON_DECL
void ON_EvaluatedeCasteljau(
        int,     //  dim
        int,     //  order
        int,     //  side <= 0  return left side of bezier in cv array
                 //       >  0  return right side of bezier in cv array
        int,     //  cv_stride
        double*, //  cv
        double   //  t 0 <= t <= 1
        );

ON_DECL
bool ON_EvaluateBezier(
        int,            // dimension
        bool,           // true if Bezier is rational
        int,            // order (>=2)
        int,            // cv_stride >= (is_rat)?dim+1:dim
        const double*,  // cv[order*cv_stride] array
        double, double, // t0,t1 = domain of bezier
        int,            // number of derivatives to compute (>=0)
        double,         // evaluation parameter
        int,            // v_stride (>=dimension)
        double*         // v[(der_count+1)*v_stride] array
        );
                                      
/*
Description:
  Evaluate B-spline basis functions
 
Parameters:
  order - [in]
    order >= 1 
    d = degree = order - 1
  knot - [in]
    array of length 2*d.  
    Generally, knot[0] <= ... <= knot[d-1] < knot[d] <= ... <= knot[2*d-1].
    These are the knots that are active for the span being evaluated.
  t - [in]
    Evaluation parameter. 
    Typically knot[d-1] <= t <= knot[d].
    In general t may be outside the interval knot[d-1],knot[d]. This can happen 
    when some type of extrapolation is being used and is almost always a bad
    idea in practical situations.

  N - [out]
    double array with capacity order*order.
    The returned values are:

    If "N" were declared as double N[order][order], then

                   k
      N[d-k][i] = N (t) = value of i-th degree k basis function at t.
                   i
    where 0 <= k <= d and k <= i <= d.

	  In particular, N[0], ..., N[d] - values of degree d basis functions.
    The "lower left" triangle is not initialized.

    Actually, the above is true when knot[d-1] <= t < knot[d].  Otherwise, the
    value returned is the value of the polynomial that agrees with N_i^k on the
    half open domain [ knot[d-1], knot[d] )

COMMENTS:
  If a degree d NURBS has n control points, then the OpenNURBS knot vector 
  for the entire NURBS curve has length d+n-1. The knot[] parameter to this
  function points to the 2*d knots active for the span being evaluated.
  
  Most literature, including DeBoor and The NURBS Book,
  duplicate the Opennurbs start and end knot values and have knot vectors
  of length d+n+1. The extra two knot values are completely superfluous 
  when degree >= 1.
  
  Assume C is a B-spline of degree d (order=d+1) with n control vertices
  (n>=d+1) and knot[] is its knot vector.  Then

    C(t) = Sum( 0 <= i < n, N_{i}(t) * C_{i} )

  where N_{i} are the degree d b-spline basis functions and C_{i} are the control
  vertices.  The knot[] array length d+n-1 and satisfies

    knot[0] <= ... <= knot[d-1] < knot[d]
    knot[n-2] < knot[n-1] <= ... <= knot[n+d-2]
    knot[i] < knot[d+i] for 0 <= i < n-1
    knot[i] <= knot[i+1] for 0 <= i < n+d-2

  The domain of C is [ knot[d-1], knot[n-1] ].

  The support of N_{i} is [ knot[i-1], knot[i+d] ).

  If d-1 <= k < n-1 and knot[k] <= t < knot[k+1], then 
  N_{i}(t) = 0 if i <= k-d
           = 0 if i >= k+2
           = B[i-k+d-1] if k-d+1 <= i <= k+1, where B[] is computed by the call
             ON_EvaluateNurbsBasis( d+1, knot+k-d+1, t, B );

  If 0 <= j < n-d, 0 <= m <= d, knot[j+d-1] <= t < knot[j+d], and B[] is 
  computed by the call
    ON_EvaluateNurbsBasis( d+1, knot+j, t, B ),
  then 
    N_{j+m}(t) = B[m].
*/
ON_DECL
bool ON_EvaluateNurbsBasis( 
  int order,
  const double* knot,
  double t,
  double* N
  );

/*
Description:
  Calculate derivatives of B-spline basis functions.
INPUT:
  order - [in]
    order >= 1 
    d = degree = order - 1
  knot - [in]
    array of length 2*d.  
    Generally, knot[0] <= ... <= knot[d-1] < knot[d] <= ... <= knot[2*d-1].
    These are the knots that are active for the span being evaluated.
  der_count - [in]
    1 <= der_count < order
    Number of derivatives. 
    Note all B-spline basis derivatives with der_count >= order are identically zero.

  N - [in]
    The input value of N[] should be the results of the call
    ON_EvaluateNurbsBasis( order, knot, t, N );
	
  N - [out]
    If "N" were declared as double N[order][order], then
	
                                    d
    N[d-k][i] = k-th derivative of N (t)
                                    i
  
	  where 0 <= k <= d and 0 <= i <= d.
	
	 In particular, 
	   N[0], ..., N[d] - values of degree d basis functions.
	   N[order], ..., N[order_d] - values of first derivative.
*/
ON_DECL
bool ON_EvaluateNurbsBasisDerivatives(
  int order,
  const double* knot,
  int der_count,
  double* N
  );

/*
Description:
  Evaluate a NURBS curve span.
Parameters:
  dim - [in]
    dimension (> 0).
  is_rat - [in] 
    true or false.
  order - [in]
    order=degree+1 (order>=2)
  knot - [in] NURBS knot vector.
    NURBS knot vector with 2*(order-1) knots, knot[order-2] != knot[order-1]
  cv_stride - [in]
  cv - [in]
    For 0 <= i < order the i-th control vertex is

          cv[n],...,cv[n+(is_rat?dim:dim+1)], 

    where n = i*cv_stride.  If is_rat is true the cv is
    in homogeneous form.
  der_count - [in] 
    number of derivatives to evaluate (>=0)
  t - [in] 
    evaluation parameter
  v_stride - [in]
  v - [out]
    An array of length v_stride*(der_count+1). The evaluation 
    results are returned in this array.

              P = v[0],...,v[m_dim-1]
              Dt = v[v_stride],...
              Dtt = v[2*v_stride],...
              ...

            In general, Dt^i returned in v[n],...,v[n+m_dim-1], where

              n = v_stride*i.
    
Returns:
  True if successful.
See Also:
  ON_NurbsCurve::Evaluate
  ON_EvaluateNurbsSurfaceSpan
  ON_EvaluateNurbsCageSpan
*/
ON_DECL
bool ON_EvaluateNurbsSpan( 
        int dim,
        bool is_rat,
        int order,
        const double* knot,
        int cv_stride,
        const double* cv,
        int der_count,
        double t,
        int v_stride,
        double* v
        );

/*
Description:
  Evaluate a NURBS surface bispan.
Parameters:
  dim - [in] >0
  is_rat - [in] true of false
  order0 - [in] >= 2
  order1 - [in] >= 2
  knot0 - [in] 
    NURBS knot vector with 2*(order0-1) knots, knot0[order0-2] != knot0[order0-1]
  knot1 - [in]
    NURBS knot vector with 2*(order1-1) knots, knot1[order1-2] != knot1[order1-1]
  cv_stride0 - [in]
  cv_stride1 - [in]
  cv - [in]
    For 0 <= i < order0 and  0 <= j < order1, the (i,j) control vertex is

          cv[n],...,cv[n+(is_rat?dim:dim+1)], 

    where n = i*cv_stride0 + j*cv_stride1.  If is_rat is true the cv is
    in homogeneous form.
   
  der_count - [in] (>=0)
  s - [in]
  t - [in] (s,t) is the evaluation parameter
  v_stride - [in] (>=dim)
  v - [out] An array of length v_stride*(der_count+1)*(der_count+2)/2.
            The evaluation results are stored in this array.

              P = v[0],...,v[m_dim-1]
              Ds = v[v_stride],...
              Dt = v[2*v_stride],...
              Dss = v[3*v_stride],...
              Dst = v[4*v_stride],...
              Dtt = v[5*v_stride],...

            In general, Ds^i Dt^j is returned in v[n],...,v[n+m_dim-1], where

              n = v_stride*( (i+j)*(i+j+1)/2 + j).

Returns:
  True if successful.
See Also:
  ON_NurbsSurface::Evaluate
  ON_EvaluateNurbsSpan
  ON_EvaluateNurbsCageSpan
*/
ON_DECL
bool ON_EvaluateNurbsSurfaceSpan(
        int dim,
        bool is_rat,
        int order0, 
        int order1,
        const double* knot0,
        const double* knot1,
        int cv_stride0,
        int cv_stride1,
        const double* cv,
        int der_count,
        double s,
        double t,
        int v_stride,
        double* v
        );
            


/*
Description:
  Evaluate a NURBS cage trispan.
Parameters:
  dim - [in] >0
  is_rat - [in] true of false
  order0 - [in] >= 2
  order1 - [in] >= 2
  order2 - [in] >= 2
  knot0 - [in] 
    NURBS knot vector with 2*(order0-1) knots, knot0[order0-2] != knot0[order0-1]
  knot1 - [in]
    NURBS knot vector with 2*(order1-1) knots, knot1[order1-2] != knot1[order1-1]
  knot2 - [in]
    NURBS knot vector with 2*(order1-1) knots, knot2[order2-2] != knot2[order2-1]
  cv_stride0 - [in]
  cv_stride1 - [in]
  cv_stride2 - [in]
  cv - [in]
    For 0 <= i < order0, 0 <= j < order1, and 0 <= k < order2, 
    the (i,j,k)-th control vertex is

          cv[n],...,cv[n+(is_rat?dim:dim+1)], 

    where n = i*cv_stride0 + j*cv_stride1 *k*cv_stride2.  
    If is_rat is true the cv is in homogeneous form.
   
  der_count - [in] (>=0)
  r - [in]
  s - [in]
  t - [in] (r,s,t) is the evaluation parameter
  v_stride - [in] (>=dim)
  v - [out] An array of length v_stride*(der_count+1)*(der_count+2)*(der_count+3)/6.
            The evaluation results are stored in this array.

              P = v[0],...,v[m_dim-1]
              Dr = v[v_stride],...
              Ds = v[2*v_stride],...
              Dt = v[3*v_stride],...
              Drr = v[4*v_stride],...
              Drs = v[5*v_stride],...
              Drt = v[6*v_stride],...
              Dss = v[7*v_stride],...
              Dst = v[8*v_stride],...
              Dtt = v[9*v_stride],...

            In general, Dr^i Ds^j Dt^k is returned in v[n],...,v[n+dim-1], where

               d = (i+j+k)
               n = v_stride*( d*(d+1)*(d+2)/6 + (j+k)*(j+k+1)/2 + k) 

Returns:
  True if successful.
See Also:
  ON_NurbsCage::Evaluate
  ON_EvaluateNurbsSpan
  ON_EvaluateNurbsSurfaceSpan
*/
ON_DECL
bool ON_EvaluateNurbsCageSpan(
        int dim,
        bool is_rat,
        int order0, int order1, int order2,
        const double* knot0,
        const double* knot1,
        const double* knot2,
        int cv_stride0, int cv_stride1, int cv_stride2,
        const double* cv,
        int der_count,
        double t0, double t1, double t2,
        int v_stride, 
        double* v
        );


ON_DECL
bool ON_EvaluateNurbsDeBoor( // for expert users only - no support available
        int,            // cv_dim ( dim+1 for rational cvs )
        int,            // order (>=2)
        int,            // cv_stride (>=cv_dim)
        double*,        // cv array - values changed to result of applying De Boor's algorithm
        const double*,  // knot array
        int,            // side,
                        //    -1  return left side of B-spline span in cv array
                        //    +1  return right side of B-spline span in cv array
                        //    -2  return left side of B-spline span in cv array
                        //        Ignore values of knots[0,...,order-3] and assume
                        //        left end of span has a fully multiple knot with
                        //        value "mult_k".
                        //    +2  return right side of B-spline span in cv array
                        //        Ignore values of knots[order,...,2*order-2] and
                        //        assume right end of span has a fully multiple
                        //        knot with value "mult_k".
        double,         // mult_k - used when side is +2 or -2.  See above for usage.
        double          // t
                        //    If side < 0, then the cv's for the portion of the NURB span to
                        //    the LEFT of t are computed.  If side > 0, then the cv's for the
                        //    portion the span to the RIGHT of t are computed.  The following
                        //    table summarizes the restrictions on t:
                        //
                        //     value of side         condition t must satisfy
                        //        -2                    mult_k < t and mult_k < knots[order-1]
                        //        -1                    knots[order-2] < t
                        //        +1                    t < knots[order-1]
                        //        +2                    t < mult_k and knots[order-2] < mult_k
        );


ON_DECL
bool ON_EvaluateNurbsBlossom(int, // cvdim,
                             int, // order, 
                             int, // cv_stride,
                             const double*, //CV, size cv_stride*order
                             const double*, //knot, nondecreasing, size 2*(order-1)
                             // knot[order-2] != knot[order-1]
                             const double*, //t, input parameters size order-1
                             double* // P

                             // DeBoor algorithm with different input at each step.
                             // returns false for bad input.
                            );


ON_DECL
void ON_ConvertNurbSpanToBezier(
        int,       // cvdim (dim+1 for rational curves)
        int,       // order, 
        int,       // cvstride (>=cvdim)
        double*,   // cv array - input has NURBS cvs, output has Bezier cvs
        const double*, // (2*order-2) knots for the NURBS span
        double,        // t0, NURBS span parameter of start point
        double         // t1, NURBS span parameter of end point
        );
#endif
