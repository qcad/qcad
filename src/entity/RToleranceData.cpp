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
#include "RTextData.h"
#include "RToleranceData.h"
#include "RUnit.h"

RToleranceData::RToleranceData()
    :
      //dimScaleOverride(0.0),
      direction(1,0,0),
      dimToleranceBlockId(REntity::INVALID_ID),
      dimscale(-1.0),
      dimtxt(-1.0),
      joinFirstField(false) {
}

RToleranceData::RToleranceData(RDocument* document, const RToleranceData& data)
    : REntityData(document),
      direction(1,0,0) {

    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

//void RToleranceData::setDimScaleOverride(double v) {
//    dimScaleOverride = v;
//}

//double RToleranceData::getDimscale(bool fromDocument) const {
//    double ret = dimScaleOverride;

//    if (document!=NULL && fromDocument && RMath::fuzzyCompare(ret, 0.0)) {
//        ret = document->getKnownVariable(RS::DIMSCALE, 1.0).toDouble();
//    }

//    return ret;
//}

//void RToleranceData::scaleVisualProperties(double scaleFactor) {
//    if (dimScaleOverride>RS::PointTolerance) {
//        setDimScaleOverride(dimScaleOverride * scaleFactor);
//    }
//    else {
//        double s = getDimscale();
//        setDimScaleOverride(scaleFactor * s);
//    }
//}

void RToleranceData::scaleVisualProperties(double scaleFactor) {
    setDimscale(getDimscale() * scaleFactor);
}

QList<RVector> RToleranceData::getCorners() const {
    QList<RVector> ret;

    if (!divisions.isEmpty()) {
        double dimtxtLocal = getDimtxt();

        QList<RVector> points;

        int iLine = 0;
        for (int i=0; i<divisions.length(); i++) {
            if (divisions[i].length()>1) {
//                points.append(RVector(0, -dimtxtLocal - iLine*dimtxtLocal*2));
//                points.append(RVector(0, dimtxtLocal - iLine*dimtxtLocal*2));
//                points.append(RVector(divisions[i].last(), -dimtxtLocal - iLine*dimtxtLocal*2));
//                points.append(RVector(divisions[i].last(), dimtxtLocal - iLine*dimtxtLocal*2));

                //if (iLine==0) {
                    // top row corners:
                    points.append(RVector(0, dimtxtLocal - iLine*dimtxtLocal*2));
                    points.append(RVector(divisions[i].last(), dimtxtLocal - iLine*dimtxtLocal*2));
//                }
//                if (iLine==divisions.length()-1) {
                    // bottom row corners:
                    points.append(RVector(0, -dimtxtLocal - iLine*dimtxtLocal*2));
                    points.append(RVector(divisions[i].last(), -dimtxtLocal - iLine*dimtxtLocal*2));
//                }
            }
            iLine++;
        }

        points = RVector::getUnique(points);

        for (int i=0; i<points.length(); i++) {
            RVector p = points[i];
            p.rotate(direction.getAngle(), RVector(0,0));
            p.move(location);

            ret.append(p);
        }
    }

    return ret;
}

QList<RVector> RToleranceData::getMiddels() const {
    QList<RVector> ret;

    if (!divisions.isEmpty()) {
        double dimtxtLocal = getDimtxt();

        QList<RVector> points;

        int iLine = 0;
        for (int i=0; i<divisions.length(); i++) {
            if (divisions[i].length()>1) {
                // top middle:
                if (iLine==0) {
                    points.append(RVector((0 + divisions[i].last()) / 2.0, dimtxtLocal - iLine*dimtxtLocal*2));
                }

                // bottom middle:
                if (iLine==divisions.length()-1) {
                    points.append(RVector((0 + divisions[i].last()) / 2.0, -dimtxtLocal - iLine*dimtxtLocal*2));
                }

                // front middle of row:
                points.append(RVector(0, -iLine*dimtxtLocal*2));

                // back middle of row:
                points.append(RVector(divisions[i].last(), -iLine*dimtxtLocal*2));
            }
            iLine++;
        }

        points = RVector::getUnique(points);

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

    //ret.append(RRefPoint(location));

    if (!divisions.isEmpty()) {
        QList<RVector> refPoints = getCorners();
        refPoints.append(getMiddels());

        for (int i=0; i<refPoints.length(); i++) {
            ret.append(RRefPoint(refPoints[i]));
        }
    }

    return ret;
}

bool RToleranceData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    Q_UNUSED(modifiers)

    bool ret = false;

//    if (referencePoint.equalsFuzzy(location)) {
//        location = targetPoint;
//        ret = true;
//        update();
//    }

    QList<RVector> refPoints = getCorners();
    refPoints.append(getMiddels());
    for (int i=0; i<refPoints.length(); i++) {
        if (referencePoint.equalsFuzzy(refPoints[i])) {
            location += targetPoint-refPoints[i];
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

QList<QSharedPointer<RShape> > RToleranceData::getShapes(const RBox& queryBox, bool ignoreComplex, bool segment, QList<RObject::Id>* entityIds) const {
    //Q_UNUSED(queryBox)
    //Q_UNUSED(ignoreComplex)
    //Q_UNUSED(segment)

    QList<QSharedPointer<RShape> > ret;

    QList<RTextData> labels = getTextLabels();
    if (!ignoreComplex) {
        for (int i=0; i<labels.length(); i++) {
            ret.append(labels[i].getShapes(queryBox, ignoreComplex, segment, entityIds));
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

QList<QStringList> RToleranceData::getFields() const {
    // create list of string lists with field texts:
    QList<QStringList> ret;

    QStringList lines = text.split("^J");
    for (int k=0; k<lines.length(); k++) {
        QString line = lines[k];
        //qDebug() << "line:" << line;

        QStringList lineFields = line.split("%%v");
        ret.append(lineFields);
    }

    return ret;
}

QList<RTextData> RToleranceData::getTextLabels() const {
    QList<RTextData> ret;

    divisions.clear();

    double dimtxt = getDimtxt();
    //qDebug() << "text:" << text;

    QList<QStringList> fields = getFields();
    joinFirstField = false;

    // find out if we need to join the first fields of the first two lines:
    if (fields.length()>1 && fields[0].length()>0 && fields[1].length()>0) {
        QString field1 = fields[0][0];
        QString field2 = fields[1][0];
        QRegularExpression reg = RS::createRegEpCI("\\\\F[gG][dD][tT];");
        field1.replace(reg, "\\Fgdt;");
        field2.replace(reg, "\\Fgdt;");
        if (!field1.isEmpty()) {
            joinFirstField = (field1==field2);
        }
    }

    double cursorY = 0;
    //QString firstField1;
    //QString firstField2;

    RColor textColor;

    if (document!=NULL) {
        QVariant v = document->getKnownVariable(RS::DIMCLRT, RColor(RColor::ByBlock));
        textColor = v.value<RColor>();
    }

    for (int k=0; k<fields.length(); k++) {
        QStringList fieldsOfLine = fields[k];
        //qDebug() << "fieldsOfLine:" << fieldsOfLine;

        //RVector cursor = location + RVector(dimtxt/2.0, 0);
        double cursorX = dimtxt/2.0;

        divisions.append(QList<double>());
        divisions.last().append(0);

        // render text strings with distance of dimtxt:
        for (int i=0; i<fieldsOfLine.length(); i++) {
            QString field = fieldsOfLine[i];
            //qDebug() << "field:" << field;
            if (field.isEmpty()) {
                continue;
            }

            RTextData textData(RVector(cursorX, cursorY),
                         RVector(cursorX, cursorY),
                         dimtxt,
                         0.0,
                         RS::VAlignMiddle,
                         RS::HAlignLeft,
                         RS::LeftToRight,
                         RS::AtLeast,
                         1.0,
                         field,
                         //"Arial", // TODO
                         (document==NULL || document->getDimensionFont().isEmpty()) ? "Standard" : document->getDimensionFont(),
                         false,
                         false,
                         0,
                         false);

            textData.setDocument(document);
            textData.setLayerId(getLayerId());
            textData.setBlockId(getBlockId());
            textData.setColor(getColor());
            textData.setLineweight(getLineweight());
            textData.setSelected(isSelected());
            textData.setDimensionLabel(true);

            RColor textColor = RColor(RColor::ByBlock);
            QSharedPointer<RDimStyle> dimStyle;
            if (document!=NULL) {
                dimStyle = document->queryDimStyleDirect();
            }
            if (!dimStyle.isNull()) {
                textColor = dimStyle->getColor(RS::DIMCLRT);
            }
            if (textColor!=RColor::ByBlock) {
                textData.setColor(textColor);
            }

            //if (!textColor.isByBlock()) {
                //textData.setColor(textColor);
            //}

//            if (textColor.isByBlock()) {
//                textData.setColor(getColor());
//            }
//            else {
//                textData.setColor(textColor);
//            }

            // move first symbol of first line down if fields are joined:
            if (k==0 && i==0 && joinFirstField) {
                textData.move(RVector(0, -dimtxt));
            }

            //cursorX += textData.getBoundingBox().getWidth();
            cursorX += textData.getWidth();
            cursorX += dimtxt;
            divisions.last().append(cursorX - dimtxt/2);

            if (k==1 && i==0 && joinFirstField) {
                // skip first symbol of second line if fields are joined:
                continue;
            }
            textData.rotate(direction.getAngle(), RVector(0,0));
            textData.move(location);
            ret.append(textData);
        }

        if (!divisions.isEmpty() && divisions.last().length()==1) {
            // remove single division line:
            //divisions.last().clear();
            divisions.removeLast();
        }
        else {
            cursorY -= dimtxt * 2;
        }
    }

    return ret;
}

QList<RLine> RToleranceData::getFrame() const {
    QList<RLine> ret;

    double dimtxt = getDimtxt();
    double offsetY = 0.0;

    for (int i=0; i<divisions.length(); i++) {
        //qDebug() << "divisions:" << divisions[i];

        // never show vertical lines for empty rows:
        if (divisions[i].length()>1) {
            for (int k=0; k<divisions[i].length(); k++) {
                double division = divisions[i][k];
                RLine line(division, -dimtxt + offsetY, division, dimtxt + offsetY);

                line.rotate(direction.getAngle());
                line.move(location);
                ret.append(line);
            }

            {
                // top line of current line:
                double startX = divisions[i].first();
                if (joinFirstField && i==1 && divisions[i].length()>1) {
                    startX = divisions[i][1];
                }
                RLine line(startX, dimtxt + offsetY, divisions[i].last(), dimtxt + offsetY);
                line.rotate(direction.getAngle());
                line.move(location);
                ret.append(line);
            }

            {
                // bottom line of current line:
                double startX = divisions[i].first();
                if (joinFirstField && i==0 && divisions[i].length()>1) {
                    startX = divisions[i][1];
                }
                RLine line(startX, -dimtxt + offsetY, divisions[i].last(), -dimtxt + offsetY);
                line.rotate(direction.getAngle());
                line.move(location);
                ret.append(line);
            }
        }

        if (!divisions[i].isEmpty()) {
            offsetY -= dimtxt*2;
        }
    }

    return ret;
}

RVector RToleranceData::getPointOnEntity() const {
    return location;
}

RVector RToleranceData::getVectorTo(const RVector& point, bool limited, double strictRange) const {
    RBox bbox = getBoundingBox();
    if (bbox.containsPoint(point)) {
        return RVector(0,0);
    }
    return RVector::invalid;
}
