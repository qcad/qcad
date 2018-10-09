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

#ifndef RRULER_H
#define RRULER_H

#include "core_global.h"

#include <Qt>
#include <QMetaType>

class QFont;
class RGraphicsView;

/**
 * Abstract base class for widgets that display a ruler, usually shown at 
 * the top and left of a graphics view.
 *
 * \scriptable
 */
class QCADCORE_EXPORT RRuler {

public:
    RRuler() :
        view(NULL), orientation(Qt::Horizontal) {
    }
    virtual ~RRuler() {
    }

    void setGraphicsView(RGraphicsView* view) {
        this->view = view;
        updateViewport();
    }

    Qt::Orientation getOrientation() const {
        return orientation;
    }

    void setOrientation(Qt::Orientation orientation) {
        this->orientation = orientation;
        updateViewport();
    }

    virtual void paintTick(int pos, bool major, const QString& label) = 0;

    virtual QFont getFont() const = 0;

    virtual void updateViewport() = 0;

protected:
    RGraphicsView* view;
    Qt::Orientation orientation;
};

Q_DECLARE_METATYPE(RRuler*)

#endif
