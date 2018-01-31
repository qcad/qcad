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

#ifndef RFILEIMPORTERREGISTRY_H
#define RFILEIMPORTERREGISTRY_H

#include "core_global.h"

#include <QString>
#include <QList>
#include <QMetaType>
#include <QStringList>

class RDocument;
class RFileImporter;
class RFileImporterFactory;
class RMessageHandler;
class RProgressHandler;

/**
 * \brief Registry of all available file importers (\ref RFileImporter). 
 *
 * File importers must register themselves in this registry to become 
 * available to the user of the application.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RFileImporterRegistry {
public:
    static void registerFileImporter(RFileImporterFactory* factory);
    static void unregisterFileImporter(RFileImporterFactory* factory);

    static RFileImporter* getFileImporter(
        const QString& fileName,
        const QString& nameFilter,
        RDocument& document,
        RMessageHandler* messageHandler = NULL,
        RProgressHandler* progressHandler = NULL
    );

    static QStringList getFilterStrings();

    static bool hasFileImporter(const QString& fileName, const QString& nameFilter);

    /**
     * \return List of all importable file extensions (e.g. 'dxf', 'dwg', ...).
     */
    static QStringList getFilterExtensions();

    /**
     * \return List of all importable file extension patterns (e.g. '*.dxf', '*.dwg', ...).
     */
    static QStringList getFilterExtensionPatterns();

private:
    static QList<RFileImporterFactory*> factories;
};

Q_DECLARE_METATYPE(RFileImporterRegistry*)

#endif
