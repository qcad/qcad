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
#include "RCircle.h"
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
RDimAngularData::RDimAngularData(const RDimensionData& dimData)
    : RDimensionData(dimData) {

}

bool RDimAngularData::isValid() const {
    return RDimensionData::isValid() &&
            getExtensionLine1End().isValid() &&
            getExtensionLine2End().isValid() &&
            getDimArcPosition().isValid();
}

bool RDimAngularData::isSane() const {
    return RDimensionData::isSane() &&
            getExtensionLine1End().isSane() &&
            getExtensionLine2End().isSane() &&
            getDimArcPosition().isSane();
}

QList<RRefPoint> RDimAngularData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    QList<RRefPoint> ret = RDimensionData::getReferencePoints(hint);

    ret.append(getTextPosition());
    ret.append(getExtensionLine1End());
    ret.append(getExtensionLine2End());
    ret.append(getDimArcPosition());

    return ret;
}

bool RDimAngularData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    Q_UNUSED(modifiers)

    bool ret = false;

    if (referencePoint.equalsFuzzy(getExtensionLine1End())) {
        setExtensionLine1End(targetPoint);
        autoTextPos = true;
        ret = true;
    }
    else if (referencePoint.equalsFuzzy(getExtensionLine2End())) {
        setExtensionLine2End(targetPoint);
        autoTextPos = true;
        ret = true;
    }
    else if (referencePoint.equalsFuzzy(getDimArcPosition())) {
        setDimArcPosition(targetPoint);
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

/*
bool RDimAngularData::move(const RVector& offset) {
    RDimensionData::move(offset);
    setExtensionLine1End(getExtensionLine1End() + offset);
    setExtensionLine2End(getExtensionLine2End() + offset);
    setDimArcPosition(getDimArcPosition() + offset);
    update();
    return true;
}

bool RDimAngularData::rotate(double rotation, const RVector& center) {
    RDimensionData::rotate(rotation, center);
    setExtensionLine1End(getExtensionLine1End().getRotated(rotation, center));
    setExtensionLine2End(getExtensionLine2End().getRotated(rotation, center));
    setDimArcPosition(getDimArcPosition().getRotated(rotation, center));
    update();
    return true;
}

bool RDimAngularData::scale(const RVector& scaleFactors, const RVector& center) {
    RDimensionData::scale(scaleFactors, center);
    setExtensionLine1End(getExtensionLine1End().getScaled(scaleFactors, center));
    setExtensionLine2End(getExtensionLine2End().getScaled(scaleFactors, center));
    setDimArcPosition(getDimArcPosition().getScaled(scaleFactors, center));
    update();
    return true;
}

bool RDimAngularData::mirror(const RLine& axis) {
    RDimensionData::mirror(axis);
    setExtensionLine1End(getExtensionLine1End().getMirrored(axis));
    setExtensionLine2End(getExtensionLine2End().getMirrored(axis));
    setDimArcPosition(getDimArcPosition().getMirrored(axis));
    update();
    return true;
}
*/

QList<QSharedPointer<RShape> > RDimAngularData::getShapes(const RBox& queryBox, bool ignoreComplex, bool segment) const {
    Q_UNUSED(queryBox)
    Q_UNUSED(ignoreComplex)
    Q_UNUSED(segment)

    QSharedPointer<RBlockReferenceEntity> dimBlockReference = getDimensionBlockReference();
    if (!dimBlockReference.isNull()) {
        return dimBlockReference->getShapes(queryBox, ignoreComplex);
    }

    bool parallel = false;
    if (getType()==RS::EntityDimArcLength) {
        if (getAngle()<M_PI/2) {
            parallel = true;
        }
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

    double rad = getDimArcPosition().getDistanceTo(center);

    // dimension line arc:
    RArc dimArc(center, rad, ang1, ang2, reversed);

    // correct arc when using parallel extension lines (arc length dimension for angle < 90):
    if (parallel) {
        RVector dir;

        double midAngle = center.getAngleTo(dimArc.getMiddlePoint());
        double arcRad = center.getDistanceTo(getExtensionLine1End());
        dir.setPolar(1.0, midAngle);

        if (rad<arcRad) {
            // dimension inside of arc: use same radius as for arc:
            rad = arcRad;
            dir.rotate(M_PI);
        }

        RCircle c(getDimArcPosition(), rad);
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

        ret.append(QSharedPointer<RShape>(new RLine(extLine1)));
        ret.append(QSharedPointer<RShape>(new RLine(extLine2)));
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

        ret.append(QSharedPointer<RShape>(new RLine(extLine1)));
        ret.append(QSharedPointer<RShape>(new RLine(extLine2)));

        //arc = RArc(center, rad, ang1, ang2, reversed);
    }

    // Create dimension line (arc):
    RArc dimArc2 = dimArc;

    // length of dimension arc:
    double distance = dimArc.getLength();

    // do we have to put the arrows outside of the arc?
    bool outsideArrow1 = (distance<dimasz*2);
    bool outsideArrow2 = outsideArrow1;

    // force flipping arrows (against logic above):
    if (isArrow1Flipped()) {
        outsideArrow1 = !outsideArrow1;
    }
    if (isArrow2Flipped()) {
        outsideArrow2 = !outsideArrow2;
    }

    // extend arc outside arrows
    //RVector dir;
    //dir.setPolar(getDimasz()*2, dimensionLine.getDirection1());
    double a = getDimasz()*2 / dimArc.getRadius();
    if (outsideArrow1) {
        dimArc2.setStartAngle(dimArc.isReversed() ? dimArc.getStartAngle() + a : dimArc.getStartAngle() - a);
        //arc.trimStartPoint(-getDimasz()*2);
        //arc.setStartAngle(arc.getStartAngle()-a);
    }
    if (outsideArrow2) {
        dimArc2.setEndAngle(dimArc.isReversed() ? dimArc.getEndAngle() - a : dimArc.getEndAngle() + a);
        //dimensionLine.setEndPoint(p2 + dir);
        //arc.trimEndPoint(-getDimasz()*2);
    }

    ret.append(QSharedPointer<RShape>(new RArc(dimArc2)));

    // arrow angles:
    double arrowAngle1, arrowAngle2;
    double arrowAng;
    if (rad>1.0e-6) {
        arrowAng = getDimasz() / rad;
    }
    else {
        arrowAng = 0.0;
    }

//    if (outsideArrow1) {
//        arrowAngle1 = arc.getDirection1();
//    }
//    else {
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
//    }

//    if (outsideArrow2) {
//        arrowAngle2 = arc.getDirection2();
//    }
//    else {
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
//    }

    // Arrows:
    //RTriangle arrow = RTriangle::createArrow(arc.getStartPoint(), arrowAngle1, dimasz);
    QList<QSharedPointer<RShape> > arrow = getArrow(dimArc.getStartPoint(), arrowAngle1);
    ret.append(arrow);
    arrow1Pos = dimArc.getStartPoint() + RVector::createPolar(dimasz, arrowAngle1 + M_PI);
    //arrow = RTriangle::createArrow(arc.getEndPoint(), arrowAngle2, dimasz);
    arrow = getArrow(dimArc.getEndPoint(), arrowAngle2);
    ret.append(arrow);
    arrow2Pos = dimArc.getEndPoint() + RVector::createPolar(dimasz, arrowAngle2 + M_PI);
    //ret.append(QSharedPointer<RShape>(new RTriangle(arrow)));

    //RVector oldMot = textPosition;
    //textPosition = RVector(0,0);
    //defaultAngle = 0.0;
    //dimLineLength = RNANDOUBLE;
    //getTextData();
    //textPosition = oldMot;

    RVector textPos = dimArc.getMiddlePoint();
    double dimAngle1 = textPos.getAngleTo(dimArc.getCenter())-M_PI/2.0;
    if (!autoTextPos) {
        dimAngle1 = textPositionCenter.getAngleTo(dimArc.getCenter())-M_PI/2.0;
    }

    RVector distV;
    double textAngle;
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

    if (!autoTextPos) {
        textPos = textPositionCenter;
    } else {
        // move text away from dimension line:
        double f = 1.0;
        if (getMeasurement().contains("\\P")) {
            f = 2.0;
        }
        textPos+=distV*f;

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

    bool dimArcLength = (getType()==RS::EntityDimArcLength);

    double ret;
    if (!reversed) {
        if (ang2<ang1) {
            ang2+=2*M_PI;
        }
        ret = ang2-ang1;
    } else {
        if (ang1<ang2) {
            ang1+=2*M_PI;
        }
        ret = ang1-ang2;
    }
    return ret;
}

double RDimAngularData::getMeasuredValue() const {
    return getAngle();
}

QString RDimAngularData::getAutoLabel() const {
    return formatAngleLabel(getMeasuredValue());
}

RArc RDimAngularData::getDimensionArc() const {
    RVector center = getCenter();
    double radius = center.getDistanceTo(getDimArcPosition());
    double ang1, ang2;
    bool reversed;
    RVector p1, p2;
    getAngles(ang1, ang2, reversed, p1, p2);
    return RArc(center, radius, ang1, ang2, reversed);
}
