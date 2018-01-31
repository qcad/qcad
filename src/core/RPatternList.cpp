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
#include "RPatternList.h"

/**
 * Initializes the pattern list.
 */
void RPatternList::init(bool metric, RResourceList<RPattern>& res) {
    //res.init();

    QStringList patternFileList;
    patternFileList.append(RS::getPatternList(metric));

    // unique:
    patternFileList = patternFileList.toSet().toList();

    for (int i=0; i<patternFileList.size(); i++) {
        QString fileName = patternFileList.at(i);
        QFileInfo fi(fileName);

        //T* res = new T(fi.absoluteFilePath());
        QList<QPair<QString, RPattern*> > patterns = RPattern::loadAllFrom(fi.absoluteFilePath());
        for (int i=0; i<patterns.size(); i++) {
            res.resMap.insert(patterns[i].first, patterns[i].second);
        }
    }

    // TODO, extend with acad pattern substitutions:
    res.resSubstitutionMap.insert("45", "ansi31");
}
