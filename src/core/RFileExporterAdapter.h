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

#ifndef RFILEEXPORTERADAPTER_H
#define RFILEEXPORTERADAPTER_H

#include "RFileExporter.h"

class RArc;
class RCircle;
class RDocument;
class REllipse;
class RImageData;
class RLine;
class RLinetype;
class RLinetypePattern;
class RPoint;
class RPolyline;
class RSpline;
class RTriangle;
class RVector;

/**
 * \brief Base class for file exporters. 
 *
 * File exporters export \ref RDocument objects into files of a specific format.
 *
 * \ingroup core
 * \scriptable
 * \generateScriptShell
 */
class RFileExporterAdapter : public RFileExporter {
public:
    RFileExporterAdapter() : RFileExporter() {}
    RFileExporterAdapter(RDocument& document) : RFileExporter(document) {}
    virtual ~RFileExporterAdapter() {}

    virtual bool exportFile(const QString& fileName, const QString& nameFilter, bool setFileName = true) {
        Q_UNUSED(fileName);
        Q_UNUSED(nameFilter);
        Q_UNUSED(setFileName);
        return false;
    }

    virtual void exportPoint(const RPoint&) {}
    virtual void exportArcSegment(const RArc&) {}
    virtual void exportLineSegment(const RLine&) {}
    virtual void exportTriangle(const RTriangle&) {}

    virtual double getPatternFactor() { return RFileExporter::getPatternFactor(); }
};

Q_DECLARE_METATYPE(RFileExporterAdapter*)

#endif
