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

    //getBoundingBox();
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
        const RVector& point, bool limited) const {

    if (document == NULL) {
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
    return res;
}

// 20120521: for texts in blocks:
double RBlockReferenceData::getDistanceTo(const RVector& point,
        bool limited, double range, bool draft) const {

    if (document == NULL) {
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
        double dist = entity->getDistanceTo(point, limited, range, draft);
        if (dist < minDist) {
            minDist = dist;
        }
    }
    return minDist;
}

/*
RVector RBlockReferenceData::getVectorTo(const RLine& line, bool limited) const {
    if (document == NULL) {
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
        RVector v = entity->getVectorTo(line, limited);
        double dist = v.getMagnitude();
        if (dist < minDist) {
            minDist = dist;
            res = v;
        }
    }
    return res;
}
*/

RBox RBlockReferenceData::getBoundingBox() const {
    if (boundingBox.isValid()) {
        return boundingBox;
    }

    if (document == NULL) {
        qWarning() << "RBlockReferenceData::getBoundingBox: document is NULL";
        return RBox();
    }

    static int recursionDepth=0;
    recursionDepth++;

    QSet<REntity::Id> ids =
        document->queryBlockEntities(referencedBlockId);

    if (ids.isEmpty()) {
        //qWarning() << "RBlockReferenceData::getBoundingBox: empty block";
    }
    QSet<REntity::Id>::iterator it;
    for (it = ids.begin(); it != ids.end(); it++) {
        QSharedPointer<REntity> entity = queryEntity(*it);
        if (entity.isNull()) {
            continue;
        }
        RBox b = entity->getBoundingBox();
        boundingBox.growToInclude(b);
    }

    recursionDepth--;

    return boundingBox;
}

QList<RBox> RBlockReferenceData::getBoundingBoxes(/*REntity::Id subEntityId*/) const {
//    if (document == NULL) {
//        return QList<RBox>();
//    }

    QList<RBox> ret;

    // 20111119: multiple spatial index entries with the same
    // ID not supported by Navel spatial index library:
    ret << getBoundingBox();

/*
    if (subEntityId!=REntity::INVALID_ID) {
        QSharedPointer<REntity> entity = queryEntity(subEntityId);
        if (entity.isNull()) {
            continue;
        }
        ret.append(entity->getBoundingBoxes());
        return ret;
    }
    */
/*
    QSet<REntity::Id> ids = document->queryBlockEntities(referencedBlockId);
    QSet<REntity::Id>::iterator it;
    for (it = ids.begin(); it != ids.end(); it++) {
        QSharedPointer<REntity> entity = queryEntity(*it);
        if (entity.isNull()) {
            continue;
        }
        ret.append(entity->getBoundingBoxes());
    }
    */

    return ret;
}

/*
QList<QPair<REntity::Id, RBox> > RBlockReferenceData::getIdBoundingBoxes() const {

    QList<QPair<REntity::Id, RBox> > ret;

    QSet<REntity::Id> ids = document->queryBlockEntities(referencedBlockId);
    QSet<REntity::Id>::iterator it;
    for (it = ids.begin(); it != ids.end(); it++) {
        QSharedPointer<REntity> entity = queryEntity(*it);
        if (entity.isNull()) {
            continue;
        }
        ret.append(QPair(*it, entity->getBoundingBox()));
    }

    return ret;
}
*/

/**
 * \return The entity with the given ID, transformed according to
 *     the transformation of this block reference.
 */
QSharedPointer<REntity> RBlockReferenceData::queryEntity(REntity::Id entityId) const {

    if (cache.contains(entityId)) {
        QSharedPointer<REntity> e = cache.value(entityId);
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
        return QSharedPointer<REntity> ();
    }

    QSharedPointer<RBlock> block = document->queryBlockDirect(referencedBlockId);
    if (block.isNull()) {
        qWarning("RBlockReferenceData::queryEntity: "
            "block %d is NULL", referencedBlockId);
        return QSharedPointer<REntity> ();
    }

    // nested block reference with negative scale factors (flipped):
    QSharedPointer<RBlockReferenceEntity> blockReference = entity.dynamicCast<RBlockReferenceEntity>();
    if (!blockReference.isNull() && scaleFactors.y<0.0) {
        blockReference->move(-block->getOrigin());
        blockReference->scale(scaleFactors);
        blockReference->rotate(-2*blockReference->getRotation(), blockReference->getPosition());
        blockReference->rotate(rotation);
        blockReference->move(position);
        cache.insert(entityId, blockReference);
        return blockReference;
    }

    entity->move(-block->getOrigin());
    entity->scale(scaleFactors);
    entity->rotate(rotation);
    entity->move(position);

    cache.insert(entityId, entity);

    return entity;
}

QList<RVector> RBlockReferenceData::getReferencePoints(
        RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    QList<RVector> ret;
    ret.append(position);
    return ret;
}

//QList<RVector> RBlockReferenceData::getEndPoints() const {
//    QList<RVector> ret;
//    QSet<REntity::Id> ids =
//        document->queryBlockEntities(referencedBlockId);
//    QSet<REntity::Id>::iterator it;
//    for (it = ids.begin(); it != ids.end(); it++) {
//        QSharedPointer<REntity> entity = queryEntity(*it);
//        if (entity.isNull()) {
//            continue;
//        }
//        ret.append(entity->getEndPoints());
//    }
//    return ret;
//}

//QList<RVector> RBlockReferenceData::getMiddlePoints() const {
//    QList<RVector> ret;
//    QSet<REntity::Id> ids =
//        document->queryBlockEntities(referencedBlockId);
//    QSet<REntity::Id>::iterator it;
//    for (it = ids.begin(); it != ids.end(); it++) {
//        QSharedPointer<REntity> entity = queryEntity(*it);
//        if (entity.isNull()) {
//            continue;
//        }
//        ret.append(entity->getMiddlePoints());
//    }
//    return ret;
//}

//QList<RVector> RBlockReferenceData::getCenterPoints() const {
//    QList<RVector> ret;
//    QSet<REntity::Id> ids =
//        document->queryBlockEntities(referencedBlockId);
//    QSet<REntity::Id>::iterator it;
//    for (it = ids.begin(); it != ids.end(); it++) {
//        QSharedPointer<REntity> entity = queryEntity(*it);
//        if (entity.isNull()) {
//            continue;
//        }
//        ret.append(entity->getCenterPoints());
//    }
//    return ret;
//}

RVector RBlockReferenceData::getClosestPointOnEntity(
        const RVector& point, double range) const {

    RVector ret;
    double minDist = RMAXDOUBLE;
    RVector vRange2(range/2,range/2);
    RBox box(point - vRange2, point + vRange2);
    QSet<REntity::Id> ids =
        document->queryIntersectedEntitiesXY(box, true, true, referencedBlockId);
    QSet<REntity::Id>::iterator it;
    for (it = ids.begin(); it != ids.end(); it++) {
        QSharedPointer<REntity> entity = queryEntity(*it);
        if (entity.isNull()) {
            continue;
        }
        RVector v = entity->getClosestPointOnEntity(point);
        double dist = v.getDistanceTo(point);
        if (dist < minDist) {
            minDist = dist;
            ret = v;
        }
    }
    return ret;
}

QList<RVector> RBlockReferenceData::getIntersectionPoints(
    const REntity& other, bool limited) const {

    QList<RVector> ret;
    QSet<REntity::Id> ids =
        document->queryBlockEntities(referencedBlockId);
    QSet<REntity::Id>::iterator it;
    for (it = ids.begin(); it != ids.end(); it++) {
        QSharedPointer<REntity> entity = queryEntity(*it);
        if (entity.isNull()) {
            continue;
        }
        ret.append(entity->getIntersectionPoints(other, limited));
    }
    return ret;
}

//QList<RVector> RBlockReferenceData::getPointsWithDistanceToEnd(
//        double distance, const RVector& point, double range) const {

//    QList<RVector> ret;
//    QSet<REntity::Id> ids =
//        document->queryBlockEntities(referencedBlockId);
//    QSet<REntity::Id>::iterator it;
//    for (it = ids.begin(); it != ids.end(); it++) {
//        QSharedPointer<REntity> entity = queryEntity(*it);
//        if (entity.isNull()) {
//            continue;
//        }
//        ret.append(entity->getPointsWithDistanceToEnd(distance));
//    }
//    return ret;
//}

QList<QSharedPointer<RShape> > RBlockReferenceData::getShapes(const RBox& queryBox) const {
    QList<QSharedPointer<RShape> > ret;

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
        ret.append(entity->getShapes(queryBox));
    }
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
