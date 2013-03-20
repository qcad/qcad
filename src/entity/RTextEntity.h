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

#ifndef RTEXTENTITY_H
#define RTEXTENTITY_H

#include "REntity.h"
#include "RTextData.h"

class RDocument;
class RExporter;

/**
 * Text entity.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class RTextEntity: public REntity {

    Q_DECLARE_TR_FUNCTIONS(RTextEntity)

public:
    static RPropertyTypeId PropertyCustom;
    static RPropertyTypeId PropertyHandle;
    static RPropertyTypeId PropertyType;
    static RPropertyTypeId PropertyBlock;
    static RPropertyTypeId PropertyLayer;
    static RPropertyTypeId PropertyLinetype;
    static RPropertyTypeId PropertyLineweight;
    static RPropertyTypeId PropertyColor;
    static RPropertyTypeId PropertyDrawOrder;

    static RPropertyTypeId PropertySimple;
    static RPropertyTypeId PropertyPositionX;
    static RPropertyTypeId PropertyPositionY;
    static RPropertyTypeId PropertyPositionZ;
    static RPropertyTypeId PropertyText;
    static RPropertyTypeId PropertyFontName;
    static RPropertyTypeId PropertyHeight;
    static RPropertyTypeId PropertyAngle;
    static RPropertyTypeId PropertyBold;
    static RPropertyTypeId PropertyItalic;
    static RPropertyTypeId PropertyLineSpacingFactor;
    static RPropertyTypeId PropertyHAlign;
    static RPropertyTypeId PropertyVAlign;

public:
    RTextEntity(RDocument* document, const RTextData& data,
        RObject::Id objectId = RObject::INVALID_ID);
    virtual ~RTextEntity();

    static void init();

    virtual RTextEntity* clone() const {
        return new RTextEntity(*this);
    }

    virtual RS::EntityType getType() const {
        return RS::EntityText;
    }

    bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value);
    QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId propertyTypeId,
            bool humanReadable = false, bool noAttributes = false);

    virtual void exportEntity(RExporter& e, bool preview=false) const;

    QList<RPainterPath> getPainterPaths(bool draft = false) const {
        return data.getPainterPaths(draft);
    }

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX) const {
        return data.getShapes(queryBox);
    }

    virtual QList<QSharedPointer<RShape> > getExploded() const {
        return data.getExploded();
    }

    virtual RTextData& getTextData() {
        return data;
    }

    virtual RTextData& getData() {
        return data;
    }

    void setData(RTextData& d) {
        data = d;
    }

    virtual const RTextData& getData() const {
        return data;
    }

    RVector getPosition() const {
        return data.getPosition();
    }

    RVector getAlignmentPoint() const {
        return data.getAlignmentPoint();
    }

    double getTextHeight() const {
        return data.getTextHeight();
    }

    double getTextWidth() const {
        return data.getTextWidth();
    }

    double getWidth() const {
        return data.getWidth();
    }
    double getHeight() const {
        return data.getHeight();
    }

    RS::VAlign getVAlign() const {
        return data.getVAlign();
    }

    RS::HAlign getHAlign() const {
        return data.getHAlign();
    }

    QString getFontName() const {
        return data.getFontName();
    }

    void setFontName(const QString& fontName) {
        data.setFontName(fontName);
    }

    QString getEscapedText() const {
        return data.getEscapedText();
    }

    //QString getHtmlText() const {
    //    return data.getHtmlText();
    //}

    QString getPlainText() const {
        return data.getPlainText();
    }

    void setText(const QString& text) {
        data.setText(text);
    }

    bool isSimple() const {
        return data.isSimple();
    }

protected:
    virtual void print(QDebug dbg) const;

protected:
    RTextData data;
};

Q_DECLARE_METATYPE(RTextEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RTextEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RTextEntity>*)

#endif
