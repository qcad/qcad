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

#ifndef RBLOCKREFERENCEDATA_H
#define RBLOCKREFERENCEDATA_H

#include "core_global.h"

#include "RBox.h"
#include "REntityData.h"
#include "RVector.h"

class RDocument;
class RExporter;
class REntity;
class RLine;
class RTransform;
class RRefPoint;

/**
 * Defines the geometry and appearance of a block reference entity.
 *
 * \scriptable
 * \copyable
 * \ingroup core
 */
class QCADCORE_EXPORT RBlockReferenceData: public REntityData {

friend class RBlockReferenceEntity;
friend class RViewportEntity;

protected:
    RBlockReferenceData(RDocument* document, const RBlockReferenceData& data);

public:
    RBlockReferenceData();
    RBlockReferenceData(RObject::Id referencedBlockId,
            const RVector& position, const RVector& scaleFactors,
            double angle,
            int columnCount=1, int rowCount=1,
            double columnSpacing=0, double rowSpacing=0,
            double visualPropertiesScale=1.0);

    static RS::EntityType getRtti() {
        return RS::EntityBlockRef;
    }

    virtual RS::EntityType getType() const {
        return RS::EntityBlockRef;
    }

    virtual bool isPointType() const;

    virtual QList<RBox> getBoundingBoxes(bool ignoreEmpty=false) const;
    virtual RBox getBoundingBox(bool ignoreEmpty=false) const;

    virtual void to2D();

    virtual RVector getPointOnEntity() const;

    virtual QList<RRefPoint> getInternalReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop, QList<RObject::Id>* subEntityIds = NULL) const;
    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;
    virtual RVector getVectorTo(const RVector& point,  bool limited = true, double strictRange = RMAXDOUBLE) const;
    virtual double getDistanceTo(const RVector& point, bool limited = true, double range = 0.0,
                                 bool draft = false, double strictRange = RMAXDOUBLE) const;

    RBox getQueryBoxInBlockCoordinates(const RBox& box) const;
    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false, QList<RObject::Id>* entityIds = NULL) const;

    //virtual void setSelected(bool on);

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);
    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool mirror(const RLine& axis);
    virtual bool scale(const RVector& scaleFactors,
                       const RVector& center = RDEFAULT_RVECTOR);

    virtual void scaleVisualProperties(double scaleFactor);

    void setReferencedBlockId(RObject::Id blockId);

    void groundReferencedBlockId() const;

    RObject::Id getReferencedBlockId() const {
        return referencedBlockId;
    }

    bool hasBlockOwnership() const;

    void setReferencedBlockName(const QString& blockName);
    QString getReferencedBlockName() const;

    RVector getPosition() const {
        return position;
    }
    void setPosition(const RVector& p);

    RVector getScaleFactors() const {
        return scaleFactors;
    }
    void setScaleFactors(const RVector& sf);

    double getRotation() const {
        return rotation;
    }
    void setRotation(double r);

    int getColumnCount() const {
        return columnCount;
    }
    void setColumnCount(int c) {
        columnCount = c;
    }

    int getRowCount() const {
        return rowCount;
    }
    void setRowCount(int c) {
        rowCount = c;
    }

    double getColumnSpacing() const {
        return columnSpacing;
    }
    void setColumnSpacing(double s) {
        columnSpacing = s;
    }

    double getRowSpacing() const {
        return rowSpacing;
    }
    void setRowSpacing(double s) {
        rowSpacing = s;
    }

    virtual void update() const;
    virtual void update(RObject::Id entityId) const;

    QSharedPointer<REntity> queryEntity(RObject::Id entityId, bool transform = false, bool ignoreAttDef = true) const;
    bool applyTransformationTo(REntity& entity) const;
    /**
     * \nonscriptable
     */
    bool applyTransformationTo(QSharedPointer<REntity>& entity) const;

    QSharedPointer<REntity> getTransformed(QSharedPointer<REntity>& entity) const {
        applyTransformationTo(entity);
        return entity;
    }

    RTransform getTransform() const;

    RVector getColumnRowOffset(int col, int row, bool rotated = false) const;
    void applyColumnRowOffsetTo(REntity& entity, int col, int row, bool rotated = false) const;
    RVector mapToBlock(const RVector& v) const;

    bool isPixelUnit() const;

#if QT_VERSION >= 0x060000
    /**
     * copy function for Qt 6 scripts:
     * \nonscriptable
     */
    RBlockReferenceData copy() const {
        return *this;
    }
#endif

private:
    mutable RObject::Id referencedBlockId;
    RVector position;
    RVector scaleFactors;
    double rotation;
    int columnCount;
    int rowCount;
    double columnSpacing;
    double rowSpacing;

    double visualPropertiesScale;

    mutable QList<RBox> boundingBoxes;
    mutable QList<RBox> boundingBoxesIgnoreEmpty;
    mutable QMap<RObject::Id, QSharedPointer<REntity> > cache;
};

Q_DECLARE_METATYPE(RBlockReferenceData)
Q_DECLARE_METATYPE(RBlockReferenceData*)
Q_DECLARE_METATYPE(const RBlockReferenceData*)
Q_DECLARE_METATYPE(QSharedPointer<RBlockReferenceData>)

#endif
