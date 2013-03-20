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
#include <QFileInfo>

#include "RFileImporterRegistry.h"
#include "RFileImporterAdapter.h"
#include "RMessageHandler.h"
#include "RProgressHandler.h"
#include "RScriptHandler.h"
#include "RScriptHandlerRegistry.h"

#include "RDebug.h"
    
    
QList<RFileImporterRegistry::FactoryFunction> RFileImporterRegistry::factoryFunctions;
QList<RFileImporterRegistry::CheckFunction> RFileImporterRegistry::checkFunctions;
QStringList RFileImporterRegistry::filterStrings;
QList<QString> RFileImporterRegistry::scriptImporters;



/**
 * Registers a file importer.
 *
 * \param factoryFunction The function that can be used to instantiate
 *      the importer.
 * \param checkFunction The function tht can be used to check whether
 *      the importer can import a given file.
 */
void RFileImporterRegistry::registerFileImporter(
    FactoryFunction factoryFunction,
    CheckFunction checkFunction,
    const QStringList& filters) {

    factoryFunctions.append(factoryFunction);
    checkFunctions.append(checkFunction);
    filterStrings.append(filters);
}


void RFileImporterRegistry::registerFileImporterScript(const QString& scriptFile, const QStringList& filters) {
    scriptImporters.append(scriptFile);
    filterStrings.append(filters);
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

    // check script importers first, so users can override C++ importers:
    for (int i=0; i<scriptImporters.size(); i++) {
        QString script = scriptImporters[i];
        QFileInfo scriptFi(script);

        RScriptHandler* handler = RScriptHandlerRegistry::getGlobalScriptHandler(scriptFi.suffix());
        if (handler!=NULL) {
            handler->doScript(script);
            RFileImporterAdapter* importer = handler->createFileImporter(
                scriptFi.completeBaseName(), document);
            if (importer!=NULL) {
                if (importer->canImport(fileName, nameFilter)) {
                    return importer;
                }
                else {
                    delete importer;
                }
            }
        }
    }

    // check C++ importers:
    QList<CheckFunction>::iterator itc;
    QList<FactoryFunction>::iterator itf;

    for (itc = checkFunctions.begin(), itf = factoryFunctions.begin(); itc
            != checkFunctions.end(), itf != factoryFunctions.end(); ++itc, ++itf) {
        bool suitable = (*itc)(fileName, nameFilter);
        if (suitable) {
            return (*itf)(document, messageHandler, progressHandler);
        }
    }

    qWarning("RFileImporterRegistry::getFileImporter: "
             "No suitable importer found");

    return NULL;
}

/**
 * \return True if an importer is available that can import the given file.
 */
bool RFileImporterRegistry::hasFileImporter(
    const QString& fileName,
    const QString& nameFilter) {

    QList<CheckFunction>::iterator itc;
    QList<FactoryFunction>::iterator itf;

    for (itc = checkFunctions.begin(), itf = factoryFunctions.begin(); itc
            != checkFunctions.end(), itf != factoryFunctions.end(); ++itc, ++itf) {
        bool suitable = (*itc)(fileName, nameFilter);
        if (suitable) {
            return true;
        }
    }

    return false;
}

QStringList RFileImporterRegistry::getFilterExtensions() {
    QStringList ret;
    for (int i=0; i<filterStrings.count(); i++) {
        QString filterString = filterStrings[i];
        //int p = filterString.

        QRegExp rx("(\\*\\.[^ ]*)");
        QStringList list;
        int pos = 0;
         
        while ((pos = rx.indexIn(filterString, pos)) != -1)  {
            ret << rx.cap(1);
            pos += rx.matchedLength();
        }
    }
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
