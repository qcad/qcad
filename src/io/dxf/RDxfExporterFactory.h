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

#ifndef RDXFEXPORTERFACTORY_H_
#define RDXFEXPORTERFACTORY_H_

#include "dxf_global.h"

#include <QFileInfo>
#include <QMetaType>

#include "RDocument.h"
#include "RDxfExporter.h"
#include "RFileExporter.h"
#include "RFileExporterFactory.h"
#include "RFileExporterRegistry.h"

class RMessageHandler;
class RProgressHandler;

/**
 * \ingroup dxf
 */
class QCADDXF_EXPORT RDxfExporterFactory: public RFileExporterFactory {
public:
    static void registerFileExporter() {
        RFileExporterRegistry::registerFileExporter(
            new RDxfExporterFactory()
        );
    }

    virtual QStringList getFilterStrings();

    virtual RFileExporter* instantiate(RDocument& document,
        RMessageHandler* messageHandler = NULL,
        RProgressHandler* progressHandler = NULL) {

        return new RDxfExporter(document, messageHandler, progressHandler);
    }

    virtual int canExport(const QString& fileName, const QString& nameFilter);
};

Q_DECLARE_METATYPE(RDxfExporterFactory*)

#endif
