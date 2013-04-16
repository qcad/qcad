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

#ifndef RDXFEXPORTER_H
#define RDXFEXPORTER_H

#include "dxf_global.h"

#include "dxflib/src/dl_creationinterface.h"
#include "dxflib/src/dl_dxf.h"

#include "RArc.h"
#include "RDocument.h"
#include "RDxfServices.h"
#include "RFileExporter.h"

class RMessageHandler;
class RProgressHandler;


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

    virtual QString getCorrectedFileName(const QString& fileName, const QString& nameFilter) {
        Q_UNUSED(nameFilter)

        return fileName;
    }

    virtual bool exportFile(const QString& fileName, const QString& nameFilter, bool resetModified = true);

    void writeVariables();
    void writeLinetype(const RLinetype& lt);
    void writeLayer(const RLayer& l);

    virtual void exportPoint(const RPoint& point) {
        Q_UNUSED(point)
    }

    virtual void exportArcSegment(const RArc& arc) {
        Q_UNUSED(arc)
    }

    virtual void exportLineSegment(const RLine& line) {
        Q_UNUSED(line)
    }

    virtual void exportTriangle(const RTriangle& triangle) {
        Q_UNUSED(triangle)
    }

private:
    DL_Dxf dxf;
    DL_WriterA* dw;
};

Q_DECLARE_METATYPE(RDxfExporter*)

#endif
