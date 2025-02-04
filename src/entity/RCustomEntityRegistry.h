/**
 * Copyright (c) 2011-2025 by Andrew Mustun. All rights reserved.
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

#ifndef RCUSTOMENTITYREGISTRY_H
#define RCUSTOMENTITYREGISTRY_H

#include "entity_global.h"

#include <QList>
#include <QMetaType>

#include "RS.h"

class RCustomEntityHandler;

/**
 * \brief Registry of all available file exporters (\ref RFileExporter).
 *
 * File exporters must register themselves in this registry to become 
 * available to the user of the application.
 *
 * \ingroup core
 * \scriptable
 */
class QCADENTITY_EXPORT RCustomEntityRegistry {
public:
    static void registerHandler(RCustomEntityHandler* handler);
    static RCustomEntityHandler* getHandler(RS::EntityType entityType);

private:
    static QList<RCustomEntityHandler*> handlers;
};

Q_DECLARE_METATYPE(RCustomEntityRegistry*)

#endif

