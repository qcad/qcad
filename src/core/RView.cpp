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
#include "RView.h"
#include "RDocument.h"

RPropertyTypeId RView::PropertyName;
RPropertyTypeId RView::PropertyCenterPoint;
RPropertyTypeId RView::PropertyWidth;
RPropertyTypeId RView::PropertyHeight;

RView::RView() : RObject(), width(0.0), height(0.0) {
}

RView::RView(RDocument* document, const QString& name, RVector centerPoint,
        double width, double height) :
    RObject(document), name(name), centerPoint(centerPoint), width(width), height(height) {

}


RView::~RView() {
}

void RView::init() {
    RView::PropertyName.generateId(typeid(RView), "", "Name");
    RView::PropertyCenterPoint.generateId(typeid(RView), "", "Center Point");
    RView::PropertyWidth.generateId(typeid(RView), "", "Width");
    RView::PropertyHeight.generateId(typeid(RView), "", "Height");
}

RView* RView::clone() const {
    return new RView(*this);
}

bool RView::setProperty(RPropertyTypeId propertyTypeId,
    const QVariant& value, RTransaction* transaction) {
    bool ret = RObject::setProperty(propertyTypeId, value, transaction);
    ret = RObject::setMember(name, value, PropertyName == propertyTypeId);
    ret = ret || RObject::setMember(centerPoint, value, PropertyCenterPoint == propertyTypeId);
    ret = ret || RObject::setMember(width, value, PropertyWidth == propertyTypeId);
    ret = ret || RObject::setMember(height, value, PropertyHeight == propertyTypeId);
    return ret;
}

QPair<QVariant, RPropertyAttributes> RView::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable,
        bool noAttributes, bool showOnRequest) {

    if (propertyTypeId == PropertyName) {
        return qMakePair(QVariant(name), RPropertyAttributes());
    }
    if (propertyTypeId == PropertyCenterPoint) {
        return qMakePair( QVariant::fromValue(centerPoint), RPropertyAttributes());
    }
    if (propertyTypeId == PropertyWidth) {
        return qMakePair(QVariant(width), RPropertyAttributes());
    }
    if (propertyTypeId == PropertyHeight) {
        return qMakePair(QVariant(height), RPropertyAttributes());
    }

    return RObject::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, const RView& v) {
    dbg.nospace() << "RView(" << (RObject&) v
            << ", name: " << v.getName()
            << ", centerPoint: " << v.getCenterPoint()
            << ", width: " << v.getWidth()
            << ", height: " << v.getHeight()
            << ")";
    return dbg.space();
}
