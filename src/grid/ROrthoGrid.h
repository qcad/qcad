/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

#ifndef RORTHOGRID_H
#define RORTHOGRID_H

#include "grid_global.h"

#include "RGrid.h"

class RGraphicsView;
class RRuler;



/**
 * \brief Grid representation.
 *
 * This class is responsible for updating the grid and snapping to the grid.
 *
 * \scriptable
 * \ingroup grids
 */
class QCADGRID_EXPORT ROrthoGrid : public RGrid {
public:
    ROrthoGrid(RGraphicsView& view);
    virtual ~ROrthoGrid();

    virtual void clearCache();

    RVector snapToGrid(const RVector& positionUcs);
    virtual void update(bool force=false);
    virtual void paint();
    virtual void paintMetaGrid();
    virtual void paintCursor(const RVector& pos);

    virtual void paintRuler(RRuler& ruler);

    virtual QString getInfoText();

    QList<RVector> getIdealSpacing(int minPixelSpacing, const RVector& minSpacing);

    // This is just an idea. This might update the grid for
    // an entity that is viewed as elevation view. This might be at
    // any angle.
    //void updateGrid(REntity& entity);

    bool isIsometric() const;
    void setIsometric(bool on);

    RS::IsoProjectionType getProjection() const;
    void setProjection(RS::IsoProjectionType p);

    static QList<RVector> getIdealGridSpacing(RGraphicsView& view, int minPixelSpacing, const RVector& minSpacing);
    static bool isFractionalFormat(RS::LinearFormat linearFormat);

private:
    static double inchAutoscale(double value, double idealSpacing, RS::Unit unit);

private:
    RBox viewBox;
    RBox gridBox;
    RBox metaGridBox;
    RVector spacing;
    RVector autoSpacing;
    RVector minSpacing;
    RVector metaSpacing;
    RVector autoMetaSpacing;
    bool scaleGrid;
    int minPixelSpacing;
    QString infoText;

    // cached:
    mutable int isometric;
    mutable int projection;
};

Q_DECLARE_METATYPE(ROrthoGrid*)

#endif
