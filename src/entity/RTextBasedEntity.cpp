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
#include "RTextBasedEntity.h"
#include "RExporter.h"

RPropertyTypeId RTextBasedEntity::PropertyCustom;
RPropertyTypeId RTextBasedEntity::PropertyHandle;
RPropertyTypeId RTextBasedEntity::PropertyType;
RPropertyTypeId RTextBasedEntity::PropertyBlock;
RPropertyTypeId RTextBasedEntity::PropertyLayer;
RPropertyTypeId RTextBasedEntity::PropertyLinetype;
RPropertyTypeId RTextBasedEntity::PropertyLineweight;
RPropertyTypeId RTextBasedEntity::PropertyColor;
RPropertyTypeId RTextBasedEntity::PropertyDrawOrder;

RPropertyTypeId RTextBasedEntity::PropertySimple;
RPropertyTypeId RTextBasedEntity::PropertyPositionX;
RPropertyTypeId RTextBasedEntity::PropertyPositionY;
RPropertyTypeId RTextBasedEntity::PropertyPositionZ;
RPropertyTypeId RTextBasedEntity::PropertyText;
RPropertyTypeId RTextBasedEntity::PropertyFontName;
RPropertyTypeId RTextBasedEntity::PropertyHeight;
RPropertyTypeId RTextBasedEntity::PropertyAngle;
RPropertyTypeId RTextBasedEntity::PropertyBold;
RPropertyTypeId RTextBasedEntity::PropertyItalic;
RPropertyTypeId RTextBasedEntity::PropertyLineSpacingFactor;
RPropertyTypeId RTextBasedEntity::PropertyHAlign;
RPropertyTypeId RTextBasedEntity::PropertyVAlign;


RTextBasedEntity::RTextBasedEntity(RDocument* document, const RTextBasedData& data,
        RObject::Id objectId) :
    REntity(document, objectId), data(document, data) {
}

RTextBasedEntity::~RTextBasedEntity() {
}

void RTextBasedEntity::init() {
    RTextBasedEntity::PropertyCustom.generateId(typeid(RTextBasedEntity), RObject::PropertyCustom);
    RTextBasedEntity::PropertyHandle.generateId(typeid(RTextBasedEntity), RObject::PropertyHandle);
    RTextBasedEntity::PropertyType.generateId(typeid(RTextBasedEntity), REntity::PropertyType);
    RTextBasedEntity::PropertyBlock.generateId(typeid(RTextBasedEntity), REntity::PropertyBlock);
    RTextBasedEntity::PropertyLayer.generateId(typeid(RTextBasedEntity), REntity::PropertyLayer);
    RTextBasedEntity::PropertyLinetype.generateId(typeid(RTextBasedEntity), REntity::PropertyLinetype);
    RTextBasedEntity::PropertyLineweight.generateId(typeid(RTextBasedEntity), REntity::PropertyLineweight);
    RTextBasedEntity::PropertyColor.generateId(typeid(RTextBasedEntity), REntity::PropertyColor);
    RTextBasedEntity::PropertyDrawOrder.generateId(typeid(RTextBasedEntity), REntity::PropertyDrawOrder);

    RTextBasedEntity::PropertySimple.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Simple"));
    RTextBasedEntity::PropertyPositionX.generateId(typeid(RTextBasedEntity), QT_TRANSLATE_NOOP("REntity", "Position"), QT_TRANSLATE_NOOP("REntity", "X"));
    RTextBasedEntity::PropertyPositionY.generateId(typeid(RTextBasedEntity), QT_TRANSLATE_NOOP("REntity", "Position"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RTextBasedEntity::PropertyPositionZ.generateId(typeid(RTextBasedEntity), QT_TRANSLATE_NOOP("REntity", "Position"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RTextBasedEntity::PropertyText.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Contents"));
    RTextBasedEntity::PropertyFontName.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Font Name"));
    RTextBasedEntity::PropertyHeight.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Height"));
    RTextBasedEntity::PropertyAngle.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Angle"));
    RTextBasedEntity::PropertyBold.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Bold"));
    RTextBasedEntity::PropertyItalic.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Italic"));
    RTextBasedEntity::PropertyLineSpacingFactor.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Line Spacing"));
    RTextBasedEntity::PropertyHAlign.generateId(typeid(RTextBasedEntity), QT_TRANSLATE_NOOP("REntity", "Alignment"), QT_TRANSLATE_NOOP("REntity", "Horizontal"));
    RTextBasedEntity::PropertyVAlign.generateId(typeid(RTextBasedEntity), QT_TRANSLATE_NOOP("REntity", "Alignment"), QT_TRANSLATE_NOOP("REntity", "Vertical"));
}

bool RTextBasedEntity::setProperty(RPropertyTypeId propertyTypeId,
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

QPair<QVariant, RPropertyAttributes> RTextBasedEntity::getProperty(
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


void RTextBasedEntity::exportEntity(RExporter& e, bool preview) const {
    Q_UNUSED(preview);

    e.exportPainterPathSource(data);
}

void RTextBasedEntity::print(QDebug dbg) const {
    dbg.nospace() << "RTextBasedEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", alignmentPoint: " << getAlignmentPoint()
                  << ", position: " << getPosition()
                  << ", text: " << getPlainText()
                  << ", textHeight: " << getTextHeight()
                  << ", textWidth: " << getTextWidth()
                  << ", drawingDirection: " << getDrawingDirection()
                  << ")";
}
