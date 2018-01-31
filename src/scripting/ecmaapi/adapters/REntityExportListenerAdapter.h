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

#ifndef RENTITYEXPORTLISTENERADAPTER_H
#define RENTITYEXPORTLISTENERADAPTER_H

#include <QObject>

#include "REntityExportListener.h"

class RExporter;

/**
 * This entity decorator adapter emits signals on block events.
 * Used to simplify entity decoration from QObjects,
 * for instance from an ECMA script.
 *
 * \scriptable
 * \ingroup ecma
 */
class REntityExportListenerAdapter : public QObject, public REntityExportListener {
Q_OBJECT

public:
    virtual ~REntityExportListenerAdapter() {}

    virtual void exportEntity(RExporter* exporter, REntity* entity) {
        // entity pointer does not cast to entity type (e.g. RLineEntity) when passed through signal:
        Q_UNUSED(entity)

        emit entityExported(exporter);
    }

signals:
    void entityExported(RExporter* exporter);
};

Q_DECLARE_METATYPE(REntityExportListenerAdapter*)

#endif
