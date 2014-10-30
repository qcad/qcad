/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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

#ifndef RDOCUMENTVARIABLES_H
#define RDOCUMENTVARIABLES_H

#include "core_global.h"

#include "RDocumentVariables.h"
#include "RLayer.h"
#include "RObject.h"

/**
 * This type of object is used to store document wide variables.
 *
 * \ingroup core
 * \scriptable
 * \sharedPointerSupport
 */
class QCADCORE_EXPORT RDocumentVariables : public RObject {
public:
    static RPropertyTypeId PropertyCustom;
    static RPropertyTypeId PropertyHandle;
    static RPropertyTypeId PropertyCurrentLayerId;
    static RPropertyTypeId PropertyUnit;
    static RPropertyTypeId PropertyLinetypeScale;
    static RPropertyTypeId PropertyDimensionFont;

public:
    RDocumentVariables(RDocument* document, RObject::Id objectId=INVALID_ID);
    virtual ~RDocumentVariables();

    static void init();

    virtual RDocumentVariables* clone() const {
        return new RDocumentVariables(*this);
    }

    virtual bool isSelectedForPropertyEditing() {
        return false;
    }

    virtual QPair<QVariant, RPropertyAttributes>
            getProperty(RPropertyTypeId& propertyTypeId,
                    bool humanReadable = false,
                    bool noAttributes = false);

    virtual bool setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction=NULL);

    void clear();

    QSet<RPropertyTypeId> getCustomPropertyTypeIds() const;
    void setKnownVariable(RS::KnownVariable key, QVariant value);
    QVariant getKnownVariable(RS::KnownVariable key) const;
    bool hasKnownVariable(RS::KnownVariable key) const;

    RLayer::Id getCurrentLayerId() const {
        return currentLayerId;
    }

    void setCurrentLayerId(RLayer::Id id) {
        currentLayerId = id;
    }

    RS::Unit getUnit() const {
        return unit;
    }

    void setUnit(RS::Unit u) {
        unit = u;
    }

    double getLinetypeScale() const {
        return linetypeScale;
    }

    void setLinetypeScale(double s) {
        linetypeScale = s;
    }

    QString getDimensionFont() const {
        return dimensionFont;
    }

    void setDimensionFont(const QString& f) {
        dimensionFont = f;
    }

    virtual void print(QDebug dbg) const;

private:
    RLayer::Id currentLayerId;
    // TODO:
    //RLayer::Id currentBlockId;
    //...
    RS::Unit unit;
    double linetypeScale;
    QString dimensionFont;
    QHash<RS::KnownVariable, QVariant> knownVariables;
};

Q_DECLARE_METATYPE(RDocumentVariables*)
Q_DECLARE_METATYPE(QSharedPointer<RDocumentVariables>)
Q_DECLARE_METATYPE(QSharedPointer<RDocumentVariables>*)

#endif
