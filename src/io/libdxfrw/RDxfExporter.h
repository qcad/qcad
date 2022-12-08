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

#ifndef RDXFEXPORTER_H
#define RDXFEXPORTER_H

#include "dxf_global.h"

#include "RArc.h"
#include "RDocument.h"
#include "RDxfServices.h"
#include "RFileExporter.h"
#include "RRay.h"
#include "RXLine.h"

class RArcEntity;
class RAttributeEntity;
class RCircleEntity;
class RDimensionEntity;
class REllipseEntity;
class RHatchEntity;
class RImageEntity;
class RLeaderEntity;
class RLineEntity;
class RMessageHandler;
class RPointEntity;
class RPolylineEntity;
class RProgressHandler;
class RRayEntity;
class RSolidEntity;
class RSplineEntity;
class RTraceEntity;
class RTextEntity;
class RTextBasedData;
class RTextBasedEntity;
class RXLineEntity;


/**
 * \brief Exporter for the DXF format, based on dxflib.
 *
 * \ingroup dxf
 */
class QCADDXF_EXPORT RDxfExporter: public RFileExporter {
public:
    RDxfExporter(RDocument& document,
        RMessageHandler* messageHandler = NULL,
        RProgressHandler* progressHandler = NULL);
    virtual ~RDxfExporter() {}

    virtual QString getCorrectedFileName(const QString& fileName, const QString& nameFilter) override;

    virtual bool exportFile(const QString& fileName, const QString& nameFilter, bool setFileName = true) override;

    virtual void exportPoint(const RPoint& point) override {
        Q_UNUSED(point)
    }

    virtual void exportArcSegment(const RArc& arc, bool allowForZeroLength = false) override {
        Q_UNUSED(arc)
        Q_UNUSED(allowForZeroLength)
    }

    virtual void exportLineSegment(const RLine& line, double angle = RNANDOUBLE) override {
        Q_UNUSED(line)
        Q_UNUSED(angle)
    }

    virtual void exportXLine(const RXLine& xLine) override  {
        Q_UNUSED(xLine)
    }

    virtual void exportRay(const RRay& ray) override {
        Q_UNUSED(ray)
    }

    virtual void exportTriangle(const RTriangle& triangle) override  {
        //Q_UNUSED(triangle)
    }
};

Q_DECLARE_METATYPE(RDxfExporter*)

#endif
