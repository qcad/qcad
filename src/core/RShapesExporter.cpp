/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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
#include "RShapesExporter.h"
#include "RSpline.h"
#include "RSplineProxy.h"

RShapesExporter::RShapesExporter(RExporter& exporter, const QList<QSharedPointer<RShape> >& shapes, double offset) :
    RExporter(exporter.getDocument()), exporter(exporter), shapes(shapes) {

    double length = 0.0;

    for (int i=0; i<shapes.length(); i++) {
        length += shapes[i]->getLength();
        lengthAt.append(length);
    }

    RLine line(RVector(0,0), RVector(length, 0));

    RSplineProxy* proxy = RSpline::getSplineProxy();
    if (proxy) {
        proxy->init();
    }
    exportLine(line, offset);
    if (proxy) {
        proxy->uninit();
    }
}

void RShapesExporter::exportLineSegment(const RLine& line, double angle) {
    int i1, i2;
    RVector p1 = getPointAt(line.startPoint.x, &i1);
    RVector p2 = getPointAt(line.endPoint.x, &i2);

    if (line.getLength()<RS::PointTolerance) {
        // zero length (point):
        exporter.exportLineSegment(RLine(p1, p2), angle);
    }
    else {
        exportShapesBetween(i1, p1, i2, p2);
    }
}

void RShapesExporter::exportPainterPaths(const QList<RPainterPath>& paths, double angle, const RVector& pos) {
    RVector p = getPointAt(pos.x);
    double a = getAngleAt(pos.x);
    RExporter::exportPainterPaths(paths, a, p);
}

RVector RShapesExporter::getPointAt(double d, int* index) {
    int i = getShapeAt(d);
    double a = d - (i==0 ? 0.0 : lengthAt[i-1]);
    QList<RVector> points = shapes[i]->getPointsWithDistanceToEnd(a, RS::FromStart);
    Q_ASSERT(points.length()>0);
    if (index) {
        *index = i;
    }
    return points[0];
}

double RShapesExporter::getAngleAt(double d) {
    int i = getShapeAt(d);
    double a = d - (i==0 ? 0.0 : lengthAt[i-1]);
    return shapes[i]->getAngleAt(a);
}

int RShapesExporter::getShapeAt(double d) {
    for (int i=0; i<shapes.length(); i++) {
        double d1 = (i==0 ? 0.0 : lengthAt[i-1]);
        double d2 = lengthAt[i];
        if (d>=d1 && d<=d2) {
            return i;
        }
    }
}

void RShapesExporter::exportShapesBetween(int i1, const RVector& p1, int i2, const RVector& p2) {
    for (int i=i1; i<=i2; i++) {
        if (i!=i1 && i!=i2) {
            // whole shape is between points:
            exporter.exportShapeSegment(shapes[i]);
        }

        QSharedPointer<RShape> shape = QSharedPointer<RShape>(shapes[i]->clone());
        QSharedPointer<RDirected> dir = shape.dynamicCast<RDirected>();
        if (dir.isNull()) {
            continue;
        }

        if (i==i1) {
            // trim start point:
            dir->trimStartPoint(p1);
        }
        if (i==i2) {
            // trim end point:
            dir->trimEndPoint(p2);
        }

        exporter.exportShapeSegment(shape);
    }
}
