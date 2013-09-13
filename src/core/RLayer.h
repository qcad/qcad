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

#ifndef RLAYER_H
#define RLAYER_H

#include "core_global.h"

#include <QString>
#include <QColor>
#include <QDebug>

#include "RGlobal.h"
#include "RObject.h"
#include "RVector.h"
#include "RPropertyTypeId.h"
#include "RLinetype.h"
#include "RColor.h"
#include "RLineweight.h"
#include "RPropertyAttributes.h"

class RDocument;

/**
 * Represents a layer in a drawing.
 *
 * \ingroup core
 * \scriptable
 * \sharedPointerSupport
 */
class QCADCORE_EXPORT RLayer: public RObject {
public:
    static RPropertyTypeId PropertyName;
    static RPropertyTypeId PropertyFrozen;
    static RPropertyTypeId PropertyLocked;
    static RPropertyTypeId PropertyColor;
    static RPropertyTypeId PropertyLinetype;
    static RPropertyTypeId PropertyLineweight;

public:
    RLayer();

    RLayer(RDocument* document, const QString& name, bool frozen = false,
        bool locked = false, const RColor& color = Qt::black,
        RLinetype::Id linetype = RLinetype::INVALID_ID,
        RLineweight::Lineweight lineweight = RLineweight::Weight000);

    virtual ~RLayer();

    static void init();

    virtual RLayer* clone() const;

    QString getName() const {
        return name;
    }

    void setName(const QString& n);

    bool isFrozen() const {
        return frozen;
    }

    void setFrozen(bool on) {
        frozen = on;
    }

    bool isLocked() const {
        return locked;
    }

    void setLocked(bool on) {
        locked = on;
    }

    RColor getColor() const {
        return color;
    }

    void setColor(const RColor& c) {
        color = c;
    }

    RLinetype::Id getLinetypeId() const {
        return linetype;
    }

    void setLinetypeId(RLinetype::Id lt) {
        linetype = lt;
    }

    RLineweight::Lineweight getLineweight() const {
        return lineweight;
    }

    void setLineweight(RLineweight::Lineweight lw) {
        lineweight = lw;
    }

    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false);
    virtual bool setProperty(RPropertyTypeId propertyTypeId,
            const QVariant& value, RTransaction* transaction=NULL);

    virtual bool isSelectedForPropertyEditing();

private:
    QString name;
    bool frozen;
    bool locked;
    RColor color;
    RLinetype::Id linetype;
    RLineweight::Lineweight lineweight;
};

QCADCORE_EXPORT QDebug operator<<(QDebug dbg, const RLayer& l);

Q_DECLARE_METATYPE(QSharedPointer<RLayer>)
Q_DECLARE_METATYPE(QSharedPointer<RLayer>*)
Q_DECLARE_METATYPE(RLayer)
Q_DECLARE_METATYPE(RLayer*)

#endif
