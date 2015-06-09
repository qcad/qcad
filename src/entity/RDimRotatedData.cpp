/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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
#include "RDimRotatedData.h"
#include "RUnit.h"

RDimRotatedData::RDimRotatedData() : rotation(0.0) {
}

RDimRotatedData::RDimRotatedData(RDocument* document, const RDimRotatedData& data)
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
RDimRotatedData::RDimRotatedData(const RDimensionData& dimData,
                               const RVector& extensionPoint1,
                               const RVector& extensionPoint2,
                               double rotation)
    : RDimLinearData(dimData, extensionPoint1, extensionPoint2),
      rotation(rotation) {

}

RBox RDimRotatedData::getBoundingBox(bool ignoreEmpty) const {
    boundingBox = RDimensionData::getBoundingBox(ignoreEmpty);
    boundingBox.growToInclude(extensionPoint1);
    boundingBox.growToInclude(extensionPoint2);
    return boundingBox;
}

bool RDimRotatedData::isValid() const {
    return RDimLinearData::isValid() && RMath::isNormal(rotation);
}

QList<RVector> RDimRotatedData::getReferencePoints(
    RS::ProjectionRenderingHint hint) const {

    QList<RVector> ret = RDimLinearData::getReferencePoints(hint);

    ret.append(extensionPoint1);
    ret.append(extensionPoint2);

    return ret;
}

void RDimRotatedData::recomputeDefinitionPoint(
    const RVector& oldExtPoint1, const RVector& oldExtPoint2,
    const RVector& newExtPoint1, const RVector& newExtPoint2) {

    Q_UNUSED(oldExtPoint1)
    Q_UNUSED(oldExtPoint2)
    Q_UNUSED(newExtPoint2)

    RVector dirDim = RVector::createPolar(1.0, rotation);

    // construction line for dimension line
    RLine dimLine(definitionPoint, definitionPoint + dirDim);

    RVector dimP1 = dimLine.getClosestPointOnShape(newExtPoint1, false);
    //RVector dimP2 = dimLine.getClosestPointOnShape(extensionPoint2, false);

    if (dimP1.isValid()) {
        definitionPoint = dimP1;
    }
}

bool RDimRotatedData::rotate(double rotation, const RVector& center) {
    RDimLinearData::rotate(rotation, center);
    //extensionPoint1.rotate(rotation, center);
    //extensionPoint2.rotate(rotation, center);
    this->rotation = RMath::getNormalizedAngle(this->rotation+rotation);
    update();
    return true;
}

bool RDimRotatedData::mirror(const RLine& axis) {
    RDimLinearData::mirror(axis);
    //extensionPoint1.mirror(axis);
    //extensionPoint2.mirror(axis);

    RLine neutralAxis = axis;
    neutralAxis.move(-neutralAxis.getStartPoint());
    RVector vec = RVector::createPolar(1.0, rotation);
    vec.mirror(neutralAxis);
    rotation = vec.getAngle();

    update();
    return true;
}

QList<QSharedPointer<RShape> > RDimRotatedData::getShapes(const RBox& queryBox, bool ignoreComplex) const {
    Q_UNUSED(queryBox)

    QList<QSharedPointer<RShape> > ret;

    double dimexo = getDimexo();
    double dimexe = getDimexe();

    double extAngle = rotation - (M_PI/2.0);

    RVector dirDim = RVector::createPolar(1.0, rotation);

    // construction line for dimension line
    RLine dimLine(definitionPoint, definitionPoint + dirDim);
    RVector dimP1 = dimLine.getClosestPointOnShape(extensionPoint1, false);
    RVector dimP2 = dimLine.getClosestPointOnShape(extensionPoint2, false);

    // definitive dimension line:
    ret += getDimensionLineShapes(dimP1, dimP2, true, true);

    // extension lines:
    RVector vDimexo1, vDimexe1, vDimexo2, vDimexe2;
    if (!extensionPoint1.equalsFuzzy(dimP1)) {
        double a1 = extensionPoint1.getAngleTo(dimP1);
        vDimexe1.setPolar(dimexe, a1);
        vDimexo1.setPolar(dimexo, a1);

        RLine line(extensionPoint1+vDimexo1, dimP1+vDimexe1);
        ret.append(QSharedPointer<RLine>(new RLine(line)));
    }

    if (!extensionPoint2.equalsFuzzy(dimP2)) {
        double a2 = extensionPoint2.getAngleTo(dimP2);
        vDimexe2.setPolar(dimexe, a2);
        vDimexo2.setPolar(dimexo, a2);

        RLine line(extensionPoint2+vDimexo2, dimP2+vDimexe2);
        ret.append(QSharedPointer<RLine>(new RLine(line)));
    }

    return ret;
}

double RDimRotatedData::getMeasuredValue() const {
    // direction of dimension line
    RVector dirDim;
    dirDim.setPolar(1.0, rotation);

    RLine dimLine(definitionPoint, definitionPoint + dirDim);

    RVector dimP1 = dimLine.getClosestPointOnShape(extensionPoint1, false);
    RVector dimP2 = dimLine.getClosestPointOnShape(extensionPoint2, false);

    // Definitive dimension line:
    return dimP1.getDistanceTo(dimP2);
}

QString RDimRotatedData::getAutoLabel() const {
    double distance = getMeasuredValue();
    distance *= linearFactor;

    return formatLabel(distance);
}
