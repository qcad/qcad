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
#include <QMetaType>

#include "RBlock.h"
#include "RDocument.h"
#include "RMetaTypes.h"
#include "RLayer.h"
#include "RObject.h"
#include "RPropertyTypeId.h"

const RObject::Id RObject::INVALID_ID = -1;
const RObject::Handle RObject::INVALID_HANDLE = -1;
QMap<QString, QMap<QString, RPropertyAttributes> > RObject::customPropertyAttributes;

RPropertyTypeId RObject::PropertyCustom;
RPropertyTypeId RObject::PropertyType;
RPropertyTypeId RObject::PropertyHandle;
RPropertyTypeId RObject::PropertyProtected;
RPropertyTypeId RObject::PropertyWorkingSet;
RPropertyTypeId RObject::PropertySelected;
RPropertyTypeId RObject::PropertyInvisible;

RObject::RObject(RDocument* document) :
    document(document),
    objectId(INVALID_ID),
    handle(INVALID_HANDLE),
    flags(NoFlags){

    //RDebug::incCounter("RObject");
}

RObject::RObject(const RObject& other) {
    //RDebug::incCounter("RObject");

    document = other.document;
    objectId = other.objectId;
    handle = other.handle;
    flags = other.flags;
    customProperties = other.customProperties;
}

RObject::~RObject() {
    //RDebug::decCounter("RObject");
}

void RObject::setDocument(RDocument* document) {
    this->document = document;
}

void RObject::init() {
    RObject::PropertyCustom.generateId(typeid(RObject), "", QT_TRANSLATE_NOOP("REntity", "Custom"));
    RObject::PropertyType.generateId(typeid(RObject), "", QT_TRANSLATE_NOOP("REntity", "Type"));
    RObject::PropertyHandle.generateId(typeid(RObject), "", QT_TRANSLATE_NOOP("REntity", "Handle"));
    RObject::PropertyProtected.generateId(typeid(RObject), "", QT_TRANSLATE_NOOP("REntity", "Protected"));
    RObject::PropertySelected.generateId(typeid(RObject), "", QT_TRANSLATE_NOOP("REntity", "Selected"));
    RObject::PropertyInvisible.generateId(typeid(RObject), "", QT_TRANSLATE_NOOP("REntity", "Invisible"));
    RObject::PropertyWorkingSet.generateId(typeid(RObject), "", QT_TRANSLATE_NOOP("REntity", "Working Set"));
}

void RObject::setUndone(bool on) {
    //undone = on;
    setFlag(RObject::Undone, on);

    if (document==NULL) {
        return;
    }

    if (on==true) {
        // current layer is undone:
        // change current layer:
        RLayer* layer = dynamic_cast<RLayer*>(this);
        if (layer!=NULL) {
            if (layer->getId()==document->getCurrentLayerId()) {
                document->setCurrentLayer("0");
            }
        }

        // current block is undone:
        // change current block:
        RBlock* block = dynamic_cast<RBlock*>(this);
        if (block!=NULL) {
            if (block->getId()==document->getCurrentBlockId()) {
                document->setCurrentBlock(document->getModelSpaceBlockId());
            }
        }
    }
}

QPair<QVariant, RPropertyAttributes> RObject::getProperty(RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {
    Q_UNUSED(humanReadable)
    Q_UNUSED(noAttributes)
    Q_UNUSED(showOnRequest)

    if (propertyTypeId==PropertyType) {
        return qMakePair(QVariant(getType()), RPropertyAttributes(RPropertyAttributes::ReadOnly));
    }
    else if (propertyTypeId==PropertyHandle) {
        return qMakePair(QVariant(handle), RPropertyAttributes(RPropertyAttributes::ReadOnly));
    }
    else if (propertyTypeId==PropertyProtected) {
        return qMakePair(QVariant(isProtected()), RPropertyAttributes(RPropertyAttributes::ReadOnly));
    }
    else if (propertyTypeId==PropertySelected) {
        return qMakePair(QVariant(isSelected()), RPropertyAttributes(RPropertyAttributes::Invisible));
    }
    else if (propertyTypeId==PropertyInvisible) {
        return qMakePair(QVariant(isInvisible()), RPropertyAttributes(RPropertyAttributes::Invisible));
    }
    else if (propertyTypeId==PropertyWorkingSet) {
        return qMakePair(QVariant(isWorkingSet()), RPropertyAttributes(RPropertyAttributes::Invisible));
    }

    if (propertyTypeId.isCustom()) {
        QString appId = propertyTypeId.getCustomPropertyTitle();
        QString name = propertyTypeId.getCustomPropertyName();
        if (customProperties.contains(appId)) {
            QVariantMap vm = customProperties.value(appId);
            if (vm.contains(name)) {
                RPropertyAttributes attr;
                if  (vm.value(name).type()==QVariant::Int) {
                    attr = RPropertyAttributes(RPropertyAttributes::Custom|RPropertyAttributes::Integer);
                }
                else {
                    attr = RPropertyAttributes(RPropertyAttributes::Custom);
                }
                return qMakePair(vm.value(name), attr);
            }
        }
    }

    return qMakePair(QVariant(), RPropertyAttributes());
}

bool RObject::setProperty(RPropertyTypeId propertyTypeId, const QVariant& value, RTransaction* transaction) {
    Q_UNUSED(transaction)

    bool ret = false;

    ret = ret || RObject::setMemberFlag(RObject::Protect, value, PropertyProtected == propertyTypeId);
    ret = ret || RObject::setMemberFlag(RObject::Selected, value, PropertySelected == propertyTypeId);
    ret = ret || RObject::setMemberFlag(RObject::Invisible, value, PropertyInvisible == propertyTypeId);
    ret = ret || RObject::setMemberFlag(RObject::WorkingSet, value, PropertyWorkingSet == propertyTypeId);

    // set custom property:
    if (propertyTypeId.getId()==RPropertyTypeId::INVALID_ID) {
        if (propertyTypeId.getCustomPropertyTitle().isEmpty() ||
            propertyTypeId.getCustomPropertyName().isEmpty()) {
            qWarning() << "RObject::setProperty: "
                << "cannot set custom property with empty title or name";
            return false;
        }

        if (value.isValid()) {
            setCustomProperty(propertyTypeId.getCustomPropertyTitle(), propertyTypeId.getCustomPropertyName(), value);
        }
        else {
            removeCustomProperty(propertyTypeId.getCustomPropertyTitle(), propertyTypeId.getCustomPropertyName());
        }
        return true;
    }

    //qWarning() << "RObject::setProperty: property not set: " << propertyTypeId.getId();
    return ret;
}

/**
 * Sets the given property.
 * \param variable a reference to the (member) variable we want to set
 * \param value the new value
 * \param condition the variable is only set to the new value if condition is true
 * \retval true: if condition is true and the value was successfully converted
 * to the same type as the variable.
 */
bool RObject::setMember(QString& variable, const QVariant& value,
        bool condition) {
    if (!condition) {
        return false;
    }
    variable = value.toString();
    return true;
}

/**
 * \overload
 */
bool RObject::setMember(double& variable, const QVariant& value,
        bool condition) {
    if (!condition) {
        return false;
    }
    bool ok;
    double d = value.toDouble(&ok);
    if (!ok) {
        qWarning() << QString("RObject::setMember: '%1' is not a double").arg(
                        value.toString());
        return false;
    }
    variable = d;
    return true;
}

/**
 * \overload
 */
bool RObject::setMember(int& variable, const QVariant& value,
        bool condition) {
    if (!condition) {
        return false;
    }
    bool ok;
    int n = value.toInt(&ok);
    if (!ok) {
        qWarning() <<
                QString("RObject::setMember: '%1' is not an integer").arg(
                        value.toString());
        return false;
    }
    variable = n;
    return true;
}

/**
 * \overload
 */
bool RObject::setMember(bool& variable, const QVariant& value, bool condition) {
    if (!condition) {
        return false;
    }
    variable = value.toBool();
    return true;
}

/**
 * \overload
 */
bool RObject::setMemberFlag(int flag, const QVariant& value, bool condition) {
    if (!condition) {
        return false;
    }
    setFlag(flag, value.toBool());
    return true;
}

/**
 * \param value A list of int / double pairs: QList<QPair<int, double> >
 *      representing indexes in the list and values.
 */
bool RObject::setMemberX(QList<RVector>& variable, const QVariant& value,
        bool condition) {

    if (!condition) {
        return false;
    }

    return setMemberVector(variable, value, RObject::X);
}

/**
 * \param value A list of int / double pairs: QList<QPair<int, double> >
 *      representing indexes in the list and values.
 */
bool RObject::setMemberY(QList<RVector>& variable, const QVariant& value,
                         bool condition) {

    if (!condition) {
        return false;
    }

    return setMemberVector(variable, value, RObject::Y);
}

/**
 * \param value A list of int / double pairs: QList<QPair<int, double> >
 *      representing indexes in the list and values.
 */
bool RObject::setMemberZ(QList<RVector>& variable, const QVariant& value,
                         bool condition) {

    if (!condition) {
        return false;
    }

    return setMemberVector(variable, value, RObject::Z);
}


/**
 * \param value A QList of QPairs of int and double where the int is the index and
 *      the double the value.
 */
bool RObject::setMemberVector(QList<RVector>& variable, const QVariant& value, RObject::XYZ xyz) {
    // list might change to invalid (e.g. for spline with fit points, converted to spline with control points):
    if (!value.isValid()) {
        variable.clear();
        return true;
    }

    if (!value.canConvert<QList<QPair<int, double> > >()) {
        qWarning() << "RObject::setMemberVector: '" << value << "' is not a QList<QPair<int, double> >";
        return false;
    }

    QList<QPair<int, double> > pairList = value.value<QList<QPair<int, double> > >();
    QList<QPair<int, double> >::iterator it;
    int offset = 0;
    for (it=pairList.begin(); it!=pairList.end(); ++it) {
        int i = (*it).first;
        double v = (*it).second;

        // entry was removed:
        if (RMath::isNaN(v) && i-offset<variable.size()) {
            variable.removeLast();
            offset++;
        }

        // entry was added:
        else if (i>=variable.size()) {
            switch (xyz) {
            case RObject::X:
                variable.append(RVector(v, 0.0, 0.0));
                break;
            case RObject::Y:
                variable.append(RVector(0.0, v, 0.0));
                break;
            case RObject::Z:
                variable.append(RVector(0.0, 0.0, v));
                break;
            }
        }

        // entry was changed:
        else if (i<variable.size()) {
            switch (xyz) {
            case RObject::X:
                variable[i].x = v;
                break;
            case RObject::Y:
                variable[i].y = v;
                break;
            case RObject::Z:
                variable[i].z = v;
                break;
            }
        }

        else {
            Q_ASSERT(false);
        }
    }

    return true;
}

/**
 * \param value A list for int / double pairs: QList<QPair<int, double> >
 */
bool RObject::setMember(QList<double>& variable, const QVariant& value, bool condition) {
    if (!condition) {
        return false;
    }
    if (!value.canConvert<QList<QPair<int, double> > >()) {
        qWarning() <<
                      QString("RObject::setMember: '%1' is not a QList<QPair<int, double> >").arg(
                          value.toString());
        return false;
    }

    QList<QPair<int, double> > pairList = value.value<QList<QPair<int, double> > >();
    QList<QPair<int, double> >::iterator it;

    int offset = 0;
    for (it=pairList.begin(); it!=pairList.end(); ++it) {
        int i = (*it).first;
        double v = (*it).second;

        // entry was removed:
        if (RMath::isNaN(v) && i-offset<variable.size()) {
            variable.removeLast();
            offset++;
        }

        // entry was added:
        else if (i>=variable.size()) {
            variable.append(v);
        }

        // entry was changed:
        else if (i<variable.size()) {
            variable[i] = v;
        }

        else {
            Q_ASSERT(false);
        }
    }

    return true;
}

/**
 * \return A set of all property IDs of properties that are available for this
 *      object.
 *      The IDs that are returned can be translated into a group title and
 *      a property title using \ref getPropertyGroupTitle and \ref getPropertyTitle.
 */
QSet<RPropertyTypeId> RObject::getPropertyTypeIds(RPropertyAttributes::Option option) const {
    QSet<RPropertyTypeId> ret = RPropertyTypeId::getPropertyTypeIds(typeid(*this), option);
    if (option==RPropertyAttributes::NoOptions) {
        ret.unite(getCustomPropertyTypeIds());
    }
    return ret;
}

/**
 * \return A set of all custom property IDs of properties that are available
 *      for this object.
 */
QSet<RPropertyTypeId> RObject::getCustomPropertyTypeIds() const {
    QSet<RPropertyTypeId> ret;

    QMap<QString, QVariantMap>::const_iterator it;
    for (it=customProperties.begin(); it!=customProperties.end(); it++) {
        QString title = it.key();
        QVariantMap vm = it.value();
        QVariantMap::const_iterator it2;
        for (it2=vm.begin(); it2!=vm.end(); it2++) {
            QString name = it2.key();
            ret.insert(RPropertyTypeId(title, name));
        }
    }

    return ret;
}

bool RObject::hasCustomProperties() const {
    return !customProperties.isEmpty();
}

bool RObject::hasCustomProperty(const QString& title, const QString& key) const {
    if (!customProperties.contains(title)) {
        return false;
    }
    return customProperties.value(title).contains(key);
}

bool RObject::hasCustomProperty(const QString& title, const QRegExp& key) const {
    if (!customProperties.contains(title)) {
        return false;
    }
    QStringList keys = customProperties.value(title).keys();
    int i = keys.indexOf(key, 0);
    if (i==-1) {
        return false;
    }
    return true;
}

/**
 * \return Value of given custom property or the given default
 * value if no such property exists.
 */
QVariant RObject::getCustomProperty(const QString& title, const QString& key, const QVariant& defaultValue) const {
    if (!customProperties.contains(title)) {
        return defaultValue;
    }
    QVariantMap vm = customProperties.value(title);
    return vm.value(key, defaultValue);
}

double RObject::getCustomDoubleProperty(const QString& title, const QString& key, double defaultValue) const {
    QVariant ret = getCustomProperty(title, key, defaultValue);
    if (ret.type()==QVariant::Double ||
        ret.type()==QVariant::Int || ret.type()==QVariant::UInt ||
        ret.type()==QVariant::LongLong || ret.type()==QVariant::ULongLong) {

        return ret.toDouble();
    }
    if (ret.type()==QVariant::String) {
        QString s = ret.toString();
        bool ok;
        double d = s.toDouble(&ok);
        if (ok) {
            return d;
        }
    }
    return defaultValue;
}

int RObject::getCustomIntProperty(const QString& title, const QString& key, int defaultValue) const {
    QVariant ret = getCustomProperty(title, key, defaultValue);
    if (ret.type()==QVariant::Int) {
        return ret.toInt();
    }
    if (ret.type()==QVariant::String) {
        QString s = ret.toString();
        bool ok;
        int i = s.toInt(&ok);
        if (ok) {
            return i;
        }
    }
    return defaultValue;
}

bool RObject::getCustomBoolProperty(const QString& title, const QString& key, bool defaultValue) const {
    QVariant ret = getCustomProperty(title, key, defaultValue);
    if (ret.type()==QVariant::Bool) {
        return ret.toBool();
    }
    if (ret.type()==QVariant::String) {
        QString s = ret.toString().toLower();
        return s=="true" || s=="1";
    }
    return defaultValue;
}

/**
 * Sets a custom property with the given name.
 */
void RObject::setCustomProperty(const QString& title, const QString& key, const QVariant& value) {
    if (!customProperties.contains(title)) {
        customProperties.insert(title, QVariantMap());
    }
    customProperties[title].insert(key, value);
}

void RObject::setCustomProperties(const RQMapQStringQString& properties) {
    QStringList propertyNames = properties.keys();
    for (int i=0; i<propertyNames.length(); i++) {
        QString name = propertyNames[i];
        QString value = properties[name];
        setCustomProperty(RSettings::getAppId(), name, value);
    }
}

/**
 * Removes the custom property with the given name.
 */
void RObject::removeCustomProperty(const QString& title, const QString& key) {
    if (!customProperties.contains(title)) {
        return;
    }
    customProperties[title].remove(key);
    if (customProperties[title].isEmpty()) {
        customProperties.remove(title);
    }
}

/**
 * \return List of custom property titles. These are typically names of applications
 * which have assigned custom properties to this object.
 */
QStringList RObject::getCustomPropertyTitles() const {
    return customProperties.keys();
}

/**
 * \return List of custom property keys for the given title (application).
 */
QStringList RObject::getCustomPropertyKeys(const QString& title) const {
    if (!customProperties.contains(title)) {
        return QStringList();
    }
    return customProperties.value(title).keys();
}

/**
 * \return Map of custom properties assigned to this object.
 */
QMap<QString, QVariantMap> RObject::getCustomProperties() const {
    return customProperties;
}

/**
 * Copies all custom properties from the given object.
 * Existing properties can be overwritten.
 */
void RObject::copyCustomPropertiesFrom(RObject* other, const QString& title,
                                       bool overwrite, const QStringList& ignoreList,
                                       const QString& mapKeyFrom, const QString& mapKeyTo) {
    QMap<QString, QVariantMap> otherProperties = other->getCustomProperties();
    QMap<QString, QVariantMap>::iterator it;
    for (it=otherProperties.begin(); it!=otherProperties.end(); it++) {
        QString otherTitle = it.key();
        QVariantMap otherMap = it.value();

        if (title.isNull() || otherTitle==title) {
            QVariantMap::iterator it2;
            for (it2=otherMap.begin(); it2!=otherMap.end(); it2++) {
                QString otherKey = it2.key();
                QVariant otherValue = it2.value();

                if (!mapKeyFrom.isEmpty()) {
                    otherKey.replace(mapKeyFrom, mapKeyTo);
                }

                if (!overwrite) {
                    if (customProperties[title].contains(otherKey)) {
                        continue;
                    }
                }

                if (ignoreList.contains(otherKey)) {
                    continue;
                }

                customProperties[title][otherKey] = otherValue;
            }
        }
    }
}

/**
 * Set attributes (read-only, invisible, ...) for the given custom property.
 */
void RObject::setCustomPropertyAttributes(const QString& title, const QString& key, const RPropertyAttributes& att) {
    if (!customPropertyAttributes.contains(title)) {
        customPropertyAttributes.insert(title, QMap<QString, RPropertyAttributes>());
    }
    customPropertyAttributes[title].insert(key, att);
}

/**
 * \return attributes (read-only, invisible, ...) for the given custom property.
 */
RPropertyAttributes RObject::getCustomPropertyAttributes(const QString& title, const QString& key) {
    if (customPropertyAttributes.contains(title)) {
        if (customPropertyAttributes[title].contains(key)) {
            return customPropertyAttributes[title].value(key);
        }
    }

    return RPropertyAttributes();
}

/**
 * Stream operator for QDebug
 */
void RObject::print(QDebug dbg) const {
    dbg.nospace() << "RObject("
            << "id: " << getId()
            << ", handle: " << QString("0x%1").arg(getHandle(), 0, 16)
            << ", document: " << QString("0x%1").arg((long int)document, 0, 16)
            << ", address: " << QString("0x%1").arg((long int) this, 0, 16)
            << ", undone: " << (int)isUndone()
            << ", protected: " << (int)isProtected()
            << ", selected: " << (int)isSelected()
            << ", working set: " << (int)isWorkingSet()
            << ")";

    if (!customProperties.isEmpty()) {
        dbg.nospace() << "\nCustom Properties:\n";

        QMap<QString, QVariantMap>::const_iterator titleIt;
        for (titleIt=customProperties.begin(); titleIt!=customProperties.end(); titleIt++) {
            dbg.nospace() << titleIt.key() << ":\n";
            QVariantMap vm = titleIt.value();
            QVariantMap::const_iterator keyIt;
            for (keyIt=vm.begin(); keyIt!=vm.end(); keyIt++) {
                dbg.nospace() << keyIt.key() << ": " << keyIt.value() << "\n";
            }
        }
    }
}
