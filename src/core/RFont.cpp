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
#include <QStringList>
#include <QTextCodec>
#include <QTextStream>

#include "RArc.h"
#include "RLine.h"
#include "RFont.h"
#include "RS.h"
#include "RSpline.h"


/**
 * Constructor.
 */
RFont::RFont() :
    loaded(false),
    letterSpacing(3.0),
    wordSpacing(6.75),
    lineSpacingFactor(1.0) {
}


/**
 * Constructor.
 */
RFont::RFont(const QString& fileName) :
    fileName(fileName),
    loaded(false),
    letterSpacing(3.0),
    wordSpacing(6.75),
    lineSpacingFactor(1.0) {
}


RFont::~RFont() {
}

RPainterPath RFont::getGlyph(const QChar& ch, bool draft) const {
    if (draft && glyphDraftMap.contains(ch)) {
        return glyphDraftMap.value(ch);
    }

    if (glyphMap.contains(ch)) {
        return glyphMap.value(ch);
    }

    RPainterPath ret;
    ret.setValid(false);
    return ret;
}

RPainterPath RFont::getShape(const QString& name) const {
    if (shapeMap.contains(name)) {
        return shapeMap.value(name);
    }
    if (name.length()==1 && glyphMap.contains(name.at(0))) {
        return glyphMap.value(name.at(0));
    }

    RPainterPath ret;
    ret.setValid(false);
    return ret;
}

QString RFont::getShapeName(const QChar& ch) const {
    if (numNameMap.contains(ch)) {
        return numNameMap.value(ch);
    }
    return QString();
}

/**
 * Loads the font into memory.
 *
 * \retval true font was already loaded or is loaded now.
 * \retval false font could not be loaded.
 */
bool RFont::load() {
    if (loaded) {
        return true;
    }

    QString path;

    // Search for the appropriate font if we only have the name of the font:
    if (!fileName.toLower().endsWith(".cxf")) {
        QStringList fonts = RS::getFontList();
        for (int i=0; i<fonts.size(); ++i) {
            QString p = fonts.at(i);
            if (QFileInfo(p).completeBaseName().toLower()==fileName.toLower()) {
                path = p;
                break;
            }
        }
    }

    // We have the full path of the font:
    else {
        path = fileName;
    }

    // No font paths found:
    if (path.isEmpty()) {
        qWarning() << "RFont::load: font not available.";
        return false;
    }

    // Open cxf file:
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() <<  "RFont::load: Cannot open font file: " <<  path;
        return false;
    }

    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    QString line;
    int lineCount = 0;
    double scale = 1.0;

    // Read line by line until we find a new letter:
    while (!ts.atEnd()) {
        line = ts.readLine();
        lineCount++;

        if (line.isEmpty()) {
            continue;
        }

        // found font meta data:
        if (line.at(0)=='#') {
            QStringList lst = line.right(line.length()-1).split(':');
            QStringList::Iterator it = lst.begin();

            QString identifier;
            QString value;

            if (it!=lst.end()) {
                identifier = (*it).trimmed();
                it++;
                if (it!=lst.end()) {
                    value = (*it).trimmed();
                }
            }

            if (identifier.toLower()=="letterspacing") {
                letterSpacing = value.toDouble();
            } else if (identifier.toLower()=="wordspacing") {
                wordSpacing = value.toDouble();
            } else if (identifier.toLower()=="linespacingfactor") {
                lineSpacingFactor = value.toDouble();
            } else if (identifier.toLower()=="scale") {
                scale = value.toDouble();
            } else if (identifier.toLower()=="author") {
                authors.append(value);
            } else if (identifier.toLower()=="name") {
                names.append(value);
            } else if (identifier.toLower()=="encoding") {
                ts.setCodec(QTextCodec::codecForName(value.toUtf8()));
                encoding = value;
            } else if (identifier.toLower()=="auxiliarylines") {
                QStringList strs = value.split(",");
                for (int i=0; i<strs.length(); i++) {
                    bool ok;
                    double v = strs[i].toDouble(&ok);
                    if (ok) {
                        auxLinePositions.append(v);
                    }
                }
            }
        }

        // found glyph definition:
        else if (line.at(0)=='[') {
            // uniode character:
            QChar ch;
            QString shapeName;

            // read unicode:
            QRegExp rx("\\[([0-9A-Fa-f]{4,4})\\]\\s*(.*)?");
            if (rx.indexIn(line)==0 && rx.captureCount()>0) {
                int uCode = rx.cap(1).toInt(0, 16);
                ch = QChar(uCode);
                if (rx.captureCount()>1) {
                    shapeName = rx.cap(2);
                    shapeName = shapeName.trimmed();
                    //qDebug() << "shapeName: " << shapeName;
                }
            }

            else {
                // skip line:
                qDebug() << "skip";
                continue;
            }

            // create new glyph:
            RPainterPath glyph;
            RPainterPath glyphDraft;
            RVector pos = RVector::invalid;

            // read glyph definition:
            QString coordsStr;
            QStringList coords;
            bool containsArcs = false;
            do {
                line = ts.readLine();

                if (!line.isEmpty()) {
                    QRegExp rx("(L|A|AR|PL|PLC) ([0-9,+-\\.e]*)");
                    if (rx.indexIn(line)==-1) {
                        continue;
                    }
                    QString code = rx.cap(1);
                    //qDebug() << "code:" << code;
                    coordsStr = rx.cap(2);
                    //qDebug() << "coords:" << coordsStr;
                    //coordsStr = line.right(line.length()-2);
                    coords = coordsStr.split(',');

                    // Polyline:
                    if ((code=="PL" || code=="PLC") && coords.length()>1) {
                        RPolyline pl;
                        for (int i=0; i<coords.length()-2; i+=3) {
                            double x = coords[i].toDouble()*scale;
                            double y = coords[i+1].toDouble()*scale;
                            double b = coords[i+2].toDouble();
                            //qDebug() << "vertex:" << x << y << b;
                            pl.appendVertex(RVector(x,y), b);
                        }
                        if (code=="PLC") {
                            pl.setClosed(true);
                        }
                        RVector startPoint = pl.getStartPoint();
                        if (!pos.isValid() || !pos.equalsFuzzy(startPoint)) {
                            glyph.moveTo(startPoint.x, startPoint.y);
                            glyphDraft.moveTo(startPoint.x, startPoint.y);
                        }
                        glyph.addPolyline(pl);
                        glyphDraft.addPolyline(pl);
                        glyph.addOriginalShape(QSharedPointer<RShape>(new RPolyline(pl)));
                        //qDebug() << "pl" << pl;
                        pos = pl.getEndPoint();
                    }

                    // Line:
                    else if (code=="L" && coords.length()==4) {
                        RVector startPoint(
                                    coords.at(0).toDouble()*scale,
                                    coords.at(1).toDouble()*scale
                        );
                        RVector endPoint(
                                    coords.at(2).toDouble()*scale,
                                    coords.at(3).toDouble()*scale
                        );

                        if (!pos.isValid() || !pos.equalsFuzzy(startPoint)) {
                            glyph.moveTo(startPoint.x, startPoint.y);
                            glyphDraft.moveTo(startPoint.x, startPoint.y);
                        }
                        glyph.lineTo(endPoint.x, endPoint.y);
                        glyphDraft.lineTo(endPoint.x, endPoint.y);
                        glyph.addOriginalShape(QSharedPointer<RShape>(new RLine(startPoint, endPoint)));
                        pos = endPoint;
                    }

                    // Arc:
                    else if ((code=="A" || code=="AR") && coords.length()==5) {
                        containsArcs = true;
                        double cx = coords.at(0).toDouble()*scale;
                        double cy = coords.at(1).toDouble()*scale;
                        double r = coords.at(2).toDouble()*scale;
                        double a1 = coords.at(3).toDouble();
                        double a2 = coords.at(4).toDouble();
                        bool reversed = (code=="AR");

                        RArc arc(RVector(cx, cy), r,
                                 RMath::deg2rad(a1),
                                 RMath::deg2rad(a2),
                                 reversed
                        );

                        RVector startPoint = arc.getStartPoint();
                        RVector endPoint = arc.getEndPoint();

                        int sweep = qAbs(RMath::mround(RMath::rad2deg(arc.getSweep())));
                        double length = arc.getLength();
                        int steps = sweep / 45;
                        QList<RVector> midPoints;
                        for (int s=1; s<steps; s++) {
                            midPoints.append(arc.getPointsWithDistanceToEnd(length/steps*s, RS::FromStart).at(0));
                        }

                        arc.mirror(RLine(RVector(cx, cy), RVector(cx+1.0, cy)));

                        if (!pos.isValid() || !pos.equalsFuzzy(startPoint)) {
                            glyph.moveTo(startPoint.x, startPoint.y);
                            glyphDraft.moveTo(startPoint.x, startPoint.y);
                        }

                        RArc arc2 = arc;
                        arc2.mirror(RLine(RVector(cx, cy), RVector(cx+1.0, cy)));
                        QList<RSpline> splines = RSpline::createSplinesFromArc(arc2);
                        for (int i=0; i<splines.length(); i++) {
                            glyph.addSpline(splines[i]);
                        }

                        glyph.addOriginalShape(QSharedPointer<RShape>(new RArc(arc2)));

//                        glyph.arcTo(cx-r, cy-r,
//                                    2*r, 2*r,
//                                    RMath::rad2deg(arc.getStartAngle()),
//                                    RMath::rad2deg(arc.getSweep())
//                        );

                        // draft version of glyph: interpolated arcs:
                        for (int li=0; li<midPoints.size(); li++) {
                            glyphDraft.lineTo(midPoints.at(li).x, midPoints.at(li).y);
                        }
                        glyphDraft.lineTo(endPoint.x, endPoint.y);

                        pos = endPoint;
                    }
                }
            } while (!line.isEmpty());

            if (!shapeName.isEmpty() && shapeName.length()>1) {
                shapeMap.insert(shapeName, glyph);
                numNameMap.insert(ch, shapeName);
            }
            else {
                glyphMap.insert(ch, glyph);
            }
            if (containsArcs) {
                glyphDraftMap.insert(ch, glyphDraft);
            }
        }
    }

    file.close();
    loaded = true;

    return true;
}


