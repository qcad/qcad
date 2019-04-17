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

#ifndef RLAYOUT_H
#define RLAYOUT_H

#include "core_global.h"

#include <QString>
#include <QDebug>

#include "RGlobal.h"
#include "RObject.h"
#include "RVector.h"
#include "RPropertyTypeId.h"

class RDocument;
class RTransaction;

/**
 * Represents a layout definition in a drawing.
 *
 * \ingroup core
 * \scriptable
 * \sharedPointerSupport
 */
class QCADCORE_EXPORT RLayout: public RObject {
public:
    static RPropertyTypeId PropertyCustom;
    static RPropertyTypeId PropertyName;
    static RPropertyTypeId PropertyTabOrder;

    static RPropertyTypeId PropertyMinLimitsX;
    static RPropertyTypeId PropertyMinLimitsY;
    static RPropertyTypeId PropertyMinLimitsZ;
    static RPropertyTypeId PropertyMaxLimitsX;
    static RPropertyTypeId PropertyMaxLimitsY;
    static RPropertyTypeId PropertyMaxLimitsZ;
    static RPropertyTypeId PropertyInsertionBaseX;
    static RPropertyTypeId PropertyInsertionBaseY;
    static RPropertyTypeId PropertyInsertionBaseZ;
    static RPropertyTypeId PropertyMinExtentsX;
    static RPropertyTypeId PropertyMinExtentsY;
    static RPropertyTypeId PropertyMinExtentsZ;
    static RPropertyTypeId PropertyMaxExtentsX;
    static RPropertyTypeId PropertyMaxExtentsY;
    static RPropertyTypeId PropertyMaxExtentsZ;

    static RPropertyTypeId PropertyPlotPaperMarginLeftMM;
    static RPropertyTypeId PropertyPlotPaperMarginBottomMM;
    static RPropertyTypeId PropertyPlotPaperMarginRightMM;
    static RPropertyTypeId PropertyPlotPaperMarginTopMM;
    static RPropertyTypeId PropertyPlotPaperSizeWidth;
    static RPropertyTypeId PropertyPlotPaperSizeHeight;
    static RPropertyTypeId PropertyPlotOriginX;
    static RPropertyTypeId PropertyPlotOriginY;
    static RPropertyTypeId PropertyPlotWindowAreaMinX;
    static RPropertyTypeId PropertyPlotWindowAreaMinY;
    static RPropertyTypeId PropertyPlotWindowAreaMaxX;
    static RPropertyTypeId PropertyPlotWindowAreaMaxY;
    static RPropertyTypeId PropertyNumeratorCustomScale;
    static RPropertyTypeId PropertyDenominatorCustomScale;
    static RPropertyTypeId PropertyPlotPaperUnits;
    static RPropertyTypeId PropertyPlotRotation;
    static RPropertyTypeId PropertyPlotType;
    static RPropertyTypeId PropertyUseStandardScale;
    static RPropertyTypeId PropertyStandardScale;
    static RPropertyTypeId PropertyStandardScaleType;
    static RPropertyTypeId PropertyCanonicalMediaName;

    enum PlotPaperUnits
    {
        Inches         = 0,   // Inches
        Millimeters    = 1,   // Millimeters
        Pixels         = 2    // Pixels
    };

    enum PlotRotation
    {
        Zero              = 0,   // No rotation (0)
        CounterClockWise  = 1,   // 90 CCW      (90)
        Inverted          = 2,   // Inverted    (180)
        ClockWise         = 3    // 90 CW       (270)
    };

    enum PlotType
    {
        Display        = 0,   // Display
        Extents        = 1,   // Extents
        Limits         = 2,   // Limits
        View           = 3,   // View
        Window         = 4,   // Window
        Layout         = 5    // Layout
    };

    enum StandardScaleType
    {
      Scale_ScaleToFit     = 0,   // Scaled to Fit
      Scale_1_128in_1ft    = 1,   // 1/128" = 1'
      Scale_1_64in_1ft     = 2,   // 1/64" = 1'
      Scale_1_32in_1ft     = 3,   // 1/32" = 1'
      Scale_1_16in_1ft     = 4,   // 1/16" = 1'
      Scale_3_32in_1ft     = 5,   // 3/32" = 1'
      Scale_1_8in_1ft      = 6,   // 1/8" = 1'
      Scale_3_16in_1ft     = 7,   // 3/16" = 1'
      Scale_1_4in_1ft      = 8,   // 1/4" = 1'
      Scale_3_8in_1ft      = 9,   // 3/8" = 1'
      Scale_1_2in_1ft      = 10,  // 1/2" = 1'
      Scale_3_4in_1ft      = 11,  // 3/4" = 1'
      Scale_1in_1ft        = 12,  // 1" = 1'
      Scale_3in_1ft        = 13,  // 3" = 1'
      Scale_6in_1ft        = 14,  // 6" = 1'
      Scale_1ft_1ft        = 15,  // 1' = 1'
      Scale_1_1            = 16,  // 1:1
      Scale_1_2            = 17,  // 1:2
      Scale_1_4            = 18,  // 1:4
      Scale_1_5            = 19,  // 1:5
      Scale_1_8            = 20,  // 1:8
      Scale_1_10           = 21,  // 1:10
      Scale_1_16           = 22,  // 1:16
      Scale_1_20           = 23,  // 1:20
      Scale_1_30           = 24,  // 1:30
      Scale_1_40           = 25,  // 1:40
      Scale_1_50           = 26,  // 1:50
      Scale_1_100          = 27,  // 1:100
      Scale_2_1            = 28,  // 2:1
      Scale_4_1            = 29,  // 4:1
      Scale_8_1            = 30,  // 8:1
      Scale_10_1           = 31,  // 10:1
      Scale_100_1          = 32,  // 100:1
      Scale_1000_1         = 33,  // 1000:1
      Scale_1and1_2in_1ft  = 34  // 1.5"= 1'
    };

public:
    RLayout();

    RLayout(RDocument* document, const QString& name);

    virtual ~RLayout();

    static void init();

    virtual RS::EntityType getType() const {
        return RS::ObjectLayout;
    }

    virtual RLayout* clone() const;

    QString getName() const {
        return name;
    }

    void setName(const QString& n);

    int getTabOrder() const {
        return tabOrder;
    }

    void setTabOrder(int to) {
        tabOrder = to;
    }

    void setMinLimits(const RVector& minLimits) {
        this->minLimits = minLimits;
    }

    RVector getMinLimits() const {
        return minLimits;
    }

    void setMaxLimits(const RVector& maxLimits) {
        this->maxLimits = maxLimits;
    }

    RVector getMaxLimits() const {
        return maxLimits;
    }

    void setInsertionBase(const RVector& insertionBase) {
        this->insertionBase = insertionBase;
    }

    RVector getInsertionBase() const {
        return insertionBase;
    }

    void setMinExtents(const RVector& minExtents) {
        this->minExtents = minExtents;
    }

    RVector getMinExtents() const {
        return minExtents;
    }

    void setMaxExtents(const RVector& maxExtents) {
        this->maxExtents = maxExtents;
    }

    RVector getMaxExtents() const {
        return maxExtents;
    }

    void setPlotPaperMarginLeftMM(double v) {
        plotPaperMarginLeftMM = v;
    }

    void setPlotPaperMarginBottomMM(double v) {
        plotPaperMarginBottomMM = v;
    }

    void setPlotPaperMarginRightMM(double v) {
        plotPaperMarginRightMM = v;
    }

    void setPlotPaperMarginTopMM(double v) {
        plotPaperMarginTopMM = v;
    }

    void setPlotPaperSize(const RVector& v) {
        plotPaperSize = v;
    }

    void setPlotOrigin(const RVector& v) {
        plotOrigin = v;
    }

    void setPlotWindowAreaMin(const RVector& v) {
        plotWindowAreaMin = v;
    }

    void setPlotWindowAreaMax(const RVector& v) {
        plotWindowAreaMax = v;
    }

    void setNumeratorCustomScale(double v) {
        numeratorCustomScale = v;
    }

    void setDenominatorCustomScale(double v) {
        denominatorCustomScale = v;
    }

    void setPlotPaperUnits(RLayout::PlotPaperUnits v) {
        plotPaperUnits = v;
    }

    void setPlotRotation(RLayout::PlotRotation v) {
        plotRotation = v;
    }

    void setPlotType(RLayout::PlotType v) {
        plotType = v;
    }

    void setUseStandardScale(bool v) {
        useStandardScale = v;
    }

    void setStandardScale(double v) {
        standardScale = v;
    }

    void setStandardScaleType(RLayout::StandardScaleType v) {
        standardScaleType = v;
    }

    void setCanonicalMediaName(const QString& v) {
        canonicalMediaName = v;
    }



    double getPlotPaperMarginLeftMM() const {
        return plotPaperMarginLeftMM;
    }

    double getPlotPaperMarginBottomMM() const {
        return plotPaperMarginBottomMM;
    }

    double getPlotPaperMarginRightMM() const {
        return plotPaperMarginRightMM;
    }

    double getPlotPaperMarginTopMM() const {
        return plotPaperMarginTopMM;
    }

    RVector getPlotPaperSize() const {
        return plotPaperSize;
    }

    RVector getPlotOrigin() const {
        return plotOrigin;
    }

    RVector getPlotWindowAreaMin() const {
        return plotWindowAreaMin;
    }

    RVector getPlotWindowAreaMax() const {
        return plotWindowAreaMax;
    }

    double getNumeratorCustomScale() const {
        return numeratorCustomScale;
    }

    double getDenominatorCustomScale() const {
        return denominatorCustomScale;
    }

    RLayout::PlotPaperUnits getPlotPaperUnits() const {
        return plotPaperUnits;
    }

    RLayout::PlotRotation getPlotRotation() const {
        return plotRotation;
    }

    RLayout::PlotType getPlotType() const {
        return plotType;
    }

    bool getUseStandardScale() const {
        return useStandardScale;
    }

    double getStandardScale() const {
        return standardScale;
    }

    RLayout::StandardScaleType getStandardScaleType() const {
        return standardScaleType;
    }

    QString getCanonicalMediaName() const {
        return canonicalMediaName;
    }



    virtual QPair<QVariant, RPropertyAttributes> getProperty(RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);
    virtual bool setProperty(RPropertyTypeId propertyTypeId,
            const QVariant& value, RTransaction* transaction=NULL);

protected:
    /**
     * \nonscriptable
     */
    virtual void print(QDebug dbg) const;

private:
    QString name;
    int tabOrder;

    RVector minLimits;
    RVector maxLimits;
    RVector insertionBase;
    RVector minExtents;
    RVector maxExtents;

    // TODO: split into base class 'RPlotSettings':
    double plotPaperMarginLeftMM;
    double plotPaperMarginBottomMM;
    double plotPaperMarginRightMM;
    double plotPaperMarginTopMM;
    RVector plotPaperSize;
    RVector plotOrigin;
    RVector plotWindowAreaMin;
    RVector plotWindowAreaMax;
    double numeratorCustomScale;
    double denominatorCustomScale;
    PlotPaperUnits plotPaperUnits;
    PlotRotation plotRotation;
    PlotType plotType;
    bool useStandardScale;
    double standardScale;
    StandardScaleType standardScaleType;
    QString canonicalMediaName;
};


Q_DECLARE_METATYPE(QSharedPointer<RLayout>)
Q_DECLARE_METATYPE(QSharedPointer<RLayout>*)
Q_DECLARE_METATYPE(RLayout)
Q_DECLARE_METATYPE(RLayout*)
Q_DECLARE_METATYPE(RLayout::PlotPaperUnits)
Q_DECLARE_METATYPE(RLayout::PlotPaperUnits*)
Q_DECLARE_METATYPE(RLayout::PlotRotation)
Q_DECLARE_METATYPE(RLayout::PlotRotation*)
Q_DECLARE_METATYPE(RLayout::PlotType)
Q_DECLARE_METATYPE(RLayout::PlotType*)
Q_DECLARE_METATYPE(RLayout::StandardScaleType)
Q_DECLARE_METATYPE(RLayout::StandardScaleType*)

#endif
