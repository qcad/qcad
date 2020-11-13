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
#include "RToleranceEntity.h"
#include "RMetaTypes.h"
#include "RStorage.h"

RPropertyTypeId RToleranceEntity::PropertyCustom;
RPropertyTypeId RToleranceEntity::PropertyHandle;
RPropertyTypeId RToleranceEntity::PropertyProtected;
RPropertyTypeId RToleranceEntity::PropertyWorkingSet;
RPropertyTypeId RToleranceEntity::PropertyType;
RPropertyTypeId RToleranceEntity::PropertyBlock;
RPropertyTypeId RToleranceEntity::PropertyLayer;
RPropertyTypeId RToleranceEntity::PropertyLinetype;
RPropertyTypeId RToleranceEntity::PropertyLinetypeScale;
RPropertyTypeId RToleranceEntity::PropertyLineweight;
RPropertyTypeId RToleranceEntity::PropertyColor;
RPropertyTypeId RToleranceEntity::PropertyDisplayedColor;
RPropertyTypeId RToleranceEntity::PropertyDrawOrder;

RPropertyTypeId RToleranceEntity::PropertyLocationX;
RPropertyTypeId RToleranceEntity::PropertyLocationY;
RPropertyTypeId RToleranceEntity::PropertyLocationZ;
RPropertyTypeId RToleranceEntity::PropertyDirectionX;
RPropertyTypeId RToleranceEntity::PropertyDirectionY;
RPropertyTypeId RToleranceEntity::PropertyDirectionZ;
RPropertyTypeId RToleranceEntity::PropertyText;
RPropertyTypeId RToleranceEntity::PropertyDimScale;


RToleranceEntity::RToleranceEntity(RDocument* document, const RToleranceData& data) :
    REntity(document), data(document, data) {
    RDebug::incCounter("RToleranceEntity");
}

RToleranceEntity::RToleranceEntity(const RToleranceEntity& other) : REntity(other) {
    RDebug::incCounter("RToleranceEntity");
    data = other.data;
}

RToleranceEntity::~RToleranceEntity() {
    RDebug::decCounter("RToleranceEntity");
}

void RToleranceEntity::init() {
    RToleranceEntity::PropertyCustom.generateId(typeid(RToleranceEntity), RObject::PropertyCustom);
    RToleranceEntity::PropertyHandle.generateId(typeid(RToleranceEntity), RObject::PropertyHandle);
    RToleranceEntity::PropertyProtected.generateId(typeid(RToleranceEntity), RObject::PropertyProtected);
    RToleranceEntity::PropertyWorkingSet.generateId(typeid(RToleranceEntity), RObject::PropertyWorkingSet);
    RToleranceEntity::PropertyType.generateId(typeid(RToleranceEntity), REntity::PropertyType);
    RToleranceEntity::PropertyBlock.generateId(typeid(RToleranceEntity), REntity::PropertyBlock);
    RToleranceEntity::PropertyLayer.generateId(typeid(RToleranceEntity), REntity::PropertyLayer);
    RToleranceEntity::PropertyLinetype.generateId(typeid(RToleranceEntity), REntity::PropertyLinetype);
    RToleranceEntity::PropertyLinetypeScale.generateId(typeid(RToleranceEntity), REntity::PropertyLinetypeScale);
    RToleranceEntity::PropertyLineweight.generateId(typeid(RToleranceEntity), REntity::PropertyLineweight);
    RToleranceEntity::PropertyColor.generateId(typeid(RToleranceEntity), REntity::PropertyColor);
    RToleranceEntity::PropertyDisplayedColor.generateId(typeid(RToleranceEntity), REntity::PropertyDisplayedColor);
    RToleranceEntity::PropertyDrawOrder.generateId(typeid(RToleranceEntity), REntity::PropertyDrawOrder);

    RToleranceEntity::PropertyLocationX.generateId(typeid(RToleranceEntity), QT_TRANSLATE_NOOP("REntity", "Location"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RToleranceEntity::PropertyLocationY.generateId(typeid(RToleranceEntity), QT_TRANSLATE_NOOP("REntity", "Location"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RToleranceEntity::PropertyLocationZ.generateId(typeid(RToleranceEntity), QT_TRANSLATE_NOOP("REntity", "Location"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
    RToleranceEntity::PropertyDirectionX.generateId(typeid(RToleranceEntity), QT_TRANSLATE_NOOP("REntity", "Direction"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RToleranceEntity::PropertyDirectionY.generateId(typeid(RToleranceEntity), QT_TRANSLATE_NOOP("REntity", "Direction"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RToleranceEntity::PropertyDirectionZ.generateId(typeid(RToleranceEntity), QT_TRANSLATE_NOOP("REntity", "Direction"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
    RToleranceEntity::PropertyText.generateId(typeid(RToleranceEntity), "", QT_TRANSLATE_NOOP("REntity", "Text"));
    RToleranceEntity::PropertyDimScale.generateId(typeid(RToleranceEntity), "", QT_TRANSLATE_NOOP("REntity", "Scale"), false, RPropertyAttributes::Geometry);
}

bool RToleranceEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = REntity::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(data.location.x, value, PropertyLocationX == propertyTypeId);
    ret = ret || RObject::setMember(data.location.y, value, PropertyLocationY == propertyTypeId);
    ret = ret || RObject::setMember(data.location.z, value, PropertyLocationZ == propertyTypeId);
    ret = ret || RObject::setMember(data.direction.x, value, PropertyDirectionX == propertyTypeId);
    ret = ret || RObject::setMember(data.direction.y, value, PropertyDirectionY == propertyTypeId);
    ret = ret || RObject::setMember(data.direction.z, value, PropertyDirectionZ == propertyTypeId);
    ret = ret || RObject::setMember(getData().text, value, PropertyText == propertyTypeId);

    if (PropertyDimScale == propertyTypeId) {
        ret = ret || RObject::setMember(data.dimScaleOverride, value, PropertyDimScale == propertyTypeId);
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RToleranceEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {

    if (propertyTypeId == PropertyLocationX) {
        return qMakePair(QVariant(data.location.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyLocationY) {
        return qMakePair(QVariant(data.location.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyLocationZ) {
        return qMakePair(QVariant(data.location.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDirectionX) {
        return qMakePair(QVariant(data.direction.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDirectionY) {
        return qMakePair(QVariant(data.direction.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDirectionZ) {
        return qMakePair(QVariant(data.direction.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyText) {
        return qMakePair(QVariant(getData().text), RPropertyAttributes(RPropertyAttributes::RichText|RPropertyAttributes::Label));
    }
    else if (propertyTypeId == PropertyDimScale) {
        return qMakePair(QVariant(data.dimScaleOverride), RPropertyAttributes());
    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}


void RToleranceEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview)
    Q_UNUSED(forceSelected)

    // TODO

    // split text string at %%v (|):
    //QStringList subs = getText().split("%%v", QString::SkipEmptyParts);

    double dimtxt = getDimtxt();
    RVector cursor = getLocation() + RVector(dimtxt/2.0, 0);
    QBrush brush = e.getBrush();
    QList<RTextData> labels = getTextLabels();

    // render text strings with distance of h:
    for (int i=0; i<labels.length(); i++) {
        RTextData label = labels[i];

        //qDebug() << "sub:" << sub;

//        RTextData textData(cursor,
//                     cursor,
//                     dimtxt,
//                     100.0,
//                     RS::VAlignMiddle,
//                     RS::HAlignLeft,
//                     RS::LeftToRight,
//                     RS::AtLeast,
//                     1.0,
//                     sub,
//                     "Arial",
//                     false,
//                     false,
//                     0,
//                     false);

        if (label.isSane()) {
            if (e.isTextRenderedAsText()) {
                QList<RPainterPath> paths = e.exportText(label, isSelected());
                e.exportPainterPaths(paths);
            }
            else {
                // render text as paths:
                // set brush explicitely:
                QVariant v = getDocument()->getKnownVariable(RS::DIMCLRT, RColor(RColor::ByBlock));
                RColor textColor = v.value<RColor>();
                if (!textColor.isByBlock()) {
                    brush.setColor(textColor);
                }
                e.setBrush(brush);
                e.exportPainterPathSource(label);
            }
        }

        cursor += RVector(label.getBoundingBox().getWidth(), 0);
        cursor += RVector(dimtxt, 0);
    }

    // render frame:
    QList<RLine> lines = getFrame();
    for (int i=0; i<lines.length(); i++) {
        RLine line = lines[i];
        e.exportLine(line);
    }

}

void RToleranceEntity::print(QDebug dbg) const {
    dbg.nospace() << "RToleranceEntity(";
    REntity::print(dbg);
    dbg.nospace()  << ")";
}
