/**
 * Copyright (c) 2011-2024 by Andrew Mustun. All rights reserved.
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

#ifndef RWIPEOUTENTITY_H
#define RWIPEOUTENTITY_H

#include "entity_global.h"

#include "RPolylineEntity.h"
#include "RWipeoutData.h"

class RDocument;
class RExporter;
class RArc;
class RLine;

#ifndef RDEFAULT_MIN1
#define RDEFAULT_MIN1 -1
#endif

/**
 * Polyline entity.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT RWipeoutEntity: public REntity {

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

//    static RPropertyTypeId PropertyClosed;
//    static RPropertyTypeId PropertyPolylineGen;
    static RPropertyTypeId PropertyVertexNX;
    static RPropertyTypeId PropertyVertexNY;
    static RPropertyTypeId PropertyVertexNZ;
    static RPropertyTypeId PropertyBulgeN;
//    static RPropertyTypeId PropertyAngleN;
//    static RPropertyTypeId PropertyStartWidthN;
//    static RPropertyTypeId PropertyEndWidthN;
//    static RPropertyTypeId PropertyGlobalWidth;

//    static RPropertyTypeId PropertyOrientation;
//    static RPropertyTypeId PropertyLength;
//    static RPropertyTypeId PropertyTotalLength;
//    static RPropertyTypeId PropertyArea;
//    static RPropertyTypeId PropertyTotalArea;

    static RPropertyTypeId PropertyBaseAngle;
    static RPropertyTypeId PropertySize1;
    static RPropertyTypeId PropertySize2;

    static RPropertyTypeId PropertyFrame;

//    static RPropertyTypeId PropertyElevation;

//    static QString TrClockwise;
//    static QString TrCounterclockwise;

public:
    RWipeoutEntity(RDocument* document, const RWipeoutData& data);
    RWipeoutEntity(const RWipeoutEntity& other);
    virtual ~RWipeoutEntity();

    static void init();

    static RS::EntityType getRtti() {
        return RS::EntityWipeout;
    }

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(RWipeoutEntity::getRtti());
    }

    virtual RWipeoutEntity* clone() const {
        return new RWipeoutEntity(*this);
    }

    virtual RWipeoutData& getData() {
        return data;
    }

    virtual const RWipeoutData& getData() const {
        return data;
    }

    virtual bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
                             RTransaction* transaction=NULL);
    virtual QPair<QVariant, RPropertyAttributes> getProperty(
        RPropertyTypeId& propertyTypeId,
        bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

    virtual void exportEntity(RExporter& e, bool preview=false, bool forceSelected=false) const;

    void setShape(const RPolyline& l);

    bool getShowFrame() const {
        return data.getShowFrame();
    }

    void setShowFrame(bool on) {
        data.setShowFrame(on);
    }

    int countVertices() const {
        return data.countVertices();
    }

    void appendVertex(const RVector& vertex, double bulge = 0.0, double w1 = 0.0, double w2 = 0.0) {
        data.appendVertex(vertex, bulge, w1, w2);
    }

    RVector getEndPoint() const {
        return data.getEndPoint();
    }

    RVector getStartPoint() const {
        return data.getStartPoint();
    }

    RVector getVertexAt(int i) const {
        return data.getVertexAt(i);
    }

    void removeLastVertex() {
        data.removeLastVertex();
    }

protected:
    RWipeoutData data;
};

Q_DECLARE_METATYPE(RWipeoutEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RWipeoutEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RWipeoutEntity>*)

#endif
