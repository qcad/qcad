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
#include "RArcExporter.h"

RArcExporter::RArcExporter(RExporter& exporter, const RArc& arc, double offset, bool firstOrLast) :
    RExporter(exporter.getDocument()), exporter(exporter), arc(arc) {

    RLine line(RVector(0,0), RVector((arc.reversed ? -1 : 1) * arc.getLength(), 0));
    exportLine(line, offset, firstOrLast);
}

void RArcExporter::exportLineSegment(const RLine& line, double angle) {
    RArc a = arc;
    double ang1 = line.getStartPoint().x / arc.getRadius();
    double ang2 = line.getEndPoint().x / arc.getRadius();
    a.setStartAngle(arc.getStartAngle() + ang1);
    a.setEndAngle(arc.getStartAngle() + ang2);
    exporter.exportArcSegment(a);
}

void RArcExporter::exportLinetypeShape(QList<RPainterPath>& pps, const RLine& line, double total, double length, bool optimizeEnds, double angle, const RVector& cursor) {
    RVector min = RPainterPath::getMinList(pps);
    RVector max = RPainterPath::getMaxList(pps);
    //                qDebug() << "total: " << total;
    //                qDebug() << "offset: " << offset;
    //                qDebug() << "min.x: " << min.x;
    bool firstShapeOutside = total+min.x<0.0;
    bool lastShapeOutside = total+max.x>length;
    if (!optimizeEnds || (!firstShapeOutside && !lastShapeOutside)) {
//        RPainterPath::rotateList(pps, angle);
//        RPainterPath::translateList(pps, cursor);
//        exportPainterPaths(pps);
        double ang = arc.getStartAngle() + cursor.x / arc.getRadius();
        RPainterPath::rotateList(pps, ang + M_PI/2.0);
        RPainterPath::translateList(pps, arc.getPointAtAngle(ang));
        exporter.exportPainterPaths(pps);
    }
    else {
//        if (firstShapeOutside) {
//            //                        qDebug("firstShapeOutside");
////            double ang = (total+max.x) / arc.getRadius();
////            RArc a = arc;
////            a.setEndAngle(a.getStartAngle() + ang);
////            exporter.exportArcSegment(a);
////            RVector p = RVector(
////                        cos(angle) * fabs(total+max.x),
////                        sin(angle) * fabs(total+max.x)
////                        );
////            exportLineSegment(RLine(line.startPoint, line.startPoint+p), angle);
//        }
//        if (lastShapeOutside) {
//            RVector p = RVector(
//                        cos(angle) * fabs(total+min.x),
//                        sin(angle) * fabs(total+min.x)
//                        );
//            exportLineSegment(RLine(line.startPoint+p, line.endPoint), angle);
//        }
    }
}
