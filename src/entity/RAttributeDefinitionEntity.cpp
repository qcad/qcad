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
RPropertyTypeId RAttributeDefinitionEntity::PropertyWidth;
RPropertyTypeId RAttributeDefinitionEntity::PropertyAngle;
RPropertyTypeId RAttributeDefinitionEntity::PropertyXScale;
RPropertyTypeId RAttributeDefinitionEntity::PropertyBold;
RPropertyTypeId RAttributeDefinitionEntity::PropertyItalic;
RPropertyTypeId RAttributeDefinitionEntity::PropertyLineSpacingFactor;
RPropertyTypeId RAttributeDefinitionEntity::PropertyHAlign;
RPropertyTypeId RAttributeDefinitionEntity::PropertyVAlign;
RPropertyTypeId RAttributeDefinitionEntity::PropertyInvisible;


RAttributeDefinitionEntity::RAttributeDefinitionEntity(RDocument* document, const RAttributeDefinitionData& data) :
    RTextBasedEntity(document), data(document, data) {
}

RAttributeDefinitionEntity::~RAttributeDefinitionEntity() {
}

void RAttributeDefinitionEntity::init() {
    RAttributeDefinitionEntity::PropertyCustom.generateId(RAttributeDefinitionEntity::getRtti(), RObject::PropertyCustom);
    RAttributeDefinitionEntity::PropertyHandle.generateId(RAttributeDefinitionEntity::getRtti(), RObject::PropertyHandle);
    RAttributeDefinitionEntity::PropertyProtected.generateId(RAttributeDefinitionEntity::getRtti(), RObject::PropertyProtected);
    RAttributeDefinitionEntity::PropertyWorkingSet.generateId(RAttributeDefinitionEntity::getRtti(), RObject::PropertyWorkingSet);
    RAttributeDefinitionEntity::PropertyType.generateId(RAttributeDefinitionEntity::getRtti(), REntity::PropertyType);
    RAttributeDefinitionEntity::PropertyBlock.generateId(RAttributeDefinitionEntity::getRtti(), REntity::PropertyBlock);
    RAttributeDefinitionEntity::PropertyLayer.generateId(RAttributeDefinitionEntity::getRtti(), REntity::PropertyLayer);
    RAttributeDefinitionEntity::PropertyLinetype.generateId(RAttributeDefinitionEntity::getRtti(), REntity::PropertyLinetype);
    RAttributeDefinitionEntity::PropertyLinetypeScale.generateId(RAttributeDefinitionEntity::getRtti(), REntity::PropertyLinetypeScale);
    RAttributeDefinitionEntity::PropertyLineweight.generateId(RAttributeDefinitionEntity::getRtti(), REntity::PropertyLineweight);
    RAttributeDefinitionEntity::PropertyColor.generateId(RAttributeDefinitionEntity::getRtti(), REntity::PropertyColor);
    RAttributeDefinitionEntity::PropertyDisplayedColor.generateId(RAttributeDefinitionEntity::getRtti(), REntity::PropertyDisplayedColor);
    RAttributeDefinitionEntity::PropertyDrawOrder.generateId(RAttributeDefinitionEntity::getRtti(), REntity::PropertyDrawOrder);

    RAttributeDefinitionEntity::PropertyPositionX.generateId(RAttributeDefinitionEntity::getRtti(), RTextBasedEntity::PropertyPositionX);
    RAttributeDefinitionEntity::PropertyPositionY.generateId(RAttributeDefinitionEntity::getRtti(), RTextBasedEntity::PropertyPositionY);
    RAttributeDefinitionEntity::PropertyPositionZ.generateId(RAttributeDefinitionEntity::getRtti(), RTextBasedEntity::PropertyPositionZ);
    RAttributeDefinitionEntity::PropertyText.generateId(RAttributeDefinitionEntity::getRtti(), RTextBasedEntity::PropertyText);
    RAttributeDefinitionEntity::PropertyPlainText.generateId(RAttributeDefinitionEntity::getRtti(), RTextBasedEntity::PropertyPlainText);
    RAttributeDefinitionEntity::PropertyFontName.generateId(RAttributeDefinitionEntity::getRtti(), RTextBasedEntity::PropertyFontName);
    RAttributeDefinitionEntity::PropertyHeight.generateId(RAttributeDefinitionEntity::getRtti(), RTextBasedEntity::PropertyHeight);
    RAttributeDefinitionEntity::PropertyWidth.generateId(RAttributeDefinitionEntity::getRtti(), RTextBasedEntity::PropertyWidth);
    RAttributeDefinitionEntity::PropertyAngle.generateId(RAttributeDefinitionEntity::getRtti(), RTextBasedEntity::PropertyAngle);
    RAttributeDefinitionEntity::PropertyXScale.generateId(RAttributeDefinitionEntity::getRtti(), RTextBasedEntity::PropertyXScale);
    RAttributeDefinitionEntity::PropertyBold.generateId(RAttributeDefinitionEntity::getRtti(), RTextBasedEntity::PropertyBold);
    RAttributeDefinitionEntity::PropertyItalic.generateId(RAttributeDefinitionEntity::getRtti(), RTextBasedEntity::PropertyItalic);
    RAttributeDefinitionEntity::PropertyLineSpacingFactor.generateId(RAttributeDefinitionEntity::getRtti(), RTextBasedEntity::PropertyLineSpacingFactor);
    RAttributeDefinitionEntity::PropertyHAlign.generateId(RAttributeDefinitionEntity::getRtti(), RTextBasedEntity::PropertyHAlign);
    RAttributeDefinitionEntity::PropertyVAlign.generateId(RAttributeDefinitionEntity::getRtti(), RTextBasedEntity::PropertyVAlign);

    RAttributeDefinitionEntity::PropertyInvisible.generateId(RAttributeDefinitionEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Invisible"));

    RAttributeDefinitionEntity::PropertyTag.generateId(RAttributeDefinitionEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Tag"));
    RAttributeDefinitionEntity::PropertyPrompt.generateId(RAttributeDefinitionEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Prompt"));
}

bool RAttributeDefinitionEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = RTextBasedEntity::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(data.invisible, value, PropertyInvisible == propertyTypeId);
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
    } else if (propertyTypeId == PropertyInvisible) {
        return qMakePair(QVariant(data.invisible), RPropertyAttributes());
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
