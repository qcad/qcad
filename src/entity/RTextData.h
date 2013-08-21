/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

#ifndef RTEXTDATA_H
#define RTEXTDATA_H

#include "entity_global.h"

#include <QTextLayout>

#include "RDocument.h"
#include "REntityData.h"
#include "RPainterPath.h"
#include "RPainterPathSource.h"
#include "RVector.h"

class QTextDocument;

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a text entity.
 *
 * \scriptable
 * \sharedPointerSupport
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RTextData: public REntityData, public RPainterPathSource {
    friend class RTextEntity;

protected:
    RTextData(RDocument* document, const RTextData& data);

public:
    RTextData();
    RTextData(const RVector& position,
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
    virtual ~RTextData() {}

    virtual RBox getBoundingBox() const;
    double getWidth() const;
    double getHeight() const;

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
        double distance, RS::From from = RS::FromAny, const RBox& queryBox = RDEFAULT_RBOX) const {
        Q_UNUSED(distance);
        Q_UNUSED(from);
        Q_UNUSED(queryBox);

        return QList<RVector>();
    }

    virtual double getDistanceTo(const RVector& point, bool limited = true, double range = 0.0, bool draft = false) const;
    virtual bool intersectsWith(const RShape& shape) const;

    RVector getPosition() const {
        return position;
    }

    void setPosition(const RVector& position) {
        this->position = position;
    }

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

    void setFontName(const QString& fontName) {
        this->fontName = fontName;
    }

    bool isBold() const {
        return bold;
    }

    void setBold(bool on) {
        bold = on;
    }

    bool isItalic() const {
        return italic;
    }

    void setItalic(bool on) {
        italic = on;
    }

    double getTextHeight() const {
        return textHeight;
    }

    void setTextHeight(double h) {
        this->textHeight = h;
    }

    /**
     * Width of the text box used for line wrapping (not supported).
     */
    double getTextWidth() const {
        return textWidth;
    }

    void setTextWidth(double w) {
        this->textWidth = w;
    }

    void setVAlign(RS::VAlign valign) {
        this->verticalAlignment = valign;
    }

    RS::VAlign getVAlign() const {
        return this->verticalAlignment;
    }

    void setHAlign(RS::HAlign halign) {
        this->horizontalAlignment = halign;
    }

    RS::HAlign getHAlign() const {
        return this->horizontalAlignment;
    }

    void setDrawingDirection(RS::TextDrawingDirection drawingDirection) {
        this->drawingDirection = drawingDirection;
    }

    RS::TextDrawingDirection getDrawingDirection() const {
        return drawingDirection;
    }

    void setLineSpacingStyle(RS::TextLineSpacingStyle lineSpacingStyle) {
        this->lineSpacingStyle = lineSpacingStyle;
    }

    RS::TextLineSpacingStyle getLineSpacingStyle() const {
        return lineSpacingStyle;
    }

    void setLineSpacingFactor(double lineSpacingFactor) {
        this->lineSpacingFactor = lineSpacingFactor;
    }

    double getLineSpacingFactor() const {
        return lineSpacingFactor;
    }

    void setAngle(double angle) {
        this->angle = angle;
    }

    double getAngle() const {
        return angle;
    }

    void setSimple(bool on) {
        simple = on;
    }

    bool isSimple() const {
        return simple;
    }

    virtual QList<RVector> getReferencePoints(
        RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, 
        const RVector& targetPoint);

    bool move(const RVector& offset);
    bool rotate(double rotation, const RVector& center);
    bool scale(const RVector& scaleFactors, const RVector& center);
    bool mirror(const RLine& axis);
    bool flipHorizontal();
    bool flipVertical();

    QString getPlainText() const;
    QString getEscapedText(bool escapeUnicode = false) const;
    QFont getMainFont() const;

    virtual void update() const;
    bool isDirty() const;

    virtual QList<RPainterPath> getPainterPaths(bool draft = false) const;
    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX) const;
    virtual QList<QSharedPointer<RShape> > getExploded() const;

    virtual QSharedPointer<RShape> getClosestShape(const RVector& pos, double range = RNANDOUBLE) const {
        Q_UNUSED(pos);
        Q_UNUSED(range);
        return QSharedPointer<RShape>();
    }

    virtual RVector getClosestPointOnEntity(const RVector& point, double range, bool limited) const;

    static QString toEscapedText(const QTextDocument& textDocument, const RColor& initialColor, double fontHeightFactor=1.0);
    static QString toRichText(const QString& escapedText, const QFont& mainFont, double fontHeightFactor=1.0);

    /**
     * \nonscriptable
     */
    friend QDebug operator<<(QDebug dbg, const RTextData& t);

private:
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
    bool bold;
    bool italic;
    double angle;
    bool simple;

    mutable double height;
    mutable double width;
    mutable RBox boundingBox;
    mutable QList<RPainterPath> painterPaths;
    mutable bool dirty;
    mutable bool gotDraft;
};

Q_DECLARE_METATYPE(RTextData)
Q_DECLARE_METATYPE(RTextData*)
Q_DECLARE_METATYPE(QSharedPointer<RTextData>)
Q_DECLARE_METATYPE(QSharedPointer<RTextData>*)

#endif
