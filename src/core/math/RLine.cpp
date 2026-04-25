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

#include <QDebug>

#include "RLine.h"
#include "RBox.h"
#include "RPolyline.h"
#include "RTriangle.h"

/**
 * Creates a line object with invalid start and end points.
 */
RLine::RLine() :
    startPoint(RVector::invalid),
    endPoint(RVector::invalid) {
}

/**
 * Creates a line from two coordinate pairs.
 */
RLine::RLine(double x1, double y1, double x2, double y2) :
    startPoint(x1, y1),
    endPoint(x2, y2) {
}

/**
 * Creates a line object with the given start and end point.
 */
RLine::RLine(const RVector& startPoint, const RVector& endPoint) :
    startPoint(startPoint),
    endPoint(endPoint) {
}

/**
 * Creates a line from a start point, angle (in rad) and length.
 */
RLine::RLine(const RVector& startPoint, double angle, double distance) :
    startPoint(startPoint) {

    endPoint = startPoint + RVector::createPolar(distance, angle);
}

/**
 * Sets the Z coordinate of both endpoints.
 */
void RLine::setZ(double z) {
    startPoint.z = z;
    endPoint.z = z;
}

/**
 * \return List of the start and end point (used for property-based transformations).
 */
QList<RVector> RLine::getVectorProperties() const {
    return QList<RVector>() << startPoint << endPoint;
}

/**
 * \return True if both endpoints are valid and finite.
 */
bool RLine::isValid() const {
    return startPoint.isSane() && endPoint.isSane();
}

/**
 * \return Length of the line.
 */
double RLine::getLength() const {
    return startPoint.getDistanceTo(endPoint);
}

/**
 * Sets the length of the line, adjusting the end point (fromStart=true) or
 * the start point (fromStart=false), keeping the other endpoint fixed.
 */
void RLine::setLength(double l, bool fromStart) {
    if (fromStart) {
        endPoint = startPoint + RVector::createPolar(l, getAngle());
    }
    else {
        startPoint = endPoint - RVector::createPolar(l, getAngle());
    }
}

/**
 * \return Angle of the line from start to end point (in rad).
 */
double RLine::getAngle() const {
    return startPoint.getAngleTo(endPoint);
}

/**
 * Sets the angle of the line (in rad), keeping start point and length fixed.
 */
void RLine::setAngle(double a) {
    endPoint = startPoint + RVector::createPolar(getLength(), a);
}

/**
 * \return True if this line is parallel to the given line (same or opposite direction).
 */
bool RLine::isParallel(const RLine& line) const {
    double a = getAngle();
    double oa = line.getAngle();

    return RMath::isSameDirection(a, oa) || RMath::isSameDirection(a, oa + M_PI);
}

/**
 * \return True if this line and the given line are collinear (lie on the same infinite line).
 * Note: the triangle area tolerance comparison is in square units while RS::PointTolerance
 * is a linear unit; this is an intentional simplification that works for typical CAD tolerances.
 */
bool RLine::isCollinear(const RLine& line) const {
    // Three points are collinear if the area of the triangle they form is zero:
    if (RTriangle(startPoint, endPoint, line.getStartPoint()).getArea() > RS::PointTolerance) {
        return false;
    }

    if (RTriangle(startPoint, endPoint, line.getEndPoint()).getArea() > RS::PointTolerance) {
        return false;
    }

    return true;
}

/**
 * \return True if the line is vertical.
 * If the start and end points of the line are identical, the line is both vertical and horizontal.
 */
bool RLine::isVertical(double tolerance) const {
    return RMath::fuzzyCompare(startPoint.x, endPoint.x, tolerance);
}

/**
 * \return True if the line is horizontal.
 * If the start and end points of the line are identical, the line is both vertical and horizontal.
 */
bool RLine::isHorizontal(double tolerance) const {
    return RMath::fuzzyCompare(startPoint.y, endPoint.y, tolerance);
}

/**
 * \return Direction angle at the start of the line (start towards end, in rad).
 */
double RLine::getDirection1() const {
    return startPoint.getAngleTo(endPoint);
}

/**
 * \return Direction angle at the end of the line (end towards start, in rad).
 */
double RLine::getDirection2() const {
    return endPoint.getAngleTo(startPoint);
}

/**
 * \return Start point of the line.
 */
RVector RLine::getStartPoint() const {
    return startPoint;
}

/**
 * Sets the start point of the line.
 */
void RLine::setStartPoint(const RVector& vector) {
    startPoint = vector;
}

/**
 * \return End point of the line.
 */
RVector RLine::getEndPoint() const {
    return endPoint;
}

/**
 * Sets the end point of the line.
 */
void RLine::setEndPoint(const RVector& vector) {
    endPoint = vector;
}

/**
 * \return Midpoint of the line.
 */
RVector RLine::getMiddlePoint() const {
    return (startPoint + endPoint) / 2.0;
}

/**
 * \return Axis-aligned bounding box of the line.
 */
RBox RLine::getBoundingBox() const {
    return RBox(RVector::getMinimum(startPoint, endPoint), RVector::getMaximum(
            startPoint, endPoint));
}

/**
 * \return List containing start and end point.
 */
QList<RVector> RLine::getEndPoints() const {
    QList<RVector> ret;
    ret.append(startPoint);
    ret.append(endPoint);
    return ret;
}

/**
 * \return List containing the midpoint of the line.
 */
QList<RVector> RLine::getMiddlePoints() const {
    QList<RVector> ret;
    ret.append(getMiddlePoint());
    return ret;
}

/**
 * \return Same as getMiddlePoints() (center = midpoint for a line).
 */
QList<RVector> RLine::getCenterPoints() const {
    return getMiddlePoints();
}

/**
 * \return Points at the given distance from the start and/or end of the line,
 *         measured along the line direction (controlled by the \c from flags).
 */
QList<RVector> RLine::getPointsWithDistanceToEnd(double distance, int from) const {
    QList<RVector> ret;

    if (from&RS::FromStart) {
        RVector normalStart = (endPoint-startPoint).getNormalized();
        ret.append(startPoint + normalStart*distance);
    }
    if (from&RS::FromEnd) {
        RVector normalEnd = (startPoint-endPoint).getNormalized();
        ret.append(endPoint + normalEnd*distance);
    }

    return ret;
}

/**
 * \return Points sampled along the line at intervals of \c segmentLength,
 *         always including start and end points.
 */
QList<RVector> RLine::getPointCloud(double segmentLength) const {
    QList<RVector> ret;
    ret.append(startPoint);
    double len = getLength();
    if (segmentLength > len / 10000.0) {
        for (double d = segmentLength; d < len; d += segmentLength) {
            ret.append(getPointWithDistanceToStart(d));
        }
    }
    ret.append(endPoint);
    return ret;
}

/**
 * \return Angle of the line at the given distance from the given end (always constant for a line).
 */
double RLine::getAngleAt(double distance, RS::From from) const {
    Q_UNUSED(distance)
    Q_UNUSED(from)

    return getAngle();
}

/**
 * \return Vector from the closest point on this line to \c point.
 *         The projection is done in 2D (XY plane). When \c limited is true,
 *         the closest point is clamped to the line segment; when the projection
 *         falls outside the segment, the nearest endpoint vector is returned
 *         only if it is within \c strictRange. Returns an invalid vector if out of range.
 */
RVector RLine::getVectorTo(const RVector& point, bool limited, double strictRange) const {

    RVector ae = (endPoint - startPoint).get2D();
    RVector ap = (point - startPoint).get2D();

    if (ae.getMagnitude2D() < 1.0e-6) {
        return RVector::invalid;
    }

    if (ap.getMagnitude2D() < 1.0e-6) {
        // distance to start point is very small:
        return RVector(0,0);
    }

    double b = RVector::getDotProduct(ap, ae) / RVector::getDotProduct(ae, ae);

    if (limited && (b < 0 || b > 1.0)) {
        // orthogonal to line does not cross line, use distance to end point:
        RVector ret = getVectorFromEndpointTo(point);
        if (ret.getMagnitude()<strictRange) {
            return ret;
        }
        else {
            // not within given range:
            return RVector::invalid;
        }
    }

    RVector closestPoint = startPoint + ae * b;

    return point - closestPoint;
}

/**
 * \return Which side of the line the given point is on (LeftHand or RightHand),
 *         relative to the direction from start to end.
 */
RS::Side RLine::getSideOfPoint(const RVector& point) const {
    double entityAngle = getAngle();
    double angleToCoord = startPoint.getAngleTo(point);
    double angleDiff = RMath::getAngleDifference(entityAngle, angleToCoord);

    if (angleDiff<M_PI) {
        return RS::LeftHand;
    }
    else {
        return RS::RightHand;
    }
}


/**
 * Clips this line to the given 2D bounding box using the Liang-Barsky algorithm.
 * Sets both endpoints to invalid if the line is entirely outside the box.
 */
void RLine::clipToXY(const RBox& box) {
    double x1 = startPoint.x;
    double y1 = startPoint.y;
    double x2 = endPoint.x;
    double y2 = endPoint.y;
    double xmin = box.getMinimum().x;
    double ymin = box.getMinimum().y;
    double xmax = box.getMaximum().x;
    double ymax = box.getMaximum().y;

    double deltaX, deltaY, p, q;
    double u1 = 0.0, u2 = 1.0;
    double r;

    deltaX = (x2 - x1);
    deltaY = (y2 - y1);

    // left edge, right edge, bottom edge and top edge checking
    double pPart[] = {-1 * deltaX, deltaX, -1 * deltaY, deltaY};
    double qPart[] = {x1 - xmin, xmax - x1, y1 - ymin, ymax - y1};

    bool accept = true;

    for (int i=0; i<4; i++) {
        p = pPart[i];
        q = qPart[i];

        if (p == 0) {
            // line is parallel to this clipping edge
            if (q < 0) {
                accept = false;
                break;
            }
            continue;  // parallel and inside: skip to next edge
        }

        r = q/p;

        if (p<0) {
            u1=qMax(u1, r);
        }

        if (p>0) {
            u2 = qMin(u2, r);
        }

        if (u1>u2) {
            accept = false;
            break;
        }
    }

    if (accept) {
        if (u2 < 1) {
            x2 = x1 + u2 * deltaX;
            y2 = y1 + u2 * deltaY;
        }
        if (u1 > 0) {
            x1 = x1 + u1 * deltaX;
            y1 = y1 + u1 * deltaY;
        }

        startPoint = RVector(x1, y1);
        endPoint = RVector(x2, y2);
    }
    else {
        startPoint = RVector::invalid;
        endPoint = RVector::invalid;
    }
}

/**
 * Moves the line by the given offset. Returns false if the offset is invalid or negligibly small.
 */
bool RLine::move(const RVector& offset) {
    if (!offset.isValid() || offset.getSquaredMagnitude() < RS::PointTolerance * RS::PointTolerance) {
        return false;
    }
    startPoint += offset;
    endPoint += offset;
    return true;
}

/**
 * Rotates the line around \c center by \c rotation (in rad).
 * Returns false if the rotation angle is negligibly small.
 */
bool RLine::rotate(double rotation, const RVector& center) {
    if (fabs(rotation) < RS::AngleTolerance) {
        return false;
    }
    startPoint.rotate(rotation, center);
    endPoint.rotate(rotation, center);
    return true;
}

/**
 * Scales the line by \c scaleFactors around \c center.
 */
bool RLine::scale(const RVector& scaleFactors, const RVector& center) {
    startPoint.scale(scaleFactors, center);
    endPoint.scale(scaleFactors, center);
    return true;
}

/**
 * Mirrors the line at the given axis line.
 */
bool RLine::mirror(const RLine& axis) {
    startPoint.mirror(axis);
    endPoint.mirror(axis);
    return true;
}

/**
 * Mirrors the line at the Y-axis (flips X coordinates).
 */
bool RLine::flipHorizontal() {
    startPoint.flipHorizontal();
    endPoint.flipHorizontal();
    return true;
}

/**
 * Mirrors the line at the X-axis (flips Y coordinates).
 */
bool RLine::flipVertical() {
    startPoint.flipVertical();
    endPoint.flipVertical();
    return true;
}

/**
 * Swaps start and end point, reversing the line direction.
 */
bool RLine::reverse() {
    RMath::swap(startPoint, endPoint);
    return true;
}

/**
 * Moves the start and/or end point by \c offset if they lie inside \c area.
 */
bool RLine::stretch(const RPolyline& area, const RVector& offset) {
    bool ret = false;

    if (area.contains(startPoint, true)) {
        startPoint += offset;
        ret = true;
    }
    if (area.contains(endPoint, true)) {
        endPoint += offset;
        ret = true;
    }

    return ret;
}

/**
 * Moves the line so that the start point coincides with \c dest.
 */
bool RLine::moveTo(const RVector& dest) {
    RVector offset = dest - startPoint;
    return move(offset);
}

/**
 * \return A new line with both endpoints transformed by the given 2D transformation matrix.
 */
QSharedPointer<RShape> RLine::getTransformed(const QTransform& transform) const {
    return QSharedPointer<RShape>(new RLine(startPoint.getTransformed2D(transform), endPoint.getTransformed2D(transform)));
}

/**
 * \return Which end of the line to trim, based on where the click point is relative
 *         to the trim point. Returns EndingStart if the click is closer to the start direction.
 */
RS::Ending RLine::getTrimEnd(const RVector& trimPoint, const RVector& clickPoint) {
    double lineAngle = getAngle();
    double angleToClickPoint = trimPoint.getAngleTo(clickPoint);
    double angleDifference = fabs(RMath::getAngleDifference180(lineAngle, angleToClickPoint));

    if (angleDifference < M_PI / 2.0) {
        return RS::EndingStart;
    } else {
        return RS::EndingEnd;
    }
}

/**
 * Moves the start point to the closest point on the line to \c trimPoint.
 */
bool RLine::trimStartPoint(const RVector& trimPoint, const RVector& clickPoint, bool extend) {
    Q_UNUSED(clickPoint)
    Q_UNUSED(extend)
    RVector tp = getClosestPointOnShape(trimPoint, false);
    if (!tp.isValid()) {
        return false;
    }
    setStartPoint(tp);
    return true;
}

/**
 * Moves the end point to the closest point on the line to \c trimPoint.
 */
bool RLine::trimEndPoint(const RVector& trimPoint, const RVector& clickPoint, bool extend) {
    Q_UNUSED(clickPoint)
    Q_UNUSED(extend)
    RVector tp = getClosestPointOnShape(trimPoint, false);
    if (!tp.isValid()) {
        return false;
    }
    setEndPoint(tp);
    return true;
}

/**
 * \return Signed arc-length distance from the start point to the projection of \c p
 *         onto the (infinite) line. Positive in the line direction, negative behind the start.
 */
double RLine::getDistanceFromStart(const RVector& p) const {
    RVector p2 = getClosestPointOnShape(p, false);
    double ret = startPoint.getDistanceTo(p2);
    double angle = startPoint.getAngleTo(p2);
    if (RMath::isSameDirection(getAngle(), angle, M_PI/2)) {
        return ret;
    }
    else {
        return -ret;
    }
}

/**
 * \return This line split into segments at the given points.
 *         Points are sorted by distance from the start point. Duplicate or
 *         endpoint-coincident points are handled gracefully.
 */
QList<QSharedPointer<RShape> > RLine::splitAt(const QList<RVector>& points) const {
    if (points.length()==0) {
        return RShape::splitAt(points);
    }

    QList<QSharedPointer<RShape> > ret;

    QList<RVector> sortedPoints = RVector::getSortedByDistance(points, startPoint);

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

        ret.append(QSharedPointer<RShape>(new RLine(sortedPoints[i], sortedPoints[i+1])));
    }

    return ret;
}

/**
 * Writes a human-readable representation of this line to \c dbg.
 */
void RLine::print(QDebug dbg) const {
//    dbg.nospace() << "RLine("
//        << startPoint.x << "," << startPoint.y << " - "
//        << endPoint.x << "," << endPoint.y << ")";
    dbg.nospace() << "RLine(";
    RShape::print(dbg);
    dbg.nospace() << ", startPoint: " << getStartPoint() << ", endPoint: "
            << getEndPoint() << ")";
}
