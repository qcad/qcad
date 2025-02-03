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

#ifndef RDIMENSIONDATA_H
#define RDIMENSIONDATA_H

#include "entity_global.h"

#include "RColor.h"
#include "RDimStyleData.h"
#include "REntityData.h"
#include "RTextData.h"
#include "RVector.h"

class RDocument;
class RLine;
class RRefPoint;

/**
 * Base class for dimension entity data classes.
 *
 * \scriptable
 * \ingroup entity
 *
 * \todo explodable interface that returns list of REntityData, maybe base class RComposedEntityData?
 */
class QCADENTITY_EXPORT RDimensionData: public REntityData {
    friend class RDimensionEntity;

protected:
    RDimensionData(RDocument* document, const RDimensionData& data);

public:
    RDimensionData(RDocument* document = NULL);
    RDimensionData(const RVector& definitionPoint,
                   const RVector& textPositionCenter,
                   RS::VAlign valign,
                   RS::HAlign halign,
                   RS::TextLineSpacingStyle lineSpacingStyle,
                   double lineSpacingFactor,
                   const QString& text,
                   const QString& fontName,
                   double textRotation);

//    ~RDimensionData() {
//        if (overrides!=NULL) {
//            delete overrides;
//            overrides = NULL;
//        }
//    }

//    RDimensionData(const RDimensionData& other) {
//        *this = other;
//    }

//    RDimensionData& operator =(const RDimensionData& other) {
//        //*this = other;

//        definitionPoint = other.definitionPoint;
//        textPositionCenter = other.textPositionCenter;
//        textPositionSide = other.textPositionSide;
//        valign = other.valign;
//        halign = other.halign;
//        lineSpacingStyle = other.lineSpacingStyle;
//        lineSpacingFactor = other.lineSpacingFactor;
//        text = other.text;
//        upperTolerance = other.upperTolerance;
//        lowerTolerance = other.lowerTolerance;
//        fontName = other.fontName;
//        dimBlockName = other.dimBlockName;
//        defaultAngle = other.defaultAngle;
//        textAngle = other.textAngle;
//        dimlunitOverride = other.dimlunitOverride;
//        arrow1Flipped = other.arrow1Flipped;
//        arrow2Flipped = other.arrow2Flipped;
//        extLineFix = other.extLineFix;
//        extLineFixLength = other.extLineFixLength;
//        dirty = other.dirty;
//        textData = other.textData;
//        boundingBox = other.boundingBox;
//        dimLineLength = other.dimLineLength;
//        arrow1Pos = other.arrow1Pos;
//        arrow2Pos = other.arrow2Pos;
//        autoTextPos = other.autoTextPos;
//        shapes = other.shapes;

//        overrides = NULL;
//        if (other.hasOverrides()) {
//            this->makeOverrides();
//            *this->overrides = *other.overrides;
//        }
//    }

    virtual RS::EntityType getType() const {
        return RS::EntityDimension;
    }
    virtual RBox getBoundingBox(bool ignoreEmpty=false) const;

    void render() const;

    void updateBoundingBox(const RBox& box) const {
        boundingBox = box;
    }
    void updateTextPositionCenter(const RVector& p) const {
        textPositionCenter = p;
    }
    void updateTextPositionSide(const RVector& p) const {
        textPositionSide = p;
    }
    void updateTextData(const RTextData& d) const {
        textData = d;
    }
    void updateShapes(const QList<QSharedPointer<RShape> >& s) const {
        shapes = s;
    }
    void updateArrowPos1(const RVector& p) const {
        arrow1Pos = p;
    }
    void updateArrowPos2(const RVector& p) const {
        arrow2Pos = p;
    }

    void clearStyleOverrides() {
        overrides.clear();
        update();
    }

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false, QList<RObject::Id>* entityIds = NULL) const {
        Q_UNUSED(queryBox)
        Q_UNUSED(ignoreComplex)
        Q_UNUSED(segment)
        Q_UNUSED(entityIds)

        render();

        return shapes;
    }

    virtual RVector getPointOnEntity() const;

    virtual bool isValid() const;
    virtual bool isSane() const;

    virtual void setDefinitionPoint(const RVector& p) {
        definitionPoint = p;
        update();
    }

    RVector getDefinitionPoint() const {
        return definitionPoint;
    }

    void setText(const QString& t) {
        text = t;
        update();
    }

    QString getText() const {
        return text;
    }

    void setUpperTolerance(const QString& t) {
        upperTolerance = t;
        update();
    }

    QString getUpperTolerance() const {
        return upperTolerance;
    }

    void setLowerTolerance(const QString& t) {
        lowerTolerance = t;
        update();
    }

    QString getLowerTolerance() const {
        return lowerTolerance;
    }

    void setTextPosition(const RVector& p) {
        if (p.isSane()) {
            textPositionCenter = p;
        }
        textPositionSide = RVector::invalid;
        update();
    }

    //virtual RVector getTextPosition() const = 0;

    virtual RVector getTextPosition() const {
        if (textPositionSide.isValid()) {
            return textPositionSide;
        }
        else {
            return textPositionCenter;
        }
    }

    void setFontName(const QString& fn) {
        fontName = fn;
        update();
    }

    QString getFontName() const {
        return fontName;
    }

//    void setTextColor(const RColor& tc) {
//        textColor = tc;
//        update();
//    }

//    RColor getTextColor() const {
//        return textColor;
//    }

    void setDimBlockName(const QString& bn) {
        dimBlockName = bn;
        //update();
    }

    QString getDimBlockName() const {
        return dimBlockName;
    }

    bool hasOverrides() const {
        return overrides.isValid();
    }

    bool hasOverride(RS::KnownVariable key) const {
        return overrides.hasOverride(key);
    }

    RDimStyleData getOverrides() const {
        return overrides;
    }

//    void makeOverrides() {
//        if (overrides==NULL) {
//            overrides = new RDimStyleData();
//        }
//    }

    void setDimXVariant(RS::KnownVariable key, const QVariant& v);
    void setDimXDouble(RS::KnownVariable key, double v);
    void setDimXInt(RS::KnownVariable key, int v);
    void setDimXBool(RS::KnownVariable key, bool v);
    void setDimXColor(RS::KnownVariable key, const RColor& v);

    QVariant getDimXVariant(RS::KnownVariable key) const;
    QVariant getVariantOverride(RS::KnownVariable key) const;

    double getDimXDouble(RS::KnownVariable key) const;
    double getDoubleOverride(RS::KnownVariable key) const;

    int getDimXInt(RS::KnownVariable key) const;
    int getIntOverride(RS::KnownVariable key) const;

    bool getDimXBool(RS::KnownVariable key) const;
    bool getBoolOverride(RS::KnownVariable key) const;

    RColor getDimXColor(RS::KnownVariable key) const;
    RColor getColorOverride(RS::KnownVariable key) const;

    double getDimlfac() const {
        return getDimXDouble(RS::DIMLFAC);
    }

    void setDimlfac(double f) {
        setDimXDouble(RS::DIMLFAC, f);
    }

    double getLinearFactor() const {
        return getDimlfac();
    }
    void setLinearFactor(double f) {
        setDimlfac(f);
    }

    double getDimscale() const {
        return getDimXDouble(RS::DIMSCALE);
    }

    void setDimscale(double f) {
        setDimXDouble(RS::DIMSCALE, f);
    }

    bool isArrow1Flipped() const {
        return arrow1Flipped;
    }
    void setArrow1Flipped(bool on) {
        arrow1Flipped = on;
    }
    bool isArrow2Flipped() const {
        return arrow2Flipped;
    }
    void setArrow2Flipped(bool on) {
        arrow2Flipped = on;
    }

    bool isExtLineFix() const {
        return extLineFix;
    }
    void setExtLineFix(bool on) {
        extLineFix = on;
    }

    double getExtLineFixLength() const {
        return extLineFixLength;
    }
    void setExtLineFixLength(double v) {
        extLineFixLength = v;
    }

    void adjustExtensionLineFixLength(RLine& extLine1, RLine& extLine2, bool addDimExe = true) const;

    bool hasSpaceForArrows() const;

    virtual double getDistanceTo(const RVector& point, bool limited = true, double range = 0.0, bool draft = false, double strictRange = RMAXDOUBLE) const;
    virtual bool intersectsWith(const RShape& shape) const;

    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool clickReferencePoint(const RVector& referencePoint);
    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center);
    virtual bool scale(const RVector& scaleFactors, const RVector& center);
    virtual void scaleVisualProperties(double scaleFactor);
    virtual bool mirror(const RLine& axis);

    double getDimexo() const {
        return getDimXDouble(RS::DIMEXO) * getDimscale();
    }
    void setDimexo(double v) {
        setDimXDouble(RS::DIMEXO, v);
    }
    double getDimexe() const {
        return getDimXDouble(RS::DIMEXE) * getDimscale();
    }
    void setDimexe(double v) {
        setDimXDouble(RS::DIMEXE, v);
    }
    double getDimasz() const {
        return getDimXDouble(RS::DIMASZ) * getDimscale();
    }
    void setDimasz(double v) {
        setDimXDouble(RS::DIMASZ, v);
    }
    double getDimdli() const {
        return getDimXDouble(RS::DIMDLI) * getDimscale();
    }
    void setDimdli(double v) {
        setDimXDouble(RS::DIMDLI, v);
    }
    double getDimgap() const {
        return getDimXDouble(RS::DIMGAP) * getDimscale();
    }
    void setDimgap(double v) {
        setDimXDouble(RS::DIMGAP, v);
    }
    double getDimtxt() const {
        return getDimXDouble(RS::DIMTXT) * getDimscale();
    }
    void setDimtxt(double t) {
        setDimXDouble(RS::DIMTXT, t);
    }
    int getDimlunit() const {
        return getDimXInt(RS::DIMLUNIT);
    }
    void setDimlunit(int l) {
        setDimXInt(RS::DIMLUNIT, l);

        //makeOverrides();
        //overrides.setDimlunit(l);
        //update();

//        dimlunitOverride = l;
//        update();
    }
    int getDimjust() const {
        return getDimXInt(RS::DIMJUST);
    }
    /**
     * \return 0 for text above dimension line, otherwise text on dimension line.
     */
    int getDimtad() const {
        return getDimXInt(RS::DIMTAD);
    }
    void setDimtad(int v) {
        setDimXInt(RS::DIMTAD, v);
    }
    /**
     * \return 0 for aligned, other for horizontal text label.
     */
    bool getDimtih() const {
        return getDimXBool(RS::DIMTIH);
    }
    void setDimtih(bool v) {
        setDimXBool(RS::DIMTIH, v);
    }
    double getDimtsz() const {
        return getDimXDouble(RS::DIMTSZ) * getDimscale();
    }
    void setDimtsz(double t) {
        setDimXDouble(RS::DIMTSZ, t);
    }
    int getDimzin() const {
        return getDimXInt(RS::DIMZIN);
    }
    void setDimzin(int v) {
        setDimXInt(RS::DIMZIN, v);
    }
    int getDimaunit() const {
        return getDimXInt(RS::DIMAUNIT);
    }
    void setDimaunit(int v) {
        setDimXInt(RS::DIMAUNIT, v);
    }
    int getDimadec() const {
        return getDimXInt(RS::DIMADEC);
    }
    void setDimadec(int v) {
        setDimXInt(RS::DIMADEC, v);
    }
    int getDimdec() const {
        return getDimXInt(RS::DIMDEC);
    }
    void setDimdec(int v) {
        setDimXInt(RS::DIMDEC, v);
    }
    int getDimazin() const {
        return getDimXInt(RS::DIMAZIN);
    }
    void setDimazin(int v) {
        setDimXInt(RS::DIMAZIN, v);
    }
    int getDimdsep() const {
        return getDimXInt(RS::DIMDSEP);
    }
    void setDimdsep(int v) {
        setDimXInt(RS::DIMDSEP, v);
    }
    RColor getDimclrt() const {
        return getDimXColor(RS::DIMCLRT);
    }
    void setDimclrt(const RColor& v) {
        setDimXColor(RS::DIMCLRT, v);
    }

    bool useArchTick() const {
        return getDimXDouble(RS::DIMTSZ) > 0.0;
    }

    int getDimblk() const {
        return getDimXInt(RS::DIMBLK);
    }

    QString getDimblkName() const;



//    template<class T>
//    T getDimX(RS::KnownVariable key, T def) const {
//        T dimX = 0;

//        // get value from override:
//        if (hasOverride(key)) {
//            if (typeid(T) == typeid(double)) {
//                return getDoubleOverride(key);
//            }
//            else if (typeid(T) == typeid(int)) {
//                return getIntOverride(key);
//            }
//            else if (typeid(T) == typeid(RColor)) {
//                return getColorOverride(key);
//            }
//        }

//        if (document!=NULL) {
//            QSharedPointer<RDimStyle> dimStyle = document->queryDimStyleDirect();
//            if (!dimStyle.isNull()) {
//                // get value from dimension style:
//                if (typeid(T) == typeid(double)) {
//                    dimX = dimStyle->getDouble(key);
//                }
//                if (typeid(T) == typeid(int)) {
//                    dimX = dimStyle->getInt(key);
//                }
//            }
//            else {
//                // TODO: get value from document (should never happen):
//                Q_ASSERT(false);
////                QVariant v = document->getKnownVariable(key, dimX);
////                if (typeid(T) == typeid(double)) {
////                    dimX = v.toDouble();
////                }
////                else if (typeid(T) == typeid(int)) {
////                    dimX = v.toInt();
////                }
////                if (isDimXScaled(key)) {
////                    dimX *= getDimscale();
////                }
//            }
//        }
//        else {
//            qWarning() << "RDimensionData::getDimexo: no document";
//        }

//        return dimX;
//    }

    bool isDimXScaled(RS::KnownVariable var) const {
        if (var==RS::DIMEXO) {
            return true;
        }

        return false;
    }

    bool hasCustomTextPosition() const;
    void setCustomTextPosition(bool on);

    RS::TextLineSpacingStyle getLineSpacingStyle() const {
        return lineSpacingStyle;
    }

    double getLineSpacingFactor() const {
        return lineSpacingFactor;
    }

    double getTextRotation() const {
        return textRotation;
    }

    void setTextRotation(double r) {
        textRotation = r;
    }

//    QList<QSharedPointer<RShape> > getDimensionLineShapes(
//        const RVector& p1, const RVector& p2,
//        bool arrow1, bool arrow2) const;
//    virtual QList<QSharedPointer<RShape> > getArrow(
//        const RVector& position, double direction) const;
    RTextData& getTextData(bool noRender = false) const;
    RTextData& initTextData() const;
    //virtual void updateTextData() const;
    virtual QString getMeasurement(bool resolveAutoMeasurement = true) const;
    virtual double getMeasuredValue() const { return 0.0; }
    virtual QString getAutoLabel() const { return ""; }
    QString formatLabel(double distance) const;
    QString formatAngleLabel(double textAngle) const;
    //virtual void updateFromTextPosition() = 0;

    virtual void update() const;

    QSharedPointer<RBlockReferenceEntity> getDimensionBlockReference() const;
    bool hasDimensionBlockReference() const;

    virtual void to2D();

protected:
    /** Definition point */
    mutable RVector definitionPoint;
    /** Middle point of dimension text */
    mutable RVector textPositionCenter;
    /**
     * Middle point of dimension text when automatically moved to
     * the side for lack of space
     */
    mutable RVector textPositionSide;
    /** Vertical alignment */
    RS::VAlign valign;
    /** Horizontal alignment */
    RS::HAlign halign;
    /** Line spacing style */
    RS::TextLineSpacingStyle lineSpacingStyle;
    /** Line spacing factor */
    double lineSpacingFactor;
    /**
     * Text string entered explicitly by user or null
     * or "<>" for the actual measurement or " " (one blank space)
     * for suppressing the text.
     */
    QString text;
    /** Upper tolerance limit */
    QString upperTolerance;
    /** Lower tolerance limit */
    QString lowerTolerance;
    /** Dimension font name */
    QString fontName;
    /** Dimension text color */
    //RColor textColor;
    /** Dimension appearance is defined in this block */
    mutable QString dimBlockName;

    mutable double defaultAngle;
    /** Rotation angle of dimension text away from default orientation */
    double textRotation;

    // RDimStyleData for overrides:
    RDimStyleData overrides;

    //double linearFactor;
    //double dimScaleOverride;
    //double dimtxtOverride;
    //int dimlunitOverride;

    bool arrow1Flipped;
    bool arrow2Flipped;

    bool extLineFix;
    double extLineFixLength;

    mutable bool dirty;
    mutable RTextData textData;
    mutable RBox boundingBox;

    mutable double dimLineLength;
    mutable RVector arrow1Pos;
    mutable RVector arrow2Pos;

    /** True if the textPosition should be automatically calculated. */
    mutable bool autoTextPos;

    mutable QList<QSharedPointer<RShape> > shapes;
};

Q_DECLARE_METATYPE(RDimensionData*)
Q_DECLARE_METATYPE(const RDimensionData*)
Q_DECLARE_METATYPE(QSharedPointer<RDimensionData>)

#endif
