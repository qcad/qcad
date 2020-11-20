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
class RViewportData;

#ifndef RDEFAULT_QSET_INT
#define RDEFAULT_QSET_INT QSet<int>()
#endif

#ifndef RDEFAULT_TOLERANCE_1E_MIN4
#define RDEFAULT_TOLERANCE_1E_MIN4 1.0e-4
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

    friend class RStorage;

public:
    static RPropertyTypeId PropertyCustom;
    static RPropertyTypeId PropertyHandle;
    static RPropertyTypeId PropertyProtected;
    static RPropertyTypeId PropertyWorkingSet;
    static RPropertyTypeId PropertyType;
    static RPropertyTypeId PropertyBlock;
    static RPropertyTypeId PropertyLayer;
    static RPropertyTypeId PropertyLinetype;
    static RPropertyTypeId PropertyLinetypeScale;
    static RPropertyTypeId PropertyLineweight;
    static RPropertyTypeId PropertyColor;
    static RPropertyTypeId PropertyDisplayedColor;
    static RPropertyTypeId PropertyDrawOrder;

    static RPropertyTypeId PropertyMinX;
    static RPropertyTypeId PropertyMinY;
    static RPropertyTypeId PropertyMaxX;
    static RPropertyTypeId PropertyMaxY;
    static RPropertyTypeId PropertySizeX;
    static RPropertyTypeId PropertySizeY;

public:
    REntity(RDocument* document);
    REntity(const REntity& other);
    virtual ~REntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(REntity));
    }

    void setDocument(RDocument* document) {
        RObject::setDocument(document);
        getData().setDocument(document);
    }

    virtual REntity* clone() const = 0;

    virtual RS::EntityType getType() const {
        return getData().getType();
    }

    virtual bool isPointType() const {
        return getData().isPointType();
    }

    static bool isComplex(const RS::EntityType type);
    static bool isDimension(const RS::EntityType type);
    static bool isTextBased(const RS::EntityType type);

    /**
     * \return Reference to the data object of the entity.
     */
    virtual REntityData& getData() = 0;

    /**
     * \return Const reference to the data object of the entity.
     */
    virtual const REntityData& getData() const = 0;

    virtual bool isValid() const {
        return getData().isValid();
    }
    virtual bool isSane() const {
        return getData().isSane();
    }

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
    virtual bool isSelected() const {
        return getData().isSelected();
    }

    virtual void setSelected(bool on);

    /**
     * \copydoc REntityData::isSelectedWorkingSet
     */
    virtual bool isSelectedWorkingSet() const {
        return getData().isSelectedWorkingSet();
    }

    virtual void setSelectedWorkingSet(bool on) {
        getData().setSelectedWorkingSet(on);
    }

    virtual bool isUpdatesEnabled() const {
        return getData().isUpdatesEnabled();
    }

    void setUpdatesEnabled(bool on) {
        getData().setUpdatesEnabled(on);
    }

    virtual bool cloneOnChange() const {
        return getData().cloneOnChange();
    }

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
     * \copydoc REntityData::setLayerName
     */
    void setLayerName(const QString& n) {
        getData().setLayerName(n);
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
     * \copydoc REntityData::setLinetypePattern
     */
    void setLinetypePattern(const RLinetypePattern& linetypePattern) {
        getData().setLinetypePattern(linetypePattern);
    }

    /**
     * \copydoc REntityData::getLinetypeId
     */
    RLinetype::Id getLinetypeId() const {
        return getData().getLinetypeId();
    }

    RLinetype::Id getLinetypeId(bool resolve,
        const QStack<REntity*>& blockRefStack) const;

    /**
     * \copydoc REntityData::getLinetypePattern
     */
    RLinetypePattern getLinetypePattern() const {
        return getData().getLinetypePattern();
    }

    /**
     * \copydoc REntityData::setLinetypeScale
     */
    void setLinetypeScale(double linetypeScale) {
        getData().setLinetypeScale(linetypeScale);
    }

    /**
     * \copydoc REntityData::getLinetypeScale
     */
    double getLinetypeScale() const {
        return getData().getLinetypeScale();
    }

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
        const QStack<REntity*>& blockRefStack) const;

    double getLineweightInUnits(const QStack<REntity*>& blockRefStack) const;

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

    RColor getColor(const RColor& unresolvedColor, const QStack<REntity*>& blockRefStack);
    RColor getColor(bool resolve, const QStack<REntity*>& blockRefStack);

    RColor getDisplayColor() {
        return getData().getDisplayColor();
    }

    void copyAttributesFrom(const REntity* entity, bool copyBlockId=true);
    void copyAttributesFrom(const REntityData& entityData, bool copyBlockId=true);

    /**
     * \copydoc REntityData::getBoundingBox
     */
    virtual RBox getBoundingBox(bool ignoreEmpty=false) const {
        return getData().getBoundingBox(ignoreEmpty);
    }

    /**
     * \copydoc REntityData::to2D
     */
    virtual void to2D() {
        getData().to2D();
    }

    /**
     * \copydoc REntityData::setZ
     */
    virtual void setZ(double z) {
        getData().setZ(z);
    }

    /**
     * \copydoc REntityData::getBoundingBoxes
     */
    virtual QList<RBox> getBoundingBoxes(bool ignoreEmpty=false) const {
        return getData().getBoundingBoxes(ignoreEmpty);
    }

    /**
     * \copydoc REntityData::getHull
     */
    virtual RPolyline getHull(double offset) const {
        return getData().getHull(offset);
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
    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false) const {
        return getData().getShapes(queryBox, ignoreComplex, segment);
    }

    /**
     * \copydoc REntityData::getClosestShape
     */
    virtual QSharedPointer<RShape> getClosestShape(const RVector& pos, double range = RNANDOUBLE, bool ignoreComplex = false) const {
        return getData().getClosestShape(pos, range, ignoreComplex);
    }

    /**
     * \copydoc REntityData::getClosestShape
     */
    virtual QSharedPointer<RShape> getClosestSimpleShape(const RVector& pos, double range = RNANDOUBLE) const {
        return getClosestShape(pos, range, true);
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
    virtual bool isOnEntity(const RVector& point, bool limited=true, double tolerance = RDEFAULT_TOLERANCE_1E_MIN4) const {
        return getData().isOnEntity(point, limited, tolerance);
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
    virtual double getDistanceTo(const RVector& point, bool limited = true, double range = 0.0, bool draft = false, double strictRange = RMAXDOUBLE) const {
        return getData().getDistanceTo(point, limited, range, draft, strictRange);
    }

    /**
     * \copydoc REntityData::getVectorTo
     */
    virtual RVector getVectorTo(const RVector& point, bool limited = true, double strictRange = RMAXDOUBLE) const {
        return getData().getVectorTo(point, limited, strictRange);
    }

    /**
     * \copydoc REntityData::getInternalReferencePoints
     */
    virtual QList<RRefPoint> getInternalReferencePoints(RS::ProjectionRenderingHint hint=RS::RenderTop) const {
        return getData().getInternalReferencePoints(hint);
    }

    /**
     * \copydoc REntityData::getReferencePoints
     */
    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint=RS::RenderTop) const {
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
            int from = RS::FromAny,
            const RBox& queryBox = RDEFAULT_RBOX) const {
        return getData().getPointsWithDistanceToEnd(distance, from, queryBox);
    }

    /**
     * \copydoc REntityData::getIntersectionPoints(const REntity&, bool)
     */
    virtual QList<RVector> getIntersectionPoints(
            const REntity& other, bool limited = true, const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = true) const;

    /**
     * \copydoc REntityData::getIntersectionPoints(const RShape&, bool)
     */
    virtual QList<RVector> getIntersectionPoints(const RShape& shape, bool limited = true, const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = true) const;

    /**
     * Make getIntersectionPoints with shape parameter accessible for script wrappers.
     */
    virtual QList<RVector> getIntersectionPointsWithShape(const RShape& shape, bool limited = true, const RBox& queryBox = RDEFAULT_RBOX) const {
        return getIntersectionPoints(shape, limited, queryBox);
    }

    /**
     * \copydoc REntityData::clickReferencePoint
     */
    virtual bool clickReferencePoint(const RVector& referencePoint) {
        return getData().clickReferencePoint(referencePoint);
    }

    /**
     * \copydoc REntityData::moveReferencePoint
     */
    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier) {
        return getData().moveReferencePoint(referencePoint, targetPoint, modifiers);
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
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR) {
        return getData().scale(scaleFactors, center);
    }

    /**
     * \copydoc REntityData::scaleNonUniform
     */
    virtual QSharedPointer<REntity> scaleNonUniform(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR);

    /**
     * \copydoc REntityData::scale
     */
    virtual bool scale(double scaleFactor, const RVector& center = RDEFAULT_RVECTOR) {
        return getData().scale(scaleFactor, center);
    }

    virtual void scaleVisualProperties(double scaleFactor) {
        getData().scaleVisualProperties(scaleFactor);
    }

    virtual void setViewportContext(const RViewportData&) {
        // MSVC does not compile this:
        //Q_UNUSED(vp);
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
    virtual void exportEntity(RExporter& e, bool preview = false, bool forceSelected=false) const = 0;

    virtual void setAutoUpdatesBlocked(bool on) {
        getData().setAutoUpdatesBlocked(on);
    }

    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

    virtual bool setProperty(RPropertyTypeId propertyTypeId,
            const QVariant& value, RTransaction* transaction=NULL);

    virtual bool isVisible(RBlock::Id blockId = RBlock::INVALID_ID) const;
    virtual bool isEditable(bool allowInvisible = false) const;
    virtual bool isInWorkingSet() const;

    virtual int getComplexity() const {
        return 1;
    }

protected:
    /**
     * \copydoc REntityData::setParentId
     * Use RStorage::setEntityParentId instead.
     */
    void setParentId(REntity::Id parentId) {
        getData().setParentId(parentId);
    }

    virtual void print(QDebug dbg) const;
};

Q_DECLARE_METATYPE(REntity*)
Q_DECLARE_METATYPE(QSharedPointer<REntity>)
Q_DECLARE_METATYPE(QSharedPointer<REntity>*)
Q_DECLARE_METATYPE(QStack<REntity*>)
Q_DECLARE_METATYPE(QStack<REntity*>*)

#endif
