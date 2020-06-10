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

#ifndef RTEXTBASEDDATA_H
#define RTEXTBASEDDATA_H

#include "core_global.h"

#include "RDocument.h"
#include "REntityData.h"
#include "RPainterPath.h"
#include "RPainterPathSource.h"
#include "RVector.h"
#include "RTextLayout.h"
#include "RTextProxy.h"

class QTextDocument;

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a text based entity (text, block attribute, block attribute definition).
 *
 * \scriptable
 * \sharedPointerSupport
 * \copyable
 * \ingroup entity
 */
class QCADCORE_EXPORT RTextBasedData: public REntityData, public RPainterPathSource {
    friend class RTextBasedEntity;

public:
    enum TextFlag {
        NoFlags = 0x000,
        Bold = 0x001,
        Italic = 0x002,
        Simple = 0x004,
        DimensionLabel = 0x008,
        Highlighted = 0x010,
        Backward = 0x020,
        UpsideDown = 0x040
    };
    Q_DECLARE_FLAGS(TextFlags, TextFlag)

protected:
    RTextBasedData(RDocument* document, const RTextBasedData& data);

public:
    RTextBasedData(RDocument* document = NULL);
    RTextBasedData(const RVector& position,
              const RVector& alignmentPoint,
              double textHeight,
              double textWidth,
              RS::VAlign verticalAlignment,
              RS::HAlign horizontalAlignment,
              RS::TextDrawingDirection drawingDirection,
              RS::TextLineSpacingStyle lineSpacingStyle,
              double lineSpacingFactor,
              const QString& text,
              const QString& fontName,
              bool bold,
              bool italic,
              double angle,
              bool simple);
    virtual ~RTextBasedData() {}

    virtual RS::EntityType getType() const {
        return RS::EntityTextBased;
    }

    void setFlag(RTextBasedData::TextFlag flag, bool on = true) {
        if (on) {
            flags |= flag;
        } else {
            flags &= ~flag;
        }
    }
    bool getFlag(RTextBasedData::TextFlag flag) const {
        return (flags & flag) == flag;
    }

    virtual bool isValid() const {
        return !text.isNull();
    }
    virtual bool isSane() const;

    virtual RBox getBoundingBox(bool ignoreEmpty=false) const;
    double getWidth() const;
    double getHeight() const;

    void sync(const RTextBasedData& other);

    virtual RVector getPointOnEntity() const;

    virtual QList<RVector> getEndPoints(const RBox& queryBox = RDEFAULT_RBOX) const {
        Q_UNUSED(queryBox);
        return QList<RVector>();
    }
    virtual QList<RVector> getMiddlePoints(const RBox& queryBox = RDEFAULT_RBOX) const {
        Q_UNUSED(queryBox);
        return QList<RVector>();
    }
    virtual QList<RVector> getCenterPoints(const RBox& queryBox = RDEFAULT_RBOX) const {
        Q_UNUSED(queryBox);
        return QList<RVector>();
    }
    virtual QList<RVector> getPointsWithDistanceToEnd(
        double distance, int from = RS::FromAny, const RBox& queryBox = RDEFAULT_RBOX) const {
        Q_UNUSED(distance);
        Q_UNUSED(from);
        Q_UNUSED(queryBox);

        return QList<RVector>();
    }

    virtual double getDistanceTo(const RVector& point, bool limited = true, double range = 0.0, bool draft = false, double strictRange = RMAXDOUBLE) const;
    virtual bool intersectsWith(const RShape& shape) const;

    /**
     * \return Position of the reference point of the text.
     */
    RVector getPosition() const {
        return position;
    }

    void setPosition(const RVector& position) {
        this->position = position;
    }

    /**
     * \return Alignment point of the reference point of the text.
     * This is usually the same as the position.
     */
    RVector getAlignmentPoint() const {
        return alignmentPoint;
    }

    void setAlignmentPoint(const RVector& alignmentPoint) {
        this->alignmentPoint = alignmentPoint;
    }

    void setText(const QString& text);

    QString getFontName() const {
        return fontName;
    }

    void setFontName(const QString& fontName);

    QString getFontFile() const {
        return fontFile;
    }

    void setFontFile(const QString& fontFile) {
        this->fontFile = fontFile;
    }

    bool isBold() const {
        return getFlag(Bold);
    }

    void setBold(bool on) {
        setFlag(Bold, on);
        update();
    }

    bool isItalic() const {
        return getFlag(Italic);
    }

    void setItalic(bool on) {
        setFlag(Italic, on);
        update();
    }

    double getTextHeight() const {
        return textHeight;
    }

    void setTextHeight(double h) {
        this->textHeight = h;
        update();
    }

    /**
     * Width of the text box used for line wrapping (not supported).
     */
    double getTextWidth() const {
        return textWidth;
    }

    void setTextWidth(double w) {
        this->textWidth = w;
        update();
    }

    void setVAlign(RS::VAlign valign) {
        this->verticalAlignment = valign;
        update();
    }

    RS::VAlign getVAlign() const {
        return this->verticalAlignment;
    }

    void setHAlign(RS::HAlign halign) {
        this->horizontalAlignment = halign;
        update();
    }

    RS::HAlign getHAlign() const {
        return this->horizontalAlignment;
    }

    void setDrawingDirection(RS::TextDrawingDirection drawingDirection) {
        this->drawingDirection = drawingDirection;
        update();
    }

    RS::TextDrawingDirection getDrawingDirection() const {
        return drawingDirection;
    }

    void setLineSpacingStyle(RS::TextLineSpacingStyle lineSpacingStyle) {
        this->lineSpacingStyle = lineSpacingStyle;
        update();
    }

    RS::TextLineSpacingStyle getLineSpacingStyle() const {
        return lineSpacingStyle;
    }

    void setLineSpacingFactor(double lineSpacingFactor) {
        if (lineSpacingFactor<0) {
            return;
        }
        this->lineSpacingFactor = lineSpacingFactor;
        update();
    }

    double getLineSpacingFactor() const {
        return lineSpacingFactor;
    }

    void setAngle(double angle) {
        this->angle = angle;
        update();
    }

    double getAngle() const {
        return angle;
    }

    void setXScale(double xScale) {
        // only positive xScale for MText:
        if (xScale<=0) {
            xScale = 1;
        }
        this->xScale = xScale;
        update();
    }

    double getXScale() const {
        return xScale;
    }

    void setSimple(bool on) {
        setFlag(Simple, on);
        update();
    }

    bool isSimple() const {
        return getFlag(Simple);
    }

    void setBackward(bool on) {
        setFlag(Backward, isSimple() && on);
        update();
    }

    bool isBackward() const {
        return isSimple() && getFlag(Backward);
    }

    void setUpsideDown(bool on) {
        setFlag(UpsideDown, isSimple() && on);
        update();
    }

    bool isUpsideDown() const {
        return isSimple() && getFlag(UpsideDown);
    }

    void setDimensionLabel(bool on) {
        setFlag(DimensionLabel, on);
        update();
    }

    bool isDimensionLabel() const {
        return getFlag(DimensionLabel);
    }

    void setSelected(bool on) {
        REntityData::setSelected(on);
        update();
    }

    void setHighlighted(bool on) {
        setFlag(Highlighted, on);
    }

    bool isHighlighted() const {
        return getFlag(Highlighted);
    }

    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center);
    virtual bool scale(const RVector& scaleFactors, const RVector& center);
    virtual bool mirror(const RLine& axis);
    virtual bool flipHorizontal();
    virtual bool flipVertical();

    virtual QString getText() const {
        return text;
    }
    virtual QString getRenderedText(bool escapeUnicode = false) const;
    virtual QString getPlainText() const;
    virtual QString getEscapedText(bool escapeUnicode = false) const;
    static QString escapeUnicode(const QString& str);
    virtual QFont getMainFont() const;

    virtual void update(bool layout) const;
    virtual void update() const {
        update(true);
    }
    virtual bool isDirty() const;

    virtual QList<RPainterPath> getPainterPaths(bool draft = false, double pixelSizeHint = RDEFAULT_MIN1) const;
    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false) const;
    virtual QList<QSharedPointer<RShape> > getExploded() const;

    virtual QSharedPointer<RShape> getClosestShape(const RVector& pos, double range = RNANDOUBLE, bool ignoreComplex = false) const {
        Q_UNUSED(pos);
        Q_UNUSED(range);
        Q_UNUSED(ignoreComplex)
        return QSharedPointer<RShape>();
    }

    virtual RVector getClosestPointOnEntity(const RVector& point, double range, bool limited) const;

    QList<RTextLayout> getTextLayouts() const;

    QList<RTextBasedData> getSimpleTextBlocks();

//    virtual RTextBasedData getRenderedTextData() const {
//        return *this;
//    }

    static bool hasProxy() {
        return textProxy!=NULL;
    }

    /**
     * \nonscriptable
     */
    static void setTextProxy(RTextProxy* p) {
        if (textProxy!=NULL) {
            delete textProxy;
        }
        textProxy = p;
    }

    /**
     * \nonscriptable
     */
    static RTextProxy* getTextProxy() {
        return textProxy;
    }

    static QString toEscapedText(const QTextDocument& textDocument, const RColor& initialColor, double fontHeightFactor=1.0, bool simpleText = false);
    static QString toRichText(const QString& escapedText, const QFont& mainFont, double fontHeightFactor=1.0);

protected:
    QString text;
    RVector position;
    RVector alignmentPoint;
    double textHeight;
    double textWidth;
    RS::VAlign verticalAlignment;
    RS::HAlign horizontalAlignment;
    RS::TextDrawingDirection drawingDirection;
    RS::TextLineSpacingStyle lineSpacingStyle;
    double lineSpacingFactor;
    QString fontName;
    QString fontFile;
    double angle;
    double xScale;
    TextFlags flags;

    mutable double height;
    mutable double width;
    mutable RBox boundingBox;
    mutable QList<RPainterPath> painterPaths;
    mutable bool dirty;
    mutable bool gotDraft;
    mutable QList<RTextLayout> textLayouts;

private:
    static RTextProxy* textProxy;
};

QCADCORE_EXPORT QDebug operator<<(QDebug dbg, const RTextBasedData& t);

Q_DECLARE_METATYPE(RTextBasedData)
Q_DECLARE_METATYPE(RTextBasedData*)
Q_DECLARE_METATYPE(const RTextBasedData*)
Q_DECLARE_METATYPE(QSharedPointer<RTextBasedData>)
Q_DECLARE_METATYPE(QSharedPointer<RTextBasedData>*)
Q_DECLARE_METATYPE(RTextBasedData::TextFlag)
Q_DECLARE_METATYPE(RTextBasedData::TextFlag*)

#endif
