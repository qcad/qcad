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
#include "RPropertyTypeId.h"
#include "RObject.h"

long int RPropertyTypeId::counter = 0;
const long int RPropertyTypeId::INVALID_ID = -1;
//const QString RPropertyTypeId::blockAttributePrefix = "[[QCAD BLOCK ATTRIBUTE]]";

QMap<QString, QSet<RPropertyTypeId> > RPropertyTypeId::propertyTypeByObjectMap;
QMap<long int, QPair<QString, QString> > RPropertyTypeId::titleMap;



RPropertyTypeId::RPropertyTypeId(const QString& customPropertyTitle, const QString& customPropertyName) :
    id(-1), customPropertyTitle(customPropertyTitle), customPropertyName(customPropertyName) {

}

RPropertyTypeId::RPropertyTypeId(const QString& customPropertyName) :
    id(-1), customPropertyName(customPropertyName) {

}

RPropertyTypeId::RPropertyTypeId(const RPropertyTypeId& other) {
    id = other.id;
    customPropertyTitle = other.customPropertyTitle;
    customPropertyName = other.customPropertyName;
}

RPropertyTypeId::RPropertyTypeId(long int id) {
    this->id = id;
}

void RPropertyTypeId::generateId(const std::type_info& classInfo,
        const QString& groupTitle, const QString& title, bool forceNew) {
    if (id!=-1) {
        qWarning("RPropertyTypeId::generateId: property already initialized");
        return;
    }

    if (getPropertyTypeId(groupTitle, title).isValid() && !forceNew) {
        generateId(classInfo, getPropertyTypeId(groupTitle, title));
        return;
    }

    id = counter++;
    propertyTypeByObjectMap[classInfo.name()].insert(*this);
    titleMap[id].first = groupTitle;
    titleMap[id].second = title;
}

void RPropertyTypeId::generateId(const std::type_info& classInfo,
        const RPropertyTypeId& other) {
    if (id!=-1) {
        qWarning("RPropertyTypeId::generateId: property already initialized");
        return;
    }

    id = other.id;
    propertyTypeByObjectMap[classInfo.name()].insert(*this);
}

RPropertyTypeId RPropertyTypeId::getPropertyTypeId(const QString& groupTitle,
        const QString& title) {

    QMap<long int, QPair<QString, QString> >::iterator i;
    for (i = titleMap.begin(); i != titleMap.end(); ++i) {
        if (i.value().first == groupTitle && i.value().second == title) {
            return RPropertyTypeId(i.key());
        }
    }

    return RPropertyTypeId(-1);
}

/**
 * \return The property group title of the given property.
 */
QString RPropertyTypeId::getPropertyGroupTitle() const {
    // TODO: make translatable
//    if (isBlockAttribute()) {
//        return "Block Attributes";
//    }
//    else
    if (isCustom()) {
        if (!customPropertyTitle.isEmpty()) {
            return customPropertyTitle;
        }
        return QT_TRANSLATE_NOOP("REntity", "Custom");
    }
    else {
        return titleMap[id].first;
    }
}

/**
 * \return The property title of the given property.
 */
QString RPropertyTypeId::getPropertyTitle() const {
    if (isCustom()) {
        return customPropertyName;
    }
    else {
        return titleMap[id].second;
    }
}

bool RPropertyTypeId::isValid() const {
    return id!=INVALID_ID || !customPropertyName.isEmpty();
}

bool RPropertyTypeId::isCustom() const {
    return id==INVALID_ID && !customPropertyName.isEmpty();
}

//bool RPropertyTypeId::isBlockAttribute() const {
//    return isCustom() && customPropertyName.startsWith(RPropertyTypeId::blockAttributePrefix);
//}

//QString RPropertyTypeId::getBlockAttributeTag() const {
//    if (!isBlockAttribute()) {
//        return "";
//    }

//    QStringList parts = customPropertyName.split("|||");
//    if (parts.length()!=3) {
//        return "";
//    }
//    return parts[0];
//}

//QString RPropertyTypeId::getBlockAttributePrompt() const {
//    if (!isBlockAttribute()) {
//        return "";
//    }

//    QStringList parts = customPropertyName.split("|||");
//    if (parts.length()!=3) {
//        return "";
//    }
//    return parts[1];
//}

//QString RPropertyTypeId::getBlockAttributeId() const {
//    if (!isBlockAttribute()) {
//        return "";
//    }

//    QStringList parts = customPropertyName.split("|||");
//    if (parts.length()!=3) {
//        return "";
//    }
//    return parts[2];
//}

/**
 * \return The internal ID of this property.
 */
long int RPropertyTypeId::getId() const {
    return id;
}

void RPropertyTypeId::setId(long int id) {
    this->id = id;
}

QString RPropertyTypeId::getCustomPropertyTitle() const {
    return customPropertyTitle;
}

void RPropertyTypeId::setCustomPropertyTitle(const QString& t) {
    customPropertyTitle = t;
}

/**
 * \return The name (key) of the custom property.
 */
QString RPropertyTypeId::getCustomPropertyName() const {
//    if (isBlockAttribute()) {
//        return customPropertyName.mid(RPropertyTypeId::blockAttributePrefix.length());
//    }
    return customPropertyName;
}

void RPropertyTypeId::setCustomPropertyName(const QString& n) {
    customPropertyName = n;
}

/**
 * \retval true: if the given class has the given property
 */
bool RPropertyTypeId::hasPropertyType(const std::type_info& classInfo,
        RPropertyTypeId propertyTypeId) {

    if (!propertyTypeByObjectMap.contains(classInfo.name())) {
        return false;
    }
    return propertyTypeByObjectMap[classInfo.name()].contains(propertyTypeId);
}

/**
 * Gets all property type IDs that where registered for the given
 * class.
 *
 * \param classInfo The class info, e.g. typeid(ObjectA)
 *
 * \return a set of property type ID pointers or an empty set if
 * the class has no registered property types.
 */
QSet<RPropertyTypeId> RPropertyTypeId::getPropertyTypeIds(
        const std::type_info& classInfo) {
    if (propertyTypeByObjectMap.contains(classInfo.name())) {
        return propertyTypeByObjectMap[classInfo.name()];
    }

    qWarning() << QString("RPropertyIdRegistry::getPropertyTypeIds: "
                          "no properties registered for class %1")
                  .arg(classInfo.name());
    return QSet<RPropertyTypeId> ();
}


/**
 * == operator
 */
bool RPropertyTypeId::operator ==(const RPropertyTypeId& other) const {
    if (id!=INVALID_ID) {
        return id == other.id;
    }
    else {
        return id == other.id &&
            customPropertyName==other.customPropertyName &&
            customPropertyTitle==other.customPropertyTitle;
    }
}

/**
 * != operator
 */
bool RPropertyTypeId::operator !=(const RPropertyTypeId& other) const {
    return !operator ==(other);
}

/**
 * < operator
 */
bool RPropertyTypeId::operator <(const RPropertyTypeId& other) const {
    if (id!=INVALID_ID && other.id!=INVALID_ID) {
        return id < other.id;
    }
    else {
        return customPropertyTitle < other.customPropertyTitle ||
            (customPropertyTitle == other.customPropertyTitle &&
             customPropertyName < other.customPropertyName);
    }
}

uint qHash(RPropertyTypeId propertyTypeId) {
    if (propertyTypeId.getId()!=RPropertyTypeId::INVALID_ID) {
        return qHash(propertyTypeId.getId());
    }
    else {
        return qHash(propertyTypeId.getCustomPropertyTitle() + "///" + propertyTypeId.getCustomPropertyName());
    }
}

QDebug operator<<(QDebug dbg, const RPropertyTypeId& p) {
    dbg.nospace()
        << "RPropertyTypeId("
        << p.getId() << ", "
        << p.getCustomPropertyTitle() << ", "
        << p.getCustomPropertyName() << ", "
        << p.getPropertyGroupTitle() << ", "
        << p.getPropertyTitle()
        << ")";
    return dbg.space();
}
