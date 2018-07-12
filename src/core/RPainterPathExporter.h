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

#ifndef RPAINTERPATHEXPORTER_H
#define RPAINTERPATHEXPORTER_H

#include "core_global.h"

#include "RArc.h"
#include "RExporter.h"
#include "RPainterPath.h"
#include "RRay.h"
#include "RXLine.h"

/**
 * Exports all exported geometry into one painter path.
 */
class QCADCORE_EXPORT RPainterPathExporter : public RExporter {
public:
    RPainterPathExporter() :
        RExporter(), exportZeroLinesAsPoints(true), ignoreZeroLines(false) { }

    virtual void exportLineSegment(const RLine& line, double angle = RNANDOUBLE);
    virtual void exportPainterPaths(const QList<RPainterPath>& paths, double z = 0.0);

    virtual void exportXLine(const RXLine& xLine) {
        Q_UNUSED(xLine)
    }

    virtual void exportRay(const RRay& ray) {
        Q_UNUSED(ray)
    }

    virtual void exportPoint(const RPoint& point) {
        Q_UNUSED(point)
    }
    virtual void exportTriangle(const RTriangle& triangle) {
        Q_UNUSED(triangle)
    }

    //void clear();
    RPainterPath getPainterPath();
    void setExportZeroLinesAsPoints(bool on) {
        exportZeroLinesAsPoints = on;
    }
    void setIgnoreZeroLines(bool on) {
        ignoreZeroLines = on;
    }

private:
    RPainterPath path;
    bool exportZeroLinesAsPoints;
    bool ignoreZeroLines;
};

#endif
