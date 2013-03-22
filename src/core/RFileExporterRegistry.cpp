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
void RFileExporterRegistry::registerFileExporter(RFileExporterFactory* factory) {
    factories.append(factory);
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

    for (it = factories.begin(); it != factories.end(); ++it) {
        bool suitable = (*it)->canExport(fileName, nameFilter);
        if (suitable) {
            return (*it)->instantiate(document, messageHandler, progressHandler);
        }
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
