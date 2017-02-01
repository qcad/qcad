/**
 * Copyright (c) 2011-2017 by Andrew Mustun. All rights reserved.
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
#include "RDimAngularData.h"
#include "RUnit.h"

RDimAngularData::RDimAngularData() {
}

RDimAngularData::RDimAngularData(RDocument* document, const RDimAngularData& data)
    : RDimensionData(document) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

/**
 * \param definitionPoint Definition point is extensionLine2End.
 */
RDimAngularData::RDimAngularData(const RDimensionData& dimData,
                                 const RVector& extensionLine1Start,
                                 const RVector& extensionLine1End,
                                 const RVector& extensionLine2Start,
                                 const RVector& dimArcPosition)
    : RDimensionData(dimData),
      extensionLine1Start(extensionLine1Start),
      extensionLine1End(extensionLine1End),
      extensionLine2Start(extensionLine2Start),
      dimArcPosition(dimArcPosition) {

}

bool RDimAngularData::isValid() const {
    return RDimensionData::isValid() &&
            extensionLine1Start.isValid() &&
            extensionLine1End.isValid() &&
            extensionLine2Start.isValid() &&
            dimArcPosition.isValid();
}

QList<RRefPoint> RDimAngularData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    QList<RRefPoint> ret = RDimensionData::getReferencePoints(hint);

    ret.append(getTextPosition());
    ret.append(extensionLine1Start);
    ret.append(extensionLine1End);
    ret.append(extensionLine2Start);
    ret.append(dimArcPosition);

    return ret;
}

bool RDimAngularData::moveReferencePoint(const RVector& referencePoint,
        const RVector& targetPoint) {

    bool ret = false;

    if (referencePoint.equalsFuzzy(extensionLine1Start)) {
        extensionLine1Start = targetPoint;
        autoTextPos = true;
        ret = true;
    }
    else if (referencePoint.equalsFuzzy(extensionLine1End)) {
        extensionLine1End = targetPoint;
        autoTextPos = true;
        ret = true;
    }
    else if (referencePoint.equalsFuzzy(extensionLine2Start)) {
        extensionLine2Start = targetPoint;
        autoTextPos = true;
        ret = true;
    }
    else if (referencePoint.equalsFuzzy(dimArcPosition)) {
        dimArcPosition = targetPoint;
        autoTextPos = true;
        ret = true;
    }

    if (!ret) {
        ret = RDimensionData::moveReferencePoint(referencePoint, targetPoint);
    }

    if (ret) {
        update();
    }

    return ret;
}

bool RDimAngularData::move(const RVector& offset) {
    RDimensionData::move(offset);
    extensionLine1Start.move(offset);
    extensionLine1End.move(offset);
    extensionLine2Start.move(offset);
    dimArcPosition.move(offset);
    update();
    return true;
}

bool RDimAngularData::rotate(double rotation, const RVector& center) {
    RDimensionData::rotate(rotation, center);
    extensionLine1Start.rotate(rotation, center);
    extensionLine1End.rotate(rotation, center);
    extensionLine2Start.rotate(rotation, center);
    dimArcPosition.rotate(rotation, center);
    update();
    return true;
}

bool RDimAngularData::scale(const RVector& scaleFactors, const RVector& center) {
    RDimensionData::scale(scaleFactors, center);
    extensionLine1Start.scale(scaleFactors, center);
    extensionLine1End.scale(scaleFactors, center);
    extensionLine2Start.scale(scaleFactors, center);
    dimArcPosition.scale(scaleFactors, center);
    update();
    return true;
}

bool RDimAngularData::mirror(const RLine& axis) {
    RDimensionData::mirror(axis);
    extensionLine1Start.mirror(axis);
    extensionLine1End.mirror(axis);
    extensionLine2Start.mirror(axis);
    dimArcPosition.mirror(axis);
    update();
    return true;
}

QList<QSharedPointer<RShape> > RDimAngularData::getShapes(const RBox& queryBox, bool ignoreComplex, bool segment) const {
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
    double dimtxt = getDimtxt();
    double dimgap = getDimgap();
    double dimasz = getDimasz();

    // find out center:
    RVector center = getCenter();

    if (!center.isValid()) {
        return ret;
    }

    double ang1 = 0.0;
    double ang2 = 0.0;
    bool reversed = false;
    RVector p1;
    RVector p2;

    getAngles(ang1, ang2, reversed, p1, p2);

    double rad = dimArcPosition.getDistanceTo(center);

    RLine line;
    RVector dir;
    double len;
    double dist;

    // 1st extension line:
    dist = center.getDistanceTo2D(p1);
    len = rad - dist + dimexe;
    dir.setPolar(1.0, ang1);
    line = RLine(center + dir*dist + dir*dimexo, center + dir*dist + dir*len);
    ret.append(QSharedPointer<RShape>(new RLine(line)));

    // 2nd extension line:
    dist = center.getDistanceTo2D(p2);
    len = rad - dist + dimexe;
    dir.setPolar(1.0, ang2);
    line = RLine(center + dir*dist + dir*dimexo, center + dir*dist + dir*len);
    ret.append(QSharedPointer<RShape>(new RLine(line)));

    // Create dimension line (arc):
    RArc arc(center, rad, ang1, ang2, reversed);
    ret.append(QSharedPointer<RShape>(new RArc(arc)));

    // length of dimension arc:
    double distance = arc.getLength();

    // do we have to put the arrows outside of the arc?
    bool outsideArrows = (distance<dimasz*2);

    // arrow angles:
    double arrowAngle1, arrowAngle2;
    double arrowAng;
    if (rad>1.0e-6) {
        arrowAng = getDimasz() / rad;
    }
    else {
        arrowAng = 0.0;
    }

    if (outsideArrows) {
        arrowAngle1 = arc.getDirection1();
        arrowAngle2 = arc.getDirection2();
    }
    else {
        RVector v1, v2;
        if (!arc.isReversed()) {
            v1.setPolar(rad, arc.getStartAngle()+arrowAng);
        } else {
            v1.setPolar(rad, arc.getStartAngle()-arrowAng);
        }
        v1+=arc.getCenter();
        arrowAngle1 = arc.getStartPoint().getAngleTo(v1);


        if (!arc.isReversed()) {
            v2.setPolar(rad, arc.getEndAngle()-arrowAng);
        } else {
            v2.setPolar(rad, arc.getEndAngle()+arrowAng);
        }
        v2+=arc.getCenter();
        arrowAngle2 = arc.getEndPoint().getAngleTo(v2);

        arrowAngle1 = arrowAngle1+M_PI;
        arrowAngle2 = arrowAngle2+M_PI;
    }

    // Arrows:
    //RTriangle arrow = RTriangle::createArrow(arc.getStartPoint(), arrowAngle1, dimasz);
    QList<QSharedPointer<RShape> > arrow = getArrow(arc.getStartPoint(), arrowAngle1);
    ret.append(arrow);
    //arrow = RTriangle::createArrow(arc.getEndPoint(), arrowAngle2, dimasz);
    arrow = getArrow(arc.getEndPoint(), arrowAngle2);
    ret.append(arrow);
    //ret.append(QSharedPointer<RShape>(new RTriangle(arrow)));

    //RVector oldMot = textPosition;
    //textPosition = RVector(0,0);
    //defaultAngle = 0.0;
    //dimLineLength = RNANDOUBLE;
    //getTextData();
    //textPosition = oldMot;

    RVector textPos = arc.getMiddlePoint();
    double dimAngle1 = textPos.getAngleTo(arc.getCenter())-M_PI/2.0;
    if (!autoTextPos) {
        dimAngle1 = textPositionCenter.getAngleTo(arc.getCenter())-M_PI/2.0;
    }

    RVector distV;
    double textAngle;
    // rotate text so it's readable from the bottom or right (ISO)
    // quadrant 1 & 4
    if (dimAngle1>M_PI/2.0*3.0+0.001 ||
        dimAngle1<M_PI/2.0+0.001) {

        distV.setPolar(dimgap + dimtxt/2, dimAngle1+M_PI/2.0);
        textAngle = dimAngle1;
    }
    // quadrant 2 & 3
    else {
        distV.setPolar(dimgap + dimtxt/2, dimAngle1-M_PI/2.0);
        textAngle = dimAngle1+M_PI;
    }

    if (!autoTextPos) {
        textPos = textPositionCenter;
    } else {
        // move text away from dimension line:
        textPos+=distV;

        textPositionCenter = textPos;
    }
    defaultAngle = textAngle;
    //getTextData();
    //textData.rotate(textAngle, RVector(0,0));
    //textData.move(textPos);

    return ret;
}

/**
 * \return Angle of the measured dimension.
 */
double RDimAngularData::getAngle() const {
    double ang1 = 0.0;
    double ang2 = 0.0;
    bool reversed = false;
    RVector p1;
    RVector p2;

    getAngles(ang1, ang2, reversed, p1, p2);

    if (!reversed) {
        if (ang2<ang1) {
            ang2+=2*M_PI;
        }
        return ang2-ang1;
    } else {
        if (ang1<ang2) {
            ang1+=2*M_PI;
        }
        return ang1-ang2;
    }
}

/**
 * Finds out which angles this dimension actually measures.
 *
 * \param ang1 Reference will return the start angle
 * \param ang2 Reference will return the end angle
 * \param reversed Reference will return the reversed flag.
 *
 * \return true: on success
 */
bool RDimAngularData::getAngles(double& ang1, double& ang2, bool& reversed,
                              RVector& p1, RVector& p2) const {

    RVector center = getCenter();
    double ang = center.getAngleTo(dimArcPosition);
    bool done = false;

    // find out the angles this dimension refers to:
    for (int f1=0; f1<=1 && !done; ++f1) {
        ang1 = RMath::getNormalizedAngle(extensionLine1End.getAngleTo(extensionLine1Start) + f1*M_PI);
        if (f1==0) {
            p1 = extensionLine1Start;
        } else {
            p1 = extensionLine1End;
        }
        for (int f2=0; f2<=1 && !done; ++f2) {
            ang2 = RMath::getNormalizedAngle(extensionLine2Start.getAngleTo(definitionPoint) + f2*M_PI);
            if (f2==0) {
                p2 = definitionPoint;
            } else {
                p2 = extensionLine2Start;
            }
            for (int t=0; t<=1 && !done; ++t) {
                reversed = (bool)t;

                double angDiff;

                if (!reversed) {
                    if (ang2<ang1) {
                        ang2+=2*M_PI;
                    }
                    angDiff = ang2-ang1;
                } else {
                    if (ang1<ang2) {
                        ang1+=2*M_PI;
                    }
                    angDiff = ang1-ang2;
                }

                ang1 = RMath::getNormalizedAngle(ang1);
                ang2 = RMath::getNormalizedAngle(ang2);

                if (RMath::isAngleBetween(ang, ang1, ang2, reversed) && angDiff<=M_PI) {
                    done = true;
                    break;
                }
            }
        }
    }

    return done;
}

/**
 * \return Center of the measured dimension.
 */
RVector RDimAngularData::getCenter() const {
    RLine l1(extensionLine1End, extensionLine1Start);
    RLine l2(extensionLine2Start, definitionPoint);
    QList<RVector> vs = l1.getIntersectionPoints(l2, false);

    if (vs.isEmpty()) {
        return RVector::invalid;
    }

    return vs.at(0);
}

double RDimAngularData::getMeasuredValue() const {
    return getAngle();
}

QString RDimAngularData::getAutoLabel() const {
    QString ret;

    ret = formatAngleLabel(getMeasuredValue());

    return ret;
}
