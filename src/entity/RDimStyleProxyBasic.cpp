/**
 * Copyright (c) 2011-2021 by Andrew Mustun. All rights reserved.
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

#include <QDebug>

#include "RCircle.h"
#include "RDimStyleProxyBasic.h"
#include "RDimensionData.h"
#include "RDimRotatedData.h"
#include "RDimAlignedData.h"
#include "RDimOrdinateData.h"
#include "RDimRadialData.h"
#include "RDimDiametricData.h"
#include "RDimAngularData.h"
#include "REntity.h"
#include "RStorage.h"
#include "RTriangle.h"

void RDimStyleProxyBasic::render(const RDimStyle& dimStyle, const REntityData& entityData, bool preview, bool forceSelected) {
    // instantiate new dim style proxy for this single rendering (thread safety):
    RDimStyleProxyBasic dimStyleProxy;
    dimStyleProxy.renderPrivate(dimStyle, entityData, preview, forceSelected);
}


void RDimStyleProxyBasic::renderPrivate(const RDimStyle& dimStyle, const REntityData& entityData, bool preview, bool forceSelected) {
    this->document = entityData.getDocument();
    this->dimStyle = &dimStyle;
    this->dimensionData = dynamic_cast<const RDimensionData*>(&entityData);
    this->preview = preview;
    this->forceSelected = forceSelected;

    //qDebug() << "rendering dim";

    if (dimensionData==NULL) {
        qWarning() << "entity is not a dimension";
        return;
    }

    switch (dimensionData->getType()) {
    case RS::EntityDimRotated:
        renderDimRotated();
        break;

    case RS::EntityDimAligned:
        renderDimAligned();
        break;

    case RS::EntityDimOrdinate:
        renderDimOrdinate();
        break;

    case RS::EntityDimRadial:
        renderDimRadial();
        break;

    case RS::EntityDimDiametric:
        renderDimDiametric();
        break;

    case RS::EntityDimAngular2L:
        renderDimAngular();
        break;

    case RS::EntityDimAngular3P:
        renderDimAngular();
        break;

    case RS::EntityDimArcLength:
        renderDimAngular();
        break;

    default:
        qWarning() << "trying to render unsupported entity";
        break;
    }
}

void RDimStyleProxyBasic::renderDimRotated() {
    const RDimRotatedData& data = *dynamic_cast<const RDimRotatedData*>(dimensionData);

    QString text = data.getText();
    QList<RVector> dimpts = data.getDimPoints();
    RVector definitionPoint1 = dimpts[0];
    RVector definitionPoint2 = dimpts[1];
    RVector extensionPoint1 = data.getExtensionPoint1();
    RVector extensionPoint2 = data.getExtensionPoint2();

    double dimexe = dimensionData->getDimexe();
    double dimexo = dimensionData->getDimexo();
    bool dimtih = dimensionData->getDimtih();

    // rotate text so it's readable from the bottom or right (ISO)
    // quadrant 1 & 4
    bool corrected=false;
    double textAngle;
    if (dimtih) {
        textAngle = 0.0;
    }
    else {
        if (definitionPoint1.equalsFuzzy(definitionPoint2)) {
            textAngle = RMath::makeAngleReadable(data.getRotation(), true, &corrected);
        }
        else {
            textAngle = RMath::makeAngleReadable(definitionPoint1.getAngleTo(definitionPoint2), true, &corrected);
        }
    }

    updateOutsideArrow(definitionPoint1, definitionPoint2);

    // export text label:
    RTextData& textData = data.initTextData();
    double textWidth = textData.getWidth();
    updateTextPosition(text, textWidth, definitionPoint1, definitionPoint2, corrected, data.getRotation());
    textData.rotate(textAngle, RVector(0,0));
    textData.move(dimensionData->getTextPosition());
    data.updateTextData(textData);

    // export lines and arrows:
    QList<QSharedPointer<RShape> > shapes = getDimensionLineShapes(definitionPoint1, definitionPoint2, true, true, data.getRotation());

    RLine extLine1, extLine2;

    // extension lines:
    RVector vDimexo1, vDimexe1, vDimexo2, vDimexe2;
    if (!extensionPoint1.equalsFuzzy(definitionPoint1)) {
        double a1 = extensionPoint1.getAngleTo(definitionPoint1);
        vDimexe1.setPolar(dimexe, a1);
        vDimexo1.setPolar(dimexo, a1);

        extLine1 = RLine(extensionPoint1+vDimexo1, definitionPoint1+vDimexe1);
    }

    if (!extensionPoint2.equalsFuzzy(definitionPoint2)) {
        double a2 = extensionPoint2.getAngleTo(definitionPoint2);
        vDimexe2.setPolar(dimexe, a2);
        vDimexo2.setPolar(dimexo, a2);

        extLine2 = RLine(extensionPoint2+vDimexo2, definitionPoint2+vDimexe2);
    }

    adjustExtensionLineFixLength(extLine1, extLine2);

    if (extLine1.isValid()) {
        shapes.append(QSharedPointer<RLine>(new RLine(extLine1)));
    }
    if (extLine2.isValid()) {
        shapes.append(QSharedPointer<RLine>(new RLine(extLine2)));
    }

    // update entity about text pos, bounding box, shapes:
    //data.updateTextData(textData);

    RBox bbox = textData.getBoundingBox(false);
    for (int i=0; i<shapes.length(); i++) {
        bbox.growToInclude(shapes[i]->getBoundingBox());
    }
    data.updateBoundingBox(bbox);
//    QList<QSharedPointer<RShape> > textShapes = textData.getShapes();
//    shapes.append(textShapes);
    data.updateShapes(shapes);


//    qDebug() << "updateShapes:";
//    for (int i=0; i<shapes.length(); i++) {
//        qDebug() << *shapes[i];
//    }
}


void RDimStyleProxyBasic::renderDimAligned() {
    const RDimAlignedData& data = *dynamic_cast<const RDimAlignedData*>(dimensionData);

    //QList<QSharedPointer<RShape> > shapes;

    double dimexo = dimensionData->getDimexo();
    double dimexe = dimensionData->getDimexe();
    bool dimtih = dimensionData->getDimtih();

    RVector definitionPoint = data.getDefinitionPoint();
    RVector extensionPoint1 = data.getExtensionPoint1();
    RVector extensionPoint2 = data.getExtensionPoint2();

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

    RVector refDefinitionPoint1 = extensionPoint1 + e1*extLength;
    RVector refDefinitionPoint2 = extensionPoint2 + e1*extLength;
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

    double rotation = data.getAngle();
    QString text = data.getText();

    // rotate text so it's readable from the bottom or right (ISO)
    // quadrant 1 & 4
    bool corrected=false;
    double textAngle;
    if (dimtih) {
        textAngle = 0.0;
    }
    else {
        textAngle = RMath::makeAngleReadable(rotation, true, &corrected);
    }

    RVector p1 = extensionPoint1 + e1*extLength;
    RVector p2 = extensionPoint2 + e1*extLength;

    updateOutsideArrow(p1, p2);

    // export text label:
    RTextData& textData = data.initTextData();
    double textWidth = textData.getWidth();
    updateTextPosition(text, textWidth, extensionPoint1 + e1*extLength, extensionPoint2 + e1*extLength, corrected);
    textData.rotate(textAngle, RVector(0,0));
    textData.move(data.getTextPosition());
    data.updateTextData(textData);

    QList<QSharedPointer<RShape> > shapes;
    shapes.append(QSharedPointer<RLine>(new RLine(extLine1)));
    shapes.append(QSharedPointer<RLine>(new RLine(extLine2)));
    shapes.append(getDimensionLineShapes(p1, p2, true, true));

    data.updateRefDefinitionPoint1(refDefinitionPoint1);
    data.updateRefDefinitionPoint2(refDefinitionPoint2);

    // update entity about text pos, bounding box, shapes:
    //data.updateTextData(textData);
    //data.updateTextPositionCenter(textPositionCenter);

    RBox bbox = textData.getBoundingBox(false);
    for (int i=0; i<shapes.length(); i++) {
        bbox.growToInclude(shapes[i]->getBoundingBox());
    }
    data.updateBoundingBox(bbox);
//    QList<QSharedPointer<RShape> > textShapes = textData.getShapes();
//    shapes.append(textShapes);
    data.updateShapes(shapes);

    //return shapes;
}

void RDimStyleProxyBasic::renderDimOrdinate() {
    const RDimOrdinateData& data = *dynamic_cast<const RDimOrdinateData*>(dimensionData);

    QList<QSharedPointer<RShape> > shapes;

    // make sure that defaultAngle is valid, even if not used:
    //double defaultAngle = 0.0;

    // distance from entities (DIMEXO)
    double dimexo = dimensionData->getDimexo();

    RVector knee1;
    RVector knee2;
    RVector textOffsetV;   // normal vector in direction of text offset
    double legSize = dimensionData->getDimasz()*2;
    RVector definingPoint = data.getDefiningPoint();
    RVector leaderEndPoint = data.getLeaderEndPoint();

    // vertical, measuring X
    if (data.isMeasuringXAxis()) {
        knee1.x = definingPoint.x;
        knee2.x = leaderEndPoint.x;

        if (definingPoint.y < leaderEndPoint.y) {
            knee1.y = leaderEndPoint.y - legSize*2;
            if (knee1.y < definingPoint.y + legSize) {
                knee1.y = definingPoint.y + legSize;
            }

            knee2.y = leaderEndPoint.y - legSize;
            textOffsetV = RVector(0,1);
        }
        else {
            knee1.y = leaderEndPoint.y + legSize*2;
            if (knee1.y > definingPoint.y - legSize) {
                knee1.y = definingPoint.y - legSize;
            }

            knee2.y = leaderEndPoint.y + legSize;
            textOffsetV = RVector(0,-1);
        }
    }

    // horizontal, measuring Y
    else {
        knee1.y = definingPoint.y;
        knee2.y = leaderEndPoint.y;

        if (definingPoint.x < leaderEndPoint.x) {
            knee1.x = leaderEndPoint.x - legSize*2;
            if (knee1.x < definingPoint.x + legSize) {
                knee1.x = definingPoint.x + legSize;
            }

            knee2.x = leaderEndPoint.x - legSize;
            textOffsetV = RVector(1,0);
        }
        else {
            knee1.x = leaderEndPoint.x + legSize*2;
            if (knee1.x > definingPoint.x - legSize) {
                knee1.x = definingPoint.x - legSize;
            }

            knee2.x = leaderEndPoint.x + legSize;
            textOffsetV = RVector(-1,0);
        }
    }

    RLine line;

    if (definingPoint.getDistanceTo(knee1) > dimexo) {
        line = RLine(definingPoint + textOffsetV*dimexo, knee1);
        RLine dummy;
        adjustExtensionLineFixLength(line, dummy, false);
        shapes.append(QSharedPointer<RLine>(new RLine(line)));
    }

    line = RLine(knee1, knee2);
    shapes.append(QSharedPointer<RLine>(new RLine(line)));

    line = RLine(knee2, leaderEndPoint);
    shapes.append(QSharedPointer<RLine>(new RLine(line)));

    double textHeight = dimensionData->getDimtxt();
    double dimgap = dimensionData->getDimgap();

    //double dimLineLength = RNANDOUBLE;
    //if (!middleOfText.isValid()) {
    //    middleOfText = RVector(0,0);
    //}
    //RVector oldMot = textPositionCenter;
    //textPositionCenter = RVector(0,0);
    //data.getTextData();
    //textPositionCenter = oldMot;

    //textData.getBoundingBox();

    RTextData& textData = data.initTextData();
    double textWidth = textData.getWidth();

    RVector textPos;
    //if (textPosition.isValid() /*&& !autoText*/) {
    if (data.hasCustomTextPosition()) {
        //textPos = textPositionCenter;
        //autoTextPos = false;
    } else {
        if (!data.isMeasuringXAxis()) {
            textPos = leaderEndPoint + textOffsetV * (textWidth/2.0+dimgap);
        }
        else {
            textPos = leaderEndPoint + textOffsetV * (textHeight/2.0+dimgap);
        }
        //RVector textPositionCenter = textPos;
        //middleOfText = RVector::invalid;
        //autoTextPos = true;

        dimensionData->updateTextPositionCenter(textPos);
    }
    textData.move(data.getTextPosition());

    data.updateTextData(textData);
    RBox bbox = textData.getBoundingBox(false);
    for (int i=0; i<shapes.length(); i++) {
        bbox.growToInclude(shapes[i]->getBoundingBox());
    }
    data.updateBoundingBox(bbox);
    data.updateShapes(shapes);
}

void RDimStyleProxyBasic::renderDimRadial() {
    const RDimRadialData& data = *dynamic_cast<const RDimRadialData*>(dimensionData);

//    QString text = data.getText();
//    RVector chordPoint = data.getChordPoint();
//    RVector definitionPoint = data.getDefinitionPoint();
//    bool dimtih = dimensionData->getDimtih();

//    // rotate text so it's readable from the bottom or right (ISO)
//    // quadrant 1 & 4
//    bool corrected=false;

//    double textAngle;
//    if (dimtih) {
//        textAngle = 0.0;
//    }
//    else {
//        textAngle = RMath::makeAngleReadable(chordPoint.getAngleTo(definitionPoint), true, &corrected);
//    }

//    // export text label:
//    RTextData& textData = data.initTextData();
//    double textWidth = textData.getWidth();
//    updateTextPosition(text, textWidth, chordPoint, definitionPoint, corrected);
//    textData.rotate(textAngle, RVector(0,0));
//    textData.move(dimensionData->getTextPosition());

//    QList<QSharedPointer<RShape> > shapes = getDimensionLineShapes(definitionPoint, chordPoint, false, true);

//    data.updateTextData(textData);
//    RBox bbox = textData.getBoundingBox(false);
//    for (int i=0; i<shapes.length(); i++) {
//        bbox.growToInclude(shapes[i]->getBoundingBox());
//    }
//    data.updateBoundingBox(bbox);
//    data.updateShapes(shapes);




    //QList<QSharedPointer<RShape> > shapes;

    //defaultAngle = 0.0;

    RVector definitionPoint = data.getDefinitionPoint();
    RVector chordPoint = data.getChordPoint();

    double angle = definitionPoint.getAngleTo(chordPoint);
    double radius = definitionPoint.getDistanceTo(chordPoint);

    // text distance to line (DIMGAP)
    double dimgap = dimensionData->getDimgap();
    double dimtxt = dimensionData->getDimtxt();
    double dimasz = dimensionData->getDimasz();
    bool archTick = dimensionData->useArchTick();
    int dimtad = dimensionData->getDimtad();
    bool dimtih = dimensionData->getDimtih();

    // length of dimension line:
    double length = definitionPoint.getDistanceTo(chordPoint);

//    RVector oldMot = textPositionCenter;
//    textPositionCenter = RVector(0,0);
//    //dimLineLength = RNANDOUBLE;
//    getTextData();
//    textPositionCenter = oldMot;

    RTextData& textData = data.initTextData();

    //QList<QSharedPointer<RShape> > shapes = getDimensionLineShapes(chordPoint, definitionPoint, true, true);

    double textWidth = textData.getWidth();

    // do we have to put the arrow / text outside of the arc?
    bool outsideArrow = (length < dimasz*2+textWidth);
    bool outsideLabel = outsideArrow;

    // force flipping arrows (against logic above):
    if (data.isArrow1Flipped()) {
        outsideArrow = !outsideArrow;
        outsideLabel = outsideArrow;
    }

    double arrowAngle;
    if (outsideArrow) {
        if (outsideLabel) {
            length += dimasz*2;
            if (!dimtih) {
                length += textWidth;
            }
        }
        else {
            length += dimasz*2;
        }
        arrowAngle = angle+M_PI;
    } else {
        if (outsideLabel) {
            length += dimasz*2;
            if (!dimtih) {
                length += textWidth;
            }
        }
        arrowAngle = angle;
    }

    RVector dimLineEndPoint = RVector::createPolar(length, angle);
    dimLineEndPoint+=definitionPoint;

//    // dimension line:
//    //shapes.append(QSharedPointer<RShape>(new RLine(definitionPoint, v3)));
//    QList<QSharedPointer<RShape> > shapes = getDimensionLineShapes(definitionPoint, v3, false, false);

//    // create arrow:
//    shapes.append(getArrow(chordPoint, arrowAngle));

    RVector arrow1Pos = RVector::invalid;
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

    if (dimtih) {
        textAngle = 0.0;
    }

    RVector textPos;
    if (data.hasCustomTextPosition()) {
        //textPos = textPositionCenter;
    } else {
        if (outsideLabel) {
            if (outsideArrow) {
                double dist = radius + dimasz + (length - radius - dimasz)/2.0;
                if (dimtad==0) {
                    dist += dimasz;
                }
                textPos.setPolar(dist, angle);
            }
            else {
                textPos.setPolar(length-textWidth/2.0-dimasz, angle);
            }

            if (dimtih) {
                // move text to the right if outside and horizontal:
                if (dimLineEndPoint.x<definitionPoint.x) {
                    textPos.x = dimLineEndPoint.x - definitionPoint.x - (textWidth/2.0 + dimasz + dimgap);
                }
                else {
                    textPos.x = dimLineEndPoint.x - definitionPoint.x + (textWidth/2.0 + dimasz + dimgap);
                }
                textPos.y = dimLineEndPoint.y - definitionPoint.y;
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
        QString text = data.getText();
        if (!text.contains("\\X")) {
            if (dimtad!=0 && !dimtih) {
                // text above dimension line (dimtad is 1):
                textPos += distV;
            }
        }

        //dimensionData->updateTextPositionSide(RVector::invalid);
        dimensionData->updateTextPositionCenter(textPos);
    }
    //defaultAngle = textAngle;
    textData.rotate(textAngle, RVector(0,0));
    textData.move(data.getTextPosition());
    data.updateTextData(textData);

    // dimension line:
    //QList<QSharedPointer<RShape> > shapes;
    //shapes.append(QSharedPointer<RShape>(new RLine(definitionPoint, v3)));
    QList<QSharedPointer<RShape> > shapes = getDimensionLineShapes(definitionPoint, dimLineEndPoint, false, false);

    // horizontal line to label:
    if (outsideLabel && dimtih) {
        if (dimLineEndPoint.x<definitionPoint.x) {
            shapes.append(QSharedPointer<RLine>(new RLine(dimLineEndPoint, dimLineEndPoint - RVector(dimasz, 0))));
        }
        else {
            shapes.append(QSharedPointer<RLine>(new RLine(dimLineEndPoint, dimLineEndPoint + RVector(dimasz, 0))));
        }
    }

    // create arrow:
    shapes.append(getArrow(chordPoint, arrowAngle));

    RBox bbox = textData.getBoundingBox(false);
    for (int i=0; i<shapes.length(); i++) {
        bbox.growToInclude(shapes[i]->getBoundingBox());
    }
    data.updateBoundingBox(bbox);
    data.updateShapes(shapes);
    data.updateArrowPos1(arrow1Pos);
}

void RDimStyleProxyBasic::renderDimDiametric() {
    const RDimDiametricData& data = *dynamic_cast<const RDimDiametricData*>(dimensionData);

    QString text = data.getText();
    RVector chordPoint = data.getChordPoint();
    RVector definitionPoint = data.getDefinitionPoint();
    bool dimtih = dimensionData->getDimtih();

    // rotate text so it's readable from the bottom or right (ISO)
    // quadrant 1 & 4
    bool corrected=false;

    double textAngle;
    if (dimtih) {
        textAngle = 0.0;
    }
    else {
        textAngle = RMath::makeAngleReadable(chordPoint.getAngleTo(definitionPoint), true, &corrected);
    }

    updateOutsideArrow(chordPoint, definitionPoint);

    // export text label:
    RTextData& textData = data.initTextData();
    double textWidth = textData.getWidth();
    updateTextPosition(text, textWidth, chordPoint, definitionPoint, corrected);
    textData.rotate(textAngle, RVector(0,0));
    textData.move(dimensionData->getTextPosition());
    data.updateTextData(textData);

    QList<QSharedPointer<RShape> > shapes = getDimensionLineShapes(chordPoint, definitionPoint, true, true);

    //data.updateTextData(textData);
    RBox bbox = textData.getBoundingBox(false);
    for (int i=0; i<shapes.length(); i++) {
        bbox.growToInclude(shapes[i]->getBoundingBox());
    }
    data.updateBoundingBox(bbox);
    data.updateShapes(shapes);
    //data.updateArrowPos1(arrow1Pos);
    //data.updateArrowPos1(arrow2Pos);
}

void RDimStyleProxyBasic::renderDimAngular() {
    const RDimAngularData& data = *dynamic_cast<const RDimAngularData*>(dimensionData);

    bool parallel = false;
    if (data.getType()==RS::EntityDimArcLength) {
        if (data.getAngle()<M_PI/2) {
            parallel = true;
        }
    }

    QList<QSharedPointer<RShape> > shapes;

    double dimexo = dimensionData->getDimexo();
    double dimexe = dimensionData->getDimexe();
    double dimtxt = dimensionData->getDimtxt();
    double dimgap = dimensionData->getDimgap();
    double dimasz = dimensionData->getDimasz();
    int dimtad = dimensionData->getDimtad();
    bool dimtih = dimensionData->getDimtih();

    // find out center:
    RVector center = data.getCenter();
    if (!center.isValid()) {
        //return ret;
    }

    double ang1 = 0.0;
    double ang2 = 0.0;
    bool reversed = false;
    RVector p1;
    RVector p2;

    data.getAngles(ang1, ang2, reversed, p1, p2);

    double rad = data.getDimArcPosition().getDistanceTo(center);

    // dimension line arc:
    RArc dimArc(center, rad, ang1, ang2, reversed);

    // correct arc when using parallel extension lines (arc length dimension for angle < 90):
    if (parallel) {
        RVector dir;

        double midAngle = center.getAngleTo(dimArc.getMiddlePoint());
        double arcRad = center.getDistanceTo(data.getExtensionLine1End());
        dir.setPolar(1.0, midAngle);

        if (rad<arcRad) {
            // dimension inside of arc: use same radius as for arc:
            rad = arcRad;
            dir.rotate(M_PI);
        }

        RCircle c(data.getDimArcPosition(), rad);
        RLine middleLine(center, midAngle, 1.0);
        QList<RVector> ips = RShape::getIntersectionPointsLC(middleLine, c, false);
        RVector cent = center.getClosest(ips);

        dimArc = RArc(cent, rad, ang1, ang2, reversed);

        // arc we are dimensioning:
        RArc arc(center, arcRad, ang1, ang2, reversed);

        RVector ip1, ip2;
        RLine line1(arc.getStartPoint(), arc.getStartPoint() + dir);
        QList<RVector> ips1 = RShape::getIntersectionPointsLA(line1, dimArc, false, true);
        if (ips1.length()==1) {
            ip1 = ips1[0];
        }

        RLine line2(arc.getEndPoint(), arc.getEndPoint() + dir);
        QList<RVector> ips2 = RShape::getIntersectionPointsLA(line2, dimArc, false, true);
        if (ips2.length()==1) {
            ip2 = ips2[0];
        }

        dimArc.trimStartPoint(ip1);
        dimArc.trimEndPoint(ip2);

        // extension line:
        RLine extLine1 = RLine(arc.getStartPoint() + dir*dimexo, ip1 + dir*dimexe);
        RLine extLine2 = RLine(arc.getEndPoint() + dir*dimexo, ip2 + dir*dimexe);

        adjustExtensionLineFixLength(extLine1, extLine2);

        shapes.append(QSharedPointer<RShape>(new RLine(extLine1)));
        shapes.append(QSharedPointer<RShape>(new RLine(extLine2)));
    }
    else {
        RVector dir;
        double len;
        double dist;
        int f;

        // 1st extension line:
        dist = center.getDistanceTo2D(p1);
        f=1;
        if (rad<dist) {
            f=-1;
        }
        len = rad - dist + dimexe*f;
        dir.setPolar(1.0, ang1);
        RLine extLine1 = RLine(center + dir*dist + dir*dimexo*f, center + dir*dist + dir*len);

        // 2nd extension line:
        dist = center.getDistanceTo2D(p2);
        f=1;
        if (rad<dist) {
            f=-1;
        }
        len = rad - dist + dimexe*f;
        dir.setPolar(1.0, ang2);
        RLine extLine2 = RLine(center + dir*dist + dir*dimexo*f, center + dir*dist + dir*len);

        adjustExtensionLineFixLength(extLine1, extLine2);

        shapes.append(QSharedPointer<RShape>(new RLine(extLine1)));
        shapes.append(QSharedPointer<RShape>(new RLine(extLine2)));

        //arc = RArc(center, rad, ang1, ang2, reversed);
    }

    // Create dimension line (arc):
    RArc dimArc2 = dimArc;

    // length of dimension arc:
    double distance = dimArc.getLength();

    // do we have to put the arrows outside of the arc?
    outsideArrow1 = (distance<dimasz*2);
    outsideArrow2 = outsideArrow1;

    // force flipping arrows (against logic above):
    if (data.isArrow1Flipped()) {
        outsideArrow1 = !outsideArrow1;
    }
    if (data.isArrow2Flipped()) {
        outsideArrow2 = !outsideArrow2;
    }

    // extend arc outside arrows
    double a = data.getDimasz()*2 / dimArc.getRadius();
    if (outsideArrow1) {
        dimArc2.setStartAngle(dimArc.isReversed() ? dimArc.getStartAngle() + a : dimArc.getStartAngle() - a);
    }
    if (outsideArrow2) {
        dimArc2.setEndAngle(dimArc.isReversed() ? dimArc.getEndAngle() - a : dimArc.getEndAngle() + a);
    }

    QSharedPointer<RArc> dimArcP(new RArc(dimArc2));
    shapes.append(dimArcP);

    // arrow angles:
    double arrowAngle1, arrowAngle2;
    double arrowAng;
    if (rad>1.0e-6) {
        arrowAng = data.getDimasz() / rad;
    }
    else {
        arrowAng = 0.0;
    }

    RVector v1;
    if (!dimArc.isReversed()) {
        if (outsideArrow1) {
            v1.setPolar(rad, dimArc.getStartAngle()-arrowAng);
        }
        else {
            v1.setPolar(rad, dimArc.getStartAngle()+arrowAng);
        }
    } else {
        if (outsideArrow1) {
            v1.setPolar(rad, dimArc.getStartAngle()+arrowAng);
        }
        else {
            v1.setPolar(rad, dimArc.getStartAngle()-arrowAng);
        }
    }
    v1+=dimArc.getCenter();
    arrowAngle1 = dimArc.getStartPoint().getAngleTo(v1);
    arrowAngle1 = arrowAngle1+M_PI;

    RVector v2;
    if (!dimArc.isReversed()) {
        if (outsideArrow2) {
            v2.setPolar(rad, dimArc.getEndAngle()+arrowAng);
        }
        else {
            v2.setPolar(rad, dimArc.getEndAngle()-arrowAng);
        }
    } else {
        if (outsideArrow2) {
            v2.setPolar(rad, dimArc.getEndAngle()-arrowAng);
        }
        else {
            v2.setPolar(rad, dimArc.getEndAngle()+arrowAng);
        }
    }
    v2+=dimArc.getCenter();
    arrowAngle2 = dimArc.getEndPoint().getAngleTo(v2);
    arrowAngle2 = arrowAngle2+M_PI;

    // Arrows:
    QList<QSharedPointer<RShape> > arrow = getArrow(dimArc.getStartPoint(), arrowAngle1);
    shapes.append(arrow);
    RVector arrow1Pos = dimArc.getStartPoint() + RVector::createPolar(dimasz, arrowAngle1 + M_PI);
    arrow = getArrow(dimArc.getEndPoint(), arrowAngle2);
    shapes.append(arrow);
    RVector arrow2Pos = dimArc.getEndPoint() + RVector::createPolar(dimasz, arrowAngle2 + M_PI);

    RVector textPos = dimArc.getMiddlePoint();
    double dimAngle1 = textPos.getAngleTo(dimArc.getCenter())-M_PI/2.0;
    if (data.hasCustomTextPosition()) {
        dimAngle1 = data.getTextPosition().getAngleTo(dimArc.getCenter())-M_PI/2.0;
    }

    RVector distV;
    double textAngle;
    if (dimtih) {
        textAngle = 0.0;
    }
    else {
        // rotate text so it's readable from the bottom or right (ISO)
        // quadrant 1 & 4
        if (RMath::isAngleReadable(dimAngle1)) {
            distV.setPolar(dimgap + dimtxt/2, dimAngle1+M_PI/2.0);
            textAngle = dimAngle1;
        }
        // quadrant 2 & 3
        else {
            distV.setPolar(dimgap + dimtxt/2, dimAngle1-M_PI/2.0);
            textAngle = dimAngle1+M_PI;
        }
    }

    if (!data.hasCustomTextPosition()) {
        // move text away from dimension line:
        double f = 1.0;
        if (data.getMeasurement().contains("\\P")) {
            f = 2.0;
        }

        if (dimtad!=0 && !dimtih) {
            // text above dimension line (dimtad is 1):
            textPos+=distV*f;
        }

        dimensionData->updateTextPositionCenter(textPos);
    }

    RTextData& textData = data.initTextData();
    //double textWidth = textData.getWidth();
    textData.rotate(textAngle, RVector(0,0));
    textData.move(dimensionData->getTextPosition());

    breakUpDimArc(shapes, dimArcP);

    data.updateTextData(textData);
    RBox bbox = textData.getBoundingBox(false);
    for (int i=0; i<shapes.length(); i++) {
        bbox.growToInclude(shapes[i]->getBoundingBox());
    }
    data.updateBoundingBox(bbox);
    data.updateShapes(shapes);
    data.updateArrowPos1(arrow1Pos);
    data.updateArrowPos1(arrow2Pos);
}

/**
 * \return Text position
 */
void RDimStyleProxyBasic::updateTextPosition(const QString& text, double textWidth, const RVector& dimLine1, const RVector& dimLine2, bool corrected, double angleHint) {
    if (!dimensionData->hasCustomTextPosition()) {
        double dimtxt = dimensionData->getDimtxt();
        double dimgap = dimensionData->getDimgap();
        double dimasz = dimensionData->getDimasz();
        int dimtad = dimensionData->getDimtad();
        bool dimtih = dimensionData->getDimtih();

        RVector newTextPos = RVector::getAverage(dimLine1, dimLine2);
        double dimAngle1;
        if (dimLine1.equalsFuzzy(dimLine2)) {
            dimAngle1 = angleHint;
        }
        else {
            dimAngle1 = dimLine1.getAngleTo(dimLine2);
        }

        //bool corrected=false;
        //defaultAngle =
        //RMath::makeAngleReadable(dimAngle1, true, &corrected);

        RVector distV;
        if (corrected) {
            distV.setPolar(dimgap + dimtxt/2.0, dimAngle1-M_PI/2.0);
        } else {
            distV.setPolar(dimgap + dimtxt/2.0, dimAngle1+M_PI/2.0);
        }

        // move text away from dimension line:
        if (!text.contains("\\X")) {
            if (dimtad!=0 && !dimtih) {
                // text above dimension line (dimtad is 1):
                newTextPos+=distV;
            }
        }

        double dimLineLength = dimLine1.getDistanceTo(dimLine2);
        double angle;
        if (dimLine1.equalsFuzzy(dimLine2)) {
            angle = angleHint;
        }
        else {
            angle = dimLine1.getAngleTo(dimLine2);
        }
        RVector textPositionSide;

        // minimum space required for text:
        double minSpace = dimLineLength;
        if (dimtad==0 || dimtih) {
            if (!outsideArrow1) {
                minSpace -= dimasz;
            }
            if (!outsideArrow2) {
                minSpace -= dimasz;
            }
            // if text is centered on dim line, we need more space:
            minSpace -= dimgap*2;
        }
        else {
            if (outsideArrow1 && outsideArrow2) {
                minSpace -= dimgap*2;
            }
        }

        if (!RMath::isNaN(minSpace) && textWidth>minSpace && !dimtih) {
            double h = textWidth/2.0+dimLineLength/2.0+dimgap;
            if (dimtad==0) {
                // text centered with dimension line:
                // move further away to move away from arrows:
                if (outsideArrow2) {
                    h += dimasz;
                }
//                else {
//                    h += dimgap;
//                }
            }
            RVector distH;
            distH.setPolar(h, angle);
            textPositionSide = newTextPos;
            textPositionSide+=distH;
        }
        else {
            textPositionSide = RVector::invalid;
        }

        dimensionData->updateTextPositionSide(textPositionSide);
        dimensionData->updateTextPositionCenter(newTextPos);
    }
}

void RDimStyleProxyBasic::updateOutsideArrow(const RVector& p1, const RVector& p2) {
    // length of dimension line:
    double dimLineLength = p1.getDistanceTo(p2);

    // do we have to put the arrows outside of the line?
    outsideArrow1 = !hasSpaceForArrows(dimLineLength);
    outsideArrow2 = outsideArrow1;

    // force flipping arrows (against logic above):
    if (dimensionData->isArrow1Flipped()) {
        outsideArrow1 = !outsideArrow1;
    }
    if (dimensionData->isArrow2Flipped()) {
        outsideArrow2 = !outsideArrow2;
    }
}

/**
 * Creates a dimensioning line (line with one, two or no arrows).
 */
QList<QSharedPointer<RShape> > RDimStyleProxyBasic::getDimensionLineShapes(const RVector& p1, const RVector& p2, bool arrow1, bool arrow2, double angleHint) const {
    QList<QSharedPointer<RShape> > ret;

    // arrow size:
    double dimasz = dimensionData->getDimasz();
    bool archTick = dimensionData->useArchTick();

    // length of dimension line:
//    double dimLineLength = p1.getDistanceTo(p2);

    // do we have to put the arrows outside of the line?
//    outsideArrow1 = !hasSpaceForArrows(dimLineLength);
//    outsideArrow2 = outsideArrow1;

    // force flipping arrows (against logic above):
//    if (dimensionData->isArrow1Flipped()) {
//        outsideArrow1 = !outsideArrow1;
//    }
//    if (dimensionData->isArrow2Flipped()) {
//        outsideArrow2 = !outsideArrow2;
//    }

//    qDebug() << "outsideArrow1:" << outsideArrow1;

    // arrow angles:
    double arrowAngle1, arrowAngle2;

    // Create dimension line:
    RLine dimensionLine(p1, p2);
    bool zeroLine = dimensionLine.getLength()<RS::PointTolerance;

    if (outsideArrow1==false) {
        arrowAngle1 = dimensionLine.getDirection2();
    }
    else {
        if (zeroLine && !RMath::isNaN(angleHint)) {
            arrowAngle1 = angleHint;
        }
        else {
            arrowAngle1 = dimensionLine.getDirection1();
        }
    }

    if (outsideArrow2==false) {
        arrowAngle2 = dimensionLine.getDirection1();
    }
    else {
        if (zeroLine && !RMath::isNaN(angleHint)) {
            arrowAngle2 = angleHint + M_PI;
        }
        else {
            arrowAngle2 = dimensionLine.getDirection2();
        }
    }

    // extend dimension line outside arrows
    RVector dir;
    double dimLineAngle;
    if (zeroLine) {
        dimLineAngle = angleHint;
    }
    else {
        dimLineAngle = dimensionLine.getDirection1();
    }
    dir.setPolar(dimensionData->getDimasz()*2, dimLineAngle);
    if (outsideArrow1) {
        if (arrow1) {
            dimensionLine.setStartPoint(p1 - dir);
        }
    }
    if (outsideArrow2) {
        if (arrow2) {
            dimensionLine.setEndPoint(p2 + dir);
        }
    }

    ret.append(QSharedPointer<RShape>(new RLine(dimensionLine)));

    RVector arrow1Pos = RVector::invalid;
    if (arrow1) {
        QList<QSharedPointer<RShape> > arrow = getArrow(p1, arrowAngle1);
        ret.append(arrow);
        if (!archTick) {
            arrow1Pos = p1 + RVector::createPolar(dimasz, arrowAngle1 + M_PI);
        }
    }

    RVector arrow2Pos = RVector::invalid;
    if (arrow2) {
        QList<QSharedPointer<RShape> > arrow = getArrow(p2, arrowAngle2);
        ret.append(arrow);
        if (!archTick) {
            arrow2Pos = p2 + RVector::createPolar(dimasz, arrowAngle2 + M_PI);
        }
    }

    dimensionData->updateArrowPos1(arrow1Pos);
    dimensionData->updateArrowPos2(arrow2Pos);

    return ret;
}

bool RDimStyleProxyBasic::hasSpaceForArrows(double dimLineLength) const {
    return dimLineLength >= dimensionData->getDimasz()*2.5;
}

QList<QSharedPointer<RShape> > RDimStyleProxyBasic::getArrow(const RVector& position, double direction) const {

    QList<QSharedPointer<RShape> > ret;
    double dimasz = dimensionData->getDimasz();

    // architecture tick:
    if (dimensionData->useArchTick()) {
        RVector p1(dimasz/2, dimasz/2);

        // TODO: replace with block reference to arrow symbol

        RLine line(p1, -p1);
        line.rotate(direction, RVector(0,0));
        line.move(position);
        ret.append(QSharedPointer<RLine>(new RLine(line)));
    }

    // standard arrow:
    else {
        RTriangle arrow = RTriangle::createArrow(position, direction, dimasz);
        ret.append(QSharedPointer<RTriangle>(new RTriangle(arrow)));
    }

    return ret;
}

void RDimStyleProxyBasic::adjustExtensionLineFixLength(RLine& extLine1, RLine& extLine2, bool addDimExe) const {
    // extension lines with fixed length:
    if (dimensionData->isExtLineFix()) {
        double extLineLen = dimensionData->getExtLineFixLength();
        if (RMath::fuzzyCompare(extLineLen, 0.0)) {
            // value of 0 for extension line fixed length means fixed length is off:
            return;
        }

        if (addDimExe) {
            double dimexe = dimensionData->getDimexe();
            extLineLen += dimexe;
        }
        if (extLine1.isValid()) {
            extLine1.setLength(qMin(extLine1.getLength(), extLineLen), false);
        }
        if (extLine2.isValid()) {
            extLine2.setLength(qMin(extLine2.getLength(), extLineLen), false);
        }
    }
}
