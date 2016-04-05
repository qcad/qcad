/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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

    void setPlotPaperUnits(PlotPaperUnits v) {
        plotPaperUnits = v;
    }

    void setPlotRotation(PlotRotation v) {
        plotRotation = v;
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

    PlotPaperUnits getPlotPaperUnits() const {
        return plotPaperUnits;
    }

    PlotRotation getPlotRotation() const {
        return plotRotation;
    }



    virtual QPair<QVariant, RPropertyAttributes> getProperty(RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false);
    virtual bool setProperty(RPropertyTypeId propertyTypeId,
            const QVariant& value, RTransaction* transaction=NULL);

    virtual bool isSelectedForPropertyEditing();

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
};


Q_DECLARE_METATYPE(QSharedPointer<RLayout>)
Q_DECLARE_METATYPE(QSharedPointer<RLayout>*)
Q_DECLARE_METATYPE(RLayout)
Q_DECLARE_METATYPE(RLayout*)
Q_DECLARE_METATYPE(RLayout::PlotPaperUnits)
Q_DECLARE_METATYPE(RLayout::PlotRotation)

#endif
