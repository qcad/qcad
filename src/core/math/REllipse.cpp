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
#include <cmath>

#include "REllipse.h"
#include "RBox.h"
#include "RMath.h"
#include "RMatrix.h"

REllipseProxy* REllipse::ellipseProxy = NULL;

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

/**
 * Produces an ellipse inscribed in the quadrilateral defined by the
 * four given ordered vertices (RVector).
 *
 * Based on:
 * http://chrisjones.id.au/Ellipses/ellipse.html
 * http://mathworld.wolfram.com/Ellipse.html
 */
REllipse REllipse::createInscribed(const RVector& p1, const RVector& p2, const RVector& p3, const RVector& p4) {
    double scale = RNANDOUBLE;

    int i;

    QList<RVector> quad;
    quad.append(p1);
    quad.append(p2);
    quad.append(p3);
    quad.append(p4);

    RBox extr = RBox(RVector::getMinimum(quad), RVector::getMaximum(quad));

    // offset to 0,0 to reduce magnitudes:
    RVector offset = extr.getCenter().getNegated();

    RVector::moveList(quad, offset);

    // numbers in this algorithm can get extremely large, so we scale down here
    // a bit if appropriate:
    if (extr.getWidth()>100.0 || extr.getHeight()>100.0) {
        scale = 100.0 / qMax(extr.getWidth(), extr.getHeight());
        RVector::scaleList(quad, scale);
    }

    QList<RLine> edges;
    for (i=0; i<4; i++) {
        edges.append(RLine(quad[i], quad[(i+1)%4]));
    }

    double x0 = quad[0].x;
    double y0 = quad[0].y;
    double x1 = quad[1].x;
    double y1 = quad[1].y;
    double x2 = quad[2].x;
    double y2 = quad[2].y;
    double x3 = quad[3].x;
    double y3 = quad[3].y;

    double ma =  x1 * x2 * y3 - x0 * x2 * y3 - x1 * y2 * x3 + x0 * y2 * x3 - x0 * y1 * x3 + y0 * x1 * x3 + x0 * y1 * x2 - y0 * x1 * x2;
    double mb =  x0 * x2 * y3 - x0 * x1 * y3 - x1 * y2 * x3 + y1 * x2 * x3 - y0 * x2 * x3 + y0 * x1 * x3 + x0 * x1 * y2 - x0 * y1 * x2;
    double mc =  x1 * x2 * y3 - x0 * x1 * y3 - x0 * y2 * x3 - y1 * x2 * x3 + y0 * x2 * x3 + x0 * y1 * x3 + x0 * x1 * y2 - y0 * x1 * x2;
    double md =  y1 * x2 * y3 - y0 * x2 * y3 - x0 * y1 * y3 + y0 * x1 * y3 - y1 * y2 * x3 + y0 * y2 * x3 + x0 * y1 * y2 - y0 * x1 * y2;
    double me = -x1 * y2 * y3 + x0 * y2 * y3 + y1 * x2 * y3 - x0 * y1 * y3 - y0 * y2 * x3 + y0 * y1 * x3 + y0 * x1 * y2 - y0 * y1 * x2;
    double mf =  x1 * y2 * y3 - x0 * y2 * y3 + y0 * x2 * y3 - y0 * x1 * y3 - y1 * y2 * x3 + y0 * y1 * x3 + x0 * y1 * y2 - y0 * y1 * x2;
    double mg =  x1 * y3 - x0 * y3 - y1 * x3 + y0 * x3 - x1 * y2 + x0 * y2 + y1 * x2 - y0 * x2;
    double mh =  x2 * y3 - x1 * y3 - y2 * x3 + y1 * x3 + x0 * y2 - y0 * x2 - x0 * y1 + y0 * x1;
    double mi =  x2 * y3 - x0 * y3 - y2 * x3 + y0 * x3 + x1 * y2 - y1 * x2 + x0 * y1 - y0 * x1;

    RMatrix T = RMatrix::create3x3(
        ma, mb, mc,
        md, me, mf,
        mg, mh, mi
    );

    RMatrix TI = T.getInverse();

    double mj = TI.get(0, 0);
    double mk = TI.get(0, 1);
    double ml = TI.get(0, 2);
    double mm = TI.get(1, 0);
    double mn = TI.get(1, 1);
    double mo = TI.get(1, 2);
    double mp = TI.get(2, 0);
    double mq = TI.get(2, 1);
    double mr = TI.get(2, 2);

    double a = mj*mj + mm*mm - mp*mp;
    double b = mj*mk + mm*mn - mp*mq;
    double c = mk*mk + mn*mn - mq*mq;
    double d = mj*ml + mm*mo - mp*mr;
    double f = mk*ml + mn*mo - mq*mr;
    double g = ml*ml + mo*mo - mr*mr;

    double term = (b*b - a*c);

    double cx, cy, axis1, axis2;

    // circle:
    if (qAbs(term)<1e-50) {
        cx = (p1.x + p3.x)/2;
        cy = (p1.y + p3.y)/2;
        axis1 = p1.getDistanceTo(p2)/2;
        axis2 = axis1;
    }
    else {
        cx = (c*d - b*f) / term;
        cy = (a*f - b*d) / term;

        double term1 = (2 * (a*f*f + c*d*d + g*b*b - 2*b*d*f - a*c*g));
        double term2 = sqrt((a-c)*(a-c) + 4*b*b);
        double term3 = (a + c);

        axis1 = sqrt(term1 / (term * (term2-term3)));
        axis2 = sqrt(term1 / (term * (-term2-term3)));
    }

    RVector center(cx, cy);

    double angle;

    if (b==0.0) {
        angle = 0;
    }
    else {
        angle = 0.5 * (M_PI/2 - atan((a-c)/(2*b)));
    }

    if (a>c) {
        angle += M_PI/2;
    }

    RVector majorPoint = RVector::createPolar(axis1, angle);

    REllipse ellipse(center, majorPoint, axis2/axis1, 0.0, 2*M_PI, false);

    // workaround if the algorithm above does not produce the correct angle
    // (90 degrees off):
    for (i=0; i<4; i++) {
        QList<RVector> ips = ellipse.getIntersectionPoints(edges[i], false);
        if (ips.length()==2) {
            if (!ips[0].equalsFuzzy(ips[1], 0.001)) {
                ellipse.rotate(M_PI/2, ellipse.getCenter());
                break;
            }
        }
    }

    if (!RMath::isNaN(scale)) {
        ellipse.scale(RVector(1.0/scale,1.0/scale));
    }
    ellipse.move(offset.getNegated());

    return ellipse;
}

bool REllipse::isValid() {
    return center.isValid() && majorPoint.isValid() && !RMath::isNaN(ratio) && !RMath::isNaN(startParam) && !RMath::isNaN(endParam);
}

QList<RVector> REllipse::getFoci() const {
    RVector vp(getMajorPoint() * sqrt(1.0 - getRatio()*getRatio()));
    return QList<RVector>() << getCenter()+vp << getCenter()-vp;
}

void REllipse::setZ(double z) {
    center.z = z;
    majorPoint.z = z;
}

QList<RVector> REllipse::getVectorProperties() const {
    return QList<RVector>() << center << majorPoint;
}

QList<double> REllipse::getDoubleProperties() const {
    return QList<double>() << ratio << startParam << endParam;
}

QList<bool> REllipse::getBoolProperties() const {
    return QList<bool>() << reversed;
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

double REllipse::getAngleAt(double distance, RS::From from) const {
    Q_UNUSED(distance)
    Q_UNUSED(from)

    // TODO: getPointWithDistanceToStart not implemented for ellipses:
//    RVector pos;
//    if (from==RS::FromStart) {
//        pos = getPointWithDistanceToStart(distance);
//    }
//    else {
//        pos = getPointWithDistanceToEnd(distance);
//    }

//    return getAngleAtPoint(pos);

    return 0.0;
}

double REllipse::getAngleAtPoint(const RVector& pos) const {
    RVector posNormalized = pos;
    posNormalized.move(-getCenter());
    posNormalized.rotate(-getAngle());

    double angle;
    if (RMath::fuzzyCompare(posNormalized.y, 0.0)) {
        if (posNormalized.x>0) {
            angle = M_PI/2;
        }
        else {
            angle = M_PI/2*3;
        }
    }
    else {
        double slope = - (pow(getMinorRadius()*2, 2) * posNormalized.x) / (pow(getMajorRadius()*2, 2) * posNormalized.y);
        angle = atan(slope) + M_PI;
    }

    if (reversed) {
        angle += M_PI;
    }

    if (posNormalized.y<0) {
        angle += M_PI;
    }

    angle += getAngle();

    return RMath::getNormalizedAngle(angle);
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
double REllipse::getRadiusAt(double param) const {
    RVector v(cos(param)*getMajorRadius(),
              sin(param)*getMinorRadius());
    return v.getMagnitude();
}

/**
 * \return Point on ellipse at given ellipse angle.
 */
RVector REllipse::getPointAt(double param) const {
    RVector v(cos(param)*getMajorRadius(),
              sin(param)*getMinorRadius());
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

/**
 * \return Start parameter: the start angle of the circular arc
 * resulting from transforming the ellipse into a circle.
 */
double REllipse::getStartParam() const {
    return startParam;
}

void REllipse::setStartParam(double a) {
    startParam = a;
}

/**
 * \return End parameter: the end angle of the circular arc
 * resulting from transforming the ellipse into a circle.
 */
double REllipse::getEndParam() const {
    return endParam;
}

void REllipse::setEndParam(double a) {
    endParam = a;
}

/**
 * \return Start angle: the angle from the ellipse
 * arc center to the ellipse arc start point.
 */
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

/**
 * \return End angle: the angle from the ellipse
 * arc center to the ellipse arc end point.
 */
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
    int interval = 20;
    double df = (a2-a1) / interval;
    double majorR = getMajorRadius();
    double minorR = getMinorRadius();

    double sum = 0.0;
    double q = 1.0;

    for (int i=0; i<=interval; ++i) {
        double y = sqrt(::pow(majorR * sin(a1 + i * df), 2) + ::pow(minorR * cos(a1 + i * df), 2));
        if (i==0 || i==interval) {
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
    return getAngleAtPoint(getStartPoint());
//    if (!reversed) {
//        return RMath::getNormalizedAngle(getAngle() + startParam+M_PI/2.0);
//    }
//    else {
//        return RMath::getNormalizedAngle(getAngle() + startParam-M_PI/2.0);
//    }
}

double REllipse::getDirection2() const{
    return RMath::getNormalizedAngle(getAngleAtPoint(getEndPoint()) + M_PI);
//    if (!reversed) {
//        return RMath::getNormalizedAngle(getAngle() + endParam-M_PI/2.0);
//    }
//    else {
//        return RMath::getNormalizedAngle(getAngle() + endParam+M_PI/2.0);
//    }
}

RS::Side REllipse::getSideOfPoint(const RVector& point) const {
    if (contains(point)) {
        if (!reversed) {
            return RS::RightHand;
        }
        else {
            return RS::LeftHand;
        }
    }
    else {
        if (!reversed) {
            return RS::LeftHand;
        }
        else {
            return RS::RightHand;
        }
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
QList<RVector> REllipse::getPointsWithDistanceToEnd(double distance, int from) const {
    Q_UNUSED(distance)
    Q_UNUSED(from)

    QList<RVector> ret;
    return ret;
}

QList<RVector> REllipse::getPointCloud(double segmentLength) const {
    RPolyline pl = approximateWithArcs(64);
    return pl.getPointCloud(segmentLength);
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
    RVector ct = center.getTransformed2D(transform);
    RVector mp = center + getMajorPoint();
    RVector mpt = mp.getTransformed2D(transform);
    RVector sp = getStartPoint();
    RVector spt = sp.getTransformed2D(transform);
    RVector ep = getEndPoint();
    RVector ept = ep.getTransformed2D(transform);

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

RS::Ending REllipse::getTrimEnd(const RVector& trimPoint, const RVector& clickPoint) {
    double paramToClickPoint = getParamTo(clickPoint);
    double paramToTrimPoint = getParamTo(trimPoint);

    if (RMath::getAngleDifference(paramToTrimPoint, paramToClickPoint)>M_PI) {
        return RS::EndingStart;
    }
    else {
        return RS::EndingEnd;
    }
}

bool REllipse::trimStartPoint(const RVector& trimPoint, const RVector& clickPoint, bool extend) {
    Q_UNUSED(clickPoint)
    Q_UNUSED(extend)
    setStartParam(getParamTo(trimPoint));
    return true;
}

bool REllipse::trimEndPoint(const RVector& trimPoint, const RVector& clickPoint, bool extend) {
    Q_UNUSED(clickPoint)
    Q_UNUSED(extend)
    setEndParam(getParamTo(trimPoint));
    return true;
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

QList<RSpline> REllipse::approximateWithSplines() const {
    if (REllipse::hasProxy()) {
        return REllipse::getEllipseProxy()->approximateWithSplines(*this);
    }
    return QList<RSpline>();
}

RPolyline REllipse::approximateWithArcs(int segments) const {
    if (REllipse::hasProxy()) {
        return REllipse::getEllipseProxy()->approximateWithArcs(*this, segments);
    }
    return RPolyline();
}

/**
 * \return Array of spline shapes representing the parallel curves to this ellipse shape.
 */
QList<QSharedPointer<RShape> > REllipse::getOffsetShapes(double distance, int number, RS::Side side, const RVector& position) {
    errorCode = 0;
    QList<QSharedPointer<RShape> > ret;
    REllipse* ellipse = dynamic_cast<REllipse*>(clone());
    if (ellipse==NULL) {
        return ret;
    }

    RVector center = ellipse->getCenter();

    if (ellipse->isReversed()) {
        ellipse->reverse();
    }

    QList<bool> insides;
    if (position.isValid()) {
        double ang = center.getAngleTo(position) - ellipse->getAngle();
        double t = ellipse->angleToParam(ang);
        RVector p = ellipse->getPointAt(t);
        insides.append(center.getDistanceTo(position) < center.getDistanceTo(p));
    }
    else {
        if (side==RS::BothSides) {
            insides.append(true);
            insides.append(false);
        }
        else {
            if (side==RS::LeftHand) {
                insides.append(true);
            }
            else {
                insides.append(false);
            }
        }
    }

    double a = ellipse->getMajorRadius();
    double b = ellipse->getMinorRadius();

    for (int i=0; i<insides.length(); i++) {
        bool inside = insides[i];
        double d = distance;

        if (inside) {
            d *= -1;
        }

        for (int n=1; n<=number; ++n) {
            RSpline* spl = NULL;
            RPolyline* pl = NULL;
            if (RSpline::hasProxy()) {
                spl = new RSpline();
            }
            else {
                pl = new RPolyline();
            }

            double endParam = ellipse->getEndParam();
            double startParam = ellipse->getStartParam();
            if (RMath::fuzzyCompare(endParam, 0.0)) {
                endParam = 2*M_PI;
            }

            if (endParam<startParam) {
                endParam += 2*M_PI;
            }

            double k = d*n;
            double tMax = endParam+0.1;
            if (ellipse->isFullEllipse()) {
                tMax = endParam;
            }

            for (double t=startParam; t<tMax; t+=0.1) {
                if (t>endParam) {
                    t = endParam;
                }

                double root = sqrt(a*a * pow(sin(t), 2) + b*b * pow(cos(t), 2));
                double x = (a + (b * k) / root) * cos(t);
                double y = (b + (a * k) / root) * sin(t);
                RVector v(x, y);
                v.rotate(ellipse->getAngle());
                v.move(center);
                if (spl!=NULL) {
                    spl->appendFitPoint(v);
                }
                else {
                    pl->appendVertex(v);
                }
            }

            if (ellipse->isFullEllipse()) {
                if (spl!=NULL) {
                    spl->setPeriodic(true);
                }
                else {
                    // no ellipse proxy: offset curve is polyline:
                    pl->setClosed(true);
                }
            }

            if (spl!=NULL) {
                ret.append(QSharedPointer<RShape>(spl));
            }
            else {
                ret.append(QSharedPointer<RShape>(pl));
            }
        }
    }

    return ret;
}

QList<QSharedPointer<RShape> > REllipse::splitAt(const QList<RVector>& points) const {
    if (points.length()==0) {
        return RShape::splitAt(points);
    }

    QList<QSharedPointer<RShape> > ret;

    if (reversed) {
        REllipse ellipse = *this;
        ellipse.reverse();
        ret = ellipse.splitAt(points);
        return RShape::getReversedShapeList(ret);
    }

    RVector startPoint = getStartPoint();
    RVector endPoint = getEndPoint();

    QList<RVector> sortedPoints = RVector::getSortedByAngle(points, center, center.getAngleTo(startPoint));

    if (!startPoint.equalsFuzzy(sortedPoints[0])) {
        sortedPoints.prepend(startPoint);
    }
    if (!endPoint.equalsFuzzy(sortedPoints[sortedPoints.length()-1])) {
        sortedPoints.append(endPoint);
    }
    for (int i=0; i<sortedPoints.length()-1; i++) {
        if (sortedPoints[i].equalsFuzzy(sortedPoints[i+1])) {
            continue;
        }

        REllipse* seg = clone();
        seg->setStartParam(seg->getParamTo(sortedPoints[i]));
        seg->setEndParam(seg->getParamTo(sortedPoints[i+1]));
        ret.append(QSharedPointer<RShape>(seg));
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
