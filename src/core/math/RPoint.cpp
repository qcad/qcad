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

#include "RBox.h"
#include "RPoint.h"
#include "RLine.h"
#include "RDebug.h"

/**
 * Creates a point object with an invalid position
 */
RPoint::RPoint() {
}

//RPoint::RPoint(const RPoint& other) : RShape() {
//    this->position = other.position;
//}

RPoint::RPoint(double x, double y) :
    position(x, y) {
}

/**
 * Creates a point object with the given position.
 *
 * \param position the position
 *
 */
RPoint::RPoint(const RVector& position) :
    position(position) {
}

RPoint::~RPoint() {
}

void RPoint::setZ(double z) {
    position.z = z;
}

QList<RVector> RPoint::getVectorProperties() const {
    return QList<RVector>() << position;
}

RBox RPoint::getBoundingBox() const {
    return RBox(position, position);
}

double RPoint::getLength() const {
    return 0.0;
}

QList<RVector> RPoint::getEndPoints() const {
    QList<RVector> ret;
    ret.append(position);
    return ret;
}

QList<RVector> RPoint::getMiddlePoints() const {
    QList<RVector> ret;
    ret.append(position);
    return ret;
}

QList<RVector> RPoint::getCenterPoints() const {
    QList<RVector> ret;
    ret.append(position);
    return ret;
}

QList<RVector> RPoint::getPointsWithDistanceToEnd(double distance, int from) const {
    Q_UNUSED(distance)
    Q_UNUSED(from)

    QList<RVector> ret;
    return ret;
}

QList<RVector> RPoint::getPointCloud(double segmentLength) const {
    Q_UNUSED(segmentLength)

    QList<RVector> ret;
    ret.append(getPosition());
    return ret;
}

double RPoint::getAngleAt(double distance, RS::From from) const {
    Q_UNUSED(distance)
    Q_UNUSED(from)
    return RNANDOUBLE;
}

RVector RPoint::getVectorTo(const RVector& point, bool limited, double strictRange) const {
    Q_UNUSED(limited)
    Q_UNUSED(strictRange)

    return point - position;
}

bool RPoint::move(const RVector& offset) {
    if (!offset.isValid() || offset.getMagnitude() < RS::PointTolerance) {
        return false;
    }
    position += offset;
    return true;
}

bool RPoint::rotate(double rotation, const RVector& center) {
    if (fabs(rotation) < RS::AngleTolerance) {
        return false;
    }
    position.rotate(rotation, center);
    return true;
}

bool RPoint::scale(const RVector& scaleFactors, const RVector& center) {
    position.scale(scaleFactors, center);
    return true;
}

bool RPoint::mirror(const RLine& axis) {
    position.mirror(axis);
    return true;
}

bool RPoint::flipHorizontal() {
    position.flipHorizontal();
    return true;
}

bool RPoint::flipVertical() {
    position.flipVertical();
    return true;
}

QSharedPointer<RShape> RPoint::getTransformed(const QTransform& transform) const {
    return QSharedPointer<RShape>(new RPoint(position.getTransformed2D(transform)));
}

void RPoint::print(QDebug dbg) const {
    dbg.nospace() << "RPoint(";
    RShape::print(dbg);
    dbg.nospace() << ", position: " << getPosition() << ")";
}
