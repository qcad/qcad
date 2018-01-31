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
#include <QFileInfo>

#include "RFileImporterRegistry.h"
#include "RFileImporter.h"
#include "RFileImporterFactory.h"
#include "RMessageHandler.h"
#include "RProgressHandler.h"
#include "RScriptHandler.h"
#include "RScriptHandlerRegistry.h"


QList<RFileImporterFactory*> RFileImporterRegistry::factories;



/**
 * Registers a file importer.
 *
 * \param factoryFunction The function that can be used to instantiate
 *      the importer.
 * \param checkFunction The function tht can be used to check whether
 *      the importer can import a given file.
 */
void RFileImporterRegistry::registerFileImporter(RFileImporterFactory* factory) {
    factories.append(factory);
}

/**
 * Unregisters a file importer.
 *
 * \param factoryFunction The function that can be used to instantiate
 *      the importer.
 * \param checkFunction The function tht can be used to check whether
 *      the importer can import a given file.
 */
void RFileImporterRegistry::unregisterFileImporter(RFileImporterFactory* factory) {
    factories.removeAll(factory);
}

/**
 * \return A new instance of the first file importer found that
 *      can handle the given file or NULL if no suitable importer 
 *      can be found.
 */
RFileImporter* RFileImporterRegistry::getFileImporter(
    const QString& fileName,
    const QString& nameFilter,
    RDocument& document,
    RMessageHandler* messageHandler, RProgressHandler* progressHandler) {

    QList<RFileImporterFactory*>::iterator it;
    RFileImporterFactory* bestMatch = NULL;

    int bestPriority = -1;
    for (it = factories.begin(); it != factories.end(); ++it) {
        int p = (*it)->canImport(fileName, nameFilter);
        if (p>0 && (p<bestPriority || bestPriority==-1)) {
            bestMatch = (*it);
            bestPriority = p;
        }
    }

    if (bestMatch!=NULL) {
        return bestMatch->instantiate(document, messageHandler, progressHandler);
    }

    qWarning() << "RFileImporterRegistry::getFileImporter: No suitable importer found for \n" << fileName;

    return NULL;
}

/**
 * \return True if an importer is available that can import the given file.
 */
bool RFileImporterRegistry::hasFileImporter(
    const QString& fileName,
    const QString& nameFilter) {

    QList<RFileImporterFactory*>::iterator it;

    for (it = factories.begin(); it != factories.end(); ++it) {
        int p = (*it)->canImport(fileName, nameFilter);
        if (p!=-1) {
            return true;
        }
    }

    return false;
}

QStringList RFileImporterRegistry::getFilterExtensions() {
    QStringList ret;
    QList<RFileImporterFactory*>::iterator it;

    for (it = factories.begin(); it != factories.end(); ++it) {
        QStringList filterStrings = (*it)->getFilterStrings();
        for (int i=0; i<filterStrings.count(); i++) {
            QString filterString = filterStrings[i];
            QRegExp rx("\\*\\.([^ )]*)");
            int pos = 0;
             
            while ((pos = rx.indexIn(filterString, pos)) != -1)  {
                ret.append(rx.cap(1));
                pos += rx.matchedLength();
            }
        }
    }

    // unique:
    ret = ret.toSet().toList();

    return ret;
}

QStringList RFileImporterRegistry::getFilterExtensionPatterns() {
    QStringList ret;
    QStringList filterExtensions = getFilterExtensions();
    for (int i=0; i<filterExtensions.count(); i++) {
        ret.append(QString("*.%1").arg(filterExtensions[i]));
    }
    return ret;
}

QStringList RFileImporterRegistry::getFilterStrings() {
    QStringList ret;
    QList<RFileImporterFactory*>::iterator it;

    for (it = factories.begin(); it != factories.end(); ++it) {
        ret.append((*it)->getFilterStrings());
    }

    return ret;
}
