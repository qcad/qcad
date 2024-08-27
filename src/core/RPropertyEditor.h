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

#ifndef RPROPERTYEDITOR_H
#define RPROPERTYEDITOR_H

#include "core_global.h"

#include <QCoreApplication>
#include <QList>
#include <QMap>
#include <QString>
#include <QStringList>
#if QT_VERSION >= 0x060000
#include <QPromise>
#endif

#include "RDocument.h"
#include "RDocumentInterface.h"
#include "RLayerListener.h"
#include "RObject.h"
#include "RProperty.h"
#include "RPropertyListener.h"


/**
 * Base class for property editors. Provides basic functionality that
 * is common to any property editor implementation.
 *
 * \ingroup core
 * \scriptable
 * \generateScriptShell
 */
class QCADCORE_EXPORT RPropertyEditor: public QObject, public RPropertyListener, public RLayerListener {
    Q_OBJECT

public:
    RPropertyEditor();
    virtual ~RPropertyEditor();

    static RPropertyEditor* getInstance();

    // from RPropertyListener interface:
    virtual void updateFromDocument(RDocument* document, bool onlyChanges, RS::EntityType filter = RS::EntityUnknown, bool manual = false, bool showOnRequest = false);

#if QT_VERSION >= 0x060000
    /**
     * \nonscriptable
     */
    void sleep(QPromise<void>& promise, RDocument* document, bool onlyChanges, RS::EntityType filter, bool manual, bool showOnRequest);
#endif

signals:
    void finished(RDocument* document, bool onlyChanges, RS::EntityType filter, bool manual, bool showOnRequest);

public slots:
    void updateFromDocumentNow(RDocument* document, bool onlyChanges, RS::EntityType filter = RS::EntityUnknown, bool manual = false, bool showOnRequest = false);

public:
    virtual void updateFromObject(RObject* object, RDocument* document = NULL);
    virtual void clearEditor();

    virtual QStringList getFixedCustomPropertyNames(const QList<RS::EntityType>& objectTypes) {
        return QStringList();
    }

    virtual void updateLayers(RDocumentInterface* documentInterface, QList<RLayer::Id>& layerIds);
    virtual void updateLayers(RDocumentInterface* documentInterface);
    virtual void setCurrentLayer(RDocumentInterface* documentInterface, RLayer::Id previousLayerId);
    virtual void clearLayers();

    void propertyChanged(RPropertyTypeId propertyTypeId, QVariant propertyValue,
                         RS::MetaType typeHint = RS::UnknownType);
    void listPropertyChanged(RPropertyTypeId propertyTypeId,
                         int index, QVariant propertyValue);

    QStringList getGroupTitles();
    QStringList getPropertyTitles(const QString& group);
    QVariant getPropertyValue(const RPropertyTypeId& propertyTypeId);
    QVariant getPropertyValue(const QString& group, const QString& title);
    RPropertyAttributes getPropertyAttributes(const RPropertyTypeId& propertyTypeId);
    RPropertyAttributes getPropertyAttributes(const QString& group, const QString& title);
    RPropertyAttributes getCustomPropertyAttributes(const QString& group, const QString& title);
    QList<RS::EntityType> getTypes();
    int getTypeCount(RS::EntityType type);

    void setEntityTypeFilter(RS::EntityType type) {
        entityTypeFilter = type;
    }

    RS::EntityType getEntityTypeFilter() const {
        return entityTypeFilter;
    }

    virtual QStringList getAppProperties() { return QStringList(); }

    static bool checkType(RS::EntityType type, RS::EntityType filter);

    static void makeReadOnly(QWidget* control, bool on);

protected:
    /**
     * \nonscriptable
     */
    virtual void updateEditor(RObject& object, const QList<RPropertyTypeId>& propertyTypeIds, bool doUpdateGui, RDocument* document = NULL, bool showOnRequest = false);

    /**
     * Updates the user interface of this property editor. This is the
     * only part of the property editor that depends on the user interface
     * and GUI toolkit that is available.
     */
    virtual void updateGui(bool onlyChanges = false) {
        Q_UNUSED(onlyChanges)
    }

    void updateProperty(const RPropertyTypeId& propertyTypeId, RObject& object, RDocument* document, bool showOnRequest = false);

    virtual bool showCustomAppProperties(RPropertyAttributes::Option opt);

    static void computePropertyValue(RProperty& property);

protected:
    //! key / value / attributes
    typedef QMap<QString, QPair<QVariant, RPropertyAttributes> > RPropertyMap;
    //! group key / key,value,attributes
    typedef QMap<QString, RPropertyMap> RPropertyGroupMap;

    QStringList groupOrder;
    QMap<QString, QStringList> propertyOrder;
    RPropertyGroupMap combinedProperties;
    QMap<RS::EntityType, int> combinedTypes;
    bool guiUpToDate;
    bool updatesDisabled;

    RS::EntityType entityTypeFilter;

    static RPropertyEditor* instance;


private:
    bool terminate;
};

Q_DECLARE_METATYPE(RPropertyEditor*)

#endif
