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

#ifndef RPROPERTYATTRIBUTES_H
#define RPROPERTYATTRIBUTES_H

#include "core_global.h"

#include <QString>
#include <QSet>
#include <QMap>
#include <QPair>
#include <QVariant>

#include "RDebug.h"
#include "RMath.h"

/**
 * Structure to transfer attributes about property types.
 * For example a property 'Side' might have the two choices
 * 'Left' and 'Right'. These choices can be stored in a
 * \c RPropertyAttributes object. Other attributes define if a property
 * is visible, if it is an angle (such properties require
 * conversion between radiants and degrees), etc.
 *
 * \ingroup core
 * \scriptable
 * \copyable
 */
class QCADCORE_EXPORT RPropertyAttributes {
public:
    enum Option {
        NoOptions = 0x0,
        ReadOnly = 0x1,                  //!< Property is read only
        Invisible = 0x2,                 //!< Property is not displayed
        Angle = 0x4,                     //!< Property is an angle (shown in user preferred angle unit)
        AffectsOtherProperties = 0x8,    //!< Property affects others, needs refresh on changing
        IgnoreCase = 0x10,               //!< Property is not case sensitive
        AllowMixedValue = 0x20,          //!< Property can be mixed
        List = 0x40,                     //!< Property is a list (e.g. x values of polyline vertices)
        Mixed = 0x80,                    //!< Property has mixed values
        RichText = 0x100,                //!< Property is rich text and can be edited as such
        Style = 0x200,                   //!< Property is a text style (font)
        DimensionLabel = 0x400,          //!< Property is a dimension label (suggests context menu to insert symbols, including <>)
        Label = 0x800,                   //!< Property is a label (suggests context menu to insert symbols)
        Pattern = 0x1000,                //!< Property is a hatch pattern name
        Custom = 0x2000,                 //!< Property is a map of custom properties
        Integer = 0x4000,                //!< Property is an int (not a double number)
        Redundant = 0x8000,              //!< Property is redundant (e.g. angle for line entities)
        VisibleToParent = 0x10000,       //!< Property can be edited in the context of the parent entity
        KnownVariable = 0x20000,         //!< Property is a known DXF variable
        NumericallySorted = 0x40000,     //!< Sort choices for this property numerically
        Percentage = 0x80000 | Integer,  //!< Property is a percentage (0...100), implies Integer
        Sum = 0x100000 | ReadOnly | Redundant,  //!< Sum up this property when multiple entities are selected (area, length),
                                         //!< implies ReadOnly and Redundant
        Undeletable = 0x200000,          //!< Property is undeletable (custom properties only)
        OnRequest = 0x400000,            //!< Property shown on request (slow to compute)
        Location = 0x800000,             //!< Property affected when transforming
        RefPoint = 0x1000000,            //!< Property affected when moving reference point
        Geometry = Location | RefPoint,  //!< Property affected when chaning geometry (Location | RefPoint)
        Scale = 0x2000000,               //!< Property is scale (1:2, 5"=1", ...)
        Area = 0x4000000,                //!< Property is area (relevant for formatting of value)
        UnitLess = 0x8000000             //!< Property has no unit (linetype scale, draw order, ...)
    };
    Q_DECLARE_FLAGS(Options, Option)

public:
    RPropertyAttributes() : options(NoOptions) {}

    RPropertyAttributes(RPropertyAttributes::Options options) :
        options(options) {
    }

    void setOption(RPropertyAttributes::Option option, bool on);

    bool isReadOnly() const {
        return options.testFlag(ReadOnly);
    }

    void setReadOnly(bool readOnly) {
        setOption(ReadOnly, readOnly);
    }

    bool isInvisible() const {
        return options.testFlag(Invisible);
    }

    void setInvisible(bool invisible) {
        setOption(Invisible, invisible);
    }

    bool isUndeletable() const {
        return options.testFlag(Undeletable);
    }

    void setUndeletable(bool undeletable) {
        setOption(Undeletable, undeletable);
    }

    bool isList() const {
        return options.testFlag(List);
    }

    void setList(bool on) {
        setOption(List, on);
    }

    bool isAngleType() const {
        return options.testFlag(Angle);
    }

    void setAngleType(bool angle) {
        setOption(Angle, angle);
    }

    bool getIgnoreCase() const {
        return options.testFlag(IgnoreCase);
    }

    void setIgnoreCase(bool ignoreCase) {
        setOption(IgnoreCase, ignoreCase);
    }

    bool affectsOtherProperties() const {
        return options.testFlag(AffectsOtherProperties);
    }

    void setAffectsOtherProperties(bool affectsOtherProperties) {
        setOption(AffectsOtherProperties, affectsOtherProperties);
    }

    void setAllowMixedValue(bool allowMixedValue) {
        setOption(AllowMixedValue, allowMixedValue);
    }

    bool getAllowMixedValue() {
        return options.testFlag(AllowMixedValue);
    }

    QSet<QString> getChoices() const {
        return choices;
    }

    void setChoices(QSet<QString> choices) {
        this->choices = choices;
    }

    bool hasChoices() {
        return !choices.isEmpty();
    }

//    QList<QVariant> getEnumChoices() const {
//        return enumChoices;
//    }

//    void setEnumChoices(QList<QVariant> ec) {
//        enumChoices = ec;
//    }

//    bool hasEnumChoices() const {
//        return !enumChoices.isEmpty();
//    }

    bool isRichText() const {
        return options.testFlag(RichText);
    }

    void setRichText(bool on) {
        setOption(RichText, on);
    }

    bool isStyle() const {
        return options.testFlag(Style);
    }

    void setStyle(bool on) {
        setOption(Style, on);
    }

    void mixWith(const RPropertyAttributes & other);

    bool isMixed() const {
        return options.testFlag(Mixed);
    }

    void setMixed(bool mixed) {
        setOption(Mixed, mixed);
    }

    bool isSum() const {
        return options.testFlag(Sum);
    }

    void setSum(bool sum) {
        setOption(Sum, sum);
    }

    bool isOnRequest() const {
        return options.testFlag(OnRequest);
    }

    void setOnRequest(bool onRequest) {
        setOption(OnRequest, onRequest);
    }

    bool isLabel() const {
        return options.testFlag(Label);
    }

    bool isCustom() const {
        return options.testFlag(Custom);
    }

    bool isDimensionLabel() const {
        return options.testFlag(DimensionLabel);
    }

    bool isInteger() const {
        return options.testFlag(Integer);
    }

    bool isRedundant() const {
        return options.testFlag(Redundant);
    }

    void setRedundant(bool on) {
        setOption(Redundant, on);
    }

    bool isVisibleToParent() const {
        return options.testFlag(VisibleToParent);
    }

    bool isNumericallySorted() const {
        return options.testFlag(NumericallySorted);
    }

    void setNumericallySorted(bool on) {
        setOption(NumericallySorted, on);
    }

    bool isScaleType() const {
        return options.testFlag(Scale);
    }

    void setScaleType(bool v) {
        setOption(Scale, v);
    }

    bool isAreaType() const {
        return options.testFlag(Area);
    }

    void setAreaType(bool v) {
        setOption(Area, v);
    }

    bool isUnitLess() const {
        return options.testFlag(UnitLess);
    }

    void setUnitLess(bool v) {
        setOption(UnitLess, v);
    }

    QString getLabel() const {
        return label;
    }

    void setLabel(const QString& l) {
        label = l;
    }

    bool operator == (const RPropertyAttributes& other) const {
        if (isInvisible() != other.isInvisible()) {
            return false;
        }
        if (isAngleType() != other.isAngleType()) {
            return false;
        }
        if (affectsOtherProperties() != other.affectsOtherProperties()) {
            return false;
        }
        if (isList() != other.isList()) {
            return false;
        }
        if (choices != other.choices) {
            return false;
        }

        return true;
    }

    bool operator !=(const RPropertyAttributes& other) const {
        return !operator ==(other);
    }


private:
    RPropertyAttributes::Options options;
    QSet<QString> choices;
    QString label;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(RPropertyAttributes::Options)

typedef QPair<QVariant, RPropertyAttributes> _RPairVariantPropertyAttributes;
Q_DECLARE_METATYPE(RPropertyAttributes)
Q_DECLARE_METATYPE(RPropertyAttributes*)
Q_DECLARE_METATYPE(QFlags<RPropertyAttributes::Option>*)
Q_DECLARE_METATYPE(RPropertyAttributes::Option)
Q_DECLARE_METATYPE(RPropertyAttributes::Option*)
Q_DECLARE_METATYPE(_RPairVariantPropertyAttributes*)
Q_DECLARE_METATYPE(_RPairVariantPropertyAttributes)

#endif
