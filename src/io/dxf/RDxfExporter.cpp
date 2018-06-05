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

#include "dxflib/src/dl_attributes.h"
#include "dxflib/src/dl_codes.h"
#include "dxflib/src/dl_writer_ascii.h"

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
    : RFileExporter(document, messageHandler, progressHandler),
    minimalistic(false) {

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

    if (nameFilter.contains("min")) {
        minimalistic = true;
    }

    // set version for DXF filter:
    DL_Codes::version exportVersion;
    if (minimalistic) {
        exportVersion = DL_Codes::AC1009_MIN;
    } else if (nameFilter.contains("R12")) {
        exportVersion = DL_Codes::AC1009;
    } else {
        // TODO: drop support for DXF 2000 (not maintainable):
        exportVersion = DL_Codes::AC1015;
    }


    textStyleCounter = 0;
    imageHandles.clear();
    textStyles.clear();

    dw = dxf.out((const char*)QFile::encodeName(fileName), exportVersion);

    if (dw==NULL) {
        qWarning() << "RDxfExporter::exportFile: cannot open file for writing";
        return false;
    }

    if (setFileName) {
        document->setFileName(fileName);
        document->setFileVersion(nameFilter);
    }

    if (!minimalistic) {
        // Header
        //qDebug() << "RDxfExporter::exportFile: header";
        dxf.writeHeader(*dw);

        // Variables
        //qDebug() << "RDxfExporter::exportFile: variables";
        writeVariables();

        // end header
        dw->sectionEnd();
    }

    // Section TABLES
    //qDebug() << "RDxfExporter::exportFile: tables";
    dw->sectionTables();

    // VPORT:
    if (!minimalistic) {
        //qDebug() << "RDxfExporter::exportFile: vport";
        dxf.writeVPort(*dw);
    }

    // Line types:
    //qDebug() << "RDxfExporter::exportFile: linetypes";
    if (minimalistic) {
        QSharedPointer<RLinetype> lt = document->queryLinetype("CONTINUOUS");
        if (!lt.isNull()) {
            dw->tableLinetypes(1);
            writeLinetype(lt->getPattern());
        }
    }
    else {
        QStringList lts = document->getLinetypeNames().toList();
        //qDebug() << "RDxfExporter::exportFile: linetypes table";
        dw->tableLinetypes(lts.size());
        // continuous must always be the first LTYPE:
        QSharedPointer<RLinetype> lt = document->queryLinetype("CONTINUOUS");
        if (!lt.isNull()) {
            writeLinetype(lt->getPattern());
        }
        //qDebug() << "RDxfExporter::exportFile: linetypes loop";
        for (int i=0; i<lts.size(); i++) {
            if (lts[i].toUpper()=="CONTINUOUS") {
                continue;
            }
            QSharedPointer<RLinetype> lt = document->queryLinetype(lts[i]);
            if (!lt.isNull()) {
                writeLinetype(lt->getPattern());
            }
        }
    }
    //qDebug() << "RDxfExporter::exportFile: linetypes table end";
    dw->tableEnd();

    // Layers:
    //qDebug() << "RDxfExporter::exportFile: layers";
    QStringList layerNames;
    if (minimalistic) {
        layerNames.append("0");
    }
    else {
        layerNames = document->getLayerNames().toList();
    }
    dw->tableLayers(layerNames.size());
    for (int i=0; i<layerNames.size(); ++i) {
        QSharedPointer<RLayer> layer = document->queryLayer(layerNames[i]);
        if (layer.isNull()) {
            continue;
        }
        writeLayer(*layer);
    }
    dw->tableEnd();

    if (!minimalistic) {
        // STYLE:
        //qDebug() << "writing styles...";
        QList<DL_StyleData> uniqueTextStyles;

        QString dimFont;
        //dimFont = document->getDimensionFont();
        //if (dimFont.toLower()=="standard") {
            dimFont = "txt";
        //}

        // add text style for dimensions:
        DL_StyleData style("Standard",
                           0,    // flags
                           0.0,  // fixed height (not fixed)
                           1.0,  // width factor
                           0.0,  // oblique angle
                           0,    // text generation flags
                           2.5,  // last height used
                           (const char*)dimFont.toLocal8Bit(), //"txt", // primary font file
                           ""    // big font file
                           );
        style.bold = false;
        style.italic = false;
        uniqueTextStyles.append(style);

        // write one text style for each new, unique combination of font, size, etc:
        QList<REntity::Id> entityIds = document->queryAllEntities(false, true).toList();
        for (int i=0; i<entityIds.size(); i++) {
            REntity::Id id = entityIds[i];
            QSharedPointer<REntity> entity = document->queryEntityDirect(id);
            QSharedPointer<RTextBasedEntity> textEntity = entity.dynamicCast<RTextBasedEntity>();
            if (textEntity.isNull()) {
                continue;
            }

            // getStyle assignes a new, unique name for the style:
            DL_StyleData style = getStyle(*textEntity);
            style.bold = textEntity->isBold();
            style.italic = textEntity->isItalic();
            if (uniqueTextStyles.contains(style)) {
                textStyleCounter--;
                continue;
            }

            textStyles.insert(id, style.name.c_str());

            uniqueTextStyles.append(style);
        }

        dw->tableStyle(uniqueTextStyles.size());
        for (int i=0; i<uniqueTextStyles.size(); i++) {
            DL_StyleData style = uniqueTextStyles[i];
            dxf.writeStyle(*dw, style);
        }
        dw->tableEnd();
    }

    // VIEW:
    if (!minimalistic) {
        //qDebug() << "writing views...";
        dxf.writeView(*dw);
    }

    // UCS:
    if (!minimalistic) {
        //qDebug() << "writing ucs...";
        dxf.writeUcs(*dw);
    }

    // Appid:
    if (!minimalistic) {
        //qDebug() << "writing appid...";
        dw->tableAppid(1);
        dxf.writeAppid(*dw, "ACAD");
        dxf.writeAppid(*dw, "QCAD");
        dw->tableEnd();
    }

    // DIMSTYLE:
    if (!minimalistic) {
        //qDebug() << "writing dim styles...";
        dxf.writeDimStyle(*dw,
                          document->getKnownVariable(RS::DIMASZ, 2.5).toDouble(),
                          document->getKnownVariable(RS::DIMEXE, 0.625).toDouble(),
                          document->getKnownVariable(RS::DIMEXO, 0.625).toDouble(),
                          document->getKnownVariable(RS::DIMGAP, 0.625).toDouble(),
                          document->getKnownVariable(RS::DIMTXT, 2.5).toDouble()
        );
    }

    // BLOCK_RECORD:
    QStringList blockNames = document->getBlockNames().toList();
    if (exportVersion!=DL_Codes::AC1009 && exportVersion!=DL_Codes::AC1009_MIN) {
        //qDebug() << "writing block records...";
        dxf.writeBlockRecord(*dw);

        for (int i=0; i<blockNames.size(); ++i) {
            //qDebug() << "writing block record: " << blockNames[i];
            if (blockNames[i].startsWith("*")) {
                continue;
            }

            QSharedPointer<RBlock> blk = document->queryBlock(blockNames[i]);
            if (blk.isNull()) {
                continue;
            }

            dxf.writeBlockRecord(*dw,
                                 std::string((const char*)RDxfExporter::escapeUnicode(blk->getName()))
                                 );
        }
        dw->tableEnd();
    }

    // end of tables:
    //qDebug() << "writing end of section TABLES...";
    dw->sectionEnd();

    // Section BLOCKS:
    //qDebug() << "writing blocks...";
    dw->sectionBlocks();

    if (exportVersion!=DL_Codes::AC1009 && exportVersion!=DL_Codes::AC1009_MIN) {
        RBlock b1(document, "*Model_Space", RVector(0.0,0.0));
        writeBlock(b1);
        RBlock b2(document, "*Paper_Space", RVector(0.0,0.0));
        writeBlock(b2);
        RBlock b3(document, "*Paper_Space0", RVector(0.0,0.0));
        writeBlock(b3);
    }

    //if (!minimalistic) {
        for (int i=0; i<blockNames.size(); ++i) {
            //qDebug() << "writing block: " << blockNames[i];
            if (blockNames[i].startsWith("*") && !blockNames[i].startsWith("*X")) {
                continue;
            }
            QSharedPointer<RBlock> block = document->queryBlock(blockNames[i]);
            if (block.isNull()) {
                continue;
            }
            writeBlock(*block);
        }
    //}

    dw->sectionEnd();

    // Section ENTITIES:
    //qDebug() << "writing section ENTITIES...";
    dw->sectionEntities();

    QSet<REntity::Id> blockEntityIds = document->queryBlockEntities(document->getModelSpaceBlockId());
    //qDebug() << "writing model space entities with IDs: " << blockEntityIds;
    QList<REntity::Id> list = document->getStorage().orderBackToFront(blockEntityIds);
    //qDebug() << "writing ordered entities with IDs: " << list;

    for (int i=0; i<list.size(); i++) {
        writeEntity(list[i]);
    }
    //qDebug() << "writing end of section ENTITIES...";
    dw->sectionEnd();

    if (exportVersion!=DL_Codes::AC1009 && exportVersion!=DL_Codes::AC1009_MIN) {
        //qDebug() << "writing section OBJECTS...";
        dxf.writeObjects(*dw, "QCAD_OBJECTS");

        if (!minimalistic) {
            // XRecords:
            dxf.writeAppDictionary(*dw);
            QMap<QString, int> handles;

            // export all QCAD specific document variables:
            QStringList variables = document->getVariables();
            document->setVariable("QCADVersion", RSettings::getVersionString());
            variables.sort();
            for (int i=0; i<variables.size(); i++) {
                QString key = variables[i];
                handles.insert(key, dxf.writeDictionaryEntry(*dw, std::string((const char*)RDxfExporter::escapeUnicode(key))));
            }
            for (int i=0; i<variables.size(); i++) {
                QString key = variables[i];
                QVariant value = document->getVariable(key);
                if (handles.contains(key)) {
                    switch (value.type()) {
                    case QVariant::Int:
                        dxf.writeXRecord(*dw, handles.value(key), value.toInt());
                        break;
                    case QVariant::Double:
                        dxf.writeXRecord(*dw, handles.value(key), value.toDouble());
                        break;
                    case QVariant::Bool:
                        dxf.writeXRecord(*dw, handles.value(key), value.toBool());
                        break;
                    case QVariant::String:
                        dxf.writeXRecord(*dw, handles.value(key), std::string((const char*)RDxfExporter::escapeUnicode(value.toString())));
                        break;
                    case QVariant::Font:
                        if (value.canConvert<QFont>()) {
                            QFont f = value.value<QFont>();
                            dxf.writeXRecord(*dw, handles.value(key), std::string((const char*)RDxfExporter::escapeUnicode(f.toString())));
                        }
                        break;
                    case QVariant::UserType:
                        if (value.canConvert<RColor>()) {
                            RColor c = value.value<RColor>();
                            dxf.writeXRecord(*dw, handles.value(key), std::string((const char*)RDxfExporter::escapeUnicode(c.getName())));
                        }
                        break;
                    default:
                        qWarning() << "RDxfExporter::exportFile: unsupported extension data type: " << value.type();
                        Q_ASSERT(false);
                        break;
                    }
                }
            }
        }


        // IMAGEDEF's from images in entities and images in blocks
        QStringList written;
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
            if (/*written.contains(file)==0 &&*/ img->getHandle()!=0) {
                writeImageDef(*img);
                written.append(file);
            }
        }
        //qDebug() << "writing end of section OBJECTS...";
        dxf.writeObjectsEnd(*dw);
    }

    //qDebug() << "writing EOF...";
    dw->dxfEOF();

    //qDebug() << "RDxfExporter::exportFile: close";
    dw->close();

    //qDebug() << "RDxfExporter::exportFile: delete";
    delete dw;
    dw = NULL;

    //qDebug() << "RDxfExporter::exportFile: OK";

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
    for (RS::KnownVariable var=RS::ANGBASE; var<RS::MaxKnownVariable; var=(RS::KnownVariable)((int)var+1)) {
        QString name = RDxfServices::variableToString(var);

        // skip unsupported variables:
        if (!DL_Dxf::checkVariable(name.toUtf8(), dxf.getVersion())) {
            continue;
        }

        // skip undefined variables:
        QVariant value = document->getKnownVariable(var);
        if (!value.isValid()) {
            continue;
        }

        int code = RDxfServices::getCodeForVariable(var);
        if (code==-1) {
            continue;
        }

        if (name=="ACADVER" || name=="HANDSEED") {
            continue;
        }

        name = "$" + name;

        switch (value.type()) {
        case QVariant::Int:
            dw->dxfString(9, (const char*)RDxfExporter::escapeUnicode(name));
            dw->dxfInt(code, value.toInt());
            break;
        case QVariant::Double:
            dw->dxfString(9, (const char*)RDxfExporter::escapeUnicode(name));
            dw->dxfReal(code, value.toDouble());
            break;
        case QVariant::String:
            dw->dxfString(9, (const char*)RDxfExporter::escapeUnicode(name));
            dw->dxfString(code, (const char*)RDxfExporter::escapeUnicode(value.toString()));
            break;
        case QVariant::UserType:
            if (value.canConvert<RVector>()) {
                RVector v = value.value<RVector>();
                dw->dxfString(9, (const char*)RDxfExporter::escapeUnicode(name));
                dw->dxfReal(code, v.x);
                dw->dxfReal(code+10, v.y);
                if (RDxfServices::isVariable2D(var)==false) {
                    dw->dxfReal(code+20, v.z);
                }
            }
            break;
        default:
            break;
        }
    }
    /*
    RS_Hash<RS_String, RS_Variable>::iterator it;
    (graphic->getVariableDict());
    for (it=graphic->getVariableDict().begin(); it!=graphic->getVariableDict().end(); ++it) {
        // exclude variables that are not known to DXF 12:
        if (!DL_Dxf::checkVariable(it.key().toUtf8(), dxf.getVersion())) {
            continue;
        }

        if (it.key()!="$ACADVER" && it.key()!="$HANDSEED") {

            dw->dxfString(9, (const char*)RDxfExporter::escapeUnicode( it.key()));
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
                             (const char*)RDxfExporter::escapeUnicode( it.value().getString()));
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
        dw->dxfString(8, (const char*)RDxfExporter::escapeUnicode(current->getName()));
    }
    dw->sectionEnd();
    */
}

void RDxfExporter::writeLinetype(const RLinetypePattern& lt) {
    int numDashes = lt.getNumDashes();
    double* dashes = new double[numDashes];
    for (int i=0; i<numDashes; i++) {
        dashes[i] = lt.getDashLengthAt(i);
    }

    dxf.writeLinetype(
        *dw,
        DL_LinetypeData(
            (const char*)RDxfExporter::escapeUnicode(lt.getName()),
            (const char*)RDxfExporter::escapeUnicode(lt.getDescription()),
            0,
            numDashes,
            lt.getPatternLength(),
            dashes
        )
    );

    delete[] dashes;
}

void RDxfExporter::writeLayer(const RLayer& l) {
    qDebug() << "RDxfExporter::writeLayer: " << l.getName();

    int colorSign = 1;
    if (l.isOff()) {
        colorSign = -1;
    }

    QSharedPointer<RLinetype> lt = document->queryLinetype(l.getLinetypeId());
    if (lt.isNull()) {
        qDebug() << "Layer " << l.getName() << " has invalid line type ID";
        return;
    }

    dxf.writeLayer(
        *dw,
        DL_LayerData((const char*)RDxfExporter::escapeUnicode(l.getName()),
                     l.isFrozen() + (l.isLocked()<<2), l.isOff()),
        DL_Attributes(std::string(""),
                      colorSign * RDxfServices::colorToNumber(l.getColor(), dxfColors),
                      RDxfServices::colorToNumber24(l.getColor()),
                      RDxfServices::widthToNumber(l.getLineweight()),
                      (const char*)RDxfExporter::escapeUnicode(lt->getName())));
}

void RDxfExporter::writeBlock(const RBlock& b) {
    QString blockName = b.getName();


    if (dxf.getVersion()==DL_Codes::AC1009 || dxf.getVersion()==DL_Codes::AC1009_MIN) {
        if (blockName.at(0)=='*') {
            blockName[0] = '_';
        }
    }

    dxf.writeBlock(*dw, DL_BlockData((const char*)RDxfExporter::escapeUnicode(blockName), 0,
                                      b.getOrigin().x,
                                      b.getOrigin().y,
                                      b.getOrigin().z));

    // entities in model space are stored in section ENTITIES, not in block:
    if (blockName.toLower()==RBlock::modelSpaceName.toLower()) {
        dxf.writeEndBlock(*dw, (const char*)RDxfExporter::escapeUnicode(b.getName()));
        return;
    }

    QSet<REntity::Id> ids = document->queryBlockEntities(b.getId());
    QList<REntity::Id> list = document->getStorage().orderBackToFront(ids);

    QList<REntity::Id>::iterator it;
    for (it=list.begin(); it!=list.end(); it++) {
        writeEntity(*it);
    }
    dxf.writeEndBlock(*dw, (const char*)RDxfExporter::escapeUnicode(b.getName()));
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
void RDxfExporter::writeEntity(const REntity& e) {
    if (e.isUndone()) {
        qDebug() << "RDxfExporter::writeEntity: entity undone...";
        // never reached:
        return;
    }

    //qDebug() << "RDxfExporter::writeEntity: " << e;

    attributes = getEntityAttributes(e);

    switch (e.getType()) {
    case RS::EntityPoint:
        writePoint(dynamic_cast<const RPointEntity&>(e));
        break;
    case RS::EntityLine:
        writeLine(dynamic_cast<const RLineEntity&>(e));
        break;
    case RS::EntityXLine:
        writeXLine(dynamic_cast<const RXLineEntity&>(e));
        break;
    case RS::EntityRay:
        writeRay(dynamic_cast<const RRayEntity&>(e));
        break;
    case RS::EntityPolyline:
        writePolyline(dynamic_cast<const RPolylineEntity&>(e));
        break;
    case RS::EntitySpline:
        writeSpline(dynamic_cast<const RSplineEntity&>(e));
        break;
    case RS::EntityCircle:
        writeCircle(dynamic_cast<const RCircleEntity&>(e));
        break;
    case RS::EntityArc:
        writeArc(dynamic_cast<const RArcEntity&>(e));
        break;
    case RS::EntityEllipse:
        writeEllipse(dynamic_cast<const REllipseEntity&>(e));
        break;
    case RS::EntityBlockRef:
        writeBlockReference(dynamic_cast<const RBlockReferenceEntity&>(e));
        break;
    case RS::EntityText:
        writeText(dynamic_cast<const RTextEntity&>(e));
        break;
    case RS::EntityAttribute:
        writeAttribute(dynamic_cast<const RAttributeEntity&>(e));
        break;

    case RS::EntityDimAligned:
    case RS::EntityDimAngular2L:
    case RS::EntityDimAngular3P:
    case RS::EntityDimRotated:
    case RS::EntityDimRadial:
    case RS::EntityDimDiametric:
    case RS::EntityDimOrdinate:
        writeDimension(dynamic_cast<const RDimensionEntity&>(e));
        break;

    case RS::EntityLeader:
        writeLeader(dynamic_cast<const RLeaderEntity&>(e));
        break;
    case RS::EntityHatch:
        writeHatch(dynamic_cast<const RHatchEntity&>(e));
        break;
    case RS::EntityImage:
        writeImage(dynamic_cast<const RImageEntity&>(e));
        break;
    case RS::EntitySolid:
        writeSolid(dynamic_cast<const RSolidEntity&>(e));
        break;
        /*
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
 * Writes the given Line entity to the file.
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
 * Writes the given XLine entity to the file.
 */
void RDxfExporter::writeXLine(const RXLineEntity& l) {
    dxf.writeXLine(
                *dw,
                DL_XLineData(l.getBasePoint().x,
                             l.getBasePoint().y,
                             l.getBasePoint().z,
                             l.getSecondPoint().x - l.getBasePoint().x,
                             l.getSecondPoint().y - l.getBasePoint().y,
                             l.getSecondPoint().z - l.getBasePoint().z),
                attributes);
}

/**
 * Writes the given Ray entity to the file.
 */
void RDxfExporter::writeRay(const RRayEntity& l) {
    dxf.writeRay(
                *dw,
                DL_RayData(l.getBasePoint().x,
                           l.getBasePoint().y,
                           l.getBasePoint().z,
                           l.getSecondPoint().x - l.getBasePoint().x,
                           l.getSecondPoint().y - l.getBasePoint().y,
                           l.getSecondPoint().z - l.getBasePoint().z),
                attributes);
}

/**
 * Writes the given circle entity to the file.
 */
void RDxfExporter::writeCircle(const RCircleEntity& c) {
    dxf.writeCircle(
        *dw,
        DL_CircleData(c.getCenter().x,
                      c.getCenter().y,
                      0.0,
                      c.getRadius()),
        attributes);
}

/**
 * Writes the given circle entity to the file.
 */
void RDxfExporter::writeArc(const RArcEntity& a) {
    double a1, a2;
    if (a.isReversed()) {
        a1 = RMath::rad2deg(a.getEndAngle());
        a2 = RMath::rad2deg(a.getStartAngle());
    } else {
        a1 = RMath::rad2deg(a.getStartAngle());
        a2 = RMath::rad2deg(a.getEndAngle());
    }
    dxf.writeArc(
        *dw,
        DL_ArcData(a.getCenter().x,
                   a.getCenter().y,
                   0.0,
                   a.getRadius(),
                   a1, a2),
        attributes);
}

/**
 * Writes the given ellipse entity to the file.
 */
void RDxfExporter::writeEllipse(const REllipseEntity& el) {
    double startParam = 0.0;
    double endParam = 0.0;

    if (el.isFullEllipse()) {
        startParam = 0.0;
        endParam = 2.0*M_PI;
    }
    else {
        if (el.isReversed()) {
            startParam = el.getEndParam();
            endParam = el.getStartParam();
        } else {
            startParam = el.getStartParam();
            endParam = el.getEndParam();
        }
    }

    dxf.writeEllipse(
        *dw,
        DL_EllipseData(el.getCenter().x,
                       el.getCenter().y,
                       0.0,
                       el.getMajorPoint().x,
                       el.getMajorPoint().y,
                       0.0,
                       el.getRatio(),
                       startParam,
                       endParam),
        attributes);
}

/**
 * Writes the given polyline entity to the file.
 */
void RDxfExporter::writePolyline(const RPolylineEntity& pl) {
    writePolyline(pl.getPolylineShape(), pl.getPolylineGen());
}

void RDxfExporter::writePolyline(const RPolyline& pl, bool plineGen) {
    int count = pl.countVertices();

    dxf.writePolyline(
                *dw,
                DL_PolylineData(count,
                                0, 0,
                                pl.isClosed()*0x1 + plineGen*0x80),
                attributes
                );

    for (int i=0; i<pl.countVertices(); i++) {
        RVector v = pl.getVertexAt(i);
        double bulge = pl.getBulgeAt(i);

        dxf.writeVertex(*dw, DL_VertexData(v.x, v.y, 0.0, bulge));
    }

    dxf.writePolylineEnd(*dw);
}

/**
 * Writes the given spline entity to the file.
 */
void RDxfExporter::writeSpline(const RSplineEntity& sp) {

    // write spline as polyline for DXF R12:
    if (dxf.getVersion()==DL_Codes::AC1009 || dxf.getVersion()==DL_Codes::AC1009_MIN) {
        int seg = RSettings::getIntValue("Explode/SplineSegments", 64);
        writePolyline(sp.getData().toPolyline(seg), false);
        return;
    }

    if (sp.countControlPoints() < sp.getDegree()+1) {
        qWarning() << "RDxfExporter::writeSpline: "
                   << "Discarding spline: not enough control points given.";
        return;
    }

    // number of control points:
    QList<RVector> cp = sp.getControlPointsWrapped();
    int numCtrlPoints = cp.count();

    // number of fit points:
    QList<RVector> fp = sp.getFitPoints();
    if (sp.isPeriodic() && !fp.isEmpty()) {
        fp.append(fp.first());
    }
    int numFitPoints = fp.count();

    // number of knots (= number of control points + spline degree + 1)
    QList<double> knotVector = sp.getActualKnotVector();

    // first and last knots are duplicated in DXF:
    if (!knotVector.isEmpty()) {
        knotVector.prepend(knotVector.first());
        knotVector.append(knotVector.last());
    }
    //int numKnots = numCtrlPoints + sp.getDegree() + 1;
    int numKnots = knotVector.count();

    int flags;
    if (sp.isClosed()) {
        flags = 11;
    } else {
        flags = 8;
    }

    // write spline header:
    dxf.writeSpline(
        *dw,
        DL_SplineData(sp.getDegree(), numKnots, numCtrlPoints, numFitPoints, flags),
        attributes
    );

    // write spline knots:
    DL_KnotData kd;
    for (int i=0; i<numKnots; i++) {
        kd = DL_KnotData(knotVector[i]);
        dxf.writeKnot(*dw, kd);
    }

    // write spline control points:
    for (int i=0; i<numCtrlPoints; i++) {
        dxf.writeControlPoint(
                    *dw,
                    DL_ControlPointData(cp[i].x, cp[i].y, 0.0, 1.0)
                    );
    }

    // write spline fit points (if any):
    for (int i=0; i<numFitPoints; i++) {
        dxf.writeFitPoint(*dw, DL_FitPointData(fp[i].x, fp[i].y, 0.0));
    }
}

DL_TextData RDxfExporter::getTextData(const RTextBasedData& t, const QString& styleName) {

    DL_TextData data(
                t.getPosition().x,
                t.getPosition().y,
                0.0,
                t.getAlignmentPoint().x,
                t.getAlignmentPoint().y,
                0.0,
                t.getTextHeight(),
                1.0,  // x scale factor
                0,    // text gen flags
                0,    // h just
                0,    // v just
                (const char*)RDxfExporter::escapeUnicode(t.getEscapedText(true)),
                (const char*)RDxfExporter::escapeUnicode(styleName),
                t.getAngle());

    if (t.getHAlign()==RS::HAlignAlign && t.getVAlign()==RS::VAlignBottom) {
        data.vJustification = 0;
        data.hJustification = 0;
    }
    else {
        switch (t.getHAlign()) {
        default:
        case RS::HAlignLeft:
            data.hJustification = 0;
            break;
        case RS::HAlignCenter:
            data.hJustification = 1;
            break;
        case RS::HAlignRight:
            data.hJustification = 2;
            break;
        }
        switch (t.getVAlign()) {
        default:
        case RS::VAlignBase:
            data.vJustification = 0;
            break;
        case RS::VAlignBottom:
            data.vJustification = 1;
            break;
        case RS::VAlignMiddle:
            data.vJustification = 2;
            break;
        case RS::VAlignTop:
            data.vJustification = 3;
            break;
        }
    }

    return data;
}

QString RDxfExporter::getStyleName(const RTextBasedEntity& t) {
    REntity::Id id = t.getId();
    if (!textStyles.contains(id)) {
        qWarning() << "RDxfExporter::getStyleName: "
            << "no style for entity with ID: " << id;
        qDebug() << "Styles:";
        qDebug() << textStyles;
        return QString();
    }
    return textStyles.value(t.getId());
}

/**
 * Writes the given text entity to the file.
 */
void RDxfExporter::writeText(const RTextEntity& t) {
    if (t.isSimple()) {
        writeSimpleText(t);
    }
    else {
        writeMText(t);
    }
}

void RDxfExporter::writeAttribute(const RAttributeEntity& t) {
    DL_TextData tData = getTextData(t.getData(), getStyleName(t));
    DL_AttributeData data(tData, (const char*)RDxfExporter::escapeUnicode(t.getTag()));
    dxf.writeAttribute(*dw, data, attributes);
}

void RDxfExporter::writeSimpleText(const RTextEntity& t) {
    DL_TextData data = getTextData(t.getData(), getStyleName(t));
    dxf.writeText(*dw, data, attributes);
}

void RDxfExporter::writeMText(const RTextEntity& t) {
//    REntity::Id id = t.getId();
//    if (!textStyles.contains(id)) {
//        qWarning() << "RDxfExporter::writeMText: "
//            << "no style for entity with ID: " << id;
//        return;
//    }
//    QString styleName = textStyles.value(t.getId());
    QString styleName = getStyleName(t);

    int attachmentPoint=1;
    switch (t.getHAlign()) {
    default:
    case RS::HAlignLeft:
        attachmentPoint=1;
        break;
    case RS::HAlignCenter:
        attachmentPoint=2;
        break;
    case RS::HAlignRight:
        attachmentPoint=3;
        break;
    }

    switch (t.getVAlign()) {
    default:
    case RS::VAlignTop:
        attachmentPoint+=0;
        break;
    case RS::VAlignMiddle:
        attachmentPoint+=3;
        break;
    case RS::VAlignBottom:
    case RS::VAlignBase:
        attachmentPoint+=6;
        break;
    }

    int drawingDirection = 1;
    switch (t.getDrawingDirection()) {
    default:
    case RS::LeftToRight:
        drawingDirection = 1;
        break;
    case RS::TopToBottom:
        drawingDirection = 3;
        break;
    case RS::ByStyle:
        drawingDirection = 5;
        break;
    }

    int lineSpacingStyle = 2;
    switch (t.getLineSpacingStyle()) {
    case RS::AtLeast:
        lineSpacingStyle = 1;
        break;
    default:
    case RS::Exact:
        lineSpacingStyle = 2;
        break;
    }

    dxf.writeMText(
                *dw,
                DL_MTextData(//t.getPosition().x,
                             //t.getPosition().y,
                             t.getAlignmentPoint().x,
                             t.getAlignmentPoint().y,
                             0.0,
                             //t.getAlignmentPoint().x,
                             //t.getAlignmentPoint().y,
                             0.0,
                             0.0,
                             0.0,
                             t.getTextHeight(),
                             t.getTextWidth(),
                             attachmentPoint,
                             drawingDirection,
                             lineSpacingStyle,
                             t.getLineSpacingFactor(),
                             (const char*)RDxfExporter::escapeUnicode(t.getEscapedText(true)),
                             (const char*)RDxfExporter::escapeUnicode(styleName),
                             t.getAngle()),
                attributes);
}

/**
 * Writes the given dimension entity to the file.
 */
void RDxfExporter::writeDimension(const RDimensionEntity& d) {
    // split dimension into simple entities:
    if (dxf.getVersion()==DL_Codes::AC1009 || dxf.getVersion()==DL_Codes::AC1009_MIN) {
        // TODO:
        //writeAtomicEntities(d, RS2::ResolveNone);
        return;
    }

    int dimType;
    int attachmentPoint=1;
//    if (d.getHAlign()==RS2::HAlignLeft) {
//        attachmentPoint=1;
//    } else if (d.getHAlign()==RS2::HAlignCenter) {
        attachmentPoint=2;
//    } else if (d.getHAlign()==RS2::HAlignRight) {
//        attachmentPoint=3;
//    }
//    if (d.getVAlign()==RS2::VAlignTop) {
//        attachmentPoint+=0;
//    } else if (d.getVAlign()==RS2::VAlignMiddle) {
//        attachmentPoint+=3;
//    } else if (d.getVAlign()==RS2::VAlignBottom) {
        attachmentPoint+=6;
//    }

    switch (d.getType()) {
    case RS::EntityDimAligned:
        dimType = 1;
        break;
    case RS::EntityDimAngular2L:
        dimType = 2;
        break;
    case RS::EntityDimAngular3P:
        dimType = 5;
        break;
    case RS::EntityDimRotated:
        dimType = 0;
        break;
    case RS::EntityDimRadial:
        dimType = 4;
        break;
    case RS::EntityDimDiametric:
        dimType = 3;
        break;
    case RS::EntityDimOrdinate:
        dimType = 6;
        break;
    default:
        dimType = 0;
        break;
    }

    if (d.hasCustomTextPosition()) {
        dimType |= 0x80;
    }

    QString text = d.getMeasurement(false);
    text.replace("^", "^ ");

    //qDebug() << "dimType: " << dimType;
    //qDebug() << "text: " << d.getMeasurement(false);

    DL_DimensionData dimData(d.getDefinitionPoint().x,
                             d.getDefinitionPoint().y,
                             0.0,
                             d.getTextPosition().x,
                             d.getTextPosition().y,
                             0.0,
                             dimType,
                             attachmentPoint,
                             d.getLineSpacingStyle(),
                             d.getLineSpacingFactor(),
                             (const char*)RDxfExporter::escapeUnicode(text),
                             // TODO: dim style:
                             (const char*)RDxfExporter::escapeUnicode(d.getFontName()),
                             d.getTextAngle(),
                             d.getLinearFactor(),
                             d.getDimScale());
    dimData.arrow1Flipped = d.isArrow1Flipped();
    dimData.arrow2Flipped = d.isArrow2Flipped();

    switch (d.getType()) {
    case RS::EntityDimAligned: {
        const RDimAlignedEntity* dim = dynamic_cast<const RDimAlignedEntity*>(&d);

        DL_DimAlignedData dimAlignedData(dim->getExtensionPoint1().x,
                                         dim->getExtensionPoint1().y,
                                         0.0,
                                         dim->getExtensionPoint2().x,
                                         dim->getExtensionPoint2().y,
                                         0.0);

        dxf.writeDimAligned(*dw, dimData, dimAlignedData, attributes);
        }
        break;
    case RS::EntityDimRotated: {
        const RDimRotatedEntity* dim = dynamic_cast<const RDimRotatedEntity*>(&d);

        DL_DimLinearData dimLinearData(dim->getExtensionPoint1().x,
                                       dim->getExtensionPoint1().y,
                                       0.0,
                                       dim->getExtensionPoint2().x,
                                       dim->getExtensionPoint2().y,
                                       0.0,
                                       dim->getRotation(),
                                       0.0 // TODO: dl->getOblique()
                                       );

        dxf.writeDimLinear(*dw, dimData, dimLinearData, attributes);
        }
        break;
    case RS::EntityDimRadial: {
        const RDimRadialEntity* dim = dynamic_cast<const RDimRadialEntity*>(&d);

        DL_DimRadialData dimRadialData(dim->getChordPoint().x,
                                       dim->getChordPoint().y,
                                       0.0,
                                       0.0 // TODO: dr->getLeader()
                                       );

        dxf.writeDimRadial(*dw, dimData, dimRadialData, attributes);
        }
        break;
    case RS::EntityDimDiametric: {
        const RDimDiametricEntity* dim = dynamic_cast<const RDimDiametricEntity*>(&d);

        DL_DimDiametricData dimDiametricData(dim->getChordPoint().x,
                                             dim->getChordPoint().y,
                                             0.0,
                                             0.0 // TODO: dr->getLeader()
                                             );

        dxf.writeDimDiametric(*dw, dimData, dimDiametricData, attributes);
        }
        break;
    case RS::EntityDimAngular2L: {
        const RDimAngular2LEntity* dim = dynamic_cast<const RDimAngular2LEntity*>(&d);

        DL_DimAngular2LData dimAngular2LData(dim->getExtensionLine1Start().x,
                                         dim->getExtensionLine1Start().y,
                                         0.0,
                                         dim->getExtensionLine1End().x,
                                         dim->getExtensionLine1End().y,
                                         0.0,
                                         dim->getExtensionLine2Start().x,
                                         dim->getExtensionLine2Start().y,
                                         0.0,
                                         dim->getDimArcPosition().x,
                                         dim->getDimArcPosition().y,
                                         0.0);

        dxf.writeDimAngular2L(*dw, dimData, dimAngular2LData, attributes);
        }
        break;
    case RS::EntityDimAngular3P: {
        const RDimAngular3PEntity* dim = dynamic_cast<const RDimAngular3PEntity*>(&d);

        DL_DimAngular3PData dimAngular3PData(dim->getExtensionLine1End().x,
                                         dim->getExtensionLine1End().y,
                                         0.0,
                                         dim->getExtensionLine2End().x,
                                         dim->getExtensionLine2End().y,
                                         0.0,
                                         dim->getCenter().x,
                                         dim->getCenter().y,
                                         0.0);

        dxf.writeDimAngular3P(*dw, dimData, dimAngular3PData, attributes);
        }
        break;
    case RS::EntityDimOrdinate: {
        const RDimOrdinateEntity* dim = dynamic_cast<const RDimOrdinateEntity*>(&d);

        DL_DimOrdinateData dimOrdinateData(dim->getDefiningPoint().x,
                                           dim->getDefiningPoint().y,
                                           0.0,
                                           dim->getLeaderEndPoint().x,
                                           dim->getLeaderEndPoint().y,
                                           0.0,
                                           dim->isMeasuringXAxis());

        dxf.writeDimOrdinate(*dw, dimData, dimOrdinateData, attributes);
        }
        break;
    default:
        break;
    }
}

/**
 * Writes the given leader entity to the file.
 */
void RDxfExporter::writeLeader(const RLeaderEntity& l) {
    if (l.countSegments()>0) {
        DL_LeaderData leaderData(l.hasArrowHead(),
                      0,
                      3,
                      0,
                      0,
                      1.0,
                      10.0,
                      l.countVertices(),
                      l.getDimScale());

        dxf.writeLeader(
            *dw,
            leaderData,
            attributes);
        bool first = true;
        for (int i=0; i<l.countSegments(); i++) {
            QSharedPointer<RShape> seg = l.getSegmentAt(i);
            if (seg.isNull()) {
                continue;
            }

            QSharedPointer<RLine> line = seg.dynamicCast<RLine>();
            if (line.isNull()) {
                continue;
            }

            if (first) {
                dxf.writeLeaderVertex(
                    *dw,
                    DL_LeaderVertexData(line->getStartPoint().x,
                                        line->getStartPoint().y,
                                        0.0));
                first = false;
            }
            dxf.writeLeaderVertex(
                *dw,
                DL_LeaderVertexData(line->getEndPoint().x,
                                    line->getEndPoint().y,
                                    0.0));
        }

        dxf.writeLeaderEnd(*dw, leaderData);
    } else {
        qWarning() << "RDxfExporter::writeLeader: "
            << "dropping leader without segments";
    }
}

/**
 * Writes the given hatch entity to the file.
 */
void RDxfExporter::writeHatch(const RHatchEntity& h) {
    // split hatch into simple entities:
    if (dxf.getVersion()==DL_Codes::AC1009 || dxf.getVersion()==DL_Codes::AC1009_MIN) {
        //writeAtomicEntities(h, RS2::ResolveAll);
        return;
    }

    if (h.getLoopCount()==0) {
        qWarning() << "RDxfExporter::writeHatch: skip hatch without loops";
        return;
    }

    // check if all of the loops contain entities:
//    for (RS_Entity* l=h->firstEntity(RS2::ResolveNone);
//         l!=NULL;
//         l=h->nextEntity(RS2::ResolveNone)) {

//        if (l->isContainer() && !l->getFlag(RS2::FlagTemp)) {
//            if (l->count()==0) {
//                writeIt = false;
//            }
//        }
//    }

    DL_HatchData data(h.getLoopCount(),
                      h.isSolid(),
                      h.getScale(),
                      RMath::rad2deg(h.getAngle()),
                      (const char*)RDxfExporter::escapeUnicode(h.getPatternName()),
                      h.getOriginPoint().x, h.getOriginPoint().y);

    dxf.writeHatch1(*dw, data, attributes);

    for (int i=0; i<h.getLoopCount(); i++) {
        QList<QSharedPointer<RShape> > loop = h.getLoopBoundary(i);
        // Write hatch loops:
        DL_HatchLoopData lData(loop.size());
        dxf.writeHatchLoop1(*dw, lData);

        // Write hatch loop edges:
        for (int k=0; k<loop.size(); k++) {
            QSharedPointer<RShape> shape = loop[k];

            // line:
            QSharedPointer<RLine> line = shape.dynamicCast<RLine>();
            if (!line.isNull()) {
                dxf.writeHatchEdge(
                            *dw,
                            DL_HatchEdgeData(line->getStartPoint().x,
                                             line->getStartPoint().y,
                                             line->getEndPoint().x,
                                             line->getEndPoint().y));
            }

            // arc:
            QSharedPointer<RArc> arc = shape.dynamicCast<RArc>();
            if (!arc.isNull()) {
                if (!arc->isReversed()) {
                    dxf.writeHatchEdge(
                                *dw,
                                DL_HatchEdgeData(arc->getCenter().x,
                                                 arc->getCenter().y,
                                                 arc->getRadius(),
                                                 arc->getStartAngle(),
                                                 arc->getEndAngle(),
                                                 true));
                } else {
                    dxf.writeHatchEdge(
                                *dw,
                                DL_HatchEdgeData(arc->getCenter().x,
                                                 arc->getCenter().y,
                                                 arc->getRadius(),
                                                 2*M_PI-arc->getStartAngle(),
                                                 2*M_PI-arc->getEndAngle(),
                                                 false));
                }
            }

            // full circle:
            QSharedPointer<RCircle> circle = shape.dynamicCast<RCircle>();
            if (!circle.isNull()) {
                dxf.writeHatchEdge(
                            *dw,
                            DL_HatchEdgeData(circle->getCenter().x,
                                             circle->getCenter().y,
                                             circle->getRadius(),
                                             0.0,
                                             2*M_PI,
                                             true));
            }

            // ellipse arc:
            QSharedPointer<REllipse> ellipse = shape.dynamicCast<REllipse>();
            if (!ellipse.isNull()) {
                double startAngle = ellipse->getStartAngle();
                double endAngle = ellipse->getEndAngle();
                if (ellipse->isFullEllipse()) {
                    startAngle = 0.0;
                    endAngle = 2*M_PI;
                }
                else if (ellipse->isReversed()) {
                    startAngle = 2*M_PI - RMath::getNormalizedAngle(startAngle);
                    endAngle = 2*M_PI - RMath::getNormalizedAngle(endAngle);
                }
                dxf.writeHatchEdge(
                            *dw,
                            DL_HatchEdgeData(ellipse->getCenter().x,
                                             ellipse->getCenter().y,
                                             ellipse->getMajorPoint().x,
                                             ellipse->getMajorPoint().y,
                                             ellipse->getRatio(),
                                             startAngle,
                                             endAngle,
                                             !ellipse->isReversed()));
            }

            // spline:
            QSharedPointer<RSpline> spline = shape.dynamicCast<RSpline>();
            if (!spline.isNull()) {
                QList<double> knotVector = spline->getActualKnotVector();
                if (knotVector.size()>0) {
                    knotVector.prepend(knotVector.first());
                    knotVector.append(knotVector.last());
                }
                std::vector<double> dxfKnotVector;
                for (int i=0; i<knotVector.size(); i++) {
                    dxfKnotVector.push_back(knotVector[i]);
                }

                std::vector<std::vector<double> > dxfControlPoints;
                QList<RVector> controlPoints = spline->getControlPoints();
                for (int i=0; i<controlPoints.size(); i++) {
                    RVector cp = controlPoints[i];
                    std::vector<double> dxfV;
                    dxfV.push_back(cp.x);
                    dxfV.push_back(cp.y);
                    dxfControlPoints.push_back(dxfV);
                }

                std::vector<std::vector<double> > dxfFitPoints;
                QList<RVector> fitPoints = spline->getFitPoints();
                for (int i=0; i<fitPoints.size(); i++) {
                    RVector fp = fitPoints[i];
                    std::vector<double> dxfV;
                    dxfV.push_back(fp.x);
                    dxfV.push_back(fp.y);
                    dxfFitPoints.push_back(dxfV);
                }

                dxf.writeHatchEdge(
                            *dw,
                            DL_HatchEdgeData(spline->getDegree(),
                                             false,                    // rational
                                             spline->isPeriodic(),
                                             knotVector.size(),
                                             spline->countControlPoints(),
                                             spline->countFitPoints(),
                                             dxfKnotVector,
                                             dxfControlPoints,
                                             dxfFitPoints,
                                             std::vector<double>(),
                                             spline->getTangentAtStart().x,
                                             spline->getTangentAtStart().y,
                                             spline->getTangentAtEnd().x,
                                             spline->getTangentAtEnd().y
                                             ));
            }
        }
        dxf.writeHatchLoop2(*dw, lData);
    }
    dxf.writeHatch2(*dw, data, attributes);
}

/**
 * Writes the given image entity to the file.
 */
void RDxfExporter::writeImage(const RImageEntity& img) {
    int handle = dxf.writeImage(
                     *dw,
                     DL_ImageData(std::string(""),
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
                                  img.getFade()),
                     attributes);
    imageHandles.insert(img.getId(), handle);
}

/**
 * Writes the given solid entity to the file.
 */
void RDxfExporter::writeSolid(const RSolidEntity& sol) {
    RVector c1 = sol.getVertexAt(0);
    RVector c2 = sol.getVertexAt(1);
    RVector c3 = sol.getVertexAt(2);
    RVector c4 = c3;

    if (sol.countVertices()>3) {
        c4 = sol.getVertexAt(3);
    }

    dxf.writeSolid(*dw,
        DL_SolidData(c1.x, c1.y, c1.z,
                     c2.x, c2.y, c2.z,
                     c3.x, c3.y, c3.z,
                     c4.x, c4.y, c4.z,
                     0),
        attributes);
}

/**
 * Writes the given trace entity to the file.
 */
void RDxfExporter::writeTrace(const RTraceEntity& t) {
    RVector c1 = t.getVertexAt(0);
    RVector c2 = t.getVertexAt(1);
    RVector c3 = t.getVertexAt(2);
    RVector c4 = t.getVertexAt(3);

    dxf.writeTrace(*dw,
                   DL_TraceData(c1.x, c1.y, c1.z,
                                c2.x, c2.y, c2.z,
                                c3.x, c3.y, c3.z,
                                c4.x, c4.y, c4.z,
                                0),
                   attributes);
}

/**
 * Writes an IMAGEDEF object into an OBJECT section.
 */
void RDxfExporter::writeImageDef(const RImageEntity& img) {
    if (!imageHandles.contains(img.getId())) {
        qWarning() << "RDxfExporter::writeImageDef: no handle for given image";
        return;
    }
    int handle = imageHandles.value(img.getId());
    dxf.writeImageDef(
        *dw,
        handle,
        DL_ImageData((const char*)RDxfExporter::escapeUnicode(img.getFileName()),
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

/**
 * Writes the given block reference entity to the file.
 */
void RDxfExporter::writeBlockReference(const RBlockReferenceEntity& br) {
    QString blockName = br.getReferencedBlockName();
    if (dxf.getVersion()==DL_Codes::AC1009 || dxf.getVersion()==DL_Codes::AC1009_MIN) {
        if (blockName.at(0)=='*') {
            blockName[0] = '_';
        }
    }

    dxf.writeInsert(
        *dw,
        DL_InsertData(
            (const char*)RDxfExporter::escapeUnicode(blockName),
            br.getPosition().x,
            br.getPosition().y,
            0.0,
            br.getScaleFactors().x,
            br.getScaleFactors().y,
            0.0,
            RMath::rad2deg(br.getRotation()),
            br.getColumnCount(), br.getRowCount(),
            br.getColumnSpacing(), br.getRowSpacing()
        ),
        attributes
    );
}

//void RDxfExporter::writeExplodedEntities(const REntity& entity) {
//    const RShape* shape = entity.castToConstShape();
//    if (shape==NULL) {
//        qWarning() << "RDxfExporter::writeExplodedEntities: not a shape";
//        return;
//    }

//    const RExplodable* explodable = dynamic_cast<RExplodable*>(&entity);
//    if (explodable!=NULL) {
//        QList<QSharedPointer<RShape> > segments = explodable->getExploded();
//        for (int i=0; i<segments.count(); i++) {
//            segments[i];
//        }
//    }


//}

/**
 * \return the entities attributes as a DL_Attributes object.
 */
DL_Attributes RDxfExporter::getEntityAttributes(const REntity& entity) {
    // Layer:
    QString layerName = entity.getLayerName();
    if (minimalistic) {
        layerName = "0";
    }

    // Color:
    int color = RDxfServices::colorToNumber(entity.getColor(), dxfColors);
    int color24 = RDxfServices::colorToNumber24(entity.getColor());

    // Linetype:
    QString linetype = document->getLinetypeName(entity.getLinetypeId());
    if (minimalistic) {
        linetype = "CONTINUOUS";
    }

    // Width:
    int width = RDxfServices::widthToNumber(entity.getLineweight());

    DL_Attributes attrib((const char*)RDxfExporter::escapeUnicode(layerName),
                         color,
                         color24,
                         width,
                         (const char*)RDxfExporter::escapeUnicode(linetype));
    attrib.setLinetypeScale(entity.getLinetypeScale());
    return attrib;
}

DL_StyleData RDxfExporter::getStyle(const RTextBasedEntity& entity) {
    QString name = QString("textstyle%1").arg(textStyleCounter++);
    return DL_StyleData((const char*)RDxfExporter::escapeUnicode(name),
        0,    // flags
        0.0,  // fixed height (not fixed)
        1.0,  // width factor
        0.0,  // oblique angle
        0,    // text generation flags
        entity.getTextHeight(),  // last height used
        (const char*)RDxfExporter::escapeUnicode(entity.getFontName()),    // primary font file
        ""                       // big font file
        );
}

QByteArray RDxfExporter::escapeUnicode(const QString& str) {
    // DXF R15: DWGCODEPAGE==ANSI_1252 means latin1:
    return RDxfServices::escapeUnicode(str).toLatin1();
}
