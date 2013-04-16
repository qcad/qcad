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

RDxfExporter::RDxfExporter(RDocument& document,
    RMessageHandler* messageHandler,
    RProgressHandler* progressHandler)
    : RFileExporter(document, messageHandler, progressHandler) {

}

bool RDxfExporter::exportFile(const QString& fileName, const QString& nameFilter, bool resetModified) {
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
    dw->tableLineTypes(lts.count());
    qDebug() << "RDxfExporter::exportFile: linetypes loop";
    for (int i=0; i<lts.count(); i++) {
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
    dw->tableLayers(layerNames.count());
    for (int i=0; i<layerNames.count(); ++i) {
        QSharedPointer<RLayer> layer = document->queryLayer(layerNames[i]);
        writeLayer(*layer);
        //RS_Layer* l = graphic->layerAt(i);
        //writeLayer(l);
    }
    dw->tableEnd();

    /*
    // STYLE:
    RS_DEBUG->print("writing styles...");
    dxf.writeStyle(*dw);

    // VIEW:
    RS_DEBUG->print("writing views...");
    dxf.writeView(*dw);

    // UCS:
    RS_DEBUG->print("writing ucs...");
    dxf.writeUcs(*dw);

    // Appid:
    RS_DEBUG->print("writing appid...");
    dw->tableAppid(1);
    writeAppid("ACAD");
    dw->tableEnd();

    // DIMSTYLE:
    RS_DEBUG->print("writing dim styles...");
    dxf.writeDimStyle(*dw,
                      graphic->getVariableDouble("$DIMASZ", 2.5),
                      graphic->getVariableDouble("$DIMEXE", 1.25),
                      graphic->getVariableDouble("$DIMEXO", 0.625),
                      graphic->getVariableDouble("$DIMGAP", 0.625),
                      graphic->getVariableDouble("$DIMTXT", 2.5));

    // BLOCK_RECORD:
    if (formatType!=RS2::FormatDxf12) {
        RS_DEBUG->print("writing block records...");
        dxf.writeBlockRecord(*dw);

        for (int i=0; i<graphic->countBlocks(); ++i) {
            RS_Block* blk = graphic->blockAt(i);
            dxf.writeBlockRecord(*dw,
                std::string((const char*)blk->getName().toLatin1()));
        }
        dw->tableEnd();
    }

    // end of tables:
    RS_DEBUG->print("writing end of section TABLES...");
    dw->sectionEnd();


    // Section BLOCKS:
    RS_DEBUG->print("writing blocks...");
    dw->sectionBlocks();

    if (formatType!=RS2::FormatDxf12) {
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

    for (int i=0; i<graphic->countBlocks(); ++i) {
        RS_Block* blk = graphic->blockAt(i);

        writeBlock(blk);
    }
    dw->sectionEnd();


    // Section ENTITIES:
    RS_DEBUG->print("writing section ENTITIES...");
    dw->sectionEntities();
    for (RS_Entity* e=graphic->firstEntity(RS2::ResolveNone);
            e!=NULL;
            e=graphic->nextEntity(RS2::ResolveNone)) {

        writeEntity(e);
    }
    RS_DEBUG->print("writing end of section ENTITIES...");
    dw->sectionEnd();

    if (formatType!=RS2::FormatDxf12) {
        RS_DEBUG->print("writing section OBJECTS...");
        dxf.writeObjects(*dw);

        // IMAGEDEF's from images in entities and images in blocks
        RS_StringList written;
        for (int i=0; i<graphic->countBlocks(); ++i) {
            RS_Block* block = graphic->blockAt(i);
            for (RS_Entity* e=block->firstEntity(RS2::ResolveAll);
                    e!=NULL;
                    e=block->nextEntity(RS2::ResolveAll)) {

                if (e->rtti()==RS2::EntityImage) {
                    RS_Image* img = dynamic_cast<RS_Image*>(e);
                    if (written.contains(file)==0 && img->getHandle()!=0) {
                        writeImageDef(img);
                        written.append(img->getFile());
                    }
                }
            }
        }
        for (RS_Entity* e=graphic->firstEntity(RS2::ResolveNone);
                e!=NULL;
                e=graphic->nextEntity(RS2::ResolveNone)) {

            if (e->rtti()==RS2::EntityImage) {
                RS_Image* img = dynamic_cast<RS_Image*>(e);
                if (written.contains(file)==0 && img->getHandle()!=0) {
                    writeImageDef(img);
                    written.append(img->getFile());
                }
            }
        }
        RS_DEBUG->print("writing end of section OBJECTS...");
        dxf.writeObjectsEnd(*dw);
    }

    RS_DEBUG->print("writing EOF...");
    dw->dxfEOF();
    */

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

    //int colorSign = 1;

    QSharedPointer<RLinetype> lt = document->queryLinetype(l.getLinetypeId());
    if (lt.isNull()) {
        qDebug() << "Layer " << l.getName() << " has invalid line type ID";
        return;
    }

    /*
    dxf.writeLayer(
        *dw,
        DL_LayerData((const char*)l.getName().toLatin1(),
                     l.isFrozen() + (l.isLocked()<<2)),
        DL_Attributes(std::string(""),
                      RDxfServices::colorToNumber(l.getColor()),
                      RDxfServices::colorToNumber24(l.getColor()),
                      RDxfServices::widthToNumber(l.getLineweight()),
                      (const char*)lt->getName().toLatin1()));
    */
}
