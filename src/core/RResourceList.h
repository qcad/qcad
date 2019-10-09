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

#ifndef RRESOURCELIST_H
#define RRESOURCELIST_H

#include "core_global.h"

#include <QDebug>
#include <QString>
#include <QMap>
#include <QFileInfo>

#include "RS.h"

/**
 * A global list of loadable resources (fonts, hatch patterns, line types, ..).
 *
 * \ingroup core
 */
template <class T>
class QCADCORE_EXPORT RResourceList {
public:
//    void init() {
//    }

    void uninit() {
        QMapIterator<QString, T*> it(resMap);

        while (it.hasNext()) {
            it.next();
            delete it.value();
        }

        resMap.clear();
        resSubstitutionMap.clear();
    }

    /**
     * \return List of all available resource names.
     */
    QStringList getNames() {
        return resMap.keys();
    }

    QString getSubName(const QString& resName, int rec=0) {
        // check substitution map first:
        if (RS::mapContainsCaseInsensitive(resSubstitutionMap, resName)) {
            // substitution found:
            QString subName = RS::mapValueCaseInsensitive(resSubstitutionMap, resName);
            if (subName.compare(resName, Qt::CaseInsensitive)==0 || rec>16) {
                qWarning() << "recursive resource substitution:" << resName << "->" << subName;
                // cannot substitute font with itself (avoid recursion):
                return QString();
            }
            return getSubName(subName, ++rec);
        }
        return resName;
    }

    /**
     * \return Resource with the given name or an invalid resource.
     * The returned resource is loaded first if it isn't already.
     */
    T* get(const QString& resName, bool substitute = true) {
        QString resNameSub = resName;
        if (substitute) {
            resNameSub = getSubName(resName);
        }

        // check if resource is available:
        if (!RS::mapContainsCaseInsensitive(resMap, resNameSub)) {
            return NULL;
        }

        T* res = RS::mapValueCaseInsensitive(resMap, resNameSub);
        if (res==NULL) {
            qWarning("RResourceList::get: list contains NULL resource.");
            Q_ASSERT(false);
            return NULL;
        }

        if (!res->isLoaded()) {
            res->load();
        }

        return res;
    }

public:
    QMap<QString, T*> resMap;
    QMap<QString, QString> resSubstitutionMap;
};

//template <class T> QMap<QString, T*> RResourceList<T>::resMap;
//template <class T> QMap<QString, QString> RResourceList<T>::resSubstitutionMap;

#endif
