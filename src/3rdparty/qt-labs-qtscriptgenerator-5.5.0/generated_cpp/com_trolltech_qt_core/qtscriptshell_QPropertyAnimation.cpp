#include "qtscriptshell_QPropertyAnimation.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qanimationgroup.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qeasingcurve.h>
#include <qlist.h>
#include <qobject.h>
#include <qpair.h>
#include <qpropertyanimation.h>
#include <qvector.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QTimerEvent*)
Q_DECLARE_METATYPE(QAbstractAnimation::Direction)
Q_DECLARE_METATYPE(QAbstractAnimation::State)

QtScriptShell_QPropertyAnimation::QtScriptShell_QPropertyAnimation(QObject*  parent)
    : QPropertyAnimation(parent) {}

QtScriptShell_QPropertyAnimation::QtScriptShell_QPropertyAnimation(QObject*  target, const QByteArray&  propertyName, QObject*  parent)
    : QPropertyAnimation(target, propertyName, parent) {}

QtScriptShell_QPropertyAnimation::~QtScriptShell_QPropertyAnimation() {}

void QtScriptShell_QPropertyAnimation::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QPropertyAnimation::childEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QPropertyAnimation::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QPropertyAnimation::customEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

int  QtScriptShell_QPropertyAnimation::duration() const
{
    QScriptValue _q_function = __qtscript_self.property("_qs_duration");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("_qs_duration") & QScriptValue::QObjectMember)) {
        return QPropertyAnimation::duration();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QPropertyAnimation::event(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QPropertyAnimation::event(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event)));
    }
}

bool  QtScriptShell_QPropertyAnimation::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QPropertyAnimation::eventFilter(arg__1, arg__2);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
    }
}

QVariant  QtScriptShell_QPropertyAnimation::interpolated(const QVariant&  from, const QVariant&  to, qreal  progress) const
{
    QScriptValue _q_function = __qtscript_self.property("interpolated");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("interpolated") & QScriptValue::QObjectMember)) {
        return QPropertyAnimation::interpolated(from, to, progress);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, from)
            << qScriptValueFromValue(_q_engine, to)
            << qScriptValueFromValue(_q_engine, progress)));
    }
}

void QtScriptShell_QPropertyAnimation::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QPropertyAnimation::timerEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QPropertyAnimation::updateCurrentTime(int  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("updateCurrentTime");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateCurrentTime") & QScriptValue::QObjectMember)) {
        QPropertyAnimation::updateCurrentTime(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QPropertyAnimation::updateCurrentValue(const QVariant&  value)
{
    QScriptValue _q_function = __qtscript_self.property("updateCurrentValue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateCurrentValue") & QScriptValue::QObjectMember)) {
        QPropertyAnimation::updateCurrentValue(value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
    }
}

void QtScriptShell_QPropertyAnimation::updateDirection(QAbstractAnimation::Direction  direction)
{
    QScriptValue _q_function = __qtscript_self.property("updateDirection");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateDirection") & QScriptValue::QObjectMember)) {
        QPropertyAnimation::updateDirection(direction);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, direction));
    }
}

void QtScriptShell_QPropertyAnimation::updateState(QAbstractAnimation::State  newState, QAbstractAnimation::State  oldState)
{
    QScriptValue _q_function = __qtscript_self.property("updateState");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateState") & QScriptValue::QObjectMember)) {
        QPropertyAnimation::updateState(newState, oldState);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, newState)
            << qScriptValueFromValue(_q_engine, oldState));
    }
}

