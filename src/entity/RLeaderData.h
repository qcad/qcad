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

#ifndef RLEADERDATA_H
#define RLEADERDATA_H

#include "entity_global.h"

#include "RDocument.h"
#include "RDimLinearData.h"
#include "RVector.h"
#include "RPolyline.h"

/**
 * Leader entity data class.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RLeaderData: public REntityData, protected RPolyline {
    friend class RLeaderEntity;

protected:
    RLeaderData(RDocument* document, const RLeaderData& data);

public:
    RLeaderData();
    RLeaderData(const RPolyline& polyline, bool arrowHead);

    virtual RS::EntityType getType() const {
        return RS::EntityLeader;
    }
    virtual RShape* castToShape() {
        return this;
    }

    double getDimasz() const;
    void setDimaszOverride(double v);

    double getDimScale(bool fromDocument=true) const;
    void setDimScaleOverride(double v);

    virtual void scaleVisualProperties(double scaleFactor);

    void setArrowHead(bool on);
    bool hasArrowHead() const {
        return arrowHead;
    }

    bool canHaveArrowHead() const;
    bool updateArrowHead() const;

//    void setPolyline(const RPolyline& polyline) {
//        *((RPolyline*)this) = polyline;
//    }

    RVector getEndPoint() const {
        return RPolyline::getEndPoint();
    }

    RVector getStartPoint() const {
        return RPolyline::getStartPoint();
    }

    int countVertices() const {
        return RPolyline::countVertices();
    }

    int countSegments() const {
        return RPolyline::countSegments();
    }

    void appendVertex(const RVector& vertex) {
        RPolyline::appendVertex(vertex);
    }

    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    QList<QSharedPointer<RShape> > getExploded(int segments = RDEFAULT_MIN1) const {
        return RPolyline::getExploded(segments);
    }

    virtual bool scale(const RVector& scaleFactors, const RVector& center);
    virtual bool stretch(const RPolyline& area, const RVector& offset);

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false) const {
        Q_UNUSED(queryBox)
        Q_UNUSED(ignoreComplex)
        Q_UNUSED(segment)

        QList<QSharedPointer<RShape> > ret;
        ret << QSharedPointer<RShape>(new RPolyline(*this));
        if (arrowHead) {
            ret << QSharedPointer<RShape>(new RTriangle(getArrowShape()));
        }
        return ret;
    }

    RTriangle getArrowShape() const;

    REntity::Id getDimLeaderBlockId() const;
    void setDimLeaderBlockId(REntity::Id id);

    virtual void update() const;

private:
    /** Arrow head on / off */
    mutable bool arrowHead;
    /** Arrow size */
    double dimaszOverride;
    /** Dimension scale */
    double dimScaleOverride;
    /** Block to use instead of arrow */
    RBlock::Id dimLeaderBlockId;
};

Q_DECLARE_METATYPE(RLeaderData)
Q_DECLARE_METATYPE(RLeaderData*)
Q_DECLARE_METATYPE(const RLeaderData*)
Q_DECLARE_METATYPE(QSharedPointer<RLeaderData>)

#endif
