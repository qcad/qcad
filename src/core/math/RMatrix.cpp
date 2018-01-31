/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */
#include <cassert>

#include "RDebug.h"
#include "RMatrix.h"

/**
 * Creates and empty matrix (zero columns and zero rows).
 */
RMatrix::RMatrix() :
    m(NULL), rows(0), cols(0) {
}

/**
 * Creates a matrix with \c r rows and \c c columns.
 * All elements are reset to 0.
 *
 * \param r number of rows
 *
 * \param c number of columns
 *
 */
RMatrix::RMatrix(int r, int c) :
    m(NULL), rows(0), cols(0) {
    init(r, c);
}

/**
 * Copy constructor.
 */
RMatrix::RMatrix(const RMatrix& other) :
    m(NULL), rows(0), cols(0) {
    (*this) = other;
}

/**
 * Deletes the matrix.
 */
RMatrix::~RMatrix() {
    clear();
}

/**
 * \return True if this matrix is a valid matrix (more than 0 columns and rows).
 */
bool RMatrix::isValid() const {
    if (cols<=0 || rows<=0) {
        return false;
    }
    if (m==NULL) {
        return false;
    }
    for (int rc = 0; rc < rows; ++rc) {
        for (int cc = 0; cc < cols; ++cc) {
            if (RMath::isNaN(m[rc][cc])) {
                return false;
            }
        }
    }
    return true;
}

/**
 * \return An identity matrix with 2 rows and 2 columns:
 * \f$
 *   \left( \begin{array}{ccc}
 *     1 & 0 \\
 *     0 & 1
 *   \end{array} \right)
 * \f$
 */
RMatrix RMatrix::createIdentity2x2() {
    return createIdentity(2);
}

/**
 * \return An identity matrix with 3 rows and 3 columns:
 * \f$
 *   \left( \begin{array}{ccc}
 *     1 & 0 & 0 \\
 *     0 & 1 & 0 \\
 *     0 & 0 & 1
 *   \end{array} \right)
 * \f$
 */
RMatrix RMatrix::createIdentity3x3() {
    return createIdentity(3);
}

/**
 * \return An identity matrix with \c size rows and \c size columns:
 * \f$
 *   \left( \begin{array}{cccc}
 *     1 & 0 & 0 & \ldots \\
 *     0 & 1 & 0 & \ldots \\
 *     0 & 0 & 1 & \ldots \\
 *     \ldots & \ldots & \ldots & \ldots
 *   \end{array} \right)
 * \f$
 */
RMatrix RMatrix::createIdentity(int size) {
    RMatrix ret(size, size);
    for (int i = 0; i < size; ++i) {
        ret.set(i, i, 1);
    }
    return ret;
}

RMatrix RMatrix::createRotation(double angle) {
    return RMatrix::create2x2(
        cos(angle), -sin(angle),
        sin(angle), cos(angle)
    );
}

/**
 * \return A matrix with 2 rows and 2 columns:
 * \f$
 *   \left( \begin{array}{ccc}
 *     a_{11} & a_{12} \\
 *     a_{21} & a_{22}
 *   \end{array} \right)
 * \f$
 */
RMatrix RMatrix::create2x2(double a11, double a12,
                           double a21, double a22) {
    RMatrix ret(2, 2);

    ret.set(0, 0, a11);
    ret.set(0, 1, a12);

    ret.set(1, 0, a21);
    ret.set(1, 1, a22);

    return ret;
}

/**
 * \return A matrix with 3 rows and 3 columns:
 * \f$
 *   \left( \begin{array}{ccc}
 *     a_{11} & a_{12} & a_{13} \\
 *     a_{21} & a_{22} & a_{23} \\
 *     a_{31} & a_{32} & a_{33}
 *   \end{array} \right)
 * \f$
 */
RMatrix RMatrix::create3x3(double a11, double a12, double a13, double a21,
        double a22, double a23, double a31, double a32, double a33) {
    RMatrix ret(3, 3);

    ret.set(0, 0, a11);
    ret.set(0, 1, a12);
    ret.set(0, 2, a13);

    ret.set(1, 0, a21);
    ret.set(1, 1, a22);
    ret.set(1, 2, a23);

    ret.set(2, 0, a31);
    ret.set(2, 1, a32);
    ret.set(2, 2, a33);

    return ret;
}

/**
 * \return A matrix with 3 rows and 1 column (vector):
 * \f$
 *   \left( \begin{array}{ccc}
 *     a_{11} \\
 *     a_{21} \\
 *     a_{31}
 *   \end{array} \right)
 * \f$
 */
RMatrix RMatrix::create3x1(double a11, double a21, double a31) {
    RMatrix ret(3, 1);

    ret.set(0, 0, a11);
    ret.set(1, 0, a21);
    ret.set(2, 0, a31);

    return ret;
}

/**
 * \return A matrix with 2 rows and 3 columns:
 * \f$
 *   \left( \begin{array}{ccc}
 *     a_{11} & a_{12} & a_{13} \\
 *     a_{21} & a_{22} & a_{23}
 *   \end{array} \right)
 * \f$
 */
RMatrix RMatrix::create2x3(
    double a11, double a12, double a13,
    double a21, double a22, double a23) {
    RMatrix ret(2, 3);

    ret.set(0, 0, a11);
    ret.set(0, 1, a12);
    ret.set(0, 2, a13);

    ret.set(1, 0, a21);
    ret.set(1, 1, a22);
    ret.set(1, 2, a23);

    return ret;
}

/**
 * Assignment operator.
 */
RMatrix& RMatrix::operator =(const RMatrix& other) {
    if (this == &other) {
        return *this;
    }

    init(other.rows, other.cols);

    for (int rc = 0; rc < rows; ++rc) {
        for (int cc = 0; cc < cols; ++cc) {
            m[rc][cc] = other.m[rc][cc];
        }
    }
    return *this;
}

/**
 * Comparison. All elements of the matrix as well as the matrix
 * dimensions have to match for the two matrices to be equal.
 */
bool RMatrix::operator ==(const RMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        return false;
    }

    for (int rc = 0; rc < rows; ++rc) {
        for (int cc = 0; cc < cols; ++cc) {
            if (m[rc][cc] != other.m[rc][cc]) {
                return false;
            }
        }
    }

    return true;
}

/**
 * Multiplies all elements of this matrix with the given factor
 * and returns this matrix.
 */
RMatrix RMatrix::operator *=(double f) {
    *this = *this * f;
    return *this;
}

/**
 * Multiplies two matrices.
 */
RMatrix RMatrix::operator *(const RMatrix& other) const {
    return multiplyWith(other);
}

/**
 * \return \f$A \cdot W\f$
 * This matrix is not affected.
 */
RMatrix RMatrix::multiplyWith(const RMatrix& w) const {
    RMatrix r(rows, w.cols);

    for (int cc = 0; cc < r.cols; ++cc) {
        for (int rc = 0; rc < r.rows; ++rc) {
            for (int i = 0; i < cols; ++i) {
                r.set(rc, cc, r.get(rc, cc) + get(rc, i) * w.get(i, cc));
            }
        }
    }

    return r;
}

RMatrix RMatrix::multiplyWith(double f) const {
    return *this * f;
}

RVector RMatrix::multiplyWith(const RVector& v) const {
    if (getRows()==2 && getCols()==2) {
        return RVector(
            get(0,0)*v.x + get(0,1)*v.y,
            get(1,0)*v.x + get(1,1)*v.y
        );
    }

    return RVector::invalid;
}

/**
 * Initializes the matrix for the given size and resets
 * all elements to 0.
 */
void RMatrix::init(int r, int c) {
    clear();
    m = new double*[r];
    for (int i = 0; i < r; i++) {
        m[i] = new double[c];
    }
    rows = r;
    cols = c;
    reset();
}

/**
 * Resets all elements to 0.
 */
void RMatrix::reset() {
    for (int rc = 0; rc < rows; ++rc) {
        for (int cc = 0; cc < cols; ++cc) {
            m[rc][cc] = 0.0;
        }
    }
}

/**
 * Deletes the elements of this matrix and resets the matrix size to 0/0.
 */
void RMatrix::clear() {
    if (m == NULL) {
        return;
    }

    for (int rc = 0; rc < rows; ++rc) {
        delete[] m[rc];
        m[rc] = NULL;
    }

    delete[] m;
    m = NULL;
    cols = 0;
    rows = 0;
}

/**
 * Sets the dimension of this matrix to 3x3 and the elements
 * to the given elements.
 */
void RMatrix::set3x3(double a11, double a12, double a13, double a21,
        double a22, double a23, double a31, double a32, double a33) {
    *this = create3x3(a11, a12, a13, a21, a22, a23, a31, a32, a33);
}

/**
 * Sets the dimension of this matrix to 3x1 and the elements
 * to the given elements.
 */
void RMatrix::set3x1(double a11, double a21, double a31) {
    *this = create3x1(a11, a21, a31);
}

/**
 * Sets the dimension of this matrix to 2x3 and the elements
 * to the given elements.
 */
void RMatrix::set2x3(double a11, double a12, double a13, double a21,
        double a22, double a23) {
    *this = create2x3(a11, a12, a13, a21, a22, a23);
}

/**
 * Sets the element at the given row/column to the given value \c v.
 *
 * \param r the row
 *
 * \param c the column
 *
 * \param v the new value at the given row / column position
 */
void RMatrix::set(int r, int c, double v) {
    assert(r<rows);
    assert(c<cols);

    m[r][c] = v;
}

/**
 * \param r the row
 *
 * \param c the column
 *
 * \return The element at the given row/column.
 */
double RMatrix::get(int r, int c) const {
    assert(r<rows);
    assert(c<cols);

    return m[r][c];
}


/**
 * Changes this matrix into its \c ref.
 *
 * \internal
 *
 * \return True on success.
 */
bool RMatrix::ref(int startRow) {
    int pr, pc;

    // row which has elements most left becomes first row
    if ((pr = getPivotRow(startRow)) == -1) {
        return false;
    }
    swapRows(startRow, pr);
    // where is the pivot element in the 1st row?
    if ((pc = getPivotCol(startRow)) == -1) {
        return false;
    }
    multiplyRow(startRow, 1.0 / m[startRow][pc]);

    for (int rc = startRow + 1; rc < rows; ++rc) {
        addRow(rc, -m[rc][pc], startRow);
    }

    if (startRow < rows) {
        ref(startRow + 1);
    }
    return true;
}

/**
 * Changes this matrix into its \c rref.
 *
 * \sa http://en.wikipedia.org/wiki/Rref#Reduced_row_echelon_form
 *
 * \return True on success.
 */
bool RMatrix::rref() {
    bool ret = ref(0);

    for (int rc = 0; rc < rows; ++rc) {
        int i = 1;
        for (int cc = getPivotCol(rc) + 1; cc < cols; ++cc, ++i) {
            if (rc + i < rows && fabs(m[rc + i][cc]) > RMATRIX_TOLERANCE) {
                addRow(rc, -m[rc][cc] / m[rc + i][cc], rc + i);
            }
        }
    }

    return ret;
}

/**
 * Multiplies row \c r with \c factor.
 *
 * \internal
 *
 * \param r the row
 *
 * \param factor the factor to apply to the row
 *
 */
void RMatrix::multiplyRow(int r, double factor) {
    for (int cc = 0; cc < cols; ++cc) {
        m[r][cc] *= factor;
    }
}

/**
 * Adds to row \c r \c factor times row \c r2.
 *
 * \internal
 *
 * \param r the row
 *
 * \param r2 the row 2
 *
 * \param factor The factor to apply to \c r2 before it is added to row \c r.
 */
void RMatrix::addRow(int r, double factor, int r2) {
    for (int cc = 0; cc < cols; ++cc) {
        m[r][cc] += factor * m[r2][cc];
    }
}

/**
 * Swaps the given two rows.
 *
 * \internal
 *
 * \param r1 the row 1
 *
 * \param r2 the row 2
 *
 */
void RMatrix::swapRows(int r1, int r2) {
    if (r1 == r2) {
        return;
    }

    double t;
    for (int cc = 0; cc < cols; ++cc) {
        t = m[r1][cc];
        m[r1][cc] = m[r2][cc];
        m[r2][cc] = t;
    }
}

/**
 * \internal
 *
 * \param startRow the start row
 *
 * \return The pivot row of this matrix, starting with the given row \c startRow.
 */
int RMatrix::getPivotRow(int startRow) {
    for (int cc = 0; cc < cols; ++cc) {
        for (int rc = startRow; rc < rows; ++rc) {
            if (fabs(m[rc][cc]) > RMATRIX_TOLERANCE) {
                return rc;
            }
        }
    }

    return -1;
}

/**
 * \internal
 *
 * \param r the row
 *
 * \return The pivot column of the given matrix row \c r.
 */
int RMatrix::getPivotCol(int r) {
    for (int cc = 0; cc < cols; ++cc) {
        if (fabs(m[r][cc]) > RMATRIX_TOLERANCE) {
            return cc;
        }
    }

    return -1;
}

/**
 * \return The inverse matrix of this matrix \f$A^{-1}\f$ or
 * an empty matrix if this matrix is not invertible.
 */
RMatrix RMatrix::getInverse() const {
    if (cols != rows) {
        return RMatrix();
    }

    RMatrix a = getAppended(createIdentity(cols));
    if (!a.rref()) {
        return RMatrix();
    }

    RMatrix ret(rows, cols);
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            ret.set(r, c, a.get(r, c + cols));
        }
    }

    return ret;
}

/**
 * \return The transposed matrix \f$A^T\f$.
 * This matrix is not affected.
 */
RMatrix RMatrix::getTransposed() const {
    RMatrix t(cols, rows);

    for (int cc = 0; cc < cols; ++cc) {
        for (int rc = 0; rc < rows; ++rc) {
            t.set(cc, rc, m[rc][cc]);
        }
    }

    return t;
}

/**
 * Appends matrix \c v to the right side of this matrix
 * and returns the new matrix. This matrix is not affected.
 *
 * \param v the matrix to append to this matrix
 *
 */
RMatrix RMatrix::getAppended(const RMatrix& v) const {
    if (rows != v.rows) {
        return RMatrix();
    }

    RMatrix r(rows, cols + v.cols);

    for (int rc = 0; rc < rows; ++rc) {
        for (int cc = 0; cc < cols; ++cc) {
            r.set(rc, cc, get(rc, cc));
        }
        for (int cc = cols; cc < cols + v.cols; ++cc) {
            r.set(rc, cc, v.get(rc, cc - cols));
        }
    }

    return r;
}

bool RMatrix::isRotationAndUniformScale() const {
    double a = getRotationAngle();

    if (RMath::isNaN(a)) {
        return false;
    }

    if (fabs(cos(a))<RS::PointTolerance) {
        return RMath::fuzzyCompare(get(0,1) / -sin(a), get(1,0) / sin(a)) &&
               RMath::fuzzyCompare(get(0,0), get(1,1));
    }
    if (fabs(sin(a))<RS::PointTolerance) {
        return RMath::fuzzyCompare(get(0,0) / cos(a), get(1,1) / cos(a)) &&
               RMath::fuzzyCompare(-get(0,1), get(1,0));
    }

    double s00 = get(0,0) / cos(a);
    double s01 = get(0,1) / -sin(a);
    double s10 = get(1,0) / sin(a);
    double s11 = get(1,1) / cos(a);

    return (RMath::fuzzyCompare(s00, s01) &&
        RMath::fuzzyCompare(s00, s10) &&
        RMath::fuzzyCompare(s00, s11));
}

double RMatrix::getUniformScaleFactor() const {
    if (getRows()!=2 || getCols()!=2) {
        return RNANDOUBLE;
    }
    double a = getRotationAngle();
    if (RMath::isNaN(a)) {
        return RNANDOUBLE;
    }
    return get(0,0) / cos(a);
}

double RMatrix::getRotationAngle() const {
    if (getRows()!=2 || getCols()!=2) {
        return RNANDOUBLE;
    }
    return atan2(get(1,0), get(0,0));
}

RMatrix RMatrix::operator *(double s) const {
    RMatrix ret = *this;

    for (int rc = 0; rc < ret.getRows(); ++rc) {
        for (int cc = 0; cc < ret.getCols(); ++cc) {
            ret.set(rc, cc, ret.get(rc, cc) * s);
        }
    }

    return ret;
}

/**
 * \return \f$matrix \cdot factor\f$.
 */
RMatrix operator *(double factor, const RMatrix& matrix) {
    return matrix * factor;
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, const RMatrix& m) {
    dbg.nospace() << "RMatrix(";
    for (int rc = 0; rc < m.getRows(); ++rc) {
        for (int cc = 0; cc < m.getCols(); ++cc) {
            dbg.nospace() << m.get(rc, cc);
            if (rc!=m.getRows()-1 || cc!=m.getCols()-1) {
                dbg.nospace() << ",";
            }
        }
    }
    dbg.nospace() << ")";
    return dbg;
}
