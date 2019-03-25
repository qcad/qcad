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

#ifndef RGRID_H
#define RGRID_H

#include "core_global.h"

#include "RVector.h"
#include "RBox.h"
#include "RRuler.h"

class RDocument;
class RGraphicsView;

/**
 * Abstract base class for grid implementations. A grid class
 * can for example implement an orthogonal grid or a polar grid.
 *
 * \scriptable
 * \ingroup core
 */
class QCADCORE_EXPORT RGrid {
public:
    RGrid(RGraphicsView& view) : view(view), visible(-1) {}
    virtual ~RGrid() {}

    virtual void clearCache();

    /**
     * Snaps the given UCS position to the grid.
     */
    virtual RVector snapToGrid(const RVector& positionUcs) = 0;

    /**
     * This is called by the graphics view this grid is attached to
     * whenever the view port changes and the grid needs to be
     * updated.
     */
    virtual void update(bool force=false) = 0;

    /**
     * This is called by the graphics view this grid is attached to
     * whenever the grid should be painted.
     */
    virtual void paint() = 0;

    /**
     * This is called by the graphics view this grid is attached to
     * whenever the meta grid should be painted.
     */
    virtual void paintMetaGrid() = 0;

    virtual void paintCursor(const RVector& pos) = 0;

    virtual void paintRuler(RRuler& ruler, qreal devicePixelRatio = 1.0) = 0;

    virtual QString getInfoText() = 0;

    virtual bool isIsometric() const {
        return false;
    }
    virtual RS::IsoProjectionType getProjection() const {
        return RS::NoProjection;
    }

    int getViewportNumber() const;

    RDocument* getDocument() const;

    void setVisible(bool on);
    bool isVisible() const;

protected:
    RGraphicsView& view;

    // cached:
    mutable int visible;
};

Q_DECLARE_METATYPE(RGrid*)

#endif
