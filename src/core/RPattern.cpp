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
#include "RPattern.h"
#include "RS.h"
#include "RMemoryStorage.h"
#include "RDocument.h"
#include "RDocumentInterface.h"
#include "RFileImporter.h"
#include "RFileImporterRegistry.h"


/**
 * Loads all patterns in the given file into memory.
 */
QList<QPair<QString, RPattern*> > RPattern::loadAllFrom(const QString& fileName) {
    QList<QPair<QString, RPattern*> > ret;

    // Open pat file:
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() <<  "RPattern::loadAllFrom: Cannot open pat file: " <<  fileName;
        return ret;
    }

    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    QString line;
    RPattern* pattern = NULL;

    // Read line by line:
    while (!ts.atEnd()) {
        line = ts.readLine();

        // handle comments (;):
        int semi = line.indexOf(';');
        if (semi==0) {
            continue;
        }

        if (semi!=-1) {
            line = line.left(semi);
        }

        // skip empty lines:
        if (line.isEmpty()) {
            continue;
        }

        // name / description:
        if (line.at(0)=='*') {
            QRegExp rx("\\*([^,]*)(?:,\\s*(.*))?", Qt::CaseSensitive, QRegExp::RegExp2);
            rx.indexIn(line);
            QString name = rx.cap(1);
            QString description = rx.cap(2);
            pattern = new RPattern(name, description);
            ret.append(qMakePair(name, pattern));
            continue;
        }

        // pattern line definition:
        if (pattern!=NULL) {
            QStringList parts = line.split(',', QString::SkipEmptyParts);
            if (parts.length()<5) {
                // 20160906: silently ignore invalid lines:
                //qWarning() << "RPattern::loadAllFrom: ignoring line: " << line << " in pattern " << fileName;
                //delete pattern;
                //ret.removeLast();
                continue;
            }

            RPatternLine patternLine;
            patternLine.angle = RMath::deg2rad(parts.at(0).toDouble());
            patternLine.basePoint.x = parts.at(1).toDouble();
            patternLine.basePoint.y = parts.at(2).toDouble();
            patternLine.offset.x = parts.at(3).toDouble();
            patternLine.offset.y = parts.at(4).toDouble();

            for (int i=5; i<parts.length(); i++) {
                double dash = parts.at(i).toDouble();
//                if (dash>=0.0 && dash<RS::PointTolerance) {
//                    dash = 0.01;
//                }
                patternLine.dashes.append(dash);
            }

            pattern->patternLines.append(patternLine);
        }
    }

    return ret;
}


/**
 * Default constructor.
 */
RPattern::RPattern() {
}

/**
 * Constructor.
 */
RPattern::RPattern(const QString& name, const QString& description) :
    name(name), description(description) {
}

RPattern::~RPattern() {
}

bool RPattern::hasDots() const {
    for (int i=0; i<patternLines.length(); ++i) {
        if (patternLines[i].hasDots()) {
            return true;
        }
    }
    return false;
}

/**
 * Scales the pattern by the given factor.
 */
void RPattern::scale(double f) {
    for (int i=0; i<patternLines.length(); ++i) {
        patternLines[i].scale(f);
    }
}

/**
 * Rotates the pattern by the given factor.
 */
void RPattern::rotate(double a) {
    for (int i=0; i<patternLines.length(); ++i) {
        patternLines[i].rotate(a);
    }
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, const RPattern& p) {
    QList<RPatternLine> patternLines = p.getPatternLines();
    dbg.nospace() << "RPattern(\n";
    for (int i=0; i<patternLines.length(); ++i) {
        dbg.nospace() << "\t" << patternLines[i];
    }
    dbg.nospace() << ")";

    return dbg.space();
}
