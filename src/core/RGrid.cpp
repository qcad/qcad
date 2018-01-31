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
#include "RDocument.h"
#include "RGraphicsView.h"
#include "RGrid.h"

int RGrid::getViewportNumber() const {
    return view.getViewportNumber();
}

RDocument* RGrid::getDocument() const {
    return view.getDocument();
}

void RGrid::clearCache() {
    visible = -1;
}

void RGrid::setVisible(bool on) {
    visible = (int)on;

    int viewportNumber = getViewportNumber();
    if (viewportNumber==-1) {
        return;
    }

    RDocument* doc = getDocument();
    if (doc==NULL) {
        return;
    }

    doc->setVariable(QString("Grid/DisplayGrid0%1").arg(viewportNumber), on);
}

bool RGrid::isVisible() const {
    if (visible==-1) {
        int viewportNumber = getViewportNumber();
        if (viewportNumber==-1) {
            return true;
        }

        RDocument* doc = getDocument();
        if (doc==NULL) {
            return true;
        }
        visible = (int)doc->getVariable(QString("Grid/DisplayGrid0%1").arg(viewportNumber), true, true).toBool();
    }
    return visible;
}
