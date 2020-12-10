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
#include "RLine.h"
#include "REllipse.h"
#include "RHatchData.h"
#include "RPainterPath.h"
#include "RPainterPathExporter.h"
#include "RPointEntity.h"
#include "RPatternListImperial.h"
#include "RPatternListMetric.h"
#include "RSettings.h"
#include "RSpline.h"
#include "RUnit.h"
#include "RPolyline.h"

RHatchProxy* RHatchData::hatchProxy = NULL;

RHatchData::RHatchData() :
    solid(true),
    scaleFactor(1.0),
    angle(0.0),
    patternName("SOLID"),
    transparency(255),
    dirty(true), gotDraft(false), gotPixelSizeHint(0.0) {
}

RHatchData::RHatchData(RDocument* document, const RHatchData& data)
    : REntityData(document) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

RHatchData::RHatchData(const RHatchData& other) : REntityData(other), RPainterPathSource(other) {
    *this = other;
}

/**
 * \param solid True for a solid fill, false for a hatch pattern.
 * \param scaleFactor Scale factor of the hatch pattern.
 * \param angle Rotation angle of the hatch pattern.
 * \param patternName Name of the hatch pattern. "SOLID" for solid fills.
 */
RHatchData::RHatchData(bool solid, double scaleFactor, double angle, const QString& patternName) :
    solid(solid),
    scaleFactor(scaleFactor),
    angle(angle),
    patternName(patternName),
    transparency(255),
    dirty(true), gotDraft(false) {
}

RHatchData& RHatchData::operator =(const RHatchData& other) {
    REntityData::operator=(other);

    solid = other.solid;
    scaleFactor = other.scaleFactor;
    angle = other.angle;
    transparency = other.transparency;
    patternName = other.patternName;
    originPoint = other.originPoint;
    other.getPainterPaths(false);
    painterPaths = other.painterPaths;
    boundaryPath = other.boundaryPath;
    gotDraft = other.gotDraft;
    pattern = other.pattern;
    gotPixelSizeHint = other.gotPixelSizeHint;

    boundary.clear();

    for (int i=0; i<other.boundary.size(); ++i) {
        newLoop();
        QList<QSharedPointer<RShape> > loop = other.boundary.at(i);
        for (int k=0; k<loop.size(); ++k) {
            QSharedPointer<RShape> shape = loop.at(k);

            QSharedPointer<RLine> line = shape.dynamicCast<RLine>();
            if (!line.isNull()) {
                addBoundary(QSharedPointer<RShape>(new RLine(*line)));
                continue;
            }

            QSharedPointer<RArc> arc = shape.dynamicCast<RArc>();
            if (!arc.isNull()) {
                addBoundary(QSharedPointer<RShape>(new RArc(*arc)));
                continue;
            }

            QSharedPointer<RCircle> circle = shape.dynamicCast<RCircle>();
            if (!circle.isNull()) {
                addBoundary(QSharedPointer<RShape>(new RCircle(*circle)));
                continue;
            }

            QSharedPointer<REllipse> ellipseArc = shape.dynamicCast<REllipse>();
            if (!ellipseArc.isNull()) {
                addBoundary(QSharedPointer<RShape>(new REllipse(*ellipseArc)));
                continue;
            }

            QSharedPointer<RSpline> spline = shape.dynamicCast<RSpline>();
            if (!spline.isNull()) {
                addBoundary(QSharedPointer<RShape>(new RSpline(*spline)));
                continue;
            }
        }
    }

    dirty = other.dirty;
    return *this;
}

void RHatchData::clearBoundary() {
    boundary.clear();
    dirty = true;
}

RBox RHatchData::getBoundingBox(bool ignoreEmpty) const {
    Q_UNUSED(ignoreEmpty)

    if (dirty) {
        getBoundaryPath();
    }

    if (boundaryPath.isEmpty()) {
        return RBox();
    }

    return boundaryPath.getBoundingBox();
}

RVector RHatchData::getPointOnEntity() const {
    if (dirty) {
        getBoundaryPath();
    }

    QPointF p = boundaryPath.pointAtPercent(0.0);
    return RVector(p.x(), p.y());
}

double RHatchData::getDistanceTo(const RVector& point, bool limited, double range, bool draft, double strictRange) const {
    Q_UNUSED(limited)
    Q_UNUSED(range)

    if (!getBoundingBox().grow(strictRange).contains(point)) {
        return RNANDOUBLE;
    }

    if (boundaryPath.isEmpty()) {
        return RNANDOUBLE;
    }

    double ret = RNANDOUBLE;

    // path is filled (solid) or very dens / huge or we're in draft mode:
    int comp = getComplexity();
    if (isSolid() || comp>10000 || painterPaths.isEmpty() || draft) {
        if (boundaryPath.contains(QPointF(point.x, point.y))) {
            if (RMath::isNaN(ret) || strictRange<ret) {
                ret = strictRange;
            }
        }
    }

    // path is not filled and relatively simple (simple hatch):
    else {
        for (int i=0; i<painterPaths.count(); i++) {
            double d = painterPaths[i].getDistanceTo(point);
            if (RMath::isNaN(ret) || d<ret) {
                ret = d;
            }
        }
    }

    return ret;
}

bool RHatchData::intersectsWith(const RShape& shape) const {
    const RPolyline* polyline = dynamic_cast<const RPolyline*>(&shape);
    if (polyline==NULL) {
        return false;
    }

    QPainterPath polylinePath = polyline->toPainterPath();

    for (int i=0; i<painterPaths.count(); i++) {
        if (polylinePath.intersects(painterPaths[i]) &&
            !polylinePath.contains(painterPaths[i])) {

            return true;
        }
    }

    return false;
}

QList<RRefPoint> RHatchData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    QList<RRefPoint> ret;

    for (int i=0; i<boundary.size(); ++i) {
        QList<QSharedPointer<RShape> > loop = boundary.at(i);
        for (int k=0; k<loop.size(); ++k) {
            QSharedPointer<RShape> shape = loop.at(k);

            QSharedPointer<RLine> line = shape.dynamicCast<RLine>();
            if (!line.isNull()) {
                ret.append(line->getStartPoint());
                continue;
            }

            QSharedPointer<RArc> arc = shape.dynamicCast<RArc>();
            if (!arc.isNull()) {
                ret.append(arc->getStartPoint());
                continue;
            }

            QSharedPointer<RCircle> circle = shape.dynamicCast<RCircle>();
            if (!circle.isNull()) {
                ret.append(circle->getCenter());
                continue;
            }

            QSharedPointer<REllipse> ellipseArc = shape.dynamicCast<REllipse>();
            if (!ellipseArc.isNull()) {
                if (ellipseArc->isFullEllipse()) {
                    ret.append(ellipseArc->getCenter());
                }
                else {
                    ret.append(ellipseArc->getStartPoint());
                }
                continue;
            }

            QSharedPointer<RSpline> spline = shape.dynamicCast<RSpline>();
            if (!spline.isNull()) {
                if (spline->hasFitPoints()) {
                    ret.append(RRefPoint::toRefPointList(spline->getFitPoints()));
                }
                else {
                    ret.append(RRefPoint::toRefPointList(spline->getControlPoints()));
                }
                continue;
            }
        }
    }

    return ret;
}

bool RHatchData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    Q_UNUSED(modifiers)

    bool ret = false;

    for (int i=0; i<boundary.size(); ++i) {
        QList<QSharedPointer<RShape> > loop = boundary.at(i);
        for (int k=0; k<loop.size(); ++k) {
            QSharedPointer<RShape> shape = loop.at(k);

            QSharedPointer<RLine> line = shape.dynamicCast<RLine>();
            if (!line.isNull()) {
                if (referencePoint.equalsFuzzy(line->getStartPoint())) {
                    line->setStartPoint(targetPoint);
                    ret = true;
                }
                if (referencePoint.equalsFuzzy(line->getEndPoint())) {
                    line->setEndPoint(targetPoint);
                    ret = true;
                }
            }

            QSharedPointer<RArc> arc = shape.dynamicCast<RArc>();
            if (!arc.isNull()) {
                if (referencePoint.equalsFuzzy(arc->getStartPoint())) {
                    arc->moveStartPoint(targetPoint);
                    ret = true;
                }
                if (referencePoint.equalsFuzzy(arc->getEndPoint())) {
                    arc->moveEndPoint(targetPoint);
                    ret = true;
                }
            }

            QSharedPointer<RCircle> circle = shape.dynamicCast<RCircle>();
            if (!circle.isNull()) {
                if (referencePoint.equalsFuzzy(circle->getCenter())) {
                    circle->setCenter(targetPoint);
                    ret = true;
                }
            }

            QSharedPointer<REllipse> ellipseArc = shape.dynamicCast<REllipse>();
            if (!ellipseArc.isNull()) {
                if (ellipseArc->isFullEllipse()) {
                    if (referencePoint.equalsFuzzy(ellipseArc->getCenter())) {
                        ellipseArc->setCenter(targetPoint);
                        ret = true;
                    }
                }
                else {
                    if (referencePoint.equalsFuzzy(ellipseArc->getStartPoint())) {
                        ellipseArc->moveStartPoint(targetPoint, false);
                        ret = true;
                    }
                    if (referencePoint.equalsFuzzy(ellipseArc->getEndPoint())) {
                        ellipseArc->moveEndPoint(targetPoint, false);
                        ret = true;
                    }
                }
            }

            QSharedPointer<RSpline> spline = shape.dynamicCast<RSpline>();
            if (!spline.isNull()) {
//                if (spline->hasFitPoints()) {
//                    QList<RVector> fitPoints = spline->setFitPoints();
//                    QList<RVector>::iterator it;
//                    for (it=fitPoints.begin(); it!=fitPoints.end(); ++it) {
//                        if (referencePoint.getDistanceTo(*it) < RS::PointTolerance) {
//                            (*it) = targetPoint;
//                            ret = true;
//                        }
//                    }

//                    if (ret) {
//                        spline->setFitPoints(fitPoints);
//                    }
//                }
//                else {
                    QList<RVector> controlPoints = spline->getControlPoints();
                    QList<RVector>::iterator it;
                    for (it=controlPoints.begin(); it!=controlPoints.end(); ++it) {
                        if (referencePoint.equalsFuzzy(*it)) {
                            (*it) = targetPoint;
                            ret = true;
                        }
                    }

                    if (ret) {
                        spline->setControlPoints(controlPoints);
                    }
//                }
            }
        }
    }

    if (ret) {
        update();
    }

    return ret;
}

bool RHatchData::move(const RVector& offset) {
    for (int i=0; i<boundary.size(); ++i) {
        QList<QSharedPointer<RShape> > loop = boundary.at(i);
        for (int k=0; k<loop.size(); ++k) {
            QSharedPointer<RShape> shape = loop.at(k);
            shape->move(offset);
        }
    }

    update();
    return true;
}

bool RHatchData::rotate(double rotation, const RVector& center) {
    angle = RMath::getNormalizedAngle(angle+rotation);

    for (int i=0; i<boundary.size(); ++i) {
        QList<QSharedPointer<RShape> > loop = boundary.at(i);
        for (int k=0; k<loop.size(); ++k) {
            QSharedPointer<RShape> shape = loop.at(k);
            shape->rotate(rotation, center);
        }
    }

    update();
    return true;
}

bool RHatchData::scale(const RVector& scaleFactors, const RVector& center) {
    scaleFactor *= scaleFactors.x;

    for (int i=0; i<boundary.size(); ++i) {
        QList<QSharedPointer<RShape> > loop = boundary.at(i);
        for (int k=0; k<loop.size(); ++k) {
            QSharedPointer<RShape> shape = loop.at(k);
            shape->scale(scaleFactors, center);
        }
    }

    // scale custom entity specific pattern:
    pattern.scale(scaleFactors.x);

    update();
    return true;
}

bool RHatchData::mirror(const RLine& axis) {
    double ang = axis.getAngle();
    angle = RMath::getNormalizedAngle(angle + ang*2.0);

    for (int i=0; i<boundary.size(); ++i) {
        QList<QSharedPointer<RShape> > loop = boundary.at(i);
        for (int k=0; k<loop.size(); ++k) {
            QSharedPointer<RShape> shape = loop.at(k);
            shape->mirror(axis);
        }
    }

    update();
    return true;
}

bool RHatchData::stretch(const RPolyline& area, const RVector& offset) {
    bool ret = false;

    for (int i=0; i<boundary.size(); ++i) {
        QList<QSharedPointer<RShape> > loop = boundary.at(i);
        for (int k=0; k<loop.size(); ++k) {
            QSharedPointer<RShape> shape = loop.at(k);
            if (shape->stretch(area, offset)) {
                ret = true;
            }
        }
    }

    if (ret) {
        update();
    }

    return ret;
}

QList<QSharedPointer<RShape> > RHatchData::getShapes(const RBox& queryBox, bool ignoreComplex, bool segment) const {
    Q_UNUSED(queryBox)
    Q_UNUSED(segment)

    QList<QSharedPointer<RShape> > ret;

    if (ignoreComplex) {
        // complex shapes are ignored for example for snapping:
        for (int i=0; i<boundary.size(); ++i) {
            QList<QSharedPointer<RShape> > loop = boundary.at(i);
            for (int k=0; k<loop.size(); ++k) {
                QSharedPointer<RShape> shape = loop.at(k);
                if (queryBox.intersects(shape->getBoundingBox())) {
                    ret.append(shape);
                }
            }
        }
        return ret;
    }

    QList<RPainterPath> paths = getPainterPaths();
    for (int i=0; i<paths.length(); i++) {
        RPainterPath path = paths[i];
        ret.append(path.getShapes());
    }

    return ret;
}

QList<QSharedPointer<RShape> > RHatchData::getExploded() const {
    return getShapes();
}

void RHatchData::clearCustomPattern() {
    pattern.clear();
    update();
}

void RHatchData::newLoop() {
    QList<QSharedPointer<RShape> > loop;
    boundary.append(loop);
    update();
}

void RHatchData::cancelLoop() {
    boundary.removeLast();
    update();
}

/**
 * Add a boundary shape to the current loop.
 * \param addAutoLoops True: create new loop if boundary does not connect.
 * Otherwise add line segment on the fly (DXF/DWG import).
 */
void RHatchData::addBoundary(QSharedPointer<RShape> shape, bool addAutoLoops) {
    if (boundary.size()==0) {
        qWarning() << "RHatchData::addBoundary: no loops found";
        return;
    }

    if (shape->getLength()<RS::PointTolerance) {
        // never append a zero length entity to a hatch boundary:
        return;
    }

    // if shape is a polyline, add segments as boundaries
    // TODO: add polyline as boundary
    QSharedPointer<RPolyline> polyline = shape.dynamicCast<RPolyline>();
    if (!polyline.isNull()) {
        QList<QSharedPointer<RShape> > segments = polyline->getExploded();
        for (int i=0; i<segments.length(); i++) {
            addBoundary(segments.at(i));
        }
    }
    else {
        // if the current loop is not empty, check if shape connects:
        if (!boundary.last().isEmpty()) {
            QSharedPointer<RShape> prev = boundary.last().last();
            QSharedPointer<RShape> next = shape;
            if (!prev.isNull() && !next.isNull()) {
                RVector ep = prev->getEndPoint();
                RVector sp = next->getStartPoint();

                // gap of more than 0.001:
                // new loop:
                if (!ep.equalsFuzzy(sp, 0.001)) {
                    if (addAutoLoops) {
                        // inserting loop on the fly:
                        newLoop();
                    }
                    else {
                        // inserting line segment on the fly to closest match point,
                        // reverse shape if necessary:
                        if (ep.getDistanceTo(sp) < ep.getDistanceTo(next->getEndPoint())) {
                            boundary.last().append(QSharedPointer<RLine>(new RLine(ep, sp)));
                        }
                        else {
                            boundary.last().append(QSharedPointer<RLine>(new RLine(ep, next->getEndPoint())));
                            shape->reverse();
                        }
                    }
                }

                // gap of more than 0.0001:
                else if (!ep.equalsFuzzy(sp, 0.0001)) {
                    // enforce tolerance accepted by DXF/DWG format:
                    // insert bridge elemenent on the fly:
                    boundary.last().append(QSharedPointer<RLine>(new RLine(ep, sp)));
                }
            }
            else {
                qWarning() << "RHatchData::addBoundary: unexpected boundary type";
            }
        }

        // 20160405: disabled, handled in getBoundaryPath at rendering time instead:
        // avoid arc boundaries with huge radius:
//        QSharedPointer<RArc> arc = shape.dynamicCast<RArc>();
//        if (!arc.isNull() && fabs(arc->getSweep())<RMath::deg2rad(2)) {
//            boundary.last().append(QSharedPointer<RShape>(new RLine(arc->getStartPoint(), arc->getEndPoint())));
//        }
//        QSharedPointer<RArc> arc = shape.dynamicCast<RArc>();
//        if (!arc.isNull() && fabs(arc->getSweep())>M_PI*2-RS::AngleTolerance) {
//            boundary.last().append(QSharedPointer<RShape>(new RCircle(arc->getCenter(), arc->getRadius())));
//        }
//        else {
            boundary.last().append(shape);
//        }
    }

    update();
}

/**
 * \param pixelSizeHint Pixel size hint for rendering arcs.
 * Negative if it does not matter (current cached painter paths are returned).
 */
QList<RPainterPath> RHatchData::getPainterPaths(bool draft, double pixelSizeHint) const {
    if (!updatesEnabled) {
        return painterPaths;
    }

    if (!dirty) {
        // cached painter path represents hatch in current draft mode (draft or normal):
        if (draft==gotDraft && (RMath::fuzzyCompare(pixelSizeHint, gotPixelSizeHint) || pixelSizeHint<0.0)) {
            return painterPaths;
        }
    }

    painterPaths.clear();

    // for solids, return boundary path, which can be filled:
    // in draft mode, return boundary path to be shown without fill:
    if (isSolid() || draft) {
        getBoundaryPath(pixelSizeHint);
        if (draft) {
            boundaryPath.setPen(QPen(Qt::SolidLine));
            boundaryPath.setBrush(QBrush(Qt::NoBrush));
        }
        else if (isSolid()) {
            boundaryPath.setPen(QPen(Qt::NoPen));
            boundaryPath.setBrush(QBrush(Qt::SolidPattern));
        }
        boundaryPath.setAutoRegen(true);
        painterPaths.append(boundaryPath);
        dirty = false;
        gotDraft = draft;
        return painterPaths;
    }

    // drop hatch patterns with very small scale factor:
    if (scaleFactor<RS::PointTolerance) {
        return painterPaths;
    }

    //RDebug::startTimer();

    // get pattern:
    const RPattern* p = NULL;
    bool customPattern = false;
    if (hasCustomPattern()) {
        p = &pattern;
        customPattern = true;
    }
    else {
        //if (document==NULL || (RUnit::isMetric(document->getUnit()) && document->getUnit()!=RS::None)) {
        if (document==NULL) {
            qDebug() << "doc is NULL";
        }

        if (document==NULL || document->isMetric()) {
            //qDebug() << "metric pattern" << getPatternName();
            p = RPatternListMetric::get(getPatternName());
        }
        else {
            //qDebug() << "imperial pattern" << getPatternName();
            p = RPatternListImperial::get(getPatternName());
        }
    }

    // cannot load pattern at this point, return boundary for bounding box correctness:
    if (p==NULL || !p->isLoaded()) {
        qWarning() << "RHatchData::getPainterPaths: cannot load hatch pattern: " << getPatternName();
        painterPaths.append(boundaryPath);
        dirty = false;
        gotDraft = draft;
        return painterPaths;
    }

    getBoundaryPath(pixelSizeHint);

    RPattern localPattern = *p;

    if (!customPattern) {
        localPattern.rotate(angle);
        localPattern.scale(scaleFactor);
    }

    bool hasDots = localPattern.hasDots();

    RBox boundaryBox = boundaryPath.getBoundingBox();
    boundaryBox.grow(1.0);
    QList<RLine> boundaryEdges = boundaryBox.getLines2d();
    QList<RVector> boundaryCorners = boundaryBox.getCorners2d();

    QTime timer;
    timer.start();
    int timeOut = -1;

    QList<RPatternLine> patternLines = localPattern.getPatternLines();
    for (int i=0; i<patternLines.length(); i++) {
        RPatternLine patternLine = patternLines[i];

        // origin for pattern line:
        RVector spBase = originPoint + patternLine.basePoint;
        RLine baseLine(spBase, spBase + RVector::createPolar(1.0, patternLine.angle));

        // iterate through corners and find left most / right most offsets:
        double maxDistLeft = RNANDOUBLE;
        double minDistLeft = RNANDOUBLE;
        double maxDistRight = RNANDOUBLE;
        double minDistRight = RNANDOUBLE;
        for (int k=0; k<boundaryCorners.length(); k++) {
            RVector corner = boundaryCorners[k];
            double dist = baseLine.getDistanceTo(corner, false);
            RS::Side side = baseLine.getSideOfPoint(corner);

            if (side==RS::LeftHand) {
                if (RMath::isNaN(maxDistLeft) || dist>qAbs(maxDistLeft)) {
                    maxDistLeft = -dist;
                }
                if (RMath::isNaN(minDistLeft) || dist<qAbs(minDistLeft)) {
                    minDistLeft = -dist;
                }
            }
            if (side==RS::RightHand) {
                if (RMath::isNaN(maxDistRight) || dist>maxDistRight) {
                    maxDistRight = dist;
                }
                if (RMath::isNaN(minDistRight) || dist<minDistRight) {
                    minDistRight = dist;
                }
            }
        }

        if (RMath::isNaN(maxDistLeft)) {
            maxDistLeft = minDistRight;
        }

        if (RMath::isNaN(maxDistRight)) {
            maxDistRight = minDistLeft;
        }

        if (RMath::isNaN(maxDistLeft) || RMath::isNaN(maxDistRight)) {
            qWarning() << "RHatchData::getPainterPaths: no max limits found";
            return painterPaths;
        }

        if (qAbs(patternLine.offset.y)<RS::PointTolerance) {
            qWarning() << "RHatchData::getPainterPaths: invalid pattern line offset: " << patternLine.offset;
            return painterPaths;
        }

        int leftMultiple = (int)(maxDistLeft / qAbs(patternLine.offset.y)) - 1;
        int rightMultiple = (int)(maxDistRight / qAbs(patternLine.offset.y)) + 1;

        RVector offset = patternLine.offset;
        offset.rotate(patternLine.angle);

        // offset leads towards the left side of the base line, switch left / right limits:
        RS::Side offsetSide = baseLine.getSideOfPoint(baseLine.getStartPoint() + offset);
        if (offsetSide==RS::LeftHand) {
            int tmp = leftMultiple;
            leftMultiple = -rightMultiple;
            rightMultiple = -tmp;
        }

        // repeat pattern line from left to right:
        for (int m=leftMultiple; m<rightMultiple; m++) {
            RVector currentOffset = offset * m;

            RVector sp = originPoint + patternLine.basePoint + currentOffset;
            RLine orthoLine(sp, sp + RVector::createPolar(1.0, patternLine.angle + M_PI/2.0));

            // limit pattern generation to area between boundaryBox edges:
            RLine line(sp, sp + RVector::createPolar(1.0, patternLine.angle));

            QList<RVector> intersections;
            for (int k=0; k<boundaryEdges.length(); k++) {
                RLine edge = boundaryEdges[k];
                QList<RVector> ips = RShape::getIntersectionPoints(line, edge, false);

                for (int ib=0; ib<ips.length(); ib++) {
                    if (edge.isOnShape(ips[ib])) {
                        intersections.append(ips[ib]);
                    }
                }
            }

            // iterate through intersection points and find closest to the left / right:
            double orthoMaxDistLeft = RNANDOUBLE;
            double orthoMinDistLeft = RNANDOUBLE;
            double orthoMaxDistRight = RNANDOUBLE;
            double orthoMinDistRight = RNANDOUBLE;

            RVector ipMaxLeft;
            RVector ipMinLeft;
            RVector ipMaxRight;
            RVector ipMinRight;
            for (int k=0; k<intersections.length(); k++) {
                RVector ip = intersections[k];
                double dist = orthoLine.getDistanceTo(ip, false);
                RS::Side side = orthoLine.getSideOfPoint(ip);

                if (side==RS::LeftHand) {
                    if (RMath::isNaN(orthoMaxDistLeft) || dist>qAbs(orthoMaxDistLeft)) {
                        orthoMaxDistLeft = -dist;
                        ipMaxLeft = ip;
                    }
                    if (RMath::isNaN(orthoMinDistLeft) || dist<qAbs(orthoMinDistLeft)) {
                        orthoMinDistLeft = -dist;
                        ipMinLeft = ip;
                    }
                }
                if (side==RS::RightHand) {
                    if (RMath::isNaN(orthoMaxDistRight) || dist>orthoMaxDistRight) {
                        orthoMaxDistRight = dist;
                        ipMaxRight = ip;
                    }
                    if (RMath::isNaN(orthoMinDistRight) || dist<orthoMinDistRight) {
                        orthoMinDistRight = dist;
                        ipMinRight = ip;
                    }
                }
            }

            if (RMath::isNaN(orthoMaxDistLeft)) {
                orthoMaxDistLeft = orthoMinDistRight;
                ipMaxLeft = ipMinRight;
            }

            if (RMath::isNaN(orthoMaxDistRight)) {
                orthoMaxDistRight = orthoMinDistLeft;
                ipMaxRight = ipMinLeft;
            }

            if (RMath::isNaN(orthoMaxDistLeft) || RMath::isNaN(orthoMaxDistRight)) {
                //qDebug() << "orthoMaxDistLeft / orthoMaxDistRight is NaN";
                continue;
            }

            // line over maximum extent of the contour to hatch:
            RLine unclippedLine(ipMaxLeft, ipMaxRight);

            // line split up into segments, cut at contour intersections:
            QList<RLine> segments = getSegments(unclippedLine);

            RPainterPathExporter ppExporter;
            //ppExporter.setExportZeroLinesAsPoints(false);
            ppExporter.setExportZeroLinesAsPoints(true);
            // ignore zero lines if
            // line was split up into segments
            ppExporter.setIgnoreZeroLines(!hasDots);
            ppExporter.setLineweight(RLineweight::Weight100);
            if (!patternLine.dashes.isEmpty()) {
                RLinetypePattern pat;
                pat.set(patternLine.dashes);
                ppExporter.setLinetypePattern(pat);
            }

            // copy segments that are inside contour into hatch pattern:
            for (int si=0; si<segments.size(); si++) {
                RVector middle = segments[si].getMiddlePoint();
                if (boundaryPath.contains(QPointF(middle.x, middle.y))) {
                    RS::Side side = orthoLine.getSideOfPoint(segments[si].getStartPoint());
                    double offset = sp.getDistanceTo(segments[si].getStartPoint());
                    if (side==RS::RightHand) {
                        offset*=-1;
                    }
                    ppExporter.exportLine(segments[si], offset);
                    RPainterPath path = ppExporter.getPainterPath();
                    path.setSimplePointDisplay(true);

                    if (!path.isEmpty()) {
                        //clippedPattern.addPath(path);
                        path.setPen(QPen(Qt::SolidLine));
                        painterPaths.append(path);
                    }
                }
            }

            if (timer.elapsed()>500) {
                if (timeOut==-1) {
                    timeOut = RSettings::getIntValue("GraphicsView/MaxHatchTime", 2000);
                }
                if (timer.elapsed()>timeOut) {
                    qWarning() << "RHatchData::getPainterPaths: hatch pattern too dense. hatch pattern generation aborted (timeout set to " << timeOut << ")...";
                    painterPaths.clear();
                    dirty = false;
                    gotDraft = draft;
                    return painterPaths;
                }
            }
        }
    }

    dirty = false;
    gotDraft = draft;

    return painterPaths;
}

/**
 * \return Painter path that represents this hatch boundary.
 */
RPainterPath RHatchData::getBoundaryPath(double pixelSizeHint) const {
    if (!dirty && (RMath::fuzzyCompare(gotPixelSizeHint, pixelSizeHint) || pixelSizeHint<0.0)) {
        return boundaryPath;
    }

    boundaryPath = RPainterPath();
    gotPixelSizeHint = pixelSizeHint;
    boundaryPath.setPixelSizeHint(pixelSizeHint);

    for (int i=0; i<boundary.size(); ++i) {
        QList<QSharedPointer<RShape> > loop = boundary.at(i);
        RVector cursor = RVector::invalid;
        RVector loopStartPoint = RVector::invalid;
        for (int k=0; k<loop.size(); ++k) {
            QSharedPointer<RShape> shape = loop.at(k);

            QSharedPointer<RLine> line = shape.dynamicCast<RLine>();
            if (!line.isNull()) {
                if (k==0) {
                    loopStartPoint = line->getStartPoint();
                    boundaryPath.moveTo(loopStartPoint);
                }
                else {
                    if (!cursor.isValid() ||
                        !cursor.equalsFuzzy(line->getStartPoint(), 0.001)) {
                        qWarning() << "RHatchData::getBoundaryPath: loop not closed: line does not connect: loop: " << i << " / element: " << k;
                        qWarning() << "RHatchData::getBoundaryPath: cursor: " << cursor;
                        qWarning() << "RHatchData::getBoundaryPath: " << *line;
                        return RPainterPath();
                    }
                }

                cursor = line->getEndPoint();
                boundaryPath.lineTo(cursor);
                continue;
            }

            QSharedPointer<RArc> arc = shape.dynamicCast<RArc>();
            if (!arc.isNull()) {
                if (k==0) {
                    loopStartPoint = arc->getStartPoint();
                    boundaryPath.moveTo(loopStartPoint);
                }
                else {
                    if (!cursor.isValid()) {
                        qWarning() << "RHatchData::getBoundaryPath: loop not closed: invalid cursor before arc";
                        return RPainterPath();
                    }
                    if (!cursor.equalsFuzzy(arc->getStartPoint(), 0.001)) {
                        qWarning() << "RHatchData::getBoundaryPath: loop not closed: arc does not connect";
                        qWarning() << "RHatchData::getBoundaryPath: cursor: " << cursor;
                        qWarning() << "RHatchData::getBoundaryPath: arc: " << *arc;
                        return RPainterPath();
                    }
                }

                RPainterPathExporter exp;
                exp.setExportZeroLinesAsPoints(false);
                exp.setPixelSizeHint(pixelSizeHint*2);
                exp.exportArcSegment(*arc);
                RPainterPath p = exp.getPainterPath();
                boundaryPath.appendPath(p);
                cursor = arc->getEndPoint();
                continue;
            }

            QSharedPointer<RCircle> circle = shape.dynamicCast<RCircle>();
            if (!circle.isNull()) {
                if (k!=0 || loop.size()!=1) {
                    qWarning() << "RHatchData::getBoundaryPath: loop not closed: cirlce in loop";
                    return RPainterPath();
                }
                RBox box(circle->getCenter() - RVector(circle->getRadius(), circle->getRadius()),
                         circle->getCenter() + RVector(circle->getRadius(), circle->getRadius()));
                RVector start = circle->getCenter() + RVector(circle->getRadius(), 0);
                boundaryPath.moveTo(start);
                boundaryPath.arcTo(box.toQRectF(), 360.0, -360);
                cursor = RVector::invalid;
                continue;
            }

            QSharedPointer<REllipse> ellipseArc = shape.dynamicCast<REllipse>();
            if (!ellipseArc.isNull()) {
                REllipse ellipseCopy = *ellipseArc;
                if (ellipseCopy.isFullEllipse()) {
                    if (k!=0 || loop.size()!=1) {
                        qWarning() << "RHatchData::getBoundaryPath: loop not closed: full ellipse in loop";
                        return RPainterPath();
                    }
                    loopStartPoint = ellipseCopy.getStartPoint();
                    boundaryPath.moveTo(loopStartPoint);
                }
                else {
                    if (k==0) {
                        loopStartPoint = ellipseCopy.getStartPoint();
                        boundaryPath.moveTo(loopStartPoint);
                    }
                    else {
                        if (!cursor.isValid()) {
                            qWarning() << "RHatchData::getBoundaryPath: loop not closed: invalid cursor before ellipse arc";
                            return RPainterPath();
                        }
                        if (!cursor.equalsFuzzy(ellipseCopy.getStartPoint(), 0.001)) {
                            qWarning() << "RHatchData::getBoundaryPath: loop not closed: ellipse arc does not connect";
                            return RPainterPath();
                        }
                    }
                }

                REllipse ellipseArcNorm = ellipseCopy;
                ellipseArcNorm.move(-ellipseArcNorm.getCenter());
                ellipseArcNorm.rotate(-ellipseArcNorm.getAngle());

                // create normalized ellipse arc at angle 0, 0/0:
                RPainterPath ePath;
                RBox box(-RVector(ellipseArcNorm.getMajorRadius(), ellipseArcNorm.getMinorRadius()),
                         RVector(ellipseArcNorm.getMajorRadius(), ellipseArcNorm.getMinorRadius()));
                ePath.moveTo(ellipseArcNorm.getStartPoint());

                // TODO: interpolate as line segments:
                ePath.arcTo(box.toQRectF(),
                            360 - RMath::rad2deg(ellipseArcNorm.getStartParam()),
                            -RMath::rad2deg(ellipseArcNorm.getSweep()));

                // transform ellipse arc to real position / angle:
                QTransform t;
                t.translate(ellipseCopy.getCenter().x, ellipseCopy.getCenter().y);
                t.rotate(RMath::rad2deg(ellipseCopy.getAngle()));
                ePath.transform(t);

                // append ellipse arc to path:
                RVector start = ePath.getStartPoint();
                if (!cursor.isValid() ||
                    !cursor.equalsFuzzy(start, 0.001)) {
                    if (k!=0) {
                        qWarning() << "RHatchData::getBoundaryPath: loop not closed: ellipse arc does not connect";
                        return RPainterPath();
                    }
                }

                if (ellipseCopy.isFullEllipse()) {
                    boundaryPath.addPath(ePath);
                }
                else {
                    boundaryPath.connectPath(ePath);
                }
                if (ellipseCopy.isFullEllipse()) {
                    cursor = RVector::invalid;
                }
                else {
                    cursor = ellipseCopy.getEndPoint();
                }

                continue;
            }

            QSharedPointer<RSpline> spline = shape.dynamicCast<RSpline>();
            if (!spline.isNull()) {
                // spline is open, a part of a loop:
                bool periodic = spline->isPeriodic();
                if (!periodic) {
                    if (k==0) {
                        loopStartPoint = spline->getStartPoint();
                        boundaryPath.moveTo(loopStartPoint);
                    }
                    else {
                        if (!cursor.isValid() ||
                            !cursor.equalsFuzzy(spline->getStartPoint(), 0.001)) {
                            qWarning() << "RHatchData::getBoundaryPath: loop not closed: spline does not connect: loop: " << i << " / element: " << k;
                            qWarning() << "RHatchData::getBoundaryPath: cursor: " << cursor;
                            qWarning() << "RHatchData::getBoundaryPath: " << *spline;
                            return RPainterPath();
                        }
                    }
                }

                QList<RSpline> beziers = spline->getBezierSegments();
                for (int b=0; b<beziers.size(); b++) {
                    RSpline s = beziers.at(b);
                    QList<RVector> controlPoints = s.getControlPoints();
                    if (periodic && b==0) {
                        boundaryPath.moveTo(controlPoints[0]);
                    }
                    if (s.getDegree()==1) {
                        Q_ASSERT(controlPoints.size()==2);
                        boundaryPath.lineTo(controlPoints[1]);
                    } else if (s.getDegree()==2) {
                        Q_ASSERT(controlPoints.size()==3);
                        boundaryPath.quadTo(
                                    controlPoints[1], controlPoints[2]);
                    } else if (s.getDegree()==3) {
                        Q_ASSERT(controlPoints.size()==4);
                        boundaryPath.cubicTo(controlPoints[1], controlPoints[2], controlPoints[3]);
                    } else {
                        Q_ASSERT(controlPoints.size()==s.getDegree()+1);
                        //boundaryPath.cubicTo(controlPoints[1], controlPoints[2], controlPoints[3]);
                        QList<QSharedPointer<RShape> > segs = s.getExploded(16);
                        for (int sc=0; sc<segs.length(); sc++) {
                            QSharedPointer<RLine> l = segs[sc].dynamicCast<RLine>();
                            if (l.isNull()) {
                                continue;
                            }
                            boundaryPath.lineTo(l->getEndPoint());
                        }
                    }

                }
                cursor = spline->getEndPoint();
                continue;
            }
        }

        if (cursor.isValid() && loopStartPoint.isValid() &&
            !cursor.equalsFuzzy(loopStartPoint, 0.001)) {

            qWarning() << "RHatchData::getBoundaryPath: loop not closed: "
                       << "end (" << cursor <<  ") does not connect to "
                       << "start (" << loopStartPoint << ")";
            //boundaryPath.lineTo(loopStartPoint);
            return RPainterPath();
        }
    }

    return boundaryPath;
}

QList<RLine> RHatchData::getSegments(const RLine& line) const {
    QList<RLine> ret;

    // find all intersections of the given line with the boundary:
    // iterate through loops:
    QList<RVector> intersections;
    for (int loopIndex=0; loopIndex<boundary.size(); loopIndex++) {
        QList<QSharedPointer<RShape> > loop = boundary[loopIndex];
        // iterate through boundary elements:
        for (int i=0; i<loop.size(); i++) {
            QSharedPointer<RShape> boundary = loop[i];
            if (boundary.isNull()) {
                continue;
            }

            QList<RVector> ips = boundary->getIntersectionPoints(line, true, false);
            if (ips.isEmpty()) {
                continue;
            }
            intersections.append(ips);
        }
    }

    if (intersections.isEmpty()) {
        return ret;
    }

    double angle = line.getAngle();
    if ((angle>=M_PI/4.0*0.0 && angle<=M_PI/4.0*1.0) ||
        (angle>=M_PI/4.0*7.0 && angle<=M_PI/4.0*8.0)) {
        qSort(intersections.begin(), intersections.end(), RVector::lessThanX);
    }
    else if (angle>=M_PI/4.0*3.0 && angle<=M_PI/4.0*5.0) {
        qSort(intersections.begin(), intersections.end(), RVector::greaterThanX);
    }
    else if (angle>=M_PI/4.0*1.0 && angle<=M_PI/4.0*3.0) {
        qSort(intersections.begin(), intersections.end(), RVector::lessThanY);
    }
    else {
        qSort(intersections.begin(), intersections.end(), RVector::greaterThanY);
    }

    for (int i=0; i<intersections.length()-1; i++) {
        ret.append(RLine(intersections[i], intersections[i+1]));
    }

    return ret;
}

/**
 * \return Pair of two shapes that connect to the vertex at the given index.
 * The first shape connects with its end point, the second with its start point.
 */
QPair<QSharedPointer<RShape>, QSharedPointer<RShape> > RHatchData::getBoundaryElementsAt(int index, int& internalIndex) const {
    QPair<QSharedPointer<RShape>, QSharedPointer<RShape> > ret;

    int indexCounter = 0;
    internalIndex = 0;

    for (int i=0; i<boundary.size(); ++i) {
        QList<QSharedPointer<RShape> > loop = boundary.at(i);

        for (int k=0; k<loop.size(); ++k) {
            if (index==indexCounter) {
                // spacial case: node is start point of a loop:
                if (k==0) {
                    ret.first = loop.last();
                    if (loop.size()>1) {
                        ret.second = loop.first();
                    }
                    else {
                        // loop with one entity (circe, ellipse, ..):
                        // set second result to NULL:
                        ret.second = QSharedPointer<RShape>();
                    }
                }
                else {
                    QSharedPointer<RShape> shape1 = loop.at(k-1);
                    QSharedPointer<RShape> shape2 = loop.at(k);

                    ret.first = shape1;
                    ret.second = shape2;
                }
                return ret;
            }

            // spline: control points are treated like additional nodes:
            QSharedPointer<RSpline> spline = loop.at(k).dynamicCast<RSpline>();
            if (!spline.isNull()) {
                // node is at end of the spline:
//                if (indexCounter+spline->countControlPoints()-1==index) {
//                    ret.first = spline;
//                    ret.second =
//                }
                if (index < indexCounter+spline->countControlPoints()-1) {
                    ret.first = spline;
                    ret.second = QSharedPointer<RShape>();
                    internalIndex = index-indexCounter;
                    return ret;
                }
                indexCounter+=spline->countControlPoints()-1;
            }
            else {
                indexCounter++;
            }
        }
    }

    return ret;
}

void RHatchData::update() const {
    dirty = true;
}

bool RHatchData::order() {
    update();
    return RShape::order(boundary);
}

QList<QSharedPointer<RShape> > RHatchData::getLoopBoundary(int index) const {
    if (index<0 || index>=boundary.count()) {
        qWarning() << "RHatchData::getLoopBoundary: invalid loop index: " << index;
        return QList<QSharedPointer<RShape> >();
    }
    return boundary[index];
}

QList<RPolyline> RHatchData::getBoundaryAsPolylines(double segmentLength) const {
    if (hasProxy()) {
        return RHatchData::getHatchProxy()->getBoundaryAsPolylines(*this, segmentLength);
    }
    else {
        return QList<RPolyline>();
    }
}

int RHatchData::getComplexity() const {
    QList<RPainterPath> pps = getPainterPaths(false);

    int ret = 0;
    for (int i=0; i<pps.count(); i++) {
        ret += pps[i].getElementCount();
    }

    return ret;
}
