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
#include "RDimAngular3PData.h"
#include "RUnit.h"

RDimAngular3PData::RDimAngular3PData() {
}

RDimAngular3PData::RDimAngular3PData(RDocument* document, const RDimAngular3PData& data)
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
RDimAngular3PData::RDimAngular3PData(const RDimensionData& dimData,
                                 const RVector& center,
                                 const RVector& extensionLine1End,
                                 const RVector& extensionLine2End)
    : RDimAngularData(dimData),
      center(center),
      extensionLine1End(extensionLine1End),
      extensionLine2End(extensionLine2End) {

}

bool RDimAngular3PData::isValid() const {
    return RDimAngularData::isValid() &&
            center.isValid() &&
            extensionLine1End.isValid() &&
            extensionLine2End.isValid();
}

bool RDimAngular3PData::isSane() const {
    return RDimAngularData::isSane() &&
            center.isSane() &&
            extensionLine1End.isSane() &&
            extensionLine2End.isSane();
}

QList<RRefPoint> RDimAngular3PData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    QList<RRefPoint> ret = RDimAngularData::getReferencePoints(hint);

    ret.append(center);

    return ret;
}

bool RDimAngular3PData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    Q_UNUSED(modifiers)

    bool ret = false;

    if (referencePoint.equalsFuzzy(center)) {
        center = targetPoint;
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

bool RDimAngular3PData::move(const RVector& offset) {
    RDimAngularData::move(offset);
    center.move(offset);
    extensionLine1End.move(offset);
    extensionLine2End.move(offset);
    update();
    return true;
}

bool RDimAngular3PData::rotate(double rotation, const RVector& center) {
    RDimAngularData::rotate(rotation, center);
    this->center.rotate(rotation, center);
    extensionLine1End.rotate(rotation, center);
    extensionLine2End.rotate(rotation, center);
    update();
    return true;
}

bool RDimAngular3PData::scale(const RVector& scaleFactors, const RVector& center) {
    RDimAngularData::scale(scaleFactors, center);
    this->center.scale(scaleFactors, center);
    extensionLine1End.scale(scaleFactors, center);
    extensionLine2End.scale(scaleFactors, center);
    update();
    return true;
}

bool RDimAngular3PData::mirror(const RLine& axis) {
    RDimAngularData::mirror(axis);
    center.mirror(axis);
    extensionLine1End.mirror(axis);
    extensionLine2End.mirror(axis);
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
bool RDimAngular3PData::getAngles(double& ang1, double& ang2, bool& reversed,
                              RVector& p1, RVector& p2) const {

    double ang = center.getAngleTo(definitionPoint);

    //if (center.getDistanceTo(center) < center.getDistanceTo(extensionLine1End)) {
        ang1 = center.getAngleTo(extensionLine1End);
        p1 = extensionLine1End;
//    }
//    else {
//        ang1 = extensionLine1End.getAngleTo(center);
//        p1 = center;
//    }

    //if (center.getDistanceTo(extensionLine2End) < center.getDistanceTo(definitionPoint)) {
        ang2 = center.getAngleTo(extensionLine2End);
        p2 = extensionLine2End;
//    }
//    else {
//        ang2 = definitionPoint.getAngleTo(extensionLine2End);
//        p2 = extensionLine2End;
//    }

    //ang1 = center.getAngleTo(extensionLine1End);
    //ang2 = extensionLine2End.getAngleTo(definitionPoint);
    //p1 = extensionLine1End;
    //p2 = definitionPoint;

    if (RMath::isAngleBetween(ang, ang1, ang2, false)) {
        reversed = false;
    }
    else {
        reversed = true;
    }

    return true;

//    bool done = false;

//    // find out the angles this dimension refers to:
//    for (int f1=0; f1<=1 && !done; ++f1) {
//        ang1 = RMath::getNormalizedAngle(extensionLine1End.getAngleTo(center) + f1*M_PI);
//        if (f1==0) {
//            p1 = center;
//        } else {
//            p1 = extensionLine1End;
//        }
//        for (int f2=0; f2<=1 && !done; ++f2) {
//            ang2 = RMath::getNormalizedAngle(extensionLine2End.getAngleTo(definitionPoint) + f2*M_PI);
//            if (f2==0) {
//                p2 = definitionPoint;
//            } else {
//                p2 = extensionLine2End;
//            }
//            for (int t=0; t<=1 && !done; ++t) {
//                reversed = (bool)t;

//                double angDiff;

//                if (!reversed) {
//                    if (ang2<ang1) {
//                        ang2+=2*M_PI;
//                    }
//                    angDiff = ang2-ang1;
//                } else {
//                    if (ang1<ang2) {
//                        ang1+=2*M_PI;
//                    }
//                    angDiff = ang1-ang2;
//                }

//                ang1 = RMath::getNormalizedAngle(ang1);
//                ang2 = RMath::getNormalizedAngle(ang2);

//                if (RMath::isAngleBetween(ang, ang1, ang2, reversed) && angDiff<=M_PI) {
//                    done = true;
//                    break;
//                }
//            }
//        }
//    }

//    return done;
}
