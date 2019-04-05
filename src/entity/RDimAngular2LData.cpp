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
#include "RDimAngular2LData.h"
#include "RUnit.h"

RDimAngular2LData::RDimAngular2LData() {
}

RDimAngular2LData::RDimAngular2LData(RDocument* document, const RDimAngular2LData& data)
    : RDimAngularData(document) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

/**
 * \param definitionPoint Definition point is extensionLine2End.
 */
RDimAngular2LData::RDimAngular2LData(const RDimensionData& dimData,
                                 const RVector& extensionLine1Start,
                                 const RVector& extensionLine1End,
                                 const RVector& extensionLine2Start,
                                 const RVector& dimArcPosition)
    : RDimAngularData(dimData),
      extensionLine1Start(extensionLine1Start),
      extensionLine1End(extensionLine1End),
      extensionLine2Start(extensionLine2Start),
      dimArcPosition(dimArcPosition) {

}

bool RDimAngular2LData::isValid() const {
    return RDimAngularData::isValid() &&
            extensionLine1Start.isValid() &&
            extensionLine1End.isValid() &&
            extensionLine2Start.isValid() &&
            dimArcPosition.isValid();
}

bool RDimAngular2LData::isSane() const {
    return RDimAngularData::isSane() &&
            extensionLine1Start.isSane() &&
            extensionLine1End.isSane() &&
            extensionLine2Start.isSane() &&
            dimArcPosition.isSane();
}

QList<RRefPoint> RDimAngular2LData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    QList<RRefPoint> ret = RDimAngularData::getReferencePoints(hint);

    ret.append(extensionLine1Start);
    ret.append(extensionLine2Start);

    return ret;
}

bool RDimAngular2LData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    Q_UNUSED(modifiers)

    bool ret = false;

    if (referencePoint.equalsFuzzy(extensionLine1Start)) {
        extensionLine1Start = targetPoint;
        autoTextPos = true;
        ret = true;
    }
    else if (referencePoint.equalsFuzzy(extensionLine2Start)) {
        extensionLine2Start = targetPoint;
        autoTextPos = true;
        ret = true;
    }

    if (!ret) {
        ret = RDimAngularData::moveReferencePoint(referencePoint, targetPoint, modifiers);
    }

    if (ret) {
        update();
    }

    return ret;
}

bool RDimAngular2LData::move(const RVector& offset) {
    RDimAngularData::move(offset);
    extensionLine1Start.move(offset);
    extensionLine1End.move(offset);
    extensionLine2Start.move(offset);
    dimArcPosition.move(offset);
    update();
    return true;
}

bool RDimAngular2LData::rotate(double rotation, const RVector& center) {
    RDimAngularData::rotate(rotation, center);
    extensionLine1Start.rotate(rotation, center);
    extensionLine1End.rotate(rotation, center);
    extensionLine2Start.rotate(rotation, center);
    dimArcPosition.rotate(rotation, center);
    update();
    return true;
}

bool RDimAngular2LData::scale(const RVector& scaleFactors, const RVector& center) {
    RDimAngularData::scale(scaleFactors, center);
    extensionLine1Start.scale(scaleFactors, center);
    extensionLine1End.scale(scaleFactors, center);
    extensionLine2Start.scale(scaleFactors, center);
    dimArcPosition.scale(scaleFactors, center);
    update();
    return true;
}

bool RDimAngular2LData::mirror(const RLine& axis) {
    RDimAngularData::mirror(axis);
    extensionLine1Start.mirror(axis);
    extensionLine1End.mirror(axis);
    extensionLine2Start.mirror(axis);
    dimArcPosition.mirror(axis);
    update();
    return true;
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
bool RDimAngular2LData::getAngles(double& ang1, double& ang2, bool& reversed,
                              RVector& p1, RVector& p2) const {

    bool done = false;

    RVector center = getCenter();
    double ang = center.getAngleTo(dimArcPosition);

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
RVector RDimAngular2LData::getCenter() const {
    RLine l1(extensionLine1End, extensionLine1Start);
    RLine l2(extensionLine2Start, definitionPoint);
    QList<RVector> vs = l1.getIntersectionPoints(l2, false);

    if (vs.isEmpty()) {
        return RVector::invalid;
    }

    return vs.at(0);
}
