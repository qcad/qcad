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
#include "RDimLinearData.h"
#include "RUnit.h"

RDimLinearData::RDimLinearData(RDocument* document) :
    RDimensionData(document) {
}

RDimLinearData::RDimLinearData(RDocument* document, const RDimLinearData& data)
    : RDimensionData(document) {
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
RDimLinearData::RDimLinearData(const RDimensionData& dimData,
                                 const RVector& extensionPoint1,
                                 const RVector& extensionPoint2)
    : RDimensionData(dimData),
      extensionPoint1(extensionPoint1),
      extensionPoint2(extensionPoint2) {

}

bool RDimLinearData::isValid() const {
    return RDimensionData::isValid() &&
            extensionPoint1.isValid() &&
            extensionPoint2.isValid();
}

bool RDimLinearData::isSane() const {
    return RDimensionData::isSane() &&
            extensionPoint1.isSane() &&
            extensionPoint2.isSane();
}

bool RDimLinearData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    bool recomputeDefPoint = false;
    if (referencePoint.equalsFuzzy(definitionPoint)) {
        recomputeDefPoint = true;
    }

    bool ret = RDimensionData::moveReferencePoint(referencePoint, targetPoint, modifiers);

    if (referencePoint.equalsFuzzy(extensionPoint1)) {
        recomputeDefinitionPoint(extensionPoint1, extensionPoint2,
                                 targetPoint, extensionPoint2);
        extensionPoint1 = targetPoint;
        autoTextPos = true;
        update();
        return true;
    }
    else if (referencePoint.equalsFuzzy(extensionPoint2)) {
        recomputeDefinitionPoint(extensionPoint1, extensionPoint2,
                                 extensionPoint1, targetPoint);
        extensionPoint2 = targetPoint;
        autoTextPos = true;
        update();
        return true;
    }
    else if (recomputeDefPoint) {
        recomputeDefinitionPoint(extensionPoint1, extensionPoint2,
                                 extensionPoint1, extensionPoint2);
    }

    if (ret) {
        update();
    }

    return ret;
}

bool RDimLinearData::move(const RVector& offset) {
    RDimensionData::move(offset);
    extensionPoint1.move(offset);
    extensionPoint2.move(offset);
    update();
    return true;
}

bool RDimLinearData::rotate(double rotation, const RVector& center) {
    RDimensionData::rotate(rotation, center);
    extensionPoint1.rotate(rotation, center);
    extensionPoint2.rotate(rotation, center);
    update();
    return true;
}

bool RDimLinearData::scale(const RVector& scaleFactors, const RVector& center) {
    RDimensionData::scale(scaleFactors, center);
    extensionPoint1.scale(scaleFactors, center);
    extensionPoint2.scale(scaleFactors, center);
    update();
    return true;
}

bool RDimLinearData::mirror(const RLine& axis) {
    RDimensionData::mirror(axis);
    extensionPoint1.mirror(axis);
    extensionPoint2.mirror(axis);
    update();
    return true;
}

bool RDimLinearData::stretch(const RPolyline& area, const RVector& offset) {
    RDimensionData::stretch(area, offset);
    extensionPoint1.stretch(area, offset);
    extensionPoint2.stretch(area, offset);
    definitionPoint.stretch(area, offset);
    update();
    return true;
}

void RDimLinearData::updateTextData() const {
    initTextData();

    double dimgap = getDimgap();

    if (RMath::isNaN(defaultAngle)) {
        // updates default angle:
        getShapes();
    }

    // move text to the side if appropriate:
    if (!hasCustomTextPosition()) {
//        RVector newTextPos = dimensionLine.getMiddlePoint();
//        RVector distV;

//        // rotate text so it's readable from the bottom or right (ISO)
//        // quadrant 1 & 4
//        if (corrected) {
//            distV.setPolar(dimgap + dimtxt/2.0, dimAngle1-M_PI/2.0);
//        } else {
//            distV.setPolar(dimgap + dimtxt/2.0, dimAngle1+M_PI/2.0);
//        }

//        // move text away from dimension line:
//        newTextPos+=distV;

//        // TODO: resets textPosition if text was moved to the side for lack of space:
//        textPosition = newTextPos;
//        qDebug() << "RDimensionData::getDimensionLineShapes(): 1: textPosition: " << textPosition;
//        //updateTextData();
//        qDebug() << "RDimensionData::getDimensionLineShapes(): 2: textPosition: " << textPosition;


        if (!RMath::isNaN(dimLineLength) && textData.getWidth()>dimLineLength) {
            RVector distH;
            distH.setPolar(textData.getWidth()/2.0+dimLineLength/2.0+dimgap, defaultAngle);
            textPositionSide = textPositionCenter;
            textPositionSide+=distH;
            //qDebug() << "RDimLinearData::updateTextData(): textPosition (side): " << textPositionCenter;
        }
        else {
            textPositionSide = RVector::invalid;
        }
    }

    textData.rotate(defaultAngle, RVector(0,0));
    textData.move(getTextPosition());
}
