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
#include "RDimensionData.h"
#include "RUnit.h"



RDimensionData::RDimensionData(RDocument* document) :
    REntityData(document),
    textPositionCenter(RVector::invalid),
    textPositionSide(RVector::invalid),
    valign(RS::VAlignMiddle),
    halign(RS::HAlignMid),
    lineSpacingStyle(RS::Exact),
    lineSpacingFactor(1.0),
    defaultAngle(RNANDOUBLE),
    textAngle(0.0),
    linearFactor(1.0),
    dimScaleOverride(0.0),
    arrow1Flipped(false),
    arrow2Flipped(false),
    extLineFix(false),
    extLineFixLength(0.0),
    dirty(true),
    dimLineLength(0.0),
    arrow1Pos(RVector::invalid),
    arrow2Pos(RVector::invalid),
    autoTextPos(true) {

}

RDimensionData::RDimensionData(RDocument* document, const RDimensionData& data)
    : REntityData(document) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

/**
 * \param definitionPoint Definition point.
 * \param textPosition Middle point of dimension text.
 * \param valign Vertical alignment.
 * \param halign Horizontal alignment.
 * \param lineSpacingStyle Line spacing style.
 * \param lineSpacingFactor Line spacing factor.
 * \param text Text string entered explicitly by user or null
 *         or "<>" for the actual measurement or " " (one blank space).
 *         for supressing the text.
 * \param style Dimension style name.
 * \param angle Rotation angle of dimension text away from
 *         default orientation.
 */
RDimensionData::RDimensionData(const RVector& definitionPoint,
                               const RVector& textPosition,
                               RS::VAlign valign,
                               RS::HAlign halign,
                               RS::TextLineSpacingStyle lineSpacingStyle,
                               double lineSpacingFactor,
                               const QString& text,
                               const QString& style,
                               double angle)
    : definitionPoint(definitionPoint),
      textPositionCenter(textPosition),
      textPositionSide(RVector::invalid),
      valign(valign),
      halign(halign),
      lineSpacingStyle(lineSpacingStyle),
      lineSpacingFactor(lineSpacingFactor),
      text(text),
      fontName(style),
      defaultAngle(RNANDOUBLE),
      textAngle(angle),
      linearFactor(1.0),
      dimScaleOverride(0.0),
      arrow1Flipped(false),
      arrow2Flipped(false),
      extLineFix(false),
      extLineFixLength(0.0),
      dirty(true),
      dimLineLength(0.0),
      arrow1Pos(RVector::invalid),
      arrow2Pos(RVector::invalid),
      autoTextPos(true) {

}

RBox RDimensionData::getBoundingBox(bool ignoreEmpty) const {
    if (dirty || !boundingBox.isValid()) {
        boundingBox = REntityData::getBoundingBox(ignoreEmpty);
        getTextData();
        boundingBox.growToInclude(textData.getBoundingBox(ignoreEmpty));
        dirty = false;
    }

    return boundingBox;
}

RVector RDimensionData::getPointOnEntity() const {
    QList<QSharedPointer<RShape> > shapes = getShapes();
    if (shapes.isEmpty()) {
        return RVector::invalid;
    }

    return shapes.first()->getStartPoint();
}

bool RDimensionData::isValid() const {
    return REntityData::isValid() && definitionPoint.isValid();
}

bool RDimensionData::isSane() const {
    return REntityData::isSane() && definitionPoint.isSane();
}

void RDimensionData::adjustExtensionLineFixLength(RLine& extLine1, RLine& extLine2, bool addDimExe) const {
    // extension lines with fixed length:
    if (isExtLineFix()) {
        double extLineLen = getExtLineFixLength();
        if (RMath::fuzzyCompare(extLineLen, 0.0)) {
            // value of 0 for extension line fixed length means fixed length is off:
            return;
        }

        if (addDimExe) {
            double dimexe = getDimexe();
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

bool RDimensionData::hasSpaceForArrows() const {
    return dimLineLength >= getDimasz()*2.5;
}

double RDimensionData::getDistanceTo(const RVector& point, bool limited, double range, bool draft, double strictRange) const {
    double ret1 = REntityData::getDistanceTo(point, limited, range, draft, strictRange);
    getTextData();
    double ret2 = textData.getDistanceTo(point, limited, range, draft, strictRange);
    if (RMath::isNaN(ret2)) {
        return ret1;
    }
    return qMin(ret1, ret2);
}

bool RDimensionData::intersectsWith(const RShape& shape) const {
    if (REntityData::intersectsWith(shape)) {
        return true;
    }
    getTextData();
    if(textData.intersectsWith(shape)) {
        return true;
    }
    return false;
}

QList<RRefPoint> RDimensionData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    QList<RRefPoint> ret;

    ret.append(definitionPoint);
    ret.append(getTextPosition());

    if (arrow1Pos.isValid()) {
        ret.append(RRefPoint(arrow1Pos, RRefPoint::Arrow));
    }
    if (arrow2Pos.isValid()) {
        ret.append(RRefPoint(arrow2Pos, RRefPoint::Arrow));
    }

    return ret;
}

bool RDimensionData::clickReferencePoint(const RVector& referencePoint) {
    if (referencePoint.equalsFuzzy(arrow1Pos)) {
        arrow1Flipped = arrow2Flipped = !arrow1Flipped;
        update();
        return true;
    }
    if (referencePoint.equalsFuzzy(arrow2Pos)) {
        arrow1Flipped = arrow2Flipped = !arrow2Flipped;
        update();
        return true;
    }
    return false;
}

bool RDimensionData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    Q_UNUSED(modifiers)

    if (referencePoint.equalsFuzzy(definitionPoint)) {
        definitionPoint = targetPoint;
        autoTextPos = true;
        update();
        return true;
    }
    if (textPositionSide.isValid()) {
        if (referencePoint.equalsFuzzy(textPositionSide)) {
            textPositionCenter = targetPoint;
            textPositionSide = RVector::invalid;
            autoTextPos = false;
            update();
            return true;
        }
    }
    if (referencePoint.equalsFuzzy(textPositionCenter)) {
        textPositionCenter = targetPoint;
        autoTextPos = false;
        update();
        return true;
    }

    return false;
}

bool RDimensionData::move(const RVector& offset) {
    definitionPoint.move(offset);
    textPositionCenter.move(offset);
    if (textPositionSide.isValid()) {
        textPositionSide.move(offset);
    }
    update();
    return true;
}

bool RDimensionData::rotate(double rotation, const RVector& center) {
    definitionPoint.rotate(rotation, center);
    textPositionCenter.rotate(rotation, center);
    if (textPositionSide.isValid()) {
        textPositionSide.rotate(rotation, center);
    }
    textAngle = RMath::getNormalizedAngle(textAngle+rotation);
    update();
    return true;
}

bool RDimensionData::scale(const RVector& scaleFactors, const RVector& center) {
    definitionPoint.scale(scaleFactors, center);
    textPositionCenter.scale(scaleFactors, center);
    if (textPositionSide.isValid()) {
        textPositionSide.scale(scaleFactors, center);
    }
    update();
    return true;
}

void RDimensionData::scaleVisualProperties(double scaleFactor) {
    if (dimScaleOverride>RS::PointTolerance) {
        setDimScale(dimScaleOverride * scaleFactor);
    }
    else {
        double s = getDimScale();
        setDimScale(scaleFactor * s);
    }

    extLineFixLength *= scaleFactor;

    if (!RMath::fuzzyCompare(scaleFactor, 0.0) && !RMath::fuzzyCompare(scaleFactor, 1.0)) {
        setLinearFactor(linearFactor / scaleFactor);
    }
}

bool RDimensionData::mirror(const RLine& axis) {
    definitionPoint.mirror(axis);
    textPositionCenter.mirror(axis);
    if (textPositionSide.isValid()) {
        textPositionSide.mirror(axis);
    }
    update();
    return true;
}

double RDimensionData::getDimScale(bool fromDocument) const {
    double ret = dimScaleOverride;

    // dimScale is 0.0 (not set): use dimScale of document
    if (fromDocument && document!=NULL && RMath::fuzzyCompare(ret, 0.0)) {
        ret = document->getKnownVariable(RS::DIMSCALE, 1.0).toDouble();
    }

    return ret;
}

double RDimensionData::getDimexo() const {
    double dimexo = 0.625;

    if (document!=NULL) {
        dimexo = document->getKnownVariable(RS::DIMEXO, dimexo).toDouble();
    }
    else {
        qWarning() << "RDimensionData::getDimexo: no document";
    }

    return dimexo * getDimScale();
}

double RDimensionData::getDimexe() const {
    double dimexe = 1.25;

    if (document!=NULL) {
        dimexe = document->getKnownVariable(RS::DIMEXE, dimexe).toDouble();
    }
    else {
        qWarning() << "RDimensionData::getDimexe: no document";
    }

    return dimexe * getDimScale();
}

double RDimensionData::getDimasz() const {
    double dimasz = 2.5;

    if (document!=NULL) {
        dimasz = document->getKnownVariable(RS::DIMASZ, dimasz).toDouble();
    }
    else {
        qWarning() << "RDimensionData::getDimasz: no document";
    }

    return dimasz * getDimScale();
}

double RDimensionData::getDimgap() const {
    double dimgap = 0.625;

    if (document!=NULL) {
        dimgap = document->getKnownVariable(RS::DIMGAP, dimgap).toDouble();
    }
    else {
        qWarning() << "RDimensionData::getDimgap: no document";
    }

    return dimgap * getDimScale();
}

double RDimensionData::getDimtxt() const {
    double dimtxt = 2.5;

    if (document!=NULL) {
        dimtxt = document->getKnownVariable(RS::DIMTXT, dimtxt).toDouble();
    }
    else {
        qWarning() << "RDimensionData::getDimtxt: no document";
    }

    return dimtxt * getDimScale();
}

bool RDimensionData::useArchTick() const {
    bool ret = false;

    if (document!=NULL) {
        ret = document->getKnownVariable(RS::DIMBLK, "").toString().toLower()=="archtick" ||
              document->getKnownVariable(RS::DIMTSZ, 0.0).toDouble() > RS::PointTolerance;
    }
    else {
        qWarning() << "RDimensionData::useArchTick: no document";
    }

    return ret;
}

bool RDimensionData::hasCustomTextPosition() const {
    return !autoTextPos;
}

void RDimensionData::setCustomTextPosition(bool on) {
    autoTextPos = !on;
}

/**
 * Creates a dimensioning line (line with one, two or no arrows).
 */
QList<QSharedPointer<RShape> > RDimensionData::getDimensionLineShapes(
    const RVector& p1, const RVector& p2,
    bool arrow1, bool arrow2) const {

    QList<QSharedPointer<RShape> > ret;

    // text height (DIMTXT)
    double dimtxt = getDimtxt();
    // text distance to line (DIMGAP)
    double dimgap = getDimgap();
    // arrow size:
    double dimasz = getDimasz();
    bool archTick = useArchTick();

    // length of dimension line:
    dimLineLength = p1.getDistanceTo(p2);

    // do we have to put the arrows outside of the line?
    bool outsideArrow1 = !hasSpaceForArrows();
    bool outsideArrow2 = outsideArrow1;

    // force flipping arrows (against logic above):
    if (isArrow1Flipped()) {
        outsideArrow1 = !outsideArrow1;
    }
    if (isArrow2Flipped()) {
        outsideArrow2 = !outsideArrow2;
    }

    // arrow angles:
    double arrowAngle1, arrowAngle2;

    // Create dimension line:
    RLine dimensionLine(p1, p2);

    if (outsideArrow1==false) {
        arrowAngle1 = dimensionLine.getDirection2();
    }
    else {
        arrowAngle1 = dimensionLine.getDirection1();
    }

    if (outsideArrow2==false) {
        arrowAngle2 = dimensionLine.getDirection1();
    }
    else {
        arrowAngle2 = dimensionLine.getDirection2();
    }

    // extend dimension line outside arrows
    RVector dir;
    dir.setPolar(getDimasz()*2, dimensionLine.getDirection1());
    if (outsideArrow1) {
        dimensionLine.setStartPoint(p1 - dir);
    }
    if (outsideArrow2) {
        dimensionLine.setEndPoint(p2 + dir);
    }

    ret.append(QSharedPointer<RShape>(new RLine(dimensionLine)));

    arrow1Pos = RVector::invalid;
    if (arrow1) {
        QList<QSharedPointer<RShape> > arrow = getArrow(p1, arrowAngle1);
        ret.append(arrow);
        if (!archTick) {
            arrow1Pos = p1 + RVector::createPolar(dimasz, arrowAngle1 + M_PI);
        }
    }

    arrow2Pos = RVector::invalid;
    if (arrow2) {
        QList<QSharedPointer<RShape> > arrow = getArrow(p2, arrowAngle2);
        ret.append(arrow);
        if (!archTick) {
            arrow2Pos = p2 + RVector::createPolar(dimasz, arrowAngle2 + M_PI);
        }
    }

    double dimAngle1 = dimensionLine.getDirection1();
    bool corrected=false;
    defaultAngle = RMath::makeAngleReadable(dimAngle1, true, &corrected);

    if (autoTextPos) {
        RVector newTextPos = dimensionLine.getMiddlePoint();
        RVector distV;

        // rotate text so it's readable from the bottom or right (ISO)
        // quadrant 1 & 4
        if (corrected) {
            distV.setPolar(dimgap + dimtxt/2.0, dimAngle1-M_PI/2.0);
        } else {
            distV.setPolar(dimgap + dimtxt/2.0, dimAngle1+M_PI/2.0);
        }

        // move text away from dimension line:
        if (!text.contains("\\X")) {
            newTextPos+=distV;
        }

        textPositionCenter = newTextPos;
    }

    return ret;
}

QList<QSharedPointer<RShape> > RDimensionData::getArrow(
    const RVector& position, double direction) const {

    QList<QSharedPointer<RShape> > ret;
    double dimasz = getDimasz();

    // architecture tick:
    if (useArchTick()) {
        RVector p1(dimasz/2, dimasz/2);

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

/**
 * \return Text data of the text label.
 */
RTextData& RDimensionData::getTextData() const {
    if (dirty || textData.isDirty()) {
        updateTextData();
    }

    return textData;
}

/**
 * Initializes the text data of the text label of this dimension.
 * The text data is created at 0/0 at an angle or 0. Moving the
 * label to the right position at the right angle is up to the
 * particular dimension implementation.
 */
void RDimensionData::initTextData() const {
    double dimtxt = getDimtxt();

    QString label = getMeasurement();

    // TODO: fontName property takes precedence

    textData = RTextData(RVector(0,0),    // position
                         RVector(0,0),    // alignment point
                         dimtxt,              // text height
                         0.0,
                         RS::VAlignMiddle, RS::HAlignCenter,
                         RS::LeftToRight,
                         RS::Exact, 1.0,
                         label,
                         //fontName,
                         (document==NULL || document->getDimensionFont().isEmpty()) ? "Standard" : document->getDimensionFont(),
                         false, false,
                         0.0,
                         false           // not simple (diameter signs, stacked text, ...)
                         );

    textData.setDocument(document);
    textData.setLayerId(getLayerId());
    textData.setBlockId(getBlockId());
    textData.setColor(getColor());
    textData.setLineweight(getLineweight());
    textData.setSelected(isSelected());
    textData.setDimensionLabel(true);

    // override text color from dimension settings:
    QVariant v = document->getKnownVariable(RS::DIMCLRT, RColor(RColor::ByBlock));
    RColor textColor = v.value<RColor>();
    if (textColor!=RColor::ByBlock) {
        textData.setColor(textColor);
    }

    //qDebug() << "label color: " << textData.getColor();
    //qDebug() << "textData: " << textData;

    dirty = true;
}

void RDimensionData::update() const {
    dirty = true;
    textData.update();
    boundingBox = RBox();
    if (!autoUpdatesBlocked) {
        //qDebug() << "clear dim block name";
        dimBlockName = "";
    }
}

QString RDimensionData::getMeasurement(bool resolveAutoMeasurement) const {
    // normal auto generated label without tolerance:
    if (text.isEmpty() && upperTolerance.isEmpty() && lowerTolerance.isEmpty()) {
        if (resolveAutoMeasurement) {
            return getAutoLabel();
        }
        else {
            return "";
        }
    }

    // a single dot means no text:
    if (text=="." && upperTolerance.isEmpty() && lowerTolerance.isEmpty()) {
        if (resolveAutoMeasurement) {
            return "";
        }
        else {
            return ".";
        }
    }

    QString alignment = "";
    QString tolerance = "";

    if (!upperTolerance.isEmpty() || !lowerTolerance.isEmpty()) {
        alignment = "\\A1;";
        tolerance = "\\S" + upperTolerance + "^" + lowerTolerance + ";";
    }

    QString measurement;
    if (resolveAutoMeasurement) {
        measurement = getAutoLabel();
    }
    else {
        measurement = "<>";
    }

    if (text.isEmpty()) {
        return alignment + measurement + tolerance;
    }
    else {
        QString main = text;
        main.replace("<>", measurement);
        return alignment + main + tolerance;
    }
}

QString RDimensionData::formatLabel(double distance) const {
    QString ret;

    if (document!=NULL) {
        ret = RUnit::formatLinear(distance, document->getUnit(),
            document->getLinearFormat(), document->getLinearPrecision(),
            false,
            document->showLeadingZeroes(), document->showTrailingZeroes(),
            false,
            document->getDecimalSeparator());
    }
    else {
        ret = QString("%1").arg(distance);
    }

    return ret;
}

QString RDimensionData::formatAngleLabel(double angle) const {
    QString ret;

    if (document!=NULL) {
        ret = RUnit::formatAngle(angle,
                                 document->getAngleFormat(), document->getAnglePrecision(),
                                 document->showLeadingZeroesAngle(), document->showTrailingZeroesAngle(),
                                 document->getDecimalSeparator());
    }
    else {
        ret = QString("%1").arg(angle);
    }

    return ret;
}

void RDimensionData::updateTextData() const {
    initTextData();
    if (RMath::isNaN(defaultAngle)) {
        // updates default angle:
        getShapes();
    }
    textData.rotate(defaultAngle, RVector(0,0));
    textData.move(getTextPosition());
}

bool RDimensionData::hasDimensionBlockReference() const {
    QString dimBlockName = getDimBlockName();
    if (dimBlockName.isEmpty()) {
        return false;
    }

    const RDocument* doc = getDocument();
    if (doc==NULL) {
        return false;
    }

    RBlock::Id dimBlockId = doc->getBlockId(dimBlockName);

    // check if block is empty (ignore):
    if (!doc->hasBlockEntities(dimBlockId)) {
        return false;
    }

    return true;
}

QSharedPointer<RBlockReferenceEntity> RDimensionData::getDimensionBlockReference() const {
    QString dimBlockName = getDimBlockName();
    if (dimBlockName.isEmpty()) {
        return QSharedPointer<RBlockReferenceEntity>();
    }

    const RDocument* doc = getDocument();
    if (doc==NULL) {
        return QSharedPointer<RBlockReferenceEntity>();
    }

    RBlock::Id dimBlockId = doc->getBlockId(dimBlockName);

    // check if block is empty (ignore):
    if (!doc->hasBlockEntities(dimBlockId)) {
        return QSharedPointer<RBlockReferenceEntity>();
    }

    // TODO: ignore block if dimension entity is valid (i.e. only use block if we cannot recompute (?))

    RBlockReferenceEntity* dimBlockReference = new RBlockReferenceEntity((RDocument*)doc, RBlockReferenceData(dimBlockId, RVector(0,0), RVector(1,1), 0.0)/*, getId()*/);
    dimBlockReference->copyAttributesFrom(*this, true);
    //e.exportEntity(*dimBlockReference, preview, false, forceSelected);
    //delete dimBlockReference;
    return QSharedPointer<RBlockReferenceEntity>(dimBlockReference);
}
