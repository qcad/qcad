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

#ifndef RFILEIMPORTERADAPTER_H
#define RFILEIMPORTERADAPTER_H

#include "RFileImporter.h"

class RDocument;
class RMessageHandler;
class RProgressHandler;

/**
 * \brief Base class for file importers. 
 *
 * File importers import files of a specific format into an \ref RDocument.
 *
 * \ingroup ecma
 * \scriptable
 * \generateScriptShell
 */
class RFileImporterAdapter : public RFileImporter {
public:
    RFileImporterAdapter() : RFileImporter() {}
    RFileImporterAdapter(RDocument& document,
        RMessageHandler* messageHandler = NULL, RProgressHandler* progressHandler = NULL)
        : RFileImporter(document, messageHandler, progressHandler) {}
    virtual ~RFileImporterAdapter() {}
    
    virtual bool importFile(const QString& fileName, const QString& nameFilter) {
        Q_UNUSED(fileName)
        Q_UNUSED(nameFilter)
        return false;
    }
};

Q_DECLARE_METATYPE(RFileImporterAdapter*)

#endif
