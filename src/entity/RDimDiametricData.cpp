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
#include "RDimDiametricData.h"
#include "RUnit.h"

RDimDiametricData::RDimDiametricData() {
}

RDimDiametricData::RDimDiametricData(RDocument* document, const RDimDiametricData& data)
    : RDimensionData(document) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

/**
 * \param definitionPoint2 Definition point. Startpoint of the
 *         first extension line.
 */
RDimDiametricData::RDimDiametricData(const RDimensionData& dimData,
                                 const RVector& choordPoint)
    : RDimensionData(dimData),
      chordPoint(choordPoint) {

}

bool RDimDiametricData::isValid() const {
    return RDimensionData::isValid() &&
            chordPoint.isValid();
}

bool RDimDiametricData::isSane() const {
    return RDimensionData::isSane() &&
            chordPoint.isSane();
}

QList<RRefPoint> RDimDiametricData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    QList<RRefPoint> ret = RDimensionData::getReferencePoints(hint);

    ret.append(getTextPosition());
    ret.append(chordPoint);

    return ret;
}

bool RDimDiametricData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    Q_UNUSED(modifiers)

    bool ret = false;

    if (referencePoint.equalsFuzzy(chordPoint)) {
        RVector c = (definitionPoint + chordPoint)/2.0;
        double d = c.getDistanceTo(chordPoint);
        double a = c.getAngleTo(targetPoint);

        RVector v = RVector::createPolar(d, a);
        chordPoint = c + v;
        definitionPoint = c - v;

        autoTextPos = true;
        ret = true;
    }
    else if (referencePoint.equalsFuzzy(definitionPoint)) {
        RVector c = (definitionPoint + chordPoint)/2.0;
        double d = c.getDistanceTo(definitionPoint);
        double a = c.getAngleTo(targetPoint);

        RVector v = RVector::createPolar(d, a);
        definitionPoint = c + v;
        chordPoint = c - v;

        autoTextPos = true;
        ret = true;
    }

    if (!ret) {
        ret = RDimensionData::moveReferencePoint(referencePoint, targetPoint, modifiers);
    }

    if (ret) {
        update();
    }

    return ret;
}

bool RDimDiametricData::move(const RVector& offset) {
    RDimensionData::move(offset);
    chordPoint.move(offset);
    update();
    return true;
}

bool RDimDiametricData::rotate(double rotation, const RVector& center) {
    RDimensionData::rotate(rotation, center);
    chordPoint.rotate(rotation, center);
    update();
    return true;
}

bool RDimDiametricData::scale(const RVector& scaleFactors, const RVector& center) {
    RDimensionData::scale(scaleFactors, center);
    chordPoint.scale(scaleFactors, center);
    update();
    return true;
}

bool RDimDiametricData::mirror(const RLine& axis) {
    RDimensionData::mirror(axis);
    chordPoint.mirror(axis);
    update();
    return true;
}

QList<QSharedPointer<RShape> > RDimDiametricData::getShapes(const RBox& queryBox, bool ignoreComplex, bool segment) const {
    Q_UNUSED(queryBox)
    Q_UNUSED(ignoreComplex)
    Q_UNUSED(segment)

    QSharedPointer<RBlockReferenceEntity> dimBlockReference = getDimensionBlockReference();
    if (!dimBlockReference.isNull()) {
        return dimBlockReference->getShapes(queryBox, ignoreComplex);
    }

    QList<QSharedPointer<RShape> > ret;

    // dimension line:
    ret.append(getDimensionLineShapes(
                   chordPoint,
                   definitionPoint,
                   true, true));

    return ret;
}

double RDimDiametricData::getMeasuredValue() const {
    return definitionPoint.getDistanceTo(chordPoint);
}

QString RDimDiametricData::getAutoLabel() const {
    double distance = getMeasuredValue();
    distance *= linearFactor;
    return formatLabel(distance);
}

void RDimDiametricData::updateTextData() const {
    initTextData();

    double dimgap = getDimgap();

    if (RMath::isNaN(defaultAngle)) {
        // updates default angle:
        getShapes();
    }

    // move text to the side if appropriate:
    if (!hasCustomTextPosition()) {
        //RBox bbox = textData.getBoundingBox();
        if (!RMath::isNaN(dimLineLength) && textData.getWidth()>dimLineLength) {
            RVector distH;
            distH.setPolar(textData.getWidth()/2.0
                           +dimLineLength/2.0+dimgap, defaultAngle);
            textPositionSide = textPositionCenter;
            textPositionSide+=distH;
        }
        else {
            textPositionSide = RVector::invalid;
        }
    }

    textData.rotate(defaultAngle, RVector(0,0));
    textData.move(getTextPosition());
}
