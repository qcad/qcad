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

#include <QFontDatabase>

#include "RFontList.h"
#include "RSettings.h"

RResourceList<RFont> RFontList::res;

/**
 * Initializes the font list by creating empty RFont
 * objects, one for each font that could be found.
 */
void RFontList::init() {
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
    res.resSubstitutionMap.insert("iso", "standard");
    res.resSubstitutionMap.insert("isocp", "standard");

    // load local TTF application fonts:
    QStringList ttfFiles = RS::getFileList("fonts", "ttf");
    for (int i=0; i<ttfFiles.length(); i++) {
        QFontDatabase::addApplicationFont(ttfFiles[i]);
    }
}

void RFontList::initSubstitutions() {

    // read substitutions from ini file:
    QString settingsKey = QString("FontSubstitution/Substitutions");
    if (RSettings::hasValue(settingsKey)) {
        QString v = RSettings::getStringValue(settingsKey, "");
        if (!v.isEmpty()) {
            QStringList substitutions = v.split(";");
            for (int i=0; i<substitutions.length(); i++) {
                // s[i]: "standard:iso,iso2"
                QStringList keyValue = substitutions[i].split(":");
                if (keyValue.length()!=2) {
                    continue;
                }
                QString key = keyValue[0];
                // key: "standard"
                QStringList values = keyValue[1].split(",");
                // values: "iso","iso2"
                for (int k=0; k<values.length(); k++) {
                    res.resSubstitutionMap.insert(values[k], key);
                }
            }
        }
    }

    // read substitutions from command line:
    QStringList args = qApp->arguments();
    for (int i=0; i<args.length(); i++) {
        if (args[i]=="-font-substitution" || args[i]=="-fs") {
            if (i+2<args.length()) {
                res.resSubstitutionMap.insert(args[i+1], args[i+2]);
            }
            i+=2;
        }
    }
}

QString RFontList::getSubName(const QString& resName) {
    return res.getSubName(resName);
}

void RFontList::uninit() {
    res.uninit();
}

/**
 * \return True if the given font name refers to a CAD font, false if it
 *      refers to a TTF font.
 */
bool RFontList::isCadFont(const QString& fontName, const QString& fontFile) {
    QString fontSubName = res.getSubName(fontName);
    RFont* font = get(fontSubName);
    if (font==NULL) {
        if (fontSubName!=fontName) {
            return false;
        }
        return fontFile.toLower().contains(".shx");
    }
    return font->isValid();
}

QStringList RFontList::getNames() {
    QStringList ret = res.getNames();
    qSort(ret.begin(), ret.end());
    return ret;
}

RFont* RFontList::get(const QString& resName, bool substitute) {
    return res.get(resName, substitute);
}
