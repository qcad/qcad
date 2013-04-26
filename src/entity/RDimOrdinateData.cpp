/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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
#include "RDimOrdinateData.h"
#include "RUnit.h"

RDimOrdinateData::RDimOrdinateData() {
}

RDimOrdinateData::RDimOrdinateData(RDocument* document, const RDimOrdinateData& data)
    : RDimensionData(document) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

/**
 * \param leaderEndPoint End point of leader (where the label is).
 * \param definingPoint The point where the ordinate is measured.
 */
RDimOrdinateData::RDimOrdinateData(const RDimensionData& dimData,
                                 const RVector& leaderEndPoint,
                                 const RVector& definingPoint)
    : RDimensionData(dimData),
      definingPoint(definingPoint),
      leaderEndPoint(leaderEndPoint) {

}

bool RDimOrdinateData::isValid() const {
    return RDimensionData::isValid() &&
            leaderEndPoint.isValid() &&
            definingPoint.isValid();
}

QList<RVector> RDimOrdinateData::getReferencePoints(
    RS::ProjectionRenderingHint hint) const {

    Q_UNUSED(hint)

    QList<RVector> ret = RDimensionData::getReferencePoints(hint);

    ret.append(leaderEndPoint);
    ret.append(definingPoint);

    return ret;
}

bool RDimOrdinateData::moveReferencePoint(const RVector& referencePoint,
        const RVector& targetPoint) {

    bool ret = RDimensionData::moveReferencePoint(referencePoint, targetPoint);

    if (referencePoint.equalsFuzzy(leaderEndPoint)) {
        leaderEndPoint = targetPoint;
        autoTextPos = true;
        ret = true;
    }
    else if (referencePoint.equalsFuzzy(definingPoint)) {
        definingPoint = targetPoint;
        autoTextPos = true;
        ret = true;
    }

    if (ret) {
        update();
    }

    return ret;
}


bool RDimOrdinateData::move(const RVector& offset) {
    RDimensionData::move(offset);
    leaderEndPoint.move(offset);
    definingPoint.move(offset);
    update();
    return true;
}

bool RDimOrdinateData::rotate(double rotation, const RVector& center) {
    RDimensionData::rotate(rotation, center);
    leaderEndPoint.rotate(rotation, center);
    definingPoint.rotate(rotation, center);
    update();
    return true;
}

bool RDimOrdinateData::scale(const RVector& scaleFactors, const RVector& center) {
    RDimensionData::scale(scaleFactors, center);
    leaderEndPoint.scale(scaleFactors, center);
    definingPoint.scale(scaleFactors, center);
    update();
    return true;
}

bool RDimOrdinateData::mirror(const RLine& axis) {
    RDimensionData::mirror(axis);
    leaderEndPoint.mirror(axis);
    definingPoint.mirror(axis);
    update();
    return true;
}

bool RDimOrdinateData::stretch(const RPolyline& area, const RVector& offset) {
    RDimensionData::stretch(area, offset);
    leaderEndPoint.stretch(area, offset);
    definingPoint.stretch(area, offset);
    update();
    return true;
}

QList<QSharedPointer<RShape> > RDimOrdinateData::getShapes(const RBox& queryBox) const {
    Q_UNUSED(queryBox)

    QList<QSharedPointer<RShape> > ret;

    // make sure that defaultAngle is valid, even if not used:
    defaultAngle = 0.0;

    // distance from entities (DIMEXO)
    double dimexo = getDimexo();

    RVector knee1;
    RVector knee2;
    RVector textOffsetV;   // normal vector in direction of text offset

    // vertical, measuring X
    if (isMeasuringXAxis()) {
        knee1.x = definingPoint.x;
        knee2.x = leaderEndPoint.x;

        if (definingPoint.y < leaderEndPoint.y) {
            knee1.y = leaderEndPoint.y - 0.36*2;
            if (knee1.y < definingPoint.y + 0.36) {
                knee1.y = definingPoint.y + 0.36;
            }

            knee2.y = leaderEndPoint.y - 0.36;
            textOffsetV = RVector(0,1);
        }
        else {
            knee1.y = leaderEndPoint.y + 0.36*2;
            if (knee1.y > definingPoint.y - 0.36) {
                knee1.y = definingPoint.y - 0.36;
            }

            knee2.y = leaderEndPoint.y + 0.36;
            textOffsetV = RVector(0,-1);
        }
    }

    // horizontal, measuring Y
    else {
        knee1.y = definingPoint.y;
        knee2.y = leaderEndPoint.y;

        if (definingPoint.x < leaderEndPoint.x) {
            knee1.x = leaderEndPoint.x - 0.36*2;
            if (knee1.x < definingPoint.x + 0.36) {
                knee1.x = definingPoint.x + 0.36;
            }

            knee2.x = leaderEndPoint.x - 0.36;
            textOffsetV = RVector(1,0);
        }
        else {
            knee1.x = leaderEndPoint.x + 0.36*2;
            if (knee1.x > definingPoint.x - 0.36) {
                knee1.x = definingPoint.x - 0.36;
            }

            knee2.x = leaderEndPoint.x + 0.36;
            textOffsetV = RVector(-1,0);
        }
    }

    RLine line;

    if (definingPoint.getDistanceTo(knee1) > dimexo) {
        line = RLine(definingPoint + textOffsetV*dimexo, knee1);
        ret.append(QSharedPointer<RLine>(new RLine(line)));
    }

    line = RLine(knee1, knee2);
    ret.append(QSharedPointer<RLine>(new RLine(line)));

    line = RLine(knee2, leaderEndPoint);
    ret.append(QSharedPointer<RLine>(new RLine(line)));

    double textHeight = getDimtxt();
    double dimgap = getDimgap();

    dimLineLength = RNANDOUBLE;
    //if (!middleOfText.isValid()) {
    //    middleOfText = RVector(0,0);
    //}
    RVector oldMot = textPositionCenter;
    textPositionCenter = RVector(0,0);
    getTextData();
    textPositionCenter = oldMot;

    //textData.getBoundingBox();

    RVector textPos;
    //if (textPosition.isValid() /*&& !autoText*/) {
    if (!autoTextPos) {
        textPos = textPositionCenter;
        //autoTextPos = false;
    } else {
        if (!isMeasuringXAxis()) {
            double labelWidth = textData.getWidth();
            textPos = leaderEndPoint + textOffsetV * (labelWidth/2.0+dimgap);
        }
        else {
            textPos = leaderEndPoint + textOffsetV * (textHeight/2.0+dimgap);
        }
        textPositionCenter = textPos;
        //middleOfText = RVector::invalid;
        //autoTextPos = true;
    }
    textData.move(textPos);

    return ret;
}

QString RDimOrdinateData::getAutoMeasurement() const {
    double distance;

    if (isMeasuringXAxis()) {
        distance = qAbs(definingPoint.x-definitionPoint.x);
    }
    else {
        distance = qAbs(definingPoint.y-definitionPoint.y);
    }

    return formatLabel(distance);
}
