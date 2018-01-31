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

#ifndef RNAVIGATIONACTION_H
#define RNAVIGATIONACTION_H

#include "core_global.h"

#include "RActionAdapter.h"
#include "RMouseEvent.h"
#include "RGraphicsView.h"
#include "RGuiAction.h"

/**
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RNavigationAction : public RActionAdapter {
public:
    RNavigationAction(RGuiAction* guiAction=NULL);

    virtual void mousePressEvent(RMouseEvent& event);
    virtual void mouseReleaseEvent(RMouseEvent& event);
    virtual void mouseMoveEvent(RMouseEvent& event);

private:
    bool panning;
    RVector panOrigin;
};

Q_DECLARE_METATYPE(RNavigationAction*)

#endif
