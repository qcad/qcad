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
#include "RBlockReferenceData.h"
#include "RBlockReferenceEntity.h"
#include "RDocument.h"

RBlockReferenceData::RBlockReferenceData() :
    referencedBlockId(RBlock::INVALID_ID), rotation(0) {
}

RBlockReferenceData::RBlockReferenceData(RDocument* document,
    const RBlockReferenceData& data) {
    *this = data;
    this->document = document;
}

RBlockReferenceData::RBlockReferenceData(
        RBlock::Id referencedBlockId, const RVector& position,
        const RVector& scaleFactors, double rotation) :
        referencedBlockId(referencedBlockId),
        position(position), scaleFactors(scaleFactors), rotation(rotation) {
}

void RBlockReferenceData::setReferencedBlockName(const QString& blockName) {
    if (document == NULL) {
        qWarning("RBlockReferenceData::setReferencedBlockName(): "
                      "document is NULL");
        return;
    }

    referencedBlockId = document->getBlockId(blockName);
}

QString RBlockReferenceData::getReferencedBlockName() const {
    if (document == NULL) {
        qWarning("RBlockReferenceData::getReferencedBlockName(): "
                      "document is NULL");
        return QString();
    }
    return document->getBlockName(referencedBlockId);
}

RVector RBlockReferenceData::getVectorTo(
        const RVector& point, bool limited, double strictRange) const {

    if (document == NULL) {
        return RVector::invalid;
    }

    static int recursionDepth=0;
    if (recursionDepth++>16) {
        recursionDepth--;
        qWarning() << "RBlockReferenceData::getVectorTo: "
            << "maximum recursion depth reached: block: " << getBlockName();
        groundReferencedBlockId();
        return RVector::invalid;
    }

    QSet<REntity::Id> ids =
        document->queryBlockEntities(referencedBlockId);
    QSet<REntity::Id>::iterator it;
    double minDist = RMAXDOUBLE;
    RVector res(RVector::invalid);
    for (it = ids.begin(); it != ids.end(); it++) {
        QSharedPointer<REntity> entity = queryEntity(*it);
        if (entity.isNull()) {
            continue;
        }
        RVector v = entity->getVectorTo(point, limited);
        double dist = v.getMagnitude();
        if (dist < minDist) {
            minDist = dist;
            res = v;
        }
    }

    recursionDepth--;

    return res;
}

// 20120521: for texts in blocks:
double RBlockReferenceData::getDistanceTo(const RVector& point,
        bool limited, double range, bool draft, double strictRange) const {

    if (document == NULL) {
        return RNANDOUBLE;
    }

    static int recursionDepth=0;
    if (recursionDepth++>16) {
        recursionDepth--;
        qWarning() << "RBlockReferenceData::getDistanceTo: "
            << "maximum recursion depth reached: block: " << getBlockName();
        groundReferencedBlockId();
        return RNANDOUBLE;
    }

    QSet<REntity::Id> ids =
        document->queryBlockEntities(referencedBlockId);
    QSet<REntity::Id>::iterator it;
    double minDist = RMAXDOUBLE;
    for (it = ids.begin(); it != ids.end(); it++) {
        QSharedPointer<REntity> entity = queryEntity(*it);
        if (entity.isNull()) {
            continue;
        }
        double dist = entity->getDistanceTo(point, limited, range, draft, strictRange);
        if (RMath::isNormal(dist) && dist < minDist) {
            minDist = dist;
        }
    }

    recursionDepth--;

    return minDist;
}

RBox RBlockReferenceData::getBoundingBox(bool ignoreEmpty) const {
    if (boundingBox.isValid()) {
        return boundingBox;
    }

    if (document == NULL) {
        qWarning() << "RBlockReferenceData::getBoundingBox: document is NULL";
        return RBox();
    }

    static int recursionDepth=0;
    if (recursionDepth++>16) {
        recursionDepth--;
        qWarning() << "RBlockReferenceData::getBoundingBox: "
            << "maximum recursion depth reached: block: " << getBlockName();
        groundReferencedBlockId();
        return RBox();
    }

    QSet<REntity::Id> ids =
        document->queryBlockEntities(referencedBlockId);

    QSet<REntity::Id>::iterator it;
    for (it = ids.begin(); it != ids.end(); it++) {
        QSharedPointer<REntity> entity = queryEntity(*it);
        if (entity.isNull()) {
            continue;
        }

        RBox b = entity->getBoundingBox(ignoreEmpty);
        boundingBox.growToInclude(b);
    }

    recursionDepth--;

    return boundingBox;
}

/**
 * \return The entity with the given ID, transformed according to
 *     the transformation of this block reference.
 */
QSharedPointer<REntity> RBlockReferenceData::queryEntity(REntity::Id entityId) const {

    if (cache.contains(entityId)) {
        QSharedPointer<REntity> e = cache.value(entityId);

        // additional check if entity has been deleted:
        if (e->isUndone()) {
            return QSharedPointer<REntity> ();
        }

        // always update selection status:
        e->setSelected(isSelected());
        return e;
    }

    if (document == NULL) {
        qWarning("RBlockReferenceData::queryEntity: document is NULL");
        return QSharedPointer<REntity> ();
    }

    QSharedPointer<REntity> entity = document->queryEntity(entityId);
    if (entity.isNull()) {
        qWarning("RBlockReferenceData::queryEntity: "
            "entity %d is NULL", entityId);
        return QSharedPointer<REntity>();
    }

    // never render attribute definition as part of a block reference:
    if (entity->getType()==RS::EntityAttributeDefinition) {
        return QSharedPointer<REntity>();
    }

    if (!applyTransformationTo(*entity)) {
        return QSharedPointer<REntity>();
    }

    cache.insert(entityId, entity);

    return entity;
}

bool RBlockReferenceData::applyTransformationTo(REntity& entity) const {
    QSharedPointer<RBlock> block = document->queryBlockDirect(referencedBlockId);
    if (block.isNull()) {
        qWarning("RBlockReferenceData::applyTransformationTo: "
            "block %d is NULL", referencedBlockId);
        return false;
    }

    // nested block reference with negative scale factors (flipped):
    RBlockReferenceEntity* blockReference = dynamic_cast<RBlockReferenceEntity*>(&entity);
    if (blockReference!=NULL && scaleFactors.y<0.0) {
        blockReference->move(-block->getOrigin());
        blockReference->scale(scaleFactors);
        blockReference->rotate(-2*blockReference->getRotation(), blockReference->getPosition());
        blockReference->rotate(rotation);
        blockReference->move(position);
        return true;
    }

    entity.move(-block->getOrigin());
    entity.scale(scaleFactors);
    entity.rotate(rotation);
    entity.move(position);

    return true;
}

RVector RBlockReferenceData::mapToBlock(const RVector& v) const {
    QSharedPointer<RBlock> block = document->queryBlockDirect(referencedBlockId);
    if (block.isNull()) {
        qWarning("RBlockReferenceData::mapToBlock: "
            "block %d is NULL", referencedBlockId);
        return RVector::invalid;
    }

    RVector ret = v;

    ret.move(-position);
    ret.rotate(-rotation);
    if (fabs(scaleFactors.x)>RS::PointTolerance && fabs(scaleFactors.y)>RS::PointTolerance) {
        ret.scale(RVector(1/scaleFactors.x, 1/scaleFactors.y));
    }
    ret.move(block->getOrigin());

    return ret;
}

QList<RVector> RBlockReferenceData::getInternalReferencePoints(
        RS::ProjectionRenderingHint hint) const {

    QList<RVector> ret;

    if (document == NULL) {
        return ret;
    }

    static int recursionDepth=0;
    if (recursionDepth++>16) {
        recursionDepth--;
        qWarning() << "RBlockReferenceData::getInternalReferencePoints: "
            << "maximum recursion depth reached: block: " << getBlockName();
        groundReferencedBlockId();
        return ret;
    }

    QSet<REntity::Id> ids =
        document->queryBlockEntities(referencedBlockId);
    QSet<REntity::Id>::iterator it;
    for (it = ids.begin(); it != ids.end(); it++) {
        QSharedPointer<REntity> entity = queryEntity(*it);
        if (entity.isNull()) {
            continue;
        }
        ret.append(entity->getInternalReferencePoints(hint));
    }

    recursionDepth--;
    return ret;
}

QList<RVector> RBlockReferenceData::getReferencePoints(
        RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    QList<RVector> ret;
    ret.append(position);
    return ret;
}

QList<QSharedPointer<RShape> > RBlockReferenceData::getShapes(const RBox& queryBox, bool ignoreComplex) const {
    QList<QSharedPointer<RShape> > ret;

    static int recursionDepth=0;
    if (recursionDepth++>16) {
        recursionDepth--;
        qWarning() << "RBlockReferenceData::getShapes: "
            << "maximum recursion depth reached: block: " << getBlockName();
        groundReferencedBlockId();
        return ret;
    }

    // query entities in query box that are part of the block definition:
    QSet<REntity::Id> ids;
    if (queryBox.isValid()) {
        QList<RVector> corners = queryBox.getCorners2d();
        RVector::moveList(corners, -position);
        RVector::rotateList(corners, -rotation);
        RVector::scaleList(corners, RVector(1.0/scaleFactors.x, 1.0/scaleFactors.y));

        RBox queryBoxNeutral(RVector::getMinimum(corners), RVector::getMaximum(corners));

        ids = document->queryIntersectedEntitiesXY(queryBoxNeutral, true, true, referencedBlockId);
    }
    else {
        ids = document->queryBlockEntities(referencedBlockId);
    }

    QSet<REntity::Id>::iterator it;
    for (it = ids.begin(); it != ids.end(); it++) {
        QSharedPointer<REntity> entity = queryEntity(*it);
        if (entity.isNull()) {
            continue;
        }

        RS::EntityType t = entity->getType();

        // ignore attribute definitions since they are not rendered in the
        // context of a block reference:
        if (t==RS::EntityAttributeDefinition) {
            continue;
        }
        if (t==RS::EntityAttribute) {
            continue;
        }
        if (ignoreComplex) {
            if (REntity::isComplex(t)) {
                continue;
            }
        }

        ret.append(entity->getShapes(queryBox));
    }

    recursionDepth--;
    return ret;
}

bool RBlockReferenceData::moveReferencePoint(const RVector& referencePoint,
        const RVector& targetPoint) {

    bool ret = false;
    if (referencePoint.getDistanceTo(position) < RS::PointTolerance) {
        position = targetPoint;
        ret = true;
    }
    update();
    return ret;
}

bool RBlockReferenceData::move(const RVector& offset) {
    if (!offset.isValid() || offset.getMagnitude() < RS::PointTolerance) {
        return false;
    }
    position += offset;
    update();
    return true;
}

bool RBlockReferenceData::rotate(double rotation, const RVector& center) {
    if (fabs(rotation) < RS::AngleTolerance) {
        return false;
    }
    position.rotate(rotation, center);
    this->rotation += rotation;
    update();
    return true;
}

bool RBlockReferenceData::mirror(const RLine& axis) {
    position.mirror(axis);

    RVector vec = RVector::createPolar(1.0, rotation);
    vec.mirror(RVector(0.0,0.0), axis.endPoint-axis.startPoint);
    rotation = vec.getAngle();

    scaleFactors.y*=-1;
    update();
    return true;
}

bool RBlockReferenceData::scale(
        const RVector& scaleFactors, const RVector& center) {

    position.scale(scaleFactors, center);
    this->scaleFactors.scale(scaleFactors);
    update();
    return true;
}

void RBlockReferenceData::update() const {
    boundingBox = RBox();
    cache.clear();
}

void RBlockReferenceData::update(REntity::Id entityId) const {
    boundingBox = RBox();
    cache.remove(entityId);
}
