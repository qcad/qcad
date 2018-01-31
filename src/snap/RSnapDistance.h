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

#ifndef RSNAPDISTANCE_H
#define RSNAPDISTANCE_H

#include "snap_global.h"

#include "REntity.h"
#include "RSnapEntityBase.h"

class RGraphicsView;
class RMouseEvent;

/**
 * \brief Distance snapper implementation.
 *
 * \scriptable
 * \generateScriptShell
 *
 * \ingroup snap
 */
class QCADSNAP_EXPORT RSnapDistance : public RSnapEntityBase {
public:
    RSnapDistance() : RSnapEntityBase(RSnap::Distance), distance(1.0) {}
    virtual ~RSnapDistance() {}

    virtual void showUiOptions();
    virtual void hideUiOptions();
    virtual void setDistance(double d);

protected:
    virtual QList<RVector> snapEntity(
            QSharedPointer<REntity> entity,
            const RVector& point,
            const RBox& queryBox,
            RGraphicsView& view);

private:
    double distance;
};

Q_DECLARE_METATYPE(RSnapDistance*)

#endif
