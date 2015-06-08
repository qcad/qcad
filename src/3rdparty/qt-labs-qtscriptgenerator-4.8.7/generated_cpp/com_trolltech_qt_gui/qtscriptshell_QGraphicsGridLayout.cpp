#include "qtscriptshell_QGraphicsGridLayout.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qcoreevent.h>
#include <qgraphicsgridlayout.h>
#include <qgraphicsitem.h>
#include <qgraphicslayoutitem.h>
#include <qrect.h>
#include <qsize.h>
#include <qsizepolicy.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(qreal*)
Q_DECLARE_METATYPE(QGraphicsLayoutItem*)
Q_DECLARE_METATYPE(Qt::SizeHint)
Q_DECLARE_METATYPE(QEvent*)

QtScriptShell_QGraphicsGridLayout::QtScriptShell_QGraphicsGridLayout(QGraphicsLayoutItem*  parent)
    : QGraphicsGridLayout(parent) {}

QtScriptShell_QGraphicsGridLayout::~QtScriptShell_QGraphicsGridLayout() {}

int  QtScriptShell_QGraphicsGridLayout::count() const
{
    QScriptValue _q_function = __qtscript_self.property("count");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("count") & QScriptValue::QObjectMember)) {
        return QGraphicsGridLayout::count();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QGraphicsGridLayout::getContentsMargins(qreal*  left, qreal*  top, qreal*  right, qreal*  bottom) const
{
    QScriptValue _q_function = __qtscript_self.property("getContentsMargins");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("getContentsMargins") & QScriptValue::QObjectMember)) {
        QGraphicsGridLayout::getContentsMargins(left, top, right, bottom);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, left)
            << qScriptValueFromValue(_q_engine, top)
            << qScriptValueFromValue(_q_engine, right)
            << qScriptValueFromValue(_q_engine, bottom));
    }
}

void QtScriptShell_QGraphicsGridLayout::invalidate()
{
    QScriptValue _q_function = __qtscript_self.property("invalidate");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("invalidate") & QScriptValue::QObjectMember)) {
        QGraphicsGridLayout::invalidate();
    } else {
        _q_function.call(__qtscript_self);
    }
}

QGraphicsLayoutItem*  QtScriptShell_QGraphicsGridLayout::itemAt(int  index) const
{
    QScriptValue _q_function = __qtscript_self.property("itemAt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("itemAt") & QScriptValue::QObjectMember)) {
        return QGraphicsGridLayout::itemAt(index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QGraphicsLayoutItem* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
    }
}

void QtScriptShell_QGraphicsGridLayout::removeAt(int  index)
{
    QScriptValue _q_function = __qtscript_self.property("removeAt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("removeAt") & QScriptValue::QObjectMember)) {
        QGraphicsGridLayout::removeAt(index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index));
    }
}

void QtScriptShell_QGraphicsGridLayout::setGeometry(const QRectF&  rect)
{
    QScriptValue _q_function = __qtscript_self.property("setGeometry");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setGeometry") & QScriptValue::QObjectMember)) {
        QGraphicsGridLayout::setGeometry(rect);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, rect));
    }
}

QSizeF  QtScriptShell_QGraphicsGridLayout::sizeHint(Qt::SizeHint  which, const QSizeF&  constraint) const
{
    QScriptValue _q_function = __qtscript_self.property("sizeHint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeHint") & QScriptValue::QObjectMember)) {
        return QGraphicsGridLayout::sizeHint(which, constraint);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QSizeF >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, which)
            << qScriptValueFromValue(_q_engine, constraint)));
    }
}

void QtScriptShell_QGraphicsGridLayout::updateGeometry()
{
    QScriptValue _q_function = __qtscript_self.property("updateGeometry");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateGeometry") & QScriptValue::QObjectMember)) {
        QGraphicsGridLayout::updateGeometry();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QGraphicsGridLayout::widgetEvent(QEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("widgetEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("widgetEvent") & QScriptValue::QObjectMember)) {
        QGraphicsGridLayout::widgetEvent(e);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
    }
}

