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

#ifndef RMATH_H
#define RMATH_H

#include "../core_global.h"

#include <QMetaType>

#include <cstdio>
#include <cmath>
#include <cerrno>
#include <limits>

#include "RVector.h"

#ifndef M_PI
#define M_PI        3.14159265358979323846264338327950288
#endif

#ifndef M_PI_2
#define M_PI_2      1.57079632679489661923132169163975144
#endif

#ifndef M_PI_4
#define M_PI_4      0.785398163397448309615660845819875721
#endif

#ifndef M_LN10
#define M_LN10      2.30258509299404568401799145468436421
#endif

#ifndef M_LN2
#define M_LN2       0.693147180559945309417232121458176568
#endif



// Somewhere in the guts of Visual C++ a macro 'max' is defined which
// breaks std::numeric_limits<double>::max(). This fix is not correct
// but good enough for now.
#ifdef _MSC_VER
#define RMAXDOUBLE 1e300
#define RMINDOUBLE -1e300
#else
#define RMAXDOUBLE std::numeric_limits<double>::max()
#define RMINDOUBLE -std::numeric_limits<double>::max()
#endif

#define RMAXINT INT_MAX
#define RMININT INT_MIN

#ifndef RNANDOUBLE
#define RNANDOUBLE std::numeric_limits<double>::quiet_NaN()
#endif

#ifndef RINFDOUBLE
#define RINFDOUBLE std::numeric_limits<double>::infinity()
#endif


/**
 * Math functions.
 *
 * \ingroup math
 * \scriptable
 */
class QCADCORE_EXPORT RMath {
public:
    static void init() {
    }

    static void uninit() {
    }

    /**
     * Rounds the given double to the next int.
     */
    static inline int mround(double v) {
#if defined(__GCC2x__) || defined(_MSC_VER)
        return (v-floor(v)<0.5 ? (int)floor(v) : (int)ceil(v));
#else
        return (int) round(v);
#endif
    }

    /**
     * Swaps two given values.
     * \nonscriptable
     */
    template <class T>
    static void swap( T &a, T &b) {
        const T ttmp(a);
        a=b;
        b=ttmp;
    }

    static double trunc(double v);

    static double pow(double x, double y);

    static bool isNormal(double v);
    static bool isNaN(double v);
    static bool isInf(double v);

    static bool isSane(double v);

    static double eval(const QString& expression, bool* ok = NULL);
    static QString getError();
    static bool hasError();
    //static double stringToAngle(const QString& str);
    static QString angleToString(double a);
    static QString trimTrailingZeroes(const QString& s);

    static double rad2deg(double a);
    static double deg2rad(double a);
    static double rad2gra(double a);
    static double gra2deg(double a);

    static bool isBetween(double value, double limit1, double limit2, bool inclusive, double tolerance = RS::PointTolerance);

    static int getGcd(int a, int b);
    static bool isAngleBetween(double a, double a1, double a2, bool reversed);
    static double getNormalizedAngle(double a);
    static double getRelativeAngle(double a, double baseAngle);
    static double getAngleDifference(double a1, double a2);
    static double getAngleDifference180(double a1, double a2);
    static double makeAngleReadable(double angle, bool readable = true, bool* corrected = NULL);
    static bool isAngleReadable(double angle, double tolerance = 0.01);
    static bool isSameDirection(double dir1, double dir2, double tol = RS::AngleTolerance);
    static int absmod(int a, int b);

    static QString toFractionString(double v, int maxDenominator);
    static void toFraction(double v, int maxDenominator, int& number, int& numerator, int& denominator);
    static void simplify(int numerator, int denominator, int& numeratorRes, int& denominatorRes);

    static bool fuzzyCompare(double v1, double v2, double tolerance = RS::PointTolerance);
    static bool fuzzyAngleCompare(double v1, double v2, double tolerance = RS::AngleTolerance);

    static bool containsFuzzy(const QList<double>& values, double v, double tol = RS::PointTolerance);

    static double parseScale(const QString& scaleString);
    static RVector parseCoordinate(const QString& coordinateString, const RVector& relativeZero = RVector::nullVector);

    /**
     * \nonscriptable
     */
    static void getQuadRoots(double p[], double r[][5]);
    /**
     * \nonscriptable
     */
    static void getCubicRoots(double p[], double r[][5]);
    /**
     * \nonscriptable
     */
    static void getBiQuadRoots(double p[], double r[][5]);
private:
    static QString lastError;
    static QString mathExt;
};

Q_DECLARE_METATYPE(RMath*);

#endif
