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
#include "RAttributeEntity.h"
#include "RExporter.h"

RPropertyTypeId RAttributeEntity::PropertyCustom;
RPropertyTypeId RAttributeEntity::PropertyHandle;
RPropertyTypeId RAttributeEntity::PropertyProtected;
RPropertyTypeId RAttributeEntity::PropertyWorkingSet;
RPropertyTypeId RAttributeEntity::PropertyType;
RPropertyTypeId RAttributeEntity::PropertyBlock;
RPropertyTypeId RAttributeEntity::PropertyLayer;
RPropertyTypeId RAttributeEntity::PropertyLinetype;
RPropertyTypeId RAttributeEntity::PropertyLinetypeScale;
RPropertyTypeId RAttributeEntity::PropertyLineweight;
RPropertyTypeId RAttributeEntity::PropertyColor;
RPropertyTypeId RAttributeEntity::PropertyDisplayedColor;
RPropertyTypeId RAttributeEntity::PropertyDrawOrder;

RPropertyTypeId RAttributeEntity::PropertyParentId;

RPropertyTypeId RAttributeEntity::PropertyPositionX;
RPropertyTypeId RAttributeEntity::PropertyPositionY;
RPropertyTypeId RAttributeEntity::PropertyPositionZ;
RPropertyTypeId RAttributeEntity::PropertyText;
RPropertyTypeId RAttributeEntity::PropertyPlainText;
RPropertyTypeId RAttributeEntity::PropertyTag;
RPropertyTypeId RAttributeEntity::PropertyFontName;
RPropertyTypeId RAttributeEntity::PropertyHeight;
RPropertyTypeId RAttributeEntity::PropertyWidth;
RPropertyTypeId RAttributeEntity::PropertyAngle;
RPropertyTypeId RAttributeEntity::PropertyXScale;
RPropertyTypeId RAttributeEntity::PropertyBold;
RPropertyTypeId RAttributeEntity::PropertyItalic;
RPropertyTypeId RAttributeEntity::PropertyLineSpacingFactor;
RPropertyTypeId RAttributeEntity::PropertyHAlign;
RPropertyTypeId RAttributeEntity::PropertyVAlign;
RPropertyTypeId RAttributeEntity::PropertyInvisible;
RPropertyTypeId RAttributeEntity::PropertyBackward;
RPropertyTypeId RAttributeEntity::PropertyUpsideDown;


RAttributeEntity::RAttributeEntity(RDocument* document, const RAttributeData& data) :
    RTextBasedEntity(document), data(document, data) {
}

RAttributeEntity::~RAttributeEntity() {
}

void RAttributeEntity::init() {
    RAttributeEntity::PropertyCustom.generateId(RAttributeEntity::getRtti(), RObject::PropertyCustom);
    RAttributeEntity::PropertyHandle.generateId(RAttributeEntity::getRtti(), RObject::PropertyHandle);
    RAttributeEntity::PropertyProtected.generateId(RAttributeEntity::getRtti(), RObject::PropertyProtected);
    RAttributeEntity::PropertyWorkingSet.generateId(RAttributeEntity::getRtti(), RObject::PropertyWorkingSet);
    RAttributeEntity::PropertyType.generateId(RAttributeEntity::getRtti(), REntity::PropertyType);
    RAttributeEntity::PropertyBlock.generateId(RAttributeEntity::getRtti(), REntity::PropertyBlock);
    RAttributeEntity::PropertyLayer.generateId(RAttributeEntity::getRtti(), REntity::PropertyLayer);
    RAttributeEntity::PropertyLinetype.generateId(RAttributeEntity::getRtti(), REntity::PropertyLinetype);
    RAttributeEntity::PropertyLinetypeScale.generateId(RAttributeEntity::getRtti(), REntity::PropertyLinetypeScale);
    RAttributeEntity::PropertyLineweight.generateId(RAttributeEntity::getRtti(), REntity::PropertyLineweight);
    RAttributeEntity::PropertyColor.generateId(RAttributeEntity::getRtti(), REntity::PropertyColor);
    RAttributeEntity::PropertyDisplayedColor.generateId(RAttributeEntity::getRtti(), REntity::PropertyDisplayedColor);
    RAttributeEntity::PropertyDrawOrder.generateId(RAttributeEntity::getRtti(), REntity::PropertyDrawOrder);

    RAttributeEntity::PropertyParentId.generateId(RAttributeEntity::getRtti(), REntity::PropertyParentId);

    RAttributeEntity::PropertyPositionX.generateId(RAttributeEntity::getRtti(), RTextBasedEntity::PropertyPositionX);
    RAttributeEntity::PropertyPositionY.generateId(RAttributeEntity::getRtti(), RTextBasedEntity::PropertyPositionY);
    RAttributeEntity::PropertyPositionZ.generateId(RAttributeEntity::getRtti(), RTextBasedEntity::PropertyPositionZ);
    RAttributeEntity::PropertyText.generateId(RAttributeEntity::getRtti(), RTextBasedEntity::PropertyText);
    RAttributeEntity::PropertyPlainText.generateId(RAttributeEntity::getRtti(), RTextBasedEntity::PropertyPlainText);
    RAttributeEntity::PropertyFontName.generateId(RAttributeEntity::getRtti(), RTextBasedEntity::PropertyFontName);
    RAttributeEntity::PropertyHeight.generateId(RAttributeEntity::getRtti(), RTextBasedEntity::PropertyHeight);
    RAttributeEntity::PropertyWidth.generateId(RAttributeEntity::getRtti(), RTextBasedEntity::PropertyWidth);
    RAttributeEntity::PropertyAngle.generateId(RAttributeEntity::getRtti(), RTextBasedEntity::PropertyAngle);
    RAttributeEntity::PropertyXScale.generateId(RAttributeEntity::getRtti(), RTextBasedEntity::PropertyXScale);
    RAttributeEntity::PropertyBold.generateId(RAttributeEntity::getRtti(), RTextBasedEntity::PropertyBold);
    RAttributeEntity::PropertyItalic.generateId(RAttributeEntity::getRtti(), RTextBasedEntity::PropertyItalic);
    RAttributeEntity::PropertyLineSpacingFactor.generateId(RAttributeEntity::getRtti(), RTextBasedEntity::PropertyLineSpacingFactor);
    RAttributeEntity::PropertyHAlign.generateId(RAttributeEntity::getRtti(), RTextBasedEntity::PropertyHAlign);
    RAttributeEntity::PropertyVAlign.generateId(RAttributeEntity::getRtti(), RTextBasedEntity::PropertyVAlign);
    RAttributeEntity::PropertyBackward.generateId(RAttributeEntity::getRtti(), RTextBasedEntity::PropertyBackward);
    RAttributeEntity::PropertyUpsideDown.generateId(RAttributeEntity::getRtti(), RTextBasedEntity::PropertyUpsideDown);

    RAttributeEntity::PropertyTag.generateId(RAttributeEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Tag"));
    RAttributeEntity::PropertyInvisible.generateId(RAttributeEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Invisible"));
}

bool RAttributeEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = RTextBasedEntity::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(data.tag, value, PropertyTag == propertyTypeId);
    ret = ret || RObject::setMember(data.invisible, value, PropertyInvisible == propertyTypeId);

    if (ret) {
        data.update();
    }
    return ret;
}

QPair<QVariant, RPropertyAttributes> RAttributeEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {

    if (propertyTypeId == PropertyTag) {
        return qMakePair(QVariant(data.tag), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyInvisible) {
        return qMakePair(QVariant(data.invisible), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyText || propertyTypeId == PropertyPlainText) {
        // add custom property title for use by parent (block reference):
        propertyTypeId.setCustomPropertyTitle("Attributes");
        propertyTypeId.setCustomPropertyName(getTag());
        return qMakePair(
            QVariant(data.text),
            RPropertyAttributes(
                RPropertyAttributes::VisibleToParent |
                (propertyTypeId==PropertyPlainText ? RPropertyAttributes::ReadOnly : RPropertyAttributes::NoOptions))
        );
    }

    return RTextBasedEntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

void RAttributeEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(e);
    Q_UNUSED(preview);
    Q_UNUSED(forceSelected);

    // TODO:
    // export attributes as part of the block reference, repeat for array

    if (!isInvisible()) {
        if (e.isTextRenderedAsText()) {
            QList<RPainterPath> paths = e.exportText(getData(), forceSelected);
            e.exportPainterPaths(paths, getPosition().z);
        }
        else {
            e.exportPainterPathSource(getData(), getPosition().z);
        }
    }
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
                  << ", invisible: " << isInvisible()
                  << ")";
}
