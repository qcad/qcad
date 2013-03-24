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

    QString getFileName() {
        return fileName;
    }

    void setFileName(const QString& fn) {
        fileName = fn;
    }

    QString getAboutString() {
        return aboutString;
    }

    void setAboutString(const QString& s) {
        aboutString = s;
    }

    QString getVersionString() {
        return versionString;
    }

    void setVersionString(const QString& vs) {
        versionString = vs;
    }

    QString getErrorString() {
        return errorString;
    }

    void setErrorString(const QString& es) {
        errorString = es;
    }

    QString getLicense() {
        return license;
    }

    void setLicense(const QString& l) {
        license = l;
    }

private:
    QString fileName;
    QString aboutString;
    QString versionString;
    QString errorString;
    QString license;
};

Q_DECLARE_METATYPE(RPluginInfo)
Q_DECLARE_METATYPE(RPluginInfo*)

#endif
