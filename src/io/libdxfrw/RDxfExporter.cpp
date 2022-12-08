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

#include <QFileInfo>
#include <QFont>

#include "RArcEntity.h"
#include "RAttributeEntity.h"
#include "RBlockReferenceEntity.h"
#include "RCircleEntity.h"
#include "RColor.h"
#include "RDimAlignedEntity.h"
#include "RDimAngular2LEntity.h"
#include "RDimAngular3PEntity.h"
#include "RDimDiametricEntity.h"
#include "RDimOrdinateEntity.h"
#include "RDimRadialEntity.h"
#include "RDimRotatedEntity.h"
#include "RDimStyle.h"
#include "RDimensionEntity.h"
#include "RDxfExporter.h"
#include "REllipseEntity.h"
#include "RHatchEntity.h"
#include "RImageEntity.h"
#include "RLeaderEntity.h"
#include "RLineEntity.h"
#include "RPointEntity.h"
#include "RPolylineEntity.h"
#include "RRayEntity.h"
#include "RSettings.h"
#include "RSolidEntity.h"
#include "RSplineEntity.h"
#include "RStorage.h"
#include "RTextEntity.h"
#include "RTraceEntity.h"
#include "RXLineEntity.h"

RDxfExporter::RDxfExporter(RDocument& document,
    RMessageHandler* messageHandler,
    RProgressHandler* progressHandler)
    : RFileExporter(document, messageHandler, progressHandler)
{

}

QString RDxfExporter::getCorrectedFileName(const QString& fileName, const QString& nameFilter) {
    Q_UNUSED(nameFilter)

    QString ret = fileName;
    QString ext = QFileInfo(ret).suffix().toLower();

    if (ext!="dxf") {
        ret += ".dxf";
    }

    return ret;
}

bool RDxfExporter::exportFile(const QString& fileName, const QString& nameFilter, bool setFileName) {
    //qDebug() << "RDxfExporter::exportFile";
        
    return false;
}
