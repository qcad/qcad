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

#ifndef RPLUGININFO_H
#define RPLUGININFO_H

#include <QMetaType>

/**
 * Information about a plugin. Ususally shown in an about dialog.
 *
 * \ingroup core
 * \scriptable
 * \copyable
 */
class RPluginInfo {
public:
    RPluginInfo() {}
    RPluginInfo(const QString& fileName,
                const QString& errorString) :
        fileName(fileName),
        errorString(errorString) {}
    RPluginInfo(const QString& fileName,
                const QString& aboutString,
                const QString& versionString,
                const QString& errorString) :
        fileName(fileName),
        versionString(versionString),
        aboutString(aboutString),
        errorString(errorString) {}

    QString getFileName() {
        return fileName;
    }

    QString getAboutString() {
        return aboutString;
    }

    QString getVersionString() {
        return versionString;
    }

    QString getErrorString() {
        return errorString;
    }

private:
    QString fileName;
    QString aboutString;
    QString versionString;
    QString errorString;
};

Q_DECLARE_METATYPE(RPluginInfo)
Q_DECLARE_METATYPE(RPluginInfo*)

#endif
