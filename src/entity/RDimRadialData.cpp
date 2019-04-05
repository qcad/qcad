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
#include "RDimRadialData.h"
#include "RUnit.h"

RDimRadialData::RDimRadialData() {
}

RDimRadialData::RDimRadialData(RDocument* document, const RDimRadialData& data)
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
RDimRadialData::RDimRadialData(const RDimensionData& dimData,
                                 const RVector& definitionPoint2)
    : RDimensionData(dimData),
      chordPoint(definitionPoint2) {

}

bool RDimRadialData::isValid() const {
    return RDimensionData::isValid() &&
            chordPoint.isValid();
}

bool RDimRadialData::isSane() const {
    return RDimensionData::isSane() &&
            chordPoint.isSane();
}

QList<RRefPoint> RDimRadialData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    QList<RRefPoint> ret = RDimensionData::getReferencePoints(hint);

    ret.append(textPositionCenter);

    if (arrow1Pos.isValid()) {
        ret.append(RRefPoint(arrow1Pos, RRefPoint::Arrow));
    }

    ret.append(chordPoint);

    return ret;
}

bool RDimRadialData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    bool ret = false;

    if (referencePoint.equalsFuzzy(chordPoint)) {
        double d = definitionPoint.getDistanceTo(chordPoint);
        double a = definitionPoint.getAngleTo(targetPoint);

        RVector v;
        v.setPolar(d, a);
        chordPoint = definitionPoint + v;

        autoTextPos = true;
        ret = true;
    }
//    else if (referencePoint.getDistanceTo(definitionPoint) < RS::PointTolerance) {
//        RVector c = (definitionPoint + chordPoint)/2.0;
//        double d = c.getDistanceTo(definitionPoint);
//        double a = c.getAngleTo(targetPoint);

//        RVector v = RVector::createPolar(d, a);
//        definitionPoint = c + v;
//        chordPoint = c - v;

//        autoTextPos = true;
//        ret = true;
//    }

    if (!ret) {
        ret = RDimensionData::moveReferencePoint(referencePoint, targetPoint, modifiers);
    }

    if (ret) {
        update();
    }

    return ret;
}

bool RDimRadialData::move(const RVector& offset) {
    RDimensionData::move(offset);
    chordPoint.move(offset);
    update();
    return true;
}

bool RDimRadialData::rotate(double rotation, const RVector& center) {
    RDimensionData::rotate(rotation, center);
    chordPoint.rotate(rotation, center);
    update();
    return true;
}

bool RDimRadialData::scale(const RVector& scaleFactors, const RVector& center) {
    RDimensionData::scale(scaleFactors, center);
    chordPoint.scale(scaleFactors, center);
    update();
    return true;
}

bool RDimRadialData::mirror(const RLine& axis) {
    RDimensionData::mirror(axis);
    chordPoint.mirror(axis);
    update();
    return true;
}

QList<QSharedPointer<RShape> > RDimRadialData::getShapes(const RBox& queryBox, bool ignoreComplex, bool segment) const {
    Q_UNUSED(queryBox)
    Q_UNUSED(ignoreComplex)
    Q_UNUSED(segment)

    QSharedPointer<RBlockReferenceEntity> dimBlockReference = getDimensionBlockReference();
    if (!dimBlockReference.isNull()) {
        return dimBlockReference->getShapes(queryBox, ignoreComplex);
    }

    QList<QSharedPointer<RShape> > ret;

    defaultAngle = 0.0;

    double angle = definitionPoint.getAngleTo(chordPoint);

    // text distance to line (DIMGAP)
    double dimgap = getDimgap();
    double dimtxt = getDimtxt();
    double dimasz = getDimasz();
    bool archTick = useArchTick();

    // length of dimension line:
    double length = definitionPoint.getDistanceTo(chordPoint);

    RVector oldMot = textPositionCenter;
    textPositionCenter = RVector(0,0);
    //dimLineLength = RNANDOUBLE;
    getTextData();
    textPositionCenter = oldMot;

    double textWidth = textData.getWidth();

    // do we have to put the arrow / text outside of the arc?
    bool outsideArrow = (length < dimasz*2+textWidth);
    bool outsideLabel = outsideArrow;

    // force flipping arrows (against logic above):
    if (isArrow1Flipped()) {
        outsideArrow = !outsideArrow;
        outsideLabel = outsideArrow;
    }

    double arrowAngle;
    if (outsideArrow) {
        if (outsideLabel) {
            length += dimasz*2 + textWidth;
        }
        else {
            length += dimasz*2;
        }
        arrowAngle = angle+M_PI;
    } else {
        if (outsideLabel) {
            length += dimasz*2 + textWidth;
        }
        arrowAngle = angle;
    }

    RVector v3 = RVector::createPolar(length, angle);
    v3+=definitionPoint;

    // dimension line:
    ret.append(QSharedPointer<RShape>(new RLine(definitionPoint, v3)));

    // create arrow:
    ret.append(getArrow(chordPoint, arrowAngle));

    if (!archTick) {
        arrow1Pos = chordPoint + RVector::createPolar(dimasz, arrowAngle + M_PI);
    }

    RVector distV;
    double textAngle;

    // rotate text so it's readable from the bottom or right (ISO)
    // quadrant 1 & 4
    if (angle > M_PI/2.0*3.0+RS::AngleTolerance ||
        angle < M_PI/2.0+RS::AngleTolerance) {

        distV.setPolar(dimgap + dimtxt/2.0, angle+M_PI/2.0);
        textAngle = angle;
    }
    // quadrant 2 & 3
    else {
        distV.setPolar(dimgap + dimtxt/2.0, angle-M_PI/2.0);
        textAngle = angle+M_PI;
    }

    RVector textPos;
    if (!autoTextPos) {
        textPos = textPositionCenter;
    } else {
        if (outsideLabel) {
            if (outsideArrow) {
                textPos.setPolar(length-textWidth/2.0-dimasz, angle);
            }
            else {
                textPos.setPolar(length-textWidth/2.0-dimasz, angle);
            }
        }
        else {
            if (outsideArrow) {
                textPos.setPolar((length-dimasz*2)/2.0, angle);
            }
            else {
                textPos.setPolar(length/2.0, angle);
            }
        }
        textPos += definitionPoint;
        // move text away from dimension line:
        textPos += distV;
        textPositionCenter = textPos;
    }
    defaultAngle = textAngle;
    textData.rotate(textAngle, RVector(0,0));
    textData.move(textPos);

    return ret;
}

double RDimRadialData::getMeasuredValue() const {
    return definitionPoint.getDistanceTo(chordPoint);
}

QString RDimRadialData::getAutoLabel() const {
    double distance = getMeasuredValue();
    distance *= linearFactor;
    return formatLabel(distance);
}
