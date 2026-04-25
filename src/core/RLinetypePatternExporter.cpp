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
#include "RLinetypePatternExporter.h"
#include "RLine.h"
#include "RSpline.h"
#include "RSplineProxy.h"


/**
 * Constructor.
 *
 * \param exporter Exporter to which the shapes are exported, e.g. a RPainterPathExporter
 * \param shapes Shapes to be exported as connected shapes with continuous line pattern.
 * \param offset Offset into the line type pattern.
 */
RLinetypePatternExporter::RLinetypePatternExporter(RExporter& exporter, const QList<QSharedPointer<RShape> >& shapes, double offset) :
    RExporter(exporter.getDocument()), exporter(exporter), shapes(shapes) {

    double length = 0.0;

    for (int i=0; i<shapes.length(); i++) {
        length += shapes[i]->getLength();
        lengthAt.push_back(length);
    }

    RLine line(RVector(0,0), RVector(length, 0));

    // export straight line with angle 0 and length of line, arc, polyline, spline, ...:
    // the pattern is mapped to the shape by this exporter:
    exportLine(line, offset);
}

/**
 * Constructor.
 *
 * \param exporter Exporter to which the shapes are exported, e.g. a RPainterPathExporter
 * \param shape Shape to be exported as connected shapes with continuous line pattern.
 * \param offset Offset into the line type pattern.
 */
RLinetypePatternExporter::RLinetypePatternExporter(RExporter& exporter, const QSharedPointer<RShape>& shape, double offset) :
    RExporter(exporter.getDocument()), exporter(exporter) {

    shapes.append(shape);

    double length = shape->getLength();
    lengthAt.push_back(length);

    RLine line(RVector(0,0), RVector(length, 0));

    // export straight line with angle 0 and length of line, arc, polyline, spline, ...:
    // the pattern is mapped to the shape by this exporter:
    exportLine(line, offset);
}

/**
 * Exports the given line segment, mapped to the shapes that are being exported.
 *
 * \param line Line segment, mapped to the straight, horizontal line starting at 0/0).
 * \param angle Always 0.0.
 */
void RLinetypePatternExporter::exportLineSegment(const RLine& line, double angle) {
    Q_UNUSED(angle)

    // indices of segments on real shape:
    int i1, i2;
    // map segment start to real shape:
    RVector p1OnShape = getPointAt(line.startPoint.x, &i1);
    // map segment start to real shape:
    RVector p2OnShape = getPointAt(line.endPoint.x, &i2);
    // get angle on real shape:
    double a = getAngleAt(line.startPoint.x);

    if (!p1OnShape.isValid() || !p2OnShape.isValid()) {
        return;
    }

    if (line.getLength()<RS::PointTolerance) {
        // zero length (point):
        exporter.exportLineSegment(RLine(p1OnShape, p2OnShape), a);
    }
    else {
        exportShapesBetween(i1, p1OnShape, i2, p2OnShape, a);
    }
}

void RLinetypePatternExporter::exportPainterPaths(const QList<RPainterPath>& paths, double angle, const RVector& pos) {
    Q_UNUSED(angle)

    RVector p = getPointAt(pos.x);
    double a = getAngleAt(pos.x);
    RExporter::exportPainterPaths(paths, a, p);
}

RVector RLinetypePatternExporter::getPointAt(double d, int* index) {
    int i = getShapeAt(d);
    if (i<0 || i>=(int)lengthAt.size() || i>=(int)shapes.length()) {
        return RVector::invalid;
    }

    double a;
    if (i==0) {
        a = d;
    }
    else {
        a = d - lengthAt[i-1];
    }
    QList<RVector> points = shapes[i]->getPointsWithDistanceToEnd(a, RS::FromStart);
    if (points.isEmpty()) {
        return RVector::invalid;
    }

    if (index) {
        *index = i;
    }
    return points[0];
}

double RLinetypePatternExporter::getAngleAt(double d) {
    int i = getShapeAt(d);
    if (i<0 || i>shapes.length() || (unsigned long)i>lengthAt.size()) {
        return 0.0;
    }
    double a = d - (i==0 ? 0.0 : lengthAt[i-1]);
    return shapes[i]->getAngleAt(a);
}

int RLinetypePatternExporter::getShapeAt(double d) {
    for (int i=0; (unsigned long)i<lengthAt.size(); i++) {
        double d1;
        if (i==0) {
            d1 = 0.0;
        }
        else {
            d1 = lengthAt[i-1];
        }
        double d2 = lengthAt[i];
        if (d>=d1 && d<=d2) {
            return i;
        }
    }
    return -1;
}

void RLinetypePatternExporter::exportShapesBetween(int i1, const RVector& p1, int i2, const RVector& p2, double angle) {
    for (int i=i1; i<=i2; i++) {
        if (i!=i1 && i!=i2) {
            // whole shape is between points:
            exporter.exportShapeSegment(shapes[i], angle);
            continue;
        }

        QSharedPointer<RShape> shape = shapes[i]->clone();
        if (!shape->isDirected()) {
            continue;
        }

        if (i==i1) {
            // trim start point:
            shape->trimStartPoint(p1);
        }
        if (i==i2) {
            // trim end point:
            shape->trimEndPoint(p2);
        }

        // invalid spline can cause artefacts when rendering splines with dashes:
        if (!shape->isValid()) {
            continue;
        }

        exporter.exportShapeSegment(shape, angle);
    }
}
