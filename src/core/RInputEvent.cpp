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
#include "RInputEvent.h"
#include "RDocumentInterface.h"
#include "RGraphicsScene.h"
#include "RGraphicsView.h"
#include "RUcs.h"

RInputEvent::RInputEvent(const RVector& position, RGraphicsScene& s, RGraphicsView& v, qreal devicePixelRatio)
    : screenPosition(position*devicePixelRatio), scene(s), view(v) {

    modelPosition = view.mapFromView(screenPosition);

    // apply input transform (used if viewport is active):
//    RDocumentInterface& di = scene.getDocumentInterface();
//    if (di.getDocument().hasCurrentViewport()) {
//        QTransform t = di.getInputTransform();
//        modelPosition.transform2D(t);
//    }

//  RUcs ucs = documentInterface.getCurrentUcs();
//  ucsPosition = ucs.mapToUcs(modelPosition);
}

RInputEvent::~RInputEvent() {
}

RVector RInputEvent::getModelPosition() const {
    return modelPosition;
}

// used for testing
void RInputEvent::setModelPosition(const RVector& v) {
    modelPosition = v;
}

RVector RInputEvent::getCursorPosition() const {
    return cursorPosition;
}

void RInputEvent::setCursorPosition(const RVector& v) {
    cursorPosition = v;
}

void RInputEvent::setScreenPosition(const RVector& v) {
    screenPosition = v;
}

//RVector RInputEvent::getUcsPosition() const {
//  return ucsPosition;
//}

RVector RInputEvent::getScreenPosition() const {
    return screenPosition;
}

RGraphicsView& RInputEvent::getGraphicsView() const {
    return view;
}

RGraphicsScene& RInputEvent::getGraphicsScene() const {
    return scene;
}
