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

#ifndef RFILEIMPORTERFACTORY_H
#define RFILEIMPORTERFACTORY_H

#include "core_global.h"

class RDocument;
class RFileImporter;
class RMessageHandler;
class RProgressHandler;

#include <QMetaType>
#include <QString>

/**
 * \brief Needs to be implemented by RFileImporter implementations
 * to check if the importer is suitable to import a file and to instantiate
 * the file importer if required.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RFileImporterFactory {
public:
    virtual QStringList getFilterStrings() = 0;
    virtual int canImport(const QString& fileName, const QString& nameFilter = "") = 0;
    virtual RFileImporter* instantiate(RDocument& document, RMessageHandler* messageHandler = NULL, RProgressHandler* progressHandler = NULL) = 0;
};

Q_DECLARE_METATYPE(RFileImporterFactory*)

#endif
