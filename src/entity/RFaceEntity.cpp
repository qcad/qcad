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
#include "RFaceEntity.h"
#include "RExporter.h"
#include "RLine.h"

RPropertyTypeId RFaceEntity::PropertyCustom;
RPropertyTypeId RFaceEntity::PropertyHandle;
RPropertyTypeId RFaceEntity::PropertyProtected;
RPropertyTypeId RFaceEntity::PropertyWorkingSet;
RPropertyTypeId RFaceEntity::PropertyType;
RPropertyTypeId RFaceEntity::PropertyBlock;
RPropertyTypeId RFaceEntity::PropertyLayer;
RPropertyTypeId RFaceEntity::PropertyLinetype;
RPropertyTypeId RFaceEntity::PropertyLinetypeScale;
RPropertyTypeId RFaceEntity::PropertyLineweight;
RPropertyTypeId RFaceEntity::PropertyColor;
RPropertyTypeId RFaceEntity::PropertyDisplayedColor;
RPropertyTypeId RFaceEntity::PropertyDrawOrder;

RPropertyTypeId RFaceEntity::PropertyPoint1X;
RPropertyTypeId RFaceEntity::PropertyPoint1Y;
RPropertyTypeId RFaceEntity::PropertyPoint1Z;
RPropertyTypeId RFaceEntity::PropertyPoint2X;
RPropertyTypeId RFaceEntity::PropertyPoint2Y;
RPropertyTypeId RFaceEntity::PropertyPoint2Z;
RPropertyTypeId RFaceEntity::PropertyPoint3X;
RPropertyTypeId RFaceEntity::PropertyPoint3Y;
RPropertyTypeId RFaceEntity::PropertyPoint3Z;
RPropertyTypeId RFaceEntity::PropertyPoint4X;
RPropertyTypeId RFaceEntity::PropertyPoint4Y;
RPropertyTypeId RFaceEntity::PropertyPoint4Z;

RPropertyTypeId RFaceEntity::PropertyLength;
RPropertyTypeId RFaceEntity::PropertyTotalLength;


RFaceEntity::RFaceEntity(RDocument* document, const RFaceData& data) :
    REntity(document), data(document, data) {
}

RFaceEntity::~RFaceEntity() {
}

void RFaceEntity::init() {
    RFaceEntity::PropertyCustom.generateId(typeid(RFaceEntity), RObject::PropertyCustom);
    RFaceEntity::PropertyHandle.generateId(typeid(RFaceEntity), RObject::PropertyHandle);
    RFaceEntity::PropertyProtected.generateId(typeid(RFaceEntity), RObject::PropertyProtected);
    RFaceEntity::PropertyWorkingSet.generateId(typeid(RFaceEntity), RObject::PropertyWorkingSet);
    RFaceEntity::PropertyType.generateId(typeid(RFaceEntity), REntity::PropertyType);
    RFaceEntity::PropertyBlock.generateId(typeid(RFaceEntity), REntity::PropertyBlock);
    RFaceEntity::PropertyLayer.generateId(typeid(RFaceEntity), REntity::PropertyLayer);
    RFaceEntity::PropertyLinetype.generateId(typeid(RFaceEntity), REntity::PropertyLinetype);
    RFaceEntity::PropertyLinetypeScale.generateId(typeid(RFaceEntity), REntity::PropertyLinetypeScale);
    RFaceEntity::PropertyLineweight.generateId(typeid(RFaceEntity), REntity::PropertyLineweight);
    RFaceEntity::PropertyColor.generateId(typeid(RFaceEntity), REntity::PropertyColor);
    RFaceEntity::PropertyDisplayedColor.generateId(typeid(RFaceEntity), REntity::PropertyDisplayedColor);
    RFaceEntity::PropertyDrawOrder.generateId(typeid(RFaceEntity), REntity::PropertyDrawOrder);

    RFaceEntity::PropertyPoint1X.generateId(typeid(RFaceEntity), QT_TRANSLATE_NOOP("REntity", "Point 1"), QT_TRANSLATE_NOOP("REntity", "X"));
    RFaceEntity::PropertyPoint1Y.generateId(typeid(RFaceEntity), QT_TRANSLATE_NOOP("REntity", "Point 1"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RFaceEntity::PropertyPoint1Z.generateId(typeid(RFaceEntity), QT_TRANSLATE_NOOP("REntity", "Point 1"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RFaceEntity::PropertyPoint2X.generateId(typeid(RFaceEntity), QT_TRANSLATE_NOOP("REntity", "Point 2"), QT_TRANSLATE_NOOP("REntity", "X"));
    RFaceEntity::PropertyPoint2Y.generateId(typeid(RFaceEntity), QT_TRANSLATE_NOOP("REntity", "Point 2"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RFaceEntity::PropertyPoint2Z.generateId(typeid(RFaceEntity), QT_TRANSLATE_NOOP("REntity", "Point 2"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RFaceEntity::PropertyPoint3X.generateId(typeid(RFaceEntity), QT_TRANSLATE_NOOP("REntity", "Point 3"), QT_TRANSLATE_NOOP("REntity", "X"));
    RFaceEntity::PropertyPoint3Y.generateId(typeid(RFaceEntity), QT_TRANSLATE_NOOP("REntity", "Point 3"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RFaceEntity::PropertyPoint3Z.generateId(typeid(RFaceEntity), QT_TRANSLATE_NOOP("REntity", "Point 3"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RFaceEntity::PropertyPoint4X.generateId(typeid(RFaceEntity), QT_TRANSLATE_NOOP("REntity", "Point 4"), QT_TRANSLATE_NOOP("REntity", "X"));
    RFaceEntity::PropertyPoint4Y.generateId(typeid(RFaceEntity), QT_TRANSLATE_NOOP("REntity", "Point 4"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RFaceEntity::PropertyPoint4Z.generateId(typeid(RFaceEntity), QT_TRANSLATE_NOOP("REntity", "Point 4"), QT_TRANSLATE_NOOP("REntity", "Z"));

    RFaceEntity::PropertyLength.generateId(typeid(RFaceEntity), "", QT_TRANSLATE_NOOP("REntity", "Length"));
    RFaceEntity::PropertyTotalLength.generateId(typeid(RFaceEntity), "", QT_TRANSLATE_NOOP("REntity", "Total Length"));
}

bool RFaceEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = REntity::setProperty(propertyTypeId, value, transaction);

    if (propertyTypeId==PropertyPoint1X || propertyTypeId==PropertyPoint1Y || propertyTypeId==PropertyPoint1Z) {
        RVector v = data.getVertexAt(0);
        if (propertyTypeId==PropertyPoint1X) {
            v.x = value.toDouble();
        }
        else if (propertyTypeId==PropertyPoint1Y) {
            v.y = value.toDouble();
        }
        else if (propertyTypeId==PropertyPoint1Z) {
            v.z = value.toDouble();
        }
        data.setVertexAt(0, v);
        ret = true;
    }
    else if (propertyTypeId==PropertyPoint2X || propertyTypeId==PropertyPoint2Y || propertyTypeId==PropertyPoint2Z) {
        RVector v = data.getVertexAt(1);
        if (propertyTypeId==PropertyPoint2X) {
            v.x = value.toDouble();
        }
        else if (propertyTypeId==PropertyPoint2Y) {
            v.y = value.toDouble();
        }
        else if (propertyTypeId==PropertyPoint2Z) {
            v.z = value.toDouble();
        }
        data.setVertexAt(1, v);
        ret = true;
    }
    else if (propertyTypeId==PropertyPoint3X || propertyTypeId==PropertyPoint3Y || propertyTypeId==PropertyPoint3Z) {
        RVector v = data.getVertexAt(2);
        if (propertyTypeId==PropertyPoint3X) {
            v.x = value.toDouble();
        }
        else if (propertyTypeId==PropertyPoint3Y) {
            v.y = value.toDouble();
        }
        else if (propertyTypeId==PropertyPoint3Z) {
            v.z = value.toDouble();
        }
        data.setVertexAt(2, v);
        ret = true;
    }
    else if (propertyTypeId==PropertyPoint4X || propertyTypeId==PropertyPoint4Y || propertyTypeId==PropertyPoint4Z) {
        if (data.countVertices()<4) {
            data.appendVertex(RVector(0,0,0));
        }

        RVector v = data.getVertexAt(3);
        if (propertyTypeId==PropertyPoint4X) {
            v.x = value.toDouble();
        }
        else if (propertyTypeId==PropertyPoint4Y) {
            v.y = value.toDouble();
        }
        else if (propertyTypeId==PropertyPoint4Z) {
            v.z = value.toDouble();
        }
        data.setVertexAt(3, v);
        ret = true;
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RFaceEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable,
        bool noAttributes, bool showOnRequest) {
    if (propertyTypeId == PropertyPoint1X) {
        return qMakePair(QVariant(data.getVertexAt(0).x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPoint1Y) {
        return qMakePair(QVariant(data.getVertexAt(0).y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPoint1Z) {
        return qMakePair(QVariant(data.getVertexAt(0).z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPoint2X) {
        return qMakePair(QVariant(data.getVertexAt(1).x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPoint2Y) {
        return qMakePair(QVariant(data.getVertexAt(1).y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPoint2Z) {
        return qMakePair(QVariant(data.getVertexAt(1).z), RPropertyAttributes());
    }else if (propertyTypeId == PropertyPoint3X) {
        return qMakePair(QVariant(data.getVertexAt(2).x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPoint3Y) {
        return qMakePair(QVariant(data.getVertexAt(2).y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPoint3Z) {
        return qMakePair(QVariant(data.getVertexAt(2).z), RPropertyAttributes());
    }else if (propertyTypeId == PropertyPoint4X) {
        if (data.countVertices()<4) {
            return qMakePair(QVariant(), RPropertyAttributes());
        }
        return qMakePair(QVariant(data.getVertexAt(3).x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPoint4Y) {
        if (data.countVertices()<4) {
            return qMakePair(QVariant(), RPropertyAttributes());
        }
        return qMakePair(QVariant(data.getVertexAt(3).y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPoint4Z) {
        if (data.countVertices()<4) {
            return qMakePair(QVariant(), RPropertyAttributes());
        }
        return qMakePair(QVariant(data.getVertexAt(3).z), RPropertyAttributes());
    } else if (propertyTypeId==PropertyLength) {
        return qMakePair(QVariant(data.getLength()), RPropertyAttributes(RPropertyAttributes::ReadOnly));
    } else if (propertyTypeId==PropertyTotalLength) {
        return qMakePair(QVariant(data.getLength()), RPropertyAttributes(RPropertyAttributes::Sum));
    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}


void RFaceEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview);
    Q_UNUSED(forceSelected);

    // note that order of fourth and third vertex is NOT swapped:
    RPolyline pl;
    pl.appendVertex(data.getVertexAt(0));
    pl.appendVertex(data.getVertexAt(1));
    pl.appendVertex(data.getVertexAt(2));
    //if (data.countVertices()>3) {
    //}
    pl.appendVertex(data.getVertexAt(3));
    pl.setClosed(true);

    e.setBrush(Qt::NoBrush);
    e.exportPolyline(pl);
}

void RFaceEntity::print(QDebug dbg) const {
    dbg.nospace() << "RFaceEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", p1: " << getData().getVertexAt(0)
                  << ", p2: " << getData().getVertexAt(1)
                  << ", p3: " << getData().getVertexAt(2)
                  << ", p4: " << getData().getVertexAt(3);
    dbg.nospace() << ")";
}
