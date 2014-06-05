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
#include "RPropertyTypeId.h"

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
        VisibleToParent = 0x10000        //!< Property can be edited in the context of the parent entity
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

    void mixWith(const RPropertyAttributes & other);

    bool isMixed() const {
        return options.testFlag(Mixed);
    }

    void setMixed(bool mixed) {
        setOption(Mixed, mixed);
    }

    bool isLabel() const {
        return options.testFlag(Label);
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

    bool isVisibleToParent() const {
        return options.testFlag(VisibleToParent);
    }

    RPropertyTypeId getPropertyTypeId() {
        return propertyTypeId;
    }

    void setPropertyTypeId(RPropertyTypeId pid) {
        propertyTypeId = pid;
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
        if (propertyTypeId != other.propertyTypeId) {
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
    //QList<QVariant> enumChoices;
    RPropertyTypeId propertyTypeId;
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
