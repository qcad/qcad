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

    static RPropertyTypeId PropertySolid;
    static RPropertyTypeId PropertyTransparency;

    static RPropertyTypeId PropertyPatternName;
    static RPropertyTypeId PropertyEntityPattern;
    static RPropertyTypeId PropertyScaleFactor;
    static RPropertyTypeId PropertyAngle;

    static RPropertyTypeId PropertyOriginX;
    static RPropertyTypeId PropertyOriginY;

    static RPropertyTypeId PropertyVertexNX;
    static RPropertyTypeId PropertyVertexNY;
    static RPropertyTypeId PropertyVertexNZ;

public:
    RHatchEntity(RDocument* document, const RHatchData& data);
    virtual ~RHatchEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RHatchEntity));
    }

    virtual RHatchEntity* clone() const;

    void setData(RHatchData& d) {
        data = d;
    }

    bool hasCustomPattern() const {
        return data.hasCustomPattern();
    }

    RPattern getCustomPattern() const {
        return data.getCustomPattern();
    }

    void setCustomPattern(const RPattern& p) {
        data.setCustomPattern(p);
    }

    virtual bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    bool setBoundaryVector(RObject::XYZ xyz, const QVariant& value, bool condition);
    RVector setComponent(const RVector& p, double v, RObject::XYZ xyz);

    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

    virtual void exportEntity(RExporter& e, bool preview=false, bool forceSelected=false) const;

    virtual RHatchData& getData() {
        return data;
    }

    virtual const RHatchData& getData() const {
        return data;
    }

    QList<RPainterPath> getPainterPaths(bool draft = false, double pixelSizeHint = 0.0) const {
        return data.getPainterPaths(draft, pixelSizeHint);
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

    RVector getOriginPoint() const {
        return data.getOriginPoint();
    }

    void setOriginPoint(const RVector& op) {
        data.setOriginPoint(op);
    }

    QString getPatternName() const {
        return data.getPatternName();
    }

    void setPatternName(const QString& n) {
        data.setPatternName(n);
    }

    int getTransparency() const {
        return data.getTransparency();
    }

    void setTransparency(int t) {
        data.setTransparency(t);
    }

    void clearCustomPattern() {
        data.clearCustomPattern();
    }

    QList<QSharedPointer<RShape> > getLoopBoundary(int index) const {
        return data.getLoopBoundary(index);
    }

    QList<RPolyline> getBoundaryAsPolylines(double segmentLength) const {
        return data.getBoundaryAsPolylines(segmentLength);
    }

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false) const {
        return data.getShapes(queryBox, ignoreComplex, segment);
    }

    virtual QList<QSharedPointer<RShape> > getExploded() const {
        return data.getExploded();
    }

    virtual void setViewportContext(const RViewportData& origin);

protected:
    virtual void print(QDebug dbg) const;

protected:
    RHatchData data;
};

Q_DECLARE_METATYPE(RHatchEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RHatchEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RHatchEntity>*)

#endif
