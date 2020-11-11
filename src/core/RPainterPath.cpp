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
#include <QPen>

#include "RArc.h"
#include "RCircle.h"
#include "RBox.h"
#include "REllipse.h"
#include "RLine.h"
#include "RMath.h"
#include "RPainterPath.h"
#include "RPainterPathExporter.h"
#include "RSpline.h"

RPainterPath::RPainterPath() :
    zLevel(0),
    pen(Qt::NoPen),
    brush(Qt::NoBrush),
    modes(RPainterPath::NoModes),
    featureSize(0.0),
    pixelSizeHint(-1) {
    //RDebug::incCounter("RPainterPath");
}

RPainterPath::RPainterPath(const QPainterPath& path) :
    QPainterPath(path),
    zLevel(0),
    pen(Qt::NoPen),
    brush(Qt::NoBrush),
    modes(RPainterPath::NoModes),
    featureSize(0.0),
    pixelSizeHint(-1) {
    //RDebug::incCounter("RPainterPath");
}

RPainterPath::RPainterPath(const RPainterPath& other) :
    QPainterPath(other),
    zLevel(other.zLevel),
    pen(other.pen),
    brush(other.brush),
    modes(other.modes),
    points(other.points),
    featureSize(other.featureSize),
    pixelSizeHint(other.pixelSizeHint) {

    // detach original shapes:
    for (int i=0; i<other.originalShapes.length(); i++) {
        QSharedPointer<RShape> originalShape = other.originalShapes[i];
        originalShapes.append(QSharedPointer<RShape>(originalShape->clone()));

//        QSharedPointer<RLine> originalLine = originalShape.dynamicCast<RLine>();
//        if (!originalLine.isNull()) {
//            originalShapes.append(QSharedPointer<RShape>(new RLine(*originalLine)));
//            continue;
//        }

//        QSharedPointer<RArc> originalArc = originalShape.dynamicCast<RArc>();
//        if (!originalArc.isNull()) {
//            originalShapes.append(QSharedPointer<RShape>(new RArc(*originalArc)));
//            continue;
//        }

//        QSharedPointer<RPolyline> originalPl = originalShape.dynamicCast<RPolyline>();
//        if (!originalPl.isNull()) {
//            originalShapes.append(QSharedPointer<RShape>(new RPolyline(*originalPl)));
//            continue;
//        }
    }

    //RDebug::incCounter("RPainterPath");
}

RPainterPath::~RPainterPath() {
    //RDebug::decCounter("RPainterPath");
}

void RPainterPath::setPath(const QPainterPath& path) {
    *((QPainterPath*)(this)) = path;
}

bool RPainterPath::isAtPosition(const RVector& p, double tolerance) const {
    if (isEmpty()) {
        return false;
    }
    return getCurrentPosition().equalsFuzzy(p, tolerance);
}

void RPainterPath::addLine(const RLine& line) {
    //moveToOrNop(line.startPoint);
    lineTo(line.endPoint);
}

void RPainterPath::addArc(const RArc& arc) {
    //moveToOrNop(arc.getStartPoint());

        // more precise, but not desirable for SVG export:
        QList<RSpline> splines = RSpline::createSplinesFromArc(arc);
        for (int i=0; i<splines.length(); i++) {
            RSpline spline = splines[i];
            cubicTo(spline.getControlPointAt(1), spline.getControlPointAt(2), spline.getControlPointAt(3));
        }

//        // NOTE: very imprecise for short arcs with large radii:
//        // causes problems with arcs with large radii
//        // in SVG exports (20180905):
//        RCircle c(arc.getCenter(), arc.getRadius());
//        RBox bb = c.getBoundingBox();
//        arcTo(bb.getMinimum().x,
//              bb.getMinimum().y,
//              bb.getSize().x,
//              bb.getSize().y,
//              -RMath::rad2deg(arc.getStartAngle()),
//              -RMath::rad2deg(arc.getSweep()));
}

void RPainterPath::addPolyline(const RPolyline& pl) {
    //moveToOrNop(line.startPoint);
    for (int i=0; i<pl.countSegments(); i++) {
        QSharedPointer<RShape> segment = pl.getSegmentAt(i);

        QSharedPointer<RLine> line = segment.dynamicCast<RLine>();
        if (!line.isNull()) {
            addLine(*line);
            continue;
        }

        QSharedPointer<RArc> arc = segment.dynamicCast<RArc>();
        if (!arc.isNull()) {
            addArc(*arc);
            continue;
        }
    }
}

void RPainterPath::addSpline(const RSpline& spline) {
    int degree = spline.getDegree();
    if (degree<=3) {
        moveTo(spline.getStartPoint());
    }

    QList<RSpline> list = spline.getBezierSegments();

    for (int i=0; i<list.count(); i++) {
        QList<RVector> cps = list[i].getControlPoints();
        // very rare splines of degree >= 4:
        if ((cps.size()>=5 && degree==cps.size()-1)) {
            QList<QSharedPointer<RShape> > segments = spline.getExploded(16);
            for (int k=0; k<segments.length(); k++) {
                QSharedPointer<RLine> l = segments[k].dynamicCast<RLine>();
                if (k==0) {
                    moveTo(l->getStartPoint());
                }
                lineTo(l->getEndPoint());
            }
        }
        else if (cps.size()==4 && degree==3) {
            cubicTo(cps[1], cps[2], cps[3]);
        }
        else if (cps.size()==3 && degree==2) {
            quadTo(cps[1], cps[2]);
        }
        else if (cps.size()==2 && degree==1) {
            lineTo(cps[1]);
        }
        else {
            qWarning() << "RPainterPath::addSpline: invalid bezier segment: " << list[i];
            continue;
        }
    }
}

/**
 * Fixes crashing QPainterPath::addRect
 */
void RPainterPath::addRect(const QRectF& rect) {
    addRect(rect.left(), rect.bottom(), rect.right(), rect.top());
}

void RPainterPath::addRect(double x1, double y1, double x2, double y2) {
    moveTo(RVector(x1, y1));
    lineTo(RVector(x2, y1));
    lineTo(RVector(x2, y2));
    lineTo(RVector(x1, y2));
    lineTo(RVector(x1, y1));
}

void RPainterPath::addBox(const RBox& box) {
    addRect(box.c1.x, box.c1.y, box.c2.x, box.c2.y);
}

QList<QSharedPointer<RShape> > RPainterPath::getShapes() const {
    // painter path stores original shapes (e.g. font glyph):
    if (!originalShapes.isEmpty()) {
        return originalShapes;
    }

    QList<QSharedPointer<RShape> > ret;
    QPointF cursor;

    for (int i = 0; i < elementCount(); ++i) {
        QPainterPath::Element el = elementAt(i);

        // line element in path:
        if (el.isLineTo()) {
            RLine* line = new RLine(RVector(cursor.x(), cursor.y()), RVector(el.x, el.y));
            ret.append(QSharedPointer<RShape>(line));
        }

        // curve element in path:
        else if (el.isCurveTo()) {
            QPointF controlPoint1(el.x, el.y);
            i++;
            if (i>=elementCount()) {
                break;
            }
            el = elementAt(i);
            QPointF controlPoint2(el.x, el.y);
            i++;
            if (i>=elementCount()) {
                break;
            }
            el = elementAt(i);
            QPointF endPoint(el.x, el.y);

            QList<RVector> controlPoints;
            controlPoints.append(RVector(cursor.x(), cursor.y()));
            controlPoints.append(RVector(controlPoint1.x(), controlPoint1.y()));
            controlPoints.append(RVector(controlPoint2.x(), controlPoint2.y()));
            controlPoints.append(RVector(endPoint.x(), endPoint.y()));
            RSpline* spline = new RSpline(controlPoints, 3);
            ret.append(QSharedPointer<RShape>(spline));
        }

        cursor = el;
    }

    QList<RVector> points = getPoints();
    for (int i=0; i<points.length(); i++) {
        ret.append(QSharedPointer<RPoint>(new RPoint(points[i])));
    }

    return ret;
}

void RPainterPath::addPath(const RPainterPath& path) {
    QPainterPath::addPath(path);
    points.append(path.getPoints());
    originalShapes.append(path.originalShapes);
}

void RPainterPath::appendPath(const RPainterPath& path) {
    for (int i = 0; i < path.elementCount(); ++i) {
        QPainterPath::Element el = path.elementAt(i);

        // line element in path:
        if (el.isLineTo()) {
            lineTo(el.x, el.y);
        }

        // curve element in path:
        else if (el.isCurveTo()) {
            RVector controlPoint1(el.x, el.y);
            i++;
            if (i>=path.elementCount()) {
                break;
            }
            el = path.elementAt(i);
            RVector controlPoint2(el.x, el.y);
            i++;
            if (i>=path.elementCount()) {
                break;
            }
            el = path.elementAt(i);
            RVector endPoint(el.x, el.y);
            cubicTo(controlPoint1, controlPoint2, endPoint);
        }
    }

    points.append(path.getPoints());
}

RBox RPainterPath::getBoundingBox() const {
    RBox box = RBox(QPainterPath::boundingRect());
    for (int i=0; i<points.count(); i++) {
        box.growToInclude(points[i]);
    }
    return box;
}

RVector RPainterPath::getStartPoint() const {
    QPointF p = pointAtPercent(0.0);
    return RVector(p.x(), p.y());
}

RVector RPainterPath::getEndPoint() const {
    QPointF p = pointAtPercent(1.0);
    return RVector(p.x(), p.y());
}

void RPainterPath::setMode(RPainterPath::Mode mode, bool on) {
    if (on) {
        modes |= mode;
    } else {
        modes &= ~mode;
    }
}

bool RPainterPath::getMode(RPainterPath::Mode mode) const {
    return (modes & mode) == mode;
}

bool RPainterPath::isValid() const {
    return !getMode(RPainterPath::Invalid);
}

bool RPainterPath::isSane() const {
    for (int i=0; i<elementCount(); i++) {
        QPainterPath::Element el = elementAt(i);
        if (!RMath::isSane(el.x) || !RMath::isSane(el.y)) {
            return false;
        }
    }
    return true;
}

void RPainterPath::setValid(bool on) {
    setMode(RPainterPath::Invalid, !on);
}

void RPainterPath::setSelected(bool on) {
    setMode(RPainterPath::Selected, on);
}

bool RPainterPath::isSelected() const {
    return getMode(RPainterPath::Selected);
}

void RPainterPath::setHighlighted(bool on) {
    setMode(RPainterPath::Highlighted, on);
}

bool RPainterPath::isHighlighted() const {
    return getMode(RPainterPath::Highlighted);
}

void RPainterPath::setFixedPenColor(bool on) {
    setMode(RPainterPath::FixedPenColor, on);
}

bool RPainterPath::isFixedPenColor() const {
    return getMode(RPainterPath::FixedPenColor);
}

void RPainterPath::setFixedBrushColor(bool on) {
    setMode(RPainterPath::FixedBrushColor, on);
}

bool RPainterPath::isFixedBrushColor() const {
    return getMode(RPainterPath::FixedBrushColor);
}

void RPainterPath::setAutoRegen(bool on) {
    setMode(RPainterPath::AutoRegen, on);
}

bool RPainterPath::getAutoRegen() const {
    return getMode(RPainterPath::AutoRegen);
}

void RPainterPath::setAlwaysRegen(bool on) {
    setMode(RPainterPath::AlwaysRegen, on);
}

bool RPainterPath::getAlwaysRegen() const {
    return getMode(RPainterPath::AlwaysRegen);
}

void RPainterPath::setInheritPen(bool on) {
    setMode(RPainterPath::InheritPen, on);
}

bool RPainterPath::getInheritPen() const {
    return getMode(RPainterPath::InheritPen);
}

void RPainterPath::setPixelUnit(bool on) {
    setMode(RPainterPath::PixelUnit, on);
}

bool RPainterPath::getPixelUnit() const {
    return getMode(RPainterPath::PixelUnit);
}

void RPainterPath::setNoClipping(bool on) {
    setMode(RPainterPath::NoClipping, on);
}

bool RPainterPath::getNoClipping() const {
    return getMode(RPainterPath::NoClipping);
}

void RPainterPath::setNoColorMode(bool on) {
    setMode(RPainterPath::NoColorMode, on);
}

bool RPainterPath::getNoColorMode() const {
    return getMode(RPainterPath::NoColorMode);
}

void RPainterPath::setSimplePointDisplay(bool on) {
    setMode(RPainterPath::SimplePointDisplay, on);
}

bool RPainterPath::getSimplePointDisplay() const {
    return getMode(RPainterPath::SimplePointDisplay);
}

void RPainterPath::setPixelWidth(bool on) {
    setMode(RPainterPath::PixelWidth, on);
}

bool RPainterPath::getPixelWidth() const {
    return getMode(RPainterPath::PixelWidth);
}

void RPainterPath::setFeatureSize(double s) {
    featureSize = s;
}

double RPainterPath::getFeatureSize() const {
    return featureSize;
}

void RPainterPath::setPixelSizeHint(double s) {
    pixelSizeHint = s;
}

double RPainterPath::getPixelSizeHint() const {
    return pixelSizeHint;
}

/**
 * \return Z-level of the painter path.
 */
int RPainterPath::getZLevel() const {
    return zLevel;
}

/**
 * Sets the z-level of the painter path. Painter paths may be 
 * ordered by z-level when drawn.
 */
void RPainterPath::setZLevel(int zl) {
    zLevel = zl;
}

/**
 * \return Pen of this painter path.
 */
QPen RPainterPath::getPen() const {
    return pen;
}

/**
 * Sets the pen of this painter path. The pen may be set before painting
 * the path but this is up to the caller.
 */
void RPainterPath::setPen(const QPen& p) {
    pen = p;
}

QBrush RPainterPath::getBrush() const {
    return brush;
}

void RPainterPath::setBrush(const QBrush& b) {
    brush = b;
}

/**
 * \return Distance from this painter path to the given point.
 *
 * This can be used for example to find out how close the visual
 * representation of an entity is to the mouse cursor on the screen.
 */
double RPainterPath::getDistanceTo(const RVector& point) const {
    double minDist = RMAXDOUBLE;
    QPointF cursor;

    // distance to path:
    for (int i = 0; i < elementCount(); ++i) {
        QPainterPath::Element el = elementAt(i);

        // line element in path:
        if (el.isLineTo()) {
            RLine line(RVector(cursor.x(), cursor.y()), RVector(el.x, el.y));
            double dist = line.getDistanceTo(point);
            if (!RMath::isNaN(dist) && dist < minDist) {
                minDist = dist;
            }
        }

        // curve element in path:
        else if (el.isCurveTo()) {
            QPointF controlPoint1(el.x, el.y);
            i++;
            if (i>=elementCount()) {
                break;
            }
            el = elementAt(i);
            QPointF controlPoint2(el.x, el.y);
            i++;
            if (i>=elementCount()) {
                break;
            }
            el = elementAt(i);
            QPointF endPoint(el.x, el.y);

            QPainterPath elPath;
            elPath.moveTo(cursor);
            elPath.cubicTo(controlPoint1, controlPoint2, endPoint);
            for (double t=0.0; t<1.0; t+=0.1) {
                QPointF pt1 = elPath.pointAtPercent(t);
                QPointF pt2 = elPath.pointAtPercent(qMin(t+0.1, 1.0));
                RLine lineSegment(RVector(pt1.x(), pt1.y()), RVector(pt2.x(), pt2.y()));
                double dist = lineSegment.getDistanceTo(point);
                if (dist < minDist) {
                    minDist = dist;
                }
            }
        }
        cursor = el;
    }

    // distance to points:
    for (int i=0; i<points.count(); ++i) {
        double dist = points.at(i).getDistanceTo(point);
        if (!RMath::isNaN(dist) && dist < minDist) {
            minDist = dist;
        }
    }

    return minDist;
}

void RPainterPath::addPoint(const RVector& position) {
    points.append(position);
}


bool RPainterPath::hasPoints() {
    return points.count()!=0;
}


QList<RVector> RPainterPath::getPoints() const {
    return points;
}

void RPainterPath::setPoints(const QList<RVector>& p) {
    points = p;
}

void RPainterPath::transform(const QTransform& t) {
    QPainterPath qp = t.map(*this);
    (*(QPainterPath*)this) = qp;

    for (int i=0; i<points.count(); i++) {
        points[i].transform2D(t);
    }

    if (!originalShapes.isEmpty()) {
//        bool hasArcs = false;
//        for (int i=0; i<originalShapes.length(); i++) {
//            if (originalShapes[i]->getShapeType()!=RShape::Line) {
//                hasArcs = true;
//                break;
//            }
//        }

//        if (hasArcs) {
//            originalShapes.clear();
//        }
//        else {
            QList<QSharedPointer<RShape> > os;
            for (int i=0; i<originalShapes.length(); i++) {
                os.append(originalShapes[i]->getTransformed(t));
            }
            originalShapes = os;
//        }
    }
}

void RPainterPath::move(const RVector& offset) {
    translate(offset.x, offset.y);

    RVector::moveList(points, offset);

    for (int i=0; i<originalShapes.length(); i++) {
        originalShapes[i]->move(offset);
    }
}

void RPainterPath::rotate(double angle) {
    QTransform t;
    t.rotate(RMath::rad2deg(angle));
    QPainterPath qp = t.map(*this);
    (*(QPainterPath*)this) = qp;

    RVector::rotateList(points, angle);

    for (int i=0; i<originalShapes.length(); i++) {
        originalShapes[i]->rotate(angle);
    }
}

void RPainterPath::scale(double fx, double fy) {
    QTransform t;
    t.scale(fx, fy);
    QPainterPath qp = t.map(*this);
    (*(QPainterPath*)this) = qp;

    RVector::scaleList(points, RVector(fx, fy, 1));

    if (RMath::fuzzyCompare(fx, fy)) {
        for (int i=0; i<originalShapes.length(); i++) {
            originalShapes[i]->scale(fx, RVector(0,0));
        }
    }
    else {
        // non-uniform scale looses original shapes:
        originalShapes.clear();
    }
}

int RPainterPath::getElementCount() const {
    return elementCount();
}

double RPainterPath::getXAt(int i) const {
    return elementAt(i).x;
}

double RPainterPath::getYAt(int i) const {
    return elementAt(i).y;
}

QPainterPath::ElementType RPainterPath::getTypeAt(int i) const {
    return elementAt(i).type;
}

bool RPainterPath::isEmpty() const {
    return QPainterPath::isEmpty() && points.isEmpty();
}

void RPainterPath::rotateList(QList<RPainterPath>& pps, double angle) {
    for (int i=0; i<pps.length(); i++) {
        pps[i].rotate(angle);
    }
}

void RPainterPath::translateList(QList<RPainterPath>& pps, const RVector& offset) {
    for (int i=0; i<pps.length(); i++) {
        pps[i].translate(offset.x, offset.y);
    }
}

void RPainterPath::scaleList(QList<RPainterPath>& pps, double fx, double fy) {
    for (int i=0; i<pps.length(); i++) {
        pps[i].scale(fx, fy);
    }
}

RVector RPainterPath::getMinList(QList<RPainterPath>& pps) {
    RVector ret = RVector::invalid;
    for (int i=0; i<pps.length(); i++) {
        RVector m = pps[i].getBoundingBox().getMinimum();
        if (!ret.isValid()) {
            ret = m;
        }
        else {
            ret.x = qMin(ret.x, m.x);
            ret.y = qMin(ret.y, m.y);
        }
    }
    return ret;
}

RVector RPainterPath::getMaxList(QList<RPainterPath>& pps) {
    RVector ret = RVector::invalid;
    for (int i=0; i<pps.length(); i++) {
        RVector m = pps[i].getBoundingBox().getMaximum();
        if (!ret.isValid()) {
            ret = m;
        }
        else {
            ret.x = qMax(ret.x, m.x);
            ret.y = qMax(ret.y, m.y);
        }
    }
    return ret;
}

/**
 * This operator allows us to sort painter paths based on z-level.
 */
bool operator<(const RPainterPath& p1, const RPainterPath& p2) {
    return p1.getZLevel() < p2.getZLevel();
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, RPainterPath& p) {
    //dbg.nospace() << p.toString();
    dbg.nospace() << "RPainterPath("
            << "\n\tselected: " << p.isSelected()
            << "\n\tfixedPenColor: " << p.isFixedPenColor()
            << "\n\tfixedBrushColor: " << p.isFixedBrushColor()
            << "\n\tfeatureSize: " << p.getFeatureSize()
            << "\n\tpixelSizeHint: " << p.getPixelSizeHint()
            << "\n\t" << p.getPen()
            << "\n\t" << p.getBrush()
            << "\n\tpoints: " << p.getPoints()
            << "\n";
    dbg.nospace() << (QPainterPath&)p;
    dbg.nospace() << ")";
    return dbg.space();
}

void RPainterPath::addShape(QSharedPointer<RShape> shape) {
    QSharedPointer<RLine> line = shape.dynamicCast<RLine>();
    if (!line.isNull()) {
        addLine(*line);
        return;
    }

    QSharedPointer<RArc> arc = shape.dynamicCast<RArc>();
    if (!arc.isNull()) {
        addArc(*arc);
        return;
    }

    QSharedPointer<RCircle> circle = shape.dynamicCast<RCircle>();
    if (!circle.isNull()) {
        addEllipse(
            QPointF(circle->getCenter().x, circle->getCenter().y),
            circle->getRadius(),
            circle->getRadius()
        );
        return;
    }

    QSharedPointer<RSpline> spline = shape.dynamicCast<RSpline>();
    if (!spline.isNull()) {
        addSpline(*spline);
        return;
    }

    QSharedPointer<REllipse> ellipse = shape.dynamicCast<REllipse>();
    if (!ellipse.isNull()) {
        RPainterPathExporter ex;
        ex.exportEllipse(*ellipse);
        RPainterPath pp = ex.getPainterPath();
        addPath(pp);
        return;
    }

    QSharedPointer<RPolyline> pl = shape.dynamicCast<RPolyline>();
    if (!pl.isNull()) {
        addPolyline(*pl);
        return;
    }
}

void RPainterPath::addOriginalShape(QSharedPointer<RShape> shape) {
    originalShapes.append(shape);
}

bool RPainterPath::hasOriginalShapes() const {
    return !originalShapes.isEmpty();
}

int RPainterPath::countOriginalShapes() const {
    return originalShapes.count();
}

QSharedPointer<RShape> RPainterPath::getOriginalShape(int i) const {
    return originalShapes[i];
}
