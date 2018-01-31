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

#ifndef RFILEEXPORTERREGISTRY_H
#define RFILEEXPORTERREGISTRY_H

#include "core_global.h"

#include <QList>
#include <QMetaType>
#include <QString>
#include <QStringList>

class RDocument;
class RFileExporter;
class RFileExporterFactory;
class RMessageHandler;
class RProgressHandler;

/**
 * \brief Registry of all available file exporters (\ref RFileExporter).
 *
 * File exporters must register themselves in this registry to become 
 * available to the user of the application.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RFileExporterRegistry {
public:
    static void registerFileExporter(RFileExporterFactory* factory, bool prepend=false);
    static void unregisterFileExporter(RFileExporterFactory* factory);

    static RFileExporter* getFileExporter(
        const QString& fileName,
        const QString& nameFilter,
        RDocument& document,
        RMessageHandler* messageHandler = NULL,
        RProgressHandler* progressHandler = NULL
    );

    static QStringList getFilterStrings();

private:
    static QList<RFileExporterFactory*> factories;
};

Q_DECLARE_METATYPE(RFileExporterRegistry*)

#endif
