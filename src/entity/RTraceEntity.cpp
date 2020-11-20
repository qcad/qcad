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
#include "RTraceEntity.h"
#include "RExporter.h"
#include "RLine.h"

RPropertyTypeId RTraceEntity::PropertyCustom;
RPropertyTypeId RTraceEntity::PropertyHandle;
RPropertyTypeId RTraceEntity::PropertyProtected;
RPropertyTypeId RTraceEntity::PropertyWorkingSet;
RPropertyTypeId RTraceEntity::PropertyType;
RPropertyTypeId RTraceEntity::PropertyBlock;
RPropertyTypeId RTraceEntity::PropertyLayer;
RPropertyTypeId RTraceEntity::PropertyLinetype;
RPropertyTypeId RTraceEntity::PropertyLinetypeScale;
RPropertyTypeId RTraceEntity::PropertyLineweight;
RPropertyTypeId RTraceEntity::PropertyColor;
RPropertyTypeId RTraceEntity::PropertyDisplayedColor;
RPropertyTypeId RTraceEntity::PropertyDrawOrder;

RPropertyTypeId RTraceEntity::PropertyPoint1X;
RPropertyTypeId RTraceEntity::PropertyPoint1Y;
RPropertyTypeId RTraceEntity::PropertyPoint1Z;
RPropertyTypeId RTraceEntity::PropertyPoint2X;
RPropertyTypeId RTraceEntity::PropertyPoint2Y;
RPropertyTypeId RTraceEntity::PropertyPoint2Z;
RPropertyTypeId RTraceEntity::PropertyPoint3X;
RPropertyTypeId RTraceEntity::PropertyPoint3Y;
RPropertyTypeId RTraceEntity::PropertyPoint3Z;
RPropertyTypeId RTraceEntity::PropertyPoint4X;
RPropertyTypeId RTraceEntity::PropertyPoint4Y;
RPropertyTypeId RTraceEntity::PropertyPoint4Z;

RPropertyTypeId RTraceEntity::PropertyLength;
RPropertyTypeId RTraceEntity::PropertyTotalLength;


RTraceEntity::RTraceEntity(RDocument* document, const RTraceData& data) :
    REntity(document), data(document, data) {
}

RTraceEntity::~RTraceEntity() {
}

void RTraceEntity::init() {
    RTraceEntity::PropertyCustom.generateId(typeid(RTraceEntity), RObject::PropertyCustom);
    RTraceEntity::PropertyHandle.generateId(typeid(RTraceEntity), RObject::PropertyHandle);
    RTraceEntity::PropertyProtected.generateId(typeid(RTraceEntity), RObject::PropertyProtected);
    RTraceEntity::PropertyWorkingSet.generateId(typeid(RTraceEntity), RObject::PropertyWorkingSet);
    RTraceEntity::PropertyType.generateId(typeid(RTraceEntity), REntity::PropertyType);
    RTraceEntity::PropertyBlock.generateId(typeid(RTraceEntity), REntity::PropertyBlock);
    RTraceEntity::PropertyLayer.generateId(typeid(RTraceEntity), REntity::PropertyLayer);
    RTraceEntity::PropertyLinetype.generateId(typeid(RTraceEntity), REntity::PropertyLinetype);
    RTraceEntity::PropertyLinetypeScale.generateId(typeid(RTraceEntity), REntity::PropertyLinetypeScale);
    RTraceEntity::PropertyLineweight.generateId(typeid(RTraceEntity), REntity::PropertyLineweight);
    RTraceEntity::PropertyColor.generateId(typeid(RTraceEntity), REntity::PropertyColor);
    RTraceEntity::PropertyDisplayedColor.generateId(typeid(RTraceEntity), REntity::PropertyDisplayedColor);
    RTraceEntity::PropertyDrawOrder.generateId(typeid(RTraceEntity), REntity::PropertyDrawOrder);

    RTraceEntity::PropertyPoint1X.generateId(typeid(RTraceEntity), QT_TRANSLATE_NOOP("REntity", "Point 1"), QT_TRANSLATE_NOOP("REntity", "X"));
    RTraceEntity::PropertyPoint1Y.generateId(typeid(RTraceEntity), QT_TRANSLATE_NOOP("REntity", "Point 1"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RTraceEntity::PropertyPoint1Z.generateId(typeid(RTraceEntity), QT_TRANSLATE_NOOP("REntity", "Point 1"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RTraceEntity::PropertyPoint2X.generateId(typeid(RTraceEntity), QT_TRANSLATE_NOOP("REntity", "Point 2"), QT_TRANSLATE_NOOP("REntity", "X"));
    RTraceEntity::PropertyPoint2Y.generateId(typeid(RTraceEntity), QT_TRANSLATE_NOOP("REntity", "Point 2"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RTraceEntity::PropertyPoint2Z.generateId(typeid(RTraceEntity), QT_TRANSLATE_NOOP("REntity", "Point 2"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RTraceEntity::PropertyPoint3X.generateId(typeid(RTraceEntity), QT_TRANSLATE_NOOP("REntity", "Point 3"), QT_TRANSLATE_NOOP("REntity", "X"));
    RTraceEntity::PropertyPoint3Y.generateId(typeid(RTraceEntity), QT_TRANSLATE_NOOP("REntity", "Point 3"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RTraceEntity::PropertyPoint3Z.generateId(typeid(RTraceEntity), QT_TRANSLATE_NOOP("REntity", "Point 3"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RTraceEntity::PropertyPoint4X.generateId(typeid(RTraceEntity), QT_TRANSLATE_NOOP("REntity", "Point 4"), QT_TRANSLATE_NOOP("REntity", "X"));
    RTraceEntity::PropertyPoint4Y.generateId(typeid(RTraceEntity), QT_TRANSLATE_NOOP("REntity", "Point 4"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RTraceEntity::PropertyPoint4Z.generateId(typeid(RTraceEntity), QT_TRANSLATE_NOOP("REntity", "Point 4"), QT_TRANSLATE_NOOP("REntity", "Z"));

    RTraceEntity::PropertyLength.generateId(typeid(RTraceEntity), "", QT_TRANSLATE_NOOP("REntity", "Length"));
    RTraceEntity::PropertyTotalLength.generateId(typeid(RTraceEntity), "", QT_TRANSLATE_NOOP("REntity", "Total Length"));
}

bool RTraceEntity::setProperty(RPropertyTypeId propertyTypeId,
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

QPair<QVariant, RPropertyAttributes> RTraceEntity::getProperty(
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


void RTraceEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview)
    Q_UNUSED(forceSelected)

    // note that order of fourth and third vertex is swapped:
    RPolyline pl;
    pl.appendVertex(data.getVertexAt(0));
    pl.appendVertex(data.getVertexAt(1));
    if (data.countVertices()>3) {
        pl.appendVertex(data.getVertexAt(3));
    }
    pl.appendVertex(data.getVertexAt(2));
    pl.setClosed(true);

    e.exportPolyline(pl);
}

void RTraceEntity::print(QDebug dbg) const {
    dbg.nospace() << "RTraceEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", p1: " << getData().getVertexAt(0)
                  << ", p2: " << getData().getVertexAt(1)
                  << ", p3: " << getData().getVertexAt(2)
                  << ", p4: " << getData().getVertexAt(3);
    dbg.nospace() << ")";
}
