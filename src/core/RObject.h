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

#ifndef ROBJECT_H
#define ROBJECT_H

#include "core_global.h"

#include "RPropertyAttributes.h"
#include "RPropertyTypeId.h"

class RDocument;
class RTransaction;

#ifndef RQMapQStringQString
typedef QMap<QString, QString> RQMapQStringQString;
#endif

#ifndef RDEFAULT_QVARIANT
#define RDEFAULT_QVARIANT QVariant()
#endif

#ifndef RDEFAULT_QSTRING
#define RDEFAULT_QSTRING QString()
#endif

#ifndef RDEFAULT_QSTRINGLIST
#define RDEFAULT_QSTRINGLIST QStringList()
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
    static RPropertyTypeId PropertyWorkingSet;
    static RPropertyTypeId PropertySelected;
    static RPropertyTypeId PropertyInvisible;

    enum XYZ {
        X, Y, Z
    };

public:
    enum ObjectFlag {
        NoFlags = 0x000,
        Undone = 0x001,           //!< object is undone
        Protect = 0x002,          //!< object is protected
        Selected = 0x004,         //!< object is selected
        Invisible = 0x008,        //!< object is invisible
        WorkingSet = 0x010        //!< object is part of the current working set
    };
    Q_DECLARE_FLAGS(Flags, ObjectFlag)

public:
    RObject(RDocument* document=NULL);
    RObject(const RObject& other);
    virtual ~RObject();

    static void init();

    virtual RS::EntityType getType() const = 0;

    virtual RObject* clone() const = 0;

    /**
     * \return True to always clone object instead of saving diff when object changes.
     * This can be used for complex object types which cannot be modified using properties.
     */
    virtual bool mustAlwaysClone() const {
        return false;
    }

    RDocument* getDocument() {
        return document;
    }

    const RDocument* getDocument() const {
        return document;
    }

    void setDocument(RDocument* document);

    void setFlag(int flag, bool on = true) {
        if (on) {
            flags |= (ObjectFlag)flag;
        } else {
            flags &= ~(ObjectFlag)flag;
        }
    }
    bool getFlag(int flag) const {
        return (int)(flags & flag) == flag;
    }

    /**
     * \nonscriptable
     */
    template<class T>
    static bool setMember(T& variable, const QVariant& value, bool condition = true) {
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

    bool isProtected() const {
        return getFlag(RObject::Protect);
    }

    void setProtected(bool on) {
        setFlag(RObject::Protect, on);
    }

    bool isInvisible() const {
        return getFlag(RObject::Invisible);
    }

    void setInvisible(bool on) {
        setFlag(RObject::Invisible, on);
    }

    virtual bool isSelected() const {
        return getFlag(RObject::Selected);
    }

    virtual void setSelected(bool on) {
        setFlag(RObject::Selected, on);
    }

    bool isUndone() const {
        return getFlag(RObject::Undone);
    }

    virtual bool isWorkingSet() const {
        return getFlag(RObject::WorkingSet);
    }

    virtual void setWorkingSet(bool on) {
        setFlag(RObject::WorkingSet, on);
    }

    virtual QSet<RPropertyTypeId> getPropertyTypeIds(RPropertyAttributes::Option option = RPropertyAttributes::NoOptions) const;
    virtual QSet<RPropertyTypeId> getCustomPropertyTypeIds() const;

    /**
     * \return The value and attributes of the given property or an invalid
     *      property if this property owner has no property with the given ID.
     */
    virtual QPair<QVariant, RPropertyAttributes> getProperty(RPropertyTypeId& propertyTypeId,
        bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

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

    bool hasCustomProperties() const;
    bool hasCustomProperty(const QString& title, const QString& key) const;

    /**
     * \nonscriptable
     */
    bool hasCustomProperty(const QString& title, const QRegExp& key) const;

    virtual QVariant getCustomProperty(const QString& title, const QString& key, const QVariant& defaultValue = RDEFAULT_QVARIANT) const;
    virtual double getCustomDoubleProperty(const QString& title, const QString& key, double defaultValue) const;
    virtual int getCustomIntProperty(const QString& title, const QString& key, int defaultValue) const;
    virtual bool getCustomBoolProperty(const QString& title, const QString& key, bool defaultValue) const;
    virtual void setCustomProperty(const QString& title, const QString& key, const QVariant& value);

    /**
     * \nonscriptable
     */
    virtual void setCustomProperties(const RQMapQStringQString& properties);
    virtual void removeCustomProperty(const QString& title, const QString& key);
    QStringList getCustomPropertyTitles() const;
    QStringList getCustomPropertyKeys(const QString& title) const;
    void copyCustomPropertiesFrom(
            RObject* other,
            const QString& title = RDEFAULT_QSTRING,
            bool overwrite = false,
            const QStringList& ignoreList = RDEFAULT_QSTRINGLIST,
            const QString& mapKeyFrom = RDEFAULT_QSTRING,
            const QString& mapKeyTo = RDEFAULT_QSTRING);

    static void setCustomPropertyAttributes(const QString& title, const QString& key, const RPropertyAttributes& att);
    static RPropertyAttributes getCustomPropertyAttributes(const QString& title, const QString& key);

    /**
     * \nonscriptable
     */
    QMap<QString, QVariantMap> getCustomProperties() const;

    virtual int getComplexity() const {
        return 0;
    }

    virtual void setAutoUpdatesBlocked(bool on) {
        Q_UNUSED(on)
    }

    void dump() const {
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

    void setUndone(bool on);

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
    bool setMemberFlag(int flag, const QVariant& value, bool condition = true);
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
     * Object flags (undone, protected, ...)
     */
    Flags flags;
    /**
     * AppID -> key -> value
     * e.g. 'QCAD' -> 'wall thickness' -> 12.0;
     * or   'SomeApplication' -> '00001_1000' -> 'SomeString'
     * where '00001' is the position in the list of values and 1000 is the
     * original DXF code from the file.
     */
    QMap<QString, QVariantMap> customProperties;

    /**
     * Attributes of custom properties (read-only, invisible, ...).
     */
    static QMap<QString, QMap<QString, RPropertyAttributes> > customPropertyAttributes;
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
Q_DECLARE_METATYPE(RObject::ObjectFlag)
Q_DECLARE_METATYPE(QFlags<RObject::ObjectFlag>)

#endif
