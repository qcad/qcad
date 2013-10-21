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
#include "RGlobal.h"
#include "RDebug.h"
#include "RMetaTypes.h"
#include "RMath.h"
#include "RMainWindow.h"
#include "RPropertyEditor.h"
#include "RPropertyEvent.h"
#include "RDocument.h"
#include "RObject.h"
#include "RColor.h"

/**
 * Default Constructor.
 */
RPropertyEditor::RPropertyEditor() {
    guiUpToDate = false;
    updatesDisabled = false;
}

/**
 * Destructor
 */
RPropertyEditor::~RPropertyEditor() {
}

/**
 * Sets the property with the given name to the given value or to 'mixed'
 * if that property exists already with a different value.
 *
 * \param propertyTypeId: Id of the property in the format "Group|Property".
 * \param property: Value and attributes of the property.
 */
void RPropertyEditor::updateProperty(const RPropertyTypeId& propertyTypeId,
        RObject& object, RDocument* document) {

    RPropertyTypeId pid = propertyTypeId;

    QString propertyGroupTitle = propertyTypeId.getPropertyGroupTitle();
    QString propertyTitle = propertyTypeId.getPropertyTitle();

    if (guiUpToDate) {
        combinedProperties.clear();
        guiUpToDate = false;
    }

    // existing group:
    if (combinedProperties.count(propertyGroupTitle) > 0) {
        RPropertyMap& propertyMap = combinedProperties[propertyGroupTitle];

        // existing property in existing group:
        if (propertyMap.count(propertyTitle) > 0) {
            QPair<QVariant, RPropertyAttributes> property =
                object.getProperty(pid, true, true);

            // mixed value:
            if (!RS::compare(propertyMap[propertyTitle], property)) {
                propertyMap[propertyTitle].first = property.first;
                propertyMap[propertyTitle].second.setMixed(true);
            }
        } else {
            // new property in existing group:
            QPair<QVariant, RPropertyAttributes> property =
                object.getProperty(pid, true);
            if (property.second.isInvisible()) {
                return;
            }
            property.second.setPropertyTypeId(propertyTypeId);
            propertyMap[propertyTitle] = property;
            propertyOrder[propertyGroupTitle].push_back(propertyTitle);
        }
    } else {
        // new property in new group:
        QPair<QVariant, RPropertyAttributes> property = object.getProperty(pid,
                document, true);
        if (property.second.isInvisible()) {
            return;
        }
        property.second.setPropertyTypeId(propertyTypeId);
        RPropertyMap propertyMap;
        propertyMap[propertyTitle] = property;
        combinedProperties[propertyGroupTitle] = propertyMap;
        groupOrder.push_back(propertyGroupTitle);
        propertyOrder[propertyGroupTitle].push_back(propertyTitle);
    }
}

/**
 * Removes all but the given properties from the combined properties
 * collected so far.
 */
void RPropertyEditor::removeAllButThese(
        const QMultiMap<QString, QString>& propertyTitles, bool customOnly) {

    // iterate through all groups of properties (e.g. "Start Point", "End Point", ...):
    QStringList removableGroups;
    RPropertyGroupMap::iterator it;
    for (it = combinedProperties.begin(); it != combinedProperties.end(); ++it) {

        // iterate through all properties in the current group (e.g. "X", "Y"):
        QStringList removableProperties;
        RPropertyMap::iterator it2;
        for (it2 = it.value().begin(); it2 != it.value().end(); ++it2) {
            if (customOnly && !it2.value().second.getPropertyTypeId().isCustom()) {
                continue;
            }

            bool keep = false;

            // check if the current property is among the given properties
            // we want to keep:
            QMultiMap<QString, QString>::const_iterator it3;
            for (it3 = propertyTitles.begin(); it3 != propertyTitles.end(); ++it3) {
                if (it3.key() == it.key() && it3.value() == it2.key()) {
                    keep = true;
                    break;
                }
            }

            if (keep == false) {
                // schedule property for removal:
                removableProperties.push_back(it2.key());
            }
        }

        // remove all properties in the current group that are scheduled for removal:
        QStringList::iterator it4;
        for (it4 = removableProperties.begin(); it4
                != removableProperties.end(); ++it4) {
            it.value().remove(*it4);
            propertyOrder[it.key()].removeAll(*it4);
        }

        // schedule empty groups for removal:
        if (it.value().empty()) {
            removableGroups.push_back(it.key());
        }
    }

    // remove all groups that are scheduled for removal:
    QStringList::iterator it5;
    for (it5 = removableGroups.begin(); it5 != removableGroups.end(); ++it5) {
        combinedProperties.remove(*it5);
        groupOrder.removeAll(*it5);
    }
}

/**
 * Updates the property editor to contain the properties of the
 * objects that are selected for editing in the given document.
 */
void RPropertyEditor::updateFromDocument(RDocument* document,
    bool onlyChanges, RS::EntityType entityTypeFilter) {

    if (updatesDisabled) {
        return;
    }

    if (document == NULL) {
        clearEditor();
        return;
    }

    combinedProperties.clear();
    combinedTypes.clear();
    propertyOrder.clear();
    groupOrder.clear();

    updatesDisabled = true;

    // add all properties of the entities in the given document:
    QSet<RObject::Id> entityIds = document->querySelectedEntities();
    QSet<RObject::Id>::iterator it;
    for (it = entityIds.begin(); it != entityIds.end(); ++it) {
        QSharedPointer<REntity> entity = document->queryEntityDirect(*it);
        if (entity.isNull()) {
            continue;
        }
        if (entityTypeFilter!=RS::EntityAll && entity->getType()!=entityTypeFilter) {
            continue;
        }

        updateEditor(*entity.data(), false, document);
    }

    // remove properties that are not shared by all selected entities:
    for (it = entityIds.begin(); it != entityIds.end(); ++it) {
        QSharedPointer<REntity> entity = document->queryEntityDirect(*it);
        if (entity.isNull()) {
            continue;
        }

        QPair<QVariant, RPropertyAttributes> p = entity->getProperty(REntity::PropertyType);
        RS::EntityType type = (RS::EntityType)p.first.toInt();

        if (entityTypeFilter!=RS::EntityAll && entity->getType()!=entityTypeFilter) {
            continue;
        }

        bool customOnly = false;
        QSet<RPropertyTypeId> propertyTypeIds;
        if (combinedTypes.contains(type)) {
            // already filtered out property type IDs of this type,
            // only look into custom properties:
            propertyTypeIds = entity->getCustomPropertyTypeIds();
            customOnly = true;
            //propertyTypeIds = entity->getPropertyTypeIds();
        }
        else {
            // not filtered out this type yet, look into all properties:
            propertyTypeIds = entity->getPropertyTypeIds();
        }

        if (!propertyTypeIds.isEmpty()) {
            QMultiMap<QString, QString> propertiesToKeep;
            QSet<RPropertyTypeId>::iterator it;
            for (it = propertyTypeIds.begin(); it != propertyTypeIds.end(); ++it) {
                propertiesToKeep.insert(it->getPropertyGroupTitle(),
                                        it->getPropertyTitle());
            }
            removeAllButThese(propertiesToKeep, customOnly);
        }

        if (combinedTypes.contains(type)) {
            combinedTypes[type]++;
        }
        else {
            combinedTypes.insert(type, 1);
        }
    }

    updateGui(onlyChanges, entityTypeFilter);

    updatesDisabled = false;
}

/**
 * Implements update from RPropertyListener.
 */
void RPropertyEditor::updateFromObject(RObject* object, RDocument* document) {
    if (object != NULL) {
        updateEditor(*object, true, document);
    }
}

/**
 * Updates the property widget to include the properties of the given property owner.
 */
void RPropertyEditor::updateEditor(RObject& object, bool doUpdateGui,
        RDocument* document) {
    QList<RPropertyTypeId> propertyTypeIds = object.getPropertyTypeIds().toList();
    qSort(propertyTypeIds);
    QList<RPropertyTypeId>::iterator it;
    for (it = propertyTypeIds.begin(); it != propertyTypeIds.end(); ++it) {
        updateProperty(*it, object, document);
    }
    if (doUpdateGui) {
        updateGui();
    }
}

void RPropertyEditor::clearEditor() {
    combinedProperties.clear();
    propertyOrder.clear();
    groupOrder.clear();
    updateGui();
}


void RPropertyEditor::propertyChanged(RPropertyTypeId propertyTypeId,
                                      QVariant propertyValue,
                                      RS::EntityType entityTypeFilter,
                                      QVariant::Type typeHint) {

    if (RMainWindow::getMainWindow() == NULL) {
        qWarning() << QString("RPropertyEditor::itemChanged: mainWindow is NULL");
        return;
    }

    if (typeHint!=QVariant::Invalid) {
        // broken for double to int conversion:
        //propertyValue = propertyValue.convert(typeHint);
        if (typeHint==QVariant::Int && propertyValue.type()==QVariant::Double) {
            propertyValue = QVariant(RMath::mround(propertyValue.toDouble()));
        }
    }

    RPropertyEvent pe(propertyTypeId, propertyValue, entityTypeFilter);
    RMainWindow::getMainWindow()->propertyChangeEvent(pe);
}

void RPropertyEditor::listPropertyChanged(RPropertyTypeId propertyTypeId,
                     int index, QVariant propertyValue,
                     RS::EntityType entityTypeFilter) {

    QVariant v;
    QList<QPair<int, double> > list;
    list.append(QPair<int, double>(index, propertyValue.toDouble()));
    v.setValue(list);

    propertyChanged(propertyTypeId, v, entityTypeFilter);
}

/**
 * \return All groups in correct order.
 */
QStringList RPropertyEditor::getGroupTitles() {
    return groupOrder;
}

/**
 * \return All properties of the given group in correct order.
 */
QStringList RPropertyEditor::getPropertyTitles(const QString& group) {
    if (!propertyOrder.contains(group)) {
        return QStringList();
    }
    return propertyOrder.value(group);
}

/**
 * \return Property value of given propery.
 */
QVariant RPropertyEditor::getPropertyValue(const RPropertyTypeId& propertyTypeId) {
    return getPropertyValue(propertyTypeId.getPropertyGroupTitle(), propertyTypeId.getPropertyTitle());
}

/**
 * \return Property value of given propery.
 */
QVariant RPropertyEditor::getPropertyValue(const QString& group, const QString& title) {
    if (!combinedProperties.contains(group)) {
        return QVariant();
    }

    if (!combinedProperties.value(group).contains(title)) {
        return QVariant();
    }

    QPair<QVariant, RPropertyAttributes> pair = combinedProperties[group][title];
    return pair.first;
}

/**
 * \return Property attributes of given propery.
 */
RPropertyAttributes RPropertyEditor::getPropertyAttributes(const RPropertyTypeId& propertyTypeId) {
    return getPropertyAttributes(propertyTypeId.getPropertyGroupTitle(), propertyTypeId.getPropertyTitle());
}

/**
 * \return Property attributes of given propery.
 */
RPropertyAttributes RPropertyEditor::getPropertyAttributes(const QString& group, const QString& title) {
    if (!combinedProperties.contains(group)) {
        return RPropertyAttributes();
    }

    if (!combinedProperties.value(group).contains(title)) {
        return RPropertyAttributes();
    }

    QPair<QVariant, RPropertyAttributes> pair = combinedProperties[group][title];
    return pair.second;
}

QList<RS::EntityType> RPropertyEditor::getTypes() {
    return combinedTypes.keys();
}

int RPropertyEditor::getTypeCount(RS::EntityType type) {
    if (combinedTypes.contains(type)) {
        return combinedTypes.value(type);
    }
    else {
        return -1;
    }
}
