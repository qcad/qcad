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
#include "RArcExporter.h"

RArcExporter::RArcExporter(RExporter& exporter, const RArc& arc, double offset) :
    RExporter(exporter.getDocument()), exporter(exporter), arc(arc) {

    RLine line(RVector(0,0), RVector((arc.reversed ? -1 : 1) * arc.getLength(), 0));
    exportLine(line, offset);
}

void RArcExporter::exportLineSegment(const RLine& line, double angle) {
    Q_UNUSED(angle)

    RArc a = arc;
    double ang1 = line.getStartPoint().x / arc.getRadius();
    double ang2 = line.getEndPoint().x / arc.getRadius();
    a.setStartAngle(arc.getStartAngle() + ang1);
    a.setEndAngle(arc.getStartAngle() + ang2);
    bool allowZeroLen = true;

    // arc segment is full circle:
    if (ang2>ang1+M_PI*2-1.0e-6) {
        allowZeroLen = false;
    }
    exporter.exportArcSegment(a, allowZeroLen);
}

void RArcExporter::exportPainterPaths(const QList<RPainterPath>& paths, double angle, const RVector& pos) {
    Q_UNUSED(angle)

    double arcAngle = arc.getStartAngle() + pos.x / arc.getRadius();
    RVector arcPos = arc.getPointAtAngle(arcAngle);

    RExporter::exportPainterPaths(paths, arcAngle + M_PI/2, arcPos);
}
