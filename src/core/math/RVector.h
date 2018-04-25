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

#ifndef RVECTOR_H
#define RVECTOR_H

#include "../core_global.h"

#include <QDebug>
#include <QList>
#include <QMetaType>
#include <QTransform>

#include "RGlobal.h"

class RMatrix;
class RBox;
class RLine;
class RPolyline;

#define RDEFAULT_RVECTOR RVector()

/**
 * Represents a 3d vector (x/y/z).
 *
 * \ingroup math
 * \scriptable
 * \copyable
 */
class QCADCORE_EXPORT RVector {
public:
    /**
     * Constructor for a valid null vector (0/0/0).
     */
    inline RVector() :
        x(0.0), y(0.0), z(0.0), valid(true) {
    }

    /**
     * Constructor for a point with given valid flag.
     *
     * \param v true: a valid vector with default coordinates is created.
     *              false: an invalid vector is created
     */
    //  inline explicit RVector(bool v) :
    //      x(0.0), y(0.0), z(0.0), valid(v) {
    //  }

    /**
     * Constructor for a point with given coordinates.
     */
    RVector(double vx, double vy, double vz = 0.0, bool valid_in = true);

    RVector(const QList<double>& tuples);

    /**
     * Sets new values for the vector and makes the vector valid.
     */
    inline void set(double vx, double vy, double vz = 0.0) {
        x = vx;
        y = vy;
        z = vz;
        valid = true;
    }
    void setPolar(double radius, double angle);

    RVector get2D() const {
        return RVector(x,y);
    }

    bool isValid() const;
    bool isZero() const;
    bool isSane() const;
    bool isNaN() const;

    bool isInside(const RBox& b) const;

    bool equalsFuzzy(const RVector& v, double tol = RS::PointTolerance) const;
    bool equalsFuzzy2D(const RVector& v, double tol = RS::PointTolerance) const;
    double getDistanceTo(const RVector& v) const;
    double getDistanceTo2D(const RVector& v) const;
    void setAngle(double a);
    double getAngle() const;
    double getAngleToPlaneXY() const;
    double getAngleTo(const RVector& v) const;
    void setMagnitude2D(double m);
    double getMagnitude() const;
    double getSquaredMagnitude() const;
    double getMagnitude2D() const;
    RVector getLerp(const RVector& v, double t) const;
    RVector getUnitVector() const;
    void setX(double x);
    double getX();
    void setY(double y);
    double getY();
    void setZ(double z);
    double getZ();

    bool isInWindow(const RVector& firstCorner, const RVector& secondCorner);

    RVector move(const RVector& offset);

    /**
     * \nonscriptable
     */
    static void moveList(QList<RVector>& list, const RVector& offset);

    RVector rotate(double rotation);
    RVector rotate(double rotation, const RVector& center);
    RVector getRotated(double rotation, const RVector& center) const;
    RVector rotate3D(const RLine& axis, double rotation);
    RVector rotate3D(const QQuaternion& quaternion);

    /**
     * \nonscriptable
     */
    static void rotateList(QList<RVector>& list, double rotation);

    /**
     * \nonscriptable
     */
    static void rotateList(QList<RVector>& list, double rotation, const RVector& center);

    RVector scale(double factor, const RVector& center=nullVector);
    RVector scale(const RVector& factors, const RVector& center=nullVector);
    RVector getScaled(const RVector& factors, const RVector& center) const;

    /**
     * \nonscriptable
     */
    static void scaleList(QList<RVector>& list, double factor, const RVector& center=nullVector);

    /**
     * \nonscriptable
     */
    static void scaleList(QList<RVector>& list, const RVector& factors, const RVector& center=nullVector);

    RVector mirror(const RLine& axis);
    RVector getMirrored(const RLine& axis) const;
    RVector mirror(const RVector& axis1, const RVector& axis2);
    RVector flipHorizontal();
    RVector flipVertical();
    RVector stretch(const RPolyline& area, const RVector& offset);
    RVector isoProject(RS::IsoProjectionType type);
    RVector axonometricProjection(RS::IsoProjectionType type);
    RVector obliqueProjection(RS::IsoProjectionType type);
    RVector transform(const RMatrix& m);
    RVector transform2DM(const RMatrix& m);
    RVector transform2D(const QTransform& t);

    RVector getTransformed(const RMatrix& m) const;
    RVector getTransformed2DM(const RMatrix& m) const;
    RVector getTransformed2D(const QTransform& t) const;

    RVector getDividedComponents(const RVector& v) const;
    RVector getMultipliedComponents(const RVector& v) const;

    RVector getClosest(const QList<RVector>& list) const;
    RVector getClosest2D(const QList<RVector>& list) const;
    double getClosestDistance(const QList<RVector>& list, int counts);
    int getClosestIndex(const QList<RVector>& list, bool ignoreZ = false) const;
    int getClosestIndex2D(const QList<RVector>& list) const {
        return getClosestIndex(list, true);
    }

    RVector operator +(const RVector& v) const;
    RVector operator -(const RVector& v) const;
    RVector operator *(double s) const;
    RVector operator /(double s) const;
    RVector operator -() const;
    RVector getNegated() const;
    RVector getAbsolute() const;

    double dot(const RVector& other) const {
        return RVector::getDotProduct(*this, other);
    }

    RVector normalize();
    RVector getNormalized() const;

    void operator +=(const RVector& v);
    void operator -=(const RVector& v);
    void operator *=(double s);
    void operator /=(double s);

    bool operator ==(const RVector& v) const;
    bool operator !=(const RVector& v) const {
        return !operator==(v);
    }

    RVector getFloor() const;
    RVector getCeil() const;

    bool lteXY(const RVector& v) const {
        return RVector::lessThanEqualXY(*this, v);
    }
    bool gteXY(const RVector& v) const {
        return RVector::greaterThanEqualXY(*this, v);
    }

    static bool containsFuzzy(const QList<RVector>& vectors, const RVector& v, double tol = RS::PointTolerance);
    static int findFirstFuzzy(const QList<RVector>& vectors, const RVector& v, double tol = RS::PointTolerance);

    static RVector getMinimum(const QList<RVector>& vectors);
    static RVector getMaximum(const QList<RVector>& vectors);

    static RVector getMinimumX(const QList<RVector>& vectors);
    static RVector getMaximumX(const QList<RVector>& vectors);
    static RVector getMinimumY(const QList<RVector>& vectors);
    static RVector getMaximumY(const QList<RVector>& vectors);

    static RVector getMinimum(const RVector& v1, const RVector& v2);
    static RVector getMaximum(const RVector& v1, const RVector& v2);

    static RVector getAverage(const RVector& v1, const RVector& v2);
    static RVector getAverage(const QList<RVector>& vectors);

    static QList<RVector> getUnion(const QList<RVector>& vectorsA, const QList<RVector>& vectorsB, double tol = RS::PointTolerance);
    static QList<RVector> getUnique(const QList<RVector>& vectors, double tol = RS::PointTolerance);

    static QList<double> getXList(const QList<RVector>& vectors);
    static QList<double> getYList(const QList<RVector>& vectors);
    static QList<double> getZList(const QList<RVector>& vectors);

    static RVector getCrossProduct(const RVector& v1, const RVector& v2);
    static double getDotProduct(const RVector& v1, const RVector& v2);
    static RVector createPolar(double radius, double angle) {
        RVector ret;
        ret.setPolar(radius, angle);
        return ret;
    }

    static bool lessThanX(const RVector& v1, const RVector& v2) {
        return v1.x < v2.x;
    }

    static bool greaterThanX(const RVector& v1, const RVector& v2) {
        return v1.x > v2.x;
    }

    static bool lessThanY(const RVector& v1, const RVector& v2) {
        return v1.y < v2.y;
    }

    static bool greaterThanY(const RVector& v1, const RVector& v2) {
        return v1.y > v2.y;
    }

    static bool lessThanEqualXY(const RVector& v1, const RVector& v2) {
        return v1.x <= v2.x && v2.y <= v2.y;
    }

    static bool greaterThanEqualXY(const RVector& v1, const RVector& v2) {
        return v1.x >= v2.x && v2.y >= v2.y;
    }


    static QList<RVector> getSortedByDistance(const QList<RVector>& list, const RVector& v);
    class RVectorDistanceSort {
    public:
        static bool lessThan(const RVector& v1, const RVector& v2);
        static RVector v;
    };

    static QList<RVector> getSortedLeftRightTopBottom(const QList<RVector>& list);
    class RVectorLeftRightTopBottomSort {
    public:
        static bool lessThan(const RVector& v1, const RVector& v2);
    };

    static QList<RVector> getSortedByAngle(const QList<RVector>& list, const RVector& center, double angle);
    class RVectorAngleSort {
    public:
        static bool lessThan(const RVector& v1, const RVector& v2);
        static RVector center;
        static double angle;
    };

public:
    /**
     * \getter{getX}
     * \setter{setX}
     */
    double x;

    /**
     * \getter{getY}
     * \setter{setY}
     */
    double y;

    /**
     * \getter{getZ}
     * \setter{setZ}
     */
    double z;

    /**
     * \getter{isValid}
     */
    bool valid;

    /**
     * invalid vector
     */
    static const RVector invalid;

    /**
     * null vector
     */
    static const RVector nullVector;

    /**
     * NaN vector
     */
    static const RVector nanVector;
};

QCADCORE_EXPORT RVector operator*(double s, const RVector& v);

QCADCORE_EXPORT QDebug operator<<(QDebug dbg, const RVector& v);

/**
 *\nonscriptable
 */
QCADCORE_EXPORT QDataStream& operator<<(QDataStream& stream, const RVector& vector);

/**
 *\nonscriptable
 */
QCADCORE_EXPORT QDataStream& operator>>(QDataStream& stream, RVector& vector);


Q_DECLARE_METATYPE(QList<RVector>)
Q_DECLARE_METATYPE(QList<RVector>*)
typedef QMultiMap<int, RVector> _RMapIntVector;
Q_DECLARE_METATYPE(_RMapIntVector*)
Q_DECLARE_METATYPE(RVector)
Q_DECLARE_METATYPE(RVector*)
Q_DECLARE_METATYPE(const RVector*)

#endif
