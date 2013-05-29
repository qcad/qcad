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
RBox::RBox(const RVector& c1, const RVector& c2) {
    // important for later x1<x2 check (cross selection):
    this->c1 = c1;
    this->c2 = c2;
    //this->c1 = RVector::getMinimum(c1, c2);
    //this->c2 = RVector::getMaximum(c1, c2);
}

/**
 * Creates a square box with the given center and the given range (= side length / 2).
 */
RBox::RBox(const RVector& center, double range) {
    c1 = RVector(center.x-range, center.y-range);
    c2 = RVector(center.x+range, center.y+range);
}

bool RBox::isValid() const {
    return (c1.isValid() && c2.isValid());
}

RBox& RBox::grow(double offset) {
    RVector min = getMinimum();
    RVector max = getMaximum();
    min -= RVector(offset, offset, offset);
    max += RVector(offset, offset, offset);
    c1 = min;
    c2 = max;
    return *this;
}

RBox& RBox::growXY(double offset) {
    RVector min = getMinimum();
    RVector max = getMaximum();
    min -= RVector(offset, offset);
    max += RVector(offset, offset);
    c1 = min;
    c2 = max;
    return *this;
}

double RBox::getWidth() const {
    return qAbs(c2.x-c1.x);
}

double RBox::getHeight() const {
    return qAbs(c2.y-c1.y);
}

RVector RBox::getSize() const {
    return c2 - c1;
}



RVector RBox::getCenter() const {
    return (c1 + c2) / 2.0;
}



RVector RBox::getMinimum() const {
    return RVector::getMinimum(c1, c2);
}



RVector RBox::getMaximum() const {
    return RVector::getMaximum(c1, c2);
}



RVector RBox::getCorner1() const {
    return c1;
}

void RBox::setCorner1(const RVector& v) {
    c1 = v;
}

RVector RBox::getCorner2() const {
    return c2;
}

void RBox::setCorner2(const RVector& v) {
    c2 = v;
}

/**
 * \return True if this box is completely inside the given box.
 */
//bool RBox::isInside(const RBox& other) const {
//    return other.contains(*this);
//}



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
 * Grows this box to include the given box or sets this box to the
 * given box if this box is invalid.
 */
void RBox::growToInclude(const RBox& other) {
    if (!other.isValid()) {
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

QList<RVector> RBox::getCorners2d() const {
    QList<RVector> ret;

    ret.append(RVector(c1.x, c1.y));
    ret.append(RVector(c2.x, c1.y));
    ret.append(RVector(c2.x, c2.y));
    ret.append(RVector(c1.x, c2.y));

    return ret;
}


QList<RLine> RBox::getLines2d() const {
    QList<RLine> ret;

    ret.append(RLine(RVector(c1.x, c1.y), RVector(c2.x, c1.y)));
    ret.append(RLine(RVector(c2.x, c1.y), RVector(c2.x, c2.y)));
    ret.append(RLine(RVector(c2.x, c2.y), RVector(c1.x, c2.y)));
    ret.append(RLine(RVector(c1.x, c2.y), RVector(c1.x, c1.y)));

    return ret;
}

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


QRectF RBox::toQRectF() const {
    return QRectF(c1.x, c1.y, c2.x - c1.x, c2.y - c1.y);
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
    dbg.nospace() << "RBox(" << b.c1 << " - " << b.c2 << ")";
    return dbg.space();
}
