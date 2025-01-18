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
#include <QLineEdit>

#if QT_VERSION >= 0x050000
#include <QtConcurrent>
#else
#include <qtconcurrentmap.h>
#endif

#include "RBlockReferenceEntity.h"
#include "RDocumentInterface.h"
#include "RMath.h"
#include "RMainWindow.h"
#include "RS.h"
#include "RSettings.h"
#include "RPropertyEditor.h"

RPropertyEditor* RPropertyEditor::instance = NULL;

/**
 * Default Constructor.
 */
RPropertyEditor::RPropertyEditor()
    : guiUpToDate(false),
      updatesDisabled(false),
      entityTypeFilter(RS::EntityAll),
      terminate(false) {

    instance = this;

#if QT_VERSION >= 0x060000
    connect(this, &RPropertyEditor::finished, this, &RPropertyEditor::updateFromDocumentNow);
#endif
}

/**
 * Destructor
 */
RPropertyEditor::~RPropertyEditor() {
}

RPropertyEditor* RPropertyEditor::getInstance() {
    return instance;
}

/**
 * Sets the property with the given name to the given value or to 'mixed'
 * if that property exists already with a different value.
 *
 * \param propertyTypeId: Id of the property.
 * \param showOnRequest: True to show also slow properties shown on request.
 */
void RPropertyEditor::updateProperty(const RPropertyTypeId& propertyTypeId,
        RObject& object, RDocument* document, bool showOnRequest) {

    Q_UNUSED(document)

    // show on request properties:
    showOnRequest = showOnRequest || RSettings::getPropertyEditorShowOnRequest()==true;

    RPropertyTypeId pid = propertyTypeId;

    QString propertyGroupTitle = propertyTypeId.getPropertyGroupTitle();
    QString propertyTitle = propertyTypeId.getPropertyTitle();

    if (guiUpToDate) {
        combinedProperties.clear();
        guiUpToDate = false;
    }

    // existing group:
    if (combinedProperties.contains(propertyGroupTitle)) {
        RPropertyMap& propertyMap = combinedProperties[propertyGroupTitle];

        // existing property in existing group:
        if (propertyMap.contains(propertyTitle)) {
            // only query property if combined property is NOT already mixed:
            if (!propertyMap[propertyTitle].second.isMixed()) {
                // get property: human readable but no attributes:
                QPair<QVariant, RPropertyAttributes> prop;
//                if (!property.isValid()) {
                    prop = object.getProperty(pid, true, true, showOnRequest);
//                }

                // property is sum:
                if (propertyMap[propertyTitle].second.isSum()) {
                    // sum of all values:
                    double v = propertyMap[propertyTitle].first.toDouble();
//                    if (!property.isValid()) {
                        v += prop.first.toDouble();
//                    }
//                    else {
//                        v += property.value.toDouble();
//                    }
                    propertyMap[propertyTitle].first.setValue(v);
                }
                else if (!RS::compare(propertyMap[propertyTitle], prop)) {
                    // mixed value:
//                    if (!property.isValid()) {
                        propertyMap[propertyTitle].first = prop.first;
//                    }
//                    else {
//                        propertyMap[propertyTitle].first = property.value;
//                    }
                    propertyMap[propertyTitle].second.setMixed(true);
                }
            }
        } else {
            // new property in existing group:
            QPair<QVariant, RPropertyAttributes> prop;
//            if (!property.isValid()) {
                prop = object.getProperty(pid, true, false, showOnRequest);
//            }
//            if (!property.isValid()) {
                if (prop.second.isInvisible()) {
                    return;
                }
                propertyMap[propertyTitle] = prop;
//            }
//            else {
//                if (property.attributes.isInvisible()) {
//                    return;
//                }
//                propertyMap[propertyTitle] = qMakePair(property.value, property.attributes);
//            }

            //property.second.setPropertyTypeId(propertyTypeId);
            propertyOrder[propertyGroupTitle].push_back(propertyTitle);
        }
    } else {
        // new property in new group:
        QPair<QVariant, RPropertyAttributes> prop;
//        if (!property.isValid()) {
            prop = object.getProperty(pid, true, false, showOnRequest);
//        }

        RPropertyMap propertyMap;
//        if (!property.isValid()) {
            if (prop.second.isInvisible()) {
                return;
            }
            propertyMap[propertyTitle] = prop;
//        }
//        else {
//            if (property.attributes.isInvisible()) {
//                return;
//            }
//            propertyMap[propertyTitle] = qMakePair(property.value, property.attributes);
//        }
        //property.second.setPropertyTypeId(propertyTypeId);
        combinedProperties[propertyGroupTitle] = propertyMap;
        groupOrder.push_back(propertyGroupTitle);
        propertyOrder[propertyGroupTitle].push_back(propertyTitle);
    }
}

/**
 * Removes all but the given properties from the combined properties
 * collected so far.
 */
//void RPropertyEditor::removeAllButThese(
//        const QMultiMap<QString, QString>& propertyTitles, bool customOnly) {

//    // iterate through all groups of properties (e.g. "Start Point", "End Point", ...):
//    QStringList removableGroups;
//    RPropertyGroupMap::iterator it;
//    for (it = combinedProperties.begin(); it != combinedProperties.end(); ++it) {

//        // iterate through all properties in the current group (e.g. "X", "Y"):
//        QStringList removableProperties;
//        RPropertyMap::iterator it2;
//        for (it2 = it.value().begin(); it2 != it.value().end(); ++it2) {
//            if (customOnly && !it2.value().second.isCustom()) {
//                continue;
//            }

//            bool keep = false;

//            // check if the current property is among the given properties
//            // we want to keep:
//            QMultiMap<QString, QString>::const_iterator it3;
//            for (it3 = propertyTitles.begin(); it3 != propertyTitles.end(); ++it3) {
//                if (it3.key() == it.key() && it3.value() == it2.key()) {
//                    keep = true;
//                    break;
//                }
//            }

//            if (keep == false) {
//                // schedule property for removal:
//                removableProperties.push_back(it2.key());
//            }
//        }

//        // remove all properties in the current group that are scheduled for removal:
//        QStringList::iterator it4;
//        for (it4 = removableProperties.begin(); it4
//                != removableProperties.end(); ++it4) {
//            it.value().remove(*it4);
//            propertyOrder[it.key()].removeAll(*it4);
//        }

//        // schedule empty groups for removal:
//        if (it.value().empty()) {
//            removableGroups.push_back(it.key());
//        }
//    }

//    // remove all groups that are scheduled for removal:
//    QStringList::iterator it5;
//    for (it5 = removableGroups.begin(); it5 != removableGroups.end(); ++it5) {
//        combinedProperties.remove(*it5);
//        groupOrder.removeAll(*it5);
//    }
//}

#if QT_VERSION >= 0x060000
void RPropertyEditor::sleep(QPromise<void>& promise, RDocument* document, bool onlyChanges, RS::EntityType filter, bool manual, bool showOnRequest) {
    terminate = false;

    QElapsedTimer t;
    t.start();
    int delay = RSettings::getIntValue("PropertyEditor/LazyUpdateDelay", 200);
    while (t.elapsed() < delay) {
        QThread::msleep(10);
        if (terminate) {
            break;
        }
    }

    if (terminate) {
        return;
    }

    emit finished(document, onlyChanges, filter, manual, showOnRequest);
}
#endif

/**
 * Implements updateFromDocument from RPropertyListener to show properties for selected objects.
 *
 * Updates the property editor to contain the properties of the
 * objects that are selected for editing in the given document.
 *
 * \param filter RS::EntityUnknown to use same filter as previously used,
 * any other value to change filter.
 */
void RPropertyEditor::updateFromDocument(RDocument* document, bool onlyChanges, RS::EntityType filter, bool manual, bool showOnRequest) {
    if (updatesDisabled) {
        return;
    }

    if (document == NULL) {
        clearEditor();
        return;
    }

    showOnRequest = showOnRequest || RSettings::getPropertyEditorShowOnRequest()==true;

#if QT_VERSION >= 0x060000
    bool gotSelection = document->hasSelection();
    int lazyUpdate = RSettings::getBoolValue("PropertyEditor/LazyUpdate", true);
    if (lazyUpdate && !showOnRequest && gotSelection) {
        // sleep, then update property editor if sleep was not interrupted by other call:
        static QFuture<void> future = QFuture<void>();

        if (future.isRunning()) {
            terminate = true;
            future.cancel();
            future.waitForFinished();

            // don't clear
            // call might be followed by update of values only:
            //clearEditor();
        }

        future = QtConcurrent::run(&RPropertyEditor::sleep, this, document, onlyChanges, filter, manual, showOnRequest);
    }
    else {
#endif

        updateFromDocumentNow(document, onlyChanges, filter, manual, showOnRequest);

#if QT_VERSION >= 0x060000
    }
#endif
}

void RPropertyEditor::updateFromDocumentNow(RDocument* document, bool onlyChanges, RS::EntityType filter, bool manual, bool showOnRequest) {
    if (updatesDisabled) {
        return;
    }

    if (document == NULL) {
        clearEditor();
        return;
    }

    if (filter!=RS::EntityUnknown) {
        setEntityTypeFilter(filter);
    }

    combinedProperties.clear();
    combinedTypes.clear();
    propertyOrder.clear();
    groupOrder.clear();

    updatesDisabled = true;

    // add all properties of the selected entities in the given document:
    QSet<RObject::Id> objectIds = document->queryPropertyEditorObjects();

    if (objectIds.size()==1) {
        // some properties might be slow even for one single entity:
        //showOnRequest = true;
    }

    QSet<RObject::Id>::iterator it;

    //qDebug() << "manual:" << manual;

    // check if only block refs and attributes are selected:
    // default to filter block ref:
    // special case: single block ref with attributes allows changing attributes:
    RObject::Id singleBlockReferenceId = RObject::INVALID_ID;  // ID of single block ref (with attributes) selected
    bool firstBlockReference = true;
    bool foundBlockRef = false;
    bool foundAttribute = false;
    bool foundOther = false;
    for (it = objectIds.begin(); it != objectIds.end(); ++it) {
        QSharedPointer<RObject> obj = document->queryObjectDirect(*it);
        if (obj.isNull()) {
            continue;
        }

        RS::EntityType type = obj->getType();

        if (foundBlockRef && type==RS::EntityBlockRef) {
            if (singleBlockReferenceId!=RObject::INVALID_ID) {
                QSharedPointer<RBlockReferenceEntity> singleBlockRef = document->queryObjectDirect(singleBlockReferenceId).dynamicCast<RBlockReferenceEntity>();
                QSharedPointer<RBlockReferenceEntity> blockRef = obj.dynamicCast<RBlockReferenceEntity>();

                if (singleBlockRef->getReferencedBlockId()!=blockRef->getReferencedBlockId()) {
                    singleBlockReferenceId = RObject::INVALID_ID;
                }
            }
        }

        if (!foundBlockRef && type==RS::EntityBlockRef) {
            foundBlockRef = true;
            if (foundAttribute && foundOther) {
                singleBlockReferenceId = RObject::INVALID_ID;
                break;
            }
            if (firstBlockReference) {
                singleBlockReferenceId = *it;
                //qDebug() << "block ref selected:" << singleBlockReferenceId;
            }
            else {
                singleBlockReferenceId = RObject::INVALID_ID;
                //qDebug() << "multiple block ref selected";
            }
            firstBlockReference = false;
        }
        if (!foundAttribute && type==RS::EntityAttribute) {
            foundAttribute = true;
            if (foundBlockRef && foundOther) {
                singleBlockReferenceId = RObject::INVALID_ID;
                break;
            }
        }
        if (!foundOther && type!=RS::EntityBlockRef && type!=RS::EntityAttribute) {
            foundOther = true;
            //qDebug() << "other selected";
            singleBlockReferenceId = RObject::INVALID_ID;
            if (foundBlockRef && foundAttribute) {
                singleBlockReferenceId = RObject::INVALID_ID;
                break;
            }
        }
    }

    // got only single block ref with attributes:
    if (singleBlockReferenceId!=RObject::INVALID_ID && foundBlockRef && foundAttribute && !foundOther) {
        if (entityTypeFilter==RS::EntityAll && !manual) {
            entityTypeFilter = RS::EntityBlockRefAttr;
        }
    }

    //qDebug() << "singleBlockReferenceId:" << singleBlockReferenceId;
    //qDebug() << "entityTypeFilter:" << entityTypeFilter;

    // collect and count entity types:
    // collect common custom properties:
    QSet<QString> customPropertyNames;

    // types to show properties for (based on current filter):
    QMap<RS::EntityType, int> combinedTypesLocal;

    bool first = true;
    for (it = objectIds.begin(); it != objectIds.end(); ++it) {
        QSharedPointer<RObject> obj = document->queryObjectDirect(*it);
        if (obj.isNull()) {
            continue;
        }

        RS::EntityType type = obj->getType();

        if (checkType(type, entityTypeFilter)) {
            if (first) {
                customPropertyNames = RS::toSet<QString>(obj->getCustomPropertyKeys("QCAD"));
                first = false;
            }
            else {
                if (!customPropertyNames.isEmpty()) {
                    customPropertyNames.intersect(RS::toSet<QString>(obj->getCustomPropertyKeys("QCAD")));
                }
            }
        }

        // single block ref with attributes:
        if (type==RS::EntityBlockRef && singleBlockReferenceId!=RObject::INVALID_ID && foundAttribute) {
            //type = RS::EntityBlockRefAttr;
            if (combinedTypes.contains(RS::EntityBlockRefAttr)) {
                combinedTypes[RS::EntityBlockRefAttr]++;
            }
            else {
                combinedTypes.insert(RS::EntityBlockRefAttr, 1);
            }
        }
        else {
            if (combinedTypes.contains(type)) {
                combinedTypes[type]++;
            }
            else {
                combinedTypes.insert(type, 1);
            }
        }

        // combined types with selection filter applied:
        if (checkType(type, entityTypeFilter)) {
            if (combinedTypesLocal.contains(type)) {
                combinedTypesLocal[type]++;
            }
            else {
                combinedTypesLocal.insert(type, 1);
            }
        }
    }


    // get list of custom properties that are always shown, even if a selected object does not provide the property:
    QStringList fixedCustomPropertyNames = getFixedCustomPropertyNames(combinedTypesLocal.keys());

    QStringList customPropertyNamesSorted = RS::toList<QString>(customPropertyNames);
    customPropertyNamesSorted.append(fixedCustomPropertyNames);
    qSort(customPropertyNamesSorted.begin(), customPropertyNamesSorted.end());
    customPropertyNamesSorted.removeDuplicates();

    bool showDimStyleOverrides = RSettings::getBoolValue("PropertyEditor/DimStyleOverrides", true);

    // find out which properties need to be collected (combined properties of selected object types):
    QSet<RPropertyTypeId> combinedPropertyTypeIds;
    QList<RS::EntityType> combinedTypeIds = combinedTypesLocal.keys();
    for (int i=0; i<combinedTypeIds.length(); i++) {
        RS::EntityType t = combinedTypeIds[i];
        if (t==RS::EntityBlockRefAttr) {
            t = RS::EntityBlockRef;
        }
        QSet<RPropertyTypeId> propertyTypeIds = RPropertyTypeId::getPropertyTypeIds(t);

        // remove advanced dim style overrides properties:
        if (!showDimStyleOverrides) {
            QSet<RPropertyTypeId> propertyTypeIdsAdv = RPropertyTypeId::getPropertyTypeIds(t, RPropertyAttributes::DimStyleOverride);
            propertyTypeIds.subtract(propertyTypeIdsAdv);
        }

        if (i==0) {
            combinedPropertyTypeIds = propertyTypeIds;
        }
        else {
            combinedPropertyTypeIds.intersect(propertyTypeIds);
        }
    }


    // only a single block (with attributes) selected:
    // add attributes as custom property types:
    if (singleBlockReferenceId!=RObject::INVALID_ID && foundAttribute && entityTypeFilter==RS::EntityBlockRefAttr /*&& !onlyChanges*/) {
        // add properties for block attributes:
        QSet<REntity::Id> childIds = document->queryChildEntities(singleBlockReferenceId, RS::EntityAttribute);
        QSet<REntity::Id>::iterator it;
        for (it=childIds.begin(); it!=childIds.end(); it++) {
            REntity::Id childId = *it;
            QSharedPointer<REntity> child = document->queryEntityDirect(childId);
            if (child.isNull()) {
                continue;
            }
            if (child->isUndone()) {
                continue;
            }

            // get block attribute properties:
            QSet<RPropertyTypeId> childProperties = child->getPropertyTypeIds();
            QSet<RPropertyTypeId>::iterator it2;
            for (it2=childProperties.begin(); it2!=childProperties.end(); it2++) {
                RPropertyTypeId pid = *it2;
                QPair<QVariant, RPropertyAttributes> p = child->getProperty(pid);
                if (p.second.isVisibleToParent()) {
                    pid.setId(RPropertyTypeId::INVALID_ID);
                    combinedPropertyTypeIds.insert(pid);
                    //qDebug() << pid.getCustomPropertyTitle() << " / " << pid.getCustomPropertyName();
                    //qDebug() << p.first.toString();
                }
            }
        }
    }


    QList<RPropertyTypeId> combinedPropertyTypeIdsSorted = RS::toList<RPropertyTypeId>(combinedPropertyTypeIds);
    qSort(combinedPropertyTypeIdsSorted.begin(), combinedPropertyTypeIdsSorted.end());

    // list of property type IDs with values (to be filled in by concurrent mapping below):
    QList<RProperty> ccProperties;
    for (int i=0; i<combinedPropertyTypeIdsSorted.length(); i++) {
        ccProperties.append(RProperty(*document, objectIds, combinedPropertyTypeIdsSorted[i], showOnRequest, entityTypeFilter));
    }

    // append custom properties common among all selected objects:
    for (int i=0; i<customPropertyNamesSorted.length(); i++) {
        ccProperties.append(RProperty(*document, objectIds, RPropertyTypeId("QCAD", customPropertyNamesSorted[i]), showOnRequest, entityTypeFilter));
    }

    // for each property, find out value (either identical value or 'mixed'):
    QtConcurrent::blockingMap(ccProperties, RPropertyEditor::computePropertyValue);

    // serial:
//    for (int i=0; i<ccProperties.length(); i++) {
//        RPropertyEditor::computePropertyValue(ccProperties[i]);
//    }

    // update combined properties map:
    for (int i=0; i<ccProperties.length(); i++) {
        RProperty& p = ccProperties[i];
        RPropertyTypeId& pid = p.propertyTypeId;
        QVariant& val = p.value;
        RPropertyAttributes& attr = p.attributes;

        // ignore custom app properties if not explicitely allowed:
        if (attr.isCustomApp001() && !showCustomAppProperties(RPropertyAttributes::CustomApp001)) {
            continue;
        }

        // group title (e.g. "Center", "QCAD" for custom propertie, "" for group less):
        QString propertyGroupTitle = pid.getPropertyGroupTitle();
        // proerty title (e.g. "X", "myProp", "Text height", etc.):
        QString propertyTitle = pid.getPropertyTitle();

        if (combinedProperties.contains(propertyGroupTitle)) {
            RPropertyMap& propertyMap = combinedProperties[propertyGroupTitle];

            if (propertyMap.contains(propertyTitle)) {
                // existing property in existing group:
                qWarning() << "should not be reached";
            }

            else {
                // new property in existing group:
                propertyMap[propertyTitle] = QPair<QVariant, RPropertyAttributes>(val, attr);

                propertyOrder[propertyGroupTitle].push_back(propertyTitle);
            }
        }
        else {
            // new property in new group:
            RPropertyMap propertyMap;
            propertyMap[propertyTitle] = QPair<QVariant, RPropertyAttributes>(val, attr);
            combinedProperties[propertyGroupTitle] = propertyMap;

            groupOrder.push_back(propertyGroupTitle);
            propertyOrder[propertyGroupTitle].push_back(propertyTitle);
        }
    }


    //RDebug::stopTimer("RPropertyEditor::updateFromDocument");

    // single block ref with attributes:
    if (combinedTypes.contains(RS::EntityBlockRef) && combinedTypes.contains(RS::EntityAttribute) && singleBlockReferenceId!=RObject::INVALID_ID) {
        combinedTypes.insert(RS::EntityBlockRefAttr, combinedTypes[RS::EntityBlockRef] + combinedTypes[RS::EntityBlockRefAttr]);
    }

//    qDebug() << "entityTypeFilter:" << entityTypeFilter;
//    qDebug() << "combinedProperties:";
//    QStringList groups = combinedProperties.keys();
//    for (int i=0; i<groups.length(); i++) {
//        qDebug() << "  group:" << groups[i];
//        QStringList keys = combinedProperties[groups[i]].keys();
//        for (int k=0; k<keys.length(); k++) {
//            qDebug() << "    prop:" << keys[k] << ": " << combinedProperties[groups[i]][keys[k]].first << " (mixed:" << combinedProperties[groups[i]][keys[k]].second.isMixed() << ")";
//        }
//    }
//    qDebug() << "combinedTypes:" << combinedTypes;

    updateGui(onlyChanges);

    updatesDisabled = false;

}

/**
 * Can be re-implemented to show custom app properties of the given type(s).
 */
bool RPropertyEditor::showCustomAppProperties(RPropertyAttributes::Option opt) {
    return false;
}

void RPropertyEditor::computePropertyValue(RProperty& ccProp) {
    bool mixed = false;
    bool invisible = false;

    QSet<RObject::Id>::const_iterator it;
    for (it = ccProp.objectIds->constBegin(); it != ccProp.objectIds->constEnd(); ++it) {
        //QSharedPointer<RObject> obj = ccProp.document->queryObjectDirect(*it);
        RObject* obj = ccProp.document->queryObjectCC(*it);
        //QSharedPointer<RObject> obj = ccProp.document->queryObject(*it);

        RS::EntityType type = obj->getType();

        //if (ccProp.entityTypeFilter!=RS::EntityAll && ccProp.entityTypeFilter!=type) {
        if (!checkType(type, ccProp.entityTypeFilter)) {
            continue;
        }

        QPair<QVariant, RPropertyAttributes> prop = obj->getProperty(ccProp.propertyTypeId, true, true, ccProp.showOnRequest);
        if (prop.second.isInvisible()) {
            // property is invisible:
            invisible = true;
            break;
        }

        if (!ccProp.value.isValid()) {
            // first value:
            ccProp.value = prop.first;
            ccProp.attributes = prop.second;
        }
        else {
            // next value:
            if (prop.second.isSum()) {
                // sum up all values:
                double v = ccProp.value.toDouble();
                ccProp.value.setValue(v + prop.first.toDouble());
            }
            else {
                // compare and set to mixed if values don't match:
                if (!RS::compare(ccProp.value, prop.first)) {
                    mixed = true;
                    break;
                }
            }
        }
    }

    if (invisible) {
        // property is invisible:
        return;
    }

    // group title (e.g. "Center", "QCAD" for custom propertie, "" for group less):
    QString propertyGroupTitle = ccProp.propertyTypeId.getPropertyGroupTitle();
    // proerty title (e.g. "X", "myProp", "Text height", etc.):
    QString propertyTitle = ccProp.propertyTypeId.getPropertyTitle();

    // retrieve custom property attributes from RObject as previously registered:
    // this allows for custom properties to have attributes such as read-only, invisible, custom label, etc):
    if (ccProp.propertyTypeId.isCustom()) {
        ccProp.attributes = RObject::getCustomPropertyAttributes(propertyGroupTitle, propertyTitle);
        if (ccProp.attributes.isInvisible()) {
            return;
        }
    }

    if (mixed) {
        // value is mixed:
        //qDebug() << "value is mixed:" << propertyGroupTitle << propertyTitle;
        ccProp.attributes.setMixed(true);
    }
}

/**
 * Implements updateFromObject from RPropertyListener to show properties for one single object.
 */
void RPropertyEditor::updateFromObject(RObject* object, RDocument* document) {
    if (object != NULL) {
        QSet<RPropertyTypeId> propertyTypeIds = object->getPropertyTypeIds();
        QList<RPropertyTypeId> propertyTypeIdsSorted = RS::toList<RPropertyTypeId>(propertyTypeIds);
        qSort(propertyTypeIdsSorted.begin(), propertyTypeIdsSorted.end());
        updateEditor(*object, propertyTypeIdsSorted, true, document);
    }
}

/**
 * Updates the property widget to include the properties of the given property owner.
 */
void RPropertyEditor::updateEditor(RObject& object, const QList<RPropertyTypeId>& propertyTypeIds, bool doUpdateGui, RDocument* document, bool showOnRequest) {
    // TODO: query all properties of an opject in one go (ordered as list)
    // try for one object type (e.g. circle) to see if it impacts performance

//    QList<RProperty> properties = object.getAllProperties(showOnRequest);
//    //qDebug() << "properties:" << properties.length();
//    for (int i=0; i<properties.length(); i++) {
//        RProperty p = properties[i];
//        updateProperty(p.propertyTypeId, p, object, document, showOnRequest);
//    }

    //QList<RPropertyTypeId> propertyTypeIds = object.getPropertyTypeIds().toList();
    //qSort(propertyTypeIds);

    //QList<RPropertyTypeId> propertyTypeIdsSorted = propertyTypeIds.toList();
    //qSort(propertyTypeIdsSorted);

    QList<RPropertyTypeId>::const_iterator it;
    for (it = propertyTypeIds.begin(); it != propertyTypeIds.end(); ++it) {
        updateProperty(*it, object, document, showOnRequest);
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

void RPropertyEditor::updateLayers(RDocumentInterface* documentInterface, QList<RObject::Id>& layerIds) {
    Q_UNUSED(layerIds)

    updateLayers(documentInterface);
}

void RPropertyEditor::updateLayers(RDocumentInterface* documentInterface) {
    if (documentInterface==NULL) {
        // 20190130: changed from false to true:
        // workaround for Qt 5.10.1 bug (crash when changing layer name in property editor)
        updateFromDocumentNow(NULL, true);
    }
    else {
        // 20190130: changed from false to true:
        // workaround for Qt 5.10.1 bug (crash when changing layer name in property editor)
        updateFromDocumentNow(&documentInterface->getDocument(), true);
    }
}

void RPropertyEditor::setCurrentLayer(RDocumentInterface* documentInterface, RObject::Id previousLayerId) {
    Q_UNUSED(previousLayerId)

    updateLayers(documentInterface);
}

void RPropertyEditor::clearLayers() {
    // do nothing
}

void RPropertyEditor::propertyChanged(RPropertyTypeId propertyTypeId,
                                      QVariant propertyValue,
                                      RS::MetaType typeHint) {

    RMainWindow* appWin = RMainWindow::getMainWindow();
    if (appWin == NULL) {
        qWarning() << QString("RPropertyEditor::itemChanged: mainWindow is NULL");
        return;
    }

    if (typeHint!=RS::UnknownType) {
        // broken for double to int conversion:
        //propertyValue = propertyValue.convert(typeHint);
        if (typeHint==RS::Int && RS::getMetaType(propertyValue)==RS::Double) {
            propertyValue = QVariant(RMath::mround(propertyValue.toDouble()));
        }
    }

    appWin->postPropertyEvent(propertyTypeId, propertyValue, entityTypeFilter);
}

void RPropertyEditor::listPropertyChanged(RPropertyTypeId propertyTypeId,
                     int index, QVariant propertyValue) {

    QVariant v;
    QList<QPair<int, double> > list;
    list.append(QPair<int, double>(index, propertyValue.toDouble()));
    v.setValue(list);

    propertyChanged(propertyTypeId, v);
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
 * \return Property value of given property.
 */
QVariant RPropertyEditor::getPropertyValue(const RPropertyTypeId& propertyTypeId) {
    return getPropertyValue(propertyTypeId.getPropertyGroupTitle(), propertyTypeId.getPropertyTitle());
}

/**
 * \return Property value of given property.
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
 * \return Property attributes of given property.
 */
RPropertyAttributes RPropertyEditor::getPropertyAttributes(const RPropertyTypeId& propertyTypeId) {
//    if (propertyTypeId.isCustom()) {
//        QString group = propertyTypeId.getPropertyGroupTitle();
//        QString title = propertyTypeId.getPropertyTitle();
//        return getCustomPropertyAttributes(group, title);
//    }

    return getPropertyAttributes(propertyTypeId.getPropertyGroupTitle(), propertyTypeId.getPropertyTitle());
}

/**
 * \return Property attributes for given property.
 */
RPropertyAttributes RPropertyEditor::getPropertyAttributes(const QString& group, const QString& title) {
    if (!combinedProperties.contains(group)) {
        return RPropertyAttributes();
    }

    if (!combinedProperties.value(group).contains(title)) {
        return RPropertyAttributes();
    }

    QPair<QVariant, RPropertyAttributes> pair = combinedProperties[group][title];

//    if (pair.second.isCustom()) {
//        return getCustomPropertyAttributes(group, title);
//    }

    return pair.second;
}

RPropertyAttributes RPropertyEditor::getCustomPropertyAttributes(const QString& group, const QString& title) {
    RPropertyAttributes ret = RObject::getCustomPropertyAttributes(group, title);
    //ret.setPropertyTypeId(RPropertyTypeId(group, title));
    return ret;
}

QList<RS::EntityType> RPropertyEditor::getTypes() {
    return combinedTypes.keys();
}

int RPropertyEditor::getTypeCount(RS::EntityType type) {
    if (combinedTypes.contains(type)) {
        return combinedTypes.value(type);
    }
    else {
        return 0;
    }
}

bool RPropertyEditor::checkType(RS::EntityType type, RS::EntityType filter) {
    if (filter==RS::EntityAll) {
        return true;
    }
    if (type==filter) {
        return true;
    }
    //if (filter==RS::EntityBlockRefAttr && (type==RS::EntityBlockRef || type==RS::EntityAttribute)) {
    if (filter==RS::EntityBlockRefAttr && type==RS::EntityBlockRef) {
        return true;
    }

    return false;
}

void RPropertyEditor::makeReadOnly(QWidget* control, bool on) {
    if (control==NULL) {
        return;
    }

    QPalette p = control->palette();
    if (control->property("oriPalette").isNull()) {
        control->setProperty("oriPalette", control->palette());
    }

    QPalette oriPalette = control->property("oriPalette").value<QPalette>();

    if (on) {
        p.setColor(QPalette::Active, QPalette::Text, oriPalette.color(QPalette::Disabled, QPalette::WindowText));
        p.setColor(QPalette::Inactive, QPalette::Text, oriPalette.color(QPalette::Disabled, QPalette::WindowText));
    }
    else {
        p.setColor(QPalette::Active, QPalette::Text, oriPalette.color(QPalette::Active, QPalette::WindowText));
        p.setColor(QPalette::Inactive, QPalette::Text, oriPalette.color(QPalette::Inactive, QPalette::WindowText));
    }

//    if (RSettings.hasDarkGuiBackground()) {
//        p.setColor(QPalette.Base, new QColor("#0a0a0a"));
//    }
//    else {
//        p.setColor(QPalette.Base, new QColor("#eeeeee"));
//    }
    control->setPalette(p);

    QLineEdit* le = qobject_cast<QLineEdit*>(control);
    if (le!=NULL) {
        le->setReadOnly(on);
    }
}
