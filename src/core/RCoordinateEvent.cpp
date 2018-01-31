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
#include "RCoordinateEvent.h"
#include "RDocumentInterface.h"
#include "RGraphicsScene.h"
#include "RGraphicsView.h"
#include "RUcs.h"

RCoordinateEvent::RCoordinateEvent(const RVector& position,
   RGraphicsScene& s, RGraphicsView& v) : QEvent((QEvent::Type)(QEvent::User+201)), RInputEvent(position, s, v), mods(Qt::NoModifier) {

    modelPosition = position;
    screenPosition = v.mapToView(position);

//    RDocumentInterface& documentInterface = s.getDocumentInterface();
//    RUcs ucs = documentInterface.getCurrentUcs();
//    ucsPosition = ucs.mapToUcs(modelPosition);
}
