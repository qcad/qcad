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
#include <QTemporaryFile>

#include "RDxfServices.h"
#include "REllipse.h"
#include "RLinetypeListImperial.h"
#include "RUnit.h"

RDxfServices::RDxfServices() :
    version2GotDIMZIN(false),
    version2GotDIMAZIN(false),
    version2GotInvalidEllipse(false),
    dxflibMajorVersion(0),
    dxflibMinorVersion(0),
    codec(NULL) {

}

void RDxfServices::reset() {
    version2LayerMapping.clear();
    version2BlockMapping.clear();
    codec = NULL;
}

void RDxfServices::fixVersion2String(QString& str) const {
    // correct stacked text
    // \S+0.1\-0.1; -> \S+0.1^-0.1;
    QRegExp rx("\\\\S([^\\\\;]*)\\\\([^;]*);");
    str.replace(rx, "\\S\\1^\\2;");
}

void RDxfServices::fixDimensionLabel(QString& text, QString& uTol, QString& lTol) const {
    // strip away initial vertical alignment, e.g. '\A1;'
    QRegExp rxAlignment("^\\\\A(\\d+);");
    text.replace(rxAlignment, "");

    // analyze and strip stacked text (tolerance) at end:
    QRegExp rxTolerance("\\\\S([^^]*)\\^([^;]*);$");
    if (rxTolerance.indexIn(text)!=-1) {
        uTol = rxTolerance.cap(1);
        lTol = rxTolerance.cap(2);
    }
    text.replace(rxTolerance, "");

    // auto measurement is default (empty string):
    if (text=="<>") {
        text = "";
    }
}

void RDxfServices::detectVersion2Format(const QString& fileName) {
    dxflibMajorVersion = 0;
    dxflibMinorVersion = 0;
    dxflibPatchVersion = 0;
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

    version2GotDIMZIN = false;
    version2GotDIMAZIN = false;
    version2GotInvalidEllipse = false;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream ts(&file);
        QString code = ts.readLine(75).trimmed();
        if (code=="999") {
            QString comment = ts.readLine(75).trimmed();
            if (comment.startsWith("dxflib ")) {
                QString versionStr = comment.mid(7);
                //qDebug() << "dxflib version: " << versionStr;
                QRegExp re("(\\d+)\\.(\\d+)\\.(\\d+)\\.(\\d+)");
                int idx = re.indexIn(versionStr);
                if (idx==0) {
                    dxflibMajorVersion = re.cap(1).toInt();
                    dxflibMinorVersion = re.cap(2).toInt();
                    dxflibPatchVersion = re.cap(3).toInt();
                }
            }
        }

        if (getVersion2Compatibility()) {
            // parse header for missing / present variables:
            QString line;
            while (!ts.atEnd()) {
                line = ts.readLine();
                if (line.contains("$DIMZIN")) {
                    version2GotDIMZIN = true;
                }
                else if (line.contains("$DIMAZIN")) {
                    version2GotDIMAZIN = true;
                }
                else if (line == "ENDSEC"){
                    break;
                }
            }
        }

        file.close();
    }
}

QString RDxfServices::getSafeBlockName(QString& blockName) {
    QString ret = blockName;
    ret.replace(QRegExp("[<>/\":;?*|,=`\\\\\n]"), "_");
    ret.replace(QChar(0x0083), "_");
    return ret;
}

void RDxfServices::fixBlockName(QString& blockName) {
    // fix invalid block names (mainly from QCAD 2):
    if (!blockName.startsWith("*")) {
        QString oldBlockName = blockName;
        blockName.replace(QRegExp("[<>/\":;?*|,=`\\\\\n]"), "_");
        blockName.replace(QChar(0x0083), "_");
        version2BlockMapping.insert(oldBlockName, blockName);
    }
}

void RDxfServices::fixLayerName(QString& layerName) {
    // fix invalid layer names (mainly from QCAD 2):
    QString oldLayerName = layerName;
    layerName.replace(QRegExp("[<>/\":;?*|,=`\\\\\n]"), "_");
    layerName.replace(QChar(0x0083), "_");
    version2LayerMapping.insert(oldLayerName, layerName);
}

QString RDxfServices::getVersion2LayerName(const QString& layerName) const {
    if (version2LayerMapping.contains(layerName)) {
        return version2LayerMapping.value(layerName);
    }
    return layerName;
}

QString RDxfServices::getVersionBlockName(const QString& blockName) const {
    if (version2BlockMapping.contains(blockName)) {
        return version2BlockMapping.value(blockName);
    }
    return blockName;
}

QString RDxfServices::getVersion2Font(const QString& handle) const {
    if (version2TextFonts.contains(handle)) {
        return version2TextFonts.value(handle);
    }

    //Q_ASSERT(false);
    return "standard";
}

QString RDxfServices::getVersion2DimensionLabel(const QString& handle) const {
    if (version2DimensionLabels.contains(handle)) {
        return version2DimensionLabels.value(handle);
    }

    Q_ASSERT(false);
    return "";
}

/**
 * QCAD 2 stores the font name in field 'text style name', DXF code 7 which
 * is not supported by Teigha. This function collects all font names of
 * MTEXT entities for use by RDwgMTextImporter.
 */
QString RDxfServices::collectVersion2Info(const QString& fileName) {
    version2TextFonts.clear();

    QFileInfo fi(fileName);
    if (!fi.exists()) {
        qWarning() << "RDxfServices::collectVersion2Info: file does not exist: " << fileName;
        return QString();
    }

    if (fi.size()==0) {
        qWarning() << "RDxfServices::collectVersion2Info: file size is zero: " << fileName;
        return QString();
    }

    if (fi.suffix().toUpper()!="DXF") {
        qWarning() << "RDxfServices::collectVersion2Info: file is not a DXF file: " << fileName;
        return QString();
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "RDxfServices::collectVersion2Info: cannot read file: " << fileName;
        return QString();
    }

    QTemporaryFile* tmpFile = new QTemporaryFile("qcad_temp_XXXXXX.dxf");
//    QTemporaryFile* tmpFile = new QTemporaryFile();
    if (!tmpFile->open()) {
        qWarning() << "RDxfServices::collectVersion2Info: cannot write to temporary file: " << tmpFile->fileName();
        delete tmpFile;

        return QString();
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
                if (majorPoint.getMagnitude2D()>1.0e-6 &&
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
                version2TextFonts.insert(handleMText, value);
            }
        }

        else if (gotDimension) {
            // parse DIMENSION for dimension text:
            if (code=="5") {
                handleDimension = value;
            }
            else if (code=="1") {
                version2DimensionLabels.insert(handleDimension, value);
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

double RDxfServices::getVersion2PatternAngle(double angle, const QString& patternName) const {
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
double RDxfServices::getVersion2PatternScale(double scale, const QString& patternName) const {
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

QString RDxfServices::getVersion2PatternName(const QString& patternName) const {
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

void RDxfServices::fixVersion2HatchData(QString& patternName, double& angle, double& scale, bool solid) const {
    if (solid || !getVersion2Compatibility()) {
        return;
    }

    //QString patternName = data.getPatternName();
    //double angle = data.getAngle();
    //double scale = data.getScale();

    // QCAD 2 stores angles in rad instead of deg as
    // it should for DXF hatch angles:
    angle = RMath::rad2deg(angle);

    // correct angle for some patterns with different base angle in QCAD 3:
    angle = getVersion2PatternAngle(angle, patternName);
    scale = getVersion2PatternScale(scale, patternName);

    // angle is now in rad!
    //data.setAngle(angle);
    //data.setScale(scale);

    // fix some QCAD 2 pattern names:
    patternName = getVersion2PatternName(patternName);
    //data.setPatternName(patternName);
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

    // txt is an a*cad font
    if (ret.toLower()=="txt") {
        ret = "standard";
    }

    if (getVersion2Compatibility() && ret.toLower()=="courier") {
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
    if (u=="MEASUREMENT") {
        return RS::MEASUREMENT;
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

QString RDxfServices::variableToString(RS::KnownVariable v) {
    switch (v) {
    case RS::ANGBASE:
        return "ANGBASE";
    case RS::ANGDIR:
        return "ANGDIR";
    case RS::ATTMODE:
        return "ATTMODE";
    case RS::AUNITS:
        return "AUNITS";
    case RS::AUPREC:
        return "AUPREC";
    case RS::CECOLOR:
        return "CECOLOR";
    case RS::CELTSCALE:
        return "CELTSCALE";
    case RS::CHAMFERA:
        return "CHAMFERA";
    case RS::CHAMFERB:
        return "CHAMFERB";
    case RS::CHAMFERC:
        return "CHAMFERC";
    case RS::CHAMFERD:
        return "CHAMFERD";
    case RS::CMLJUST:
        return "CMLJUST";
    case RS::CMLSCALE:
        return "CMLSCALE";
    case RS::DIMADEC:
        return "DIMADEC";
    case RS::DIMALT:
        return "DIMALT";
    case RS::DIMALTD:
        return "DIMALTD";
    case RS::DIMALTF:
        return "DIMALTF";
    case RS::DIMALTRND:
        return "DIMALTRND";
    case RS::DIMALTTD:
        return "DIMALTTD";
    case RS::DIMALTTZ:
        return "DIMALTTZ";
    case RS::DIMALTU:
        return "DIMALTU";
    case RS::DIMALTZ:
        return "DIMALTZ";
    case RS::DIMAPOST:
        return "DIMAPOST";
    case RS::DIMASZ:
        return "DIMASZ";
    case RS::DIMATFIT:
        return "DIMATFIT";
    case RS::DIMAUNIT:
        return "DIMAUNIT";
    case RS::DIMAZIN:
        return "DIMAZIN";
    case RS::DIMBLK:
        return "DIMBLK";
    case RS::DIMBLK1:
        return "DIMBLK1";
    case RS::DIMBLK2:
        return "DIMBLK2";
    case RS::DIMCEN:
        return "DIMCEN";
    case RS::DIMCLRD:
        return "DIMCLRD";
    case RS::DIMCLRE:
        return "DIMCLRE";
    case RS::DIMCLRT:
        return "DIMCLRT";
    case RS::DIMDEC:
        return "DIMDEC";
    case RS::DIMDLE:
        return "DIMDLE";
    case RS::DIMDLI:
        return "DIMDLI";
    case RS::DIMDSEP:
        return "DIMDSEP";
    case RS::DIMEXE:
        return "DIMEXE";
    case RS::DIMEXO:
        return "DIMEXO";
    case RS::DIMFRAC:
        return "DIMFRAC";
    case RS::DIMGAP:
        return "DIMGAP";
    case RS::DIMJUST:
        return "DIMJUST";
    case RS::DIMLDRBLK:
        return "DIMLDRBLK";
    case RS::DIMLFAC:
        return "DIMLFAC";
    case RS::DIMLIM:
        return "DIMLIM";
    case RS::DIMLUNIT:
        return "DIMLUNIT";
    case RS::DIMLWD:
        return "DIMLWD";
    case RS::DIMLWE:
        return "DIMLWE";
    case RS::DIMPOST:
        return "DIMPOST";
    case RS::DIMRND:
        return "DIMRND";
    case RS::DIMSAH:
        return "DIMSAH";
    case RS::DIMSCALE:
        return "DIMSCALE";
    case RS::DIMSD1:
        return "DIMSD1";
    case RS::DIMSD2:
        return "DIMSD2";
    case RS::DIMSE1:
        return "DIMSE1";
    case RS::DIMSE2:
        return "DIMSE2";
    case RS::DIMSOXD:
        return "DIMSOXD";
    case RS::DIMTAD:
        return "DIMTAD";
    case RS::DIMTDEC:
        return "DIMTDEC";
    case RS::DIMTFAC:
        return "DIMTFAC";
    case RS::DIMTIH:
        return "DIMTIH";
    case RS::DIMTIX:
        return "DIMTIX";
    case RS::DIMTM:
        return "DIMTM";
    case RS::DIMTOFL:
        return "DIMTOFL";
    case RS::DIMTOH:
        return "DIMTOH";
    case RS::DIMTOL:
        return "DIMTOL";
    case RS::DIMTOLJ:
        return "DIMTOLJ";
    case RS::DIMTP:
        return "DIMTP";
    case RS::DIMTSZ:
        return "DIMTSZ";
    case RS::DIMTVP:
        return "DIMTVP";
    case RS::DIMTXSTY:
        return "DIMTXSTY";
    case RS::DIMTXT:
        return "DIMTXT";
    case RS::DIMTZIN:
        return "DIMTZIN";
    case RS::DIMUPT:
        return "DIMUPT";
    case RS::DIMZIN:
        return "DIMZIN";
    case RS::DISPSILH:
        return "DISPSILH";
    case RS::DRAWORDERCTL:
        return "DRAWORDERCTL";
    case RS::DWGCODEPAGE:
        return "DWGCODEPAGE";
    case RS::ELEVATION:
        return "ELEVATION";
    case RS::EXTMAX:
        return "EXTMAX";
    case RS::EXTMIN:
        return "EXTMIN";
    case RS::FACETRES:
        return "FACETRES";
    case RS::FILLETRAD:
        return "FILLETRAD";
    case RS::FILLMODE:
        return "FILLMODE";
    case RS::INSBASE:
        return "INSBASE";
    case RS::INSUNITS:
        return "INSUNITS";
    case RS::ISOLINES:
        return "ISOLINES";
    case RS::LIMCHECK:
        return "LIMCHECK";
    case RS::LIMMAX:
        return "LIMMAX";
    case RS::LIMMIN:
        return "LIMMIN";
    case RS::LTSCALE:
        return "LTSCALE";
    case RS::LUNITS:
        return "LUNITS";
    case RS::LUPREC:
        return "LUPREC";
    case RS::MAXACTVP:
        return "MAXACTVP";
    case RS::MEASUREMENT:
        return "MEASUREMENT";
    case RS::MIRRTEXT:
        return "MIRRTEXT";
    case RS::ORTHOMODE:
        return "ORTHOMODE";
    case RS::PDMODE:
        return "PDMODE";
    case RS::PDSIZE:
        return "PDSIZE";
    case RS::PELEVATION:
        return "PELEVATION";
    case RS::PELLIPSE:
        return "PELLIPSE";
    case RS::PEXTMAX:
        return "PEXTMAX";
    case RS::PEXTMIN:
        return "PEXTMIN";
    case RS::PINSBASE:
        return "PINSBASE";
    case RS::PLIMCHECK:
        return "PLIMCHECK";
    case RS::PLIMMAX:
        return "PLIMMAX";
    case RS::PLIMMIN:
        return "PLIMMIN";
    case RS::PLINEGEN:
        return "PLINEGEN";
    case RS::PLINEWID:
        return "PLINEWID";
    case RS::PROXYGRAPHICS:
        return "PROXYGRAPHICS";
    case RS::PSLTSCALE:
        return "PSLTSCALE";
    case RS::PUCSNAME:
        return "PUCSNAME";
    case RS::PUCSORG:
        return "PUCSORG";
    case RS::PUCSXDIR:
        return "PUCSXDIR";
    case RS::PUCSYDIR:
        return "PUCSYDIR";
    case RS::QTEXTMODE:
        return "QTEXTMODE";
    case RS::REGENMODE:
        return "REGENMODE";
    case RS::SHADEDGE:
        return "SHADEDGE";
    case RS::SHADEDIF:
        return "SHADEDIF";
    case RS::SKETCHINC:
        return "SKETCHINC";
    case RS::SKPOLY:
        return "SKPOLY";
    case RS::SPLFRAME:
        return "SPLFRAME";
    case RS::SPLINESEGS:
        return "SPLINESEGS";
    case RS::SPLINETYPE:
        return "SPLINETYPE";
    case RS::SURFTAB1:
        return "SURFTAB1";
    case RS::SURFTAB2:
        return "SURFTAB2";
    case RS::SURFTYPE:
        return "SURFTYPE";
    case RS::SURFU:
        return "SURFU";
    case RS::SURFV:
        return "SURFV";
    case RS::TEXTQLTY:
        return "TEXTQLTY";
    case RS::TEXTSIZE:
        return "TEXTSIZE";
    case RS::TEXTSTYLE:
        return "TEXTSTYLE";
    case RS::THICKNESS:
        return "THICKNESS";
    case RS::TILEMODE:
        return "TILEMODE";
    case RS::TRACEWID:
        return "TRACEWID";
    case RS::TREEDEPTH:
        return "TREEDEPTH";
    case RS::UCSNAME:
        return "UCSNAME";
    case RS::UCSORG:
        return "UCSORG";
    case RS::UCSXDIR:
        return "UCSXDIR";
    case RS::UCSYDIR:
        return "UCSYDIR";
    case RS::UNITMODE:
        return "UNITMODE";
    case RS::USERI1:
        return "USERI1";
    case RS::USERI2:
        return "USERI2";
    case RS::USERI3:
        return "USERI3";
    case RS::USERI4:
        return "USERI4";
    case RS::USERI5:
        return "USERI5";
    case RS::USERR1:
        return "USERR1";
    case RS::USERR2:
        return "USERR2";
    case RS::USERR3:
        return "USERR3";
    case RS::USERR4:
        return "USERR4";
    case RS::USERR5:
        return "USERR5";
    case RS::USRTIMER:
        return "USRTIMER";
    case RS::VISRETAIN:
        return "VISRETAIN";
    case RS::WORLDVIEW:
        return "WORLDVIEW";
    default:
        return QString();
    }
}

int RDxfServices::getCodeForVariable(RS::KnownVariable v) {
    switch (v) {
//    case RS::3DDWFPREC:
//        return 40;
//    case RS::ACADMAINTVER:
//        return 70;
//    case RS::ACADVER:
//        return 1;
    case RS::ANGBASE:
        return 50;
    case RS::ANGDIR:
        return 70;
    case RS::ATTMODE:
        return 70;
    case RS::AUNITS:
        return 70;
    case RS::AUPREC:
        return 70;
//    case RS::CAMERADISPLAY:
//        return 290;
//    case RS::CAMERAHEIGHT:
//        return 40;
    case RS::CECOLOR:
        return 62;
    case RS::CELTSCALE:
        return 40;
//    case RS::CELTYPE:
//        return 6;
//    case RS::CELWEIGHT:
//        return 370;
//    case RS::CEPSNTYPE:
//        return 380;
    case RS::CHAMFERA:
        return 40;
    case RS::CHAMFERB:
        return 40;
    case RS::CHAMFERC:
        return 40;
    case RS::CHAMFERD:
        return 40;
//    case RS::CLAYER:
//        return 8;
//    case RS::CMATERIAL:
//        return 347;
    case RS::CMLJUST:
        return 70;
    case RS::CMLSCALE:
        return 40;
//    case RS::CMLSTYLE:
//        return 2;
//    case RS::CSHADOW:
//        return 280;
//    case RS::DGNFRAME:
//        return 280;
    case RS::DIMADEC:
        return 70;
    case RS::DIMALT:
        return 70;
    case RS::DIMALTD:
        return 70;
    case RS::DIMALTF:
        return 40;
    case RS::DIMALTRND:
        return 40;
    case RS::DIMALTTD:
        return 70;
    case RS::DIMALTTZ:
        return 70;
    case RS::DIMALTU:
        return 70;
    case RS::DIMALTZ:
        return 70;
    case RS::DIMAPOST:
        return 1;
//    case RS::DIMARCSYM:
//        return 70;
//    case RS::DIMASO:
//        return 70;
//    case RS::DIMASSOC:
//        return 280;
    case RS::DIMASZ:
        return 40;
    case RS::DIMATFIT:
        return 70;
    case RS::DIMAUNIT:
        return 70;
    case RS::DIMAZIN:
        return 70;
    case RS::DIMBLK:
        return 1;
    case RS::DIMBLK1:
        return 1;
    case RS::DIMBLK2:
        return 1;
    case RS::DIMCEN:
        return 40;
    case RS::DIMCLRD:
        return 70;
    case RS::DIMCLRE:
        return 70;
    case RS::DIMCLRT:
        return 70;
    case RS::DIMDEC:
        return 70;
    case RS::DIMDLE:
        return 40;
    case RS::DIMDLI:
        return 40;
    case RS::DIMDSEP:
        return 70;
    case RS::DIMEXE:
        return 40;
    case RS::DIMEXO:
        return 40;
    case RS::DIMFRAC:
        return 70;
//    case RS::DIMFXL:
//        return 40;
//    case RS::DIMFXLON:
//        return 70;
    case RS::DIMGAP:
        return 40;
//    case RS::DIMJOGANG:
//        return 40;
    case RS::DIMJUST:
        return 70;
    case RS::DIMLDRBLK:
        return 1;
    case RS::DIMLFAC:
        return 40;
    case RS::DIMLIM:
        return 70;
//    case RS::DIMLTEX1:
//        return 6;
//    case RS::DIMLTEX2:
//        return 6;
//    case RS::DIMLTYPE:
//        return 6;
    case RS::DIMLUNIT:
        return 70;
    case RS::DIMLWD:
        return 70;
    case RS::DIMLWE:
        return 70;
    case RS::DIMPOST:
        return 1;
    case RS::DIMRND:
        return 40;
    case RS::DIMSAH:
        return 70;
    case RS::DIMSCALE:
        return 40;
    case RS::DIMSD1:
        return 70;
    case RS::DIMSD2:
        return 70;
    case RS::DIMSE1:
        return 70;
    case RS::DIMSE2:
        return 70;
//    case RS::DIMSHO:
//        return 70;
    case RS::DIMSOXD:
        return 70;
//    case RS::DIMSTYLE:
//        return 2;
    case RS::DIMTAD:
        return 70;
    case RS::DIMTDEC:
        return 70;
    case RS::DIMTFAC:
        return 40;
//    case RS::DIMTFILL:
//        return 70;
//    case RS::DIMTFILLCLR:
//        return 70;
    case RS::DIMTIH:
        return 70;
    case RS::DIMTIX:
        return 70;
    case RS::DIMTM:
        return 40;
//    case RS::DIMTMOVE:
//        return 70;
    case RS::DIMTOFL:
        return 70;
    case RS::DIMTOH:
        return 70;
    case RS::DIMTOL:
        return 70;
    case RS::DIMTOLJ:
        return 70;
    case RS::DIMTP:
        return 40;
    case RS::DIMTSZ:
        return 40;
    case RS::DIMTVP:
        return 40;
    case RS::DIMTXSTY:
        return 7;
    case RS::DIMTXT:
        return 40;
//    case RS::DIMTXTDIRECTION:
//        return 70;
    case RS::DIMTZIN:
        return 70;
    case RS::DIMUPT:
        return 70;
    case RS::DIMZIN:
        return 70;
    case RS::DISPSILH:
        return 70;
//    case RS::DWFFRAME:
//        return 280;
    case RS::DWGCODEPAGE:
        return 3;
    case RS::ELEVATION:
        return 40;
//    case RS::ENDCAPS:
//        return 280;
    case RS::EXTMAX:
        return 10;
    case RS::EXTMIN:
        return 10;
//    case RS::EXTNAMES:
//        return 290;
    case RS::FILLETRAD:
        return 40;
    case RS::FILLMODE:
        return 70;
//    case RS::FINGERPRINTGUID:
//        return 2;
//    case RS::HALOGAP:
//        return 280;
//    case RS::HANDSEED:
//        return 5;
//    case RS::HIDETEXT:
//        return 280;
//    case RS::HYPERLINKBASE:
//        return 1;
//    case RS::INDEXCTL:
//        return 280;
    case RS::INSBASE:
        return 10;
    case RS::INSUNITS:
        return 70;
//    case RS::INTERFERECOLOR:
//        return 62;
//    case RS::INTERSECTIONCOLOR:
//        return 70;
//    case RS::INTERSECTIONDISPLAY:
//        return 280;
//    case RS::JOINSTYLE:
//        return 280;
//    case RS::LATITUDE:
//        return 40;
//    case RS::LENSLENGTH:
//        return 40;
//    case RS::LIGHTGLYPHDISPLAY:
//        return 280;
    case RS::LIMCHECK:
        return 70;
    case RS::LIMMAX:
        return 10;
    case RS::LIMMIN:
        return 10;
//    case RS::LOFTANG1:
//        return 40;
//    case RS::LOFTANG2:
//        return 40;
//    case RS::LOFTMAG1:
//        return 40;
//    case RS::LOFTMAG2:
//        return 40;
//    case RS::LOFTNORMALS:
//        return 280;
//    case RS::LOFTPARAM:
//        return 70;
//    case RS::LONGITUDE:
//        return 40;
    case RS::LTSCALE:
        return 40;
    case RS::LUNITS:
        return 70;
    case RS::LUPREC:
        return 70;
//    case RS::LWDISPLAY:
//        return 290;
    case RS::MAXACTVP:
        return 70;
    case RS::MEASUREMENT:
        return 70;
//    case RS::MENU:
//        return 1;
    case RS::MIRRTEXT:
        return 70;
//    case RS::NORTHDIRECTION:
//        return 40;
//    case RS::OBSCOLOR:
//        return 70;
//    case RS::OBSLTYPE:
//        return 280;
//    case RS::OLESTARTUP:
//        return 290;
    case RS::ORTHOMODE:
        return 70;
    case RS::PDMODE:
        return 70;
    case RS::PDSIZE:
        return 40;
    case RS::PELEVATION:
        return 40;
    case RS::PEXTMAX:
        return 10;
    case RS::PEXTMIN:
        return 10;
    case RS::PINSBASE:
        return 10;
    case RS::PLIMCHECK:
        return 70;
    case RS::PLIMMAX:
        return 10;
    case RS::PLIMMIN:
        return 10;
    case RS::PLINEGEN:
        return 70;
    case RS::PLINEWID:
        return 40;
//    case RS::PROJECTNAME:
//        return 1;
    case RS::PROXYGRAPHICS:
        return 70;
    case RS::PSLTSCALE:
        return 70;
//    case RS::PSOLHEIGHT:
//        return 40;
//    case RS::PSOLWIDTH:
//        return 40;
//    case RS::PSTYLEMODE:
//        return 290;
//    case RS::PSVPSCALE:
//        return 40;
//    case RS::PUCSBASE:
//        return 2;
    case RS::PUCSNAME:
        return 2;
    case RS::PUCSORG:
        return 10;
//    case RS::PUCSORGBACK:
//        return 10;
//    case RS::PUCSORGBOTTOM:
//        return 10;
//    case RS::PUCSORGFRONT:
//        return 10;
//    case RS::PUCSORGLEFT:
//        return 10;
//    case RS::PUCSORGRIGHT:
//        return 10;
//    case RS::PUCSORGTOP:
//        return 10;
//    case RS::PUCSORTHOREF:
//        return 2;
//    case RS::PUCSORTHOVIEW:
//        return 70;
    case RS::PUCSXDIR:
        return 10;
    case RS::PUCSYDIR:
        return 10;
    case RS::QTEXTMODE:
        return 70;
//    case RS::REALWORLDSCALE:
//        return 290;
    case RS::REGENMODE:
        return 70;
    case RS::SHADEDGE:
        return 70;
    case RS::SHADEDIF:
        return 70;
//    case RS::SHADOWPLANELOCATION:
//        return 40;
//    case RS::SHOWHIST:
//        return 280;
    case RS::SKETCHINC:
        return 40;
    case RS::SKPOLY:
        return 70;
//    case RS::SOLIDHIST:
//        return 280;
//    case RS::SORTENTS:
//        return 280;
    case RS::SPLFRAME:
        return 70;
    case RS::SPLINESEGS:
        return 70;
    case RS::SPLINETYPE:
        return 70;
//    case RS::STEPSIZE:
//        return 40;
//    case RS::STEPSPERSEC:
//        return 40;
//    case RS::STYLESHEET:
//        return 1;
    case RS::SURFTAB1:
        return 70;
    case RS::SURFTAB2:
        return 70;
    case RS::SURFTYPE:
        return 70;
    case RS::SURFU:
        return 70;
    case RS::SURFV:
        return 70;
//    case RS::TDCREATE:
//        return 40;
//    case RS::TDINDWG:
//        return 40;
//    case RS::TDUCREATE:
//        return 40;
//    case RS::TDUPDATE:
//        return 40;
//    case RS::TDUSRTIMER:
//        return 40;
//    case RS::TDUUPDATE:
//        return 40;
    case RS::TEXTSIZE:
        return 40;
    case RS::TEXTSTYLE:
        return 7;
    case RS::THICKNESS:
        return 40;
    case RS::TILEMODE:
        return 70;
//    case RS::TILEMODELIGHTSYNCH:
//        return 280;
//    case RS::TIMEZONE:
//        return 70;
    case RS::TRACEWID:
        return 40;
    case RS::TREEDEPTH:
        return 70;
//    case RS::UCSBASE:
//        return 2;
    case RS::UCSNAME:
        return 2;
    case RS::UCSORG:
        return 10;
//    case RS::UCSORGBACK:
//        return 10;
//    case RS::UCSORGBOTTOM:
//        return 10;
//    case RS::UCSORGFRONT:
//        return 10;
//    case RS::UCSORGLEFT:
//        return 10;
//    case RS::UCSORGRIGHT:
//        return 10;
//    case RS::UCSORGTOP:
//        return 10;
//    case RS::UCSORTHOREF:
//        return 2;
//    case RS::UCSORTHOVIEW:
//        return 70;
    case RS::UCSXDIR:
        return 10;
    case RS::UCSYDIR:
        return 10;
    case RS::UNITMODE:
        return 70;
    case RS::USERI1:
        return 70;
    case RS::USERI2:
        return 70;
    case RS::USERI3:
        return 70;
    case RS::USERI4:
        return 70;
    case RS::USERI5:
        return 70;
    case RS::USERR1:
        return 40;
    case RS::USERR2:
        return 40;
    case RS::USERR3:
        return 40;
    case RS::USERR4:
        return 40;
    case RS::USERR5:
        return 40;
    case RS::USRTIMER:
        return 70;
//    case RS::VERSIONGUID:
//        return 2;
    case RS::VISRETAIN:
        return 70;
    case RS::WORLDVIEW:
        return 70;
//    case RS::XCLIPFRAME:
//        return 280;
//    case RS::XEDIT:
//        return 290;
    default:
        return -1;
    }
}

RDxfServices::Type RDxfServices::getTypeForVariable(RS::KnownVariable v) {
    int c = getCodeForVariable(v);
    if (c>=0 && c<=9) {
        return String;
    }
    if (c>=10 && c<=39) {
        return Vector;
    }
    if (c>=40 && c<=59) {
        return Float;
    }
    if (c>=60 && c<=99) {
        return Int;
    }

    return Unknown;
}

/**
 * Checks if the given variable is two-dimensional (e.g. $LIMMIN).
 */
bool RDxfServices::isVariable2D(RS::KnownVariable v) {
    if (v==RS::LIMMIN ||
            v==RS::LIMMAX ||
            v==RS::PLIMMIN ||
            v==RS::PLIMMAX
            //v==RS::GRIDUNIT ||
            //v==RS::VIEWCTR
            ) {

        return true;
    } else {
        return false;
    }
}

/**
 * @return Pen with the same attributes as 'attributes'.
 */
RColor RDxfServices::attributesToColor(int color, int color24, const double dxfColors[][3], bool forLayer) {
    RColor ret;
    if (color24!=-1) {
        ret = numberToColor24(color24);
    }
    else {
        ret = numberToColor(color, dxfColors, false, forLayer);
    }

    return ret;
}

/**
 * Converts a color index (num) into a RColor object.
 * Please refer to the dxflib documentation for details.
 *
 * @param num Color number.
 * @param comp Compatibility with older QCad versions (1.5.3 and older)
 */
RColor RDxfServices::numberToColor(int num, const double dxfColors[][3], bool comp, bool forLayer) {
    if (forLayer) {
        num = abs(num);
    }

    // Compatibility with QCad 1.5.3 and older:
    if (comp) {
        switch(num) {
        case 0:
            return RColor(Qt::black);
            break;
        case 1:
            return RColor(Qt::darkBlue);
            break;
        case 2:
            return RColor(Qt::darkGreen);
            break;
        case 3:
            return RColor(Qt::darkCyan);
            break;
        case 4:
            return RColor(Qt::darkRed);
            break;
        case 5:
            return RColor(Qt::darkMagenta);
            break;
        case 6:
            return RColor(Qt::darkYellow);
            break;
        case 7:
            return RColor(Qt::lightGray);
            break;
        case 8:
            return RColor(Qt::darkGray);
            break;
        case 9:
            return RColor(Qt::blue);
            break;
        case 10:
            return RColor(Qt::green);
            break;
        case 11:
            return RColor(Qt::cyan);
            break;
        case 12:
            return RColor(Qt::red);
            break;
        case 13:
            return RColor(Qt::magenta);
            break;
        case 14:
            return RColor(Qt::yellow);
            break;
        case 15:
            return RColor(Qt::black);
            break;
        default:
            break;
        }
    } else {
        if (num==0) {
            return RColor(RColor::ByBlock);
        } else if (num==256) {
            return RColor(RColor::ByLayer);
        } else if (num<=255 && num>=0) {
            return RColor((int)(dxfColors[num][0]*255),
                          (int)(dxfColors[num][1]*255),
                          (int)(dxfColors[num][2]*255));
        } else {
            qWarning() << "RDxfImporter::numberToColor: Invalid color number given.";
            return RColor(RColor::ByLayer);
        }
    }
    return RColor();
}

/**
 * @return color object from DXF coded integer 24 bit color number.
 */
RColor RDxfServices::numberToColor24(int num) {
    return RColor(
              (num&0x00ff0000) >> 16,
              (num&0x0000ff00) >> 8,
              (num&0x000000ff) >> 0
           );
}

/**
 * Converts a line width number (e.g. 1) into a RS2::LineWidth.
 */
RLineweight::Lineweight RDxfServices::numberToWeight(int num) {
    switch (num) {
    case -1:
        return RLineweight::WeightByLayer;
    case -2:
        return RLineweight::WeightByBlock;
    case -3:
        return RLineweight::WeightByLwDefault;
    default:
        if (num<3) {
            return RLineweight::Weight000;
        } else if (num<7) {
            return RLineweight::Weight005;
        } else if (num<11) {
            return RLineweight::Weight009;
        } else if (num<14) {
            return RLineweight::Weight013;
        } else if (num<16) {
            return RLineweight::Weight015;
        } else if (num<19) {
            return RLineweight::Weight018;
        } else if (num<22) {
            return RLineweight::Weight020;
        } else if (num<27) {
            return RLineweight::Weight025;
        } else if (num<32) {
            return RLineweight::Weight030;
        } else if (num<37) {
            return RLineweight::Weight035;
        } else if (num<45) {
            return RLineweight::Weight040;
        } else if (num<52) {
            return RLineweight::Weight050;
        } else if (num<57) {
            return RLineweight::Weight053;
        } else if (num<65) {
            return RLineweight::Weight060;
        } else if (num<75) {
            return RLineweight::Weight070;
        } else if (num<85) {
            return RLineweight::Weight080;
        } else if (num<95) {
            return RLineweight::Weight090;
        } else if (num<103) {
            return RLineweight::Weight100;
        } else if (num<112) {
            return RLineweight::Weight106;
        } else if (num<130) {
            return RLineweight::Weight120;
        } else if (num<149) {
            return RLineweight::Weight140;
        } else if (num<180) {
            return RLineweight::Weight158;
        } else if (num<205) {
            return RLineweight::Weight200;
        } else {
            return RLineweight::Weight211;
        }
    }
    return (RLineweight::Lineweight)num;
}

/**
 * Converts a color into a color number in the DXF palette.
 * The color that fits best is chosen.
 */
int RDxfServices::colorToNumber(const RColor& col, const double dxfColors[][3]) {

    // Special color BYBLOCK:
    if (col.isByBlock()) {
        return 0;
    }

    // Special color BYLAYER
    else if (col.isByLayer()) {
        return 256;
    }

    // Special color black is not in the table but white represents both
    // black and white
    else if (col.red()==0 && col.green()==0 && col.blue()==0) {
        return 7;
    }

    // All other colors
    else {
        int num=0;
        int diff=255*3;  // smallest difference to a color in the table found so far

        // Run through the whole table and compare
        for (int i=1; i<=255; i++) {
            int d = abs(col.red()-(int)(dxfColors[i][0]*255))
                    + abs(col.green()-(int)(dxfColors[i][1]*255))
                    + abs(col.blue()-(int)(dxfColors[i][2]*255));

            if (d<diff) {
                diff = d;
                num = i;
                if (d==0) {
                    break;
                }
            }
        }
        return num;
    }
}

/**
 * @return 24 bit color as DXF prepared int.
 */
int RDxfServices::colorToNumber24(const RColor& col) {
    if (col.isByLayer() || col.isByBlock()) {
        return -1;
    }
    else {
        return (col.red()<<16) | (col.green()<<8) | (col.blue()<<0);
    }
}

/**
 * Converts a RLineweight::Lineweight into an int width for use in DXF files.
 */
int RDxfServices::widthToNumber(RLineweight::Lineweight w) {
    switch (w) {
    case RLineweight::WeightByLayer:
        return -1;
        break;
    case RLineweight::WeightByBlock:
        return -2;
        break;
    case RLineweight::WeightByLwDefault:
        return -3;
        break;
    default:
        break;
    }
    return (int)w;
}

QString RDxfServices::escapeUnicode(const QString& str) {
    QString ret;

    for (int i=0; i<str.length(); i++) {
        QChar ch = str.at(i);
        ushort uc = ch.unicode();
        if (uc>127) {
            ret += QString("\\U+%1").arg(uc, 4, 16, QChar('0'));
        }
        else {
            ret += ch;
        }
    }

    return ret;
}

QString RDxfServices::parseUnicode(const QString& str) {
    QString ret = str;
    QRegExp reg;
    reg.setPattern("\\\\[Uu]\\+([0-9a-fA-F]{4})");
    int ucPos = 0;
    bool ok = true;
    int uc = 0;
    while ((ucPos = reg.indexIn(ret, 0)) != -1) {
        uc = reg.cap(1).toInt(&ok, 16);
        if (!ok) {
            break;
        }
        ret.replace(ucPos, reg.matchedLength(), QChar(uc));
    }
    return ret;
}

void RDxfServices::autoFixLinetypePattern(RLinetypePattern& pattern) {
//    if (metric) {
//        return;
//    }

    RLinetypePattern* pat = RLinetypeListImperial::get(pattern.getName());
    if (pat==NULL) {
        return;
    }

    // pattern appears to be metric even though it's in an imperial definition or drawing file:
    if (pattern.getPatternLength()>pat->getPatternLength()*(25.4/2) || pattern.getName().startsWith("ACAD_ISO")) {
        pattern.setMetric(true);
    }
}
