/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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
#include "RColor.h"
#include "RGlobal.h"
#include "RLinetype.h"
#include "RLineweight.h"
#include "RPropertyAttributes.h"
#include "RSettings.h"
#include "RVector.h"

const double RS::PointTolerance = 1.0e-9;
const double RS::AngleTolerance = 1.0e-9;

bool RS::compare(const QVariant& v1, const QVariant& v2) {
    // 20120609: tolerance when comparing doubles (property editor)
    // 20140513: handle basic types since Qt 5 thinks it can convert double, bool, int to line type
    if (v1.type()==QVariant::Double && v2.type()==QVariant::Double) {
        return fabs(v1.toDouble() - v2.toDouble()) < RS::PointTolerance;
    }
    if (v1.type()==QVariant::Bool && v2.type()==QVariant::Bool) {
        return v1.toBool()==v2.toBool();
    }
    if (v1.type()==QVariant::Int && v2.type()==QVariant::Int) {
        return v1.toInt()==v2.toInt();
    }
    if (v1.type()==QVariant::UInt && v2.type()==QVariant::UInt) {
        return v1.toUInt()==v2.toUInt();
    }
    if (v1.type()==QVariant::LongLong && v2.type()==QVariant::LongLong) {
        return v1.toLongLong()==v2.toLongLong();
    }
    if (v1.type()==QVariant::ULongLong && v2.type()==QVariant::ULongLong) {
        return v1.toULongLong()==v2.toULongLong();
    }
    if (v1.type()==QVariant::String && v2.type()==QVariant::String) {
        return v1.toString()==v2.toString();
    }

    if (v1.canConvert<RColor> () && v2.canConvert<RColor> ()) {
        return v1.value<RColor> () == v2.value<RColor> ();
    }
    if (v1.canConvert<RLinetype> () && v2.canConvert<RLinetype> ()) {
        return v1.value<RLinetype> () == v2.value<RLinetype> ();
    }
    if (v1.canConvert<RLineweight::Lineweight> () && v2.canConvert<RLineweight::Lineweight> ()) {
        return v1.value<RLineweight::Lineweight> () == v2.value<RLineweight::Lineweight> ();
    }
    if (v1.canConvert<QList<RVector> > () && v2.canConvert<QList<RVector> > ()) {
        return v1.value<QList<RVector> > () == v2.value<QList<RVector> > ();
    }
    return v1 == v2;
}

bool RS::compare(const QPair<QVariant, RPropertyAttributes>& p1, const QPair<
                 QVariant, RPropertyAttributes>& p2) {
    return compare(p1.first, p2.first);
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
    // Mac OS X app bundle:
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

    // TODO: add a path to users home to be used to extend pattern, etc.
    //QString appDirName = QSettings.applicationName();
    //dirList.append(RSettings::getHomeLocation() + "/." + appDirName + "/" + subDirectory);

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
    return getFileList("fonts", "cxf");
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

