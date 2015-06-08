#include "qtscriptshell_QInputContext.h"

#include <QtScript/QScriptEngine>
#include <QTextFormat>
#include <QVariant>
#include <qaction.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qevent.h>
#include <qfont.h>
#include <qinputcontext.h>
#include <qlist.h>
#include <qobject.h>
#include <qtextformat.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QAction*)
Q_DECLARE_METATYPE(QList<QAction*>)
Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QMouseEvent*)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QInputContext::QtScriptShell_QInputContext(QObject*  parent)
    : QInputContext(parent) {}

QtScriptShell_QInputContext::~QtScriptShell_QInputContext() {}

QList<QAction* >  QtScriptShell_QInputContext::actions()
{
    QScriptValue _q_function = __qtscript_self.property("actions");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("actions") & QScriptValue::QObjectMember)) {
        return QInputContext::actions();
    } else {
        return qscriptvalue_cast<QList<QAction* > >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QInputContext::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QInputContext::childEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QInputContext::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QInputContext::customEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

bool  QtScriptShell_QInputContext::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QInputContext::event(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

bool  QtScriptShell_QInputContext::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QInputContext::eventFilter(arg__1, arg__2);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
    }
}

bool  QtScriptShell_QInputContext::filterEvent(const QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("filterEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("filterEvent") & QScriptValue::QObjectMember)) {
        return QInputContext::filterEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QEvent *>(event))));
    }
}

QFont  QtScriptShell_QInputContext::font() const
{
    QScriptValue _q_function = __qtscript_self.property("font");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("font") & QScriptValue::QObjectMember)) {
        return QInputContext::font();
    } else {
        return qscriptvalue_cast<QFont >(_q_function.call(__qtscript_self));
    }
}

QString  QtScriptShell_QInputContext::identifierName()
{
    QScriptValue _q_function = __qtscript_self.property("identifierName");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("identifierName") & QScriptValue::QObjectMember)) {
        qFatal("QInputContext::identifierName() is abstract!");
    } else {
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QInputContext::isComposing() const
{
    QScriptValue _q_function = __qtscript_self.property("isComposing");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isComposing") & QScriptValue::QObjectMember)) {
        qFatal("QInputContext::isComposing() is abstract!");
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

QString  QtScriptShell_QInputContext::language()
{
    QScriptValue _q_function = __qtscript_self.property("language");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("language") & QScriptValue::QObjectMember)) {
        qFatal("QInputContext::language() is abstract!");
    } else {
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QInputContext::mouseHandler(int  x, QMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mouseHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseHandler") & QScriptValue::QObjectMember)) {
        QInputContext::mouseHandler(x, event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, x)
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QInputContext::reset()
{
    QScriptValue _q_function = __qtscript_self.property("reset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("reset") & QScriptValue::QObjectMember)) {
        qFatal("QInputContext::reset() is abstract!");
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QInputContext::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QInputContext::timerEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QInputContext::update()
{
    QScriptValue _q_function = __qtscript_self.property("update");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("update") & QScriptValue::QObjectMember)) {
        QInputContext::update();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QInputContext::widgetDestroyed(QWidget*  w)
{
    QScriptValue _q_function = __qtscript_self.property("widgetDestroyed");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("widgetDestroyed") & QScriptValue::QObjectMember)) {
        QInputContext::widgetDestroyed(w);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, w));
    }
}

