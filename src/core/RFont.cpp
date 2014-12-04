/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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

QPainterPath RFont::getGlyph(const QChar& ch, bool draft) const {
    if (draft && glyphDraftMap.contains(ch)) {
        return glyphDraftMap.value(ch);
    }

    if (glyphMap.contains(ch)) {
        return glyphMap.value(ch);
    }

    return QPainterPath();
}

QPainterPath RFont::getShape(const QString& name) const {
    if (shapeMap.contains(name)) {
        return shapeMap.value(name);
    }
    if (name.length()==1 && glyphMap.contains(name.at(0))) {
        return glyphMap.value(name.at(0));
    }
    return QPainterPath();
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
            }
        }

        // found glyph definition:
        else if (line.at(0)=='[') {
            // uniode character:
            QChar ch;
            QString shapeName;

            // read unicode:
            QRegExp rx("\\[([0-9A-Fa-f]{4,4})\\]\\s*(.*)?");
            rx.indexIn(line);
            //QString cap = regexp.cap();
            if (rx.captureCount()>0) {
                int uCode = rx.cap(1).toInt(0, 16);
                ch = QChar(uCode);
                if (rx.captureCount()>1) {
                    shapeName = rx.cap(2);
                    shapeName = shapeName.trimmed();
                    //qDebug() << "shapeName: " << shapeName;
                }
            }

            // read UTF8 (qcad 1 compatibility)
            else if (line.indexOf(']')>=3) {
                int i = line.indexOf(']');
                QString mid = line.mid(1, i-1);
                ch = QString::fromUtf8(mid.toLatin1()).at(0);
            }

            // read normal ascii character:
            else {
                ch = line.at(1);
            }

            // create new glyph:
            QPainterPath glyph;
            QPainterPath glyphDraft;
            RVector pos = RVector::invalid;

            // read glyph definition:
            QString coordsStr;
            QStringList coords;
            bool containsArcs = false;
            do {
                line = ts.readLine();

                if (!line.isEmpty()) {
                    coordsStr = line.right(line.length()-2);
                    coords = coordsStr.split(',');

                    // Line:
                    if (line.at(0)=='L' && coords.size()==4) {
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
                        pos = endPoint;
                    }

                    // Arc:
                    else if (line.at(0)=='A' && coords.size()==5) {
                        containsArcs = true;
                        double cx = coords.at(0).toDouble()*scale;
                        double cy = coords.at(1).toDouble()*scale;
                        double r = coords.at(2).toDouble()*scale;
                        double a1 = coords.at(3).toDouble();
                        double a2 = coords.at(4).toDouble();
                        bool reversed = (line.at(1)=='R');

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

                        glyph.arcTo(cx-r, cy-r,
                                    2*r, 2*r,
                                    RMath::rad2deg(arc.getStartAngle()),
                                    RMath::rad2deg(arc.getSweep())
                        );

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


