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
#include <QQuaternion>

#include "RBox.h"
#include "RDebug.h"
#include "RLine.h"
#include "RMath.h"
#include "RMatrix.h"
#include "RPolyline.h"
#include "RVector.h"

const RVector RVector::invalid = RVector(0, 0, 0, false);
const RVector RVector::nullVector = RVector(0, 0, 0, true);

RVector::RVector(double vx, double vy, double vz, bool valid_in) :
    x(vx), y(vy), z(vz) {

    valid = valid_in &&
        RMath::isNormal(x) &&
        RMath::isNormal(y) &&
        RMath::isNormal(z);
}

bool RVector::isValid() const {
    return valid;
}

void RVector::setX(double x) {
    this->x = x;
}

double RVector::getX() {
    return x;
}

void RVector::setY(double y) {
    this->y = y;
}

double RVector::getY() {
    return y;
}

void RVector::setZ(double z) {
    this->z = z;
}

double RVector::getZ() {
    return z;
}


/**
 * Sets a new position for the vector in polar coordinates.
 *
 * \param radius the radius or the distance
 *
 * \param angle the angle in rad
 */
void RVector::setPolar(double radius, double angle) {
    x = radius * cos(angle);
    y = radius * sin(angle);
    z = 0.0;
    valid = RMath::isNormal(radius) && RMath::isNormal(angle);
}

void RVector::setAngle(double a) {
    double m = getMagnitude();
    setPolar(m, a);
}

/**
 * \return The angle from zero to this vector (in rad).
 */
double RVector::getAngle() const {
    double ret = 0.0;
    double m = getMagnitude2d();

    if (m > 1.0e-6) {
        double dp = getDotProduct(*this, RVector(1.0, 0.0));
        if (dp / m >= 1.0) {
            ret = 0.0;
        } else if (dp / m < -1.0) {
            ret = M_PI;
        } else {
            ret = acos(dp / m);
        }
        if (y < 0.0) {
            ret = 2*M_PI - ret;
        }
    }
    return ret;
}

/**
 * \return Angle between this vector and XY plane (horizontal plane).
 */
double RVector::getAngleToPlaneXY() const {
    RVector n(0, 0, 1);

    if (getMagnitude() < 1.0e-4) {
        return M_PI / 2;
    } else if ((getDotProduct(*this, n) / (getMagnitude() * 1)) > 1.0) {
        return 0.0;
    } else {
        return M_PI / 2 - acos(getDotProduct(*this, n) / (getMagnitude() * 1));
    }
}

/**
 * \return The angle from this and the given coordinate (in rad).
 */
double RVector::getAngleTo(const RVector& v) const {
    if (!valid || !v.valid) {
        return RNANDOUBLE;
    } else {
        return (v - (*this)).getAngle();
    }
}

/**
 * Sets the vector magnitude without chaning the direction.
 */
void RVector::setMagnitude2d(double m) {
    double a = getAngle();
    setPolar(m, a);
}

/**
 * \return Magnitude (length) of the vector.
 */
double RVector::getMagnitude() const {
    if (!valid) {
        return RNANDOUBLE;
    }
    // Note that the z coordinate is also needed for 2d
    //   (due to definition of crossP())
    return sqrt(RMath::pow(x, 2) + RMath::pow(y, 2) + RMath::pow(z, 2));
}

/**
 * \return Magnitude (length) of the vector projected to the x/y plane (2d).
 */
double RVector::getMagnitude2d() const {
    if (!valid) {
        return RNANDOUBLE;
    }
    return sqrt(RMath::pow(x, 2) + RMath::pow(y, 2));
}

/**
 * \return Square of magnitude (length).
 */
double RVector::getSquaredMagnitude() const {
    if (!valid) {
        return RNANDOUBLE;
    }

    return RMath::pow(x, 2) + RMath::pow(y, 2) + RMath::pow(z, 2);
}

/**
 * Linear interpolation between this and \c v by fraction 't'.
 */
RVector RVector::getLerp(const RVector& v, double t) const {
    return RVector(x + (v.x - x) * t, y + (v.y - y) * t, z + (v.z - z) * t);
}

/**
 * \return Unit vector for this vector.
 */
RVector RVector::getUnitVector() const {
    return *this / getMagnitude();
}

/**
 * \return True if this vector is inside the given box, false otherwise.
 */
bool RVector::isInside(const RBox& b) const {
    RVector bMin = b.getMinimum();
    RVector bMax = b.getMaximum();

    return (x >= bMin.x && x <= bMax.x && y >= bMin.y && y <= bMax.y && z
            >= bMin.z && z <= bMax.z);
}

/**
 * \return True if this vector and the given vector are almost equal
 * (see RS::PointTolerance).
 *
 * \param tol Tolerance in X, Y and Z.
 */
bool RVector::equalsFuzzy(const RVector& v, double tol) const {
    return (qAbs(x-v.x)<tol &&
            qAbs(y-v.y)<tol &&
            qAbs(z-v.z)<tol);
}

/**
 * \return The distance between this and the given coordinate.
 */
double RVector::getDistanceTo(const RVector& v) const {
    if (!valid || !v.valid) {
        return RMAXDOUBLE;
    } else {
        return (*this - v).getMagnitude();
    }
}

/**
 * \return The distance between this and the given coordinate on the XY plane.
 */
double RVector::getDistanceTo2d(const RVector& v) const {
    if (!valid || !v.valid) {
        return RMAXDOUBLE;
    } else {
        return (*this - v).getMagnitude2d();
    }
}

/**
 * \return true if this vector is within the given range (2d).
 */
bool RVector::isInWindow(const RVector& firstCorner,
        const RVector& secondCorner) {

    double minX = qMin(firstCorner.x, secondCorner.x);
    double maxX = qMax(firstCorner.x, secondCorner.x);
    double minY = qMin(firstCorner.y, secondCorner.y);
    double maxY = qMax(firstCorner.y, secondCorner.y);

    return (x >= minX && x <= maxX && y >= minY && y <= maxY);
}

/**
 * Moves this vector by the given offset. Equal to the operator +=.
 */
RVector RVector::move(const RVector& offset) {
    *this += offset;
    return *this;
}

void RVector::moveList(QList<RVector>& list, const RVector& offset) {
    for (int i=0; i<list.length(); i++) {
        list[i].move(offset);
    }
}

/**
 * Rotates this vector around 0/0 by the given angle.
 */
RVector RVector::rotate(double rotation) {
    if (!valid) {
        return *this;
    }

    double r = getMagnitude2d();
    double a = getAngle() + rotation;

    x = cos(a) * r;
    y = sin(a) * r;

    return *this;
}

/**
 * Rotates this vector around the given center by the given angle.
 */
RVector RVector::rotate(double rotation, const RVector& center) {
    *this = center + (*this - center).rotate(rotation);
    return *this;
}

RVector RVector::rotate3d(const RLine& axis, double rotation) {
    RVector off = -axis.getStartPoint();
    RVector ret = *this;
    ret.move(off);
    RVector ax = axis.getStartPoint() - axis.getEndPoint();
    QQuaternion quat = QQuaternion::fromAxisAndAngle(ax.x, ax.y, ax.z, RMath::rad2deg(rotation));
    QVector3D qv = quat.rotatedVector(QVector3D(ret.x, ret.y, ret.z));
    ret = RVector(qv.x(), qv.y(), qv.z());
    ret.move(-off);
    *this = ret;
    return *this;
}

RVector RVector::rotate3d(const QQuaternion& quaternion) {
    QVector3D qv = quaternion.rotatedVector(QVector3D(x, y, z));
    *this = RVector(qv.x(), qv.y(), qv.z());
    return *this;
}

void RVector::rotateList(QList<RVector>& list, double rotation) {
    for (int i=0; i<list.length(); i++) {
        list[i].rotate(rotation);
    }
}

void RVector::rotateList(QList<RVector>& list, double rotation, const RVector& center) {
    for (int i=0; i<list.length(); i++) {
        list[i].rotate(rotation, center);
    }
}

/**
 * Scales this vector by the given factor with the given center.
 */
RVector RVector::scale(double factor, const RVector& center) {
    return scale(RVector(factor, factor, factor), center);
}

/**
 * Scales this vector by the given factors with the given center.
 */
RVector RVector::scale(const RVector& factors, const RVector& center) {
    if (center==RVector()) {
        x *= factors.x;
        y *= factors.y;
        z *= factors.z;
        return *this;
    }

    *this = center + (*this - center).scale(factors);
    return *this;
}

void RVector::scaleList(QList<RVector>& list, double factor, const RVector& center) {
    for (int i=0; i<list.length(); i++) {
        list[i].scale(factor, center);
    }
}

void RVector::scaleList(QList<RVector>& list, const RVector& factors, const RVector& center) {
    for (int i=0; i<list.length(); i++) {
        list[i].scale(factors, center);
    }
}

/**
 * Mirrors this vector at the given axis.
 */
RVector RVector::mirror(const RLine& axis) {
    double phi1 = axis.startPoint.getAngleTo(*this);
    double phi2 = axis.startPoint.getAngleTo(axis.endPoint) - phi1;
    double r1 = axis.startPoint.getDistanceTo(*this);
    double r2 = axis.endPoint.getDistanceTo(*this);

    if (r1 < 1.0e-6 || r2 < 1.0e-6) {
        // point touches one axis point
    } else {
        setPolar(r1, phi1 + 2* phi2 );
        (*this) += axis.startPoint;
    }

    return *this;
}

RVector RVector::mirror(const RVector& axis1, const RVector& axis2) {
   return mirror(RLine(axis1, axis2));
}

/**
 * Mirrors this vector at the Y-axis.
 */
RVector RVector::flipHorizontal() {
    return mirror(RVector(0,0,0), RVector(0,1,0));
}

/**
 * Mirrors this vector at the X-axis.
 */
RVector RVector::flipVertical() {
    return mirror(RVector(0,0,0), RVector(1,0,0));
}

/**
 * Moves this vector by offset if it is inside the given area.
 */
RVector RVector::stretch(const RPolyline& area, const RVector& offset) {
    if (area.contains(*this)) {
        return move(offset);
    }
    return *this;
}

/**
 * Changes this vector into its isometric projection.
 * \todo refactor
 */
RVector RVector::isoProject(RS::IsoProjectionType type, bool trueScale) {
    static RMatrix iso =
            RMatrix::create3x3(
                sqrt(3.0), 0.0, -sqrt(3.0),
                1.0, 2.0, 1.0,
                sqrt(2.0), -sqrt(2.0), sqrt(2.0))
            * (1.0 / sqrt(6.0));

    RMatrix input;
    switch (type) {
    case RS::IsoRight:
        input = RMatrix::create3x1(x, y, -z);
        break;
    case RS::IsoRightBack:
        input = RMatrix::create3x1(-x, y, z);
        break;
    case RS::IsoTop:
        //input = RMatrix::create3x1(y, 0.0, -x);
        input = RMatrix::create3x1(y, z, -x);
        break;
    case RS::IsoBottom:
        input = RMatrix::create3x1(y, z, x);
        break;
    case RS::IsoLeft:
        input = RMatrix::create3x1(z, y, -x);
        break;
    case RS::IsoLeftBack:
        input = RMatrix::create3x1(z, y, x);
        break;
    }

    RMatrix res = iso * input;

    x = res.get(0, 0);
    y = res.get(1, 0);
    z = 0.0;

    if (trueScale) {
        double f = 1.0 / cos(RMath::deg2rad(35.0 + 16.0/60.0));
//        double f = 1.22477928993;
        x *= f;
        y *= f;
    }

    return *this;
}

/**
 * binary + operator.
 */
RVector RVector::operator +(const RVector& v) const {
    return RVector(x + v.x, y + v.y, z + v.z, valid && v.valid);
}

/**
 * binary - operator.
 */
RVector RVector::operator -(const RVector& v) const {
    return RVector(x - v.x, y - v.y, z - v.z, valid && v.valid);
}

/**
 * binary * operator.
 */
RVector RVector::operator *(double s) const {
    return RVector(x * s, y * s, z * s, valid);
}

/**
 * binary / operator.
 */
RVector RVector::operator /(double s) const {
    return RVector(x / s, y / s, z / s, valid);
}

/**
 * unary - operator.
 */
RVector RVector::operator -() const {
    return getNegated();
}

/**
 * \return New vector with negated components.
 */
RVector RVector::getNegated() const {
    return RVector(-x, -y, -z, valid);
}

/**
 * Normalizes this vector and returns a reference to this vector.
 */
RVector RVector::normalize() {
    *this = getNormalized();
    return *this;
}

/**
 * \return A new unit vector with the same direction as this vector.
 */
RVector RVector::getNormalized() const {
    double l = getMagnitude();
    if (l<RS::PointTolerance) {
        return RVector::invalid;
    }
    return *this / l;
}

/**
 * Scalarproduct (dot product).
 */
double RVector::getDotProduct(const RVector& v1, const RVector& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/**
 * += operator. The result is only valid if both vectors are valid.
 */
void RVector::operator +=(const RVector& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    valid = valid && v.valid;
}

/**
 * -= operator. The result is only valid if both vectors are valid.
 */
void RVector::operator -=(const RVector& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    valid = valid && v.valid;
}

/**
 * *= operator
 */
void RVector::operator *=(double s) {
    x *= s;
    y *= s;
    z *= s;
}

/**
 * /= operator
 */
void RVector::operator /=(double s) {
    x /= s;
    y /= s;
    z /= s;
}

/**
 * == operator
 */
bool RVector::operator ==(const RVector& v) const {
    if (valid == true && v.valid == true) {
        return x == v.x && y == v.y && z == v.z;
    } else if (valid == false && v.valid == false) {
        return true;
    }
    return false;
}

/**
 * \return A vector with the minimum components from the given vectors.
 * These might be mixed components from all vectors.
 */
RVector RVector::getMinimum(const QList<RVector>& vectors) {
    if (vectors.size() == 0) {
        return RVector();
    }

    RVector ret = vectors[0];

    QList<RVector>::const_iterator it = vectors.begin();
    it++;
    for (; it != vectors.end(); it++) {
        ret = getMinimum(ret, *it);
    }

    return ret;
}

/**
 * \return A vector with the maximum components from the given vectors.
 * These might be mixed components from all vectors.
 */
RVector RVector::getMaximum(const QList<RVector>& vectors) {
    if (vectors.size() == 0) {
        return RVector();
    }

    RVector ret = vectors[0];

    QList<RVector>::const_iterator it = vectors.begin();
    it++;
    for (; it != vectors.end(); it++) {
        ret = getMaximum(ret, *it);
    }

    return ret;
}

/**
 * \return A vector with the minimum components from the vectors v1 and v2.
 * These might be mixed components from both vectors.
 */
RVector RVector::getMinimum(const RVector& v1, const RVector& v2) {
    return RVector(qMin(v1.x, v2.x), qMin(v1.y, v2.y), qMin(v1.z, v2.z), v1.valid && v2.valid);
}

/**
 * \return A vector with the maximum values from the vectors v1 and v2
 */
RVector RVector::getMaximum(const RVector& v1, const RVector& v2) {
    return RVector(qMax(v1.x, v2.x), qMax(v1.y, v2.y), qMax(v1.z, v2.z), v1.valid && v2.valid);
}

/**
 * Convenience function.
 * \return (v1 + v2) / 2.0
 */
RVector RVector::getAverage(const RVector& v1, const RVector& v2) {
    return (v1+v2)/2.0;
}

/**
 * \return All X values of the given list of vectors as a new list.
 */
QList<double> RVector::getXList(const QList<RVector>& vectors) {
    QList<double> ret;
    QList<RVector>::const_iterator it;
    for (it=vectors.constBegin(); it!=vectors.constEnd(); ++it) {
         ret.append((*it).x);
    }
    return ret;
}

/**
 * \return All Y values of the given list of vectors as a new list.
 */
QList<double> RVector::getYList(const QList<RVector>& vectors) {
    QList<double> ret;
    QList<RVector>::const_iterator it;
    for (it=vectors.constBegin(); it!=vectors.constEnd(); ++it) {
        ret.append((*it).y);
    }
    return ret;
}

/**
 * \return All Z values of the given list of vectors as a new list.
 */
QList<double> RVector::getZList(const QList<RVector>& vectors) {
    QList<double> ret;
    QList<RVector>::const_iterator it;
    for (it=vectors.constBegin(); it!=vectors.constEnd(); ++it) {
        ret.append((*it).z);
    }
    return ret;
}

/**
 * \return Vector with all components floored to the next lower integer.
 */
RVector RVector::getFloor() const {
    return RVector(floorl(x), floorl(y), floorl(z), valid);
}

/**
 * \return Vector with all components ceiled to the next higher integer.
 */
RVector RVector::getCeil() const {
    return RVector(ceill(x), ceill(y), ceill(z), valid);
}

/**
 * \return Cross product of two vectors.
 */
RVector RVector::getCrossProduct(const RVector& v1, const RVector& v2) {
    return RVector(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x
            * v2.y - v1.y * v2.x, v1.valid && v2.valid);
}

/**
 * Generic 3d transformation. \c m must be a 3x3 matrix.
 */
RVector RVector::transform(const RMatrix& m) {
    RMatrix input;

    input = RMatrix::create3x1(x, y, z);
    RMatrix res = m * input;
    x = res.get(0, 0);
    y = res.get(1, 0);
    z = res.get(2, 0);

    return *this;
}

/**
 * \return A new vector which is the result of this vector transformed by
 * the given matrix.
 */
RVector RVector::getTransformed(const RMatrix& m) const {
    RVector ret = *this;
    return ret.transform(m);
}

/**
 * Generic 2d transformation. \c m must be a 3x2 matrix.
 */
RVector RVector::transform2d(const RMatrix& m) {
    RMatrix input;

    input = RMatrix::create3x1(x, y, z);
    RMatrix res = m * input;
    x = res.get(0, 0);
    y = res.get(1, 0);
    z = 0.0;

    return *this;
}

/**
 * \return A new vector which is the result of this vector transformed by
 * the given matrix.
 */
RVector RVector::getTransformed2d(const RMatrix& m) const {
    RVector ret = *this;
    return ret.transform2d(m);
}

/**
 * Transforms this vector with the given transformation matrix.
 */
RVector RVector::transform2d(const QTransform& t) {
    QPointF p(x, y);
    p = t.map(p);
    x = p.x();
    y = p.y();
    return *this;
}

/**
 * \return A new vector with all components divided by the components
 *      given in vector \c v.
 *      Note that the division of two vectors is not defined. This is
 *      merely a helper function that does what it does.
 *
 * \todo refactor
 */
RVector RVector::getDividedComponents(const RVector& v) const {
    return RVector(x / v.x, y / v.y, z / v.z, valid);
}

/**
 * \return A new vector with all components multiplied by the components
 *      given in vector \c v.
 *      Note that the multiplication of two vectors is not defined. This is
 *      merely a helper function that does what it does.
 *
 * \todo refactor
 */
RVector RVector::getMultipliedComponents(const RVector& v) const {
    return RVector(x * v.x, y * v.y, z * v.z, valid);
}

/**
 * \return The vector in the given vectors that is closest to this vector
 *      or an invalid vector if the given vector does not contain any
 *      (valid) vectors.
 */
RVector RVector::getClosest(const QList<RVector>& list) const {
    int index = getClosestIndex(list);
    if (index==-1) {
        return RVector::invalid;
    }
    return list[index];
}

double RVector::getClosestDistance(const QList<RVector>& list, int counts) {
    double ret=RMAXDOUBLE;
    int i=list.count();
    if (counts<i) {
        i=counts;
    }
    if (i<1) {
        return ret;
    }
    for (int j=0; j<i; j++) {
        double d = getDistanceTo(list[j]);
        if (d<ret) {
            ret=d;
        }
    }
    return ret;
}

int RVector::getClosestIndex(const QList<RVector>& list) const {
    double minDist = RMAXDOUBLE;
    int index = -1;

    for (int i = 0; i<list.size(); ++i) {
        if (list[i].valid) {
            double dist = getDistanceTo(list[i]);
            if (dist < minDist) {
                minDist = dist;
                index = i;
            }
        }
    }

    return index;
}


/**
 * Multiplication operator
 */
RVector operator*(double s, const RVector& v) {
    return v * s;
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, const RVector& v) {
    if (v.valid) {
        dbg.nospace() << "RVector(" << v.x << ", " << v.y << ", " << v.z << ")";
    } else {
        dbg.nospace() << "RVector(invalid)";
    }
    return dbg.space();
}

/**
 * Serializes the given RVector object. Used for RSettings, keep in sync
 * with operator>>.
 */
QDataStream& operator<<(QDataStream& stream, const RVector& vector) {
    stream << vector.x;
    stream << vector.y;
    stream << vector.z;
    stream << vector.valid;
    return stream;
}

/**
 * Deserializes the given RColor object.
 */
QDataStream& operator>>(QDataStream& stream, RVector& vector) {
    stream >> vector.x;
    stream >> vector.y;
    stream >> vector.z;
    stream >> vector.valid;
    return stream;
}
