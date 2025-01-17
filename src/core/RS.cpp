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
#include <QtGlobal>

#if QT_VERSION < 0x050000
#include <QTextDocument>
#endif

#if QT_VERSION < 0x060000
#include <QTextCodec>
#include <QDesktopWidget>
#endif

#if QT_VERSION >= 0x060000
#include <QStringDecoder>
#endif

#if QT_VERSION >= 0x050300
#include <QPageSize>
#endif

#include "RGlobal.h"
#include "RLinetype.h"
#include "RLineweight.h"
#include "RPropertyAttributes.h"
#include "RSettings.h"
#include "RVector.h"

const double RS::PointTolerance = 1.0e-9;
const double RS::AngleTolerance = 1.0e-9;

#if QT_VERSION >= 0x060000
    const Qt::MouseButton RS::MiddleButton = Qt::MiddleButton;
    const QPageLayout::Orientation RS::Portrait = QPageLayout::Portrait;
    const QPageLayout::Orientation RS::Landscape = QPageLayout::Landscape;
#else
    const Qt::MouseButton RS::MiddleButton = Qt::MidButton;
    const QPrinter::Orientation RS::Portrait = QPrinter::Portrait;
    const QPrinter::Orientation RS::Landscape = QPrinter::Landscape;
#endif

/**
 * \return True if the two values are considered to be equal.
 * \param noTolerance True strict comparison of doubles.
 */
bool RS::compare(const QVariant& v1, const QVariant& v2, bool noTolerance) {
    // 20120609: tolerance when comparing doubles (property editor)
    // 20140513: handle basic types since Qt 5 converts double, bool, int to line type
    switch (v1.type()) {
    case QVariant::Double:
        if (noTolerance) {
            if (v2.type()==QVariant::Double) {
                return v1.toDouble() == v2.toDouble();
            }
            else if (v2.type()==QVariant::Int) {
                return v1.toDouble() == (double)v2.toInt();
            }
        }
        else {
            if (v2.type()==QVariant::Double) {
                return fabs(v1.toDouble() - v2.toDouble()) < RS::PointTolerance;
            }
            else if (v2.type()==QVariant::Int) {
                return fabs(v1.toDouble() - v2.toInt()) < RS::PointTolerance;
            }
        }
        break;

    case QVariant::Int:
        if (noTolerance) {
            if (v2.type()==QVariant::Int) {
                return v1.toInt()==v2.toInt();
            }
            else if (v2.type()==QVariant::Double) {
                return (double)v1.toInt() == v2.toDouble();
            }
        }
        else {
            if (v2.type()==QVariant::Int) {
                return v1.toInt()==v2.toInt();
            }
            else if (v2.type()==QVariant::Double) {
                return fabs(v1.toInt() - v2.toDouble()) < RS::PointTolerance;
            }
        }
        break;

    case QVariant::Bool:
        if (v2.type()==QVariant::Bool) {
            return v1.toBool()==v2.toBool();
        }
        break;

    case QVariant::UInt:
        if (v2.type()==QVariant::UInt) {
            return v1.toUInt()==v2.toUInt();
        }
        break;

    case QVariant::LongLong:
        if (v2.type()==QVariant::LongLong) {
            return v1.toLongLong()==v2.toLongLong();
        }
        break;

    case QVariant::ULongLong:
        if (v2.type()==QVariant::ULongLong) {
            return v1.toULongLong()==v2.toULongLong();
        }
        break;

    case QVariant::String:
        if (v2.type()==QVariant::String) {
            return v1.toString()==v2.toString();
        }
        break;

    default:
        if (v1.canConvert<RColor> () && v2.canConvert<RColor> ()) {
            return v1.value<RColor> () == v2.value<RColor> ();
        }
        else if (v1.canConvert<RLinetype> () && v2.canConvert<RLinetype> ()) {
            return v1.value<RLinetype> () == v2.value<RLinetype> ();
        }
        else if (v1.canConvert<RLineweight::Lineweight> () && v2.canConvert<RLineweight::Lineweight> ()) {
            return v1.value<RLineweight::Lineweight> () == v2.value<RLineweight::Lineweight> ();
        }
        else if (v1.canConvert<QList<RVector> > () && v2.canConvert<QList<RVector> > ()) {
            return v1.value<QList<RVector> > () == v2.value<QList<RVector> > ();
        }
        else {
            return v1 == v2;
        }
        break;
    }
    return false;
}

bool RS::compare(const QPair<QVariant, RPropertyAttributes>& p1, const QPair<
                 QVariant, RPropertyAttributes>& p2, bool noTolerance) {
    return compare(p1.first, p2.first, noTolerance);
}

/**
 * \return List of all directories in subdirectory 'subDirectory' in
 * all possible QCAD directories.
 */
QStringList RS::getDirectoryList(const QString& subDirectory) {
    QStringList dirList;

    QString appDir = QCoreApplication::applicationDirPath();
    QFileInfo fi(appDir);
    if (fi.fileName() == "debug" || fi.fileName() == "release") {
        appDir = fi.absolutePath();
    }

#ifdef Q_OS_MAC
    // macOS app bundle:
    dirList.append(appDir + "/../Resources/" + subDirectory);
    dirList.append(appDir + "/../../../" + subDirectory);
    dirList.append(QDir::currentPath() + "/" + subDirectory);
#else
    dirList.append(appDir + "/" + subDirectory);
#endif

    /*
#ifdef Q_OS_MAC
    if (subDirectory!="library") {
#endif
        //local (application) directory has priority over other dirs:
        dirList.append(appDir + QDir::separator() + subDirectory);

 #ifdef Q_OS_LINUX
        QString appDirName = QSettings.applicationName();
        // Redhat style:
        dirList.append("/usr/share/" + appDirName + "/" + subDirectory);

        // SuSE style:
        dirList.append("/usr/X11R6/" + appDirName + "/" + subDirectory);

        dirList.append("/usr/X11R6/share/" + appDirName + "/" + subDirectory);
        dirList.append(QDir::homePath() + "/." + appDirName + "/" + subDirectory);
#endif

#ifdef Q_OS_MAC
    }
#endif
    */

    // add a path to users home (config dir) to be used to extend pattern, linetypes, etc.
    dirList.append(RSettings::getPath() + "/" + subDirectory);
    dirList.append(RSettings::getDataLocation() + "/" + subDirectory);

    QStringList ret;
    for (int i=0; i<dirList.size(); i++) {
        QFileInfo fi(dirList.at(i));
        QString dir = fi.canonicalFilePath();
        if (fi.isDir() && !ret.contains(dir)) {
            ret.append(dir);
        }
    }

    return ret;
}

/**
 * Searches for files in various directories under the given
 * subdirectory which match the given file extension.
 *
 * \return List of the absolute paths of the files found.
 */
QStringList RS::getFileList(const QString& subDirectory, const QString& fileExtension) {

    QStringList dirList = getDirectoryList(subDirectory);

    QStringList fileList;
    QString path;
    QDir dir;

    for (int i=0; i<dirList.size(); ++i) {
        path = dirList.at(i);
        dir = QDir(path);

        if (dir.exists() && dir.isReadable()) {
            // this seems to be case insensitive by default:
            QStringList files =
                dir.entryList(QStringList("*." + fileExtension), QDir::Files|QDir::Readable);
            for (int k=0; k<files.size(); ++k) {
                QString f = path + QDir::separator() + files.at(k);
                fileList.append(f);
            }
        }
    }

    return fileList;
}

/**
 * \return A list of absolute paths to all font files found.
 */
QStringList RS::getFontList() {
    //return getFileList("fonts", "cxf");

    QStringList ret = getFileList("fonts", "cxf");
    ret.append(getFileList("fonts", "shx"));
    return ret;
}

/**
 * \return A list of absolute paths to all pattern files found.
 */
QStringList RS::getPatternList(bool metric) {
    if (metric) {
        return getFileList("patterns/metric", "pat");
    }
    else {
        return getFileList("patterns/imperial", "pat");
    }
}

/**
 * \return A list of absolute paths to all pattern files found.
 */
QStringList RS::getLinetypeList(bool metric) {
    if (metric) {
        return getFileList("linetypes/metric", "lin");
    }
    else {
        return getFileList("linetypes/imperial", "lin");
    }
}

/**
 * Alphanumerical sorting.
 */
QStringList RS::sortAlphanumerical(const QStringList& list) {
    QStringList ret = list;

    std::sort(
        ret.begin(),
        ret.end(),
        RS::lessThanAlphanumerical
    );

    return ret;
}

/**
 * \return List of strings containing either only numbers or non-numbers.
 * E.g. "abc123" -> "abc", "123"
 */
QStringList RS::compareChunkify(const QString& s) {
    static QRegularExpression rx("0x[0-9a-fA-F]*");

    QStringList tz;
    bool nummerical = false;
    QString sLocal;

    if (s.startsWith("0x")) {
        QRegularExpressionMatch match;
        if (RS::indexIn(rx, match, s)==0) {
            int len = RS::matchedLength(rx, match);
            sLocal = s.mid(len);
            nummerical = true;
            tz.append(s.left(len));
        }
    }
    else {
        sLocal = s;
    }

    for (int i=0; i<sLocal.length(); i++) {
        QChar c = sLocal.at(i);
        bool n = c.isDigit() || c=='.';
        if (n!=nummerical || i==0) {
            tz.append(c);
            nummerical = n;
        }
        else {
            tz.last().append(c);
        }
    }

    return tz;
}

/**
 * Alphanumerical, locale aware, case insensitive comparison.
 */
int RS::compareAlphanumerical(const QString& s1, const QString& s2) {
    // note: we deliberately do not use QCollator here (buggy, crashes under Linux):
    QStringList aa = compareChunkify(s1.toLower());
    QStringList bb = compareChunkify(s2.toLower());

    for (int x = 0; x<aa.length() && x < bb.length(); x++) {
        if (aa[x] != bb[x]) {
            bool ok1, ok2;
            float c, d;
            if (x==0 && aa[0].startsWith("0x") && bb[0].startsWith("0x")) {
                c = aa[0].mid(2).toInt(&ok1, 16);
                d = bb[0].mid(2).toInt(&ok2, 16);
            }
            else {
                c = aa[x].toFloat(&ok1);
                d = bb[x].toFloat(&ok2);
            }
            if (ok1 && ok2) {
                if (c-d<0.0) {
                    return -1;
                }
                if (c-d>0.0) {
                    return 1;
                }
                return 0;
            }
            else {
                return aa[x].localeAwareCompare(bb[x]);
            }
        }
    }

    return aa.length() - bb.length();
}

bool RS::lessThanAlphanumerical(const QString& s1, const QString& s2) {
    return RS::compareAlphanumerical(s1, s2)<0;
}

int RS::getPageSizeId(const QString& name) {
#if QT_VERSION >= 0x050300
    if (name=="A0" || name=="ISO A0") {
        return QPageSize::A0;
    }
    else if (name=="A1" || name=="ISO A1") {
        return QPageSize::A1;
    }
    else if (name=="A2" || name=="ISO A2") {
        return QPageSize::A2;
    }
    else if (name=="A3" || name=="ISO A3") {
        return QPageSize::A3;
    }
    else if (name=="A4" || name=="ISO A4") {
        return QPageSize::A4;
    }
    else if (name=="A5" || name=="ISO A5") {
        return QPageSize::A5;
    }
    else if (name=="A6" || name=="ISO A6") {
        return QPageSize::A6;
    }
    else if (name=="A7" || name=="ISO A7") {
        return QPageSize::A7;
    }
    else if (name=="A8" || name=="ISO A8") {
        return QPageSize::A8;
    }
    else if (name=="A9" || name=="ISO A9") {
        return QPageSize::A9;
    }
    else if (name=="A10" || name=="ISO A10") {
        return QPageSize::Custom;
    }

    else if (name=="B0" || name=="ISO B0") {
        return QPageSize::B0;
    }
    else if (name=="B1" || name=="ISO B1") {
        return QPageSize::B1;
    }
    else if (name=="B2" || name=="ISO B2") {
        return QPageSize::B2;
    }
    else if (name=="B3" || name=="ISO B3") {
        return QPageSize::B3;
    }
    else if (name=="B4" || name=="ISO B4") {
        return QPageSize::B4;
    }
    else if (name=="B5" || name=="ISO B5") {
        return QPageSize::B5;
    }
    else if (name=="B6" || name=="ISO B6") {
        return QPageSize::B6;
    }
    else if (name=="B7" || name=="ISO B7") {
        return QPageSize::B7;
    }
    else if (name=="B8" || name=="ISO B8") {
        return QPageSize::B8;
    }
    else if (name=="B9" || name=="ISO B9") {
        return QPageSize::B9;
    }
    else if (name=="B10" || name=="ISO B10") {
        return QPageSize::B10;
    }

    else if (name=="C0" || name=="ISO C0") {
        return QPageSize::Custom;
    }
    else if (name=="C1" || name=="ISO C1") {
        return QPageSize::Custom;
    }
    else if (name=="C2" || name=="ISO C2") {
        return QPageSize::Custom;
    }
    else if (name=="C3" || name=="ISO C3") {
        return QPageSize::Custom;
    }
    else if (name=="C4" || name=="ISO C4") {
        return QPageSize::Custom;
    }
    else if (name=="C5" || name=="ISO C5") {
        return QPageSize::Custom;
    }
    else if (name=="C6" || name=="ISO C6") {
        return QPageSize::Custom;
    }
    else if (name=="C7" || name=="ISO C7") {
        return QPageSize::Custom;
    }
    else if (name=="C8" || name=="ISO C8") {
        return QPageSize::Custom;
    }
    else if (name=="C9" || name=="ISO C9") {
        return QPageSize::Custom;
    }
    else if (name=="C10" || name=="ISO C10") {
        return QPageSize::Custom;
    }

    else if (name=="DIN 476 4A0") {
        return QPageSize::Custom;
    }
    else if (name=="DIN 476 2A0") {
        return QPageSize::Custom;
    }

    // JIS:
    else if (name=="JIS B0") {
        return QPageSize::Custom;
    }
    else if (name=="JIS B1") {
        return QPageSize::Custom;
    }
    else if (name=="JIS B2") {
        return QPageSize::Custom;
    }
    else if (name=="JIS B3") {
        return QPageSize::Custom;
    }
    else if (name=="JIS B4") {
        return QPageSize::Custom;
    }
    else if (name=="JIS B5") {
        return QPageSize::Custom;
    }
    else if (name=="JIS B6") {
        return QPageSize::Custom;
    }
    else if (name=="JIS B7") {
        return QPageSize::Custom;
    }
    else if (name=="JIS B8") {
        return QPageSize::Custom;
    }
    else if (name=="JIS B9") {
        return QPageSize::Custom;
    }
    else if (name=="JIS B10") {
        return QPageSize::Custom;
    }
    else if (name=="JIS B11") {
        return QPageSize::Custom;
    }
    else if (name=="JIS B12") {
        return QPageSize::Custom;
    }

    // 7.5" x 10"
    else if (name=="Executive") {
        return QPageSize::Executive;
    }
    // 8.5" x 14"
    else if (name=="Legal") {
        return QPageSize::Legal;
    }
    // 8.5" x 11"
    else if (name=="ANSI A" || name=="Letter" || name=="ANSI A (Letter)") {
        return QPageSize::Letter;
    }
    // 11" x 17"
    else if (name=="ANSI B" || name=="Ledger" || name=="Tabloid" || name=="ANSI B (Ledger, Tabloid)") {
        return QPageSize::Tabloid;
    }
    // 13" x 19"
    else if (name=="Super B") {
        return QPageSize::Custom;
    }
    // 17" x 22"
    else if (name=="ANSI C") {
        return QPageSize::Custom;
    }
    // 22" x 34"
    else if (name=="ANSI D") {
        return QPageSize::Custom;
    }
    // 34" x 44"
    else if (name=="ANSI E") {
        return QPageSize::Custom;
    }

    // US Architectural:
    // 9" x 12"
    else if (name=="Arch A") {
        return QPageSize::Custom;
    }
    // 12" x 18"
    else if (name=="Arch B") {
        return QPageSize::Custom;
    }
    // 18" x 24"
    else if (name=="Arch C") {
        return QPageSize::Custom;
    }
    // 24" x 36"
    else if (name=="Arch D") {
        return QPageSize::Custom;
    }
    // 36" x 48"
    else if (name=="Arch E") {
        return QPageSize::Custom;
    }
    // 30" x 42"
    else if (name=="Arch E1") {
        return QPageSize::Custom;
    }
    // 26" x 38"
    else if (name=="Arch E2") {
        return QPageSize::Custom;
    }
    // 27" x 39"
    else if (name=="Arch E3") {
        return QPageSize::Custom;
    }

    // Others:
    // Folio / Foolscap:
    else if (name=="F4" || name=="Folio" || name=="Foolscap" || name=="F4 (Folio, Foolscap)") {
        return QPageSize::Folio;
    }
    // U.S. Common 10 Envelope:
    else if (name=="Common 10 Envelope") {
        return QPageSize::Comm10E;
    }
    // DLE Envelope:
    else if (name=="DLE Envelope") {
        return QPageSize::DLE;
    }

    else {
        return QPageSize::Custom;
    }
#else
    return -1;
#endif
}

QSizeF RS::getPageSize(const QString& name) {
    if (name=="A4" || name=="ISO A4") {
        return QSizeF(210,  297);
    }

    else if (name=="ISO A0" || name=="A0") {
        return QSizeF(841, 1189);
    }
    else if (name=="ISO A1" || name=="A1") {
        return QSizeF(594, 841);
    }
    else if (name=="ISO A2" || name=="A2") {
        return QSizeF(420, 594);
    }
    else if (name=="ISO A3" || name=="A3") {
        return QSizeF(297, 420);
    }
    else if (name=="ISO A4" || name=="A4") {
        return QSizeF(210, 297);
    }
    else if (name=="ISO A5" || name=="A5") {
        return QSizeF(148, 210);
    }
    else if (name=="ISO A6" || name=="A6") {
        return QSizeF(105, 148);
    }
    else if (name=="ISO A7" || name=="A7") {
        return QSizeF(74, 105);
    }
    else if (name=="ISO A8" || name=="A8") {
        return QSizeF(52, 74);
    }
    else if (name=="ISO A9" || name=="A9") {
        return QSizeF(37, 52);
    }
    else if (name=="ISO A10" || name=="A10") {
        return QSizeF(26, 37);
    }

    else if (name=="ISO B0" || name=="B0") {
        return QSizeF(1000, 1414);
    }
    else if (name=="ISO B1" || name=="B1") {
        return QSizeF(707, 1000);
    }
    else if (name=="ISO B2" || name=="B2") {
        return QSizeF(500, 707);
    }
    else if (name=="ISO B3" || name=="B3") {
        return QSizeF(353, 500);
    }
    else if (name=="ISO B4" || name=="B4") {
        return QSizeF(250, 353);
    }
    else if (name=="ISO B5" || name=="B5") {
        return QSizeF(176, 250);
    }
    else if (name=="ISO B6" || name=="B6") {
        return QSizeF(125, 176);
    }
    else if (name=="ISO B7" || name=="B7") {
        return QSizeF(88, 125);
    }
    else if (name=="ISO B8" || name=="B8") {
        return QSizeF(62, 88);
    }
    else if (name=="ISO B9" || name=="B9") {
        return QSizeF(44, 62);
    }
    else if (name=="ISO B10" || name=="B10") {
        return QSizeF(31, 44);
    }

    else if (name=="ISO C0" || name=="C0") {
        return QSizeF(917, 1297);
    }
    else if (name=="ISO C1" || name=="C1") {
        return QSizeF(648, 917);
    }
    else if (name=="ISO C2" || name=="C2") {
        return QSizeF(458, 648);
    }
    else if (name=="ISO C3" || name=="C3") {
        return QSizeF(324, 458);
    }
    else if (name=="ISO C4" || name=="C4") {
        return QSizeF(229, 324);
    }
    else if (name=="ISO C5" || name=="C5") {
        return QSizeF(162, 229);
    }
    else if (name=="ISO C6" || name=="C6") {
        return QSizeF(114, 162);
    }
    else if (name=="ISO C7" || name=="C7") {
        return QSizeF(81, 114);
    }
    else if (name=="ISO C8" || name=="C8") {
        return QSizeF(57, 81);
    }
    else if (name=="ISO C9" || name=="C9") {
        return QSizeF(40, 57);
    }
    else if (name=="ISO C10" || name=="C10") {
        return QSizeF(28, 40);
    }

    else if (name=="DIN 476 4A0") {
        return QSizeF(1682, 2378);
    }
    else if (name=="DIN 476 2A0") {
        return QSizeF(1189, 1682);
    }

    // JIS:
    else if (name=="JIS B0") {
        return QSizeF(1030, 1456);
    }
    else if (name=="JIS B1") {
        return QSizeF(728, 1030);
    }
    else if (name=="JIS B2") {
        return QSizeF(515, 728);
    }
    else if (name=="JIS B3") {
        return QSizeF(364, 515);
    }
    else if (name=="JIS B4") {
        return QSizeF(257, 364);
    }
    else if (name=="JIS B5") {
        return QSizeF(182, 257);
    }
    else if (name=="JIS B6") {
        return QSizeF(128, 182);
    }
    else if (name=="JIS B7") {
        return QSizeF(91, 128);
    }
    else if (name=="JIS B8") {
        return QSizeF(64, 91);
    }
    else if (name=="JIS B9") {
        return QSizeF(45, 64);
    }
    else if (name=="JIS B10") {
        return QSizeF(32, 45);
    }
    else if (name=="JIS B11") {
        return QSizeF(22, 32);
    }
    else if (name=="JIS B12") {
        return QSizeF(16, 22);
    }

    // 7.5" x 10"
    else if (name=="Executive") {
        return QSizeF(190.5, 254);
    }
    // 8.5" x 14"
    else if (name=="Legal") {
        return QSizeF(215.9, 355.6);
    }
    // 8.5" x 11"
    else if (name=="ANSI A" || name=="Letter" || name=="ANSI A (Letter)") {
        return QSizeF(215.9, 279.4);
    }
    // 11" x 17"
    else if (name=="ANSI B" || name=="Ledger" || name=="Tabloid" || name=="ANSI B (Ledger, Tabloid)") {
        return QSizeF(279.4, 431.8);
    }
    // 13" x 19"
    else if (name=="Super B") {
        return QSizeF(330.2, 482.6);
    }
    // 17" x 22"
    else if (name=="ANSI C") {
        return QSizeF(431.8, 558.8);
    }
    // 22" x 34"
    else if (name=="ANSI D") {
        return QSizeF(558.8, 863.6);
    }
    // 34" x 44"
    else if (name=="ANSI E") {
        return QSizeF(863.6, 1117.6);
    }

    // US Architectural:
    // 9" x 12"
    else if (name=="Arch A") {
        return QSizeF(228.6, 304.8);
    }
    // 12" x 18"
    else if (name=="Arch B") {
        return QSizeF(304.8, 457.2);
    }
    // 18" x 24"
    else if (name=="Arch C") {
        return QSizeF(457.2, 609.6);
    }
    // 24" x 36"
    else if (name=="Arch D") {
        return QSizeF(609.6, 914.4);
    }
    // 36" x 48"
    else if (name=="Arch E") {
        return QSizeF(914.4, 1219.2);
    }
    // 30" x 42"
    else if (name=="Arch E1") {
        return QSizeF(762, 1066.8);
    }
    // 26" x 38"
    else if (name=="Arch E2") {
        return QSizeF(660.4, 965.2);
    }
    // 27" x 39"
    else if (name=="Arch E3") {
        return QSizeF(685.8, 990.6);
    }

    // Others:
    // Folio / Foolscap:
    else if (name=="F4 (Folio, Foolscap)") {
        return QSizeF(210, 330);
    }
    // U.S. Common 10 Envelope:
    else if (name=="Common 10 Envelope") {
        return QSizeF(105, 241);
    }
    // DLE Envelope:
    else if (name=="DLE Envelope") {
        return QSizeF(110, 220);
    }

    return QSizeF();
}

bool RS::exactMatch(const QRegularExpression& rx, const QString& string) {
#if QT_VERSION >= 0x050000
    QString pat = rx.pattern();
    pat = "^" + pat + "$";
    QRegularExpression rxExact(pat);
    return rxExact.match(string).hasMatch();
#else
    return rx.exactMatch(string);
#endif
}

bool RS::exactMatch(const QRegularExpression& rx, QRegularExpressionMatch& match, const QString& string) {
#if QT_VERSION >= 0x050000
    QString pat = rx.pattern();
    pat = "^" + pat + "$";
    QRegularExpression rxExact(pat);
    match = rxExact.match(string);
    return match.hasMatch();
#else
    return rx.exactMatch(string);
#endif
}

bool RS::exactMatch(const QString& rxStr, const QString& string) {
    QRegularExpression rx("^" + rxStr + "$");
#if QT_VERSION >= 0x050000
    return rx.match(string).hasMatch();
#else
    return rx.exactMatch(string);
#endif
}

int RS::indexIn(const QRegularExpression& rx, QRegularExpressionMatch& match, const QString& string, int from) {
#if QT_VERSION >= 0x050000
    return (int)string.indexOf(rx, from, &match);
#else
    return rx.indexIn(string, from);
#endif
}

QString RS::captured(const QRegularExpression& rx, const QRegularExpressionMatch& match, int nth) {
#if QT_VERSION >= 0x050000
    return match.captured(nth);
#else
    return rx.cap(nth);
#endif
}

int RS::matchedLength(const QRegularExpression& rx, const QRegularExpressionMatch& match) {
#if QT_VERSION >= 0x050000
    return (int)match.capturedLength();
#else
    return rx.matchedLength();
#endif
}

QRegularExpression RS::createRegEpCI(const QString& str, bool regExp2) {
#if QT_VERSION >= 0x050000
    return QRegularExpression(str, QRegularExpression::CaseInsensitiveOption);
#else
    if (regExp2) {
        return QRegExp(str, Qt::CaseInsensitive, QRegExp::RegExp2);
    }
    else {
        return QRegExp(str, Qt::CaseInsensitive);
    }
#endif
}

void RS::setUtf8Codec(QTextStream& ts) {
#if QT_VERSION >= 0x060000
    ts.setEncoding(QStringConverter::Utf8);
#else
    ts.setCodec("UTF-8");
#endif
}

QString RS::escape(const QString& plain) {
#if QT_VERSION >= 0x050F00
    return plain.toHtmlEscaped();
#else
    return Qt::escape(plain);
#endif
}

int RS::getScreenCount() {
#if QT_VERSION >= 0x060000
    return (int)QGuiApplication::screens().count();
#else
    return (int)QApplication::desktop()->screenCount();
#endif
}

QSize RS::getAvailableGeometry(int screen) {
#if QT_VERSION >= 0x060000
    QList<QScreen*> screens = QGuiApplication::screens();
    if (screen < screens.count() && screens[screen]!=NULL) {
        return screens[screen]->availableSize();
    }
    return QSize();
#else
    return QApplication::desktop()->availableGeometry(screen).size();
#endif
}

QString RS::convert(const QByteArray& str, const QString& codecName) {
#if QT_VERSION >= 0x060000
    std::optional<QStringConverter::Encoding> encoding = QStringConverter::encodingForName(codecName.toLatin1());
    if (!encoding.has_value()) {
        qWarning() << "RS::convert: unsupported text codec: " << codecName;
        return str;
    }
    auto enc = QStringDecoder(encoding.value());
    return enc(QByteArray(str));
#else
    // get the text codec:
    QTextCodec* codec = QTextCodec::codecForName(codecName.toLatin1());
    if (codec==NULL) {
        qWarning() << "RDxfImporter::addMText: unsupported text codec: " << codecName;
        return str;
    }
    else {
        return codec->toUnicode(str);
    }
#endif
}
