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
#include "RToleranceData.h"
#include "RUnit.h"

RToleranceData::RToleranceData()
    :
      dimScaleOverride(0.0),
      dimToleranceBlockId(REntity::INVALID_ID) {
}

RToleranceData::RToleranceData(RDocument* document, const RToleranceData& data)
    : REntityData(document) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

RToleranceData::RToleranceData(const RPolyline& polyline, bool arrowHead)
    : dimScaleOverride(1.0), dimToleranceBlockId(REntity::INVALID_ID) {

}

double RToleranceData::getDimtxt() const {
    double dimtxt = 2.5;

    if (document!=NULL) {
        dimtxt = document->getKnownVariable(RS::DIMTXT, dimtxt).toDouble();
    }
    else {
        qWarning() << "RDimensionData::getDimtxt: no document";
    }

    return dimtxt * getDimScale();
}


void RToleranceData::setDimScaleOverride(double v) {
    dimScaleOverride = v;
}

double RToleranceData::getDimScale(bool fromDocument) const {
    double ret = dimScaleOverride;

    if (document!=NULL && fromDocument && RMath::fuzzyCompare(ret, 0.0)) {
        ret = document->getKnownVariable(RS::DIMSCALE, 1.0).toDouble();
    }

    return ret;
}

void RToleranceData::scaleVisualProperties(double scaleFactor) {
    if (dimScaleOverride>RS::PointTolerance) {
        setDimScaleOverride(dimScaleOverride * scaleFactor);
    }
    else {
        double s = getDimScale();
        setDimScaleOverride(scaleFactor * s);
    }
}

QList<RVector> RToleranceData::getCorners() const {
    QList<RVector> ret;

    if (!divisions.isEmpty()) {
        double dimtxt = getDimtxt();

        QList<RVector> points;
        if (!divisions.last().isEmpty()) {
            points.append(RVector(0, -dimtxt));
            points.append(RVector(0, dimtxt));
            points.append(RVector(divisions.last().last(), -dimtxt));
            points.append(RVector(divisions.last().last(), dimtxt));
        }

        for (int i=0; i<points.length(); i++) {
            RVector p = points[i];
            p.rotate(direction.getAngle(), RVector(0,0));
            p.move(location);

            ret.append(p);
        }
    }

    return ret;
}

QList<RRefPoint> RToleranceData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    QList<RRefPoint> ret;

    ret.append(RRefPoint(location));

    if (!divisions.isEmpty()) {
        QList<RVector> corners = getCorners();

        for (int i=0; i<corners.length(); i++) {
            ret.append(RRefPoint(corners[i]));
        }
    }

    return ret;
}

bool RToleranceData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    Q_UNUSED(modifiers)

    bool ret = false;

    if (referencePoint.equalsFuzzy(location)) {
        location = targetPoint;
        ret = true;
        update();
    }

    QList<RVector> corners = getCorners();
    for (int i=0; i<corners.length(); i++) {
        if (referencePoint.equalsFuzzy(corners[i])) {
            location += targetPoint-corners[i];
            ret = true;
            update();
        }
    }

    return ret;
}

bool RToleranceData::move(const RVector& offset) {
    location.move(offset);
    update();
    return true;
}

bool RToleranceData::rotate(double rotation, const RVector& center) {
    location.rotate(rotation, center);
    direction.rotate(rotation);
    update();
    return true;
}

bool RToleranceData::scale(const RVector& scaleFactors, const RVector& center) {
    location.scale(scaleFactors, center);
    update();
    return true;
}

bool RToleranceData::mirror(const RLine& axis) {
    RVector p = location + direction;
    p.mirror(axis);

    location.mirror(axis);

    direction = p-location;

    update();
    return true;
}

bool RToleranceData::flipHorizontal() {
    return mirror(RLine(RVector(0,0), RVector(0,1)));
}

bool RToleranceData::flipVertical() {
    return mirror(RLine(RVector(0,0), RVector(1,0)));
}

QList<QSharedPointer<RShape> > RToleranceData::getShapes(const RBox& queryBox, bool ignoreComplex, bool segment) const {
    Q_UNUSED(queryBox)
    //Q_UNUSED(ignoreComplex)
    Q_UNUSED(segment)

    QList<QSharedPointer<RShape> > ret;

    QList<RTextData> labels = getTextLabels();
    if (!ignoreComplex) {
        for (int i=0; i<labels.length(); i++) {
            ret.append(labels[i].getShapes(queryBox, ignoreComplex, segment));
        }
    }

    QList<RLine> lines = getFrame();
    for (int i=0; i<lines.length(); i++) {
        ret.append(QSharedPointer<RShape>(new RLine(lines[i])));
    }

    return ret;
}

void RToleranceData::update() const {
    REntityData::update();
}

QList<RTextData> RToleranceData::getTextLabels() const {
    QList<RTextData> ret;

    QStringList subs = text.split("%%v", QString::SkipEmptyParts);

    double dimtxt = getDimtxt();
    //RVector cursor = location + RVector(dimtxt/2.0, 0);
    double cursor = dimtxt/2.0;

    divisions.clear();
    divisions.append(QList<double>());
    divisions[0].append(0);

    // render text strings with distance of h:
    for (int i=0; i<subs.length(); i++) {
        QString sub = subs[i];

        RTextData textData(RVector(cursor, 0),
                     RVector(cursor, 0),
                     dimtxt,
                     100.0,
                     RS::VAlignMiddle,
                     RS::HAlignLeft,
                     RS::LeftToRight,
                     RS::AtLeast,
                     1.0,
                     sub,
                     "Arial",
                     false,
                     false,
                     0,
                     false);

        cursor += textData.getBoundingBox().getWidth();
        cursor += dimtxt;
        divisions[0].append(cursor - dimtxt/2);

        textData.rotate(direction.getAngle(), RVector(0,0));
        textData.move(location);
        ret.append(textData);
    }

    return ret;
}

QList<RLine> RToleranceData::getFrame() const {
    QList<RLine> ret;

    double dimtxt = getDimtxt();

    for (int i=0; i<divisions.length(); i++) {
        for (int k=0; k<divisions[i].length(); k++) {
            double division = divisions[i][k];
            RLine line(division, -dimtxt, division, dimtxt);

            line.rotate(direction.getAngle());
            line.move(location);
            ret.append(line);
        }

        // top / bottom:
        {
            RLine line(divisions[i].first(), dimtxt, divisions[i].last(), dimtxt);
            line.rotate(direction.getAngle());
            line.move(location);
            ret.append(line);
        }

        {
            RLine line(divisions[i].first(), -dimtxt, divisions[i].last(), -dimtxt);
            line.rotate(direction.getAngle());
            line.move(location);
            ret.append(line);
        }
    }

    return ret;
}
