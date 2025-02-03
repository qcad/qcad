/**
 * Copyright (c) 2011-2024 by Andrew Mustun. All rights reserved.
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

#ifndef RWIPEOUTDATA_H
#define RWIPEOUTDATA_H

#include "entity_global.h"

#include "RPolylineData.h"

class RBox;
class RDocument;
class RPolyline;
class RPolylineData;
class RRefPoint;
class RVector;
class RWipeoutData;
class RWipeoutEntity;


#ifndef RDEFAULT_MIN1
#define RDEFAULT_MIN1 -1
#endif

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a wipeout entity.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RWipeoutData: public RPolylineData {

    friend class RWipeoutEntity;

protected:
    RWipeoutData(RDocument* document, const RWipeoutData& data);

public:
    RWipeoutData();
    RWipeoutData(const RPolyline& polyline);

    virtual RS::EntityType getType() const {
        return RS::EntityWipeout;
    }

    virtual QList<RBox> getBoundingBoxes(bool ignoreEmpty) const;

    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers);

    virtual double getDistanceTo(const RVector& point, bool limited = true, double range = 0.0, bool draft = false, double strictRange = RMAXDOUBLE) const;

    bool getShowFrame() const {
        return showFrame;
    }

    void setShowFrame(bool on) {
        showFrame = on;
    }

    RPolyline getBoundary() const;

private:
    bool showFrame;
};

Q_DECLARE_METATYPE(RWipeoutData)
Q_DECLARE_METATYPE(RWipeoutData*)
Q_DECLARE_METATYPE(const RWipeoutData*)
Q_DECLARE_METATYPE(QSharedPointer<RWipeoutData>)

#endif
