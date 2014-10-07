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
#include "RLinetypeList.h"

/**
 * Initializes the linetype list.
 */
void RLinetypeList::init(bool metric, RResourceList<RLinetypePattern>& res) {
    QStringList linetypeFileList;
    linetypeFileList.append(RS::getLinetypeList(metric));

    // unique:
    linetypeFileList = linetypeFileList.toSet().toList();

    for (int i=0; i<linetypeFileList.size(); i++) {
        QString fileName = linetypeFileList.at(i);
        QFileInfo fi(fileName);

        QList<QPair<QString, RLinetypePattern*> > linetypes = RLinetypePattern::loadAllFrom(fi.absoluteFilePath());
        for (int i=0; i<linetypes.size(); i++) {
            res.resMap.insert(linetypes[i].first, linetypes[i].second);
        }
    }

    // TODO, extend with acad linetype substitutions:
    //res.resSubstitutionMap.insert("ACAD_ISO02W100", "QCAD_ISO02W100");
}
