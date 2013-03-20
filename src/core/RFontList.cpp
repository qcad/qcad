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
#include "RFontList.h"

RResourceList<RFont> RFontList::res;

/**
 * Initializes the font list by creating empty RFont
 * objects, one for each font that could be found.
 */
void RFontList::init() {
    //res.init();

    QStringList fontFileList = RS::getFontList();

    for (int i=0; i<fontFileList.size(); i++) {
        QString fileName = fontFileList.at(i);
        QFileInfo fi(fileName);

        QString resName = fi.completeBaseName();

        if (RS::mapContainsCaseInsensitive(res.resMap, resName)) {
            continue;
        }

        res.resMap.insert(resName, new RFont(fi.absoluteFilePath()));
    }

    res.resSubstitutionMap.insert("txt", "standard");
}

void RFontList::uninit() {
    res.uninit();
}

/**
 * \return True if the given font name refers to a CAD font, false if it
 *      refers to a TTF font.
 */
bool RFontList::isCadFont(const QString& fontName) {
    RFont* font = res.get(fontName);
    if (font==NULL) {
        return false;
    }
    return font->isValid();
}

QStringList RFontList::getNames() {
    QStringList ret = res.getNames();
    qSort(ret.begin(), ret.end());
    return ret;
}
