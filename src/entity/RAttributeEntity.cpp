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
#include "RAttributeEntity.h"
#include "RExporter.h"

RPropertyTypeId RAttributeEntity::PropertyCustom;
RPropertyTypeId RAttributeEntity::PropertyHandle;
RPropertyTypeId RAttributeEntity::PropertyType;
RPropertyTypeId RAttributeEntity::PropertyBlock;
RPropertyTypeId RAttributeEntity::PropertyLayer;
RPropertyTypeId RAttributeEntity::PropertyLinetype;
RPropertyTypeId RAttributeEntity::PropertyLineweight;
RPropertyTypeId RAttributeEntity::PropertyColor;
RPropertyTypeId RAttributeEntity::PropertyDrawOrder;

RPropertyTypeId RAttributeEntity::PropertySimple;
RPropertyTypeId RAttributeEntity::PropertyPositionX;
RPropertyTypeId RAttributeEntity::PropertyPositionY;
RPropertyTypeId RAttributeEntity::PropertyPositionZ;
RPropertyTypeId RAttributeEntity::PropertyText;
RPropertyTypeId RAttributeEntity::PropertyTag;
RPropertyTypeId RAttributeEntity::PropertyFontName;
RPropertyTypeId RAttributeEntity::PropertyHeight;
RPropertyTypeId RAttributeEntity::PropertyAngle;
RPropertyTypeId RAttributeEntity::PropertyBold;
RPropertyTypeId RAttributeEntity::PropertyItalic;
RPropertyTypeId RAttributeEntity::PropertyLineSpacingFactor;
RPropertyTypeId RAttributeEntity::PropertyHAlign;
RPropertyTypeId RAttributeEntity::PropertyVAlign;


RAttributeEntity::RAttributeEntity(RDocument* document, const RAttributeData& data,
        RObject::Id objectId) :
    RTextBasedEntity(document, objectId), data(document, data) {
}

RAttributeEntity::~RAttributeEntity() {
}

void RAttributeEntity::init() {
    RAttributeEntity::PropertyCustom.generateId(typeid(RAttributeEntity), RObject::PropertyCustom);
    RAttributeEntity::PropertyHandle.generateId(typeid(RAttributeEntity), RObject::PropertyHandle);
    RAttributeEntity::PropertyType.generateId(typeid(RAttributeEntity), REntity::PropertyType);
    RAttributeEntity::PropertyBlock.generateId(typeid(RAttributeEntity), REntity::PropertyBlock);
    RAttributeEntity::PropertyLayer.generateId(typeid(RAttributeEntity), REntity::PropertyLayer);
    RAttributeEntity::PropertyLinetype.generateId(typeid(RAttributeEntity), REntity::PropertyLinetype);
    RAttributeEntity::PropertyLineweight.generateId(typeid(RAttributeEntity), REntity::PropertyLineweight);
    RAttributeEntity::PropertyColor.generateId(typeid(RAttributeEntity), REntity::PropertyColor);
    RAttributeEntity::PropertyDrawOrder.generateId(typeid(RAttributeEntity), REntity::PropertyDrawOrder);

    RAttributeEntity::PropertySimple.generateId(typeid(RAttributeEntity), RTextBasedEntity::PropertySimple);
    RAttributeEntity::PropertyPositionX.generateId(typeid(RAttributeEntity), RTextBasedEntity::PropertyPositionX);
    RAttributeEntity::PropertyPositionY.generateId(typeid(RAttributeEntity), RTextBasedEntity::PropertyPositionY);
    RAttributeEntity::PropertyPositionZ.generateId(typeid(RAttributeEntity), RTextBasedEntity::PropertyPositionZ);
    RAttributeEntity::PropertyText.generateId(typeid(RAttributeEntity), RTextBasedEntity::PropertyText);
    RAttributeEntity::PropertyFontName.generateId(typeid(RAttributeEntity), RTextBasedEntity::PropertyFontName);
    RAttributeEntity::PropertyHeight.generateId(typeid(RAttributeEntity), RTextBasedEntity::PropertyHeight);
    RAttributeEntity::PropertyAngle.generateId(typeid(RAttributeEntity), RTextBasedEntity::PropertyAngle);
    RAttributeEntity::PropertyBold.generateId(typeid(RAttributeEntity), RTextBasedEntity::PropertyBold);
    RAttributeEntity::PropertyItalic.generateId(typeid(RAttributeEntity), RTextBasedEntity::PropertyItalic);
    RAttributeEntity::PropertyLineSpacingFactor.generateId(typeid(RAttributeEntity), RTextBasedEntity::PropertyLineSpacingFactor);
    RAttributeEntity::PropertyHAlign.generateId(typeid(RAttributeEntity), RTextBasedEntity::PropertyHAlign);
    RAttributeEntity::PropertyVAlign.generateId(typeid(RAttributeEntity), RTextBasedEntity::PropertyVAlign);

    RAttributeEntity::PropertyTag.generateId(typeid(RAttributeEntity), "", QT_TRANSLATE_NOOP("REntity", "Tag"));
}

bool RAttributeEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value) {
    bool ret = RTextBasedEntity::setProperty(propertyTypeId, value);

    ret = ret || RObject::setMember(data.tag, value, PropertyTag == propertyTypeId);

    if (ret) {
        data.update();
    }
    return ret;
}

QPair<QVariant, RPropertyAttributes> RAttributeEntity::getProperty(
        RPropertyTypeId propertyTypeId, bool humanReadable, bool noAttributes) {

    if (propertyTypeId == PropertyTag) {
        return qMakePair(QVariant(data.tag), RPropertyAttributes());
    }
    return RTextBasedEntity::getProperty(propertyTypeId, humanReadable, noAttributes);
}

//void RAttributeEntity::setSelected(bool on) {
//    RDocument* doc = getDocument();
//    if (doc==NULL) {
//        RTextBasedEntity::setSelected(on);
//        return;
//    }

//    QSharedPointer<REntity> blockRef = doc->queryEntityDirect(getBlockReferenceId());
//    if (blockRef.isNull()) {
//        RTextBasedEntity::setSelected(on);
//        return;
//    }

//    blockRef->setSelected(on);

//    REntity::setSelected(on);
//}

void RAttributeEntity::exportEntity(RExporter& e, bool preview) const {
    Q_UNUSED(preview);

    RAttributeData data = getData();

    e.exportPainterPathSource(data);
}

void RAttributeEntity::print(QDebug dbg) const {
    dbg.nospace() << "RAttributeEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", alignmentPoint: " << getAlignmentPoint()
                  << ", position: " << getPosition()
                  << ", text: " << getPlainText()
                  << ", tag: " << getTag()
                  << ", block reference ID: " << getParentId()
                  << ", textHeight: " << getTextHeight()
                  << ", textWidth: " << getTextWidth()
                  << ", drawingDirection: " << getDrawingDirection()
                  << ")";
}
