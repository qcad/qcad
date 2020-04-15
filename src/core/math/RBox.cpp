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
#include "RBox.h"
#include "RPolyline.h"



/**
 * Constructor for an invalid box with invalid corner points.
 */
RBox::RBox() :
    c1(RVector::invalid),
    c2(RVector::invalid) {}

/**
 * Constructor for a box based on the given QRectF object.
 */
RBox::RBox(const QRectF& rect) {
    c1.x = qMin(rect.left(), rect.right());
    c1.y = qMin(rect.top(), rect.bottom());
    c1.z = 0;
    c2.x = qMax(rect.left(), rect.right());
    c2.y = qMax(rect.top(), rect.bottom());
    c2.z = 0;
}

/**
 * Constructor for a box with two given diagonally opposite corners.
 */
RBox::RBox(const RVector& c1, const RVector& c2) : c1(c1), c2(c2) {
    // important for later x1<x2 check (cross selection): keep c1, c2 order
}

RBox::RBox(double x1, double y1, double x2, double y2) : c1(x1,y1), c2(x2,y2) {
}

/**
 * Creates a square box with the given center and the given range (= side length / 2).
 */
RBox::RBox(const RVector& center, double range) {
    c1 = RVector(center.x-range, center.y-range);
    c2 = RVector(center.x+range, center.y+range);
}

/**
 * Creates a box with the given center and the given width / height.
 */
RBox::RBox(const RVector& center, double width, double height) {
    c1 = center - RVector(width, height)/2;
    c2 = center + RVector(width, height)/2;
}

/**
 * \return True if this box is valid (i.e. both diagonally opposite corners are valid).
 */
bool RBox::isValid() const {
    return (c1.isValid() && c2.isValid());
}

/**
 * \return True if this box is sane (i.e. both diagonally opposite corners are
 * valid and not Infitiy or NaN).
 */
bool RBox::isSane() const {
    return (c1.isSane() && c2.isSane());
}

bool RBox::equalsFuzzy(const RBox& b, double tol) const {
    return c1.equalsFuzzy(b.c1) && c2.equalsFuzzy(b.c2);
}

bool RBox::equalsFuzzy2D(const RBox& b, double tol) const {
    return c1.equalsFuzzy2D(b.c1) && c2.equalsFuzzy2D(b.c2);
}

/**
 * Grows this box by the given offset in X, Y and Z (!).
 * \return pointer to this box
 */
RBox& RBox::grow(double offset) {
    RVector min = getMinimum();
    RVector max = getMaximum();
    min -= RVector(offset, offset, offset);
    max += RVector(offset, offset, offset);
    c1 = min;
    c2 = max;
    return *this;
}

/**
 * Grows this box by the given offset in X and Y only.
 * \return pointer to this box
 */
RBox& RBox::growXY(double offset) {
    RVector min = getMinimum();
    RVector max = getMaximum();
    min -= RVector(offset, offset);
    max += RVector(offset, offset);
    c1 = min;
    c2 = max;
    return *this;
}

/**
 * Grows this box by the given offsets in X and Y only.
 * \return pointer to this box
 */
RBox& RBox::growXY(double offsetX, double offsetY) {
    RVector min = getMinimum();
    RVector max = getMaximum();
    min -= RVector(offsetX, offsetY);
    max += RVector(offsetX, offsetY);
    c1 = min;
    c2 = max;
    return *this;
}

/**
 * Moves this box by the given offset.
 */
void RBox::move(const RVector& offset) {
    c1.move(offset);
    c2.move(offset);
}

/**
 * \todo implement fromCenter
 */
bool RBox::scaleByReference(const RVector& referencePoint, const RVector& targetPoint, bool keepAspectRatio, bool fromCenter) {
    RVector oriSize = getSize().getAbsolute();

    // prevent division by 0:
    if (RMath::fuzzyCompare(oriSize.x, 0.0)) oriSize.x = 1;
    if (RMath::fuzzyCompare(oriSize.y, 0.0)) oriSize.y = 1;
    if (RMath::fuzzyCompare(oriSize.z, 0.0)) oriSize.z = 1;

    int match = -1;
    if (referencePoint.equalsFuzzy(c1)) match = 1;
    if (referencePoint.equalsFuzzy(c2)) match = 2;

    RVector c3 = RVector(c2.x, c1.y);
    RVector c4 = RVector(c1.x, c2.y);
    if (referencePoint.equalsFuzzy(c3)) match = 3;
    if (referencePoint.equalsFuzzy(c4)) match = 4;

    if (match==-1) {
        return false;
    }

    RVector center = getCenter();

    // vector of translation of corner:
    RVector vf;
    switch (match) {
    case 1:
        vf = (c2-targetPoint);
        break;
    case 2:
        vf = (targetPoint-c1);
        break;
    case 3:
        vf = (targetPoint-c4);
        vf.y*=-1;
        break;
    case 4:
        vf = (c3-targetPoint);
        vf.y*=-1;
        break;
    }
    vf = vf.getDividedComponents(oriSize);

    if (keepAspectRatio) {
        if (qAbs(vf.x)>qAbs(vf.y)) {
            if (vf.x*vf.y>=0.0) {
                vf.y = vf.x;
            }
            else {
                vf.y = -vf.x;
            }
        }
        else {
            if (vf.x*vf.y>=0.0) {
                vf.x = vf.y;
            }
            else {
                vf.x = -vf.y;
            }
        }
        //vf.x = vf.y = qMax(vf.x, vf.y);
    }

    switch (match) {
    case 1:
        c1.scale(vf, c2);
        break;
    case 2:
        c2.scale(vf, c1);
        break;
    case 3:
        c3.scale(vf, c4);
        break;
    case 4:
        c4.scale(vf, c3);
        break;
    }

    if (match==3 || match==4) {
        c1 = RVector(c4.x, c3.y);
        c2 = RVector(c3.x, c4.y);
    }

    return true;

//    else if (referencePoint.equalsFuzzy(c2)) {
//        RVector vf = (targetPoint-c1).getDividedComponents(oriSize);
//        if (keepAspectRatio) {
//            if (qAbs(vf.x)>qAbs(vf.y)) {
//                vf.y = vf.x;
//            }
//            else {
//                vf.x = vf.y;
//            }
//            //vf.x = vf.y = qMax(vf.x, vf.y);
//        }
//        c2.scale(vf, c1);
//        return true;
//    }
//    else {
//        RVector c3 = RVector(c2.x, c1.y);
//        RVector c4 = RVector(c1.x, c2.y);
//        bool ret = false;

//        if (referencePoint.equalsFuzzy(c3)) {
//            RVector vf = (c4-targetPoint).getDividedComponents(oriSize).getAbsolute();
//            if (keepAspectRatio) {
//                vf.x = vf.y = qMax(vf.x, vf.y);
//            }
//            c3.scale(vf, c4);
//            ret = true;
//        }
//        else if (referencePoint.equalsFuzzy(c4)) {
//            RVector vf = (c3-targetPoint).getDividedComponents(oriSize).getAbsolute();
//            if (keepAspectRatio) {
//                vf.x = vf.y = qMax(vf.x, vf.y);
//            }
//            c4.scale(vf, c3);
//            ret = true;
//        }

//        if (ret) {
//            c1 = RVector(c4.x, c3.y);
//            c2 = RVector(c3.x, c4.y);
//        }
//        return ret;
//    }
//    else if (referencePointPx.equalsFuzzy(cornersPx[1], 0.01)) {
//        cornersPx[1] = targetPointPx;
//        cornersPx[0].y = targetPointPx.y;
//        cornersPx[2].x = targetPointPx.x;
//        ret = true;
//    }
//    else if (referencePointPx.equalsFuzzy(cornersPx[2], 0.01)) {
//        cornersPx[2] = targetPointPx;
//        cornersPx[1].x = targetPointPx.x;
//        cornersPx[3].y = targetPointPx.y;
//        ret = true;
//    }
//    else if (referencePointPx.equalsFuzzy(cornersPx[3], 0.01)) {
//        cornersPx[3] = targetPointPx;
//        cornersPx[0].x = targetPointPx.x;
//        cornersPx[2].y = targetPointPx.y;
//        ret = true;
//    }
}

/**
 * \return Width of this box.
 */
double RBox::getWidth() const {
    return qAbs(c2.x-c1.x);
}

/**
 * \return Height of this box.
 */
double RBox::getHeight() const {
    return qAbs(c2.y-c1.y);
}

/**
 * \return Size of this box (X,Y,Z).
 */
RVector RBox::getSize() const {
    return c2 - c1;
}

double RBox::getArea() const {
    return getWidth() * getHeight();
}

/**
 * \return Center of this box.
 */
RVector RBox::getCenter() const {
    return (c1 + c2) / 2.0;
}

/**
 * \return Minimum point of this box (minimum X,Z and Z).
 */
RVector RBox::getMinimum() const {
    return RVector::getMinimum(c1, c2);
}

/**
 * \return Maximum point of this box (maximum X,Z and Z).
 */
RVector RBox::getMaximum() const {
    return RVector::getMaximum(c1, c2);
}

/**
 * \return First of two diagonally opposite corners that define the box.
 */
RVector RBox::getCorner1() const {
    return c1;
}

/**
 * Set first of two diagonally opposite corners that define the box.
 */
void RBox::setCorner1(const RVector& v) {
    c1 = v;
}

/**
 * \return Second of two diagonally opposite corners that define the box.
 */
RVector RBox::getCorner2() const {
    return c2;
}

/**
 * Set second of two diagonally opposite corners that define the box.
 */
void RBox::setCorner2(const RVector& v) {
    c2 = v;
}

/**
 * \return True if the given box is completely outside this box.
 */
bool RBox::isOutside(const RBox& other) const {
    RVector maximum = getMaximum();
    RVector minimum = getMinimum();
    RVector otherMaximum = other.getMaximum();
    RVector otherMinimum = other.getMinimum();

    return (
        minimum.x > otherMaximum.x ||
        minimum.y > otherMaximum.y ||
        minimum.z > otherMaximum.z ||
        maximum.x < otherMinimum.x ||
        maximum.y < otherMinimum.y ||
        maximum.z < otherMinimum.z
    );
}

/**
 * \return True if the given box is completely outside this box.
 */
bool RBox::isOutsideXY(const RBox& other) const {
    RVector maximum = getMaximum();
    RVector minimum = getMinimum();
    RVector otherMaximum = other.getMaximum();
    RVector otherMinimum = other.getMinimum();

    return (
                minimum.x > otherMaximum.x ||
                minimum.y > otherMaximum.y ||
                maximum.x < otherMinimum.x ||
                maximum.y < otherMinimum.y
           );
}

/**
 * \return True if the given box is completely inside this box.
 */
bool RBox::contains(const RBox& other) const {
    return other.c1.isInside(*this) && other.c2.isInside(*this);
}

/**
 * \return True if the given vector is inside this box.
 */
bool RBox::contains(const RVector& v) const {
    return v.isInside(*this);
}

/**
 * \return True if this box intersects the given other box.
 */
bool RBox::intersects(const RBox& other) const {
    RVector maximum = getMaximum();
    RVector minimum = getMinimum();
    RVector otherMaximum = other.getMaximum();
    RVector otherMinimum = other.getMinimum();

    if (minimum.x>otherMaximum.x || 
        minimum.y>otherMaximum.y || 
        minimum.z>otherMaximum.z) {
        return false;
    }
    if (maximum.x<otherMinimum.x || 
        maximum.y<otherMinimum.y || 
        maximum.z<otherMinimum.z) {
        return false;
    }

    return true;
}

/**
 * \return True if this box intersects the given shape.
 * \param limited True to limit the shape to its actual length,
 * false to return true if the extended shape interesects this box.
 */
bool RBox::intersectsWith(const RShape& shape, bool limited) const {
    if (limited && !intersects(shape.getBoundingBox())) {
        return false;
    }

    QList<RLine> boxEdges = getLines2d();
    for (int i=0; i<boxEdges.length(); i++) {
        if (boxEdges[i].intersectsWith(shape, limited)) {
            return true;
        }
    }

    return false;
}

/**
 * Grows this box to include all other given boxes.
 */
void RBox::growToIncludeBoxes(const QList<RBox>& others) {
    for (int i=0; i<others.length(); i++) {
        growToInclude(others[i]);
    }
}

/**
 * Grows this box to include the given box or sets this box to the
 * given box if this box is invalid.
 */
void RBox::growToInclude(const RBox& other) {
    if (!other.isSane()) {
        return;
    }

    if (!isValid()) {
        *this = other;
        return;
    }

    RVector min = getMinimum();
    RVector max = getMaximum();
    RVector omin = other.getMinimum();
    RVector omax = other.getMaximum();

    c1 = RVector::getMinimum(min, omin);
    c2 = RVector::getMaximum(max, omax);
}

/**
 * Grows this box to include the given point.
 */
void RBox::growToInclude(const RVector& v) {
    if (!isValid()) {
        c1 = c2 = v;
        return;
    }

    RVector min = RVector::getMinimum(getMinimum(), v);
    RVector max = RVector::getMaximum(getMaximum(), v);
    c1 = min;
    c2 = max;
}

/**
 * \return 8 vectors for the eight corners of the box.
 *
 * The first box corner is the first defining corner \c c1.
 * The next three corners are the corners on the same Z level
 * as \c c1, counter-clockwise.
 * The next four corners are on the same Z-level as \c c2
 * starting with the corner at the same X/Y position as \c c1,
 * continueing counter-clockwise.
 */
QList<RVector> RBox::getCorners() const {
    QList<RVector> ret;
    
    ret.append(RVector(c1.x, c1.y, c1.z));
    ret.append(RVector(c2.x, c1.y, c1.z));
    ret.append(RVector(c2.x, c2.y, c1.z));
    ret.append(RVector(c1.x, c2.y, c1.z));
    ret.append(RVector(c1.x, c1.y, c2.z));
    ret.append(RVector(c2.x, c1.y, c2.z));
    ret.append(RVector(c2.x, c2.y, c2.z));
    ret.append(RVector(c1.x, c2.y, c2.z));

    return ret;
}

/**
 * \return List of all four corners of this box flattened to 2D.
 */
QList<RVector> RBox::getCorners2d() const {
    QList<RVector> ret;

    ret.append(RVector(c1.x, c1.y));
    ret.append(RVector(c2.x, c1.y));
    ret.append(RVector(c2.x, c2.y));
    ret.append(RVector(c1.x, c2.y));

    return ret;
}

/**
 * \return List of all four sides of this box flattened to 2D.
 */
QList<RLine> RBox::getLines2d() const {
    QList<RLine> ret;

    ret.append(RLine(RVector(c1.x, c1.y), RVector(c2.x, c1.y)));
    ret.append(RLine(RVector(c2.x, c1.y), RVector(c2.x, c2.y)));
    ret.append(RLine(RVector(c2.x, c2.y), RVector(c1.x, c2.y)));
    ret.append(RLine(RVector(c1.x, c2.y), RVector(c1.x, c1.y)));

    return ret;
}

/**
 * \return Polyline representing the four sides of this box flattened to 2D.
 */
RPolyline RBox::getPolyline2d() const {
    RPolyline ret;
    ret.appendVertex(RVector(c1.x, c1.y));
    ret.appendVertex(RVector(c2.x, c1.y));
    ret.appendVertex(RVector(c2.x, c2.y));
    ret.appendVertex(RVector(c1.x, c2.y));
    ret.setClosed(true);
    return ret;
}

/**
 * \return 12 triangles, two for each side of the box.
 */
QList<RTriangle> RBox::getTriangles() const {
    QList<RTriangle> ret;
    QList<RVector> corners = getCorners();

    // front:
    ret.append(RTriangle(corners[0], corners[1], corners[5]));
    ret.append(RTriangle(corners[0], corners[5], corners[4]));

    // right:
    ret.append(RTriangle(corners[1], corners[2], corners[6]));
    ret.append(RTriangle(corners[1], corners[6], corners[5]));

    // back:
    ret.append(RTriangle(corners[2], corners[3], corners[7]));
    ret.append(RTriangle(corners[2], corners[7], corners[6]));

    // left
    ret.append(RTriangle(corners[3], corners[0], corners[4]));
    ret.append(RTriangle(corners[3], corners[4], corners[7]));

    // bottom:
    ret.append(RTriangle(corners[0], corners[2], corners[1]));
    ret.append(RTriangle(corners[0], corners[3], corners[2]));

    // top:
    ret.append(RTriangle(corners[4], corners[5], corners[7]));
    ret.append(RTriangle(corners[5], corners[6], corners[7]));

    return ret;
}

/**
 * \return This box converted to a QRectF object (2D).
 */
QRectF RBox::toQRectF() const {
    return QRectF(c1.x, c1.y, c2.x - c1.x, c2.y - c1.y);
}

void RBox::transform(QTransform& t) {
    RBox res;

    QList<RVector> corners = getCorners2d();
    for (int i=0; i<corners.length(); i++) {
        QPointF qp(corners[i].x, corners[i].y);
        QPointF qpTransformed = t.map(qp);
        res.growToIncludePoint(RVector(qpTransformed.x(), qpTransformed.y()));
    }

    c1 = res.c1;
    c2 = res.c2;
}

/**
 * == operator
 */
bool RBox::operator ==(const RBox& other) const {
    return c1==other.c1 && c2==other.c2;
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, const RBox& b) {
    dbg.nospace() << "RBox(" << b.c1.x << "," << b.c1.y << ": " << b.getWidth() << "x" << b.getHeight() << ")";
    return dbg.space();
}
