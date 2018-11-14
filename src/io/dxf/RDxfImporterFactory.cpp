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

#include "RDxfImporterFactory.h"

QStringList RDxfImporterFactory::getFilterStrings() {
    QStringList ret;
    ret << QString("DXF Files [dxflib] (*.dxf)");
    return ret;
}

int RDxfImporterFactory::canImport(const QString& fileName, const QString& nameFilter) {
    QFileInfo fi(fileName);

    if (nameFilter.contains("dxflib")) {
        return 1;
    }

    // supported file suffix:
    if (fi.suffix().toLower() == "dxf") {
        return 100;
    }

    // supported name filter if no extension is given:
    QString nfl = nameFilter.toLower();
    if (nfl.contains(".dxf")) {
        return 100;
    }

    return -1;
}
