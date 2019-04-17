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

#ifndef RLAYERLISTENER_H
#define RLAYERLISTENER_H

#include "core_global.h"

#include "RLayer.h"

class RDocumentInterface;



/**
 * \brief Abstract base class for classes that are interested 
 * in being notified whenever a layer has been added or changed.
 * This can for example be a widget that lists all layers.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RLayerListener {
public:
    virtual ~RLayerListener() {}

    /**
     * This method is called whenever at least one layer in the given
     * document has changed.
     */
    virtual void updateLayers(RDocumentInterface* documentInterface, QList<RLayer::Id>& layerIds) = 0;

    /**
     * This method is called when a different layer becomes the new current layer.
     */
    virtual void setCurrentLayer(RDocumentInterface* documentInterface, RLayer::Id previousLayerId) = 0;

    /**
     * This method is called to signal that no document is currently active.
     */
    virtual void clearLayers() = 0;
};

Q_DECLARE_METATYPE(RLayerListener*)

#endif
