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
#include "RDocumentInterface.h"
#include "RGraphicsScene.h"
#include "RGraphicsView.h"
#include "RTabletEvent.h"
#include "RUcs.h"


/*
RTabletEvent::RTabletEvent(
        QEvent::Type type,
        const RVector& position,
        int device,
        int pointerType,
        qreal pressure,
        int xTilt,
        int yTilt,
        qreal tangentialPressure,
        qreal rotation,
        int z,
        Qt::KeyboardModifiers keyState,
        qint64 uniqueID,
        RGraphicsScene& s,
        RGraphicsView& v)

    :   QTabletEvent(type, QPoint(position.x, position.y), button, buttons, modifiers),
        screenPosition(position),
        scene(s),
        view(v) {

    modelPosition = view.mapFromView(position);

    RDocumentInterface& documentInterface = view.getDocumentInterface();
    RUcs ucs = documentInterface.getCurrentUcs();
    ucsPosition = ucs.mapToUcs(modelPosition);
}
*/


RTabletEvent::RTabletEvent(const QTabletEvent& tabletEvent, RGraphicsScene& s,
        RGraphicsView& v) :
    QTabletEvent(tabletEvent), screenPosition(tabletEvent.pos().x(),
            tabletEvent.pos().y()), scene(s), view(v) {

}


RTabletEvent::~RTabletEvent() {
}



RVector RTabletEvent::getModelPosition() const {
    return modelPosition;
}



RVector RTabletEvent::getUcsPosition() const {
    return ucsPosition;
}


RVector RTabletEvent::getScreenPosition() const {
    return screenPosition;
}

RGraphicsView& RTabletEvent::getGraphicsView() const {
    return view;
}


RGraphicsScene& RTabletEvent::getGraphicsScene() const {
    return scene;
}
