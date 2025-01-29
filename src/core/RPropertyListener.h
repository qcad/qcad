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

#ifndef RPROPERTYLISTENER_H
#define RPROPERTYLISTENER_H

#include "core_global.h"

#include "RS.h"
#include "RPropertyTypeId.h"

class RDocument;
class REntity;
class RDocument;
class RObject;



/**
 * \brief Abstract base class for classes that are interested in properties 
 * of the current selection or the current action. For example a 
 * property browser or editor.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RPropertyListener {
public:
    virtual ~RPropertyListener() {}

    /**
     * This method is called whenever the relevant combined properties of 
     * the objects in \c document have changed.
     * 
     * For example this can mean that the selection in a document has 
     * changed and the combined properties of the selected entities 
     * should be displayed in a property browser or editor.
     *
     * \param onlyChanges Only changes of entities, the set of entities has
     *      not changed (no deletes, no additions).
     */
    virtual void updateFromDocument(RDocument* document, bool onlyChanges,
              RS::EntityType entityTypeFilter = RS::EntityAll, bool manual = false, bool showOnRequest = false) = 0;
    
    /**
     * This method is called if only the properties of the given property owner
     * are currently relevant.
     *
     * For example this can be the case when an entity is being drawn and
     * only the properties of that entity should be displayed, so that the user
     * can adjust properties before or while drawing the entity.
     */
    virtual void updateFromObject(RObject* object, RDocument* document = NULL) = 0;

    /**
     * This method is called to signal that no properties are currently 
     * relevant. For example that no entities are selected in a document
     * or that nothing is being drawn at the moment.
     */
    virtual void clearEditor() = 0;
};

Q_DECLARE_METATYPE(RPropertyListener*)

#endif
