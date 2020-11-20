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
#include "RAttributeDefinitionEntity.h"
#include "RExporter.h"

RPropertyTypeId RAttributeDefinitionEntity::PropertyCustom;
RPropertyTypeId RAttributeDefinitionEntity::PropertyHandle;
RPropertyTypeId RAttributeDefinitionEntity::PropertyProtected;
RPropertyTypeId RAttributeDefinitionEntity::PropertyWorkingSet;
RPropertyTypeId RAttributeDefinitionEntity::PropertyType;
RPropertyTypeId RAttributeDefinitionEntity::PropertyBlock;
RPropertyTypeId RAttributeDefinitionEntity::PropertyLayer;
RPropertyTypeId RAttributeDefinitionEntity::PropertyLinetype;
RPropertyTypeId RAttributeDefinitionEntity::PropertyLinetypeScale;
RPropertyTypeId RAttributeDefinitionEntity::PropertyLineweight;
RPropertyTypeId RAttributeDefinitionEntity::PropertyColor;
RPropertyTypeId RAttributeDefinitionEntity::PropertyDisplayedColor;
RPropertyTypeId RAttributeDefinitionEntity::PropertyDrawOrder;

RPropertyTypeId RAttributeDefinitionEntity::PropertyPositionX;
RPropertyTypeId RAttributeDefinitionEntity::PropertyPositionY;
RPropertyTypeId RAttributeDefinitionEntity::PropertyPositionZ;
RPropertyTypeId RAttributeDefinitionEntity::PropertyText;
RPropertyTypeId RAttributeDefinitionEntity::PropertyPlainText;
RPropertyTypeId RAttributeDefinitionEntity::PropertyTag;
RPropertyTypeId RAttributeDefinitionEntity::PropertyPrompt;
RPropertyTypeId RAttributeDefinitionEntity::PropertyFontName;
RPropertyTypeId RAttributeDefinitionEntity::PropertyHeight;
RPropertyTypeId RAttributeDefinitionEntity::PropertyAngle;
RPropertyTypeId RAttributeDefinitionEntity::PropertyXScale;
RPropertyTypeId RAttributeDefinitionEntity::PropertyBold;
RPropertyTypeId RAttributeDefinitionEntity::PropertyItalic;
RPropertyTypeId RAttributeDefinitionEntity::PropertyLineSpacingFactor;
RPropertyTypeId RAttributeDefinitionEntity::PropertyHAlign;
RPropertyTypeId RAttributeDefinitionEntity::PropertyVAlign;


RAttributeDefinitionEntity::RAttributeDefinitionEntity(RDocument* document, const RAttributeDefinitionData& data) :
    RTextBasedEntity(document), data(document, data) {
}

RAttributeDefinitionEntity::~RAttributeDefinitionEntity() {
}

void RAttributeDefinitionEntity::init() {
    RAttributeDefinitionEntity::PropertyCustom.generateId(typeid(RAttributeDefinitionEntity), RObject::PropertyCustom);
    RAttributeDefinitionEntity::PropertyHandle.generateId(typeid(RAttributeDefinitionEntity), RObject::PropertyHandle);
    RAttributeDefinitionEntity::PropertyProtected.generateId(typeid(RAttributeDefinitionEntity), RObject::PropertyProtected);
    RAttributeDefinitionEntity::PropertyWorkingSet.generateId(typeid(RAttributeDefinitionEntity), RObject::PropertyWorkingSet);
    RAttributeDefinitionEntity::PropertyType.generateId(typeid(RAttributeDefinitionEntity), REntity::PropertyType);
    RAttributeDefinitionEntity::PropertyBlock.generateId(typeid(RAttributeDefinitionEntity), REntity::PropertyBlock);
    RAttributeDefinitionEntity::PropertyLayer.generateId(typeid(RAttributeDefinitionEntity), REntity::PropertyLayer);
    RAttributeDefinitionEntity::PropertyLinetype.generateId(typeid(RAttributeDefinitionEntity), REntity::PropertyLinetype);
    RAttributeDefinitionEntity::PropertyLinetypeScale.generateId(typeid(RAttributeDefinitionEntity), REntity::PropertyLinetypeScale);
    RAttributeDefinitionEntity::PropertyLineweight.generateId(typeid(RAttributeDefinitionEntity), REntity::PropertyLineweight);
    RAttributeDefinitionEntity::PropertyColor.generateId(typeid(RAttributeDefinitionEntity), REntity::PropertyColor);
    RAttributeDefinitionEntity::PropertyDisplayedColor.generateId(typeid(RAttributeDefinitionEntity), REntity::PropertyDisplayedColor);
    RAttributeDefinitionEntity::PropertyDrawOrder.generateId(typeid(RAttributeDefinitionEntity), REntity::PropertyDrawOrder);

    RAttributeDefinitionEntity::PropertyPositionX.generateId(typeid(RAttributeDefinitionEntity), RTextBasedEntity::PropertyPositionX);
    RAttributeDefinitionEntity::PropertyPositionY.generateId(typeid(RAttributeDefinitionEntity), RTextBasedEntity::PropertyPositionY);
    RAttributeDefinitionEntity::PropertyPositionZ.generateId(typeid(RAttributeDefinitionEntity), RTextBasedEntity::PropertyPositionZ);
    RAttributeDefinitionEntity::PropertyText.generateId(typeid(RAttributeDefinitionEntity), RTextBasedEntity::PropertyText);
    RAttributeDefinitionEntity::PropertyPlainText.generateId(typeid(RAttributeDefinitionEntity), RTextBasedEntity::PropertyPlainText);
    RAttributeDefinitionEntity::PropertyFontName.generateId(typeid(RAttributeDefinitionEntity), RTextBasedEntity::PropertyFontName);
    RAttributeDefinitionEntity::PropertyHeight.generateId(typeid(RAttributeDefinitionEntity), RTextBasedEntity::PropertyHeight);
    RAttributeDefinitionEntity::PropertyAngle.generateId(typeid(RAttributeDefinitionEntity), RTextBasedEntity::PropertyAngle);
    RAttributeDefinitionEntity::PropertyXScale.generateId(typeid(RAttributeDefinitionEntity), RTextBasedEntity::PropertyXScale);
    RAttributeDefinitionEntity::PropertyBold.generateId(typeid(RAttributeDefinitionEntity), RTextBasedEntity::PropertyBold);
    RAttributeDefinitionEntity::PropertyItalic.generateId(typeid(RAttributeDefinitionEntity), RTextBasedEntity::PropertyItalic);
    RAttributeDefinitionEntity::PropertyLineSpacingFactor.generateId(typeid(RAttributeDefinitionEntity), RTextBasedEntity::PropertyLineSpacingFactor);
    RAttributeDefinitionEntity::PropertyHAlign.generateId(typeid(RAttributeDefinitionEntity), RTextBasedEntity::PropertyHAlign);
    RAttributeDefinitionEntity::PropertyVAlign.generateId(typeid(RAttributeDefinitionEntity), RTextBasedEntity::PropertyVAlign);

    RAttributeDefinitionEntity::PropertyTag.generateId(typeid(RAttributeDefinitionEntity), "", QT_TRANSLATE_NOOP("REntity", "Tag"));
    RAttributeDefinitionEntity::PropertyPrompt.generateId(typeid(RAttributeDefinitionEntity), "", QT_TRANSLATE_NOOP("REntity", "Prompt"));
}

bool RAttributeDefinitionEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = RTextBasedEntity::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(data.tag, value, PropertyTag == propertyTypeId);
    ret = ret || RObject::setMember(data.prompt, value, PropertyPrompt == propertyTypeId);

    if (ret) {
        data.update();
    }
    return ret;
}

QPair<QVariant, RPropertyAttributes> RAttributeDefinitionEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {

    if (propertyTypeId == PropertyTag) {
        return qMakePair(QVariant(data.tag), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPrompt) {
        return qMakePair(QVariant(data.prompt), RPropertyAttributes());
    }
    return RTextBasedEntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

//void RAttributeDefinitionEntity::exportEntity(RExporter& e, bool preview) const {
//    Q_UNUSED(preview);

//    RBlock::Id currentBlockId = e.getDocument().getCurrentBlockId();

//    // attribute definition is being rendered in the context of the
//    // block it is in (show tag):
//    if (getBlockId()==currentBlockId) {
//        RAttributeDefinitionData data = getData();
//        data.setText(getTag());
//        e.exportPainterPathSource(data);
//    }
//}

void RAttributeDefinitionEntity::print(QDebug dbg) const {
    dbg.nospace() << "RAttributeDefinitionEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", alignmentPoint: " << getAlignmentPoint()
                  << ", position: " << getPosition()
                  << ", text: " << getPlainText()
                  << ", tag: " << getTag()
                  << ", prompt: " << getPrompt()
                  << ", textHeight: " << getTextHeight()
                  << ", textWidth: " << getTextWidth()
                  << ", drawingDirection: " << getDrawingDirection()
                  << ")";
}
