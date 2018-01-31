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

#ifndef RFILEEXPORTER_H
#define RFILEEXPORTER_H

#include "core_global.h"

#include <QString>

#include "RDocument.h"
#include "RExporter.h"

class RMessageHandler;
class RProgressHandler;


/**
 * \brief Base class for file exporters. 
 *
 * File exporters export \ref RDocument objects into files of a specific format.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RFileExporter : public RExporter {
public:
    RFileExporter();
    RFileExporter(RDocument& document, RMessageHandler* messageHandler = NULL, RProgressHandler* progressHandler = NULL);
    virtual ~RFileExporter();

    /**
     * Must be implemented by file exporters to correct the given
     * file name if necessary (add extension based on chosen name filter).
     */
    virtual QString getCorrectedFileName(const QString& fileName, const QString& nameFilter) = 0;
    
    /**
     * Must be implemented by file exporters to export the document
     * into the given file.
     */
    virtual bool exportFile(const QString& fileName, const QString& nameFilter, bool setFileName = true) = 0;
};

Q_DECLARE_METATYPE(RFileExporter*)

#endif
