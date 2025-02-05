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
#include "RTextEntity.h"

RPropertyTypeId RTextEntity::PropertyCustom;
RPropertyTypeId RTextEntity::PropertyHandle;
RPropertyTypeId RTextEntity::PropertyProtected;
RPropertyTypeId RTextEntity::PropertyWorkingSet;
RPropertyTypeId RTextEntity::PropertyType;
RPropertyTypeId RTextEntity::PropertyBlock;
RPropertyTypeId RTextEntity::PropertyLayer;
RPropertyTypeId RTextEntity::PropertyLinetype;
RPropertyTypeId RTextEntity::PropertyLinetypeScale;
RPropertyTypeId RTextEntity::PropertyLineweight;
RPropertyTypeId RTextEntity::PropertyColor;
RPropertyTypeId RTextEntity::PropertyDisplayedColor;
RPropertyTypeId RTextEntity::PropertyDrawOrder;

RPropertyTypeId RTextEntity::PropertySimple;
RPropertyTypeId RTextEntity::PropertyPositionX;
RPropertyTypeId RTextEntity::PropertyPositionY;
RPropertyTypeId RTextEntity::PropertyPositionZ;
RPropertyTypeId RTextEntity::PropertyText;
RPropertyTypeId RTextEntity::PropertyPlainText;
RPropertyTypeId RTextEntity::PropertyFontName;
RPropertyTypeId RTextEntity::PropertyHeight;
RPropertyTypeId RTextEntity::PropertyWidth;
RPropertyTypeId RTextEntity::PropertyAngle;
RPropertyTypeId RTextEntity::PropertyXScale;
RPropertyTypeId RTextEntity::PropertyBold;
RPropertyTypeId RTextEntity::PropertyItalic;
RPropertyTypeId RTextEntity::PropertyLineSpacingFactor;
RPropertyTypeId RTextEntity::PropertyHAlign;
RPropertyTypeId RTextEntity::PropertyVAlign;
RPropertyTypeId RTextEntity::PropertyBackward;
RPropertyTypeId RTextEntity::PropertyUpsideDown;


RTextEntity::RTextEntity(RDocument* document, const RTextData& data) :
    RTextBasedEntity(document), data(document, data) {
}

RTextEntity::~RTextEntity() {
}

void RTextEntity::init() {
    RTextEntity::PropertyCustom.generateId(RTextEntity::getRtti(), RObject::PropertyCustom);
    RTextEntity::PropertyHandle.generateId(RTextEntity::getRtti(), RObject::PropertyHandle);
    RTextEntity::PropertyProtected.generateId(RTextEntity::getRtti(), RObject::PropertyProtected);
    RTextEntity::PropertyWorkingSet.generateId(RTextEntity::getRtti(), RObject::PropertyWorkingSet);
    RTextEntity::PropertyType.generateId(RTextEntity::getRtti(), REntity::PropertyType);
    RTextEntity::PropertyBlock.generateId(RTextEntity::getRtti(), REntity::PropertyBlock);
    RTextEntity::PropertyLayer.generateId(RTextEntity::getRtti(), REntity::PropertyLayer);
    RTextEntity::PropertyLinetype.generateId(RTextEntity::getRtti(), REntity::PropertyLinetype);
    RTextEntity::PropertyLinetypeScale.generateId(RTextEntity::getRtti(), REntity::PropertyLinetypeScale);
    RTextEntity::PropertyLineweight.generateId(RTextEntity::getRtti(), REntity::PropertyLineweight);
    RTextEntity::PropertyColor.generateId(RTextEntity::getRtti(), REntity::PropertyColor);
    RTextEntity::PropertyDisplayedColor.generateId(RTextEntity::getRtti(), REntity::PropertyDisplayedColor);
    RTextEntity::PropertyDrawOrder.generateId(RTextEntity::getRtti(), REntity::PropertyDrawOrder);

    RTextEntity::PropertySimple.generateId(RTextEntity::getRtti(), RTextBasedEntity::PropertySimple);
    RTextEntity::PropertyPositionX.generateId(RTextEntity::getRtti(), RTextBasedEntity::PropertyPositionX);
    RTextEntity::PropertyPositionY.generateId(RTextEntity::getRtti(), RTextBasedEntity::PropertyPositionY);
    RTextEntity::PropertyPositionZ.generateId(RTextEntity::getRtti(), RTextBasedEntity::PropertyPositionZ);
    RTextEntity::PropertyText.generateId(RTextEntity::getRtti(), RTextBasedEntity::PropertyText);
    RTextEntity::PropertyPlainText.generateId(RTextEntity::getRtti(), RTextBasedEntity::PropertyPlainText);
    RTextEntity::PropertyFontName.generateId(RTextEntity::getRtti(), RTextBasedEntity::PropertyFontName);
    RTextEntity::PropertyHeight.generateId(RTextEntity::getRtti(), RTextBasedEntity::PropertyHeight);
    RTextEntity::PropertyWidth.generateId(RTextEntity::getRtti(), RTextBasedEntity::PropertyWidth);
    RTextEntity::PropertyAngle.generateId(RTextEntity::getRtti(), RTextBasedEntity::PropertyAngle);
    RTextEntity::PropertyXScale.generateId(RTextEntity::getRtti(), RTextBasedEntity::PropertyXScale);
    RTextEntity::PropertyBold.generateId(RTextEntity::getRtti(), RTextBasedEntity::PropertyBold);
    RTextEntity::PropertyItalic.generateId(RTextEntity::getRtti(), RTextBasedEntity::PropertyItalic);
    RTextEntity::PropertyLineSpacingFactor.generateId(RTextEntity::getRtti(), RTextBasedEntity::PropertyLineSpacingFactor);
    RTextEntity::PropertyHAlign.generateId(RTextEntity::getRtti(), RTextBasedEntity::PropertyHAlign);
    RTextEntity::PropertyVAlign.generateId(RTextEntity::getRtti(), RTextBasedEntity::PropertyVAlign);
    RTextEntity::PropertyBackward.generateId(RTextEntity::getRtti(), RTextBasedEntity::PropertyBackward);
    RTextEntity::PropertyUpsideDown.generateId(RTextEntity::getRtti(), RTextBasedEntity::PropertyUpsideDown);
}

void RTextEntity::print(QDebug dbg) const {
    dbg.nospace() << "RTextEntity(";
    RTextBasedEntity::print(dbg);
    dbg.nospace() << ")";
}
