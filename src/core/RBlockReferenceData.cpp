/**
 * Copyright (c) 2011-2017 by Andrew Mustun. All rights reserved.
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
#include "RMainWindow.h"
#include "RMouseEvent.h"

RBlockReferenceData::RBlockReferenceData() :
    referencedBlockId(RBlock::INVALID_ID),
    rotation(0),
    columnCount(1),
    rowCount(1),
    columnSpacing(0),
    rowSpacing(0) {
}

RBlockReferenceData::RBlockReferenceData(RDocument* document,
    const RBlockReferenceData& data) {
    *this = data;
    this->document = document;
}

RBlockReferenceData::RBlockReferenceData(
        RBlock::Id referencedBlockId, const RVector& position,
        const RVector& scaleFactors, double rotation,
        int columnCount, int rowCount,
        double columnSpacing, double rowSpacing) :
        referencedBlockId(referencedBlockId),
        position(position),
        scaleFactors(scaleFactors),
        rotation(rotation),
        columnCount(columnCount),
        rowCount(rowCount),
        columnSpacing(columnSpacing),
        rowSpacing(rowSpacing) {
}

void RBlockReferenceData::setReferencedBlockName(const QString& blockName) {
    if (document == NULL) {
        qWarning("RBlockReferenceData::setReferencedBlockName(): "
                      "document is NULL");
        return;
    }

    referencedBlockId = document->getBlockId(blockName);
    update();
}

QString RBlockReferenceData::getReferencedBlockName() const {
    if (document == NULL) {
        qWarning("RBlockReferenceData::getReferencedBlockName(): "
                      "document is NULL");
        return QString();
    }
    return document->getBlockName(referencedBlockId);
}

RVector RBlockReferenceData::getVectorTo(const RVector& point, bool limited, double strictRange) const {
    Q_UNUSED(strictRange)

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

    QSet<REntity::Id> ids = document->queryBlockEntities(referencedBlockId);
    QSet<REntity::Id>::iterator it;
    double minDist = RMAXDOUBLE;
    RVector res(RVector::invalid);

    // TODO: narrow down col / row using bounding boxes

    for (int col=0; col<columnCount; col++) {
        for (int row=0; row<rowCount; row++) {
            for (it = ids.begin(); it != ids.end(); it++) {
                QSharedPointer<REntity> entity = queryEntity(*it);
                if (entity.isNull()) {
                    continue;
                }
                if (col!=0 || row!=0) {
                    // entity might be from cache: clone:
                    entity = QSharedPointer<REntity>(entity->clone());
                    applyColumnRowOffsetTo(*entity, col, row);
                }
                RVector v = entity->getVectorTo(point, limited);
                double dist = v.getMagnitude();
                if (dist < minDist) {
                    minDist = dist;
                    res = v;
                }
            }
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

    bool isArray = (columnCount!=1 || rowCount!=1);

    QSet<REntity::Id> ids;
    if (range<RS::PointTolerance || isArray) {
        ids = document->queryBlockEntities(referencedBlockId);
    }
    else {
        RBox qb = getQueryBoxInBlockCoordinates(RBox(point, range));
        ids = document->queryIntersectedEntitiesXY(qb, true, true, referencedBlockId);
    }

    if (ids.isEmpty()) {
        recursionDepth--;
        return RNANDOUBLE;
    }

    QSet<REntity::Id>::iterator it;
    double minDist = RNANDOUBLE;
    for (int col=0; col<columnCount; col++) {
        for (int row=0; row<rowCount; row++) {
            for (it = ids.begin(); it != ids.end(); it++) {
                QSharedPointer<REntity> entity = queryEntity(*it);
                if (entity.isNull()) {
                    continue;
                }
                if (col!=0 || row!=0) {
                    // entity might be from cache: clone:
                    entity = QSharedPointer<REntity>(entity->clone());
                    applyColumnRowOffsetTo(*entity, col, row);
                }
                // TODO: range might have to be scaled here:
                double dist = entity->getDistanceTo(point, limited, range, draft, strictRange);

                if (!RMath::isNormal(dist)) {
                    continue;
                }

                if (dist < minDist || RMath::isNaN(minDist)) {
                    minDist = dist;
                }
            }
        }
    }

    recursionDepth--;

    return minDist;
}

QList<RBox> RBlockReferenceData::getBoundingBoxes(bool ignoreEmpty) const {
    QList<RBox>* bbs;
    if (ignoreEmpty) {
        bbs = &boundingBoxes;
    }
    else {
        bbs = &boundingBoxesIgnoreEmpty;
    }

    if (!bbs->isEmpty()) {
        return *bbs;
    }

    if (document == NULL) {
        qWarning() << "RBlockReferenceData::getBoundingBox: document is NULL";
        return QList<RBox>();
    }

    static int recursionDepth=0;
    if (recursionDepth++>16) {
        recursionDepth--;
        qWarning() << "RBlockReferenceData::getBoundingBoxes: "
            << "maximum recursion depth reached: block: " << getBlockName();
        groundReferencedBlockId();
        return QList<RBox>();
    }

    QSet<REntity::Id> ids = document->queryBlockEntities(referencedBlockId);

//    RBox baseBBox;
//    QSet<REntity::Id>::iterator it;
//    for (it = ids.begin(); it != ids.end(); it++) {
//        QSharedPointer<REntity> entity = queryEntity(*it);
//        if (entity.isNull()) {
//            continue;
//        }

//        RBox b = entity->getBoundingBox(ignoreEmpty);
//        baseBBox.growToInclude(b);
//    }

//    if (columnCount==1 && rowCount==1) {
//        boundingBoxes.append(baseBBox);
//    }
//    else {
//        // add bounding boxes for rows and columns:
//        for (int col=0; col<columnCount; col++) {
//            for (int row=0; row<rowCount; row++) {
//                RVector offset = getColumnRowOffset(col, row);
//                RBox b = baseBBox;
//                b.c1 += offset;
//                b.c2 += offset;
//                boundingBoxes.append(b);
//            }
//        }
//    }

    QSet<REntity::Id>::iterator it;
    for (int col=0; col<columnCount; col++) {
        for (int row=0; row<rowCount; row++) {
            for (it = ids.begin(); it != ids.end(); it++) {
                QSharedPointer<REntity> entity = queryEntity(*it);
                if (entity.isNull()) {
                    continue;
                }
                if (col!=0 || row!=0) {
                    // entity might be from cache: clone:
                    entity = QSharedPointer<REntity>(entity->clone());
                    applyColumnRowOffsetTo(*entity, col, row);
                }
                entity->update();
                bbs->append(entity->getBoundingBoxes(ignoreEmpty));
            }
        }
    }

    if (!ignoreEmpty) {
        if (bbs->isEmpty()) {
            // add reference point to bounding boxes for empty block:
            bbs->append(RBox(position, 0.0));
        }
    }

    recursionDepth--;

    return *bbs;
}

RBox RBlockReferenceData::getBoundingBox(bool ignoreEmpty) const {
    RBox ret;
    ret.growToIncludeBoxes(getBoundingBoxes(ignoreEmpty));
    return ret;
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

RVector RBlockReferenceData::getColumnRowOffset(int col, int row) const {
    if (col==0 && row==0) {
        return RVector(0,0);
    }

    RVector offset(col*columnSpacing, row*rowSpacing);
    offset.rotate(rotation);
    return offset;
}

void RBlockReferenceData::applyColumnRowOffsetTo(REntity& entity, int col, int row) const {
    if (col==0 && row==0) {
        return;
    }
    entity.move(getColumnRowOffset(col, row));
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

QList<RRefPoint> RBlockReferenceData::getInternalReferencePoints(RS::ProjectionRenderingHint hint) const {
    QList<RRefPoint> ret;

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

    QSet<REntity::Id> ids = document->queryBlockEntities(referencedBlockId);
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

QList<RRefPoint> RBlockReferenceData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    QList<RRefPoint> ret;
    RRefPoint rp(position);
    if (RSettings::getIgnoreBlockReferencePoint()) {
        rp.setIgnore(true);
    }
    ret.append(rp);

    return ret;
}

RBox RBlockReferenceData::getQueryBoxInBlockCoordinates(const RBox& box) const {
    QList<RVector> corners = box.getCorners2d();
    RVector::moveList(corners, -position);
    RVector::rotateList(corners, -rotation);
    RVector::scaleList(corners, RVector(1.0/scaleFactors.x, 1.0/scaleFactors.y));
    if (document!=NULL) {
        QSharedPointer<RBlock> block = document->queryBlockDirect(referencedBlockId);
        if (!block.isNull()) {
            RVector::moveList(corners, block->getOrigin());
        }
    }
    return RBox(RVector::getMinimum(corners), RVector::getMaximum(corners));
}

QList<QSharedPointer<RShape> > RBlockReferenceData::getShapes(const RBox& queryBox, bool ignoreComplex, bool segment) const {
    Q_UNUSED(segment)

    QList<QSharedPointer<RShape> > ret;

    static int recursionDepth=0;
    if (recursionDepth++>16) {
        recursionDepth--;
        qWarning() << "RBlockReferenceData::getShapes: "
            << "maximum recursion depth reached: block: " << getBlockName();
        groundReferencedBlockId();
        return ret;
    }

    bool isArray = (columnCount!=1 || rowCount!=1);

    // query entities in query box that are part of the block definition:
    // ignore query box for block arrays:
    QSet<REntity::Id> ids;
    if (queryBox.isValid() && !isArray) {
//        QList<RVector> corners = queryBox.getCorners2d();
//        RVector::moveList(corners, -position);
//        RVector::rotateList(corners, -rotation);
//        RVector::scaleList(corners, RVector(1.0/scaleFactors.x, 1.0/scaleFactors.y));
//        RBox queryBoxNeutral(RVector::getMinimum(corners), RVector::getMaximum(corners));
        RBox queryBoxNeutral = getQueryBoxInBlockCoordinates(queryBox);
        //qDebug() << "queryBoxNeutral:" << queryBoxNeutral;

        ids = document->queryIntersectedEntitiesXY(queryBoxNeutral, true, true, referencedBlockId);
    }
    else {
        ids = document->queryBlockEntities(referencedBlockId);
    }

    QSet<REntity::Id>::iterator it;

    for (int col=0; col<columnCount; col++) {
        for (int row=0; row<rowCount; row++) {
            for (it = ids.begin(); it != ids.end(); it++) {
                if (RMouseEvent::hasMouseMoved()) {
                    recursionDepth--;
                    return QList<QSharedPointer<RShape> >();
                }

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

                // ignore complex entities for operations like snap (hatches, texts):
                if (ignoreComplex && REntity::isComplex(t)) {
                    continue;
                }

                if (isArray && (col>0 || row>0)) {
                    // entity might be from cache: clone:
                    entity = QSharedPointer<REntity>(entity->clone());
                    applyColumnRowOffsetTo(*entity, col, row);

                    // bounding box check for arrays:
                    if (queryBox.isValid()) {
                        if (!queryBox.intersects(entity->getBoundingBox())) {
                            continue;
                        }
                    }
                }
                ret.append(entity->getShapes(queryBox, ignoreComplex));
            }
        }
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

bool RBlockReferenceData::scale(const RVector& scaleFactors, const RVector& center) {
    position.scale(scaleFactors, center);
    this->scaleFactors.scale(scaleFactors);
    update();
    return true;
}

void RBlockReferenceData::setReferencedBlockId(RBlock::Id blockId) {
    referencedBlockId = blockId;
    update();
}

void RBlockReferenceData::groundReferencedBlockId() const {
    RMainWindow* mainWindow = RMainWindow::getMainWindow();
    if (mainWindow!=NULL) {
        mainWindow->handleUserWarning(QT_TRANSLATE_NOOP("REntity", "Circular (recursive) block referencing detected:"));
        if (document!=NULL) {
            mainWindow->handleUserWarning(QT_TRANSLATE_NOOP("REntity", "Block name:") + QString(" ") + document->getBlockName(referencedBlockId));
        }
    }

    referencedBlockId = RBlock::INVALID_ID;
}

void RBlockReferenceData::setPosition(const RVector& p) {
    position = p;
    update();
}

void RBlockReferenceData::setScaleFactors(const RVector& sf) {
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
    update();
}

void RBlockReferenceData::setRotation(double r) {
    rotation = r;
    update();
}

void RBlockReferenceData::update() const {
    boundingBoxes.clear();
    boundingBoxesIgnoreEmpty.clear();
    cache.clear();
}

void RBlockReferenceData::update(REntity::Id entityId) const {
    boundingBoxes.clear();
    boundingBoxesIgnoreEmpty.clear();
    cache.remove(entityId);
}
