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
#include "RNavigationAction.h"

RNavigationAction::RNavigationAction(RGuiAction* guiAction) 
    : RActionAdapter(guiAction), 
    panning(false) {
}

void RNavigationAction::mousePressEvent(RMouseEvent& event) {
    if (event.button() == Qt::MidButton ||
        ( event.button() == Qt::LeftButton && 
          event.modifiers() == Qt::ControlModifier)) {
        panOrigin = event.getScreenPosition();
        panning = true;
        event.getGraphicsView().startPan();
    }
}

void RNavigationAction::mouseReleaseEvent(RMouseEvent& event) {
    if (event.button() == Qt::MidButton ||
        event.button() == Qt::LeftButton) {
        panning = false;
    }
}

void RNavigationAction::mouseMoveEvent(RMouseEvent& event) {
    if (panning &&
        ( event.buttons() == Qt::MidButton ||
          ( event.buttons() == Qt::LeftButton &&
            event.modifiers() == Qt::ControlModifier )
        )) {

        RVector panTarget = event.getScreenPosition();
        RVector panDelta = panTarget - panOrigin;
        if (fabs(panDelta.x) > 1 || fabs(panDelta.y) > 1) {
            event.getGraphicsView().pan(panDelta);
            panOrigin = panTarget;
        }
    }
}
