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
#include "RDimAlignedData.h"
#include "RUnit.h"

RDimAlignedData::RDimAlignedData() {
}

RDimAlignedData::RDimAlignedData(RDocument* document, const RDimAlignedData& data)
    : RDimLinearData(document) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

/**
 * \param extensionPoint1 Definition point. Startpoint of the
 *         first extension line.
 * \param extensionPoint2 Definition point. Startpoint of the
 *         second extension line.
 */
RDimAlignedData::RDimAlignedData(const RDimensionData& dimData,
                                 const RVector& extensionPoint1,
                                 const RVector& extensionPoint2)
    : RDimLinearData(dimData, extensionPoint1, extensionPoint2) {

}

RBox RDimAlignedData::getBoundingBox(bool ignoreEmpty) const {
    boundingBox = RDimensionData::getBoundingBox(ignoreEmpty);

    // 20200306: this breaks area selection of dimensions
    // if extension points are far away from dimension shapes:
    //if (!hasDimensionBlockReference()) {
    //    boundingBox.growToInclude(extensionPoint1);
    //    boundingBox.growToInclude(extensionPoint2);
    //}

    return boundingBox;
}

QList<RRefPoint> RDimAlignedData::getReferencePoints(RS::ProjectionRenderingHint hint) const {

    Q_UNUSED(hint)

    // we don't want to add definitionPoint, so we don't call the base
    // class implementation here on purpose
    QList<RRefPoint> ret;

    ret.append(getTextPosition());

    if (arrow1Pos.isValid()) {
        ret.append(RRefPoint(arrow1Pos, RRefPoint::Arrow));
    }
    if (arrow2Pos.isValid()) {
        ret.append(RRefPoint(arrow2Pos, RRefPoint::Arrow));
    }

    ret.append(extensionPoint1);
    ret.append(extensionPoint2);
    ret.append(refDefinitionPoint1);
    ret.append(refDefinitionPoint2);

    return ret;
}

bool RDimAlignedData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    Q_UNUSED(modifiers)

    bool ret = RDimLinearData::moveReferencePoint(referencePoint, targetPoint, modifiers);

    if (referencePoint.equalsFuzzy(refDefinitionPoint1)) {
        definitionPoint = targetPoint;
        autoTextPos = true;
        ret = true;
    }
    else if (referencePoint.equalsFuzzy(refDefinitionPoint2)) {
        definitionPoint = targetPoint;
        autoTextPos = true;
        ret = true;
    }

    if (ret) {
        update();
    }

    return ret;
}

void RDimAlignedData::recomputeDefinitionPoint(
    const RVector& oldExtPoint1, const RVector& oldExtPoint2,
    const RVector& newExtPoint1, const RVector& newExtPoint2) {

    RLine dLine(oldExtPoint1, oldExtPoint2);
    double d = dLine.getDistanceTo(definitionPoint, false);
    if (!RMath::isSane(d)) {
        definitionPoint = RVector::nullVector;
        return;
    }
    RS::Side s = dLine.getSideOfPoint(definitionPoint);

    double a = newExtPoint1.getAngleTo(newExtPoint2);
    if (s==RS::LeftHand) {
        a+=M_PI/2.0;
    }
    else {
        a-=M_PI/2.0;
    }
    RVector v = RVector::createPolar(d, a);
    RVector dp = newExtPoint1 + v;
    if (dp.isValid()) {
        definitionPoint = dp;
    }
}

QList<QSharedPointer<RShape> > RDimAlignedData::getShapes(const RBox& queryBox, bool ignoreComplex, bool segment) const {
    Q_UNUSED(queryBox)
    Q_UNUSED(ignoreComplex)
    Q_UNUSED(segment)

    QSharedPointer<RBlockReferenceEntity> dimBlockReference = getDimensionBlockReference();
    if (!dimBlockReference.isNull()) {
        return dimBlockReference->getShapes(queryBox, ignoreComplex);
    }

    QList<QSharedPointer<RShape> > ret;

    double dimexo = getDimexo();
    double dimexe = getDimexe();

    RLine extensionLine(extensionPoint1, extensionPoint2);

    // angle from extension endpoints towards dimension line
    double extAngle = extensionPoint1.getAngleTo(extensionPoint2);

    RS::Side side = extensionLine.getSideOfPoint(definitionPoint);
    if (side==RS::RightHand) {
        extAngle -= M_PI/2.0;
    }
    else {
        extAngle += M_PI/2.0;
    }

    // extension lines length
    double extLength = extensionLine.getDistanceTo(definitionPoint, false);

    RVector v1, v2, e1;

    // from entity to inner point of extension line:
    v1.setPolar(dimexo, extAngle);
    // from entity to outer point of extension line:
    v2.setPolar(dimexe, extAngle);
    e1.setPolar(1.0, extAngle);

    refDefinitionPoint1 = extensionPoint1 + e1*extLength;
    refDefinitionPoint2 = extensionPoint2 + e1*extLength;
    if (refDefinitionPoint1.isSane()) {
        definitionPoint = refDefinitionPoint1;
    }
    else {
        definitionPoint = RVector::nullVector;
    }

    // extension line 1:
    RLine extLine1 = RLine(extensionPoint1 + v1, extensionPoint1 + e1*extLength + v2);
    // extension line 2:
    RLine extLine2 = RLine(extensionPoint2 + v1, extensionPoint2 + e1*extLength + v2);

    adjustExtensionLineFixLength(extLine1, extLine2);

    ret.append(QSharedPointer<RLine>(new RLine(extLine1)));
    ret.append(QSharedPointer<RLine>(new RLine(extLine2)));

    // dimension line:
    ret.append(getDimensionLineShapes(
                   extensionPoint1 + e1*extLength,
                   extensionPoint2 + e1*extLength,
                   true, true));

    return ret;
}

double RDimAlignedData::getMeasuredValue() const {
    return extensionPoint1.getDistanceTo(extensionPoint2);
}

QString RDimAlignedData::getAutoLabel() const {
    double distance = getMeasuredValue();
    distance *= linearFactor;
    return formatLabel(distance);
}

double RDimAlignedData::getAngle() const {
    return extensionPoint1.getAngleTo(extensionPoint2);
}
