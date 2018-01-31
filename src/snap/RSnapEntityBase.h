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

#ifndef RSNAPENTITYBASE_H
#define RSNAPENTITYBASE_H

#include "snap_global.h"

#include "RSnap.h"
#include "RGraphicsView.h"

class RMouseEvent;

/**
 * \brief Base class for entity based snap classes.
 *
 * \scriptable
 *
 * \ingroup snap
 */
class QCADSNAP_EXPORT RSnapEntityBase : public RSnap {
public:
    RSnapEntityBase(RSnap::Status s) : RSnap(s) {}
    virtual ~RSnapEntityBase() {}

    virtual RVector snap(
            const RVector& position,
            RGraphicsView& view,
            double range=RNANDOUBLE);

    virtual RVector snap(
            const RVector& position,
            RGraphicsView& view,
            const QSet<REntity::Id>& candidates,
            const RBox& queryBox);

protected:
    virtual QList<RVector> snapEntity(
            QSharedPointer<REntity> entity,
            const RVector& point,
            const RBox& queryBox,
            RGraphicsView& view) = 0;
};

Q_DECLARE_METATYPE(RSnapEntityBase*)

#endif
