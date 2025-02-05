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

#ifndef RCUSTOMENTITYHANDLER_H
#define RCUSTOMENTITYHANDLER_H

#include "entity_global.h"

#include "RBlockReferenceEntity.h"
#include "RBlockReferenceData.h"

class RDocument;
class RExporter;
class RCustomEntity;

/**
 * Interface for custom entity handlers that implement rendering of custom entities.
 *
 * \scriptable
 * \ingroup core
 */
class QCADENTITY_EXPORT RCustomEntityHandler {

public:
    virtual ~RCustomEntityHandler() {}

    /**
     * \return The type of the custom entity handled by this handler.
     */
    virtual RS::EntityType getEntityType() const = 0;

    /**
     * Renders the entity into the block of the given block reference.
     */
    virtual void render(const RBlockReferenceEntity* entity) = 0;

    /**
     * Sets the given property for the custom entity.
     */
    virtual void setProperty(RCustomEntity& entity, RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction = NULL) = 0;

    /**
     * \return The value of the given property for the custom entity.
     */
    virtual QPair<QVariant, RPropertyAttributes> getProperty(RCustomEntity& entity,
            RPropertyTypeId& propertyTypeId, bool humanReadable = false,
            bool noAttributes = false, bool showOnRequest = false) = 0;
};

Q_DECLARE_METATYPE(RCustomEntityHandler*)

#endif
