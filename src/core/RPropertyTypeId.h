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

#ifndef RPROPERTYTYPEID_H_
#define RPROPERTYTYPEID_H_

#include "core_global.h"

#include <typeinfo>

#include <QMap>
#include <QMetaType>
#include <QSet>
#include <QSharedPointer>
#include <QString>

#include "RDebug.h"
#include "RS.h"
#include "RPropertyAttributes.h"

/**
 * Represents unique property type IDs. Every property type an object can have
 * has such an unique ID.
 *
 * E.g. all objects of type car may have a property
 * type called brand. This property type is uniquely identified by an instance
 * of this class. All instances of this class are automatically unique.
 *
 * \code
 * class QCADCORE_EXPORT Car {
 * public:
 * static RPropertyTypeId propertyBrand;
 * }
 *
 * RPropertyTypeId Car::propertyBrand(typeid(Car));
 * \endcode
 *
 * \ingroup core
 *
 * \scriptable
 * \copyable
 */
class QCADCORE_EXPORT RPropertyTypeId {
public:
    /**
     * \ nonscriptable
     */
    //RPropertyTypeId(const std::type_info& classInfo, const QString& groupTitle,
    //      const QString& title);
    /**
     * \ nonscriptable
     */
    //RPropertyTypeId(const std::type_info& classInfo, const RPropertyTypeId& other);

    RPropertyTypeId(const QString& customPropertyTitle, const QString& customPropertyName);
    RPropertyTypeId(const QString& customPropertyName);

    RPropertyTypeId(const RPropertyTypeId& other);
    RPropertyTypeId(long int id = INVALID_ID);

    long int getId() const;
    void setId(long int id);
    QString getCustomPropertyTitle() const;
    void setCustomPropertyTitle(const QString& t);
    QString getCustomPropertyName() const;
    void setCustomPropertyName(const QString& n);

    bool isValid() const;
    bool isCustom() const;
    //bool isBlockAttribute() const;

//    QString getBlockAttributeTag() const;
//    QString getBlockAttributePrompt() const;
//    QString getBlockAttributeId() const;

    /**
     * \nonscriptable
     */
    void generateId(const std::type_info& classInfo,
        const QString& groupTitle, const QString& title, bool forceNew = false,
        RPropertyAttributes::Options options = RPropertyAttributes::NoOptions);
    /**
     * \nonscriptable
     */
    void generateId(const std::type_info& classInfo, 
        const RPropertyTypeId& other);

    /**
     * \nonscriptable
     */
    static QSet<RPropertyTypeId> getPropertyTypeIds(const std::type_info& classInfo, RPropertyAttributes::Option = RPropertyAttributes::NoOptions);
    /**
     * \nonscriptable
     */
    static bool hasPropertyType(const std::type_info& classInfo,
            RPropertyTypeId propertyTypeId);
    QString getPropertyGroupTitle() const;
    QString getPropertyTitle() const;
    static RPropertyTypeId getPropertyTypeId(const QString& groupTitle,
            const QString& title);

    bool operator ==(const RPropertyTypeId& other) const;
    bool operator !=(const RPropertyTypeId& other) const;
    bool operator <(const RPropertyTypeId& other) const;

public:
    const static long int INVALID_ID;
    //const static QString blockAttributePrefix;

private:
    long int id;
    RPropertyAttributes::Options options;
    QString customPropertyTitle;
    QString customPropertyName;

    static long int counter;

    // maps class ID to set of property IDs:
    static QMap<QString, QSet<RPropertyTypeId> > propertyTypeByObjectMap;

    // maps class ID / option combinations to set of property IDs:
    static QMap<QPair<QString, RPropertyAttributes::Option>, QSet<RPropertyTypeId> > propertyTypeByObjectOptionMap;

    // maps property type IDs to group title / title:
    static QMap<long int, QPair<QString, QString> > idToTitleMap;

    // maps group title / title to property ID:
    static QMap<QString, QMap<QString, RPropertyTypeId> > titleToIdMap;

    static QList<RPropertyAttributes::Option> cachedOptionList;
};

QCADCORE_EXPORT QDebug operator<<(QDebug dbg, const RPropertyTypeId& p);

QCADCORE_EXPORT uint qHash(const RPropertyTypeId& propertyTypeId);

Q_DECLARE_METATYPE(RPropertyTypeId)
Q_DECLARE_METATYPE(RPropertyTypeId*)
Q_DECLARE_METATYPE(const RPropertyTypeId*)
Q_DECLARE_METATYPE(QSet<RPropertyTypeId>)
Q_DECLARE_METATYPE(QList<RPropertyTypeId>)

#endif /* RPROPERTYTYPEID_H_ */
