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

#ifndef RVIEWPORTENTITY_H
#define RVIEWPORTENTITY_H

#include "core_global.h"

#include "REntity.h"
#include "RViewportData.h"

class RDocument;
class RExporter;

/**
 * Viewport entity.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup core
 */
class QCADCORE_EXPORT RViewportEntity: public REntity {

public:
    static RPropertyTypeId PropertyCustom;
    static RPropertyTypeId PropertyHandle;
    static RPropertyTypeId PropertyType;
    static RPropertyTypeId PropertyBlock;
    static RPropertyTypeId PropertyLayer;
    static RPropertyTypeId PropertyLinetype;
    static RPropertyTypeId PropertyLinetypeScale;
    static RPropertyTypeId PropertyLineweight;
    static RPropertyTypeId PropertyColor;
    static RPropertyTypeId PropertyDisplayedColor;
    static RPropertyTypeId PropertyDrawOrder;

    static RPropertyTypeId PropertyCenterX;
    static RPropertyTypeId PropertyCenterY;
    static RPropertyTypeId PropertyCenterZ;
    static RPropertyTypeId PropertyWidth;
    static RPropertyTypeId PropertyHeight;
    static RPropertyTypeId PropertyScale;
    static RPropertyTypeId PropertyRotation;
    static RPropertyTypeId PropertyOn;
    static RPropertyTypeId PropertyViewCenterX;
    static RPropertyTypeId PropertyViewCenterY;
    static RPropertyTypeId PropertyViewTargetX;
    static RPropertyTypeId PropertyViewTargetY;
    static RPropertyTypeId PropertyViewTargetZ;

    static RPropertyTypeId PropertyOverall;

public:
    RViewportEntity(RDocument* document, const RViewportData& data);
    virtual ~RViewportEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RViewportEntity));
    }

    virtual RViewportEntity* clone() const {
        return new RViewportEntity(*this);
    }

    virtual bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

    virtual void exportEntity(RExporter& e, bool preview=false, bool forceSelected=false) const;

    virtual RViewportData& getData() {
        return data;
    }

    virtual const RViewportData& getData() const {
        return data;
    }

    void setData(RViewportData& d);

    int getViewportId() const {
       return data.getViewportId();
    }

    void setViewportId(int id) {
        data.setViewportId(id);
    }

    int getStatus() const {
        return data.getStatus();
    }

    void setStatus(int s) {
        data.setStatus(s);
    }

    RVector getCenter() const {
       return data.getCenter();
    }

    void setCenter(const RVector& c) {
        data.setCenter(c);
    }

    RVector getViewCenter() const {
        return data.getViewCenter();
    }

    void setViewCenter(const RVector& c) {
        data.setViewCenter(c);
    }

    RVector getViewTarget() const {
        return data.getViewTarget();
    }

    void setViewTarget(const RVector& t) {
        data.setViewTarget(t);
    }

    double getWidth() const {
        return data.getWidth();
    }

    void setWidth(double w) {
        data.setWidth(w);
    }

    double getHeight() const {
        return data.getHeight();
    }

    void setHeight(double h) {
        data.setHeight(h);
    }

    double getScale() const {
        return data.getScale();
    }

    void setScale(double s) {
        data.setScale(s);
    }

    double getRotation() const {
        return data.getRotation();
    }

    void setRotation(double r) {
        data.setRotation(r);
    }

    bool isOverall() const {
        return data.isOverall();
    }

    void setOverall(bool on) {
        data.setOverall(on);
    }

    bool isOff() const {
        return data.isOff();
    }

    void setOff(bool v) {
        data.setOff(v);
    }

    RVector getViewOffset() const {
        return data.getViewOffset();
    }

    RVector getPosition() const {
        return data.getPosition();
    }

    void setPosition(const RVector& p) {
        data.setPosition(p);
    }

protected:
    virtual void print(QDebug dbg) const;

protected:
    RViewportData data;
};

Q_DECLARE_METATYPE(RViewportEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RViewportEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RViewportEntity>*)

#endif
