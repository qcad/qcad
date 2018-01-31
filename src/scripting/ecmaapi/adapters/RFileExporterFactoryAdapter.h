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

#ifndef RFILEEXPORTERFACTORYADAPTER_H
#define RFILEEXPORTERFACTORYADAPTER_H

#include "RFileExporter.h"
#include "RFileExporterFactory.h"

class RDocument;
class RMessageHandler;
class RProgressHandler;


/**
 * \brief Need to be implemented for every RFileExporter implementation
 * to check if the exporter is suitable to export a file and to instantiate
 * the file exporter if required.
 *
 * \ingroup ecma
 * \scriptable
 * \generateScriptShell
 */
class RFileExporterFactoryAdapter : public RFileExporterFactory {
public:
    virtual QStringList getFilterStrings() { 
        return QStringList(); 
    }
    virtual int canExport(const QString& fileName, const QString& nameFilter = "") {
        Q_UNUSED(fileName)
        Q_UNUSED(nameFilter)
        return -1;
    }
    virtual RFileExporter* instantiate(RDocument& document,
        RMessageHandler* messageHandler = NULL,
        RProgressHandler* progressHandler = NULL) {

        Q_UNUSED(document)
        Q_UNUSED(messageHandler)
        Q_UNUSED(progressHandler)
        return NULL;
    }
};

Q_DECLARE_METATYPE(RFileExporterFactoryAdapter*)

#endif
