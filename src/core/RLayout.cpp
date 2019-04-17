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
#include "RLayout.h"
#include "RDocument.h"

RPropertyTypeId RLayout::PropertyCustom;
RPropertyTypeId RLayout::PropertyName;
RPropertyTypeId RLayout::PropertyTabOrder;

RPropertyTypeId RLayout::PropertyMinLimitsX;
RPropertyTypeId RLayout::PropertyMinLimitsY;
RPropertyTypeId RLayout::PropertyMinLimitsZ;
RPropertyTypeId RLayout::PropertyMaxLimitsX;
RPropertyTypeId RLayout::PropertyMaxLimitsY;
RPropertyTypeId RLayout::PropertyMaxLimitsZ;
RPropertyTypeId RLayout::PropertyInsertionBaseX;
RPropertyTypeId RLayout::PropertyInsertionBaseY;
RPropertyTypeId RLayout::PropertyInsertionBaseZ;
RPropertyTypeId RLayout::PropertyMinExtentsX;
RPropertyTypeId RLayout::PropertyMinExtentsY;
RPropertyTypeId RLayout::PropertyMinExtentsZ;
RPropertyTypeId RLayout::PropertyMaxExtentsX;
RPropertyTypeId RLayout::PropertyMaxExtentsY;
RPropertyTypeId RLayout::PropertyMaxExtentsZ;

RPropertyTypeId RLayout::PropertyPlotPaperMarginLeftMM;
RPropertyTypeId RLayout::PropertyPlotPaperMarginBottomMM;
RPropertyTypeId RLayout::PropertyPlotPaperMarginRightMM;
RPropertyTypeId RLayout::PropertyPlotPaperMarginTopMM;
RPropertyTypeId RLayout::PropertyPlotPaperSizeWidth;
RPropertyTypeId RLayout::PropertyPlotPaperSizeHeight;
RPropertyTypeId RLayout::PropertyPlotOriginX;
RPropertyTypeId RLayout::PropertyPlotOriginY;
RPropertyTypeId RLayout::PropertyPlotWindowAreaMinX;
RPropertyTypeId RLayout::PropertyPlotWindowAreaMinY;
RPropertyTypeId RLayout::PropertyPlotWindowAreaMaxX;
RPropertyTypeId RLayout::PropertyPlotWindowAreaMaxY;
RPropertyTypeId RLayout::PropertyNumeratorCustomScale;
RPropertyTypeId RLayout::PropertyDenominatorCustomScale;
RPropertyTypeId RLayout::PropertyPlotPaperUnits;
RPropertyTypeId RLayout::PropertyPlotRotation;
RPropertyTypeId RLayout::PropertyPlotType;
RPropertyTypeId RLayout::PropertyUseStandardScale;
RPropertyTypeId RLayout::PropertyStandardScale;
RPropertyTypeId RLayout::PropertyStandardScaleType;
RPropertyTypeId RLayout::PropertyCanonicalMediaName;

RLayout::RLayout() :
    RObject(),
    tabOrder(0) {
}

RLayout::RLayout(RDocument* document, const QString& name) :
    RObject(document),
    name(name.trimmed()),
    tabOrder(0) {
}

RLayout::~RLayout() {
}

void RLayout::init() {
    RLayout::PropertyCustom.generateId(typeid(RLayout), RObject::PropertyCustom);
    RLayout::PropertyName.generateId(typeid(RLayout), "", QT_TRANSLATE_NOOP("REntity", "Name"));
    RLayout::PropertyTabOrder.generateId(typeid(RLayout), "", QT_TRANSLATE_NOOP("REntity", "Tab Order"));
    RLayout::PropertyMinLimitsX.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Min Limits"), QT_TRANSLATE_NOOP("REntity", "X"));
    RLayout::PropertyMinLimitsY.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Min Limits"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RLayout::PropertyMinLimitsZ.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Min Limits"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RLayout::PropertyMaxLimitsX.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Max Limits"), QT_TRANSLATE_NOOP("REntity", "X"));
    RLayout::PropertyMaxLimitsY.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Max Limits"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RLayout::PropertyMaxLimitsZ.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Max Limits"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RLayout::PropertyInsertionBaseX.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Insertion Base"), QT_TRANSLATE_NOOP("REntity", "X"));
    RLayout::PropertyInsertionBaseY.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Insertion Base"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RLayout::PropertyInsertionBaseZ.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Insertion Base"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RLayout::PropertyMinExtentsX.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Min Extents"), QT_TRANSLATE_NOOP("REntity", "X"));
    RLayout::PropertyMinExtentsY.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Min Extents"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RLayout::PropertyMinExtentsZ.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Min Extents"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RLayout::PropertyMaxExtentsX.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Max Extents"), QT_TRANSLATE_NOOP("REntity", "X"));
    RLayout::PropertyMaxExtentsY.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Max Extents"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RLayout::PropertyMaxExtentsZ.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Max Extents"), QT_TRANSLATE_NOOP("REntity", "Z"));

    // TODO: make these properties translatable
    RLayout::PropertyPlotPaperMarginLeftMM.generateId(typeid(RLayout), "Plot Margins", QT_TRANSLATE_NOOP("REntity", "Left"));
    RLayout::PropertyPlotPaperMarginBottomMM.generateId(typeid(RLayout), "Plot Margins", QT_TRANSLATE_NOOP("REntity", "Bottom"));
    RLayout::PropertyPlotPaperMarginRightMM.generateId(typeid(RLayout), "Plot Margins", QT_TRANSLATE_NOOP("REntity", "Right"));
    RLayout::PropertyPlotPaperMarginTopMM.generateId(typeid(RLayout), "Plot Margins", QT_TRANSLATE_NOOP("REntity", "Top"));
    RLayout::PropertyPlotPaperSizeWidth.generateId(typeid(RLayout), "Plot Paper Size", QT_TRANSLATE_NOOP("REntity", "Width"));
    RLayout::PropertyPlotPaperSizeHeight.generateId(typeid(RLayout), "Plot Paper Size", QT_TRANSLATE_NOOP("REntity", "Height"));
    RLayout::PropertyPlotOriginX.generateId(typeid(RLayout), "Plot Origin", "X");
    RLayout::PropertyPlotOriginY.generateId(typeid(RLayout), "Plot Origin", "Y");
    RLayout::PropertyPlotWindowAreaMinX.generateId(typeid(RLayout), "Plot Window Area Min", "X");
    RLayout::PropertyPlotWindowAreaMinY.generateId(typeid(RLayout), "Plot Window Area Min", "Y");
    RLayout::PropertyPlotWindowAreaMaxX.generateId(typeid(RLayout), "Plot Window Area Max", "X");
    RLayout::PropertyPlotWindowAreaMaxY.generateId(typeid(RLayout), "Plot Window Area Max", "Y");
    RLayout::PropertyNumeratorCustomScale.generateId(typeid(RLayout), "Custom Scale", "Numerator");
    RLayout::PropertyDenominatorCustomScale.generateId(typeid(RLayout), "Custom Scale", "Denominator");
    RLayout::PropertyPlotPaperUnits.generateId(typeid(RLayout), "", "Plot Paper Units");
    RLayout::PropertyPlotRotation.generateId(typeid(RLayout), "", "Plot Rotation");
    RLayout::PropertyPlotType.generateId(typeid(RLayout), "", "Plot Type");
    RLayout::PropertyUseStandardScale.generateId(typeid(RLayout), "", "Use Standard Scale");
    RLayout::PropertyStandardScale.generateId(typeid(RLayout), "", "Standard Scale");
    RLayout::PropertyStandardScaleType.generateId(typeid(RLayout), "", "Standard Scale Type");
    RLayout::PropertyCanonicalMediaName.generateId(typeid(RLayout), "", "Media Name");
}

RLayout* RLayout::clone() const {
    return new RLayout(*this);
}

void RLayout::setName(const QString& n) {
    name = n.trimmed();
}

bool RLayout::setProperty(RPropertyTypeId propertyTypeId,
    const QVariant& value, RTransaction* transaction) {

    bool ret = RObject::setProperty(propertyTypeId, value, transaction);

    if (PropertyName == propertyTypeId) {
        // never change name of layouts starting with * (model space, paper space, ...):
        if (name.startsWith("*")) {
            return false;
        }
        // never change layout name to empty string:
        if (value.toString().isEmpty()) {
            return false;
        }
    }

    ret = ret || RObject::setMember(name, value.toString().trimmed(), PropertyName == propertyTypeId);
    ret = ret || RObject::setMember(tabOrder, value, PropertyTabOrder == propertyTypeId);

    ret = ret || RObject::setMember(minLimits.x, value, PropertyMinLimitsX == propertyTypeId);
    ret = ret || RObject::setMember(minLimits.y, value, PropertyMinLimitsY == propertyTypeId);
    ret = ret || RObject::setMember(minLimits.z, value, PropertyMinLimitsZ == propertyTypeId);
    ret = ret || RObject::setMember(maxLimits.x, value, PropertyMaxLimitsX == propertyTypeId);
    ret = ret || RObject::setMember(maxLimits.y, value, PropertyMaxLimitsY == propertyTypeId);
    ret = ret || RObject::setMember(maxLimits.z, value, PropertyMaxLimitsZ == propertyTypeId);
    ret = ret || RObject::setMember(insertionBase.x, value, PropertyInsertionBaseX == propertyTypeId);
    ret = ret || RObject::setMember(insertionBase.y, value, PropertyInsertionBaseY == propertyTypeId);
    ret = ret || RObject::setMember(insertionBase.z, value, PropertyInsertionBaseZ == propertyTypeId);
    ret = ret || RObject::setMember(minExtents.x, value, PropertyMinExtentsX == propertyTypeId);
    ret = ret || RObject::setMember(minExtents.y, value, PropertyMinExtentsY == propertyTypeId);
    ret = ret || RObject::setMember(minExtents.z, value, PropertyMinExtentsZ == propertyTypeId);
    ret = ret || RObject::setMember(maxExtents.x, value, PropertyMaxExtentsX == propertyTypeId);
    ret = ret || RObject::setMember(maxExtents.y, value, PropertyMaxExtentsY == propertyTypeId);
    ret = ret || RObject::setMember(maxExtents.z, value, PropertyMaxExtentsZ == propertyTypeId);

    ret = ret || RObject::setMember(plotPaperMarginLeftMM, value, PropertyPlotPaperMarginLeftMM == propertyTypeId);
    ret = ret || RObject::setMember(plotPaperMarginBottomMM, value, PropertyPlotPaperMarginBottomMM == propertyTypeId);
    ret = ret || RObject::setMember(plotPaperMarginRightMM, value, PropertyPlotPaperMarginRightMM == propertyTypeId);
    ret = ret || RObject::setMember(plotPaperMarginTopMM, value, PropertyPlotPaperMarginTopMM == propertyTypeId);
    ret = ret || RObject::setMember(plotPaperSize.x, value, PropertyPlotPaperSizeWidth == propertyTypeId);
    ret = ret || RObject::setMember(plotPaperSize.y, value, PropertyPlotPaperSizeHeight == propertyTypeId);
    ret = ret || RObject::setMember(plotOrigin.x, value, PropertyPlotOriginX == propertyTypeId);
    ret = ret || RObject::setMember(plotOrigin.y, value, PropertyPlotOriginY == propertyTypeId);
    ret = ret || RObject::setMember(plotWindowAreaMin.x, value, PropertyPlotWindowAreaMinX == propertyTypeId);
    ret = ret || RObject::setMember(plotWindowAreaMin.y, value, PropertyPlotWindowAreaMinY == propertyTypeId);
    ret = ret || RObject::setMember(plotWindowAreaMax.x, value, PropertyPlotWindowAreaMaxX == propertyTypeId);
    ret = ret || RObject::setMember(plotWindowAreaMax.y, value, PropertyPlotWindowAreaMaxY == propertyTypeId);
    ret = ret || RObject::setMember(numeratorCustomScale, value, PropertyNumeratorCustomScale == propertyTypeId);
    ret = ret || RObject::setMember(denominatorCustomScale, value, PropertyDenominatorCustomScale == propertyTypeId);
    ret = ret || RObject::setMember(plotPaperUnits, value, PropertyPlotPaperUnits == propertyTypeId);
    ret = ret || RObject::setMember(plotRotation, value, PropertyPlotRotation == propertyTypeId);
    ret = ret || RObject::setMember(plotType, value, PropertyPlotType == propertyTypeId);
    ret = ret || RObject::setMember(useStandardScale, value, PropertyUseStandardScale == propertyTypeId);
    ret = ret || RObject::setMember(standardScale, value, PropertyStandardScale == propertyTypeId);
    ret = ret || RObject::setMember(standardScaleType, value, PropertyStandardScaleType == propertyTypeId);
    ret = ret || RObject::setMember(canonicalMediaName, value, PropertyCanonicalMediaName == propertyTypeId);

    return ret;
}

QPair<QVariant, RPropertyAttributes> RLayout::getProperty(
        RPropertyTypeId& propertyTypeId,
        bool humanReadable, bool noAttributes, bool showOnRequest) {

    if (propertyTypeId == PropertyName) {
        return qMakePair(QVariant(name), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyTabOrder) {
        return qMakePair(QVariant(tabOrder), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMinLimitsX) {
        return qMakePair(QVariant(minLimits.x), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMinLimitsY) {
        return qMakePair(QVariant(minLimits.y), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMinLimitsZ) {
        return qMakePair(QVariant(minLimits.z), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMaxLimitsX) {
        return qMakePair(QVariant(maxLimits.x), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMaxLimitsY) {
        return qMakePair(QVariant(maxLimits.y), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMaxLimitsZ) {
        return qMakePair(QVariant(maxLimits.z), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyInsertionBaseX) {
        return qMakePair(QVariant(insertionBase.x), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyInsertionBaseY) {
        return qMakePair(QVariant(insertionBase.y), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyInsertionBaseZ) {
        return qMakePair(QVariant(insertionBase.z), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMinExtentsX) {
        return qMakePair(QVariant(minExtents.x), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMinExtentsY) {
        return qMakePair(QVariant(minExtents.y), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMinExtentsZ) {
        return qMakePair(QVariant(minExtents.z), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMaxExtentsX) {
        return qMakePair(QVariant(maxExtents.x), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMaxExtentsY) {
        return qMakePair(QVariant(maxExtents.y), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMaxExtentsZ) {
        return qMakePair(QVariant(maxExtents.z), RPropertyAttributes());
    }

    else if (propertyTypeId == PropertyPlotPaperMarginLeftMM) {
        return qMakePair(QVariant(plotPaperMarginLeftMM), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyPlotPaperMarginBottomMM) {
        return qMakePair(QVariant(plotPaperMarginBottomMM), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyPlotPaperMarginRightMM) {
        return qMakePair(QVariant(plotPaperMarginRightMM), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyPlotPaperMarginTopMM) {
        return qMakePair(QVariant(plotPaperMarginTopMM), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyPlotPaperSizeWidth) {
        return qMakePair(QVariant(plotPaperSize.x), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyPlotPaperSizeHeight) {
        return qMakePair(QVariant(plotPaperSize.y), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyPlotOriginX) {
        return qMakePair(QVariant(plotOrigin.x), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyPlotOriginY) {
        return qMakePair(QVariant(plotOrigin.y), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyPlotWindowAreaMinX) {
        return qMakePair(QVariant(plotWindowAreaMin.x), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyPlotWindowAreaMinY) {
        return qMakePair(QVariant(plotWindowAreaMin.y), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyPlotWindowAreaMaxX) {
        return qMakePair(QVariant(plotWindowAreaMax.x), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyPlotWindowAreaMaxY) {
        return qMakePair(QVariant(plotWindowAreaMax.y), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyNumeratorCustomScale) {
        return qMakePair(QVariant(numeratorCustomScale), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyDenominatorCustomScale) {
        return qMakePair(QVariant(denominatorCustomScale), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyPlotPaperUnits) {
        return qMakePair(QVariant(plotPaperUnits), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyPlotRotation) {
        return qMakePair(QVariant(plotRotation), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyPlotType) {
        return qMakePair(QVariant(plotType), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyUseStandardScale) {
        return qMakePair(QVariant(useStandardScale), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyStandardScale) {
        return qMakePair(QVariant(standardScale), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyStandardScaleType) {
        return qMakePair(QVariant(standardScaleType), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyCanonicalMediaName) {
        return qMakePair(QVariant(canonicalMediaName), RPropertyAttributes());
    }

    return RObject::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

void RLayout::print(QDebug dbg) const {
    dbg.nospace() << "RLayout(";
    RObject::print(dbg);
    dbg.nospace() << ", name: " << getName()
            << ", insertionBase: " << getInsertionBase()
            << ")";
}
