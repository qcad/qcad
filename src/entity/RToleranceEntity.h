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

#ifndef RTOLERANCEENTITY_H
#define RTOLERANCEENTITY_H

#include "entity_global.h"

#include <QList>

#include "REntity.h"
#include "RToleranceData.h"

class RDocument;
class RExporter;

/**
 * Tolerance entity class.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT RToleranceEntity: public REntity {
    Q_DECLARE_TR_FUNCTIONS(RToleranceEntity)

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

    static RPropertyTypeId PropertyLocationX;
    static RPropertyTypeId PropertyLocationY;
    static RPropertyTypeId PropertyLocationZ;
    static RPropertyTypeId PropertyDirectionX;
    static RPropertyTypeId PropertyDirectionY;
    static RPropertyTypeId PropertyDirectionZ;
    static RPropertyTypeId PropertyText;
    static RPropertyTypeId PropertyDimScale;

public:
    RToleranceEntity(RDocument* document, const RToleranceData& data);
    RToleranceEntity(const RToleranceEntity& other);
    virtual ~RToleranceEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RToleranceEntity));
    }

    virtual RToleranceEntity* clone() const {
        return new RToleranceEntity(*this);
    }

    virtual bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

    virtual RToleranceData& getData() {
        return data;
    }

    void setData(RToleranceData& d) {
        data = d;
    }

    virtual const RToleranceData& getData() const {
        return data;
    }

    void setLocation(const RVector& l) {
        data.setLocation(l);
    }

    RVector getLocation() const {
        return data.getLocation();
    }

    void setDirection(const RVector& p) {
        data.setDirection(p);
    }

    RVector getDirection() const {
        return data.getDirection();
    }

    void setText(const QString& t) {
        data.setText(t);
    }

    QString getText() const {
        return data.getText();
    }

    double getDimtxt() const {
        return data.getDimtxt();
    }

    double getDimScale(bool fromDocument=true) const {
        return data.getDimScale(fromDocument);
    }

    QList<QSharedPointer<RShape> > getExploded() const {
        return data.getExploded();
    }

    virtual void exportEntity(RExporter& e, bool preview=false, bool forceSelected=false) const;

    QList<RTextData> getTextLabels() const {
        return data.getTextLabels();
    }

    QList<RLine> getFrame() const {
        return data.getFrame();
    }

protected:
    virtual void print(QDebug dbg) const;

protected:
    RToleranceData data;
};

Q_DECLARE_METATYPE(RToleranceEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RToleranceEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RToleranceEntity>*)

#endif
