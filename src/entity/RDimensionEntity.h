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

#ifndef RDIMENSIONENTITY_H
#define RDIMENSIONENTITY_H

#include "entity_global.h"

#include "REntity.h"
#include "RDimensionData.h"

class RDocument;
class RExporter;

/**
 * Base class for dimension entity classes.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT RDimensionEntity: public REntity {

    Q_DECLARE_TR_FUNCTIONS(RDimensionEntity)

public:
    static RPropertyTypeId PropertyCustom;
    static RPropertyTypeId PropertyHandle;
    static RPropertyTypeId PropertyProtected;
    static RPropertyTypeId PropertyWorkingSet;
    static RPropertyTypeId PropertyType;
    static RPropertyTypeId PropertyBlock;
    static RPropertyTypeId PropertyLayer;
    static RPropertyTypeId PropertyLinetype;
    static RPropertyTypeId PropertyLinetypeScale;
    static RPropertyTypeId PropertyLineweight;
    static RPropertyTypeId PropertyColor;
    static RPropertyTypeId PropertyDisplayedColor;
    static RPropertyTypeId PropertyDrawOrder;

    static RPropertyTypeId PropertyDefinitionPointX;
    static RPropertyTypeId PropertyDefinitionPointY;
    static RPropertyTypeId PropertyDefinitionPointZ;
    static RPropertyTypeId PropertyMiddleOfTextX;
    static RPropertyTypeId PropertyMiddleOfTextY;
    static RPropertyTypeId PropertyMiddleOfTextZ;
    static RPropertyTypeId PropertyText;
    static RPropertyTypeId PropertyUpperTolerance;
    static RPropertyTypeId PropertyLowerTolerance;

    //static RPropertyTypeId PropertyLinearFactor;
    //static RPropertyTypeId PropertyDimScale;
    static RPropertyTypeId PropertyDimBlockName;
    static RPropertyTypeId PropertyAutoTextPos;
    static RPropertyTypeId PropertyFontName;
    static RPropertyTypeId PropertyTextRotation;
    //static RPropertyTypeId PropertyTextColor;
    static RPropertyTypeId PropertyArrow1Flipped;
    static RPropertyTypeId PropertyArrow2Flipped;

    static RPropertyTypeId PropertyExtLineFix;
    static RPropertyTypeId PropertyExtLineFixLength;
    //static RPropertyTypeId PropertyHeight;
    //static RPropertyTypeId PropertyLineSpacingFactor;
    //static RPropertyTypeId PropertyHAlign;
    //static RPropertyTypeId PropertyVAlign;

    static RPropertyTypeId PropertyAutoLabel;
    static RPropertyTypeId PropertyMeasuredValue;

    static RPropertyTypeId PropertyDimscale;
    static RPropertyTypeId PropertyDimlfac;
    static RPropertyTypeId PropertyDimtxt;
    static RPropertyTypeId PropertyDimgap;
    static RPropertyTypeId PropertyDimasz;
    //static RPropertyTypeId PropertyDimdli;
    static RPropertyTypeId PropertyDimexe;
    static RPropertyTypeId PropertyDimexo;
    static RPropertyTypeId PropertyDimtad;
    static RPropertyTypeId PropertyDimtih;
    static RPropertyTypeId PropertyDimtsz;
    static RPropertyTypeId PropertyDimlunit;
    static RPropertyTypeId PropertyDimdec;
    static RPropertyTypeId PropertyDimdsep;
    static RPropertyTypeId PropertyDimzin;
    static RPropertyTypeId PropertyDimaunit;
    static RPropertyTypeId PropertyDimadec;
    static RPropertyTypeId PropertyDimazin;
    static RPropertyTypeId PropertyArchTick;
    static RPropertyTypeId PropertyDimclrt;

public:
    RDimensionEntity(RDocument* document);
    virtual ~RDimensionEntity();

    static void init();

    static RS::EntityType getRtti() {
        return RS::EntityDimension;
    }

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(RDimensionEntity::getRtti());
    }

    virtual bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

    virtual void exportEntity(RExporter& e, bool preview=false, bool forceSelected=false) const;

    static void renderDimensionText(RExporter& e, const RDocument* doc, RTextData& textData, bool isSelected=false, bool forceSelected=false);

    virtual RDimensionData& getData() = 0;

    virtual const RDimensionData& getData() const = 0;

    void clearStyleOverrides() {
        getData().clearStyleOverrides();
    }

    void setDefinitionPoint(const RVector& p) {
        getData().setDefinitionPoint(p);
    }

    RVector getDefinitionPoint() const {
        return getData().getDefinitionPoint();
    }

    void setText(const QString& t) {
        getData().setText(t);
    }

    QString getText() const {
        return getData().getText();
    }

    QString getMeasurement(bool resolveAutoMeasurement = true) const {
        return getData().getMeasurement(resolveAutoMeasurement);
    }

    RTextData getTextData() const {
        return getData().getTextData();
    }

    void updateBoundingBox(const RBox& b) const {
        getData().updateBoundingBox(b);
    }
    void updateTextPositionCenter(const RVector& p) const {
        getData().updateTextPositionCenter(p);
    }
    void updateTextData(const RTextData& d) const {
        getData().updateTextData(d);
    }
    void updateShapes(const QList<QSharedPointer<RShape> >& s) const {
        getData().updateShapes(s);
    }

    void setTextPosition(const RVector& p) {
        getData().setTextPosition(p);
    }

    RVector getTextPosition() const {
        return getData().getTextPosition();
    }

    void setFontName(const QString& fn) {
        getData().setFontName(fn);
    }

    QString getFontName() const {
        return getData().getFontName();
    }

//    void setTextColor(const QString& tc) {
//        getData().setTextColor(RColor(tc));
//    }

//    RColor getTextColor() const {
//        return getData().getTextColor();
//    }

    bool hasCustomTextPosition() const {
        return getData().hasCustomTextPosition();
    }

    void setCustomTextPosition(bool on) {
        getData().setCustomTextPosition(on);
    }

    RS::TextLineSpacingStyle getLineSpacingStyle() const {
        return getData().getLineSpacingStyle();
    }

    double getLineSpacingFactor() const {
        return getData().getLineSpacingFactor();
    }

    double getTextRotation() const {
        return getData().getTextRotation();
    }

    double getLinearFactor() const {
        return getData().getLinearFactor();
    }

    void setLinearFactor(double f) {
        getData().setLinearFactor(f);
    }

    double getDimscale() const {
        return getData().getDimscale();
    }

    void setDimscale(double f) {
        getData().setDimscale(f);
    }

    QString getDimBlockName() const {
        return getData().getDimBlockName();
    }

    bool hasDimensionBlockReference() const {
        return getData().hasDimensionBlockReference();
    }

    bool isArrow1Flipped() const {
        return getData().isArrow1Flipped();
    }
    void setArrow1Flipped(bool on) {
        getData().setArrow1Flipped(on);
    }
    bool isArrow2Flipped() const {
        return getData().isArrow2Flipped();
    }
    void setArrow2Flipped(bool on) {
        getData().setArrow2Flipped(on);
    }

    bool isExtLineFix() const {
        return getData().isExtLineFix();
    }
    void setExtLineFix(bool on) {
        getData().setExtLineFix(on);
    }

    double getExtLineFixLength() const {
        return getData().getExtLineFixLength();
    }
    void setExtLineFixLength(double v) {
        getData().setExtLineFixLength(v);
    }

    bool hasOverride(RS::KnownVariable key) const {
        return getData().hasOverride(key);
    }

    static QSet<QString> getDimensionBlockNames(RDocument* doc);

protected:
    virtual void print(QDebug dbg) const;
};

Q_DECLARE_METATYPE(RDimensionEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RDimensionEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RDimensionEntity>*)

#endif
