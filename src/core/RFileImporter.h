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

#ifndef RFILEIMPORTER_H
#define RFILEIMPORTER_H

#include "core_global.h"

#include "RImporter.h"

#include <QString>

/**
 * \brief Base class for file importers. 
 *
 * File importers import files of a specific format into an \ref RDocument.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RFileImporter : public RImporter {
public:
    RFileImporter();
    RFileImporter(RDocument& document, RMessageHandler* messageHandler = NULL, RProgressHandler* progressHandler = NULL);
    virtual ~RFileImporter();
    
    /**
     * Must be implemented by file importers to import the given file into
     * the document.
     */
    virtual bool importFile(const QString& fileName, const QString& nameFilter) = 0;
};

Q_DECLARE_METATYPE(RFileImporter*)

#endif
