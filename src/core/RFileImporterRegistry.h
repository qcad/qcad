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

#ifndef RFILEIMPORTERREGISTRY_H
#define RFILEIMPORTERREGISTRY_H

class RFileImporter;
class RDocument;
class RMessageHandler;
class RProgressHandler;

#include <QString>
#include <QList>
#include <QMetaType>
#include <QStringList>


/**
 * \brief Registry of all available file importers (\ref RFileImporter). 
 *
 * File importers must register themselves in this registry to become 
 * available to the user of the application.
 *
 * \ingroup core
 * \scriptable
 */
class RFileImporterRegistry {
public:
    typedef RFileImporter* (*FactoryFunction)(RDocument& document,
        RMessageHandler* messageHandler, RProgressHandler* progressHandler);
    typedef bool (*CheckFunction)(const QString&, const QString&);

    /**
     * \nonscriptable
     */
    static void registerFileImporter(
        RFileImporterRegistry::FactoryFunction factoryFunction,
        RFileImporterRegistry::CheckFunction checkFunction,
        const QStringList& filters
    );

    static void registerFileImporterScript(
        const QString& scriptFile,
        const QStringList& filters
    );

    static RFileImporter* getFileImporter(
        const QString& fileName,
        const QString& nameFilter,
        RDocument& document,
        RMessageHandler* messageHandler = NULL,
        RProgressHandler* progressHandler = NULL
    );

    static bool hasFileImporter(const QString& fileName, const QString& nameFilter);

    /**
     * \return List of all available filter strings, e.g. for a file open
     * dialog.
     */
    static QStringList getFilterStrings() {
        return filterStrings;
    }

    /**
     * \return List of all importable file extensions (e.g. 'dxf', 'dwg', ...).
     */
    static QStringList getFilterExtensions();

    /**
     * \return List of all importable file extension patterns (e.g. '*.dxf', '*.dwg', ...).
     */
    static QStringList getFilterExtensionPatterns();

private:
    static QList<FactoryFunction> factoryFunctions;
    static QList<CheckFunction> checkFunctions;

    static QList<QString> scriptImporters;

    static QStringList filterStrings;
};

Q_DECLARE_METATYPE(RFileImporterRegistry*)

#endif
