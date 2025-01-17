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
#include "RPluginLoader.h"

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
RPropertyTypeId RLeaderEntity::PropertySplineShaped;
RPropertyTypeId RLeaderEntity::PropertyDimLeaderBlock;
RPropertyTypeId RLeaderEntity::PropertyVertexNX;
RPropertyTypeId RLeaderEntity::PropertyVertexNY;
RPropertyTypeId RLeaderEntity::PropertyVertexNZ;

RPropertyTypeId RLeaderEntity::PropertyDimscale;
RPropertyTypeId RLeaderEntity::PropertyDimasz;

RPropertyTypeId RLeaderEntity::PropertyLength;
RPropertyTypeId RLeaderEntity::PropertyTotalLength;


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
    RLeaderEntity::PropertyCustom.generateId(RLeaderEntity::getRtti(), RObject::PropertyCustom);
    RLeaderEntity::PropertyHandle.generateId(RLeaderEntity::getRtti(), RObject::PropertyHandle);
    RLeaderEntity::PropertyProtected.generateId(RLeaderEntity::getRtti(), RObject::PropertyProtected);
    RLeaderEntity::PropertyWorkingSet.generateId(RLeaderEntity::getRtti(), RObject::PropertyWorkingSet);
    RLeaderEntity::PropertyType.generateId(RLeaderEntity::getRtti(), REntity::PropertyType);
    RLeaderEntity::PropertyBlock.generateId(RLeaderEntity::getRtti(), REntity::PropertyBlock);
    RLeaderEntity::PropertyLayer.generateId(RLeaderEntity::getRtti(), REntity::PropertyLayer);
    RLeaderEntity::PropertyLinetype.generateId(RLeaderEntity::getRtti(), REntity::PropertyLinetype);
    RLeaderEntity::PropertyLinetypeScale.generateId(RLeaderEntity::getRtti(), REntity::PropertyLinetypeScale);
    RLeaderEntity::PropertyLineweight.generateId(RLeaderEntity::getRtti(), REntity::PropertyLineweight);
    RLeaderEntity::PropertyColor.generateId(RLeaderEntity::getRtti(), REntity::PropertyColor);
    RLeaderEntity::PropertyDisplayedColor.generateId(RLeaderEntity::getRtti(), REntity::PropertyDisplayedColor);
    RLeaderEntity::PropertyDrawOrder.generateId(RLeaderEntity::getRtti(), REntity::PropertyDrawOrder);

    RLeaderEntity::PropertyArrowHead.generateId(RLeaderEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Arrow"));
    RLeaderEntity::PropertySplineShaped.generateId(RLeaderEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Spline"));
    RLeaderEntity::PropertyDimLeaderBlock.generateId(RLeaderEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Arrow Block"));
    RLeaderEntity::PropertyVertexNX.generateId(RLeaderEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RLeaderEntity::PropertyVertexNY.generateId(RLeaderEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RLeaderEntity::PropertyVertexNZ.generateId(RLeaderEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);

    RLeaderEntity::PropertyDimscale.generateId(RLeaderEntity::getRtti(), RDimStyle::PropertyDimscale);
    if (RPluginLoader::hasPlugin("DWG")) {
        RLeaderEntity::PropertyDimasz.generateId(RLeaderEntity::getRtti(), RDimStyle::PropertyDimasz);
    }

    RLeaderEntity::PropertyLength.generateId(RLeaderEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Length"));
    RLeaderEntity::PropertyTotalLength.generateId(RLeaderEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Total Length"));
}

bool RLeaderEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = REntity::setProperty(propertyTypeId, value, transaction);

    if (PropertyArrowHead == propertyTypeId) {
        if (value.toBool()==false || data.canHaveArrowHead()) {
            ret = ret || RObject::setMember(data.arrowHead, value);
        }
    }

    if (PropertySplineShaped == propertyTypeId) {
        ret = ret || RObject::setMember(data.splineShaped, value);
    }

    if (propertyTypeId == PropertyDimLeaderBlock) {
        if (RS::getMetaType(value) == RS::Int ||
            RS::getMetaType(value) == RS::LongLong) {

            ret = ret || RObject::setMember(
                getData().dimLeaderBlockId, value.toInt(), true);
        } else if (RS::getMetaType(value) == RS::String) {
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

    ret = ret || RObject::setMember(getData().dimscale, value, PropertyDimscale == propertyTypeId);
    ret = ret || RObject::setMember(getData().dimasz, value, PropertyDimasz == propertyTypeId);

//    if (PropertyDimScale == propertyTypeId) {
//        ret = ret || RObject::setMember(data.dimScaleOverride, value, PropertyDimScale == propertyTypeId);
//        data.updateArrowHead();
//    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RLeaderEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {

    if (propertyTypeId == PropertyArrowHead) {
        return qMakePair(QVariant(data.arrowHead), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertySplineShaped) {
        return qMakePair(QVariant(data.splineShaped), RPropertyAttributes());
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
    else if (propertyTypeId == PropertyDimscale || propertyTypeId == PropertyDimasz) {
        double v;
        if (propertyTypeId == PropertyDimscale) {
            v = data.dimscale;
        }
        else {
            v = data.dimasz;
        }
        if (v<0.0) {
            RDocument* doc = getDocument();
            if (doc!=NULL) {
                QSharedPointer<RDimStyle> dimStyle = getDocument()->queryDimStyleDirect();
                if (!dimStyle.isNull()) {
                    if (propertyTypeId == PropertyDimscale) {
                        v = dimStyle->getDouble(RS::DIMSCALE);
                    }
                    else {
                        v = dimStyle->getDouble(RS::DIMASZ);
                    }
                }
            }
        }

        RPropertyAttributes attr;

        if (propertyTypeId==PropertyDimscale) {
            attr.setUnitLess(true);
        }

        return qMakePair(QVariant(v), attr);
    }

    if (humanReadable) {
        if (propertyTypeId == PropertyLength) {
            QVariant v;
            v.setValue(data.getLength());
            return qMakePair(v, RPropertyAttributes(RPropertyAttributes::Redundant|RPropertyAttributes::ReadOnly));
        } else if (propertyTypeId == PropertyTotalLength) {
            if (showOnRequest) {
                QVariant v;
                v.setValue(data.getLength());
                return qMakePair(v, RPropertyAttributes(RPropertyAttributes::Sum));
            }
            else {
                QVariant v;
                v.setValue(0.0);
                return qMakePair(v, RPropertyAttributes(RPropertyAttributes::Redundant|RPropertyAttributes::OnRequest));
            }
        }
    }

//    else if (propertyTypeId == PropertyDimScale) {
//        return qMakePair(QVariant(data.dimScaleOverride), RPropertyAttributes());
//    }

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
