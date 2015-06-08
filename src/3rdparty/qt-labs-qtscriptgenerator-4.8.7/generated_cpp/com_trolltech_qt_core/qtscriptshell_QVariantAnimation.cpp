#include "qtscriptshell_QVariantAnimation.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qanimationgroup.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qeasingcurve.h>
#include <qlist.h>
#include <qobject.h>
#include <qpair.h>
#include <qvariantanimation.h>
#include <qvector.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QTimerEvent*)
Q_DECLARE_METATYPE(QAbstractAnimation::Direction)
Q_DECLARE_METATYPE(QAbstractAnimation::State)

QtScriptShell_QVariantAnimation::QtScriptShell_QVariantAnimation(QObject*  parent)
    : QVariantAnimation(parent) {}

QtScriptShell_QVariantAnimation::~QtScriptShell_QVariantAnimation() {}

void QtScriptShell_QVariantAnimation::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QVariantAnimation::childEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QVariantAnimation::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QVariantAnimation::customEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

int  QtScriptShell_QVariantAnimation::duration() const
{
    QScriptValue _q_function = __qtscript_self.property("_qs_duration");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("_qs_duration") & QScriptValue::QObjectMember)) {
        return QVariantAnimation::duration();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QVariantAnimation::event(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QVariantAnimation::event(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event)));
    }
}

bool  QtScriptShell_QVariantAnimation::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QVariantAnimation::eventFilter(arg__1, arg__2);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
    }
}

QVariant  QtScriptShell_QVariantAnimation::interpolated(const QVariant&  from, const QVariant&  to, qreal  progress) const
{
    QScriptValue _q_function = __qtscript_self.property("interpolated");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("interpolated") & QScriptValue::QObjectMember)) {
        return QVariantAnimation::interpolated(from, to, progress);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, from)
            << qScriptValueFromValue(_q_engine, to)
            << qScriptValueFromValue(_q_engine, progress)));
    }
}

void QtScriptShell_QVariantAnimation::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QVariantAnimation::timerEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QVariantAnimation::updateCurrentTime(int  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("updateCurrentTime");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateCurrentTime") & QScriptValue::QObjectMember)) {
        QVariantAnimation::updateCurrentTime(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QVariantAnimation::updateCurrentValue(const QVariant&  value)
{
    QScriptValue _q_function = __qtscript_self.property("updateCurrentValue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateCurrentValue") & QScriptValue::QObjectMember)) {
        qFatal("QVariantAnimation::updateCurrentValue() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
    }
}

void QtScriptShell_QVariantAnimation::updateDirection(QAbstractAnimation::Direction  direction)
{
    QScriptValue _q_function = __qtscript_self.property("updateDirection");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateDirection") & QScriptValue::QObjectMember)) {
        QVariantAnimation::updateDirection(direction);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, direction));
    }
}

void QtScriptShell_QVariantAnimation::updateState(QAbstractAnimation::State  newState, QAbstractAnimation::State  oldState)
{
    QScriptValue _q_function = __qtscript_self.property("updateState");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateState") & QScriptValue::QObjectMember)) {
        QVariantAnimation::updateState(newState, oldState);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, newState)
            << qScriptValueFromValue(_q_engine, oldState));
    }
}

