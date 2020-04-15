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

#ifndef RBOX_H
#define RBOX_H

#include "../core_global.h"

#include <QRectF>

#include "RVector.h"
#include "RTriangle.h"

class RPolyline;

#define RDEFAULT_RBOX RBox()

/**
 * Represents a box e.g. a bounding box.
 * The surfaces of the box are orthogonal to the Cartesian coordinate system.
 *
 * \ingroup math
 * \scriptable
 * \sharedPointerSupport
 * \copyable
 */
class QCADCORE_EXPORT RBox {
public:
    RBox();
    explicit RBox(const QRectF& rect);
    RBox(double x1, double y1, double x2, double y2);
    RBox(const RVector& c1, const RVector& c2);
    RBox(const RVector& center, double range);
    RBox(const RVector& center, double width, double height);

    bool isValid() const;
    bool isSane() const;

    bool equalsFuzzy(const RBox& b, double tol = RS::PointTolerance) const;
    bool equalsFuzzy2D(const RBox& b, double tol = RS::PointTolerance) const;

    RBox get2D() const {
        return RBox(c1.get2D(), c2.get2D());
    }

    double getWidth() const;
    double getHeight() const;
    RVector getSize() const;
    double getArea() const;
    RVector getCenter() const;
    RVector getMinimum() const;
    RVector getMaximum() const;
    bool isOutside(const RBox& other) const;
    bool isOutsideXY(const RBox& other) const;
    bool contains(const RBox& other) const;
    /**
     * \nonscriptable
     */
    bool contains(const RVector& v) const;
    bool containsBox(const RBox& other) const {
        return contains(other);
    }
    bool containsPoint(const RVector& v) const {
        return contains(v);
    }
    bool intersects(const RBox& other) const;
    bool intersectsWith(const RShape& shape, bool limited = true) const;

    void growToInclude(const RBox& other);
    void growToIncludeBoxes(const QList<RBox>& others);
    void growToIncludeBox(const RBox& other) {
        growToInclude(other);
    }
    /**
     * \nonscriptable
     */
    void growToInclude(const RVector& v);
    void growToIncludePoint(const RVector& v) {
        growToInclude(v);
    }

    RVector getCorner1() const;
    void setCorner1(const RVector& v);
    RVector getCorner2() const;
    void setCorner2(const RVector& v);

    QList<RVector> getCorners() const;
    QList<RVector> getCorners2d() const;
    QList<RLine> getLines2d() const;
    RPolyline getPolyline2d() const;
    QList<RTriangle> getTriangles() const;

    RBox& grow(double offset);
    RBox& growXY(double offset);
    RBox& growXY(double offsetX, double offsetY);

    void move(const RVector& offset);
    bool scaleByReference(const RVector& referencePoint, const RVector& targetPoint, bool keepAspectRatio = false, bool fromCenter = false);

    QRectF toQRectF() const;

    bool operator ==(const RBox& other) const;
    bool operator !=(const RBox& other) const {
        return !operator==(other);
    }

    void transform(QTransform& t);

public:
    /**
     * \getter{getCorner1}
     * \setter{setCorner1}
     */
    RVector c1;
    /**
     * \getter{getCorner2}
     * \setter{setCorner2}
     */
    RVector c2;
};

QCADCORE_EXPORT QDebug operator<<(QDebug dbg, const RBox& b);

Q_DECLARE_METATYPE(RBox)
Q_DECLARE_METATYPE(RBox*)
Q_DECLARE_METATYPE(QSharedPointer<RBox>)
Q_DECLARE_METATYPE(QSharedPointer<RBox>*)
Q_DECLARE_METATYPE(QList<RBox>)

#endif
