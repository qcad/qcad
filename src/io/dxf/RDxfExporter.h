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

class RArcEntity;
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
class RSolidEntity;
class RSplineEntity;
class RTextEntity;


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

    virtual QString getCorrectedFileName(const QString& fileName, const QString& nameFilter);

    virtual bool exportFile(const QString& fileName, const QString& nameFilter, bool resetModified = true);

    void writeVariables();
    void writeLinetype(const RLinetype& lt);
    void writeLayer(const RLayer& l);
    void writeBlock(const RBlock& b);

    void writeEntity(REntity::Id id);
    void writeEntity(const REntity& e);
    void writePoint(const RPointEntity& p);
    void writeLine(const RLineEntity& l);
    void writeCircle(const RCircleEntity& c);
    void writeArc(const RArcEntity& a);
    void writeEllipse(const REllipseEntity& el);
    void writePolyline(const RPolylineEntity& pl);
    void writePolyline(const RPolyline& pl);
    void writeSpline(const RSplineEntity& sp);
    void writeText(const RTextEntity& t);
    void writeSimpleText(const RTextEntity& t);
    void writeMText(const RTextEntity& t);
    void writeDimension(const RDimensionEntity& d);
    void writeLeader(const RLeaderEntity& l);
    void writeHatch(const RHatchEntity& h);
    void writeImage(const RImageEntity& img);
    void writeSolid(const RSolidEntity& sol);

    void writeBlockReference(const RBlockReferenceEntity& br);

    void writeImageDef(const RImageEntity& img);

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

    static QByteArray escapeUnicode(const QString& str);

private:
    DL_Attributes getEntityAttributes(const REntity& entity);
    DL_StyleData getStyle(const RTextEntity& entity);

private:
    DL_Dxf dxf;
    DL_WriterA* dw;
    DL_Attributes attributes;
    int textStyleCounter;
    QMap<int, QString> textStyles;
    //QList<DL_StyleData> textStyles;
    // maps image entity IDs to handles:
    QMap<int, int> imageHandles;
};

Q_DECLARE_METATYPE(RDxfExporter*)

#endif
