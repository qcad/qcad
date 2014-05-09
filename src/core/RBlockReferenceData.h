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

#ifndef RBLOCKREFERENCEDATA_H
#define RBLOCKREFERENCEDATA_H

#include "core_global.h"

#include "RBox.h"
#include "REntity.h"
#include "RVector.h"
#include "RBlock.h"

class RDocument;

/**
 * Defines the geometry and appearance of a block reference entity.
 *
 * \scriptable
 * \ingroup core
 */
class QCADCORE_EXPORT RBlockReferenceData: public REntityData {

friend class RBlockReferenceEntity;

protected:
    RBlockReferenceData(RDocument* document, const RBlockReferenceData& data);

public:
    RBlockReferenceData();
    RBlockReferenceData(RBlock::Id referencedBlockId,
            const RVector& position, const RVector& scaleFactors, double angle);

    virtual RBox getBoundingBox() const;

    virtual QList<RVector> getInternalReferencePoints(
        RS::ProjectionRenderingHint hint = RS::RenderTop) const;
    virtual QList<RVector> getReferencePoints(
        RS::ProjectionRenderingHint hint = RS::RenderTop) const;
    virtual RVector getVectorTo(const RVector& point, 
        bool limited = true) const;
    virtual double getDistanceTo(const RVector& point,
        bool limited = true, double range = 0.0, bool draft = false) const;

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX) const;

    //virtual void setSelected(bool on);

    virtual bool moveReferencePoint(const RVector& referencePoint, 
        const RVector& targetPoint);
    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool mirror(const RLine& axis);
    virtual bool scale(const RVector& scaleFactors,
                       const RVector& center = RDEFAULT_RVECTOR);

    void setReferencedBlockId(RBlock::Id blockId) {
        referencedBlockId = blockId;
    }

    void groundReferencedBlockId() const {
        referencedBlockId = RBlock::INVALID_ID;
    }

    RBlock::Id getReferencedBlockId() const {
        return referencedBlockId;
    }

    void setReferencedBlockName(const QString& blockName);
    QString getReferencedBlockName() const;

    RVector getPosition() const {
        return position;
    }

    void setPosition(const RVector& p) {
        position = p;
    }

    RVector getScaleFactors() const {
        return scaleFactors;
    }

    void setScaleFactors(const RVector& sf) {
        scaleFactors = sf;
        if (fabs(scaleFactors.x) < RS::PointTolerance) {
            scaleFactors.x = 1.0;
        }
        if (fabs(scaleFactors.y) < RS::PointTolerance) {
            scaleFactors.y = 1.0;
        }
        if (fabs(scaleFactors.z) < RS::PointTolerance) {
            scaleFactors.z = 1.0;
        }
    }

    double getRotation() const {
        return rotation;
    }

    void setRotation(double r) {
        rotation = r;
    }

    virtual void update() const;
    virtual void update(RObject::Id entityId) const;

    QSharedPointer<REntity> queryEntity(REntity::Id entityId) const;
    bool applyTransformationTo(REntity& entity) const;
    RVector mapToBlock(const RVector& v) const;

private:
    mutable RBlock::Id referencedBlockId;
    RVector position;
    RVector scaleFactors;
    double rotation;
    mutable RBox boundingBox;
    mutable QMap<REntity::Id, QSharedPointer<REntity> > cache;
};

Q_DECLARE_METATYPE(RBlockReferenceData*)
Q_DECLARE_METATYPE(const RBlockReferenceData*)
Q_DECLARE_METATYPE(QSharedPointer<RBlockReferenceData>)

#endif
