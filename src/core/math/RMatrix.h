/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

#ifndef RMATRIX_H
#define RMATRIX_H

#include "RMath.h"

#define RMATRIX_TOLERANCE 1.0e-8

/**
 * Simple matrix class.
 *
 * \ingroup math
 * \copyable
 */
class RMatrix {
public:
    RMatrix();
    RMatrix(int r, int c);
    RMatrix(const RMatrix& other);
    ~RMatrix();

    bool isValid() const;

    static RMatrix createIdentity2x2();
    static RMatrix createIdentity3x3();
    static RMatrix createIdentity(int size);
    static RMatrix create3x3(double a11, double a12, double a13, double a21,
            double a22, double a23, double a31, double a32, double a33);
    static RMatrix create3x1(double a11, double a21, double a31);
    static RMatrix create2x3(double a11, double a12, double a13, double a21,
            double a22, double a23);

    RMatrix& operator =(const RMatrix& other);
    bool operator ==(const RMatrix& other) const;
    RMatrix operator *=(double f);
    RMatrix operator *(const RMatrix& other) const;
    RMatrix multiplyWith(const RMatrix& w) const;
    double* operator [](int i);

    void init(int r, int c);
    void reset();
    void clear();

    void set3x3(double a11, double a12, double a13, double a21, double a22,
            double a23, double a31, double a32, double a33);
    void set3x1(double a11, double a21, double a31);
    void set2x3(double a11, double a12, double a13, double a21, double a22,
            double a23);

    void set(int r, int c, double v);
    double get(int r, int c) const;

    /**
     * \return Number of rows of this matrix.
     */
    int getRows() const {
        return rows;
    }
    /**
     * \return Number of columns of this matrix.
     */
    int getCols() const {
        return cols;
    }

    void print() const;
    void printRow(int r) const;

    bool rref();

    RMatrix getInverse() const;
    RMatrix getTransposed() const;
    RMatrix getAppended(const RMatrix& v) const;

protected:
    bool ref(int startRow);
    void multiplyRow(int r, double factor);
    void addRow(int r, double factor, int r2);
    void swapRows(int r1, int r2);
    int getPivotRow(int startRow);
    int getPivotCol(int r);

private:
    double** m;
    int rows, cols;
};

RMatrix operator *(const RMatrix& matrix, double factor);
RMatrix operator *(double factor, const RMatrix& matrix);

Q_DECLARE_METATYPE(RMatrix)
Q_DECLARE_METATYPE(RMatrix*)

#endif
