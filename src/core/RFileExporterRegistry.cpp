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

#include "RDebug.h"
#include "RFileExporterFactory.h"
#include "RFileExporterRegistry.h"

    
QList<RFileExporterFactory*> RFileExporterRegistry::factories;



/**
 * Registers a file exporter.
 *
 * \param factory exporter factory that provides information about the
 * exporter and can instantiate it.
 */
void RFileExporterRegistry::registerFileExporter(RFileExporterFactory* factory, bool prepend) {
    if (prepend) {
        factories.prepend(factory);
    }
    else {
        factories.append(factory);
    }
}

/**
 * Unregisters a file exporter.
 */
void RFileExporterRegistry::unregisterFileExporter(RFileExporterFactory* factory) {
    factories.removeAll(factory);
}

/**
 * \return A new instance of the first file exporter found that
 *      can handle the given file or NULL if no suitable exporter
 *      can be found.
 */
RFileExporter* RFileExporterRegistry::getFileExporter(
    const QString& fileName,
    const QString& nameFilter, 
    RDocument& document,
    RMessageHandler* messageHandler, RProgressHandler* progressHandler) {

    QList<RFileExporterFactory*>::iterator it;
    RFileExporterFactory* bestMatch = NULL;

    int bestPriority = -1;
    for (it = factories.begin(); it != factories.end(); ++it) {
        int p = (*it)->canExport(fileName, nameFilter);
        if (p>0 && (p<bestPriority || bestPriority==-1)) {
            bestMatch = (*it);
            bestPriority = p;
        }
    }

    if (bestMatch!=NULL) {
        return bestMatch->instantiate(document, messageHandler, progressHandler);
    }

    qWarning("RFileExporterRegistry::getFileExporter: "
        "No suitable exporter found");

    return NULL;
}

QStringList RFileExporterRegistry::getFilterStrings() {
    QStringList ret;
    QList<RFileExporterFactory*>::iterator it;

    for (it = factories.begin(); it != factories.end(); ++it) {
        ret.append((*it)->getFilterStrings());
    }

    return ret;
}
