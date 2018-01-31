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

#ifndef REXPORTLISTENER_H
#define REXPORTLISTENER_H

#include <QMetaType>

#include "core_global.h"

class RDocumentInterface;
class RExporter;

/**
 * \brief Abstract base class for classes that are interested in 
 * file export events.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RExportListener {
public:
    virtual ~RExportListener() {}

    /**
     * Called by the document whenever a document is about to be exported.
     */
    virtual void preExportEvent(RDocumentInterface* documentInterface) = 0;

    /**
     * Called by the document whenever a document has been exported.
     */
    virtual void postExportEvent(RDocumentInterface* documentInterface) = 0;

    /**
     * Called by the exporter just before the export finishes.
     */
    virtual void endOfExportEvent(RExporter* exporter) = 0;
};

Q_DECLARE_METATYPE(RExportListener*)

#endif
