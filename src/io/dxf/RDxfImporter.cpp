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
#include <QTextCodec>
#include <QMultiMap>
#include  <QDebug>

#include "dxflib/src/dl_dxf.h"

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


RDxfImporter::RDxfImporter(RDocument& document, RMessageHandler* messageHandler, RProgressHandler* progressHandler)
    : RFileImporter(document, messageHandler, progressHandler),
      polylinePlineGen(false),
      leaderArrowHead(false),
      inDict(false) {
}

RDxfImporter::~RDxfImporter() {
}

bool RDxfImporter::importFile(const QString& fileName, const QString& nameFilter) {
    Q_UNUSED(nameFilter);

    this->fileName = fileName;
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

    // detect QCAD 2 DXF file format (dxflib 2.x):
    dxfServices.detectVersion2Format(fileName);

    lockedLayers.clear();
    mtext = "";
    textStyles.clear();

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

    DL_Dxf dxflib;

#ifdef Q_OS_WIN
    wchar_t* winfn = new wchar_t[2000];
    int len = fileName.toWCharArray(winfn);
    winfn[len] = '\0';
    bool success = dxflib.in((std::istream&)std::ifstream(winfn, std::ifstream::in), this);
#else
    bool success = dxflib.in((const char*)fileName.toUtf8(), this);
#endif

    if (success==false) {
        qWarning() << "Cannot open DXF file: " << fileName;
        return false;
    }

    document->setFileVersion("R15 (2000) DXF Drawing (dxflib) (*.dxf)");

    // make sure dimension font is set to standard,
    // the only dimension font supported by the QCAD CE:
    document->setDimensionFont("Standard");

    // dimension text color always by block:
    QVariant v;
    v.setValue(RColor(RColor::ByBlock));
    document->setKnownVariable(RS::DIMCLRT, v);

    // lock locked layers now. they are unlocked during import to load
    // the entities on them:
    for (int i=0; i<lockedLayers.size(); i++) {
        RModifyObjectsOperation op;
        QSharedPointer<RLayer> layer = document->queryLayer(lockedLayers.at(i));
        if (layer.isNull()) {
            continue;
        }
        layer->setLocked(true);
        op.addObject(layer);
        op.apply(*document, false);
    }

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

void RDxfImporter::processCodeValuePair(unsigned int groupCode, const std::string& groupValue) {
    Q_UNUSED(groupCode)
    Q_UNUSED(groupValue)

    //printf("group code: %d\n", groupCode);
    //printf("group value: %s\n", groupValue);
}



void RDxfImporter::addLayer(const DL_LayerData& data) {
    QString layerName = decode(data.name.c_str());

    bool off = attributes.getColor()<0;
    bool frozen = data.flags&0x01;
    bool locked = data.flags&0x04;
    attributes.setColor(abs(attributes.getColor()));
    RColor color = RDxfServices::attributesToColor(
        attributes.getColor(), attributes.getColor24(), dxfColors, true);
    RLinetype::Id linetypeId = RLinetype::INVALID_ID;
    linetypeId = document->getLinetypeId(attributes.getLinetype().c_str());
    if (linetypeId == RLinetype::INVALID_ID) {
        linetypeId = document->getLinetypeId("CONTINUOUS");
    }
    RLineweight::Lineweight lw = RDxfServices::numberToWeight(attributes.getWidth());

    if (lw==RLineweight::WeightByLayer) {
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

void RDxfImporter::addLinetype(const DL_LinetypeData& data) {
    QString name = decode(data.name.c_str());
    QString description = decode(data.description.c_str());
    //QString description = decode(data.description.c_str());
    //int numDashes = data.numberOfDashes;
    //double patternLength = data.patternLength;

    if (pattern.count() > 0) {
        for (int i = 0; i < pattern.count(); i++) {
            if (pattern.at(i) == 0) {
                // subtract half of 0.1 (0.05) from previous space
                // and following space (if any)
                // The spaces are negative numbers so we add 0.05
                if (i == 0) {
                    pattern.replace(i, 0.1);
                    pattern.replace(i + 1, pattern.at(i + 1) + 0.1);
                } else if (i > 0 && i < pattern.count() - 1) {
                    pattern.replace(i - 1, pattern.at(i - 1) + 0.05);
                    pattern.replace(i, 0.1);
                    pattern.replace(i + 1, pattern.at(i + 1) + 0.05);
                } else if (i == pattern.count() - 1) {
                    pattern.replace(i - 1, pattern.at(i - 1) + 0.1);
                    pattern.replace(i, 0.1);
                }
            }
        }
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

void RDxfImporter::addLinetypeDash(double length) {
    pattern.append(length);
}

void RDxfImporter::addBlock(const DL_BlockData& data) {
    QString blockName = decode(data.name.c_str());

    /*
    if (blockName.toLower()=="*paper_space0" ||
        blockName.toLower()=="*paper_space" ||
        blockName.toLower()=="*model_space" ||
        blockName.toLower()=="$paper_space0" ||
        blockName.toLower()=="$paper_space" ||
        blockName.toLower()=="$model_space") {
        return;
    }
    */

    // ignore internal dimension entity blocks:
    if (blockName.toLower().startsWith("*d")) {
        setCurrentBlockId(RBlock::INVALID_ID);
        return;
    }

    // fix invalid block names (mainly from QCAD 2):
    // TODO
//    if (!blockName.startsWith("*")) {
//        QString oldBlockName = blockName;
//        blockName.replace(QRegExp("[<>/\":;?*|,=`\\\\]"), "_");
//        version2BlockMapping.insert(oldBlockName, blockName);
//    }

    RVector bp(data.bpx, data.bpy);
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

void RDxfImporter::endBlock() {
    setCurrentBlockId(document->getModelSpaceBlockId());
}

void RDxfImporter::endEntity() {
    if (polyline.countVertices()>1) {
        QSharedPointer<RPolylineEntity> entity(new RPolylineEntity(document, RPolylineData(polyline)));
        entity->setPolylineGen(polylinePlineGen);
        importEntity(entity);
        polyline = RPolyline();
    }
    if (leader.countVertices()>1) {
        QSharedPointer<RLeaderEntity> entity(new RLeaderEntity(document, leader));
        importEntity(entity);
        leader = RLeaderData();
    }
    if (spline.isValid()) {
//        bool periodic = true;
//        QList<RVector> controlPoints = spline.getControlPoints();
//        QList<double> knots = spline.getKnotVector();

//        for (int i=0; i<spline.getDegree(); i++) {
//            if (controlPoints.at(i).getDistanceTo(controlPoints.at(controlPoints.size()-spline.getDegree()+i)) > RS::PointTolerance) {
//                periodic = false;
//            }
//        }

//        if (periodic) {
//            for (int i=0; i<spline.getDegree(); ++i) {
//                controlPoints.removeLast();
//            }
//            spline.setControlPoints(controlPoints);
//            spline.setPeriodic(true);
//        }
//        else {
//            spline.setControlPoints(controlPoints);
//            spline.setKnotVector(knots);
//        }

        QList<RVector> fitPoints = spline.getFitPoints();
        if (!fitPoints.isEmpty() && spline.isPeriodic()) {
            // TODO: check for start / end tangent equality if given:
            if (fitPoints.first().equalsFuzzy(fitPoints.last())) {
                spline.setPeriodic(true);
                //fitPoints.removeLast();
                spline.removeLastFitPoint();
            }
            else {
                spline.setPeriodic(false);
            }
        }
        else {
            spline.setPeriodic(false);
        }

        QList<double> kv = spline.getKnotVector();

        if (kv.size()>=2) {
            // remove historical, superfluous knots:
            kv.removeFirst();
            kv.removeLast();
        }

        spline.setKnotVector(kv);

        QSharedPointer<RSplineEntity> entity(new RSplineEntity(document, RSplineData(spline)));
        importEntity(entity);
        spline = RSpline();
    }
    if (hatch.getLoopCount()>0) {
        QSharedPointer<RHatchEntity> entity(new RHatchEntity(document, hatch));
        importEntity(entity);
        hatch = RHatchData();
    }
}

void RDxfImporter::endSection() {
    xData.clear();
    xDataAppId = "";
}

void RDxfImporter::importEntity(QSharedPointer<REntity> entity) {
    if (getCurrentBlockId()==RBlock::INVALID_ID) {
        qDebug() << "RDxfImporter::importEntity: ignoring entity";
        return;
    }

    // Layer:
    QString layerName = decode(attributes.getLayer().c_str());
    if (layerName.isEmpty()) {
        qWarning() << "RDxfImporter::importEntity: default to layer: '0'";
        entity->setLayerId(document->getLayer0Id());
    } else {
        // add layer in case it doesn't exist:
        if (document->queryLayer(layerName).isNull()) {
            qWarning() << "RDxfImporter::importEntity: "
                << "creating layer: " << layerName;
            addLayer(DL_LayerData(attributes.getLayer(), 0));
        }

        entity->setLayerId(document->getLayerId(layerName));
    }

    // Color:
    RColor col = RDxfServices::numberToColor(attributes.getColor(), dxfColors);
    RColor col24 = RDxfServices::numberToColor24(attributes.getColor24());

    // bylayer / byblock overrules all colors:
    if (col.isByBlock() || col.isByLayer()) {
        entity->setColor(col);
    }
    else {
        // 24 bit colors overrule palette colors:
        if (attributes.getColor24()!=-1) {
            entity->setColor(col24);
        }
        else {
            entity->setColor(col);
        }
    }

    // Linetype:
    QString linetypeName = decode(attributes.getLinetype().c_str());
    RLinetype::Id linetypeId = document->getLinetypeId(linetypeName);
    if (linetypeId==RLinetype::INVALID_ID) {
        qWarning() << "RDxfImporter::importEntity: "
            << "unsupported linetype name (defaulting to BYLAYER): "
            << linetypeName;
        linetypeId = document->getLinetypeByLayerId();
    }
    entity->setLinetypeId(linetypeId);

    // Linetype scale:
    entity->setLinetypeScale(attributes.getLinetypeScale());

    // Width:
    entity->setLineweight(RDxfServices::numberToWeight(attributes.getWidth()));

    int handle = attributes.getHandle();
    if (handle!=-1) {
        document->getStorage().setObjectHandle(*entity, handle);
    }

    // Block:
    if (attributes.isInPaperSpace()) {
        RBlock::Id paperSpaceBlockId = document->getBlockId("*Paper_Space");
        if (paperSpaceBlockId!=RBlock::INVALID_ID) {
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

void RDxfImporter::addPoint(const DL_PointData& data) {
    RVector v(data.x, data.y);
    QSharedPointer<RPointEntity> entity(
        new RPointEntity(document, RPointData(v))
    );
    importEntity(entity);
}

void RDxfImporter::addLine(const DL_LineData& data) {
    RVector v1(data.x1, data.y1);
    RVector v2(data.x2, data.y2);
    QSharedPointer<RLineEntity> entity(
        new RLineEntity(document, RLineData(v1, v2))
    );
    importEntity(entity);
}

void RDxfImporter::addXLine(const DL_XLineData& data) {
    RVector v1(data.bx, data.by);
    RVector v2(data.dx, data.dy);
    QSharedPointer<RXLineEntity> entity(
        new RXLineEntity(document, RXLineData(v1, v2))
    );
    importEntity(entity);
}

void RDxfImporter::addRay(const DL_RayData& data) {
    RVector v1(data.bx, data.by);
    RVector v2(data.dx, data.dy);
    QSharedPointer<RRayEntity> entity(
        new RRayEntity(document, RRayData(v1, v2))
    );
    importEntity(entity);
}

void RDxfImporter::addArc(const DL_ArcData& data) {
    RVector v(data.cx, data.cy);
    QSharedPointer<RArcEntity> entity(
        new RArcEntity(document,
            RArcData(v, data.radius,
                RMath::deg2rad(data.angle1),
                RMath::deg2rad(data.angle2),
                false)
        )
    );

    if (getExtrusion()->getDirection()[2]<0.0) {
        entity->flipHorizontal();
    }

    importEntity(entity);
}

void RDxfImporter::addEllipse(const DL_EllipseData& data) {
    RVector v1(data.cx, data.cy);
    RVector v2(data.mx, data.my);
    QSharedPointer<REllipseEntity> entity(
        new REllipseEntity(document,
            REllipseData(v1, v2,
                data.ratio,
                data.angle1,
                data.angle2,
                false)
        )
    );
    importEntity(entity);
}

void RDxfImporter::addCircle(const DL_CircleData& data) {
    RVector v(data.cx, data.cy);
    QSharedPointer<RCircleEntity> entity(
        new RCircleEntity(document,
            RCircleData(v, data.radius)
        )
    );
    importEntity(entity);
}

void RDxfImporter::addPolyline(const DL_PolylineData& data) {
    polyline = RPolyline();
    polyline.setClosed(data.flags&0x1);
    polylinePlineGen = data.flags&0x80;
}

void RDxfImporter::addVertex(const DL_VertexData& data) {
    RVector v(data.x, data.y);
    polyline.appendVertex(v, data.bulge);
}

void RDxfImporter::addSpline(const DL_SplineData& data) {
    spline.setDegree(data.degree);
    spline.setPeriodic(data.flags&0x2);
    RVector tanS(data.tangentStartX, data.tangentStartY, data.tangentStartZ);
    RVector tanE(data.tangentEndX, data.tangentEndY, data.tangentEndZ);
    if (tanS.getMagnitude()>RS::PointTolerance) {
        spline.setTangentAtStart(tanS);
    }
    if (tanE.getMagnitude()>RS::PointTolerance) {
        spline.setTangentAtEnd(tanE);
    }
}

void RDxfImporter::addControlPoint(const DL_ControlPointData& data) {
    RVector v(data.x, data.y);

    // weight is ignored for now:
    //double w = data.w;

    spline.appendControlPoint(v);
}

void RDxfImporter::addFitPoint(const DL_FitPointData& data) {
    RVector v(data.x, data.y);
    spline.appendFitPoint(v);
}

void RDxfImporter::addKnot(const DL_KnotData& data) {
//    printf("add knot\n");
    spline.appendKnot(data.k);
}

void RDxfImporter::addInsert(const DL_InsertData& data) {
    QString blockName = decode(data.name.c_str());
//    if (blockName.left(3)=="A$C") {
//        return;
//    }

    RBlock::Id blockId = RBlock::INVALID_ID;

//    RBlock::Id blockId = document->getBlockId(blockName);
//    if (blockId==RBlock::INVALID_ID) {
//        qWarning() << "RDxfImporter::import: "
//                   << "block reference references invalid block: " << blockName;
//        return;
//    }

    RVector insertionPoint(data.ipx, data.ipy);
    RVector scale(data.sx, data.sy);

    QSharedPointer<RBlockReferenceEntity> entity(
            new RBlockReferenceEntity(
                    document,
                    RBlockReferenceData(
                            blockId,
                            insertionPoint,
                            scale,
                            RMath::deg2rad(data.angle),
                            data.cols, data.rows,
                            data.colSp, data.rowSp
                    )
            )
    );
    entity->setCustomProperty("", "block", blockName);

    importEntity(entity);
}

void RDxfImporter::addSolid(const DL_SolidData& data) {
    RVector v1(data.x[0], data.y[0], data.z[0]);
    RVector v2(data.x[1], data.y[1], data.z[1]);
    RVector v3(data.x[2], data.y[2], data.z[2]);
    RVector v4(data.x[3], data.y[3], data.z[3]);

    RSolidData d;
    if (v3.equalsFuzzy(v4)) {
        // last two vertices identical: triangle:
        d = RSolidData(v1, v2, v3);
    }
    else {
        d = RSolidData(v1, v2, v3, v4);
    }

    QSharedPointer<RSolidEntity> entity(new RSolidEntity(document, d));
    importEntity(entity);
}

void RDxfImporter::addTrace(const DL_TraceData& data) {
    RVector v1(data.x[0], data.y[0], data.z[0]);
    RVector v2(data.x[1], data.y[1], data.z[1]);
    RVector v3(data.x[2], data.y[2], data.z[2]);
    RVector v4(data.x[3], data.y[3], data.z[3]);

    QSharedPointer<RTraceEntity> entity(
        new RTraceEntity(document, RTraceData(v1, v2, v3, v4))
    );
    importEntity(entity);
}

void RDxfImporter::addTextStyle(const DL_StyleData& data) {
    QString xDataFont = getXDataString("ACAD", 1000, 0);
    int xDataFlags = getXDataInt("ACAD", 1071, 0);

    RDxfTextStyle s;

    s.font = decode(data.primaryFontFile.c_str());
    //qDebug() << "text style: name:" << (const char*)data.name.c_str();
    //qDebug() << "text style: s.font:" << s.font;
    s.font = s.font.replace(".ttf", "", Qt::CaseInsensitive);
    s.font = s.font.replace(".shx", "", Qt::CaseInsensitive);
    if (s.font.isEmpty()) {
        s.font = xDataFont;
        //qDebug() << "text style: xDataFont:" << xDataFont;
    }

    s.italic = xDataFlags&0x1000000;
    s.bold = xDataFlags&0x2000000;

    textStyles.insert(decode(data.name.c_str()), s);
}

void RDxfImporter::addMTextChunk(const std::string& text) {
    mtext.append(text.c_str());
}

void RDxfImporter::addMText(const DL_MTextData& data) {
    RVector ip(data.ipx, data.ipy);
    //RVector dirx(data.dirx, data.diry);
    RS::VAlign valign;
    RS::HAlign halign;
    RS::TextDrawingDirection dir;
    RS::TextLineSpacingStyle lss;

    RDxfTextStyle s = textStyles.value(decode(data.style.c_str()), RDxfTextStyle());

    // QCAD 2 compat: use style name as font name:
    if (s.font.isEmpty()) {
        s.font = decode(data.style.c_str());
    }

    if (data.attachmentPoint<=3) {
        valign=RS::VAlignTop;
    } else if (data.attachmentPoint<=6) {
        valign=RS::VAlignMiddle;
    } else {
        valign=RS::VAlignBottom;
    }

    if (data.attachmentPoint%3==1) {
        halign=RS::HAlignLeft;
    } else if (data.attachmentPoint%3==2) {
        halign=RS::HAlignCenter;
    } else {
        halign=RS::HAlignRight;
    }

    if (data.drawingDirection==1) {
        dir = RS::LeftToRight;
    } else if (data.drawingDirection==3) {
        dir = RS::TopToBottom;
    } else {
        dir = RS::ByStyle;
    }

    if (data.lineSpacingStyle==1) {
        lss = RS::AtLeast;
    } else {
        lss = RS::Exact;
    }

    mtext.append(data.text.c_str());
    mtext.replace(QByteArray("^ "), QByteArray("^"));
    QString mtextString = QString(mtext);

    QVariant vDwgCodePage = document->getKnownVariable(RS::DWGCODEPAGE);
    if (vDwgCodePage.isValid()) {
        QString dwgCodePage = vDwgCodePage.toString();
        QString enc = getEncoding(dwgCodePage);

        // get the text codec:
        QTextCodec* codec = QTextCodec::codecForName(enc.toLatin1());
        if (codec!=NULL) {
            mtextString = codec->toUnicode(mtext);
        }
        else {
            qWarning() << "RDxfImporter::addMText: unsupported text codec: " << enc;
        }
    }

    // use default style for the drawing:
    if (s.font.isEmpty()) {
        // japanese, cyrillic:
        QString codepage = document->getKnownVariable(RS::DWGCODEPAGE, "ANSI_1252").toString().toUpper();
        if (codepage=="ANSI_932" || codepage=="ANSI_1251") {
            s.font = "Unicode";
        } else {
            s.font = document->getKnownVariable(RS::TEXTSTYLE, "Standard").toString();
        }
    }

    dxfServices.fixVersion2String(mtextString);

    RTextData d(
        RVector::invalid, ip,
        data.height, data.width,
        valign, halign,
        dir, lss,
        data.lineSpacingFactor,
        mtextString, s.font,
        s.bold,
        s.italic,
        data.angle,
        false
    );

    QSharedPointer<RTextEntity> entity(new RTextEntity(document, d));
    importEntity(entity);

    mtext = "";
}

RTextBasedData RDxfImporter::getTextBasedData(const DL_TextData& data) {
    RS::VAlign valign;
    RS::HAlign halign;

    RDxfTextStyle s = textStyles.value(decode(data.style.c_str()), RDxfTextStyle());

    // QCAD 2 compat: use style name as font name:
    if (s.font.isEmpty()) {
        s.font = decode(data.style.c_str());
    }

    RVector alignmentPoint(data.apx, data.apy);
    RVector position(data.ipx, data.ipy);

    if (data.vJustification!=0 || data.hJustification!=0) {

        // horizontal alignment:
        switch (data.hJustification) {
        default:
        case 0: // left aligned
            halign = RS::HAlignLeft;
            //refPoint = alignmentPoint;
            break;
        case 1: // centered
            halign = RS::HAlignCenter;
            //refPoint = alignmentPoint;
            break;
        case 2: // right aligned
            halign = RS::HAlignRight;
            //refPoint = RVector(data.apx, data.apy);
            break;
        case 3: // aligned (TODO)
            halign = RS::HAlignCenter;
            //refPoint = RVector((data.ipx+data.apx)/2.0,
            //                     (data.ipy+data.apy)/2.0);
            //angle =
            //    RVector(data.ipx, data.ipy).getAngleTo(
            //        RVector(data.apx, data.apy));
            break;
        case 4: // Middle (TODO)
            halign = RS::HAlignCenter;
            //refPoint = RVector(data.apx, data.apy);
            break;
        case 5: // fit (TODO)
            halign = RS::HAlignCenter;
//            refPoint = RVector((data.ipx+data.apx)/2.0,
//                                 (data.ipy+data.apy)/2.0);
//            angle =
//                RVector(data.ipx, data.ipy).getAngleTo(
//                    RVector(data.apx, data.apy));
            break;
        }

        // vertical alignment:
        switch (data.vJustification) {
        default:
        case 0: // baseline
            valign = RS::VAlignBase;
            break;

        case 1: // bottom
            valign = RS::VAlignBottom;
            break;

        case 2: // middle
            valign = RS::VAlignMiddle;
            break;

        case 3: // top
            valign = RS::VAlignTop;
            break;
        }
    } else {
        halign = RS::HAlignLeft;
        valign = RS::VAlignBase;
        //refPoint = RVector(data.ipx, data.ipy);
    }

    //int drawingDirection = 5;
    //double width = 100.0;
    double width = 0.0;

    RTextBasedData textBasedData(
        RVector::invalid, RVector::invalid,
//        refPoint, refPoint,
        data.height, width,
        valign, halign,
        RS::LeftToRight, RS::Exact,
        1.0,
        data.text.c_str(),
        s.font,
        s.bold,                      // bold
        s.italic,                    // italic
        data.angle,
        true                         // simple
    );

    textBasedData.setPosition(position);

    // if alignment is left / base or alignment point is omitted for other reason,
    // set alignment point to same as position.
    if ((textBasedData.getHAlign()==RS::HAlignLeft && textBasedData.getVAlign()==RS::VAlignBase) ||
        (RMath::isNaN(alignmentPoint.x) || RMath::isNaN(alignmentPoint.y))) {

        textBasedData.setAlignmentPoint(position);
    }
    else {
        // QCAD 1 compatibility:
        if (s.font=="txt" && qAbs(alignmentPoint.x)<RS::PointTolerance && qAbs(alignmentPoint.y)<RS::PointTolerance) {
            textBasedData.setAlignmentPoint(position);
        }
        else {
            textBasedData.setAlignmentPoint(alignmentPoint);
        }
    }

    return textBasedData;
}

/**
 * Implementation of the method which handles
 * texts (TEXT).
 */
void RDxfImporter::addText(const DL_TextData& data) {
    RTextBasedData d = getTextBasedData(data);
    QSharedPointer<RTextEntity> entity(new RTextEntity(document, RTextData(d)));
    importEntity(entity);
}

void RDxfImporter::addArcAlignedText(const DL_ArcAlignedTextData& data) {
    // TODO
    qDebug() << "addArcAlignedText";
    qDebug() << "text" << data.text.c_str();
    qDebug() << "cx" << data.cx;
    qDebug() << "cy" << data.cy;
    qDebug() << "cz" << data.cz;
    qDebug() << "radius" << data.radius;
    qDebug() << "font" << data.font.c_str();
    qDebug() << "style" << data.style.c_str();
    qDebug() << "alignment" << data.alignment;
    qDebug() << "char set" << data.characerSet;
    qDebug() << "char order" << data.reversedCharacterOrder;
}


/**
 * Implementation of the method which handles
 * block attributes (ATTRIB).
 */
void RDxfImporter::addAttribute(const DL_AttributeData& data) {
    RTextBasedData d = getTextBasedData(data);
    QSharedPointer<RAttributeEntity> entity(new RAttributeEntity(document, RAttributeData(d, getCurrentBlockId(), data.tag.c_str())));
    importEntity(entity);
}


RDimensionData RDxfImporter::convDimensionData(const DL_DimensionData& data) {
    RVector defP(data.dpx, data.dpy);
    RVector midP(data.mpx, data.mpy);
    RS::VAlign valign;
    RS::HAlign halign;
    RS::TextLineSpacingStyle lss;

    QString t;

    if (dxfServices.getVersion2Compatibility()) {
        // middlepoint of text can be 0/0 which is considered to be invalid (!):
        //  because older QCad 1 versions save the middle of the text as 0/0
        //  althought they didn't support custom text positions.
        if (fabs(data.mpx)<1.0e-6 && fabs(data.mpy)<1.0e-6) {
            midP = RVector::invalid;
        }
    }

    // auto positioned:
    if ((data.type&0x80)==0) {
        midP = RVector::invalid;
    }

    if (data.attachmentPoint<=3) {
        valign=RS::VAlignTop;
    } else if (data.attachmentPoint<=6) {
        valign=RS::VAlignMiddle;
    } else {
        valign=RS::VAlignBottom;
    }

    if (data.attachmentPoint%3==1) {
        halign=RS::HAlignLeft;
    } else if (data.attachmentPoint%3==2) {
        halign=RS::HAlignCenter;
    } else {
        halign=RS::HAlignRight;
    }

    if (data.lineSpacingStyle==1) {
        lss = RS::AtLeast;
    } else {
        lss = RS::Exact;
    }

    t = decode(data.text.c_str());
    t.replace("^ ", "^");
    dxfServices.fixVersion2String(t);
    QString uTol, lTol;
    dxfServices.fixDimensionLabel(t, uTol, lTol);

    // data needed to add the actual dimension entity
    RDimensionData ret(defP, midP,
                       valign, halign,
                       lss,
                       data.lineSpacingFactor,
                       t, "Standard",
                       data.angle);
    ret.setUpperTolerance(uTol);
    ret.setLowerTolerance(lTol);
    ret.setArrow1Flipped(data.arrow1Flipped);
    ret.setArrow2Flipped(data.arrow2Flipped);

    if (midP.isValid()) {
        ret.setCustomTextPosition(true);
    }

    if (xData.contains("ACAD")) {
        QList<QPair<int, QVariant> > list = xData["ACAD"];
        for (int i=0; i<list.size(); i++) {
            QPair<int, QVariant> tuple = list[i];
            // linear factor override (DIMLFAC):
            if (tuple.first==1070 && tuple.second==144 && i<list.size()-1) {
                tuple = list[i+1];
                if (tuple.first==1040) {
                    ret.setLinearFactor(tuple.second.toDouble());
                }
            }
            // dimension scale (DIMSCALE):
            if (tuple.first==1070 && tuple.second==40 && i<list.size()-1) {
                tuple = list[i+1];
                if (tuple.first==1040) {
                    ret.setDimScale(tuple.second.toDouble());
                }
            }
        }
    }

    return ret;
}

void RDxfImporter::addDimAlign(const DL_DimensionData& data, const DL_DimAlignedData& edata) {
    RDimensionData dimData = convDimensionData(data);

    RVector ext1(edata.epx1, edata.epy1);
    RVector ext2(edata.epx2, edata.epy2);

    RDimAlignedData d(dimData, ext1, ext2);

    QSharedPointer<RDimAlignedEntity> entity(new RDimAlignedEntity(document, d));
    importEntity(entity);
}

void RDxfImporter::addDimLinear(const DL_DimensionData& data,
                                const DL_DimLinearData& edata) {
    RDimensionData dimData = convDimensionData(data);

    RVector dxt1(edata.dpx1, edata.dpy1);
    RVector dxt2(edata.dpx2, edata.dpy2);

    RDimRotatedData d(dimData, dxt1, dxt2, RMath::deg2rad(edata.angle));

    QSharedPointer<RDimRotatedEntity> entity(new RDimRotatedEntity(document, d));
    importEntity(entity);
}

void RDxfImporter::addDimRadial(const DL_DimensionData& data,
                                const DL_DimRadialData& edata) {
    RDimensionData dimData = convDimensionData(data);
    RVector dp(edata.dpx, edata.dpy);

    RDimRadialData d(dimData, dp);

    QSharedPointer<RDimRadialEntity> entity(new RDimRadialEntity(document, d));
    importEntity(entity);
}

void RDxfImporter::addDimDiametric(const DL_DimensionData& data,
                                   const DL_DimDiametricData& edata) {
    RDimensionData dimData = convDimensionData(data);
    RVector dp(edata.dpx, edata.dpy);

    RDimDiametricData d(dimData, dp);

    QSharedPointer<RDimDiametricEntity> entity(new RDimDiametricEntity(document, d));
    importEntity(entity);
}

void RDxfImporter::addDimAngular(const DL_DimensionData& data,
                                 const DL_DimAngular2LData& edata) {
    RDimensionData dimData = convDimensionData(data);
    RVector dp1(edata.dpx1, edata.dpy1);
    RVector dp2(edata.dpx2, edata.dpy2);
    RVector dp3(edata.dpx3, edata.dpy3);
    RVector dp4(edata.dpx4, edata.dpy4);

    RDimAngular2LData d(dimData, dp1, dp2, dp3, dp4);

    QSharedPointer<RDimAngular2LEntity> entity(new RDimAngular2LEntity(document, d));
    importEntity(entity);
}

void RDxfImporter::addDimAngular3P(const DL_DimensionData& data,
                                   const DL_DimAngular3PData& edata) {

    RDimensionData dimData = convDimensionData(data);
    RVector center(edata.dpx3, edata.dpy3);
    RVector dp1(edata.dpx1, edata.dpy1);
    RVector dp2(edata.dpx2, edata.dpy2);

    RDimAngular3PData d(dimData, center, dp1, dp2);

    QSharedPointer<RDimAngular3PEntity> entity(new RDimAngular3PEntity(document, d));
    importEntity(entity);
}

void RDxfImporter::addDimOrdinate(const DL_DimensionData& data,
                               const DL_DimOrdinateData& edata) {
    RDimensionData dimData = convDimensionData(data);
    RVector leaderEndPoint(edata.dpx2, edata.dpy2);
    RVector definingPoint(edata.dpx1, edata.dpy1);

    RDimOrdinateData d(dimData, leaderEndPoint, definingPoint);
    if (edata.xtype) {
        d.setMeasuringXAxis();
    }
    else {
        d.setMeasuringYAxis();
    }

    QSharedPointer<RDimOrdinateEntity> entity(new RDimOrdinateEntity(document, d));
    importEntity(entity);
}

void RDxfImporter::addLeader(const DL_LeaderData& data) {
    leader = RLeaderData();
    leader.setDocument(document);

    if (xData.contains("ACAD")) {
        QList<QPair<int, QVariant> > list = xData["ACAD"];
        for (int i=0; i<list.size(); i++) {
            QPair<int, QVariant> tuple = list[i];
            // dimension scale (DIMSCALE):
            if (tuple.first==1070 && tuple.second==40 && i<list.size()-1) {
                tuple = list[i+1];
                if (tuple.first==1040) {
                    leader.setDimScaleOverride(tuple.second.toDouble());
                }
            }
        }
    }

    leaderArrowHead = data.arrowHeadFlag==1;
}

void RDxfImporter::addLeaderVertex(const DL_LeaderVertexData& data) {
    RVector v(data.x, data.y);
    leader.appendVertex(v);
    leader.setArrowHead(leaderArrowHead);
}

void RDxfImporter::addHatch(const DL_HatchData& data) {
    QString patternName = decode(data.pattern.c_str());
    double angle = RMath::deg2rad(data.angle);
    double scale = data.scale;

    if (dxfServices.getVersion2Compatibility()) {
        dxfServices.fixVersion2HatchData(patternName, angle, scale, data.solid);
    }

    hatch = RHatchData(data.solid, scale, angle, patternName);

    // xData might contain hatch origin:
    if (xData.contains("ACAD")) {
        RVector op;
        QList<QPair<int, QVariant> > list = xData["ACAD"];
        for (int i=0; i<list.size(); i++) {
            QPair<int, QVariant> tuple = list[i];
            // hatch pattern offset:
            if (tuple.first==1010) {
                op.x = tuple.second.toDouble();
            }
            if (tuple.first==1020) {
                op.y = tuple.second.toDouble();
            }
        }
        hatch.setOriginPoint(op);
    }
}

void RDxfImporter::addHatchLoop(const DL_HatchLoopData& data) {
    Q_UNUSED(data)
    hatch.newLoop();
}

void RDxfImporter::addHatchEdge(const DL_HatchEdgeData& data) {
    QSharedPointer<RShape> shape;

    switch (data.type) {
    case 0: {
        RPolyline pl;
        for (int i=0; (unsigned long)i<data.vertices.size(); i++) {
            if (data.vertices[i].size()==2) {
                pl.appendVertex(RVector(data.vertices[i][0], data.vertices[i][1]));
            }
            else if (data.vertices[i].size()==3) {
                pl.appendVertex(RVector(data.vertices[i][0], data.vertices[i][1]), data.vertices[i][2]);
            }
        }
        pl.setClosed(true);
        shape = QSharedPointer<RShape>(new RPolyline(pl));
        } break;

    case 1:
        shape = QSharedPointer<RShape>(
            new RLine(RVector(data.x1, data.y1),
                      RVector(data.x2, data.y2))
        );
        break;

    case 2:
        if (data.ccw && data.angle1<RS::AngleTolerance && data.angle2>2*M_PI-RS::AngleTolerance) {
            shape = QSharedPointer<RShape>(
                //new RCircle(RVector(data.cx, data.cy), data.radius)
                new RArc(RVector(data.cx, data.cy),
                     data.radius,
                     0.0,
                     2*M_PI,
                     false)
            );
        } else {
            if (data.ccw) {
                shape = QSharedPointer<RShape>(
                    new RArc(RVector(data.cx, data.cy),
                             data.radius,
                             RMath::getNormalizedAngle(data.angle1),
                             RMath::getNormalizedAngle(data.angle2),
                             false)
                );
            } else {
                shape = QSharedPointer<RShape>(
                    new RArc(RVector(data.cx, data.cy),
                             data.radius,
                             RMath::getNormalizedAngle(2*M_PI-data.angle1),
                             RMath::getNormalizedAngle(2*M_PI-data.angle2),
                             true)
                );
            }
        }
        break;

    case 3:
        if (!data.ccw) {
            REllipse* el = new REllipse(RVector(data.cx, data.cy),
                         RVector(data.mx, data.my),
                         data.ratio,
                         0.0,
                         0.0,
                         true);
            el->setStartAngle(-data.angle1);
            el->setEndAngle(-data.angle2);
            shape = QSharedPointer<RShape>(el);
        }
        else {
            REllipse* el = new REllipse(RVector(data.cx, data.cy),
                             RVector(data.mx, data.my),
                             data.ratio,
                             0.0,
                             0.0,
                             false);
            el->setStartAngle(data.angle1);
            el->setEndAngle(data.angle2);
            shape = QSharedPointer<RShape>(el);
        }
        break;

    case 4: {
        RSpline* s = new RSpline();

        s->setDegree(data.degree);
        QList<RVector> controlPoints;
        for (int i=0; (unsigned long)i<data.controlPoints.size(); i++) {
            RVector v(data.controlPoints[i][0], data.controlPoints[i][1]);
            controlPoints.append(v);
        }
        QList<double> knots;
        for (int i=0; (unsigned long)i<data.knots.size(); i++) {
            knots.append(data.knots[i]);
        }
        //Q_ASSERT(data.degree + 1 + controlPoints.size() == knots.size());

        bool periodic = true;
        for (unsigned int i=0; i<data.degree; i++) {
            if (!controlPoints.at(i).equalsFuzzy(controlPoints.at(controlPoints.size()-data.degree+i))) {
                periodic = false;
                break;
            }
        }

        if (periodic) {
            for (unsigned int i=0; i<data.degree; ++i) {
                controlPoints.removeLast();
            }
            s->setControlPoints(controlPoints);
            s->setPeriodic(true);
        }
        else {
            s->setControlPoints(controlPoints);
            if (!knots.isEmpty()) {
                knots.removeFirst();
            }
            if (!knots.isEmpty()) {
                knots.removeLast();
            }
            s->setKnotVector(knots);
        }

        shape = QSharedPointer<RShape>(s);
        }
        break;

    default:
        break;
    }

    if (!shape.isNull()) {
        hatch.addBoundary(shape);
    }
}

void RDxfImporter::addImage(const DL_ImageData& data) {
    int handle = QString(data.ref.c_str()).toInt(NULL, 16);
    RVector ip(data.ipx, data.ipy);
    RVector uv(data.ux, data.uy);
    RVector vv(data.vx, data.vy);

    RImageData d("", ip, uv, vv, data.brightness, data.contrast, data.fade);

    QSharedPointer<RImageEntity> entity(new RImageEntity(document, d));
    importEntity(entity);
    images.insertMulti(handle, entity->getId());
}

void RDxfImporter::linkImage(const DL_ImageDefData& data) {
    int handle = QString(data.ref.c_str()).toInt(NULL, 16);

    if (!images.contains(handle)) {
        qWarning() << "unused image definition: " << data.ref.c_str();
        return;
    }

    QString filePath = decode(data.file.c_str());

    QList<RObject::Id> imageData = images.values(handle);
    for (int i=0; i<imageData.length(); i++) {
        RObject::Id id = imageData.at(i);
        QSharedPointer<REntity> entity = document->queryEntity(id);
        if (entity.isNull()) {
            continue;
        }
        QSharedPointer<RImageEntity> image = entity.dynamicCast<RImageEntity>();
        if (image.isNull()) {
            continue;
        }
        //image->setFileName(fi.absoluteFilePath());
        image->setFileName(filePath);
        importObjectP(image);
    }

    images.remove(handle);
}

void RDxfImporter::addXRecord(const std::string& handle) {
    if (qcadDict.count(handle.c_str())==1) {
        variableKey = qcadDict[handle.c_str()];
    }
    else {
        variableKey = QString();
    }
}

void RDxfImporter::addXRecordString(int code, const std::string& value) {
    Q_UNUSED(code)

    if (variableKey.isEmpty()) {
        return;
    }
    document->setVariable(variableKey, decode(value.c_str()));
}

void RDxfImporter::addXRecordReal(int code, double value) {
    Q_UNUSED(code)

    if (variableKey.isEmpty()) {
        return;
    }
    document->setVariable(variableKey, value);
}

void RDxfImporter::addXRecordInt(int code, int value) {
    Q_UNUSED(code)

    if (variableKey.isEmpty()) {
        return;
    }
    document->setVariable(variableKey, value);
}

void RDxfImporter::addXRecordBool(int code, bool value) {
    Q_UNUSED(code)

    if (variableKey.isEmpty()) {
        return;
    }
    document->setVariable(variableKey, value);
}

void RDxfImporter::addXDataApp(const std::string& appId) {
    xDataAppId = decode(appId.c_str());
    xData.insert(xDataAppId, QList<QPair<int, QVariant> >());
}

void RDxfImporter::addXDataString(int code, const std::string& value) {
    if (!xData.contains(xDataAppId)) {
        qWarning() << "RDxfImporter::addXDataString: app ID not found: " << xDataAppId;
        return;
    }

    xData[xDataAppId].append(QPair<int, QVariant>(code, decode(value.c_str())));
}

void RDxfImporter::addXDataReal(int code, double value) {
    if (!xData.contains(xDataAppId)) {
        qWarning() << "RDxfImporter::addXDataString: app ID not found: " << xDataAppId;
        return;
    }

    xData[xDataAppId].append(QPair<int, QVariant>(code, value));
}

void RDxfImporter::addXDataInt(int code, int value) {
    if (!xData.contains(xDataAppId)) {
        qWarning() << "RDxfImporter::addXDataString: app ID not found: " << xDataAppId;
        return;
    }

    xData[xDataAppId].append(QPair<int, QVariant>(code, value));
}

void RDxfImporter::addDictionary(const DL_DictionaryData& data) {
    if (qcadDictHandle==data.handle.c_str()) {
        inDict = true;
    }
}

void RDxfImporter::addDictionaryEntry(const DL_DictionaryEntryData& data) {
    if (data.name=="QCAD_OBJECTS") {
        qcadDictHandle = data.handle.c_str();
        return;
    }

    if (inDict) {
        qcadDict[data.handle.c_str()] = data.name.c_str();
    }
}

void RDxfImporter::setVariableVector(const std::string& key,
                                     double v1, double v2, double v3, int code) {
    Q_UNUSED(code)

    RS::KnownVariable v = dxfServices.stringToVariable(decode(key.c_str()));
    if (v!=RS::INVALID) {
        setKnownVariable(v, RVector(v1, v2, v3));
    }
}

void RDxfImporter::setVariableString(const std::string& key,
                                     const std::string& value, int code) {
    Q_UNUSED(code)

    RS::KnownVariable v = dxfServices.stringToVariable(key.c_str());
    if (v!=RS::INVALID) {
        setKnownVariable(v, value.c_str());
    }
}

void RDxfImporter::setVariableInt(const std::string& key, int value, int code) {
    Q_UNUSED(code)

    RS::KnownVariable v = dxfServices.stringToVariable(key.c_str());
    if (v!=RS::INVALID) {
        setKnownVariable(v, value);
    }
}

void RDxfImporter::setVariableDouble(const std::string& key, double value, int code) {
    Q_UNUSED(code)

    RS::KnownVariable v = dxfServices.stringToVariable(key.c_str());
    if (v!=RS::INVALID) {
        setKnownVariable(v, value);
    }
}

/**
 * Tries to convert the given DXF encoding string to an encoding recognized by Qt.
 */
QString RDxfImporter::getEncoding(const QString& str) {
    QString l=str.toLower();

    if (l=="latin1" || l=="ansi_1252" || l=="iso-8859-1" ||
            l=="cp819" || l=="csiso" || l=="ibm819" || l=="iso_8859-1" ||
            l=="iso8859-1" || l=="iso-ir-100" || l=="l1") {
        return "Latin1";
    } else if (l=="big5" || l=="ansi_950" || l=="cn-big5" || l=="csbig5" ||
               l=="x-x-big5") {
        return "Big5";
    } else if (l=="big5-hkscs") {
        return "Big5-HKSCS";
    } else if (l=="eucjp" || l=="euc-jp" || l=="cseucpkdfmtjapanese" ||
               l=="x-euc" || l=="x-euc-jp") {
        return "eucJP";
    } else if (l=="euckr") {
        return "eucKR";
    } else if (l=="gb2312" || l=="gb2312" || l=="chinese" || l=="cn-gb" ||
               l=="csgb2312" || l=="csgb231280" || l=="csiso58gb231280" ||
               l=="gb_2312-80" || l=="gb231280" || l=="gb2312-80" || l=="gbk" ||
               l=="iso-ir-58") {
        return "GB2312";
    } else if (l=="gbk") {
        return "GBK";
    } else if (l=="gb18030") {
        return "GB18030";
    } else if (l=="jis7") {
        return "JIS7";
    } else if (l=="shift-jis" || l=="ansi_932" || l=="shift_jis" || l=="csShiftJIS" ||
               l=="cswindows31j" || l=="ms_kanji" || l=="x-ms-cp932" || l=="x-sjis") {
        return "Shift-JIS";
    } else if (l=="tscii") {
        return "TSCII";
    } else if (l=="utf88-bit") {
        return "utf88-bit";
    } else if (l=="utf16") {
        return "utf16";
    } else if (l=="koi8-r") {
        return "KOI8-R";
    } else if (l=="koi8-u") {
        return "KOI8-U";
    } else if (l=="iso8859-1") {
        return "ISO8859-1";
    } else if (l=="iso8859-2") {
        return "ISO8859-2";
    } else if (l=="iso8859-3") {
        return "ISO8859-3";
    } else if (l=="iso8859-4" || l=="ansi_1257") {
        return "ISO8859-4";
    } else if (l=="iso8859-5") {
        return "ISO8859-5";
    } else if (l=="iso8859-6" || l=="ansi_1256") {
        return "ISO8859-6";
    } else if (l=="iso8859-7" || l=="ansi_1253") {
        return "ISO8859-7";
    } else if (l=="iso8859-8") {
        return "ISO8859-8";
    } else if (l=="iso8859-8-i" || l=="ansi_1255") {
        return "ISO8859-8-i";
    } else if (l=="iso8859-9" || l=="ansi_1254") {
        return "ISO8859-9";
    } else if (l=="iso8859-10") {
        return "ISO8859-10";
    } else if (l=="iso8859-13") {
        return "ISO8859-13";
    } else if (l=="iso8859-14") {
        return "ISO8859-14";
    } else if (l=="iso8859-15") {
        return "ISO8859-15";
    } else if (l=="ibm 850") {
        return "IBM 850";
    } else if (l=="ibm 866") {
        return "IBM 866";
    } else if (l=="cp874") {
        return "CP874";
    } else if (l=="cp1250") {
        return "CP1250";
    } else if (l=="cp1251") {
        return "CP1251";
    } else if (l=="cp1252") {
        return "CP1252";
    } else if (l=="cp1253") {
        return "CP1253";
    } else if (l=="cp1254") {
        return "CP1254";
    } else if (l=="cp1255") {
        return "CP1255";
    } else if (l=="cp1256") {
        return "CP1256";
    } else if (l=="cp1257") {
        return "CP1257";
    } else if (l=="cp1258") {
        return "CP1258";
    } else if (l=="apple roman") {
        return "Apple Roman";
    } else if (l=="tis-620") {
        return "TIS-620";
    }

    return "Latin1";
}

QString RDxfImporter::getXDataString(const QString& appId, int code, int pos) {
    if (!xData.contains(appId)) {
        return QString::null;
    }

    int c = 0;
    for (int i=0; i<xData[appId].count(); i++) {
        if (c==pos && xData[appId][i].first==code) {
            return xData[appId][i].second.toString();
        }
    }

    return QString::null;
}

int RDxfImporter::getXDataInt(const QString& appId, int code, int pos) {
    if (!xData.contains(appId)) {
        return 0;
    }

    int c = 0;
    for (int i=0; i<xData[appId].count(); i++) {
        if (c==pos && xData[appId][i].first==code) {
            return xData[appId][i].second.toInt();
        }
    }

    return 0;
}

QString RDxfImporter::decode(const QString& str) {
    return RDxfServices::parseUnicode(str);
}
