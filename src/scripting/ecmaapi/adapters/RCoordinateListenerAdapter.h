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

#ifndef RCOORDINATELISTENERADAPTER_H_
#define RCOORDINATELISTENERADAPTER_H_

#include <QObject>

#include "RVector.h"
#include "RCoordinateListener.h"

class RDocumentInterface;

/**
 * This coordinate listener adapter emits signals on coordinate events.
 * Used to simplify listening to coordinate events from QObjects,
 * for instance from an ECMA script.
 *
 * \scriptable
 * \ingroup ecma
 */
class RCoordinateListenerAdapter: public QObject, public RCoordinateListener {
Q_OBJECT

public:
    RCoordinateListenerAdapter(QObject* parent=NULL) : QObject(parent) { }
    virtual ~RCoordinateListenerAdapter() { }

    virtual void updateCoordinate(RDocumentInterface* documentInterface) {
        emit coordinateUpdated(documentInterface);
    }

signals:
    void coordinateUpdated(RDocumentInterface* documentInterface);
};

Q_DECLARE_METATYPE(RCoordinateListenerAdapter*)

#endif
