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
#include "RExporter.h"
#include "RLeaderEntity.h"
#include "RMetaTypes.h"
#include "RStorage.h"

RPropertyTypeId RLeaderEntity::PropertyCustom;
RPropertyTypeId RLeaderEntity::PropertyHandle;
RPropertyTypeId RLeaderEntity::PropertyProtected;
RPropertyTypeId RLeaderEntity::PropertyWorkingSet;
RPropertyTypeId RLeaderEntity::PropertyType;
RPropertyTypeId RLeaderEntity::PropertyBlock;
RPropertyTypeId RLeaderEntity::PropertyLayer;
RPropertyTypeId RLeaderEntity::PropertyLinetype;
RPropertyTypeId RLeaderEntity::PropertyLinetypeScale;
RPropertyTypeId RLeaderEntity::PropertyLineweight;
RPropertyTypeId RLeaderEntity::PropertyColor;
RPropertyTypeId RLeaderEntity::PropertyDisplayedColor;
RPropertyTypeId RLeaderEntity::PropertyDrawOrder;

RPropertyTypeId RLeaderEntity::PropertyArrowHead;
RPropertyTypeId RLeaderEntity::PropertyDimLeaderBlock;
RPropertyTypeId RLeaderEntity::PropertyVertexNX;
RPropertyTypeId RLeaderEntity::PropertyVertexNY;
RPropertyTypeId RLeaderEntity::PropertyVertexNZ;

RPropertyTypeId RLeaderEntity::PropertyDimScale;


RLeaderEntity::RLeaderEntity(RDocument* document, const RLeaderData& data) :
    REntity(document), data(document, data) {
    RDebug::incCounter("RLeaderEntity");
}

RLeaderEntity::RLeaderEntity(const RLeaderEntity& other) : REntity(other) {
    RDebug::incCounter("RLeaderEntity");
    data = other.data;
}

RLeaderEntity::~RLeaderEntity() {
    RDebug::decCounter("RLeaderEntity");
}

void RLeaderEntity::init() {
    RLeaderEntity::PropertyCustom.generateId(typeid(RLeaderEntity), RObject::PropertyCustom);
    RLeaderEntity::PropertyHandle.generateId(typeid(RLeaderEntity), RObject::PropertyHandle);
    RLeaderEntity::PropertyProtected.generateId(typeid(RLeaderEntity), RObject::PropertyProtected);
    RLeaderEntity::PropertyWorkingSet.generateId(typeid(RLeaderEntity), RObject::PropertyWorkingSet);
    RLeaderEntity::PropertyType.generateId(typeid(RLeaderEntity), REntity::PropertyType);
    RLeaderEntity::PropertyBlock.generateId(typeid(RLeaderEntity), REntity::PropertyBlock);
    RLeaderEntity::PropertyLayer.generateId(typeid(RLeaderEntity), REntity::PropertyLayer);
    RLeaderEntity::PropertyLinetype.generateId(typeid(RLeaderEntity), REntity::PropertyLinetype);
    RLeaderEntity::PropertyLinetypeScale.generateId(typeid(RLeaderEntity), REntity::PropertyLinetypeScale);
    RLeaderEntity::PropertyLineweight.generateId(typeid(RLeaderEntity), REntity::PropertyLineweight);
    RLeaderEntity::PropertyColor.generateId(typeid(RLeaderEntity), REntity::PropertyColor);
    RLeaderEntity::PropertyDisplayedColor.generateId(typeid(RLeaderEntity), REntity::PropertyDisplayedColor);
    RLeaderEntity::PropertyDrawOrder.generateId(typeid(RLeaderEntity), REntity::PropertyDrawOrder);

    RLeaderEntity::PropertyArrowHead.generateId(typeid(RLeaderEntity), "", QT_TRANSLATE_NOOP("REntity", "Arrow"));
    RLeaderEntity::PropertyDimLeaderBlock.generateId(typeid(RLeaderEntity), "", QT_TRANSLATE_NOOP("REntity", "Arrow Block"));
    RLeaderEntity::PropertyVertexNX.generateId(typeid(RLeaderEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RLeaderEntity::PropertyVertexNY.generateId(typeid(RLeaderEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RLeaderEntity::PropertyVertexNZ.generateId(typeid(RLeaderEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);

    RLeaderEntity::PropertyDimScale.generateId(typeid(RLeaderEntity), "", QT_TRANSLATE_NOOP("REntity", "Scale"));
}

bool RLeaderEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = REntity::setProperty(propertyTypeId, value, transaction);

    if (PropertyArrowHead == propertyTypeId) {
        if (value.toBool()==false || data.canHaveArrowHead()) {
            ret = ret || RObject::setMember(data.arrowHead, value);
        }
    }

    if (propertyTypeId == PropertyDimLeaderBlock) {
        if (value.type() == QVariant::Int ||
            value.type() == QVariant::LongLong) {

            ret = ret || RObject::setMember(
                getData().dimLeaderBlockId, value.toInt(), true);
        } else if (value.type() == QVariant::String) {
            RDocument* document = getData().getDocument();
            if (document != NULL) {
                ret = ret || RObject::setMember(getData().dimLeaderBlockId,
                        document->getBlockId(value.toString()), true);
            }
        }
    }

//    ret = ret || RObject::setMember(data.arrowHead, value, PropertyArrowHead == propertyTypeId);
    ret = ret || RObject::setMemberX(data.vertices, value, PropertyVertexNX == propertyTypeId);
    ret = ret || RObject::setMemberY(data.vertices, value, PropertyVertexNY == propertyTypeId);
    ret = ret || RObject::setMemberZ(data.vertices, value, PropertyVertexNZ == propertyTypeId);

    if (PropertyDimScale == propertyTypeId) {
        ret = ret || RObject::setMember(data.dimScaleOverride, value, PropertyDimScale == propertyTypeId);
        data.updateArrowHead();
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RLeaderEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {

    if (propertyTypeId == PropertyArrowHead) {
        return qMakePair(QVariant(data.arrowHead), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyDimLeaderBlock) {
        if (humanReadable) {
            RDocument* document = getData().getDocument();
            if (document != NULL) {
                RPropertyAttributes attr;
//                if (!noAttributes) {
//                    QSet<QString> blockNames = document->getBlockNames();
//                    QSet<QString> filtered;
//                    QSet<QString>::iterator it;
//                    for (it=blockNames.begin(); it!=blockNames.end(); it++) {
//                        if (!(*it).startsWith("*")) {
//                            filtered.insert(*it);
//                        }
//                    }
//                    attr.setChoices(filtered);
//                }
                // invisible property for now (cannot be written back to file):
                attr.setInvisible(true);
                return qMakePair(QVariant(document->getBlockName(
                        getData().getDimLeaderBlockId())), attr);
            }
        } else {
            RPropertyAttributes attr;
            //attr.setReadOnly(true);
            attr.setInvisible(true);
            return qMakePair(QVariant(getData().getDimLeaderBlockId()), attr);
        }
    }
    else if (propertyTypeId == PropertyVertexNX) {
        QVariant v;
        v.setValue(RVector::getXList(data.vertices));
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
    }
    else if (propertyTypeId == PropertyVertexNY) {
        QVariant v;
        v.setValue(RVector::getYList(data.vertices));
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
    }
    else if (propertyTypeId == PropertyVertexNZ) {
        QVariant v;
        v.setValue(RVector::getZList(data.vertices));
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
    }
    else if (propertyTypeId == PropertyDimScale) {
        return qMakePair(QVariant(data.dimScaleOverride), RPropertyAttributes());
    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}


void RLeaderEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview)
    Q_UNUSED(forceSelected)

    // a leader needs at least two vertices to display something:
    if (countVertices()<=1) {
        return;
    }

    if (hasArrowHead()) {
        RDocument* doc = (RDocument*)getDocument();
        REntity::Id dimLeaderBlockId = data.getDimLeaderBlockId();
        if (dimLeaderBlockId!=REntity::INVALID_ID && doc!=NULL) {
            // create temporary block reference to leader arrow block:
            RBlockReferenceEntity arrowBlock(
                doc,
                RBlockReferenceData(
                    dimLeaderBlockId,
                    getStartPoint(),
                    RVector(data.getDimasz(), data.getDimasz()),
                    getDirection1() + M_PI
                )
            );
            arrowBlock.setLayerId(getLayerId());
            arrowBlock.setSelected(isSelected());
            arrowBlock.update();
            arrowBlock.exportEntity(e, preview, forceSelected);
        }
        else {
            // use regular arrow for leader:
            RTriangle arrow = data.getArrowShape();
            QList<QSharedPointer<RShape> > arrowShapes;
            arrowShapes.append(QSharedPointer<RShape>(new RTriangle(arrow)));
            e.exportShapes(arrowShapes);
        }
    }

    e.setBrush(Qt::NoBrush);
    e.exportPolyline(data);
}

void RLeaderEntity::print(QDebug dbg) const {
    dbg.nospace() << "RLeaderEntity(";
    REntity::print(dbg);
    data.print(dbg);
    dbg.nospace()  << ")";
}
