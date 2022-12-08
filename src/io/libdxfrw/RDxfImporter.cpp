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
#include <QDir>
#include <QList>
#include <QFileInfo>
#if QT_VERSION >= 0x060000
#  include <QStringConverter>
#else
#  include <QTextCodec>
#endif
#include <QMultiMap>
#include  <QDebug>

#include "RArcEntity.h"
#include "RAttributeEntity.h"
#include "RBlock.h"
#include "RBlockReferenceEntity.h"
#include "RCircleEntity.h"
#include "RColor.h"
#include "RDebug.h"
#include "RDimAlignedEntity.h"
#include "RDimAngular2LEntity.h"
#include "RDimAngular3PEntity.h"
#include "RDimDiametricEntity.h"
#include "RDimRadialEntity.h"
#include "RDimRotatedEntity.h"
#include "RDimOrdinateEntity.h"
#include "RDocument.h"
#include "RDxfImporter.h"
#include "REllipseEntity.h"
#include "RFileImporterRegistry.h"
#include "RGlobal.h"
#include "RHatchEntity.h"
#include "RImageEntity.h"
#include "RLayer.h"
#include "RLeaderEntity.h"
#include "RLineEntity.h"
#include "RLinetype.h"
#include "RLinetypePattern.h"
#include "RModifyObjectsOperation.h"
#include "RPointEntity.h"
#include "RPolylineEntity.h"
#include "RRayEntity.h"
#include "RSettings.h"
#include "RSolidEntity.h"
#include "RSplineEntity.h"
#include "RStorage.h"
#include "RTextEntity.h"
#include "RTextRenderer.h"
#include "RTraceEntity.h"
#include "RVector.h"
#include "RView.h"
#include "RXLineEntity.h"
#include "dx_data.h"
#include "dx_iface.h"


const double dxfColors[][3] = {
                                  {0,0,0},                // unused
                                  {1,0,0},                // 1
                                  {1,1,0},
                                  {0,1,0},
                                  {0,1,1},
                                  {0,0,1},
                                  {1,0,1},
                                  {1,1,1},                // black or white
                                  {0.5,0.5,0.5},
                                  {0.75,0.75,0.75},
                                  {1,0,0},                // 10
                                  {1,0.5,0.5},
                                  {0.65,0,0},
                                  {0.65,0.325,0.325},
                                  {0.5,0,0},
                                  {0.5,0.25,0.25},
                                  {0.3,0,0},
                                  {0.3,0.15,0.15},
                                  {0.15,0,0},
                                  {0.15,0.075,0.075},
                                  {1,0.25,0},             // 20
                                  {1,0.625,0.5},
                                  {0.65,0.1625,0},
                                  {0.65,0.4063,0.325},
                                  {0.5,0.125,0},
                                  {0.5,0.3125,0.25},
                                  {0.3,0.075,0},
                                  {0.3,0.1875,0.15},
                                  {0.15,0.0375,0},
                                  {0.15,0.0938,0.075},
                                  {1,0.5,0},              // 30
                                  {1,0.75,0.5},
                                  {0.65,0.325,0},
                                  {0.65,0.4875,0.325},
                                  {0.5,0.25,0},
                                  {0.5,0.375,0.25},
                                  {0.3,0.15,0},
                                  {0.3,0.225,0.15},
                                  {0.15,0.075,0},
                                  {0.15,0.1125,0.075},
                                  {1,0.75,0},             // 40
                                  {1,0.875,0.5},
                                  {0.65,0.4875,0},
                                  {0.65,0.5688,0.325},
                                  {0.5,0.375,0},
                                  {0.5,0.4375,0.25},
                                  {0.3,0.225,0},
                                  {0.3,0.2625,0.15},
                                  {0.15,0.1125,0},
                                  {0.15,0.1313,0.075},
                                  {1,1,0},                // 50
                                  {1,1,0.5},
                                  {0.65,0.65,0},
                                  {0.65,0.65,0.325},
                                  {0.5,0.5,0},
                                  {0.5,0.5,0.25},
                                  {0.3,0.3,0},
                                  {0.3,0.3,0.15},
                                  {0.15,0.15,0},
                                  {0.15,0.15,0.075},
                                  {0.75,1,0},             // 60
                                  {0.875,1,0.5},
                                  {0.4875,0.65,0},
                                  {0.5688,0.65,0.325},
                                  {0.375,0.5,0},
                                  {0.4375,0.5,0.25},
                                  {0.225,0.3,0},
                                  {0.2625,0.3,0.15},
                                  {0.1125,0.15,0},
                                  {0.1313,0.15,0.075},
                                  {0.5,1,0},              // 70
                                  {0.75,1,0.5},
                                  {0.325,0.65,0},
                                  {0.4875,0.65,0.325},
                                  {0.25,0.5,0},
                                  {0.375,0.5,0.25},
                                  {0.15,0.3,0},
                                  {0.225,0.3,0.15},
                                  {0.075,0.15,0},
                                  {0.1125,0.15,0.075},
                                  {0.25,1,0},             // 80
                                  {0.625,1,0.5},
                                  {0.1625,0.65,0},
                                  {0.4063,0.65,0.325},
                                  {0.125,0.5,0},
                                  {0.3125,0.5,0.25},
                                  {0.075,0.3,0},
                                  {0.1875,0.3,0.15},
                                  {0.0375,0.15,0},
                                  {0.0938,0.15,0.075},
                                  {0,1,0},                // 90
                                  {0.5,1,0.5},
                                  {0,0.65,0},
                                  {0.325,0.65,0.325},
                                  {0,0.5,0},
                                  {0.25,0.5,0.25},
                                  {0,0.3,0},
                                  {0.15,0.3,0.15},
                                  {0,0.15,0},
                                  {0.075,0.15,0.075},
                                  {0,1,0.25},             // 100
                                  {0.5,1,0.625},
                                  {0,0.65,0.1625},
                                  {0.325,0.65,0.4063},
                                  {0,0.5,0.125},
                                  {0.25,0.5,0.3125},
                                  {0,0.3,0.075},
                                  {0.15,0.3,0.1875},
                                  {0,0.15,0.0375},
                                  {0.075,0.15,0.0938},
                                  {0,1,0.5},              // 110
                                  {0.5,1,0.75},
                                  {0,0.65,0.325},
                                  {0.325,0.65,0.4875},
                                  {0,0.5,0.25},
                                  {0.25,0.5,0.375},
                                  {0,0.3,0.15},
                                  {0.15,0.3,0.225},
                                  {0,0.15,0.075},
                                  {0.075,0.15,0.1125},
                                  {0,1,0.75},             // 120
                                  {0.5,1,0.875},
                                  {0,0.65,0.4875},
                                  {0.325,0.65,0.5688},
                                  {0,0.5,0.375},
                                  {0.25,0.5,0.4375},
                                  {0,0.3,0.225},
                                  {0.15,0.3,0.2625},
                                  {0,0.15,0.1125},
                                  {0.075,0.15,0.1313},
                                  {0,1,1},                // 130
                                  {0.5,1,1},
                                  {0,0.65,0.65},
                                  {0.325,0.65,0.65},
                                  {0,0.5,0.5},
                                  {0.25,0.5,0.5},
                                  {0,0.3,0.3},
                                  {0.15,0.3,0.3},
                                  {0,0.15,0.15},
                                  {0.075,0.15,0.15},
                                  {0,0.75,1},             // 140
                                  {0.5,0.875,1},
                                  {0,0.4875,0.65},
                                  {0.325,0.5688,0.65},
                                  {0,0.375,0.5},
                                  {0.25,0.4375,0.5},
                                  {0,0.225,0.3},
                                  {0.15,0.2625,0.3},
                                  {0,0.1125,0.15},
                                  {0.075,0.1313,0.15},
                                  {0,0.5,1},              // 150
                                  {0.5,0.75,1},
                                  {0,0.325,0.65},
                                  {0.325,0.4875,0.65},
                                  {0,0.25,0.5},
                                  {0.25,0.375,0.5},
                                  {0,0.15,0.3},
                                  {0.15,0.225,0.3},
                                  {0,0.075,0.15},
                                  {0.075,0.1125,0.15},
                                  {0,0.25,1},             // 160
                                  {0.5,0.625,1},
                                  {0,0.1625,0.65},
                                  {0.325,0.4063,0.65},
                                  {0,0.125,0.5},
                                  {0.25,0.3125,0.5},
                                  {0,0.075,0.3},
                                  {0.15,0.1875,0.3},
                                  {0,0.0375,0.15},
                                  {0.075,0.0938,0.15},
                                  {0,0,1},                // 170
                                  {0.5,0.5,1},
                                  {0,0,0.65},
                                  {0.325,0.325,0.65},
                                  {0,0,0.5},
                                  {0.25,0.25,0.5},
                                  {0,0,0.3},
                                  {0.15,0.15,0.3},
                                  {0,0,0.15},
                                  {0.075,0.075,0.15},
                                  {0.25,0,1},             // 180
                                  {0.625,0.5,1},
                                  {0.1625,0,0.65},
                                  {0.4063,0.325,0.65},
                                  {0.125,0,0.5},
                                  {0.3125,0.25,0.5},
                                  {0.075,0,0.3},
                                  {0.1875,0.15,0.3},
                                  {0.0375,0,0.15},
                                  {0.0938,0.075,0.15},
                                  {0.5,0,1},              // 190
                                  {0.75,0.5,1},
                                  {0.325,0,0.65},
                                  {0.4875,0.325,0.65},
                                  {0.25,0,0.5},
                                  {0.375,0.25,0.5},
                                  {0.15,0,0.3},
                                  {0.225,0.15,0.3},
                                  {0.075,0,0.15},
                                  {0.1125,0.075,0.15},
                                  {0.75,0,1},             // 200
                                  {0.875,0.5,1},
                                  {0.4875,0,0.65},
                                  {0.5688,0.325,0.65},
                                  {0.375,0,0.5},
                                  {0.4375,0.25,0.5},
                                  {0.225,0,0.3},
                                  {0.2625,0.15,0.3},
                                  {0.1125,0,0.15},
                                  {0.1313,0.075,0.15},
                                  {1,0,1},                // 210
                                  {1,0.5,1},
                                  {0.65,0,0.65},
                                  {0.65,0.325,0.65},
                                  {0.5,0,0.5},
                                  {0.5,0.25,0.5},
                                  {0.3,0,0.3},
                                  {0.3,0.15,0.3},
                                  {0.15,0,0.15},
                                  {0.15,0.075,0.15},
                                  {1,0,0.75},             // 220
                                  {1,0.5,0.875},
                                  {0.65,0,0.4875},
                                  {0.65,0.325,0.5688},
                                  {0.5,0,0.375},
                                  {0.5,0.25,0.4375},
                                  {0.3,0,0.225},
                                  {0.3,0.15,0.2625},
                                  {0.15,0,0.1125},
                                  {0.15,0.075,0.1313},
                                  {1,0,0.5},              // 230
                                  {1,0.5,0.75},
                                  {0.65,0,0.325},
                                  {0.65,0.325,0.4875},
                                  {0.5,0,0.25},
                                  {0.5,0.25,0.375},
                                  {0.3,0,0.15},
                                  {0.3,0.15,0.225},
                                  {0.15,0,0.075},
                                  {0.15,0.075,0.1125},
                                  {1,0,0.25},             // 240
                                  {1,0.5,0.625},
                                  {0.65,0,0.1625},
                                  {0.65,0.325,0.4063},
                                  {0.5,0,0.125},
                                  {0.5,0.25,0.3125},
                                  {0.3,0,0.075},
                                  {0.3,0.15,0.1875},
                                  {0.15,0,0.0375},
                                  {0.15,0.075,0.0938},
                                  {0.33,0.33,0.33},       // 250
                                  {0.464,0.464,0.464},
                                  {0.598,0.598,0.598},
                                  {0.732,0.732,0.732},
                                  {0.866,0.866,0.866},
                                  {1,1,1}                 // 255
}
;

RDxfImporter::RDxfImporter(RDocument& document, RMessageHandler* messageHandler, RProgressHandler* progressHandler)
    : RFileImporter(document, messageHandler, progressHandler) {
}

RDxfImporter::~RDxfImporter() {
}

bool RDxfImporter::importFile(const QString& fileName, const QString& nameFilter, const QVariantMap& params) {
    Q_UNUSED(nameFilter)

    QFileInfo fi(fileName);
    if (!fi.exists()) {
        qWarning() << "RDxfImporter::importFile: "
                   << "file does not exist: " << fileName;
        return false;
    }

    if (fi.size()==0) {
        qWarning() << "RDxfImporter::importFile: "
                   << "file has 0 length: " << fileName;
        return false;
    }

    // defaults, compatible with other DXF libraries:
    setKnownVariable(RS::INSUNITS, RS::None);
    setKnownVariable(RS::DIMASZ, 0.18);
    setKnownVariable(RS::DIMAUNIT, 0);
    setKnownVariable(RS::DIMAZIN, 0);
    setKnownVariable(RS::DIMDEC, 4);
    setKnownVariable(RS::DIMEXE, 0.18);
    setKnownVariable(RS::DIMEXO, 0.0625);
    setKnownVariable(RS::DIMGAP, 0.09);
    setKnownVariable(RS::DIMLUNIT, 2);
    setKnownVariable(RS::DIMTSZ, 0.0);
    setKnownVariable(RS::DIMTXT, 0.18);
    setKnownVariable(RS::DIMZIN, 0);
    setKnownVariable(RS::DIMDLI, 0.18*2);
    setKnownVariable(RS::LTSCALE, 1);

    setCurrentBlockId(document->getModelSpaceBlockId());

    RImporter::startImport();


    dxfRW* dxf = new dxfRW(fileName.toUtf8());
    bool success = dxf->read(this, false);
    delete dxf;
    if (!success)
    {
        qWarning() << "Cannot open DXF file: " << fileName;
        return false;
    }

    document->setFileVersion("R15 (2000) DXF Drawing (libdxfrw) (*.dxf)");

    // make sure dimension font is set to standard,
    // the only dimension font supported by the QCAD CE:
    document->setDimensionFont("Standard");

    // dimension text color always by block:
    QVariant v;
    v.setValue(RColor(RColor::ByBlock));
    document->setKnownVariable(RS::DIMCLRT, v);    

    RImporter::endImport();

    // set block reference IDs in the end to support nested blocks (FS#1016):
    //RSpatialIndex& si = document->getSpatialIndex();
    QSet<REntity::Id> ids = document->queryAllBlockReferences();
    QSet<REntity::Id>::const_iterator it;
    for (it=ids.constBegin(); it!=ids.constEnd(); it++) {
        RBlockReferenceEntity::Id id = *it;
        QSharedPointer<REntity> entity = document->queryEntityDirect(id);
        if (entity.isNull()) {
            continue;
        }
        QSharedPointer<RBlockReferenceEntity> blockRef = entity.dynamicCast<RBlockReferenceEntity>();
        if (blockRef.isNull()) {
            continue;
        }

        QList<RBox> bbs = blockRef->getBoundingBoxes();
        QVariant v = blockRef->getCustomProperty("", "block");
        if (!v.isValid()) {
            continue;
        }
        QString blockName = v.toString();
        RBlock::Id blockId = document->getBlockId(blockName);

        if (blockId==RBlock::INVALID_ID) {
            continue;
        }

        blockRef->setReferencedBlockId(blockId);

        document->removeFromSpatialIndex(blockRef, bbs);
        document->addToSpatialIndex(blockRef);
        //si.removeFromIndex(blockRef->getId(), bbs);
        //si.addToIndex(blockRef->getId(), blockRef->getBoundingBoxes());
    }


    // add some variables that need to be there for DXF drawings:
    /*
    TODO
    if (graphic->getVariableString("$DIMSTYLE", "").isEmpty()) {
        RS_DEBUG->print("RDxfImporter::fileImport: adding DIMSTYLE");
        graphic->addVariable("$DIMSTYLE", "Standard", 2);
        RS_DEBUG->print("RDxfImporter::fileImport: adding DIMSTYLE: OK");
    }
    */

    return true;
}


QString RDxfImporter::decode(const QString& str) {
    return RDxfServices::parseUnicode(str);
}

void RDxfImporter::addHeader(const DRW_Header* data) {
}

void RDxfImporter::addLType(const DRW_LType& data)
{
    QString name = decode(data.name.c_str());
    QString description = decode(data.desc.c_str());
    //QString description = decode(data.description.c_str());
    //int numDashes = data.numberOfDashes;
    //double patternLength = data.patternLength;
  
    QList<double> pattern;
    for (auto it = data.path.begin(); it != data.path.end(); it++)
    {
        pattern.push_back(*it);
    }

    RLinetypePattern p(document->isMetric(), name, description, pattern);
    RDxfServices::autoFixLinetypePattern(p);

    //    for (int i = 0; i < numDashes; i++) {
    //        data.pattern[i] = pattern[i];
    //    }

        //RLinetypePattern lt = RLinetypePatternMap::getPattern(name.toUpper());
        //if (!lt.isValid()) {
            // linetype name not found
            //RLinetypePatternMap::addLinetype(data);
            //document->addLinetype(name);
    QSharedPointer<RLinetype> linetype(new RLinetype(document, p));

    importObjectP(linetype);
    //}
    pattern.clear();
}

void RDxfImporter::addLayer(const DRW_Layer& data) {
    QString layerName = decode(data.name.c_str());

    bool off = data.color < 0;
    bool frozen = data.flags & 0x01;
    bool locked = data.flags & 0x04;

    RColor color = RDxfServices::attributesToColor(data.color, data.color24, dxfColors, true);
    RLinetype::Id linetypeId = RLinetype::INVALID_ID;
    linetypeId = document->getLinetypeId(data.lineType.c_str());
    if (linetypeId == RLinetype::INVALID_ID) {
        linetypeId = document->getLinetypeId("CONTINUOUS");
    }
    RLineweight::Lineweight lw = RDxfServices::numberToWeight(DRW_LW_Conv::lineWidth2dxfInt(data.lWeight));

    if (lw == RLineweight::WeightByLayer) {
        lw = RLineweight::Weight005;
    }

    QSharedPointer<RLayer> layer(
        new RLayer(
            document,
            layerName,
            // only support one flag for visibility for CE:
            frozen || off,
            false,
            color,
            linetypeId,
            lw,
            off
        )
    );

    if (locked) {
        lockedLayers.append(layerName);
    }

    importObjectP(layer);
}

void RDxfImporter::addDimStyle(const DRW_Dimstyle& data) {
    dimStyles.insert(data.name.c_str(), data);
}

void RDxfImporter::addVport(const DRW_Vport& data) {}

void RDxfImporter::addTextStyle(const DRW_Textstyle& data) {
    textStyles.insert(data.name.c_str(), data);
}

void RDxfImporter::addAppId(const DRW_AppId& data) {}

void RDxfImporter::addBlock(const DRW_Block& data) {
    QString blockName = decode(data.name.c_str());

    // ignore internal dimension entity blocks:
    if (blockName.toLower().startsWith("*d")) {
        setCurrentBlockId(RBlock::INVALID_ID);
        return;
    }

    RVector bp(data.basePoint.x, data.basePoint.y, data.basePoint.z);
    QSharedPointer<RBlock> block(
        new RBlock(
            document,
            blockName,
            bp
        )
    );

    importObjectP(block);
    setCurrentBlockId(block->getId());
}

void RDxfImporter::setBlock(const int handle) {
}

void RDxfImporter::endBlock() {
    setCurrentBlockId(document->getModelSpaceBlockId());
}

void RDxfImporter::addPoint(const DRW_Point& data) {
    RVector v(data.basePoint.x, data.basePoint.y, data.basePoint.z);
    QSharedPointer<RPointEntity> entity(
        new RPointEntity(document, RPointData(v))
    );
    importEntity(entity, &data);
}

void RDxfImporter::addLine(const DRW_Line& data) {
    RVector v1(data.basePoint.x, data.basePoint.y, data.basePoint.z);
    RVector v2(data.secPoint.x, data.secPoint.y, data.secPoint.z);
    QSharedPointer<RLineEntity> entity(
        new RLineEntity(document, RLineData(v1, v2))
    );
    importEntity(entity, &data);
}

void RDxfImporter::addRay(const DRW_Ray& data) {}

void RDxfImporter::addXline(const DRW_Xline& data) {}

void RDxfImporter::addArc(const DRW_Arc& data) {}

void RDxfImporter::addCircle(const DRW_Circle& data) {}

void RDxfImporter::addEllipse(const DRW_Ellipse& data) {}

void RDxfImporter::addLWPolyline(const DRW_LWPolyline& data) {
    RPolyline polyline;
    polyline.setClosed(data.flags & 0x01);
    polyline.setWidth(data.width);

    for (auto it = data.vertlist.begin(); it != data.vertlist.end(); it++)
    {
        auto vert = *it;
        RVector v(vert->x, vert->y);
        polyline.appendVertex(v, vert->bulge);
    }

    bool polylinePlineGen = data.flags & 0x80;
    QSharedPointer<RPolylineEntity> entity(new RPolylineEntity(document, RPolylineData(polyline)));
    entity->setPolylineGen(polylinePlineGen);
    importEntity(entity, &data);
}

void RDxfImporter::addPolyline(const DRW_Polyline& data) {
    RPolyline polyline;
    polyline.setClosed(data.flags & 0x01);

    for (auto it = data.vertlist.begin(); it != data.vertlist.end(); it++)
    {
        auto vert = *it;
        RVector v(vert->basePoint.x, vert->basePoint.y, vert->basePoint.z);
        polyline.appendVertex(v, vert->bulge);
    }

    bool polylinePlineGen = data.flags & 0x80;
    QSharedPointer<RPolylineEntity> entity(new RPolylineEntity(document, RPolylineData(polyline)));
    entity->setPolylineGen(polylinePlineGen);
    importEntity(entity, &data);
}

void RDxfImporter::addSpline(const DRW_Spline* data) {}

void RDxfImporter::addKnot(const DRW_Entity& data) {}

void RDxfImporter::addInsert(const DRW_Insert& data) {}

void RDxfImporter::addTrace(const DRW_Trace& data) {}

void RDxfImporter::add3dFace(const DRW_3Dface& data) {}

void RDxfImporter::addSolid(const DRW_Solid& data) {}

void RDxfImporter::addMText(const DRW_MText& data) {
    RVector ip(data.basePoint.x, data.basePoint.y);
    //RVector dirx(data.dirx, data.diry);
    RS::VAlign valign;
    RS::HAlign halign;
    RS::TextDrawingDirection dir;
    RS::TextLineSpacingStyle lss;

    DRW_Textstyle s = textStyles.value(decode(data.style.c_str()), DRW_Textstyle());

    if (data.attachmentPoint <= 3) {
        valign = RS::VAlignTop;
    }
    else if (data.attachmentPoint <= 6) {
        valign = RS::VAlignMiddle;
    }
    else {
        valign = RS::VAlignBottom;
    }

    if (data.attachmentPoint % 3 == 1) {
        halign = RS::HAlignLeft;
    }
    else if (data.attachmentPoint % 3 == 2) {
        halign = RS::HAlignCenter;
    }
    else {
        halign = RS::HAlignRight;
    }

    dir = RS::LeftToRight;
    lss = RS::Exact;

    if (data.drawingDirection == 1) {
        dir = RS::LeftToRight;
    }
    else if (data.drawingDirection == 3) {
        dir = RS::TopToBottom;
    }
    else {
        dir = RS::ByStyle;
    }
    if (data.lineSpacingStyle == 1) {
        lss = RS::AtLeast;
    }
    else {
        lss = RS::Exact;
    }

    QByteArray mtext;
    mtext.append(data.text.c_str());
    mtext.replace(QByteArray("^ "), QByteArray("^"));
    QString mtextString = QString(mtext);

    QVariant vDwgCodePage = document->getKnownVariable(RS::DWGCODEPAGE);
    if (vDwgCodePage.isValid()) {
        QString dwgCodePage = vDwgCodePage.toString();
        QString enc = getEncoding(dwgCodePage);

        mtextString = RS::convert(mtext, enc);

        //        // get the text codec:
        //        QTextCodec* codec = QTextCodec::codecForName(enc.toLatin1());
        //        if (codec!=NULL) {
        //            mtextString = codec->toUnicode(mtext);
        //        }
        //        else {
        //            qWarning() << "RDxfImporter::addMText: unsupported text codec: " << enc;
        //        }
    }

    // use default style for the drawing:
    if (s.font.empty()) {
        // japanese, cyrillic:
        QString codepage = document->getKnownVariable(RS::DWGCODEPAGE, "ANSI_1252").toString().toUpper();
        if (codepage == "ANSI_932" || codepage == "ANSI_1251") {
            s.font = "Unicode";
        }
        else {
            s.font = document->getKnownVariable(RS::TEXTSTYLE, "Standard").toString().toUtf8();
        }
    }

    dxfServices.fixVersion2String(mtextString);

    // TODO:
    bool bold = false;
    bool italic = false;

    RTextData d(
        RVector::invalid, ip,
        data.height, data.widthscale,
        valign, halign,
        dir, lss,
        data.interlin,
        mtextString, dxfServices.fixFontName(s.font.c_str()),
        bold,
        italic,
        data.angle,
        false
    );

    QSharedPointer<RTextEntity> entity(new RTextEntity(document, d));
    importEntity(entity, &data);
}

void RDxfImporter::addText(const DRW_Text& data) {
    RS::VAlign valign;
    RS::HAlign halign;

    auto s = textStyles.value(decode(data.style.c_str()), DRW_Textstyle());

    RVector alignmentPoint(data.basePoint.x, data.basePoint.y, data.basePoint.z);
    RVector position(data.secPoint.x, data.secPoint.y, data.secPoint.z);

    if (data.alignH != 0 || data.alignV != 0) {

        // horizontal alignment:
        switch (data.alignH) {
        default:
        case DRW_Text::HLeft: // left aligned
            halign = RS::HAlignLeft;
            //refPoint = alignmentPoint;
            break;
        case DRW_Text::HCenter: // centered
            halign = RS::HAlignCenter;
            //refPoint = alignmentPoint;
            break;
        case DRW_Text::HRight: // right aligned
            halign = RS::HAlignRight;
            //refPoint = RVector(data.apx, data.apy);
            break;
        case DRW_Text::HAligned: // aligned (TODO)
            halign = RS::HAlignCenter;
            //refPoint = RVector((data.ipx+data.apx)/2.0,
            //                     (data.ipy+data.apy)/2.0);
            //angle =
            //    RVector(data.ipx, data.ipy).getAngleTo(
            //        RVector(data.apx, data.apy));
            break;
        case DRW_Text::HMiddle: // Middle (TODO)
            halign = RS::HAlignCenter;
            //refPoint = RVector(data.apx, data.apy);
            break;
        case DRW_Text::HFit: // fit (TODO)
            halign = RS::HAlignCenter;
            //            refPoint = RVector((data.ipx+data.apx)/2.0,
            //                                 (data.ipy+data.apy)/2.0);
            //            angle =
            //                RVector(data.ipx, data.ipy).getAngleTo(
            //                    RVector(data.apx, data.apy));
            break;
        }

        // vertical alignment:
        switch (data.alignV) {
        default:
        case DRW_Text::VBaseLine: // baseline
            valign = RS::VAlignBase;
            break;

        case DRW_Text::VBottom: // bottom
            valign = RS::VAlignBottom;
            break;

        case DRW_Text::VMiddle: // middle
            valign = RS::VAlignMiddle;
            break;

        case DRW_Text::VTop: // top
            valign = RS::VAlignTop;
            break;
        }
    }
    else {
        halign = RS::HAlignLeft;
        valign = RS::VAlignBase;
        //refPoint = RVector(data.ipx, data.ipy);
    }

    //int drawingDirection = 5;
    //double width = 100.0;
    double width = 0.0;
    bool bold = false;
    bool italic = false;

    RTextBasedData textBasedData(
        RVector::invalid, RVector::invalid,
        //        refPoint, refPoint,
        data.height, width,
        valign, halign,
        RS::LeftToRight, RS::Exact,
        1.0,
        data.text.c_str(),
        dxfServices.fixFontName(s.font.c_str()),
        bold,                      // bold
        italic,                    // italic
        data.angle,
        true                         // simple
    );

    textBasedData.setPosition(position);

    // if alignment is left / base or alignment point is omitted for other reason,
    // set alignment point to same as position.
    if ((textBasedData.getHAlign() == RS::HAlignLeft && textBasedData.getVAlign() == RS::VAlignBase) ||
        (RMath::isNaN(alignmentPoint.x) || RMath::isNaN(alignmentPoint.y))) {

        textBasedData.setAlignmentPoint(position);
    }
    else {
        // QCAD 1 compatibility:
        if (s.font == "txt" && qAbs(alignmentPoint.x) < RS::PointTolerance && qAbs(alignmentPoint.y) < RS::PointTolerance) {
            textBasedData.setAlignmentPoint(position);
        }
        else {
            textBasedData.setAlignmentPoint(alignmentPoint);
        }
    }

    QSharedPointer<RTextEntity> entity(new RTextEntity(document, RTextData(textBasedData)));
    importEntity(entity, &data);
}

void RDxfImporter::addDimAlign(const DRW_DimAligned* data) {}

void RDxfImporter::addDimLinear(const DRW_DimLinear* data) {}

void RDxfImporter::addDimRadial(const DRW_DimRadial* data) {}

void RDxfImporter::addDimDiametric(const DRW_DimDiametric* data) {}

void RDxfImporter::addDimAngular(const DRW_DimAngular* data) {}

void RDxfImporter::addDimAngular3P(const DRW_DimAngular3p* data) {}

void RDxfImporter::addDimOrdinate(const DRW_DimOrdinate* data) {}

void RDxfImporter::addLeader(const DRW_Leader* data) {}

void RDxfImporter::addHatch(const DRW_Hatch* data) {
    RHatchData d;
    d.setSolid(data->solid);
    d.setAngle(data->angle);
    d.setScale(data->scale);
    RVector v(data->basePoint.x, data->basePoint.y, data->basePoint.z);
    d.setOriginPoint(v);

    for (auto it = data->looplist.begin(); it != data->looplist.end(); it++)
    {
        auto loop = *it;
        d.newLoop();
        for (auto it2 = loop->objlist.begin(); it2 != loop->objlist.end(); it2++) {
            auto ent = dynamic_cast<DRW_LWPolyline*>(*it2);
            if (ent != nullptr) {
                bool closed = ent->flags & 0x01;
                QList<RVector> verts;
                for (auto it3 = ent->vertlist.begin(); it3 != ent->vertlist.end(); it3++)
                {
                    auto vd = *it3;
                    RVector v(vd->x, vd->y);
                    verts.push_back(v);
                }
                QSharedPointer<RShape> shape(new RPolyline(verts, closed));
                d.addBoundary(shape);
            }            
        }
    }

    if (data->deflinesnum > 0)
    {
        RPattern pattern;
        for (auto it = data->defines.begin(); it != data->defines.end(); it++)
        {
            DRW_HatchDefine* define = *it;
            RPatternLine patternLine;
            patternLine.angle = RMath::deg2rad(define->angle);
            patternLine.basePoint = RVector(define->origin.x, define->origin.y);
            patternLine.offset = RVector(define->delta.x, define->delta.y);
            for (auto it2 = define->segments.begin(); it2 != define->segments.end(); it2++)
            {
                patternLine.dashes.push_back(*it2);
            }
            pattern.addPatternLine(patternLine);
        }
        d.setPattern(pattern);
    }

    QSharedPointer<RHatchEntity> entity(
        new RHatchEntity(document, d)
    );
    importEntity(entity, data);
}

void RDxfImporter::addViewport(const DRW_Viewport& data) {}

void RDxfImporter::addImage(const DRW_Image* data) {}

void RDxfImporter::linkImage(const DRW_ImageDef* data) {}

void RDxfImporter::addComment(const char* comment) {}

void RDxfImporter::importEntity(QSharedPointer<REntity> entity, const DRW_Entity* data)
{
    if (getCurrentBlockId() == RBlock::INVALID_ID) {
        qDebug() << "RDxfImporter::importEntity: ignoring entity";
        return;
    }

    // Layer:
    QString layerName = decode(data->layer.c_str());
    if (layerName.isEmpty()) {
        qWarning() << "RDxfImporter::importEntity: default to layer: '0'";
        entity->setLayerId(document->getLayer0Id());
    }
    else {
        // add layer in case it doesn't exist:
        if (document->queryLayer(layerName).isNull()) {
            qWarning() << "RDxfImporter::importEntity: " << "creating layer: " << layerName;
        }

        entity->setLayerId(document->getLayerId(layerName));
    }

    // Color:
    RColor col = RDxfServices::numberToColor(data->color, dxfColors);
    RColor col24 = RDxfServices::numberToColor24(data->color24);

    // bylayer / byblock overrules all colors:
    if (col.isByBlock() || col.isByLayer()) {
        entity->setColor(col);
    }
    else {
        // 24 bit colors overrule palette colors:
        if (data->color24 != -1) {
            entity->setColor(col24);
        }
        else {
            entity->setColor(col);
        }
    }

    // Linetype:
    QString linetypeName = decode(data->lineType.c_str());
    RLinetype::Id linetypeId = document->getLinetypeId(linetypeName);
    if (linetypeId == RLinetype::INVALID_ID) {
        qWarning() << "RDxfImporter::importEntity: "
            << "unsupported linetype name (defaulting to BYLAYER): "
            << linetypeName;
        linetypeId = document->getLinetypeByLayerId();
    }
    entity->setLinetypeId(linetypeId);

    // Linetype scale:
    entity->setLinetypeScale(data->ltypeScale);

    // Width:
    entity->setLineweight(RDxfServices::numberToWeight(DRW_LW_Conv::lineWidth2dxfInt(data->lWeight)));

    int handle = data->handle;
    if (handle != -1) {
        document->getStorage().setObjectHandle(*entity, handle);
    }

    // Block:
    if (data->space == DRW::PaperSpace) {
        RBlock::Id paperSpaceBlockId = document->getBlockId("*Paper_Space");
        if (paperSpaceBlockId != RBlock::INVALID_ID) {
            entity->setBlockId(paperSpaceBlockId);
        }
        else {
            qWarning() << "paper space block not found for entity:" << *entity;
            entity->setBlockId(getCurrentBlockId());
        }
    }
    else {
        entity->setBlockId(getCurrentBlockId());
    }

    if (RSettings::isXDataEnabled()) {
        // TODO:
        //importXData(odEntity, entity);
    }

    //qDebug() << "RDxfImporter::importEntity" << *entity;

    importObjectP(entity);
}

QString RDxfImporter::getEncoding(const QString& str) {
    QString l = str.toLower();

    if (l == "latin1" || l == "ansi_1252" || l == "iso-8859-1" ||
        l == "cp819" || l == "csiso" || l == "ibm819" || l == "iso_8859-1" ||
        l == "iso8859-1" || l == "iso-ir-100" || l == "l1") {
        //return "Latin1";
        return "utf8";
    }
    else if (l == "big5" || l == "ansi_950" || l == "cn-big5" || l == "csbig5" ||
        l == "x-x-big5") {
        return "Big5";
    }
    else if (l == "big5-hkscs") {
        return "Big5-HKSCS";
    }
    else if (l == "eucjp" || l == "euc-jp" || l == "cseucpkdfmtjapanese" ||
        l == "x-euc" || l == "x-euc-jp") {
        return "eucJP";
    }
    else if (l == "euckr") {
        return "eucKR";
    }
    else if (l == "gb2312" || l == "gb2312" || l == "chinese" || l == "cn-gb" ||
        l == "csgb2312" || l == "csgb231280" || l == "csiso58gb231280" ||
        l == "gb_2312-80" || l == "gb231280" || l == "gb2312-80" || l == "gbk" ||
        l == "iso-ir-58") {
        return "GB2312";
    }
    else if (l == "gbk") {
        return "GBK";
    }
    else if (l == "gb18030") {
        return "GB18030";
    }
    else if (l == "jis7") {
        return "JIS7";
    }
    else if (l == "shift-jis" || l == "ansi_932" || l == "shift_jis" || l == "csShiftJIS" ||
        l == "cswindows31j" || l == "ms_kanji" || l == "x-ms-cp932" || l == "x-sjis") {
        return "Shift-JIS";
    }
    else if (l == "tscii") {
        return "TSCII";
    }
    else if (l == "utf88-bit") {
        return "utf88-bit";
    }
    else if (l == "utf16") {
        return "utf16";
    }
    else if (l == "koi8-r") {
        return "KOI8-R";
    }
    else if (l == "koi8-u") {
        return "KOI8-U";
    }
    else if (l == "iso8859-1") {
        return "ISO8859-1";
    }
    else if (l == "iso8859-2") {
        return "ISO8859-2";
    }
    else if (l == "iso8859-3") {
        return "ISO8859-3";
    }
    else if (l == "iso8859-4" || l == "ansi_1257") {
        return "ISO8859-4";
    }
    else if (l == "iso8859-5") {
        return "ISO8859-5";
    }
    else if (l == "iso8859-6" || l == "ansi_1256") {
        return "ISO8859-6";
    }
    else if (l == "iso8859-7" || l == "ansi_1253") {
        return "ISO8859-7";
    }
    else if (l == "iso8859-8") {
        return "ISO8859-8";
    }
    else if (l == "iso8859-8-i" || l == "ansi_1255") {
        return "ISO8859-8-i";
    }
    else if (l == "iso8859-9" || l == "ansi_1254") {
        return "ISO8859-9";
    }
    else if (l == "iso8859-10") {
        return "ISO8859-10";
    }
    else if (l == "iso8859-13") {
        return "ISO8859-13";
    }
    else if (l == "iso8859-14") {
        return "ISO8859-14";
    }
    else if (l == "iso8859-15") {
        return "ISO8859-15";
    }
    else if (l == "ibm 850") {
        return "IBM 850";
    }
    else if (l == "ibm 866") {
        return "IBM 866";
    }
    else if (l == "cp874") {
        return "CP874";
    }
    else if (l == "cp1250") {
        return "CP1250";
    }
    else if (l == "cp1251") {
        return "CP1251";
    }
    else if (l == "cp1252") {
        return "CP1252";
    }
    else if (l == "cp1253") {
        return "CP1253";
    }
    else if (l == "cp1254") {
        return "CP1254";
    }
    else if (l == "cp1255") {
        return "CP1255";
    }
    else if (l == "cp1256") {
        return "CP1256";
    }
    else if (l == "cp1257") {
        return "CP1257";
    }
    else if (l == "cp1258") {
        return "CP1258";
    }
    else if (l == "apple roman") {
        return "Apple Roman";
    }
    else if (l == "tis-620") {
        return "TIS-620";
    }

    return "Latin1";
}
