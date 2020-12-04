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

#ifndef RDOCUMENTVARIABLES_H
#define RDOCUMENTVARIABLES_H

#include "core_global.h"

#include "RLayer.h"
#include "RObject.h"

class RDocument;

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
    static RPropertyTypeId PropertyProtected;
    static RPropertyTypeId PropertyCurrentLayerId;
    static RPropertyTypeId PropertyUnit;
    static RPropertyTypeId PropertyLinetypeScale;
    static RPropertyTypeId PropertyDimensionFont;
    static RPropertyTypeId PropertyWorkingSetBlockReferenceId;

public:
    RDocumentVariables(RDocument* document);
    virtual ~RDocumentVariables();

    static void init();

    virtual RS::EntityType getType() const {
        return RS::ObjectDocumentVariable;
    }

    virtual RDocumentVariables* clone() const {
        return new RDocumentVariables(*this);
    }

    virtual QPair<QVariant, RPropertyAttributes>
            getProperty(RPropertyTypeId& propertyTypeId,
                    bool humanReadable = false,
                    bool noAttributes = false,
                    bool showOnRequest = false);

    virtual bool setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction=NULL);

    void clear();

    QSet<RPropertyTypeId> getCustomPropertyTypeIds() const;
    void setKnownVariable(RS::KnownVariable key, const RVector& value);
    void setKnownVariable(RS::KnownVariable key, const RColor& value);
    void setKnownVariable(RS::KnownVariable key, const QVariant& value);
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
        QVariant v;
        v.setValue((int)u);
        knownVariables.insert(RS::INSUNITS, v);
        unit = u;
    }

    RS::Measurement getMeasurement() const {
        return measurement;
    }

    void setMeasurement(RS::Measurement m) {
        if (m!=RS::Metric && m!=RS::Imperial) {
            return;
        }

        QVariant v;
        v.setValue((int)m);
        knownVariables.insert(RS::MEASUREMENT, v);
        measurement = m;
    }

    double getLinetypeScale() const {
        return linetypeScale;
    }

    void setLinetypeScale(double s) {
        QVariant v;
        v.setValue((double)s);
        knownVariables.insert(RS::LTSCALE, v);
        linetypeScale = s;
    }

    QString getDimensionFont() const {
        return dimensionFont;
    }

    void setDimensionFont(const QString& f) {
        dimensionFont = f;
    }

//    RObject::Id getWorkingSetBlockReferenceId() const {
//        return workingSetBlockReferenceId;
//    }

//    void setWorkingSetBlockReferenceId(RObject::Id id) {
//        workingSetBlockReferenceId = id;
//    }

    QString addAutoVariable(double value);
    QStringList getAutoVariables() const;

    virtual void print(QDebug dbg) const;

private:
    RLayer::Id currentLayerId;
    // TODO:
    //RLayer::Id currentBlockId;
    //...
    RS::Unit unit;
    RS::Measurement measurement;
    double linetypeScale;
    QString dimensionFont;
    QHash<RS::KnownVariable, QVariant> knownVariables;
    // ID of block reference that we are currently editing in-place (current working set):
    RObject::Id workingSetBlockReferenceId;
};

Q_DECLARE_METATYPE(RDocumentVariables*)
Q_DECLARE_METATYPE(QSharedPointer<RDocumentVariables>)
Q_DECLARE_METATYPE(QSharedPointer<RDocumentVariables>*)

#endif
