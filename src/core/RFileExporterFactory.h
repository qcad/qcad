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

#ifndef RFILEEXPORTERFACTORY_H
#define RFILEEXPORTERFACTORY_H

#include "core_global.h"

class RDocument;
class RFileExporter;
class RMessageHandler;
class RProgressHandler;

#include <QMetaType>
#include <QString>

/**
 * \brief Needs to be implemented by RFileExporter implementations
 * to check if the exporter is suitable to export a file and to instantiate
 * the file exporter if required.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RFileExporterFactory {
public:
    virtual ~RFileExporterFactory() {}

    virtual QStringList getFilterStrings() = 0;
    virtual int canExport(const QString& fileName,
        const QString& nameFilter = "") = 0;
    virtual RFileExporter* instantiate(RDocument& document,
        RMessageHandler* messageHandler = NULL,
        RProgressHandler* progressHandler = NULL) = 0;
};

Q_DECLARE_METATYPE(RFileExporterFactory*)

#endif
