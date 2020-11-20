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

#ifndef RENTITYDATA_H
#define RENTITYDATA_H

#include "core_global.h"

#include <QList>
#include <QStack>

#include "RBlock.h"
#include "RBox.h"
#include "RColor.h"
#include "RLayer.h"
#include "RLine.h"
#include "RMatrix.h"
#include "RObject.h"
#include "RPolyline.h"
#include "RRefPoint.h"
#include "RSettings.h"
#include "RView.h"

class RBlockReferenceEntity;
class RDocument;
class REntity;
class RExporter;

#ifndef RDEFAULT_QSET_INT
#define RDEFAULT_QSET_INT QSet<int>()
#endif

#ifndef RDEFAULT_TOLERANCE_1E_MIN4
#define RDEFAULT_TOLERANCE_1E_MIN4 1.0e-4
#endif

/**
 * Base class for all entity data classes. Such classes are
 * used to separate functionality from data. Data objects may
 * for example be used to perform certain calculations. A
 * custom entity might use the same data class as a standard
 * entity to provide similar behavior (e.g. a wall might
 * behave similar like a line entity).
 *
 * \TODO derive from RObjectData with flags for selection status etc.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup core
 */
class QCADCORE_EXPORT REntityData {

    friend class REntity;

public:
    REntityData(RDocument* document=NULL);

    virtual ~REntityData() {}

    RDocument* getDocument() {
        return document;
    }

    const RDocument* getDocument() const {
        return document;
    }

    void setDocument(RDocument* document) {
        this->document = document;
    }

    virtual RS::EntityType getType() const {
        return RS::EntityUnknown;
    }

    /**
     * \return True if entity is of point nature (point, pixel based block).
     */
    virtual bool isPointType() const {
        return false;
    }

    virtual bool isValid() const {
        return true;
    }
    virtual bool isSane() const {
        return true;
    }

    /**
     * \return Shapes that represent the geometry of this entity.
     *
     * \param queryBox Limit returned shapes to query box
     * \param ignoreComplex Ignore complex shapes and explode those into simple shapes
     * \param segment Split up splines into spline segments
     */
    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false) const {
        Q_UNUSED(queryBox)
        Q_UNUSED(ignoreComplex)
        Q_UNUSED(segment)

        return QList<QSharedPointer<RShape> >();
    }

    /**
     * \return The one shape that is part of this entity which is the
     *      closest to the given position.
     */
    virtual QSharedPointer<RShape> getClosestShape(const RVector& pos, double range = RNANDOUBLE, bool ignoreComplex = false) const;

    virtual RShape* castToShape() {
        return NULL;
    }

    /**
     * \nonscriptable
     */
    virtual const RShape* castToConstShape() const {
        return const_cast<REntityData*>(this)->castToShape();
    }

    virtual RBox getBoundingBox(bool ignoreEmpty=false) const;

    void copyAttributesFrom(const REntityData& entityData, bool copyBlockId = true);

    virtual void to2D();
    virtual void setZ(double z);

    /**
     * \return List of bounding boxes that contain this entity.
     * This is used for complex entities such as block references
     * to further optimize algorithms that depend on bounding boxes
     * (e.g. spatial index algorithms). The default implementation
     * returns the bounding box that contains the whole entity.
     */
    virtual QList<RBox> getBoundingBoxes(bool ignoreEmpty=false) const {
        return QList<RBox>() << getBoundingBox(ignoreEmpty);
    }

    virtual RPolyline getHull(double offset) const;

    /**
     * \return True if the entity caches are updated when the entity is being exported.
     */
    virtual bool isUpdatesEnabled() const {
        return updatesEnabled;
    }

    /**
     * Enables / disables cache updates.
     */
    void setUpdatesEnabled(bool on) {
        updatesEnabled = on;
    }

    /**
     * Reimplement to force clone on change in transactions.
     */
    virtual bool cloneOnChange() const {
        return false;
    }

    /**
     * \return True if the entity is currently selected. This can for example
     *      influence the color in which the entity is exported.
     */
    virtual bool isSelected() const {
        return selectionStatus;
    }

    /**
     * Selects or deselects this entity.
     */
    virtual void setSelected(bool on) {
        selectionStatus = on;
    }

    /**
     * \return True if the entity is currently selected to be added to the working set.
     */
    virtual bool isSelectedWorkingSet() const {
        return selectionStatusWorkingSet;
    }

    /**
     * Selects or deselects this entity for addition to the current working set.
     */
    virtual void setSelectedWorkingSet(bool on) {
        selectionStatusWorkingSet = on;
    }

    /**
     * \return The draw order of this entity. Entities are usually drawn in
     * ascending order of this number.
     */
    virtual int getDrawOrder() const {
        return drawOrder;
    }

    /**
     * Sets the draw order of this entity.
     */
    virtual void setDrawOrder(int drawOrder) {
        this->drawOrder = drawOrder;
    }

    virtual void setLayerId(RLayer::Id layerId) {
        this->layerId = layerId;
    }

    RLayer::Id getLayerId() const {
        return layerId;
    }

    void setLayerName(const QString& layerName);
    QString getLayerName() const;

    virtual void setBlockId(RBlock::Id blockId) {
        this->blockId = blockId;
    }

    RBlock::Id getBlockId() const {
        return blockId;
    }

    virtual void setParentId(RObject::Id parentId) {
        this->parentId = parentId;
    }

    /**
     * \return ID of parent entity (block reference for block attribute).
     */
    RObject::Id getParentId() const {
        return parentId;
    }

    QString getBlockName() const;

    /**
     * Sets the linetype of this entity to the given linetype ID.
     * \see RDocument::getLinetypeId
     */
    virtual void setLinetypeId(RLinetype::Id linetypeId) {
        this->linetypeId = linetypeId;
    }

    /**
     * \return Linetype ID of this entity. Note that this might be ByLayer or ByBlock.
     */
    virtual RLinetype::Id getLinetypeId() const {
        return linetypeId;
    }

    virtual void setLinetypePattern(const RLinetypePattern& p);
    virtual RLinetypePattern getLinetypePattern() const;

    virtual RLinetype::Id getLinetypeId(bool resolve,
        const QStack<REntity*>& blockRefStack) const;

    virtual void setLinetypeScale(double linetypeScale) {
        this->linetypeScale = linetypeScale;
    }

    virtual double getLinetypeScale() const {
        return linetypeScale;
    }

    virtual RLineweight::Lineweight getLineweight() const {
        return lineweight;
    }

    virtual RLineweight::Lineweight getLineweight(bool resolve,
        const QStack<REntity*>& blockRefStack) const;

    double getLineweightInUnits(const QStack<REntity*>& blockRefStack) const;

    void setLineweight(RLineweight::Lineweight lineweight) {
        this->lineweight = lineweight;
//        if (RSettings::getAutoScaleLinetypePattern()) {
//            this->linetypeScale = lineweight;
//        }
    }

    void setColor(const RColor& color) {
        this->color = color;
    }

    virtual RColor getColor() const {
        return color;
    }

    virtual RColor getColor(const RColor& unresolvedColor, const QStack<REntity *>& blockRefStack) const;
    virtual RColor getColor(bool resolve, const QStack<REntity *>& blockRefStack) const;

    virtual RColor getDisplayColor() {
        QStack<REntity*> stack;
        return getColor(true, stack);
    }

    /**
     * Can be overwritten to return internal, resolved reference points.
     * This is used for example for block references in combination with
     * snap to reference points.
     * Default implementation returns same as getReferencePoints().
     */
    virtual QList<RRefPoint> getInternalReferencePoints(RS::ProjectionRenderingHint hint=RS::RenderTop) const {
        return getReferencePoints(hint);
    }

    /**
     * \return Vector of reference points of this entity. Reference points
     *      can usually be moved around by the user to change the geometry
     *      of the entity.
     */
    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint=RS::RenderTop) const = 0;

    virtual RVector getPointOnEntity() const;
    virtual QList<RVector> getEndPoints(const RBox& queryBox = RDEFAULT_RBOX) const;
    virtual QList<RVector> getMiddlePoints(const RBox& queryBox = RDEFAULT_RBOX) const;
    virtual QList<RVector> getCenterPoints(const RBox& queryBox = RDEFAULT_RBOX) const;
    virtual QList<RVector> getArcReferencePoints(const RBox& queryBox = RDEFAULT_RBOX) const;
    virtual QList<RVector> getPointsWithDistanceToEnd(
        double distance, int from = RS::FromAny, const RBox& queryBox = RDEFAULT_RBOX) const;

    virtual RVector getClosestPointOnEntity(const RVector& point,
        double range=RNANDOUBLE, bool limited=true) const;

//    /**
//     * Override to disable intersection point
//     */
//    virtual bool intersectionsEnabled() {
//        return true;
//    }

    virtual QList<RVector> getIntersectionPoints(
            const REntityData& other, bool limited = true, bool same = false,
            const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = true) const;
    virtual QList<RVector> getIntersectionPoints(
            const RShape& shape, bool limited = true,
            const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = true) const;

    virtual RVector getVectorTo(const RVector& point, bool limited=true, double strictRange = RMAXDOUBLE) const;

    virtual double getDistanceTo(const RVector& point, bool limited = true, double range = 0.0, bool draft = false, double strictRange = RMAXDOUBLE) const;

    /**
     * \return True if this entity is completely inside the given box,
     *     false otherwise. Only geometry is accounted for, not the line width.
     */
    virtual bool isInside(const RBox& box) const {
        return box.contains(getBoundingBox());
    }

    virtual bool isOnEntity(const RVector& point, bool limited = true, double tolerance = RDEFAULT_TOLERANCE_1E_MIN4) const;

    virtual bool intersectsWith(const RShape& shape) const;

    /**
     * Called when user clicks a reference point.
     *
     * \return True if clicking the reference point had any immediate effect.
     */
    virtual bool clickReferencePoint(const RVector& referencePoint) {
        Q_UNUSED(referencePoint)
        return false;
    }

    /**
     * Moves the given reference point to the given target point or does nothing
     * if this entity has no reference point as the given location.
     *
     * \return True if a reference point has been moved successfully,
     *        false otherwise.
     */
    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier) = 0;

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool scale(double scaleFactor, const RVector& center = RDEFAULT_RVECTOR);
    virtual void scaleVisualProperties(double scaleFactor);
    virtual bool mirror(const RLine& axis);
    virtual bool mirror(const RVector& axis1, const RVector& axis2);
    virtual bool flipHorizontal();
    virtual bool flipVertical();
    virtual bool stretch(const RPolyline& area, const RVector& offset);

    /**
     * Entities can reimplement this function to invalidate any internal cache
     * (mark the entity as dirty).
     */
    virtual void update() const {}
    void setAutoUpdatesBlocked(bool on);

    static int getDefaultDrawOrder() {
        return RMININT;
    }

protected:
    RDocument* document;
    bool updatesEnabled;
    bool selectionStatus;
    bool selectionStatusWorkingSet;
    /** Block auto updates is true during imports, undo and redo. */
    bool autoUpdatesBlocked;
    int drawOrder;
    RLayer::Id layerId;
    RBlock::Id blockId;
    RObject::Id parentId;
    RLinetype::Id linetypeId;
    double linetypeScale;
    RLineweight::Lineweight lineweight;
    RColor color;
};

Q_DECLARE_METATYPE(REntityData*)
Q_DECLARE_METATYPE(const REntityData*)
Q_DECLARE_METATYPE(QSharedPointer<REntityData>)
Q_DECLARE_METATYPE(QSharedPointer<REntityData>*)

#endif
