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

#ifndef RLAYER_H
#define RLAYER_H

#include "core_global.h"

#include <QString>
#include <QColor>
#include <QDebug>

#include "RGlobal.h"
#include "RObject.h"
#include "RVector.h"
#include "RPropertyTypeId.h"
#include "RLayerProxy.h"
#include "RLinetype.h"
#include "RColor.h"
#include "RLineweight.h"
#include "RPropertyAttributes.h"

class RDocument;

/**
 * Represents a layer in a drawing.
 *
 * \ingroup core
 * \scriptable
 * \sharedPointerSupport
 */
class QCADCORE_EXPORT RLayer: public RObject {
public:
    static RPropertyTypeId PropertyCustom;
    static RPropertyTypeId PropertyType;
    static RPropertyTypeId PropertyHandle;
    static RPropertyTypeId PropertyProtected;
    static RPropertyTypeId PropertySelected;

    static RPropertyTypeId PropertyName;
    static RPropertyTypeId PropertyOff;
    static RPropertyTypeId PropertyFrozen;
    static RPropertyTypeId PropertyLocked;
    static RPropertyTypeId PropertyCollapsed;
    static RPropertyTypeId PropertyPlottable;
    static RPropertyTypeId PropertySnappable;
    static RPropertyTypeId PropertyOffIsFreeze;
    static RPropertyTypeId PropertyColor;
    static RPropertyTypeId PropertyLinetype;
    static RPropertyTypeId PropertyLineweight;


public:
    enum LayerFlag {
        // these complement the RObject flags
        Off = 0x010,              //!< layer is off
        Frozen = 0x020,           //!< layer is frozen
        Locked = 0x040,           //!< layer is locked
        Collapsed = 0x080,        //!< layer is collapsed
        Plottable = 0x100,        //!< printing disabled for this layer
        Snappable = 0x200,        //!< snap disabled for this layer
        OffIsFreeze = 0x400       //!< off means freeze for this layer
    };
    Q_DECLARE_FLAGS(LayerFlags, LayerFlag)

public:
    RLayer();

    RLayer(RDocument* document, const QString& name, bool frozen = false,
        bool locked = false, const RColor& color = Qt::black,
        RLinetype::Id linetypeId = RLinetype::INVALID_ID,
        RLineweight::Lineweight lineweight = RLineweight::Weight000,
        bool off = false);

    RLayer(const RLayer& other);
    virtual ~RLayer();

    static void init();

    virtual RS::EntityType getType() const {
        return RS::ObjectLayer;
    }

    virtual RLayer* clone() const;

    RLayer::Id getParentLayerId() const;

    QString getName() const {
        return name;
    }

    void setName(const QString& n);

    bool isOffOrFrozen() const {
        return isOff() || isFrozen();
    }

    bool isOff() const {
        return getFlag(RLayer::Off);
    }

    void setOff(bool on) {
        setFlag(RLayer::Off, on);
    }

    bool isFrozen() const {
        return getFlag(RLayer::Frozen);
    }

    void setFrozen(bool on) {
        setFlag(RLayer::Frozen, on);
    }

    bool isLocked() const {
        return getFlag(RLayer::Locked);
    }

    void setLocked(bool on) {
        setFlag(RLayer::Locked, on);
    }

    bool isCollapsed() const {
        return getFlag(RLayer::Collapsed);
    }

    void setCollapsed(bool on) {
        setFlag(RLayer::Collapsed, on);
    }

    bool isPlottable() const {
        return getFlag(RLayer::Plottable);
    }

    void setPlottable(bool on) {
        if (name.toLower()!="defpoints") {
            setFlag(RLayer::Plottable, on);
        }
    }

    bool isSnappable() const {
        return getFlag(RLayer::Snappable);
    }

    void setSnappable(bool on) {
        setFlag(RLayer::Snappable, on);
    }

    bool isOffIsFreeze() const {
        return getFlag(RLayer::OffIsFreeze);
    }

    void setOffIsFreeze(bool on) {
        setFlag(RLayer::OffIsFreeze, on);
    }

    RColor getColor() const {
        return color;
    }

    void setColor(const RColor& c) {
        color = c;
    }

    RLinetype::Id getLinetypeId() const {
        return linetypeId;
    }

    void setLinetypeId(RLinetype::Id lt) {
        linetypeId = lt;
    }

    RLineweight::Lineweight getLineweight() const {
        return lineweight;
    }

    void setLineweight(RLineweight::Lineweight lw) {
        lineweight = lw;
    }

    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);
    virtual bool setProperty(RPropertyTypeId propertyTypeId,
            const QVariant& value, RTransaction* transaction=NULL);

    bool hasChildLayers() const {
        const RDocument* doc = getDocument();
        if (doc==NULL) {
            return false;
        }
        return RLayer::hasChildLayersStatic(doc, name);
    }

    QList<QString> getChildLayerNames(bool recursive = true) const {
        const RDocument* doc = getDocument();
        if (doc==NULL) {
            return QList<QString>();
        }
        return RLayer::getChildLayerNamesStatic(doc, name, recursive);
    }

    QString getParentLayerName() const {
        return RLayer::getParentLayerNameStatic(name);
    }

    QString getShortLayerName() const {
        return RLayer::getShortLayerNameStatic(name);
    }

    QList<QString> getLayerNameHierarchy() const {
        return RLayer::getLayerNameHierarchyStatic(name);
    }

    bool isChildLayerOf(const QString& layerName) const {
        return RLayer::isChildLayerOfStatic(name, layerName);
    }

    static QString getHierarchySeparator() {
        if (layerProxy!=NULL) {
            return layerProxy->getHierarchySeparator();
        }
        return "";
    }

    static bool hasChildLayersStatic(const RDocument* doc, const QString& layerName) {
        if (layerProxy!=NULL) {
            return layerProxy->hasChildLayers(doc, layerName);
        }
        return false;
    }

    static QList<QString> getChildLayerNamesStatic(const RDocument* doc, const QString& layerName, bool recursive = true) {
        if (layerProxy!=NULL) {
            return layerProxy->getChildLayerNames(doc, layerName, recursive);
        }
        return QList<QString>();
    }

    static QString getParentLayerNameStatic(const QString& layerName) {
        if (layerProxy!=NULL) {
            return layerProxy->getParentLayerName(layerName);
        }
        return QString();
    }

    static QString getShortLayerNameStatic(const QString& layerName) {
        if (layerProxy!=NULL) {
            return layerProxy->getShortLayerName(layerName);
        }
        return QString();
    }

    static QList<QString> getLayerNameHierarchyStatic(const QString& layerName) {
        if (layerProxy!=NULL) {
            return layerProxy->getLayerNameHierarchy(layerName);
        }
        return QList<QString>();
    }

    static bool isChildLayerOfStatic(const QString& layerName, const QString& parentLayerName) {
        if (layerProxy!=NULL) {
            return layerProxy->isChildLayerOf(layerName, parentLayerName);
        }
        return false;
    }

    static bool hasProxy() {
        return layerProxy!=NULL;
    }

    /**
     * \nonscriptable
     */
    static void setLayerProxy(RLayerProxy* p) {
        if (layerProxy!=NULL) {
            delete layerProxy;
        }
        layerProxy = p;
    }

    /**
     * \nonscriptable
     */
    static RLayerProxy* getLayerProxy() {
        return layerProxy;
    }

private:
    QString name;
    LayerFlags flags;
    RColor color;
    RLinetype::Id linetypeId;
    RLineweight::Lineweight lineweight;

    static RLayerProxy* layerProxy;
};

QCADCORE_EXPORT QDebug operator<<(QDebug dbg, const RLayer& l);

Q_DECLARE_METATYPE(QSharedPointer<RLayer>)
Q_DECLARE_METATYPE(QSharedPointer<RLayer>*)
Q_DECLARE_METATYPE(RLayer)
Q_DECLARE_METATYPE(RLayer*)
Q_DECLARE_METATYPE(RLayer::LayerFlag)
Q_DECLARE_METATYPE(QFlags<RLayer::LayerFlag>)

#endif
