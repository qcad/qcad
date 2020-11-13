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
#include "RSolidEntity.h"
#include "RExporter.h"
#include "RLine.h"

RPropertyTypeId RSolidEntity::PropertyCustom;
RPropertyTypeId RSolidEntity::PropertyHandle;
RPropertyTypeId RSolidEntity::PropertyProtected;
RPropertyTypeId RSolidEntity::PropertyWorkingSet;
RPropertyTypeId RSolidEntity::PropertyType;
RPropertyTypeId RSolidEntity::PropertyBlock;
RPropertyTypeId RSolidEntity::PropertyLayer;
RPropertyTypeId RSolidEntity::PropertyLinetype;
RPropertyTypeId RSolidEntity::PropertyLinetypeScale;
RPropertyTypeId RSolidEntity::PropertyLineweight;
RPropertyTypeId RSolidEntity::PropertyColor;
RPropertyTypeId RSolidEntity::PropertyDisplayedColor;
RPropertyTypeId RSolidEntity::PropertyDrawOrder;

RPropertyTypeId RSolidEntity::PropertyPoint1X;
RPropertyTypeId RSolidEntity::PropertyPoint1Y;
RPropertyTypeId RSolidEntity::PropertyPoint1Z;
RPropertyTypeId RSolidEntity::PropertyPoint2X;
RPropertyTypeId RSolidEntity::PropertyPoint2Y;
RPropertyTypeId RSolidEntity::PropertyPoint2Z;
RPropertyTypeId RSolidEntity::PropertyPoint3X;
RPropertyTypeId RSolidEntity::PropertyPoint3Y;
RPropertyTypeId RSolidEntity::PropertyPoint3Z;
RPropertyTypeId RSolidEntity::PropertyPoint4X;
RPropertyTypeId RSolidEntity::PropertyPoint4Y;
RPropertyTypeId RSolidEntity::PropertyPoint4Z;

RPropertyTypeId RSolidEntity::PropertyLength;
RPropertyTypeId RSolidEntity::PropertyTotalLength;


RSolidEntity::RSolidEntity(RDocument* document, const RSolidData& data) :
    REntity(document), data(document, data) {
}

RSolidEntity::~RSolidEntity() {
}

void RSolidEntity::init() {
    RSolidEntity::PropertyCustom.generateId(typeid(RSolidEntity), RObject::PropertyCustom);
    RSolidEntity::PropertyHandle.generateId(typeid(RSolidEntity), RObject::PropertyHandle);
    RSolidEntity::PropertyProtected.generateId(typeid(RSolidEntity), RObject::PropertyProtected);
    RSolidEntity::PropertyWorkingSet.generateId(typeid(RSolidEntity), RObject::PropertyWorkingSet);
    RSolidEntity::PropertyType.generateId(typeid(RSolidEntity), REntity::PropertyType);
    RSolidEntity::PropertyBlock.generateId(typeid(RSolidEntity), REntity::PropertyBlock);
    RSolidEntity::PropertyLayer.generateId(typeid(RSolidEntity), REntity::PropertyLayer);
    RSolidEntity::PropertyLinetype.generateId(typeid(RSolidEntity), REntity::PropertyLinetype);
    RSolidEntity::PropertyLinetypeScale.generateId(typeid(RSolidEntity), REntity::PropertyLinetypeScale);
    RSolidEntity::PropertyLineweight.generateId(typeid(RSolidEntity), REntity::PropertyLineweight);
    RSolidEntity::PropertyColor.generateId(typeid(RSolidEntity), REntity::PropertyColor);
    RSolidEntity::PropertyDisplayedColor.generateId(typeid(RSolidEntity), REntity::PropertyDisplayedColor);
    RSolidEntity::PropertyDrawOrder.generateId(typeid(RSolidEntity), REntity::PropertyDrawOrder);

    RSolidEntity::PropertyPoint1X.generateId(typeid(RSolidEntity), QT_TRANSLATE_NOOP("REntity", "Point 1"), QT_TRANSLATE_NOOP("REntity", "X"));
    RSolidEntity::PropertyPoint1Y.generateId(typeid(RSolidEntity), QT_TRANSLATE_NOOP("REntity", "Point 1"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RSolidEntity::PropertyPoint1Z.generateId(typeid(RSolidEntity), QT_TRANSLATE_NOOP("REntity", "Point 1"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RSolidEntity::PropertyPoint2X.generateId(typeid(RSolidEntity), QT_TRANSLATE_NOOP("REntity", "Point 2"), QT_TRANSLATE_NOOP("REntity", "X"));
    RSolidEntity::PropertyPoint2Y.generateId(typeid(RSolidEntity), QT_TRANSLATE_NOOP("REntity", "Point 2"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RSolidEntity::PropertyPoint2Z.generateId(typeid(RSolidEntity), QT_TRANSLATE_NOOP("REntity", "Point 2"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RSolidEntity::PropertyPoint3X.generateId(typeid(RSolidEntity), QT_TRANSLATE_NOOP("REntity", "Point 3"), QT_TRANSLATE_NOOP("REntity", "X"));
    RSolidEntity::PropertyPoint3Y.generateId(typeid(RSolidEntity), QT_TRANSLATE_NOOP("REntity", "Point 3"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RSolidEntity::PropertyPoint3Z.generateId(typeid(RSolidEntity), QT_TRANSLATE_NOOP("REntity", "Point 3"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RSolidEntity::PropertyPoint4X.generateId(typeid(RSolidEntity), QT_TRANSLATE_NOOP("REntity", "Point 4"), QT_TRANSLATE_NOOP("REntity", "X"));
    RSolidEntity::PropertyPoint4Y.generateId(typeid(RSolidEntity), QT_TRANSLATE_NOOP("REntity", "Point 4"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RSolidEntity::PropertyPoint4Z.generateId(typeid(RSolidEntity), QT_TRANSLATE_NOOP("REntity", "Point 4"), QT_TRANSLATE_NOOP("REntity", "Z"));

    RSolidEntity::PropertyLength.generateId(typeid(RSolidEntity), "", QT_TRANSLATE_NOOP("REntity", "Length"));
    RSolidEntity::PropertyTotalLength.generateId(typeid(RSolidEntity), "", QT_TRANSLATE_NOOP("REntity", "Total Length"));
}

bool RSolidEntity::setProperty(RPropertyTypeId propertyTypeId,
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

QPair<QVariant, RPropertyAttributes> RSolidEntity::getProperty(
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


void RSolidEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview);
    Q_UNUSED(forceSelected);

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

void RSolidEntity::print(QDebug dbg) const {
    dbg.nospace() << "RSolidEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", p1: " << getData().getVertexAt(0)
                  << ", p2: " << getData().getVertexAt(1)
                  << ", p3: " << getData().getVertexAt(2);

    if (getData().countVertices()>3) {
        dbg.nospace() << ", p4: " << getData().getVertexAt(3);
    }

    dbg.nospace() << ")";
}
