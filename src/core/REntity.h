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

#ifndef RENTITY_H
#define RENTITY_H

#include "core_global.h"

#include <QList>
#include <QStack>

#include "RBox.h"
#include "RColor.h"
#include "RDebug.h"
#include "REntityData.h"
#include "RLayer.h"
#include "RLineweight.h"
#include "RMatrix.h"
#include "RObject.h"
#include "RPropertyAttributes.h"
#include "RPropertyTypeId.h"
#include "RVector.h"
#include "RExplodable.h"

class RDocument;
class REntity;
class RBlockReferenceEntity;
class RExporter;

#ifndef RDEFAULT_QSET_INT
#define RDEFAULT_QSET_INT QSet<int>()
#endif

/**
 * Base class for all entity classes.
 *
 * Entities can be exported using an implementor of the exporter
 * interface by calling \ref exportEntity.
 *
 * \ingroup core
 * \scriptable
 * \sharedPointerSupport
 */
class QCADCORE_EXPORT REntity : public RObject {

    Q_DECLARE_TR_FUNCTIONS(REntity)

public:
    static RPropertyTypeId PropertyCustom;
    static RPropertyTypeId PropertyHandle;
    static RPropertyTypeId PropertyType;
    static RPropertyTypeId PropertyBlock;
    static RPropertyTypeId PropertyLayer;
    static RPropertyTypeId PropertyLinetype;
    static RPropertyTypeId PropertyLineweight;
    static RPropertyTypeId PropertyColor;
    static RPropertyTypeId PropertyDrawOrder;

public:
    REntity(RDocument* document, Id objectId=-1) : RObject(document, objectId) {}
    virtual ~REntity();

    static void init();

    void setDocument(RDocument* document) {
        RObject::setDocument(document);
        getData().setDocument(document);
    }

    virtual REntity* clone() const = 0;

    virtual RS::EntityType getType() const {
        return RS::EntityUnknown;
    }

    /**
     * \return Reference to the data object of the entity.
     */
    virtual REntityData& getData() = 0;

    /**
     * \return Const reference to the data object of the entity.
     */
    virtual const REntityData& getData() const = 0;

    /**
     * Reimplemented by entities that are part of a block reference but not stored
     * as part of the block definition (currently only block attributes).
     * The default implementation returns false.
     */
//    virtual bool isPartOfBlockReference(REntity::Id blockRefId) const {
//        Q_UNUSED(blockRefId)

//        return false;
//    }

    /**
     * Reimplemented by entities that do not want to be automatically painted
     */
//    virtual bool getAutoVisualize() const {
//        return true;
//    }

    /**
     * \copydoc REntityData::isSelected
     */
    bool isSelected() const {
        return getData().isSelected();
    }

    virtual void setSelected(bool on);

    /**
     * \copydoc REntityData::setDrawOrder
     */
    void setDrawOrder(int drawOrder) {
        getData().setDrawOrder(drawOrder);
    }

    /**
     * \copydoc REntityData::getDrawOrder
     */
    int getDrawOrder() const {
        return getData().getDrawOrder();
    }

    /**
     * \copydoc REntityData::setLayerId
     */
    void setLayerId(RLayer::Id layerId) {
        getData().setLayerId(layerId);
    }

    /**
     * \copydoc REntityData::getLayerId
     */
    RLayer::Id getLayerId() const {
        return getData().getLayerId();
    }

    /**
     * \copydoc REntityData::getLayerName
     */
    QString getLayerName() const {
        return getData().getLayerName();
    }

    /**
     * \copydoc REntityData::setBlockId
     */
    void setBlockId(RBlock::Id blockId) {
        getData().setBlockId(blockId);
    }

    /**
     * \copydoc REntityData::getBlockId
     */
    RBlock::Id getBlockId() const {
        return getData().getBlockId();
    }

    /**
     * \copydoc REntityData::getBlockName
     */
    QString getBlockName() const {
        return getData().getBlockName();
    }

    /**
     * \copydoc REntityData::setParentId
     */
    void setParentId(REntity::Id parentId) {
        getData().setParentId(parentId);
    }

    /**
     * \copydoc REntityData::getParentId
     */
    REntity::Id getParentId() const {
        return getData().getParentId();
    }

    /**
     * \copydoc REntityData::setLinetypeId
     */
    void setLinetypeId(RLinetype::Id linetypeId) {
        getData().setLinetypeId(linetypeId);
    }

    /**
     * \copydoc REntityData::setLinetype
     */
    void setLinetype(RLinetype linetype) {
        getData().setLinetype(linetype);
    }

    /**
     * \copydoc REntityData::getLinetypeId
     */
    RLinetype::Id getLinetypeId() const {
        return getData().getLinetypeId();
    }

    RLinetype::Id getLinetypeId(bool resolve,
        const QStack<RBlockReferenceEntity*>& blockRefStack) const;

    /**
     * \copydoc REntityData::setLineweight
     */
    void setLineweight(RLineweight::Lineweight lineweight) {
        getData().setLineweight(lineweight);
    }

    /**
     * \copydoc REntityData::getLineweight
     */
    RLineweight::Lineweight getLineweight() const {
        return getData().getLineweight();
    }

    RLineweight::Lineweight getLineweight(bool resolve,
        const QStack<RBlockReferenceEntity*>& blockRefStack) const;

    double getLineweightInUnits(const QStack<RBlockReferenceEntity*>& blockRefStack) const;

    /**
     * \copydoc REntityData::setColor
     */
    void setColor(const RColor& color) {
        getData().setColor(color);
    }

    /**
     * \copydoc REntityData::getColor
     */
    RColor getColor() const {
        return getData().getColor();
    }

    RColor getColor(bool resolve, const QStack<RBlockReferenceEntity*>& blockRefStack);

    void copyAttributesFrom(REntity* entity);

    /**
     * \copydoc REntityData::getBoundingBox
     */
    virtual RBox getBoundingBox() const {
        return getData().getBoundingBox();
    }

    /**
     * \copydoc REntityData::getBoundingBoxes
     */
    virtual QList<RBox> getBoundingBoxes(/*REntity::Id subEntityId = REntity::INVALID_ID*/) const {
        return getData().getBoundingBoxes(/*subEntityId*/);
    }

    /**
     * \copydoc REntityData::getIdBoundingBoxes
     */
//    virtual QList<QPair<REntity::Id, RBox> > getIdBoundingBoxes() const {
//        return getData().getIdBoundingBoxes();
//    }

    /**
     * \copydoc REntityData::getShapes
     */
    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX) const {
        return getData().getShapes(queryBox);
    }

    /**
     * \copydoc REntityData::getClosestShape
     */
    virtual QSharedPointer<RShape> getClosestShape(const RVector& pos, double range = RNANDOUBLE) const {
        return getData().getClosestShape(pos, range);
    }

    /**
     * \copydoc REntityData::isInside
     */
    virtual bool isInside(const RBox& box) const {
        return getData().isInside(box);
    }

    /**
     * \copydoc REntityData::isOnEntity
     */
    virtual bool isOnEntity(const RVector& point, bool limited=true) const {
        return getData().isOnEntity(point, limited);
    }

    /**
     * \copydoc REntityData::intersectsWith
     */
    virtual bool intersectsWith(const RShape& shape) const {
        return getData().intersectsWith(shape);
    }

    /**
     * \copydoc REntityData::getDistanceTo(const RVector& point)
     */
    virtual double getDistanceTo(const RVector& point, bool limited = true, double range = 0.0, bool draft = false) const {
        return getData().getDistanceTo(point, limited, range, draft);
    }

    /**
     * \copydoc REntityData::getVectorTo
     */
    virtual RVector getVectorTo(const RVector& point, bool limited = true) const {
        return getData().getVectorTo(point, limited);
    }

    /**
     * \copydoc REntityData::getInternalReferencePoints
     */
    virtual QList<RVector> getInternalReferencePoints(RS::ProjectionRenderingHint hint=RS::RenderTop) const {
        return getData().getInternalReferencePoints(hint);
    }

    /**
     * \copydoc REntityData::getReferencePoints
     */
    virtual QList<RVector> getReferencePoints(RS::ProjectionRenderingHint hint=RS::RenderTop) const {
        return getData().getReferencePoints(hint);
    }

    /**
     * \copydoc REntityData::getPointOnEntity
     */
    virtual RVector getPointOnEntity() const {
        return getData().getPointOnEntity();
    }

    /**
     * \copydoc REntityData::getEndPoints
     */
    virtual QList<RVector> getEndPoints(const RBox& queryBox = RDEFAULT_RBOX) const {
        return getData().getEndPoints(queryBox);
    }

    /**
     * \copydoc REntityData::getMiddlePoints
     */
    virtual QList<RVector> getMiddlePoints(const RBox& queryBox = RDEFAULT_RBOX) const {
        return getData().getMiddlePoints(queryBox);
    }

    /**
     * \copydoc REntityData::getCenterPoints
     */
    virtual QList<RVector> getCenterPoints(const RBox& queryBox = RDEFAULT_RBOX) const {
        return getData().getCenterPoints(queryBox);
    }

    /**
     * \copydoc REntityData::getClosestPointOnEntity
     */
    virtual RVector getClosestPointOnEntity(const RVector& point,
        double range=RNANDOUBLE, bool limited=true) const {

        return getData().getClosestPointOnEntity(point, range, limited);
    }

    /**
     * \copydoc REntityData::getPointsWithDistanceToEnd
     */
    virtual QList<RVector> getPointsWithDistanceToEnd(
            double distance,
            RS::From from = RS::FromAny,
            const RBox& queryBox = RDEFAULT_RBOX) const {
        return getData().getPointsWithDistanceToEnd(distance, from, queryBox);
    }

    /**
     * \copydoc REntityData::getIntersectionPoints(const REntity&, bool)
     */
    virtual QList<RVector> getIntersectionPoints(
            const REntity& other, bool limited = true, const RBox& queryBox = RDEFAULT_RBOX) const;

    /**
     * \copydoc REntityData::getIntersectionPoints(const RShape&, bool)
     */
    virtual QList<RVector> getIntersectionPoints(const RShape& shape, bool limited = true, const RBox& queryBox = RDEFAULT_RBOX) const;

    /**
     * \copydoc REntityData::moveReferencePoint
     */
    virtual bool moveReferencePoint(
        const RVector& referencePoint, const RVector& targetPoint) {
        return getData().moveReferencePoint(referencePoint, targetPoint);
    }

    /**
     * \copydoc REntityData::move
     */
    virtual bool move(const RVector& offset) {
        return getData().move(offset);
    }

    /**
     * \copydoc REntityData::rotate
     */
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR) {
        return getData().rotate(rotation, center);
    }

    /**
     * \copydoc REntityData::scale
     */
    virtual bool scale(const RVector& scaleFactors,
        const RVector& center = RDEFAULT_RVECTOR) {

        return getData().scale(scaleFactors, center);
    }

    /**
     * \copydoc REntityData::scale
     */
    virtual bool scale(double scaleFactor,
        const RVector& center = RDEFAULT_RVECTOR) {

        return getData().scale(scaleFactor, center);
    }

    /**
     * \copydoc REntityData::mirror
     */
    virtual bool mirror(const RLine& axis) {
        return getData().mirror(axis);
    }

    /**
     * \copydoc REntityData::mirror
     */
    virtual bool mirror(const RVector& axis1, const RVector& axis2) {
        return getData().mirror(axis1, axis2);
    }

    /**
     * \copydoc REntityData::flipHorizontal
     */
    virtual bool flipHorizontal() {
        return getData().flipHorizontal();
    }

    /**
     * \copydoc REntityData::flipVertical
     */
    virtual bool flipVertical() {
        return getData().flipVertical();
    }

    /**
     * \copydoc REntityData::stretch
     */
    virtual bool stretch(const RPolyline& area, const RVector& offset) {
        return getData().stretch(area, offset);
    }

    /**
     * \copydoc REntityData::update
     */
    void update() const {
        getData().update();
    }

    /**
     * \copydoc REntityData::castToShape
     */
    virtual RShape* castToShape() {
        return getData().castToShape();
    }

    /**
     * \nonscriptable
     */
    virtual const RShape* castToConstShape() const {
        return getData().castToConstShape();
    }

    /**
     * Exports the entity to the given exporter. The exporter might be a file
     * exporter, a graphics scene or any other platform one can export entities
     * to.
     */
    virtual void exportEntity(RExporter& e, bool preview = false) const = 0;

    // from RObject:
    virtual bool isSelectedForPropertyEditing() {
        return isSelected();
    }

    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId propertyTypeId,
            bool humanReadable = false, bool noAttributes = false);

    virtual bool setProperty(RPropertyTypeId propertyTypeId,
            const QVariant& value);

    bool isVisible() const;
    bool isEditable(bool allowInvisible = false) const;

    virtual int getComplexity() const {
        return 1;
    }

    void dump();

protected:
    virtual void print(QDebug dbg) const;
};

Q_DECLARE_METATYPE(REntity*)
Q_DECLARE_METATYPE(QSharedPointer<REntity>)
Q_DECLARE_METATYPE(QSharedPointer<REntity>*)
Q_DECLARE_METATYPE(QStack<REntity*>)

#endif
