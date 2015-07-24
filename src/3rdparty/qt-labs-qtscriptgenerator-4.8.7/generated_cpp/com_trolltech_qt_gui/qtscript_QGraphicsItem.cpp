#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qgraphicsitem.h>
#include <QVariant>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qgraphicseffect.h>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <qgraphicssceneevent.h>
#include <qgraphicstransform.h>
#include <qgraphicswidget.h>
#include <qlist.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpoint.h>
#include <qpolygon.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qstyleoption.h>
#include <qtransform.h>
#include <qwidget.h>

#include "qtscriptshell_QGraphicsItem.h"

static const char * const qtscript_QGraphicsItem_function_names[] = {
    "QGraphicsItem"
    // static
    // prototype
    , "acceptDrops"
    , "acceptHoverEvents"
    , "acceptTouchEvents"
    , "acceptedMouseButtons"
    , "acceptsHoverEvents"
    , "advance"
    , "boundingRect"
    , "boundingRegion"
    , "boundingRegionGranularity"
    , "cacheMode"
    , "childItems"
    , "childrenBoundingRect"
    , "clearFocus"
    , "clipPath"
    , "collidesWithItem"
    , "collidesWithPath"
    , "collidingItems"
    , "commonAncestorItem"
    , "contains"
    , "cursor"
    , "data"
    , "deviceTransform"
    , "effectiveOpacity"
    , "ensureVisible"
    , "filtersChildEvents"
    , "flags"
    , "focusItem"
    , "focusProxy"
    , "focusScopeItem"
    , "grabKeyboard"
    , "grabMouse"
    , "graphicsEffect"
    , "group"
    , "handlesChildEvents"
    , "hasCursor"
    , "hasFocus"
    , "hide"
    , "inputMethodHints"
    , "installSceneEventFilter"
    , "isActive"
    , "isAncestorOf"
    , "isBlockedByModalPanel"
    , "isClipped"
    , "isEnabled"
    , "isObscured"
    , "isObscuredBy"
    , "isPanel"
    , "isSelected"
    , "isUnderMouse"
    , "isVisible"
    , "isVisibleTo"
    , "isWidget"
    , "isWindow"
    , "itemTransform"
    , "mapFromItem"
    , "mapFromParent"
    , "mapFromScene"
    , "mapRectFromItem"
    , "mapRectFromParent"
    , "mapRectFromScene"
    , "mapRectToItem"
    , "mapRectToParent"
    , "mapRectToScene"
    , "mapToItem"
    , "mapToParent"
    , "mapToScene"
    , "moveBy"
    , "opacity"
    , "opaqueArea"
    , "paint"
    , "panel"
    , "panelModality"
    , "parentItem"
    , "parentObject"
    , "parentWidget"
    , "pos"
    , "removeSceneEventFilter"
    , "resetTransform"
    , "rotate"
    , "rotation"
    , "scale"
    , "scene"
    , "sceneBoundingRect"
    , "scenePos"
    , "sceneTransform"
    , "scroll"
    , "setAcceptDrops"
    , "setAcceptHoverEvents"
    , "setAcceptTouchEvents"
    , "setAcceptedMouseButtons"
    , "setAcceptsHoverEvents"
    , "setActive"
    , "setBoundingRegionGranularity"
    , "setCacheMode"
    , "setCursor"
    , "setData"
    , "setEnabled"
    , "setFiltersChildEvents"
    , "setFlag"
    , "setFlags"
    , "setFocus"
    , "setFocusProxy"
    , "setGraphicsEffect"
    , "setGroup"
    , "setHandlesChildEvents"
    , "setInputMethodHints"
    , "setOpacity"
    , "setPanelModality"
    , "setParentItem"
    , "setPos"
    , "setRotation"
    , "setScale"
    , "setSelected"
    , "setToolTip"
    , "setTransform"
    , "setTransformOriginPoint"
    , "setTransformations"
    , "setVisible"
    , "setX"
    , "setY"
    , "setZValue"
    , "shape"
    , "shear"
    , "show"
    , "stackBefore"
    , "toGraphicsObject"
    , "toolTip"
    , "topLevelItem"
    , "topLevelWidget"
    , "transform"
    , "transformOriginPoint"
    , "transformations"
    , "translate"
    , "type"
    , "ungrabKeyboard"
    , "ungrabMouse"
    , "unsetCursor"
    , "update"
    , "window"
    , "x"
    , "y"
    , "zValue"
    , "toString"
};

static const char * const qtscript_QGraphicsItem_function_signatures[] = {
    "QGraphicsItem parent, QGraphicsScene scene"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , "int phase"
    , ""
    , "QTransform itemToDeviceTransform"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QGraphicsItem other, ItemSelectionMode mode"
    , "QPainterPath path, ItemSelectionMode mode"
    , "ItemSelectionMode mode"
    , "QGraphicsItem other"
    , "QPointF point"
    , ""
    , "int key"
    , "QTransform viewportTransform"
    , ""
    , "QRectF rect, int xmargin, int ymargin\nqreal x, qreal y, qreal w, qreal h, int xmargin, int ymargin"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QGraphicsItem filterItem"
    , ""
    , "QGraphicsItem child"
    , "QGraphicsItem blockingPanel"
    , ""
    , ""
    , "\nQRectF rect\nqreal x, qreal y, qreal w, qreal h"
    , "QGraphicsItem item"
    , ""
    , ""
    , ""
    , ""
    , "QGraphicsItem parent"
    , ""
    , ""
    , "QGraphicsItem other, bool ok"
    , "QGraphicsItem item, QPainterPath path\nQGraphicsItem item, QPointF point\nQGraphicsItem item, QPolygonF polygon\nQGraphicsItem item, QRectF rect\nQGraphicsItem item, qreal x, qreal y\nQGraphicsItem item, qreal x, qreal y, qreal w, qreal h"
    , "QPainterPath path\nQPointF point\nQPolygonF polygon\nQRectF rect\nqreal x, qreal y\nqreal x, qreal y, qreal w, qreal h"
    , "QPainterPath path\nQPointF point\nQPolygonF polygon\nQRectF rect\nqreal x, qreal y\nqreal x, qreal y, qreal w, qreal h"
    , "QGraphicsItem item, QRectF rect\nQGraphicsItem item, qreal x, qreal y, qreal w, qreal h"
    , "QRectF rect\nqreal x, qreal y, qreal w, qreal h"
    , "QRectF rect\nqreal x, qreal y, qreal w, qreal h"
    , "QGraphicsItem item, QRectF rect\nQGraphicsItem item, qreal x, qreal y, qreal w, qreal h"
    , "QRectF rect\nqreal x, qreal y, qreal w, qreal h"
    , "QRectF rect\nqreal x, qreal y, qreal w, qreal h"
    , "QGraphicsItem item, QPainterPath path\nQGraphicsItem item, QPointF point\nQGraphicsItem item, QPolygonF polygon\nQGraphicsItem item, QRectF rect\nQGraphicsItem item, qreal x, qreal y\nQGraphicsItem item, qreal x, qreal y, qreal w, qreal h"
    , "QPainterPath path\nQPointF point\nQPolygonF polygon\nQRectF rect\nqreal x, qreal y\nqreal x, qreal y, qreal w, qreal h"
    , "QPainterPath path\nQPointF point\nQPolygonF polygon\nQRectF rect\nqreal x, qreal y\nqreal x, qreal y, qreal w, qreal h"
    , "qreal dx, qreal dy"
    , ""
    , ""
    , "QPainter painter, QStyleOptionGraphicsItem option, QWidget widget"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QGraphicsItem filterItem"
    , ""
    , "qreal angle"
    , ""
    , "\nqreal sx, qreal sy"
    , ""
    , ""
    , ""
    , ""
    , "qreal dx, qreal dy, QRectF rect"
    , "bool on"
    , "bool enabled"
    , "bool enabled"
    , "MouseButtons buttons"
    , "bool enabled"
    , "bool active"
    , "qreal granularity"
    , "CacheMode mode, QSize cacheSize"
    , "QCursor cursor"
    , "int key, Object value"
    , "bool enabled"
    , "bool enabled"
    , "GraphicsItemFlag flag, bool enabled"
    , "GraphicsItemFlags flags"
    , "FocusReason focusReason"
    , "QGraphicsItem item"
    , "QGraphicsEffect effect"
    , "QGraphicsItemGroup group"
    , "bool enabled"
    , "InputMethodHints hints"
    , "qreal opacity"
    , "PanelModality panelModality"
    , "QGraphicsItem parent"
    , "QPointF pos\nqreal x, qreal y"
    , "qreal angle"
    , "qreal scale"
    , "bool selected"
    , "String toolTip"
    , "QTransform matrix, bool combine"
    , "QPointF origin\nqreal ax, qreal ay"
    , "List transformations"
    , "bool visible"
    , "qreal x"
    , "qreal y"
    , "qreal z"
    , ""
    , "qreal sh, qreal sv"
    , ""
    , "QGraphicsItem sibling"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "qreal dx, qreal dy"
    , ""
    , ""
    , ""
    , ""
    , "QRectF rect\nqreal x, qreal y, qreal width, qreal height"
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QGraphicsItem_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 2
    , 2
    , 1
    , 1
    , 1
    , 0
    , 1
    , 1
    , 0
    , 6
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 1
    , 1
    , 0
    , 0
    , 4
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 2
    , 5
    , 4
    , 4
    , 5
    , 4
    , 4
    , 5
    , 4
    , 4
    , 5
    , 4
    , 4
    , 2
    , 0
    , 0
    , 3
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 1
    , 0
    , 2
    , 0
    , 0
    , 0
    , 0
    , 3
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 2
    , 1
    , 2
    , 1
    , 1
    , 2
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 2
    , 1
    , 1
    , 1
    , 1
    , 2
    , 2
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 2
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 2
    , 0
    , 0
    , 0
    , 0
    , 4
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QGraphicsItem_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsItem::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QtScriptShell_QGraphicsItem*)
Q_DECLARE_METATYPE(QGraphicsItem::CacheMode)
Q_DECLARE_METATYPE(QGraphicsItem::PanelModality)
Q_DECLARE_METATYPE(QGraphicsItem::GraphicsItemFlag)
Q_DECLARE_METATYPE(QFlags<QGraphicsItem::GraphicsItemFlag>)
Q_DECLARE_METATYPE(QGraphicsItem::GraphicsItemChange)
Q_DECLARE_METATYPE(QFlags<Qt::MouseButton>)
Q_DECLARE_METATYPE(QList<QGraphicsItem*>)
Q_DECLARE_METATYPE(QPainterPath)
Q_DECLARE_METATYPE(Qt::ItemSelectionMode)
Q_DECLARE_METATYPE(QGraphicsEffect*)
Q_DECLARE_METATYPE(QGraphicsItemGroup*)
Q_DECLARE_METATYPE(QFlags<Qt::InputMethodHint>)
Q_DECLARE_METATYPE(QGraphicsItem**)
Q_DECLARE_METATYPE(bool*)
Q_DECLARE_METATYPE(QPolygonF)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QStyleOptionGraphicsItem*)
Q_DECLARE_METATYPE(QGraphicsObject*)
Q_DECLARE_METATYPE(QGraphicsWidget*)
Q_DECLARE_METATYPE(Qt::FocusReason)
Q_DECLARE_METATYPE(QGraphicsTransform*)
Q_DECLARE_METATYPE(QList<QGraphicsTransform*>)

static QScriptValue qtscript_create_enum_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto, 1);
}

static QScriptValue qtscript_create_flags_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString,
    QScriptEngine::FunctionSignature equals)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("equals"),
        engine->newFunction(equals), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto);
}

//
// QGraphicsItem::CacheMode
//

static const QGraphicsItem::CacheMode qtscript_QGraphicsItem_CacheMode_values[] = {
    QGraphicsItem::NoCache
    , QGraphicsItem::ItemCoordinateCache
    , QGraphicsItem::DeviceCoordinateCache
};

static const char * const qtscript_QGraphicsItem_CacheMode_keys[] = {
    "NoCache"
    , "ItemCoordinateCache"
    , "DeviceCoordinateCache"
};

static QString qtscript_QGraphicsItem_CacheMode_toStringHelper(QGraphicsItem::CacheMode value)
{
    if ((value >= QGraphicsItem::NoCache) && (value <= QGraphicsItem::DeviceCoordinateCache))
        return qtscript_QGraphicsItem_CacheMode_keys[static_cast<int>(value)-static_cast<int>(QGraphicsItem::NoCache)];
    return QString();
}

static QScriptValue qtscript_QGraphicsItem_CacheMode_toScriptValue(QScriptEngine *engine, const QGraphicsItem::CacheMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QGraphicsItem"));
    return clazz.property(qtscript_QGraphicsItem_CacheMode_toStringHelper(value));
}

static void qtscript_QGraphicsItem_CacheMode_fromScriptValue(const QScriptValue &value, QGraphicsItem::CacheMode &out)
{
    out = qvariant_cast<QGraphicsItem::CacheMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QGraphicsItem_CacheMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QGraphicsItem::NoCache) && (arg <= QGraphicsItem::DeviceCoordinateCache))
        return qScriptValueFromValue(engine,  static_cast<QGraphicsItem::CacheMode>(arg));
    return context->throwError(QString::fromLatin1("CacheMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QGraphicsItem_CacheMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsItem::CacheMode value = qscriptvalue_cast<QGraphicsItem::CacheMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGraphicsItem_CacheMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsItem::CacheMode value = qscriptvalue_cast<QGraphicsItem::CacheMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QGraphicsItem_CacheMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QGraphicsItem_CacheMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QGraphicsItem_CacheMode,
        qtscript_QGraphicsItem_CacheMode_valueOf, qtscript_QGraphicsItem_CacheMode_toString);
    qScriptRegisterMetaType<QGraphicsItem::CacheMode>(engine, qtscript_QGraphicsItem_CacheMode_toScriptValue,
        qtscript_QGraphicsItem_CacheMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QGraphicsItem_CacheMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QGraphicsItem_CacheMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QGraphicsItem::PanelModality
//

static const QGraphicsItem::PanelModality qtscript_QGraphicsItem_PanelModality_values[] = {
    QGraphicsItem::NonModal
    , QGraphicsItem::PanelModal
    , QGraphicsItem::SceneModal
};

static const char * const qtscript_QGraphicsItem_PanelModality_keys[] = {
    "NonModal"
    , "PanelModal"
    , "SceneModal"
};

static QString qtscript_QGraphicsItem_PanelModality_toStringHelper(QGraphicsItem::PanelModality value)
{
    if ((value >= QGraphicsItem::NonModal) && (value <= QGraphicsItem::SceneModal))
        return qtscript_QGraphicsItem_PanelModality_keys[static_cast<int>(value)-static_cast<int>(QGraphicsItem::NonModal)];
    return QString();
}

static QScriptValue qtscript_QGraphicsItem_PanelModality_toScriptValue(QScriptEngine *engine, const QGraphicsItem::PanelModality &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QGraphicsItem"));
    return clazz.property(qtscript_QGraphicsItem_PanelModality_toStringHelper(value));
}

static void qtscript_QGraphicsItem_PanelModality_fromScriptValue(const QScriptValue &value, QGraphicsItem::PanelModality &out)
{
    out = qvariant_cast<QGraphicsItem::PanelModality>(value.toVariant());
}

static QScriptValue qtscript_construct_QGraphicsItem_PanelModality(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QGraphicsItem::NonModal) && (arg <= QGraphicsItem::SceneModal))
        return qScriptValueFromValue(engine,  static_cast<QGraphicsItem::PanelModality>(arg));
    return context->throwError(QString::fromLatin1("PanelModality(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QGraphicsItem_PanelModality_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsItem::PanelModality value = qscriptvalue_cast<QGraphicsItem::PanelModality>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGraphicsItem_PanelModality_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsItem::PanelModality value = qscriptvalue_cast<QGraphicsItem::PanelModality>(context->thisObject());
    return QScriptValue(engine, qtscript_QGraphicsItem_PanelModality_toStringHelper(value));
}

static QScriptValue qtscript_create_QGraphicsItem_PanelModality_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QGraphicsItem_PanelModality,
        qtscript_QGraphicsItem_PanelModality_valueOf, qtscript_QGraphicsItem_PanelModality_toString);
    qScriptRegisterMetaType<QGraphicsItem::PanelModality>(engine, qtscript_QGraphicsItem_PanelModality_toScriptValue,
        qtscript_QGraphicsItem_PanelModality_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QGraphicsItem_PanelModality_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QGraphicsItem_PanelModality_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QGraphicsItem::GraphicsItemFlag
//

static const QGraphicsItem::GraphicsItemFlag qtscript_QGraphicsItem_GraphicsItemFlag_values[] = {
    QGraphicsItem::ItemIsMovable
    , QGraphicsItem::ItemIsSelectable
    , QGraphicsItem::ItemIsFocusable
    , QGraphicsItem::ItemClipsToShape
    , QGraphicsItem::ItemClipsChildrenToShape
    , QGraphicsItem::ItemIgnoresTransformations
    , QGraphicsItem::ItemIgnoresParentOpacity
    , QGraphicsItem::ItemDoesntPropagateOpacityToChildren
    , QGraphicsItem::ItemStacksBehindParent
    , QGraphicsItem::ItemUsesExtendedStyleOption
    , QGraphicsItem::ItemHasNoContents
    , QGraphicsItem::ItemSendsGeometryChanges
    , QGraphicsItem::ItemAcceptsInputMethod
    , QGraphicsItem::ItemNegativeZStacksBehindParent
    , QGraphicsItem::ItemIsPanel
    , QGraphicsItem::ItemIsFocusScope
    , QGraphicsItem::ItemSendsScenePositionChanges
    , QGraphicsItem::ItemStopsClickFocusPropagation
    , QGraphicsItem::ItemStopsFocusHandling
};

static const char * const qtscript_QGraphicsItem_GraphicsItemFlag_keys[] = {
    "ItemIsMovable"
    , "ItemIsSelectable"
    , "ItemIsFocusable"
    , "ItemClipsToShape"
    , "ItemClipsChildrenToShape"
    , "ItemIgnoresTransformations"
    , "ItemIgnoresParentOpacity"
    , "ItemDoesntPropagateOpacityToChildren"
    , "ItemStacksBehindParent"
    , "ItemUsesExtendedStyleOption"
    , "ItemHasNoContents"
    , "ItemSendsGeometryChanges"
    , "ItemAcceptsInputMethod"
    , "ItemNegativeZStacksBehindParent"
    , "ItemIsPanel"
    , "ItemIsFocusScope"
    , "ItemSendsScenePositionChanges"
    , "ItemStopsClickFocusPropagation"
    , "ItemStopsFocusHandling"
};

static QString qtscript_QGraphicsItem_GraphicsItemFlag_toStringHelper(QGraphicsItem::GraphicsItemFlag value)
{
    for (int i = 0; i < 19; ++i) {
        if (qtscript_QGraphicsItem_GraphicsItemFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QGraphicsItem_GraphicsItemFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QGraphicsItem_GraphicsItemFlag_toScriptValue(QScriptEngine *engine, const QGraphicsItem::GraphicsItemFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QGraphicsItem"));
    return clazz.property(qtscript_QGraphicsItem_GraphicsItemFlag_toStringHelper(value));
}

static void qtscript_QGraphicsItem_GraphicsItemFlag_fromScriptValue(const QScriptValue &value, QGraphicsItem::GraphicsItemFlag &out)
{
    out = qvariant_cast<QGraphicsItem::GraphicsItemFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QGraphicsItem_GraphicsItemFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 19; ++i) {
        if (qtscript_QGraphicsItem_GraphicsItemFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QGraphicsItem::GraphicsItemFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("GraphicsItemFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QGraphicsItem_GraphicsItemFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsItem::GraphicsItemFlag value = qscriptvalue_cast<QGraphicsItem::GraphicsItemFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGraphicsItem_GraphicsItemFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsItem::GraphicsItemFlag value = qscriptvalue_cast<QGraphicsItem::GraphicsItemFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QGraphicsItem_GraphicsItemFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QGraphicsItem_GraphicsItemFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QGraphicsItem_GraphicsItemFlag,
        qtscript_QGraphicsItem_GraphicsItemFlag_valueOf, qtscript_QGraphicsItem_GraphicsItemFlag_toString);
    qScriptRegisterMetaType<QGraphicsItem::GraphicsItemFlag>(engine, qtscript_QGraphicsItem_GraphicsItemFlag_toScriptValue,
        qtscript_QGraphicsItem_GraphicsItemFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 19; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QGraphicsItem_GraphicsItemFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QGraphicsItem_GraphicsItemFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QGraphicsItem::GraphicsItemFlags
//

static QScriptValue qtscript_QGraphicsItem_GraphicsItemFlags_toScriptValue(QScriptEngine *engine, const QGraphicsItem::GraphicsItemFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QGraphicsItem_GraphicsItemFlags_fromScriptValue(const QScriptValue &value, QGraphicsItem::GraphicsItemFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QGraphicsItem::GraphicsItemFlags>())
        out = qvariant_cast<QGraphicsItem::GraphicsItemFlags>(var);
    else if (var.userType() == qMetaTypeId<QGraphicsItem::GraphicsItemFlag>())
        out = qvariant_cast<QGraphicsItem::GraphicsItemFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QGraphicsItem_GraphicsItemFlags(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsItem::GraphicsItemFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QGraphicsItem::GraphicsItemFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QGraphicsItem::GraphicsItemFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("GraphicsItemFlags(): argument %0 is not of type GraphicsItemFlag").arg(i));
            }
            result |= qvariant_cast<QGraphicsItem::GraphicsItemFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QGraphicsItem_GraphicsItemFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsItem::GraphicsItemFlags value = qscriptvalue_cast<QGraphicsItem::GraphicsItemFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGraphicsItem_GraphicsItemFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsItem::GraphicsItemFlags value = qscriptvalue_cast<QGraphicsItem::GraphicsItemFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 19; ++i) {
        if ((value & qtscript_QGraphicsItem_GraphicsItemFlag_values[i]) == qtscript_QGraphicsItem_GraphicsItemFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QGraphicsItem_GraphicsItemFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QGraphicsItem_GraphicsItemFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QGraphicsItem::GraphicsItemFlags>() == otherObj.value<QGraphicsItem::GraphicsItemFlags>())));
}

static QScriptValue qtscript_create_QGraphicsItem_GraphicsItemFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QGraphicsItem_GraphicsItemFlags, qtscript_QGraphicsItem_GraphicsItemFlags_valueOf,
        qtscript_QGraphicsItem_GraphicsItemFlags_toString, qtscript_QGraphicsItem_GraphicsItemFlags_equals);
    qScriptRegisterMetaType<QGraphicsItem::GraphicsItemFlags>(engine, qtscript_QGraphicsItem_GraphicsItemFlags_toScriptValue,
        qtscript_QGraphicsItem_GraphicsItemFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QGraphicsItem::GraphicsItemChange
//

static const QGraphicsItem::GraphicsItemChange qtscript_QGraphicsItem_GraphicsItemChange_values[] = {
    QGraphicsItem::ItemPositionChange
    , QGraphicsItem::ItemMatrixChange
    , QGraphicsItem::ItemVisibleChange
    , QGraphicsItem::ItemEnabledChange
    , QGraphicsItem::ItemSelectedChange
    , QGraphicsItem::ItemParentChange
    , QGraphicsItem::ItemChildAddedChange
    , QGraphicsItem::ItemChildRemovedChange
    , QGraphicsItem::ItemTransformChange
    , QGraphicsItem::ItemPositionHasChanged
    , QGraphicsItem::ItemTransformHasChanged
    , QGraphicsItem::ItemSceneChange
    , QGraphicsItem::ItemVisibleHasChanged
    , QGraphicsItem::ItemEnabledHasChanged
    , QGraphicsItem::ItemSelectedHasChanged
    , QGraphicsItem::ItemParentHasChanged
    , QGraphicsItem::ItemSceneHasChanged
    , QGraphicsItem::ItemCursorChange
    , QGraphicsItem::ItemCursorHasChanged
    , QGraphicsItem::ItemToolTipChange
    , QGraphicsItem::ItemToolTipHasChanged
    , QGraphicsItem::ItemFlagsChange
    , QGraphicsItem::ItemFlagsHaveChanged
    , QGraphicsItem::ItemZValueChange
    , QGraphicsItem::ItemZValueHasChanged
    , QGraphicsItem::ItemOpacityChange
    , QGraphicsItem::ItemOpacityHasChanged
    , QGraphicsItem::ItemScenePositionHasChanged
    , QGraphicsItem::ItemRotationChange
    , QGraphicsItem::ItemRotationHasChanged
    , QGraphicsItem::ItemScaleChange
    , QGraphicsItem::ItemScaleHasChanged
    , QGraphicsItem::ItemTransformOriginPointChange
    , QGraphicsItem::ItemTransformOriginPointHasChanged
};

static const char * const qtscript_QGraphicsItem_GraphicsItemChange_keys[] = {
    "ItemPositionChange"
    , "ItemMatrixChange"
    , "ItemVisibleChange"
    , "ItemEnabledChange"
    , "ItemSelectedChange"
    , "ItemParentChange"
    , "ItemChildAddedChange"
    , "ItemChildRemovedChange"
    , "ItemTransformChange"
    , "ItemPositionHasChanged"
    , "ItemTransformHasChanged"
    , "ItemSceneChange"
    , "ItemVisibleHasChanged"
    , "ItemEnabledHasChanged"
    , "ItemSelectedHasChanged"
    , "ItemParentHasChanged"
    , "ItemSceneHasChanged"
    , "ItemCursorChange"
    , "ItemCursorHasChanged"
    , "ItemToolTipChange"
    , "ItemToolTipHasChanged"
    , "ItemFlagsChange"
    , "ItemFlagsHaveChanged"
    , "ItemZValueChange"
    , "ItemZValueHasChanged"
    , "ItemOpacityChange"
    , "ItemOpacityHasChanged"
    , "ItemScenePositionHasChanged"
    , "ItemRotationChange"
    , "ItemRotationHasChanged"
    , "ItemScaleChange"
    , "ItemScaleHasChanged"
    , "ItemTransformOriginPointChange"
    , "ItemTransformOriginPointHasChanged"
};

static QString qtscript_QGraphicsItem_GraphicsItemChange_toStringHelper(QGraphicsItem::GraphicsItemChange value)
{
    if ((value >= QGraphicsItem::ItemPositionChange) && (value <= QGraphicsItem::ItemTransformOriginPointHasChanged))
        return qtscript_QGraphicsItem_GraphicsItemChange_keys[static_cast<int>(value)-static_cast<int>(QGraphicsItem::ItemPositionChange)];
    return QString();
}

static QScriptValue qtscript_QGraphicsItem_GraphicsItemChange_toScriptValue(QScriptEngine *engine, const QGraphicsItem::GraphicsItemChange &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QGraphicsItem"));
    return clazz.property(qtscript_QGraphicsItem_GraphicsItemChange_toStringHelper(value));
}

static void qtscript_QGraphicsItem_GraphicsItemChange_fromScriptValue(const QScriptValue &value, QGraphicsItem::GraphicsItemChange &out)
{
    out = qvariant_cast<QGraphicsItem::GraphicsItemChange>(value.toVariant());
}

static QScriptValue qtscript_construct_QGraphicsItem_GraphicsItemChange(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QGraphicsItem::ItemPositionChange) && (arg <= QGraphicsItem::ItemTransformOriginPointHasChanged))
        return qScriptValueFromValue(engine,  static_cast<QGraphicsItem::GraphicsItemChange>(arg));
    return context->throwError(QString::fromLatin1("GraphicsItemChange(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QGraphicsItem_GraphicsItemChange_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsItem::GraphicsItemChange value = qscriptvalue_cast<QGraphicsItem::GraphicsItemChange>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGraphicsItem_GraphicsItemChange_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsItem::GraphicsItemChange value = qscriptvalue_cast<QGraphicsItem::GraphicsItemChange>(context->thisObject());
    return QScriptValue(engine, qtscript_QGraphicsItem_GraphicsItemChange_toStringHelper(value));
}

static QScriptValue qtscript_create_QGraphicsItem_GraphicsItemChange_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QGraphicsItem_GraphicsItemChange,
        qtscript_QGraphicsItem_GraphicsItemChange_valueOf, qtscript_QGraphicsItem_GraphicsItemChange_toString);
    qScriptRegisterMetaType<QGraphicsItem::GraphicsItemChange>(engine, qtscript_QGraphicsItem_GraphicsItemChange_toScriptValue,
        qtscript_QGraphicsItem_GraphicsItemChange_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 34; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QGraphicsItem_GraphicsItemChange_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QGraphicsItem_GraphicsItemChange_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QGraphicsItem
//

static QScriptValue qtscript_QGraphicsItem_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 142;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGraphicsItem* _q_self = qscriptvalue_cast<QGraphicsItem*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsItem.%0(): this object is not a QGraphicsItem")
            .arg(qtscript_QGraphicsItem_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->acceptDrops();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->acceptHoverEvents();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->acceptTouchEvents();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QFlags<Qt::MouseButton> _q_result = _q_self->acceptedMouseButtons();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->acceptsHoverEvents();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->advance(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QRectF _q_result = _q_self->boundingRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
        QRegion _q_result = _q_self->boundingRegion(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->boundingRegionGranularity();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QGraphicsItem::CacheMode _q_result = _q_self->cacheMode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QList<QGraphicsItem*> _q_result = _q_self->childItems();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QRectF _q_result = _q_self->childrenBoundingRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        _q_self->clearFocus();
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QPainterPath _q_result = _q_self->clipPath();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        bool _q_result = _q_self->collidesWithItem(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        Qt::ItemSelectionMode _q_arg1 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(1));
        bool _q_result = _q_self->collidesWithItem(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        bool _q_result = _q_self->collidesWithPath(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        Qt::ItemSelectionMode _q_arg1 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(1));
        bool _q_result = _q_self->collidesWithPath(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QList<QGraphicsItem*> _q_result = _q_self->collidingItems();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        Qt::ItemSelectionMode _q_arg0 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(0));
        QList<QGraphicsItem*> _q_result = _q_self->collidingItems(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        QGraphicsItem* _q_result = _q_self->commonAncestorItem(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        bool _q_result = _q_self->contains(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QCursor _q_result = _q_self->cursor();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QVariant _q_result = _q_self->data(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
        QTransform _q_result = _q_self->deviceTransform(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->effectiveOpacity();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        _q_self->ensureVisible();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        _q_self->ensureVisible(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->ensureVisible(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->ensureVisible(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->ensureVisible(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 5) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        int _q_arg4 = context->argument(4).toInt32();
        _q_self->ensureVisible(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 6) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        int _q_arg4 = context->argument(4).toInt32();
        int _q_arg5 = context->argument(5).toInt32();
        _q_self->ensureVisible(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->filtersChildEvents();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 0) {
        QFlags<QGraphicsItem::GraphicsItemFlag> _q_result = _q_self->flags();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        QGraphicsItem* _q_result = _q_self->focusItem();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        QGraphicsItem* _q_result = _q_self->focusProxy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 0) {
        QGraphicsItem* _q_result = _q_self->focusScopeItem();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 0) {
        _q_self->grabKeyboard();
        return context->engine()->undefinedValue();
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        _q_self->grabMouse();
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 0) {
        QGraphicsEffect* _q_result = _q_self->graphicsEffect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 0) {
        QGraphicsItemGroup* _q_result = _q_self->group();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 33:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->handlesChildEvents();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 34:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasCursor();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 35:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasFocus();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 36:
    if (context->argumentCount() == 0) {
        _q_self->hide();
        return context->engine()->undefinedValue();
    }
    break;

    case 37:
    if (context->argumentCount() == 0) {
        QFlags<Qt::InputMethodHint> _q_result = _q_self->inputMethodHints();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        _q_self->installSceneEventFilter(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 39:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isActive();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 40:
    if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        bool _q_result = _q_self->isAncestorOf(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 41:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isBlockedByModalPanel();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QGraphicsItem** _q_arg0 = qscriptvalue_cast<QGraphicsItem**>(context->argument(0));
        bool _q_result = _q_self->isBlockedByModalPanel(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 42:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isClipped();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 43:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEnabled();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 44:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isObscured();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        bool _q_result = _q_self->isObscured(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        bool _q_result = _q_self->isObscured(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 45:
    if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        bool _q_result = _q_self->isObscuredBy(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 46:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isPanel();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 47:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isSelected();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 48:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isUnderMouse();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 49:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isVisible();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 50:
    if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        bool _q_result = _q_self->isVisibleTo(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 51:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isWidget();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 52:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isWindow();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 53:
    if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        QTransform _q_result = _q_self->itemTransform(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        bool* _q_arg1 = qscriptvalue_cast<bool*>(context->argument(1));
        QTransform _q_result = _q_self->itemTransform(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 54:
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QGraphicsItem*>(context->argument(0))
            && (qMetaTypeId<QPainterPath>() == context->argument(1).toVariant().userType())) {
            QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
            QPainterPath _q_arg1 = qscriptvalue_cast<QPainterPath>(context->argument(1));
            QPainterPath _q_result = _q_self->mapFromItem(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QGraphicsItem*>(context->argument(0))
            && (qMetaTypeId<QPointF>() == context->argument(1).toVariant().userType())) {
            QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
            QPointF _q_arg1 = qscriptvalue_cast<QPointF>(context->argument(1));
            QPointF _q_result = _q_self->mapFromItem(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QGraphicsItem*>(context->argument(0))
            && (qMetaTypeId<QPolygonF>() == context->argument(1).toVariant().userType())) {
            QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
            QPolygonF _q_arg1 = qscriptvalue_cast<QPolygonF>(context->argument(1));
            QPolygonF _q_result = _q_self->mapFromItem(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QGraphicsItem*>(context->argument(0))
            && (qMetaTypeId<QRectF>() == context->argument(1).toVariant().userType())) {
            QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
            QRectF _q_arg1 = qscriptvalue_cast<QRectF>(context->argument(1));
            QPolygonF _q_result = _q_self->mapFromItem(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        QPointF _q_result = _q_self->mapFromItem(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        QPolygonF _q_result = _q_self->mapFromItem(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 55:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPainterPath>() == context->argument(0).toVariant().userType())) {
            QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
            QPainterPath _q_result = _q_self->mapFromParent(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            QPointF _q_result = _q_self->mapFromParent(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPolygonF>() == context->argument(0).toVariant().userType())) {
            QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
            QPolygonF _q_result = _q_self->mapFromParent(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            QPolygonF _q_result = _q_self->mapFromParent(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QPointF _q_result = _q_self->mapFromParent(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QPolygonF _q_result = _q_self->mapFromParent(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 56:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPainterPath>() == context->argument(0).toVariant().userType())) {
            QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
            QPainterPath _q_result = _q_self->mapFromScene(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            QPointF _q_result = _q_self->mapFromScene(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPolygonF>() == context->argument(0).toVariant().userType())) {
            QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
            QPolygonF _q_result = _q_self->mapFromScene(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            QPolygonF _q_result = _q_self->mapFromScene(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QPointF _q_result = _q_self->mapFromScene(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QPolygonF _q_result = _q_self->mapFromScene(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 57:
    if (context->argumentCount() == 2) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        QRectF _q_arg1 = qscriptvalue_cast<QRectF>(context->argument(1));
        QRectF _q_result = _q_self->mapRectFromItem(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        QRectF _q_result = _q_self->mapRectFromItem(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 58:
    if (context->argumentCount() == 1) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        QRectF _q_result = _q_self->mapRectFromParent(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QRectF _q_result = _q_self->mapRectFromParent(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 59:
    if (context->argumentCount() == 1) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        QRectF _q_result = _q_self->mapRectFromScene(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QRectF _q_result = _q_self->mapRectFromScene(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 60:
    if (context->argumentCount() == 2) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        QRectF _q_arg1 = qscriptvalue_cast<QRectF>(context->argument(1));
        QRectF _q_result = _q_self->mapRectToItem(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        QRectF _q_result = _q_self->mapRectToItem(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 61:
    if (context->argumentCount() == 1) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        QRectF _q_result = _q_self->mapRectToParent(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QRectF _q_result = _q_self->mapRectToParent(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 62:
    if (context->argumentCount() == 1) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        QRectF _q_result = _q_self->mapRectToScene(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QRectF _q_result = _q_self->mapRectToScene(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 63:
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QGraphicsItem*>(context->argument(0))
            && (qMetaTypeId<QPainterPath>() == context->argument(1).toVariant().userType())) {
            QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
            QPainterPath _q_arg1 = qscriptvalue_cast<QPainterPath>(context->argument(1));
            QPainterPath _q_result = _q_self->mapToItem(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QGraphicsItem*>(context->argument(0))
            && (qMetaTypeId<QPointF>() == context->argument(1).toVariant().userType())) {
            QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
            QPointF _q_arg1 = qscriptvalue_cast<QPointF>(context->argument(1));
            QPointF _q_result = _q_self->mapToItem(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QGraphicsItem*>(context->argument(0))
            && (qMetaTypeId<QPolygonF>() == context->argument(1).toVariant().userType())) {
            QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
            QPolygonF _q_arg1 = qscriptvalue_cast<QPolygonF>(context->argument(1));
            QPolygonF _q_result = _q_self->mapToItem(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QGraphicsItem*>(context->argument(0))
            && (qMetaTypeId<QRectF>() == context->argument(1).toVariant().userType())) {
            QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
            QRectF _q_arg1 = qscriptvalue_cast<QRectF>(context->argument(1));
            QPolygonF _q_result = _q_self->mapToItem(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        QPointF _q_result = _q_self->mapToItem(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        QPolygonF _q_result = _q_self->mapToItem(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 64:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPainterPath>() == context->argument(0).toVariant().userType())) {
            QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
            QPainterPath _q_result = _q_self->mapToParent(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            QPointF _q_result = _q_self->mapToParent(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPolygonF>() == context->argument(0).toVariant().userType())) {
            QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
            QPolygonF _q_result = _q_self->mapToParent(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            QPolygonF _q_result = _q_self->mapToParent(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QPointF _q_result = _q_self->mapToParent(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QPolygonF _q_result = _q_self->mapToParent(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 65:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPainterPath>() == context->argument(0).toVariant().userType())) {
            QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
            QPainterPath _q_result = _q_self->mapToScene(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            QPointF _q_result = _q_self->mapToScene(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPolygonF>() == context->argument(0).toVariant().userType())) {
            QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
            QPolygonF _q_result = _q_self->mapToScene(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            QPolygonF _q_result = _q_self->mapToScene(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QPointF _q_result = _q_self->mapToScene(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QPolygonF _q_result = _q_self->mapToScene(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 66:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->moveBy(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 67:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->opacity();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 68:
    if (context->argumentCount() == 0) {
        QPainterPath _q_result = _q_self->opaqueArea();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 69:
    if (context->argumentCount() == 2) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QStyleOptionGraphicsItem* _q_arg1 = qscriptvalue_cast<QStyleOptionGraphicsItem*>(context->argument(1));
        _q_self->paint(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QStyleOptionGraphicsItem* _q_arg1 = qscriptvalue_cast<QStyleOptionGraphicsItem*>(context->argument(1));
        QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(2));
        _q_self->paint(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 70:
    if (context->argumentCount() == 0) {
        QGraphicsItem* _q_result = _q_self->panel();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 71:
    if (context->argumentCount() == 0) {
        QGraphicsItem::PanelModality _q_result = _q_self->panelModality();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 72:
    if (context->argumentCount() == 0) {
        QGraphicsItem* _q_result = _q_self->parentItem();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 73:
    if (context->argumentCount() == 0) {
        QGraphicsObject* _q_result = _q_self->parentObject();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 74:
    if (context->argumentCount() == 0) {
        QGraphicsWidget* _q_result = _q_self->parentWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 75:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->pos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 76:
    if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        _q_self->removeSceneEventFilter(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 77:
    if (context->argumentCount() == 0) {
        _q_self->resetTransform();
        return context->engine()->undefinedValue();
    }
    break;

    case 78:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->rotate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 79:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->rotation();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 80:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->scale();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->scale(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 81:
    if (context->argumentCount() == 0) {
        QGraphicsScene* _q_result = _q_self->scene();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 82:
    if (context->argumentCount() == 0) {
        QRectF _q_result = _q_self->sceneBoundingRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 83:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->scenePos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 84:
    if (context->argumentCount() == 0) {
        QTransform _q_result = _q_self->sceneTransform();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 85:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->scroll(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QRectF _q_arg2 = qscriptvalue_cast<QRectF>(context->argument(2));
        _q_self->scroll(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 86:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setAcceptDrops(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 87:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setAcceptHoverEvents(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 88:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setAcceptTouchEvents(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 89:
    if (context->argumentCount() == 1) {
        QFlags<Qt::MouseButton> _q_arg0 = qscriptvalue_cast<QFlags<Qt::MouseButton> >(context->argument(0));
        _q_self->setAcceptedMouseButtons(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 90:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setAcceptsHoverEvents(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 91:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setActive(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 92:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setBoundingRegionGranularity(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 93:
    if (context->argumentCount() == 1) {
        QGraphicsItem::CacheMode _q_arg0 = qscriptvalue_cast<QGraphicsItem::CacheMode>(context->argument(0));
        _q_self->setCacheMode(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QGraphicsItem::CacheMode _q_arg0 = qscriptvalue_cast<QGraphicsItem::CacheMode>(context->argument(0));
        QSize _q_arg1 = qscriptvalue_cast<QSize>(context->argument(1));
        _q_self->setCacheMode(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 94:
    if (context->argumentCount() == 1) {
        QCursor _q_arg0 = qscriptvalue_cast<QCursor>(context->argument(0));
        _q_self->setCursor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 95:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QVariant _q_arg1 = context->argument(1).toVariant();
        _q_self->setData(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 96:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setEnabled(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 97:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setFiltersChildEvents(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 98:
    if (context->argumentCount() == 1) {
        QGraphicsItem::GraphicsItemFlag _q_arg0 = qscriptvalue_cast<QGraphicsItem::GraphicsItemFlag>(context->argument(0));
        _q_self->setFlag(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QGraphicsItem::GraphicsItemFlag _q_arg0 = qscriptvalue_cast<QGraphicsItem::GraphicsItemFlag>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setFlag(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 99:
    if (context->argumentCount() == 1) {
        QFlags<QGraphicsItem::GraphicsItemFlag> _q_arg0 = qscriptvalue_cast<QFlags<QGraphicsItem::GraphicsItemFlag> >(context->argument(0));
        _q_self->setFlags(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 100:
    if (context->argumentCount() == 0) {
        _q_self->setFocus();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        Qt::FocusReason _q_arg0 = qscriptvalue_cast<Qt::FocusReason>(context->argument(0));
        _q_self->setFocus(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 101:
    if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        _q_self->setFocusProxy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 102:
    if (context->argumentCount() == 1) {
        QGraphicsEffect* _q_arg0 = qscriptvalue_cast<QGraphicsEffect*>(context->argument(0));
        _q_self->setGraphicsEffect(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 103:
    if (context->argumentCount() == 1) {
        QGraphicsItemGroup* _q_arg0 = qscriptvalue_cast<QGraphicsItemGroup*>(context->argument(0));
        _q_self->setGroup(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 104:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setHandlesChildEvents(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 105:
    if (context->argumentCount() == 1) {
        QFlags<Qt::InputMethodHint> _q_arg0 = qscriptvalue_cast<QFlags<Qt::InputMethodHint> >(context->argument(0));
        _q_self->setInputMethodHints(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 106:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setOpacity(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 107:
    if (context->argumentCount() == 1) {
        QGraphicsItem::PanelModality _q_arg0 = qscriptvalue_cast<QGraphicsItem::PanelModality>(context->argument(0));
        _q_self->setPanelModality(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 108:
    if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        _q_self->setParentItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 109:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setPos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->setPos(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 110:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setRotation(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 111:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setScale(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 112:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setSelected(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 113:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setToolTip(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 114:
    if (context->argumentCount() == 1) {
        QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
        _q_self->setTransform(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setTransform(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 115:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setTransformOriginPoint(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->setTransformOriginPoint(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 116:
    if (context->argumentCount() == 1) {
        QList<QGraphicsTransform*> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setTransformations(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 117:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setVisible(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 118:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setX(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 119:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setY(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 120:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setZValue(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 121:
    if (context->argumentCount() == 0) {
        QPainterPath _q_result = _q_self->shape();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 122:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->shear(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 123:
    if (context->argumentCount() == 0) {
        _q_self->show();
        return context->engine()->undefinedValue();
    }
    break;

    case 124:
    if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        _q_self->stackBefore(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 125:
    if (context->argumentCount() == 0) {
        QGraphicsObject* _q_result = _q_self->toGraphicsObject();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 126:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toolTip();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 127:
    if (context->argumentCount() == 0) {
        QGraphicsItem* _q_result = _q_self->topLevelItem();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 128:
    if (context->argumentCount() == 0) {
        QGraphicsWidget* _q_result = _q_self->topLevelWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 129:
    if (context->argumentCount() == 0) {
        QTransform _q_result = _q_self->transform();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 130:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->transformOriginPoint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 131:
    if (context->argumentCount() == 0) {
        QList<QGraphicsTransform*> _q_result = _q_self->transformations();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 132:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->translate(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 133:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->type();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 134:
    if (context->argumentCount() == 0) {
        _q_self->ungrabKeyboard();
        return context->engine()->undefinedValue();
    }
    break;

    case 135:
    if (context->argumentCount() == 0) {
        _q_self->ungrabMouse();
        return context->engine()->undefinedValue();
    }
    break;

    case 136:
    if (context->argumentCount() == 0) {
        _q_self->unsetCursor();
        return context->engine()->undefinedValue();
    }
    break;

    case 137:
    if (context->argumentCount() == 0) {
        _q_self->update();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        _q_self->update(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->update(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 138:
    if (context->argumentCount() == 0) {
        QGraphicsWidget* _q_result = _q_self->window();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 139:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->x();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 140:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->y();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 141:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->zValue();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 142: {
    QString result;
    QDebug d(&result);
    d << _q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsItem_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsItem_function_names[_id+1],
        qtscript_QGraphicsItem_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsItem_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsItem(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsItem* _q_cpp_result = new QtScriptShell_QGraphicsItem();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        QtScriptShell_QGraphicsItem* _q_cpp_result = new QtScriptShell_QGraphicsItem(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        QGraphicsScene* _q_arg1 = qscriptvalue_cast<QGraphicsScene*>(context->argument(1));
        QtScriptShell_QGraphicsItem* _q_cpp_result = new QtScriptShell_QGraphicsItem(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsItem_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsItem_function_names[_id],
        qtscript_QGraphicsItem_function_signatures[_id]);
}

QScriptValue qtscript_create_QGraphicsItem_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsItem*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsItem*)0));
    for (int i = 0; i < 143; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsItem_prototype_call, qtscript_QGraphicsItem_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsItem_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGraphicsItem*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsItem_static_call, proto, qtscript_QGraphicsItem_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("CacheMode"),
        qtscript_create_QGraphicsItem_CacheMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("PanelModality"),
        qtscript_create_QGraphicsItem_PanelModality_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("GraphicsItemFlag"),
        qtscript_create_QGraphicsItem_GraphicsItemFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("GraphicsItemFlags"),
        qtscript_create_QGraphicsItem_GraphicsItemFlags_class(engine));
    ctor.setProperty(QString::fromLatin1("GraphicsItemChange"),
        qtscript_create_QGraphicsItem_GraphicsItemChange_class(engine, ctor));
    return ctor;
}
