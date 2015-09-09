/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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

#ifndef ROBJECT_H
#define ROBJECT_H

#include "core_global.h"

#include "RPropertyAttributes.h"
#include "RPropertyTypeId.h"

class RDocument;
class RTransaction;

#ifndef RDEFAULT_QVARIANT
#define RDEFAULT_QVARIANT QVariant()
#endif


/**
 * Abstract base class for all objects. Objects have
 * an unique ID. Object types may register property types.
 * Objects manage their own set of properties.
 * Example objects are entities, layers, user coordinate systems.
 *
 * \sa RPropertyTypeId
 *
 * \ingroup core
 * \scriptable
 * \sharedPointerSupport
 */
class QCADCORE_EXPORT RObject {

    friend class RStorage;

public:
    typedef int Id;
    const static Id INVALID_ID;
    typedef int Handle;
    const static Handle INVALID_HANDLE;

    static RPropertyTypeId PropertyCustom;
    static RPropertyTypeId PropertyType;
    static RPropertyTypeId PropertyHandle;
    static RPropertyTypeId PropertyProtected;

    enum XYZ {
        X, Y, Z
    };

public:

    RObject(RDocument* document=NULL, Id id = INVALID_ID) :
        document(document), objectId(id), handle(INVALID_HANDLE), undone(false), protect(false) {
    }
    virtual ~RObject() {
    }

    static void init();

    virtual RObject* clone() const = 0;

    RDocument* getDocument() {
        return document;
    }

    const RDocument* getDocument() const {
        return document;
    }

    void setDocument(RDocument* document) {
        this->document = document;
    }

    //  static double variantToDouble(const QVariant& v, double defaultValue,
    //          bool ignoreError = true);
    //  static int variantToInt(const QVariant& v, int defaultValue,
    //          bool ignoreError = true);

    /**
     * \nonscriptable
     */
    template<class T>
    static bool setMember(T& variable, const QVariant& value,
        bool condition = true) {

        if (!condition) {
            return false;
        }
        variable = value.value<T> ();
        return true;
    }

    /**
     * \return The ID of the object or -1 if the object has no ID.
     * An object without ID is not stored in the DB and not part of
     * a document.
     */
    RObject::Id getId() const {
        return objectId;
    }

    RObject::Handle getHandle() const {
        return handle;
    }

    virtual RS::EntityType getType() const {
        return RS::ObjectUnknown;
    }

    bool isProtected() const {
        return protect;
    }

    void setProtected(bool on) {
        protect = on;
    }

    bool isUndone() const {
        return undone;
    }

    virtual void setUndone(bool on);

    virtual QSet<RPropertyTypeId> getPropertyTypeIds() const;
    virtual QSet<RPropertyTypeId> getCustomPropertyTypeIds() const;

    /**
     * \return The value and attributes of the given property or an invalid
     *      property if this property owner has no property with the given ID.
     */
    virtual QPair<QVariant, RPropertyAttributes>
            getProperty(RPropertyTypeId& propertyTypeId,
                    bool humanReadable = false,
                    bool noAttributes = false);

    /**
     * Sets the given property to the given value. If this property owner
     * does not know a property with that ID, it is up to the property owner
     * what happens. The property might be added into a list of dynamic properties
     * or dropped.
     *
     * \return True if the property owner was modified in any way, false otherwise.
     */
    virtual bool setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction=NULL);

    /**
     * \return True if this property owner has a property with the given ID,
     *      false otherwise.
     */
    virtual bool hasPropertyType(RPropertyTypeId propertyTypeId) {
        return RPropertyTypeId::hasPropertyType(typeid(*this), propertyTypeId);
    }

    /**
     * \return True if this object is selected for editing. This means
     *      that the properties of this object should for example
     *      be shown in a property editor.
     */
    virtual bool isSelectedForPropertyEditing() = 0;

    bool hasCustomProperties() const;
    bool hasCustomProperty(const QString& title, const QString& key) const;
    QVariant getCustomProperty(const QString& title, const QString& key, const QVariant& defaultValue = RDEFAULT_QVARIANT) const;
    bool getCustomBoolProperty(const QString& title, const QString& key, bool defaultValue) const;
    void setCustomProperty(const QString& title, const QString& key, const QVariant& value);
    void removeCustomProperty(const QString& title, const QString& key);
    QStringList getCustomPropertyTitles() const;
    QStringList getCustomPropertyKeys(const QString& title) const;

    /**
     * \nonscriptable
     */
    QMap<QString, QVariantMap> getCustomProperties() const;

    virtual int getComplexity() const {
        return 0;
    }

    void dump() {
        qDebug() << *this;
    }

    /**
     * \nonscriptable
     */
    friend QDebug operator<<(QDebug dbg, const RObject& o) {
        o.print(dbg);
        return dbg;
    }

protected:
    virtual void print(QDebug dbg) const;

    void setId(RObject::Id id) {
        objectId = id;
    }

    void setHandle(RObject::Handle h) {
        handle = h;
    }

    /**
     * \nonscriptable
     */
    static bool setMember(QString& variable, const QVariant& value, bool condition = true);
    /**
     * \nonscriptable
     */
    static bool setMember(double& variable, const QVariant& value, bool condition = true);
    /**
     * \nonscriptable
     */
    static bool setMember(int& variable, const QVariant& value, bool condition = true);
    /**
     * \nonscriptable
     */
    static bool setMember(bool& variable, const QVariant& value, bool condition = true);
    /**
     * \nonscriptable
     */
    static bool setMember(QList<double>& variable, const QVariant& value, bool condition);
    /**
     * \nonscriptable
     */
    static bool setMemberX(QList<RVector>& variable, const QVariant& value, bool condition = true);
    /**
     * \nonscriptable
     */
    static bool setMemberY(QList<RVector>& variable, const QVariant& value, bool condition = true);
    /**
     * \nonscriptable
     */
    static bool setMemberZ(QList<RVector>& variable, const QVariant& value, bool condition = true);

    /**
     * \nonscriptable
     */
    static bool setMemberVector(QList<RVector>& variable, const QVariant& value, RObject::XYZ xyz);

private:
    RDocument* document;
    /**
     * Unique ID of this object.
     */
    Id objectId;
    /**
     * Handle of this object (from DXF / DWG).
     */
    Handle handle;
    /**
     * True if this object has been undone (deleted).
     */
    bool undone;
    /**
     * True if this object is protected (undeletable).
     */
    bool protect;
    /**
     * AppID -> key -> value
     * e.g. 'QCAD' -> 'wall thickness' -> 12.0;
     * or   'SomeApplication' -> '00001_1000' -> 'SomeString'
     * where '00001' is the position in the list of values and 1000 is the
     * original DXF code from the file.
     */
    QMap<QString, QVariantMap> customProperties;
};

Q_DECLARE_METATYPE(RObject::Id)
Q_DECLARE_METATYPE(RObject::XYZ)
Q_DECLARE_METATYPE(RObject::XYZ*)
Q_DECLARE_METATYPE(QList<QSharedPointer<RObject> >)
Q_DECLARE_METATYPE(QSharedPointer<RObject>)
Q_DECLARE_METATYPE(QSharedPointer<RObject>*)
typedef QMap<int, QSharedPointer<RObject> > _RMapIntObjectPointer;
Q_DECLARE_METATYPE(_RMapIntObjectPointer)
Q_DECLARE_METATYPE(RObject*)

#endif
