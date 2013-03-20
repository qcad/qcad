#include "qtscriptshell_QGraphicsPolygonItem.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbrush.h>
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
#include <qpen.h>
#include <qpoint.h>
#include <qpolygon.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qstyleoption.h>
#include <qtransform.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(Qt::ItemSelectionMode)
Q_DECLARE_METATYPE(QPainterPath)
Q_DECLARE_METATYPE(QGraphicsSceneContextMenuEvent*)
Q_DECLARE_METATYPE(QGraphicsSceneDragDropEvent*)
Q_DECLARE_METATYPE(QFocusEvent*)
Q_DECLARE_METATYPE(QGraphicsSceneHoverEvent*)
Q_DECLARE_METATYPE(QInputMethodEvent*)
Q_DECLARE_METATYPE(Qt::InputMethodQuery)
Q_DECLARE_METATYPE(QGraphicsItem::GraphicsItemChange)
Q_DECLARE_METATYPE(QKeyEvent*)
Q_DECLARE_METATYPE(QGraphicsSceneMouseEvent*)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QStyleOptionGraphicsItem*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QGraphicsSceneWheelEvent*)

QtScriptShell_QGraphicsPolygonItem::QtScriptShell_QGraphicsPolygonItem(QGraphicsItem*  parent, QGraphicsScene*  scene)
    : QGraphicsPolygonItem(parent, scene) {}

QtScriptShell_QGraphicsPolygonItem::QtScriptShell_QGraphicsPolygonItem(const QPolygonF&  polygon, QGraphicsItem*  parent, QGraphicsScene*  scene)
    : QGraphicsPolygonItem(polygon, parent, scene) {}

QtScriptShell_QGraphicsPolygonItem::~QtScriptShell_QGraphicsPolygonItem() {}

void QtScriptShell_QGraphicsPolygonItem::advance(int  phase)
{
    QScriptValue _q_function = __qtscript_self.property("advance");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("advance") & QScriptValue::QObjectMember)) {
        QGraphicsPolygonItem::advance(phase);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, phase));
    }
}

QRectF  QtScriptShell_QGraphicsPolygonItem::boundingRect() const
{
    QScriptValue _q_function = __qtscript_self.property("boundingRect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("boundingRect") & QScriptValue::QObjectMember)) {
        return QGraphicsPolygonItem::boundingRect();
    } else {
        return qscriptvalue_cast<QRectF >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QGraphicsPolygonItem::collidesWithItem(const QGraphicsItem*  other, Qt::ItemSelectionMode  mode) const
{
    QScriptValue _q_function = __qtscript_self.property("collidesWithItem");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("collidesWithItem") & QScriptValue::QObjectMember)) {
        return QGraphicsPolygonItem::collidesWithItem(other, mode);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QGraphicsItem *>(other))
            << qScriptValueFromValue(_q_engine, mode)));
    }
}

bool  QtScriptShell_QGraphicsPolygonItem::collidesWithPath(const QPainterPath&  path, Qt::ItemSelectionMode  mode) const
{
    QScriptValue _q_function = __qtscript_self.property("collidesWithPath");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("collidesWithPath") & QScriptValue::QObjectMember)) {
        return QGraphicsPolygonItem::collidesWithPath(path, mode);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, path)
            << qScriptValueFromValue(_q_engine, mode)));
    }
}

bool  QtScriptShell_QGraphicsPolygonItem::contains(const QPointF&  point) const
{
    QScriptValue _q_function = __qtscript_self.property("contains");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("contains") & QScriptValue::QObjectMember)) {
        return QGraphicsPolygonItem::contains(point);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, point)));
    }
}

void QtScriptShell_QGraphicsPolygonItem::contextMenuEvent(QGraphicsSceneContextMenuEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("contextMenuEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("contextMenuEvent") & QScriptValue::QObjectMember)) {
        QGraphicsPolygonItem::contextMenuEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QGraphicsPolygonItem::dragEnterEvent(QGraphicsSceneDragDropEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dragEnterEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragEnterEvent") & QScriptValue::QObjectMember)) {
        QGraphicsPolygonItem::dragEnterEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QGraphicsPolygonItem::dragLeaveEvent(QGraphicsSceneDragDropEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dragLeaveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragLeaveEvent") & QScriptValue::QObjectMember)) {
        QGraphicsPolygonItem::dragLeaveEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QGraphicsPolygonItem::dragMoveEvent(QGraphicsSceneDragDropEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dragMoveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragMoveEvent") & QScriptValue::QObjectMember)) {
        QGraphicsPolygonItem::dragMoveEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QGraphicsPolygonItem::dropEvent(QGraphicsSceneDragDropEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dropEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dropEvent") & QScriptValue::QObjectMember)) {
        QGraphicsPolygonItem::dropEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

QVariant  QtScriptShell_QGraphicsPolygonItem::extension(const QVariant&  variant) const
{
    QScriptValue _q_function = __qtscript_self.property("extension");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("extension") & QScriptValue::QObjectMember)) {
        return QGraphicsPolygonItem::extension(variant);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, variant)));
    }
}

void QtScriptShell_QGraphicsPolygonItem::focusInEvent(QFocusEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("focusInEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusInEvent") & QScriptValue::QObjectMember)) {
        QGraphicsPolygonItem::focusInEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QGraphicsPolygonItem::focusOutEvent(QFocusEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("focusOutEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusOutEvent") & QScriptValue::QObjectMember)) {
        QGraphicsPolygonItem::focusOutEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QGraphicsPolygonItem::hoverEnterEvent(QGraphicsSceneHoverEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("hoverEnterEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hoverEnterEvent") & QScriptValue::QObjectMember)) {
        QGraphicsPolygonItem::hoverEnterEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QGraphicsPolygonItem::hoverLeaveEvent(QGraphicsSceneHoverEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("hoverLeaveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hoverLeaveEvent") & QScriptValue::QObjectMember)) {
        QGraphicsPolygonItem::hoverLeaveEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QGraphicsPolygonItem::hoverMoveEvent(QGraphicsSceneHoverEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("hoverMoveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hoverMoveEvent") & QScriptValue::QObjectMember)) {
        QGraphicsPolygonItem::hoverMoveEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QGraphicsPolygonItem::inputMethodEvent(QInputMethodEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("inputMethodEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("inputMethodEvent") & QScriptValue::QObjectMember)) {
        QGraphicsPolygonItem::inputMethodEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

QVariant  QtScriptShell_QGraphicsPolygonItem::inputMethodQuery(Qt::InputMethodQuery  query) const
{
    QScriptValue _q_function = __qtscript_self.property("inputMethodQuery");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("inputMethodQuery") & QScriptValue::QObjectMember)) {
        return QGraphicsPolygonItem::inputMethodQuery(query);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, query)));
    }
}

bool  QtScriptShell_QGraphicsPolygonItem::isObscuredBy(const QGraphicsItem*  item) const
{
    QScriptValue _q_function = __qtscript_self.property("isObscuredBy");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isObscuredBy") & QScriptValue::QObjectMember)) {
        return QGraphicsPolygonItem::isObscuredBy(item);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QGraphicsItem *>(item))));
    }
}

QVariant  QtScriptShell_QGraphicsPolygonItem::itemChange(QGraphicsItem::GraphicsItemChange  change, const QVariant&  value)
{
    QScriptValue _q_function = __qtscript_self.property("itemChange");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("itemChange") & QScriptValue::QObjectMember)) {
        return QGraphicsPolygonItem::itemChange(change, value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, change)
            << qScriptValueFromValue(_q_engine, value)));
    }
}

void QtScriptShell_QGraphicsPolygonItem::keyPressEvent(QKeyEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("keyPressEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("keyPressEvent") & QScriptValue::QObjectMember)) {
        QGraphicsPolygonItem::keyPressEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QGraphicsPolygonItem::keyReleaseEvent(QKeyEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("keyReleaseEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("keyReleaseEvent") & QScriptValue::QObjectMember)) {
        QGraphicsPolygonItem::keyReleaseEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QGraphicsPolygonItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mouseDoubleClickEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseDoubleClickEvent") & QScriptValue::QObjectMember)) {
        QGraphicsPolygonItem::mouseDoubleClickEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QGraphicsPolygonItem::mouseMoveEvent(QGraphicsSceneMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mouseMoveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseMoveEvent") & QScriptValue::QObjectMember)) {
        QGraphicsPolygonItem::mouseMoveEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QGraphicsPolygonItem::mousePressEvent(QGraphicsSceneMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mousePressEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mousePressEvent") & QScriptValue::QObjectMember)) {
        QGraphicsPolygonItem::mousePressEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QGraphicsPolygonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mouseReleaseEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseReleaseEvent") & QScriptValue::QObjectMember)) {
        QGraphicsPolygonItem::mouseReleaseEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

QPainterPath  QtScriptShell_QGraphicsPolygonItem::opaqueArea() const
{
    QScriptValue _q_function = __qtscript_self.property("opaqueArea");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("opaqueArea") & QScriptValue::QObjectMember)) {
        return QGraphicsPolygonItem::opaqueArea();
    } else {
        return qscriptvalue_cast<QPainterPath >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QGraphicsPolygonItem::paint(QPainter*  painter, const QStyleOptionGraphicsItem*  option, QWidget*  widget)
{
    QScriptValue _q_function = __qtscript_self.property("paint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paint") & QScriptValue::QObjectMember)) {
        QGraphicsPolygonItem::paint(painter, option, widget);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOptionGraphicsItem *>(option))
            << qScriptValueFromValue(_q_engine, widget));
    }
}

bool  QtScriptShell_QGraphicsPolygonItem::sceneEvent(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("sceneEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sceneEvent") & QScriptValue::QObjectMember)) {
        return QGraphicsPolygonItem::sceneEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event)));
    }
}

bool  QtScriptShell_QGraphicsPolygonItem::sceneEventFilter(QGraphicsItem*  watched, QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("sceneEventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sceneEventFilter") & QScriptValue::QObjectMember)) {
        return QGraphicsPolygonItem::sceneEventFilter(watched, event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, watched)
            << qScriptValueFromValue(_q_engine, event)));
    }
}

QPainterPath  QtScriptShell_QGraphicsPolygonItem::shape() const
{
    QScriptValue _q_function = __qtscript_self.property("shape");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("shape") & QScriptValue::QObjectMember)) {
        return QGraphicsPolygonItem::shape();
    } else {
        return qscriptvalue_cast<QPainterPath >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QGraphicsPolygonItem::type() const
{
    QScriptValue _q_function = __qtscript_self.property("type");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("type") & QScriptValue::QObjectMember)) {
        return QGraphicsPolygonItem::type();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QGraphicsPolygonItem::wheelEvent(QGraphicsSceneWheelEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("wheelEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("wheelEvent") & QScriptValue::QObjectMember)) {
        QGraphicsPolygonItem::wheelEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

