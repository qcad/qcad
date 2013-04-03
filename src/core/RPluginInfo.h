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

#include "core_global.h"

#include <QMetaType>

/**
 * Information about a plugin. Ususally shown in an about dialog.
 *
 * \ingroup core
 * \scriptable
 * \copyable
 */
class QCADCORE_EXPORT RPluginInfo {
public:
    RPluginInfo() {}

    QString getFileName() const {
        return fileName;
    }

    void setFileName(const QString& fn) {
        fileName = fn;
    }

    QString getAboutString() const {
        return aboutString;
    }

    void setAboutString(const QString& s) {
        aboutString = s;
    }

    QString getDescription() const {
        return description;
    }

    void setDescription(const QString& s) {
        description = s;
    }

    QString getVersionString() const {
        return versionString;
    }

    void setVersionString(const QString& vs) {
        versionString = vs;
    }

    QString getErrorString() const {
        return errorString;
    }

    void setErrorString(const QString& es) {
        errorString = es;
    }

    QString getLicense() const {
        return license;
    }

    void setLicense(const QString& l) {
        license = l;
    }

    QString getUrl() const {
        return url;
    }

    void setUrl(const QString& u) {
        url = u;
    }

private:
    QString fileName;
    QString aboutString;
    QString description;
    QString versionString;
    QString errorString;
    QString license;
    QString url;
};

Q_DECLARE_METATYPE(RPluginInfo)
Q_DECLARE_METATYPE(RPluginInfo*)

#endif
