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
#include "RBlockReferenceData.h"
#include "RBlockReferenceEntity.h"
#include "RDocument.h"
#include "RExporter.h"
#include "RMainWindow.h"
#include "RMouseEvent.h"
#include "RStorage.h"
#include "RTransform.h"

RBlockReferenceData::RBlockReferenceData() :
    referencedBlockId(RBlock::INVALID_ID),
    rotation(0),
    columnCount(1),
    rowCount(1),
    columnSpacing(0),
    rowSpacing(0),
    visualPropertiesScale(1.0) {
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
                QSharedPointer<REntity> entity = queryEntity(*it, true);
                if (entity.isNull()) {
                    continue;
                }
                if (col!=0 || row!=0) {
                    // entity might be from cache: clone:
                    entity = QSharedPointer<REntity>(entity->clone());
                    applyColumnRowOffsetTo(*entity, col, row, true);
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
                QSharedPointer<REntity> entity = queryEntity(*it, true);
                if (entity.isNull()) {
                    continue;
                }
                if (col!=0 || row!=0) {
                    // entity might be from cache: clone:
                    entity = QSharedPointer<REntity>(entity->clone());
                    applyColumnRowOffsetTo(*entity, col, row, true);
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

bool RBlockReferenceData::isPointType() const {
    if (document==NULL) {
        return false;
    }

    QSharedPointer<RBlock> block = document->queryBlockDirect(referencedBlockId);
    if (block.isNull()) {
        return false;
    }

    return block->isPixelUnit();
}

QList<RBox> RBlockReferenceData::getBoundingBoxes(bool ignoreEmpty) const {
    QList<RBox>* bbs;
    if (ignoreEmpty) {
        bbs = &boundingBoxesIgnoreEmpty;
    }
    else {
        bbs = &boundingBoxes;
    }

    if (!bbs->isEmpty()) {
        return *bbs;
    }

    if (document == NULL) {
        return QList<RBox>();
    }

    QSharedPointer<RBlock> block = document->queryBlockDirect(referencedBlockId);
    if (block.isNull()) {
        return QList<RBox>();
    }
    if (block->isPixelUnit()) {
        // pixel unit block:
        // bounding box is point:
        bbs->append(RBox(getPosition(), getPosition()));
        return *bbs;
    }

    static int recursionDepth=0;
    if (recursionDepth++>16) {
        recursionDepth--;
        qWarning() << "RBlockReferenceData::getBoundingBoxes: "
            << "maximum recursion depth reached: block: " << getBlockName();
        groundReferencedBlockId();
        return QList<RBox>();
    }

    // transform for whole block reference:
    QTransform blockRefTransform = getTransform();

    QSet<REntity::Id> ids = document->queryBlockEntities(referencedBlockId);

    // TODO: take into account block references in all instances of block array:
    //QSet<REntity::Id> attributeIds = document->queryChildEntities(getId(), RS::EntityAttribute);

    QSet<REntity::Id>::iterator it;
    for (int col=0; col<columnCount; col++) {
        for (int row=0; row<rowCount; row++) {
            for (it = ids.begin(); it != ids.end(); it++) {
                QSharedPointer<REntity> entity = queryEntity(*it);
                if (entity.isNull()) {
                    continue;
                }
                if (ignoreEmpty) {
                    if (!entity->isVisible()) {
                        continue;
                    }
                }

                QTransform t = blockRefTransform;
                if (col!=0 || row!=0) {
                    RVector offs = getColumnRowOffset(col, row);

                    if (RMath::fuzzyCompare(scaleFactors.x, 0.0)) {
                        offs.x = 0.0;
                    }
                    else {
                        offs.x /= scaleFactors.x;
                    }
                    if (RMath::fuzzyCompare(scaleFactors.y, 0.0)) {
                        offs.y = 0.0;
                    }
                    else {
                        offs.y /= scaleFactors.y;
                    }

                    t.translate(offs.x, offs.y);
                }

                QList<RBox> ebs = entity->getBoundingBoxes(ignoreEmpty);

                // transform bounding box according to block / row / col transformation:
                for (int i=0; i<ebs.length(); i++) {
                    RBox eb = ebs[i];
                    QList<RVector> corners = eb.getCorners();
                    for (int k=0; k<corners.length(); k++) {
                        corners[k].transform2D(t);
                    }
                    RBox b(RVector::getMinimum(corners), RVector::getMaximum(corners));
                    bbs->append(b);
                }
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

void RBlockReferenceData::to2D() {
    position.z = 0.0;
    update();
}

RVector RBlockReferenceData::getPointOnEntity() const {
    if (document == NULL) {
        return RVector::invalid;
    }

    QSet<REntity::Id> ids = document->queryBlockEntities(referencedBlockId);
    if (ids.isEmpty()) {
        return RVector::invalid;
    }

    QList<REntity::Id> idsOrdered = document->getStorage().orderBackToFront(ids);

    QList<REntity::Id>::iterator it = idsOrdered.begin();
    QSharedPointer<REntity> entity = queryEntity(*it, true);
    if (entity.isNull()) {
        return RVector::invalid;
    }

    return entity->getPointOnEntity();
}

/**
 * \return The entity with the given ID.
 *
 * \param transform Transform according to the transformation of this block reference.
 */
QSharedPointer<REntity> RBlockReferenceData::queryEntity(REntity::Id entityId, bool transform, bool ignoreAttDef) const {

    if (cache.contains(entityId) && !transform) {
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
    if (ignoreAttDef && entity->getType()==RS::EntityAttributeDefinition) {
        return QSharedPointer<REntity>();
    }

    // transform entity into (new type of) entity:
    if (transform) {
        applyTransformationTo(entity);
    }
    else {
        if (!RMath::fuzzyCompare(visualPropertiesScale, 1.0)) {
            entity->scaleVisualProperties(visualPropertiesScale);
        }
    }

    if (!transform) {
        cache.insert(entityId, entity);
    }

    return entity;
}

RVector RBlockReferenceData::getColumnRowOffset(int col, int row, bool rotated) const {
    if (col==0 && row==0) {
        return RVector(0,0);
    }

    RVector offset;
    if (RMath::fuzzyCompare(scaleFactors.x, 0.0)) {
        offset.x = 0.0;
    }
    else {
        offset.x = col*columnSpacing;
        //offset.x = col*columnSpacing/scaleFactors.x;
    }
    if (RMath::fuzzyCompare(scaleFactors.y, 0.0)) {
        offset.y = 0.0;
    }
    else {
        offset.y = row*rowSpacing;
        //offset.y = row*rowSpacing/scaleFactors.y;
    }
    if (rotated) {
        offset.rotate(rotation);
    }
    return offset;
}

void RBlockReferenceData::applyColumnRowOffsetTo(REntity& entity, int col, int row, bool rotated) const {
    if (col==0 && row==0) {
        return;
    }
    entity.move(getColumnRowOffset(col, row, rotated));
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
        if (!RMath::fuzzyCompare(visualPropertiesScale, 1.0)) {
            blockReference->scaleVisualProperties(visualPropertiesScale);
        }
        return true;
    }

    if (!RMath::fuzzyCompare(visualPropertiesScale, 1.0)) {
        entity.scaleVisualProperties(visualPropertiesScale);
    }

    entity.move(-block->getOrigin());
    entity.scale(scaleFactors, RVector());
    //entity.scale(scaleFactors, RVector(), newShapes);
    entity.rotate(rotation);
    entity.move(position);

    return true;
}

bool RBlockReferenceData::applyTransformationTo(QSharedPointer<REntity>& entity) const {
//    qDebug() << "swap";

    //QSharedPointer<REntity> e = QSharedPointer<REntity>(new RBlockReferenceEntity(entity->getDocument(), RBlockReferenceData()));
    //entity.swap(e);
    //entity = ;

    QSharedPointer<RBlock> block = document->queryBlockDirect(referencedBlockId);
    if (block.isNull()) {
        qWarning("RBlockReferenceData::applyTransformationTo: "
            "block %d is NULL", referencedBlockId);
        return false;
    }

    // nested block reference with negative scale factors (flipped):
    RBlockReferenceEntity* blockReference = dynamic_cast<RBlockReferenceEntity*>(entity.data());
    if (blockReference!=NULL && scaleFactors.y<0.0) {
        blockReference->move(-block->getOrigin());
        blockReference->scale(scaleFactors);
        blockReference->rotate(-2*blockReference->getRotation(), blockReference->getPosition());
        blockReference->rotate(rotation);
        blockReference->move(position);
        if (!RMath::fuzzyCompare(visualPropertiesScale, 1.0)) {
            blockReference->scaleVisualProperties(visualPropertiesScale);
        }
        return true;
    }

    if (!RMath::fuzzyCompare(visualPropertiesScale, 1.0)) {
        entity->scaleVisualProperties(visualPropertiesScale);
    }

    entity->move(-block->getOrigin());
    if (RMath::fuzzyCompare(scaleFactors.x, scaleFactors.y)) {
        // uniform scale:
        entity->scale(scaleFactors.x, RVector());
    }
    else if (RMath::fuzzyCompare(scaleFactors.x, -scaleFactors.y)) {
        entity->scale(scaleFactors.x, RVector());
        entity->mirror(RVector(0,0), RVector::createPolar(1.0, 0.0));
    }
    else {
        // non-uniform scale:
        QSharedPointer<REntity> e = entity->scaleNonUniform(scaleFactors, RVector());
        if (!e.isNull() && e.data()!=entity.data()) {
            entity.swap(e);
        }
    }
    entity->rotate(rotation);
    entity->move(position);

    return true;
}

RTransform RBlockReferenceData::getTransform() const {
    QSharedPointer<RBlock> block = document->queryBlockDirect(referencedBlockId);
    if (block.isNull()) {
        qWarning("RBlockReferenceData::getTransform: "
                 "block %d is NULL", referencedBlockId);
        return RTransform();
    }

    RTransform ret;
    ret.translate(position.x, position.y);
    ret.rotateRadians(rotation);
    ret.scale(scaleFactors.x, scaleFactors.y);
    ret.translate(-block->getOrigin().x, -block->getOrigin().y);
    return ret;
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

bool RBlockReferenceData::isPixelUnit() const {
    if (document==NULL) {
        return false;
    }
    QSharedPointer<RBlock> block = document->queryBlockDirect(referencedBlockId);
    if (block==NULL) {
        return false;
    }
    return block->isPixelUnit();
}

QList<RRefPoint> RBlockReferenceData::getInternalReferencePoints(RS::ProjectionRenderingHint hint) const {
    QList<RRefPoint> ret;

    QList<QSharedPointer<RShape> > shapes = getShapes();
    for (int i=0; i<shapes.size(); i++) {
        QSharedPointer<RShape> shape = shapes[i];

        QList<RVector> ps = shape->getArcReferencePoints();
        for (int k=0; k<ps.length(); k++) {
            ret.append(RRefPoint(ps[k], RRefPoint::Tertiary));
        }
    }

    return ret;

//    QList<RRefPoint> ret;


//    if (document == NULL) {
//        return ret;
//    }

//    static int recursionDepth=0;
//    if (recursionDepth++>16) {
//        recursionDepth--;
//        qWarning() << "RBlockReferenceData::getInternalReferencePoints: "
//            << "maximum recursion depth reached: block: " << getBlockName();
//        groundReferencedBlockId();
//        return ret;
//    }

//    // transform for whole block reference:
//    QTransform blockRefTransform = getTransform();

//    QSet<REntity::Id> ids = document->queryBlockEntities(referencedBlockId);
//    QSet<REntity::Id>::iterator it;
//    for (it = ids.begin(); it != ids.end(); it++) {
//        QSharedPointer<REntity> entity = queryEntity(*it);
//        if (entity.isNull()) {
//            continue;
//        }

//        // transform ref points:
//        QList<RRefPoint> refPoints = entity->getInternalReferencePoints(hint);
//        for (int i=0; i<refPoints.length(); i++) {
//            RRefPoint refPoint = refPoints[i];
//            refPoint.transform2D(blockRefTransform);
//            ret.append(refPoint);
//        }
//    }

//    recursionDepth--;
//    return ret;
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

/**
 * Block shapes, transformed.
 */
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
    bool isUniform = RMath::fuzzyCompare(scaleFactors.x, scaleFactors.y);

    RBox queryBoxBlockCoordinates;
    if (queryBox.isValid()) {
        if (isUniform) {
            // query box optimization only available for uniform scales:
            queryBoxBlockCoordinates = getQueryBoxInBlockCoordinates(queryBox);
            //qDebug() << "queryBoxBlockCoordinates:" << queryBoxBlockCoordinates;
        }
    }

    // query entities in query box that are part of the block definition:
    // ignore query box for block arrays:
    QSet<REntity::Id> ids;
    if (queryBoxBlockCoordinates.isValid() && !isArray) {
//        QList<RVector> corners = queryBox.getCorners2d();
//        RVector::moveList(corners, -position);
//        RVector::rotateList(corners, -rotation);
//        RVector::scaleList(corners, RVector(1.0/scaleFactors.x, 1.0/scaleFactors.y));
//        RBox queryBoxNeutral(RVector::getMinimum(corners), RVector::getMaximum(corners));
        //RBox queryBoxNeutral = getQueryBoxInBlockCoordinates(queryBox);
        ids = document->queryIntersectedEntitiesXY(queryBoxBlockCoordinates, true, true, referencedBlockId);
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

                QSharedPointer<REntity> entity = queryEntity(*it, true);
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

                if (isArray) {
                    if (col>0 || row>0) {
                        // entity might be from cache:
                        // clone and transform to col / row coordinates:
                        entity = QSharedPointer<REntity>(entity->clone());
                        applyColumnRowOffsetTo(*entity, col, row, true);
                    }

                    // bounding box check for arrays:
                    if (queryBoxBlockCoordinates.isValid()) {
                        if (!queryBoxBlockCoordinates.intersects(entity->getBoundingBox())) {
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

bool RBlockReferenceData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    Q_UNUSED(modifiers)

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

    if (!isPixelUnit()) {
        this->rotation += rotation;
    }
    update();
    return true;
}

bool RBlockReferenceData::mirror(const RLine& axis) {
    position.mirror(axis);

    if (!isPixelUnit()) {
        RVector vec = RVector::createPolar(1.0, rotation);
        vec.mirror(RVector(0.0,0.0), axis.endPoint-axis.startPoint);
        rotation = vec.getAngle();

        scaleFactors.y*=-1;
    }
    update();
    return true;
}

bool RBlockReferenceData::scale(const RVector& scaleFactors, const RVector& center) {
    position.scale(scaleFactors, center);
    columnSpacing*=scaleFactors.x;
    rowSpacing*=scaleFactors.x;

    if (!isPixelUnit()) {
        this->scaleFactors.scale(scaleFactors);
    }
    update();
    return true;
}

void RBlockReferenceData::scaleVisualProperties(double scaleFactor) {
    visualPropertiesScale = scaleFactor;
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
