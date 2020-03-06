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

    // 20200306: this breaks area selection of dimensions
    // if extension points are far away from dimension shapes:
    //if (!hasDimensionBlockReference()) {
    //    boundingBox.growToInclude(extensionPoint1);
    //    boundingBox.growToInclude(extensionPoint2);
    //}

    return boundingBox;
}

bool RDimRotatedData::isValid() const {
    return RDimLinearData::isValid() && RMath::isNormal(rotation);
}

bool RDimRotatedData::isSane() const {
    return RDimLinearData::isSane() && RMath::isSane(rotation);
}

QList<RRefPoint> RDimRotatedData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    QList<RRefPoint> ret = RDimLinearData::getReferencePoints(hint);

    ret.append(extensionPoint1);
    ret.append(extensionPoint2);

    return ret;
}

bool RDimRotatedData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    // if definition point and extension points are on one line,
    // move the extension points together with the definition point:
    bool moveExtensionPoints = false;
    if (referencePoint.equalsFuzzy(definitionPoint)) {
        if (RLine(extensionPoint1, extensionPoint2).isOnShape(definitionPoint, false)) {
            moveExtensionPoints = true;
        }
    }

    bool ret = RDimLinearData::moveReferencePoint(referencePoint, targetPoint, modifiers);

    if (moveExtensionPoints) {
        // move extension points with definition point:
        RVector dir = RVector::createPolar(1.0, rotation);
        RLine dimLine = RLine(targetPoint, targetPoint + dir);
        extensionPoint1 = dimLine.getClosestPointOnShape(extensionPoint1, false);
        extensionPoint2 = dimLine.getClosestPointOnShape(extensionPoint2, false);
        definitionPoint = RVector::getAverage(extensionPoint1, extensionPoint2);
        //recomputeDefinitionPoint(referencePoint, targetPoint);
    }

    return ret;
}

QList<RVector> RDimRotatedData::getDimPoints() const {
    QList<RVector> ret;

    RVector dirDim = RVector::createPolar(1.0, rotation);

    // construction line for dimension line
    RLine dimLine(definitionPoint, definitionPoint + dirDim);
    ret.append(dimLine.getClosestPointOnShape(extensionPoint1, false));
    ret.append(dimLine.getClosestPointOnShape(extensionPoint2, false));

    return ret;
}

/**
 * Recompute definition point if extension point(s) have changed.
 */
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
    RVector dimP2 = dimLine.getClosestPointOnShape(newExtPoint2, false);

    // make sure the dimension line is movable if dimension point == extension point
    if (dimP1.equalsFuzzy(newExtPoint1) || dimP1.equalsFuzzy(newExtPoint2)) {
        dimP1 = RVector::getAverage(dimP1, dimP2);
    }

    if (dimP1.isValid()) {
        definitionPoint = dimP1;
    }
}

/**
 * Recompute definition point if
 */
//void RDimRotatedData::recomputeDefinitionPoint(const RVector& oldDimLineGrip, const RVector& newDimLineGrip) {
//    Q_UNUSED(oldDimLineGrip)

//    RVector extDir = RVector::createPolar(1.0, rotation);

//    // construction line for dimension line
//    RLine extLine1(extensionPoint1, extensionPoint1 + extDir);

//    RVector dimP1 = extLine1.getClosestPointOnShape(newDimLineGrip, false);

//    if (dimP1.isValid()) {
//        definitionPoint = dimP1;
//    }
//}

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

QList<QSharedPointer<RShape> > RDimRotatedData::getShapes(const RBox& queryBox, bool ignoreComplex, bool segment) const {
    Q_UNUSED(queryBox)
    Q_UNUSED(ignoreComplex)
    Q_UNUSED(segment)

    QSharedPointer<RBlockReferenceEntity> dimBlockReference = getDimensionBlockReference();
    if (!dimBlockReference.isNull()) {
//        QList<QSharedPointer<RShape> > sps = dimBlockReference->getShapes(queryBox, ignoreComplex);
//        for (int i=0; i<sps.length(); i++) {
//            qDebug() << "getShapes: from block ref" << *sps.at(i);
//        }
        return dimBlockReference->getShapes(queryBox, ignoreComplex);
    }

    QList<QSharedPointer<RShape> > ret;

    double dimexo = getDimexo();
    double dimexe = getDimexe();

    QList<RVector> l = getDimPoints();
    RVector dimP1 = l.at(0);
    RVector dimP2 = l.at(1);

    // definitive dimension line:
    ret += getDimensionLineShapes(dimP1, dimP2, true, true);

    RLine extLine1, extLine2;

    // extension lines:
    RVector vDimexo1, vDimexe1, vDimexo2, vDimexe2;
    if (!extensionPoint1.equalsFuzzy(dimP1)) {
        double a1 = extensionPoint1.getAngleTo(dimP1);
        vDimexe1.setPolar(dimexe, a1);
        vDimexo1.setPolar(dimexo, a1);

        extLine1 = RLine(extensionPoint1+vDimexo1, dimP1+vDimexe1);
    }

    if (!extensionPoint2.equalsFuzzy(dimP2)) {
        double a2 = extensionPoint2.getAngleTo(dimP2);
        vDimexe2.setPolar(dimexe, a2);
        vDimexo2.setPolar(dimexo, a2);

        extLine2 = RLine(extensionPoint2+vDimexo2, dimP2+vDimexe2);
    }

    adjustExtensionLineFixLength(extLine1, extLine2);

    if (extLine1.isValid()) {
        ret.append(QSharedPointer<RLine>(new RLine(extLine1)));
    }
    if (extLine2.isValid()) {
        ret.append(QSharedPointer<RLine>(new RLine(extLine2)));
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
