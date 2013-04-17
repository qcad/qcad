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

#include "dxflib/src/dl_attributes.h"
#include "dxflib/src/dl_codes.h"
#include "dxflib/src/dl_writer_ascii.h"

#include <QFileInfo>

#include "RDxfExporter.h"
#include "RLinetypePatternMap.h"
#include "RLineEntity.h"
#include "RImageEntity.h"
#include "RPointEntity.h"
#include "RStorage.h"

RDxfExporter::RDxfExporter(RDocument& document,
    RMessageHandler* messageHandler,
    RProgressHandler* progressHandler)
    : RFileExporter(document, messageHandler, progressHandler) {

}

bool RDxfExporter::exportFile(const QString& fileName, const QString& nameFilter, bool setFileName) {
    qDebug() << "RDxfExporter::exportFile";

    // set version for DXF filter:
    DL_Codes::version exportVersion;
    if (nameFilter.contains("R12")) {
        exportVersion = DL_Codes::AC1009;
    } else {
        // TODO: drop support for DXF 2000 (not maintainable):
        exportVersion = DL_Codes::AC1015;
    }

    qDebug() << "RDxfExporter::exportFile: 001";

    dw = dxf.out((const char*)QFile::encodeName(fileName), exportVersion);

    qDebug() << "RDxfExporter::exportFile: 002";

    if (dw==NULL) {
        qWarning() << "RS_FilterDxf::fileExport: cannot open file for writing";
        return false;
    }

    if (setFileName) {
        document->setFileName(fileName);
    }

    // Header
    qDebug() << "RDxfExporter::exportFile: header";
    dxf.writeHeader(*dw);

    // Variables
    qDebug() << "RDxfExporter::exportFile: variables";
    writeVariables();

    // Section TABLES
    qDebug() << "RDxfExporter::exportFile: tables";
    dw->sectionTables();

    // VPORT:
    qDebug() << "RDxfExporter::exportFile: vport";
    dxf.writeVPort(*dw);

    // Line types:
    qDebug() << "RDxfExporter::exportFile: linetypes";
    QStringList lts = document->getLinetypeNames().toList();
    qDebug() << "RDxfExporter::exportFile: linetypes table";
    dw->tableLineTypes(lts.size());
    qDebug() << "RDxfExporter::exportFile: linetypes loop";
    for (int i=0; i<lts.size(); i++) {
        QSharedPointer<RLinetype> lt = document->queryLinetype(lts[i]);
        writeLinetype(*lt);
    }
//    for (int t=(int)RS2::LineByBlock; t<=(int)RS2::BorderLineX2; ++t) {
//        if ((RS2::LineType)t!=RS2::NoPen) {
//            writeLineType((RS2::LineType)t);
//        }
//    }
    qDebug() << "RDxfExporter::exportFile: linetypes table end";
    dw->tableEnd();

    // Layers:
    qDebug() << "RDxfExporter::exportFile: layers";
    QStringList layerNames = document->getLayerNames().toList();
    dw->tableLayers(layerNames.size());
    for (int i=0; i<layerNames.size(); ++i) {
        QSharedPointer<RLayer> layer = document->queryLayer(layerNames[i]);
        if (layer.isNull()) {
            continue;
        }
        writeLayer(*layer);
    }
    dw->tableEnd();

    // STYLE:
    qDebug() << "writing styles...";
    dxf.writeStyle(*dw);

    // VIEW:
    qDebug() << "writing views...";
    dxf.writeView(*dw);

    // UCS:
    qDebug() << "writing ucs...";
    dxf.writeUcs(*dw);

    // Appid:
    qDebug() << "writing appid...";
    dw->tableAppid(1);
    dxf.writeAppid(*dw, "QCAD");
    dw->tableEnd();

    // DIMSTYLE:
    qDebug() << "writing dim styles...";
    dxf.writeDimStyle(*dw,
                      document->getKnownVariable(RS::DIMASZ, 2.5).toDouble(),
                      document->getKnownVariable(RS::DIMEXE, 0.625).toDouble(),
                      document->getKnownVariable(RS::DIMEXO, 0.625).toDouble(),
                      document->getKnownVariable(RS::DIMGAP, 0.625).toDouble(),
                      document->getKnownVariable(RS::DIMTXT, 2.5).toDouble()
    );

    // BLOCK_RECORD:
    QStringList blockNames = document->getBlockNames().toList();
    if (exportVersion!=DL_Codes::AC1009) {
        qDebug() << "writing block records...";
        dxf.writeBlockRecord(*dw);

        for (int i=0; i<blockNames.size(); ++i) {
            QSharedPointer<RBlock> blk = document->queryBlock(blockNames[i]);
            if (blk.isNull()) {
                continue;
            }

            dxf.writeBlockRecord(*dw,
                std::string((const char*)blk->getName().toLatin1()));
        }
        dw->tableEnd();
    }

    // end of tables:
    qDebug() << "writing end of section TABLES...";
    dw->sectionEnd();

    // Section BLOCKS:
    qDebug() << "writing blocks...";
    dw->sectionBlocks();

    /*
    if (exportVersion!=DL_Codes::AC1009) {

        RS_Block b1(graphic, RS_BlockData("*Model_Space",
                                          RS_Vector(0.0,0.0), false));
        writeBlock(&b1);
        RS_Block b2(graphic, RS_BlockData("*Paper_Space",
                                          RS_Vector(0.0,0.0), false));
        writeBlock(&b2);
        RS_Block b3(graphic, RS_BlockData("*Paper_Space0",
                                          RS_Vector(0.0,0.0), false));
        writeBlock(&b3);
    }
    */

    for (int i=0; i<blockNames.size(); ++i) {
        QSharedPointer<RBlock> block = document->queryBlock(blockNames[i]);
        if (block.isNull()) {
            continue;
        }
        writeBlock(*block);
    }
    dw->sectionEnd();

    // Section ENTITIES:
    qDebug() << "writing section ENTITIES...";
    dw->sectionEntities();

    QSet<REntity::Id> ids = document->queryBlockEntities(document->getModelSpaceBlockId());
    QList<REntity::Id> list = document->getStorage().orderBackToFront(ids);

    for (int i=0; i<list.size(); i++) {
        writeEntity(list[i]);
    }
    qDebug() << "writing end of section ENTITIES...";
    dw->sectionEnd();

    if (exportVersion!=DL_Codes::AC1009) {
        qDebug() << "writing section OBJECTS...";
        dxf.writeObjects(*dw);

        // IMAGEDEF's from images in entities and images in blocks
        QStringList written;
//        for (int i=0; i<blockNames.size(); ++i) {
//            RS_Block* block = graphic->blockAt(i);
//            for (RS_Entity* e=block->firstEntity(RS2::ResolveAll);
//                    e!=NULL;
//                    e=block->nextEntity(RS2::ResolveAll)) {

//                if (e->rtti()==RS2::EntityImage) {
//                    RS_Image* img = dynamic_cast<RS_Image*>(e);
//                    if (written.contains(file)==0 && img->getHandle()!=0) {
//                        writeImageDef(img);
//                        written.append(img->getFile());
//                    }
//                }
//            }
//        }

        QSet<REntity::Id> ids = document->queryAllEntities(false, true);
        QList<REntity::Id> list = document->getStorage().orderBackToFront(ids);
        for (int i=0; i<list.size(); i++) {
            QSharedPointer<REntity> e = document->queryEntity(list[i]);
            if (e.isNull()) {
                continue;
            }

            QSharedPointer<RImageEntity> img = e.dynamicCast<RImageEntity>();

            if (img.isNull()) {
                continue;
            }

            QString file = img->getFileName();
            if (written.contains(file)==0 && img->getHandle()!=0) {
                writeImageDef(*img);
                written.append(file);
            }
        }
        qDebug() << "writing end of section OBJECTS...";
        dxf.writeObjectsEnd(*dw);
    }

    qDebug() << "writing EOF...";
    dw->dxfEOF();

    qDebug() << "RDxfExporter::exportFile: close";
    dw->close();

    qDebug() << "RDxfExporter::exportFile: delete";
    delete dw;
    dw = NULL;

    qDebug() << "RDxfExporter::exportFile: OK";

    // check if file was actually written. Windows might not write
    // any output without reporting an error.
    if (QFileInfo(fileName).exists()==false) {
        return false;
    }

    return true;
}

/**
 * Writes all known variable settings to the DXF file.
 */
void RDxfExporter::writeVariables() {
    /*
    RS_Hash<RS_String, RS_Variable>::iterator it;
    (graphic->getVariableDict());
    for (it=graphic->getVariableDict().begin(); it!=graphic->getVariableDict().end(); ++it) {
        // exclude variables that are not known to DXF 12:
        if (!DL_Dxf::checkVariable(it.key().toLatin1(), dxf.getVersion())) {
            continue;
        }

        if (it.key()!="$ACADVER" && it.key()!="$HANDSEED") {

            dw->dxfString(9, (const char*) it.key().toLatin1());
            switch (it.value().getType()) {
            case RS2::VariableVoid:
                break;
            case RS2::VariableInt:
                dw->dxfInt(it.value().getCode(), it.value().getInt());
                break;
            case RS2::VariableDouble:
                dw->dxfReal(it.value().getCode(), it.value().getDouble());
                break;
            case RS2::VariableString:
                dw->dxfString(it.value().getCode(),
                             (const char*) it.value().getString().toLatin1());
                break;
            case RS2::VariableVector:
                dw->dxfReal(it.value().getCode(),
                           it.value().getVector().x);
                dw->dxfReal(it.value().getCode()+10,
                           it.value().getVector().y);
                if (isVariableTwoDimensional(it.key())==false) {
                    dw->dxfReal(it.value().getCode()+20,
                               it.value().getVector().z);
                }
                break;
            }
        }
    }
    RS_Layer* current = graphic->getActiveLayer();
    if (current!=NULL) {
        dw->dxfString(9, "$CLAYER");
        dw->dxfString(8, (const char*)current->getName().toLatin1());
    }
    dw->sectionEnd();
    */
}

void RDxfExporter::writeLinetype(const RLinetype& lt) {
    dxf.writeLineType(
        *dw,
        DL_LineTypeData((const char*)lt.getName().toLatin1(), 0));
}

void RDxfExporter::writeLayer(const RLayer& l) {
    qDebug() << "RS_FilterDxf::writeLayer: " << l.getName();

    int colorSign = 1;
    if (l.isFrozen()) {
        colorSign = -1;
    }

    QSharedPointer<RLinetype> lt = document->queryLinetype(l.getLinetypeId());
    if (lt.isNull()) {
        qDebug() << "Layer " << l.getName() << " has invalid line type ID";
        return;
    }

    dxf.writeLayer(
        *dw,
        DL_LayerData((const char*)l.getName().toLatin1(),
                     l.isFrozen() + (l.isLocked()<<2)),
        DL_Attributes(std::string(""),
                      colorSign * RDxfServices::colorToNumber(l.getColor(), dxfColors),
                      RDxfServices::colorToNumber24(l.getColor()),
                      RDxfServices::widthToNumber(l.getLineweight()),
                      (const char*)lt->getName().toLatin1()));
}

void RDxfExporter::writeBlock(const RBlock& b) {
    QString blockName = b.getName();
    if (dxf.getVersion()==DL_Codes::AC1009) {
        if (blockName.at(0)=='*') {
            blockName[0] = '_';
        }
    }

    dxf.writeBlock( *dw, DL_BlockData((const char*)blockName.toLatin1(), 0,
                                      b.getOrigin().x,
                                      b.getOrigin().y,
                                      b.getOrigin().z));

    QSet<REntity::Id> ids = document->queryBlockEntities(b.getId());
    QList<REntity::Id> list = document->getStorage().orderBackToFront(ids);

    QList<REntity::Id>::iterator it;
    for (it=list.begin(); it!=list.end(); it++) {
        writeEntity(*it);
    }
    dxf.writeEndBlock(*dw, (const char*)b.getName().toLatin1());
}

void RDxfExporter::writeEntity(REntity::Id id) {
    QSharedPointer<REntity> e = document->queryEntity(id);
    if (e.isNull()) {
        return;
    }
    writeEntity(*e);
}

/**
 * Writes the given entity to the DXF file.
 */
void RDxfExporter::writeEntity(REntity& e) {
    if (e.isUndone()) {
        // never reached:
        return;
    }
    qDebug() << "writing entity";

    attributes = getEntityAttributes(e);

    switch (e.getType()) {
    case RS::EntityPoint:
        writePoint(dynamic_cast<RPointEntity&>(e));
        break;
    case RS::EntityLine:
        writeLine(dynamic_cast<RLineEntity&>(e));
        break;
    /*
    case RS::EntityPolyline:
        writePolyline(dynamic_cast<RS_Polyline*>(e));
        break;
    case RS::EntitySpline:
        writeSpline(dynamic_cast<RS_Spline*>(e));
        break;
    case RS::EntityCircle:
        writeCircle(dynamic_cast<RS_Circle*>(e));
        break;
    case RS::EntityArc:
        writeArc(dynamic_cast<RS_Arc*>(e));
        break;
    case RS::EntityEllipse:
        writeEllipse(dynamic_cast<RS_Ellipse*>(e));
        break;
    case RS::EntityBlockRef:
        writeInsert(dynamic_cast<RS_Insert*>(e));
        break;
    case RS::EntityText:
        writeText(dynamic_cast<RS_Text*>(e));
        break;

    case RS::EntityDimAligned:
    case RS::EntityDimAngular:
    case RS::EntityDimLinear:
    case RS::EntityDimRadial:
    case RS::EntityDimDiametric:
    case RS::EntityDimOrdinate:
        writeDimension(dynamic_cast<RS_Dimension*>(e));
        break;
    case RS::EntityDimLeader:
        writeLeader(dynamic_cast<RS_Leader*>(e));
        break;
    case RS::EntityHatch:
        writeHatch(dynamic_cast<RS_Hatch*>(e));
        break;
    case RS::EntityImage:
        writeImage(dynamic_cast<RS_Image*>(e));
        break;
    case RS::EntitySolid:
        writeSolid(dynamic_cast<RS_Solid*>(e));
        break;
    case RS::Entity3dFace:
        write3dFace(dynamic_cast<RS_3dFace*>(e));
        break;

#ifndef RS_NO_COMPLEX_ENTITIES
    case RS::EntityContainer:
        writeEntityContainer(dynamic_cast<RS_EntityContainer*>(e));
        break;
#endif
    */

    default:
        break;
    }
}

/**
 * Writes the given Point entity to the file.
 */
void RDxfExporter::writePoint(const RPointEntity& p) {
    dxf.writePoint(
        *dw,
        DL_PointData(p.getPosition().x,
                     p.getPosition().y,
                     0.0),
        attributes);
}

/**
 * Writes the given Line( entity to the file.
 */
void RDxfExporter::writeLine(const RLineEntity& l) {
    dxf.writeLine(
        *dw,
        DL_LineData(l.getStartPoint().x,
                    l.getStartPoint().y,
                    l.getStartPoint().z,
                    l.getEndPoint().x,
                    l.getEndPoint().y,
                    l.getEndPoint().z),
        attributes);
}

/**
 * \return the entities attributes as a DL_Attributes object.
 */
DL_Attributes RDxfExporter::getEntityAttributes(REntity& entity) {
    // Layer:
    QString layerName = entity.getLayerName();

    // Color:
    int color = RDxfServices::colorToNumber(entity.getColor(), dxfColors);
    int color24 = RDxfServices::colorToNumber24(entity.getColor());

    // Linetype:
    QString lineType = document->getLinetypeName(entity.getLinetypeId());

    // Width:
    int width = RDxfServices::widthToNumber(entity.getLineweight());

    DL_Attributes attrib((const char*)layerName.toLatin1(),
                         color,
                         color24,
                         width,
                         (const char*)lineType.toLatin1());

    return attrib;
}

/**
 * Writes an IMAGEDEF object into an OBJECT section.
 */
void RDxfExporter::writeImageDef(const RImageEntity& img) {
    dxf.writeImageDef(
        *dw,
        img.getHandle(),
        DL_ImageData((const char*)img.getFileName().toLatin1(),
                     img.getInsertionPoint().x,
                     img.getInsertionPoint().y,
                     0.0,
                     img.getUVector().x,
                     img.getUVector().y,
                     0.0,
                     img.getVVector().x,
                     img.getVVector().y,
                     0.0,
                     img.getWidth(),
                     img.getHeight(),
                     img.getBrightness(),
                     img.getContrast(),
                     img.getFade()));
}
