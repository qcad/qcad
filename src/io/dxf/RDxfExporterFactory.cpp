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

#include "RDxfExporterFactory.h"

QStringList RDxfExporterFactory::getFilterStrings() {
    QStringList ret;

    QString sDrawing = QObject::tr("Drawing");

    ret << QString("R15 [2000/LT2000] DXF %1 [dxflib] (*.dxf)").arg(sDrawing);
    //ret << QString("R12 (LT2) DXF %1 (dxflib) (*.dxf)").arg(sDrawing);

    return ret;
}

int RDxfExporterFactory::canExport(const QString& fileName, const QString& nameFilter) {
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
