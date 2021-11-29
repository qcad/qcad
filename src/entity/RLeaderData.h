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
#include "RPolyline.h"
#include "RTriangle.h"
#include "RVector.h"

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

    double getDimasz(bool scale = true) const {
        double v = 2.5;

        // get value from override:
        if (dimasz>0.0) {
            v = dimasz;
        }

        else if (document!=NULL) {
            QSharedPointer<RDimStyle> dimStyle = document->queryDimStyleDirect();
            if (!dimStyle.isNull()) {
                // get value from dimension style:
                v = dimStyle->getDouble(RS::DIMASZ);
            }
            else {
                // TODO: get value from document (should never happen):
                Q_ASSERT(false);
            }
        }

        if (scale) {
            v *= getDimscale();
        }

        return v;
    }

    void setDimasz(double v) {
        dimasz = v;
        update();
    }

    double getDimscale() const {
        // get value from override:
        if (dimscale>0.0) {
            return dimscale;
        }

        double v = 1.0;
        if (document!=NULL) {
            QSharedPointer<RDimStyle> dimStyle = document->queryDimStyleDirect();
            if (!dimStyle.isNull()) {
                // get value from dimension style:
                v = dimStyle->getDouble(RS::DIMSCALE);
            }
            else {
                // TODO: get value from document (should never happen):
                Q_ASSERT(false);
            }
        }

        return v;
    }

    void setDimscale(double f) {
        dimscale = f;
        update();
    }

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

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false, QList<RObject::Id>* entityIds = NULL) const;
    RTriangle getArrowShape() const;

    REntity::Id getDimLeaderBlockId() const;
    void setDimLeaderBlockId(REntity::Id id);

    virtual void update() const;

    void clearStyleOverrides() {
        dimscale = -1.0;
        dimasz = -1.0;
        update();
    }

private:
    /** Arrow head on / off */
    mutable bool arrowHead;
    /** Arrow size */
    double dimasz;
    /** Dimension scale */
    double dimscale;
    /** Block to use instead of arrow */
    RBlock::Id dimLeaderBlockId;
};

Q_DECLARE_METATYPE(RLeaderData)
Q_DECLARE_METATYPE(RLeaderData*)
Q_DECLARE_METATYPE(const RLeaderData*)
Q_DECLARE_METATYPE(QSharedPointer<RLeaderData>)

#endif
