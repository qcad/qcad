/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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
#include "RTextEntity.h"
#include "RExporter.h"

RPropertyTypeId RTextEntity::PropertyCustom;
RPropertyTypeId RTextEntity::PropertyHandle;
RPropertyTypeId RTextEntity::PropertyType;
RPropertyTypeId RTextEntity::PropertyBlock;
RPropertyTypeId RTextEntity::PropertyLayer;
RPropertyTypeId RTextEntity::PropertyLinetype;
RPropertyTypeId RTextEntity::PropertyLineweight;
RPropertyTypeId RTextEntity::PropertyColor;
RPropertyTypeId RTextEntity::PropertyDrawOrder;

RPropertyTypeId RTextEntity::PropertySimple;
RPropertyTypeId RTextEntity::PropertyPositionX;
RPropertyTypeId RTextEntity::PropertyPositionY;
RPropertyTypeId RTextEntity::PropertyPositionZ;
RPropertyTypeId RTextEntity::PropertyText;
RPropertyTypeId RTextEntity::PropertyFontName;
RPropertyTypeId RTextEntity::PropertyHeight;
RPropertyTypeId RTextEntity::PropertyAngle;
RPropertyTypeId RTextEntity::PropertyBold;
RPropertyTypeId RTextEntity::PropertyItalic;
RPropertyTypeId RTextEntity::PropertyLineSpacingFactor;
RPropertyTypeId RTextEntity::PropertyHAlign;
RPropertyTypeId RTextEntity::PropertyVAlign;


RTextEntity::RTextEntity(RDocument* document, const RTextData& data,
        RObject::Id objectId) :
    REntity(document, objectId), data(document, data) {
}

RTextEntity::~RTextEntity() {
}

void RTextEntity::init() {
    RTextEntity::PropertyCustom.generateId(typeid(RTextEntity), RObject::PropertyCustom);
    RTextEntity::PropertyHandle.generateId(typeid(RTextEntity), RObject::PropertyHandle);
    RTextEntity::PropertyType.generateId(typeid(RTextEntity), REntity::PropertyType);
    RTextEntity::PropertyBlock.generateId(typeid(RTextEntity), REntity::PropertyBlock);
    RTextEntity::PropertyLayer.generateId(typeid(RTextEntity), REntity::PropertyLayer);
    RTextEntity::PropertyLinetype.generateId(typeid(RTextEntity), REntity::PropertyLinetype);
    RTextEntity::PropertyLineweight.generateId(typeid(RTextEntity), REntity::PropertyLineweight);
    RTextEntity::PropertyColor.generateId(typeid(RTextEntity), REntity::PropertyColor);
    RTextEntity::PropertyDrawOrder.generateId(typeid(RTextEntity), REntity::PropertyDrawOrder);

    RTextEntity::PropertySimple.generateId(typeid(RTextEntity), "", QT_TRANSLATE_NOOP("REntity", "Simple"));
    RTextEntity::PropertyPositionX.generateId(typeid(RTextEntity), QT_TRANSLATE_NOOP("REntity", "Position"), QT_TRANSLATE_NOOP("REntity", "X"));
    RTextEntity::PropertyPositionY.generateId(typeid(RTextEntity), QT_TRANSLATE_NOOP("REntity", "Position"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RTextEntity::PropertyPositionZ.generateId(typeid(RTextEntity), QT_TRANSLATE_NOOP("REntity", "Position"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RTextEntity::PropertyText.generateId(typeid(RTextEntity), "", QT_TRANSLATE_NOOP("REntity", "Contents"));
    RTextEntity::PropertyFontName.generateId(typeid(RTextEntity), "", QT_TRANSLATE_NOOP("REntity", "Font Name"));
    RTextEntity::PropertyHeight.generateId(typeid(RTextEntity), "", QT_TRANSLATE_NOOP("REntity", "Height"));
    RTextEntity::PropertyAngle.generateId(typeid(RTextEntity), "", QT_TRANSLATE_NOOP("REntity", "Angle"));
    RTextEntity::PropertyBold.generateId(typeid(RTextEntity), "", QT_TRANSLATE_NOOP("REntity", "Bold"));
    RTextEntity::PropertyItalic.generateId(typeid(RTextEntity), "", QT_TRANSLATE_NOOP("REntity", "Italic"));
    RTextEntity::PropertyLineSpacingFactor.generateId(typeid(RTextEntity), "", QT_TRANSLATE_NOOP("REntity", "Line Spacing"));
    RTextEntity::PropertyHAlign.generateId(typeid(RTextEntity), QT_TRANSLATE_NOOP("REntity", "Alignment"), QT_TRANSLATE_NOOP("REntity", "Horizontal"));
    RTextEntity::PropertyVAlign.generateId(typeid(RTextEntity), QT_TRANSLATE_NOOP("REntity", "Alignment"), QT_TRANSLATE_NOOP("REntity", "Vertical"));
}

bool RTextEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value) {
    bool ret = REntity::setProperty(propertyTypeId, value);

    ret = ret || RObject::setMember(data.simple, value, PropertySimple == propertyTypeId);
    ret = ret || RObject::setMember(data.alignmentPoint.x, value, PropertyPositionX == propertyTypeId);
    ret = ret || RObject::setMember(data.alignmentPoint.y, value, PropertyPositionY == propertyTypeId);
    ret = ret || RObject::setMember(data.alignmentPoint.z, value, PropertyPositionZ == propertyTypeId);
    ret = ret || RObject::setMember(data.text, value, PropertyText == propertyTypeId);
    ret = ret || RObject::setMember(data.fontName, value, PropertyFontName == propertyTypeId);
    ret = ret || RObject::setMember(data.textHeight, value, PropertyHeight == propertyTypeId);
    ret = ret || RObject::setMember(data.angle, value, PropertyAngle == propertyTypeId);
    ret = ret || RObject::setMember(data.bold, value, PropertyBold == propertyTypeId);
    ret = ret || RObject::setMember(data.italic, value, PropertyItalic == propertyTypeId);
    ret = ret || RObject::setMember(data.lineSpacingFactor, value, PropertyLineSpacingFactor == propertyTypeId);
    ret = ret || RObject::setMember((int&)data.horizontalAlignment, value.value<int>(), PropertyHAlign == propertyTypeId);
    ret = ret || RObject::setMember((int&)data.verticalAlignment, value.value<int>(), PropertyVAlign == propertyTypeId);

    if (ret) {
        data.update();
    }
    return ret;
}

QPair<QVariant, RPropertyAttributes> RTextEntity::getProperty(
        RPropertyTypeId propertyTypeId, bool humanReadable, bool noAttributes) {
    if (propertyTypeId == PropertyType) {
        return qMakePair(QVariant(RS::EntityText), RPropertyAttributes(
            RPropertyAttributes::ReadOnly));
    } else if (propertyTypeId == PropertySimple) {
        return qMakePair(QVariant(data.simple), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPositionX) {
        return qMakePair(QVariant(data.alignmentPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPositionY) {
        return qMakePair(QVariant(data.alignmentPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPositionZ) {
        return qMakePair(QVariant(data.alignmentPoint.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyText) {
        return qMakePair(QVariant(data.text),
            RPropertyAttributes(RPropertyAttributes::RichText|RPropertyAttributes::Label));
    } else if (propertyTypeId == PropertyFontName) {
        return qMakePair(QVariant(data.fontName),
            RPropertyAttributes(RPropertyAttributes::Style));
    } else if (propertyTypeId == PropertyHeight) {
        return qMakePair(QVariant(data.textHeight), RPropertyAttributes());
    } else if (propertyTypeId == PropertyAngle) {
        return qMakePair(QVariant(data.angle), RPropertyAttributes(
            RPropertyAttributes::Angle));
    } else if (propertyTypeId == PropertyBold) {
        return qMakePair(QVariant(data.bold), RPropertyAttributes());
    } else if (propertyTypeId == PropertyItalic) {
        return qMakePair(QVariant(data.italic), RPropertyAttributes());
    } else if (propertyTypeId == PropertyLineSpacingFactor) {
        return qMakePair(QVariant(data.lineSpacingFactor), RPropertyAttributes());
    } else if (propertyTypeId == PropertyHAlign) {
//        return qMakePair(QVariant(data.horizontalAlignment), RPropertyAttributes(RPropertyAttributes::AffectsOtherProperties));
        return qMakePair(QVariant(data.horizontalAlignment), RPropertyAttributes());
    } else if (propertyTypeId == PropertyVAlign) {
//        return qMakePair(QVariant(data.verticalAlignment), RPropertyAttributes(RPropertyAttributes::AffectsOtherProperties));
        return qMakePair(QVariant(data.verticalAlignment), RPropertyAttributes());
    }
    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes);
}


void RTextEntity::exportEntity(RExporter& e, bool preview) const {
    Q_UNUSED(preview);

    e.exportPainterPathSource(data);
}

void RTextEntity::print(QDebug dbg) const {
    dbg.nospace() << "RTextEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", alignmentPoint: " << getAlignmentPoint()
                  << ", position: " << getPosition()
                  << ", text: " << getPlainText()
                  << ")";
}
