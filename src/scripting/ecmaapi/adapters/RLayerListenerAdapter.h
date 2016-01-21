/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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

#ifndef RLAYERLISTENERADAPTER_H_
#define RLAYERLISTENERADAPTER_H_

#include <QObject>

#include "RDocumentInterface.h"
#include "RLayerListener.h"

/**
 * \scriptable
 * \ingroup ecma
 */
class RLayerListenerAdapter: public QObject, public RLayerListener {
Q_OBJECT

public:
    RLayerListenerAdapter(QObject* parent=NULL) : QObject(parent) { }
    virtual ~RLayerListenerAdapter() { }

    virtual void updateLayers(RDocumentInterface* documentInterface) {
        emit layersUpdated(documentInterface);
    }

    virtual void clearLayers() {
        emit layersCleared();
    }

signals:
    void layersUpdated(RDocumentInterface* documentInterface);
    void layersCleared();
};

Q_DECLARE_METATYPE(RLayerListenerAdapter*)

#endif
