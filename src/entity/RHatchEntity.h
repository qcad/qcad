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

#ifndef RHATCHENTITY_H
#define RHATCHENTITY_H

#include "entity_global.h"

#include "REntity.h"
#include "RHatchData.h"

class RDocument;
class RExporter;

/**
 * Point entity.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT RHatchEntity: public REntity {

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

    static RPropertyTypeId PropertySolid;

    static RPropertyTypeId PropertyPatternName;
    static RPropertyTypeId PropertyScaleFactor;
    static RPropertyTypeId PropertyAngle;

    static RPropertyTypeId PropertyVertexNX;
    static RPropertyTypeId PropertyVertexNY;
    static RPropertyTypeId PropertyVertexNZ;

public:
    RHatchEntity(RDocument* document, const RHatchData& data,
        RObject::Id objectId = RObject::INVALID_ID);
    virtual ~RHatchEntity();

    static void init();

    virtual RHatchEntity* clone() const;

    virtual RS::EntityType getType() const {
        return RS::EntityHatch;
    }

    bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value);
    bool setBoundaryVector(RObject::XYZ xyz, const QVariant& value, bool condition);
    RVector setComponent(const RVector& p, double v, RObject::XYZ xyz);

    QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId propertyTypeId,
            bool humanReadable = false, bool noAttributes = false);

    virtual void exportEntity(RExporter& e, bool preview=false) const;

    virtual RHatchData& getData() {
        return data;
    }

    virtual const RHatchData& getData() const {
        return data;
    }

    QList<RPainterPath> getPainterPaths(bool draft = false) const {
        return data.getPainterPaths(draft);
    }

    virtual int getComplexity() const {
        return data.getComplexity();
    }

    void newLoop() {
        data.newLoop();
    }

    void addBoundary(QSharedPointer<RShape> shape) {
        data.addBoundary(shape);
    }

    int getLoopCount() const {
        return data.getLoopCount();
    }

    bool isSolid() const {
        return data.isSolid();
    }

    void setSolid(bool on) {
        data.setSolid(on);
    }

    double getScale() const {
        return data.getScale();
    }

    void setScale(double s) {
        data.setScale(s);
    }

    double getAngle() const {
        return data.getAngle();
    }

    void setAngle(double a) {
        data.setAngle(a);
    }

    QString getPatternName() const {
        return data.getPatternName();
    }

    void setPatternName(const QString& n) {
        data.setPatternName(n);
    }

    QList<QSharedPointer<RShape> > getLoopBoundary(int index) const {
        return data.getLoopBoundary(index);
    }

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX) const {
        return data.getShapes(queryBox);
    }

    virtual QList<QSharedPointer<RShape> > getExploded() const {
        return data.getExploded();
    }

protected:
    virtual void print(QDebug dbg) const;

protected:
    RHatchData data;
};

Q_DECLARE_METATYPE(RHatchEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RHatchEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RHatchEntity>*)

#endif
