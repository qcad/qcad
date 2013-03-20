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

#ifndef RFILEEXPORTERFACTORY_H
#define RFILEEXPORTERFACTORY_H

class RFileExporter;
class RDocument;

#include <QMetaType>
#include <QString>

/**
 * \brief Need to be implemented for every RFileExporter implementation
 * to check if the exporter is suitable to export a file and to instantiate
 * the file exporter if required.
 *
 * \ingroup core
 * \scriptable
 */
class RFileExporterFactory {
public:
    virtual QStringList getFilterStrings() = 0;
    virtual bool canExport(const QString& fileName, const QString& nameFilter = "") = 0;
    virtual RFileExporter* instantiate(RDocument& document) = 0;
};

Q_DECLARE_METATYPE(RFileExporterFactory*)

#endif
