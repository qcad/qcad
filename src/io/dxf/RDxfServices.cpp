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
#include <QFileInfo>
#include <QTemporaryFile>

#include "RDimensionData.h"
#include "RDxfServices.h"
#include "REllipse.h"
#include "RHatchData.h"
#include "RTextRenderer.h"
#include "RUnit.h"

RDxfServices::RDxfServices() :
    qcad2GotDIMZIN(false),
    qcad2GotDIMAZIN(false),
    qcad2GotInvalidEllipse(false),
    qcad2Compatibility(false) {

}

void RDxfServices::reset() {
    qcad2LayerMapping.clear();
    qcad2BlockMapping.clear();
}

void RDxfServices::fixQCad2String(QString& str) const {
    // correct stacked text
    // \S+0.1\-0.1; -> \S+0.1^-0.1;
    QRegExp rx("\\\\S([^\\\\]*)\\\\([^;]*);");
    str.replace(rx, "\\S\\1^\\2;");
}

void RDxfServices::fixDimensionLabel(RDimensionData& dimData) {
    QString text = dimData.getText();

    // strip away initial vertical alignment, e.g. '\A1;' :
    QRegExp rxAlignment("^" + RTextRenderer::rxAlignmentChange);
    text.replace(rxAlignment, "");

    // analyze and strip stacked text (tolerance) at end:
    QRegExp rxTolerance(RTextRenderer::rxStackedText + "$");
    if (rxTolerance.indexIn(text)!=-1) {
        dimData.setUpperTolerance(rxTolerance.cap(1));
        dimData.setLowerTolerance(rxTolerance.cap(2));
    }
    text.replace(rxTolerance, "");

    // auto measurement is default (empty string):
    if (text=="<>") {
        text = "";
    }

    dimData.setText(text);
}

void RDxfServices::detectQCad2Format(const QString& fileName) {
    qcad2Compatibility = false;
    QFileInfo fi(fileName);
    if (!fi.exists()) {
        return;
    }

    if (fi.size()==0) {
        return;
    }

    if (fi.suffix().toUpper()!="DXF") {
        return;
    }

    qcad2GotDIMZIN = false;
    qcad2GotDIMAZIN = false;
    qcad2GotInvalidEllipse = false;
    qcad2Compatibility = false;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream ts(&file);
        QString code = ts.readLine(75).trimmed();
        if (code=="999") {
            QString comment = ts.readLine(75).trimmed();
            if (comment.startsWith("dxflib 2.")) {
                qcad2Compatibility = true;
            }
        }

        if (qcad2Compatibility) {
            // parse header for missing / present variables:
            QString line;
            while (!ts.atEnd()) {
                line = ts.readLine();
                if (line.contains("$DIMZIN")) {
                    qcad2GotDIMZIN = true;
                }
                else if (line.contains("$DIMAZIN")) {
                    qcad2GotDIMAZIN = true;
                }
                else if (line == "ENDSEC"){
                    break;
                }
            }
        }

        file.close();
    }
}

void RDxfServices::fixBlockName(QString& blockName) {
    // fix invalid block names (mainly from QCAD 2):
    if (!blockName.startsWith("*")) {
        QString oldBlockName = blockName;
        blockName.replace(QRegExp("[<>/\":;?*|,=`\\\\]"), "_");
        qcad2BlockMapping.insert(oldBlockName, blockName);
    }
}

void RDxfServices::fixLayerName(QString& layerName) {
    // fix invalid layer names (mainly from QCAD 2):
    QString oldLayerName = layerName;
    layerName.replace(QRegExp("[<>/\":;?*|,=`\\\\]"), "_");
    qcad2LayerMapping.insert(oldLayerName, layerName);
}

QString RDxfServices::getQCad2LayerName(const QString& layerName) const {
    if (qcad2LayerMapping.contains(layerName)) {
        return qcad2LayerMapping.value(layerName);
    }
    return layerName;
}

QString RDxfServices::getQCad2BlockName(const QString& blockName) const {
    if (qcad2BlockMapping.contains(blockName)) {
        return qcad2BlockMapping.value(blockName);
    }
    return blockName;
}

QString RDxfServices::getQCad2Font(const QString& handle) const {
    if (qcad2TextFonts.contains(handle)) {
        return qcad2TextFonts.value(handle);
    }

    //Q_ASSERT(false);
    return "standard";
}

QString RDxfServices::getQCad2DimensionLabel(const QString& handle) const {
    if (qcad2DimensionLabels.contains(handle)) {
        return qcad2DimensionLabels.value(handle);
    }

    Q_ASSERT(false);
    return "";
}

/**
 * QCAD 2 stores the font name in field 'text style name', DXF code 7 which
 * is not supported by Teigha. This function collects all font names of
 * MTEXT entities for use by RDwgMTextImporter.
 */
QString RDxfServices::collectQCad2Info(const QString& fileName) {
    qcad2TextFonts.clear();

    QFileInfo fi(fileName);
    if (!fi.exists()) {
        qWarning() << "RDxfServices::collectQCad2Info: file does not exist: " << fileName;
        return NULL;
    }

    if (fi.size()==0) {
        qWarning() << "RDxfServices::collectQCad2Info: file size is zero: " << fileName;
        return NULL;
    }

    if (fi.suffix().toUpper()!="DXF") {
        qWarning() << "RDxfServices::collectQCad2Info: file is not a DXF file: " << fileName;
        return NULL;
    }


    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "RDxfServices::collectQCad2Info: cannot read file: " << fileName;
        return NULL;
    }

    //QTemporaryFile* tmpFile = new QTemporaryFile("qcad_temp_XXXXXX.dxf");
    QTemporaryFile* tmpFile = new QTemporaryFile();
    if (!tmpFile->open()) {
        qWarning() << "RDxfServices::collectQCad2Info: cannot write to file: " << tmpFile->fileName();
        delete tmpFile;

        return NULL;
    }

    QTextStream ts(&file);
    //ts.setCodec("ISO 8859-1");
    QTextStream tsTmp(tmpFile);
    //tsTmp.setCodec("UTF-8");
    //tsTmp.setCodec("ISO 8859-1");
    tsTmp.setFieldAlignment(QTextStream::AlignRight);

    bool gotMText = false;
    bool gotDimension = false;
    bool gotEllipse = false;
    bool gotPSVPSCALE = false;
    bool skip = false;
    QString handleMText;
    QString handleDimension;
    QMultiMap<int, QString> ellipseData;
    QList<int> ellipseDataOrder;

    while (!ts.atEnd()) {
        skip = false;
        QString code = ts.readLine().trimmed();
        QString value = ts.readLine().trimmed();

        if (code=="9") {
            if (value=="$PSVPSCALE") {
                gotPSVPSCALE = true;
            }
            else {
                gotPSVPSCALE = false;
            }
        }

        if (gotPSVPSCALE && (code=="10" || code=="20" || code=="30")) {
            if (code=="10") {
                tsTmp << "40";
                tsTmp << '\n';
                tsTmp << value << '\n';
            }
            skip = true;
        }

        if (code=="0") {
            if (gotEllipse) {
                RVector majorPoint;
                majorPoint.x = ellipseData.value(11).toDouble();
                majorPoint.y = ellipseData.value(21).toDouble();

                // correct ratio:
                double ratio = ellipseData.value(40).toDouble();
                if (ratio<0.0 || ratio>1.0) {
                    RVector center;
                    center.x = ellipseData.value(10).toDouble();
                    center.y = ellipseData.value(20).toDouble();
                    double startParam = ellipseData.value(41).toDouble();
                    double endParam = ellipseData.value(42).toDouble();
                    REllipse ellipse(center, majorPoint, ratio, startParam, endParam, false);
                    ratio = ellipse.getRatio();
                    majorPoint = ellipse.getMajorPoint();
                    startParam = ellipse.getStartParam();
                    endParam = ellipse.getEndParam();

                    ellipseData.replace(11, QString("%1").arg(majorPoint.x));
                    ellipseData.replace(21, QString("%1").arg(majorPoint.y));
                    ellipseData.replace(40, QString("%1").arg(ratio));
                    ellipseData.replace(41, QString("%1").arg(startParam));
                    ellipseData.replace(42, QString("%1").arg(endParam));
                }

                // check if major radius is 0 or ratio is 0
                // and drop ellipse if that is the case:
                if (majorPoint.getMagnitude2d()>1.0e-6 &&
                    fabs(ratio)>1.0e-6) {
                    // write corrected ellipse entity to temporary file:
                    for (int i=0; i<ellipseDataOrder.size(); i++) {
                        int iCode = ellipseDataOrder.at(i);
                        QStringList values = ellipseData.values(iCode);
                        ellipseData.remove(iCode);
                        QString value = values.takeLast();
                        for (int k=values.size()-1; k>=0; k--) {
                            ellipseData.insertMulti(iCode, values[k]);
                        }

                        tsTmp << iCode;
                        tsTmp << '\n';
                        tsTmp << value << '\n';
                    }
                }
                else {
                    qDebug() << "dropping ellipse";
                }
            }

            gotMText = false;
            gotDimension = false;
            gotEllipse = false;
            gotPSVPSCALE = false;
            ellipseData.clear();
            ellipseDataOrder.clear();

            if (value=="MTEXT") {
                gotMText = true;
            }
            else if (value=="DIMENSION") {
                gotDimension = true;
            }
            else if (value=="ELLIPSE") {
                gotEllipse = true;
            }
        }

        if (gotMText) {
            // parse MTEXT for font name:
            if (code=="5") {
                handleMText = value;
            }
            else if (code=="7") {
                value = value.toLower();
                if (value=="courier") {
                    value="CourierCad";
                }
                else if (value=="normal") {
                    value="standard";
                }
                else if (value=="symbol") {
                    value="SymbolCad";
                }
                qcad2TextFonts.insert(handleMText, value);
            }
        }

        else if (gotDimension) {
            // parse DIMENSION for dimension text:
            if (code=="5") {
                handleDimension = value;
            }
            else if (code=="1") {
                qcad2DimensionLabels.insert(handleDimension, value);
            }
        }

        else if (gotEllipse) {
            int iCode = code.toInt();
            ellipseDataOrder.append(iCode);
            ellipseData.insertMulti(iCode, value);
        }

        if (!gotEllipse && !skip) {
            tsTmp << code;
            tsTmp << '\n';
            tsTmp << value;
            tsTmp << '\n';
        }
    }

    file.close();
    tmpFile->close();

    QString tmpFileName = tmpFile->fileName();

    tmpFile->setAutoRemove(false);
    delete tmpFile;

    return tmpFileName;
}

double RDxfServices::getQCad2PatternAngle(double angle, const QString& patternName) const {
    QString pat = patternName.toUpper();
    if (pat=="ESCHER") {
        return angle - M_PI/2.0;
    }
    else if (pat=="HEX") {
        return angle + M_PI/6;
    }
    else if (pat=="HONEYCOMB") {
        return angle + M_PI/2.0;
    }
    else if (pat=="TRIANGLE_A" || pat=="TRIANGLE_B") {
        return angle + M_PI;
    }
    else if (pat=="ISO03W100" || pat=="ISO03W100A") {
        // converted to ANSI31 for compatibility:
        return angle - M_PI/4.0;
    }

    return angle;
}

/**
 * \param scale Old QCAD 2 pattern scale.
 * \param patternName Old QCAD 2 pattern name.
 */
double RDxfServices::getQCad2PatternScale(double scale, const QString& patternName) const {
    QString pat = patternName.toUpper();
    if (pat=="ANGLE") {
        return scale * 7;
    }
    else if (pat=="ANSI31" || pat=="CONCRETE") {
        return scale * (sqrt(2.0) / 3.175);
    }
    else if (pat=="AR-B816" || pat=="AR-B816C" ||
             pat=="AR-B88" ||
             pat=="AR-BRELM" || pat=="AR-BRSTD" ||
             pat=="AR-CONC" || pat=="AR-HBONE" ||
             pat=="AR-PARQ1" || pat=="AR-ROOF" ||
             pat=="AR-RSHKE" || pat=="SAND") {
        return scale * (5.0 / 20.32);
    }
    else if (pat=="CLAY") {
        return scale * 4.2;
    }
    else if (pat=="EARTH") {
        return scale * (1.0 / 0.127);
    }
    else if (pat=="ESCHER") {
        return scale * (10.0 / 5.279);
    }
    else if (pat=="HEXAGON_A" || pat=="HEXAGON_B" || pat=="PANTAGON_A" || pat=="PANTAGON_B") {
        return scale * (3.031117 / 0.9525);
    }
    else if (pat=="TRIANGLE_A" || pat=="TRIANGLE_B") {
        return scale * (3.03 / 0.47625);
    }
    else if (pat=="GRASS" || pat=="GRASS_B") {
        return scale * 1.68;
    }
    else if (pat=="BOX") {
        return scale * (7.5 / 1.905);
    }
    else if (pat=="BRICK") {
        return scale * (5.0 / 0.635);
    }
    else if (pat=="BRSTONE") {
        return scale * (1.6667 / 0.8382);
    }
    else if (pat=="CROSS") {
        return scale * (15.0 / 3.175);
    }
    else if (pat=="DOLMIT") {
        return scale * (8.333 / 6.35);
    }
    else if (pat=="FLEX") {
        return scale * (50.0 / 6.35);
    }
    else if (pat=="HEX") {
        return scale * (8.334 / 5.5);
    }
    else if (pat=="HONEYCOMB") {
        return scale * (9.523823 / 6.35);
    }
    else if (pat=="HOUND") {
        return scale * (12.5 / 4.7625);
    }
    else if (pat=="KERPELE") {
        return scale * (14.1421 / 3.175);
    }
    else if (pat=="PLASTIC") {
        return scale * (1.414216 / 3.175);
    }
    else if (pat=="ISO03W100") {
        // converted to ANSI31 for compatibility:
        return scale * (16.0+2.0/3.0) / 3.175;
    }
    else if (pat=="ISO03W100A") {
        // converted to ANSI31 for compatibility:
        return scale * 33.333 / 3.175;
    }
    else if (pat=="SACNCR") {
        return scale * (16.6777 / 2.381);
    }
    else if (pat=="SQUARE") {
        return scale * (50.0 / 3.175);
    }

    return scale;
}

QString RDxfServices::getQCad2PatternName(const QString& patternName) const {
    QString pat = patternName.toUpper();
    if (pat=="CONCRETE") {
        return "ANSI33";
    }
    else if (pat=="PLASTIC") {
        return "ANSI37";
    }
    else if (pat=="AR-ROOF") {
        return "AR-RROOF";
    }
    else if (pat=="SAND") {
        return "AR-SAND";
    }
    else if (pat=="HEXAGON_A" || pat=="HEXAGON_B" || pat=="PANTAGON_A" || pat=="PANTAGON_B") {
        return "STARS";
    }
    else if (pat=="TRIANGLE_A" || pat=="TRIANGLE_B") {
        return "TRIANG";
    }
    else if (pat=="GRASS_B") {
        return "GRASS";
    }
    else if (pat=="HONEYCOMB") {
        return "HONEY";
    }
    else if (pat=="SQUARE") {
        return "NET";
    }
    else if (pat=="ISO03W100" || pat=="ISO03W100A") {
        // converted to ANSI31 for compatibility:
        return "ANSI31";
    }

    // unsupported / obsolete patterns:
    else if (pat=="ARCS" || pat=="ARCS_2" ||
        pat=="DAEMON" || pat=="KERPELE" ||
        pat=="MISC01" || pat=="MISC02" || pat=="MISC03" ||
        pat=="PAISLEY") {

        return "ANSI31";
    }

    return pat;
}

void RDxfServices::fixQCad2HatchData(RHatchData& data) const {
    if (data.isSolid() || !getQCad2Compatibility()) {
        return;
    }

    QString patternName = data.getPatternName();
    double angle = data.getAngle();
    double scale = data.getScale();

    // QCAD 2 stores angles in rad instead of deg as
    // it should for DXF hatch angles:
    angle = RMath::rad2deg(angle);

    // correct angle for some patterns with different base angle in QCAD 3:
    angle = getQCad2PatternAngle(angle, patternName);
    scale = getQCad2PatternScale(scale, patternName);

    // angle is now in rad!
    data.setAngle(angle);
    data.setScale(scale);

    // fix some QCAD 2 pattern names:
    patternName = getQCad2PatternName(patternName);
    data.setPatternName(patternName);
}

/**
 * Makes DXF/DWG font names QCAD compatible by removing .shx and fixing the name if
 * appropriate.
 */
QString RDxfServices::fixFontName(const QString& fontName) const {
    QString ret = fontName;

    if (ret.toLower().contains(".shx")) {
        ret.replace(".shx", "", Qt::CaseInsensitive);
    }

    // CSS in QTextEdit cannot handle a font called "normal":
    if (ret.toLower()=="normal") {
        ret = "standard";
    }

    if (qcad2Compatibility && ret.toLower()=="courier") {
        ret = "courier_2";
    }

    if (ret=="") {
        ret = "standard";
    }

    return ret;
}

RS::KnownVariable RDxfServices::stringToVariable(const QString& s) {
    QString u = s.toUpper();
    if (u.startsWith("$")) {
        u = u.mid(1);
    }
    if (u=="ANGBASE") {
        return RS::ANGBASE;
    }
    if (u=="ANGDIR") {
        return RS::ANGDIR;
    }
    if (u=="ATTMODE") {
        return RS::ATTMODE;
    }
    if (u=="AUNITS") {
        return RS::AUNITS;
    }
    if (u=="AUPREC") {
        return RS::AUPREC;
    }
    if (u=="CECOLOR") {
        return RS::CECOLOR;
    }
    if (u=="CELTSCALE") {
        return RS::CELTSCALE;
    }
    if (u=="CHAMFERA") {
        return RS::CHAMFERA;
    }
    if (u=="CHAMFERB") {
        return RS::CHAMFERB;
    }
    if (u=="CHAMFERC") {
        return RS::CHAMFERC;
    }
    if (u=="CHAMFERD") {
        return RS::CHAMFERD;
    }
    if (u=="CMLJUST") {
        return RS::CMLJUST;
    }
    if (u=="CMLSCALE") {
        return RS::CMLSCALE;
    }
    if (u=="DIMADEC") {
        return RS::DIMADEC;
    }
    if (u=="DIMALT") {
        return RS::DIMALT;
    }
    if (u=="DIMALTD") {
        return RS::DIMALTD;
    }
    if (u=="DIMALTF") {
        return RS::DIMALTF;
    }
    if (u=="DIMALTRND") {
        return RS::DIMALTRND;
    }
    if (u=="DIMALTTD") {
        return RS::DIMALTTD;
    }
    if (u=="DIMALTTZ") {
        return RS::DIMALTTZ;
    }
    if (u=="DIMALTU") {
        return RS::DIMALTU;
    }
    if (u=="DIMALTZ") {
        return RS::DIMALTZ;
    }
    if (u=="DIMAPOST") {
        return RS::DIMAPOST;
    }
    if (u=="DIMASZ") {
        return RS::DIMASZ;
    }
    if (u=="DIMATFIT") {
        return RS::DIMATFIT;
    }
    if (u=="DIMAUNIT") {
        return RS::DIMAUNIT;
    }
    if (u=="DIMAZIN") {
        return RS::DIMAZIN;
    }
    if (u=="DIMBLK") {
        return RS::DIMBLK;
    }
    if (u=="DIMBLK1") {
        return RS::DIMBLK1;
    }
    if (u=="DIMBLK2") {
        return RS::DIMBLK2;
    }
    if (u=="DIMCEN") {
        return RS::DIMCEN;
    }
    if (u=="DIMCLRD") {
        return RS::DIMCLRD;
    }
    if (u=="DIMCLRE") {
        return RS::DIMCLRE;
    }
    if (u=="DIMCLRT") {
        return RS::DIMCLRT;
    }
    if (u=="DIMDEC") {
        return RS::DIMDEC;
    }
    if (u=="DIMDLE") {
        return RS::DIMDLE;
    }
    if (u=="DIMDLI") {
        return RS::DIMDLI;
    }
    if (u=="DIMDSEP") {
        return RS::DIMDSEP;
    }
    if (u=="DIMEXE") {
        return RS::DIMEXE;
    }
    if (u=="DIMEXO") {
        return RS::DIMEXO;
    }
    if (u=="DIMFRAC") {
        return RS::DIMFRAC;
    }
    if (u=="DIMGAP") {
        return RS::DIMGAP;
    }
    if (u=="DIMJUST") {
        return RS::DIMJUST;
    }
    if (u=="DIMLDRBLK") {
        return RS::DIMLDRBLK;
    }
    if (u=="DIMLFAC") {
        return RS::DIMLFAC;
    }
    if (u=="DIMLIM") {
        return RS::DIMLIM;
    }
    if (u=="DIMLUNIT") {
        return RS::DIMLUNIT;
    }
    if (u=="DIMLWD") {
        return RS::DIMLWD;
    }
    if (u=="DIMLWE") {
        return RS::DIMLWE;
    }
    if (u=="DIMPOST") {
        return RS::DIMPOST;
    }
    if (u=="DIMRND") {
        return RS::DIMRND;
    }
    if (u=="DIMSAH") {
        return RS::DIMSAH;
    }
    if (u=="DIMSCALE") {
        return RS::DIMSCALE;
    }
    if (u=="DIMSD1") {
        return RS::DIMSD1;
    }
    if (u=="DIMSD2") {
        return RS::DIMSD2;
    }
    if (u=="DIMSE1") {
        return RS::DIMSE1;
    }
    if (u=="DIMSE2") {
        return RS::DIMSE2;
    }
    if (u=="DIMSOXD") {
        return RS::DIMSOXD;
    }
    if (u=="DIMTAD") {
        return RS::DIMTAD;
    }
    if (u=="DIMTDEC") {
        return RS::DIMTDEC;
    }
    if (u=="DIMTFAC") {
        return RS::DIMTFAC;
    }
    if (u=="DIMTIH") {
        return RS::DIMTIH;
    }
    if (u=="DIMTIX") {
        return RS::DIMTIX;
    }
    if (u=="DIMTM") {
        return RS::DIMTM;
    }
    if (u=="DIMTOFL") {
        return RS::DIMTOFL;
    }
    if (u=="DIMTOH") {
        return RS::DIMTOH;
    }
    if (u=="DIMTOL") {
        return RS::DIMTOL;
    }
    if (u=="DIMTOLJ") {
        return RS::DIMTOLJ;
    }
    if (u=="DIMTP") {
        return RS::DIMTP;
    }
    if (u=="DIMTSZ") {
        return RS::DIMTSZ;
    }
    if (u=="DIMTVP") {
        return RS::DIMTVP;
    }
    if (u=="DIMTXSTY") {
        return RS::DIMTXSTY;
    }
    if (u=="DIMTXT") {
        return RS::DIMTXT;
    }
    if (u=="DIMTZIN") {
        return RS::DIMTZIN;
    }
    if (u=="DIMUPT") {
        return RS::DIMUPT;
    }
    if (u=="DIMZIN") {
        return RS::DIMZIN;
    }
    if (u=="DISPSILH") {
        return RS::DISPSILH;
    }
    if (u=="DRAWORDERCTL") {
        return RS::DRAWORDERCTL;
    }
    if (u=="DWGCODEPAGE") {
        return RS::DWGCODEPAGE;
    }
    if (u=="ELEVATION") {
        return RS::ELEVATION;
    }
    if (u=="EXTMAX") {
        return RS::EXTMAX;
    }
    if (u=="EXTMIN") {
        return RS::EXTMIN;
    }
    if (u=="FACETRES") {
        return RS::FACETRES;
    }
    if (u=="FILLETRAD") {
        return RS::FILLETRAD;
    }
    if (u=="FILLMODE") {
        return RS::FILLMODE;
    }
    if (u=="INSBASE") {
        return RS::INSBASE;
    }
    if (u=="INSUNITS") {
        return RS::INSUNITS;
    }
    if (u=="ISOLINES") {
        return RS::ISOLINES;
    }
    if (u=="LIMCHECK") {
        return RS::LIMCHECK;
    }
    if (u=="LIMMAX") {
        return RS::LIMMAX;
    }
    if (u=="LIMMIN") {
        return RS::LIMMIN;
    }
    if (u=="LTSCALE") {
        return RS::LTSCALE;
    }
    if (u=="LUNITS") {
        return RS::LUNITS;
    }
    if (u=="LUPREC") {
        return RS::LUPREC;
    }
    if (u=="MAXACTVP") {
        return RS::MAXACTVP;
    }
    if (u=="MIRRTEXT") {
        return RS::MIRRTEXT;
    }
    if (u=="ORTHOMODE") {
        return RS::ORTHOMODE;
    }
    if (u=="PDMODE") {
        return RS::PDMODE;
    }
    if (u=="PDSIZE") {
        return RS::PDSIZE;
    }
    if (u=="PELEVATION") {
        return RS::PELEVATION;
    }
    if (u=="PELLIPSE") {
        return RS::PELLIPSE;
    }
    if (u=="PEXTMAX") {
        return RS::PEXTMAX;
    }
    if (u=="PEXTMIN") {
        return RS::PEXTMIN;
    }
    if (u=="PINSBASE") {
        return RS::PINSBASE;
    }
    if (u=="PLIMCHECK") {
        return RS::PLIMCHECK;
    }
    if (u=="PLIMMAX") {
        return RS::PLIMMAX;
    }
    if (u=="PLIMMIN") {
        return RS::PLIMMIN;
    }
    if (u=="PLINEGEN") {
        return RS::PLINEGEN;
    }
    if (u=="PLINEWID") {
        return RS::PLINEWID;
    }
    if (u=="PROXYGRAPHICS") {
        return RS::PROXYGRAPHICS;
    }
    if (u=="PSLTSCALE") {
        return RS::PSLTSCALE;
    }
    if (u=="PUCSNAME") {
        return RS::PUCSNAME;
    }
    if (u=="PUCSORG") {
        return RS::PUCSORG;
    }
    if (u=="PUCSXDIR") {
        return RS::PUCSXDIR;
    }
    if (u=="PUCSYDIR") {
        return RS::PUCSYDIR;
    }
    if (u=="QTEXTMODE") {
        return RS::QTEXTMODE;
    }
    if (u=="REGENMODE") {
        return RS::REGENMODE;
    }
    if (u=="SHADEDGE") {
        return RS::SHADEDGE;
    }
    if (u=="SHADEDIF") {
        return RS::SHADEDIF;
    }
    if (u=="SKETCHINC") {
        return RS::SKETCHINC;
    }
    if (u=="SKPOLY") {
        return RS::SKPOLY;
    }
    if (u=="SPLFRAME") {
        return RS::SPLFRAME;
    }
    if (u=="SPLINESEGS") {
        return RS::SPLINESEGS;
    }
    if (u=="SPLINETYPE") {
        return RS::SPLINETYPE;
    }
    if (u=="SURFTAB1") {
        return RS::SURFTAB1;
    }
    if (u=="SURFTAB2") {
        return RS::SURFTAB2;
    }
    if (u=="SURFTYPE") {
        return RS::SURFTYPE;
    }
    if (u=="SURFU") {
        return RS::SURFU;
    }
    if (u=="SURFV") {
        return RS::SURFV;
    }
    if (u=="TEXTQLTY") {
        return RS::TEXTQLTY;
    }
    if (u=="TEXTSIZE") {
        return RS::TEXTSIZE;
    }
    if (u=="TEXTSTYLE") {
        return RS::TEXTSTYLE;
    }
    if (u=="THICKNESS") {
        return RS::THICKNESS;
    }
    if (u=="TILEMODE") {
        return RS::TILEMODE;
    }
    if (u=="TRACEWID") {
        return RS::TRACEWID;
    }
    if (u=="TREEDEPTH") {
        return RS::TREEDEPTH;
    }
    if (u=="UCSNAME") {
        return RS::UCSNAME;
    }
    if (u=="UCSORG") {
        return RS::UCSORG;
    }
    if (u=="UCSXDIR") {
        return RS::UCSXDIR;
    }
    if (u=="UCSYDIR") {
        return RS::UCSYDIR;
    }
    if (u=="UNITMODE") {
        return RS::UNITMODE;
    }
    if (u=="USERI1") {
        return RS::USERI1;
    }
    if (u=="USERI2") {
        return RS::USERI2;
    }
    if (u=="USERI3") {
        return RS::USERI3;
    }
    if (u=="USERI4") {
        return RS::USERI4;
    }
    if (u=="USERI5") {
        return RS::USERI5;
    }
    if (u=="USERR1") {
        return RS::USERR1;
    }
    if (u=="USERR2") {
        return RS::USERR2;
    }
    if (u=="USERR3") {
        return RS::USERR3;
    }
    if (u=="USERR4") {
        return RS::USERR4;
    }
    if (u=="USERR5") {
        return RS::USERR5;
    }
    if (u=="USRTIMER") {
        return RS::USRTIMER;
    }
    if (u=="VISRETAIN") {
        return RS::VISRETAIN;
    }
    if (u=="WORLDVIEW") {
        return RS::WORLDVIEW;
    }

    return RS::INVALID;
}

