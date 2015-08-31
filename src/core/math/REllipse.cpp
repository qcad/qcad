/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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
#include <cmath>

#include "REllipse.h"
#include "RBox.h"
#include "RMath.h"

/**
 * Creates an ellipse shape with invalid
 */
REllipse::REllipse() :
    center(RVector::invalid),
    majorPoint(RVector::invalid),
    ratio(0.0),
    startParam(0.0),
    endParam(0.0),
    reversed(false) {
}

REllipse::REllipse(const RVector& center, const RVector& majorPoint,
                   double ratio,
                   double startParam, double endParam, bool reversed) :
    center(center),
    majorPoint(majorPoint),
    ratio(ratio),
    startParam(startParam),
    endParam(endParam),
    reversed(reversed) {

    correctMajorMinor();
}

REllipse::~REllipse() {
}

bool REllipse::isValid() {
    return center.isValid();
}

QList<RVector> REllipse::getFoci() const {
    RVector vp(getMajorPoint() * sqrt(1.0 - getRatio()*getRatio()));
    return QList<RVector>() << getCenter()+vp << getCenter()-vp;
}

void REllipse::to2D() {
    center.z = 0.0;
    majorPoint.z = 0.0;
}

void REllipse::moveStartPoint(const RVector& pos, bool changeAngleOnly) {
    if (changeAngleOnly) {
        startParam = getParamTo(pos);
    }
    else {
        RVector ep = getEndPoint();
        double distOri = ep.getDistanceTo(getStartPoint());
        double angleOri = ep.getAngleTo(getStartPoint());
        if (distOri<RS::PointTolerance) {
            return;
        }

        double distNew = ep.getDistanceTo(pos);
        double angleNew = ep.getAngleTo(pos);
        double factor = distNew / distOri;
        if (factor<RS::PointTolerance) {
            return;
        }
        double angleDelta = angleNew - angleOri;

        center.scale(factor, ep);
        center.rotate(angleDelta, ep);
        majorPoint.scale(factor);
        majorPoint.rotate(angleDelta);
    }
}

void REllipse::moveEndPoint(const RVector& pos, bool changeAngleOnly) {
    if (changeAngleOnly) {
        endParam = getParamTo(pos);
    }
    else {
        RVector sp = getStartPoint();
        double distOri = sp.getDistanceTo(getEndPoint());
        double angleOri = sp.getAngleTo(getEndPoint());
        if (distOri<RS::PointTolerance) {
            return;
        }

        double distNew = sp.getDistanceTo(pos);
        double angleNew = sp.getAngleTo(pos);
        double factor = distNew / distOri;
        if (factor<RS::PointTolerance) {
            return;
        }
        double angleDelta = angleNew - angleOri;

        center.scale(factor, sp);
        center.rotate(angleDelta, sp);
        majorPoint.scale(factor);
        majorPoint.rotate(angleDelta);
    }
}

// previously: getEllipseAngle
double REllipse::getParamTo(const RVector& pos) const {
    RVector m = pos;
    m.rotate(-majorPoint.getAngle(), center);
    RVector v = m-center;
    v.scale(RVector(1.0, 1.0/ratio));
    return v.getAngle();
}

/**
 * \return Radius of ellipse at given ellipse angle.
 */
double REllipse::getRadiusAt(double angle) const {
    RVector v(cos(angle)*getMajorRadius(),
              sin(angle)*getMinorRadius());
    return v.getMagnitude();
}

/**
 * \return Point on ellipse at given ellipse angle.
 */
RVector REllipse::getPointAt(double angle) const {
    RVector v(cos(angle)*getMajorRadius(),
              sin(angle)*getMinorRadius());
    v.rotate(getAngle());
    v.move(center);
    return v;
}

RVector REllipse::getMiddlePoint() const {
    double a;
    a = getStartParam() + getSweep()/2.0;
    return getPointAt(a);
}

RVector REllipse::getCenter() const{
    return center;
}

void REllipse::setCenter(const RVector& vector) {
    center = vector;
}

/**
 * \return Major point relative to the center point.
 */
RVector REllipse::getMajorPoint() const{
    return majorPoint;
}

/**
 * Sets the major point relative to the center point.
 */
void REllipse::setMajorPoint(const RVector& p) {
    majorPoint = p;
    correctMajorMinor();
}

/**
 * \return Minor point relative to the center point.
 */
RVector REllipse::getMinorPoint() const{
    double angle = RMath::getNormalizedAngle(getAngle() + M_PI/2.0);
    RVector ret;
    ret.setPolar(getMinorRadius(), angle);
    return ret;
}

/**
 * Sets the minor point relative to the center point.
 */
void REllipse::setMinorPoint(const RVector& p) {
    double angle = RMath::getNormalizedAngle(p.getAngle() - M_PI/2.0);
    majorPoint.setPolar(getMajorRadius(), angle);
    setRatio(p.getMagnitude() / getMajorRadius());
}

bool REllipse::switchMajorMinor() {
    if (fabs(ratio) < RS::PointTolerance) {
        return false;
    }
    RVector vp_start=getStartPoint();
    RVector vp_end=getStartPoint();
    RVector vp=getMajorPoint();
    setMajorPoint(RVector(-ratio*vp.y, ratio*vp.x));
    setRatio(1.0/ratio);
    setStartParam(getParamTo(vp_start));
    setEndParam(getParamTo(vp_end));
    return true;
}

double REllipse::getRatio() const{
    return ratio;
}

void REllipse::setRatio(double r) {
    ratio = r;
    correctMajorMinor();
}

double REllipse::getStartParam() const {
    return startParam;
}

void REllipse::setStartParam(double a) {
    startParam = a;
}

double REllipse::getEndParam() const {
    return endParam;
}

void REllipse::setEndParam(double a) {
    endParam = a;
}

double REllipse::getStartAngle() const {
    return RMath::getNormalizedAngle(center.getAngleTo(getStartPoint()) - getAngle());
}

void REllipse::setStartAngle(double a) {
    double p = angleToParam(a);
    if (RMath::isNaN(p)) {
        return;
    }
    startParam = p;
}

double REllipse::getEndAngle() const {
    return RMath::getNormalizedAngle(center.getAngleTo(getEndPoint()) - getAngle());
}

void REllipse::setEndAngle(double a) {
    double p = angleToParam(a);
    if (RMath::isNaN(p)) {
        return;
    }
    endParam = p;
}

double REllipse::angleToParam(double a) const {
    double p;
    if (fabs(a - 2*M_PI)<RS::AngleTolerance) {
        p = 2*M_PI;
    }
    else if (fabs(a)<RS::AngleTolerance) {
        p = 0.0;
    }
    else {
        REllipse normEllipse = *this;
        normEllipse.move(-center);
        normEllipse.rotate(-getAngle());
        normEllipse.setStartParam(0.0);
        normEllipse.setEndParam(2*M_PI);

        RLine line(RVector(0,0), RVector::createPolar(getMajorRadius()*2, a));
        QList<RVector> r = RShape::getIntersectionPoints(line, normEllipse, true);
        if (r.length()!=1) {
            return RNANDOUBLE;
        }

        p = acos(r[0].x / getMajorRadius());
    }

    if (RMath::getNormalizedAngle(a) > M_PI) {
        p = 2*M_PI-p;
    }

    return p;
}

/**
 * \return Angle length in rad.
 */
double REllipse::getAngleLength(bool allowForZeroLength) const {
    double ret = 0.0;

    if (isReversed()) {
        if (startParam<endParam) {
            ret = startParam+2*M_PI-endParam;
        } else {
            ret = startParam-endParam;
        }
    } else {
        if (endParam<startParam) {
            ret = endParam+2*M_PI-startParam;
        } else {
            ret = endParam-startParam;
        }
    }

    // full ellipse or zero length ellipse arc:
    if (!allowForZeroLength) {
        if (fabs(ret) < RS::AngleTolerance) {
            ret = 2 * M_PI;
        }
    }
    else {
        if (ret > 2 * M_PI - RS::AngleTolerance) {
            ret = 0.0;
        }
    }

    return ret;
}

RVector REllipse::getStartPoint() const {
    RVector p(
        center.x + cos(startParam) * getMajorRadius(),
        center.y + sin(startParam) * getMinorRadius()
    );
    p.rotate(getAngle(), center);
    return p;
}

RVector REllipse::getEndPoint() const {
    RVector p(
        center.x + cos(endParam) * getMajorRadius(),
        center.y + sin(endParam) * getMinorRadius()
    );
    p.rotate(getAngle(), center);
    return p;
}

/**
 * \return The major radius of this ellipse.
 */
double REllipse::getMajorRadius() const {
    return majorPoint.getMagnitude();
}

/**
 * \return The minor radius of this ellipse.
 */
double REllipse::getMinorRadius() const {
    return majorPoint.getMagnitude()*ratio;
}

/**
 * \return The rotation angle of this ellipse.
 */
double REllipse::getAngle() const {
    return majorPoint.getAngle();
}

/**
 * Sets the rotation angle of this ellipse without changing the major radius.
 */
void REllipse::setAngle(double a) {
    majorPoint = RVector::createPolar(majorPoint.getMagnitude(), a);
}

bool REllipse::isFullEllipse() const {
    double a1 = RMath::getNormalizedAngle(startParam);
    double a2 = RMath::getNormalizedAngle(endParam);
    return (a1 < RS::AngleTolerance && a2 > 2*M_PI-RS::AngleTolerance) ||
        (fabs(a1 - a2) < RS::AngleTolerance);
}

/**
 * \return True if minor radius and major radius are equal, i.e. ratio is 1.0.
 */
bool REllipse::isCircular() const {
    return getRatio()>(1.0-RS::PointTolerance);
}

/**
 * \return Approximation for ellipse arc length.
 */
double REllipse::getLength() const {
    double a1, a2;

    if (isFullEllipse()) {
        a1 = 0.0;
        a2 = 2*M_PI;
    }
    else {
        a1 = RMath::getNormalizedAngle(startParam);
        a2 = RMath::getNormalizedAngle(endParam);
    }

    if (reversed) {
        double t = a1;
        a1 = a2;
        a2 = t;
    }

    if (RMath::fuzzyCompare(a2, 0.0)) {
        a2 = 2*M_PI;
    }

    if (fabs(a1-a2)<RS::AngleTolerance) {
        return 0.0;
    }

    if (a1<a2) {
        if (a1<M_PI && a2<=M_PI) {
            return getSimpsonLength(a1, a2);
        }
        if (a1<M_PI && a2>M_PI) {
            return getSimpsonLength(a1, M_PI) + getSimpsonLength(M_PI, a2);
        }
        if (a1>=M_PI && a2>M_PI) {
            return getSimpsonLength(a1, a2);
        }
    }
    else {
        if (a1>M_PI && a2<M_PI) {
            return getSimpsonLength(a1, 2*M_PI) + getSimpsonLength(0, a2);
        }
        if (a1>M_PI && a2>M_PI) {
            return getSimpsonLength(a1, 2*M_PI) + getSimpsonLength(0, M_PI) + getSimpsonLength(M_PI, a2);
        }
        if (a1<M_PI && a2<M_PI) {
            return getSimpsonLength(a1, M_PI) + getSimpsonLength(M_PI, 2*M_PI) + getSimpsonLength(0, a2);
        }
    }

    return RNANDOUBLE;
}

/**
 * \return Length of the ellipse segment from angle a1 to angle a2.
 */
double REllipse::getSimpsonLength(double a1, double a2) const {
    double df = (a2-a1) / 20;
    double R = getMajorRadius();
    double r = getMinorRadius();

    double sum = 0.0;
    double q = 1.0;

    for (int i=0; i<=20; ++i) {
        double y = sqrt(::pow(R * sin(a1 + i * df), 2) + ::pow(r * cos(a1 + i * df), 2));
        if (i==0 || i==20) {
            q = 1.0;
        }
        else {
            if (i%2==0) {
                q = 2.0;
            }
            else {
                q = 4.0;
            }
        }

        sum += q * y;
    }

    return (df / 3.0) * sum;
}

bool REllipse::contains(const RVector& p) const {
    RVector pt = p;
    pt.move(-center);
    pt.rotate(-getAngle());
    double rx = getMajorRadius();
    double ry = getMinorRadius();
    return (pt.x*pt.x) / (rx*rx) + (pt.y*pt.y) / (ry*ry) <= 1.0;
}

// depends on implementation of getPointsWithDistanceToEnd:
//double REllipse::getAngleAt(double distance, RS::From from) const {
//    REllipse normal = *this;
//    normal.rotate(-getAngle());

//    QList<RVector> points = normal.getPointsWithDistanceToEnd(distance, from);
//    if (points.length()!=1) {
//        return RNANDOUBLE;
//    }

//    RVector p = points[0];

//    double minR = normal.getMinorRadius();
//    double majR = normal.getMajorRadius();

//    double ret = - ((minR*minR*p.x) / (majR*majR*p.y));
//    ret+=getAngle();
//    return ret;
//}


bool REllipse::isReversed() const {
    return reversed;
}

void REllipse::setReversed(bool r) {
    reversed = r;
}

double REllipse::getDirection1() const{
    if (!reversed) {
        return RMath::getNormalizedAngle(getAngle() + startParam+M_PI/2.0);
    }
    else {
        return RMath::getNormalizedAngle(getAngle() + startParam-M_PI/2.0);
    }
}

double REllipse::getDirection2() const{
    if (!reversed) {
        return RMath::getNormalizedAngle(getAngle() + endParam-M_PI/2.0);
    }
    else {
        return RMath::getNormalizedAngle(getAngle() + endParam+M_PI/2.0);
    }
}

RBox REllipse::getBoundingBox() const {
    double radius1 = getMajorRadius();
    double radius2 = getMinorRadius();
    double angle = getAngle();
    double a1 = ((!isReversed()) ? startParam : endParam);
    double a2 = ((!isReversed()) ? endParam : startParam);
    RVector startPoint = getStartPoint();
    RVector endPoint = getEndPoint();

    double minX = qMin(startPoint.x, endPoint.x);
    double minY = qMin(startPoint.y, endPoint.y);
    double maxX = qMax(startPoint.x, endPoint.x);
    double maxY = qMax(startPoint.y, endPoint.y);

    // kind of a brute force. TODO: exact calculation
    RVector vp;
    double a = a1;
    do {
        vp.set(center.x + radius1 * cos(a),
               center.y + radius2 * sin(a));
        vp.rotate(angle, center);

        minX = qMin(minX, vp.x);
        minY = qMin(minY, vp.y);
        maxX = qMax(maxX, vp.x);
        maxY = qMax(maxY, vp.y);

        a += 0.03;
    } while (RMath::isAngleBetween(a, a1, a2, false) && a<4*M_PI);

    return RBox(RVector(minX,minY), RVector(maxX,maxY));
}

QList<RVector> REllipse::getEndPoints() const {
    QList<RVector> ret;
    ret.append(getStartPoint());
    ret.append(getEndPoint());
    return ret;
}

/**
 * \todo implement
 */
QList<RVector> REllipse::getMiddlePoints() const {
    QList<RVector> ret;
    //ret.append(getMiddlePoint());
    return ret;
}

QList<RVector> REllipse::getCenterPoints() const {
    QList<RVector> ret;
    ret.append(getCenter());
    return ret;
}

/**
 * \todo implement
 */
QList<RVector> REllipse::getPointsWithDistanceToEnd(double distance, RS::From from) const {
    Q_UNUSED(distance)
    Q_UNUSED(from)

    QList<RVector> ret;
    return ret;
}

RVector REllipse::getVectorTo(const RVector& point, bool limited, double strictRange) const {
    Q_UNUSED(strictRange)

    RVector ret = RVector::invalid;

    double ang = getAngle();
    //double dDistance = RMAXDOUBLE;
    bool swap = false;
    bool majorSwap = false;

    RVector normalized = (point - center).rotate(-ang);

    // special case: point in line with major axis:
    if (fabs(normalized.getAngle()) < RS::AngleTolerance || fabs(normalized.getAngle()) > 2*M_PI-RS::AngleTolerance) {
        ret = RVector(getMajorRadius(), 0.0);
        //dDistance = ret.distanceTo(normalized);
    }

    else if (fabs(normalized.getAngle()-M_PI) < RS::AngleTolerance) {
        ret = RVector(-getMajorRadius(), 0.0);
        //dDistance = ret.distanceTo(normalized);
    }
    else {
        double dU = normalized.x;
        double dV = normalized.y;
        double dA = getMajorRadius();
        double dB = getMinorRadius();
        double dEpsilon = 1.0e-8;
        // iteration maximum
        int iMax = 32;
        double rdX = 0.0;
        double rdY = 0.0;

        if (dA<dB) {
            double dum = dA;
            dA = dB;
            dB = dum;
            dum = dU;
            dU = dV;
            dV = dum;
            majorSwap = true;
        }

        if (dV<0.0) {
            dV*=-1.0;
            swap = true;
        }

        // initial guess:
        double dT = dB*(dV - dB);

        // newton's method:
        int i;
        for (i = 0; i < iMax; i++) {
            double dTpASqr = dT + dA*dA;
            double dTpBSqr = dT + dB*dB;
            double dInvTpASqr = 1.0/dTpASqr;
            double dInvTpBSqr = 1.0/dTpBSqr;
            double dXDivA = dA*dU*dInvTpASqr;
            double dYDivB = dB*dV*dInvTpBSqr;
            double dXDivASqr = dXDivA*dXDivA;
            double dYDivBSqr = dYDivB*dYDivB;
            double dF = dXDivASqr + dYDivBSqr - 1.0;
            if (fabs(dF) < dEpsilon) {
                // f(t0) is very close to zero:
                rdX = dXDivA*dA;
                rdY = dYDivB*dB;
                break;
            }
            double dFDer = 2.0*(dXDivASqr*dInvTpASqr + dYDivBSqr*dInvTpBSqr);

            double dRatio = dF/dFDer;

            if ( fabs(dRatio) < dEpsilon ) {
                // t1-t0 is very close to zero:
                rdX = dXDivA*dA;
                rdY = dYDivB*dB;
                break;
            }
            dT += dRatio;
        }

        if (i == iMax) {
            // failed to converge:
            //dDistance = RMAXDOUBLE;
            ret = RVector::invalid;
        }
        else {
            //double dDelta0 = rdX - dU;
            //double dDelta1 = rdY - dV;
            //dDistance = sqrt(dDelta0*dDelta0 + dDelta1*dDelta1);
            ret = RVector(rdX, rdY);
        }
    }

    if (ret.isValid()) {
        if (swap) {
            ret.y*=-1.0;
        }
        if (majorSwap) {
            double dum = ret.x;
            ret.x = ret.y;
            ret.y = dum;
        }
        ret = (ret.rotate(ang) + center);

        if (limited) {
            double a1 = center.getAngleTo(getStartPoint());
            double a2 = center.getAngleTo(getEndPoint());
            double a = center.getAngleTo(ret);
            if (!RMath::isAngleBetween(a, a1, a2, reversed)) {
                ret = RVector::invalid;
            }
        }
    }

    /*
    if (dist!=NULL) {
        if (ret.valid) {
            *dist = dDistance;
        } else {
            *dist = RS_MAXDOUBLE;
        }
    }

    if (entity!=NULL) {
        if (ret.valid) {
            *entity = this;
        }
        else {
            *entity = NULL;
        }
    }
    */

    return point - ret;
}

bool REllipse::move(const RVector& offset) {
    if (!offset.isValid() || offset.getMagnitude() < RS::PointTolerance) {
        return false;
    }
    center += offset;
    return true;
}

bool REllipse::rotate(double rotation, const RVector& c) {
    if (fabs(rotation) < RS::AngleTolerance) {
        return false;
    }

    center.rotate(rotation, c);
    majorPoint.rotate(rotation);

    return true;
}

QList<RVector> REllipse::getBoxCorners() {
    QList<RVector> ret;

    RVector minorPoint = getMinorPoint();
    ret.append(center + majorPoint + minorPoint);
    ret.append(center + majorPoint - minorPoint);
    ret.append(center - majorPoint - minorPoint);
    ret.append(center - majorPoint + minorPoint);

    return ret;
}

bool REllipse::scale(const RVector& scaleFactors, const RVector& c) {
    if (fabs(fabs(scaleFactors.x) - fabs(scaleFactors.y)) > RS::PointTolerance) {
        qWarning("REllipse::scale: scaling with different factors in X/Y not supported for ellipses at this point");
        return false;
    }

    //RVector oldMinorPoint = getMinorPoint();

    // negative scaling: mirroring and scaling
    if (scaleFactors.x < 0.0) {
        mirror(RLine(center, center + RVector(0.0, 1.0)));
    }
    if (scaleFactors.y < 0.0) {
        mirror(RLine(center, center + RVector(1.0, 0.0)));
    }

    center.scale(scaleFactors, c);

    //oldMinorPoint.scale(scaleFactors);

    RVector f = RVector(fabs(scaleFactors.x), fabs(scaleFactors.y), fabs(scaleFactors.z));
    majorPoint.scale(f);

//    if (fabs(majorPoint.getMagnitude()) > 1.0e-4) {
//        ratio = oldMinorPoint.getMagnitude() / majorPoint.getMagnitude();
//    }

    return true;

//    QList<RVector> box = getBoxCorners();
//    RVector::scaleList(box, scaleFactors, c);
//    // TODO:
//    REllipse e = REllipse::createInscribed(box);
//    //*this = e;

//    return true;
}

bool REllipse::mirror(const RLine& axis) {
    RVector mp = center + majorPoint;
    RVector sp = getStartPoint();
    RVector ep = getEndPoint();

    center.mirror(axis);
    mp.mirror(axis);

    majorPoint = mp - center;

    if (!isFullEllipse()) {
        reversed = (!reversed);

        sp.mirror(axis);
        setStartParam(getParamTo(sp));

        ep.mirror(axis);
        setEndParam(getParamTo(ep));
    }

    return true;
}

bool REllipse::reverse() {
    double a = startParam;
    startParam = endParam;
    endParam = a;
    reversed = !reversed;
    return true;
}

QSharedPointer<RShape> REllipse::getTransformed(const QTransform& transform) const {
    RVector ct = center.getTransformed2d(transform);
    RVector mp = center + getMajorPoint();
    RVector mpt = mp.getTransformed2d(transform);
    RVector sp = getStartPoint();
    RVector spt = sp.getTransformed2d(transform);
    RVector ep = getEndPoint();
    RVector ept = ep.getTransformed2d(transform);

    QSharedPointer<REllipse> ret = QSharedPointer<REllipse>(
        new REllipse(
            ct,
            mpt - ct,
            ratio,
            0.0,
            M_PI*2,
            reversed
        )
    );
    ret->setStartParam(ret->getParamTo(spt));
    ret->setEndParam(ret->getParamTo(ept));
    return ret;
}

RS::Ending REllipse::getTrimEnd(const RVector& coord, const RVector& trimPoint) {
    double angEl = getParamTo(trimPoint);
    double angM = getParamTo(coord);

    if (RMath::getAngleDifference(angM, angEl)>M_PI) {
        return RS::EndingStart;
    }
    else {
        return RS::EndingEnd;
    }
}

void REllipse::trimStartPoint(const RVector& p) {
    setStartParam(getParamTo(p));
}

void REllipse::trimEndPoint(const RVector& p) {
    setEndParam(getParamTo(p));
}

void REllipse::correctMajorMinor() {
    if (ratio>1.0) {
        RVector mp = getMinorPoint();
        ratio = 1.0/ratio;
        setMajorPoint(mp);
        startParam = RMath::getNormalizedAngle(startParam - M_PI/2.0);
        endParam = RMath::getNormalizedAngle(endParam - M_PI/2.0);
    }
}

/**
 * \return Arc sweep in rad. The sweep is the angle covered by this arc.
 * Positive for ccw, negative for cw.
 */
double REllipse::getSweep() const {
    double ret = 0.0;

    if (reversed) {
        if (startParam <= endParam) {
            ret = -(startParam + 2 * M_PI - endParam);
        } else {
            ret = -(startParam - endParam);
        }
    } else {
        if (endParam <= startParam) {
            ret = endParam + 2 * M_PI - startParam;
        } else {
            ret = endParam - startParam;
        }
    }

    return ret;
}

QList<RLine> REllipse::getTangents(const RVector& point) const {
    QList<RLine> ret;

    if (getDistanceTo(point, false) < RS::PointTolerance) {
        // point is on ellipse:
        return ret;
    }

    // point is at center (prevents recursion when swapping ellipse minor / major):
    if (point.getDistanceTo(getCenter())<RS::PointTolerance) {
        return ret;
    }

    // swap ellipse minor / major if point is on minor axis
    // 20120928: and not also on major axis (prevent recursion):
    RLine minorAxis(getCenter(), getCenter() + getMinorPoint());
    RLine majorAxis(getCenter(), getCenter() + getMajorPoint());
    if (minorAxis.isOnShape(point, false) && !majorAxis.isOnShape(point, false)) {
        REllipse e2 =*this;
        e2.majorPoint = getMinorPoint();
        e2.ratio = 1.0/ratio;
        return e2.getTangents(point);
    }

    double a = getMajorRadius();     // the length of the major axis / 2
    double b = getMinorRadius();     // the length of the minor axis / 2

    // rotate and move point:
    RVector point2 = point;
    point2.move(-getCenter());
    point2.rotate(-getAngle());

    double xp = point2.x;             // coordinates of the given point
    double yp = point2.y;

    double xt1;                      // Tangent point 1
    double yt1;
    double xt2;                      // Tangent point 2
    double yt2;

    double a2 = a * a;
    double b2 = b * b;
    double d = a2 / b2 * yp / xp;
    double e = a2 / xp;
    double af = b2 * d * d + a2;
    double bf = -b2 * d * e * 2.0;
    double cf = b2 * e * e - a2 * b2;
    double t = sqrt(bf * bf - af * cf * 4.0);
    if (RMath::isNaN(t)) {
        return ret;
    }

    yt1 = (t - bf) / (af * 2.0);
    xt1 = e - d * yt1;
    yt2 = (-t - bf) / (af * 2.0);
    xt2 = e - d * yt2;

    RVector s1(xt1, yt1);
    s1.rotate(getAngle());
    s1.move(getCenter());

    RVector s2(xt2, yt2);
    s2.rotate(getAngle());
    s2.move(getCenter());

    if (s1.isValid()) {
        ret.append(RLine(point, s1));
    }

    if (s2.isValid()) {
        ret.append(RLine(point, s2));
    }

    return ret;
}

void REllipse::print(QDebug dbg) const {
    dbg.nospace() << "REllipse(";
    RShape::print(dbg);
    dbg.nospace() << ", startPoint: " << getStartPoint()
                  << ", endPoint: " << getEndPoint()
                  << ", center: " << getCenter()
                  << ", majorPoint: " << getMajorPoint()
                  << ", majorRadius: " << getMajorRadius()
                  << ", minorRadius: " << getMinorRadius()
                  << ", ratio: " << getRatio()
                  << ", startAngle: " << RMath::rad2deg(getStartParam())
                  << ", endAngle: " << RMath::rad2deg(getEndParam())
                  << ", full: " << isFullEllipse()
                  << ", clockwise: " << isReversed()
                  << ")";
}
