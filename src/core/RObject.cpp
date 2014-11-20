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
#include <QMetaType>

#include "RBlock.h"
#include "RDocument.h"
#include "RMetaTypes.h"
#include "RLayer.h"
#include "RObject.h"
#include "RPropertyTypeId.h"

const RObject::Id RObject::INVALID_ID = -1;
const RObject::Handle RObject::INVALID_HANDLE = -1;

RPropertyTypeId RObject::PropertyCustom;
RPropertyTypeId RObject::PropertyHandle;
RPropertyTypeId RObject::PropertyProtected;

void RObject::init() {
    RObject::PropertyCustom.generateId(typeid(RObject), "", QT_TRANSLATE_NOOP("RObject", "Custom"));
    RObject::PropertyHandle.generateId(typeid(RObject), "", QT_TRANSLATE_NOOP("RObject", "Handle"));
    RObject::PropertyProtected.generateId(typeid(RObject), "", QT_TRANSLATE_NOOP("RObject", "Protected"));
}

void RObject::setUndone(bool on) {
    undone = on;

    if (document==NULL) {
        return;
    }

    if (on==true) {
        // make sure that the current layer is not undone:
        RLayer* layer = dynamic_cast<RLayer*>(this);
        if (layer!=NULL) {
            if (layer->getId()==document->getCurrentLayerId()) {
                document->setCurrentLayer("0");
            }
        }

        // make sure that the current block is not undone:
        RBlock* block = dynamic_cast<RBlock*>(this);
        if (block!=NULL) {
            if (block->getId()==document->getCurrentBlockId()) {
                document->setCurrentBlock(document->getModelSpaceBlockId());
            }
        }
    }
}

QPair<QVariant, RPropertyAttributes> RObject::getProperty(RPropertyTypeId& propertyTypeId,
        bool humanReadable, bool noAttributes) {

    Q_UNUSED(humanReadable)
    Q_UNUSED(noAttributes)

    if (propertyTypeId == PropertyHandle) {
        return qMakePair(QVariant(handle), RPropertyAttributes(RPropertyAttributes::ReadOnly));
    }
    if (propertyTypeId == PropertyProtected) {
        return qMakePair(QVariant(protect), RPropertyAttributes(RPropertyAttributes::Invisible));
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

bool RObject::setProperty(RPropertyTypeId propertyTypeId,
    const QVariant& value, RTransaction* transaction) {

    bool ret = false;

    ret = ret || RObject::setMember(protect, value, PropertyProtected == propertyTypeId);

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
bool RObject::setMember(bool& variable, const QVariant& value,
        bool condition) {
    if (!condition) {
        return false;
    }
    variable = value.toBool();
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
bool RObject::setMemberVector(QList<RVector>& variable, const QVariant& value,
                         RObject::XYZ xyz) {

    if (!value.canConvert<QList<QPair<int, double> > >()) {
        qWarning() <<
                      QString("RObject::setMemberVector: '%1' is not a QList<QPair<int, double> >").arg(
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
bool RObject::setMember(QList<double>& variable, const QVariant& value,
                         bool condition) {

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
    for (it=pairList.begin(); it!=pairList.end(); ++it) {
        int i = (*it).first;
        double v = (*it).second;

        // entry was removed:
        if (RMath::isNaN(v) && i<variable.size()) {
            variable.removeLast();
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
QSet<RPropertyTypeId> RObject::getPropertyTypeIds() const {
    QSet<RPropertyTypeId> ret = RPropertyTypeId::getPropertyTypeIds(typeid(*this));
    ret.unite(getCustomPropertyTypeIds());
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

/**
 * \return Value of given custom property.
 */
QVariant RObject::getCustomProperty(const QString& title, const QString& key, const QVariant& defaultValue) {
    if (!customProperties.contains(title)) {
        return defaultValue;
    }
    QVariantMap vm = customProperties.value(title);
    return vm.value(key, defaultValue);
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

QStringList RObject::getCustomPropertyTitles() const {
    return customProperties.keys();
}

/**
 * \return List of custom property keys.
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
