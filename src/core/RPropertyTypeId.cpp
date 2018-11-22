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
#include <QDebug>

#include "RPropertyTypeId.h"
#include "RPropertyAttributes.h"
//#include "RObject.h"

long int RPropertyTypeId::counter = 0;
const long int RPropertyTypeId::INVALID_ID = -1;
//const QString RPropertyTypeId::blockAttributePrefix = "[[QCAD BLOCK ATTRIBUTE]]";

QMap<QString, QSet<RPropertyTypeId> > RPropertyTypeId::propertyTypeByObjectMap;
QMap<QPair<QString, RPropertyAttributes::Option>, QSet<RPropertyTypeId> > RPropertyTypeId::propertyTypeByObjectOptionMap;
QMap<long int, QPair<QString, QString> > RPropertyTypeId::idToTitleMap;
QMap<QString, QMap<QString, RPropertyTypeId> > RPropertyTypeId::titleToIdMap;

QList<RPropertyAttributes::Option> RPropertyTypeId::cachedOptionList;


RPropertyTypeId::RPropertyTypeId(const QString& customPropertyTitle, const QString& customPropertyName) :
    id(-1), options(false), customPropertyTitle(customPropertyTitle), customPropertyName(customPropertyName) {

}

RPropertyTypeId::RPropertyTypeId(const QString& customPropertyName) :
    id(-1), options(false), customPropertyName(customPropertyName) {

}

RPropertyTypeId::RPropertyTypeId(const RPropertyTypeId& other) {
    id = other.id;
    options = other.options;
    customPropertyTitle = other.customPropertyTitle;
    customPropertyName = other.customPropertyName;
}

RPropertyTypeId::RPropertyTypeId(long int id) :
    id(id), options(false) {
}

void RPropertyTypeId::generateId(const std::type_info& classInfo,
        const QString& groupTitle, const QString& title, bool forceNew, RPropertyAttributes::Options options) {

    if (cachedOptionList.isEmpty()) {
        cachedOptionList.append(RPropertyAttributes::Location);
        cachedOptionList.append(RPropertyAttributes::RefPoint);
        cachedOptionList.append(RPropertyAttributes::Geometry);
    }

    if (id!=-1) {
        qWarning() << "RPropertyTypeId::generateId: property already initialized: " << classInfo.name() << ":" << groupTitle << ":" << title;
        return;
    }

    if (!forceNew && getPropertyTypeId(groupTitle, title).isValid()) {
        RPropertyTypeId pid = getPropertyTypeId(groupTitle, title);
        pid.options = options;
        generateId(classInfo, pid);
        return;
    }

    id = counter++;
    this->options = options;
    propertyTypeByObjectMap[classInfo.name()].insert(*this);
    if (this->options!=RPropertyAttributes::NoOptions) {
        for (int i=0; i<cachedOptionList.length(); i++) {
            propertyTypeByObjectOptionMap[QPair<QString, RPropertyAttributes::Option>(classInfo.name(), cachedOptionList[i])].insert(*this);
        }
    }
    idToTitleMap[id].first = groupTitle;
    idToTitleMap[id].second = title;

    if (!titleToIdMap.contains(groupTitle)) {
        titleToIdMap.insert(groupTitle, QMap<QString, RPropertyTypeId>());
    }

    if (!titleToIdMap[groupTitle].contains(title)) {
        titleToIdMap[groupTitle].insert(title, *this);
    }
//    else {
//        qWarning() << "duplicate property ID: " << groupTitle << "/" << title
//                   << " class: " << classInfo.name();
//    }
}

void RPropertyTypeId::generateId(const std::type_info& classInfo,
        const RPropertyTypeId& other) {
    if (id!=-1) {
        qWarning("RPropertyTypeId::generateId: property already initialized");
        return;
    }

    id = other.id;
    options = other.options;
    propertyTypeByObjectMap[classInfo.name()].insert(*this);
    if (options!=RPropertyAttributes::NoOptions) {
        for (int i=0; i<cachedOptionList.length(); i++) {
            propertyTypeByObjectOptionMap[QPair<QString, RPropertyAttributes::Option>(classInfo.name(), cachedOptionList[i])].insert(*this);
        }
    }
}

RPropertyTypeId RPropertyTypeId::getPropertyTypeId(const QString& groupTitle, const QString& title) {

    if (titleToIdMap.contains(groupTitle)) {
        if (titleToIdMap[groupTitle].contains(title)) {
            return titleToIdMap[groupTitle][title];
        }
    }

//    QMap<long int, QPair<QString, QString> >::iterator i;
//    for (i = idToTitleMap.begin(); i != idToTitleMap.end(); ++i) {
//        if (i.value().first == groupTitle && i.value().second == title) {
//            return RPropertyTypeId(i.key());
//        }
//    }

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
        return idToTitleMap[id].first;
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
        return idToTitleMap[id].second;
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
 * \param geometryOnly Only return geometric properties
 *
 * \return a set of property type ID pointers or an empty set if
 * the class has no registered property types.
 */
QSet<RPropertyTypeId> RPropertyTypeId::getPropertyTypeIds(const std::type_info& classInfo, RPropertyAttributes::Option option) {
    if (option!=RPropertyAttributes::NoOptions) {
        QPair<QString, RPropertyAttributes::Option> pair(classInfo.name(), option);
        if (propertyTypeByObjectOptionMap.contains(pair)) {
            return propertyTypeByObjectOptionMap[pair];
        }
        qWarning() << QString("RPropertyIdRegistry::getPropertyTypeIds: "
                              "no properties with option %1 registered for class %2")
                      .arg(option).arg(classInfo.name());
    }
    else {
        if (propertyTypeByObjectMap.contains(classInfo.name())) {
            return propertyTypeByObjectMap[classInfo.name()];
        }
        qWarning() << QString("RPropertyIdRegistry::getPropertyTypeIds: "
                              "no properties registered for class %1")
                      .arg(classInfo.name());
    }

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

uint qHash(const RPropertyTypeId& propertyTypeId) {
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
