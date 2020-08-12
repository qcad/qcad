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

#ifndef RTEXTBASEDENTITY_H
#define RTEXTBASEDENTITY_H

#include "core_global.h"

#include "REntity.h"
#include "RTextBasedData.h"

class RDocument;
class RExporter;

/**
 * Text entity.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADCORE_EXPORT RTextBasedEntity: public REntity {

    Q_DECLARE_TR_FUNCTIONS(RTextBasedEntity)

public:
    static RPropertyTypeId PropertyCustom;
    static RPropertyTypeId PropertyHandle;
    static RPropertyTypeId PropertyType;
    static RPropertyTypeId PropertyBlock;
    static RPropertyTypeId PropertyLayer;
    static RPropertyTypeId PropertyLinetype;
    static RPropertyTypeId PropertyLinetypeScale;
    static RPropertyTypeId PropertyLineweight;
    static RPropertyTypeId PropertyColor;
    static RPropertyTypeId PropertyDisplayedColor;
    static RPropertyTypeId PropertyDrawOrder;

    static RPropertyTypeId PropertySimple;
    static RPropertyTypeId PropertyPositionX;
    static RPropertyTypeId PropertyPositionY;
    static RPropertyTypeId PropertyPositionZ;
    static RPropertyTypeId PropertyText;
    static RPropertyTypeId PropertyPlainText;
    static RPropertyTypeId PropertyFontName;
    static RPropertyTypeId PropertyHeight;
    static RPropertyTypeId PropertyAngle;
    static RPropertyTypeId PropertyXScale;
    static RPropertyTypeId PropertyBold;
    static RPropertyTypeId PropertyItalic;
    static RPropertyTypeId PropertyLineSpacingFactor;
    static RPropertyTypeId PropertyHAlign;
    static RPropertyTypeId PropertyVAlign;
    static RPropertyTypeId PropertyBackward;
    static RPropertyTypeId PropertyUpsideDown;

public:
    RTextBasedEntity(RDocument* document);
    virtual ~RTextBasedEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RTextBasedEntity));
    }

    virtual RTextBasedData& getData() = 0;

    virtual const RTextBasedData& getData() const = 0;

    virtual bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

    virtual void exportEntity(RExporter& e, bool preview=false, bool forceSelected=false) const;

    virtual QSharedPointer<REntity> scaleNonUniform(const RVector& scaleFactors, const RVector& center);

    QList<RPainterPath> getPainterPaths(bool draft = false) const {
        return getData().getPainterPaths(draft);
    }

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false) const {
        return getData().getShapes(queryBox, ignoreComplex, segment);
    }

    virtual QList<QSharedPointer<RShape> > getExploded() const {
        return getData().getExploded();
    }

    virtual RTextBasedData& getTextData() {
        return getData();
    }

    bool isBold() const {
        return getData().isBold();
    }

    void setBold(bool on) {
        getData().setBold(on);
    }

    bool isItalic() const {
        return getData().isItalic();
    }

    void setItalic(bool on) {
        getData().setItalic(on);
    }

    bool isBackward() const {
        return getData().isBackward();
    }

    void setBackward(bool on) {
        getData().setBackward(on);
    }

    bool isUpsideDown() const {
        return getData().isUpsideDown();
    }

    void setUpsideDown(bool on) {
        getData().setUpsideDown(on);
    }

    RVector getPosition() const {
        return getData().getPosition();
    }

    void setPosition(const RVector& position) {
        getData().setPosition(position);
    }

    RVector getAlignmentPoint() const {
        return getData().getAlignmentPoint();
    }

    void setAlignmentPoint(const RVector& alignmentPoint) {
        getData().setAlignmentPoint(alignmentPoint);
    }

    double getTextHeight() const {
        return getData().getTextHeight();
    }

    void setTextHeight(double h) {
        getData().setTextHeight(h);
    }

    double getTextWidth() const {
        return getData().getTextWidth();
    }

    double getWidth() const {
        return getData().getWidth();
    }
    double getHeight() const {
        return getData().getHeight();
    }

    RS::VAlign getVAlign() const {
        return getData().getVAlign();
    }

    void setVAlign(RS::VAlign va) {
        getData().setVAlign(va);
    }

    RS::HAlign getHAlign() const {
        return getData().getHAlign();
    }

    void setHAlign(RS::HAlign ha) {
        getData().setHAlign(ha);
    }

    QString getFontName() const {
        return getData().getFontName();
    }

    void setFontName(const QString& fontName) {
        getData().setFontName(fontName);
    }

    QString getFontFile() const {
        return getData().getFontFile();
    }

    void setDrawingDirection(RS::TextDrawingDirection drawingDirection) {
        getData().setDrawingDirection(drawingDirection);
    }

    RS::TextDrawingDirection getDrawingDirection() const {
        return getData().getDrawingDirection();
    }

    void setLineSpacingStyle(RS::TextLineSpacingStyle lineSpacingStyle) {
        getData().setLineSpacingStyle(lineSpacingStyle);
    }

    RS::TextLineSpacingStyle getLineSpacingStyle() const {
        return getData().getLineSpacingStyle();
    }

    void setLineSpacingFactor(double lineSpacingFactor) {
        getData().setLineSpacingFactor(lineSpacingFactor);
    }

    double getLineSpacingFactor() const {
        return getData().getLineSpacingFactor();
    }

    void setAngle(double angle) {
        getData().setAngle(angle);
    }

    double getAngle() const {
        return getData().getAngle();
    }

    void setXScale(double xScale) {
        getData().setXScale(xScale);
    }

    double getXScale() const {
        return getData().getXScale();
    }

    void setSimple(bool on) {
        getData().setSimple(on);
    }

    bool isSimple() const {
        return getData().isSimple();
    }

    QString getEscapedText(bool escapeUnicode = false) const {
        return getData().getEscapedText(escapeUnicode);
    }

    //QString getHtmlText() const {
    //    return getData().getHtmlText();
    //}

    QString getPlainText() const {
        return getData().getPlainText();
    }

    void setText(const QString& text) {
        getData().setText(text);
    }

    void sync(const RTextBasedEntity& other) {
        getData().sync(other.getData());
    }

    QList<RTextBasedData> getSimpleTextBlocks() {
        return getData().getSimpleTextBlocks();
    }

protected:
    virtual void print(QDebug dbg) const;
};

Q_DECLARE_METATYPE(RTextBasedEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RTextBasedEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RTextBasedEntity>*)

#endif
