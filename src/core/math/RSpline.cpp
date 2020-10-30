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

#include "RArc.h"
#include "RDebug.h"
#include "RLine.h"
#include "RSpline.h"
#include "RPainterPath.h"
#include "RPolyline.h"


//RSpline::UpdateFromFitPointsFunction RSpline::updateFromFitPointsFunction = NULL;
//RSpline::SplitFunction RSpline::splitFunction = NULL;
RSplineProxy* RSpline::splineProxy = NULL;

/**
 * Creates a spline object without controlPoints.
 */
RSpline::RSpline() :
    degree(3), periodic(false), dirty(true), updateInProgress(false), length(RNANDOUBLE) {
}

RSpline::RSpline(const RSpline& other) {
    *this = other;
}

/**
 * Creates a spline object with the given control points and degree.
 */
RSpline::RSpline(const QList<RVector>& controlPoints, int degree) :
    controlPoints(controlPoints), degree(degree), periodic(false), dirty(true), updateInProgress(false), length(RNANDOUBLE) {

    //updateInternal();
}

//RSpline::~RSpline() {
    //invalidate();
//}

RSpline& RSpline::operator =(const RSpline& other) {
    controlPoints = other.controlPoints;
    knotVector = other.knotVector;
    weights = other.weights;
    fitPoints = other.fitPoints;
    degree = other.degree;
    tangentStart = other.tangentStart;
    tangentEnd = other.tangentEnd;
    periodic = other.periodic;
    dirty = other.dirty;
    updateInProgress = other.updateInProgress;
#ifndef R_NO_OPENNURBS
    if (other.curve.IsValid()) {
        curve = other.curve;
    }
#endif
    boundingBox = other.boundingBox;
    exploded = other.exploded;
    length = other.length;

    return *this;
}

void RSpline::copySpline(const RSpline& other) {
    this->degree = other.degree;
    this->periodic = other.periodic;
    this->controlPoints = other.controlPoints;
    this->fitPoints = other.fitPoints;
    this->knotVector = other.knotVector;
    this->weights = other.weights;
    this->tangentStart = other.tangentStart;
    this->tangentEnd = other.tangentEnd;
    this->boundingBox = other.boundingBox;
    this->length = other.length;
    bool d = other.dirty;

    // do NOT copy curve member (copying of ON_NurbsCurve is broken, segfaults).
    dirty = true;
    updateInternal();

    // if original was not dirty, copy cached exploded representation:
    if (!d) {
        this->exploded = other.exploded;
    }
}

/**
 *  \return List of splines which approximate the given arc.
 */
QList<RSpline> RSpline::createSplinesFromArc(const RArc& arc) {
    RArc a = arc;
    bool reversed = false;
    if (a.isReversed()) {
        reversed = true;
        a.reverse();
    }

    double startAngle = RMath::getNormalizedAngle(a.getStartAngle());
    double endAngle = RMath::getNormalizedAngle(a.getEndAngle());
    if (a.isFullCircle()) {
        startAngle = 0.0;
        endAngle = 2*M_PI;
    }

    // normalize startAngle, endAngle to [-2PI, 2PI]
    double twoPI = M_PI * 2;
    //double startAngle = RMath::getNormalizedAngle(a.getStartAngle());
    //double endAngle = RMath::getNormalizedAngle(a.getEndAngle());
    if (startAngle>endAngle) {
        startAngle-=2*M_PI;
    }
    double radius = a.getRadius();
    double EPSILON = 0.00001;

    // Compute the sequence of arc curves, up to PI/2 at a time.  Total arc angle
    // is less than 2PI.

    QList<RSpline> curves;

    double piOverTwo = M_PI_2;
    double segmentationAngle = piOverTwo/8;
    //double segmentationAngle = M_PI/8;
    double sgn = (startAngle < endAngle) ? +1 : -1;

    double a1 = startAngle;
    for (double totalAngle = qMin(twoPI, qAbs(endAngle - startAngle)); totalAngle > EPSILON; ) {
        double a2 = a1 + sgn * qMin(totalAngle, segmentationAngle);
        RSpline sp = RSpline::createBezierFromSmallArc(radius, a1, a2);
        sp.move(a.getCenter());
        if (reversed) {
            sp.reverse();
            curves.prepend(sp);
        }
        else {
            curves.append(sp);
        }
        totalAngle -= qAbs(a2 - a1);
        a1 = a2;
    }

    return curves;
}

/**
 *  Cubic bezier approximation of a circular arc centered at the origin,
 *  from (radians) a1 to a2, where a2-a1 < pi/2.  The arc's radius is r.
 *
 *  Returns an spline approximation.
 *
 *  This algorithm is based on the approach described in:
 *  A. Riškus, "Approximation of a Cubic Bezier Curve by Circular Arcs and Vice Versa,"
 *  Information Technology and Control, 35(4), 2006 pp. 371-378.
 */
RSpline RSpline::createBezierFromSmallArc(double r, double a1, double a2) {
    // Compute all four points for an arc that subtends the same total angle
    // but is centered on the X-axis

    double a = (a2 - a1) / 2.0; //

    double x4 = r * cos(a);
    double y4 = r * sin(a);
    double x1 = x4;
    double y1 = -y4;

    //double k = 0.552284749831;
    //double k = 4.0/3.0*(sqrt(2.0)-1.0);
    //double f = k * tan(a);

    double q1 = x1*x1 + y1*y1;
    double q2 = q1 + x1*x4 + y1*y4;
    double k2 = 4/3 * (sqrt(2 * q1 * q2) - q2) / (x1 * y4 - y1 * x4);

    double x2 = x1 - k2 * y1;
    double y2 = y1 + k2 * x1;
    //double x2 = x1 + f * y4;
    //double y2 = y1 + f * x4;
    double x3 = x2;
    double y3 = -y2;

    // Find the arc points actual locations by computing x1,y1 and x4,y4
    // and rotating the control points by a + a1
    double ar = a + a1;
    double cos_ar = cos(ar);
    double sin_ar = sin(ar);

    QList<RVector> ctrlPts;
    ctrlPts
        << RVector(
            r * cos(a1),
            r * sin(a1)
           )
        << RVector(
            x2 * cos_ar - y2 * sin_ar, 
            x2 * sin_ar + y2 * cos_ar
           )
        << RVector(
            x3 * cos_ar - y3 * sin_ar, 
            x3 * sin_ar + y3 * cos_ar
           )
        << RVector(
            r * cos(a2), 
            r * sin(a2)
           );

//    qDebug() << "ctrlPts: " << ctrlPts[0];
//    qDebug() << "ctrlPts: " << ctrlPts[1];
//    qDebug() << "ctrlPts: " << ctrlPts[2];
//    qDebug() << "ctrlPts: " << ctrlPts[3];

    // this should be cubic but appears to be far off if cubic
    return RSpline(ctrlPts, 2);
}

void RSpline::setZ(double z) {
    bool upd = false;

    for (int i=0; i<controlPoints.size(); i++) {
        if (fabs(controlPoints[i].z)>RS::PointTolerance) {
            controlPoints[i].z = z;
            upd = true;
        }
    }

    for (int i=0; i<fitPoints.size(); i++) {
        if (fabs(fitPoints[i].z)>RS::PointTolerance) {
            fitPoints[i].z = z;
            upd = true;
        }
    }

    if (upd) {
        update();
    }
}

QList<RVector> RSpline::getVectorProperties() const {
    return QList<RVector>() << tangentStart << tangentEnd << controlPoints << fitPoints;
}

QList<double> RSpline::getDoubleProperties() const {
    return QList<double>() << knotVector << weights;
}

QList<int> RSpline::getIntProperties() const {
    return QList<int>() << degree;
}

QList<bool> RSpline::getBoolProperties() const {
    return QList<bool>() << periodic;
}

/**
 * Disabled for splines (bad performance).
 * 20120223: Re-enabled, seems to perform OK, needed by some users.
 */
//RVector RSpline::getClosestPointOnShape(const RVector& p, bool limited) const {
//    return RVector::invalid;
//}

/**
 * Appends a control point.
 */
void RSpline::appendControlPoint(const RVector& point) {
    controlPoints.append(point);
    update();
}

/**
 * Appends the given control points.
 */
void RSpline::appendControlPoints(const QList<RVector>& points) {
    controlPoints.append(points);
    update();
}

/**
 * Removes the last control point.
 *
 * \param upd Update internal spline representation.
 */
void RSpline::removeLastControlPoint() {
    controlPoints.removeLast();
    update();
}

/**
 * Sets the control points of this spline.
 */
void RSpline::setControlPoints(const QList<RVector>& controlPoints) {
    this->controlPoints = controlPoints;
    update();
}

/**
 * \return Control points.
 */
QList<RVector> RSpline::getControlPoints() const {
    return controlPoints;
}

/**
 * \return Control points of internal spline representation (may be closed).
 */
QList<RVector> RSpline::getControlPointsWrapped() const {
    QList<RVector> ret;

    updateInternal();

#ifndef R_NO_OPENNURBS
    ON_3dPoint onp;
    for (int i=0; i<curve.CVCount(); ++i) {
        curve.GetCV(i, onp);
        ret.append(RVector(onp.x, onp.y));
    }
#endif

    return ret;
}

/**
 * \return Number of control points.
 */
int RSpline::countControlPoints() const {
    return controlPoints.size();
}

RVector RSpline::getControlPointAt(int i) const {
    if (i>=0 && i<controlPoints.size()) {
        return controlPoints.at(i);
    }
    return RVector::invalid;
}

/**
 * Appends a fit point.
 */
void RSpline::appendFitPoint(const RVector& point) {
    fitPoints.append(point);
    update();
}

/**
 * Prepends a fit point.
 */
void RSpline::prependFitPoint(const RVector& point) {
    fitPoints.prepend(point);
    update();
}

/**
 * Inserts a fit point at the point on the spline closest to the given position.
 */
void RSpline::insertFitPointAt(const RVector& point) {
    RVector p = getClosestPointOnShape(point);

    // find out T at the point closest to point:
    double t = getTAtPoint(p);

    insertFitPointAt(t, p);
}

void RSpline::insertFitPointAt(double t, const RVector& p) {
    // find out index of fit point before t:
    int index = -1;
    for (int i=0; i<fitPoints.length(); i++) {
        double tc = getTAtPoint(fitPoints[i]);
        if (i==0 && (isClosed() || getStartPoint().equalsFuzzy(getEndPoint()))) {
            // closed spline: two t's for first fit point:
            tc = 0.0;
        }
        //qWarning() << "tc: " << tc;
        if (tc<t) {
            index = i+1;
        }
        else {
            break;
        }
    }

    // point not on spline:
    if (index<0 || index>=fitPoints.length()) {
        if (isClosed()) {
            index = 0;
        }
        else {
            qWarning() << "no point on spline found. t: " << t << ", index: " << index;
            return;
        }
    }

    fitPoints.insert(index, p);
    update();
}

void RSpline::removeFitPointAt(const RVector& point) {
    double minDist = RMAXDOUBLE;
    int index = -1;
    for (int i=0; i<fitPoints.length(); i++) {
        double dist = point.getDistanceTo(fitPoints[i]);
        if (dist<minDist) {
            minDist = dist;
            index = i;
        }
    }

    if (index<0 || index>=fitPoints.length()) {
        return;
    }

    fitPoints.removeAt(index);
    update();
}

/**
 * Removes the last fit point.
 */
void RSpline::removeLastFitPoint() {
    fitPoints.removeLast();
    update();
}

/**
 * Removes the first fit point.
 */
void RSpline::removeFirstFitPoint() {
    fitPoints.removeFirst();
    update();
}

/**
 * Sets the fit points.
 */
void RSpline::setFitPoints(const QList<RVector>& fitPoints) {
    this->fitPoints = fitPoints;
    update();
}

/**
 * \return Fit points.
 */
QList<RVector> RSpline::getFitPoints() const {
    return fitPoints;
}

/**
 * \return Number of fit points.
 */
int RSpline::countFitPoints() const {
    return fitPoints.size();
}

/**
 * \return True if this spline has fit points and is therefore defined
 *      by its fit points, false otherwise.
 */
bool RSpline::hasFitPoints() const {
    return !fitPoints.isEmpty();
}

RVector RSpline::getFitPointAt(int i) const {
    if (i>=0 && i<fitPoints.size()) {
        return fitPoints.at(i);
    }
    return RVector::invalid;
}

/**
 * \return Knot vector, internally calculated and updated.
 */
QList<double> RSpline::getKnotVector() const {
    return knotVector;
}

QList<double> RSpline::getActualKnotVector() const {
#ifndef R_NO_OPENNURBS
    updateInternal();
    QList<double> ret;
    for (int i=0; i<curve.KnotCount(); ++i) {
        ret.append(curve.Knot(i));
    }
    return ret;
#else
    return QList<double>();
#endif
}

/**
 * Sets the knot vector manually. Mainly for importing ready data.
 */
void RSpline::setKnotVector(const QList<double>& knots) {
    knotVector = knots;
    update();
}

void RSpline::appendKnot(double k) {
    knotVector.append(k);
    update();
}

/**
 * \return Knot weights, internally calculated and updated.
 */
QList<double> RSpline::getWeights() const {
    return weights;

    /*
    QList<double> ret;

    for (int i=0; i<curve.CVCount(); ++i) {
        ret.append(curve.Weight(i));
    }
    return ret;
    */
}

/**
 * Sets the degree of this spline (2 or 3 for control point defined spline,
 * 3 for fit point defined spline).
 */
void RSpline::setDegree(int d) {
    degree = d;
    update();
}

/**
 * \return Degree of this spline.
 */
int RSpline::getDegree() const {
    return degree;
}

/**
 * \return Order of this spline (=degree+1).
 */
int RSpline::getOrder() const {
    return degree + 1;
}

void RSpline::setPeriodic(bool on) {
    periodic = on;

    // TODO: tangent support:
//    tangentStart.valid = false;
//    tangentEnd.valid = false;
//    if (on) {
//        if (!fitPoints.isEmpty()) {
//            if (fitPoints.first().equalsFuzzy(fitPoints.last())) {
//                fitPoints.removeLast();
//            }
//        }
//    }

    update();
}

/**
 * \return True if this spline is closed, i.e. start point and end point
 *      are very close to each other.
 */
bool RSpline::isClosed() const {
    return periodic;

    //return curve.IsClosed();

    /*
    if (hasFitPoints()) {
        return fitPoints.first().getDistanceTo(fitPoints.last()) < RS::PointTolerance;
    }
    else {
        //return controlPoints.first().getDistanceTo(controlPoints.last()) < RS::PointTolerance;
        if (controlPoints.count()<degree) {
            return false;
        }

        bool ret = true;
        for (int i=0; i<degree; i++) {
            if (controlPoints.at(i).getDistanceTo(controlPoints.at(controlPoints.count()-degree+i)) > RS::PointTolerance) {
                ret = false;
            }
        }
        return ret;

        //return controlPoints.at(0).getDistanceTo(controlPoints.at(controlPoints.count()-degree)) < RS::PointTolerance &&
        //       controlPoints.at(1).getDistanceTo(controlPoints.at(controlPoints.count()-1)) < RS::PointTolerance
    }
    */
}

bool RSpline::isGeometricallyClosed(double tolerance) const {
    return isClosed() || getStartPoint().getDistanceTo(getEndPoint()) < tolerance;
}

/**
 * \return True if this spline is periodic, i.e. closed and 'smooth'
 *      where start and end connect. The tangents at the start point and
 *      end point are nearly identical.
 */
bool RSpline::isPeriodic() const {
    return periodic;
    /*
    int c = curve.CVCount();
    if (c<=degree) {
        return false;
    }

    if (hasFitPoints()) {
        return periodic;
    }
    else {
        // check if first N control points match with N last control points:
 #ifndef R_NO_OPENNURBS
        for (int i=0; i<degree; i++) {
            ON_3dPoint onp1;
            curve.GetCV(i, onp1);
            RVector p1(onp1.x, onp1.y);

            ON_3dPoint onp2;
            curve.GetCV(curve.CVCount()-degree+i, onp2);
            RVector p2(onp2.x, onp2.y);
            if (p1.getDistanceTo(p2) > RS::PointTolerance) {
                return false;
            }
        }
 #endif
    }

    return true;
    */

//    return periodic;

    //return curve.IsPeriodic();
    /*
    if (!isClosed()) {
        return false;
    }

    double ad = RMath::getAngleDifference180(getDirection1(), getDirection2()+M_PI);
    if (fabs(ad) < RS::AngleTolerance) {
        return true;
    }

    return false;
    */
}

/**
 * \return Tangent angle of spline at start point.
 */
double RSpline::getDirection1() const {
    if (!isValid()) {
        return 0.0;
    }
    updateInternal();

#ifndef R_NO_OPENNURBS
    ON_3dVector ontan = curve.TangentAt(getTMin());
    RVector rtan(ontan.x, ontan.y);
    return rtan.getAngle();
#else
    return 0.0;
#endif
}

/**
 * \return Tangent angle of spline at end point.
 */
double RSpline::getDirection2() const {
    if (!isValid()) {
        return 0.0;
    }
    updateInternal();

#ifndef R_NO_OPENNURBS
    ON_3dVector ontan = curve.TangentAt(getTMax());
    RVector rtan(ontan.x, ontan.y);
    return RMath::getNormalizedAngle(rtan.getAngle() + M_PI);
#else
    return 0.0;
#endif
}

RS::Side RSpline::getSideOfPoint(const RVector& point) const {
    RPolyline pl = toPolyline(16);
    return pl.getSideOfPoint(point);
}

RVector RSpline::getStartPoint() const {
//    if (!isClosed()) {
//        if (hasFitPoints()) {
//            return fitPoints.first();
//        }
//        else if (!controlPoints.isEmpty()) {
//            return controlPoints.first();
//        }
//    }
    return getPointAt(getTMin());
}

void RSpline::setStartPoint(const RVector& v) {
    // TODO: handle fit points
    controlPoints[0] = v;
    update();
}

RVector RSpline::getEndPoint() const {
//    if (!isClosed()) {
//        if (hasFitPoints()) {
//            return fitPoints.last();
//        }
//        else if (!controlPoints.isEmpty()) {
//            return controlPoints.last();
//        }
//    }
    return getPointAt(getTMax());
}

void RSpline::setEndPoint(const RVector& v) {
    // TODO: handle fit points
    controlPoints[controlPoints.size()-1] = v;
    update();
}

/**
 * Sets the start and end tangents.
 */
void RSpline::setTangents(const RVector& start, const RVector& end) {
    tangentStart = start;
    tangentEnd = end;
    update();
}

/**
 * Sets the start tangent.
 */
void RSpline::setTangentAtStart(const RVector& t) {
    tangentStart = t;
    update();
}

/**
 * \return The start tangent.
 */
RVector RSpline::getTangentAtStart() const {
    return tangentStart;
}

/**
 * Sets the end tangent.
 */
void RSpline::setTangentAtEnd(const RVector& t) {
    tangentEnd = t;
    update();
}

/**
 * \return The end tangent.
 */
RVector RSpline::getTangentAtEnd() const {
    return tangentEnd;
}

/**
 * Clears the valud of the start tangent. The start tangent is calculated
 *      and updated internally if not set manually.
 */
void RSpline::unsetTangentAtStart() {
    setTangentAtStart(RVector::invalid);
}

/**
 * Clears the valud of the end tangent. The end tangent is calculated
 *      and updated internally if not set manually.
 */
void RSpline::unsetTangentAtEnd() {
    setTangentAtEnd(RVector::invalid);
}

/**
 * Clears the valud of the start and end tangents. The tangents are calculated
 *      and updated internally if not set manually.
 */
void RSpline::unsetTangents() {
    setTangents(RVector::invalid, RVector::invalid);
}

/**
 * Updates the tangents at the start and end to make the spline periodic.
 */
void RSpline::updateTangentsPeriodic() {
    if (!isValid() || !isClosed()) {
        qWarning() << "RSpline::updateTangentsPeriodic(): "
                      "spline not valid or not closed";
    }

    // TODO: tangent support:
//    RVector lStartTangent = tangentStart;
//    RVector lEndTangent = tangentEnd;

    unsetTangents();

    double tangent1 = getDirection1();
    double tangent2 = RMath::getNormalizedAngle(getDirection2() + M_PI);
    RVector v1 = RVector::createPolar(1.0, tangent1);
    RVector v2 = RVector::createPolar(1.0, tangent2);
    RVector t = (v1 + v2).getNormalized();

    // TODO: tangent support:
//    RVector t1 = t;
//    RVector t2 = t;
//    t1.valid = lStartTangent.valid;
//    t2.valid = lEndTangent.valid;

//    if (!lStartTangent.isValid()) {
//        setTangentAtStart(t1);
//    }
//    else {
//        setTangentAtStart(lStartTangent);
//    }
//    if (!lEndTangent.isValid()) {
//        setTangentAtEnd(t2);
//    }
//    else {
//        setTangentAtEnd(lEndTangent);
//    }
    setTangents(t, t);
}

RPolyline RSpline::approximateWithArcs(double tolerance) const {
    if (hasProxy()) {
        return getSplineProxy()->approximateWithArcs(*this, tolerance);
    }
    return RPolyline();
}

RPolyline RSpline::toPolyline(int segments) const {
    RPolyline ret;

    QList<QSharedPointer<RShape> > lineSegments = getExplodedBezier(segments);
    for (int k=0; k<lineSegments.size(); k++) {
        QSharedPointer<RShape> shape = lineSegments[k];
        if (shape.isNull() || !shape->isDirected()) {
            continue;
        }
        if (k==0) {
            ret.appendVertex(shape->getStartPoint());
        }
        ret.appendVertex(shape->getEndPoint());
    }
    if (isClosed()) {
        ret.setClosed(true);
    }

    return ret;
}

/**
 * \return List of RLines describing this spline.
 */
QList<QSharedPointer<RShape> > RSpline::getExploded(int segments) const {
    if (!exploded.isEmpty() && segments==-1) {
        return exploded;
    }

    //qDebug() << "RSpline::getExploded: segments: " << segments;
    //RDebug::printBacktrace("getExploded:    ");

    //##boundingBox = RBox();

    updateInternal();

    exploded.clear();

    if (!isValid()) {
        //qWarning() << "RSpline::getExploded: invalid spline";
        return exploded;
    }

    if (segments==-1) {
        segments = 8;
    }

    double tMin = getTMin();
    double tMax = getTMax();

    double step = getTDelta() / (controlPoints.size() * segments);

    RVector p1;
    RVector prev = RVector::invalid;
    for (double t = tMin; t<tMax+(step/2.0); t+=step) {
        double tc = qMin(t, tMax);
        p1 = getPointAt(tc);

        if (RMath::isNaN(p1.x) || RMath::isNaN(p1.y)) {
            continue;
        }

        if (prev.isValid()) {
            appendToExploded(RLine(prev, p1));
//            RLine* line = new RLine(prev, p1);
//            exploded.append(QSharedPointer<RShape>(line));
        }
        prev = p1;

        //##boundingBox.growToInclude(p1);
    }

    p1 = getEndPoint();
    if (!RMath::isNaN(p1.x) && !RMath::isNaN(p1.y)) {
        if (prev.isValid()) {
            appendToExploded(RLine(prev, p1));
//            RLine* line = new RLine(prev, p1);
            // prevent zero length line at the end:
//            if (line->getLength()>1.0e-4) {
//                exploded.append(QSharedPointer<RShape>(line));
//            }
        }
    }

    return exploded;
}

/**
 * \return exploded spline, treated as one spline segment, typically only
 * used for bezier spline segments (degree+1 control points).
 */
QList<QSharedPointer<RShape> > RSpline::getExplodedBezier(int segments) const {
    QList<QSharedPointer<RShape> > ret;
    QList<RSpline> bezierSegments = getBezierSegments();
    for (int i=0; i<bezierSegments.length(); i++) {
        ret.append(bezierSegments[i].getExploded(segments));
    }
    return ret;
}

void RSpline::appendToExploded(const RLine& line) const {
    if (line.getLength()<1.0e-6) {
        return;
    }

    if (!exploded.isEmpty()) {
        // compare angle of this sement with last segment and
        // modify last segment if angle is the same (straight line):
        QSharedPointer<RLine> prev = exploded.last().dynamicCast<RLine>();
        if (!prev.isNull()) {
            if (RMath::fuzzyCompare(prev->getAngle(), prev->getStartPoint().getAngleTo(line.getEndPoint()))) {
                prev->setEndPoint(line.getEndPoint());
                return;
            }
        }
    }

    exploded.append(QSharedPointer<RShape>(new RLine(line)));
}

QList<QSharedPointer<RShape> > RSpline::getExplodedWithSegmentLength(double segmentLength) const {
    QList<QSharedPointer<RShape> > ret;
    QList<RSpline> bezierSegments = getBezierSegments();
    for (int i=0; i<bezierSegments.length(); i++) {
        double len = bezierSegments[i].getLength();
        int seg = static_cast<int>(ceil(len / segmentLength));
        ret.append(bezierSegments[i].getExploded(seg));
    }
    return ret;
}

RBox RSpline::getBoundingBox() const {
    if (!isValid()) {
        return RBox();
    }

    if (!boundingBox.isValid()) {
        updateBoundingBox();
    }

    return boundingBox;

    //ON_3dPoint onmin;
    //ON_3dPoint onmax;
    //curve.GetBoundingBox(onmin, onmax);

//    double min[3];
//    double max[3];
//    curve.GetBBox(min, max);

    //ON_BoundingBox bb;
    //curve.GetTightBoundingBox(bb);

    //return RBox(RVector(bb.Min().x, bb.Min().y), RVector(bb.Max().x, bb.Max().y));
    //return RBox(RVector(min[0], min[1]), RVector(max[0], max[1]));
}

double RSpline::getLength() const {
    if (!isValid()) {
        return 0.0;
    }
    if (!dirty && !RMath::isNaN(length)) {
        return length;
    }

    if (hasProxy()) {
        length = splineProxy->getDistanceAtT(*this, getTMax());
    }
    else {
        length = 0.0;
        QList<QSharedPointer<RShape> > shapes = getExploded();
        for (int i=0; i<shapes.size(); i++) {
            QSharedPointer<RShape> shape = shapes[i];
            length += shape->getLength();
        }
    }

    return length;

    // seems to only work in the context of another product which uses OpenNURBS:
    // curve.GetLength(&length);
}

/**
 * \return Point on spline at given position t (0..1).
 */
RVector RSpline::getPointAt(double t) const {
    updateInternal();
#ifndef R_NO_OPENNURBS
    ON_3dPoint p = curve.PointAt(t);
    if (p.IsUnsetPoint()) {
        return RVector::invalid;
    }
    return RVector(p.x, p.y);
#else
    return RVector::invalid;
#endif
}

RVector RSpline::getPointAtDistance(double distance) const {
    double t = getTAtDistance(distance);
    return getPointAt(t);
}

double RSpline::getAngleAt(double distance, RS::From from) const {
    QList<RVector> points = getPointsWithDistanceToEnd(distance, from);
    if (points.length()!=1) {
        return RNANDOUBLE;
    }
    double t = getTAtPoint(points[0]);
    ON_3dVector v = curve.DerivativeAt(t);
    return RVector(v.x, v.y).getAngle();
}

QList<RVector> RSpline::getEndPoints() const {
    QList<RVector> ret;

    ret.append(getStartPoint());
    ret.append(getEndPoint());

    return ret;
}

RVector RSpline::getMiddlePoint() const {
    return getPointAt(getTMin() + (getTDelta()/2.0));
}

QList<RVector> RSpline::getMiddlePoints() const {
    QList<RVector> ret;

    ret.append(getMiddlePoint());

    return ret;
}

QList<RVector> RSpline::getCenterPoints() const {
    return QList<RVector>();
}

QList<RVector> RSpline::getPointsWithDistanceToEnd(double distance, int from) const {
    QList<RVector> ret;

    if (hasProxy()) {
        double t;
        if (from&RS::FromStart) {
            t = splineProxy->getTAtDistance(*this, distance);
            ret << getPointAt(t);
        }
        if (from&RS::FromEnd) {
            t = splineProxy->getTAtDistance(*this, getLength() - distance);
            ret << getPointAt(t);
        }
    }
    else {
        // no spline proxy (not precise, but better than nothing in some cases):
        double length = getLength();
        if (length<=RS::PointTolerance) {
            return ret;
        }

        if (from&RS::FromStart) {
            RVector p = getPointAt(getTMin() + (distance/length*getTDelta()));
            ret.append(p);
        }

        if (from&RS::FromEnd) {
            RVector p = getPointAt(getTMin() + ((length-distance)/length*getTDelta()));
            ret.append(p);
        }
    }

    return ret;
}

QList<RVector> RSpline::getPointCloud(double segmentLength) const {
    RPolyline pl = approximateWithArcs(0.01);
    return pl.getPointCloud(segmentLength);
}

RVector RSpline::getVectorTo(const RVector& point, bool limited, double strictRange) const {
    if (hasProxy()) {
        return splineProxy->getVectorTo(*this, point, limited, strictRange);
    }
    else {
        RVector ret = RVector::invalid;

        QList<QSharedPointer<RShape> > sub = getExploded();
        QList<QSharedPointer<RShape> >::iterator it;
        for (it=sub.begin(); it!=sub.end(); ++it) {
            RVector v = (*it)->getVectorTo(point, limited, strictRange);
            if (v.isValid() && (!ret.isValid() || v.getMagnitude()<ret.getMagnitude())) {
                ret = v;
            }
        }

        return ret;
    }
}

bool RSpline::isOnShape(const RVector& point, bool limited, double tolerance) const {
    if (hasProxy()) {
        double t = getTAtPoint(point);
        RVector p = getPointAt(t);
        return point.getDistanceTo(p) < tolerance;
    }
    else {
        return RShape::isOnShape(point, limited, tolerance);
    }
}

bool RSpline::move(const RVector& offset) {
    for (int i=0; i<controlPoints.size(); i++) {
        controlPoints[i].move(offset);
    }
    for (int i=0; i<fitPoints.size(); i++) {
        fitPoints[i].move(offset);
    }
    update();
    return true;
}

bool RSpline::rotate(double rotation, const RVector& center) {
    if (fabs(rotation) < RS::AngleTolerance) {
        return false;
    }
    for (int i=0; i<controlPoints.size(); i++) {
        controlPoints[i].rotate(rotation, center);
    }
    for (int i=0; i<fitPoints.size(); i++) {
        fitPoints[i].rotate(rotation, center);
    }
    tangentStart.rotate(rotation);
    tangentEnd.rotate(rotation);
    update();
    return true;
}

bool RSpline::scale(const RVector& scaleFactors, const RVector& center) {
    for (int i=0; i<controlPoints.size(); i++) {
        controlPoints[i].scale(scaleFactors, center);
    }
    for (int i=0; i<fitPoints.size(); i++) {
        fitPoints[i].scale(scaleFactors, center);
    }
    update();
    return true;
}

bool RSpline::mirror(const RLine& axis) {
    RVector sp = getStartPoint();
    RVector ep = getEndPoint();

    for (int i=0; i<controlPoints.size(); i++) {
        controlPoints[i].mirror(axis);
    }
    for (int i=0; i<fitPoints.size(); i++) {
        fitPoints[i].mirror(axis);
    }

    RVector absTan = sp+tangentStart;
    absTan.mirror(axis);
    sp.mirror(axis);
    tangentStart = absTan-sp;

    absTan = ep+tangentEnd;
    absTan.mirror(axis);
    ep.mirror(axis);
    tangentEnd = absTan-ep;

    update();

    return true;
}

bool RSpline::flipHorizontal() {
    for (int i=0; i<controlPoints.size(); i++) {
        controlPoints[i].flipHorizontal();
    }
    for (int i=0; i<fitPoints.size(); i++) {
        fitPoints[i].flipHorizontal();
    }
    tangentStart.flipHorizontal();
    tangentEnd.flipHorizontal();
    update();
    return true;
}

bool RSpline::flipVertical() {
    for (int i=0; i<controlPoints.size(); i++) {
        controlPoints[i].flipVertical();
    }
    for (int i=0; i<fitPoints.size(); i++) {
        fitPoints[i].flipVertical();
    }
    tangentStart.flipVertical();
    tangentEnd.flipVertical();
    update();
    return true;
}

bool RSpline::reverse() {
    int k;
    if (!isClosed()) {
        for (k = 0; k < controlPoints.size()/2; k++) {
            controlPoints.swap(k,controlPoints.size()-(1+k));
        }
        for (k = 0; k < fitPoints.size()/2; k++) {
            fitPoints.swap(k,fitPoints.size()-(1+k));
        }
        double t;
        int i, j;
        for(i = 0, j = knotVector.size()-1; i <= j; i++, j--) {
            t = knotVector[i];
            knotVector[i] = -knotVector[j];
            knotVector[j] = -t;
        }
        RVector ts = tangentStart;
        tangentStart = tangentEnd.getNegated();
        tangentEnd = ts.getNegated();
    }
    else {
        if (hasFitPoints()) {
            for (k = 0; k < (int)floor(fitPoints.size()/2.0); k++) {
                fitPoints.swap(k,fitPoints.size()-(1+k));
            }
            // keep start node the same:
            fitPoints.prepend(fitPoints.takeLast());
        }
        else {
            for (k = 0; k < controlPoints.size()/2; k++) {
                controlPoints.swap(k,controlPoints.size()-(1+k));
            }
        }
        updateTangentsPeriodic();
    }
    update();
    return true;
}

bool RSpline::stretch(const RPolyline& area, const RVector& offset) {
    if (!fitPoints.isEmpty()) {
        for (int i=0; i<fitPoints.size(); i++) {
            fitPoints[i].stretch(area, offset);
        }
        update();
        return true;
    }
    return false;
}

QSharedPointer<RShape> RSpline::getTransformed(const QTransform& transform) const {
    QSharedPointer<RSpline> ret = QSharedPointer<RSpline>(clone());

    for (int i=0; i<ret->controlPoints.size(); i++) {
        ret->controlPoints[i].transform2D(transform);
    }
    for (int i=0; i<ret->fitPoints.size(); i++) {
        ret->fitPoints[i].transform2D(transform);
    }

    ret->update();

    return ret;
}

bool RSpline::isValid() const {
    if (!dirty) {
#ifndef R_NO_OPENNURBS
//        enable for opennurbs debugging:
//        ON_wString s;
//        ON_TextLog log(s);
//        if (!curve.IsValid(&log)) {
//            qDebug() << "RSpline::isValid: spline curve is not valid:";
//            QString qs;
//            for (int i=0; i<s.Length(); i++) {
//                qs.append(QChar(s.GetAt(i)));
//            }
//            qDebug() << qs;
//        }
        return curve.IsValid();
#endif
    }

    if (degree<1) {
        qDebug() << "RSpline::isValid: spline not valid: degree: " << degree;
        return false;
    }
    if (hasFitPoints()) {
        // spline with two fit points is line:
        if (fitPoints.count() < 2) {
            //qDebug() << "RSpline::isValid: spline not valid: less than 2 fit points";
            return false;
        }
        return true;
    }
    else {
        if (controlPoints.count() < degree+1) {
            //qDebug() << "RSpline::isValid: spline not valid: less than " << degree+1 << " control points";
            return false;
        }
        return true;
    }
    /*
    bool ret = curve.ctrlPnts().size() > degree &&
           curve.ctrlPnts().size() + degree + 1 == curve.knot().size();
    if (!ret) {
        qWarning() << "RSpine::isValid: false";
    }
    return ret;
    */
    //return true;
}

double RSpline::getTDelta() const {
    return getTMax() - getTMin();
}

double RSpline::getTMin() const {
    updateInternal();

    if (isValid()) {
#ifndef R_NO_OPENNURBS
        return curve.Domain().Min();
#endif
    }

    return 0.0;
}

double RSpline::getTMax() const {
    updateInternal();

    if (isValid()) {
#ifndef R_NO_OPENNURBS
        return curve.Domain().Max();
#endif
    }

    return 0.0;
}

double RSpline::getTAtPoint(const RVector& point) const {
    if (hasProxy()) {
        // TODO: fails for splines with clamped control points in the middle (multiple control points at the same location):
        return splineProxy->getTAtPoint(*this, point);
    }

    return 0.0;
}

double RSpline::getTAtDistance(double distance) const {
    if (hasProxy()) {
        return splineProxy->getTAtDistance(*this, distance);
    }
    return 0.0;
}

double RSpline::getDistanceAtT(double t) const {
    if (hasProxy()) {
        return splineProxy->getDistanceAtT(*this, t);
    }
    return 0.0;
}

QList<RSpline> RSpline::getSegments(const QList<RVector>& points) const {
    return splitAtPoints(points);
}

QList<RVector> RSpline::getDiscontinuities() const {
    updateInternal();

    QList<RVector> ret;

#ifndef R_NO_OPENNURBS
    if (isValid()) {
        for (int c=0; c<=11; c++) {
            double t0=getTMin();
            double t1=getTMax();
            bool found;
            do {
                double t;
                found = curve.GetNextDiscontinuity((ON::continuity)c, t0, t1, &t);
                if (found) {
                    ret.append(getPointAt(t));
                    t0=t;
                }
            } while(found);
        }
    }
#endif

    return ret;
}

RSpline RSpline::simplify(double tolerance) {
    if (hasProxy()) {
        return splineProxy->simplify(*this, tolerance);
    }
    return *this;
}

void RSpline::invalidate() const {
#ifndef R_NO_OPENNURBS
    curve.Destroy();
    //curve.Initialize();
#endif
    exploded.clear();
    length = RNANDOUBLE;
}

void RSpline::updateInternal() const {
    if (!dirty || updateInProgress) {
        return;
    }

    dirty = false;
    updateInProgress = true;

    if (degree<1) {
        invalidate();
        qWarning() << "RSpline::updateInternal: invalid degree: " << degree;
        updateInProgress = false;
        return;
    }

    exploded.clear();
    length = RNANDOUBLE;

    // if fit points are known, update from fit points, otherwise from
    // control points:
    // TODO: use fitpoints from DXF/DWG file if possible (fit points might not correspond to control points):
    if (fitPoints.size()==0) {
        updateFromControlPoints();
    }
    else {
        updateFromFitPoints();
    }

    //updateBoundingBox();
    boundingBox = RBox();
    //getExploded();

    updateInProgress = false;
}

void RSpline::updateFromControlPoints() const {
#ifndef R_NO_OPENNURBS
    if (controlPoints.size()<degree+1) {
        invalidate();
        qWarning() << "RSpline::updateFromControlPoints: not enough control points: "
                   << controlPoints.size();
        return;
    }

    // periodic:
    if (periodic && !hasFitPoints()) {
        ON_3dPoint* points = new ON_3dPoint[controlPoints.size()];
        for (int i=0; i<controlPoints.size(); ++i) {
            RVector cp = controlPoints.at(i);
            points[i] = ON_3dPoint(cp.x, cp.y, cp.z);
        }
        curve.CreatePeriodicUniformNurbs(3, getOrder(), controlPoints.size(), points);
        delete[] points;
    }

    // open or from fit points:
    else {
        curve.Create(3, false, getOrder(), controlPoints.size());

        // setting control points:
        for (int i=0; i<controlPoints.size(); ++i) {
            RVector cp = controlPoints.at(i);
            ON_3dPoint onp(cp.x, cp.y, cp.z);
            curve.SetCV(i, onp);
            //qDebug() << "RSpline: controlPoints[" << i << "]: " << cp;
        }

        bool knotCondition = (knotVector.size() == getOrder() + controlPoints.size() - 2);
        //knotCondition = true;

        // genetate knot vector automatically:
        if (knotVector.isEmpty() || !knotCondition) {
//            if (!knotVector.isEmpty()) {
//                qDebug() << "RSpline: knotVector ignored";
//                qDebug() << "RSpline:   knots: " << knotVector.size();
//                qDebug() << "RSpline:   order: " << getOrder();
//                qDebug() << "RSpline:   controlPoints: " << controlPoints.size();
//            }

            int si = ON_KnotCount(getOrder(), controlPoints.size());
            double* knot = new double[si];
            //ON_MakePeriodicUniformKnotVector(getOrder(), controlPoints.size(), knot);
            ON_MakeClampedUniformKnotVector(getOrder(), controlPoints.size(), knot);
            for (int i=0; i<si; ++i) {
//                qDebug() << "RSpline: knot[" << i << "]: " << knot[i];
                curve.SetKnot(i, knot[i]);
            }
            delete[] knot;
        }
        else {
            int k=0;
            for (int i=0; i<knotVector.count(); ++i) {
                //qDebug() << "RSpline: knot[" << i << "]: " << knotVector.at(i);
                bool ok = curve.SetKnot(k++, knotVector.at(i));
                if (!ok) {
                    //qDebug() << "RSpline: knot[" << i << "]: NOT set";
                }
            }
        }
    }

    //##getExploded();
#endif
}


/**
 * Closes this spline and makes it periodic if it isn't already.
 */
/*void RSpline::close() {
    if (hasFitPoints()) {
        if (!isValid()) {
            return;
        }

        if (isClosed() && isPeriodic()) {
            return;
        }

        RVector fp0 = getFitPoints().at(0);
        appendFitPoint(fp0);
        updateTangentsPeriodic();
    }
    else {
        ON_3dPoint* points = new ON_3dPoint[controlPoints.size()];
        for (int i=0; i<controlPoints.size(); ++i) {
            RVector cp = controlPoints.at(i);
            points[i] = ON_3dPoint(cp.x, cp.y, cp.z);
        }
        curve.CreatePeriodicUniformNurbs(3, getOrder(), controlPoints.size(), points);
        delete[] points;

        / *
        int si = controlPoints.size() + degree + 1;
        PlVector_double knot(si-1);
        double v=0.0;
        for (int i=0; i<si-1; ++i) {
            knot[i] = v;
            //qDebug() << "knot[<< " << i << "]: " << knot[i];
            v+=1.0/(si-2);
        }

        Vector_HPoint2Dd pointsWrapped;
        PlVector_double knotWrapped;
        PLib::wrapPointVectorH(curve.ctrlPnts(),degree,pointsWrapped);
        PLib::knotAveragingClosed(knot,degree,knotWrapped);

        v = 0.0;
        for (int i=0; i<knotWrapped.n(); ++i) {
            knotWrapped[i] = v;
            //qDebug() << "knotWrapped[<< " << i << "]: " << knotWrapped[i];
            v+=1.0/(knotWrapped.n()-1);
        }

        curve.reset(pointsWrapped, knotWrapped, degree);

        controlPoints.clear();
        Vector_HPoint2Dd ctrlPts = curve.ctrlPnts();
        Vector_HPoint2Dd::iterator it;
        for (it=ctrlPts.begin(); it!=ctrlPts.end(); ++it) {
            PLib::HPoint2Dd p = *it;
            controlPoints.append(RVector(p.x(), p.y()));
        }

        knotVector.clear();
        PlVector_double knotV = curve.knot();
        PlVector_double::iterator it2;
        for (it2=knotV.begin(); it2!=knotV.end(); it2++) {
            double v = *it2;
            knotVector.append(v);
        }

        updateBoundingBox();
        * /
    }
}
*/

/**
 * Updates the internal spline data from \c fitPoints.
 * Degree is always corrected to 3rd degree.
 */
void RSpline::updateFromFitPoints() const {
    // spline with two fit points is line:
    if (fitPoints.size()<2) {
        invalidate();
        return;
    }

    // call into plugin
    if (hasProxy()) {
        RSpline spline = splineProxy->updateFromFitPoints(*this);
//        qDebug() << "tan start before:" << this->tangentStart;
//        qDebug() << "tan start:" << spline.tangentStart;
        this->degree = spline.degree;
        this->periodic = spline.periodic;
        this->controlPoints = spline.controlPoints;
        this->knotVector = spline.knotVector;
        this->weights = spline.weights;
        this->tangentStart = spline.tangentStart;
        this->tangentEnd = spline.tangentEnd;
        this->curve = spline.curve;
        this->dirty = false;
    }
    else {
        invalidate();
        return;
    }
}

/**
 * Updates the internal bounding box.
 */
void RSpline::updateBoundingBox() const {
    //getExploded();
    RPainterPath pp;
    pp.addSpline(*this);
    boundingBox = pp.getBoundingBox();
}

/**
 * \return List of bezier spline segments which together represent this curve.
 */
QList<RSpline> RSpline::getBezierSegments(const RBox& queryBox) const {
    int ctrlCount = countControlPoints();

    // spline is a single bezier segment:
    if (ctrlCount==getDegree()+1) {
        return QList<RSpline>() << *this;
    }

    updateInternal();

    QList<RSpline> ret;
#ifndef R_NO_OPENNURBS
    if (ctrlCount>0) {
        ON_NurbsCurve* dup = dynamic_cast<ON_NurbsCurve*>(curve.DuplicateCurve());
        if (dup==NULL) {
            return ret;
        }

        dup->MakePiecewiseBezier();
        for (int i=0; i<=dup->CVCount() - dup->Order(); ++i) {
            ON_BezierCurve bc;
            if (!dup->ConvertSpanToBezier(i, bc)) {
                continue;
            }

            QList<RVector> ctrlPts;
            for (int cpi=0; cpi<bc.CVCount(); cpi++) {
                ON_3dPoint onp;
                bc.GetCV(cpi, onp);
                ctrlPts.append(RVector(onp.x, onp.y, onp.z));
            }
            RSpline bezierSegment(ctrlPts, degree);

            if (!queryBox.isValid() || queryBox.intersects(bezierSegment.getBoundingBox())) {
                ret.append(bezierSegment);
            }
        }
        delete dup;
    }
 #endif

    return ret;
}

RS::Ending RSpline::getTrimEnd(const RVector& trimPoint, const RVector& clickPoint) {
    double tAtClickPoint = getTAtPoint(clickPoint);
    double tAtTrimPoint = getTAtPoint(trimPoint);

    if (tAtTrimPoint < tAtClickPoint) {
        return RS::EndingStart;
    }
    else {
        return RS::EndingEnd;
    }
}

bool RSpline::trimStartPoint(const RVector& trimPoint, const RVector& clickPoint, bool extend) {
    Q_UNUSED(clickPoint)
    Q_UNUSED(extend)
    if (!isValid()) {
        return false;
    }
    if (trimPoint.equalsFuzzy(getStartPoint())) {
        return true;
    }
    if (trimPoint.equalsFuzzy(getEndPoint())) {
        this->invalidate();
        return true;
    }

    QList<RSpline> splines = splitAtPoints(QList<RVector>() << trimPoint);
    if (splines.length()>1) {
        copySpline(splines[1]);
    }
    update();
    return true;
}

bool RSpline::trimEndPoint(const RVector& trimPoint, const RVector& clickPoint, bool extend) {
    Q_UNUSED(clickPoint)
    Q_UNUSED(extend)
    if (!isValid()) {
        return false;
    }
    if (trimPoint.equalsFuzzy(getStartPoint())) {
        this->invalidate();
        return true;
    }
    if (trimPoint.equalsFuzzy(getEndPoint())) {
        return true;
    }

    QList<RSpline> splines = splitAtPoints(QList<RVector>() << trimPoint);
    if (splines.length()>0) {
        copySpline(splines[0]);
    }
    update();
    return true;
}

double RSpline::getDistanceFromStart(const RVector& p) const {
    double t = getTAtPoint(p);
    return getDistanceAtT(t);
}

QList<RSpline> RSpline::splitAtPoints(const QList<RVector>& points) const {
    QList<double> params;
    for (int i=0; i<points.length(); i++) {
        params.append(getTAtPoint(points[i]));
    }
    return splitAtParams(params);
}

QList<RSpline> RSpline::splitAtParams(const QList<double>& params) const {
    if (hasProxy()) {
        return splineProxy->split(*this, params);
    }
    return QList<RSpline>();
}

void RSpline::update() const {
    dirty = true;
    boundingBox = RBox();
    exploded.clear();
}


/**
 * \return New spline that covers this spline from d1 to d2, where
 *      d1 and d2 are distances from the start point of this spline.
 */
//RSpline RSpline::getSubSpline(double d1, double d2) const {
    /*
    double u1 = d1 / getLength() * getTMax();
    //double u2 = d2 / getLength();
    PLib::NurbsCurve_2Dd curve1;
    PLib::NurbsCurve_2Dd curve2;
    curve.splitAt(u1, curve1, curve2);
    double u2 = (d2 - d1) / curve2.length() * curve2.knot(curve2.knot().n()-1-degree);
    PLib::NurbsCurve_2Dd curve3;
    PLib::NurbsCurve_2Dd curve4;
    curve2.splitAt(u2, curve3, curve4);

    return RSpline::createFrom(curve3);
    */
    //return RSpline();
//}

/**
 * \internal
 */
/*
RSpline RSpline::createFrom(PLib::NurbsCurve_2Dd& sp) {
    QList<RVector> ctrlPts;

    Vector_HPoint2Dd cps = sp.ctrlPnts();
    Vector_HPoint2Dd::iterator it;
    for (it=cps.begin(); it!=cps.end(); it++) {
        PLib::HPoint2Dd p = *it;
        ctrlPts.append(RVector(p.x(), p.y()));
    }

    return RSpline(ctrlPts, sp.degree());
}
*/

QList<QSharedPointer<RShape> > RSpline::splitAt(const QList<RVector>& points) const {
    if (points.length()==0 || !RSpline::hasProxy()) {
        return RShape::splitAt(points);
    }

    QList<QSharedPointer<RShape> > ret;

    QMap<double, RVector> sortable;
    for (int i=0; i<points.length(); i++) {
        double t = getTAtPoint(points[i]);
        sortable.insert(t, points[i]);
    }

    QList<double> keys = sortable.keys();
#if QT_VERSION > 0x050000
    std::sort(keys.begin(), keys.end());
#else
    qSort(keys);
#endif

    QList<RVector> sortedPoints;
    for (int i=0; i<keys.length(); i++) {
        QList<RVector> values = sortable.values(keys[i]);
        for (int k=0; k<values.length(); k++) {
            sortedPoints.append(values[k]);
        }
    }

    QList<RSpline> subSplines = splitAtPoints(sortedPoints);
    for (int i=0; i<subSplines.length(); i++) {
        ret.append(QSharedPointer<RShape>(subSplines[i].clone()));
    }
    return ret;
}

QList<RVector> RSpline::getSelfIntersectionPoints() const {
    return getIntersectionPointsSS(*this, *this, true, true);
}

void RSpline::print(QDebug dbg) const {
    dbg.nospace() << "RSpline(";
    RShape::print(dbg);

    dbg.nospace() << ", degree: " << getDegree();
    dbg.nospace() << ", dirty: " << dirty;
    dbg.nospace() << ", order: " << getOrder();
    dbg.nospace() << ", closed: " << isClosed();
    dbg.nospace() << ", periodic: " << isPeriodic();
    dbg.nospace() << ", start point: " << getStartPoint();
    dbg.nospace() << ", end point: " << getEndPoint();
    dbg.nospace() << ", start tan: " << getTangentAtStart();
    dbg.nospace() << ", end tan: " << getTangentAtEnd();
    dbg.nospace() << ", t_min: " << getTMin();
    dbg.nospace() << ", t_max: " << getTMax();

    QList<RVector> controlPoints = getControlPointsWrapped();
    dbg.nospace() << ",\ncontrolPoints (" << controlPoints.count() << "): ";
    for (int i=0; i<controlPoints.count(); ++i) {
        dbg.nospace() << i << ": " << controlPoints.at(i) << ", ";
    }

    QList<RVector> fitPoints = getFitPoints();
    dbg.nospace() << ",\nfitPoints (" << fitPoints.count() << "): ";
    for (int i=0; i<fitPoints.count(); ++i) {
        dbg.nospace() << i << ": " << fitPoints.at(i) << ", ";
    }

    QList<double> knotVector = getKnotVector();
    dbg.nospace() << ",\nknots (" << knotVector.count() << "): ";
    for (int i=0; i<knotVector.count(); ++i) {
        dbg.nospace() << i << ": " << knotVector.at(i) << ", ";
    }

    knotVector = getActualKnotVector();
    dbg.nospace() << ",\ninternally used knots (" << knotVector.count() << "): ";
    for (int i=0; i<knotVector.count(); ++i) {
        dbg.nospace() << i << ": " << knotVector.at(i) << ", ";
    }
}
