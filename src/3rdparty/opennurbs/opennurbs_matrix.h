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

#if !defined(ON_MATRIX_INC_)
#define ON_MATRIX_INC_

class ON_Xform;

class ON_CLASS ON_Matrix
{
public:
  ON_Matrix();
  ON_Matrix( 
    int row_count,
    int col_count
     );
  ON_Matrix( // see ON_Matrix::Create(int,int,int,int) for details
     int, // first valid row index
     int, // last valid row index
     int, // first valid column index
     int  // last valid column index
     );
  ON_Matrix( const ON_Xform& );
  ON_Matrix( const ON_Matrix& );

#if defined(ON_HAS_RVALUEREF)
  // rvalue copy constructor
  ON_Matrix(ON_Matrix&&) ON_NOEXCEPT;

  // The rvalue assignment operator calls ON_Object::operator=(ON_Object&&)
  // which could throw exceptions.  See the implementation of
  // ON_Object::operator=(ON_Object&&) for details.
  ON_Matrix& operator=(ON_Matrix&&);
#endif

  /*
  Description:
    This constructor is for experts who have storage for a matrix
    and need to use it in ON_Matrix form.
  Parameters:
    row_count - [in]
    col_count - [in]
    M - [in]
    bDestructorFreeM - [in]
      If true, ~ON_Matrix will call onfree(M).
      If false, caller is managing M's memory.
  Remarks:
    ON_Matrix functions that increase the value of row_count or col_count
    will fail on a matrix created with this constructor.
  */
  ON_Matrix(
    int row_count,
    int col_count,
    double** M,
    bool bDestructorFreeM
    );

  /*
  Returns:
    A row_count X col_count martix on the heap that can be 
    deleted by calling ON_Matrix::Deallocate().
  */
  static double** Allocate(
    unsigned int row_count,
    unsigned int col_count
    );

  static void Deallocate(
    double** M
    );

  virtual ~ON_Matrix();
  void EmergencyDestroy(); // call if memory pool used matrix by becomes invalid

  // ON_Matrix[i][j] = value at row i and column j
  //           0 <= i < RowCount()
  //           0 <= j < ColCount()
  double* operator[](int);
  const double* operator[](int) const;

  ON_Matrix& operator=(const ON_Matrix&);
  ON_Matrix& operator=(const ON_Xform&);

  bool IsValid() const;
  int IsSquare() const; // returns 0 for no and m_row_count (= m_col_count) for yes

  int RowCount() const;
  int ColCount() const;
  int MinCount() const; // smallest of row and column count
  int MaxCount() const; // largest of row and column count

  unsigned int UnsignedRowCount() const;
  unsigned int UnsignedColCount() const;
  unsigned int UnsignedMinCount() const; // smallest of row and column count
  unsigned int UnsignedMaxCount() const; // largest of row and column count

  void RowScale(int,double); 
  void ColScale(int,double);
  void RowOp(int,double,int);
  void ColOp(int,double,int);

  bool Create(
     int, // number of rows
     int  // number of columns
     );

  bool Create( // E.g., Create(1,5,1,7) creates a 5x7 sized matrix that with
               // "top" row = m[1][1],...,m[1][7] and "bottom" row
               // = m[5][1],...,m[5][7].  The result of Create(0,m,0,n) is
               // identical to the result of Create(m+1,n+1).
     int, // first valid row index
     int, // last valid row index
     int, // first valid column index
     int  // last valid column index
     );

  /*
  Description:
    This constructor is for experts who have storage for a matrix
    and need to use it in ON_Matrix form.
  Parameters:
    row_count - [in]
    col_count - [in]
    M - [in]
      M should point to the start of an array of double*,
      each pointing to the start of the storage for a row.
    bDestructorFreeM - [in]
      If true, ~ON_Matrix will call onfree(M).
      If false, caller is managing M's memory.
  Remarks:
    ON_Matrix functions that increase the value of row_count or col_count
    will fail on a matrix created with this constructor.
  */
  bool Create(
    int row_count,
    int col_count,
    double** M,
    bool bDestructorFreeM
    );


  void Destroy();

  void Zero();

  void SetDiagonal(double); // sets diagonal value and zeros off diagonal values
  void SetDiagonal(const double*); // sets diagonal values and zeros off diagonal values
  void SetDiagonal(int, const double*); // sets size to count x count and diagonal values and zeros off diagonal values
  void SetDiagonal(const ON_SimpleArray<double>&); // sets size to length X lengthdiagonal values and zeros off diagonal values

  bool Transpose();

  bool SwapRows( int, int ); // ints are row indices to swap
  bool SwapCols( int, int ); // ints are col indices to swap
  bool Invert( 
          double // zero tolerance
          );

  /*
  Description:
    Set this = A*B.
  Parameters:
    A - [in]
      (Can be this)
    B - [in]
      (Can be this)
  Returns:
    True when A is an mXk matrix and B is a k X n matrix; in which case
    "this" will be an mXn matrix = A*B.
    False when A.ColCount() != B.RowCount().
  */
  bool Multiply( const ON_Matrix& A, const ON_Matrix& B );

  /*
  Description:
    Set this = A+B.
  Parameters:
    A - [in]
      (Can be this)
    B - [in]
      (Can be this)
  Returns:
    True when A and B are mXn matrices; in which case
    "this" will be an mXn matrix = A+B.
    False when A and B have different sizes.
  */
  bool Add( const ON_Matrix& A, const ON_Matrix& B );


  /*
  Description:
    Set this = s*this.
  Parameters:
    s - [in]
  Returns:
    True when A and s are valid.
  */
  bool Scale( double s );


  // Description:
  //   Row reduce a matrix to calculate rank and determinant.
  // Parameters:
  //   zero_tolerance - [in] (>=0.0) zero tolerance for pivot test
  //       If the absolute value of a pivot is <= zero_tolerance,
  //       then the pivot is assumed to be zero.
  //   determinant - [out] value of determinant is returned here.
  //   pivot - [out] value of the smallest pivot is returned here
  // Returns:
  //   Rank of the matrix.
  // Remarks:
  //   The matrix itself is row reduced so that the result is
  //   an upper triangular matrix with 1's on the diagonal.
  int RowReduce( // returns rank
    double,  // zero_tolerance
    double&, // determinant
    double&  // pivot
    ); 

  // Description:
  //   Row reduce a matrix as the first step in solving M*X=B where
  //   B is a column of values.
  // Parameters:
  //   zero_tolerance - [in] (>=0.0) zero tolerance for pivot test
  //       If the absolute value of a pivot is <= zero_tolerance,
  //       then the pivot is assumed to be zero.
  //   B - [in/out] an array of m_row_count values that is row reduced
  //       with the matrix.
  //   determinant - [out] value of determinant is returned here.
  //   pivot - [out] If not nullptr, then the value of the smallest 
  //       pivot is returned here
  // Returns:
  //   Rank of the matrix.
  // Remarks:
  //   The matrix itself is row reduced so that the result is
  //   an upper triangular matrix with 1's on the diagonal.
  // Example:
  //   Solve M*X=B;
  //   double B[m] = ...;
  //   double B[n] = ...;
  //   ON_Matrix M(m,n) = ...;
  //   M.RowReduce(ON_ZERO_TOLERANCE,B); // modifies M and B
  //   M.BackSolve(m,B,X); // solution is in X
  // See Also: 
  //   ON_Matrix::BackSolve
  int RowReduce(
    double,        // zero_tolerance
    double*,       // B
    double* = nullptr // pivot
    ); 

  // Description:
  //   Row reduce a matrix as the first step in solving M*X=B where
  //   B is a column of 3d points
  // Parameters:
  //   zero_tolerance - [in] (>=0.0) zero tolerance for pivot test
  //       If the absolute value of a pivot is <= zero_tolerance,
  //       then the pivot is assumed to be zero.
  //   B - [in/out] an array of m_row_count 3d points that is 
  //       row reduced with the matrix.
  //   determinant - [out] value of determinant is returned here.
  //   pivot - [out] If not nullptr, then the value of the smallest 
  //       pivot is returned here
  // Returns:
  //   Rank of the matrix.
  // Remarks:
  //   The matrix itself is row reduced so that the result is
  //   an upper triangular matrix with 1's on the diagonal.
  // See Also: 
  //   ON_Matrix::BackSolve
  int RowReduce(
    double,        // zero_tolerance
    ON_3dPoint*,   // B
    double* = nullptr // pivot
    ); 

  // Description:
  //   Row reduce a matrix as the first step in solving M*X=B where
  //   B is a column arbitrary dimension points.
  // Parameters:
  //   zero_tolerance - [in] (>=0.0) zero tolerance for pivot test
  //       If a the absolute value of a pivot is <= zero_tolerance,
  //       then the pivoit is assumed to be zero.
  //   pt_dim - [in] dimension of points
  //   pt_stride - [in] stride between points (>=pt_dim)
  //   pt - [in/out] array of m_row_count*pt_stride values.
  //        The i-th point is
  //        (pt[i*pt_stride],...,pt[i*pt_stride+pt_dim-1]).
  //        This array of points is row reduced along with the 
  //        matrix.
  //   pivot - [out] If not nullptr, then the value of the smallest 
  //       pivot is returned here
  // Returns:
  //   Rank of the matrix.
  // Remarks:
  //   The matrix itself is row reduced so that the result is
  //   an upper triangular matrix with 1's on the diagonal.
  // See Also: 
  //   ON_Matrix::BackSolve
  int RowReduce( // returns rank
    double,      // zero_tolerance
    int,         // pt_dim
    int,         // pt_stride
    double*,     // pt
    double* = nullptr // pivot
    ); 

  // Description:
  //   Solve M*X=B where M is upper triangular with a unit diagonal and
  //   B is a column of values.
  // Parameters:
  //   zero_tolerance - [in] (>=0.0) used to test for "zero" values in B
  //       in under determined systems of equations.
  //   Bsize - [in] (>=m_row_count) length of B.  The values in
  //       B[m_row_count],...,B[Bsize-1] are tested to make sure they are
  //       "zero".
  //   B - [in] array of length Bsize.
  //   X - [out] array of length m_col_count.  Solutions returned here.
  // Remarks:
  //   Actual values M[i][j] with i <= j are ignored. 
  //   M[i][i] is assumed to be one and M[i][j] i<j is assumed to be zero.
  //   For square M, B and X can point to the same memory.
  // See Also:
  //   ON_Matrix::RowReduce
  bool BackSolve(
    double,        // zero_tolerance
    int,           // Bsize
    const double*, // B
    double*        // X
      ) const;

  // Description:
  //   Solve M*X=B where M is upper triangular with a unit diagonal and
  //   B is a column of 3d points.
  // Parameters:
  //   zero_tolerance - [in] (>=0.0) used to test for "zero" values in B
  //       in under determined systems of equations.
  //   Bsize - [in] (>=m_row_count) length of B.  The values in
  //       B[m_row_count],...,B[Bsize-1] are tested to make sure they are
  //       "zero".
  //   B - [in] array of length Bsize.
  //   X - [out] array of length m_col_count.  Solutions returned here.
  // Remarks:
  //   Actual values M[i][j] with i <= j are ignored. 
  //   M[i][i] is assumed to be one and M[i][j] i<j is assumed to be zero.
  //   For square M, B and X can point to the same memory.
  // See Also:
  //   ON_Matrix::RowReduce
  bool BackSolve(
    double,            // zero_tolerance
    int,               // Bsize
    const ON_3dPoint*, // B
    ON_3dPoint*        // X
      ) const;

  // Description:
  //   Solve M*X=B where M is upper triangular with a unit diagonal and
  //   B is a column of points
  // Parameters:
  //   zero_tolerance - [in] (>=0.0) used to test for "zero" values in B
  //       in under determined systems of equations.
  //   pt_dim - [in] dimension of points
  //   Bsize - [in] (>=m_row_count) number of points in B[].  The points
  //       corresponding to indices m_row_count, ..., (Bsize-1)
  //       are tested to make sure they are "zero".
  //   Bpt_stride - [in] stride between B points (>=pt_dim)
  //   Bpt - [in/out] array of m_row_count*Bpt_stride values.
  //        The i-th B point is
  //        (Bpt[i*Bpt_stride],...,Bpt[i*Bpt_stride+pt_dim-1]).
  //   Xpt_stride - [in] stride between X points (>=pt_dim)
  //   Xpt - [out] array of m_col_count*Xpt_stride values.
  //        The i-th X point is
  //        (Xpt[i*Xpt_stride],...,Xpt[i*Xpt_stride+pt_dim-1]).
  // Remarks:
  //   Actual values M[i][j] with i <= j are ignored. 
  //   M[i][i] is assumed to be one and M[i][j] i<j is assumed to be zero.
  //   For square M, B and X can point to the same memory.
  // See Also:
  //   ON_Matrix::RowReduce
  bool BackSolve(
    double,       // zero_tolerance
    int,          // pt_dim
    int,          // Bsize
    int,          // Bpt_stride
    const double*,// Bpt
    int,          // Xpt_stride
    double*       // Xpt
      ) const;

  bool IsRowOrthoganal() const;
  bool IsRowOrthoNormal() const;

  bool IsColOrthoganal() const;
  bool IsColOrthoNormal() const;

  // 2024-09-05, Pierre:
  // Note that this does not mean the memory allocated is contiguous.
  // m points to the start of m_rowmem[0] in most cases.
  // When the matrix is bigger than max_dblblk_size (see ON_Matrix::Create), m_rowmem does
  // not point to contiguous pieces of memory, and indexing as **(m + i*m_col_count + j)
  // would read into the wrong place.
  double** m = nullptr; // m[i][j] = value at row i and column j
              //           0 <= i < RowCount()
              //           0 <= j < ColCount()
private:
  int m_row_count = 0;
  int m_col_count = 0;
  // m_rowmem[i][j] = row i+m_row_offset and column j+m_col_offset.
  ON_SimpleArray<double*> m_rowmem; 
	double** m_Mmem = nullptr; // used by Create(row_count,col_count,user_memory,true);
	int   m_row_offset = 0; // = ri0 when sub-matrix constructor is used
  int   m_col_offset = 0; // = ci0 when sub-matrix constructor is used
  void* m_cmem = nullptr;
  // returns 0 based arrays, even in submatrix case.
  double const * const * ThisM() const;
  double * * ThisM();
};


/*
Description:
  Perform simple row reduction on a matrix.  If A is square, positive
  definite, and really really nice, then the returned B is the inverse
  of A.  If A is not positive definite and really really nice, then it
  is probably a waste of time to call this function.
Parameters:
  row_count - [in]
  col_count - [in]
  zero_pivot - [in]
    absolute values <= zero_pivot are considered to be zero
  A - [in/out]
    A row_count X col_count matrix.  Input is the matrix to be
    row reduced.  The calculation destroys A, so output A is garbage.
  B - [out]
    A a row_count X row_count matrix. That records the row reduction.
  pivots - [out]
    minimum and maximum absolute values of pivots.
Returns:
  Rank of A.  If the returned value < min(row_count,col_count),
  then a zero pivot was encountered.
  If C = input value of A, then B*C = (I,*)
*/
ON_DECL
int ON_RowReduce( 
          int row_count, 
          int col_count,
          double zero_pivot,
          double** A, 
          double** B, 
          double pivots[2] 
          );


/*
Description:
  Calculate a row reduction matrix so that R*M = upper triangular matrixPerform simple row reduction on a matrix.  If A is square, positive
  definite, and really really nice, then the returned B is the inverse
  of A.  If A is not positive definite and really really nice, then it
  is probably a waste of time to call this function.
Parameters:
  row_count - [in]
  col_count - [in]
  zero_pivot - [in]
    absolute values <= zero_pivot_tolerance are considered to be zero
  constA - [in]
    nullptr or a row_count x col_count matrix.
  bInitializeB - [in]
    If true, then B is set to the rox_count x row_count identity
    before the calculation begins.
  bInitializeColumnPermutation - [in]
    If true and nullptr != column_permutation, then
    column_permutation[] is initialized to (0, 1, ..., col_count-1)
    before the calculation begins.
  A - [in/out]
    A row_count X col_count matrix.  
    If constA is not null, then A can be null or is the workspace used
    to row reduce.
    If constA is null, then the input A must not be null and must be initialized.
    In all cases, the calculation destroys the contents of A and
    output A contains garbage.
  B - [in/out]
    A a row_count X row_count matrix
    The row operations applied to A are also applied to B.  
    If the input B is the identity, then R*(input A) would have zeros below the diagonal.
  column_permutation - [in/out]
    The permutation applied to the columns of A is also applied to
    the column_permutation[] array.
    pivots - [out]
    pivots[0] = maximum nonzero pivot
    pivots[1] = minimum nonzero pivot
    pivots[2] = largest pivot that was treated as zero
Returns:
  Rank of A.  If the returned value < min(row_count,col_count),
  then a zero pivot was encountered.
  If C = input value of A, then B*C = (I,*)
*/
ON_DECL
unsigned int ON_RowReduce(
  unsigned int row_count,
  unsigned  col_count,
  double zero_pivot_tolerance,
  const double*const* constA,
  bool bInitializeB,
  bool bInitializeColumnPermutation,
  double** A,
  double** B,
  unsigned int* column_permutation,
  double pivots[3]
  );

/*
Parameters:
  N - [in] >= 1
  M - [in]
    M is an NxN matrix
  
  bTransposeM - [in]
    If true, the eigenvectors of the transpose of M are calculated.
    Put another way, if bTransposeM is false, then the "right"
    eigenvectors are calculated;  if bTransposeM is true, then the "left"
    eigenvectors are calculated.

  lambda - [in]
    known eigenvalue of M

  lambda_multiplicity - [in]
    > 0: known algebraic multiplicity of lambda
    0: algebraic multiplicity is unknown.

  termination_tolerances - [in]
    An array of three tolerances that control when the calculation
    will stop searching for eigenvectors.
    If you do not understand what pivot values are, then pass nullptr
    and the values (1.0e-12, 1.0e-3, 1.0e4) will be used.
    If termination_tolerances[0] is not strictly positive, then 1.0e-12 is used.
    If termination_tolerances[1] is not strictly positive, then 1.0e-3 is used.
    If termination_tolerances[2] is not strictly positive, then 1.0e4 is used.

    The search for eigenvectors will continue if condition 1, 
    and condition 2, and condition 3a or 3b is true.

    1) The number of found eigenvectors is < lambda_multiplicity.
    2) eigenpivots[0] >= eigenpivots[1] > eigenpivots[2] >= 0.
    3a) eigenpivots[1]/eigenpivots[0] < termination_tolerance[0].
    3b) eigenpivots[1]/eigenpivots[0] > termination_tolerance[1]
        or
        eigenpivots[0] - eigenpivots[1] <= termination_tolerance[2]*eigenpivots[1].

  eigenvectors - [out]
    eigenvectors[0,...,eigendim-1][0,...,N-1]
    a basis for the lambda eigenspace.  The eigenvectors are generally
    neither normalized nor orthogonal. 

  eigenprecision - [out]
    eigenprecision[i] = maximum value of fabs(lambda*E[j] = E[j])/length(E) 0 <= j < N,
    where E = eigenvectors[i].
    If eigenprecision[i] is not "small" compared to nonzero coefficients in M and E,
    then E is not precise.

  eigenpivots - [out]
    eigenpivots[0] = maximum nonzero pivot
    eigenpivots[1] = minimum nonzero pivot
    eigenpivots[2] = maximum "zero" pivot
    When eigenpivots[2] s not "small" compared to eigenpivots[1],
    the answer is suspect.

Returns:
  Number of eigenvectors found. In stable cases, this is the geometric
  multiplicity of the eigenvalue.
*/
ON_DECL
unsigned int ON_GetEigenvectors(
  const unsigned int N,
  const double*const* M,
  bool bTransposeM,
  double lambda,
  unsigned int lambda_multiplicity,
  const double* termination_tolerances,
  double** eigenvectors,
  double* eigenprecision,
  double* eigenpivots
  );

ON_DECL
double ON_EigenvectorPrecision(
  const unsigned int N,
  const double*const* M,
  bool bTransposeM,
  double lambda,
  const double* eigenvector
  );

/*
Returns:
  Maximum of fabs( ((M-lambda*I)*X)[i] - B[i] ) for 0 <= i < N
  Pass lambda = 0.0 if you're not testing some type of generalized eigenvalue.
*/
ON_DECL
double ON_MatrixSolutionPrecision(
  const unsigned int N,
  const double*const* M,
  bool bTransposeM,
  double lambda,
  const double* X,
  const double* B
  );

#endif
